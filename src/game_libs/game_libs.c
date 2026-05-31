#include "common.h"

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000000);

#ifdef NON_MATCHING
/* gl_func_000001CC: 79-insn alloc-if-null constructor + color-normalize.
 * Allocates a 0x13C-byte object if a0==NULL (and a 0x10C sub-object if
 * that's NULL too), wires several setup callees, then fills the object:
 *   - obj[0x28] = &D_0; obj[0xC] = &gl_ref_0000CAFC
 *   - color floats obj[0xC4..0xD0] = {250,235,100,0} / 255.0f
 *   - obj[0xD4..0xDC] = {0, 255, 130}; obj[0xE0] = a1 (saved param)
 *   - trailing setup call gl_func(obj, -78, -1, -51, 0)
 * Structural first pass — many cross-USO jal-0 calls + magic args;
 * exact match deferred to a later tightening tick. */
extern int gl_func_00000000();
extern char gl_ref_0000CAF4;
extern char gl_ref_0000CAFC;
int gl_func_000001CC(int *a0, int a1) {
    int *s0 = a0;
    if (a0 == 0) {
        s0 = (int*)gl_func_00000000(0x13C);
        if (s0 == 0) {
            return 0;
        }
    }
    if (s0 == 0) {
        int *p = (int*)gl_func_00000000(0x10C);
        if (p != 0) {
            gl_func_00000000(p, &gl_ref_0000CAF4);
            *(int*)((char*)p + 0x28) = (int)&D_00000000;
            gl_func_00000000((char*)p + 0x2C);
        }
    }
    *(int*)((char*)s0 + 0xC) = (int)&gl_ref_0000CAFC;
    gl_func_00000000((char*)s0 + 0x10C, 0x50000);
    gl_func_00000000((char*)s0 + 0x124, 0x50007);
    gl_func_00000000(s0, (char*)s0 + 0x124);
    *(float*)((char*)s0 + 0xC4) = 250.0f / 255.0f;
    *(float*)((char*)s0 + 0xC8) = 235.0f / 255.0f;
    *(float*)((char*)s0 + 0xCC) = 100.0f / 255.0f;
    *(float*)((char*)s0 + 0xD0) = 0.0f / 255.0f;
    *(int*)((char*)s0 + 0xD4) = 0;
    *(int*)((char*)s0 + 0xD8) = 255;
    *(int*)((char*)s0 + 0xDC) = 130;
    *(int*)((char*)s0 + 0xE0) = a1;
    gl_func_00000000(s0, -78, -1, -51, 0);
    return (int)s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000001CC);
#endif

extern int gl_func_00000000();
int gl_func_00000308(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

#ifdef NON_MATCHING
/* gl_func_00000338: 50-insn time/value formatter. Two divs (a1 / 60000,
 * remainder / 1000), each guarded by IDO -O2's standard div-by-zero +
 * INT_MIN-overflow trap insns (`teq zero, 0x7000` and `teq zero, 0x6000`).
 * Then calls a sprintf-like callee with format string at &D_8000_0xCB08
 * and args (a2 = quotient1, ?, ?).
 *
 * Decoded structure (semantics partially uncertain — the second use of
 * `subu` looks like ms - quotient_minutes, which doesn't cleanly map to
 * ms→MM:SS:hh; may be a different formula like a base/offset transform):
 *
 *   void f(char *out, unsigned a1) {
 *       unsigned mins = a1 / 60000;     // 0xEA60 = 60000
 *       unsigned rem = a1 - mins;       // not %, literal subtraction
 *       unsigned secs = rem / 1000;     // 0x3E8 = 1000
 *       unsigned ms_part = rem - secs * 10;  // some scaling
 *       sprintf(out + 0xE4, FORMAT_8000_CB08, mins, secs, ms_part);
 *   }
 *
 * Multi-tick decompile; this captures structural decode for future
 * pass to refine formula + match the format-arg passthrough. */
extern int gl_func_00000000();
void gl_func_00000338(char *a0, unsigned a1) {
    unsigned mins = a1 / 60000;
    unsigned rem = a1 - mins;
    unsigned secs = rem / 1000;
    unsigned ms_part = rem - secs * 10;
    gl_func_00000000(a0 + 0xE4, (char*)&D_00000000 + 0xCB08, mins, secs, ms_part);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000338);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000400);

extern int gl_func_00000000();
int gl_func_00000574(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0001CB30;

void gl_func_000005A4(char *a0, char a1, char a2, char a3) {
    gl_func_00000000(a0 + 0xE4, &gl_ref_0001CB30, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000005EC);

extern int gl_func_00000000();
int gl_func_00000760(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CB58;
int gl_func_00000790(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CB58, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000007BC);

/* 3-insn 2-field setter: a0[0x44]=a1, a0[0x5C]=a2. No frame, no jal. */
void game_libs_func_0000099C(int *a0, int a1, int a2) {
    a0[0x44/4] = a1;
    a0[0x5C/4] = a2;
}

/* 3-insn 2-field setter: a0[0x74]=a1, a0[0x8C]=a2. Sibling of 0x999C. */
void game_libs_func_000009A8(int *a0, int a1, int a2) {
    a0[0x74/4] = a1;
    a0[0x8C/4] = a2;
}

#ifdef NON_MATCHING
/* gl_func_000009B4: render-setup updater. 6 callbacks driving two sub-objects
 * (arg0->0xAC and arg0->0xB0). For each: cb(obj), then cb(obj, (int)((float)
 * arg0->0xA8 * scale), arg0+0x94, arg0->0xA4) where scale = *(float*)&D_00000000
 * (int->float via cvt.s.w, *scale, trunc.w.s, mfc1-passed), then cb(obj, fieldsum,
 * fieldsum, arg0+0xB4/0xBC). Fresh decode 2026-05-29 (m2c-confirmed), upgraded
 * from deferred-decode marker. 74.1% reg-blind, exact 54-insn count. Residuals:
 * frame size (target reserves ~0x20 unused stack, like gl_func_000628EC), FP-temp
 * regalloc swap (f4/f6), minor t-reg scheduling. Caps: arg0 struct + 6 cb prototypes
 * untyped (USO-reloc), scale-const not symbolized. NON_MATCHING. */
extern int gl_func_00000000();
void gl_func_000009B4(char *arg0) {
    char *a2;

    gl_func_00000000(*(int *)(arg0 + 0xAC));
    a2 = arg0 + 0x94;
    gl_func_00000000(*(int *)(arg0 + 0xAC),
                     (int)((float)*(int *)(arg0 + 0xA8) * *(float *)&D_00000000),
                     a2, *(int *)(arg0 + 0xA4));
    gl_func_00000000(*(int *)(arg0 + 0xAC), *(int *)(arg0 + 0x44),
                     *(int *)(arg0 + 0x5C), arg0 + 0xB4);
    gl_func_00000000(*(int *)(arg0 + 0xB0));
    gl_func_00000000(*(int *)(arg0 + 0xB0),
                     (int)((float)*(int *)(arg0 + 0xA8) * *(float *)&D_00000000),
                     a2, *(int *)(arg0 + 0xA4));
    gl_func_00000000(*(int *)(arg0 + 0xB0),
                     *(int *)(arg0 + 0x44) + *(int *)(arg0 + 0x74),
                     *(int *)(arg0 + 0x5C) + *(int *)(arg0 + 0x8C),
                     arg0 + 0xBC);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000009B4);
#endif

#ifdef NON_MATCHING
/* gl_func_00000A8C: 64-insn (0x100) nested-alloc + color-normalize
 * constructor. Full hand-decode 2026-05-28 (m2c can't parse the raw-.word
 * USO format). Same alloc-cascade family as gl_func_000001CC / func_0000FC28.
 *
 * Structure (verified from asm 0x0A8C-0x0B88):
 *   obj = a0;
 *   if (obj == 0) { obj = alloc(0xD4); if (!obj) return 0; }    // 212-byte
 *   sub = obj;
 *   if (sub == 0) { sub = alloc(0xC4); if (!sub) goto colors; } // 196-byte (defensive)
 *   init(sub, &gl_ref_0000CB84, sub);   // jal @0xADC
 *   sub->0x28 = &D_00000000;
 *   init2(sub + 0x2C);                  // jal @0xAF4
 * colors:
 *   obj->0x94 = 235.0f/255.0f;  obj->0x98 = 80.0f/255.0f;       // RGBA normalize
 *   obj->0x9C = 80.0f/255.0f;   obj->0xA0 = 0.0f/255.0f;
 *   obj->0xC  = &gl_ref_0000CB8C;       // type/vtable
 *   obj->0xA4 = 0; obj->0xA8 = 255;
 *   obj->0xAC = a1_saved; obj->0xB0 = a2_saved;
 *   gl_func(obj, 0x59, 2);              // jal @0xB64 (89, 2)
 *   obj->0xC4 = 0; obj->0xC8 = 1;
 *   return obj;
 *
 * The 0xCB84 / 0xCB8C data refs are %hi/%lo with sign-extended %lo (lui 1 +
 * addiu negative folds to 0x0000CB84). Reloc-bearing → objdiff-aware compare.
 *
 * 95.91% as of 2026-05-28 (fresh decode this session: 0% → 64% → 91.6% → 95.9%).
 * Four levers found:
 *  (1) `denom = 255.0f; x = 235.0f/denom;` FORCES a runtime div.s — the literal
 *      `235.0f/255.0f` lets IDO constant-fold it to lwc1-from-rodata-pool
 *      (the documented named-local-divisor lever, IDO_CODEGEN.md
 *      #feedback-ido-div-2-mul-fold-and-mtc1-load-delay-nops).
 *  (2) `if (alloc==0) goto ret;` to a shared epilogue instead of `return 0;`
 *      (which emits a separate `move v0,zero` block).
 *  (3) Home the a1/a2 PARAMS directly (no a1_saved/a2_saved locals) → 0x30→0x28
 *      frame.
 *  (4) The first init call is 2-arg `init(sub, &ref)`, NOT 3-arg `(sub,&ref,sub)`
 *      — sub is live across the call (used after for ->0x28 + the 2nd call) so it
 *      stays in $a2 and is homed; writing it as a 3rd arg forced an extra
 *      `move a2,a3` (+1 insn, $a3 vs $a2). This was the 91.6%→95.9% jump.
 *  Data refs use the `(char*)&D_00000000 + 0xCB84` ADDEND idiom (NOT a separate
 *  gl_ref_XXXX extern): the addend rides in the .o reloc so objdiff matches it
 *  against the raw-word expected baseline; an undefined gl_ref symbol resolves
 *  to 0 and does NOT match (undefined_syms_auto.txt is link-time-only).
 * RESIDUAL CAP (~4%, scheduling/stack-slot, not C-fixable): (a) `move s0,a0` is
 * scheduled into the bnez delay slot (mine) vs hoisted before `sw ra` (target);
 * (b) the `sub` spill homes to sp+0x20 (mine) vs sp+0x24 (target). Both are
 * IDO scheduler/stack-slot-order choices, deterministic + permuter-resistant.
 * Stays NM. */
extern int gl_func_00000000();
int gl_func_00000A8C(int *a0, int a1, int a2) {
    int *obj = a0;
    int *sub;
    float denom;

    if (obj == 0) {
        obj = (int*)gl_func_00000000(0xD4);
        if (obj == 0) goto ret;
    }
    sub = obj;
    if (sub == 0) {
        sub = (int*)gl_func_00000000(0xC4);
        if (sub == 0) goto colors;
    }
    gl_func_00000000(sub, (char*)&D_00000000 + 0xCB84);
    *(int*)((char*)sub + 0x28) = (int)&D_00000000;
    gl_func_00000000((char*)sub + 0x2C);
colors:
    denom = 255.0f;
    *(float*)((char*)obj + 0x94) = 235.0f / denom;
    *(float*)((char*)obj + 0x98) = 80.0f / denom;
    *(float*)((char*)obj + 0x9C) = 80.0f / denom;
    *(float*)((char*)obj + 0xA0) = 0.0f / denom;
    *(int*)((char*)obj + 0x0C) = (int)((char*)&D_00000000 + 0xCB8C);
    *(int*)((char*)obj + 0xA4) = 0;
    *(int*)((char*)obj + 0xA8) = 255;
    *(int*)((char*)obj + 0xAC) = a1;
    *(int*)((char*)obj + 0xB0) = a2;
    gl_func_00000000(obj, 0x59, 2);
    *(int*)((char*)obj + 0xC4) = 0;
    *(int*)((char*)obj + 0xC8) = 1;
ret:
    return (int)obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000A8C);
#endif

void game_libs_func_00000B8C(int a0) {}

/* game_libs_func_00000B94: ms->time formatter (a1 / 60000 = minutes, etc.).
 * Merged 2026-05-23: splat mis-split this at 0xBAC into game_libs_func_00000B94
 * (head: div a1,60000; v0<<4; multu v0,60000 — no prologue/jr) + gl_func_00000BAC
 * (body: mflo of B94's multu, prologue, sprintf-style calls, epilogue). The
 * multu(B94)/mflo(BAC) LO-register dependency proves they are one function;
 * IDO scheduled the division setup before the addiu sp prologue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00000B94);

/* gl_func_00000D5C - verified structural decode (0x118, 70 insns,
 * get-or-create constructor + child wiring).
 * Struct-typing reference: object = 316 (0x13C) bytes. s0->0xC (12)
 * descriptor/vtable ptr (&D); sub-object (separate alloc) ->0x28
 * (40) descriptor (&D); s0+0x10C (268) and s0+0x124 (292) = two
 * embedded child sub-objects init'd with packed ids 0x050001 /
 * 0x050007 then cross-wired; field block s0->0xC4/0xC8/0xCC
 * (196/200/204) f32 = a global default (loaded from &D + 0xC70),
 * s0->0xD0 (208) f32 = 0.0, s0->0xD4 (212)=0, s0->0xD8 (216)=255,
 * s0->0xDC (220)=130, s0->0xE0 (224)=a1. Final
 * gl_func_00000000(s0,-56,-1,-13) = a (mode,-1,-13) init.
 * Caps <80: get-or-create branch + ~8 gl_func_00000000 reloc calls +
 * &D descriptor relocs + FP const + packed-id args. INCLUDE_ASM
 * remains build path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void *gl_func_00000D5C(char *s0, int a1) {
    char *sub;
    float k;
    if (s0 == 0) {
        s0 = (char*)gl_func_00000000(316);
        if (s0 == 0) return 0;
    }
    sub = (char*)gl_func_00000000(0xCBC0);
    *(int*)(sub + 0x28) = (int)&D_00000000;
    gl_func_00000000(sub + 0x2C);
    *(int*)(s0 + 0xC) = (int)&D_00000000;
    gl_func_00000000(s0 + 268, 0x050001);
    gl_func_00000000(s0 + 292, 0x050007);
    gl_func_00000000(s0, s0 + 292, s0 + 268);
    k = *(float*)((char*)&D_00000000 + 0xC70);
    *(float*)(s0 + 0xC4) = k;
    *(float*)(s0 + 0xC8) = k;
    *(float*)(s0 + 0xCC) = k;
    *(float*)(s0 + 0xD0) = 0.0f;
    *(int*)(s0 + 0xD4) = 0;
    *(int*)(s0 + 0xD8) = 255;
    *(int*)(s0 + 0xDC) = 130;
    *(int*)(s0 + 0xE0) = a1;
    gl_func_00000000(s0, -56, -1, -13);
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000D5C);
#endif

extern int gl_func_00000000();
int gl_func_00000E74(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CBD8;
int gl_func_00000EA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CBD8, arg1);
}

#ifdef NON_MATCHING
/* gl_func_00000ED0: constructor. obj = a0 ?: alloc(212); a defensive second
 * obj-or-alloc (node); init(node, &D+0xCBE0); node->0x28 = &D; init(node+0x2C);
 * then field inits (vtable ptr &D+0xCBE8, three 0xC74-floats, flags). Returns
 * obj. Fresh decode 2026-05-29: bare INCLUDE_ASM -> 93.51%, logic-complete and
 * SIZE-EXACT (51/51 insns). Residual is a clean register renumber — IDO puts
 * obj in $v1 / node in $a2 where the target uses $a2 / $a3 (spill slots shift
 * sp+0x18/0x1C vs target sp+0x1C/0x20); decl-order swap didn't flip it.
 * Allocator-internal reg-renumber cap; logic + structure are exact. */
int gl_func_00000ED0(int a0, int a1) {
    int obj;
    int node;
    float v;
    obj = a0;
    if (obj == 0) {
        obj = gl_func_00000000(212);
        if (obj == 0) {
            goto ret;
        }
    }
    node = obj;
    if (node == 0) {
        node = gl_func_00000000(212);
        if (node == 0) {
            goto ret;
        }
    }
    gl_func_00000000(node, (char*)&D_00000000 + 0xCBE0);
    *(int*)(node + 0x28) = (int)&D_00000000;
    gl_func_00000000(node + 0x2C);
    v = *(float*)((char*)&D_00000000 + 0xC74);
    *(int*)(obj + 0xC) = (int)((char*)&D_00000000 + 0xCBE8);
    *(int*)(obj + 0x74) = 0;
    *(int*)(obj + 0x78) = 255;
    *(float*)(obj + 0x64) = v;
    *(float*)(obj + 0x68) = v;
    *(float*)(obj + 0x6C) = v;
    *(float*)(obj + 0x70) = 0.0f;
    *(int*)(obj + 0xA0) = 0;
    *(int*)(obj + 0xB0) = a1;
ret:
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000ED0);
#endif

void game_libs_func_00000F9C(int a0) {
}

extern int gl_func_00000000();
extern char gl_ref_0000CBF8;
int gl_func_00000FA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xB4, &gl_ref_0000CBF8, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000FD0);

extern int gl_func_00000000();
int gl_func_00001114(char *a0) {
    return gl_func_00000000(a0 + 0x10C);
}

/* gl_func_00001134: 3-way value-formatter dispatcher — picks one of
 * 3 format strings by a1's magnitude and calls the cross-USO
 * printf-like gl_func_00000000. Per-arm arg counts/buffers differ. */
extern int gl_data_00000000;
void gl_func_00001134(char *a0, int a1) {
    if (a1 < 10) {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC10, a1);
    } else if (a1 < 100) {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC18);
    } else {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC1C);
    }
}

