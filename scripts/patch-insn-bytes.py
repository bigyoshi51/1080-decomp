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

Mechanism: the .o size and section layout are UNCHANGED. We rewrite N
words at known offsets within the function's .text bytes. We also strip
orphan R_MIPS_26 relocations when a patch replaces a `jal 0` placeholder
with a non-jal instruction — otherwise the linker would re-apply the
relocation to whatever non-jal opcode is now there and corrupt it (which
shows up as `relocation truncated to fit: R_MIPS_26 against ...` at link
time, since the addend bits collide with the new instruction's opcode/
immediate fields).

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
REL_FMT = ">II"  # Elf32_Rel: r_offset, r_info

R_MIPS_26 = 4
R_MIPS_HI16 = 5
R_MIPS_LO16 = 6

# MIPS opcodes that participate in HI16/LO16 paired relocations:
# - lui (0x0F): receives R_MIPS_HI16
# - addiu (0x09), lw (0x23), sw (0x2B), lhu (0x25), lh (0x21), lb (0x20),
#   lbu (0x24), sh (0x29), sb (0x28), lwc1 (0x31), swc1 (0x39),
#   ldc1 (0x35), sdc1 (0x3D): receive R_MIPS_LO16 (immediate-form)
_LO16_OPCODES = frozenset(
    {0x09, 0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B, 0x31, 0x35, 0x39, 0x3D}
)


def _opcode(word):
    return (word >> 26) & 0x3F


# A MIPS jal/j has opcode 0b00001x (top 6 bits = 0x02 or 0x03).
def _is_jump_opcode(word):
    op = _opcode(word)
    return op == 0x02 or op == 0x03


def _is_lui_opcode(word):
    return _opcode(word) == 0x0F


def _is_lo16_opcode(word):
    return _opcode(word) in _LO16_OPCODES


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


def find_rel_text(data):
    """Return (file_offset, size, entry_size) for .rel.text, or None."""
    h = struct.unpack(ELF_HDR_FMT, data[:struct.calcsize(ELF_HDR_FMT)])
    e_shoff, e_shentsize, e_shnum, e_shstrndx = h[6], h[11], h[12], h[13]

    sections = []
    for i in range(e_shnum):
        off = e_shoff + i * e_shentsize
        sections.append(struct.unpack(SECT_HDR_FMT, data[off:off + e_shentsize]))

    shstr = sections[e_shstrndx]
    for i, s in enumerate(sections):
        name_off = s[0]
        end = data.index(b"\x00", shstr[4] + name_off)
        nm = bytes(data[shstr[4] + name_off:end]).decode("ascii")
        if nm == ".rel.text":
            return s[4], s[5], s[9]
    return None


