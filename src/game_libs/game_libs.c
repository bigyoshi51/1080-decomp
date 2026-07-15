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
    float div255 = 255.0f;
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
    *(float*)((char*)s0 + 0xC4) = 250.0f / div255;
    *(float*)((char*)s0 + 0xC8) = 235.0f / div255;
    *(float*)((char*)s0 + 0xCC) = 100.0f / div255;
    *(float*)((char*)s0 + 0xD0) = 0.0f / div255;
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

/* gl_func_00000338: MATCHED 2026-05-31. ms time formatter — SIGNED div (the
 * break-0x7/0x6 div-by-zero+INT_MIN-overflow traps confirm signed, not unsigned):
 * mins = a1/60000, rem = a1 - mins*60000, secs = rem/1000, ms = (rem - secs*1000)/10;
 * then sprintf(out+0xE4, &D+0xCB08, mins, secs, ms). The old stub had a1 unsigned +
 * wrong arithmetic (a1-mins, rem-secs*10). */
extern int gl_func_00000000();
void gl_func_00000338(char *a0, int a1) {
    int mins = a1 / 60000;
    int rem = a1 - mins * 60000;
    int secs = rem / 1000;
    int ms_part = (rem - secs * 1000) / 10;
    gl_func_00000000(a0 + 0xE4, (char*)&D_00000000 + 0xCB08, mins, secs, ms_part);
}

#ifdef NON_MATCHING
/* gl_func_00000400: 93-insn nested-alloc + color-normalize constructor.
 * Alloc-cascade family (cf gl_func_000001CC / gl_func_00000A8C) with THREE
 * nested alloc levels (obj -> sub -> sub2), each defensively initialized, plus
 * the 250/235/100/0 RGBA-over-255 color set. Short-circuit || cascade colors
 * sub=$v1 like the target; fixes the m2c dump bugs: 0xCB18/0xCB20 are
 * (char*)&D_00000000 + off relocs (not integer ori); init(sub2,&ref) is 2-arg
 * (sub2 stays $a2); denom = 255.0f forces the runtime div.s. */
extern int gl_func_00000000();
int gl_func_00000400(int *a0, int a1) {
    int *obj;
    float denom;
    int *sub;
    int *sub2;

    obj = a0;
    if ((a0 != 0) || (obj = (int*)gl_func_00000000(0x13C), obj != 0)) {
        sub = obj;
        if ((obj != 0) || (sub = (int*)gl_func_00000000(0x10C), sub != 0)) {
            sub2 = sub;
            if ((sub != 0) || (sub2 = (int*)gl_func_00000000(0x10C), sub2 != 0)) {
                gl_func_00000000(sub2, (char*)&D_00000000 + 0xCB18);
                *(int*)((char*)sub2 + 0x28) = (int)&D_00000000;
                gl_func_00000000((char*)sub2 + 0x2C);
            }
            *(int*)((char*)sub + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)obj + 0xC) = (int)((char*)&D_00000000 + 0xCB20);
        gl_func_00000000((char*)obj + 0x10C, 0x5001B);
        gl_func_00000000((char*)obj + 0x124, 0x5001D);
        gl_func_00000000(obj, (char*)obj + 0x124, (char*)obj + 0x10C);
        *(int*)((char*)obj + 0xD4) = 0;
        *(int*)((char*)obj + 0xD8) = 255;
        *(int*)((char*)obj + 0xDC) = 130;
        denom = 255.0f;
        *(float*)((char*)obj + 0xC4) = 250.0f / denom;
        *(float*)((char*)obj + 0xC8) = 235.0f / denom;
        *(float*)((char*)obj + 0xCC) = 100.0f / denom;
        *(float*)((char*)obj + 0xD0) = 0.0f / denom;
        *(int*)((char*)obj + 0xE0) = a1;
        gl_func_00000000(obj, -80, -1, -61, 0);
    }
    return (int)obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000400);
#endif

extern int gl_func_00000000();
int gl_func_00000574(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CB30;

void gl_func_000005A4(char *a0, char a1, char a2, char a3) {
    gl_func_00000000(a0 + 0xE4, &gl_ref_0000CB30, a1, a2, a3);
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000005EC)();
char *gl_func_000005EC(char *arg0, s32 arg1) {
    f32 d255 = 255.0f;
    char *var_a2;
    char *var_s0;
    char *var_v1;

    var_s0 = arg0;
    if ((arg0 != 0) || (var_s0 = (char*)func_00000000((char *)0x13C), (var_s0 != 0))) {
        var_v1 = var_s0;
        if ((var_s0 != 0) || (var_v1 = (char*)func_00000000((char *)0x10C), (var_v1 != 0))) {
            var_a2 = var_v1;
            if ((var_v1 != 0) || (var_a2 = (char*)func_00000000((char *)0x10C), (var_a2 != 0))) {
                (char*)func_00000000(var_a2, (char*)&D_00000000 + 0xCB40, var_a2);
                FW(var_a2, 0x28) = (int)&D_00000000;
                (char*)func_00000000(var_a2 + 0x2C);
            }
            FW(var_v1, 0x28) = (int)&D_00000000;
        }
        FW(var_s0, 0xC) = (int)((char*)&D_00000000 + 0xCB48);
        (char*)func_00000000(var_s0 + 0x10C, (char *)0x5001E);
        (char*)func_00000000(var_s0 + 0x124, (char *)0x5001D);
        (char*)func_00000000(var_s0, var_s0 + 0x124, var_s0 + 0x10C);
        FW(var_s0, 0xD4) = 0;
        FW(var_s0, 0xD8) = 0xFF;
        FW(var_s0, 0xDC) = 0x82;
        *(f32*)((char*)var_s0 + 0xC4) = 250.0f / d255;
        *(f32*)((char*)var_s0 + 0xC8) = 235.0f / d255;
        *(f32*)((char*)var_s0 + 0xCC) = 100.0f / d255;
        *(f32*)((char*)var_s0 + 0xD0) = 0.0f / d255;
        FW(var_s0, 0xE0) = arg1;
        (char*)func_00000000(var_s0, (char *)-0x38, (char *)-1, -0x26, 0);
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000005EC);
#endif

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

/* gl_func_000007BC: MATCH 2026-07-15 (agent-h) — 5-member composite constructor,
 * full ||-alloc-fallback reconstruction (was 59.4% m2c lift). Levers, in order:
 * (1) head `if (self != 0 || (self = alloc(0x68)) != 0)` with alloc-failure
 *     falling to the SHARED epilogue; per-member `if ((m = self+OFF) != 0 ||
 *     (m = alloc(0x18)) != 0)` — IDO folds m!=0 into `bne s0,-OFF` with the
 *     addiu in the delay slot.
 * (2) the arg value is a 4-byte STRUCT passed by value: `u1.v = <sym>; t = u1;
 *     ctor(m, self, t, 1)` — struct-by-value gives BOTH the arg-slot store
 *     `sw a2,8(sp)` in the ctor jal delay AND the join-order `lw a2,home`
 *     before `move a1,s0`; the struct copy keeps the loaded value a RING temp
 *     feeding both member stores (every scalar spelling colored it $v0);
 *     u1..u4 = per-expansion dead-store homes 0x44..0x38, t = shared 0x24.
 * (3) gl_ref_0000CBxx_i SYMBOL loads (not literal derefs) for destructive
 *     base reuse `lui t7; lw t7,%lo(t7)`; 4 DISTINCT gl_ref_0000C764_N
 *     aliases bust the cross-expansion &sym CSE (a shared extern spilled the
 *     address across calls); addr-store FIRST + one-line join flips the
 *     addr/value ring creation order while keeping sw 0x10-before-0xC.
 * (4) volatile pads pad1/pad2 = the 2 phantom frame slots between p and m.
 * 102/120 .o words exact; all 18 remaining are %hi/%lo reloc fields resolved
 * by undefined_syms (ROM cmp = gate). */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern char gl_ref_0000CB60;
extern char gl_ref_0000C764_1;
extern char gl_ref_0000C764_2;
extern char gl_ref_0000C764_3;
extern char gl_ref_0000C764_4;
extern int gl_ref_0000CB74_i;
extern int gl_ref_0000CB78_i;
extern int gl_ref_0000CB7C_i;
extern int gl_ref_0000CB80_i;
struct SB7BC { int v; };
char *gl_func_000007BC(char *self) {
    struct SB7BC u1;
    struct SB7BC u2;
    struct SB7BC u3;
    struct SB7BC u4;
    char *p;
    volatile int pad1;
    volatile int pad2;
    char *m;
    struct SB7BC t;
    if (self != 0 || (self = (char *)gl_func_00000000(0x68)) != 0) {
        if ((p = self) != 0 || (p = (char *)gl_func_00000000(8)) != 0) {
            FW(p, 0) = (int)&gl_ref_0000CB60;
            FW(p, 4) = 0;
        }
        u1.v = gl_ref_0000CB74_i;
        t = u1;
        if ((m = self + 8) != 0 || (m = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m, self, t, 1);
            FW(m, 0xC) = (int)&gl_ref_0000C764_1; FW(m, 0x10) = 0x1E; FW(m, 0x14) = 0;
        }
        u2.v = gl_ref_0000CB78_i;
        t = u2;
        if ((m = self + 0x20) != 0 || (m = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m, self, t, 1);
            FW(m, 0xC) = (int)&gl_ref_0000C764_2; FW(m, 0x10) = 0x1E; FW(m, 0x14) = 0;
        }
        u3.v = gl_ref_0000CB7C_i;
        t = u3;
        if ((m = self + 0x38) != 0 || (m = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m, self, t, 1);
            FW(m, 0xC) = (int)&gl_ref_0000C764_3; FW(m, 0x10) = 4; FW(m, 0x14) = 0;
        }
        u4.v = gl_ref_0000CB80_i;
        t = u4;
        if ((m = self + 0x50) != 0 || (m = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m, self, t, 1);
            FW(m, 0xC) = (int)&gl_ref_0000C764_4; FW(m, 0x10) = -2; FW(m, 0x14) = 0;
        }
    }
    return self;
}


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

extern int gl_func_00000000();
void gl_func_000009B4(char *arg0) {
    char *a2;
    volatile int pad[7];  /* phantom-slot lever: the target's 0x20 unused stack (cf. 628EC) */

    gl_func_00000000(*(int *)(arg0 + 0xAC));
    a2 = arg0 + 0x94;
    gl_func_00000000(*(int *)(arg0 + 0xAC),
                     (int)(*(float *)&D_00000000 * (float)*(int *)(arg0 + 0xA8)),
                     a2, *(int *)(arg0 + 0xA4));
    gl_func_00000000(*(int *)(arg0 + 0xAC), *(int *)(arg0 + 0x44),
                     *(int *)(arg0 + 0x5C), arg0 + 0xB4);
    gl_func_00000000(*(int *)(arg0 + 0xB0));
    gl_func_00000000(*(int *)(arg0 + 0xB0),
                     (int)(*(float *)&D_00000000 * (float)*(int *)(arg0 + 0xA8)),
                     a2, *(int *)(arg0 + 0xA4));
    gl_func_00000000(*(int *)(arg0 + 0xB0),
                     *(int *)(arg0 + 0x74) + *(int *)(arg0 + 0x44),
                     *(int *)(arg0 + 0x8C) + *(int *)(arg0 + 0x5C),
                     arg0 + 0xBC);
}

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
/* game_libs_func_00000B94: ms->time formatter (a1 / 60000 = minutes, etc.).
 * Merged 2026-05-23: splat mis-split this at 0xBAC into game_libs_func_00000B94
 * (head: div a1,60000; v0<<4; multu v0,60000 — no prologue/jr) + gl_func_00000BAC
 * (body: mflo of B94's multu, prologue, sprintf-style calls, epilogue). The
 * multu(B94)/mflo(BAC) LO-register dependency proves they are one function;
 * IDO scheduled the division setup before the addiu sp prologue. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
void game_libs_func_00000B94(char *arg0, s32 arg1, s32 arg2) {
    s32 sp24;
    s32 qmin;
    s32 rem;
    s32 qsec;
    s32 secs;
    s32 temp_a2;
    s32 temp_v0;

    qmin = arg1 / 60000;
    rem = arg1 - (qmin * 60000);
    FW(arg0, 0xC8) = arg2;
    qsec = rem / 1000;
    secs = qsec + (qmin * 0x3C);
    FW(arg0, 0xD0) = secs;
    if (secs == 0) {
        sp24 = (rem - (qsec * 1000)) / 10;
        if (sp24 != 0) {
            goto block_4;
        }
        goto block_5;
    }
block_4:
    sp24 = (rem - (qsec * 1000)) / 10;
    if (FW(arg0, 0xC8) == 0) {
block_5:
        FW(arg0, 0xC4) = 8;
    }
    temp_a2 = FW(arg0, 0xD0);
    if (temp_a2 >= 0x64) {
        gl_func_00000000((int)arg0 + 0xB4, 0xCB9C, temp_a2, rem);
    } else if (temp_a2 >= 0xA) {
        gl_func_00000000((int)arg0 + 0xB4, 0xCBA0, temp_a2, rem);
    } else {
        if (temp_a2 != FW(arg0, 0xCC)) {
            gl_func_00000000((char *)0x13, temp_a2, temp_a2, rem);
        }
        temp_v0 = FW(arg0, 0xC4);
        FW(arg0, 0xC4) = (s32) (temp_v0 + 1);
        if (temp_v0 & 8) {
            gl_func_00000000((int)arg0 + 0xB4, 0xCBA8, FW(arg0, 0xD0));
        } else {
            gl_func_00000000((int)arg0 + 0xB4, 0xCBB0, FW(arg0, 0xD0));
        }
        FW(arg0, 0xCC) = (s32) FW(arg0, 0xD0);
    }
    gl_func_00000000((int)arg0 + 0xBC, 0xCBB8, sp24);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00000B94);
#endif

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
/* gl_func_00000D5C - get-or-create constructor + child wiring (0x118,
 * 70 insns). Two nested get-or-create branches: outer allocs the main
 * object s0 (316/0x13C bytes) when arg null; inner allocs a sub-object
 * `sub` (268/0x10C bytes) when null, then init-calls
 * gl_func_00000000(sub, &D+0xCBC0). sub->0x28 = &D descriptor, then
 * gl_func_00000000(sub+0x2C). s0->0xC = &D+0xCBC8 descriptor. Two
 * embedded children at s0+268 / s0+292 init'd with packed ids
 * 0x050001 / 0x050007 then cross-wired via
 * gl_func_00000000(s0, s0+292, s0+268). Field block 0xC4/0xC8/0xCC f32
 * = global default (&D+0xC70); 0xD0 f32 = 0.0; 0xD4=0; 0xD8=255;
 * 0xDC=130; 0xE0=a1. Final gl_func_00000000(s0,-56,-1,-13,0).
 * MATCHED 2026-07-11 (byte-exact): BASE-SYMBOLIZE (pointer-arith (char*)&D+off,
 * not (int)&D+off which folds to a raw `ori` since D is absolute-0) recovered
 * the lui/addiu descriptor relocs; outer alloc-fail routed to shared `done`
 * (returns s0=0) not a separate `return 0`; inner alloc-fail skips only the
 * sub-init block (goto skip_init) rather than the whole tail. */
void *gl_func_00000D5C(char *s0, int a1) {
    char *sub;
    float k;
    if (s0 == 0) {
        s0 = (char*)gl_func_00000000(316);
        if (s0 == 0) goto done;
    }
    sub = s0;
    if (sub == 0) {
        sub = (char*)gl_func_00000000(268);
        if (sub == 0) goto skip_init;
    }
    gl_func_00000000(sub, (char*)&D_00000000 + 0xCBC0);
    *(int*)(sub + 0x28) = (int)&D_00000000;
    gl_func_00000000(sub + 0x2C);
skip_init:
    *(int*)(s0 + 0xC) = (int)((char*)&D_00000000 + 0xCBC8);
    gl_func_00000000(s0 + 268, 0x050001);
    gl_func_00000000(s0 + 292, 0x050007);
    gl_func_00000000(s0, s0 + 292, s0 + 268);
    k = *(float*)((char*)&D_00000000 + 0xC70);
    *(int*)(s0 + 0xD4) = 0;
    *(int*)(s0 + 0xD8) = 255;
    *(int*)(s0 + 0xDC) = 130;
    *(float*)(s0 + 0xC4) = k;
    *(float*)(s0 + 0xC8) = k;
    *(float*)(s0 + 0xCC) = k;
    *(float*)(s0 + 0xD0) = 0.0f;
    *(int*)(s0 + 0xE0) = a1;
    gl_func_00000000(s0, -56, -1, -13, 0);
done:
    return s0;
}

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

/* gl_func_00000ED0: constructor. obj = a0 ?: alloc(212); a defensive second
 * obj-or-alloc (node); init(node, &D+0xCBE0); node->0x28 = &D; init(node+0x2C);
 * then field inits (vtable ptr &D+0xCBE8, three 0xC74-floats, flags). Returns
 * obj. Matched: param-direct (reuse a0 instead of separate obj local) puts obj
 * in $a2 / node in $a3; second-alloc failure falls through to field-init (not
 * ret); 0xA0/0xB0 store-order swap fixes the as1 scheduler tie. */
int gl_func_00000ED0(int a0, int a1) {
    int node;
    float v;
    if (a0 == 0) {
        a0 = gl_func_00000000(212);
        if (a0 == 0) {
            goto ret;
        }
    }
    node = a0;
    if (node == 0) {
        node = gl_func_00000000(212);
        if (node == 0) {
            goto initfields;
        }
    }
    gl_func_00000000(node, (char*)&D_00000000 + 0xCBE0);
    *(int*)(node + 0x28) = (int)&D_00000000;
    gl_func_00000000(node + 0x2C);
initfields:
    v = *(float*)((char*)&D_00000000 + 0xC74);
    *(int*)(a0 + 0xC) = (int)((char*)&D_00000000 + 0xCBE8);
    *(int*)(a0 + 0x74) = 0;
    *(int*)(a0 + 0x78) = 255;
    *(float*)(a0 + 0x64) = v;
    *(float*)(a0 + 0x68) = v;
    *(float*)(a0 + 0x6C) = v;
    *(float*)(a0 + 0x70) = 0.0f;
    *(int*)(a0 + 0xB0) = a1;
    *(int*)(a0 + 0xA0) = 0;
ret:
    return a0;
}

void game_libs_func_00000F9C(int a0) {
}

extern int gl_func_00000000();
extern char gl_ref_0000CBF8;
int gl_func_00000FA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xB4, &gl_ref_0000CBF8, arg1);
}

#ifdef NON_MATCHING
extern int func_00000000();
extern char gl_ref_0000CBFC;
extern char gl_ref_0000CC04;
char *gl_func_00000FD0(char *arg0, s32 arg1) {
  f32 d255;
  char *var_s0;
  char *var_a2;
  volatile char pad[4];
  (void)pad;

  var_s0 = arg0;
  if ((arg0 != 0) || ((var_s0 = (char *) func_00000000((char *) 0x13C)) != 0)) {
    var_a2 = var_s0;
    if ((var_s0 != 0) || ((var_a2 = (char *) func_00000000((char *) 0x10C)) != 0)) {
      func_00000000(var_a2, &gl_ref_0000CBFC);
      *((int *) (var_a2 + 0x28)) = (int) (&D_00000000);
      func_00000000(var_a2 + 0x2C);
    }
    *((int *) (var_s0 + 0xC)) = (int) (&gl_ref_0000CC04);
    func_00000000(var_s0 + 0x10C, (char *) 0x50002);
    func_00000000(var_s0 + 0x124, (char *) 0x50008);
    func_00000000(var_s0, var_s0 + 0x124, var_s0 + 0x10C);
    *((int *) (var_s0 + 0xD4)) = 0x80;
    *((int *) (var_s0 + 0xD8)) = 0xFF;
    *((int *) (var_s0 + 0xDC)) = 0x82;
    d255 = 255.0f;
    *((f32 *) (var_s0 + 0xC4)) = 250.0f / d255;
    *((f32 *) (var_s0 + 0xC8)) = 235.0f / d255;
    *((f32 *) (var_s0 + 0xCC)) = 100.0f / d255;
    *((f32 *) (var_s0 + 0xD0)) = 0.0f / d255;
    *((int *) (var_s0 + 0xE0)) = arg1;
    func_00000000(var_s0, (char *) (-3), (char *) (-1), 0x25, 0);
  }
  return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000FD0);
#endif

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

/* gl_func_000011A4: MATCH 2026-07-15 (agent-h) — ||-alloc-fallback rewrite of
 * the goto-form get-or-create body (89.7 -> 100). The documented residual
 * ("prologue scheduler tie + sub spill 0x24 vs 0x20 — not C-coaxable") was
 * the CONTROL-FLOW SPELLING: `if (self != 0 || (self = alloc(0x140)) != 0)`
 * param-reassign head gives move-s0-before-bnez with sw ra in the delay, and
 * the inner `if ((sub = self) != 0 || (sub = alloc(0x10C)) != 0)` recolors
 * sub to $a2 with home 0x24. Distinct abs-0 alias gl_data_00000000_11a4 for
 * the 0x54 load base busts the &gl_data CSE with the self->0x28 store
 * (target rematerializes; shared symbol spilled a candidate). 54/54 words. */
extern int gl_data_00000000;
extern int gl_data_00000000_11a4;
int* gl_func_000011A4(int *self) {
    int *sub;
    float f;
    if (self != 0 || (self = (int*)gl_func_00000000(0x140)) != 0) {
        if ((sub = self) != 0 || (sub = (int*)gl_func_00000000(0x10C)) != 0) {
            gl_func_00000000(sub, (char*)&gl_data_00000000 + 0xCC20);
            *(int*)((char*)sub + 0x28) = (int)&D_00000000;
            gl_func_00000000((char*)sub + 0x2C);
        }
        *(int*)((char*)self + 0x28) = (int)&gl_data_00000000;
        *(int*)((char*)self + 0xC) = (int)((char*)&gl_data_00000000 + 0xCC28);
        gl_func_00000000((char*)self + 0x110,
            *(int*)((char*)&gl_data_00000000_11a4 + 0x54) | 0x001E0000);
        f = *(float*)((char*)&D_00000000 + 0xC78);
        *(int*)((char*)self + 0xD4) = 0;
        *(int*)((char*)self + 0xD8) = 0xFF;
        *(int*)((char*)self + 0x10C) = 0;
        *(float*)((char*)self + 0xC4) = f;
        *(float*)((char*)self + 0xC8) = f;
        *(float*)((char*)self + 0xCC) = f;
        *(float*)((char*)self + 0xD0) = 0.0f;
    }
    return self;
}

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

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_0000135C: MATCH 2026-07-15 (agent-h) — direct transfer of the
 * gl_func_000007BC struct-by-value ||-alloc-fallback kit (see 7BC comment /
 * docs/IDO_CODEGEN "struct-by-value arg carrier"): 6-member get-or-create
 * constructor, head alloc 0x98, header node CC38, member seeds CC40..CC54
 * as gl_ref symbol loads (destructive lui/lw base reuse), 4-byte struct t2
 * passed by value to the member ctor (sw a2,8(sp) delay store — the exact
 * residual the old cap note said "the C form can't force"), distinct
 * gl_ref_0000C764_135C_N aliases per expansion, volatile pads for the two
 * phantom slots. Retracts the "genuine cap / scheduler tie" verdict — the
 * prologue tie disappeared with this structure too. */
