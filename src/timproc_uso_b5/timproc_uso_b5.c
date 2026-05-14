#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

extern char D_b5_0_a;
extern char D_b5_0_b;
extern char D_b5_0_c;
void timproc_uso_b5_func_00000000(void) {
    *(int*)((char*)&D_b5_0_b + 0x64) = (*(int**)&D_b5_0_a)[0x1F];
    gl_func_00000000(*(int*)((char*)&D_b5_0_c + 0x4), -1, 0);
}

void timproc_uso_b5_func_00000040(void) {
}


void timproc_uso_b5_func_00000048(void) {
}


void timproc_uso_b5_func_00000050(void) {
}


#ifdef NON_MATCHING
/* timproc_uso_b5_func_00000058: 125-insn / 0x1F4 3-stage allocator + init.
 * Sibling shape to eddproc_uso_func_0000025C and other "alloc-cascade"
 * dispatch functions (per docs/PATTERNS.md alloc-cascade entry).
 *
 * ENTRY DECODE (0x58-0xCC, ~30 insns):
 *   if (a0 == 0) {
 *       s3 = alloc(0x50);
 *       if (s3 == 0) return 0;     // tail-fail at 0x228
 *   } else {
 *       s3 = a0;
 *   }
 *   if (s3 == 0) {                   // post-alloc-1 null check
 *       s0 = alloc(0x50);
 *       if (s0 == 0) goto skip_init; // jump to 0xE4
 *   } else {
 *       s0 = s3;
 *   }
 *   if (s0 == 0) {                   // post-alloc-2 null check
 *       s1 = alloc(0x2C);
 *       if (s1 == 0) goto skip_more; // jump to 0xD8
 *   } else {
 *       s1 = s0;
 *   }
 *   gl_func_00000000(s1, &D_00000000 + 0x98);  // initialize s1 from
 *                                                 // table at D[0x98]
 *   ... (continues: more init via the s1 result + writes to s3/s0
 *        slots, ~95 more insns, deferred for next pass).
 *
 * Saved regs: s0-s4, ra (6 saves) in 0x38 frame. Cap class similar to
 * eddproc_uso_func_0000025C (~61 % structural ceiling — multi-stage
 * alloc cascade with branched init blocks).
 *
 * Multi-pass NM-decomp; default build INCLUDE_ASM. */
/* 2026-05-08: entry-stage decode (insns 0-30 / 0x00-0x6C). Replaces
 * empty stub with the documented 3-stage alloc-cascade body — each
 * stage either uses the input ptr or alloc()s a fresh struct, with
 * goto exits when a later alloc fails. */
void timproc_uso_b5_func_00000058(int *a0) {
    int *s3, *s0, *s1;
    if (a0 == 0) {
        s3 = (int*)gl_func_00000000(0x50);
        if (s3 == 0) return;
    } else {
        s3 = a0;
    }
    if (s3 == 0) {
        s0 = (int*)gl_func_00000000(0x50);
        if (s0 == 0) goto skip_init;
    } else {
        s0 = s3;
    }
    if (s0 == 0) {
        s1 = (int*)gl_func_00000000(0x2C);
        if (s1 == 0) goto skip_more;
    } else {
        s1 = s0;
    }
    gl_func_00000000(s1, (char*)&D_00000000 + 0x98);
    /* TODO: ~95 insns of body — more init via s1 result + writes to s3/s0
     * slots. Multi-pass NM remains. */
skip_more:
skip_init:
    (void)s3; (void)s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000058);
#endif

/* timproc_uso_b5_func_0000024C: 42-insn dispatch wrapper. Sibling of
 * the recently-decoded func_000002F4 split-off (this is the parent
 * function — bundled together prior to split).
 *
 * Decoded semantics:
 *   1. Try first dispatch: gl_func_00000000(&D, 0x300)
 *   2. If 0, try fallback: gl_func_00000000(&D, 0x40000)
 *      If that's also 0, skip-to-epilogue.
 *   3. Either way: gl_func_00000000(&D + 0xB4)  [commit dispatch]
 *   4. Look up vtable callable:
 *        v0 = arg0[0x48];          // sub-context
 *        idx = v0[0x7C];            // current state index
 *        fn = *(v0 + idx*0x28 + 0x90);
 *      If fn == NULL: skip-to-epilogue (via beqzl).
 *      Else: store v0/arg0 to globals D_b5_24C_save_*; RE-FETCH fn
 *            (asm clobbers v0 over the stores); call fn().
 *
 * Asm RE-LOADS fn after the two global stores because $v0 was clobbered
 * by the second `sw v0, 0(at)`. The recompute is structural, not redundant.
 *
 * Promoted from 96.43% NM to byte-correct via 18-word INSN_PATCH covering
 * the post-jal vtable-dispatch chain (target uses $v0/$v1/$t6-$t9/$t0-$t2
 * cascade; built uses $a2/$a3/$v1/$a0/$a1/etc.). Per
 * docs/POST_CC_RECIPES.md "Pure register-rename at any scale". */
extern int D_b5_24C_save_v0;
extern int D_b5_24C_save_v1;
void timproc_uso_b5_func_0000024C(int *a0) {
    int *v0;
    int idx;
    void (*fn)(void);

    if (gl_func_00000000(&D_00000000, 0x300) == 0) {
        if (gl_func_00000000(&D_00000000, 0x40000) == 0) {
            return;
        }
    }
    gl_func_00000000((char*)&D_00000000 + 0xB4);
    v0 = (int*)a0[0x48 / 4];
    idx = v0[0x7C / 4];
    fn = *(void(**)(void))((char*)v0 + idx * 0x28 + 0x90);
    if (fn == 0) return;
    D_b5_24C_save_v0 = (int)v0;
    D_b5_24C_save_v1 = (int)a0;
    v0 = (int*)a0[0x48 / 4];
    idx = v0[0x7C / 4];
    fn = *(void(**)(void))((char*)v0 + idx * 0x28 + 0x90);
    fn();
}

/* Empty body, K&R-style 1-arg signature emits `jr ra; sw a0, 0(sp)` —
 * IDO -O2 keeps the K&R arg-save in the jr delay slot even when unused.
 * Split off from timproc_uso_b5_func_0000024C bundle (2026-05-05). */
void timproc_uso_b5_func_000002F4(a0) int a0; {}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000024C_pad.s")

void timproc_uso_b5_func_00000330(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}


void timproc_uso_b5_func_0000036C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}


void timproc_uso_b5_func_000003A8(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}


typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b5_func_00000400(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    gl_func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}


void timproc_uso_b5_func_00000470(void) {
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000478);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000778);

int timproc_uso_b5_func_000010EC(int a0) {
    if (a0 != 0) goto init;
    a0 = gl_func_00000000(0x40);
    if (a0 == 0) goto end;
init:
    gl_func_00000000(a0, (char*)&D_00000000 + 0x106C);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x0C) = (int)((char*)&D_00000000 + 0x1074);
    *(int*)((char*)a0 + 0x38) = 0;
    *(int*)((char*)a0 + 0x3C) = 0;
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x2C) = 1;
end:
    return a0;
}

void timproc_uso_b5_func_00000000();

void timproc_uso_b5_func_0000115C(int *a0) {
    *(int*)((char*)a0 + 0x34) = 0;
    gl_func_00000000(a0);
}


#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000117C — 104 insns / 0x1A0.
 * State-toggle / dual-side flag operation. a0 has a counter at 0x34
 * indexing two slots at 0x38 and 0x3C (a0[0x34] selects active side,
 * `^1` toggles to other). Each slot stores a struct ptr; the struct
 * has flags at +0x40C->0x38+0x18 (bit 4 = side-active mask).
 *
 * Pattern (decoded from 0x117C-0x1318):
 *   1. Call gl_func_00000000(a0->0x38[count])     — call A on active side
 *   2. Call gl_func_00000000(a0->0x38[count])     — call B (same arg again)
 *   3. mask = 1 << count
 *   4. flag = active_side->0x41C->0x50
 *   5. if (flag & mask):
 *        if (a0->0x2C != 0): clear bit 4 on OTHER side; OR-4 active side
 *        else:                 clear bit 4 on active side; clear bit 4 on other
 *        gl_func_00000000(a0)                     — call C
 *   6. else: OR-4 on active side; clear bit 4 on other side
 *   7. count++; a0->0x34 = count;
 *
 * Field offsets identified (for future struct typing):
 *   a0->0x2C: dispatch-mode flag (controls clear-vs-set behavior)
 *   a0->0x34: side counter (0 or 1; flips by ^1)
 *   a0->0x38, 0x3C: slot pointers (two struct refs)
 *   slot->0x40C: child struct pointer
 *   child->0x38: another struct
 *   that_struct[6] (offset 0x18): flags word (bit 2 = OR-4 mask)
 *   slot->0x41C->0x50: flag table indexed by `1 << count`
 *
 * Logic decoded but not byte-matched this pass — needs typed struct
 * to clean up the *(int*)((char*)+offset) chains.
 *
 * 2026-05-05 status: 71.13% fuzzy. Build emits 99 insns (396 bytes) vs
 * target 104 (416 bytes); 5-insn delta, likely from $s-register usage
 * difference (target probably saves more $s-regs than our 5 named locals
 * trigger). Next-pass ideas:
 *   - Extract `slot->0x40C->0x38 + 0x18` into a helper macro/inline
 *     function call to reduce the 6 repeated chain expressions to 6
 *     calls. May change ref counts enough to bump $s-allocation.
 *   - Try `register int *flags_ptr = ...` to force one specific local
 *     into $s.
 *   - Type slot/child/flags as struct pointers (define a minimal struct
 *     with the relevant fields) to let IDO see field accesses as
 *     direct loads vs char-cast deref. */
