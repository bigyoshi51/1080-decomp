#include "common.h"

/* -O1 -mips3 donor for game_libs_func_0006C8AC — byte-identical twin of the
 * landed kernel func_80002BA8 (kernel_056). 64-bit-by-short divmod: outputs
 * *quot and *rem of (val / d) and (val % d). At -O1 -mips3 IDO emits 2
 * sequential ddivu (no CSE), each with break-on-zero check; the 0x60-byte
 * body has NO relocs (self-contained). Spliced into game_libs_post1b2c.c.o
 * via REPLACE_FUNC_BODY (real -O1 -mips3 compiler output, not
 * instruction-forcing). See kernel_056.c for the original. */
void game_libs_func_0006C8AC(u64 *quot, u64 *rem, u64 val, u16 d) {
    *quot = val / d;
    *rem = val % d;
}

/* gl_func_0006C90C — byte-identical twin of landed kernel func_80002C08
 * (kernel_056). Euclidean mod. At -O1 -mips3 IDO keeps arg-homing (39 insns,
 * 0x9c, no relocs); the -O2 standalone form leaf-optimizes to 33 insns, hence
 * this donor must stay -O1. Spliced into game_libs_post1b2c.c.o. */
long long gl_func_0006C90C(long long a, long long b) {
    long long r = a % b;
    if ((r < 0 && b > 0) || (r > 0 && b < 0)) r += b;
    return r;
}
