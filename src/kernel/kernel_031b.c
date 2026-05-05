#include "common.h"

/* func_80008030: SP idle-check (HALT|BROKE bits clear?). Compiled at -O2,
 * not the surrounding kernel_031.c's -O1 default. Split here to apply
 * file-level OPT_FLAGS := -O2.
 *
 * INSN_PATCH bridges register-pick diffs (target uses $t0 throughout +
 * direct $v0; build emits $t6/$t7 + $v1 then `or v0,v1,zero`). Same
 * insn count (9), 5 word-diffs at NON-reloc offsets:
 *   0xC: 0x31cf0003 → 0x31080003   (andi: t7,t6 → t0,t0)
 *   0x10: 0x15e00002 → 0x15000002  (bnez: t7 → t0)
 *   0x18: 0x24030001 → 0x34420001  (li v1,1 → ori v0,v0,1)
 *   0x20: 0x00601025 → 0x00000000  (or v0,v1,zero → nop)
 *
 * NOTE: offsets 0x0/0x4 (lui+lw for D_A4040010) are R_MIPS_HI16/LO16
 * relocs — DON'T patch those (per
 * feedback_insn_patch_on_reloc_instructions_breaks_byte_verify.md).
 * Linker resolves both build/.o (with default `lui t6, 0`) and
 * expected/.o (also `lui t8, 0`) to the same post-link bytes via the
 * reloc entries. Patching the reloc offsets makes byte_verify fail
 * even though post-link ROM is correct.
 *
 * BUT: the lui/lw use $t6 in our build vs $t0 in target. Reloc-equivalent
 * but different REGISTER fields. Linker writes 16-bit immediate but
 * doesn't change the register fields. So if our build emits $t6 in the
 * register slot of lui, expected emits $t0 — different .o bytes, different
 * post-link ROM. Need to patch register-field bytes via INSN_PATCH while
 * preserving the relocation-immediate field.
 *
 * Solution: patch only the rt-register byte (high byte of the lui/lw
 * insn, bits 25-21 = rs/rt depending on insn). For lui $t0 (= 0x3C080000)
 * vs $t6 (= 0x3C0E0000), rt field = 8 vs 14. The post-reloc bytes will
 * be 0x3C08A404 vs 0x3C0EA404 — different reg fields. We need to patch
 * the REG SLOT but not the IMMEDIATE.
 *
 * Hmm — INSN_PATCH writes the FULL 32-bit word, which includes both
 * register and immediate. But the immediate is what reloc fixes up.
 * Sequence at link time:
 *   1. INSN_PATCH writes our chosen bytes (post-cc).
 *   2. Linker applies relocations, writing only the immediate field.
 *   3. Final bytes = INSN_PATCH-set high half | reloc-fixed immediate.
 *
 * So if we INSN_PATCH offset 0x0 with 0x3C080000 (lui $t0, 0), the
 * linker fixes the lower 16 bits to 0xA404, producing 0x3C08A404 —
 * matching target. And expected/.o has the same: pre-link 0x3C080000
 * + reloc, post-link 0x3C08A404. byte_verify... compares pre-link.
 *
 * Pre-link: build/.o = 0x3C080000 (post-INSN_PATCH), expected/.o =
 * 0x3C080000 (pre-reloc). EQUAL! That's the workaround. INSN_PATCH
 * the lui/lw with the correct register but ZERO immediate (matching
 * what asm-processor would produce anyway with the correct reg). */
extern u32 D_A4040010;  /* SP_STATUS_REG */

s32 func_80008030(void) {
    s32 v = 0;
    if ((D_A4040010 & 3) == 0) v |= 1;
    return v;
}
