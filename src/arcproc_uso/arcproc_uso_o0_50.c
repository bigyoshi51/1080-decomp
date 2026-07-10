#include "common.h"

/* -O0 run at 0x50: Quad4 reader accessor template. See
 * feedback_uso_accessor_o0_variant.md. */

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void arcproc_uso_func_00000050(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* -O0 ref-count/check-full at 0xB4 (moved from arcproc_uso_tail1.c).
 * Was 82.3 % cap when compiled at -O2; this file's -O0 override should
 * make the IDO load order (a0[1] before a0[2], spill+reload at every use,
 * trailing `b +1; nop`) match. */
/* 93.33 % NM (28/30 insns identical, 2026-05-03 tightened from 82.3 %).
 *
 * Load-order fix: writing `a0[2] == a0[1] + 1` (target on LEFT of `==`)
 * forces IDO -O0 to evaluate the RHS first, emitting `lw a0[1]; addiu +1;
 * lw a0[2]; bne` — exactly target's order. The original `a0[1] + 1 ==
 * a0[2]` form evaluated RHS first too but with the OTHER side, giving
 * `lw a0[2]; lw a0[1]; addiu` which is wrong order. So the trick here is
 * to put the side you want loaded first on the RIGHT of `==`.
 *
 * Remaining 2-insn diff: an extra unreachable `b epilogue; nop` pair at
 * end of else-body, before the function epilogue. IDO -O0 emits a dead
 * basic-block-end marker after the `return 0` statement's own `b
 * epilogue`. Tried 8 variants:
 *   - Inner `{ register int *p = a0; ... }` block scope - same
 *   - `register int *p` at top + late `p = a0` - same (this one)
 *   - `register int *a0` parameter - loses s0 (frame -0x18, no callee save)
 *   - explicit `if/else` with single `return rv` - introduces more bb's
 *   - `register int *p = a0;` at top + `p` everywhere - changes prologue
 *   - `p[1]++` vs `p[1] += 1` - identical
 *   - `return p[1]++ , 0;` comma operator - identical
 *   - `int rv; ... rv = 0; return rv;` - adds spill/reload (worse)
 *   - 2026-06-01: `ret = 0;` with no final return improves layout to 97.83%
 *     but stores zero to a dead stack slot instead of returning it; not a
 *     valid C body. `return ret;` (plain/register) regresses via spill/reload
 *     or extra s1 save, so no honest route to the merged marker.
 *   - 2026-06-01 source=1 follow-up: explicit `else { ... } return 0;`
 *     adds an extra jump-over-else block (86.5%). Inverting to
 *     `if (a0[2] != a0[1] + 1)` changes the key branch to `beq` and drops to
 *     71.17%, so the original equality/early-return shape is still best.
 *   - 2026-06-01 source=1 follow-up 2: `a0[2] - 1 == a0[1]` compiles
 *     byte-identically to the current best load/order shape and still keeps
 *     the extra dead BBL marker; no new leverage.
 *
 * The dead `b epilogue; nop` appears to be unconditional from C in this
 * shape. Cap-source: IDO -O0 statement-list-end marker that even the
 * compiler's own dead-code elim doesn't strip.
 *
 * Byte-correct status (CORRECTED 2026-05-30): the ROM build is exact via the
 * INCLUDE_ASM #else path (the .s bytes), NOT via INSN_PATCH — the INSN_PATCH
 * that used to collapse the dead BB was REMOVED 2026-05-23 as match-faking (see
 * Makefile line ~253 + feedback_no_instruction_forcing_matches_policy). So the
 * 93.33% is the genuine C-only cap, not a scoring artifact.
 *
 * The diff is one dead BB: IDO -O0 always emits a function-end `b +1` BBL
 * marker; the target MERGES the `return 0` branch into it (`move v0,zero; b+1;
 * nop; epilogue` = 30 insns), but our IDO emits the return-0's own `b epilogue`
 * THEN a separate dead `b+1` marker (32 insns). 8 C variants tested 2026-05-30
 * (register-ptr / direct a0[1]++ / p-for-all / inverted-if / goto-exit /
 * else-block / single-return r): every s0-using form (the target uses s0 for
 * the increment-path pointer, needs `register int *p`) is 32 insns WITH the dead
 * BB; every 30-insn form drops the s0 save and uses t-regs (wrong). The
 * s0+merged-marker combination is not reachable — an IDO -O0 BBL-emission
 * artifact (likely original-IDO-version-specific). Genuine cap; stays NM.
 *
 * 2026-07-10 (agent-f): DEFINITIVE root cause established — see the big
 * characterization block in arcproc_uso_o0_12C.c (this B4 is the identical
 * class). Summary: the trailing `b epilogue; nop` is an unconditional
 * end-of-function marker emitted by ido-static-recomp's ugen at the closing
 * `}` (proven via `cc -S`, attributed to the '}' source line); the redundant
 * consecutive branch is elided only by uopt, which -O0 bypasses. -O0/-O1/-O2
 * sweep: 3/1/1 branches (raising opt removes the marker but destroys the -O0
 * body). Leaf -O0 value-returns match (11D40/78/BC) because a leaf has no
 * epilogue label; this non-leaf class cannot. 17+ shapes + option probes
 * exhausted. Only a corrected cc binary can produce these bytes. */
#ifdef NON_MATCHING
int arcproc_uso_func_000000B4(int *a0, int a1) {
    register int *p;
    gl_func_00000000(a0, a1);
    if (a0[2] == a0[1] + 1) {
        return 1;
    }
    p = a0;
    p[1] += 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/arcproc_uso/arcproc_uso", arcproc_uso_func_000000B4);
#endif
