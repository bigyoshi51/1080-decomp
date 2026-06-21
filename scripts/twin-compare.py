#!/usr/bin/env python3
"""twin-compare.py DONOR_NAME TARGET_NAME
Confirm two functions are exact masked-twins: reloc-masked words identical.
Prints per-index diffs and reloc symbol mapping."""
import os, sys, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from twinlib import ROOT, text_funcs, text_bytes, reloc_offsets
import glob

def find(name):
    for opath in glob.glob(os.path.join(ROOT, 'expected/src/**/*.c.o'), recursive=True):
        fs = text_funcs(opath)
        if name in fs:
            a, sz = fs[name]
            data = text_bytes(opath)
            w = list(struct.unpack('>%dI' % (sz//4), data[a:a+sz][:sz//4*4]))
            rel = {(o-a)//4: v for o, v in reloc_offsets(opath).items() if a <= o < a+sz}
            return opath, w, rel
    return None, None, None

def maskw(w, typ):
    if typ == 'R_MIPS_26': return w & 0xFC000000
    return w & 0xFFFF0000

def main():
    dn, tn = sys.argv[1], sys.argv[2]
    do, dw, dr = find(dn)
    to, tw, tr = find(tn)
    if dw is None: print("donor not found", dn); return
    if tw is None: print("target not found", tn); return
    print(f"DONOR  {dn} [{do}] {len(dw)} insns, {len(dr)} relocs")
    print(f"TARGET {tn} [{to}] {len(tw)} insns, {len(tr)} relocs")
    if len(dw) != len(tw):
        print("LENGTH MISMATCH", len(dw), len(tw)); return
    ndiff = 0
    for i in range(len(dw)):
        dwm = maskw(dw[i], dr[i][0]) if i in dr else dw[i]
        twm = maskw(tw[i], tr[i][0]) if i in tr else tw[i]
        if dwm != twm:
            ndiff += 1
            print(f"  DIFF [{i}] donor={dw[i]:08X}({dr.get(i)}) target={tw[i]:08X}({tr.get(i)})")
    print(f"NON-RELOC DIFFS: {ndiff}")
    print("--- reloc map (index: donor_sym -> target_sym) ---")
    for i in sorted(set(dr)|set(tr)):
        print(f"  [{i}] {dr.get(i)}  ->  {tr.get(i)}")

if __name__ == '__main__':
    main()
