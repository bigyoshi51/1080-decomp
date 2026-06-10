#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);






/* split from kernel_020.c - 2026-06-10 kernel ROM-order relayout */


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
