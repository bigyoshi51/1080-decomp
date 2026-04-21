#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000000);

void titproc_uso_func_00000098(void) {
    gl_func_00000000(&D_00000000 + 0x60, 1);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000000C0);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000194);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000001E4);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000238);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000028C);

extern char D_000002D8_A;

/* Reverse-merge boundary: real function starts at 0x2D8 (splat put the
 * `lui $v0; addiu $v0` prologue 8 bytes earlier, attributed to 0x28C's
 * trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md. */
void titproc_uso_func_000002D8(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 2;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 4);
    gl_func_00000000(*(int*)((char*)&D_000002D8_A + 0xA8), -1, 0);
}

extern char D_0000032C_A;

/* Reverse-merge boundary: real function starts at 0x32C (splat put the
 * `lui $v0; addiu $v0` prologue 8 bytes earlier, attributed to 0x2E0's
 * trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md. */
void titproc_uso_func_0000032C(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 7;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 5);
    gl_func_00000000(*(int*)((char*)&D_0000032C_A + 0xA8), -1, 0);
}

extern char D_00000380_A;

/* Reverse-merge boundary fix: real function starts at 0x380 (splat put
 * the `lui $v0; addiu $v0` prologue 8 bytes earlier and attributed it to
 * 0x334's trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md.
 * Signature is `void f(void)` — no args; $v0 = &D_00000000 via prologue. */
void titproc_uso_func_00000380(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 1;
    *(int*)((char*)&D_00000000 + 0x40) = 1;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(9);
    gl_func_00000000(*(int*)((char*)&D_00000380_A + 0xA8), -1, 0);
}

extern char D_000003D0_A;

void titproc_uso_func_000003D0(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 8;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(*(int*)((char*)&D_000003D0_A + 0xA8), -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000418);

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

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000FD0);

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

