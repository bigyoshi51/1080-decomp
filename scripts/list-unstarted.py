#!/usr/bin/env python3
"""List genuinely-unstarted functions, authoritatively, from report.json.

The grep-the-src census repeatedly produced false "unstarted" candidates
(2026-06-10: three in one tick) because C definitions take many shapes a
simple regex misses: pointer returns (`void *fn(`), K&R implicit-int
(`fn(a0) int *a0; {`), and macro-wrapped forms. report.json is the
authority: fuzzy_match_percent == 100 means matched, anything else is
genuinely-not-matched. A fn is "started" if src holds an #ifdef
NON_MATCHING wrap mentioning it (partial C exists).

Usage: python3 scripts/list-unstarted.py [--max-size N] [--seg SEG]
Sort: size ascending. Run from the project root after refreshing
report.json (objdiff-cli report generate -o report.json).
"""
import json, os, re, argparse

ap = argparse.ArgumentParser()
ap.add_argument('--max-size', type=lambda x: int(x, 0), default=0x10000)
ap.add_argument('--seg', default=None)
args = ap.parse_args()

wrapped = set()
for root, dirs, files in os.walk('src'):
    for fn in files:
        if not fn.endswith('.c'):
            continue
        txt = open(os.path.join(root, fn)).read()
        for m in re.finditer(r'#ifdef NON_MATCHING(.*?)#endif', txt, re.S):
            for f in re.findall(r'\b((?:\w+_)?(?:gl_)?func_\w{8})\s*\(', m.group(1)):
                wrapped.add(f)

rows = []
r = json.load(open('report.json'))
for u in r['units']:
    seg = u['name'].split('/')[1] if '/' in u['name'] else u['name']
    if args.seg and args.seg not in u['name']:
        continue
    for f in u.get('functions', []):
        pct = f.get('fuzzy_match_percent')
        if pct is None or float(pct) >= 100.0:
            # None = no diff data (e.g. handwritten/no-target); skip both
            continue
        size = int(f.get('size', 0) or 0)
        if size and size <= args.max_size:
            state = 'WRAPPED' if f['name'] in wrapped else 'BARE'
            rows.append((size, f['name'], u['name'], state, pct))

rows.sort()
for size, name, unit, state, pct in rows:
    print(f"{size:#8x} {state:8s} {pct if pct is not None else '-':>8} {name}  ({unit})")
print(f"\n{len(rows)} unmatched functions", f"({sum(1 for r_ in rows if r_[3]=='BARE')} bare)")
