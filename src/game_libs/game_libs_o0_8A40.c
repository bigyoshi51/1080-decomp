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

/* EXACT 41/41 (2026-07-03). The "genuine -O0 frame-packing cap" (90-combo sweep +
 * compiler-axis exhaustion) fell to the F2EC register-home interleave lever:
 * -O0 reserves a 4-byte home slot per `register` var IN DECLARATION ORDER even
 * when colored to an s-reg — moving p1/p2 decls AFTER raw drops their two home
 * slots below raw, lifting &raw from sp+0x40 to sp+0x48 frame-neutrally.
 * The old sweep only permuted the aggregates, never the register decls. */
void gl_func_00008A40(Vec3 *dst) {
    register Vec3 *q;
    Tri3i raw;
    register Vec3 *p1;
    register Vec3 *p2;
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
