/* IDO 5.3 -O2 -mips2 donor for gl_func_00070A14 = guMtxL2F
 * (libreultra src/gu/mtxutil.c verbatim). PROVEN EXACT 2026-08-22:
 * 45/45 words identical at -O2 first compile, ZERO relocs. The .s
 * block spans 0x70A0C..0x70AC0 (splat's glabel name is +8 into the
 * body): the leading lui $at,0x3780 / mtc1 $at,$f0 pair IS the
 * FIX32TOF 1/65536.0f constant load, i.e. part of THIS function --
 * the old "ARCHITECTURAL CAP caller-set $f0" verdict is RETRACTED
 * (the $f0 producer was merely on the wrong side of a stale splat
 * boundary note). Single-fn carve-out like neighbor 70954 =
 * guMtxIdentF (the gu cluster does not follow mtxutil.c TU order).
 * POST_COMPILE renames guMtxL2F -> gl_func_00070A14 for the
 * REPLACE_FUNC_BODY splice key. Spliced into game_libs_post1c.c.o. */

typedef long Mtx_t[4][4];
typedef union {
    Mtx_t m;
    long long int forc_structure_alignment;
} Mtx;

#define FIX32TOF(x) ((float)(x) * (1.0f / 65536.0f))

void guMtxL2F(float mf[4][4], Mtx *m)
{
	int		i, j;
	unsigned int	e1,e2;
	unsigned int	*ai,*af;
	int		q1,q2;

	ai=(unsigned int *) &m->m[0][0];
	af=(unsigned int *) &m->m[2][0];

	for (i=0; i<4; i++)
	for (j=0; j<2; j++) {
		e1 = (*ai & 0xffff0000) | ((*af >> 16) & 0xffff);
		e2 = ((*(ai++) << 16) & 0xffff0000) | (*(af++) & 0xffff);
		q1 = *((int *)&e1);
		q2 = *((int *)&e2);

		mf[i][j*2] = FIX32TOF(q1);
		mf[i][j*2+1] = FIX32TOF(q2);
	}
}
