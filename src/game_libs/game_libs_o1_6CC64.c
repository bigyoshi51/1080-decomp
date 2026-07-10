/* IDO -O1 donor for gl_func_0006CC64 = libultra osViBlack
 * (references/libreultra/src/io/viblack.c, verbatim: saveMask =
 * __osDisableInt(); __osViNext->state |= / &= ~VI_STATE_BLACK(0x20);
 * __osRestoreInt(saveMask)). PROVEN EXACT 28/28 standalone at BOTH IDO
 * 7.1 -O1 and 5.3 -O1 (identical output; built with 7.1). Retires the
 * old "rv in s0 / frame -0x28 regalloc cap" NM note: `register u32
 * saveMask` across the call at -O1 IS the s0 coloring.
 * Blank externs: fn0 = __osDisableInt, fn1 = __osRestoreInt;
 * D_00000000_vinext = __osViNext (OSViContext*, u16 state at +0).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef struct { unsigned short state; } ViCtx;
extern ViCtx *D_00000000_vinext;    /* __osViNext */
extern u32 gl_func_00000000(void);  /* __osDisableInt */
extern void gl_func_00000001(u32);  /* __osRestoreInt */

void gl_func_0006CC64(u8 active) {
    register u32 saveMask = gl_func_00000000();
    if (active)
        D_00000000_vinext->state |= 0x20;
    else
        D_00000000_vinext->state &= ~0x20;
    gl_func_00000001(saveMask);
}
