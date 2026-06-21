#include "common.h"

/* gl_func_00070634 = libultra __osDisableGlobalIntMask-ish (clears bits from the
 * global int-mask word), statically linked into the game_libs USO. Byte-exact
 * masked-twin of matched kernel func_80006250 (kernel_013): disable-int, AND-NOT
 * the (mask & ~0x401) bits out of the global int-mask word, restore-int. IDO 5.3
 * -O1, spliced into game_libs_post1c.c.o via REPLACE_FUNC_BODY. Both OS-API
 * callees -> gl_func_00000000; the global int-mask word (kernel D_8000A3E0) ->
 * D_00000000. */
extern int gl_func_00000000();
extern int D_00000000;

void gl_func_00070634(int mask) {
    register int sr = gl_func_00000000();
    D_00000000 &= ~(mask & ~0x401);
    gl_func_00000000(sr);
}
