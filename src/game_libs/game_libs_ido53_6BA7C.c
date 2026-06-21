#include "common.h"

/* gl_func_0006BA7C = libultra __osPiRawReadIo variant (PI status spin + uncached
 * cart read), statically linked into the game_libs USO. Byte-exact masked-twin
 * of matched kernel func_800029B0 (kernel_045): spin while PI_STATUS & 3, then
 * read the KSEG1-uncached cart word ((D | devAddr) | 0xA0000000) into *out.
 * IDO 5.3 -O1, spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY. The
 * cart-base global (kernel D_80000308) maps to the zero-resolving D_00000000;
 * PI_STATUS is a direct 0xA4600010 literal. */
#define PI_STATUS (*(volatile unsigned int *)0xA4600010)
extern int D_00000000;

int gl_func_0006BA7C(unsigned int devAddr, unsigned int *out) {
    char pad[4];
    register unsigned int s;
    s = PI_STATUS;
    if (s & 3) {
        do { s = PI_STATUS; } while (s & 3);
    }
    *out = *(unsigned int *)(((unsigned int)D_00000000 | devAddr) | 0xA0000000);
    return 0;
}
