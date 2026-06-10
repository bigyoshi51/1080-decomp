#include "common.h"

/* -O0 Vec3 reader at 0x8A40. Mirrors bootup_uso func_0000F2EC:
 * same logical body, same s-reg/stack-offset encoding patch class.
 *
 * NATURAL CEILING 99.90% — 4 `addiu rX, sp, OFF` diffs: target places
 * `raw` at sp+0x48 and `tmp` at sp+0x34 within a 0x58 frame; this C shape
 * puts them at 0x2c/0x40. Declaration-reorder/padding variants tested
 * 2026-05-28 (all NEGATIVE, still 4 diffs or worse):
 *   - swap raw<->tmp decl order: relative order corrects but whole group
 *     shifts -8 (raw=0x40 vs 0x48) — same 4 diffs.
 *   - swap + `int pad_bot[2]` after tmp: fixes the 4 local offsets BUT
 *     grows frame 0x58->0x60 (4 NEW frame-size diffs at prologue/epilogue/
 *     ra-save). Net 4 diffs, just relocated.
 *   - swap + `int pad_top[2]` first: WORSE (8 diffs — frame AND offsets).
 * The 0x58 frame is tightly packed (outgoing-arg area + 2 structs + ra);
 * target's exact raw-high/tmp-low-in-0x58 layout is unreachable by add/
 * remove-padding from C. Permuter won't help (its scorer normalizes
 * sp-relative offsets — feedback-permuter-score-0-sp-offset-false-positive).
 *
 * 2026-05-29 IMPROVED 4 -> 2 diffs (not the documented "permanent cap"): decl
 * order `Tri3i raw; Tri3i tmp; int pad_mid[2];` (raw first/highest, tmp adjacent
 * below, the 8-byte dead pad LAST/lowest) lands tmp@0x34 EXACTLY and keeps frame
 * 0x58 — only &raw remains @0x40 vs target 0x48 (+8). The residual: target wants
 * an 8-byte GAP between tmp-top(0x40) and raw(0x48) with the block pinned to the
 * frame top (raw just below the a0-home@0x58), but every C layout either (a) puts
 * the gap between them and drops the whole block -8 (pad_mid-between = 4 diffs),
 * or (b) packs raw/tmp adjacent at the top (pad-bottom = this, tmp exact, raw -8).
 * The 8-byte top-slack (home->raw) is an -O0 alignment artifact not C-drivable via
 * decl/pad. A standalone-IDO decl-permutation campaign or a real 3rd local in the
 * gap could finish it; near-miss at 2 diffs.
 *
 * 2026-06-01 retest on current body: moving `pad_mid[2]` between raw and tmp
 * (`raw; pad_mid; tmp`) keeps the frame 0x58 but regresses tmp from sp+0x34 to
 * sp+0x2C while raw stays at sp+0x40. The residual is not solved by placing the
 * existing dead pad between the structs.
 *
 * 2026-06-01 NEW MECHANISM (isolates the residual exactly; does NOT crack it).
 * The reason a pad can't land BETWEEN raw and tmp is that they are the SAME type
 * (Tri3i) so -O0 POOLS them adjacent and ejects any pad to an end. Giving them
 * DISTINCT struct types (`Tri3j raw; Tri3i tmp;`, identical layout) breaks the
 * pool — a pad declared between them DOES land between them. With distinct types
 * + raw-first/tmp-last + an 8-byte `pad_mid` between + a LAST-declared bottom pad
 * (`int pad_bot;`), the standalone -O0 emit lands &raw@sp+0x48 and &tmp@sp+0x34
 * EXACTLY (target offsets, 0 offset diffs!) — BUT the bottom pad grows the frame
 * 0x58 -> 0x60 (prologue/epilogue/a0-home shift +8 = MORE diffs than the current
 * 2). Without the bottom pad the offsets drop 8 low (raw@0x40/tmp@0x2c, 4 diffs).
 * So the cap is now precise: target pins the raw/tmp/pad block to frame-TOP with
 * a 12-byte dead gap (0x28-0x33) BELOW tmp inside a 0x58 frame, but every C layout
 * either (a) grows the frame to supply that bottom gap, or (b) packs the block 8
 * low. Genuine -O0 frame-packing cap; the distinct-type pooling-break is the right
 * gap lever but can't coexist with the 0x58 frame. See docs/IDO_CODEGEN.md
 * "distinct struct types break -O0 same-type stack pooling". */