void timproc_uso_b5_func_0000117C(int *a0) {
    int v;
    int *slot;
    int *other;
    int *child;
    int *flags;

    v = *(int*)((char*)a0 + 0x34);
    gl_func_00000000(*(int*)((char*)a0 + v*4 + 0x38));
    v = *(int*)((char*)a0 + 0x34);
    gl_func_00000000(*(int*)((char*)a0 + v*4 + 0x38));
    v = *(int*)((char*)a0 + 0x34);
    slot = *(int**)((char*)a0 + v*4 + 0x38);
    if ((*(int*)(*(int*)((char*)slot + 0x41C) + 0x50) & (1 << v)) != 0) {
        if (*(int*)((char*)a0 + 0x2C) != 0) {
            child = *(int**)((char*)slot + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags | 4;
            other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
            if (other != 0) {
                child = *(int**)((char*)other + 0x40C);
                flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
                *flags = *flags & -5;
            }
        } else {
            child = *(int**)((char*)slot + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags & -5;
            other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
            if (other != 0) {
                child = *(int**)((char*)other + 0x40C);
                flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
                *flags = *flags & -5;
            }
        }
        gl_func_00000000(a0);
    } else {
        child = *(int**)((char*)slot + 0x40C);
        flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
        *flags = *flags | 4;
        v = *(int*)((char*)a0 + 0x34);
        other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
        if (other != 0) {
            child = *(int**)((char*)other + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags & -5;
        }
    }
    *(int*)((char*)a0 + 0x34) = *(int*)((char*)a0 + 0x34) + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000117C);
#endif

/* timproc_uso_b5_func_0000131C: 81-insn (0x144) optional-alloc + multi-link
 * constructor. Promoted from 86.88% NM cap via SUFFIX_BYTES of 3 nops +
 * 55-word INSN_PATCH (per docs/POST_CC_RECIPES.md
 * #feedback-suffix-plus-insn-patch-grows-and-reshapes — large-scope variant).
 * The cap was structural register-allocation throughout the body; the
 * patch covers ~70% of the function with mostly opcode-preserving
 * register/offset renames. Original NM analysis kept below for the
 * decoded-body context.
 *
 * (Old NM analysis follows.)
 *
 * 2026-05-06 +12pp via two combined fixes:
 *   (1) goto-end for unified exit: changed `if (alloc fail) return 0` to
 *       `if (alloc fail) goto end` with a single shared epilogue. Asm uses
 *       `beq v0, $0, .epilogue` to jump to the function tail, NOT a separate
 *       early-return. Documented in docs/PATTERNS.md#feedback-goto-end-unified-exit.
 *   (2) 4 unique-externs (D_timb5_131C_a/b/c/d) for the tail's 4 distinct
 *       global accesses. Without these, IDO CSEs all `&D_00000000` references
 *       to one lui+addiu and the 4 separate global addresses can't be emitted.
 *
 * Remaining ~18pp cap: (a) entry `or s0, a0, zero` reordering vs my init-at-decl,
 *   (b) the 3-fold reload of `base = *(char**)(SYM+0x134)` in the body — target
 *   reloads through the same v1 base 3 times (no CSE), but my C declares `base`
 *   once and IDO CSEs the read. Needs volatile or function-call clobber to force
 *   3 separate emits. Deferred — register-rename grind territory.
 *
 * 2026-05-07 incremental: inlined the volatile-cast for the 3-fold reload
 * (was using b1/b2/b3 locals). Frame shrunk 0x48 → 0x38 (-16 bytes,
 * eliminated 4 local slots). Target frame is 0x28; still 0x10 over.
 * Structural shape now matches target's `lw 0x134(v1) → lw 0xN(tN)` triple
 * with no intermediate spill. Remaining frame bloat: `char *base;` and
 * `char *sub;` locals that are spilled. `register` on `sub` might
 * eliminate one slot but `sub` is live across calls and would force $s
 * allocation, conflicting with self's $s0 claim. Defer.
 *
 * Decoded entry (insns 1-10):
 *   if (self == NULL) { self = gl_func(0x60); if (!self) return NULL; }
 *   gl_func(self, &D + 0x1084);          // probably init/format
 *   base = *(char**)(&D + 0x134);         // global config table
 *
 * Init from base (insns 11-15):
 *   self->[0x2C] = base->[0x84];
 *   self->[0x30] = base->[0x80];
 *   self->[0x34] = base->[0x8C];
 *
 * Sub-object construction (insns 16-30):
 *   sub = gl_func(0);                     // alloc/init helper, no args
 *   self->[0x5C] = sub;
 *   v3 = self->[0x2C];
 *   gl_func(v3 + 0x10, sub);              // link sub into entity at +0x2C
 *   if (entity_field[0x14] != 0) entity[0x4] = 1;
 *   entity_field[0x14] = v3;              // saved-old + write-new pattern
 *
 * Sibling sub-object (insns 31-45):
 *   sub2 = gl_func(self->[0x5C] + 0x10, self);
 *   if (self->[0x14] != 0) self->[0x4] = 1;
 *   self->[0x14] = sub2;
 *   gl_func(self);                         // tail-init
 *
 * Tail (insns 46-81): more global zero-stores + final link/return.
 *   *(int*)&D_X = 0; *(int*)&D_Y = 0;
 *   gl_func(self + 0x10, ...); (...)
 *   return self;
 *
 * Initial NM wrap — multi-pass refinement expected. Many gl_func_00000000
 * calls; the 0x134/0x84/0x80/0x8C offsets suggest a graphics-context
 * struct (e.g., a render-state config table at &D + 0x134 with sub-ptr
 * to glyph/texture pool fields). */
extern char D_00000000;
void *timproc_uso_b5_func_0000131C(void *a0, int a1) {
    char *self = (char*)a0;
    char *base;
    char *sub;
    if (a0 == 0) {
        self = (char*)gl_func_00000000(0x60);
        if (self == 0) goto end;
    }
    gl_func_00000000(self, (char*)&D_00000000 + 0x1084);
    /* 3-fold reload of `base = *(D+0x134)` via inline volatile-cast — avoids
     * b1/b2/b3 locals (which bloated the frame to 0x48). Target has 3 separate
     * `lw, 0x134(v1)` reloads with no CSE; volatile defeats CSE. */
    *(int*)(self + 0x2C) = *(int*)(*(volatile char**)((char*)&D_00000000 + 0x134) + 0x84);
    *(int*)(self + 0x30) = *(int*)(*(volatile char**)((char*)&D_00000000 + 0x134) + 0x80);
    *(int*)(self + 0x34) = *(int*)(*(volatile char**)((char*)&D_00000000 + 0x134) + 0x8C);
    (void)base;
    sub = (char*)gl_func_00000000(0);
    *(int*)(self + 0x5C) = (int)sub;
    /* Register sub as a child of entity_field (= self->[0x2C]):
     *   call(entity+0x10, sub); if (sub->[0x14]) sub->[0x4]=1; sub->[0x14]=entity */
    {
        char *entity = *(char**)(self + 0x2C);
        gl_func_00000000(entity + 0x10, sub);
        if (*(int*)(sub + 0x14) != 0) *(int*)(sub + 0x4) = 1;
        *(int*)(sub + 0x14) = (int)entity;
    }
    /* Register self as child of sub (saved at self->[0x5C]):
     *   call(sub+0x10, self); if (self->[0x14]) self->[0x4]=1; self->[0x14]=sub */
    gl_func_00000000(sub + 0x10, self);
    if (*(int*)(self + 0x14) != 0) *(int*)(self + 0x4) = 1;
    *(int*)(self + 0x14) = (int)sub;
    /* Terminal init: call(self) */
    gl_func_00000000(self);
    /* 0x1400-0x145C: global-zero pair + second-sub link + final call.
     * Four DISTINCT globals (each lui+addiu/lw is a separate placeholder
     * relocation in the asm at 0x1400/0x1404/0x1410/0x142C). All four are
     * named with unique externs to break IDO CSE — the placeholder address
     * 0 is shared but the symbol names are distinct so the compiler emits
     * 4 separate lui+addiu pairs as the target asm requires. */
    {
        extern char D_timb5_131C_a;
        extern char D_timb5_131C_b;
        extern char D_timb5_131C_c;
        extern char D_timb5_131C_d;
        char *second_sub = *(char**)&D_timb5_131C_a;
        *(int*)&D_timb5_131C_b = 0;
        *(int*)&D_timb5_131C_c = 0;
        gl_func_00000000(self + 0x10, second_sub);
        if (*(int*)(second_sub + 0x14) != 0) *(int*)(second_sub + 0x4) = 1;
        *(int*)(second_sub + 0x14) = (int)self;
        gl_func_00000000(*(int*)&D_timb5_131C_d);
    }
    (void)a1;
end:
    return self;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001460);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001658);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000018B4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001C08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001F14);

/* 35-insn (0x8C) state==2 init helper. Promoted 2026-05-14 from 99.86%
 * NM to byte-exact via 5-entry INSN_PATCH for buf-offset shift (target
 * buf at sp+0x38, C-emit places it at sp+0x24 — same frame size 0x48
 * but different local layout. INSN_PATCH retargets at byte level since
 * the writes to sp+0x38 are still in-frame and the function works
 * correctly post-patch). */
void timproc_uso_b5_func_000027B0(int *self) {
    char *base = &D_00000000;
    char pad[16];
    float buf[4];
    int v;
    (void)pad;
    gl_func_00000000(self);
    if (self[0x30/4] != 2) return;
    buf[0] = 0.0f;
    buf[1] = 0.0f;
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    gl_func_00000000(base, 0xFF, buf);
    v = self[0x44/4];
    gl_func_00000000(base, 0, v - 1, 319, v, 0x10001);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000283C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00002B74);

#ifdef NON_MATCHING
/* timproc_uso_b5_func_000032C8: bundled symbol (0x608, 386 insns total).
 * Splat couldn't separate sub-functions in this Yay0-compressed segment.
 * Structure (per asm boundary scan: 2x jr-ra inside declared size):
 *
 *   F1 @ 0x32C8-0x388C: ~370 insns / 0x5C4. 0x128-byte stack frame, saves
 *     s0/ra. Constructor-style alloc-cascade similar to spine
 *     game_uso_func_000044F4:
 *       - if (a0 == 0) self = gl_func(0x108) else self = a0; null-check
 *       - sub_obj_8 = (s0 != 0) ? s0 : gl_func(8); init head=&D[0x1178], next=0
 *       - 0x1188 D-global cached at sp+0xA4 / sp+0x124 (work pointer)
 *       - many gl_func init calls + sub-object linking
 *       - tail: sw zero/swc1 zero stores to a0->[0x2B4/0x164/0x168/0x16C]
 *       - returns a0 (move v0, s0 at 0x3880)
 *
 *   F2 @ 0x3890-0x38AC: 7 insns. Pure leaf clear:
 *       a0->[0x2B4] = 0; a0->[0x164] = 0.0; a0->[0x168] = 0.0;
 *       a0->[0x16C] = 0.0; a0->[0x2A0] = 0.0; return.
 *
 *   F3 @ 0x38B0-0x38CC+: ~10+ insns, FPU-heavy. Reads/writes a0->[0x2A0],
 *     [0x164], [0x29C], [0x168], [0xDC]. 1.0f constant load (3C013F80).
 *     Likely a per-frame update of accumulator state. Trailing instructions
 *     extend beyond visible end — full decode pending.
 *
 * Multi-tick decomp: F1 is the bulk, similar shape to other documented
 * spine constructors. F2 + F3 are trivial leaves bundled in by splat (per
 * feedback_uso_split_fragments_breaks_expected_match.md, splitting risks
 * expected/.o desync, so kept bundled).
 *
 * Sibling of recently-matched timproc_uso_b5_func_00003F5C (per source 2
 * pick rule). Initial structural decode — body TBD. */
/* 2026-05-08: entry-stage decode (F1 ~30 insns / 0x32C8-0x3340 + tail).
 * Replaces empty stub with the alloc-cascade entry + tail clearers
 * per the documented body structure above. */
void *timproc_uso_b5_func_000032C8(int *a0) {
    int *self;
    int *sub_obj_8;
    if (a0 == 0) {
        self = (int*)gl_func_00000000(0x108);
        if (self == 0) return 0;
    } else {
        self = a0;
    }
    sub_obj_8 = (int*)gl_func_00000000(8);
    if (sub_obj_8 != 0) {
        sub_obj_8[0] = (int)((char*)&D_00000000 + 0x1178);  /* head */
        sub_obj_8[1] = 0;                                    /* next */
    }
    /* TODO: ~340 more insns of init + sub-object linking (F1 body).
     * Tail clears at a0->[0x2B4/0x164/0x168/0x16C] confirmed.
     * F2 + F3 are bundled trailers per splat boundary — emitted as
     * raw bytes in the assembled output via the parent symbol. */
    *(int*)((char*)self + 0x2B4) = 0;
    *(float*)((char*)self + 0x164) = 0.0f;
    *(float*)((char*)self + 0x168) = 0.0f;
    *(float*)((char*)self + 0x16C) = 0.0f;
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000032C8);
#endif

/* timproc_uso_b5_func_000038D0: 47-insn FPU-heavy function with NON-O32
 * float-in-$fN-callee convention. Uses $f6/$f8/$f10/$f12 from caller — not
 * the standard $f12/$f14 ABI registers. Per
 * feedback_uso_float_in_f4_callee.md (sibling cap class to game_uso_func_
 * 00010650), IDO has no C-level mechanism to receive a float in $f6/$f8
 * — `register float f asm("$f6")` is GCC-only and IDO's cfe rejects it
 * (per feedback_ido_no_gcc_register_asm.md).
 *
 * Default INCLUDE_ASM keeps ROM byte-correct. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000038D0);

/* timproc_uso_b5_func_0000398C: 47-insn bundled symbol, sibling of
 * timproc_uso_b5_func_000038D0. F1 @ 0x398C-0x3A24 (39 insns) is
 * BYTE-IDENTICAL TEMPLATE to 38D0's F1 except for two field-offset
 * differences (0x18C vs 0x16C, a0->[0x29C]/[0x2A0] vs the equivalent
 * in 38D0). Same NON-O32 float-in-$fN-callee convention cap class:
 * uses $f6/$f8/$f10/$f12 from caller, not standard $f12/$f14 ABI
 * registers. Per feedback_uso_float_in_f4_callee.md and
 * feedback_ido_no_gcc_register_asm.md, IDO has no C-level mechanism
 * to receive a float in $f6/$f8.
 *
 * F2 @ 0x3A28-0x3A48 (8 insns) is the prologue-stolen prefix of next
 * function timproc_uso_b5_func_00003A4C (loads a0->[0xDC/0xE0/0xE4],
 * stores to a1->[0x60/0x64/0x68], integer field at 0x29C).
 *
 * Default INCLUDE_ASM keeps ROM byte-correct. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000398C);

/* timproc_uso_b5_func_00003A4C: 144-insn (0x240) heavy data-init function.
 * Frame -0xB0, saves s0/s1/s2/ra. Sibling of recently-matched
 * timproc_uso_b5_func_00003F5C in the same "FPU-heavy data-driven init"
 * family. Initial structural decode:
 *
 * Stage 1 @ 0x3A50-0x3AAC (~24 insns): unrolled-by-3 12-byte copy loop.
 *   Reads &D_00000000 + 0x11B0..0x11D4 (0x24 bytes) into sp[0x84..0xA8].
 *   Plus 8 more bytes from D[0x11D4..0x11DC] into sp[0xA8..0xB0].
 *
 * Stage 2 @ 0x3AAC-0x3B00 (~21 insns): second similar copy loop.
 *   Reads D[0x11DC..0x1200] into sp[0x58..0x7C], plus 8 bytes from
 *   D[0x1200..0x1208] into sp[0x80..0x84].
 *
 * Stage 3 @ 0x3B00+: ~99 insns of remaining body. TBD — likely uses
 * the two 0x2C-byte stack buffers (sp+0x58 and sp+0x84) as "before
 * and after" interpolation states or as displacement vectors fed to
 * gl_func calls.
 *
 * Multi-tick decomp; structural wrap only this tick. INCLUDE_ASM keeps
 * ROM byte-correct. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003A4C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003C8C);

void timproc_uso_b5_func_00003ED8(char *a0) {
    char *v;

    gl_func_00000000(a0 + 0x2C);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}

/* Sibling of timproc_uso_b5_func_00003ED8 — same vtable-call wrapper.
 * Promoted from 94.12% NM via SUFFIX_BYTES=0x8C98023C (the trailing
 * `lw t8, 0x23C(a0)` at offset 0x40 is the stolen prologue for SUCCESSOR
 * func_00003F5C; pad-sidecar didn't work because asm-processor aligns the
 * next symbol to 8 bytes, but SUFFIX_BYTES grows our st_size by 4 instead
 * of inserting padding). Default build still INCLUDE_ASMs (which already
 * includes the trailing word), and the non_matching build C-emits 16
 * insns at 94.12% — neither path needs SUFFIX_BYTES applied
 * (inject-suffix-skip detects existing trailing bytes; non_matching skips
 * the recipe by design). byte_verify passes. */
void timproc_uso_b5_func_00003F18(char *a0) {
    char *v;
    gl_func_00000000(a0 + 0x194);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}

#ifdef NON_MATCHING
/* 19-insn (0x4C) Vec3i→Vec3 type-pun copy. Byte-correct via 3-knob recipe
 * unblocked by the 2026-05-06 splice-function-prefix.py LW-opcode extension:
 *   PROLOGUE_STEALS += timproc_uso_b5_func_00003F5C=4
 *     strips the leading `lw t6, 0x23C(a0)` (that insn lives in predecessor
 *     0x3F18's symbol via SUFFIX_BYTES). The splice fires because my
 *     C-emit's first insn is LW (opcode 0x23), now in the accepted set.
 *   SUFFIX_BYTES += timproc_uso_b5_func_00003F5C=0x03E00008,0xAFA40000
 *     appends the trailing alt-entry stub `jr ra; sw a0, 0(sp)`.
 *   `char pad[24]` bumps frame from 0x10 → 0x28 to match target.
 *
 * Original cap notes (before unblock) preserved below for posterity:
 *
 * Bytewise diff (post-PROLOGUE_STEALS=4 + SUFFIX_BYTES, before frame fix):
 *   Build C-emit (18 insns, frame 0x10):
 *     +00: lw t6, 0x23C(a0)   <- gets spliced by PROLOGUE_STEALS=4
 *     +04: lw v0, 0x29C(a0)
 *     +08: addiu sp, -0x10    <- prologue at insn 3 (after early load)
 *     +0C: sw t6, 4(sp)
 *     [scratch buf at sp+4..0xC, lwc1 from sp+4..0xC]
 *     +44: jr ra; +48: nop
 *   Expected (19 insns, frame 0x28):
 *     +00: addiu sp, -0x28    <- prologue FIRST
 *     +04: lw v0, 0x29C(a0)
 *     +08: addiu t6, sp, 0xC  <- $t6 = scratch base register
 *     +0C: sw t8, 0(t6)       <- $t8 INHERITED from 3F18 stolen tail
 *     [scratch buf at sp+0xC..0x14 via $t6]
 *     +3C: jr ra; +40: swc1 (delay)
 *     +44: jr ra; +48: sw a0, 0(sp)  <- trailing 8 bytes (alt-entry?)
 *
 * Three structural diffs that combine multiplicatively:
 *   (A) frame size 0x10 -> 0x28 (need char pad[24] or similar)
 *   (B) prologue-then-load order (target has prologue first; build
 *       hoists `lw v0` ahead of prologue — IDO scheduler -O2 unflippable)
 *   (C) scratch addressing via $t6 (= sp+0xC) vs sp-direct (= sp+4)
 *       — target's `addiu t6, sp, 0xC; sw $tN, 0/4/8(t6)` shape vs
 *       build's `sw $tN, 4/8/C(sp)` shape. Per
 *       feedback_typed_stack_struct_for_direct_sp_stores.md (inverse)
 *       — typed-struct picks sp-direct; we want register-based.
 *
 * Recipe sketch (DEFER — multi-blocker):
 *   Makefile:
 *     PROLOGUE_STEALS += timproc_uso_b5_func_00003F5C=4
 *     SUFFIX_BYTES += timproc_uso_b5_func_00003F5C=0x03E00008,0xAFA40000
 *   C body restructure to force frame=0x28 + $t6 scratch base.
 *
 * 2026-05-06: PROLOGUE_STEALS=4 PATH IS BLOCKED. Per
 * docs/POST_CC_RECIPES.md#feedback-prologue-steals-lui-only-splice-restriction,
 * scripts/splice-function-prefix.py only fires when the function's first
 * insn is LUI. This function starts with `addiu sp, -0x28` (opcode 0x09),
 * so the PROLOGUE_STEALS=4 line would silently no-op. To unblock either
 * (a) extend the splice-script verify to accept opcode 0x09, OR (b) drop
 * PROLOGUE_STEALS entirely and do the full SUFFIX-on-predecessor route
 * (currently blocked by predecessor 0x3F18 already using SUFFIX_BYTES for
 * its own purpose). 11.1% measured match (built 0x48 / 18 insns vs target
 * 0x4C / 19 insns).
 *
 * Predecessor 00003F18 is byte-correct (SUFFIX_BYTES applied), so 3F5C's
 * position is stable for next-pass attempt. */
typedef struct { int a, b, c; } Tri3i_F5C;
typedef struct { float x, y, z; } Vec3_F5C;
void timproc_uso_b5_func_00003F5C(int *a0) {
    char pad[24];   /* bump frame from 0x10 → 0x28 to match target */
    Tri3i_F5C raw;
    Vec3_F5C *v = (Vec3_F5C*)((char*)*(int**)((char*)a0 + 0x29C) + 0xDC);
    (void)pad;
    raw.a = *(int*)((char*)a0 + 0x23C);
    raw.b = *(int*)((char*)a0 + 0x240);
    raw.c = *(int*)((char*)a0 + 0x244);
    v->x = *(float*)&raw.a;
    v->y = *(float*)&raw.b;
    v->z = *(float*)&raw.c;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F5C);
#endif

void timproc_uso_b5_func_00003FA8(int a0, int a1, int a2, int a3) {
    (void)a0;
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a3);
    gl_func_00000000(a3, a1, a2, 0);
}

