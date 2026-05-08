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
 * pattern as arcproc_uso_func_000000B4 sibling.
 *
 * 2026-05-05: tested 4 more variant shapes hoping to eliminate the extra
 * 8 bytes (2 insns: the join-point `b end; nop` between the if-arm and
 * else-arm exits):
 *   (a) Explicit `else { return 0; }` — 4 dead branches (worse).
 *   (b) `register int rv; if(...) rv=1; else rv=0; return rv;` — uses $s1
 *       successfully but adds a join-point, still 3 branches (same).
 *   (c) `if (*a0 != 0) goto zero_path; return 1; zero_path: return 0;` —
 *       extra `b zero_path` from the else fall-through (worse).
 *   (d) `register int rv; rv = 0; if (...) rv = 1; return rv;` — 2 trailers
 *       (same shape as current).
 * Confirms cap is structural — IDO -O0 emits a join-point branch after
 * any if/else chain that has explicit early return inside the if-arm,
 * regardless of how the else-arm is written. The expected shape (NO
 * join-point, both arms branch directly to epilogue) requires dataflow
 * normalization that IDO -O0 doesn't perform. INSN_PATCH-blocked: would
 * need to grow expected/.o by +8 bytes, which post-cc tooling can't do
 * (only shrink via PROLOGUE_STEALS or overwrite via INSN_PATCH).
 *
 * 2026-05-08 5th variant: single-return shape `return *a0 == 0;` —
 * REGRESSED 92.86% -> 77.68% (-15pp). The boolean cast emits extra
 * sltu+xori sequence at -O0 (vs target's beq-conditional shape).
 * Confirms 4-variant exhaustion was not exhaustive across the boolean-
 * coercion family. Reverted. */
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

/* arcproc_uso_func_0000019C: -O0 size allocator-state update (41 insns, 0xA4).
 * Adds allocation of size a1 to slab at a0. If count==0, store at slot 0;
 * else sum existing allocations and store new at slot=count with value
 * (a1 - sum). Both paths fall through to a0[13] = a1 (cached total).
 *
 * Promoted to exact via if/else fall-through merge (replacing the
 * earlier `if (==0) {store; return}` early-return form). The single
 * 1-byte diff at the early-exit branch displacement (build `b +29` to
 * epilogue vs expected `b +26` to the a0[13] = a1 store) is fixed by
 * letting both arms fall through to the merge. */
void arcproc_uso_func_0000019C(int *a0, int a1) {
    int i, j;
    if (a0[1] == 0) {
        a0[8 + a0[1]] = a1;
    } else {
        i = 0;
        j = 0;
        if (a0[1] > 0) {
            do {
                i += a0[8 + j];
            } while (++j < a0[1]);
        }
        a0[8 + a0[1]] = a1 - i;
    }
    a0[13] = a1;
}
