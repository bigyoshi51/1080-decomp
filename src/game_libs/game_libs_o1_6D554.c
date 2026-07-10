/* IDO 7.1 -O1 donor for gl_func_0006D554 — 104-insn osPfsIsPlug (libultra
 * pfsisplug.c, identified 2026-07-09 vs references/libreultra/src/io/
 * pfsisplug.c; decode matches line-for-line). PROVEN EXACT 104/104 at plain
 * 7.1 -O1, first probe (5.3 not needed — no struct copy, so no $at
 * discriminator).
 * 1080 deltas vs libreultra: MAXCONTROLLERS = 4 (data[4], 16 bytes at
 * sp+0x24) and a compact 4-byte OSContStatus {u16 type; u8 status; u8
 * errno} (sll channel,2 indexing; status at +2, errno at +3). Everything
 * else verbatim: crc_error_cnt = 3, __osPfsRequestData(CONT_CMD_REQUEST_
 * STATUS = 0), OS_WRITE/OS_READ __osSiRawStartDma pair around osRecvMesg,
 * CONT_ADDR_CRC_ER = 0x04 retry loop, CONT_CARD_ON = 0x01 bit build.
 * Locals take decl-order slots: ret 0x3C, dummy 0x38, bitpattern 0x37,
 * data 0x24, channel 0x20, bits 0x1F, crc_error_cnt 0x18.
 * Blank externs (all game_libs-internal, USO reloc words blanked = link
 * to 0): fn0 = __osSiGetAccess, fn1 = __osPfsRequestData,
 * fn2 = __osSiRawStartDma, fn3 = osRecvMesg, fn4 = __osPfsGetInitData,
 * fn5 = __osSiRelAccess; D_pifram = __osPfsPifRam, D_max =
 * __osMaxControllers. The TU siblings are the 6D6F4/6D7CC donors
 * (__osPfsRequestData / __osPfsGetInitData, both IDO 5.3).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef struct { u16 type; u8 status; u8 errnum; } StatusData;
extern u8 D_00000000_pifram[];
extern u8 D_00000000_max;
extern void gl_func_00000000(void);
extern void gl_func_00000001(u8);
extern s32 gl_func_00000002(s32, void *);
extern s32 gl_func_00000003(void *, void *, s32);
extern void gl_func_00000004(u8 *, StatusData *);
extern void gl_func_00000005(void);
s32 gl_func_0006D554(void *queue, u8 *pattern) {
    s32 ret;
    void *dummy;
    u8 bitpattern;
    StatusData data[4];
    int channel;
    u8 bits;
    int crc_error_cnt;
    ret = 0;
    bits = 0;
    crc_error_cnt = 3;
    gl_func_00000000();
    while (1) {
        gl_func_00000001(0);
        ret = gl_func_00000002(1, D_00000000_pifram);
        gl_func_00000003(queue, &dummy, 1);
        ret = gl_func_00000002(0, D_00000000_pifram);
        gl_func_00000003(queue, &dummy, 1);
        gl_func_00000004(&bitpattern, data);
        for (channel = 0; channel < D_00000000_max; channel++) {
            if ((data[channel].status & 4) == 0) {
                crc_error_cnt--;
                break;
            }
        }
        if (D_00000000_max == channel)
            crc_error_cnt = 0;
        if (crc_error_cnt < 1) {
            for (channel = 0; channel < D_00000000_max; channel++) {
                if (data[channel].errnum == 0 && (data[channel].status & 1) != 0)
                    bits |= 1 << channel;
            }
            gl_func_00000005();
            *pattern = bits;
            return ret;
        }
    }
}
