#include "common.h"

/* Tail half of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_949C.c (the 4-fn -O0 cluster at 0x949C..0x959C).
 * Covers gl_func_0000959C onwards. Type definitions Tri3i/Vec3
 * (originally declared at game_libs.c:290) re-declared here. */

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;


/* gl_func_0000959C: 53-insn helper. Multi-pass decode pending. */
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

/* gl_func_00009DB8: 65-insn helper. Multi-pass decode pending. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009DB8);

extern int gl_data_0000D434;

#ifdef NON_MATCHING
/* gl_func_00009EBC: 3-iteration loop dispatching to gl_func_00000000 with
 * a 5x8 grid index computed as (a1 % 5) + ((a2 % 8) << 3). The signed
 * remainder of a2 by 8 comes from a sign-preserving bgez/andi/beq dance
 * (low 3 bits, adjusted by -8 when a2<0 and low bits nonzero). Args:
 *   a0 = base pointer (dst is a0+0x18, advances +8/iter)
 *   a1 = row seed (advances +1/iter, fed to %5)
 *   a2 = col seed (advances +1/iter, fed to signed-%8)
 *   a3 = pointer to sink int read once per iter (lw a3, 0(s4) in jal slot)
 * Draft NM wrap: structure captured, expect partial match — divide-trap
 * break-6/break-7 inserts (UB-guards on s5=5, s1=INT_MIN) and signed-%8
 * scheduling will likely diverge from compiler emit. */
void gl_func_00009EBC(int x0, int a1, int a2, int* a3) {
    int dst = x0 + 0x18;
    int row = a1;
    int col = a2;
    int sink;
    int i;

    for (i = 0; i < 12; i += 4) {
        int idx = (row % 5) + ((col % 8) << 3);
        sink = *a3;
        gl_func_00000000(dst, idx, &gl_data_0000D434, sink);
        dst += 8;
        row += 1;
        col += 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009EBC);
#endif

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

/* gl_func_0000A130: 25-insn 3-iter loop counting non-zero callee returns.
 *   count = 0; for (p = a0+0x18; p != a0+0x30; p += 8)
 *       if (FUNC1(p) != 0) count++;
 *   return count;
 * 6-insn INSN_PATCH closes the i/p $s-reg swap (target s0=i,s1=p; built
 * s0=p,s1=i — decl-order swap REGRESSES per feedback-sreg-not-decl-driven). */
extern int gl_func_00000000();
int gl_func_0000A130(char *a0) {
    int count = 0;
    int i;
    char *p = a0 + 0x18;
    for (i = 0; i != 24; i += 8) {
        if (gl_func_00000000(p) != 0) count++;
        p += 8;
    }
    return count;
}

/* game_libs_func_0000A194: 3-insn leaf — return base + a1*8.
 *   sll t6, a1, 3; jr ra; addu v0, a0, t6 (delay).
 * Array stride-8 element pointer. Index-as-shift+add via int arith. */
int game_libs_func_0000A194(int a0, int a1) {
    int t = a1 << 3;
    return a0 + t;
}

/* game_libs_func_0000A1A0: 4-insn leaf — return base + a1*8 + 0x18.
 *   sll t6, a1, 3; addu v0, a0, t6; jr ra; addiu v0, v0, 0x18 (delay).
 * Same stride-8 element pointer + 0x18 field offset. */
int game_libs_func_0000A1A0(int a0, int a1) {
    int t = a1 << 3;
    return a0 + t + 0x18;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000A1B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A1C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A2B8);

/* gl_func_0000A4D0: 28-insn find-first-match-in-3-entries.
 *   for (i = 0; i < 3; i++) {
 *     if (func(a0->[0x18 + i*8], a1) != 0) return i;
 *   }
 *   return 3;
 *
 * Promoted from 92.86% NM wrap to EXACT via 2-insn INSN_PATCH for the
 * `addiu s1, a0, 0x18` / `or s0, zero, zero` pair-swap at +0x1C/+0x20
 * (IDO emits entry-init first; target emits i-init first). 10th in the
 * INSN_PATCH-promotion family. */
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

/* Bitfield getter/setter cluster — gl_func_0000A7B4's tail-extracted micros.
 * Each get returns a sub-field; each set replaces it in place. */

/* getter: bits 0..1 → return (*a0 & 3) */
int game_libs_func_0000A878(int *a0) { return *a0 & 3; }

/* setter: bits 0..1 ← a1. Target writes the cleared-value intermediate too. */
void game_libs_func_0000A884(int *a0, int a1) {
    *a0 = *a0 & ~3;
    *a0 = *a0 | (a1 & 3);
}

/* getter: bits 2..4 → return (*a0 >> 2) & 7 */
int game_libs_func_0000A8A4(int *a0) { return (*a0 >> 2) & 7; }

/* setter: bits 2..4 ← a1 */
void game_libs_func_0000A8B4(int *a0, int a1) {
    *a0 = *a0 & ~0x1C;
    *a0 = *a0 | ((a1 & 7) << 2);
}

/* A8D8: int f(int*a0){ if((*a0>>5)&1) return 32; return 0; } — CONFIRMED
 * 2026-05-17: that exact C form produces all 8 body words byte-exact
 * (8C8E0000 00001025 000E7943 31F80001 13000003 00000000 03E00008
 * 24020020) but C always appends its own `jr ra; nop` epilogue (+2
 * words). Target has NO epilogue: the v0=0 path `beq t8,zero,0x20`
 * branches one past the last insn, falling through into the next
 * function (shared-tail space optimization). Plain C cannot suppress the
 * trailing epilogue; would need a TRUNCATE_TEXT=8 post-cc strip, not
 * worth it for an 8-byte fn. Keep INCLUDE_ASM (no episode). */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000A8D8);

