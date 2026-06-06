#!/usr/bin/env python3
"""Fix the "Label .LX refers to a delay slot" m2c abort on jumptable .s files.

`uso-jumptable-to-m2c.py` emits m2c-ready .s with .L case labels, but a case
target often lands on a branch/jal DELAY SLOT (very common in the game_libs
script-VM family: `jal handler` / `bnel ...` with the next insn doubling as a
jumptable target). m2c aborts on a label in a delay slot.

This duplicates the delay-slot instruction: one copy stays as the branch's real
delay slot (unlabeled), the other carries the .L label as a normal instruction.
Semantically safe for the IDEMPOTENT arg-setup instructions that dominate these
slots (li/move/lui/lw-into-arg): the fall-through path runs it twice but IDO
dedups the redundant store, so the compiled bytes are unchanged. (Not safe for
non-idempotent delay slots — stores, sp adjusts — but those don't occur as
jumptable targets here.)

Usage:
    uso-jumptable-to-m2c.py ... > fn.s
    fix-jumptable-delay-slot.py fn.s      # in place
    uv run m2c --target mips-ido-c fn.s

Validated 2026-06-06: unblocked m2c on gl_func_00026790 / 0002C7A4 / 00039094 /
0002BB7C / 00030AF4 (game_libs). NOTE: m2c may still need REGISTER-CARRYING
cleanup afterward (case operands loaded pre-`jr` show as `M2C_ERROR(unset
register $tN)` — resolve them from the dispatch prologue in the .s).
"""
import sys, re

BR = re.compile(r'^\s*/\*[^*]*\*/\s*(jal|j|jr|b|beq|bne|blez|bgtz|bgez|bltz|'
                r'beql|bnel|bc1t|bc1f|bgezal|bltzal)\b')


def is_insn(l):
    return l.lstrip().startswith('/*')


def is_lbl(l):
    return re.match(r'^\.L[0-9a-f]+:', l.strip())


def main():
    path = sys.argv[1]
    lines = open(path).read().split('\n')
    out = []
    i = 0
    n = len(lines)
    patched = 0
    while i < n:  # noqa
        l = lines[i]
        if is_lbl(l):
            j = len(out) - 1
            while j >= 0 and out[j].strip() == '':
                j -= 1
            prev = out[j] if j >= 0 else ''
            k = i + 1
            while k < n and lines[k].strip() == '':
                k += 1
            if BR.match(prev) and k < n and is_insn(lines[k]):
                out.append(lines[k])   # duplicate -> real delay slot
                out.append(l)          # the label
                patched += 1
                i += 1                 # original delay insn stays (now under the label)
                continue
        out.append(l)
        i += 1
    open(path, 'w').write('\n'.join(out))
    print("patched %d delay-slot label(s)" % patched)


if __name__ == '__main__':
    main()
