#include "common.h"

/* 64-bit libgcc-style helpers. Compile at -O2 -mips3 so that IDO inlines the
 * d-arithmetic instructions (dsrlv/dsllv/ddivu/dmultu/...) instead of
 * emitting `jal __ull_rshift` back to themselves.
 *
 * Warning "should not be used for ucode 32-bit compiles" is expected. */

u64 func_80002A10(u64 a, u64 b) {
    return a >> b;
}
