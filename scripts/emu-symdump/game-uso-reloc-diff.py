#!/usr/bin/env python3
"""Recover game_uso's resolved reloc sites by DIFFING the on-disk (placeholder)
Text against the RAM-resolved Text from a gameplay emulator dump.

WHY this instead of parsing the on-disk Sym/TextReloc sections: game_uso is a
COMPRESSED Kyoto USO (Yay0 blocks) and is only ~88% byte-matched, so the build
.o's ELF relocs are incomplete (INCLUDE_ASM functions carry raw-.word relocs
absent from the .o). Diffing the full decompressed Text against the loader's
resolved Text in RAM captures EVERY reloc site -- matched and INCLUDE_ASM alike
-- with no Sym/TextReloc parsing.

PIPELINE (all steps validated 2026-05-30):
  1. Decompress game_uso's Yay0 CODE block -> assets/game_uso_block_1.bin
     (`scripts/extract-uso-yay0.py --write`; block 1 = 0x11B30 Text).
  2. Dump RAM at gameplay via `uso-emu-dump.py --real-render` (game_uso only
     loads once the title/menu is reached).
  3. Probe-align: a unique 32-byte non-reloc slice of block1 locates the RAM
     Text base (validated constant tbase across offsets 0x80..0x8000).
  4. Diff word-by-word: every differing word is a reloc site; the RAM word is
     the resolved value. ~2038 sites (978 jal call-sites + ~1060 data hi/lo).

TARGET CLASSIFICATION (empirical RAM module map, this dump):
  * 0x007Exxxx / 0x007Fxxxx  -> inside game_uso text -> internal  func_<projoff>
  * 0x807Exxxx / 0x807Fxxxx  -> KSEG0 mirror of game_uso rodata/data -> D_<addr>
  * 0x0009xxxx..0x0011xxxx and 0x80(02/05/06/08)xxxx
                             -> bootup_uso / game_libs / kernel -> import_<addr>
  The import_ addresses still need a final join against the bootup/kernel RAM
  symbol tables (the 1672-symbol bootup dump) to get func_/game_libs_func/osXxx
  NAMES; this script emits the resolved ADDRESS + class so that join is a pure
  lookup. See the migration memo for the remaining join step.

Usage:
  game-uso-reloc-diff.py --block assets/game_uso_block_1.bin --ram /tmp/final_rdram.bin \
      --out scripts/emu-symdump/game_uso.reloc-sites.json
"""
import argparse, json, struct, sys

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--block', required=True, help='decompressed game_uso CODE block (block_1.bin)')
    ap.add_argument('--ram', required=True, help='gameplay RDRAM dump (big-endian, from uso-emu-dump.py)')
    ap.add_argument('--tbase', type=lambda x:int(x,0), default=0, help='RAM Text base; 0=auto-probe')
    ap.add_argument('--out', required=True)
    a=ap.parse_args()
    ram=open(a.ram,'rb').read(); blk=open(a.block,'rb').read()
    ru=lambda p:struct.unpack_from('>I',ram,p)[0]; bu=lambda p:struct.unpack_from('>I',blk,p)[0]
    TEXT_SZ=len(blk)

    tbase=a.tbase
    if not tbase:
        for poff in range(0x80, TEXT_SZ-32, 0x80):
            probe=blk[poff:poff+32]
            if probe.count(0)>=10: continue
            idx=ram.find(probe)
            if idx>=0 and ram.find(probe, idx+4)<0:
                tbase=idx-poff; break
        if not tbase: sys.exit('auto-probe failed: no unique non-reloc slice found')
    print(f'tbase={tbase:#x} text_sz={TEXT_SZ:#x}', file=sys.stderr)

    op=lambda w:w>>26
    lo,hi=tbase,tbase+TEXT_SZ
    def classify(addr):
        a32=addr&0xffffffff; reg=a32>>16
        if lo<=a32<hi: return 'func', f'func_{a32-tbase:08X}'   # internal call (project offset)
        if 0x807e<=reg<=0x807f: return 'data', f'D_{a32:08X}'    # KSEG0 game_uso data
        return 'import', f'import_{a32:08X}'                      # other module / kernel

    sites=[]; i=0
    while i<TEXT_SZ:
        d,r=bu(i),ru(tbase+i)
        if d!=r:
            o=op(d)
            if o==3:                       # jal (R_MIPS_26)
                tgt=(tbase&0xf0000000)|((r&0x3FFFFFF)<<2)
                cls,name=classify(tgt)
                sites.append({'off':i,'kind':'jal','resolved':tgt&0xffffffff,'class':cls,'name':name})
            elif o==0xF:                   # lui (R_MIPS_HI16) - pair with following lo16
                hi16=r&0xFFFF; paired=False
                for j in range(i+4,min(i+0x60,TEXT_SZ),4):
                    rj,dj=ru(tbase+j),bu(j)
                    if dj!=rj and op(dj) in (9,0x23,0x2b,0x21,0x25,0x29,0x28,0x24,0x35,0x37):
                        lo16=rj&0xFFFF; lo16=lo16-0x10000 if lo16&0x8000 else lo16
                        addr=(hi16<<16)+lo16; cls,name=classify(addr)
                        sites.append({'off':i,'kind':'hi16','resolved':addr&0xffffffff,'class':cls,'name':name,'lo_off':j})
                        paired=True; break
                if not paired:
                    sites.append({'off':i,'kind':'hi16','resolved':(hi16<<16),'class':'unpaired','name':None})
        i+=4
    cnt={}
    for s in sites: cnt[s['class']]=cnt.get(s['class'],0)+1
    json.dump({'tbase':tbase,'text_sz':TEXT_SZ,'n_sites':len(sites),'class_counts':cnt,'sites':sites},
              open(a.out,'w'), indent=0)
    print(f'wrote {a.out}: {len(sites)} reloc sites  {cnt}', file=sys.stderr)

if __name__=='__main__':
    main()
