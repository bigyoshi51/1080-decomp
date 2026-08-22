#!/usr/bin/env python3
"""Rename symbols in a MIPS ELF .o by strtab repointing (metadata only).

Why not `objcopy --redefine-sym`: objcopy rewrites the whole symbol
table and drops/renames the LOCAL SECTION symbols (".data" etc.) that
replace-function-body.py's donor-reloc import keys on for its
"<func>_<section>" rename — the imported relocs then degrade to *ABS*
and the linker leaves the fields unresolved (caught 2026-08-22 on the
xlitob.c donor: the four ldigs/udigs %hi/%lo words shipped unbaked and
broke ROM cmp). This script only appends the new name to .strtab and
repoints st_name — section content and all other symbols untouched.

Usage: rename-elf-symbol.py <obj> <old>=<new> [...]
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
rfb = __import__("replace-function-body")


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    path = Path(sys.argv[1])
    elf = rfb.Elf(path.read_bytes())
    symtab_idx = elf.find_section(".symtab")
    strtab_idx = elf.sections[symtab_idx][6]
    symtab = elf.sections[symtab_idx]
    ent = symtab[9]
    for spec in sys.argv[2:]:
        old, _, new = spec.partition("=")
        hits = 0
        for sym_idx, fields in list(elf.iter_symtab(symtab_idx)):
            if elf.strtab_string(strtab_idx, fields[0]) == old:
                name_off = elf._strtab_add(strtab_idx, new)
                # _strtab_add may have shifted .symtab; recompute offset.
                abs_off = elf.sections[symtab_idx][4] + sym_idx * ent
                fields = list(fields)
                fields[0] = name_off
                struct.pack_into(rfb.SYM_FMT, elf.data, abs_off, *fields)
                hits += 1
        if hits == 0:
            raise SystemExit(f"rename-elf-symbol: {old} not found in {path}")
        print(f"rename-elf-symbol: {old} -> {new} ({hits}) in {path}")
    path.write_bytes(bytes(elf.data))


if __name__ == "__main__":
    main()
