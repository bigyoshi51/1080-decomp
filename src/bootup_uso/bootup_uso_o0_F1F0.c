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

/* func_0000F2EC: Vec3 reader at -O0 (41 insns / 0xA4). Target uses 4
 * callee-saved s-regs (s0-s3). 4-`register` C body produces s-saves but
 * frame is +0x10 (0x68 vs target 0x58) — IDO -O0 reserves backup stack
 * slots for register-typed locals (4 × 4 bytes = 16 byte overhead) that
 * target doesn't have. Possibly target was compiled with a different
 * IDO -O0 variant or had non-register stack-only locals that got
 * promoted by a later pass.
 *
 * Fuzzy and structure are MUCH closer than INCLUDE_ASM; tmp/raw stack
 * layouts match (sp+0x34/sp+0x48). All 4 s-saves emit. Cap is the +0x10
 * frame overhead. Partial wrap kept for future-pass continuation. */
#ifdef NON_MATCHING
/* 2026-05-05: tried dropping unused p1/q register-locals (4→2 register
 * vars). Frame stayed at -0x68 vs target -0x58, +0x10 overhead unchanged.
 * The 16-byte frame overhead persists regardless of register-local count,
 * suggesting it's NOT the register-backup-slot theory — it's likely raw
 * + tmp + src each getting redundant slot reservations from IDO -O0's
 * naive stack-allocator. Remove `register` to test (likely regresses).
 * Reverting to 4-register-var form for stable baseline.
 *
 * 2026-05-06 retry (no-register-vars): dropped all 4 `register` qualifiers
 * + replaced p1/p2/q with direct `dst` accesses. Frame shrank from -0x68
 * to -0x50 (-0x18 below target -0x58!). Match 84.61% → 60.00% (regression
 * 24.6pp). Without register hints, IDO -O0 doesn't allocate s-regs, so
 * no s-reg saves emit and frame collapses past target's layout.
 * Confirms target uses register-typed locals (4 of them, hence 0x10 of
 * s-reg backup) but with -0x10 less stack frame than C produces. The
 * remaining gap is IDO -O0 producing extra slot reservations that target
 * doesn't have — possibly from a non-IDO toolchain pass on the original
 * ROM, or a subtle -O0 sub-flag (e.g., -O0 -fno-something).
 *
 * 2026-05-06 retry: tried minimal-locals (drop pads, init all post-jal
 * via `p1 = dst; tmp = raw; src = ...; q = p1; p2 = q;`) — regressed
 * to 68.3 % (the post-jal init pattern doesn't reach target's exact
 * `lw s1, 0x58(sp)` placement; introduces extra `move s2, s1` shuffle).
 * Also tried no-register variant — collapsed to 14.6 % (no s-reg saves
 * emit). The baseline 4-register-var + 3-pad-array form remains the
 * tightest reachable; cap is structural per IDO -O0 frame-slot reservation. */
void func_0000F2EC(Vec3 *dst) {
    register Vec3 *p1 = dst;
    register Vec3 *p2 = p1;
    register Vec3 *q;
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[3];
    register float *src = (float*)&tmp;
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    p2->x = src[0];
    p2->y = src[1];
    p2->z = src[2];
    q = p1;
    (void)q;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F2EC);
#endif
