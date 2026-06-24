#include "common.h"



/* 2026-06-24 reference-confirmed PRIVILEGED-ASM handwritten (CP0/TLB/FPU: mtc0/mfc0/tlbwi/ctc1/cfc1 — no C form, like libreultra src/os/*.s). INCLUDE_ASM is canonical/permanent; 0.0% fuzzy is CORRECT, not a pending decode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800062D0);

extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern s32 D_8000A490;
extern u32 __osRdb_IP6_Ct;
extern u32 __osRdb_IP6_CurWrite;
extern s32 __osRdb_IP6_Data;
extern u32 __osRdb_IP6_Size;
typedef struct {
    unsigned type : 6;
    unsigned length : 2;
    char buf[3];
} rdbPacket;
/* __osRdbSend(buf, size, type): pack `size` chars (3 per packet) into rdbPackets
 * (header byte = type<<2 | length). With interrupts disabled, optionally emit one
 * packet to the local-write register (0xC0000000) if D_8000A490 is set, then fill
 * the __osRdb_IP6 ring buffer (slot = CurWrite*4 + Data) until the source is
 * drained or the ring is full. Returns the number of chars queued. */
u32 func_800062F0(s32 arg0, u32 arg1, s32 arg2) {
    rdbPacket *sp34;
    rdbPacket sp30;
    u32 sp2C;
    u32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    u32 sp18;

    sp24 = 0;
    sp20 = 0;
    sp18 = 0;
    sp1C = func_800066B0();
    if (D_8000A490 != 0) {
        D_8000A490 = 0;
        sp30.type = arg2;
        if (arg1 < 3U) {
            sp2C = arg1;
        } else {
            sp2C = 3;
        }
        sp28 = 0;
        sp30.length = sp2C;
        if (sp2C != 0) {
            do {
                sp30.buf[sp28] = *((char *) (sp24 + arg0));
                sp28 += 1;
                sp24 += 1;
            } while (sp28 < sp2C);
        }
        arg1 -= sp2C;
        sp18 = sp2C;
        sp20 = 1;
    }
    if ((arg1 != 0) && (__osRdb_IP6_Ct < __osRdb_IP6_Size)) {
        do {
            if (arg1 < 3U) {
                sp2C = arg1;
            } else {
                sp2C = 3;
            }
            sp34 = (rdbPacket *) (__osRdb_IP6_CurWrite * 4 + __osRdb_IP6_Data);
            sp34->type = arg2;
            sp34->length = sp2C;
            sp28 = 0;
            if (sp2C != 0) {
                do {
                    sp34->buf[sp28] = *((char *) (sp24 + arg0));
                    sp28 += 1;
                    sp24 += 1;
                } while (sp28 < sp2C);
            }
            __osRdb_IP6_CurWrite += 1;
            if (__osRdb_IP6_CurWrite >= __osRdb_IP6_Size) {
                __osRdb_IP6_CurWrite = 0;
            }
            __osRdb_IP6_Ct += 1;
            arg1 -= sp2C;
            sp18 += sp2C;
        } while ((arg1 != 0) && (__osRdb_IP6_Ct < __osRdb_IP6_Size));
    }
    if (sp20 != 0) {
        *(s32 *) 0xC0000000 = *(s32 *) &sp30;
    }
    func_800066D0(sp1C);
    return sp18;
}

