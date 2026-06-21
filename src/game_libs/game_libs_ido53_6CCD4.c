#include "common.h"

/* gl_func_0006CCD4 = libultra __osPiRawReadIo (io/pirawread.c), statically
 * linked into the game_libs USO. Byte-exact masked-twin of the matched kernel
 * func_80004AC0 (kernel_001.c) -- identical 20-insn body after masking the one
 * collapsed callee. Compiled IDO 5.3 -O1, spliced into game_libs_post1b2c.c.o
 * via REPLACE_FUNC_BODY. The PI-busy probe collapses to the address-0
 * placeholder gl_func_00000000 (jal 0); the uncached cart read (0xA0000000 |
 * devAddr) is a direct-mapped KSEG1 literal stored verbatim in the ROM. */
extern int gl_func_00000000();

int gl_func_0006CCD4(int devAddr, int *data) {
    if (gl_func_00000000() != 0) {
        return -1;
    }
    *data = *(volatile int *)(0xA0000000 | devAddr);
    return 0;
}
