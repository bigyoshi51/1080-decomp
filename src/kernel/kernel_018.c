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
INCLUDE_ASM("asm/nonmatchings/kernel", func_80006790);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000698C);








/* __rmonWriteWordTo (unimplemented stub) */
s32 func_80006C58(s32 arg0) {
    return -1;
}








/* func_800070A0 - verified structural decode (kernel, 0x120, 72
 * insns, memory-dump / word-stream transmit; rmon-family helper).
 *   void func_800070A0(char *addr, int len) {
 *       u32 n = (len + 3) >> 2;                   // word count
 *       if ((u32)addr & 3) {                      // misaligned base
 *           while (n--) {
 *               func_80006AEC(&tmp, addr, 4);     // unaligned read
 *               func_80005584(tmp);               // send word
 *               addr += 4;
 *           }
 *       } else {                                  // aligned base
 *           while (n--) {
 *               if ((u32)addr >= 0x04000000 &&
 *                   (u32)addr <  0x05000000) {    // cart/PI region
 *                   func_80008FB0(addr, &tmp);    // DMA read
 *                   func_80005584(tmp);
 *               } else {
 *                   func_80005584(*(int*)addr);   // direct read
 *               }
 *               addr += 4;
 *           }
 *       }
 *       func_80005534();                          // flush/finalize
 *   }
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
 * spilled counter/cursor at sp+0x30/0x34. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800070A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800071C0);





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

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000745C);

/* func_80007564 - verified structural decode (kernel, 0x134, rmon
 * thread-list command handler). rmon family (cf. func_8000798C /
 * func_80009584 / func_80007A98; libreultra rmon).
 *   s32 func_80007564(RmonMsg *msg) {
 *       UB *ub = &__rmonUtilityBuffer;
 *       if (msg->0xC == -1) { ub->0xC = 0x3EA; goto send; }
 *       ub->0xC = msg->0xC;
 *       if (msg->0x9 == 1) {                      // single-target
 *           ub->0x10 = 1;                         // count
 *           ub->0x14 = 0x3E8;                     // one entry
 *           goto send;
 *       }
 *       t = func_80009C30();                      // thread-list head
 *       ub->0x10 = 0;
 *       if (t->0x4 == -1) goto send;              // empty list
 *       if (t->0x14 != 0) {
 *           do {                                  // walk chain
 *               ub->0x14[ub->0x10] = t->0x14;     // append id
 *               ub->0x10++;
 *               t = t->0xC;                       // next
 *           } while (t->0x4 != -1);
 *       }
 *       ub->0x4 = (u8)msg->0x4;                    // domain
 *       ub->0x6 = 0;
 *   send:
 *       func_800073F8(ub, ub->0x10 * 4 + 0x14, 1);// __rmonSendHeader
 *       return 0;
 *   }
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
 * __rmonSendHeader. Full body INCLUDE_ASM-preserved (.s = source
 * of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007564);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007698);








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
INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);