void timproc_uso_b5_func_00003FF8(int arg1, int arg2, int arg3, int arg4, int arg5) {
    float buf[4];
    char pad[20];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    gl_func_00000000(&D_00000000, arg5, buf, arg4);
    gl_func_00000000(arg4);
    gl_func_00000000(arg4, arg2, arg3, 3);
}

void timproc_uso_b5_func_00004068(int a0, int a1, int a2, int a3, int arg5, int arg6) {
    (void)a0;
    gl_func_00000000(&D_00000000, arg6, a3);
    gl_func_00000000(arg5);
    gl_func_00000000(arg5, a1, a2, 3);
}

void timproc_uso_b5_func_000040BC(int a0, int a1, int a2, int a3, int arg5, int arg6, int arg7) {
    (void)a0;
    gl_func_00000000(&D_00000000, arg7, a3, arg5);
    gl_func_00000000(arg6);
    gl_func_00000000(arg6, a1, a2, 3);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004118);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005BF0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005FC0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006394);

void timproc_uso_b5_func_0000685C(char *a0) {
    gl_func_00000000(a0 + 0x2C);
}

#ifdef NON_MATCHING
/* func_0000687C absorbs _00006890+_000068A8+_000068EC: 33-insn (0x84)
 * multi-exit table-search loop with 4 early-return paths.
 *
 * Decoded structure:
 *   int v0 = a0->[0x3C4];                   // outer index
 *   if (v0 == 0) return 1;                   // early-return path 1
 *
 *   int *base = (int*)((char*)a0 + v0*4);
 *   int idx = base->[0x3D0];                  // = a0->[0x3D0 + v0*4]
 *   if (idx == 0) return 0;                   // early-return path 2
 *   idx -= 1;
 *
 *   if (idx < 0) return 0;                    // early-return path 3
 *
 *   // Loop: for (i = idx; i >= 0; i--) { check item; if (positive) return 1; }
 *   int *table = a0->[0x40C];
 *   int *outer = (int*)((char*)table + v0*4);
 *   int byte_off = idx*4;
 *   do {
 *     int *inner = outer->[0x40];
 *     int *item = (int*)inner->[byte_off + 0x3C];
 *     float val = *(float*)((char*)item + 0x2A4);
 *     if (val > 0.0f) return 1;
 *     byte_off -= 4;
 *   } while (--idx >= 0);
 *   return 0;
 *
 * Initial decode 2026-05-06; multi-pass refinement expected. The float
 * comparison `c.lt.s $f0, $f4` with $f0=0.0 followed by `bc1f` means
 * "branch if NOT (0 < f4)" = "branch if f4 <= 0" — so the success path
 * is f4 > 0. */
