#include "common.h"



INCLUDE_ASM("asm/nonmatchings/kernel", func_800065F0);

/* func_80006640: `addiu $sp, $sp, +0x28; jr $ra; nop` — a 3-insn EPILOGUE-
 * only stub with no prologue. This is not a standalone function; it's the
 * tail of func_800065F0 (which ends at 0x8000663C with `lw $ra, 0x14(sp)`
 * and was declared size 0x50 = ends at 0x80006640, so the shared-tail code
 * at 0x80006640 is physically contiguous with its natural end at
 * 0x80006648). Other callers — notably func_800003A8 (which is 100%
 * matching) — `jal 0x80006640` directly to reuse the "pop 0x28 bytes from
 * sp and return" sequence. This is a cross-function tail-share analogue to
 * feedback_cross_function_tail_share.md, but in the other direction:
 * instead of sharing the zero-return epilogue of an adjacent function,
 * multiple callers jal directly into func_800065F0's sp-pop+return tail.
 *
 * Not matchable as a standalone function from IDO C — no IDO -O level
 * emits a function starting with `addiu $sp, +N` (positive sp adjust is
 * the epilogue marker, not an entry prologue). Keep as INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006640);
