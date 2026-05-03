#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* USO entry-0: leading `beq zero,zero,+0x1BC00` trampoline (loader-patched
 * at runtime) followed by an empty void body. The 4-byte trampoline is
 * injected post-cc via PREFIX_BYTES (Makefile + scripts/inject-prefix-bytes.py).
 * The body is just jr ra + nop (8 bytes); after injection the function
 * symbol covers the full 12 bytes target wants. */
void h2hproc_uso_func_00000000(void) {
}

void h2hproc_uso_func_0000000C(void) {
}

void h2hproc_uso_func_00000014(int *a0, int a1) {
    a0[a1]++;
}

#ifdef NON_MATCHING
/* 71.88 % NM. 120-insn / 0x1E0 do-while loop wrapping a 7-case switch
 * dispatcher (jumptable form, IDO -O2 with .rodata).
 *
 * Loop shape:
 *   do {
 *       flag = 0;
 *       switch (a1) {  // jumptable, cases 0-6
 *           case N: setup(); jal_chain(); flag = 1; break;
 *           default: special_path();  // doesn't set flag
 *       }
 *       common_alloc_link();
 *       a1 = D[+0x40];                // re-read for next iter
 *   } while (flag == 0);
 *
 * Per case sets: s3=1 (success flag), D[+0x44]=5, D[+0x48]=6.
 * Default (a1>=7) does extra alloc work, doesn't set flag → loop iterates.
 *
 * Common cleanup chain: alloc(0,1,0) → r1; alloc(&D+0x10, r1) → r2;
 *   if (r2->0x14) r2->0x4 = 1; r2->0x14 = &D.
 *
 * IDO -O2 emits this switch as .rodata jumptable
 * (feedback_ido_switch_rodata_jumptable.md). 1080 discards .rodata, so
 * target's `lui at, 0; addu at,t6; lw t6, 0(at); jr t6` dispatch is
 * unreproducible from a C `switch` (would emit different bytes plus the
 * jumptable in a discarded section).
 *
 * Per feedback_ido_dispatch_goto_chain_beats_switch_and_ifelse.md, for
 * compares-grouped-at-top dispatchers we'd use the goto-chain idiom — but
 * THIS asm uses true jumptable (lui+lw+jr), not chained beq. Goto-chain
 * won't reproduce the jumptable bytes either; expected match cap likely
 * 40-60 % regardless of dispatch form.
 *
 * Body is structural skeleton only — does NOT execute correctly (the
 * switch cases call gl_func_00000000 with various small-int args, but
 * the actual data flow needs more decode work. Keep INCLUDE_ASM as the
 * default-build path; wrap is reference for next pass). */