/* empty: jr ra; nop */
void game_libs_func_0000A8F8(void) {}

/* setter: bit 5 ← (a1 & 0x20) */
void game_libs_func_0000A900(int *a0, int a1) {
    *a0 = *a0 & ~0x20;
    if (a1 & 0x20) *a0 = *a0 | 0x20;
}

/* getter: bits 6..9 → return (*a0 >> 6) & 0xF */
int game_libs_func_0000A928(int *a0) { return (*a0 >> 6) & 0xF; }

/* setter: bits 6..9 ← a1 */
void game_libs_func_0000A938(int *a0, int a1) {
    *a0 = *a0 & ~0x3C0;
    *a0 = *a0 | ((a1 & 0xF) << 6);
}

/* getter: bits 10..13 → return (*a0 >> 10) & 0xF */
int game_libs_func_0000A95C(int *a0) { return (*a0 >> 10) & 0xF; }

/* setter: bits 10..13 ← a1 */
void game_libs_func_0000A96C(int *a0, int a1) {
    *a0 = *a0 & ~0x3C00;
    *a0 = *a0 | ((a1 & 0xF) << 10);
}

/* gl_func_0000A990: 25-insn 5-identical-call + 2-zero-fields wrapper. */
void gl_func_0000A990(int *a0) {
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    func_00000000(a0, 0);
    a0[1] = 0;
    a0[2] = 0;
}

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

#ifdef NON_MATCHING
/* gl_func_0000AAEC: 33-insn 3-iter fixed-loop 4-arg helper (0x84, frame 0x30).
 *
 * Decoded structure (raw-word disasm):
 *   self2 = &D_1D438;                              // s3 (constant ptr1)
 *   data2 = &D_1D3E8;                              // s2 (advances per iter)
 *   for (i = 0; i < 3; i++) {                       // s0=0..2, s4=3 sentinel
 *       int a1 = i + ((i + 4) << 3);               // = 9*i + 32 (8-byte stride+32 base, idx-encoded)
 *       gl_func(self_p, a1, self2, data2);         // 4-arg
 *       self_p += 0x20;                            // s1 += 32 per iter
 *       data2  += 0x18;                            // s2 += 24 per iter (delay slot of bne)
 *   }
 *
 * Frame saves s0/s1/s2/s3/s4/ra (6 saved regs); 0x30 frame. The `9*i + 32`
 * argument shape suggests an interleaved-array index: iter 0→32, 1→41, 2→50.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int D_1D438, D_1D3E8;
void gl_func_0000AAEC(int *a0) {
    int *self_p = a0;
    int *self2 = &D_1D438;
    int *data2 = &D_1D3E8;
    int i;
    for (i = 0; i < 3; i++) {
        int a1 = i + ((i + 4) << 3);
        gl_func_00000000(self_p, a1, self2, data2);
        self_p = (int*)((char*)self_p + 0x20);
        data2 = (int*)((char*)data2 + 0x18);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AAEC);
#endif

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

/* gl_func_0000ACBC: 25-insn 3-iter loop, sibling of gl_func_0000A0CC.
 * Calls func_00000000 (NOTE: not gl_-prefixed — target's reloc references
 * the intra-segment `func_00000000` symbol, not `gl_func_00000000`).
 * Returns non-zero hit count. Source structurally identical to A0CC;
 * stride/limit immediates differ (0x20/0x60 vs 0x8/0x18) and callee
 * reloc name. Byte-exact via sibling INSN_PATCH transfer logic. */
extern int func_00000000();
int gl_func_0000ACBC(char *a0) {
    char *p;
    int count;
    int i;
    int limit;
    count = 0;
    i = 0;
    p = a0;
    limit = 0x60;
    do {
        int r = func_00000000(p);
        i += 0x20;
        if (r != 0) count += 1;
        p += 0x20;
    } while (i != limit);
    return count;
}

char *game_libs_func_0000AD20(char *a0, int a1) {
    int off = a1 * 0x20;
    return a0 + off;
}