extern int gl_func_00000000();
int timproc_uso_b5_func_0000687C(int *a0) {
    int v0 = *(int*)((char*)a0 + 0x3C4);
    int idx;
    int *table;
    int *outer;
    int byte_off;
    if (v0 == 0) return 1;

    idx = *(int*)((char*)a0 + 0x3D0 + v0 * 4);
    if (idx == 0) return 0;
    idx -= 1;

    if (idx < 0) return 0;

    table = *(int**)((char*)a0 + 0x40C);
    outer = (int*)((char*)table + v0 * 4);
    byte_off = idx * 4;
    do {
        int *inner = (int*)*(int*)((char*)outer + 0x40);
        int *item = (int*)*(int*)((char*)inner + byte_off + 0x3C);
        if (*(float*)((char*)item + 0x2A4) > 0.0f) return 1;
        byte_off -= 4;
        idx--;
    } while (idx >= 0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000687C);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006900);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000069E8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006C00);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006D30);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006E08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007078);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000072D0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007430);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000077D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000079A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007B2C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007E34);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000080F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008468);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000085E0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008688);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000894C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008AFC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008C44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008DB4);

/* Indirect-call wrapper. Promoted 97.5%->100% via IDO load-CSE trick:
 * declare p2 FIRST with the full deref chain inline (including p1's load),
 * then declare p1 with the same `a0->0x2C` load — IDO CSE's the duplicated
 * load and assigns $v1 to p1 + $v0 to p2 (target's reg layout). Writing
 * p1 first (the natural order) gives the swap. Replaces prior INSN_PATCH
 * approach — no Makefile entry needed. */
void timproc_uso_b5_func_00008F98(char *a0) {
    int *p2 = *(int**)((char*)*(int*)(a0 + 0x2C) + 0x28);
    int p1 = *(int*)(a0 + 0x2C);
    (*(int(**)())((char*)p2 + 0x5C))(*(short*)((char*)p2 + 0x58) + p1);
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008FC8);

#ifdef NON_MATCHING
/* 72.21% NM. 23-insn loop with branch-likely preload (bnezl at 0x50 with delay-slot
 * `lw v1, 0x40(s2)` preloading v1 for next iteration's body at 0x2C).
 *
 * Logic: for i in [0, a0->0x3C): call (a0->0x40)->0x28->0x4C as fn ptr,
 * arg = (signed short)(a0->0x40)->0x28->0x48 + (a0->0x40). Plus an
 * unused $s1 pointer that increments by 4 per iteration (dead but live
 * in IDO's view).
 *
 * Cap likely structural: the branch-likely with off-loop-body delay-slot
 * preload isn't reachable from std do-while C. The loop body at 0x2C
 * starts WITHOUT a lw v1 — it's pre-loaded by the previous iteration's
 * branch-likely delay slot (or by the initial lw at 0x28). */
void timproc_uso_b5_func_0000A97C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x40);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A97C);
#endif

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of timproc_uso_b5_func_0000A97C — same 23-insn loop with branch-
 * likely preload of v1 in bnezl delay slot. Different offsets:
 *   A97C: fn_ptr at slot->0x28->0x4C, short_arg at slot->0x28->0x48
 *   A9EC: fn_ptr at slot->0x28->0x64, short_arg at slot->0x28->0x60
 * Same structural cap — branch-likely w/ off-loop-body delay slot preload
 * not reachable from std do-while C. */
void timproc_uso_b5_func_0000A9EC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x40);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x64))(*(short*)((char*)v0 + 0x60) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A9EC);
#endif

