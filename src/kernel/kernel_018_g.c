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









/* func_80007A98 - verified structural decode (0xA4, 41 insns).
 * SIBLING of the rmon register-fetch family (func_8000798C
 * __rmonGetGRegisters calls this as func_80007A98(domain, id, &buf);
 * func_800079F4 is the dispatch sibling that donates the -0x78 stack
 * frame - this .s has no own prologue, it runs in func_800079F4's
 * frame and exits via the shared epilogue / cross-function labels
 * .L80007AB4/.L80007B28 (undefined_syms_auto.txt). NOT a fragment;
 * boundary already resolved.
 *   s32 func_80007A98(s32 domain, s32 id, void *buf) {
 *       func_80008498();                          // setup/lock
 *       ... shared-tail paths return -4 / -2 on error (.L80007B28)
 *       // recursive sub-fetch:
 *       v0 = func_80007A98(savedMsg->0x9, savedPayload->0xC, &hdr);
 *       if (v0 != 0) return -2;
 *       // build rmon header in stack struct at sp+0x28:
 *       hdr.0x2C = savedMsg->0x4;  hdr.0x2E = 0;
 *       func_800073F8(&hdr, 0x4C, 1);             // __rmonSendHeader
 *       if (hdr.0x34 == 1) {
 *           hdr.0x2C = 4;
 *           func_800073F8(&hdr, 0x4C, 2);
 *       }
 *       return 0;                                 // shared epilogue
 *   }
 * Struct-typing reference: rmon command sender for the register-fetch
 * family. buf/hdr stack struct at sp+0x28: +0x2C (0x2C) u8 command
 * tag (savedMsg->0x4, or 4 on the resend path), +0x2E (0x2E) s16
 * cleared field, +0x34 (0x34) s32 status checked == 1 (triggers a
 * second SendHeader with tag 4 / flag 2). func_800073F8 =
 * __rmonSendHeader(hdr, len=0x4C, flag). Caps <80: prologue-donated
 * shared frame (no local addiu sp) + recursion + 2x func_800073F8
 * rmon-builder + cross-function shared-epilogue branch-likely. Full
 * body INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM
 * (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007A98);

/* func_80007B3C - verified structural decode (kernel, 0x294, 165
 * insns, rmon breakpoint / thread-control command handler). rmon
 * family (cf. func_80007564 / func_80009584; __rmonRcpAtBreak,
 * func_800073F8 = __rmonSendHeader, func_80009C30 = thread list).
 *   s32 func_80007B3C(RmonMsg *msg) {
 *       switch (msg->0x9) {                        // command kind
 *       case 0:                                    // set/arm break
 *           t = func_80009C30();                   // thread head
 *           while (t->0x4 != -1) {                 // find by id
 *               if (t->0x14 == msg->0xC) break;
 *               t = t->0xC;                         // next
 *           }
 *           if (t->0x4 == -1) return -2;            // not found
 *           if (t->0x10 != 1) return -4;            // bad state
 *           t->0x12 &= ~0x4;                        // clear flag
 *           if (msg->0x10 & 0x2)                    // opt arg
 *               t->0x11C = msg->0x14;
 *           ... (program RCP/HW break via func_80006A50/_80006A98,
 *                __rmonRcpAtBreak; __rmonSendHeader reply) ...
 *           break;
 *       case 1: ...                                 // continue/clear
 *       default: ...
 *       }
 *   }
 * Struct-typing reference: RmonMsg msg - msg->0x9 (9) u8 command
 * kind (0 = arm breakpoint, 1 = another op), msg->0xC (12) target
 * thread id, msg->0x10 (16) flags (bit 1 / 0x2 = "set field"),
 * msg->0x14 (20) the value. Thread-chain node (func_80009C30 head):
 * node->0x4 (4) sentinel (-1 = end), node->0xC (12) next, node->
 * 0x10 (16) s32 state (must be 1 / runnable), node->0x12 (18) u16
 * flags (bit 2 / 0x4 cleared here = clear-pending-break), node->
 * 0x14 (20) thread id, node->0x11C (284) = a programmable break
 * value. Returns -2 (no such thread) / -4 (wrong state). Programs
 * the RCP/CPU breakpoint via func_80006A50/func_80006A98 +
 * __rmonRcpAtBreak, then __rmonSendHeader (func_800073F8). MATCHED
 * byte-exact: cmd/var_s0/var_s1 pinned to s2/s0/s1 via register
 * hints + decl-order (buf/header/sp94 layout), shared SendHeader
 * epilogue (case 0 -> var_s1=1 -> wake), loop compare operand-order
 * (sp94->0xC != node->0x14) fixed temp-register numbering. */
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
#ifndef FHU
#define FHU(p, o) (*(u16 *)((char *)(p) + (o)))
#endif
extern void func_80006A50(s32, s32);
extern s32 func_80006A98(s32);
extern s32 func_8000898C(s32, s32, s32);
extern void func_80008498(void);
extern void func_800084AC(void);
extern void func_80008D0C(void *);
extern s32 func_80008C48(s32, s32);
extern char *func_80009C30(void);
extern void func_8000A110(void *);
extern u8 __rmonRcpAtBreak;
/* rmon command dispatch on arg0->unk9. case 0: resume a thread - find it in the
 * chain by id (unk14==arg0->unkC), require it stopped (unk10==1), clear its
 * run-flags (unk12 &= ~3), optionally set the resume PC (unk11C) / validate via
 * func_80008C48, ack (0x10 header), wake it (func_8000A110), return 1. case 1:
 * RCP single-step - arm/disarm the RCP break (func_80006A50 / func_8000898C /
 * __rmonRcpAtBreak), ack, and if stepping set the temp break
 * (func_80007A98 -> func_80008D0C -> 0x4C reply). default: -4. */
