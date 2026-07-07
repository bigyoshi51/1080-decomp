#include "common.h"

/* Contiguous -O0 run [0x19C, 0xAE0) of the mgrproc_uso Yay0 block, carved into
 * a dedicated -O0 sub-unit (region 2) and concatenated with the -O2 objects
 * before crunch64 compression. See the mgrproc_uso_block1_yay0 rule in the
 * Makefile. func_000009A8 is byte-matched at -O0 (its D_0000014C store's %lo is
 * baked into the blob by scripts/bake-data-relocs.py); the rest are still
 * INCLUDE_ASM caps (NM bodies kept for objdiff scoring / grep). */

extern int gl_func_00000000();
extern int D_00000000;
extern int D_00000148;
extern int D_0000014C;

#define MGR_D_64 (*(int*)((char*)&D_00000000 + 0x64))
#define MGR_STATE_CODE (*(int*)((char*)&D_00000000 + 0x40))
#define MGR_D_44 (*(int*)((char*)&D_00000000 + 0x44))

#ifdef NON_MATCHING
extern char D_a_4_x;
extern int D_b_4_x[];
extern char D_c_4_x;
extern char D_8_x;
extern char import_80020098;
extern int import_000A5B9C();
extern int mgrproc_uso_func_07ACE0();
mgrproc_uso_func_0000019C(a0, a1) char * a0; int a1; {
    int loop_continue;
    int v0_save;
    int buf;
    loop_continue = 0;
    do {
        switch (a1) {
            case 0:
                gl_func_00000000(a0, 1, 0xB, 8);
                MGR_D_44 = 2;
                *(int*)((char*)&D_00000000 + 0x48) = 8;
                loop_continue = 1;
                break;
            case 1:
                gl_func_00000000(a0, 1, 7, 4);
                MGR_D_44 = 2;
                *(int*)((char*)&D_00000000 + 0x48) = 8;
                loop_continue = 1;
                break;
            case 2:
                gl_func_00000000(a0);
                MGR_STATE_CODE = 3;
                break;
            case 3:
                gl_func_00000000(a0, *(int*)((char*)&D_00000000 + 0x68));
                MGR_STATE_CODE = 4;
                break;
            case 4: {
                int *p;
                int *q;
                register int s0_save;
                gl_func_00000000(&D_a_4_x, D_b_4_x[1]);
                p = (int*)*(int**)((char*)a0 + 8);
                q = p + p[1];
                MGR_D_64 = q[3];
                *(int*)((char*)&D_00000000 + 0x80) =
                    *(int*)((char*)&D_00000000 + 0x80) ^ 1;
                p = (int*)*(int**)((char*)a0 + 8);
                q = p + p[1];
                *((char*)&D_00000000 + 0x17D) = (char)q[9];
                *((char*)&D_00000000 + 0x17F) =
                    (char)*(int*)((char*)&D_00000000 +
                                  ((unsigned char)*((char*)&D_00000000 + 0x17D) * 4) +
                                  0x90);
                gl_func_00000000(&D_c_4_x, 4, MGR_D_64, 0);
                gl_func_00000000(&D_c_4_x, MGR_D_64);
                v0_save = gl_func_00000000(a0, *(int*)a0, 1);
                s0_save = gl_func_00000000(0, 0x45000000, v0_save,
                                           *(int*)((char*)a0 + 8),
                                           *(int*)a0);
                gl_func_00000000(a0, 0, s0_save);
                loop_continue = 1;
                break;
            }
            case 5:
                v0_save = gl_func_00000000(a0, &buf);
                gl_func_00000000(a0, (buf | 0x2000) | v0_save, 0x2000,
                                 *(int*)a0);
                loop_continue = 1;
                break;
            case 6:
                gl_func_00000000(a0);
                MGR_STATE_CODE = 1;
                break;
            case 7:
                gl_func_00000000(a0);
                MGR_STATE_CODE = 8;
                break;
            case 8: {
                register int *s0_p;
                register char *base;
                register char *p10;
                s0_p = (int*)import_000A5B9C(0, 1, 0);
                base = &import_80020098;
                p10 = base + 0x10;
                mgrproc_uso_func_07ACE0(p10, s0_p);
                if (s0_p[0x14 / 4] != 0) {
                    s0_p[1] = 1;
                }
                s0_p[0x14 / 4] = (int)base;
                loop_continue = 1;
                break;
            }
            default:
                break;
        }
        a1 = MGR_STATE_CODE;
    } while (!loop_continue);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000019C);
