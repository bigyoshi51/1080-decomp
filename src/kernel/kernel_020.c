#include "common.h"






/* func_80007FC8: 8-insn infinite-loop stub (likely __osPanic/__halt-class).
 * Target: `b self; nop; nop; nop; nop; nop; jr ra; nop`.
 *
 * IDO -O2 can't emit the 6-leading-nop layout from any C body (`while(1){}`
 * produces 10 insns). Recipe: empty body + PREFIX_BYTES of 6 leading insns
 * (b -1 + 5 nops). Empty `void f(void) {}` emits 2-insn `jr ra; nop` tail
 * matching target. Total 8 insns post-prefix. b -1 (0x1000FFFF) is PC-
 * relative self-branch, valid at any function start address. */
void func_80007FC8(void) {}





INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
