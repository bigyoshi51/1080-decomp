#include "common.h"

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000000);

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void game_uso_func_000001D4(Vec3 *dst) {
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

extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00000244(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern int gl_func_00000000();
extern char D_00000000;
void game_uso_func_00000280(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000002BC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000314);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000035C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000039C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000003F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000005B8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000608);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000724);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000007EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000858);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000008FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000940);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B14);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B3C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001644);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001714);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000174C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000018FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001D30);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001DDC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000023D8);

extern void game_uso_func_00000000();

void game_uso_func_0000249C(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000024BC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002714);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002744);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002814);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000028C0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002CA8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002CC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002FC8);

void game_uso_func_00002FF8(void) {
    game_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003018);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000034A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003558);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003948);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003968);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003998);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000039C8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000039F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003A28);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003AC0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003ED4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003FAC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00004080);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000040BC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000040F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00004168);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000041C0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000043E4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000044C8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000044F4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00005780);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000057B8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000057D8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00005924);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006A30);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006CF0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006E88);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006ECC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006F40);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006FA8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071E0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007424);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ACC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007C1C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00008CD8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000097EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A0E8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A374);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A3C4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A604);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A7F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000ABB8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000ABE8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AC18);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AC48);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AC78);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AD10);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AD4C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AD88);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000ADE0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AE1C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B274);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B424);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B498);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B4C0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B750);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B884);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B8D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BB8C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BF7C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BFDC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C05C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C08C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C0BC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C0F0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C12C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C194);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C1D0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C20C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C27C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C2D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C3F8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C48C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D210);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D418);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D458);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D63C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D6E4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D74C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D7F4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D8A8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D8EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000D9CC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E1FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E35C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E564);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E5C8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000E91C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000ECEC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EE30);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EE84);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EF20);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000EF70);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F060);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F13C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F284);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F360);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F424);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F49C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F514);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F5A8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F664);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F6D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F8E8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000F948);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FA54);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FABC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FB7C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FBF8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FC34);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FD04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FDCC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FEC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FF48);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000FFB8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001001C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010068);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010128);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000102CC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010408);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000104A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001056C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000105DC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010650);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010694);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010840);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001094C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010A0C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010AC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010B38);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010BAC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010C4C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010CF0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010DC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010E2C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010E8C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010EC8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010F04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010F40);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010F7C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00010FB8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011024);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000110A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011124);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011168);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011258);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000112E0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011368);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000113C8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011428);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011460);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000114FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011564);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000115EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011624);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000116D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011750);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001189C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000119D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A04);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A34);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A64);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A94);

