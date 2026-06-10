#include "common.h"
extern int D_00000000;

/* gl_func_000718C0 = libultra __osIdCheckSum (io/contpfs.c), statically
 * linked into game_libs. Byte-exact ONLY with IDO 5.3 -O1 (per-file
 * CC/OPT_FLAGS override) from the verbatim libreultra source — same story
 * as gl_func_00071864 in the sibling unit. This unit starts 16-aligned
 * (0x718C0) and also carries gl_func_00071928's INCLUDE_ASM so the
 * following unit can start at the 16-aligned 0x71D40. */
s32 gl_func_000718C0(u16 *ptr, u16 *csum, u16 *icsum)
{
    u16 data;
    u32 j;
    data = 0;
    *icsum = 0;
    *csum = *icsum;
    for (j = 0; j < 28; j += 2)
    {
        data = *(u16 *)((u8 *)ptr + j);
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00071928)();
s32 gl_func_00071928(u8 *arg0, char *arg1, u8 *arg2) {
    s16 sp20[4];
    s32 sp74;
    u8 sp54[0x20];
    u8 sp34[0x20];
    u8 sp33;
    s32 sp2C;
    s32 sp28;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t5_2;
    u8 *temp_t0;

    sp74 = 0;
    sp33 = 0;
    if (FW(arg0, 0x65) != 0) {
        FW(arg0, 0x65) = 0U;
        sp74 = game_libs_func_00070FCC(arg0);
        if (sp74 != 0) {
        return sp74;
    }
    }
    FW(arg2, 0x0) = -1;
    FW(arg2, 0x4) = game_libs_func_00070FCC();
    FW(arg2, 0x8) = (s32) FW(arg1, 0x8);
    FW(arg2, 0xC) = (s32) FW(arg1, 0xC);
    FW(arg2, 0x10) = (s32) FW(arg1, 0x10);
    FW(arg2, 0x14) = (s32) FW(arg1, 0x14);
    sp28 = 0;
loop_4:
    FW(arg0, 0x65) = (u8) sp28;
    sp74 = game_libs_func_00070FCC(arg0);
    if (sp74 != 0) {
        return sp74;
    }
    sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), 0, sp54);
    if (sp74 != 0) {
        return sp74;
    }
    sp54[0] = sp28 | 0x80;
    sp2C = 1;
    do {
        temp_t0 = &sp54[sp2C];
        *temp_t0 = ~*temp_t0;
        temp_t5 = sp2C + 1;
        sp2C = temp_t5;
    } while (temp_t5 < 0x20);
    sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), 0, sp54, 0);
    if (sp74 != 0) {
        return sp74;
    }
    sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), 0, sp34);
    if (sp74 != 0) {
        return sp74;
    }
    sp2C = 0;
loop_15:
    if (sp54[sp2C] == sp34[sp2C]) {
        temp_t4 = sp2C + 1;
        sp2C = temp_t4;
        if (temp_t4 < 0x20) {
            goto loop_15;
        }
    }
    if (sp2C == 0x20) {
        if (sp28 > 0) {
            FW(arg0, 0x65) = 0U;
            sp74 = game_libs_func_00070FCC(arg0);
            if (sp74 != 0) {
        return sp74;
    }
            sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), 0, sp54);
            if (sp74 != 0) {
        return sp74;
    }
            if (sp54[0] == 0x80) {
                goto block_24;
            }
            goto block_25;
        }
block_24:
        sp28 += 1;
        if (sp28 >= 0x3E) {
            goto block_25;
        }
        goto loop_4;
    }
block_25:
    FW(arg0, 0x65) = 0U;
    sp74 = game_libs_func_00070FCC(arg0);
    if (sp74 != 0) {
        return sp74;
    }
    if (sp28 > 0) {
        sp33 = 1;
    } else {
        sp33 = 0;
    }
    FW(arg2, 0x18) = (s16) ((FW(arg1, 0x18) & 0xFFFE) | sp33);
    FW(arg2, 0x1A) = (s8) sp28;
    FW(arg2, 0x1B) = (u8) FW(arg1, 0x1B);
    game_libs_func_00070FCC(arg2, (int)arg2 + 0x1C, (int)arg2 + 0x1E);
    sp20[0] = 1;
    sp20[1] = 3;
    sp20[2] = 4;
    sp20[3] = 6;
    sp2C = 0;
loop_31:
    sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), (char *) sp20[sp2C], arg2, 1);
    if (sp74 != 0) {
        return sp74;
    }
    temp_t3 = sp2C + 1;
    sp2C = temp_t3;
    if (temp_t3 >= 4) {
        sp74 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), (char *)1, sp54);
        if (sp74 != 0) {
        return sp74;
    }
        sp2C = 0;
loop_37:
        if (arg2[sp2C] != sp54[sp2C]) {
            return 0xA;
        }
        temp_t5_2 = sp2C + 1;
        sp2C = temp_t5_2;
        if (temp_t5_2 >= 0x20) {
            return 0;
        }
        goto loop_37;
    }
    goto loop_31;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071928);
#endif
