#!/usr/bin/env python3
"""Find GENUINE, fixable decomp near-misses using objdiff's per-function fuzzy.

WHY (2026-05-31): a raw build-vs-expected `.o` byte-diff OVER-REPORTS — it flags
reloc-blind functions (jal-bake, `&D+N` addend, scalar-%lo) as diffs, but objdiff
(which generates report.json -> decomp.dev) is RELOC-AWARE and already scores them
100%. Chasing those gains ZERO %. The ONLY genuine uncounted near-misses are real
instruction-field diffs. This script uses objdiff `fuzzy_match_percent` (the decomp.dev
metric) to find them, then decodes each and classifies the diff SHAPE so you can target
the C-FIXABLE ones (branch-polarity, wrong offset/immediate, signedness) instead of the
hard caps (register-renumber, instruction-scheduler reorder, -O0 stack-slot, FP-operand).

Usage:
    scripts/find-fixable-nearmisses.py [--min 95] [--max-size 200] [--exclude game_uso,gui_uso]
    # regenerate the report first if stale:
    objdiff-cli report generate -o /tmp/rep.json    (then --report /tmp/rep.json)
"""
import argparse, json, re, subprocess, os, sys

def meta(o, sym):
    out = subprocess.check_output(['mips-linux-gnu-readelf', '-sW', o], text=True)
    for ln in out.splitlines():
        p = ln.split()
        if len(p) >= 8 and p[7] == sym:
            return int(p[1], 16), int(p[2])
    return None

def dis(o, a, s):
    d = subprocess.check_output(['mips-linux-gnu-objdump', '-d', '-j', '.text',
                                 '--no-show-raw-insn', '-M', 'no-aliases', o], text=True)
    r = {}
    for ln in d.splitlines():
        m = re.match(r'\s+([0-9a-f]+):\t(.*)', ln)
        if m:
            x = int(m.group(1), 16)
            if a <= x < a + s:
                r[x - a] = re.sub(r'\s+', ' ', m.group(2).split(';')[0]).strip()
    return r

def norm_branch(s):  # strip absolute target so PC-relative branches aren't false diffs
    return re.sub(r'[0-9a-f]+ <', '<', s) if s else s

def classify(real):
    """Return (fixable_tag or None, all_tags) for a list of (off, exp, got) diffs."""
    tags = set()
    for o, e, b in real:
        if not e or not b:
            tags.add('SIZE'); continue
        em, bm = e.split()[0], b.split()[0]
        if em != bm:
            if {em, bm} <= {'beq','bne','beql','bnel','beqz','bnez'}: tags.add('BRANCH-POL')
            elif {em, bm} <= {'srl','sra'}: tags.add('SIGNED-SHIFT')
            elif {em, bm} <= {'slt','sltu','slti','sltiu'}: tags.add('SIGNED-CMP')
            elif {em, bm} <= {'addu','addiu','subu'}: tags.add('ADD-FORM')
            else: tags.add('MNEM-OTHER')
        elif re.search(r'\bsp\b', e) or re.search(r'\bsp\b', b):
            tags.add('STACK-SLOT')  # sp-relative offset/addiu = frame/spill placement (HARD cap, not C-fixable)
        else:
            eoff = re.search(r'(-?\d+)\(', e); boff = re.search(r'(-?\d+)\(', b)
            ei = re.search(r',(-?\d+)$', e); bi = re.search(r',(-?\d+)$', b)
            if eoff and boff and eoff.group(1) != boff.group(1): tags.add('OFFSET')
            elif ei and bi and ei.group(1) != bi.group(1): tags.add('IMM')
            else: tags.add('REG')  # same mnemonic, register operand differs
    FIX = {'BRANCH-POL', 'SIGNED-SHIFT', 'SIGNED-CMP', 'OFFSET', 'IMM', 'ADD-FORM'}
    fixable = tags & FIX and not (tags & {'REG', 'SIZE', 'MNEM-OTHER', 'STACK-SLOT'})
    return (fixable, tags)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--report', default='/tmp/rep.json')
    ap.add_argument('--min', type=float, default=95.0)
    ap.add_argument('--max-size', type=int, default=200)
    ap.add_argument('--max-diffs', type=int, default=4)
    ap.add_argument('--exclude', default='')
    ap.add_argument('--all', action='store_true', help='show hard caps too, not just fixable')
    a = ap.parse_args()
    if not os.path.exists(a.report):
        subprocess.run(['objdiff-cli', 'report', 'generate', '-o', a.report], check=True)
    r = json.load(open(a.report))
    excl = [x for x in a.exclude.split(',') if x]
    rows = []
    for u in r['units']:
        seg = u['name']
        if any(x in seg for x in excl): continue
        B, E = 'build/non_matching/' + seg + '.c.o', 'expected/' + seg + '.c.o'
        if not (os.path.exists(B) and os.path.exists(E)): continue
        for fn in u.get('functions', []):
            f = fn.get('fuzzy_match_percent')
            if not f or not (a.min <= f < 100) or int(fn['size']) > a.max_size: continue
            mb, me = meta(B, fn['name']), meta(E, fn['name'])
            if not mb or not me: continue
            bd, ed = dis(B, *mb), dis(E, *me)
            real = [(o, ed.get(o), bd[o]) for o in sorted(bd)
                    if bd[o] != ed.get(o)
                    and norm_branch(ed.get(o)) != norm_branch(bd[o])]
            if not real or len(real) > a.max_diffs: continue
            fixable, tags = classify(real)
            if fixable or a.all:
                rows.append((f, int(fn['size']), fn['name'], seg.split('/')[-1],
                             len(real), 'FIXABLE' if fixable else 'cap', sorted(tags), real))
    rows.sort(key=lambda x: (-int(x[5] == 'FIXABLE'), -x[0]))
    for f, sz, n, s, nd, kind, tags, real in rows:
        print(f"[{kind}] {f:6.2f}% {sz:4d}b {n} ({s}) {nd}d {tags}")
        for o, e, b in real:
            print(f"        {o:#6x} exp:{e:28s} got:{b}")
    print(f"\n{sum(1 for x in rows if x[5]=='FIXABLE')} fixable / {len(rows)} shown", file=sys.stderr)

if __name__ == '__main__':
    main()
