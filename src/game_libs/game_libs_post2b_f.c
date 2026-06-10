#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;



INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

/* gl_func_00074EFC: 1080 osCreatePiManager-family singleton init (96 insns,
 * 12 jals) -- NOT osPfsIsPlug (tested verbatim 2026-06-10, wrong shape).
 * BOUNDARY FIXED 2026-06-10: the initialized-flag LOAD (lui t6/lw t6) was
 * misattributed to the predecessor pad symbol (74EDC); the two words now
 * live at the head of this .s (size 0x180 -> 0x188, fn truly starts at
 * USO 0x74EF4). With the guard load in-symbol, an `if (!D_flag)` C body
 * emits the lui/lw/bnez head naturally -- the remaining blocker is only
 * the gl_dref fixed-address data symbols. Body, with hardcoded RUNTIME data addresses (the
 * data analog of the gl_ref jal thunks; bootup-region block at 0x45230):
 *   osCreateMesgQueue(Q_45230, MSGS_45248, 5);
 *   REC_45260 = {type 13, 0, 0}; REC_45278 = {type 14, 0, 0};
 *   osSetEventMesg(7, Q_45230, &REC_45260);
 *   osSetEventMesg(3, Q_45230, &REC_45278);
 *   saved = -1; cur = osGetThreadPri(0);
 *   if (cur < pri) { saved = cur; osSetThreadPri(0, pri); }
 *   v = call();  -- saved at sp+0x2C
 *   CTL = {1, &THREAD_45230+?, base, base};  -- reloc'd control block
 *   CTL+0x10..0x18 = 0;
 *   osCreateThread(&THREAD_44080?, 0, entry_0x8xxxx-ish, reloc_arg,
 *                  STACK_45230+0x1000, pri_from_arg);
 *   call(); osStartThread-like(&T_44080); call(v);
 *   if (saved != -1) osSetThreadPri(0, saved);
 * Matching needs: the stolen flag-load boundary fix (splat boundary
 * correction) + fixed-address data symbols (gl_dref_00045230 family) --
 * multi-step infra; INCLUDE_ASM is build path. */
/* 2026-06-10 MATCH PUSH (5.3 -O1, reloc-aware standalone): 105/98 insns,
 * 30 non-reloc diffs. CONFIRMED: head (pre-prologue flag load) emits
 * naturally from if(!flag) at 5.3 -O1; gl_dref extern symbols produce
 * the addiu %lo forms (literals emit ori -- wrong); decl order v,saved,
 * cur fixes the stack homes; gl_ref_000896E8 (= USO 0x7507C + 0x1466C,
 * the thread entry = the NEXT function!) passes as a code pointer with
 * the correct lui 9/addiu -26904 shape. Residual: +7 insns from the
 * event-record constant stores (target uses lui-at + %lo-folded sh/sb/sw
 * with at reuse; build materializes per-field temps) and downstream
 * scheduling. Needed for in-tree: gl_dref_* + D_74EFC_* values in
 * undefined_syms (0x45230/45248/45260/45278/44230/44080; gl_ref_000896E8
 * = 0x000896E8) and a 5.3 -O1 carve. */
#ifdef NON_MATCHING
typedef struct {
    u16 type; u8 b; u8 pad; s32 w;
} GlEvRec;

extern int gl_func_00000000();
extern int gl_ref_000896E8();
extern s32 D_74EFC_flag;
extern char *D_74EFC_t1;
extern char *D_74EFC_t2a;
extern char *D_74EFC_t2b;
extern s32 D_74EFC_z0;
extern s32 D_74EFC_z1;
extern s32 D_74EFC_z2;
extern int D_74EFC_arg;
extern char gl_dref_00045230;
extern char gl_dref_00045248;
extern GlEvRec gl_dref_00045260;
extern GlEvRec gl_dref_00045278;
extern char gl_dref_00044230;
extern char gl_dref_00044080;

