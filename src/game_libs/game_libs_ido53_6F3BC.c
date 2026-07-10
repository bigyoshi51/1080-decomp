/* IDO 5.3 -O1 donor for gl_func_0006F3BC = libultra __osSiDeviceBusy
 * (si.c verbatim). PROVEN EXACT 11/11 standalone (5.3 AND 7.1 -O1 agree)
 * against the concatenated 0x6F3B4..0x6F3DC stream.
 * BOUNDARY FIX: splat's game_libs_func_0006F3B0 "3-insn alt-entry
 * fragment" (nop + lui t6,0xA480 + lw a0,0x18) was this function's
 * HOISTED HEAD -- IDO -O1 schedules the `register u32 stat = IO_READ(
 * SI_STATUS_REG)` load (into a0, per the register hint) before the
 * addiu-sp prologue, and splat split at the prologue. True entry =
 * 0x6F3B4; spliced symbol covers 0x6F3B4..0x6F3DC. The 0x6F3B0 leading
 * pad nop is emitted as SUFFIX_BYTES_FORCE on gl_func_0006F38C; the
 * 0x6F3E0 trailing pad nop as SUFFIX_BYTES_FORCE on this symbol.
 * This RETIRES the 2026-04-20/2026-05-30 "sp=-8 frame with no stack use
 * has no C trigger" cap: all those sweeps probed the SPLIT fragment as a
 * standalone int-arg fn at -O2. The frame is just the -O1 non-leaf-style
 * frame of the full merged function.
 * Constant-MMIO deref (0xA4800018 = SI_STATUS_REG) -> no externs needed.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;

int gl_func_0006F3BC(void) {
    register u32 stat = *(volatile u32 *)0xA4800018; /* SI_STATUS_REG */

    if (stat & 3) { /* SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY */
        return 1;
    }
    return 0;
}
