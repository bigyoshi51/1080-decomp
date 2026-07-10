#include "common.h"

/* Contiguous -O0 run [0x19C, 0xAE0) of the mgrproc_uso Yay0 block, carved into
 * a dedicated -O0 sub-unit (region 2) and concatenated with the -O2 objects
 * before crunch64 compression. See the mgrproc_uso_block1_yay0 rule in the
 * Makefile. func_0000019C, func_00000504, func_000009A8 (+ the trailing -O0
 * leaves) are byte-matched at -O0 (data-%lo values bake into the blob via
 * scripts/bake-data-relocs.py); the rest are INCLUDE_ASM caps (NM bodies
 * kept for objdiff scoring / grep). */

extern int gl_func_00000000();
extern int D_00000000;
extern int D_00000148;
extern int D_0000014C;

#define MGR_D_64 (*(int*)((char*)&D_00000000 + 0x64))
#define MGR_STATE_CODE (*(int*)((char*)&D_00000000 + 0x40))
#define MGR_D_44 (*(int*)((char*)&D_00000000 + 0x44))

/* State-machine dispatcher. BYTE-EXACT (218/218 words, ROM byte-identical,
 * promoted to the plain-C build path) 2026-07-10. Levers:
 * - every D-global is an extern STRUCT at its import_800200xx symbol with the
 *   member at the baked %lo offset -> IDO -O0 emits the $at-fused single-lui
 *   form (lui at; sw %lo(sym+off)(at)) matching the baked expected relocs
 *   (see docs/IDO_CODEGEN.md $at-fused extern-struct-member entry);
 * - case 4 field chains are single-statement DAGs (no p/q locals);
 * - ONE function-scope register ptr (node -> s0) shared by case 4/8 + base
 *   (s1) + p10 (s2) reproduce the 3-s-reg prologue;
 * - plain locals DECLARED BEFORE the register vars (a register var declared
 *   first reserves a dead home slot above the locals, shifting the whole
 *   column down 0xC); decl order v0_save,loop_continue,buf,ret = slots
 *   0x4C,0x48,0x44,0x40; no default: arm (jumptable default = loop tail);
 * - import_80073CF0 read is the ARRAY form [1] (3-insn lui/addiu/lw, NOT
 *   fused member form) — the one materialized global read in the target;
 * - the switch jumptable's HI16/LO16 ride against local .rodata vs expected's
 *   import_80263D90 symbol: imms are 0 both ways (USO load-time reloc), so
 *   bytes bake identically (bake-data-relocs no-op; symbols all =0).
 * Real callee names wired from expected relocs. */