#endif

/* 51-insn allocator+init wrapper, byte-matched at -O0. v3 is `register` (s0,
 * the target's callee-saved result reg); the dead `v3 = (int)&D_00000000`
 * reproduces the target's lui/addiu of &D in s0; the sentinel read uses the
 * direct int symbol D_00000000 for the $at-fused load. D_00000148/_0000014C are
 * fused stores/loads whose %lo bakes into the blob (bake-data-relocs). */
void mgrproc_uso_func_00000504(int *a0) {
    int v1;
    register int v3;
    v1 = gl_func_00000000(2);
    a0[2] = gl_func_00000000(0x3C);
    v3 = gl_func_00000000(0, D_00000148, -1, -1);
    a0[0] = v3;
    D_0000014C = v3;
    gl_func_00000000(v1);
    v3 = (int)&D_00000000;
    if (D_00000000 == 0x17D7) {
        *(int*)((char*)a0[0] + 0x14) = 1;
    } else {
        *(int*)((char*)a0[0] + 0x14) = 0;
    }
}

#ifdef NON_MATCHING
/* 76-insn (0x130) random-unique-ID assignment: fills 4 entries at
 * (a0->8)->[idx*4 + 0x24] with 4 unique random IDs in {0..4}.
 *
 * 23-diff NM, 76/76 insns (was 76-diff). FRAME NOW EXACT (-0x28), all stack
 * slots exact, all 3 relocs exact (import_802600E4/import_800200E4 hi/lo +
 * gl_func_00000000f jal), full structure exact. The float-eval-order "floor"
 * documented previously was WRONG: the reason the old body spilled f0 (swc1;lwc1
 * or mov->f20/sdc1, +8 frame) was the const/int loads were pointer-arith forms
 * (`*(float*)((char*)&D+0x24)`) that IDO -O0 materializes as lui/addiu into a
 * GPR, forcing f0 to be parked across them. Accessing them as STRUCT MEMBERS of
 * an extern struct at the import symbol (import_802600E4.v @ +0x24,
 * import_800200E4.v @ +0x4C) makes IDO emit the $at-fused single-lui lvalue load
 * (lui $at,%hi; lwc1 %lo($at)) with NOTHING between the jal and the mul -> f0
 * used directly, no spill, frame -0x28. Key structural levers: result=-1 at the
 * TOP of the do-body (back-edge re-inits it, no bottom reset); no `arr` local
 * (inline `*(int**)(a0+8)` in the tail store, else +1 slot/+8 frame); decl order
 * result,count,candidate,idx -> slots 0x24,0x20,0x1C,0x18; `while(++count<4)`
 * fuses the increment+test (no reload).
 *
 * RESIDUAL (23 diffs) = pure IDO -O0 temp-register renumbering in the loop body:
 * the inner compare `candidate == elem` -- IDO evaluates the heavier `elem`
 * subtree first (Sethi-Ullman) and loads candidate last, whereas the target
 * holds candidate in $t5 across the elem chain. This shifts the temp-allocator
 * rotation, renumbering scratch $t regs in the inner compare, the idx==count
 * check, and the tail store/increment (stack slots + mnemonics all still exact).
 * No C operand order or loop/subscript form changes it (probed >8 variants).
 * Documented regalloc-renumber cap class -- leave INCLUDE_ASM. */