#ifdef NON_MATCHING
/* gl_func_000011A4: 54-insn alloc-or-given + init constructor.
 * Current fuzzy: 37.31% (216-byte function). Cap class: dead-inner-alloc
 * emission — target has a 4-insn dead `alloc(0x10C)` block at offset
 * 0x2C-0x38 that's provably unreachable (s0 always non-zero post-merge)
 * but emitted by the original C. Tried docs/PATTERNS.md feedback-
 * alloc-or-passthrough-cascade-includes-dead-arms recipe (sub = self;
 * if (sub == 0) alloc): REGRESSED to 61 insns (+7 over target) because
 * the named `sub` local forced an extra $s reg + spill pair. The
 * dead-arm in target uses ONE $s reg (s0) for both 'self' and
 * 'sub'-like role — unreachable from 2-var C without inline-asm.
 * 2026-05-17 tested goto-end form (alloc-fail jumps to shared epilogue
 * `return self;`) — REGRESSED (the long body's regalloc uses $s-regs
 * for self/intermediate values; merging via goto changes the live-range
 * across the 11-store body and IDO picks a totally different $s
 * allocation). The simple `return 0` early-exit form is actually the
 * local maximum for this function class.
 * 2026-05-27 reconfirmed: alloc-or-null sibling family's goto-out
 * lever (which landed gl_func_0001FD98 100% and improved 36E74/3D16C/
 * 37AF0/35B1C +10-34pp) does NOT apply here — the dead-inner-alloc
 * + long-body $s-reg promotion makes this function a different cap
 * class from the simpler alloc-or-null siblings.
 * Stays NM-wrap; default INCLUDE_ASM exact. */
extern int gl_data_00000000;
int* gl_func_000011A4(int *a0) {
    int *self = a0;
    if (self == 0) {
        self = (int*)gl_func_00000000(0x140);
        if (self == 0) return 0;
    }
    gl_func_00000000(self, (char*)&gl_data_00000000 + 0xCC20, self);
    *(int*)((char*)self + 0x28) = (int)&D_00000000;
    gl_func_00000000((char*)self + 0x2C);
    *(int*)((char*)self + 0x28) = (int)&D_00000000;
    *(int*)((char*)self + 0xC) = (int)((char*)&gl_data_00000000 + 0xCC28);
    gl_func_00000000((char*)self + 0x110,
        *(int*)((char*)&gl_data_00000000 + 0x54) | 0x001E0000);
    *(int*)((char*)self + 0xD4) = 0;
    *(int*)((char*)self + 0xD8) = 0xFF;
    *(int*)((char*)self + 0x10C) = 0;
    *(float*)((char*)self + 0xC4) = 0.0f;
    *(float*)((char*)self + 0xC8) = 0.0f;
    *(float*)((char*)self + 0xCC) = 0.0f;
    *(float*)((char*)self + 0xD0) = *(float*)((char*)&D_00000000 + 0xC78);
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000011A4);
#endif

