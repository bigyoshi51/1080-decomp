#include "common.h"

/* gl_func_0006C9F4 = libultra __osPiRawStartDma (io/pirawdma.c), statically
 * linked into the game_libs USO. Byte-exact masked-twin of the matched kernel
 * func_80004650 (kernel_042_b.c): identical 56-insn body after masking the
 * one R_MIPS_26 callee + the one HI16/LO16 global pair. Compiled IDO 5.3 -O1
 * (same per-file carve recipe as the other game_libs_ido53_* libultra units).
 *
 * The PI hardware register block (0xA4600000..0xA4600010) is direct-mapped and
 * stored verbatim in the ROM (resolved lui 0xA460 literals, no reloc). The two
 * collapsed cross-references the USO loader fixes up at runtime — the cart-base
 * helper (kernel func_80004B30 = osVirtualToPhysical-ish) and the DMA cfg base
 * global — are stored as bare placeholders (jal 0 / lui 0,lw 0) in the ROM, so
 * we reproduce them with the address-0 placeholders gl_func_00000000 / the
 * zero-offset global D_00000000. Standard 1080 USO placeholder-callee
 * convention (see game_libs_ido53_6C384.c / _73334.c). */
extern int gl_func_00000000();   /* collapsed cart-base helper (jal 0) */
extern int D_00000000;           /* collapsed DMA cfg-base global (lui 0,lw 0) */

int gl_func_0006C9F4(int direction, unsigned int devAddr, int dramAddr, unsigned int size) {
    register unsigned int status;

    while ((status = *(volatile unsigned int*)0xA4600010) & 3) ;

    *(volatile unsigned int*)0xA4600000 = gl_func_00000000(dramAddr);
    *(volatile unsigned int*)0xA4600004 = (D_00000000 | devAddr) & 0x1FFFFFFF;

    switch (direction) {
        case 0:
            *(volatile unsigned int*)0xA460000C = size - 1;
            break;
        case 1:
            *(volatile unsigned int*)0xA4600008 = size - 1;
            break;
        default:
            return -1;
    }

    return 0;
}