extern float gl_func_00000000f(void);
struct FC { float pad[9]; float v; };
struct IC { int pad[0x13]; int v; };
extern struct FC import_802600E4;
extern struct IC import_800200E4;
void mgrproc_uso_func_000005D0(char *a0) {
    int result;
    int count;
    int candidate;
    int idx;

    count = 0;
    do {
        result = -1;
        while (result == -1) {
            candidate = ((int)(gl_func_00000000f() * import_802600E4.v)
                         + import_800200E4.v + 1) % 5;
            for (idx = 0; idx < count; idx++) {
                if (candidate == *(int*)((char*)*(int**)(a0 + 8) + idx * 4 + 0x24)) break;
            }
            if (idx == count) {
                result = candidate;
            }
        }
        *(int*)((char*)*(int**)(a0 + 8) + count * 4 + 0x24) = result;
    } while (++count < 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000005D0);
#endif

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00000700)();
void mgrproc_uso_func_00000700(char *arg0, s32 arg1) {
    *(int*)(FW(arg0, 0x8)) = 3;
    FW(FW(arg0, 0x8), 0x4) = 0;
    switch (arg1) {                                 /* irregular */
    case 1:
        if (*(s32 *)0xA0000284 == 0x240B17D7) {
            FW(FW(arg0, 0x8), 0x8) = 4;
        } else {
            FW(FW(arg0, 0x8), 0x8) = 3;
        }
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        mgrproc_uso_func_0000019C(arg0);
        break;
    case 2:
        FW(FW(arg0, 0x8), 0x8) = 5;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        mgrproc_uso_func_0000019C(arg0);
        FW(FW(arg0, 0x8), 0x34) = (s32) *(char *)0x4C;
        break;
    case 3:
        FW(FW(arg0, 0x8), 0x8) = 6;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        FW(FW(arg0, 0x8), 0x20) = 7;
        mgrproc_uso_func_0000019C(arg0);
        FW(FW(arg0, 0x8), 0x34) = (s32) *(s32 *)0x4C;
        if (FW((*(char **)0x154), 0x2) == 3) {
            FW(FW(arg0, 0x8), 0x38) = 5;
        } else if (FW((*(char *)0x154), 0x2) == 4) {
            FW(FW(arg0, 0x8), 0x38) = 6;
        } else {
            FW(FW(arg0, 0x8), 0x38) = 7;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000700);
#endif

/* 27-insn -O0 cleanup wrapper, byte-matched at -O0. The `register int z=0`
 * lands in callee-saved s0 (the target's shared-zero reg); D_0000014C (defined
 * = 0x14C) gives the $at-fused `lui at; sw %lo(D_0000014C)(at)` store, whose
 * %lo (0x14c) is baked into the blob by scripts/bake-data-relocs.py. */
void mgrproc_uso_func_000009A8(int *a0) {
    register int z;
    gl_func_00000000(a0[2]);
    a0[2] = 0;
    gl_func_00000000(a0[0], 3);
    z = 0;
    a0[0] = z;
    D_0000014C = z;
}

#ifdef NON_MATCHING
/* mgrproc_uso_func_00000A14 — BEST BODY (IMPROVED over checked-in), still CAP.
 * VERIFIED 2026-07-03 in-tree (build/non_matching, -O0 IDO 7.1): 42/48 words,
 * build 50 insns vs target 48 (checked-in body was 37/48, build 51).
 * IMPROVEMENT: union-alias for buf (arr[8] + head overlay) —
 *   - `*arg1 = buf.head` emits the target's direct `lw t6,0x30(sp)` instead of
 *     the array-form recompute `addiu t6,sp,0x30; lw t7,0(t6)` (-1 insn, and
 *     un-shifts t-reg numbering across the tail: words +0x94..+0xA4 now exact);
 *   - loop `buf.arr[i]` keeps the target's sll/addu/lw-0x30 fold;
 *   - `&buf` call arg keeps `addiu a1,sp,0x30`.
 * This is the union-alias trick referenced in
 * docs/IDO_CODEGEN.md#feedback-ido-o0-value-return-extra-branch ("got to 50 vs
 * 48") but it was never applied to the checked-in NM body — worth committing.
 * Residual (6 word diffs) = purely the systematic value-returning -O0 extra
 * return-branch: `lw v0,0x28(sp); b epi; nop; b+1; nop` vs target
 * `lw v0,0x28(sp); b+1; nop`. Same cap as arcproc 0xB4/0x12C; IDO 5.3 and all
 * flag/shape probes negative. Leave INCLUDE_ASM. */
s32 mgrproc_uso_func_00000A14(s32 *arg0, s32 *arg1) {
    union { s32 arr[8]; s32 head; } buf;
    s32 count;
    s32 acc;
    s32 i;
    register s32 r;

    acc = 0;
    count = import_000B574C(*arg0);
    mgrproc_uso_D_01F97C(*arg0, &buf);
    i = 0;
    if (count > 0)
        do {
            r = import_000AE5B0(buf.arr[i]);
            acc |= r;
        } while (++i < count);
    *arg1 = buf.head;
    return acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000A14);
/* func_00000A14_pad (0xC trailing block-alignment zeros) is added by the
 * block1 yay0 concat rule's intermediate pad-to-0xAE0, not a GLOBAL_ASM here:
 * asm-processor rejects the 3-word pad block as "too short". */
#endif
