#!/usr/bin/env python3
"""Symbolize a game_uso INCLUDE_ASM .s: rewrite its reloc-site placeholder `.word`s
to named mnemonic instructions carrying the REAL target name from game_uso.symnames.

game_uso .s are raw `.word`. At an IMPORT reloc site the word is a placeholder
(`jal 0`=0x0C000000, `lui rt,0`=0x3Cxx0000, `addiu/lw/sw/... rt,rs,0` with imm 0).
Rewriting it to `jal NAME` / `lui rt,%hi(NAME)` / `<op> rt,rs,%lo(NAME)` with NAME
left UNDEFINED assembles to the SAME placeholder bytes PLUS an R_MIPS_26/HI16/LO16
reloc to NAME (validated). Defining NAME=0 in undefined_syms keeps the linked bytes
identical. => real call graph in the disassembly, byte-identical, game_uso.c untouched.

Naming: internal targets -> game_uso_<name> (avoid colliding with bootup's global
func_<off>); imports keep their real cross-module name. Only PLACEHOLDER words
(imm==0) are rewritten; already-baked intra `.word`s (e.g. jal 0xA0) are left as-is.

Emits the rewritten .s to --out (or in place with --apply) and appends the needed
`NAME = 0;` defines to --defs. Prints the (offset,word,name) it changed.

  game-uso-symbolize-s.py --s <file.s> --symnames game_uso.symnames.json --out /tmp/x.s --defs /tmp/defs.txt
"""
import argparse, json, re, struct, sys

def reg(n): return ["zero","at","v0","v1","a0","a1","a2","a3","t0","t1","t2","t3","t4","t5","t6","t7",
                    "s0","s1","s2","s3","s4","s5","s6","s7","t8","t9","k0","k1","gp","sp","fp","ra"][n]
# memory/imm ops by primary opcode -> mnemonic (LO16 reloc)
LO_OPS={0x09:"addiu",0x0D:"ori",0x23:"lw",0x2B:"sw",0x21:"lh",0x25:"lhu",0x20:"lb",0x24:"lbu",
        0x28:"sb",0x29:"sh",0x31:"lwc1",0x39:"swc1",0x35:"ldc1",0x3D:"sdc1"}

def localname(name):
    # internal func_/D_/RO_ -> game_uso-prefixed (avoid bootup global-namespace clash)
    if re.match(r'(func|D|RO)_[0-9A-Fa-f]+$', name): return "game_uso_"+name
    return name   # import_<addr> / real cross-module names stay

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--s', required=True); ap.add_argument('--symnames', required=True)
    ap.add_argument('--out'); ap.add_argument('--defs'); ap.add_argument('--apply', action='store_true')
    a=ap.parse_args()
    sym=json.load(open(a.symnames)); names=sym.get('names',sym)
    lines=open(a.s).read().splitlines(); out=[]; changed=[]; defs=set()
    for l in lines:
        m=re.search(r'/\* ([0-9A-Fa-f]{6}) ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s+\.word 0x([0-9A-Fa-f]{8})', l)
        if not m: out.append(l); continue
        modoff=int(m.group(1),16); w=int(m.group(4),16)
        key=hex(modoff); nm=names.get(key)
        if nm is None or nm.startswith('unpaired'): out.append(l); continue
        op=w>>26; rt=(w>>16)&0x1f; rs=(w>>21)&0x1f; imm=w&0xffff
        ins=None; name=localname(nm)
        if op==3 and (w&0x3ffffff)==0:                 # jal 0 placeholder
            ins=f"jal {name}"
        elif op==0x0F and imm==0:                      # lui rt,0
            ins=f"lui ${reg(rt)}, %hi({name})"
        elif op in LO_OPS and imm==0:                  # <memop/addiu> ...,0
            mn=LO_OPS[op]
            if op in (0x09,0x0D): ins=f"{mn} ${reg(rt)}, ${reg(rs)}, %lo({name})"
            else:                 ins=f"{mn} ${reg(rt)}, %lo({name})(${reg(rs)})"
        if ins is None: out.append(l); continue        # baked / non-placeholder -> leave
        indent=l[:len(l)-len(l.lstrip())]
        out.append(f"{indent}{ins}   /* {m.group(1)} {m.group(3)} -> {name} */")
        changed.append((modoff,w,name)); defs.add(name)
    txt="\n".join(out)+"\n"
    dst=a.s if a.apply else (a.out or "/dev/stdout")
    open(dst,"w").write(txt)
    if a.defs:
        with open(a.defs,"a") as fp:
            for n in sorted(defs): fp.write(f"{n} = 0;\n")
    for o,w,n in changed: print(f"  {o:#x}: {w:#010x} -> {n}", file=sys.stderr)
    print(f"changed {len(changed)} reloc sites, {len(defs)} defines -> {dst}", file=sys.stderr)

if __name__=='__main__':
    main()
