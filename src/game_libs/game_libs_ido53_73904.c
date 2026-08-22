/* IDO 5.3 -O3 donor for the libc printf float pair:
 *   gl_func_00073904 = _Genld  (donor .text [0x000,0x568))
 *   gl_func_00073E74 = _Ldtob  (donor .text [0x570,0xAC0), incl. the
 *                               trailing alignment nop = target 0x550)
 * (Plauger libc xldtob.c verbatim, libreultra source.) PROVEN EXACT
 * 2026-08-22 probe: _Genld 348/348 words vs expected [0x270,0x7E0),
 * _Ldtob 340/340 words vs expected [0x7E0,0xD30) -- every diff word is
 * a reloc field with a single consistent story:
 *   - .rodata %hi/%lo pairs (pows table @+0x00, "Inf" @+0x48, "NaN"
 *     @+0x4C, "0" @+0x50, 1.0e8 @+0x58): target bakes .rodata base
 *     0x2540 (USO data segment); pins gl_func_00073904_rodata /
 *     gl_func_00073E74_rodata = 0x2540 in undefined_syms_auto.txt.
 *   - blank USO jals (memcpy x6, ldiv=gl_func_000744CC): field 0 both
 *     sides (gl_func_00000000_* externs).
 *   - the ONE intra-TU jal _Ldtob->_Genld: target bakes 0x0C021FDC
 *     (jal 0x87F70, the USO's original-link address of _Genld); donor
 *     reloc vs local .text renamed to gl_func_00073E74_text by the
 *     splice, pinned = 0x87F70.
 * WHY -O3: the WHOLE-TU interprocedural register allocation gives the
 * static _Genld its custom linkage -- it receives its five args in
 * $s0-$s4 (the documented "caller-set s-reg cap" on 73904 was exactly
 * this), and _Ldunscale is integrated into _Ldtob (the old 74.0%
 * "_Ldunscale-family classifier" redecode was the inlined classifier
 * head). No -O1/-O2 compile can produce the s-reg call.
 * Statics keep no symtab entries at -O3, so the donor rule's
 * POST_COMPILE (scripts/add-elf-func-symbol.py) injects the two
 * function symbols the REPLACE_FUNC_BODY splice keys on.
 * Spliced into game_libs_post2b_d.c.o via REPLACE_FUNC_BODY. */

typedef unsigned int size_t;

typedef struct
{
    union {
        /* 00 */ long long s64;
        double f64;
    } value;
    /* 08 */ char *buff;
    /* 0c */ int n0;
    /* 10 */ int num_leading_zeros;
    /* 14 */ int part2_len;
    /* 18 */ int num_mid_zeros;
    /* 1c */ int part3_len;
    /* 20 */ int num_trailing_zeros;
    /* 24 */ int precision;
    /* 28 */ int width;
    /* 2c */ unsigned int size;
    /* 30 */ unsigned int flags;
    /* 34 */ char length;
} printf_struct;

#define FLAGS_SPACE 1
#define FLAGS_PLUS 2
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
#define FLAGS_ZERO 16

typedef struct ldiv_t
{
    long quot;
    long rem;
} ldiv_t;

/* blank USO-reloc externs (jal field 0): memcpy and ldiv
 * (= gl_func_000744CC, already landed as the ldiv identity). */
extern void *gl_func_00000000_mcpy73(void *, const void *, size_t);
extern ldiv_t gl_func_00000000_ldiv73(long, long);
#define memcpy gl_func_00000000_mcpy73
#define ldiv gl_func_00000000_ldiv73

typedef double f64;

#define BUFF_LEN 0x20

static short _Ldunscale(short *, printf_struct *);
static void _Genld(printf_struct *, char, char *, short, short);

static const double pows[] = {10e0L, 10e1L, 10e3L, 10e7L, 10e15L, 10e31L, 10e63L, 10e127L, 10e255L};