extern char gl_ref_0000CC38;
extern char gl_ref_0000C764_135C_1;
extern char gl_ref_0000C764_135C_2;
extern char gl_ref_0000C764_135C_3;
extern char gl_ref_0000C764_135C_4;
extern char gl_ref_0000C764_135C_5;
extern char gl_ref_0000C764_135C_6;
extern int gl_ref_0000CC40_i;
extern int gl_ref_0000CC44_i;
extern int gl_ref_0000CC48_i;
extern int gl_ref_0000CC4C_i;
extern int gl_ref_0000CC50_i;
extern int gl_ref_0000CC54_i;
struct SB135C { int v; };
char *gl_func_0000135C(char *self) {
    struct SB135C u1;
    struct SB135C u2;
    struct SB135C u3;
    struct SB135C u4;
    struct SB135C u5;
    struct SB135C u6;
    char *p2;
    volatile int pad1;
    volatile int pad2;
    char *m2;
    struct SB135C t2;
    if (self != 0 || (self = (char *)gl_func_00000000(0x98)) != 0) {
        if ((p2 = self) != 0 || (p2 = (char *)gl_func_00000000(8)) != 0) {
            FW(p2, 0) = (int)&gl_ref_0000CC38;
            FW(p2, 4) = 0;
        }
        u1.v = gl_ref_0000CC40_i;
        t2 = u1;
        if ((m2 = self + 8) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_1; FW(m2, 0x10) = 0x1E; FW(m2, 0x14) = 0;
        }
        u2.v = gl_ref_0000CC44_i;
        t2 = u2;
        if ((m2 = self + 0x20) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_2; FW(m2, 0x10) = 0x1E; FW(m2, 0x14) = 0;
        }
        u3.v = gl_ref_0000CC48_i;
        t2 = u3;
        if ((m2 = self + 0x38) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_3; FW(m2, 0x10) = 2; FW(m2, 0x14) = 0;
        }
        u4.v = gl_ref_0000CC4C_i;
        t2 = u4;
        if ((m2 = self + 0x50) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_4; FW(m2, 0x10) = -0xC; FW(m2, 0x14) = 0;
        }
        u5.v = gl_ref_0000CC50_i;
        t2 = u5;
        if ((m2 = self + 0x68) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_5; FW(m2, 0x10) = 2; FW(m2, 0x14) = 0;
        }
        u6.v = gl_ref_0000CC54_i;
        t2 = u6;
        if ((m2 = self + 0x80) != 0 || (m2 = (char *)gl_func_00000000(0x18)) != 0) {
            gl_func_00000000(m2, self, t2, 1);
            FW(m2, 0xC) = (int)&gl_ref_0000C764_135C_6; FW(m2, 0x10) = -0xC; FW(m2, 0x14) = 0;
        }
    }
    return self;
}


#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_000015FC: NM wrap. Minimal-locals (drop redundant sp2C/sp28/temp_*)
 * shrinks frame 0x50->0x38 to match expected; distinct float-pool symbols
 * (D_00000C7C..) force per-load re-deref (lui at; lwc1 off(at)) instead of a
 * CSE'd cached base; D_0000CC58/D_0000CC60 give lui+addiu (not ori) for the
 * 0xCC58/0xCC60 absolutes. Residual = IDO swc1/lwc1 scheduling + prologue
 * move-s0 placement (coloring/scheduling cap). 69.96 -> 81.96% fuzzy. */
extern f32 D_00000C7C, D_00000C80, D_00000C84, D_00000C88, D_00000C8C, D_00000C90, D_00000C94;
extern char D_0000CC58[], D_0000CC60[];
char *gl_func_000015FC(char *arg0, s32 arg1) {
    f32 temp_f2;
    char *var_s0;

    var_s0 = arg0;
    if ((arg0 != 0) || (var_s0 = (char*)func_00000000((char *)0x198), (var_s0 != 0))) {
        (char*)func_00000000(var_s0, D_0000CC58);
        FW(var_s0, 0x28) = 0;
        (char*)func_00000000(var_s0 + 0x2C);
        temp_f2 = D_00000C7C;
        FW(var_s0, 0xC) = (int)D_0000CC60;
        *(f32*)((char*)var_s0 + 0xE8) = temp_f2;
        *(f32*)((char*)var_s0 + 0xF8) = temp_f2;
        *(f32*)((char*)var_s0 + 0xEC) = 0.0f;
        *(f32*)((char*)var_s0 + 0xF0) = 0.0f;
        *(f32*)((char*)var_s0 + 0xF4) = 0.0f;
        *(f32*)((char*)var_s0 + 0xFC) = 0.0f;
        *(f32*)((char*)var_s0 + 0x100) = 0.0f;
        *(f32*)((char*)var_s0 + 0x104) = 0.0f;
        *(f32*)((char*)var_s0 + 0x114) = 0.0f;
        *(f32*)((char*)var_s0 + 0x110) = 0.0f;
        *(f32*)((char*)var_s0 + 0x10C) = 0.0f;
        *(f32*)((char*)var_s0 + 0x108) = D_00000C80;
        *(f32*)((char*)var_s0 + 0x118) = 1.0f;
        *(f32*)((char*)var_s0 + 0x124) = 0.0f;
        *(f32*)((char*)var_s0 + 0x120) = 0.0f;
        *(f32*)((char*)var_s0 + 0x11C) = D_00000C84;
        *(f32*)((char*)var_s0 + 0xD8) = D_00000C88;
        *(f32*)((char*)var_s0 + 0xDC) = D_00000C8C;
        *(f32*)((char*)var_s0 + 0xE4) = 0.0f;
        *(f32*)((char*)var_s0 + 0xE0) = D_00000C90;
        FW(var_s0, 0xCC) = 0x64;
        FW(var_s0, 0xC8) = 0x64;
        *(f32*)((char*)var_s0 + 0x128) = 0.0f;
        FW(var_s0, 0xD4) = arg1;
        FW(var_s0, 0xD0) = 0x82;
        *(f32*)((char*)var_s0 + 0x12C) = D_00000C94;
        (char*)func_00000000(var_s0 + 0x138, (char *)0x5000A);
        (char*)func_00000000(var_s0 + 0x150, (char *)0x50009);
        (char*)func_00000000(var_s0 + 0x180, (char *)0x5000B);
        (char*)func_00000000(var_s0 + 0x168, (char *)0x5001C);
        (char*)func_00000000(var_s0, var_s0 + 0x168, var_s0 + 0x180);
        (char*)func_00000000(var_s0, (char *)-0x49, (char *)-2, -0x32, -1);
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000015FC);
#endif

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

/* game_libs_func_00001818: 2-insn FPU preload fragment, not a standalone
 * function. SOURCE=3 audit 2026-06-01: 0x1818 has no prologue and no
 * `jr ra` (`grep -c 03E00008` = 0); it materializes $f0 = 1.0f and falls
 * through into gl_func_00001820, whose entry stores incoming $f0 to the
 * local float buffer at sp+0x80..0x8C. No honest C wrapper can express this
 * caller-visible FPU-register seed, so keep INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00001818);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001820);

#ifdef NON_MATCHING
/* PASS-4 2026-06-27 (5th-arg fix, 69.8% -> 77.1% fuzzy):
 * init() takes FIVE args, not four: init(child, arg0, id, 1, id). The target
 * emits `sw a2,8(sp)` in every jal delay slot (the 5th stack arg = id again),
 * which also forces the doubled id spill (rotating slot + 132/8(sp)). Passing
 * the id twice reproduces both. +7.3pp across all 16 call blocks.
 * PASS-3 2026-06-22 (big-swing reconstruction, 54.5% -> 69.8% fuzzy):
 * alloc-cascade constructor. 16 near-identical "register child slot" blocks:
 * read a setup id from the D_00000000+0xCC74.. table (real HI16/LO16 globals,
 * not literals), compute child = arg0+off, alloc(0x18) when arg0 is the -off
 * sentinel, init(child,arg0,id,1), then stamp child[0xC]=&D+0xC764 + magic.
 * The 14 ids[] dead stores survive via array-address-taken (blocks IDO DCE);
 * the float block (0x24 child) sets up 3 stack quads {0,1,glob,1}/{1,1,1,1}/
 * {0,0,0,0} and word-copies (Quad4) before reading the first into the child.
 * RESIDUAL = register-coloring cap (same as timproc_uso_b5_func_00002B74):
 * target keeps ONLY arg0 in $s0 and caller-saves/spills every child around its
 * alloc/init call (~33 extra `sw`); IDO promotes the child to a 2nd callee-saved
 * reg here, shifting all stack offsets. Tried param-reuse, separate-`self`,
 * distinct per-slot scalars (the doc'd fix), split-live-range goto, recycled
 * `char*[1]` spill buf + cached reload -- each whack-a-moles ONE value into
 * $s/spill but not both (the child's 3 post-call field stores tip IDO to $s
 * unlike timproc's 1). Genuine coloring cap; structure/callees/globals exact. */
extern int gl_func_00000000();
#define D_REF(o) ((char *)&D_00000000 + (o))
#define GL_ID(o)  (*(s32 *)D_REF(o))
#define GL_C764   ((s32)D_REF(0xC764))

void *gl_func_00001C54(char *arg0) {
    s32 ids[14];
    s32 id9C;
    s32 id98;

    if ((arg0 != 0) || (arg0 = (char *)gl_func_00000000(0x194), (arg0 != 0))) {
        char *v1 = arg0;
        if ((arg0 != 0) || (v1 = (char *)gl_func_00000000(8), (v1 != 0))) {
            *(s32 *)(v1 + 0x0) = (s32)D_REF(0xCC6C);
            *(s32 *)(v1 + 0x4) = 0;
        }
        ids[0] = GL_ID(0xCC74);
        { char *c0 = arg0 + 0x8;
        if ((arg0 != (char *)-0x8) || (c0 = (char *)gl_func_00000000(0x18), (c0 != 0))) {
            gl_func_00000000(c0, arg0, ids[0], 1, ids[0]);
            *(s32 *)(c0 + 0x10) = 0x1E;
            *(s32 *)(c0 + 0xC) = GL_C764;
            *(s32 *)(c0 + 0x14) = 0;
        } }
        ids[1] = GL_ID(0xCC78);
        { char *c1 = arg0 + 0x20;
        if ((arg0 != (char *)-0x20) || (c1 = (char *)gl_func_00000000(0x18), (c1 != 0))) {
            gl_func_00000000(c1, arg0, ids[1], 1, ids[1]);
            *(s32 *)(c1 + 0x10) = 0x1E;
            *(s32 *)(c1 + 0xC) = GL_C764;
            *(s32 *)(c1 + 0x14) = 0;
        } }
        ids[2] = GL_ID(0xCC7C);
        { char *c2 = arg0 + 0x38;
        if ((arg0 != (char *)-0x38) || (c2 = (char *)gl_func_00000000(0x18), (c2 != 0))) {
            gl_func_00000000(c2, arg0, ids[2], 1, ids[2]);
            *(s32 *)(c2 + 0x10) = 0xA;
            *(s32 *)(c2 + 0xC) = GL_C764;
            *(s32 *)(c2 + 0x14) = 0;
        } }
        ids[3] = GL_ID(0xCC80);
        { char *c3 = arg0 + 0x50;
        if ((arg0 != (char *)-0x50) || (c3 = (char *)gl_func_00000000(0x18), (c3 != 0))) {
            gl_func_00000000(c3, arg0, ids[3], 1, ids[3]);
            *(s32 *)(c3 + 0x10) = 0x73;
            *(s32 *)(c3 + 0xC) = GL_C764;
            *(s32 *)(c3 + 0x14) = 0;
        } }
        ids[4] = GL_ID(0xCC84);
        { char *c4 = arg0 + 0x68;
        if ((arg0 != (char *)-0x68) || (c4 = (char *)gl_func_00000000(0x18), (c4 != 0))) {
            gl_func_00000000(c4, arg0, ids[4], 1, ids[4]);
            *(s32 *)(c4 + 0xC) = GL_C764;
            *(s32 *)(c4 + 0x14) = 0;
            *(s32 *)(c4 + 0x10) = 0;
        } }
        ids[5] = GL_ID(0xCC88);
        { char *c5 = arg0 + 0x80;
        if ((arg0 != (char *)-0x80) || (c5 = (char *)gl_func_00000000(0x18), (c5 != 0))) {
            gl_func_00000000(c5, arg0, ids[5], 1, ids[5]);
            *(s32 *)(c5 + 0xC) = GL_C764;
            *(s32 *)(c5 + 0x14) = 0;
            *(s32 *)(c5 + 0x10) = 0;
        } }
        ids[6] = GL_ID(0xCC8C);
        { char *c6 = arg0 + 0x98;
        if ((arg0 != (char *)-0x98) || (c6 = (char *)gl_func_00000000(0x18), (c6 != 0))) {
            gl_func_00000000(c6, arg0, ids[6], 1, ids[6]);
            *(s32 *)(c6 + 0x10) = 0xB;
            *(s32 *)(c6 + 0xC) = GL_C764;
            *(s32 *)(c6 + 0x14) = 0;
        } }
        ids[7] = GL_ID(0xCC90);
        { char *c7 = arg0 + 0xB0;
        if ((arg0 != (char *)-0xB0) || (c7 = (char *)gl_func_00000000(0x18), (c7 != 0))) {
            gl_func_00000000(c7, arg0, ids[7], 1, ids[7]);
            *(s32 *)(c7 + 0x10) = 0xD;
            *(s32 *)(c7 + 0xC) = GL_C764;
            *(s32 *)(c7 + 0x14) = 0;
        } }
        ids[8] = GL_ID(0xCC94);
        { char *c8 = arg0 + 0xC8;
        if ((arg0 != (char *)-0xC8) || (c8 = (char *)gl_func_00000000(0x18), (c8 != 0))) {
            gl_func_00000000(c8, arg0, ids[8], 1, ids[8]);
            *(s32 *)(c8 + 0xC) = GL_C764;
            *(s32 *)(c8 + 0x14) = 0;
            *(s32 *)(c8 + 0x10) = 0;
        } }
        ids[9] = GL_ID(0xCC98);
        { char *c9 = arg0 + 0xE0;
        if ((arg0 != (char *)-0xE0) || (c9 = (char *)gl_func_00000000(0x18), (c9 != 0))) {
            gl_func_00000000(c9, arg0, ids[9], 1, ids[9]);
            *(s32 *)(c9 + 0xC) = GL_C764;
            *(s32 *)(c9 + 0x14) = 0;
            *(s32 *)(c9 + 0x10) = 0;
        } }
        ids[10] = GL_ID(0xCC9C);
        { char *c10 = arg0 + 0xF8;
        if ((arg0 != (char *)-0xF8) || (c10 = (char *)gl_func_00000000(0x18), (c10 != 0))) {
            gl_func_00000000(c10, arg0, ids[10], 1, ids[10]);
            *(s32 *)(c10 + 0x10) = 0x10C;
            *(s32 *)(c10 + 0xC) = GL_C764;
            *(s32 *)(c10 + 0x14) = 0;
        } }
        ids[11] = GL_ID(0xCCA0);
        { char *c11 = arg0 + 0x110;
        if ((arg0 != (char *)-0x110) || (c11 = (char *)gl_func_00000000(0x18), (c11 != 0))) {
            gl_func_00000000(c11, arg0, ids[11], 1, ids[11]);
            *(s32 *)(c11 + 0x10) = 0x50;
            *(s32 *)(c11 + 0xC) = GL_C764;
            *(s32 *)(c11 + 0x14) = 0;
        } }
        ids[12] = GL_ID(0xCCA4);
        { char *c12 = arg0 + 0x128;
        if ((arg0 != (char *)-0x128) || (c12 = (char *)gl_func_00000000(0x18), (c12 != 0))) {
            gl_func_00000000(c12, arg0, ids[12], 1, ids[12]);
            *(s32 *)(c12 + 0x10) = 0xA0;
            *(s32 *)(c12 + 0xC) = GL_C764;
            *(s32 *)(c12 + 0x14) = 0;
        } }
        ids[13] = GL_ID(0xCCA8);
        { char *c13 = arg0 + 0x140;
        if ((arg0 != (char *)-0x140) || (c13 = (char *)gl_func_00000000(0x18), (c13 != 0))) {
            gl_func_00000000(c13, arg0, ids[13], 1, ids[13]);
            *(s32 *)(c13 + 0x10) = 0xDC;
            *(s32 *)(c13 + 0xC) = GL_C764;
            *(s32 *)(c13 + 0x14) = 0;
        } }
        {
            f32 srcC0[4];
            f32 srcB0[4];
            f32 srcA0[4];
            Quad4 dst40;
            Quad4 dst30;
            Quad4 dst20;
            char *cf = arg0 + 0x158;

            srcC0[1] = 1.0f; srcC0[3] = 1.0f;
            srcA0[0] = 1.0f; srcA0[1] = 1.0f; srcA0[2] = 1.0f; srcA0[3] = 1.0f;
            srcC0[0] = 0.0f;
            srcB0[0] = 0.0f; srcB0[1] = 0.0f; srcB0[2] = 0.0f; srcB0[3] = 0.0f;
            id9C = GL_ID(0xCCAC);
            srcC0[2] = *(f32 *)D_REF(0xC98);

            dst40 = *(Quad4 *)srcC0;
            dst30 = *(Quad4 *)srcB0;
            dst20 = *(Quad4 *)srcA0;

            if ((arg0 != (char *)-0x158) || (cf = (char *)gl_func_00000000(0x24), (cf != 0))) {
                gl_func_00000000(cf, arg0, id9C, 1, id9C);
                *(s32 *)(cf + 0xC) = (s32)D_REF(0xCA34);
                *(s32 *)(cf + 0x20) = 0;
                *(s32 *)(cf + 0x10) = dst40.a;
                *(s32 *)(cf + 0x14) = dst40.b;
                *(s32 *)(cf + 0x18) = dst40.c;
                *(s32 *)(cf + 0x1C) = dst40.d;
            }
        }
        id98 = GL_ID(0xCCB0);
        { char *cz = arg0 + 0x17C;
        if ((arg0 != (char *)-0x17C) || (cz = (char *)gl_func_00000000(0x18), (cz != 0))) {
            gl_func_00000000(cz, arg0, id98, 1, id98);
            *(s32 *)(cz + 0xC) = GL_C764;
            *(s32 *)(cz + 0x14) = 0;
            *(s32 *)(cz + 0x10) = 0;
        } }
    }
    return arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001C54);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0000237C)();