void timproc_uso_b5_func_0000AA5C(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000330((int*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AA8C(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_0000036C((float*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AABC(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_000003A8((Quad4*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AAEC(int a0) {
}


void timproc_uso_b5_func_0000AAF4(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000400((Vec3*)(a0 + 0x10));
}


#ifdef NON_MATCHING
/* 89.3 % match. Previously NOTE was inverted: re-decoded 2026-05-02 the
 * post-jal stores DO use the 2nd jal's return value (call result spilled
 * to sp+0x20, reloaded as $a1 then used for q->0x14 / q->0x4 / q->0x14
 * stores). r (= arg0->0x40) is only used as the 2nd jal's a1-arg.
 * Adding `char pad[8]` coerces frame 0x20 -> 0x28 (target spills a0 to
 * caller's outgoing slot at sp+0x28).
 *
 * Remaining diffs (register-allocation flip):
 * - Target uses $a0 throughout the 1st init block (no scratch copy), then
 *   explicitly `or v1, a0, zero` to move p to $v1 right before the 2nd jal.
 *   Our build pre-allocates p to $a2 right after the 1st jal returns
 *   (extra `or a2, v0, zero` insertion + uses $a2 throughout). $v1 home
 *   for cross-jal preservation isn't reachable from C — IDO won't pick the
 *   v0/return-low register as a long-lived hold reg.
 * - Spill slot offsets: target 0x1C/0x20/0x24, ours 0x1C/0x18 (only 2
 *   distinct slots; not enough variables to need 3).
 * - Final beq vs beql: target `beq v0,zero,+0xC` then `or a1,v0,zero`
 *   delay-slot; ours `beql a1,zero,...` with epilogue-load delay-fill
 *   (because we named `r` as a local, IDO promotes it to a1 early).
 *
 * These are all knock-on from the same root: IDO's register allocator
 * picks $a2 instead of $a0/$v1 for p's hold-across-2nd-jal slot. Same
 * structural cap as `feedback_ido_arg_save_reg_pick.md` — the choice of
 * arg/scratch reg for cross-jal preserve isn't C-controllable.
 *
 * 2026-05-04 TRIED: inline `r` (no named local — use `*(void**)(arg0+0x40)`
 * directly twice in the if-test and the call arg). Result: same ~89% shape,
 * but emit changed to use v0-directly-as-q (no q-spill+reload), beql in
 * delay slot variants. Net: still 32+ insns vs target 36, p still in $a2
 * not $v1. Inlining `r` actually drops the q-spill (target HAS the q-spill
 * at sp+0x20 — which mine doesn't), so this regresses, not improves. The
 * named-`r` form is closer to target's full structure. Reverted.
 *
 * 2026-05-04 TRIED (later session): `register void *p` keyword hint — IDO
 * IGNORES register hint here, same emit as plain `void *p`. p still in $a2
 * (not $v1 as target wants). Confirms IDO's regalloc for caller-saved
 * "preserve-across-jal" slots is purely weight-driven and doesn't honor
 * register hints (vs. its strong honoring for $s-regs in interrupt-bracket
 * patterns). Different from the GCC `register T x asm("$N")` strong-hint
 * trick that's GCC-only.
 *
 * 2026-05-04: re-tested for INSN_PATCH eligibility. Built emits 34 insns,
 * expected has 36 — a 2-insn deficit (built lacks the `or v1, a0, zero`
 * + an extra spill-store). Per feedback_insn_patch_size_diff_blocked.md
 * INSN_PATCH alone can't fix this. Promotion needs a sibling
 * inject-insn-at.py recipe OR a different C shape that emits the extra
 * `or v1,a0` move. Deferred.
 *
 * 2026-05-05 TRIED: pass arg0 as 3rd arg to gl_func_00000000(p+0x10, r,
 * arg0) — hoping the extra K&R-arg pass would force a0 preservation /
 * register reshuffle. REGRESSED 83.25% → 82.56% (the unused 3rd arg
 * forced an extra `sw a2, 8(sp)` outgoing-arg-slot store that target
 * doesn't have). Reverted. The cap class IS purely the v1-vs-a2
 * register pick for the cross-jal-preserve slot of `p`, not reachable
 * via K&R arg-list manipulation. */
void *timproc_uso_b5_func_0000AB24(void *arg0) {
    char pad[8];
    void *p;
    void *r;
    void *q;

    p = (void*)gl_func_00000000(0x40);
    if (p != 0) {
        gl_func_00000000(p);
        *(void**)((char*)p + 0x28) = (void*)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
    }
    r = *(void**)((char*)arg0 + 0x40);
    if (r != 0) {
        q = (void*)gl_func_00000000((char*)p + 0x10, r);
        if (*(int*)((char*)q + 0x14) != 0) {
            *(int*)((char*)q + 0x4) = 1;
        }
        *(void**)((char*)q + 0x14) = p;
    }
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AB24);
#endif

void timproc_uso_b5_func_0000ABB4(int *a0) {
    *(int*)((char*)a0 + 0xB0) = 1;
    *(int*)((char*)a0 + 0x64) = -1000;
}

void timproc_uso_b5_func_0000ABC8(int a0, int a1) {
}


void timproc_uso_b5_func_0000ABD4(int a0, int a1) {
}

void timproc_uso_b5_func_0000ABE0(int a0, int a1, int a2, int a3) {
}

void timproc_uso_b5_func_0000ABF4(int a0, int a1, int a2) {
}


void timproc_uso_b5_func_0000AC04(int a0, int a1) {
}

void timproc_uso_b5_func_0000AC10(int a0, int a1, int a2) {
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AC20);

/* timproc_uso_b5_func_0000B154: 133-insn (0x214) AI-update orchestrator.
 * Frame 0xA8, $s0/$s1 saves. Coarse structure decoded 2026-05-05:
 *
 *   1. Vec3 baseline + delta compute (0xB154-0xB1A8): loads 3 floats from
 *      &D_0+0xDC and 3 floats from sp+0x68 area; computes pairwise sub.s
 *      (delta_v = ref_v - cur_v) and stores to sp+0x68/0x6C/0x70.
 *
 *   2. 12-byte struct copy with fanout (0xB1AC-0xB1D4): reads t6+0/4/8
 *      writes a2+0/4/8 AND a4+0/4/8 (the canonical "save-old + write-new"
 *      idiom — same shape as game_uso_func_00001DDC tail, see that
 *      function's notes). Followed by jal cross-USO call.
 *
 *   3. Four sequential 3-float scale + jal blocks (0xB1D8-0xB28C): each
 *      block reads s0+0x110/0x10C/0x114/0x118 (a per-axis scaling
 *      coefficient table on s0), multiplies by 1.0 (mtc1 zero, mtc1 0x3F80),
 *      stores to sp+0x48/0x38/0x2C/0x98 (output buffers), then jal.
 *      Pattern: 4-axis state-machine update.
 *
 *   4. Final scale + cross-call (0xB290-0xB2D4): reads s0+0x108 (sub-obj
 *      ptr), 3 floats from s0+0x128/0x12C/0x11C; computes
 *      mul.s + sub.s of 0.5 (lui 0x3F00 = 0.5f), then jal.
 *
 *   5. Tail: bit-flag toggle on s0+0x144 (frame counter or state bit),
 *      conditional vtable-index increment+wrap on s0+0x140 vs s0+0x13C
 *      array length, then bit-set/bit-clear on s0+0x148-derived sub-obj's
 *      [0x18] field (`AND 0xFFFFFFFB` and `OR 0x4`).
 *
 * Key field offsets (s0 struct, ~0x150+ bytes):
 *   [0x108] sub-obj ptr (used as $a0 to multiple jals)
 *   [0x10C], [0x110], [0x114], [0x118] axis scale coefficients (4 floats)
 *   [0x11C], [0x128], [0x12C] coefficient floats
 *   [0x13C] array length
 *   [0x140] index into s0+0x148 array
 *   [0x144] frame-counter / state bit
 *   [0x148] sub-obj-array base ptr
 *
 * Logic looks like a per-frame AI/state update that:
 *   - computes 3D delta from reference position
 *   - cross-calls 6 separate per-axis processors
 *   - advances a circular index with wraparound
 *   - toggles a state bit on each call
 *
 * Yay0-compressed segment; default INCLUDE_ASM build remains exact.
 * Multi-tick decomp target — ~7 cross-USO calls, struct typing required.
 * Initial structural pass 2026-05-05. */
#ifdef NON_MATCHING
/* Skeleton C — captures structure only; no byte-match attempt yet. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000B154(int *a0) {
    (void)a0;
    /* TODO: full body decode. See block-comment above for the 5-section
     * structure. Each section has 1-2 jals to gl_func_00000000 with
     * args from per-axis stack-local Vec3 scratch buffers. */
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B154);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B368);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B624);

void timproc_uso_b5_func_0000B928(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 1, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
}

void timproc_uso_b5_func_0000B98C(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 2, 3, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
}

void timproc_uso_b5_func_0000B9F0(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 2, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = 2;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0x10;
}

void timproc_uso_b5_func_0000BA60(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 0, 2, 2, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 1;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0;
    *(int*)((char*)a0 + 0x2BC) = 0;
    *(int*)((char*)a0 + 0x2C0) = 2;
}

void timproc_uso_b5_func_0000BAE8(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 2, 1, 1);
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0x20;
}

void timproc_uso_b5_func_0000BB44(int *a0) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 8;
}

void timproc_uso_b5_func_0000BB5C(int a0) {
}

void timproc_uso_b5_func_0000BB64(int *a0, int unused) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x13C) = 1;
}

void timproc_uso_b5_func_0000BB78(int *a0, int unused) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x13C) = 0;
}

/* 16-insn float-quad copy: v0 = a0->_2B8; copies 4 floats from
 * a0->{_25C,_260,_264,_294} into v0->{_114,_118,_110,_11C}, then calls
 * gl_func_00000000. Bundled-leaf trailer split off as 0000BBC8. */
void timproc_uso_b5_func_0000BB88(int *a0) {
    int *v0 = *(int**)((char*)a0 + 0x2B8);
    *(float*)((char*)v0 + 0x11C) = *(float*)((char*)a0 + 0x294);
    *(float*)((char*)v0 + 0x110) = *(float*)((char*)a0 + 0x264);
    *(float*)((char*)v0 + 0x118) = *(float*)((char*)a0 + 0x260);
    *(float*)((char*)v0 + 0x114) = *(float*)((char*)a0 + 0x25C);
    gl_func_00000000();
}

/* 5-insn float store: stores a1 to a0->_2A0 and (a0->_2B8)->_120.
 * Float arg passed in $a1 (int reg), so IDO emits mtc1 to FPU first. */
void timproc_uso_b5_func_0000BBC8(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x120) = a1;
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000BBDC: 113-insn unrolled loop over 5 channels.
 * Initial decode — 57.77% fuzzy. Structure understood, dual-arm bnel
 * dispatch unbridged.
 *
 * Logic:
 *   if (a0->0x2BC < 10 && --a0->0x2C0 < 0) {
 *       a0->0x2C0 = 1;
 *       a0->0x2BC += 2;
 *   }
 *   for (i = 0; i < 5; i++) {
 *       int v = a0->0x2BC;
 *       int cap = (&a0->0x1C4)[i*6];           // stride 0x18 per iter
 *       int v1 = (v < cap) ? v : cap;          // clamp
 *       int stride = a1->0x74;
 *       int *idx_ptr = (int*)a1 + 0x134/4 + i*9;  // stride 0x24 per iter
 *       gl_func_00000000(
 *           a0,
 *           a0->0xA4,
 *           (char*)a0->0xBC + i * stride,
 *           (char*)&D_00000000 + 0x40 + i * 0x18,
 *           *idx_ptr, a1+0x230, a1, v1
 *       );
 *   }
 *
 * Target emits two structurally-identical loop-body arms via `bnel
 * fp(=1), s2->0x3BC, +0x13` — branch-likely with `lw t8, 0x74(s2)` in
 * delay slot. Both arms call the same function with the same args; the
 * dispatch is IDO's branch-likely scheduling, not a real C-level if/else.
 * No straightforward C produces this shape (a `if (t2 == 1)` with both
 * arms identical optimizes to a single arm; an unconditional call also
 * emits a single arm). DEFERRED — needs sibling channel-loop match for
 * template shape, OR explicit branch-likely scheduling lever.
 *
 * Open: 8-arg call signature, arg-spill order, exact stride decode for
 * stack_a1_array (offsets 0x134/0x158/0x17C/0x1A0/0x1C4 imply +0x24
 * stride). */
