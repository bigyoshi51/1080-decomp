#!/usr/bin/env python3
"""Bake R_MIPS_HI16/LO16 data relocations into a raw .text binary.

The Yay0-compressed USOs build their code block by `objcopy -O binary
--only-section=.text` of a .o, then crunch64-compressing the result. objcopy
extracts the .text *pre-link*, so any relocations are left UNAPPLIED (raw
addend, usually 0). For INCLUDE_ASM functions that's fine (raw .word = ROM
bytes). But a decompiled C body that references a data symbol at a non-zero
%lo (e.g. `lui at,%hi(D_0000014C); sw rX,%lo(D_0000014C)(at)`) ends up with a
raw 0 where the real ROM has the baked %lo (0x14c) — the blob diverges even
though objdiff (reloc-aware) scores the .o as a match.

This script applies the HI16/LO16 data relocations to the extracted .text
binary, exactly the values the USO ships:
  - R_MIPS_HI16 / R_MIPS_LO16: baked from the symbol value (+ in-place addend).
  - Everything else (notably R_MIPS_26 jal): left RAW — the USO ships jals
    unrelocated and fixes them via its load-time reloc table.

Symbol values come from the .o's own symtab when defined there, else from the
linker symbol file (undefined_syms_auto.txt: `NAME = 0xVALUE;`). This is a
no-op for %lo=0 refs (e.g. &D_00000000), so it does not disturb existing
splits whose data refs all resolve to 0.

Usage: bake-data-relocs.py <elf.o> <text.bin> <undefined_syms.txt> [--bake-jal-pinned]
The .text binary is modified in place.

--bake-jal-pinned (opt-in, per block rule): also fill R_MIPS_26 fields whose
symbol is UNDEFINED in the .o and pinned in undefined_syms (the in-unit jal
alias convention: an alias pinned to the module-relative target the ROM ships
pre-filled, e.g. timproc b1 `timproc_uso_b1_func_0000083C_jal = 0x83C`). This
is what the linker does for the same alias in a directly linked unit. Defined
symbols and unpinned names (imports, jal 0) stay raw.
"""
import sys, struct
from elftools.elf.elffile import ELFFile
from elftools.elf.constants import SH_FLAGS

R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6


def parse_syms_file(path):
    vals = {}
    with open(path) as f:
        for line in f:
            line = line.split("//")[0].strip()
            if "=" not in line:
                continue
            name, _, rhs = line.partition("=")
            name = name.strip()
            rhs = rhs.strip().rstrip(";").strip()
            try:
                vals[name] = int(rhs, 0)
            except ValueError:
                pass
    return vals


def sext16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def main():
    elf_path, bin_path, syms_path = sys.argv[1], sys.argv[2], sys.argv[3]
    bake_jal = "--bake-jal-pinned" in sys.argv[4:]
    linker_syms = parse_syms_file(syms_path)

    with open(elf_path, "rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        if text is None:
            return
        text_idx = elf.get_section_index(".text")
        symtab = elf.get_section_by_name(".symtab")

        # find the relocation section that targets .text
        relsec = None
        for sec in elf.iter_sections():
            if sec.header["sh_info"] == text_idx and sec.header["sh_type"] in (
                "SHT_REL",
                "SHT_RELA",
            ):
                relsec = sec
                break
        if relsec is None:
            return

        def symval(sym_idx):
            sym = symtab.get_symbol(sym_idx)
            name = sym.name
            if sym["st_shndx"] != "SHN_UNDEF":
                return sym["st_value"]
            if name in linker_syms:
                return linker_syms[name]
            raise SystemExit(
                f"bake-data-relocs: {elf_path}: no value for symbol '{name}'"
            )

        # Resolve everything while the ELF file is still open: (offset, type, value)
        relocs = []
        for r in sorted(relsec.iter_relocations(), key=lambda r: r["r_offset"]):
            rtype = r["r_info_type"]
            val = None
            if rtype in (R_MIPS_HI16, R_MIPS_LO16):
                val = symval(r["r_info_sym"])
            elif rtype == R_MIPS_26 and bake_jal:
                sym = symtab.get_symbol(r["r_info_sym"])
                if sym["st_shndx"] == "SHN_UNDEF" and sym.name in linker_syms:
                    val = linker_syms[sym.name]
            relocs.append((r["r_offset"], rtype, val))

    data = bytearray(open(bin_path, "rb").read())
    size = len(data)

    def rd(off):
        return struct.unpack(">H", data[off + 2 : off + 4])[0]

    def wr(off, val):
        data[off + 2 : off + 4] = struct.pack(">H", val & 0xFFFF)

    pending_hi = []
    for off, rtype, val in relocs:
        if off + 4 > size:
            continue  # past the truncated .text
        if rtype == R_MIPS_HI16:
            pending_hi.append((off, val))
        elif rtype == R_MIPS_LO16:
            lo_imm = rd(off)
            for hoff, hval in pending_hi:
                hi_imm = rd(hoff)
                v = hval + (hi_imm << 16) + sext16(lo_imm)
                wr(hoff, ((v + 0x8000) >> 16) & 0xFFFF)
            pending_hi = []
            v = val + sext16(lo_imm)
            wr(off, v & 0xFFFF)
        elif rtype == R_MIPS_26 and val is not None:
            w = struct.unpack(">I", data[off : off + 4])[0]
            field = ((w & 0x03FFFFFF) + (val >> 2)) & 0x03FFFFFF
            data[off : off + 4] = struct.pack(">I", (w & 0xFC000000) | field)
        # other R_MIPS_26 and everything else: leave raw (USO load-time relocs)

    if pending_hi:
        raise SystemExit(
            f"bake-data-relocs: {elf_path}: {len(pending_hi)} HI16 reloc(s) "
            "without a matching LO16"
        )

    with open(bin_path, "wb") as f:
        f.write(data)


if __name__ == "__main__":
    main()
