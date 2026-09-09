#include "common.h"

extern void func_800073F8(void*, s32, s32);

typedef struct { s32 pad0; u8 type; char pad5; u16 flags; s32 pad8; s32 id; } RmonHdr16;
typedef struct { s32 pad0; u8 type; char pad5[7]; s32 id; } RmonMsg;

/* __rmonListProcesses */
s32 func_80007EA0(RmonMsg* msg) {
    RmonMsg* p = msg;
    RmonHdr16 hdr;
    hdr.type = p->type;
    hdr.flags = 0;
    hdr.id = p->id;
    func_800073F8(&hdr, 0x10, 1);
    return 0;
}

/* __rmonInit */
extern s32 __rmonMQ;
extern s32 rmonmisc_bss_01C8;
extern s32 rmonmisc_bss_01E8;
extern s32 rmonmisc_bss_0018;
extern s32 rmonmisc_bss_4208;
extern s32 rmonmisc_bss_41E8;
extern s32 D_800055F0;
extern void func_800053D0(void*, void*, s32);
extern void func_800051E0(s32, void*, s32);
extern void func_80005F10(void*, s32, void*, s32, void*, s32);
extern void func_80005920(s32, void*, void*, s32);
extern void func_8000A110(void*);

void func_80007EEC(void) {
    func_800053D0(&__rmonMQ, &rmonmisc_bss_01C8, 8);
    func_800051E0(0xA, &__rmonMQ, 2);
    func_800051E0(0xB, &__rmonMQ, 4);
    func_800051E0(0xC, &__rmonMQ, 8);
    func_800051E0(0xD, &__rmonMQ, 0);
    func_80005F10(&rmonmisc_bss_0018, 0, &D_800055F0, 0,
                  (char*)&rmonmisc_bss_01E8 + 0x4000, 0xFF);
    func_80005920(0x96, &rmonmisc_bss_4208, &rmonmisc_bss_41E8, 8);
    func_8000A110(&rmonmisc_bss_0018);
}

/* Halt stub. Keep this after its real neighbors: its offset is 0x128 in
 * this unit (8 modulo 32). IDO aligns the unreachable return to 32 bytes,
 * placing jr ra at function+0x18, exactly as in the ROM. A standalone unit
 * starts at zero and adds eight extra padding bytes before that return.
 * No instruction patching or artificial prefix is needed. */
void func_80007FC8(void) {
    for (;;) {
    }
}