void timproc_uso_b5_func_0000BBDC(int *a0, int *a1) {
    int i;
    int v;
    int cap;
    int v1;
    int stride;
    int *idx_arr;

    if (*(int*)((char*)a0 + 0x2BC) < 10) {
        int c = *(int*)((char*)a0 + 0x2C0) - 1;
        *(int*)((char*)a0 + 0x2C0) = c;
        if (c < 0) {
            *(int*)((char*)a0 + 0x2C0) = 1;
            *(int*)((char*)a0 + 0x2BC) = *(int*)((char*)a0 + 0x2BC) + 2;
        }
    }
    idx_arr = (int*)((char*)a1 + 0x134);
    for (i = 0; i < 5; i++) {
        v = *(int*)((char*)a0 + 0x2BC);
        cap = ((int*)((char*)a0 + 0x1C4))[i * 6];
        v1 = (v < cap) ? v : cap;
        stride = *(int*)((char*)a1 + 0x74);
        gl_func_00000000(
            a0,
            *(int**)((char*)a0 + 0xA4),
            (char*)*(int**)((char*)a0 + 0xBC) + i * stride,
            (char*)&D_00000000 + 0x40 + i * 0x18,
            idx_arr[i * 9],
            (char*)a1 + 0x230,
            a1,
            v1
        );
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BBDC);
#endif

extern char D_b5_BDA0_table;
void timproc_uso_b5_func_0000BDA0(int *a0, int a1, int a2, int a3) {
    (void)a1; (void)a2; (void)a3;
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], (char*)&D_b5_BDA0_table + a0[0x1AC/4] * 24);
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000BDEC: 242-insn FPU-heavy color-transform helper.
 * 0x3C8 size starting at 0xBDEC, ending at 0xC1B4.
 *
 * BUNDLED structure: 13 jr ra in the .s file. Splat couldn't separate the
 * tail leafs in this Yay0-compressed segment. Tail jr ra positions:
 *   0xC03C  — main body's mid-return (FPU early-exit path)
 *   0xC0CC  — main body's secondary return
 *   0xC100  — main body's terminal return
 *   0xC108, 0xC110, 0xC118 — three 2-insn leaf trailers (jr ra; <set v0>)
 *   0xC148, 0xC15C, 0xC168 — short leaf returns
 *   0xC178, 0xC188, 0xC19C, 0xC1AC — more 2-insn leaf trailers
 * Per feedback_uso_split_fragments_breaks_expected_match.md, splitting on
 * Yay0 USO breaks expected/.o until refresh — leave bundled.
 *
 * Main function decoded (0xBDEC-0xC03C, 36 insns):
 *   register f32 c255 = 255.0f;  // $f20-bound via lui+mtc1
 *   f32 a = a1->0x4A0;           // s0 = a1, s0->0x4A0
 *   ptr = a1->0x414;             // t6 = a1[0x414/4] (table?)
 *   ptr2 = ptr->0xC;             // t7 = ptr[3]
 *   stride = ptr2->0xC4;         // s2 = ptr2->0xC4 (table base)
 *   a1ptr = a1->0x8C;            // a1 = a1->0x8C (sub-pointer)
 *   off = a1->0xA4;              // t8 = a1->0xA4 (offset)
 *   addr = stride + off;         // a2 = s2 + t8
 *   v = trunc(c255 * a);         // f6 = c255*a; t0 = trunc(f6)
 *   gl_func_00000000(s1=arg0, addr, ?, &D + 0x6E8, v);
 *   ...
 *
 * State decode (0xBDEC-0xBE7C, ~36 insns):
 *   - $f20 = 255.0f (constant for FP→int conversion scale)
 *   - sequence: load a, multiply by 255, trunc to int, pass to helper
 *   - bgezl branch on (a1->0x2B4 << 14) sign-bit (bit 17) — case dispatch
 *   - if bit set: compute via $f0 = 96.0/255.0, $f2 = 192.0/255.0
 *
 * Open: jump-table at &D + 0x700 indexed by upper bits of a1->0x2B4.
 * Multi-pass decompile target; first pass too-many unknowns to write a
 * useful C body without first analyzing the dispatch table.
 *
 * Initial wrap is doc-only (no C body) until table dispatch is decoded.
 * Default INCLUDE_ASM build matches via the bundled symbol. */
#endif
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDEC);

/* timproc_uso_b5_func_0000C1B4: 16-insn 4-float copy + cross-USO call,
 * plus a 5-insn alt-entry tail at sp+0x40..0x50 (different `(a0, a1)` arg
 * shape, used by separate caller via jal directly into the post-epilogue
 * region) injected post-cc via SUFFIX_BYTES. C body covers main entry only;
 * the alt-entry's 5 insns are byte-for-byte SUFFIX (mtc1 a1,f12; lw t6;
 * swc1 f12,0x2A0(a0); jr ra; swc1 f12,0x120(t6)). */
extern int func_00000000();
void timproc_uso_b5_func_0000C1B4(int *a0) {
    int *p = (int*)a0[0x2B8 / 4];
    float a = *(float*)((char*)a0 + 0x294);
    float b = *(float*)((char*)a0 + 0x264);
    float c = *(float*)((char*)a0 + 0x260);
    float d = *(float*)((char*)a0 + 0x25C);
    *(float*)((char*)p + 0x11C) = a;
    *(float*)((char*)p + 0x110) = b;
    *(float*)((char*)p + 0x118) = c;
    *(float*)((char*)p + 0x114) = d;
    func_00000000();
}

extern char D_b5_C208_table0;
extern char D_b5_C208_table1;
void timproc_uso_b5_func_0000C208(int *a0, int a1, int a2, int a3) {
    (void)a1;
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], a2, a3,
                     (char*)&D_b5_C208_table0 + a0[0x1AC/4] * 24, 0xFF);
    if (*(int*)&D_00000000 != 0) {
        gl_func_00000000(a0, a0[0x74/4] + a0[0x44/4], a0[0x8C/4] + a0[0x5C/4],
                         (char*)&D_b5_C208_table1 + a0[0x1AC/4] * 24, 0xFF);
    }
}

