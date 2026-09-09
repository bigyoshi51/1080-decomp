/* IDO -O1 donor for gl_func_0006CD44 = libultra osViSetMode
 * (references/libreultra/src/io/visetmode.c, verbatim). PROVEN EXACT 26/26
 * standalone at BOTH IDO 7.1 -O1 and 5.3 -O1 (identical output; built with
 * 7.1), agent-g 2026-09-09. Section 0x813B0 = bootup.uso export sym 1988
 * (three jal refs from one caller at 0x59220/34/48). The 86% NM decode
 * ("factory + 3 global-data stores + chain, D_A/D_B/D_C") was this function
 * at -O2 with three anonymous globals: all three lui/lw reloads hit ONE
 * symbol, __osViNext (per-statement reload = the -O1 tell, though here -O2
 * also has to reload after each store through the context pointer), and
 * `register u32 saveMask` is what puts the __osDisableInt result in s0.
 * OSViContext: state u16 @0, retraceCount @2, framep @4, modep @8,
 * control @0xC; OSViMode: type u8 @0, comRegs.ctrl @4. VI_STATE_01 =
 * VI_STATE_MODE_UPDATED.
 * Blank externs (USO load-time relocs, existing pins = 0):
 * D_00000000_vinext = __osViNext, gl_func_00000000_disint = __osDisableInt,
 * gl_func_00000000_resint = __osRestoreInt. Spliced into
 * game_libs_post1b2c.c.o via REPLACE_FUNC_BODY; the 2-word
 * gl_func_0006CD44_pad.s (inter-object pad before the contpfs.c pair at
 * 0x6CDB4) stays as it is -- the C body is the same 0x68 as the old .s. */
typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    /* 0x00 */ u32 ctrl;
    /* 0x04 */ u32 width;
    /* 0x08 */ u32 burst;
    /* 0x0C */ u32 vSync;
    /* 0x10 */ u32 hSync;
    /* 0x14 */ u32 leap;
    /* 0x18 */ u32 hStart;
    /* 0x1C */ u32 xScale;
    /* 0x20 */ u32 vCurrent;
} OSViCommonRegs;

typedef struct {
    /* 0x00 */ u32 origin;
    /* 0x04 */ u32 yScale;
    /* 0x08 */ u32 vStart;
    /* 0x0C */ u32 vBurst;
    /* 0x10 */ u32 vIntr;
} OSViFieldRegs;

typedef struct {
    /* 0x00 */ unsigned char type;
    /* 0x04 */ OSViCommonRegs comRegs;
    /* 0x28 */ OSViFieldRegs fldRegs[2];
} OSViMode;

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ void *mq;
    /* 0x14 */ void *msg;
    /* 0x18 */ u32 xScale;
    /* 0x1C */ u32 yScale;
} OSViContext;

#define VI_STATE_01 0x01 /* VI_STATE_MODE_UPDATED */

extern OSViContext *D_00000000_vinext;      /* __osViNext */
extern u32 gl_func_00000000_disint(void);   /* __osDisableInt */
extern void gl_func_00000000_resint(u32);   /* __osRestoreInt */
#define __osViNext D_00000000_vinext
#define __osDisableInt gl_func_00000000_disint
#define __osRestoreInt gl_func_00000000_resint

void gl_func_0006CD44(OSViMode *modep)
{
    register u32 saveMask;
    saveMask = __osDisableInt();
    __osViNext->modep = modep;
    __osViNext->state = VI_STATE_01;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;
    __osRestoreInt(saveMask);
}
