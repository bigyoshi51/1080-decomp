#include "common.h"
extern int D_00000000;
/* Carved from game_libs_post.c to its own -O2 -g3 unit: this INT-reader
 * emits an UNFILLED jr-delay (lui/lw/jr/nop) only at -g3; post.c is -O2
 * which fills the delay. Byte-verified identical to target. */
int game_libs_func_00070FBC(void) {
    return *(int*)((char*)&D_00000000 + 0x8);
}
