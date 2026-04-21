#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000000);

void timproc_uso_b5_func_00000040(void) {
}

void timproc_uso_b5_func_00000048(void) {
}

void timproc_uso_b5_func_00000050(void) {
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000058);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000024C);
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000024C_pad.s")

void timproc_uso_b5_func_00000330(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b5_func_0000036C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b5_func_000003A8(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b5_func_00000400(Vec3 *dst) {
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

void timproc_uso_b5_func_00000470(void) {
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000478);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000778);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000010EC);

void timproc_uso_b5_func_00000000();

void timproc_uso_b5_func_0000115C(int *a0) {
    *(int*)((char*)a0 + 0x34) = 0;
    timproc_uso_b5_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000117C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000131C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001460);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001658);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000018B4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001C08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001F14);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000027B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000283C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00002B74);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000032C8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000038D0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000398C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003A4C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003C8C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003ED8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F18);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F5C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003FA8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003FF8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004068);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000040BC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004118);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005BF0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005FC0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006394);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000685C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006900);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000069E8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006C00);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006D30);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006E08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007078);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000072D0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007430);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000077D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000079A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007B2C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007E34);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000080F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008468);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000085E0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008688);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000894C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008AFC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008C44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008DB4);

int timproc_uso_b5_func_00008F98(int *a0) {
    int *p = (int*)((int*)a0[0x2C/4])[0x28/4];
    return ((int(*)(int))p[0x5C/4])((int)(int*)a0[0x2C/4] + *(short*)((char*)p + 0x58));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008FC8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A97C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A9EC);

void timproc_uso_b5_func_0000AA5C(char *dst) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000330((int*)(dst + 0x10));
}

void timproc_uso_b5_func_0000AA8C(char *dst) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_0000036C((float*)(dst + 0x10));
}

void timproc_uso_b5_func_0000AABC(char *dst) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_000003A8((Quad4*)(dst + 0x10));
}

void timproc_uso_b5_func_0000AAEC(int a0) {
}

void timproc_uso_b5_func_0000AAF4(char *dst) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000400((Vec3*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AB24);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AC20);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B154);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B368);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B624);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B928);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B98C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B9F0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BA60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BAE8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BB88);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BBDC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDA0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDEC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C1B4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C208);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C2C0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C310);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C8AC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C98C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CC74);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CCC8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CE6C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CEB4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D06C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D0DC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D14C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D550);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D884);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000DF14);

void timproc_uso_b5_func_0000E5AC(void) {
    *(int*)&D_00000000 = 0;
    gl_func_00000000();
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000E5AC_pad.s")

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000E5D8);

