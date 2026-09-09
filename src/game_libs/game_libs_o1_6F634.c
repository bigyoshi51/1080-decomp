/* IDO -O1 donor for gl_func_0006F634 = libultra osViSwapBuffer
 * (references/libreultra/src/io/viswapbuf.c, verbatim). PROVEN EXACT 20/20
 * standalone at BOTH IDO 7.1 -O1 and 5.3 -O1 (identical output; built with
 * 7.1), agent-g 2026-09-09. Section 0x83CA0 = bootup.uso export sym 1549
 * (two jal refs at 0x48860 / 0x5B210). The old NM decode ("2-call +
 * 2-global-state-update, D_6F634_state / D_6F634_flag") was this function
 * with two anonymous globals: both lui/lw reloads hit ONE symbol,
 * __osViNext (framep @4, state u16 @0 |= VI_STATE_BUFFER_UPDATED = 0x10).
 * No `register` on saveMask (the source's spelling): the __osDisableInt
 * result spills to sp+0x1C instead of s0 -- same as osEPiLinkHandle.
 * Blank externs (USO load-time relocs, existing pins = 0):
 * D_00000000_vinext = __osViNext, gl_func_00000000_disint = __osDisableInt,
 * gl_func_00000000_resint = __osRestoreInt. Spliced into
 * game_libs_post1b2c.c.o via REPLACE_FUNC_BODY; no pad (game_libs_func_0006F684
 * follows directly), the C body is the same 0x50 as the old .s. */
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ void *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ void *mq;
    /* 0x14 */ void *msg;
    /* 0x18 */ u32 xScale;
    /* 0x1C */ u32 yScale;
} OSViContext;

#define VI_STATE_10 0x10 /* VI_STATE_BUFFER_UPDATED */

extern OSViContext *D_00000000_vinext;      /* __osViNext */
extern u32 gl_func_00000000_disint(void);   /* __osDisableInt */
extern void gl_func_00000000_resint(u32);   /* __osRestoreInt */
#define __osViNext D_00000000_vinext
#define __osDisableInt gl_func_00000000_disint
#define __osRestoreInt gl_func_00000000_resint

void gl_func_0006F634(void *frameBufPtr)
{
    u32 saveMask;
    saveMask = __osDisableInt();
    __osViNext->framep = frameBufPtr;
    __osViNext->state |= VI_STATE_10;
    __osRestoreInt(saveMask);
}
