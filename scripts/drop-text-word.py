#!/usr/bin/env python3
"""Drop one asserted-zero word from the .text of a COPY of a .o, relocating
everything after it like a linker would.

Used by the game_uso Yay0 block recipe for the asm-processor 1-word-pad
defect: a 1-word GLOBAL_ASM pad sidecar emits 8 bytes (the C placeholder
minimum), one ZERO word more than the ROM. The recipe used to drop that word
from the extracted binary, which left every later `.text`-section addend
(static-callee jal fields) 4 bytes too high. Dropping it from the object
instead shifts later symbols and r_offsets by -4 and rebases the
`.text+X` in-place addends (scripts/elf_text_addends.py), so the code after
the pad keeps consistent self-references. No instruction is created or
chosen: the word must be zero and must not belong to any symbol's start.

Usage: drop-text-word.py <in.o> <out.o> <text_offset>
"""
import importlib.util
import struct
import sys
from pathlib import Path

from elf_text_addends import rebase_text_addends

_spec = importlib.util.spec_from_file_location(
    "rfb", Path(__file__).with_name("replace-function-body.py"))
rfb = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(rfb)


def main():
    src, dst, off = sys.argv[1], sys.argv[2], int(sys.argv[3], 0)
    elf = rfb.Elf(Path(src).read_bytes())
    text_idx = elf.find_section(".text")
    t = elf.sections[text_idx]
    word = bytes(elf.data[t[4] + off:t[4] + off + 4])
    if word != b"\x00" * 4:
        raise SystemExit(f"drop-text-word: word at .text+{off:#x} is {word.hex()}, not zero")

    symtab_idx = elf.find_section(".symtab")
    for sym_idx, f in elf.iter_symtab(symtab_idx):
        if f[5] == text_idx and (f[3] & 0xF) != 3 and f[1] == off and f[2]:
            name = elf.strtab_string(elf.sections[symtab_idx][6], f[0])
            raise SystemExit(f"drop-text-word: {name} starts at the dropped word")

    elf.replace_text_range(off, 4, b"")
    limit = off + 4
    for sym_idx, f in elf.iter_symtab(symtab_idx):
        if f[5] != text_idx:
            continue
        if (f[3] & 0xF) == 3:          # section symbol covers the section
            continue
        if f[1] >= limit:
            f[1] -= 4
            elf.write_sym(symtab_idx, sym_idx, f)
        elif f[1] <= off < f[1] + f[2]:  # a sized symbol spanning the word
            f[2] -= 4
            elf.write_sym(symtab_idx, sym_idx, f)
    # r_offsets: no reloc may sit on the zero word; later ones move by -4
    elf.fix_relocations(off, 4, -4)
    n = rebase_text_addends(elf.data, limit, -4, forbid_inside=(off, limit))
    Path(dst).write_bytes(elf.data)
    print(f"drop-text-word: dropped .text+{off:#x} ({n} .text addend(s) rebased)")


if __name__ == "__main__":
    main()
