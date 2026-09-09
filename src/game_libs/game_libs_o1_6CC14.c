/* IDO -O1 donor for gl_func_0006CC14 = libultra osEPiLinkHandle
 * (references/libreultra/src/io/epilinkhandle.c, verbatim). PROVEN EXACT
 * 19/19 (incl. the jr-ra delay nop) standalone at BOTH IDO 7.1 -O1 and
 * 5.3 -O1 (identical output; built with 7.1), agent-g 2026-09-09. Section
 * 0x81280 = bootup.uso export sym 1583 (one jal ref at 0x491AC). The old
 * 93.56% NM decode ("2-call helper, D / D_cc14_alias2, volatile spill
 * cross") was this function: both globals are __osPiTable (handle->next @0
 * = __osPiTable; __osPiTable = handle), the sp+0x1C spill is the
 * un-`register`ed saveMask. The tracked .s is 18 words (ends at jr ra) and
 * gl_func_0006CC14_pad.s carried the delay nop + the 16-byte inter-object
 * pad word before osEPiReadIo (6CC64 section 0x812D0); the C body emits
 * its own delay nop, so the pad.s pragma is retired and the single pad
 * word is an all-zero SUFFIX_BYTES_FORCE gl_func_0006CC14=0x00000000.
 * Blank externs (USO load-time relocs, existing pins = 0):
 * D_00000000_pitable = __osPiTable, gl_func_00000000_disint =
 * __osDisableInt, gl_func_00000000_resint = __osRestoreInt. Spliced into
 * game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef signed int s32;

typedef struct OSPiHandle_s {
    /* 0x00 */ struct OSPiHandle_s *next;
    /* 0x04 */ unsigned char type;
    /* 0x05 */ unsigned char latency;
    /* 0x06 */ unsigned char pageSize;
    /* 0x07 */ unsigned char relDuration;
    /* 0x08 */ unsigned char pulse;
    /* 0x09 */ unsigned char domain;
    /* 0x0C */ u32 baseAddress;
    /* 0x10 */ u32 speed;
    /* 0x14 */ u32 transferInfo[2];
} OSPiHandle;

extern OSPiHandle *D_00000000_pitable;      /* __osPiTable */
extern u32 gl_func_00000000_disint(void);   /* __osDisableInt */
extern void gl_func_00000000_resint(u32);   /* __osRestoreInt */
#define __osPiTable D_00000000_pitable
#define __osDisableInt gl_func_00000000_disint
#define __osRestoreInt gl_func_00000000_resint

s32 gl_func_0006CC14(OSPiHandle *handle)
{
    u32 saveMask;
    saveMask = __osDisableInt();
    handle->next = __osPiTable;
    __osPiTable = handle;
    __osRestoreInt(saveMask);
    return 0;
}