/* float properties */
#define _D0 0
#define _DBIAS 0x3ff
#define _DLONG 1
#define _DOFF 4
#define _FBIAS 0x7e
#define _FOFF 7
#define _FRND 1
#define _LBIAS 0x3ffe
#define _LOFF 15
/* integer properties */
#define _C2 1
#define _CSIGN 1
#define _ILONG 0
#define _MBMAX 8
#define NAN 2
#define INF 1
#define FINITE -1
#define _DFRAC ((1 << _DOFF) - 1)
#define _DMASK (0x7fff & ~_DFRAC)
#define _DMAX ((1 << (15 - _DOFF)) - 1)
#define _DNAN (0x8000 | _DMAX << _DOFF | 1 << (_DOFF - 1))
#define _DSIGN 0x8000
#define _D1 1 /* big-endian order */
#define _D2 2
#define _D3 3

void _Ldtob(printf_struct *args, char type)
{
  char buff[BUFF_LEN];
  char *p;
  f64 ldval;
  short err;
  short nsig;
  short exp;

  p = buff;
  ldval = args->value.f64;
  if (args->precision < 0)
  {
    args->precision = 6;
  }
  else
  {
    if (args->precision == 0 && (type == 'g' || type == 'G'))
    {
      args->precision = 1;
    }
  }
  err = _Ldunscale(&exp, args);
  if (err > 0)
  {
    memcpy(args->buff, err == 2 ? "NaN" : "Inf", args->part2_len = 3);
    return;
  }
  if (err == 0)
  {
    nsig = 0;
    exp = 0;
  }
  else
  {
    int i;
    int n;

    if (ldval < 0)
    {
      ldval = -ldval;
    }
    exp = exp * 30103 / 0x000186A0 - 4;
    if (exp < 0)
    {
      n = (3 - exp) & ~3;
      exp = -n;
      for (i = 0; n > 0; n >>= 1, i++)
      {
        if ((n & 1) != 0)
        {
          ldval *= pows[i];
        }
      }
    }
    else
    {
      if (exp > 0)
      {
        f64 factor;
        factor = 1;
        exp &= ~3;
        for (n = exp, i = 0; n > 0; n >>= 1, i++)
        {
          if ((n & 1) != 0)
          {
            factor *= pows[i];
          }
        }
        ldval /= factor;
      }
    }
    {
      int gen;
      gen = ((type == 'f') ? exp + 10 : 6) + args->precision;
      if (gen > 0x13)
      {
        gen = 0x13;
      }
      *p++ = '0';
      while (gen > 0 && 0 < ldval)
      {
        int j;
        int lo;
        lo = ldval;
        if ((gen -= 8) > 0)
        {
          ldval = (ldval - lo) * 1.0e8;
        }
        p = p + 8;
        for (j = 8; lo > 0 && --j >= 0;)
        {
          ldiv_t qr = ldiv(lo, 10);
          *--p = qr.rem + '0';
          lo = qr.quot;
        }
        while (--j >= 0)
        {
          p--;
          *p = '0';
        }
        p += 8;
      }

      gen = p - &buff[1];
      for (p = &buff[1], exp += 7; *p == '0'; p++)
      {
        --gen, --exp;
      }

      nsig = ((type == 'f') ? exp + 1 : ((type == 'e' || type == 'E') ? 1 : 0)) + args->precision;
      if (gen < nsig)
      {
        nsig = gen;
      }
      if (nsig > 0)
      {
        char drop;
        int n;
        if (nsig < gen && p[nsig] > '4')
        {
          drop = '9';
        }
        else
        {
          drop = '0';
        }

        for (n = nsig; p[--n] == drop;)
        {
          nsig--;
        }
        if (drop == '9')
        {
          p[n]++;
        }
        if (n < 0)
        {
          --p, ++nsig, ++exp;
        }
      }
    }
  }
  _Genld(args, type, p, nsig, exp);
}

static short _Ldunscale(short *pex, printf_struct *px)
{

  unsigned short *ps = (unsigned short *)px;
  short xchar = (ps[_D0] & _DMASK) >> _DOFF;
  if (xchar == _DMAX)
  { /* NaN or INF */
    *pex = 0;
    return (short)(ps[_D0] & _DFRAC || ps[_D1] || ps[_D2] || ps[_D3] ? NAN : INF);
  }
  else if (0 < xchar)
  {
    ps[_D0] = (ps[_D0] & ~_DMASK) | (_DBIAS << _DOFF);
    *pex = xchar - (_DBIAS - 1);
    return (FINITE);
  }
  if (0 > xchar)
  {
    return NAN;
  }
  else
  {
    *pex = 0;
    return (0);
  }
}

