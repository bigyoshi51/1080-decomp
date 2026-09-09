/* game_libs_func_00044B78 -- video-mode selector (bootup.uso export sym1553,
 * jal'd from text 0x4896C / 0x48A10 / 0x58F54).
 *
 * BOUNDARY FIX (2026-09-09, agent-c): ONE function that splat had split into
 * 44B78 (the 3-word "orphan" `lui at; sw a0,0(at); andi t8,a0,0xff` = the
 * hoisted first statement: the D+0x3C8E0 flags-word store and the switch
 * selector) and gl_func_00044B84 (the jumptable dispatcher + arms). Merged
 * .s = 0x124 / 73 words; this C is 73/73 word-exact at IDO 7.1 -O2 except the
 * jumptable `%lo` field, which is why it is WIRED via the REPLACE_FUNC_BODY
 * donor splice into game_libs_post0b.c.o (the 29CCC recipe): the C `switch`
 * puts its 9-entry jumptable in this donor's local .rodata; the splice renames
 * that reloc to game_libs_func_00044B78_rodata, pinned in undefined_syms_auto
 * to the table the USO ships in RoData at +0x1B3C (entries: 44C3C 44BB0 44C00
 * 44BC4 44C50 44BD8 44C50 44C50 44BEC = cases 0..8; the target's
 * `lui at,0; addu at,t8; lw t8,0x1B3C(at); jr t8`).
 *
 * Body: store the mode word to the GBI-emit flags global (sym1924 @0x3C8E0 =
 * the existing D_00000000_3c8e0), dispatch on the low byte to
 * setmode(&modes[k]) where the mode table is Data sym1947 @0x2D700 (zero alias
 * D_44B78_modes; 0x50-byte OSViMode records: 0x0, 0x50, 0xA0, 0x280, 0x320,
 * 0x3C0, 0x960 -> the addends bake into the lui/addiu pairs), case 2 picks
 * &modes[2] for osTvType == 1 (sym1351 = 0x80000300 = D_00000000_tvtype)
 * else &modes[30], and cases 4/6/7 + out-of-range go to the error printer
 * (sym306 = text 0x75AE4 = gl_func_00061478) with the Data string at
 * +0x1FE78 "video mode not supported". Tail: osViSetSpecialFeatures-style
 * callee (sym1989 = text 0x857B0 = gl_func_00071144) with
 * 2 | (mode & 0x200 ? 0x40 : 0), bit 1 cleared when mode & 0x400. All three
 * callees are R_MIPS_26 imports (blank jal = gl_func_00000000).
 *
 * Load-bearing spellings: `switch ((unsigned char)mode)` (the folded cast
 * burns the one ugen ring slot that puts the selector in t8 -- `mode & 0xFF`
 * gives t7 and every later temp one register low); cases in source order
 * 1, 3, 5, 8, 2, 0, default (= the target's arm layout); the mode-table arms
 * as `(char *)&D_44B78_modes + K` call args; `f = 2; if (mode & 0x200) f =
 * 0x42; if (mode & 0x400) f &= ~2;` for the tail. */
#include "common.h"

extern int D_00000000;
extern int gl_func_00000000();
extern s32 D_00000000_3c8e0;     /* GBI-emit flags word (sym1924 @0x3C8E0) */
extern s32 D_00000000_tvtype;    /* osTvType (sym1351 = 0x80000300) */
extern char D_44B78_modes;       /* OSViMode table (sym1947 @0x2D700), zero alias */

#define VIMODE_44B78(k) ((char *)&D_44B78_modes + (k))

void game_libs_func_00044B78(int mode) {
    int f;

    D_00000000_3c8e0 = mode;
    switch ((unsigned char)mode) {
        case 1: gl_func_00000000(VIMODE_44B78(0x280)); break;
        case 3: gl_func_00000000(VIMODE_44B78(0x320)); break;
        case 5: gl_func_00000000(VIMODE_44B78(0x3C0)); break;
        case 8: gl_func_00000000(VIMODE_44B78(0x50)); break;
        case 2:
            if (D_00000000_tvtype == 1) {
                gl_func_00000000(VIMODE_44B78(0xA0));
            } else {
                gl_func_00000000(VIMODE_44B78(0x960));
            }
            break;
        case 0: gl_func_00000000(VIMODE_44B78(0x0)); break;
        default: gl_func_00000000((char *)&D_00000000 + 0x1FE78); break;
    }
    f = 2;
    if (mode & 0x200) {
        f = 0x42;
    }
    if (mode & 0x400) {
        f &= ~2;
    }
    gl_func_00000000(f);
}
