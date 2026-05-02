#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

#ifdef NON_MATCHING
/* Two NM causes:
 *   1. Leading `beq zero, zero, +0x6F00` (word 0x10006F00) at offset 0 -- USO
 *      loader-patched branch trampoline (per feedback_uso_branch_placeholder_trampoline.md).
 *      The trampoline sends control to a runtime-resolved target far outside
 *      this USO; the body that follows is dead code by construction. Same
 *      pattern as boarder5_uso_func_00000000, eddproc_uso_func_00000000, etc.
 *      Blocked by feedback_prefix_sidecar_symbol_collision.md — leading-pad
 *      sidecars need linker-level symbol-table patching that the project
 *      doesn't yet have.
 *   2. Body IS the int-reader template at -O0. VERIFIED 2026-05-02 by
 *      adding `OPT_FLAGS := -O0` to arcproc_uso.c.o + building with
 *      `CPPFLAGS=-DNON_MATCHING`: the C body emits BYTE-IDENTICAL 19 insns
 *      matching target's offsets 0x4..0x4C exactly (prologue, lui+addiu &D,
 *      addiu sp+0x18 a1, li 4 a2, jal+nop, addiu t6 sp+0x18, lw t7, lw t8
 *      sp+0x20, sw t7, b+1, nop, lw ra, addiu sp, jr ra, nop). Only the
 *      trampoline at offset 0 remains unmatched. So the moment a leading-
 *      pad-sidecar mechanism lands, this function will reach exact match
 *      with: standard int-reader C template + `OPT_FLAGS := -O0` Makefile
 *      override + the trampoline injected via the new sidecar.
 *
 * Status: keep INCLUDE_ASM until leading-pad-sidecar tooling exists. */
void arcproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000000);
#endif
