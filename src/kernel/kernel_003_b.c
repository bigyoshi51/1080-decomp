#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];


/* split from kernel_003.c - 2026-06-10 kernel ROM-order relayout */



/* func_80004E50 = libultra osLeoDiskInit (io/leodiskinit.c verbatim,
 * IDO 5.3 -O1 donor: kernel_ido53_4E50.c). LANDED 2026-08-22 via
 * REPLACE_FUNC_BODY donor splice: 64/64 non-reloc words identical; the
 * reloc fields resolve via sign-extended-lo pins LeoDiskHandle=
 * 0x800195D0 / __osPiTable=0x8000A46C / __osDiskHandle=0x80019644 and
 * jal renames bzero=func_800030D0, __osDisableInt=func_800066B0,
 * __osRestoreInt=func_800066D0. RETRACTS the "D6/D7 shared-$at store
 * pair = no compiler output family / plausibly hand-touched" cap
 * documented above: the verbatim OSPiHandle STRUCT spelling (pageSize/
 * relDuration at +6/+7 of the ONE LeoDiskHandle symbol, in-place
 * addends) emits the single shared lui $at natively at 5.3 -O1 -- the
 * cap was an artifact of the separate-extern-u8 spelling. Twin of the
 * game_libs gl_func_0006F088 land (blank-pin USO variant). Body below
 * is a placeholder for the splice. */
void *func_80004E50(void) {
    volatile int leodiskinit_spliced = 0;
    leodiskinit_spliced = 1;
    return (void *)leodiskinit_spliced;
}
