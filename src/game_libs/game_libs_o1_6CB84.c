/* IDO -O1 donor for gl_func_0006CB84 = libultra __osSpRawStartDma
 * (references/libreultra/src/io/sprawdma.c, verbatim: SP busy guard,
 * SP_MEM_ADDR_REG = devAddr, SP_DRAM_ADDR_REG = osVirtualToPhysical,
 * dir-selected SP_WR_LEN/RD_LEN = size - 1). PROVEN EXACT 35/35
 * standalone at BOTH IDO 7.1 -O1 and 5.3 -O1 (identical output; built
 * with 7.1). The jr-ra delay nop was carved into a _pad.s sidecar by
 * splat; merged back into gl_func_0006CB84.s (0x88 -> 0x8c) per the
 * absorption prerequisite.
 * Blank externs: fn0 = __osSpDeviceBusy, fn1 = osVirtualToPhysical.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef int s32;
typedef unsigned int u32;
extern s32 gl_func_00000000(void);   /* __osSpDeviceBusy */
extern u32 gl_func_00000001(void *); /* osVirtualToPhysical */

s32 gl_func_0006CB84(s32 direction, u32 devAddr, void *dramAddr, u32 size) {
    if (gl_func_00000000())
        return -1;
    *(volatile u32 *)0xA4040000 = devAddr;
    *(volatile u32 *)0xA4040004 = gl_func_00000001(dramAddr);
    if (direction == 0)
        *(volatile u32 *)0xA404000C = size - 1;
    else
        *(volatile u32 *)0xA4040008 = size - 1;
    return 0;
}
