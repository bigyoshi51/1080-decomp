#!/usr/bin/env python3
"""Auto-apply the reloc-blind cleanup recipe to an m2c decode of a USO function.
Usage: uso-auto-lift.py <matching.c.o> <func>  > body.c
Emits a cleaned C body (splice over the stub). Hand-fix residuals:
  - counters wrongly retyped char* (vars compared to a count) -> revert to s32
  - any base-0 computed pointers m2c missed (add `g +`)
"""
import subprocess,re,sys,os
obj,fn=sys.argv[1],sys.argv[2]
# 1. width map from asm (s6/base-reg-relative loads/stores)
out=subprocess.run(["mips-linux-gnu-objdump","-d",obj],capture_output=True,text=True).stdout
cap=False; wmap={}
for ln in out.split('\n'):
    if re.match(rf'^[0-9a-f]+ <{fn}>:',ln): cap=True; continue
    if cap:
        if re.match(r'^[0-9a-f]+ <',ln): break
        m=re.match(r'^\s*[0-9a-f]+:\s+[0-9a-f]{8}\s+(\w+)\s+\$?[\w$]+,(-?\d+)\(\$?(s[0-9]|fp|gp)\)',ln)
        if m:
            op,off=m.group(1),int(m.group(2))
            t={'sw':'s32','lw':'s32','sh':'s16','lh':'s16','lhu':'u16','sb':'u8','lb':'s8','lbu':'u8','swc1':'f32','lwc1':'f32'}.get(op)
            if t and off>=0: wmap.setdefault(off,t)
# 2. m2c decode
here=os.path.dirname(os.path.abspath(__file__))
s=subprocess.run(["python3",f"{here}/uso-objdump-to-m2c.py",obj,fn],capture_output=True,text=True).stdout
open('/tmp/_al.s','w').write(s)
m2c=subprocess.run(["uv","run","m2c","--target","mips-ido-c","/tmp/_al.s"],capture_output=True,text=True).stdout
if 'failure' in m2c[:200] or 'Unable' in m2c[:200]:
    sys.stderr.write("m2c failed (jumptable?)\n"); sys.exit(1)
i=m2c.index(f'void {fn}') if f'void {fn}' in m2c else m2c.index(fn+'(')
# back up to return type line
i=m2c.rfind('\n',0,i)+1
body=m2c[i:]
# 3. retype void* -> char*
body=re.sub(r'\bvoid \*(\w+)', r'char *\1', body)
# 4. insert g
body=body.replace('{\n','{\n    char *g = (char *)&D_00000000;\n',1)
# 5. typed field: (CAST) VAR->unkOFF
def tf(m):
    c,v,off=m.group(1),m.group(2),m.group(3); sign='-' if off.startswith('-') else '+'; o=off.lstrip('-')
    return f'(*({c} *)({v} {sign} 0x{o}))'
body=re.sub(r'\(([su]\d+|f32) \*?\)\s*(\w+)->unk(-?[0-9A-Fa-f]+)', tf, body)
def bf(m):
    v,off=m.group(1),m.group(2); sign='-' if off.startswith('-') else '+'; o=off.lstrip('-')
    return f'(*(s32 *)({v} {sign} 0x{o}))'
body=re.sub(r'\b(\w+)->unk(-?[0-9A-Fa-f]+)', bf, body)
# 6. absolute globals with width
def ag(m):
    t,a=m.group(1),int(m.group(2),16); return f'*({wmap.get(a,t)} *)(g + 0x{a:X})'
