/* IDO -O1 donor for gl_func_0006D964 = libultra osPiStartDma
 * (references/libreultra/src/io/pidma.c, verbatim). PROVEN EXACT 67/67
 * standalone at BOTH IDO 7.1 -O1 and 5.3 -O1 (identical output; built with
 * 7.1), agent-g 2026-09-09, first compile. Section 0x81FD0 = bootup.uso
 * export sym 1530 (two jal refs at 0x47EBC / 0x47F8C); the reloc at +4 is
 * sym 2612 (.data 0x2E430 = __osPiDevMgr, the same symbol the 6DA74
 * osCreatePiManager donor imports as gl_devmgr_6DA74). The old 54% NM decode
 * ("67-insn command-record builder + dual-dispatch helper, 20-byte record,
 * halfword type 0xC/0xB, kind-gated builder pair") was this function at the
 * wrong opt level: the record is the OSIoMesg (type OS_MESG_TYPE_DMAWRITE 12
 * / DMAREAD 11, pri @2, retQueue @4, dramAddr @8, devAddr @C, size @10,
 * piHandle @14 = NULL), the "builder pair" is osJamMesg(osPiGetCmdQueue(),..)
 * for OS_MESG_PRI_HIGH else osSendMesg(osPiGetCmdQueue(),..), and the
 * "reload every arg before every use from the sp+0x28.. homes" is the -O1
 * tell (the same shape as osEPiStartDma 6EF64). `register s32 ret` is the
 * source's spelling. The trailing zero word of the old 0x110 .s (section
 * 0x820DC, NOT exported; 6DA74 at 0x820E0 is) is this object's own 16-byte
 * alignment pad -> SUFFIX_BYTES_FORCE gl_func_0006D964=0x00000000, and the
 * tracked .s is trimmed to the 67-word body (0x10C).
 * Blank externs (USO load-time relocs, pins = 0): gl_devmgr_6DA74 =
 * __osPiDevMgr, gl_func_00000000_pigetcmdq = osPiGetCmdQueue,
 * gl_func_00000000_jammesg6d = osJamMesg, gl_func_00000000_sendmesg =
 * osSendMesg. Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef void *OSMesg;

typedef struct {
    /* 0x00 */ u32 active;
    /* 0x04 */ void *thread;
    /* 0x08 */ void *cmdQueue;
    /* 0x0C */ void *evtQueue;
    /* 0x10 */ void *acsQueue;
    /* 0x14 */ s32 (*dma)();
    /* 0x18 */ s32 (*edma)();
} OSDevMgr;

typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pri;
    /* 0x03 */ u8 status;
    /* 0x04 */ void *retQueue;
} OSIoMesgHdr;

typedef struct {
    /* 0x00 */ OSIoMesgHdr hdr;
    /* 0x08 */ void *dramAddr;
    /* 0x0C */ u32 devAddr;
    /* 0x10 */ u32 size;
    /* 0x14 */ void *piHandle;
} OSIoMesg;

#define OS_READ 0
#define OS_MESG_TYPE_DMAREAD 11
#define OS_MESG_TYPE_DMAWRITE 12
#define OS_MESG_PRI_HIGH 1
#define OS_MESG_NOBLOCK 0
#define NULL 0

extern OSDevMgr gl_devmgr_6DA74;                                  /* __osPiDevMgr */
extern void *gl_func_00000000_pigetcmdq(void);                    /* osPiGetCmdQueue */
extern s32 gl_func_00000000_jammesg6d(void *, OSMesg, s32);       /* osJamMesg */
extern s32 gl_func_00000000_sendmesg(void *, OSMesg, s32);        /* osSendMesg */
#define __osPiDevMgr gl_devmgr_6DA74
#define osPiGetCmdQueue gl_func_00000000_pigetcmdq
#define osJamMesg gl_func_00000000_jammesg6d
#define osSendMesg gl_func_00000000_sendmesg

s32 gl_func_0006D964(OSIoMesg *mb, s32 priority, s32 direction, u32 devAddr, void *dramAddr, u32 size, void *mq)
{
    register s32 ret;
    if (!__osPiDevMgr.active)
        return -1;
    if (direction == OS_READ)
        mb->hdr.type = OS_MESG_TYPE_DMAREAD;
    else
        mb->hdr.type = OS_MESG_TYPE_DMAWRITE;
    mb->hdr.pri = priority;
    mb->hdr.retQueue = mq;
    mb->dramAddr = dramAddr;
    mb->devAddr = devAddr;
    mb->size = size;
    mb->piHandle = NULL;
    if (priority == OS_MESG_PRI_HIGH)
    {
        ret = osJamMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    }
    else
    {
        ret = osSendMesg(osPiGetCmdQueue(), (OSMesg)mb, OS_MESG_NOBLOCK);
    }
    return ret;
}