char *gl_func_0000237C(char *arg0, s32 arg1) {
    char *temp_v0;
    char *var_s0;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = (char*)func_00000000((char *)0x2FC), var_s0 = temp_v0, (temp_v0 != 0))) {
        (char*)func_00000000(var_s0, (char*)&D_00000000 + 0xCCB4);
        FW(var_s0, 0x28) = (int)&D_00000000;
        (char*)func_00000000(var_s0 + 0x2C);
        FW(var_s0, 0xC) = (int)((char*)&D_00000000 + 0xCCBC);
        *(f32*)((char*)var_s0 + 0x1DC) = 0.0f;
        *(f32*)((char*)var_s0 + 0x1D4) = 0.0f;
        *(f32*)((char*)var_s0 + 0x1E0) = 0.0f;
        *(f32*)((char*)var_s0 + 0x1D8) = 0.0f;
        FW(var_s0, 0x1C0) = arg1;
        (char*)func_00000000(var_s0, *(s32 *)((char*)&D_00000000 + 0x64));
        (char*)func_00000000(var_s0 + 0x1F4, 0x50019);
        (char*)func_00000000(var_s0 + 0x20C, 0x5001A);
        (char*)func_00000000(var_s0 + 0x224, 0x50010);
        (char*)func_00000000(var_s0 + 0x23C, 0x50011);
        (char*)func_00000000(var_s0 + 0x254, 0x50012);
        (char*)func_00000000(var_s0 + 0x26C, 0x50013);
        (char*)func_00000000(var_s0 + 0x284, 0x50014);
        (char*)func_00000000(var_s0 + 0x29C, 0x50015);
        (char*)func_00000000(var_s0 + 0x2B4, 0x50016);
        (char*)func_00000000(var_s0 + 0x2CC, 0x50017);
        (char*)func_00000000(var_s0 + 0x2E4, 0x50018);
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000237C);
#endif

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

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00002840)();
void gl_func_00002840(char *arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp54;
    f32 sp50;
    f32 sp3C;
    f32 sp38;
    f32 *sp28;
    f32 *temp_a0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f14;
    f32 var_f2;
    char *temp_v0;

    temp_v0 = FW(FW(((*(s32*)((char*)&D_00000000 + 0x134)) + (arg1 * 4)), 0x108), 0x70);
    temp_f0 = (*(f32*)((char*)temp_v0 + 0xBC));
    temp_f16 = (*(f32*)((char*)temp_v0 + 0xA0));
    temp_f2 = (*(f32*)((char*)temp_v0 + 0xDC));
    temp_f18 = (*(f32*)((char*)temp_v0 + 0xA8));
    temp_f12 = (temp_f16 * temp_f0) + (temp_f18 * temp_f2);
    temp_f14 = (temp_f0 * arg2) + (temp_f2 * arg3);
    if ((temp_f12 < temp_f14) && ((temp_f14 - temp_f12) < 4000.0f)) {
        temp_f2_2 = arg2 - temp_f16;
        sp54 = (*(f32*)((char*)temp_v0 + 0xB4));
        temp_f14_2 = arg3 - temp_f18;
        sp3C = temp_f2_2;
        sp50 = (*(f32*)((char*)temp_v0 + 0xD4));
        sp38 = temp_f14_2;
        temp_f0_2 = ((f32(*)())gl_func_00000000)((temp_f2_2 * temp_f2_2) + (temp_f14_2 * temp_f14_2), temp_f14_2);
        var_f2 = temp_f2_2;
        var_f14 = temp_f14_2;
        if (temp_f0_2 != 0.0f) {
            var_f2 /= temp_f0_2;
            var_f14 /= temp_f0_2;
        }
        sp60 = 1.0f;
        temp_a0 = (int)arg0 + 0x2E4;
        sp68 = 0.0f;
        sp6C = 0.0f;
        sp28 = temp_a0;
        sp3C = var_f2;
        sp38 = var_f14;
        sp64 = (*(f32*)((char*)&D_00000000 + 0xCB4));
        (char*)func_00000000(0.0f, var_f14, temp_a0);
        (char*)func_00000000(temp_a0, (f32) (s32) (255.0f * (*(int*)&D_00000000)), &sp60, 0xFF);
        (char*)func_00000000(sp28, (f32) (s32) ((f32) (FW(arg0, 0x164) - 0xC) + (((sp54 * sp3C) + (sp50 * sp38)) * 150.0f)), arg4 - 8, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002840);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000029F8);

#ifdef NON_MATCHING
/* PASS-2 2026-06-22 (big-swing tighten): hand reconstruction from
 * expected/ disasm. Normalized opcode-stream match 23.9% -> 51.2%.
 * Key corrections vs PASS-1 m2c graft:
 *   - int array spA8[4], float array spB8[4]={1,1,1,1}, sp74[4]
 *   - obj->0x10 fields at +0x20/+0x22 are s16 (lh, not lwl/lwr)
 *   - 0xFF color uses f32 global: (s32)(255.0f * *(f32*)&D_00000000), inline
 *     (no CSE local -> distinct lwc1 per site, matches target)
 *   - obj->0x1CC/0x1D0/0x1D4.. compared/used as FLOAT (c.lt.s / c.le.s / div.s)
 *   - single-arg first call gl_func_00000000(p); single reused s1 ptr
 *   - 0x8 / 0x20 tail blocks re-read m1C0 fresh
 * RESIDUAL = pure register-allocation + instruction-scheduling cap (correct
 * logic, divergent IDO coloring/scheduling; target frame -200 vs minimal -168
 * implies extra named locals in original). Permuter not installed (multi-tick
 * infra). Class: documented 1080 regalloc cap.
 * PASS-3 PROBES (2026-07-10, all fuzzy-negative, code reverted; keep for
 * the next serious attempt):
 *  - FRAME/SLOT MAP SOLVED: decl relayout `...sp98; volatile char pad94[4];
 *    sp90; sp8C; volatile char pad84[8]; f32 sp74[4]; volatile char
 *    pad28[0x14];` gives frame -200 EXACT and 16 named slots at exact
 *    target offsets (sp74@0x74, sp98..A4, spB8@0xB8; census-verified).
 *    But objdiff fuzzy DROPS 83.34->83.08 (sp-displacement fixes are
 *    underweighted vs the coloring residual they expose) -- if the reg/
 *    order residual is ever cracked, apply this relayout FIRST.
 *  - build spills its cross-call webs to BOTTOM templocs 0x3C-0x44; the
 *    target instead spills sp8C(x5)/sp90(x4) at their decl homes. volatile
 *    (-0.36) and if(0)&-escape (-0.34) both force the homes but shred
 *    load order/CSE globally = wrong mechanism. Open: the entry-19
 *    "volatile-slot arg-fold" def-in-call-arg form was not tried on the
 *    sp8C=var_v0 def (needs restructure of the var_v0/var_t0 if-chain).
 *  - target stores spA8[0..3] THROUGH the materialized call-arg reg
 *    (sw 0/4/8/12(a2), a2=addiu sp,0xA8 hoisted early) = unrolled-loop
 *    or held-pointer shape; UNREACHABLE from: direct array stores, held
 *    `s32 *pa8` (copy-prop folds), for-loop 0..3 (unroller folds IXA back
 *    to sp-direct), while(0) phantom-def fold-bar. sp-array pointer
 *    stores resist every known fold-bar; likely needs the address to
 *    come from a NON-sp web (e.g. arg-fold via callee?). ~4 operand
 *    words + a2-schedule shift if cracked. */
void gl_func_00002B94(char *arg0) {
    f32 spB8[4];
    s32 spA8[4];
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp90;
    s32 sp8C;
    f32 sp74[4];
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    char *temp_a0;
    char *temp_a1;
    char *var_s1;

    temp_a1 = *(char **)((char *)(arg0) + 0x1F0);
    if (temp_a1 != 0) {
        gl_func_00000000(temp_a1);
        temp_a0 = *(char **)((char *)(arg0) + 0x1F0);
        *(s32 *)((char *)(arg0) + 0x44) = (s32) (*(s32 *)((char *)(arg0) + 0x1C4) - *(s16 *)((char *)(*(char **)((char *)(temp_a0) + 0x10)) + 0x20));
        *(s32 *)((char *)(arg0) + 0x5C) = (s32) (*(s32 *)((char *)(arg0) + 0x1C8) - *(s16 *)((char *)(*(char **)((char *)(temp_a0) + 0x10)) + 0x22));
        spB8[3] = 1.0f;
        spB8[2] = 1.0f;
        spB8[1] = 1.0f;
        spB8[0] = 1.0f;
        spA8[0] = *(s32 *)((char *)(arg0) + 0x194);
        spA8[1] = *(s32 *)((char *)(arg0) + 0x198);
        spA8[2] = *(s32 *)((char *)(arg0) + 0x19C);
        spA8[3] = *(s32 *)((char *)(arg0) + 0x1A0);
        gl_func_00000000(*(char **)((char *)(arg0) + 0x1F0), (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), spA8, 0xFF);
        gl_func_00000000(*(char **)((char *)(arg0) + 0x1F0), *(s32 *)((char *)(arg0) + 0x44), *(s32 *)((char *)(arg0) + 0x5C), 0);
        var_s1 = arg0 + 0x224;
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), spB8, 0xFF);
        gl_func_00000000(var_s1, *(s32 *)((char *)(arg0) + 0x44) + *(s32 *)((char *)(arg0) + 0x74) + *(s32 *)((char *)(arg0) + 0xA4), *(s32 *)((char *)(arg0) + 0x5C) + *(s32 *)((char *)(arg0) + 0x8C) + *(s32 *)((char *)(arg0) + 0xBC), 3);
        var_s1 = arg0 + 0x23C;
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), spB8, 0xFF);
        gl_func_00000000(var_s1, *(s32 *)((char *)(arg0) + 0x44) + *(s32 *)((char *)(arg0) + 0xD4) + *(s32 *)((char *)(arg0) + 0x104), *(s32 *)((char *)(arg0) + 0x5C) + *(s32 *)((char *)(arg0) + 0xEC) + *(s32 *)((char *)(arg0) + 0x11C), 3);
        temp_f12 = *(f32 *)((char *)(arg0) + 0x1E4);
        temp_f2 = *(f32 *)((char *)(arg0) + 0x1EC);
        var_s1 = arg0 + 0x254;
        var_v0 = 2;
        temp_f0 = (f32) *(s32 *)((char *)(arg0) + 0xEC) - (f32) *(s32 *)((char *)(arg0) + 0x8C);
        spA4 = (s32) (temp_f0 * ((*(f32 *)((char *)(arg0) + 0x1D4) - temp_f12) / temp_f2));
        temp_f14 = *(f32 *)((char *)(arg0) + 0x1E8);
        spA0 = (s32) (temp_f0 * ((*(f32 *)((char *)(arg0) + 0x1D8) - temp_f14) / temp_f2));
        sp9C = (s32) (temp_f0 * ((*(f32 *)((char *)(arg0) + 0x1DC) - temp_f12) / temp_f2));
        sp98 = (s32) (temp_f0 * ((*(f32 *)((char *)(arg0) + 0x1E0) - temp_f14) / temp_f2));
        if (*(f32 *)((char *)(arg0) + 0x1D0) < *(f32 *)((char *)(arg0) + 0x1CC)) {
            var_s1 = arg0 + 0x26C;
            var_v0 = -0x10;
        }
        sp8C = var_v0;
        sp90 = -0x13;
        gl_func_00000000(var_s1);
        gl_func_00000000(var_s1, (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), spB8, 0xFF);
        gl_func_00000000(var_s1, (*(s32 *)((char *)(arg0) + 0x44) + *(s32 *)((char *)(arg0) + 0x74) + spA4) - 0x13, *(s32 *)((char *)(arg0) + 0x5C) + *(s32 *)((char *)(arg0) + 0x8C) + spA0 + sp8C, 0);
        temp_v1 = *(s32 *)((char *)(arg0) + 0x1C0);
        var_v0_2 = sp8C;
        var_t0 = sp90;
        var_a0 = 0;
        if (temp_v1 & 2) {
            var_a0 = 1;
            var_v0_2 = -0xE;
            var_s1 = arg0 + 0x284;
            var_t0 = -3;
            if (*(f32 *)((char *)(arg0) + 0x1CC) <= *(f32 *)((char *)(arg0) + 0x1D0)) {
                var_s1 = arg0 + 0x29C;
                var_t0 = -3;
            } else {
                var_v0_2 = 0;
            }
        } else if (temp_v1 & 4) {
            var_a0 = 1;
            var_s1 = arg0 + 0x2B4;
            var_t0 = -3;
            var_v0_2 = 0;
            if (*(f32 *)((char *)(arg0) + 0x1CC) <= *(f32 *)((char *)(arg0) + 0x1D0)) {
                var_s1 = arg0 + 0x2CC;
                var_t0 = -3;
                var_v0_2 = -0xE;
            }
        }
        if (var_a0 != 0) {
            sp8C = var_v0_2;
            sp90 = var_t0;
            gl_func_00000000(var_s1);
            gl_func_00000000(var_s1, (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), spB8, 0xFF);
            gl_func_00000000(var_s1, *(s32 *)((char *)(arg0) + 0x44) + *(s32 *)((char *)(arg0) + 0x74) + sp9C + sp90, *(s32 *)((char *)(arg0) + 0x5C) + *(s32 *)((char *)(arg0) + 0x8C) + sp98 + sp8C, 0);
        }
        var_v0_3 = *(s32 *)((char *)(arg0) + 0x1C0) & 8;
        if (var_v0_3 != 0) {
            var_s1 = arg0 + 0x20C;
            if (*(f32 *)((char *)(arg0) + 0x1D0) < *(f32 *)((char *)(arg0) + 0x1CC)) {
                var_s1 = arg0 + 0x1F4;
                sp74[0] = 1.0f;
                sp74[1] = *(f32 *)((char *)&D_00000000 + 0xCB8);
                sp74[2] = *(f32 *)((char *)&D_00000000 + 0xCBC);
                sp74[3] = 0.0f;
            } else {
                sp74[0] = *(f32 *)((char *)&D_00000000 + 0xCC0);
                sp74[1] = *(f32 *)((char *)&D_00000000 + 0xCC4);
                sp74[2] = 1.0f;
                sp74[3] = 0.0f;
            }
            gl_func_00000000(var_s1);
            *(s32 *)((char *)(arg0) + 0x134) = (s32) (*(s32 *)((char *)(arg0) + 0x44) + *(s32 *)((char *)(arg0) + 0xD4));
            *(s32 *)((char *)(arg0) + 0x14C) = (s32) ((*(s32 *)((char *)(arg0) + 0x5C) + *(s32 *)((char *)(arg0) + 0xEC)) - 0x18);
            gl_func_00000000(var_s1, (s32) (255.0f * *(f32 *)((char *)&D_00000000 + 0)), sp74, 0xFF);
            gl_func_00000000(var_s1, *(s32 *)((char *)(arg0) + 0x134), *(s32 *)((char *)(arg0) + 0x14C), 3);
            var_v0_3 = *(s32 *)((char *)(arg0) + 0x1C0) & 8;
        }
        if (var_v0_3 != 0) {
            gl_func_00000000(arg0, 0, *(s32 *)((char *)(arg0) + 0x1DC), *(s32 *)((char *)(arg0) + 0x1E0), *(s32 *)((char *)(arg0) + 0x17C));
        }
        if (*(s32 *)((char *)(arg0) + 0x1C0) & 0x20) {
            gl_func_00000000(arg0, 0, *(s32 *)((char *)(arg0) + 0x1DC), *(s32 *)((char *)(arg0) + 0x1E0), *(s32 *)((char *)(arg0) + 0x17C) - 0x6E);
            gl_func_00000000(arg0, 1, *(s32 *)((char *)(arg0) + 0x1D4), *(s32 *)((char *)(arg0) + 0x1D8), *(s32 *)((char *)(arg0) + 0x17C));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002B94);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00003138)();
char *gl_func_00003138(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 d255 = 255.0f;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s32 var_s0;
    char *temp_v0;
    char *var_s1;
    char *var_s3;

    var_s3 = arg0;
    if ((arg0 != 0) || (temp_v0 = (char*)func_00000000((char *)0x168), var_s3 = temp_v0, (temp_v0 != 0))) {
        (char*)func_00000000(var_s3, (char*)&D_00000000 + 0xCCD0);
        *(int*)((char*)var_s3 + 0x28) = (int)&D_00000000;
        FW(var_s3, 0xC) = (int)((char*)&D_00000000 + 0xCCD8);
        FW(var_s3, 0x50) = arg3;
        FW(var_s3, 0x54) = arg1;
        FW(var_s3, 0x58) = arg2;
        (char*)func_00000000(var_s3 + 0xF0, 0x50003);
        (char*)func_00000000(var_s3 + 0x108, 0x50004);
        (char*)func_00000000(var_s3 + 0x120, 0x50006);
        (char*)func_00000000(var_s3 + 0x150, 0x50005);
        (char*)func_00000000(var_s3 + 0x138, 0x50021);
        var_s0 = 0;
        var_s1 = var_s3;
        do {
            FW(var_s1, 0x2C) = (char*)func_00000000(0, arg1);
            var_s1 += 4;
            var_s0 += 1;
        } while (var_s0 != 8);
        (char*)func_00000000(var_s3);
        temp_f0 = (f32)255 / d255;
        temp_f2 = 102.0f / d255;
        *(f32*)((char*)var_s3 + 0xCC) = temp_f0;
        *(f32*)((char*)var_s3 + 0xD8) = temp_f0;
        *(f32*)((char*)var_s3 + 0xE0) = temp_f0;
        *(f32*)((char*)var_s3 + 0xE8) = temp_f0;
        temp_f12 = 80.0f / d255;
        *(f32*)((char*)var_s3 + 0xD0) = temp_f2;
        *(f32*)((char*)var_s3 + 0xDC) = temp_f2;
        *(f32*)((char*)var_s3 + 0xD4) = temp_f12;
        *(f32*)((char*)var_s3 + 0xE4) = temp_f12;
    }
    return var_s3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003138);
#endif

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
/* gl_func_000032B0: 77-insn FP color/material setup. The four color channels are
 * normalized at runtime via div.s using FP consts that partly live in the stolen
 * prologue (game_libs_func_00003298 sets f4=100, f6=255, f8=235); the loop walks
 * two distinct sub-pointer arrays a0[0x2C+i*4] and a0[0x28+i*4], zeroes
 * sub2C->0x98 and sub28->0x94, calls a placeholder with two K&R 1.0f args (mfc1
 * a3 + swc1 stack), then writes the 4 channels into sub2C->0x64..0x70. Trailing
 * block zero/0xFF-inits a0 fields. Caps remain (prologue-stolen f4/f6/f8 +
 * caller-set-float K&R call + raw-.word placeholder reloc) so no episode. */
