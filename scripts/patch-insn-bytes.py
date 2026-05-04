#!/usr/bin/env python3
"""patch-insn-bytes.py — overwrite N specific instruction words inside a
function's body in a .o file, without changing the function's size or any
other symbol/reloc layout.

Use case: an unmatchable IDO codegen cap where the C body produces 99% of
the right bytes but 1-2 instructions differ in operand order or register
choice that no C-source variant can flip (e.g. FPU pipeline-driven add.s
operand order, scheduler register choices). The function's logic is
correct; we just patch the offending bytes post-cc to match the target
ROM exactly.

Mechanism: the .o size and section layout are UNCHANGED. We just rewrite
N words at known offsets within the function's .text bytes. No shifting,
no symbol-size growth, no reloc adjustment.

Spec syntax:
    func_name=offset:word[,offset:word...]

`offset` is in bytes, relative to the function's start (st_value). Hex
literals (0x...) accepted.

Example:
    build/src/foo/bar.c.o: INSN_PATCH := \\
        bar_func_dot4=0x34:0x46102200

    Replaces 4 bytes at (bar_func_dot4 + 0x34) with 0x46102200, big-endian.

Detect-and-skip: if the bytes at the offset already match the patch word,
no-op (idempotent across re-runs and INCLUDE_ASM build paths).
"""
import argparse
import struct
import sys
from pathlib import Path

ELF_HDR_FMT = ">16sHHIIIIIHHHHHH"
SECT_HDR_FMT = ">IIIIIIIIII"
SYM_FMT = ">IIIBBH"


def find_text_and_sym(data, func_name):
    h = struct.unpack(ELF_HDR_FMT, data[:struct.calcsize(ELF_HDR_FMT)])
    e_shoff, e_shentsize, e_shnum, e_shstrndx = h[6], h[11], h[12], h[13]

    sections = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        sections.append(struct.unpack(SECT_HDR_FMT, data[off:off + e_shentsize]))

    shstr = sections[e_shstrndx]

    def name_of(idx):
        name_off = sections[idx][0]
        end = data.index(b"\x00", shstr[4] + name_off)
        return bytes(data[shstr[4] + name_off:end]).decode("ascii")

    text_idx = next(i for i in range(e_shnum) if name_of(i) == ".text")
    symtab_idx = next(i for i in range(e_shnum) if name_of(i) == ".symtab")
    strtab_idx = sections[symtab_idx][6]

    sym_sec = sections[symtab_idx]
    sym_off, sym_size, sym_ent = sym_sec[4], sym_sec[5], sym_sec[9]
    str_off = sections[strtab_idx][4]

    for i in range(sym_size // sym_ent):
        e_off = sym_off + i * sym_ent
        f = struct.unpack(SYM_FMT, data[e_off:e_off + sym_ent])
        nm_off = f[0]
        end = data.index(b"\x00", str_off + nm_off)
        nm = bytes(data[str_off + nm_off:end]).decode("ascii")
        if nm == func_name:
            return sections[text_idx][4], f[1], f[2]
    return None, None, None


def patch_one(data, func_name, patches):
    text_file_off, func_addr, func_size = find_text_and_sym(data, func_name)
    if text_file_off is None:
        raise KeyError(f"function {func_name} not found in .symtab")

    skipped = 0
    applied = 0
    for insn_off, word in patches:
        if not (0 <= insn_off < func_size):
            raise ValueError(
                f"{func_name}: offset {insn_off:#x} outside function "
                f"(size {func_size:#x})")
        if insn_off & 3:
            raise ValueError(
                f"{func_name}: offset {insn_off:#x} not 4-byte aligned")
        abs_off = text_file_off + func_addr + insn_off
        existing = struct.unpack(">I", data[abs_off:abs_off + 4])[0]
        if existing == word:
            skipped += 1
            continue
        data[abs_off:abs_off + 4] = struct.pack(">I", word)
        applied += 1

    return applied, skipped


def parse_spec(spec):
    """Parse `func_name=off:word[,off:word]` into (func_name, [(off, word), ...])."""
    name, body = spec.split("=", 1)
    pairs = []
    for chunk in body.split(","):
        off_s, word_s = chunk.split(":", 1)
        pairs.append((int(off_s, 0), int(word_s, 0)))
    return name, pairs


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("o_file", type=Path)
    ap.add_argument("spec",
                    help="func_name=offset:word[,offset:word...]")
    args = ap.parse_args()

    raw = bytearray(args.o_file.read_bytes())
    func_name, patches = parse_spec(args.spec)
    applied, skipped = patch_one(raw, func_name, patches)
    args.o_file.write_bytes(bytes(raw))

    if applied:
        words = ", ".join(f"@{o:#x}={w:#010x}" for o, w in patches)
        print(f"patch-insn: {func_name} patched {applied}/{len(patches)} "
              f"insns ({words})", file=sys.stderr)
    if skipped == len(patches):
        print(f"patch-insn-skip: {func_name} all {skipped} bytes already "
              f"match (likely INCLUDE_ASM build path); no-op",
              file=sys.stderr)


if __name__ == "__main__":
    main()
