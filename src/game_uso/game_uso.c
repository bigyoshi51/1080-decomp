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

typedef struct { int a, b, c, d; } Quad4;
void game_uso_func_000002BC(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b; } Pair2;
void game_uso_func_00000314(Pair2 *dst) {
    Pair2 buf;
    gl_func_00000000(&D_00000000, &buf, 8);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 92%: int-reader variant with pointer-indirect load. Target emits
 * `addiu t7, sp, 0x18; lw t9, 0(t7)` (16 instr) instead of standard `lw t6, 0x18(sp)` (15 instr).
 * IDO won't force the address-materialize-then-load from C without pipe-breaking tricks. */
void game_uso_func_0000035C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000035C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000039C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000003F8);

void game_uso_func_000005B8(Vec3 *a0) {
    game_uso_func_000001D4(a0);
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0xC));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x18));
    game_uso_func_00000244((float*)((char*)a0 + 0x24));
    game_uso_func_00000280((int*)((char*)a0 + 0x28));
    game_uso_func_000001D4((Vec3*)((char*)a0 + 0x2C));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000608);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000724);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000007EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000858);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000008FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000940);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00000B3C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001644);

#ifdef NON_MATCHING
/* 92.9%: body matches; IDO spills a0 (unused) to caller arg slot per feedback_ido_unused_arg_save.md
 * but target doesn't. Fixable if a0 can be dropped from signature without changing a1's register. */
void game_uso_func_00001714(int a0, int *a1) {
    int v = *a1;
    if (v == 8 || v == 9) {
        gl_func_00000000();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00001714);
#endif

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

void game_uso_func_00002714(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00000000(a0, a2);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002744);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002814);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000028C0);

void game_uso_func_00002CA8(char *a0) {
    game_uso_func_00000000(a0 + 0x44);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00002CC8);

void game_uso_func_00002FC8(int *a0, int a1, int a2) {
    if (*(int*)((char*)a0 + 0x40) == a1) return;
    *(int*)((char*)a0 + 0x40) = a1;
    game_uso_func_00000000(a0, a2);
}

void game_uso_func_00002FF8(void) {
    game_uso_func_00000000();
}

void game_uso_func_00000B14(void *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003018);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000034A4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003558);

void game_uso_func_00003948(char *a0) {
    game_uso_func_00000000(a0 + 0x50);
}

void game_uso_func_00003968(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_00000244((float*)(dst + 0x10));
}

void game_uso_func_00003998(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_000001D4((Vec3*)(dst + 0x10));
}

void game_uso_func_000039C8(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_0000039C((Quad4*)(dst + 0x10));
}

void game_uso_func_000039F8(char *dst) {
    int tmp;
    game_uso_func_00000280(&tmp);
    game_uso_func_00000280((int*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003A28);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003AC0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003ED4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00003FAC);

void game_uso_func_00004080(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_000040BC(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_000040F8(Vec3 *dst) {
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

void game_uso_func_00004168(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000041C0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000043E4);

void game_uso_func_000044C8(char *a0) {
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0 + 0x3C);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000044F4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00005780);

void game_uso_func_000057B8(char *a0) {
    game_uso_func_00000000(a0 + 0xE4);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000057D8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00005924);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006A30);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006CF0);

void game_uso_func_00006E88(int *a0) {
    int r;
    gl_func_00000000(a0);
    r = gl_func_00000000(a0);
    *(int*)((char*)a0 + 0x80) = r;
    if (r == 0) return;
    *(int*)((char*)a0 + 0x40) = gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006ECC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006F40);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00006FA8);

void game_uso_func_000071A4(int *a0) {
    *(int*)((char*)a0 + 0x64) = 1;
    *(int*)((char*)a0 + 0x70) = 0;
    if (*(int*)((char*)a0 + 0x4C4) > 0) {
        gl_func_00000000(a0);
        *(int*)((char*)a0 + 0x4C4) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000071E0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007424);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007ACC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00007C1C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00008CD8);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000097EC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00009B88);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A0E8);

