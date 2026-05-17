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



INCLUDE_ASM("asm/nonmatchings/kernel", func_80008454);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008498);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084AC);

/* func_800084D0 (size 0xBC, was 0xAC): merged in former func_8000857C
 * fragment (4-insn epilogue at 0x8000857C — `lw $s0,0x14(sp); lw $s1,0x18(sp);
 * jr $ra; addiu $sp,+0x48`). func_8000857C was the natural tail of
 * func_800084D0 (its body ends at 0x80008578 with `lw $ra, 0x1C(sp)`).
 * Several callers — func_80008A08 etc — `jal 0x8000857C` directly to reuse
 * the restore-saved-regs+sp-pop+return sequence (cross-function shared-tail
 * entry, same pattern as func_80006640 → func_800065F0). The address is
 * re-exported via undefined_syms_auto.txt for those callers. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800084D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);

/* Classifies a MIPS instruction: returns 1 if J/JAL/JR/JALR, else 0.
 * NON_MATCHING: IDO picks $v0 for opcode register; target uses $a1.
 * Logic identical, 37 insts, register allocation differs. */
#ifdef NON_MATCHING
s32 func_800087B4(u32 inst) {
    u32 opcode = (inst >> 26) & 0x3F;
    if (opcode == 0) {
        if (((inst >> 5) & 0x7FFF) == 0 && (inst & 0x3F) == 8) return 1;
        if (((inst >> 16) & 0x1F) == 0 && (inst & 0x7FF) == 9) return 1;
        return 0;
    }
    if (opcode == 2 || opcode == 3) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800087B4);
#endif


/* func_8000894C split out to kernel_054.c (-O1) */


void func_80008A08(void) {
    func_8000857C();
    func_8000785C(0);
    func_80008ED0();
}



void func_80008AA0(void) {
    func_80007760();
    func_8000785C(0);
    func_80008ED0();
}







/* func_80008C30 - verified structural decode (0x118, jr-count 2).
 * BUNDLE: this .s holds TWO functions splat couldn't separate -
 * func_80008C30 (~33 insns, ends at the first jr ra) plus an
 * unnamed sibling at ~0x80008CB4 (its own `addiu sp,-0x20`
 * prologue, no glabel). Next real symbol is func_80008D4C. Needs
 * scripts/split-fragments.py to introduce the mid boundary before
 * either can be C-matched; harmless for the INCLUDE_ASM build
 * (bytes are bytes). Deferred (mid-bundle split is address-fragile
 * under a 60s loop tick; do it in a focused pass).
 *   void func_80008C30(int a0, int a1) {        // a0 sp20, a1 sp24
 *       u8 cmd[4] = {0};                          // sp+0x1C
 *       s32 x = (a0 << 26) >> 26;                 // sign-ext 6-bit
 *       s32 y = (a1 << 27) >> 27;                 // sign-ext 5-bit
 *       cmd[0] = (cmd[0] & 0x03) | ((x << 2) & 0xFC);
 *       cmd[1] = (cmd[1] & 0xE0) | (y & 0x1F);
 *       func_80006A50(0x40010000, *(int*)cmd);    // submit word
 *       func_80006A50(0x40800000, 0);             // kick/commit
 *   }
 *   // bundled sibling: same shape but packs a 3rd 6-bit field into
 *   // cmd[2] (mask 0x07, sets bit 0x20) before the same submit.
 * Struct-typing reference: a0/a1 carry small signed bitfields (6-bit
 * x from a0, 5-bit y from a1) packed into a stack command struct
 * (byte 0: bits 2-7 = x<<2, byte 1: bits 0-4 = y; sibling adds byte
 * 2: bits 0-2 = z|0x20). func_80006A50(addr, val) = an MMIO/command
 * submit helper; 0x40010000 / 0x40800000 are the command + kick
 * register addresses (RSP/RDP-style command emit). Caps <80:
 * 2-function bundle (boundary) + bitfield sll/sra/andi/or pack +
 * func_80006A50 calls. Full body INCLUDE_ASM-preserved (.s =
 * source of truth). INCLUDE_ASM (no episode; tautology-trap rule +
 * unresolved bundle boundary). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C30);





/* func_80008E98 / _EA0 / _ED0 / _FB0: 86-insn alt-entry rmon packet
 * builder spanning 0x80008E98-0x80008FF0 (size 0x158). Splat split into 4
 * .s files because of the alt-entry symbol at 0x80008EA0 (called by
 * func_800071C0 via `jal 0x80008EA0`). The 0x80008E98 entry adds 2-insn
 * prelude (addiu $sp, -0xD8; sw $a0, 0xD8($sp)) before falling into the
 * shared body at 0x80008EA0; the 0x80008EA0 entry expects the caller to
 * have done the frame setup itself (caller `func_800071C0` does so).
 *
 * Body shape (rmon packet builder pattern, see docs/IDO_CODEGEN.md for
 * "rmon packet builder pattern" and CLAUDE.md notes):
 *   s0 = (RmonMsg*)msg                  // reloaded from sp+0xD8 spill
 *   pkt[0xC] = s0->[0xC]                // dword field copy
 *   pkt[0x36] = (short)0
 *   pkt[0x34] = s0->[0x4]               // byte field
 *   if (s0->[0x9] != 0) goto .L80008FC4  // skip-call path
 *   ...continues in func_80008ED0 with jal func_800077DC + branch logic
 *   ...continues in func_80008FB0 with sub-packet field copy from
 *      caller's stack frame at sp+0x2C
 *   ...ends at jr $ra at 0x80008FEC, frame teardown at 0x80008FE0-FE8
 *
 * Multi-tick decomp target (alt-entry + likely -O1 file-split).
 *
 * 2026-05-06 PROGRESS: 4-fragment merge applied. The previous 4 .s files
 * (E98/EA0/ED0/FB0) are now consolidated into one 0x15C func_80008E98.s
 * with three `alabel`s (EA0 at offset 0x8, ED0 at 0x38, FB0 at 0x118)
 * preserving cross-callers' jal targets. expected/.o regenerated.
 * The merge unblocks future C decode — splat-boundary issues no longer
 * apply, and the function can be NM-wrapped or matched normally now.
 *
 * Remaining work:
 *   1. Type a RmonMsg / RmonHdr struct pair
 *   2. File-split into kernel_NNN.c with -O1 OPT_FLAGS override + linker
 *      script slot insertion
 *   3. Write C body using rmon packet builder pattern from
 *      docs/IDO_CODEGEN.md
 *   4. Optional: PROLOGUE_STEALS for the EA0 alt-entry (caller
 *      `func_800071C0` jumps into +0x8 expecting frame already set up;
 *      C-only emit duplicates the prologue at the symbol address)
 *
 * Default INCLUDE_ASM build remains byte-exact. */
