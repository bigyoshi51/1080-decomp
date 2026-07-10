/* -O1 donor for func_80009AB0 = libultra osEPiRawWriteIo (epirawwrite.c;
 * PROVEN EXACT 100/100 standalone 2026-07-10 vs the combined
 * asm/nonmatchings/kernel/func_80009AB0.s + func_80009B60.s splat
 * fragments, IDO 7.1 -O1 -mips2 — the two INCLUDE_ASMs were one function).
 * KEY LEVERS:
 *   - PI registers accessed as BAKED-CONSTANT derefs (IO_REG macro, the
 *     libreultra IO_WRITE/PHYS_TO_K1 form), NOT extern D_A46000xx scalars:
 *     constant-pointer deref materializes the base in a FRESH TEMP per
 *     store (lui t3; sw val,0x14(t3)) where the extern-scalar form emits
 *     the $at-fused store (lui at; sw val,%lo(at)) — 28/100 floor.
 *     Register numbering cascades into place once the form is right.
 *   - register stat/domain + plain cHandle: cHandle homed at 0x4(sp) and
 *     statement-granularly reloaded before each UPDATE_REG compare.
 *   - EPI_SYNC structure straight from libreultra piint.h.
 * Spliced into kernel_024.c.o via REPLACE_FUNC_BODY (real -O1 output;
 * C_FILES filter-out). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next; /* 0x00 */
    u8 type;        /* 0x04 */
    u8 latency;     /* 0x05 */
    u8 pageSize;    /* 0x06 */
    u8 relDuration; /* 0x07 */
    u8 pulse;       /* 0x08 */
    u8 domain;      /* 0x09 */
    u8 pad[2];
    u32 baseAddress; /* 0x0C */
} OSPiHandle;

#define IO_REG(a) (*(volatile u32 *)(a))
extern OSPiHandle *D_8000A470[]; /* __osCurrentHandle */

s32 func_80009AB0(OSPiHandle *pihandle, u32 devAddr, u32 data) {
    register u32 stat;
    register u32 domain;

    stat = IO_REG(0xA4600010);
    while (stat & 3) {
        stat = IO_REG(0xA4600010);
    }

    domain = pihandle->domain;
    if (D_8000A470[domain] != pihandle) {
        OSPiHandle *cHandle = D_8000A470[domain];
        if (domain == 0) {
            if (cHandle->latency != pihandle->latency) {
                IO_REG(0xA4600014) = pihandle->latency;
            }
            if (cHandle->pageSize != pihandle->pageSize) {
                IO_REG(0xA460001C) = pihandle->pageSize;
            }
            if (cHandle->relDuration != pihandle->relDuration) {
                IO_REG(0xA4600020) = pihandle->relDuration;
            }
            if (cHandle->pulse != pihandle->pulse) {
                IO_REG(0xA4600018) = pihandle->pulse;
            }
        } else {
            if (cHandle->latency != pihandle->latency) {
                IO_REG(0xA4600024) = pihandle->latency;
            }
            if (cHandle->pageSize != pihandle->pageSize) {
                IO_REG(0xA460002C) = pihandle->pageSize;
            }
            if (cHandle->relDuration != pihandle->relDuration) {
                IO_REG(0xA4600030) = pihandle->relDuration;
            }
            if (cHandle->pulse != pihandle->pulse) {
                IO_REG(0xA4600028) = pihandle->pulse;
            }
        }
        D_8000A470[domain] = pihandle;
    }

    *(volatile u32 *)(0xA0000000 | (pihandle->baseAddress | devAddr)) = data;
    return 0;
}
