#include "common.h"

extern int gl_func_00000000();
extern int D_0000014C;

/* -O0 donor for arcproc_uso_func_00000748 — byte-identical sibling of the
 * matched mgrproc_uso_func_000009A8 (27-insn -O0 cleanup wrapper). Spliced into
 * the -O2 main object via REPLACE_FUNC_BODY (real -O0 compiler output). arcproc
 * is non-Yay0, so the imported R_MIPS HI16/LO16 vs D_0000014C (=0x14C) is
 * resolved by the linker. `register int z` lands in the target's shared-zero
 * $s0. See docs/MATCHING_WORKFLOW.md#feedback-replace-func-body-o0-donor. */
void arcproc_uso_func_00000748(int *a0) {
    register int z;
    gl_func_00000000(a0[2]);
    a0[2] = 0;
    gl_func_00000000(a0[0], 3);
    z = 0;
    a0[0] = z;
    D_0000014C = z;
}
