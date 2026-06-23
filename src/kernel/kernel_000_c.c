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
extern s32 D_80012BE4;
extern s32 D_80012C64;
extern s32 D_80012C68;
extern s32 D_80012D60[];
extern s32 D_80013000;
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
extern s32 func_80009EA0(void);
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

typedef struct {
    u8 pad_00[0x98];
    u8 in_use;
    u8 pad_99[3];
} UsoSlot;

typedef struct {
    UsoSlot slots[4];
} UsoSlotGroup;

extern u8 D_80013138;
extern UsoSlot D_800130A0;
extern u8 D_800131D4;
extern UsoSlot D_8001313C;
extern u8 D_80013270;
extern UsoSlot D_800131D8;
extern UsoSlotGroup D_80013274;
extern UsoSlotGroup D_800182E4;


/* split from kernel_000.c - 2026-06-10 kernel ROM-order relayout */







/* func_800047E4 merged into func_800047B0 — see kernel_027.c. The
 * 9-insn body that USED $t2/$t5 from "predecessor" was actually the
 * tail of a single 22-insn unaligned-big-endian-load function that
 * splat mis-split at 0x800047E4. Symbol kept as alt-entry via
 * undefined_syms_auto.txt for direct callers (jal func_800047E4). */

/* ===== func_80004808: -O2 double-store / coloring cap (NOT branch-likely) =====
 * CORRECTION 2026-06-23: the older "branch-LIKELY-emission cap" header (below, in
 * spirit) is STALE for func_80004808. The current clean -O2 C body emits REGULAR
 * beqz/bnez — identical branch TYPE to the target. There is NO branch-likely diff.
 * The real residual is a STRUCTURAL/coloring gap: target = 29 insns, clean -O2 C = 26.
 * The 3 extra target insns form the "double-store" idiom for the sp+0x4 header byte:
 *   (1) sb $t8,0x4($sp)   <- a FIRST store of (sp4[0]&0xFF03)|0x30
 *   (2) andi $t1,$t8,0xFF <- read sp4[0] back as a u8 (in-register, not reloaded)
 *   (3) andi $t0,$t9,0x3  <- a redundant 2nd mask of (arg1 & 3)
 * plus the final read is `addiu $t1,$sp,0x4; lw 0x0($t1)` (2 insns) not `lw 0x4($sp)`.
 * The clean -O2 body CSEs the two `sp4[0]=` assigns into ONE store with no readback,
 * folds (arg1&3) once, and folds the final read to `lw 0x4($sp)`. To get the target's
 * double-store at -O2 you must defeat CSE on the readback, but every legitimate lever
 * that does so MATERIALIZES a pointer the target lacks AND/OR narrows the wide masks:
 *   - volatile-cast header writes  -> double-store BUT `addiu $v0,$sp,4` ptr + reload
 *   - union {u32 w; u8 b[4]}       -> double-store BUT `addiu $v0,$sp,4` ptr + `&0xfc`
 *   - sp4[arg1*0] CSE-defeat hack  -> closest shape BUT `*0` index is match-faking
 *   - u8 temp x reused             -> dead-store-eliminated (first sb dropped, frame+8)
 * The target wants double-store WITH direct 4($sp) addressing AND wide masks — a
 * combination IDO -O2 will not emit from any clean C. -O1 reproduces the double-store
 * + addiu/lw character but is 32 insns (unfilled delays, extra reloads); -O0 = 36.
 * Permuter cannot bridge a 3-insn structural gap (coloring-only). Genuine -O2 ugen cap.
 * VERIFIED 2026-05-31 (still relevant for the bnezl family elsewhere): no branch-likely
 * disable flag exists in IDO 7.1 cc. */
#ifdef NON_MATCHING
/* 2026-06-04 (72.68->73.03%): structural cleanup. sp4 is the 4-byte packet
 * word at sp+0x4 (declare `u8 sp4[4]` BEFORE `u32 sp0` so IDO lays sp0 at
 * 0x0, sp4 at 0x4 — frame -0x8 matches target, final read folds to lw 0x4).
 * Second header write reads sp4[0] back (not a temp) so the intermediate
 * store stays live. RESIDUAL: target keeps a 2nd `sb` of the header (RMW
 * memory round-trip + andi 0xFF reload-truncate); IDO register-caches
 * sp4[0] across the two assigns and emits one store (volatile sp4 forces
 * the round-trip but over-corrects the loop -> 67.6%). */
void func_80004808(u8* arg0, u32 arg1) {
    u8 sp4[4];
    u32 sp0;

    sp4[0] = (sp4[0] & 0xFF03) | 0x30;
    sp4[0] = (arg1 & 3) | (sp4[0] & 0xFFFC);
    sp0 = 0;
    if (arg1 != 0) {
        do {
            *((u8*)&sp0 + sp0 + 5) = arg0[sp0];
            sp0++;
        } while (sp0 < arg1);
    }
    *(volatile u32*)0xC0000000 = *(u32*)sp4;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);
#endif

/* RSP status-bit poller. Two loops wait for SP_STATUS bit 0x2000 to be
 * SET then CLEAR around a write to 0xC000000C. The do-while form with the
 * func call in the BODY (not the while-condition) gets IDO to emit plain
 * bnez/beqz instead of branch-likely (which the empty-body form caused). */
#ifdef NON_MATCHING
void func_8000487C(void) {
    s32 r = func_80009EA0();
    if ((r & 0x2000) == 0) {
        do {
            r = func_80009EA0();
        } while ((r & 0x2000) == 0);
    }
    *(volatile u32*)0xC000000C = 0;
    r = func_80009EA0();
    if (r & 0x2000) {
        do {
            r = func_80009EA0();
        } while (r & 0x2000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000487C);
#endif
