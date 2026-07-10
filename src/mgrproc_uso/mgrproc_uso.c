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

mgrproc_uso_func_00000AE0() {
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
extern int import_80263D60;
extern int import_80020098[];
extern int import_000A5A1C();
extern int import_000A5938();
extern int mgrproc_uso_func_01FA1C();
extern int mgrproc_uso_func_00F954();
/* mgrproc_uso_func_00000B5C: 46-insn (0xB8) state-update with cond branch.
 * Sibling of mgrproc_uso_func_00000C14 — identical control structure, same
 * state-slot (&import_80263D60 + 0x30) and `other` base (&import_80020098),
 * different constants. True-arm: [0x504]=0; [0x4E0]=7; other[0x40]=5;
 * other[0x44]=3; [0x7D8]=1; import_000A5938(state). FALSE-arm: other[0x40]=3;
 * mgrproc_uso_func_00F954(state, 4, state->[0x6A8]->[0xC]).
 *
 * 2026-07-03 (agent-e): 38/46 raw words (was 45-word UNDER-decode: form-b state
 * loads + FALSE-arm args swapped). Rewritten to the cracked 00C14 form-a shape:
 *  - state slot via pointer-MUTATION if(1) barrier (pp=&import_80263D60;
 *    if(1){pp+=0xC;}) → form-a `lui;addiu v1,0x30;lw 0(v1)` w/ v1 reused per
 *    region; 4 aliasing `lw 0(v1)` reloads in the true arm.
 *  - `other` base held in ONE reg via `extern int import_80020098[]` direct index.
 *  - FALSE-arm state hoisted into a local (`int *st=*pp`) so `lw a0` loads BEFORE
 *    the `other[0x40]=3` store — false arm now 13/13 EXACT; front reloc pair,
 *    beqz/b displacements, and both call regions all EXACT.
 *  RESIDUAL (8 words = same irreducible if(1)-barrier scheduling cap as 00C14):
 *   (A) region-1 `sw ra` schedules between lui/addiu (target: after addiu) — 2 wds.
 *   (B) true-arm: with correct REGISTERS (other=v0, 0x7D8-reload=t4) the `li t9,7`
 *       and the 0x7D8 reload emit un-hoisted (li/lui swap + reload 3 slots late) —
 *       6 wds. Hoisting via a named temp (s3=*pp) fixes the SCHEDULE perfectly but
 *       steals v0 (other→a3, reload→v0) → still 6. Can't have form-a schedule AND
 *       the natural coloring; the if(1) barriers that force form-a perturb as1/uopt
 *       exactly here. Default build INCLUDE_ASM. */
void mgrproc_uso_func_00000B5C(void) {
    int **pp;
    int v0;
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    import_000A5A1C(*pp);
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    v0 = mgrproc_uso_func_01FA1C(*(int *)((char *)((int **)*pp)[0x6AC / 4] + 0x4C));
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    if (v0 != 0) {
        (*pp)[0x504 / 4] = 0;
        (*pp)[0x4E0 / 4] = 7;
        import_80020098[0x40 / 4] = 5;
        import_80020098[0x44 / 4] = 3;
        (*pp)[0x7D8 / 4] = 1;
        import_000A5938(*pp);
    } else {
        int *st = *pp;
        import_80020098[0x40 / 4] = 3;
        mgrproc_uso_func_00F954(st, 4, *(int *)((char *)*(int **)((char *)st + 0x6A8) + 0xC));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000B5C);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00000C14: 44-insn (0xB0) state-update with conditional
 * branch. state = *(int**)(&import_80263D60 + 0x30) (global state ptr);
 * queries import_01FA1C(state->[0x6AC]->[0x4C]) and based on result either:
 *   - cond TRUE: clear state[0x504], state[0x4E0]=7, other[0x40]=5,
 *                other[0x44]=7, state[0x7D8]=1, call import_000A5938(state)
 *   - cond FALSE: other[0x40]=7, call mgrproc_uso_func_00F954(state, 0, 0)
 *   where other = &import_80020098.
 *
 * SYMBOLS RE-DERIVED 2026-06-20: the prior body used gl_func_00000000 /
 * D_C14_state / D_00000000 placeholders (relocs all WRONG). The four calls
 * are DISTINCT real targets (import_000A5A1C, import_01FA1C, import_000A5938,
 * mgrproc_uso_func_00F954) and the two bases are DISTINCT imports
 * (import_80263D60+0x30 = state-storage, import_80020098 = `other`). Body
 * below now emits the correct relocs + the 6 fresh `lw 0(v1)` state reloads
 * IDO uses (no CSE across the call/if boundaries) — front + reload count + all
 * struct offsets are byte-exact except for the cap below.
 *
 * 2026-07-03 (agent-e): 40/44 raw words (was 17/44). Both prior "caps" CRACKED:
 *  (1) LO16-FOLD on the state slot — target `lui v1,%hi; addiu v1,v1,0x30;
 *      lw 0(v1)` (form-a, 0x30 in the addiu). At -O2 `&sym+0x30` ALWAYS folds
 *      to form-b (`addiu %lo; lw 0x30`). FIX: pointer MUTATION in an `if(1)`
 *      barrier — `pp=(int**)&import_80263D60; if(1){pp+=0xC;}` per region.
 *      Mutation commits +0x30 to the addiu (form-a); the `if(1)` blocks IDO's
 *      cross-call CSE so pp rematerializes (lui+addiu) each region instead of
 *      spilling. (Plain mutation spills; struct/array/`&sym+K` all fold.)
 *  (2) `other` base held in $a3 + const-7 CSE — FIX: declare import_80020098
 *      as `extern int[]` and index it DIRECTLY (array-decay holds the base in
 *      one reg; the scalar `int *other=&sym` form refolds `lui at` per store).
 *  RESIDUAL (4 words = genuine as1/uopt SCHEDULING cap, coupled to form-a):
 *  the `if(1)` barrier introduces basic-block boundaries that perturb the
 *  scheduler in exactly 2 spots — (A) region-1 `sw ra` lands between lui/addiu
 *  (bb-split; target puts it after the addiu); (B) the 0x7D8 state reload
 *  (`lw t2`) schedules after the two `other` stores (target hoists it before).
 *  The struct/natural-global form schedules BOTH perfectly but folds to form-b
 *  (10 words + wrong baked bytes). Can't have form-a AND the natural schedule.
 *  Default build INCLUDE_ASM. */
extern int import_80263D60;
extern int import_80020098[];
extern int import_000A5A1C();
extern int import_000A5938();
extern int mgrproc_uso_func_01FA1C();
extern int mgrproc_uso_func_00F954();
void mgrproc_uso_func_00000C14(void) {
    int **pp;
    int v0;
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    import_000A5A1C(*pp);
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    v0 = mgrproc_uso_func_01FA1C(*(int *)((char *)((int **)*pp)[0x6AC / 4] + 0x4C));
    pp = (int **)&import_80263D60; if (1) { pp += 0xC; }
    if (v0 != 0) {
        (*pp)[0x504 / 4] = 0;
        (*pp)[0x4E0 / 4] = 7;
        (*pp)[0x7D8 / 4] = (import_80020098[0x40 / 4] = 5, import_80020098[0x44 / 4] = 7, 1);
        import_000A5938(*pp);
    } else {
        import_80020098[0x40 / 4] = 7;
        mgrproc_uso_func_00F954(*pp, 0, 0);
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

#ifdef NON_MATCHING
/* mgrproc_uso_func_00000E04: 0x396-byte constructor. SYMBOLS RE-DERIVED
 * 2026-06-23 from the resolved .s — the prior body used gl_func_00000000 /
 * single-`d`(&D_00000000) placeholders (all relocs WRONG). Real form:
 *  - 4-stage find-or-create cascade (sizes 2032/1704/80/44), collapses to obj
 *    since arg!=0; returns obj (move v0,s0 in epilogue).
 *  - Each vtable/base reference is a DISTINCT USO data import
 *    (import_80XXXXXX, value 0 in undefined_syms) referenced as
 *    `(char*)&sym + off` / `*(T*)(&sym + off)`. Each distinct char-symbol
 *    keeps its own unpaired-HI16 lui (offset folded into the addiu/lw/sw
 *    displacement, no LO16) — the B20/12AC matched idiom. One shared base
 *    would CSE the luis and emit paired HI16+LO16.
 *  - All cross-USO calls are DISTINCT named targets (import_000XXXXX /
 *    mgrproc_uso_func_XXXXXX), not a single gl_func placeholder.
 * 75.19 -> 76.67 (objdiff fuzzy). All R_MIPS_26 call relocs + struct offsets
 * + control flow byte-exact. Residual (~23%) is genuine IDO regalloc/scheduling
 * divergence, NOT logic: (1) frame 0x40 vs 0x58 — target threads the 4-stage
 * cascade through a single $a3 + stack temps 0x38/0x3c; build keeps o0..o3 in
 * more slots (~100 register-renumber + frame diffs cascade from this).
 * (2) record-flag blocks: target emits beqzl (likely, store hoisted+dup) for
 * the 2nd/3rd `if(rec[0x14]){rec[4]=1;} rec[0x14]=o0;` but plain beqz for the
 * 1st — IDO scheduler-tie, identical C, no source lever. (3) a few
 * &import+offset refs render as %hi+0x608 addend vs target's addend-0 lui +
 * literal addiu (byte-identical low-half, objdiff-flagged only). K&R param
 * style tested = no change. Genuine coloring/scheduling cap. */
extern int mgrproc_uso_func_055750();
extern int import_000AE700();
extern int import_000B0DBC();
extern int import_000A7ECC();
extern int import_000B6C40();
extern int import_000A5D38();
extern int import_000A5F40();
extern int import_000A69BC();
extern int import_000A5FBC();
extern int mgrproc_uso_func_04C678();
extern void mgrproc_uso_func_0000119C();
extern int mgrproc_uso_func_074710();
extern void mgrproc_uso_func_00002EF0();
extern int mgrproc_uso_func_07ACE0();
extern int mgrproc_uso_func_01B0F8();
extern int mgrproc_uso_func_0139B0();
extern int mgrproc_uso_func_074840();
extern char import_802649D8;
extern char import_80073B18;
extern char import_80073B80;
extern char import_800745F8;
extern char import_80264880;
extern char import_802649E0;
extern char import_802649F0;
extern int import_80020098[];
extern char import_80264800;
extern char import_800201D0;
extern char import_8002022C;
extern char import_80265570;
extern char import_802655B0;
extern char import_802655EC;
extern char import_802656A4;
extern int import_80020228;
extern char import_800200D8;
void mgrproc_uso_func_00000E04(char *obj, int a1, int a2, int a3, int arg5) {
    char *o0, *o1, *o2, *o3;
    char *w;
    float f0 = 0.0f;
    int n;

    o0 = obj;
    if (obj == 0) {
        o0 = (char *)mgrproc_uso_func_055750(2032);
        if (o0 == 0) return;
    }
    o1 = o0;
    if (o0 == 0) {
        o1 = (char *)mgrproc_uso_func_055750(1704);
        if (o1 == 0) goto Lvt0;
    }
    o2 = o1;
    if (o1 == 0) {
        o2 = (char *)mgrproc_uso_func_055750(80);
        if (o2 == 0) goto Lvt1;
    }
    o3 = o2;
    if (o2 == 0) {
        o3 = (char *)mgrproc_uso_func_055750(44);
        if (o3 == 0) goto Lvt2;
    }
    mgrproc_uso_func_04C678(o3, &import_802649D8 + 1544);
    *(int *)(o3 + 0x28) = (int)&import_80073B18;
Lvt2:
    *(int *)(o2 + 0x28) = (int)&import_80073B80;
Lvt1:
    import_000AE700(o1 + 80);
    *(int *)(o1 + 0x28) = (int)&import_800745F8;
Lvt0:
    *(int *)(o0 + 0x28) = (int)&import_80264880;
    *(int *)(o0 + 0x568) = 0;
    import_000B0DBC(o0, a1, &import_802649E0 + 1552, a2);
    *(int *)(o0 + 0x528) = arg5;
    *(int *)(o0 + 0x7D4) = 0;
    mgrproc_uso_func_0000119C(o0);
    *(int *)(o0 + 0x6A8) = a3;
    w = *(char **)(o0 + 0x6A8);
    *(int *)(o0 + 0x7C4) = 0;
    *(float *)(o0 + 0x7A0) = f0;
    *(float *)(o0 + 0x7A4) = f0;
    *(float *)(o0 + 0x7B8) = f0;
    n = *(int *)w;
    *(int *)(o0 + 0x7D8) = 1;
    *(int *)(o0 + 0x7C8) = n;
    *(float *)(o0 + 0x7AC) = 210.0f;
    *(float *)(o0 + 0x7A8) = 160.0f - (float)(n * 2 - 2);
    mgrproc_uso_func_074710(&import_802649F0 + 1568, 0);
    import_000A7ECC(&import_80020098, 0);

    {
        char *o5;
        char *rec;
        char *vt;
        o5 = (char *)mgrproc_uso_func_055750(224);
        if (o5 != 0) {
            import_000B6C40(o5);
            *(int *)(o5 + 0x28) = (int)&import_80264800;
        }
        *(int *)(o0 + 0x6AC) = (int)o5;
        *(int *)(&import_800201D0 + 312) = (int)o5;

        mgrproc_uso_func_00002EF0(*(int *)(o0 + 0x6AC), o0, *(int *)(o0 + 0x568),
                                  *(int *)(o0 + 0x6A8), *(int *)(o0 + 0x528));

        rec = *(char **)(o0 + 0x6AC);
        vt = *(char **)(rec + 0x28);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)rec);

        rec = (char *)mgrproc_uso_func_07ACE0(o0 + 16, *(int *)(o0 + 0x6AC));
        if (*(int *)(rec + 0x14) != 0) {
            *(int *)(rec + 0x4) = 1;
        }
        *(int *)(rec + 0x14) = (int)o0;

        mgrproc_uso_func_01B0F8(o0, a1);
        *(int *)(o0 + 0x48) = import_000A5D38(0);
        import_000A5F40(*(int *)(o0 + 0x48), o0);

        import_000A69BC(*(int *)(o0 + 0x48), (*(int *)&import_8002022C + 3) << 16,
                        -1, &import_80265570);
        import_000A69BC(*(int *)(o0 + 0x48),
                        ((*(int *)&import_8002022C + 3) << 16) | 8, -1,
                        &import_802655B0);
        import_000A69BC(*(int *)(o0 + 0x48),
                        ((*(int *)&import_8002022C + 3) << 16) | 9, -1,
                        &import_802655EC);
        import_000A69BC(*(int *)(o0 + 0x48),
                        ((*(int *)&import_8002022C + 3) << 16) | 5, -1,
                        &import_802656A4);

        *(int *)(*(int *)(o0 + 0x48) + 0x30) = *(int *)(o0 + 0x568);
        import_000A5FBC(*(int *)(o0 + 0x48));

        rec = (char *)mgrproc_uso_func_07ACE0(o0 + 16, *(int *)(o0 + 0x48));
        if (*(int *)(rec + 0x14) != 0) {
            *(int *)(rec + 0x4) = 1;
        }
        *(int *)(rec + 0x14) = (int)o0;

        rec = (char *)mgrproc_uso_func_07ACE0(o0 + 16,
                                              *(int *)((char *)&import_80020228 + 400));
        if (*(int *)(rec + 0x14) != 0) {
            *(int *)(rec + 0x4) = 1;
        }
        *(int *)(rec + 0x14) = (int)o0;

        mgrproc_uso_func_0139B0(*(int *)((char *)&import_80020228 + 400), 1, 0);
        mgrproc_uso_func_074840();
        *(int *)(&import_800200D8 + 0x40) = 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000E04);
#endif

/* mgrproc_uso_func_0000119C: 2-insn alternate entry for
 * mgrproc_uso_func_000011A4. SOURCE=4 audit 2026-06-01: 0x119C has
 * no prologue and no `jr ra` (`grep -c 03E00008` = 0); it only loads
 * a1 from import_80020100+0x68, then falls through into 11A4 with
 * caller-provided a0. This is an alternate entry, not a missed accessor
 * template, and has no honest standalone C body. */
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
 * value from &D_x/&D_y). 2026-06-20: replaced placeholder gl_func_00000000
 * calls with the REAL reloc callees — first 6 calls = import_0024F228,
 * last 5 = import_0024F278 — and the real bases (&import_80263D30 arg0;
 * global reads from &import_800200FC+0x64 and &import_800200EC+0x54). The
 * remaining 2-of-66 diff is a schedule-swap between the first arg's lui-
 * const (`lui at,0x20` for 0x200000) and the `(a1-1)` addiu — previously
 * INSN_PATCH'd (REMOVED 2026-05-23). Dataflow-independent as1 scheduler
 * tie: IDO consistently schedules the `addiu a1,a1,-1` decrement before
 * the const-lui; OR-operand reorder, separate-statement, and named-temp
 * forms all leave it (the swap just migrates to the next adjacent op).
 * No reliable C lever. Still NM; default build is INCLUDE_ASM. */
#ifdef NON_MATCHING
extern int import_0024F228();
extern int import_0024F278();
extern char import_80263D30;
extern int import_800200EC;
extern int import_800200FC;
void mgrproc_uso_func_000011A4(char *s0, int a1) {
    int *q;
    import_0024F228(&import_80263D30, (a1 - 1) | 0x200000);
    import_0024F228(s0 + 0x6B0, *(int *)((char *)&import_800200FC + 0x64) | 0x000A0000);
    import_0024F228(s0 + 0x6C8, 0x210000);
    q = *(int **)(s0 + 0x6A8);
    if (q[2] == q[1] + 1) {
        import_0024F228(s0 + 0x6E0, 0x210000 | 1);
    } else {
        import_0024F228(s0 + 0x6E0, 0x210000 | (q[1] + 2));
    }
    import_0024F228(s0 + 0x6F8, *(int *)((char *)&import_800200EC + 0x54) | 0x001E0000);
    import_0024F278(s0 + 0x728, 0x210000 | 0x7);
    import_0024F278(s0 + 0x740, 0x210000 | 0x8);
    import_0024F278(s0 + 0x758, 0x210000 | 0x9);
    import_0024F278(s0 + 0x770, 0x210000 | 0xA);
    import_0024F278(s0 + 0x788, 0x210000 | 0xD);
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
 * 2026-06-01 SOURCE=4 retest: 99.63% NM. Resolved stale placeholder
 * callees to import_000B72F4 / mgrproc_uso_func_000000B0 / 000000F8 /
 * 00000170 / 01FA1C, then reversed the final two source stores:
 *   arg0[0x7D0] = arg0[0x4F8]; arg0[0x4FC] = 1;
 * IDO schedules that as the target order (`sw 1,0x4FC`; `sw state,0x7D0`)
 * while also assigning the target t9/t0 registers. Remaining diff is the
 * early state local only: IDO picks v1 where target uses v0 for
 * `lw state,0x4F8(s0); bne state,zero; beq state,2`. Tried
 * `register int v asm("$2")` (IDO syntax error) and inverted if nesting
 * (`if (v != 0) ... else ...`, regressed to 88.66%). The v0 lever turned
 * out to be an `if (1) {}` BB boundary (see below). */
/* 2026-06-04 PROMOTED to exact match via the if(1){} BB-boundary lever
 * (the "C-level v0 allocation lever" the prior note awaited): the empty block
 * after import_000B72F4 forces a BB boundary that flips arg0->0x4F8 from $v0
 * to $v1, matching the target. Byte-exact 41/41. */
extern int import_000B72F4();
extern int mgrproc_uso_func_000000B0();
extern int mgrproc_uso_func_000000F8();
extern int mgrproc_uso_func_00000170();
extern int mgrproc_uso_func_01FA1C();
int mgrproc_uso_func_00001324(char *arg0) {
    int v;
    if (*(int*)(arg0 + 0x4FC) == 0) {
        import_000B72F4(*(int*)(arg0 + 0x6AC), 0, 1);
        if (1) {}
        v = *(int*)(arg0 + 0x4F8);
        if (v == 0) {
            mgrproc_uso_func_000000B0(*(int*)(arg0 + 0x6A8));
        } else if (v != 2) {
            mgrproc_uso_func_000000F8(*(int*)(arg0 + 0x6A8));
        }
        if (mgrproc_uso_func_00000170(*(int*)(arg0 + 0x6A8)) != 0 &&
            mgrproc_uso_func_01FA1C(*(int*)(*(int*)(arg0 + 0x6AC) + 0x4C)) != 0) {
            *(int*)(arg0 + 0x4EC) = -0x258;
        }
        *(int*)(arg0 + 0x7D0) = *(int*)(arg0 + 0x4F8);
        *(int*)(arg0 + 0x4FC) = 1;
    }
    return 1;
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_000013C8: 75-insn (0x12C) post-init state dispatcher.
 * Real symbols re-derived 2026-06-20 from the resolved .s (the prior body
 * used gl_func_00000000 / &D_00000000 placeholders + wrong constants — ALL
 * relocs were wrong). Correct callees: mgrproc_uso_func_00000140 / _00000170
 * / _01FA1C / import_000A8114. Globals: import_800200DC (slot 0x44),
 * import_800200D8 (slot 0x40), import_80020100 (args to import_000A8114).
 *
 * Flow (s0 = a0; spill = stack 0x24):
 *   spill = 0;
 *   if (a0[0x4F8] == 0) {
 *       if (func_140(a0[0x6A8]) == 0) goto term;
 *       spill = 1; DC[0x44] = 7;
 *       if (*(int*)0xA0000200 == 0xAC290000) { s0[0x7C8]=0; return; }
 *       import_000A8114(&import_80020100, import_80020100[0x68] - 1);
 *       goto term;
 *   }
 *   // a0[0x4F8] != 0
 *   if (func_170(s0[0x6A8]) == 0) goto term;
 *   D8[0x40] = DC[0x44]; spill = 1; DC[0x44] = 7;
 * term:
 *   if (s0[0x7C8] != 0) { if (func_170(s0[0x6A8])==0) goto store; t5=s0[0x6AC]; }
 *   else                { t5 = s0[0x6AC]; }
 *   if (func_01FA1C(t5[0x4C]) != 0) { D8[0x40]=5; s0[0x7D8]=1; }
 *   else                           { D8[0x40]=7; spill=0; }
 * store:
 *   s0[0x504] = (spill == 0) ? 4 : 0;
 *
 * 0xA0000200 = SI_DRAM_ADDR_REG; 0xAC290000 = SI command-word check.
 *
 * NM cap (logic + control-flow + all symbols byte-correct, same size 0x12C).
 * Residual is genuine IDO addressing/scheduling idiom, multi-diff:
 *  - two separate `lui import_80020100` for the a0/a1 args (IDO does not
 *    reuse the base across the two operands; C reuse/fold collapses it);
 *  - per-store `lui at,%hi` rematerialization of the import_800200D8/DC
 *    global bases (target keeps the base register live; held-pointer C
 *    variants CSE it away);
 *  - branch-likely DIRECTION on the terminal (target beql spill==0 -> store 4;
 *    C emits bnel regardless of if/else or ternary phrasing).
 * Cap class = LO16/address-rematerialization + as1 branch-likely tie.
 * Default build INCLUDE_ASM keeps the ROM byte-correct. */
extern int mgrproc_uso_func_00000140();
extern int mgrproc_uso_func_00000170();
extern int mgrproc_uso_func_01FA1C();
extern int import_000A8114();
extern int import_800200DC[];
extern char import_800200D8;
extern int import_80020100[];
void mgrproc_uso_func_000013C8(int *a0) {
    int spill;          /* stack 0x24(sp) */
    int *s0 = a0;
    int *t5;
    spill = 0;
    if (a0[0x4F8 / 4] == 0) {
        if (mgrproc_uso_func_00000140(a0[0x6A8 / 4]) != 0) {
            spill = 1;
            import_800200DC[0x44 / 4] = 7;
            if (*(volatile int *)0xA0000200 == (int)0xAC290000) {
                import_000A8114(&import_80020100[0], import_80020100[0x68 / 4] - 1);
                goto term;
            } else {
                s0[0x7C8 / 4] = 0;
                goto epi;
            }
        }
        goto term;
    }
    /* a0[0x4F8] != 0 */
    if (mgrproc_uso_func_00000170(s0[0x6A8 / 4]) == 0) goto term;
    *(int *)((char *)&import_800200D8 + 0x40) = import_800200DC[0x44 / 4];
    spill = 1;
    import_800200DC[0x44 / 4] = 7;
term:
    if (s0[0x7C8 / 4] != 0) {
        if (mgrproc_uso_func_00000170(s0[0x6A8 / 4]) == 0) goto storestate;
    }
    t5 = (int *)s0[0x6AC / 4];
    if (mgrproc_uso_func_01FA1C(t5[0x4C / 4]) == 0) {
        *(int *)((char *)&import_800200D8 + 0x40) = 7;
        spill = 0;
    } else {
        *(int *)((char *)&import_800200D8 + 0x40) = 5;
        s0[0x7D8 / 4] = 1;
    }
storestate:
    s0[0x504 / 4] = (spill != 0) ? 0 : 4;
epi:
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000013C8);
#endif

/* mgrproc_uso_func_000014F4: 40-insn 3-way switch on a0->[0x4D8] (v):
 *   v == 2: func_0139B0(D[0x190], 3, 1, a0); a0->[0x7D4] = 1;
 *   v == 1 || v == 3: func_00001AD0(a0, D[0x170] + 0x26000F);
 *   else: skip
 *   Always-call func_048E7C(D + 0x628, a0->[0x4D8]) at entry.
 *
 * MATCHED 2026-06-20. The v==3 test had emitted a branch-likely fold
 * (bnel v0,at,end; lw ra) instead of the target's plain `beq case_13; b end;
 * lw ra (delay)`. Lever: write the third test as `if (v != 3) goto end;
 * goto case_13;` (split the equality+fallthrough into an explicit inverted
 * skip-branch + unconditional goto) — this suppresses the branch-likely
 * conversion and emits the plain beq + b end. Byte-exact, 40/40 words. */
extern char import_802649F8;
extern int import_80020228;
extern char import_80020208;
extern void mgrproc_uso_func_048E7C(void *, int);
extern void mgrproc_uso_func_00001AD0(int *, int);
extern int mgrproc_uso_func_0139B0();
void mgrproc_uso_func_000014F4(int *a0) {
    int v;
    mgrproc_uso_func_048E7C((char*)&import_802649F8 + 0x628, *(int*)((char*)a0 + 0x4D8));
    v = *(int*)((char*)a0 + 0x4D8);
    if (v == 2) goto case_2;
    if (v == 1) goto case_13;
    if (v != 3) goto end;
    goto case_13;
end:
    return;
case_2:
    mgrproc_uso_func_0139B0(*(int*)((char*)&import_80020228 + 0x190), 3, 1, a0);
    *(int*)((char*)a0 + 0x7D4) = 1;
    return;
case_13:
    mgrproc_uso_func_00001AD0(a0, *(int *)(&import_80020208 + 0x170) + 0x26000F);
}

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
 * 2. The 13-insn register-rename at 0x28-0x68 (the post-jal multu chain
 *    — IDO -O2 prefers $a2/$v1/{t6..t8}; target uses $v1/{t6..t9}) was
 *    previously documented as INSN_PATCH-promotable; INSN_PATCH REMOVED
 *    2026-05-23 as match-faking. 2026-06-20: replaced placeholder
 *    gl_func/D externs with the REAL reloc symbols (callee
 *    mgrproc_uso_func_013980; bases &import_80020228 (D[0x190]) and
 *    &import_80263D60 (D[0x30])). ROOT CAUSE confirmed via -zdbug:6 dump:
 *    the loop-invariant stride constant 0x28 (used by BOTH multu chains)
 *    is the LAST-encountered constrained candidate, so IDO colors it $a2
 *    (color 5); the target colored it $v1 (color 2), cascading the whole
 *    multu chain ($v1/t6..t9 vs $a2/v1/t6..t8). Its first-use is
 *    structurally after the two index loads, so no decl-order / named-
 *    local / commutative-operand lever moves it earlier (all verified
 *    in-tree: stride local, 0x28*idx, etc — candidate stays last). Genuine
 *    register-renumber cap. Default build is INCLUDE_ASM. */
extern int gl_func_00000000();
extern int D_mgr_1594_a, D_mgr_1594_c;
extern int import_80020228;
extern int import_80263D60;
extern int mgrproc_uso_func_013980();
/* mgrproc_uso_func_00001594 — EXACT 32/32 body (verified clean-rebuild 2026-07-02, agent-e).
 *
 * Replaces the former NM body (which was a documented "register-renumber cap").
 * CAP CRACKED — two levers, in order:
 *
 * 1. remove-local-inline-recompute (docs/IDO_CODEGEN.md): the old body's
 *    locals p/idx/q/fn were register-allocation CANDIDATES; idx colored $v1
 *    and fn colored $a0, pushing the shared stride constant 0x28 to $a2.
 *    In the target, only the CSE'd 0x28 is a candidate (gets low color $v1)
 *    and idx/q/fn are pure temps (t6..t9, then t0..t2, jalr t9).
 *    Inlining everything into two big expressions reproduced 30/32.
 * 2. commutative-operand source swap: residual was addu operand order
 *    (target `addu t8,v0,t7` base-first vs built mult-first). Writing the
 *    address as `idx*0x28 + (char*)base + 0x90` (mult FIRST in source)
 *    flips IDO's emitted addu to base-first. 32/32.
 *
 * Externs required (already at file scope in mgrproc_uso.c):
 *   extern int mgrproc_uso_func_013980();
 *   extern int import_80020228;
 *   extern int import_80263D60;
 */
void mgrproc_uso_func_00001594(int *a0) {
    if (mgrproc_uso_func_013980(*(int*)((char*)&import_80020228 + 0x190), a0) == 0) return;
    if (*(int*)(*(int*)((char*)a0[0x48 / 4] + 0x7C) * 0x28 + (char*)a0[0x48 / 4] + 0x90) == 0) return;
    *(int*)((char*)&import_80263D60 + 0x30) = (int)a0;
    ((void(*)()) *(int*)(*(int*)((char*)a0[0x48 / 4] + 0x7C) * 0x28 + (char*)a0[0x48 / 4] + 0x90))();
}

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
 * compare-dispatch (beqz/beq/beql/b). Residual: deep spill-slot regalloc.
 *
 * 2026-06-21: ALL 13 callees resolved from expected-.o relocs (gl_func_00000000
 * placeholders -> mgrproc_uso_func_0139B0/000188/013924/000148/012110/00001AD0/
 * 00002940/07ACE0/00000140/00001BD4/00F954 + imports 000B2888/007FE4E8). 96.27%
 * -> 97.65%. RESIDUAL (2 caps): (a) target frame -0x30 vs C-emit -0x28 (1 extra
 * 8-byte spill slot, cascades the jal-delay scheduling, +1 word); (b) the
 * import_80020228+0x190 reads use the inline %hi/%lo(sym+0x190) addend-fold
 * (form a) vs the base+displacement form (b) the held-base context emits
 * (docs/IDO_CODEGEN.md R_MIPS_LO16 entry). NON_MATCHING. */
extern int gl_func_00000000();
extern int mgrproc_uso_func_0139B0();
extern int mgrproc_uso_func_000188();
extern int mgrproc_uso_func_013924();
extern int mgrproc_uso_func_000148();
extern int mgrproc_uso_func_012110();
extern int mgrproc_uso_func_07ACE0();
extern int mgrproc_uso_func_00F954();
extern int mgrproc_uso_func_00001BD4();
extern void *mgrproc_uso_func_00002940(char *, int, int);
void mgrproc_uso_func_00001614(char *arg0) {
    int state = *(int *)(arg0 + 0x504);
    void *node;
    int hdr;

    switch (state) {
    case 0:
        mgrproc_uso_func_0139B0(*(int *)((char *)&import_80020228 + 0x190), 3, 1);
        *(int *)(arg0 + 0x504) = 1;
        mgrproc_uso_func_000188(7, 0, 0);
        break;
    case 1:
        if (mgrproc_uso_func_013924(*(int *)((char *)&import_80020228 + 0x190), state, 1) != 0) {
            *(int *)(arg0 + 0x4D8) = 1;
            mgrproc_uso_func_000148(7, 0, 0);
            mgrproc_uso_func_012110(&import_80020098);
            import_000B2888(arg0);
            mgrproc_uso_func_00001AD0(arg0, *(int *)((char *)&import_80020208 + 0x170) + 0x26000F);
            *(void **)(arg0 + 0x524) = (void *)mgrproc_uso_func_00002940(0, arg0, *(int *)(arg0 + 0x7D8));
            import_007FE4E8(*(void **)(arg0 + 0x524), *(int *)(arg0 + 0x528));
            hdr = *(int *)(arg0 + 0x56C);
            node = *(void **)(arg0 + 0x524);
            mgrproc_uso_func_07ACE0(hdr + 0x10, node);
            if (*(int *)((char *)node + 0x14) != 0) {
                *(int *)((char *)node + 4) = 1;
            }
            *(int *)((char *)node + 0x14) = hdr;
            if (mgrproc_uso_func_00000140(*(int *)(arg0 + 0x6A8), node) != 0) {
                *(int *)((char *)*(void **)(arg0 + 0x524) + 0x60) = 2;
                mgrproc_uso_func_00001BD4(arg0);
            }
            mgrproc_uso_func_0139B0(*(int *)((char *)&import_80020228 + 0x190), 1, 1);
        }
        break;
    case 4:
        {
            char *p = *(char **)(arg0 + 0x6A8);
            mgrproc_uso_func_00F954(arg0, 4, *(int *)(p + (*(int *)(p + 4) * 4) + 0x10));
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

#ifdef NON_MATCHING
/* Full structural decode 2026-06-01. Per-frame state machine: sub-state
 * gate on s0->0x7D4, a 5-case timer-countdown dispatch on s0->0x7E4 (each
 * decrements the s0->0x7E8 timer and transitions at 0), and a phase-1 init
 * block. Calls/data refs resolved to their real import/intra-segment
 * symbols (was gl_func_00000000/&D placeholders).
 *
 * 2026-06-23: switch-form lever on the 0x7E4 dispatch (was if/else-if
 * cascade) -> IDO now emits the jump-table dispatch (sltiu .,5 / beqz /
 * sll *4 / lui %hi / addu / lw 0(at) / jr). Drove the decode size-EXACT
 * (142 == 142 words) and fuzzy 79.9% -> 90.8%.
 *
 * DECODE-ONLY (permanent INCLUDE_ASM cap): the dispatch is the documented
 * jr-via-EXTERNAL-rodata-table cap. Target: `lui %hi(import_80264348)`
 * HI16-only (NO LO16 reloc) + `lw t8,1464(at)` with the 0x5B8 table offset
 * FOLDED into the lw displacement = indexing a pre-existing external/cross-TU
 * data table. IDO's C switch ALWAYS lowers to `lui %hi(.rodata)` +
 * `lw 0(at)` with a PAIRED HI16+LO16 against a SELF-LOCAL .rodata label and
 * zero displacement -- unreproducible from any C, and forcing the external
 * reference would be match-faking (banned). Plus the data globals
 * import_80020098/80020208/800200D8 are HI16-only-unpaired too (IDO-from-C
 * always emits HI16+LO16 pairs). Class = the 12-fn external-rodata-table
 * cohort in docs/MATCHING_WORKFLOW.md, now extended to mgrproc_uso. Residual
 * beyond the dispatch reloc = jump-table case-block ordering + register
 * coloring. No episode (NON_MATCHING). */
extern int import_000A7B90();
extern int import_00096228();
extern int import_000B2888();
extern int import_80020098[];
extern char import_80020208;
extern char import_800200D8;
extern int mgrproc_uso_func_0002DC();
extern int mgrproc_uso_func_000188();
extern int mgrproc_uso_func_000148();
extern int mgrproc_uso_func_01FA1C();
extern void mgrproc_uso_func_00001AD0(int *, int);
extern int mgrproc_uso_func_0139B0();
extern int mgrproc_uso_func_00F954();
void mgrproc_uso_func_00001824(char *s0) {
    char *v0;
    char *r;
    char *vt;
    int phase;
    int state;

    v0 = (char *)import_000A7B90(&import_80020098, 1);
    import_00096228(*(signed char *)(v0 + 8), *(signed char *)(v0 + 9));
    *(int *)(s0 + 0x7EC) = *(int *)(s0 + 0x7EC) + 1;
    phase = *(int *)(s0 + 0x7D4);
    if (phase == 0) {
        state = *(int *)(s0 + 0x7E4);
        switch (state) {
        case 0:
            if (--*(int *)(s0 + 0x7E8) == 0) {
                *(int *)(s0 + 0x7E4) = 1;
                *(int *)(s0 + 0x7E8) = 1050;
                mgrproc_uso_func_0002DC(512);
            }
            break;
        case 1:
            if (--*(int *)(s0 + 0x7E8) == 0) {
                *(int *)(s0 + 0x7D4) = 1;
            }
            break;
        case 2:
            if (--*(int *)(s0 + 0x7E8) == 0) {
                *(int *)(s0 + 0x7E4) = 3;
                *(int *)(s0 + 0x7E8) = 1650;
                mgrproc_uso_func_000188(13, 0, 0);
                mgrproc_uso_func_000148(13, 0, 0);
            }
            break;
        case 3: {
            int n;
            if (--*(int *)(s0 + 0x7E8) == 0) {
                *(int *)(s0 + 0x7E8) = 300;
                *(int *)(s0 + 0x7E4) = 4;
                mgrproc_uso_func_0002DC(512);
            }
            n = *(int *)(s0 + 0x7E0) + 1;
            if (n >= 16) {
                *(int *)(s0 + 0x7E0) = n - 16;
                *(int *)(s0 + 0x7DC) = *(int *)(s0 + 0x7DC) + 1;
            } else {
                *(int *)(s0 + 0x7E0) = n;
            }
            break;
        }
        case 4:
            if (--*(int *)(s0 + 0x7E8) == 0) {
                *(int *)(s0 + 0x7D4) = 1;
            }
            break;
        }
    } else if (phase == 1) {
        r = (char *)mgrproc_uso_func_01FA1C(*(int *)(s0 + 0x528));
        if (r != 0) {
            import_000B2888(s0);
            mgrproc_uso_func_000148(7, 0, 0);
            mgrproc_uso_func_00001AD0(s0, *(int *)(&import_80020208 + 368) + 0x26000F);
            vt = (char *)&import_80020098;
            *(int *)(s0 + 0x4D8) = 3;
            *(int *)(*(char **)(s0 + 0x524) + 0x60) = 1;
            *(int *)(vt + 0x40) = 5;
            *(int *)(vt + 0x44) = 7;
            *(float *)(s0 + 0x7A4) = 0.0f;
            mgrproc_uso_func_0139B0(*(int *)(vt + 0x190), 1, 1);
        } else {
            *(int *)(&import_800200D8 + 0x40) = 7;
            mgrproc_uso_func_00F954(s0, 0, 0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001824);
#endif

void mgrproc_uso_func_00001A5C(int a0) {
}

extern char import_800201CC;
void mgrproc_uso_func_00001A64(int *a0) {
  int *ptr;
  ptr = *((int **) (((char *) a0) + 0x51C));
  ptr = (int *) (((char *) ptr) + 0x18);
  *ptr = *ptr & (~8);
  ptr = *((int **) (((char *) a0) + 0x51C));
  ptr = (int *) (((char *) ptr) + 0x18);
  *ptr = *ptr & (~4);
  ptr = *((int **) (((char *) a0) + 0x520));
  ptr = (int *) (((char *) ptr) + 0x18);
  *ptr = *ptr | 8;
  ptr = *((int **) (((char *) a0) + 0x520));
  ptr = (int *) (((char *) ptr) + 0x18);
  *ptr = *ptr | 4;
  *((int **) ((*((int *) (((char *) (&import_800201CC)) + 0x134))) + 0x108)) = *((int **) (((char *) a0) + 0x520));
}

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

/* mgrproc_uso_func_00001B58: 0x7C, 31-insn leaf orchestrator. BYTE-EXACT.
 *
 * Two regalloc levers landed it (2026-06-20, agent-e):
 *  1. $v1-coloring: naming the throwaway intermediate `c4 = p[0xC4/4]` as its
 *     own short-lived local forces IDO to color it into $v1 (the natural
 *     next register after $v0=p), giving the v1->t6->t7 chain. Inlining it
 *     skips $v1 and shifts the whole chain up (t6->t7->t8).
 *  2. Spill-slot decl-order: the two call-crossing pointers t6/t7 home at
 *     0x20/0x18 (gap at 0x1C). Decl order `p; t6; c4; t7;` (c4 BETWEEN the
 *     two spilled temps) packs the slots to match; adjacent decls 4-pack
 *     them (0x1C/0x18). See docs/IDO_CODEGEN interleave-decl-spill-slot
 *     (same lever cracked the sibling func_00001AD0). */
extern int gl_func_00000000();
extern int mgrproc_uso_func_01B0F8();
extern int mgrproc_uso_func_01CCD4();
extern int mgrproc_uso_func_07BA68();
extern int import_000B7FF0();
void mgrproc_uso_func_00001B58(int *a0) {
  int *p;
  int *t6;
  int *c4;
  int *t7;
  mgrproc_uso_func_01B0F8(a0);
  p = *((int **) (((char *) (&D_00000000)) + 0x134));
  c4 = (int *) p[0xC4 / 4];
  t6 = (int *) c4[0x800 / 4];
  t7 = (int *) ((int *) p[0xCC / 4])[0x800 / 4];
  mgrproc_uso_func_01CCD4(a0, p[0xCC / 4]);
  mgrproc_uso_func_07BA68(t6, 0);
  mgrproc_uso_func_07BA68(t7, 0);
  import_000B7FF0(*((int *) (((char *) (&D_00000000)) + 0x138)), 0, 0);

  a0[0x4F4 / 4] = 0;
}

/* vram 0x1BD4: 4-word stolen-prologue donation to func_00001BE4 (the old
 * SUFFIX_BYTES absorption was removed 2026-05-23, silently dropping these
 * bytes from the Yay0 block). Standalone GLOBAL_ASM block emits exactly. */
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_orphan_00001BD4.s")

#ifdef NON_MATCHING
extern int import_802649C0;
extern int import_802649CC;

/* mgrproc_uso_func_00001BE4 (partial-shape NM body).
 * v1/idx and a2/state are inherited from predecessor's stolen tail; modeled
 * as explicit params so the body does NOT recompute them (no spurious lui/lw).
 * Call 3 (func_1B58) takes exactly 2 args (a0,a1) — no extra zeroed args. */
void mgrproc_uso_func_00001BE4(int idx, int *a2) {
    idx -= 5;
    *(int*)((char*)a2 + 0x4D8) = 2;
    *(int*)((char*)a2 + 0x7DC) = 0;
    *(int*)((char*)a2 + 0x7E0) = 0;
    *(int*)((char*)a2 + 0x7E4) = *(int*)((char*)&import_802649C0 + idx * 4 + 0x5F0);
    *(int*)((char*)a2 + 0x7EC) = 0;
    *(int*)((char*)a2 + 0x7E8) = *(int*)((char*)&import_802649CC + idx * 4 + 0x5FC);
    mgrproc_uso_func_012110(a2);
    mgrproc_uso_func_00001A64(a2);
    mgrproc_uso_func_00001B58(a2);
    mgrproc_uso_func_000188(0xB, 0, 0);
    mgrproc_uso_func_000148(0xB, *(int*)((char*)&import_800200FC + 0x64) - 5, 0);
    mgrproc_uso_func_0139B0(*(int*)((char*)&import_80020228 + 0x190), 1, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001BE4);
#endif

#ifdef NON_MATCHING
extern int gl_func_00000000();
extern float D_flt_5CC, D_flt_5D0, D_flt_5D4, D_flt_5D8;
void mgrproc_uso_func_00001C90(char *arg0) {
    volatile int pt_a, pt_b, pt_c, pt_d;
    float sp50[4];
    volatile int pmid;
    int sp48;
    char *p6a8;
    volatile int pad_a, pad_b, pad_c, pad_d, pad_e, pad_f, pad_g;

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
 * {200,160,-64,0,120}.
 *
 * MATCHED 2026-06-21 (byte-exact, ROM-identical). The prior "FP-scheduling cap"
 * was really two C-steerable shape issues, cracked by two source-order levers:
 *   (1) STORE-ORDER: the target emits the two integer stores (0x7C4=1,
 *       0x7C8-=1) BEFORE the FP stores 0x7A8/0x7AC. Moving those two int
 *       statements ahead of the x+4/y-4 stores in source drops 12->6 diffs
 *       (the as1 scheduler then matches the int/FP store interleave).
 *   (2) CONST-FIRST FP-REG: the 1.0f written to 0x7C0 must color $f10 (LOW),
 *       and the add/sub results $f16/$f18 (HIGH). IDO numbers FP pseudos in
 *       source-statement order, so placing `*(0x7C0) = one;` BEFORE the
 *       x+4/y-4 stores creates the const pseudo first -> $f10, pushing the
 *       arith results up to $f16/$f18 (target). 6->0. (`float two=2.0f; /two`
 *       still forces the div.s-by-literal, frame 0x18, target-like bnel returns
 *       — keep it.) The real tail callee is mgrproc_uso_func_0002DC(50) (was
 *       the cross-USO placeholder gl_func_00000000); both disk-encode jal as
 *       0C000000 under the USO R_MIPS_26 runtime reloc, so the ROM is identical
 *       and the swap only makes objdiff count the call. */
void mgrproc_uso_func_00002324(char *a0) {
    float x, y;
    float two = 2.0f;
    float one = 1.0f;
    if (*(int *)(a0 + 0x7C4) != 0) return;
    x = *(float *)(a0 + 0x7A8);
    y = *(float *)(a0 + 0x7AC);
    *(float *)(a0 + 0x7BC) = *(float *)(a0 + 0x7B8) / two;
    *(int *)(a0 + 0x7C4) = 1;
    *(int *)(a0 + 0x7C8) -= 1;
    *(float *)(a0 + 0x7C0) = one;
    *(float *)(a0 + 0x7A8) = x + 4.0f;
    *(float *)(a0 + 0x7AC) = y - 4.0f;
    *(float *)(a0 + 0x7B0) = x;
    *(float *)(a0 + 0x7B4) = y;
    mgrproc_uso_func_0002DC(50);
    if (*(int *)(a0 + 0x7C8) != 0) return;
    *(float *)(a0 + 0x554) = 200.0f;
    *(float *)(a0 + 0x558) = 160.0f;
    *(float *)(a0 + 0x55C) = -64.0f;
    *(float *)(a0 + 0x560) = 0.0f;
    *(float *)(a0 + 0x564) = 120.0f;
}

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* 2026-07-10 (78.23 -> 83.72 fuzzy): the four `255.0f * FW(arg0, 0x7A0)` alpha
 * expressions used an INT load of field 0x7A0 followed by cvt.s.w; the target
 * emits `lwc1 $f6,1952(s3)` (no convert) -- 0x7A0 is genuinely a FLOAT field.
 * Switched those reads to `*(float*)(arg0 + 0x7A0)`, dropping one cvt.s.w per
 * site and re-aligning the FP chain. RESIDUAL (~16%): the six draw calls pass
 * &D_00000000 as arg0; the target rematerializes it per-site (`lui a0; addiu`,
 * form a) at some calls and holds it in $s0 (`move a0,s0`, form b) at others --
 * the address-fold-vs-CSE allocator coin-flip SKIP class (a held-`dbase` local
 * regressed to 82.5%). Plus frame 0x120 vs 0xB8 + $f0/$f4 const numbering +
 * beq/beql branch-likely picks -- whole-function coloring caps. Stays NM. */
typedef char *(*GP_000023FC)();
void mgrproc_uso_func_000023FC(char *arg0) {
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    u8 sp90;
    s32 sp60;
    s32 sp5C;
    s32 sp54;
    s32 sp4C;
    u8 *sp44;
    s32 sp38;
    s32 sp30;
    s16 temp_v1;
    s32 temp_a1;
    s32 temp_s0_3;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    u8 *temp_a0;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_4;
    u8 *temp_s1;
    u8 *var_s0;
    u8 temp_v0_2;
    char *temp_t5;

    sp110 = 1.0f;
    sp114 = 1.0f;
    sp118 = 1.0f;
    sp11C = 1.0f;
    if (FW(arg0, 0x4F8) != 2) {
        mgrproc_uso_func_00000AE0(0);
        mgrproc_uso_func_00000AE0(0, (s32) (255.0f * *(float*)(arg0 + 0x7A0)), &sp110);
        mgrproc_uso_func_00000AE0(0, 0xA0, (f32 *)0x8C, (char *)3);
    }
    mgrproc_uso_func_00000AE0(0, (s32) (255.0f * *(float*)(arg0 + 0x7A0)), (int)arg0 + 0x338, (int)arg0 + 0x35C);
    FW(arg0, 0x508) = (s32) (FW(arg0, 0x508) + 1);
    if (FW(arg0, 0x4F8) == 0) {
        temp_s0 = (int)arg0 + 0x728;
        if (mgrproc_uso_func_00000AE0(FW(arg0, 0x6A8)) != 0) {
            temp_s0_2 = (int)arg0 + 0x740;
            if (FW(arg0, 0x508) & 8) {
                mgrproc_uso_func_00000AE0(temp_s0_2);
                mgrproc_uso_func_00000AE0(temp_s0_2, 0xA0, (f32 *)0x78, (char *)3);
            }
        } else {
            mgrproc_uso_func_00000AE0(temp_s0);
            mgrproc_uso_func_00000AE0(temp_s0, 0xA0, (f32 *)0x78, (char *)3);
        }
    }
    if ((FW(arg0, 0x508) & 8) && (FW(FW(arg0, 0x528), 0x14) & 1)) {
        temp_t5 = *(char **)0x138;
        sp60 = (s32) FW(temp_t5, 0x30) / 60000;
        sp5C = (s32) (FW(temp_t5, 0x30) % 60000) / 1000;
        temp_s0_3 = (s32) ((FW(temp_t5, 0x30) % 60000) % 1000) / 10;
        mgrproc_uso_func_00000AE0(0, (s32) (255.0f * *(float*)(arg0 + 0x7A0)), (int)arg0 + 0x2A8, (int)arg0 + 0x2CC);
        temp_a0 = (int)arg0 + 0x788;
        sp44 = temp_a0;
        mgrproc_uso_func_00000AE0(temp_a0);
        temp_s1 = (int)arg0 + 0x770;
        temp_s2 = (s16) FW(FW(arg0, 0x798), 0x20) / 12;
        mgrproc_uso_func_00000AE0(temp_s1);
        mgrproc_uso_func_00000AE0(&sp90, 0x640, (f32 *) sp60, (char *) sp5C, temp_s0_3);
        temp_v0 = mgrproc_uso_func_00000AE0(&sp90);
        temp_v1 = FW(FW(arg0, 0x780), 0x20);
        temp_a1 = 0xA0 - ((s32) (temp_v1 + (temp_v0 * 0xD) + 8) / 2);
        sp4C = temp_v1 + temp_a1 + 8;
        sp54 = temp_v0;
        mgrproc_uso_func_00000AE0(temp_s1, temp_a1, (f32 *)0xBE, (char *)2);
        var_t2 = temp_v0;
        var_s0 = &sp90;
        var_t0 = 0;
        var_s1 = sp4C;
        if (var_t2 > 0) {
            var_t1 = var_t2 * 0xD;
            do {
                temp_v0_2 = *(int*)var_s0;
                if (temp_v0_2 == 0x5B) {
                    *var_s0 = 0xA;
                } else if (temp_v0_2 == 0x5D) {
                    *var_s0 = 0xB;
                } else {
                    *var_s0 = temp_v0_2 - 0x30;
                }
                sp54 = var_t2;
                sp30 = var_t1;
                sp38 = var_t0;
                mgrproc_uso_func_00000AE0(sp44, var_s1, 0xBE - ((s16) FW(FW(arg0, 0x798), 0x22) / 2), (char *) (*(int*)var_s0 * temp_s2), temp_s2);
                var_t0 += 0xD;
                var_s0 += 1;
                var_s1 += 0xD;
            } while (var_t0 != var_t1);
        }
    }
    var_s0_2 = 0;
    if ((FW(FW(arg0, 0x528), 0x14) & 1) && (FW(arg0, 0x4FC) != 0) && (FW(FW((*(char *)0x138), 0x44), 0x38) < 3)) {
        var_s0_2 = 1;
    }
    mgrproc_uso_func_00000AE0(0, (s32) (255.0f * *(float*)(arg0 + 0x7A0)), (int)arg0 + 0x2F0, (int)arg0 + 0x314);
    temp_s0_4 = (int)arg0 + 0x758;
    if (var_s0_2 != 0) {
        mgrproc_uso_func_00000AE0(temp_s0_4);
        if (FW(arg0, 0x508) & 8) {
            mgrproc_uso_func_00000AE0(temp_s0_4, 0xA0, (f32 *)0xA0, (char *)3);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000023FC);
#endif

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
 * mgrproc_uso_func_00002324).
 *
 * SYMBOLS RE-DERIVED 2026-06-20: the prior body used gl_func_00000000 /
 * &D_00000000 placeholders (relocs WRONG). The three calls are DISTINCT
 * real targets (import_0024E608, import_0024F2C8, import_0024F34C) and the
 * first call's buffer base is import_8024CAF8 — fixed below. The loop is
 * rewritten as the target's pointer-walk form (p1 = &a1[i] decrementing,
 * p2 = &a2[-i] incrementing, do/while) to match the s1/s2 pointer-walk
 * with homed-and-reloaded a1/a2.
 *
 * NM (53/53 words, ~17 prologue-only diffs, was 84.96% / 42 raw diffs):
 * FRAME-LAYOUT solved + AS1-SCHEDULER-TIE residual. The 0x10-short frame and
 * the buf-position diff are CRACKED: `volatile int pad0..pad3;` declared AFTER
 * buf[4] grows the frame -0x58 -> -0x68 (4 dead slots at the bottom, zero
 * insns) AND pins buf[4] to the TOP (sp+0x58..0x64) while a1/a2 home to their
 * incoming-arg slots sp+0x6C/0x70 — every frame/offset word now matches. The
 * loop is the index/byte-offset pointer-walk (s0=i<<2 counter, p1=&a1[i]
 * decrementing, p2=&a2[-i] incrementing, bltz-guard + bgez-continue) — body,
 * frame, and all 3 R_MIPS_26 calls are byte-exact.
 *   RESIDUAL = pure prologue instruction SCHEDULE: target emits
 *     sw s0,0x14 ; move s0,a0 ; sw ra ; sw s3 ; sw s2 ; sw s1
 *   then reads the struct field via `lwc1 $f6,1956(s0)` (s0 established early
 *   because a0 is reused for the first call's `lui a0`). Every natural-C form
 *   instead emits the reverse save-block order (ra..s0) and reads the field
 *   from a0 (`lwc1 $f4,1956(a0)`) with `move s0,a0` deferred to just before
 *   the jal. The const-vs-field f-reg pick (f4/f6) and the s0-early copy are an
 *   as1/uopt scheduler tie not reachable by statement reorder / operand swap /
 *   tgt-hoist (all tried). Genuine scheduler-tie cap; default INCLUDE_ASM. */
extern char import_8024CAF8;
extern void import_0024E608();
extern void import_0024F2C8();
extern void import_0024F34C();
#ifdef NON_MATCHING
void mgrproc_uso_func_00002850(char *s0, int *a1, int *a2, int a3) {
    float buf[4];
    volatile int pad0, pad1, pad2, pad3;
    int n;
    char *tgt;
    int i;
    int off;
    int *p1;
    int *p2;
    buf[0] = 1.0f; buf[1] = 1.0f; buf[2] = 1.0f; buf[3] = 1.0f;
    n = (int)(255.0f * *(float *)(s0 + 0x7A4));
    import_0024E608(&import_8024CAF8, n, buf);
    tgt = s0 + 0x6F8;
    import_0024F2C8(tgt);
    i = a3 - 1;
    if (i >= 0) {
        off = i << 2;
        p1 = (int *)((char *)a1 + off);
        p2 = (int *)((char *)a2 - off);
        do {
            import_0024F34C(tgt, p1, p2, 3);
            off -= 4;
            p1--;
            p2++;
        } while (off >= 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002850);
#endif

void mgrproc_uso_func_00002924(int *a0) {
    *(float *)((char *)a0 + 0x54C) = 116.0f;
    *(float *)((char *)a0 + 0x554) = 170.0f;
}

/* mgrproc_uso_func_00002940 — family variant of arcproc_uso_func_0000199C
 * (4-level alloc-cascade ctor; head/cascade/field-block identical shape,
 * sizes 0x174/0xD4/0x50/0x2C, init-call base +0x650). mgr-specific tail:
 * 0x16C=0, 0x168=1.0f, 0x170=0xFA, cb(&sym+0x18,7), four cb(self+sub,
 * 0x23000N) installs, final cb(self+0x150, ((id+0x23)<<16)|(q68-1)).
 * Head lever (from the 199C crack): reassign arg0 itself in the
 * short-circuit cascade (a named s0 copy shifts the `move s0,a0` and
 * loses a word). Packed-id tail here is global|global — textual order
 * already creates the id chain first (no typed-member lever needed). */
extern int gl_func_00000000();
extern char D_mgr2940_v[];   /* import_80264A20: init-call a1 base (+0x650) */
extern char D_mgr2940_w[];   /* import_80073B18: a0->0x28 (level-4) */
extern char D_mgr2940_x[];   /* import_80073B80: v1->0x28 (level-3) */
extern char D_mgr2940_y[];   /* mgrproc_uso_D_807FFA80: a2->0x28 (level-2) */
extern char D_mgr2940_z[];   /* import_80264508: s0->0x28 (level-1/main) */
extern char D_mgr2940_t[];   /* import_80263D48: cb arg base (+0x18) */
extern int D_mgr2940_id;     /* import_8002022C: packed-id value read */
extern struct Mgr2940Q { char pad[0x68]; int v; } D_mgr2940_q; /* import_80020100: packed-id low half (.v @+0x68) */

void *mgrproc_uso_func_00002940(char *arg0, int arg1, int arg2) {
    char *a2;   /* level-2 (0xD4), home 0x2C(sp) */
    char *v1;   /* level-3 (0x50), home 0x28(sp) */
    char *a0;   /* level-4 (0x2C), home 0x24(sp) */

    if ((arg0 != 0) || (arg0 = (char *)gl_func_00000000(0x174), (arg0 != 0))) {
        a2 = arg0;
        if ((arg0 != 0) || (a2 = (char *)gl_func_00000000(0xD4), (a2 != 0))) {
            v1 = a2;
            if ((a2 != 0) || (v1 = (char *)gl_func_00000000(0x50), (v1 != 0))) {
                a0 = v1;
                if ((v1 != 0) || (a0 = (char *)gl_func_00000000(0x2C), (a0 != 0))) {
                    gl_func_00000000(a0, D_mgr2940_v + 0x650); *(char **)(a0 + 0x28) = D_mgr2940_w;
                }
                *(char **)(v1 + 0x28) = D_mgr2940_x;
            }
            *(char **)(a2 + 0x28) = D_mgr2940_y;
        }
        *(char **)(arg0 + 0x28) = D_mgr2940_z;
        *(int *)(arg0 + 0x60) = arg2;
        *(int *)(arg0 + 0xD4) = arg1;
        *(int *)(arg0 + 0xE0) = 0xA0;
        *(int *)(arg0 + 0xE4) = 0x1D;
        *(int *)(arg0 + 0xD8) = 0xA0;
        *(int *)(arg0 + 0xDC) = 0x82;
        *(int *)(arg0 + 0xE8) = 0xA0;
        *(int *)(arg0 + 0xEC) = 0x69;
        *(int *)(arg0 + 0x16C) = 0;
        *(float *)(arg0 + 0x168) = 1.0f;
        gl_func_00000000(D_mgr2940_t + 0x18, 7);
        *(int *)(arg0 + 0x170) = 0xFA;
        gl_func_00000000(arg0 + 0xF0, 0x230004);
        gl_func_00000000(arg0 + 0x108, 0x230003);
        gl_func_00000000(arg0 + 0x120, 0x230005);
        gl_func_00000000(arg0 + 0x138, 0x230006);
        gl_func_00000000(arg0 + 0x150,
            ((D_mgr2940_id + 0x23) << 16) | (D_mgr2940_q.v - 1));
    }
    return arg0;
}

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
 * 0x7E4). a3 = arg0->0xD4 (the mgr sub-object); s4 = arg0.
 *
 * Case 1: two labeled rows. import_0024D108(a3->0x568); blit a digit/value via
 *   import_0024E608(&import_8024CAF8, 0xFF, a3+0x4A0); then for each of two label
 *   strings (&import_80264A28+0x658, &import_80264A3C+0x66C) call the text-layout
 *   helper mgrproc_uso_func_083574(&sp60, str), then
 *   import_0024D704(h->0x568, import_0024E060(h->0x568, 0xA0, &sp60), x, &sp60)
 *   with x = 0x46 (70) then 0x64 (100).
 * Case 3: 16-glyph loop. s2 = -1 - a3->0x7E0; import_0024D108(a3->0x568); for
 *   i in 0..15: reload a3; s1 = ((char**)&import_8025CAF8)[a3->0x7DC + i];
 *   digit = *s1 - '0'; s1++; inner switch(digit){0:a3+0x458; 1:a3+0x47C;
 *   2(+default):a3+0x4A0} -> sub-object s3; import_0024E608(&import_8024CAF8,
 *   0xFF, s3); import_0024D704(h->0x568, import_0024E060(h->0x568,0xA0,s1), s2,
 *   s1); s2 += 0x10. After loop, if a3->0x7E8 < 0x96 do the fade+panel tail
 *   (shared with case 4): if arg0->0x170 >= 0x79 decrement it;
 *   import_0024E608(&import_8024CAF8, 0xFF, h+0x4C4); import_0024F2C8(panel);
 *   import_0024F34C(panel, 0xA0, arg0->0x170, 3) where panel = &import_80263D48+0x18.
 * Case 4: just the fade+panel tail.
 *
 * SYMBOLS RE-DERIVED 2026-06-23 (was 73.91%, all calls collapsed to
 * gl_func_00000000 / glyph table = &D_00000000 -> WRONG R_MIPS_26 + reloc form).
 * Six distinct real R_MIPS_26 callees now wired (import_0024D108 / _0024E608 /
 * _0024E060 / _0024D704 / _0024F2C8 / _0024F34C + the intra-USO text helper
 * mgrproc_uso_func_083574); the four data bases (import_8024CAF8 string buffer,
 * import_8025CAF8 glyph-ptr table, import_80264A28/3C label strings,
 * import_80263D48 panel object) symbolized.
 *
 * RESIDUAL CAPS (DECODE-ONLY, not landable from C):
 *  (1) HI16-PAIR: every data base (import_8024CAF8/8025CAF8/80264A28/80264A3C/
 *      80263D48) is reached in the TARGET by an *unpaired* R_MIPS_HI16 lui plus a
 *      baked, un-relocated addiu immediate (the symbols are NOT page-aligned:
 *      low16 != 0, so this is the USO link-direct form where the loader patches
 *      only HI16). Standard C `&import_X + off` always emits a HI16/LO16 *pair*
 *      (objdump shows R_MIPS_LO16 on our addiu's), which cannot be suppressed.
 *  (2) 5-SAVED-REG / FRAME COLORING: the target pins arg0 to s4 (5 saved regs
 *      s0..s4, frame -0xB8) and keeps the sub-object ptr in saved s3 spilled/
 *      reloaded at 0xA0(sp) live across the loop (`lw s3,0xA0` pre-loop on an
 *      uninit value, `sw s3,0xA0` post-loop). Our C only needs 4 saved regs
 *      (arg0->s3, frame -0xA8); a `sub=sub` self-assign is DCE'd. The s3-vs-s4
 *      base-register difference cascades through every `lw ...,0xD4(sX)`.
 *  (3) LOOP STRENGTH-REDUCTION: target keeps the 0..15 index in s0 and recomputes
 *      `(field+i)<<2` each iter; IDO instead strength-reduces our index into a
 *      byte-offset counter (+=4, compare !=0x40). Coloring/IV tie.
 * What IS now correct vs the prior 73.91% placeholder body: all six DISTINCT
 * R_MIPS_26 callees, the full case-1/3/4 control flow, the inner digit switch,
 * and the data symbols are right. Best-effort correct-C decode; NON_MATCHING. */
extern char import_8025CAF8;
extern char import_80264A28;
extern char import_80264A3C;
extern char import_80263D48;
extern int import_0024D108();
extern int import_0024E060();
extern int import_0024D704();
extern int mgrproc_uso_func_083574();
void mgrproc_uso_func_00002B7C(char *arg0) {
    volatile float spB0;
    volatile float spAC;
    volatile float spA8;
    volatile float spA4;
    char *panel;
    char sp60[68];
    char *a3;
    char *h;
    int s0;
    int s2;
    char *s1;
    int digit;
    char *sub;

    spA4 = 1.0f;
    spA8 = 1.0f;
    spAC = 1.0f;
    spB0 = 1.0f;
    a3 = *(char **)(arg0 + 0xD4);
    switch (*(int *)(a3 + 0x7E4)) {
    case 1:
        import_0024D108(*(int *)(a3 + 0x568));
        import_0024E608(&import_8024CAF8, 0xFF, a3 + 0x4A0);
        mgrproc_uso_func_083574(&sp60, &import_80264A28 + 0x658);
        import_0024D704(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                        import_0024E060(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, &sp60),
                        0x46, &sp60);
        mgrproc_uso_func_083574(&sp60, &import_80264A3C + 0x66C);
        import_0024D704(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                        import_0024E060(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, &sp60),
                        0x64, &sp60);
        return;
    case 3:
        s2 = -1 - *(int *)(a3 + 0x7E0);
        import_0024D108(*(int *)(a3 + 0x568));
        s0 = 0;
        do {
            a3 = *(char **)(arg0 + 0xD4);
            s1 = ((char **)&import_8025CAF8)[*(int *)(a3 + 0x7DC) + s0];
            digit = *s1 - 0x30;
            s1++;
            switch (digit) {
            case 0:
                sub = a3 + 0x458;
                break;
            case 1:
                sub = a3 + 0x47C;
                break;
            case 2:
            default:
                sub = a3 + 0x4A0;
                break;
            }
            import_0024E608(&import_8024CAF8, 0xFF, sub);
            import_0024D704(*(int *)(*(char **)(arg0 + 0xD4) + 0x568),
                            import_0024E060(*(int *)(*(char **)(arg0 + 0xD4) + 0x568), 0xA0, s1),
                            s2, s1);
            s0 += 1;
            s2 += 0x10;
        } while (s0 != 0x10);
        h = *(char **)(arg0 + 0xD4);
        if (*(int *)(h + 0x7E8) < 0x96) {
            if (*(int *)(arg0 + 0x170) >= 0x79) {
                *(int *)(arg0 + 0x170) = *(int *)(arg0 + 0x170) - 1;
                h = *(char **)(arg0 + 0xD4);
            }
            import_0024E608(&import_8024CAF8, 0xFF, h + 0x4C4);
            panel = &import_80263D48 + 0x18;
            import_0024F2C8(panel);
            import_0024F34C(panel, 0xA0, *(int *)(arg0 + 0x170), 3);
        }
        return;
    case 4:
        if (*(int *)(arg0 + 0x170) >= 0x79) {
            *(int *)(arg0 + 0x170) = *(int *)(arg0 + 0x170) - 1;
            a3 = *(char **)(arg0 + 0xD4);
        }
        import_0024E608(&import_8024CAF8, 0xFF, a3 + 0x4C4);
        panel = &import_80263D48 + 0x18;
        import_0024F2C8(panel);
        import_0024F34C(panel, 0xA0, *(int *)(arg0 + 0x170), 3);
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002B7C);
#endif

/* vram 0x2E34: 2-word FPU-const stolen prologue (lui $at,0x3F80; mtc1
 * $at,$f0). The old "C-emit-absorbed by _00002B7C" note was stale: 2B7C's
 * INCLUDE_ASM emits exactly its 0x2B8 decl, so the orphan had vanished from
 * the block (-8). Restored 2026-06-10 as a standalone 2-word GLOBAL_ASM. */
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_orphan_00002E34.s")

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
extern int mgrproc_uso_func_01F874();
extern void import_0024E388();
#ifdef NON_MATCHING
/* RE-DERIVED 2026-06-22: prior body claimed -O0/Yay0 cap, but the target is
 * -O2 with FILLED delay slots and real reloc names. Three calls are distinct
 * real targets (mgrproc_uso_func_01F874, import_0024F2C8, import_0024E388,
 * import_0024F34C); a0 is saved across F2C8 (sw/lw sp+68) and reused.
 * Twin (if/else form) of titproc_uso_func_00001710. Body now logically
 * byte-faithful (97.49%): frame -0x58, rgba@sp+0x48, branch order, all 4
 * callees + args match. RESIDUAL = a single STOLEN-PROLOGUE `mtc1 zero,$f0`
 * that lives in the 8-byte splat gap at 0x2E34..0x2E38 (predecessor 2B7C ends
 * at 0x2E34; 2E3C declared from 0x2E3C) — the real fn start with the f0-init
 * is OUTSIDE the splat boundary, so the swc1 f0 stores read f0 set by that
 * orphaned insn. Natural C must emit `mtc1 zero,f0` to zero rgba (the
 * DIFF_INSERT). This is a SPLAT-BOUNDARY / stolen-prologue cap (not -O0, not
 * C-reachable without a fragment-merge of 0x2E34). INCLUDE_ASM build path. */
void mgrproc_uso_func_00002E3C(char *a0) {
  float rgba[4];
  char pad[0x18];
  char *target;
  int state;
  int alpha;
  (void) pad;
  rgba[0] = 0.0f;
  rgba[1] = 0.0f;
  rgba[2] = 0.0f;
  rgba[3] = 0.0f;
  *((int *) (a0 + 0x68)) = (*((int *) (a0 + 0x68))) + 1;
  state = mgrproc_uso_func_01F874(*((int *) (a0 + 0x50)));
  if (state == 0)
  {
    return;
  }
  if (state == 1)
  {
    target = a0 + 0x120;
  }
  else
  {
    target = a0 + 0x138;
  }
  import_0024F2C8(target);
  alpha = (int) (255.0f * (*((float *) (a0 + 0x168))));
  import_0024E388(target, alpha, rgba, 255);
  if (((*((int *) (a0 + 0x68))) & 8) != 0)
  {
    import_0024F34C(target, 160, 124, 3);
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002E3C);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00002EF0: one ~97-insn (0x184) object initializer + draw-list
 * builder. BOUNDARY MERGED 2026-06-02: splat had split it into 2EF0 (8-insn
 * FP-const prologue — f2=255, f4=192, f6=255, f10=0, then div.s f0=192/255 —
 * hoisted above the frame setup; the real entry, jal'd from 0E04) + 2F10 (the
 * `addiu sp` prologue + body + jr ra, ZERO callers). IDO hoisted the entry's
 * FP-const setup above the prologue, so splat cut at 2F10. Absorbed 2F10's 89
 * words into 2EF0 (0x20 -> 0x184) and dropped the 2F10 symbol; the FP consts
 * are now in-scope (removes the chained-FPU-stolen-prologue cap that blocked
 * the decode). Remaining caps keep it NM: Yay0/-O0 segment, branch-likely
 * (bgezl/beqzl), two &D bases, placeholder calls. Body = field layout + draw
 * sequence; ends in the linked-set finalizer idiom
 * (reference_1080_linked_set_finalizer_tail_idiom). */
void mgrproc_uso_func_00002EF0(self, a1, a2, a3, arg5)
    int *self; int a1, a2, a3, arg5;
{
    float div255 = 255.0f;
    float c = 192.0f / div255;   /* the merged FP prologue: div.s f4(192)/f2(255) */

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
    *(float*)((char*)self + 0xC8) = 255.0f / div255;   /* f8 = f6/f2 */
    *(float*)((char*)self + 0xD0) = 0.0f / div255;     /* f10 = f10/f2 */

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
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002EF0);
#endif
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_00003074: per-frame step gated on arg0->0xBC->0x4F0 bit-16 &&
 * ->0x4DC==1. Bumps arg0->0x30 by 0x21 if gated; cb(arg0,sub). Then (if gated):
 * a 3-way dispatch on arg0->0x44->0x94 (0/1/else) when ->0x34 set; a mod-0x33
 * frame counter at arg0->0xDC; periodic cb(0x135,0) when arg0->0x98->0xC4>=0xC;
 * cb(sub) when arg0->0x98->0xC8<=0. Final block (if still gated && ->0x4DC==1 &&
 * cb()!=0): cb(sub), sub->0x554=200.0f, arg0->0x2C=0; then two cb(arg0->0x80, ...)
 * from arg0->0x44 fields. cb(arg0) tail. Decode refined 2026-06-23: float-5th-arg
 * FIXED (016BEC prototyped with trailing `float` → swc1, no cvt.d.s/sdc1); the BC
 * pointer is CSE-reused for the final gate test (a1 reload before final v0); the
 * 0xC8 cb reuses the 0x98 pointer; the 0xDC counter is inlined (`*p += 1`) so it
 * no longer steals v0 — counter region now byte-exact. Register-BLIND structure is
 * now IDENTICAL to target. RESIDUAL (64 diffs, all derived from ONE coloring
 * decision): IDO assigns the post-call gate value + the 0x44/0x98 pointers to v1
 * here vs v0 in target — a uniform v0<->v1 global-coloring renumber. The 3-way
 * dispatch's redundant beqz-recheck and the B139C duplicate-arg move both follow
 * from that swap. PERMUTER-IMMUNE (40k iters, temp_for_expr/reorder passes: base
 * score 480 -> 360 floor, no zero; only no-op if(1){}/const-mangle "wins").
 * decl-order, if(1)-wrap, &&-reorder, nested-else, truthy-cond all 0-effect on the
 * swap. Genuine IDO post-call v-reg coloring cap. Caps: arg0/sub structs + cb
 * prototypes untyped (USO-reloc). NON_MATCHING. */
extern int import_000B70AC();
extern int import_000B1284();
extern int import_000B1334();
extern int import_000B12B4();
extern int mgrproc_uso_func_0002FC();
extern int import_000B139C();
extern int import_000B7058();
extern int import_000B14CC();
extern int mgrproc_uso_func_016BB8();
extern int mgrproc_uso_func_016BEC(int, int, int, int, float);
extern int mgrproc_uso_func_04CD94();
void mgrproc_uso_func_00003074(char *arg0) {
    char *a1;
    int v0;
    char *p;
    int v1;

    a1 = *(char **)(arg0 + 0xBC);
    if ((*(int *)(a1 + 0x4F0) & 0x10000) && (*(int *)(a1 + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
    }
    import_000B70AC(arg0, a1);
    a1 = *(char **)(arg0 + 0xBC);
    v0 = *(int *)(a1 + 0x4F0) & 0x10000;
    if ((v0 != 0) && (*(int *)(a1 + 0x4DC) == 1)) {
        p = *(char **)(arg0 + 0x44);
        if (*(int *)(p + 0x34) != 0) {
            v1 = *(int *)(p + 0x94);
            if (v1 == 0) {
                import_000B1284(a1);
            } else if (v1 == 1) {
                import_000B1334(a1);
            } else {
                import_000B12B4(a1);
            }
        }
        *(int *)(arg0 + 0xDC) += 1;
        if (*(int *)(arg0 + 0xDC) >= 0x33) {
            *(int *)(arg0 + 0xDC) = 0;
        }
        p = *(char **)(arg0 + 0x98);
        if ((p != 0) && (*(int *)(p + 0xC4) >= 0xC) && (*(int *)(arg0 + 0xDC) == 0)) {
            mgrproc_uso_func_0002FC(0x135, 0);
        }
        p = *(char **)(arg0 + 0x98);
        if (*(int *)(p + 0xC8) <= 0) {
            import_000B139C(*(int *)(arg0 + 0xBC), *(int *)(arg0 + 0xBC));
        }
        a1 = *(char **)(arg0 + 0xBC);
        v0 = *(int *)(a1 + 0x4F0) & 0x10000;
    }
    if (v0 != 0) {
        if ((*(int *)(a1 + 0x4DC) == 1) && (import_000B7058(arg0) != 0)) {
            import_000B14CC(*(int *)(arg0 + 0xBC));
            *(float *)(*(char **)(arg0 + 0xBC) + 0x554) = 200.0f;
            *(int *)(arg0 + 0x2C) = 0;
        }
        p = *(char **)(arg0 + 0x44);
        mgrproc_uso_func_016BB8(*(int *)(arg0 + 0x80), *(int *)(p + 0x30), *(int *)(p + 0x90));
        p = *(char **)(arg0 + 0x44);
        mgrproc_uso_func_016BEC(*(int *)(arg0 + 0x80), *(int *)(p + 8), *(int *)(p + 0xC),
                         *(int *)(p + 0x68), *(float *)(p + 0x6C));
    }
    mgrproc_uso_func_04CD94(arg0);
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
 * register choices as expected/. The only ".o diff" is the unrelocated jal
 * placeholder (`jal 0` + R_MIPS_26 reloc to mgrproc_uso_func_00000CC4);
 * objdiff is reloc-symbol-aware and scores them 100%.
 *
 * 2026-06-04: now PROMOTED (plain C build path, episodes logged) — the old
 * reloc-encoding cap (#reloc-encoding-pinning... in docs/MATCHING_WORKFLOW.md,
 * which claimed these score 65%) no longer applies; the report shows 100%. */
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

/* mgrproc_uso_func_00003358: 36-insn (0x90) alloc-and-link node helper.
 * BYTE-IDENTICAL sibling of eddproc_uso_func_000003BC (matched 100%). The
 * "file-level state cap" was a MISDIAGNOSIS — porting eddproc's exact body
 * verbatim (p1/p2 split + decl order p2,head,p1 + reload of arg0[0x40])
 * matches byte-for-byte here. The frame-0x28 two-web spill shape is forced
 * by the variable reuse, not file context. Do not "simplify" the reuse or
 * the re-load; they are load-bearing for the register/slot allocation. */
extern int mgrproc_uso_func_051C28();
extern char import_8006ED80;

void *mgrproc_uso_func_00003358(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)mgrproc_uso_func_055750(0x40);
    if (p1 != 0) {
        mgrproc_uso_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_8006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        mgrproc_uso_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}

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
