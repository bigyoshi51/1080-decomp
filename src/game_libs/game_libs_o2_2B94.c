/* IDO 7.1 -O2 donor for gl_func_00002B94 -- HUD gauge draw: positions two
 * sprite elements from the bound object's s16 extents, then draws the base
 * quad + up to five overlay sprites (direction arrows, flag icons, colour
 * swatch) at offsets derived from the 1CC..1EC float fields (0x5A4 bytes,
 * 361 words). PROVEN EXACT 361/361 words standalone; the link-resolved
 * words are the blank jals (gl_func_00000000 and the five-arg alias), the
 * blank D_2B94_alpha HI/LO pair, and the four .rodata float-literal %lo
 * words below.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs.c.o (the
 * 6F684 / 68990 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-switch-
 * jumptable-rodata-rename): the four colour literals (200/255, 30/255,
 * 93/255, 162/255) land in this TU's .rodata at +0..+0xC in first-use
 * order; the splice renames that section reloc to gl_func_00002B94_rodata,
 * pinned in undefined_syms_auto.txt to bootup.uso RoData +0xCB8 where the
 * USO ships them (words 0x3F48C8C9 0x3DF0F0F1 0x3EBABABB 0x3F22A2A3).
 *
 * Load-bearing shapes (docs/IDO_CODEGEN.md#struct-assign-through-arg-reg-
 * reassoc-2b94):
 *  - `spA8 = self->e[14].q;` struct assignment = the sw 0/4/8/12(a2) block
 *    copy through the hoisted &spA8 argument register.
 *  - head colouring (self->1F0 in a0, pointer v0, s16 v1): the reloaded
 *    holder temp_a0 must ALSO be the first argument of the 255*alpha call
 *    (`temp_a0 = self->unk1F0; f(temp_a0, ...)` - the struct copy kills the
 *    load so the reload stays, and the shared variable precolours a0); the
 *    pointer/s16 pair must use two otherwise-dead homed decls declared
 *    between sp98 and sp90 (`half`) and between sp8C and sp84 (`sub`). Any
 *    other variable choice gives v1/v0 or t-reg temps.
 *  - sums written last-term-first (`e[2] + e[4] + e[0]`) for IDO's
 *    reassociation; inline FP field reads in the four quotient lines; full
 *    if/else triples for the x/y offsets; every declared scalar takes a
 *    home (pad70[10] + dummies rebuild the 200-byte frame). */
#include "common.h"

typedef struct { int a, b, c, d; } Quad4;

extern int gl_func_00000000();
extern f32 D_2B94_alpha;
extern void gl_func_00000000_2B94f(void *, s32, f32, f32, s32);

typedef struct GlE18 {
    Quad4 q;
    s32 pad10[2];
} GlE18;

typedef struct GlObj2B94 {
    char pad0[0x44];
    GlE18 e[15];                    /* 0x44 */
    char pad1AC[0x1C0 - 0x1AC];
    s32 unk1C0;
    s32 unk1C4;
    s32 unk1C8;
    f32 unk1CC;
    f32 unk1D0;
    f32 unk1D4;
    f32 unk1D8;
    f32 unk1DC;
    f32 unk1E0;
    f32 unk1E4;
    f32 unk1E8;
    f32 unk1EC;
    char *unk1F0;
} GlObj2B94;

