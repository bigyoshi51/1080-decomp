#include "common.h"

extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 siacs_bss_0000;
extern void func_800053D0(s32*, s32*, s32);
extern void func_80005DC0(s32*, s32, s32);

/* func_80005350 (splat fragment "0x1D0" @ kernel) is NOT a standalone
 * function and CANNOT be landed as C. Verified 2026-06-23 from the linked
 * ELF symbol table (build/tenshoe.elf):
 *
 *     800052f0 T func_800052F0       <- the ONLY real text symbol here
 *     80005350 A func_80005350       <- ABSOLUTE (alt-entry address const)
 *     800053d0 A func_800053D0       <- ABSOLUTE
 *     80005400 A func_80005400       <- ABSOLUTE
 *     800054c0 A func_800054C0       <- ABSOLUTE
 *
 * The single real function is func_800052F0 = __osEPiRawStartDma
 * (libreultra src/io/epirawdma.c; EPI_SYNC macro inlined). Its body spans
 * 0x800052F0..0x8000551C with ONE -0x30 frame (prologue in func_800052F0)
 * and ONE epilogue/`jr ra` at 0x80005508. The four 0x350/0x3D0/0x400/0x4C0
 * symbols are alt-ENTRY points into that shared body, exported as absolutes
 * in undefined_syms so the PI raw read/write/DMA wrapper callers can jal
 * directly to the appropriate offset (shared-tail / multi-entry pattern).
 *
 * Proof these are mid-body, not function starts (raw ROM bytes):
 *   0x800053D0 = 0x114D0024  beq  $t2,$t5,...   (a compare, not a prologue)
 *   0x80005400 = 0xAF380024  sw   $t8,0x24($t9) (mid store)
 *   0x800054C0 = 0x00000000  nop                (a branch-DELAY slot!)
 * A C function cannot begin at a delay-slot nop, and standalone C cannot
 * emit multiple external entry points into one frame. The prior annotation
 * "func_800053D0 = osCreateMesgQueue" was incorrect (those bytes are a beq,
 * and the symbol is ABSOLUTE, not a T function).
 *
 * CONFIRMED CAP (not a bug): no honest C decode exists for func_80005350 on
 * its own; the whole function is func_800052F0 (decoded NON_MATCHING in
 * kernel_005_b.c, itself an -O1 reg-coloring/scheduling residual). Body
 * kept INCLUDE_ASM (.s = source of truth, ROM byte-exact). No episode. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80005350);

/* func_80005520 - verified structural decode (kernel, 0x1CC, 115
 * insns) = libultra osCreatePiManager. Reference: libreultra
 * src/io/pimgr.c (__osPiDevMgr, __osPiAccessQueue,
 * __osPiCreateAccessQueue, osCreateThread/osStartThread).
 *   void func_80005520(OSPri pri, OSMesgQueue *cmdQ,
 *                      OSMesg *cmdBuf, s32 cmdMsgCnt) {
 *       if (__osPiDevMgr.active) return;          // D_8000A450
 *       osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);   // 800053D0
 *       osCreateMesgQueue(&__osPiAccessQueue,
 *                         &pimgr_bss_17B8, 1);
 *       if (D_8000A480) func_80005584();          // accessQ enable
 *       else {
 *           func_80005C00();
 *           osCreateThread(8, &pimgr_bss_17A0, ...,
 *                          stack(0x22222222 fill));     // 800051E0
 *           ...
 *           if (osGetThreadPri(NULL) < pri)            // 800064F0
 *               osSetThreadPri(NULL, pri);             // 80006510
 *           s = __osDisableInt();                      // 800066B0
 *           __osPiDevMgr.active     = 1;               // D_8000A450
 *           __osPiDevMgr.cmdQueue   = pimgr_bss_0000;  // D_8000A454
 *           __osPiDevMgr.cmdQueue2  = cmdQ;            // D_8000A458
 *           __osPiDevMgr.thread     = &pimgr_bss_17A0; // D_8000A45C
 *           ... osStartThread + __osRestoreInt(s) ...
 *       }
 *   }
 * Struct-typing reference: D_8000A450 = __osPiDevMgr.active flag
 * (created-once guard), D_8000A454/0x458/0x45C = devmgr fields
 * (evt/cmd queues, mgr thread); __osPiAccessQueue = the access
 * mesg-queue; pimgr_bss_0000/01B0/17A0/17B8 = PI-manager BSS
 * (thread struct, stack, queue storage); D_8000A480 = an
 * access-queue-enable selector. func_800053D0 = osCreateMesgQueue,
 * func_800051E0 = osCreateThread (stack pre-filled 0x22222222),
 * func_800064F0/_80006510 = osGetThreadPri/osSetThreadPri,
 * func_800066B0 = __osDisableInt. 2026-06-23: devmgr fields now
 * modeled as one PiDevMgr struct at D_8000A450 (offsets +0..+0x18:
 * active/cmdQueue/evtQueue/thread/acsQueue/dma/edma) — semantically
 * exact, objdiff unchanged at 77.43%.
 * 2026-07-10: the old "not -O1-reachable / -O2 store-base CSE" cap FELL —
 * the shared-%hi store cluster is the TU-DEFINED-global codegen (the
 * original pimgr.c DEFINES __osPiDevMgr; `extern` was the 77% floor). Same
 * lever as the game_libs sibling gl_func_0006DA74 (docs/IDO_CODEGEN
 * "TU-DEFINED global = shared-lui $at store cluster"). EXACT 115/115 via
 * the -O1 donor src/kernel/kernel_006_o1_5520.c (REPLACE_FUNC_BODY splice;
 * this TU keeps `extern D_8000A450` so the C body below compiles ~77% and
 * the donor bytes replace it in the .o; D_8000A450 resolves via
 * undefined_syms_auto.txt = 0x8000A450, and the donor's
 * %lo(D_8000A450)+addend relocs resolve byte-identically to the .s's
 * per-field D_8000A454/8/C/60/64/68 relocs). Second lever: assignment
 * order f8=cmdQ BEFORE fC=&thread fixes the t3/t4 temp numbering. */
