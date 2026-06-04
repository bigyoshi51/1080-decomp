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

/* func_800066EC: 1-insn (`or $a3, $a2, $0`) alias entry point that falls
 * through into func_800066F0 (split out to kernel_048.c, -O1). Callers
 * either jal func_800066EC (which copies a2→a3 then enters 66F0's body)
 * or jal func_800066F0 (which uses $a3 directly). Cross-function alias
 * entry — not reproducible from standalone C; INCLUDE_ASM stays. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800066EC);

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
 * 4 callees. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
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
    char *volatile sp2C = &__rmonUtilityBuffer;
    void *volatile sp30 = arg0;
    s32 sp34;
    s32 sp38;
    s32 var_s0;
    s32 var_s1;
    u32 temp_t0;
    u32 temp_t4;
    u32 addr;
    char *p;

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
        temp_t0 = FW(sp30, 0x10);
        if ((temp_t0 < 0x04001000U) || ((u32) (temp_t0 + FW(sp30, 0x14)) >= 0x04002000U)) {
            var_s0 = 0;
        } else {
            var_s0 = 1;
        }
        if (var_s0 == 0) {
            temp_t4 = FW(sp30, 0x10);
            if ((temp_t4 < 0x04000000U) || ((u32) (temp_t4 + FW(sp30, 0x14)) >= 0x04001000U)) {
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
    p = (char *) &sp34;
    sp38 = 0;
    sp34 = FW(sp30, 0x14) + 0x10;
    do {
        sp38 += func_800066F0(p + sp38, 4 - sp38, 8);
    } while (sp38 < 4);
    __rmonSendHeader(sp2C, 0x10, 1);
    func_800074A0(addr, FW(sp30, 0x14));
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
/* rmon memory-write command handler (write sibling of func_80006790). Validate
 * the RDRAM address (func_80004B30) / length (<=0x400). For an SP-window address
 * (0x04000000..0x05000000): unaligned single-byte/halfword -> read-modify-write
 * via func_80006A98/func_80006A50; aligned -> word-loop via func_80006A50. Else
 * (general RAM) bulk-write via func_80006AEC. Then send the 0x10 reply header. */