extern struct { char pad[0x40]; int v; } import_800200D8;   /* state code */
extern struct { char pad[0x44]; int v; } import_800200DC;
extern struct { char pad[0x48]; int v; } import_800200E0;
extern struct { char pad[0x64]; int v; } import_800200FC;
extern struct { char pad[0x68]; int v; } import_80020100;
extern struct { char pad[0x80]; int v; } import_80020118;
extern struct { char pad[0x90]; int arr[0x100]; } import_80020128;
extern struct { char pad[0x17D]; unsigned char v; } import_80020215;
extern struct { char pad[0x17F]; unsigned char v; } import_80020217;
extern char import_80020098[];
extern int import_80073CF0[];
extern int import_000B2FA0();
extern int import_000A8094();
extern int import_000B34B8();
extern int import_000B3268();
extern int import_000A5B9C();
extern int mgrproc_uso_func_07ACE0();
extern int mgrproc_uso_func_0118E4();
extern int mgrproc_uso_func_0120A8();
extern int mgrproc_uso_func_00000E04();
extern int mgrproc_uso_func_01DA48();
void mgrproc_uso_func_00000504();
int mgrproc_uso_func_00000700();
void mgrproc_uso_func_000009A8();
s32 mgrproc_uso_func_00000A14();
mgrproc_uso_func_0000019C(a0, a1) char * a0; int a1; {
    int v0_save;          /* sp+0x4C (case 4) */
    int loop_continue;    /* sp+0x48 */
    int buf;              /* sp+0x44 (case 5) */
    int ret;              /* sp+0x40 (case 5) */
    register int *node;   /* s0: case4 E04 result / case8 A5B9C node */
    register char *base;  /* s1 */
    register char *p10;   /* s2 */
    loop_continue = 0;
    do {
        switch (a1) {
            case 0:
                import_000B2FA0(a0, 1, 0xB, 8);
                import_800200DC.v = 2;
                import_800200E0.v = 8;
                loop_continue = 1;
                break;
            case 1:
                import_000B2FA0(a0, 1, 7, 4);
                import_800200DC.v = 2;
                import_800200E0.v = 8;
                loop_continue = 1;
                break;
            case 2:
                mgrproc_uso_func_00000504(a0);
                import_800200D8.v = 3;
                break;
            case 3:
                mgrproc_uso_func_00000700(a0, import_80020100.v);
                import_800200D8.v = 4;
                break;
            case 4:
                mgrproc_uso_func_0118E4(import_80020098, import_80073CF0[1]);
                import_800200FC.v =
                    (*(int**)(a0 + 8))[(*(int**)(a0 + 8))[1] + 3];
                import_80020118.v = import_80020118.v ^ 1;
                import_80020215.v =
                    (*(int**)(a0 + 8))[(*(int**)(a0 + 8))[1] + 9];
                import_80020217.v = import_80020128.arr[import_80020215.v];
                mgrproc_uso_func_0120A8(import_80020098, 4,
                                        import_800200FC.v, 0);
                import_000A8094(import_80020098, import_800200FC.v);
                v0_save = import_000B34B8(a0, *(int*)a0, 1);
                node = (int*)mgrproc_uso_func_00000E04(0, 0x450000, v0_save,
                                                       *(int*)(a0 + 8),
                                                       *(int*)a0);
                mgrproc_uso_func_01DA48(a0, 0, node);
                loop_continue = 1;
                break;
            case 5:
                ret = mgrproc_uso_func_00000A14(a0, &buf);
                import_000B3268(a0, (buf | 0x2000) | ret, 0x2000,
                                *(int*)a0);
                loop_continue = 1;
                break;
            case 6:
                mgrproc_uso_func_000009A8(a0);
                import_800200D8.v = 1;
                break;
            case 7:
                mgrproc_uso_func_000009A8(a0);
                import_800200D8.v = 8;
                break;
            case 8:
                node = (int*)import_000A5B9C(0, 1, 0);
                base = import_80020098;
                p10 = base + 0x10;
                mgrproc_uso_func_07ACE0(p10, node);
                if (node[0x14 / 4] != 0) {
                    node[1] = 1;
                }
                p10 = base;
                node[0x14 / 4] = (int)p10;
                loop_continue = 1;
                break;
        }
        a1 = import_800200D8.v;
    } while (!loop_continue);
}

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
/* mgrproc_uso_func_00000700: 3-case state-init dispatcher. 90.05 -> 93.31
 * (2026-07-10): real callees wired from expected relocs (all three case
 * calls are mgrproc_uso_func_000005D0, NOT func_0000019C as the old body
 * had), import_800200E4.v (D+0x4C, int; old body lbu'd *(char*)0x4C),
 * import_800201EC.v[1] u16 reads (lhu at ptr+2; old body lwl/lwr), and the
 * case-1 dead `register char *base = &D_00000000` la (lui/addiu s0 =
 * import_8005C6E0, the func_00000504 v3 idiom).
 *
 * RESIDUAL (+2 words, whole-switch t-reg renumber): the target's switch
 * temp is t1 (plain rotation temp after the head's t6..t0, single lw
 * 0x2C(sp), NO home store, no extra save); IDO 7.1/5.3 -O0 ALWAYS promotes
 * a beq-chain switch temp to the lowest free callee-saved reg (here s1,
 * +save/+restore = 172 vs 170). Probed exhaustively: +0/|0/(short)/comma/
 * deref-of-& exprs, struct/union by-value arg, K&R vs ANSI, varargs, extra
 * params, int return, do-while(0)/if(1)/goto-out/fallthrough wraps,
 * register-in-case, 7 register dummies (fn+block scope: s-exhaustion
 * spills the temp WITH a home store + frame 96 — wrong shape), volatile
 * body access, second switch, 5.3, -g/-g2/-g3/-Olimit. All promote or
 * distort. Same -O0 toolchain-binary gap family as the value-return
 * double-b cap (docs/IDO_CODEGEN.md#feedback-ido-o0-return-value-dead-
 * double-b): the original 1080 cc's -O0 kept switch temps in the t
 * rotation. Everything else (all relocs, control flow, la, lhu forms) is
 * exact; the s1-vs-t1 class shifts every subsequent t number. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern struct { char pad[0x154]; unsigned short *v; } import_800201EC;
mgrproc_uso_func_00000700(arg0, arg1) char *arg0; int arg1; {
    register char *base; /* s0; case-1 dead la of &D (import_8005C6E0) */
    *(int*)(FW(arg0, 0x8)) = 3;
    FW(FW(arg0, 0x8), 0x4) = 0;
    switch (arg1) { /* irregular */
    case 1:
        base = (char *)&D_00000000;
        if (*(s32 *)0xA0000284 == 0x240B17D7) {
            FW(FW(arg0, 0x8), 0x8) = 4;
        } else {
            FW(FW(arg0, 0x8), 0x8) = 3;
        }
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        mgrproc_uso_func_000005D0(arg0);
        break;
    case 2:
        FW(FW(arg0, 0x8), 0x8) = 5;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        mgrproc_uso_func_000005D0(arg0);
        FW(FW(arg0, 0x8), 0x34) = import_800200E4.v;
        break;
    case 3:
        FW(FW(arg0, 0x8), 0x8) = 6;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        FW(FW(arg0, 0x8), 0x20) = 7;
        mgrproc_uso_func_000005D0(arg0);
        FW(FW(arg0, 0x8), 0x34) = import_800200E4.v;
        if (import_800201EC.v[1] == 3) {
            FW(FW(arg0, 0x8), 0x38) = 5;
        } else if (import_800201EC.v[1] == 4) {
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