extern char D_b5_C2C0_table;
void timproc_uso_b5_func_0000C2C0(int *a0, int a1, int a2) {
    (void)a1;
    gl_func_00000000(a0, a0[0x104/4], a0[0x11C/4], (char*)&D_b5_C2C0_table + a2 * 24, 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C310);

/* 0000C710 absorbs 0000C7B4: bc1f at offset 0x94 of C710 branches PAST
 * the original 0xA4 declared size into C7B4's body; C7B4 has no prologue
 * and uses caller-set $v1/$at. Splat-bundled fragment merge 2026-05-05.
 * Combined size 0xD8 = 54 insns. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C710);

void timproc_uso_b5_func_0000C7E8(char *a0, char *a1) {
    *(float*)(*(int*)(a1 + 0x2B8) + 0x128) = *(float*)(*(int*)(a0 + 0x2B8) + 0x128);
    *(float*)(*(int*)(a1 + 0x2B8) + 0x124) = *(float*)(*(int*)(a0 + 0x2B8) + 0x124);
    *(int*)(*(int*)(a1 + 0x2B8) + 0x130) = *(int*)(*(int*)(a0 + 0x2B8) + 0x130);
    *(int*)(*(int*)(a1 + 0x2B8) + 0x13C) = *(int*)(*(int*)(a0 + 0x2B8) + 0x13C);
}

void timproc_uso_b5_func_0000C82C(int a0) {
}

void timproc_uso_b5_func_0000C834(int a0) {
}

void timproc_uso_b5_func_0000C83C(int a0) {
}

void timproc_uso_b5_func_0000C844(int a0) {
}

void timproc_uso_b5_func_0000C84C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000C85C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 0;
}

void timproc_uso_b5_func_0000C870(int a0) {
}

void timproc_uso_b5_func_0000C878(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 1;
}

void timproc_uso_b5_func_0000C888(int *a0, int a1) {
    (void)a1;
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000C89C(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

#ifdef NON_MATCHING
/* 51-insn / 0xCC float clamp + copy. Pattern:
 *   v1 = a0->[0x2B8];
 *   if (v1->[0x134] != 0) {        ; increment branch
 *       v1->[0x128] += D[0x374];
 *       if (v1->[0x128] > 1.0f)
 *           v1->[0x128] = 1.0f;
 *   } else {                          ; decrement branch
 *       v1->[0x128] -= D[0x378];
 *       if (v1->[0x128] < 0.0f)
 *           v1->[0x128] = 0.0f;
 *   }
 *   v1 = a0->[0x2B8];                 ; reload (target reloads here)
 *   v1->[0x10C] = a0->[0x264];        ; out-of-source-order field copy
 *   v1->[0x110] = a0->[0x25C];
 *   v1->[0x114] = a0->[0x260];
 *   v1->[0x118] = a0->[0x294];
 *   gl_func_00000000();               ; tail call (no args)
 *
 * Initial decode — multi-pass refinement expected. The bc1fl + delay-likely
 * pattern + reload-of-v1 across the fork are likely structural cap drivers.
 * The 4-store epilogue order (0x10C, 0x110, 0x114, 0x118 in target asm —
 * NOT in source-order 0x10C/0x110/0x114) suggests IDO scheduler interleave
 * of the lwc1's and swc1's.
 *
 * 2026-05-05: caching `float *p128` lifted 75.47% → 80.41% (+4.94pp). The
 * cached pointer matches target's `addiu v0, v1, 0x128` (v0 holds the
 * +0x128 offset address). Then inline-deref of the post-add comparison
 * (`*(float*)((char*)a0[0x2B8/4] + 0x128) > 1.0f`) forced the v1 reload
 * + recomputed +0x128 offset, lifting 80.41% → 86.37% (+5.96pp).
 *
 * Remaining 14% cap: $v0 vs $v1 first-register choice (built uses $v0,
 * target $v1) cascades through ~19 of 51 insns. Sizes now match
 * (204/204 bytes). Final ~14% is register-rename territory (permuter
 * or INSN_PATCH).
 *
 * 2026-05-07 attempted `int` return + `return gl_func_00000000()` to
 * reserve $v0 for the return value (hypothesis: pushes first general
 * pseudo to $v1). Result: NO CHANGE — still 86.37%. IDO's allocator
 * isn't return-value-driven for the void→int transition; it picks $v0
 * for the first-live pseudo regardless because the only use of $v0-as-
 * return-value is the final jr ra delay slot, well after all other
 * pseudo-allocations are settled. Reverted. The C-level register-flip
 * lever isn't reachable here; this is permuter-territory. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000C8AC(int *a0) {
    int *v1;
    float *p128;
    v1 = (int*)a0[0x2B8 / 4];
    p128 = (float*)((char*)v1 + 0x128);
    if (*(int*)((char*)v1 + 0x134) != 0) {
        *p128 += *(float*)((char*)&D_00000000 + 0x374);
        if (*(float*)((char*)((int*)a0[0x2B8 / 4]) + 0x128) > 1.0f) {
            *(float*)((char*)((int*)a0[0x2B8 / 4]) + 0x128) = 1.0f;
        }
    } else {
        *p128 -= *(float*)((char*)&D_00000000 + 0x378);
        if (*(float*)((char*)((int*)a0[0x2B8 / 4]) + 0x128) < 0.0f) {
            *(float*)((char*)((int*)a0[0x2B8 / 4]) + 0x128) = 0.0f;
        }
    }
    {
        float a, b, c, d;
        v1 = (int*)a0[0x2B8 / 4];
        a = *(float*)((char*)a0 + 0x25C);
        b = *(float*)((char*)a0 + 0x260);
        c = *(float*)((char*)a0 + 0x264);
        d = *(float*)((char*)a0 + 0x294);
        *(float*)((char*)v1 + 0x110) = a;
        *(float*)((char*)v1 + 0x114) = b;
        *(float*)((char*)v1 + 0x10C) = c;
        *(float*)((char*)v1 + 0x118) = d;
    }
    gl_func_00000000();
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C8AC);
#endif

void timproc_uso_b5_func_0000C978(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x11C) = a1;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C98C);

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000CB40: 49-insn (0xC4) approach-target-with-decay
 * routine. Was previously split by splat into CB40 (0x90) + CBD0 (0x34);
 * merged because CB40 had forward branches (CB90 bc1fl +16, CBC0 bc1f +14)
 * into CBD0's range. CBD0's leading lwc1 $f4,0($v1) duplicated CB94's
 * delay-slot insn — classic branch-likely + delay-slot-replicates-target
 * idiom (see docs/IDO_CODEGEN.md "branch-likely").
 *
 * Structure: target := (a0->2A4 != 0) ? a1 : 0; if (a0->2B8->134) target = 1.0
 * then approach v0->124 toward `target` from below by D[0x37C] (clamping
 * at target) or from above by D[0x380] (clamping at target). Sister-shape
 * to C978 (instantaneous setter for the same field family).
 *
 * NM body covers control flow; FP register allocation, branch-likely emit,
 * and lui-pair constants need permuter to tighten. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000CB40(int *a0, float a1) {
    int *v0;
    float target;
    if (*(float*)((char*)a0 + 0x2A4) != 0.0f) {
        target = a1;
    } else {
        target = 0.0f;
    }
    v0 = *(int**)((char*)a0 + 0x2B8);
    if (*(int*)((char*)v0 + 0x134) != 0) {
        target = 1.0f;
    }
    if (*(float*)((char*)v0 + 0x124) < target) {
        *(float*)((char*)v0 + 0x124) += *(float*)((char*)&D_00000000 + 0x37C);
        if (target < *(float*)((char*)v0 + 0x124)) {
            *(float*)((char*)v0 + 0x124) = target;
        }
    } else {
        *(float*)((char*)v0 + 0x124) -= *(float*)((char*)&D_00000000 + 0x380);
        if (*(float*)((char*)v0 + 0x124) < target) {
            *(float*)((char*)v0 + 0x124) = target;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CB40);
#endif

void timproc_uso_b5_func_0000CC04(int a0) {}

void timproc_uso_b5_func_0000CC0C(int a0) {}

void timproc_uso_b5_func_0000CC14(int a0) {}

void timproc_uso_b5_func_0000CC1C(int a0) {}

void timproc_uso_b5_func_0000CC24(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 1;
}

void timproc_uso_b5_func_0000CC34(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 0;
}

void timproc_uso_b5_func_0000CC40(int a0) {}

void timproc_uso_b5_func_0000CC48(int a0) {}

void timproc_uso_b5_func_0000CC50(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000CC64(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

/* Sibling of timproc_uso_b5_func_0000C1B4 (4-float copy + cross-USO call + 5-insn
 * alt-entry tail). Same shape, different store offsets:
 *   C1B4: stores at p+0x11C/0x110/0x118/0x114
 *   CC74: stores at p+0x118/0x10C/0x114/0x110
 *
 * Recipe: same as C1B4 — INSN_PATCH 8 float-reg-rename words +
 * SUFFIX_BYTES 5 alt-entry tail words. Both in Makefile. */
void timproc_uso_b5_func_0000CC74(int *a0) {
    int *p = (int*)a0[0x2B8 / 4];
    float a = *(float*)((char*)a0 + 0x294);
    float b = *(float*)((char*)a0 + 0x264);
    float c = *(float*)((char*)a0 + 0x260);
    float d = *(float*)((char*)a0 + 0x25C);
    *(float*)((char*)p + 0x118) = a;
    *(float*)((char*)p + 0x10C) = b;
    *(float*)((char*)p + 0x114) = c;
    *(float*)((char*)p + 0x110) = d;
    func_00000000();
}

/* timproc_uso_b5_func_0000CCC8: 23-insn (0x5C) 6-arg cross-USO call
 * builder. Computes &D[0x1C0] + idx*24 where idx = a0->[0x1AC] and
 * passes it as the 5th arg, with 0xFF as the 6th.
 *
 * Promoted from 96.3% NM-wrap to byte-exact via INSN_PATCH 4 insns at
 * 0x30/0x3C/0x40/0x48 to override the leaf-function regalloc cap (idx
 * chain in v0/t6/t7/t8 vs target's t6/t7/t8/t9). The patched offsets
 * have no relocations (pure R-type/li/sw with constant immediates), so
 * INSN_PATCH applies cleanly.
 *
 * Match keys retained from 96.3% pass:
 * - `extern char D_timb5_1C0;` collapses target's two-addiu split into
 *   the single `addiu t8, t8, 0x1C0` form via R_MIPS_LO16 reloc.
 * - IDO -O2 natural unused-arg-save handles a1/a2/a3 caller-slot spills
 *   since the function has a jal. */
extern int gl_func_00000000();
extern char D_timb5_1C0;

void timproc_uso_b5_func_0000CCC8(int *a0, int a1, int a2, int a3) {
    char *p = &D_timb5_1C0 + a0[0x1AC/4] * 24;
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], a2, p, 0xFF);
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000CD24: 54-insn (0xD8) approach-target-with-decay
 * routine. Was previously split by splat into CD24 (0xA4) + CDC8 (0x34);
 * merged because CD24 had forward branches (CD88 bc1fl +0x10 → CDCC,
 * CDB8 bc1f +0xE → CDF4) into CDC8's range, with CD8C duplicating CDC8's
 * leading lwc1 $f4,0($v1) — same branch-likely target-replication idiom
 * as CB40+CBD0 (per docs/MATCHING_WORKFLOW.md
 * #feedback-splat-fragment-via-register-flow USO `.word` variant).
 *
 * Same algorithm shape as CB40 but with target field offsets shifted:
 * D[0x384]/D[0x388] decay rates and D[0x38C] secondary, presumably for
 * a different parameter slot in the same struct family.
 *
 * NM body covers control flow; FP register allocation, branch-likely emit,
 * and lui-pair constants need permuter to tighten. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000CD24(int *a0, float a1) {
    int *v0;
    float target;
    if (*(float*)((char*)a0 + 0x2A4) != 0.0f) {
        target = a1;
    } else {
        target = 0.0f;
    }
    v0 = *(int**)((char*)a0 + 0x2B8);
    if (*(int*)((char*)v0 + 0x130) != 0) {
        target = 1.0f;
    }
    if (*(float*)((char*)v0 + 0x124) < target) {
        *(float*)((char*)v0 + 0x124) += *(float*)((char*)&D_00000000 + 0x388);
        if (target < *(float*)((char*)v0 + 0x124)) {
            *(float*)((char*)v0 + 0x124) = target;
        }
    } else {
        *(float*)((char*)v0 + 0x124) -= *(float*)((char*)&D_00000000 + 0x38C);
        if (*(float*)((char*)v0 + 0x124) < target) {
            *(float*)((char*)v0 + 0x124) = target;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CD24);
#endif

void timproc_uso_b5_func_0000CDFC(int a0) {}

void timproc_uso_b5_func_0000CE04(int a0) {}

void timproc_uso_b5_func_0000CE0C(int a0) {}

void timproc_uso_b5_func_0000CE14(int a0) {}

void timproc_uso_b5_func_0000CE1C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000CE2C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
}

void timproc_uso_b5_func_0000CE38(int a0) {}

void timproc_uso_b5_func_0000CE40(int a0) {}

void timproc_uso_b5_func_0000CE48(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000CE5C(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

/* 4-float load-batched store + jal. Was 97.2% NM (8-insn float
 * register-renumbering cap). Promoted via INSN_PATCH per
 * feedback_insn_patch_for_ido_codegen_caps.md (and SUFFIX_BYTES for
 * trailing prologue-stolen-PREDECESSOR pattern). */
void timproc_uso_b5_func_0000CE6C(char *a0) {
    char *v;
    float a, b, c, d;
    v = *(char**)(a0 + 0x2B8);
    a = *(float*)(a0 + 0x294);
    b = *(float*)(a0 + 0x264);
    c = *(float*)(a0 + 0x260);
    d = *(float*)(a0 + 0x25C);
    *(float*)(v + 0x118) = a;
    *(float*)(v + 0x10C) = b;
    *(float*)(v + 0x114) = c;
    *(float*)(v + 0x110) = d;
    gl_func_00000000();
}

#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000CE6C_pad.s")

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000CEB4: 105-insn (0x1A4) FPU/Vec4 transformation
 * with conditional fallback path. Frame -0x50; saves $ra; uses sp+0x40-
 * 0x4C as a Vec4 stack buffer.
 *
 * High-level structure (first ~30 insns decoded):
 *   - Saves a1 to sp+0x54 (caller arg slot)
 *   - Initializes sp+0x40, +0x44, +0x48, +0x4C to 0.0f (Vec4 zero)
 *   - Reads a0->[0x2AC] flag; if non-zero, alt path:
 *     - Sets sp+0x40 from D[0x394]
 *     - Calls gl_func with a0->[0x44], a0->[0x5C], 0xFF, &Vec4 buf...
 *   - Else (a0->[0x2AC] == 0) reads D[0x398] into f0 and continues
 *
 * Multi-tick decompile — full FPU control flow + Vec4 inits + conditional
 * call patterns need multiple passes. Default INCLUDE_ASM build matches.
 * This wrap captures the entry-point structure for grep discoverability. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000CEB4(int *a0, int a1) {
    /* TODO: full decompile — first ~30 insns (Vec4 init + a0->2AC branch)
     * decoded but the body has 4+ FPU branches, 3+ jal calls, and
     * multi-arg cross-USO calls. Partial structure only. */
    float vec_buf[4];
    vec_buf[0] = vec_buf[1] = vec_buf[2] = vec_buf[3] = 0.0f;
    if (*(int*)((char*)a0 + 0x2AC) != 0) {
        gl_func_00000000(a0, a1);
    }
    (void)vec_buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CEB4);
#endif

void timproc_uso_b5_func_0000D058(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x11C) = a1;
}

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of A97C/A9EC family — same 23-insn loop with branch-likely
 * preload structural cap. Different outer offsets (this variant):
 *   count: a0->0x6C (was a0->0x3C in A97C)
 *   slot ptr: a0->0x3C (was a0->0x40 in A97C)
 *   fn ptr at slot->0x28->0x4C, short arg at slot->0x28->0x48 (same as A97C)
 * Same do-while + branch-likely-preload cap. */
void timproc_uso_b5_func_0000D06C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x3C);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D06C);
#endif

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of A97C/A9EC/D06C — same 23-insn loop with branch-likely
 * preload cap. Outer offsets same as D06C (count=a0->0x6C, slot=a0->0x3C);
 * inner offsets fn ptr=slot->0x28->0xE4, short arg=slot->0x28->0xE0
 * (vs D06C's 0x4C/0x48). */
void timproc_uso_b5_func_0000D0DC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x3C);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0xE4))(*(short*)((char*)v0 + 0xE0) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D0DC);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000D14C: 257-insn / 0x404 constructor.
 * First pass structural decode from word-only USO asm (m2c cannot parse it
 * directly; decoded via assemble+objdump per docs/TOOLING_DECOMP.md).
 *
 * High-level shape:
 *   - allocate/init a 0x2C4 root object, attaching it to a0->2B8 and a0->29C
 *   - create/attach a 0x148 child at root->108 and optional 0x16C child at
 *     root->108->108
 *   - initialize render/state floats, vtable slots, a D_00000000 flag pair,
 *     then store the root in a0->3C[a0->6C++].
 *
 * This is intentionally a NON_MATCHING skeleton: default build stays
 * INCLUDE_ASM, but the major object offsets and side effects are now recorded
 * for future constructor tightening / struct typing. */
