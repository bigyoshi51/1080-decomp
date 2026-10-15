/* IDO 7.1 -O2 donor for gl_func_000025A8 -- mode -> slot-value setter
 * (0x298 bytes, 166 words). PROVEN EXACT 166/166 words standalone; the
 * link-resolved words are the blank jals and the jumptable %lo.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs.c.o (the 7344
 * recipe, docs/MATCHING_WORKFLOW.md#game-libs-rodata-literals-and-tables-76f0):
 * the switch's donor-local .rodata jumptable reloc is renamed
 * gl_func_000025A8_rodata, pinned in undefined_syms_auto.txt to the table the
 * USO ships in bootup.uso RoData at +0xC9C (file offset +0xCA0). Shipped
 * words 0x16C48 0x16CA8 0x16D08 0x16D64 0x16DC4 0x16E1C; minus the 0x1466C
 * shim: cases 2..7 -> 0x25DC 0x263C 0x269C 0x26F8 0x2758 0x27B0, in source
 * order; out-of-range -> 0x2808 (default). Straight first-compile match:
 * IDO picks v0 for the per-arm constant it reuses (or the D4 value in
 * case 3 / default) on its own. */
#include "common.h"

extern int gl_func_00000000();

typedef struct GlEnt25A8 {
    s32 v;
    char pad4[0x18 - 4];
} GlEnt25A8;

typedef struct GlObj25A8 {
    char pad0[0x74];
    GlEnt25A8 e[8];
    char pad134[0x1F0 - 0x134];
    s32 unk1F0;
} GlObj25A8;

void gl_func_000025A8(GlObj25A8 *arg0, s32 arg1) {
    s32 r;

    switch (arg1) {
    case 2:
        arg0->e[0].v = 9;
        arg0->e[1].v = 107;
        arg0->e[2].v = 1;
        arg0->e[3].v = 7;
        arg0->e[4].v = 12;
        arg0->e[5].v = 13;
        arg0->e[6].v = 0;
        arg0->e[7].v = -5;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x5000C);
        break;
    case 3:
        arg0->e[0].v = 9;
        arg0->e[1].v = 110;
        arg0->e[2].v = 1;
        arg0->e[3].v = 4;
        arg0->e[4].v = 14;
        arg0->e[5].v = 15;
        arg0->e[6].v = 0;
        arg0->e[7].v = -7;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x5000D);
        break;
    case 4:
        arg0->e[0].v = 11;
        arg0->e[1].v = 107;
        arg0->e[2].v = 0;
        arg0->e[3].v = 7;
        arg0->e[4].v = 11;
        arg0->e[5].v = 12;
        arg0->e[6].v = 1;
        arg0->e[7].v = -4;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x5000E);
        break;
    case 5:
        arg0->e[0].v = 17;
        arg0->e[1].v = 107;
        arg0->e[2].v = -2;
        arg0->e[3].v = 7;
        arg0->e[4].v = 8;
        arg0->e[5].v = 13;
        arg0->e[6].v = 0;
        arg0->e[7].v = -5;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x5000F);
        break;
    case 6:
        arg0->e[0].v = 14;
        arg0->e[1].v = 108;
        arg0->e[2].v = 0;
        arg0->e[3].v = 6;
        arg0->e[4].v = 9;
        arg0->e[5].v = 14;
        arg0->e[6].v = 0;
        arg0->e[7].v = -6;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x5001F);
        break;
    case 7:
        arg0->e[0].v = 14;
        arg0->e[1].v = 108;
        arg0->e[2].v = 0;
        arg0->e[3].v = 7;
        arg0->e[4].v = 17;
        arg0->e[5].v = 14;
        arg0->e[6].v = 0;
        arg0->e[7].v = -6;
        r = gl_func_00000000(24);
        arg0->unk1F0 = r;
        gl_func_00000000(r, 0x50020);
        break;
    default:
        arg0->e[0].v = 10;
        arg0->e[1].v = 115;
        arg0->e[4].v = 11;
        arg0->e[5].v = 13;
        arg0->unk1F0 = 0;
        break;
    }
}
