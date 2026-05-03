#!/usr/bin/env python3
"""inject-prefix-bytes.py — insert N bytes (a USO loader-trampoline word, etc.)
at the start of a function in a .o file, then grow the function's st_size and
shift everything after by +N.

Use case: USO entry-0 functions whose target asm starts with a runtime-patched
trampoline insn (e.g. `beq zero,zero,+0x6F00`, encoded `0x10006F00`) before the
standard C-compiled body. The body alone matches target's offsets [N, end);
prepending the trampoline makes the whole function bytewise identical.

Why post-cc and not via #pragma GLOBAL_ASM(prefix.s)? asm-processor's per-block
min-instruction-count check (6 at -O0, 2 at -O2) rejects 1-word sidecars. This
script bypasses asm-processor entirely.

Operations on the .o:
  1. .text section: insert n_bytes (the trampoline word) at the function's
     st_value. All following bytes shift by +n_bytes.
  2. Symbol table: leave func's st_value unchanged (insertion happened AT it,
     so it now covers the prefix). Grow func's st_size by n_bytes. Shift any
     other text-section symbol with st_value > func's by +n_bytes.
  3. .rel.text: shift any reloc with r_offset >= (func_addr + n_bytes) by
     +n_bytes. (Body bytes that had relocs are now at +n_bytes.) Relocs at
     positions strictly inside the original [func_addr, func_addr + body_size)
     range are body-relative and ALL move by +n_bytes.
  4. Section header table: grow .text sh_size by n_bytes; shift sh_offset of
     subsequent sections by +n_bytes.

Detect-and-skip: if the function's first insn already matches the prefix
(e.g. INCLUDE_ASM build path), no-op. This lets `make expected` reuse the
same Makefile recipe for INCLUDE_ASM-emit builds.
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

    def shift_symbols(self, after_addr_excl, n_bytes, exempt_sym_idx):
        """Shift text-section symbols with st_value > after_addr_excl by +n_bytes
        (except the exempt sym). The exempt sym is the function whose st_value
        stays put (insertion happened AT its address) but st_size grows."""
        symtab_idx = self.find_section(".symtab")
        text_idx = self.find_section(".text")
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if sym_idx == exempt_sym_idx:
                continue
            if fields[5] != text_idx:
                continue
            if fields[1] > after_addr_excl:
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


def inject_prefix(o_path: Path, func_name: str, prefix_words: list[int],
                  verify: bool):
    n_bytes = 4 * len(prefix_words)
    payload = b"".join(struct.pack(">I", w) for w in prefix_words)

    raw = o_path.read_bytes()
    elf = ElfPatcher(raw)
    found = elf.find_symbol(func_name)
    if found is None:
        raise KeyError(f"function {func_name} not found")
    sym_idx, fields, symtab_idx = found
    func_addr = fields[1]
    func_size = fields[2]

    text_idx = elf.find_section(".text")
    text_off = elf.sections[text_idx][4]

    if verify:
        first = struct.unpack(
            ">I", bytes(elf.data[text_off + func_addr:
                                 text_off + func_addr + 4]))[0]
        if first == prefix_words[0]:
            print(f"inject-skip: {func_name} already starts with prefix word "
                  f"{first:#010x} (likely an INCLUDE_ASM build); no-op",
                  file=sys.stderr)
            return
        # Body should start with a real prologue insn — either:
        #   - addiu sp,sp,-N  (0x27BDxxxx) — normal function with stack frame
        #   - jr ra           (0x03E00008) — empty void function (no prologue)
        if (first >> 16) != 0x27BD and first != 0x03E00008:
            print(f"WARN: {func_name} first insn is {first:#010x}, expected "
                  f"addiu sp prologue (0x27BDxxxx) or jr ra (0x03E00008); "
                  f"refusing to patch",
                  file=sys.stderr)
            sys.exit(1)

    elf.insert_text_bytes(text_idx, func_addr, payload)
    # Grow target function's size; do NOT touch its st_value (insertion was AT
    # st_value so the prefix is now part of the function).
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
    # Shift symbols whose st_value is strictly after the function's start.
    elf.shift_symbols(func_addr, n_bytes, exempt_sym_idx=sym_idx)
    # Shift relocations whose r_offset is at or after the function's body
    # (which is now at func_addr + n_bytes). All body relocs move by +n.
    elf.shift_relocations(func_addr, n_bytes)

    o_path.write_bytes(bytes(elf.data))
    print(f"inject: {func_name} prepended {n_bytes} bytes "
          f"({' '.join(f'{w:#010x}' for w in prefix_words)})",
          file=sys.stderr)


def parse_words(spec: str) -> list[int]:
    """Parse comma-separated hex words: '0x10006F00' or '0x10006F00,0x00000000'."""
    return [int(w, 0) for w in spec.split(",")]


def main():
    ap = argparse.ArgumentParser(
        description="Insert N bytes at the start of a function in a .o file "
                    "and grow the function's symbol coverage.")
    ap.add_argument("o_file", type=Path)
    ap.add_argument("func_name")
    ap.add_argument("prefix",
                    help="comma-separated hex words, e.g. 0x10006F00")
    ap.add_argument("--no-verify", action="store_true")
    args = ap.parse_args()
    inject_prefix(args.o_file, args.func_name, parse_words(args.prefix),
                  verify=not args.no_verify)


if __name__ == "__main__":
    main()
