#!/usr/bin/env python3
"""inject-suffix-bytes.py — append N bytes at the end of a function in a .o
file, then grow the function's st_size and shift everything after by +N.

**SCOPE 2026-05-25:** the instruction-appending use of this script (combined
with INSN_PATCH / PROLOGUE_STEALS) was REMOVED 2026-05-23 as match-faking; see
`feedback_no_instruction_forcing_matches_policy`. The only sanctioned current
use is **appending all-zero data-padding bytes** (matches genuine trailing-zero
data in the ROM symbol, no instruction-byte editing).

Historical context (no longer applicable as a pipeline):
  ~ Mirror of inject-prefix-bytes.py for the prologue-stolen-PREDECESSOR class:
  ~ when a successor function used PROLOGUE_STEALS=N (its &D-load prologue
  ~ lived in the predecessor's tail), the predecessor's expected st_size
  ~ INCLUDED those N trailing dead bytes... PROLOGUE_STEALS is now banned.

Operations on the .o (mechanism unchanged):
  1. .text section: insert n_bytes (the suffix word(s)) at the END
     of the function (st_value + st_size). Following bytes shift by +n_bytes.
  2. Symbol table: leave func's st_value unchanged. Grow func's st_size by
     n_bytes. Shift any other text-section symbol with st_value >=
     (func_addr + func_size_old) by +n_bytes.
  3. .rel.text: shift any reloc with r_offset >= (func_addr + func_size_old)
     by +n_bytes.
  4. Section header table: grow .text sh_size by n_bytes; shift sh_offset of
     subsequent sections by +n_bytes.

Sanctioned use today: SUFFIX_BYTES=N where N bytes are all zeros, matching
trailing-zero data within the function's ROM symbol (e.g. word-aligned padding
the .s declares as part of the function but IDO doesn't emit). NOT for
instruction-bytes that complete a partial codegen (banned).

Detect-and-skip: if the bytes at (func_addr + func_size_old - n_bytes) already
match the suffix words (e.g. INCLUDE_ASM build path where the .s already
emitted them), no-op.
"""
import argparse
import struct
import sys
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
REL_FMT = ">II"


