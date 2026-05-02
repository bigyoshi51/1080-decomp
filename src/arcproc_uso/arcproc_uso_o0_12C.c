#include "common.h"

extern int gl_func_00000000();

#ifdef NON_MATCHING
/* -O0 refcount-decrement-and-check (28 insns, 0x70). 2-arg variant of the
 * pattern in mgrproc_uso_func_000000B0: calls gl_func_00000000(a0, a1),
 * decrements *a0, returns 1 if it hit zero else 0.
 *
 * Match: 85.71% (24/28 insns). All four arg-spill+reload, jal-with-unfilled-
 * delay, s0-via-register-keyword, decrement-via-t6/t7/t8, bne+arm-layout
 * MATCH. Sole diff: target's epilogue starts at offset 0x5C with no extra
 * dead branch; mine emits a trailing `b +1; nop` at 0x5C-0x60 then puts the
 * epilogue at 0x64. The extra `b zero, zero, +1` is IDO -O0's implicit "end-
 * of-function falls through to epilogue" goto when the last statement is
 * `return 0;` after an `if (...) return 1;`.
 *
 * Tried (2026-05-02):
 *   - Plain `if (==) return 1; return 0;` → 85.71% (extra b at 0x5C)
 *   - `if (!=) return 0; return 1;` (swap arms) → SAME 85.71% (still extra b)
 *   - Explicit `if (==) {return 1;} else {return 0;}` → REGRESSED to ~82%
 *     (added one more `b` from else-branch jump)
 *
 * The 24/28 cap matches the same -O0 epilogue-extra-jump pattern documented
 * in arcproc_uso_func_000000B4 (sibling, ~85% with same shape). */
int arcproc_uso_func_0000012C(int *a0, int a1) {
    register int *p;
    gl_func_00000000(a0, a1);
    p = a0;
    *p -= 1;
    if (*a0 == 0) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000012C);
#endif
