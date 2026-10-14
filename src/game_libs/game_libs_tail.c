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
gl_func_0000959C(a0) int *a0; {
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

/* game_libs_func_000097B4: checksum-pair writer. Sum the len/4 words at src;
 * out[0]=0xF251F205-sum; out[1]=key-(out[0]-sum). BYTE-EXACT 2026-07-23:
 * the three levers were (1) `q = src; src++; ... sum += *q;` old-pointer-copy
 * body (reproduces the per-load `or a0,a1` and frees a0, which homes `out` to
 * 0(sp) with per-store reloads — no address-taken barrier needed); (2) NO named
 * n — inline `len / 4` in guard + do-while condition CSEs to a SINGLE web
 * (named n split into def+loop webs = extra `or t0,t1` that blocked the lui
 * 0xf251 hoist into the blez delay slot); (3) destructive tail
 * `sum = chk - sum` (reuses v0) instead of a fresh temp. IDO auto-unrolls x4
 * with the (n&3) remainder pre-loop. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
void game_libs_func_000097B4(s32 *out, s32 *src, s32 len, s32 key) {
    s32 sum = 0;
    s32 i = 0;
    s32 *q;
    s32 chk;

    if (len / 4 > 0) {
        do {
            q = src;
            src++;
            i++;
            sum += *q;
        } while (i != len / 4);
    }
    chk = 0xF251F205 - sum;
    out[0] = chk;
    sum = chk - sum;
    out[1] = key - sum;
}

/* game_libs_func_0000986C: checksum-pair VERIFIER, sibling of the writer
 * 97B4 above (same auto-unrolled x4 sum loop, byte-identical bar the blez
 * delay slot: `lw t2,0(sp)` reload of the homed `out` vs the writer's lui).
 * Checks out[0] + sum == 0xF251F205 and out[1] + (out[0] - sum) == key.
 * BYTE-EXACT 2026-09-05 (agent-g) as ONE 54-word function [0x986C,0x9944):
 * the former symbols 9920 (7w: the second check) and 993C (2w `jr ra; nop`,
 * "matched" as `void f(void){}` with an episode) were this function's own
 * blocks, mis-split at each internal `jr ra` -- 986C's `beq t3,at,+3` lands
 * ON 9920 and 9920's `beq a3,t6,+3` (preset `li v0,1` in the delay slot)
 * lands ON 993C = the return-1 exit block.  The old "leaf-branch-past-end
 * cross-fn epilogue CAP" comment covering 9920 was this mis-split.  Keys:
 * inverted guards (`!= -> return 0`) give the beq-forward + inline return-0
 * layout; named `chk = out[0]` + destructive `sum = chk - sum` (as in 97B4)
 * reuse v1/v0; and the last addu's operand order (`addu t6,v0,t5`, sum first)
 * needs the assignment-expr pin `out[1] + (chk = sum)` -- plain `sum + out[1]`
 * / `out[1] + sum` both emit the load as rs (docs/IDO_CODEGEN.md
 * #feedback-ido-fp-commutative-operand-order-assignment-lever, integer form).
 * See docs/MATCHING_WORKFLOW.md #o0-predicate-misplit-merge-recipe and
 * #feedback-beql-next-symbol-plus-4-is-mis-split-branch-likely-block. */
int game_libs_func_0000986C(s32 *out, s32 *src, s32 len, s32 key) {
    s32 sum = 0;
    s32 i = 0;
    s32 *q;
    s32 chk;

    if (len / 4 > 0) {
        do {
            q = src;
            src++;
            i++;
            sum += *q;
        } while (i != len / 4);
    }
    chk = out[0];
    if (sum + chk != 0xF251F205) {
        return 0;
    }
    sum = chk - sum;
    if (key != out[1] + (chk = sum)) {
        return 0;
    }
    return 1;
}

/* game_libs_func_00009944: 2-word equality compare -- 1 iff a0[0]==a1[0]
 * and a0[1]==a1[1].  BYTE-EXACT 2026-09-05 (agent-g) as ONE 13-word
 * function [0x9944,0x9978): the former "matched" 2-word stub 9970
 * (`jr ra; nop`, `void f(void){}` with an episode) was this function's own
 * return-1 exit block -- the `beq t8,t9,+3` (preset `li v0,1` in front of it)
 * lands ON it.  Plain -O2: filled `jr` delay, preset return value; the two
 * branch-delay nops just follow immediately-dependent loads.  Key: the
 * target has ONE shared `jr ra; move v0,zero` block (the first `bne` lands
 * on it), so both return-0s must be a single `||` guard; two separate
 * `if (!=) return 0;` statements give a beql + inline return-0 (15w), and
 * the `&&`-return-1 spelling flips the last branch to bne (13w, 3 diffs).
 * See docs/MATCHING_WORKFLOW.md
 * #feedback-beql-next-symbol-plus-4-is-mis-split-branch-likely-block. */
int game_libs_func_00009944(s32 *a0, s32 *a1) {
    if (a0[0] != a1[0] || a0[1] != a1[1]) {
        return 0;
    }
    return 1;
}

void game_libs_func_00009978(unsigned char *arg0) {
    *arg0 &= 0x7F;
}

/* 4-arg string-builder: a0[2..4] = a1[0..2] (3-byte copy); then pack a flag
 * byte a0[0] = (a0[0] & 0xFF80) | a2 | (a3 << 3). EXACT 21/21 (2026-07-08):
 * the old "modified-param home-spill cap" dissolved via the 9C04 lever —
 * unsigned char params emit BOTH the sw a2,8(sp)/sw a3,0xC(sp) arg homes AND
 * the eager andi 0xFF zero-extends; comma-init for-loop pre-header + trailing
 * if(n==3)break (99DC/9B60/9C04 recipe) gives li a1,3 + sb-in-delay. */
void game_libs_func_00009988(char *a0, char *a1, unsigned char a2, unsigned char a3) {
    int n;
    char *d, *s;
    for (n = 0, d = a0, s = a1; ;) {
        n++;
        d++;
        d[1] = *s;
        s++;
        if (n == 3) {
            break;
        }
    }
    a0[0] = ((unsigned char)a0[0] & 0xFF80) | a2 | (a3 << 3);
}

/* 7-arg string-builder: a0[0]=a1; a0[1]=a2; 3x copy (a3[i]-0x61)->a0[2..4];
 * a0[5..7]=stack args. MATCHED (byte-exact). The prior "loop-bound const
 * scheduling tie" was MISDIAGNOSED: the fix is to place the n/d/s inits in
 * the for-init clause AFTER the two byte stores, with the loop exit as a
 * trailing `if (n == 3) break;`. That ordering makes GCC materialize the
 * bound `li a1,3` immediately after the stores (before the setup moves),
 * exactly as the target schedules it. */
void game_libs_func_000099DC(char *a0, int a1, int a2, char *a3, int a4, int a5, int a6) {
    int n;
    char *d;
    char *s;
    a0[0] = a1;
    a0[1] = a2;
    for (n = 0, d = a0, s = a3; ;) {
        n++;
        d++;
        d[1] = *s - 0x61;
        s++;
        if (n == 3) {
            break;
        }
    }
    a0[5] = a4;
    a0[6] = a5;
    a0[7] = a6;
}

/* game_libs_func_00009A2C: flag-test accessor. splat's jr-ra heuristic split
 * the return-0 tail (jr ra; nop) into 00009A48 — which coincidentally matched
 * as an empty `void f(void){}` stub. Merged it is one function: the `beqz`
 * return-0 path targets that tail. The `if(...)return 1; return 0;` form keeps
 * the early `move v0,zero` default + `li v0,1` in the taken jr-ra delay. */
int game_libs_func_00009A2C(unsigned char *a0) {
    if (*a0 & 0x80) {
        return 1;
    }
    return 0;
}

/* game_libs_func_00009A50 (34 insns, 0x88): strict date-triple compare,
 * returns 1 if the record's stored triple a0[5..7] is greater than the triple
 * a1[0..2] (field-by-field, most significant first), else 0. Inverse-setter is
 * 9AD8 (a0[5]=a1, a0[6]=a2, a0[7]=a3).
 * BOUNDARY MERGE 2026-09-05: the former 9A6C/9A80/9A9C/9AB0 "leaf-branch-past-
 * end CAP" symbols and the 9AD0 "empty function" were never functions. Each
 * 5-word block begins with a byte-identical copy of the preceding beql's delay
 * slot and the beql targets block+4 -- IDO's branch-likely dup-first-insn idiom
 * (docs/MATCHING_WORKFLOW.md #feedback-beql-next-symbol-plus-4-is-mis-split-
 * branch-likely-block). generate-uso-asm cut at each early `jr ra`. 9AD0
 * (jr ra; nop) is this function's own `return 1` block reached by the final
 * `bnez`. Nothing else references any of the five. Merged the .s (0x1C+0x14+
 * 0x1C+0x14+0x20+0x8) and put the real C on the build path.
 * Match key: the LAST test must be written `if (a1[2] >= a0[7]) return 0;
 * return 1;` -- IDO hoists `li v0,1` above the `bnez at` and branches to the
 * trailing `jr ra; nop`. `if (a1[2] < a0[7]) return 1; return 0;` puts the
 * `li v0,1` in a taken-branch delay slot instead (3 words differ). */
int game_libs_func_00009A50(unsigned char *a0, unsigned char *a1) {
    if (a0[5] < a1[0]) return 0;
    if (a1[0] < a0[5]) return 1;
    if (a0[6] < a1[1]) return 0;
    if (a1[1] < a0[6]) return 1;
    if (a1[2] >= a0[7]) return 0;
    return 1;
}

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

/* Sibling of 00009988 (copy to a0[1..3] via d[0]; same flag-pack a0[0]).
 * EXACT 21/21 (2026-07-08) via the same uchar-param + comma-init-for-loop
 * lever (see 00009988 / 00009C04). */
void game_libs_func_00009B0C(char *a0, char *a1, unsigned char a2, unsigned char a3) {
    int n;
    char *d, *s;
    for (n = 0, d = a0, s = a1; ;) {
        n++;
        d++;
        d[0] = *s;
        s++;
        if (n == 3) {
            break;
        }
    }
    a0[0] = ((unsigned char)a0[0] & 0xFF80) | a2 | (a3 << 3);
}

/* 3-byte transform copy (a2[i]-0x61 -> a0[1..3]) + a0[0]=a1 + a0[4]=a3.
 * Byte-exact via comma-init for-loop AFTER the leading store + trailing
 * `if (n==3) break;` exit: materializes `li a1,3` right after `sb a1,0(a0)`
 * (target schedule) AND keeps the loop-bottom order (store before branch,
 * `s++` in the delay slot). See docs/IDO_CODEGEN.md "for-loop comma-init
 * flips the loop-pre-header schedule" (sibling game_libs_func_000099DC). */
void game_libs_func_00009B60(char *a0, int a1, char *a2, int a3) {
    int n;
    char *d, *s;
    a0[0] = a1;
    for (n = 0, d = a0, s = a2; ;) {
        n++;
        d++;
        *d = *s - 0x61;
        s++;
        if (n == 3) {
            break;
        }
    }
    *(int *)(a0 + 4) = a3;
}

/* Flag/compare-test accessor family (sibling of 00009A2C): splat split each
 * return-0 tail into the following empty-stub symbol; merged each is one fn. */
int game_libs_func_00009B98(unsigned char *a0) {
    if (*a0 & 0x80) {
        return 1;
    }
    return 0;
}

int game_libs_func_00009BBC(int *a0, int a1) {
    if (a0[1] < a1) {
        return 1;
    }
    return 0;
}

void game_libs_func_00009BE0(char *a0, int a1) { *(int*)(a0 + 4) = a1; *(unsigned char*)a0 |= 0x80; }

void game_libs_func_00009BF4(int *a0) { *(int*)((char*)a0 + 0x0) &= 0x7F; }

/* Word-variant sibling of 00009988: copy to a0[5..7] via d[4]; word flag-pack
 * *(int*)a0 = (*(int*)a0 & ~0x7F) | a2 | (a3<<3) (lw/sw, mask via li -0x80).
 * EXACT 22/22 (2026-07-08): the "modified-param home-spill cap" was the
 * unsigned-char-param lever (docs/IDO_CODEGEN.md
 * feedback-ido-unsigned-char-param-homes-and-extends) — uchar a2/a3 emit the
 * sw a2,8(sp)/sw a3,0xC(sp) homes + eager andi zero-extends; comma-init
 * for-loop pre-header (sibling 99DC recipe) gives li a1,3 + sb-in-delay.
 * Siblings 9988/9B0C should re-try the same lever. */
void game_libs_func_00009C04(int *a0, char *a1, unsigned char a2, unsigned char a3) {
    int n;
    char *d, *s;
    for (n = 0, d = (char *)a0, s = a1; ;) {
        n++;
        d++;
        d[4] = *s;
        s++;
        if (n == 3) {
            break;
        }
    }
    *a0 = (*a0 & ~0x7F) | a2 | (a3 << 3);
}

/* game_libs_func_00009C5C: a0->0 = a1&0xFF; 3-iter char-transform loop
 * (a0 bytes 5..7 = a2[0..2] - 0x61, family 99DC/9B60/9C04 comma-init recipe);
 * then a 5-word copy a0[2..6] = a3[1..5], a0 byte 4 = 5, a0[7] = a3[0].
 * EXACT 32/32 (2026-07-08). The old diagnosis ("shared strength-reduced
 * offset C can't force") was wrong: the `li v0,1; sll v1,v0,2; addu a2,a3,v1;
 * addu a1,a0,v1` residue is IDO -O2's LOOP-UNROLL signature — write the copy
 * as a plain `for (i = 0; i < 5; i++) a0[i+2] = a3[i+1];`. IDO peels iter 0
 * with direct bases (lw 4(a3)/sw 8(a0)), materializes i=1, and emits the
 * remaining 4 iters at constant offsets from the shared i<<2 bases. The loop
 * MUST be phrased base-0 (`i=0..4`, indices i+2/i+1): the equivalent
 * `for (i = 1; i < 6; i++) a0[i+1] = a3[i];` materializes i=2 instead
 * (bases +8, offsets 0..C) = 23/32. */
void game_libs_func_00009C5C(int *a0, int a1, unsigned char *a2, int *a3) {
    int n;
    char *d;
    unsigned char *s;
    int i;
    *a0 = a1 & 0xFF;
    for (n = 0, d = (char *)a0, s = a2; ;) {
        n++;
        d++;
        d[4] = *s - 0x61;
        s++;
        if (n == 3) {
            break;
        }
    }
    for (i = 0; i < 5; i++) {
        a0[i + 2] = a3[i + 1];
    }
    *((char *)a0 + 4) = 5;
    a0[7] = a3[0];
}

int game_libs_func_00009CDC(int *a0) {
    if (a0[0] & 0x80) {
        return 1;
    }
    return 0;
}

int game_libs_func_00009D00(int *a0, int a1) {
    if (a0[7] < a1) {
        return 1;
    }
    return 0;
}

/* game_libs_func_00009D24 — 37/37 EXACT (2026-07-03, agent-e w4).
 * Target is IDO -O2's 4x-unrolled copy loop (andi rem=n&3 remainder-first
 * pre-loop + pointer-compare main loop). Two source properties required:
 *  1. Natural `for (i = 0; i < arg3; i++)` — NOT m2c's
 *     `if (arg3 > 0) do {...} while (i != arg3)` (91% shape) and NOT a
 *     guarded `!=` for-loop (emits a DOUBLE guard blez+beq and flips the
 *     sb/blez head order).
 *  2. Array-IXA spelling of the body: `((s32*)(arg0+8))[i] = ((s32*)arg2)[i]`
 *     — with char-pointer-arithmetic spelling (*(s32*)(arg0+i*4+8) = ...) the
 *     unroller fires but LFTR does NOT convert the main-loop exit test to the
 *     pointer compare (bne t0,t1 vs end-ptr a2+a3*4); it keeps the index
 *     counter (bne v0,a3 + addiu v0,v0,4 in-loop) = 36/37 + shifted. The
 *     IXA form makes uopt eliminate the index in the main loop (v0 dead
 *     after the entry beq) and test the strength-reduced source pointer.
 * Also: `sb a3` needs no mask (& 0xFFFF was harmless but pointless).
 */
void game_libs_func_00009D24(char *arg0, s32 arg1, s32 arg2, s32 arg3) {
  s32 i;
  *((int *) (((char *) arg0) + 0x1C)) = arg1;
  *((s8 *) (((char *) arg0) + 0x4)) = arg3;
  for (i = 0; i < arg3; i++) {
    ((s32 *) (arg0 + 8))[i] = ((s32 *) arg2)[i];
  }
  *((int *) (((char *) arg0) + 0x0)) = (s32) ((*((int *) (((char *) arg0) + 0x0))) | 0x80);
}

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
 *    feedback_doc_marker_is_bail.md.
 *
 * 2026-05-28: converted the comment-only bail into a real C body, 38.9%. 3-iter
 * loop (i: 0,12,24; exit at 36) over 12-byte records; each iter computes ia%5
 * (div + IDO break-6/7 safety traps), a signed floor-adjust on ib, a grid index,
 * and a 7-arg hook call (out_p, grid_idx, 0, ctx, *src, *(src+1), *(src+2)) where
 * ctx = &D+0xD430. The div/break traps, the floor-adjust, the 7-arg call shape and
 * the loop bounds match.
 * 2026-07-31 (agent-h) 38.9->92.31: (a) DECODE FIX — the "alignment adjust"
 * ternary was wrong for ib>=0; the andi/bgez/addiu-8 cluster is plain C
 * truncated `(ib % 8) << 3`, added unconditionally to ia%5. (b) REGALLOC
 * CRACKED via local-copy decl order: copy ALL loop-carried params to locals
 * declared op,va,vb,i (ctx last) — uopt colors a3->s0 first, then locals in
 * decl order s1..s4, hoisted consts 5/36 -> s5/s7, ctx -> s6 = target exactly;
 * inline src[k] call args give the target lw/sw arg-slot pairing; increment
 * order op,va,vb,src puts src+=3 in the latch delay slot like target.
 * RESIDUAL (~7.7%): 2-insn prologue schedule (sw ra/addiu s6 placement) + a
 * dead pre-header `move v0,zero` in target (kept init of a copy-propagated
 * z=0 third arg; a plain `int z=0` local gets DCE'd, does not reproduce).
 * Stays NM.
 * 2026-09-11 (agent-g): EXACT 65/65. The "dead pre-header move v0,zero that
 * no C form reproduces" + the sw ra/addiu s6 prologue split are the A670
 * eliminated-induction-variable shape
 * (docs/IDO_CODEGEN.md#basic-iv-elimination-leaves-dead-init-a670): the
 * loop is `for (k = 0; k < 3; k++)` with EVERY cursor derived inline in the
 * call -- out + k*2 (s1), ia + k (s2), ib + k (s3), src[k*3 + n] (s0 = src
 * + 12k) -- so k itself is eliminated (its init is the dead or v0,zero,zero
 * at 0x4C) and the trip test is retargeted onto the 12k byte-index IV (s4 vs
 * s7 = 36). Naming any cursor (`p = src + k*3`) re-orders the colours and
 * retargets the test onto the out cursor (s1 vs 24): keep them all inline.
 * ctx stays the inline `(char *)&D_00000000 + 0xD430` (uopt hoists it: lui
 * s6 / sw ra / addiu s6). */
extern int gl_func_00000000();
void gl_func_00009DB8(int *out, int ia, int ib, int *src) {
    int k;
    for (k = 0; k < 3; k++) {
        gl_func_00000000(out + k * 2, ((ia + k) % 5) + (((ib + k) % 8) << 3), 0,
                         (char *)&D_00000000 + 0xD430,
                         src[k * 3], src[k * 3 + 1], src[k * 3 + 2]);
    }
}

/* gl_func_00009EBC: 3-iteration loop dispatching to gl_func_00000000 with
 * a 5x8 grid index computed as (a1 % 5) + ((a2 % 8) << 3). The signed
 * remainder of a2 by 8 comes from a sign-preserving bgez/andi/beq dance
 * (low 3 bits, adjusted by -8 when a2<0 and low bits nonzero). Args:
 *   a0 = base pointer (dst is a0+0x18, advances +8/iter)
 *   a1 = row seed (advances +1/iter, fed to %5)
 *   a2 = col seed (advances +1/iter, fed to signed-%8)
 *   a3 = pointer to sink ints, advancing one word per iter.
 * 2026-09-11 (agent-g): EXACT 59/59. The 84.1% wrap hand-stepped four
 * cursors (dst += 8; row++; col++; a3++) inside `for (i = 0; i != 12; i += 4)`
 * and named the D+0xD434 arg as a pinned extern. Same shape as its sibling
 * gl_func_00009DB8 (docs/IDO_CODEGEN.md
 * #iv-elimination-corollaries-candidate-first-addu-inline-cursors-aaec-9db8-afc4):
 * `for (k = 0; k < 3; k++)` with every cursor derived INLINE in the call --
 * x0 + 0x18 + k*8 (s0, first occurrence = a0 + 24), (a1 + k) % 5 (s1),
 * (a2 + k) % 8 (s2), a3[k] (s4 = a3 + 4k) -- so k is eliminated (the dead
 * `or v0,zero,zero` is its init) and the trip test is retargeted onto the
 * 4k byte-index IV (s3 vs s7 = 12); the D+0xD434 arg is the inline
 * `(char *)&D_00000000 + 0xD434` (uopt hoists it to s6, lui s6,1 /
 * addiu s6,s6,-11212 = the carry form). */
extern int gl_func_00000000();
void gl_func_00009EBC(char *x0, int a1, int a2, int *a3) {
    int k;
    for (k = 0; k < 3; k++) {
        gl_func_00000000(x0 + 0x18 + k * 8, ((a1 + k) % 5) + (((a2 + k) % 8) << 3),
                         (char *)&D_00000000 + 0xD434, a3[k]);
    }
}

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

/* gl_func_0000A00C: process two parallel slot-arrays (a0 and a0+0x18), 3 iters
 * of stride 8: for each slot, if gl_func(slot) != 0, gl_func(slot, a1, a2, a3).
 * a2/a3 are `unsigned char` params -> IDO homes the raw args to their incoming
 * slots (sw a2,0x40; sw a3,0x44) AND eagerly zero-extends once at the top
 * (andi s4,a2,0xFF; andi s5,a3,0xFF), matching the target exactly. */
extern int gl_func_00000000();
void gl_func_0000A00C(int a0, int a1, unsigned char a2, unsigned char a3) {
    int s3 = a1;
    int s4 = a2;
    int s5 = a3;
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
 * CRACKED 2026-05-27 via first-assignment-order lever:
 *   - `int i, count; char *p;` (decl)
 *   - `count = 0;` then `i = 0;` then `p = a0 + 0x18;` (assignment order)
 *   - `for (; i != 24; i += 8)` (empty for-init since i already set)
 * The decl-order said "register-priority isn't decl-driven", but the
 * ASSIGNMENT ORDER controls the emit order of the `or sX, zero, zero`
 * init insns. Target emits `or s2, zero` (count) BEFORE `or s0, zero`
 * (i); source-order `count = 0; i = 0;` (count assigned first) produces
 * exactly that. Bytes 25/25. */
extern int gl_func_00000000();
int gl_func_0000A130(char *a0) {
    int i, count;
    char *p;
    count = 0;
    i = 0;
    p = a0 + 0x18;
    for (; i != 24; i += 8) {
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

/* game_libs_func_0000A1B0: ms -> {minutes, seconds, hundredths} byte triple,
 * then find-first-match over 3 stride-8 entries. BYTE-EXACT 66/66 (2026-09-09,
 * agent-g) as ONE function [0xA1B0,0xA2B8): the 4-word "game_libs_func_0000A1B0"
 * (`ori a3,zero,0xEA60; div a1,a3; mflo v0; li t0,1000`) was the hoisted
 * `ms / 60000` head of the 0xF8 INCLUDE_ASM gl_func_0000A1C0 (agent-c's
 * fake-param class, docs/MATCHING_WORKFLOW.md#game-libs-fake-param-exact-sweep-agent-c).
 * Sym oracle (section = splat + 0x1466C): 0x1E81C (0xA1B0) = export sym 1066
 * with 1 R_MIPS_26 ref (TextReloc @0x2154C); 0x1E82C (0xA1C0) not exported, no
 * baked jal. The jal at +0xC4 is blank R_MIPS_26 to sym1044 (text 0x1E0BC =
 * splat 0x9A50, game_libs_func_00009A50) -> func_00000000, same callee shape as
 * the matched gl_func_0000A4D0 sibling below (loop body identical: beqzl +
 * `addiu s0` likely-fill, `b` + `or v0,s0` exit, tail-dup `addiu s0`).
 * Shape keys: (1) the remainders are written as `x - q * d` (IDO emits
 * `mflo q; multu q,d; subu` -- a `%` gives `mfhi` instead); (2) `int i`
 * declared BEFORE `buf` puts i's dead home at 0x44 and buf at 0x40; (3) only
 * three named scalars (min, rem, sec) -- a fourth `rem2` home grows the frame
 * to 0x50; (4) i/entry initialised in the for-header so their `or s0/s1` land
 * in the multu latency slot after the second div check, not above it. */
extern int func_00000000();
int game_libs_func_0000A1B0(int *a0, int ms) {
    int i;
    unsigned char buf[4];
    char *entry;
    int min, rem, sec;
    min = ms / 60000;
    rem = ms - min * 60000;
    buf[0] = min;
    sec = rem / 1000;
    buf[1] = sec;
    buf[2] = (rem - sec * 1000) / 10;
    for (i = 0, entry = (char *)a0; i < 3; i++) {
        if (func_00000000(entry, buf) != 0) {
            return i;
        }
        entry += 8;
    }
    return 3;
}

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

/* gl_func_0000A670: 8-slot twin-call loop over two data-segment tables (62 insns,
 * frame 0x38, s0-s7) -- EXACT 62/62 (2026-09-11 agent-g; was NM 95.5). The three
 * cursors are BASIC-INDUCTION-VARIABLE derivations, not hand-stepped pointers: written
 * as `for (k = 0; k < 8; k++)` with `arg0 + k*0x30`, `k*3`, `&D + 0xD268 + k*0x24`,
 * `&D + 0xD388 + k*0xC`, uopt's findinduct/eliminduct turns each product into its own
 * s-register IV, replaces the trip test with the 0xD388 cursor vs the baked end
 * (`lui/addiu -11288` = 0xD3E8), and leaves the eliminated k's init behind as the dead
 * `or v0,zero,zero` (the residual the hand-stepped form could never emit). The s-colours
 * follow first occurrence: the arg cursor must be named BEFORE `i = k * 3` (s0/s1).
 * Both callees are the USO-reloc blank (jal 0x0): the in-TU K&R gl_func_0000959C would
 * link a real address into the ROM. See docs/IDO_CODEGEN.md#basic-iv-elimination-leaves-dead-init-a670. */
void gl_func_0000A670(s32 arg0) {
    s32 k;
    s32 p;
    s32 i;
    for (k = 0; k < 8; k++) {
        p = arg0 + k * 0x30;
        i = k * 3;
        gl_func_00000000(p, i % 5, i % 8, (char *)&D_00000000 + 0xD268 + k * 0x24);
        gl_func_00000000(p, i % 5, i % 8, (char *)&D_00000000 + 0xD388 + k * 0xC);
    }
}

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

void gl_func_0000A7B4(char *obj, int a1, unsigned char c2, unsigned char c3, unsigned char *flags) {
    char *p = obj;
    int i;
    for (i = 0; i != 8; i++) {
        if (gl_func_00000000(p) != 0 || gl_func_00000000(p + 0x18) != 0) {
            *flags |= (1 << i);
        }
        gl_func_00000000(p, a1, c2, c3);
        if (a1) {}
        p += 0x30;
    }
}

/* === EXACT MATCH 49/49 (in-tree, clean rebuild x2, 2026-07-03 agent-e) ===
 * CRACK: 3-register cyclic s-reg renumber (a1/c2/c3 wanted s3/s4/s5, got s5/s3/s4).
 * Root (zdbug:6): coloring priority adjsave a1=3.33 < masks=3.67 -> masks colored
 * first. LEVER (new): dead `if (a1) {}` placed AFTER the third call, BEFORE
 * `p += 0x30` -- the empty-if is deleted (zero emission, still 49 insns) but its
 * BB survives to priority computation: a1 gets +10 in-loop refs (cond use) while
 * the masks are DEAD at that point (last use = call args), so they keep span 3:
 * a1 (10+10)/4 = 5.0 > masks 11/3 = 3.67 > bound8 10/3 = 3.33, and flags 20/3 =
 * 6.67 stays above. Placement is EVERYTHING:
 *   - inside flags-block: masks live-through -> span-hit -> masks fall below bound8
 *   - pre-loop: a1 span-hit at entry weight -> a1 falls to s6 + i/obj flip
 *   - after third call: EXACT.
 * Multi-var conditions (a1&&c2 etc.) EMIT +4 insns; only single-var empty-if is free. */

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
/* game_libs_func_0000A8D8: bit-test accessor; splat split the return-0 tail
 * into the 0000A8F8 empty stub (sibling of the 00009A2C family). Merged. */
int game_libs_func_0000A8D8(int *a0) {
    if ((a0[0] >> 5) & 1) {
        return 32;
    }
    return 0;
}

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

/* gl_func_0000AA28 — 21/21 EXACT (2026-07-03, agent-e w4).
 * Was documented "cap: IDO scheduling choice, redundant lw a1 reload not
 * reachable from C". FALSE — it was a LOGIC bug. The target has NO a1/a2
 * reloads before the second jal (only `lw a0,0x18(sp)` in the delay slot),
 * so the second call takes ONLY a0: gl_func_00000000(a0), not (a0,a1,a2).
 * With three args, the compiler must reload a1/a2 before the 2nd call ->
 * the +1-insn "redundant reload" residual. One-arg call = byte-exact,
 * including the dead `move v0,zero` fail-block head at +0x40 (both bnels
 * retargeted past it with the v0=0 dup in their delay slots) and the
 * `b +2; li v0,1` tail. goto-fail structure unchanged.
 * Sub-94% "scheduler cap" verdicts can hide arg-list logic diffs: check
 * which arg regs are (re)loaded before each jal FIRST. */
extern int gl_func_00000000();
int gl_func_0000AA28(int a0, int a1, int a2) {
    if (gl_func_00000000(a0, a1, a2) != a1) goto fail;
    if (gl_func_00000000(a0) != a2) goto fail;
    return 1;
fail:
    return 0;
}

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
 * INSN_PATCH was the previous lever for IDO's unreachable setup scheduling
 * and raw USO data immediates. INSN_PATCH REMOVED 2026-05-23 as match-faking
 * per feedback_no_instruction_forcing_matches_policy. Now an honest NM cap.
 */
/* 2026-09-11 (agent-g): EXACT 33/33. The "IDO's unreachable setup
 * scheduling" cap was the A670 eliminated-induction-variable shape
 * (docs/IDO_CODEGEN.md#basic-iv-elimination-leaves-dead-init-a670): the
 * hand-stepped self_p / data2 cursors rotate the s-colours (s1<->s2, 12
 * words); `for (i = 0; i < 3; i++)` with both cursors derived as
 * `base + i * stride` gives s0 = i, s1 = a0 + i*0x20, s2 = D + 0xD3E8 +
 * i*0x18 (A670's second-table END cursor: this walks the next 3 records),
 * s3 = D + 0xD438 held, s4 = 3 (the old "D_1D438 / D_1D3E8" reading of the
 * `lui 1; addiu -0x2C18` pair ignored the carry: the pair is D + 0xD3E8). The index arg `(i | 0) + ((i + 4)
 * << 3)` keeps the candidate FIRST in the addu (target `addu a1,s0,t7`; the
 * bare `i + ...` / `... + i` both put the sll temp first -- the 675A4
 * deeper-operand-first rule); `(i + 4) * 8 + i` / `i * 9 + 32` are
 * strength-reduced into a second derived IV (32 words, `addiu s2,s2,9`). */
void gl_func_0000AAEC(char *a0) {
    int i;
    for (i = 0; i < 3; i++) {
        gl_func_00000000(a0 + i * 0x20, (i | 0) + ((i + 4) << 3),
                         (char *)&D_00000000 + 0xD438,
                         (char *)&D_00000000 + 0xD3E8 + i * 0x18);
    }
}

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

/* gl_func_0000ABBC: 3-slot notify loop with flag-history update, BYTE-EXACT
 * 64/64 (2026-10-14 agent-g; the 83.2% wrap hand-carried i / one / limit /
 * cursor locals). For each 0x20-byte slot whose probe returns non-zero: call
 * the second handler with (slot, a1, a2, a3), then shift the history byte
 * by slot (i == 0: keep bits 0-1 shifted up; i == 1: move bit 1 to bit 2)
 * and set bit i. Match keys: the `beqzl s0 / beql s0,s6 / b` ladder with
 * the case blocks laid out after it is a SWITCH (if/else-if gives bnez +
 * fallthrough); the s6 = 1 / s7 = 3 registers are IDO's hoisted loop
 * constants, not locals; the case-1 value puts the shifted term FIRST,
 * `((*f & 2) << 1) | (*f & 1)` (andi-1 then takes t9 with the and-2/sll
 * pair in t0/t1 -- the written-second-is-allocated-first order). */
void gl_func_0000ABBC(char *a0, int a1, unsigned char a2, unsigned char a3, unsigned char *arg4) {
    int i;
    for (i = 0; i < 3; i++) {
        if (gl_func_00000000(a0 + i * 0x20) != 0) {
            gl_func_00000000(a0 + i * 0x20, a1, a2, a3);
            switch (i) {
            case 0:
                *arg4 = (*arg4 & 3) << 1;
                break;
            case 1:
                *arg4 = ((*arg4 & 2) << 1) | (*arg4 & 1);
                break;
            }
            *arg4 |= 1 << i;
        }
    }
}

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

/* gl_func_0000AD2C: 28-insn 3-iter try-or-advance loop. MATCHED (byte-exact).
 * The "natural ceiling 92.14%" prologue-setup-reorder cap was MISDIAGNOSED:
 * it was a first-use ordering issue. Fix = a separate pointer local `p = a0`
 * AND initializing `i = 0` BEFORE `p = a0` (so the saved-reg copy order becomes
 *   move s2,a1 / sw ra / move s0,0 (i) / move s1,a0 (p)
 * matching target). Both levers needed: the bare-loop form copied s1=a0 first. */
extern int gl_func_00000000();
int gl_func_0000AD2C(char *a0, int a1) {
    char *p;
    int i;
    i = 0;
    p = a0;
    for (; i != 3; i++) {
        if (gl_func_00000000(p, a1) != 0) return i;
        p += 0x20;
    }
    return 3;
}

/* gl_func_0000AD9C: insert-shift on a 3-slot array of 32-byte records:
 * if idx < 3, move records [idx..1] up one slot (arr[i] = arr[i - 1] for
 * i = 2 down to idx + 1), then hand the freed slot &arr[idx] to the
 * callee with the three trailing args. The 138-word body is IDO's x4
 * unrolled struct-copy loop (remainder loop + 4-copy main loop); the old
 * m2c wrap spelled the unrolled form out by hand (90.74%).
 * Matching notes: the explicit `if (idx < 2)` guard is the duplicated
 * `slti at,a1,2; beqz` pair (the for's own entry test is the second);
 * the call address must be the int-scaled `(char *)arr + idx * 32`
 * (arr-first t2/t5 ring) -- `&arr[idx]` / `arr + idx` swap the reload and
 * shift registers in both preheaders. */
struct AD9C_Rec {
    int w[8];
};
void gl_func_0000AD9C(struct AD9C_Rec *arr, s32 idx, s32 a2, s32 a3, s32 a4) {
    s32 i;

    if (idx < 3) {
        if (idx < 2) {
            for (i = 2; i > idx; i--) {
                arr[i] = arr[i - 1];
            }
        }
        gl_func_00000000((char *)arr + idx * 32, a2, a3, a4);
    }
}

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_0000AFC4: 57-insn joybus/controller-block init. WAVE-3 REDECODE
 * 2026-07-15 (agent-h): old body was mis-typed m2c (int derefs at byte
 * offsets -> swl/swr pairs, 65 insns, 32.65 fuzzy). Retyped: s16/u16 header
 * words, byte stores, u8 call args (lbu), scalar-extern flag store ($at
 * macro), fnptr call via *(D+0x28) vtable with lh 0x30 + &D base arg.
 * Frame 0x48 via volatile pads split 2-above/4-below sp3C (slot 0x3C).
 * Calls are jal 0x0 zero-alias. RESIDUAL 6 words = three adjacent-pair
 * as1 emission-order ties (li 8/move zero preheader; lui at/lui v1; sw
 * flag/addiu base) — probed 12 spellings (joins, statement order, decl
 * order, if(1), loop-form): all inert. NM wrap; INCLUDE_ASM build path.
 * 2026-09-11 (agent-g): EXACT 57/57. The three "as1 emission-order ties"
 * were two spellings: (1) `for (var_v1 = 0; var_v1 != 8; var_v1 += 4)` puts
 * the counter init AFTER the hoisted bound (`addiu a0,8; or v1,zero`) where
 * the do/while put it before (docs/IDO_CODEGEN.md
 * #for-init-vs-dowhile-preheader-lui-addiu-adjacency-66d54, C784 corollary);
 * (2) the held `&D_00000000` web (lui v1 / addiu v1,v1,0: the vtable load
 * base AND the `addu a0,t2,v1` arg) is hoisted to the top of its basic block,
 * i.e. above the flag-store chain (`lui at ... sw t0,0(at)`); a
 * `do { } while (0)` around the vtable-call block starts that BB after the
 * flag store, so uopt emits the flag chain first and as1 lands `lui at; lui
 * v1; ...; sw t0,0(at); addiu v1,v1,0` (64DEC finding 3). A `do {}` around
 * the flag store alone or `if (1) { }` work the same; a named `base` local
 * grows the frame (+8) and keeps the web first. */
typedef char *(*GP_0000AFC4)();
extern int gl_flag_AFC4_bit2;
void gl_func_0000AFC4(char *arg0) {
    volatile int padA_afc4[2];
    s32 sp3C;
    volatile int padB_afc4[4];
    s32 var_v1;
    char *temp_v0;
    char *var_v0;

    *(s16 *)(arg0 + 2) = 1;
    *(s16 *)(arg0 + 0) = 0x1F;
    *(u16 *)(arg0 + 4) = 8;
    arg0[18] = 8;
    arg0[19] = 8;
    arg0[20] = 8;
    var_v0 = arg0;
    for (var_v1 = 0; var_v1 != 8; var_v1 += 4) {
        var_v0[6] = 0;
        var_v0[7] = 0;
        var_v0[8] = 0;
        var_v0[9] = 0;
        var_v0 += 4;
    }
    arg0[14] = 0;
    arg0[15] = 0;
    arg0[16] = 0;
    arg0[17] = 0;
    gl_func_00000000(*(u8 *)(arg0 + 18));
    gl_func_00000000(*(u8 *)(arg0 + 19));
    gl_func_00000000(*(u8 *)(arg0 + 20));
    gl_func_00000000(*(u16 *)(arg0 + 4) & 3);
    gl_flag_AFC4_bit2 = (*(u16 *)(arg0 + 4) & 4) == 4;
    do {
        temp_v0 = *(char **)((char *)&D_00000000 + 0x28);
        sp3C = 0x15;
        ((GP_0000AFC4)FW(temp_v0, 0x34))(*(s16 *)(temp_v0 + 0x30) + (int)&D_00000000, &sp3C);
    } while (0);
}

#ifdef NON_MATCHING
/* gl_func_0000B0A8: constructor. obj = arg0 ?: alloc(0x18); obj->0x10=arg1,
 * obj->0x14=0; obj->0=cb(arg1); obj->4=cb(obj->0x10); obj->8=cb(obj->0x10);
 * if (arg3==-1) arg3=cb(obj->8); v=cb(obj->8,arg2,arg3); if (v==0) {
 * cb(obj->8,0); obj->8->4=0; if(obj->8->8) cb(obj->8->8); obj->8->8=0; }.
 * 2026-07-02 relever (agent-e): 11 -> 5 diffs (53/58). Two cracks: (1) REUSE
 * THE PARAM (no `int *s0` local) -- param arg0 colors $s0 and its `or s0,a0`
 * reglod emits in the SAVE region (target pos 2), freeing the bnez delay for
 * `sw a3` (was: local copy deferred into the delay slot). (2) declare the
 * flag local FIRST -- M-var homes map vreg-order->descending sp slots, so
 * flag -4 -> sp+0x24 (was second/-8 -> sp+0x20). RESIDUAL (5 diffs, cap):
 * cleanup web `(int*)obj->8` reload colored $v1, target $v0. zdbug:6 shows
 * the web colored (adjsave 2.0) with v0 FORBIDDEN (piece live into the jal's
 * v0-def); target's is uncolored/ugen-bound v0. Split spellings (ptr-load
 * (int**)[2] vs cvt) DO break the web but ugen binds t8/t9, not v0; volatile,
 * char-cast, int-arith, if(1){}, do-while, dup-store all inert or regress. Doc 13516
 * reload-site v0/v1 class -- interferer for v1 is never emission-neutral.
 * 2026-07-15 agent-h: volatile base-load (`*(int * volatile *)(arg0+2)`) DOES
 * split the cross-call union (t8/t9 separate ugen temps) but a volatile store
 * can't be hoisted into the beql-likely delay (reload lands there instead) and
 * regs land t8/t9 not v0. Store-duplicated if/else arms split the post-call
 * reload (t8, own web) but cond web stays v1 and the else arm blocks the
 * cross-jump merge (+2 insns). Return-capture precolor N/A (capture point is
 * before the union span). Cap confirmed.
 * 2026-07-15b CAP RETRACTED — 58/58 masked-exact via the void-alias
 * dead-$v0-exclusion lever (docs #wave3-game-uso-transfer 102CC): BOTH
 * discarded-return cleanup calls (f(obj[2],0) AND f(obj[2][2])) go through
 * void-returning zero-alias gl_func_00000000_b0a8v, removing their jals'
 * v0-defs; the multi-def cleanup web then colors $v0 (was v0-FORBIDDEN by
 * "piece live into the jal's v0-def"). Aliasing only the inner call was
 * INERT — the web's first piece is created at the FIRST call's arg
 * evaluation (arg0[2] CSE'd between arg use and post-call reload), so every
 * jal the web touches must shed its v0-def. Placeholder-callee (jal 0)
 * objdiff-100: stays NM wrap, no episode. */
extern int gl_func_00000000();
int gl_func_0000B0A8(int *arg0, int arg1, int arg2, int arg3) {
    int v1;
    if (arg0 == 0) {
        arg0 = (int *)gl_func_00000000(0x18);
        if (arg0 == 0) goto end;
    }
    arg0[0x10 / 4] = arg1;
    arg0[0x14 / 4] = 0;
    arg0[0] = gl_func_00000000(arg1);
    arg0[1] = gl_func_00000000(arg0[0x10 / 4]);
    arg0[2] = gl_func_00000000(arg0[0x10 / 4]);
    if (arg3 == -1) {
        arg3 = gl_func_00000000(arg0[2]);
    }
    v1 = 0;
    if (gl_func_00000000(arg0[2], arg2, arg3) != 0) {
        v1 = 1;
    }
    if (v1 == 0) {
        {
            extern void gl_func_00000000_b0a8v();
            gl_func_00000000_b0a8v(arg0[2], 0);
        }
        ((int *)arg0[2])[1] = 0;
        if (((int *)arg0[2])[2] != 0) {
            extern void gl_func_00000000_b0a8v();
            gl_func_00000000_b0a8v(((int *)arg0[2])[2]);
        }
        ((int *)arg0[2])[2] = 0;
    }
end:
    return (int)arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B0A8);
#endif

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
/* gl_func_0000B310 — 40/40 EXACT (2026-07-03, agent-e w4).
 * Was documented "NATURAL CEILING 92.93% — or v0,s2,zero delay-slot insertion
 * not naturally reachable". CRACKED with three coupled levers:
 *  1. Explicit copy-then-redefine order `r = count; count++; a1[r] = iter;`
 *     — the genuine redefinition of count BETWEEN the copy's def and its use
 *     blocks copyprop (D418 lever-1 rule: "only a genuine later redefinition
 *     sticks"), so `or v0,s2,zero` materializes at the store-block head and
 *     as1 dups it into the bnel delay + fills the beq delay with it.
 *     (a1[count++], |0, |known-zero-var, 2-def-web idx all FOLD.)
 *  2. VOID return type — with `int` return, as1 treats $v0 as live-out at jr,
 *     which forbids the fall-through `or v0,s2,zero` fill on the taken path
 *     of the second branch -> rule-3 beql + iter++ dup (+1 insn). void ->
 *     plain beq + or-in-delay = target shape (38/40).
 *  3. Same-line tie-break: `r = count; count++; a1[r] = iter;` all on ONE
 *     line flips the final as1 tie (addiu s2,s2,1 vs sw s0,0(t9)) so the
 *     store emits first (40/40). The shared line is LOAD-BEARING.
 */
extern int gl_func_00000000();
void gl_func_0000B310(int *a0, int *a1) {
  int count = 0;
  int iter = 0;
  int offset = 0;
  int r;
  for (; iter != 8; iter++)
  {
    if (gl_func_00000000(a0[0] + offset) || gl_func_00000000(a0[0] + offset))
    {
      r = count; count++; a1[r] = iter;
    }
    offset += 0x30;
  }
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

/* 15-insn 2-call wrapper (0x3C). LANDED fuzzy=100. The historical 4-byte
 * SUFFIX_BYTES tail (`sll/subu/addiu/div` computing (a1*3)/5, supplying
 * stolen-prologue setup for successor gl_func_0000B5AC) was REMOVED
 * 2026-05-23 as match-faking; those bytes now belong to B5AC's own symbol.
 * The 4 words [0xB59C,0xB5AC) were later restored to gl_func_0000B5AC.s
 * (relayout, 2026-06); they are B5AC's own hoisted head, matched as C
 * 2026-09-09 -- see the successor just below. */
extern int gl_func_00000000();
void gl_func_0000B560(int *p) {
    gl_func_00000000(p[4], p[0]);
    gl_func_00000000(p[4], p[1]);
}

/* gl_func_0000B5AC: per-slot dispatch pair, BYTE-EXACT 35/35 (2026-09-09, agent-g)
 * as ONE function [0xB59C,0xB628) -- the .s already carries the 4-word head
 * (`sll v0,a1,2; subu v0,v0,a1; li at,5; div v0,at`), which is the hoisted
 * `n = a1*3` + `n % 5` of the body, exactly as its twin game_libs_func_0000B628
 * just below (docs/MATCHING_WORKFLOW.md#game-libs-fake-param-exact-sweep-agent-c).
 * Sym oracle (section = splat + 0x1466C): 0x1FC08 (0xB59C) = export sym 1103;
 * 0x1FC18 (0xB5AC) is NOT exported. The 3-month "inherits $hi and $v0 from
 * B560's tail-SUFFIX, caller-specific $v0" verdict is retracted: the div has no
 * mflo, $v0 stays n = a1*3 (`bgez v0 / andi v0,7 / addiu -8` = signed n % 8),
 * `mfhi a1` = n % 5 (single-use constant divisor -> assembler div macro, no
 * zero/overflow checks). Differences from B628: the table is `D + 0xD268`
 * (`lui 1; addiu 0xD268` = sign-carry, NOT 0x1D268) and the entry index is
 * `a1 * 9` ints (`or t8,a1; sll t0,t8,3; addu t0,t0,t8; sll t1,t0,2`), not n.
 * Load-bearing: the a1*9 index must be a NAMED local (`int k = a1 * 9;`) --
 * inline `tbl + a1 * 9` / `tbl + a1 * 36` bytes / `tbl[a1]` on a stride-36
 * row all emit the same insns but renumber the triple (t0 reused for the sll,
 * lui in t1) -> 8 diff words; the named temp keeps t0 live so the sll gets t1
 * and the hi/lo pair t2. `a1 * 48` is a separate stride-48 record index; the
 * `do { } while (0)` around the table base is the same reassociation guard as
 * B628 (docs/IDO_CODEGEN.md#bb-boundary-blocks-sym-addend-reassociation-b628).
 * Both jals are blank (R_MIPS_26 -> func_00000000). */
extern int func_00000000();
void gl_func_0000B5AC(int *a0, int a1) {
    int n = a1 * 3;
    int k = a1 * 9;
    int *tbl;
    do { tbl = (int *)((char *)&D_00000000 + 0xD268); } while (0);
    func_00000000(*a0 + a1 * 48, n % 5, n % 8, tbl + k);
    func_00000000(a0);
}

/* game_libs_func_0000B628: per-slot dispatch pair, BYTE-EXACT 33/33 (2026-09-09,
 * agent-g) as ONE function [0xB628,0xB6AC): the 4-word "game_libs_func_0000B628"
 * (`sll v0,a1,2; subu v0,v0,a1; li at,5; div v0,at`) was the hoisted `n = a1*3`
 * + `n % 5` head of the 0x74 INCLUDE_ASM gl_func_0000B638 (agent-c's fake-param
 * class, docs/MATCHING_WORKFLOW.md#game-libs-fake-param-exact-sweep-agent-c).
 * Sym oracle (section = splat + 0x1466C): 0x1FC94 (0xB628) = export sym 1104;
 * 0x1FCA4 (0xB638) not exported, no baked jal. The old "INHERITS $hi and $v0
 * from B5AC's tail, uninterruptible mfhi-then-bgez" verdict is retracted: the
 * div has NO mflo -- $v0 stays n = a1*3 (the `bgez v0 / andi v0,7` is the
 * signed `n % 8`, `sll t0,v0,2` the table index) and `mfhi a1` is `n % 5`
 * (single-use constant divisor -> assembler macro form `li at,5; div`, no
 * zero/overflow checks). bootup.uso TextReloc: HI16/LO16 @+0x30/+0x34 ->
 * sym2 (Data base) with 0xD388 baked = the table `(char *)&D_00000000 +
 * 0xD388` (the A670 cursor family below), R_MIPS_26 @+0x64 -> sym1059 (text
 * 0x1E528 = splat 0x9EBC) and @+0x6C -> sym1102 (text 0x1FBCC = splat 0xB560,
 * the dispatcher head), both blank -> func_00000000. `a1 * 48` is strength-
 * reduced from scratch (`sll; subu; sll 4`), not `n << 4`: a separate
 * stride-48 record index, so it is spelled separately. The `do { } while (0)`
 * around the table-base assignment is load-bearing: without the block
 * boundary uopt reassociates `(D + 0xD388) + n*4` into `D + (0xD388 + n*4)`
 * (`lui/addiu D; ori at,0xD388; addu; addu`, 36 words) instead of holding
 * D+0xD388 with the addend in the hi/lo pair (`sll t0,v0,2; addu a3,t0,t1`)
 * -- docs/IDO_CODEGEN.md#bb-boundary-blocks-sym-addend-reassociation-b628. */
extern int func_00000000();
void game_libs_func_0000B628(int *a0, int a1) {
    int n = a1 * 3;
    int *tbl;
    do { tbl = (int *)((char *)&D_00000000 + 0xD388); } while (0);
    func_00000000(*a0 + a1 * 48, n % 5, n % 8, tbl + n);
    func_00000000(a0);
}

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
    if (a0 == 0) {
        a0 = (void*)gl_func_00000000(8);
        if (a0 == 0) {
            goto end;
        }
    }
    *(int*)a0 = 6400;
    gl_func_00000000((char*)&D_00000000 + 0xD43C);
    if (gl_func_00000000(a0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD460);
        gl_func_00000000(a0);
    }
    if (gl_func_00000000(a0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD478);
        gl_func_00000000(a0);
    }
    if (gl_func_00000000(a0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD490);
        gl_func_00000000(a0);
    }
    if (gl_func_00000000(a0) == 0) {
        gl_func_00000000((char*)&D_00000000 + 0xD4A8);
        gl_func_00000000(a0);
    }
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000((char*)&D_00000000 + 0xD4C0, 0x8004);
end:
    return a0;
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

#ifdef NON_MATCHING
/* gl_func_0000B958: 69-insn word-array equality predicate. Compares a3/4 words
 * (signed div, trunc-toward-zero — target's `bgez a3; sra a3,2 / addiu a3,3;
 * sra` idiom, NOT (a3+3)/4) of a1[] vs a2[]; returns 0 on first mismatch, 1 if
 * all equal. a0 is dead (saved, never read). RELOC-FREE and -O2.
 * Target is IDO's 4-way Duff's-device UNROLL (andi&3 remainder prologue, v0
 * counts up; 4-wide main body, v0 += 4; v0==n short-exit only on the rem!=0
 * path). A hand-unrolled C form was tried 2026-06-02: IDO re-expanded the
 * nested do-whiles to 173 insns (vs 69) — worse, fuzzy=None. The plain loop
 * below (corrected divisor) is the faithful reference; exact unroll is
 * permuter-class. */
int gl_func_0000B958(int a0, int *a1, int *a2, int a3) {
    int n = a3 / 4;
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

/* gl_func_0000BB14: reads 4 8-byte chunks from a0 (offsets
 * 0x188/0x1F0/0x210/0x228) into local data[32], hashes via 0xD1265205 into
 * hash[8], then submits at offset 0. The stack slot order is the match key:
 * declaring `hash` BEFORE `data` puts hash at the higher slot (sp+0x40) and
 * data at sp+0x20 (IDO first-declared = highest offset). The prior comment
 * called this "C-unreproducible / frame -0x60" — that was stale; the swap
 * makes it byte-exact. */
extern int gl_func_00000000();
void gl_func_0000BB14(int a0) {
    char hash[8];
    char data[0x20];
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

/* gl_func_0000BC84: record-pair load/compare/store with 0xDEADBBAD sentinel.
 * Loads two records (504/528) into stack bufs, builds a compare block, compares;
 * if first pair matches returns 1, else tries a second pair (0x7FC8/0x7FE0) and
 * on match stores it back + returns 1, else returns 0. MATCHED 2026-05-29 (fresh
 * decode): the key was structuring the second-pair logic UNDER `if (cmp1 == 0)`
 * with a SHARED `return 1` at the end — the target jumps to that shared exit via
 * bnez (an inline `if (cmp1 != 0) return 1;` emits beqz + a duplicated block).
 * Buffer sizes (24/8) from the cb args; layout bufA@0x50/bufB@0x48/cmp@0x40/
 * bufC@0x28/bufD@0x20 falls out of declaration order. */
extern int gl_func_00000000();
int gl_func_0000BC84(int *s0) {
    char bufA[24];
    char bufB[8];
    char cmp[8];
    char bufC[24];
    char bufD[8];
    gl_func_00000000(s0, bufA, 504, 24);
    gl_func_00000000(s0, bufB, 528, 8);
    gl_func_00000000(cmp, bufA, 24, 0xDEADBBAD);
    if (gl_func_00000000(cmp, bufB) == 0) {
        gl_func_00000000(s0, bufC, 0x7FC8, 24);
        gl_func_00000000(s0, bufD, 0x7FE0, 8);
        gl_func_00000000(cmp, bufC, 24, 0xDEADBBAD);
        if (gl_func_00000000(cmp, bufD) == 0) {
            return 0;
        }
        gl_func_00000000(s0, 504, bufC, 24);
        gl_func_00000000(s0, 528, bufD, 8);
    }
    return 1;
}

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

/* gl_func_0000BDE8: copies a 384-byte struct from src into a stack buffer, then
 * runs 7 callbacks marshalling buf1 (384B) and buf2 (8B) with a 0xDEADBBAD
 * sentinel and the field constants 8/384/392/0x7DD8/0x7F58. Fresh decode
 * 2026-05-29: 96.15%, everything exact (the 3-word-unrolled 384B copy, all 7
 * calls + args, buffer layout buf1@sp+0x28/buf2@sp+0x20) EXCEPT a 2-instruction
 * prologue tie -- target emits `move t9,a0` (copy-cursor init) before
 * `sw ra,28(sp)`; the multi-line source emitted the ra-save first.
 * 2026-09-11 (agent-g): EXACT 52/52. as1 breaks that tie by SOURCE LINE
 * (docs/IDO_CODEGEN.md#same-line-brace-return-sinks-arg-home-c3e8): `sw ra`
 * belongs to the entry line (the `{`), the copy-cursor `or t9,a0` to the
 * `buf1 = *src` line; on separate lines line order wins (sw ra first). The
 * initializer `struct B384 buf1 = *src;` ON THE BRACE LINE gives both the
 * same line and the copy init sinks first. The brace-line layout is
 * LOAD-BEARING -- do not reformat. (A plain `buf1 = *src;` statement on the
 * brace line works too; the copy + first call joined on a later line does
 * not.) */
extern int gl_func_00000000();
struct B384 { int w[96]; };
struct B8 { int w[2]; };
void gl_func_0000BDE8(int s0, struct B384 *src) { struct B384 buf1 = *src; struct B8 buf2;
    gl_func_00000000(&buf1);
    gl_func_00000000(s0, 8, &buf1, 384);
    gl_func_00000000(&buf2, &buf1, 384, 0xDEADBBAD);
    gl_func_00000000(s0, 392, &buf2, 8);
    gl_func_00000000(s0, 0x7DD8, &buf1, 384);
    gl_func_00000000(s0, 0x7F58, &buf2, 8);
    gl_func_00000000(s0);
}

/* gl_func_0000BEB8: record-pair load/compare/store, sibling of gl_func_0000BC84
 * (same 0xDEADBBAD-sentinel compare structure; bigger 384-byte records, keys
 * 8/392 then 0x7DD8/0x7F58). Fresh decode 2026-05-29 via the BC84 template
 * (shared `return 1`, second pair nested under `if (cmp1 == 0)`). */
extern int gl_func_00000000();
int gl_func_0000BEB8(int *s0) {
    char bufA[384];
    char bufB[8];
    char cmp[8];
    char bufC[384];
    char bufD[8];
    gl_func_00000000(s0, bufA, 8, 384);
    gl_func_00000000(s0, bufB, 392, 8);
    gl_func_00000000(cmp, bufA, 384, 0xDEADBBAD);
    if (gl_func_00000000(cmp, bufB) == 0) {
        gl_func_00000000(s0, bufC, 0x7DD8, 384);
        gl_func_00000000(s0, bufD, 0x7F58, 8);
        gl_func_00000000(cmp, bufC, 384, 0xDEADBBAD);
        if (gl_func_00000000(cmp, bufD) == 0) {
            return 0;
        }
        gl_func_00000000(s0, 8, bufC, 384);
        gl_func_00000000(s0, 392, bufD, 8);
    }
    return 1;
}

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

/* gl_func_0000C0EC: record-pair load/compare/store, sibling of gl_func_0000BC84
 * /BEB8 (same 0xDEADBBAD-sentinel structure; 96-byte records, keys 400/496 then
 * 0x7F60/0x7FC0). Fresh decode 2026-05-29 via the BC84 template. */
extern int gl_func_00000000();
int gl_func_0000C0EC(int *s0) {
    char bufA[96];
    char bufB[8];
    char cmp[8];
    char bufC[96];
    char bufD[8];
    gl_func_00000000(s0, bufA, 400, 96);
    gl_func_00000000(s0, bufB, 496, 8);
    gl_func_00000000(cmp, bufA, 96, 0xDEADBBAD);
    if (gl_func_00000000(cmp, bufB) == 0) {
        gl_func_00000000(s0, bufC, 0x7F60, 96);
        gl_func_00000000(s0, bufD, 0x7FC0, 8);
        gl_func_00000000(cmp, bufC, 96, 0xDEADBBAD);
        if (gl_func_00000000(cmp, bufD) == 0) {
            return 0;
        }
        gl_func_00000000(s0, 400, bufC, 96);
        gl_func_00000000(s0, 496, bufD, 8);
    }
    return 1;
}

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
/* gl_func_0000C28C: 16-byte record copy + header writes (0xEC, frame 0x38).
 * EXACT 59/59 (2026-10-14, agent-g). The 99.83 wrap's documented "t8 vs t9
 * skipped-temp uoptlist cap" (ugen pops one extra scratch between the 16-byte
 * move and the self->4 copy) was the copy's TYPE: self->4 = arg1->0 is a
 * 4-byte struct assignment, and eval_mov pops a data pair (t8,t9) and binds
 * pop #2 -- `lw t9,0(a1); sw t9,4(a0)` exactly. The 16-byte move keeps the
 * struct-assign + `&buf10`-in-a2 reuse for the first call
 * (docs/IDO_CODEGEN.md#feedback-ido-struct-copy-vs-field-copy-treg-order).
 * docs/IDO_CODEGEN.md#c49c-one-word-struct-move-skips-ring-slot */
typedef struct { int x; } C28C_W;
typedef struct { int pad0; C28C_W f4; } C28C_Self;
struct gl_func_0000C28C_Four { C28C_W a; int b, c, d; };
void gl_func_0000C28C(C28C_Self *arg0, struct gl_func_0000C28C_Four *arg1) {
    struct gl_func_0000C28C_Four buf10;
    int buf08[2];

    buf10 = *arg1;
    buf10.c = 0;

    arg0->f4 = arg1->a;
    gl_func_00000000(arg0, 0x218, &buf10, 0x10);
    if (gl_func_00000000(arg1) != 0) {
        gl_func_00000000(arg0, 0x230, arg1->c, arg1->b * 4);
    }

    gl_func_00000000(buf08, &buf10, 0x10, 0xDEADBBAD);
    gl_func_00000000(arg0, 0x228, buf08, 8);
    gl_func_00000000(arg0, 0x7FE8, &buf10, 0x10);
    gl_func_00000000(arg0, 0x7FF8, buf08, 8);
    gl_func_00000000(arg0);
}

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

/* gl_func_0000C49C: 21-insn 3-call wrapper. r = g(self); self->1 = r->0;
 * if (r->2) g(r->2, r); g(r). EXACT 21/21 (2026-10-14, agent-g). Two levers
 * over the 82.29 wrap: (1) the last call takes ONE argument -- the target
 * never writes a1 after the `or a1,v0` at the top, so r colours a1 for the
 * whole function (docs/IDO_CODEGEN.md#c8b8-param-in-a1-means-single-arg-call;
 * g(r, r) colours r a2 + copies, 23 words); (2) the copy self->1 = r->0 is a
 * 4-byte STRUCT assignment: its `lw t8,0(v0)` skips t7 (eval_mov pops a data
 * pair and uses pop #2), which a plain int copy (t6/t7) cannot reproduce.
 * docs/IDO_CODEGEN.md#c49c-one-word-struct-move-skips-ring-slot */
typedef struct { int x; } C49C_W;
typedef struct { int pad0; C49C_W f4; } C49C_Self;
typedef struct { C49C_W f0; int pad4; int f8; } C49C_Rec;
void gl_func_0000C49C(C49C_Self *a0) {
    C49C_Rec *r = (C49C_Rec *)gl_func_00000000(a0);
    a0->f4 = r->f0;
    if (r->f8 != 0) {
        gl_func_00000000(r->f8, r);
    }
    gl_func_00000000(r);
}

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
/* 2026-07-18 WORD-EXACT (35/35; was 86.1%): raw-word twin scan showed this
 * is 0-delta identical to gl_func_000088B4's 35 body words (88B4 has one
 * extra trailing nop delay word; C5B0's delay slot lives in the _pad.s).
 * 88B4 was cracked 2026-06-21 with the flat int* donor form (decl-order
 * p2,head,p1; p1-reuse-for-arg0; condition re-load -> two-web spill,
 * frame 0x28); the struct-typed body formerly here produced
 * frame 0x30. Ported verbatim. jal targets are USO placeholders ->
 * stays NM wrap, no episode. */
int *gl_func_0000C5B0(int *arg0) {
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

/* gl_func_0000C784: constructor, 77/77 BYTE-EXACT (2026-09-11 agent-g; was
 * NM 95.84 with three "not C-drivable" residuals, all three were spellings).
 * Allocs self (0xB8) if arg0 == NULL; cb(self, D+0xD678); self->0x28 = &D;
 * zeros 17 fields; allocs a 0x300 buffer into self->0x44 and zeros 8 records
 * of it in a 2-iteration stride-0x180 loop (self->0x44 re-read per store);
 * cb(self), cb(*(D+0x134), self), cb(self); returns self (NULL on alloc
 * failure). (1) `or s0,a0,zero; bnez a0; sw ra` head: the PARAM itself is
 * the s0 web (a `self = arg0` local puts the copy after `sw ra` and as1
 * fills the bnez delay with it); (2) the 0xD678 argument is
 * `(char *)&D_00000000 + 0xD678` -- the addend is baked into the lui/addiu
 * words (`extern char D_0000D678` gives blank hi/lo fields, the reloc-blind
 * gate's non-exception class); (3) the record loop is a for-init loop:
 * `v1 = 0; do {} while (v1 != 0x300)` emits the same words with
 * `or v1,zero,zero` scheduled before the hoisted `addiu v0,zero,768` (see
 * docs/IDO_CODEGEN.md #for-init-vs-dowhile-preheader-lui-addiu-adjacency-66d54).
 * Calls are jal 0x0 blanks (gl_func_00000000). */
extern int gl_func_00000000();
void *gl_func_0000C784(char *arg0) {
    int v1;

    if ((arg0 != 0) || (arg0 = (char *)gl_func_00000000(0xB8), (arg0 != 0))) {
        gl_func_00000000(arg0, (char *)&D_00000000 + 0xD678);
        *(char **)(arg0 + 0x28) = (char *)&D_00000000;
        *(int *)(arg0 + 0x4C) = 0;
        *(int *)(arg0 + 0xB4) = 0;
        *(int *)(arg0 + 0x5C) = 0;
        *(int *)(arg0 + 0x58) = 0;
        *(int *)(arg0 + 0x54) = 0;
        *(int *)(arg0 + 0x68) = 0;
        *(int *)(arg0 + 0x64) = 0;
        *(int *)(arg0 + 0x60) = 0;
        *(int *)(arg0 + 0x6C) = 0;
        *(int *)(arg0 + 0x70) = 0;
        *(int *)(arg0 + 0x8C) = 0;
        *(int *)(arg0 + 0x78) = 0;
        *(int *)(arg0 + 0x80) = 0;
        *(int *)(arg0 + 0x84) = 0;
        *(int *)(arg0 + 0x94) = 0;
        *(int *)(arg0 + 0x98) = 0;
        *(int *)(arg0 + 0x48) = 0;
        *(int *)(arg0 + 0x44) = gl_func_00000000(0x300);
        for (v1 = 0; v1 != 0x300; v1 += 0x180) {
            *(int *)(*(char **)(arg0 + 0x44) + v1) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 4) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0x60) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0x64) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0xC0) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0xC4) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0x120) = 0;
            *(int *)(*(char **)(arg0 + 0x44) + v1 + 0x124) = 0;
        }
        gl_func_00000000(arg0);
        gl_func_00000000(*(int *)((char *)&D_00000000 + 0x134), arg0);
        gl_func_00000000(arg0);
    }
    return arg0;
}

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_0000C8B8: entry-array reset + view setup. Zeroes the five 0x60
 * entries at self->0x44 (floats 0x08/0x0C/0x10/0x30, ints 0x14..0x28/0x34,
 * stage counters 0x38/0x3C/0x40 = 3), then 0x30 = 0, 0x34 = 600000,
 * 0xB0 = 1, copies the camera floats from (*(D + 0x134))->0x98 (+0xC4,
 * +0xCC, +0xD8 - 0x3C), notifies self and the optional child 0x6C, sets
 * (self->0x98)->0xC8 = 100 and 0x2C = 1.
 * Matching note: the first call takes ONE argument. Spelled
 * `gl_func_00000000(self, self)` (the old wrap) self colours a2 and both
 * calls get `or a1,a2` copies (+2 words, 32 diffs); with the single-arg
 * call self colours a1 from the entry and the second call's a1 is just
 * that colouring (the target never writes a1 before either jal). */
void gl_func_0000C8B8(char *self) {
    s32 i;
    char *p;

    for (i = 0; i != 0x300; i += 0x60) {
        *(f32 *)(FW(self, 0x44) + i + 0x8) = 0.0f;
        *(f32 *)(FW(self, 0x44) + i + 0xC) = 0.0f;
        *(f32 *)(FW(self, 0x44) + i + 0x10) = 0.0f;
        FW(FW(self, 0x44) + i, 0x18) = 0;
        FW(FW(self, 0x44) + i, 0x14) = 0;
        FW(FW(self, 0x44) + i, 0x1C) = 0;
        FW(FW(self, 0x44) + i, 0x20) = 0;
        FW(FW(self, 0x44) + i, 0x24) = 0;
        FW(FW(self, 0x44) + i, 0x28) = 0;
        *(f32 *)(FW(self, 0x44) + i + 0x30) = 0.0f;
        FW(FW(self, 0x44) + i, 0x34) = 0;
        FW(FW(self, 0x44) + i, 0x38) = 3;
        FW(FW(self, 0x44) + i, 0x3C) = 3;
        FW(FW(self, 0x44) + i, 0x40) = 3;
    }
    FW(self, 0x30) = 0;
    FW(self, 0x34) = 0x927C0;
    FW(self, 0xB0) = 1;
    *(f32 *)(self + 0x38) = *(f32 *)(FW(FW(&D_00000000, 0x134), 0x98) + 0xC4);
    *(f32 *)(self + 0x3C) = *(f32 *)(FW(FW(&D_00000000, 0x134), 0x98) + 0xCC);
    *(f32 *)(self + 0x40) = *(f32 *)(FW(FW(&D_00000000, 0x134), 0x98) + 0xD8) - *(f32 *)(self + 0x3C);
    gl_func_00000000(self);
    if (FW(self, 0x6C) != 0) {
        gl_func_00000000(FW(self, 0x6C), self);
    }
    p = (char *)FW(self, 0x98);
    if (p != 0) {
        FW(p, 0xC8) = 0x64;
    }
    FW(self, 0x2C) = 1;
}

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
void game_libs_func_0000CA30(char *arg0, s32 arg1, s32 arg2) {
    *(int*)(FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)) = arg1;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x4) = arg2;
    *(f32*)((char*)(FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)) + 0x10) = 0.0f;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x18) = 0;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x14) = 0;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x1C) = 0;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x20) = 0;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x24) = -1;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x28) = 0x32;
    *(f32*)((char*)(FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)) + 0x30) = 0.0f;
    FW((FW(arg0, 0x44) + (FW(arg0, 0x48) * 0x60)), 0x34) = 0;
    FW(arg0, 0x48) = (s32) (FW(arg0, 0x48) + 1);
}

