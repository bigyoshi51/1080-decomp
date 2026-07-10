/* IDO 5.3 -O1 donor for gl_func_00070040 = libultra osAiSetFrequency
 * (aisetfreq.c verbatim). PROVEN EXACT 88/88 standalone at IDO 5.3 -O1.
 * 5.3 DISCRIMINATOR: the u8 bitRate truncation — 5.3 emits the target's
 * andi-to-temp + or copy (`andi t8,a2,0xff; or a2,t8,zero`); 7.1 -O1
 * coalesces to andi-in-place (57/88 shifted). Absorbs the 3-word orphan
 * game_libs_func_00070030 (lui/lw osViClock + mtc1 a0,$f8 = the hoisted
 * head IDO schedules before the addiu-sp prologue; true entry = 0x70034).
 * The orphan's word 0 (0x70030) is the previous fn's trailing pad nop ->
 * SUFFIX_BYTES_FORCE on gl_func_0006FFE4.
 * Blank extern: D_00000000_viclock = osViClock (USO reloc word, blanked).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef float f32;

extern s32 D_00000000_viclock; /* osViClock */

#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))

s32 gl_func_00070040(u32 frequency) {
    register u32 dacRate;
    register u8 bitRate;
    register f32 f;

    f = D_00000000_viclock / (f32)frequency + .5f;
    dacRate = f;
    if (dacRate < 132) {
        return -1;
    }
    bitRate = dacRate / 66;
    if (bitRate > 16) {
        bitRate = 16;
    }
    IO_WRITE(0xA4500010, dacRate - 1); /* AI_DACRATE_REG */
    IO_WRITE(0xA4500014, bitRate - 1); /* AI_BITRATE_REG */
    IO_WRITE(0xA4500008, 1);           /* AI_CONTROL_REG = DMA_ON */
    return D_00000000_viclock / (s32)dacRate;
}
