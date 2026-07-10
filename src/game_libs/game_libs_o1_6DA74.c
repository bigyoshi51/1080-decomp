/* -O1 donor for gl_func_0006DA74 — 98-insn osCreatePiManager (libultra
 * pimgr.c, identified 2026-07-09 vs references/libreultra/src/io/pimgr.c;
 * decode matches field-for-field). PROVEN EXACT 98/98 at both IDO 7.1 and
 * 5.3 -O1 (standalone probe, relocs baked with the gl_ref values below);
 * built here with 7.1 (plain -O1).
 * KEY LEVER — TU-DEFINED DevMgr: `DevMgr gl_devmgr_6DA74 = {0};` (a
 * definition, NOT extern) is what makes IDO emit the 4+3 store cluster
 * with ONE `lui $at` per group + batched value materializations (every
 * extern/array/pointer/comma spelling emits a `lui $at` per store — floor
 * 48/98, verified exhaustively). The splice imports the reloc as a global
 * UNDEF in the host, so the link resolves it via undefined_syms_auto.txt
 * (= 0, matching the USO's blanked words) — the donor's own .bss never
 * enters the link (C_FILES filter-out).
 * gl_ref absolutes (kernel VRAM, baked by the link):
 *   gl_ref_00042CE0 = piThread, gl_ref_00042E90 = piThreadStack (stack top
 *   passed as +0x1000 = OS_PIM_STACKSIZE, the addiu-after-lui/addiu form),
 *   gl_ref_00043E90 = piEventQueue, gl_ref_00043EA8 = piEventBuf.
 * Blank externs: fn0/1=osCreateMesgQueue, fn2=__osPiCreateAccessQueue,
 * fn3=osSetEventMesg(OS_EVENT_PI=8, q, 0x22222222), fn4/5=osGet/SetThreadPri,
 * fn6=__osDisableInt, fn7=osCreateThread(D_main=__osDevMgrMain),
 * fn8=osStartThread, fn9=__osRestoreInt; D_b=__osPiAccessQueueEnabled,
 * D_f=acsQueue(__osPiAccessQueue), D_g=dma, D_h=edma handlers.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; relocs imported by the splice). */
typedef struct { int f0; void *f4; void *f8; void *f12; void *f16, *f20, *f24; } DevMgr;
typedef int OSPri;
extern unsigned char gl_ref_00043E90[], gl_ref_00043EA8[], gl_ref_00042CE0[], gl_ref_00042E90[];
extern int D_00000000_b;
extern int D_00000000_f, D_00000000_g, D_00000000_h;
extern void D_00000000_main(void *);
extern void gl_func_00000000(void *, void *, int);
extern void gl_func_00000001(void *, void *, int);
extern void gl_func_00000002(void);
extern void gl_func_00000003(int, void *, void *);
extern OSPri gl_func_00000004(void *);
extern void gl_func_00000005(void *, OSPri);
extern unsigned int gl_func_00000006(void);
extern void gl_func_00000007(void *, int, void (*)(void *), void *, void *, OSPri);
extern void gl_func_00000008(void *);
extern void gl_func_00000009(unsigned int);
DevMgr gl_devmgr_6DA74 = {0};
void gl_func_0006DA74(OSPri pri, void *cmdQ, void *cmdBuf, int cmdMsgCnt) {
    unsigned int savedMask;
    OSPri oldPri;
    OSPri myPri;
    if (!gl_devmgr_6DA74.f0) {
        gl_func_00000000(cmdQ, cmdBuf, cmdMsgCnt);
        gl_func_00000001(gl_ref_00043E90, gl_ref_00043EA8, 1);
        if (!D_00000000_b) {
            gl_func_00000002();
        }
        gl_func_00000003(8, gl_ref_00043E90, (void *)0x22222222);
        oldPri = -1;
        myPri = gl_func_00000004(0);
        if (myPri < pri) {
            oldPri = myPri;
            gl_func_00000005(0, pri);
        }
        savedMask = gl_func_00000006();
        gl_devmgr_6DA74.f0 = 1;
        gl_devmgr_6DA74.f4 = gl_ref_00042CE0;
        gl_devmgr_6DA74.f8 = cmdQ;
        gl_devmgr_6DA74.f12 = gl_ref_00043E90;
        gl_devmgr_6DA74.f16 = &D_00000000_f;
        gl_devmgr_6DA74.f20 = &D_00000000_g;
        gl_devmgr_6DA74.f24 = &D_00000000_h;
        gl_func_00000007(gl_ref_00042CE0, 0, D_00000000_main, &gl_devmgr_6DA74, gl_ref_00042E90 + 0x1000, pri);
        gl_func_00000008(gl_ref_00042CE0);
        gl_func_00000009(savedMask);
        if (oldPri != -1) {
            gl_func_00000005(0, oldPri);
        }
    }
}
