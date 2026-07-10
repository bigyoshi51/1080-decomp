#include "common.h"

/* bootup_uso 0x10C8C..0x116C7 remainder of the former tail3a mid-section,
 * moved out of bootup_uso_tail3a.c on 2026-07-10 when func_00010B6C
 * (0x10B6C, -O0) was carved into bootup_uso_o0_10B6C.c. Same OPT_FLAGS as
 * tail3a was -O2 -g3 but both residents are -O0 (flipped 2026-07-10):
 * func_00010C8C is MATCHED (real C in build path); func_00010FEC is an
 * honest 94.5% NM wrap (INCLUDE_ASM in build path). TRUNCATE_TEXT 0xA3C. */

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

/* func_00010FEC: mode-switch dispatcher (439 insns), -O0. Tears down /
 * re-registers three sub-objects (0x134 / self / 0x150) against the module
 * event list, bumps the global sequence counter, then switch(arg1) builds
 * the mode object (->0x30): per case, alloc(8|0xC) + alloc(8) vtable pair.
 * Case source order 0,1,3,2,4,5,6,7,8 recovered from the RoData jumptable
 * at module 0xC20 (scripts/extract-uso-jumptable.py; targets bias +8 =
 * Text leading marker word). The C switch emits a local .rodata jumptable:
 * tenshoe.ld pins this unit's .rodata at VMA 0xC20 via a NOLOAD section so
 * the lui/lw dispatch fields bake %hi/%lo(0xC20) while the table bytes
 * (present in the baked USO RoData asset) stay out of the ROM image.
 *
 * Honest NM at 415/439 (94.5%, masked-reloc byte compare vs target).
 * SOLE root diff (4 words @ +0x17C): the `arg1 != arg0->0x38` guard.
 * Target evaluates arg1 FIRST (lw t0,0x44(sp); lw t1,0x40; lw t2,0x38(t1);
 * beq t0,t2). Our IDO 7.1 (and 5.3) -O0 ALWAYS evaluates the memory-deref
 * side of a scalar==/!= first (cfe canonicalizes; ~25 spellings probed:
 * operand swap, u32/int/ptr/float types, casts, volatile, *(&arg1),
 * struct/union param, goto/else/while/for/do forms, &&/|| context, comma/
 * assignment hoists, -cckr/-ansi/-mips1/3/-KPIC/-G8/-g0..3, 5.3+7.1 —
 * ALL deref-first). The remaining 20 diff words are pure t-reg FIFO
 * recycle-order knock-ons of that one block (t0/t1 swaps in the case
 * bodies). Same value-first shape blocks func_00010540 (its while-head) —
 * the only two value-first compare sites in all USO -O0 asm. See
 * docs/IDO_CODEGEN.md "-O0 scalar-vs-deref equality eval order". */
#ifdef NON_MATCHING
typedef int (*FN10FEC)();

extern char D_0000C550;
extern char D_0000C604;
extern char D_0000C60C;
extern int D_0000C4EC[];

void func_00010FEC(char *arg0, int arg1, int arg2) {
    int sp3C;
    register char *p;   /* s0 */
    register char *q;   /* s1 */
    register char *r;   /* s2 */
    register char *s;   /* s3 */
    int sp28;

    q = arg0;
    p = q + 0x10;
    *(int *)p = 0;

    p = *(char **)((char *)arg0 + 0x134);
    q = (char *)&D_00000000;
    r = q + 0x10;
    func_00000000(r, p);
    if (*(int *)(p + 0x14) != 0) {
        *(int *)(p + 4) = 1;
    }
    r = q;
    *(int *)(p + 0x14) = (int)r;

    p = arg0;
    q = (char *)&D_00000000;
    r = q + 0x10;
    func_00000000(r, p);
    if (*(int *)(p + 0x14) != 0) {
        *(int *)(p + 4) = 1;
    }
    s = q;
    *(int *)(p + 0x14) = (int)s;

    p = *(char **)((char *)arg0 + 0x150);
    q = arg0;
    r = q + 0x10;
    func_00000000(r, p);
    if (*(int *)(p + 0x14) != 0) {
        *(int *)(p + 4) = 1;
    }
    s = q;
    *(int *)(p + 0x14) = (int)s;

    func_00000000(arg0);
    *(int *)((char *)arg0 + 0x74) = 0;
    *(int *)((char *)arg0 + 0x78) = 0;

    p = (char *)D_00000000;
    D_00000000 = (int)p + 1;
    func_00000000(func_000000F0, &D_0000C604, p, (&D_00000000)[arg1]);
    sp3C = func_00000000(func_000000F0);
    if (sp3C != 1) {
        func_00000000(&D_0000C60C);
    }

    if (arg1 != *(int *)((char *)arg0 + 0x38)) {
        *(int *)((char *)arg0 + 0x34) = arg1;
        func_00000000(arg0);
        func_00000000(arg0, D_0000C4EC[(&D_00000000)[arg1]]);
        sp28 = func_00000000(3);
        func_00000000(&D_00000000, 1);
        switch (arg1) {
        case 0:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 1:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 3:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(0xC)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 2:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(0xC)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 4:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 5:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(0xC)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 6:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 7:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        case 8:
            q = 0;
            if (q != 0 || (q = (char *)func_00000000(8)) != 0) {
                r = q;
                if (r != 0 || (r = (char *)func_00000000(8)) != 0) {
                    *(int *)(r + 4) = (int)&D_0000C550;
                }
                *(int *)(q + 4) = (int)&D_00000000;
            }
            p = q;
            *(int *)((char *)arg0 + 0x30) = (int)p;
            break;
        }
        func_00000000(&D_00000000, 0);
        func_00000000(sp28);
    }

    (*(FN10FEC)*(int *)(p + 0xC))(
        *(int *)((char *)arg0 + 0x30) +
            *(short *)((p = *(char **)(*(int *)((char *)arg0 + 0x30) + 4)) + 8),
        arg2);
    *(int *)((char *)arg0 + 0x38) = arg1;
    func_00000000();
    p = (char *)D_00000000;
    func_00000000(*(int *)(*(int *)((char *)arg0 + 0x134) + 0x114), p);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);
#endif
