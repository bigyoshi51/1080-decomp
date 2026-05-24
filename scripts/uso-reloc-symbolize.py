#!/usr/bin/env python3
"""Symbolize USO .s files using the embedded reloc table.

The Kyoto USO format stores relocations in a custom TextReloc section (NOT the
standard Z64 overlay format). splat disassembles USO text with placeholder
operands (lui/addiu literal 0; jal to whatever offset-0 symbol). This script
reads the real reloc table and rewrites each relocated instruction to reference
a canonical per-symbol name `usosym_<symIdx>`, emitting %hi/%lo/jal so the
assembled .o carries proper R_MIPS_HI16/LO16/26 relocs.

On-disk TextReloc entry (12 bytes), validated against the loader (func_80001ADC
relocator + func_800018F0 un-relocator) and 15543 entries with 0 opcode errors:
  field0 = flag (1; entry0 has 0x08000000 start bit)
  field1 = (symIdx << 4) | (kind & 7)   ->  symIdx = field1>>4, kind = field1&7
  field2 = byte offset into the Text section (== splat project offset)
  kind: 1=R_MIPS_26 (jal/j), 2=LO16 (addiu/lw/sw/lwc1/...), 3=HI16 (lui)

usosym_<symIdx> symbols must be defined (=0) so the assembled bytes equal the
runtime placeholders the ROM stores (lui0/addiu0/jal0). Real human names are a
later drop-in rename once the on-disk Sym name table is decoded.
"""
import argparse, glob, os, re, struct, sys

GPR = ['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7',
       's0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra']
SEC = {0:'Info',1:'Sym',2:'TextReloc',3:'DataReloc',4:'RoDataReloc',5:'Text',
       6:'Data',7:'RoData',8:'Bss',9:'EntrySym',10:'EOF',11:'End'}
# LO16-class load/store opcodes -> mnemonic; FP ones use $f registers
LS = {0x20:'lb',0x21:'lh',0x23:'lw',0x24:'lbu',0x25:'lhu',0x28:'sb',0x29:'sh',
      0x2b:'sw',0x31:'lwc1',0x39:'swc1',0x35:'ldc1',0x3d:'sdc1',0x37:'ldl',0x3f:'sdc2'}
FP_OPS = {0x31,0x39,0x35,0x3d}

def u32(d,o): return struct.unpack_from('>I',d,o)[0]

def walk_dir(d, mod):
    if u32(d,mod) != 0x12345678: return None
    o = mod+0xC; secs={}
    for _ in range(64):
        typ,size = u32(d,o+4),u32(d,o+8)
        if typ in (10,11) or typ not in SEC: break
        secs.setdefault(typ,(o+12,size))
        o += 12 + (0 if typ==8 else ((size+3)&~3))
    return secs

def build_relocmap(d, treloc_data, treloc_size):
    m={}
    o=treloc_data
    while o+12 <= treloc_data+treloc_size:
        f1=u32(d,o+4); off=u32(d,o+8)
        m[off]=(f1>>4, f1&7)
        o+=12
    return m

def reg(w,shift): return GPR[(w>>shift)&0x1f]
def sext16(x): return x-0x10000 if x & 0x8000 else x

LINE_RE = re.compile(r'^(\s*/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s*\*/\s*)(\S.*)$')

def addend_str(sym, addend):
    """Format `usosym_N` or `usosym_N + 0xNN` / `usosym_N - 0xNN`.
    The baked instruction immediate IS the addend (the symbol base = 0 is added
    at runtime). %hi/%lo of (0 + addend) reproduces the original immediate bytes."""
    if addend==0: return sym
    if addend>0:  return f'{sym} + 0x{addend:X}'
    return f'{sym} - 0x{-addend:X}'

