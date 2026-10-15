/* IDO 7.1 -O2 donor for gl_func_0002FB74 -- event -> sound command
 * dispatcher (612/612 words; st_size 0x990).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post.c.o (the
 * 29CCC / 31334 recipe, docs/MATCHING_WORKFLOW.md#two-jumptables-one-donor-
 * 31334). Both jumptables land in this unit's local .rodata (the st.w10 gate
 * switch, 21 entries for sel 19..39, at +0; the main switch, 49 entries for
 * sel 2..50, at +0x54); the splice renames the reloc to
 * gl_func_0002FB74_rodata, pinned to 0x1750, so the %lo words link to
 * 0x1750 / 0x17A4 as the USO ships them.
 *
 * Load-bearing shapes (97.0 -> exact, 2026-10-15 agent-c):
 *  - case 39 has its OWN level local (b3). Sharing `b` with cases 2/36/512
 *    rotated three webs: v a2 / c v1 / b a3 instead of v a3 / c a2 / b v1.
 *  - case 39 reads gN into `cmd` (the v0 web) after `b3 = 0;`, and the level
 *    steps are `b3++` twice: the first folds to a copy of the constant-1
 *    register (or v1,t1), the second is `addiu v1,t1,1`.
 *  - case 34 tests gG inline after the gH store (a named local became a
 *    global web in v0; the target loads it into a t-temp).
 *  - case 36 reuses `b` for the toggle: n = tgl; sel = n + 186; n ^= 1.
 *  - case 2/4/8/258: `case 258: case 2:` share one arm (beql into the arm
 *    with `c = 28` in the delay slot; IDO_CODEGEN#beql-into-arm-shared-case-
 *    labels-2f934).
 *  - case 17: `p = &chan;` INSIDE the gD == 0 arm keeps the full address in
 *    v0 (scheduled above the branch); assigning it one level up folds it
 *    into the lbu.
 *  - the mode-1 call's 0 is `addiu a1,zero,0` = 0.0f to the (int, float)
 *    blank alias gl_func_00000000_f.
 *  - baked words: 0x1C908 / 0x1C90C counters and toggle (per-site pinned
 *    names keep a lui per access), in-unit jals 0x423A4 / 0x42428 /
 *    0x44B70 (gl_ref_ pins / the pinned gl_func_00042428). */
#include "common.h"

extern void gl2FB74_snd();                  /* USO-relocated submit (jal 0) */
extern int gl_func_00000000_f(int, float);  /* (int, float) blank alias */
extern int gl_func_00042428();              /* pinned 0x42428, case 50 */
void gl_ref_00044B70(int a0);               /* baked tail call (gl_func_00030504) */
void gl_ref_000423A4(unsigned char a0);     /* baked call (game_libs_func_0002DD38), case 512 */

extern s32 D_2FB74_mode;                    /* t2 web (==0/1/8 state) */
extern s32 D_2FB74_cmdsrc;                  /* per-case cmd reload */
extern s32 D_2FB74_g7, D_2FB74_g8, D_2FB74_g9;
extern s32 D_2FB74_gA, D_2FB74_gB, D_2FB74_gC, D_2FB74_gD, D_2FB74_gF;
extern s32 D_2FB74_gG, D_2FB74_gH, D_2FB74_gI, D_2FB74_gJ, D_2FB74_gK;
extern s32 D_2FB74_gL, D_2FB74_gN, D_2FB74_gO, D_2FB74_gP, D_2FB74_gQ;
extern s32 D_2FB74_gS, D_2FB74_gT, D_2FB74_gV, D_2FB74_gW, D_2FB74_gX;
/* abs 0x1C908/0x1C90C baked in expected (reloc-free USO). Per-site distinct
 * extern names break address-CSE so every access is its own lui/%lo pair,
 * matching the baked shape (imm bytes remain the documented USO-reloc residual). */
extern s32 D_2FB74_cnt;                     /* case 39 = 0 */
extern s32 D_2FB74_cnt2;                    /* case 34 = 0 */
extern s32 D_2FB74_cnt3, D_2FB74_cnt3w;     /* case 32 ++ (read/write split) */
extern s32 D_2FB74_cnt4;                    /* case 17 = 0 */
extern s32 D_2FB74_tgl, D_2FB74_tglw;       /* case 36 read / write split */

typedef struct Gl2FB74St {
    s32 w0;
    s32 w4;                                 /* busy/refresh (10) */
    s32 w8;                                 /* cooldown (300) */
    s32 wC;
    s32 w10;                                /* timer (20/30/40/60) */
    s32 w14;                                /* accum (+= 32) */
    s32 w18;                                /* level (0x7F) */
} Gl2FB74St;
extern Gl2FB74St D_2FB74_st;

