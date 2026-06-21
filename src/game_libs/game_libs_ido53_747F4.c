#include "common.h"

/* gl_func_000747F4 = libultra __osPiRawWriteIo (io/pirawwrite.c), statically
 * linked into the game_libs USO. Byte-exact masked-twin of matched kernel
 * func_80009C40 (kernel_046): PI-busy probe, then uncached KSEG1 write of data
 * to (devAddr | 0xA0000000). IDO 5.3 -O1, spliced into game_libs_post2b_d.c.o
 * via REPLACE_FUNC_BODY. The busy probe collapses to the address-0 placeholder
 * gl_func_00000000. (Write twin of the landed gl_func_0006CCD4 read.) */
extern int gl_func_00000000();

int gl_func_000747F4(int devAddr, int data) {
    if (gl_func_00000000() != 0) {
        return -1;
    }
    *(volatile int *)(0xA0000000 | devAddr) = data;
    return 0;
}
