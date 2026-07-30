/* IDO 5.3 -O1 donor for gl_func_0006F8A4 = libultra osEPiRawStartDma
 * (io/epirawdma.c verbatim, 2.0I): EPI_SYNC (WAIT_ON_IOBUSY spin on
 * PI_STATUS_REG, then domain-latch — if __osCurrentHandle[domain] !=
 * pihandle, UPDATE_REG the four BSD DOM1/DOM2 latency/pageSize/
 * relDuration/pulse registers that differ and swap the handle in),
 * then PI_DRAM_ADDR = osVirtualToPhysical(dramAddr), PI_CART_ADDR =
 * K1_TO_PHYS(baseAddress|devAddr), and kick WR_LEN (OS_READ) /
 * RD_LEN (OS_WRITE); unknown direction returns -1. Sibling of the
 * LEO-family donors (6DD14 __osDevMgrMain etc). Blank externs:
 * D_00000000_curhdl = __osCurrentHandle[2] (lui 0/%lo 0 table),
 * gl_func_00000000_vtop = osVirtualToPhysical (blank jal). PI regs are
 * absolute 0xA460xxxx literals (no reloc). Spliced into
 * game_libs_post1b2c.c.o via REPLACE_FUNC_BODY; the trailing pad
 * sidecar gl_func_0006F8A4_pad.s is unaffected (splice is size-exact,
 * 0x224). */
typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;

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
    u8 transferInfo[0x60];      /* 0x14 */
} OSPiHandle;

extern OSPiHandle *D_00000000_curhdl[2];       /* __osCurrentHandle */
extern u32 gl_func_00000000_vtop(void *);      /* osVirtualToPhysical */

#define IO_READ(a) (*(volatile u32 *)(a))
#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))

s32 gl_func_0006F8A4(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size)
{
    u32 stat;
    u32 domain;

    /* WAIT_ON_IOBUSY */
    stat = IO_READ(0xA4600010);
    while (stat & 3)
        stat = IO_READ(0xA4600010);

    domain = pihandle->domain;
    if (D_00000000_curhdl[domain] != pihandle) {
        OSPiHandle *cHandle = D_00000000_curhdl[domain];
        if (domain == 0) {
            if (cHandle->latency != pihandle->latency)
                IO_WRITE(0xA4600014, pihandle->latency);
            if (cHandle->pageSize != pihandle->pageSize)
                IO_WRITE(0xA460001C, pihandle->pageSize);
            if (cHandle->relDuration != pihandle->relDuration)
                IO_WRITE(0xA4600020, pihandle->relDuration);
            if (cHandle->pulse != pihandle->pulse)
                IO_WRITE(0xA4600018, pihandle->pulse);
        } else {
            if (cHandle->latency != pihandle->latency)
                IO_WRITE(0xA4600024, pihandle->latency);
            if (cHandle->pageSize != pihandle->pageSize)
                IO_WRITE(0xA460002C, pihandle->pageSize);
            if (cHandle->relDuration != pihandle->relDuration)
                IO_WRITE(0xA4600030, pihandle->relDuration);
            if (cHandle->pulse != pihandle->pulse)
                IO_WRITE(0xA4600028, pihandle->pulse);
        }
        D_00000000_curhdl[domain] = pihandle;
    }

    IO_WRITE(0xA4600000, gl_func_00000000_vtop(dramAddr));
    IO_WRITE(0xA4600004, (pihandle->baseAddress | devAddr) & 0x1FFFFFFF);
    switch (direction) {
    case 0: /* OS_READ */
        IO_WRITE(0xA460000C, size - 1);
        break;
    case 1: /* OS_WRITE */
        IO_WRITE(0xA4600008, size - 1);
        break;
    default:
        return -1;
    }
    return 0;
}
