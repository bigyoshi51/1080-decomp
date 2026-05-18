#include "common.h"

/* Mid section of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_8944.c (the 3-fn -O0 cluster at 0x8944..0x8A40).
 * Covers gl_func_00008AE4..gl_func_000093DC (offset 0x8AE4..0x949C).
 * Built at -O2 (default). */

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008AE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);

/* gl_func_00008DAC: 38-insn (0x98) 4-call sequencer. -O0 indicators
 * present: all 4 args spilled at entry (sw a0..a3 0x28..0x34), `b .+8`
 * placeholder branch, unfilled jal delays. Body:
 *   func(&D_A, &D_B + 0x1D150);
 *   func(&D_C, 8, 0, 0);
 *   rv = func(0, a1, a2, a3);   (with args reloaded from caller slots)
 *   func(a0, 1, rv);            (a0 reloaded too)
 * Same -O0 island style as siblings 8A40 and the 8944 family. Promotion
 * likely needs another file split per project_o1o2_split.md plus matching
 * Makefile/linker boundaries. Until then, INCLUDE_ASM is the build path. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008DAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000093DC);
