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
 *   - func_800073DC (this file, 7 insns / 0x1C — prologue + first jal)
 *   - func_800073F8 (kernel_018.c INCLUDE_ASM, 25 insns / 0x64 — body + epilogue)
 *
 * The full decompiled body lives above as `__rmonSendHeader` (matched 100%
 * per report.json) — that is the canonical source-of-truth for these bytes.
 * The INCLUDE_ASM below is residual dead duplicate code emitted at a separate
 * .o offset; removing it would shift downstream .o layout so it stays for now.
 *
 * Stub body documents the fragment relationship for grep discoverability;
 * not a real decode (the actual semantics are in __rmonSendHeader). */
void func_800073DC(void) {
    /* see __rmonSendHeader above — this fragment is its prologue */
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800073DC);
#endif
