#!/usr/bin/env python3
"""Metadata-only ELF32-BE .o edit for hoisted-head merges of a TRACKED expected/ baseline:
delete the retired successor symbols (FUNC + .NON_MATCHING twin), resize the head symbol,
renumber reloc symbol indices. .text and the reloc listing stay byte-identical -- verify with
objcopy -O binary --only-section=.text + objdump -r before installing. Use when neither
strip+EXPECTED_BASELINE=1 route reproduces the tracked .text (timproc b1/b3: donor-spliced,
baked, 14 injected relocs). See docs/MATCHING_WORKFLOW.md#orphan-sweep-agent-c-25th-h2hproc-timproc.
Usage: elf-symtab-merge-orphan.py <in.o> <out.o> <dead1,dead2,...> <head=newsize>
"""
import struct, sys
src, dst = sys.argv[1], sys.argv[2]
delete = set(sys.argv[3].split(',')); resize_name, resize_val = sys.argv[4].split('='); resize_val=int(resize_val,0)
d = bytearray(open(src,'rb').read())
assert d[:4]==b'\x7fELF' and d[5]==2, 'ELF32 big-endian expected'
e_shoff = struct.unpack_from('>I', d, 0x20)[0]; e_shentsize, e_shnum, e_shstrndx = struct.unpack_from('>HHH', d, 0x2E)
shdrs=[]
for i in range(e_shnum):
    o=e_shoff+i*e_shentsize
    shdrs.append(list(struct.unpack_from('>IIIIIIIIII', d, o)))
shstr = shdrs[e_shstrndx]
def name(off, tab): 
    s=tab[4]+off; e=d.index(b'\0', s); return d[s:e].decode()
secnames=[name(sh[0], shstr) for sh in shdrs]
symtab_i = secnames.index('.symtab'); strtab = shdrs[shdrs[symtab_i][6]]
st=shdrs[symtab_i]; nsym=st[5]//16
syms=[list(struct.unpack_from('>IIIBBH', d, st[4]+i*16)) for i in range(nsym)]
names=[name(s[0], strtab) for s in syms]
del_idx=[i for i,n in enumerate(names) if n in delete]
print('deleting', [(i,names[i],syms[i][1],syms[i][2]) for i in del_idx])
assert len(del_idx)==len(delete), (del_idx, delete)
for i,n in enumerate(names):
    if n==resize_name or n==resize_name+'.NON_MATCHING':
        print('resize', i, n, syms[i][2], '->', resize_val); syms[i][2]=resize_val
# index remap
remap={}; new=[]
for i,s in enumerate(syms):
    if i in del_idx: continue
    remap[i]=len(new); new.append(s)
# renumber relocs
for si,sh in enumerate(shdrs):
    if sh[1] in (4,9) and sh[6]==symtab_i:  # SHT_RELA/SHT_REL linked to symtab
        ent=sh[9]; n=sh[5]//ent
        for k in range(n):
            o=sh[4]+k*ent; r_off, r_info = struct.unpack_from('>II', d, o)
            s_idx=r_info>>8; t=r_info&0xFF
            assert s_idx not in del_idx, ('reloc refs deleted symbol', secnames[si], hex(r_off))
            struct.pack_into('>II', d, o, r_off, (remap[s_idx]<<8)|t)
# rewrite symtab in place (shrink), pad tail with zeros
for i,s in enumerate(new):
    struct.pack_into('>IIIBBH', d, st[4]+i*16, *s)
tail = st[4]+len(new)*16
d[tail:st[4]+nsym*16] = b'\0'*((nsym-len(new))*16)
st[5]=len(new)*16
# sh_info = index of first non-local: adjust if deleted locals (none expected)
first_nonlocal = next(i for i,s in enumerate(new) if (s[3]>>4)!=0)
st[7]=first_nonlocal
struct.pack_into('>IIIIIIIIII', d, e_shoff+symtab_i*e_shentsize, *st)
open(dst,'wb').write(d); print('wrote', dst, 'syms', nsym, '->', len(new))