extern void func_800051E0(s32, s32 *, s32);
extern void func_800053D0(s32 *, s32 *, s32);
extern void func_80005C00(void);
extern s32 func_800064F0(s32);
extern void func_80006510(s32, s32);
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80005F10(void *, s32, void *, void *, void *, s32);
extern void func_8000A110(void *);
typedef struct {
    /* 0x00 */ s32 active;
    /* 0x04 */ s32 cmdQueue;
    /* 0x08 */ s32 evtQueue;
    /* 0x0C */ s32 thread;
    /* 0x10 */ s32 acsQueue;
    /* 0x14 */ s32 dma;
    /* 0x18 */ s32 edma;
} PiDevMgr;
extern PiDevMgr D_8000A450;
extern s32 D_80006060, D_80005AEC;
extern void func_80004A50();
/* 2026-06-10 kernel-relayout: this is ROM 0x800056EC (addiu included).
 * ALL ROM callers jal 0x800056F0 (post-addiu alt entry, the old "stolen
 * prologue" idiom); that name is now a link-time absolute in
 * undefined_syms_auto.txt so caller relocs hit ROM truth. */
extern void func_800056F0(); /* post-addiu alt entry (undefined_syms absolute 0x800056F0) */
extern s32 pimgr_bss_0000, pimgr_bss_01B0, pimgr_bss_11B0, pimgr_bss_1360, pimgr_bss_17A0, pimgr_bss_17B8;
/* PI manager init (one-shot, gated on D_8000A450). Register the two DMA message
 * queues (func_800053D0), enable access if needed (func_80005C00), create the PI
 * thread (func_800051E0, stack-filled 0x22222222), tune priority
 * (func_800064F0/func_80006510), then populate the manager state block
 * (D_8000A450 flag + the queue/handler pointers at +4..+0x18) and spin up the two
 * device workers (func_80005F10 + func_8000A110). func_80005584 is a mid-block
 * alt-entry (the PI word-streamer), reached via undefined_syms. */