#ifdef NON_MATCHING
/* 86.7%: body+control flow match; target has 2 extra a1 spills (to sp+0x1C and sp+0x4)
 * that appear when callee is varargs — unique-extern varargs trick not applied here because
 * callee is the shared placeholder gl_func_00000000. */
int game_uso_func_0000A374(int a0, int a1, int a2) {
    int r = gl_func_00000000(*(int*)&D_00000000, a1);
    if (r == 0) return 0;
    return gl_func_00000000(r, a2, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A374);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A3C4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A604);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000A7F8);

void game_uso_func_0000ABB8(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_000040BC((float*)(dst + 0x10));
}

void game_uso_func_0000ABE8(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_000040F8((Vec3*)(dst + 0x10));
}

void game_uso_func_0000AC18(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_00004168((Quad4*)(dst + 0x10));
}

void game_uso_func_0000AC48(char *dst) {
    int tmp;
    game_uso_func_00004080(&tmp);
    game_uso_func_00004080((int*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AC78);

void game_uso_func_0000AD10(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000AD4C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000AD88(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void game_uso_func_0000ADE0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000AE1C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B274);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B424);

#ifdef NON_MATCHING
/* 80.0%: USO wrapper a0+=0xEC. Body 8 instr matches, target has 2 trailing data words
 * (lui+lw — looks like a data load from next function mis-bundled by splat). */
void game_uso_func_0000B498(char *a0) {
    game_uso_func_00000000(a0 + 0xEC);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B498);
#endif

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B4C0);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B750);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B884);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000B8D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BB8C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BF7C);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000BFDC);

void game_uso_func_0000C05C(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000AD10((float*)(dst + 0x10));
}

void game_uso_func_0000C08C(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000ADE0((int*)(dst + 0x10));
}

#ifdef NON_MATCHING
/* 92.3%: composite reader (int + Quad4 at dst+0x10). Target has trailing nop padding
 * (13 instructions; body is 12). See feedback_function_trailing_nop_padding.md. */
void game_uso_func_0000C0BC(char *dst) {
    int tmp;
    game_uso_func_0000AD4C(&tmp);
    game_uso_func_0000AD88((Quad4*)(dst + 0x10));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C0BC);
#endif

void game_uso_func_0000C0F0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0000C12C);

void game_uso_func_0000C194(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000C1D0(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void game_uso_func_0000C20C(Vec3 *dst) {
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

void game_uso_func_0000C27C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

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

void game_uso_func_00010E8C(int a0) {
    game_uso_func_00000000(a0, 0x70005, 0, 1, 1, 1);
}

void game_uso_func_00010EC8(int a0) {
    game_uso_func_00000000(a0, 0x7000F, 0, 1, 1, 1);
}

void game_uso_func_00010F04(int a0) {
    game_uso_func_00000000(a0, 0x70003, 0, 1, 1, 1);
}

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

void game_uso_func_00011428(int *a0) {
    game_uso_func_00000000(a0, *(int*)((char*)a0 + 0x74), 4, 1, 1, 1);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011460);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000114FC);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011564);

void game_uso_func_000115EC(int *a0, int a1) {
    *(int*)((char*)a0 + 0x108) = a1;
    game_uso_func_00000000(a0);
    game_uso_func_00000000(a0);
    *(int*)((char*)a0 + 0x114) = 0;
    game_uso_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011624);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_000116D4);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011750);

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_0001189C);

void game_uso_func_000119D4(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C1D0((float*)(dst + 0x10));
}

void game_uso_func_00011A04(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C20C((Vec3*)(dst + 0x10));
}

void game_uso_func_00011A34(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C27C((Quad4*)(dst + 0x10));
}

void game_uso_func_00011A64(char *dst) {
    int tmp;
    game_uso_func_0000C194(&tmp);
    game_uso_func_0000C194((int*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/game_uso/game_uso", game_uso_func_00011A94);

