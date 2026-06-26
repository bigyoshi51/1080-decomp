#include "common.h"

extern int gl_func_00000000();

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by an empty void body. The 4-byte trampoline is
 * injected post-cc via PREFIX_BYTES (Makefile + scripts/inject-prefix-bytes.py).
 * The body is just jr ra + nop (8 bytes); after injection the function
 * symbol covers the full 12 bytes target wants. */
void n64proc_uso_func_00000000(void) {
}

void n64proc_uso_func_0000000C(void) {
}

extern char D_00000000;

extern char gl_d_n64p14[];
void n64proc_uso_func_00000014(int arg0, int arg1) {
    char *base = gl_d_n64p14;
    char *base10 = gl_d_n64p14 + 0x10;
    int *cur;
    int flag = 0;
    int one = 1;
    int r;

    do {
        switch (arg1) {
        case 0:
            gl_func_00000000(base, one, 0, 0);
            flag = one;
            r = gl_func_00000000(0);
            gl_func_00000000(arg0, one, r);
            break;
        case 1:
            cur = (int*)gl_func_00000000(0, one, 0);
            flag = one;
            gl_func_00000000(base10, cur);
            if (*(int*)((char*)cur + 0x14) != 0) {
                *(int*)((char*)cur + 0x4) = one;
            }
            *(int*)((char*)cur + 0x14) = (int)base;
            break;
        }
        arg1 = *(int*)(gl_d_n64p14 + 0x40);
    } while (flag == 0);
}