/* Linear search: scan count (a0->0x48) elements (stride 0x60) at a0->0x44 for
 * one whose first field == a1; return that element, else 0. Merged: the loop-
 * back/not-found epilogue was splat-split off as game_libs_func_0000CB88
 * (UNSHARED); merged back (0x30 -> 0x44). BYTE-EXACT 2026-07-07: goto-to-shared
 * return-0 tail (not if-guard: that trips the -O2 unroller) gives the blezl +
 * dup-in-delay shape; decl-order i-before-count colors i=v0/count=v1; the dead
 * empty if (a1) {} is an emission-free priority boost that lets the key keep
 * its a1 home so the cursor colors a2 (no move a2,a1). */
void *game_libs_func_0000CB58(int *a0, int a1) {
    int i = 0;
    int count = a0[0x48 / 4];
    int *p;
    if (a1) {}
    if (count <= 0) goto end;
    p = (int*)a0[0x44 / 4];
    do {
        i++;
        if (*p == a1) {
            return p;
        }
        p = (int*)((char*)p + 0x60);
    } while (i < count);
end:
    return 0;
}

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
    int p;
    int n;

    if (a0[0x30 / 4] < a0[0x34 / 4]) {
        goto retzero;
    }
    p = a0[0x78 / 4];
    n = a0[0x34 / 4] - 8;
    if (p != 0) {
        a0[0x30 / 4] = n;
        gl_func_00000000(p, n);
    }
    return 1;
