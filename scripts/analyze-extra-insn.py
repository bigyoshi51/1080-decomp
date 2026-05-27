#!/usr/bin/env python3
"""For EXTRA_INSN=1 candidates: identify the single missing/extra instruction
and suggest C-level fixes.

Many functions with exactly 1 size-mismatch insn are 'unused-arg-save' caps
(missing sw aN, off(sp) at entry) or 'dead-arg-load' caps. The tool diffs
the disassembly, locates the diverging insn, and classifies the pattern.

Usage:
  analyze-extra-insn.py [--limit N]
"""
import argparse, json, os, re, struct, subprocess, sys
from pathlib import Path

REPO = Path(__file__).parent.parent.resolve()


def get_disasm_insns(obj_path, sym):
    """Return list of (offset, word, mnemonic_line) tuples."""
    if not os.path.exists(obj_path): return None
    try:
        out = subprocess.check_output(['mips-linux-gnu-objdump', '-d', '-M', 'no-aliases',
                                       obj_path], text=True)
    except: return None
    # Find the function body
    m = re.search(rf'<{re.escape(sym)}>:\s*\n', out)
    if not m: return None
    body = out[m.end():]
    end = re.search(r'\n\s*\.\.\.|\n[0-9a-f]+\s+<', body)
    if end: body = body[:end.start()]
    insns = []
    for line in body.split('\n'):
        m = re.match(r'\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)', line)
        if m:
            insns.append((int(m.group(1), 16), m.group(2), m.group(3).strip()))
    return insns


def analyze_extra(built, expected):
    """Diff two insn lists, return (kind, where, details)."""
    # Find the first divergence
    n = min(len(built), len(expected))
    i = 0
    while i < n and built[i][1] == expected[i][1]:
        i += 1
    if i == n:
        # End-mismatch: one has more insns at the end
        if len(expected) > len(built):
            extras = [e[2] for e in expected[len(built):]]
            return ('MISSING_END', i, extras)
        else:
            extras = [b[2] for b in built[len(expected):]]
            return ('EXTRA_END', i, extras)
    # Check if expected has an extra insn at position i
    if i < len(expected) and i+1 < len(expected):
        # Try shifting: does built[i] == expected[i+1]?
        if i < len(built) and built[i][1] == expected[i+1][1]:
            return ('MISSING_AT', i, expected[i][2])
    if i < len(built) and i+1 < len(built):
        if i < len(expected) and built[i+1][1] == expected[i][1]:
            return ('EXTRA_AT', i, built[i][2])
    # First divergence is an in-place diff
    if i < len(built) and i < len(expected):
        return ('INPLACE', i, f'{built[i][2]} vs {expected[i][2]}')
    return ('UNKNOWN', i, '')


def classify_missing(mnem):
    """Categorize a missing instruction by mnemonic."""
    m = mnem.strip()
    if m.startswith('sw') and 'a0' in m or 'a1' in m or 'a2' in m or 'a3' in m:
        if '(sp)' in m:
            return 'UNUSED_ARG_SAVE'
    if m.startswith('lui '):
        return 'EXTRA_LUI'
    if m.startswith('addiu sp') or m.startswith('addiu\tsp'):
        return 'FRAME_DIFF'
    if 'mtc1' in m or 'mfc1' in m:
        return 'FP_TRANSFER'
    if m.startswith('lw') or m.startswith('lh') or m.startswith('lb'):
        return 'EXTRA_LOAD'
    if m.startswith('sll') or m.startswith('sra') or m.startswith('srl'):
        return 'SHIFT'
    return 'OTHER'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--limit', type=int, default=40)
    args = ap.parse_args()

    subprocess.run(['objdiff-cli', 'report', 'generate', '-o', '/tmp/extra-rep.json'],
                   capture_output=True, cwd=REPO)
    r = json.load(open('/tmp/extra-rep.json'))

    candidates = []
    for u in r['units']:
        unit = u['name']
        for fn in u.get('functions', []):
            fm = fn.get('fuzzy_match_percent', 100)
            sz = int(fn['size'])
            if fm == 100.0 or 'fuzzy_match_percent' not in fn: continue
            if 85 <= fm < 100 and sz <= 250:
                candidates.append((fm, sz, fn['name'], unit))

    # Find candidates where size differs (which is what EXTRA_INSN means)
    by_kind = {}
    seen = 0
    for fm, sz, name, unit in sorted(candidates, key=lambda x: (-x[0], x[1])):
        if seen >= args.limit: break
        nm_obj = str(REPO / 'build/non_matching' / f'{unit}.c.o')
        ex_obj = str(REPO / 'expected' / f'{unit}.c.o')
        b = get_disasm_insns(nm_obj, name)
        e = get_disasm_insns(ex_obj, name)
        if not b or not e: continue
        if len(b) == len(e): continue  # not EXTRA_INSN
        if abs(len(b) - len(e)) > 2: continue  # focus on 1-2 insn diff
        kind, idx, details = analyze_extra(b, e)
        if kind in ('MISSING_AT', 'MISSING_END'):
            mnem = details[0] if isinstance(details, list) else details
            cls = classify_missing(mnem)
            by_kind.setdefault(f'MISSING/{cls}', []).append(
                (fm, sz, name, unit, idx, mnem))
        elif kind in ('EXTRA_AT', 'EXTRA_END'):
            mnem = details[0] if isinstance(details, list) else details
            by_kind.setdefault(f'EXTRA/{classify_missing(mnem)}', []).append(
                (fm, sz, name, unit, idx, mnem))
        else:
            by_kind.setdefault(kind, []).append((fm, sz, name, unit, idx, details[:60]))
        seen += 1

    print(f'\n=== Analysis of {seen} EXTRA_INSN candidates ===\n')
    for kind in sorted(by_kind, key=lambda k: -len(by_kind[k])):
        items = by_kind[kind]
        print(f'  {kind}: {len(items)}')
        for fm, sz, name, unit, idx, detail in items[:5]:
            print(f'    {fm:6.2f}  size={sz:3}  idx={idx:2}  {name:38}  {detail[:50]}')
        if len(items) > 5:
            print(f'    ... +{len(items)-5} more')


if __name__ == '__main__':
    main()
