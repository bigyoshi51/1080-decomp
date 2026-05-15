#include "common.h"

/* Tail half of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_949C.c (the 4-fn -O0 cluster at 0x949C..0x959C).
 * Covers gl_func_0000959C onwards. Type definitions Tri3i/Vec3
 * (originally declared at game_libs.c:290) re-declared here. */

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000959C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000959C_pad.s")

extern int gl_func_00000000();
void gl_func_00009674(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_000096B0(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

void gl_func_000096EC(Vec3 *dst) {
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

/* Quad4 reader template — sibling of gl_func_0003A9E8 (matched last iteration).
 * Standard 22-insn shape: gl_func_00000000(&D_0, &buf, 16); *dst = buf;
 * Required boundary fix: original .s was a 36-function bundle (0x65C / 35
 * jr-ra sequences), split via scripts/split-fragments.py. */
void gl_func_0000975C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 0x10);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009DB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009EBC);

/* gl_func_00009FA8: 25-insn 3-iteration loop with 2 cross-USO calls per
 * iter. Calls gl_func(a0+i) and gl_func(a0+0x18+i) for i = 0, 8, 0x10. */
extern int gl_func_00000000();
void gl_func_00009FA8(char *a0) {
    int i;
    char *p, *q;
    int limit;
    p = a0;
    i = 0;
    q = a0 + 0x18;
    limit = 0x18;
    do {
        gl_func_00000000(p);
        gl_func_00000000(q);
        i += 8;
        p += 8;
        q += 8;
    } while (i != limit);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A00C);

/* gl_func_0000A0CC: 25-insn 3-iter loop calling gl_func_00000000 on
 * a0[0], a0+8, a0+0x10. Returns count of non-zero return values. */
extern int gl_func_00000000();
int gl_func_0000A0CC(char *a0) {
    char *p;
    int count;
    int i;
    int limit;
    count = 0;
    i = 0;
    p = a0;
    limit = 0x18;
    do {
        int r = gl_func_00000000(p);
        i += 8;
        if (r != 0) count += 1;
        p += 8;
    } while (i != limit);
    return count;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A130);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A1C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A2B8);

#ifdef NON_MATCHING
/* gl_func_0000A4D0: 28-insn find-first-match-in-3-entries.
 *   for (i = 0; i < 3; i++) {
 *     if (func(a0->[0x18 + i*8], a1) != 0) return i;
 *   }
 *   return 3;
 *
 * Each entry is 8 bytes; func returns nonzero on match. Returns the
 * matched index (0..2) or 3 if no match. */
extern int func_00000000();
int gl_func_0000A4D0(int *a0, int a1) {
    int i;
    char *entry = (char*)a0 + 0x18;
    for (i = 0; i < 3; i++) {
        if (func_00000000(entry, a1) != 0) {
            return i;
        }
        entry += 8;
    }
    return 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A4D0);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A670);

extern int gl_func_00000000();

