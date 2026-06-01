#include "common.h"

/* Mid-block -O2 -g3 carve-out for timproc_uso_b5_func_000087E8.
 *
 * The target is `return 0` with an unfilled jr-delay slot:
 *   move v0,zero / jr ra / nop
 * Plain -O2 fills the delay slot, while -O2 -g3 keeps the optimized leaf shape
 * but disables the reorg filler. The block5 Makefile rule splices this 0xC-byte
 * sub-unit back at offset 0x87E8. */
int timproc_uso_b5_func_000087E8(void) {
    return 0;
}
