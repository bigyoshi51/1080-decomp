#include "common.h"

/* The TLB-probe callee is an intra-module call that the USO loader relocates
 * at runtime; the ROM stores it as a bare `jal 0` (0x0C000000). Calling the
 * address-0 placeholder gl_func_00000000 reproduces those .text bytes exactly
 * (resolving the real symbol gl_func_00062F64 would emit a non-zero jal that
 * diverges from the ROM). Standard 1080 USO placeholder-callee convention. */
extern u32 gl_func_00000000();

/* gl_func_0006C384 = libultra osVirtualToPhysical (os/virtualtophysical.c).
 * KSEG0 (0x80000000..0x9FFFFFFF) and KSEG1 (0xA0000000..0xBFFFFFFF) are
 * direct-mapped to physical via `& 0x1FFFFFFF`; otherwise delegate to the
 * TLB-probe runtime helper (collapsed intra-module jal at splat time).
 *
 * MATCHES byte-exact only at -O1 (the target homes a0 to the stack and
 * reloads it for each KSEG comparison and for the fallback call -- a -O1
 * codegen trait; -O2 keeps a0 in $a0 and emits no homing). Carved out of
 * game_libs_post1b2.c (which is -O2) into this dedicated -O1 unit so the
 * function compiles with the matching optimization level. See the .ld for
 * the VRAM ordering (between post1b2 head and post1b2c tail). */
u32 gl_func_0006C384(u32 a0) {
    if (a0 >= 0x80000000U && a0 < 0xA0000000U) {
        return a0 & 0x1FFFFFFF;
    }
    if (a0 >= 0xA0000000U && a0 < 0xC0000000U) {
        return a0 & 0x1FFFFFFF;
    }
    return gl_func_00000000(a0);
}
