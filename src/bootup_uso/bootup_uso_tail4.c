#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001304C);

int func_00013924(int *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        if (*(int*)((char*)a0 + 0x68) == 0) {
            func_00000000(&D_00000000, 1);
        }
        return 1;
    }
    return 0;
}

int func_00013980(float *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000139B0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013B20);

void func_00013C70(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CAC(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CE8(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013D40);

void func_00013FE0(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x44) = a1;
    *(int*)(a0 + 0x5C) = a2;
}

void func_00013FEC(char *a0, int a1, int a2, int a3, int arg5) {
    *(int*)(a0 + 0x74) = a1;
    *(int*)(a0 + 0x8C) = a2;
    *(int*)(a0 + 0xA4) = a3;
    *(int*)(a0 + 0xBC) = arg5;
}

void func_00014004(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x104) = a1;
    *(int*)(a0 + 0x108) = a2;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014010);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000140C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014228);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001438C);

void func_000144B4(int *a0, int a1, int a2, float a3, float arg5) {
    *(float*)((char*)a0 + 0x44) = (float)a1;
    *(float*)((char*)a0 + 0x5C) = (float)a2;
    *(float*)((char*)a0 + 0x88) = a3;
    *(float*)((char*)a0 + 0x8C) = arg5;
}

void func_000144E0(void *a0, float a1, float a2) {
    *(float*)((char*)a0 + 0x88) = a1;
    *(float*)((char*)a0 + 0x8C) = a2;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144F4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014598);
