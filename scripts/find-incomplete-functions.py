#!/usr/bin/env python3
"""Find INCOMPLETE decomp functions (NM-wrap bodies missing logic) by build-vs-target SIZE GAP.

Companion to find-fixable-nearmisses.py (which finds last-mile near-misses). This one
finds the OTHER productive vein: functions whose C body is structurally incomplete —
the build emits FEWER instructions than the target because the body is a partial/wrong
sketch (missing a loop, missing calls/stores, wrong guard/args). Completing the logic
typically gains +20..40pp of objdiff fuzzy (and fixes genuinely-wrong code).

It ranks by objdiff fuzzy_match_percent (the decomp.dev metric, from a fresh
`objdiff-cli report generate`) and the .o size gap (expected .text bytes - build .text
bytes). A positive gap means the build is SHORT = missing logic.

WORKFLOW per candidate (2026-05-31, ~8 landed this way in game_libs_post):
  1. READ the function's own source comment FIRST (many document the cap / ruled-out
     levers — skip those; see feedback_read_function_comment_before_nearmiss_attempt).
  2. Decode the expected asm + diff vs build; identify the missing/wrong logic.
  3. Rewrite the body; rebuild the .c.o; `objdiff-cli report generate`; check the fn's
     fuzzy went UP. REVERT if it dropped — some gaps are register-allocation / codegen
     (sltu bool-normalize, CSE-hoist, branch-likely, pointer-advance choreography), NOT
     missing logic, and "completing" them regresses.
  4. SKIP fast if the diff is dominated by FP (cvt/swc1/mtc1), `sltu zero,vN`, caller-set
     registers, unaligned lwl/lwr, or heavy register reassignment — those are codegen
     caps, not logic gaps.

Usage:
    objdiff-cli report generate -o /tmp/rep.json
    scripts/find-incomplete-functions.py --report /tmp/rep.json [--min 55 --max 82]
        [--min-gap 20] [--exclude game_uso,gui_uso] [--max-size 360]
"""
import argparse, json, os, subprocess, sys

def fsize(o, sym):
    try:
        out = subprocess.check_output(['mips-linux-gnu-readelf', '-sW', o], text=True)
    except subprocess.CalledProcessError:
        return None
    for ln in out.splitlines():
        p = ln.split()
        if len(p) >= 8 and p[7] == sym and p[3] == 'FUNC':
            return int(p[2])
    return None

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--report', default='/tmp/rep.json')
    ap.add_argument('--min', type=float, default=55.0, help='min fuzzy %')
    ap.add_argument('--max', type=float, default=82.0, help='max fuzzy %')
    ap.add_argument('--min-gap', type=int, default=20, help='min (expected-build) .text byte gap')
    ap.add_argument('--max-size', type=int, default=360)
    ap.add_argument('--exclude', default='game_uso,gui_uso')
    a = ap.parse_args()
    if not os.path.exists(a.report):
        subprocess.run(['objdiff-cli', 'report', 'generate', '-o', a.report], check=True)
    r = json.load(open(a.report))
    excl = [x for x in a.exclude.split(',') if x]
    rows = []
    for u in r['units']:
        seg = u['name']
        if any(x in seg for x in excl):
            continue
        B, E = 'build/non_matching/' + seg + '.c.o', 'expected/' + seg + '.c.o'
        if not (os.path.exists(B) and os.path.exists(E)):
            continue
        for fn in u.get('functions', []):
            f = fn.get('fuzzy_match_percent')
            if f is None or not (a.min <= f <= a.max):
                continue
            se = int(fn['size'])
            if se > a.max_size or se < 80:
                continue
            sb = fsize(B, fn['name'])
            if sb is None:
                continue
            gap = se - sb
            if gap >= a.min_gap:
                rows.append((f, gap, se, fn['name'], seg.split('/')[-1]))
    rows.sort(key=lambda x: -x[0])  # highest fuzzy first (closest to done)
    for f, gap, se, n, s in rows:
        print(f"{f:6.2f}% gap-{gap:<3d} {se:4d}b {n} ({s})")
    print(f"\n{len(rows)} incomplete candidates", file=sys.stderr)

if __name__ == '__main__':
    main()