retzero:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CB9C);
#endif


#ifdef NON_MATCHING
/* game_libs_func_0000CBF0: per-record percentage scaler + four handler
 * dispatches, ONE function [0xCBF0,0xCD74) = 0xC + 0x178 -> 0x184 (97 words;
 * 2026-09-09, agent-g). The 3-word "game_libs_func_0000CBF0" (`lui a3; addiu
 * a3; lw t6,0x134(a3)`) was the hoisted held-base read of the registry chain
 * for the INCLUDE_ASM gl_func_0000CBFC body (agent-c's fake-param class,
 * docs/MATCHING_WORKFLOW.md#game-libs-fake-param-exact-sweep-agent-c). Sym
 * oracle (section = splat + 0x1466C): 0x2125C (0xCBF0) = export sym 1127
 * (DataReloc fn-table entry @0xD52C); 0x21268 (0xCBFC) not exported, no baked
 * jal. bootup.uso TextReloc: HI16/LO16 @+0x0/+0x4 -> sym272 (Data 0xF8, addend
 * 0; the same `&D + 0x134` chain the CB9C/CD.. neighbours use, held in a3 for
 * the pre-loop read and the per-iteration reload), four blank R_MIPS_26 at
 * +0x110/+0x130/+0x150/+0x16C -> sym916/894/910/927 (text 0x157A0/0x149A4/
 * 0x15510/0x15E58 = splat 0x1134/0x338/0xEA4/0x17EC) -> func_00000000.
 *
 * Decode: g = (*(D+0x134))->0x98 holds lo @0xCC / hi @0xD8 (floats); range =
 * hi - lo is computed once above the loop (sub.s in the blez delay slot);
 * for each of self->n (@0x48) stride-0x60 records off self->recs (@0x44),
 * gated per iteration on self->active (@0x2C): x = rec->0xC; pct @0x30 =
 * x < lo ? 0.0f : hi < x ? 100.0f : (x - lo) / range * 100.0f; the chain is
 * re-read every iteration (stores may alias), rec is re-indexed after the
 * pct store, and `rec->pct == 100.0f` bumps rec->0x34 (the bc1fl slot's `lw
 * v1,72(a2)` is nullified on the equal path, so the `lw t2,52(v1)` is the
 * RECORD, not self->n). Then if (self->0x70) f(self->0x70, (int)*self->0x74)
 * (trunc.w.s/mfc1), and three more (0x78/0x7C, 0x8C/0x90, 0x98/0x9C) with
 * int deref args; the next handler's load sits in each beqzl likely slot.
 *
 * Status: objdiff 97.78 (97/97 words, structure exact from the first
 * compile, 35 register-name words); the `else
 * { continue; }` arm is load-bearing -- a plain `if (self->active) { }` body
 * makes uopt re-load self->n on the inactive path too (`lw t5,72(a2)` in the
 * beqzl slot, `addiu a1` at the join) instead of keeping the guard's value in
 * v1 and reloading only after the stores (the target's PRE shape). Residual =
 * 35 colouring words, no structural diff: int G->v1/n,rec->v0 where the
 * target has G->v0 and n,rec->v1; held base ->t0 and the 96 stride ->a3
 * (target a3/t0); FP 100.0f->f12, 0.0f->f14, lo->f2, x-lo->f10, quotient
 * ->f18 where the target has lo->f12, 100.0f->f14, range->f16 (same), 0.0f
 * ->f18, x-lo->f2, quotient->f10. Inert: named lo/x locals, `100.0f == pct`,
 * dead while(0) refs on the chain, a named `g` chain local (same 35), a
 * named `reg` base (kills the held base: per-site lui, 55), raw-cast vs
 * struct-typed access, while/do-while/`self->n > i` loop spellings,
 * `* (100.0f / range)`. A pure v0/v1 + a3/t0 + FP-ring renumber knot
 * (docs/IDO_CODEGEN.md#feedback-ido-regalloc-renumber-matching-techniques);
 * the -zdbug:6 uoptlist dump needs the ecvt patch on this machine.
 *
 * 2026-10-14 agent-g: 35 -> 21 words. (1) Name the in-range difference
 * `d = rec->x - lo` (block-local assignment to a function-scope float): the
 * FP knot collapses to the target -- lo f12, x-lo f2, quotient f10, 100.0f
 * f14 -- leaving only range/0.0f as f18/f16; (2) the rotated `i = 0; if (i <
 * n) do { ... } while (++i < n);` loop (vs `for`) swaps range/0.0f to
 * f16/f18 AND the held base / stride to a3/t0 (target). RESIDUAL 21 words =
 * one pure v0<->v1 swap: the target colours the registry chain G (pre-loop
 * and per-iteration `lw v0,152(..)`) v0 and n / rec v1; ours G v1, n/rec
 * v0. Inert on top of this shape: void alias on all four handler calls
 * (E5D0 lever), named g (one web or two), named n, de-named rec (direct
 * self->recs[i] everywhere), `self->recs + i`, rec re-index before the ==
 * test, register rec, `if (self->n > 0)` guard, stmt order of i=0 / range,
 * same-line join, `active != 0`, extra dead decls. A dead `if (rec) {}`
 * breaks the shape (49). */
