#include "common.h"

extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 siacs_bss_0000;
extern void func_800053D0(s32*, s32*, s32);
extern void func_80005DC0(s32*, s32, s32);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005350);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800053D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005400);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800054C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005520);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005534);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80005584);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056C0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800056F0);

/* __osSiCreateAccessQueue */
void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}
