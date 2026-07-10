#include "common.h"

extern int gl_func_00000000();
extern int D_00000148, D_0000014C, D_00000068;

/* -O0 donor for arcproc_uso_func_000005C8 (48-insn / 0xC0 alloc wrapper).
 * Spliced into the -O2 tail1 object via REPLACE_FUNC_BODY (real -O0 output).
 * arcproc is non-Yay0, so the imported R_MIPS HI16/LO16 vs D_00000148/14C/68
 * and the jal-0 + R_MIPS_26 gl_func_00000000 relocs are resolved by the linker
 * (same as the arcproc_uso_o0_748 donor).
 *
 * KEY LEVER (breaks the 2026-06-24 "NOT C-steerable temp-slot" cap): the single
 * reused temp `saved` (holding the two gl_func_00000000(2) results) must home to
 * sp+0x24, but the prior body declared `register int s0;` FIRST, which at -O0
 * grabbed the top local slot 0x24 (unused, s0-resident) and pushed `saved` down
 * to 0x20. Declaring the stack temp `saved` BEFORE the register var gives it the
 * 0x24 slot -> byte-exact. Decl-order slot lever (docs/IDO_CODEGEN.md -O0 kit). */
void arcproc_uso_func_000005C8(int *a0) {
    int saved;
    register int s0;
    saved = gl_func_00000000(2);
    a0[2] = gl_func_00000000(0x38);
    gl_func_00000000(saved);
    saved = gl_func_00000000(2);
    s0 = gl_func_00000000(0, D_00000148, -1, -1);
    a0[0] = s0;
    D_0000014C = s0;
    gl_func_00000000(saved);
    *(int *)((char *)a0[0] + 0x14) = 4;
    D_00000068 = 0;
}
