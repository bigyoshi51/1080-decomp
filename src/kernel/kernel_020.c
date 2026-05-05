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





INCLUDE_ASM("asm/nonmatchings/kernel", func_80008054);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800081D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008264);
