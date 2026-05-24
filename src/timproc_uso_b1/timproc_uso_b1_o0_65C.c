#include "common.h"

extern int gl_func_00000000();
extern int D_0000014C;

/* RELOC-BLIND CAP (residual 0.05% = one instruction field).
 * Target: `lui at,0; sw s0,0x14c(at)` — a 2-insn symbol-store with 0x14C baked
 * into the %lo field. The reloc-blind expected/.o is post-link (relocs applied
 * then stripped), so that field is literal 0x14C.
 * Our donor splice drops relocs (matching reloc-blind expected, same as the
 * `jal 0` which baked to 0 and DOES match). So the residual field must come from
 * the unlinked instruction itself. No IDO-emittable C produces 2-insn-with-field
 * -0x14C:
 *   - `D_0000014C` (extern symbol)  -> 2 insns but field=0 (offset is in the
 *     symbol value, applied by the dropped reloc).  [used here, best form]
 *   - `&D_00000000 + 0x14C`         -> 3 insns at -O0 (base materialized first).
 *   - `*(int*)0x14C`                -> 1 insn (zero-relative, lui dropped).
 * Real fix is the spimdisasm USO-reloc migration (expected/ becomes reloc-aware),
 * not a per-fn C change. See docs/MATCHING_WORKFLOW.md reloc-blind-donor entry. */
void timproc_uso_b1_func_0000065C(int *a0) {
    register int zero;
    gl_func_00000000((int*)a0[0], 3);
    zero = 0;
    a0[0] = zero;
    D_0000014C = zero;
}
