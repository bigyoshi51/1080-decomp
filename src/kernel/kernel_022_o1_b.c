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
#ifdef NON_MATCHING
extern u32 D_A4600010;
extern s32 D_A4600014, D_A4600018, D_A460001C, D_A4600020;
extern s32 D_A4600024, D_A4600028, D_A460002C, D_A4600030;
extern s32 D_A0000000;
extern void *D_8000A470;
/* PI raw cartridge read with BSD domain register setup. Wait for PI not-busy
 * (PI_STATUS D_A4600010 & 3), then if this handle isn't the cached one for its
 * domain (arg0->unk9, the D_8000A470[domain] slot), reprogram the domain's BSD
 * timing registers that changed (latency unk5, pagesize unk6, release unk7,
 * pulse unk8 -> dom0 D_A4600014/1C/20/18 or dom1 D_A4600024/2C/30/28) and cache
 * the handle. Finally read the cartridge word at (&D_A0000000 + base|offset).
 * Externalized MMIO symbols (vs raw 0xA46000xx) give the HI16/LO16 reloc form
 * the target uses; residual = -O1 register-coloring of domain/status only. */
s32 func_80009850(void *arg0, s32 arg1, s32 *arg2) {
    s32 domain;
    void *sp4;

    if (D_A4600010 & 3) {
        do {
        } while (D_A4600010 & 3);
    }
    domain = *(u8 *)((char *) arg0 + 9);
    if (((void **) &D_8000A470)[domain] != arg0) {
        sp4 = ((void **) &D_8000A470)[domain];
        if (domain == 0) {
            if (*(u8 *)((char *) sp4 + 5) != *(u8 *)((char *) arg0 + 5)) {
                D_A4600014 = *(u8 *)((char *) arg0 + 5);
            }
            if (*(u8 *)((char *) sp4 + 6) != *(u8 *)((char *) arg0 + 6)) {
                D_A460001C = *(u8 *)((char *) arg0 + 6);
            }
            if (*(u8 *)((char *) sp4 + 7) != *(u8 *)((char *) arg0 + 7)) {
                D_A4600020 = *(u8 *)((char *) arg0 + 7);
            }
            if (*(u8 *)((char *) sp4 + 8) != *(u8 *)((char *) arg0 + 8)) {
                D_A4600018 = *(u8 *)((char *) arg0 + 8);
            }
        } else {
            if (*(u8 *)((char *) sp4 + 5) != *(u8 *)((char *) arg0 + 5)) {
                D_A4600024 = *(u8 *)((char *) arg0 + 5);
            }
            if (*(u8 *)((char *) sp4 + 6) != *(u8 *)((char *) arg0 + 6)) {
                D_A460002C = *(u8 *)((char *) arg0 + 6);
            }
            if (*(u8 *)((char *) sp4 + 7) != *(u8 *)((char *) arg0 + 7)) {
                D_A4600030 = *(u8 *)((char *) arg0 + 7);
            }
            if (*(u8 *)((char *) sp4 + 8) != *(u8 *)((char *) arg0 + 8)) {
                D_A4600028 = *(u8 *)((char *) arg0 + 8);
            }
        }
        ((void **) &D_8000A470)[domain] = arg0;
    }
    *arg2 = *(s32 *)((char *) &D_A0000000 + (*(s32 *)((char *) arg0 + 0xC) | arg1));
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);
#endif
