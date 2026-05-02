#!/usr/bin/env python3
"""splice-function-prefix.py — remove a redundant N-byte prefix from a function's
emit in a .o file, fixing up symbol values, sizes, and relocations.

Use case: prologue-stolen-successor cases where the predecessor's INCLUDE_ASM
already emits the lui+addiu that sets up a base register, and the C-emit for
the successor naturally produces the same lui+addiu at its own start. The
8-byte duplication shifts everything after by +8 in the .o; this script splices
those 8 bytes out and slides everything down.

Operations:
  1. .text section: delete bytes [func_addr, func_addr+N)
  2. Symbol table: shift all symbols with st_value >= func_addr+N by -N
                   shrink target function's st_size by N (st_value unchanged)
  3. Relocation table: drop entries with r_offset in [func_addr, func_addr+N)
                       shift remaining: r_offset >= func_addr+N → -= N
  4. Section header table: shrink .text sh_size by N
                           shift sh_offset of subsequent sections by -N

Pre-conditions: target function's first N bytes must be a "redundant prefix"
that's already present at the predecessor's tail. Caller is responsible for
verifying that — this script doesn't sanity-check semantically.
"""
import argparse
import struct
import sys
from pathlib import Path

# ELF32 big-endian struct formats
ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"  # e_ident, type, machine, version, entry,
                                    # phoff, shoff, flags, ehsize, phentsize,
                                    # phnum, shentsize, shnum, shstrndx
SECT_HDR_FMT = ">IIIIIIIIII"  # name, type, flags, addr, offset, size, link,
                              # info, addralign, entsize
SYM_FMT = ">IIIBBH"  # name, value, size, info, other, shndx
REL_FMT = ">II"  # offset, info

SHT_PROGBITS = 1
SHT_SYMTAB = 2
SHT_STRTAB = 3
SHT_REL = 9