void h2hproc_uso_func_0000002C(int *a0, int a1) {
    int *s0;
    int flag;
    int prev;

    do {
        flag = 0;
        switch (a1) {
            case 0:
                gl_func_00000000(a0);
                *(int*)((char*)&D_00000000 + 0x40) = 1;
                goto cleanup;
            case 1:
                gl_func_00000000(a0, 2, 7, 1);
                flag = 1;
                *(int*)((char*)&D_00000000 + 0x44) = 5;
                *(int*)((char*)&D_00000000 + 0x48) = 6;
                break;
            case 2:
                gl_func_00000000(a0, 2, 7, 1);
                flag = 1;
                *(int*)((char*)&D_00000000 + 0x44) = 5;
                *(int*)((char*)&D_00000000 + 0x48) = 6;
                break;
            case 3:
                gl_func_00000000(a0, 2, 7, 2);
                flag = 1;
                *(int*)((char*)&D_00000000 + 0x44) = 5;
                *(int*)((char*)&D_00000000 + 0x48) = 6;
                break;
            case 4:
                gl_func_00000000(a0, 2, 7, 4);
                flag = 1;
                *(int*)((char*)&D_00000000 + 0x44) = 5;
                *(int*)((char*)&D_00000000 + 0x48) = 6;
                break;
            case 5:
                gl_func_00000000(&D_00000000, 4,
                                 *(int*)((char*)&D_00000000 + 0x64), 4);
                flag = 1;
                gl_func_00000000(a0, *a0);
                prev = gl_func_00000000(0, 0x01450000, 0);
                gl_func_00000000(a0, 0, prev, *(int*)((char*)a0 + 8));
                break;
            case 6:
                gl_func_00000000(a0);
                flag = 1;
                break;
            default:
                break;
        }
cleanup:
        s0 = (int*)gl_func_00000000(0, 1, 0);
        s0 = (int*)gl_func_00000000(&D_00000000 + 0x10, s0);
        if (*(int*)((char*)s0 + 0x14) == 0) {
            *(int*)((char*)s0 + 0x14) = (int)&D_00000000;
        }
        *(int*)((char*)s0 + 0x4) = 1;
        *(int*)((char*)s0 + 0x14) = (int)&D_00000000;
        a1 = *(int*)((char*)&D_00000000 + 0x40);
    } while (flag == 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000002C);
#endif

void h2hproc_uso_func_0000020C(int *a0) {
    int saved = gl_func_00000000(2);
    a0[2] = gl_func_00000000(8);
    gl_func_00000000(saved);
    *a0 = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
    *(int*)a0[2] = 0;
    *(int*)(a0[2] + 4) = 0;
    *(int*)((char*)&D_00000000 + 0x68) = 0;
}

void h2hproc_uso_func_00000274(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso/h2hproc_uso_func_00000274_pad.s")

extern char *D_h2h_2A4_a;       /* call 1 base, *(D+4) */
extern char *D_h2h_2A4_b;       /* call 2 a0 + store +0x40 */
extern int  *D_h2h_2A4_c;       /* call 3 base, *D->0x30 = 0 + delay-arg */

void h2hproc_uso_func_000002A4(void) {
    gl_func_00000000(*(int*)((char*)&D_h2h_2A4_a + 4));
    *(int*)((char*)&D_h2h_2A4_b + 0x40) = 5;
    gl_func_00000000(&D_h2h_2A4_b);
    *(int*)((char*)D_h2h_2A4_c + 0x30) = 0;
    gl_func_00000000(D_h2h_2A4_c, -1, 0);
}

extern char *D_h2h_2FC_a;       /* call 1 base, *(D+4) */
extern char *D_h2h_2FC_b;       /* call 2 a0 + store +0x40 */
extern int  *D_h2h_2FC_c;       /* call 3 base, *D->0x30 = 0 + delay-arg */

void h2hproc_uso_func_000002FC(void) {
    gl_func_00000000(*(int*)((char*)&D_h2h_2FC_a + 4));
    *(int*)((char*)&D_h2h_2FC_b + 0x40) = 2;
    gl_func_00000000(&D_h2h_2FC_b);
    *(int*)((char*)D_h2h_2FC_c + 0x30) = 0;
    gl_func_00000000(D_h2h_2FC_c, -1, 0);
}

extern char *D_h2h_354_a;       /* call 1 base, *(D+4) */
extern char *D_h2h_354_b;       /* call 2 a0 + store +0x40 */
extern int  *D_h2h_354_c;       /* call 3 base, *D->0x30 = 0 + delay-arg */

void h2hproc_uso_func_00000354(void) {
    gl_func_00000000(*(int*)((char*)&D_h2h_354_a + 4));
    *(int*)((char*)&D_h2h_354_b + 0x40) = 3;
    gl_func_00000000(&D_h2h_354_b);
    *(int*)((char*)D_h2h_354_c + 0x30) = 0;
    gl_func_00000000(D_h2h_354_c, -1, 0);
}

extern char *D_h2h_3AC_a;       /* call 1 base, *(D+4) */
extern char *D_h2h_3AC_b;       /* call 2 a0 + store +0x40 */
extern int  *D_h2h_3AC_c;       /* call 3 base, *D->0x30 = 0 + delay-arg */

void h2hproc_uso_func_000003AC(void) {
    gl_func_00000000(*(int*)((char*)&D_h2h_3AC_a + 4));
    *(int*)((char*)&D_h2h_3AC_b + 0x40) = 4;
    gl_func_00000000(&D_h2h_3AC_b);
    *(int*)((char*)D_h2h_3AC_c + 0x30) = 0;
    gl_func_00000000(D_h2h_3AC_c, -1, 0);
}

extern char *D_h2h_404_a;       /* call 1 base, *(D+4) */
extern char *D_h2h_404_b;       /* call 2 a0 + store +0x40 */
extern int  *D_h2h_404_c;       /* call 3 base, *D->0x30 = 0 + delay-arg */

void h2hproc_uso_func_00000404(void) {
    gl_func_00000000(*(int*)((char*)&D_h2h_404_a + 4));
    *(int*)((char*)&D_h2h_404_b + 0x40) = 6;
    gl_func_00000000(&D_h2h_404_b);
    *(int*)((char*)D_h2h_404_c + 0x30) = 0;
    gl_func_00000000(D_h2h_404_c, -1, 0);
}

void h2hproc_uso_func_0000045C(void) {
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(*(int*)(*(char**)&D_00000000 + 0x6B0));
    gl_func_00000000(&D_00000000);
}

/* h2hproc_uso_func_0000049C: 2-insn fragment (0x8), NO jr ra (grep -c=0).
 *   lui   a0, 0
 *   lw    a0, 0(a0)        ; a0 = *D_00000000
 * Falls through directly into func_000004A4 (real prologue at 0x4A4).
 * Alternate entry point: callers `jal 0x49C` get a0 reset to
 * *D_00000000 before the 4A4 body runs (callers don't supply a0).
 * Not reachable from C (no standalone function signature for an
 * alt-entry that falls through). Per feedback_split_fragments_unreachable_tail
 * class — leave INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_0000049C);

void h2hproc_uso_func_000004A4(char *a0) {
    gl_func_00000000(a0, *(int*)(a0 + 0x6B4) ^ 1);
    gl_func_00000000(*(int*)&D_00000000);
    gl_func_00000000(&D_00000000);
}

void h2hproc_uso_func_000004E0(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_0000051C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void h2hproc_uso_func_00000558(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void h2hproc_uso_func_000005B0(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000620);

#ifdef NON_MATCHING
/* 0x8EC + 0x944 are BYTE-IDENTICAL sibling functions (verified). Decoded:
 *   void f(char *a0, int a1) {
 *     a0->0x6B8 = a1;
 *     gl_func_X(a0->0x6A8);                  ; first call - shared
 *     if (a1 != 0) gl_func_T(a0);            ; true path
 *     else         gl_func_F(a0);            ; false path
 *   }
 *
 * The two branches call DIFFERENT real functions at runtime via USO loader's
 * placeholder relocation table. Both jal targets are 0x0C000000 (= jal 0)
 * but the relocation entries differ. IDO can only emit this if-else if the
 * two callees are distinct symbols (per feedback_usoplaceholder_unique_extern.md);
 * with a single shared `gl_func_00000000` decl, IDO will collapse the
 * identical-body if-else and emit only one jal.
 *
 * NM body uses simple shared-call form (loses the branch). Cap ~70% (single
 * jal in body where target has bne+two jals). Promotion path: declare
 * gl_func_h2hproc_8EC_t / gl_func_h2hproc_8EC_f as unique externs in
 * undefined_syms_auto.txt, then call them distinctly in the if/else arms. */
void h2hproc_uso_func_000008EC(char *a0, int a1) {
    *(int*)(a0 + 0x6B8) = a1;
    gl_func_00000000(*(int*)(a0 + 0x6A8));
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000008EC);
#endif

#ifdef NON_MATCHING
/* Sibling of h2hproc_uso_func_000008EC -- byte-identical asm. Same NM cap.
 * See full notes on 0x8EC. */
void h2hproc_uso_func_00000944(char *a0, int a1) {
    *(int*)(a0 + 0x6B8) = a1;
    gl_func_00000000(*(int*)(a0 + 0x6A8));
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000944);
#endif

void h2hproc_uso_func_0000099C(int *a0) {
    int v;
    gl_func_00000000(&D_00000000, *(int*)((char*)a0 + 0x514) - 1);
    v = *(int*)((char*)a0 + 0x514) - 1;
    *(int*)((char*)a0 + 0x6B4) = v;
    gl_func_00000000(*(int*)((char*)a0 + 0x48), v * 120 + 60);
}

#ifdef NON_MATCHING
/* 83.00% NM (cap: IDO &D base-register form). Logic verified correct by
 * walking the asm: target's `beql t9,zero,end; lw ra (delay); sw v1,0(at)`
 * → if (method_ptr != 0) { D[0]=a0; call(); } else early-out. Same as mine.
 *
 * Concrete diff (2026-05-02, after measure):
 *   target: `lui at,0; lw v0,0x48(at); ...; sw v1,0(at)` — &D held in $at
 *           with offset folded into lw/sw immediate (single hi-only setup,
 *           reused for both load D[0x48] and store D[0]).
 *   mine:   `lui t0,0; addiu t0,t0,0; lw a1,0x48(t0); ...; sw a0,0(t0)` —
 *           &D fully computed (lui+addiu) into $t0, then offset added.
 *
 * Tried (this run): unique-extern aliases for D+0x190, D+0x48, D+0x0
 * (per feedback_combine_prologue_steals_with_unique_extern.md). Regressed
 * to 82.75% — IDO emits separate hi/lo pairs for each unique extern,
 * losing target's single-hi-shared-base form.
 *
 * The hi-only-with-offset address form is IDO's choice when the base is
 * used in narrow scope; the hi+addiu form kicks in for wider liveness.
 * Not C-flippable for this 6-use mix. Permuter or accept cap.
 *
 * 36-insn / 0x90 indirect-table dispatcher with double-method-call
 * pattern. Per /decompile run: structural decode, % to be measured.
 *
 * Decoded structure:
 *   v0 = gl_func(D[0x190]);          // probably "find subsystem"
 *   if (v0 != 0) {
 *       gl_func(5);                   // some setup with const 5
 *       a0_orig = saved_a0;
 *       v0 = D[0x48];                  // pointer table base
 *       idx = a0_orig->0x7C;           // index field
 *       method_ptr = (v0 + idx*0x28)[0x90 / 4];
 *       if (method_ptr != 0) {
 *           D[0] = a0_orig;
 *           method_ptr_2 = (v0 + a0_orig->0x7C * 0x28)[0x90 / 4];
 *           method_ptr_2(arg = 0x28);   // jalr indirect call
 *       }
 *   }
 *
 * Trailing 2 insns past `jr ra; nop` (jr ra; sw zero,0x504(a0)) are part
 * of the SUCCESSOR function (likely h2hproc_uso_func_00000A80) — splat
 * boundary issue. Fix in a future tick. */
void h2hproc_uso_func_000009F8(int *a0) {
    extern char D_00000000;
    int *p;
    int v;
    if (gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190)) != 0) {
        gl_func_00000000(5);
        v = *(int*)((char*)&D_00000000 + 0x48);
        p = (int*)(v + a0[0x7C/4] * 0x28);
        if (p[0x90/4] != 0) {
            *(int**)&D_00000000 = a0;
            (*(void(**)(int))(v + a0[0x7C/4] * 0x28 + 0x90))(0x28);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000009F8);
#endif

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000A88);

void h2hproc_uso_func_00000BAC(int *a0) {
    int v0, v1;

    if (*(int*)((char*)*(int**)((char*)*(int**)((char*)a0 + 0x6AC) + 0x34) + 0x3C) < 0xFF) {
        *(int*)((char*)a0 + 0x4F4) = 1;
        return;
    }
    v0 = *(int*)((char*)&D_00000000 + 0x170);
    v1 = *(int*)((char*)&D_00000000 + 0x174);
    if ((unsigned)v1 < (unsigned)v0) v0 = v1;
    gl_func_00000000(a0, v0 + 0x26000F);
}

#ifdef NON_MATCHING
/* 123-insn / 0x1EC orchestrator for h2h player setup.
 * Sibling of func_00000BAC by offset (immediately follows).
 *
 * Entry dispatch:
 *   v1 = a0->0x6B8;   // h2h slot index, or -1 for default
 *   if (v1 == -1):
 *       s2 = D->0x134->0xC4;
 *   else:
 *       s2 = (D->0x134 + v1*8)->0xC4;        // indexed slot
 *
 * Then runs a fixed setup sequence:
 *  1. (D->0x134->0xC4)[0xA58/4] |= 0x8000
 *  2. (D->0x134->0xCC->0xA58 region) |= 0x8000  (writes to v1+0xA58 base)
 *  3. tmp1 = gl_func(D->0x134, 0, D->0x134->0x80, s2, s2->0x800)
 *  4. tmp2 = gl_func(D->0x134, 1, D->0x134->0x80, s2, s2->0x800)
 *  5. a0->0x520 = D->0x134->0x108                             // pointer copy
 *  6. (a0->0x520 + 0x18) field &= 0xFFFFFFF7                  // clear bit 3
 *  7. (a0->0x520 + 0x18) field &= 0xFFFFFFFB                  // clear bit 2
 *  8. (D->0x134->0x10C + 0x18) field &= ~(0x8 | 0x4)
 *  9. gl_func(D->0x134, &D2 + 0x1C, tmp1)
 * 10. a0->0x51C = result; D->0x134->0x108 = result
 * 11. a0->0x520 = gl_func(D->0x134, 0x80) -- but only if a0->0x520->0x14 == 0?
 *     followed by *->0x4 = 1 / *->0x14 = D->0x134
 * 12. gl_func(D->0x134, a0, D->0x134->0x84+0x10, ...)
 * 13. a0->0x4F0 &= 0xFEFFFFFF                                  // clear bit 24
 *
 * Many cross-USO calls (jal 0 + delay-slot spill of t4/t5/etc into stack args).
 * Extensive use of unique D_-base addrs for D->0x134, D->0x108, D->0x10C, etc.
 *
 * First-pass decode; structure preserved without byte-match attempt this run.
 * Default build still uses INCLUDE_ASM. Multi-pass refinement expected. */
void h2hproc_uso_func_00000C18(int *a0) {
    int *slot;
    int idx;
    int *root;
    int *s518_ret;
    int *bound;
    int v;

    idx = *(int*)((char*)a0 + 0x6B8);
    root = *(int**)((char*)&D_00000000 + 0x134);
    if (idx == -1) {
        slot = *(int**)((char*)root + 0xC4);
    } else {
        slot = *(int**)((char*)((char*)root + idx * 8) + 0xC4);
    }

    /* Set 0x8000 flag on slot's 0xA58 region (root->0xC4 + 0xA58). */
    *(int*)((char*)slot + 0xA58) = *(int*)((char*)slot + 0xA58) | 0x8000;
    /* Same for root->0xCC's 0xA58 region. */
    {
        int *r2 = *(int**)((char*)root + 0xCC);
        *(int*)((char*)r2 + 0xA58) = *(int*)((char*)r2 + 0xA58) | 0x8000;
    }

    /* Two parallel gl_func calls — likely "make per-side data" paired. */
    s518_ret = (int*)gl_func_00000000(root, 0, *(int*)((char*)root + 0x80), slot, *(int*)((char*)slot + 0x800));
    bound    = (int*)gl_func_00000000(root, 1, *(int*)((char*)root + 0x80), slot, *(int*)((char*)slot + 0x800));

    /* Mask off bits 3/2 on the 0x108-pointed struct's 0x18 field. */
    {
        int *p108 = *(int**)((char*)root + 0x108);
        *(int*)((char*)a0 + 0x520) = (int)p108;
        *(int*)((char*)p108 + 0x18) = *(int*)((char*)p108 + 0x18) & ~0x8;
        *(int*)((char*)p108 + 0x18) = *(int*)((char*)p108 + 0x18) & ~0x4;
    }
    /* Mask off bits 3/2 on 0x10C-pointed struct's 0x18 field (combined). */
    {
        int *p10C = *(int**)((char*)root + 0x10C);
        v = *(int*)((char*)p10C + 0x18) & ~0x8;
        *(int*)((char*)p10C + 0x18) = v;
        *(int*)((char*)p10C + 0x18) = v & ~0x4;
    }

    /* Bind retval, post-setup calls. */
    {
        int *retbind = (int*)gl_func_00000000(root, &D_00000000 + 0x1C, s518_ret);
        *(int*)((char*)a0 + 0x51C) = (int)retbind;
        *(int*)((char*)root + 0x108) = (int)retbind;

        if (*(int*)((char*)retbind + 0x14) == 0) {
            int *alloc2 = (int*)gl_func_00000000(root, 0x80);
            *(int*)((char*)retbind + 0x14) = (int)alloc2;
            *(int*)((char*)alloc2 + 0x4) = 1;
            *(int*)((char*)alloc2 + 0x14) = (int)retbind;
        }
        gl_func_00000000(root, a0, *(int*)((char*)root + 0x84) + 0x10);
    }

    /* Final flag clear. */
    *(int*)((char*)a0 + 0x4F0) = *(int*)((char*)a0 + 0x4F0) & 0xFEFFFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000C18);
#endif

#ifdef NON_MATCHING
/* 43-insn / 0xAC h2h dual-side update routine. Sibling-by-offset of
 * func_00000C18 (also touches D->0x134's 0xC4/0xCC sub-pointers).
 *
 * Decoded:
 *   gl_func(a0, a1);                       // passthrough call (delay-slot saves)
 *   slotC4 = D->0x134->0xC4;
 *   slotC4->0x8DC = D->0x134->0x108;        // bind 0x108 onto C4's 0x8DC slot
 *   r1 = slotC4->0x800;
 *   gl_func(r1);                            // setup
 *   gl_func(r1, D->0x168, D->0x170);        // configure with x/y
 *   slotCC = D->0x134->0xCC;
 *   slotCC->0x8DC = D->0x134->0x108;        // same bind for CC side
 *   r2 = slotCC->0x800;
 *   gl_func(r2);                            // setup
 *   gl_func(r2, D->0x16C, D->0x174);        // configure
 *   gl_func(a0);                            // post-update call on root arg
 *   a0->0x4F4 = a1 & 0xFFFF;                // store low-16 of a1 into flag word
 *
 * Same 0xC4/0xCC pair structure as func_00000C18; D->0x168/0x170 paired
 * with D->0x16C/0x174 (likely (x0,y0) for left side, (x1,y1) for right).
 *
 * First-pass decode; not byte-matched. Default build INCLUDE_ASM unchanged. */
void h2hproc_uso_func_00000E04(int *a0, unsigned int a1) {
    int *root;
    int *slotC4, *slotCC;
    int *r1, *r2;

    gl_func_00000000(a0, a1);

    root = *(int**)((char*)&D_00000000 + 0x134);
    slotC4 = *(int**)((char*)root + 0xC4);
    *(int*)((char*)slotC4 + 0x8DC) = *(int*)((char*)root + 0x108);
    r1 = *(int**)((char*)slotC4 + 0x800);
    gl_func_00000000(r1);
    gl_func_00000000(r1, *(int*)((char*)root + 0x168), *(int*)((char*)root + 0x170));

    root = *(int**)((char*)&D_00000000 + 0x134);
    slotCC = *(int**)((char*)root + 0xCC);
    *(int*)((char*)slotCC + 0x8DC) = *(int*)((char*)root + 0x108);
    r2 = *(int**)((char*)slotCC + 0x800);
    gl_func_00000000(r2);
    gl_func_00000000(r2, *(int*)((char*)root + 0x16C), *(int*)((char*)root + 0x174));

    gl_func_00000000(a0);
    *(unsigned int*)((char*)a0 + 0x4F4) = a1 & 0xFFFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000E04);
#endif

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000EB0);