typedef struct {
    /* 0x00 */ char pad0[0xC];
    /* 0x0C */ float x;
    /* 0x10 */ char pad1[0x20];
    /* 0x30 */ float pct;
    /* 0x34 */ int hits;
    /* 0x38 */ char pad2[0x28];
} CBF0_Rec; /* 0x60 */
typedef struct {
    /* 0x00 */ char pad0[0x2C];
    /* 0x2C */ int active;
    /* 0x30 */ char pad1[0x14];
    /* 0x44 */ CBF0_Rec *recs;
    /* 0x48 */ int n;
    /* 0x4C */ char pad2[0x24];
    /* 0x70 */ int h0;
    /* 0x74 */ float *p0;
    /* 0x78 */ int h1;
    /* 0x7C */ int *p1;
    /* 0x80 */ char pad3[0xC];
    /* 0x8C */ int h2;
    /* 0x90 */ int *p2;
    /* 0x94 */ char pad4[4];
    /* 0x98 */ int h3;
    /* 0x9C */ int *p3;
} CBF0_Self;
#define CBF0_G (*(char **)(*(char **)((char *)&D_00000000 + 0x134) + 0x98))
#define CBF0_LO (*(float *)(CBF0_G + 0xCC))
#define CBF0_HI (*(float *)(CBF0_G + 0xD8))
extern int func_00000000();
void game_libs_func_0000CBF0(CBF0_Self *self) {
    int i;
    float range;
    float d;
    range = CBF0_HI - CBF0_LO;
    i = 0;
    if (i < self->n) do {
        if (self->active) {
            CBF0_Rec *rec = &self->recs[i];
            if (rec->x < CBF0_LO) rec->pct = 0.0f;
            else if (CBF0_HI < rec->x) rec->pct = 100.0f;
            else { d = rec->x - CBF0_LO; rec->pct = d / range * 100.0f; }
            if (self->recs[i].pct == 100.0f) self->recs[i].hits++;
        } else {
            continue;
        }
    } while (++i < self->n);
    if (self->h0) func_00000000(self->h0, (int)*self->p0);
    if (self->h1) func_00000000(self->h1, *self->p1);
    if (self->h2) func_00000000(self->h2, *self->p2);
    if (self->h3) func_00000000(self->h3, *self->p3);
}
#undef CBF0_G
#undef CBF0_LO
#undef CBF0_HI
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0000CBF0);
#endif