s32 func_80007B3C(void *arg0) {
    extern s32 func_80008430();
    extern void func_80007A98();
    extern void func_800073F8();
    void *sp94 = arg0;
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } sp84;
    u8 sp38[0x4C];
    register void *var_s0;
    register s32 var_s1;

    var_s1 = 0;
    switch (*(u8 *)((char *) arg0 + 9)) {
    case 0:
        var_s0 = (void *) func_80009C30();
        if (FW(var_s0, 4) != -1) {
loop_4:
            if (FW(sp94, 0xC) != FW(var_s0, 0x14)) {
                var_s0 = (void *) FW(var_s0, 0xC);
                if (FW(var_s0, 4) != -1) {
                    goto loop_4;
                }
            }
        }
        if (FW(var_s0, 4) == -1) {
            return -2;
        }
        if (FHU(var_s0, 0x10) != 1) {
            return -4;
        }
        FHU(var_s0, 0x12) = FHU(var_s0, 0x12) & ~3;
        if (FW(sp94, 0x10) & 2) {
            FW(var_s0, 0x11C) = FW(sp94, 0x14);
        }
        if ((FW(sp94, 0x10) & 1) && (func_80008C48(FW(sp94, 0xC), FW(var_s0, 0x11C)) == 0)) {
            return -4;
        }
        var_s1 = 1;
        break;
    case 1:
        if (func_80008430() != 0) {
            return -4;
        }
        if (FW(sp94, 0x10) & 2) {
            func_80006A50(0x04080000, FW(sp94, 0x14) + 0xFBFFF000);
        }
        if (FW(sp94, 0x10) & 1) {
            if (!(func_8000898C(1, 0x3E8, func_80006A98(0x04080000) + 0x04001000) & 3)) {
                func_80008498();
            }
            func_80008498();
            __rmonRcpAtBreak = 1;
        } else {
            __rmonRcpAtBreak = 0;
            func_800084AC();
        }
        sp84.tag = *(u8 *)((char *) sp94 + 4);
        sp84.zero = 0;
        sp84.id = FW(sp94, 0xC);
        func_800073F8(&sp84, 0x10, 1);
        if (FW(sp94, 0x10) & 1) {
            func_80007A98(1, 0x3E8, sp38);
            func_80008D0C(sp38);
            func_800073F8(sp38, 0x4C, 2);
        }
        return 0;
    default:
        return -4;
    }

    sp84.tag = *(u8 *)((char *) sp94 + 4);
    sp84.zero = 0;
    sp84.id = FW(sp94, 0xC);
    func_800073F8(&sp84, 0x10, 1);
    if (var_s1 != 0) {
        func_8000A110(var_s0);
    }
    return 1;
}
