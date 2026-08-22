/* IDO 5.3 -O3 donor for the libc printf core pair (Plauger xprintf.c
 * verbatim, libreultra source):
 *   gl_func_0006E224 = _Putfld (donor .text [0x000,0x670), static)
 *   gl_func_0006E894 = _Printf (donor .text [0x670,0xCB8))
 * PROVEN EXACT 2026-08-22: 814/814 words vs expected post1b2c.c.o
 * [0x1E24,0x2ADC) with every diff word a reloc field:
 *   - spaces/zeroes TU statics: target bakes ABSOLUTE %hi/%lo 0x2E460
 *     (spaces) / 0x2E484 (zeroes) -- ROM data @0xDD0850 shows 32 spaces
 *     THEN 32 zeros, so spaces is the LOWER address (the 2026-08-22
 *     vein-probe doc had the two swapped). Modelled as pinned externs
 *     gl_spaces_pin6E / gl_zeroes_pin6E.
 *   - donor-local .rodata ("hlL" +0x00, fchar " +-#0" +0x04, fbit[6]
 *     +0x0C, _Putfld's 25-entry 'F'..'^' jumptable +0x24): target bakes
 *     lo 9168/9172/9180/9204 = single base 0x23D0; splice renames the
 *     section relocs to gl_func_0006E224_rodata / gl_func_0006E894_rodata
 *     (pins = 0x23D0). Table/rodata CONTENT already ships in the USO
 *     data segment (6DD14 technique).
 *   - blank USO jals: strchr x3, strlen, _Litob x3, _Ldtob
 *     (gl_func_00000000_* externs, field 0 both sides).
 *   - the ONE intra-TU jal _Printf->_Putfld: target bakes 0x0C020A24
 *     (jal 0x82890, _Putfld's original-link address); donor reloc vs
 *     local .text renamed to gl_func_0006E894_text by the splice,
 *     pinned = 0x82890.
 * WHY -O3: whole-TU interprocedural regalloc gives static _Putfld its
 * custom linkage -- px arrives in $s0 (never saved; the long-documented
 * "caller-set $s0 permanent cap" on 6E224 was exactly this), code in a1,
 * pap in a2, ac in a3. IDO stdarg (libreultra 2.0I) supplies the
 * align-then-bump va_arg forms ((p+3&~3)+4 / (p+7&~7)+8).
 * ROM/donor emission order is _Putfld then _Printf (IDO -O3 emits the
 * static first, as with _Genld in game_libs_ido53_73904.c).
 * Statics keep no symtab entry at -O3, so the donor rule's POST_COMPILE
 * injects gl_func_0006E224 and renames _Printf -> gl_func_0006E894.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */

typedef unsigned int size_t;
#define NULL 0
typedef signed long long s64;
typedef unsigned long long u64;
typedef signed short s16;
typedef unsigned short u16;
typedef double f64;

/* IDO stdarg */
typedef char *va_list;
#define _FP 1
#define _INT 0
#define _STRUCT 2
#define _VA_FP_SAVE_AREA 0x10
#define _VA_ALIGN(p, a) (((unsigned int)(((char *)p) + ((a) > 4 ? (a) : 4) - 1)) & -((a) > 4 ? (a) : 4))
#define __va_stack_arg(list, mode)                                 \
  (                                                                \
      ((list) = (char *)_VA_ALIGN(list, __builtin_alignof(mode)) + \
                _VA_ALIGN(sizeof(mode), 4)),                       \
      (((char *)list) - (_VA_ALIGN(sizeof(mode), 4) - sizeof(mode))))
#define __va_double_arg(list, mode)                                                                  \
  (                                                                                                  \
      (((long)list & 0x1)                                                                            \
           ? (list = (char *)((long)list + 7), (char *)((long)list - 6 - _VA_FP_SAVE_AREA))          \
           : (((long)list & 0x2)                                                                     \
                  ? (list = (char *)((long)list + 10), (char *)((long)list - 24 - _VA_FP_SAVE_AREA)) \
                  : __va_stack_arg(list, mode))))
