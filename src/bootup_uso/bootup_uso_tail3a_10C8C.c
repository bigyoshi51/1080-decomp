#include "common.h"

/* bootup_uso 0x10C8C..0x116C7 remainder of the former tail3a mid-section,
 * moved out of bootup_uso_tail3a.c on 2026-07-10 when func_00010B6C
 * (0x10B6C, -O0) was carved into bootup_uso_o0_10B6C.c. Same OPT_FLAGS as
 * tail3a (-O2 -g3); both functions here are honest-NM (build path stays
 * INCLUDE_ASM, ROM exact). TRUNCATE_TEXT 0xA3C. */

extern int func_00000000();
extern int D_00000000;
extern char *func_00010324();

/* func_00010C8C: -O0 object constructor (216 insns). Inits arg0's struct
 * fields, builds a temp Vec4-ish stack record (sp6C) passed by value to a
 * registrar call, allocates two 0x80 sub-objects (->0xC0/->0xC4), then a
 * sub-record (->0x154) whose byte/halfword fields drive 4 callbacks + a
 * global flag. sp6C.w loads from the shared FP literal pool (reloc to
 * .text func_00000C10 @ module-offset 0xC10, +0xC; same recipe as
 * bootup_uso_o0_100F0.c). MATCHED 2026-07-10 (216/216). */
extern int func_000000F0;
extern struct { float f0, f1, f2, f3; } func_00000C10; /* FP literal pool */
extern char D_0000C5D0;
extern char D_0000C5DC;
extern char D_0000C5E4;
extern char D_0000C5F0;

typedef struct {
    float x, y, z, w;
} Vec4_10C8C;

void func_00010C8C(int *arg0, int arg1) {
    int sp84;
    register char *p;   /* s0, home 0x80 */
    register char *q;   /* s1, home 0x7C */
    Vec4_10C8C rec;     /* sp6C */
    int sp68;
    register float x;   /* f20, home 0x64 */
    register float y;   /* f22, home 0x60 */
    register float z;   /* f24, home 0x5C */
    register float w;   /* f26, home 0x58 */

    p = (char *)arg0;
    q = (char *)&D_0000C5D0;
    *(int *)(p + 0xC) = (int)q;
    *(int *)((char *)arg0 + 0x12C) = arg1;
    sp68 = func_00000000(0);
    p = (char *)&rec;
    if (p != 0 || (p = (char *)func_00000000(0x10)) != 0) {
        q = p;
        x = 0;
        y = 0;
        z = 0;
        w = func_00000C10.f3;
        *(float *)q = x;
        *(float *)(q + 4) = y;
        *(float *)(q + 8) = z;
        *(float *)(q + 0xC) = w;
    }
    func_000000F0 = func_00000000(0, &D_0000C5DC, 0x10, 0x12C, 0x10, 0x14, rec);
    func_00000000(sp68);
    *(int *)((char *)arg0 + 0x130) = 0;
    *(int *)((char *)arg0 + 0x2C) = 0;
    *(int *)((char *)arg0 + 0x38) = 9;
    *(int *)((char *)arg0 + 0x6C) = -1;
    *(int *)((char *)arg0 + 0x70) = 0;
    *(int *)((char *)arg0 + 0x13C) = 0;
    sp84 = func_00000000(0);
    func_00000000(&D_00000000, &D_0000C5E4);
    p = 0;
    if (p != 0 || (p = (char *)func_00000000(0x80)) != 0) {
        func_00000000(p, 1);
    }
    *(int *)((char *)arg0 + 0xC0) = (int)p;
    p = 0;
    if (p != 0 || (p = (char *)func_00000000(0x80)) != 0) {
        func_00000000(p, 2);
    }
    *(int *)((char *)arg0 + 0xC4) = (int)p;
    func_00000000(arg0);
    *(int *)((char *)arg0 + 0x84) = 0;
    *(int *)((char *)arg0 + 0x88) = 1;
    *(int *)((char *)arg0 + 0x18C) = 0;
    *(int *)((char *)arg0 + 0x134) = func_00000000(0);
    *(int *)((char *)arg0 + 0x190) = func_00000000(0, 0);
    *(int *)((char *)arg0 + 0x148) = func_00000000(0);
    *(int *)((char *)arg0 + 0x154) = func_00000000(*(int *)((char *)arg0 + 0x148));
    func_00000000(*(unsigned char *)(*(int *)((char *)arg0 + 0x154) + 0x12));
    func_00000000(*(unsigned char *)(*(int *)((char *)arg0 + 0x154) + 0x13));
    func_00000000(*(unsigned char *)(*(int *)((char *)arg0 + 0x154) + 0x14));
    func_00000000(*(unsigned short *)(*(int *)((char *)arg0 + 0x154) + 4) & 3);
    D_00000000 = (*(unsigned short *)(*(int *)((char *)arg0 + 0x154) + 4) & 4) == 4;
    *(int *)((char *)arg0 + 0x164) = **(int **)((char *)arg0 + 0x148);
    *(int *)((char *)arg0 + 0x160) = func_00000000(*(int *)((char *)arg0 + 0x164) << 2);
    *(int *)((char *)arg0 + 0x150) = func_00000000(0, &D_0000C5F0);
    func_00000000(sp84);
    func_00000000(arg0);
}

