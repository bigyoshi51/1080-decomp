#include "common.h"

/* bootup_uso 0xFC28..0x100F0 region, split off bootup_uso_tail1.c on
 * 2026-05-28 so that func_0000FBCC could move to a -O0 sub-file
 * (bootup_uso_o0_FBCC.c) and land as a byte-exact match. These four
 * functions stay INCLUDE_ASM NM-wraps (documented -O0 alloc-cascade /
 * dead-BB / t-reg caps — see per-function notes). TRUNCATE_TEXT clips
 * this file's .text to FEE8's true end (0x4C8) so o0_100F0.c.o abuts at
 * bootup offset 0x100F0. */

extern int func_00000000();
extern struct { char _p2C[0x2C]; int f2C; char _p38[0x8]; int f38; } func_00000008; /* USO-base reloc; struct-typed for $at-fused member stores */
extern char D_00000000;
extern char D_0000C58C;
extern char D_0000C594;
extern char D_0000C5A4;
extern char D_0000C5AC;
extern int D_bootup_scratch0;         /* int-typed base-0 alias of D_00000000; $at-fused scratch store/reload */

#ifdef NON_MATCHING
/* func_0000FC28: 73-insn (0x124) constructor + init chain, returns a0.
 *
 * 2026-07-10: 56.23% -> 97.06% (byte-exact except the ONE documented
 * -O0 return-value dead-double-b toolchain gap; see FD4C below for the
 * full lever writeup — FC28 is the smaller sibling, same recipe).
 * Levers: (1) STRUCTURED nested if(){} (NOT if()goto) so each alloc/fail
 * check emits a single `b!cond endif` — a `goto` at -O0 always emits a
 * 2-insn branch-over (bnez;b); the whole rest is guarded by if(a0!=0){}
 * so the a0-alloc-fail is the beqz-to-end guard. (2) `register void*
 * s0,s1` (callee-saved cascade temps, no home spill). (3) TAIL recycles
 * the now-dead s0/s1: `s0=a0; s1=&D_0000C594; *(int*)(s0+0xC)=(int)s1;`
 * reproduces `lw s0; lui s1; sw s1,0xC(s0)`, and `s0=a0; f(scratch,s0)`
 * the final-call arg. (4) D_bootup_scratch0 (int-typed base-0 alias of
 * D_00000000, undefined_syms) $at-fuses the *&D store/reload (lui/sw)
 * vs the address-of-cast's lui/addiu/sw. RESIDUAL = the dead second
 * `b epilogue` only (value-return -O0 cap, NOT C-fixable). NM stays. */
