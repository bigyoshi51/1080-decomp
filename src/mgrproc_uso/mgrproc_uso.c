#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Macro definitions for NM-wrap bodies. Auto-managed by /struct-name-tick.
 * Default build never sees these — wrap bodies aren't compiled.
 * MGR_STATE_PTR: pointer to the manager state struct (read into `state`/`s`
 * locals, then deref'd for fields 0x4C/0x6A8/0x6AC). mgrproc_uso D+0x30.
 * MGR_D_64: int slot — written from q[3], read as an index (`idx = MGR_D_64
 * - 5`) and OR'd with flag 0xA0000 (positional, mixed use). mgrproc_uso D+0x64.
 * MGR_STATE_CODE: int state/mode enum — assigned discrete codes (1,3,4,5,7,8)
 * across the dispatch funcs and read into a `state` local. mgrproc_uso D+0x40.
 * MGR_D_44: int state-companion slot — set alongside MGR_STATE_CODE/0x48 with
 * discrete values (2,7), sometimes copied from arg field 0x44. Positional.
 * mgrproc_uso D+0x44.
 */
#define MGR_STATE_PTR (*(int**)((char*)&D_00000000 + 0x30))
#define MGR_D_64 (*(int*)((char*)&D_00000000 + 0x64))
#define MGR_STATE_CODE (*(int*)((char*)&D_00000000 + 0x40))
#define MGR_D_44 (*(int*)((char*)&D_00000000 + 0x44))
#endif

/* mgrproc_uso_func_00000000 / _0000004C / _000000B0 (contiguous -O0 run,
 * 0x0..0xF8) live in mgrproc_uso_o0_0.c — carved into a dedicated -O0 sub-unit
 * and concatenated into the Yay0 block (region 0) before compression. See the
 * block1 yay0 rule in the Makefile. */

/* mgrproc_uso_func_000000F8 .. _00000A14 (the block's two -O0 runs + the small
 * leaves between them, 0xF8..0xAE0) live in mgrproc_uso_head.c (-O2, [0xF8,0x19C))
 * and mgrproc_uso_o0_19C.c (-O0, [0x19C,0xAE0)) — carved sub-units concatenated
 * into the Yay0 block before compression. See the block1 yay0 rule. func_000009A8
 * is byte-matched at -O0 there. */

void mgrproc_uso_func_00000AE0(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)((char*)*(int**)(&D_00000000 + 0x30) + 0x6AC));
    gl_func_00000000(&D_00000000);
}

extern char D_mgr_B20_1;
extern char D_mgr_B20_2;
void mgrproc_uso_func_00000B20(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)(&D_mgr_B20_1 + 0x30));
    gl_func_00000000(&D_mgr_B20_2);
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_00000B5C: 46-insn (0xB8) state-update with cond branch.
 * Sibling of mgrproc_uso_func_00000C14 — identical structure, different
 * constants (state[0x4E0]=5 vs 7 in 00C14; otherD[0x40]=3 vs 5; FALSE arm
 * passes 4 instead of 0 to gl_func).
 *
 * Decoded:
 *   state = D[0x30];
 *   gl_func(state);
 *   v0 = gl_func(state->[0x6AC]->[0x4C]);
 *   if (v0 != 0) {
 *     state->[0x504] = 7;
 *     state->[0x4E0] = 5;
 *     otherD[0x40] = 3;
 *     otherD[0x44] = 7;
 *     state->[0x7D8] = 1;
 *     gl_func(state);
 *   } else {
 *     otherD[0x40] = 3;
 *     gl_func(state, state->[0x6A8]->[0xC], 4);
 *   }
 *
 * Multi-pass NM. Default INCLUDE_ASM build remains byte-correct. */
extern int gl_func_00000000();
void mgrproc_uso_func_00000B5C(void) {
    int *state = MGR_STATE_PTR;
    int *other = (int*)&D_00000000;
    int v0;
    gl_func_00000000(state);
    v0 = gl_func_00000000(*(int*)((char*)*(int**)((int*)((char*)&D_00000000 + 0x30))[0x6AC/4] + 0x4C));
    if (v0 != 0) {
        int *s = MGR_STATE_PTR;
        s[0x504/4] = 7;
        s = MGR_STATE_PTR;
        s[0x4E0/4] = 5;
        other[0x40/4] = 3;
        other[0x44/4] = 7;
        s = MGR_STATE_PTR;
        s[0x7D8/4] = 1;
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x30));
    } else {
        other[0x40/4] = 3;
        gl_func_00000000(
            *(int*)((char*)&D_00000000 + 0x30),
            *(int*)((char*)MGR_STATE_PTR + 0x6A8 + 0xC),
            4);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000B5C);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00000C14: 44-insn (0xB0) state-update with conditional
 * branch. Reads (int*)&D[0x30] = global state ptr, queries via gl_func()
 * the outer->[0x6AC]->[0x4C] sub-state, and based on result either:
 *   - cond TRUE: clear state[0x504], state[0x4E0]=7, D[0x40]=5,
 *                D[0x44]=7, state[0x7D8]=1, call gl_func(state)
 *   - cond FALSE: D[0x40]=7, call gl_func(state, 0, 0)
 *
 * Multiple D[0x30] reloads in target asm (5 separate `lw rN, 0(v1)`)
 * suggest IDO -O2 doesn't CSE the state-ptr load across the if-arm
 * boundaries.
 *
 * 2026-05-14 retest with `D_00000000 + 0x30` alias: makes built 20 bytes
 * SHORTER than target (38 diffs, 156 vs 176) — IDO CSEs the lui/addiu/lw
 * sequence into named-local + 3 reloads, but target wants 5 separate
 * 3-insn reload sequences. INSN_PATCH+SUFFIX_BYTES grow recipe would be
 * heavy (~38 entries + 20 bytes). Deferred. */
