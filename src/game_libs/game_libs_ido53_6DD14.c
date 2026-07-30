/* IDO 5.3 -O1 donor for gl_func_0006DD14 = libultra __osDevMgrMain
 * (devmgr.c verbatim, 2.0I struct layout). The PI device-manager thread
 * loop: recv on dm->cmdQueue; 64DD LEO block/track transfers get the
 * special path (sectorNum=-1, dramAddr rewind for non-sector mode,
 * LEO_BM_CTL start write, evtQueue completion loop with LEO_ERROR_29
 * reset recovery + PI_STATUS_REG clear), everything else dispatches on
 * mb->hdr.type: DMAREAD/DMAWRITE via dm->dma, EDMAREAD/EDMAWRITE via
 * dm->edma, LOOPBACK echoes. Sibling of the already-landed LEO family
 * donors (6DA74 osCreatePiManager, 6F088 osLeoDiskInit, 6DC0C
 * osCartRomInit). No data relocs: LEO_BM_CTL/LEO_STATUS (0x0500051x)
 * and PI_STATUS_REG (0xA4600010) are absolute literals; the only relocs
 * are the seven blank jals. Spliced into game_libs_post1b2c.c.o via
 * REPLACE_FUNC_BODY (donor relocs imported, resolve to 0 via
 * undefined_syms_auto). */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef void *OSMesg;

typedef struct {
    u32 errStatus;      /* 0x00 */
    void *dramAddr;     /* 0x04 */
    void *C2Addr;       /* 0x08 */
    u32 sectorSize;     /* 0x0C */
    u32 C1ErrNum;       /* 0x10 */
    u32 C1ErrSector[4]; /* 0x14 */
} __OSBlockInfo; /* sizeof = 0x24 */

typedef struct {
    u32 cmdType;          /* 0x00 */
    u16 transferMode;     /* 0x04 */
    u16 blockNum;         /* 0x06 */
    s32 sectorNum;        /* 0x08 */
    u32 devAddr;          /* 0x0C */
    u32 bmCtlShadow;      /* 0x10 */
    u32 seqCtlShadow;     /* 0x14 */
    __OSBlockInfo block[2]; /* 0x18 */
} __OSTranxInfo;

typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next;  /* 0x00 */
    u8 type;                    /* 0x04 */
    u8 latency;                 /* 0x05 */
    u8 pageSize;                /* 0x06 */
    u8 relDuration;             /* 0x07 */
    u8 pulse;                   /* 0x08 */
    u8 domain;                  /* 0x09 */
    u32 baseAddress;            /* 0x0C */
    u32 speed;                  /* 0x10 */
    __OSTranxInfo transferInfo; /* 0x14 */
} OSPiHandle;

typedef struct {
    u16 type;   /* 0x00 */
    u8 pri;     /* 0x02 */
    u8 status;  /* 0x03 */
    void *retQueue; /* 0x04 (OSMesgQueue *) */
} OSIoMesgHdr;

typedef struct {
    OSIoMesgHdr hdr;    /* 0x00 */
    void *dramAddr;     /* 0x08 */
    u32 devAddr;        /* 0x0C */
    u32 size;           /* 0x10 */
    OSPiHandle *piHandle; /* 0x14 */
} OSIoMesg;

typedef struct {
    s32 active;         /* 0x00 */
    void *thread;       /* 0x04 */
    void *cmdQueue;     /* 0x08 (OSMesgQueue *) */
    void *evtQueue;     /* 0x0C */
    void *acsQueue;     /* 0x10 */
    s32 (*dma)(s32, u32, void *, u32);              /* 0x14 */
    s32 (*edma)(OSPiHandle *, s32, u32, void *, u32); /* 0x18 */
} OSDevMgr;

extern s32 gl_func_00000000_recv(void *, OSMesg *, s32);   /* osRecvMesg */
extern s32 gl_func_00000000_send(void *, OSMesg, s32);     /* osSendMesg */
extern s32 gl_func_00000000_ewio(OSPiHandle *, u32, u32);  /* osEPiRawWriteIo */
extern s32 gl_func_00000000_erio(OSPiHandle *, u32, u32 *);/* osEPiRawReadIo */
extern void gl_func_00000000_rgim(u32);                    /* __osResetGlobalIntMask */
extern void gl_func_00000000_sgim(u32);                    /* __osSetGlobalIntMask */
extern void gl_func_00000000_yield(void);                  /* osYieldThread */

