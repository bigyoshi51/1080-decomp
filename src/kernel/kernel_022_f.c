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
extern s32 func_80008430(); /* K&R no-proto: see func_800092B0 note */
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


/* func_80009148 split out to kernel_054.c (-O1, absorbed func_800091F0 fragment) */

/* func_800091F0 merged into func_80009148 */

/* func_800091FC split out to kernel_054.c (-O1) */

/* rmon execute */
s32 func_800092B0(s32 a0) {
    s32 result;
    /* 2026-06-10 kernel-relayout: call with NO explicit arg (K&R decl;
     * $a0 still holds `a0` at the call, runtime-identical). Passing the
     * arg explicitly makes IDO home $a0 BEFORE the jal + reload it in the
     * delay slot (+1 insn vs ROM); the no-arg form sinks the `sw a0`
     * home into the jal delay slot, matching ROM exactly. */
    if (func_80008430() != 0) {
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
 * Struct-typing reference: s0 = RmonMsg (s0->0x4 u8 domain, s0->0xC
 * type - same family layout as func_80007564/func_80009584).
 * func_80006A98(addr) = a single MMIO/coprocessor register read
 * (addr in the N64 0x0404xxxx RSP/RDP command+status block and
 * 0x04080000 SP PC, plus 0x04000000 RDRAM-config; the +0x04001000
 * applied to the SP read is the DP/PI command-region bias). The
 * 32-iteration loop (func_80009030(0x2B,i) + func_80008498 +
 * func_80006A98(RDRAM)) snapshots a 32-entry register window;
 * 8 fixed RSP/RDP regs follow. Shipped via __rmonSendHeader
 * (func_800073F8), flag 1.
 * rmon stack-buffer build + 32x callee loop + 8 MMIO-read calls.
 * MATCHED byte-exact 2026-06-23 (agent-d): register-pin arg->s0 + loop
 * idx->s1; single contiguous RmonRegDump struct (regs[] at +0x10) passed
 * whole; direct (non-fn-ptr-cast) call to func_800073F8; decl-order
 * `register s0; struct dump; register i;` pins the struct to sp+0x24
 * (struct-FIRST overshoots to +0x28, struct-LAST to +0x20). */
extern void func_800073F8(void *hdr, int len, int flag);
extern void func_80009148(int x);
extern void func_80008498(void);
extern void func_800091F0(int x);
/* func_80006A98 / func_80009030 already file-scope-declared at top. */

typedef struct RmonRegDump {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ unsigned char domain;
    /* 0x05 */ char pad5;
    /* 0x06 */ unsigned short zero6;
    /* 0x08 */ char pad8[4];
    /* 0x0C */ int type;
    /* 0x10 */ int regs[40];   /* 32 loop entries + 8 fixed */
} RmonRegDump;                 /* 0xB0 bytes */

s32 func_80009314(char *arg0) {
    register char *s0 = arg0;
    RmonRegDump dump;
    register int i;
    if (func_80008430() != 0) {
        return -4;
    }
    dump.type = *(int *)(s0 + 0xC);
    dump.domain = *(unsigned char *)(s0 + 0x4);
    dump.zero6 = 0;
    func_80009148(0);
    for (i = 0; i < 0x20; i++) {
        func_80009030(0x2B, i);
        func_80008498();
        dump.regs[i] = func_80006A98(0x04000000);
    }
    func_800091F0(0);
    dump.regs[0x20] = func_80006A98(0x04040004);
    dump.regs[0x21] = func_80006A98(0x04040000);
    dump.regs[0x22] = func_80006A98(0x04040008);
    dump.regs[0x23] = func_80006A98(0x04080000) + 0x04001000;
    dump.regs[0x24] = func_80006A98(0x0404000C);
    dump.regs[0x25] = func_80006A98(0x04040010);
    dump.regs[0x26] = func_80006A98(0x04040014);
    dump.regs[0x27] = func_80006A98(0x04040018);
    func_800073F8(&dump, 0xB0, 1);
    return 0;
}
