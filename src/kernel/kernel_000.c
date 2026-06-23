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


INCLUDE_ASM("asm/nonmatchings/kernel", func_80000000);

extern u32 D_8000A2D8;
extern u32 D_8000A2DC;
extern s32 D_80012D5C;

/* Bump allocator with alignment + bookkeeping. NATURAL CEILING: 91.15% NM.
 * Was previously documented (2026-05-14) as "Promoted from 91.15% NM ->
 * byte-exact via 17-entry INSN_PATCH + 1-word SUFFIX_BYTES_FORCE (4 bytes)"
 * — INSN_PATCH + grow-by-1-insn SUFFIX_BYTES_FORCE REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Cap class: "preemptive set + nop delay" structural shape — target emits
 * `or v0, v1, 0` before the bounds-check branch (separating the move from
 * the branch delay), making the function 1 insn larger than IDO's natural
 * emit. 11+ negative C-shape attempts confirmed the cap is unreachable
 * from naturally-emitted C; default build is INCLUDE_ASM.
 *   D_8000A2D8 = current heap top (bumps on each call)
 *   D_8000A2DC = heap end limit (returns NULL when exceeded)
 *   D_80012D5C = running total of bytes allocated
 *
 * Current match: 18/25 insns (~72%), 7 mnemonic diffs (was 15/26 ~58%).
 * 2026-06-23 NM-body rewrite (agent-i) cut the residual from 11 diffs to 7:
 *   - INLINE the alignment mask `(alignment - 1)` (drop the named `v` mask
 *     var) so IDO frees $a1/$a2 for the two global-pointer bases and hoists
 *     `lui %hi(D_80012D5C)` into the early beqz delay slot — the entire
 *     address-materialization region (a1/a2 coloring) now MATCHES the target.
 *   - explicit `r = v; if (oom) r = 0; return r;` reserves $v0 for the result
 *     so the load/store/bookkeeping region matches too.
 * Residual 7 diffs are the genuine documented structural cap:
 *   (1) `and t6,a0,v0` vs `and t6,v0,a0` — commutative & operand order; IDO
 *       won't swap it from any C source orientation (verified flip-and = 7).
 *   (2-7) the target preemptively emits `move v0,v1` BEFORE the sltu/bnez and
 *       uses TWO `jr ra` (success falls to a bare return; OOM zeroes v0 in the
 *       second jr's delay slot), making the target 25 insns vs IDO's natural
 *       24. No tested C shape forces IDO to emit the +1-insn double-jr-ra form
 *       (goto-out, do/while-break, nested if/else, explicit two-return all
 *       regress; permuter-immune per cap_analysis_2026-05-28, 153k iters).
 *
 * Tried: condition-flip with goto-out (9/26, regressed), explicit
 * `result = orig; if (oom) result = 0; return result;` early-set
 * pattern (5/26, regressed harder — IDO still lets new_top win $v0).
 * Both alternatives shorten the function further by combining the
 * preemptive set into the branch delay slot. No tested C shape forces
 * IDO to emit the +1-insn longer "preemptive set + nop delay" pattern.
 *
 * 2026-05-08 — additional negative attempts:
 *   (a) `if (new_top < D_8000A2DC) return result; return 0;` (flipped
 *       condition with early-return success): 91.15% → 88.65% (-2.5pp).
 *   (b) `ret = result; if (new_top >= D_8000A2DC) ret = 0; return ret;`
 *       (explicit ret local to force preemptive set): 91.15% → 85.38%
 *       (-5.8pp). IDO collapses `ret` into `result` and emits the same
 *       shortened branch-delay pattern.
 * Both retests confirm the shape cap. The 91.15% wrap is the local maximum
 * for naturally-emitted IDO -O2 with current REG_ALLOC_ORDER constraints.
 *
 * 2026-05-08 retest #3 — `register u32 mask;` IDO register hint to coerce
 *   $v0 allocation: emit unchanged ($v1 still selected for mask). IDO's
 *   `register` honors strong reg-class hints but doesn't override the
 *   priority-based $v0/$v1 split when $v0 is reserved for a longer-live
 *   pseudo. Confirms cap is structural, not register-hint-fixable.
 *
 * 2026-05-27 retest #4 — split-jr-ra-via-goto-out lever (the same lever
 *   that landed gl_func_0001FD98 / improved gl_func_00036E74 + 0003D16C):
 *   `if (new_top < D_8000A2DC) goto succ; return 0; succ: return result;`.
 *   Standalone-cc shows mine still places `or v0, v1, $0` in the bnez
 *   delay slot rather than target's BEFORE-sltu position. The goto-out
 *   lever splits the jr-ra into two but doesn't move the preemptive set
 *   out of the delay slot — same root structural-cap as variants (a)/(b).
 *   The cap is the position of the v0=v1 copy, not the number of jr-ra blocks.
 *
 * 2026-06-01 retest #5 — explicit `ret = v; __asm__(""); if (...) return`
 *   barrier is invalid for this IDO/asm-processor path: empty `__asm__` emits
 *   a real jal to `__asm__`, adds a frame/spills, and drops this function to
 *   29.04%. Do not use the asm-barrier lever here.
 *
 * 2026-06-01 retest #6 — GCC-style explicit register locals for the target
 *   `$t9/$t1/$t3` allocation, e.g. `register u32 new_top asm("$25");`, are not
 *   accepted by IDO cfe (`Syntax Error` at `asm`). This lever is unavailable. */
