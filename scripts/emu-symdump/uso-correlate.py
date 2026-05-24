#!/usr/bin/env python3
"""Correlate a byteswapped RDRAM dump (from uso-emu-dump.py) with the decoded
on-disk TextReloc table to recover real symbol names for a USO module.

The loader relocated each placeholder instruction in place, so the RESOLVED word
now encodes the real target address. We re-read each relocated instruction from
the dump, reconstruct its target, and classify it against the module's loaded
sections to name it:
    text   -> func_<off>     (the real intra-module call graph)
    data   -> D_<off>
    rodata -> RO_<off>
    else   -> import_<addr>  (cross-module / kernel ref; needs the on-disk Sym
                              name string to get a human name -- left as addr)

Section layout in RAM is contiguous RoData -> Data -> Text, so given the Text base
(found.json from the dump) and the section sizes (USO directory), the Data and
RoData bases back-compute exactly (validated for bootup.uso: rodata 0x6523c,
data 0x677dc, text 0x95e4c; text_base - data_sz - rodata_sz == rodata_base).

Output: symnames.json {symIdx(str) -> name}, feed to
uso-reloc-symbolize.py --symnames.

Usage: uso-correlate.py --rom baserom.z64 --module 0xD9FE28 \\
           --dump /tmp/rdram.bin --found /tmp/found.json --out symnames.json
"""
import argparse, collections, json, struct, sys

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--module', type=lambda x:int(x,0), required=True)
    ap.add_argument('--dump', default='/tmp/rdram.bin')
    ap.add_argument('--found', default='/tmp/found.json')
    ap.add_argument('--out', default='symnames.json')
    a=ap.parse_args()
    d=open(a.rom,'rb').read()
    be=open(a.dump,'rb').read()
    def u32(o): return struct.unpack_from('>I',d,o)[0]
    def r32(p): return struct.unpack_from('>I',be,p)[0]

    # USO directory -> section data offsets + sizes
    SEC={0,1,2,3,4,5,6,7,8,9}
    if u32(a.module)!=0x12345678: sys.exit(f'no USO magic at {a.module:#x}')
    o=a.module+0xC; secs={}
    while True:
        typ,size=u32(o+4),u32(o+8)
        if typ in (10,11) or typ not in SEC: break
        secs.setdefault(typ,(o+12,size)); o += 12 + (0 if typ==8 else ((size+3)&~3))
    TEXT_SZ=secs[5][1]; DATA_SZ=secs.get(6,(0,0))[1]; ROD_SZ=secs.get(7,(0,0))[1]
    treloc,trsize=secs[2]; treloc+=0  # treloc data offset (entries are 12 bytes)

    TB=json.load(open(a.found))['textbase']     # phys base of Text section data (marker @ TB, func_0 @ TB+4)
    DB=TB-DATA_SZ                                # contiguous: RoData -> Data -> Text
    RB=DB-ROD_SZ
    print(f'bases: rodata={RB:#x} data={DB:#x} text={TB:#x} (sizes ro={ROD_SZ:#x} d={DATA_SZ:#x} t={TEXT_SZ:#x})')

    ents=[]; p=treloc
    while p+12<=treloc+trsize:
        f1=u32(p+4); ents.append((f1>>4, f1&7, u32(p+8))); p+=12
    def resolved(P): return r32(TB+4+P)         # project offset P -> resolved word
    def sext(x): return x-0x10000 if x&0x8000 else x

    def classify(addr):
        q=addr & 0x1FFFFFFF
        if TB+4<=q<TB+TEXT_SZ: return f'func_{q-TB-4:06X}'
        if DB<=q<DB+DATA_SZ:   return f'D_{q-DB:06X}'
        if RB<=q<RB+ROD_SZ:    return f'RO_{q-RB:06X}'
        return f'import_{q:08X}'

    names={}; cls=collections.Counter()
    for symidx,kind,P in ents:
        if symidx in names: continue
        w=resolved(P)
        if kind==1:                              # R_MIPS_26 jal/j
            addr=(w&0x3ffffff)<<2
        elif kind==3:                            # HI16 -> find paired LO16 same symidx
            hi=w&0xffff; lo=None
            for s2,k2,P2 in ents:
                if k2==2 and s2==symidx: lo=resolved(P2)&0xffff; break
            if lo is None: continue
            addr=(hi<<16)+sext(lo)
        elif kind==2:                            # standalone LO16 (rare)
            addr=sext(w&0xffff)
        else: continue
        nm=classify(addr); names[symidx]=nm; cls[nm.split('_')[0]]+=1
    print(f'resolved {len(names)} symIdx; classes: {dict(cls)}')
    json.dump({str(k):v for k,v in names.items()}, open(a.out,'w'))
    print(f'wrote {a.out}')

if __name__=='__main__':
    main()
