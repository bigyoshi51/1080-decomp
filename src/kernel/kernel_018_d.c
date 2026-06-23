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
    register s32 phantom;
    s32 sp20;

    D_8001B7D0 = 0;
    rmonmain_bss_0469 = 0;
    rmonmain_bss_0468 = 0;
    func_800082EC();
    D_8000A580 = 1;
    rmonmain_bss_046C = 0;
    rmonmain_bss_0470 = &rmonmain_bss_0008;
    phantom = 0;
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
