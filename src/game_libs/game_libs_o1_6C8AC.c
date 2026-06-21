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
