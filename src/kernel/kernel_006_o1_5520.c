/* -O1 donor for func_80005520 — 115-insn kernel osCreatePiManager (KMC
 * kernel variant of libultra pimgr.c; sibling of the game_libs crack
 * gl_func_0006DA74, see docs/IDO_CODEGEN "TU-DEFINED global = shared-lui
 * $at store cluster"). PROVEN EXACT 115/115 (2026-07-10 standalone probe vs
 * asm/nonmatchings/kernel/func_80005520.s; identical at IDO 5.3 AND 7.1
 * -O1 — built here with the default 7.1 at -O1).
 * KEY LEVERS:
 *   - TU-DEFINED PiDevMgr: `PiDevMgr D_8000A450 = {0};` (a definition, NOT
 *     extern) makes IDO emit the 4+3 store cluster with ONE `lui $at` per
 *     group + batched value materializations (extern form = one lui $at per
 *     store, the old 77% floor). The splice imports the reloc as a global
 *     UNDEF in the host; undefined_syms_auto.txt already carries
 *     D_8000A450 = 0x8000A450, and %lo(D_8000A450)+0x4/0x8/0xC/... resolve
 *     byte-identically to the .s's per-field D_8000A454/8/C/60/64/68 relocs.
 *   - Field assignment order f0,f4,f8,fC (f8=cmdQ BEFORE fC=&thread) gives
 *     the target's t3=arg-reload / t4=&pimgr_bss_17A0 temp numbering while
 *     as1 still emits the stores in the target's 0/4/C/8 order.
 * KMC-variant differences vs stock pimgr.c: TWO __osDevMgrMain workers
 * (func_80005F10 pairs with stacks pimgr_bss_01B0+0x1000 and
 * pimgr_bss_1360+0x400, second at pri-1, arg block NULL) and dma/edma
 * handlers func_80004A50 / func_800056F0 (the post-addiu alt entry).
 * Spliced into kernel_006.c.o via REPLACE_FUNC_BODY (real -O1 output;
 * donor relocs imported by the splice; C_FILES filter-out). */
typedef int s32;
typedef s32 OSPri;
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern void func_800053D0(void *, void *, s32);
extern void func_80005C00(void);
extern void func_800051E0(s32, void *, void *);
extern OSPri func_800064F0(void *);
extern void func_80006510(void *, OSPri);
extern unsigned int func_800066B0(void);
extern void func_800066D0(unsigned int);
extern void func_80005F10(void *, s32, void *, void *, void *, OSPri);
extern void func_8000A110(void *);
typedef struct { s32 f0; void *f4; void *f8; void *fC; void *f10, *f14, *f18; } PiDevMgr;
extern s32 D_80006060, D_80005AEC;
extern void func_80004A50();
extern void func_800056F0();
extern unsigned char pimgr_bss_0000[], pimgr_bss_01B0[], pimgr_bss_11B0[], pimgr_bss_1360[], pimgr_bss_17A0[], pimgr_bss_17B8[];

PiDevMgr D_8000A450 = {0};

void func_80005520(OSPri pri, void *cmdQ, void *cmdBuf, s32 cmdMsgCnt) {
    unsigned int savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!D_8000A450.f0) {
        func_800053D0(cmdQ, cmdBuf, cmdMsgCnt);
        func_800053D0(pimgr_bss_17A0, pimgr_bss_17B8, 1);
        if (!D_8000A480) {
            func_80005C00();
        }
        func_800051E0(8, pimgr_bss_17A0, (void *)0x22222222);
        oldPri = -1;
        myPri = func_800064F0(0);
        if (myPri < pri) {
            oldPri = myPri;
            func_80006510(0, pri);
        }
        savedMask = func_800066B0();
        D_8000A450.f0 = 1;
        D_8000A450.f4 = pimgr_bss_0000;
        D_8000A450.f8 = cmdQ;
        D_8000A450.fC = pimgr_bss_17A0;
        D_8000A450.f10 = &__osPiAccessQueue;
        D_8000A450.f14 = &func_80004A50;
        D_8000A450.f18 = &func_800056F0;
        func_80005F10(pimgr_bss_0000, 0, &D_80006060, &D_8000A450, pimgr_bss_01B0 + 0x1000, pri);
        func_8000A110(pimgr_bss_0000);
        func_80005F10(pimgr_bss_11B0, 0, &D_80005AEC, 0, pimgr_bss_1360 + 0x400, pri - 1);
        func_8000A110(pimgr_bss_11B0);
        func_800066D0(savedMask);
        if (oldPri != -1) {
            func_80006510(0, oldPri);
        }
    }
}
