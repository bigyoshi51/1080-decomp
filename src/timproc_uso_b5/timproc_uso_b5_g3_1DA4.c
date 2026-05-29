#include "common.h"

/* Mid-block -O2 -g3 carve-out for timproc_uso_b5_func_00001DA4.
 *
 * The target is `return 1` but with an UNFILLED jr-delay slot:
 *   li v0,1 / jr ra / nop      (plain -O2 emits the filled `jr ra / li v0,1`).
 * IDO `-O2 -g3` disables the reorg delay-slot filler while keeping -O2
 * optimization, reproducing the exact target bytes with no -O0 bloat
 * (docs/IDO_CODEGEN.md#feedback-ido-g3-disables-delay-slot-fill).
 *
 * -g3 can't be applied to the whole timproc_uso_b5.c TU (150+ matched
 * compiled-C functions there have normal filled delay slots and would
 * regress), and this function sits mid-block, so it is compiled in this
 * dedicated -g3 sub-unit, truncated to 0xC bytes, and spliced into the
 * Yay0 block5 .text at offset 0x1DA4 (see the timproc_uso_block5_yay0
 * Makefile rule). */
int timproc_uso_b5_func_00001DA4(void) {
    return 1;
}