/* Cross-USO template: byte-identical to titproc_uso_func_00001E2C. Same C body
 * matches both per feedback_uso_accessor_template_reuse.md. Logic:
 *   v = a0->0x3C; if (v >= 0x100) v = 0xFF; if (v == 0) return;
 *   gl_func(&D_0, v, a0+0x2C); gl_func(&D_0, 0, 0, 0x13F, 0xEF, 0x10001); */
void h2hproc_uso_func_00000F60(char *a0) {
    int v = *(int*)(a0 + 0x3C);
    if (v >= 0x100) v = 0xFF;
    if (v == 0) return;
    gl_func_00000000(&D_00000000, v, a0 + 0x2C);
    gl_func_00000000(&D_00000000, 0, 0, 0x13F, 0xEF, 0x10001);
}

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00000FD0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001204);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001360);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000015F0);

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_000017A0);

void h2hproc_uso_func_000019DC(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_000004E0((int*)(dst + 0x10));
}

void h2hproc_uso_func_00001A0C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_0000051C((float*)(dst + 0x10));
}

void h2hproc_uso_func_00001A3C(char *dst) {
    int tmp;
    h2hproc_uso_func_000004E0(&tmp);
    h2hproc_uso_func_00000558((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso", h2hproc_uso_func_00001A6C);

extern int h2hproc_uso_func_h2h_4DC();
extern int h2hproc_uso_func_h2h_5AC();

void h2hproc_uso_func_00001AFC(char *a0) {
    int tmp;
    h2hproc_uso_func_h2h_4DC(&tmp);
    h2hproc_uso_func_h2h_5AC(a0 + 0x10);
}
#pragma GLOBAL_ASM("asm/nonmatchings/h2hproc_uso/h2hproc_uso/h2hproc_uso_func_00001AFC_pad.s")

