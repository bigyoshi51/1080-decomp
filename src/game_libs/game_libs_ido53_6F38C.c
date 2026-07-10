/* IDO 5.3 -O1 donor for gl_func_0006F38C = libultra __osSpDeviceBusy
 * (sp.c verbatim). PROVEN EXACT 11/11 standalone at IDO 5.3 -O1 against
 * the concatenated 0x6F384..0x6F3AC stream. Sibling of gl_func_0006F3BC
 * = __osSiDeviceBusy (same wiring, see that donor's header): splat's
 * game_libs_func_0006F380 3-word fragment (nop + lui t6,0xA404 + lw
 * a0,0x10) was the HOISTED HEAD (`register` load scheduled before the
 * addiu-sp prologue). True entry = 0x6F384. Leading pad nop 0x6F380 ->
 * SUFFIX_BYTES_FORCE on game_libs_func_0006F35C; trailing pad 0x6F3B0
 * -> SUFFIX_BYTES_FORCE on this symbol.
 * SP_STATUS_REG = 0xA4040010; mask 0x1C = SP_STATUS_DMA_BUSY |
 * SP_STATUS_DMA_FULL | SP_STATUS_IO_FULL.
 * Constant-MMIO deref -> no externs needed.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;

int gl_func_0006F38C(void) {
    register u32 stat = *(volatile u32 *)0xA4040010; /* SP_STATUS_REG */

    if (stat & 0x1C) { /* DMA_BUSY | DMA_FULL | IO_FULL */
        return 1;
    }
    return 0;
}
