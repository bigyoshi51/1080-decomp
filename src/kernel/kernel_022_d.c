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



/* split from kernel_022.c - 2026-06-10 kernel ROM-order relayout */








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
 *       func_80006A50(0x04001000, *(int*)cmd);    // submit word
 *       func_80006A50(0x04080000, 0);             // kick/commit
 *   }
 *   // bundled sibling: same shape but packs a 3rd 6-bit field into
 *   // cmd[2] (mask 0x07, sets bit 0x20) before the same submit.
 * Struct-typing reference: a0/a1 carry small signed bitfields (6-bit
 * x from a0, 5-bit y from a1) packed into a stack command struct
 * (byte 0: bits 2-7 = x<<2, byte 1: bits 0-4 = y; sibling adds byte
 * 2: bits 0-2 = z|0x20). func_80006A50(addr, val) = an MMIO/command
 * submit helper; 0x04001000 / 0x04080000 are the command + kick
 * register addresses (RSP/RDP-style command emit).
 * 2026-06-04: BOUNDARY SPLIT DONE — splat had bundled func_80008C30 +
 * func_80008CB4 under one 0x118 symbol; now two .s (0x84 + 0x94) and
 * func_80008CB4 is a separate INCLUDE_ASM symbol (was in undefined_syms,
 * removed). + constant fix (0x40010000 -> 0x04001000, 0x40800000 ->
 * 0x04080000): 24.93% -> 49.18%.
 * + BITFIELD STRUCT (49.18 -> 67.90%): the byte RMW (andi 0xFF03 / andi
 * 0xFFE0) is IDO char-bitfield codegen — a plain u8[4] zeroes the whole
 * struct so IDO drops the read-back, but `char x:6; char :2;` (BE =
 * MSB-first, so x lands at byte bits 2-7) reproduces the exact masks.
 * The 0xFF03 (not 0x03) is IDO promoting the complement mask to int and
 * taking the low-16 andi imm. REMAINING (~32%, structure-driven cap):
 * target spills+reloads a0/a1 to home slots (frame -0x20, args 0x20/0x24)
 * and keeps the sll/sra sign-ext of x; mine keeps a0/a1 in regs (frame
 * -0x28) and collapses the sign-ext. NOT opt-driven (-O1/-g3/-g all
 * WORSE than -O2's 67.90). Same residual on the func_80008CB4 sibling. */
#ifdef NON_MATCHING
typedef struct {
    char x : 6;
    char f0lo : 2;
    char f1hi : 3;
    char y : 5;
    char b2;
    char b3;
} CmdBits8C30;

void func_80008C30(int a0, int a1) {
    CmdBits8C30 cmd;
    int x = (a0 << 26) >> 26;
    int y = (a1 << 27) >> 27;
    *(int *)&cmd = 0;
    cmd.x = x;
    cmd.y = y;
    func_80006A50(0x04001000, *(int *)&cmd);
    func_80006A50(0x04080000, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008C30);
#endif

/* func_80008CB4: 0x80008CB4-0x80008D44 (size 0x94). The split-off sibling of
 * func_80008C30 (splat had bundled both under one 0x118 symbol). Same RSP/RDP
 * command-emit shape but packs a 3rd 6-bit field into cmd[2] (mask 0x07, sets
 * bit 0x20) before the func_80006A50(0x4001000, *cmd) submit. INCLUDE_ASM for
 * now (boundary split 2026-06-04). C body 0 -> 47.6% (mirror of func_80008C30),
 * then BITFIELD STRUCT -> 68.16%: the 3rd field is `char z:5; char :3;` at
 * byte2 (z at bits 3-7), set to 4 so (4<<3)=0x20 -> andi 0xFF07 + ori 0x20
 * matches. Same ~32% structure-driven arg-reload residual as the sibling. */
#ifdef NON_MATCHING
typedef struct {
    char x : 6;
    char f0lo : 2;
    char f1hi : 3;
    char y : 5;
    char z : 5;
    char b2lo : 3;
    char b3;
} CmdBitsCB4;

void func_80008CB4(int a0, int a1) {
    CmdBitsCB4 cmd;
    int x = (a0 << 26) >> 26;
    int y = (a1 << 27) >> 27;
    *(int *)&cmd = 0;
    cmd.x = x;
    cmd.y = y;
    cmd.z = 4;
    func_80006A50(0x04001000, *(int *)&cmd);
    func_80006A50(0x04080000, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80008CB4);
#endif
