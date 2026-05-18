#!/usr/bin/env python3
"""Clip an ELF .text section while preserving section alignment.

Usage:
    clip-elf-text-keep-align.py <elf_file> <text_size> [symbol=size ...]

This is for split objects where the linked layout needs the original trailing
alignment padding, but an oversized C-emitted symbol must still be tightened for
objdiff. Relocations at or after the clipped .text end are dropped.
"""
import struct
import sys
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
REL_FMT = ">II"


def _name(data, str_off, name_off):
    end = data.index(b"\x00", str_off + name_off)
    return bytes(data[str_off + name_off:end]).decode("ascii")


def main():
    if len(sys.argv) < 3:
        raise SystemExit(__doc__)

    path = Path(sys.argv[1])
    target_size = int(sys.argv[2], 0)
    forced_sizes = {}
    for spec in sys.argv[3:]:
        name, size_s = spec.split("=", 1)
        forced_sizes[name] = int(size_s, 0)

    data = bytearray(path.read_bytes())
    if data[:4] != b"\x7fELF" or data[5] != 2:
        raise SystemExit(f"{path}: expected big-endian ELF")

    header = struct.unpack(ELF_HDR_FMT, data[:struct.calcsize(ELF_HDR_FMT)])
    e_shoff, e_shentsize, e_shnum, e_shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        list(struct.unpack(SECT_HDR_FMT, data[e_shoff + i * e_shentsize:e_shoff + (i + 1) * e_shentsize]))
        for i in range(e_shnum)
    ]
    shstr = sections[e_shstrndx]

    def section_name(idx):
        return _name(data, shstr[4], sections[idx][0])

    text_idx = next(i for i in range(e_shnum) if section_name(i) == ".text")
    symtab_idx = next(i for i in range(e_shnum) if sections[i][1] == 2)
    strtab_idx = sections[symtab_idx][6]

    text = sections[text_idx]
    if text[5] > target_size:
        old = text[5]
        text[5] = target_size
        data[e_shoff + text_idx * e_shentsize:e_shoff + (text_idx + 1) * e_shentsize] = struct.pack(SECT_HDR_FMT, *text)
        print(f"{path}: clipped .text from 0x{old:x} to 0x{target_size:x}")
    elif text[5] < target_size:
        raise SystemExit(f"{path}: .text 0x{text[5]:x} smaller than requested 0x{target_size:x}")

    symtab = sections[symtab_idx]
    sym_off, sym_size, sym_ent = symtab[4], symtab[5], symtab[9]
    str_off = sections[strtab_idx][4]
    for i in range(sym_size // sym_ent):
        entry_off = sym_off + i * sym_ent
        fields = list(struct.unpack(SYM_FMT, data[entry_off:entry_off + sym_ent]))
        st_name, st_value, st_size, _info, _other, st_shndx = fields
        if st_shndx != text_idx:
            continue
        name = _name(data, str_off, st_name) if st_name else ""
        new_size = forced_sizes.get(name)
        if new_size is None and st_value + st_size > target_size:
            new_size = max(0, target_size - st_value)
        if new_size is not None and new_size != st_size:
            fields[2] = new_size
            data[entry_off:entry_off + sym_ent] = struct.pack(SYM_FMT, *fields)
            label = name or "<no-name>"
            print(f"{path}: resized symbol {label} @ 0x{st_value:x} from 0x{st_size:x} to 0x{new_size:x}")

    for idx, section in enumerate(sections):
        sh_type, sh_info = section[1], section[7]
        if sh_type not in (4, 9) or sh_info != text_idx:
            continue
        rel_off, rel_size, rel_ent = section[4], section[5], section[9]
        kept = bytearray()
        dropped = 0
        for off in range(rel_off, rel_off + rel_size, rel_ent):
            r_offset, _r_info = struct.unpack(REL_FMT, data[off:off + rel_ent])
            if r_offset < target_size:
                kept.extend(data[off:off + rel_ent])
            else:
                dropped += 1
        if dropped:
            data[rel_off:rel_off + len(kept)] = kept
            data[rel_off + len(kept):rel_off + rel_size] = b"\x00" * (rel_size - len(kept))
            section[5] = len(kept)
            data[e_shoff + idx * e_shentsize:e_shoff + (idx + 1) * e_shentsize] = struct.pack(SECT_HDR_FMT, *section)
            print(f"{path}: dropped {dropped} .text reloc(s) at/after 0x{target_size:x}")

    path.write_bytes(bytes(data))


if __name__ == "__main__":
    main()
