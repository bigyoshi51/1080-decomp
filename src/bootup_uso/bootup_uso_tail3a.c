#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010324);

void func_00010344(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

#ifdef NON_MATCHING
/* Unmatchable from C at -O2: target has `sw zero,0x78(a0); jr ra; nop`
 * (unfilled delay slot, 3 insns) but IDO -O2 schedules the store into the
 * delay slot producing `jr ra; sw zero,0x78(a0)` (2 insns). Different size.
 * See feedback_ido_unfilled_store_return.md. Kept as INCLUDE_ASM; wrapping
 * C here just documents the semantic content. */
void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010A9C);
#endif

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

