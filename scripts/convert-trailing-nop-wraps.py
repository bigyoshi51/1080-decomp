#!/usr/bin/env python3
"""Convert NON_MATCHING wraps caused by trailing-nop padding into plain
decompositions, now that `<func>_pad.s` sidecars provide the alignment bytes
via `#pragma GLOBAL_ASM`.

Pattern detected:
    #ifdef NON_MATCHING
    /* ... mentions "trailing" or "alignment" ... */
    void func(...) { ... }
    #else
    INCLUDE_ASM(..., func);
    [#pragma GLOBAL_ASM(..._pad.s)]
    #endif

Replaced with:
    void func(...) { ... }
    #pragma GLOBAL_ASM(..._pad.s)

Skips functions in --skip list (those with non-trailing-nop diff reasons).

Usage:
    python3 scripts/convert-trailing-nop-wraps.py [--skip name1,name2,...]
"""
import os
import re
import sys
from pathlib import Path


def find_sidecars() -> dict[str, str]:
    """func_name -> pragma path."""
    sidecars = {}
    for root, dirs, files in os.walk('asm/nonmatchings'):
        for f in files:
            if f.endswith('_pad.s'):
                func_name = f[:-len('_pad.s')]
                sidecars[func_name] = os.path.join(root, f)
    return sidecars


def convert_one(c_file: Path, sidecars: dict[str, str], skip_set: set, dry_run: bool = False) -> int:
    content = c_file.read_text()
    new_content = content
    converted = 0

    # Pattern: #ifdef NM ... [comment] ... C body ... #else INCLUDE_ASM ... [#pragma GLOBAL_ASM] #endif
    pattern = re.compile(
        r'#ifdef NON_MATCHING\n'
        r'((?:/\*.*?\*/\s*\n)?)'           # optional block comment
        r'(.*?)\n'                          # C body (decl + function)
        r'#else\n'
        r'INCLUDE_ASM\([^,]+,\s*(\w+)\);\n'
        r'(?:#pragma GLOBAL_ASM\(\"([^\"]+)\"\)\n)?'
        r'#endif',
        re.DOTALL
    )

    def replacer(m):
        nonlocal converted
        comment, body, fname, pragma_path = m.groups()
        if fname in skip_set:
            return m.group(0)  # keep as-is
        if fname not in sidecars:
            return m.group(0)  # no sidecar, can't convert safely
        # Check comment mentions trailing/alignment
        comment_lower = (comment or "").lower()
        if 'trailing' not in comment_lower and 'alignment' not in comment_lower:
            return m.group(0)
        # Convert: keep body, append pragma
        sidecar_path = pragma_path or sidecars[fname]
        converted += 1
        return f"{body}\n#pragma GLOBAL_ASM(\"{sidecar_path}\")"

    new_content = pattern.sub(replacer, content)

    if not dry_run and converted > 0:
        c_file.write_text(new_content)

    return converted


def main():
    args = sys.argv[1:]
    dry_run = "--dry-run" in args
    args = [a for a in args if a != "--dry-run"]

    skip_set = set()
    if "--skip" in args:
        i = args.index("--skip")
        skip_set = set(args[i+1].split(","))
        args = args[:i] + args[i+2:]

    sidecars = find_sidecars()
    total = 0
    for c_file in Path('src').rglob('*.c'):
        n = convert_one(c_file, sidecars, skip_set, dry_run)
        if n > 0:
            print(f"  {c_file}: {n} conversions")
            total += n

    if dry_run:
        print(f"\n[DRY RUN] would convert {total} functions")
    else:
        print(f"\nConverted {total} functions")


if __name__ == "__main__":
    main()
