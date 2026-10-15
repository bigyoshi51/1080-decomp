/* IDO 7.1 -O2 donor for gl_func_00031334 -- stepped sound/cue driver with two
 * jumptable switches (123/123 words standalone; st_size 0x1EC).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post.c.o (the
 * 29CCC / 2E290 / 343F4 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-
 * switch-jumptable-rodata-rename). Both tables land in the donor's local
 * .rodata (switch 1 at +0, 15 entries; switch 2 at +0x3C, 11 entries); the
 * splice renames the reloc to gl_func_00031334_rodata, pinned to 0x1900 in
 * undefined_syms_auto.txt, so the %lo words link to 0x1900 / 0x193C exactly
 * as the USO ships them (tables read from bootup.uso RoData with
 * scripts/extract-uso-jumptable.py --shim 0x1466C; that dump starts one
 * entry late, at +0x1904).
 *
 * Load-bearing shapes:
 *  - switch 1 is on the step word itself with cases -1..13 (IDO's
 *    `addiu t8,t7,1; sltiu at,t8,15`); the empty -1 and 13 labels fix the
 *    range, arms in source order 0, 3, 4, 5, 7, 10-12.
 *  - switch 2 is on the reloaded param a with cases -1..9; it needs enough
 *    empty labels for IDO to pick a table over a beq chain.
 *  - the (0xFF, 0, 0) call's middle 0 is `addiu a1,zero,0` = a 0.0f float
 *    arg to a prototyped (int, float, int) callee (the blank alias
 *    gl_func_00000000_fi); the scanner flagged the missing 3rd arg.
 *  - `if (a != 4 && a != 0)` loads a once (t9); two separate early breaks
 *    reload it.
 *  - jal 0x44F18 is a baked in-unit call (gl_ref_00044F18). */
#include "common.h"

extern int gl_func_00000000();
extern int D_00000000;
extern int D_31334_st, D_31334_x, D_31334_y, D_31334_z;
extern void gl_ref_00044F18();
extern int gl_func_00000000_fi(int, float, int);

void gl_func_00031334(int a, int b, int c) {
    gl_func_00000000(0);
    gl_func_00000000(1);
    *(int *)&D_00000000 = 1;
    gl_func_00000000_fi(0xFF, 0.0f, 0);
    switch (D_31334_st) {
        case -1:
            break;
        case 0:
            if (a != 4 && a != 0) {
                gl_func_00000000(0x83010000, 0x50);
            }
            break;
        case 3:
            gl_func_00000000(0x83010000, 0x50);
            break;
        case 4:
            if (a == 5) {
                if (D_31334_x == 0) {
                    gl_func_00000000(0x83010000, 2000);
                } else if (D_31334_y != 1) {
                    gl_func_00000000(0x83010000, 0x50);
                }
            } else if (a == 6) {
                gl_func_00000000(0x83010000, 2000);
            } else {
                gl_func_00000000(0x83010000, 320);
                gl_ref_00044F18(0);
                gl_func_00000000_fi(0xFF, 0.0f, 0);
            }
            break;
        case 5:
            if (D_31334_z == 13) break;
            if (D_31334_z == 14) break;
            gl_func_00000000();
            break;
        case 7:
            if (a != 7) {
                gl_func_00000000(0x83010000, 0x50);
            }
            break;
        case 10:
        case 11:
        case 12:
            gl_func_00000000(0x83010000, 400);
            break;
        case 13:
            break;
    }
    switch (a) {
        case -1:
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
        case 6:
            *(int *)((char *)&D_00000000 + 0xC) = 256;
            break;
        case 7:
        case 8:
        case 9:
            break;
    }
}
