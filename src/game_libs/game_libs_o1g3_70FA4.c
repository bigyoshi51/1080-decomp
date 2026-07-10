#include "common.h"

/* game_libs_func_00070FA0 (true entry 0x70FA4): guarded VI-side getter
 * `if (!flag) return 0; return buf.field8;`. PROVEN EXACT 10/10 at IDO
 * 7.1 -O1 -g3 (5.3 agrees): -O1 -g3 is the only mode that emits the
 * unfilled bnez delay + the un-hoisted %lo-folded `lui v0; lw v0,8(v0)`
 * tail (-O2 hoists the lui above the branch; plain -O1 materializes an
 * addiu base; -O2 -g/-g2 add per-return jr-ra echoes).
 * BOUNDARY FIX: this function's splat coverage was THREE pieces --
 * game_libs_func_00070FA0 (0x1C fragment: leading pad nop 0x70FA0 +
 * insns 1-6, "leaf-branch-past-end CAP": its bnez targets 0x70FBC) +
 * the game_libs_g3_70FBC.c carve (the lui/lw/jr/nop tail, previously
 * "matched" as a standalone -g3 INT-reader) -- one function split
 * mid-body by splat. This TU replaces the g3_70FBC carve in the ld
 * script and covers 0x70FA4..0x70CC8; the 0x70FA0 pad nop moved to
 * SUFFIX_BYTES_FORCE on gl_func_00070C44 (post1c.c), and the 8 bytes
 * of natural -g3 .text zero-padding here cover the 0x70FCC/0x70FD0 pad
 * nops before game_libs_func_00070FCC (= cosf, post2.c).
 * Blank externs (runtime-reloc'd words): D_00000000_vistate (guard
 * flag), D_00000000_vibuf (+8 field read; struct-field spelling keeps
 * the %lo fold). Identity: sits between __osViSwapContext and fcos --
 * plausibly a framebuffer/VI-state getter of the game's VI wrapper. */
extern int D_00000000_vistate;
extern struct {
    int a;
    int b;
    int c;
} D_00000000_vibuf;

int game_libs_func_00070FA0(void) {
    if (D_00000000_vistate == 0) {
        return 0;
    }
    return D_00000000_vibuf.c;
}
