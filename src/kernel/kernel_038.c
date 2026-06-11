#include "common.h"

extern s32 D_80003FE0;
extern s32 D_8000A41C;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);

/* osCreateThread */
void func_80005B10(s32* t, s32 id, void* entry, s32 arg, void* sp, s32 p) {
    register s32 saveMask;
    /* u32: ROM emits srl (not sra) for (mask & 0x3F0000) >> 16 — the old
     * s32 decl was ONE WORD off ROM (sra), caught in the 2026-06-10 kernel
     * relayout audit. */
    u32 mask;
    t[5] = id;
    t[1] = p;
    t[0] = 0;
    t[2] = 0;
    *(s32*)((char*)t + 0x11C) = (s32)entry;
    *(s64*)((char*)t + 0x38) = (s64)arg;
    *(s64*)((char*)t + 0xF0) = (s64)(s32)sp - 16;
    *(s64*)((char*)t + 0x100) = (s64)(s32)&D_80003FE0;
    mask = 0x3FFF01;
    *(s32*)((char*)t + 0x118) = 0xFF03;
    *(s32*)((char*)t + 0x128) = (mask & 0x3F0000) >> 16;
    *(s32*)((char*)t + 0x12C) = 0x01000800;
    *(s32*)((char*)t + 0x18) = 0;
    *(u16*)((char*)t + 0x10) = 1;
    *(u16*)((char*)t + 0x12) = 0;
    saveMask = func_800066B0();
    *(s32*)((char*)t + 0x0C) = D_8000A41C;
    D_8000A41C = (s32)t;
    func_800066D0(saveMask);
}
/* func_80005B10 (osCreateThread): ALREADY MATCHED -- this C is the
 * real build path (no wrap) and the kernel ROM is byte-exact with it.
 * The report's 98.75 was an ARTIFACT: the NM-path .o goes through
 * asm-processor, which 16-aligns .text (0x150) and attributes a pad
 * nop to the symbol (0x144 vs true 0x140). Fixed via
 * NON_MATCHING_TRUNCATE_TEXT := 0x140 in the Makefile. All other insn
 * "diffs" were reloc-false. */

