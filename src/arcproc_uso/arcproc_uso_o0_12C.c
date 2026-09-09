#include "common.h"

extern int gl_func_00000000();

#ifdef NON_MATCHING
/* Refcount decrement/check, 28 target instructions / 0x70. Remains 92.86% NM:
 * IDO 7.1 -O0 matches through return-value generation but emits an extra
 * b-to-epilogue + nop; both earlier return-branch displacements grow by two.
 *
 * 2026-09-09 compiler-phase audit (agent-h):
 * - IDO 5.3 and 7.1 -O0 are byte-identical here.
 * - O1/g2 and O2/g2 skip uopt and fold the redundant branch in assembly,
 *   but fill the jal delay slot and alter the tail (108 bytes, not 112).
 *   Their unassembled ugen output STILL contains all three branches.
 *   Thus the old claim that uopt alone folds it was incorrect.
 * - Wab,-O0 cannot override the generated per-function .option O1.
 * - NR suppresses automatic delay slots, producing incorrect control flow;
 *   RD adds load-hazard nops. Neither is a usable matching configuration.
 * - nopeep/nobopt/noglobal/no_branch_target, C dialect switches, same-line
 *   closing brace, one-line source and K&R definition did not match.
 *
 * No compiler defect or impossibility proof follows from these probes.
 * Keep the real partial C; do not remove instructions or fake an episode.
 * See docs/IDO_CODEGEN.md#o0-extra-branch-phase-audit-12c. */
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
