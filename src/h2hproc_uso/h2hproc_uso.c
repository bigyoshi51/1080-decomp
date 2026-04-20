#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000000);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000002C);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000020C);

#ifdef NON_MATCHING
/* 91.7%: body matches 11/12. Target has trailing 0x00000000 padding that IDO won't emit;
 * bytes through pos 10 are identical. See feedback_function_trailing_nop_padding.md. */
void h2hproc_uso_func_00000274_inner(int *arg);

void h2hproc_uso_func_00000274(int *a0) {
    h2hproc_uso_func_00000274_inner((int*)a0[2]);
    a0[2] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000274);
#endif

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000002A4);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000002FC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000354);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000003AC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000404);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000045C);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000004A4);

void h2hproc_uso_func_000004E0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_0000051C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_00000558(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void h2hproc_uso_func_000005B0(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000620);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000008EC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000944);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000099C);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000009F8);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000A88);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000BAC);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000C18);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000E04);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000EB0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000F60);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000FD0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001204);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001360);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000015F0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000017A0);

void h2hproc_uso_func_000019DC(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_000004E0((int*)(dst + 0x10));
}

void h2hproc_uso_func_00001A0C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_0000051C((float*)(dst + 0x10));
}

void h2hproc_uso_func_00001A3C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_00000558((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001A6C);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001AFC);

