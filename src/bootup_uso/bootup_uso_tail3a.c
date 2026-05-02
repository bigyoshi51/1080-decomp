#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


#ifdef NON_MATCHING
/* Array-indexing utility: return a0 + a0->field_7C * 0x28 + 0x84.
 * Target has 8 insns with `addiu v0,v0,0x84; jr ra; nop` (unfilled delay slot).
 * IDO -O2 fills the delay slot with the addiu, producing 7 insns instead.
 * Also addu operand order differs (a0,t7 vs t6,a0) and $v1 vs $t6 for the
 * index temp. Same unfilled-delay class as feedback_ido_unfilled_store_return.md,
 * compute/return variant. Likely needs -O0 or a sibling handwritten stub. */
char *func_00010324(char *a0) {
    int idx = *(int*)(a0 + 0x7C);
    return a0 + idx * 0x28 + 0x84;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010324);
#endif

void func_00010344(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}

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

#ifdef NON_MATCHING
/* append-to-array helper: a0->0x120 is the count, a0->0xE0[count] = a1.
 * 13 insns / 0x34. -O0 indicators: empty `addiu sp,-8` frame with no spill,
 * `b +1; nop` dead-branch BBL marker, leaf function. Verified 2026-05-02
 * that BYTE-IDENTICAL at standalone -O0 with `register s32 idx; register
 * s32 *p = a0;` decl order (idx FIRST so p gets $a3 = higher arg slot).
 *
 * BLOCKED: containing file bootup_uso_tail3a.c is built at -O2 -g3 (per
 * Makefile line 52). To match, would need to split this function out into
 * a new bootup_uso_o0_11C70.c with -O0 OPT_FLAGS, plus migrate ~20 other
 * 0x11C70..0x120A8 functions and adjust tenshoe.ld + tail3a's
 * TRUNCATE_TEXT. Infrastructure work, not single-tick scope. */
void func_00011C70(s32 *a0, s32 a1) {
    register s32 idx;
    register s32 *p = a0;
    idx = *(s32*)((char*)p + 0x120);
    *(s32*)((char*)p + 0x120) = idx + 1;
    *(s32*)((char*)a0 + idx*4 + 0xE0) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011C70);
#endif

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

void func_0001207C(int *a0, int a1) {
    *(int*)((char*)a0 + 0x128) = a1;
}

void func_00012088(void) {
}

void func_00012090(int *a0) {
    *(int*)((char*)a0 + 0x128) = -1;
}

void func_000120A0(void) {
}