#define va_arg(list, mode) ((mode *)(((__builtin_classof(mode) == _FP &&          \
                                       __builtin_alignof(mode) == sizeof(double)) \
                                          ? __va_double_arg(list, mode)           \
                                          : __va_stack_arg(list, mode))))[-1]

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
typedef char *outfun(char *, const char *, size_t);

/* blank USO-reloc externs (jal field 0) */
extern char *gl_func_00000000_strchr6E(const char *, int);
extern size_t gl_func_00000000_strlen6E(const char *);
extern void gl_func_00000000_litob6E(printf_struct *, char);
extern void gl_func_00000000_ldtob6E(printf_struct *, char);
#define strchr gl_func_00000000_strchr6E
#define strlen gl_func_00000000_strlen6E
#define _Litob gl_func_00000000_litob6E
#define _Ldtob gl_func_00000000_ldtob6E

/* spaces/zeroes: baked-absolute pinned externs (0x2E484 / 0x2E460) */
extern char gl_spaces_pin6E[33];
extern char gl_zeroes_pin6E[33];
#define spaces gl_spaces_pin6E
#define zeroes gl_zeroes_pin6E

#define isdigit(x) ((x >= '0' && x <= '9'))
#define LDSIGN(x) (((unsigned short *)&(x))[0] & 0x8000)

#define ATOI(dst, src)                   \
    for (dst = 0; isdigit(*src); ++src)  \
    {                                    \
        if (dst < 999)                   \
            dst = dst * 10 + *src - '0'; \
    }

#define MAX_PAD ((sizeof(spaces) - 1))
#define PAD(s, n)                                             \
    if (0 < (n))                                              \
    {                                                         \
        int i, j = (n);                                       \
        for (; 0 < j; j -= i)                                 \
        {                                                     \
            i = MAX_PAD < (unsigned int)j ? (int)MAX_PAD : j; \
            PUT(s, i);                                        \
        }                                                     \
    }
#define PUT(s, n)                                \
    if (0 < (n))                                 \
    {                                            \
        if ((arg = (*prout)(arg, s, n)) != NULL) \
            x.size += (n);                       \
        else                                     \
            return x.size;                       \
    }

static void _Putfld(printf_struct *pf, va_list *pap, char code, char *ac);

int _Printf(outfun prout, char *arg, const char *fmt, va_list args)
{
    printf_struct x;
    const char *s;
    char c;
    const char *t;
    static const char fchar[6] = " +-#0";
    static const int fbit[6] = {FLAGS_SPACE, FLAGS_PLUS, FLAGS_MINUS, FLAGS_HASH, FLAGS_ZERO, 0};
    char ac[32];
    x.size = 0;
    for (;;)
    {
        s = fmt;
        for (c = *s; c != 0 && c != '%';)
        {
            c = *++s;
        }
        PUT(fmt, s - fmt);
        if (c == 0)
            return x.size;
        fmt = ++s;
        for (x.flags = 0; (t = strchr(fchar, *s)) != NULL; s++)
        {
            x.flags |= fbit[t - fchar];
        }
        if (*s == '*')
        {
            x.width = va_arg(args, int);
            if (x.width < 0)
            {
                x.width = -x.width;
                x.flags |= FLAGS_MINUS;
            }
            s++;
        }
        else
        {
            ATOI(x.width, s);
        }
        if (*s != '.')
            x.precision = -1;
        else if (*++s == '*')
        {
            x.precision = va_arg(args, int);
            ++s;
        }
        else
        {
            ATOI(x.precision, s);
        }
        x.length = strchr("hlL", *s) ? *s++ : '\0';
        if (x.length == 'l' && *s == 'l')
        {
            x.length = 'L';
            ++s;
        }
        _Putfld(&x, &args, *s, ac);
        x.width -= x.n0 + x.num_leading_zeros + x.part2_len + x.num_mid_zeros + x.part3_len + x.num_trailing_zeros;
        if (!(x.flags & FLAGS_MINUS))
            PAD(spaces, x.width);
        PUT(ac, x.n0);
        PAD(zeroes, x.num_leading_zeros);
        PUT(x.buff, x.part2_len);
        PAD(zeroes, x.num_mid_zeros);
        PUT(x.buff + x.part2_len, x.part3_len);
        PAD(zeroes, x.num_trailing_zeros);
        if (x.flags & FLAGS_MINUS)
            PAD(spaces, x.width);
        fmt = s + 1;
    }
    return 0;
}

