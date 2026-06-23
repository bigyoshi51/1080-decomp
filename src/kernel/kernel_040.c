#include "common.h"

extern s32 rmonbrk_bss_0000;
extern s32 D_8001FEF4;
extern s32 D_8001FEF0;
extern void func_800031F0(void*, s32);
extern void func_80005350(void*, s32);

/* __rmonSetBreak */
void func_800080D0(s32* arg0, s32* arg1) {
    *((s32*)((char*)&rmonbrk_bss_0000 + 4)) = *arg0;
    *arg0 = 0x40D;
    func_800031F0(arg0, 4);
    func_80005350(arg0, 4);
    *(s32*)&rmonbrk_bss_0000 = (s32)arg0;
    if (arg1 != 0) {
        D_8001FEF4 = *arg1;
        *arg1 = 0x40D;
        func_800031F0(arg1, 4);
        func_80005350(arg1, 4);
        D_8001FEF0 = (s32)arg1;
    }
}

/* func_8000817C: __rmonClearBreak — inverse of __rmonSetBreak above.
 * 21-insn entry block (0x54) that falls through into func_800081D0
 * (37-insn continuation, 0x94). Combined 0xE8 / 58 insns total.
 *
 * Decoded structure (covers BOTH entries 0x817C + 0x81D0):
 *
 *   void __rmonClearBreak(void) {
 *       s32 *saved_a = (s32*)rmonbrk_bss_0000;
 *       if (saved_a != NULL) {
 *           if ((*saved_a & 0xFC00003F) == 0xD) {  // is BREAK opcode?
 *               *saved_a = *((s32*)((char*)&rmonbrk_bss_0000 + 4));  // restore orig
 *               func_800031F0((void*)rmonbrk_bss_0000, 4);  // ICache invalidate
 *               func_80005350((void*)rmonbrk_bss_0000, 4);  // DCache flush
 *           }
 *           rmonbrk_bss_0000 = 0;
 *       }
 *       if (D_8001FEF0 != 0) {
 *           if ((*(s32*)D_8001FEF0 & 0xFC00003F) == 0xD) {
 *               *(s32*)D_8001FEF0 = D_8001FEF4;
 *               func_800031F0((void*)D_8001FEF0, 4);
 *               func_80005350((void*)D_8001FEF0, 4);
 *           }
 *           D_8001FEF0 = 0;
 *       }
 *   }
 *
 * The 0x40D constant from __rmonSetBreak (`*arg0 = 0x40D`) is a BREAK
 * trap instruction (opcode 0xD = SPECIAL/BREAK). Mask 0xFC00003F isolates
 * the opcode-major + opcode-minor bits to detect BREAK.
 *
 * Exact-match path (2026-06-23): the FULL function (both entry blocks) now
 * compiles byte-exact here. TRUNCATE_TEXT=0x194 (Makefile) keeps the whole
 * 0xE8/58-insn body (0x800080D0..0x80008264) instead of clipping at block 1.
 * The mid-function alt-entry label func_800081D0 (jal'd from kernel_018_o2.c
 * and func_8000745C) is exposed in tenshoe.ld as `func_800081D0 =
 * func_8000817C + 0x54` (section-relative so R_MIPS_26 jal relocs resolve).
 * kernel_020_c.c no longer owns func_800081D0 — its INCLUDE_ASM fragment was
 * removed and the orphaned asm/nonmatchings/kernel/func_800081D0.s deleted.
 * Full ROM verified cmp-clean vs baserom.
 *
 * KEY LEVER 1 (named-value-local spill, 2026-06-21): IDO -O1 homes the masked
 * BREAK-test value into a dead phantom stack slot (written once in the bne
 * delay slot, never reloaded). Earlier spellings homed the POINTER instead and
 * filled the wrong delay slot. Naming the dereferenced compare value as its own
 * local — while reading the pointer FRESH (NOT caching it) — reproduces the
 * exact phantom-slot home + delay-slot fill.
 *
 * KEY LEVER 2 (dead-slot coalesce, 2026-06-23): block 2's BREAK-test value must
 * REUSE block 1's slot (0x1C(sp)). Spelling block 2 with its own fresh local
 * (instr_b) gives it a separate slot (0x18(sp)) — one diff word. REUSING the
 * single local `instr_a` for both blocks (their lifetimes don't overlap)
 * coalesces to 0x1C(sp), matching the target's `sw t7,0x1C(sp)`. */
void func_8000817C(void) {
    s32 instr_a;

    if (((s32 *)&rmonbrk_bss_0000)[0] != 0) {
        instr_a = *(s32 *)((s32 *)&rmonbrk_bss_0000)[0];
        if ((instr_a & 0xFC00003F) == 0xD) {
            *(s32 *)((s32 *)&rmonbrk_bss_0000)[0] = ((s32 *)&rmonbrk_bss_0000)[1];
            func_800031F0((void *)((s32 *)&rmonbrk_bss_0000)[0], 4);
            func_80005350((void *)((s32 *)&rmonbrk_bss_0000)[0], 4);
        }
        ((s32 *)&rmonbrk_bss_0000)[0] = 0;
    }

    if (D_8001FEF0 != 0) {
        instr_a = *(s32 *)D_8001FEF0;
        if ((instr_a & 0xFC00003F) == 0xD) {
            *(s32 *)D_8001FEF0 = D_8001FEF4;
            func_800031F0((void *)D_8001FEF0, 4);
            func_80005350((void *)D_8001FEF0, 4);
        }
        D_8001FEF0 = 0;
    }
}
