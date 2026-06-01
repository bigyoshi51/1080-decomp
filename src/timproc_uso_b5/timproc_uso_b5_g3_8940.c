#include "common.h"

/* Mid-block -O2 -g3 carve-out for timproc_uso_b5_func_00008940.
 *
 * Same unfilled-jr-delay return-zero leaf as 000087E8 and 00008894:
 *   move v0,zero / jr ra / nop
 * The block5 Makefile rule splices this 0xC-byte sub-unit back at offset
 * 0x8940 after the earlier 1DA4, 87E8, and 8894 carve-outs. */
int timproc_uso_b5_func_00008940(void) {
    return 0;
}