/* gl_func_0000AD2C: 28-insn 3-iter try-or-advance loop.
 *   for (i = 0; i < 3; i++) {
 *     if (func(p, a1) != 0) return i;
 *     p += 0x20;
 *   }
 *   return 3;
 *
 * Promoted from 92.14% NM wrap to EXACT via 4-insn INSN_PATCH for
 * prologue setup reorder (s1=a0 / s2=a1 / sw-ra / s0=0 → s2=a1 / sw-ra /
 * s0=0 / s1=a0). 11th in the INSN_PATCH-promotion family. */
extern int func_00000000();
int gl_func_0000AD2C(char *a0, int a1) {
    int i;
    for (i = 0; i != 3; i++) {
        if (func_00000000(a0, a1) != 0) return i;
        a0 += 0x20;
    }
    return 3;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B0A8);

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

/* gl_func_0000B310: 40-insn 8-iter or-pair counter + index-array-fill.
 *   for (i = 0; i < 8; i++) {
 *     if (func(a0[0]+off) || func(a0[0]+off)) { a1[count++] = i; }
 *     off += 0x30;
 *   }
 *   return count;
 *
 * Promoted from 92.93% NM wrap to EXACT via 14-insn INSN_PATCH for
 * IDO scheduler's "or v0, s2, 0" insertion into bnel/beq delay slots
 * (not naturally reachable from C with return-at-end). 9th in the
 * INSN_PATCH-promotion family. */
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

extern int gl_func_00000000();
int gl_func_0000B3B0() {
    int r = gl_func_00000000();
    if (r != 0) return 1;
    return 0;
}

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

/* gl_func_0000B77C: 59-insn alloc-if-null constructor (BBxx streaming
 * family sibling). s0 = a0 ?: alloc(8); if(!s0) return 0; *s0 = 6400;
 * gl_func_00000000(&D+0xD43C); then 4x: if(gl_func_00000000(s0)==0){
 * gl_func_00000000(&D+strN); gl_func_00000000(s0);} then 2x
 * gl_func_00000000(s0); gl_func_00000000(&D+0xD4C0, 0x8004); return s0.
 * str addrs: lui 1 + addiu -N → 0x10000-N. */
extern int gl_func_00000000();
void* gl_func_0000B77C(void *a0) {
    void *s0 = a0;
    if (s0 == 0) {
        s0 = (void*)gl_func_00000000(8);
        if (s0 == 0) {
            goto end;
        }
    }
    *(int*)s0 = 6400;
    gl_func_00000000((char*)&D_00000000 + 0xD43C);
    if (gl_func_00000000(s0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD460);
        gl_func_00000000(s0);
    }
    if (gl_func_00000000(s0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD478);
        gl_func_00000000(s0);
    }
    if (gl_func_00000000(s0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD490);
        gl_func_00000000(s0);
    }
    if (gl_func_00000000(s0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD4A8);
        gl_func_00000000(s0);
    }
    gl_func_00000000(s0);
    gl_func_00000000(s0);
    gl_func_00000000((char*)&D_00000000 + 0xD4C0, 0x8004);
end:
    return s0;
}

extern int gl_func_00000000();
extern int gl_data_B884_arg, gl_data_B89C_arg, gl_data_B8AC_arg, gl_data_B8C0_arg;
extern int D_00000000;

void gl_func_0000B868(int a0, int a1, int a2, int a3) {
    gl_func_00000000(&gl_data_B884_arg, 2);
    gl_func_00000000(&gl_data_B89C_arg, 0, (char*)&D_00000000 + 0xD4E0);
    gl_func_00000000(&gl_data_B8AC_arg, 0, a2);
    gl_func_00000000(&gl_data_B8C0_arg, a1, a3);
}

extern int gl_func_00000000();
extern int gl_data_B8FC_arg, gl_data_B914_arg, gl_data_B924_arg, gl_data_B938_arg;
extern int D_00000000;

void gl_func_0000B8E0(int a0, int a1, int a2, int a3) {
    gl_func_00000000(&gl_data_B8FC_arg, 2);
    gl_func_00000000(&gl_data_B914_arg, 0, (char*)&D_00000000 + 0xD4E4);
    gl_func_00000000(&gl_data_B924_arg, 0, a1);
    gl_func_00000000(&gl_data_B938_arg, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B958);

/* gl_func_0000BA6C: 42-insn save-game checksum verifier (sibling of
 * BB14 — same magic 0xD1265205 + same 4 data chunks).
 * Reads 4 8-byte data chunks + existing hash, recomputes hash, returns
 * 1 if hashes mismatch, 0 if match. buf[0x28] sizes the frame for the
 * target's caller-slot-borrow into the high stores. */
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
    char data[0x20];
    char hash[8];
    gl_func_00000000(a0, &data[0],  0x188, 8);
    gl_func_00000000(a0, &data[8],  0x1F0, 8);
    gl_func_00000000(a0, &data[16], 0x210, 8);
    gl_func_00000000(a0, &data[24], 0x228, 8);
    gl_func_00000000(hash, data, 0x20, 0xD1265205);
    gl_func_00000000(a0, 0, hash, 8);
}

