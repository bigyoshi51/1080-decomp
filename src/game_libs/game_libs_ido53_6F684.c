/* IDO 5.3 -O3 -mips2 donor for game_libs_func_0006F684 = libultra guPositionF
 * (references/libreultra/src/gu/position.c, verbatim). PROVEN 105/108 words
 * standalone at BOTH 5.3 -O3 and 7.1 -O3 (agent-g 2026-09-09), the three
 * remaining words being the reloc addends of the two `dtor` accesses, which
 * the in-tree link bakes via pins (see below) -> 108/108 in the unit. -O2 is
 * 96 words off (frame/spill layout, no static write-back). Section 0x83CF0 =
 * bootup.uso export sym 2629; its one jal ref is at 0x83EE4 = gl_func_0006F834
 * + 0x44, i.e. the "guFrustum" wrapper 6F834 is really guPosition (the
 * guFrustum / guPosition wrapper bodies are byte-identical: Matrix mf at
 * sp+40, mtc1/mfc1 re-marshal of three float args, F-variant jal then
 * guMtxF2L). The old 84% NM decode ("Vec3-style float triple * D[0x24D0],
 * six game_libs_func_0006C400 calls") was this function: D[0x24D0] is the
 * `dtor` float literal (rodata), the six calls are sinf/cosf (in-module
 * fsin 6A144 / fcos 70FCC, shipped as blank load-time relocs), and the
 * 3x3 rotation is roll/pitch/yaw with scale, row 3 = x/y/z/1.
 * -O3 static tell: `static float dtor = 3.1415926 / 180.0` is NOT emitted as
 * initialised .data -- IDO -O3 puts `dtor` in .bss and WRITES the literal
 * into it on every entry (`lwc1 f0,%lo(lit)(at)` ... `swc1 f0,%lo(dtor)(at)`,
 * the lui at,0x0004 / swc1 0x4030 pair). Both relocs are against donor-local
 * section symbols; replace-function-body.py renames them to
 * game_libs_func_0006F684_rodata / _bss, pinned in undefined_syms_auto.txt to
 * the USO's baked 0x24D0 / 0x44030 (the 6DD14 jumptable recipe).
 * Blank externs (USO load-time relocs, pins = 0): gl_func_00000000_sinf6f =
 * sinf, gl_func_00000000_cosf6f = cosf. Built by the direct-CC rule pair
 * (asm-processor rejects -O3), spliced into game_libs_post1b2c.c.o via
 * REPLACE_FUNC_BODY; no pad (the C body is the same 0x1B0 as the old .s). */
extern float gl_func_00000000_sinf6f(float); /* sinf = game_libs_func_0006A144 (fsin) */
extern float gl_func_00000000_cosf6f(float); /* cosf = gl_func_00070FCC (fcos) */
#define sinf gl_func_00000000_sinf6f
#define cosf gl_func_00000000_cosf6f

/*
 *  Return position matrix given roll, pitch, and yaw in degrees
 *  plus scale and position.
 *
 * r = roll  (degrees)
 * p = pitch (degrees)
 * h = yaw   (degrees)
 * s = scale
 * x,y,z = position (world coordinates)
 *
 */

void game_libs_func_0006F684(float mf[4][4], float r, float p, float h, float s,
		 float x, float y, float z)
{
        static float    dtor = 3.1415926 / 180.0;
        float   sinr, sinp, sinh;
        float   cosr, cosp, cosh;

        r *= dtor;
        p *= dtor;
        h *= dtor;
        sinr = sinf(r);
        cosr = cosf(r);
        sinp = sinf(p);
        cosp = cosf(p);
        sinh = sinf(h);
        cosh = cosf(h);

        mf[0][0] = (cosp*cosh) * s;
        mf[0][1] = (cosp*sinh) * s;
        mf[0][2] = (-sinp) * s;
        mf[0][3] = 0.0;

        mf[1][0] = (sinr*sinp*cosh - cosr*sinh) * s;
        mf[1][1] = (sinr*sinp*sinh + cosr*cosh) * s;
        mf[1][2] = (sinr*cosp) * s;
        mf[1][3] = 0.0;

        mf[2][0] = (cosr*sinp*cosh + sinr*sinh) * s;
        mf[2][1] = (cosr*sinp*sinh - sinr*cosh) * s;
        mf[2][2] = (cosr*cosp) * s;
        mf[2][3] = 0.0;

        mf[3][0] = x;
        mf[3][1] = y;
        mf[3][2] = z;
        mf[3][3] = 1.0;
}
