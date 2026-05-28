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
 * Permanent NM sp-layout cap. */

extern int gl_func_00000000();
extern char D_00000000;

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

#ifdef NON_MATCHING
void gl_func_00008A40(Vec3 *dst) {
    register Vec3 *q;
    register Vec3 *p1;
    register Vec3 *p2;
    Tri3i tmp;
    int pad_mid[2];
    Tri3i raw;
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