extern int func_00000000();
void gl_func_000032B0(int *a0) {
    float div255 = 255.0f;       /* shared divisor blocks const/const fold -> runtime div.s */
    float r = 100.0f / div255;   /* f22 = f4/f6, f4 stolen from predecessor */
    float g = 235.0f / div255;   /* f24 = f8/255 */
    float b = 250.0f / div255;   /* f26 = 250/255 */
    float al = 0.0f / div255;    /* f28 = 0/255 */
    int i;
    for (i = 0; i < 8; i++) {
        int *sub = *(int**)((char*)a0 + 0x2C + i * 4);
        *(int*)((char*)sub + 0x98) = 0;
        sub = *(int**)((char*)a0 + 0x2C + i * 4);
        func_00000000(sub, 0xA0, 0x5A, 1.0f, 1.0f);
        sub = *(int**)((char*)a0 + 0x2C + i * 4);
        *(float*)((char*)sub + 0x70) = al;
        *(float*)((char*)sub + 0x6C) = b;
        *(float*)((char*)sub + 0x68) = g;
        *(float*)((char*)sub + 0x64) = r;
        *(int*)((char*)(*(int**)((char*)a0 + 0x28 + i * 4)) + 0x94) = 0;
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

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
#ifndef FF
#define FF(p, o) (*(f32 *)((char *)(p) + (o)))
#endif
/* PASS-2 2026-06-22 (big-swing): full float-typed reconstruction of the 8-way
 * state-machine jumptable; FF=f32 fields, FW=int fields per mnemonics.
 * Distinct externs per pool/global ref defeat the &D_00000000 base-pointer
 * CSE hoist (target reloads `lui at` each use). */
extern f32 D_00000000_3430_cc8;
extern f32 D_00000000_3430_cec;
extern f32 D_00000000_3430_cf0;
extern f32 D_00000000_3430_cf4;
extern char D_00000000_3430_cce8;
void gl_func_00003430(char *arg0) {
    f32 var_f2;
    f32 temp;
    s32 t;
    s32 i;
    s32 n;
    char *s0;
    char *v0;
    char *p;

    FW(arg0, 0xEC) = 1;
    var_f2 = D_00000000_3430_cc8;
    i = 0;
    v0 = arg0;
    do {
        s0 = (char *)FW(v0, 0x2C);
        t = FW(s0, 0x94);
        if ((u32)(t - 1) < 8U) {
            switch (t) {
            case 1:
                FF(s0, 0xA8) = FF(s0, 0xA8) + FF(s0, 0xAC);
                temp = FF(s0, 0xA8);
                FW(s0, 0x74) = 0;
                FW(s0, 0x9C) = FW(s0, 0x9C) - 1;
                FF(s0, 0x5C) = FF(s0, 0x5C) + temp;
                FF(s0, 0x44) = FF(s0, 0x44) + FF(s0, 0xA4);
                if (110.0f < FF(s0, 0x5C)) {
                    FF(s0, 0xA8) = -temp;
                }
                t = FW(s0, 0x78);
                if (t < 0xFF) {
                    t += 0x20;
                    FW(s0, 0x78) = t;
                    if (t >= 0x100) {
                        FW(s0, 0x78) = 0xFF;
                    }
                }
                if (FF(s0, 0x88) < 1.0f) {
                    FF(s0, 0x88) = FF(s0, 0x88) + var_f2;
                    FF(s0, 0x8C) = FF(s0, 0x8C) + var_f2;
                } else {
                    FF(s0, 0x88) = 1.0f;
                    FF(s0, 0x8C) = 1.0f;
                }
                if (FW(s0, 0x9C) < 0) {
                    FW(s0, 0x94) = 4;
                    FF(s0, 0xA4) = (100.0f - FF(s0, 0x44)) / 10.625f;
                    FF(s0, 0xA8) = (40.0f - FF(s0, 0x5C)) / 10.625f;
                }
                if (FW(s0, 0x7C) != 0) {
                    FW(arg0, 0xEC) = 0;
                }
                break;
            case 2:
                t = FW(s0, 0x78);
                if (t != 0) {
                    FF(s0, 0x44) = FF(s0, 0x44) + FF(s0, 0xA4);
                    FF(s0, 0x5C) = FF(s0, 0x5C) + FF(s0, 0xA8);
                    t -= 0x20;
                    FW(s0, 0x78) = t;
                    if (t < 0) {
                        FW(s0, 0x78) = 0;
                        FW(s0, 0x94) = 0;
                        p = (char *)FW(*(char **)((char *)&D_00000000 + 0x138), 0x44) + 0x18;
                        *(int *)p = *(int *)p + FW(s0, 0x98);
                    }
                }
                if (FW(s0, 0x7C) != 0) {
                    FW(arg0, 0xEC) = 0;
                }
                break;
            case 3:
                FF(s0, 0xA8) = FF(s0, 0xA8) + FF(s0, 0xAC);
                FW(s0, 0x74) = 0;
                FW(s0, 0x9C) = FW(s0, 0x9C) - 1;
                FF(s0, 0x44) = FF(s0, 0x44) + FF(s0, 0xA4);
                FF(s0, 0x5C) = FF(s0, 0x5C) + FF(s0, 0xA8);
                t = FW(s0, 0x78);
                if (t < 0xFF) {
                    t += 0x20;
                    FW(s0, 0x78) = t;
                    if (t >= 0x100) {
                        FW(s0, 0x78) = 0xFF;
                    }
                }
                if (FW(s0, 0x9C) < 0) {
                    FW(s0, 0x94) = 2;
                    FF(s0, 0xA4) = (200.0f - FF(s0, 0x44)) / 10.625f;
                    FF(s0, 0xA8) = (20.0f - FF(s0, 0x5C)) / 10.625f;
                }
                FW(arg0, 0xEC) = 0;
                break;
            case 4:
                t = FW(s0, 0x78);
                if (t != 0) {
                    FF(s0, 0x44) = FF(s0, 0x44) + FF(s0, 0xA4);
                    FF(s0, 0x5C) = FF(s0, 0x5C) + FF(s0, 0xA8);
                    t -= 0x18;
                    FW(s0, 0x78) = t;
                    if (t < 0) {
                        FW(s0, 0x78) = 0;
                        FW(s0, 0x94) = 0;
                    }
                }
                FW(arg0, 0xEC) = 0;
                break;
            case 5:
                t = FW(s0, 0x9C) - 1;
                if (t < 0) {
                    FW(s0, 0x9C) = t;
                    FW(s0, 0x94) = 6;
                    FW(s0, 0x74) = 0;
                }
                break;
            case 6:
                if (gl_func_00000000(s0, 0xB4) != 0) {
                    FW(s0, 0x94) = 7;
                }
                var_f2 = D_00000000_3430_cec;
                break;
            case 7:
                t = FW(s0, 0x98);
                if (t != 0) {
                    t -= 0x32;
                    FW(s0, 0x98) = t;
                }
                if (t <= 0) {
                    FW(s0, 0x98) = 0;
                    FW(s0, 0x94) = 8;
                    t = 0;
                }
                gl_func_00000000(s0 + 0xB4, &D_00000000_3430_cce8, t);
                t = FW(s0, 0x74) + 0x10;
                FW(s0, 0x74) = t;
                if (t >= 0x100) {
                    FW(s0, 0x74) = 0xFF;
                }
                gl_func_00000000(s0, 0x104);
                var_f2 = D_00000000_3430_cf0;
                break;
            case 8:
                t = FW(s0, 0x74) + 0x10;
                FW(s0, 0x74) = t;
                if (t >= 0x100) {
                    FW(s0, 0x74) = 0xFF;
                }
                t = FW(s0, 0x78) - 8;
                FW(s0, 0x78) = t;
                if (t < 0) {
                    FW(s0, 0x78) = 0;
                }
                if (gl_func_00000000(s0, 0x104) != 0) {
                    FW(s0, 0x94) = 0;
                }
                var_f2 = D_00000000_3430_cf4;
                break;
            }
        }
        i += 4;
        v0 += 4;
    } while (i != 0x20);
    n = 0;
    v0 = arg0;
    do {
        t = FW(v0, 0x8C);
        n += 4;
        if (t < 0x80) {
            t += 1;
            FW(v0, 0x8C) = t;
            if (t < 0x70) {
                t = FW(v0, 0x9C);
                if (t < 0xFF) {
                    t += 0x10;
                    FW(v0, 0x9C) = t;
                    if (t >= 0x100) {
                        FW(v0, 0x9C) = 0xFF;
                    }
                }
            } else {
                t = FW(v0, 0x9C);
                if (t > 0) {
                    t -= 0x10;
                    FW(v0, 0x9C) = t;
                    if (t < 0) {
                        FW(v0, 0x9C) = 0;
                        FW(v0, 0xBC) = 0x64;
                    }
                }
            }
        }
        if (FW(arg0, 0x88) != 0) {
            FW(v0, 0xBC) = FW(v0, 0xBC) - 2;
        }
        v0 += 4;
    } while (n != 0x10);
    t = FW(arg0, 0x88);
    if (t > 0) {
        FW(arg0, 0x88) = t - 2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003430);
#endif

/* gl_func_000038F4 — EXACT MATCH 138/138 words (2026-07-03, agent-e w5).
 * Was 118/138. Fix stack, in order:
 * 1. RELOC EXTERNS: the two format strings are baked USO data addrs. Target
 *    words lui a1,0x1 / addiu a1,CCEC compose to 0x0000CCEC (NOT 0x1CCEC —
 *    prior extern names D_0001CCEC/F8 mis-derived the value by ignoring lo16
 *    sign). extern char D_0000CCEC / D_0000CCF8 + undefined_syms_auto.txt
 *    entries `D_0000CCEC = 0x0000CCEC; D_0000CCF8 = 0x0000CCF8;` make ld bake
 *    the exact 4 words (verified by link simulation of HI16/LO16).
 * 2. NAMED idx LOCAL: `idx = (FW(arg0,0x80)+var_s4)&3; s0v = &((int*)arg0)[idx]`
 *    instead of one nested expression — named int colors to v0 and reuses it
 *    (addu v0/andi v0), snapping the ENTIRE downstream t-reg cascade
 *    (13 words: t4/t6/t9 -> t2/t4/t6, t0 -> t9, slt operand).
 * 3. NAMED-SLOT BUDGET (frame): every named scalar reserves a decl-order home
 *    even when colored (dead space). Target = 5 dead words ABOVE spE4 +
 *    9-word temp area BELOW sp64; we had 11 named scalars below. Fixed by
 *    (a) moving 5 scalars (temp_s2,temp_s3,temp_s7,var_s4,var_s2) ABOVE the
 *    buffer decls, (b) merging the two same-register disjoint pairs into one
 *    name each: idx+temp_v0 -> tv0 (both v0), var_s0+temp_s0 -> s0v (both s0)
 *    — one name = ONE named slot; disjoint ranges keep their per-range color.
 *    Frame 0x170->0x168, buffers 0x74/0xF4 -> 0x64/0xE4, all byte-exact.
 * 4. ARRAY-IXA for the final addu operand order: `(char*)&((int*)arg0)[tv0]`
 *    emits addu s0,s1,t1 (base-first); `arg0 + tv0*4` emits addu s0,t1,s1
 *    and IDO canonicalizes the source-level operand swap back.
 * REQUIRES (report to lander): undefined_syms_auto.txt additions
 *   D_0000CCEC = 0x0000CCEC;
 *   D_0000CCF8 = 0x0000CCF8;
 */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef int (*GP_000038F4)();
#ifndef FF
#define FF(p, o) (*(f32 *)((char *)(p) + (o)))
#endif
extern char D_0000CCEC;  /* baked USO data addr 0xCCEC (lui 1/addiu CCEC); defined in undefined_syms_auto.txt */
extern char D_0000CCF8;  /* baked USO data addr 0xCCF8 */
void gl_func_000038F4(char *arg0) {
    int temp_s2;
    int temp_s3;
    char *temp_s7;
    s32 var_s4;
    char *var_s2;
    char spE4[112];
    char sp64[128];
    int *temp_a3;
    char *temp_v1;
    int tv0;
    char *s0v;

    s0v = 0;
    var_s2 = arg0;
    do {
        temp_v1 = (char *)FW(var_s2, 0x2C);
        if (FW(temp_v1, 0x94) != 0) {
            tv0 = FW(temp_v1, 0x28);
            ((GP_000038F4)FW(tv0, 0x1C))(*(s16*)((char *)tv0 + 0x18) + temp_v1);
        }
        s0v += 4;
        var_s2 += 4;
    } while (s0v != (char *)0x20);
    func_00000000(FW(arg0, 0x50));
    var_s4 = 0;
    temp_s7 = arg0 + 0xCC;
    if (FW(arg0, 0x84) > 0) {
        do {
            tv0 = (FW(arg0, 0x80) + var_s4) & 3;
            s0v = (char *)&((int *)arg0)[tv0];
            temp_a3 = (int *)FW(s0v, 0x6C);
            if (temp_a3 != (int *)-1) {
                func_00000000(spE4, &D_0000CCEC, FW(s0v, 0x5C), temp_a3);
                func_00000000(sp64, &D_0000CCF8, FW(s0v, 0x6C));
                temp_s2 = func_00000000(FW(arg0, 0x50), FW(s0v, 0xAC), spE4);
                temp_s3 = func_00000000(FW(arg0, 0x50), FW(s0v, 0x5C)) + temp_s2;
                func_00000000(FW(arg0, 0x50), (s32) (*(f32 *)&D_00000000 * (f32) FW(s0v, 0x9C)), temp_s7, 0xFF);
                func_00000000(FW(arg0, 0x50), temp_s2, FW(s0v, 0xBC), FW(s0v, 0x5C));
                func_00000000(FW(arg0, 0x50), (s32) (*(f32 *)&D_00000000 * (f32) FW(s0v, 0x9C)), arg0 + 0xDC, 0xFF);
                func_00000000(FW(arg0, 0x50), temp_s3, FW(s0v, 0xBC), sp64);
            } else {
                func_00000000(FW(arg0, 0x50), (s32) (*(f32 *)&D_00000000 * (f32) FW(s0v, 0x9C)), temp_s7, 0xFF);
                func_00000000(FW(arg0, 0x50), func_00000000(FW(arg0, 0x50), FW(s0v, 0xAC), FW(s0v, 0x5C)), FW(s0v, 0xBC), FW(s0v, 0x5C));
            }
            var_s4 += 1;
        } while (var_s4 < FW(arg0, 0x84));
    }
}

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
/* gl_func_00003B1C - free-slot allocator + initializer (0xF0, 60 insns).
 * 53.58 -> 71.5% (near-miss, structural rewrite). Scans 8 table entries at
 * v1+0x2C for a slot whose 0x94 state == 0, claims it (state=5), fills fields,
 * runs two absolute-0 init callbacks, returns the slot. Three fixes landed the
 * structure/promote:
 *   (1) primary init takes TWO float args (1.0f, 1.0f) -> arg4 in $a3 (mfc1),
 *       arg5 on stack (swc1) — NOT a single K&R-promoted double. Typed 5-arg
 *       absolute-0 alias gl_func_00000000_i3ff(int,int,int,float,float). This
 *       fixes the cvt.d.s/sdc1 asymmetry (the vein) — frame now -40 (matches),
 *       loop induction (off=v0/table=v1) matches, beqz-a3 if/else matches.
 *   (2) loop sentinel is 32 (off != 32, 8 entries), not 0x10000.
 *   (3) the a3 flag is an explicit if/else (duplicated 0x94=5 store) with slot
 *       homed to $s0 in the beqz delay, not a ?: select.
 * TWO residual caps prevent EXACT: (a) IDO colors `slot` into $s0 for the whole
 * loop; target keeps it in $a0 during scan and copies `move s0,a0` at the found
 * point (a per-fn live-range-split coloring choice; the `o=slot` split-var was
 * coalesced away). (b) the 2nd init's magic 0xCD00 is emitted by the target as
 * lui 0x1 + addiu -13056 = the %hi/%lo of an absolute 0xCD00 USO symbol baked
 * into the raw .word — IDO loads a plain 0xCD00 int as a single `ori`
 * (confirmed 4 literal forms), and a symbol ref would be reloc-placeholder
 * bytes, so the baked address can't be reproduced literally. All callees jal 0
 * (landable). */
extern void *gl_func_00000000_i3ff(int, int, int, float, float);
#ifdef NON_MATCHING
void *gl_func_00003B1C(char *a0, int a1, int a2, int a3) {
    int off = 0;
    char *v1 = a0;
    char *slot;
    do {
        slot = *(char**)(v1 + 0x2C);
        off += 4;
        if (*(int*)(slot + 0x94) == 0) {
            if (a3 != 0) {
                *(int*)(slot + 0x94) = 5;
                *(int*)(slot + 0x9C) = 32;
            } else {
                *(int*)(slot + 0x94) = 5;
                *(int*)(slot + 0x9C) = 0;
            }
            gl_func_00000000_i3ff(slot, 161, a2 + 90, 1.0f, 1.0f);
            *(int*)(slot + 0x78) = 255;
            *(int*)(slot + 0xA0) = 0;
            *(int*)(slot + 0x98) = a1;
            *(int*)(slot + 0x80) = 0;
            *(int*)(slot + 0x84) = -18;
            *(float*)(slot + 0xA8) = 0.0f;
            *(int*)(slot + 0xB0) = *(int*)(a0 + 0x54);
            gl_func_00000000(slot + 0xB4, 0xCD00);
            return slot;
        }
        v1 += 4;
    } while (off != 32);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003B1C);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00003C0C)();
char *gl_func_00003C0C(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_f0;
    s32 var_v0;
    char *temp_s1;
    char *temp_s1_2;
    char *temp_v0;
    char *var_s0;

    var_s0 = arg0;
    var_v0 = 0;
loop_1:
    temp_s1 = FW(var_s0, 0x2C);
    var_v0 += 4;
    if (FW(temp_s1, 0x94) == 0) {
        ((GP_00003C0C)gl_func_00000000)(temp_s1, 0xA0, (int)arg2 + 0x5A, 0x3F800000, 1.0f);
        FW(FW(var_s0, 0x2C), 0xA0) = 0;
        FW(FW(var_s0, 0x2C), 0x7C) = 1;
        temp_v0 = FW((*(char**)((char*)&D_00000000 + 0x138)), 0x44);
        FW(temp_v0, 0x14) = (s32) (FW(temp_v0, 0x14) + (int)arg1);
        if (arg3 != 0) {
            temp_f0 = (*(s32*)((char*)&D_00000000 + 0xCF8));
            FW(FW(var_s0, 0x2C), 0x94) = 3;
            FW(FW(var_s0, 0x2C), 0x9C) = 0xE;
            ((GP_00003C0C)gl_func_00000000)(FW(var_s0, 0x2C), temp_f0, temp_f0);
            FW(FW(var_s0, 0x2C), 0x78) = 0;
        } else {
            FW(FW(var_s0, 0x2C), 0x94) = 3;
            FW(FW(var_s0, 0x2C), 0x9C) = 0;
            FW(FW(var_s0, 0x2C), 0x78) = 0xFF;
        }
        FW(FW(var_s0, 0x2C), 0x98) = arg1;
        *(f32*)((char*)FW(var_s0, 0x2C) + 0xA4) = (-2.0f - (((f32(*)())gl_func_00000000)() * 2.0f));
        *(f32*)((char*)FW(var_s0, 0x2C) + 0xA8) = -3.0f;
        *(f32*)((char*)FW(var_s0, 0x2C) + 0xAC) = 0.5f;
        FW(FW(var_s0, 0x2C), 0x80) = 0;
        FW(FW(var_s0, 0x2C), 0x84) = -0x12;
        FW(FW(var_s0, 0x2C), 0xB0) = (s32) FW(arg0, 0x54);
        temp_s1_2 = FW(var_s0, 0x2C);
        ((GP_00003C0C)gl_func_00000000)(temp_s1_2 + 0xB4, 0xCD04, FW(temp_s1_2, 0x98));
        return FW(var_s0, 0x2C);
    }
    var_s0 += 4;
    if (var_v0 == 0x20) {
        return 0;
    }
    goto loop_1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003C0C);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_00003DB8 - free-slot allocator variant (same family as 3B1C/3C0C).
 * Reload-per-access shape (slot is NOT homed to $s0 — reloaded *(v1+0x2C) each
 * field write; v1 spilled across calls). cvt.d.s asymmetry fixed via the same
 * 5-arg two-float alias gl_func_00000000_i3ff(slot,220,120,1.0f,1.0f) — arg4 in
 * $a3 (mfc1), arg5 on stack (swc1), no double-promote. Removed the m2c sp20
 * spill artifacts (IDO spills v1 itself). Residual cap (blocks EXACT): the 2nd
 * init's 0xCD08 magic is a baked absolute USO symbol (target lui 0x1 + addiu
 * -13048); IDO loads a plain 0xCD08 int as a single ori, and a symbol ref would
 * be reloc-placeholder bytes — not literally reproducible (see 3B1C note). Plus
 * a 1-insn base-materialization scheduling diff on the arg1>=10 decrement. */
char *gl_func_00003DB8(char *arg0, s32 arg1, int arg2, s32 arg3) {
    s32 var_v0;
    char *temp_a0;
    char *temp_v0;
    char *var_v1;

    var_v0 = 0;
    var_v1 = arg0;
    do {
    temp_a0 = FW(var_v1, 0x2C);
    var_v0 += 4;
    if (FW(temp_a0, 0x94) == 0) {
        if (arg3 != 0) {
            FW(temp_a0, 0x94) = 1;
            FW(FW(var_v1, 0x2C), 0x9C) = 0x10;
            FW(FW(var_v1, 0x2C), 0x78) = 0;
        } else {
            FW(temp_a0, 0x94) = 1;
            FW(FW(var_v1, 0x2C), 0x9C) = 0;
            FW(FW(var_v1, 0x2C), 0x78) = 0xFF;
        }
        gl_func_00000000_i3ff(FW(var_v1, 0x2C), 220, 120, 1.0f, 1.0f);
        FW(FW(var_v1, 0x2C), 0x98) = 0;
        FW(FW(var_v1, 0x2C), 0xA0) = (char *) ((int)arg0 + 0xF0);
        *(f32*)((char*)FW(var_v1, 0x2C) + 0xA4) = 0.0f;
        *(f32*)((char*)FW(var_v1, 0x2C) + 0xA8) = 0.0f;
        *(f32*)((char*)FW(var_v1, 0x2C) + 0xAC) = 0.0f;
        FW(FW(var_v1, 0x2C), 0x80) = 0;
        if (arg1 >= 0xA) {
            temp_v0 = FW(var_v1, 0x2C) + 0x80;
            *(s32 *)temp_v0 = *(s32 *)temp_v0 - 6;
        }
        FW(FW(var_v1, 0x2C), 0x84) = 8;
        FW(FW(var_v1, 0x2C), 0xB0) = (s32) FW(arg0, 0x58);
        gl_func_00000000(FW(var_v1, 0x2C) + 0xB4, 0xCD08, arg1, arg0);
        return FW(var_v1, 0x2C);
    }
    var_v1 += 4;
    } while (var_v0 != 0x20);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003DB8);
#endif

void game_libs_func_00003F08(int *a0, int a1, int a2) {
    int diff;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x5C) = a1;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x6C) = a2;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x9C) = 0;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0x8C) = 0;
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0xBC) = 200;
    diff = *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0xBC) - a0[((a0[0x7C / 4] - 1) & 3) + 0x2F];
    if (diff < 15) {
        *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0xBC) = a0[((a0[0x7C / 4] - 1) & 3) + 0x2F] + 16;
    }
    *(int *)((char *)a0 + a0[0x7C / 4] * 4 + 0xAC) = 160;
    a0[0x88 / 4] += 16;
    a0[0x7C / 4] = (a0[0x7C / 4] + 1) & 3;
    if (a0[0x80 / 4] == a0[0x7C / 4]) {
        a0[0x80 / 4] = (a0[0x80 / 4] + 1) & 3;
    }
    if (a0[0x84 / 4] < 4) {
        a0[0x84 / 4] = a0[0x84 / 4] + 1;
    }
}

/* game_libs_func_00003FF8: clamp four ring-slot fields (+0x8C..+0x98) to a floor of 112.
 * VOID return is load-bearing: as int*-returning, the return-value LR claims $v0 (3-LR
 * coloring p=v1/R=v0 + trailing move v0,v1 — unflippable, every barrier/decl lever floored);
 * as void, the copy candidate p itself colors $v0 first-appearance and the jr delay is a nop.
 * The a0=0 kill after block 1 keeps p as a real second web (block 1 via a0, blocks 2-4 via p). */
void game_libs_func_00003FF8(int *a0) {
    int *p;
    p = a0;
    if (a0[0x8C / 4] < 112) a0[0x8C / 4] = 112;
    a0 = 0;
    if (p[0x90 / 4] < 112) p[0x90 / 4] = 112;
    if (p[0x94 / 4] < 112) p[0x94 / 4] = 112;
    if (p[0x98 / 4] < 112) p[0x98 / 4] = 112;
}

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
/* game_libs_func_000040EC BOUNDARY-CORRECTED 2026-06-10 (the 3ECDC
 * class): the 0x18 symbol was TWO misattributed inter-fn pad nops + a
 * true 4-insn fn. Split into the _pad sidecar and
 * game_libs_func_000040F4 = `return 1 << (a0 + 4);` -- BYTE-EXACT
 * standalone (4/4, 0 diffs) but mid-file land-blocked (catch-all unit);
 * relayout queue (10 ready bodies). */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_000040EC_pad.s")
int game_libs_func_000040F4(int a0) {
    return 1 << (a0 + 4);
}

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

// gl_func_00004244 — m2c DECODE (28.62% NM, no episode). LARGEST non-jumptable lift (2479w); game_libs control-flow via scripts/decomp-uso-cf.py.
/* gl_func_00004244 — BEST VERIFIED STATE 2363/2479 words (95.3% positional,
 * byte-level vs own .s, 2026-07-03 agent-e w5). NOT exact; deliverable is this
 * best state + the corrected residual map below. Source below is byte-identical
 * to the in-tree NM wrap (no change improved it this session).
 *
 * RESIDUAL MAP — CORRECTION TO THE DOCUMENTED 66-WORD COUNT: the true
 * positional word residual vs the fn's own .s is 116, not 66. agent-y's
 * "reloc-filtered word LCS" EXCLUDED 50 real mismatch words because they carry
 * HI16 relocs — but they are ORDER swaps of adjacent lui pairs, which mismatch
 * positionally in the linked ROM. Full 116 = 4 classes:
 *
 * 1. [58w, 29 sw/lw pairs] CLASS C spill-home sharing: target spills each
 *    unit's alloc-ptr to ONE gettemp slot 0x38(sp) (+unit1 at its named 0x8C);
 *    any C spelling gives N names -> N slots / 1 name -> s3 promotion /
 *    volatile-or-addressed -> extra loads-stores. RE-VERIFIED this session:
 *    (a) per-unit BLOCK-SCOPED `char *va` (NEW axis, not in agent-y's sweep):
 *        NO overlay — each scoped candidate got its own gettemp slot
 *        0x3C..0xB8 ascending, frame grew 0x748->0x7C8. Rule 1 holds for
 *        scoped names too.
 *    (b) single fn-scope name: reconfirmed s3 promotion (2449 insns, -30).
 *    (c) `if(0){func(&va);}` address-take: shares ONE slot AND it is exactly
 *        0x38 with va declared last (slot placement IS reachable) but
 *        addressed-residency adds ~96 insns (2575) — dead stores at the
 *        pre-if def + post-call reloads. CONFIRMED CAP.
 * 2. [50w, 25 lui pairs] LUI-ORDER — RESOLVED 2026-07-15 agent-h via the
 *    SAME-LINE JOIN lever (as1 debug-line tie-break, the 3D68C crack):
 *    joining the unit's `uN_f.v = *(s32*)cfxx;` and `uN_a.z = *(f32*)0dxx;`
 *    statements onto ONE source line lets as1 cross-schedule the two lui's
 *    (line-number tie no longer forces statement order). Join ORDER is
 *    shape-dependent: units whose f.v line is PRECEDED by another float
 *    D-load (u5,7,9,11,13,15,16,17,20,21,22,23,25,26,27,28,29,31: type A)
 *    join in original order `f.v; a.z`; units without one (u6,8,10,12,14,
 *    18,19: type B) join REVERSED `a.z; f.v`. All 25 pairs now byte-exact.
 *    Word residual 116 -> 66; fn now AT its documented ceiling 2413/2479
 *    (97.3%) + the 58w class-C + 8w no-handle below.
 * 3. [6w] prologue as1 schedule (move s0,a0 hoisted above saves, sdc1 $f20
 *    in bnez delay) — no-handle (documented).
 * 4. [2w] li at,-8 vs addiu s2,sp,84 hoist order — no-handle (documented).
 *
 * The A-win lever of this session (decl-order named-home moves, cracked
 * 7FF4/38F4/85B0) does NOT apply here: 4244's 58w class is gettemp-region
 * sharing across 29 distinct webs, not a named-home position issue. */
#ifdef NON_MATCHING
/* PASS-O 2026-06-11 (578B4-ladder from 53.60 -> 99.76, insns 2479 exact,
 * 96.5% words byte-exact): 32 light-record units rewritten as per-unit
 * V4/F1 structs w/ aggregate copies (beats const-forwarding/DSE);
 * &D_00000000 depooled into per-offset aliases (kills HI16-pool s-reg);
 * per-unit cd58 aliases break the 31-use constant LR (s-reg cascade
 * snaps: var_s0->s0, &sp78->s1@120, &sp54->s2@84); ptr-name pairing
 * (14 names) + decl layout + 2 pads = frame 1864 exact.
 * RESIDUE CHARACTERIZED (agent-y 2026-06-15, reloc-filtered word LCS
 * 2417/2479, positional 2413; the "~87" was a fuzzy artifact, true 66
 * non-reloc words). ZERO logic/structural errors; all 66 = 3 caps:
 *   C (58w, 29 sw/lw pairs): per-unit var_a0 spill home — target shares
 *     ONE temploc 0x38(sp) (anonymous spilltemp, rule-6 region sharing);
 *     we get distinct named-M-class homes 0xC0..0x90 (rule-1, no repack).
 *     NO-CLEAN-HANDLE: distinct names=distinct slots; single name=COLORS
 *     to a new s-reg (spill vanishes, -30 insns); volatile=shares slot
 *     but reloads every use (+insns). All verified in-tree + 2-unit mini
 *     + -zdbug:6. See docs/IDO_CODEGEN.md "4244 ladder levers".
 *   A (6w): prologue as1 schedule — target hoists move s0,a0 above saves,
 *     fills bnez delay with sdc1 $f20. No-handle.
 *   B (2w): li at,-8 (sentinel) vs addiu s2,sp,84 (&sp54 hoist) order.
 *     No-handle (sp54 is loop-invariant; source position doesn't move it).
 * At byte-exact ceiling under no-instruction-forcing policy; leave NM. */
extern int D_00000000_cd58_u1;
extern int D_00000000_cd58_u2;
extern int D_00000000_cd58_u3;
extern int D_00000000_cd58_u4;
extern int D_00000000_cd58_u5;
extern int D_00000000_cd58_u6;
extern int D_00000000_cd58_u7;
extern int D_00000000_cd58_u8;
extern int D_00000000_cd58_u9;
extern int D_00000000_cd58_u10;
extern int D_00000000_cd58_u11;
extern int D_00000000_cd58_u12;
extern int D_00000000_cd58_u13;
extern int D_00000000_cd58_u14;
extern int D_00000000_cd58_u15;
extern int D_00000000_cd58_u16;
extern int D_00000000_cd58_u17;
extern int D_00000000_cd58_u18;
extern int D_00000000_cd58_u19;
extern int D_00000000_cd58_u20;
extern int D_00000000_cd58_u21;
extern int D_00000000_cd58_u22;
extern int D_00000000_cd58_u23;
extern int D_00000000_cd58_u24;
extern int D_00000000_cd58_u25;
extern int D_00000000_cd58_u26;
extern int D_00000000_cd58_u27;
extern int D_00000000_cd58_u28;
extern int D_00000000_cd58_u29;
extern int D_00000000_cd58_u30;
extern int D_00000000_cd58_u31;
extern int D_00000000_cd58_u32;
extern int D_00000000_0d0c;
extern int D_00000000_0d10;
extern int D_00000000_0d14;
extern int D_00000000_0d18;
extern int D_00000000_0d1c;
extern int D_00000000_0d20;
extern int D_00000000_0d24;
extern int D_00000000_0d28;
extern int D_00000000_0d2c;
extern int D_00000000_0d30;
extern int D_00000000_0d34;
extern int D_00000000_0d38;
extern int D_00000000_0d3c;
extern int D_00000000_0d40;
extern int D_00000000_0d44;
extern int D_00000000_0d48;
extern int D_00000000_0d4c;
extern int D_00000000_0d50;
extern int D_00000000_0d54;
extern int D_00000000_0d58;
extern int D_00000000_0d5c;
extern int D_00000000_0d60;
extern int D_00000000_0d64;
extern int D_00000000_0d68;
extern int D_00000000_0d6c;
extern int D_00000000_0d70;
extern int D_00000000_0d74;
extern int D_00000000_0d78;
extern int D_00000000_0d7c;
extern int D_00000000_0d80;
extern int D_00000000_0d84;
extern int D_00000000_0d88;
extern int D_00000000_0d8c;
extern int D_00000000_0d90;
extern int D_00000000_0d94;
extern int D_00000000_0d9c;
extern int D_00000000_0da0;
extern int D_00000000_0da4;
extern int D_00000000_0da8;
extern int D_00000000_0dac;
extern int D_00000000_0db0;
extern int D_00000000_0db4;
extern int D_00000000_0db8;
extern int D_00000000_0dbc;
extern int D_00000000_0dc0;
extern int D_00000000_0dc4;
extern int D_00000000_0dc8;
extern int D_00000000_0dcc;
extern int D_00000000_0dd0;
extern int D_00000000_0dd4;
extern int D_00000000_0ddc;
extern int D_00000000_0de0;
extern int D_00000000_0de4;
extern int D_00000000_cf80;
extern int D_00000000_cf90;
extern int D_00000000_cf94;
extern int D_00000000_cf98;
extern int D_00000000_cf9c;
extern int D_00000000_cfa0;
extern int D_00000000_cfa4;
extern int D_00000000_cfa8;
extern int D_00000000_cfac;
extern int D_00000000_cfb0;
extern int D_00000000_cfb4;
extern int D_00000000_cfb8;
extern int D_00000000_cfbc;
extern int D_00000000_cfc0;
extern int D_00000000_cfc4;
extern int D_00000000_cfc8;
extern int D_00000000_cfcc;
extern int D_00000000_cfd0;
extern int D_00000000_cfd4;
extern int D_00000000_cfd8;
extern int D_00000000_cfdc;
extern int D_00000000_cfe0;
extern int D_00000000_cfe4;
extern int D_00000000_cfe8;
extern int D_00000000_cfec;
extern int D_00000000_cff0;
extern int D_00000000_cff4;
extern int D_00000000_cff8;
extern int D_00000000_cffc;
extern int D_00000000_d000;
extern int D_00000000_d004;
extern int D_00000000_d008;
extern int D_00000000_d00c;
typedef struct { f32 x, y, z, w; } GlV4_4244;
typedef struct { s32 v; } GlF1_4244;
/* 9916-byte fully-unrolled initializer (32 units, zero backward branches).
 * NM 99.762%, residual = CONFIRMED CAP, no logic/decode error remains.
 * DO NOT re-grind names/decl-order/pads — see docs/IDO_CODEGEN.md
 * "4244 ladder levers" (agent-y 2026-06-15, full characterization).
 * Residual re-verified independently 2026-06-17 (116 insn diffs, identical
 * picture): 58 = CLASS C spill-home sharing (target reuses ONE temploc
 * sw/lw a0,0x38(sp) for every unit's alloc-ptr spill; any C spelling makes
 * it a NAMED M-class home — uopt never repacks named homes, rule 1; the
 * only C forms that share a slot either drop the spill entirely or force
 * volatile reloads); 50 = lui-order schedule swap; 6 = prologue or-first.
 * Canonical "spilltemps region-sharing unreproduced" cap. */
