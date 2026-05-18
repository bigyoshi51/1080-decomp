#!/usr/bin/env python3
"""Patch instruction words and retarget existing .text relocations.

Spec syntax:
    func=off:word[,off:word...]@old:TYPE:new[,old:TYPE:new...]

Offsets are bytes relative to the function start. TYPE is HI16, LO16, or 26.
This is for cases where a C body emits the right relocation symbol but IDO
schedules the relocation-bearing instruction pair at the wrong fixed offsets.
"""
import argparse
import struct
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"
REL_FMT = ">II"

RELOC_TYPES = {
    "26": 4,
    "HI16": 5,
    "LO16": 6,
}


def _sections(data):
    header = struct.unpack(ELF_HDR_FMT, data[:struct.calcsize(ELF_HDR_FMT)])
    e_shoff, e_shentsize, e_shnum, e_shstrndx = header[6], header[11], header[12], header[13]
    sections = [
        struct.unpack(SECT_HDR_FMT, data[e_shoff + i * e_shentsize:e_shoff + (i + 1) * e_shentsize])
        for i in range(e_shnum)
    ]
    shstr = sections[e_shstrndx]

    def name_of(idx):
        name_off = sections[idx][0]
        end = data.index(b"\x00", shstr[4] + name_off)
        return bytes(data[shstr[4] + name_off:end]).decode("ascii")

    return header, sections, name_of


def _find_text_sym_and_rels(data, func_name):
    _header, sections, name_of = _sections(data)
    text_idx = next(i for i in range(len(sections)) if name_of(i) == ".text")
    rel_idx = next(i for i in range(len(sections)) if name_of(i) == ".rel.text")
    symtab_idx = next(i for i in range(len(sections)) if name_of(i) == ".symtab")
    strtab_idx = sections[symtab_idx][6]

    sym_off, sym_size, sym_ent = sections[symtab_idx][4], sections[symtab_idx][5], sections[symtab_idx][9]
    str_off = sections[strtab_idx][4]
    for i in range(sym_size // sym_ent):
        entry_off = sym_off + i * sym_ent
        sym = struct.unpack(SYM_FMT, data[entry_off:entry_off + sym_ent])
        name_off = sym[0]
        end = data.index(b"\x00", str_off + name_off)
        name = bytes(data[str_off + name_off:end]).decode("ascii")
        if name == func_name:
            return sections[text_idx][4], sym[1], sym[2], sections[rel_idx]
    raise KeyError(f"function {func_name} not found")


def _parse_spec(spec):
    func_name, rest = spec.split("=", 1)
    patch_part, reloc_part = rest.split("@", 1)
    patches = []
    for chunk in patch_part.split(","):
        off_s, word_s = chunk.split(":", 1)
        patches.append((int(off_s, 0), int(word_s, 0)))
    relocs = []
    for chunk in reloc_part.split(","):
        old_s, typ_s, new_s = chunk.split(":", 2)
        relocs.append((int(old_s, 0), RELOC_TYPES[typ_s], int(new_s, 0)))
    return func_name, patches, relocs


def patch_one(data, spec):
    func_name, patches, relocs = _parse_spec(spec)
    text_file_off, func_addr, func_size, rel_sec = _find_text_sym_and_rels(data, func_name)

    for insn_off, word in patches:
        if not (0 <= insn_off < func_size):
            raise ValueError(f"{func_name}: patch offset {insn_off:#x} outside size {func_size:#x}")
        if insn_off & 3:
            raise ValueError(f"{func_name}: patch offset {insn_off:#x} is not aligned")
        abs_off = text_file_off + func_addr + insn_off
        data[abs_off:abs_off + 4] = struct.pack(">I", word)

    rel_file_off, rel_size, rel_ent = rel_sec[4], rel_sec[5], rel_sec[9]
    retargeted = 0
    wanted = {(func_addr + old, typ): func_addr + new for old, typ, new in relocs}
    already_targeted = set()
    for i in range(rel_size // rel_ent):
        entry_off = rel_file_off + i * rel_ent
        r_offset, r_info = struct.unpack(REL_FMT, data[entry_off:entry_off + rel_ent])
        r_type = r_info & 0xFF
        key = (r_offset, r_type)
        if key in wanted:
            data[entry_off:entry_off + rel_ent] = struct.pack(REL_FMT, wanted[key], r_info)
            retargeted += 1
            continue
        for _old, typ, new in relocs:
            if r_type == typ and r_offset == func_addr + new:
                already_targeted.add((typ, func_addr + new))

    satisfied = retargeted + len(already_targeted)
    if satisfied != len(relocs):
        raise ValueError(f"{func_name}: retargeted {retargeted}/{len(relocs)} requested relocations")
    return func_name, len(patches), retargeted


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("o_file", type=Path)
    parser.add_argument("spec")
    args = parser.parse_args()

    data = bytearray(args.o_file.read_bytes())
    func_name, patch_count, reloc_count = patch_one(data, args.spec)
    args.o_file.write_bytes(bytes(data))
    print(
        f"patch-insn-relocs: {func_name} patched {patch_count} insn(s), "
        f"retargeted {reloc_count} reloc(s)"
    )


if __name__ == "__main__":
    main()
