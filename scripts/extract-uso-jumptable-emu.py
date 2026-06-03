#!/usr/bin/env python3
"""Extract a USO function's jr jump-table targets from an EMULATOR RDRAM dump.

For COMPRESSED/blocked modules (timproc, game_uso) only a stub is in the ROM, so
the static reloc-table path (extract-uso-jumptable.py) can't see the table. Instead
dump RDRAM after the module is loaded+relocated (scripts/emu-symdump/uso-emu-dump.py)
and read the RELOCATED table directly: each entry is an absolute KSEG text address,
so target_text_offset = dump_word - ram_base, where ram_base = 0x80000000 | (textbase-4)
(the -4 skips the Text section's leading marker word). found.json from uso-emu-dump
gives `textbase` (phys). Validated on bootup func_00010FEC: the 9 entries resolve to
the exact offsets AND the absolute-stored last entry resolves cleanly (0x115b8),
matching the static path.

The jump table = a run of >=N consecutive dump words whose (word - ram_base) all land
in the target function's [vaddr, vaddr+size) text range.

Usage:
  uso-emu-dump.py ... --out /tmp/rdram.bin --found /tmp/found.json   # produce dump
  extract-uso-jumptable-emu.py <func> --dump /tmp/rdram.bin --found /tmp/found.json \
      --vaddr 0x<proj_off> --size 0x<sz>   # (proj_off = func's module text offset)
"""
import argparse, struct, json
def u32(d,o): return struct.unpack_from('>I',d,o)[0]

def extract(dump, textbase, vaddr, size):
    d=open(dump,'rb').read()
    ram_base=0x80000000 | (textbase-4)
    lo,hi=ram_base+vaddr, ram_base+vaddr+size
    hits=[]
    for o in range(0, len(d)-3, 4):
        w=u32(d,o)
        if lo<=w<hi: hits.append((o, w-ram_base))
    # group consecutive dump offsets (4 apart) into tables
    tables=[]; i=0
    while i<len(hits):
        j=i
        while j+1<len(hits) and hits[j+1][0]==hits[j][0]+4: j+=1
        if j-i+1>=4:
            tables.append({'dump_off':hits[i][0],'n':j-i+1,
                           'targets_vaddr':[h[1] for h in hits[i:j+1]]})
        i=j+1
    return tables, ram_base

if __name__=='__main__':
    ap=argparse.ArgumentParser()
    ap.add_argument('func'); ap.add_argument('--dump',required=True)
    ap.add_argument('--found',required=True)
    ap.add_argument('--vaddr',required=True); ap.add_argument('--size',required=True)
    a=ap.parse_args()
    tb=json.load(open(a.found))['textbase']
    ts,rb=extract(a.dump,tb,int(a.vaddr,0),int(a.size,0))
    print(json.dumps({'func':a.func,'ram_base':hex(rb),'tables':ts},indent=2,
                     default=lambda x:hex(x) if isinstance(x,int) else x))
