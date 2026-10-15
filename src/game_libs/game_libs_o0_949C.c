#include "common.h"

/* (2026-10-15: now also holds gl_func_0000959C, 0x959C..0x9674 -> TRUNCATE
 * 0x1D8; see its note at the end of the file.)
 * -O0 sub-file split out of game_libs.c on 2026-05-07. Holds the
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

/* gl_func_0000959C (0xD8 incl. one trailing pad word), moved here from
 * game_libs_tail.c 2026-10-15 (agent-g): it is -O0 like the cluster above
 * (unfilled jal/branch delays, s-reg `register` locals, arg + result homed),
 * not -O2. Decoded as an inlined constructor `obj = new T` (cfront-style:
 * this==0 -> alloc 0x40; base-init, vtable at +0x28, +0x3C = 0) followed by
 * linking the owner's head child (a0->0x40) to it.
 * Standalone -O0: byte-for-byte the target PLUS the dead closing-brace
 * `b epilogue; nop` pair of every value-returning framed -O0 function (the
 * toolchain-binary gap, docs/IDO_CODEGEN.md#feedback-ido-o0-return-value-
 * dead-double-b), so the live return branch reads 10000003 vs 10000001.
 * Load-bearing (docs/IDO_CODEGEN.md#ido-o0-decl-order-slot-lever-register-
 * reserve-plain-home-alias): `ret` declared BEFORE the three `register`
 * locals -> its home is the top slot sp+0x34 (after them: sp+0x28); the
 * `s1 != 0 || (s1 = alloc) != 0` shape gives the bnez/beqz pair (a nested
 * if + goto gives a bnez + extra b). */
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int *gl_func_0000959C(int *a0) {
    int *ret;
    register int *s0;
    register int *s1;
    register int *s2;

    s1 = 0;
    if (s1 != 0 || (s1 = (int *)gl_func_00000000(0x40)) != 0) {
        gl_func_00000000(s1);
        s1[0x28 / 4] = (int)&D_00000000;
        s1[0x3C / 4] = 0;
    }
    ret = s0 = s1;
    if (a0[0x40 / 4] != 0) {
        s0 = (int *)a0[0x40 / 4];
        s1 = ret;
        s2 = (int *)((char *)s1 + 0x10);
        gl_func_00000000(s2, s0);
        if (s0[0x14 / 4] != 0) {
            s0[1] = 1;
        }
        s2 = s1;
        s0[0x14 / 4] = (int)s2;
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000959C);
#endif
