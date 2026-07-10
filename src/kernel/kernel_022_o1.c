#include "common.h"

/* kernel_022_o1: -O1 carve-out of the kernel_022 functions that are genuinely
 * -O1 (spill-every-local). The file is otherwise -O2 (the bitfield packers
 * func_80008C30/CB4 and the exact-match func_800092B0 REGRESS at -O1). Carved
 * here: func_80009850 (PI raw read, 45->85%) and func_800087B4 (MIPS insn
 * classifier, 44->52%). objdiff is per-function so .ld placement is cosmetic.
 * Verified 2026-06-04 via the mixed-opt diagnostic. */

/* Classifies a MIPS instruction: returns 1 if it is a jump/branch-to-register
 * (opcode J=2 / JAL=3, or SPECIAL JR=8 / JALR=9), else 0.
 * EXACT 2026-07-10 (37/37) at IDO 5.3 -O1 — unit flipped wholesale to
 * $(IDO53_DIR)/cc. The old "genuine IDO -O1 register-renumber cap" (target
 * `srl $a1; andi $t6,$a1; or $a1,$t6,$zero` AND-into-temp-then-copy-back vs
 * 7.1's `andi $a1,$a1` AND-in-place, permuter-immune 24k iters) is the
 * 7.1-only copy-propagation fold — 5.3 -O1 emits the temp+copy-back form
 * from this identical C (3rd crack of the class; see docs/IDO_CODEGEN.md
 * 5.3-vs-7.1 residual-class discriminator, func_80007564/func_80008264). */
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
