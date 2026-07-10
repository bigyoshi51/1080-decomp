#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];



/* func_800066B0+func_800066D0 INCLUDE_ASM moved to kernel_017.c on
 * 2026-05-05 to enable the 3-way merge with the parent fragment
 * func_80006698. Per
 * feedback_cross_file_fragment_unblock_via_move_then_merge.md: moving
 * just the INCLUDE_ASM (no C body change) is layout-neutral when both
 * .o files reside in adjacent linker-script slots and the destination
 * .o gets exactly the bytes the source loses. Adjacent .ld slots
 * verified: kernel_017.c.o then kernel_018.c.o.
 * 800066D0 caller-entry symbol preserved via undefined_syms_auto.txt
 * (still resolves at 0x800066D0 inside the merged 800066B0 body). */

/* split from kernel_018.c - 2026-06-10 kernel ROM-order relayout */



/* func_80007564 - verified structural decode (kernel, 0x134, rmon
 * thread-list command handler). rmon family (cf. func_8000798C /
 * func_80009584 / func_80007A98; libreultra rmon).
 * Struct-typing reference: __rmonUtilityBuffer (UB) - UB->0x4 (4)
 * u8 domain, UB->0x6 (6) u16 cleared, UB->0xC (12) s32 status/echo
 * (0x3EA = error code when msg->0xC==-1), UB->0x10 (16) u16 entry
 * count, UB->0x14 (20) s32[] entry-id array. RmonMsg msg: msg->0x4
 * (4) domain, msg->0x9 (9) u8 mode (1 = single), msg->0xC (12) s32
 * request id (-1 = invalid). Thread chain node (from func_80009C30
 * = __osThreadList/queue head): node->0x4 (4) sentinel (-1 = end),
 * node->0xC (12) next, node->0x14 (20) thread id. func_800073F8 =
 * __rmonSendHeader(buf, len = count*4 + 0x14, flag = 1). Caps <80:
 * rmon utility-buffer build + thread-chain walk + branch-likely +
 * __rmonSendHeader. INCLUDE_ASM remains build path (no episode;
 * tautology-trap rule).
 * 2026-06-04 (22.9 -> 37.99%): control-flow fix. The old C `goto send`
 * from the msg->0xC==-1 and msg->9==1 arms SKIPPED the `ub->4=msg->4;
 * ub->6=0` stores, but in the asm those live in the common end block
 * (.L8000764C) that EVERY path reaches — so the -1 arm must fall through
 * to the msg->9 check and the two end-stores must be unconditional after
 * the if/else, not behind the early-exit label. Now structured as plain
 * nested if/else with one tail.
 * 2026-06-23 (37.99 -> 76/77 words, 1-insn residual): full regalloc rebuild.
 * Levers that reproduced the target's frame -0x30 layout exactly:
 *   (1) `register char *m = msg;` + `register char *t;` — pins msg to $s0
 *       (reloaded once from its 0x30 arg-home at entry, live across the two
 *       jals to its 0x4 use at .L8000764C) and the thread node to $s1
 *       (register-resident through the chain walk). m used for msg->0xC/0x4.
 *   (2) the msg->0x9 check reads the RAW PARAMETER `msg` (NOT `m`): at the
 *       branch-join .L800075B0 the target reloads msg from 0x30(sp) rather
 *       than reuse $s0 — using `msg` here emits that `lw $t1,0x30(sp)`.
 *   (3) the msg->0xC==-1 arm writes the GLOBAL directly
 *       (`*(int*)(&__rmonUtilityBuffer+0xC)=0x3EA`) so it uses the live
 *       lui/addiu $t6 (`sw $t8,0xC($t6)`); every other ub access goes
 *       through the stack-homed `ub` pointer (reloaded from 0x28(sp), 9x).
 *   (4) `int pad;` declared BEFORE `ub` reserves slot 0x2C so the M-class
 *       `ub` pointer lands at 0x28 (decl-order = high->low slot numbering:
 *       first-declared gets the highest sp offset; without pad ub takes
 *       0x2C, with ub-last it takes 0x24). Phantom-slot frame-layout lever.
 *   (5) func_800073F8 called DIRECTLY (no fn-ptr cast) -> `jal` not jalr.
 * RESIDUAL (1 real insn, genuine -O1 coloring artifact): the tail builds
 * the 2nd arg as `count*4+0x14`. Target emits `sll $t0,$a1,2; or $a1,$t0,0`
 * (materializes the product in a scratch $t reg then MOVES it back to $a1),
 * mine emits `sll $a1,$a1,2` in place — exactly 1 instr short (76 vs 77
 * words). The redundant `move $a1,$t0` is an IDO scheduling/coloring
 * consequence of `a0=ub` being assigned BETWEEN the lhu(count) and the
 * shift; clean C at -O1 never re-materializes through the temp. Verified
 * non-reproducible across ~10 arg-expression forms (int/unsigned/short
 * casts, <<2 vs *4, operand reorder, register-temp, block-scoped copy —
 * each either folds the move away or regresses the frame to -0x38). The
 * other 4 word-diffs are HI16/LO16(__rmonUtilityBuffer) + R_MIPS_26
 * (func_80009C30, func_800073F8) reloc placeholders that resolve at link.
 * 2026-07-10 EXACT via IDO 5.3 -O1 donor splice: the sll-temp+move residual
 * is a 7.1-only fold — IDO 5.3 -O1 emits `sll t0,a1,2; or a1,t0,zero`
 * exactly like the target (77/77, standalone-proven vs the .s, only reloc
 * placeholders differ). Donor: src/kernel/kernel_018_f_ido53_7564.c,
 * spliced over the body below via REPLACE_FUNC_BODY (this unit is 7.1 -O1,
 * which compiles the same C 1 insn short; donor bytes replace it in the
 * .o). */