void gl_func_0000127C(char *a0) {
    gl_func_00000000(a0 + 0x110);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000127C_pad.s")

#ifdef NON_MATCHING
/* gl_func_000012B4: 40-insn helper (0xA0, frame 0x68, saves s0/s1/s2/ra).
 *
 * Caller-set float convention ($f4, $f6, $f0): same family as
 * gl_func_00010650 / game_uso_func_00010650 — IDO C-level cannot receive
 * floats in $f4/$f6/$f0 (intra-USO non-O32 call convention,
 * docs/IDO_CODEGEN.md#feedback-ido-no-gcc-register-asm). Real C body
 * sketched below for documentation; INCLUDE_ASM is the build path.
 *
 * Decoded structure:
 *   self = a0; product_int = (int)(f4 * f6);
 *   Quad4 buf = {0,0,0,0};                 // 4× swc1 f0 (=0.0f caller-set)
 *   gl_func_00000000(&D_NNN, product_int, &buf, 0);     // 4-arg call
 *   s2 = self + 0x110;                                 // subobject pointer
 *   gl_func_00000000(s2);                              // unary call
 *   for (i = self->[0x10C] - 1; i >= 0; i--) {
 *       byte_off = i * 4;                              // sll 2
 *       p = (char*)self->[0x44] + byte_off;
 *       q = self->[0x5C] - byte_off;
 *       gl_func_00000000(s2, p, q, 3);                 // a3=3 literal
 *   }
 *
 * Structural-decode note 2026-05-18: was 1-line "Multi-pass decode pending"
 * doc-marker (the bail pattern per feedback_doc_marker_is_bail.md).
 * Replaced with substantive structural decode + caller-set-float-cap class
 * attribution. INCLUDE_ASM path holds. CAP: $f4/$f6/$f0 caller-set float
 * calling convention is unreachable from IDO C; promotion via INSN_PATCH
 * REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — stays NM.
 */
void gl_func_000012B4(int *self) {
    /* Real C below documents the body shape. Cannot byte-match due to
     * intra-USO float-in-fN callee convention; INCLUDE_ASM #else branch is
     * the build path. */
    extern int gl_func_00000000();
    extern int D_00000000;
    extern float gl_float_f4, gl_float_f6;  /* placeholder caller-set floats */
    int product_int = (int)(gl_float_f4 * gl_float_f6);
    int buf[4] = {0, 0, 0, 0};
    int *s2;
    int i;
    gl_func_00000000(&D_00000000, product_int, &buf, 0);
    s2 = (int*)((char*)self + 0x110);
    gl_func_00000000(s2);
    for (i = self[0x10C / 4] - 1; i >= 0; i--) {
        int byte_off = i * 4;
        int *p = (int*)((char*)self[0x44 / 4] + byte_off);
        int q = self[0x5C / 4] - byte_off;
        gl_func_00000000(s2, p, q, 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000012B4);
#endif

void game_libs_func_00001354(int *a0, int a1) {
    a0[0x10C/4] = a1;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000135C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000015FC);

void gl_func_00001798(char *a0) {
    gl_func_00000000(a0 + 0x138);
    gl_func_00000000(a0 + 0x150);
    gl_func_00000000(a0 + 0x180);
    gl_func_00000000(a0 + 0x168);
}

/* 3-insn 2-field setter: a0[0x44]=a1, a0[0x5C]=a2. */
void game_libs_func_000017E0(int *a0, int a1, int a2) {
    a0[0x44/4] = a1;
    a0[0x5C/4] = a2;
}

/* 2-insn 1-field setter: a0[0xCC]=a1 (in jr-ra delay slot). */
void game_libs_func_000017EC(int *a0, int a1) {
    a0[0xCC/4] = a1;
}

/* 3-insn 2-field setter: a0[0x130]=a1, a0[0x134]=a2. */
void game_libs_func_000017F4(int *a0, int a1, int a2) {
    a0[0x130/4] = a1;
    a0[0x134/4] = a2;
}

/* 6-insn 4-arg setter: a0[0x74]=a1, a0[0x8C]=a2, a0[0xA4]=a3, a0[0xBC]=a4
 * (a4 from caller-arg-save sp+0x10). */
void game_libs_func_00001800(int *a0, int a1, int a2, int a3, int a4) {
    a0[0x74/4] = a1;
    a0[0x8C/4] = a2;
    a0[0xA4/4] = a3;
    a0[0xBC/4] = a4;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00001818);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001820);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001C54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000237C);

extern int gl_func_00000000();
void gl_func_000024C4(char *a0) {
    gl_func_00000000(a0 + 0x1F4);
    gl_func_00000000(a0 + 0x20C);
    gl_func_00000000(a0 + 0x224);
    gl_func_00000000(a0 + 0x23C);
    gl_func_00000000(a0 + 0x254);
    gl_func_00000000(a0 + 0x26C);
    gl_func_00000000(a0 + 0x284);
    gl_func_00000000(a0 + 0x29C);
    gl_func_00000000(a0 + 0x2B4);
    gl_func_00000000(a0 + 0x2CC);
    gl_func_00000000(a0 + 0x2E4);
}

/* 3-insn 2-int setter: a0[0x1C4]=a1, a0[0x1C8]=a2. */
void game_libs_func_00002540(int *a0, int a1, int a2) {
    a0[0x1C4/4] = a1;
    a0[0x1C8/4] = a2;
}

/* 5-insn 2-float setter (mtc1 in body — caller passes int in $a1/$a2). */
void game_libs_func_0000254C(int *a0, float a1, float a2) {
    *(float*)((char*)a0 + 0x1CC) = a1;
    *(float*)((char*)a0 + 0x1D0) = a2;
}

/* 8-insn 3-float setter (3rd float via stack round-trip per K&R ABI). */
void game_libs_func_00002560(int *a0, float a1, float a2, float a3) {
    *(float*)((char*)a0 + 0x1E4) = a1;
    *(float*)((char*)a0 + 0x1E8) = a2;
    *(float*)((char*)a0 + 0x1EC) = a3;
}

/* 10-insn 4-float setter (3rd+4th via stack round-trip; 4th from caller sp+0x10). */
void game_libs_func_00002580(int *a0, float a1, float a2, float a3, float a4) {
    *(float*)((char*)a0 + 0x1D4) = a1;
    *(float*)((char*)a0 + 0x1D8) = a2;
    *(float*)((char*)a0 + 0x1DC) = a3;
    *(float*)((char*)a0 + 0x1E0) = a4;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000025A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002840);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000029F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002B94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003138);

/* game_libs_func_00003298 (0x18, no prologue/jr): stolen FP-const prologue of
 * the successor gl_func_000032B0 — six lui/mtc1 insns materializing f4=100.0f,
 * f6=255.0f, f8=235.0f. gl_func_000032B0 reads these uninitialized before its
 * own `addiu sp` (e.g. `mul.s f22, f4, f6` at +0x1C). Same chained-FP-stolen-
 * prologue pattern as mgrproc_uso_func_00002EF0 -> _00002F10; leave INCLUDE_ASM
 * (the bytes belong logically to 32B0's prologue). 32B0 itself = 77-insn FP
 * color/material setup (8-iter loop + placeholder call + caller-set/stolen FP) =
 * multi-tick FP-pipeline cap. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00003298);

#ifdef NON_MATCHING
/* gl_func_000032B0: 77-insn FP color/material setup. Decoded algorithm:
 * normalize 4 color channels (using the stolen-prologue consts from
 * game_libs_func_00003298 above: f4=100, f6=255, f8=235) and apply them to 8
 * sub-objects pointed to by a0->0x2C..0x48, calling a placeholder per sub, then
 * zero/init a block of a0 fields. Stays NON_MATCHING (no episode): three caps
 * stack here -- (1) prologue-stolen (f4/f6/f8 live in the split-off head, so the
 * C re-materializes them = extra insns), (2) the per-sub call is caller-set-float
 * (mfc1 $a3 + swc1 stack, both 1.0f) which IDO C can't emit, (3) raw-.word
 * game_libs reloc depression on the placeholder call. Reference decode only. */
extern int func_00000000();
void gl_func_000032B0(int *a0) {
    float r = 100.0f / 255.0f;   /* f22 = f4/f6 */
    float g = 235.0f / 255.0f;   /* f24 = f8/255 */
    float b = 250.0f / 255.0f;   /* f26 */
    float al = 0.0f / 255.0f;    /* f28 */
    int i;
    for (i = 0; i < 8; i++) {
        int *sub = *(int**)((char*)a0 + 0x2C + i * 4);
        *(int*)((char*)sub + 0x98) = 0;
        func_00000000(sub, 0xA0, 0x5A, 1.0f, 1.0f);
        *(float*)((char*)sub + 0x64) = r;
        *(float*)((char*)sub + 0x68) = g;
        *(float*)((char*)sub + 0x6C) = b;
        *(float*)((char*)sub + 0x70) = al;
        *(int*)((char*)sub + 0x94) = 0;
    }
    *(int*)((char*)a0 + 0x5C) = 0;
    *(int*)((char*)a0 + 0x9C) = 0;
    *(int*)((char*)a0 + 0x8C) = 0xFF;
    *(int*)((char*)a0 + 0x90) = 0xFF;
    *(int*)((char*)a0 + 0x94) = 0xFF;
    *(int*)((char*)a0 + 0x98) = 0xFF;
    *(int*)((char*)a0 + 0x60) = 0;
    *(int*)((char*)a0 + 0xA0) = 0;
    *(int*)((char*)a0 + 0x64) = 0;
    *(int*)((char*)a0 + 0xA4) = 0;
    *(int*)((char*)a0 + 0x68) = 0;
    *(int*)((char*)a0 + 0xA8) = 0;
    *(int*)((char*)a0 + 0x84) = 0;
    *(int*)((char*)a0 + 0x7C) = 0;
    *(int*)((char*)a0 + 0x80) = 0;
    *(int*)((char*)a0 + 0x88) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000032B0);
#endif

extern int gl_func_00000000();

void gl_func_000033E4(char *a0) {
    gl_func_00000000(a0 + 0xF0);
    gl_func_00000000(a0 + 0x108);
    gl_func_00000000(a0 + 0x120);
    gl_func_00000000(a0 + 0x150);
    gl_func_00000000(a0 + 0x138);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003430);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000038F4);

/* gl_func_00003B1C - verified structural decode (0xF0, 60 insns,
 * free-slot allocator + initializer).
 * Struct-typing reference: a0 = a table of slot-pointer entries
 * (stride 4); each entry's slot = entry->0x2C. Slot fields: 0x94
 * (148) s32 state (0 = free, 5 = claimed), 0x9C (156) s32 = 32 or
 * 0 (by a3), 0x78 (120) s32 = 255, 0x80 (128) s32 = 0, 0x84 (132)
 * s32 = -18, 0x98 (152) s32 = a1 (caller handle), 0xA0 (160) s32 =
 * 0, 0xA8 (168) f32 = 0.0, 0xB0 (176) = a0->0x54 (source field
 * copied in), slot+0xB4 (180) = a sub-struct passed to a second
 * reloc init. gl_func_00000000(slot,161,a2+90,1.0f) = primary
 * init (arg2 a2+90, f32 1.0). Caps <80: scan loop + FP-const
 * (mfc1/swc1 1.0) + 2x reloc + large sentinel limit constant.
 * INCLUDE_ASM remains build path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void *gl_func_00003B1C(char *a0, int a1, int a2, int a3) {
    char *v1 = a0;
    int off = 0;
    char *slot;
    do {
        off += 4;
        slot = *(char**)(v1 + 0x2C);
        if (*(int*)(slot + 0x94) == 0) {
            *(int*)(slot + 0x94) = 5;
            *(int*)(slot + 0x9C) = a3 ? 32 : 0;
            gl_func_00000000(slot, 161, a2 + 90, 1.0f);
            *(int*)(slot + 0x78) = 255;
            *(int*)(slot + 0xA0) = 0;
            *(int*)(slot + 0x98) = a1;
            *(int*)(slot + 0x80) = 0;
            *(int*)(slot + 0x84) = -18;
            *(float*)(slot + 0xA8) = 0.0f;
            *(int*)(slot + 0xB0) = *(int*)(a0 + 0x54);
            gl_func_00000000(slot + 0xB4);  /* additional args truncated in decode */
            return slot;
        }
        v1 += 4;
    } while (off != 0x10000);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003B1C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003C0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003DB8);

#ifdef NON_MATCHING
/* Ring-buffer (4-slot, index a0->0x7C) record append + advance. Writes
 * a1/a2/0/0/200 into the current slot's fields (0x5C/0x6C/0x9C/0x8C/0xBC),
 * then sets 0xAC=160 and clamps the slot's 0xBC to prev->0xBC+16 when the
 * delta < 15; advances 0x7C/0x80 ring indices (&3), bumps 0x88 by 16 and
 * 0x84 (cap 4). First 26 insns (the 5 indexed stores + delta setup) match
 * exactly; the prev/cur/160/delta tail caps on register allocation
 * (reload/temp slot picks). Logic exact. */
