#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000000);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000098);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000000CC);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000194);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000001E4);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000238);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000028C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000002E0);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000334);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000388);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000003D8);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000420);

void titproc_uso_func_0000049C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void titproc_uso_func_000004D8(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void titproc_uso_func_00000514(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void titproc_uso_func_0000056C(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000005DC);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000B6C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000C0C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000C54);

#ifdef NON_MATCHING
/* 99.42 %: body matches; bnel branch target differs by 3 instructions.
 * Target tail-merges the v0!=21 epilogue with the v0==21 third-call's a0/a1
 * reloads (bnel target = 0x1008 = `lw a1, 0x1C(sp)`). My version goes
 * straight to epilogue (bnel target = 0x1010 = `addiu sp`). Cosmetic. */
void titproc_uso_func_00000FD0(void *a0, int *a1) {
    int v = *a1;
    if (v == 21) {
        gl_func_00000000();
        gl_func_00000000(a0);
        gl_func_00000000(a0, a1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000FD0);
#endif

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000101C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000116C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000015F4);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001718);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001840);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001950);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001B10);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001BB8);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001C68);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001D7C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001E2C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001E9C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00002270);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000022BC);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000240C);

void titproc_uso_func_00000000();

void titproc_uso_func_000026D0(int *a0) {
    int *p = *(int**)((char*)a0 + 0x6C0);
    if (p == 0) return;
    titproc_uso_func_00000000(p);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000026FC);

void titproc_uso_func_000028C0(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_0000049C((int*)(dst + 0x10));
}

void titproc_uso_func_000028F0(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_000004D8((float*)(dst + 0x10));
}

void titproc_uso_func_00002920(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_00000514((Quad4*)(dst + 0x10));
}

void titproc_uso_func_00002950(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_0000056C((Vec3*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00002980);
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_00002980_pad.s")