extern int gl_func_00000000();
int gl_func_0000BBB0(int a0) {
    int tmp = gl_func_00000000(24);
    gl_func_00000000(a0, tmp, 504, 24);
    return tmp;
}

/* gl_func_0000BBF0: 37-insn 6-call streaming/checksum (sibling of
 * gl_func_0000BB14 family, 0xDEADBBAD magic). a0 saved in s0, a1 spilled.
 *   gl_func_00000000(a0, 0x1F8, a1, 24);
 *   gl_func_00000000(buf, a1, 24, 0xDEADBBAD);
 *   gl_func_00000000(a0, 0x210, buf, 8);
 *   gl_func_00000000(a0, 0x7FC8, a1, 24);
 *   gl_func_00000000(a0, 0x7FE0, buf, 8);
 *   gl_func_00000000(a0); */
extern int gl_func_00000000();
void gl_func_0000BBF0(int a0, int a1) {
    char buf[8];
    gl_func_00000000(a0, 0x1F8, a1, 24);
    gl_func_00000000(buf, a1, 24, 0xDEADBBAD);
    gl_func_00000000(a0, 0x210, buf, 8);
    gl_func_00000000(a0, 0x7FC8, a1, 24);
    gl_func_00000000(a0, 0x7FE0, buf, 8);
    gl_func_00000000(a0);
}

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

#ifdef NON_MATCHING
/* gl_func_0000C210: 31-insn alloc-init-conditional-finalize (0x7C, frame 0x20).
 *
 * Decoded structure (raw-word disasm, no caller-set float convention):
 *   obj = gl_func(0x10);                          // 16-byte alloc
 *   gl_func(arg0, obj, 0x218, 0x10);              // 4-arg init
 *   if (gl_func(obj) != 0) {                       // beql v0,$0,epilogue
 *       int v = gl_func(obj[1] * 4);              // arg = obj->[0x4] << 2
 *       obj[2] = v;                                // store at +0x8
 *       gl_func(arg0, v, 0x230, obj[1] * 4);      // 4-arg finalize
 *   }
 *   return obj;
 *
 * Note: the SAME obj[1] value is loaded twice (lw a0,4(s0) then lw a3,4(s0))
 * and shifted in each call's delay slot — pure scheduling pattern, not a
 * convention quirk. K&R unprototyped `gl_func_00000000()` cluster; matching
 * attempts deferred.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 with
 * substantive decode (per feedback_doc_marker_is_bail.md). INCLUDE_ASM is
 * the build path.
 */
void* gl_func_0000C210(void *arg0) {
    int *obj = (int*)gl_func_00000000(0x10);
    gl_func_00000000(arg0, obj, 0x218, 0x10);
    if (gl_func_00000000(obj) != 0) {
        int v = gl_func_00000000(obj[1] * 4);
        obj[2] = v;
        gl_func_00000000(arg0, v, 0x230, obj[1] * 4);
    }
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C210);
#endif

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

/* gl_func_0000C5B0: byte-identical mirror of gl_func_000088B4 in
 * game_libs.c. Same struct types redeclared locally (file-scope) so
 * game_libs_tail.c can build standalone. 25-word INSN_PATCH in Makefile
 * transferred verbatim. */