void *func_0000FC28(void *a0) {
    register void *s0, *s1;

    if (a0 == 0) {
        a0 = (void*)func_00000000(0x50);
    }
    if (a0 != 0) {
        s0 = a0;
        if (s0 == 0) {
            s0 = (void*)func_00000000(0x50);
        }
        if (s0 != 0) {
            s1 = s0;
            if (s1 == 0) {
                s1 = (void*)func_00000000(0x2C);
            }
            if (s1 != 0) {
                func_00000000(s1, &D_0000C58C);
                *(int*)((char*)s1 + 0x28) = (int)&D_00000000;
            }
            *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
        s0 = a0;
        s1 = (void*)&D_0000C594;
        *(int*)((char*)s0 + 0x0C) = (int)s1;
        D_bootup_scratch0 = func_00000000(a0, 0);
        s0 = a0;
        func_00000000(D_bootup_scratch0, s0);
    }
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);
#endif

#ifdef NON_MATCHING
/* func_0000FD4C: 85-insn (0x154) alloc-chain + multi-init helper, returns a0.
 * Larger sibling of func_0000FC28 (+ a1/a2 global stashes, 0x44/0x48 zeroing).
 *
 * 2026-07-10: 58.18% -> 97.47% (byte-exact except the ONE documented -O0
 * return-value dead-double-b toolchain gap: our cc emits `lw v0; b epi; nop;
 * b epi(DEAD); nop`, the target has a single b — value-return -O0 cap,
 * docs/IDO_CODEGEN.md#feedback-ido-o0-return-value-dead-double-b, NOT C-fixable).
 *
 * LEVER KIT (the reusable part — cracked all diffs except the double-b):
 * (1) STRUCTURED-CONTROL-FLOW: IDO -O0 renders `if(E) goto L;` as a 2-insn
 *     branch-over (`b!E over; b L`), but `if(cond){body}` as a SINGLE
 *     `b!cond endif`. The target's alloc-cascade is all single branches, so
 *     express it as NESTED if(){} blocks: allocs guarded by `if(x==0){x=alloc;}`,
 *     the whole rest guarded by `if(a0!=0){...}` (that guard IS the
 *     a0-alloc-fail `beqz t7,end`). No goto/label anywhere.
 * (2) `register void *s0,s1;` = the callee-saved cascade temps (or s0,v0 / or
 *     s1,s0 — no home spill; plain locals would stack-home and lose the shape).
 * (3) TAIL RE-USE of the now-dead register vars as scratch (the target recycles
 *     $s0/$s1 once the cascade vars die): `s0=a0; s1=&D_0000C5AC;
 *     *(int*)(s0+0xC)=(int)s1;` -> `lw s0; lui s1; sw s1,0xC(s0)`; and
 *     `s0=a0; f(scratch,s0)` for the last call's arg.
 * (4) struct-typed func_00000008 (member .f2C/.f38) $at-fuses the global stashes
 *     (lui at; sw ...(at)) vs the (char*)&sym+off cast's lui/addiu/sw.
 * (5) D_bootup_scratch0 = int-typed base-0 alias of D_00000000 (undefined_syms)
 *     $at-fuses the *&D scratch store + reload.
 * RESIDUAL = the dead double-b only. NM stays. */
void *func_0000FD4C(void *a0, int a1, int a2) {
    register void *s0, *s1;

    if (a0 == 0) {
        a0 = (void*)func_00000000(0x50);
    }
    if (a0 != 0) {
        s0 = a0;
        if (s0 == 0) {
            s0 = (void*)func_00000000(0x50);
        }
        if (s0 != 0) {
            s1 = s0;
            if (s1 == 0) {
                s1 = (void*)func_00000000(0x2C);
            }
            if (s1 != 0) {
                func_00000000(s1, &D_0000C5A4);
                *(int*)((char*)s1 + 0x28) = (int)&D_00000000;
            }
            *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
        s0 = a0;
        s1 = (void*)&D_0000C5AC;
        *(int*)((char*)s0 + 0x0C) = (int)s1;
        func_00000008.f2C = a1;
        func_00000008.f38 = a2;
        *(int*)((char*)a0 + 0x44) = 0;
        *(int*)((char*)a0 + 0x48) = 0;
        D_bootup_scratch0 = func_00000000(a0, 0);
        s0 = a0;
        func_00000000(D_bootup_scratch0, s0);
    }
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);
#endif

/* func_0000FEA0: 18-insn indirect-call wrapper:
 *   p = a0->field_28; (*p->field_64)(a0 + (short)p->field_60).
 * MATCHED 2026-07-10 (w50 island sweep, 18/18): the long-documented
 * "double-reload residual cap" (19 vs 18 insns) was the cfe DAG-share
 * lever from func_0000F6C4 — single expression statement with the
 * register-p assignment EMBEDDED IN THE ARG:
 *   (*(void(**)())(p + 0x64))(*(short*)((p = *(char**)(a0+0x28)) + 0x60) + a0);
 * The arg's `+ a0` DAG-shares the assignment chain's a0 home reload
 * (t6) -> `addu a0,t7,t6` with no second lw; fn-ptr load lands in $t9.
 * Required flipping this file to -O0 (all other members stay INCLUDE_ASM
 * so the flag only affects this compiled body). Old exhaustive-variant
 * notes retired: all four 2026-05-08 variants were two-statement forms. */
void func_0000FEA0(char *a0) {
    register char *p;
    (*(void(**)())(p + 0x64))(*(short*)((p = *(char**)(a0 + 0x28)) + 0x60) + a0);
}

/* func_0000FEE8 - verified structural decode (0x208, 130 insns,
 * get-or-create constructor + normalized-colour init). bootup_uso
 * constructor family (cf. func_00005124 / func_0001438C).
 *   void *func_0000FEE8(void *a0) {
 *       o = a0 ? a0 : func_00000000(0x304);
 *       if (!o) return 0;
 *       s = func_00000000(0x2C);
 *       if (!s) return ...;
 *       func_00000000(s, &D_0000C5BC);            // init sub
 *       s->0x28 = &D_a;                            // descriptor
 *       o->0x28 = &D_b;                            // descriptor
 *       o->0xC  = &D_0000C5C4;                     // type/vtable
 *       f32 *c = (f32*)((char*)o + 0x4C);
 *       c[0] = 0x77 / 255.0f;                      // 119/255
 *       c[1] = 0x75 / 255.0f;                      // 117/255
 *       c[2] = 0xE5 / 255.0f;                      // 229/255
 *       c[3] = ... / 255.0f;                       // (RGBA-ish)
 *       ... (further normalized float fields)
 *   }
 * Struct-typing reference: o = 0x304-byte object; o->0x28 (40)
 * descriptor (&D), o->0xC (12) type/vtable ptr (&D_0000C5C4).
 * s = 0x2C-byte sub-object (s->0x28 descriptor, init datum
 * D_0000C5BC). o+0x4C (76) = a float array initialized from u8
 * literals divided by 255.0f (0x437F0000) - a 0..1 normalized
 * colour / parameter vector (the int-byte / 255.0 idiom). Caps
 * <80: get-or-create + alloc-cascade (~3 reloc) + repeated
 * cvt.s.w + div.s by 255.0 chain + &D descriptors. Full body
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
#ifdef NON_MATCHING
/* 2026-06-04 EXTEND via Ghidra 24.5% -> 27.8%: added the 2nd color quad
 * (0x5c-0x68 = 0xC0/0xC2/0xE5/1.0 over 255), 0x80=0, the dead-arm 2nd alloc
 * cascade, and the tail init call. (Ghidra mis-shows the /255 colors as folded
 * word constants 0x3eeeeeef — the asm computes them via mtc1+cvt.s.w+div.s.)
 * Residual: get-or-create cascade keeps the object in $a2 (regalloc). */
void *func_0000FEE8(char *a0) {
    char *o;
    char *q;
    float *c;
    o = a0 ? a0 : (char *)func_00000000(0x304);
    if (!o) return 0;
    q = o;
    if (o != 0 || (q = (char *)func_00000000(0x2C)) != 0) {
        func_00000000(q, (char *)&D_00000000 + 0xC5BC);
        *(char **)(q + 0x28) = &D_00000000;
    }
    *(char **)(o + 0x28) = &D_00000000;
    *(char **)(o + 0xC) = (char *)&D_00000000 + 0xC5C4;
    c = (float *)(o + 0x4C);
    c[0] = (float)0x77 / 255.0f;
    c[1] = (float)0x75 / 255.0f;
    c[2] = (float)0xE5 / 255.0f;
    c[3] = 1.0f;
    c[4] = (float)0xC0 / 255.0f;
    c[5] = (float)0xC2 / 255.0f;
    c[6] = (float)0xE5 / 255.0f;
    c[7] = 1.0f;
    *(int *)(o + 0x80) = 0;
    func_00000000(o);
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);
#endif
