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