extern int gl_func_00000000();
extern char D_00000000;
extern int *D_C14_state; /* alias of D + 0x30 (state ptr) */
void mgrproc_uso_func_00000C14(void) {
    int *other = (int*)&D_00000000;
    int v0;
    gl_func_00000000(D_C14_state);
    v0 = gl_func_00000000(*(int*)((char*)(D_C14_state)[0x6AC/4] + 0x4C));
    if (v0 != 0) {
        D_C14_state[0x504/4] = 0;
        D_C14_state[0x4E0/4] = 7;
        other[0x40/4] = 5;
        other[0x44/4] = 7;
        D_C14_state[0x7D8/4] = 1;
        gl_func_00000000(D_C14_state);
    } else {
        other[0x40/4] = 7;
        gl_func_00000000(D_C14_state, 0, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000C14);
#endif

void mgrproc_uso_func_00000CC4(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D00(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D3C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void mgrproc_uso_func_00000D94(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000E04);

/* Alternate entry point for mgrproc_uso_func_000011A4: loads a1 from D+0x68
 * and falls through into 11A4 with caller-provided a0. No standalone jr-ra. */
void mgrproc_uso_func_000011A4(char *s0, int a1);
#ifdef NON_MATCHING
void mgrproc_uso_func_0000119C(char *a0) {
    mgrproc_uso_func_000011A4(a0, *(int *)((char *)&D_00000000 + 0x68));
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000119C);
#endif

/* mgrproc_uso_func_000011A4 - verified structural decode (0x108,
 * 66 insns, sub-object registration table builder).
 *   void mgrproc_uso_func_000011A4(St *s0, int a1) {
 *       reg(&D_00000000, (a1 - 1) | 0x200000);
 *       reg(s0 + 0x6B0, *(int*)&D_x | 0x000A0000);
 *       reg(s0 + 0x6C8, 0x210000);
 *       q = s0->0x6A8;
 *       if (q->0x8 == q->0x4 + 1)
 *           reg(s0 + 0x6E0, 0x210000 | 1);
 *       else
 *           reg(s0 + 0x6E0, 0x210000 | (q->0x4 + 2));
 *       reg(s0 + 0x6F8, *(int*)&D_y | 0x001E0000);
 *       reg(s0 + 0x728, 0x210000 | 0x7);
 *       reg(s0 + 0x740, 0x210000 | 0x8);
 *       reg(s0 + 0x758, 0x210000 | 0x9);
 *       reg(s0 + 0x770, 0x210000 | 0xA);
 *       reg(s0 + 0x788, 0x210000 | 0xD);
 *   }
 * (reg = func_00000000(sub_obj_ptr, packed_id).)
 * Struct-typing reference: s0 holds a block of registrable sub-
 * objects at offsets 0x6B0 (1712), 0x6C8 (1736), 0x6E0 (1760),
 * 0x6F8 (1784), 0x728 (1832), 0x740 (1856), 0x758 (1880), 0x770
 * (1904), 0x788 (1928); s0->0x6A8 (1704) = a queue/range struct
 * whose 0x4 (start) and 0x8 (end) gate the 0x6E0 entry's id
 * (full-range -> id 1, else start+2). Packed ids: high bits select
 * a category (0x210000 = the main widget group, 0x200000 / 0xA0000
 * / 0x1E0000 = variants OR'd with a per-element index or a global
 * value from &D_x/&D_y). ~10x gl_func_00000000 reloc calls + lui/ori
 * packed-constant builds + a branch on the queue range. C body builds
 * builds at ~97% NM (64/66 byte-exact, placeholder calls -> addr 0). The
 * remaining 2-of-66 diff is a schedule-swap between the first arg's lui-
 * const and the `(a1-1)` addiu — previously INSN_PATCH'd; INSN_PATCH
 * REMOVED 2026-05-23 (per feedback_no_instruction_forcing_matches_policy).
 * No episode (reloc-blind call targets); default build is INCLUDE_ASM. */
#ifdef NON_MATCHING
void mgrproc_uso_func_000011A4(char *s0, int a1) {
    int *q;
    gl_func_00000000(&D_00000000, (a1 - 1) | 0x200000);
    gl_func_00000000(s0 + 0x6B0, *(int *)((char *)&D_00000000 + 0x64) | 0x000A0000);
    gl_func_00000000(s0 + 0x6C8, 0x210000);
    q = *(int **)(s0 + 0x6A8);
    if (q[2] == q[1] + 1) {
        gl_func_00000000(s0 + 0x6E0, 0x210000 | 1);
    } else {
        gl_func_00000000(s0 + 0x6E0, 0x210000 | (q[1] + 2));
    }
    gl_func_00000000(s0 + 0x6F8, *(int *)((char *)&D_00000000 + 0x54) | 0x001E0000);
    gl_func_00000000(s0 + 0x728, 0x210000 | 0x7);
    gl_func_00000000(s0 + 0x740, 0x210000 | 0x8);
    gl_func_00000000(s0 + 0x758, 0x210000 | 0x9);
    gl_func_00000000(s0 + 0x770, 0x210000 | 0xA);
    gl_func_00000000(s0 + 0x788, 0x210000 | 0xD);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000011A4);
#endif

void mgrproc_uso_func_000012AC(char *a0) {
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a0 + 0x6B0);
    gl_func_00000000(a0 + 0x6C8);
    gl_func_00000000(a0 + 0x6E0);
    gl_func_00000000(a0 + 0x6F8);
}

void mgrproc_uso_func_00000000();  /* K&R-style: matches the K&R def above */

void mgrproc_uso_func_00001304(void) {
    mgrproc_uso_func_00000000();
}

/* mgrproc_uso_func_00001324: 41-insn lazy-init guard. Idempotent
 * "ensure-initialized" check on arg0->[0x4FC] flag. If unset, runs init
 * cascade. Sets arg0[0x4FC]=1 (guard) + arg0[0x7D0]=arg0[0x4F8] (cached
 * state). Returns 1.
 *
 * NATURAL CEILING: 80.5% NM. The 8-word diff at 0x28/0x30/0x48/0x64/0x80/
 * 0x84/0x88/0x8C is a pure register-rename (v0<->v1 in the early
 * conditional chain, t0<->t9 in the final 0x4F8 reload + flag store +
 * cache store). Was previously documented as INSN_PATCH-promotable per
 * docs/POST_CC_RECIPES.md "Pure register-rename at any scale" — INSN_PATCH
 * REMOVED 2026-05-23 and docs/POST_CC_RECIPES.md deprecated (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
#ifdef NON_MATCHING
int mgrproc_uso_func_00001324(char *arg0) {
    int v;
    if (*(int*)(arg0 + 0x4FC) == 0) {
        gl_func_00000000(*(int*)(arg0 + 0x6AC), 0, 1);
        v = *(int*)(arg0 + 0x4F8);
        if (v == 0) {
            gl_func_00000000(*(int*)(arg0 + 0x6A8));
        } else if (v != 2) {
            gl_func_00000000(*(int*)(arg0 + 0x6A8));
        }
        if (gl_func_00000000(*(int*)(arg0 + 0x6A8)) != 0 &&
            gl_func_00000000(*(int*)(*(int*)(arg0 + 0x6AC) + 0x4C)) != 0) {
            *(int*)(arg0 + 0x4EC) = -0x258;
        }
        *(int*)(arg0 + 0x4FC) = 1;
        *(int*)(arg0 + 0x7D0) = *(int*)(arg0 + 0x4F8);
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001324);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_000013C8: 75-insn (0x12C) post-init dispatcher.
 *
 * Sibling of mgrproc_uso_func_00001324 (the lazy-init guard at +0x4FC),
 * runs AFTER guard is set. Reads a0[0x4F8] (state idx); if non-zero,
 * runs early-return. Otherwise calls a0[0x6A8] init, checks v0 (alloc
 * result); if 0 returns. On success, sets D[0x44]=7, then probes
 * 0xA0000200 (likely RDP MI hardware reg or memory signature) against
 * 0xAC290000 — if equals, takes one branch (D[0x40]=7 + clears state),
 * else other branch (loads D[0x68], decrements arg, calls func_0).
 * Continues into a 3-stage check ladder calling a0[0x6A8] / a0[0x6AC]
 * / a0[0x6AC]+0x4C with conditional state writes to D[0x40]/D[0x44]
 * and a0[0x504]/a0[0x7D8].
 *
 * Hardware register read at 0xA0000200 is the SI (Serial Interface)
 * SI_DRAM_ADDR_REG per references/indexes/hw_registers.h — likely a
 * controller-pak / EEPROM probe sequence. Comparison constant
 * 0xAC290000 is SI command bytes (RAM-write opcode upper).
 *
 * 75 insns is multi-tick decomp. Initial structural NM. Default build
 * INCLUDE_ASM keeps ROM byte-correct. */
/* 2026-05-07: full structural decode (was TODO stub).
 *
 * Logic (75 insns):
 *   if (a0->[0x4F8] != 0) goto epilogue;     // state guard
 *   if (gl_func(a0->[0x6A8]) == 0) goto epi; // init callback returns
 *   spill_var = 1;
 *   D[0x44] = 7;
 *   if (*(int*)0xA0000200 != 0xAC290000) {
 *       // SI register doesn't match expected: load D[0x68], decrement,
 *       // call func_0(&D, D[0x68] - 1), then go to merge
 *       gl_func(&D, D[0x68] - 1);
 *       goto merge;  // skip 7C8 reset
 *   } else {
 *       // SI register matches: clear a0->[0x7C8], goto epilogue
 *       a0->[0x7C8] = 0;
 *       goto epi;
 *   }
 *  merge:
 *   t4 = a0->[0x7C8];
 *   if (gl_func(a0->[0x6A8]) == 0) {
 *       D[0x40] = 7;
 *       D[0x44] = a0->[0x44];  // re-load (likely just preserve)
 *       spill_var = 1;
 *   } else {
 *       t4 = a0->[0x7C8];
 *       if (gl_func(a0->[0x6AC]) == 0) {
 *           t4 = a0->[0x6AC];
 *           if (gl_func(t4 + 0x4C) != 0) {
 *               D[0x40] = 5;
 *               spill_var = 0;
 *           } else {
 *               D[0x40] = 7;
 *           }
 *           a0->[0x7D8] = 1;
 *       }
 *   }
 *   if (spill_var == 4) a0->[0x504] = spill_var;
 *   else                a0->[0x504] = 0;
 *  epi: return;
 *
 * Hardware register read at 0xA0000200 = SI_DRAM_ADDR_REG; comparison
 * 0xAC290000 likely an opcode pattern check (controller-pak / EEPROM
 * probe). Multi-tick: structure captured, but byte match needs unique
 * externs (D[0x40], D[0x44], D[0x68]), the SI-register pattern, and
 * IDO's specific branch shape. Default INCLUDE_ASM remains exact. */
extern int gl_func_00000000();
void mgrproc_uso_func_000013C8(int *a0) {
    int spill_var = 0;
    int t4;
    if (a0[0x4F8 / 4] != 0) return;
    if (gl_func_00000000(a0[0x6A8 / 4]) == 0) return;
    spill_var = 1;
    MGR_D_44 = 7;
    if (*(volatile int*)0xA0000200 != (int)0xAC290000) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000 + 0x68) - 1);
        t4 = a0[0x7C8 / 4];
    } else {
        a0[0x7C8 / 4] = 0;
        return;
    }
    if (gl_func_00000000(a0[0x6A8 / 4]) == 0) {
        MGR_STATE_CODE = 7;
        MGR_D_44 = a0[0x44 / 4];
        spill_var = 1;
    } else {
        if (gl_func_00000000(a0[0x6AC / 4]) == 0) {
            t4 = a0[0x6AC / 4];
            if (gl_func_00000000(t4 + 0x4C / 4) != 0) {
                MGR_STATE_CODE = 5;
                spill_var = 0;
            } else {
                MGR_STATE_CODE = 7;
            }
            a0[0x7D8 / 4] = 1;
        }
    }
    if (spill_var == 4) {
        a0[0x504 / 4] = spill_var;
    } else {
        a0[0x504 / 4] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000013C8);
#endif

/* mgrproc_uso_func_000014F4: 40-insn 3-way switch on a0->[0x4D8] (v):
 *   v == 2: gl_func_0(D[0x190], 3, 1, a0); a0->[0x7D4] = 1;
 *   v == 1 || v == 3: gl_func_0(a0, D[0x170] + 0x26000F);
 *   else: skip
 *
 * Always-call gl_func_0(D + 0x628, a0->[0x4D8]) at entry.
 *
 * NATURAL CEILING: ~90% NM. Was previously documented as "exact via 3-extern
 * split + 4-insn INSN_PATCH at 0x4C/0x50/0x54/0x58" — INSN_PATCH REMOVED
 * 2026-05-23 as match-faking (per feedback_no_instruction_forcing_matches_policy).
 * The remaining cap is the third equality test's branch-likely-vs-beq+goto-
 * epilogue diff: target emits `beq v0,at(=3),case_13; nop; b end; lw ra (delay)`
 * vs IDO's `bnel v0,at,end; lw ra (delay); b case_13; nop`. The 3-extern split
 * (D_mgr_14F4_a/b/c, all aliased to 0x0) is retained to keep the lui/lo
 * structural decode honest in the NM body; default build is INCLUDE_ASM. */
extern int D_mgr_14F4_a, D_mgr_14F4_b, D_mgr_14F4_c;
#ifdef NON_MATCHING
void mgrproc_uso_func_000014F4(int *a0) {
    int v;
    gl_func_00000000((char*)&D_mgr_14F4_a + 0x628, *(int*)((char*)a0 + 0x4D8));
    v = *(int*)((char*)a0 + 0x4D8);
    if (v == 2) goto case_2;
    if (v == 1) goto case_13;
    if (v == 3) goto case_13;
    return;
case_2:
    gl_func_00000000(*(int*)((char*)&D_mgr_14F4_b + 0x190), 3, 1, a0);
    *(int*)((char*)a0 + 0x7D4) = 1;
    return;
case_13:
    gl_func_00000000(a0, *(int*)((char*)&D_mgr_14F4_c + 0x170) + 0x26000F);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000014F4);
#endif

/* mgrproc_uso_func_00001594: 32-insn (0x80) check-then-vtable-call helper.
 * Decoded:
 *   if (gl_func_0(D[0x190], a0) == 0) return;
 *   int *p = a0[0x48/4]; int idx = p[0x7C/4];
 *   if (p[idx*0xA + 0x24] == 0) return;
 *   D[0x30/4] = (int)a0;
 *   p = a0[0x48/4]; idx = p[0x7C/4];
 *   ((void(*)())p[idx*0xA + 0x24])();
 *
 * NATURAL CEILING: high-NM via recipe (1) only:
 * 1. feedback-ido-cse-bust-via-distinct-externs (docs/IDO_CODEGEN.md):
 *    D_mgr_1594_a + D_mgr_1594_c are distinct externs both aliased to
 *    0x00000000 in undefined_syms_auto.txt. The split forces IDO to
 *    emit 2 separate `lui rN, 0` instead of caching `&D` across both
 *    use sites — matches target's no-cache pattern.
 * 2. The 14-insn register-rename at 0x28-0x68 (the post-jal multu chain
 *    — IDO -O2 prefers $a2/$v1/{t6..t8}; target uses $v1/{t6..t9}) was
 *    previously documented as INSN_PATCH-promotable; INSN_PATCH REMOVED
 *    2026-05-23 as match-faking (per
 *    feedback_no_instruction_forcing_matches_policy). Default build is
 *    INCLUDE_ASM. */
extern int gl_func_00000000();
extern int D_mgr_1594_a, D_mgr_1594_c;
#ifdef NON_MATCHING
void mgrproc_uso_func_00001594(int *a0) {
    int *p;
    int idx;
    int *q;
    void (*fn)();
    if (gl_func_00000000(*(int*)((char*)&D_mgr_1594_a + 0x190), a0) == 0) return;
    p = (int*)a0[0x48 / 4];
    idx = *(int*)((char*)p + 0x7C);
    q = (int*)((char*)p + idx * 0x28);
    if (q[0x90 / 4] == 0) return;
    *(int*)((char*)&D_mgr_1594_c + 0x30) = (int)a0;
    p = (int*)a0[0x48 / 4];
    idx = *(int*)((char*)p + 0x7C);
    q = (int*)((char*)p + idx * 0x28);
    fn = (void(*)())q[0x90 / 4];
    fn();
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001594);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00001614: state-machine step (switch arg0->0x504, cases 0/1/4
 * as an if-else chain). Case 0: cb(&D+0x190,3,1), set state=1, cb(7,0,0). Case 1:
 * if cb(&D+0x190,1,1): set 0x4D8=1, several inits, alloc a node into arg0->0x524,
 * link it into the 0x56C list (header+0x10), conditional flag, register via
 * cb(arg0->0x6A8, node) and on success set node->0x60=2 + cb(arg0); then cb(&D+
 * 0x190,1,1). Case 4: cb(arg0, 4, indexed-entry from arg0->0x6A8). Fresh first-pass
 * decode 2026-05-29 (m2c-confirmed). Caps: arg0/node structs + ~14 cb prototypes
 * untyped (USO-reloc), &D-relative literals not symbolized. 91.8% reg-blind, exact
 * 98-insn count — the `switch` (not if-else chain) matched the target's up-front
 * compare-dispatch (beqz/beq/beql/b). Residual: deep spill-slot regalloc. NON_MATCHING. */
extern int gl_func_00000000();
void mgrproc_uso_func_00001614(char *arg0) {
    int state = *(int *)(arg0 + 0x504);
    void *node;
    int hdr;

    switch (state) {
    case 0:
        gl_func_00000000(*(int *)((char *)&D_00000000 + 0x190), 3, 1);
        *(int *)(arg0 + 0x504) = 1;
        gl_func_00000000(7, 0, 0);
        break;
    case 1:
        if (gl_func_00000000(*(int *)((char *)&D_00000000 + 0x190), state, 1) != 0) {
            *(int *)(arg0 + 0x4D8) = 1;
            gl_func_00000000(7, 0, 0);
            gl_func_00000000(0);
            gl_func_00000000(arg0);
            gl_func_00000000(arg0, *(int *)((char *)&D_00000000 + 0x170) + 0x26000F);
            *(void **)(arg0 + 0x524) = (void *)gl_func_00000000(0, arg0, *(int *)(arg0 + 0x7D8));
            gl_func_00000000(*(void **)(arg0 + 0x524), *(int *)(arg0 + 0x528));
            hdr = *(int *)(arg0 + 0x56C);
            node = *(void **)(arg0 + 0x524);
            gl_func_00000000(hdr + 0x10, node);
            if (*(int *)((char *)node + 0x14) != 0) {
                *(int *)((char *)node + 4) = 1;
            }
            *(int *)((char *)node + 0x14) = hdr;
            if (gl_func_00000000(*(int *)(arg0 + 0x6A8), node) != 0) {
                *(int *)((char *)*(void **)(arg0 + 0x524) + 0x60) = 2;
                gl_func_00000000(arg0);
            }
            gl_func_00000000(*(int *)((char *)&D_00000000 + 0x190), 1, 1);
        }
        break;
    case 4:
        {
            char *p = *(char **)(arg0 + 0x6A8);
            gl_func_00000000(arg0, 4, *(int *)(p + (*(int *)(p + 4) * 4) + 0x10));
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001614);
#endif

/* mgrproc_uso_func_0000179C: 30-insn (0x78) gated state-set.
 * Adjacent 2-insn alt-entry stubs (mgrproc_uso_func_00001814 / 0000181C,
 * each `jr ra; sw a0, 0(sp)`) used to be bundled into the symbol via a
 * 16-byte SUFFIX_BYTES recipe; that recipe was REMOVED 2026-05-23 as
 * instruction-byte-appending match-faking (per
 * feedback_no_instruction_forcing_matches_policy). The function still
 * lands at fuzzy=100 — the alt-entry stubs are tracked as separate
 * symbols now (their bytes come from .s).
 *
 * Decoded:
 *   if (a0->[0x7E4] != 1) return;
 *   if (a0->[0x7E8] >= 0x2EE) return;        // 750
 *   if (gl_func(&D, 0x40100, a0) == 0) return;
 *   if (gl_func(*(int*)(&D + 0x190)) == 0) return;
 *   a0->[0x7D4] = 1; */
void mgrproc_uso_func_0000179C(int *a0) {
    if (*(int*)((char*)a0 + 0x7E4) != 1) return;
    if (*(int*)((char*)a0 + 0x7E8) >= 0x2EE) return;
    if (gl_func_00000000(&D_00000000, 0x40100, a0) == 0) return;
    if (gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190)) == 0) return;
    *(int*)((char*)a0 + 0x7D4) = 1;
}

/* mgrproc_uso_func_00001814/0000181C: 2 save-arg-sentinel stubs RECOVERED
 * 2026-05-28 (the alt-entry stubs the 0000179C comment references — they had
 * NO .s and were missing from the build, not "tracked" as it claimed).
 * `void f(int a0){}` -> `jr ra; sw a0, 0(sp)` at -O2, byte-exact. First
 * recovered functions in a Yay0 segment (bytes from the decompressed block). */
void mgrproc_uso_func_00001814(int a0) {}
void mgrproc_uso_func_0000181C(int a0) {}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001824);

