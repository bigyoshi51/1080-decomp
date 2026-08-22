/* IDO 5.3 -O2 -mips2 donor for game_libs_func_00070954 = guMtxIdentF
 * (libreultra src/gu/mtxutil.c verbatim). PROVEN EXACT 2026-08-22:
 * 34/34 words identical at -O2 (and -O3; -O1 fully rescheduled), ZERO
 * relocs -- the fn is pure code (lui 0x3F80 = 1.0f, mtc1 zero, the
 * i==j diagonal selects). NOTE the gu cluster layout does NOT follow
 * mtxutil.c's TU emit order (Ident,IdentF,F2L,L2F,..): the game links
 * F2L-shaped 70850 BEFORE IdentF 70954, so these land as single-fn
 * carve-outs, not one mtxutil TU. Neighbor 70850 is F2L-shaped but
 * 64/64-word divergent from libreultra guMtxF2L at every opt level
 * (different variant/source) -- negative result, stays NM.
 * POST_COMPILE renames guMtxIdentF -> game_libs_func_00070954 for the
 * REPLACE_FUNC_BODY splice key. Spliced into game_libs_post1c.c.o. */

void guMtxIdentF(float mf[4][4])
{
	int	i, j;

	for (i=0; i<4; i++)
	for (j=0; j<4; j++)
		if (i == j) mf[i][j] = 1.0;
		else mf[i][j] = 0.0;
}
