"""Lift an m2c decode of a NON-jumptable (or jumptable-injected) USO control-flow
function into a compilable NON_MATCHING body. Mechanizes the recipe in
docs/MATCHING_WORKFLOW.md: drop m2c ?-typed forward-decls + jtbl stubs, convert
X->unkN chains to FW(X,0xN), type sp<H> stack scratch as a function-unique Q_<suf>
struct (siblings folded to .unk4/8/C), cast the void-returning placeholder via a
function-unique GP_<suf>, void*->char* for IDO pointer arithmetic, NULL->0,
*expr->*(int*)(expr) for m2c lost-base reads, neutralize bitwise reinterprets via
(int), and auto-declare/dedup aliased-stack locals. Function-unique typedef names
avoid Q/GP clashes between multiple lifted functions in one .c file.

NOT for: FP-vector functions (int typing regresses them to ~0%; see docs FP
LIMITATION) or register-carrying switches (grep m2c for "Read from unset register").

Usage: lift-uso-controlflow.py <FN> <PLACEHOLDER_FN> <m2c_in.c> <body_out.c>
Then splice body_out between the function's #ifdef NON_MATCHING and #else.
Validated: timproc_uso_b5_func_00000778 (4.5->68.9%), func_00007E34 (11->64.8%).
"""
import re, sys
# usage: liftcf.py <FN> <PH> <in.c> <out.c>
FN, PH, INP, OUT = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
suf = FN.split("_")[-1]              # unique tag per function
QT, GT = "Q_"+suf, "GP_"+suf        # unique struct + cast typedef names
c = open(INP).read()

# drop m2c '? name(...); /* extern|static */' forward-decls and jtbl stubs (whitespace-tolerant)
# m2c forward-decls: drop '/* static */' (jtbl stubs); rewrite '/* extern */'
# callee decls to K&R 'extern int name();' (keeps symbol, accepts any argc,
# avoids strict-prototype arg-count mismatch and cast-mangling)
c = re.sub(r'^.*?([A-Za-z_]\w*)\s*\([^;]*\);\s*/\* extern \*/.*$',
           r'extern int \1();', c, flags=re.M)
c = re.sub(r'^.*/\* static \*/.*\n', '', c, flags=re.M)
c = re.sub(r'^\?\s.*\n', '', c, flags=re.M)

# arrows X->unkN -> FW(X,0xN), balanced operand
def conv_arrows(s):
    while True:
        i = s.find('->unk')
        if i < 0: break
        j = i+5; k = j
        while k < len(s) and s[k] in '0123456789ABCDEFabcdef': k += 1
        off = s[j:k]; p = i-1
        while p >= 0 and s[p] == ' ': p -= 1
        if s[p] == ')':
            d = 0; q = p
            while q >= 0:
                if s[q] == ')': d += 1
                elif s[q] == '(': d -= 1
                if d == 0: break
                q -= 1
            r = q-1
            while r >= 0 and (s[r].isalnum() or s[r] == '_'): r -= 1
            st = r+1
        else:
            r = p
            while r >= 0 and (s[r].isalnum() or s[r] == '_'): r -= 1
            st = r+1
        s = s[:st] + 'FW(%s, 0x%s)' % (s[st:i].strip(), off) + s[k:]
    return s
# m2c '?' param/var type -> int (only after '(' or ',' to avoid ternaries)
c = re.sub(r'([(,]\s*)\?(\s+[A-Za-z_])', r'\1int\2', c)
c = conv_arrows(c)
# arr[idx].FW(unkN, off) -> FW(arr[idx].unkN, off)
c = re.sub(r'([A-Za-z_]\w*\[[^\]]*\])\.FW\((unk[0-9A-F]+), (0x[0-9A-Fa-f]+)\)', r'FW(\1.\2, \3)', c)

# struct bases (.unkN), per-base max member; siblings up to max, never aliasing a base
bases = {}; bmax = {}
for m in re.finditer(r'\b(sp([0-9A-F]+))\.unk([0-9A-F]+)\b', c):
    bases[m.group(1)] = int(m.group(2), 16)
    bmax[m.group(1)] = max(bmax.get(m.group(1), 0), int(m.group(3), 16))
sib = {}
for b, off in bases.items():
    for d, mem in ((4, 'unk4'), (8, 'unk8'), (0xC, 'unkC')):
        if d > bmax[b]: continue
        nm = 'sp%X' % (off+d)
        if nm in bases: continue
        sib[nm] = (b, mem)
out = []
for l in c.split("\n"):
    md = re.match(r'^\s*(?:void \*|f32|s32|int|\?32|\?)\s+(sp[0-9A-F]+);\s*(?:/\*.*)?$', l)
    if md and (md.group(1) in bases or md.group(1) in sib): continue
    for nm, (b, mem) in sib.items(): l = re.sub(r'\b'+nm+r'\b', '%s.%s' % (b, mem), l)
    out.append(l)
c = "\n".join(out)
c = c.replace('(?32)', '(s32)').replace('?32', 's32')

