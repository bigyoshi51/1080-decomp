#include "common.h"






/* 8-insn infinite-loop stub (likely __osPanic/__halt-class):
 *   b self; nop; nop; nop; nop; nop; jr ra; nop
 *
 * Promotion via PREFIX_BYTES alone (no INSN_PATCH needed) per
 * feedback_prefix_bytes_plus_insn_patch_breaks_documented_caps.md
 * applicability window — 8-insn function with 2-insn-tail (jr ra; nop)
 * matches empty-void C body's natural emit. Recipe:
 *   - C body: `void f(void) {}` emits 2 insns (jr ra; nop = 8 bytes)
 *   - PREFIX_BYTES: 6 leading insns (b -1; nop; nop; nop; nop; nop = 24 bytes)
 *
 * b -1 (0x1000FFFF) is PC-relative self-branch — target = PC + 4 + (-1)*4
 * = PC, valid at any function start address. */
void func_80007FC8(void) {}





#ifdef NON_MATCHING
/* func_80008054: 4-FUNCTION BUNDLE (0x7C / 31 insns) — RSP/SP control.
 * Splat-bundled, can't be split per
 * feedback_uso_split_fragments_breaks_expected_match.md (kernel applies
 * same way). Sub-functions:
 *
 *   F1 @ 0x8054-0x8076: 9 insns. Wait-for-DMA-idle then write 0x82 to
 *     SP_STATUS (clear interrupt). Falls THROUGH to F2 (no own jr ra).
 *       while (*SP_DMA_BUSY_REG != 0) {}
 *       *SP_STATUS_REG = 0x82;
 *       (fall through to F2)
 *
 *   F2 @ 0x8078-0x8094: 7 insns. Wait until SP_STATUS bits 0|1 set, then
 *     return. (SP_STATUS_HALT | SP_STATUS_BROKE = "RSP halted/broken".)
 *       while ((*SP_STATUS_REG & 3) == 0) {}
 *       return;
 *
 *   F3 @ 0x8098-0x80A8: 5 insns. Write 0xC5 to SP_STATUS, then `b F2`
 *     (i.e., wait for halt). The 0xC5 = SP_STATUS_HALT-clear |
 *     SP_STATUS_BROKE-clear | SP_STATUS_INTR-clear | SP_STATUS_TASKDONE
 *     | SP_STATUS_INTR_BREAK (per N64 SP doc). Tail-shares F2's wait.
 *       *SP_STATUS_REG = 0xC5;
 *       /\* falls through to F2 via b instruction \*/
 *
 *   F4 @ 0x80AC-0x80CC: 8 insns. Write 0x2 to MI_INTR_MASK_REG (0xA430000C)
 *     to enable SP interrupt, then write 0x125 to SP_STATUS, jr ra.
 *       *MI_INTR_MASK_REG = 0x2;     /\* enable SP interrupt \*/
 *       *SP_STATUS_REG = 0x125;
 *       return;
 *
 * Whole bundle is RSP startup/halt/dma-control. F1+F2 are likely a
 * "wait-for-RSP-completion" routine; F3 is a "kick-RSP" entry; F4 is
 * "init-RSP-interrupt".
 *
 * NM-blocked by 4-function-bundle structure: cross-function fall-through
 * (F1→F2 via no-jr-ra) and tail-share (F3→F2 via `b`) require IDO to
 * emit ALL 4 functions in this exact byte-layout, which standard C
 * cannot reproduce. Bundle stays INCLUDE_ASM. Documented for future
 * split-fragments + per-sub-function recipe attempt. */
void func_80008054(void) {}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