class ElfPatcher:
    def __init__(self, data: bytes):
        self.data = bytearray(data)
        self._parse_header()
        self._parse_sections()

    def _parse_header(self):
        h = struct.unpack(ELF_HDR_FMT, self.data[:struct.calcsize(ELF_HDR_FMT)])
        (self.e_ident, self.e_type, self.e_machine, self.e_version,
         self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
         self.e_ehsize, self.e_phentsize, self.e_phnum,
         self.e_shentsize, self.e_shnum, self.e_shstrndx) = h
        assert self.e_ident[:4] == b"\x7fELF"
        assert self.e_ident[4] == 1
        assert self.e_ident[5] == 2

    def _parse_sections(self):
        self.sections = []
        for i in range(self.e_shnum):
            off = self.e_shoff + i * self.e_shentsize
            self.sections.append(list(struct.unpack(
                SECT_HDR_FMT, bytes(self.data[off:off + self.e_shentsize]))))
        shstr = self.sections[self.e_shstrndx]
        self.shstrtab = bytes(self.data[shstr[4]:shstr[4] + shstr[5]])

    def section_name(self, idx):
        name_off = self.sections[idx][0]
        end = self.shstrtab.index(b"\x00", name_off)
        return self.shstrtab[name_off:end].decode("ascii")

    def find_section(self, name):
        for i in range(self.e_shnum):
            if self.section_name(i) == name:
                return i
        raise KeyError(name)

    def has_section(self, name):
        try:
            self.find_section(name)
            return True
        except KeyError:
            return False

    def iter_symtab(self, symtab_idx):
        sec = self.sections[symtab_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        for i in range(size // ent):
            entry_off = off + i * ent
            yield i, list(struct.unpack(
                SYM_FMT, bytes(self.data[entry_off:entry_off + ent])))

    def write_sym(self, symtab_idx, sym_idx, fields):
        sec = self.sections[symtab_idx]
        off = sec[4] + sym_idx * sec[9]
        self.data[off:off + sec[9]] = struct.pack(SYM_FMT, *fields)

    def strtab_string(self, strtab_idx, name_off):
        sec = self.sections[strtab_idx]
        off = sec[4] + name_off
        end = self.data.index(b"\x00", off)
        return bytes(self.data[off:end]).decode("ascii")

    def find_symbol(self, name):
        symtab_idx = self.find_section(".symtab")
        strtab_idx = self.sections[symtab_idx][6]
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if self.strtab_string(strtab_idx, fields[0]) == name:
                return sym_idx, fields, symtab_idx
        return None

    def write_section_header(self, idx):
        off = self.e_shoff + idx * self.e_shentsize
        self.data[off:off + self.e_shentsize] = struct.pack(
            SECT_HDR_FMT, *self.sections[idx])

    def write_elf_header(self):
        self.data[:struct.calcsize(ELF_HDR_FMT)] = struct.pack(
            ELF_HDR_FMT,
            self.e_ident, self.e_type, self.e_machine, self.e_version,
            self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
            self.e_ehsize, self.e_phentsize, self.e_phnum,
            self.e_shentsize, self.e_shnum, self.e_shstrndx)

    def insert_text_bytes(self, text_idx, insert_off_in_text, payload):
        n = len(payload)
        text_sec = self.sections[text_idx]
        text_file_off = text_sec[4]
        absolute_insert = text_file_off + insert_off_in_text
        self.data[absolute_insert:absolute_insert] = payload
        text_sec[5] += n
        for i, sec in enumerate(self.sections):
            if i == text_idx:
                continue
            if sec[4] >= absolute_insert:
                sec[4] += n
        if self.e_shoff >= absolute_insert:
            self.e_shoff += n
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()

    def shift_symbols(self, after_addr_incl, n_bytes, exempt_sym_idx):
        """Shift text-section symbols with st_value >= after_addr_incl by
        +n_bytes (except the exempt sym). The exempt sym is the function whose
        st_value stays put but st_size grows."""
        symtab_idx = self.find_section(".symtab")
        text_idx = self.find_section(".text")
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if sym_idx == exempt_sym_idx:
                continue
            if fields[5] != text_idx:
                continue
            if fields[1] >= after_addr_incl:
                fields[1] += n_bytes
                self.write_sym(symtab_idx, sym_idx, fields)

    def grow_func_size(self, sym_idx, n_bytes, symtab_idx):
        for idx, fields in self.iter_symtab(symtab_idx):
            if idx == sym_idx:
                fields[2] += n_bytes
                self.write_sym(symtab_idx, idx, fields)
                return
        raise RuntimeError("target sym disappeared")

    def grow_section_symbol(self, section_idx, n_bytes):
        symtab_idx = self.find_section(".symtab")
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if fields[5] == section_idx and (fields[3] & 0xF) == 3:
                fields[2] += n_bytes
                self.write_sym(symtab_idx, sym_idx, fields)
                return

    def shift_relocations(self, after_addr_incl, n_bytes):
        if not self.has_section(".rel.text"):
            return
        rel_idx = self.find_section(".rel.text")
        sec = self.sections[rel_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        n = size // ent
        for i in range(n):
            entry_off = off + i * ent
            r_off, r_info = struct.unpack(
                REL_FMT, bytes(self.data[entry_off:entry_off + ent]))
            if r_off >= after_addr_incl:
                r_off += n_bytes
                self.data[entry_off:entry_off + ent] = struct.pack(
                    REL_FMT, r_off, r_info)


def inject_suffix(o_path: Path, func_name: str, suffix_words: list[int],
                  verify: bool, allow_natural_epilogue: bool = False,
                  skip_if_size_ge: int | None = None):
    n_bytes = 4 * len(suffix_words)
    payload = b"".join(struct.pack(">I", w) for w in suffix_words)

    raw = o_path.read_bytes()
    elf = ElfPatcher(raw)
    found = elf.find_symbol(func_name)
    if found is None:
        raise KeyError(f"function {func_name} not found")
    sym_idx, fields, symtab_idx = found
    func_addr = fields[1]
    func_size = fields[2]
    tail_addr = func_addr + func_size  # where suffix is inserted

    if skip_if_size_ge is not None and func_size >= skip_if_size_ge:
        print(f"inject-suffix-skip: {func_name} size {func_size:#x} >= "
              f"{skip_if_size_ge:#x}; no-op",
              file=sys.stderr)
        return

    text_idx = elf.find_section(".text")
    text_off = elf.sections[text_idx][4]

    if verify:
        # Skip path 1: bytes AT the tail (post-st_size) already match the
        # suffix. Happens when running the script twice in a row.
        # FALSE-POSITIVE (2026-07-11): when the target fn is the LAST fn in the
        # object and a PRECEDING fn's C body shrinks, this fn shifts and the
        # bytes now sitting after its st_size are trailing .text zeros that
        # coincidentally == the all-zero payload → injection wrongly skipped,
        # dropping the fn's forced suffix (e.g. bootup func_0000F1B4 went
        # 100%→80% when func_00000E68 was width-fixed smaller). --allow-natural-
        # epilogue (which the NON_MATCHING_SUFFIX_BYTES_FORCE Makefile path
        # already passes = "force") now bypasses skip-path-1 too, so FORCE
        # always injects. Safe: each build recompiles the .o before injecting,
        # so the re-run double-inject this guard protected against can't occur.
        existing = bytes(elf.data[text_off + tail_addr:
                                   text_off + tail_addr + n_bytes])
        if existing == payload and not allow_natural_epilogue:
            print(f"inject-suffix-skip: {func_name} already has suffix bytes "
                  f"at tail (likely re-run); no-op",
                  file=sys.stderr)
            return
        # Skip path 2: the function's TRAILING n_bytes (inside st_size) already
        # match the suffix payload. This is the INCLUDE_ASM build path: the .s
        # file's symbol declaration encompasses the suffix bytes (e.g. when
        # the suffix is the stolen-prologue of the next function), so the
        # baseline build naturally produces a function with the suffix already
        # baked in. C-emit builds produce a shorter function and rely on this
        # (FALSE-POSITIVE GUARD): when the C body's natural epilogue happens
        # to be `jr ra; nop` AND the suffix payload is also `jr ra; nop`
        # (because target's actual tail has those bytes appended after a
        # body that ends in `lw ra; addiu sp`), this check would skip even
        # though injection is required. Pass --allow-natural-epilogue to
        # bypass skip-path-2 for these known false-positive cases. See
        # docs/POST_CC_RECIPES.md
        # #feedback-suffix-skip-path-2-false-positive-on-natural-epilogue.
        # script to extend it.
        if func_size >= n_bytes and not allow_natural_epilogue:
            in_func_tail = bytes(elf.data[text_off + tail_addr - n_bytes:
                                           text_off + tail_addr])
            if in_func_tail == payload:
                print(f"inject-suffix-skip: {func_name} already ends with "
                      f"suffix bytes inside st_size (INCLUDE_ASM build path); "
                      f"no-op", file=sys.stderr)
                return
        # Verify the function's last insn is `nop` (delay slot of jr ra) — the
        # standard end of a function before any trailing dead/stolen-prologue
        # bytes. The tail-1 insn should be `jr ra` (0x03E00008).
        if func_size < 8:
            print(f"WARN: {func_name} too small ({func_size} bytes) for "
                  f"suffix injection; refusing", file=sys.stderr)
            sys.exit(1)
        last = struct.unpack(
            ">I", bytes(elf.data[text_off + tail_addr - 4:
                                  text_off + tail_addr]))[0]
        prev = struct.unpack(
            ">I", bytes(elf.data[text_off + tail_addr - 8:
                                  text_off + tail_addr - 4]))[0]
        if prev != 0x03E00008:
            print(f"WARN: {func_name} doesn't end with jr ra+nop "
                  f"(insn[-2]={prev:#010x}, insn[-1]={last:#010x}); refusing "
                  f"to inject suffix", file=sys.stderr)
            sys.exit(1)

    elf.insert_text_bytes(text_idx, tail_addr, payload)
    # Grow target function's size; do NOT touch its st_value.
    elf.grow_func_size(sym_idx, n_bytes, symtab_idx)
    # Also handle the .NON_MATCHING twin OBJECT symbol if present.
    twin = elf.find_symbol(func_name + ".NON_MATCHING")
    if twin is not None:
        t_idx, t_fields, _ = twin
        if t_fields[1] == func_addr:
            t_fields[2] += n_bytes
            elf.write_sym(symtab_idx, t_idx, t_fields)
    # Grow .text section symbol so it still covers the section.
    elf.grow_section_symbol(text_idx, n_bytes)
    # Shift symbols whose st_value is at or after the suffix insertion point.
    elf.shift_symbols(tail_addr, n_bytes, exempt_sym_idx=sym_idx)
    # Shift relocations whose r_offset is at or after the suffix point.
    elf.shift_relocations(tail_addr, n_bytes)

    o_path.write_bytes(bytes(elf.data))
    print(f"inject-suffix: {func_name} appended {n_bytes} bytes "
          f"({' '.join(f'{w:#010x}' for w in suffix_words)})",
          file=sys.stderr)


def parse_words(spec: str) -> list[int]:
    return [int(w, 0) for w in spec.split(",")]


def main():
    ap = argparse.ArgumentParser(
        description="Append N bytes at the end of a function in a .o file "
                    "and grow the function's symbol coverage. Mirror of "
                    "inject-prefix-bytes.py for prologue-stolen-PREDECESSOR.")
    ap.add_argument("o_file", type=Path)
    ap.add_argument("func_name")
    ap.add_argument("suffix",
                    help="comma-separated hex words, e.g. 0x3C020000,0x24420000")
    ap.add_argument("--no-verify", action="store_true")
    ap.add_argument("--allow-natural-epilogue", action="store_true",
                    help="Bypass skip-path-2 (the INCLUDE_ASM-build false-"
                         "positive on natural-jr-ra-nop epilogue C bodies). "
                         "[Historical: was used when SUFFIX_BYTES + INSN_PATCH "
                         "together overwrote the body's last 2 insns. "
                         "INSN_PATCH was removed 2026-05-23 as match-faking; "
                         "this flag is now only relevant for the all-zero "
                         "data-padding case where the genuine padding shares "
                         "those last 2 byte positions.]")
    ap.add_argument("--skip-if-size-ge", type=lambda s: int(s, 0),
                    help="No-op when the function symbol is already at least "
                         "this size. Useful for C builds that need a forced "
                         "suffix but INCLUDE_ASM baselines already cover it.")
    args = ap.parse_args()
    inject_suffix(args.o_file, args.func_name, parse_words(args.suffix),
                  verify=not args.no_verify,
                  allow_natural_epilogue=args.allow_natural_epilogue,
                  skip_if_size_ge=args.skip_if_size_ge)


if __name__ == "__main__":
    main()
