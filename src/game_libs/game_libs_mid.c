#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern int D_8C3C_arg;
extern char D_8C3C_child_desc;
extern char D_8C3C_mid_desc;
extern char D_8C3C_root_desc;

/* Mid section of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_8944.c (the 3-fn -O0 cluster at 0x8944..0x8A40).
 * Covers gl_func_00008AE4..gl_func_000093DC (offset 0x8AE4..0x949C).
 * Built at -O2 (default). */

#ifdef NON_MATCHING
/* gl_func_00008C3C: 92-insn alloc-or-passthrough cascade. The first three
 * calls configure globals, then the root/mid/child chain allocates 0xD4,
 * 0x50, and 0x2C byte nodes through dead-arm passthrough guards.
 *
 * 2026-05-18 deep attempt: default -O2 emits a structurally short stack-temp
 * form; scratch -O0 compile matches the target's 0x38 frame, s0/s1/s2
 * cascade, and most branch layout. Exact promotion likely needs a dedicated
 * -O0 split for this single function (like the adjacent 8AE4/8944 island)
 * plus final constant/reloc cleanup. Default build stays INCLUDE_ASM. */
void gl_func_00008C3C(int *a0, int a1) {
    register int *root;
    register int *mid;
    register int *child;

    gl_func_00000000(&D_00000000, (char*)0x1D138);
    gl_func_00000000(&D_00000000, D_8C3C_arg);
    gl_func_00000000(&D_00000000, 7, 0, 0);

    root = 0;
    if (root == 0) {
        root = (int*)gl_func_00000000(0xD4);
    }
    if (root != 0) {
        mid = root;
        if (mid == 0) {
            mid = (int*)gl_func_00000000(0x50);
        }
        if (mid != 0) {
            child = mid;
            if (child == 0) {
                child = (int*)gl_func_00000000(0x2C);
            }
            if (child != 0) {
                gl_func_00000000(child, (char*)0x1D148);
                child[0x28 / 4] = (int)&D_8C3C_child_desc;
            }

            mid[0x28 / 4] = (int)&D_8C3C_mid_desc;
        }
        root[0x28 / 4] = (int)&D_8C3C_root_desc;
    }
    {
        int *call_root = root;
        gl_func_00000000(call_root, a0[0]);
        gl_func_00000000(call_root);
        root = call_root;
    }
    gl_func_00000000(a0, 0, root);
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);
#endif

/* gl_func_00008DAC: 39-insn 4-call init sequencer. -O0 island (file built
 * OPT_FLAGS := -O0: all 4 args spilled at entry, unfilled jal delays, b-to-epilogue).
 * The 2nd arg is the data symbol at offset 0xD150 referenced DIRECTLY as
 * &D_0000D150 (defined = 0x0000D150 in undefined_syms) so -O0 emits the 2-insn
 * %hi/%lo (lui 0x1; addiu -0x2EB0) the target uses -- NOT &D_00000000+0xD150 (3
 * insns at -O0). rv kept in s0 via `register`. */
extern int gl_func_00000000();
extern char D_0000D150;
void gl_func_00008DAC(int a0, int a1, int a2, int a3) {
    register int rv;
    gl_func_00000000(&D_00000000, &D_0000D150);
    gl_func_00000000(&D_00000000, 8, 0, 0);
    rv = gl_func_00000000(0, a1, a2, a3);
    gl_func_00000000(a0, 1, rv);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000093DC);