void *gl_func_00004244(char *arg0) {
    GlV4_4244 u1_a;
    GlV4_4244 u1_b;
    GlV4_4244 u1_c;
    GlF1_4244 u1_f;
    GlV4_4244 u2_a;
    GlV4_4244 u2_b;
    GlV4_4244 u2_c;
    GlF1_4244 u2_f;
    GlV4_4244 u3_a;
    GlV4_4244 u3_b;
    GlV4_4244 u3_c;
    GlF1_4244 u3_f;
    GlV4_4244 u4_a;
    GlV4_4244 u4_b;
    GlV4_4244 u4_c;
    GlF1_4244 u4_f;
    GlV4_4244 u5_a;
    GlV4_4244 u5_b;
    GlV4_4244 u5_c;
    GlF1_4244 u5_f;
    GlV4_4244 u6_a;
    GlV4_4244 u6_b;
    GlV4_4244 u6_c;
    GlF1_4244 u6_f;
    GlV4_4244 u7_a;
    GlV4_4244 u7_b;
    GlV4_4244 u7_c;
    GlF1_4244 u7_f;
    GlV4_4244 u8_a;
    GlV4_4244 u8_b;
    GlV4_4244 u8_c;
    GlF1_4244 u8_f;
    GlV4_4244 u9_a;
    GlV4_4244 u9_b;
    GlV4_4244 u9_c;
    GlF1_4244 u9_f;
    GlV4_4244 u10_a;
    GlV4_4244 u10_b;
    GlV4_4244 u10_c;
    GlF1_4244 u10_f;
    GlV4_4244 u11_a;
    GlV4_4244 u11_b;
    GlV4_4244 u11_c;
    GlF1_4244 u11_f;
    GlV4_4244 u12_a;
    GlV4_4244 u12_b;
    GlV4_4244 u12_c;
    GlF1_4244 u12_f;
    GlV4_4244 u13_a;
    GlV4_4244 u13_b;
    GlV4_4244 u13_c;
    GlF1_4244 u13_f;
    GlV4_4244 u14_a;
    GlV4_4244 u14_b;
    GlV4_4244 u14_c;
    GlF1_4244 u14_f;
    GlV4_4244 u15_a;
    GlV4_4244 u15_b;
    GlV4_4244 u15_c;
    GlF1_4244 u15_f;
    GlV4_4244 u16_a;
    GlV4_4244 u16_b;
    GlV4_4244 u16_c;
    GlF1_4244 u16_f;
    GlV4_4244 u17_a;
    GlV4_4244 u17_b;
    GlV4_4244 u17_c;
    GlF1_4244 u17_f;
    GlV4_4244 u18_a;
    GlV4_4244 u18_b;
    GlV4_4244 u18_c;
    GlF1_4244 u18_f;
    GlV4_4244 u19_a;
    GlV4_4244 u19_b;
    GlV4_4244 u19_c;
    GlF1_4244 u19_f;
    GlV4_4244 u20_a;
    GlV4_4244 u20_b;
    GlV4_4244 u20_c;
    GlF1_4244 u20_f;
    GlV4_4244 u21_a;
    GlV4_4244 u21_b;
    GlV4_4244 u21_c;
    GlF1_4244 u21_f;
    GlV4_4244 u22_a;
    GlV4_4244 u22_b;
    GlV4_4244 u22_c;
    GlF1_4244 u22_f;
    GlV4_4244 u23_a;
    GlV4_4244 u23_b;
    GlV4_4244 u23_c;
    GlF1_4244 u23_f;
    GlV4_4244 u24_a;
    GlV4_4244 u24_b;
    GlV4_4244 u24_c;
    GlF1_4244 u24_f;
    GlV4_4244 u25_a;
    GlV4_4244 u25_b;
    GlV4_4244 u25_c;
    GlF1_4244 u25_f;
    GlV4_4244 u26_a;
    GlV4_4244 u26_b;
    GlV4_4244 u26_c;
    GlF1_4244 u26_f;
    GlV4_4244 u27_a;
    GlV4_4244 u27_b;
    GlV4_4244 u27_c;
    GlF1_4244 u27_f;
    GlV4_4244 u28_a;
    GlV4_4244 u28_b;
    GlV4_4244 u28_c;
    GlF1_4244 u28_f;
    GlV4_4244 u29_a;
    GlV4_4244 u29_b;
    GlV4_4244 u29_c;
    GlF1_4244 u29_f;
    GlV4_4244 u30_a;
    GlV4_4244 u30_b;
    GlV4_4244 u30_c;
    GlF1_4244 u30_f;
    GlV4_4244 u31_a;
    GlV4_4244 u31_b;
    GlV4_4244 u31_c;
    GlF1_4244 u31_f;
    GlV4_4244 u32_a;
    GlV4_4244 u32_b;
    GlV4_4244 u32_c;
    GlF1_4244 u32_f;
    volatile s32 pad_4244_a;
    char *var_a0_4;
    char *var_a0_6;
    char *var_a0_8;
    char *var_a0_10;
    char *var_a0_12;
    char *var_a0_14;
    char *var_a0_16;
    char *var_a0_18;
    char *var_a0_20;
    char *var_a0_22;
    char *var_a0_24;
    char *var_a0_26;
    char *var_a0_30;
    char *var_a0;
    volatile s32 pad_4244_b;
    GlV4_4244 sp78;
    GlV4_4244 sp68;
    GlV4_4244 sp58;
    GlF1_4244 sp54;
    f32 temp_f0;
    f32 temp_f0_2;
    char *temp_v0;
    char *temp_v0_2;
    char *var_s0;
    char *var_v1;
    char *var_a0_2;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = func_00000000(0x488), var_s0 = temp_v0, (temp_v0 != 0))) {
        var_v1 = var_s0;
        if ((var_s0 != 0) || (temp_v0_2 = func_00000000(8), var_v1 = temp_v0_2, (temp_v0_2 != 0))) {
            *(s32 *)((char *)(var_v1) + 0x0) = (s32)((char *)&D_00000000_cf80 + 0xCF80);
            *(s32 *)((char *)(var_v1) + 0x4) = 0;
        }
        u1_a.x = 1.0f;
        u1_a.y = 1.0f;
        u1_a.z = 1.0f;
        u1_c.x = 1.0f;
        u1_c.y = 1.0f;
        u1_c.z = 1.0f;
        u1_c.w = 1.0f;
        u1_a.w = 0.0f;
        u1_b.x = 0.0f;
        u1_b.y = 0.0f;
        u1_b.z = 0.0f;
        u1_b.w = 0.0f;
        u1_f.v = *(s32 *)((char *)&D_00000000_cf90 + 0xCF90);
        sp78 = u1_a;
        var_a0 = var_s0 + 8;
        sp68 = u1_b;
        sp58 = u1_c;
        sp54 = u1_f;
        if ((var_s0 != (void *)-8) || (temp_v0_2 = func_00000000(0x24), var_a0 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0) + 0xC) = (s32)((char *)&D_00000000_cd58_u1 + 0xCD58);
            *(s32 *)((char *)(var_a0) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0) + 0x10) = sp78;
        }
        u2_a.x = 1.0f;
        u2_a.y = 1.0f;
        u2_a.z = 1.0f;
        u2_a.w = 0.0f;
        u2_b.x = 0.0f;
        u2_b.y = 0.0f;
        u2_b.z = 0.0f;
        u2_b.w = 0.0f;
        u2_c.x = 1.0f;
        u2_c.y = 1.0f;
        u2_c.z = 1.0f;
        u2_c.w = 1.0f;
        u2_f.v = *(s32 *)((char *)&D_00000000_cf94 + 0xCF94);
        sp78 = u2_a;
        var_a0_2 = var_s0 + 0x2C;
        sp68 = u2_b;
        sp58 = u2_c;
        sp54 = u2_f;
        if ((var_s0 != (void *)-0x2C) || (temp_v0_2 = func_00000000(0x24), var_a0_2 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_2, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_2) + 0xC) = (s32)((char *)&D_00000000_cd58_u2 + 0xCD58);
            *(s32 *)((char *)(var_a0_2) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_2) + 0x10) = sp78;
        }
        u3_a.x = 1.0f;
        u3_a.y = 1.0f;
        u3_a.z = 1.0f;
        u3_a.w = 0.0f;
        u3_b.x = 0.0f;
        u3_b.y = 0.0f;
        u3_b.z = 0.0f;
        u3_b.w = 0.0f;
        u3_c.x = 1.0f;
        u3_c.y = 1.0f;
        u3_c.z = 1.0f;
        u3_c.w = 1.0f;
        u3_f.v = *(s32 *)((char *)&D_00000000_cf98 + 0xCF98);
        sp78 = u3_a;
        var_a0_2 = var_s0 + 0x50;
        sp68 = u3_b;
        sp58 = u3_c;
        sp54 = u3_f;
        if ((var_s0 != (void *)-0x50) || (temp_v0_2 = func_00000000(0x24), var_a0_2 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_2, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_2) + 0xC) = (s32)((char *)&D_00000000_cd58_u3 + 0xCD58);
            *(s32 *)((char *)(var_a0_2) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_2) + 0x10) = sp78;
        }
        u4_a.x = 1.0f;
        u4_a.y = 1.0f;
        u4_a.z = 1.0f;
        u4_a.w = 0.0f;
        u4_b.x = 0.0f;
        u4_b.y = 0.0f;
        u4_b.z = 0.0f;
        u4_b.w = 0.0f;
        u4_c.x = 1.0f;
        u4_c.y = 1.0f;
        u4_c.z = 1.0f;
        u4_c.w = 1.0f;
        u4_f.v = *(s32 *)((char *)&D_00000000_cf9c + 0xCF9C);
        sp78 = u4_a;
        var_a0_4 = var_s0 + 0x74;
        sp68 = u4_b;
        sp58 = u4_c;
        sp54 = u4_f;
        if ((var_s0 != (void *)-0x74) || (temp_v0_2 = func_00000000(0x24), var_a0_4 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_4, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_4) + 0xC) = (s32)((char *)&D_00000000_cd58_u4 + 0xCD58);
            *(s32 *)((char *)(var_a0_4) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_4) + 0x10) = sp78;
        }
        u5_a.x = 1.0f;
        u5_a.w = 0.0f;
        u5_b.x = 0.0f;
        u5_b.y = 0.0f;
        u5_b.z = 0.0f;
        u5_b.w = 0.0f;
        u5_c.x = 1.0f;
        u5_c.y = 1.0f;
        u5_c.z = 1.0f;
        u5_c.w = 1.0f;
        u5_a.y = *(f32 *)((char *)&D_00000000_0d0c + 0xD0C);
        u5_f.v = *(s32 *)((char *)&D_00000000_cfa0 + 0xCFA0); u5_a.z = *(f32 *)((char *)&D_00000000_0d10 + 0xD10);
        sp78 = u5_a;
        var_a0_4 = var_s0 + 0x98;
        sp68 = u5_b;
        sp58 = u5_c;
        sp54 = u5_f;
        if ((var_s0 != (void *)-0x98) || (temp_v0_2 = func_00000000(0x24), var_a0_4 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_4, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_4) + 0xC) = (s32)((char *)&D_00000000_cd58_u5 + 0xCD58);
            *(s32 *)((char *)(var_a0_4) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_4) + 0x10) = sp78;
        }
        u6_a.x = 1.0f;
        u6_a.y = 1.0f;
        u6_a.w = 0.0f;
        u6_b.x = 0.0f;
        u6_b.y = 0.0f;
        u6_b.z = 0.0f;
        u6_b.w = 0.0f;
        u6_c.x = 1.0f;
        u6_c.y = 1.0f;
        u6_c.z = 1.0f;
        u6_c.w = 1.0f;
        u6_a.z = *(f32 *)((char *)&D_00000000_0d14 + 0xD14); u6_f.v = *(s32 *)((char *)&D_00000000_cfa4 + 0xCFA4);
        sp78 = u6_a;
        var_a0_6 = var_s0 + 0xBC;
        sp68 = u6_b;
        sp58 = u6_c;
        sp54 = u6_f;
        if ((var_s0 != (void *)-0xBC) || (temp_v0_2 = func_00000000(0x24), var_a0_6 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_6, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_6) + 0xC) = (s32)((char *)&D_00000000_cd58_u6 + 0xCD58);
            *(s32 *)((char *)(var_a0_6) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_6) + 0x10) = sp78;
        }
        u7_a.x = 1.0f;
        u7_a.w = 0.0f;
        u7_b.x = 0.0f;
        u7_b.y = 0.0f;
        u7_b.z = 0.0f;
        u7_b.w = 0.0f;
        u7_c.x = 1.0f;
        u7_c.y = 1.0f;
        u7_c.z = 1.0f;
        u7_c.w = 1.0f;
        u7_a.y = *(f32 *)((char *)&D_00000000_0d18 + 0xD18);
        u7_f.v = *(s32 *)((char *)&D_00000000_cfa8 + 0xCFA8); u7_a.z = *(f32 *)((char *)&D_00000000_0d1c + 0xD1C);
        sp78 = u7_a;
        var_a0_6 = var_s0 + 0xE0;
        sp68 = u7_b;
        sp58 = u7_c;
        sp54 = u7_f;
        if ((var_s0 != (void *)-0xE0) || (temp_v0_2 = func_00000000(0x24), var_a0_6 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_6, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_6) + 0xC) = (s32)((char *)&D_00000000_cd58_u7 + 0xCD58);
            *(s32 *)((char *)(var_a0_6) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_6) + 0x10) = sp78;
        }
        u8_a.x = 1.0f;
        u8_a.y = 1.0f;
        u8_a.w = 0.0f;
        u8_b.x = 0.0f;
        u8_b.y = 0.0f;
        u8_b.z = 0.0f;
        u8_b.w = 0.0f;
        u8_c.x = 1.0f;
        u8_c.y = 1.0f;
        u8_c.z = 1.0f;
        u8_c.w = 1.0f;
        u8_a.z = *(f32 *)((char *)&D_00000000_0d20 + 0xD20); u8_f.v = *(s32 *)((char *)&D_00000000_cfac + 0xCFAC);
        sp78 = u8_a;
        var_a0_8 = var_s0 + 0x104;
        sp68 = u8_b;
        sp58 = u8_c;
        sp54 = u8_f;
        if ((var_s0 != (void *)-0x104) || (temp_v0_2 = func_00000000(0x24), var_a0_8 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_8, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_8) + 0xC) = (s32)((char *)&D_00000000_cd58_u8 + 0xCD58);
            *(s32 *)((char *)(var_a0_8) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_8) + 0x10) = sp78;
        }
        u9_a.x = 1.0f;
        u9_a.w = 0.0f;
        u9_b.x = 0.0f;
        u9_b.y = 0.0f;
        u9_b.z = 0.0f;
        u9_b.w = 0.0f;
        u9_c.x = 1.0f;
        u9_c.y = 1.0f;
        u9_c.z = 1.0f;
        u9_c.w = 1.0f;
        u9_a.y = *(f32 *)((char *)&D_00000000_0d24 + 0xD24);
        u9_f.v = *(s32 *)((char *)&D_00000000_cfb0 + 0xCFB0); u9_a.z = *(f32 *)((char *)&D_00000000_0d28 + 0xD28);
        sp78 = u9_a;
        var_a0_8 = var_s0 + 0x128;
        sp68 = u9_b;
        sp58 = u9_c;
        sp54 = u9_f;
        if ((var_s0 != (void *)-0x128) || (temp_v0_2 = func_00000000(0x24), var_a0_8 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_8, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_8) + 0xC) = (s32)((char *)&D_00000000_cd58_u9 + 0xCD58);
            *(s32 *)((char *)(var_a0_8) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_8) + 0x10) = sp78;
        }
        u10_a.x = 1.0f;
        u10_a.y = 1.0f;
        u10_a.w = 0.0f;
        u10_b.x = 0.0f;
        u10_b.y = 0.0f;
        u10_b.z = 0.0f;
        u10_b.w = 0.0f;
        u10_c.x = 1.0f;
        u10_c.y = 1.0f;
        u10_c.z = 1.0f;
        u10_c.w = 1.0f;
        u10_a.z = *(f32 *)((char *)&D_00000000_0d2c + 0xD2C); u10_f.v = *(s32 *)((char *)&D_00000000_cfb4 + 0xCFB4);
        sp78 = u10_a;
        var_a0_10 = var_s0 + 0x14C;
        sp68 = u10_b;
        sp58 = u10_c;
        sp54 = u10_f;
        if ((var_s0 != (void *)-0x14C) || (temp_v0_2 = func_00000000(0x24), var_a0_10 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_10, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_10) + 0xC) = (s32)((char *)&D_00000000_cd58_u10 + 0xCD58);
            *(s32 *)((char *)(var_a0_10) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_10) + 0x10) = sp78;
        }
        u11_a.x = 1.0f;
        u11_a.w = 0.0f;
        u11_b.x = 0.0f;
        u11_b.y = 0.0f;
        u11_b.z = 0.0f;
        u11_b.w = 0.0f;
        u11_c.x = 1.0f;
        u11_c.y = 1.0f;
        u11_c.z = 1.0f;
        u11_c.w = 1.0f;
        u11_a.y = *(f32 *)((char *)&D_00000000_0d30 + 0xD30);
        u11_f.v = *(s32 *)((char *)&D_00000000_cfb8 + 0xCFB8); u11_a.z = *(f32 *)((char *)&D_00000000_0d34 + 0xD34);
        sp78 = u11_a;
        var_a0_10 = var_s0 + 0x170;
        sp68 = u11_b;
        sp58 = u11_c;
        sp54 = u11_f;
        if ((var_s0 != (void *)-0x170) || (temp_v0_2 = func_00000000(0x24), var_a0_10 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_10, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_10) + 0xC) = (s32)((char *)&D_00000000_cd58_u11 + 0xCD58);
            *(s32 *)((char *)(var_a0_10) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_10) + 0x10) = sp78;
        }
        u12_a.x = 1.0f;
        u12_a.y = 1.0f;
        u12_a.w = 0.0f;
        u12_b.x = 0.0f;
        u12_b.y = 0.0f;
        u12_b.z = 0.0f;
        u12_b.w = 0.0f;
        u12_c.x = 1.0f;
        u12_c.y = 1.0f;
        u12_c.z = 1.0f;
        u12_c.w = 1.0f;
        u12_a.z = *(f32 *)((char *)&D_00000000_0d38 + 0xD38); u12_f.v = *(s32 *)((char *)&D_00000000_cfbc + 0xCFBC);
        sp78 = u12_a;
        var_a0_12 = var_s0 + 0x194;
        sp68 = u12_b;
        sp58 = u12_c;
        sp54 = u12_f;
        if ((var_s0 != (void *)-0x194) || (temp_v0_2 = func_00000000(0x24), var_a0_12 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_12, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_12) + 0xC) = (s32)((char *)&D_00000000_cd58_u12 + 0xCD58);
            *(s32 *)((char *)(var_a0_12) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_12) + 0x10) = sp78;
        }
        u13_a.x = 1.0f;
        u13_a.w = 0.0f;
        u13_b.x = 0.0f;
        u13_b.y = 0.0f;
        u13_b.z = 0.0f;
        u13_b.w = 0.0f;
        u13_c.x = 1.0f;
        u13_c.y = 1.0f;
        u13_c.z = 1.0f;
        u13_c.w = 1.0f;
        u13_a.y = *(f32 *)((char *)&D_00000000_0d3c + 0xD3C);
        u13_f.v = *(s32 *)((char *)&D_00000000_cfc0 + 0xCFC0); u13_a.z = *(f32 *)((char *)&D_00000000_0d40 + 0xD40);
        sp78 = u13_a;
        var_a0_12 = var_s0 + 0x1B8;
        sp68 = u13_b;
        sp58 = u13_c;
        sp54 = u13_f;
        if ((var_s0 != (void *)-0x1B8) || (temp_v0_2 = func_00000000(0x24), var_a0_12 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_12, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_12) + 0xC) = (s32)((char *)&D_00000000_cd58_u13 + 0xCD58);
            *(s32 *)((char *)(var_a0_12) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_12) + 0x10) = sp78;
        }
        u14_a.x = 1.0f;
        u14_a.y = 1.0f;
        u14_a.w = 0.0f;
        u14_b.x = 0.0f;
        u14_b.y = 0.0f;
        u14_b.z = 0.0f;
        u14_b.w = 0.0f;
        u14_c.x = 1.0f;
        u14_c.y = 1.0f;
        u14_c.z = 1.0f;
        u14_c.w = 1.0f;
        u14_a.z = *(f32 *)((char *)&D_00000000_0d44 + 0xD44); u14_f.v = *(s32 *)((char *)&D_00000000_cfc4 + 0xCFC4);
        sp78 = u14_a;
        var_a0_14 = var_s0 + 0x1DC;
        sp68 = u14_b;
        sp58 = u14_c;
        sp54 = u14_f;
        if ((var_s0 != (void *)-0x1DC) || (temp_v0_2 = func_00000000(0x24), var_a0_14 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_14, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_14) + 0xC) = (s32)((char *)&D_00000000_cd58_u14 + 0xCD58);
            *(s32 *)((char *)(var_a0_14) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_14) + 0x10) = sp78;
        }
        u15_a.x = 1.0f;
        u15_a.w = 0.0f;
        u15_b.x = 0.0f;
        u15_b.y = 0.0f;
        u15_b.z = 0.0f;
        u15_b.w = 0.0f;
        u15_c.x = 1.0f;
        u15_c.y = 1.0f;
        u15_c.z = 1.0f;
        u15_c.w = 1.0f;
        u15_a.y = *(f32 *)((char *)&D_00000000_0d48 + 0xD48);
        u15_f.v = *(s32 *)((char *)&D_00000000_cfc8 + 0xCFC8); u15_a.z = *(f32 *)((char *)&D_00000000_0d4c + 0xD4C);
        sp78 = u15_a;
        var_a0_14 = var_s0 + 0x200;
        sp68 = u15_b;
        sp58 = u15_c;
        sp54 = u15_f;
        if ((var_s0 != (void *)-0x200) || (temp_v0_2 = func_00000000(0x24), var_a0_14 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_14, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_14) + 0xC) = (s32)((char *)&D_00000000_cd58_u15 + 0xCD58);
            *(s32 *)((char *)(var_a0_14) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_14) + 0x10) = sp78;
        }
        u16_a.z = 0.0f;
        u16_a.w = 0.0f;
        u16_b.x = 0.0f;
        u16_b.y = 0.0f;
        u16_b.z = 0.0f;
        u16_b.w = 0.0f;
        u16_c.x = 1.0f;
        u16_c.y = 1.0f;
        u16_c.z = 1.0f;
        u16_c.w = 1.0f;
        u16_a.x = *(f32 *)((char *)&D_00000000_0d50 + 0xD50);
        u16_f.v = *(s32 *)((char *)&D_00000000_cfcc + 0xCFCC); u16_a.y = *(f32 *)((char *)&D_00000000_0d54 + 0xD54);
        sp78 = u16_a;
        var_a0_16 = var_s0 + 0x224;
        sp68 = u16_b;
        sp58 = u16_c;
        sp54 = u16_f;
        if ((var_s0 != (void *)-0x224) || (temp_v0_2 = func_00000000(0x24), var_a0_16 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_16, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_16) + 0xC) = (s32)((char *)&D_00000000_cd58_u16 + 0xCD58);
            *(s32 *)((char *)(var_a0_16) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_16) + 0x10) = sp78;
        }
        u17_a.w = 0.0f;
        u17_b.x = 0.0f;
        u17_b.y = 0.0f;
        u17_b.z = 0.0f;
        u17_b.w = 0.0f;
        u17_c.x = 1.0f;
        u17_c.y = 1.0f;
        u17_c.z = 1.0f;
        u17_c.w = 1.0f;
        u17_a.x = *(f32 *)((char *)&D_00000000_0d58 + 0xD58);
        u17_a.y = *(f32 *)((char *)&D_00000000_0d5c + 0xD5C);
        u17_f.v = *(s32 *)((char *)&D_00000000_cfd0 + 0xCFD0); u17_a.z = *(f32 *)((char *)&D_00000000_0d60 + 0xD60);
        sp78 = u17_a;
        var_a0_16 = var_s0 + 0x248;
        sp68 = u17_b;
        sp58 = u17_c;
        sp54 = u17_f;
        if ((var_s0 != (void *)-0x248) || (temp_v0_2 = func_00000000(0x24), var_a0_16 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_16, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_16) + 0xC) = (s32)((char *)&D_00000000_cd58_u17 + 0xCD58);
            *(s32 *)((char *)(var_a0_16) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_16) + 0x10) = sp78;
        }
        u18_a.x = 0.0f;
        u18_a.y = 0.0f;
        u18_a.w = 0.0f;
        u18_b.x = 0.0f;
        u18_b.y = 0.0f;
        u18_b.z = 0.0f;
        u18_b.w = 0.0f;
        u18_c.x = 1.0f;
        u18_c.y = 1.0f;
        u18_c.z = 1.0f;
        u18_c.w = 1.0f;
        u18_a.z = *(f32 *)((char *)&D_00000000_0d64 + 0xD64); u18_f.v = *(s32 *)((char *)&D_00000000_cfd4 + 0xCFD4);
        sp78 = u18_a;
        var_a0_18 = var_s0 + 0x26C;
        sp68 = u18_b;
        sp58 = u18_c;
        sp54 = u18_f;
        if ((var_s0 != (void *)-0x26C) || (temp_v0_2 = func_00000000(0x24), var_a0_18 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_18, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_18) + 0xC) = (s32)((char *)&D_00000000_cd58_u18 + 0xCD58);
            *(s32 *)((char *)(var_a0_18) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_18) + 0x10) = sp78;
        }
        u19_a.y = 1.0f;
        u19_a.z = 0.0f;
        u19_a.w = 0.0f;
        u19_b.x = 0.0f;
        u19_b.y = 0.0f;
        u19_b.z = 0.0f;
        u19_b.w = 0.0f;
        u19_c.x = 1.0f;
        u19_c.y = 1.0f;
        u19_c.z = 1.0f;
        u19_c.w = 1.0f;
        u19_a.x = *(f32 *)((char *)&D_00000000_0d68 + 0xD68); u19_f.v = *(s32 *)((char *)&D_00000000_cfd8 + 0xCFD8);
        sp78 = u19_a;
        var_a0_18 = var_s0 + 0x290;
        sp68 = u19_b;
        sp58 = u19_c;
        sp54 = u19_f;
        if ((var_s0 != (void *)-0x290) || (temp_v0_2 = func_00000000(0x24), var_a0_18 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_18, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_18) + 0xC) = (s32)((char *)&D_00000000_cd58_u19 + 0xCD58);
            *(s32 *)((char *)(var_a0_18) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_18) + 0x10) = sp78;
        }
        u20_a.z = 0.0f;
        u20_a.w = 0.0f;
        u20_b.x = 0.0f;
        u20_b.y = 0.0f;
        u20_b.z = 0.0f;
        u20_b.w = 0.0f;
        u20_c.x = 1.0f;
        u20_c.y = 1.0f;
        u20_c.z = 1.0f;
        u20_c.w = 1.0f;
        u20_a.x = *(f32 *)((char *)&D_00000000_0d6c + 0xD6C);
        u20_f.v = *(s32 *)((char *)&D_00000000_cfdc + 0xCFDC); u20_a.y = *(f32 *)((char *)&D_00000000_0d70 + 0xD70);
        sp78 = u20_a;
        var_a0_20 = var_s0 + 0x2B4;
        sp68 = u20_b;
        sp58 = u20_c;
        sp54 = u20_f;
        if ((var_s0 != (void *)-0x2B4) || (temp_v0_2 = func_00000000(0x24), var_a0_20 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_20, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_20) + 0xC) = (s32)((char *)&D_00000000_cd58_u20 + 0xCD58);
            *(s32 *)((char *)(var_a0_20) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_20) + 0x10) = sp78;
        }
        u21_a.w = 0.0f;
        u21_b.x = 0.0f;
        u21_b.y = 0.0f;
        u21_b.z = 0.0f;
        u21_b.w = 0.0f;
        u21_c.x = 1.0f;
        u21_c.y = 1.0f;
        u21_c.z = 1.0f;
        u21_c.w = 1.0f;
        u21_a.x = *(f32 *)((char *)&D_00000000_0d74 + 0xD74);
        u21_a.y = *(f32 *)((char *)&D_00000000_0d78 + 0xD78);
        u21_f.v = *(s32 *)((char *)&D_00000000_cfe0 + 0xCFE0); u21_a.z = *(f32 *)((char *)&D_00000000_0d7c + 0xD7C);
        sp78 = u21_a;
        var_a0_20 = var_s0 + 0x2D8;
        sp68 = u21_b;
        sp58 = u21_c;
        sp54 = u21_f;
        if ((var_s0 != (void *)-0x2D8) || (temp_v0_2 = func_00000000(0x24), var_a0_20 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_20, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_20) + 0xC) = (s32)((char *)&D_00000000_cd58_u21 + 0xCD58);
            *(s32 *)((char *)(var_a0_20) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_20) + 0x10) = sp78;
        }
        u22_a.w = 0.0f;
        u22_b.x = 0.0f;
        u22_b.y = 0.0f;
        u22_b.z = 0.0f;
        u22_b.w = 0.0f;
        u22_c.x = 1.0f;
        u22_c.y = 1.0f;
        u22_c.z = 1.0f;
        u22_c.w = 1.0f;
        u22_a.x = *(f32 *)((char *)&D_00000000_0d80 + 0xD80);
        u22_a.y = *(f32 *)((char *)&D_00000000_0d84 + 0xD84);
        u22_f.v = *(s32 *)((char *)&D_00000000_cfe4 + 0xCFE4); u22_a.z = *(f32 *)((char *)&D_00000000_0d88 + 0xD88);
        sp78 = u22_a;
        var_a0_22 = var_s0 + 0x2FC;
        sp68 = u22_b;
        sp58 = u22_c;
        sp54 = u22_f;
        if ((var_s0 != (void *)-0x2FC) || (temp_v0_2 = func_00000000(0x24), var_a0_22 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_22, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_22) + 0xC) = (s32)((char *)&D_00000000_cd58_u22 + 0xCD58);
            *(s32 *)((char *)(var_a0_22) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_22) + 0x10) = sp78;
        }
        u23_a.x = 1.0f;
        u23_a.w = 0.0f;
        u23_b.x = 0.0f;
        u23_b.y = 0.0f;
        u23_b.z = 0.0f;
        u23_b.w = 0.0f;
        u23_c.x = 1.0f;
        u23_c.y = 1.0f;
        u23_c.z = 1.0f;
        u23_c.w = 1.0f;
        u23_a.y = *(f32 *)((char *)&D_00000000_0d8c + 0xD8C);
        u23_f.v = *(s32 *)((char *)&D_00000000_cfe8 + 0xCFE8); u23_a.z = *(f32 *)((char *)&D_00000000_0d90 + 0xD90);
        sp78 = u23_a;
        var_a0_22 = var_s0 + 0x320;
        sp68 = u23_b;
        sp58 = u23_c;
        sp54 = u23_f;
        if ((var_s0 != (void *)-0x320) || (temp_v0_2 = func_00000000(0x24), var_a0_22 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_22, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_22) + 0xC) = (s32)((char *)&D_00000000_cd58_u23 + 0xCD58);
            *(s32 *)((char *)(var_a0_22) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_22) + 0x10) = sp78;
        }
        temp_f0 = *(f32 *)((char *)&D_00000000_0d94 + 0xD94);
        u24_a.w = 0.0f;
        u24_b.x = 0.0f;
        u24_b.y = 0.0f;
        u24_b.z = 0.0f;
        u24_b.w = 0.0f;
        u24_c.x = 1.0f;
        u24_c.y = 1.0f;
        u24_c.z = 1.0f;
        u24_c.w = 1.0f;
        u24_a.x = temp_f0;
        u24_a.y = temp_f0;
        u24_a.z = temp_f0;
        u24_f.v = *(s32 *)((char *)&D_00000000_cfec + 0xCFEC);
        sp78 = u24_a;
        var_a0_24 = var_s0 + 0x344;
        sp68 = u24_b;
        sp58 = u24_c;
        sp54 = u24_f;
        if ((var_s0 != (void *)-0x344) || (temp_v0_2 = func_00000000(0x24), var_a0_24 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_24, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_24) + 0xC) = (s32)((char *)&D_00000000_cd58_u24 + 0xCD58);
            *(s32 *)((char *)(var_a0_24) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_24) + 0x10) = sp78;
        }
        u25_a.w = 0.0f;
        u25_b.x = 0.0f;
        u25_b.y = 0.0f;
        u25_b.z = 0.0f;
        u25_b.w = 0.0f;
        u25_c.x = 1.0f;
        u25_c.y = 1.0f;
        u25_c.z = 1.0f;
        u25_c.w = 1.0f;
        u25_a.x = *(f32 *)((char *)&D_00000000_0d9c + 0xD9C);
        u25_a.y = *(f32 *)((char *)&D_00000000_0da0 + 0xDA0);
        u25_f.v = *(s32 *)((char *)&D_00000000_cff0 + 0xCFF0); u25_a.z = *(f32 *)((char *)&D_00000000_0da4 + 0xDA4);
        sp78 = u25_a;
        var_a0_24 = var_s0 + 0x368;
        sp68 = u25_b;
        sp58 = u25_c;
        sp54 = u25_f;
        if ((var_s0 != (void *)-0x368) || (temp_v0_2 = func_00000000(0x24), var_a0_24 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_24, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_24) + 0xC) = (s32)((char *)&D_00000000_cd58_u25 + 0xCD58);
            *(s32 *)((char *)(var_a0_24) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_24) + 0x10) = sp78;
        }
        u26_a.w = 0.0f;
        u26_b.x = 0.0f;
        u26_b.y = 0.0f;
        u26_b.z = 0.0f;
        u26_b.w = 0.0f;
        u26_c.x = 1.0f;
        u26_c.y = 1.0f;
        u26_c.z = 1.0f;
        u26_c.w = 1.0f;
        u26_a.x = *(f32 *)((char *)&D_00000000_0da8 + 0xDA8);
        u26_a.y = *(f32 *)((char *)&D_00000000_0dac + 0xDAC);
        u26_f.v = *(s32 *)((char *)&D_00000000_cff4 + 0xCFF4); u26_a.z = *(f32 *)((char *)&D_00000000_0db0 + 0xDB0);
        sp78 = u26_a;
        var_a0_26 = var_s0 + 0x38C;
        sp68 = u26_b;
        sp58 = u26_c;
        sp54 = u26_f;
        if ((var_s0 != (void *)-0x38C) || (temp_v0_2 = func_00000000(0x24), var_a0_26 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_26, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_26) + 0xC) = (s32)((char *)&D_00000000_cd58_u26 + 0xCD58);
            *(s32 *)((char *)(var_a0_26) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_26) + 0x10) = sp78;
        }
        u27_a.w = 0.0f;
        u27_b.x = 0.0f;
        u27_b.y = 0.0f;
        u27_b.z = 0.0f;
        u27_b.w = 0.0f;
        u27_c.x = 1.0f;
        u27_c.y = 1.0f;
        u27_c.z = 1.0f;
        u27_c.w = 1.0f;
        u27_a.x = *(f32 *)((char *)&D_00000000_0db4 + 0xDB4);
        u27_a.y = *(f32 *)((char *)&D_00000000_0db8 + 0xDB8);
        u27_f.v = *(s32 *)((char *)&D_00000000_cff8 + 0xCFF8); u27_a.z = *(f32 *)((char *)&D_00000000_0dbc + 0xDBC);
        sp78 = u27_a;
        var_a0_26 = var_s0 + 0x3B0;
        sp68 = u27_b;
        sp58 = u27_c;
        sp54 = u27_f;
        if ((var_s0 != (void *)-0x3B0) || (temp_v0_2 = func_00000000(0x24), var_a0_26 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_26, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_26) + 0xC) = (s32)((char *)&D_00000000_cd58_u27 + 0xCD58);
            *(s32 *)((char *)(var_a0_26) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_26) + 0x10) = sp78;
        }
        u28_a.w = 0.0f;
        u28_b.x = 0.0f;
        u28_b.y = 0.0f;
        u28_b.z = 0.0f;
        u28_b.w = 0.0f;
        u28_c.x = 1.0f;
        u28_c.y = 1.0f;
        u28_c.z = 1.0f;
        u28_c.w = 1.0f;
        u28_a.x = *(f32 *)((char *)&D_00000000_0dc0 + 0xDC0);
        u28_a.y = *(f32 *)((char *)&D_00000000_0dc4 + 0xDC4);
        u28_f.v = *(s32 *)((char *)&D_00000000_cffc + 0xCFFC); u28_a.z = *(f32 *)((char *)&D_00000000_0dc8 + 0xDC8);
        sp78 = u28_a;
        var_a0_26 = var_s0 + 0x3D4;
        sp68 = u28_b;
        sp58 = u28_c;
        sp54 = u28_f;
        if ((var_s0 != (void *)-0x3D4) || (temp_v0_2 = func_00000000(0x24), var_a0_26 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_26, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_26) + 0xC) = (s32)((char *)&D_00000000_cd58_u28 + 0xCD58);
            *(s32 *)((char *)(var_a0_26) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_26) + 0x10) = sp78;
        }
        u29_a.x = 1.0f;
        u29_a.w = 0.0f;
        u29_b.x = 0.0f;
        u29_b.y = 0.0f;
        u29_b.z = 0.0f;
        u29_b.w = 0.0f;
        u29_c.x = 1.0f;
        u29_c.y = 1.0f;
        u29_c.z = 1.0f;
        u29_c.w = 1.0f;
        u29_a.y = *(f32 *)((char *)&D_00000000_0dcc + 0xDCC);
        u29_f.v = *(s32 *)((char *)&D_00000000_d000 + 0xD000); u29_a.z = *(f32 *)((char *)&D_00000000_0dd0 + 0xDD0);
        sp78 = u29_a;
        var_a0_26 = var_s0 + 0x3F8;
        sp68 = u29_b;
        sp58 = u29_c;
        sp54 = u29_f;
        if ((var_s0 != (void *)-0x3F8) || (temp_v0_2 = func_00000000(0x24), var_a0_26 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_26, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_26) + 0xC) = (s32)((char *)&D_00000000_cd58_u29 + 0xCD58);
            *(s32 *)((char *)(var_a0_26) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_26) + 0x10) = sp78;
        }
        temp_f0_2 = *(f32 *)((char *)&D_00000000_0dd4 + 0xDD4);
        u30_a.w = 0.0f;
        u30_b.x = 0.0f;
        u30_b.y = 0.0f;
        u30_b.z = 0.0f;
        u30_b.w = 0.0f;
        u30_c.x = 1.0f;
        u30_c.y = 1.0f;
        u30_c.z = 1.0f;
        u30_c.w = 1.0f;
        u30_a.x = temp_f0_2;
        u30_a.y = temp_f0_2;
        u30_a.z = temp_f0_2;
        u30_f.v = *(s32 *)((char *)&D_00000000_d004 + 0xD004);
        sp78 = u30_a;
        var_a0_30 = var_s0 + 0x41C;
        sp68 = u30_b;
        sp58 = u30_c;
        sp54 = u30_f;
        if ((var_s0 != (void *)-0x41C) || (temp_v0_2 = func_00000000(0x24), var_a0_30 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_30, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_30) + 0xC) = (s32)((char *)&D_00000000_cd58_u30 + 0xCD58);
            *(s32 *)((char *)(var_a0_30) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_30) + 0x10) = sp78;
        }
        u31_a.w = 0.0f;
        u31_b.x = 0.0f;
        u31_b.y = 0.0f;
        u31_b.z = 0.0f;
        u31_b.w = 0.0f;
        u31_c.x = 1.0f;
        u31_c.y = 1.0f;
        u31_c.z = 1.0f;
        u31_c.w = 1.0f;
        u31_a.x = *(f32 *)((char *)&D_00000000_0ddc + 0xDDC);
        u31_a.y = *(f32 *)((char *)&D_00000000_0de0 + 0xDE0);
        u31_f.v = *(s32 *)((char *)&D_00000000_d008 + 0xD008); u31_a.z = *(f32 *)((char *)&D_00000000_0de4 + 0xDE4);
        sp78 = u31_a;
        var_a0_30 = var_s0 + 0x440;
        sp68 = u31_b;
        sp58 = u31_c;
        sp54 = u31_f;
        if ((var_s0 != (void *)-0x440) || (temp_v0_2 = func_00000000(0x24), var_a0_30 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_30, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_30) + 0xC) = (s32)((char *)&D_00000000_cd58_u31 + 0xCD58);
            *(s32 *)((char *)(var_a0_30) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_30) + 0x10) = sp78;
        }
        u32_a.x = 1.0f;
        u32_a.y = 1.0f;
        u32_a.z = 1.0f;
        u32_a.w = 0.0f;
        u32_b.x = 0.0f;
        u32_b.y = 0.0f;
        u32_b.z = 0.0f;
        u32_b.w = 0.0f;
        u32_c.x = 1.0f;
        u32_c.y = 1.0f;
        u32_c.z = 1.0f;
        u32_c.w = 1.0f;
        u32_f.v = *(s32 *)((char *)&D_00000000_d00c + 0xD00C);
        sp78 = u32_a;
        var_a0_30 = var_s0 + 0x464;
        sp68 = u32_b;
        sp58 = u32_c;
        sp54 = u32_f;
        if ((var_s0 != (void *)-0x464) || (temp_v0_2 = func_00000000(0x24), var_a0_30 = temp_v0_2, (temp_v0_2 != 0))) {
            func_00000000(var_a0_30, var_s0, sp54, 1);
            *(s32 *)((char *)(var_a0_30) + 0xC) = (s32)((char *)&D_00000000_cd58_u32 + 0xCD58);
            *(s32 *)((char *)(var_a0_30) + 0x20) = 0;
            *(GlV4_4244 *)((char *)(var_a0_30) + 0x10) = sp78;
        }
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00004244);
#endif

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
void gl_func_00006900(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
    volatile int pad;
    char *sp28;
    char *temp_v0;
    char *temp_v0_2;

    FW(arg0, 0xC) = arg2;
    FW(arg0, 0x4C) = arg3;
    FW(arg0, 0x4F0) = arg1;
    if (arg1 & 0x10000) {
        if (FW(arg0, 0x568) == 0) {
            temp_v0 = (char*)func_00000000(0, &D_00000000, 0x48, 0xEE, 3, 0xE);
            FW(arg0, 0x568) = temp_v0;
            (char*)func_00000000(temp_v0, (char *)-8);
        }
        (char*)func_00000000((int)arg0 + 0x588, (char *)0x60000);
        (char*)func_00000000((int)arg0 + 0x5A0, (char *)0x60003);
        (char*)func_00000000((int)arg0 + 0x5B8, (char *)0x60004);
        (char*)func_00000000((int)arg0 + 0x5D0, (char *)0x60005);
        (char*)func_00000000((int)arg0 + 0x5E8, (char *)0x60001);
        (char*)func_00000000((int)arg0 + 0x600, (char *)0x60002);
        (char*)func_00000000((int)arg0 + 0x618, (char *)0x60006);
        (char*)func_00000000((int)arg0 + 0x630, (char *)0x60007);
        (char*)func_00000000((int)arg0 + 0x660, (char *)0x60008);
        (char*)func_00000000((int)arg0 + 0x678, (char *)0x60009);
        (char*)func_00000000((int)arg0 + 0x690, (char *)0x6000A);
        (char*)func_00000000((int)arg0 + 0x648, (char *)0x6000B);
    }
    FW(arg0, 0x4D8) = 0;
    (char*)func_00000000(arg0, (char *)1, (char *)&D_00000000 + 0xD010);
    temp_v0_2 = (char*)func_00000000(0, (char *)&D_00000000 + 0xD020);
    FW(arg0, 0x56C) = temp_v0_2;
    sp28 = temp_v0_2;
    (char*)func_00000000((int)arg0 + 0x10, temp_v0_2);
    if (FW(sp28, 0x14) != 0) {
        FW(sp28, 0x4) = 1;
    }
    FW(sp28, 0x14) = arg0;
}

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
 * global f32 zeroed.
 * EXACT MATCH 2026-07-11 (agent-f, mis-diagnosed-cap crossing). The "caps <80"
 * were global-CSE + store-order, not FP/reloc: target holds the &D base in ONE
 * register across the two post-call stores (G->0x8C, G->0x7C); build re-derived
 * it via lui $at per site. Fix: a FRESH post-call base pointer H=(int*)&D reused
 * for both stores (persistent reg) cascades to fix the FP-const load order +
 * jr-delay fill; swap the 0x510/0x508 zero-stores; gl_d_x/y/z = 3 distinct
 * base-0 aliases reproduce target's 3 separate lui $at,0 (no CSE). cmp clean. */
