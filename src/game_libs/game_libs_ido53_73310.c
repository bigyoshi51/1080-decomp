/* IDO 5.3 -O1 donor for game_libs_func_00073310 = libultra
 * osViGetCurrentField (vigetfield.c verbatim: IO_READ(VI_CURRENT_REG) & 1).
 * PROVEN EXACT 5/5 standalone at IDO 5.3 -O1. 5.3 DISCRIMINATOR: 5.3
 * lands the andi in a temp with the copy in the jr delay (`andi t7,v0,1;
 * jr ra; or v0,t7,zero`) — the exact pair the 2026-06-10 7.1 shape sweep
 * (6 forms x O1/O2/g/g3) proved 7.1 never emits. True entry = 0x73314;
 * the .s's leading word (0x73310) is the previous fn's alignment pad nop
 * -> SUFFIX_BYTES_FORCE on gl_func_000732C4.
 * Spliced into game_libs_post2b_c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;

#define IO_READ(a) (*(volatile u32 *)((a) | 0xA0000000))

u32 game_libs_func_00073310(void) {
    return IO_READ(0xA4400010) & 1; /* VI_CURRENT_REG */
}
