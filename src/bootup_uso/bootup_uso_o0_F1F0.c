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
 * Exact match via 10-insn INSN_PATCH at 0x24/0x34/0x38/0x3C/0x58/0x5C/
 * 0x64/0x6C/0x74/0x78. IDO -O0 picks $s0 for the first reg-local; target
 * picks $s1 (one-slot shift across all 4 reg-locals). Stack layout
 * is the same size (0x58 frame) but the 3-Tri3i scratch slots sit at
 * different sp offsets in target (sp+0x34/0x48 vs IDO's sp+0x2C/0x40).
 * Both diffs (s-reg shift + 8-byte offset shift) are pure encoding
 * renames — function logic identical, INSN_PATCH overwrites the 10
 * differing words. */
void func_0000F2EC(Vec3 *dst) {
    register Vec3 *p1;
    register Vec3 *p2;
    register Vec3 *q;
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    register float *src;
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