def strip_orphan_jal_relocs(data, func_addr, orphan_offsets):
    """Zero out R_MIPS_26 relocs at any of `orphan_offsets` (relative to .text).

    `orphan_offsets` is a set of absolute .text offsets where INSN_PATCH
    replaced a `jal 0` placeholder with a non-jump instruction. Any reloc
    whose r_offset matches must be neutralized so the linker doesn't apply
    a 26-bit jump fixup to the new addiu/or/etc opcode.

    We zero the entry in-place (r_offset=0, r_info=0 → R_MIPS_NONE for
    sym 0) rather than removing it, to avoid resizing/reordering the
    relocation table. R_MIPS_NONE is a no-op at link time.
    """
    rel = find_rel_text(data)
    if rel is None:
        return 0
    rel_off, rel_size, rel_ent = rel
    stripped = 0
    for i in range(rel_size // rel_ent):
        e_off = rel_off + i * rel_ent
        r_offset, r_info = struct.unpack(REL_FMT, data[e_off:e_off + rel_ent])
        r_type = r_info & 0xFF
        # Reloc r_offset is relative to .text section start (r_offset is the
        # offset within the section being relocated). Compare directly.
        if r_type == R_MIPS_26 and r_offset in orphan_offsets:
            data[e_off:e_off + rel_ent] = struct.pack(REL_FMT, 0, 0)
            stripped += 1
    return stripped


def strip_orphan_hilo_relocs(data, hi_offsets, lo_offsets):
    """Zero out R_MIPS_HI16 / R_MIPS_LO16 relocs at orphan offsets.

    Counterpart to strip_orphan_jal_relocs for HI16/LO16 paired relocs.
    Triggers when INSN_PATCH replaces a `lui rD, %hi(SYM)` with a non-lui
    instruction (HI16 reloc would be re-applied to bits 15..0 of the new
    word, which for non-lui opcodes are the immediate field — wrong) or
    replaces an `addiu/lw/sw rD,rS,%lo(SYM)` with an opcode outside the
    LO16-bearing set (LO16 reloc would corrupt bits 15..0 of the new
    word).

    Safe under USO context where every cross-USO symbol resolves to 0 at
    link time and the post-patch word already encodes the correct
    immediate (since `%hi(0+addend)` and `%lo(0+addend)` both resolve to
    addend's bits, which the patch caller has baked into the instruction).
    """
    if not hi_offsets and not lo_offsets:
        return 0
    rel = find_rel_text(data)
    if rel is None:
        return 0
    rel_off, rel_size, rel_ent = rel
    stripped = 0
    for i in range(rel_size // rel_ent):
        e_off = rel_off + i * rel_ent
        r_offset, r_info = struct.unpack(REL_FMT, data[e_off:e_off + rel_ent])
        r_type = r_info & 0xFF
        if r_type == R_MIPS_HI16 and r_offset in hi_offsets:
            data[e_off:e_off + rel_ent] = struct.pack(REL_FMT, 0, 0)
            stripped += 1
        elif r_type == R_MIPS_LO16 and r_offset in lo_offsets:
            data[e_off:e_off + rel_ent] = struct.pack(REL_FMT, 0, 0)
            stripped += 1
    return stripped


def patch_one(data, func_name, patches):
    text_file_off, func_addr, func_size = find_text_and_sym(data, func_name)
    if text_file_off is None:
        raise KeyError(f"function {func_name} not found in .symtab")

    skipped = 0
    applied = 0
    orphan_jal_offsets = set()
    orphan_hi_offsets = set()
    orphan_lo_offsets = set()
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
        rel_offset = func_addr + insn_off
        # If we're overwriting a jal/j with a non-jump opcode, remember the
        # .text-relative offset so we can neutralize the (now-orphan)
        # R_MIPS_26 relocation that was emitted for the original jal.
        if _is_jump_opcode(existing) and not _is_jump_opcode(word):
            orphan_jal_offsets.add(rel_offset)
        # Same for HI16/LO16: if the existing word's opcode bears that
        # reloc but the new word's doesn't, the reloc is now an orphan
        # that would corrupt the new instruction's immediate field.
        if _is_lui_opcode(existing) and not _is_lui_opcode(word):
            orphan_hi_offsets.add(rel_offset)
        if _is_lo16_opcode(existing) and not _is_lo16_opcode(word):
            orphan_lo_offsets.add(rel_offset)
        data[abs_off:abs_off + 4] = struct.pack(">I", word)
        applied += 1

    jal_stripped = 0
    hilo_stripped = 0
    if orphan_jal_offsets:
        jal_stripped = strip_orphan_jal_relocs(
            data, func_addr, orphan_jal_offsets)
    if orphan_hi_offsets or orphan_lo_offsets:
        hilo_stripped = strip_orphan_hilo_relocs(
            data, orphan_hi_offsets, orphan_lo_offsets)

    return applied, skipped, jal_stripped, hilo_stripped


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
    applied, skipped, jal_stripped, hilo_stripped = patch_one(
        raw, func_name, patches)
    args.o_file.write_bytes(bytes(raw))

    if applied:
        words = ", ".join(f"@{o:#x}={w:#010x}" for o, w in patches)
        print(f"patch-insn: {func_name} patched {applied}/{len(patches)} "
              f"insns ({words})", file=sys.stderr)
    if jal_stripped:
        print(f"patch-insn: {func_name} stripped {jal_stripped} orphan "
              f"R_MIPS_26 reloc(s) at jal-→non-jal offsets",
              file=sys.stderr)
    if hilo_stripped:
        print(f"patch-insn: {func_name} stripped {hilo_stripped} orphan "
              f"R_MIPS_HI16/LO16 reloc(s) at lui/addiu-→other-opcode offsets",
              file=sys.stderr)
    if skipped == len(patches):
        print(f"patch-insn-skip: {func_name} all {skipped} bytes already "
              f"match (likely INCLUDE_ASM build path); no-op",
              file=sys.stderr)


if __name__ == "__main__":
    main()
