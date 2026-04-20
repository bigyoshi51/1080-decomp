#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000000);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000004C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000000B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000005A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000065C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000006B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000006F0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000734);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000778);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000007BC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000800);

void timproc_uso_b1_func_0000083C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_00000878(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_000008B4(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b1_func_0000090C(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000097C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000D1C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000DA0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000DEC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000E40);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000EC0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000EE8);

void timproc_uso_b1_func_00000000();

void timproc_uso_b1_func_000010DC(int a0, char *a1) {
    timproc_uso_b1_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00001100(int a0) {
    gl_ref_00000040 = 9;
    gl_func_00000000(a0, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001130);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001340);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000016F8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001860);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000018D4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001908);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000019C0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001A64);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001BCC);

void timproc_uso_b1_func_00001E44(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000083C((int*)(dst + 0x10));
}

void timproc_uso_b1_func_00001E74(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_00000878((float*)(dst + 0x10));
}

void timproc_uso_b1_func_00001EA4(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_000008B4((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001ED4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001F64);

void timproc_uso_b1_func_00001FA0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001FE4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002030);

void timproc_uso_b1_func_000020AC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_000020F0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00002134(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002178);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000021D4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000024F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002740);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002838);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002A8C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002BE4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002CE0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002D48);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002E50);

