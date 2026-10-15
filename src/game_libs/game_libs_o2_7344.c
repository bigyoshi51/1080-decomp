/* IDO 7.1 -O2 donor for gl_func_00007344 -- per-panel HUD-element updater
 * (0x384 bytes, 225 words). PROVEN EXACT 225/225 words standalone; the
 * link-resolved words are the blank jals, the &D_00000000 HI/LO pairs and
 * the jumptable %lo.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs.c.o (the 2E290 /
 * 68990 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-switch-jumptable-
 * rodata-rename): the switch's donor-local .rodata jumptable reloc is renamed
 * gl_func_00007344_rodata, pinned in undefined_syms_auto.txt to the table the
 * USO ships in bootup.uso RoData at +0xDE8 (file offset +0xDEC). Shipped
 * words 0x1B9EC 0x1BCB8 0x1BAD8 0x1BB5C 0x1BC50 0x1B9EC 0x1BBCC; minus the
 * 0x1466C shim:
 *   0/5 -> 0x7380 (mode-dependent 0x140/0x164 pair, +0x618 / +0x600, vcall FC)
 *   1   -> 0x764C (no arm: the post-switch test, same as out-of-range)
 *   2   -> 0x746C (0x410/0x434, +0x648, vcall FC)
 *   3   -> 0x74F0 (0x188/0x1AC, +0x630)
 *   6   -> 0x7560 (0x218/0x23C, +0x678, vcall 104)
 *   4   -> 0x75E4 (0x1D0/0x1F4, +0x660)
 * The old NM wrap (77.5) had case 1/6 on the 0x410 arm and 2/3 shifted; the
 * arms lay out in SOURCE order 0/5, 2, 3, 6, 4.
 *
 * Load-bearing shapes:
 *  - spA/spB are Quad4 STRUCT ASSIGNMENTS (block copy through the addiu'd
 *    &local register, docs/IDO_CODEGEN.md#struct-assign-through-arg-reg-
 *    reassoc-2b94).
 *  - the alpha ramp is written on the FIELD, no local: `if (o->544 < 255)
 *    { o->544 += 2; if (o->544 >= 255) { o->544 = 255; ... } } f(.., o->544,
 *    ..)`. uopt forwards the stored values, giving the target's ugen temp
 *    t2 for the +2 and the `or a1,t2` / `li a1,255; sw a1` copies. Any
 *    local (alpha += 2, alpha = o->544 = alpha + 2, a second temp) colours
 *    v0 or grows the frame by 8. */
#include "common.h"

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
extern int gl_func_00000000();

typedef struct GlHudObj {
    char unk0[0x28];
    struct GlHudVt *unk28;          /* 0x28 vtable/handler */
    char unk2C[0x140 - 0x2C];
    Quad4 unk140;                   /* case 0/5 src A */
    char unk150[0x164 - 0x150];
    Quad4 unk164;                   /* case 0/5 src B */
    char unk174[0x188 - 0x174];
    Quad4 unk188;                   /* case 3 src A */
    char unk198[0x1AC - 0x198];
    Quad4 unk1AC;                   /* case 3 src B */
    char unk1BC[0x1D0 - 0x1BC];
    Quad4 unk1D0;                   /* case 4 src A */
    char unk1E0[0x1F4 - 0x1E0];
    Quad4 unk1F4;                   /* case 4 src B */
    char unk204[0x218 - 0x204];
    Quad4 unk218;                   /* case 6 src A */
    char unk228[0x23C - 0x228];
    Quad4 unk23C;                   /* case 6 src B */
    char unk24C[0x410 - 0x24C];
    Quad4 unk410;                   /* case 2 src A */
    char unk420[0x434 - 0x420];
    Quad4 unk434;                   /* case 2 src B */
    char unk444[0x544 - 0x444];
    int unk544;                     /* alpha ramp counter */
    char unk548[0x554 - 0x548];
    float unk554;                   /* alpha ramp clamp float */
} GlHudObj;

typedef struct GlHudVt {
    char unkF8pad[0xF8];
    short unkF8;                    /* 0xF8 element-offset (short) */
    char unkFApad[0xFC - 0xFA];
    void (*unkFC)(void *);          /* 0xFC handler */
    short unk100;                   /* 0x100 element-offset (short) */
    char unk102pad[0x104 - 0x102];
    void (*unk104)(void *);         /* 0x104 handler */
} GlHudVt;

void gl_func_00007344(GlHudObj *arg0, u32 arg1, void *arg2) {
    void *target;
    Quad4 spA;
    Quad4 spB;
    int mode;

    target = NULL;
    switch (arg1) {
    case 0:
    case 5:
        mode = *(int *)((char *)&D_00000000 + 0x34);
        if (mode == 3 || mode == 2) {
            spA = arg0->unk140;
            target = (char *)arg0 + 0x618;
            spB = arg0->unk164;
        } else {
            spA = arg0->unk140;
            target = (char *)arg0 + 0x600;
            spB = arg0->unk164;
        }
        if (mode != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unkFC(arg0->unk28->unkF8 + (char *)arg0);
        break;
    case 2:
        spA = arg0->unk410;
        target = (char *)arg0 + 0x648;
        spB = arg0->unk434;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unkFC(arg0->unk28->unkF8 + (char *)arg0);
        break;
    case 3:
        spA = arg0->unk188;
        target = (char *)arg0 + 0x630;
        spB = arg0->unk1AC;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        break;
    case 6:
        spA = arg0->unk218;
        target = (char *)arg0 + 0x678;
        spB = arg0->unk23C;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unk104(arg0->unk28->unk100 + (char *)arg0);
        break;
    case 4:
        spA = arg0->unk1D0;
        target = (char *)arg0 + 0x660;
        spB = arg0->unk1F4;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        break;
    }
    if (target != NULL) {
        if (arg0->unk544 < 255) {
            arg0->unk544 += 2;
            if (arg0->unk544 >= 255) {
                arg0->unk544 = 255;
                arg0->unk554 = 175.0f;
            }
        }
        gl_func_00000000(&D_00000000, arg0->unk544, &spA, &spB);
        gl_func_00000000(target);
        gl_func_00000000(target, 0xA0, arg2, 3);
    }
}
