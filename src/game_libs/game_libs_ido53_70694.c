/* IDO 5.3 -O3 -mips2 whole-TU donor for the libultra gu ortho pair:
 *   gl_func_00070694 = guOrthoF (donor .text [0x000,0x154))
 *   gl_func_000707E8 = guOrtho  (donor .text [0x154,0x1BC))
 * (libreultra src/gu/ortho.c verbatim.) PROVEN EXACT 2026-08-22:
 * first -O3 whole-TU compile is 111/111 FULL-word identical to the raw
 * target .s (not just masked -- the three R_MIPS_26 jal fields are
 * already the target's blank 0x0C000000, the USO ships load-time
 * relocs). -O2 diverges in guOrthoF's scale loop (20 words) and emits
 * guOrtho at 0x64; -O1 is completely differently scheduled; -O3 is the
 * class, same as the xldtob TU next door.
 * Identification keys (old NM wraps had these as anonymous float math):
 *   - 707E8 is the classic guOrtho wrapper shape: mtc1/mfc1 single-
 *     precision arg re-marshal (ANSI floats, NO K&R double promotion),
 *     Matrix mf[4][4] at sp+40 (64 bytes), two blank jals =
 *     guOrthoF(mf, l..scale) then guMtxF2L(mf, m);
 *   - 70694 opens with jal guMtxIdentF then the 2/(r-l), 2/(t-b),
 *     -2/(f-n) diagonal + row-3 translate terms + 4x4 *= scale loop.
 * Reloc story (single consistent story, all three relocs):
 *   - jal guMtxIdentF / jal guMtxF2L / internal jal guOrthoF: the USO
 *     ships all three blank (load-time reloc table, already matched as
 *     data) -> POST_COMPILE renames all three symbols to
 *     gl_func_00000000_{identf706,orthof706,f2l706} pins = 0, so the
 *     imported relocs bake the target's 0x0C000000 verbatim.
 * Renaming guOrthoF away (its internal-call reloc must stay blank)
 * removes the splice key, so POST_COMPILE re-injects a duplicate
 * gl_func_00070694=0x0:0x154 symbol (metadata only, bytes untouched);
 * guOrtho carries no relocs against it and is renamed to
 * gl_func_000707E8 directly. Spliced into game_libs_post1c.c.o via
 * REPLACE_FUNC_BODY. */
typedef signed short s16;
typedef long s32;
typedef unsigned long u32;
typedef union {
    struct { u32 m1[8]; u32 m2[8]; } b;
    s32 m[4][4];
    long long forcealign;
} Mtx;
typedef float Matrix[4][4];

extern void guMtxIdentF(float mf[4][4]);
extern void guMtxF2L(float mf[4][4], Mtx *m);

void guOrthoF(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale)
{
	int	i, j;

	guMtxIdentF(mf);

	mf[0][0] = 2/(r-l);
	mf[1][1] = 2/(t-b);
	mf[2][2] = -2/(f-n);
	mf[3][0] = -(r+l)/(r-l);
	mf[3][1] = -(t+b)/(t-b);
	mf[3][2] = -(f+n)/(f-n);
	mf[3][3] = 1;

	for (i=0; i<4; i++)
	    for (j=0; j<4; j++)
		mf[i][j] *= scale;
}

void guOrtho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale)
{
	Matrix	mf;

	guOrthoF(mf, l, r, b, t, n, f, scale);

	guMtxF2L(mf, m);
}
