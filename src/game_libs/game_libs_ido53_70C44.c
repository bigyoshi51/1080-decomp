/* IDO 5.3 -O1 donor for gl_func_00070C44 = libultra __osViSwapContext
 * (viswapcontext.c verbatim). PROVEN EXACT 215/215 standalone at IDO
 * 5.3 -O1. vc colors s1, vm s0, osVirtualToPhysical result s2; field
 * (48sp), nomValue (52sp), hStart (56sp), origin (60sp) are stack
 * locals; the f32->u32 y.scale cast is the inline cfc1/ctc1 dance and
 * the 0x30-byte *__osViNext = *__osViCurr tail is the 12-byte/iter
 * lwl-free struct-copy loop.
 * Blank externs: D_00000000_vicurr/vinext (__osViCurr/__osViNext),
 * gl_func_00000000_v2p = osVirtualToPhysical (blank jal).
 * Spliced into game_libs_post1c.c.o via REPLACE_FUNC_BODY. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

typedef struct {
    u32 ctrl, width, burst, vSync, hSync, leap, hStart, xScale, vCurrent;
} OSViCommonRegs;

typedef struct {
    u32 origin, yScale, vStart, vBurst, vIntr;
} OSViFieldRegs;

typedef struct {
    u8 type;                  /* 0x00 */
    OSViCommonRegs comRegs;   /* 0x04 */
    OSViFieldRegs fldRegs[2]; /* 0x28 */
} OSViMode;

typedef struct {
    f32 factor; /* 0x0 */
    u16 offset; /* 0x4 */
    u32 scale;  /* 0x8 */
} __OSViScale;

typedef struct {
    u16 state;        /* 0x00 */
    u16 retraceCount; /* 0x02 */
    void *framep;     /* 0x04 */
    OSViMode *modep;  /* 0x08 */
    u32 control;      /* 0x0C */
    void *msgq;       /* 0x10 */
    void *msg;        /* 0x14 */
    __OSViScale x;    /* 0x18 */
    __OSViScale y;    /* 0x24 */
} __OSViContext;      /* sizeof 0x30 */

extern __OSViContext *D_00000000_vicurr;   /* __osViCurr */
extern __OSViContext *D_00000000_vinext;   /* __osViNext */
extern u32 gl_func_00000000_v2p(void *);   /* osVirtualToPhysical */

#define IO_READ(a) (*(volatile u32 *)((a) | 0xA0000000))
#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))

#define VI_STATE_XSCALE_UPDATED 0x02
#define VI_STATE_YSCALE_UPDATED 0x04
#define VI_STATE_BLACK 0x20
#define VI_STATE_REPEATLINE 0x40
#define VI_STATE_FADE 0x80
#define VI_SCALE_MASK 0xfff
#define VI_2_10_FPART_MASK 0x3ff
#define VI_SUBPIXEL_SH 0x10

void gl_func_00070C44(void) {
    register OSViMode *vm;
    register __OSViContext *vc;
    u32 origin;
    u32 hStart;
    u32 nomValue;
    u32 field;

    field = 0;
    vc = D_00000000_vinext;
    vm = vc->modep;

    field = IO_READ(0xA4400010) & 1; /* VI_CURRENT_REG */

    origin = gl_func_00000000_v2p(vc->framep) + (vm->fldRegs[field].origin);
    if (vc->state & VI_STATE_XSCALE_UPDATED) {
        vc->x.scale |= (vm->comRegs.xScale & ~VI_SCALE_MASK);
    } else {
        vc->x.scale = vm->comRegs.xScale;
    }
    if (vc->state & VI_STATE_YSCALE_UPDATED) {
        nomValue = vm->fldRegs[field].yScale & VI_SCALE_MASK;
        vc->y.scale = vc->y.factor * nomValue;
        vc->y.scale |= vm->fldRegs[field].yScale & ~VI_SCALE_MASK;
    } else {
        vc->y.scale = vm->fldRegs[field].yScale;
    }
    hStart = vm->comRegs.hStart;
    if (vc->state & VI_STATE_BLACK) {
        hStart = 0;
    }
    if (vc->state & VI_STATE_REPEATLINE) {
        vc->y.scale = 0;
        origin = gl_func_00000000_v2p(vc->framep);
    }
    if (vc->state & VI_STATE_FADE) {
        vc->y.scale = (vc->y.offset << VI_SUBPIXEL_SH) & (VI_2_10_FPART_MASK << VI_SUBPIXEL_SH);
        origin = gl_func_00000000_v2p(vc->framep);
    }
    IO_WRITE(0xA4400004, origin);                       /* VI_ORIGIN */
    IO_WRITE(0xA4400008, vm->comRegs.width);            /* VI_WIDTH */
    IO_WRITE(0xA4400014, vm->comRegs.burst);            /* VI_BURST */
    IO_WRITE(0xA4400018, vm->comRegs.vSync);            /* VI_V_SYNC */
    IO_WRITE(0xA440001C, vm->comRegs.hSync);            /* VI_H_SYNC */
    IO_WRITE(0xA4400020, vm->comRegs.leap);             /* VI_LEAP */
    IO_WRITE(0xA4400024, hStart);                       /* VI_H_START */
    IO_WRITE(0xA4400028, vm->fldRegs[field].vStart);    /* VI_V_START */
    IO_WRITE(0xA440002C, vm->fldRegs[field].vBurst);    /* VI_V_BURST */
    IO_WRITE(0xA440000C, vm->fldRegs[field].vIntr);     /* VI_INTR */
    IO_WRITE(0xA4400030, vc->x.scale);                  /* VI_X_SCALE */
    IO_WRITE(0xA4400034, vc->y.scale);                  /* VI_Y_SCALE */
    IO_WRITE(0xA4400000, vc->control);                  /* VI_CONTROL */

    D_00000000_vinext = D_00000000_vicurr;
    D_00000000_vicurr = vc;
    *D_00000000_vinext = *D_00000000_vicurr;
}