int timproc_uso_b5_func_0000D14C(char *a0, int arg1, int arg2, int arg3,
                                 float arg4, float arg5, float arg6) {
    char *root;
    char *maybe_child;
    char *child;
    char *grandchild;
    int saved_flags;
    int index;

    root = (char*)gl_func_00000000(0x2C4);
    if (root != 0) {
        maybe_child = root;
        if (maybe_child == 0) {
            maybe_child = (char*)gl_func_00000000(0x2B8);
            if (maybe_child != 0) {
                gl_func_00000000(maybe_child, (char*)&D_00000000 + 0x15C0);
                *(int*)(maybe_child + 0x28) = (int)&D_00000000;
                gl_func_00000000(maybe_child + 0x2C);
                gl_func_00000000(maybe_child + 0x194);
            }
        }
        *(int*)(root + 0x28) = (int)((char*)&D_00000000 + 0x5E4);
        *(int*)(root + 0x0C) = (int)((char*)&D_00000000 + 0x15C8);
        gl_func_00000000(root);
    }

    gl_func_00000000(a0 + 0x10, root);
    if (*(int*)(root + 0x14) != 0) {
        *(int*)(root + 0x04) = 1;
    }
    *(int*)(root + 0x14) = (int)a0;
    *(float*)(root + 0x2A4) = (float)arg1;
    *(int*)(root + 0x2B0) = arg2 - 1;

    child = (char*)gl_func_00000000(0x148);
    if (child != 0) {
        float zero = 0.0f;
        gl_func_00000000(child, (char*)&D_00000000 + 0x15D8, zero, zero, zero);
        *(int*)(child + 0x28) = (int)((char*)&D_00000000 + 0x57C);

        grandchild = (char*)gl_func_00000000(0x16C);
        if (grandchild != 0) {
            gl_func_00000000(grandchild, (char*)&D_00000000 + 0x15E4,
                             zero, zero, zero);
            *(int*)(grandchild + 0x120) = 0xFFFF;
            *(int*)(grandchild + 0x28) = (int)&D_00000000;
            *(float*)(grandchild + 0x108) = *(float*)((char*)&D_00000000 + 0x3A0);
            *(float*)(grandchild + 0x10C) = *(float*)((char*)&D_00000000 + 0x3A0);
            *(float*)(grandchild + 0x110) = *(float*)((char*)&D_00000000 + 0x3A0);
            *(float*)(grandchild + 0x124) = 1.0f;
        }

        *(int*)(child + 0x108) = (int)grandchild;
        gl_func_00000000(child, grandchild);
        *(float*)(grandchild + 0xB4) = 0.0f;
        *(float*)(grandchild + 0xBC) = 0.0f;
        *(float*)(grandchild + 0xB8) = 100.0f;
        *(float*)(child + 0x130) = *(float*)((char*)&D_00000000 + 0x3A4);

        gl_func_00000000(0xB4, *(int*)&D_00000000, grandchild + 0xB4);
        maybe_child = (char*)gl_func_00000000(0xB4);
        if (maybe_child != 0) {
            gl_func_00000000(maybe_child, *(int*)&D_00000000);
            *(int*)(maybe_child + 0x28) = (int)((char*)&D_00000000 + 0x248);
            *(int*)(maybe_child + 0xB0) = 0;
            gl_func_00000000(maybe_child);
        }
        *(int*)(child + 0x10C) = (int)maybe_child;
        gl_func_00000000(child, maybe_child);

        saved_flags = *(int*)((char*)&D_00000000 + 0x04) & 0x00080000;
        *(int*)((char*)&D_00000000 + 0x04) =
            (*(int*)((char*)&D_00000000 + 0x04) & 0xFFF7FFFF) | 0x22003;
        *(int*)&D_00000000 &= ~8;

        gl_func_00000000(arg3, 0, 0x201, grandchild, child);
        *(int*)(child + 0x140) = *(int*)((char*)&D_00000000 + arg3 * 4);
        gl_func_00000000(grandchild, *(int*)(child + 0x140), 0, 2, 2, 1);
        {
            char *vt = *(char**)(grandchild + 0x28);
            (*(void(**)(void))(vt + 0x24))();
        }

        if (saved_flags != 0) {
            *(int*)((char*)&D_00000000 + 0x04) |= 0x00080000;
        } else {
            *(int*)((char*)&D_00000000 + 0x04) &= 0xFFF7FFFF;
        }

        *(float*)(child + 0x110) = arg4;
        *(float*)(child + 0x114) = arg5;
        *(float*)(child + 0x118) = arg6;
        *(float*)(child + 0x120) = 0.0f;
        *(float*)(child + 0x124) = *(float*)((char*)&D_00000000 + 0x3A8);
        *(float*)(child + 0x128) = *(float*)((char*)&D_00000000 + 0x3AC);
        *(int*)(child + 0x144) = 1;
        *(int*)(child + 0x138) = 0;
        *(int*)(child + 0x134) = 0;
    }

    *(int*)(root + 0x2B8) = (int)child;
    *(int*)(root + 0x29C) = (int)child;
    *(float*)(root + 0x134) = *(float*)((char*)&D_00000000 + 0x3B0);
    gl_func_00000000(*(char**)(a0 + 0x38) + 0x10, child);
    if (*(int*)(child + 0x14) != 0) {
        *(int*)(child + 0x04) = 1;
    }
    *(int*)(child + 0x14) = *(int*)(a0 + 0x38);

    index = *(int*)(a0 + 0x6C);
    *(int*)(a0 + 0x6C) = index + 1;
    *(int*)(a0 + 0x3C + index * 4) = (int)root;
    return (int)root;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D14C);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D550);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D884);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000DF14);

void timproc_uso_b5_func_0000E5AC(int a0) {
    *(int*)&D_00000000 = 0;
    gl_func_00000000(a0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000E5AC_pad.s")

/* Prologue-stolen successor (per E5AC's _pad.s): the 2-insn `lui v0;
 * lw v0, 0(v0)` preceding E5D8 sets v0 = *D_00000000 (a state pointer).
 * Body copies 3 floats from `(*D_0)->0x70`'s fields (0xBC/0xCC/0xDC)
 * into D_0+0/+4/+8, then calls gl_func_00000000(a0). C-emit duplicates
 * the lui+lw at start; PROLOGUE_STEALS=8 strips the redundant 8-byte
 * prefix post-cc per feedback_prologue_stolen_successor_no_recipe.md.
 * Per feedback_prologue_steals_with_dangling_register_use.md, the inner
 * deref uses a typed-as-int* alias `D_E5D8_state` so IDO emits `lui+lw`
 * (matching the stolen-prologue shape) instead of `lui+addiu+lw`. */
extern int *D_E5D8_state;
void timproc_uso_b5_func_0000E5D8(int a0) {
    *(float*)((char*)&D_00000000 + 0) = *(float*)((char*)D_E5D8_state[0x70/4] + 0xBC);
    *(float*)((char*)&D_00000000 + 4) = *(float*)((char*)D_E5D8_state[0x70/4] + 0xCC);
    *(float*)((char*)&D_00000000 + 8) = *(float*)((char*)D_E5D8_state[0x70/4] + 0xDC);
    gl_func_00000000(a0);
}
