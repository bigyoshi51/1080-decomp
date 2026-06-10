#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;


#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int D_00000000;   // D_a: fixed data arg threaded to the cb (lui+addiu)
extern int D_74C_b;      // D_b: address compared against arg0->0x8
extern int *D_74C_c;     // *&D_c: gate pointer + record (->4)
extern int *D_74C_d;     // *&D_d: peer record stored into (->0x10)
// State-machine step keyed on the u16 arg0->0x10. st==1: if the handle
// arg0->0x8 is null or the sentinel &D_b, demote to 2 and notify(&D_a,arg0);
// else promote to 8, notify(handle,arg0) and notify(&D_a, notify(handle)).
// st==8: demote to 2 + notify(&D_a,arg0). Then a global-record pass: if *&D_c
// is null, notify(); else if (*&D_d)->4 < (*&D_c)->4 demote (*&D_d)->0x10 to 2
// + notify(&D_a). Finally notify(s0) with the saved first-call result. The cb
// (game_libs_func_00070FCC) and &D globals are reloc-blind (field-0 matchable).
// 2026-06-10 SUPERSEDED CAP ANALYSIS: at IDO 5.3 -O1 (the ido53-carve
// compiler) with `register char *s0; register int x;` (x holds st AND the
// later call result -- one variable, the s1 reuse), the build reproduces
// the s0/s1 saves, the v0->s0 capture, and 84/84 instruction count with
// correct branch polarity when the st arms are written as
// `if (x != 1) { if (x == 8) {...} } else {...}`. Residual (~5 real
// shapes cascading into ~73 word diffs via offset/regnum shift): (a) the
// target reloads p from its stack home INSIDE the st==8 arm while 5.3
// CSEs the earlier load (basic-block-boundary reload not yet forced --
// typed struct members did NOT change this, unlike the -O0 case); (b)
// frame 0x28 vs 0x30 (+8, likely the h temp slot). Next pass: shapes
// that force a fresh p reload in the st==8 arm (volatile-pointer-fetch
// lever from docs/IDO_CODEGEN?), then carve at 5.3 -O1.
void gl_func_00074C04(char *arg0) {
    char *s0;
    unsigned short st;
    int r;

    s0 = (char *)game_libs_func_00070FCC();
    st = *(unsigned short *)(arg0 + 0x10);
    if (st == 1) {
        char *h = *(char **)(arg0 + 0x8);
        if ((h == 0) || (h == (char *)&D_74C_b)) {
            *(unsigned short *)(arg0 + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000, arg0);
        } else {
            *(unsigned short *)(arg0 + 0x10) = 8;
            game_libs_func_00070FCC(*(char **)(arg0 + 0x8), arg0);
            r = game_libs_func_00070FCC(*(char **)(arg0 + 0x8));
            game_libs_func_00070FCC((char *)&D_00000000, r);
        }
    } else if (st == 8) {
        *(unsigned short *)(arg0 + 0x10) = 2;
        game_libs_func_00070FCC((char *)&D_00000000, arg0);
    }
    if (D_74C_c == 0) {
        game_libs_func_00070FCC();
    } else {
        if (D_74C_d[1] < D_74C_c[1]) {
            *(unsigned short *)((char *)D_74C_d + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000);
        }
    }
    game_libs_func_00070FCC(s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074C04);
#endif

#ifdef NON_MATCHING
/* gl_func_00074D54: 22-insn float-arg + global-state wrapper.
 *   rv = func_a(f);            // jal#1 takes float
 *   g->[0x24] = f;              // store f as float
 *   *(short*)g |= 4;            // bit-set in halfword
 *   return func_b(rv);          // jal#2 takes int
 *
 * 2026-05-15 — applied unique-extern recipe (gl_data_00074_a and
 * gl_data_00074_b separate symbols added to undefined_syms_auto.txt) to
 * break IDO's CSE on the duplicate `lui+lw 0(*)` pair. Plus `register`
 * hint on rv. Result: 19/22 insns (still 3 short). Target uses $s0 for
 * rv across the FPU work; IDO sees rv's only post-jal use is the next
 * jal (immediate tail-call style) and keeps it in $v0 → no $s0 save.
 * The "rv needs $s0" can't be forced without an artificial extra use
 * that would add MORE insns. Cap holds at the documented 67-86% range. */
extern int gl_data_00074_a;
extern int gl_data_00074_b;
int gl_func_00074D54(int a0, float arg1) {
    int rv = gl_func_00000000(a0);
    *(float*)((char*)gl_data_00074_a + 0x24) = arg1;
    *(short*)gl_data_00074_b |= 4;
    return gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074D54);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074D54_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074DB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074EFC);

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
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007507C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075248);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075260);

#ifdef NON_MATCHING
/* SP_PC_REG (uncached, 0xA4080000) conditional writer.
 *   if ((flag & 1) != 0) { *(volatile u32*)0xA4080000 = pc; return 0; }
 *   else { return -1; }
 *
 * 11-insn target with `addiu sp, -8` + matching `addiu sp, sp, 8` at the
 * very end — fake stack frame even though no body uses it. Per
 * feedback_ido_sp_frame_without_stack_use.md: IDO -O2 won't allocate a
 * frame from standard C unless something actually touches the stack.
 *   - With body alone: 9 insns, no frame (mismatch).
 *   - With `volatile int x = 0;` to force a slot: 11 insns + frame BUT also
 *     emits `sw zero, 4(sp)` in the delay slot AND shifts $tN registers up
 *     by 1 (target uses t7/t8; mine t6/t7). Mismatch.
 *
 * Cap: ~85 % via the volatile-int form. Real fix needs a way to allocate
 * frame without stack use — which IDO doesn't expose.
 *
 * 2026-05-30 — DUAL-ENTRY context: the predecessor orphan game_libs_func_00075260
 * (`nop; lui t6,0xA404; lw a1,0x10(t6)`, no jr ra) loads this body's `flag` (a1)
 * from the RSP register 0xA4040010 (SP_STATUS read), then falls through. So the fn
 * is an RSP-poll: entered via 0x75260, flag = SP_STATUS; entered directly here,
 * flag = caller's. NOT an orphan-merge candidate — (a) dual-entry (body callable
 * with caller flag), and (b) the merged single-entry C reads SP_STATUS into $v0 and
 * emits a different leaf shape (no frame), so it can't reproduce the body's frame.
 * The hw write target 0xA4080000 = SP_PC_REG (RSP program counter). Both INCLUDE_ASM. */
int gl_func_0007526C(unsigned int pc, int flag) {
    volatile int x = 0;
    if ((flag & 1) == 0) {
        return -1;
    }
    *(volatile unsigned int*)0xA4080000 = pc;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007526C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0007526C_pad.s")
#endif