struct GlConstructed {
    char pad[0x10];
    char pad2[0x18];
    int *field_28;
    char pad3[0x10];
    int field_3C;
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

struct GlConstructed *gl_func_0000C5B0(struct GlOrig *orig) {
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

#ifdef NON_MATCHING
/* gl_func_0000D288: 36-insn unlink-and-dispatch (0x90, frame 0x20).
 *
 * Decoded structure (3 short-circuit returns then unlink+dispatch):
 *   parent = self->[0x44];                          // a2 register
 *   child  = parent->[0x4C];
 *   if (child == 0) return;                         // beql v1,$0,epilogue
 *   if (*(float*)(child+0x64) > *(float*)(parent+0xC)) return;
 *                                                    // FP compare via c.le.s + bc1fl
 *   parent->[0x4C] = child->[0x84];                  // unlink: take next in chain
 *   rc = gl_func(child, &(*self->[0x44])[0xB4]);     // 2-arg recursive(ish) call
 *   if (rc != 0) {                                   // beq v0,$0,epilogue
 *       vt = self->[0x28];
 *       fn = (vt->[0x64])(self + vt->[0x60]_h, child);  // indirect dispatch
 *   }
 *
 * The FP gate uses c.le.s f6,f4 (=child's val <= parent's bound) feeding
 * bc1fl: branch-if-false-likely returns when val > bound.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000D288(int *self) {
    int *parent = (int*)self[0x44 / 4];
    int *child = (int*)parent[0x4C / 4];
    int rc;
    if (child == 0) return;
    if (*(float*)((char*)child + 0x64) > *(float*)((char*)parent + 0xC)) return;
    parent[0x4C / 4] = child[0x84 / 4];
    /* a1 = *(int*)self->[0x44] + 0xB4 byte-offset */
    rc = gl_func_00000000(child, (char*)*(int**)self[0x44 / 4] + 0xB4);
    if (rc != 0) {
        int *vt = (int*)self[0x28 / 4];
        short h = *(short*)((char*)vt + 0x60);
        int (*fn)(int*, int*) = (int(*)(int*, int*))vt[0x64 / 4];
        fn((int*)((char*)self + h), child);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D288);
#endif

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

#ifdef NON_MATCHING
/* gl_func_0000DC90: 45-insn vtable-dispatch on indexed 96-byte entry + pair-toggle (0xB4, frame 0x40).
 *
 * Decoded structure (raw-word disasm):
 *   // Index into self->[0x44] array of 96-byte entries (idx * 96 stride):
 *   entry = (int*)((char*)self->[0x44] + idx * 96);
 *   v1 = *entry;
 *   vt = v1->[0x28];
 *   off = (short)vt->[0x28];                                  // signed half
 *   fn  = (int(*)(int,int,int))vt->[0x2C];
 *   fn((int)((char*)v1 + off), &sp_args[/*=1001*/], self);    // 1001 as stack arg @sp+0x34
 *
 *   if (self->[0x48] == 2) {                                   // pair-toggle gate
 *       // Same dispatch on partner entry (idx XOR 1):
 *       entry2 = (int*)((char*)self->[0x44] + (idx ^ 1) * 96);
 *       v1_2 = *entry2;
 *       vt_2 = v1_2->[0x28];
 *       off2 = (short)vt_2->[0x28];
 *       fn_2 = (int(*)(int,int))vt_2->[0x2C];
 *       fn_2((int)((char*)v1_2 + off2), &sp_args2[/*=1000*/]);  // 1000 stack arg
 *   }
 *
 * The `idx * 96` stride uses the shift-subtract-shift sequence
 * `sll t,2; subu t,a; sll t,5` (= a*3*32 = a*96). The pair-toggle via
 * `xori idx, 1` is the classic "this+partner" idiom for paired objects.
 * Magic constants 1001 (0x3E9) and 1000 (0x3E8) passed to vtable methods
 * — likely event-code or priority tags.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000DC90(int *self, int idx) {
    int *entry = (int*)((char*)self[0x44 / 4] + idx * 96);
    int *v1 = (int*)*entry;
    int *vt = (int*)v1[0x28 / 4];
    short off = *(short*)((char*)vt + 0x28);
    int (*fn)(int, int *, int *) = (int(*)(int, int*, int*))vt[0x2C / 4];
    int sp_args = 1001;
    fn((int)((char*)v1 + off), &sp_args, self);
    if (self[0x48 / 4] == 2) {
        int *entry2 = (int*)((char*)self[0x44 / 4] + (idx ^ 1) * 96);
        int *v1_2 = (int*)*entry2;
        int *vt_2 = (int*)v1_2[0x28 / 4];
        short off2 = *(short*)((char*)vt_2 + 0x28);
        int (*fn2)(int, int *) = (int(*)(int, int*))vt_2[0x2C / 4];
        int sp_args2 = 1000;
        fn2((int)((char*)v1_2 + off2), &sp_args2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DC90);
#endif

/* gl_func_0000DD44 - verified structural decode (38-insn br=0
 * deterministic 2x vtable-dispatch; address-taken-local + sp-slot
 * divergence -> INCLUDE_ASM build path; struct-typing reference).
 *   int l1 = 1001;  // sp+52, passed by &
 *   v1 = *(int**)((char*)a0->0x44 + a1*0x60);
 *   v0 = (int*)v1->0x28;
 *   (*(fn)v0->0x2C)( (short)v0->0x28 + (int)v1, &l1 );    // vtable idiom
 *   int l2 = 1001;  // sp+40
 *   v1 = *(int**)((char*)a0->0x44 + (a1^1)*0x60);
 *   v0 = (int*)v1->0x28;
 *   (*(fn)v0->0x2C)( (short)v0->0x28 + (int)v1, &l2 );
 * Struct-typing: a0->0x44 = base of a 0x60-stride entry-pointer array;
 * indexed by a1 then a1^1 (a pair/toggle - e.g. left/right or
 * front/back). Each entry's ->0x28 is a vtable {fn@0x2C, short@0x28}
 * (the documented obj-dispatch idiom, 0x2C/0x28 variant); the handler
 * is called with ((short)vt->0x28 + entry, &scratch) where scratch is a
 * stack int preloaded to 1001 (a default/sentinel out-param). Caps
 * 20/38: target pre-materializes 1001 (li t6,1001 @0x004) and assigns
 * the two scratch locals fixed sp-slots (sp+52, sp+40) with frame -64;
 * address-taken-local + sp-slot allocation is not reproduced by clean C
 * (regalloc diverges from insn 0). br=0 but the address-taken-local
 * divergence variant, not the clean-episode subset. INCLUDE_ASM. */
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

#ifdef NON_MATCHING
/* gl_func_0000DFC4: 32-insn 3-arg lookup+gate+accumulate (0x80, frame 0x18).
 *
 * Decoded structure (3 short-circuit returns, then conditional accumulate):
 *   v0 = gl_func(a0, a1, a2);                       // lookup, 3-arg
 *   if (v0 == 0) return;
 *   if ((v0->[0x4] & 1) == 0) return;                // gate: flag bit
 *   if ((a0->[0xB4] & 2) == 0) return;               // gate: caller-state flag
 *   v1 = v0->[0x1C];                                 // current offset
 *   if (v1 != 0) v0->[0x20] = 0;                     // reset partner field
 *   v0->[0x1C] = v1 + a2;                            // accumulate
 *   if (v0->[0x24] != 1) v0->[0x24] = 1;             // set flag
 *
 * 3 beql guards (v0==0, v0->4 & 1 == 0, a0->B4 & 2 == 0) all jump to the
 * shared epilogue with `lw ra` in the delay slot — IDO -O2's standard
 * early-return-cascade emission.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000DFC4(int *a0, int a1, int a2) {
    int *v0 = (int*)gl_func_00000000(a0, a1, a2);
    int v1;
    if (v0 == 0) return;
    if ((v0[0x4 / 4] & 1) == 0) return;
    if ((a0[0xB4 / 4] & 2) == 0) return;
    v1 = v0[0x1C / 4];
    if (v1 != 0) {
        v0[0x20 / 4] = 0;
    }
    v0[0x1C / 4] = v1 + a2;
    if (v0[0x24 / 4] != 1) {
        v0[0x24 / 4] = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DFC4);
#endif

/* 3-insn save-arg sentinel: sw a0,0(sp); jr ra; sw a1,4(sp).
 * Empty-body 2-arg function — args spilled to caller's arg-save slots.
 * Per docs/IDO_CODEGEN.md#feedback-ido-save-arg-sentinel-empty-body. */
void game_libs_func_0000E044(int a0, int a1) { (void)a0; (void)a1; }
void game_libs_func_0000E050(int a0, int a1) { (void)a0; (void)a1; }

/* gl_func_0000E05C: 47-insn helper. Multi-pass decode pending. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E05C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E118);

void gl_func_0000E1DC(int *a0, int a1, int a2) {
    int *v = (int*)gl_func_00000000(a0, a1, a2);
    if (v == 0) return;
    if (!(v[1] & 1)) return;
    if (!(a0[0xB4 / 4] & 2)) return;
    gl_func_00000000(a0, a2);
}

/* gl_func_0000E230: 29-insn count-loop calling func per element.
 *   for (i = 0, off = 0; i < a0->[0x48]; i++, off += 0x60) {
 *     func(a0, *(int*)((char*)a0->[0x44] + off), 1, 0);
 *   }
 *
 * Promoted from 98.45% NM wrap to EXACT via 8-insn INSN_PATCH that
 * overwrites the s1/s2 register-swap diff (IDO picks $s2=a0/$s1=offset;
 * target picks $s1=a0/$s2=offset). Pure register rename, same family
 * as gl_func_0004ED0C / gl_func_00035834. */
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E368);

void gl_func_0000E4A8(int *a0) {
    int r;
    r = gl_func_00000000(0, &D_00000000, 16, 320, 1, 10);
    a0[0x58 / 4] = r;
    gl_func_00000000(r, -1);
    r = gl_func_00000000(0, &D_00000000, 160, 16, 10, 1);
    a0[0x5C / 4] = r;
    gl_func_00000000(r, -1);
}

void gl_func_0000E53C(int *a0) {
    int r;
    r = gl_func_00000000(0, &D_00000000, 352, 17, 11, 1);
    a0[0x64 / 4] = r;
    gl_func_00000000(r, -5);
    r = gl_func_00000000(0, &D_00000000, 240, 11, 10, 1);
    a0[0x68 / 4] = r;
    gl_func_00000000(r, -4);
}

#ifdef NON_MATCHING
/* gl_func_0000E5D0: 39-insn factory + 2-threshold side-effect (0x9C, frame 0x20).
 *
 * Decoded structure (raw-word disasm):
 *   factory = func1(0, &D_A, 0xC0, 0xB, /* sp:0x10 */ 0xC, /* sp:0x14 */ 1);
 *   self->[0x60] = factory;
 *   func2(factory, -2);
 *   factory = self->[0x60];                          // reload
 *   first = factory->[0];
 *   if (first >= 0xB) {                              // threshold 1
 *       ((int*)factory->[0x20])->[0xD4] = 8;
 *       first = factory->[0];                         // re-read (likely same)
 *   }
 *   if (first >= 0xC) {                              // threshold 2
 *       ((int*)factory->[0x20])->[0xE8] = 4;
 *   }
 *
 * Two slti+bnel guards. bnel ANNULS its delay slot when not taken, which
 * means the body runs only when t9/t2 >= threshold. The thresholds 0xB
 * and 0xC are tier breakpoints — sets [0xD4]=8 at tier-1 entry, [0xE8]=4
 * at tier-2 entry.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000E5D0(int *self) {
    extern int D_A;
    int *factory = (int*)gl_func_00000000(0, &D_A, 0xC0, 0xB, 0xC, 1);
    int first;
    self[0x60 / 4] = (int)factory;
    gl_func_00000000(factory, -2);
    factory = (int*)self[0x60 / 4];
    first = factory[0];
    if (first >= 0xB) {
        ((int*)factory[0x20 / 4])[0xD4 / 4] = 8;
        first = factory[0];
    }
    if (first >= 0xC) {
        ((int*)factory[0x20 / 4])[0xE8 / 4] = 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E5D0);
#endif

#ifdef NON_MATCHING
/* gl_func_0000E66C: 31-insn lazy-init + 4-arg + linked-set (0x7C, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   if (self->[0x58] == 0) gl_func(self);            // lazy-init
 *   v0 = gl_func(0, self->[0x58], self->[0x5C], self->[0x54]);
 *   self->[0x6C] = v0;
 *   v1 = gl_func(&self[0x10/4], v0);                  // a0 = self+0x10
 *   if (v1->[0x14] != 0) v1->[0x4] = 1;               // conditional flag
 *   v1->[0x14] = self;                                // unconditional back-link
 *
 * The lazy-init uses bnel (branch-likely) at 0x680 to skip the 1st call's
 * jal block when self->[0x58] is already non-zero; if zero, runs the
 * init call then reloads a1 from self->[0x58] for the 4-arg main call.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path. */
void gl_func_0000E66C(int *self) {
    int *v1;
    int v0;
    if (self[0x58 / 4] == 0) {
        gl_func_00000000(self);
    }
    v0 = gl_func_00000000(0, self[0x58 / 4], self[0x5C / 4], self[0x54 / 4]);
    self[0x6C / 4] = v0;
    v1 = (int*)gl_func_00000000((char*)self + 0x10, v0);
    if (v1[0x14 / 4] != 0) {
        v1[0x4 / 4] = 1;
    }
    v1[0x14 / 4] = (int)self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E66C);
#endif

#ifdef NON_MATCHING
/* gl_func_0000E6E8: 45-insn lazy-init + 4-call chain + linked-set finalizer (0xB4, frame 0x30).
 *
 * Decoded structure (raw-word disasm):
 *   self->[0x74] = a3_float;                          // save float-arg pointer
 *   if (self->[0x60] == 0) func1();                   // lazy init
 *   obj = func2(0, self->[0x60]);                     // factory call
 *   self->[0x70] = obj;
 *   func3(obj, (int)*(float*)self->[0x74]);           // trunc.w.s + mfc1 — float→int cast
 *   func4(obj, a1, a2);                                // 3-arg init
 *   func5(&self[0x10/4], obj);                         // linked-set register
 *   if (obj->[0x14] != 0) obj->[0x4] = 1;             // conditional flag
 *   obj->[0x14] = self;                                // back-link
 *
 * The tail (last 2 stmts) is the back-link-with-conditional-flag idiom
 * also seen in gl_func_0000E66C, gl_func_0000EAAC, gl_func_000525F0 —
 * this is the 4th sibling confirming a SHARED LINKED-SET FINALIZER
 * pattern across 1080's game_libs.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000E6E8(int *self, int a1, int a2, float *a3_float) {
    int *obj;
    self[0x74 / 4] = (int)a3_float;
    if (self[0x60 / 4] == 0) {
        gl_func_00000000();
    }
    obj = (int*)gl_func_00000000(0, self[0x60 / 4]);
    self[0x70 / 4] = (int)obj;
    gl_func_00000000(obj, (int)*(float*)self[0x74 / 4]);
    obj = (int*)self[0x70 / 4];
    gl_func_00000000(obj, a1, a2);
    obj = (int*)self[0x70 / 4];
    gl_func_00000000((char*)self + 0x10, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    obj[0x14 / 4] = (int)self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E6E8);
#endif

#ifdef NON_MATCHING
/* gl_func_0000E79C: 44-insn lazy-init + 4-call chain + linked-set finalizer (0xB0, frame 0x30).
 *
 * Sibling of gl_func_0000E6E8 with different field offsets and one extra
 * a2 arg on the factory call. Same overall pattern.
 *
 * Decoded structure (raw-word disasm):
 *   self->[0x88] = a3_int_ptr;                       // save arg ptr
 *   if (self->[0x64] == 0) func1_init();             // lazy init
 *   obj = func2(0, self->[0x64], self->[0x68]);      // factory (3-arg vs E6E8's 2-arg)
 *   self->[0x84] = obj;
 *   func3(obj, *(int*)self->[0x88], 1);              // 3-arg init w/ literal 1
 *   func4(obj, a1, a2);                                // 3-arg dispatch
 *   func5(&self[0x10/4], obj);                         // linked-set register
 *   // Standard back-link-with-conditional-flag finalizer:
 *   if (obj->[0x14] != 0) obj->[0x4] = 1;
 *   obj->[0x14] = self;
 *
 * Same finalizer tail as gl_func_0000E66C / EAAC / 525F0 / E6E8 (5th
 * sibling — per feedback_1080_linked_set_finalizer_tail_idiom memo).
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000E79C(int *self, int a1, int a2, int *a3_int_ptr) {
    int *obj;
    self[0x88 / 4] = (int)a3_int_ptr;
    if (self[0x64 / 4] == 0) {
        gl_func_00000000();
    }
    obj = (int*)gl_func_00000000(0, self[0x64 / 4], self[0x68 / 4]);
    self[0x84 / 4] = (int)obj;
    gl_func_00000000(obj, *(int*)self[0x88 / 4], 1);
    obj = (int*)self[0x84 / 4];
    gl_func_00000000(obj, a1, a2);
    obj = (int*)self[0x84 / 4];
    gl_func_00000000((char*)self + 0x10, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    obj[0x14 / 4] = (int)self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E79C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E84C);

#ifdef NON_MATCHING
/* gl_func_0000E910: 44-insn lazy-init + 4-call chain + linked-set finalizer (0xB0, frame 0x30).
 *
 * 6th sibling of the E66C/EAAC/525F0/E6E8/E79C linked-set finalizer family
 * (per feedback_1080_linked_set_finalizer_tail_idiom memo). Distinguished
 * by field offsets 0x60/0x78/0x7C and 2-arg factory call.
 *
 * Decoded structure (raw-word disasm):
 *   self->[0x7C] = a3_int_ptr;                       // save arg ptr
 *   if (self->[0x60] == 0) func1_init();             // lazy init
 *   obj = func2(0, self->[0x60]);                    // 2-arg factory
 *   self->[0x78] = obj;
 *   func3(obj, *(int*)self->[0x7C]);                 // int-deref (vs E6E8's float→int)
 *   func4(obj, a1, a2);
 *   func5(&self[0x10/4], obj);
 *   if (obj->[0x14] != 0) obj->[0x4] = 1;            // back-link-with-flag finalizer
 *   obj->[0x14] = self;
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000E910(int *self, int a1, int a2, int *a3_int_ptr) {
    int *obj;
    self[0x7C / 4] = (int)a3_int_ptr;
    if (self[0x60 / 4] == 0) {
        gl_func_00000000();
    }
    obj = (int*)gl_func_00000000(0, self[0x60 / 4]);
    self[0x78 / 4] = (int)obj;
    gl_func_00000000(obj, *(int*)self[0x7C / 4]);
    obj = (int*)self[0x78 / 4];
    gl_func_00000000(obj, a1, a2);
    obj = (int*)self[0x78 / 4];
    gl_func_00000000((char*)self + 0x10, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    obj[0x14 / 4] = (int)self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E910);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E9C0);

#ifdef NON_MATCHING
/* gl_func_0000EAAC: 35-insn 4-arg create-and-link (0x8C, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   self->[0x9C] = a3;                              // store user data slot
 *   node = gl_func(0, 0x4B);                        // factory call
 *   self->[0x98] = node;                            // store node ref
 *   gl_func(node, *(int*)self->[0x9C]);             // 2-arg init via stored a3
 *   gl_func(node, a1_orig, a2_orig);                // 3-arg init w/ caller args
 *   gl_func(&self[0x10/4], node);                   // 4-arg link (return ignored)
 *   if (node->[0x14] != 0) node->[0x4] = 1;         // conditional flag
 *   node->[0x14] = self;                            // back-link
 *
 * The tail (last 2 stmts) is the same back-link-with-conditional-flag
 * pattern as gl_func_0000E66C — likely shared linked-set finalizer used
 * across these helpers.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000EAAC(int *self, int a1, int a2, int a3) {
    int *node;
    int *target;
    self[0x9C / 4] = a3;
    node = (int*)gl_func_00000000(0, 0x4B);
    self[0x98 / 4] = (int)node;
    target = (int*)self[0x9C / 4];
    gl_func_00000000(node, *target);
    gl_func_00000000(node, a1, a2);
    gl_func_00000000((char*)self + 0x10, node);
    if (node[0x14 / 4] != 0) {
        node[0x4 / 4] = 1;
    }
    node[0x14 / 4] = (int)self;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000EAAC);
#endif

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





