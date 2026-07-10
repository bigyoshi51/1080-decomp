/* IDO 5.3 -O1 donor for gl_func_0006D7CC — 52-insn __osPfsGetInitData
 * (libultra pfsisplug.c TU sibling of 6D554 = osPfsIsPlug; identified
 * 2026-07-09 vs references/libreultra/src/io/pfsisplug.c). PROVEN EXACT
 * 52/52 at IDO 5.3 -O1 against the MERGED span 0x6D7C4..0x6D890 (7.1 -O1
 * = 35/52; 8-byte lwl/lwr $at struct copy = the 5.3 discriminator).
 * BOUNDARY FIX (41008 precedent): the 2-word orphan game_libs_func_
 * 0006D7C4 (`lui t7,%hi(__osMaxControllers); lbu t7,%lo(...)`) is this
 * function's first load, scheduled BEFORE the addiu-sp prologue by 5.3;
 * splat mis-split it. Its INCLUDE_ASM is removed and the donor's 52 words
 * cover 0x6D7C4..0x6D890 (2 orphan + 50 labeled).
 * 1080 deltas vs libreultra: compact 4-byte OSContStatus {u16 type; u8
 * status; u8 errno} (data++ = addiu a1,4 in the loop-branch delay slot).
 * Everything else verbatim: per-channel 8-byte __OSContRequesFormat
 * readback, errno = CHNL_ERR = (rxsize & 0xC0) >> 4, type = typel<<8 |
 * typeh, bits |= 1<<i, *pattern = bits (sb in the jr delay).
 * Blank externs: D_pifram = __osPfsPifRam, D_max = __osMaxControllers.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { u8 dummy; u8 txsize; u8 rxsize; u8 cmd; u8 typeh; u8 typel; u8 status; u8 dummy1; } ReqFormat;
typedef struct { u16 type; u8 status; u8 errnum; } StatusData;
extern u8 D_00000000_pifram[];
extern u8 D_00000000_max;
void gl_func_0006D7CC(u8 *pattern, StatusData *data) {
    u8 *ptr;
    ReqFormat requestformat;
    int i;
    u8 bits;
    bits = 0;
    ptr = D_00000000_pifram;
    for (i = 0; i < D_00000000_max; i++, ptr += sizeof(ReqFormat)) {
        requestformat = *(ReqFormat *)ptr;
        data->errnum = (requestformat.rxsize & 0xc0) >> 4;
        if (data->errnum == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
        data++;
    }
    *pattern = bits;
}
