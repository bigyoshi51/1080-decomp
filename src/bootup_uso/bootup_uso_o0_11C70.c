#include "common.h"

/* -O0 sub-file split out of bootup_uso_tail3a.c on 2026-05-07. Carries
 * func_00011C70's verified -O0 body + INCLUDE_ASM stubs for the still-NM
 * functions in this address range (11CA4, 11CD8). When 11CA4 / 11CD8 are
 * individually verified at -O0, they migrate into this file and replace
 * the INCLUDE_ASM lines.
 *
 * Pattern: minimal -O0 frame, register-typed locals, b .+1 dead-branch BB
 * marker. */

/* func_00011C70: append-to-array helper. a0->0x120 is the count, the array
 * is at a0->0xE0 (4-byte entries). Decl order matters — `idx` declared
 * BEFORE `p` so that the local pointer copy lands in $a3 (higher arg slot)
 * via IDO -O0's first-allocated-reg-local pick. Body byte-exact at -O0
 * (verified 2026-05-02 and re-verified 2026-05-07). */
void func_00011C70(s32 *a0, s32 a1) {
    register s32 idx;
    register s32 *p = a0;
    idx = *(s32*)((char*)p + 0x120);
    *(s32*)((char*)p + 0x120) = idx + 1;
    *(s32*)((char*)a0 + idx*4 + 0xE0) = a1;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CD8);