extern float gl_d_x, gl_d_y, gl_d_z;  /* 3 global floats zeroed by this fn */
void gl_func_00006AAC(int *a0) {
    int *G = (int*)&D_00000000;
    int *H;
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x2C) = 0;
    *(int*)((char*)a0 + 0x4E0) = 0;
    *(int*)((char*)a0 + 0x4DC) = 0;
    *(int*)((char*)a0 + 0x4FC) = 0;
    *(int*)((char*)a0 + 0x4F4) = 0x1FFFF;
    G[0x78 / 4] = 1;
    gl_func_00000000(&D_00000000, 0);
    *(int*)((char*)a0 + 0x4E8) = 20;
    *(int*)((char*)a0 + 0x4E4) = (*(int*)((char*)a0 + 0x4F0) & (1 << 18)) ? 120 : 0;
    H = (int*)&D_00000000;
    H[0x8C / 4] = *(int*)((char*)a0 + 0x4F0);
    *(int*)((char*)a0 + 0x540) = 255;
    *(float*)((char*)a0 + 0x534) = 1.0f;
    *(float*)((char*)a0 + 0x538) = 1.0f;
    gl_d_x = 0.0f;
    gl_d_y = 0.0f;
    gl_d_z = 0.0f;
    *(int*)((char*)a0 + 0x500) = 0;
    *(int*)((char*)a0 + 0x510) = 0;
    *(int*)((char*)a0 + 0x508) = 0;
    H[0x7C / 4] = 0;
}