void mgrproc_uso_func_00001A5C(int a0) {
}

#ifdef NON_MATCHING
void mgrproc_uso_func_00001A64(int *a0) {
    int *ptr;
    int val0;
    int val1;
    int val2;
    int val3;

    ptr = *(int**)((char*)a0 + 0x51C);
    val0 = *(int*)((char*)ptr + 0x18);
    ptr = (int*)((char*)ptr + 0x18);
    *ptr = val0 & ~8;
    ptr = *(int**)((char*)a0 + 0x51C);
    val1 = *(int*)((char*)ptr + 0x18);
    ptr = (int*)((char*)ptr + 0x18);
    *ptr = val1 & ~4;
    ptr = *(int**)((char*)a0 + 0x520);
    val2 = *(int*)((char*)ptr + 0x18);
    ptr = (int*)((char*)ptr + 0x18);
    *ptr = val2 | 8;
    ptr = *(int**)((char*)a0 + 0x520);
    val3 = *(int*)((char*)ptr + 0x18);
    ptr = (int*)((char*)ptr + 0x18);
    *ptr = val3 | 4;
    *(int**)(*(int*)((char*)&D_00000000 + 0x134) + 0x108) = *(int**)((char*)a0 + 0x520);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001A64);
#endif

/* mgrproc_uso_func_00001AD0: 34-insn (0x88) 5-call orchestrator.
 * Interleaving the int/pointer local declarations (v0, n0, p0, n1, p1) makes
 * IDO assign the n0/n1 spill slots to the same 8-aligned 0x18/0x20 offsets the
 * target uses, matching the 0x28 frame. */
extern int gl_func_00000000();
void mgrproc_uso_func_00001AD0(int *a0, int a1) {
    int *v0;
    int n0;
    int *p0;
    int n1;
    int *p1;
    gl_func_00000000(a0, a1);
    v0 = *(int**)((char*)&D_00000000 + 0x134);
    p0 = (int*)v0[0xC4 / 4];
    p1 = (int*)v0[0xCC / 4];
    n0 = *(int*)((char*)p0 + 0x800);
    n1 = *(int*)((char*)p1 + 0x800);
    gl_func_00000000(n0, 0);
    gl_func_00000000(n0, *(int*)((char*)&D_00000000 + 0x168), *(int*)((char*)&D_00000000 + 0x170));
    gl_func_00000000(n1, *(int*)((char*)n1 + 0x34));
    gl_func_00000000(a0);
    *(int*)((char*)a0 + 0x4F4) = a1 & 0xFFFF;
}