#ifdef NON_MATCHING
/* n64proc_uso_func_00000100: 76-insn TRIPLE-alloc-or-passthrough constructor.
 * 0x130 size, target frame 0x28; build frame 0x30 (1 extra spill slot).
 *
 * Logic: cascade of `x = prev; if (x == 0) { x = alloc(N); if (!x) goto end; }`
 *   p = a0; if (!p) { p = alloc(0x88); if (!p) goto end; }
 *   q = p;  if (!q) { q = alloc(0x50); if (!q) goto end; }   // dead arm
 *   r = q;  if (!r) { r = alloc(0x2C); if (!r) goto end; }   // dead arm
 *   helper(r, &D + 0xB0);
 *   r[0x28] = &D;
 *   q[0x28] = &D;
 *   p[0x28] = &D + 0x18;
 *   p[0xC]  = &D + 0xB8;
 *   helper(p);
 *   p[0x50] = 0; p[0x3C] = 0x64; p[0x54] = 0xFF;
 *   z = *(int*)(&D + 0x190);
 *   helper(p + 0x10, z);
 *   if (z[0x14] != 0) z[1] = 1;
 *   z[0x14] = p;
 *   helper(*(int*)(&D + 0x190));   // fresh load
 *   helper(0xA3);
 *   p[0x48] = 0; p[0x30] = 0; p[0x2C] = 0;
 *   end: return p;
 *
 * 2026-05-05 BIG PROMOTION: 73.33% -> 88.04% (+14.71pp) via THREE fixes:
 *
 *   FIX 1 (+4.64pp): Triple alloc-cascade. Previous wrap had only 2 cascade
 *   steps (`p = a0; q = alloc(0x50); r = q`). Target has 3: each step is
 *   `x = prev; if (!x) { x = alloc(N); if (!x) goto end; }`. The 2nd and 3rd
 *   bnez tests are dead-arm guards but IDO emits them. See
 *   feedback_alloc_or_passthrough_cascade_includes_dead_arms.md.
 *
 *   FIX 2 (+3.30pp): Defeat IDO -O2 CSE on &D base. Target emits 4 fresh
 *   `lui+addiu` pairs for the &D-derived stores (r[0x28]=&D, q[0x28]=&D,
 *   p[0x28]=&D+0x18, p[0xC]=&D+0xB8); inline `&D_00000000` form CSEs the
 *   base into v1. Recipe per feedback_unique_extern_with_offset_cast_breaks_cse.md:
 *   declare 5 unique externs (D_n64_100_a..e) all mapped to 0x0 in
 *   undefined_syms_auto.txt, write each access as `(char*)&D_n64_100_X + N`.
 *   IDO sees them as different symbols → no CSE.
 *
 *   FIX 3 (+6.78pp): Missing args on the post-conditional helper call. Target
 *   prepares `li a1, 2; move a2, zero` BEFORE the beqzl-and-store, then uses
 *   them in the jal at 0xFC. The C had `gl_func(*(int*)(&D + 0x190))` (1 arg);
 *   should be `gl_func(*(int*)(&D + 0x190), 2, 0)` (3 args).
 *
 * Remaining 12% diff (verified 2026-05-05 via objdump):
 *   1. Frame size: 0x30 (build) vs 0x28 (target) — build has 5 spill slots,
 *      target has 4. Build can't share q-spill slot with z-spill (live ranges
 *      overlap in build's allocation, not in target's).
 *   2. Register choice for q/r passthroughs: target uses a3 for q + a0 for r;
 *      build uses v1 for q + a2 for r. Cascades through ~15 insns of register-
 *      rename diff. `register` hint on q/r had no effect (88.04% identical).
 *   3. Spill ordering at first jal helper(r, &D+0xB0) — target's spill of a3
 *      to sp+0x24 in BD slot vs build's spill of a2 to sp+0x24 BEFORE jal.
 *
 * All three remaining caps are IDO regalloc-priority choices not reachable
 * from C-source modifications.
 *
 * (4) TRIED 2026-05-05: two more variants, both byte-identical to baseline
 * (88.04 %, no shift in spill slots or register cascade):
 *   (a) Block-scope `z` (declared inside the inner block instead of top of
 *       function). Hypothesis: shorten z's RTL live range so it doesn't
 *       conflict with q/r spill slots in IDO's allocator (was hoping to
 *       collapse build's 5 spill slots → 4 like target). Result: zero
 *       byte diff. C lexical scope doesn't influence IDO's RTL pseudo
 *       extent; live range is data-flow derived. Confirms doc on variant
 *       (23) for n64proc_uso_func_00000014 (block-scope is a no-op).
 *       Kept the change for code clarity (no regression).
 *   (b) Ternary alloc-cascade form `p = a0 ? a0 : alloc(0x88);` instead
 *       of `if (p == 0) { p = alloc(0x88); ... }`. Same logic, different
 *       textual shape. Result: zero byte diff. IDO normalizes both forms
 *       to identical RTL post-front-end. Reverted to if-form because the
 *       existing doc references "x = prev; if (!x) { ... }" pattern with
 *       dead arms and other agents will look for that form.
 *
 * Both confirm the [register] cap is at IDO's RTL allocator level, not at the C
 * source-form level. No further C-textual variant will shift register
 * allocation for this function.
 *
 * 2026-05-30 — 88.04% -> 95.01% via a STRUCTURAL control-flow fix the regalloc
 * analysis above had missed: the 2nd/3rd alloc failure arms must NOT `goto end`
 * (early-return) — the target CONVERGES them into the init sequence. The 0x50-alloc
 * failure jumps to the `p->0x28 = ...` write (label Lp28, target 0x90) and the
 * 0x2C-alloc failure jumps to the `q->0x28 = ...` write (label Lq28, target 0x84),
 * because those sub-object-pointer 0x28 stores are SHARED tails reached both by the
 * success path (fall-through) and the alloc-failure path. Splitting the single
 * 0x28-writes block into Lq28/Lp28 labeled tails + retargeting the dead-arm gotos
 * fixed every branch target. Residual ~5% is now PURELY the regalloc/frame cap
 * documented above (q/r in $v1+stack-spill@0x28/0x2C vs target $a3/$a0@0x24/0x20;
 * frame 0x30 vs 0x28). Real allocator cap; structure is exact. */