void gl_func_00074EFC(int pri) {
    s32 v;
    s32 saved;
    s32 cur;

    if (D_74EFC_flag == 0) {
        gl_func_00000000();
        gl_func_00000000(&gl_dref_00045230, &gl_dref_00045248, 5);
        gl_dref_00045260.type = 13;
        gl_dref_00045260.b = 0;
        gl_dref_00045260.w = 0;
        gl_dref_00045278.type = 14;
        gl_dref_00045278.b = 0;
        gl_dref_00045278.w = 0;
        gl_func_00000000(7, &gl_dref_00045230, &gl_dref_00045260);
        gl_func_00000000(3, &gl_dref_00045230, &gl_dref_00045278);
        saved = -1;
        cur = gl_func_00000000(0);
        if (cur < pri) {
            saved = cur;
            gl_func_00000000(0, pri);
        }
        v = gl_func_00000000();
        D_74EFC_flag = 1;
        D_74EFC_t1 = &gl_dref_00044230;
        D_74EFC_t2a = &gl_dref_00044080;
        D_74EFC_t2b = &gl_dref_00044080;
        D_74EFC_z0 = 0;
        D_74EFC_z1 = 0;
        D_74EFC_z2 = 0;
        gl_func_00000000(&gl_dref_00044230, 0, gl_ref_000896E8, &D_74EFC_arg,
                         &gl_dref_00044230 + 0x1000, pri);
        gl_func_00000000();
        gl_func_00000000(&gl_dref_00044080);
        gl_func_00000000(v);
        if (saved != -1) {
            gl_func_00000000(0, saved);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074EFC);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0007507C)();
void gl_func_0007507C(char *arg0) {
    char *sp34;
    char *sp30;
    u16 *sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t6;
    u16 temp_s0;
    u16 temp_t3;
    u16 temp_t7;
    char *temp_t3_2;
    char *temp_t5;
    char *temp_t8;

    sp2C = 0;
    sp28 = 0;
    sp34 = game_libs_func_00070FCC();
    temp_t7 = FW(sp34, 0x2);
    *(u16 *)0x45290 = temp_t7;
    if (temp_t7 == 0) {
        *(char *)0x45290 = 1U;
    }
    sp30 = arg0;
loop_3:
    game_libs_func_00070FCC(FW(sp30, 0xC), &sp2C, 1);
    temp_s0 = *(int*)sp2C;
    if (temp_s0 == 0xD) {
        game_libs_func_00070FCC();
        temp_t3 = *(char *)0x45290 - 1;
        *(char *)0x45290 = temp_t3;
        if (!(temp_t3 & 0xFFFF)) {
            sp34 = game_libs_func_00070FCC();
            temp_t6 = FW(sp34, 0x10);
            if (temp_t6 != 0) {
                game_libs_func_00070FCC(temp_t6, FW(sp34, 0x14), 0);
            }
            *(char *)0x45290 = (u16) FW(sp34, 0x2);
        }
        *(int*)0 = (char *) (*(int*)0 + 1);
        if (sp28 != 0) {
            sp24 = game_libs_func_00070FCC();
            *(int*)0 = 0;
            *(char **)4 = sp24;
            sp28 = 0;
        }
        sp24 = *(int*)0;
        *(int*)0 = game_libs_func_00070FCC();
        temp_t3_2 = *(char *)4;
        temp_t8 = *(int*)0 - (int)sp24;
        temp_t5 = temp_t8 + (int)temp_t3_2;
        *(int*)0 = (char *) (((u32) temp_t5 < (u32) temp_t3_2) + *(int*)0);
        sp24 = temp_t8;
        *(char *)4 = temp_t5;
        goto loop_3;
    }
    if (temp_s0 != 0xE) {
        goto loop_3;
    }
    game_libs_func_00070FCC();
    goto loop_3;
}
#else
/* gl_func_0007507C = the PI-manager THREAD MAIN (identified via 74EFC's
 * hardcoded entry 0x896E8 = USO 0x7507C + reloc base). -Olimit-fallback
 * shape (scheduled -O0: homed locals, per-use reloads, filled bnez
 * delays, unfilled jal delays). Decoded structure: one-time init copies
 * g->u16_2 into the hardcoded countdown halfword 0x45290 (assignment-in-
 * condition -- a named temp would get homed, the target's t7 reuse only
 * comes from `if ((GH = expr) == 0)`); then an infinite osRecvMesg
 * dispatch on msg->u16 type: 13 = tick (countdown u16 RMW, on zero
 * re-fetch state and fire callback g->p_10(g->p_14, 0) + reload
 * countdown; then event counter ++, optional u64-accumulator rebase, and
 * ACC += (now - prev) via the compiler's 32->64 addu/sltu pair); 14 =
 * single call. 2026-06-10 standalone at 5.3 -O1 -Olimit 1: 109/115
 * insns (target includes 6 zero pad words before the dead epilogue).
 * 2026-06-10 pass 2: SWITCH dispatch (not if/else-if) drops diffs 61->50
 * (case-13-first layout right). Residual = the persistent +8 frame
 * (0x40 vs 0x38): the dispatch value's reserved slot -- register var,
 * plain local, switch expr, 5.3/7.1, -O1 and -Olimit ALL reserve it;
 * the target keeps the value in s0 with NO slot. Pass 3 negatives
 * (2026-06-10): reusing the existing t local as the switch value keeps
 * frame 0x40 AND worsens diffs to 64 -- the slot belongs to the
 * switch's INTERNAL temp, not the named variable. Note the target s0
 * live range (one lhu, two compares) crosses NO call, yet sits in a
 * saved reg -- an -Olimit allocator quirk we cannot reproduce with any
 * tested shape; possibly needs the uoptlist regalloc dump
 * (project_1080_regalloc_dump_unlocked memo) to settle.
 * Carve recipe when matched: gl_dref_00045290 = 0x00045290 +
 * D_7507C_cnt/acc/prev placeholders (already in undefined_syms). */
#ifdef NON_MATCHING
typedef unsigned long long u64;
extern int gl_func_00000000();
extern unsigned short gl_dref_00045290;
extern unsigned int D_7507C_cnt;
extern u64 D_7507C_acc;
extern unsigned int D_7507C_prev;

void gl_func_0007507C(char *arg) {
    char *g;
    char *q;
    int msg;
    int flag;
    unsigned int t;

    msg = 0;
    flag = 0;
    g = (char *)gl_func_00000000();
    if ((gl_dref_00045290 = *(unsigned short *)(g + 2)) == 0) {
        gl_dref_00045290 = 1;
    }
    q = arg;
    for (;;) {
        gl_func_00000000(*(int *)(q + 0xC), &msg, 1);
        switch (*(unsigned short *)msg) {
        case 13: {
            gl_func_00000000();
            gl_dref_00045290 = gl_dref_00045290 - 1;
            if (gl_dref_00045290 == 0) {
                gl_func_00000000();
                g = (char *)gl_func_00000000();
                if (*(int *)(g + 0x10) != 0) {
                    gl_func_00000000(*(int *)(g + 0x10), *(int *)(g + 0x14), 0);
                }
                gl_dref_00045290 = *(unsigned short *)(g + 2);
            }
            D_7507C_cnt += 1;
            if (flag != 0) {
                t = gl_func_00000000();
                D_7507C_acc = t;
                flag = 0;
            }
            t = D_7507C_prev;
            D_7507C_prev = gl_func_00000000();
            D_7507C_acc += (unsigned int)(D_7507C_prev - t);
            break;
        }
        case 14:
            gl_func_00000000();
            break;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007507C);
#endif
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_00075248_pad.s")
/* game_libs_func_00075254: the standard cross-USO int-reader template
 * (return D_global), matched in-place at the unit's default 7.1 -O2.
 * The symbol was mis-split as 75248 (3 leading zero pad words now in the
 * _pad sidecar); cc's natural function padding supplies the trailing
 * alignment to 0x7526C. */
extern int D_75254_v;
int game_libs_func_00075254(void) {
    return D_75254_v;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075260);

/* gl_func_0007526C MATCHED 2026-06-10 as game_libs_func_00075264 (own
 * -O1 carve unit game_libs_ido_75264.c): the "dual-entry" theory was
 * wrong -- 75260's lui/lw was the fn's own first statement (boundary
 * mis-split) and the leading nop is 75254's trailing pad (kept below as
 * the 1-word 75260 pad INCLUDE). */
