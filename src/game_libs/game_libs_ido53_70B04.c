/* IDO 5.3 -O1 donor for gl_func_00070B04 = libultra __osViInit
 * (vi.c verbatim). PROVEN EXACT 78/78 standalone at IDO 5.3 -O1 (donor
 * symbol 0x13C = 79 words incl. the jr-ra delay nop; the last 0x70C40
 * alignment word -> SUFFIX_BYTES_FORCE, _pad.s sidecar deleted).
 * The vi[2] context array is game_libs-internal data BAKED to 0x2E4C0
 * (lui 3 / addiu -0x1B40) -> gl_ref_0002E4C0. All other globals are
 * blanked USO reloc words: D_00000000_vicurr/vinext (__osViCurr/Next),
 * D_00000000_tvtype (osTvType), D_00000000_pal/mpal/ntsc
 * (osViModePalLan1/MpalLan1/NtscLan1). Callees (blank jal 0x0C000000):
 * gl_func_00000000 = bzero, gl_func_00000001 = __osViSwapContext
 * (= gl_func_00070C44, the next function).
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
    u8 type;                /* 0x00 */
    OSViCommonRegs comRegs; /* 0x04 */
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

extern __OSViContext gl_ref_0002E4C0[2];    /* vi[2] (baked 0x2E4C0) */
extern __OSViContext *D_00000000_vicurr;    /* __osViCurr */
extern __OSViContext *D_00000000_vinext;    /* __osViNext */
extern s32 D_00000000_tvtype;               /* osTvType */
extern OSViMode D_00000000_pal;             /* osViModePalLan1 */
extern OSViMode D_00000000_mpal;            /* osViModeMpalLan1 */
extern OSViMode D_00000000_ntsc;            /* osViModeNtscLan1 */
extern void gl_func_00000000(void *, s32);  /* bzero */
extern void gl_func_00000001(void);         /* __osViSwapContext = gl_func_00070C44 */

#define vi gl_ref_0002E4C0
#define IO_READ(a) (*(volatile u32 *)((a) | 0xA0000000))
#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))

void gl_func_00070B04(void) {
    gl_func_00000000(vi, sizeof(vi)); /* bzero */
    D_00000000_vicurr = &vi[0];
    D_00000000_vinext = &vi[1];
    D_00000000_vinext->retraceCount = 1;
    D_00000000_vicurr->retraceCount = 1;
    D_00000000_vinext->framep = (void *)0x80000000;
    D_00000000_vicurr->framep = (void *)0x80000000;
    if (D_00000000_tvtype == 0) { /* OS_TV_PAL */
        D_00000000_vinext->modep = &D_00000000_pal;
    } else if (D_00000000_tvtype == 2) { /* OS_TV_MPAL */
        D_00000000_vinext->modep = &D_00000000_mpal;
    } else {
        D_00000000_vinext->modep = &D_00000000_ntsc;
    }
    D_00000000_vinext->state = 0x20; /* VI_STATE_BLACK */
    D_00000000_vinext->control = D_00000000_vinext->modep->comRegs.ctrl;
    while (IO_READ(0xA4400010) > 10) /* VI_CURRENT_REG */
        ;
    IO_WRITE(0xA4400000, 0); /* VI_CONTROL_REG */
    gl_func_00000001();      /* __osViSwapContext */
}