void gl_func_00002B94(GlObj2B94 *self) {
    f32 spB8[4];
    Quad4 spA8;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 half;
    s32 sp90;
    s32 sp8C;
    char *sub;
    s32 sp84;
    f32 sp74[4];
    s32 pad70[10];
    s32 var_a0;
    s32 var_v0_3;
    char *temp_a0;
    char *temp_a1;
    char *var_s1;

    temp_a1 = self->unk1F0;
    if (temp_a1 != 0) {
        gl_func_00000000(temp_a1);
        temp_a0 = self->unk1F0;
        sub = *(char **)(temp_a0 + 0x10);
        half = *(s16 *)(sub + 0x20);
        self->e[0].q.a = self->unk1C4 - half;
        sub = *(char **)(temp_a0 + 0x10);
        half = *(s16 *)(sub + 0x22);
        self->e[1].q.a = self->unk1C8 - half;
        spB8[3] = 1.0f;
        spB8[2] = 1.0f;
        spB8[1] = 1.0f;
        spB8[0] = 1.0f;
        spA8 = self->e[14].q;
        temp_a0 = self->unk1F0;
        gl_func_00000000(temp_a0, (s32) (255.0f * D_2B94_alpha), &spA8, 0xFF);
        gl_func_00000000(self->unk1F0, self->e[0].q.a, self->e[1].q.a, 0);
        var_s1 = (char *)self + 0x224;
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * D_2B94_alpha), spB8, 0xFF);
        gl_func_00000000(var_s1, self->e[2].q.a + self->e[4].q.a + self->e[0].q.a, self->e[3].q.a + self->e[5].q.a + self->e[1].q.a, 3);
        var_s1 = (char *)self + 0x23C;
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * D_2B94_alpha), spB8, 0xFF);
        gl_func_00000000(var_s1, self->e[6].q.a + self->e[8].q.a + self->e[0].q.a, self->e[7].q.a + self->e[9].q.a + self->e[1].q.a, 3);
        spA4 = (s32) (((f32) self->e[7].q.a - (f32) self->e[3].q.a) * ((self->unk1D4 - self->unk1E4) / self->unk1EC));
        spA0 = (s32) (((f32) self->e[7].q.a - (f32) self->e[3].q.a) * ((self->unk1D8 - self->unk1E8) / self->unk1EC));
        sp9C = (s32) (((f32) self->e[7].q.a - (f32) self->e[3].q.a) * ((self->unk1DC - self->unk1E4) / self->unk1EC));
        sp98 = (s32) (((f32) self->e[7].q.a - (f32) self->e[3].q.a) * ((self->unk1E0 - self->unk1E8) / self->unk1EC));
        if (self->unk1D0 < self->unk1CC) {
            var_s1 = (char *)self + 0x26C;
            sp90 = -0x13;
            sp8C = -0x10;
        } else {
            var_s1 = (char *)self + 0x254;
            sp90 = -0x13;
            sp8C = 2;
        }
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * D_2B94_alpha), spB8, 0xFF);
        gl_func_00000000(var_s1, self->e[2].q.a + self->e[0].q.a + spA4 + sp90, self->e[3].q.a + self->e[1].q.a + spA0 + sp8C, 0);
        var_a0 = 0;
        if (self->unk1C0 & 2) {
            var_a0 = 1;
            if (self->unk1CC <= self->unk1D0) {
                var_s1 = (char *)self + 0x29C;
                sp90 = -3;
                sp8C = -0xE;
            } else {
                var_s1 = (char *)self + 0x284;
                sp90 = -3;
                sp8C = 0;
            }
        } else if (self->unk1C0 & 4) {
            var_a0 = 1;
            if (self->unk1CC <= self->unk1D0) {
                var_s1 = (char *)self + 0x2CC;
                sp90 = -3;
                sp8C = -0xE;
            } else {
                var_s1 = (char *)self + 0x2B4;
                sp90 = -3;
                sp8C = 0;
            }
        }
        if (var_a0 != 0) {
            gl_func_00000000(var_s1);
            gl_func_00000000(var_s1, (s32) (255.0f * D_2B94_alpha), spB8, 0xFF);
            gl_func_00000000(var_s1, self->e[2].q.a + self->e[0].q.a + sp9C + sp90, self->e[3].q.a + self->e[1].q.a + sp98 + sp8C, 0);
        }
        var_v0_3 = self->unk1C0 & 8;
        if (var_v0_3 != 0) {
            if (self->unk1D0 < self->unk1CC) {
                var_s1 = (char *)self + 0x1F4;
                sp74[0] = 1.0f;
                sp74[1] = 0.78431374f;
                sp74[2] = 0.11764706f;
                sp74[3] = 0.0f;
            } else {
                sp74[0] = 0.36470589f;
                sp74[1] = 0.63529414f;
                sp74[2] = 1.0f;
                sp74[3] = 0.0f;
                var_s1 = (char *)self + 0x20C;
            }
            gl_func_00000000(var_s1);
            self->e[10].q.a = (s32) (self->e[6].q.a + self->e[0].q.a);
            self->e[11].q.a = (s32) ((self->e[7].q.a + self->e[1].q.a) - 0x18);
            gl_func_00000000(var_s1, (s32) (255.0f * D_2B94_alpha), sp74, 0xFF);
            gl_func_00000000(var_s1, self->e[10].q.a, self->e[11].q.a, 3);
            var_v0_3 = self->unk1C0 & 8;
        }
        if (var_v0_3 != 0) {
            gl_func_00000000_2B94f(self, 0, self->unk1DC, self->unk1E0, self->e[13].q.a);
        }
        if (self->unk1C0 & 0x20) {
            gl_func_00000000_2B94f(self, 0, self->unk1DC, self->unk1E0, self->e[13].q.a - 0x6E);
            gl_func_00000000_2B94f(self, 1, self->unk1D4, self->unk1D8, self->e[13].q.a);
        }
    }
}