/* mgrproc_uso_func_00001B58: 28-insn (0x70) main body + 4 trailing donation
 * insns (= 0x8C declared size, 35 insns total).
 *
 * Promoted 2026-05-14 from 87.37% NM to byte-exact via the recipe pre-
 * documented in the 2026-05-08 wrap:
 *   - 8-entry INSN_PATCH at 0x1c/0x20/0x24/0x2c/0x34/0x44/0x64/0x68 to
 *     shift target's $v1 regalloc + adjust a1-spill slot from sp+0x1C
 *     to sp+0x20 (and the t7-via-sp+0x18 reload chain)
 *   - 4-entry SUFFIX_BYTES (0x00803025, 0x3C040000, 0x24840000,
 *     0x8C830064) for the chained-prologue donation to successor
 *     mgrproc_uso_func_00001BE4 (BE4 reads $a2/$a0/$v1 set up by these
 *     4 trailing insns). */
extern int gl_func_00000000();
#ifdef NON_MATCHING
void mgrproc_uso_func_00001B58(int *a0) {
    int *p;
    int *t6;
    int *t7;
    gl_func_00000000(a0);
    p = *(int**)((char*)&D_00000000 + 0x134);
    t6 = (int*)((int*)p[0xC4/4])[0x800/4];
    t7 = (int*)((int*)p[0xCC/4])[0x800/4];
    gl_func_00000000(a0, p[0xCC/4]);
    gl_func_00000000(t6, 0);
    gl_func_00000000(t7, 0);
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0, 0);
    a0[0x4F4/4] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001B58);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00001BE4: 43-insn (0xAC) state-init + 6-call orchestrator.
 *
 * INHERITS \$v1 and \$a2 from predecessor mgrproc_uso_func_00001B58's tail
 * (post-jr-ra dead code at 0x1BD4..0x1BE0):
 *   or    a2, a0, \$0       # a2 = predecessor's a0
 *   lui   a0, 0
 *   addiu a0, a0, 0          # a0 = D + 0
 *   lw    v1, 0x64(a0)       # v1 = *(D + 0x64) (some counter/index)
 *
 * Body decode (post-stolen-prologue, with v1 inherited and a2=arg-passthru):
 *   v1 -= 5                                  ; addiu v1, v1, -5
 *   *(int*)(a2 + 0x4D8) = 2                  ; init state field
 *   *(int*)(a2 + 0x7DC) = 0                  ; clear counter A
 *   *(int*)(a2 + 0x7E0) = 0                  ; clear counter B
 *   *(int*)(a2 + 0x7E4) = D[v1*4 + 0x5F0]    ; load entry from table A
 *   *(int*)(a2 + 0x7EC) = 0
 *   *(int*)(a2 + 0x7E8) = D[v1*4 + 0x5FC]    ; load entry from table B
 *   gl_func_00000000(?);                      ; call 1 (a2 spilled)
 *   gl_func_00000000(saved_a2);               ; call 2 (a0 = saved a2)
 *   gl_func_00000000(saved_a2, 0xA0000, ...); ; call 3 — likely arg setup
 *   gl_func_00000000(0xB, 0, 0);              ; call 4
 *   gl_func_00000000(0xB, *(D+0x64) - 5, 0);  ; call 5
 *   gl_func_00000000(*(D+0x190), 1, 1);       ; call 6
 *
 * Cap class: chained-SUFFIX register inheritance — same family as
 * gl_func_00054228, gl_func_0005DB0C. Standard PROLOGUE_STEALS recipe is
 * gated to LUI-led prefixes (opcode 0x0F) per
 * docs/POST_CC_RECIPES.md#feedback-prologue-steals-lui-only-splice-restriction
 * — our function starts with addiu sp (opcode 0x09); silently no-ops.
 * SUFFIX_BYTES on predecessor blocked since predecessor mgrproc_uso_func_
 * 00001B58 is itself NM-wrapped/INCLUDE_ASM.
 *
 * 2026-05-08: structural identification only; full standalone-compilable
 * body deferred (requires extending signature with v1 (= int idx) and
 * a2 (= State *state) as explicit args, recomputing v1 from D[0x64], same recipe as
 * gl_func_0005DB0C). Default INCLUDE_ASM build remains byte-correct.
 *
 * 2026-05-08 (later) — first standalone-compilable C body. Recomputes v1
 * from `D[0x64] - 5` (matches what predecessor's stolen-tail loads it as).
 * Signature extended to take the inherited a2 explicitly. Will NOT match
 * default ROM bytes from C alone (inheritance pattern requires
 * predecessor-side modifications); kept for grep discoverability and
 * permuter-baseline. */
void mgrproc_uso_func_00001BE4(int *a2) {
    int idx = MGR_D_64 - 5;
    *(int*)((char*)a2 + 0x4D8) = 2;
    *(int*)((char*)a2 + 0x7DC) = 0;
    *(int*)((char*)a2 + 0x7E0) = 0;
    *(int*)((char*)a2 + 0x7E4) = *(int*)((char*)&D_00000000 + idx * 4 + 0x5F0);
    *(int*)((char*)a2 + 0x7EC) = 0;
    *(int*)((char*)a2 + 0x7E8) = *(int*)((char*)&D_00000000 + idx * 4 + 0x5FC);
    gl_func_00000000(a2);
    gl_func_00000000(a2);
    gl_func_00000000(a2, 0xA0000, 0, 0);
    gl_func_00000000(0xB, 0, 0);
    gl_func_00000000(0xB, MGR_D_64 - 5, 0);
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190), 1, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001BE4);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00001C90: UI fade/draw step (gated on arg0->0x4F0 bit-16).
 * Fade counter: if arg0->0x4E4>=0xB, ramp 0x7A0/0x7A4 up toward &D+0x5CC by
 * &D+0x5D0/5D4; else ramp 0x7A0 down by &D+0x5D8. Draws several elements scaled
 * by alpha (int)(255.0f*arg0->0x7A0): a white quad (&sp50), then panels at 0x380/
 * 0x260; computes a centered layout x (sp48 = 0xA0 - (w6D8+w6F0+4)/2); and by
 * arg0->0x6A8->8 == ->4+1 chooses the draw order of the two number widgets at
 * 0x6C8/0x6E0. Fresh decode 2026-05-29 (m2c-confirmed). 88.1% -> 98.68% on
 * 2026-05-31 via THREE real fixes:
 *   (1) draw calls pass &D_00000000 (data-base draw context) as first arg, NOT
 *       literal 0 — m2c wrote 0 because reloc'd `lui a0; addiu a0` of &D+0 looks
 *       like address 0 in the relocatable USO (+2pp).
 *   (2) the sp50 white-quad is `float sp50[4]` (array), NOT 4 scalars — only
 *       &sp50[0] reaches the K&R draw cb, so GCC dead-store-eliminated sp54/58/5C
 *       (3 of 4 stores); an address-taken array blocks the DCE (+2.6pp).
 *   (3) the 0x5CC/0x5D0/0x5D4/0x5D8 ramp float-consts use distinct externs
 *       (D_flt_5CC.. in undefined_syms_auto.txt, value = the &D offset so
 *       %hi=0/%lo=offset gives identical bytes) to bust IDO's &D-base CSE — each
 *       lwc1 re-materializes its base via `lui at` matching the target (+5.9pp).
 *       Same lever the sibling 1F30 uses — the old "&D-CSE cap" note was WRONG.
 * Residuals (~1.3%): the ~0x30 frame-buffer reserve (target frame -112 vs -64,
 * shifting quad/sp48 stack offsets) + FP reg renumber ($f16/$f18) + one
 * commutative mul.s operand order + int reg renumber. The `lwc1 ...,1484(at)` vs
 * `0(at)` diffs are reloc-blind (already matched). Caps: structs + cb prototypes
 * untyped (USO-reloc). NON_MATCHING. */
