#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

/* -O0 sub-file prep — sibling to game_libs_o0_949C.c. Holds the
 * 0x8944..0x8A40 region with verified -O0 bodies for the int-reader
 * (gl_func_00008944) and float-reader (gl_func_000089F4) accessor
 * templates.
 *
 * STATUS — step 0 of multi-tick split. This commit creates the file
 * with verified C bodies. Full wiring still requires:
 *   1. Truncate game_libs.c TRUNCATE_TEXT 0x949C → 0x8944.
 *   2. Create `src/game_libs/game_libs_mid.c` covering 0x8A40..0x949C
 *      (the section between this file's tail and the o0_949C cluster).
 *   3. Update Makefile: add this file with `OPT_FLAGS := -O0` +
 *      `TRUNCATE_TEXT := 0xFC` + INSN_PATCH for the 1 jal in each
 *      reader (gl_func_00008944=0x1c:0xJALTARGET, similarly for 89F4)
 *      + the INCLUDE_ASM-sandwich gl_func_00008990 (0x64) just emits
 *      from .s, no patches needed.
 *   4. Update tenshoe.ld: insert this .o + game_libs_mid.c.o between
 *      game_libs.c.o and game_libs_o0_949C.c.o.
 *   5. Strip the gl_func_00008944 + gl_func_000089F4 NM wraps from
 *      game_libs.c (they'll move to this file as C bodies; the
 *      gl_func_00008990 INCLUDE_ASM moves here as a sandwich stub).
 *   6. Add unit entry to objdiff.json (-O0 c_flags).
 *
 * Until step 1 lands, this file is dead-storage — not built, not linked.
 *
 * Recipe per docs/POST_CC_RECIPES.md
 * #feedback-jal-insn-patch-to-match-include-asm-derived-expected:
 * once wired, INSN_PATCH the jal targets to match expected/.o (which is
 * INCLUDE_ASM-derived). For gl_func_00000000 (callee=0), the resolved
 * jal target is 0x0C000000 itself, so no patch needed for those.
 *
 * Verified standalone at -O0 (2026-05-07):
 *   gl_func_00008944: 19 insns / 0x4C, byte-exact.
 *   gl_func_000089F4: 19 insns / 0x4C, byte-exact (lwc1/swc1 form). */

/* Bodies bracketed with #if 0 to prevent duplicate-symbol link error
 * with game_libs.c's existing INCLUDE_ASM (which still emits the bytes
 * from .s for the default build). When step 1-6 of the migration land,
 * remove the `#if 0`/`#endif` here AND strip the wraps in game_libs.c. */
#if 0
void gl_func_00008944(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008990);

void gl_func_000089F4(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#endif
