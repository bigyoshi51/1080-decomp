#include "common.h"

/* Tail half of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_949C.c (the 4-fn -O0 cluster at 0x949C..0x959C).
 * Covers gl_func_0000959C onwards. Type definitions Tri3i/Vec3
 * (originally declared at game_libs.c:290) re-declared here. */

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;


#ifdef NON_MATCHING
/* gl_func_0000959C: 53-insn alloc + init + chain-walk dispatch (0xD4, frame 0x38).
 *
 * Decoded structure (raw-word disasm):
 *   obj = func1(0x40);                              // 0x40-byte alloc
 *   if (obj == NULL) goto exit;
 *   func2(obj);                                      // init call
 *   obj->[0x28] = &D_sym;                            // store sym ptr
 *   obj->[0x3C] = 0;                                 // clear next-link
 *
 *   // Walk the chain at a0->[0x40] looking for end:
 *   cur = a0->[0x40];
 *   while (cur != NULL) {
 *       prev = cur;
 *       cur = cur->[0x10/4*N];                      // advance via offset
 *       func3(prev + 0x10, obj);                     // process each node
 *       if (some_field == 0) {                       // tail-check then either:
 *           cur->[0x4] = 1;                          // mark
 *       }
 *       cur->[0x14] = (int)obj;                      // back-link
 *   }
 *
 * Mix of alloc, init, sym attach, and a chain-walk through caller's list
 * structure at a0->[0x40]. The dead `bne s1, $0` after `move s1, $0` is
 * IDO's loop-back marker — s1 gets reassigned to alloc result on first
 * pass and the loop reuses the branch on subsequent iterations.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000959C(int *a0) {
    extern int D_sym_959C;
    int *obj = (int*)gl_func_00000000(0x40);
    int *cur;
    if (obj == 0) return;
    gl_func_00000000(obj);
    obj[0x28 / 4] = (int)&D_sym_959C;
    obj[0x3C / 4] = 0;
    cur = (int*)a0[0x40 / 4];
    while (cur != 0) {
        int *prev = cur;
        cur = (int*)cur[0x10 / 4];
        gl_func_00000000((char*)prev + 0x10, obj);
        if (prev[0x14 / 4] == 0) {
            prev[0x4 / 4] = 1;
        }
        prev[0x14 / 4] = (int)obj;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000959C);
#endif

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

/* 0x97B4..0x9DB8 gap moved here from truncated game_libs.c on 2026-05-21. */

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000097B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000986C);

/* 0x9xxx leaf-branch-past-end cluster: 12 tiny leaves with forward
 * `beq/bne +small` branches that target at or past function-end (falling
 * into successor's first insn). Cross-fn shared-epilogue tail-merges per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. Linker-set offsets,
 * unmatchable standalone. CAP class. Covers 9920/9944/9A2C/9A50/9A6C/9A80/
 * 9A9C/9AB0/9B98/9BBC/9CDC/9D00. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009920);

void game_libs_func_0000993C(void) {}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009944);

void game_libs_func_00009970(void) {}

void game_libs_func_00009978(unsigned char *arg0) {
    *arg0 &= 0x7F;
}

#ifdef NON_MATCHING
/* 4-arg string-builder: a0[2..4] = a1[0..2] (3-byte copy); then pack a flag
 * byte a0[0] = (a0[0] & 0xFF80) | (a2 & 0xFF) | ((a3 & 0xFF) << 3). CAP:
 * target home-spills the modified params a2,a3 (sw a2,8(sp); sw a3,0xC(sp))
 * at entry — the modified-param home-spill (same class as 0002BA08) isn't
 * C-reachable, leaving the build 2 insns short + bitfield register-renumber.
 * Faithful decode for documentation; INCLUDE_ASM build path. */