/* gl_func_00006B80 - object initializer (0xB8, 46 insns). MATCHED 2026-06-20.
 * Two landing levers: (1) assign a0->0x4E4 = a1 BEFORE the two zero-stores so
 * IDO's as1 scheduler hoists the a1 reload + the &D mode-load lui to cover
 * load latency (matches target schedule exactly); (2) call the vtable fn
 * THROUGH the dereferenced pointer (no intermediate `fn` local) so IDO uses
 * $t9 for the jalr target instead of $v1. a0 = large object: 0x4DC=2, 0x4E0=3,
 * 0x4E4=a1, 0x4EC=0, 0x4F8=a2, 0x518=0, 0x544=255, 0x54C f32 duration (120,
 * or 60 when global mode *(&D)->0x34==2), 0x550=0.0, 0x554=150.0; a0->0x28
 * vtable ptr, fn @0x7C, s16 base-adjust @0x78 (obj-0x28 dispatch idiom). */
void gl_func_00006B80(char *a0, int a1, int a2) {
    char *v;
    *(int *)(a0 + 0x4F8) = a2;
    *(int *)(a0 + 0x4E0) = 3;
    *(int *)(a0 + 0x4DC) = 2;
    gl_func_00000000(&D_00000000, 0);
    *(int *)(a0 + 0x4E4) = a1;
    *(int *)(a0 + 0x4EC) = 0;
    *(int *)(a0 + 0x518) = 0;
    *(float *)(a0 + 0x54C) = 120.0f;
    if (*(int *)((char *)&D_00000000 + 0x34) == 2) {
        *(float *)(a0 + 0x54C) = 60.0f;
    }
    *(float *)(a0 + 0x550) = 0.0f;
    *(int *)(a0 + 0x544) = 255;
    *(float *)(a0 + 0x554) = 150.0f;
    v = *(char **)(a0 + 0x28);
    (*(void (**)(char *))(v + 0x7C))((char *)((int)(short)*(short *)(v + 0x78) + (int)a0));
}

/* gl_func_00006C38: 41-insn struct-init. Sets a0->{0x4F8,0x4E0,0x4DC} from
 * args; calls gl_func_0(&D, 0, a2, orig_a0) (4 args, a3 = saved orig_a0);
 * post-call: writes a0->{0x4E4=a1, 0x4EC=0, 0x518=0, 0x54C=120.0f, 0x550=0.0f,
 * 0x544=0xFF, 0x554=150.0f}; if (D[0x34]==2) overwrite 0x54C with 60.0f.
 * Match key: the 0x4E4=a1 store is the FIRST post-call statement so IDO hoists
 * the a1 reload ahead of the FP setup and fills the load-delay slots with the
 * zero stores. (Prior "INSN_PATCH scheduling cap" diagnosis was wrong.) */
void gl_func_00006C38(int *a0, int a1, int a2) {
    a0[0x4F8/4] = a2;
    a0[0x4E0/4] = 3;
    a0[0x4DC/4] = 2;
    gl_func_00000000(&D_00000000, 0, a2, a0);
    a0[0x4E4/4] = a1;
    a0[0x4EC/4] = 0;
    a0[0x518/4] = 0;
    *(float*)((char*)a0 + 0x54C) = 120.0f;
    if (*(int*)((char*)&D_00000000 + 0x34) == 2) {
        *(float*)((char*)a0 + 0x54C) = 60.0f;
    }
    *(float*)((char*)a0 + 0x550) = 0.0f;
    a0[0x544/4] = 0xFF;
    *(float*)((char*)a0 + 0x554) = 150.0f;
}

/* gl_func_00006CDC - large-object initializer, near-sibling of the matched
 * gl_func_00006B80. Variant differences from 6B80: 0x518 (1304) s32 = 60
 * (0 in 6B80); extra global-mode==3 branch calls gl_func_00000000(48); vtable
 * dispatch via obj->0x28 -> {fn@0x84, s16@0x80}. Struct map: 0x4DC=2, 0x4E0=3,
 * 0x4E4=a1, 0x4EC=0, 0x4F8=a2, 0x544=255, 0x54C f32=120/60 by mode, 0x550=0.0,
 * 0x554=150.0. */
void gl_func_00006CDC(char *a0, int a1, int a2) {
  char *v;
  v = a0 + 0x4DC;
  *((int *) (a0 + 0x4F8)) = a2;
  *((int *) (a0 + 0x4E0)) = 3;
  *((int *) v) = 2;
  gl_func_00000000(&D_00000000, 0);
  *((int *) (a0 + 0x4E4)) = a1;
  *((int *) (a0 + 0x4EC)) = 0;
  *((int *) (a0 + 0x518)) = 60;
 if (1) { }
  a1++;
  a1--;
  *((float *) (a0 + 0x54C)) = 120.0f;
  if ((*((int *) (((char *) (&D_00000000)) + 0x34))) == 2)
  {
    *((float *) (a0 + 0x54C)) = 60.0f;
  }
  if ((*((int *) (((char *) (&D_00000000)) + 0x34))) == 3)
  {
    gl_func_00000000(48);
  }
  *((int *) (a0 + 0x544)) = 255;
  *((float *) (a0 + 0x550)) = 0.0f;
  *((float *) (a0 + 0x554)) = 150.0f;
  v = *((char **) (a0 + 0x28));
  (*((void (**)(char *)) (v + 0x84)))((char *) (((int) ((short) (*((short *) (v + 0x80))))) + ((int) a0)));
}

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
/* Full decode 2026-06-05 (was ~10% stub; second/third dispatch trees + epilogue
 * were TODO). Control flow: a0->0x510 guard; then IF (next=a0->0x528) != 0 AND
 * setup-call(next) != 0, run the FIRST setup+dispatch and jump straight to the
 * epilogue. OTHERWISE (next==0 || call==0) fall into the SECOND dispatch
 * (D[0x34] in {6,5} -> D[0x138] sub-tree), then the THIRD dispatch on a0->0x4F8,
 * then epilogue (a0->0x510 = 1). Calls are USO placeholders (gl_func_00000000);
 * several leave $a0 register-leftover so exact arg recovery is partial.
 *
 * NOT LANDABLE — HARD CAP (confirmed 2026-06-23, agent-e):
 *   game_libs.c is the raw-word USO BASE object: `readelf -r
 *   expected/src/game_libs/game_libs.c.o` => "There are no relocations in this
 *   file." Every jal/lui-data target is baked into the ROM as ZERO (relocs are
 *   applied at USO load time, not in the static image). This function has 14+
 *   jal calls + several lui/lw data refs, so compiled C emits R_MIPS_26 /
 *   R_MIPS_HI16/LO16 against gl_func_00000000 / D_00000000 (verified in
 *   build/non_matching/.../game_libs.c.o) which the static linker resolves to
 *   NON-ZERO addresses -> can never match the zeroed ROM words. Only call-free
 *   / data-ref-free LEAF stubs (e.g. game_libs_func_00000B8C) land in this
 *   zero-reloc base. Landing this fn requires the deferred multi-day
 *   spimdisasm-proper USO-reloc migration (project_1080_uso_spimdisasm_migration_todo).
 *   Do not re-attempt as a single-tick land. Residual vs target after the call
 *   words (which display-match as both-zero): the body is also 5 words short and
 *   carries genuine arg-arity (4-arg f(5,5,X,0)) + regalloc decode drift in the
 *   second/third dispatch — decode-quality only, irrelevant to landability. */
void gl_func_000070FC(int *a0) {
    int *next;
    int m;
    int *obj;
    if (*(int*)((char*)a0 + 0x510) != 0) return;
    next = *(int**)((char*)a0 + 0x528);
    if (next != 0 && gl_func_00000000(next) != 0) {
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
        gl_func_00000000(5, 0, 0);
        m = *(int*)((char*)&D_00000000 + 0x34);
        if (m == 5 || m == 4 || m == 6) {
            if (*(int*)((char*)&D_00000000 + 0x7C) == 1) {
                gl_func_00000000(5, 2, 0);
            } else {
                gl_func_00000000(5, 1, 0);
            }
        } else {
            gl_func_00000000(5, 1, 0);
        }
        goto epilogue;
    }
    /* second dispatch (reached when next==0 || setup-call==0) @ 0x71C8 */
    m = *(int*)((char*)&D_00000000 + 0x34);
    if (m == 6 || m == 5) {
        obj = *(int**)((char*)&D_00000000 + 0x138);
        if (*(int*)((char*)*(int**)((char*)obj + 0x44) + 0x14) != 0) {
            gl_func_00000000(obj, 0);
        } else {
            gl_func_00000000(obj, 0);
        }
    }
    /* third dispatch on a0->0x4F8 @ 0x7228 */
    if (*(int*)((char*)a0 + 0x4F8) == 5) {
        gl_func_00000000(6, 0);
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x0), 6, 0, 0);
    } else {
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x0), 0);
        m = *(int*)((char*)&D_00000000 + 0x34);
        if (m == 5) {
            if (*(int*)((char*)&D_00000000 + 0x64) == 4) {
                gl_func_00000000(5, 1, 0);
            } else {
                gl_func_00000000(5, 0, 0);
            }
        } else if (m == 4 || m == 6) {
            gl_func_00000000(5, 0, 0);
        } else {
            gl_func_00000000(5, 1, 0);
        }
    }
epilogue:
    *(int*)((char*)a0 + 0x510) = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070FC);
#endif

void game_libs_func_00007324(int a0) {}

void game_libs_func_0000732C(int a0) {}

void game_libs_func_00007334(int a0) {
}

void game_libs_func_0000733C(int a0) {}

#ifdef NON_MATCHING
/* gl_func_00007344: per-panel HUD-element updater/dispatcher.
 *   switch(arg1) over 7 element slots (cases 0/5, 1/6, 2, 3, 4 share bodies).
 *   Each case snapshots two Quad4 field-blocks from the object into local
 *   scratch (spA=obj fields, spB=obj fields), points `target` at a per-slot
 *   sub-object (obj + 0x600..0x678), and — unless the global mode word
 *   (&D_0 + 0x34) == 2 — runs a refresh callee + a vtable dispatch
 *   (*(obj->u28->fptr))(obj + (short)obj->u28->ofs).
 * Trailing: if a target was selected, ramp obj->u544 by +2 clamped to 255
 *   (on reaching 255 also set obj->u554 = 175.0f), then 3 emit callees. */
extern int gl_func_00000000();

typedef struct GlHudObj {
    char unk0[0x28];
    struct GlHudVt *unk28;          /* 0x28 vtable/handler */
    char unk2C[0x140 - 0x2C];
    Quad4 unk140;                   /* case 0/5 src A */
    char unk150[0x164 - 0x150];
    Quad4 unk164;                   /* case 0/5 src B */
    char unk174[0x188 - 0x174];
    Quad4 unk188;                   /* case 2 src A */
    char unk198[0x1AC - 0x198];
    Quad4 unk1AC;                   /* case 2 src B */
    char unk1BC[0x1D0 - 0x1BC];
    Quad4 unk1D0;                   /* case 4 src A */
    char unk1E0[0x1F4 - 0x1E0];
    Quad4 unk1F4;                   /* case 4 src B */
    char unk204[0x218 - 0x204];
    Quad4 unk218;                   /* case 3 src A */
    char unk228[0x23C - 0x228];
    Quad4 unk23C;                   /* case 3 src B */
    char unk24C[0x410 - 0x24C];
    Quad4 unk410;                   /* case 1/6 src A */
    char unk420[0x434 - 0x420];
    Quad4 unk434;                   /* case 1/6 src B */
    char unk444[0x544 - 0x444];
    int unk544;                     /* alpha ramp counter */
    char unk548[0x554 - 0x548];
    float unk554;                   /* alpha ramp clamp float */
} GlHudObj;

typedef struct GlHudVt {
    char unkF8pad[0xF8];
    short unkF8;                    /* 0xF8 element-offset (short) */
    char unkFApad[0xFC - 0xFA];
    void (*unkFC)(void *);          /* 0xFC handler */
    short unk100;                   /* 0x100 element-offset (short) */
    char unk102pad[0x104 - 0x102];
    void (*unk104)(void *);         /* 0x104 handler */
} GlHudVt;

