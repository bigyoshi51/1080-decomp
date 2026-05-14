#!/usr/bin/env python3
"""
Find functions that are still plain INCLUDE_ASM (no `#ifdef NON_MATCHING`
wrap, no C body, no decompilation attempt), sorted by size ascending.

Use this BEFORE the survey-of-NM-wraps tool — these are the truly fresh
candidates without any prior C-decode work. Filters out:

- Handwritten asm functions (skip per /decompile workflow)
- Functions in #ifdef NON_MATCHING wraps (covered by find-nm-wraps-without-episodes.py)
- Functions whose asm size is below a configurable threshold

Run from a project worktree.
"""
import os
import re
import sys
import json
import subprocess
from pathlib import Path


def parse_asm_size(asm_path: str) -> int | None:
    """Read the `nonmatching <fn>, 0xN` header to get function size in bytes."""
    try:
        with open(asm_path) as fp:
            first = fp.readline().strip()
            # Some files have a blank/handwritten-comment first line
            if not first:
                first = fp.readline().strip()
            if "Handwritten" in first:
                return -1  # sentinel
            second = fp.readline().strip()
            for line in [first, second]:
                m = re.search(r"nonmatching\s+\w+,\s*(0x[0-9A-Fa-f]+)", line)
                if m:
                    return int(m.group(1), 16)
    except (OSError, UnicodeDecodeError):
        return None
    return None


def asm_shape_flags(asm_path: str) -> str:
    """Return single-char flag:
       'F' = full standalone (has addiu sp prologue + jr ra)
       'X' = fragment-suspect (missing prologue or jr ra)
       '?' = couldn't determine"""
    try:
        content = open(asm_path).read()
    except (OSError, UnicodeDecodeError):
        return "?"
    # The .s file may use either `.word 0xWORDVAL` (fully .word) or
    # mnemonic form. Look at instruction-bearing lines.
    insns = [
        l for l in content.splitlines()
        if "/* " in l and ("*/" in l) and any(c in l for c in ("\t", "  "))
    ]
    # Filter out the glabel header line and endlabel
    insn_lines = [l for l in insns if "glabel" not in l and "endlabel" not in l]
    if not insn_lines:
        return "?"
    first = insn_lines[0]
    # Two patterns: ".word 0x27BDFFE8" or "addiu $sp, $sp, -N"
    has_prologue = (
        "0x27BD" in first or "addiu" in first.lower() and "sp" in first.lower() and "-" in first
    )
    # jr ra ends with .word 0x03E00008, or mnemonic "jr   $ra"
    has_jr_ra = "0x03E00008" in content or "jr         $ra" in content or "jr     $ra" in content or "jr\t$ra" in content
    if has_prologue and has_jr_ra:
        return "F"
    return "X"


def find_plain_include_asm() -> list[tuple[str, int, str, str]]:
    """Return [(function_name, size_bytes, source_file_path, shape), ...]
    for plain `INCLUDE_ASM("...", FN);` lines that are NOT inside a
    #ifdef NON_MATCHING / #else / #endif wrap and NOT shadowed by an
    NM-wrap elsewhere in the file."""
    results = []
    plain_re = re.compile(
        r'^INCLUDE_ASM\("(?P<asm>[^"]+)",\s*(?P<fn>\w+)\);\s*$', re.MULTILINE
    )
    # NM-wrap pattern: #ifdef NON_MATCHING ... #else ... INCLUDE_ASM(...,FN); ... #endif
    # Allow other directives (e.g. #pragma GLOBAL_ASM) between INCLUDE_ASM and #endif.
    nm_wrap_re = re.compile(
        r'#ifdef NON_MATCHING.*?#else.*?INCLUDE_ASM\("[^"]+",\s*(\w+)\);.*?#endif',
        re.DOTALL,
    )
    for root, _, files in os.walk("src"):
        for f in files:
            if not f.endswith(".c"):
                continue
            path = os.path.join(root, f)
            try:
                text = open(path).read()
            except (OSError, UnicodeDecodeError):
                continue
            wrapped = {m.group(1) for m in nm_wrap_re.finditer(text)}
            for m in plain_re.finditer(text):
                fn = m.group("fn")
                if fn in wrapped:
                    continue  # this INCLUDE_ASM is inside an NM-wrap
                asm_seg = m.group("asm")
                asm_path = f"{asm_seg}/{fn}.s"
                size = parse_asm_size(asm_path)
                if size is None or size < 0:
                    continue
                shape = asm_shape_flags(asm_path)
                results.append((fn, size, path, shape))
    return results


def report_match_percents(names: set[str]) -> dict[str, float | None]:
    if not os.path.exists("report.json"):
        return {}
    try:
        d = json.load(open("report.json"))
    except json.JSONDecodeError:
        return {}
    out = {}
    for unit in d.get("units", []):
        for fn in unit.get("functions", []):
            n = fn.get("name")
            if n in names:
                out[n] = fn.get("fuzzy_match_percent")
    return out


def main() -> int:
    import argparse
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument(
        "--min-size", type=lambda x: int(x, 0), default=0x10,
        help="exclude functions smaller than this (default 0x10)",
    )
    ap.add_argument(
        "--max-size", type=lambda x: int(x, 0), default=0x80,
        help="exclude functions larger than this (default 0x80)",
    )
    ap.add_argument("--limit", type=int, default=50, help="max rows to print")
    ap.add_argument(
        "--exclude-matched", action="store_true",
        help="exclude functions already at 100% in report.json (rare for plain INCLUDE_ASM)",
    )
    args = ap.parse_args()

    if not Path("src").is_dir():
        print("error: run from a project worktree", file=sys.stderr)
        return 1
    cands = find_plain_include_asm()
    sized = [(fn, sz, p, sh) for fn, sz, p, sh in cands if args.min_size <= sz <= args.max_size]
    pcts = report_match_percents({fn for fn, _, _, _ in sized})
    rows = []
    for fn, sz, p, sh in sized:
        mp = pcts.get(fn)
        if args.exclude_matched and mp == 100.0:
            continue
        rows.append((fn, sz, p, mp, sh))
    rows.sort(key=lambda r: (r[1], r[0]))
    n_F = sum(1 for r in rows if r[4] == "F")
    n_X = sum(1 for r in rows if r[4] == "X")
    print(f"plain-INCLUDE_ASM in [{hex(args.min_size)}..{hex(args.max_size)}]: {len(rows)} (F={n_F} standalone, X={n_X} fragment-suspect)")
    for fn, sz, p, mp, sh in rows[: args.limit]:
        mp_str = f"{mp:.1f}%" if mp is not None else "—"
        rel = os.path.relpath(p)
        print(f"  {sh}  {hex(sz):>6}  {mp_str:>6}  {fn}  ({rel})")
    if len(rows) > args.limit:
        print(f"  ... {len(rows) - args.limit} more")
    return 0


if __name__ == "__main__":
    sys.exit(main())