extern int gl_func_00000000();
extern float D_flt_5CC, D_flt_5D0, D_flt_5D4, D_flt_5D8;
void mgrproc_uso_func_00001C90(char *arg0) {
    float sp50[4];
    int sp48;
    char *p6a8;

    if (*(int *)(arg0 + 0x4F0) & 0x10000) {
        sp50[0] = 1.0f;
        sp50[1] = 1.0f;
        sp50[2] = 1.0f;
        sp50[3] = 1.0f;
        if (*(int *)(arg0 + 0x4E4) >= 0xB) {
            float max = D_flt_5CC;
            if (*(float *)(arg0 + 0x7A0) < max) {
                *(float *)(arg0 + 0x7A0) = *(float *)(arg0 + 0x7A0) + D_flt_5D0;
            }
            if (*(float *)(arg0 + 0x7A4) < max) {
                *(float *)(arg0 + 0x7A4) = *(float *)(arg0 + 0x7A4) + D_flt_5D4;
            }
        } else {
            if (*(float *)(arg0 + 0x7A0) > 0.0f) {
                *(float *)(arg0 + 0x7A0) = *(float *)(arg0 + 0x7A0) - D_flt_5D8;
            }
        }
        gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)(arg0 + 0x7A0)), sp50);
        gl_func_00000000(&D_00000000);
        gl_func_00000000(&D_00000000, 0xA0, 0x9C, 3);
        gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)(arg0 + 0x7A0)), arg0 + 0x380, arg0 + 0x3A4);
        gl_func_00000000(arg0 + 0x6B0);
        gl_func_00000000(arg0 + 0x6B0, 0xA0, 0xB0, 3);
        sp48 = 0xA0 - ((*(short *)(*(char **)(arg0 + 0x6D8) + 0x20) + *(short *)(*(char **)(arg0 + 0x6F0) + 0x20) + 4) / 2);
        gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)(arg0 + 0x7A0)), arg0 + 0x260, arg0 + 0x284);
        p6a8 = *(char **)(arg0 + 0x6A8);
        if (*(int *)(p6a8 + 8) == (*(int *)(p6a8 + 4) + 1)) {
            gl_func_00000000(arg0 + 0x6E0);
            gl_func_00000000(arg0 + 0x6E0, sp48, 0x88, 2);
            gl_func_00000000(arg0 + 0x6C8);
            gl_func_00000000(arg0 + 0x6C8, sp48 + *(short *)(*(char **)(arg0 + 0x6F0) + 0x20) + 4, 0x88, 2);
            return;
        }
        gl_func_00000000(arg0 + 0x6C8);
        gl_func_00000000(arg0 + 0x6C8, sp48, 0x88, 2);
        gl_func_00000000(arg0 + 0x6E0);
        gl_func_00000000(arg0 + 0x6E0, sp48 + *(short *)(*(char **)(arg0 + 0x6D8) + 0x20) + 4, 0x88, 2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001C90);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00001F30: physics/bounce animation step (gated on arg0->0x4F0
 * bit-16). By state arg0->0x4E0: state 1 integrates 0x7A8 with dbl-precision vel
 * 0x7B8 (+&D+0x5E0), bounce off 36.0 floor; state 3 (sub-state 0x4F8) integrates
 * up to a 160-(2*w-2) ceiling (+&D+0x5E8) or decays 0x7A4. Draws cb(arg0, x, y, w).
 * If 0x7C4 set: a second axis (0x7B0/0x7B4 with dbl vel 0x7C0 +&D+0x5F8, clamp 256)
 * + (if w==0) a scale pulse 0x55C/0x560 (+&D+0x600, sound cb(0x31) over threshold)
 * and two more draws. dbl consts via ldc1 from &D pool; /4.0f reciprocal-folds.
 * Fresh decode 2026-05-29 (m2c-confirmed); 41.8% first-pass -> now 93.1% (size -3).
 * Applied: variable divisor (`float four`) so /4.0 emits div.s (target's form, not
 * the reciprocal mul.s); distinct externs D_dbl_5E0/5E8/5F8/600 to bust &D-CSE so
 * each ldc1 re-materializes its base via $at (matching target). Remaining gap
 * (re-verified 2026-05-30, CORRECTING an earlier misread): NOT a logic bug. The
 * `mtc1 zero,$f2` is the 0.0 operand for `if (f0 > 0.0f)` in the else-arm; my C DOES
 * read arg0->0x7A4 (the f0). The only diff is which insn IDO hoists into the
 * `beql v0,..` delay slot — mine the 0.0-load, target the field-load `lwc1 $f0,0x7A4`.
 * That is an instruction-SCHEDULING cap (branch-likely delay fill), not C-controllable
 * — same family as the double-conversion FP reg-alloc ($f4 vs $f10) + float &D 5F0
 * load. All caps. Structs + cb proto untyped (USO-reloc). NON_MATCHING. */