extern int gl_func_00000000();
void *n64proc_uso_func_00000100(void *a0) {
    void *p;
    void *q;
    void *r;

    p = a0;
    if (p == 0) {
        p = (void*)gl_func_00000000(0x88);
        if (p == 0) goto end;
    }
    q = p;
    if (q == 0) {
        q = (void*)gl_func_00000000(0x50);
        if (q == 0) goto Lp28;
    }
    r = q;
    if (r == 0) {
        r = (void*)gl_func_00000000(0x2C);
        if (r == 0) goto Lq28;
    }
    {
        extern char D_n64_100_a, D_n64_100_b;
        gl_func_00000000(r, (char*)&D_n64_100_a + 0xB0);
        *(int*)((char*)r + 0x28) = (int)&D_n64_100_b;
    }
Lq28:
    {
        extern char D_n64_100_c;
        *(int*)((char*)q + 0x28) = (int)&D_n64_100_c;
    }
Lp28:
    {
        extern char D_n64_100_d, D_n64_100_e;
        *(int*)((char*)p + 0x28) = (int)((char*)&D_n64_100_d + 0x18);
        *(int*)((char*)p + 0xC)  = (int)((char*)&D_n64_100_e + 0xB8);
    }
    gl_func_00000000(p);

    *(int*)((char*)p + 0x50) = 0;
    *(int*)((char*)p + 0x3C) = 0x64;
    *(int*)((char*)p + 0x54) = 0xFF;
    {
        extern char D_n64_100_f;
        int *z = *(int**)((char*)&D_n64_100_f + 0x190);
        gl_func_00000000((char*)p + 0x10, z);
        if (z[0x14 / 4] != 0) z[1] = 1;
        z[0x14 / 4] = (int)p;
        gl_func_00000000(*(int*)((char*)&D_n64_100_f + 0x190), 2, 0);
    }
    gl_func_00000000(0xA3);
    *(int*)((char*)p + 0x48) = 0;
    *(int*)((char*)p + 0x30) = 0;
    *(int*)((char*)p + 0x2C) = 0;
end:
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso", n64proc_uso_func_00000100);
#endif

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

/* n64proc_uso_func_00000268: MATCHED 2026-06-01. State machine on a0->0x50
 * (key dispatch).
 *   case 0: decrement a0->0x3C; if <16, decay a0->0x54 by 16 (clamp>=0);
 *           when a0->0x3C hits 0, transition to mode 1 + reset a0->0x3C=100.
 *   case 1: ramp a0->0x54 by 8 (clamp<=255); decrement a0->0x3C; on 0 OR
 *           (a0->0x3C<0x55 && gl_func(&D,0x40100)!=0), set D[0x40]=1, call gl_func(a0,0,0).
 *
 * Switch form emits the target's beql-to-case dispatch polarity; in-place RMW
 * on the counters makes IDO re-read fields into fresh $t regs instead of
 * collapsing named temporaries into $v0. */
void n64proc_uso_func_00000268(int *a0) {
    int v;

    v = a0[0x50/4];
    switch (v) {
    case 0:
        a0[0x3C/4]--;
        if (a0[0x3C/4] < 0x10) {
            a0[0x54/4] -= 0x10;
            if (a0[0x54/4] < 0) a0[0x54/4] = 0;
            if (a0[0x3C/4] == 0) {
                a0[0x50/4] = 1;
                a0[0x3C/4] = 0x64;
            }
        }
        break;
    case 1:
        a0[0x54/4] += 8;
        if (a0[0x54/4] >= 0x100) a0[0x54/4] = 0xFF;
        a0[0x3C/4]--;
        if (a0[0x3C/4] == 0 || (a0[0x3C/4] < 0x55 && gl_func_00000000(&D_00000000, 0x40100) != 0)) {
            *(int*)((char*)&D_00000000 + 0x40) = 1;
            gl_func_00000000(a0, 0, 0);
        }
        break;
    }
}

/* n64proc_uso_func_0000035C: MATCHED 2026-05-31. key-dispatch on *(a0+0x50):
 * case 0 inits a0+0x58 subobject, case 1 inits a0+0x70, both from a 4x1.0f buf.
 * Cracked the key==1 branch-polarity cap with a `switch` — the if/goto chain
 * emitted `bne key,1,end` (k1 as fall-through); the switch emits the target's
 * `beq key,1,k1` dispatch. Frame layout via pad1[4]/pad2[12] around buf[4].
 * See docs/IDO_CODEGEN.md#switch-vs-if-goto-dispatch-polarity. */
void n64proc_uso_func_0000035C(char *a0) {
    char pad1[4];
    float buf[4];
    int key;
    int val;
    char pad2[12];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    key = *(int*)(a0 + 0x50);
    switch (key) {
    case 0:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x58);
        gl_func_00000000(a0 + 0x58, 0xA0, 0x78, 3);
        break;
    case 1:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x70);
        gl_func_00000000(a0 + 0x70, 0xA0, 0x78, 3);
        break;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_0000035C_pad.s")
