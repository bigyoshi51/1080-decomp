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


/* func_800066F0 split out to kernel_048.c (-O1) */

/* func_80006720 split out to kernel_049.c (-O1) */

/* func_80006754 split out to kernel_047.c (-O1) */

/* func_80006790 - verified structural decode (kernel, 0x1FC, 127
 * insns, rmon memory-read command handler). rmon family (cf.
 * func_80009584 / func_80007564; __rmonUtilityBuffer /
 * __rmonSendHeader).
 *   s32 func_80006790(RmonMsg *msg) {
 *       UB *ub = &__rmonUtilityBuffer;
 *       ub->0x4 = msg->0x4;                       // domain
 *       ub->0xC = msg->0xC;                       // type/id echo
 *       ub->0x6 = 0;
 *       if (msg->0x10 == -1)       return -5;     // bad address
 *       if (msg->0x14 >= 0x401)    return -8;     // len > 1024
 *       if (msg->0x9 == 1)                        // RSP IMEM win
 *           ok = msg->0x10 >= 0x04001000 &&
 *                msg->0x10 + msg->0x14 < 0x04002000;
 *       else                                       // RSP DMEM win
 *           ok = msg->0x10 >= 0x04000000 &&
 *                msg->0x10 + msg->0x14 < 0x04001000;
 *       if (ok) {
 *           phys = osVirtualToPhysical(msg->0x10);// func_80004B30
 *           func_800074A0(phys, ...);             // PI read
 *           func_800066F0(ub->payload, ..., n);   // copy out
 *       }
 *       __rmonSendHeader(ub, len, flag);          // ship reply
 *       return 0;
 *   }
 * Struct-typing reference: RmonMsg msg - msg->0x4 (4) u8 domain,
 * msg->0x9 (9) u8 mode (1 = RSP IMEM 0x04001000..0x04002000 else
 * DMEM 0x04000000..0x04001000), msg->0xC (12) type/id, msg->0x10
 * (16) target address (-1 = invalid), msg->0x14 (20) byte length
 * (must be < 0x401 / 1024). __rmonUtilityBuffer: ->0x4 domain,
 * ->0x6 (6) u16 cleared, ->0xC status/echo. func_80004B30 =
 * osVirtualToPhysical, func_800074A0 = PI/cart IO read,
 * func_800066F0 = bounded copy, __rmonSendHeader = the shared rmon
 * emit. The RSP DMEM/IMEM range gate prevents reads outside the
 * SP memory window. Caps <80: rmon buffer build + multi-range
 * sltu validation + osVirtualToPhysical/PI-read + branch-likely +
 * 4 callees. MATCHED byte-exact (agent-b 2026-06-23): -O1, register
 * flags var_s0/var_s1 -> s0/s1 (loop accumulator reuses s0), decl
 * order pins the stack-slot layout (frame 0x40), and the SP-range
 * `len + addr` summands plus `sp34 = len+0x10` ordered before `p =
 * &sp34` fix the addu commutativity + token-loop scheduling. */
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern void __rmonSendHeader(void *, s32, s32);
extern s32 func_80004B30(u32);
extern s32 func_800066F0(void *, s32, s32);
extern void func_800074A0(u32, u32);
extern char __rmonUtilityBuffer;
/* rmon read-memory request handler. Stamp the reply header (__rmonUtilityBuffer:
 * tag=req->unk4, unkC=req->unkC, unk6=0). Reject a -1 address (-5) or a length
 * over 0x400 (-8). For an instruction-space read (req->unk9==1) require the range
 * to lie wholly within SP IMEM (0x04001000..0x04002000) or SP DMEM
 * (0x04000000..0x04001000) else -5; otherwise validate the RDRAM address via
 * func_80004B30. Then set the reply length (len+0x10), poll 4 bytes of the read
 * token (func_800066F0), send the header, and kick the transfer
 * (func_800074A0(addr, len)). */
s32 func_80006790(void *arg0) {
    char *p;
    s32 sp38;
    s32 sp34;
    void *sp30 = arg0;
    char *sp2C = &__rmonUtilityBuffer;
    u32 addr;
    register s32 var_s0;
    register s32 var_s1;

    *(u8 *)(sp2C + 4) = *(u8 *)((char *)arg0 + 4);
    FW(sp2C, 0xC) = FW(sp30, 0xC);
    *(s16 *)(sp2C + 6) = 0;
    if ((u32) FW(sp30, 0x10) == 0xFFFFFFFFU) {
        return -5;
    }
    if ((u32) FW(sp30, 0x14) >= 0x401U) {
        return -8;
    }
    if (*(u8 *)((char *)arg0 + 9) == 1) {
        if (((u32) FW(sp30, 0x10) < 0x04001000U) || ((u32) (FW(sp30, 0x14) + FW(sp30, 0x10)) >= 0x04002000U)) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if (var_s0 == 0) {
            if (((u32) FW(sp30, 0x10) < 0x04000000U) || ((u32) (FW(sp30, 0x14) + FW(sp30, 0x10)) >= 0x04001000U)) {
                var_s1 = 0;
            } else {
                var_s1 = 1;
            }
            if (var_s1 == 0) {
                return -5;
            }
        }
    } else {
        if (func_80004B30(FW(sp30, 0x10)) == -1) {
            return -5;
        }
    }
    addr = FW(sp30, 0x10);
    FW(sp2C, 0) = FW(sp30, 0x14) + 0x10;
    sp34 = FW(sp30, 0x14) + 0x10;
    p = (char *) &sp34;
    sp38 = 0;
    do {
        var_s0 = func_800066F0(p + sp38, 4 - sp38, 8);
        sp38 += var_s0;
    } while (sp38 < 4);
    __rmonSendHeader(sp2C, 0x10, 1);
    func_800074A0(addr, FW(sp30, 0x14));
    return 0;
}

