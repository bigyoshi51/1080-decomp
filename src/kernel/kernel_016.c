#include "common.h"



/* func_800065F0 (size 0x5C, was 0x50): merged in former func_80006640
 * fragment (3-insn epilogue at 0x80006640 — `addiu $sp, +0x28; jr $ra; nop`).
 * func_80006640 was the natural tail of func_800065F0 (its body ends at
 * 0x8000663C with `lw $ra, 0x14(sp)`, and the merged epilogue runs
 * 0x80006640..0x80006648). Several other callers — func_800003A8 etc —
 * `jal 0x80006640` directly to reuse the "pop 0x28 + return" sequence
 * (cross-function shared-tail entry). The address is re-exported via
 * undefined_syms_auto.txt for those callers. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800065F0);