void func_80005520(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if (D_8000A450.active == 0) {
        func_800053D0(arg1, arg2, arg3);
        func_800053D0(&pimgr_bss_17A0, &pimgr_bss_17B8, 1);
        if (D_8000A480 == 0) {
            func_80005C00();
        }
        func_800051E0(8, &pimgr_bss_17A0, 0x22222222);
        sp28 = -1;
        sp24 = func_800064F0(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            func_80006510(0, arg0);
        }
        temp_v0 = func_800066B0();
        D_8000A450.active = 1;
        D_8000A450.cmdQueue = (s32) &pimgr_bss_0000;
        D_8000A450.thread = (s32) &pimgr_bss_17A0;
        D_8000A450.evtQueue = (s32) arg1;
        sp2C = temp_v0;
        D_8000A450.acsQueue = (s32) &__osPiAccessQueue;
        D_8000A450.dma = (s32) &func_80004A50;
        D_8000A450.edma = (s32) &func_800056F0; /* ROM stores the post-addiu entry */
        func_80005F10(&pimgr_bss_0000, 0, &D_80006060, &D_8000A450, (char *) &pimgr_bss_01B0 + 0x1000, arg0);
        func_8000A110(&pimgr_bss_0000);
        func_80005F10(&pimgr_bss_11B0, 0, &D_80005AEC, NULL, (char *) &pimgr_bss_1360 + 0x400, arg0 - 1);
        func_8000A110(&pimgr_bss_11B0);
        func_800066D0(sp2C);
        if (sp28 != -1) {
            func_80006510(0, sp28);
        }
    }
}
/* (donor bytes replace the body above in the .o; see comment + Makefile) */




#ifdef NON_MATCHING
extern void func_800051E0(s32, s32 *, s32);
extern void func_80004FE0(s32 *, s32, s32);
extern void func_80005C50(void);
extern void func_80005C94(void);
extern s32 func_800066F0(s32 *, s32, s32);
extern s32 D_8001B5D0, D_8001B5E8, D_8001B5F0, D_8001B608;
/* Kernel event-pump thread loop: registers two message queues
 * (D_8001B5D0/D_8001B5F0) + their event handlers (events 0x12/0x13), then loops
 * forever — block on queue A, run handler func_80005C50, poll func_800066F0
 * until it returns non-zero, block on queue B, run handler func_80005C94.
 * 2026-06-04: kernel_006 flipped to -O1 (whole-file, all funcs prefer or are
 * opt-indifferent to -O1): func_800056EC 47->91.3%, func_80005520 68->77%,
 * func_80005800 stays 100%.
 * 2026-07-10 (44CC lever kit): the "loop-accumulator spill" residual FELL —
 * the accumulator is a LOCAL-STRUCT member (`v.sum`, sp-resident at -O1,
 * reloaded per statement incl. the post-store while-test reload lw t8,0x2C)
 * and the call result is a `register` var (colors s0, or s0,v0). With those
 * two levers the ENTIRE LIVE BODY is byte-exact standalone (insns 0..53 of
 * 66, verified 5.3 AND 7.1 -O1, both identical). REMAINING CAP: the ROM has
 * SEVEN nop words between the loop's back-branch (0x800057BC) and the dead
 * (unreachable) epilogue at 0x800057D4; IDO emits the dead epilogue
 * immediately after the branch with no padding under every flag combo tried
 * (5.3/7.1 x -O0/-O1/-O2/-g/-g3). Mid-function nop block is not
 * source-reachable -> stays NM (no episode). */
void func_800056EC(s32 arg0) {
    struct { s32 sum; } v;
    s32 sp28;
    register s32 r;

    func_800053D0(&D_8001B5D0, &D_8001B5E8, 1);
    func_800053D0(&D_8001B5F0, &D_8001B608, 1);
    func_800051E0(0x12, &D_8001B5D0, 0);
    func_800051E0(0x13, &D_8001B5F0, 0);
    for (;;) {
        func_80004FE0(&D_8001B5D0, 0, 1);
        func_80005C50();
        v.sum = 0;
        do {
            r = func_800066F0(&sp28, 1, 9);
            v.sum = v.sum + r;
        } while (v.sum == 0);
        func_80004FE0(&D_8001B5F0, 0, 1);
        func_80005C94();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800056EC);
#endif

/* __osSiCreateAccessQueue */
void func_80005800(void) {
    D_8000A480 = 1;
    func_800053D0(&__osPiAccessQueue, &siacs_bss_0000, 1);
    func_80005DC0(&__osPiAccessQueue, 0, 0);
}
