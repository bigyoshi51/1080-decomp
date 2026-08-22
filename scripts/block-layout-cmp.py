#!/usr/bin/env python3
"""Compare basic-block LAYOUT of a function: build/non_matching vs expected.

Usage: block-layout-cmp.py <unit-rel-path e.g. src/game_libs/game_libs_post0b.c.o> <funcname>

Blocks are branch-target-delimited regions fingerprinted by mnemonic-sequence md5,
greedy-matched target->build; a mostly-matched but out-of-order mapping = the NM body
has the right CONTENT in the wrong BLOCK ORDER (objdiff charges moved blocks
delete+insert 200/insn, understating fuzzy 2x/moved-insn, clamping to 0.0 past ~50%).
See docs/MATCHING_WORKFLOW.md "objdiff-fuzzy-hard-zero-nm-body" -- note the 2026-08-22
closure: the [20,60) band was swept with this tool, 55470 was the only hit, and fixing
layout via inline nesting broke register agreement (worse score). Diagnostic, not a vein.
"""
import subprocess, sys, re, hashlib

unit, fn = sys.argv[1], sys.argv[2]
import os
root = os.getcwd()

def disas(obj, fn):
    out = subprocess.run(["mips-linux-gnu-objdump","-d","-j",".text",obj],
                         capture_output=True, text=True).stdout
    lines = out.splitlines()
    insns = []
    active = False
    for L in lines:
        m = re.match(r'^[0-9a-f]+ <(.+)>:$', L)
        if m:
            active = (m.group(1) == fn)
            continue
        if not active: continue
        m = re.match(r'^\s+([0-9a-f]+):\s+[0-9a-f]{8}\s+(\S+)\s*(.*)$', L)
        if m:
            addr = int(m.group(1),16); mn = m.group(2); ops = m.group(3)
            insns.append((addr, mn, ops))
    return insns

BR = re.compile(r'^(b|beq|bne|blez|bgtz|bltz|bgez|beql|bnel|blezl|bgtzl|bltzl|bgezl|bc1t|bc1f|bc1tl|bc1fl|j|jal|jr|jalr|bltzal|bgezal)$')

def blocks(insns):
    if not insns: return []
    base = insns[0][0]
    leaders = {base}
    n = len(insns)
    for i,(a,mn,ops) in enumerate(insns):
        if BR.match(mn):
            # branch target
            m = re.search(r'([0-9a-f]+)\s+<', ops)
            if m and mn not in ('jr','jalr','jal','j'):
                t = int(m.group(1),16)
                if insns[0][0] <= t <= insns[-1][0]: leaders.add(t)
            # fallthrough after delay slot
            if i+2 < n and mn not in ('jal','jalr','bltzal','bgezal'):
                leaders.add(insns[i+2][0])
    leaders = sorted(leaders)
    blks = []
    li = 0
    for k,start in enumerate(leaders):
        end = leaders[k+1] if k+1 < len(leaders) else insns[-1][0]+4
        body = [x for x in insns if start <= x[0] < end]
        blks.append((start-base, body))
    return blks

def fp(body):
    # mnemonic-sequence fingerprint (ignore operands for move detection)
    s = ",".join(mn for _,mn,_ in body)
    h = hashlib.md5(s.encode()).hexdigest()[:6]
    return h, len(body), body[0][1] if body else ""

exp = disas(f"{root}/expected/{unit}", fn)
bld = disas(f"{root}/build/non_matching/{unit.replace('.c.o','.c')}.o".replace('.c.o.o','.c.o'), fn)
if not bld:
    bld = disas(f"{root}/build/non_matching/{unit}", fn)

eb = blocks(exp); bb = blocks(bld)
efps = [fp(b) for _,b in eb]; bfps = [fp(b) for _,b in bb]
bmap = {}
for i,(h,l,m0) in enumerate(bfps): bmap.setdefault(h,[]).append(i)

print(f"target: {len(exp)} insns, {len(eb)} blocks | build: {len(bld)} insns, {len(bb)} blocks")
print(f"{'T#':>3} {'off':>6} {'len':>4} {'hash':6} {'first':10} -> build block#")
used=set()
for i,((off,body),(h,l,m0)) in enumerate(zip(eb,efps)):
    cands = [j for j in bmap.get(h,[]) if j not in used]
    j = cands[0] if cands else None
    if j is not None: used.add(j)
    print(f"{i:>3} {off:>#6x} {l:>4} {h:6} {m0:10} -> {j if j is not None else 'NONE'}")
print("build blocks unmatched:", [j for j in range(len(bb)) if j not in used])
