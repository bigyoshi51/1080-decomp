/* IDO 5.3 -O3 -mips2 donor for gl_func_0006F834 = libultra guFrustum
 * (references/libreultra/src/gu/frustum.c, verbatim). PROVEN EXACT 26/26
 * standalone at BOTH 5.3 -O3 and 7.1 -O3 (agent-g 2026-09-09; built with
 * 5.3 like the guOrtho donor game_libs_ido53_70694.c, whose -O3 class this
 * is). -O2 is 23 words off (two FP homes + `sw a3` stack home): the old
 * "2-FP-home budget cap / no probed mode homes three float params" verdict
 * in the 87.7% wrap was -O2 vs -O3, not a compiler limit. Section 0x83EA0 =
 * bootup.uso export sym 162 (one jal ref at 0x1B00).
 * Shape: Matrix mf at sp+40 (64 bytes), mtc1/mfc1 single-precision arg
 * re-marshal of l/r/b (a1-a3 -> f12/f14/f16 -> a1-a3), t/n/f/scale copied
 * sp+0x78.. -> sp+0x10.. via lwc1/swc1, two blank jals = guFrustumF(mf, ...)
 * then guMtxF2L(mf, m).
 * guFrustumF is the in-unit game_libs_func_0006F684 (0x1B0; its target body
 * is 108 words, NOT the 88-word libreultra guFrustumF, so it is not part of
 * this donor) -- named through the blank import gl_func_00000000_frustumf
 * (pin = 0) so the jal word stays 0C000000 + USO reloc; guMtxF2L reuses the
 * guOrtho donor's blank pin gl_func_00000000_f2l706. The 2-word
 * gl_func_0006F834_pad.s (inter-object pad before osEPiRawStartDma 6F8A4)
 * stays as it is. Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef signed short s16;
typedef long s32;
typedef unsigned long u32;
typedef union {
    struct { u32 m1[8]; u32 m2[8]; } b;
    s32 m[4][4];
    long long forcealign;
} Mtx;
typedef float Matrix[4][4];

extern void gl_func_00000000_frustumf(float mf[4][4], float l, float r, float b, float t, float n, float f, float scale); /* guFrustumF = game_libs_func_0006F684 */
extern void gl_func_00000000_f2l706(float mf[4][4], Mtx *m);                                                         /* guMtxF2L = game_libs_func_00070854 */
#define guFrustumF gl_func_00000000_frustumf
#define guMtxF2L gl_func_00000000_f2l706

void gl_func_0006F834(Mtx *m, float l, float r, float b, float t, float n, float f, float scale)
{
	Matrix	mf;

	guFrustumF(mf, l, r, b, t, n, f, scale);

	guMtxF2L(mf, m);
}
