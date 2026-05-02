#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

#ifdef NON_MATCHING
/* USO loader-patched branch trampoline at offset 0 (word 0x10006F00 =
 * `beq zero, zero, +0x6F00`) followed by a standard -O2 int-reader
 * template body. Same pattern as boarder5_uso_func_00000000 and
 * arcproc_uso_func_00000000. The leading 4-byte trampoline is unmatchable
 * from C alone (per feedback_uso_branch_placeholder_trampoline.md). The
 * body is the standard int-reader template (delay slots filled, direct lw
 * for buf reload -- so -O2, not -O0). Body without trampoline matches the
 * other USOs' int-readers. */
void eddproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_00000000);
#endif

void eddproc_uso_func_00000040(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void eddproc_uso_func_0000007C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void eddproc_uso_func_000000D4(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void eddproc_uso_func_00000144(int a0, int a1) {
}

void eddproc_uso_func_00000150(int a0, int a1) {
}

extern int D_00000004;

void eddproc_uso_func_0000015C(char *a0) {
    *(char**)(a0 + 0xC) = &D_00000000 + 0x220;
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0xD6, 0x13, *(char**)(a0 + 0x44) + 0x10);
    gl_func_00000000(a0, 0x6C, 0x11, (char*)a0 + 0xA0);
    *(int*)(a0 + 0xA0) = 0x2328;
    *(int*)(a0 + 0xA4) = 0;
    *(int*)&D_00000000 = gl_func_00000000(0x3E80);
    D_00000004 = 0;
    gl_func_00000000(a0);
}

void eddproc_uso_func_000001E8(char *a0) {
    if (*(int*)(&D_00000000 + 0x74) == 0) {
        gl_func_00000000();
        gl_func_00000000(a0);
        if ((*(int*)(a0 + 0xA0) -= 0xA) < 0) {
            *(int*)(a0 + 0xA0) = 0;
        }
    }
    gl_func_00000000(a0);
    gl_func_00000000(*(int*)(a0 + 0x84), *(int*)(a0 + 0xA0), 1);
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000025C);

void eddproc_uso_func_00000324(int a0) {
}

void eddproc_uso_func_0000032C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    gl_func_00000000(dst + 0x10);
}

void eddproc_uso_func_0000035C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_00000040((float*)(dst + 0x10));
}

void eddproc_uso_func_0000038C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_0000007C((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000003BC);

void eddproc_uso_func_0000044C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_000000D4((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso/eddproc_uso_func_0000044C_pad.s")

