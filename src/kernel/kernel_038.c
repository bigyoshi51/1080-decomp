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
/* func_80005B10 NEAR-EXACT 2026-06-10 (reloc-aware diff): ALL insn
 * diffs are reloc-false (lui/addiu/jal/lw resolve correctly: D_8000A41C,
 * func_800066B0/66D0, the 0x80003FE0 handler addr); the SOLE real diff
 * is ONE TRAILING NOP -- the build emits 0x144 vs the .s's declared
 * 0x140 (an alignment nop after the jr-ra delay, inside the symbol
 * size). One padding insn from exact; promotion blocked until the nop
 * source is found (kernel ROM is byte-exact -- a +4 symbol would shift
 * the section). Candidate causes: cc .align inside size attribution vs
 * splat's boundary; see MATCHING_WORKFLOW size-attribution entries. */

