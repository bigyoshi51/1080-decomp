#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






/* split from kernel_020.c - 2026-06-10 kernel ROM-order relayout */






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
 * NATURAL CEILING: ~entry-0-only NM at ~50% (the alt-entries 1 and 2 are
 * not reachable from a single-entry C body). Was previously documented
 * as "Exact-match path: compile entry 0 from C, use INSN_PATCH to force
 * the hand-scheduled non-branch-likely poll loops (same SP_STATUS cap
 * family as func_80008030), then append jr ra; nop + the two raw
 * relocation-free alt-entry tails with SUFFIX_BYTES" — INSN_PATCH +
 * instruction-appending SUFFIX_BYTES REMOVED 2026-05-23 as match-faking
 * (per feedback_no_instruction_forcing_matches_policy).
 *
 * SP_STATUS write bit decode (SP_STATUS write = SET/CLR bit pairs):
 *   0x82  = 0x80 | 0x02 = set_sig0 + clr_broke
 *   0xC5  = 0xC0 | 0x05 = set_sig1 + set_intr_break + clr_dma_busy + clr_halt
 *   0x125 = 0x100|0x25 = clr_sig1 + clr_sstep + clr_dma_busy + clr_halt
 *
 * Default build is INCLUDE_ASM. */
#ifdef NON_MATCHING
void func_80008054(void) {
    volatile u32* busy;
    volatile u32* statusReg;
    u32 status;

    busy = (volatile u32*)0xA4040018;
loop_busy:
    status = *busy;
    if (status != 0) {
        goto loop_busy;
    }

    statusReg = (volatile u32*)0xA4040010;
    *statusReg = 0x82;
loop_status:
    status = *statusReg;
    status &= 3;
    if (status == 0) {
        goto loop_status;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);
#endif