void gl_func_0006DD14(void *args)
{
    OSIoMesg *mb;
    OSMesg em;
    OSMesg dummy;
    s32 ret;
    OSDevMgr *dm;
    s32 messageSend;

    messageSend = 0;
    mb = 0;
    ret = 0;
    dm = (OSDevMgr *)args;
    while (1) {
        gl_func_00000000_recv(dm->cmdQueue, (OSMesg *)&mb, 1);
        if (mb->piHandle != 0 &&
            mb->piHandle->type == 2 &&
            (mb->piHandle->transferInfo.cmdType == 0 ||
             mb->piHandle->transferInfo.cmdType == 1)) {
            __OSBlockInfo *blockInfo;
            __OSTranxInfo *info;
            info = &mb->piHandle->transferInfo;
            blockInfo = &info->block[info->blockNum];
            info->sectorNum = -1;
            if (info->transferMode != 3) {
                blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr - blockInfo->sectorSize);
            }
            if (info->transferMode == 2 && mb->piHandle->transferInfo.cmdType == 0)
                messageSend = 1;
            else
                messageSend = 0;
            gl_func_00000000_recv(dm->acsQueue, &dummy, 1);
            gl_func_00000000_rgim(0x00100401);
            gl_func_00000000_ewio(mb->piHandle, 0x05000510, info->bmCtlShadow | 0x80000000);
            while (1) {
                gl_func_00000000_recv(dm->evtQueue, &em, 1);
                info = &mb->piHandle->transferInfo;
                blockInfo = &info->block[info->blockNum];
                if (blockInfo->errStatus == 29) {
                    u32 stat;
                    gl_func_00000000_ewio(mb->piHandle, 0x05000510, info->bmCtlShadow | 0x10000000);
                    gl_func_00000000_ewio(mb->piHandle, 0x05000510, info->bmCtlShadow);
                    gl_func_00000000_erio(mb->piHandle, 0x05000508, &stat);
                    if (stat & 0x02000000) {
                        gl_func_00000000_ewio(mb->piHandle, 0x05000510, info->bmCtlShadow | 0x01000000);
                    }
                    blockInfo->errStatus = 4;
                    *(volatile u32 *)0xA4600010 = 2;
                    gl_func_00000000_sgim(0x00100C01);
                }
                gl_func_00000000_send(mb->hdr.retQueue, mb, 0);
                if (messageSend != 1)
                    break;
                if (mb->piHandle->transferInfo.block[0].errStatus != 0)
                    break;
                messageSend = 0;
            }
            gl_func_00000000_send(dm->acsQueue, 0, 0);
            if (mb->piHandle->transferInfo.blockNum == 1)
                gl_func_00000000_yield();
        } else {
            switch (mb->hdr.type) {
            case 10: /* OS_MESG_TYPE_DMAREAD */
                gl_func_00000000_recv(dm->acsQueue, &dummy, 1);
                ret = dm->dma(0, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case 11: /* OS_MESG_TYPE_DMAWRITE */
                gl_func_00000000_recv(dm->acsQueue, &dummy, 1);
                ret = dm->dma(1, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case 12: /* OS_MESG_TYPE_EDMAREAD */
                gl_func_00000000_recv(dm->acsQueue, &dummy, 1);
                ret = dm->edma(mb->piHandle, 0, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case 13: /* OS_MESG_TYPE_EDMAWRITE */
                gl_func_00000000_recv(dm->acsQueue, &dummy, 1);
                ret = dm->edma(mb->piHandle, 1, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case 14: /* OS_MESG_TYPE_LOOPBACK */
                gl_func_00000000_send(mb->hdr.retQueue, mb, 0);
                ret = -1;
                break;
            case 15: /* jumptable spans 10..16 (sltiu 7): 15/16 -> default */
            case 16:
            default:
                ret = -1;
                break;
            }
            if (ret == 0) {
                gl_func_00000000_recv(dm->evtQueue, &em, 1);
                gl_func_00000000_send(mb->hdr.retQueue, mb, 0);
                gl_func_00000000_send(dm->acsQueue, 0, 0);
            }
        }
    }
}