/* 4-fragment merge complete: func_80008E98 + func_80008EA0 (alt-entry at +8)
 * + func_80008ED0 + func_80008FB0 -> single 0x15C (87-insn) function.
 * func_80008EA0 is preserved as `alabel` inside the merged .s, keeping the
 * alt-entry callable from func_800071C0. ED0 and FB0 .s files deleted. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008E98);

/* func_80008FF4 absorbed the former func_80009000 + func_80009030
 * (splat mis-split: 8FF4 was prologue-only, 9000 and 9030 shared the
 * same frame with 8FF4). Now one 0x150 function. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008FF4);

/* func_80009148 split out to kernel_054.c (-O1, absorbed func_800091F0 fragment) */

/* func_800091F0 merged into func_80009148 */

/* func_800091FC split out to kernel_054.c (-O1) */

/* rmon execute */
s32 func_800092B0(s32 a0) {
    s32 result;
    if (func_80008430(a0) != 0) {
        return 0;
    }
    func_80009148(0);
    func_80009030(0x2B, a0);
    func_80008498();
    result = func_80006A98(0x04000000);
    func_800091F0(0);
    return result;
}

/* func_80009314 - verified structural decode (kernel, 0x160, rmon
 * register-dump command handler). rmon family (cf. func_80009584 /
 * func_80007564; func_800073F8 = __rmonSendHeader).
 *   s32 func_80009314(RmonMsg *s0) {
 *       if (func_80008430() == 0) return -4;     // precondition
 *       hdr.type   = s0->0xC;                     // sp+0x30
 *       hdr.flags  = 0;                           // sp+0x2A
 *       hdr.domain = s0->0x4;                     // sp+0x28
 *       func_80009148(0);                         // bracket begin
 *       for (i = 0; i < 0x20; i++) {              // 32 entries
 *           func_80009030(0x2B, i);
 *           func_80008498();
 *           buf[i] = func_80006A98(0x04000000);   // RDRAM reg read
 *       }
 *       func_800091F0(0);                         // bracket end
 *       blk[0] = func_80006A98(0x04040004);
 *       blk[1] = func_80006A98(0x04040000);
 *       blk[2] = func_80006A98(0x04040008);
 *       blk[3] = func_80006A98(0x04080000) + 0x04001000;  // SP+bias
 *       blk[4] = func_80006A98(0x0404000C);
 *       blk[5] = func_80006A98(0x04040010);
 *       blk[6] = func_80006A98(0x04040014);
 *       blk[7] = func_80006A98(0x04040018);
 *       func_800073F8(&hdr, 0xB0, 1);             // __rmonSendHeader
 *       return 0;
 *   }
 * Struct-typing reference: s0 = RmonMsg (s0->0x4 u8 domain, s0->0xC
 * type - same family layout as func_80007564/func_80009584).
 * func_80006A98(addr) = a single MMIO/coprocessor register read
 * (addr in the N64 0x0404xxxx RSP/RDP command+status block and
 * 0x04080000 SP PC, plus 0x04000000 RDRAM-config; the +0x04001000
 * applied to the SP read is the DP/PI command-region bias). The
 * 32-iteration loop (func_80009030(0x2B,i) + func_80008498 +
 * func_80006A98(RDRAM)) snapshots a 32-entry register window into
 * the reply at sp+0x24+0x34; then 8 fixed RSP/RDP regs follow at
 * +0x90.. The whole 0xB0-byte buffer is shipped via
 * __rmonSendHeader (func_800073F8), flag 1. Caps <80: rmon
 * stack-buffer build + 32x callee loop + 8 MMIO-read calls + 7
 * distinct callees. Full body INCLUDE_ASM-preserved (.s = source
 * of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009314);

/* func_80009474 split out to kernel_054.c (-O1, NON_MATCHING) */

