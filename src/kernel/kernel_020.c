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
 * produces 10 insns). Previously matched via `void f(void){}` + PREFIX_BYTES
 * (6-insn instruction-appending prefix). PREFIX_BYTES REMOVED 2026-05-27
 * (cleanup of policy violation, was missed by 2026-05-23 sweep) per
 * feedback_no_instruction_forcing_matches_policy — was instruction-appending
 * match-faking, not USO-header data. Function stays NM (INCLUDE_ASM build
 * path); honest unmatched. */
#ifdef NON_MATCHING
void func_80007FC8(void) {}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007FC8);
#endif





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

#ifdef NON_MATCHING
/* func_800081D0: callable continuation of func_8000817C's clear-break path.
 * The entry has no stack-frame setup because func_8000817C falls through
 * into it after saving ra and reserving 0x20 bytes. It is also called
 * directly by the rmon event loop, so normal C cannot express both entry
 * modes in one byte-matching function.
 *
 * 2026-05-17 source-2 exact attempt after func_8000817C land:
 * - Reference search for __rmonClearBreak/rmonClearBreak found no local
 *   libreultra/OoT/Papermario source hit.
 * - Baseline C-only objdiff: 74.13513%. Target begins at the inherited frame
 *   (`addiu a1,4; lui/addiu t3,&rmonbrk_bss_0000`) and later writes the
 *   fetched instruction to caller stack arg slot 0x1C(sp). Natural C emits a
 *   fresh `addiu sp,-0x18; sw ra,0x14(sp)` prologue and relocations at the
 *   wrong offsets, so a full-function INSN_PATCH/PREFIX rewrite would lose
 *   required kernel symbol relocations and is not a valid promotion.
 * - Tried pointer-base locals for `&rmonbrk_bss_0000` / `&D_8001FEF0`:
 *   still 74.13513%.
 * - Tried volatile saved-instruction variants to force the 0x1C(sp) store:
 *   regressed to 65.35135% / 64.54054%.
 * - Tried explicit early-return/goto shape to avoid IDO's beql epilogue
 *   preload: still 74.13513%.
 * - Tried m2c's inherited-stack-arg hint with an 8-arg dummy signature
 *   (`arg7 = inst`): regressed to 67.10811% because IDO spilled incoming
 *   args and shifted the useful relocations later.
 *
 * Keep this as NM until there is a real alt-entry/mid-function-label recipe
 * that can preserve relocations without replacing the whole function body. */
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

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern s32 rmonbrk_bss_0088;
extern void func_80006A50(s32, s32);
extern s32 func_80006A98(s32);
extern void func_800073F8(void *, s32, s32);
/* rmon set-breakpoint (__rmonSetBreak-class). Pick the instruction- or
 * data-breakpoint table (rmonbrk_bss_0088 / _0000 by arg0->unk9), scan its
 * 8-byte slots (offsets 0x8..0x80, addr at +0 / saved-insn at +4) for one holding the target
 * address (arg0->unk10) or a free slot; table full -> -0xA. For a fresh slot,
 * save the original word and patch in a BREAK insn (code = (slot>>3)+0x10) via
 * MMIO (func_80006A50/A98) or direct store + cache flush
 * (func_800031F0/func_80005350), then record the address. Finally send a 0x18
 * reply (func_800073F8). */
s32 func_80008264(void *arg0) {
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 idC; s32 idx; s32 saved; } reply;
    char *var_s1;
    char *var_s2;
    char *var_s3;
    if (*(u8 *)((char *)arg0 + 9) == 1) {
        var_s1 = (char *) &rmonbrk_bss_0088;
        var_s2 = (char *) &rmonbrk_bss_0088 + 8;
        var_s3 = (char *) &rmonbrk_bss_0088 + 0x80;
    } else {
        var_s1 = (char *) &rmonbrk_bss_0000;
        var_s2 = (char *) &rmonbrk_bss_0000 + 8;
        var_s3 = (char *) &rmonbrk_bss_0000 + 0x80;
    }
    while (var_s2 < var_s3) {
        if (*(s32 *)var_s2 == 0) {
            break;
        }
        if (*(s32 *)var_s2 == FW(arg0, 0x10)) {
            break;
        }
        var_s2 += 8;
    }
    if (var_s2 == var_s3) {
        return -0xA;
    }
    if (*(s32 *)var_s2 == 0) {
        if (*(u8 *)((char *)arg0 + 9) == 1) {
            *(s32 *)(var_s2 + 4) = func_80006A98(FW(arg0, 0x10));
            func_80006A50(FW(arg0, 0x10), ((((var_s2 - var_s1) >> 3) + 0x10) & 0xFFFFF) << 6 | 0xD);
        } else {
            *(s32 *)(var_s2 + 4) = *(s32 *)FW(arg0, 0x10);
            *(s32 *)FW(arg0, 0x10) = ((((var_s2 - var_s1) >> 3) + 0x10) & 0xFFFFF) << 6 | 0xD;
            func_800031F0((void *) FW(arg0, 0x10), 4);
            func_80005350((void *) FW(arg0, 0x10), 4);
        }
        *(s32 *)var_s2 = FW(arg0, 0x10);
    }
    reply.zero = 0;
    reply.tag = *(u8 *)((char *)arg0 + 4);
    reply.idx = (var_s2 - var_s1) >> 3;
    reply.idC = FW(arg0, 0xC);
    reply.saved = *(s32 *)(var_s2 + 4);
    func_800073F8(&reply, 0x18, 1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
#endif