extern void func_800073F8(); /* needed by the C body; split piece lost the chunk-local extern */
extern char __rmonUtilityBuffer;
extern char *func_80009C30(void);
/* func_800073F8 is forward-declared 0-arg above (fragment stub); cast at
 * call site to its real 3-arg __rmonSendHeader signature. */
s32 func_80007564(char *msg) {
    int pad;
    char *ub = &__rmonUtilityBuffer;
    register char *m = msg;
    register char *t;
    if (*(int*)(m + 0xC) == -1) {
        *(int*)(&__rmonUtilityBuffer + 0xC) = 0x3EA;
    } else {
        *(int*)(ub + 0xC) = *(int*)(m + 0xC);
    }
    if (*(unsigned char*)(msg + 0x9) == 1) {
        *(unsigned short*)(ub + 0x10) = 1;
        *(int*)(ub + 0x14) = 0x3E8;
    } else {
        t = func_80009C30();
        *(unsigned short*)(ub + 0x10) = 0;
        if (*(int*)(t + 0x4) != -1) {
            do {
                if (*(int*)(t + 0x14) != 0) {
                    ((int*)(ub + 0x14))[*(unsigned short*)(ub + 0x10)] = *(int*)(t + 0x14);
                    *(unsigned short*)(ub + 0x10) += 1;
                }
                t = *(char**)(t + 0xC);
            } while (*(int*)(t + 0x4) != -1);
        }
    }
    *(unsigned char*)(ub + 0x4) = *(unsigned char*)(m + 0x4);
    *(unsigned short*)(ub + 0x6) = 0;
    func_800073F8(ub, *(unsigned short*)(ub + 0x10) * 4 + 0x14, 1);
    return 0;
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
#define HW(p, o) (*(u16 *)((char *)(p) + (o)))
extern u8 __rmonRcpAtBreak;
/* rmon thread/RCP register-query setup. Populate the reply context arg2 for
 * thread arg1: mode arg0==1 = RCP (SP IMEM window 0x04001000, read the RCP
 * break-word via func_80006A98, flag a pending RCP break), else find the CPU
 * thread in the chain (func_80009C30) by id and copy its saved PC/break state.
 * The 0x8000785C alt-entry (external callers via undefined_syms) is the shared
 * unk12-flag tail. (Unblocked by adding an alabel for m2c parsing.)
 *
 * 2026-06-20 (95.9 -> 99.5%): structural rebuild. (1) `void *volatile sp18`
 * forces the per-statement reload of the thread-chain node that the target does
 * everywhere (loop walk + 4 tail accesses) — at -O1 IDO otherwise CSEs the
 * pointer across the loop's branch BB and collapses the `sp18 = sp18->0xC`
 * reload (loop emitted 2 insns short). (2) the goto-loop form (NOT `while`,
 * which let IDO cache sp18 and grew it +5 insns) matches the guard+top-test
 * shape. (3) the HW(sp18,0x10) value is reused via `sp1C` (already homed for
 * the later 0x11C value) so the lhu result is held in a register across the
 * branch, matching the target's single `lhu $t0` reuse — NOT a fresh named
 * `temp_t0` (that adds a 3rd M-class home → frame 0x20 -> 0x28, the +8 cascade).
 * RESIDUAL (1 real insn, genuine cap): target keeps the HW value in a
 * register-only subexpression temp ($t0, no stack home); reusing the homed
 * `sp1C` forces a dead `sw $t0,0x1C(sp)` into the beqz delay slot (target=nop).
 * Register-only temp is unreachable from C here: named locals always home
 * (M-class), and the volatile sp18 required for the loop blocks the inline-CSE
 * that would otherwise yield a homeless temp. Verified across 12+ variants
 * (named/block/register temp, ternary, arg0-reuse, inline, ptr-snapshot,
 * store-then-fixup, RW(&sp18) volatile-addr, non-volatile do-while). The other
 * 6 word-diffs are R_MIPS_26/HI16/LO16 reloc placeholders (func_80008430,
 * func_80006A98, func_80009C30, __rmonRcpAtBreak) that resolve at link. */
s32 func_80007698(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_80008430();
    s32 sp1C;
    void *volatile sp18;

    FW(arg2, 0x14) = arg1;
    if (arg0 == 1) {
        FW(arg2, 0x18) = 0x3E9;
    } else {
        FW(arg2, 0x18) = 0x3EA;
    }
    HW(arg2, 0x10) = 1;
    HW(arg2, 0x12) = 0;
    HW(arg2, 0x24) = 0;
    HW(arg2, 0x26) = 0;
    FW(arg2, 0x30) = 0;
    if (arg0 == 1) {
        FW(arg2, 0x2C) = 0x04001000;
        FW(arg2, 0x28) = 0x2A;
        if (func_80008430() != 0) {
            FW(arg2, 0xC) = 4;
            FW(arg2, 0x20) = 0;
            FW(arg2, 0x1C) = 0;
        } else {
            FW(arg2, 0xC) = 1;
            FW(arg2, 0x20) = func_80006A98(0x04080000) + 0x04001000;
            sp1C = func_80006A98(FW(arg2, 0x20));
            if ((sp1C & 0xFC00003F) == 0xD) {
                sp1C = 0xD;
            }
            if (__rmonRcpAtBreak != 0) {
                HW(arg2, 0x10) = 2;
                HW(arg2, 0x24) = 2;
                HW(arg2, 0x26) = 4;
            }
            FW(arg2, 0x1C) = sp1C;
        }
        goto block_25;
    }
    sp18 = (void *) func_80009C30();
    if (FW(sp18, 4) != -1) {
loop_12:
        if (FW(sp18, 0x14) != arg1) {
            sp18 = (void *) FW(sp18, 0xC);
            if (FW(sp18, 4) != -1) {
                goto loop_12;
            }
        }
    }
    if (FW(sp18, 4) == -1) {
        return -2;
    }
    FW(arg2, 0x28) = FW(sp18, 4);
    sp1C = HW(sp18, 0x10);
    if (sp1C != 0) {
        FW(arg2, 0xC) = sp1C;
    } else {
        FW(arg2, 0xC) = 1;
    }
    FW(arg2, 0x20) = FW(sp18, 0x11C);
    sp1C = *(s32 *) FW(sp18, 0x11C);
    if ((sp1C & 0xFC00003F) == 0xD) {
        sp1C = 0xD;
    }
    FW(arg2, 0x1C) = sp1C;
    FW(arg2, 0x2C) = (s32) sp18;
    if (HW(sp18, 0x12) & 1) {
        HW(arg2, 0x10) = 2;
        HW(arg2, 0x24) = 2;
        HW(arg2, 0x26) = 4;
    } else if (HW(sp18, 0x12) & 2) {
        HW(arg2, 0x10) = 2;
        HW(arg2, 0x24) = 1;
        HW(arg2, 0x26) = 2;
    }
block_25:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007698);
#endif
