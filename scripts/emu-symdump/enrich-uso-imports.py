#!/usr/bin/env python3
"""Enrich a USO symname table's import_<addr> entries with REAL names from a
reference module's symname table (typically bootup_uso, which holds most of the
cross-module call targets).

A freshly-correlated proc USO (uso-correlate.py) names its external targets
import_<RAMaddr>. Many of those addresses land inside bootup_uso/game_libs (one
shared RAM image). Given bootup's RAM textbase, import_addr - textbase = a bootup
project offset whose name is in bootup_uso.symnames. This rewrites the resolvable
imports to those real names; KSEG0-kernel and mid-object addrs are left as-is (the
address is the identity). Works on both the symIdx->name (uso-correlate) and
offset->name (game-uso-name-join, under a top-level "names" key) layouts.

Textbase is auto-voted (import_addr - knownRefFuncOff clusters at the true base);
for the 2026-05-30 dump that is bootup textbase 0x95e50.

Usage:
  enrich-uso-imports.py --in titproc_uso.symnames.json \
      --ref bootup_uso.symnames.json [--textbase 0x95e50] --out titproc_uso.symnames.json
"""
import argparse, json, re, collections

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--in', dest='inp', required=True)
    ap.add_argument('--ref', required=True)
    ap.add_argument('--textbase', type=lambda x:int(x,0), default=0)
    ap.add_argument('--out', required=True)
    a=ap.parse_args()
    ref=json.load(open(a.ref))
    func_off={}; data_off={}
    for name in ref.values():
        m=re.match(r'func_([0-9A-Fa-f]+)$',name)
        if m: func_off[int(m.group(1),16)]=name
        m=re.match(r'D_([0-9A-Fa-f]+)$',name)
        if m: data_off[int(m.group(1),16)]=name
    doc=json.load(open(a.inp))
    table=doc['names'] if isinstance(doc,dict) and 'names' in doc else doc
    imps=[int(m.group(1),16) for n in table.values()
          for m in [re.match(r'import_([0-9A-Fa-f]+)$',n)] if m and int(m.group(1),16)<0x80000000]
    tb=a.textbase
    if not tb:
        votes=collections.Counter()
        for addr in imps:
            for off in func_off:
                t=addr-off
                if 0<t<0x100000: votes[t]+=1
        tb=votes.most_common(1)[0][0]
        print(f'auto textbase={tb:#x} (votes={votes.most_common(1)[0][1]})')
    named=0; kept=0
    for k,n in list(table.items()):
        m=re.match(r'import_([0-9A-Fa-f]+)$',n)
        if not m: continue
        a_=int(m.group(1),16)
        if a_>=0x80000000: kept+=1; continue
        off=a_-tb
        if off in func_off:   table[k]=func_off[off]; named+=1
        elif off in data_off: table[k]=data_off[off]; named+=1
        else: kept+=1
    json.dump(doc, open(a.out,'w'))
    print(f'enriched {named} imports -> real names; {kept} kept as import_<addr>. wrote {a.out}')

if __name__=='__main__':
    main()