class ElfWriter:
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
        assert self.e_ident[:4] == b"\x7fELF", "not an ELF file"
        assert self.e_ident[4] == 1, "not ELF32"
        assert self.e_ident[5] == 2, "not big-endian"
        assert self.e_shentsize == struct.calcsize(SECT_HDR_FMT)

    def _parse_sections(self):
        self.sections = []
        for i in range(self.e_shnum):
            off = self.e_shoff + i * self.e_shentsize
            fields = struct.unpack(SECT_HDR_FMT,
                                   bytes(self.data[off:off + self.e_shentsize]))
            self.sections.append(list(fields))
        # Read section name strings from shstrtab
        shstrtab = self.sections[self.e_shstrndx]
        strtab_off = shstrtab[4]
        strtab_size = shstrtab[5]
        self.shstrtab_data = bytes(self.data[strtab_off:strtab_off + strtab_size])

    def section_name(self, idx: int) -> str:
        name_off = self.sections[idx][0]
        end = self.shstrtab_data.index(b"\x00", name_off)
        return self.shstrtab_data[name_off:end].decode("ascii")

    def find_section(self, name: str) -> int:
        for i in range(self.e_shnum):
            if self.section_name(i) == name:
                return i
        raise KeyError(f"section {name} not found")

    def get_symtab(self, sym_section_idx: int):
        """Yield (sym_idx, [name_off, value, size, info, other, shndx])."""
        sec = self.sections[sym_section_idx]
        off = sec[4]
        size = sec[5]
        entsize = sec[9]
        assert entsize == struct.calcsize(SYM_FMT), \
            f"unexpected sym entsize {entsize}"
        n = size // entsize
        for i in range(n):
            entry_off = off + i * entsize
            fields = list(struct.unpack(
                SYM_FMT, bytes(self.data[entry_off:entry_off + entsize])))
            yield i, fields

    def write_symtab_entry(self, sym_section_idx: int, sym_idx: int, fields):
        sec = self.sections[sym_section_idx]
        off = sec[4] + sym_idx * sec[9]
        self.data[off:off + sec[9]] = struct.pack(SYM_FMT, *fields)

    def get_strtab_string(self, strtab_idx: int, name_off: int) -> str:
        sec = self.sections[strtab_idx]
        off = sec[4] + name_off
        end = self.data.index(b"\x00", off)
        return bytes(self.data[off:end]).decode("ascii")

    def find_symbol_by_name(self, name: str):
        symtab_idx = self.find_section(".symtab")
        strtab_idx = self.sections[symtab_idx][6]  # sh_link → strtab
        for sym_idx, fields in self.get_symtab(symtab_idx):
            if self.get_strtab_string(strtab_idx, fields[0]) == name:
                return sym_idx, fields, symtab_idx, strtab_idx
        raise KeyError(f"symbol {name} not found")

    def write_section_header(self, idx: int):
        off = self.e_shoff + idx * self.e_shentsize
        self.data[off:off + self.e_shentsize] = struct.pack(
            SECT_HDR_FMT, *self.sections[idx])

    def splice_text(self, text_idx: int, splice_off_in_text: int, n_bytes: int):
        """Delete n_bytes from .text starting at splice_off_in_text (offset
        within the section, NOT file offset). Shifts file offsets of every
        section whose sh_offset > .text's sh_offset by -n_bytes."""
        text_sec = self.sections[text_idx]
        text_file_off = text_sec[4]
        absolute_splice = text_file_off + splice_off_in_text
        # Delete bytes
        del self.data[absolute_splice:absolute_splice + n_bytes]
        # Shrink .text size
        text_sec[5] -= n_bytes
        # Shift sh_offset of all sections whose data follows the splice point
        for i, sec in enumerate(self.sections):
            if i == text_idx:
                continue
            if sec[4] > absolute_splice:
                sec[4] -= n_bytes
        # Shift e_shoff if it follows the splice
        if self.e_shoff > absolute_splice:
            self.e_shoff -= n_bytes
        # Write all section headers
        for i in range(self.e_shnum):
            self.write_section_header(i)
        # Write ELF header (e_shoff may have changed)
        self.data[:struct.calcsize(ELF_HDR_FMT)] = struct.pack(
            ELF_HDR_FMT,
            self.e_ident, self.e_type, self.e_machine, self.e_version,
            self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
            self.e_ehsize, self.e_phentsize, self.e_phnum,
            self.e_shentsize, self.e_shnum, self.e_shstrndx)

    def sync_section_symbol(self, section_idx: int):
        """Set the section symbol's st_size to match the section header's
        current sh_size. objdiff bounds-checks function symbols against this
        and rejects parsing if any sym extends past it. Setting from sh_size
        (rather than subtracting our splice bytes) handles the case where
        an earlier build step (e.g. asm-processor's alignment reduction)
        already shrunk sh_size but didn't update the section symbol."""
        target_size = self.sections[section_idx][5]  # current sh_size
        symtab_idx = self.find_section(".symtab")
        for sym_idx, fields in self.get_symtab(symtab_idx):
            # Section symbols have st_info type STT_SECTION (3) and shndx == section_idx.
            if fields[5] == section_idx and (fields[3] & 0xF) == 3:
                fields[2] = target_size
                self.write_symtab_entry(symtab_idx, sym_idx, fields)
                return

    def shift_symbols(self, splice_addr: int, n_bytes: int, exempt_sym_idx: int):
        """Shift all symbols with st_value > splice_addr by -n_bytes
        (except the exempt sym, whose st_value stays put — its size shrunk
        separately). Shifts apply only to symbols in section .text."""
        symtab_idx = self.find_section(".symtab")
        text_idx = self.find_section(".text")
        for sym_idx, fields in self.get_symtab(symtab_idx):
            if sym_idx == exempt_sym_idx:
                continue
            shndx = fields[5]
            if shndx != text_idx:
                continue
            # Symbol is in .text. Shift if st_value >= splice_addr + n_bytes
            # (strictly inside the spliced range gets dropped; we don't expect
            # any other symbols at the spliced location).
            if fields[1] >= splice_addr + n_bytes:
                fields[1] -= n_bytes
                self.write_symtab_entry(symtab_idx, sym_idx, fields)
            elif splice_addr <= fields[1] < splice_addr + n_bytes:
                raise RuntimeError(
                    f"symbol at st_value=0x{fields[1]:x} is inside the "
                    f"spliced range [0x{splice_addr:x}, "
                    f"0x{splice_addr + n_bytes:x}) — splice would orphan it")

    def fix_target_symbol_size(self, sym_idx: int, n_bytes: int, symtab_idx: int):
        """Shrink the target symbol's st_size by n_bytes."""
        for idx, fields in self.get_symtab(symtab_idx):
            if idx == sym_idx:
                fields[2] -= n_bytes
                self.write_symtab_entry(symtab_idx, idx, fields)
                return
        raise RuntimeError("target sym disappeared")

    def fix_relocations(self, splice_addr: int, n_bytes: int):
        """Drop relocations in [splice_addr, splice_addr+n_bytes); shift
        relocations with r_offset >= splice_addr+n_bytes by -n_bytes."""
        rel_idx = self.find_section(".rel.text")
        sec = self.sections[rel_idx]
        off = sec[4]
        size = sec[5]
        entsize = sec[9]
        assert entsize == struct.calcsize(REL_FMT)
        n = size // entsize
        new_entries = []
        for i in range(n):
            r_off, r_info = struct.unpack(
                REL_FMT, bytes(self.data[off + i * entsize:
                                         off + (i + 1) * entsize]))
            if splice_addr <= r_off < splice_addr + n_bytes:
                continue  # drop
            if r_off >= splice_addr + n_bytes:
                r_off -= n_bytes
            new_entries.append((r_off, r_info))
        # Pack new entries
        new_data = b"".join(struct.pack(REL_FMT, o, i) for o, i in new_entries)
        old_size = size
        new_size = len(new_data)
        # Replace bytes; if size shrank, splice .rel.text section too
        delta = old_size - new_size
        self.data[off:off + old_size] = new_data
        if delta != 0:
            sec[5] = new_size
            # Shift sh_offset of sections whose data follows .rel.text
            rel_end = off + old_size
            for i, s in enumerate(self.sections):
                if i == rel_idx:
                    continue
                if s[4] >= rel_end:
                    s[4] -= delta
            if self.e_shoff >= rel_end:
                self.e_shoff -= delta
            for i in range(self.e_shnum):
                self.write_section_header(i)
            self.data[:struct.calcsize(ELF_HDR_FMT)] = struct.pack(
                ELF_HDR_FMT,
                self.e_ident, self.e_type, self.e_machine, self.e_version,
                self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
                self.e_ehsize, self.e_phentsize, self.e_phnum,
                self.e_shentsize, self.e_shnum, self.e_shstrndx)


