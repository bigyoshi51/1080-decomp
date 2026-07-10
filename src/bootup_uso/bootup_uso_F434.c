#include "common.h"

/* -O0 sub-file covering bootup_uso offset 0xF6C4..0xF76B (single function,
 * 42 insns, 0xA8 bytes). Layout shim between bootup_uso_o0_F390.c and
 * bootup_uso_o0_F7F4.c -O0 clusters. The asm has -O0 hallmarks (8-byte
 * a0-spill on every use, dead `b +1; nop` BB-end marker before epilogue,
 * no register caching across statements) so the file-level OPT_FLAGS is
 * -O0 (set in the Makefile). */

extern int func_00000000();
extern struct { int a, b, c; } func_00000188;

/* 42-insn -O0 method dispatcher: optionally invokes a pre-call hook
 * (vtable[0x6C] with arg = base + h_68) when state field 0x2C is zero,
 * runs the USO helper on a0, then optionally invokes a post-call hook
 * (vtable[0x64], h_60) gated by both state-nonzero AND a global-flag
 * predicate read from `func_00000188.c` (USO base 0x188 + 8 = 0x190).
 *
 * MATCHED 2026-07-10 (w50 island sweep, 42/42 words): the old "interleaved
 * schedule not reachable at -O0" cap was cfe DAG-sharing — the whole hook
 * dispatch must be ONE expression statement with the register-m assignment
 * EMBEDDED IN THE ARG (args evaluate first):
 *   (*(int(**)())(m + 0x6C))(*(short*)((m = *(char**)(a0+0x28)) + 0x68) + a0);
 * The arg's trailing `+ a0` then DAG-shares the assignment chain's a0 home
 * reload (t8) => `addu a0,t9,t8` with NO second lw, and the fn-ptr load
 * reads m from $s0 directly and lands in $t9 (jalr target ring slot).
 * Assignment placed in the FN expression instead evaluates the arg with
 * stale m (wrong order AND wrong bytes). Two-statement forms (the old
 * 91.31% body) always reload a0 (+1 word per block). */
void func_0000F6C4(char *a0) {
    register char *m;
    if (*(int*)(a0 + 0x2C) == 0) {
        (*(int(**)())(m + 0x6C))(*(short*)((m = *(char**)(a0 + 0x28)) + 0x68) + a0);
    }
    func_00000000(a0);
    if (*(int*)(a0 + 0x2C) != 0) {
        if (func_00000000(func_00000188.c)) {
            (*(int(**)())(m + 0x64))(*(short*)((m = *(char**)(a0 + 0x28)) + 0x60) + a0);
        }
    }
}