void game_libs_func_00003F08(int *a0, int a1, int a2) {
    int idx;
    int *cur;
    int *prev;
    int prevbc;
    int next;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x5C) = a1;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x6C) = a2;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x9C) = 0;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x8C) = 0;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0xBC) = 200;
    idx = a0[0x7C / 4];
    cur = (int *)((char *)a0 + idx * 4);
    prev = (int *)((char *)a0 + ((idx - 1) & 3) * 4);
    prevbc = prev[0xBC / 4];
    /* NB: the cur[0xAC]=160 store is a SHARED TAIL of both arms (cur is
     * recomputed to the same a0+idx*4 in the <15 arm), so it lives once after
     * the if — collapsing it into both arms emits a redundant `beq zero,zero`
     * (63 vs 60 insns). Target still beats this by 1 idiom: it folds the else
     * store into a `beql` delay slot (90.7% residual = that beql + the prev/cur
     * pointer register cascade $a3 vs $v1). */
    if (cur[0xBC / 4] - prevbc < 15) {
        cur[0xBC / 4] = prevbc + 16;
        cur = (int *)((char *)a0 + a0[0x7C / 4] * 4);
    }
    cur[0xAC / 4] = 160;
    next = (a0[0x7C / 4] + 1) & 3;
    a0[0x88 / 4] += 16;
    if (a0[0x80 / 4] == next) {
        a0[0x80 / 4] = (a0[0x80 / 4] + 1) & 3;
    }
    a0[0x7C / 4] = next;
    if (a0[0x84 / 4] < 4) {
        a0[0x84 / 4] = a0[0x84 / 4] + 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00003F08);
#endif

#ifdef NON_MATCHING
/* Clamp 4 consecutive fields (0x8C/0x90/0x94/0x98) to a minimum of 112,
 * returns a0. Logic exact; caps on register allocation — target copies
 * a0→v0 early and uses v0 as the base for fields 2-4 (a0 only for field 1),
 * and re-materializes `li 112` before each field; IDO instead parks the
 * constant 112 in v0 and emits the a0→v0 return-move at the end. Branch-
 * likely (beqzl) skip-store with the next field's load in the delay slot.
 *
 * 2026-05-23 RE-VERIFIED cap (4 levers all coalesce to the 24-insn form):
 * root cause is the delay-slot-fill scheduling class — target is 25 insns
 * (early `move v0,a0` + nop in jr-ra delay + v0-base for fields 2-4); IDO's
 * natural emit is 24 (a0-base throughout + late move-in-delay-slot). The
 * v0=a0 copy is free so IDO always picks the shorter form. See
 * docs/IDO_CODEGEN.md#feedback-ido-target-larger-preemptive-set-nop-delay
 * (return-the-pointer-arg leaf cascade instance). Permanent NM, no episode. */
int *game_libs_func_00003FF8(int *a0) {
    if (a0[0x8C / 4] < 112) a0[0x8C / 4] = 112;
    if (a0[0x90 / 4] < 112) a0[0x90 / 4] = 112;
    if (a0[0x94 / 4] < 112) a0[0x94 / 4] = 112;
    if (a0[0x98 / 4] < 112) a0[0x98 / 4] = 112;
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00003FF8);
#endif

extern int gl_ref_00013C70();
int gl_func_0000405C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013C70(a0 + 0x10);
}

extern int gl_ref_00013C70();
extern int gl_ref_00013CAC();
int gl_func_0000408C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013CAC(a0 + 0x10);
}

extern int gl_ref_00013C70();
extern int gl_ref_00013CE8();
void gl_func_000040BC(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    gl_ref_00013CE8(a0 + 0x10);
}

/* Body is 4 insns (addiu t6, a0, 4; li t7, 1; jr ra; sllv v0, t7, t6),
 * but symbol coverage includes 2 leading nops at 0x40EC/0x40F0 (artifact
 * of split-fragments.py including inter-function alignment pad in the
 * split-off symbol). Previously matched via PREFIX_BYTES (8-byte leading-
 * nop injection). PREFIX_BYTES REMOVED 2026-05-27 (was missed by
 * 2026-05-23 sweep) per feedback_no_instruction_forcing_matches_policy
 * — leading-nop injection on a non-USO-header function is instruction-
 * appending match-faking. Function stays NM-wrapped (INCLUDE_ASM build
 * path covers the 2 leading nops + body bytes); honest unmatched. */
