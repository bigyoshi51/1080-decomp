#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern int D_00000000_a;
extern int D_8AE4_mode;
/* 3-diff NM. The 3 diffs are the D_8AE4_mode reads: build emits
 *   lui rX,%hi; lw rX,0(rX)   but target is   lui rX,%hi; lw rX,52(rX)
 * i.e. the symbol must resolve to base+0x34 so %lo bakes 52 into the lw.
 * At -O0 NO C expression produces this 2-insn folded form: `(char*)&D+0x34`
 * and the array-index form both MATERIALIZE the base (lui;addiu;lw, +1 insn,
 * 63 diffs); `*(int*)0x34` drops the lui (lw 52(zero), 1 insn). The only fix
 * is to DEFINE the symbol D_8AE4_mode at base+0x34 (a symbol_addrs / undefined_
 * syms value, the same mechanism that bakes D_0000014C=0x14C in mgrproc), then
 * read it directly. That's a symbol-definition task, not a C change. */

void gl_func_00008AE4(int a0, int a1, int a2, int a3) {
    register int rv;

    gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x0));
    gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0xC));

    if (D_8AE4_mode == 3) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x10));
    }

    if (D_8AE4_mode != 2) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x14));
    }

    if ((D_8AE4_mode != 3) && (D_8AE4_mode != 5)) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x18));
    }

    gl_func_00000000(&D_00000000, 3, 0, 0);
    rv = gl_func_00000000(0, a1, a2, a3);
    gl_func_00000000(a0, 0, rv);
}
