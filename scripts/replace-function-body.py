#!/usr/bin/env python3
"""Replace one function body in a MIPS ELF .o with bytes from a donor .o.

This is for compressed USO blocks that are extracted from a single .o, where
ordinary file-splitting would put an -O0 function in the wrong text stream.
The destination object still compiles the C body, then this script swaps just
that function's bytes with a verified donor body and shifts later symbols and
relocations if the size changes.
"""
import argparse
import struct
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
REL_FMT = ">II"


class Elf:
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
        if self.e_ident[:4] != b"\x7fELF" or self.e_ident[4] != 1 or self.e_ident[5] != 2:
            raise ValueError("expected big-endian ELF32")

    def _parse_sections(self):
        self.sections = []
        for i in range(self.e_shnum):
            off = self.e_shoff + i * self.e_shentsize
            self.sections.append(list(struct.unpack(SECT_HDR_FMT, self.data[off:off + self.e_shentsize])))
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

    def write_section_header(self, idx):
        off = self.e_shoff + idx * self.e_shentsize
        self.data[off:off + self.e_shentsize] = struct.pack(SECT_HDR_FMT, *self.sections[idx])

    def write_elf_header(self):
        self.data[:struct.calcsize(ELF_HDR_FMT)] = struct.pack(
            ELF_HDR_FMT,
            self.e_ident, self.e_type, self.e_machine, self.e_version,
            self.e_entry, self.e_phoff, self.e_shoff, self.e_flags,
            self.e_ehsize, self.e_phentsize, self.e_phnum,
            self.e_shentsize, self.e_shnum, self.e_shstrndx)

    def iter_symtab(self, symtab_idx):
        sec = self.sections[symtab_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        for i in range(size // ent):
            entry_off = off + i * ent
            yield i, list(struct.unpack(SYM_FMT, self.data[entry_off:entry_off + ent]))

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
        text_idx = self.find_section(".text")
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if fields[5] == text_idx and self.strtab_string(strtab_idx, fields[0]) == name:
                return sym_idx, fields, symtab_idx
        raise KeyError(f"symbol {name} not found")

    def text_bytes_for(self, name):
        _, fields, _ = self.find_symbol(name)
        text = self.sections[self.find_section(".text")]
        start = text[4] + fields[1]
        return bytes(self.data[start:start + fields[2]])

    def replace_text_range(self, old_start, old_size, payload):
        text_idx = self.find_section(".text")
        text = self.sections[text_idx]
        absolute = text[4] + old_start
        old_end = absolute + old_size
        self.data[absolute:old_end] = payload
        delta = len(payload) - old_size
        text[5] += delta
        if delta:
            for i, sec in enumerate(self.sections):
                if i != text_idx and sec[4] >= old_end:
                    sec[4] += delta
            if self.e_shoff >= old_end:
                self.e_shoff += delta
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()
        return delta

    def fix_symbols(self, func_name, old_start, old_size, new_size, delta):
        symtab_idx = self.find_section(".symtab")
        text_idx = self.find_section(".text")
        old_limit = old_start + old_size
        for sym_idx, fields in self.iter_symtab(symtab_idx):
            if fields[5] != text_idx:
                continue
            name = self.strtab_string(self.sections[symtab_idx][6], fields[0])
            if name == func_name:
                fields[2] = new_size
                self.write_sym(symtab_idx, sym_idx, fields)
            elif delta and fields[1] >= old_limit:
                fields[1] += delta
                self.write_sym(symtab_idx, sym_idx, fields)
            elif old_start < fields[1] < old_limit:
                raise RuntimeError(f"{name} lies inside replaced body")

    def fix_relocations(self, old_start, old_size, delta):
        if not self.has_section(".rel.text"):
            return
        rel_idx = self.find_section(".rel.text")
        sec = self.sections[rel_idx]
        off, size, ent = sec[4], sec[5], sec[9]
        old_limit = old_start + old_size
        kept = bytearray()
        dropped = 0
        for i in range(size // ent):
            entry_off = off + i * ent
            r_off, r_info = struct.unpack(REL_FMT, self.data[entry_off:entry_off + ent])
            if old_start <= r_off < old_limit:
                dropped += 1
                continue
            if delta and r_off >= old_limit:
                r_off += delta
            kept += struct.pack(REL_FMT, r_off, r_info)
        if dropped:
            self.data[off:off + len(kept)] = kept
            del self.data[off + len(kept):off + size]
            shrink = dropped * ent
            sec[5] -= shrink
            for i, other in enumerate(self.sections):
                if i != rel_idx and other[4] > off:
                    other[4] -= shrink
            if self.e_shoff > off:
                self.e_shoff -= shrink
        self.write_section_header(rel_idx)
        for i in range(self.e_shnum):
            self.write_section_header(i)
        self.write_elf_header()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dest")
    ap.add_argument("func")
    ap.add_argument("donor")
    args = ap.parse_args()

    dest_path = Path(args.dest)
    dest = Elf(dest_path.read_bytes())
    donor = Elf(Path(args.donor).read_bytes())
    payload = donor.text_bytes_for(args.func)
    _, fields, _ = dest.find_symbol(args.func)
    old_start, old_size = fields[1], fields[2]

    old_payload = dest.text_bytes_for(args.func)
    if old_payload == payload:
        print(f"replace-body-skip: {args.func} already matches donor")
        return

    delta = dest.replace_text_range(old_start, old_size, payload)
    dest.fix_symbols(args.func, old_start, old_size, len(payload), delta)
    dest.fix_relocations(old_start, old_size, delta)
    dest_path.write_bytes(dest.data)
    print(f"replace-body: {args.func} {old_size:#x}->{len(payload):#x} in {dest_path}")


if __name__ == "__main__":
    main()
