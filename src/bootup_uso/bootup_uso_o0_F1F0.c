#include "common.h"

/* -O0 accessor cluster at 0xF1F0..0xF38F. Split out of bootup_uso.c so
 * these wrappers build at -O0, matching their original frame +
 * spill+reload + b-+1 patterns. Parallel to bootup_uso_o0_F390.c.
 *
 * Templates per feedback_uso_accessor_template_reuse.md:
 *   F1F0  — int reader (4 bytes,  19 insns, 0x4C)
 *   F23C  — float reader (4 bytes, 19 insns, 0x4C, lwc1/swc1 variant)
 *   F288  — Quad4 reader (16 bytes, 25 insns, 0x64)
 *   F2EC  — Vec3 reader (12 bytes, 41 insns, 0xA4, struct-copy + lwc1)
 */

extern int func_00000000();
extern char D_00000000;

typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

void func_0000F1F0(int *a0) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *a0 = buf[0];
}

void func_0000F23C(float *a0) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *a0 = buf[0];
}

void func_0000F288(Quad4 *a0) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *a0 = buf;
}

/* func_0000F2EC: Vec3 reader at -O0 (41 insns / 0xA4). Built at -O0
 * (per per-file Makefile override). Body uses 4 register-typed locals
 * (Vec3* p1/p2/q, float* src) + Tri3i raw + Tri3i tmp on stack.
 *
 * NATURAL CEILING: 98.93% NM (current body; the "~75%" in the old note is
 * obsolete/pre-pad_mid). Was once "exact via 10-insn INSN_PATCH" — INSN_PATCH
 * REMOVED 2026-05-23 as match-faking. The pad_mid[2] already fixes inter-slot
 * spacing (raw/tmp 0x14 apart, matching target). Two residual diffs remain,
 * BOTH permuter-class -O0 caps:
 *   (a) $s-register ROTATION: target's first reg-local is $s1 (s1/s2/s3/s0),
 *       IDO picks $s0 first (s0/s1/s2/s3). -O0 assigns s-regs by first-use
 *       order; no C reorder flips it without regressing.
 *   (b) Whole scratch BLOCK sits 8 bytes higher in target (raw@sp+0x34,
 *       tmp@sp+0x48) vs IDO (raw@sp+0x2C, tmp@sp+0x40), same 0x58 frame. A
 *       leading 8-byte local to push it up regresses to 92% (verified
 *       2026-06-02) — the -O0 allocator re-packs everything. Coupled to (a).
 * Logic byte-identical; residual is -O0 frame-pack + s-reg renumber. NM. */
/* func_0000F2EC — EXACT (41/41) verified 2026-07-02 on agent-e.
 * TU: src/bootup_uso/bootup_uso_o0_F1F0.c (per-file OPT_FLAGS := -O0).
 * Lever: -O0 slot allocation is TOP-DOWN in DECLARATION ORDER, and each
 * `register` var reserves a 4-byte home slot even when it gets an s-reg.
 * Interleaving the scalar decls between the aggregates places raw@sp+0x48
 * and tmp@sp+0x34 (was uniformly 12 low with all 4 reg vars declared first).
 * s-reg assignment follows register-decl order (q=s0, p1=s1, p2=s2, src=s3),
 * which is preserved because only the aggregates moved between them.
 * Slot map: q@0x54, raw@0x48, p1@0x44, p2@0x40, tmp@0x34, src@0x30, pad_lo@0x28.
 * Types (file-scope in the TU):
 *   typedef struct { int a, b, c; } Tri3i;
 *   typedef struct { float x, y, z; } Vec3;
 *   extern int func_00000000(); extern char D_00000000;
 */
void func_0000F2EC(Vec3 *dst) {
    register Vec3 *q;
    Tri3i raw;
    register Vec3 *p1;
    register Vec3 *p2;
    Tri3i tmp;
    register float *src;
    int pad_lo[2];
    func_00000000(&D_00000000, &raw, 12);
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
