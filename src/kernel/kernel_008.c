#include "common.h"

typedef struct {
    u8 pad[0x74];
} OSPiHandle;

extern OSPiHandle CartRomHandle;
extern void* D_8000A46C;
extern u8 D_8001B654;
extern u8 D_8001B655;
extern u8 D_8001B656;
extern u8 D_8001B657;
extern u8 D_8001B658;
extern u8 D_8001B659;
extern volatile u32 D_8001B65C;
extern u32 D_8001B660;
extern s32 func_80002DB0(s32, u32*);
extern void func_800030D0(void*, s32);
extern s32 func_800066B0(void);
extern void func_800066D0(s32);

/* func_800058C0 = libultra osCartRomInit (cartrominit.c).
 * 2026-07-10 CRACKED EXACT 60/60: the documented "one extra lui" cap (the
 * pageSize/relDuration sb pair sharing one $at lui) falls to the TU-DEFINED
 * shared-$at lever — the -O1 donor kernel_008_o1_58C0.c defines a 2-byte
 * struct at D_8001B656 so that pair batches under one lui; all other fields
 * stay extern scalars (statement-granular own-lui stores). CartRomHandle is
 * typed `extern void *` in the donor so the `next = __osPiTable` store emits
 * the direct lui-$at global-store form. Donor bytes replace the body below
 * in the .o via REPLACE_FUNC_BODY (see Makefile); this -O2 host body is the
 * semantic reference.
 * (Historical: 2026-06-10 relayout retracted an earlier FALSE match that
 * emitted 0xE0 vs ROM's 0xF4.) */
OSPiHandle* func_800058C0(void) {
    u32 domain;
    u32 saveMask;

    domain = 0;
    if (D_8001B65C == 0xB0000000) {
        return &CartRomHandle;
    }

    D_8001B654 = 0;
    D_8001B65C = 0xB0000000;
    func_80002DB0(0, &domain);
    D_8001B655 = domain & 0xFF;
    D_8001B658 = (domain >> 8) & 0xFF;
    D_8001B656 = (domain >> 0x10) & 0xF;
    D_8001B657 = (domain >> 0x14) & 0xF;
    D_8001B659 = 0;
    D_8001B660 = 0;
    func_800030D0((u8*)&CartRomHandle + 0x14, 0x60);
    saveMask = func_800066B0();
    *(void**)&CartRomHandle = D_8000A46C;
    D_8000A46C = &CartRomHandle;
    func_800066D0(saveMask);
    return &CartRomHandle;
}
/* (donor bytes replace the body above in the .o; see Makefile) */
