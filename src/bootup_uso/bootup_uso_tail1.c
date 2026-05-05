#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F81C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F954);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F9E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FAE8);

#ifdef NON_MATCHING
/* Single-block bit-clear (set=0, mask=8) on `(arg0->field_48) + 0x18`.
 * Same shape as the bootup_uso_o0_F390.c bit-set/clear cluster
 * (func_0000F564 etc.) but with one extra deref on arg0 (asm has
 * `lw a1, 0x48(a0); addiu a1, a1, 0x18` vs the F390 cluster's
 * `addiu a1, a0, 0x18`).
 *
 * O0-blocked: 23 insns / 0x5C with -O0 signals (extra `b +1; nop` at
 * 0xFC14, redundant `or t0, a2, zero` reload, no `register`-promoted
 * reg-only path). bootup_uso_tail1.c is -O2 by default so this wrap
 * won't byte-match; promotion path is the file-split recipe per
 * feedback_uso_accessor_o0_file_split_recipe.md (move to a new
 * bootup_uso_o0_FBCC.c file with OPT_FLAGS := -O0). */
void func_0000FBCC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0[0x48/4] + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FBCC);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);

#ifdef NON_MATCHING
/* 18-insn indirect-call wrapper. Logic verified:
 *   p = a0->field_28; off = (short)p->field_60; (*p->field_64)(a0 + off).
 *
 * BLOCKED: function is -O0-shape (frame -0x28 with s0 spill/reload pattern,
 * dead 'b +1; nop' BB-end marker after the jalr) but lives in
 * bootup_uso_tail1.c which builds at -O2. IDO -O2 inlines my C to 11
 * insns with t-regs only — 7-insn deficit + frame-size mismatch.
 *
 * Promotion path: file split per feedback_o0_cluster_split_with_layout_shim.md
 * (create src/bootup_uso/bootup_uso_o0_FEA0.c with -O0 OPT_FLAGS, update
 * linker script). Deferred — file-split infra change is heavier than
 * one-tick scope. */
void func_0000FEA0(char *a0) {
    char *p = *(char**)(a0 + 0x28);
    ((void(*)(char*))*(int*)(p + 0x64))(a0 + *(short*)(p + 0x60));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000100F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001016C);