s32 func_8000698C(void *arg0) {
    extern void func_800073F8();
    extern void func_80006A50();
    extern void func_80006AEC();
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    s32 *sp24;
    s32 temp_a1;
    s32 temp_t4;
    s32 var_s1;
    s32 var_t2;

    if ((*(u8 *)((char *) arg0 + 9) == 0) && (func_80004B30(FW(arg0, 0x10)) == -1)) {
        return -5;
    }
    if ((u32) FW(arg0, 0x14) >= 0x401U) {
        return -8;
    }
    if (((u32) FW(arg0, 0x10) < 0x04000000U) || ((u32) (FW(arg0, 0x10) + FW(arg0, 0x14)) >= 0x05000000U)) {
        var_s1 = 0;
    } else {
        var_s1 = 1;
    }
    if (var_s1 != 0) {
        temp_t4 = FW(arg0, 0x10) & 3;
        sp30 = temp_t4;
        if (temp_t4 != 0) {
            if (FW(arg0, 0x14) != 1) {
                return -5;
            }
            sp2C = func_80006A98(FW(arg0, 0x10) & ~3);
            if (sp30 == 1) {
                var_t2 = (FW(arg0, 0x18) << 0x10) | (sp2C & 0xFF00FFFF);
                goto block_18;
            }
            if (sp30 == 2) {
                sp2C = (FW(arg0, 0x18) << 8) | (sp2C & 0xFFFF00FF);
            } else {
                var_t2 = FW(arg0, 0x18) | (sp2C & ~0xFF);
block_18:
                sp2C = var_t2;
            }
            func_80006A50(FW(arg0, 0x10) & ~3, sp2C);
            goto block_26;
        }
        sp24 = (s32 *)((char *) arg0 + 0x18);
        sp28 = (u32) FW(arg0, 0x14) >> 2;
        if (FW(arg0, 0x14) & 3) {
            return -5;
        }
        sp28 -= 1;
        if (sp28 != 0) {
            do {
                temp_a1 = *sp24;
                sp24 += 1;
                func_80006A50(FW(arg0, 0x10), temp_a1);
                FW(arg0, 0x10) = FW(arg0, 0x10) + 4;
                sp28 -= 1;
            } while (sp28 != 0);
        }
        goto block_26;
    }
    func_80006AEC(FW(arg0, 0x10), (char *) arg0 + 0x18, FW(arg0, 0x14));
block_26:
    sp34.zero = 0;
    sp34.tag = *(u8 *)((char *) arg0 + 4);
    sp34.id = FW(arg0, 0xC);
    func_800073F8(&sp34, 0x10, 1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000698C);
#endif








/* __rmonWriteWordTo (unimplemented stub) */
s32 func_80006C58(s32 arg0) {
    return -1;
}








/* func_800070A0 - verified structural decode (kernel, 0x120, 72
 * insns, memory-dump / word-stream transmit; rmon-family helper).
 * Struct-typing reference: addr/len are a raw memory range; the
 * routine streams ceil(len/4) 32-bit words out via func_80005584
 * (send-one-word). Addresses in [0x04000000, 0x05000000) are the
 * N64 cartridge/PI domain (not CPU-load-safe), so those words are
 * fetched with func_80008FB0 (PI/DMA read into a stack tmp);
 * everything else is a direct lw. A misaligned base forces every
 * word through func_80006AEC (unaligned 4-byte read). func_80005534
 * = end-of-stream flush. (Same rmon memory-inspect family as
 * func_80009584 / the __rmon* handlers.) Caps <80: alignment
 * branch + cart-range sltu check + 4 callees + decrement loop with
 * spilled counter/cursor at sp+0x30/0x34. INCLUDE_ASM remains build
 * path (no episode; tautology-trap rule).
 * 2026-05-28 opt-level probe (NEGATIVE): the entry double arg-home-spill
 * (sw a1;lw / sw a0;lw) + stack-spilled loop vars look like an -O1/-g
 * marker, but building this TU at -O1 is WORSE (7% raw vs -O2's 15%); -O2
 * is correct. The gap is loop-STRUCTURE (the goto-based aligned/cart/
 * misaligned three-way control flow + stack-resident n/addr), not opt
 * level. Improving it needs a structural C rewrite to mirror the target's
 * exact basic-block layout — not an opt-flag or file-split. */
#ifdef NON_MATCHING
extern void func_80006AEC(void *dst, void *src, int n);
extern void func_80005584(int word);
extern void func_80008FB0(void *src, void *dst);
extern void func_80005534(void);
/* rmon word-streamer: write len bytes (word at a time) via func_80005584,
 * routing SP-range addresses through func_80008FB0. 2026-06-04 (49.6->84.0%,
 * -O1): two structural fixes — (1) the aligned path must be the if-BODY
 * (`if (!(addr&3))`) so IDO inlines it and emits `bnez addr&3 -> unaligned`
 * matching the target's arm order (+24pp); (2) the SP-range test needs BOTH
 * bounds `0x04000000 <= addr < 0x05000000` (the upper `lui 0x500; sltu` is
 * real). Residual ~16% is the -O1 frame-size (8 bytes smaller than target =
 * a spill the target keeps) + loop-counter RA. */
void func_800070A0(char *addr, int len) {
    unsigned int n = ((unsigned int)len + 3) >> 2;
    int tmp;
    if (!((unsigned int)addr & 3)) {
        while (n--) {
            if ((unsigned int)addr >= 0x04000000U && (unsigned int)addr < 0x05000000U) {
                func_80008FB0(addr, &tmp);
                func_80005584(tmp);
            } else {
                func_80005584(*(int*)addr);
            }
            addr += 4;
        }
    } else {
        while (n--) {
            func_80006AEC(&tmp, addr, 4);
            func_80005584(tmp);
            addr += 4;
        }
    }
    func_80005534();
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);
#endif

#ifdef NON_MATCHING
extern void func_800082EC(void);
extern void func_80008E08(void);
extern void func_80008E38(void);
extern void func_80008EA0(void);
extern volatile s32 D_8001B7D0;
extern s32 D_8000A580;
extern s8 rmonmain_bss_0468;
extern s8 rmonmain_bss_0469;
extern s32 rmonmain_bss_046C;
extern void *rmonmain_bss_0470;
extern s32 rmonmain_bss_0008;
extern s32 __rmonMQ;
/* rmon main dispatch loop (__rmonIOhandler-class). Init state, then loop
 * forever: recv a flag word from __rmonMQ, OR it into D_8001B7D0, and dispatch
 * each set bit (2 -> func_80008E08, 4 -> func_80008E38, 8 -> func_80008EA0,
 * 0x10 -> just clear), clearing the bit as it goes; bit 0x20 is a one-shot
 * (clear and continue), otherwise re-loop. */
void func_800071C0(void) {
    s32 sp20;

    D_8001B7D0 = 0;
    rmonmain_bss_0469 = 0;
    rmonmain_bss_0468 = 0;
    func_800082EC();
    D_8000A580 = 1;
    rmonmain_bss_046C = 0;
    rmonmain_bss_0470 = &rmonmain_bss_0008;
loop_1:
    func_80004FE0(&__rmonMQ, &sp20, 1);
    D_8001B7D0 |= sp20;
    if (D_8001B7D0 & 2) {
        D_8001B7D0 &= ~2;
        func_80008E08();
    }
    if (D_8001B7D0 & 4) {
        D_8001B7D0 &= ~4;
        func_80008E38();
    }
    if (D_8001B7D0 & 8) {
        D_8001B7D0 &= ~8;
        func_80008EA0();
    }
    if (D_8001B7D0 & 0x10) {
        D_8001B7D0;
        D_8001B7D0 &= 0xEF;
    }
    if (!(D_8001B7D0 & 0x20)) {
        goto loop_1;
    }
    D_8001B7D0;
    D_8001B7D0 &= 0xDF;
    goto loop_1;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);
#endif





#ifdef NON_MATCHING
/* func_800073F8 is the body fragment of the original 31-insn function
 * at ROM 0x800073DC, which splat split into:
 *   - func_800073DC (kernel_036.c orphan stub, 7 insns / 0x1C — prologue + first jal)
 *   - func_800073F8 (this file, 25 insns / 0x64 — body + epilogue)
 *
 * The full decompiled body lives in kernel_036.c as `__rmonSendHeader`
 * (matched 100% per report.json) — that is the canonical source-of-truth
 * for these bytes. The INCLUDE_ASM below is residual dead duplicate code
 * emitted at a separate .o offset; removing it would shift downstream .o
 * layout so it stays for now.
 *
 * Stub body documents the fragment relationship for grep discoverability;
 * not a real decode. See feedback_orphan_include_asm_after_split_function_decomp.md.
 *
 * EXTERNAL CALLERS BEWARE: kernel_015.c / kernel_018.c / kernel_029.c /
 * kernel_032.c declare `extern void func_800073F8(void*, s32, s32)` and
 * call it as a 3-arg function. At link time those resolve to address
 * 0x800073F8 (THIS orphan stub's address), NOT to __rmonSendHeader's
 * unified body. So the runtime semantics are: caller's args land in
 * $a0/$a1/$a2, but THIS body uses $t6 from the predecessor's tail
 * (which external callers don't set). Likely an in-the-original
 * "shared-tail entry point" that the decomp can't represent cleanly. */
void func_800073F8(void) {
    /* see __rmonSendHeader in kernel_036.c — this fragment is its body */
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800073F8);
#endif


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
 * nested if/else with one tail. RESIDUAL (regalloc tail, multi-tick): the
 * target spills &__rmonUtilityBuffer to 0x28(sp) at entry and RELOADS it
 * per use (9x) + spills/reloads the arg (sw a0,0x30(sp); lw s0,0x30(sp)),
 * frame -0x30; my C keeps ub register-resident (frame -0x18). Sibling
 * func_80006790 hits this reload-per-use shape at plain -O2 (68%), so it
 * is structure-driven not opt-driven — kernel_018 -O2 -g3 only nudges 7564
 * +0.8pp and REGRESSES 6790/71C0/745C, so NOT an opt split. */
#ifdef NON_MATCHING
extern char __rmonUtilityBuffer;
extern char *func_80009C30(void);
/* func_800073F8 is forward-declared 0-arg above (fragment stub); cast at
 * call site to its real 3-arg __rmonSendHeader signature. */
s32 func_80007564(char *msg) {
    char *ub = &__rmonUtilityBuffer;
    char *t;
    if (*(int*)(msg + 0xC) == -1) {
        *(int*)(ub + 0xC) = 0x3EA;
    } else {
        *(int*)(ub + 0xC) = *(int*)(msg + 0xC);
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
    *(unsigned char*)(ub + 0x4) = *(unsigned char*)(msg + 0x4);
    *(unsigned short*)(ub + 0x6) = 0;
    ((void (*)(void*, int, int))func_800073F8)(ub, *(unsigned short*)(ub + 0x10) * 4 + 0x14, 1);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);
#endif

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
 * unk12-flag tail. (Unblocked by adding an alabel for m2c parsing.) */
s32 func_80007698(s32 arg0, s32 arg1, void *arg2) {
    extern s32 func_80008430();
    s32 sp1C;
    void *sp18;
    u16 temp_t0;

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
    temp_t0 = HW(sp18, 0x10);
    if (temp_t0 != 0) {
        FW(arg2, 0xC) = temp_t0;
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
 * __rmonRcpAtBreak, then __rmonSendHeader (func_800073F8). Caps
 * <80: command switch + thread-chain walk + flag RMW + ~9 rmon/
 * MMIO callees + branch-likely. Full body INCLUDE_ASM-preserved
 * (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap
 * rule). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern void func_80006A50(s32, s32);
extern s32 func_8000898C(s32, s32, s32);
extern void func_800084AC(void);
extern void func_80008D0C(void *);
extern s32 func_80008C48(s32, s32);
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
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } sp84;
    u8 sp38[0x4C];
    void *volatile sp94 = arg0;
    void *var_s0;

    switch (*(u8 *)((char *) arg0 + 9)) {
    case 0:
        var_s0 = (void *) func_80009C30();
        if (FW(var_s0, 4) != -1) {
loop_4:
            if (FW(var_s0, 0x14) != FW(sp94, 0xC)) {
                var_s0 = (void *) FW(var_s0, 0xC);
                if (FW(var_s0, 4) != -1) {
                    goto loop_4;
                }
            }
        }
        if (FW(var_s0, 4) == -1) {
            return -2;
        }
        if (FW(var_s0, 0x10) != 1) {
            return -4;
        }
        *(u16 *)((char *) var_s0 + 0x12) = *(u16 *)((char *) var_s0 + 0x12) & ~3;
        if (FW(sp94, 0x10) & 2) {
            FW(var_s0, 0x11C) = FW(sp94, 0x14);
        }
        if ((FW(sp94, 0x10) & 1) && (func_80008C48(FW(sp94, 0xC), FW(var_s0, 0x11C)) == 0)) {
            return -4;
        }
        sp84.zero = 0;
        sp84.tag = *(u8 *)((char *) sp94 + 4);
        sp84.id = FW(sp94, 0xC);
        func_800073F8(&sp84, 0x10, 1);
        func_8000A110(var_s0);
        return 1;
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
        sp84.zero = 0;
        sp84.tag = *(u8 *)((char *) sp94 + 4);
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
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);
#endif