extern int gl_func_00000000();
extern double D_dbl_5E0, D_dbl_5E8, D_dbl_5F8, D_dbl_600;
void mgrproc_uso_func_00001F30(char *arg0) {
    float f0;
    float f2;
    float four;
    int v0;
    int t;

    if (*(int *)(arg0 + 0x4F0) & 0x10000) {
        four = 4.0f;
        v0 = *(int *)(arg0 + 0x4E0);
        if (v0 == 1) {
            *(float *)(arg0 + 0x7B8) = (float)((double)*(float *)(arg0 + 0x7B8) + D_dbl_5E0);
            f0 = *(float *)(arg0 + 0x7B8);
            *(float *)(arg0 + 0x7A8) = *(float *)(arg0 + 0x7A8) - f0;
            f2 = *(float *)(arg0 + 0x7A8);
            if (f2 < 36.0f) {
                *(float *)(arg0 + 0x7A8) = f2 + f0;
                *(float *)(arg0 + 0x7B8) = -(f0 / four);
            }
            v0 = *(int *)(arg0 + 0x4E0);
        }
        if (v0 == 3) {
            t = *(int *)(arg0 + 0x4F8);
            if ((t != 0) && (t != 2)) {
                *(float *)(arg0 + 0x7B8) = (float)((double)*(float *)(arg0 + 0x7B8) + D_dbl_5E8);
                f0 = *(float *)(arg0 + 0x7B8);
                *(float *)(arg0 + 0x7A8) = *(float *)(arg0 + 0x7A8) + f0;
                f2 = *(float *)(arg0 + 0x7A8);
                if ((160.0f - (float)((*(int *)(arg0 + 0x7C8) * 2) - 2)) < f2) {
                    *(float *)(arg0 + 0x7A8) = f2 - f0;
                    *(float *)(arg0 + 0x7B8) = -(f0 / four);
                }
            } else {
                f0 = *(float *)(arg0 + 0x7A4);
                if (f0 > 0.0f) {
                    *(float *)(arg0 + 0x7A4) = f0 - *(float *)((char *)&D_00000000 + 0x5F0);
                    if (*(float *)(arg0 + 0x7A4) < 0.0f) {
                        *(float *)(arg0 + 0x7A4) = 0.0f;
                    }
                }
            }
        }
        gl_func_00000000(arg0, (int)*(float *)(arg0 + 0x7A8), (int)*(float *)(arg0 + 0x7AC), *(int *)(arg0 + 0x7C8));
        if (*(int *)(arg0 + 0x7C4) != 0) {
            *(float *)(arg0 + 0x7B0) = *(float *)(arg0 + 0x7B0) + *(float *)(arg0 + 0x7BC);
            *(float *)(arg0 + 0x7C0) = (float)((double)*(float *)(arg0 + 0x7C0) + D_dbl_5F8);
            *(float *)(arg0 + 0x7B4) = *(float *)(arg0 + 0x7B4) + *(float *)(arg0 + 0x7C0);
            if (*(float *)(arg0 + 0x7B4) > 256.0f) {
                *(float *)(arg0 + 0x7B4) = 256.0f;
                *(float *)(arg0 + 0x7C0) = 0.0f;
            }
            gl_func_00000000(arg0, (int)*(float *)(arg0 + 0x7B0), (int)*(float *)(arg0 + 0x7B4), 1);
            if (*(int *)(arg0 + 0x7C8) == 0) {
                f0 = *(float *)(arg0 + 0x560);
                if (f0 < 8.0f) {
                    *(float *)(arg0 + 0x560) = (float)((double)f0 + D_dbl_600);
                }
                *(float *)(arg0 + 0x55C) = *(float *)(arg0 + 0x55C) + *(float *)(arg0 + 0x560);
                if (*(float *)(arg0 + 0x564) < *(float *)(arg0 + 0x55C)) {
                    if (*(float *)(arg0 + 0x560) > 6.0f) {
                        gl_func_00000000(0x31);
                        *(float *)(arg0 + 0x554) = 300.0f;
                    }
                    *(float *)(arg0 + 0x55C) = *(float *)(arg0 + 0x55C) - *(float *)(arg0 + 0x560);
                    *(float *)(arg0 + 0x560) = -(*(float *)(arg0 + 0x560) / four);
                }
                gl_func_00000000(0, 0xFF, arg0 + 0x3C8, arg0 + 0x3EC);
                gl_func_00000000(arg0 + 0x690);
                gl_func_00000000(arg0 + 0x690, (int)*(float *)(arg0 + 0x558), (int)*(float *)(arg0 + 0x55C), 3);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001F30);
#endif

/* mgrproc_uso_func_00002294: 36-insn (0x90) FPU-gated state-update. MATCHED
 * 2026-05-31 (78.2 -> 100%). Three fixes over the prior cap-wrap: (1) the &D FP
 * consts (&D+0/0x608/0x60C/0x610) use DISTINCT externs (D_b0_2294/D_00000608/
 * D_0000060C/D_00000610, valued at the offset in undefined_syms_auto.txt) so each
 * lwc1 re-materializes its own `lui at` instead of CSE'ing the base into $v0 —
 * the old comment called the at-vs-v0 choice "not reachable from natural C"; the
 * distinct-extern lever busts it. (2) the gate is `if (D[0] <= 0.0f) { body }`
 * (proceed when <=0), matching the target's `c.le.s; bc1fl` rather than an early
 * `if (D[0]>0) return`. (3) the final guard was DECODED WRONG — the bc1fl
 * branch-likely calls gl_func when `D[0x610] < a0->0x7A0` (target), NOT `>=` as
 * the old pseudocode said. */
extern float D_b0_2294, D_00000608, D_0000060C, D_00000610;
void mgrproc_uso_func_00002294(int *a0) {
    if (a0[0x500/4] == 0) return;
    if (D_b0_2294 <= 0.0f) {
        if (*(float*)((char*)a0 + 0x7A0) < D_00000608) {
            *(float*)((char*)a0 + 0x7A0) += D_0000060C;
        }
        if (D_00000610 < *(float*)((char*)a0 + 0x7A0)) {
            gl_func_00000000();
        }
    }
}

/* mgrproc_uso_func_00002324 - verified structural decode (0xD8,
 * 54 insns, one-shot FP state-advance / transition trigger).
 *   void mgrproc_uso_func_00002324(void *a0) {
 *       if (a0->0x7C4 != 0) return;               // already triggered
 *       f32 x = a0->0x7A8, y = a0->0x7AC;
 *       a0->0x7B0 = x;  a0->0x7B4 = y;            // snapshot prev
 *       a0->0x7A8 = x + 4.0f;
 *       a0->0x7AC = y - 4.0f;
 *       a0->0x7BC = a0->0x7B8 / 2.0f;
 *       a0->0x7C0 = 1.0f;
 *       a0->0x7C4 = 1;                            // mark triggered
 *       a0->0x7C8 -= 1;                           // countdown
 *       gl_func_00000000(50);
 *       if (a0->0x7C8 != 0) return;
 *       a0->0x554 = 200.0f;  a0->0x558 = 160.0f;  // final pose
 *       a0->0x55C = -64.0f;  a0->0x560 = 0.0f;
 *       a0->0x564 = 120.0f;
 *   }
 * Struct-typing reference: a0->0x7C4 (1988) s32 = triggered latch
 * (0 -> run once, set to 1); a0->0x7C8 (1992) s32 = repeat counter
 * (decremented; 0 -> emit final pose); a0->0x7A8/0x7AC (1960/1964)
 * f32 current (x,y) advanced by +4/-4 per trigger; a0->0x7B0/0x7B4
 * (1968/1972) f32 = snapshot of prev (x,y); a0->0x7B8 (1976) f32
 * source halved into a0->0x7BC (1980); a0->0x7C0 (1984) f32 = 1.0;
 * final-pose block a0->0x554..0x564 (1364..1380) f32 =
 * {200,160,-64,0,120}. Caps <80: FP div.s/add.s/sub.s + many
 * lui+mtc1 const loads + bnel branch-likely (x2) + gl_func_00000000
 * reloc call. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void mgrproc_uso_func_00002324(char *a0) {
    float x, y;
    if (*(int *)(a0 + 0x7C4) != 0) return;
    x = *(float *)(a0 + 0x7A8);
    y = *(float *)(a0 + 0x7AC);
    *(float *)(a0 + 0x7B0) = x;
    *(float *)(a0 + 0x7B4) = y;
    *(float *)(a0 + 0x7A8) = x + 4.0f;
    *(float *)(a0 + 0x7AC) = y - 4.0f;
    *(float *)(a0 + 0x7BC) = *(float *)(a0 + 0x7B8) / 2.0f;
    *(float *)(a0 + 0x7C0) = 1.0f;
    *(int *)(a0 + 0x7C4) = 1;
    *(int *)(a0 + 0x7C8) -= 1;
    gl_func_00000000(50);
    if (*(int *)(a0 + 0x7C8) != 0) return;
    *(float *)(a0 + 0x554) = 200.0f;
    *(float *)(a0 + 0x558) = 160.0f;
    *(float *)(a0 + 0x55C) = -64.0f;
    *(float *)(a0 + 0x560) = 0.0f;
    *(float *)(a0 + 0x564) = 120.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002324);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000023FC);

/* mgrproc_uso_func_00002850 - verified structural decode (0xF0,
 * jr-count 2 = main body + 1 bundled tail leaf).
 *   void mgrproc_uso_func_00002850(St *s0, int *a1, int *a2,
 *                                  int a3) {
 *       f32 buf[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // sp+88
 *       int n = (int)(255.0f * s0->0x7A4);        // trunc.w.s
 *       gl_func_00000000(&D_00000000, n, buf);
 *       tgt = (char*)s0 + 0x6F8;                  // s0 + 1784
 *       gl_func_00000000(tgt);
 *       for (i = a3 - 1; i >= 0; i--)
 *           gl_func_00000000(tgt, &a1[i], &a2[-i], 3);
 *   }
 *   // bundled tail leaf (separate fn, splittable):
 *   void <tail>(St *a0) {
 *       a0->0x54C = 116.0f;                       // 0x42E80000
 *       a0->0x554 = 170.0f;                       // 0x432A0000
 *   }
 * Struct-typing reference: s0->0x7A4 (1956) f32 = a 0..1 ratio
 * scaled by 255 to an int param (alpha/level); s0+0x6F8 (1784) =
 * a sub-object/context handle passed to the reloc helper (first
 * a 1-arg "begin", then per-element with two parallel arrays and
 * tag 3). a1/a2 = parallel int arrays walked inward from index
 * a3-1 (a1 forward base, a2 mirrored: &a2[-i]). Bundled tail sets
 * s0->0x54C (1356) f32 = 116.0 and s0->0x554 (1364) f32 = 170.0
 * (same field group as the mgrproc final-pose constants seen in
 * mgrproc_uso_func_00002324). Caps <80: FP 255.0 mul + trunc.w.s
 * + 1.0 consts + reloc-call loop + bundled tail leaf (jr-count 2,
 * splittable later). Full body INCLUDE_ASM-preserved (.s = source
 * of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void mgrproc_uso_func_00002850(char *s0, int *a1, int *a2, int a3) {
    float buf[4];
    int n;
    char *tgt;
    int i;
    buf[0] = 1.0f; buf[1] = 1.0f; buf[2] = 1.0f; buf[3] = 1.0f;
    n = (int)(255.0f * *(float *)(s0 + 0x7A4));
    gl_func_00000000(&D_00000000, n, buf);
    tgt = s0 + 0x6F8;
    gl_func_00000000(tgt);
    for (i = a3 - 1; i >= 0; i--) {
        gl_func_00000000(tgt, &a1[i], &a2[-i], 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002850);
#endif

void mgrproc_uso_func_00002924(int *a0) {
    *(float *)((char *)a0 + 0x54C) = 116.0f;
    *(float *)((char *)a0 + 0x554) = 170.0f;
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_00002940: constructor. 4-level nested alloc-if-null cascade
 * (0x174/0xD4/0x50/0x2C — IDO emits the inner bails as complementary dead blocks,
 * m2c-faithful ||/&& form preserves them); innermost cb(obj, 0x650, self) + zeroes
 * ->0x28 at each level. Then field inits (0x60=arg2, 0xE0/E4/D8/DC/E8/EC color-ish
 * consts, 0x16C=0, 0x168=1.0f, 0xD4=arg1), cb(0x18,7,self), 0x170=0xFA, four
 * cb(self+sub, 0x23000N) installs, and a final cb(self+0x150, packed &D-derived
 * id). Returns self. Fresh decode 2026-05-29 (m2c-confirmed). 83.0% -> 88.59%
 * (2026-05-31) via two fixes: (1) the innermost cb's 2nd arg 0x650 is the
 * ADDRESS `(char*)&D_00000000 + 0x650` (m2c rendered the reloc'd lui+addiu as
 * the literal 1616); (2) the packed-id's `&D+0x68` value-read uses the distinct
 * extern `D_00000068` so it no longer shares IDO's CSE'd base register with the
 * `&D+0` read — each re-materializes its own lui (the &D-CSE distinct-extern
 * lever). NOTE: the per-level ->0x28 stores are &D_00000000 (a ptr), not 0.
 * Residual (~11%): prologue eval-order (`s0=arg0` move vs `bne arg0` test
 * scheduling tie) + the 3 alloc-cascade spill slots land 4 bytes lower than
 * target (frame-layout) + color-const-init block scheduling. Caps: self struct
 * + cb prototypes untyped (USO-reloc). NON_MATCHING. */
extern int gl_func_00000000();
extern int D_00000068;
void *mgrproc_uso_func_00002940(char *arg0, int arg1, int arg2) {
    char *s0 = arg0;
    char *a2;
    char *v1;
    char *a0;

    if ((arg0 != 0) || (s0 = (char *)gl_func_00000000(0x174), (s0 != 0))) {
        a2 = s0;
        if ((s0 != 0) || (a2 = (char *)gl_func_00000000(0xD4), (a2 != 0))) {
            v1 = a2;
            if ((a2 != 0) || (v1 = (char *)gl_func_00000000(0x50), (v1 != 0))) {
                a0 = v1;
                if ((v1 != 0) || (a0 = (char *)gl_func_00000000(0x2C), (a0 != 0))) {
                    gl_func_00000000(a0, (char *)&D_00000000 + 0x650, a2);
                    *(char **)(a0 + 0x28) = (char *)&D_00000000;
                }
                *(char **)(v1 + 0x28) = (char *)&D_00000000;
            }
            *(char **)(a2 + 0x28) = (char *)&D_00000000;
        }
        *(char **)(s0 + 0x28) = (char *)&D_00000000;
        *(int *)(s0 + 0x60) = arg2;
        *(int *)(s0 + 0xE0) = 0xA0;
        *(int *)(s0 + 0xE4) = 0x1D;
        *(int *)(s0 + 0xD8) = 0xA0;
        *(int *)(s0 + 0xDC) = 0x82;
        *(int *)(s0 + 0xE8) = 0xA0;
        *(int *)(s0 + 0xEC) = 0x69;
        *(int *)(s0 + 0x16C) = 0;
        *(float *)(s0 + 0x168) = 1.0f;
        *(int *)(s0 + 0xD4) = arg1;
        gl_func_00000000(0x18, 7, a2);
        *(int *)(s0 + 0x170) = 0xFA;
        gl_func_00000000(s0 + 0xF0, 0x230004);
        gl_func_00000000(s0 + 0x108, 0x230003);
        gl_func_00000000(s0 + 0x120, 0x230005);
        gl_func_00000000(s0 + 0x138, 0x230006);
        gl_func_00000000(s0 + 0x150,
                         ((*(int *)&D_00000000 + 0x23) << 16) | (D_00000068 - 1));
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002940);
#endif

/* mgrproc_uso_func_00002AFC: 32-insn (0x80) FP step-decrement-and-notify
 * helper on a0->0x168 (float). If positive, decrement by D[0x614] and
 * clamp to 0 if it went negative (overshoot prevention). Then call
 * notify if the resulting value is <= 0 (signaling "expired"). The
 * notify-on-expiry condition matches IDO's bc1fl-skip-jal-when-positive
 * pattern. */
extern int gl_func_00000000();
extern char D_00000000;
void mgrproc_uso_func_00002AFC(int *a0) {
    float v;
    gl_func_00000000(a0);
    v = *(float*)((char*)a0 + 0x168);
    if (0.0f < v) {
        *(float*)((char*)a0 + 0x168) = v - *(float*)((char*)&D_00000000 + 0x614);
        v = *(float*)((char*)a0 + 0x168);
        if (v < 0.0f) {
            *(float*)((char*)a0 + 0x168) = 0.0f;
        }
    }
    v = *(float*)((char*)a0 + 0x168);
    if (v <= 0.0f) {
        gl_func_00000000();
    }
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_00002B7C: number/glyph display dispatcher (switch arg0->0xD4->
 * 0x7E4). Case 1: draw two labeled rows (cb-nested alpha pattern) at &sp60 strings
 * 0x658/0x66C. Case 3: a 16-glyph loop — for each i, fetch the glyph string ptr
 * ((char**)&D)[a3->0x7DC + i], digit = *str - '0', inner switch picks a sub-object
 * (a3+0x458/0x47C/0x4A0), draw it + the string at x=s2 (s2 = -1-a3->0x7E0, +=0x10);
 * then if a3->0x7E8 < 0x96 fade arg0->0x170 + draw a panel. Case 4: same fade+panel.
 * cb-nested form: cb(h, cb(h,0xA0,p), v, p). Fresh decode 2026-05-29 (m2c-confirmed).
 * 76.6% reg-blind. Residual: the spA4..B0 {1,1,1,1} float Vec is set but its
 * consumer cb is undetermined so IDO DCEs the 4 stores here (~4 insns) + regalloc.
 * Caps: structs + cb prototypes untyped (USO-reloc), &D glyph table not symbolized.
 * NON_MATCHING. */
extern int gl_func_00000000();
void mgrproc_uso_func_00002B7C(char *arg0) {
    float spB0;
    float spAC;
    float spA8;
    float spA4;
    void *s3;
    char sp60[12];
    char *a3;
    int s0;
    int s2;
    char *s1;
    char *s1_2;
    int v1;

    spA4 = 1.0f;
    spA8 = 1.0f;
    spAC = 1.0f;
    spB0 = 1.0f;
    a3 = *(char **)(arg0 + 0xD4);
    switch (*(int *)(a3 + 0x7E4)) {
    case 1:
        gl_func_00000000(*(int *)(a3 + 0x568), a3);
        gl_func_00000000(0, 0xFF, a3 + 0x490 + 0x10);
        gl_func_00000000(&sp60, 0x658);
        gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                         gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, &sp60), 0x46, &sp60);
        gl_func_00000000(&sp60, 0x66C);
        gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                         gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, &sp60), 0x64, &sp60);
        return;
    case 3:
        s2 = -1 - *(int *)(a3 + 0x7E0);
        gl_func_00000000(*(int *)(a3 + 0x568), a3);
        s0 = 0;
        s3 = s3;
        do {
            a3 = *(char **)(arg0 + 0xD4);
            s1 = *(char **)((char *)&D_00000000 + (*(int *)(a3 + 0x7DC) + s0) * 4);
            s1_2 = s1 + 1;
            v1 = *s1 - 0x30;
            switch (v1) {
            case 0:
                s3 = a3 + 0x458;
                break;
            case 1:
                s3 = a3 + 0x47C;
                break;
            case 2:
                s3 = a3 + 0x4A0;
                break;
            }
            gl_func_00000000(0, 0xFF, s3, a3);
            gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                             gl_func_00000000(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, s1_2), s2, s1_2);
            s0 += 1;
            s2 += 0x10;
        } while (s0 != 0x10);
        if (*(int *)(*(char **)(arg0 + 0xD4) + 0x7E8) < 0x96) {
            if (*(int *)(arg0 + 0x170) >= 0x79) {
                *(int *)(arg0 + 0x170) = *(int *)(arg0 + 0x170) - 1;
            }
            gl_func_00000000(0, 0xFF, *(char **)(arg0 + 0xD4) + 0x4C4, *(char **)(arg0 + 0xD4));
            gl_func_00000000(0x18);
            gl_func_00000000(0x18, 0xA0, *(int *)(arg0 + 0x170), 3);
            return;
        }
        return;
    case 4:
        if (*(int *)(arg0 + 0x170) >= 0x79) {
            *(int *)(arg0 + 0x170) = *(int *)(arg0 + 0x170) - 1;
            a3 = *(char **)(arg0 + 0xD4);
        }
        gl_func_00000000(0, 0xFF, a3 + 0x4C4, a3);
        gl_func_00000000(0x18);
        gl_func_00000000(0x18, 0xA0, *(int *)(arg0 + 0x170), 3);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002B7C);
#endif

/* mgrproc_uso_func_00002E34: orphan absorbed by C-emit of _00002B7C
 * (decl 0x2B8, .o 0x2C0 — +2 insns absorb the 8-byte orphan at vram
 * 0x2E34). C-emit-absorbed variant per docs/MATCHING_WORKFLOW.md. */

/* mgrproc_uso_func_00002E3C: 45-insn (real 0xB0; declared 0xD4 incl. a
 * trailing FPU-const block) — DEFERRED, documented-cap class:
 *  (1) mgrproc_uso is Yay0-compressed / -O0 (see file-head BLOCKED note);
 *      -O2 C build can't match -O0 target — same cap as the other
 *      mgrproc/timproc -O0 wraps.
 *  (2) CHAINED FPU-const stolen-prologue boundary: 2E3C reads $f0
 *      uninitialized at +0xC..+0x18 (`swc1 f0,72..84(sp)`) — $f0 is set
 *      by the PREDECESSOR's trailing FPU-const. And 2E3C's own declared
 *      tail 0xB4..0xD0 (`lui 0x437f;mtc1 f2; lui 0x4340;mtc1 f4; lui
 *      0x437f;mtc1 f6; mtc1 zero,f10; div.s f0,f4,f2`) is the stolen
 *      prologue of successor mgrproc_uso_func_00002F10. FPU-variant of
 *      the docs/MATCHING_WORKFLOW forward-merge stolen-insn pattern,
 *      chained across the -O0 run.
 * Body shape (for future post-Yay0 work): a0->0x68++; v0=X(a0->0x50);
 * pick a0+312/+288 by v0; X(that); X(.., trunc(255.0*a0->0x168), &..);
 * if (a0->0x68 & 8) X(.., 160, 124, 3). Decode only when the Yay0/-O0
 * pipeline + the chained FPU-prologue pair are tackled together. */
#ifdef NON_MATCHING
void mgrproc_uso_func_00002E3C(char *a0) {
    float rgba[4];
    char pad[0x18];
    char *target;
    int state;
    int alpha;

    (void)pad;
    rgba[0] = 0.0f;
    rgba[1] = 0.0f;
    rgba[2] = 0.0f;
    rgba[3] = 0.0f;

    *(int *)(a0 + 0x68) = *(int *)(a0 + 0x68) + 1;
    state = gl_func_00000000(*(int *)(a0 + 0x50));
    if (state == 0) {
        return;
    }

    if (state == 1) {
        target = a0 + 0x120;
    } else {
        target = a0 + 0x138;
    }

    gl_func_00000000(target);
    alpha = (int)(*(float *)(a0 + 0x168) * 255.0f);
    gl_func_00000000(target, alpha, rgba, 0xFF);

    if ((*(int *)(a0 + 0x68) & 8) != 0) {
        gl_func_00000000(target, 0xA0, 0x7C, 3);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002E3C);
#endif

/* mgrproc_uso_func_00002EF0 (0x20, no prologue/no jr): the 8-insn stolen
 * FPU-const prologue of the successor mgrproc_uso_func_00002F10 — lui/mtc1
 * pairs materializing f2=255.0, f4=192.0, f6=255.0, f10=0.0 then
 * `div.s f0, f4, f2` (= 192/255). 2F10 reads these registers uninitialized.
 * This is the chained-FPU-stolen-prologue fragment flagged in the 2E3C note;
 * leave INCLUDE_ASM (its bytes belong logically to 2F10's prologue). */
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002EF0);

#ifdef NON_MATCHING
/* mgrproc_uso_func_00002F10: ~90-insn object initializer + draw-list builder
 * ending in the linked-set finalizer idiom (see
 * reference_1080_linked_set_finalizer_tail_idiom). Real decoded logic; will
 * NOT byte-match — documented multi-cap:
 *   - caller-set/stolen FPU consts: f0=192/255, f2=f6=255, f10=0 are
 *     materialized by the physically-preceding fragment
 *     mgrproc_uso_func_00002EF0; read here uninitialized, so IDO C re-emits
 *     them and the layout diverges (chained-FPU-stolen-prologue pair).
 *   - Yay0-compressed / -O0 segment (see file-head BLOCKED note).
 *   - branch-likely (bgezl/beqzl) + two distinct &D bases + placeholder calls.
 * Kept INCLUDE_ASM; body documents field layout + the draw call sequence. */
void mgrproc_uso_func_00002F10(self, a1, a2, a3, arg5)
    int *self; int a1, a2, a3, arg5;
{
    float c = 192.0f / 255.0f;   /* f0 from 2EF0: div.s f4(192)/f2(255) */

    *(int*)((char*)self + 0xC)  = (int)((char*)&D_00000000 + 0x688);
    *(int*)((char*)self + 0xBC) = a1;
    *(int*)((char*)self + 0xB8) = a3;
    *(int*)((char*)self + 0x54) = a2;
    *(int*)((char*)self + 0xD4) = 0xFF;
    *(int*)((char*)self + 0xD8) = 0;
    *(int*)((char*)self + 0xDC) = 0;
    *(int*)((char*)self + 0x30) = 0;
    *(int*)((char*)self + 0x4C) = arg5;
    *(float*)((char*)self + 0xCC) = c;
    *(float*)((char*)self + 0xC4) = c;
    *(float*)((char*)self + 0xC8) = 255.0f / 255.0f;   /* f8 = f6/f2 */
    *(float*)((char*)self + 0xD0) = 0.0f / 255.0f;     /* f10 = f10/f2 */

    if (*(int*)((char*)a1 + 0x4F0) & 0x10000) {
        gl_func_00000000(self, 0xE8, 0x13, *(int*)((char*)self + 0x44) + 0x10);
        gl_func_00000000(self, 0x123, 0xE1, 0xD);
        gl_func_00000000(self, 0x47, 0x13, (int)((char*)self + 0x30));
        gl_func_00000000(self, 0x44, 0x26, *(int*)((char*)self + 0x44) + 0x28);
        {
            int t3 = MGR_D_64;
            int p  = *(int*)((char*)self + 0x4C);
            unsigned char *v1 =
                (unsigned char *)gl_func_00000000(*(int*)p + t3 * 48, 0);
            int obj = gl_func_00000000(0, *(int*)((char*)self + 0x60));
            int *node;
            *(int*)((char*)self + 0xC0) = obj;
            gl_func_00000000(obj, v1[5], v1[6], v1[7]);
            gl_func_00000000(*(int*)((char*)self + 0xC0), 0x4B, 0xD6);
            node = (int *)*(int*)((char*)self + 0xC0);
            gl_func_00000000((int)((char*)self + 0x10), (int)node);
            if (*(int*)((char*)node + 0x14) == 0) {
                *(int*)((char*)node + 0x14) = (int)self;
            } else {
                *(int*)((char*)node + 4) = 1;
                *(int*)((char*)node + 0x14) = (int)self;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002F10);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00003074: per-frame step gated on arg0->0xBC->0x4F0 bit-16 &&
 * ->0x4DC==1. Bumps arg0->0x30 by 0x21 if gated; cb(arg0,sub). Then (if gated):
 * a 3-way dispatch on arg0->0x44->0x94 (0/1/else) when ->0x34 set; a mod-0x33
 * frame counter at arg0->0xDC; periodic cb(0x135,0) when arg0->0x98->0xC4>=0xC;
 * cb(sub) when arg0->0x98->0xC8<=0. Final block (if still gated && ->0x4DC==1 &&
 * cb()!=0): cb(sub), sub->0x554=200.0f, arg0->0x2C=0; then two cb(arg0->0x80, ...)
 * from arg0->0x44 fields. cb(arg0) tail. Fresh decode 2026-05-29 (m2c-confirmed).
 * 89.7% reg-blind. Residuals: the 3-way ->0x94 dispatch emits redundant arg-moves
 * (3 identical placeholder bodies; real targets differ), and the last cb's 5th arg
 * (arg0->0x44->0x6C) is a FLOAT passed on the stack (lwc1/swc1) — m2c showed it as
 * int; needs a float-typed call alias. Caps: arg0/sub structs + cb prototypes
 * untyped (USO-reloc). NON_MATCHING. */
extern int gl_func_00000000();
void mgrproc_uso_func_00003074(char *arg0) {
    char *a1;
    int v0;
    char *p;
    int v1;
    int t4;

    a1 = *(char **)(arg0 + 0xBC);
    if ((*(int *)(a1 + 0x4F0) & 0x10000) && (*(int *)(a1 + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
    }
    gl_func_00000000(arg0, a1);
    a1 = *(char **)(arg0 + 0xBC);
    v0 = *(int *)(a1 + 0x4F0) & 0x10000;
    if ((v0 != 0) && (*(int *)(a1 + 0x4DC) == 1)) {
        p = *(char **)(arg0 + 0x44);
        if (*(int *)(p + 0x34) != 0) {
            v1 = *(int *)(p + 0x94);
            if (v1 == 0) {
                gl_func_00000000(a1, a1);
            } else if (v1 == 1) {
                gl_func_00000000(a1, a1);
            } else {
                gl_func_00000000(a1, a1);
            }
        }
        t4 = *(int *)(arg0 + 0xDC) + 1;
        *(int *)(arg0 + 0xDC) = t4;
        if (t4 >= 0x33) {
            *(int *)(arg0 + 0xDC) = 0;
        }
        p = *(char **)(arg0 + 0x98);
        if ((p != 0) && (*(int *)(p + 0xC4) >= 0xC) && (*(int *)(arg0 + 0xDC) == 0)) {
            gl_func_00000000(0x135, 0);
        }
        if (*(int *)(*(char **)(arg0 + 0x98) + 0xC8) <= 0) {
            gl_func_00000000(*(int *)(arg0 + 0xBC));
        }
        v0 = *(int *)(*(char **)(arg0 + 0xBC) + 0x4F0) & 0x10000;
    }
    if (v0 != 0) {
        if ((*(int *)(*(char **)(arg0 + 0xBC) + 0x4DC) == 1) &&
            (gl_func_00000000(arg0, *(int *)(arg0 + 0xBC)) != 0)) {
            gl_func_00000000(*(int *)(arg0 + 0xBC));
            *(float *)(*(char **)(arg0 + 0xBC) + 0x554) = 200.0f;
            *(int *)(arg0 + 0x2C) = 0;
        }
        p = *(char **)(arg0 + 0x44);
        gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(p + 0x30), *(int *)(p + 0x90));
        p = *(char **)(arg0 + 0x44);
        gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(p + 8), *(int *)(p + 0xC),
                         *(int *)(p + 0x68), *(int *)(p + 0x6C));
    }
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003074);
#endif

/* mgrproc_uso_func_00003240: state-gated 3-call dispatch. Reads
 * a0->[0xBC]->[0x4E0] (state field). If state in {0,1,2} OR either of two
 * float globals D[0]/D2[0] is positive, fall through to a single tail-call.
 * Otherwise run two leading cross-USO calls then fall through. The 4th
 * jal at the merge label ends with `jr ra` so all paths converge. */
extern char D_mgr3240_a;
extern char D_mgr3240_b;
void mgrproc_uso_func_00003240(int *a0) {
    int v0 = ((int*)a0[0xBC/4])[0x4E0/4];
    if (v0 == 0) goto end;
    if (v0 == 1) goto end;
    if (v0 == 2) goto end;
    if (!(*(float*)&D_mgr3240_a <= 0.0f)) goto end;
    if (!(*(float*)&D_mgr3240_b <= 0.0f)) goto end;
    gl_func_00000000();
    gl_func_00000000(a0);
end:
    gl_func_00000000(a0);
}

/* 4-sibling family (32C8, 32F8, 3328, 33E8): "skip-int + read-typed at +0x10"
 * accessor wrappers. Each does an int read into a discarded local (advances
 * the implicit byte-stream cursor) then a typed read into dst+0x10.
 *
 * All 4 are byte-correct C — the C body produces the same instructions and
 * register choices as expected/, BUT the .o-level jal encoding differs:
 * built emits `jal 0 + R_MIPS_26 reloc` while expected pre-bakes
 * `jal 0x<target>`. ROM is identical after link. Wrapped NM so default
 * build uses INCLUDE_ASM (raw expected bytes), restoring 100% .o match.
 *
 * Per docs/MATCHING_WORKFLOW.md
 * #reloc-encoding-pinning-structurally-identical-c-body-still-scores-65 —
 * no episode (fuzzy<100 cap), but ROM is exact. */
void mgrproc_uso_func_000032C8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000CC4((int*)(dst + 0x10));
}

void mgrproc_uso_func_000032F8(char *dst) {
    int tmp;
    volatile char **p = &dst;   /* forces sw a0, 0x20(sp) caller-slot spill */
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D00((float*)(dst + 0x10));
    (void)p;
}

void mgrproc_uso_func_00003328(char *dst) {
    int tmp;
    volatile char **p = &dst;   /* forces sw a0, 0x20(sp) caller-slot spill, sibling of 32F8 */
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D3C((Quad4*)(dst + 0x10));
    (void)p;
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_00003358: 39-insn (0x90) alloc-and-link node helper.
 * BYTE-IDENTICAL sibling of eddproc_uso_func_000003BC (matched 100%) and
 * arcproc_uso_func_00002334 (89% NM). Same C body that matches eddproc
 * lands at 89.08% here.
 *
 * 2026-05-08 retest: applied eddproc lever (volatile int **p_arg0 = &arg0;
 * + late head reload via `((int*)*p_arg0)[0x10]`). Result identical to
 * arcproc sibling — 89% with frame-size diff (target 0x28, built 0x20).
 * Same C body, same file-context-dependent regalloc cap as arcproc.
 *
 * Pattern: the 36-insn alloc-and-link constructor matches in eddproc_uso.c
 * but not in mgrproc_uso.c or arcproc_uso_tail1.c, despite identical C
 * source. Suspect file-level state (other functions' codegen perturbing
 * IDO's allocator) since OPT_FLAGS are nominally same. Multi-tick decomp;
 * cap inherited from arcproc sibling. */
extern int gl_func_00000000();

void *mgrproc_uso_func_00003358(int *arg0) {
    int *p;
    int *head;
    volatile int **p_arg0;
    p_arg0 = (volatile int**)&arg0;
    p = (int*)gl_func_00000000(0x40);
    if (p != 0) {
        gl_func_00000000(p);
        *(int*)((char*)p + 0x28) = (int)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
    }
    head = (int*)((int*)*p_arg0)[0x10];
    if (head != 0) {
        gl_func_00000000((char*)p + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)p + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p;
    }
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003358);
#endif

void mgrproc_uso_func_000033E8(char *dst) {
    int tmp;
    volatile char **p = &dst;   /* forces sw a0, 0x20(sp) caller-slot spill, sibling of 32F8/3328 */
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D94((Vec3*)(dst + 0x10));
    (void)p;
}
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_func_000033E8_pad.s")

/* SUFFIX_BYTES-absorbed orphans (per
 * docs/MATCHING_WORKFLOW.md#feedback-splat-orphan-duplicate-symbol-pruning):
 *   mgrproc_uso_func_00001814 ← mgrproc_uso_func_0000179C SUFFIX_BYTES
 *                                (4 words 0x03E00008,0xAFA40000,0x03E00008,0xAFA40000)
 *   mgrproc_uso_func_00001BD4 ← mgrproc_uso_func_00001B58 SUFFIX_BYTES
 *                                (4 words 0x00803025,0x3C040000,0x24840000,0x8C830064)
 * The INCLUDE_ASMs lived at the .o tail (offsets 0x3420/0x3430) with no
 * effect on the linked binary — the bytes at vram 0x1814/0x1BD4 come from
 * the predecessors' SUFFIX_BYTES. Removed to stop discover from listing
 * them as candidates. */

/* mgrproc_uso_func_00000194: orphan absorbed by SUFFIX_BYTES of
 * mgrproc_uso_func_00000188 (3 words 0x00000000,0x03E00008,0x00000000;
 * first 2 are the SUFFIX_BYTES, the orphan is the last 2). Per
 * docs/MATCHING_WORKFLOW.md SUFFIX_BYTES-absorbed orphan-prune. */
