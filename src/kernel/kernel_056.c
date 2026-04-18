#include "common.h"

/* 64-bit libgcc-style helpers. Compile at -O2 -mips3 so that IDO inlines the
 * d-arithmetic instructions (dsrlv/dsllv/ddivu/dmultu/...) instead of
 * emitting `jal __ull_rshift` back to themselves.
 *
 * Warning "should not be used for ucode 32-bit compiles" is expected. */

u64 func_80002A10(u64 a, u64 b) { return a >> b; }  /* __ull_rshift */
u64 func_80002A3C(u64 a, u64 b) { return a % b; }   /* __ull_rem */
u64 func_80002A78(u64 a, u64 b) { return a / b; }   /* __ull_div */
u64 func_80002AB4(u64 a, u64 b) { return a << b; }  /* __ll_lshift */
u64 func_80002AE0(u64 a, u64 b) { return a % b; }   /* duplicate of A3C */
s64 func_80002B1C(s64 a, s64 b) { return a / b; }   /* __ll_div */
s64 func_80002B78(s64 a, s64 b) { return a * b; }   /* __ll_mul */
s64 func_80002C08(s64 a, s64 b) {                   /* Euclidean mod */
    s64 r = a % b;
    if ((r < 0 && b > 0) || (r > 0 && b < 0)) r += b;
    return r;
}
s64 func_80002CA4(s64 a, s64 b) { return a >> b; }  /* __ll_rshift */
