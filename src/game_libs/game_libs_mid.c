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
