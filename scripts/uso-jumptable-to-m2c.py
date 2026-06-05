#!/usr/bin/env python3
"""Like uso-objdump-to-m2c.py but for JUMPTABLE functions: injects the jr
jump-table (extracted statically by extract-uso-jumptable.py) as a jtbl_<fn>
.rodata symbol + .L labels at the case targets, so m2c can resolve the
computed `jr` into a switch. Then feed the output to m2c and uso-auto-lift.py.

Usage: uso-jumptable-to-m2c.py <matching.c.o> <func> <oo_off_hex> \
         --vaddr 0xVADDR --size 0xSIZE [--module 0xD9FE28 --shim 0x1466C]
  (game_libs lives in bootup.uso: --module 0xD9FE28 --shim 0x1466C)
  oo_off_hex = the func's address in `objdump -d <matching.c.o>`.

CAVEAT: m2c rejects a label landing in a branch DELAY SLOT
("Label .LX refers to a delay slot") — that's a separate control-flow quirk,
not fixable here; skip such functions or hand-patch the .s.
"""
import subprocess,json,re,sys,argparse
ap=argparse.ArgumentParser()
ap.add_argument('obj'); ap.add_argument('func'); ap.add_argument('ooff')
ap.add_argument('--vaddr',required=True); ap.add_argument('--size',required=True)
ap.add_argument('--module',default='0xD9FE28'); ap.add_argument('--shim',default='0x1466C')
a=ap.parse_args()
fn=a.func; ooff=int(a.ooff,16); modbase=int(a.vaddr,16)+int(a.shim,16)
jt=json.loads(subprocess.run(["python3","scripts/extract-uso-jumptable.py",fn,"--module",a.module,
    "--vaddr",a.vaddr,"--size",a.size,"--shim",a.shim],capture_output=True,text=True).stdout)
labaddrs=[]
for tbl in jt['tables']:
    labaddrs+= [ooff+(t-modbase) for t in tbl['targets_vaddr']]
out=subprocess.run(["mips-linux-gnu-objdump","-dr",a.obj],capture_output=True,text=True).stdout
cap=False; insns=[]
for ln in out.split('\n'):
    if re.match(rf'^[0-9a-f]+ <{fn}>:',ln): cap=True; continue
    if cap:
        if re.match(r'^[0-9a-f]+ <',ln): break
        m=re.match(r'^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)',ln)
        if m: insns.append((int(m.group(1),16),m.group(3).strip()))
labset=set(labaddrs)
for x,ins in insns:
    mb=re.search(rf'([0-9a-f]+) <{fn}\+',ins)
    if mb: labset.add(int(mb.group(1),16))
GPR=r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra)\b'
asm=['.set noat','.set noreorder','','.section .text','',f'glabel {fn}']
for x,ins in insns:
    if x in labset: asm.append(f'.L{x:x}:')
    s=ins
    mb=re.search(rf'[0-9a-f]+ <{fn}\+0x[0-9a-f]+>',s)
    if mb: s=re.sub(rf'[0-9a-f]+ <{fn}\+0x[0-9a-f]+>', f'.L{int(mb.group(0).split()[0],16):x}', s)
    mj=re.search(r'\b(jal|j)\s+([0-9a-f]+)\s+<(\w+)(\+0x[0-9a-f]+)?>',s)
    if mj:
        tgt=mj.group(3) if (mj.group(2)=='0' and not mj.group(4)) else f'func_{mj.group(2)}'
        s=re.sub(r'\b(jal|j)\s+[0-9a-f]+\s+<[\w+x0-9a-f]+>', f'{mj.group(1)} {tgt}', s)
    s=re.sub(r'\s+<[\w+x0-9a-f]+>','',s); s=re.sub(r'\bs8\b','fp',s); s=re.sub(GPR, r'$\1', s)
    s=re.sub(r'lw\t\$t9,\d+\(\$at\)', f'lw\t$t9,%lo(jtbl_{fn})($at)', s)
    asm.append('/* */ '+s)
txt='\n'.join(asm).replace(f'lui\t$at,0x0\n/* */ addu\t$at,$at,$t9', f'lui\t$at,%hi(jtbl_{fn})\n/* */ addu\t$at,$at,$t9')
txt+=f'\n\n.section .rodata\nglabel jtbl_{fn}\n'+''.join(f'.word .L{a:x}\n' for a in labaddrs)
print(txt)
