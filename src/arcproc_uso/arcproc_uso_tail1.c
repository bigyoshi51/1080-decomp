#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* Continues arcproc_uso .text at 0xB4 (after arcproc_uso_o0_50.c).
 * Original single-file body split into arcproc_uso.c (0x0..0x50 func_00000000),
 * arcproc_uso_o0_50.c (0x50..0xB4 Quad4 reader -O0), and this tail. */

void arcproc_uso_func_00001B88(int *a0) {
    int *t;
    arcproc_uso_func_00000000(a0);
    t = *(int**)((char*)a0 + 0xD4);
    arcproc_uso_func_00000000(t, 0x8C, *(int*)((char*)t + 0x6B0));
}

#ifdef NON_MATCHING
/* -O0 ref-count/check-full pattern (tried 2026-04-20, cap 82.3%).
 * Semantics decoded: gl_func_0(a0, a1); if (a0[1]+1 == a0[2]) return 1;
 * else a0[1] += 1; return 0. Two blockers at -O0:
 *   1. IDO loads a0[2] BEFORE a0[1] regardless of expression order —
 *      tried `p[1]+1==p[2]`, `p[2]==p[1]+1`, both give `lw 8(t6); lw 4(t6)`.
 *   2. `register int *p = a0` promotes to $s0 in second half (matches
 *      target) but if-else-through-r-variable emits an extra sw/lw pair
 *      for the return value vs target's direct-return pattern.
 * Promotion attempt would require per-insn-order grinding — leaving at
 * 82% cap as future-pass candidate. */
int arcproc_uso_func_000000B4(int *a0, int a1) {
    gl_func_00000000(a0, a1);
    if (a0[1] + 1 == a0[2]) {
        return 1;
    }
    a0[1] += 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000000B4);
#endif

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000012C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000019C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000240);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000005C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000688);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000748);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000007B4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000800);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000880);

void arcproc_uso_func_000008FC(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000938(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void arcproc_uso_func_00000974(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void arcproc_uso_func_000009CC(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000A3C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000D70);

void arcproc_uso_func_00000E58(char *a0) {
    arcproc_uso_func_00000000(a0 + 0x6BC);
    arcproc_uso_func_00000000(a0 + 0x6D4);
    arcproc_uso_func_00000000(a0 + 0x6EC);
    arcproc_uso_func_00000000(a0 + 0x71C);
    arcproc_uso_func_00000000(a0 + 0x704);
    arcproc_uso_func_00000000(a0 + 0x734);
    arcproc_uso_func_00000000(a0 + 0x74C);
    arcproc_uso_func_00000000(a0 + 0x764);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000EBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000F50);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000FA8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001170);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000125C);

int arcproc_uso_func_00000000();

void arcproc_uso_func_00001488(void) {
    arcproc_uso_func_00000000();
}

void arcproc_uso_func_000014A8(void) {
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000014C8);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001604);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000016F4);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000199C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001B04);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001BBC);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001C74);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001D18);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F0C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00001F54);

void arcproc_uso_func_000022A4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000008FC((int*)(dst + 0x10));
}

void arcproc_uso_func_000022D4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000938((float*)(dst + 0x10));
}

void arcproc_uso_func_00002304(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_00000974((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002334);

void arcproc_uso_func_000023C4(char *dst) {
    int tmp;
    arcproc_uso_func_000008FC(&tmp);
    arcproc_uso_func_000009CC((Vec3*)(dst + 0x10));
}

extern int gl_ref_00000040;
extern int gl_ref_00000070;
extern int gl_ref_00000074;

void arcproc_uso_func_000023F4(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

void arcproc_uso_func_00002438(void) {
    gl_func_00000000(gl_ref_00000070);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_00000074, -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000247C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000024C0);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000251C);

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000027BC);

void arcproc_uso_func_00002864(void) {
    arcproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00002884);
#pragma GLOBAL_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso/arcproc_uso_func_00002884_pad.s")