#ifdef NON_MATCHING
u32 func_800000B0(u32 size, u32 alignment) {
    u32 v;   /* old heap top -> $v1, the returned ptr on success */
    u32 r;   /* result: r=v then forced to 0 on OOM, lives in return reg */

    /* inline mask (alignment-1) instead of a named var: lets IDO put the mask
     * in $v0/$v1 and free $a1/$a2 for the two global-pointer bases, matching
     * the target's a1/a2 pointer coloring and the lui-%hi-in-beqz-delay hoist. */
    if (size & (alignment - 1)) {
        size = (size + alignment) & ~(alignment - 1);
    }
    v = D_8000A2D8;
    D_8000A2D8 = v + size;
    D_80012D5C += size;
    r = v;
    if (D_8000A2D8 >= D_8000A2DC) {
        r = 0U;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800000B0);
#endif

/* Boot init */
void func_80000118(s32 a0, s32 a1) {
    s32 saved = func_80002890(1);
    func_8000A0E0();
    func_80005350(a0, a1);
    func_80005400(a0, a1);
    func_80002890(saved);
}

#ifdef NON_MATCHING
/* String-compare returning 0 if equal, 1 if different.
 *
 * UPDATE 2026-05-02: 124 → 120 bytes (target 116) via goto-based structure
 * with `p1 = a0` saved across loop iter (mirrors target's `or v1, a0, zero`
 * delay slot). 4 bytes closer to target.
 *
 * Remaining 4 bytes / 1-insn cap: target uses `beql v0, zero, end` with
 * `sltu v1, zero, v0` in delay slot for entry/loop-tail v0==0 checks; mine
 * emits `beq v0, zero` with nop-filled delay. To reach target, IDO needs to
 * recognize the v0==0 branch's target as starting with the sltu pattern (so
 * it can hoist into delay), but my tail uses `if (v0 != 0) return 1;` which
 * compiles to a different shape. Tried (v4): explicit `v1 = v0 != 0; if(v1)
 * return v1;` — compiles to 124 bytes (back to baseline, sltu emitted but
 * with different surrounding structure). Cap is structural beql-emission
 * not flippable from C. */
s32 func_80000168(char *a0, char *a1) {
    s32 v0;
    s32 t7, t8;
    char *vv;
    char *p1;

    v0 = (u8)*a0;
    if (v0 == 0) goto tail;
    if ((u8)*a1 == 0) goto tail;
    p1 = a0;
loop:
    vv = a1;
    t7 = (u8)*vv;
    t8 = (u8)*p1;
    a1++;
    a0++;
    if (t7 != t8) return 1;
    v0 = (u8)*a0;
    if (v0 == 0) goto tail;
    if ((u8)*a1 == 0) goto tail;
    p1 = a0;
    goto loop;
tail:
    if (v0 != 0) return 1;
    return (u8)*a1 != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000168);
#endif

void func_800001DC(char* dst, char* src) {
    char* s = src;
    unsigned char c = *src;
    char* d = dst;

    *dst = c;
    if (c == 0) {
        return;
    }

    do {
        c = *(s + 1);
        s = s + 1;
        d = d + 1;
        *d = c;
    } while (c != 0);
}

/* uso_find_slash — scan a string for '/' and write its index to *arg1.
 *
 * Returns 1 if found (writing the slash's index to *arg1), 0 if end of
 * string reached.
 *
 * Cap (96 bytes vs target 84): IDO's bnel-back-branch with v0=v1 in delay
 * slot is the load-bearing optimization that target uses to merge the
 * "next-iteration v0 update" into the loop-tail branch. Standard C goto/do-while
 * shapes emit bne+nop without the delay-slot preload (3 extra insns).
 *
 * UPDATE 2026-05-02: cleaned up old wrap that had 6× `if (1) {}` dummy
 * blocks and a `dummy_label_580214` goto-into-fallthrough. Those didn't
 * close the bnel-preload gap and obscured the actual logic. */
#ifdef NON_MATCHING
s32 func_8000020C(char *arg0, s32 *arg1) {
    s32 v0;
    s32 v1;

    v0 = 0;
    v1 = 0;
    if ((u8)arg0[0] == 0) return 0;
    do {
        if ((u8)arg0[v0] == '/') {
            v1 -= 1;
            *arg1 = v1;
            return 1;
        }
        v0 = v1;
        v1++;
    } while ((u8)arg0[v1] != 0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000020C);
#endif

extern s32 func_800005DC();
extern s32 func_8000060C();
extern void func_80000660();

#ifdef NON_MATCHING
/* +472 bytes bloat (built 800 vs baserom 328). Unrolled byte-copy loops
 * produce 2.4x the original asm. Likely the original used memcpy/bcopy
 * helpers or a different byte-copy idiom. Preserved as INCLUDE_ASM in
 * default build so kernel section size matches baserom (this single bloat
 * was responsible for ~80% of the kernel-section ROM-size mismatch). */
void func_80000260(u8* arg0, s32 arg1, u8* arg2) {
    u8 sp48[0x40];
    s32 sp44;
    s32 sp40;
    s32 a2;
    s32 v1;

    if (func_8000060C(arg0, &sp44) != 0) {
        a2 = 0;
        if (sp44 > 0) {
            if ((sp44 & 3) != 0) {
                do {
                    sp48[a2] = arg0[a2];
                    a2++;
                } while ((sp44 & 3) != a2);

                if (a2 != sp44) {
                    do {
                        sp48[a2] = arg0[a2];
                        sp48[a2 + 1] = arg0[a2 + 1];
                        sp48[a2 + 2] = arg0[a2 + 2];
                        sp48[a2 + 3] = arg0[a2 + 3];
                        a2 += 4;
                    } while (a2 != sp44);
                }
            } else {
                do {
                    sp48[a2] = arg0[a2];
                    sp48[a2 + 1] = arg0[a2 + 1];
                    sp48[a2 + 2] = arg0[a2 + 2];
                    sp48[a2 + 3] = arg0[a2 + 3];
                    a2 += 4;
                } while (a2 != sp44);
            }
        }

        sp48[a2] = 0;
        sp40 = sp44 + 1;
        func_800005DC(arg1, sp48, sp40, arg0);

        v1 = 1;
        arg2[0] = arg0[sp40];
        sp40++;
        if (arg2[0] != 0) {
            do {
                arg2[v1] = arg0[sp40];
                v1++;
                sp40++;
            } while (arg2[v1 - 1] != 0);
        }
    } else {
        func_800005DC(arg1, arg0);
        arg2[0] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000260);
#endif

void func_800003A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 savedMask;
    s32 status;
    u16 first16;
    u16 loop16;

    D_80013000 = 0;
    func_8000A0E0();
    while (func_80006640() & 3) {}
    func_80004A50(0, arg1, arg0, arg2);
    status = func_80006640();
    first16 = status;
    D_80013000 = status;
    if (first16 & 3) {
        do {
            status = func_80006640();
            loop16 = status;
            D_80013000 = status;
        } while (loop16 & 3);
    }
    savedMask = func_80002890(1);
    func_80005350(arg0, arg2);
    func_80005400(arg0, arg2);
    func_80002890(savedMask);
}

/* uso_set_alloc */
extern s32 D_8000A2E0;
void func_80000474(s32 val) {
    D_8000A2E0 = val;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Struct00480Src;

typedef struct {
    s32 unk0;
    s32 unk4;
    Struct00480Src blk; /* 0x8..0x1C: copied wholesale from src */
    s32 unk1C;
} Struct00480Dst;

/* 2026-06-10 kernel-relayout: previous body (field-by-field copy with
 * unk18/unk1C swapped) was a FALSE match - it emitted 13 insns with
 * CSE'd forwarding vs ROM's 14 (verified pre-relayout against a shifted
 * baseline). ROM truth is a 5-word struct assignment (t7/t6-alternating
 * block-copy idiom) + reload of dst->blk.unk8 + zero of unk4. */
void func_80000480(Struct00480Dst* dst, Struct00480Src* src) {
    dst->blk = *src;
    dst->unk1C = dst->blk.unk8;
    dst->unk4 = 0;
}

#ifdef NON_MATCHING
/* func_800004B8: 44-insn handler-table iterator. Walks function table at
 * D_8000A2E0, calling func_80000568(entry, a1_saved) for each entry; on
 * first handler returning 0, calls func_80000880(saved_a0, entry) and
 * returns ptr to D_80012C70[s1].
 *
 * STRUCTURE WITH CROSS-FUNCTION BRANCHES (asm 0x4B8-0x568):
 *   table_base = D_8000A2E0;      // global function table head ptr
 *   v0 = *table_base;             // first table entry
 *   s1 = 0; saved_a0 = a0; saved_a1 = s3 = a1;
 *   if (v0 == NULL) {
 *       s1 = 0; v0 = 0;
 *       goto func_80000568+.L80000570;  // shared epilogue, no s1 update
 *   }
 *   if (v0[0] == NULL) {          // entries[0].first_func == NULL?
 *       s0 = s1 * 20;
 *       goto func_80000568+.L8000056C; // shared epilogue, s1 cleared
 *   }
 *   for (;;) {
 *       a0 = v0[s1*5];            // fetch entry[s1].handler
 *       ret = func_80000568(a0, saved_a1);   // CALL shared trampoline
 *       if (ret != 0) {
 *           s1++; s0 += 20;
 *           a0 = (*table_base)[s1*5];  // next entry handler
 *           if (a0 != 0) continue;     // loop back
 *           // fall through to "no more handlers" exit
 *       }
 *       // ret == 0 (handler signaled stop) or no more entries:
 *       func_80000880(saved_a0, *table_base + s0);  // followup call
 *       v0 = (s32*)((char*)&D_80012C70 + s1*20);    // compute ret ptr
 *       goto func_80000568+.L80000570;  // shared epilogue with v0 set
 *   }
 *
 * SHAPE NOTES:
 *   - 3 cross-function `b/beqz` branches into func_80000568's PREFIX-injected
 *     body: .L80000570 lands at 0x14 (lw ra,0x24(sp)), .L8000056C lands
 *     at 0x10 (or v0,zero,zero). Both resolve correctly post-link because
 *     func_80000568 is in the same .o at known offset.
 *   - The cross-function jump uses `b/beqz <abs_label>` which IDO C-emit
 *     won't reproduce — would need PREFIX_BYTES or asm-processor's
 *     `__asm__("b .Lext")` (IDO rejects per feedback_ido_no_asm_barrier.md).
 *   - 4 saved regs: s0 (s1*20 byte offset), s1 (entry index), s2 (table
 *     base ptr cache), s3 (saved a1). Plus 3 caller-arg spills at
 *     sp+0x28/0x2C/0x30 (a0, a1 dead, a2 dead).
 *
 * Cap: ~40-50% structural — control-flow shape can't be reproduced from
 * standard C due to cross-function branches. Could potentially use the
 * PREFIX_BYTES + INSN_PATCH combo if .L8000056C / .L80000570 land on
 * fixed offsets and the C body's natural emit can be "wrapped" with
 * leading prefix that handles the 0x4F0/0x4F4/0x504/0x548 branches
 * directly. Deferred — current structure documents the algorithm. */
extern s32 D_80012C70[];
extern int func_80000880();
extern s32 func_80000568();

s32 *func_800004B8(s32 a0, s32 a1, s32 a2) {
    s32 s1 = 0;
    s32 *v0;
    s32 *entry;
    (void)a2;  /* spilled at sp+0x30 but never reloaded — dead spill */

    v0 = (s32*)D_8000A2E0;
    if (v0 == NULL) {
        return NULL;
    }
    entry = (s32*)v0[0];
    if (entry == NULL) {
        return NULL;
    }
    {
        s32 (*shared_epilogue)(s32, s32) = (s32(*)(s32,s32))func_80000568;
        do {
            s32 ret = shared_epilogue(entry[s1*5], a1);
            if (ret == 0) {
                func_80000880(a0, &(((s32*)D_8000A2E0)[s1*5]));
                return &D_80012C70[s1*5];
            }
            s1++;
        } while (((s32*)D_8000A2E0)[s1*5] != 0);
    }
    return NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800004B8);
#endif

/* Cross-function shared-epilogue-return-0 stub. 9 insns:
 *   nop; or v0,zero,zero; lw ra,0x24(sp); lw s0,0x14(sp); lw s1,0x18(sp);
 *   lw s2,0x1C(sp); lw s3,0x20(sp); jr ra; addiu sp,+0x28
 *
 * 4 callers (`func_800004B8`, `func_800008F0`, `func_80000A98`,
 * `uso_find_file`) `jal func_80000568` to share this "pop my 0x28 frame
 * and return 0" sequence. The function lacks a prologue and walks the
 * CALLER's saved s0-s3/ra slots — unreproducible from standard C since
 * any function definition emits its own prologue.
 *
 * NATURAL CEILING: empty-stub C body emits only `jr ra; nop` (2 insns /
 * 8 bytes) but the target shape walks the CALLER's saved s0-s3/ra slots
 * and is 9 insns / 36 bytes. The function has no prologue — any C
 * function definition emits its own prologue, so this shape is
 * unreproducible from standard C. Was previously documented as
 * "Promotion via PREFIX_BYTES + INSN_PATCH combo (3rd application after
 * 7ABC and 7A98)" — the instruction-injecting PREFIX_BYTES form
 * (prologue-stealing) plus INSN_PATCH overwriting trailing nop with
 * `addiu sp,sp,+0x28` was REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy; only genuine all-zero
 * SUFFIX_BYTES, USO-header PREFIX_BYTES, and TRUNCATE_TEXT remain).
 * docs/POST_CC_RECIPES.md is deprecated.
 *
 * Type signature is `void` here but callers declare/expect
 * `s32 func(s32, s32)` — runtime $v0=0 from the target's
 * `or v0,zero,zero` is the actual return value. Args ignored. Default
 * build is INCLUDE_ASM. */
#ifdef NON_MATCHING
s32 func_80000568() { return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);
#endif

/* uso_stub_ret0 */
s32 func_8000058C(s32 arg0) {
    return 0;
}

/* Byte-copy loop, 16 insns / 0x40 in target. Tightened wrap (14 insns / 0x38,
 * verified standalone IDO -O2) — was previously 30 insns / 0x78 (+52 bytes
 * bloat). Body now matches target's structure (post-decrement do-while with
 * `bnez count, loop; addiu count, -1` epilogue) — still 2 insns short of
 * target's 16:
 *   - missing `or $a3, $a2, $zero` snapshot at top (count snapshot, dead —
 *     a3 is overwritten in loop). Standard `register s32 cp = count;` doesn't
 *     emit it because IDO sees no use post-loop.
 *   - missing `or $a0, $v0, $zero; lbu t, 0(a0)` 2-insn snapshot+load (target
 *     pattern). My emit folds to `lbu a0, 0(v0)` (1-insn direct).
 * Also target uses (a3=dst-snap, a1=count-snap dead); my emit picks
 * (a1=dst-snap, a3=rem-snap). Register-pick diff inside the snapshots.
 *
 * 2026-05-06 retry: tried explicit `register` qualifiers on every local
 * (sp/dp/cp/p/q/rem/c) + `do { ... rem = count--; } while (rem != 0)`
 * post-decrement form to shape the loop epilogue. Got correct loop tail
 * (bnez+addiu in delay slot) but couldn't restore the dead snapshots —
 * IDO's DCE removes any local that isn't read post-assignment, even with
 * `register` and `(void)` casts.
 *
 * Cap class likely INSN_PATCH (target +2 dead ors over my body) or shaped
 * by a different inlining/calling convention not reproducible from std C.
 * The 2 dead `or` insns suggest the original was a hand-written byte-copy
 * (CRT/libc-style) where the dead ARGV-passthrough ors are remnants of
 * an inline-tail-call ABI dance. Stays NM.
 *
 * 2026-05-17: was previously promoted to exact via PREFIX_BYTES +
 * INSN_PATCH + SUFFIX_BYTES_FORCE — all three instruction-injecting
 * mechanisms REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy; only genuine all-zero
 * SUFFIX_BYTES, USO-header PREFIX_BYTES, and TRUNCATE_TEXT remain).
 * Reverted to "stays NM" — default build is INCLUDE_ASM.
 *
 * 2026-05-31 PERMUTER TRIED (was un-tried; now ruled out): the residual is
 * a SIZE mismatch — target keeps 2 redundant `or` ABI-dance moves (16 insns,
 * no frame) that -O2 coalesces (mine=14) while -O1 ADDS a frame (18 insns).
 * decomp-permuter -j2 ~200s FLOORED at score ~230 (base 310), NEVER reached
 * 0 — finds closer variants but no C structure reproduces the exact 2
 * redundant moves at -O2-no-frame. Genuine redundant-move/size cap; not
 * permuter-crackable. (Kernel = non-asm-processor so the permuter runs
 * cleanly here, unlike the game_libs asm-processor floor.) */
#ifdef NON_MATCHING
void func_80000598(u8* src, u8* dst, s32 count) {
    register u8* sp;
    register u8* dp;
    register s32 cp;
    register u8* p, *q;
    register s32 rem;
    register u8 c;
    cp = count;
    sp = src;
    dp = dst;
    (void)cp;
    if (count == 0) return;
    count--;
    do {
        p = sp;
        c = *p;
        q = dp;
        rem = count;
        dp++;
        sp++;
        *q = c;
        rem = count--;
    } while (rem != 0);
}
#else
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_80000598)();
void func_80000598(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 var_a2;
    u8 *temp_a3;
    u8 *var_v0;
    u8 *var_v1;
    u8 temp_t6;

    var_v0 = arg0;
    var_v1 = arg1;
    var_a2 = arg2 - 1;
    if (arg2 != 0) {
        do {
            temp_t6 = *var_v0;
            temp_a3 = var_v1;
            var_v1 += 1;
            var_v0 += 1;
            *temp_a3 = temp_t6;
            var_a2 -= 1;
        } while (var_a2 != 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);
#endif
#endif

/* func_800005DC: 44-insn (0xB0) DMA-aligned bounded read helper.
 * Splat-split into 3 fragments: 800005DC (0x34, 13 insns) + 8000060C
 * (0x54, 21 insns) + 80000660 (0x28, 10 insns). All three share one
 * stack frame (addiu sp,-0x20 at 800005D8 prologue + lw ra,addiu sp at
 * 80000678 epilogue inside the third fragment).
 *
 * Decoded body (initial structural pass 2026-05-05):
 *
 *   s32 fread_aligned(void *buf, u32 count, u32 chunkSize, FileState *file) {
 *       s32 total;
 *       if ((u32)buf & 7) {
 *           D_80013004 = -0x1C;       // misaligned destination → set errno-style
 *           return 0;
 *       }
 *       total = count * chunkSize;     // multu $a1, $a2
 *       if (file->[0x1C] < file->[0x4] + total) {
 *           total = file->[0x1C] - file->[0x4];   // clamp to remaining
 *       }
 *       if (total < 0) return 0;        // bgez $a2 path
 *       if (total != 0) {
 *           D_80012C40(buf, count, file->[0xC] + file->[0x4]);  // indirect read fn
 *       }
 *       file->[0x4] += total;          // advance pos
 *       return total;
 *   }
 *
 * Field interpretation (FileState ~0x20+ bytes):
 *   [0x4]  s32 pos          (current read position)
 *   [0xC]  void *buf        (file's data buffer base)
 *   [0x1C] s32 capacity     (max bytes accessible)
 *
 * Globals:
 *   D_80013004: errno-style status word
 *   D_80012C40: indirect-call read function pointer (DMA-style)
 *
 * Cross-fragment merge BLOCKED on the same .s-file split as
 * func_80006698 / func_80008430 (linker layout shift if .s files are
 * concatenated). Wrap is for grep discoverability + structural seed; the
 * default INCLUDE_ASM build remains exact. Multi-tick refinement target. */
#ifdef NON_MATCHING
extern s32 D_80013004;
typedef s32 (*ReadFunc)(void *, u32, void *);
extern ReadFunc D_80012C40;
typedef struct {
    s32 pad0;
    s32 pos;     /* +0x4 */
    s32 pad8;
    void *buf;   /* +0xC */
    s32 padN[3];
    s32 capacity; /* +0x1C */
} FileStateRdr;
s32 func_800005DC(void *buf, u32 count, u32 chunkSize, FileStateRdr *file) {
    s32 total;
    if (((u32)buf & 7) != 0) {
        D_80013004 = -0x1C;
        return 0;
    }
    total = (s32)(count * chunkSize);
    if (file->capacity < (s32)(file->pos + total)) {
        total = file->capacity - file->pos;
    }
    if (total < 0) return 0;
    if (total != 0) {
        D_80012C40(buf, count, (char*)file->buf + file->pos);
    }
    file->pos += total;
    return total;
}
#else
/* 3-fragment merge complete: func_800005DC + func_8000060C + func_80000660
 * -> single 0xB0 (44-insn) function with 2 alabels (60C at offset 0x34,
 * 660 at offset 0x88) preserving cross-callers.
 *
 * Branches that previously crossed fragment boundaries (b .L80000678 from
 * 5DC and 60C, beqz .L8000066C from 60C) now land in the single merged
 * file's .L labels. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
/* Bounded read/transfer: require arg0 (handle/addr) 8-aligned (else errno
 * D_80013004 = -0x1C). Compute requested size arg1*arg2, clamp to the stream's
 * remaining (limit unk1C - position unk4); if nothing left return 0. Otherwise
 * DMA via the D_80012C40 ReadFunc (handle, buf=unkC+pos, size), advance the
 * position (unk4 += size), and return the bytes transferred. */
s32 func_800005DC(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 var_a2;
    s32 var_v1;
    u32 temp_a0;

    if (arg0 & 7) {
        D_80013004 = -0x1C;
        return -0x1C;
    }
    var_v1 = FW(arg3, 4);
    temp_a0 = *(u32 *)((char *)arg3 + 0x1C);
    var_a2 = arg1 * arg2;
    if (temp_a0 < (u32) (var_a2 + var_v1)) {
        var_a2 = temp_a0 - var_v1;
    }
    if (var_a2 < 0) {
        return 0;
    }
    if (var_a2 != 0) {
        D_80012C40((void *) arg0, (u32) (FW(arg3, 0xC) + var_v1), (void *) var_a2);
        var_v1 = FW(arg3, 4);
    }
    FW(arg3, 4) = var_v1 + var_a2;
    return var_a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800005DC);
#endif
#endif

/* uso_advance_position */
void func_80000688(s32* file, s32 offset) {
    file[1] += offset;
}

s32 uso_file_open(FileState* file, u32* arg1) {
    struct {
        u32 type;
        u32 size;
        u32 unk8;
        s32 pad;
    } header;

    if (func_800009D8(&header, 0xC, 1, file) < 0) {
        return D_80013004;
    }
    if (header.type == 0xA) {
        return 0;
    }
    if (func_800009D8(arg1, header.size, 1, file) < 0) {
        return D_80013004;
    }
    if (*arg1 != 0x12345678) {
        return -0x15;
    }
    return 1;
}

/* uso_skip_to_end: reads USO section headers until End (type 11).
 *
 * CRACKED 2026-06-11 (rules sweep wave 2, 100.0): the bnel operand-order
 * "cap" was ucode shape, not emit normalization. uoptinput.c swaps ==/!=
 * operands when the LEFT operand is not an isvar at READ time. A local
 * ARRAY element (header[0]) reads as lda+ilod (isop) -> always swapped
 * to const-first (bnel s3,t0). A local STRUCT FIELD (header.type) reads
 * as a direct var ref (isvar) -> no swap -> var-first (bnel t0,s3).
 * So the original buffer is a 3-word STRUCT, not u32[3]. Same emitted
 * bytes everywhere else (escaped local -> conservative temp reloads). */
s32 uso_skip_to_end(FileState *file)
{
  s32 pad;
  struct { u32 type; u32 size; u32 x; } header;
  s32 new_var;
  do
  {
    new_var = func_800009D8(&header, 12, 1, file);
    pad = header.type;
    if (new_var < 0)
    {
      return D_80013004;
    }
    if (8 != pad)
    {
      ((s32 *) file)[1] += header.size;
    }
  }
  while (header.type != 11);
  return 0;
}


/* uso_file_check — always returns 1 (success) */
s32 func_800007C4(s32 a0, s32 a1) {
    return 1;
}

typedef struct {
    char pad_00[0x14];
    s32 field_14;
    char pad_18[0x34];
    s32 field_4C;
    char pad_50[0x22];
} UsoEntry74;

typedef struct {
    char pad_00[0x84];
    void (*field_84)(void*, void*, s32, s32);
} UsoCallbacks84;

extern s32 D_8000A2E4;
extern s32 D_80012F7C;

#ifdef NON_MATCHING
/* Logic-exact NM. Iterate a fixed table of entry pointers
 * (D_80012D60 .. D_80012F7C); for each non-NULL entry dispatch the callback
 * at D_80012BC0 + 0x84 with (arg0, &entry[0x72], field_4C, field_4C+field_14).
 *
 * SINGLE residual = IDO -O2 register-allocation cap (verified 2026-06-23,
 * decl-order sweep + 480s permuter / multiple variants, none reached 0).
 * Target saves FOUR callee-saved s-regs and hoists all four loop-invariant
 * base pointers: s0=D_80012D60(p), s1=D_8000A2E4(arg0), s2=D_80012BC0(state),
 * s3=D_80012F7C(end) — `lui` order p/arg0/state/end (decls below mirror it),
 * `addiu` order reversed. It then loads the callback via `lw $t9,0x84($s2)`.
 *
 * This build saves only THREE s-regs (s0/s1/s2) and leaves `state` in a
 * caller-saved temp: `lui $t9; lw $t9,0x84($t9)` rematerialized per iter.
 * Cause: `state`'s live range dies before the `jalr` (it is read only to
 * fetch the function pointer into t9), so -O2 declines callee-save promotion
 * for it and keeps end+arg0 instead. The `addu $a3,$a2,$t6` vs `$t6,$a2`
 * operand-order diff is downstream of the same allocation (IDO canonicalizes
 * the commutative add by allocated-reg order, not by C source order — verified
 * both `off+field_14` and `field_14+off` emit `t6,a2`).
 *
 * No semantics-preserving C reshaping promotes a 4th callee-saved invariant
 * whose range dies pre-call. Genuine -O2 coloring cap, not C-source-reachable. */
void func_800007D4(void) {
    register UsoEntry74 **p = (UsoEntry74**)&D_80012D60;
    register void *arg0 = &D_8000A2E4;
    register UsoCallbacks84 *state = (UsoCallbacks84*)&D_80012BC0;
    register UsoEntry74 **end = (UsoEntry74**)&D_80012F7C;

    do {
        UsoEntry74 *e = *p;
        if (e != 0) {
            s32 off = e->field_4C;
            state->field_84(arg0, (char*)e + 0x72, off, off + e->field_14);
        }
        p++;
    } while (p != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800007D4);
#endif

typedef struct {
    char pad_00[0x94];
    s32 field_94;
} UsoTable94;

extern s32 D_8000A2F4;

/* NON_MATCHING: traversal is correct, but the callback argument setup still
 * compiles with the wrong register pairing for `var_s0` and `var_s2`. */
#ifdef NON_MATCHING
void func_8000085C(void) {
    s32 var_s0;
    UsoTable94* var_s1;
    void* var_s2;
    void* arg0;
    UsoCallbacks84* state;
    s32 end;

    var_s1 = (UsoTable94*)0x800130A0;
    var_s2 = (void*)0x80013112;
    arg0 = &D_8000A2F4;
    state = (UsoCallbacks84*)&D_80012BC0;
    var_s0 = 0;
    end = 0x87;
    do {
        state->field_84(arg0, var_s0, var_s1->field_94, var_s2);
        var_s0 += 1;
        var_s1 = (UsoTable94*)((char*)var_s1 + 0x9C);
        var_s2 = (char*)var_s2 + 0x9C;
    } while (var_s0 != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000085C);
#endif



#ifdef NON_MATCHING
/* func_800008F0: 58-insn iterator over a 135-entry table at D_80012D60.
 * Sibling caller of func_80000568 (the shared-epilogue stub).
 *
 * STRUCTURE (asm 0x8F0-0x9D8):
 *   1. Calls indirect fn-ptr D_80012C44(D_8000A300, a0).
 *   2. Calls func_80000660(a0, &D_80012FC0, &D_80012F80) — 3-arg helper.
 *   3. Outer loop: s2 = 0; while (s2 != 0x87 = 135):
 *        entry = D_80012D60[s2];
 *        if (entry == NULL) goto skip;
 *        ret = func_80000568(D_80012F80, entry + 0x72);  // shared trampoline
 *        if (ret == 0) {
 *            entry->[0x98] = 0;          // sb byte clear
 *            D_80012D60[s2] = NULL;
 *            // Inner cleanup loop (0x990-0x9B4): scan D_80012D60 entries
 *            // 0..0x86 (135) again:
 *            //   if (e != NULL) { func_800021D0(e, s2); func_8000275C(e, s2); }
 *            return 0;
 *        }
 *      skip: s2++;
 *   4. Falls through to return 0.
 *
 * 4th caller of `func_80000568(D_80012F80, entry+0x72)` — uses the
 * shared cross-function trampoline whose recipe ($v0=0 via PREFIX) was
 * just landed (see func_80000568 wrap doc).
 *
 * Cap: ~30-50% structural — cross-function jal works cleanly via fn-ptr
 * cast, but matching nested-loop `bnel` shapes and 4-saved-reg allocation
 * is hard. Documented body captures algorithm; default build INCLUDE_ASM. */
extern s32 D_8000A300;
extern s32 D_80012F80;
extern s32 D_80012FC0;
extern s32 func_800021D0();
extern s32 func_8000275C();
extern s32 D_8000A314;
extern s32 D_8000A328;
extern s32* func_800008B8(void*, void*, void*);
extern s32 func_80000A98();

s32 func_800008F0(s32 a0) {
    s32 s2;
    s32 (*shared_epilogue)(s32, s32) = (s32(*)(s32,s32))func_80000568;
    void (*helper660)(s32, s32*, s32*) = (void(*)(s32, s32*, s32*))func_80000660;

    D_80012C44((void*)&D_8000A300, (void*)a0);
    helper660(a0, &D_80012FC0, &D_80012F80);
    for (s2 = 0; s2 != 0x87; s2++) {
        s32 *entry = (s32*)D_80012D60[s2];
        if (entry == NULL) continue;
        if (shared_epilogue((s32)&D_80012F80, (s32)entry + 0x72) == 0) {
            s32 i;
            *((u8*)entry + 0x98) = 0;
            D_80012D60[s2] = 0;
            for (i = 0; i < 0x87; i++) {
                s32 *e = (s32*)D_80012D60[i];
                if (e != NULL) {
                    func_800021D0(e, s2);
                    func_8000275C(e, s2);
                }
            }
            return 0;
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800008F0);
#endif

/* func_800009D8 (5-insn shared-tail epilogue: lw s1/s2/s3, jr ra, addiu sp,+0x28)
 * merged into predecessor func_8000098C (size 0x4C → 0x60). Address re-exported
 * via undefined_syms_auto.txt for the many cross-jal callers (kernel_000.c
 * line 383, 389, 409, etc.). */
#ifdef NON_MATCHING
/* func_800009EC: front block for the USO module loader tail at func_80000A88 /
 * func_80000A98. Boundary check: this symbol has no jr-ra and branches to
 * func_80000A98's epilogue label, while both 80000A88 and 80000A98 are also
 * standalone jal targets. That makes a merge unsafe per
 * docs/PATTERNS.md#feedback-contiguous-fragment-can-be-alt-entry-check-extern-first
 * and docs/PATTERNS.md#feedback-dual-role-tail-and-callable.
 *
 * Decoded front semantics:
 *   - reset pending module/function indexes to -1
 *   - call the registered loader callback with D_8000A314 and the file
 *   - clear two fields in D_80012BC0, then prime D_80012FC0/D_80012F80
 *   - read a range descriptor into the stack header buffer
 *   - on failure, return -17 through func_80000A98's shared epilogue
 *   - on success, seed D_8000A2D8/D_8000A2DC and fall through to 80000A98
 *
 * Natural C has to model the final fall-through as a call to the continuation,
 * so the default byte-correct build stays INCLUDE_ASM. */
s32 func_800009EC(s32 file) {
    s32 header[12];
    s32 *range;

    D_80012C64 = -1;
    D_80012C68 = -1;
    D_80012C44(&D_8000A314, (void*)file);

    ((s32*)&D_80012BC0)[6] = 0;
    ((s16*)&D_80012BC0)[0x16] = 0;

    func_80000660(file, &D_80012FC0, &D_80012F80);
    range = func_800008B8(header, &D_80012FC0, &D_8000A328);
    if (range == 0) {
        return -17;
    }

    D_8000A2D8 = range[0];
    D_8000A2DC = range[1];
    return func_80000A98();
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800009EC);
#endif

#ifdef NON_MATCHING
/* func_80000A88: 4-insn alt-entry preamble for func_80000A98.
 *
 * Body: `lui at, %hi(D_8000A2D8); lui s1, 0x8001; sw t6, %lo(D_8000A2D8)(at);
 *        lw t7, 0x4(v0)` — NO prologue, NO jr ra, falls through into
 * func_80000A98 (124-insn body). Caller's $ra survives to A98's epilogue.
 *
 * The asm reads $v0 and $t6 from the caller's state (carried over from
 * `lw t6, 0(v0)` at the tail of func_800009EC) and primes $s1 with the
 * high-half of 0x80010000 (used as a base reg in A98's body). Same cap
 * class as `tail-fall-through alt-entry preamble` documented in
 * docs/MATCHING_WORKFLOW.md#feedback-tail-fall-through-alt-entry-preamble.
 *
 * Caller (func_80001348) uses `func_80000A88(file, header[1])` 2-arg
 * signature, but the asm body doesn't honor $a0/$a1 — those args flow
 * into A98's body, not A88's preamble. This is a hidden alt-entry that
 * also serves as a regular jal target (jal at func_800013D0).
 *
 * Cap: standard C cannot produce 4 insns with no jr ra that read
 * caller's $v0/$t6 directly. Match paths:
 *  - TRUNCATE_TEXT + INSN_PATCH writing the 4 insn words manually
 *  - merge-fragments combining A88+A98 into a single 128-insn function
 *    (would change A88's standalone-callable shape)
 *  - inline asm at the call site triggering this preamble
 *
 * Default INCLUDE_ASM path produces correct bytes via the asm file. */
void func_80000A88(void *p, s32 v) {
    /* Decoded only as documentation — see comment above. The 4 insns
     * cannot be expressed in standard C without altering the function's
     * external-call signature or its no-jr-ra fall-through shape. */
    (void)p;
    (void)v;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A88);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A98);

/* uso_call_init — dispatches a function from the USO module vtable */
typedef s32 (*UsoFunc)(void*);

s32 func_80000C88(void) {
    s32 modIndex = D_80012C68;
    s32* mod;
    s32 funcIndex;
    s32 funcTable;

    if (modIndex < 0) {
        return -1;
    }

    mod = (s32*)D_80012D60[modIndex];
    if (mod == 0) {
        return -1;
    }

    funcIndex = D_80012C64;
    if (funcIndex < 0) {
        return -1;
    }

    funcTable = *(s32*)((char*)mod + 0x3C);
    if (funcTable == 0) {
        return -1;
    }

    {
        /* (t = funcTable) assignment-expr pins funcTable as the addu rs
         * (ROM: addu t8,a2,t7) - docs/IDO_CODEGEN integer commutative
         * operand-order lever; plain source-order swap does not flip it.
         * (2026-06-10 kernel relayout audit; was the last kernel_000
         * non-reloc word diff.) */
        s32 t;
        UsoFunc fn = (UsoFunc)*(s32*)((t = funcTable) + funcIndex * 12 + 4);
        D_80012BE4 = fn(&D_80012BC0);
    }
    return 0;
}

/* func_80000D2C: name-lookup. If D_80012D60[id] is set, strcpy its name (at
 * +0x72) into out and return 2. Else iterate the D_8000A2E0 list (0x14 stride):
 * for each entry, enumerate via func_80000880/func_80000A98; on an entry whose
 * +0x4 field == id, copy its name (func_800005DC, src=entry+0xC) and return 1;
 * func_80000B34<0 aborts with D_80013004. Logic-complete, size-exact NM wrap
 * (75/75 insns, ~83%). The merged-TU 2-arg-call-vs-4-arg-def conflict on
 * func_800005DC (which forced a cast emitting lui+addiu+jalr) is solved via an
 * alias symbol (DSC, below) → direct jal. Residual (not yet matched): frame is
 * 0x98 vs target 0x90 (an 8-byte spill/temp slot this C structure allocates and
 * the target doesn't), the entry+0x4==id test canonicalizes to swapped bne
 * operands, and the list-continue flag lands in v1 vs target t3.
 * 2026-05-31 TOOL ATTEMPTS (all failed, don't repeat): (1) permuter 28k iters
 * "improved" to score 15 but its scorer NORMALIZES sp-offsets, so it's BLIND to
 * the frame-size diff (the dominant blocker) and actually GREW the frame to 0xA0
 * — permuter cannot crack a frame-size cap here; (2) `c = tbl[i+0x72]` in the
 * strcpy (vs re-reading D_80012D60[id]) REGRESSES to 72 diffs — the target
 * genuinely re-reads, original is correct; (3) swapping the bne operands
 * (`id == *(entry+4)`) is a NO-OP — IDO normalizes operand order ($s-first),
 * same cap as uso_skip_to_end. So this fn is IDO-emit-blocked from C regardless
 * of the frame; not permuter-crackable (scorer blind spot). */
extern s32 func_8000098C(void*);
extern s32 func_80000B34(void*);
/* func_800005DC is defined 4-arg earlier in this merged TU; call it 2-arg here
 * via an alias symbol (undefined_syms_auto.txt: func_800005DC_d2c = 0x800005DC)
 * so the redecl is legal and emits a direct jal (not the cast's lui+addiu+jalr).
 * See docs/MATCHING_WORKFLOW.md#feedback-alias-extern-via-undefined-syms. */
extern s32 func_800005DC_d2c(void*, void*);
#define DSC func_800005DC_d2c
#ifdef NON_MATCHING
s32 func_80000D2C(u8 *out, s32 id) {
  u8 iter[0x2C];
  s32 new_var3;
  u8 entry[0x2C];
  u8 *new_var;
  s32 *list;
  u8 *tbl;
  s32 i;
  u8 new_var2;
  u8 c;
  tbl = (u8 *) D_80012D60[id];
  new_var = tbl;
  list = (s32 *) D_8000A2E0;
  if (new_var != ((void *) 0))
  {
    c = new_var[0x72];
    i = 0;
    out[0] = c;
    if (c != 0)
    {
      do
      {
        i++;
        c = ((u8 *) D_80012D60[id])[i + 0x72];
        out[i] = (new_var2 = c);
      }
      while (c != 0);
    }
    return 2;
  }
  if ((*list) != 0)
  {
    do
    {
      func_80000880(iter, list);
      if (func_80000A98(iter, entry) != 0)
      {
        do
        {
          if (1)
          {
            new_var3 = *((s32 *) (entry + 0x4));
          }
          if (new_var3 == id)
          {
            func_800005DC_d2c(out, entry + 0xC);
            return 1;
          }
          if (func_80000B34(iter) < 0)
          {
            return D_80013004;
          }
        }
        while (func_80000A98(iter, entry) != 0);
      }
      func_8000098C(iter);
      i = *((s32 *) (((u8 *) list) + 0x14));
      list = (s32 *) (((u8 *) list) + 0x14);
    }
    while (i != 0);
  }
  return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000D2C);
#endif

void func_80000E58(void) {
    D_80012C44(&D_8000A32C, &D_8000A340);
}

extern s32 D_8000A344;
/* Address -> loaded-USO resolver: scan the USO slot-pointer table
 * (&D_80012D60 .. &D_80012F7C); for the first loaded slot whose
 * [field_4C, field_4C+field_14) range contains arg0, return its code base
 * (slot+0x72) and the in-USO offset (arg0 - field_4C). Not found -> &D_8000A344
 * / 0. IDO -O2 unrolls the simple slot loop x4 with a 3-iteration prologue.
 * The `tbl` decl inside the loop body is load-bearing: it makes IDO recompute
 * the table base each iteration (matching the target's coloring exactly). */
void func_80000E8C(u32 arg0, void **arg1, s32 *arg2) {
    s32 i;

    for (i = 0; i < 135; i++) {
        UsoEntry74 **tbl = (UsoEntry74 **) &D_80012D60;
        UsoEntry74 *e = tbl[i];
        if (e != NULL) {
            if ((arg0 >= (u32) e->field_4C) && (arg0 < (u32) (e->field_4C + e->field_14))) {
                *arg1 = (char *) e + 0x72;
                *arg2 = arg0 - e->field_4C;
                return;
            }
        }
    }
    *arg1 = &D_8000A344;
    *arg2 = 0;
}

/* uso_get_vtable — returns pointer to USO vtable */
extern s32 D_80012BC0;
void* func_800010B4(void) {
    return &D_80012BC0;
}

/* uso_set_callbacks (no-op) */
void func_800010C0(s32 a0, s32 a1) {
}

void func_800010CC(s32 a0, ...) {
}

extern s32 D_8000A34C;
extern s32 D_8000A35C;
extern s32 D_8000A2A0;
extern s32 D_80012D30;

#ifdef NON_MATCHING
/* Logic-correct decode of the D_80012BC0+0x84 logger-dump family
 * (SIBLING of func_800007D4 / func_8000085C). Hits func_800007D4's
 * exact documented -O1 cap (see its NM comment, "state isn't getting
 * $s-promoted ... build inlines lui+lw per iter; target uses
 * lw 0x84(s2) with s2=state"): my build emits lui+lw of the absolute
 * D_80012BC0 address per call and allocates 4 s-saves (s0/s1/s2/s3,
 * frame -0x28) while the target keeps state in s2, reloads
 * lw t9,0x84(s2), and uses 5 s-saves (s0-s4, frame -0x30) with s4
 * holding `end` (&D_80012D5C). The state-pointer CSE/promotion is an
 * IDO -O1 codegen choice not reachable from C source (same as the
 * sibling). Logic verified correct vs asm.
 * Struct-typing: prints &D_8000A34C with arg D_80012D5C once, then
 * walks parallel s32 tables D_80012D30[] (values) and D_8000A2A0[]
 * (values), 11 entries (D_80012D30..D_80012D5C), calling the
 * UsoCallbacks84.field_84 logger(&D_8000A35C, D_8000A2A0[i],
 * D_80012D30[i]) per entry. */
void func_800010E8(void) {
    register s32 *p0 = &D_80012D30;
    register s32 *p1 = &D_8000A2A0;
    register UsoCallbacks84 *state = (UsoCallbacks84*)&D_80012BC0;
    register void *fmt2 = &D_8000A35C;
    register s32 *end = &D_80012D5C;

    (*(void (**)())((char*)state + 0x84))(&D_8000A34C, D_80012D5C);
    do {
        (*(void (**)())((char*)state + 0x84))(fmt2, *p1, *p0);
        p0++;
        p1++;
    } while (p0 != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800010E8);
#endif

extern s32 D_80012D30;
extern s32 D_80012D34;
extern s32 D_80012D38;
extern s32 D_80012D3C[];
extern s32 D_80012D5C;
extern s32 D_80012D5C_alias; /* distinct extern @ 0x80012D5C: breaks store<->end CSE */

#ifdef NON_MATCHING
/* NON_MATCHING: target uses a fixed 2-iter pointer loop with no zero-guard.
 * The current explicit-goto loop avoids IDO's bulk-unroll transform and emits
 * the target-sized 0x4C body, but initialization scheduling/register selection
 * still differs: IDO combines the D_80012D5C zero-store with the end pointer
 * load, while target emits a direct $at store first and reloads the end later.
 * Current score: 72.10526% (objdiff, 2026-05-08).
 *
 * Earlier structural variants tried: do-while, for(i<8), explicit end pointer,
 * 8-way unroll, same-array `end = D_80012D3C + 8`; these produced IDO's
 * subu+andi guard plus bulk-unrolled loop instead of the compact target loop.
 *
 * 2026-05-04: 5th variant attempt was `end = D_80012D3C + 8` to make the
 * end-bound a same-array compile-time-known-multiple-of-16 offset. IDO
 * STILL emits the duplicate-loop + guard. Confirms the auto-unroll +
 * guard isn't keyed on whether bounds are extern-vs-array-derived; it's
 * purely the loop-shape that triggers it. Cap unchanged.
 *
 * 2026-05-06: 6th variant attempt added an unused iteration counter `i`
 * (incremented inside the loop body) to add another phi-target that might
 * change the loop-shape detection. No effect on auto-unroll — same cap.
 * The auto-unroll trigger is more fundamental than the loop's variable
 * count; likely tied to detecting a constant trip count from the
 * extern-pointer bounds, which IDO sees through.
 *
 * 2026-05-08: 7th variant changed the loop to byte pointers with a 0x10
 * stride; no effect, same guarded bulk-unroll as the s32* loop. 8th variant
 * changed the loop to an explicit label/goto; this is kept because it removes
 * the guard/unroll and matches the target size, leaving only the init-order
 * and v0/v1 allocation differences.
 *
 * 2026-05-08 (later) 9th variant: tried `extern int D_80012D30[2]` to merge
 * D_80012D30 + D_80012D34 into a shared-base array. IDO emitted ONE shared
 * `lui a0; addiu a0` for the array base instead of fresh lui per element
 * — partial regression toward target shape — but TARGET uses `$at` as the
 * shared base (`lui at; sw zero, %lo($at); sw zero, %lo+4($at)` — IDO's
 * compact extern-store form), not `$a0`. Array form picks `$a0` because
 * it's a regular C local; the at-form is the single-insn-store recipe IDO
 * uses for naked `*(int*)&extern = 0` only when no addiu pre-add is
 * required. To force at-form for adjacent-extern stores, write each as
 * `(*(int*)&D_NAME) = 0` with NO array indexing. Reverted (no improvement
 * over baseline).
 *
 * 2026-05-08 (later2) 10th variant: explicit `*(s32*)&D_80012D5C = 0` casts
 * + swapped end/ptr declaration order (end first). No effect — IDO still
 * CSEs the &D_80012D5C between the naked-store and the `end = &...`
 * assignment. Same 20-insn diff as 8th variant baseline. Cap holds.
 * Kept anyway — the explicit-cast form is closer in style to target's
 * naked-store pattern and may help future attempts read the diff.
 *
 * 2026-05-13 11th variant: `end = D_80012D3C + 8` instead of `end = &D_80012D5C`.
 * BIG WIN: 72.10% -> 81.58%. The pointer-arithmetic expression breaks IDO's
 * CSE between the D_80012D5C naked-store and the end-pointer load, so the
 * prologue now emits `lui at; sw 0(at)` (2 insns, matching target) instead
 * of `lui v1; addiu v1; sw 0(v1)` (3 insns with $v1 CSE). The
 * `end = D_80012D3C + 8` expression doesn't reference D_80012D5C
 * syntactically, so no CSE opportunity — even though both addresses
 * resolve to the same final VRAM. Remaining diffs: (a) target merges
 * D_80012D30 + D_80012D34 stores under one `lui at` (single insn drop),
 * (b) reg allocation swap — target uses $v1 for ptr (heavy-use) and $v0
 * for end (light-use), opposite of IDO's default priority order. Diff (b)
 * is the dominant cost — IDO's reg-priority formula (refs × loop_depth)
 * always favors ptr for the lower reg #.
 *
 * 2026-05-14 12th variant: removed `#ifdef NON_MATCHING` to test the
 * naked-store + post-decrement-loop body in DEFAULT build (vs prior
 * NM-build measurements). Result: default-build emit is 80 bytes vs
 * target 76 (+4 bytes, 14 diffs concentrated at offsets 0x10-0x48). The
 * extra insn is a 4th `lui $at` for D_80012D38's store (target merges
 * D_80012D30/34 under one $at; built emits four separate lui+sw pairs).
 * INSN_PATCH can't shrink the function size; would need a C variant
 * that forces shared-$at base on two of the four naked stores. The
 * `extern int[2]` array trick picks $a0 (per 9th variant), not $at.
 * No new naked-store form found that triggers $at-base reuse. Reverted.
 *
 * 2026-06-23 13th variant: 81.58% -> 82.11%. Two refinements:
 * (1) Store D_80012D5C via a distinct extern `D_80012D5C_alias` (same
 *     VRAM, via undefined_syms_auto.txt) so the naked $at store no longer
 *     CSEs with `end = &D_80012D5C`. This lets `end` keep the clean
 *     `lui v?; addiu v?` D5C load form AND keeps the prologue store naked
 *     ($at), instead of the earlier `end = D_80012D3C + 8` workaround that
 *     re-derived end from the D3C base (extra lui + addiu N).
 * (2) Compare `end != ptr` (not `ptr != end`) -> `bne v1,v0` operand order
 *     now matches target exactly.
 * Residual = exactly TWO confirmed IDO-7.1 hard caps (verified by direct
 * cc probes of naked/array/struct/ptr-arith forms at -O1/-O2/-O3/mips1/2):
 *   (a) D_80012D34 merge: target emits `lui at,D30; sw 0(at); sw 0(at)[D34]`
 *       (one $at, two stores). IDO 7.1 NEVER reuses $at across naked
 *       absolute stores (always re-`lui at`); any base-sharing form
 *       (array[i]=0 / struct field / ptr-arith) materializes the base in a
 *       GPR (a0/v1) instead of $at. Merged-naked-$at is unreachable here.
 *   (b) reg-renumber: target gives the loop-incremented ptr the HIGHER reg
 *       (v1) and the constant bound `end` the lower (v0); IDO's priority
 *       (refs x loop_depth) always assigns the incremented loop var v0.
 *       Decl-order / assign-order / register hints do not flip it.
 * Both are emit-shape caps, not C bugs. Stays NON_MATCHING. */
void func_80001184(void) {
    s32* ptr;
    s32* end;

    *(s32*)&D_80012D5C_alias = 0;
    *(s32*)&D_80012D30 = 0;
    *(s32*)&D_80012D34 = 0;
    *(s32*)&D_80012D38 = 0;
    ptr = D_80012D3C;
    end = &D_80012D5C;
loop:
    ptr += 4;
    ptr[-4] = 0;
    ptr[-3] = 0;
    ptr[-2] = 0;
    ptr[-1] = 0;
    if (end != ptr) {
        goto loop;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80001184);
#endif

/* uso_find_file(arg0, arg1): load the USO directory (func_80000660(arg0, &D_80012FC0,
 * &D_80012F80)), verify it (func_800008B8(arg1, &D_80012FC0, &D_8000A368) != 0 else
 * return -0x11), then walk a parallel key/record table (stride 0x9C: keys from
 * D_80013112, records from D_800130A0, end D_80018356), comparing each key via a
 * DIRECT `jal func_80000568(key, &D_80012F80)`; on match copy record->[0x94] into
 * arg1->[4], set found, return 0; else -0x11. Logic decoded 2026-05-30 (m2c +
 * hand-trace). ~55% NM. UNLOCK (2026-05-30): func_80000568's decl changed from
 * `void(void)` to `s32 func_80000568()` (callable) so this can DIRECT-`jal` it
 * instead of the jalr-emitting func-ptr cast — that took it 3%->55% (func_80000568
 * stays INCLUDE_ASM/EXACT in the default build; the cast-callers at ~482/886 still
 * compile). 2026-06-23 REWORK (agent-e): residual cut from ~25 to 10 words.
 *   FIXED: return tail now byte-exact — `if (found == 0) return -0x11; return 0;`
 *     emits `or v0,zero,zero / bnez found / nop / b / addiu v0,-0x11` (was a
 *     v1-based bnezl form). The 0-value must be the FALL-THROUGH return so IDO
 *     materializes v0=0 first and tests `bnez found`.
 *   FIXED: pointer-setup lui delay-slot — assigning `p` (D_800130A0) BEFORE `q`
 *     puts `lui s1,%hi(D_800130A0)` in the verify-branch delay slot, matching.
 *   REMAINING (10 words, 3 HARD backend caps — permuter 40k iters never beat
 *     base score 150, exhaustive C-variant grind failed):
 *   (a) FRAME 0x38 vs 0x60 — 0x30 bytes (0x30-0x5C) of UNUSED stack = a ghost
 *       DCE'd address-taken local. Any surviving address-taken local needs an
 *       `addiu reg,sp,off` to materialize the address (=+1 insn, breaks match);
 *       volatile array adds a spurious access. uopt retains the slot WITHOUT any
 *       access only via a pattern no C construct reproduces. (4 words: 1,9,17,55.)
 *   (b) loop-preamble addiu LO order: target emits end(s2)/q(s0)/p(s1), build
 *       emits q/p/end — same coloring, different ugen emission schedule. (2 words.)
 *   (c) found-block scheduler tie: target interleaves `li t6,1; sw t6,found`
 *       BETWEEN the two record/arg1 loads and the deferred store; build does the
 *       const+store first. Same registers (t7/t8/t6), different as1 schedule;
 *       not statement-order-fixable. (4 words.)
 *   Genuine ugen/as1 cap — leave NON_MATCHING. */
#ifdef NON_MATCHING
extern char D_8000A368, D_80013112, D_80018356;
s32 uso_find_file(void *arg0, void *arg1) {
    char *q;
    char *p;
    s32 found;
    func_80000660(arg0, &D_80012FC0, &D_80012F80);
    if (func_800008B8(arg1, &D_80012FC0, &D_8000A368) == 0) {
        return -0x11;
    }
    found = 0;
    p = (char *)&D_800130A0;
    q = &D_80013112;
    do {
        s32 r = func_80000568(q, &D_80012F80);
        q += 0x9C;
        if (r == 0) {
            found = 1;
            ((s32 *)arg1)[1] = *(s32 *)(p + 0x94);
            break;
        }
        p += 0x9C;
    } while (q != &D_80018356);
    if (found == 0) {
        return -0x11;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", uso_find_file);
#endif

/* uso_get_error — returns last error code */
s32 func_800012AC(s32 arg0) {
    return D_80013004;
}

extern void* (*D_80012BF4)(s32, s32);
extern s32 func_800015D0(void*, void*);

/* uso_open_file: alloc 0x28-byte file struct, init via func_800015D0, read
 * 12-byte header. Byte-exact: the `char pad[8]` declared BEFORE `header`
 * makes IDO place header[3] at sp+0x18 (and the 8-byte pad in the 0x24-0x2B
 * gap) to match the target frame layout. */
void* func_800012BC(void* arg0) {
    void* file;
    char pad[8];  /* frame padding to push header to sp+0x18 */
    s32 header[3];

    file = D_80012BF4(0x28, 8);
    if (func_800015D0(arg0, file) < 0) {
        return 0;
    }
    if (func_800009D8(header, 0xC, 1, file) < 0) {
        return 0;
    }
    ((s32*)file)[8] = ((s32*)file)[1];
    ((s32*)file)[7] = header[1] + ((s32*)file)[1];
    return file;
    (void)pad;
}

extern void func_80000A88(void*, s32);

#ifdef NON_MATCHING
/* NON_MATCHING: local stack layout differs from target, so the loop header
 * buffer and file-state fields end up at different offsets and branch layout
 * drifts after the `header[0] == 6` check. */
s32 func_80001348(void* arg0, s32* arg1) {
    s32 file[10];
    s32 header[3];
    s32 result;

    result = func_800015D0(arg0, file);
    if (result < 0) {
        return result;
    }

    while (1) {
        result = func_800009D8(header, 0xC, 1, file);
        if (result <= 0) {
            if (result == 0) {
                result = -1000;
            }
            return result;
        }
        if (header[0] == 6) {
            *arg1 = file[3] + file[1];
            return 0;
        }
        if (header[0] != 8) {
            func_80000A88(file, header[1]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80001348);
#endif

/* uso_read */
s32 func_80001414(void* file, void* buf, s32 size) {
    extern s32 D_80013004;
    extern s32 func_800009D8(void*, s32, s32, void*);
    s32 result;
    result = func_800009D8(buf, size, 1, file);
    if (result < 0) {
        return D_80013004;
    }
    return result;
}

/* uso_file_end — returns file position + size */
s32 func_80001460(s32* file) {
    return file[1] + file[3];
}

/* uso_seek — set or adjust file position */
s32 func_80001470(s32* file, s32 whence, s32 offset) {
    if (whence) {
        file[1] += offset;
    } else {
        file[1] = offset;
    }
    return file[1];
}

/* uso_file_close (no-op) */
void func_80001494(s32 arg0) {
}

/* uso_ret_zero — returns 0.0f */
float func_8000149C(void) {
    return 0.0f;
}

#ifdef NON_MATCHING
/* USO loader main loop: walk the pending-request list (D_8000A2E0, 0x14-byte
 * entries); for each, iterate its USO records (func_80000880 fills a record
 * buffer, func_80000A98 advances + yields the next), and for each valid slot
 * index (sp44 >= 0) read the USO body into D_800130A0[idx] (0x9C-stride slot)
 * via func_800005DC and stamp slot->unk94 from the record. */
void func_800014A8(void) {
    extern s32 func_800005DC();
    u8 sp70[0x28];
    u8 sp4C[0x24];
    u8 sp40[0xC];
    s32 *var_s6;
    s32 temp_t9;
    UsoSlot *temp_s0;

    var_s6 = (s32 *) D_8000A2E0;
    if (*var_s6 != 0) {
        do {
            func_80000880(sp70, var_s6);
            if (func_80000A98(sp70, sp40) != 0) {
                do {
                    if (*(s32 *)(sp40 + 4) >= 0) {
                        temp_s0 = &D_800130A0 + *(s32 *)(sp40 + 4);
                        func_800005DC((char *) temp_s0 + 0x72, sp4C);
                        *(s32 *)((char *) temp_s0 + 0x94) = *(s32 *)(sp70 + 4);
                    }
                    func_80000B34(sp70);
                } while (func_80000A98(sp70, sp40) != 0);
            }
            temp_t9 = *(s32 *)((char *) var_s6 + 0x14);
            var_s6 = (s32 *)((char *) var_s6 + 0x14);
        } while (temp_t9 != 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800014A8);
#endif




void func_800017B4(void) {
}

#ifdef NON_MATCHING
/* NON_MATCHING: the pool-walk body matches well, but the first three singleton
 * flag checks still allocate the base registers differently from target
 * (`v1`/`a0` in build versus direct `t6`/`t8`/`t0` loads with `at` stores). */
void* func_800017BC(void) {
    register u8* var_v1;

    if (D_80013138 == 0) {
        D_80013138 = 1;
        return &D_800130A0;
    }
    if (D_800131D4 == 0) {
        D_800131D4 = 1;
        return &D_8001313C;
    }
    var_v1 = (u8*)&D_80013274;
    if (D_80013270 == 0) {
        D_80013270 = 1;
        return &D_800131D8;
    }
loop_7:
    if (*(u8*)(var_v1 + 0x98) == 0) {
        *(u8*)(var_v1 + 0x98) = 1;
        return var_v1;
    }
    if (*(u8*)(var_v1 + 0x134) == 0) {
        *(u8*)(var_v1 + 0x134) = 1;
        return var_v1 + 0x9C;
    }
    if (*(u8*)(var_v1 + 0x1D0) == 0) {
        *(u8*)(var_v1 + 0x1D0) = 1;
        return var_v1 + 0x138;
    }
    if (*(u8*)(var_v1 + 0x26C) == 0) {
        *(u8*)(var_v1 + 0x26C) = 1;
        return var_v1 + 0x1D4;
    }
    var_v1 += 0x270;
    if (var_v1 != (u8*)&D_800182E4) {
        goto loop_7;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800017BC);
#endif

void func_800018A8(void) {
}

void func_800018B0(void* arg0) {
    s32 i;
    char* ptr;

    *(u8*)((char*)arg0 + 0x99) = 1;
    *(s32*)((char*)arg0 + 0x38) = 0;
    *(s32*)((char*)arg0 + 0x3C) = 0;
    /* 2026-06-10 kernel-relayout: previous do-while form was a FALSE match
     * (v0/v1 swapped + bound/counter pre-header order; verified against a
     * shifted baseline). for-comma-init pins ptr->$v1, bound-before-counter
     * (docs/IDO_CODEGEN.md for-loop comma-init lever). Now byte-exact. */
    for (i = 2, ptr = (char*)arg0 + 8; i != 0xE; ) {
        i += 4;
        *(s32*)(ptr + 0x38) = 0;
        *(s32*)(ptr + 0x3C) = 0;
        *(s32*)(ptr + 0x40) = 0;
        *(s32*)(ptr + 0x44) = 0;
        ptr += 0x10;
    }
}

/* func_800018F0 - splat over-split repaired: merged former
 * func_80001994 (0x148) back in (was split at the internal early-return
 * `bnez a2; jr ra; v0=0` ~0x80001900, NOT a function boundary). True
 * size 0x1EC (123 insns, ends 0x80001AD8); func_80001ADC is the next
 * genuine function. func_80001994 = 0x80001994 added to
 * undefined_syms_auto.txt for the in-function `bnel ...,0x80001994`.
 * Per docs/MATCHING_WORKFLOW.md#feedback-split-fragments-over-splits-
 * on-internal-early-return.
 * Structural decode: s32 func_800018F0(tbl a0, a1, a2, s32 a3, ...)
 *   table-scan/insert helper. Early-outs: if (!a1) ret on a0->0x3C
 *   path; if (a2) continue else return 0; if (a3 <= 0) goto tail
 *   (return 0). Walks a3 entries of a 12-byte (0xC-stride) record
 *   array based at a0->0x3C (idx = (rec>>4)*12); per entry checks
 *   (h&7)==1, (h>>4)==arg@sp+0x10, (h&8)!=0 to find a match; on hit
 *   links via *a2 chain (t1=a2, rec->0x4/0x8 copied), sets flags
 *   (&~8 etc.), returns 1; no match returns 0. a0->0x3C = record
 *   table base; record: +0 s16 header (bit0-2 kind, bit3 flag, >>4
 *   id), +0x4 / +0x8 link words. Caps <80: beql/bnel branch-likely
 *   x3 + multu/mflo index + cross-block b-to-shared-tail. Full body
 *   INCLUDE_ASM-preserved. INCLUDE_ASM (no episode; tautology-trap). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
/* USO relocation/fixup applier: walk arg2's 0xC-byte fixup records (count arg3,
 * processed two-per-iteration after an odd-count peel). For each record whose
 * flag (unk0/unkC) bit3 is set and whose target table slot (arg0->unk3C indexed
 * by flag>>4) is live (low-3==1), matches the module arg4 (slot>>4) and is
 * loaded (bit3), apply the patch (*(arg1 + rec->unk4) = rec->unk8) and clear the
 * flag. (func_80001994 is the loop-body alt-entry via undefined_syms.) */
s32 func_800018F0(void *arg0, s32 arg1, void *arg2, s32 arg3, s32 arg4) {
    void *temp_v0;
    s16 *temp_t4;
    s16 temp_t0;
    s32 temp_t2;
    s32 var_t0;
    s32 var_t3;
    void *var_t1;

    temp_v0 = (void *) FW(arg0, 0x3C);
    if ((arg1 == 0) || (arg2 == NULL)) {
        return 0;
    }
    var_t0 = 0;
    if (arg3 > 0) {
        if (arg3 & 1) {
            temp_t2 = FW(arg2, 0);
            if (temp_t2 & 8) {
                var_t3 = 0;
                temp_t4 = (s16 *)((char *) temp_v0 + ((temp_t2 >> 4) * 0xC));
                if ((*temp_t4 & 7) == 1) {
                    temp_t0 = *temp_t4;
                    if ((arg4 == (temp_t0 >> 4)) && (temp_t0 & 8)) {
                        var_t3 = 1;
                    }
                }
                if (var_t3 != 0) {
                    *(s32 *)(arg1 + FW(arg2, 4)) = FW(arg2, 8);
                    FW(arg2, 0) = FW(arg2, 0) & ~8;
                }
            }
            var_t0 = 1;
            if (arg3 != 1) {
                goto block_15;
            }
        } else {
block_15:
            var_t1 = (char *) arg2 + (var_t0 * 0xC);
            do {
                temp_t2 = FW(var_t1, 0);
                if (temp_t2 & 8) {
                    var_t3 = 0;
                    temp_t4 = (s16 *)((char *) temp_v0 + ((temp_t2 >> 4) * 0xC));
                    if ((*temp_t4 & 7) == 1) {
                        temp_t0 = *temp_t4;
                        if ((arg4 == (temp_t0 >> 4)) && (temp_t0 & 8)) {
                            var_t3 = 1;
                        }
                    }
                    if (var_t3 != 0) {
                        *(s32 *)(arg1 + FW(var_t1, 4)) = FW(var_t1, 8);
                        FW(var_t1, 0) = FW(var_t1, 0) & ~8;
                    }
                }
                temp_t2 = FW(var_t1, 0xC);
                if (temp_t2 & 8) {
                    var_t3 = 0;
                    temp_t4 = (s16 *)((char *) temp_v0 + ((temp_t2 >> 4) * 0xC));
                    if (((*temp_t4 & 7) == 1) && (arg4 == (*temp_t4 >> 4)) && (*temp_t4 & 8)) {
                        var_t3 = 1;
                    }
                    if (var_t3 != 0) {
                        *(s32 *)(arg1 + FW(var_t1, 0x10)) = FW(var_t1, 0x14);
                        FW(var_t1, 0xC) = FW(var_t1, 0xC) & ~8;
                    }
                }
                var_t1 = (char *) var_t1 + 0x18;
            } while (var_t1 != (char *)((arg3 * 0xC) + (s32) arg2));
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800018F0);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001ADC);

/* func_80001CF4 - verified structural decode (kernel, 56 insns incl.
 * a leaked predecessor word).
 * BOUNDARY ARTIFACT: the .s text begins at 0x80001CF0 (addiu sp,sp,
 * 0x50) but the symbol func_80001CF4 = 0x80001CF4. That leading
 * +0x50 is the PREDECESSOR's epilogue delay-slot (its jr ra +
 * addiu sp,sp,0x50), disassembled one word early by splat. The
 * real function starts at 0x80001CF4 = `addiu sp,sp,-0x20`. Harmless
 * for the INCLUDE_ASM build (bytes are bytes), but a future C match
 * must target the -0x20 prologue and the predecessor must own the
 * +0x50 word (split-fragments / undefined_syms boundary fix needed
 * before this can be byte-matched).
 * Struct-typing reference: s = a 3-slot resource/handle holder.
 * Parallel field groups, slot i in {0,1,2}: handle s->{0x54,0x50,
 * 0x4C} (84/80/76), paramA s->{0x48,0x44,0x40} (72/68/64), paramB
 * s->{0x10,0xC,0x8} (16/12/8), paramC s->{0x1C,0x18,0x14} (28/24/20).
 * Per non-null slot: func_80001EDC(handle, paramA, paramB) (init/
 * validate; nonzero = failure -> abort with -0xE/-0xF/-0x10 for
 * slots 0/1/2), then func_80000518(handle, paramC) (commit/apply).
 * Caps <80: leaked predecessor prologue word (boundary) + beql
 * branch-likely chain + 2 callees. INCLUDE_ASM remains build path
 * (no episode; tautology-trap rule + unresolved head boundary). */
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
/* func_80001CF4: MATCHED 2026-06-21 (dead-#else promotion). Three-stage
 * sub-object finalize/validate: for each non-NULL sub-object (unk54/unk50/
 * unk4C) run func_80001EDC(self, sub, paramA, paramB) + the func_80000518(
 * sub, paramC) cleanup (commit runs in the beql delay slot, BEFORE the
 * failure test); bail with -0xE/-0xF/-0x10 if the stage fails. The matching
 * body sat in a dead #else/#ifdef branch (never compiled) while the build
 * path was INCLUDE_ASM. ROM byte-identical to baserom. */
s32 func_80001CF4(void *arg0) {
    extern s32 func_80001EDC();
    s32 temp_s1;

    if (FW(arg0, 0x54) != 0) {
        temp_s1 = func_80001EDC(arg0, FW(arg0, 0x54), FW(arg0, 0x48), FW(arg0, 0x10));
        func_80000518(FW(arg0, 0x54), FW(arg0, 0x1C));
        if (temp_s1 != 0) {
            return -0xE;
        }
    }
    if (FW(arg0, 0x50) != 0) {
        temp_s1 = func_80001EDC(arg0, FW(arg0, 0x50), FW(arg0, 0x44), FW(arg0, 0xC));
        func_80000518(FW(arg0, 0x50), FW(arg0, 0x18));
        if (temp_s1 != 0) {
            return -0xF;
        }
    }
    if (FW(arg0, 0x4C) != 0) {
        temp_s1 = func_80001EDC(arg0, FW(arg0, 0x4C), FW(arg0, 0x40), FW(arg0, 0x8));
        func_80000518(FW(arg0, 0x4C), FW(arg0, 0x14));
        if (temp_s1 != 0) {
            return -0x10;
        }
    }
    return 0;
}

/* func_80001DD0 - verified structural decode (kernel, 0xF8, 62
 * insns). SIBLING of func_80001CF4 (same 3-slot resource init/
 * commit family); variant: calls func_80001CF0 (not func_80001EDC)
 * and threads an extra arg `a1` via the sp+0x10 stack-arg slot.
 * Clean prologue here (NO leaked-predecessor-word artifact, unlike
 * func_80001CF4).
 * Struct-typing reference: identical 3-slot layout to func_80001CF4
 * - slot i in {0,1,2}: handle s->{0x54,0x50,0x4C} (84/80/76),
 * paramA s->{0x48,0x44,0x40} (72/68/64), paramB s->{0x10,0xC,0x8}
 * (16/12/8), paramC s->{0x1C,0x18,0x14} (28/24/20). a1 = a shared
 * extra arg passed to every func_80001CF0 (init/validate; nonzero
 * = failure -> -0xE/-0xF/-0x10), then func_80000518(handle, paramC)
 * commits. func_80001CF0 here vs func_80001EDC in CF4 = the
 * with-extra-arg variant of the same init helper. Caps <80: beql
 * branch-likely chain + 2 callees + sp+0x10 stack-arg passing.
 * INCLUDE_ASM remains build path.
 * 2026-05-31 RULED OUT: adding a leading `s` arg to func_80001CF0 (making it
 * 5-arg func(s,handle,paramA,paramB,a1)) REGRESSES 62.7->56.9%. The 4-arg
 * form below is correct; do not re-try the 5-arg form. */
#ifdef NON_MATCHING
extern int func_80001CF0(int handle, int paramA, int paramB, int a1);
s32 func_80001DD0(char *s, int a1) {
    if (*(int*)(s + 0x54) != 0) {
        if (func_80001CF0(*(int*)(s + 0x54), *(int*)(s + 0x48), *(int*)(s + 0x10), a1) != 0)
            return -0xE;
        func_80000518(*(int*)(s + 0x54), *(int*)(s + 0x1C));
    }
    if (*(int*)(s + 0x50) != 0) {
        if (func_80001CF0(*(int*)(s + 0x50), *(int*)(s + 0x44), *(int*)(s + 0xC), a1) != 0)
            return -0xF;
        func_80000518(*(int*)(s + 0x50), *(int*)(s + 0x18));
    }
    if (*(int*)(s + 0x4C) != 0) {
        if (func_80001CF0(*(int*)(s + 0x4C), *(int*)(s + 0x40), *(int*)(s + 0x8), a1) != 0)
            return -0x10;
        func_80000518(*(int*)(s + 0x4C), *(int*)(s + 0x14));
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80001DD0);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001EC8);


/* func_800021A4: 43-insn entry-list walker (absorbed func_800021D0 fragment
 * via merge-fragments). objdiff 94.53% (2026-06-23, agent-e) — up from the
 * old ~85% ceiling after a structural rewrite: insn COUNT now exact (43),
 * the comparison constants 2/4/3 are correctly hoisted before the loop, the
 * case-2/case-4 (beq/beql) dispatch and store-block (addu a0+(type>>4)*4;
 * lw 0x38; add value; sh|8; sw) match shape exactly, and entry/exit/loop
 * back-edge are byte-identical.
 *
 * RESIDUAL = 2 mnemonic diffs + register-coloring (genuine cap class):
 *   1. case-3 (a3==3) scheduling: target emits `beq a3,t2,.L2230` with the
 *      `ori` speculatively in the delay slot and a separate `sh t8` block
 *      falling into the shared `slt`; my emit inverts to `bne` and inlines
 *      `sh` in the b-delay (slt vs sh swap). IDO branch-sense + delay-slot
 *      scheduling artifact — no C lever flips it without duplicating the
 *      loop tail (tried: !=3/goto-skip splits → +slt/+addiu dup, regresses).
 *   2. t-register renumber: constants land in t1/t2/t3 not t0/t1/t2 because
 *      the store-block value-load (lw 0x4(a2)) grabs t0; cascades into the
 *      whole +0x44..+0x68 store block (t9/a3/t0/t4 vs t3/t4/t7/t6) and the
 *      post-shift branch offsets. Live-range coloring, decl-order-invariant
 *      (verified). Permuter would be the tool but import is blocked here by
 *      the asm-processor two-phase build (cc1 chokes on INCLUDE_ASM; see
 *      docs/MATCHING_WORKFLOW.md "PERMUTER=1 DOESN'T work").
 * Default build is INCLUDE_ASM (byte-exact via raw bytes). */
#ifdef NON_MATCHING
int func_800021A4(int *a0) {
    int *v0;
    int v1;
    short *a2;
    int a1;
    short type_word;
    int a3, t8, t9, t3, t4, t7, t5, t6;
    v0 = (int*)a0[0x3C / 4];
    if (v0 == 0) return 0;
    v1 = 0;
    a1 = a0[0x4 / 4];
    a2 = (short*)v0;
    if (a1 <= 0) goto end;
    do {
        type_word = a2[0];
        v1++;
        if (type_word & 0x8) goto cond;
        a3 = type_word & 0x7;
        t8 = type_word >> 4;
        if (a3 == 2) {
            t9 = t8 << 2;
            goto store_lookup;
        }
        if (a3 == 4) {
            t9 = t8 << 2;
            goto do_store;
        }
        t8 = type_word | 0x8;
        if (a3 == 3) goto set_flag;
        goto cond;
    store_lookup:
    do_store: {
            int *tp = (int*)((char*)a0 + t9);
            t4 = tp[0x38 / 4];
            t7 = ((int*)a2)[0x4 / 4];
            t6 = type_word | 0x8;
            *a2 = (short)t6;
            t5 = t7 + t4;
            ((int*)a2)[0x4 / 4] = t5;
            a1 = a0[0x4 / 4];
            goto cond;
        }
    set_flag:
        *a2 = (short)t8;
        a1 = a0[0x4 / 4];
    cond:
        a2 = (short*)((char*)a2 + 0xC);
    } while (v1 < a1);
end:
    return 0;
    (void)t3;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);
#endif

/* func_800021D0 is now an alabel inside func_800021A4 (merged via splat
 * fragment-merge — the original split-at-0x800021D0 was a splat boundary
 * artifact since 0x800021D0 has no prologue and uses registers set up
 * by the 0x800021A4 prologue). */

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern s32 D_8000A3A0;
/* USO request-list scan: walk arg0's 0xC-byte request entries (head arg0->unk3C,
 * count arg0->unk4). For each entry with flags (unk0) bit3 clear and low-3 == 1,
 * resolve the target USO via the D_80012D60 pointer table (index = flags>>4). If
 * the slot is empty, mark arg0->unk99 and bump the miss counter (D_80012BC0+0x18);
 * if the target isn't loaded yet (unk3C==0), fire the callback
 * (D_80012BC0->field_84) and bail -2; else link the entry's unk4 to the target's
 * resolved address.
 * Residual = 23 diff words (do-while form, size-exact 0x10C), all the SAME
 * single coloring decision: target puts arg0 in saved $s0 (freeing $a0 for the
 * entry-field_8 index `lh $a0,8($v1)`) and the loop counter in caller-saved
 * $a3 (=4th call-arg slot, so the callback delay is a nop); our build does the
 * reverse (arg0->$a3, counter->$s0, delay = `move a3,s0`). Everything else
 * (multu/addu operand order, index temp reg) cascades from that one swap.
 *
 * 2026-06-23 PROGRESS (agent-b): rewrote goto->do/while which MERGED the
 * count<=0 skip and loop-exit into one shared `return 0` tail (was the +2-word
 * structural diff, 56->25 words). Then `new_var = &var_v1->4` store-target
 * hoist + inline `((UsoCallbacks84*)&D_80012BC0)->field_84` (drop the `state`
 * local) trimmed 25->23. Levers that FAIL (do not re-try): decl-order swap
 * (no-op), `register`/plain `void *self=arg0` alias (30/65 words, forces a
 * copy), `register s32 var_a3` (no-op), counter-copy for call arg (no-op).
 * REGALLOC-DUMP (cc -Wo,-zdbug:6 -> uoptlist) for the do/while body: arg0 is a
 * LATE candidate (73, "not colored / -ve save") while the counter is candidate
 * 13 winning the saved slot. Permuter (>18k iters, 7 threads, reseeded from the
 * 23-word body) finds NO clean zero - its best (135 score) only matches by
 * overwriting var_a3 with the index (semantic corruption, rejected). Genuine
 * candidate-creation-order coloring cap: arg0(param, read-only) vs counter(IV
 * passed as 4th call-arg) contest for the single saved register. */
s32 func_80002250(void *arg0) {
    s16 temp_v0_2;
    s32 temp_a2;
    s32 var_a3;
    void *temp_a1;
    void *temp_v0;
    void *var_v1;
    s32 *new_var;

    temp_v0 = (void *) FW(arg0, 0x3C);
    *(u8 *)((char *)arg0 + 0x99) = 0;
    if (temp_v0 == NULL) {
        return 0;
    }
    var_a3 = 0;
    var_v1 = temp_v0;
    if (FW(arg0, 4) > 0) {
        do {
            temp_v0_2 = *(s16 *)var_v1;
            var_a3 += 1;
            if (!(temp_v0_2 & 8) && ((temp_v0_2 & 7) == 1)) {
                temp_a1 = ((void **)&D_80012D60)[temp_v0_2 >> 4];
                if (temp_a1 == NULL) {
                    *(u8 *)((char *)arg0 + 0x99) = 1;
                    FW(&D_80012BC0, 0x18) = FW(&D_80012BC0, 0x18) + 1;
                    goto block_12;
                }
                temp_a2 = FW(temp_a1, 0x3C);
                if (temp_a2 == 0) {
                    ((UsoCallbacks84 *)&D_80012BC0)->field_84(&D_8000A3A0, temp_a1, temp_a2, var_a3);
                    return -2;
                }
                new_var = (s32 *)((char *)var_v1 + 4);
                *(s16 *)var_v1 = temp_v0_2 | 8;
                *new_var = *(s32 *)((char *)temp_a2 + (*(s16 *)((char *)var_v1 + 8)) * 0xC + 4);
            }
block_12:
            var_v1 = (char *)var_v1 + 0xC;
        } while (var_a3 < FW(arg0, 4));
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80002250);
#endif

/* func_8000235C: 33-insn entry-list clear-by-type helper.
 *   if no entry list at a0+0x3C, return 0.
 *   For each 0xC-byte entry, if low type bits == 1, high bits match arg1,
 *   and bit 3 is set, clear bit 3 and mark a0+0x99 dirty.
 *
 * C structure is correct, but natural IDO -O2 rotates the saved original arg,
 * loop counter, entry pointer, and loaded type word through v0/v1/a2/a3
 * instead of the target's a3/v1/a2/v0 layout. The emitted body is same-size;
 * Makefile INSN_PATCH previously closed the register-allocation diff. INSN_PATCH
 * REMOVED 2026-05-23 (see lower note).
 *
 * 2026-05-17: tested `register int saved_a1 = a1;` + renamed locals (p, v,
 * i) — fuzzy unchanged at 91.06%. IDO's register-priority formula is driven
 * by ref-count + loop-depth, not local-name or `register` hint for this case.
 * Permuter-class register-allocation cap.
 *
 * 2026-05-20: direct-pointer/count-reload variants also emitted the same
 * rotated-register body. The INSN_PATCH promotion was REMOVED 2026-05-23
 * as match-faking; the function is now at honest 91.06% NM (permuter-class
 * register-allocation cap).
 *
 * 2026-06-20 (agent-b): statement-reorder narrowed the coloring. Loading the
 * list (`v0 = a0[0x3C/4]`) BEFORE saving the arg, and initializing the entry
 * pointer (`a2 = ...`) BEFORE the counter (`v1 = 0`), pins list->$v0, entry
 * ptr->$a2 and the loop type-word->$v0 EXACTLY as target (was list->$v1,
 * ptr->$a3 fully-rotated before). RESIDUAL is now a single 2-register swap:
 * saved-arg lands in $v1 / counter in $a3 (target: arg->$a3, counter->$v1).
 * This last swap is coupled to the as1 scheduler: emitting the counter-init
 * before the ptr-init (to flip the coloring) reorders the prologue insns and
 * sends the entry ptr to $a3 instead. The two can't be satisfied together via
 * statement order (scheduler-tie + coloring). Genuine ugen coloring cap. */
#ifdef NON_MATCHING
int func_8000235C(int *a0, int a1) {
    int a3;
    int v1;
    short *a2;
    int v0;

    v0 = a0[0x3C / 4];
    if (v0 == 0) return 0;

    a3 = a1;
    a1 = a0[0x4 / 4];
    a2 = (short*)v0;
    v1 = 0;
    if (a1 <= 0) goto end;

    do {
        v0 = a2[0];
        v1++;
        if (((v0 & 0x7) == 1) && (a3 == (v0 >> 4)) && (v0 & 0x8)) {
            *a2 = (short)(v0 & ~0x8);
            *(unsigned char*)((char*)a0 + 0x99) = 1;
            a1 = a0[0x4 / 4];
        }
        a2 = (short*)((char*)a2 + 0xC);
    } while (v1 < a1);

end:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000235C);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_800023E0);

#ifdef NON_MATCHING
extern s32 func_800031E0(void);
extern void func_80009C40(s32);
extern s32 func_80004EC0(s32, s32 *);
extern s32 func_8000A040(s32, s32);
extern void func_80009DF0(void);
extern void func_80002DB0(s32, u32 *);
extern s32 func_80002F78(s32, s32, s32, s32);
extern u32 func_80002E78(s32, u32, s32, s32);
extern void func_800030D0(void *, s32);
typedef struct { s32 w0, w1, w2, w3; } VecHandler;
extern VecHandler D_80003270;
extern VecHandler func_80000000;
extern u32 D_8000A3D0;
extern s32 D_8000A3D4;
extern s32 D_8000A3D8;
extern s32 D_8000030C;
extern s32 D_80000300;
extern s32 D_8000031C;
extern s32 __kmc_pt_mode;
extern s32 D_BFF00000;
/* Kernel boot / exception-vector + KMC-debugger init. Set SR, configure caches
 * (func_80009C40), poll the PIF (0x1FC007FC), install the exception-handler stub
 * (D_80003270, 4 words) at the reset/TLB/XTLB/general vectors
 * (0x80000000 [=func_80000000] / 0x80000080 / 0x80000100 / 0x80000180) + flush,
 * size RDRAM (func_80002DB0) and set up the heap/TLB, pick the cart ID word by
 * D_80000300, then if running under KMC (D_BFF00000 == 'KMC\0') relocate its
 * handler + ROM image and jump to its entry.
 *
 * NON_MATCHING (~53%). Logic + relocs reconstructed. Residual is IDO-internal
 * and resists C expression: (1) the four 16-byte handler copies share one
 * &D_80003270 base (CSE) whereas the target re-materializes %hi/%lo per group;
 * (2) the PIF poll loops hoist 0x1FC007FC into $s0 + emit branch-likely, target
 * re-loads the literal per call with plain bnez+nop; (3) the KMC stub/ROM copies
 * are stack-resident pointer-walks (sp44/sp48 spilled+incremented per word) that
 * array/pointer-walk C does not reproduce. Documented coloring/CSE cap class. */
void func_80002530(void) {
    extern void func_800031D0();
    extern s32 func_800031F0();
    u32 sp58;
    s32 sp5C;
    void (*sp54)();
    s32 *sp38;
    s32 *sp34;
    s32 *sp30;
    void *sp3C;
    s32 sp40;
    s32 sp2C;
    s32 sp20;
    u32 sp24;
    s32 *dst;
    s32 *src;

    sp58 = 0;
    func_800031D0(func_800031E0() | 0x20000000);
    func_80009C40(0x01000800);
    while (func_80004EC0(0x1FC007FC, &sp5C) != 0) {
    }
    while (func_8000A040(0x1FC007FC, sp5C | 8) != 0) {
    }
    *(VecHandler *)&func_80000000 = D_80003270;
    *(VecHandler *)0x80000080 = D_80003270;
    *(VecHandler *)0x80000100 = D_80003270;
    *(VecHandler *)0x80000180 = D_80003270;
    func_800031F0(0x80000000, 0x190);
    func_80005350(0x80000000, 0x190);
    func_80009DF0();
    func_80002DB0(4, &sp58);
    sp58 = sp58 & ~0xF;
    if (sp58 != 0) {
        D_8000A3D0 = 0;
        D_8000A3D0 = sp58;
    }
    sp20 = func_80002F78(D_8000A3D0, D_8000A3D4, 0, 3);
    sp24 = sp20;
    D_8000A3D0 = func_80002E78(sp20, sp24, 0, 4);
    if (D_8000030C == 0) {
        func_800030D0(&D_8000031C, 0x40);
    }
    if (D_80000300 == 0) {
        D_8000A3D8 = 0x02F5B2D2;
    } else if (D_80000300 == 2) {
        D_8000A3D8 = 0x02E6025C;
    } else {
        D_8000A3D8 = 0x02E6D354;
    }
    if (__kmc_pt_mode == 0) {
        sp38 = (s32 *)0xBFF08004;
        sp3C = (void *)0xBFF00000;
        if (D_BFF00000 == 0x4B4D4300) {
            dst = (s32 *)0x80000180;
            src = (s32 *)0x80003280;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
            dst[8] = src[8];
            func_800031F0(0x80000180, 0x24);
            func_80005350(0x80000180, 0x24);
            __kmc_pt_mode = 1;
            if (!(*sp38 & 0x10)) {
                sp40 = *(s32 *)((char *) sp3C + 4);
                if (sp40 != 0xBFF00000) {
                    sp30 = (s32 *)(sp40 | 0x20000000);
                    sp2C = 0x800;
                    sp34 = (s32 *)0xBFF00000;
                    do {
                        *sp30 = *sp34;
                        sp2C -= 1;
                        sp30 += 1;
                        sp34 += 1;
                    } while (sp2C != 0);
                }
                sp54 = (void (*)())(sp40 + 8);
                sp54(0x4B4D4300, 0);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80002530);
#endif






void func_800029A0(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/func_800029A0_pad.s")
