#!/usr/bin/env python3
"""Join game_uso's reloc-sites (game-uso-reloc-diff.py) against the bootup_uso
symbol table to give each game_uso reloc its REAL target name.

The reloc-sites map classifies targets as func_/D_ (internal) or import_<addr>
(external RAM address). Most external imports land in bootup_uso/game_libs (which
share one RAM image); this resolves them to real names via:

    bootup_off = import_addr - BOOTUP_TEXTBASE
    name       = bootup_uso.symnames[symIdx whose name is func_<bootup_off>]

BOOTUP_TEXTBASE is recovered by voting: for the true base, (import_addr - off)
clusters at one value across all known bootup func offsets. In the 2026-05-30
game_uso gameplay dump the winner was 0x95e50 (486 votes vs 326 runner-up).

Imports that miss (data-refs into the middle of an object -> hi/lo offset isn't a
symbol START; or KSEG0 0x80xxxxxx kernel addrs absent from symbol_addrs.txt) keep
their import_<addr> name -- the address IS the identity.

Usage:
  game-uso-name-join.py --sites game_uso.reloc-sites.json \
      --bootup bootup_uso.symnames.json --textbase 0x95e50 \
      --out game_uso.symnames.json
"""
import argparse, json, re

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--sites', required=True)
    ap.add_argument('--bootup', required=True)
    ap.add_argument('--textbase', type=lambda x:int(x,0), default=0,
                    help='bootup RAM textbase; 0 = auto-vote from the import targets')
    ap.add_argument('--out', required=True)
    a=ap.parse_args()
    sym=json.load(open(a.bootup))
    func_off={}; data_off={}
    for name in sym.values():
        m=re.match(r'func_([0-9A-Fa-f]+)$',name)
        if m: func_off[int(m.group(1),16)]=name
        m=re.match(r'D_([0-9A-Fa-f]+)$',name)
        if m: data_off[int(m.group(1),16)]=name
    d=json.load(open(a.sites))
    imp=[s['resolved'] for s in d['sites'] if s['class']=='import' and s['resolved']<0x80000000]

    tb=a.textbase
    if not tb:
        import collections
        votes=collections.Counter()
        for addr in imp:
            for off in func_off:
                t=addr-off
                if 0<t<0x100000: votes[t]+=1
        tb=votes.most_common(1)[0][0]
        print(f'auto textbase={tb:#x} (votes={votes.most_common(1)[0][1]})')

    out={}; stats={'func':0,'data':0,'import_named':0,'import_kernel':0,'import_unnamed':0}
    for s in d['sites']:
        off=f"{s['off']:#x}"; cls=s['class']; a_=s['resolved']
        if cls=='func': out[off]=s['name']; stats['func']+=1
        elif cls=='data': out[off]=s['name']; stats['data']+=1
        elif cls=='import':
            if a_>=0x80000000:
                out[off]=s['name']; stats['import_kernel']+=1            # import_<kseg0addr>
            else:
                bo=a_-tb
                if bo in func_off:   out[off]=func_off[bo]; stats['import_named']+=1
                elif bo in data_off: out[off]=data_off[bo]; stats['import_named']+=1
                else:                out[off]=s['name']; stats['import_unnamed']+=1
        else:
            out[off]=s.get('name') or f"unpaired_{s['off']:#x}"
    json.dump({'bootup_textbase':tb,'stats':stats,'names':out}, open(a.out,'w'), indent=0)
    print(f'wrote {a.out}: {len(out)} named reloc sites  {stats}')

if __name__=='__main__':
    main()