extern int gl_func_00000000();
extern char D_00000000;

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

#ifdef NON_MATCHING
/* 99.95% (2 diffs). Residual PRECISELY characterized 2026-05-31: &raw is at
 * sp+0x40, target sp+0x48 (raw needs +8). Target -O0 layout (by offset):
 * tmp@0x34, pad_mid@0x40, raw@0x48 — i.e. pad_mid sits in the 8-byte gap
 * BETWEEN tmp and raw. Mine packs tmp@0x34, raw@0x40, pad_mid@0x4C (raw/pad
 * swapped). RULED OUT (all REGRESSED to 4-8 diffs, do not re-try): all 6 decl
 * orderings of {raw,tmp,pad_mid}; pad as Tri3i / int[4] / two structs; pad
 * before raw. -O0 packs these same-type structs non-obviously and no C-level
 * decl/type lever swaps raw and pad_mid. Needs a finer -O0 layout insight.
 *
 * 2026-05-31 EXTENDED NEGATIVE (new levers, all CONFIRMED FAIL in-tree + a
 * 90-combo standalone -O0 sweep; do not re-try any of these):
 *  - raw as `int raw[3]` (break the same-type struct grouping): arrays alloc
 *    at the BOTTOM, so raw drops to sp+0x2c (tmp rises to 0x40) — 4 diffs, worse.
 *  - 8-byte struct pad `struct{int a,b;} pad_mid;` order raw/pad/tmp: gives the
 *    correct RELATIVE order (tmp,pad,raw low->high) but the whole block sits 8
 *    low (tmp@0x2c,raw@0x40); won't pin to frame-top — 4 diffs.
 *  - 90-combo standalone brute-force {raw,tmp,pad type} x {6 orderings} x {pad
 *    sizes i1..i4/d1/c8} x {direct vs cast-address body}: ZERO produce the
 *    target's raw@top / tmp-low / pad-between layout.
 *  ROOT CAUSE (now precise): target has 16 bytes between the ra-save@0x24 and
 *  tmp@0x34; every C layout yields only 8 (block ends with 8-byte slack ABOVE
 *  raw instead of below tmp). Pinning the block to the frame-top needs 8 bytes
 *  allocated at the BOTTOM (0x2c-0x34) WITHOUT growing the 0x58 frame — not
 *  expressible via local decl/type/order. A bottom pad fixes offsets but grows
 *  the frame (already documented). Genuine -O0 frame-packing cap.
 *
 * 2026-06-09 COMPILER-AXIS SWEEP (all CONFIRMED FAIL standalone; do not
 * re-try): 7.1 -O0 with -g/-g2/-g3/-g0 (identical 2 diffs -- -g does NOT
 * change IDO -O0 frame layout); 5.3 -O0 (8 diffs, worse); 7.1/5.3
 * -O1 -Olimit 1 fallback (37 insns vs 41 -- target is TRUE -O0, the
 * fallback schedules too much). The cap is C-source-level frame packing
 * at 7.1 -O0 specifically; every flag axis is now exhausted.
 *
 * NOTE (metric): objdiff scores the placeholder `jal func_00000000` reloc-aware
 * (=100% on that insn), VERIFIED 2026-05-31 (100%-fuzzy fns in report.json DO
 * contain placeholder R_MIPS_26 relocs). So cracking this to 100% fuzzy WOULD
 * count on decomp.dev even without resolving the real callee — the 2-diff frame
 * residual is the only thing between this fn and a metric gain. */
void gl_func_00008A40(Vec3 *dst) {
    register Vec3 *q;
    register Vec3 *p1;
    register Vec3 *p2;
    Tri3i raw;
    Tri3i tmp;
    int pad_mid[2];
    register float *src;
    gl_func_00000000(&D_00000000, &raw, 12);
    p1 = dst;
    tmp = raw;
    p2 = p1;
    src = (float*)&tmp;
    p2->x = src[0];
    p2->y = src[1];
    p2->z = src[2];
    q = p1;
    (void)q;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008A40);
#endif
