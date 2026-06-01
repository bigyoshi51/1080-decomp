#include "common.h"

/* Mid-block -O2 -g3 carve-out for timproc_uso_b5_func_00008894.
 *
 * Same unfilled-jr-delay return-zero leaf as 000087E8:
 *   move v0,zero / jr ra / nop
 * Plain -O2 fills the delay slot, while -O2 -g3 preserves the unfilled target
 * form. The block5 Makefile rule splices this 0xC-byte sub-unit back at offset
 * 0x8894 after the earlier 1DA4 and 87E8 carve-outs. */
int timproc_uso_b5_func_00008894(void) {
    return 0;
}
