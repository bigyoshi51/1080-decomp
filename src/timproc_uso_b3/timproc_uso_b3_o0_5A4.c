#include "common.h"

extern int gl_func_00000000();
extern int D_00000148;
extern int D_0000014C;
extern int D_00000068;

/* -O0 donor for timproc_uso_b3_func_000005A4 — masked-shape TWIN of the landed
 * timproc_uso_b1_func_000005A4 (46-insn -O0 allocator-wrapper at the same 0x5A4
 * offset). The two target functions are instruction-for-instruction identical
 * except for two immediate constants (b1 uses 0x1, b3 uses 0x2). Spliced into
 * the -O2 main object via REPLACE_FUNC_BODY (real -O0 compiler output, not
 * instruction-forcing); the splice imports the donor HI16/LO16/26 relocs.
 * See timproc_uso_b1_o0_5A4.c + feedback_splice_import_donor_relocs_recipe. */
void timproc_uso_b3_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    register int new_obj = gl_func_00000000(0, D_00000148, 2, arg2);
    *arg0 = (int*)new_obj;
    D_0000014C = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 2;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    D_00000068 = 0;
}