def splice_prefix(o_path: Path, func_name: str, n_bytes: int, verify: bool):
    raw = o_path.read_bytes()
    elf = ElfWriter(raw)

    sym_idx, sym_fields, symtab_idx, _strtab_idx = elf.find_symbol_by_name(func_name)
    func_addr = sym_fields[1]
    func_size = sym_fields[2]

    if verify:
        # Detect-and-skip: when the function's first insn isn't LUI, we're
        # most likely processing an INCLUDE_ASM-derived .o (e.g. during
        # `make expected` via refresh-expected-baseline.py — the C body got
        # swapped for INCLUDE_ASM, and the asm starts with `addiu sp` not
        # `lui`). No prefix to splice → silent no-op so the same Makefile
        # works for both C-emit builds and INCLUDE_ASM-emit builds.
        text_idx = elf.find_section(".text")
        text_off = elf.sections[text_idx][4] + func_addr
        first_word = struct.unpack(">I", bytes(elf.data[text_off:text_off + 4]))[0]
        second_word = struct.unpack(">I", bytes(elf.data[text_off + 4:text_off + 8]))[0]
        opcode1 = (first_word >> 26) & 0x3F
        opcode2 = (second_word >> 26) & 0x3F
        if opcode1 != 0x0F:  # not LUI — this .o was built from INCLUDE_ASM
            print(f"splice-skip: {func_name} doesn't start with LUI "
                  f"(word={first_word:#010x}); leaving as-is "
                  f"(probably an INCLUDE_ASM build path)", file=sys.stderr)
            return
        if opcode2 not in (0x09, 0x23, 0x25, 0x21):  # ADDIU, LW, LHU, ADDU
            print(f"WARN: {func_name}+4 is not ADDIU/LW "
                  f"(opcode={opcode2:#x}, word={second_word:#010x})", file=sys.stderr)
            sys.exit(1)
        print(f"verify: {func_name} starts with "
              f"opcode {opcode1:#x}+{opcode2:#x} ({first_word:#010x} {second_word:#010x})",
              file=sys.stderr)

    text_idx = elf.find_section(".text")

    # 1. Splice .text bytes [func_addr, func_addr + n_bytes)
    elf.splice_text(text_idx, func_addr, n_bytes)

    # 2. Shift symbols
    elf.shift_symbols(func_addr, n_bytes, exempt_sym_idx=sym_idx)

    # 3. Shrink target sym size
    elf.fix_target_symbol_size(sym_idx, n_bytes, symtab_idx)

    # 4. (Section symbol untouched.) Pre-splice .o has section symbol st_size
    #    >= sh_size (asm-processor's alignment truncation shrinks sh_size but
    #    leaves the section symbol at its original logical extent). Preserving
    #    that relationship lets the section symbol cover function symbols that
    #    extend past sh_size into alignment-pad bytes.

    # 5. Fix .rel.text
    elf.fix_relocations(func_addr, n_bytes)

    o_path.write_bytes(bytes(elf.data))
    print(f"spliced {n_bytes} bytes from start of {func_name} in {o_path}",
          file=sys.stderr)


def main():
    ap = argparse.ArgumentParser(
        description="Splice a redundant N-byte prefix from a function's emit "
                    "in a .o file (prologue-stolen successor cases).")
    ap.add_argument("o_file", type=Path, help="path to .c.o file")
    ap.add_argument("func_name", help="symbol name of the function to shrink")
    ap.add_argument("-n", "--bytes", type=int, default=8,
                    help="number of bytes to remove from the function's start "
                         "(default 8 = lui+addiu)")
    ap.add_argument("--no-verify", action="store_true",
                    help="skip the lui+addiu sanity check")
    args = ap.parse_args()
    splice_prefix(args.o_file, args.func_name, args.bytes,
                  verify=not args.no_verify)


if __name__ == "__main__":
    main()
