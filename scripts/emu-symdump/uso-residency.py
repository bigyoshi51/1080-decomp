#!/usr/bin/env python3
"""Is a USO's decompressed CODE block GENUINELY resident + relocated in a RAM dump?

The single-probe trap (README "Verify residency"): a 32- or even 64-byte slice of
a USO block can coincidentally appear in RAM, falsely reporting "resident". The
honest test, used by every dump step:
  1. multi-probe: many unique 48-byte non-zero slices must all back-compute the
     SAME text base (a coincidence won't be consistent),
  2. relocated: at that base, RAM has ZERO jal-0 placeholders (a loaded-but-not-
     relocated or wrong-base region still shows the on-disk jal 0 / lui 0).

Returns the text base (and vote count) when genuine, else None. Importable
(`genuine_residency(ram, blk)`) or CLI.

  uso-residency.py --block assets/timproc_uso_block_1.bin --ram /tmp/race_HIT.bin
"""
import argparse, struct, collections, sys

def genuine_residency(ram, blk, min_votes=8, step=0x100):
    """-> (tbase, votes) if blk is genuinely resident+relocated in ram, else None."""
    tbs=collections.Counter()
    for poff in range(0x40, len(blk)-48, step):
        probe=blk[poff:poff+48]
        if probe.count(0)>=16: continue          # skip placeholder/zero runs
        idx=ram.find(probe)
        if idx>=0 and ram.find(probe, idx+4)<0:  # found AND unique
            tbs[idx-poff]+=1
    if not tbs: return None
    tb,v=tbs.most_common(1)[0]
    if v<min_votes: return None                  # too few consistent probes
    ru=lambda p: struct.unpack_from(">I",ram,p)[0]
    ph=sum(1 for i in range(0,len(blk),4) if (ru(tb+i)>>26)==3 and (ru(tb+i)&0x3ffffff)==0)
    return (tb,v) if ph==0 else None             # any RAM jal-0 left = not relocated here

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--block', required=True)
    ap.add_argument('--ram', required=True)
    ap.add_argument('--min-votes', type=int, default=8)
    a=ap.parse_args()
    r=genuine_residency(open(a.ram,'rb').read(), open(a.block,'rb').read(), a.min_votes)
    if r: print(f"RESIDENT tbase={r[0]:#x} ({r[1]} unique probes, RAM fully relocated)"); sys.exit(0)
    print("absent / not genuinely resident"); sys.exit(1)

if __name__=='__main__':
    main()
