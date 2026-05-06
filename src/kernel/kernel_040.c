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
 * MATCH BLOCKED: alt-entry pattern. func_800081D0 is externally callable
 * from func_800074A0 / func_8000745C via `jal 0x800081D0`. Standard C-emit
 * can't produce a function whose internal label is also a callable entry —
 * IDO always emits prologue+epilogue at function boundary. Same class as
 * func_80008430 / func_80006698 cross-file alt-entry blockers per
 * docs/PATTERNS.md#feedback-contiguous-fragment-can-be-alt-entry-check-extern-first.
 *
 * Default INCLUDE_ASM build remains exact. Documented for future-pass
 * Ghidra-assisted decode + permuter exploration. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000817C);
