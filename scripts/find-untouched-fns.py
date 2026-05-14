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


def find_plain_include_asm() -> list[tuple[str, int, str]]:
    """Return [(function_name, size_bytes, source_file_path), ...] for
    plain `INCLUDE_ASM("...", FN);` lines that are NOT inside a
    #ifdef NON_MATCHING / #else / #endif wrap."""
    results = []
    plain_re = re.compile(
        r'^INCLUDE_ASM\("(?P<asm>[^"]+)",\s*(?P<fn>\w+)\);\s*$', re.MULTILINE
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
            for m in plain_re.finditer(text):
                fn = m.group("fn")
                asm_seg = m.group("asm")
                asm_path = f"{asm_seg}/{fn}.s"
                size = parse_asm_size(asm_path)
                if size is None or size < 0:
                    continue  # handwritten or unreadable
                results.append((fn, size, path))
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
    sized = [(fn, sz, p) for fn, sz, p in cands if args.min_size <= sz <= args.max_size]
    pcts = report_match_percents({fn for fn, _, _ in sized})
    rows = []
    for fn, sz, p in sized:
        mp = pcts.get(fn)
        if args.exclude_matched and mp == 100.0:
            continue
        rows.append((fn, sz, p, mp))
    rows.sort(key=lambda r: (r[1], r[0]))
    print(f"plain-INCLUDE_ASM in size band [{hex(args.min_size)}..{hex(args.max_size)}]: {len(rows)}")
    for fn, sz, p, mp in rows[: args.limit]:
        mp_str = f"{mp:.1f}%" if mp is not None else "—"
        rel = os.path.relpath(p)
        print(f"  {hex(sz):>6}  {mp_str:>6}  {fn}  ({rel})")
    if len(rows) > args.limit:
        print(f"  ... {len(rows) - args.limit} more")
    return 0


if __name__ == "__main__":
    sys.exit(main())
