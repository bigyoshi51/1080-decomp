#include "common.h"

/* -O0 sub-file split out of game_libs.c on 2026-05-07. Holds the
 * 0x949C..0x959C cluster (4 functions, 16 insns / 0x40 each, total 0x100):
 * 4 sibling 2-call accessor wrappers all compiled at -O0 in the original.
 *
 * Pattern: minimal -O0 frame (sp-0x20), arg spill at sp+0x20, scratch local
 * at sp+0x1C, 2 jal calls (first with &scratch, second with arg+0x10),
 * trailing `b +1; nop` BB-end marker. All 4 verified byte-exact at -O0
 * standalone (2026-05-07; .text size 0x100 confirmed via readelf).
 *
 * STATUS — partial migration. This run created the file with verified C
 * bodies. Full wiring still requires:
 *   1. Update Makefile: shrink game_libs.c TRUNCATE_TEXT 0xEC00 → 0x949C,
 *      add this file with `OPT_FLAGS := -O0` + `TRUNCATE_TEXT := 0x100`,
 *      add a new `game_libs_tail.c` with -O2 + TRUNCATE_TEXT 0x5664.
 *   2. Create `src/game_libs/game_libs_tail.c` containing everything from
 *      `gl_func_0000959C` onwards (~825 lines moved from game_libs.c).
 *   3. Update tenshoe.ld: insert these two .o files between game_libs.c.o
 *      and game_libs_post.c.o.
 *   4. Strip the 4 #ifdef NON_MATCHING wraps + their INCLUDE_ASMs from
 *      game_libs.c (lines ~729-822).
 *   5. Migrate the SUFFIX_BYTES for `gl_func_0000B560` from game_libs.c.o
 *      to game_libs_tail.c.o (function lives in the tail half).
 *
 * Until step 1 lands, this file is dead-storage — not built, not linked.
 * The default build still uses game_libs.c's INCLUDE_ASM path for the
 * cluster, which emits the correct bytes from the .s. So this commit
 * is forward-progress on the multi-tick split without breaking the
 * current build.
 *
 * Recipe per docs/MATCHING_WORKFLOW.md#feedback-o0-cluster-include-asm-sandwich
 * applies. game_libs is NOT Yay0-compressed, so the per-file -O0 override
 * works (unlike the timproc_uso_b1 / mgrproc_uso siblings which ARE
 * Yay0-compressed and blocked). */

extern int gl_ref_0001CFB0();
extern int gl_ref_0001CFFC();
extern int gl_ref_0001D060();
extern int gl_ref_0001D0AC();

void gl_func_0000949C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001CFFC(a0 + 0x10);
}

void gl_func_000094DC(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001CFB0(a0 + 0x10);
}

void gl_func_0000951C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001D060(a0 + 0x10);
}

void gl_func_0000955C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001D0AC(a0 + 0x10);
}
