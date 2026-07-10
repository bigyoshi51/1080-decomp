/* IDO 5.3 -O1 donor for gl_func_0006D6F4 — 52-insn __osPfsRequestData
 * (libultra pfsisplug.c TU sibling of 6D554 = osPfsIsPlug; identified
 * 2026-07-09 vs references/libreultra/src/io/pfsisplug.c). PROVEN EXACT
 * 52/52 at IDO 5.3 -O1 (7.1 -O1 = 44/52 — the 8-byte `*(fmt*)ptr =
 * requestformat` struct copy uses the $at lw/swl/swr scratch, the
 * documented 5.3-vs-7.1 discriminator).
 * Verbatim libreultra: builds __OSContRequesFormat {FF,1,3,cmd,FF,FF,FF,FF}
 * on the stack, __osContLastCmd = cmd, __osPfsPifRam.pifstatus = CONT_CMD_
 * EXE(1) (the +0x3C member store — OSPifRam {u8 ramarray[60]; s32
 * pifstatus}), copies it per channel (< __osMaxControllers), then the
 * CONT_CMD_END = 0xFE terminator (sb in the jr delay slot).
 * This retires the old "record-stream emit helper" NM decode: the three
 * globals are DISTINCT symbols (__osContLastCmd / __osPfsPifRam /
 * __osMaxControllers), all blanked USO reloc words -> 0, not one D+0 blob.
 * Blank externs: D_pifram = __osPfsPifRam, D_max = __osMaxControllers,
 * D_lastcmd = __osContLastCmd.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef unsigned char u8;
typedef int s32;
typedef struct { u8 dummy; u8 txsize; u8 rxsize; u8 cmd; u8 typeh; u8 typel; u8 status; u8 dummy1; } ReqFormat;
typedef struct { u8 ramarray[60]; s32 pifstatus; } PifRam;
extern PifRam D_00000000_pifram;
extern u8 D_00000000_max;
extern u8 D_00000000_lastcmd;
void gl_func_0006D6F4(u8 cmd) {
    u8 *ptr;
    ReqFormat requestformat;
    int i;
    ptr = (u8 *)&D_00000000_pifram;
    D_00000000_lastcmd = cmd;
    D_00000000_pifram.pifstatus = 1;
    requestformat.dummy = 0xff;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = cmd;
    requestformat.typeh = 0xff;
    requestformat.typel = 0xff;
    requestformat.status = 0xff;
    requestformat.dummy1 = 0xff;
    for (i = 0; i < D_00000000_max; i++) {
        *(ReqFormat *)ptr = requestformat;
        ptr += sizeof(ReqFormat);
    }
    *ptr = 0xfe;
}