def process_file(path, relmap, apply):
    # Pass 1: parse lines, index reloc instructions
    lines=[l for l in open(path)]
    parsed=[]   # (idx, off, word) for reloc lines
    for i,line in enumerate(lines):
        m=LINE_RE.match(line.rstrip('\n'))
        if not m: continue
        off=int(m.group(2),16)
        if off in relmap:
            parsed.append((i,off,int(m.group(3),16)))
    # Pass 2: compute per-reloc addend. Pair HI16(lui $rX) with the nearest forward
    # LO16 (same symIdx, base reg == lui's rt) to get the full combined addend.
    addends={}   # off -> addend
    for k,(i,off,w) in enumerate(parsed):
        symidx,kind=relmap[off]
        if kind==2:  # LO16 standalone default = sign-extended low imm
            addends.setdefault(off, sext16(w & 0xffff))
        elif kind==3:  # HI16: find paired LO16
            rt=(w>>16)&0x1f; hi=w & 0xffff; paired=None
            for (j,off2,w2) in parsed[k+1:k+8]:
                s2,k2=relmap[off2]
                if k2==2 and s2==symidx and ((w2>>21)&0x1f)==rt:
                    paired=w2; lo_off=off2; break
            lo = sext16(paired & 0xffff) if paired is not None else 0
            full=(hi<<16)+lo
            addends[off]=full
            if paired is not None: addends[lo_off]=full   # LO uses same full addend
        # kind 1 (jal/j): addend from the 26-bit field (USO placeholders are 0)
        elif kind==1:
            addends[off]=(w & 0x3ffffff)<<2
    # Pass 3: rewrite
    changed=0
    for i,off,w in parsed:
        symidx,kind=relmap[off]; sym=f'usosym_{symidx}'; op=w>>26
        a=addends.get(off,0); sa=addend_str(sym,a)
        m=LINE_RE.match(lines[i].rstrip('\n')); prefix=m.group(1)
        if kind==1:
            instr=f"{'j' if op==2 else 'jal':<10} {sym}" if a==0 else \
                  f"{'j' if op==2 else 'jal':<10} {sa}"
        elif kind==3:
            instr=f"{'lui':<10} ${reg(w,16)}, %hi({sa})"
        elif kind==2:
            if op==9:
                instr=f"{'addiu':<10} ${reg(w,16)}, ${reg(w,21)}, %lo({sa})"
            else:
                mn=LS.get(op,'addiu')
                rt=f'$f{(w>>16)&0x1f}' if op in FP_OPS else f'${reg(w,16)}'
                instr=f"{mn:<10} {rt}, %lo({sa})(${reg(w,21)})"
        else: continue
        lines[i]=prefix+instr+'\n'; changed+=1
    if apply and changed:
        open(path,'w').write(''.join(lines))
    return changed

def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('segment')                       # e.g. bootup_uso
    ap.add_argument('module', type=lambda x:int(x,0))# ROM offset of module (magic 0x12345678)
    ap.add_argument('--rom', default='baserom.z64')
    ap.add_argument('--asmdir', default=None)
    ap.add_argument('--apply', action='store_true')
    a=ap.parse_args()
    d=open(a.rom,'rb').read()
    secs=walk_dir(d,a.module)
    if not secs or 5 not in secs or 2 not in secs:
        sys.exit(f'no Text/TextReloc at module {a.module:#x}')
    tr_data,tr_size = secs[2]
    relmap = build_relocmap(d,tr_data,tr_size)
    kinds={}
    for _,(_,k) in relmap.items(): kinds[k]=kinds.get(k,0)+1
    syms=sorted({s for s,_ in relmap.values()})
    print(f'{a.segment}: {len(relmap)} relocs, {len(syms)} distinct symbols '
          f'(kinds: {kinds}); usosym range usosym_{syms[0]}..usosym_{syms[-1]}')
    asmdir=a.asmdir or f'asm/nonmatchings/{a.segment}'
    total=0; files=0
    for f in sorted(glob.glob(os.path.join(asmdir,'*.s'))):
        c=process_file(f,relmap,a.apply)
        if c: files+=1; total+=c
    print(f'{"APPLIED" if a.apply else "DRY-RUN"}: {total} instructions in {files} .s files'
          f' would be symbolized')
    # emit usosym definitions list
    if a.apply:
        with open(f'{a.segment}.usosyms.txt','w') as fo:
            for s in syms: fo.write(f'usosym_{s} = 0x00000000;\n')
        print(f'wrote {a.segment}.usosyms.txt ({len(syms)} symbols = 0)')

if __name__=='__main__':
    main()