#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
/* rmon memory-write command handler (write sibling of func_80006790). Validate
 * the RDRAM address (func_80004B30) / length (<=0x400). For an SP-window address
 * (0x04000000..0x05000000): unaligned single-byte write -> read-modify-write
 * via func_80006A98/func_80006A50 (the byte-merge is an if/else-if/else CHAIN
 * on the misalignment 1/2/else); aligned -> word-loop via func_80006A50. Else
 * (general RAM) bulk-write via func_80006AEC. Then send the 0x10 reply header.
 *
 * MATCHED byte-exact 147/147 (agent-f 2026-07-10): IDO 5.3 -O1 donor
 * (kernel_018_b_ido53_698C.c, REPLACE_FUNC_BODY splice) — 5th
 * 5.3-vs-7.1 temp-rematerialization crack. The old "coloring/frame-layout
 * cap" note fell to four levers: else-if chain structure, first byte-read
 * through the RAW param (keeps the deferred `or s0,t6` commit), register-var
 * DEAD HOME SLOTS in decl order (`register arg0` first = home 0x44,
 * `register var_s1` last = home 0x20 -> frame 0x48 with struct at 0x34),
 * and order ties (sp28-before-sp24 init, len-first range sum, tail
 * tag->zero->id). See the donor file header for the full mechanism. */
extern void func_80006A50(s32, s32);
extern void func_80006AEC(s32, void *, s32);
extern void func_800073F8(void *, s32, s32);

s32 func_8000698C(void *sp48) {
    register void *arg0;
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    s32 *sp24;
    register s32 var_s1;

    arg0 = sp48;
    if ((*(u8 *)((char *) sp48 + 9) == 0) && (func_80004B30(FW(arg0, 0x10)) == -1)) {
        return -5;
    }
    if ((u32) FW(arg0, 0x14) >= 0x401U) {
        return -8;
    }
    if (((u32) FW(arg0, 0x10) < 0x04000000U) || ((u32) (FW(arg0, 0x14) + FW(arg0, 0x10)) >= 0x05000000U)) {
        var_s1 = 0;
    } else {
        var_s1 = 1;
    }
    if (var_s1 != 0) {
        sp30 = FW(arg0, 0x10) & 3;
        if (sp30 != 0) {
            if (FW(arg0, 0x14) != 1) {
                return -5;
            }
            sp2C = func_80006A98(FW(arg0, 0x10) & ~3);
            if (sp30 == 1) {
                sp2C = (*(u8 *)((char *) arg0 + 0x18) << 0x10) | (sp2C & 0xFF00FFFF);
            } else if (sp30 == 2) {
                sp2C = (*(u8 *)((char *) arg0 + 0x18) << 8) | (sp2C & 0xFFFF00FF);
            } else {
                sp2C = *(u8 *)((char *) arg0 + 0x18) | (sp2C & ~0xFF);
            }
            func_80006A50(FW(arg0, 0x10) & ~3, sp2C);
            goto block_26;
        }
        sp28 = (u32) FW(arg0, 0x14) >> 2;
        sp24 = (s32 *)((char *) arg0 + 0x18);
        if (FW(arg0, 0x14) & 3) {
            return -5;
        }
        var_s1 = sp28;
        sp28 -= 1;
        if (var_s1 != 0) {
            do {
                func_80006A50(FW(arg0, 0x10), *sp24++);
                FW(arg0, 0x10) = FW(arg0, 0x10) + 4;
                var_s1 = sp28;
                sp28 -= 1;
            } while (var_s1 != 0);
        }
        goto block_26;
    }
    func_80006AEC(FW(arg0, 0x10), (char *) arg0 + 0x18, FW(arg0, 0x14));
block_26:
    sp34.tag = *(u8 *)((char *) arg0 + 4);
    sp34.zero = 0;
    sp34.id = FW(arg0, 0xC);
    func_800073F8(&sp34, 0x10, 1);
    return 0;
}