body=re.sub(r'\*\(([su]\d+|f32) \*\)(0x[0-9A-Fa-f]+)', ag, body)
body=re.sub(r'\*\(([su]\d+|f32) \*\)(\d+)\b', lambda m:f'*({m.group(1)} *)(g + {m.group(2)})', body)
body=re.sub(r'\*\(void \*\)(0x[0-9A-Fa-f]+|\d+)', r'*(s32 *)(g + \1)', body)
# extra base-loss: *(T**)0xNNN -> *(T**)(g + 0xNNN); *(T*)(0xNNN + ...) bare-literal base
body=re.sub(r'\*\(([su]\d+|void) \*\*\)(0x[0-9A-Fa-f]+)', r'*(\1 **)(g + \2)', body)
body=re.sub(r'\*\(([su]\d+|f32) \*\)\((0x[0-9A-Fa-f]+) \+', r'*(\1 *)(g + \2 +', body)
# m2c (bitwise void *) on a float -> reinterpret bits
body=re.sub(r'\(bitwise void \*\) (\w+)', r'(*(s32 *)&\1)', body)
# (void *)-1 sentinel -> -1 (int handle fields); double-deref pointer chain
body=body.replace('(void *)-1','-1')
body=re.sub(r'\*\(\*\((s32) \*\)', r'*(\1 *)(*(\1 *)', body)
# *NULL = deref of addr 0 = &D base
body=re.sub(r'\*NULL', r'(*(s32 *)g)', body)
# **(s32 *)(EXPR) pointer-chain
body=re.sub(r'\*\*\((s32) \*\)(\([^;\n]*?\))', r'*(\1 *)(*(\1 *)\2)', body)
# parenthesized-base struct fields: (EXPR)->unkN  (backward-scan)
def _pf(s):
    while True:
        m=re.search(r'->unk(-?[0-9A-Fa-f]+)', s)
        if not m: break
        off=m.group(1); end=m.start()
        if s[end-1]==')':
            d=0; i=end-1
            while i>=0:
                if s[i]==')': d+=1
                elif s[i]=='(':
                    d-=1
                    if d==0: break
                i-=1
            base=s[i:end]
        else:
            j=end
            while j>0 and (s[j-1].isalnum() or s[j-1]=='_'): j-=1
            base=s[j:end]; i=j
        sign='-' if off.startswith('-') else '+'; o=off.lstrip('-')
        s=s[:i]+f'(*(s32 *)((char *){base} {sign} 0x{o}))'+s[m.end():]
    return s
body=_pf(body)
# 7. base-0 ptr inits & bounds
body=re.sub(r'= NULL;', '= g;', body)
body=re.sub(r'= \(void \*\)(0x[0-9A-Fa-f]+|\d+);', r'= g + \1;', body)
body=re.sub(r'!= \(void \*\)(0x[0-9A-Fa-f]+|\d+)\)', r'!= (g + \1))', body)
# 8. cfc1 float-to-int blocks -> (s32) cast (scan & replace through matching brace)
bl=body.split('\n'); o=[]; i=0
while i<len(bl):
    if 'M2C_ERROR(/* cfc1 */) & 0x78) {' in bl[i] and bl[i].strip().startswith('if'):
        ind=bl[i][:len(bl[i])-len(bl[i].lstrip())]
        var=None
        for j in range(i,min(i+12,len(bl))):
            m=re.search(r'(\w+) = \(s32\) (\w+);', bl[j])
            if m: var=(m.group(1),m.group(2)); break
        d=0; k=i
        while k<len(bl):
            d+=bl[k].count('{')-bl[k].count('}')
            if d==0 and k>i: break
            k+=1
        if var: o.append(f'{ind}{var[0]} = (s32) {var[1]};')
        i=k+1; continue
    o.append(bl[i]); i+=1
body='\n'.join(o)
# 9. m2c `?`-typed stack structs -> s32[4] (size guess; hand-fix if frame mismatches)
body=re.sub(r'^(\s*)\? (sp\w+);', r'\1s32 \2[4];', body, flags=re.M)
print('extern char D_00000000;')
# emit extern decls for called funcs
for c in sorted(set(re.findall(r'\b(gl_func_[0-9A-Fa-f]+|game_\w+_func_[0-9A-Fa-f]+|func_[0-9a-f]+)\s*\(', body))):
    if c!=fn: print(f'extern int {c}();')
print(body)
