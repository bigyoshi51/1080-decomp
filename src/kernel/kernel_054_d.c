#include "common.h"

extern void* func_800077DC(s32 id);
extern void func_80006B20(void* dst, void* src, s32 n);
extern void func_800073F8(void* hdr, s32 size, s32 flags);
extern void func_80007A98(s32 a, s32 b, void* buf);
extern void func_80008D0C(void* buf);

typedef struct { s32 pad0; u8 type; char pad5; s16 flags; s32 data[17]; } RmonBuf76;

typedef struct {
    s32  pad_00;
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[0x14];
    s32  field_1C;
    char pad_20[4];
    s16  field_24;
    s16  field_26;
    char pad_28[0x24];
} RmonBuf76B;

typedef struct {
    char pad_00[4];
    u8   field_04;
    char pad_05[4];
    u8   field_09;
    char pad_0A[2];
    s32  field_0C;
    char pad_10[0x80];
    s32  field_90;
} RmonMsg91FC;

typedef struct {
    char pad_00[4];
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[4];
    s32  field_0C;
} RmonHdr16;

typedef struct {
    char pad_00[4];
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[4];
    s32  field_0C;
    char pad_10[0x80];
    s32  field_90;
} RmonPkt98;

/* split from kernel_054.c - 2026-06-10 kernel ROM-order relayout */

extern s32 func_80008430();
extern void func_800090B4(s32, s32);
extern void func_80008498(void);
extern void func_800091F0(s32);

/* NON_MATCHING: 99.7% match; 3 IDO -O1 scheduling diffs remain:
 *  - sw s0 / sw s1 store order at prologue is swapped
 *  - jal delay slot loads $a0 (redundant) instead of $s0
 *  - hdr stack offset differs by 4 bytes (0x28 vs 0x24)
 * All are pure scheduler/frame-layout choices; logic and size match.
 * Permuter ran 14k iterations, best score 15 (target 0).
 *
 * Variants tested 2026-04-20 (none promoted to 100%):
 *   v2: `register s32 *p = msg;` at decl → emits extra `lw t6; move s0, t6`
 *       (2 insns worse, frame grows)
 *   v3: drop `p` entirely, use `msg` directly → IDO doesn't promote to $s0
 *       (frame shrinks to 0x30, loop reloads from spill each iter — much worse)
 *   v4: `p = msg;` AFTER first jal → adds `lw s0, 0x38(sp)` at early-return
 *       join point (1 insn worse) but delay-slot reload still goes to $a0
 *
 * Root cause: target's `lw s0, 0x38(sp)` in the jal-0 delay slot is IDO's
 * exact scheduling for the pattern "spill a0; jal; next-block reads s0".
 * Our IDO version fills the delay slot with `lw a0, 0x38(sp)` (benign but
 * wasted) because `p` is declared-but-unassigned — from IDO's POV nothing
 * forces s0 to hold msg at that point. Any C that tries to force s0=msg
 * adds an extra instruction somewhere else. Fundamentally a scheduler
 * decision that our C source can't reach; leave for decomp-permuter's
 * next run.
 *
 *   v10 (2026-05-02): `func_80008430(p = msg)` — assign in call arg.
 *     Result: 2.04 % match. IDO loads s0 BEFORE jal (`lw s0,0x38(sp)`)
 *     and uses delay slot for `move a0, s0`. Logic correct but the entire
 *     prologue is reshuffled — far worse than the 99.7 % baseline.
 *   v11 (2026-05-02): `p = msg;` as separate first statement.
 *     Result: 4.08 % match. Adds explicit `lw t6,0x38(sp); move s0,t6`
 *     before the call (matches v2's "2 insns worse" finding) — also a
 *     full-function shift that wrecks the rest of the diff.
 *
 * BOTH v10/v11 confirm: any C-level path that forces s0=msg before the
 * call ALSO commits IDO to scheduling the load EARLY (not in delay slot).
 * The target's pattern requires IDO to discover the delay-slot fill on
 * its own — which it only does when p is referenced AFTER the call but
 * neither defined nor live before. Reachable only via permuter mutations
 * to surrounding statements (e.g., loop init, hdr field order).
 *
 *   v12 (2026-05-02): hdr field-store reorder (flags→type→field_0C). Result:
 *     79.59 % match (regression). The reorder shifted the tail's stack
 *     offsets by 4 bytes and propagated mismatches at +0x88..+0xA8.
 *   v13 (2026-05-02): decl reorder `register s32 *p; register s32 i; hdr` (i
 *     before hdr). Result: 85.71 % match (regression). Putting i before hdr
 *     pushed hdr's stack slot up 4 bytes — frame stayed 0x28 but hdr moved
 *     from sp+0x24 to sp+0x20, breaking all hdr-relative addressing.
 *     Confirms RmonHdr16 stack slot is anchored to its decl-order position.
 *
 * Both v12 and v13 confirm: prologue-store-order is decoupled from C-level
 * decl/use order at -O1. The s0/s1 store order is set by IDO's allocno-id
 * tiebreaker, which we can't influence from C. Permuter only.
 * 2026-05-27 v14 retest: tried `register s32* p = msg;` (replacing the
 * unreachable post-return `p = msg;`) — IDO emits extra `or s0, a0, zero`
 * insn, shifting the entire body by 1 insn → 2/49. The unreachable
 * `p = msg;` is the documented form that doesn't introduce extra emit.
 * Permuter only. */
#ifdef NON_MATCHING
s32 func_8000969C(s32* msg) {
    register s32* p;
    RmonHdr16 hdr;
    register s32 i;

    if (func_80008430(msg) != 0) {
        return -4;
    }
    func_80009148((RmonMsg91FC*)1);
    for (i = 0; i < 0x20; i++) {
        func_80006B20((void*)0x04000000, (char*)p + i * 4 + 0x10, 4);
        func_800090B4(0x32, i);
        func_80008498();
    }
    func_800091F0(1);
    hdr.field_0C = p[3];
    hdr.type = ((u8*)p)[4];
    hdr.flags = 0;
    func_800073F8(&hdr, 0x10, 1);
    return 0;
    p = msg;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000969C);
#endif
