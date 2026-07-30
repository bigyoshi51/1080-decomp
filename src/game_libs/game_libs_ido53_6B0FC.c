/* IDO 5.3 -O1 donor for gl_func_0006B0FC = libultra __osLeoInterrupt
 * (io/leointerrupt.c verbatim, 2.0-era struct layout): the 64DD LEO
 * cart-interrupt service routine. PI_STATUS DMA-busy => LEO_ERROR_29 +
 * __OSGlobalIntMask &= ~SR_IBIT4 + resume; LEO_STATUS mechanic-interrupt
 * ack via LEO_BM_CTL |= CLR_MECHANIC_INTR; buffer-manager-error =>
 * LEO_ERROR_22; cmdType1 (write) sector chaining via osEPiRawStartDma
 * OS_WRITE LEO_SECTOR_BUFF; cmdType0 (read) path: C1 error bookkeeping
 * (C1ErrSector[4]), C2 transfer kickoff (LEO_C2_BUFF, sectorSize*4),
 * track-mode block flip, final C2-buffer zero check. The old NM wrap's
 * "caller-set $t6" was the stolen-prologue misread: the 2-word orphan
 * game_libs_func_0006B0F4 lui/lw pair is this function's __osDiskHandle
 * load, so the donor's true entry is 0x6B0F4 and the splice covers
 * 0x6B0F4..0x6B790 (orphan words absorbed into the host .s; the leading
 * alignment nop at 0x6B0F0 stays as the 1-word pad INCLUDE_ASM).
 * Blank externs: D_00000000_ldh = __osDiskHandle, D_00000000_gim =
 * __OSGlobalIntMask, gl_func_00000000_edma = osEPiRawStartDma (blank
 * in-segment jal = gl_func_0006F8A4); baked jals gl_ref_0007FEEC =
 * __osLeoResume / gl_ref_0007FE04 = __osLeoAbnormalResume (out-of-
 * segment, hardcoded 0C01FFBB/0C01FF81 like the 6B7A0 donor). LEO regs
 * are absolute 0xA500050x literals (no reloc). Spliced into
 * game_libs_post1b.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;

typedef struct {
    u32 errStatus;       /* 0x00 */
    void *dramAddr;      /* 0x04 */
    void *C2Addr;        /* 0x08 */
    u32 sectorSize;      /* 0x0C */
    u32 C1ErrNum;        /* 0x10 */
    u32 C1ErrSector[4];  /* 0x14 */
} __OSBlockInfo;         /* 0x24 */

