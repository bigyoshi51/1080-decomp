#include "common.h"

/* kernel_022_o1: -O1 carve-out of the kernel_022 functions that are genuinely
 * -O1 (spill-every-local). The file is otherwise -O2 (the bitfield packers
 * func_80008C30/CB4 and the exact-match func_800092B0 REGRESS at -O1). Carved
 * here: func_80009850 (PI raw read, 45->85%) and func_800087B4 (MIPS insn
 * classifier, 44->52%). objdiff is per-function so .ld placement is cosmetic.
 * Verified 2026-06-04 via the mixed-opt diagnostic. */

/* split from kernel_022_o1.c - 2026-06-10 kernel ROM-order relayout */


/* func_80009850 - verified structural decode (kernel, 0x194, 104
 * insns) = libultra __osEPiRawReadIo. Reference: libreultra
 * src/io/epirawread.c / piint.c; same OSPiHandle layout as the
 * documented func_800052F0 (__osEPiRawStartDma).
 *   s32 func_80009850(OSPiHandle *h, u32 cartAddr, u32 *data) {
 *       if (IO_READ(PI_STATUS_REG) & 3)           // 0xA4600010
 *           while (IO_READ(PI_STATUS_REG) & 3) {} // wait idle
 *       cur = __osPiTable[h->domain];             // D_8000A470[]
 *       if (cur != h) {
 *           if (h->domain == 0) {                 // DOM1 regs
 *               if (cur->latency    != h->latency)    PI_BSD_DOM1_LAT = h->latency;   // 0xA4600014
 *               if (cur->pageSize   != h->pageSize)   PI_BSD_DOM1_PGS = h->pageSize;  // 0xA460001C
 *               if (cur->relDuration!= h->relDuration)PI_BSD_DOM1_RLS = h->relDuration;//0xA4600020
 *               if (cur->pulse      != h->pulse)      PI_BSD_DOM1_PWD = h->pulse;     // 0xA4600018
 *           } else {                              // DOM2 regs
 *               ... PI_BSD_DOM2_{LAT 0xA4600024, PGS 0xA460002C,
 *                                RLS 0xA4600030, PWD 0xA4600028} ...
 *           }
 *           __osPiTable[h->domain] = h;
 *       }
 *       *data = *(vu32*)(h->baseAddress | cartAddr | 0xA0000000);
 *       return 0;
 *   }
 * Struct-typing reference: h = OSPiHandle (same as func_800052F0) -
 * h->0x5 latency, 0x6 pageSize, 0x7 relDuration, 0x8 pulse, 0x9
 * domain (u8; 0 = DOM1 else DOM2), 0xC baseAddress. __osPiTable =
 * D_8000A470 (OSPiHandle*[] indexed by domain). PI BSD config
 * registers only rewritten when the cached handle for that domain
 * differs and the individual field changed (lazy reprogram). The
 * final read is an uncached (0xA0000000 / KSEG1) load of
 * baseAddress|cartAddr into *data. PI_STATUS_REG bit 0/1 = DMA/IO
 * busy. (HW addrs per references/indexes/hw_registers.h.) Caps
 * <80: ~11 MMIO reloc (D_A46000xx) + KSEG1 read + DOM1/DOM2 branch
 * + per-field beq compares + busy-wait loop. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
/* 2026-07-10 CRACKED EXACT 101/101 (identity: libultra osEPiRawReadIo,
 * epirawread.c). The "<80 caps" above fall to the baked-constant IO_REG
 * form: constant-pointer MMIO derefs give the fresh-temp store/load bases
 * (extern D_A46000xx scalars emit $at-fused stores = the old floor), with
 * register stat/domain + plain cHandle homed at sp+4 (statement-granular
 * reloads). Host file already -O1: plain body, no donor. Sibling
 * func_80009AB0 (osEPiRawWriteIo, kernel_024) matched the same tick. */
#define IO_REG(a) (*(volatile u32 *)(a))

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

extern OSPiHandle *D_8000A470[]; /* __osCurrentHandle */

s32 func_80009850(OSPiHandle *pihandle, u32 devAddr, u32 *data) {
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

    *data = *(volatile u32 *)(0xA0000000 | (pihandle->baseAddress | devAddr));
    return 0;
}

