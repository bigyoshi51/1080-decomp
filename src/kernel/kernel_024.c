#include "common.h"



INCLUDE_ASM("asm/nonmatchings/kernel", func_80009AB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009B60);

/* func_80009C30: 4-insn tail (or $t2,$t5,$at; sw $a2,0($t2); jr ra;
 * or $v0,0,0). Uses uninitialized $t5/$at at entry and always returns 0
 * in $v0. Served two roles in the original binary:
 *   (a) Fall-through tail of func_80009B60 (which ends without jr ra;
 *       previous insn sets $t5 = a0->0xC | a1 and $at = 0xA0000000 →
 *       store $a2 at uncached(a0->0xC | a1)). The "return 0" in v0 is
 *       incidental here — parent function returned void.
 *   (b) Called as a standalone function from func_80008AD0 (__rmonHit-
 *       CpuBreak pattern) which expects a pointer return. Since v0=0
 *       and the caller's $s0 = v0, this crashes unless $t5/$at happen
 *       to survive from unrelated prior context — which in practice
 *       they do because the exception handler path never actually
 *       hits this callsite with the current thread list empty.
 * Keep as INCLUDE_ASM. Unmatchable from C (uninitialized-register
 * entry + 2-role semantics) per feedback_cross_function_tail_share.md. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009C30);

/* func_80009C40 split out to kernel_046.c (-O1) */

