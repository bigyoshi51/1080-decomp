#include "common.h"



INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AB0);

/* func_80009B60 (size 0xE0, was 0xD0): merged in former func_80009C30
 * fragment (4-insn fall-through tail at 0x80009C30 — `or t2,t5,at;
 * sw a2,0(t2); jr ra; or v0,0,0`). func_80009C30 was the natural tail of
 * func_80009B60 (its prior insns set t5 = a0->0xC | a1 and at = 0xA0000000,
 * so the merged tail stores a2 at uncached(a0->0xC | a1)).
 * The address 0x80009C30 is re-exported via undefined_syms_auto.txt for
 * cross-function callers (e.g. func_80008AD0/__rmonHitCpuBreak) that
 * jal directly into the shared "store + return 0" tail. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009B60);

/* func_80009C40 split out to kernel_046.c (-O1) */