/* func_80009584 - verified structural decode (kernel, 0x118, rmon
 * debug command handler). SIBLING of the rmon family (calls
 * __rmonSendHeader; cf. func_8000798C / func_80007A98 / RmonMsg).
 *   s32 func_80009584(RmonMsg *s0) {
 *       if (func_80008430() == 0) return -4;     // precondition
 *       hdr.type   = s0->0xC;                     // sp+0x30 struct
 *       hdr.field  = 0x210;
 *       hdr.flags  = 0;
 *       hdr.domain = s0->0x4;
 *       buf[ ] @ sp+0x244; bufptr=&buf; cnt=0;
 *       n = func_800066F0(bufptr + cnt, 4 - cnt, 8);  // read
 *       cnt += n;
 *       if (cnt >= 4) {
 *           __rmonSendHeader(&hdr, 0x10, 1);
 *           func_80009148(1);
 *           for (i = 0; i < 0x20; i++) {
 *               func_800090B4(0x3A, i);
 *               func_80008498();
 *               func_800074A0(0x04000000, 0x10);
 *           }
 *       }
 *       func_800091F0(1);
 *       return 0;
 *   }
 * Struct-typing reference: s0 = RmonMsg (same layout as the
 * func_8000798C family) - s0->0x4 (4) u8 domain, s0->0xC (12) type;
 * stack rmon header at sp+0x30 {type@+0xC i.e. hdr+0, 0x210 const,
 * domain byte, flags u16}. func_800066F0(dst, maxlen, chunk) =
 * bounded read returning bytes read; needs >=4 to proceed.
 * __rmonSendHeader(hdr, len=0x10, flag=1) = the shared rmon emit.
 * The 0x20-iteration loop (func_800090B4(0x3A,i) build +
 * func_80008498 + func_800074A0(0x04000000=PI/cart, 0x10) IO)
 * streams 32 records; func_80009148(1)/func_800091F0(1) = bracket
 * begin/end. Caps <80: rmon stack-struct builder + bounded-read +
 * 32x callee loop + 8 distinct callees. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009584);

/* func_8000969C split out to kernel_054.c (-O1, NON_MATCHING) */


/* __osSetFpcCsr — hand-written assembly in libultra (cfc1 $v0,$31; ctc1 $a0,$31;
 * jr $ra; nop). Matches libreultra/src/os/setfpccsr.s exactly. IDO doesn't
 * parse GCC inline asm, so there's no C form; INCLUDE_ASM is correct. */
INCLUDE_ASM("asm/nonmatchings/kernel", __osSetFpcCsr);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80009850);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800099F0);