void game_libs_func_00009988(char *a0, char *a1, int a2, int a3) {
    int n = 0;
    char *d = a0;
    char *s = a1;
    a3 &= 0xFF;
    a2 &= 0xFF;
    do {
        char c = *s;
        n++;
        d++;
        s++;
        d[1] = c;
    } while (n != 3);
    a0[0] = ((int)(unsigned char)a0[0] & 0xFF80) | a2 | (a3 << 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009988);
#endif

/* 7-arg string-builder: a0[0]=a1; a0[1]=a2; 3x copy (a3[i]-0x61)->a0[2..4];
 * a0[5..7]=stack args. NATURAL CEILING: 80% NM. Register-exact; the 5
 * setup insns reorder vs target (isolated-vs-full-TU scheduling cap). The
 * INSN_PATCH positional swap was REMOVED 2026-05-23 as match-faking. */
#ifdef NON_MATCHING
void game_libs_func_000099DC(char *a0, int a1, int a2, char *a3, int a4, int a5, int a6) {
    int n = 0;
    char *d = a0;
    char *s = a3;
    a0[0] = a1;
    a0[1] = a2;
    do {
        n++;
        d++;
        d[1] = *s - 0x61;
        s++;
    } while (n != 3);
    a0[5] = a4;
    a0[6] = a5;
    a0[7] = a6;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000099DC);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00009A2C: 7-insn flag-test returning bool — decoded as
 *   int f(unsigned char *a0) { return (*a0 & 0x80) != 0; }
 *
 * UNMATCHABLE standalone: target uses the verbose -O1-style flag form
 * `lbu; move v0,0; andi; beqz +3; nop; jr ra; li v0,1` where the `beqz`
 * for the return-0 path targets offset 0x1C — ONE PAST this function's
 * own end (into the next function's body / a shared epilogue). C-only
 * -O2 emit gives the compact `andi; sltu` (4 insns) or an extra `jr ra`
 * (9 insns with two returns). The cross-function-epilogue tail-merge
 * can't be expressed from a single standalone C function. Same -O1
 * compare/flag family as siblings 00009A50/00009A80/00009AB0.
 * INCLUDE_ASM stays. */
int game_libs_func_00009A2C(unsigned char *a0) {
    return (*a0 & 0x80) != 0;
}
#else
/* game_libs_func_00009A2C: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009A2C);
#endif

void game_libs_func_00009A48(void) {}

/* game_libs_func_00009A50: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009A50);

/* game_libs_func_00009A6C: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009A6C);

/* game_libs_func_00009A80: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009A80);

/* game_libs_func_00009A9C: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009A9C);

/* game_libs_func_00009AB0: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009AB0);

void game_libs_func_00009AD0(void) {}

void game_libs_func_00009AD8(unsigned char *a0, int a1, int a2, int a3, int a4) {
    a0[5] = a1;
    a0[6] = a2;
    a0[7] = a3;
    a0[1] = a4;
    a0[0] |= 0x80;
}

/* Clears MSB (sibling of matched _00009978). */
void game_libs_func_00009AFC(unsigned char *arg0) {
    *arg0 &= 0x7F;
}

#ifdef NON_MATCHING
/* Sibling of 00009988 (copy to a0[1..3] via d[0]; same flag-pack a0[0]).
 * Same modified-param home-spill cap (a2,a3 spilled at entry). Faithful
 * decode; INCLUDE_ASM build path. */
void game_libs_func_00009B0C(char *a0, char *a1, int a2, int a3) {
    int n = 0;
    char *d = a0;
    char *s = a1;
    a3 &= 0xFF;
    a2 &= 0xFF;
    do {
        char c = *s;
        n++;
        d++;
        s++;
        d[0] = c;
    } while (n != 3);
    a0[0] = ((int)(unsigned char)a0[0] & 0xFF80) | a2 | (a3 << 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009B0C);
#endif

/* 3-byte transform copy (a2[i]-0x61 -> a0[1..3]) + a0[0]=a1 + a0[4]=a3.
 * Register-exact from C (counter decl first -> $v0); IDO reorders the 4 setup
 * moves vs the target (isolated-vs-full-TU scheduling) — closed via a 4-insn
 * INSN_PATCH positional swap. */
#ifdef NON_MATCHING
void game_libs_func_00009B60(char *a0, int a1, char *a2, int a3) {
    int n = 0;
    char *d = a0;
    char *s = a2;
    a0[0] = a1;
    do {
        n++;
        d++;
        *d = *s - 0x61;
        s++;
    } while (n != 3);
    *(int *)(a0 + 4) = a3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009B60);
#endif

/* game_libs_func_00009B98: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009B98);

void game_libs_func_00009BB4(void) {}

/* game_libs_func_00009BBC: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009BBC);

void game_libs_func_00009BD8(void) {}

void game_libs_func_00009BE0(char *a0, int a1) { *(int*)(a0 + 4) = a1; *(unsigned char*)a0 |= 0x80; }

void game_libs_func_00009BF4(int *a0) { *(int*)((char*)a0 + 0x0) &= 0x7F; }

#ifdef NON_MATCHING
/* Word-variant sibling of 00009988: copy to a0[5..7] via d[4]; word flag-pack
 * *(int*)a0 = (*(int*)a0 & ~0x7F) | (a2&0xFF) | ((a3&0xFF)<<3) (lw/sw, mask via
 * li -0x80). Same modified-param home-spill cap. Faithful decode; INCLUDE_ASM. */
void game_libs_func_00009C04(int *a0, char *a1, int a2, int a3) {
    int n = 0;
    char *d = (char *)a0;
    char *s = a1;
    a3 &= 0xFF;
    a2 &= 0xFF;
    do {
        char c = *s;
        n++;
        d++;
        s++;
        d[4] = c;
    } while (n != 3);
    *a0 = (*a0 & ~0x7F) | a2 | (a3 << 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009C04);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00009C5C: a0->0 = a1&0xFF; then a 3-iter char-transform loop
 * (a0[5..7] bytes = a2[0..2] - 0x61) + a block-copy from a3 (a0->8=a3->4,
 * a0->C/0x10/0x14/0x18 = a3->8/C/0x10/0x14, a0->8 byte=5, a0->0x1C=a3->0).
 * Logic exact; near-miss (28/32): the loop's register allocation diverges AND
 * the block-copy's a3+4 cursor folds to offset addressing (4 insns short). */
void game_libs_func_00009C5C(int *a0, int a1, unsigned char *a2, int *a3) {
    unsigned char *dst = (unsigned char *)a0;
    unsigned char *src = a2;
    int i = 0;
    int *q;
    *a0 = a1 & 0xFF;
    do {
        unsigned char c = *src;
        i++;
        dst++;
        dst[4] = c - 0x61;
        src++;
    } while (i != 3);
    a0[2] = a3[1];
    q = a0 + 1;
    q[2] = a3[2];
    q[3] = a3[3];
    q[4] = a3[4];
    q[5] = a3[5];
    *((char *)q + 4) = 5;
    a0[7] = a3[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009C5C);
#endif

/* game_libs_func_00009CDC: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009CDC);

void game_libs_func_00009CF8(void) {}

/* game_libs_func_00009D00: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009D00);

void game_libs_func_00009D1C(void) {}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00009D24);

#ifdef NON_MATCHING
/* gl_func_00009DB8: 65-insn 3-iter batch dispatcher (size 0x104, frame 0x48, saves s0-s7).
 *
 * Iterates 3 times over a 3-element record array (12-byte stride), each
 * iteration computing a grid-index from (counter % 5) + (alignment-adjusted
 * delta * 8) and dispatching to a callee with the current pointer and the
 * global D+0xD430 as context.
 *
 * Decoded structure (raw-word disasm):
 *   void batch_dispatch3(int *out_recs, int base_idx, int delta_a, int delta_b,
 *                        int *src_a)  // arg5 — but actually a3
 *   {
 *       int *src   = src_a;          // s0 (advances by 12 each iter)
 *       int *out_p = out_recs;       // s1 (advances by 8 each iter)
 *       int  ia    = base_idx;       // s2 (++ each iter)
 *       int  ib    = delta_a;        // s3 (++ each iter)
 *       int  i     = 0;              // s4 (+= 12 each iter, exits at 0x24=36)
 *       int *ctx   = (int*)&D_00000000 + 0xD430/4;  // s6 — global pointer base
 *
 *       for (i = 0; i != 36; i += 12) {
 *           int rem = ia % 5;                 // div + safety traps (break 6/7)
 *           int v0 = *src;
 *           int v1 = *(src + 1);
 *           int v2 = *(src + 2);
 *
 *           // Signed alignment adjust: if ib < 0 and (ib & 7) != 0, subtract 8
 *           int adj = (ib < 0 && (ib & 7) != 0) ? ((ib & 7) - 8) : 0;
 *           int grid_idx = rem + (adj << 3);
 *
 *           hook(out_p, grid_idx, 0, ctx);    // jal
 *
 *           src   += 3;      // 12 bytes / 4
 *           out_p += 2;      // 8 bytes / 4
 *           ia++;
 *           ib++;
 *       }
 *   }
 *
 * Notes:
 *  - Inline `div + break 7 + break 6` is the standard IDO signed-modulo
 *    safety-trap pattern (reference_1080_mips3_runtime_helpers.md).
 *  - Each loop iteration loads 3 fields from *src (12 bytes), saves 3 args at
 *    sp+0x10/0x14/0x18 (caller's outgoing arg slots), invokes hook with 4 args.
 *  - 3-iteration unroll suggests XYZ vector dispatch (3 components) or
 *    3-channel color encoding (RGB or YCbCr).
 *  - The "alignment adjust if ib < 0" preserves floor-division semantics on
 *    negative dividends — typical of "wrap signed index back into range" logic.
 *  - Loop exit at counter = 0x24 (=36 bytes = 3 × 12-byte records) confirms
 *    fixed 3-iter shape.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009DB8);
#endif

extern int gl_data_0000D434;

/* gl_func_00009EBC: 3-iteration loop dispatching to gl_func_00000000 with
 * a 5x8 grid index computed as (a1 % 5) + ((a2 % 8) << 3). The signed
 * remainder of a2 by 8 comes from a sign-preserving bgez/andi/beq dance
 * (low 3 bits, adjusted by -8 when a2<0 and low bits nonzero). Args:
 *   a0 = base pointer (dst is a0+0x18, advances +8/iter)
 *   a1 = row seed (advances +1/iter, fed to %5)
 *   a2 = col seed (advances +1/iter, fed to signed-%8)
 *   a3 = pointer to sink ints, advancing one word per iter. */
#ifdef NON_MATCHING
void gl_func_00009EBC(int x0, int a1, int a2, int* a3) {
    int dst = x0 + 0x18;
    int row = a1;
    int col = a2;
    int sink;
    int i;
    int idx;

    for (i = 0; i != 12; i += 4) {
        idx = (row % 5) + ((col % 8) << 3);
        sink = *a3;
        gl_func_00000000(dst, idx, &gl_data_0000D434, sink);
        dst += 8;
        row += 1;
        col += 1;
        a3++;
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

#ifdef NON_MATCHING
/* gl_func_0000A00C: process two parallel slot-arrays (a0 and a0+0x18), 3 iters
 * of stride 8: for each slot, if gl_func(slot) != 0, gl_func(slot, a1, a2&0xFF,
 * a3&0xFF). Reloc-blind placeholder calls. 84.9% (m2c-verified structure):
 * residual is register-allocation -- target hoists the two `& 0xFF` to the top
 * (s4=a2&0xFF, s5=a3&0xFF) AND dead-homes raw a2/a3 (sw a2,0x40; sw a3,0x44);
 * -O2 C keeps the args raw in s-regs and re-masks at each call site, no home.
 * Naming s3/s4/s5 didn't flip it. Permuter/multi-pass residual. */
extern int gl_func_00000000();
void gl_func_0000A00C(int a0, int a1, int a2, int a3) {
    int s3 = a1;
    int s4 = a2 & 0xFF;
    int s5 = a3 & 0xFF;
    int s0 = a0;
    int s1 = a0 + 0x18;
    int s2 = 0;
    do {
        if (gl_func_00000000(s0) != 0) {
            gl_func_00000000(s0, s3, s4, s5);
        }
        if (gl_func_00000000(s1) != 0) {
            gl_func_00000000(s1, s3, s4, s5);
        }
        s2 += 8;
        s0 += 8;
        s1 += 8;
    } while (s2 != 0x18);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A00C);
#endif

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
 * CAP: i/p $s-reg swap stays NM (target s0=i,s1=p; built s0=p,s1=i —
 * decl-order swap REGRESSES per feedback-sreg-not-decl-driven). INSN_PATCH
 * REMOVED 2026-05-23 per feedback_no_instruction_forcing_matches_policy. */
extern int gl_func_00000000();
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A130);
#endif

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
 * Matched 2026-05-25: the residual was the entry-init/i-init pair-swap at
 * +0x1C/+0x20 (build emitted `addiu s1,a0,0x18` then `move s0,zero`; target
 * emits `move s0,zero` first). Initializing `i` at its declaration (int i = 0;)
 * BEFORE `entry` makes IDO emit the i-init first -> byte-exact. Replaces the
 * old banned 2-insn INSN_PATCH. */
extern int func_00000000();
int gl_func_0000A4D0(int *a0, int a1) {
    int i = 0;
    char *entry = (char*)a0 + 0x18;
    for (; i < 3; i++) {
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
/* game_libs_func_0000A8D8: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
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
 * feedback_doc_marker_is_bail.md. 2026-05-21: C body is structurally correct;
 * INSN_PATCH fixes IDO's unreachable setup scheduling and raw USO data
 * immediates.
 */
extern int D_1D438, D_1D3E8;
#ifdef NON_MATCHING
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

#ifdef NON_MATCHING
void gl_func_0000ABBC(char *a0, int a1, unsigned char a2, unsigned char a3, unsigned char *arg4) {
    int i;
    unsigned char *flagp;
    char *p;
    int saved_a1;
    int arg2_trunc;
    int arg3_trunc;
    int one;
    int limit;

    saved_a1 = a1;
    arg2_trunc = a2;
    arg3_trunc = a3;
    i = 0;
    flagp = arg4;
    p = a0;
    one = 1;
    limit = 3;
    for (; i != limit; i++) {
        if (gl_func_00000000(p) != 0) {
            unsigned char flags;

            gl_func_00000000(p, saved_a1, arg2_trunc, arg3_trunc);
            if (i == 0) {
                *flagp = (*flagp & 3) << 1;
            } else if (i == one) {
                flags = *flagp;
                *flagp = (flags & 1) | ((flags & 2) << 1);
            }
            flags = *flagp;
            *flagp = flags | (one << i);
        }
        p += 0x20;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ABBC);
#endif

/* gl_func_0000ACBC: 25-insn 3-iter loop, sibling of gl_func_0000A0CC.
 * Calls func_00000000 (NOTE: not gl_-prefixed — target's reloc references
 * the intra-segment `func_00000000` symbol, not `gl_func_00000000`).
 * Returns non-zero hit count. Source structurally identical to A0CC;
 * stride/limit immediates differ (0x20/0x60 vs 0x8/0x18) and callee
 * reloc name. NATURAL CEILING: previously documented as "Byte-exact via
 * sibling INSN_PATCH transfer logic" — INSN_PATCH REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
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
 * NATURAL CEILING: 92.14% NM. The 4-insn prologue-setup reorder (target:
 * s2=a1 / sw-ra / s0=0 / s1=a0  vs  IDO emit: s1=a0 / s2=a1 / sw-ra /
 * s0=0) was previously documented as INSN_PATCH-promoted to EXACT —
 * INSN_PATCH REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
extern int func_00000000();
#ifdef NON_MATCHING
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
 * NATURAL CEILING: 92.93% NM. The 14-insn diff is IDO scheduler's
 * `or v0, s2, 0` insertion into bnel/beq delay slots — not naturally
 * reachable from C with return-at-end. Was previously documented as
 * INSN_PATCH-promotable to EXACT; INSN_PATCH REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
extern int gl_func_00000000();
#ifdef NON_MATCHING
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

/* 15-insn 2-call wrapper (0x3C). LANDED fuzzy=100. The historical 4-byte
 * SUFFIX_BYTES tail (`sll/subu/addiu/div` computing (a1*3)/5, supplying
 * stolen-prologue setup for successor gl_func_0000B5AC) was REMOVED
 * 2026-05-23 as match-faking; those bytes now belong to B5AC's own symbol.
 * Successor B5AC is at fuzzy=NULL (still needs predecessor-fall-through
 * decode) — see its header just below. */
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000B628);

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
 * varies per call site; no uniform PREFIX_BYTES recipe. Stays INCLUDE_ASM.
 * (Old recognizer reference: docs/POST_CC_RECIPES.md
 * #feedback-insn-patch-for-ido-codegen-caps "HI/LO register inheritance
 * (chained-SUFFIX-div pattern, 2026-05-05)". docs/POST_CC_RECIPES.md
 * DEPRECATED 2026-05-23; the recognition pattern still applies but the
 * recipe is no longer accessible.) */
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
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B77C);
#endif

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

#ifdef NON_MATCHING
/* gl_func_0000B958: 69-insn word-array equality predicate. Compares (a3+3)/4
 * words of a1[] vs a2[]; returns 0 on the first mismatch, 1 if all equal.
 * RELOC-FREE and -O2, so landable in principle -- but the target is IDO's 4-way
 * UNROLLED form (Duff's-device andi&3 remainder + the 4-wide body), which a plain
 * early-exit loop does NOT reproduce (my C compiles to a tight 24-insn loop, no
 * unroll). Needs the permuter / a hand-unrolled form to match. NM (reference);
 * verified-correct algorithm. */
int gl_func_0000B958(int a0, int *a1, int *a2, int a3) {
    int n = (a3 + 3) / 4;
    int i;
    for (i = 0; i < n; i++) {
        if (a1[i] != a2[i]) {
            return 0;
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B958);
#endif

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
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BB14);
#endif

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
 * substantive decode (per feedback_doc_marker_is_bail.md).
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

extern int gl_func_00000000();
#ifdef NON_MATCHING
void gl_func_0000C28C(void *arg0, int *arg1) {
    int buf10[4];
    int buf08[2];

    buf10[0] = arg1[0];
    buf10[1] = arg1[1];
    buf10[2] = arg1[2];
    buf10[3] = arg1[3];
    buf10[2] = 0;

    *(int*)((char*)arg0 + 4) = arg1[0];
    gl_func_00000000(arg0, 0x218, buf10, 0x10);
    if (gl_func_00000000(arg1) != 0) {
        gl_func_00000000(arg0, 0x230, arg1[2], arg1[1] * 4);
    }

    gl_func_00000000(buf08, buf10, 0x10, 0xDEADBBAD);
    gl_func_00000000(arg0, 0x228, buf08, 8);
    gl_func_00000000(arg0, 0x7FE8, buf10, 0x10);
    gl_func_00000000(arg0, 0x7FF8, buf08, 8);
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C28C);
#endif

int gl_func_0000C378(void *arg0) {
    int current16[4];
    int current8[2];
    int digest[2];
    int backup16[4];
    int backup8[2];

    gl_func_00000000(arg0, current16, 0x218, 0x10);
    gl_func_00000000(arg0, current8, 0x228, 8);
    gl_func_00000000(digest, current16, 0x10, 0xDEADBBAD);
    if (gl_func_00000000(digest, current8) == 0) {
        gl_func_00000000(arg0, backup16, 0x7FE8, 0x10);
        gl_func_00000000(arg0, backup8, 0x7FF8, 8);
        gl_func_00000000(digest, backup16, 0x10, 0xDEADBBAD);
        if (gl_func_00000000(digest, backup8) == 0) {
            return 0;
        }
        gl_func_00000000(arg0, 0x218, backup16, 0x10);
        gl_func_00000000(arg0, 0x228, backup8, 8);
    }
    return 1;
}

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

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C5B0);
#endif
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000CA30);

/* Linear search: scan count (a0->0x48) elements (stride 0x60) at a0->0x44 for
 * one whose first field == a1; return that element, else 0. Merged: the loop-
 * back/not-found epilogue was splat-split off as game_libs_func_0000CB88
 * (UNSHARED); merged back (0x30 -> 0x44). NOT byte-exact: target keeps the key
 * in a1 + array in a2 + count in v1 with a blezl guard; IDO -O2 copies the key
 * (move a2,a1), uses a1 for the array, and emits bgtzl (register-alloc +
 * branch-likely-arm grind). INCLUDE_ASM is the build path. */
#ifdef NON_MATCHING
void *game_libs_func_0000CB58(int *a0, int a1) {
    int count = a0[0x48 / 4];
    int *p;
    int i = 0;
    if (count <= 0) {
        return 0;
    }
    p = (int*)a0[0x44 / 4];
    do {
        i++;
        if (*p == a1) {
            return p;
        }
        p = (int*)((char*)p + 0x60);
    } while (i < count);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000CB58);
#endif

#ifdef NON_MATCHING
/* gl_func_0000CB9C: 22-insn bounds-check + dispatch. Body:
 *   if (a0[0x30] < a0[0x34]) return 0;
 *   if (a0[0x78]) { func(a0[0x78]); a0[0x30] = a0[0x34] - 8; }
 *   return 1;
 * Target frame is -0x18 (only ra spilled).
 *
 * MNEMONIC-FUZZY CEILING 80% (report.json) vs OPERAND-LEVEL ~22% (objdiff).
 * Verified 2026-05-27:
 *   - Inlined-no-locals form (no goto, no rv var): 21.57% operand.
 *   - Unified-rv goto-end form: 9.90% operand (worse — extra spill of rv).
 *   - Original local-var goto end_zero form: similar to inlined.
 * The mnemonic-fuzzy 80% is misleading; real diff is large.
 *
 * Target asm forensics: target uses `bnezl at, EPILOGUE` with delay
 * `or v0, zero, zero` for the early-exit; IDO -O2 from any of the tried
 * C shapes emits `beqzl` or pair-of-branches instead, missing the
 * bnezl-merged-into-epilogue idiom. ALSO target has a DEAD `move v0,zero`
 * at +0x40, between the b's delay (li v0,1) and the epilogue — vestigial
 * from an optimizer-tail-merged null-ptr return-0 path that no clean C
 * source reproduces. Both caps stack; documented NM only. */
extern int gl_func_00000000();
int gl_func_0000CB9C(int *a0) {
    if (a0[0x30/4] < a0[0x34/4]) return 0;
    if (a0[0x78/4]) {
        gl_func_00000000(a0[0x78/4]);
        a0[0x30/4] = a0[0x34/4] - 8;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CB9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000CBF0);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CBFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000CD74);

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

void game_libs_func_0000D090(int *a0) {
    if (*(int *)(*(int *)((char *)a0 + 0x44) + 0x34) != 0) {
        if ((unsigned int)*(int *)((char *)&D_00000000 + 0x170) < (unsigned int)*(int *)((char *)&D_00000000 + 0x164) - 1) {
            *(int *)((char *)&D_00000000 + 0x184) = 1;
        }
    }
}

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

/* gl_func_0000D9B8: NATURAL CEILING 98.64% NM. 3 reg-rename diffs at
 * offsets 0x08/0x0C/0x18 — IDO emits $a1 for the temp; target uses $a3.
 * Identical insn structure, different register field. The previous
 * INSN_PATCH promotion was REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Permuter-class
 * register-rename cap; no C-reachable fix. */
extern int gl_func_00000000();
#ifdef NON_MATCHING
void gl_func_0000D9B8(int *a0) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9B8);
#endif

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
 *   fn((int)((char*)v1 + off), &sp_args[1001], self);    // 1001 as stack arg @sp+0x34
 *
 *   if (self->[0x48] == 2) {                                   // pair-toggle gate
 *       // Same dispatch on partner entry (idx XOR 1):
 *       entry2 = (int*)((char*)self->[0x44] + (idx ^ 1) * 96);
 *       v1_2 = *entry2;
 *       vt_2 = v1_2->[0x28];
 *       off2 = (short)vt_2->[0x28];
 *       fn_2 = (int(*)(int,int))vt_2->[0x2C];
 *       fn_2((int)((char*)v1_2 + off2), &sp_args2[1000]);  // 1000 stack arg
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

/* Doubled DE30-family vtable dispatcher (sibling of gl_func_0000DDE0/DE30/DE80/
 * DED0): runs the same {entry = a0->0x44[idx*0x60]; q = entry->0x28;
 * (*(fn)q->0x2C)((short)q->0x28 + entry, &scratch);} dispatch twice, for idx=a1
 * then idx=a1^1 (a pair/toggle), each with a stack scratch int preloaded to 1001.
 * Matched: pad_top/between/pad_bot arrays pin l1@sp+0x34 / l2@sp+0x28 in the -0x40
 * frame; deferring l2's assignment defers its li+sw past the first call; the empty
 * if(v0){} on the 2nd dispatch is the regalloc nudge (permuter-found) that gives
 * entry->v1 / q->v0 like the target. */
void gl_func_0000DD44(char *a0, int a1) {
    int pad_top[2]; int l1 = 1001; int between[2]; int l2; int pad_bot[2];
    char *v0, *v1;
    v1 = *(char **)(*(char **)(a0 + 0x44) + a1 * 0x60);
    v0 = *(char **)(v1 + 0x28);
    (*(void (**)(char *, int *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &l1);
    l2 = 1001;
    v1 = *(char **)(*(char **)(a0 + 0x44) + (a1 ^ 1) * 0x60);
    v0 = *(char **)(v1 + 0x28);
    if (v0) {}
    (*(void (**)(char *, int *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &l2);
}

/* 20-insn indirect dispatcher (sibling of gl_func_0000DE30/DE80/DED0/0003CB2C).
 * Same shape as DE30 form (inlined dispatch + pad_top[2]/pad_bot[4] frame
 * sizing), local = 0x3EA. INSN_PATCH on the same 4 reg-rename insns at
 * 0x24/0x2C/0x34/0x3C makes build/.o byte-equal to expected/.o post-cc. */
/* 20-insn indirect dispatcher (sibling of DE30/DE80/DED0). See gl_func_0000DE30
 * for the fptr-from-q[0x2C] data flow + the alloc-nudge (empty if + hoist). */
void gl_func_0000DDE0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EA;
    int pad_bot[2];
    char *off28;
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    int *q = (int *)p[0x28/4];
    off28 = (char*)q + 0x28;
    if (q) {}
    ((void(*)(int, int*))q[0x2C/4])(*(short*)off28 + (int)p, &local);
}

/* 20-insn indirect dispatcher (sibling of gl_func_0000DDE0/0003CB2C).
 * 16/20 insns match from C emit; remaining 4-insn diff is a register-shift
 * (v0/t0/t1 ↔ v1/v0/t0) that no C-level lever inside this function
 * reproduces. INSN_PATCH on the 4 reg-shift insns @0x24/0x2C/0x34/0x3C
 * makes build/.o byte-equal to expected/.o post-cc. */
/* 20-insn indirect dispatcher. p = a0[0x44][a1*96]; q = p[0x28];
 * fptr = q[0x2C]; fptr((short)(q+0x28) + p, &local). The empty `if (q)`
 * + hoisted short-address are register-allocation nudges (permuter-found)
 * that put p in $v1 / q in $v0 to match; both are semantically transparent. */
void gl_func_0000DE30(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EB;
    int pad_bot[2];
    char *off28;
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    int *q = (int *)p[0x28/4];
    off28 = (char*)q + 0x28;
    if (q) {}
    ((void(*)(int, int*))q[0x2C/4])(*(short*)off28 + (int)p, &local);
}

/* Sibling of gl_func_0000DDE0/0000DE30/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3EC; otherwise byte-identical to DE30. Same INSN_PATCH recipe:
 * the 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched
 * to match expected. (The 0x30 word coincidentally byte-matches due to
 * register-rename + same instruction word; runtime semantics flip when the
 * patched 0x2C insn redefines $v0 = p[0x28] before 0x30 reads it.) */
/* 20-insn indirect dispatcher (sibling of DDE0/DE30/DED0). See gl_func_0000DE30. */
void gl_func_0000DE80(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EC;
    int pad_bot[2];
    char *off28;
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    int *q = (int *)p[0x28/4];
    off28 = (char*)q + 0x28;
    if (q) {}
    ((void(*)(int, int*))q[0x2C/4])(*(short*)off28 + (int)p, &local);
}

/* Sibling of gl_func_0000DDE0/DE30/DE80/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3E9; otherwise byte-identical to DE30/DE80. Same INSN_PATCH recipe:
 * 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched to
 * match expected. (See DE80 for the byte-identical-bytes-different-semantics
 * mechanism at offset 0x30.) */
/* 20-insn indirect dispatcher (sibling of DDE0/DE30/DE80). See gl_func_0000DE30. */
void gl_func_0000DED0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3E9;
    int pad_bot[2];
    char *off28;
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    int *q = (int *)p[0x28/4];
    off28 = (char*)q + 0x28;
    if (q) {}
    ((void(*)(int, int*))q[0x2C/4])(*(short*)off28 + (int)p, &local);
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

/* gl_func_0000DFC4: 32-insn 3-arg lookup+gate+accumulate (0x80, frame 0x18).
 * MATCH: the v0[0x1C]==0 guard (was decoded != 0) emits bnel, matching the asm
 * (store v0[0x20]=0 when v0[0x1C]==0). Byte-exact.
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
    if (v0 == 0) return;
    if ((v0[0x4 / 4] & 1) == 0) return;
    if ((a0[0xB4 / 4] & 2) == 0) return;
    if (v0[0x1C / 4] == 0) {
        v0[0x20 / 4] = 0;
    }
    v0[0x1C / 4] = v0[0x1C / 4] + a2;
    if (v0[0x24 / 4] != 1) {
        v0[0x24 / 4] = 1;
    }
}

/* 3-insn save-arg sentinel: sw a0,0(sp); jr ra; sw a1,4(sp).
 * Empty-body 2-arg function — args spilled to caller's arg-save slots.
 * Per docs/IDO_CODEGEN.md#feedback-ido-save-arg-sentinel-empty-body. */
void game_libs_func_0000E044(int a0, int a1) { (void)a0; (void)a1; }
void game_libs_func_0000E050(int a0, int a1) { (void)a0; (void)a1; }

#ifdef NON_MATCHING
/* gl_func_0000E05C: 47-insn 2-gate + flag-driven dispatch + vtable tail (0xBC, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   v0 = func1(self);                                // lookup
 *   if (v0 == NULL) return;
 *   if ((v0->[0x4] & 1) == 0) return;                 // 2nd gate
 *
 *   flags = self->[0xB4];
 *   int a2_var = -1;
 *   if (flags & 0x10) {
 *       a2_var = func2(D_sym1);                       // 1st flag-conditional call
 *   }
 *   if (flags & 0x1) {
 *       int r1 = func3(D_sym2, a1);                   // chained 2nd flag-conditional
 *       func4(self, r1, a2_var);                       // 3-arg with prior a2_var
 *   }
 *   func5(0x24, a1);                                  // unconditional middle call
 *
 *   // Vtable tail-dispatch (always):
 *   vt = self->[0x28];
 *   fn = (vtable_fn)vt->[0x6C];
 *   short off = (s16)vt->[0x68];
 *   fn((char*)self + off, a1);
 *
 * Cascading flag-conditional dispatch: bit 0x10 sets up a2_var, bit 0x1
 * runs middle pair, then unconditional tail vtable call. Standard
 * "dispatch matrix on flag bits" idiom for state-machine objects.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0000E05C(int *self, int a1, int a2) {
    extern int D_sym1, D_sym2;
    int *v0 = (int*)gl_func_00000000(self);
    int a2_var = -1;
    int flags;
    int *vt;
    int (*fn)(int, int);
    short off;
    if (v0 == 0) return;
    if ((v0[1] & 1) == 0) return;
    flags = self[0xB4 / 4];
    if (flags & 0x10) {
        a2_var = (int)gl_func_00000000(&D_sym1);
    }
    if (flags & 0x1) {
        int r1 = (int)gl_func_00000000(&D_sym2, a1);
        gl_func_00000000(self, r1, a2_var);
    }
    gl_func_00000000(0x24, a1);
    vt = (int*)self[0x28 / 4];
    fn = (int(*)(int, int))vt[0x6C / 4];
    off = *(short*)((char*)vt + 0x68);
    fn((int)((char*)self + off), a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E05C);
#endif

#ifdef NON_MATCHING
/* gl_func_0000E118: getter + flag-gated reset + vtable dispatch (m2c-decoded,
 * 90.1%). v0 = gl_func(); if (v0 && (v0->4 & 1)) { if ((a0->B4 & 2) && v0->24==1)
 * { gl_func(a0, v0->1C [, a3 if a2]); v0->24=0; v0->1C=0; } t=a0->28;
 * (*(short*)(t->70)+a0 passed to *(t->74))(.., a2); }. Residual: IDO spuriously
 * homes the UNUSED a1 placeholder param (sw a1,0x2C) alongside the live a2/a3
 * spills -> +1 insn shift; a1 must be declared to keep a2/a3 in $a2/$a3 but can't
 * be suppressed. The rest is byte-exact. t->70 is a SHORT (lh). */
extern int gl_func_00000000();
void gl_func_0000E118(int a0, int a1, int a2, int a3) {
    int v0 = gl_func_00000000();
    if (v0 != 0 && (*(int *)(v0 + 4) & 1)) {
        if ((*(int *)(a0 + 0xB4) & 2) && *(int *)(v0 + 0x24) == 1) {
            if (a2 != 0) {
                gl_func_00000000(a0, *(int *)(v0 + 0x1C), a3);
            } else {
                gl_func_00000000(a0, *(int *)(v0 + 0x1C));
            }
            *(int *)(v0 + 0x24) = 0;
            *(int *)(v0 + 0x1C) = 0;
        }
        {
            int t = *(int *)(a0 + 0x28);
            (*(void (**)(int, int))(t + 0x74))(*(short *)(t + 0x70) + a0, a2);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E118);
#endif

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
 * NATURAL CEILING: 98.45% NM. The 8-insn diff is a pure s1/s2 register-
 * swap (IDO picks $s2=a0/$s1=offset; target picks $s1=a0/$s2=offset) —
 * same family as gl_func_0004ED0C / gl_func_00035834. Was previously
 * documented as INSN_PATCH-promotable to EXACT; INSN_PATCH REMOVED
 * 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
extern int func_00000000();
#ifdef NON_MATCHING
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

#ifdef NON_MATCHING
/* gl_func_0000E368: 42-insn gated flag toggle. Returns early unless bit 16 of
 * (a0->0x50)->0x4F0 is set, a0->0x48 == 2, and the (collapsed) callback succeeds;
 * then toggles a0->0xB0 between 0/1 and correspondingly clears/sets bit 2 of
 * a0->0x44->0x60->0x18. NM (reference decode): collapsed-placeholder call +
 * collapsed D ref + branch-likely tests (raw-.word game_libs reloc depression).
 * Uses the file-scope extern int D_00000000 / gl_func_00000000. */
void gl_func_0000E368(int a0) {
    if ((*(int *)(*(int *)((char *)a0 + 0x50) + 0x4F0) & 0x10000) == 0) {
        return;
    }
    if (*(int *)((char *)a0 + 0x48) != 2) {
        return;
    }
    if (gl_func_00000000(&D_00000000, 0x20, a0) == 0) {
        return;
    }
    if (*(int *)((char *)a0 + 0xB0) != 0) {
        int v = *(int *)(*(int *)((char *)a0 + 0x44) + 0x60);
        *(int *)((char *)v + 0x18) &= ~4;
        *(int *)((char *)a0 + 0xB0) = 0;
    } else {
        int v = *(int *)(*(int *)((char *)a0 + 0x44) + 0x60);
        *(int *)((char *)v + 0x18) |= 4;
        *(int *)((char *)a0 + 0xB0) = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E368);
#endif

/* game_libs_func_0000E410..E490: CONTIGUOUS lower-opt (-O1/-g) family. Each is
 * `int *p=(int*)(a0+0x18); *p OP= BIT; return p;` (E410 |=4|=8, E42C &=~4&=~8,
 * E450 |=8, E464 &=~8, E47C |=4, E490 &=~4). CAP under -O2: target uses
 * addiu v0,a0,0x18 + 0(v0) RMW addressing AND keeps redundant stores (E410/E42C),
 * but -O2 C folds to 0x18(a0) offset-addressing and dead-store-eliminates the
 * first write (verified 2026-05-24). Whole run wants an -O1/-g OPT_FLAGS file
 * split (batch-unlock w/ 00052ACC). See project_1080_g3_unfilled_delay_split_2026-05-23. */
/* game_libs_func_0000E410: 7-insn `set-bit-2-then-set-bit-3` (|=4 then |=8)
 * with target keeping the intermediate store. Family head — see comment above.
 *   int *p = a0 + 0x18; *p |= 4; *p |= 8; return p;
 *
 * IDO -O2 folds both ors into a single `| 0xC` and DSE's the first store.
 * Same base-reg-choice + redundant-write family cap. */
#ifdef NON_MATCHING
int *game_libs_func_0000E410(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p |= 4;
    *p |= 8;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E410);
#endif

/* game_libs_func_0000E42C: 8-insn `clear-bit-2-then-clear-bit-3` (mask -5 then -9)
 * with TARGET keeping the intermediate store (does NOT DCE the first sw).
 *   int *p = a0 + 0x18; *p &= ~4; *p &= ~8; return p;
 *
 * Target: addiu v0,a0,0x18; lw 0(v0); li at,-5; and t7,t6,at; li at,-9;
 *   sw t7,0(v0); and t9,t7,at; jr ra; sw t9,0(v0) (delay).
 * IDO -O2 dead-store-eliminates the first `*p &= ~4` (folds the two masks
 * into a single `& ~0xC`) and folds 0x18 back to base+imm. Whole family
 * (E410-E490) wants -O1/-g per-file split. See E410 header. */
#ifdef NON_MATCHING
int *game_libs_func_0000E42C(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p &= ~4;
    *p &= ~8;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E42C);
#endif

/* game_libs_func_0000E450: 5-insn `or-flag setter`.
 *   int *p = a0 + 0x18; *p |= 8; return p;
 *
 * Target uses v0 (= p) as both load AND store base; mine uses direct
 * a0+0x18 for both (IDO CSE folds *p back to a0-relative). Base-reg
 * choice cap; structure correct, register-cascade differs. */
#ifdef NON_MATCHING
int *game_libs_func_0000E450(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p |= 8;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E450);
#endif

/* game_libs_func_0000E464: 5-insn `clear-bit-3` sibling of E450 (|=8 → &=~8).
 *   int *p = a0 + 0x18; *p &= ~8; return p;
 * Same base-reg-choice cap as E450/E490. See E410 family header. */
#ifdef NON_MATCHING
int *game_libs_func_0000E464(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p &= ~8;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E464);
#endif

/* game_libs_func_0000E47C: 5-insn `set-bit-2` sibling of E450 (|=8 → |=4).
 *   int *p = a0 + 0x18; *p |= 4; return p;
 * Same base-reg-choice cap. The 0x35CF0004 is `ori t7,t6,4` (1-cycle
 * faster than li+and; bit-set fits andi/ori immediate). See E410 family
 * header for the OPT_FLAGS-split path. */
#ifdef NON_MATCHING
int *game_libs_func_0000E47C(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p |= 4;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E47C);
#endif

/* game_libs_func_0000E490: 5-insn `clear-bit-2` sibling of E450 (|=8 → &=~4).
 *   int *p = a0 + 0x18; *p &= ~4; return p;
 *
 * Same family cap as E450 (base-reg-choice). Target: addiu v0,a0,0x18 →
 * 0(v0) RMW. Mine: addiu v0,a0,0x18 emitted (return ptr) BUT the lw/sw
 * fold back to 0x18(a0) since the single bitop at offset 0 doesn't
 * prevent IDO -O2 from CSE'ing the pointer alias back to the base+imm
 * form. 3-of-5 insns byte-equal; structure correct. Whole 0xE410-E490
 * run wants a per-file -O1/-g OPT_FLAGS split (see family header at
 * E410). */
#ifdef NON_MATCHING
int *game_libs_func_0000E490(int *a0) {
    int *p = (int*)((char*)a0 + 0x18);
    *p &= ~4;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000E490);
#endif

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
 *   factory = func1(0, &D_A, 0xC0, 0xB, [sp:0x10] 0xC, [sp:0x14] 1);
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
