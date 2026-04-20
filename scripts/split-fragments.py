#!/usr/bin/env python3
"""Split mis-merged USO function .s files at mid-function `jr $ra` boundaries.

Splat / generate-uso-asm.py only detects `addiu $sp, -N` prologues when picking
function boundaries. Leaf functions with no stack frame (e.g. small field-
setters) get merged into the end of the preceding function. This is the mirror
problem of `merge-fragments`: one .s file that should be two.

Detection: after a `jr $ra` + delay slot, any non-nop instruction inside the
declared size implies a hidden function boundary. If the post-boundary code
reads caller-save argument registers ($a0-$a3) without initialising them, it
must be a standalone function — caller-save are garbage across calls.

Usage:
    # Dry-run: list all candidates across USO segments + game_libs.
    scripts/split-fragments.py --list

    # Split a specific function at its first mid-jr boundary:
    scripts/split-fragments.py game_uso_func_00001D30

    # Split every high-confidence candidate (leaf-shaped tail, ≥3 insns):
    scripts/split-fragments.py --all

Effect:
 1. Truncate the `.s` file: shorten `nonmatching` size, drop trailing insns.
 2. Create a new `.s` file for the split-off function.
 3. Update the segment's `.c` file: insert INCLUDE_ASM for the new function
    immediately after the original one.
"""
import argparse
import glob
import re
import sys
from pathlib import Path


INSN_LINE_RE = re.compile(
    r"/\*\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+\*/"
)
HEADER_RE = re.compile(r"nonmatching\s+(\S+),\s+0x([0-9A-Fa-f]+)")


def parse_asm_file(path):
    """Return (name, size, [(rom, vram, word, line), ...])."""
    with open(path) as f:
        content = f.read()
    m = HEADER_RE.search(content)
    if not m:
        return None
    name, size = m.group(1), int(m.group(2), 16)
    insns = []
    for line in content.split("\n"):
        m2 = INSN_LINE_RE.search(line)
        if m2:
            rom = int(m2.group(1), 16)
            vram = int(m2.group(2), 16)
            word = int(m2.group(3), 16)
            insns.append((rom, vram, word, line))
    return name, size, insns


def find_split_point(insns, size):
    """Return index of first instruction belonging to the next function, or None.

    The boundary is: `jr $ra` (0x03E00008) at position i, delay slot at i+1,
    then non-nop instruction at i+2 still inside declared size. Trailing
    all-nops are padding (don't split).
    """
    if len(insns) < 3:
        return None
    for i in range(len(insns) - 2):
        rom, vram, word, _ = insns[i]
        if word != 0x03E00008:
            continue
        tail = insns[i + 2 :]
        if not tail:
            continue
        if all(w == 0 for _, _, w, _ in tail):
            continue  # pure alignment nops
        return i + 2
    return None


def is_high_confidence(tail):
    """High confidence if tail is leaf-shaped: ≥3 insns, no jal, ends in jr ra."""
    if len(tail) < 3:
        return False
    has_jal = any((w >> 26) == 0x03 for _, _, w, _ in tail)
    if has_jal:
        return False
    # Need a jr ra somewhere in the tail (complete function)
    has_jr = any(w == 0x03E00008 for _, _, w, _ in tail)
    return has_jr


def rewrite_asm_file(path, insns, split_idx, new_size):
    """Truncate the file at split_idx; return the original header line and
    the dropped lines for the new function."""
    name, _, _ = parse_asm_file(path)
    kept = insns[:split_idx]
    dropped = insns[split_idx:]

    # Build new .s content
    out_lines = [
        f"nonmatching {name}, 0x{new_size:X}",
        "",
        f"glabel {name}",
    ]
    for _, _, _, line in kept:
        out_lines.append(line)
    out_lines.append(f"endlabel {name}")
    Path(path).write_text("\n".join(out_lines) + "\n")
    return dropped


def write_split_file(path_dir, seg, new_addr, dropped):
    new_name = f"{seg}_func_{new_addr:08X}"
    new_size = len(dropped) * 4
    out_lines = [
        f"nonmatching {new_name}, 0x{new_size:X}",
        "",
        f"glabel {new_name}",
    ]
    for _, _, _, line in dropped:
        out_lines.append(line)
    out_lines.append(f"endlabel {new_name}")
    new_path = path_dir / f"{new_name}.s"
    new_path.write_text("\n".join(out_lines) + "\n")
    return new_name


