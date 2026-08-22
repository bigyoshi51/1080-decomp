/* IDO 7.1 -O1 whole-fn donor for gl_func_00071144 = libultra
 * osViSetSpecialFeatures (libreultra src/io/visetspecial.c verbatim).
 * PROVEN EXACT 2026-08-22: first -O1 compile is 110/110 FULL-word
 * identical to the raw target .s (5.3 -O1 identical too; -O2 CSEs the
 * __osViNext reloads and hoists the andi tests, 88-word divergence).
 * The -O1 shape is the fingerprint the old NM wrap called a
 * "register-allocation cap": arg re-read from its stack home before
 * every test, sequential t-reg temps, beql fallthroughs, and the
 * `register u32 saveMask` living in $a0 across the whole body.
 * Reloc story (all blank in the USO, load-time reloc table already
 * matched as data):
 *   - jal __osDisableInt / jal __osRestoreInt -> extern names
 *     gl_func_00000000_{disint711,rstint711}, pins = 0
 *     (undefined_syms_auto.txt) so the link bakes 0x0C000000 verbatim;
 *   - 9x lui/lo16 __osViNext -> gl_func_00000000_vinext711, pin = 0,
 *     baking the blank 3C0x0000/8C4x0000 pairs.
 * The 2 trailing zero words the compiler pads the TU with are NOT
 * spliced (fn symbol size 0x1B8); the unit keeps
 * gl_func_00071144_pad.s. Spliced into game_libs_post2.c.o via
 * REPLACE_FUNC_BODY. */
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
    u32 ctrl;
    u32 width;
    u32 burst;
    u32 vSync;
    u32 hSync;
    u32 leap;
    u32 hStart;
    u32 xScale;
    u32 vCurrent;
} OSViCommonRegs;

typedef struct {
    u32 origin;
    u32 yScale;
    u32 vStart;
    u32 vBurst;
    u32 vIntr;
} OSViFieldRegs;

typedef struct {
    u8 type;
    OSViCommonRegs comRegs;
    OSViFieldRegs fldRegs[2];
} OSViMode;

typedef struct {
    u16 state;
    u16 retraceCount;
    void *framep;
    OSViMode *modep;
    u32 control;
} __OSViContext;

/* __osViNext (blank USO reloc, pin = 0) */
extern __OSViContext *gl_func_00000000_vinext711;
/* __osDisableInt / __osRestoreInt (blank USO jal relocs, pins = 0) */
extern u32 gl_func_00000000_disint711(void);
extern void gl_func_00000000_rstint711(u32);

#define OS_VI_GAMMA_ON          0x0001
#define OS_VI_GAMMA_OFF         0x0002
#define OS_VI_GAMMA_DITHER_ON   0x0004
#define OS_VI_GAMMA_DITHER_OFF  0x0008
#define OS_VI_DIVOT_ON          0x0010
#define OS_VI_DIVOT_OFF         0x0020
#define OS_VI_DITHER_FILTER_ON  0x0040
#define OS_VI_DITHER_FILTER_OFF 0x0080

#define VI_CTRL_GAMMA_ON         0x0008
#define VI_CTRL_GAMMA_DITHER_ON  0x0004
#define VI_CTRL_DIVOT_ON         0x0010
#define VI_CTRL_DITHER_FILTER_ON 0x10000
#define VI_CTRL_ANTIALIAS_MASK   0x0300
#define VI_STATE_08              0x0008

/* osViSetSpecialFeatures */
void gl_func_00071144(u32 func)
{
    register u32 saveMask;
    saveMask = gl_func_00000000_disint711();
    if ((func & OS_VI_GAMMA_ON) != 0) {
        gl_func_00000000_vinext711->control |= VI_CTRL_GAMMA_ON;
    }
    if ((func & OS_VI_GAMMA_OFF) != 0) {
        gl_func_00000000_vinext711->control &= ~VI_CTRL_GAMMA_ON;
    }
    if ((func & OS_VI_GAMMA_DITHER_ON) != 0) {
        gl_func_00000000_vinext711->control |= VI_CTRL_GAMMA_DITHER_ON;
    }
    if ((func & OS_VI_GAMMA_DITHER_OFF) != 0) {
        gl_func_00000000_vinext711->control &= ~VI_CTRL_GAMMA_DITHER_ON;
    }
    if ((func & OS_VI_DIVOT_ON) != 0) {
        gl_func_00000000_vinext711->control |= VI_CTRL_DIVOT_ON;
    }
    if ((func & OS_VI_DIVOT_OFF) != 0) {
        gl_func_00000000_vinext711->control &= ~VI_CTRL_DIVOT_ON;
    }
    if ((func & OS_VI_DITHER_FILTER_ON) != 0) {
        gl_func_00000000_vinext711->control |= VI_CTRL_DITHER_FILTER_ON;
        gl_func_00000000_vinext711->control &= ~VI_CTRL_ANTIALIAS_MASK;
    }
    if ((func & OS_VI_DITHER_FILTER_OFF) != 0) {
        gl_func_00000000_vinext711->control &= ~VI_CTRL_DITHER_FILTER_ON;
        gl_func_00000000_vinext711->control |=
            gl_func_00000000_vinext711->modep->comRegs.ctrl & VI_CTRL_ANTIALIAS_MASK;
    }
    gl_func_00000000_vinext711->state |= VI_STATE_08;

    gl_func_00000000_rstint711(saveMask);
}