void gl_func_00007344(GlHudObj *arg0, u32 arg1, void *arg2) {
    void *target;
    Quad4 spA;
    Quad4 spB;
    int mode;
    int alpha;

    target = NULL;
    switch (arg1) {
    case 0:
    case 5:
        mode = *(int *)((char *)&D_00000000 + 0x34);
        if (mode == 3 || mode == 2) {
            spA = arg0->unk140;
            target = (char *)arg0 + 0x618;
            spB = arg0->unk164;
        } else {
            spA = arg0->unk140;
            target = (char *)arg0 + 0x600;
            spB = arg0->unk164;
        }
        if (mode != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unkFC(arg0->unk28->unkF8 + (char *)arg0);
        break;
    case 1:
    case 6:
        spA = arg0->unk410;
        target = (char *)arg0 + 0x648;
        spB = arg0->unk434;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unkFC(arg0->unk28->unkF8 + (char *)arg0);
        break;
    case 2:
        spA = arg0->unk188;
        target = (char *)arg0 + 0x630;
        spB = arg0->unk1AC;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        break;
    case 3:
        spA = arg0->unk218;
        target = (char *)arg0 + 0x678;
        spB = arg0->unk23C;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        arg0->unk28->unk104(arg0->unk28->unk100 + (char *)arg0);
        break;
    case 4:
        spA = arg0->unk1D0;
        target = (char *)arg0 + 0x660;
        spB = arg0->unk1F4;
        if (*(int *)((char *)&D_00000000 + 0x34) != 2) {
            gl_func_00000000(arg0);
        }
        break;
    }
    if (target != NULL) {
        alpha = arg0->unk544;
        if (alpha < 255) {
            alpha += 2;
            arg0->unk544 = alpha;
            if (alpha >= 255) {
                alpha = 255;
                arg0->unk544 = 255;
                arg0->unk554 = 175.0f;
            }
        }
        gl_func_00000000(&D_00000000, alpha, &spA, &spB);
        gl_func_00000000(target);
        gl_func_00000000(target, 0xA0, arg2, 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007344);
#endif

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

#ifdef NON_MATCHING
/* PASS-1 2026-06-10 (big-swing): FULL m2c graft, THREE small sparse
 * jumptables synthesized (bounds 6/4/4, full head coverage; order
 * approximate). First C body for this fn.
 * PASS-2 2026-06-20 (agent-e): added explicit `case 2/3/4: break;` to
 * switch1 (on field 0x4E0) so IDO emits the bounds-6 indirect jumptable
 * (sltiu at,v0,6; jr t7) matching the target head instead of a beql
 * cascade. True opcode-alignment 30.2%->32.2% (exact-byte still ~2.8% —
 * fuzzy% overstates). Residual: pervasive scattered regalloc (v0/v1 swaps,
 * a0-vs-s0 base, branch-likely delay-fill order) + switch2/switch4
 * jumptable case-data ambiguity (USO base-0 jtbl resolved at load, absent
 * from .s). Genuine regalloc/scheduling cap.
 * PASS-3 2026-07-11 (agent-f): WIDTH-FIX. m2c had mis-typed the float
 * fields (arg0+0x534/0x538/0x548/0x54C/0x550, all swc1 in target) and the
 * global camera/alpha float (&D_00000000+0, lwc1/swc1 in target) as s32,
 * emitting li+sw and lw+cvt.s.w instead. Retyped to f32 -> swc1/lwc1 direct,
 * removing all bogus int-to-float conversions. Fuzzy 56.97 -> 63.88%.
 * Residual is the unresolvable USO load-time jumptables + regalloc cap. */
void gl_func_000076F0(char *arg0) {
    s32 sp24;
    s32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f2;
    s32 temp_lo;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t9;
    s32 temp_v0_10;
    s32 temp_v0_13;
    s32 temp_v0_15;
    s32 temp_v0_2;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    u32 temp_t7;
    u32 temp_t7_2;
    char *temp_v0;
    char *temp_v0_11;
    char *temp_v0_12;
    char *temp_v0_14;
    char *temp_v0_16;
    char *temp_v0_17;
    char *temp_v0_18;
    char *temp_v0_19;
    char *temp_v0_20;
    char *temp_v0_21;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_9;

    if (*(s32 *)((char *)(arg0) + 0x30) == 0) {
        temp_t7 = *(s32 *)((char *)(arg0) + 0x4E0);
        switch (temp_t7) {                          /* switch 1 */
        case 0:                                     /* switch 1 */
            temp_t9 = *(s32 *)((char *)(arg0) + 0x4E4) - 1;
            *(s32 *)((char *)(arg0) + 0x4E4) = temp_t9;
            if (temp_t9 <= 0) {
                temp_v0 = *(s32 *)((char *)(arg0) + 0x28);
                *(s32 *)((char *)(arg0) + 0x4E0) = 1U;
                *(s32 *)((char *)(arg0) + 0x4E4) = (s32) (*(s32 *)((char *)(arg0) + 0x4E8) * 4);
                ((void (*)())*(s32 *)((char *)(temp_v0) + 0x94))(*(s16 *)((char *)(temp_v0) + 0x90) + arg0);
            }
            break;
        case 1:                                     /* switch 1 */
            temp_v1 = *(s32 *)((char *)(arg0) + 0x4E8);
            temp_v0_2 = *(s32 *)((char *)(arg0) + 0x4E4);
            temp_t6 = temp_v0_2 - 1;
            temp_lo = temp_t6 / temp_v1;
            sp24 = temp_v0_2 / temp_v1;
            *(s32 *)((char *)(arg0) + 0x4E4) = temp_t6;
            sp20 = temp_lo;
            if (*(s32 *)((char *)(arg0) + 0x4F0) & 0x10000) {
                if (sp24 != temp_lo) {
                    *(s32 *)((char *)(arg0) + 0x50C) = 0;
                    switch (sp20) {                 /* switch 2 */
                    case 0:                         /* switch 2 */
                        func_00000000(0x11);
                        *(f32 *)((char *)(arg0) + 0x534) = 1.0f;
                        *(f32 *)((char *)(arg0) + 0x538) = 1.0f;
                        *(f32 *)((char *)(arg0) + 0x548) = 160.0f;
                        *(f32 *)((char *)(arg0) + 0x550) = 0.0f;
                        *(f32 *)((char *)(arg0) + 0x54C) = 120.0f;
                        if (*(s32 *)((char *)&D_00000000 + 0x34) == 2) {
                            *(f32 *)((char *)(arg0) + 0x54C) = 60.0f;
                        }
                        goto block_13;
                    case 2:                         /* switch 1 */
                    case 1:                         /* switch 2 */
                        *(s32 *)((char *)(arg0) + 0x540) = 0xFF;
                        *(f32 *)((char *)(arg0) + 0x534) = 1.0f;
                        *(f32 *)((char *)(arg0) + 0x538) = 1.0f;
                        func_00000000(0x12);
                        func_00000000(0x10);
                        goto block_13;
                    case 3:                         /* switch 1 */
                    /* dup case 2 */
                        *(s32 *)((char *)(arg0) + 0x540) = 0xFF;
                        *(f32 *)((char *)(arg0) + 0x534) = 1.0f;
                        *(f32 *)((char *)(arg0) + 0x538) = 1.0f;
                        func_00000000(0x12);
                        goto block_13;
                    case 4:                         /* switch 1 */
                    /* dup case 3 */
                        temp_v0_3 = *(s32 *)((char *)(arg0) + 0x28);
                        if (((int (*)())*(s32 *)((char *)(temp_v0_3) + 0x9C))(*(s16 *)((char *)(temp_v0_3) + 0x98) + arg0) != 0) {
                            var_v0 = *(s32 *)((char *)(arg0) + 0x518);
                            if (var_v0 != 0) {
                                temp_t2 = var_v0 - 1;
                                *(s32 *)((char *)(arg0) + 0x518) = temp_t2;
                                var_v0 = temp_t2;
                            }
                            if (var_v0 == 0) {
                                *(s32 *)((char *)(arg0) + 0x500) = 1;
                            }
                            *(s32 *)((char *)(arg0) + 0x4E4) = (s32) (*(s32 *)((char *)(arg0) + 0x4E4) - 1);
                            *(s32 *)((char *)(arg0) + 0x4EC) = (s32) (*(s32 *)((char *)(arg0) + 0x4EC) + 1);
                        }
                        if ((*(s32 *)((char *)(arg0) + 0x4EC) >= 0x3D) && (func_00000000(0, 0x40100) != 0)) {
                            *(s32 *)((char *)(arg0) + 0x4E4) = 0;
                        }
                        if (*(s32 *)((char *)(arg0) + 0x4E4) < 0) {
                            temp_v0_4 = *(s32 *)((char *)(arg0) + 0x28);
                            *(s32 *)((char *)(arg0) + 0x4E0) = 7U;
                            ((void (*)())*(s32 *)((char *)(temp_v0_4) + 0xB4))(*(s16 *)((char *)(temp_v0_4) + 0xB0) + arg0);
                        }
                        break;
                    }
                } else {
                default:                            /* switch 2 */
block_13:
                    if ((sp20 == 0) && (*(s32 *)((char *)(arg0) + 0x50C) > 0)) {
                        func_00000000(arg0 + 0x5A0);
                        func_00000000(arg0 + 0x5B8);
                        func_00000000(arg0 + 0x5D0);
                        func_00000000(arg0 + 0x5E8);
                    }
                    *(s32 *)((char *)(arg0) + 0x50C) = (s32) (*(s32 *)((char *)(arg0) + 0x50C) + 1);
                    goto block_17;
                }
            } else {
block_17:
                if ((sp24 == 1) && (sp20 == 0)) {
                    func_00000000(0, 1);
                    if (*(s32 *)((char *)(arg0) + 0x4F0) & 0x10000) {
                        func_00000000(arg0 + 0x588);
                    }
                    *(s32 *)((char *)&D_00000000 + 0x78) = 0;
                    *(s32 *)((char *)(arg0) + 0x4DC) = 1;
                    func_00000000(*(s32 *)((char *)&D_00000000 + 0x138));
                }
                if (-*(s32 *)((char *)(arg0) + 0x4E8) >= *(s32 *)((char *)(arg0) + 0x4E4)) {
                    *(s32 *)((char *)(arg0) + 0x4E0) = 2U;
                }
            }
            break;
        case 5:                                     /* switch 1 */
            temp_v0_5 = *(s32 *)((char *)(arg0) + 0x28);
            if (((int (*)())*(s32 *)((char *)(temp_v0_5) + 0xA4))(*(s16 *)((char *)(temp_v0_5) + 0xA0) + arg0) != 0) {
                var_v0_2 = *(s32 *)((char *)(arg0) + 0x518);
                temp_t3 = var_v0_2 - 1;
                if (var_v0_2 != 0) {
                    *(s32 *)((char *)(arg0) + 0x518) = temp_t3;
                    var_v0_2 = temp_t3;
                }
                if (var_v0_2 == 0) {
                    *(s32 *)((char *)(arg0) + 0x500) = 1;
                }
                *(s32 *)((char *)(arg0) + 0x4E4) = (s32) (*(s32 *)((char *)(arg0) + 0x4E4) - 1);
                *(s32 *)((char *)(arg0) + 0x4EC) = (s32) (*(s32 *)((char *)(arg0) + 0x4EC) + 1);
            }
            if ((*(s32 *)((char *)(arg0) + 0x4EC) >= 0x1F) && (func_00000000(0, 0x40100) != 0)) {
                *(s32 *)((char *)(arg0) + 0x4E4) = 0;
            }
            if (*(s32 *)((char *)(arg0) + 0x4E4) < 0) {
                temp_v0_6 = *(s32 *)((char *)(arg0) + 0x28);
                *(s32 *)((char *)(arg0) + 0x4E0) = 7U;
                ((void (*)())*(s32 *)((char *)(temp_v0_6) + 0xCC))(*(s16 *)((char *)(temp_v0_6) + 0xC8) + arg0);
            }
            break;
        case 2:                                     /* switch 1 */
        case 3:                                     /* switch 1 */
        case 4:                                     /* switch 1 */
            break;
        }
        if ((*(s32 *)((char *)(arg0) + 0x500) != 0) && ((temp_v0_7 = *(s32 *)((char *)(arg0) + 0x28), ((void (*)())*(s32 *)((char *)(temp_v0_7) + 0xE4))(*(s16 *)((char *)(temp_v0_7) + 0xE0) + arg0), temp_v0_8 = *(s32 *)((char *)(arg0) + 0x4F8), (temp_v0_8 == 0)) || (temp_v0_8 == 5))) {
            func_00000000(arg0);
        }
        if (*(s32 *)((char *)(arg0) + 0x4E0) == 7) {
            temp_v0_9 = *(s32 *)((char *)(arg0) + 0x28);
            ((void (*)())*(s32 *)((char *)(temp_v0_9) + 0xAC))(*(s16 *)((char *)(temp_v0_9) + 0xA8) + arg0);
        }
    }
    temp_v1_2 = *(s32 *)((char *)(arg0) + 0x4DC);
    switch (temp_v1_2) {                            /* switch 3; irregular */
    case 1:                                         /* switch 3 */
        if (*(s32 *)((char *)(arg0) + 0x4F0) & 0x10000) {
            temp_f0 = *(f32 *)((char *)&D_00000000 + 0);
            if (temp_f0 < 1.0f) {
                *(f32 *)((char *)&D_00000000 + 0) = (f32) (temp_f0 + *(f32 *)((char *)&D_00000000 + 0xE2C));
            }
            temp_f2 = *(f32 *)((char *)&D_00000000 + 0xE30);
            if (*(s32 *)((char *)&D_00000000 + 0x34) != 3) {
                temp_f0_2 = *(f32 *)((char *)&D_00000000 + 0);
                if (temp_f0_2 < 1.0f) {
                    *(f32 *)((char *)&D_00000000 + 0) = (f32) (temp_f0_2 + temp_f2);
                }
            }
            temp_f0_3 = *(f32 *)((char *)&D_00000000 + 0);
            if (temp_f0_3 < 1.0f) {
                *(f32 *)((char *)&D_00000000 + 0) = (f32) (temp_f0_3 + temp_f2);
            }
        }
        if ((*(s32 *)((char *)(arg0) + 0x4DC) != 0) && (*(s32 *)((char *)(arg0) + 0x30) == 0)) {
            temp_v0_10 = *(s32 *)((char *)(arg0) + 0x4F4);
            if (temp_v0_10 > 0) {
                temp_t2_2 = temp_v0_10 - 1;
                *(s32 *)((char *)(arg0) + 0x4F4) = temp_t2_2;
                if (temp_t2_2 == 0) {
                    if (*(s32 *)((char *)(arg0) + 0x4F0) & 0x100000) {
                        temp_v0_11 = *(s32 *)((char *)(arg0) + 0x28);
                        ((void (*)())*(s32 *)((char *)(temp_v0_11) + 0xBC))(*(s16 *)((char *)(temp_v0_11) + 0xB8) + arg0);
                        func_00000000(arg0, -1, 0);
                    } else {
                        temp_v0_12 = *(s32 *)((char *)(arg0) + 0x28);
                        ((void (*)())*(s32 *)((char *)(temp_v0_12) + 0xC4))(*(s16 *)((char *)(temp_v0_12) + 0xC0) + arg0);
                    }
                }
            }
        }
        break;
    case 2:                                         /* switch 3 */
        if ((*(s32 *)((char *)(arg0) + 0x4F0) & 0x10000) && (*(s32 *)((char *)(arg0) + 0x500) != 0)) {
            temp_f0_4 = *(f32 *)((char *)&D_00000000 + 0);
            if (temp_f0_4 > 0.0f) {
                *(f32 *)((char *)&D_00000000 + 0) = temp_f0_4 - *(f32 *)((char *)&D_00000000 + 0xE34);
                if (*(f32 *)((char *)&D_00000000 + 0) < 0.0f) {
                    *(f32 *)((char *)&D_00000000 + 0) = 0.0f;
                }
            }
            if (*(f32 *)((char *)&D_00000000 + 0) <= 0.0f) {
                temp_f0_5 = *(f32 *)((char *)&D_00000000 + 0);
                if (temp_f0_5 > 0.0f) {
                    *(f32 *)((char *)&D_00000000 + 0) = (f32) (temp_f0_5 - *(f32 *)((char *)&D_00000000 + 0xE38));
                    if (*(f32 *)((char *)&D_00000000 + 0) < 0.0f) {
                        *(f32 *)((char *)&D_00000000 + 0) = 0.0f;
                    }
                }
            }
            if ((*(s32 *)((char *)(arg0) + 0x4F8) == 0) && (*(s32 *)((char *)&D_00000000 + 0x34) == 3)) {
                temp_f0_6 = *(f32 *)((char *)&D_00000000 + 0);
                if (temp_f0_6 < 1.0f) {
                    *(f32 *)((char *)&D_00000000 + 0) = (f32) (temp_f0_6 + *(f32 *)((char *)&D_00000000 + 0xE3C));
                }
            }
        }
        break;
    }
    if ((*(s32 *)((char *)(arg0) + 0x4DC) != 2) && (*(s32 *)((char *)(arg0) + 0x4D8) == 0)) {
        if (*(s32 *)((char *)(arg0) + 0x30) == 0) {
            if ((func_00000000(*(s32 *)((char *)&D_00000000 + 0x190)) != 0) && (*(s32 *)((char *)(arg0) + 0x48) != 0)) {
                temp_v0_13 = func_00000000(0, 0x40000);
                *(s32 *)((char *)(arg0) + 0x514) = temp_v0_13;
                if (temp_v0_13 != 0) {
                    temp_v0_14 = *(s32 *)((char *)(arg0) + 0x28);
                    ((void (*)())*(s32 *)((char *)(temp_v0_14) + 0x8C))(*(s16 *)((char *)(temp_v0_14) + 0x88) + arg0);
                    func_00000000(arg0);
                    func_00000000(*(s32 *)((char *)&D_00000000 + 0x138));
                }
            }
        } else {
            temp_v0_15 = *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x48)) + 0x80);
            if (temp_v0_15 == 0) {
                if (func_00000000(0, 0x100) != 0) {
                    *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x48)) + 0x80) = 0x100;
                }
                if (func_00000000(0, 0x40000) != 0) {
                    *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x48)) + 0x80) = 0x40000;
                }
            } else if (func_00000000(0, temp_v0_15) != 0) {
                temp_v0_16 = *(s32 *)((char *)(arg0) + 0x28);
                ((void (*)())*(s32 *)((char *)(temp_v0_16) + 0xD4))(*(s16 *)((char *)(temp_v0_16) + 0xD0) + arg0);
                *(s32 *)((char *)(*(s32 *)((char *)(arg0) + 0x48)) + 0x80) = 0;
            }
        }
    }
    temp_t7_2 = *(s32 *)((char *)(arg0) + 0x4D8);
    switch (temp_t7_2) {                            /* switch 4 */
    case 0:                                         /* switch 4 */
        temp_v0_17 = *(s32 *)((char *)(arg0) + 0x28);
        ((void (*)())*(s32 *)((char *)(temp_v0_17) + 0x114))(*(s16 *)((char *)(temp_v0_17) + 0x110) + arg0);
        break;
    case 1:                                         /* switch 4 */
        temp_v0_18 = *(s32 *)((char *)(arg0) + 0x28);
        ((void (*)())*(s32 *)((char *)(temp_v0_18) + 0x11C))(*(s16 *)((char *)(temp_v0_18) + 0x118) + arg0);
        break;
    case 2:                                         /* switch 4 */
        temp_v0_19 = *(s32 *)((char *)(arg0) + 0x28);
        ((void (*)())*(s32 *)((char *)(temp_v0_19) + 0x124))(*(s16 *)((char *)(temp_v0_19) + 0x120) + arg0);
        break;
    case 3:                                         /* switch 4 */
        temp_v0_20 = *(s32 *)((char *)(arg0) + 0x28);
        ((void (*)())*(s32 *)((char *)(temp_v0_20) + 0x12C))(*(s16 *)((char *)(temp_v0_20) + 0x128) + arg0);
        break;
    }
    if ((*(s32 *)((char *)(arg0) + 0x4F0) & 0x80000) && ((func_00000000(0, 0x300) != 0) || (func_00000000(0, 0x40000) != 0))) {
        temp_v0_21 = *(s32 *)((char *)(arg0) + 0x28);
        ((void (*)())*(s32 *)((char *)(temp_v0_21) + 0xDC))(*(s16 *)((char *)(temp_v0_21) + 0xD8) + arg0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000076F0);
#endif

// gl_func_00007FF4 — FULL DECODE, 99.98% (220/222 words byte-exact).
// Logic verified exact: new_var-CSE for case-3 (&D base shared by the 0x34 flag
// + ((int*)&D)[idx] array load), s16 vtable offsets (0xE8/0x108/0xF0), float-trunc
// call args ((s32)*(f32*)…0x548/0x54C), frame -0x90 via the volatile pad layout
// (pu[9] upper dead-local gap → sp8C@0x8C; pl0 → sp58@0x58). Sole residual: the
// temp_lo spill lands at sp+0x48 vs target sp+0x3C — an IDO stack-spill-allocator
// slot diff (4 lw/sw words). Resists pad relayout (pads move spill+arg-spills
// together) AND the permuter (floored at score 130 — regalloc-renumber class).
/* gl_func_00007FF4 — EXACT MATCH 222/222 words (2026-07-03, agent-e w5).
 * Was 218/222: temp_lo jal-delay spill homed at sp+0x48 vs target sp+0x3C.
 * LEVER (new, cracked the documented "regalloc-renumber" cap): NAMED-SCALAR
 * DECL-ORDER SLOT MAP — non-addressed named scalars still reserve decl-order
 * homes (framesize-4, -8, ... after the addressed/volatile locals), and a
 * named var's caller-save spill goes to ITS OWN named home. Moving `temp_lo`
 * 3 decl positions later (after temp_a2/temp_a3/new_var) moved its home
 * 0x48->0x3C. Verified word-exact vs own .s on clean rebuild. */

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef int (*GP_00007FF4)();
extern int gl_func_00000000();
void gl_func_00007FF4(char *arg0) {
    int *sp8C;
    volatile int pu0, pu1, pu2, pu3, pu4, pu5, pu6, pu7, pu8;
    f32 sp58[4];
    volatile int pl0;
    s32 sp3C;
    int *temp_v0;
    int *temp_a2;
    int *temp_a3;
    int *new_var;
    int temp_lo;
    f32 temp_f0;

    if (FW(arg0, 0x4F0) & 0x01000000) {
        sp58[0] = 0.0f;
        sp58[1] = 0.0f;
        sp58[2] = 0.0f;
        sp58[3] = 0.0f;
        gl_func_00000000(&D_00000000, 0xFF, sp58);
        gl_func_00000000(&D_00000000, 0, 0x77, 0x13F, 0x78, 0x10001);
    }
    if (FW(arg0, 0x30) == 0) {
        if (FW(arg0, 0x4F0) & 0x10000) {
            gl_func_00000000(FW(arg0, 0x568));
            gl_func_00000000(FW(arg0, 0x568));
        }
        switch (FW(arg0, 0x4E0)) {                   /* irregular */
        case 0:
            temp_v0 = (int *)FW(arg0, 0x28);
            ((GP_00007FF4)FW(temp_v0, 0xF4))(*(s16 *)((char *)temp_v0 + 0xF0) + (int)arg0);
            break;
        case 1:
            if ((FW(arg0, 0x4F0) & 0x10000) && (FW(arg0, 0x4F0) & 0x400000)) {
                temp_lo = (s32)FW(arg0, 0x4E4) / (s32)FW(arg0, 0x4E8);
                if (temp_lo < 4) {
                    temp_f0 = *(f32 *)((char *)&D_00000000 + 0xE50);
                    FW(arg0, 0x540) = FW(arg0, 0x540) - 4;
                    *(f32 *)((char *)arg0 + 0x534) = *(f32 *)((char *)arg0 + 0x534) + temp_f0;
                    *(f32 *)((char *)arg0 + 0x538) = *(f32 *)((char *)arg0 + 0x538) + temp_f0;
                    if (temp_lo != -1) {
                        sp8C = (int *)((int)arg0 + temp_lo * 0x18 + 0x588);
                    } else {
                        sp8C = (int *)((int)arg0 + 0x588);
                    }
                    sp3C = temp_lo;
                    gl_func_00000000(sp8C);
                    if ((temp_lo == 0) || (temp_lo == -1)) {
                        temp_a2 = (int *)((int)arg0 + 0xF8);
                        temp_a3 = (int *)((int)arg0 + 0x11C);
                        gl_func_00000000(sp8C, FW(arg0, 0x540), temp_a2, temp_a3);
                        gl_func_00000000(sp8C, (s32)*(f32 *)((char *)arg0 + 0x548), (s32)*(f32 *)((char *)arg0 + 0x54C), 3);
                        if (*(s32 *)((char *)&D_00000000 + 0x34) == 2) {
                            gl_func_00000000(sp8C, FW(arg0, 0x540), temp_a2, temp_a3);
                            gl_func_00000000(sp8C, (s32)*(f32 *)((char *)arg0 + 0x548), (s32)(*(f32 *)((char *)arg0 + 0x54C) + 120.0f), 3);
                        }
                    } else {
                        gl_func_00000000(sp8C, FW(arg0, 0x540), (int)arg0 + 0xB0, (int)arg0 + 0xD4);
                        gl_func_00000000(sp8C, 0xA0, 0xA0, 3);
                    }
                    if (sp3C != 0) {
                        gl_func_00000000((int)arg0 + 0x5E8);
                        gl_func_00000000((int)arg0 + 0x5E8, 0xFF, (int)arg0 + 0x68, (int)arg0 + 0x8C);
                        gl_func_00000000((int)arg0 + 0x5E8, 0xA8, 0x50, 3);
                    }
                }
            }
            break;
        case 3:
            new_var = &D_00000000;
            if (!(FW(arg0, 0x4F0) & 0x04000000)) {
                temp_v0 = (int *)FW(arg0, 0x28);
                ((GP_00007FF4)FW(temp_v0, 0x10C))(*(s16 *)((char *)temp_v0 + 0x108) + (int)arg0, FW(arg0, 0x4F8), (s32)*(f32 *)((char *)arg0 + 0x54C));
                if (*(s32 *)((char *)new_var + 0x34) == 2) {
                    temp_v0 = (int *)FW(arg0, 0x28);
                    ((GP_00007FF4)FW(temp_v0, 0x10C))(*(s16 *)((char *)temp_v0 + 0x108) + (int)arg0, ((int *)new_var)[FW(arg0, 0x4F8)], (s32)(*(f32 *)((char *)arg0 + 0x54C) + 120.0f));
                }
            }
            break;
        }
    }
    temp_v0 = (int *)FW(arg0, 0x28);
    ((GP_00007FF4)FW(temp_v0, 0xEC))(*(s16 *)((char *)temp_v0 + 0xE8) + (int)arg0);
}

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
 * D_00000000+0x134 (re-read fresh at every use — NOT cached in a saved reg;
 * the saved reg s0 holds the original arg a0), calls gl_func_00000000 5 times
 * with state-derived args, mutates state flags between calls.
 *
 * STATE() re-derefs the global each use so IDO rematerializes the load rather
 * than caching the pointer across calls (this matched the per-block reload
 * shape in the target). Remaining residual is a result-coloring cap: IDO holds
 * &D_00000000 in s0 here, but the target holds the arg a0 in s0 — values all
 * match, only which saved reg holds which differs (coloring-immune). */
extern int gl_func_00000000();
void gl_func_000083CC(int *a0) {
#define STATE (*(int**)((char*)&D_00000000 + 0x134))
    int *t6 = *(int**)((char*)STATE + 0x108);
    int *a3 = *(int**)((char*)STATE + 0xC4);
    int t7 = *(int*)((char*)t6 + 0x70);
    int v0_call1 = gl_func_00000000(STATE, 1,
                                    *(int*)((char*)STATE + 0x80),
                                    a3,
                                    *(int*)((char*)a3 + 0x800));
    int *t9 = *(int**)((char*)STATE + 0x108);
    *(int**)((char*)a0 + 0x520) = t9;
    *(int*)((char*)t9 + 0x18) &= ~8;
    {
        int *v1 = *(int**)((char*)a0 + 0x520);
        *(int*)((char*)v1 + 0x18) = *(int*)((char*)v1 + 0x18) & ~4;
    }
    {
        int v0_call2 = gl_func_00000000(STATE, 0x70, t7);
        *(int*)((char*)a0 + 0x51C) = v0_call2;
    }
    {
        int v0_call3 = gl_func_00000000(0x80);
        int *obj;
        int *side;
        *(int*)((char*)STATE + 0x108) = v0_call3;
        if (v0_call3 != 0) {
            gl_func_00000000(v0_call3, 1);
        }
        obj = (int*)gl_func_00000000(0, v0_call3,
                         *(int*)((char*)STATE + 0xC4),
                         *(int*)((char*)a0 + 0x51C),
                         t7, v0_call1);
        side = *(int**)((char*)STATE + 0x84);
        gl_func_00000000((char*)side + 0x10, obj);
        if (*(int*)((char*)obj + 0x14) != 0) *(int*)((char*)obj + 4) = 1;
        *(int*)((char*)obj + 0x14) = (int)side;
    }
#undef STATE
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

/* gl_func_000085B0 — EXACT MATCH 46/46 words (2026-07-03, agent-e w5).
 * Was 28/46: whole-body temp-reg cascade (+1/+2) plus p2 spill 0x24 vs 0x20.
 * ROOT: target reuses ONE named temp (v0) for the three reloaded pointers
 * (*(state+0xC4), *(state+0xCC), *(*(arg0+0x528)+8)) and homes `state` in v1.
 * FIX: single function-scope `int *q` assigned at all 3 sites (replacing two
 * anonymous temps + the block-scoped `t`). q (6 refs) outranks state at
 * coloring -> q=v0, state=v1, t6.. cascade snaps. q's decl between `p` and
 * the block-scoped `p2` also shifts p2's named home 0x24->0x20 (q's dead
 * colored slot absorbs 0x24), fixing the spill slot. First-variant match. */
void gl_func_000085B0(int *arg0, int arg1) {
    char *state;
    char *p;
    int *q;

    gl_func_00000000(arg0);
    state = *(char**)((char*)&D_00000000 + 0x134);
    q = *(int**)(state + 0xC4);
    p = *(char**)((char*)q + 0x800);
    if (*(int**)((char*)*(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8) + 0x8) != 0) {
        char *p2;
        q = *(int**)(state + 0xCC);
        p2 = *(char**)((char*)q + 0x800);
        gl_func_00000000(p2, *(int*)(p2 + 0x34));
        q = *(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8);
        gl_func_00000000(p2, *(int*)((char*)q + 0x8), *(int*)((char*)q + 0x4));
    }
    gl_func_00000000(p, 0);
    gl_func_00000000(p,
        *(int*)((char*)&D_00000000 + 0x168),
        *(int*)((char*)&D_00000000 + 0x170));
    gl_func_00000000(arg0);
    *(int*)((char*)arg0 + 0x4F4) = arg1 & 0xFFFF;
}

/* gl_func_00008674: RECONSTRUCTED 2026-07-11. NOT caller-set — the prior
 * comment mis-read the prologue. The dispatcher pointer comes from a GLOBAL:
 *   v1 = &D_00000000 (absolute base, links at 0)
 *   v0 = *(int**)(v1 + 0x28)          (the object)
 * then calls obj->fn64 with arg = &D_00000000 + (s16)obj->off60 (addu reuses
 * the live base register v1). The incoming $a0 is homed to 0x18(sp) via
 * &unused. This is a global-table indirect dispatch, coaxable in C. */
int gl_func_00008674(int unused) {
    int *obj = *(int**)((char*)&D_00000000 + 0x28);
    volatile int *spill = &unused;
    (void)spill;
    return ((int (*)(int))obj[0x64/4])((int)((char*)&D_00000000 + *(s16*)((char*)obj + 0x60)));
}

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
 * MATCHED 2026-06-21: as1 FP-setup scheduler tie (lwc1 f550 vs mtc1 four
 * order swap) flipped by inlining the f550 load into the comparison
 * condition `(f550 = *...) < four`, forcing `four` materialization first.
 * Byte-exact; only reloc residue is benign &D_00000000+0xE60. */
void gl_func_0000871C(int *a0) {
    float four = 4.0f;
    float f550;
    if ((f550 = *(float*)((char*)a0 + 0x550)) < four) {
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
/* gl_func_000088B4: 36-insn constructor + list insert. MATCHED 2026-06-21 via
 * masked-twin port from game_uso_func_00003A28 (byte-exact donor; same
 * eddproc_uso_func_000003BC family). The prior duplicate struct-typed body sat
 * in a dead #else/#ifdef branch (never compiled) while the active body produced
 * frame 0x30; the donor's flat int* form (decl-order p2,head,p1; p1-reuse-for-arg0;
 * condition re-load) gives the tight two-web spill (frame 0x28). jal targets are
 * USO placeholders (jal 0 in both build and expected) -> reloc-blind exact. */
extern int gl_func_00000000();
int *gl_func_000088B4(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)gl_func_00000000(0x40);
    if (p1 != 0) {
        gl_func_00000000(p1);
        *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        gl_func_00000000((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}

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

/* game_libs_func_00070A0C RE-HOMED 2026-06-10: it was gl_func_00070A14's
 * stolen prologue (lui/mtc1 FP-constant setup) emitting at the wrong
 * position (build 0x8938); the words are now prepended to 70A14's .s
 * in post1c where ROM has them. (Relayout ledger event.) */

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006BA74);


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00051654);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0004E57C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0003FB64);

/* game_libs_func_0002DF64 (ONE word, mtc1 a1,$f12 -- the stolen leading
 * insn of gl_func_0002DF68): re-homed during the relayout session as the
 * prepended first word of gl_func_0002DF68.s in post.c (74EFC-style
 * leading-insn boundary correction). The orphan INCLUDE that used to sit
 * here emitted at game_libs.c.o offset 0x8944 (= TRUNCATE_TEXT cap) and
 * never reached the link; removed with the re-home. */

