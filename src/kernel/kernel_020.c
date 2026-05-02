#include "common.h"






#ifdef NON_MATCHING
/* func_80007FC8: 8-insn infinite-loop stub.
 *   beq $zero,$zero,func_80007FC8   (branch to self — never returns)
 *   nop  (delay slot)
 *   nop nop nop nop nop  (5 unreachable nops)
 *   jr $ra  (unreachable epilogue)
 *   nop  (delay slot)
 *
 * Equivalent C is `void f(void) { while (1) {} }` — but IDO -O2 emits the
 * jr $ra at offset 0x20 with SEVEN intervening nops (function size 0x28),
 * not the target's offset 0x18 with FIVE intervening nops (size 0x20).
 *
 * The two extra middle nops are IDO scheduler alignment padding before the
 * "next basic block" (the unreachable epilogue) — same byte pattern at -O0,
 * -O1, -O2, -O3, with or without dummy stack frames or `for(;;);` /
 * `goto here;` shapes (4 variants tried). Truncating .text to 0x20 only
 * solves the size half — the byte at offset 0x18 still differs (target has
 * `jr $ra` = 0x03E00008, build has `nop` = 0x00000000).
 *
 * Likely an `__osPanic` / `__halt` style stub. Stays INCLUDE_ASM. */
void func_80007FC8(void) {
    while (1) {}
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);
#endif





INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
