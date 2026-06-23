#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






/* split from kernel_020.c - 2026-06-10 kernel ROM-order relayout */


/* func_800081D0: the no-prologue CONTINUATION (second half) of the single
 * logical function __rmonClearBreak. The matching bytes for 0x800081D0..0x80008264
 * are emitted by the full C body of func_8000817C in kernel_040.c (verified
 * byte-exact, reloc-correct). kernel_040.c.o now compiles the WHOLE function
 * (TRUNCATE_TEXT=0x194) so the continuation is real compiled C, not asm.
 * The mid-function entry label func_800081D0 (jal'd from kernel_018_o2.c /
 * func_8000745C) is provided as a fixed address symbol in symbol_addrs.txt —
 * splat would emit the same glabel. There is no standalone C body here because
 * the entry has no stack frame of its own (it reuses func_8000817C's frame). */

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
 * reply (func_800073F8).
 *
 * STATUS (2026-06-23, agent-e): structurally exact NM. -O1 file. The `register`
 * keyword pins arg0->s0 + the 3 table pointers->s1/s2/s3 (the saved-reg pin is an
 * -O1 lever; ignored at -O2), and reversing the loop-compare operand order
 * (FW(s0,0x10) == *var_s2) fixes the commutative load-order. RESIDUAL (permuter-
 * immune coloring cap): branch-1 (free-slot, MMIO path) passes the BREAK-insn
 * value as call-arg $a1 — the target computes each op (sra/and/sll/ori) into a
 * fresh temp and copies back `move $a1,tN` (4 redundant moves), interleaving the
 * saved-insn store into the gap; IDO at -O1 folds these in place for us, so we
 * emit 4 words fewer. Those 4 missing moves renumber every downstream temp and
 * shift the reply-struct frame slots — all remaining diffs trace to this one
 * cause. No clean C form synthesizes redundant arg-reg copies at -O1; permuter
 * can't add insns to close a size shortfall (see docs/IDO_CODEGEN.md "AND->temp
 * ->copy back ... permuter-immune"). Branch-2 (cache-flush path) stores the value
 * to memory and has NO copy-back, confirming the arg-reg dataflow is the trigger. */
s32 func_80008264(void *arg0) {
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 idC; s32 idx; s32 saved; } reply;
    register void *s0 = arg0;
    register char *var_s1;
    register char *var_s2;
    register char *var_s3;
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
        if (FW(s0, 0x10) == *(s32 *)var_s2) {
            break;
        }
        var_s2 += 8;
    }
    if (var_s2 == var_s3) {
        return -0xA;
    }
    if (*(s32 *)var_s2 == 0) {
        if (*(u8 *)((char *)arg0 + 9) == 1) {
            *(s32 *)(var_s2 + 4) = func_80006A98(FW(s0, 0x10));
            func_80006A50(FW(s0, 0x10), ((((var_s2 - var_s1) >> 3) + 0x10) & 0xFFFFF) << 6 | 0xD);
        } else {
            *(s32 *)(var_s2 + 4) = *(s32 *)FW(s0, 0x10);
            *(s32 *)FW(s0, 0x10) = ((((var_s2 - var_s1) >> 3) + 0x10) & 0xFFFFF) << 6 | 0xD;
            func_800031F0((void *) FW(s0, 0x10), 4);
            func_80005350((void *) FW(s0, 0x10), 4);
        }
        *(s32 *)var_s2 = FW(s0, 0x10);
    }
    reply.zero = 0;
    reply.tag = *(u8 *)((char *)s0 + 4);
    reply.idx = (var_s2 - var_s1) >> 3;
    reply.idC = FW(s0, 0xC);
    reply.saved = *(s32 *)(var_s2 + 4);
    func_800073F8(&reply, 0x18, 1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
#endif
