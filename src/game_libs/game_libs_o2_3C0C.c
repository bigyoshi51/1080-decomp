/* IDO 7.1 -O2 donor for gl_func_00003C0C -- free-slot allocator (3B1C/3DB8
 * family; 0x1AC bytes, 107 words). PROVEN EXACT 107/107 words standalone;
 * the link-resolved words are the blank jals, the two &D_00000000 HI/LO
 * pairs (+0x138 global, +0xCD04 baked absolute = the `lui 1; addiu -X`
 * carry form) and the .rodata %lo of the 0.1f literal.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs.c.o (the 2B94 /
 * 7344 recipe, docs/MATCHING_WORKFLOW.md#game-libs-rodata-literals-and-
 * tables-76f0): the 0.1f literal lands at this TU's .rodata +0; the splice
 * renames that reloc gl_func_00003C0C_rodata, pinned to bootup.uso RoData
 * +0xCF8 (word 0x3DCCCCCD).
 *
 * Load-bearing shapes:
 *  - every slot access after the first call goes back through p->slot
 *    (the target reloads entry+0x2C before each store).
 *  - `-2.0f - r * 2` (INT 2): a 2.0f literal is strength-reduced to add.s;
 *    the target keeps lui 0x4000 / mul.s.
 *  - the +0x14 counter: ONE pointer expression `q = (s32 *)(chain + 0x14);
 *    *q += arg1;` gives `lw 20(v0); addiu v0,v0,20; sw 0(v0)`. Any
 *    intermediate pointer local for the chain (g = chain; q = g + 0x14), or
 *    `((s32 *)g)[5] += arg1`, folds the offset into the sw.
 *  - the two float calls are prototyped blanks: (obj, f32, f32) with mfc1
 *    a1/a2 and an f32-returning no-arg blank. */
#include "common.h"

extern int D_00000000;
extern int gl_func_00000000();
extern void *gl_func_00000000_i3ff(int, int, int, float, float);
extern void gl_func_00000000_3c0cff(void *, f32, f32);
extern f32 gl_func_00000000_3c0cr();

typedef struct GlSlot3C0C {
    char pad0[0x78];
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    char pad88[0x94 - 0x88];
    s32 unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    f32 unkA4;
    f32 unkA8;
    f32 unkAC;
    s32 unkB0;
    char unkB4[4];
} GlSlot3C0C;

typedef struct GlEnt3C0C {
    char pad0[0x2C];
    GlSlot3C0C *slot;
} GlEnt3C0C;

GlSlot3C0C *gl_func_00003C0C(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
    GlEnt3C0C *p = (GlEnt3C0C *)arg0;
    s32 off = 0;
    GlSlot3C0C *slot;
    s32 *q;

    do {
        slot = p->slot;
        off += 4;
        if (slot->unk94 == 0) {
            gl_func_00000000_i3ff((int)slot, 160, arg2 + 90, 1.0f, 1.0f);
            p->slot->unkA0 = 0;
            p->slot->unk7C = 1;
            q = (s32 *)(*(char **)(*(char **)((char *)&D_00000000 + 0x138) + 0x44) + 0x14);
            *q += arg1;
            if (arg3 != 0) {
                p->slot->unk94 = 3;
                p->slot->unk9C = 14;
                gl_func_00000000_3c0cff(p->slot, 0.1f, 0.1f);
                p->slot->unk78 = 0;
            } else {
                p->slot->unk94 = 3;
                p->slot->unk9C = 0;
                p->slot->unk78 = 255;
            }
            p->slot->unk98 = arg1;
            p->slot->unkA4 = -2.0f - gl_func_00000000_3c0cr() * 2;
            p->slot->unkA8 = -3.0f;
            p->slot->unkAC = 0.5f;
            p->slot->unk80 = 0;
            p->slot->unk84 = -18;
            p->slot->unkB0 = *(s32 *)(arg0 + 0x54);
            slot = p->slot;
            gl_func_00000000(slot->unkB4, (char *)&D_00000000 + 0xCD04, slot->unk98);
            return p->slot;
        }
        p = (GlEnt3C0C *)((char *)p + 4);
    } while (off != 32);
    return 0;
}
