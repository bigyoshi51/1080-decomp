#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






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

#ifdef NON_MATCHING
/* func_800081D0: callable continuation of func_8000817C's clear-break path.
 * The entry has no stack-frame setup because func_8000817C falls through
 * into it after saving ra and reserving 0x20 bytes. It is also called
 * directly by the rmon event loop, so normal C cannot express both entry
 * modes in one byte-matching function. */
void func_800081D0(void) {
    func_80005350((void*)rmonbrk_bss_0000, 4);
    rmonbrk_bss_0000 = 0;

    if (D_8001FEF0 != 0) {
        s32 *saved = (s32*)D_8001FEF0;

        if ((*saved & 0xFC00003F) == 0xD) {
            *saved = D_8001FEF4;
            func_800031F0((void*)D_8001FEF0, 4);
            func_80005350((void*)D_8001FEF0, 4);
        }
        D_8001FEF0 = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
