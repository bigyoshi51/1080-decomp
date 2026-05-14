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





#ifdef NON_MATCHING
/* func_80008054: 31-insn (0x7C) bundled libultra SP/MI helper. Contains THREE
 * separately-callable entry points (similar alt-entry cap class as
 * func_8000817C / func_800052F0 / func_80006698):
 *
 *   Entry 0 @ 0x80008054: __osSpDeviceBusy + status reset
 *     while (*SP_DMA_BUSY_REG != 0) ;   // wait for DMA idle
 *     *SP_STATUS_REG = 0x82;             // clear sig0 + broke
 *     while ((*SP_STATUS_REG & 3) == 0) ;// wait for halt|broke set
 *     return;
 *
 *   Entry 1 @ 0x80008098: alt-entry — set status 0xC5, then loop to entry-0's
 *     wait-for-halt loop (.L80008078).
 *     *SP_STATUS_REG = 0xC5;             // clear sig1+intr_break+dma_busy+halt
 *     goto entry-0's wait-for-halt;
 *
 *   Entry 2 @ 0x800080AC: __osSpResetSp/init — final SP reset.
 *     *MI_INTR_MASK_REG = 2;             // clear SP intr mask
 *     *SP_STATUS_REG = 0x125;            // clear sig1+sig0+sstep+dma_busy+halt
 *     return;
 *
 * MATCH BLOCKED: alt-entry pattern — standard C-emit can't produce one symbol
 * with 3 separately-callable entry points. External callers in kernel_*.c
 * likely call entries 1 and 2 directly via `extern void
 * func_80008098(void)`/`func_800080AC(void)`. Same cap class as func_8000817C
 * documented in src/kernel/kernel_040.c.
 *
 * SP_STATUS write bit decode (SP_STATUS write = SET/CLR bit pairs):
 *   0x82  = 0x80 | 0x02 = set_sig0 + clr_broke
 *   0xC5  = 0xC0 | 0x05 = set_sig1 + set_intr_break + clr_dma_busy + clr_halt
 *   0x125 = 0x100|0x25 = clr_sig1 + clr_sstep + clr_dma_busy + clr_halt
 *
 * Default INCLUDE_ASM build remains exact. Documented for future Ghidra-assisted
 * decode + permuter exploration. */
void func_80008054(void) {
    /* Stub — see decoded structure above. Full body lives in INCLUDE_ASM
     * bytes via func_80008054.s. */
}
#else
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
