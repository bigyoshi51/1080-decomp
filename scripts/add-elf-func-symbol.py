#!/usr/bin/env python3
"""Append named GLOBAL FUNC .text symbols to a MIPS ELF .o.

Why: IDO -O3 merges static functions under whole-TU interprocedural
register allocation and emits NO symtab entries for them (only the
global entry points survive). REPLACE_FUNC_BODY (replace-function-body.py)
keys on a named donor symbol with a correct st_size, so a donor built at
-O3 needs its function symbols re-introduced post-compile. Adding symbols
never touches section content — the compiled bytes are untouched (this is
symbol metadata, not instruction patching).

Usage: add-elf-func-symbol.py <obj> <name>=<offset>:<size> [...]
Offsets/sizes hex or decimal. Idempotent: an existing symbol with the
same name/offset/size is left alone; a same-name symbol with different
placement is an error.

First user: game_libs_ido53_73904.c (xldtob.c at IDO 5.3 -O3 — _Genld
= gl_func_00073904 with its s-reg custom linkage, _Ldtob =
gl_func_00073E74).
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
rfb = __import__("replace-function-body")
Elf = rfb.Elf
SYM_FMT = rfb.SYM_FMT


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    path = Path(sys.argv[1])
    elf = Elf(path.read_bytes())
    symtab_idx = elf.find_section(".symtab")
    strtab_idx = elf.sections[symtab_idx][6]
    text_idx = elf.find_section(".text")
    changed = False
    for spec in sys.argv[2:]:
        name, _, rest = spec.partition("=")
        off_s, _, size_s = rest.partition(":")
        off, size = int(off_s, 0), int(size_s, 0)
        existing = None
        for _, fields in elf.iter_symtab(symtab_idx):
            if elf.strtab_string(strtab_idx, fields[0]) == name:
                existing = fields
                break
        if existing is not None:
            if existing[1] == off and existing[2] == size and existing[5] == text_idx:
                print(f"add-func-symbol: {name} already present in {path}")
                continue
            raise SystemExit(
                f"add-func-symbol: {name} exists in {path} with different "
                f"placement ({existing[1]:#x}:{existing[2]:#x})")
        text_size = elf.sections[text_idx][5]
        if off + size > text_size:
            raise SystemExit(
                f"add-func-symbol: {name} {off:#x}:{size:#x} exceeds .text "
                f"size {text_size:#x} in {path}")
        name_off = elf._strtab_add(strtab_idx, name)
        symtab = elf.sections[symtab_idx]
        ent = symtab[9]
        new_abs = elf._grow_section(symtab_idx, ent)
        # STB_GLOBAL=1, STT_FUNC=2 -> st_info=0x12; st_shndx=.text
        struct.pack_into(SYM_FMT, elf.data, new_abs, name_off, off, size, 0x12, 0, text_idx)
        print(f"add-func-symbol: {name}={off:#x}:{size:#x} -> {path}")
        changed = True
    if changed:
        path.write_bytes(bytes(elf.data))


if __name__ == "__main__":
    main()
