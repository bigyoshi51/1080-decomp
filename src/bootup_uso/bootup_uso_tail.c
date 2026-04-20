#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F81C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F954);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F9E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FAE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FBCC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000100F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001016C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001024C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010260);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102A4);

void func_000102E8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102F0);

void func_00010308(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010310);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010324);

void func_00010344(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010A9C);

void func_00010AA8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010AB0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000118E4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001195C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011A34);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011AB4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011BF0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011C70);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CD8);

#ifdef NON_MATCHING
/* Structure matches but IDO emits beql with duplicated lw in epilogue rather than
 * target's beq+or v0,zero path. Common IDO -O2 -> O1-style unfilled-slot mismatch. */
int func_00011D40(int *a0, int a1) {
    if (*(int*)((char*)a0 + 0x120) < a1) return 0;
    return *(int*)((char*)a0 + a1 * 4 + 0xDC);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D40);
#endif

void func_00011D70(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D78);

void func_00011DB4(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011DBC);

void func_00011DF8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011ED4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011FA8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001207C);

void func_00012088(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012090);

void func_000120A0(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000120A8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012110);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012150);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012188);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012244);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000123F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012458);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000124C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001252C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012598);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012600);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001266C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000127CC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012818);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000128AC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000129A0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012AC4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012B7C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012BF8);

void func_00012C08(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012C10);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012C64);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012D64);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012DA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012DB8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001304C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013924);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013980);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144B4);

void func_000144E0(void *a0, float a1, float a2) {
    *(float*)((char*)a0 + 0x88) = a1;
    *(float*)((char*)a0 + 0x8C) = a2;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144F4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014598);
