#!/usr/bin/env python3
"""Convert a USO function's mnemonic asm (from objdump -dr of the matching .o)
into an m2c-parseable .s, so m2c can decompile USO functions whose
asm/nonmatchings/*.s is raw .word (which m2c can't parse).

Usage: uso-objdump-to-m2c.py <matching.o> <func_name>  > func.s
Then:  uv run m2c --target mips-ido-c func.s
"""
import subprocess,re,sys
obj,fn=sys.argv[1],sys.argv[2]
out=subprocess.run(["mips-linux-gnu-objdump","-dr",obj],capture_output=True,text=True).stdout
cap=False; body=[]
for ln in out.split('\n'):
    if re.match(rf'^[0-9a-f]+ <{fn}>:',ln): cap=True; continue
    if cap:
        if re.match(r'^[0-9a-f]+ <',ln): break
        m=re.match(r'^\s*([0-9a-f]+):\s+([0-9a-f]{8})\s+(.*)$',ln)
        if m: body.append((m.group(1),m.group(3).strip()))
labels={re.search(rf'\b([0-9a-f]+) <{fn}\+',b[1]).group(1) for b in body if re.search(rf'\b[0-9a-f]+ <{fn}\+',b[1])}
asm=['.set noat','.set noreorder','',f'glabel {fn}']
GPR=r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra)\b'
for addr,insn in body:
    if addr in labels: asm.append(f'.L{addr}:')
    s=insn
    # local branch target -> .Laddr
    mb=re.search(rf'([0-9a-f]+) <{fn}\+0x[0-9a-f]+>',s)
    if mb: s=re.sub(rf'[0-9a-f]+ <{fn}\+0x[0-9a-f]+>', f'.L{mb.group(1)}', s)
    # jal/j target -> symbol
    mj=re.search(r'\b(jal|j)\s+([0-9a-f]+)\s+<(\w+)(\+0x[0-9a-f]+)?>',s)
    if mj:
        tgt = mj.group(3) if (mj.group(2)=='0' and not mj.group(4)) else f'func_{mj.group(2)}'
        s=re.sub(r'\b(jal|j)\s+[0-9a-f]+\s+<[\w+x0-9a-f]+>', f'{mj.group(1)} {tgt}', s)
    s=re.sub(r'\s+<[\w+x0-9a-f]+>','',s)
    s=re.sub(r'\bs8\b','fp',s)
    s=re.sub(GPR, r'$\1', s)
    asm.append('/* */ '+s)
print('\n'.join(asm))