ba = '|'.join(sorted(bases, key=len, reverse=True))
if bases:
    c = re.sub(r'\b('+ba+r') = (?!\1)([^;=]+;)', r'\1.unk0 = \2', c)
    c = re.sub(r'= ('+ba+r');', r'= \1.unk0;', c)
    bl = []
    for l in c.split("\n"):
        if not re.match(r'^\s*[A-Za-z_][\w *]*?\*?\s*sp[0-9A-F]+;\s*(?:/\*.*)?$', l):
            l = re.sub(r'(?<![\w.&])('+ba+r')(?!\w)(?!\.)', r'\1.unk0', l)
        bl.append(l)
    c = "\n".join(bl)

c = c.replace("bitwise ", "")
# fn-ptr member call FW(...)( -> ((GT)FW(...))(
def wrap(s):
    o = []; i = 0
    while i < len(s):
        if s.startswith("FW(", i):
            j = i+3; d = 1
            while j < len(s) and d:
                if s[j] == '(': d += 1
                elif s[j] == ')': d -= 1
                j += 1
            if j < len(s) and s[j] == '(': o.append("(("+GT+")"+s[i:j]+")"); i = j; continue
            o.append(s[i:j]); i = j; continue
        o.append(s[i]); i += 1
    return "".join(o)
c = wrap(c)
c = c.replace(PH+"(", "(("+GT+")"+PH+")(")
c = c.replace("(f32) (("+GT+")", "(f32) (int) (("+GT+")")
c = re.sub(r'\(char \*\) \((FW\([^()]*\) \* \*\(f32 \*\)0x[0-9A-Fa-f]+)\)', r'(char *) (int) (\1)', c)
c = c.replace("void *", "char *")
c = c.replace("NULL", "0")
c = re.sub(r'\*0(?!\w)', '*(int*)0', c)
# deref of a non-pointer expr: *(EXPR) -> *(int*)(EXPR), balanced, skip real casts
def cast_derefs(s):
    TYPES = ('int','char','f32','s32','u32','s8','u8','s16','u16','void','unsigned','long','short','f64')
    o=[]; i=0
    while i < len(s):
        if s[i]=='*' and s[i+1:i+4]=='FW(':
            j=i+4; d=1
            while j<len(s) and d:
                if s[j]=='(': d+=1
                elif s[j]==')': d-=1
                j+=1
            o.append('*(int*)('+s[i+1:j]+')'); i=j; continue
        if s[i]=='*' and i+1<len(s) and s[i+1]=='(':
            j=i+2; d=1
            while j<len(s) and d:
                if s[j]=='(': d+=1
                elif s[j]==')': d-=1
                j+=1
            inner=s[i+2:j-1]
            t=inner.lstrip()
            first=re.match(r'[A-Za-z_]\w*', t)
            is_ptr_cast = first and first.group(0) in TYPES and '*' in t[:first.end()+3]
            wrap=False
            if not is_ptr_cast and not t.startswith('&'):
                if t.startswith('('):
                    d2=0; e=0
                    for e in range(len(t)):
                        if t[e]=='(': d2+=1
                        elif t[e]==')': d2-=1
                        if d2==0: break
                    g=t[:e+1]            # leading balanced ( ... ) group
                    wrap = '*' not in g  # value-cast/group -> wrap; pointer-cast -> skip
                elif t[:1].islower() or t.startswith('FW('):
                    wrap=True
            if wrap:
                o.append('*(int*)('+inner+')'); i=j; continue
        o.append(s[i]); i+=1
    return "".join(o)
c = cast_derefs(c)

inject = ("\n#ifndef FW\n#define FW(p, o) (*(int *)((char *)(p) + (o)))\n#endif\n"
          "typedef char *(*%s)();\n" % GT)
if bases:
    inject += "typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } %s;\n" % QT
c = re.sub(r'([A-Za-z_][\w *]*?'+FN+r'\([^)]*\)\s*\{)', inject+r'\1', c, count=1)
if bases:
    decls = "\n".join("    %s %s;" % (QT, b) for b in sorted(bases))
    c = re.sub(r'([A-Za-z_][\w *]*?'+FN+r'\([^)]*\)\s*\{)', r'\1\n'+decls, c, count=1)

idx = c.find("\n}\n")
if idx > 0: c = c[:idx+3]

# auto-declare undeclared sp vars (m2c aliased-stack omissions)
used = set(re.findall(r'\bsp[0-9A-F]+\b', c))
decl = set(re.findall(r'^\s*[A-Za-z_][\w *]*?\*?\s*(sp[0-9A-F]+);\s*(?:/\*.*)?$', c, flags=re.M))
miss = sorted(used-decl)
if miss:
    add = "\n".join("    int %s;" % v for v in miss)
    c = re.sub(r'([A-Za-z_][\w *]*?'+FN+r'\([^)]*\)\s*\{)', r'\1\n'+add, c, count=1)
# dedup decls
seen = set(); dl = []
for l in c.split("\n"):
    m = re.match(r'^\s*[A-Za-z_][\w *]*?\*?\s*(sp[0-9A-F]+);\s*(?:/\*.*)?$', l)
    if m:
        if m.group(1) in seen: continue
        seen.add(m.group(1))
    dl.append(l)
c = "\n".join(dl)
open(OUT, "w").write(c)
print("bases:", len(bases), "miss:", miss, "QT:", QT, "GT:", GT)
