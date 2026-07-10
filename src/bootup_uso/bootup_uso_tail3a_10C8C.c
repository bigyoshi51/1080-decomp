#include "common.h"

/* bootup_uso 0x10C8C..0x116C7 remainder of the former tail3a mid-section,
 * moved out of bootup_uso_tail3a.c on 2026-07-10 when func_00010B6C
 * (0x10B6C, -O0) was carved into bootup_uso_o0_10B6C.c. Same OPT_FLAGS as
 * tail3a (-O2 -g3); both functions here are honest-NM (build path stays
 * INCLUDE_ASM, ROM exact). TRUNCATE_TEXT 0xA3C. */

extern int func_00000000();
extern char D_00000000;
extern char *func_00010324();

/* func_00010C8C: -g3 object constructor (216 insns). Inits arg0's struct
 * fields, builds a temp Vec4-ish stack record (sp6C) passed to a registrar
 * call, allocates two 0x80 sub-objects (->0xC0/->0xC4), then a sub-record
 * (->0x154) whose byte/halfword fields drive 4 callbacks + a global flag.
 *
 * Honestly NM: (1) sp6C.uC loads from the shared FP literal pool (splat
 * misresolved the reloc to .text func_00000C10 @ module-offset 0xC10; see
 * docs/N64_FORENSICS FP-pool fold) and (2) -g3 homed-arg/unfilled-delay
 * codegen. Real C body documents the struct-field semantics; the build
 * path stays INCLUDE_ASM (ROM exact). */
#ifdef NON_MATCHING
extern int *func_000000F0;
extern char D_0000C5D0;
extern char D_0000C5DC;
extern char D_0000C5E4;
extern char D_0000C5F0;
extern float D_FP_POOL_0C10[];

void func_00010C8C(int *arg0, int arg1) {
    struct { int u0; float u4; float u8; float uC; } sp6C;
    int *sp68, *sp84, *p, *c0, *c4, *sub;

    *(int *)((char *)arg0 + 0xC) = (int)&D_0000C5D0;
    *(int *)((char *)arg0 + 0x12C) = arg1;
    sp68 = (int *)func_00000000(0);
    p = (int *)&sp6C;
    if ((p != 0) || (p = (int *)func_00000000(0x10), p != 0)) {
        p[0] = 0;
        *(float *)&p[1] = 0.0f;
        *(float *)&p[2] = 0.0f;
        *(float *)&p[3] = D_FP_POOL_0C10[3];
    }
    func_000000F0 = (int *)func_00000000(0, &D_0000C5DC, 0x10, 0x12C, 0x10, 0x14,
                                         sp6C.u0, sp6C.u4, sp6C.u8, sp6C.uC);
    func_00000000(sp68);
    *(int *)((char *)arg0 + 0x130) = 0;
    *(int *)((char *)arg0 + 0x2C) = 0;
    *(int *)((char *)arg0 + 0x38) = 9;
    *(int *)((char *)arg0 + 0x6C) = -1;
    *(int *)((char *)arg0 + 0x70) = 0;
    *(int *)((char *)arg0 + 0x13C) = 0;
    sp84 = (int *)func_00000000(0);
    func_00000000(0, &D_0000C5E4);
    c0 = (int *)func_00000000(0x80);
    if (c0 != 0) {
        func_00000000(c0, 1);
    }
    *(int *)((char *)arg0 + 0xC0) = (int)c0;
    c4 = (int *)func_00000000(0x80);
    if (c4 != 0) {
        func_00000000(c4, 2);
    }
    *(int *)((char *)arg0 + 0xC4) = (int)c4;
    func_00000000(arg0);
    *(int *)((char *)arg0 + 0x84) = 0;
    *(int *)((char *)arg0 + 0x88) = 1;
    *(int *)((char *)arg0 + 0x18C) = 0;
    *(int *)((char *)arg0 + 0x134) = (int)func_00000000(0);
    *(int *)((char *)arg0 + 0x190) = (int)func_00000000(0, 0);
    *(int *)((char *)arg0 + 0x148) = (int)func_00000000(0);
    sub = (int *)func_00000000(*(int *)((char *)arg0 + 0x148));
    *(int *)((char *)arg0 + 0x154) = (int)sub;
    func_00000000(*(unsigned char *)((char *)sub + 0x12));
    func_00000000(*(unsigned char *)((char *)sub + 0x13));
    func_00000000(*(unsigned char *)((char *)sub + 0x14));
    func_00000000(*(unsigned short *)((char *)sub + 0x4) & 3);
    *(int *)&D_00000000 = (*(unsigned short *)((char *)sub + 0x4) & 4) == 4;
    *(int *)((char *)arg0 + 0x164) = *(int *)*(int *)((char *)arg0 + 0x148);
    *(int *)((char *)arg0 + 0x160) =
        (int)func_00000000(*(int *)((char *)arg0 + 0x164) << 2);
    *(int *)((char *)arg0 + 0x150) = (int)func_00000000(0, &D_0000C5F0);
    func_00000000(sp84);
    func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);
#endif

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
