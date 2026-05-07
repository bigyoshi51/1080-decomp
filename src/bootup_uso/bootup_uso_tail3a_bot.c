#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* Tail-bot half of the original bootup_uso_tail3a.c, split on 2026-05-07
 * to carve func_00011D40 out into bootup_uso_o0_11D40.c (-O0). The rest
 * of the 0x11C70..0x120A8 -O0 cluster (CA4/CD8/D78/DBC) stays NM-wrapped
 * here at -O2 -g3 since their bodies haven't been verified byte-exact at
 * -O0 yet — separate /decompile runs will migrate them as they get
 * verified. */

void func_00011D70(void) {
}

#ifdef NON_MATCHING
/* 40.00% NM at -O2 (target -O0). Indexed-pointer-array float load with
 * early-out. 15 insns / 0x3C.
 * -O0 indicators: 3 separate `jr ra` exits with dead jr-ra-nop pair at
 * 0xA0/0xA4, no shared epilogue. Same O0-split-blocked cluster as
 * adjacent func_00011C70/func_00011CA4.
 *
 * Structure:
 *   if (a0->0x18C != 0) return 0.0f;
 *   idx = a0->0x128;
 *   p = (float*)a0[+0xE0 + idx*4];   // pointer-array + index
 *   return *p;
 *
 * Per /decompile run: structural decode, % to be measured. */
float func_00011D78(int *a0) {
    int idx;
    float *p;
    if (*(int*)((char*)a0 + 0x18C) != 0) return 0.0f;
    idx = *(int*)((char*)a0 + 0x128);
    p = *(float**)((char*)a0 + idx * 4 + 0xE0);
    return *p;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D78);
#endif

void func_00011DB4(void) {
}

#ifdef NON_MATCHING
/* Sibling of func_00011D78 — byte-identical structure, reads p[1] (.y)
 * instead of p[0] (.x). Same -O0 cluster blocker (3 separate jr ra exits,
 * no shared epilogue). 15 insns / 0x3C.
 *
 * Structure:
 *   if (a0->0x18C != 0) return 0.0f;
 *   idx = a0->0x128;
 *   p = (float*)a0[+0xE0 + idx*4];   // pointer-array + index
 *   return p[1];                     // .y component
 *
 * Same O0-split-blocked cluster as adjacent func_00011C70/CA4/D78. */
float func_00011DBC(int *a0) {
    int idx;
    float *p;
    if (*(int*)((char*)a0 + 0x18C) != 0) return 0.0f;
    idx = *(int*)((char*)a0 + 0x128);
    p = *(float**)((char*)a0 + idx * 4 + 0xE0);
    return p[1];
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011DBC);
#endif

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
