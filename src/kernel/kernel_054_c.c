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
extern void func_80006A50(u32 addr, u32 val);
extern void func_80009030(s32, s32);

/* NON_MATCHING: same IDO -O1 prologue scheduling diffs as func_8000969C
 * (sw s0/s1 order, jal delay slot), PLUS the 0xFFF mask emitted as a
 * delay-slot `andi a1,a1,0xFFF` instead of target's pre-jal `andi t8,
 * t9,0xFFF` with `move a1,t8` in delay. The mask placement causes a
 * 2-insn structural deficit (67 vs 69 insns) that INSN_PATCH alone
 * can't fix — the function size differs.
 *
 * Tried 2026-05-04: `u32 masked = ((u32*)p)[0x27] & 0xFFF;` block-local
 * — IDO spills masked to stack (+1 sw), bumps frame -0x38→-0x40, adds
 * extra reload — net WORSE (34 diffs in 69 insns).
 *
 * 2026-05-05 RE-VERIFIED: build now 67 insns vs expected 68 (only 1-insn
 * deficit, not 2). 29 word-diffs remain. The mask placement (pre-jal vs
 * delay-slot) accounts for the 1-insn size delta; remaining 28 diffs are
 * cascade register-renumber from the position shift.
 *
 * 2026-05-05 v14 TRIED: `register u32 masked = ((u32*)p)[0x27]; __asm__("");
 * masked &= 0xFFF; func_80006A50(0x04080000, masked);` — explicit 3-step
 * compute with scheduling barrier between load and andi, hoping IDO would
 * emit `lw t8; andi t8; move a1, t8` (matching target). Result: REGRESSION
 * 94.97 % → 87.94 %. The barrier broke other delay-slot fills upstream;
 * register hint didn't prevent the move into a1 directly. Net negative.
 * Reverted.
 *
 * 2026-06-04 (94.97 -> 97.57%): the promotion path landed — split the
 * masked arg into a plain `s32 masked = p[0x27] & 0xFFF;` block-local
 * computed BEFORE the call (NOT register-hinted — `register` re-perturbs
 * to 96.1%). IDO now emits `andi t8, a1, 0xfff; jal; or a1, t8, zero`
 * matching the target instead of the andi-in-delay-slot form. RESIDUAL
 * (~2.4%): the frame is 8 bytes too big (the ghost-spill-slot cap shared
 * with func_80000D2C/func_80007698) + the func_8000969C-class prologue
 * schedule (lw s0 vs lw a0, sw s1 position) + t-reg renumber. All
 * remaining are RA/scheduling caps. */
#ifdef NON_MATCHING
/* NON_MATCHING (~99.4% fuzzy, 6 diff sites / 8 reg fields in 68 insns).
 *
 * 2026-07-15 (agent-h): the func_8000969C-class prologue residuals are GONE —
 * `s32* volatile msg` param + `p = msg;` first statement + zero-arg K&R
 * `func_80008430()` call fixed the sw s0/s1 order AND the jal-delay
 * `lw s0,0x38(sp)` (see kernel_054_d.c func_8000969C, now EXACT).
 *
 * SOLE REMAINING RESIDUAL: the 0xFFF mask ping-pong. Target:
 *   lw a1,0x9C(s0); lui a0,0x408; andi t8,a1,0xfff; jal; move a1,t8
 * i.e. load INTO a1, mask a1 -> NEW temp t8, copy back a1 in the delay slot.
 * Probed 2026-07-15 (all in-tree, -O1): inline mask either operand order and
 * bitfield-read (u32 :20,:12) both collapse to in-place `andi a1,a1` (-1 insn,
 * ugen copy-props the move when the source dies); named local / initialized
 * inner-block local -> home store sw N(sp) +frame growth; phantom K&R 2nd
 * param (plain AND register) -> homed at 60(sp) with sw/lw churn (-O1 homes
 * ALL params); u64 mask -> +4 insns of pair-reg churn; <<0 / >>0 phantoms
 * cfe-fold to the inline form (no -O1 ugen ring effect). i-reuse (current)
 * keeps size exact but colors the mask web s1: andi s1,s1 + move a1,s1, and
 * the s1-vs-t8 choice cascades a t8/t9/t0 -> t9/t0 renumber over the tail 4
 * insns. Needs a spelling that keeps the loaded value live past the andi with
 * zero emission — no -O1 form found (dead-if would cross the call = s-reg).
 * The -O2 coloring-lever wave (same-name web, ring burns) does not transfer:
 * -O1 has no uopt web splitting and no ugen temp-ring range folding. */
s32 func_80009474(s32* volatile msg) {
  register s32 *p;
  RmonHdr16 hdr;
  register s32 i;
  p = msg;
  if (func_80008430() != 0)
  {
    return -4;
  }
  func_80009148((RmonMsg91FC *) 0);
  for (i = 0; i < 0x20; i++)
  {
    func_80006A50(0x04000000, ((u32 *) p)[4 + i]);
    func_80009030(0x23, i);
    func_80008498();
  }

  func_800091F0(0);
  func_80006A50(0x04040004, ((u32 *) p)[0x24]);
  func_80006A50(0x04040000, ((u32 *) p)[0x25]);
  i = ((u32 *) p)[0x27] & 0xFFF;
  func_80006A50(0x04080000, i);
  func_80006A50(0x0404000C, ((u32 *) p)[0x28]);
  func_80006A50(0x04040010, ((u32 *) p)[0x29]);
  hdr.field_0C = p[3];
  hdr.type = ((u8 *) p)[4];
  hdr.flags = 0;
  func_800073F8(&hdr, 0x10, 1);
  return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80009474);
#endif
