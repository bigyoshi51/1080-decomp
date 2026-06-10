#include "common.h"

/* kernel_022_o1: -O1 carve-out of the kernel_022 functions that are genuinely
 * -O1 (spill-every-local). The file is otherwise -O2 (the bitfield packers
 * func_80008C30/CB4 and the exact-match func_800092B0 REGRESS at -O1). Carved
 * here: func_80009850 (PI raw read, 45->85%) and func_800087B4 (MIPS insn
 * classifier, 44->52%). objdiff is per-function so .ld placement is cosmetic.
 * Verified 2026-06-04 via the mixed-opt diagnostic. */

/* Classifies a MIPS instruction: returns 1 if J/JAL/JR/JALR, else 0.
 * NON_MATCHING: IDO picks $v0 for opcode register; target uses $a1.
 * Logic identical, 37 insts, register allocation differs. */
#ifdef NON_MATCHING
s32 func_800087B4(u32 inst) {
    u32 opcode = (inst >> 26) & 0x3F;
    if (opcode == 0) {
        if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) return 1;
        if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) return 1;
        return 0;
    }
    if (opcode == 2 || opcode == 3) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);
#endif
