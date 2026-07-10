/* IDO -O1 donor for gl_func_0006CAD4 = libultra __osSiRawStartDma
 * (references/libreultra/src/io/sirawdma.c, verbatim: SI busy guard,
 * OS_WRITE(1) pre-writeback, SI_DRAM_ADDR_REG = osVirtualToPhysical,
 * dir-selected SI_PIF_ADDR_RD64B/WR64B = 0x1FC007C0 PIF RAM start,
 * OS_READ(0) post-invalidate). PROVEN EXACT 43/43 standalone at BOTH
 * IDO 7.1 -O1 and 5.3 -O1 (identical output; built with 7.1, no CC
 * override needed). The jr-ra delay nop was carved into a _pad.s
 * sidecar by splat; merged back into gl_func_0006CAD4.s (0xa8 -> 0xac)
 * per the absorption prerequisite.
 * Blank externs: fn0 = __osSiDeviceBusy, fn1 = osWritebackDCache,
 * fn2 = osVirtualToPhysical, fn3 = osInvalDCache. IO regs are KSEG1
 * literals. Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef int s32;
typedef unsigned int u32;
extern s32 gl_func_00000000(void);            /* __osSiDeviceBusy */
extern void gl_func_00000001(void *, s32);    /* osWritebackDCache */
extern u32 gl_func_00000002(void *);          /* osVirtualToPhysical */
extern void gl_func_00000003(void *, s32);    /* osInvalDCache */

s32 gl_func_0006CAD4(s32 direction, void *dramAddr) {
    if (gl_func_00000000())
        return -1;

    if (direction == 1)
        gl_func_00000001(dramAddr, 64);

    *(volatile u32 *)0xA4800000 = gl_func_00000002(dramAddr);

    if (direction == 0)
        *(volatile u32 *)0xA4800004 = 0x1FC007C0;
    else
        *(volatile u32 *)0xA4800010 = 0x1FC007C0;

    if (direction == 0)
        gl_func_00000003(dramAddr, 64);

    return 0;
}
