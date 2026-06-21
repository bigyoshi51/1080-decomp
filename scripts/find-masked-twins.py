#!/usr/bin/env python3
"""find-masked-twins.py — cross-module masked-twin sweep.

DONORS  = MATCHED functions (build/.o reloc-masked == expected/.o reloc-masked
          AND reloc symbol-sets equal). We have correct C for these.
TARGETS = UNMATCHED functions (not matched). Raw bytes from expected/.o (target bytes).

Signature masks immediate/branch/jump/mem-offset bits, keeps opcode+regs.
Report clusters with >=1 MATCHED donor + >=1 UNMATCHED target of DIFFERENT name.
"""
import os, sys, glob, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from twinlib import ROOT, funcs_words, text_funcs, text_bytes, reloc_offsets

def mask_word(w):
    op = (w >> 26) & 0x3f
    if op == 0:
        return ('R', w & 0x3f, (w >> 21) & 0x1f, (w >> 16) & 0x1f, (w >> 11) & 0x1f, (w >> 6) & 0x1f)
    if op == 1:
        return ('R1', (w >> 16) & 0x1f, (w >> 21) & 0x1f)
    if op in (2, 3):
        return ('J', op)
    if op in (16, 17, 18):
        return ('C', op, (w >> 21) & 0x1f, (w >> 16) & 0x1f, (w >> 11) & 0x1f, w & 0x7ff)
    return ('I', op, (w >> 21) & 0x1f, (w >> 16) & 0x1f)

def sig(words):
    return tuple(mask_word(w) for w in words)

def func_reloc_set(opath, name, fs):
    a, sz = fs[name]
    rel = {}
    for off, (typ, symb) in reloc_offsets(opath).items():
        if a <= off < a + sz:
            rel[(off - a) // 4] = (typ, symb)
    return rel

def masked_for_match(words, rel):
    out = list(words)
    for idx, (typ, _s) in rel.items():
        if idx < len(out):
            if typ == 'R_MIPS_26':
                out[idx] = out[idx] & 0xFC000000
            else:
                out[idx] = out[idx] & 0xFFFF0000
    return out

def reloc_symset(rel):
    return frozenset((typ, s) for typ, (t2, s) in [(r[0], r) for r in []]) if False else \
        frozenset((typ, s) for (typ, s) in rel.values())

def episode_set():
    d = os.path.join(ROOT, 'episodes')
    return set(f[:-5] for f in os.listdir(d) if f.endswith('.json'))

def main():
    # cache per-unit data
    exp_units = glob.glob(os.path.join(ROOT, 'expected/src/**/*.c.o'), recursive=True)
    eps = episode_set()
    matched = {}      # name -> (unit, words)
    unmatched = {}    # name -> (unit, words)
    name_words = {}

    for opath in exp_units:
        unit = os.path.relpath(opath, os.path.join(ROOT, 'expected/src'))
        bpath = os.path.join(ROOT, 'build/src', unit)
        efs = text_funcs(opath)
        if not efs: continue
        edata = text_bytes(opath)
        bfs = text_funcs(bpath) if os.path.exists(bpath) else {}
        bdata = text_bytes(bpath) if os.path.exists(bpath) else b''
        erel_all = reloc_offsets(opath)
        brel_all = reloc_offsets(bpath) if os.path.exists(bpath) else {}
        for nm, (a, sz) in efs.items():
            chunk = edata[a:a+sz]
            if len(chunk) < sz: continue
            ew = list(struct.unpack('>%dI' % (sz // 4), chunk[:sz//4*4]))
            if len(ew) < 4: continue
            name_words[nm] = ew
            # reloc set within func (expected)
            erel = {(o-a)//4: v for o, v in erel_all.items() if a <= o < a+sz}
            is_matched = nm in eps
            if is_matched:
                matched[nm] = (unit, ew, erel)
            else:
                unmatched[nm] = (unit, ew, erel)

    print(f"matched={len(matched)} unmatched={len(unmatched)}", file=sys.stderr)

    by_sig = {}
    for nm, (unit, ew, erel) in matched.items():
        by_sig.setdefault(sig(ew), {'d': [], 't': []})['d'].append((nm, unit))
    for nm, (unit, ew, erel) in unmatched.items():
        s = sig(ew)
        if s in by_sig:
            by_sig[s]['t'].append((nm, unit))

    clusters = []
    for s, dt in by_sig.items():
        if dt['d'] and dt['t']:
            # require at least one target name differs from all donor names
            dnames = set(n for n, _ in dt['d'])
            tgts = [(n, u) for n, u in dt['t'] if n not in dnames]
            if tgts:
                clusters.append((len(s), dt['d'], tgts))
    clusters.sort(key=lambda c: -c[0])
    print(f"=== {len(clusters)} cross-name twin clusters ===\n")
    for n, dl, tl in clusters:
        print(f"[{n} insns]")
        for nm, u in dl: print(f"  DONOR  {nm}  ({u})")
        for nm, u in tl: print(f"  TARGET {nm}  ({u})")
        print()

if __name__ == '__main__':
    main()
