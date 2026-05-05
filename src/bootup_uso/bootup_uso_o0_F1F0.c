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
 * callee-saved s-regs (s0-s3) which our C body doesn't reach via -O0
 * codegen (no register promotion at -O0; need explicit s-reg-typed
 * register locals). Deferred — leave INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F2EC);