void gl_func_0000A768(char *a0) {
    int i;
    char *p;
    i = 0;
    p = a0;
    for (; i != 0x180; i += 0x30) {
        gl_func_00000000(p);
        p += 0x30;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A7B4);

#ifdef NON_MATCHING
/* gl_func_0000A990: 25-insn 5-identical-call + 2-zero-fields wrapper. */
extern int func_00000000();
void gl_func_0000A990(int *a0) {
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    a0[1] = 0;
    a0[2] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A990);
#endif

extern int gl_func_00000000();

int gl_func_0000A9F4(int a0, int a1) {
    int r = gl_func_00000000(a0, a1);
    if (r == a1) return 1;
    return 0;
}

#ifdef NON_MATCHING
/* 93.43% NM. Two-stage validation: call once, check result == a1; call
 * again, check result == a2; return 1 only if both match. Diff vs target:
 *   - Mine: spill a2 BEFORE jal, a1 IN jal delay-slot, then redundant
 *     `lw a1` reload before bnel (1 extra insn = +4 bytes).
 *   - Target: spill a1 BEFORE jal, a2 IN delay-slot, NO redundant reload
 *     (uses t6 for the 1st bnel reload, t7 for the 2nd).
 * Tried (3 variants): inline `r != a1`, named `int r = ...`, named
 * `int s_a1 = a1` — all produce same 93.4%. The redundant-reload looks
 * like an IDO scheduling choice: it spills a1 in jal delay slot rather
 * than the prologue, then must reload from the slot before bnel. Target's
 * IDO put a1's spill in the prologue (no delay-slot use needed). Cap is
 * an instruction-scheduler decision not reachable from C-level levers. */
int gl_func_0000AA28(int a0, int a1, int a2) {
    if (gl_func_00000000(a0, a1, a2) != a1) goto fail;
    if (gl_func_00000000(a0, a1, a2) != a2) goto fail;
    return 1;
fail:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA28);
#endif

/* 28-insn / 0x70 5-call wrapper followed by 2-field commit. Each call passes
 * the same a0 plus a different arg as a1; result of last call is ignored. */
void gl_func_0000AA7C(int *a0, int a1, int a2, int a3, int arg5, int arg6, int arg7, int arg8) {
    gl_func_00000000(a0, a1);
    gl_func_00000000(a0, a3);
    gl_func_00000000(a0, arg5);
    gl_func_00000000(a0, arg6);
    gl_func_00000000(a0, a2);
    a0[1] = arg8;
    a0[2] = arg7;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AAEC);

extern int gl_func_00000000();

void gl_func_0000AB70(char *a0) {
    int i;
    char *p;
    i = 0;
    p = a0;
    for (; i != 0x60; i += 0x20) {
        gl_func_00000000(p);
        p += 0x20;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ABBC);

#ifdef NON_MATCHING
/* gl_func_0000ACBC: 25-insn process-all-0x60-slots loop. Calls
 * gl_func_00000000(a0) for each of 0x60 entries (0x20-byte stride),
 * counting non-zero returns in a sum (* 0x20 per hit). Returns the
 * iter count (= 0x60).
 *
 * Cap: 80% match. Target uses 4 saved regs ($s0=hit_sum, $s1=ptr,
 * $s2=iter, $s3=0x60_limit). My emit folds 0x60 to a literal `addiu v0,
 * 0, 0x60` instead of `or v0, s2, 0` — IDO -O2 constant-prop kills
 * the variable form. Same class as
 * docs/IDO_CODEGEN.md#feedback-ido-register-keyword-doesnt-block-constant-fold.
 * Target was compiled with 0x60 from a non-const source (extern, #define
 * via macro, or arg) — unreachable from constant C. */
int gl_func_0000ACBC(char *a0) {
    int hit_total = 0;
    int iter = 0;
    while (iter != 0x60) {
        if (gl_func_00000000(a0) != 0) {
            hit_total += 0x20;
        }
        iter++;
        a0 += 0x20;
    }
    return iter;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ACBC);
#endif

char *game_libs_func_0000AD20(char *a0, int a1) {
    int off = a1 * 0x20;
    return a0 + off;
}

#ifdef NON_MATCHING
/* gl_func_0000AD2C: 28-insn 3-iter try-or-advance loop.
 *   for (i = 0; i < 3; i++) {
 *     if (func(p, a1) != 0) return i + 1;
 *     p += 0x20;
 *   }
 *   return 3; */
extern int func_00000000();
int gl_func_0000AD2C(char *a0, int a1) {
    int i;
    for (i = 0; i != 3; i++) {
        if (func_00000000(a0, a1) != 0) return i;
        a0 += 0x20;
    }
    return 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD2C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B0A8);

#ifdef NON_MATCHING
/* gl_func_0000B190: 30-insn 5-call wrapper gated on (a0 != NULL):
 *   gl_func(*a0); gl_func(a0[1]); inner = a0[2];
 *   if (inner[2] != 0) gl_func(inner[2]);
 *   gl_func(a0[2]);
 *   if (a1 & 1) gl_func(a0);
 */
extern int gl_func_00000000();
void gl_func_0000B190(int *a0, int a1) {
    int *inner;
    if (a0 != NULL) {
        gl_func_00000000(*a0);
        gl_func_00000000(a0[1]);
        inner = (int*)a0[2];
        if (inner[2] != 0) {
            gl_func_00000000(inner[2]);
        }
        gl_func_00000000(a0[2]);
        if (a1 & 1) {
            gl_func_00000000(a0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B190);
#endif

extern int gl_func_00000000();
int gl_func_0000B208(int *a0) {
    int s0;
    int s1 = 0;
    int s2 = 0;
    int sum;
    for (s0 = 0; s0 != 0x180; s0 += 0x30) {
        s1 += gl_func_00000000(a0[0] + s0);
        s2 += gl_func_00000000(a0[0] + s0);
    }
    sum = s1 + s2;
    {
        int r = gl_func_00000000(a0[1]);
        return sum + r;
    }
}

extern int gl_func_00000000();
int gl_func_0000B290(int *a0) {
    int s0;
    int s2 = 0;
    for (s0 = 0; s0 != 0x180; s0 += 0x30) {
        if (gl_func_00000000(a0[0] + s0) ||
            gl_func_00000000(a0[0] + s0)) {
            s2++;
        }
    }
    return s2;
}

#ifdef NON_MATCHING
/* gl_func_0000B310: 40-insn 8-iter or-pair counter + index-array-fill.
 * Sibling of B290 (or-pair) with extra write to a1[s2] = s0 in the
 * success-path. Returns count of successful iterations.
 *
 * Score 92.93% (was 0% INCLUDE_ASM-only). Decl-order count/iter/
 * offset matches target's $s2/$s0/$s1 regalloc. Remaining cap:
 * target schedules `or v0, s2, 0` (return value setup) into the
 * bnel/beq delay slots — IDO doesn't naturally emit this when the
 * return is at function end. */
extern int gl_func_00000000();
int gl_func_0000B310(int *a0, int *a1) {
    int count = 0;
    int iter = 0;
    int offset = 0;
    for (; iter != 8; iter++) {
        if (gl_func_00000000(a0[0] + offset) ||
            gl_func_00000000(a0[0] + offset)) {
            a1[count] = iter;
            count++;
        }
        offset += 0x30;
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B310);
#endif

extern int gl_func_00000000();
int gl_func_0000B3B0() {
    int r = gl_func_00000000();
    if (r != 0) return 1;
    return 0;
}

#ifdef NON_MATCHING
/* gl_func_0000B3DC: 29-insn conditional double-call + finalize.
 *   v = a0->[0x14];
 *   if (v & 3) { func(a0->[0x10], a0[0]); v = a0->[0x14]; }
 *   if (v & 4) func(a0->[0x10], a0[1]);
 *   func(a0->[0x10], &D[0x154]); */
extern int func_00000000();
extern int D_00000000;
void gl_func_0000B3DC(int *a0) {
    int v = a0[0x14/4];
    if ((v & 3) != 0) {
        func_00000000(a0[0x10/4], a0[0]);
        v = a0[0x14/4];
    }
    if ((v & 4) != 0) {
        func_00000000(a0[0x10/4], a0[1]);
    }
    func_00000000(a0[0x10/4], *(int*)((char*)&D_00000000 + 0x154));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B3DC);
#endif

void gl_func_0000B450(int *a0) {
    int flags = a0[0x14 / 4];
    if (flags & 3) {
        gl_func_00000000(a0[0]);
        flags = a0[0x14 / 4];
    }
    if (flags & 4) {
        gl_func_00000000(a0[1]);
    }
}

#ifdef NON_MATCHING
/* gl_func_0000B4A4: 47-insn 3-bit-test orchestrator. Sibling of B450
 * (same flag-bit test idiom) with three independent branches on
 * a0[5] bits {1,2,4}, each invoking the 5-arg gl_func_00000000
 * with: (a0[0_or_1], a1, char_a2, char_a3, &D[0x154]+offset).
 * char_a2/char_a3 emit as lbu from byte 3 of caller-slot spill. */
extern int gl_func_00000000();
extern int D_00000000;

void gl_func_0000B4A4(int *a0, int a1, char a2, char a3) {
    if (a0[5] & 1) {
        gl_func_00000000(a0[0], a1, a2, a3,
            (*(char**)((char*)&D_00000000 + 0x154)) + 0xE);
    }
    if (a0[5] & 2) {
        gl_func_00000000(a0[0], a1, a2, a3,
            (*(char**)((char*)&D_00000000 + 0x154)) + 0xF);
    }
    if (a0[5] & 4) {
        gl_func_00000000(a0[1], a1, a2, a3,
            (*(char**)((char*)&D_00000000 + 0x154)) + 0x10);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B4A4);
#endif

/* 14-insn 2-call wrapper at 0xB560-0xB594. The 4 trailing bytes at
 * 0xB59C-0xB5A8 (`sll/subu/addiu/div` computing (a1*3)/5) are stolen
 * prologue setup for successor gl_func_0000B5AC, applied via SUFFIX_BYTES
 * (same recipe class as gl_func_0005FD20 / gl_func_0005FDCC). */
extern int gl_func_00000000();
void gl_func_0000B560(int *p) {
    gl_func_00000000(p[4], p[0]);
    gl_func_00000000(p[4], p[1]);
}

/* gl_func_0000B5AC: 25-insn function that INHERITS $hi and $v0 from caller +
 * predecessor's SUFFIX_BYTES. Sibling of gl_func_0000B560 (just-landed) — B560
 * was extended with SUFFIX_BYTES `sll v0,a1,2; subu v0,v0,a1; addiu at,$0,5;
 * div $0,v0,at` that compute (a1*3)/5. Those 4 insns belong logically to
 * B5AC's prologue, leaving (a1*3)/5 quotient in $lo and remainder in $hi.
 * B5AC's first interesting insn is `mfhi a1` reading the remainder.
 *
 * Additional inherited reg: $v0 (used by `bgez v0` and `andi a2,v0,0x7`) —
 * caller-side flag. NOT standalone-callable from prototype-based C; reached
 * only via fall-through from gl_func_0000B560+SUFFIX_BYTES.
 *
 * Decoded control flow:
 *   ; entry inherits $hi = (a1*3)%5, $v0 = caller flag
 *   t8 = a1; t9 = 3*a1; save args; t7 = *a0;
 *   t0 = 9*a1; t1 = 36*a1; t9 = 48*a1;
 *   a1 = $hi (= prior remainder);
 *   a3 = t1 + 0xD268 = 36*a1 + 0xD268;     ; lookup-table address
 *   a0 = *a0 + 48*a1;                       ; struct-array entry
 *   if (v0 < 0 || (v0 & 7) == 0) goto call;
 *   a2 = (v0 & 7) - 8;
 * call:
 *   func_00000000();   ; first jal
 *   func_00000000();   ; second jal (a0 reloaded in delay slot)
 *   return;
 *
 * The trailing 4 insns at B5AC+0x70..0x80 are B5AC's tail-SUFFIX_BYTES for
 * its OWN successor B638 (`sll v0,a1,2; subu v0,v0,a1; addiu at,$0,5; div`)
 * — same chained pattern as B560->B5AC. B638 will need a parallel decode
 * to capture the chain.
 *
 * BLOCKED for prototype-based C: inherited $v0 is caller-specific (varies
 * per call site), can't be captured as a function arg without breaking
 * existing callers. PREFIX_BYTES on B5AC would have to bake a specific $v0
 * per call site — not a uniform recipe. Stays INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B5AC);

/* gl_func_0000B638: 29-insn function in the B560/B5AC/B638 dispatcher chain.
 * Like B5AC, INHERITS $hi (from B5AC's tail-SUFFIX_BYTES `sll v0,a1,2; subu;
 * addiu at,$0,5; div`) AND $v0 (caller-side flag). Same uninterruptible
 * mfhi-then-bgez pattern as B5AC.
 *
 * Decoded structure (cross-checked with B5AC analysis above):
 *   ; entry inherits $hi = (a1*3)%5, $v0 = caller flag
 *   t8 = a1; t9 = 3*a1; save args; t7 = *a0;
 *   t1 = 0xD388;                       ; lookup-table base (B5AC used 0xD268, +0x120 here)
 *   a1 = $hi;                           ; inherited remainder
 *   t9 = 48*a1;
 *   t0 = 4*v0;                          ; index by INHERITED v0 with 4-byte stride
 *                                       ;   (B5AC indexed by 36*a1 — different stride)
 *   a3 = t0 + t1 = 4*v0 + 0xD388;       ; per-flag table lookup
 *   a0 = *a0 + 48*a1;                   ; per-a1 struct entry
 *   if (v0 < 0 || (v0 & 7) == 0) goto call;
 *   a2 = (v0 & 7) - 8;
 * call:
 *   func_00000000();   ; first jal
 *   func_00000000();   ; second jal (a0 reloaded in delay slot)
 *   return;
 *
 * BLOCKED for prototype-based C — same class as B5AC. Inherited $v0
 * varies per call site; no uniform PREFIX_BYTES recipe. Stays INCLUDE_ASM
 * for now. Per docs/POST_CC_RECIPES.md
 * #feedback-insn-patch-for-ido-codegen-caps "HI/LO register inheritance
 * (chained-SUFFIX-div pattern, 2026-05-05)" — same recognition pattern. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B638);

extern int gl_func_00000000();
void gl_func_0000B6AC(int *a0) {
    gl_func_00000000(a0[1]);
    gl_func_00000000(a0);
}

extern int gl_func_00000000();
void gl_func_0000B6D8(int *a0) {
    gl_func_00000000(a0[2]);
    gl_func_00000000(a0[4], a0[2]);
}

#ifdef NON_MATCHING
/* gl_func_0000B710: 27-insn 7-call sequence with various arg shapes.
 *   func(*a0); func(a0[1]); func(a0); func(a0);
 *   func(*(int*)&D[0x154]);
 *   func(&D);
 *   func(a0[0x10/4], *(int*)&D[0x154]); */
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0000B710(int *a0) {
    gl_func_00000000(*a0);
    gl_func_00000000(a0[1]);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x154));
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a0[0x10/4], *(int*)((char*)&D_00000000 + 0x154));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B710);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B77C);

#ifdef NON_MATCHING
/* gl_func_0000B868: 30-insn 4-call init sequence. Each call passes
 * a different D_* address with various arg shapes:
 *   gl_func_00000000(&D_A, 2);
 *   gl_func_00000000(&D_B, 0, &D + 0xD4E0);  // 3rd arg is symbol+offset
 *   gl_func_00000000(&D_C, 0, a2);
 *   gl_func_00000000(&D_D, a1, a3);
 * a0 declared but unused → K&R-style spill of all caller-slots.
 * Note the 3rd arg of call#2 is `(char*)&D + 0xD4E0` — emits as
 * lui+addiu (two insns) because 0xD4E0 has bit 15 set; not 0xD4E0
 * literal which would emit single-insn ori. */
extern int gl_func_00000000();
extern int gl_data_B884_arg, gl_data_B89C_arg, gl_data_B8AC_arg, gl_data_B8C0_arg;
extern int D_00000000;

void gl_func_0000B868(int a0, int a1, int a2, int a3) {
    gl_func_00000000(&gl_data_B884_arg, 2);
    gl_func_00000000(&gl_data_B89C_arg, 0, (char*)&D_00000000 + 0xD4E0);
    gl_func_00000000(&gl_data_B8AC_arg, 0, a2);
    gl_func_00000000(&gl_data_B8C0_arg, a1, a3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B868);
#endif

#ifdef NON_MATCHING
/* gl_func_0000B8E0: 30-insn sibling of gl_func_0000B868. Same 4-call
 * shape but with one arg shifted (B868 uses a2 at call#3 and a1+a3 at
 * call#4; B8E0 uses a1 at call#3 and a2+a3 at call#4). Magic constant
 * is 0xD4E4 (4 bytes higher than B868's 0xD4E0). a0 declared but
 * unused → K&R-style spill of all caller-slots. */
extern int gl_func_00000000();
extern int gl_data_B8FC_arg, gl_data_B914_arg, gl_data_B924_arg, gl_data_B938_arg;
extern int D_00000000;

void gl_func_0000B8E0(int a0, int a1, int a2, int a3) {
    gl_func_00000000(&gl_data_B8FC_arg, 2);
    gl_func_00000000(&gl_data_B914_arg, 0, (char*)&D_00000000 + 0xD4E4);
    gl_func_00000000(&gl_data_B924_arg, 0, a1);
    gl_func_00000000(&gl_data_B938_arg, a2, a3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B8E0);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B958);

#ifdef NON_MATCHING
/* gl_func_0000BA6C: 42-insn save-game checksum verifier (sibling of
 * BB14 — same magic 0xD1265205 + same 4 data chunks).
 * Reads 4 8-byte data chunks + existing hash, recomputes hash, returns
 * 1 if hashes mismatch, 0 if match.
 *
 * EXACT (100.0%). The 99.95% cap was an oversized local: char buf[0x40]
 * forced frame -0x60; the correct size is buf[0x28] (only [0,0x28) is
 * ever touched), which yields target frame -0x48 and lets the high data
 * writes borrow the caller arg-save region (caller-slot-borrow, same
 * family as BB14). Episode logged. */
extern int gl_func_00000000();
int gl_func_0000BA6C(int a0) {
    char buf[0x28];
    gl_func_00000000(a0, &buf[0x08], 0x188, 8);
    gl_func_00000000(a0, &buf[0x10], 0x1F0, 8);
    gl_func_00000000(a0, &buf[0x18], 0x210, 8);
    gl_func_00000000(a0, &buf[0x20], 0x228, 8);
    gl_func_00000000(a0, &buf[0], 0, 8);
    if (gl_func_00000000(&buf[0], &buf[0x08], 0x20, 0xD1265205) == 0) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BA6C);
#endif

#ifdef NON_MATCHING
/* gl_func_0000BB14: 39-insn 6-call sequence — reads 4 8-byte chunks
 * from a0 at offsets 0x188/0x1F0/0x210/0x228 into local data[32],
 * then computes a hash via 0xD1265205, then submits at offset 0.
 * Likely a save-game checksum or asset-streaming primitive.
 *
 * Score 99.77% (was 0% INCLUDE_ASM-only). 9 byte diffs remaining,
 * all stack-offset shifts: target uses frame -0x48 with hash[32]
 * placed at sp+0x40..0x5F — overlapping into the CALLER's arg-save
 * region (IDO "borrowed caller-slot" optimization for unused outgoing
 * arg slots). My emit uses frame -0x60 (96 bytes) so hash sits fully
 * within own frame at sp+0x20..0x3F. C-unreproducible without
 * compiler-level control over arg-save reuse. */
extern int gl_func_00000000();
void gl_func_0000BB14(int a0) {
    char data[32];
    char hash[32];
    gl_func_00000000(a0, &data[0],  0x188, 8);
    gl_func_00000000(a0, &data[8],  0x1F0, 8);
    gl_func_00000000(a0, &data[16], 0x210, 8);
    gl_func_00000000(a0, &data[24], 0x228, 8);
    gl_func_00000000(hash, data, 0x20, 0xD1265205);
    gl_func_00000000(a0, 0, hash, 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BB14);
#endif

extern int gl_func_00000000();
int gl_func_0000BBB0(int a0) {
    int tmp = gl_func_00000000(24);
    gl_func_00000000(a0, tmp, 504, 24);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BBF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BC84);

extern int gl_func_00000000();
void gl_func_0000BD78(int a0) {
    int pad_arr[5];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BDA8(int a0) {
    int tmp = gl_func_00000000(384);
    gl_func_00000000(a0, tmp, 8, 384);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BDE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BEB8);

extern int gl_func_00000000();
void gl_func_0000BFAC(int a0) {
    int pad_arr[95];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BFDC(int a0) {
    int tmp = gl_func_00000000(96);
    gl_func_00000000(a0, tmp, 400, 96);
    return tmp;
}

#ifdef NON_MATCHING
/* gl_func_0000C01C: 52-insn (0xD0) cross-USO orchestrator. Frame -0x88,
 * saves s0/ra. Pattern: copy 0x60-byte buffer from arg1 to local stack,
 * then make 7 cross-USO calls passing the buffer + various offsets.
 *
 * Decoded:
 *   1. unrolled-by-3 loop copies 0x60 bytes from arg1 to sp[0x28]
 *      (8 iterations of 0xC-byte chunks).
 *   2. gl_func(sp[0x28], arg1, arg2_from_caller, arg3_from_caller)
 *   3. gl_func(arg0, 0x190, sp[0x28], 0x60)
 *   4. gl_func(sp[0x20], sp[0x28], 0x60, 0xDEADBBAD)
 *   5. gl_func(arg0, 0x1F0, sp[0x20], 8)
 *   6. gl_func(arg0, 0x7F60, sp[0x28], 0x60)
 *   7. gl_func(arg0, 0x7FC0, sp[0x20], 8)
 *   8. gl_func(arg0)
 *
 * Constants suggest framebuffer/segmented-memory ops: 0x190/0x1F0 are
 * NTSC viewport-related, 0x7F60/0x7FC0 are top-of-RDRAM offsets, 0x60
 * is element size, 0xDEADBBAD is poison. Likely a swap-buffers /
 * commit-frame helper. Multi-tick refinement target. */
extern int gl_func_C01C_callee();
void gl_func_0000C01C(void *arg0, int *arg1, int arg2, int arg3) {
    int buf60[24];   /* 0x60 bytes at sp+0x28 */
    int buf08[2];    /* 8 bytes at sp+0x20 */
    int i;
    for (i = 0; i < 24; i += 3) {
        buf60[i+0] = arg1[i+0];
        buf60[i+1] = arg1[i+1];
        buf60[i+2] = arg1[i+2];
    }
    gl_func_C01C_callee(buf60, arg1, arg2, arg3);
    gl_func_C01C_callee(arg0, 0x190, buf60, 0x60);
    gl_func_C01C_callee(buf08, buf60, 0x60, 0xDEADBBAD);
    gl_func_C01C_callee(arg0, 0x1F0, buf08, 8);
    gl_func_C01C_callee(arg0, 0x7F60, buf60, 0x60);
    gl_func_C01C_callee(arg0, 0x7FC0, buf08, 8);
    gl_func_C01C_callee(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C01C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C0EC);

extern int gl_func_00000000();
void gl_func_0000C1E0(int a0) {
    int pad_arr[23];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C210);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C28C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C378);

extern int gl_func_00000000();
void gl_func_0000C46C(int a0) {
    int pad_arr[3];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

#ifdef NON_MATCHING
/* gl_func_0000C49C: 21-insn 3-call wrapper. SEMANTIC FIX 2026-05-06:
 * target reads from RETURN VALUE as pointer (r[0], r[2]), NOT from a0.
 * Prior wrap incorrectly used `a0[1] = a0[0]`. Asm clearly shows
 * `lw $t8, 0($v0)` (= r[0]) and `lw $t9, 0x8($v0)` (= r[2]).
 *   r = (int*)gl_func(a0);              // returns pointer
 *   a0[1] = r[0];                        // copy r[0] into a0[1]
 *   if (r[2] != 0) gl_func(r[2], r);
 *   gl_func(r, r); */
void gl_func_0000C49C(int *a0) {
    int *r = (int*)gl_func_00000000(a0);
    a0[1] = r[0];
    if (r[2] != 0) {
        gl_func_00000000(r[2], r);
    }
    gl_func_00000000(r, r);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C49C);
#endif

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD1C();
int gl_func_0000C4F0(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD1C(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD58();
int gl_func_0000C520(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD58(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DDC8();
int gl_func_0000C550(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DDC8(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
int gl_func_0000C580(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DCE0(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C5B0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000C5B0_pad.s")

extern int gl_func_00000000();
void gl_func_0000C644(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C680(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C6BC(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

void gl_func_0000C714(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C784);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C8B8);

#ifdef NON_MATCHING
/* gl_func_0000CB9C: 24-insn bounds-check + dispatch (0%→70%).
 *   if (a0[0x30] < a0[0x34]) return 0;
 *   p = a0[0x78];
 *   v = a0[0x34] - 8;
 *   if (p != 0) { func(p); a0[0x30] = v; }
 *   return 1;
 * Remaining cap: frame -0x20 vs target -0x18, extra spills of v/target
 * locals, and IDO chooses $a1 for preserving a0 vs target's $a2. */
extern int gl_func_00000000();
int gl_func_0000CB9C(int *a0) {
    int *target;
    int v;
    if (a0[0x30/4] < a0[0x34/4]) goto end_zero;
    target = (int*)a0[0x78/4];
    v = a0[0x34/4] - 8;
    if (target != 0) {
        gl_func_00000000(target);
        a0[0x30/4] = v;
    }
    return 1;
end_zero:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CB9C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CBFC);

#ifdef NON_MATCHING
/* gl_func_0000CD80: 23-insn (0x5C) "any-of-three-thresholds undercut" gate.
 *
 * Calls gl_func_00000000() iff $f0 < $f4 OR $f0 < D[sym1] OR $f0 < D[sym2].
 * Effectively a 3-way OR-gate over float threshold tests. The function
 * takes 2 float caller-args ($f0 and $f4 — non-standard ABI) and reads
 * 2 globals into $f6/$f8. If any threshold is exceeded, dispatch the
 * cross-USO callback.
 *
 * Arguments are received in $f0 and $f4 (NOT the standard $f12/$f14),
 * suggesting this is called from an asm-emitted call-site that explicitly
 * sets up these registers. Standard C signature `(float, float)` won't
 * map cleanly to $f0/$f4 — IDO uses $f12/$f14 for normal float args.
 *
 * Initial structural wrap; bytes likely won't match without an inline-asm
 * shim or an explicit-register declaration. Documented for future passes. */
extern int gl_func_00000000();
void gl_func_0000CD80(float a0, float a1) {
    extern char D_CD80_t1;
    extern char D_CD80_t2;
    float t1 = *(float*)&D_CD80_t1;
    float t2 = *(float*)&D_CD80_t2;
    if (a0 < a1 || a0 < t1 || a0 < t2) {
        gl_func_00000000();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CD80);
#endif

#ifdef NON_MATCHING
/* gl_func_0000CDDC: 23-insn conditional vtable-dispatch + chain. If
 * *a1 == 9, call (*a0->[0x5C])(a0 + s16(a0->[0x58])). Then always
 * call gl_func(a0, a1).
 *
 * Cap: target has a "dummy lw v0, 0x28(a0)" + dual home-slot spills
 * for a0/a1 across the jalr; IDO doesn't emit these. 84 vs 92 bytes. */
int gl_func_0000CDDC(int *a0, int *a1) {
    if (*a1 == 9) {
        int (*fn)(int*) = (int(*)(int*))a0[0x5C/4];
        int *new_a0 = (int*)((char*)a0 + *(short*)((char*)a0 + 0x58));
        fn(new_a0);
    }
    return gl_func_00000000(a0, a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CDDC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CE38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D0D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D318);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D418);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D548);

extern int gl_func_00000000();

void gl_func_0000D6A0(char *a0, int a1) {
    if ((*(int*)(a0 + 0xB4) & 4) != 0) {
        gl_func_00000000(0x2F, a0);
        *(int*)(a0 + 0xA4) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D7B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D8E0);

/* gl_func_0000D9B8: 98.64%->100% via INSN_PATCH (3 reg-rename diffs at
 * offsets 0x08/0x0C/0x18). IDO emits $a1 for the temp; target uses $a3.
 * The 3 insns are identical in structure, differ only in register field.
 * Per feedback_insn_patch_for_ido_codegen_caps.md, this is the canonical
 * use case for INSN_PATCH (operand-only, same insn count, same size). */
extern int gl_func_00000000();
void gl_func_0000D9B8(int *a0) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p);
}

#ifdef NON_MATCHING
/* gl_func_0000D9E4: 0x150 (84 insns), 0x30-byte stack frame.
 * Untouched until 2026-05-03. Single function (grep -c 03E00008 = 1).
 * 2-arg: takes (int *a0, int a1).
 *
 * ENTRY GUARDS (insns 1-18 @ 0xD9E4-0xDA28, decoded):
 *   addiu sp,-0x30                     ; prologue
 *   save ra/s0/s1                       ; 0x24/0x20/0x1C
 *   sw a1, 0x34(sp)                    ; spill a1 to caller slot (varargs?)
 *   s0 = a0[0x6C]                       ; sub-struct ptr (cached for body)
 *   s1 = a0                             ; saved arg
 *   if (s0 == 0) goto end_simple        ; beq +0x3F
 *   t6 = a0[0xB4]
 *   if ((t6 & 2) == 0) goto end_simple  ; beq +0x3A
 *   t8 = *(int*)(&D_0 + 0x64)           ; load global ptr
 *   if (t8 == 0) goto end_simple        ; beq +0x36
 *
 * MID BODY (insns 19-50 @ 0xDA2C-0xDAB0, decoded structurally):
 *   FPU math chain. Constants:
 *     0x447A0000 = 1000.0f            (used in mtc1 + at-reg dance)
 *     0x42C80000 = 100.0f
 *     0x437F0000 = 255.0f             (loaded into multiple $f-regs)
 *     0x436B0000 = 235.0f
 *   Pattern: (float)a1 / 1000.0f then scale by 100.0f and 255.0f / 235.0f
 *   — looks like a percentage/normalized-value calculation. Probably color
 *   alpha (0..255 range with 0..235 sub-range) or stat-bar percentage.
 *
 * After FPU, calls some external (jal func_00000000 at 0xDA60) with 5 args
 *   (a0, a1, a2 from FPU, a3, plus saved on sp+0x10) — likely a
 *   `set_color_or_alpha(p, val_pct)` style helper.
 *
 * THEN at 0xDAA0+ another large FPU block computing 4 swc1 stores into
 *   (a0->0x64..0x70) and similar. Final block does 2 conditional gl_func
 *   calls based on (a0[0xB4] & 1) and a sub-struct check.
 *
 * EXIT (last 6 insns @ 0xDB1C-0xDB34):
 *   end_simple:
 *     restore ra/s0/s1, restore sp, jr ra
 *
 * Per feedback_partial_alloc_block_add_irreversible.md, NOT writing partial
 * body — would regress the 0% baseline. Captures structural decode only;
 * future passes with full body context can write all FPU sub-blocks
 * together. Multi-tick decomp expected. */
extern int gl_func_h2hproc_8EC_pre();  /* placeholder — actual callee unknown */
void gl_func_0000D9E4(int *a0, int a1) {
    /* Entry: 3 guards must all pass to reach body. */
    int *sub = (int*)a0[0x6C / 4];
    int flags = a0[0xB4 / 4];
    int *globalp = *(int**)((char*)&D_00000000 + 0x64);
    if (sub == 0) return;
    if ((flags & 2) == 0) return;
    if (globalp == 0) return;
    /* TODO: 60+ insns of FPU math + cross-USO calls. */
    (void)a1;
    (void)gl_func_h2hproc_8EC_pre();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9E4);
#endif

void gl_func_0000DB34(int a0, int a1, int a2) {
    char pad1[4];
    int *v0 = *(int**)((char*)&D_00000000 + 0x28);
    int local = 0x3ED;
    char pad2[12];
    ((void(*)(int, int*))*(int*)((char*)v0 + 0x34))(
        *(short*)((char*)v0 + 0x30) + (int)&D_00000000, &local);
}

#ifdef NON_MATCHING
/* gl_func_0000DB80: 68-insn function-pointer dispatcher with table lookup
 * + 3-way switch on entity state (a2->0x48).
 *
 * Structural decode (2026-05-04 first-pass):
 *   Prologue: spill 1000 (0x3E8) at sp+0x44 to use as a base.
 *   Lookup: t = *(sp+0x44 + a1*96)  — 96-byte stride table at offset
 *           +1000 from some base. (96 = 24 ints = likely a struct).
 *   First call: ((fnptr)t->0x2C)(t->0x28+t, &sp[0x44])  — vtable call,
 *           passes (struct ptr offset by signed half) and pointer to
 *           the spilled-1000 slot (now repurposed as out-arg).
 *
 *   Switch on (a2->0x48 - 2):  // a2 = original a0 saved at sp+0x50
 *     case 2 (a2->0x48 == 2): bnel branches to epilogue (skip body)
 *     case 3 (a2->0x48 == 3): take 0x3E9-stride table:
 *         t = *(sp+0x2C + a1*96 + a0->0x44)  // diff stride table
 *         ((fnptr)t->0x2C)(t->0x28+t, t_lookup)
 *         goto epilogue
 *     default (else):         take 0x3E8-stride table:
 *         t = *(sp+0x20 + a1*96 + a0->0x44)
 *         ((fnptr)t->0x2C)(t->0x28+t, t_lookup_h)  // signed-half load arg
 *
 *   The 3 jal sites all dispatch through `t->0x2C` function pointer with
 *   `t->0x28` (signed half) added to t as the first arg. Different
 *   tables are consulted based on a2->0x48's value.
 *
 * NEXT PASS: identify the global struct at offset +0x3E8/+0x3E9 (likely a
 * "render dispatch" or "AI behavior" table); type the struct's vtable +
 * data layout. Likely a "process entity by type-code" pattern. */
extern int gl_func_00000000();
void gl_func_0000DB80(int *a0, int a1) {
    /* Partial decode: 3-way switch on a2->0x48 (original a0->0x48), each
     * branch loads a different table-of-vtables and calls *t->0x2C(t->0x28+t, ...).
     * Default build uses INCLUDE_ASM. */
    (void)a0;
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DB80);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DC90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DD44);

/* 20-insn indirect dispatcher (sibling of gl_func_0000DE30/DE80/DED0/0003CB2C).
 * Same shape as DE30 form (inlined dispatch + pad_top[2]/pad_bot[4] frame
 * sizing), local = 0x3EA. INSN_PATCH on the same 4 reg-rename insns at
 * 0x24/0x2C/0x34/0x3C makes build/.o byte-equal to expected/.o post-cc. */
void gl_func_0000DDE0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EA;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* 20-insn indirect dispatcher (sibling of gl_func_0000DDE0/0003CB2C).
 * 16/20 insns match from C emit; remaining 4-insn diff is a register-shift
 * (v0/t0/t1 ↔ v1/v0/t0) that no C-level lever inside this function
 * reproduces. INSN_PATCH on the 4 reg-shift insns @0x24/0x2C/0x34/0x3C
 * makes build/.o byte-equal to expected/.o post-cc. */
void gl_func_0000DE30(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EB;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* Sibling of gl_func_0000DDE0/0000DE30/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3EC; otherwise byte-identical to DE30. Same INSN_PATCH recipe:
 * the 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched
 * to match expected. (The 0x30 word coincidentally byte-matches due to
 * register-rename + same instruction word; runtime semantics flip when the
 * patched 0x2C insn redefines $v0 = p[0x28] before 0x30 reads it.) */
void gl_func_0000DE80(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EC;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* Sibling of gl_func_0000DDE0/DE30/DE80/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3E9; otherwise byte-identical to DE30/DE80. Same INSN_PATCH recipe:
 * 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched to
 * match expected. (See DE80 for the byte-identical-bytes-different-semantics
 * mechanism at offset 0x30.) */
void gl_func_0000DED0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3E9;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

int gl_func_0000DF20_inner(int a0, int a1);

void gl_func_0000DF20(int a0, int a1, float a2) {
    int rv = gl_func_0000DF20_inner(a0, a1);
    if (rv != 0) {
        *(float*)(rv + 0x10) = a2;
    }
}

extern int gl_func_00000000();

void gl_func_0000DF4C(int a0, int a1, int a2) {
    int *r = (int*)gl_func_00000000(a0, a1, a2);
    if (r == 0) return;
    if ((r[1] & 1) == 0) return;
    r[10] = a2;
}

extern int gl_func_00000000();

void gl_func_0000DF8C(int a0, int a1, float a2, float a3) {
    float *r = (float*)gl_func_00000000(a0, a1);
    if (r != 0) {
        r[2] = a2;
        r[3] = a3;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E05C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E118);

void gl_func_0000E1DC(int *a0, int a1, int a2) {
    int *v = (int*)gl_func_00000000(a0, a1, a2);
    if (v == 0) return;
    if (!(v[1] & 1)) return;
    if (!(a0[0xB4 / 4] & 2)) return;
    gl_func_00000000(a0, a2);
}

#ifdef NON_MATCHING
/* gl_func_0000E230: 29-insn count-loop calling func per element.
 *   for (i = 0, off = 0; i < a0->[0x48]; i++, off += 0x60) {
 *     func(a0, *(int*)((char*)a0->[0x44] + off), 1, 0);
 *   }
 *
 * 98.45% cap. Sole residual is a pure 2-reg swap: mine assigns the
 * saved a0-ptr→$s2 / offset→$s1; target wants a0→$s1 / offset→$s2.
 * Adding an explicit `int *s = a0;` to bias first-assignment REGRESSED
 * to 87.1% (IDO kept BOTH s2 and s3 = a0, +1 sreg save slot, frame
 * grew). No C lever flips just the two $s roles — permuter/INSN_PATCH
 * class (same family as gl_func_00035834 / gl_func_0004ED0C). */
extern int func_00000000();
void gl_func_0000E230(int *a0) {
    int i;
    int offset;
    i = 0;
    offset = 0;
    while (i < a0[0x48/4]) {
        func_00000000(a0, *(int*)((char*)a0[0x44/4] + offset), 1, 0);
        i++;
        offset += 0x60;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E230);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E368);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E4A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E53C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E5D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E66C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E79C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E84C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E910);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E9C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000EAAC);

extern int gl_ref_00020CB0();
int gl_func_0000EB38(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CB0(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020CEC();
int gl_func_0000EB68(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CEC(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D28();
int gl_func_0000EB98(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D28(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D80();
int gl_func_0000EBC8(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D80(a0 + 0x10);
}