static void _Putfld(printf_struct *x, va_list *args, char type, char *buff)
{
    x->n0 = x->num_leading_zeros = x->part2_len = x->num_mid_zeros = x->part3_len =
        x->num_trailing_zeros = 0;

    switch (type)
    {
    case 'c':
        buff[x->n0++] = va_arg(*args, int);
        break;

    case 'd':
    case 'i':
        if (x->length == 'l')
            x->value.s64 = va_arg(*args, int);
        else if (x->length == 'L')
            x->value.s64 = va_arg(*args, s64);
        else
            x->value.s64 = va_arg(*args, int);

        if (x->length == 'h')
        {
            x->value.s64 = (s16)x->value.s64;
        }

        if (x->value.s64 < 0)
        {
            buff[x->n0++] = '-';
        }
        else if (x->flags & FLAGS_PLUS)
        {
            buff[x->n0++] = '+';
        }
        else if (x->flags & FLAGS_SPACE)
        {
            buff[x->n0++] = ' ';
        }

        x->buff = (char *)&buff[x->n0];

        _Litob(x, type);
        break;

    case 'x':
    case 'X':
    case 'u':
    case 'o':
        if (x->length == 'l')
        {
            x->value.s64 = va_arg(*args, int);
        }
        else if (x->length == 'L')
        {
            x->value.s64 = va_arg(*args, s64);
        }
        else
        {
            x->value.s64 = va_arg(*args, int);
        }

        if (x->length == 'h')
        {
            x->value.s64 = (u16)x->value.s64;
        }
        else if (x->length == 0)
        {
            x->value.s64 = (unsigned int)x->value.s64;
        }

        if (x->flags & FLAGS_HASH)
        {
            buff[x->n0++] = '0';
            if (type == 'x' || type == 'X')
            {
                buff[x->n0++] = type;
            }
        }
        x->buff = (char *)&buff[x->n0];
        _Litob(x, type);
        break;

    case 'e':
    case 'f':
    case 'g':
    case 'E':
    case 'G':
        x->value.f64 = x->length == 'L' ? va_arg(*args, f64) : va_arg(*args, f64);

        if (LDSIGN(x->value.f64))
            buff[x->n0++] = '-';
        else if (x->flags & FLAGS_PLUS)
            buff[x->n0++] = '+';
        else if (x->flags & FLAGS_SPACE)
            buff[x->n0++] = ' ';

        x->buff = (char *)&buff[x->n0];
        _Ldtob(x, type);
        break;

    case 'n':
        if (x->length == 'h')
            *(va_arg(*args, u16 *)) = x->size;
        else if (x->length == 'l')
            *va_arg(*args, unsigned int *) = x->size;
        else if (x->length == 'L')
            *va_arg(*args, u64 *) = x->size;
        else
            *va_arg(*args, unsigned int *) = x->size;
        break;

    case 'p':
        x->value.s64 = (long)va_arg(*args, void *);
        x->buff = (char *)&buff[x->n0];
        _Litob(x, 'x');
        break;

    case 's':
        x->buff = va_arg(*args, char *);
        x->part2_len = strlen(x->buff);
        if (x->precision >= 0 && x->part2_len > x->precision)
            x->part2_len = x->precision;
        break;
    case '%':
        buff[x->n0++] = '%';
        break;
    default:
        buff[x->n0++] = type;
        break;
    }
}