#ifdef NON_MATCHING
void func_00010FEC(char *arg0, u32 arg1, s32 arg2) {
    char *sp3C;
    char *sp28;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    char *temp_s0_4;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *var_s2;
    char *var_s2_2;
    char *var_s2_3;
    char *var_s2_4;
    char *var_s2_5;
    char *var_s2_6;
    char *var_s2_7;
    char *var_s2_8;

    *(s32 *)((char *)(arg0) + 0x10) = 0;
    temp_s0 = *(s32 *)((char *)(arg0) + 0x134);
    func_00010324((void *)0x10, temp_s0);
    if (*(s32 *)((char *)(temp_s0) + 0x14) != 0) {
        *(s32 *)((char *)(temp_s0) + 0x4) = 1;
    }
    *(s32 *)((char *)(temp_s0) + 0x14) = 0;
    func_00010324((void *)0x10, arg0);
    if (*(s32 *)((char *)(arg0) + 0x14) != 0) {
        *(s32 *)((char *)(arg0) + 0x4) = 1;
    }
    *(s32 *)((char *)(arg0) + 0x14) = 0;
    temp_s0_2 = *(s32 *)((char *)(arg0) + 0x150);
    func_00010324(arg0 + 0x10, temp_s0_2);
    if (*(s32 *)((char *)(temp_s0_2) + 0x14) != 0) {
        *(s32 *)((char *)(temp_s0_2) + 0x4) = 1;
    }
    *(s32 *)((char *)(temp_s0_2) + 0x14) = arg0;
    func_00010324(arg0);
    *(s32 *)((char *)(arg0) + 0x74) = 0;
    *(s32 *)((char *)(arg0) + 0x78) = 0;
    temp_s0_3 = *(s32 *)((char *)&D_00000000 + 0);
    *(s32 *)((char *)&D_00000000 + 0) = (void *) (temp_s0_3 + 1);
    func_00010324(*(s32 *)((char *)&D_00000000 + 0), 0, temp_s0_3, *(s32 *)((char *)&D_00000000 + arg1 * 4));
    sp3C = func_00010324(*(s32 *)((char *)&D_00000000 + 0));
    if (sp3C != (void *)1) {
        func_00010324(0);
    }
    if (arg1 != *(s32 *)((char *)(arg0) + 0x38)) {
        *(s32 *)((char *)(arg0) + 0x34) = arg1;
        func_00010324(arg0);
        func_00010324(arg0, *(s32 *)((char *)&D_00000000 + (*(s32 *)((char *)&D_00000000 + arg1 * 4)) * 4));
        sp28 = func_00010324((void *)3);
        func_00010324(0, (void *)1);
        if (arg1 < 9U) {
            switch (arg1) {
            case 0:
                temp_v0 = func_00010324((void *)8);
                if (temp_v0 != 0) {
                    var_s2 = temp_v0;
                    if ((var_s2 != 0) || (var_s2 = func_00010324((void *)8), (var_s2 != 0))) {
                        *(s32 *)((char *)(var_s2) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0;
                break;
            case 1:
                temp_v0_2 = func_00010324((void *)8);
                if (temp_v0_2 != 0) {
                    var_s2_2 = temp_v0_2;
                    if ((var_s2_2 != 0) || (var_s2_2 = func_00010324((void *)8), (var_s2_2 != 0))) {
                        *(s32 *)((char *)(var_s2_2) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_2) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_2;
                break;
            case 3:
                temp_v0_3 = func_00010324((void *)0xC);
                if (temp_v0_3 != 0) {
                    var_s2_3 = temp_v0_3;
                    if ((var_s2_3 != 0) || (var_s2_3 = func_00010324((void *)8), (var_s2_3 != 0))) {
                        *(s32 *)((char *)(var_s2_3) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_3) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_3;
                break;
            case 2:
                temp_v0_4 = func_00010324((void *)0xC);
                if (temp_v0_4 != 0) {
                    var_s2_4 = temp_v0_4;
                    if ((var_s2_4 != 0) || (var_s2_4 = func_00010324((void *)8), (var_s2_4 != 0))) {
                        *(s32 *)((char *)(var_s2_4) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_4) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_4;
                break;
            case 4:
                temp_v0_5 = func_00010324((void *)8);
                if (temp_v0_5 != 0) {
                    var_s2_5 = temp_v0_5;
                    if ((var_s2_5 != 0) || (var_s2_5 = func_00010324((void *)8), (var_s2_5 != 0))) {
                        *(s32 *)((char *)(var_s2_5) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_5) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_5;
                break;
            case 5:
                temp_v0_6 = func_00010324((void *)0xC);
                if (temp_v0_6 != 0) {
                    var_s2_6 = temp_v0_6;
                    if ((var_s2_6 != 0) || (var_s2_6 = func_00010324((void *)8), (var_s2_6 != 0))) {
                        *(s32 *)((char *)(var_s2_6) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_6) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_6;
                break;
            case 6:
                temp_v0_7 = func_00010324((void *)8);
                if (temp_v0_7 != 0) {
                    var_s2_7 = temp_v0_7;
                    if ((var_s2_7 != 0) || (var_s2_7 = func_00010324((void *)8), (var_s2_7 != 0))) {
                        *(s32 *)((char *)(var_s2_7) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_7) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_7;
                break;
            case 7:
                temp_v0_8 = func_00010324((void *)8);
                if (temp_v0_8 != 0) {
                    var_s2_8 = temp_v0_8;
                    if ((var_s2_8 != 0) || (var_s2_8 = func_00010324((void *)8), (var_s2_8 != 0))) {
                        *(s32 *)((char *)(var_s2_8) + 0x4) = 0;
                    }
                    *(s32 *)((char *)(temp_v0_8) + 0x4) = 0;
                }
                *(s32 *)((char *)(arg0) + 0x30) = temp_v0_8;
                break;
            }
        }
        func_00010324(0, 0);
        func_00010324(sp28);
    }
    temp_s0_4 = *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x30)) + 0x4);
    ((void (*)())*(s32 *)((char *)(temp_s0_4) + 0xC))(*(s32 *)((char *)(temp_s0_4) + 0x8) + *(s32 *)((char *)(arg0) + 0x30), arg2);
    *(s32 *)((char *)(arg0) + 0x38) = arg1;
    func_00010324();
    func_00010324(*(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x134)) + 0x114), *(s32 *)((char *)&D_00000000 + 0));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);
#endif
