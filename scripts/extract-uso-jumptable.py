#!/usr/bin/env python3
"""Statically extract a USO function's jr jump-table target list from the
module's Data/RoData reloc tables (NO emulator needed for UNCOMPRESSED modules
like bootup.uso). The jump table is N consecutive relocs in DataReloc(3)/
RoDataReloc(4) whose resolved targets land inside the function's text range.

Usage:
  extract-uso-jumptable.py <func_name> --module 0xD9FE28 --vaddr 0x10FEC \
      --size 0x6DC [--symnames scripts/emu-symdump/bootup_uso.symnames.json]
  # add --emit-m2c to also write an m2c-ready .s (labels+jtbl) and run m2c.

Reuses the Kyoto-USO section/reloc format (see uso-reloc-symbolize.py):
  dir at module+0xC, 12-byte entries [flag, type, size]; reloc entry
  [flag, (symIdx<<4)|kind, section_offset]; target = symval(symIdx)+addend
  where addend = the placeholder word in the data section at that offset.
GAME_LIBS lives inside bootup.uso at shim +0x1466C: pass --shim 0x1466C with
the game_libs-local --vaddr (validated: gl_func_0006E224 52-case table extracted,
all targets landed in range). The decoded m2c may need extra cleanup for
register-carrying switches (unset-reg reads) + pointer post-incr (->unk-N).

NOTE the Text section has a leading marker word, so disasm-func.py offsets are
text-data-relative (= vaddr - module_text_base_in_proj); map accordingly.
"""
import argparse, struct, json, subprocess, re, sys
def u32(d,o): return struct.unpack_from('>I',d,o)[0]
SEC=set(range(12))
def walk(d, mod):
    o=mod+0xC; secs={}
    for _ in range(16):
        typ,size=u32(d,o+4),u32(d,o+8)
        if typ not in SEC: break
        secs.setdefault(typ,(o+12,size))
        if typ in (10,11): break
        o+=12+(0 if typ==8 else ((size+3)&~3))
    return secs

def extract(rom, mod, vaddr, size, symnames):
    d=open(rom,'rb').read()
    secs=walk(d,mod)
    syms=json.load(open(symnames)) if symnames else {}
    def symval(si):
        n=syms.get(str(si))
        return int(n[5:],16) if n and n.startswith('func_') else None
    lo,hi=vaddr,vaddr+size
    tables=[]
    for rt,st in ((3,6),(4,7)):
        if rt not in secs or st not in secs: continue
        rdata,rsize=secs[rt]; sdata,ssize=secs[st]
        p=rdata; hits=[]
        while p+12<=rdata+rsize:
            f1=u32(d,p+4); off=u32(d,p+8); si=f1>>4
            sv=symval(si)
            if sv is not None:
                addend=u32(d,sdata+off) if sdata+off+4<=sdata+ssize else 0
                t=sv+addend
                if lo<=t<hi: hits.append((off,t))
            p+=12
        # group consecutive 4-spaced offsets -> a table
        hits.sort()
        i=0
        while i<len(hits):
            j=i
            while j+1<len(hits) and hits[j+1][0]==hits[j][0]+4: j+=1
            tables.append({'sec':('Data' if rt==3 else 'RoData'),
                           'roff':hits[i][0],'n':j-i+1,
                           'targets_vaddr':[h[1] for h in hits[i:j+1]]})
            i=j+1
    return tables

if __name__=='__main__':
    ap=argparse.ArgumentParser()
    ap.add_argument('func'); ap.add_argument('--rom',default='baserom.z64')
    ap.add_argument('--module',required=True); ap.add_argument('--vaddr',required=True)
    ap.add_argument('--size',required=True)
    ap.add_argument('--shim',default='0',help='add to --vaddr; game_libs-in-bootup = 0x1466C')
    ap.add_argument('--symnames',default='scripts/emu-symdump/bootup_uso.symnames.json')
    a=ap.parse_args()
    ts=extract(a.rom,int(a.module,0),int(a.vaddr,0)+int(a.shim,0),int(a.size,0),a.symnames)
    out={'func':a.func,'vaddr':int(a.vaddr,0),'tables':ts}
    print(json.dumps(out,indent=2,default=lambda x:hex(x) if isinstance(x,int) else x))
