/* IDO 7.1 -O2 donor for game_libs_func_00070FCC = libultra fcos/__cosf
 * (gu/cosf.c verbatim, Cody-Waite reduction). PROVEN EXACT 90/90
 * standalone at -O2 (5.3 -O2 agrees; -O1 is 112 insns) against the
 * concatenated 0x70FD4..0x71138 stream -- the 5 rodata addend words
 * resolve at link via the baked gl_ref_* values below.
 * BOUNDARY FIX: splat split this one function into FOUR fragments at
 * its interior branch targets / second+third return points:
 *   70FCC (2 leading pad nops + head), 710F8 (the old "caller-set $f2
 *   double polynomial CAP" -- it's just the n-odd negated-result tail),
 *   71114 (the NaN check), 71130 (the old "prologue-stolen $at CAP" --
 *   the `return zero.f` tail). All four INCLUDE_ASMs removed; spliced
 *   symbol covers 0x70FD4..0x7113B. True entry = 0x70FD4 (the 0x70FCC/
 *   0x70FD0 pads are the -g3 .text zero-padding of the preceding
 *   game_libs_o1g3_70FA4.c unit).
 * Static rodata (P[5]/rpi/pihi/pilo/zero) lives in the ROM's game_libs
 * data at segment offsets 0x24E0..0x2523 -> extern gl_ref_* with baked
 * values (gl_ref_0002E4C0 precedent); __libm_qnan_f is a runtime-reloc
 * blanked extern (D_00000000_qnanf).
 * Spliced into game_libs_post2.c.o via REPLACE_FUNC_BODY. */
typedef union {
    struct {
        unsigned int hi, lo;
    } word;
    double d;
} du;

typedef union {
    unsigned int i;
    float f;
} fu;

#define ROUND(d) (int)(((d) >= 0.0) ? ((d) + 0.5) : ((d) - 0.5))
#define ABS(d) ((d) > 0) ? (d) : -(d)

extern const du gl_ref_000024E0[]; /* P[5]: sin poly coeffs on +/- pi/2 */
extern const du gl_ref_00002508;   /* rpi  = 1/pi */
extern const du gl_ref_00002510;   /* pihi */
extern const du gl_ref_00002518;   /* pilo */
extern const fu gl_ref_00002520;   /* zero */
extern float D_00000000_qnanf;     /* __libm_qnan_f */

float game_libs_func_00070FCC(float x) {
    float absx;
    double dx, xsq, poly;
    double dn;
    int n;
    double result;
    int ix, xpt;

    ix = *(int *)&x;
    xpt = (ix >> 22);
    xpt &= 0x1ff;

    /* xpt is exponent(x) + 1 bit of mantissa */

    if (xpt < 0x136) {
        /* |x| < 2^28 */
        absx = ABS(x);
        dx = absx;

        dn = dx * gl_ref_00002508.d + 0.5;
        n = ROUND(dn);
        dn = n;
        dn -= 0.5;

        dx = dx - dn * gl_ref_00002510.d;
        dx = dx - dn * gl_ref_00002518.d; /* dx = x - (n - 0.5)*pi */

        xsq = dx * dx;
        poly = ((gl_ref_000024E0[4].d * xsq + gl_ref_000024E0[3].d) * xsq + gl_ref_000024E0[2].d) * xsq
               + gl_ref_000024E0[1].d;
        result = dx + (dx * xsq) * poly;

        if ((n & 1) == 0)
            return ((float)result);

        /* negate result if n is odd */
        return (-(float)result);
    }

    if (x != x) {
        /* x is a NaN; return a quiet NaN */
        return (D_00000000_qnanf);
    }

    /* just give up and return 0.0 */
    return (gl_ref_00002520.f);
}