def update_c_file(seg_c_path, seg, original_name, new_name):
    """Insert an INCLUDE_ASM for new_name right after the one for original_name."""
    txt = seg_c_path.read_text()
    # Pattern for original INCLUDE_ASM (may be inside #ifdef wrap, but locate the
    # bare INCLUDE_ASM reference to the function we split).
    include_re = re.compile(
        r'(INCLUDE_ASM\(["\'][^"\']+["\'],\s*' + re.escape(original_name) + r'\);)'
    )
    match = include_re.search(txt)
    if not match:
        # Might already have a NON_MATCHING wrap — still find the INCLUDE_ASM.
        # Or the function is decompiled (no INCLUDE_ASM). In that case we just
        # append at the end of the file.
        print(
            f"  warn: INCLUDE_ASM for {original_name} not found in {seg_c_path}; appending",
            file=sys.stderr,
        )
        new_line = (
            f'\nINCLUDE_ASM("asm/nonmatchings/{seg}/{seg}", {new_name});\n'
        )
        seg_c_path.write_text(txt + new_line)
        return
    new_include = (
        match.group(1)
        + f'\n\nINCLUDE_ASM("asm/nonmatchings/{seg}/{seg}", {new_name});'
    )
    seg_c_path.write_text(include_re.sub(new_include, txt, count=1))


def split_one(asm_path, high_confidence_only=True):
    """Return (ok, message)."""
    parsed = parse_asm_file(asm_path)
    if parsed is None:
        return False, "header-parse failed"
    name, size, insns = parsed
    split_idx = find_split_point(insns, size)
    if split_idx is None:
        return False, "no mid-jr split point"
    tail = insns[split_idx:]
    if high_confidence_only and not is_high_confidence(tail):
        return False, f"low confidence ({len(tail)} insns; has_jal)"

    new_addr = tail[0][1]
    seg = Path(asm_path).parts[-3]  # asm/nonmatchings/<seg>/<seg>/file.s
    new_first_vram = insns[0][1]
    new_size_of_orig = new_addr - new_first_vram
    dropped = rewrite_asm_file(asm_path, insns, split_idx, new_size_of_orig)

    new_name = write_split_file(Path(asm_path).parent, seg, new_addr, dropped)

    seg_c = Path(f"src/{seg}/{seg}.c")
    if seg_c.exists():
        update_c_file(seg_c, seg, name, new_name)
    return True, f"split off {new_name} ({len(dropped)} insns)"


def list_candidates():
    glob_pattern = "asm/nonmatchings/*/*/*.s"
    rows = []
    for p in sorted(glob.glob(glob_pattern)):
        parsed = parse_asm_file(p)
        if parsed is None:
            continue
        name, size, insns = parsed
        idx = find_split_point(insns, size)
        if idx is None:
            continue
        tail = insns[idx:]
        conf = "HIGH" if is_high_confidence(tail) else "LOW "
        rows.append((conf, name, insns[idx][1], len(tail), p))
    for r in rows:
        print(f"  {r[0]}  {r[1]:40s}  next@0x{r[2]:X}  {r[3]:3d} insns  [{r[4]}]")
    print(f"TOTAL: {len(rows)} candidates")


def find_asm_path(func_name):
    matches = glob.glob(f"asm/nonmatchings/*/*/{func_name}.s")
    if not matches:
        return None
    if len(matches) > 1:
        raise SystemExit(f"ambiguous: {matches}")
    return matches[0]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("function", nargs="?", help="function name to split")
    ap.add_argument("--list", action="store_true", help="list candidates only")
    ap.add_argument("--all", action="store_true", help="split every high-confidence candidate")
    args = ap.parse_args()

    if args.list:
        list_candidates()
        return

    if args.all:
        n_ok = n_skip = 0
        for p in sorted(glob.glob("asm/nonmatchings/*/*/*.s")):
            parsed = parse_asm_file(p)
            if parsed is None:
                continue
            _, _, insns = parsed
            idx = find_split_point(insns, 0)
            if idx is None:
                continue
            if not is_high_confidence(insns[idx:]):
                n_skip += 1
                continue
            ok, msg = split_one(p, high_confidence_only=True)
            if ok:
                n_ok += 1
                print(f"  ok: {Path(p).stem} — {msg}")
            else:
                n_skip += 1
        print(f"split {n_ok}; skipped {n_skip} low-confidence")
        return

    if not args.function:
        ap.print_help()
        return

    asm_path = find_asm_path(args.function)
    if not asm_path:
        raise SystemExit(f"not found: {args.function}")
    ok, msg = split_one(asm_path, high_confidence_only=False)
    print(f"{args.function}: {msg}")


if __name__ == "__main__":
    main()
