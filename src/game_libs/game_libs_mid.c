#include "common.h"

/* Mid section of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_8944.c (the 3-fn -O0 cluster at 0x8944..0x8A40).
 * Covers gl_func_00008A40..gl_func_000093DC (offset 0x8A40..0x949C).
 * Built at -O2 (default). */

#ifdef NON_MATCHING
/* gl_func_00008A40: 41-insn (0xA4) Vec3-from-data initializer. -O0 indicators
 * present: dead-store `or s0, s1, zero` (s0 never used after), `b .+8` no-op
 * branch over a nop, frame -0x58 with all 4 s-regs spilled, unfilled
 * jal-delay-slot. Matches the -O0 pattern of existing siblings 8944/89F4/8990
 * (already split into game_libs_o0_8944.c).
 *
 * Body decoded:
 *   1. Save $s0-$s3 + $ra; spill a0 to sp+0x58.
 *   2. gl_func_00000000(&D_00000000, &sp+0x48, 0xC) — read 12 bytes.
 *   3. Reload a0 from sp+0x58 into $s1.
 *   4. 12-byte int fanout: sp+0x48 -> sp+0x34 (3 lw/sw pairs).
 *   5. Vec3 float copy from sp+0x34 to a0+0..8 (3 lwc1/swc1 pairs).
 *   6. Dead `s0 = s1` (-O0 unused-value compute).
 *   7. `b .+8 / nop` then epilogue.
 *
 * Logical C (this body matches at -O2 only — needs an -O0 file split to
 * preserve the dead-store + `b .+8` + redundant fanout pattern).
 *
 * Multi-tick: split into a new src/game_libs/game_libs_o0_8A40.c file with
 * `OPT_FLAGS := -O0` per project_o1o2_split.md. Family of -O0 functions in
 * this region (8A40, 8AE4, ...) deserves shared file. Same pattern as the
 * existing game_libs_o0_8944.c. */
extern int gl_func_00000000();
extern char D_00000000;
typedef struct { float x, y, z; } Vec3f;
void gl_func_00008A40(Vec3f *dst) {
    int buf1[3];
    int buf2[3];
    gl_func_00000000(&D_00000000, buf1, 0xC);
    buf2[0] = buf1[0];
    buf2[1] = buf1[1];
    buf2[2] = buf1[2];
    dst->x = *(float*)&buf2[0];
    dst->y = *(float*)&buf2[1];
    dst->z = *(float*)&buf2[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008A40);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008AE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);

/* gl_func_00008DAC: 38-insn (0x98) 4-call sequencer. -O0 indicators
 * present: all 4 args spilled at entry (sw a0..a3 0x28..0x34), `b .+8`
 * placeholder branch, unfilled jal delays. Body:
 *   func(&D_A, &D_B + 0x1D150);
 *   func(&D_C, 8, 0, 0);
 *   rv = func(0, a1, a2, a3);   (with args reloaded from caller slots)
 *   func(a0, 1, rv);            (a0 reloaded too)
 * Same -O0 cluster as siblings 8A40 (and the 8944 family that already
 * has a stub file). Promotion blocked on multi-tick file split per
 * project_o1o2_split.md — create game_libs_o0_8A40.c covering this
 * region + Makefile OPT_FLAGS := -O0 + linker-script insert. Until
 * then, INCLUDE_ASM is the build path. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008DAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000093DC);