/* game_libs_func_0000CD74: three-threshold OR-gate, BYTE-EXACT 26/26
 * (2026-09-09, agent-g) as ONE no-argument function [0xCD74,0xCDDC):
 *   if (D_c758 > 0.0f || D_c75c > 0.0f || D_c760 > 0.0f) callback();
 * The old 3-word "game_libs_func_0000CD74" (`lui at; mtc1 zero,$f0; lwc1
 * $f4,0(at)`) was the hoisted head of the 59.8% "gl_func_0000CD80(float
 * a0, float a1)" wrap: IDO -O2 materialises the shared 0.0f operand and the
 * first global load above the addiu-sp prologue (agent-c's fake-param
 * class, docs/MATCHING_WORKFLOW.md#game-libs-fake-param-exact-sweep-agent-c).
 * Sym oracle (section = splat + 0x1466C): 0x213E0 (0xCD74) = export sym
 * 1126 with 1 R_MIPS_26 ref; 0x213EC (0xCD80) not exported. The "$f0/$f4
 * caller-arg, dual-entry, do NOT merge" verdict is retracted. bootup.uso
 * TextReloc: three DISTINCT Data symbols 858/859/860 = consecutive floats at
 * Data 0xC758/0xC75C/0xC760 (own hi/lo pair each -> three zero externs, not
 * one base + offsets); the jal is blank R_MIPS_26 to sym156 (text 0x4CCA8 =
 * splat 0x3863C). `x > 0.0f` gives the target `c.lt.s $f0,$f4` with the
 * single `mtc1 zero,$f0` CSE'd across all three compares; the third test
 * is bc1fl-to-epilogue with `lw ra` in the likely slot -- plain -O2 shape. */
extern float D_00000000_c758;
extern float D_00000000_c75c;
extern float D_00000000_c760;
extern int gl_func_00000000();
void game_libs_func_0000CD74(void) {
    if (D_00000000_c758 > 0.0f || D_00000000_c75c > 0.0f || D_00000000_c760 > 0.0f) {
        gl_func_00000000();
    }
}

/* gl_func_0000CDDC: 23-insn conditional vtable-dispatch + chain. If
 * *a1 == 9, load the sub-object p = *(a0 + 0x28), then call
 * (*p->[0x5C])(a0 + s16(p->[0x58])). Then always call gl_func(a0, a1).
 * The "lw v0,0x28(a0)" is the real sub-object deref (not a dummy):
 * the 0x58/0x5C accesses are off p, not off a0. */