#ifdef NON_MATCHING
int game_libs_func_000040EC(int a0) {
    return 1 << (a0 + 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000040EC);
#endif

extern int gl_func_00000000();
void gl_func_00004104(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004140(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004198(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void gl_func_000041D4(Vec3 *dst) {
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

#ifdef NON_MATCHING
/* gl_func_00004244: 2479-insn (0x26BC) constructor / setup orchestrator.
 * Stack frame 0x748 (1864 bytes — many local accumulators + working buffers).
 * Single function (grep -c 03E00008 = 1).
 *
 * Entry decode (insns 1-12 @ 0x4244-0x4274):
 *   sp -= 0x748                    ; massive frame
 *   save s0..s2, ra, f20, f22 (FPU regs preserved)
 *   s0 = a0                        ; saved arg
 *   if (a0 == 0) {                 ; alloc-or-passthrough ternary
 *       a0 = alloc(0x488);         ; 1160-byte primary buffer
 *       if (a0 == 0) goto epilogue ; alloc fail early-exit (jump +0x99A insns)
 *       s0 = a0;
 *   }
 *
 * Body (~2470 insns): main initialization. Sets a chain of D[+CF80] fields
 * to floats (1.0 via lui $at,0x3F80; mtc1), zero-inits 4-byte and 8-byte
 * regions, copies bytes in/out of accumulator regions at sp+0x718..738
 * (looks like a 12-float matrix init), then dispatches multiple cross-USO
 * calls (jal placeholders).
 *
 * Multi-tick decompile in scope; this captures structural decode + entry
 * stage for future passes to extend. Constructor pattern per
 * project_1080_strategy.md: not a skip reason — partial C IS the struct-
 * typing work for D+CF80 (a global state struct) and the a0 +0x488-byte
 * primary instance.
 *
 * Decoded entry stub for grep/discoverability; default build INCLUDE_ASM
 * matches via the original asm. */
extern int gl_func_00000000();
void gl_func_00004244(int *a0) {
    int *p = a0;
    if (p == 0) {
        p = (int*)gl_func_00000000(0x488);
        if (p == 0) return;
    }
    /* TODO: ~2470 insns of init + dispatch math + cross-USO calls */
    (void)p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00004244);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006900);

extern int gl_func_00000000();
int gl_func_00006A8C(char *a0, int a1) {
    *(int*)(a0 + 0x4F0) = a1;
    return gl_func_00000000(a0);
}

/* gl_func_00006AAC - verified structural decode (0xD4, 53 insns,
 * object reset/init). SIBLING of gl_func_00006B80 (same large object
 * + same global G = *(&D)); this is the clear/reset entry.
 * Struct-typing reference (extends the gl_func_00006B80 object map):
 * 0x2C (44) / 0x30 (48) s32 = 0; 0x4DC (1244) / 0x4E0 (1248) s32 = 0
 * (the "2/3" pair gl_func_00006B80 sets - here zeroed); 0x4E4 (1252)
 * s32 timer = 120 or 0 by bit 18 of 0x4F0; 0x4E8 (1256) s32 = 20;
 * 0x4F0 (1264) s32 mode/flags (bit 18 gate, also copied to G->0x8C);
 * 0x4F4 (1268) s32 = 0x1FFFF mask; 0x4FC (1276) / 0x500 (1280) /
 * 0x508 (1288) / 0x510 (1296) s32 = 0; 0x534 (1332) / 0x538 (1336)
 * f32 = 1.0; 0x540 (1344) s32 = 255. Global G = *(&D): G->0x78 (120)
 * = 1, G->0x7C (124) = 0, G->0x8C (140) = a0->0x4F0; plus 3 standalone
 * global f32 zeroed. Caps <80: FP-const (1.0/0.0) loads + bgez bit
 * test + gl_func_00000000 reloc + multiple &D global relocs. INCLUDE_ASM
 * remains the build path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
extern float gl_d_x, gl_d_y, gl_d_z;  /* placeholder 3 global floats zeroed by this fn */
void gl_func_00006AAC(int *a0) {
    int *G = *(int**)&D_00000000;
    *(int*)((char*)a0 + 0x2C) = 0;
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x4DC) = 0;
    *(int*)((char*)a0 + 0x4E0) = 0;
    *(int*)((char*)a0 + 0x4FC) = 0;
    *(int*)((char*)a0 + 0x4F4) = 0x1FFFF;
    G[0x78 / 4] = 1;
    gl_func_00000000(&D_00000000, 0);
    *(int*)((char*)a0 + 0x4E8) = 20;
    *(int*)((char*)a0 + 0x4E4) = (*(int*)((char*)a0 + 0x4F0) & (1 << 18)) ? 0 : 120;
    G[0x8C / 4] = *(int*)((char*)a0 + 0x4F0);
    *(int*)((char*)a0 + 0x540) = 255;
    *(float*)((char*)a0 + 0x534) = 1.0f;
    *(float*)((char*)a0 + 0x538) = 1.0f;
    gl_d_x = 0.0f;
    gl_d_y = 0.0f;
    gl_d_z = 0.0f;
    *(int*)((char*)a0 + 0x500) = 0;
    *(int*)((char*)a0 + 0x508) = 0;
    *(int*)((char*)a0 + 0x510) = 0;
    G[0x7C / 4] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006AAC);
#endif

/* gl_func_00006B80 - verified structural decode (0xB8, 46 insns,
 * object initializer).
 *   void gl_func_00006B80(int *a0, int a1, int a2) {
 *       a0->0x4F8 = a2;
 *       a0->0x4E0 = 3;
 *       a0->0x4DC = 2;
 *       gl_func_00000000(&D_00000000, 0);
 *       a0->0x4EC = 0;
 *       a0->0x518 = 0;
 *       a0->0x4E4 = a1;
 *       a0->0x54C = 120.0f;                       // 0x42F00000
 *       if (g_mode == 2)                          // *(&D)->0x34
 *           a0->0x54C = 60.0f;                    // 0x42700000
 *       a0->0x550 = 0.0f;
 *       a0->0x544 = 255;
 *       a0->0x554 = 150.0f;                       // 0x43160000
 *       v = a0->0x28;
 *       (*(fn)v->0x7C)((s16)v->0x78 + (int)a0);   // obj-0x28 dispatch
 *   }
 * Struct-typing reference: a0 = a large object. Fields: 0x4DC (1244)
 * s32 = 2, 0x4E0 (1248) s32 = 3, 0x4E4 (1252) s32 = a1, 0x4EC (1260)
 * s32 = 0, 0x4F8 (1272) s32 = a2, 0x518 (1304) s32 = 0, 0x544 (1348)
 * s32 = 255, 0x54C (1356) f32 timer/duration = 120.0 (60.0 when the
 * global mode *(&D)->0x34 == 2), 0x550 (1360) f32 = 0.0, 0x554
 * (1364) f32 = 150.0; a0->0x28 (40) vtable ptr with fn @0x7C (124)
 * + s16 base-adjust @0x78 (120) - the engine-wide obj-0x28 dispatch
 * idiom, 0x7C/0x78 variant. Caps <80: FP-const loads (lui+mtc1) x4
 * + bne global-mode branch + gl_func_00000000 reloc call + &D reloc
 * + vtable jalr. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void gl_func_00006B80(char *a0, int a1, int a2) {
    char *v;
    *(int *)(a0 + 0x4F8) = a2;
    *(int *)(a0 + 0x4E0) = 3;
    *(int *)(a0 + 0x4DC) = 2;
    gl_func_00000000(&D_00000000, 0);
    *(int *)(a0 + 0x4EC) = 0;
    *(int *)(a0 + 0x518) = 0;
    *(int *)(a0 + 0x4E4) = a1;
    *(float *)(a0 + 0x54C) = 120.0f;
    if (*(int *)((char *)&D_00000000 + 0x34) == 2) {
        *(float *)(a0 + 0x54C) = 60.0f;
    }
    *(float *)(a0 + 0x550) = 0.0f;
    *(int *)(a0 + 0x544) = 255;
    *(float *)(a0 + 0x554) = 150.0f;
    v = *(char **)(a0 + 0x28);
    {
        void (*fn)(char *) = *(void (**)(char *))(v + 0x7C);
        fn((char *)((int)(short)*(short *)(v + 0x78) + (int)a0));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006B80);
#endif

/* gl_func_00006C38: 41-insn struct-init. Sets a0->{0x4F8,0x4E0,0x4DC} from
 * args; calls gl_func_0(&D, 0, a2, orig_a0) (4 args, a3 = saved orig_a0);
 * post-call: writes a0->{0x4EC=0, 0x518=0, 0x4E4=a1, 0x54C=120.0f, 0x550=0.0f,
 * 0x544=0xFF, 0x554=150.0f}; if (D[0x34]==2) overwrite 0x54C with 60.0f.
 *
 * Closed with INSN_PATCH for an IDO post-call scheduling cap:
 *   - Mine:   lui+mtc1 (120.0f); sw 0, 4EC; sw 0, 518; lw t8 (a1 reload);
 *             lui t9 (D base); swc1 f4; sw t8 (a1 store); lw t9 (D[0x34])
 *   - Target: lw t8 (a1) FIRST; lui+mtc1 (120.0f); lui t9 (D base);
 *             sw 0, 4EC; sw 0, 518; sw t8; swc1 f4; lw t9 (D[0x34])
 * Target hoists the a1 reload before the FP setup, then fills load-delay
 * slots with the zero stores. */
#ifdef NON_MATCHING
void gl_func_00006C38(int *a0, int a1, int a2) {
    a0[0x4F8/4] = a2;
    a0[0x4E0/4] = 3;
    a0[0x4DC/4] = 2;
    gl_func_00000000(&D_00000000, 0, a2, a0);
    a0[0x4EC/4] = 0;
    a0[0x518/4] = 0;
    a0[0x4E4/4] = a1;
    *(float*)((char*)a0 + 0x54C) = 120.0f;
    if (*(int*)((char*)&D_00000000 + 0x34) == 2) {
        *(float*)((char*)a0 + 0x54C) = 60.0f;
    }
    *(float*)((char*)a0 + 0x550) = 0.0f;
    a0[0x544/4] = 0xFF;
    *(float*)((char*)a0 + 0x554) = 150.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006C38);
#endif

/* gl_func_00006CDC - verified structural decode (0xEC, ~55 insns +
 * 2 bundled stubs). NEAR-SIBLING of gl_func_00006B80 (same large-
 * object initializer family); variant differences noted.
 * BUNDLED: jr-count 3 - after the main body splat appended TWO tiny
 * leaf stubs `void f(int a0){ *(int*)sp = a0; }` (jr ra; sw a0,0(sp))
 * - separate 2-insn functions, splittable via split-fragments later.
 * NM-wrap body below documents ONLY the main body; trailing stubs
 * stay inside the INCLUDE_ASM build path.
 * Struct-typing reference (extends gl_func_00006B80 object map):
 * 0x4DC (1244)=2, 0x4E0 (1248)=3, 0x4E4 (1252)=a1, 0x4EC (1260)=0,
 * 0x4F8 (1272)=a2, 0x518 (1304) s32 = 60 (this variant; 0 in 6B80),
 * 0x540 (1344)=255, 0x54C (1356) f32 = 120.0/60.0 by global mode
 * *(&D)->0x34, 0x550 (1360) f32=0.0, 0x554 (1364) f32=150.0; a0->
 * 0x28 (40) vtable -> {fn@0x84 (132), s16@0x80 (128)} (obj-0x28
 * dispatch, 0x84/0x80 variant). Caps <80: FP-const loads + global-
 * mode branches (==2 / ==3) + gl_func_00000000 reloc + vtable jalr
 * + 2 bundled tail stubs. INCLUDE_ASM remains build path
 * (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void gl_func_00006CDC(char *a0, int a1, int a2) {
    char *v;
    *(int*)(a0 + 0x4F8) = a2;
    *(int*)(a0 + 0x4E0) = 3;
    *(int*)(a0 + 0x4DC) = 2;
    gl_func_00000000(&D_00000000, 0);
    *(int*)(a0 + 0x4EC) = 0;
    *(int*)(a0 + 0x518) = 60;
    *(int*)(a0 + 0x4E4) = a1;
    *(float*)(a0 + 0x54C) = 120.0f;
    if (*(int*)((char*)&D_00000000 + 0x34) == 2) *(float*)(a0 + 0x54C) = 60.0f;
    if (*(int*)((char*)&D_00000000 + 0x34) == 3) gl_func_00000000(a0);
    *(int*)(a0 + 0x540) = 255;
    *(float*)(a0 + 0x550) = 0.0f;
    *(float*)(a0 + 0x554) = 150.0f;
    v = *(char**)(a0 + 0x28);
    {
        void (*fn)(char *) = *(void (**)(char*))(v + 0x84);
        fn((char*)((int)(short)*(short*)(v + 0x80) + (int)a0));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006CDC);
#endif

void game_libs_func_00006DB8(int a0) {}

void game_libs_func_00006DC0(int a0) {}

extern int gl_func_00000000();
extern int *gl_ref_00000138;

void gl_func_00006DC8(int a0) {
    int *p;
    gl_func_00000000(a0, 0x1E0, 0);
    p = *(int **)((char *)&D_00000000 + 0x138);
    p[45] = 0;
}

/* Sibling of gl_func_00006EE0 (matched 2026-05-08): identical 32-insn
 * template, only 4 constants differ (0xF0/4/6/6 → 0x168/3/5/5). */
void gl_func_00006DF8(int *a0) {
    int *p;
    gl_func_00000000(a0, 0x168, 3);
    *(int*)((char*)a0 + 0x544) = 0;
    *(float*)((char*)a0 + 0x554) = 120.0f;
    p = *(int**)((char*)&D_00000000 + 0x138);
    *(int*)((char*)p + 0xB4) = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(5, 0, 0);
    gl_func_00000000(&D_00000000, 5, 0, 0);
}

void gl_func_00006E78(int a0_passthrough) {
    int *p;
    gl_func_00000000(a0_passthrough, 0x140, 2);
    p = *(int**)((char*)&D_00000000 + 0x138);
    p[0xB4/4] = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(5, 0, 0);
    gl_func_00000000(&D_00000000, 5, 3, 0);
}

/* Init function: zero-initialize a0 fields, store 120.0f at +0x554, clear
 * a child obj field, then 3 calls. Composite of int-reader-shape prologue
 * + custom init logic. */
void gl_func_00006EE0(int *a0) {
    int *p;
    gl_func_00000000(a0, 0xF0, 4);
    *(int*)((char*)a0 + 0x544) = 0;
    *(float*)((char*)a0 + 0x554) = 120.0f;
    p = *(int**)((char*)&D_00000000 + 0x138);
    *(int*)((char*)p + 0xB4) = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(6, 0, 0);
    gl_func_00000000(&D_00000000, 6, 0, 0);
}

void gl_func_00006F60(int a0) {
    int *p;
    gl_func_00000000(a0, 0x1E0, 5);
    p = *(int **)((char *)&D_00000000 + 0x138);
    p[45] = 0;
}

/* Sibling of gl_func_00006EE0 (just-landed): same 32-insn 4-call init
 * shape but with different field offsets and 1-arg jal at end. */
void gl_func_00006F90(int *a0) {
    int *p;
    gl_func_00000000(a0, 0xF0, 4);
    *(int*)((char*)a0 + 0x544) = 0;
    *(float*)((char*)a0 + 0x554) = 120.0f;
    p = *(int**)((char*)&D_00000000 + 0x138);
    *(int*)((char*)p + 0xB4) = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(6, 0, 0);
    gl_func_00000000(&D_00000000, 6, 0, 0);
}

/* Sibling of gl_func_00006E78 (matched 2026-05-08): same 26-insn 4-call
 * dispatch shape with different constants (0xF0/6/6/1 vs 0x140/2/5/3).
 * Same named-local+inline-second-deref recipe from
 * docs/IDO_CODEGEN.md#feedback-ido-v1-base-materialization-via-second-inline-deref. */
void gl_func_00007010(int a0_passthrough) {
    int *p;
    gl_func_00000000(a0_passthrough, 0xF0, 6);
    p = *(int**)((char*)&D_00000000 + 0x138);
    p[0xB4/4] = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(6, 0, 0);
    gl_func_00000000(&D_00000000, 6, 1, 0);
}

/* 4-function bundle 0x7078..0x709F split via split-fragments.py 2026-05-08:
 * 2x save-arg sentinels + 2x return-1 stubs. */
void game_libs_func_00007078(int a0) {}
void game_libs_func_00007080(int a0) {}
int  game_libs_func_00007088(int a0) { return 1; }
int  game_libs_func_00007094(int a0) { return 1; }

/* gl_func_000070A0: 9-insn 1-call wrapper.
 *
 * F1 @ 0x70A0-0x70C0: gl_func_00000000(a0, -1, 0). The following
 * 0x70C4..0x70F8 empty stubs are standalone split symbols. */
extern int gl_func_00000000();
void gl_func_000070A0(int a0) {
    gl_func_00000000(a0, -1, 0);
}

void game_libs_func_000070C4(int a0) {}

void game_libs_func_000070CC(int a0) {}

void game_libs_func_000070D4(int a0) {}

void game_libs_func_000070DC(int a0) {}

void game_libs_func_000070E4(int a0) {}

/* Empty K&R one-arg function: IDO keeps the unused a0 save in the
 * jr-ra delay slot (`sw a0, 0(sp)`). */
void game_libs_func_000070EC(a0) int a0; {}

void game_libs_func_000070F4(int a0) {}

#ifdef NON_MATCHING
/* gl_func_000070FC: 0x248 = 146 insns. Sibling of gl_func_000070A0.
 * Body proper is 138 insns at 0x70FC..0x7320; the 4 trailing 2-insn
 * `jr ra; sw a0, 0(sp)` alt-entry stubs at offsets 0x228/0x230/0x238/0x240
 * are now tracked as separate symbols (after the 2026-05-23 policy change).
 *
 * The historical SUFFIX_BYTES recipe (absorbing 4 stubs × 2 insns = 8
 * words) was REMOVED 2026-05-23 as instruction-byte match-faking. The
 * `split-fragments.py` warning below also stale — splitting is now the
 * correct path (the alt-entry stubs are separate symbols, not absorbed).
 *
 * ENTRY DECODE (insns 1-15 @ 0x70FC-0x7140):
 *   void f(struct *a0) {
 *       if (a0->field_510 != 0) return;        // bnel-likely early exit
 *       struct *next = a0->field_528;
 *       if (next == 0) return;
 *       int v = func_call_1(next);
 *       if (v == 0) return;
 *       func_call_2(D[0x138], 0);
 *       func_call_3(5, ...);                    // body continues 130+ insns
 *
 * Multi-pass: this iteration decoded ~10% of body; current fuzzy 31% NM
 * via INCLUDE_ASM path. */
extern int gl_func_00000000();
void gl_func_000070FC(int *a0) {
    int *next;
    int v;
    int mode;
    int sub_state;
    if (*(int*)((char*)a0 + 0x510) != 0) return;
    next = *(int**)((char*)a0 + 0x528);
    if (next == 0) return;
    v = gl_func_00000000(next);
    if (v == 0) return;
    /* @ 0x712C-0x7148 (decoded 2026-05-07):
     * 3 cross-USO setup calls before the main switch:
     *   call(D[0x138], 0)  // setup 1, a1=0
     *   call(5, 0)         // setup 2, a0=5 a1=0
     *   call(0, 0)         // setup 3, a0=0 a1=0 (or zeroed via or a2,0,0)
     */
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(5, 0);
    gl_func_00000000(0, 0);

    /* @ 0x714C-0x71B8 (decoded 2026-05-07): MODE-SWITCH on D[0x34].
     *   if (D[0x34] == 5) goto case_5;
     *   if (D[0x34] == 4) goto case_4;
     *   if (D[0x34] != 6) goto default_branch;
     *   case_6: a1 = 5; t8 = D[0x7C];
     *           if (t8 != 1) {
     *               a1 = 5; a2 = 1;          // not-1: pass (5, 1, 1)
     *               call(5, 1, 1);
     *           } else {
     *               a1 = 5; a2 = 2;          // is-1: pass (5, 1, 2)
     *               call(5, 1, 2);
     *           }
     *           goto common_after; (b +0x5C, target ~0x7320)
     *
     * The 4/5 cases (TODO @ 0x71B0+) follow a similar shape: load D[0x34]/etc,
     * dispatch a parameterized call(a1, a2, a3), then b common_after. */
    mode = *(int*)((char*)&D_00000000 + 0x34);
    if (mode == 6) {
        sub_state = *(int*)((char*)&D_00000000 + 0x7C);
        if (sub_state != 1) {
            gl_func_00000000(5, 1, 1);
        } else {
            gl_func_00000000(5, 1, 2);
        }
        goto common_after;
    }
    /* TODO @ 0x71B0-0x7320 (~85 insns): mode==4 / mode==5 / default arms +
     * common_after merge block. (4 trailing 2-insn alt-entry stubs at
     * 0x228..0x240 are now separate symbols, not absorbed — see header.) */
    if (mode == 5) {
        /* TODO arm body */
    } else if (mode == 4) {
        /* TODO arm body */
    } else {
        /* TODO default branch */
    }
common_after:
    /* TODO common merge block + epilogue */
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070FC);
#endif

void game_libs_func_00007324(int a0) {}

void game_libs_func_0000732C(int a0) {}

void game_libs_func_00007334(int a0) {
}

void game_libs_func_0000733C(int a0) {}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007344);

/* Empty one-arg stub; IDO keeps the caller-slot spill in the return delay. */
void game_libs_func_000076C8(int a0) {
}

void game_libs_func_000076D0(int a0) {}

void game_libs_func_000076D8(int a0) {}

/* Empty one-arg stub; IDO keeps the caller-slot spill in the return delay. */
void game_libs_func_000076E0(int a0) {
}

/* Empty one-arg stub; sibling of game_libs_func_000076E0. */
void game_libs_func_000076E8(int a0) {
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000076F0);

#ifdef NON_MATCHING
/* gl_func_00007FF4: 222-insn (0x378) game_libs subsystem dispatcher.
 * Frame 0x90, saves ra+s0 at sp+0x24/0x20.
 *
 * Entry structure (decoded 2026-05-05, first 28 insns):
 *
 *   s0 = a0;                         // save struct ptr to s-reg (long-lived)
 *   t6 = a0->[0x4F0];                // load flags/state field
 *   t7 = t6 << 7;                    // shift bit 24 to sign position
 *   if (t7 < 0) {                    // bgez +0x17 → bit 24 is set, skip 23 insns
 *       // bit-set arm (~23 insns, 0x800C-0x8068):
 *       //   t0 = s0->[0x30];        // sub-obj ptr
 *       //   mtc1 $zero, $f0         // f0 = 0.0
 *       //   lui+addiu &D            // a1 = &D + N
 *       //   a3 = 0xFF
 *       //   addiu a2, sp, 0x58      // local Quad4 buf
 *       //   swc1 $f0, 0x58/0x5C/0x60/0x64(sp)  // 4 zero floats
 *       //   jal gl_func(&D, ..., quad4, 0xFF)
 *       //   t8 = 0x10001            // bit-flag tag stored to sp+0x10
 *       //   ... continues with second jal, more sub-arg setup ...
 *   }
 *   // bit-clear arm (fall-through, target of bgez):
 *   //   ... TBD: ~190 insns of subsystem update / FPU math ...
 *   epi: lw ra, ...; lw s0, ...; addiu sp, 0x90; jr ra
 *
 * First-pass NM stub — captures only the entry guard structure for grep
 * discoverability. Multi-pass decomp expected (this is comparable size to
 * 1080's larger spine functions). Default build INCLUDE_ASM matches; this
 * doc provides reference for the next agent. */
extern int gl_func_00000000();
void gl_func_00007FF4(int *a0) {
    int flags;
    flags = a0[0x4F0 / 4];
    if ((flags & 0x01000000) != 0) {
        /* bit-24 arm: alloc Quad4-of-zeros, dispatch first jal — TBD */
        (void)a0[0x30 / 4];
        (void)gl_func_00000000;
    }
    /* bit-24-clear arm (~190 insns, FPU math + subsystem update) — TBD */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007FF4);
#endif

extern int gl_func_00000000();
void gl_func_0000836C(int a0, int *a1) {
    int v = *a1;
    if (v == 9) {
        gl_func_00000000(a0, a1);
    }
    gl_func_00000000(a0, a1);
}

extern int gl_func_00000000();
int gl_func_000083AC(char *a0) {
    return gl_func_00000000(a0 + 0x50);
}

#ifdef NON_MATCHING
/* gl_func_000083CC: 79-insn 5-call dispatcher + 2 trailing prologue-stolen
 * words for gl_func_00008510 (the next function). Reads global state at
 * D_00000000+0x134, calls gl_func_00000000 5 times with state-derived args,
 * mutates state flags between calls.
 *
 * Structural decode (2026-05-04 partial):
 *   state = D[0x134]                 ; global state pointer
 *   t6 = state->0x108                ; sub-pointer
 *   a3 = state->0xC4                 ; sub-pointer
 *   t7 = t6->0x70                    ; saved at sp+0x44
 *   v0 = a3->0x800                   ; passed as 5th arg in 1st call
 *   a2 = state->0x80                 ; passed as 3rd arg in 1st call
 *   gl_func(state, 1, state->0x80, state->0xC4, a3->0x800);  /\* CALL 1 *\/
 *
 *   t9 = state->0x108                ; reload (state may have changed)
 *   s0->0x520 = t9                   ; spill to caller obj
 *   t9->0x18 &= ~8                   ; clear flag bit 3
 *   v1 = s0->0x520                   ; reload
 *   v1->0x18 &= ~4                   ; clear flag bit 2 — at &v1[0x18+0x18]
 *   gl_func(state, 0x70, t6->0x70);  /\* CALL 2 *\/
 *
 *   s0->0x51C = result_of_call2
 *   state->0x108 = result_of_call3   ; call3 first
 *   gl_func(0x80);                   /\* CALL 3 *\/
 *   if (call3_result != 0) {
 *       gl_func(call3_result, 1);    /\* CALL 4 *\/
 *   }
 *   gl_func(0, call3_result, state->0xC4, s0->0x51C, t7, call1_result);
 *                                    /\* CALL 5 — 6 args *\/
 *
 * NEXT-FUNCTION PROLOGUE-STEALS: trailing 2 words at 0x8508-0x850C
 * (`lui v1, 0; lw v1, 0x134(v1)`) belong to gl_func_00008510 logically.
 * To match gl_func_00008510 exact, will need
 * `build/src/game_libs/game_libs.c.o: PROLOGUE_STEALS := gl_func_00008510=8`.
 *
 * NEXT PASS: tighten the call-arg signatures, identify what callbacks
 * gl_func_00000000 resolves to at runtime (likely "spawn entity" /
 * "register handler" / "register" sequence given 5-call init pattern). */
extern int gl_func_00000000();
void gl_func_000083CC(int *a0) {
    int *state = *(int**)((char*)&D_00000000 + 0x134);
    int *t6 = *(int**)((char*)state + 0x108);
    int *a3 = *(int**)((char*)state + 0xC4);
    int t7 = *(int*)((char*)t6 + 0x70);
    int v0_call1 = gl_func_00000000(state, 1,
                                    *(int*)((char*)state + 0x80),
                                    a3,
                                    *(int*)((char*)a3 + 0x800));
    int *t9 = *(int**)((char*)state + 0x108);
    *(int**)((char*)a0 + 0x520) = t9;
    *(int*)((char*)t9 + 0x18) &= ~8;
    {
        int *v1 = *(int**)((char*)a0 + 0x520);
        *(int*)((char*)v1 + 0x18 + 0x18) = *(int*)((char*)v1 + 0x18) & ~4;
    }
    {
        int v0_call2 = gl_func_00000000(state, 0x70, t7);
        *(int*)((char*)a0 + 0x51C) = v0_call2;
    }
    {
        int v0_call3 = gl_func_00000000(0x80);
        *(int*)((char*)state + 0x108) = v0_call3;
        if (v0_call3 != 0) {
            gl_func_00000000(v0_call3, 1);
        }
        gl_func_00000000(0, v0_call3,
                         *(int*)((char*)state + 0xC4),
                         *(int*)((char*)a0 + 0x51C),
                         t7, v0_call1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000083CC);
#endif


/* gl_func_00008510: 42-insn dispatcher. ORPHAN-MERGED 2026-05-30: the 8-byte
 * stolen prologue (`lui v1,0; lw v1,0x134(v1)` = load `state = D[0x134]`),
 * formerly the separate orphan symbol game_libs_func_00008508 at 0x8508, is now
 * the first 2 words of this function's .s (entry moved 0x8510 -> 0x8508, size
 * 0xA0 -> 0xA8). This is the LEGITIMATE form of the previously-banned
 * PROLOGUE_STEALS=8 (removed 2026-05-23): the bytes belong to this function, so
 * the boundary is corrected rather than the match faked. The C below already
 * emits the state load.
 *
 * RESIDUAL CAP (blocks byte-exact): the merged target keeps `state` in $v1 (the
 * donated register) and reuses $v0 as scratch for the state->0xC4/0xCC reloads;
 * IDO -O2 puts our named `state` local in $v0 (highest-priority pseudo -> lowest
 * reg) and the reloads in $t-regs, giving a $v0/$v1 + cascade register-renumber
 * delta (~14/42 insns). Same class as the documented permuter register-rename
 * caps; not C-reachable without the regalloc dump. Stays NM until then.
 *
 * Structure:
 *   state = D[0x134]                    (predecessor-loaded into v1)
 *   p     = state->0xC4->0x800          (saved at sp+0x20)
 *   if (arg0->0x528->0x8->0x8 != 0) {
 *       p2 = state->0xCC->0x800
 *       gl_func(p2, p2->0x34)           (call 1)
 *       t = arg0->0x528->0x8            (refetched)
 *       gl_func(p2, t->0x8, t->0x4)     (call 2)
 *   }
 *   gl_func(p, p->0x34)                 (call 3)
 *   gl_func(p, D[0x168], D[0x164], &D + 0x170)  (call 4)
 *   gl_func(arg0)                       (call 5)
 *
 * History: once promoted via PROLOGUE_STEALS=8 (banned 2026-05-23 as match-
 * faking), rolled back to NM, now orphan-MERGED (the correct boundary fix). */
#ifdef NON_MATCHING
void gl_func_00008510(int *arg0) {
    char *state = *(char**)((char*)&D_00000000 + 0x134);
    char *p = *(char**)(*(char**)((char*)state + 0xC4) + 0x800);
    if (*(int**)((char*)*(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8) + 0x8) != 0) {
        char *p2 = *(char**)(*(char**)((char*)state + 0xCC) + 0x800);
        gl_func_00000000(p2, *(int*)((char*)p2 + 0x34));
        {
            int *t = *(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8);
            gl_func_00000000(p2, *(int*)((char*)t + 0x8), *(int*)((char*)t + 0x4));
        }
    }
    gl_func_00000000(p, *(int*)(p + 0x34));
    gl_func_00000000(p,
        *(int*)((char*)&D_00000000 + 0x168),
        *(int*)((char*)&D_00000000 + 0x164),
        (char*)&D_00000000 + 0x170);
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008510);
#endif

#ifdef NON_MATCHING
void gl_func_000085B0(int *arg0, int arg1) {
    char *state;
    char *p;

    gl_func_00000000(arg0);
    state = *(char**)((char*)&D_00000000 + 0x134);
    p = *(char**)(*(char**)(state + 0xC4) + 0x800);
    if (*(int**)((char*)*(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8) + 0x8) != 0) {
        char *p2 = *(char**)(*(char**)(state + 0xCC) + 0x800);
        gl_func_00000000(p2, *(int*)(p2 + 0x34));
        {
            int *t = *(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8);
            gl_func_00000000(p2, *(int*)((char*)t + 0x8), *(int*)((char*)t + 0x4));
        }
    }
    gl_func_00000000(p, 0);
    gl_func_00000000(p,
        *(int*)((char*)&D_00000000 + 0x168),
        *(int*)((char*)&D_00000000 + 0x170));
    gl_func_00000000(arg0);
    *(int*)((char*)arg0 + 0x4F4) = arg1 & 0xFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000085B0);
#endif

/* Hidden-register dispatch stub. The real ABI has the dispatcher pointer in
 * $v0 and addend in $v1 while still spilling caller $a0. C emits the same
 * shape with ordinary args; Makefile INSN_PATCH rewrites a1/a2 to v0/v1. */
#ifdef NON_MATCHING
int gl_func_00008674(int unused, int *hidden_v0, int hidden_v1) {
    volatile int *spill = &unused;
    (void)spill;
    return ((int (*)(int))hidden_v0[0x64/4])(*(s16*)((char*)hidden_v0 + 0x60) + hidden_v1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008674);
#endif

/* game_libs_func_000086A0: 31-insn FPU-only updater on two adjacent floats
 * at a0+0x550 (f550) and a0+0x54C (f54C).
 *
 * Pseudocode:
 *   f550 = *(float*)(a0 + 0x550);
 *   if (f550 < 4.0f) {
 *     f550 = (float)((double)f550 + *(double*)(&D + 0xE58));  // double step
 *     *(float*)(a0 + 0x550) = f550;
 *     f550 = *(float*)(a0 + 0x550);  // reload (IDO emit quirk)
 *   }
 *   f54C = *(float*)(a0 + 0x54C);
 *   *(float*)(a0 + 0x54C) = f54C - f550;
 *   f54C = *(float*)(a0 + 0x54C);  // reload
 *   if (f54C < 58.0f) {
 *     *(float*)(a0 + 0x54C) = f54C + f550;
 *     *(float*)(a0 + 0x550) = -(f550 / 4.0f);
 *   }
 *
 * NON_MATCHING (2 diffs): FP-temp-register swap in the double add — built does
 * ldc1->f4 (Dconst) / cvt.d.s->f6 (d550); target wants ldc1->f6 / cvt.d.s->f4.
 * IDO schedules the memory load (ldc1) first regardless of C operand order
 * (verified: operand swap is no-op, explicit-var ordering cascades 26 diffs).
 * Which f-reg holds load vs convert is IDO's FP allocator choice, not
 * C-reachable. Was INSN_PATCH'd (2 words, removed 2026-05-23). */
void game_libs_func_000086A0(char *a0) {
    float four = 4.0f;
    float f550 = *(float*)(a0 + 0x550);

    if (f550 < four) {
        double t;
        *(float*)(a0 + 0x550) = (float)(*(double*)((char*)&D_00000000 + 0xE58) + (t = (double)f550));
        f550 = *(float*)(a0 + 0x550);
    }

    *(float*)(a0 + 0x54C) = *(float*)(a0 + 0x54C) - f550;
    if (*(float*)(a0 + 0x54C) < 58.0f) {
        *(float*)(a0 + 0x54C) = *(float*)(a0 + 0x54C) + f550;
        *(float*)(a0 + 0x550) = -(f550 / four);
    }
}

/* gl_func_0000871C: 54-insn (0xD8) FPU updater + conditional indirect-call.
 *   if (a0->f550 < 4.0f) a0->f550 = (float)((double)a0->f550 + D[0xE60]);
 *   a0->f54C += a0->f550;
 *   if (a0->f554 < a0->f54C) {
 *     if (2.0f < a0->f550) {
 *       v = a0->[0x28]; short off = (s16)v->[0x130];
 *       ((fn*)v->[0x134])(off + (int)a0);
 *     }
 *     a0->f54C -= a0->f550;
 *     a0->f550 = -(a0->f550 / 4.0f);
 *   }
 * CAP: C-emit's $f6/$f8 reg-swap on the double-add stays NM ($f4-pinning
 * via named `four = 4.0f` plus inline D-deref with literal +0xE60 offset
 * gets 50/54 byte-identical; INSN_PATCH REMOVED 2026-05-23 per
 * feedback_no_instruction_forcing_matches_policy). */
#ifdef NON_MATCHING
void gl_func_0000871C(int *a0) {
    float four = 4.0f;
    float f550 = *(float*)((char*)a0 + 0x550);
    if (f550 < four) {
        double t;
        *(float*)((char*)a0 + 0x550) =
            (float)(*(double*)((char*)&D_00000000 + 0xE60) + (t = (double)f550));
        f550 = *(float*)((char*)a0 + 0x550);
    }
    *(float*)((char*)a0 + 0x54C) = *(float*)((char*)a0 + 0x54C) + f550;
    if (*(float*)((char*)a0 + 0x554) < *(float*)((char*)a0 + 0x54C)) {
        if (2.0f < f550) {
            int *v = (int*)a0[0x28/4];
            ((void(*)(int))v[0x134/4])(
                *(short*)((char*)v + 0x130) + (int)a0);
            f550 = *(float*)((char*)a0 + 0x550);
        }
        *(float*)((char*)a0 + 0x54C) =
            *(float*)((char*)a0 + 0x54C) - f550;
        *(float*)((char*)a0 + 0x550) = -(f550 / four);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000871C);
#endif

extern int gl_ref_00018770();
extern int gl_ref_000187AC();
int gl_func_000087F4(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_000187AC(a0 + 0x10);
}

extern int gl_ref_00018770();
int gl_func_00008824(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018770(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018804();
int gl_func_00008854(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018804(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018840();
int gl_func_00008884(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018840(a0 + 0x10);
}

/* Constructor pattern: alloc 64 bytes, init two fields, link into orig->field_40
 * list. 36 insns / 0x90 at -O2; 3 cross-USO jal calls, branch-likely on field
 * presence test.
 *
 * Flow (decoded from asm 2026-05-07, sibling of 0x8944/0x949C cluster):
 *   ptr = alloc(0x40);            // jal#1 with li a0, 0x40
 *   if (ptr) {
 *       init(ptr);                // jal#2 with a0=ptr
 *       ptr->field_28 = &D_00000000;
 *       ptr->field_3C = 0;
 *   }
 *   // following block runs unconditionally (alloc-fail path corrupts pointers
 *   // but original code does this — typical 90s "alloc never fails" pattern):
 *   existing = orig->field_40;
 *   if (existing) {
 *       link(ptr + 0x10, existing);   // jal#3 with a0=ptr+0x10, a1=existing
 *       if (existing->field_14 != 0) {
 *           existing->field_4 = 1;     // beql delay-likely emit pattern
 *       }
 *       existing->field_14 = ptr;
 *   }
 *   return ptr;
 *
 * (Old recipe: "INSN_PATCH for the 3 jal targets (all encoded as 0x0C000000
 * placeholders, runtime-resolved by USO loader); recipe at
 * docs/POST_CC_RECIPES.md". docs/POST_CC_RECIPES.md is DEPRECATED and
 * INSN_PATCH REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy.) Beql for
 * `if (existing->field_14 != 0)` followed by `existing->field_14 = ptr`
 * relies on the duplicate-store IDO emit pattern; the C body above triggers
 * it (write same value in both branches → IDO speculates via delay-likely).
 *
 * 2026-05-08 grind: tried to break the cap via frame-size lever.
 *   Built emits sp -= 0x20 (32 bytes), target sp -= 0x28 (40 bytes).
 *   v1) `char frame_pad[8]` — IDO optimized away, frame stayed 0x20.
 *   v2) `volatile char frame_pad[8]` (no access) — also elided.
 *   v3) `char frame_pad[16]` — also elided.
 *   v4) `volatile int frame_pad; frame_pad = 0;` — frame grew to 0x28
 *       BUT the added `sw zero, 28(sp)` insn doesn't match target → no
 *       net fuzzy% gain.
 * Confirms: bare-array frame-pad trick (works for 1DDC's 184-byte gap)
 * does NOT work here for the 8-byte gap. Possibly because: (a) IDO's
 * spill allocator already has 32 bytes of "slack" with the existing 4
 * spill slots, so an 8-16 byte unused array fits without growing; OR
 * (b) IDO's frame-rounding heuristic only kicks in for larger arrays.
 * 2026-05-08 follow-up: fixed GlConstructed padding so field_28/field_3C
 * compile at the target offsets, and split `ret` from `ptr` to grow the
 * C-body frame to 0x28 without an extra store. Remaining cap is the
 * ptr-in-a2 vs target ptr-in-v1 allocation plus a beqzl-vs-beqz layout in the
 * existing-link branch. Objdiff C-body score: 88.83%.
 *
 * 2026-05-08 (later): tried the sibling-port test with the matched
 * titproc_uso_func_00002980 / mgrproc_uso_func_00003358 / arcproc_uso
 * _func_00002334 verbatim C body (`if (p == 0) return 0; init;`).
 * Result: fuzzy DROPPED 89.31% → 77.83%. Same C body that lands
 * byte-exact in titproc/mgrproc/arcproc fails here because the file-
 * context (game_libs.c is large, ~1500 functions) perturbs IDO's
 * register allocator differently. Both the if-branch direction (target
 * uses beq early-exit, mine emits bne+goto-init) and frame size
 * (target -0x28 vs mine -0x20) diverge under game_libs.c's allocator
 * state, despite identical C source. The sibling-port test recipe
 * (docs/MATCHING_WORKFLOW.md#feedback-port-matched-sibling-c-before-
 * trusting-frame-regalloc-cap-claim) has a SCALE LIMIT — it only works
 * across files of similar size+complexity. Reverted.
 *
 * 2026-05-08 Codex pass: tried `register struct GlConstructed *ret asm("$3")`
 * to force the desired v1 return carrier. IDO ignored the hard-register hint
 * for this local: build/non_matching emitted byte-identical code to the
 * baseline (ptr still lives in a2, same beqzl early-exit). Reverted.
 *
 * 2026-05-11 Codex pass: was promoted with default-build INSN_PATCH.
 * INSN_PATCH REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to NM-wrap.
 * C-only emit caps at the a2/v1 allocator split + one-block schedule shift
 * + 3 jal-target relocs; NATURAL CEILING, stays NM. */
struct GlConstructed {
    char pad[0x10];          /* embedded array passed to link() */
    char pad2[0x18];
    int *field_28;           /* set to &D_00000000 */
    char pad3[0x10];
    int field_3C;            /* set to 0 */
};
struct GlOrig {
    char pad[0x40];
    struct GlExisting *field_40;
};
struct GlExisting {
    int field_0;
    int field_4;
    char pad8[0x14 - 8];
    void *field_14;
};
extern int gl_func_00000000();
#ifdef NON_MATCHING
struct GlConstructed *gl_func_000088B4(struct GlOrig *orig) {
    struct GlConstructed *ptr;
    struct GlConstructed *ret;
    struct GlExisting *existing;
    ptr = (struct GlConstructed *)gl_func_00000000(0x40);
    if (ptr != 0) {
        gl_func_00000000(ptr);
        ptr->field_28 = (int *)&D_00000000;
        ptr->field_3C = 0;
    }
    ret = ptr;
    if ((existing = orig->field_40) != 0) {
        gl_func_00000000((char *)ret + 0x10, existing);
        if (existing->field_14 != 0) {
            existing->field_4 = 1;
        }
        existing->field_14 = ret;
    }
    return ret;
}
#else
#ifdef NON_MATCHING
/* gl_func_000088B4: 36-insn constructor + list insert. Alloc a 0x40 object; if
 * non-null, init it (callback) and set obj->0x28 = global, obj->0x3C = 0. Then if
 * the list head a0->0x40 is non-null, locate the insertion node via the callback
 * (obj+0x10, head) and link obj into node->0x14 (setting node->0x4 = 1 first if
 * the slot was occupied). Returns the object. NM (reference decode): collapsed-
 * placeholder calls + collapsed D ref + a beql (raw-.word game_libs reloc
 * depression). */
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_000088B4(int a0) {
    int obj = gl_func_00000000(0x40);
    if (obj != 0) {
        gl_func_00000000(obj);
        *(int *)((char *)obj + 0x28) = (int)&D_00000000;
        *(int *)((char *)obj + 0x3C) = 0;
    }
    if (*(int *)((char *)a0 + 0x40) != 0) {
        int *node = (int *)gl_func_00000000(obj + 0x10, *(int *)((char *)a0 + 0x40));
        if (*(int *)((char *)node + 0x14) != 0) {
            *(int *)((char *)node + 0x4) = 1;
        }
        *(int *)((char *)node + 0x14) = obj;
    }
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000088B4);
#endif
#endif

/* Cluster 0x8944..0x8A40 (-O0 reader templates + sandwich INCLUDE_ASM
 * for 0x8990) split out to game_libs_o0_8944.c on 2026-05-07.
 * Mid 0x8A40..0x949C split out to game_libs_mid.c. Cluster 0x949C..
 * 0x959C (-O0) in game_libs_o0_949C.c. Tail (0x959C+) in
 * game_libs_tail.c. */


/* Fragments 000097B4..00009D24 moved to game_libs_tail.c on
 * 2026-05-21; game_libs.c is truncated at 0x8944. */

/* Fragments 00037E98, 00037F10, 00037F40, 0003AA40, 0003AA5C, 00061F70
 * moved to game_libs_post.c (correct file for VRAM past 0x8944 cap of
 * game_libs.c). */

/* game_libs_func_000622C8 split off from gl_func_00062298 bundle on
 * 2026-05-08; decompiled to C body in game_libs_post.c. */

/* game_libs_func_00024360 + game_libs_func_0002436C split off from
 * gl_func_00024330 bundle on 2026-05-08; decompiled to C bodies in
 * game_libs_post.c.
 *
 * game_libs_func_00024948 split off from gl_func_00024378 bundle on
 * 2026-05-08; decompiled to C body in game_libs_post.c (correct file
 * for VRAM > 0x8944 cap).
 *
 * game_libs_func_00024B8C split off from gl_func_00024B28 bundle on
 * 2026-05-08; 2-insn `jr ra; nop` alt-entry stub. Stays INCLUDE_ASM in
 * game_libs_post.c (no C-decompilable form per fall-through-prologue-stub
 * doc — IDO empty void emit doesn't reproduce explicit nop in delay). */

/* game_libs_func_000671D4 split off from gl_func_0006719C bundle on 2026-05-08; decompiled in game_libs_post.c. */

/* game_libs_func_00060574 split off from gl_func_0006052C bundle on 2026-05-08; decompiled in game_libs_post.c. */

/* game_libs_func_0006833{8,40,48} split off from gl_func_000682F8 bundle on 2026-05-08; INCLUDE_ASMs in game_libs_post.c. */

/* game_libs_func_000683C4 split off from gl_func_00068350 bundle on 2026-05-08; INCLUDE_ASM in game_libs_post.c. */

/* game_libs_func_0004D014 split off from gl_func_0004CFD4 bundle on 2026-05-08; NM-wrapped in game_libs_post.c. */

/* game_libs_func_00054144 split off from gl_func_00053C04 bundle on 2026-05-08; INCLUDE_ASM in game_libs_post.c. */

/* game_libs_func_00031580 split off from gl_func_00031560 bundle on 2026-05-08; NM-wrapped in game_libs_post.c. */

/* game_libs_func_0004EB28 + game_libs_func_0004EB4C split off from gl_func_0004E96C bundle on 2026-05-08; decompiled in game_libs_post.c. */

/* game_libs_func_0003EB90, _0003EB98 split off from gl_func_0003EB3C bundle
 * 2026-05-08; decompiled in game_libs_post.c. */

/* game_libs_func_0003E9C0 split off from gl_func_0003E968 bundle 2026-05-08;
 * decompiled in game_libs_post.c. */

/* game_libs_func_00046048 split off from gl_func_00045FF4 bundle 2026-05-08;
 * decompiled in game_libs_post.c. */

/* gl_func_0004D0B4 bundle split 2026-05-08; children INCLUDE_ASM live in
 * game_libs_post.c next to the parent gl_func_0004D0B4. */

/* gl_func_0004D224 bundle split 2026-05-08; children INCLUDE_ASM live in
 * game_libs_post.c next to the parent gl_func_0004D224. */

/* gl_func_0004D2A0 bundle split 2026-05-08; children INCLUDE_ASM live in
 * game_libs_post.c next to the parent gl_func_0004D2A0. */

/* gl_func_0004D354 bundle split 2026-05-08; children INCLUDE_ASM live in
 * game_libs_post.c next to the parent gl_func_0004D354. */

/* game_libs_func_00033444 split 2026-05-15; INCLUDE_ASM lives in
 * game_libs_post.c next to parent gl_func_0003341C. */

/* game_libs_func_00039988 split 2026-05-15; INCLUDE_ASM/body lives in
 * game_libs_post.c next to parent gl_func_00039960. */

/* game_libs_func_00035360 split 2026-05-15; INCLUDE_ASM lives in
 * game_libs_post.c next to parent gl_func_00035338. */

/* game_libs_func_00066C58 / _00066C60 split 2026-05-15 from gl_func_00066C30;
 * bodies live in game_libs_post.c next to parent. */

/* game_libs_func_0004D3D0: orphan absorbed by the C-emit of
 * game_libs_func_0004D39C (doubly-linked-list insert-after-head;
 * 18/18 exact at .o size 0x48 in game_libs_post.c.o, covers vram
 * 0x4D39C-0x4D3E3 inclusive of the orphan's 5-insn range). The
 * INCLUDE_ASM here was past TRUNCATE_TEXT=0x8944 anyway (dead).
 * Same pattern as the SUFFIX_BYTES-absorbed orphan-prune variants
 * documented in MATCHING_WORKFLOW.md, except absorbed by a C body
 * instead of a Makefile recipe. */

/* game_libs_func_00066200 + game_libs_func_00066208 + game_libs_func_0002D7C0:
 * SUFFIX_BYTES-absorbed orphans whose bytes are emitted by the post-cc
 * recipes on adjacent gl_func_* entries in game_libs_post.c.o (see Makefile:
 * gl_func_000661D8 SUFFIX_BYTES covers 0x66200/0x66208; gl_func_0002D788
 * INSN_PATCH+SUFFIX_BYTES + gl_func_0002D7D0 PROLOGUE_STEALS cover 0x2D7C0).
 * The .s files existed as splat-extracted symbol entries but were never used
 * by the build (game_libs.c.o gets truncated to 0x8944, dropping any
 * INCLUDE_ASM bytes placed past that offset). Removed to stop the discover
 * tool from re-surfacing them as candidates. See
 * docs/MATCHING_WORKFLOW.md#feedback-splat-orphan-duplicate-symbol-pruning
 * SUFFIX_BYTES-absorbed orphan variant. */

/* Additional SUFFIX_BYTES-absorbed orphans (same pattern as the cluster
 * above): game_libs_func_0003058C → gl_func_00030564 SUFFIX_BYTES (3 words
 * 0x3C020000,0x24420000,0x8C4E0008); game_libs_func_00030610 →
 * gl_func_000305CC SUFFIX_BYTES (3 words 0x3C020000,0x24420000,0x8C4E0000);
 * game_libs_func_0005FDC0 → gl_func_0005FD20 SUFFIX_BYTES (3 words
 * 0x00000000,0x3C060000,0x8CC60000); game_libs_func_0002DEF4 →
 * gl_func_0002DED0 SUFFIX_BYTES (3 words 0x000470C0,0x01C52021,0x2484001A).
 * All four predecessor recipes live on game_libs_post.c.o. */

/* game_libs_func_00008668: SUFFIX_BYTES-absorbed orphan ← gl_func_000085B0
 * (3 words 0x3C030000,0x24630000,0x8C620028 exact match). gl_func_000085B0
 * is in this same file with size 0xC4 covering the orphan's vram. The
 * orphan symbol pre-prune sat at .o offset 0x8944 (= TRUNCATE_TEXT cap)
 * with size 0 — its bytes never reached the link. */

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070A0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006BA74);


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00051654);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0004E57C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0003FB64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002DF30);