typedef union Gl2FB74Chan {
    s32 w;
    u8 b[4];
} Gl2FB74Chan;
extern Gl2FB74Chan D_2FB74_chan;

typedef struct Gl2FB74Bank {
    u8 pad[0x2F0];
    s32 arr[2];                             /* lw/sw 0x2F0(base + i*4) */
} Gl2FB74Bank;
extern Gl2FB74Bank D_2FB74_bank;

void gl_func_0002FB74(s32 sel, s32 v) {
    s32 t;
    s32 cmd;
    s32 c;
    s32 b;
    s32 b3;
    s32 n;
    Gl2FB74Chan *p;

    c = 0;
    if (sel == 0x13) {
        if (D_2FB74_mode == 1 && v == 8) {
            D_2FB74_st.w18 = 0x7F;
        }
    }
    if (D_2FB74_st.w10 != 0) {
        switch (sel) {
        case 19:
        case 32:
        case 34:
        case 36:
        case 39:
            return;
        }
    }
    if (sel == 0x13) {
        if (D_2FB74_st.w4 != 0) {
            return;
        }
    }
    cmd = 10;
    D_2FB74_st.w4 = cmd;
    switch (sel) {
    case 19:
        if (v == 5 && D_2FB74_st.w8 == 0) {
            gl2FB74_snd(3);
            D_2FB74_st.w8 = 300;
        }
        if (v < 4) {
            sel = 45;
        }
        cmd = D_2FB74_cmdsrc;
        break;
    case 23:
        if (v < 2) {
            gl2FB74_snd(2);
        } else {
            gl2FB74_snd(1);
        }
        D_2FB74_st.w10 = 40;
        cmd = D_2FB74_cmdsrc;
        break;
    case 7:
        if (D_2FB74_gA == 1 || D_2FB74_gA == 2 || D_2FB74_gA == 4) {
            gl2FB74_snd(0x6020301, (s8) (v + 42));
        } else {
            gl2FB74_snd(0x6020301, 50);
        }
        cmd = D_2FB74_cmdsrc;
        break;
    case 2:
    case 4:
    case 8:
    case 258:
        if ((v & 0x80) == 0) {
            b = 0;
        } else {
            b = 1;
        }
        if (sel == 258) {
            t = D_2FB74_bank.arr[b];
        } else {
            t = (v & 0xF) - 1;
            if (t < 0) {
                t = 0;
            }
            D_2FB74_bank.arr[b] = t;
        }
        gl2FB74_snd(0x6000003, (s8) b);
        switch (sel) {
        case 8:
            c = 16;
            break;
        case 4:
            c = 22;
            break;
        case 258:
        case 2:
            c = 28;
            break;
        }
        gl2FB74_snd(0x6020304, 50);
        gl2FB74_snd(0x6020302, (s8) (t + c));
        cmd = D_2FB74_cmdsrc;
        break;
    case 36:
        b = D_2FB74_gI;
        D_2FB74_gJ = 32;
        if (b != 4) {
            return;
        }
        if (D_2FB74_mode == 1 || D_2FB74_mode == 0 || D_2FB74_mode == 8 || D_2FB74_gK == 2) {
            gl2FB74_snd(v + 16);
            b = D_2FB74_gL;
        }
        if (b != 4) {
            return;
        }
        b = D_2FB74_tgl;
        sel = b + 186;
        b ^= 1;
        D_2FB74_tglw = b;
        cmd = D_2FB74_cmdsrc;
        break;
    case 39:
        b3 = 0;
        cmd = D_2FB74_gN;
        if (v < 1000) {
            sel += 2;
        } else {
            b3++;
            if (v >= 2000) {
                b3++;
                sel += 1;
            }
            if (v >= 4000) {
                sel += 2;
            }
        }
        D_2FB74_gO = b3 * 16 + 32;
        D_2FB74_st.w14 += 32;
        if (cmd == 0) {
            gl2FB74_snd(8, 360, 11);
        } else {
            gl2FB74_snd(8, 48, b3 + 3);
        }
        D_2FB74_cnt = 0;
        if (D_2FB74_gP != 4) {
            return;
        }
        switch (sel) {
        case 0:
        case 1:
            D_2FB74_st.w10 = 20;
            break;
        case 2:
            D_2FB74_st.w10 = 30;
            break;
        case 3:
            D_2FB74_st.w10 = 40;
            break;
        }
        cmd = D_2FB74_cmdsrc;
        break;
    case 34:
        if (D_2FB74_mode == 0) {
            gl2FB74_snd(8, 120, 10);
        } else {
            gl2FB74_snd(8, 8, 1);
        }
        D_2FB74_cnt2 = 0;
        D_2FB74_gH = 0;
        if (D_2FB74_gG != 4) {
            return;
        }
        cmd = D_2FB74_cmdsrc;
        break;
    case 32:
        D_2FB74_cnt3w = D_2FB74_cnt3 + 1;
        if (v != 1) {
            sel += 1;
        }
        gl2FB74_snd(40, 30, 0);
        cmd = D_2FB74_cmdsrc;
        break;
    case 12:
        D_2FB74_gB = v;
        gl2FB74_snd(0x6020301, (s8) (v + 9));
        cmd = D_2FB74_cmdsrc;
        break;
    case 9:
        gl2FB74_snd(0x6020301, 15);
        cmd = D_2FB74_cmdsrc;
        break;
    case 17:
        if (D_2FB74_gC == 4) {
            if (D_2FB74_gD == 0) {
                p = &D_2FB74_chan;
                gl2FB74_snd(p->b[3], 22);
                D_2FB74_gF = 1;
            }
        }
        if (D_2FB74_mode == 0) {
            gl2FB74_snd(240, 220, 9);
        }
        gl2FB74_snd(0x6020300, 8);
        D_2FB74_cnt4 = 0;
        cmd = D_2FB74_cmdsrc;
        break;
    case 16:
        if (D_2FB74_mode == 0) {
            D_2FB74_g7 = 0;
        }
        if (D_2FB74_mode == 1) {
            gl_func_00000000_f(0x1010300, 0.0f);
            D_2FB74_st.w18 = 0;
        }
        c = 1;
        if (D_2FB74_g8 == 4) {
            sel = 10;
            goto L_lad6;
        }
        if (D_2FB74_g8 != 2) {
            goto L_lad6;
        }
        if (D_2FB74_g9 >= 5) {
            goto L_lad6;
        }
        gl2FB74_snd(D_2FB74_g9 + 9);
        cmd = D_2FB74_cmdsrc;
        break;
    case 13:
L_lad6:
        c += 1;
    case 20:
L_lad5:
        c += 1;
    case 22:
        c += 1;
    case 21:
        c += 1;
    case 14:
        c += 1;
    case 15:
        c += 1;
    case 1190:
        gl2FB74_snd(0x6020300, (s8) c);
        D_2FB74_st.w10 = 60;
        cmd = D_2FB74_cmdsrc;
        break;
    case 256:
        gl2FB74_snd(0x6020300, 9);
        D_2FB74_st.w10 = 60;
        cmd = D_2FB74_cmdsrc;
        break;
    case 523:
        gl2FB74_snd(0x6020300, 10);
        D_2FB74_st.w10 = 60;
        cmd = D_2FB74_cmdsrc;
        break;
    case 405:
        gl2FB74_snd(0x6020300, 11);
        cmd = D_2FB74_cmdsrc;
        break;
    case 934:
        if (D_2FB74_gV == 8 && D_2FB74_gW == 10 && D_2FB74_gX == 2) {
            gl2FB74_snd(0x6020301, 57);
        } else {
            gl2FB74_snd(0x6020301, 51);
        }
        cmd = D_2FB74_cmdsrc;
        break;

    case 512:
        if (D_2FB74_gT == 2) {
            b = 1;
        } else {
            b = 0;
        }
        gl2FB74_snd(0x6020301, (s8) (b + 61));
        p = &D_2FB74_chan;
        p->w = 15;
        gl_ref_000423A4(p->b[3]);
        gl2FB74_snd(0x83010000, 3200);
        cmd = D_2FB74_cmdsrc;
        break;
    case 50:
        gl_func_00042428(14, 30, 2000, 0x3F333333);
        cmd = D_2FB74_cmdsrc;
        break;
    case 49:
        if (D_2FB74_gQ < 5) {
            gl2FB74_snd(0x6020301, (s8) (D_2FB74_gQ + 34));
        }
        return;
    case 309:
        cmd = D_2FB74_gS;
        if (cmd == 4) {
            if (v >= 2) {
                v = 1;
            }
            sel = sel + v;
        } else {
            sel = 55;
        }
        break;
    case 160:
        p = &D_2FB74_chan;
        if (p->w == 15) {
            gl2FB74_snd(0x8030900, 1);
        }
        cmd = D_2FB74_cmdsrc;
        break;
    case 260:
        return;
    default:
        cmd = D_2FB74_cmdsrc;
        break;
    }
    if (cmd == 0) {
        if (sel == 14 || sel == 21) {
            sel = 52;
        }
    }
    gl_ref_00044B70(sel);
}
