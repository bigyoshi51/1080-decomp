#include "common.h"

extern int gl_func_00000000();

#ifdef NON_MATCHING
/* -O0 refcount-decrement-and-check (28 insns, 0x70). 2-arg variant of the
 * pattern in mgrproc_uso_func_000000B0: calls gl_func_00000000(a0, a1),
 * decrements *a0, returns 1 if it hit zero else 0.
 *
 * ============================================================================
 * DEFINITIVE ROOT CAUSE (2026-07-10, agent-f) — the "-O0 value-return extra-b"
 * cap. Applies to the WHOLE class: arcproc B4/12C, bootup F81C/11B5C/A14/
 * FC28/FD4C, game_libs 8E48/8FFC/9100 — every NON-LEAF, value-returning,
 * multi-return function compiled at -O0. Do NOT re-run shape sweeps; this is
 * a cc-binary artifact, not a C-shape cap.
 *
 * DIVERGENCE (byte-exact through +0x58; sole defect is the tail):
 *   Everything from prologue through the two return paths is byte-identical
 *   to the target. IDO 7.1 -O0 then emits ONE EXTRA `b epilogue; nop` at the
 *   function's closing brace that the target does not have. The target has
 *   exactly (#returns) branch-to-epilogue insns; ido-static-recomp emits
 *   (#returns + 1). The extra `b` also shifts the epilogue, so the two prior
 *   branch DISPLACEMENTS diverge too — but eliminating the marker fixes all
 *   of it at once. For 12C: 2 returns -> target 2 b's, build 3 b's.
 *
 * PROOF (`cc -S -O0`): the third branch is attributed to the source line of
 * the closing `}` — an unconditional end-of-function fall-through marker to
 * the epilogue label ($33), emitted by ugen regardless of the fact that the
 * immediately-preceding `return 0` already branched to $33:
 *       move  $2,$0        # return 0
 *       b     $33          # return 0's branch      <- target keeps this
 *     # line 9  '}'
 *       b     $33          # END-OF-FUNCTION MARKER  <- ido-static-recomp ADDS
 *     $33: <epilogue>
 *   It appears even for a TRIVIAL single-return non-leaf (`return 1;` -> 2
 *   b's: the return's own + the marker). It is structural, not shape-driven.
 *
 * WHY IT'S UNFIXABLE FROM C: the redundant consecutive `b $33` is elided by
 * uopt (the optimizer), which -O0 BYPASSES entirely. Confirmed by opt-level
 * sweep on this exact body: -O0 = 3 branches, -O1 = 1 branch (29 insns,
 * reordered), -O2 = 1 branch (20 insns). So raising the opt level removes the
 * marker but simultaneously destroys the -O0 body shape (fewer insns, merged
 * tails, different regalloc) — NOT a match route. The target is unambiguously
 * -O0 (spill-everything, reload-at-every-use, 7 stack reloads).
 *
 * WHY LEAF -O0 value-returns DO match (11D40/11D78/11DBC): a leaf has no
 * epilogue label — each return is `jr $31` directly, so there is no shared
 * epilogue for a marker to branch to. The B4/12C class are NON-leaf (they
 * call gl_func_00000000) and MUST have the shared epilogue + marker.
 *
 * 17+ distinct C shapes tested (2026-07-10) — ALL non-leaf multi-return
 * shapes emit >= (#returns + 1) branches:
 *   if/return+return, single-goto, if/else single-return, ternary,
 *   do{}while(0)+break, explicit-else (4 b's), inverted-cond (bne),
 *   switch (4 b's), goto-both (4 b's), nested if/else (4 b's), comma-return,
 *   register-retvar, else-fall (4 b's). Compiler-option probes (-Wo,-bbopt,
 *   -g0, -non_shared) — no effect (branch-merge lives in uopt, off at -O0).
 *   The single-return boolean form `return *a0==0;` emits sltu+xori and
 *   regresses the body (matches memo's 77.68%).
 *
 * CONCLUSION: only a corrected cc binary (one whose ugen elides the trailing
 * redundant branch, as the original 1080 IDO cc did) can produce these bytes.
 * The whole class stays honest NON_MATCHING. Historical PROLOGUE_STEALS /
 * INSN_PATCH workarounds were REMOVED 2026-05-23 as match-faking.
 * Same characterization applies verbatim to arcproc_uso_func_000000B4.
 * ============================================================================ */
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
