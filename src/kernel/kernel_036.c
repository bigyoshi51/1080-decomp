#include "common.h"

extern void* func_80009C30(void);

/* __rmonSendHeader — find free comm slot and configure it */
void __rmonSendHeader(void) {
    register s32* node = (s32*)func_80009C30();
    while (node[1] != -1) {
        if (node[1] == 0) {
            *(s32*)((char*)node + 0x118) = *(s32*)((char*)node + 0x118) & 0xFFFF00FE;
            *(s32*)((char*)node + 0x118) = *(s32*)((char*)node + 0x118) | 0x6C01;
            break;
        }
        node = (s32*)node[3];
    }
}

#ifdef NON_MATCHING
/* func_800073DC is the prologue fragment of the original 31-insn function
 * at ROM 0x800073DC, which splat split into:
 *   - func_800073DC (this file, 7 insns / 0x1C — prologue + first jal,
 *     no jr ra — falls through to next function in linker layout)
 *   - func_800073F8 (kernel_018.c INCLUDE_ASM, 25 insns / 0x64 — body)
 *
 * The full decompiled body lives above as `__rmonSendHeader` (matched 100%
 * per report.json). The INCLUDE_ASM below is residual dead duplicate code
 * emitted at a separate .o offset; removing it would shift downstream .o
 * layout so it stays for now.
 *
 * 2026-05-05 — evaluated PREFIX_BYTES + INSN_PATCH promotion (per
 * `docs/POST_CC_RECIPES.md` and feedback_prefix_bytes_plus_insn_patch_
 * breaks_documented_caps.md): BLOCKED by two combined constraints:
 *   1. The function's `jal func_80009C30` must carry an R_MIPS_26
 *      relocation in the .o for byte_verify against expected/.o. Raw
 *      PREFIX_BYTES are reloc-less, so prefix-encoded jals would produce
 *      correct ROM bytes but mismatch expected/.o at the .o level.
 *   2. Putting the jal in the C body emits a reloc'd jal but also a
 *      full 8-insn prologue+epilogue (0x20), which can't shrink to
 *      target's 7-insn (0x1C) "no-epilogue, falls-through" shape.
 * No recipe combines "function with .o reloc on jal" + "no jr ra
 * epilogue." Combo applicability window narrowed: leading-N insns of
 * any prefix must contain zero reloc'd jal or lui-extern-pair. Stays
 * INCLUDE_ASM-tautology (build/.o byte-correct via #else branch). */
void func_800073DC(void) {
    /* see __rmonSendHeader above — this fragment is its prologue */
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800073DC);
#endif
