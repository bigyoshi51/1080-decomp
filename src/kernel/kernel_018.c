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

INCLUDE_ASM("asm/nonmatchings/kernel", func_80007B3C);
