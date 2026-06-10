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

/* osCartRomInit
 * 2026-06-10 kernel-relayout RETRACTION: the previous C was a FALSE match —
 * it emitted 0xE0 bytes vs ROM's 0xF4 (verified pre-relayout against a
 * shifted baseline; episode deleted). The libreultra-shape body below gets
 * 60/61 insns but one extra lui: ROM pairs the pageSize/relDuration
 * computations (srl;srl;andi;andi;sb;sb sharing one $at lui) which -O1
 * won't reproduce from separate statements (one-line/comma/temp forms all
 * tried; -g/-mips1/5.3 matrices too). INCLUDE_ASM is the build path. */
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800058C0);
#endif
