#include "common.h"

/* gl_func_0006FFE4 = libultra __osSetGlobalIntMask (os/setglobalintmask.c),
 * statically linked into the game_libs USO. Byte-exact masked-twin of matched
 * kernel func_800061F0 (kernel_011_b): disable-int, OR mask into the global
 * int-mask word, restore-int. IDO 5.3 -O1, spliced into game_libs_post1b2c.c.o
 * via REPLACE_FUNC_BODY. Both OS-API callees collapse to the address-0
 * placeholder gl_func_00000000; the global int-mask word (kernel D_8000A3E0)
 * maps to the zero-resolving global D_00000000. */
extern int gl_func_00000000();
extern int D_00000000;

void gl_func_0006FFE4(int mask) {
    register int sr = gl_func_00000000();
    D_00000000 |= mask;
    gl_func_00000000(sr);
}
