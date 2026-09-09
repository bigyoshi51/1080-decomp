/* IDO 5.3 -O2 -mips2 donor for game_libs_func_00070854 = guMtxF2L
 * (libreultra src/gu/mtxutil.c verbatim, FTOFIX32 from gu.h). PROVEN
 * EXACT 2026-09-09: 64/64 words identical at -O2 (and -O3; -O1 is 1/64),
 * ZERO relocs (lui 0x4780 = 65536.0f, the unrolled j<2 inner pair). The
 * 2026-08-22 "64/64 divergent at every opt level" note was an off-by-one
 * comparison against the old padded .s (game_libs_func_00070850 carried
 * guOrtho's inter-object pad word at 0x70850; the export is 0x70854).
 * Single-fn carve-out like guMtxIdentF 70954 (the game's gu cluster does
 * not follow mtxutil.c's TU emit order). POST_COMPILE renames
 * guMtxF2L -> game_libs_func_00070854 for the REPLACE_FUNC_BODY splice
 * key. Spliced into game_libs_post1c.c.o. */

typedef union {
	long m[4][4];
	long long int force_structure_alignment;
} Mtx;

#define FTOFIX32(x)	(long)((x) * (float)0x00010000)

void guMtxF2L(float mf[4][4], Mtx *m)
{
	int	i, j;
	int	e1,e2;
	int	*ai,*af;


	ai=(int *) &m->m[0][0];
	af=(int *) &m->m[2][0];

	for (i=0; i<4; i++)
	for (j=0; j<2; j++) {
		e1=FTOFIX32(mf[i][j*2]);
		e2=FTOFIX32(mf[i][j*2+1]);
		*(ai++) = ( e1 & 0xffff0000 ) | ((e2 >> 16)&0xffff);
		*(af++) = ((e1 << 16) & 0xffff0000) | (e2 & 0xffff);
	}
}
