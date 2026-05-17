#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];


/* __osSiDeviceBusy */
s32 func_800052C0(void) {
    register u32 status = *(volatile u32*)0xA4800018;
    if (status & 3) {
        return 1;
    }
    return 0;
}


#ifdef NON_MATCHING
typedef struct {
    u32 unk_00;
    u8 type;
    u8 latency;
    u8 pageSize;
    u8 relDuration;
    u8 pulse;
    u8 domain;
    u8 pad_0A[2];
    u32 baseAddress;
} OSPiHandle;

extern OSPiHandle *D_8000A470[];
extern s32 func_80004B30(void *);

#define PI_REG(offset) (*(volatile u32 *)(0xA4600000 + (offset)))

/* func_800052F0: __osEPiRawStartDma - extended PI DMA setup with handle.
 * 24-insn entry block (0x60). Falls through into func_80005350 (116 insns
 * / 0x1D0) which contains the body + epilogue. Combined function is the
 * full __osEPiRawStartDma per OoT reference (libultra/io/epirawdma.c).
 *
 * Decoded structure (covers BOTH halves):
 *
 *   s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, u32 cartAddr,
 *                          void* dramAddr, s32 size) {
 *       u32 status;
 *       OSPiHandle* curHandle;
 *       status = IO_READ(PI_STATUS_REG);                    // 0xA4600010
 *       while (status & 3) { status = IO_READ(PI_STATUS_REG); }
 *
 *       curHandle = __osPiTable[handle->domain];            // table at 0x8000A470
 *       if (curHandle != handle) {
 *           // Per-domain BSD register updates (DOM1: 0x14/1C/20/18, DOM2: 0x24/2C/30/28)
 *           if (curHandle->latency    != handle->latency)    IO_WRITE(LAT_REG, ...);
 *           if (curHandle->pageSize   != handle->pageSize)   IO_WRITE(PGS_REG, ...);
 *           if (curHandle->relDuration!= handle->relDuration)IO_WRITE(RLS_REG, ...);
 *           if (curHandle->pulse      != handle->pulse)      IO_WRITE(PWD_REG, ...);
 *           __osPiTable[handle->domain] = handle;
 *       }
 *       IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));  // func_80004B30
 *       IO_WRITE(PI_CART_ADDR_REG, (handle->baseAddress | cartAddr) & 0x1FFFFFFF);
 *       if      (direction == 0) IO_WRITE(PI_WR_LEN_REG, size - 1);  // OS_READ
 *       else if (direction == 1) IO_WRITE(PI_RD_LEN_REG, size - 1);  // OS_WRITE
 *       else                     return -1;
 *       return 0;
 *   }
 *
 * Field offsets used: handle->{0x04 type, 0x05 latency, 0x06 pageSize,
 * 0x07 relDuration, 0x08 pulse, 0x09 domain, 0x0C baseAddress}.
 * Same OSPiHandle layout as OoT/libreultra (PI_BASE = 0xA4600000).
 *
 * MATCH BLOCKED: same alt-entry shared-tail pattern as func_800073DC /
 * func_8000817C / func_80008430. External callers in kernel_000.c /
 * kernel_001.c / kernel_003.c declare `extern void func_80005350(s32, s32)`
 * and call it as a 2-arg function — those callers expect to enter mid-body
 * (uses prologue's $sp frame + spilled $a0/$a3 args). Standard C-emit can't
 * produce a function whose internal label is also a callable entry — IDO
 * always emits prologue+epilogue at function boundary. See
 * docs/MATCHING_WORKFLOW.md#feedback-cross-function-epilogue-entry.
 *
 * Default INCLUDE_ASM build remains exact. */
s32 func_800052F0(OSPiHandle *handle, s32 direction, u32 cartAddr, void *dramAddr, s32 size) {
    u32 status;
    u32 domain;
    OSPiHandle *curHandle;

    status = PI_REG(0x10);
    while (status & 3) {
        status = PI_REG(0x10);
    }

    domain = handle->domain;
    curHandle = D_8000A470[domain];
    if (curHandle != handle) {
        if (domain == 0) {
            if (curHandle->latency != handle->latency) {
                PI_REG(0x14) = handle->latency;
            }
            if (curHandle->pageSize != handle->pageSize) {
                PI_REG(0x1C) = handle->pageSize;
            }
            if (curHandle->relDuration != handle->relDuration) {
                PI_REG(0x20) = handle->relDuration;
            }
            if (curHandle->pulse != handle->pulse) {
                PI_REG(0x18) = handle->pulse;
            }
        } else {
            if (curHandle->latency != handle->latency) {
                PI_REG(0x24) = handle->latency;
            }
            if (curHandle->pageSize != handle->pageSize) {
                PI_REG(0x2C) = handle->pageSize;
            }
            if (curHandle->relDuration != handle->relDuration) {
                PI_REG(0x30) = handle->relDuration;
            }
            if (curHandle->pulse != handle->pulse) {
                PI_REG(0x28) = handle->pulse;
            }
        }
        D_8000A470[domain] = handle;
    }

    PI_REG(0x00) = func_80004B30(dramAddr);
    PI_REG(0x04) = (handle->baseAddress | cartAddr) & 0x1FFFFFFF;

    if (direction == 0) {
        PI_REG(0x0C) = size - 1;
    } else if (direction == 1) {
        PI_REG(0x08) = size - 1;
    } else {
        return -1;
    }

    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800052F0);
#endif

#undef PI_REG
