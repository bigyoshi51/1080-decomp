/* IDO 5.3 -O2 donor for gl_func_00074554 = _Litob (Plauger libc
 * xlitob.c verbatim) -- the printf integer-formatter, completing the
 * xldtob.c pair (73904=_Genld / 73E74=_Ldtob) and the ldiv identity
 * (744CC). PROVEN EXACT 2026-08-22 probe: 166/166 words vs expected
 * [0xEC0,0x1158) of game_libs_post2b_d.c.o at IDO 5.3 -O2 -mips2 (7.1
 * diverges in 77 words; -O3 identical to -O2 here). The only diff words
 * are the four ldigs/udigs .data reloc fields: target bakes hi 0x3 /
 * lo 0xE620("0123..def")+0xE634("0123..DEF") = .data base 0x2E620 in
 * the USO data segment; donor-local .data reloc renamed
 * gl_func_00074554_data by the splice, pinned 0x2E620.
 * Blank USO jals (field 0 both sides): __ull_rem / __ull_div
 * (compiler-generated for the u64 %/ base -- POST_COMPILE objcopy
 * redefines them to gl_func_00000000_* blanks, since __ull_div is
 * pinned to its KERNEL address 0x80002E78 for other units while the
 * USO ships this jal blank; the USO's load-time reloc table points it
 * at the game_libs copies 6C740/6C77C), lldiv, memcpy.
 * Spliced into game_libs_post2b_d.c.o via REPLACE_FUNC_BODY. */

typedef unsigned int size_t;
typedef int s32;

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

typedef struct lldiv_t
{
    long long quot;
    long long rem;
} lldiv_t;

extern void *gl_func_00000000_mcpy73(void *, const void *, size_t);
extern lldiv_t gl_func_00000000_lldiv74(long long, long long);
#define memcpy gl_func_00000000_mcpy73
#define lldiv gl_func_00000000_lldiv74

#define BUFF_LEN 0x18

static char ldigs[] = "0123456789abcdef";
static char udigs[] = "0123456789ABCDEF";

void gl_func_00074554(printf_struct *args, char type)
{
  char buff[BUFF_LEN];
  const char *digs;
  s32 base;
  s32 i;
  unsigned long long ullval;

  if (type == 'X')
  {
    digs = udigs;
  }
  else
  {
    digs = ldigs;
  }

  base = (type == 'o') ? 8 : ((type != 'x' && type != 'X') ? 10 : 16);
  i = BUFF_LEN;
  ullval = args->value.s64;

  if ((type == 'd' || type == 'i') && args->value.s64 < 0)
  {
    ullval = -ullval;
  }

  if (ullval != 0 || args->precision != 0)
  {
    buff[--i] = digs[ullval % base];
  }

  args->value.s64 = ullval / base;

  while (args->value.s64 > 0 && i > 0)
  {

    lldiv_t qr = lldiv(args->value.s64, base);
    args->value.s64 = qr.quot;
    buff[--i] = digs[qr.rem];
  }

  args->part2_len = BUFF_LEN - i;

  memcpy(args->buff, buff + i, args->part2_len);

  if (args->part2_len < args->precision)
  {
    args->num_leading_zeros = args->precision - args->part2_len;
  }

  if (args->precision < 0 && (args->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO)
  {
    i = args->width - args->n0 - args->num_leading_zeros - args->part2_len;
    if (i > 0)
    {
      args->num_leading_zeros += i;
    }
  }
}
