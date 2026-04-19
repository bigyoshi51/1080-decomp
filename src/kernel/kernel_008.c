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

/* osCartRomInit */
OSPiHandle* func_800058C0(void) {
    u32 domain;
    s32 saveMask;

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
    func_800030D0((void*)0x8001B664, 0x60);
    saveMask = func_800066B0();
    *(void**)&CartRomHandle = D_8000A46C;
    D_8000A46C = &CartRomHandle;
    func_800066D0(saveMask);
    return &CartRomHandle;
}
