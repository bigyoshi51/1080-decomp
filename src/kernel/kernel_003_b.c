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



#ifdef NON_MATCHING
/* PI DOM2 timing + system init. Single residual diff (2026-06-23): the target
 * shares ONE `lui $at` across the two adjacent byte stores D6/D7
 * (`li t0,6; li t1,2; sb t0,%lo(D6)(at); sb t1,%lo(D7)(at)`), hoisting both
 * immediates before the pair; IDO -O1 from straight C instead reloads
 * `lui $at` for D7. Every other store (D4/D5/D8/D9) emits its own `lui $at`
 * and matches exactly. All structural levers regress (char* base / u8[] array
 * spill a held base reg; struct retype no-ops the share — IDO_CODEGEN.md:741);
 * permuter (2 runs, ~1.5k iters, temp/reorder/split weights) never beat the
 * baseline 1-diff. This is an IDO internal-scheduler `$at`-coalescing decision
 * not reachable from source. Leave NON_MATCHING (no episode).
 * 2026-07-10 negative probe (w48 sweep): `extern u8 D_800195D6[];` +
 * D6[0]/D6[1] indexing (array-decay, hoping for one %hi + %lo/%lo+1 pair)
 * REGRESSES — IDO materializes the base in a NAMED reg (lui+addiu per
 * access, +5 words, whole store block re-schedules). Reverted; cap stands.
 * 2026-07-15 (agent-h) lever-wave re-verify — cap CONFIRMED, exhaustively:
 * comma-operator single statement (D6=6, D7=2) = no change; (&D6)[1]=2 =
 * base materialization regression (as documented); struct {u8 d6,d7} pair
 * (SAME symbol, +1 offset) still emits TWO lui $at at -O1 (7.1 AND 5.3);
 * -O2 hoists %hi into a named reg (zero lui $at, wrong shape). No IDO
 * config emits one shared $at across two adjacent byte stores. The target
 * pair (both li's hoisted above both sb's, one $at) matches no compiler
 * output family — plausibly hand-touched asm or a different tool. */
extern u8 D_800195D4;
extern u8 D_800195D5;
extern u8 D_800195D6;
extern u8 D_800195D7;
extern u8 D_800195D8;
extern u8 D_800195D9;
extern s32 D_800195D0;
extern s32 D_800195DC;
extern s32 D_800195E0;
extern s32 D_80019644;
extern void* D_8000A46C;
extern s32 func_800030D0(s32*, s32);

#define IO_WRITE(addr, val) (*(volatile s32*)(addr) = (val))

/* func_80004E50: global-init + PI-BSD-DOM HW-reg writes. NOTES:
 * - The 4 IO_WRITE literals (0xA46000xx) link byte-identical to the expected
 *   D_A46000xx relocs (both resolve to the same final address). Do NOT convert
 *   to `extern volatile s32 D_A46000xx = v;` — that re-schedules the whole fn.
 * - func_800030D0's first arg is derived from &D_800195D0 (the returned base),
 *   NOT &D_800195E0: `&D_800195D0 + 5` == 0x800195E4 == &D_800195E0 + 1. This
 *   matters for the linked bytes (target materializes &D_800195D0 then +0x14),
 *   fixed 2026-06-23; previously baked &D_800195E0 (a real byte diff).
 * - Sole remaining diff: the D6/D7 shared-$at store pair (see comment above). */
void* func_80004E50(void) {
    s32 sr;
    D_800195D4 = 2;
    D_800195DC = 0xA5000000;
    D_800195D5 = 3;
    D_800195D8 = 6;
    D_800195D6 = 6;
    D_800195D7 = 2;
    D_800195D9 = 1;
    IO_WRITE(0xA4600024, 3);
    IO_WRITE(0xA4600028, D_800195D8);
    IO_WRITE(0xA460002C, D_800195D6);
    IO_WRITE(0xA4600030, D_800195D7);
    D_800195E0 = 0;
    func_800030D0(&D_800195D0 + 5, 0x60);
    sr = func_800066B0();
    D_800195D0 = (s32)D_8000A46C;
    D_8000A46C = &D_800195D0;
    D_80019644 = (s32)&D_800195D0;
    func_800066D0(sr);
    return &D_800195D0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004E50);
#endif
