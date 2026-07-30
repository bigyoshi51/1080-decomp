/* IDO 5.3 -O1 donor for gl_func_000717CC = libultra
 * __osPfsGetOneChannelData (io/pfsgetstatus.c verbatim, 2.0I layout) --
 * pfs sibling family; __osPfsGetStatus=gl_func_00071624 jals this as its
 * last call. TRUE ENTRY 0x717C8: the compiled function's first insn is
 * `lui $t6,%hi(__osPfsPifRam)`, which the old split carried as the
 * 1-word _pad_pre_717CC stolen-prologue orphan (split off
 * gl_func_00071708.s, see that donor's comment); folded back into
 * gl_func_000717CC.s so the symbol covers all 39 words. PROVEN EXACT
 * 39/39 vs the 0x717C8..0x71860 stream (2026-07-30 probe): donor word k
 * == expected[k-1] for the old 38-word symbol, word 0 == the orphan lui;
 * the single data reloc pair (__osPfsPifRam lui/addiu) is addend-0 =
 * blank D_00000000 extern; no calls. CHNL_ERR = (rxsize & 0xC0) >> 4.
 * Spliced into game_libs_post2.c.o via REPLACE_FUNC_BODY. */
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct
{
    u16 type;   /* 0x0 */
    u8 status;  /* 0x2 */
    u8 errno;   /* 0x3 */
} OSContStatus;

typedef struct
{
    u8 txsize;  /* 0x0 */
    u8 rxsize;  /* 0x1 */
    u8 cmd;     /* 0x2 */
    u8 typeh;   /* 0x3 */
    u8 typel;   /* 0x4 */
    u8 status;  /* 0x5 */
} __OSContRequesFormatShort;

extern u8 D_00000000; /* __osPfsPifRam */

void gl_func_000717CC(int channel, OSContStatus *data)
{
    u8 *ptr;
    __OSContRequesFormatShort requestformat;
    int i;
    ptr = &D_00000000;
    for (i = 0; i < channel; i++)
        ptr++;
    requestformat = *(__OSContRequesFormatShort *)ptr;
    data->errno = (requestformat.rxsize & 0xC0) >> 4;
    if (data->errno == 0)
    {
        data->type = (requestformat.typel << 8) | (requestformat.typeh);
        data->status = requestformat.status;
    }
}
