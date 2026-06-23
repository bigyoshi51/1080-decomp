#include "common.h"

/* kernel_022_o1: -O1 carve-out of the kernel_022 functions that are genuinely
 * -O1 (spill-every-local). The file is otherwise -O2 (the bitfield packers
 * func_80008C30/CB4 and the exact-match func_800092B0 REGRESS at -O1). Carved
 * here: func_80009850 (PI raw read, 45->85%) and func_800087B4 (MIPS insn
 * classifier, 44->52%). objdiff is per-function so .ld placement is cosmetic.
 * Verified 2026-06-04 via the mixed-opt diagnostic. */

/* Classifies a MIPS instruction: returns 1 if it is a jump/branch-to-register
 * (opcode J=2 / JAL=3, or SPECIAL JR=8 / JALR=9), else 0.
 * NON_MATCHING: switch-on-opcode form reproduces the TARGET register allocation
 * (opcode home = $a1, phantom -8 frame, no spill) and the EXACT control flow /
 * delay-slot layout. The decode is byte-identical to target EXCEPT the opcode
 * masking: target emits `srl $a1; andi $t6,$a1; or $a1,$t6,$zero` (AND into a
 * temp then copy back to the $a1 home), whereas IDO -O1 emits this body with
 * `srl $a1; andi $a1,$a1` (AND in place). That single allocator decision shifts
 * every temp register number by one and is permuter-immune (24k iters, base
 * score 165, no zero). Genuine IDO -O1 register-renumber cap; logic verified
 * equivalent over the 32-bit input space. */
#ifdef NON_MATCHING
s32 func_800087B4(u32 inst) {
    switch ((inst >> 26) & 0x3F) {
    case 0:
        if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) return 1;
        if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) return 1;
        break;
    case 2:
    case 3:
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);
#endif
