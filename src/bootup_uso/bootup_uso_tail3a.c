#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* Array-indexing utility: return a0 + a0->field_7C * 0x28 + 0x84.
 * 7/8 NM cap structural (IDO -O2 fills jr-ra delay slot with addiu,
 * target had unfilled). Promoted to exact via INSN_PATCH at offsets
 * 0x10/0x14 (Makefile entry, ports the 2-word patch from agent-b). */
char *func_00010324(char *a0) {
    return a0 + *(int*)(a0 + 0x7C) * 0x28 + 0x84;
}

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

#ifdef NON_MATCHING
/* 44.62% NM at -O2 (target -O0). Append-to-array helper at offsets 0x124
 * (count) + 0x100 (4-byte entries).
 * 13 insns / 0x34. -O0 indicators: minimal `addiu sp,-8` frame with no spill,
 * `b +1; nop` dead-branch BB-ender, leaf function, `or a3, a0, zero` arg copy
 * to high register. Same structure as adjacent func_00011C70 which is also
 * documented as O0-split-blocked.
 *
 * BLOCKED: this is part of the ~20-function 0x11C70..0x120A8 -O0 cluster
 * inside bootup_uso_tail3a.c (which builds at -O2 -g3). To match, would need
 * to split this function (and the rest of the cluster) into a new
 * bootup_uso_o0_11C70.c with -O0 OPT_FLAGS, plus adjust tail3a's
 * TRUNCATE_TEXT and the linker script. Same infrastructure scope as
 * func_00011C70's wrap doc.
 *
 * Body inferred (default -O2 emit will diverge — kept here for reference): */
void func_00011CA4(int *a0, int a1) {
    int idx = *(int*)((char*)a0 + 0x124);
    *(int*)((char*)a0 + 0x124) = idx + 1;
    *(int*)((char*)a0 + idx * 4 + 0x100) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CA4);
#endif

#ifdef NON_MATCHING
/* func_00011CD8: 46.35%, 26-insn flag-setter. Target is -O0-shape (full
 * arg-spill at entry, every var reloaded from stack, dead `b .L+1` BB
 * markers). bootup_uso_tail3a is -O2 -g3 which produces 19 insns — 7
 * insn deficit reproduces the logic but won't byte-match. Promotion
 * needs file split to -O0 (per project_1080_bootup_uso_o0_runs memo). */
void func_00011CD8(int *a0, int a1) {
    if (a1 != 0) {
        func_00000000(a0);
        *(int*)((char*)a0 + 0x188) = 0;
    } else {
        func_00000000(a0);
        *(int*)((char*)a0 + 0x188) = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CD8);
#endif

/* func_00011D40 split out to bootup_uso_o0_11D40.c on 2026-05-07 (verified
 * byte-exact at -O0; needed sub-file for per-file optimisation override).
 * func_00011D70 onwards split out to bootup_uso_tail3a_bot.c (still -O2 -g3
 * for the rest of this segment until each remaining cluster fn is
 * individually verified at -O0). */
