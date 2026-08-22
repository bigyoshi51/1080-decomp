#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;



INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

/* gl_func_00074EFC = osCreateViManager + gl_func_0007507C = viMgrMain
 * (libultra vimgr.c verbatim, ONE IDO 5.3 -O1 -mips2 TU donor:
 * game_libs_ido53_74EF4.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice, both first-compile word-exact (98/98 + 115/115 incl.
 * the 6-word zero gap before viMgrMain's dead epilogue -- as1 32-byte-
 * aligns the unreachable block, offset falls out once create is the
 * right 0x188 size). Keys that cracked it:
 *   - whole-TU compile (viMgrMain static; .bss layout viThread 0x1B0 +
 *     stack 0x1000 + queue + buf + msgs + static retrace == USO
 *     0x44080..0x45292 exactly);
 *   - __osViDevMgr DEFINED in the TU (USO .data offset 0 -- the baked
 *     "blank-looking" lui/lo 0 words are its real address): local-.data
 *     definition makes IDO share $at across the 7 field stores; extern
 *     decl re-luis $at each store (+5 words, the old 65% residual);
 *   - viMgrMain fn-ptr materialized against .text (baked original-link
 *     0x896E8, addend 0x188 -> pin gl_func_00074EFC_text = 0x89560).
 * The old "-Olimit allocator quirk" verdict on 7507C is RETRACTED --
 * whole-TU -O1 gives the s0 switch value + 0x38 frame naturally.
 * Bodies below are placeholders for the splice. */
void gl_func_00074EFC(int pri) {
    volatile int vimgr_spliced = 0;
    if (pri != 0) {
        vimgr_spliced = pri;
    }
}

void gl_func_0007507C(char *arg0) {
    volatile int vimgrmain_spliced = 0;
    if (arg0 != 0) {
        vimgrmain_spliced = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_00075248_pad.s")
/* game_libs_func_00075254: the standard cross-USO int-reader template
 * (return D_global), matched in-place at the unit's default 7.1 -O2.
 * The symbol was mis-split as 75248 (3 leading zero pad words now in the
 * _pad sidecar); cc's natural function padding supplies the trailing
 * alignment to 0x7526C. */
extern int D_75254_v;
int game_libs_func_00075254(void) {
    return D_75254_v;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075260);

/* gl_func_0007526C MATCHED 2026-06-10 as game_libs_func_00075264 (own
 * -O1 carve unit game_libs_ido_75264.c): the "dual-entry" theory was
 * wrong -- 75260's lui/lw was the fn's own first statement (boundary
 * mis-split) and the leading nop is 75254's trailing pad (kept below as
 * the 1-word 75260 pad INCLUDE). */
