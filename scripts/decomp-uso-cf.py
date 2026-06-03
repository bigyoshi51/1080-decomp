#!/usr/bin/env python3
"""End-to-end driver for the non-jumptable USO control-flow lift vein.

For a given USO function name it: locates the expected .o (split files for
game_libs) and the src .c, disassembles (fixing the bc1f/bc1t spacing bug),
runs m2c, SCREENS for blockers (M2C_ERROR / unset register / M2C_MEMCPY /
struct-array sp[idx] / jumptable jr-to-reg), lifts via lift-uso-controlflow.py
(passing the src for decl-awareness), casts calls to any OTHER in-file
'void NAME(void)' placeholder, splices the body between #ifdef NON_MATCHING and
#else, builds the non_matching object, and reports the error count.

Usage: scripts/decomp-uso-cf.py <FUNC>      # then review + measure + commit
It does NOT commit. On a blocker it prints BLOCKED:<reason> and makes no edit.
"""
import re, sys, subprocess, glob, os
from elftools.elf.elffile import ELFFile

FN = sys.argv[1]
# module + placeholder from the name
if FN.startswith("gl_func_") or FN.startswith("game_libs_func_"):
    MOD, ASM, PH = "game_libs", "game_libs", "gl_func_00000000"
else:
    MOD = FN.rsplit("_func_", 1)[0]; ASM = MOD; PH = MOD + "_func_00000000"

def find_obj():
    for o in glob.glob("expected/src/%s/*.c.o" % MOD):
        try:
            st = ELFFile(open(o, "rb")).get_section_by_name(".symtab")
            if st and any(s.name == FN and s["st_size"] for s in st.iter_symbols()):
                return o
        except Exception:
            pass
    return None

def find_src():
    needle = 'INCLUDE_ASM("asm/nonmatchings/%s/%s", %s)' % (MOD, ASM, FN)
    for f in glob.glob("src/%s/*.c" % MOD):
        if needle in open(f).read():
            return f
    return None

obj, src = find_obj(), find_src()
if not obj: sys.exit("no expected obj for " + FN)
if not src: sys.exit("no src for " + FN)

raw = subprocess.run(["python3", "scripts/disasm-func.py", FN, "--obj", obj],
                     capture_output=True, text=True).stdout
raw = re.sub(r'(bc1[ft]l?)\.L', r'\1 .L', raw)
open("/tmp/cf_raw.s", "w").write(raw)
m2c = subprocess.run(["uv", "run", "m2c", "--target", "mips-ido-c", "/tmp/cf_raw.s"],
                     capture_output=True, text=True).stdout
open("/tmp/cf.c", "w").write(m2c)

for pat, why in [(r'M2C_ERROR', 'M2C_ERROR'), (r'Read from unset register', 'unset-register'),
                 (r'M2C_MEMCPY', 'memcpy-intrinsic'), (r'\w+\[[^\]]*\]\.unk', 'struct-array-access'),
                 (r'Unable to determine', 'jumptable')]:
    if re.search(pat, m2c):
        sys.exit("BLOCKED:" + why)

subprocess.run(["python3", "scripts/lift-uso-controlflow.py", FN, PH, "/tmp/cf.c", "/tmp/cf_body.c", src],
               check=True)
body = open("/tmp/cf_body.c").read()
# cast calls to OTHER in-file 'void NAME(void) {' placeholders (the primary PH is
# already GP-cast by the lifter)
for m in re.finditer(r'^\s*void\s+([A-Za-z_]\w*)\s*\(void\)\s*\{', open(src).read(), flags=re.M):
    name = m.group(1)
    if name not in (PH, FN) and (name + "(") in body:
        body = body.replace(name + "(", "((int(*)())" + name + ")(")
open("/tmp/cf_body.c", "w").write(body)

L = open(src).read().split("\n")
defi = next(i for i in range(len(L)) if re.match(r'^[A-Za-z_][\w *]*?' + FN + r'\(', L[i]) and L[i].rstrip().endswith("{"))
ifdef = max(i for i in range(defi) if L[i].strip() == "#ifdef NON_MATCHING")
els = next(i for i in range(defi, len(L)) if L[i].strip() == "#else")
open(src, "w").write("\n".join(L[:ifdef + 1] + [body.rstrip("\n")] + L[els:]))

r = subprocess.run(["make", "non_matching_objects", "RUN_CC_CHECK=0"], capture_output=True, text=True)
errs = [l for l in (r.stdout + r.stderr).split("\n") if "cfe: Error" in l]
print("FUNC=%s SRC=%s OBJ=%s" % (FN, os.path.basename(src), os.path.basename(obj)))
print("errcount=%d" % len(errs))
for l in errs[:6]: print(l)
