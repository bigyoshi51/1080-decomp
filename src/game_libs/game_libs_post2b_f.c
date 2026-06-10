#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074DB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

/* gl_func_00074EFC: 1080 osCreatePiManager-family singleton init (96 insns,
 * 12 jals) -- NOT osPfsIsPlug (tested verbatim 2026-06-10, wrong shape).
 * Guarded by an initialized-flag whose LOAD (lui at/lw t6) is stolen into
 * the predecessor symbol (bnez t6 at +0x8 uses t6 set before the prologue
 * boundary -- the leading-insn misattribution family; the flag store at
 * the end is reloc'd). Body, with hardcoded RUNTIME data addresses (the
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
#ifdef NON_MATCHING
void gl_func_00074EFC(int pri) {
    /* structural skeleton only -- see decode above; the hardcoded
     * bootup-region addresses and the stolen flag-load make a compiling
     * faithful body dependent on the boundary fix + dref symbols. */
    (void)pri;
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
