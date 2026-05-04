#include "common.h"

extern int gl_func_00000000();

#ifdef NON_MATCHING
/* -O0 refcount-decrement-and-check (28 insns, 0x70). 2-arg variant of the
 * pattern in mgrproc_uso_func_000000B0: calls gl_func_00000000(a0, a1),
 * decrements *a0, returns 1 if it hit zero else 0.
 *
 * Match: 92.86% (re-confirmed 2026-05-04 via unwrap-and-rebuild test per
 * feedback_nm_wrap_99pct_may_be_silently_exact.md — cap is REAL, not
 * stale; current emit still 92.86%, slight drift from prior 92.68%).
 *
 * Sole structural diff: trailing dead `b +1; nop` at end of function (target
 * skips this since the natural fall-through reaches epilogue with no jump).
 * IDO -O0 emits `b epilogue` after BOTH return paths; the second one is
 * dead since PC+4 IS the epilogue. C-side cannot eliminate this without
 * shrinking the function past TRUNCATE_TEXT.
 *
 * Cap stands at 92.86% (1-insn dead-branch trailing). Same -O0 epilogue
 * pattern as arcproc_uso_func_000000B4 sibling. */
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

#ifdef NON_MATCHING
/* arcproc_uso_func_0000019C: -O0 size allocator-state update (41 insns, 0xA4).
 * Adds a new allocation of size `a1` to the slab at `a0`:
 *   - If a0[1] (count) == 0: a0[8 + a0[1]] = a1; return.
 *   - Else: sum existing allocations a0[8..8+count], place new at index
 *     `count` with value `a1 - sum`, set a0[13] = a1 (cached current total).
 *
 * -O0 markers: addiu sp,-8 (tiny frame for 2 stack-resident locals i/j at
 * sp+0x4/sp+0x0), all loads/stores of locals via $sp, trailing dead `b +1;
 * nop` before epilogue. Sibling-of arcproc_uso_func_0000012C in this file.
 *
 * 2026-05-03 LIFTED 65.92 -> 95.0 % NM via THREE C-form changes:
 *   1. EARLY-RETURN form `if (==0) {store; return}` instead of if/else
 *      flips bnez/beqz arm to match target. (65.9 -> 75.0%)
 *   2. SAME-EXPRESSION early-return `a0[8 + a0[1]] = a1` (with index
 *      recomputed even though a0[1]==0) prevents IDO from constant-folding
 *      to `a0[8]`. (no % change but matched insns 4-7)
 *   3. ENTRY-GUARDED do-while `if (a0[1] > 0) { do {...} while (++j < N); }`
 *      emits `blez` entry guard + `slt+bnez` back-edge with `++j` keeping
 *      j in t8 across the back-edge slt (vs `j++; while(...)` which spills).
 *      (75.0 -> 88.5 -> 95.0%)
 *
 * Residual ~5pp is the trailing dead `b +1; nop` IDO -O0 emits but mine
 * doesn't (function emits 2 fewer insns). Same TRUNCATE_TEXT-style cap
 * as 0x12C sibling. Acceptable. */
void arcproc_uso_func_0000019C(int *a0, int a1) {
    int i, j;
    if (a0[1] == 0) { a0[8 + a0[1]] = a1; return; }
    i = 0;
    j = 0;
    if (a0[1] > 0) {
        do {
            i += a0[8 + j];
        } while (++j < a0[1]);
    }
    a0[8 + a0[1]] = a1 - i;
    a0[13] = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_0000019C);
#endif