static void _Genld(printf_struct *px, char code, char *p, short nsig, short xexp)
{
  const char point = '.';
  if (nsig <= 0)
  {
    nsig = 1,

    p = (char *)"0";
  }

  if (code == 'f' || ((code == 'g' || code == 'G') && (-4 <= xexp) && (xexp < px->precision)))
  {         /* 'f' format */
    ++xexp; /* change to leading digit count */
    if (code != 'f')
    { /* fixup for 'g' */
      if (!(px->flags & FLAGS_HASH) && nsig < px->precision)
      {
        px->precision = nsig;
      }
      if ((px->precision -= xexp) < 0)
      {
        px->precision = 0;
      }
    }
    if (xexp <= 0)
    { /* digits only to right of point */
      px->buff[px->part2_len++] = '0';
      if (0 < px->precision || px->flags & FLAGS_HASH)
      {
        px->buff[px->part2_len++] = point;
      }
      if (px->precision < -xexp)
      {
        xexp = -px->precision;
      }
      px->num_mid_zeros = -xexp;
      px->precision += xexp;
      if (px->precision < nsig)
      {
        nsig = px->precision;
      }
      memcpy(&px->buff[px->part2_len], p, px->part3_len = nsig);
      px->num_trailing_zeros = px->precision - nsig;
    }
    else if (nsig < xexp)
    { /* zeros before point */
      memcpy(&px->buff[px->part2_len], p, nsig);
      px->part2_len += nsig;
      px->num_mid_zeros = xexp - nsig;
      if (0 < px->precision || px->flags & FLAGS_HASH)
      {
        px->buff[px->part2_len] = point, ++px->part3_len;
      }
      px->num_trailing_zeros = px->precision;
    }
    else
    { /* enough digits before point */
      memcpy(&px->buff[px->part2_len], p, xexp);
      px->part2_len += xexp;
      nsig -= xexp;
      if (0 < px->precision || px->flags & FLAGS_HASH)
      {
        px->buff[px->part2_len++] = point;
      }
      if (px->precision < nsig)
      {
        nsig = px->precision;
      }
      memcpy(&px->buff[px->part2_len], p + xexp, nsig);
      px->part2_len += nsig;
      px->num_mid_zeros = px->precision - nsig;
    }
  }
  else
  { /* 'e' format */
    if (code == 'g' || code == 'G')
    { /* fixup for 'g' */
      if (nsig < px->precision)
      {
        px->precision = nsig;
      }
      if (--px->precision < 0)
      {
        px->precision = 0;
      }
      code = code == 'g' ? 'e' : 'E';
    }
    px->buff[px->part2_len++] = *p++;
    if (0 < px->precision || px->flags & FLAGS_HASH)
    {
      px->buff[px->part2_len++] = point;
    }
    if (0 < px->precision)
    { /* put fraction digits */
      if (px->precision < --nsig)
      {
        nsig = px->precision;
      }
      memcpy(&px->buff[px->part2_len], p, nsig);
      px->part2_len += nsig;
      px->num_mid_zeros = px->precision - nsig;
    }
    p = (char *)&px->buff[px->part2_len]; /* put exponent */
    *p++ = code;
    if (0 <= xexp)
    {
      *p++ = '+';
    }
    else
    { /* negative exponent */
      *p++ = '-';
      xexp = -xexp;
    }
    if (100 <= xexp)
    { /* put oversize exponent */
      if (1000 <= xexp)
      {
        *p++ = xexp / 1000 + '0', xexp %= 1000;
      }
      *p++ = xexp / 100 + '0', xexp %= 100;
    }
    *p++ = xexp / 10 + '0', xexp %= 10;
    *p++ = xexp + '0';
    px->part3_len = p - (char *)&px->buff[px->part2_len];
  }
  if ((px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO)
  { /* pad with leading zeros */
    int n =
        px->n0 + px->part2_len + px->num_mid_zeros + px->part3_len + px->num_trailing_zeros;

    if (n < px->width)
    {
      px->num_leading_zeros = px->width - n;
    }
  }
}
