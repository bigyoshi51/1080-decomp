#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

#ifdef NON_MATCHING
/* Two NM causes (both unflippable from C):
 *   1. Leading `beq zero, zero, +0x6F00` (word 0x10006F00) at offset 0 -- USO
 *      loader-patched branch trampoline (per feedback_uso_branch_placeholder_trampoline.md).
 *      The trampoline sends control to a runtime-resolved target far outside
 *      this USO; the body that follows is dead code by construction. Same
 *      pattern as boarder5_uso_func_00000000, eddproc_uso_func_00000000, etc.
 *   2. Body is the int-reader template compiled at -O0 (per
 *      feedback_uso_accessor_template_reuse.md + the -O0 indicators):
 *        - nop in jal delay slot (offset 0x24) instead of useful work
 *        - pointer-indirect reload `addiu t6, sp, 0x18; lw t7, 0(t6)` instead of direct lw
 *        - trailing `b +1; nop` (offsets 0x38/0x3C) before epilogue
 *      Per feedback_yay0_uso_blocks_file_split_recipe.md, file-splitting for
 *      per-function -O0 doesn't apply to Yay0-compressed USOs. arcproc_uso
 *      is NOT Yay0 -- but a per-function -O0 split for a single 0x4C-byte
 *      accessor isn't worth the file-split tax. */
void arcproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_00000000);
#endif