int gl_func_0000CDDC(int *a0, int *a1) {
    int cmd = *a1;
    if (cmd == 9) {
        int *p = (int *)a0[0x28 / 4];
        int *new_a0 = (int*)((char*)a0 + *(short*)((char*)p + 0x58));
        (*(int(**)(int*))((char*)p + 0x5C))(new_a0);
    }
    return gl_func_00000000(a0, a1);
}

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_0000CE38: per-entry refresh over self->0x44 (count self->0x48,
 * stride 0x60). For each entry whose flags (+0x04) bit 0 is set, with the
 * manager m = self->0x4C non-NULL and its mode m->0x14:
 *   bit0 (entry +0x34 set): e->0x38 = f(m->0 + D.0x64*0x30, self->0x30),
 *        g(..., e->0x38, self->0x30, D.0x68 - 1)
 *   bit1 (entry +0x34 set): e->0x3C = f(m->0 + D.0x64*0x30, e->0x14), g(...)
 *   bit2: e->0x40 = f(m->4, e->0x14), g(m->4, e->0x40, e->0x14, a1, a2)
 * and each stage bumps D.0x7C to (value + 1) when value < 3.
 * Matching notes:
 * - the count is a local re-read only after the call groups (skip paths keep
 *   it in a3, `bnel`/`beqzl` delays increment i);
 * - `D.0x64 * 0x30 + base` order (product first) fixes the t-ring;
 * - the entry pointer is NEVER a named local (inline everywhere; a named
 *   cursor swaps v1/a0 at the loop head or t6/t8 in the bit2 call);
 * - the second call of each group returns nothing used: through the void
 *   alias gl_func_00000000_ce38_v (kills the dead $v0 def, docs
 *   IDO_CODEGEN #e5d0-void-alias-frees-v0-spilltemp-cap);
 * - `if (n) {}` (emission-free dead-if) lifts the constant-1 LR over the
 *   two pass-through params: s5 = 1, s6 = a1, s7 = a2 (without it 1 -> s7). */
extern void gl_func_00000000_ce38_v();
#define CE38_E(i) ((char *)FW(self, 0x44) + (i) * 0x60)
#define CE38_D(o) FW(&D_00000000, o)
void gl_func_0000CE38(char *self, s32 a1, s32 a2) {
    s32 i;
    char *m;
    s32 fl;
    s32 v;
    s32 n;

    n = FW(self, 0x48);
    if (n) {}
    for (i = 0; i < n; i++) {
        if ((FW(CE38_E(i), 0x4) & 1) == 1) {
            m = (char *)FW(self, 0x4C);
            if (m != 0) {
                fl = FW(m, 0x14);
                if (FW(CE38_E(i), 0x34) != 0) {
                    if (fl & 1) {
                        FW(CE38_E(i), 0x38) = gl_func_00000000(CE38_D(0x64) * 0x30 + FW(m, 0x0), FW(self, 0x30));
                        gl_func_00000000_ce38_v(CE38_D(0x64) * 0x30 + FW(FW(self, 0x4C), 0x0), FW(CE38_E(i), 0x38), FW(self, 0x30), CE38_D(0x68) - 1);
                        v = FW(CE38_E(i), 0x38);
                        if (v < 3) CE38_D(0x7C) = v + 1;
                        m = (char *)FW(self, 0x4C);
                        fl = FW(m, 0x14);
                    }
                    if (fl & 2) {
                        FW(CE38_E(i), 0x3C) = gl_func_00000000(CE38_D(0x64) * 0x30 + FW(m, 0x0), FW(CE38_E(i), 0x14));
                        gl_func_00000000_ce38_v(CE38_D(0x64) * 0x30 + FW(FW(self, 0x4C), 0x0), FW(CE38_E(i), 0x3C), FW(CE38_E(i), 0x14));
                        v = FW(CE38_E(i), 0x3C);
                        if (v < 3) CE38_D(0x7C) = v + 1;
                        m = (char *)FW(self, 0x4C);
                        fl = FW(m, 0x14);
                    }
                }
                if (fl & 4) {
                    FW(CE38_E(i), 0x40) = gl_func_00000000(FW(m, 0x4), FW(CE38_E(i), 0x14));
                    gl_func_00000000_ce38_v(FW(FW(self, 0x4C), 0x4), FW(CE38_E(i), 0x40), FW(CE38_E(i), 0x14), a1, a2);
                    v = FW(CE38_E(i), 0x40);
                    if (v < 3) CE38_D(0x7C) = v + 1;
                }
                n = FW(self, 0x48);
            }
        }
    }
}
#undef CE38_E
#undef CE38_D

void game_libs_func_0000D090(int *a0) {
    if (*(int *)(*(int *)((char *)a0 + 0x44) + 0x34) != 0) {
        if ((unsigned int)*(int *)((char *)&D_00000000 + 0x170) < (unsigned int)*(int *)((char *)&D_00000000 + 0x164) - 1) {
            *(int *)((char *)&D_00000000 + 0x184) = 1;
        }
    }
}

#ifdef NON_MATCHING
/* gl_func_0000D0D0 NM 78.59 -> 89.49 (2026-10-14 agent-g): per child (stride
 * 0x60) reset +0xC to -6553600.0f, then three lookups f(D, key, owner+0xDC, 0)
 * whose key is a 4-byte STRUCT PASSED BY VALUE (the `sw a1,4(sp)` before
 * each jal; docs/IDO_CODEGEN.md#struct-by-value-arg-carrier-7bc): the int at
 * D+0xD680/D684/D688 is stored into a struct local (sp 104/100/96) and the
 * by-value arg reloads it through the hoisted &local (s5..s7). Result 0 ->
 * +0x4C; results 1/2 -> +0x54/+0x58 ordered by (+0x64 - owner->0xE4). The old
 * body called through a gl_func_0000959C fn-ptr (jalr) without the struct.
 * RESIDUAL: the target re-materializes each key load per iteration
 * (`lui t9,1; lw t9,-0x2980(t9)`, destructive) while uopt here promotes the
 * key addresses (D_D0D0_D680/D684 -> s5/s7, using s8: +1 save, locals +4).
 * Not fixed by if(1) barriers (around loads, calls, store, step), per-site
 * pad-struct aliases, whole-struct global copies, volatile, literal
 * addresses (dli s5,0xd680) or block-scoped locals. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0000D0D0)();
typedef struct { int v; } S4_D0D0;
extern int D_D0D0_D680;
extern int D_D0D0_D684;
extern int D_D0D0_D688;
void gl_func_0000D0D0(char *arg0) {
    S4_D0D0 a;
    S4_D0D0 b;
    S4_D0D0 c;
    char *r1;
    char *r2;
    char *p;
    f32 base;
    s32 off;
    s32 i;

    off = 0;
    i = 0;
    if (FW(arg0, 0x48) > 0) {
        do {
            *(f32 *)(FW(arg0, 0x44) + off + 0xC) = -6553600.0f;
            if (1) { a.v = D_D0D0_D680; }
            FW(FW(arg0, 0x44), 0x4C) = gl_func_00000000(D_00000000, a, FW(FW(arg0, 0x44), 0x0) + 0xDC, 0);
            if (1) { b.v = D_D0D0_D684; }
            r1 = (char *)gl_func_00000000(D_00000000, b, FW(FW(arg0, 0x44), 0x0) + 0xDC, 0);
            if (1) { c.v = D_D0D0_D688; }
            r2 = (char *)gl_func_00000000(D_00000000, c, FW(FW(arg0, 0x44), 0x0) + 0xDC, 0);
            if (r1 == 0 || (r2 != 0) == 0) {
                FW(FW(arg0, 0x44) + off, 0x54) = 0;
            } else {
                p = (char *)FW(arg0, 0x44);
                base = *(f32 *)((char *)FW(p, 0x0) + 0xE4);
                if (*(f32 *)(r1 + 0x64) - base < *(f32 *)(r2 + 0x64) - base) {
                    FW(p + off, 0x54) = (int)r1;
                    FW(FW(arg0, 0x44) + off, 0x58) = (int)r2;
                } else {
                    FW(p + off, 0x54) = (int)r2;
                    FW(FW(arg0, 0x44) + off, 0x58) = (int)r1;
                }
            }
            i += 1;
            off += 0x60;
        } while (i < FW(arg0, 0x48));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D0D0);
#endif

#ifdef NON_MATCHING
/* gl_func_0000D288: 36-insn unlink-and-dispatch (0x90, frame 0x20).
 *   child = self->[0x44]->[0x4C]; if (!child) return;
 *   if (!(child->f64 <= self->[0x44]->fC)) return;      c.le.s f6,f4 + bc1fl
 *   self->[0x44]->[0x4C] = child->[0x84];                unlink
 *   if (call(child, *(char **)self->[0x44] + 0xB4))      blank jal
 *       vt = self->[0x28]; vt->fn64(self + vt->h60, child);   cfront vcall
 *
 * NM 72.69 -> 97.86 (2026-10-14 agent-g; 24/36 words, same 36-word shape).
 * Keys: (1) `self` is MEMORY-RESIDENT -- the target homes a0 in the
 * prologue (`sw a0,32(sp)`) and reloads self before the call (t7/t8 chain)
 * and after it; a dead `if (1) { int **bar = &self; }` makes it
 * address-taken without a frame word (block-scope bar), cf.
 * docs/IDO_CODEGEN.md#address-taken-iterator-locals-forwarded-ring-6337c.
 * (2) parent is NOT a named local: re-reading self->[0x44] per use (CSE'd
 * from the forwarded home) moves the child spill to 0x1C (target) from 0x18.
 * (3) named `next` gives the unlink value a candidate reg (target v0) and
 * re-aligns the ring (t7/t8 for the self reload). (4) `o = self` after the
 * call = the post-call self reload in v1 before the branch; the cfront
 * vcall `(o + vt->h)` computed before the `vt->fn` load reproduces the
 * lh t9 / addu / lw t9 / jalr / nop tail exactly.
 * RESIDUAL (registers only, 12 words): target colours next=v0, child=v1,
 * parent-CSE=a2 and reloads child post-call into a3 (in the beqz delay,
 * `or a1,a3`) -- i.e. child's live range is SPLIT at the call (pre v1 /
 * post a3). Build keeps child one web (a2 both sides, since o holds v1
 * post-call) -> parent-CSE v0, next v1. Probed inert: decl order (5
 * perms), register on each local, early-return vs nested ifs, copies
 * (`c2 = child` before/after the call), while(0) dead appearances (move
 * next to v0 but child stays a2), `&child` (child memory-resident: wrong).
 */
void gl_func_0000D288(int *self) {
    int *child;
    int *next;
    int *o;
    int rc;
    if (1) {
        int **bar = &self;
    }
    child = (int *)((int *)self[0x44 / 4])[0x4C / 4];
    if (child != 0) {
        if (*(float *)((char *)child + 0x64) <= *(float *)((char *)self[0x44 / 4] + 0xC)) {
            next = (int *)child[0x84 / 4];
            ((int *)self[0x44 / 4])[0x4C / 4] = (int)next;
            rc = gl_func_00000000(child, *(char **)self[0x44 / 4] + 0xB4);
            o = self;
            if (rc != 0) {
                int *vt = (int *)o[0x28 / 4];
                ((void (*)(int *, int *))vt[0x64 / 4])((int *)((char *)o + *(short *)((char *)vt + 0x60)), child);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D288);
#endif

/* gl_func_0000D318: 64-insn (0x100) conditional sub-object builder + color init.
 * Fresh hand-decode 2026-05-28 (raw-.word USO, m2c can't parse).
 *
 * Structure (asm 0xD318-0xD414):
 *   if (a0->0xB4 & 8) {
 *       obj = gl_func(a0->0x6C, a1->0x88, 0, 1);   // jal @0xD344
 *       obj->0xAC = 0.0f;
 *       gl_func(obj, 0xDC, 0x78, 1.0f, 1.0f);      // jal @0xD370, K&R float args
 *                                                  //   (4th arg 1.0f via mfc1->a3, 5th on stack)
 *       obj->0xA8 = 0.0f;  obj->0xA4 = 0.0f;       // color/param normalize (/255)
 *       obj->0x64 = 235.0f/255; obj->0x68 = 80.0f/255;
 *       obj->0x6C = 80.0f/255;  obj->0x70 = 0.0f/255;
 *       gl_func(0x17, a0->0xA0 / 1000);            // jal @0xD3D4
 *       a0->0xA0 += a1->0x88 * 1000;               // tail: *1000 via shift-add (t1*125<<3)
 *   }
 * div.s forced via named-local denom (else IDO folds 235.0/255.0 to lwc1-pool).
 * 96.17% as of 2026-05-28 (fresh decode: 0% -> 75% -> 92% -> 96%). Levers:
 *  (1) positive `if(cond){body}` + void return (not `if(!cond) return 0;`) ->
 *      direct `beqz t7, epilogue`, no separate `move v0,zero` block.
 *  (2) the 2nd call's two trailing floats must stay SINGLE -- a K&R call promotes
 *      them to double (cvt.d.s + sdc1, +8 frame). FIXED with the differently-named
 *      prototyped extern `gl_proto_D318` (resolves via R_MIPS_26 to the same jal-0
 *      target) -> direct `jal` + single floats, per
 *      docs/IDO_CODEGEN.md#feedback-ido-knr-float-call. (A function-pointer cast
 *      also keeps singles but emits indirect `jalr t9`; the named-proto avoids that.)
 * 2026-09-11 (agent-g): EXACT 64/64. The "0.0f in THREE FP regs, not
 * C-forceable" residual was the same-literal CSE: with every zero spelled
 * `0.0f`, uopt makes ONE 4-use candidate ($f12) that spans the call (pre-call
 * store, 0/255 numerator, two post-call stores) and the ring renumbers. The
 * target has two zero PSEUDOS in the post-call block: the two-use store zero
 * (candidate $f12) and the one-use numerator (ring $f16). Spelling the
 * numerator as the CAST form `(float)0 / denom` (distinct pseudo from the
 * `0.0f` literal, docs/IDO_CODEGEN.md
 * #game-libs-64124-distinct-f4-zero-via-cast-2026-07-03) splits them; the
 * pre-call `obj->0xAC = 0.0f` then stays a one-use ring temp ($f4) on its own
 * (any spelling). Swapping which side is the literal also works; `0.0` as the
 * numerator promotes the div to double. The int tail `a0->0xA0 += ...*1000`
 * must be the COMPOUND assignment: `x = x + p` emits the product first in the
 * addu (t1+t2) and renumbers t9/t0; `+=` gives the target's base-first
 * `addu t3,t9,t2` with the a1 reload in t0. */
extern int gl_func_00000000();
/* Differently-named prototyped extern: resolves via R_MIPS_26 to the SAME jal-0
 * target as gl_func_00000000, but lets the trailing float args stay SINGLE with a
 * DIRECT `jal` -- avoids both K&R float->double promotion AND the fn-ptr-cast
 * `jalr $t9`. Per docs/IDO_CODEGEN.md#feedback-ido-knr-float-call verified workaround. */
extern int gl_proto_D318(void*, int, int, float, float);
void gl_func_0000D318(int *a0, int *a1) {
    int *obj;
    float denom;

    if (a0[0xB4 / 4] & 8) {
        obj = (int*)gl_func_00000000(a0[0x6C / 4], a1[0x88 / 4], 0, 1);
        *(float*)((char*)obj + 0xAC) = 0.0f;
        gl_proto_D318(obj, 0xDC, 0x78, 1.0f, 1.0f);
        denom = 255.0f;
        *(float*)((char*)obj + 0xA8) = 0.0f;
        *(float*)((char*)obj + 0xA4) = 0.0f;
        *(float*)((char*)obj + 0x64) = 235.0f / denom;
        *(float*)((char*)obj + 0x68) = 80.0f / denom;
        *(float*)((char*)obj + 0x6C) = 80.0f / denom;
        *(float*)((char*)obj + 0x70) = (float)0 / denom;
        gl_func_00000000(0x17, a0[0xA0 / 4] / 1000);
        a0[0xA0 / 4] += a1[0x88 / 4] * 1000;
    }
}

extern int gl_func_00000000();
void gl_func_0000D418(int *arg0) {
    int *e;
    int *mgr = (int *)arg0[0x44 / 4];
    int *cur = (int *)mgr[0x54 / 4];
    int *tmp;
    int *alt;
    float f0;
    e = arg0;
    arg0 = 0;
    if (cur == 0) return;
    f0 = *(float *)((char *)mgr + 0xC);
    if (!(*(float *)((char *)cur + 0x64) <= f0)) return;
    {
        alt = (int *)cur[0x84 / 4];
        tmp = cur;
        if (alt == 0) {
            cur = (int *)mgr[0x58 / 4];
            if (cur == 0) {
                mgr[0x54 / 4] = 0;
            } else {
                mgr[0x54 / 4] = (int)cur;
                ((int *)e[0x44 / 4])[0x58 / 4] = 0;
            }
        } else {
            cur = (int *)mgr[0x58 / 4];
            if ((*(float *)((char *)alt + 0x64) - f0) < (*(float *)((char *)cur + 0x64) - f0)) {
                mgr[0x54 / 4] = (int)alt;
            } else {
                mgr[0x54 / 4] = (int)cur;
                ((int *)e[0x44 / 4])[0x58 / 4] = (int)alt;
            }
        }
    }
    if (tmp) {}
    if (tmp[0xC8 / 4] & 1) {
        if (*(float *)((char *)e[0x44 / 4] + 8) <= *(float *)((char *)tmp + 0x5C)) {
            gl_func_00000000((int *)((int)e | (int)arg0), tmp, e);
            return;
        }
        gl_func_00000000((int *)((int)e | (int)arg0), tmp, e);
        return;
    }
    if (*(float *)((char *)tmp + 0x5C) <= *(float *)((char *)e[0x44 / 4] + 8)) {
        gl_func_00000000((int *)((int)e | (int)arg0), tmp, e);
        return;
    }
    gl_func_00000000((int *)((int)e | (int)arg0), tmp, e);
}

/* === EXACT MATCH 76/76 (in-tree, clean rebuild x2, 2026-07-03 agent-e) ===
 * Was 94.5% "entity-ptr-in-$a2 cap, not C-reachable" -- FALSE: fully C-reachable.
 * FOUR coupled levers (all zero-emission):
 * 1. MULTI-DEF cur: reuse `cur` for the next-node load in both arms (cur = mgr[0x16])
 *    -- the redefinition blocks copyprop, so `tmp = cur` (defined BEFORE the alt
 *    load's use of cur) survives as a separate web -> or a1,v0 emitted; tmp carries
 *    the dispatch arg (colors a1 via arg-2 slot), cur stays v0, mgr v1.
 * 2. dead `if (tmp) {}` AFTER the arms' join (before the 0xC8 test): boosts tmp's
 *    priority above alt -> tmp=a1, alt falls to a0 (same lever as A7B4).
 * 3. e-SPLIT of the param: `e = arg0; arg0 = 0;` -- entry mgr load stays on a0
 *    (lw v1,0x44(a0)), all later uses via e; the dead kill blocks copyprop from
 *    re-merging e into the param web (kill itself const-propped away, 0 insns).
 * 4. arg1 as an EXPRESSION: cb((int *)((int)e | (int)arg0), tmp, e) with arg0==0
 *    known -- keeps position-1 an op node so the a2-slot copy becomes e's death
 *    point -> e coalesces into $a2 (or a2,a0 emitted as entry reglod); the |-with-
 *    known-zero folds to the exact `or a0,a2` per-call copy. Plain `cb(e,tmp,e)`
 *    leaves e's last use at the a0-slot -> a2 forbidden -> e lands a3 (+4 words).
 * Callees left as the standard gl_func_00000000 placeholder (jal 0). */

/* gl_func_0000D548: sub-object spawn pair (sibling of D6E8 / D9E4). EXACT 86/86
 * (2026-10-14 agent-g). Levers:
 * - The a4 bump is written on the FIELD with the call arg re-read from it:
 *   `if (o->a4 < 500) o->a4 += 100; g(o->6c, o->a4, 0, 1)`. uopt forwards the
 *   field into a1 on both paths, so the then-path value lands in a ring temp
 *   (addiu t1; sw t1; or a1,t1). Every local-variable spelling (n += 100 /
 *   a1 = o->a4 = n + 100 / temp copy) either drops the move or colours the sum v0.
 * - FP: three named numerators r/g/b const-propagated (runtime div.s per D6E8);
 *   b is REUSED for the 255.0 DOUBLE-literal numerator and the trailing 0.0,
 *   r for 80. g/255 is NOT named: the second object's 0x64 store re-divides
 *   g, which uopt CSEs across the call into the 0x2C spill temp. Four named
 *   locals = the target frame 0x40 (a fifth name, or a named quotient, adds
 *   8 bytes and moves the spill homes).
 * - The 0xAC zero store goes AFTER the 0xA0 store (the scheduler then places
 *   it between the lw and addiu, as the target does).
 * - The h() call needs a prototyped (int*, int, int, float, float) blank
 *   alias: a3 = mfc1 1.0f, 5th arg swc1 at 0x10(sp). */
extern void gl_func_00000000_d548f(int *, int, int, float, float);
void gl_func_0000D548(int *o, int a1) {
    int *obj;
    float r, g, b;
    if (o[0x6C / 4] == 0 || (o[0xB4 / 4] & 4) == 0) return;
    gl_func_00000000(0x2C);
    o[0xA0 / 4] += 2000;
    if (o[0xA4 / 4] < 500) {
        o[0xA4 / 4] += 100;
    }
    obj = (int *)gl_func_00000000(o[0x6C / 4], o[0xA4 / 4], 0, 1);
    r = 100.0f;
    g = 235.0f;
    b = 250.0f;
    *(float *)((char *)obj + 0x64) = r / 255.0f;
    *(float *)((char *)obj + 0x68) = g / 255.0f;
    *(float *)((char *)obj + 0x6C) = b / 255.0f;
    b = 255.0;
    *(float *)((char *)obj + 0x70) = b / 255.0f;
    *(int *)((char *)obj + 0xA0) = o[0x6C / 4] + 0x150;
    *(float *)((char *)obj + 0xAC) = 0.0f;
    gl_func_00000000_d548f(obj, 100, 0x86, 1.0f, 1.0f);
    *(float *)((char *)obj + 0xA8) = 0.0f;
    *(float *)((char *)obj + 0xA4) = 0.0f;
    obj = (int *)gl_func_00000000(o[0x6C / 4], 2, 0, 1);
    r = 80.0f;
    b = 0.0f;
    *(float *)((char *)obj + 0x64) = g / 255.0f;
    *(float *)((char *)obj + 0x68) = r / 255.0f;
    *(float *)((char *)obj + 0x6C) = r / 255.0f;
    *(float *)((char *)obj + 0x70) = b / 255.0f;
}

extern int gl_func_00000000();

void gl_func_0000D6A0(char *a0, int a1) {
    if ((*(int*)(a0 + 0xB4) & 4) != 0) {
        gl_func_00000000(0x2F, a0);
        *(int*)(a0 + 0xA4) = 0;
    }
}

/* gl_func_0000D6E8: build+init a sub-object (cb(node, a1, 0, 1) -> obj,
 * then obj->f44 += 70, f5C = 70, fA4/A8/AC = 0, colour f64..f70 =
 * {250,219,68,255}/255, i9C = 30, iA0 = o->6C + 0x138). EXACT 52/52
 * (2026-10-14 agent-g; was NM 78.5).
 * Keys: (1) the four colour components are NAMED float locals (r,g,b,a)
 * declared FIRST: their dead -O2 homes are the 4 frame words 0x20..0x2C
 * (frame 0x30, node spill 0x1C), and uopt const-propagates them into
 * runtime div.s (cfe only folds literal/literal). (2) `a = 255.0;` -- a
 * DOUBLE literal -- gives the numerator its own 255.0f materialization
 * (lui 0x437F/mtc1 f8); `a = 255.0f` CSEs it with the divisor
 * (div.s f8,f0,f0, -2 words). (3) one `||` early-out keeps the ring at
 * t8/t9 (two ifs burn a slot). (4) the 0xA0 store is written BEFORE the
 * 0x9C = 30 store so the constant takes ring t3 after the o->6C reload.
 * docs/IDO_CODEGEN.md#double-literal-defeats-fp-const-cse-d6e8 */
extern int gl_func_00000000();
void gl_func_0000D6E8(int *o, int a1) {
    float r, g, b, a;
    int node = o[0x6C / 4];
    int *obj;
    if (node == 0 || (o[0xB4 / 4] & 2) == 0) return;
    obj = (int *)gl_func_00000000(node, a1, 0, 1);
    r = 250.0f;
    g = 219.0f;
    b = 68.0f;
    a = 255.0;
    *(float *)((char *)obj + 0x44) += 70.0f;
    *(float *)((char *)obj + 0x5C) = 70.0f;
    *(float *)((char *)obj + 0xA4) = 0.0f;
    *(float *)((char *)obj + 0xA8) = 0.0f;
    *(float *)((char *)obj + 0xAC) = 0.0f;
    *(float *)((char *)obj + 0x64) = r / 255.0f;
    *(float *)((char *)obj + 0x68) = g / 255.0f;
    *(float *)((char *)obj + 0x6C) = b / 255.0f;
    *(float *)((char *)obj + 0x70) = a / 255.0f;
    *(int *)((char *)obj + 0xA0) = o[0x6C / 4] + 0x138;
    *(int *)((char *)obj + 0x9C) = 30;
}

/* gl_func_0000D7B8: gated initializer. Guarded by arg0->0x6C != 0 && (arg0->0xB4
 * & 2): calls cb(0x27, arg1+arg2), then cb2(arg0->0x6C, arg1, 0, 1) -> v0; writes
 * float fields (70.0f, three 0.0f, and the 250/235/100/255-over-255 ratios via
 * runtime div.s, variable divisor `float denom = 255.0f`), arg0->0x6C+0x108 then
 * int 14, calls cb3(v0, 1.0f, 1.0f) (single-float args via the gl_proto_d7b8 typed
 * alias, pinned to 0 in undefined_syms_auto.txt), sets v0->0x78=255. Then a
 * second gate arg0->0x6C != 0 && (arg0->0xB4 & 1) calls cb(arg0->0x6C).
 * BYTE-EXACT 74/74 (2026-09-11). The 89.9% residuals were three separate levers:
 * (1) the 255/255 numerator is the CAST class `(float)255` (distinct pseudo from
 * the `255.0f` denom, own lui/mtc1 in ring $f6 -- D318/D8E0 lever); (2) the v0
 * spill slot (target 0x24, was 0x20) is declaration order -- `v0` declared FIRST
 * (`char *v0; int a3; float denom;`), the named-scalar-home interleave of
 * docs/IDO_CODEGEN.md#named-scalar-homes-interleave-declaration-order-65060;
 * (3) the `= 14` store is SUNK into the `lw t9,0x6C(s0)` load-delay slot with
 * t1/t9/t0 numbering only when it is written AFTER the 0xA0 = a0->0x6C + 0x108
 * store (source order = ring order; the scheduler then hoists the `addiu t1,14`). */
extern int gl_func_00000000();
extern int gl_proto_d7b8(void *, float, float);
void gl_func_0000D7B8(char *arg0, int arg1, int arg2) {
    char *v0;
    int a3;
    float denom;

    a3 = *(int *)(arg0 + 0x6C);
    if ((a3 != 0) && (*(int *)(arg0 + 0xB4) & 2)) {
        gl_func_00000000(0x27, arg1 + arg2);
        v0 = (char *)gl_func_00000000(*(int *)(arg0 + 0x6C), arg1, 0, 1);
        denom = 255.0f;
        *(float *)(v0 + 0x5C) = 70.0f;
        *(float *)(v0 + 0xA4) = 0.0f;
        *(float *)(v0 + 0xA8) = 0.0f;
        *(float *)(v0 + 0xAC) = 0.0f;
        *(float *)(v0 + 0x64) = 250.0f / denom;
        *(float *)(v0 + 0x68) = 235.0f / denom;
        *(float *)(v0 + 0x6C) = 100.0f / denom;
        *(float *)(v0 + 0x70) = (float)255 / denom;
        *(int *)(v0 + 0xA0) = *(int *)(arg0 + 0x6C) + 0x108;
        *(int *)(v0 + 0x9C) = 14;
        gl_proto_d7b8(v0, 1.0f, 1.0f);
        *(int *)(v0 + 0x78) = 255;
        a3 = *(int *)(arg0 + 0x6C);
    }
    if ((a3 != 0) && (*(int *)(arg0 + 0xB4) & 1)) {
        gl_func_00000000(a3);
    }
}

/* gl_func_0000D8E0: simpler 2-arg sibling of gl_func_0000D7B8. Gated by arg0->0x6C
 * != 0 && (arg0->0xB4 & 2): cb(0x22), cb2(arg0->0x6C, arg1, 0, 0) -> v0; writes
 * 70.0f + the four x/255 color ratios (250/235/100/255-over-255) via runtime div.s
 * (variable divisor `float denom=255.0f`). Trailing gate arg0->0x6C != 0 &&
 * (arg0->0xB4 & 1) calls cb(arg0->0x6C). BYTE-EXACT 54/54 (2026-09-11): the old
 * "255/255 numerator-CSE cap" (target loads 255.0 twice, f6 numerator + f0 denom;
 * IDO CSEd `255.0f / denom` to div.s f6,f0,f0) is the same-literal value-numbering
 * of docs/IDO_CODEGEN.md#two-zero-pseudos-literal-vs-cast-compound-tail-d318 --
 * the numerator spelled as the CAST class `(float)255` is a distinct pseudo from
 * the `255.0f` literal denom, so it gets its own lui/mtc1 (ring $f6). */
extern int gl_func_00000000();
void gl_func_0000D8E0(char *arg0, int arg1) {
    int a2;
    char *v0;
    float denom;

    a2 = *(int *)(arg0 + 0x6C);
    if ((a2 != 0) && (*(int *)(arg0 + 0xB4) & 2)) {
        gl_func_00000000(0x22);
        v0 = (char *)gl_func_00000000(*(int *)(arg0 + 0x6C), arg1, 0, 0);
        denom = 255.0f;
        *(float *)(v0 + 0x5C) = 70.0f;
        *(float *)(v0 + 0x64) = 250.0f / denom;
        *(float *)(v0 + 0x68) = 235.0f / denom;
        *(float *)(v0 + 0x6C) = 100.0f / denom;
        *(float *)(v0 + 0x70) = (float)255 / denom;
        a2 = *(int *)(arg0 + 0x6C);
    }
    if ((a2 != 0) && (*(int *)(arg0 + 0xB4) & 1)) {
        gl_func_00000000(a2);
    }
}

/* gl_func_0000D9B8: CRACKED 2026-06-11 (wave 2, 100.0; was "no C-reachable
 * fix" 98.64 a1-vs-a3 rename cap). The $a3 temp means $a1/$a2 are LIVE at
 * the load: the original is a 3-arg fn passing a1/a2 THROUGH to the callee
 * (`gl(p, a1, a2)`). Pass-through args occupy a1/a2 (no unused-arg spills,
 * unlike unused named params) -> p colors a3. Recognition: a mid-arg-reg
 * temp ($a3) in a tiny wrapper = hidden pass-through arity. */
extern int gl_func_00000000();
void gl_func_0000D9B8(int *a0, int a1, int a2) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p, a1, a2);
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
extern void gl_func_00000000_d9e4b(int *, int, int, float, float);
void gl_func_0000D9E4(int *a0, int a1) {
    int *v0;
    int *sub;
    f32 num100;
    f32 num235;
    f32 num255;

    sub = (int *)a0[0x6C / 4];
    if ((sub != 0) && (a0[0xB4 / 4] & 2) && (*(int **)((char *)&D_00000000 + 0x64) != 0)) {
        v0 = (int *)gl_func_00000000(sub, (int)((float)a1 / 1000.0f * 100.0f), 0, 1);
        v0[0x9C / 4] = 230;
        v0[0x7C / 4] = 0;
        *(float *)((char *)v0 + 0xAC) = 0.0f;
        gl_func_00000000_d9e4b(v0, 160, 140, 1.0f, 1.0f);
        *(float *)((char *)v0 + 0xA8) = 0.0f;
        *(float *)((char *)v0 + 0xA4) = 0.0f;
        num100 = 100.0f;
        num235 = 235.0f;
        num255 = (float)255;
        *(float *)((char *)v0 + 0x64) = num100 / 255.0f;
        *(float *)((char *)v0 + 0x6C) = num100 / 255.0f;
        *(float *)((char *)v0 + 0x68) = num235 / 255.0f;
        *(float *)((char *)v0 + 0x70) = num255 / 255.0f;
        v0[0xA0 / 4] = (int)((char *)a0[0x6C / 4] + 0x120);
    }
    sub = (int *)a0[0x6C / 4];
    if (sub != 0) {
        if (a0[0xB4 / 4] & 1) {
            gl_func_00000000(sub);
        }
    }
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

/* gl_func_0000DB80: paired vtable dispatch with a mode gate, BYTE-EXACT 68/68
 * (2026-10-14 agent-g). Same entry/method shape as the matched twins DC90 /
 * DD44 below: entry = self->0x44[idx*0x60]; q = entry->0x28; method q->0x2C
 * called with ((short)q->0x28 + entry, &msgcode). First the own entry with
 * msgcode 1000; then, if self->0x48 == 2, the partner entry (idx^1) with
 * msgcode 1001 when the global mode (&D + 0x34) is 3 or 2, else 1000.
 * Match keys (the 86.5% wrap had the decode right):
 *  - frame 0x50 slots l0@0x44 / l1@0x2C / l2@0x20: l0 is function-scope
 *    between pad_a[2] and pad_b[2]; l1/l2 are BLOCK-scope (each arm), padded
 *    by pad_c[2] / pad_d[1]; one more block int (pad_m) in the outer if.
 *  - mode read twice inline, NOT a named local: a named `m` makes the second
 *    compare `bne v0,v1` (target `bne v1,v0` against the shared 2 constant).
 *  - the empty `if (v0) {}` after the FIRST arm's q load flips the
 *    entry/q colouring of all three dispatches to v1/v0 (DC90/DD44 nudge; on
 *    the else arm or on the first dispatch it is inert or worse). */
void gl_func_0000DB80(char *self, int idx) {
    int pad_a[2]; int l0 = 1000; int pad_b[2];
    char *v1, *v0;
    v1 = *(char **)(*(char **)(self + 0x44) + idx * 0x60);
    v0 = *(char **)(v1 + 0x28);
    (*(void (**)(char *, int *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &l0);
    if (*(int *)(self + 0x48) == 2) {
        int pad_m;
        if (*(int *)((char *)&D_00000000 + 0x34) == 3 || *(int *)((char *)&D_00000000 + 0x34) == 2) {
            int l1 = 1001; int pad_c[2];
            v1 = *(char **)(*(char **)(self + 0x44) + (idx ^ 1) * 0x60);
            v0 = *(char **)(v1 + 0x28);
            if (v0) {}
            (*(void (**)(char *, int *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &l1);
        } else {
            int l2 = 1000; int pad_d[1];
            v1 = *(char **)(*(char **)(self + 0x44) + (idx ^ 1) * 0x60);
            v0 = *(char **)(v1 + 0x28);
            (*(void (**)(char *, int *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &l2);
        }
    }
}

/* gl_func_0000DC90: vtable-dispatch on indexed 96-byte entry + pair-toggle (0xB4, frame 0x40).
 * MATCHED (2026-07-14, decomp-permuter --stack-diffs): decl order pins the two
 * by-ref locals in the -0x40 frame. sp34 (msgcode 1001) is declared early to
 * seat at 0x34; sp1C (msgcode 1000) sits between the v0/v1 pointer decls so IDO
 * packs it at 0x1C. pad_a/pad_b/pad_c and the empty `if (v0){}` regalloc nudge
 * were carried over from the twin gl_func_0000DD44; the sp1C decl-slot move was
 * the last-2-word residual the permuter's decl-reorder pass cracked.
 *
 * self->unk44 = base of idx*0x60 entry array; entry[0] -> obj; obj->unk28 ->
 * vtable; (short)vtable->unk28 = ptr adjust; vtable->unk2C = method. Calls
 * method((char*)obj + adj, &msgcode, self) with msgcode 1001, then if
 * self->unk48 == 2 the partner entry (idx^1) with msgcode 1000.
 */
void gl_func_0000DC90(char *self, int idx) {
    int pad_a[2]; int sp34 = 1001; int pad_b[3]; int pad_c[1];
    char *v0; int sp1C; char *v1;
    v1 = *(char **)(*(char **)(self + 0x44) + idx * 0x60);
    v0 = *(char **)(v1 + 0x28);
    (*(void (**)(char *, int *, char *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &sp34, self);
    if (*(int *)(self + 0x48) == 2) {
        sp1C = 1000;
        v1 = *(char **)(*(char **)(self + 0x44) + (idx ^ 1) * 0x60);
        v0 = *(char **)(v1 + 0x28);
        if (v0) {}
        (*(void (**)(char *, int *, char *))(v0 + 0x2C))((char *)((int)*(short *)(v0 + 0x28) + (int)v1), &sp1C, self);
    }
}

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

/* gl_func_0000E05C: 47-insn 2-gate + flag-driven dispatch + vtable tail (0xBC, frame 0x28).
 *
 *   v0 = func1(self); if (v0 == NULL) return; if ((v0->[0x4] & 1) == 0) return;
 *   a2_var = -1;
 *   if (self->[0xB4] & 0x10) a2_var = func2(D_sym, a2);
 *   if (self->[0xB4] & 0x1) { r1 = func3(D_sym, a2); func4(self, r1, a2_var); func5(0x24, a2); }
 *   vt = self->[0x28]; (vt->[0x6C])((char*)self + (s16)vt->[0x68], a2);
 *
 * BYTE-EXACT 47/47 (2026-09-11 agent-g), from the 96.91% wrap. Three levers:
 *  1. The old decode had func5(0x24, a2) UNCONDITIONAL; the target's `beqz t9,+0x90`
 *     skips it, so it is the third call INSIDE the flags&1 block. Fixing this alone
 *     also removed the "vt in v1 vs v0" residual (control-flow, not colouring).
 *  2. a1 is an unreferenced param: IDO homes it (`sw a1,0x2C(sp)`, +1 word). The
 *     emission-free dead `if (a1) {}` (E118 lever) removes the home ONLY when it is
 *     the first STATEMENT before the lookup call -- with `int *v0 = func1(self);`
 *     as a declaration initializer the ref comes after the call and the home stays.
 *     So v0 is assigned as a statement and `a2_var = -1` is set AFTER the call
 *     (setting it before the call materialises -1 pre-jal and spills it, +1).
 *  3. Vtable tail in the CDDC form (named `new_a0` pointer local, fn-ptr deref
 *     inline) gives the ring t9/t0 + `addu a0,t0,s0`; named fn/off locals colour
 *     a2/a3 and flip the addu. */
void gl_func_0000E05C(int *self, int a1, int a2) {
    int *v0;
    int a2_var;
    int *vt;
    int *new_a0;
    if (a1) {}
    v0 = (int*)gl_func_00000000(self);
    a2_var = -1;
    if (v0 == 0) return;
    if ((v0[1] & 1) == 0) return;
    if (self[0xB4 / 4] & 0x10) {
        a2_var = (int)gl_func_00000000(*(int*)&D_00000000, a2);
    }
    if (self[0xB4 / 4] & 0x1) {
        int r1 = (int)gl_func_00000000(*(int*)&D_00000000, a2);
        gl_func_00000000(self, r1, a2_var);
        gl_func_00000000(0x24, a2);
    }
    vt = (int*)self[0x28 / 4];
    new_a0 = (int*)((char*)self + *(short*)((char*)vt + 0x68));
    (*(int(**)(int*, int))((char*)vt + 0x6C))(new_a0, a2);
}

/* gl_func_0000E118 — 49/49 EXACT (2026-07-03, agent-e w4).
 * Was documented "cap: IDO spuriously homes the UNUSED a1 placeholder param
 * (sw a1,0x2C); can't be suppressed". CRACKED with two levers:
 *  1. UNREFERENCED-param homing rule: IDO homes a param that has NO
 *     references in the body (ugen's home store survives because uopt never
 *     builds a web for it). `register` does NOT help. An emission-free
 *     reference — dead `if (a1) {}` as the first statement — gives a1 a web
 *     and the home store disappears (0 insns emitted, 49->48).
 *  2. Store duplication is source-level, not a scheduler artifact: the target
 *     duplicates `v->0x24 = 0` into BOTH arms of the a2!=0 if/else (then-arm
 *     copy lands in the `b` delay slot; else-arm copy stays inline) while
 *     `v->0x1C = 0` is shared after the join. Writing both stores after the
 *     join emits the shared-tail form (1 insn short). Move the 0x24 store
 *     into each arm.
 */
extern int gl_func_00000000();
void gl_func_0000E118(int a0, int a1, int a2, int a3) {
    int v0;
    if (a1) {}
    v0 = gl_func_00000000();
    if (v0 != 0 && (*(int *)(v0 + 4) & 1)) {
        if ((*(int *)(a0 + 0xB4) & 2) && *(int *)(v0 + 0x24) == 1) {
            if (a2 != 0) {
                gl_func_00000000(a0, *(int *)(v0 + 0x1C), a3);
                *(int *)(v0 + 0x24) = 0;
            } else {
                gl_func_00000000(a0, *(int *)(v0 + 0x1C));
                *(int *)(v0 + 0x24) = 0;
            }
            *(int *)(v0 + 0x1C) = 0;
        }
        {
            int t = *(int *)(a0 + 0x28);
            (*(void (**)(int, int))(t + 0x74))(*(short *)(t + 0x70) + a0, a2);
        }
    }
}

void gl_func_0000E1DC(int *a0, int a1, int a2) {
    int *v = (int*)gl_func_00000000(a0, a1, a2);
    if (v == 0) return;
    if (!(v[1] & 1)) return;
    if (!(a0[0xB4 / 4] & 2)) return;
    gl_func_00000000(a0, a2);
}

/* gl_func_0000E230: BYTE-EXACT (2026-05-30). 29-insn count-loop calling func
 * per element: for each i (0..a0->0x48), call func(a0, *(a0->0x44 + i*0x60), 1, 0).
 * Was a documented 98.45% s1/s2 reg-swap cap (a0 vs offset swapped). CRACKED via
 * the UCODE-encounter-order lever: the target's `blez` guard reads a0->0x48 and
 * sets offset=0 in the delay slot, so a0 is ENCOUNTERED BEFORE offset → a0=$s1,
 * offset=$s2. The old plain-`while` form put `offset=0` before the first a0 ref,
 * so offset grabbed $s1. Rewriting as `if (a0->0x48 > 0) { offset=0; do{...} }`
 * (guard references a0 first) flips the coloring to match. See
 * docs/IDO_CODEGEN.md "Promoted loop-invariants ... UCODE-encounter order". */
extern int func_00000000();
void gl_func_0000E230(int *a0) {
    int i = 0;
    if (a0[0x48/4] > 0) {
        int offset = 0;
        do {
            func_00000000(a0, *(int*)((char*)a0[0x44/4] + offset), 1, 0);
            i++;
            offset += 0x60;
        } while (i < a0[0x48/4]);
    }
}

/* gl_func_0000E2A4: destructor — conditionally release 8 sub-objects of `o`.
 * For each of fields 0x6C, 0x70, 0x8C, 0x78, 0x80, 0x84, 0x94, 0x98: if
 * non-null, cb(field). MATCHED 2026-05-29 (fresh decode, first attempt): the
 * `if (o->field) cb(o->field)` chain emits the beqzl-with-next-load-in-delay
 * idiom; cb is the gl_func_00000000 release placeholder. */
extern int gl_func_00000000();
void gl_func_0000E2A4(int *o) {
    if (o[0x6C / 4]) gl_func_00000000(o[0x6C / 4]);
    if (o[0x70 / 4]) gl_func_00000000(o[0x70 / 4]);
    if (o[0x8C / 4]) gl_func_00000000(o[0x8C / 4]);
    if (o[0x78 / 4]) gl_func_00000000(o[0x78 / 4]);
    if (o[0x80 / 4]) gl_func_00000000(o[0x80 / 4]);
    if (o[0x84 / 4]) gl_func_00000000(o[0x84 / 4]);
    if (o[0x94 / 4]) gl_func_00000000(o[0x94 / 4]);
    if (o[0x98 / 4]) gl_func_00000000(o[0x98 / 4]);
}

/* gl_func_0000E368: 42-insn gated flag toggle. Returns early unless bit 16 of
 * (a0->0x50)->0x4F0 is set, a0->0x48 == 2, and the callback succeeds; then
 * toggles a0->0xB0 between 0/1 and clears/sets bit 2 of a0->0x44->0x60->0x18.
 * EXACT 42/42 (2026-10-14, agent-g). The old 98.45 wrap's "v1 vs t2 read temp
 * renumber cap" was the pointer spelling: the target's `lw t2,24(v0); addiu
 * v0,v0,24; sw 0(v0)` is a field POINTER (v = base + 0x18) with a plain
 * compound `*v &= ~4` -- the read is then an unnamed ring temp (t2/t5) instead
 * of the named `t` candidate (v1). The old "reassign the base" spelling
 * (int t = v[6]; v += 6; *v = t | 4) only reproduced the advance shape.
 * docs/IDO_CODEGEN.md#e368-field-pointer-compound-rmw-ring-temp */
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
        int *v = (int *)(*(int *)(*(int *)((char *)a0 + 0x44) + 0x60) + 0x18);
        *v &= ~4;
        *(int *)((char *)a0 + 0xB0) = 0;
    } else {
        int *v = (int *)(*(int *)(*(int *)((char *)a0 + 0x44) + 0x60) + 0x18);
        *v |= 4;
        *(int *)((char *)a0 + 0xB0) = 1;
    }
}

/* game_libs_func_0000E410..E490: CONTIGUOUS lower-opt (-O1/-g) family. Each is
 * `int *p=(int*)(a0+0x18); *p OP= BIT; return p;` (E410 |=4|=8, E42C &=~4&=~8,
 * E450 |=8, E464 &=~8, E47C |=4, E490 &=~4). CAP under -O2: target uses
 * addiu v0,a0,0x18 + 0(v0) RMW addressing AND keeps redundant stores (E410/E42C),
 * but -O2 C folds to 0x18(a0) offset-addressing and dead-store-eliminates the
 * first write (verified 2026-05-24).
 * OPT-SPLIT DEAD END (verified 2026-05-31): the "-O1/-g OPT_FLAGS split would
 * batch-unlock this" idea is WRONG. Tested E464's body at -O1, -O1-g, -O1-g3,
 * -O2-g: ALL add a `addiu sp,sp,-8` FRAME and SPILL the pointer
 * (sw/lw 4(sp); lw/sw 0(reg)) — frame-size mismatch, worse than -O2's direct
 * form. The target is -O2-SIZE (no frame) with pointer-in-v0 (addiu v0,a0,0x18;
 * 0(v0) RMW); NO opt level produces that. Genuine cap — do NOT attempt the
 * OPT_FLAGS split. */
/* CARVE ATTEMPT 2026-06-10 (the E410 sextet as its own landable unit):
 * REVERTED. The unit C compiles 38/38 byte-exact with correct 4-byte
 * fn packing (IDO packs consecutive fns at align-4 -- verified), BUT
 * the tail split is NOT layout-safe: game_libs_tail.c.o carries a
 * trailing align pad (+0xC) and the unit exhibits the post1b-class
 * pre-existing internal drift (symbols land -0x10 from their USO
 * names), so the naive three-way split shifted 103k words. The sextet
 * promote therefore belongs to the RELAYOUT SESSION with the other
 * ready bodies; the verified unit source is preserved in this comment
 * block's history (commit) and each wrap below. */
/* game_libs_func_0000E410: set flags 4|8 on a0->i_18, returns the
 * field pointer. BYTE-EXACT C FOUND 2026-06-10 (0 diffs standalone):
 * the same role-#6 barrier as the E450 quartet -- `int *p; p = ...;
 * if (1) {}` materializes the addiu base so ALL accesses go via 0(v0)
 * (without it the first load folds to 24(a0) and the stores split).
 * Fifth member of the flag-helper family, all five now byte-exact.
 * LAND BLOCKED on the mid-file constraint; relayout session. */
int *game_libs_func_0000E410(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p |= 4;
    *p |= 8;
    return p;
}

/* game_libs_func_0000E42C: clear flags 4+8 on a0->i_18, returns the
 * field pointer. BYTE-EXACT 2026-06-10 (0 diffs standalone) via the
 * role-#6 barrier; SIXTH member of the flag-helper family (E410/E42C/
 * E450/E464/E47C/E490 -- set/clear x {4, 8, both}, all solved). LAND
 * BLOCKED mid-file; relayout session. */
int *game_libs_func_0000E42C(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p &= ~4;
    *p &= ~8;
    return p;
}

/* game_libs_func_0000E450: set flag 8 on a0->i_18. BYTE-EXACT C FOUND
 * 2026-06-10 (0 diffs standalone): the explicit-pointer addiu form
 * needs `int *p; p = (int *)(a0 + 0x18); if (1) {}` -- the BB-split
 * lever's 6th role: it blocks IDO's offset-folding across the block
 * boundary so the addiu v0,a0,24 materializes. LAND BLOCKED on the
 * mid-file in-place constraint; promote via the relayout session. */
void game_libs_func_0000E450(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p = *p | 8;
}

/* game_libs_func_0000E464: clear flag 8 on a0->i_18. BYTE-EXACT C FOUND
 * 2026-06-10 (0 diffs standalone): the explicit-pointer addiu form
 * needs `int *p; p = (int *)(a0 + 0x18); if (1) {}` -- the BB-split
 * lever's 6th role: it blocks IDO's offset-folding across the block
 * boundary so the addiu v0,a0,24 materializes. LAND BLOCKED on the
 * mid-file in-place constraint; promote via the relayout session. */
void game_libs_func_0000E464(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p = *p & ~8;
}

/* game_libs_func_0000E47C: set flag 4 on a0->i_18. BYTE-EXACT C FOUND
 * 2026-06-10 (0 diffs standalone): the explicit-pointer addiu form
 * needs `int *p; p = (int *)(a0 + 0x18); if (1) {}` -- the BB-split
 * lever's 6th role: it blocks IDO's offset-folding across the block
 * boundary so the addiu v0,a0,24 materializes. LAND BLOCKED on the
 * mid-file in-place constraint; promote via the relayout session. */
void game_libs_func_0000E47C(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p = *p | 4;
}

/* game_libs_func_0000E490: clear flag 4 on a0->i_18. BYTE-EXACT C FOUND
 * 2026-06-10 (0 diffs standalone): the explicit-pointer addiu form
 * needs `int *p; p = (int *)(a0 + 0x18); if (1) {}` -- the BB-split
 * lever's 6th role: it blocks IDO's offset-folding across the block
 * boundary so the addiu v0,a0,24 materializes. LAND BLOCKED on the
 * mid-file in-place constraint; promote via the relayout session. */
void game_libs_func_0000E490(char *a0) {
    int *p;
    p = (int *)(a0 + 0x18);
    if (1) {}
    *p = *p & ~4;
}

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

/* gl_func_0000E5D0: 39-insn factory + 2-threshold side-effect (0x9C, frame 0x20).
 *
 *   factory = func1(0, &D_00000000, 0xC0, 0xB, 0xC, 1); self->[0x60] = factory;
 *   func2(factory, -2);
 *   factory = self->[0x60]; if (factory->n >= 0xB) factory->sub[0xD4] = 8;
 *   factory = self->[0x60]; if (factory->n >= 0xC) factory->sub[0xE8] = 4;
 *
 * BYTE-EXACT 39/39 (2026-10-14 agent-g), from the 98.72% wrap. The UNCONDITIONAL
 * reload before the second check (2026-06-20) gave the structure; the last
 * 8-word residual (self $a0 / factory $v1 vs target $v1 / $v0) was NOT a
 * spilltemp-reload colouring cap: the K&R int return of func2 is a dead $v0
 * def that excludes $v0 from the post-call webs. Calling func2 through the
 * void-returning alias gl_func_00000000_e5d0_v (=0 in undefined_syms_auto.txt)
 * frees $v0 -> factory $v0, self reload $v1 (38C0 / 082F8 void-alias lever,
 * docs/IDO_CODEGEN.md#wave3-round2-38c0-15fc). */
struct gl_E5D0_factory { int n; char pad[0x1c]; int *sub; };
extern void gl_func_00000000_e5d0_v();
void gl_func_0000E5D0(int *self) {
    struct gl_E5D0_factory *factory =
        (struct gl_E5D0_factory *)gl_func_00000000(0, &D_00000000, 0xC0, 0xB, 0xC, 1);
    self[0x60 / 4] = (int)factory;
    gl_func_00000000_e5d0_v(factory, -2);
    factory = (struct gl_E5D0_factory *)self[0x60 / 4];
    if (factory->n >= 0xB) {
        factory->sub[0xD4 / 4] = 8;
    }
    factory = (struct gl_E5D0_factory *)self[0x60 / 4];
    if (factory->n >= 0xC) {
        factory->sub[0xE8 / 4] = 4;
    }
}

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
 * 2026-05-28 MATCHED (byte-exact). The key was finalizing on the MAIN-call result
 * (the object) — held across the 3rd call (spilled + reloaded), with the 3rd call's
 * return DISCARDED — NOT on the 3rd call's return (the prior wrong decode). Same
 * back-link-finalizer family shape as gl_func_0003FF44. */
void gl_func_0000E66C(int *self) {
    int *obj;
    if (self[0x58 / 4] == 0) {
        gl_func_00000000(self);
    }
    obj = (int*)gl_func_00000000(0, self[0x58 / 4], self[0x5C / 4], self[0x54 / 4]);
    self[0x6C / 4] = (int)obj;
    gl_func_00000000((char*)self + 0x10, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    obj[0x14 / 4] = (int)self;
}

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
 * feedback_doc_marker_is_bail.md. 2026-05-29: 99.27% -> 99.82% by applying the
 * gl_func_0000E84C pattern (store factory result straight to self->0x70, re-read
 * self->0x70 inline per call, dedicated `q` spanning func5+final) — this fixed
 * the reloaded-obj register (was $a3, now $a1). RESIDUAL (8 frame-cascade diffs):
 * target frame -48 has an 8-byte UNUSED alignment gap that IDO here packs away
 * (-40); a named float local for the cast forces -48 but then stack-homes the
 * float (wrong, target keeps it in $f4) and regresses to 99.49%. Genuine
 * frame-alignment cap. INCLUDE_ASM remains build path.
 *
 * 2026-05-29 PRECISE CHARACTERIZATION (exhaustive pad grind): a `volatile double`
 * or `volatile int pad[2]` unused local DOES crack the frame SIZE (0x28->0x30) with
 * zero extra instructions — that removes the prologue + a1/a2-home cascade, leaving
 * ONLY 2 diffs: the a1 spill-reload (insns 32-33) lands at 0x24 (mine) vs 0x2C
 * (target). Root cause: IDO lays named locals (the pad) ABOVE compiler-generated
 * spills, so the pad takes 0x28-0x2F and the spill drops to 0x24; the target instead
 * has the spill HIGH (0x2C) with the 8-byte unused gap BELOW it (0x24-0x2B). That
 * inverted ordering (unused-low, spill-high) is NOT producible from a named C local
 * — confirmed via volatile double/int/int[2], all leave the spill at 0x24. Genuine
 * irreducible 2-insn spill-position cap; pad omitted (no exact gain, keeps C clean).
 * 2026-06-10: the EARLY-PSEUDO trick (dead-init, cracked 674's v0/v1 cap) probed
 * here in 4 decl-order x init permutations -- spill position UNMOVED (99.93 best,
 * pad-first forms regress to 99.89). The slot-ordering cap survives pseudo-order
 * forcers too; it is allocator-internal (uoptlist territory).
 * CRACKED 2026-06-11 (wave 2, 100.0): `volatile int pad[2]` (8-byte phantom,
 * not 4) occupies 0x24-0x2B so the self[0x60] CSE spill home drops to 0x20 =
 * target layout (rule 4 dead-local sizing: the gap was 8 bytes, the pad must
 * match it). Same lever cracked E79C + E910 same day.
 */
void gl_func_0000E6E8(int *self, int a1, int a2, float *a3_float) {
    int *q;
    volatile int pad[2];  /* phantom-slot lever, 8-byte form (wave-2 2026-06-11) */
    self[0x74 / 4] = (int)a3_float;
    if (self[0x60 / 4] == 0) {
        gl_func_00000000();
    }
    self[0x70 / 4] = gl_func_00000000(0, self[0x60 / 4]);
    gl_func_00000000((int *)self[0x70 / 4], (int)*(float *)self[0x74 / 4]);
    gl_func_00000000((int *)self[0x70 / 4], a1, a2);
    q = (int *)self[0x70 / 4];
    gl_func_00000000((char *)self + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)self;
}


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
 * feedback_doc_marker_is_bail.md. 2026-05-29: applied the gl_func_0000E84C
 * pattern (factory result straight to self->0x84, re-read inline per call,
 * dedicated `q` spanning func5+final) -> 99.82%, fixing the reloaded-obj reg
 * ($a3 -> $a1). RESIDUAL = the SAME 8-byte frame-alignment gap as E6E8 (target
 * -48 vs -40); present even though func3 here is an int deref (no float), so the
 * gap is a consistent family spill-slot-packing cap, not float-related.
 * INCLUDE_ASM remains build path.
 */
void gl_func_0000E79C(int *self, int a1, int a2, int *a3_int_ptr) {
    int *q;
    volatile int pad[2];  /* phantom-slot lever, 8-byte form (wave-2 2026-06-11) */
    self[0x88 / 4] = (int)a3_int_ptr;
    if (self[0x64 / 4] == 0) {
        gl_func_00000000();
    }
    self[0x84 / 4] = gl_func_00000000(0, self[0x64 / 4], self[0x68 / 4]);
    gl_func_00000000((int *)self[0x84 / 4], *(int *)self[0x88 / 4], 1);
    gl_func_00000000((int *)self[0x84 / 4], a1, a2);
    q = (int *)self[0x84 / 4];
    gl_func_00000000((char *)self + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)self;
}


/* gl_func_0000E84C: constructor. obj = cb(0, a3); s0->0x80 = obj. Then marshals
 * obj with: cb(obj, 0.0f, 0.0f); cb(obj, f38, f3C, f38, f3C) [floats as raw bits
 * in int regs/stack via mfc1]; cb(obj, i38, i3C, i40) [same fields as int];
 * cb(obj, a1, a2); cb(s0+0x10, obj). Ends: if (obj->0x14) obj->4 = 1; obj->0x14
 * = s0. MATCHED 2026-05-29 (fresh decode). Three levers: (1) float-typed aliases
 * (gl_func_00000000_e84c2/4 in undefined_syms) so the float args pass via mfc1
 * (O32 float-after-int → int reg) instead of a stack roundtrip from
 * `*(int*)&f`; (2) re-read s0->0x80 from memory each call (don't cache obj in an
 * s-reg) — `q` spans the cb6 call (spilled+reloaded), matching the target; (3)
 * INLINE the 0x38/0x3C float reads in the cb call (no named float locals) —
 * named locals reserved a dead 8-byte stack slot, bloating the frame -48 -> -56;
 * IDO CSEs the inlined reads into single f0/f2 loads. */
extern int gl_func_00000000();
extern void gl_func_00000000_e84c2(int, float, float);
extern void gl_func_00000000_e84c4(int, float, float, float, float);
void gl_func_0000E84C(int *s0, int a1, int a2, int a3) {
    int *q;
    s0[0x80 / 4] = gl_func_00000000(0, a3);
    gl_func_00000000_e84c2(s0[0x80 / 4], 0.0f, 0.0f);
    gl_func_00000000_e84c4(s0[0x80 / 4], *(float *)&s0[0x38 / 4], *(float *)&s0[0x3C / 4], *(float *)&s0[0x38 / 4], *(float *)&s0[0x3C / 4]);
    gl_func_00000000((int *)s0[0x80 / 4], s0[0x38 / 4], s0[0x3C / 4], s0[0x40 / 4]);
    gl_func_00000000((int *)s0[0x80 / 4], a1, a2);
    q = (int *)s0[0x80 / 4];
    gl_func_00000000((char *)s0 + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)s0;
}

/* gl_func_0000E910: 44-insn lazy-init + 4-call chain + linked-set finalizer (0xB0, frame 0x30).
 *
 * 6th sibling of the E66C/EAAC/525F0/E6E8/E79C linked-set finalizer family
 * (per feedback_1080_linked_set_finalizer_tail_idiom memo). Distinguished
 * by field offsets 0x60/0x78/0x7C and 2-arg factory call.
 *
 * Decoded structure (raw-word disasm):
 *   if (self->[0x60] == 0) func1_init();             // lazy init (no body store)
 *   self->[0x7C] = a3_int_ptr;                        // UNCONDITIONAL (after the if)
 *   obj = func2(0, self->[0x60]);                    // 2-arg factory
 *   self->[0x78] = obj;
 *   func3(obj, *(int*)self->[0x7C]);                 // int-deref (vs E6E8's float→int)
 *   func4(obj, a1, a2);
 *   func5(&self[0x10/4], obj);
 *   if (obj->[0x14] != 0) obj->[0x4] = 1;            // back-link-with-flag finalizer
 *   obj->[0x14] = self;
 *
 * 2026-05-29: 90.39% → 99.77%. PRIOR DECODE WAS WRONG: the `self->0x7C = a3`
 * store is UNCONDITIONAL, not inside the lazy-init `if` — the target's `bnez`
 * lands BEFORE that store (both paths execute it). Moving it after the `if` makes
 * a3 live across func1() so IDO homes it at entry (sw a3) + reloads — exactly the
 * "2 insns mine lacks" the old comment misattributed to a regalloc cap. Also
 * applied the gl_func_0000E84C pattern (factory result straight to self->0x78,
 * re-read inline per call, dedicated `q`). 2026-06-10 FRAME CRACKED:
 * `volatile int pad;` (unused, declared after q) reserves the missing
 * 8-byte slot WITHOUT emitting any access -- the -O2 phantom-slot
 * maker (plain unused locals are dropped; volatile ones keep their
 * slot). 10 -> 3 diffs. Remaining 3: the a3 home spills at 0x24 (mine)
 * vs 0x20 (target) -- the volatile local always takes the BOTTOM slot
 * and the spill goes above; the target has them swapped, and local-vs-
 * spill slot ordering is not C-controllable (3 placements tested).
 * TRY THE SAME PAD ON E6E8/E79C (same family gap). */
void gl_func_0000E910(int *self, int a1, int a2, int *a3_int_ptr) {
    int *q;
    volatile int pad[2];
    if (self[0x60 / 4] == 0) {
        gl_func_00000000();
    }
    self[0x7C / 4] = (int)a3_int_ptr;
    self[0x78 / 4] = gl_func_00000000(0, self[0x60 / 4]);
    gl_func_00000000((int *)self[0x78 / 4], *(int *)self[0x7C / 4]);
    gl_func_00000000((int *)self[0x78 / 4], a1, a2);
    q = (int *)self[0x78 / 4];
    gl_func_00000000((char *)self + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)self;
}


/* gl_func_0000E9C0: linked-set-finalizer family member with FP color init.
 * Lazy-init self->0x60; self->0x90 = a3; obj = factory(0, self->0x60) -> 0x8C;
 * cb(obj, a1, a2); write RGBA {250,235,100,0}/255 to obj+0xC4..0xD0; cb(self+0x10,
 * obj); finalizer (if obj->0x14 set obj->4=1; obj->0x14=self). Fresh decode
 * 2026-05-29 via the gl_func_0000E84C pattern + inv-divisor runtime div.s.
 * EXACT 2026-07-15 (was 99.20; the "not reachable from C" $a1 cap RETRACTED).
 * Cracks: (1) the color-base is q ITSELF advanced destructively
 * (q = self->0x8C; q = (int*)((char*)q + 0xC4)) — same-name web reuse binds
 * the base web to $a1, the register q's later call-arg web is constrained to
 * (the old a1-param overwrite regressed because the param var s-promoted;
 * the same-name-q spelling splits webs cleanly and fixes the whole a1/v1
 * cascade + the addiu schedule swap). (2) a third named local
 * `volatile int pad;` (uninitialized, unused) homes at 36(sp), dropping the
 * lazy-flag spilltemp to 32(sp) (frame 48 unchanged: q=44, inv=40, pad=36,
 * temp=32). */
extern int gl_func_00000000();
void gl_func_0000E9C0(int *self, int a1, int a2, int a3) {
    int *q;
    float inv;
    volatile int pad;
    inv = 255.0f;
    if (self[0x60 / 4] == 0) {
        gl_func_00000000();
    }
    self[0x90 / 4] = a3;
    self[0x8C / 4] = gl_func_00000000(0, self[0x60 / 4]);
    gl_func_00000000((int *)self[0x8C / 4], a1, a2);
    q = (int *)self[0x8C / 4];
    q = (int *)((char *)q + 0xC4);
    ((float *)q)[0] = 250.0f / inv;
    ((float *)q)[1] = 235.0f / inv;
    ((float *)q)[2] = 100.0f / inv;
    ((float *)q)[3] = 0.0f / inv;
    q = (int *)self[0x8C / 4];
    gl_func_00000000((char *)self + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)self;
}

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
 * pattern as gl_func_0000E66C — shared linked-set finalizer family.
 *
 * MATCHED 2026-05-29 via the gl_func_0000E84C pattern: store the factory result
 * straight to self->0x98, re-read self->0x98 inline for each call (don't cache
 * the node in an $s-reg), and use a dedicated `q` spanning the link call + the
 * finalizer. The simplest family member (no lazy-init, no a3-home-across-call)
 * so it has no frame-alignment gap — full byte match.
 */
void gl_func_0000EAAC(int *self, int a1, int a2, int a3) {
    int *q;
    self[0x9C / 4] = a3;
    self[0x98 / 4] = gl_func_00000000(0, 0x4B);
    gl_func_00000000((int *)self[0x98 / 4], *(int *)self[0x9C / 4]);
    gl_func_00000000((int *)self[0x98 / 4], a1, a2);
    q = (int *)self[0x98 / 4];
    gl_func_00000000((char *)self + 0x10, q);
    if (q[0x14 / 4] != 0) {
        q[0x4 / 4] = 1;
    }
    q[0x14 / 4] = (int)self;
}

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