typedef struct {
    u32 cmdType;         /* 0x00 */
    u16 transferMode;    /* 0x04 */
    u16 blockNum;        /* 0x06 */
    s32 sectorNum;       /* 0x08 */
    u32 track;           /* 0x0C */
    u32 bmCtlShadow;     /* 0x10 */
    u32 seqCtlShadow;    /* 0x14 */
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

extern OSPiHandle *D_00000000_ldh;  /* __osDiskHandle */
extern u32 D_00000000_gim;          /* __OSGlobalIntMask */
extern void gl_ref_0007FEEC(void);  /* __osLeoResume */
extern void gl_ref_0007FE04(void);  /* __osLeoAbnormalResume */
extern s32 gl_func_00000000_edma(OSPiHandle *, s32, u32, void *, u32); /* osEPiRawStartDma */

#define IO_READ(a) (*(volatile u32 *)(a))
#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))
#define WAIT_ON_IOBUSY(stat) \
    { stat = IO_READ(0xA4600010); while (stat & 3) stat = IO_READ(0xA4600010); }

s32 gl_func_0006B0FC(void)
{
    u32 stat;
    volatile u32 pi_stat;
    u32 bm_stat;
    __OSTranxInfo *info;
    __OSBlockInfo *blockInfo;

    stat = 0;
    info = &D_00000000_ldh->transferInfo;
    blockInfo = &info->block[info->blockNum];
    pi_stat = IO_READ(0xA4600010);
    if (pi_stat & 1) { /* PI_STATUS_DMA_BUSY */
        D_00000000_gim = D_00000000_gim & ~0x800; /* ~SR_IBIT4 */
        blockInfo->errStatus = 29;                /* LEO_ERROR_29 */
        gl_ref_0007FEEC();
        return 1;
    }
    WAIT_ON_IOBUSY(pi_stat);
    stat = IO_READ(0xA5000508); /* LEO_STATUS */
    if (stat & 0x02000000) {    /* MECHANIC_INTERRUPT */
        WAIT_ON_IOBUSY(pi_stat);
        IO_WRITE(0xA5000510, info->bmCtlShadow | 0x01000000); /* CLR_MECHANIC_INTR */
        blockInfo->errStatus = 0;
        return 0;
    }
    if (info->cmdType == 2)
        return 1;
    if (stat & 0x08000000) { /* BUFFER_MANAGER_ERROR */
        WAIT_ON_IOBUSY(pi_stat);
        stat = IO_READ(0xA5000508);
        blockInfo->errStatus = 22; /* LEO_ERROR_22 */
        gl_ref_0007FEEC();
        IO_WRITE(0xA4600010, 2); /* PI_STATUS_CLR_INTR */
        D_00000000_gim |= 0x00100401; /* OS_IM_PI */
        return 1;
    }
    if (info->cmdType == 1) {
        if ((stat & 0x40000000) == 0) { /* !DATA_REQUEST */
            if (info->sectorNum + 1 != info->transferMode * 85) {
                blockInfo->errStatus = 24; /* LEO_ERROR_24 */
                gl_ref_0007FE04();
                return 1;
            }
            IO_WRITE(0xA4600010, 2);
            D_00000000_gim |= 0x00100401;
            blockInfo->errStatus = 0;
            gl_ref_0007FEEC();
            return 1;
        }
        blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr + blockInfo->sectorSize);
        info->sectorNum++;
        gl_func_00000000_edma(D_00000000_ldh, 1, 0x05000400, blockInfo->dramAddr,
                              blockInfo->sectorSize); /* OS_WRITE, LEO_SECTOR_BUFF */
        return 1;
    }
    if (info->cmdType == 0) {
        if (info->transferMode == 3) { /* LEO_SECTOR_MODE */
            if ((s32)blockInfo->C1ErrNum + 17 < info->sectorNum) {
                blockInfo->errStatus = 0;
                gl_ref_0007FE04();
                return 1;
            }
            if ((stat & 0x40000000) == 0) {
                blockInfo->errStatus = 23; /* LEO_ERROR_23 */
                gl_ref_0007FE04();
                return 1;
            }
        } else {
            blockInfo->dramAddr = (void *)((u32)blockInfo->dramAddr + blockInfo->sectorSize);
        }
        bm_stat = IO_READ(0xA5000510); /* LEO_BM_STATUS */
        if ((bm_stat & 0x00200000 && bm_stat & 0x00400000) || bm_stat & 0x02000000) {
            /* (C1SINGLE && C1DOUBLE) || MICRO */
            if (blockInfo->C1ErrNum > 3) {
                if (info->transferMode != 3 || info->sectorNum > 0x52) {
                    blockInfo->errStatus = 23;
                    gl_ref_0007FE04();
                    return 1;
                }
            } else {
                int errNum = blockInfo->C1ErrNum;
                blockInfo->C1ErrSector[errNum] = info->sectorNum + 1;
            }
            blockInfo->C1ErrNum += 1;
        }
        if (stat & 0x10000000) { /* C2_TRANSFER */
            if (info->sectorNum != 87) {
                blockInfo->errStatus = 24;
                gl_ref_0007FE04();
            }
            if (info->transferMode == 2 && info->blockNum == 0) { /* LEO_TRACK_MODE */
                info->blockNum = 1;
                info->sectorNum = -1;
                info->block[1].dramAddr =
                    (void *)((u32)info->block[1].dramAddr - info->block[1].sectorSize);
                blockInfo->errStatus = 22;
            } else {
                IO_WRITE(0xA4600010, 2);
                D_00000000_gim |= 0x00100401;
                info->cmdType = 2;
                blockInfo->errStatus = 0;
            }
            gl_func_00000000_edma(D_00000000_ldh, 0, 0x05000000, blockInfo->C2Addr,
                                  blockInfo->sectorSize * 4); /* OS_READ, LEO_C2_BUFF */
            return 1;
        }
        if (info->sectorNum == -1 && info->transferMode == 2 && info->blockNum == 1) {
            __OSBlockInfo *bptr = &info->block[0];
            if (bptr->C1ErrNum == 0) {
                if (((u32 *)bptr->C2Addr)[0] | ((u32 *)bptr->C2Addr)[1] |
                    ((u32 *)bptr->C2Addr)[2] | ((u32 *)bptr->C2Addr)[3]) {
                    bptr->errStatus = 24;
                    gl_ref_0007FE04();
                    return 1;
                }
            }
            bptr->errStatus = 0;
            gl_ref_0007FEEC();
        }
        info->sectorNum++;
        if (stat & 0x40000000) {
            if (info->sectorNum > 0x54) {
                blockInfo->errStatus = 24;
                gl_ref_0007FE04();
                return 1;
            }
            gl_func_00000000_edma(D_00000000_ldh, 0, 0x05000400, blockInfo->dramAddr,
                                  blockInfo->sectorSize);
            blockInfo->errStatus = 0;
            return 1;
        }
        if (info->sectorNum <= 0x54) {
            blockInfo->errStatus = 24;
            gl_ref_0007FE04();
            return 1;
        }
        return 1;
    }
    blockInfo->errStatus = 4; /* LEO_ERROR_4 */
    gl_ref_0007FE04();
    return 1;
}
