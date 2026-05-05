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
 *
 * The dead `b epilogue; nop` appears to be unconditional from C in this
 * shape. Cap-source: IDO -O0 statement-list-end marker that even the
 * compiler's own dead-code elim doesn't strip.
 *
 * Byte-correct status (verified 2026-05-04): the function IS exact in
 * the actual ROM build. The Makefile's INSN_PATCH overwrites 7 specific
 * bytes (0x40, 0x5C, 0x64-0x74) post-cc to collapse the dead BB-marker
 * into the truncated tail (per feedback_insn_patch_collapses_dead_bb_into_truncated_tail.md
 * + TRUNCATE_TEXT 0xDC). The 93.33% fuzzy is the C-only score under
 * build/non_matching/, which (by the dual-build design in
 * feedback_non_matching_build_for_fuzzy_scoring.md) deliberately excludes
 * post-cc tricks. So 93.33% is the structural fuzzy cap; ROM byte-match
 * is already 100%. Same class as the USO entry-0 trampoline caps
 * (feedback_uso_entry0_trampoline_95pct_cap_class.md) but driven by
 * INSN_PATCH rather than PREFIX_BYTES. */
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
