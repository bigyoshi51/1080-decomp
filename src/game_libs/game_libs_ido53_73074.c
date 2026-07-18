#include "common.h"

/* gl_func_0007307C = libultra osPiRawWriteIo variant (PI status spin +
 * uncached cart word write), statically linked into the game_libs USO.
 * Write-side twin of gl_func_0006BA7C __osPiRawReadIo (same donor recipe).
 * BOUNDARY FIX: splat's game_libs_func_00073074 (0x8, no jr ra:
 * `lui $t6,0xA460; lw $a2,0x10($t6)`) was this function's HOISTED HEAD —
 * IDO 5.3 -O1 schedules the first PI_STATUS_REG read before the addiu-sp
 * prologue, and splat split at the prologue (0x7307C). True entry =
 * 0x73074; the spliced symbol covers 0x73074..0x730C4 (0x50). The old
 * "caller-set $a2" implication was wrong: $a2 is the hoisted status read.
 * Spin while PI_STATUS & 3 (DMA/IO busy), then write data to the
 * KSEG1-uncached cart word ((D | devAddr) | 0xA0000000), return 0.
 * The cart-base global maps to the zero-resolving D_00000000; PI_STATUS
 * is a direct 0xA4600010 literal. PROVEN EXACT 20/20 standalone at IDO
 * 5.3 -O1. Spliced into game_libs_post2b_c.c.o via REPLACE_FUNC_BODY. */
#define PI_STATUS (*(volatile unsigned int *)0xA4600010)
extern int D_00000000;

int gl_func_0007307C(unsigned int devAddr, unsigned int data) {
    char pad[4];
    register unsigned int s;
    s = PI_STATUS;
    if (s & 3) {
        do { s = PI_STATUS; } while (s & 3);
    }
    *(unsigned int *)(((unsigned int)D_00000000 | devAddr) | 0xA0000000) = data;
    return 0;
}
