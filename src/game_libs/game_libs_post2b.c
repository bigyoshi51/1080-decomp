#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;
#ifdef NON_MATCHING
#define GL_COUNT_2070 (*(int*)((char*)&D_00000000 + 0x2070))
#endif





#ifdef NON_MATCHING
/* gl_func_000725C4 - STRUCTURAL PASS (big-swing 2026-06-02).
 * Multi-pass formatted-string layout/render driver, 0x6C4 (433 insns).
 * Sole callee gl_func_0001CA10 (the family's measure/emit/lookup helper;
 * each call returns an error code that is propagated immediately). No
 * folded-pool refs. Three passes over the FI(arg0, 0x50) glyph slots:
 *   pass 1 (loop_7): per slot decode a glyph (gl_func_0001CA10 -> &meas),
 *     run the line-fit inner loop (loop_15) advancing through the wrap
 *     candidates in sp27C[], track break opportunity, flush on overflow;
 *   pass 2 (loop_42): record the chosen break column into sp23C[slot];
 *   pass 3 (loop_51 over FI(arg0, 0x64) rows): build the per-row glyph table
 *     sp37C[] from sp27C[]/sp23C[] and emit it via gl_func_0001CA10.
 * Finally set/clear FI(arg0, 0x0) bit 1 from the overflow flag sp34.
 *
 * Locals: sp38/sp27C/sp37C/sp23C are u16[] working buffers; the (sp25C,
 * sp260..sp266) group is one measure-result struct (passed by &). m2c
 * artifacts resolved: unksp47D == (u8)sp47C (LSB of the u16 char), and the
 * inner-measure 2nd arg is the current char sp47C.
 *
 * NOT matched (working-buffer register allocation + the family helper's
 * untyped signature); default INCLUDE_ASM path byte-exact. Structure
 * documented for the next pass. */
#define FI(p, o) (*(int *)((char *)(p) + (o)))

extern int gl_func_0001CA10();

s32 gl_func_000725C4(void *arg0) {
    struct { s32 status; u16 code; u16 col; s8 b264; s16 h266; } meas;
    u16 sp38[0x80];
    u16 sp27C[0x80];
    u16 sp37C[0x80];
    u16 sp23C[0x80];
    u16 sp47C;
    s32 err;
    s32 slot;
    s32 brk;
    s32 prevw;
    s32 overflow;
    u8 row;
    s32 i;
    s32 n;

    err = gl_func_0001CA10(arg0);
    if (err == 2) {
        err = gl_func_0001CA10(arg0);
    }
    if (err != 0) {
        return err;
    }
    err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp38[0]);
    if (err != 0) {
        return err;
    }

    overflow = 0;
    slot = 0;
    if (FI(arg0, 0x50) > 0) {
    loop_7:
        err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas);
        if (err != 0) {
            return err;
        }
        if ((meas.code != 0) && (meas.status != 0)) {
            sp47C = meas.col;
            brk = 0;
            prevw = 0;
            if (((s32) sp47C >= FI(arg0, 0x60)) && ((s32) (u8) sp47C < (s32) FI(arg0, 0x64)) &&
                ((s32) (u8) sp47C > 0) && ((s32) (u8) sp47C < 0x80)) {
            loop_15:
                /* advance through wrap candidates accumulating width */
                err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp27C[0], NULL, (s32 *) (u8) sp47C);
                if ((err != 0) && (err != 3)) {
                    return err;
                }
                brk = gl_func_0001CA10(arg0, sp47C, (u16 (*)[]) &sp38[0]) - prevw;
                if (brk != 0) {
                    prevw = 1;
                    sp47C = sp27C[(u8) sp47C];
                    if (((s32) sp47C >= FI(arg0, 0x60)) && ((s32) (u8) sp47C < (s32) FI(arg0, 0x64)) &&
                        ((s32) (u8) sp47C > 0) && ((s32) (u8) sp47C < 0x80)) {
                        goto loop_15;
                    }
                }
            }
            if ((brk != 0) || (sp47C != 1)) {
                meas.code = 0;
                meas.status = 0;
                meas.col = 0;
                meas.b264 = 0;
                meas.h266 = 0;
                if (FI(arg0, 0x65) != 0) {
                    FI(arg0, 0x65) = 0;
                    err = gl_func_0001CA10(arg0);
                    if (err != 0) {
                        return err;
                    }
                }
                err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas, 0);
                if (err != 0) {
                    return err;
                }
                overflow += 1;
            }
        } else if ((meas.code != 0) || (meas.status != 0)) {
            meas.code = 0;
            meas.status = 0;
            meas.col = 0;
            meas.b264 = 0;
            meas.h266 = 0;
            if (FI(arg0, 0x65) != 0) {
                FI(arg0, 0x65) = 0;
                err = gl_func_0001CA10(arg0);
                if (err != 0) {
                    return err;
                }
            }
            err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas, 0);
            if (err != 0) {
                return err;
            }
            overflow += 1;
        }
        slot += 1;
        if (slot < FI(arg0, 0x50)) {
            goto loop_7;
        }
    }

    slot = 0;
    if (FI(arg0, 0x50) > 0) {
    loop_42:
        err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas);
        if (err != 0) {
            return err;
        }
        if ((meas.code != 0) && (meas.status != 0) && ((s32) meas.col >= (s32) FI(arg0, 0x62))) {
            sp23C[slot] = meas.col;
        } else {
            sp23C[slot] = 0;
        }
        slot += 1;
        if (slot < FI(arg0, 0x50)) {
            goto loop_42;
        }
    }

    row = 0;
    if ((s32) FI(arg0, 0x64) > 0) {
    loop_51:
        err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp27C[0], NULL, (s32 *) row);
        if ((err != 0) && (err != 3)) {
            return err;
        }
        if ((s32) row > 0) {
            n = 1;
        } else {
            n = FI(arg0, 0x60);
        }
        for (i = 0; i < n; i++) {
            sp37C[i] = sp27C[i];
        }
        for (; i < 0x80; i++) {
            sp37C[i] = 3;
        }
        for (i = 0; i < FI(arg0, 0x50); i++) {
            while ((sp23C[i] == row) && ((s32) sp23C[i] >= (s32) FI(arg0, 0x62))) {
                u8 idx = (u8) sp23C[i];
                u16 v = sp27C[idx];
                sp37C[idx] = v;
                sp23C[i] = v;
            }
        }
        err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp37C[0], (u16 (*)[]) 1, (s32 *) row);
        if (err != 0) {
            return err;
        }
        row += 1;
        if ((row & 0xFF) < (s32) FI(arg0, 0x64)) {
            goto loop_51;
        }
    }

    if (overflow != 0) {
        FI(arg0, 0x0) = FI(arg0, 0x0) | 2;
    } else {
        FI(arg0, 0x0) = FI(arg0, 0x0) & ~2;
    }
    return 0;
}
#undef FI
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000725C4);
#endif
