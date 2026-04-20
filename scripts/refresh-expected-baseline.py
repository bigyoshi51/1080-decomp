#!/usr/bin/env python3
"""Regenerate expected/*.o from a pure-INCLUDE_ASM build.

Why: objdiff's match % compares `build/*.o` against `expected/*.o`. If
`make expected` runs while src/*.c has decompiled C bodies, expected/
gets populated with your own build output — objdiff then compares your
build against a copy of itself and reports bogus 100 %.

This script prevents that by swapping every decomp C function back to
INCLUDE_ASM before `make expected`, then restoring src/ to its original
state. The resulting `expected/*.o` reflects the raw-asm baseline.

For each `func_NAME` that has a corresponding
`asm/nonmatchings/<seg>/<seg>/func_NAME.s` file, the script strips any
C definition from src/ and substitutes INCLUDE_ASM. NM-wrapped forms
(`#ifdef NON_MATCHING ... #else INCLUDE_ASM(...); #endif`) collapse to
just the INCLUDE_ASM line.

Usage:
    scripts/refresh-expected-baseline.py
"""
import glob
import re
import subprocess
import sys
from pathlib import Path


def func_map():
    """Return {func_name: segment} for each .s file."""
    out = {}
    for p in glob.glob("asm/nonmatchings/*/*/*.s"):
        parts = Path(p).parts
        out[Path(p).stem] = parts[-3]
    return out


# Regex for a bare `<func_name>(...)` — used to find candidate call/def sites.
# Wrapped per-function, but compiled once per name per file.
def find_occurrences(text, func_name):
    """Yield (start_of_name, end_of_name_open_paren) for each `func_name(` in text."""
    name_re = re.compile(r"\b" + re.escape(func_name) + r"\s*\(")
    for m in name_re.finditer(text):
        yield m.start(), m.end()


def skip_paren_group(text, i):
    """Given text[i-1] == '(', walk past the matching ')'. Return index past ')'."""
    depth = 1
    while i < len(text) and depth > 0:
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
        i += 1
    return i


def skip_brace_group(text, i):
    """Given text[i-1] == '{', walk past the matching '}'. Return index past '}'."""
    depth = 1
    while i < len(text) and depth > 0:
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
        i += 1
    return i


def is_function_definition_here(text, name_start, args_end):
    """Given `func_name(` matched at name_start..args_end-1, check if
    it's a function definition (not a call or forward decl).
    Returns the past-of-closing-`}` index, or None if not a definition."""
    # Check prefix: must be start-of-line (modulo whitespace + return type)
    line_start = text.rfind("\n", 0, name_start) + 1
    prefix = text[line_start:name_start].rstrip()
    # Prefix should end with identifier/`*` (a type) and not contain `(`
    if "(" in prefix or prefix.endswith(";") or prefix.endswith(","):
        return None
    if not prefix:
        # Could be `name(` at start of line — unlikely to be a def
        return None
    last = prefix[-1]
    if not (last.isalnum() or last == "_" or last == "*"):
        return None

    # Walk past the arglist
    i = skip_paren_group(text, args_end)
    # Skip whitespace
    while i < len(text) and text[i] in " \t\n":
        i += 1
    if i >= len(text) or text[i] != "{":
        return None
    end = skip_brace_group(text, i + 1)
    return end


def strip_decomp_in_file(text, asm_funcs, seg_hint):
    """For every func_name in asm_funcs that appears in text as either
    a bare def or an NM wrap, replace with INCLUDE_ASM. Returns (new_text, n)."""
    replacements = []  # list of (start, end, include_line)

    # First pass: locate NM wraps. These span #ifdef NON_MATCHING .. #endif.
    nm_blocks = []
    idx = 0
    while True:
        start = text.find("#ifdef NON_MATCHING", idx)
        if start < 0:
            break
        # Find matching #endif (no nesting expected in this project)
        endif = text.find("#endif", start)
        if endif < 0:
            break
        block_end = endif + len("#endif")
        # Advance past trailing newline so we don't leave a blank artifact
        if block_end < len(text) and text[block_end] == "\n":
            block_end += 1
        block = text[start:block_end]
        # Extract the INCLUDE_ASM from #else path
        m = re.search(r"#else\s*\n\s*(INCLUDE_ASM\([^;]*\);)", block)
        if m:
            nm_blocks.append((start, block_end, m.group(1) + "\n"))
        idx = endif + 1

    # Apply NM replacements first (reverse order, so earlier indices stay valid).
    for start, end, replacement in reversed(nm_blocks):
        text = text[:start] + replacement + text[end:]

    # Second pass: bare function definitions.
    n = 0
    for name, seg in asm_funcs.items():
        pos = 0
        while True:
            hit = text.find(name, pos)
            if hit < 0:
                break
            # Require word-boundary before/after `name`
            before = text[hit - 1] if hit > 0 else " "
            after_idx = hit + len(name)
            after = text[after_idx] if after_idx < len(text) else " "
            if (before.isalnum() or before == "_") or (after.isalnum() or after == "_"):
                pos = hit + 1
                continue
            # Must be followed by `(` (possibly with whitespace)
            j = after_idx
            while j < len(text) and text[j] in " \t":
                j += 1
            if j >= len(text) or text[j] != "(":
                pos = hit + 1
                continue
            end_of_def = is_function_definition_here(text, hit, j + 1)
            if end_of_def is None:
                pos = hit + 1
                continue
            # Found a definition. Replace from start-of-line to end.
            line_start = text.rfind("\n", 0, hit) + 1
            include = f'INCLUDE_ASM("asm/nonmatchings/{seg}/{seg}", {name});\n'
            text = text[:line_start] + include + text[end_of_def:]
            n += 1
            pos = line_start + len(include)

    return text, n + len(nm_blocks)


def main():
    asm_funcs = func_map()
    src_c = sorted(glob.glob("src/**/*.c", recursive=True))
    if not src_c:
        print("refresh-baseline: no src/**/*.c found", file=sys.stderr)
        sys.exit(1)

    backup = {p: Path(p).read_text() for p in src_c}

    try:
        total = 0
        for p in src_c:
            new_txt, n = strip_decomp_in_file(backup[p], asm_funcs, None)
            if n:
                Path(p).write_text(new_txt)
                total += n
        print(f"refresh-baseline: swapped {total} decomp bodies → INCLUDE_ASM")

        print("refresh-baseline: make clean")
        subprocess.check_call(["make", "clean"], stdout=subprocess.DEVNULL)
        print("refresh-baseline: make RUN_CC_CHECK=0 (baseline build)")
        subprocess.check_call(
            ["make", "-j", "4", "RUN_CC_CHECK=0"], stdout=subprocess.DEVNULL
        )
        print("refresh-baseline: make expected")
        subprocess.check_call(
            ["make", "expected", "RUN_CC_CHECK=0"], stdout=subprocess.DEVNULL
        )
    finally:
        for p, txt in backup.items():
            Path(p).write_text(txt)

    print("refresh-baseline: make (restore build with decomp C)")
    subprocess.check_call(["make", "-j", "4", "RUN_CC_CHECK=0"], stdout=subprocess.DEVNULL)
    print("refresh-baseline: done; expected/*.o now reflects pure-asm baseline")


if __name__ == "__main__":
    main()
