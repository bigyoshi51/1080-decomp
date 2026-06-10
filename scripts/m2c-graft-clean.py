#!/usr/bin/env python3
"""Clean raw m2c output into IDO-compilable C (the graft checklist,
docs/TOOLING_DECOMP items 1-16). Usage:
    m2c-graft-clean.py <m2c_output.c> <func_name> [--self-recursive]
Prints cleaned body to stdout; extern lines for recovered callees to stderr.
Order matters (item 14): NULL-calls before NULL->0 before *0 derefs."""
import re, sys

def fix_chain(b):
    m = re.search(r'\)->unk([0-9A-Fa-f]+)', b)
    if not m: return b, False
    end = m.start()+1; depth = 0; j = end-1
    while j >= 0:
        if b[j] == ')': depth += 1
        elif b[j] == '(':
            depth -= 1
            if depth == 0: break
        j -= 1
    k = j
    mm = re.search(r'(\*\(s32 \*\)|\*\(f32 \*\)|\*\(char \*\*\))$', b[max(0,k-12):k])
    if mm: k -= len(mm.group(1))
    rep = f'*(s32 *)((char *)({b[k:end]}) + 0x{int(m.group(1),16):X})'
    return b[:k]+rep+b[end+len(m.group(0))-1:], True

def clean(b, fn, self_recursive=False):
    b = re.sub(r'(?<![\w.])(?:NULL|0)\(', 'func_00000000(', b)            # 1
    b = b.replace('NULL','0')                                              # 14: before *0
    b = b.replace('?32','s32')
    b = re.sub(r'^(\s+)\? \*', r'\1char *', b, flags=re.M)
    b = re.sub(r'^(\s+)\? ', r'\1s32 ', b, flags=re.M)
    b = re.sub(r'\(([\w? ]+)\(\*\)\(([^)]*)\)\)0x([0-9A-Fa-f]+)\(',        # 13
               lambda m: f'{fn.rsplit("_",1)[0]}_{int(m.group(3),16):08X}('
               if False else f'gl_func_{int(m.group(3),16):08X}(', b)
    b = re.sub(r'([A-Za-z_][A-Za-z0-9_]*)->unk-([0-9A-Fa-f]+)',            # 2 neg
               lambda m: f'*(s32 *)((char *)({m.group(1)}) - 0x{int(m.group(2),16):X})', b)
    b = re.sub(r'([A-Za-z_][A-Za-z0-9_]*)->unk([0-9A-Fa-f]+)',             # 2
               lambda m: f'*(s32 *)((char *)({m.group(1)}) + 0x{int(m.group(2),16):X})', b)
    ch = True
    while ch: b, ch = fix_chain(b)                                          # 9
    b = re.sub(r'\bx[0-9A-Fa-f]{3,}\b(?=\) )', lambda m: m.group(0), b)    # 2-trap detect only
    b = re.sub(r'([A-Za-z_]\w*)\.unk([0-9A-Fa-f]+)',                        # 6
               lambda m: f'*((s32 *)&{m.group(1)} + {int(m.group(2),16)//4})', b)
    b = re.sub(r'\*\((f32|s32|u8|u16) \*\)0x([0-9A-Fa-f]+)',               # 3
               lambda m: f'*({m.group(1)} *)((char *)&D_00000000 + 0x{m.group(2)})', b)
    b = re.sub(r'(?<![\w])\*0(?![\w.x])', '*(s32 *)((char *)&D_00000000 + 0)', b)
    b = re.sub(r'\*\(void \*\)0x([0-9A-Fa-f]+)',
               lambda m: f'*(s32 *)((char *)&D_00000000 + 0x{m.group(1)})', b)
    b = re.sub(r'\*\(void \*\)([0-9]+)',
               lambda m: f'*(s32 *)((char *)&D_00000000 + {m.group(1)})', b)
    b = re.sub(r'^(\s+)void \*', r'\1char *', b, flags=re.M)               # 4
    b = re.sub(r'\*\(s32 \*\)\(([^;]+)\) = \(f32\)', r'*(f32 *)(\1) = (f32)', b)  # 5
    b = re.sub(r'M2C_ERROR\*\(s32 \*\)\(\(char \*\)\(\(/\* Read from unset register \$(\w+) \*/\)\) \+ (0x[0-9A-Fa-f]+)\)',
               lambda m: f'*(s32 *)((char *)&D_00000000 + {m.group(2)}) /* M2C unset ${m.group(1)} */', b)
    b = re.sub(r'\*M2C_ERROR\(/\* Read from unset register \$(\w+) \*/\)', # 15
               lambda m: f'*(s32 *)((char *)&D_00000000 + 0) /* M2C unset ${m.group(1)} */', b)
    b = re.sub(r'M2C_ERROR\(/\* Read from unset register \$(\w+) \*/\)',
               lambda m: f'0 /* M2C unset ${m.group(1)} */', b)
    b = re.sub(rf'((?:void|s32|int) \*?){fn}\(void \*arg0', rf'\g<1>{fn}(char *arg0', b, count=1)
    # all remaining void* args in the signature -> char* (IDO: no void* arith)
    msig = re.search(rf'{fn}\(([^)]*)\)\s*{{', b)
    if msig:
        fixed = msig.group(1).replace('void *', 'char *')
        b = b[:msig.start(1)] + fixed + b[msig.end(1):]
    # missing sp decls + arrays (6/3)
    decl = set(re.findall(r'^\s+(?:[suf]32|u8|u16|char) \*?\*?(sp[0-9A-Fa-f]+)', b, re.M))
    used = set(re.findall(r'\b(sp[0-9A-Fa-f]+)\b', b))
    arrs = set(re.findall(r'&?(sp[0-9A-Fa-f]+)\[', b))
    missing = sorted(used-decl)
    if missing:
        j = b.index('\n', b.index('{'))+1
        parts = [f's32 {v}[16];' if v in arrs else f'f32 {v};' for v in missing]
        b = b[:j]+'    '+' '.join(parts)+'\n'+b[j:]
    for v in (arrs - set(missing)):
        b = re.sub(rf'(^\s+)f32 {v};', rf'\1s32 {v}[16];', b, flags=re.M)
    callees = sorted(set(int(x,16) for x in re.findall(r'gl_func_([0-9A-F]{8})\(', b)) - {0})
    if self_recursive and fn.startswith('gl_func_'):
        callees = [c for c in callees if f'gl_func_{c:08X}' != fn]
    return b, callees

if __name__ == '__main__':
    src = open(sys.argv[1]).read()
    fn = sys.argv[2]
    i = src.find(fn)
    i = src.rfind('\n', 0, i)+1 if i > 0 and '\n' in src[:i] else 0
    body, callees = clean(src[i:], fn, '--self-recursive' in sys.argv)
    sys.stdout.write(body)
    for c in callees:
        sys.stderr.write(f'extern int gl_func_{c:08X}();\n')
