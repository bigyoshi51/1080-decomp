#!/usr/bin/env python3
"""Find NM-wrapped functions whose BUILT instruction count != TARGET (.s) count.

A size mismatch is a STRUCTURAL signal: built > target = over-production (often a
control-flow bug, e.g. alloc-cascade failure arms that `goto end` instead of
converging into the init tail — see docs/PATTERNS.md); built < target = an
incomplete decode (missing logic). Either is C-FIXABLE, unlike same-size
register-allocation / scheduling caps. Run from a project worktree after
`make non_matching_objects`. Requires report.json (objdiff-cli report generate).

Usage:  python3 scripts/find-size-mismatch.py [min_fuzzy] [max_fuzzy]
        (defaults 60 100; prints by |delta| descending)
"""
import json, re, os, subprocess, sys

minf = float(sys.argv[1]) if len(sys.argv) > 1 else 60.0
maxf = float(sys.argv[2]) if len(sys.argv) > 2 else 100.0
rep = json.load(open("report.json"))


def target_insns(seg, fdir, name):
    p = f"asm/nonmatchings/{seg}/{fdir}/{name}.s"
    try:
        return sum(1 for l in open(p) if re.search(r"\.word 0x", l))
    except OSError:
        return None


rows = []
for u in rep["units"]:
    un = u["name"]
    parts = un.split("/")
    if len(parts) < 3 or not un.startswith("src/"):
        continue
    seg, fdir = parts[1], parts[2]
    oo = f"build/non_matching/{un}.c.o"
    if not os.path.exists(oo):
        continue
    nm = subprocess.run(
        ["mips-linux-gnu-nm", "--print-size", oo], capture_output=True, text=True
    ).stdout
    built = {}
    for l in nm.splitlines():
        p = l.split()
        if len(p) >= 4 and p[2] in ("t", "T"):
            built[p[3]] = int(p[1], 16) // 4
    for f in u.get("functions") or []:
        fp = f.get("fuzzy_match_percent", 0)
        if not (isinstance(fp, (int, float)) and minf <= fp < maxf):
            continue
        bi, ti = built.get(f["name"]), target_insns(seg, fdir, f["name"])
        if bi and ti and bi != ti:
            rows.append((abs(bi - ti), bi - ti, bi, ti, fp, f["name"], seg))

rows.sort(reverse=True)
for _, delta, bi, ti, fp, n, seg in rows:
    kind = "OVER (control-flow/redundancy)" if delta > 0 else "UNDER (missing logic)"
    print(f"delta={delta:+4d} (built {bi}/tgt {ti}) fuzzy={fp:5.1f}  {n} [{seg}]  {kind}")
print(f"\n{len(rows)} size-mismatch functions (fuzzy {minf:g}-{maxf:g}). "
      f"OVER (+) ~ convergence/redundancy fix; UNDER (-) ~ complete the decode.")
