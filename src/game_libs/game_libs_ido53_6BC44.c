#include "common.h"
extern char D_00000000;
extern u8 gl_data_00000000;

/* gl_func_0006BC44 = 1080-customized osContGetReadData (libultra
 * contreaddata.c ancestry; statically-linked libultra, ido53-carve vein).
 * Boundary-fixed 2026-06-09: splat had split the leading MAX_CONTROLLERS
 * load (lui+lbu) into a phantom 8-byte symbol "game_libs_func_0006BC44";
 * the true function spans [0x6BC44..0x6BD14). vs stock libultra: two args
 * (a0 = connected-controller bitmask out, a1 = 4-byte pad records), button
 * stored byte-swapped ((lo<<8)|hi), stick_y dropped, mask |= 1<<i per good
 * controller; all format fields u8 (stick loads are lbu). Bound and PIF
 * buffer are two distinct runtime-patched data placeholders. Byte-exact at
 * IDO 5.3 -O1 (52/52 incl. the pre-prologue lui/lbu pair). */
typedef struct {
    u8 dummy; u8 txsize; u8 rxsize; u8 cmd;
    u8 button_hi; u8 button_lo; u8 stick_x; u8 stick_y;
} GlContReadFormat;

void gl_func_0006BC44(u8 *maskOut, u8 *pads) {
    u8 *ptr;
    GlContReadFormat fmt;
    int i;
    u8 mask;

    mask = 0;
    ptr = (u8 *)&D_00000000;
    for (i = 0; i < gl_data_00000000; i++, ptr += 8, pads += 4) {
        fmt = *(GlContReadFormat *)ptr;
        pads[3] = (fmt.rxsize & 0xC0) >> 4;
        if (pads[3] == 0) {
            *(u16 *)pads = (fmt.button_lo << 8) | fmt.button_hi;
            pads[2] = fmt.stick_x;
            mask |= 1 << i;
        }
    }
    *maskOut = mask;
}

/* gl_func_0006BD14 = 1080-customized __osPackReadData (contreaddata.c
 * sibling of gl_func_0006BC44 above): clears the 15-word PIF command
 * buffer, sets pifstatus = CONT_CMD_EXE, builds the 8-byte read-command
 * record (dummy=0xFF, tx=1, rx=3 -- 4-byte responses -- cmd byte passed as
 * the ARG, 4x 0xFF payload), then stamps it per controller (swl/swr
 * unaligned struct copies) and terminates with 0xFE (CONT_CMD_END).
 * Byte-exact at IDO 5.3 -O1 (61/61). Load-bearing shapes: pifstatus store
 * via a DISTINCT struct-typed placeholder global (direct member access
 * emits the 2-insn lui+sw with the 0x3C offset folded; char*-cast arith
 * emits a 3-insn la+sw, and sharing D_00000000 CSEs the la with ptr);
 * pifstatus store BEFORE ptr init; ptr += 8 at body end (not in the
 * comma-update) so the ptr store fills the loop's bne delay slot. */
typedef struct { int ramarray[15]; int pifstatus; } GlPifRam;
extern GlPifRam D_6BD14_pifram;

void gl_func_0006BD14(u8 cmd) {
    u8 *ptr;
    GlContReadFormat fmt;
    int i;

    for (i = 0; i < 15; i++) {
        *(int *)((char *)&D_00000000 + i * 4) = 0;
    }
    D_6BD14_pifram.pifstatus = 1;
    ptr = (u8 *)&D_00000000;
    fmt.dummy = 0xFF;
    fmt.txsize = 1;
    fmt.rxsize = 3;
    fmt.cmd = cmd;
    fmt.button_hi = 0xFF;
    fmt.button_lo = 0xFF;
    fmt.stick_x = 0xFF;
    fmt.stick_y = 0xFF;
    for (i = 0; i < gl_data_00000000; i++) {
        *(GlContReadFormat *)ptr = fmt;
        ptr += 8;
    }
    *ptr = 0xFE;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BD14_pad.s")
