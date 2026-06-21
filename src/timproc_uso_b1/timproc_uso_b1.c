#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* timproc_uso_b1_func_00000000 / _0000004C (contiguous -O0 run, 0x0..0xB0) live
 * in timproc_uso_b1_o0_0.c — carved into a dedicated -O0 sub-unit and
 * concatenated into the Yay0 block (region 0) before compression. See the
 * timproc_uso_block1_yay0 rule in the Makefile. */

#ifdef NON_MATCHING
/* timproc_uso_b1_func_000000B0: 0x4F4 (317 insns), 0x40-byte stack frame.
 * Untouched until 2026-05-03. Single function (grep -c 03E00008 = 1).
 *
 * 14-CASE SWITCH DISPATCH on a1 (insns 1-12):
 *   if ((u32)a1 >= 14) goto default_case;          ; sltiu+beqz
 *   t6 = jumptable[a1*4];                           ; jr t6
 *
 * Per feedback_ido_switch_rodata_jumptable.md, 1080's linker DISCARDS the
 * .rodata jumptable; matching requires if-else or if-goto chain rewrite
 * instead of the C `switch` statement. Same structural cap as the spine
 * function game_uso_func_00000B3C.
 *
 * CASE 0 (insns 13-22 @ 0xFC-0x120, decoded):
 *   gl_func_X(a0, 1, 7, 1)                          ; some 4-arg helper
 *   *(int*)(sp+0x44) = 4                            ; param? next-state?
 *   *(int*)(sp+0x48) = 0xD                          ; another param/const
 *
 * BODY (insns 23-317, ~290 insns remaining): per-case bodies for cases
 * 0..13. Each case dispatches to gl_func_00000000 with case-specific args
 * and returns. Heavy use of sp+0x44/0x48 as scratch params.
 *
 * Per feedback_partial_alloc_block_add_irreversible.md, NOT writing partial
 * body — the switch dispatch needs the FULL case-chain decoded together to
 * have any chance of matching the if-else rewrite. Default INCLUDE_ASM
 * matches via original asm. Multi-tick decompile expected. */
timproc_uso_b1_func_000000B0(a0, a1) int * a0; int a1; {
    char *d = (char *)&D_00000000;
    int done = 0;
    int state;
    int v, s0v;
    do {
        state = a1;
        if ((unsigned int)state < 14) {
        switch (state) {
        case 0:
            gl_func_00000000(a0, 1, 7, 1);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 1:
            gl_func_00000000(a0, 1, 7, 1);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 2:
            gl_func_00000000(a0, 1, 7, 2);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 3:
            gl_func_00000000(a0, 1, 7, 4);
            *(int *)(d + 0x44) = 4; *(int *)(d + 0x48) = 13; done = 1;
            break;
        case 4:
            gl_func_00000000(a0, 1, *(int *)(d + 0x64));
            *(int *)(d + 0x40) = 5;
            break;
        case 5:
            gl_func_00000000(d, *(int *)(d + 4));
            gl_func_00000000(d, 4, *(int *)(d + 0x64), 1);
            v = gl_func_00000000(a0, *a0, 1);
            s0v = gl_func_00000000(0, 0x410000, v, *a0);
            gl_func_00000000(a0, 0, s0v);
            done = 1;
            break;
        case 6:
            gl_func_00000000(a0, 0, *(unsigned char *)(d + 376));
            *(int *)(d + 0x40) = 7;
            break;
        case 7:
            gl_func_00000000(d, 10, *(int *)(d + 0x64), 1);
            v = gl_func_00000000(a0, *a0, 1);
            s0v = gl_func_00000000(0, *(int *)(d + 368) + 0x1A000F, v, *a0);
            gl_func_00000000(a0, 0, s0v);
            done = 1;
            break;
        case 8:
            gl_func_00000000(a0);
            *(int *)(d + 0x40) = *(int *)(d + 0x44);
            break;
        case 9:
            gl_func_00000000(a0);
            *(int *)(d + 0x40) = 10;
            break;
        case 10:
            gl_func_00000000(d, 7, 0, 0);
            s0v = gl_func_00000000(0);
            gl_func_00000000(a0, 1, s0v);
            done = 1;
            break;
        case 11:
            v = gl_func_00000000(a0, *a0, 4);
            s0v = gl_func_00000000(0, *(int *)(d + 368) + 0x20000, v, *a0);
            {
                char *r = (char *)s0v;
                gl_func_00000000(d + 16, r);
                if (*(int *)(r + 0x14) != 0) *(int *)(r + 0x4) = 1;
                *(int *)(r + 0x14) = (int)d;
            }
            gl_func_00000000(a0, *a0);
            done = 1;
            break;
        case 12:
            s0v = gl_func_00000000(*(int *)(d + 0x64));
            gl_func_00000000(a0, (*(int *)(d + 0x64) | 0x2000) | s0v, 8192, *a0);
            done = 1;
            break;
        case 13:
            s0v = gl_func_00000000(0, 1, 0);
            {
                char *r = (char *)s0v;
                gl_func_00000000(d + 16, r);
                if (*(int *)(r + 0x14) != 0) *(int *)(r + 0x4) = 1;
                *(int *)(r + 0x14) = (int)d;
            }
            done = 1;
            break;
        }
        }
        a1 = *(int *)(d + 0x40);
    } while (done == 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000000B0);
#endif

extern int D_00000148;
extern int D_0000014C;
extern int D_00000068;

/* 46-insn -O0 allocator-wrapper (0xB8). LANDED 2026-05-25 via splice-import-
 * donor-relocs recipe — compiled through donor file timproc_uso_b1_o0_5A4.c,
 * spliced in via REPLACE_FUNC_BODY; the updated splice (commit 8d1b9c93a in
 * scripts/replace-function-body.py) now imports the donor's HI16/LO16/26
 * relocs into the destination .o instead of dropping them. Combined with
 * D_00000148/0x14C/0x68 defined in undefined_syms_auto.txt = their offsets,
 * objdiff resolves the relocs to the same bytes expected/.o has post-link.
 * fuzzy=100. See feedback_splice_import_donor_relocs_recipe + the
 * project_1080_reloc_blind_caps_are_unlockable parent breakthrough.
 *
 * -O0 indicators preserved (the donor IS compiled at -O0):
 *   1. Unfilled jal delay slots, 2. `move s0, v0` save, 3. trailing `b
 *   epilogue; nop` before the epilogue, 4. Frame -0x28 with s0 save. */
void timproc_uso_b1_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    register int new_obj = gl_func_00000000(0, D_00000148, 1, arg2);
    *arg0 = (int*)new_obj;
    D_0000014C = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 1;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    D_00000068 = 0;
}

/* 21-insn -O0 helper. Sibling of 0x5A4. RELOC-BLIND CAP (residual 1 insn,
 * NOT byte-exact — corrected 2026-05-31). The donor (timproc_uso_b1_o0_65C.c,
 * spliced via REPLACE_FUNC_BODY) drops relocs to mirror the reloc-blind
 * expected/.o, but the final store `sw s0,0x14C(at)` needs 0x14C baked into the
 * %lo field — and no IDO-emittable C produces a 2-insn scalar store with the
 * offset literal in .text (the offset lives in the reloc-filled %lo; `D_0000014C`
 * gives field=0, `&D+0x14C` gives 3 insns at -O0). Real fix = spimdisasm USO-reloc
 * migration (expected/ becomes reloc-aware), per the donor comment + the
 * project's USO-reloc-migration TODO. Distinct from game_uso_func_0000D7F4, which
 * landed only because its 0xE90 baked into an ADDIU (struct-by-value base-
 * materialization), not a load/store %lo. Default build = donor splice. */
void timproc_uso_b1_func_0000065C(int *a0) {
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}

extern int D_b1_06B0_a;
extern char *D_b1_06B0_b;
extern int D_b1_06B0_c;
void timproc_uso_b1_func_000006B0(void) {
    gl_func_00000000(D_b1_06B0_a);
    gl_func_00000000(*(int*)(D_b1_06B0_b + 0x6A8));
    gl_func_00000000(&D_b1_06B0_c);
}

extern int D_b1_06F0_a;
extern int D_b1_06F0_b;
extern int D_b1_06F0_c;
void timproc_uso_b1_func_000006F0(void) {
    gl_func_00000000(D_b1_06F0_a);
    gl_func_00000000(&D_b1_06F0_b);
    gl_func_00000000(D_b1_06F0_c);
}
/* Chain sibling of 0x778, 0x7BC, 0x800. MATCHED via boundary correction
 * (replacing the banned PROLOGUE_STEALS): the leading `lui v0,0; addiu v0,0`
 * (&D_00000000 base for the +0x40/+0x44 stores) was emitted as the predecessor
 * func_000006F0's pad sidecar (stolen prologue); moved it into this fn's .s
 * (now 17 insns / 0x44, starts 0x72C) and removed that pad pragma. ROM bytes
 * preserved. (This fn's OWN pad sidecar below still holds 0x778's orphan.) */
extern int D_state_b1_734;
void timproc_uso_b1_func_00000734(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 1;
    gl_func_00000000(D_state_b1_734, -1, 0);
}
/* Chain sibling: t7=2. MATCHED via pad-sidecar boundary correction (orphan
 * lui v0,0; addiu v0,0 moved from func_00000734's pad into this fn's .s;
 * 0x3C->0x44, starts 0x770; pad pragma+.s removed). */
extern int D_state_b1_778;
void timproc_uso_b1_func_00000778(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(D_state_b1_778, -1, 0);
}
/* Chain sibling: t7=3. MATCHED via pad-sidecar boundary correction (orphan
 * moved from func_00000778's pad into this fn's .s; 0x3C->0x44, starts 0x7B4). */
extern int D_state_b1_7BC;
void timproc_uso_b1_func_000007BC(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 3;
    gl_func_00000000(D_state_b1_7BC, -1, 0);
}
/* Byte-identical sibling of timproc_uso_b3_func_00000818. MATCHED via
 * pad-sidecar boundary correction (orphan lui v0,0; addiu v0,0 moved from
 * func_000007BC's pad into this fn's .s; 0x3C->0x44, starts 0x7F8). End of the
 * timproc_uso_b1 chain (no own pad). */
extern int D_state_b1_800;
void timproc_uso_b1_func_00000800(void) {
    *(int*)((char*)&D_00000000 + 0x40) = 8;
    *(int*)((char*)&D_00000000 + 0x44) = 0xD;
    gl_func_00000000(D_state_b1_800, -1, 0);
}

void timproc_uso_b1_func_0000083C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_00000878(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void timproc_uso_b1_func_000008B4(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b1_func_0000090C(Vec3 *dst) {
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
/* timproc_uso_b1_func_0000097C — 232-insn manager get-or-create + register.
 * This is a SIBLING of timproc_uso_b3_func_00000994 (same constructor in a
 * different USO; sub-node alloc is 0xE0 here vs 0xDC there, else near-identical).
 *
 * FRAME PARTIAL-FIX DOESN'T MOVE THE METRIC (2026-06-01): removing 3 dead locals
 * shrank the build frame -0x48 -> -0x40 with ZERO fuzzy change (59.71552 both).
 * NOT because sp-offsets are unscored (they ARE — cf. 8A40's scored addiu-sp
 * diff) but because -0x40 is STILL != target -0x38, so the prologue/arg-home/
 * spill insns stay diffs either way. To move the metric the frame must hit -0x38
 * EXACTLY, which needs the cascade to use one fewer spill slot (target 4 work
 * slots, build 5). That extra slot is a register-allocation artifact of the 4
 * simultaneously-live cascade pointers (self/n1/n2/n3); reducing it needs the
 * regalloc dump (-Wo,-zdbug:6) or a per-fn structure change, not dead-local
 * removal. Dead locals removed for hygiene anyway. The family's 60-74% residual
 * is this slot-count + register-renumber, the documented hard cap.
 * 2026-06-01 (31.97 -> 59.71): ported 994's corrected structure block-by-block
 * (build-gated each step per docs/MATCHING_WORKFLOW.md incremental method):
 *   cascade  37.43 (5-stage goto-chain + distinct externs D_b1_097C_v0..3)
 *   field    42.84 (gl(self,a1,&D+0x3c0,a2); self->0x528=a3; gl(self); 0x72c=0)
 *   vtable   47.40 (sub->0x28=v4; D[0x138]=sub; sub->0xb4 cond; jalr dispatch;
 *                   gl(self+0x10,sub); beql sub->0x14 dance)
 *   regcond  59.71 (reg loop wrapped in `if((self->0x4f0<<15)<0)` + preamble +
 *                   post-loop beql dance)
 * TBD (same as 994): the MERGE TAIL (self->0x4f4=arg1&0xffff; node=D[0x190]; ...)
 * regresses when added — frame -0x40 vs target -0x38 (extra cascade spill slot).
 * See timproc_uso_b3_func_00000994's note for the full blocker analysis. */
extern int gl_func_00000000();
extern char D_b1_097C_v0;
extern char D_b1_097C_v1;
extern char D_b1_097C_v2;
extern char D_b1_097C_v3;
extern char D_b1_097C_v4;
int timproc_uso_b1_func_0000097C(int *a0, int a1, int a2, int a3) {
    int *s0 = a0;
    int *n1, *n2, *n3;
    int *h;

    /* 5-stage get-or-create cascade (ported from sibling timproc_uso_b3_func_
     * 00000994): alloc self(0x730)/n1(0x6a8)/n2(0x50)/n3(0x2c); dead stage-guards
     * via goto-chain; each node->0x28 = vtable via DISTINCT extern (CSE-bust). */
    if (a0 == 0) {
        s0 = (int *)gl_func_00000000(0x730);
        if (s0 == 0) return 0;
    }
    n1 = s0;
    if (s0 == 0) { n1 = (int *)gl_func_00000000(0x6A8); if (n1 == 0) goto S_self; }
    n2 = n1;
    if (n1 == 0) { n2 = (int *)gl_func_00000000(0x50); if (n2 == 0) goto S_n1; }
    n3 = n2;
    if (n2 == 0) { n3 = (int *)gl_func_00000000(0x2C); if (n3 == 0) goto S_n2; }
    gl_func_00000000(n3, (char *)&D_00000000 + 0x3B8);
    n3[0x28 / 4] = (int)&D_b1_097C_v0;
S_n2:
    n2[0x28 / 4] = (int)&D_b1_097C_v1;
S_n1:
    n1[0x28 / 4] = (int)&D_b1_097C_v2;
    gl_func_00000000((char *)n1 + 0x50);
S_self:
    s0[0x28 / 4] = (int)&D_b1_097C_v3;
    s0[0x568 / 4] = 0;
    gl_func_00000000(s0, a1, (char *)&D_00000000 + 0x3C0, a2);
    s0[0x528 / 4] = a3;
    gl_func_00000000(s0);
    *(float *)&s0[0x72C / 4] = 0.0f;
    gl_func_00000000((char *)&D_00000000 + 0x3D0, 0);
    gl_func_00000000(&D_00000000, 0);

    h = (int *)gl_func_00000000(0xE0);
    if (h != 0) {
        h[0x28 / 4] = (int)&D_b1_097C_v4;
    }
    s0[0x6A8 / 4] = (int)h;
    *(int **)((char *)&D_00000000 + 0x138) = h;

    /* vtable-dispatch block */
    if ((s0[0x4F0 / 4] << 15) >= 0) {
        h[0xB4 / 4] = 0;
    } else {
        h[0xB4 / 4] = 11;
    }
    gl_func_00000000(h, s0, s0[0x568 / 4], s0[0x528 / 4]);
    {
        int *vt = (int *)h[0x28 / 4];
        ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)h);
    }
    gl_func_00000000((char *)s0 + 0x10, h);
    if (h[0x14 / 4] != 0) {
        h[0x4 / 4] = 1;
    }
    h[0x14 / 4] = (int)s0;

    /* registration block (only when self->0x4f0 bit16 set) */
    if ((s0[0x4F0 / 4] << 15) < 0) {
        s0[0x48 / 4] = (int)gl_func_00000000(0);
        gl_func_00000000(s0[0x48 / 4], s0);
        *(int *)((char *)s0[0x48 / 4] + 0x30) = s0[0x568 / 4];
        gl_func_00000000(s0[0x48 / 4], (*(int *)&D_00000000 + 3) << 16, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 1, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 4, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 3, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 2, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4], ((*(int *)&D_00000000 + 3) << 16) | 5, -1, &D_00000000);
        gl_func_00000000(s0[0x48 / 4]);
        gl_func_00000000((char *)s0 + 0x10, s0[0x48 / 4]);
        if (*(int *)((char *)s0[0x48 / 4] + 0x14) != 0) {
            *(int *)((char *)s0[0x48 / 4] + 0x4) = 1;
        }
        *(int *)((char *)s0[0x48 / 4] + 0x14) = (int)s0;
    }

    return (int)s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_0000097C);
#endif

/* 33-insn 5-call dispatcher: each call passes a different a0+offset and
 * a packed (high16|low16) constant. First two calls OR in the high half
 * with values loaded from D[0x4C]/D[0x54]; last three use pure constants
 * (0x0021000A / 0x0021000D / 0x00210009). */
extern int gl_func_00000000();
void timproc_uso_b1_func_00000D1C(char *a0) {
    gl_func_00000000(a0 + 0x6B4, *(int*)((char*)&D_00000000 + 0x4C) | 0x001D0000);
    gl_func_00000000(a0 + 0x6CC, *(int*)((char*)&D_00000000 + 0x54) | 0x001E0000);
    gl_func_00000000(a0 + 0x6FC, 0x0021000A);
    gl_func_00000000(a0 + 0x714, 0x0021000D);
    gl_func_00000000(a0 + 0x6E4, 0x00210009);
}

void timproc_uso_b1_func_00000DA0(char *a0) {
    gl_func_00000000(a0 + 0x6B4);
    gl_func_00000000(a0 + 0x6CC);
    gl_func_00000000(a0 + 0x6FC);
    gl_func_00000000(a0 + 0x714);
    gl_func_00000000(a0 + 0x6E4);
}

#ifdef NON_MATCHING
/* 98.57% — 5 register-position word-diffs only (regalloc-renumber).
 * NOT the splice-donor recipe class: tested 2026-05-26 with -O0 donor
 * (emitted 0x78 / 30 insn — 9 over target) and -O1 donor (emitted 0x5C /
 * 23 insn — 2 over target with early stack-spill); target is 0x54 / 21
 * insn at -O2-style register coloring but with FRESH temps (t7, t9, t8)
 * per reload of saved-a0 rather than reuse of a3. IDO 7.1 at any -O*
 * level reuses a3 after the first jal saves it; the "reload into fresh
 * temp" allocator decision is not C-reachable for our toolchain binary.
 * See feedback_splice_import_donor_relocs_recipe for the working sibling
 * (5A4/65C) cases, and project_1080_other_diff_nearmiss_vein for the
 * regalloc-renumber cap class. CAP — keep INCLUDE_ASM. */
/* 2026-06-10 re-test with the new session levers, ALL negative (still
 * the same 5 reload-reg diffs, ours a3-reuse vs target t7/t9/t8 fresh):
 * volatile-qualified PARAM (over-homes: 24 insns), post-call copy var
 * p=a0 (coalesced away, x2 placements), return-inside-if (epilogue
 * dup), arg4 as a0+0 / &a0[0] / int-typed a0 (all folded). The target's
 * temp numbering (t7 reload1, t8 li-1, t9 reload2) = pure expression-
 * temp pool, i.e. the post-call a0 web is MEMORY-RESIDENT in the
 * original; no tested C shape stops IDO from coalescing the web with
 * the a3 arg copy. Residual lever: uoptlist regalloc dump session. */
int timproc_uso_b1_func_00000DEC(char *a0) {
    if (*(int*)(a0 + 0x4FC) == 0) {
        gl_func_00000000(*(int*)(a0 + 0x6A8), 0, 1, a0);
        gl_func_00000000(*(int*)(a0 + 0x6A8));
        *(int*)(a0 + 0x4FC) = 1;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000DEC);
#endif

/* 32-insn dispatcher: lookup-call gates state set on D[0x40]/D[0x44]
 * then ALWAYS runs the t9 check (a0->[0x4F8] -> store-or-call).
 * v0!=0: D[0x40]=12, D[0x44]=9; v0==0: D[0x40]=9 (no D[0x44] write). */
void timproc_uso_b1_func_00000E40(int *a0) {
    int v0 = gl_func_00000000(*(int*)((char*)a0 + 0x528));
    if (v0 != 0) {
        *(int*)((char*)&D_00000000 + 0x40) = 0xC;
        *(int*)((char*)&D_00000000 + 0x44) = 9;
    } else {
        *(int*)((char*)&D_00000000 + 0x40) = 9;
    }
    if (*(int*)((char*)a0 + 0x4F8) == 0) {
        *(int*)((char*)a0 + 0x504) = 0;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

void timproc_uso_b1_func_00000EC0(int a0) {
    gl_func_00000000(&D_00000000 + 0x3D8);
    (void)a0;
}

/* timproc_uso_b1_func_00000EE8: 2-FUNCTION BUNDLE (0x1F4 / 125 insns).
 * Splat-bundled (USO segment); cannot be cleanly split per
 * feedback_uso_split_fragments_breaks_expected_match.md.
 *
 * F1 @ 0x0EE8-0x10BC: ~117 insns — heavy state-update orchestrator.
 *   Reads a0->[0x504] (t9), spills s0=a0, t9=1.
 *   if (t9 == 1) early-exit-with-store branch
 *   else: a0->[0x6A8] is the work pointer:
 *     - if work->[0x30] (lw t9) == s3=1 goto cleanup-with-jal-chain
 *     - main loop subu s2,s2,-1: iterate 0x10..0x70 over 0x10-stride
 *       struct fields, calling cross-USO funcs per element
 *     - 3 char-byte equality-test ladder at 0x0FA4-0x0FE0 (a3->[5/6/7]
 *       vs s7->[5/6/7]) — hash/sequence compare
 *     - on full match: a0->[0x4D8] = 1; gl_func(a0->[0x190], 3); commit
 *     - else: increment s0, sub s4 -1, branch back to loop head
 *   Tail: 5 cross-USO gl_func calls with shuffled args; jr ra at 0x10B8.
 *
 * F2 @ 0x10C0-0x10D0: 5 insns — `D[0x40] = 9; sw t6 (delay)`. Mini-stub
 *   that sets the dispatcher state field.
 *
 * Trailing 4 insns @ 0x10D4-0x10D8: `lui a1, 0; lw a1, 0x170(a1)` —
 * incomplete, likely a prologue-stolen prefix for F3 (next function).
 *
 * Multi-day decomp; this comment captures structural fingerprints for
 * future passes. Sibling of timproc_uso_b1_func_00000E40 (E40 sets the
 * D[0x40]/D[0x44] state, EE8 reads work-state and runs the orchestrator). */
#ifdef NON_MATCHING
/* Full structural decode 2026-06-01. State machine on obj->0x504:
 *   state 0: byte-compare scan loop over obj->0x6B0 elements (s1[5/6/7]
 *            vs result[5/6/7]); commits state=1.
 *   state 1: cascade of cross-USO gl_func calls (init/spawn chain).
 *   else:    return.
 * All cross-USO calls are gl_func_00000000 imports (reloc'd at load). */
void timproc_uso_b1_func_00000EE8(char *obj) {
    int state = *(int *)(obj + 0x504);
    int i;
    char *s1;
    char *r;
    char *o0;
    char *o1;

    if (state == 0) {
        *(int *)(obj + 0x6AC) = *(int *)(obj + 0x30);
        *(int *)(obj + 0x6B0) = *(int *)(*(char **)(obj + 0x44) + 0x38);
        s1 = (char *)gl_func_00000000(*(int *)(*(char **)(obj + 0x528)) + *(int *)((char *)&D_00000000 + 0x64) * 0x30);
        for (i = *(int *)(obj + 0x6B0) - 1; i >= 0; i--) {
            r = (char *)gl_func_00000000(*(int *)(*(char **)(obj + 0x528)) + *(int *)((char *)&D_00000000 + 0x64), i);
            if (*(unsigned char *)(s1 + 5) != *(unsigned char *)(r + 5)) break;
            if (*(unsigned char *)(s1 + 6) != *(unsigned char *)(r + 6)) break;
            if (*(unsigned char *)(s1 + 7) != *(unsigned char *)(r + 7)) break;
            *(int *)(obj + 0x6B0) = *(int *)(obj + 0x6B0) - 1;
        }
        *(int *)(obj + 0x4D8) = 1;
        gl_func_00000000(*(int *)(obj + 0x190), 3, 1);
        *(int *)(obj + 0x504) = 1;
    } else if (state == 1) {
        gl_func_00000000(*(int *)(obj + 0x190));
        if (gl_func_00000000() != 0) {
            gl_func_00000000(obj);
            gl_func_00000000((char *)&D_00000000);
            gl_func_00000000(obj);
            gl_func_00000000(obj, *(int *)(obj + 0x170) + 0x220000);
            *(int *)(obj + 0x524) = gl_func_00000000(0, obj, 0);
            o0 = *(char **)(obj + 0x524);
            gl_func_00000000(o0, *(int *)(obj + 0x528));
            o1 = *(char **)(obj + 0x56C);
            gl_func_00000000(o1 + 0x10, o0);
            if (*(int *)(o0 + 0x14) != 0) {
                *(int *)(o0 + 0x4) = 1;
            }
            *(int *)(o0 + 0x14) = (int)o1;
            gl_func_00000000(*(int *)(obj + 0x190), 1, 1);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00000EE8);
#endif

void timproc_uso_b1_func_000010C0(int a0) {
    *(int *)((char *)&D_00000000 + 0x40) = 9;
}

/* timproc_uso_b1_func_000010D4: 2-insn `lui a1; lw a1, 0x170(a1)` pre-load
 * fragment (sets $a1 = *(D+0x170) for successor 010DC). NOT C-emit-absorbed —
 * the earlier prune was mistaken (010C0 is a 5-insn `*(D+0x40)=9`, doesn't
 * emit these bytes); restored to keep the 8 bytes at vram 0x10D4-0x10DB in
 * the linked layout. SOURCE=4 audit 2026-06-01: not an accessor-template miss;
 * it mirrors timproc_uso_b3_func_00001088 and has no standalone C body.
 * INCLUDE_ASM (uninitialized-reg fragment, no standalone C). */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000010D4);

void timproc_uso_b1_func_00000000();

void timproc_uso_b1_func_000010DC(int a0, char *a1) {
    timproc_uso_b1_func_00000000(a0, a1 + 0x00220000);
}

extern int gl_ref_00000040;
extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00001100(int a0) {
    *(int *)((char *)&D_00000000 + 0x40) = 9;
    gl_func_00000000(a0, -1, 0);
}

/* Vtable-entry dispatcher (twin of timproc_uso_b3_func_000010E4). Pass 2 2026-06-10:
 * re-decode fixed the OLD body's structure -- the *40 is a real multu
 * with the stride in a register (variable stride; old body's shift
 * decomposition was wrong), the gl(5) arg loads EARLY into a0 before
 * the beqzl, and the if(1){} BB-split after the call is load-bearing
 * (the 4-for-4 v0/v1 lever). 29/40 -> 11 word-diffs remaining: stride
 * colors a2 vs target a0 (the 5-then-40 single-web trick did not take;
 * k still splits), and the fn-temp renumber downstream of it.
 * 2026-06-10 pseudo-order family sweep NEGATIVE: early-pseudo (stride
 * dead-initialized / pre-declared first) and decl reorders all leave
 * stride in a2. The residual is ARG-REGISTER coloring of a non-arg
 * value (a0 freed after the jal consumed the 5); none of the three
 * pseudo-order levers (BB-split / web-inversion / early-pseudo)
 * address arg-reg targeting. Remaining lever: uoptlist dump. */
#ifdef NON_MATCHING
extern int D_arg_b1_1130[];
extern int D_cur_b1_1130;
void timproc_uso_b1_func_00001130(int *self) {
  int *v0;
  int v1;
  int stride;
  if (gl_func_00000000(D_arg_b1_1130[0x190 / 4]) == 0) {
    return;
  }
  v0 = (int *) self[0x48 / 4];
  v1 = v0[0x7C / 4];
  if (v1 != 0) {
    gl_func_00000000(5);
    if (1) {
    }
    v0 = (int *) self[0x48 / 4];
    v1 = v0[0x7C / 4];
  }
  stride = 40;
  if (((void (*)(void)) (*((int *) ((((char *) v0) + (v1 * stride)) + 0x90)))) != 0) {
    D_cur_b1_1130 = (int) self;
    if (1) {
    }
    v0 = (int *) self[0x48 / 4];
    /* Direct indirect-call through the inline-loaded fn-ptr: coalesces the
     * index web with the $t9 call register exactly as the target does
     * (lw $t9; ...; lw $t9,0x90($t1); jalr $t9). 39/40 words; the single
     * residual is the addr addu operand order: target emits
     * `addu $t1,$v0,$t0` (base rs) but the inline web (required for the
     * $t9 coalesce) forces `addu $t1,$t0,$v0` (product rs). Naming the
     * index OR the address flips the addu to base-rs but breaks the $t9
     * coalesce (index/addr colors $v1) -> more diffs. The two are mutually
     * exclusive in C: web-unification with $t9 implies product-rs addu. */
    (*((void (**)(void)) ((((char *) v0) + (v0[0x7C / 4] * stride)) + 0x90)))();
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001130);
#endif

/* timproc_uso_b1_func_000011D0: 2-insn alt-entry (lui at,0x3F80; mtc1 at,$f0
 * = set f0=1.0f) that falls through into 000011D8. RECOVERED 2026-05-28 from
 * the Yay0 block_1 gap (no .s, segment was 2 words short). SOURCE=4 audit
 * 2026-06-01: not an accessor-template miss; this is a float-constant preload
 * fragment for the successor. INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D0);

/* timproc_uso_b1_func_000011D8 — verified structural decode (EE84-family,
 * 90 insns, 4% LEN-DIFF; branch-likely + FPU compares + D-consts + multi-
 * call = documented sub-80 ceiling → INCLUDE_ASM build path; struct ref).
 *   if (a0->0x500 == 0) return;
 *   if (*(float*)&D <= 0.0f) return;
 *   fv = *(float*)(a0+0x72C);
 *   if (fv < *(float*)(&D+0x40)) *(float*)(a0+0x72C) = fv + *(float*)(&D+0x44);
 *   s0->0x508 += 1;
 *   v0 = (((int*)s0->0x528)->0x14 & 1) && s0->0x4FC &&
 *        ((int*)((int*)(*(int*)(&D+0x138)))->0x44)->0x38 < 3;
 *   if (v0) {
 *     saved = gl_func_00000000(s0+0x6E4);
 *     gl_func_00000000(saved, (int)(255.0f * *(float*)(s0+0x72C)),
 *                       s0+0x2F0, s0+0x314);
 *     if (s0->0x508 & 8) {
 *       gl_func_00000000(saved, 160,160,3);
 *       gl_func_00000000(s0, 140, ((int*)s0->0x6A8)->0x30); return;
 *     }
 *   }
 *   gl_func_00000000(s0, 0, ((int*)s0->0x6A8)->0x30);
 * Struct-typing: a0->0x500 enable gate, 0x72C float accumulator (clamped
 * +D[0x44] while < D[0x40]), 0x508 frame counter (bit 0x8 tested), 0x528
 * obj (->0x14 bit 0x1), 0x4FC flag, 0x6E4 sub-obj (gl arg), 0x6A8 obj
 * (->0x30), 0x2F0/0x314 out bufs. D consts: [0]/[0x40]/[0x44] floats,
 * [0x138] global ptr. The 255.0f*x trunc.w.s is a float→u8 quantize.
 * 75.88 -> 82.34 (2026-05-31): the &D FP consts (&D+0/0x40/0x44) + the +0x138
 * pointer use DISTINCT externs (D_b1_11d8_0/40/44 float + D_b1_11d8_138 int) to
 * bust the &D-base CSE; and the v0 = (a && b && c) guard is inlined into the `if`
 * (removes the sltu boolean-materialization). Same family as the now-EXACT
 * mgrproc_uso_func_00002294. DEFERRED decode corrections (identified via the
 * branch-likely bytes, but they REGRESS the metric until the whole structural set
 * is fixed together — multi-tick): (1) the D[0] gate should be the body-WRAP form
 * `if (D[0] <= 0) { ... }` (target c.le.s; bc1fl), not the early `if(<=0)return`;
 * (2) the &D+0x138 chain is `*(*(p1+0x44)+0x38)` not `*(p1)+0x7C` (target
 * lw 0x138; lw 0x44; lw 0x38); (3) a missing {?}x4 Vec color buffer at sp+0x50
 * (frame -96 vs -48, 4 swc1 $f0). Still NON_MATCHING. */
extern float D_b1_11d8_0, D_b1_11d8_40, D_b1_11d8_44;
extern int D_b1_11d8_138;
#ifdef NON_MATCHING
void timproc_uso_b1_func_000011D8(char *a0) {
    char *s0 = a0;
    float fv;
    int saved;
    if (*(int *)(a0 + 0x500) == 0) return;
    if (D_b1_11d8_0 <= 0.0f) return;
    fv = *(float *)(a0 + 0x72C);
    if (fv < D_b1_11d8_40) {
        *(float *)(a0 + 0x72C) = fv + D_b1_11d8_44;
    }
    *(int *)(s0 + 0x508) = *(int *)(s0 + 0x508) + 1;
    if ((*(int *)(*(char **)(s0 + 0x528) + 0x14) & 1) &&
        *(int *)(s0 + 0x4FC) &&
        *(int *)(*(int *)(D_b1_11d8_138) + 0x44 + 0x38) < 3) {
        saved = (int)gl_func_00000000(s0 + 0x6E4);
        gl_func_00000000(saved, (int)(255.0f * *(float *)(s0 + 0x72C)),
                         s0 + 0x2F0, s0 + 0x314);
        if (*(int *)(s0 + 0x508) & 8) {
            gl_func_00000000(saved, 160, 160, 3);
            gl_func_00000000(s0, 140, *(int *)(*(char **)(s0 + 0x6A8) + 0x30));
            return;
        }
    }
    gl_func_00000000(s0, 0, *(int *)(*(char **)(s0 + 0x6A8) + 0x30));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000011D8);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00001340)();
void timproc_uso_b1_func_00001340(char *arg0, s32 arg1, s32 arg2) {
    f32 sp14C;
    f32 sp148;
    f32 sp144;
    f32 sp140;
    u8 spC0;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    u8 *sp68;
    u8 *sp64;
    u8 *sp60;
    f32 *sp58;
    f32 *temp_a2;
    s32 temp_a1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_s6_2;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s32 var_t1;
    u8 *temp_a0;
    u8 *temp_s1;
    u8 *temp_s6;
    u8 *temp_s7;
    u8 *var_s0;
    u8 temp_v0_2;
    char *temp_t2;
    char *temp_t3;
    char *temp_t4;

    sp140 = 1.0f;
    sp144 = 1.0f;
    sp148 = 1.0f;
    sp14C = 1.0f;
    if (FW(FW(arg0, 0x528), 0x14) & 1) {
        timproc_uso_b1_func_000000B0(0, (s32) (255.0f * FW(arg0, 0x72C)), (int)arg0 + 0x2A8, (int)arg0 + 0x2CC);
        temp_a0 = (int)arg0 + 0x714;
        sp68 = temp_a0;
        timproc_uso_b1_func_000000B0(temp_a0);
        temp_s6 = (int)arg0 + 0x6CC;
        temp_s3 = (s16) FW(FW(arg0, 0x724), 0x20) / 12;
        timproc_uso_b1_func_000000B0(temp_s6);
        temp_s7 = (int)arg0 + 0x6B4;
        timproc_uso_b1_func_000000B0(temp_s7);
        temp_s1 = (int)arg0 + 0x6FC;
        timproc_uso_b1_func_000000B0(temp_s1);
        timproc_uso_b1_func_000000B0(&spC0, 0x3F4, (arg2 / 60000), (char *) ((s32) (arg2 % 60000) / 1000), (s32) ((arg2 % 60000) % 1000) / 10);
        sp64 = temp_s6;
        sp60 = temp_s7;
        temp_v0 = timproc_uso_b1_func_000000B0(&spC0);
        temp_t4 = FW(arg0, 0x70C);
        temp_t2 = FW(arg0, 0x6DC);
        temp_t3 = FW(arg0, 0x6C4);
        temp_a2 = (int)arg1 + 0x32;
        temp_s2 = 0xA0 - ((s32) (FW(temp_t4, 0x20) + (temp_v0 * 0xD) + FW(temp_t2, 0x20) + FW(temp_t3, 0x20) + 0x10) / 2);
        temp_s4 = FW(temp_t3, 0x20) + temp_s2 + 4;
        temp_a1 = FW(temp_t2, 0x20) + temp_s4 + 4;
        temp_s6_2 = FW(temp_t4, 0x20) + temp_a1 + 8;
        sp90 = temp_s4;
        sp94 = temp_s2;
        sp98 = temp_v0;
        sp58 = temp_a2;
        timproc_uso_b1_func_000000B0(temp_s1, temp_a1, temp_a2, (char *)2);
        var_t1 = temp_v0;
        var_s0 = &spC0;
        var_s1 = 0;
        var_s2 = temp_s6_2;
        if (var_t1 > 0) {
            temp_s4_2 = var_t1 * 0xD;
            do {
                temp_v0_2 = *(int*)var_s0;
                if (temp_v0_2 == 0x5B) {
                    *var_s0 = 0xA;
                } else if (temp_v0_2 == 0x5D) {
                    *var_s0 = 0xB;
                } else {
                    *var_s0 = temp_v0_2 - 0x30;
                }
                sp98 = var_t1;
                timproc_uso_b1_func_000000B0(sp68, var_s2, (arg1 - ((s16) FW(FW(arg0, 0x724), 0x22) / 2)) + 0x32, (char *) (*(int*)var_s0 * temp_s3), temp_s3);
                var_s1 += 0xD;
                var_s0 += 1;
                var_s2 += 0xD;
            } while (var_s1 != temp_s4_2);
        }
        timproc_uso_b1_func_000000B0(sp64, (s32) (255.0f * FW(arg0, 0x72C)), &sp140, (char *)0xFF);
        timproc_uso_b1_func_000000B0(sp64, sp90, sp58, (char *)2);
        timproc_uso_b1_func_000000B0(sp60, (s32) (255.0f * FW(arg0, 0x72C)), &sp140, (char *)0xFF);
        timproc_uso_b1_func_000000B0(sp60, sp94, sp58, (char *)2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001340);
#endif

/* timproc_uso_b1_func_000016F8 — verified structural decode; near-clone
 * SIBLING of arcproc_uso_func_0000199C (same 4-level alloc-cascade ctor
 * template). Documented alloc-cascade defensive-dead-check + spill/reloc
 * ceiling → <80 INCLUDE_ASM build path; struct-typing cross-confirm.
 * int *f(int *a0, int a1, int a2){
 *   s0 = a0 ? a0 : gl_func_00000000(268);  if(!s0) return s0;
 *   p2 = gl_func_00000000(212);  if(!p2) goto init4;
 *   p3 = gl_func_00000000(80);   if(!p3) goto init3;
 *   p4 = gl_func_00000000(44);   if(!p4) goto init2;
 *   gl_func_00000000(p4, &D+0x404); p4->0x28=&D;     // 199C used &D+0x3DC
 * init2: p3->0x28=&D; init3: p2->0x28=&D; init4: s0->0x28=&D;
 *   s0->0x60=a2;
 *   s0->0xE0=160; s0->0xE4=29; s0->0xD8=160; s0->0xDC=130;
 *   s0->0xE8=160; s0->0xEC=105; *(float*)(s0+0x108)=1.0f;
 *   s0->0xD4=a1; *(float*)(a1+0x72C)=1.0f;           // 199C: a1+0x77C
 *   gl_func_00000000(s0+0xF0,
 *       ((*(int*)&D + 35) << 16) | (((int*)s0->0xD4)->0x6B0 + 7)); // 199C: 0x6B4
 *   return s0;
 * }
 * Cross-confirms the 199C ctor family: object sizes 268/212/80/44, every
 * sub-object ptr @0x28=&D, s0 field block 0xD8..0xEC={160,130,160,29,160,
 * 105} + 0x60=a2 + 0xD4=a1 + 0x108=1.0f. This sibling's deltas vs 199C:
 * a1-base &D+0x404 (was 0x3DC), a1->0x72C (was 0x77C), s0->0xD4->0x6B0
 * (was 0x6B4). Caps <80: defensive `if(ptr!=0)skip` alloc-cascade dead
 * checks + per-call stack-spill + &D %hi/%lo reloc scheduling (same as
 * 199C, ~9%). INCLUDE_ASM is the correct build path (no episode). */
#ifdef NON_MATCHING
char *timproc_uso_b1_func_000016F8(char *a0, char *a1, int a2) {
    char *s0;
    char *p2;
    char *p3;
    char *p4;
    s0 = a0 ? a0 : (char *)gl_func_00000000(268);
    if (!s0) return s0;
    p2 = (char *)gl_func_00000000(212);
    if (p2) {
        p3 = (char *)gl_func_00000000(80);
        if (p3) {
            p4 = (char *)gl_func_00000000(44);
            if (p4) {
                gl_func_00000000(p4, (char *)&D_00000000 + 0x404);
                *(char **)(p4 + 0x28) = &D_00000000;
            }
            *(char **)(p3 + 0x28) = &D_00000000;
        }
        *(char **)(p2 + 0x28) = &D_00000000;
    }
    *(char **)(s0 + 0x28) = &D_00000000;
    *(int *)(s0 + 0x60) = a2;
    *(int *)(s0 + 0xE0) = 160;
    *(int *)(s0 + 0xE4) = 29;
    *(int *)(s0 + 0xD8) = 160;
    *(int *)(s0 + 0xDC) = 130;
    *(int *)(s0 + 0xE8) = 160;
    *(int *)(s0 + 0xEC) = 105;
    *(float *)(s0 + 0x108) = 1.0f;
    *(char **)(s0 + 0xD4) = a1;
    *(float *)(a1 + 0x72C) = 1.0f;
    gl_func_00000000(s0 + 0xF0,
        ((*(int *)&D_00000000 + 35) << 16) | (*(int *)(*(char **)(s0 + 0xD4) + 0x6B0) + 7));
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000016F8);
#endif

void timproc_uso_b1_func_00001860(int *a0) {
    if (gl_func_00000000(*(int*)(&D_00000000 + 0x190)) == 0) return;
    if (gl_func_00000000(&D_00000000, 0x40100) == 0) return;
    if (gl_func_00000000(a0[0x50/4]) != 0) {
        a0[0x60/4] = 1;
    } else {
        gl_func_00000000(a0, -1, 0);
    }
}

void timproc_uso_b1_func_000018D4(char *a0) {
    char *p;
    gl_func_00000000(a0);
    p = *(char**)(a0 + 0xD4);
    gl_func_00000000(p, 0x8C, *(int*)(p + 0x6AC));
}

/* Decay-tick handler: decrement sub->f_72C by the global rate (D+0x48),
 * clamp at 0, fire the 140-event mid-call, and on reaching <= 0 fire
 * the threshold call. MATCHED 2026-06-10 (44/44): the old wrap had a
 * DECODE ERROR (the mid-call's arg0 is SUB, not self) and a misplaced
 * sub-reload (only the clamp-taken path reloads); the final read goes
 * through the inlined full chain (fresh temp t6) rather than the sub
 * variable (whose web would color a0). bc1fl delay structure falls out
 * naturally from the val-carried if/if shape. */
void timproc_uso_b1_func_00001908(int *self) {
    char *base = &D_00000000;
    int *sub;
    float *fp;
    float val;

    gl_func_00000000(self);
    sub = (int *)self[0xD4 / 4];
    fp = (float *)((char *)sub + 0x72C);
    val = *fp;
    if (val > 0.0f) {
        *fp -= *(float *)(base + 0x48);
        sub = (int *)self[0xD4 / 4];
        if (*(float *)((char *)sub + 0x72C) < 0.0f) {
            *(float *)((char *)sub + 0x72C) = 0.0f;
            sub = (int *)self[0xD4 / 4];
        }
        gl_func_00000000(sub, 140, *(int *)((char *)sub + 0x6AC));
        val = *(float *)((char *)(int *)self[0xD4 / 4] + 0x72C);
    }
    if (val <= 0.0f) {
        gl_func_00000000(self);
    }
}
/* vram 0x19B8: 2-word stolen-prologue orphan (lui $at,0x3F80; mtc1 $at,$f0
 * = the 1.0f that func_000019C0 stores from $f0). Standalone 2-word
 * GLOBAL_ASM emits exactly; see the .s header. */
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_orphan_000019B8.s")


#ifdef NON_MATCHING
/* timproc_uso_b1_func_000019C0: byte-identical mirror of
 * arcproc_uso_func_00001C74 (sig=739fd8d1d3, 41-insn 0xA4 counter+
 * conditional-scale wrapper).
 *
 * Per scripts/find-byte-identical-clones.py — see arcproc_uso_func_00001C74's
 * wrap doc for full structural decode. Mirrored source=4 2026-06-01; expected
 * to inherit the same O2 residual as the canonical arcproc body (target 0x58
 * frame + incoming-$f0 stores vs C's explicit-zero smaller frame).
 * 2026-06-10 negatives: an uninitialized `float g; buf[i]=g;` and the
 * `register float g` variant BOTH emit lwc1-from-home first (IDO homes
 * even uninit register floats) -- the target's store-only swc1 $f0 x4
 * with NO prior load/set of $f0 remains C-unreachable; the value is
 * literally the incoming garbage register. Cap stands. */
void timproc_uso_b1_func_000019C0(int *a0) {
    float buf[4];

    buf[0] = 0.0f;
    buf[1] = 0.0f;
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    *(int *)((char *)a0 + 0x68) += 1;
    if (gl_func_00000000(*(int *)((char *)a0 + 0x50)) != 0) {
        gl_func_00000000(&D_00000000, (int)(255.0f * *(float *)((char *)a0 + 0x108)), buf);
        gl_func_00000000((char *)a0 + 0xF0);
        if ((*(int *)((char *)a0 + 0x68) & 8) != 0) {
            gl_func_00000000((char *)a0 + 0xF0, 0xA0, 0x7C, 3);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000019C0);
#endif

/* timproc_uso_b1_func_00001A64 — verified structural decode (89-insn
 * init+configure constructor; 8 gl_ calls + branch-likely list-link tail
 * = documented constructor sub-80 ceiling → INCLUDE_ASM build path;
 * struct-typing reference).
 * void f(int *a0, int a1, int a2, int a3){
 *   s0 = a0;
 *   a0->0xC  = &D_00000000 + 0x40C;
 *   a0->0xB8 = a1;  a0->0x50 = a1;  a0->0x4C = a3;
 *   a0->0xAC = 0;   a0->0xD8 = 0;   a0->0x54 = a2;
 *   a0->0xD0 = 255; a0->0xD4 = 0;   a0->0xDC = 1;
 *   *(float*)(a0+0xCC)=*(float*)(a0+0xC8)=*(float*)(a0+0xC4)=
 *     *(float*)(a0+0xC0)=1.0f;
 *   if (((int*)a1)->0x4F0 << 15 >= 0) {        // bgezl on (a1->0x4F0)<<15
 *     gl_func_00000000(s0, 232, 19, s0->0x44 + 16);     // s0->0x44 = a3 home
 *     gl_func_00000000(s0, 291, 225, 1);
 *     gl_func_00000000(s0, 71, 19, s0+0x30);
 *     gl_func_00000000(s0, 68, 34, s0->0x44 + 40);
 *     // table lookup: t3=*(int*)(&D+0x64); base=*(int*)s0->0x4C;
 *     gl_func_00000000(base + (t3*0x3C)*16 ...);          // (t3*4-t3)<<4 = t3*0x30
 *     v0 = gl_func_00000000(s0->0x60); s0->0xBC = v0;
 *     gl_func_00000000(v0, v1[5], v1[6], v1[7]);          // v1 = prev ret
 *     gl_func_00000000(s0->0xBC, 75, 214);
 *     gl_func_00000000(s0+0x10, s0->0xBC);
 *     a1x = ...; if (a1x->0x14 == 0) a1x->0x4 = 1;
 *     a1x->0x14 = s0;                                     // list link
 *   }
 * }
 * Struct-typing: a0 widget/element — ptr @0xC (&D+0x40C), @0xB8/@0x50
 * both = a1 (parent?), @0x4C = a3, @0x54 = a2, flags @0xAC/@0xD8/@0xD4
 * zeroed, @0xD0 = 255 (alpha), @0xDC = 1, float quad @0xC0..@0xCC = 1.0f
 * (scale/color), @0x44 sub-region base, @0x60 handle, @0xBC built child,
 * @0x30 inline sub-struct, @0x10 another. a1->0x4F0 bit-31-after-<<15
 * gates the whole configure block. Linked into a1x->0x14 list (sets
 * ->0x4=1 on first). Caps <80: 8-call spill cascade + beql/bgezl branch-
 * likely + &D %hi/%lo + 1.0f/255 const scheduling. INCLUDE_ASM is the
 * correct build path (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void timproc_uso_b1_func_00001A64(int *a0, int a1, int a2, int a3) {
  int *s0 = a0;
  int r5;
  int r6;
  int *a1x;
  int new_var;
  a0[0xC / 4] = (int) (((char *) (&D_00000000)) + 0x40C);
  a0[0xB8 / 4] = a1;
  a0[0x50 / 4] = a1;
  a0[0x4C / 4] = a3;
  a0[0xAC / 4] = 0;
  a0[0xD8 / 4] = 0;
  a0[0x54 / 4] = a2;
  a0[0xD0 / 4] = 0xFF;
  a0[0xD4 / 4] = 0;
  a0[0xDC / 4] = 1;
  *((float *) (((char *) a0) + 0xCC)) = 1.0f;
  *((float *) (((char *) a0) + 0xC8)) = 1.0f;
  *((float *) (((char *) a0) + 0xC4)) = 1.0f;
  *((float *) (((char *) a0) - -0xC0)) = 1.0f;
  if (((*((int *) (((char *) a1) + 0x4F0))) << 15) >= 0)
  {
    return;
  }
  gl_func_00000000(s0, 0xE8, 0x13, s0[0x44 / 4] + 0x10);
  gl_func_00000000(s0, 0x123, 0xE1, 1);
  gl_func_00000000(s0, 0x47, 0x13, ((int) s0) + 0x30);
  gl_func_00000000(s0, 0x44, 0x22, s0[0x44 / 4] + 0x28);
  r5 = gl_func_00000000((*((int *) s0[0x4C / 4])) + ((*((int *) (((char *) (&D_00000000)) + 0x64))) * 0x30), 0);
  r6 = gl_func_00000000(0, s0[0x60 / 4]);
  s0[0xBC / 4] = r6;
  gl_func_00000000(r6, *((unsigned char *) (r5 + 5)), *((unsigned char *) (r5 + 6)), *((unsigned char *) (r5 + 7)));
  gl_func_00000000(s0[0xBC / 4], 0x4B, 0xD6);
  new_var = s0[0xBC / 4];
  gl_func_00000000(((int) s0) + 0x10, new_var);
  a1x = (int *) new_var;
  if (a1x[0x14 / 4] != 0)
  {
    a1x[4 / 4] = 1;
  }
  a1x[0x14 / 4] = (int) s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001A64);
#endif

/* timproc_uso_b1_func_00001BCC - verified structural decode (~158-insn
 * per-frame update state machine; 20 branches incl bnel/beql
 * branch-likely + 11 calls + deep struct chains = documented sub-80
 * ceiling -> INCLUDE_ASM build path; struct-typing reference).
 *   s0 = a0;  func_00000000(a0);                      // entry tick
 *   ctx = (int*)s0->0xB8;                              // 184
 *   if (((ctx->0x4F0 << 15) >= 0) and ctx->0x4DC == 1)
 *       s0->0x30 += 33;                                // 48: frame counter
 *   func_00000000(s0);                                 // update
 *   ctx = (int*)s0->0xB8;
 *   if ((ctx->0x4F0 & 0x10000) and ctx->0x4DC == 1) {
 *       if (s0->0x48 == 2) {                           // 72: state
 *           if (s0->0xDC != 1                          // 220: sub-state
 *               and ((int*)((int*)s0->0x44)->0x60)->0x800 -> 0x4C != 0)
 *               func_00000000(s0, 1);
 *           s0->0xDC = ((int*)((int*)s0->0x44)->0x60)->0x800 -> 0x4C;
 *       }
 *       if (((int*)s0->0x44)->0x34 == 0) func_00000000(s0->0xB8 ...);
 *       ... (continues: more state-gated func_00000000 dispatches on
 *            s0->0x44 sub-object chain + ctx flag combinations) ...
 *   }
 * Struct-typing: s0->0xB8 ctx (->0x4F0 flag word: bit-16 enable, sign
 * bit gate; ->0x4DC mode == 1), s0->0x30 frame counter (+=33),
 * s0->0x48 state (==2), s0->0xDC sub-state/cached value, s0->0x44
 * active obj whose ->0x60 -> ->0x800 -> ->0x4C is a status field and
 * ->0x34 a flag. Per-frame: tick, conditional counter advance, then
 * state-machine dispatch of func_00000000 sub-updates. Caps <80:
 * bnel/beql branch-likely throughout + 11-call spill + multi-level
 * pointer-chain reload scheduling. Full per-state dispatch is
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
#ifdef NON_MATCHING
/* timproc_uso_b1_func_00001BCC: per-frame UI step (sibling of mgrproc 3074 /
 * timproc_b3 1C68). cb(); gate arg0->0xB8 bit-16 && ->0x4DC==1 bumps 0x30. Then if
 * gated: state-2 0xDC sync from arg0->0x44->0x60->0x800->0x4C (cb on change); cb on
 * 0x44->0x34; if arg0->0x98->0xC8<=0 reset sub (0x554=192.0f, 0x544=0xFF); mod-0x33
 * counter at 0xD8 with periodic cb(0x135,0). Final block (still gated): if ->0x4DC
 * ==1 && cb(arg0): reset sub + 0x2C=0; cb(0x80, 0x44->0x30, 0); cb(0x80, v8, vC,
 * 0.0f, 0.0f) via gl_proto_1c68; state-2 blink 0x78 by (0xAC++ & 8). cb(arg0) tail.
 * Fresh decode 2026-05-29 (m2c-confirmed). 97.1% reg-blind (157/158 insns) —
 * structure near-exact; residual is 1 insn + register renames. Caps: structs +
 * cb prototypes untyped (USO-reloc). NON_MATCHING. */
extern int gl_proto_1c68(void *, int, int, float, float);
void timproc_uso_b1_func_00001BCC(char *arg0) {
    char *bc;
    char *p44;
    char *p;
    int v1;
    int t0;
    int t2;

    gl_func_00000000();
    bc = *(char **)(arg0 + 0xB8);
    if ((*(int *)(bc + 0x4F0) & 0x10000) && (*(int *)(bc + 0x4DC) == 1)) {
        *(int *)(arg0 + 0x30) = *(int *)(arg0 + 0x30) + 0x21;
    }
    gl_func_00000000(arg0);
    bc = *(char **)(arg0 + 0xB8);
    v1 = *(int *)(bc + 0x4F0) & 0x10000;
    if ((v1 != 0) && (*(int *)(bc + 0x4DC) == 1)) {
        if (*(int *)(arg0 + 0x48) == 2) {
            if ((*(int *)(arg0 + 0xDC) == 1) &&
                (*(int *)(*(char **)(*(char **)(*(char **)(arg0 + 0x44) + 0x60) + 0x800) + 0x4C) == 0)) {
                gl_func_00000000(arg0, 1);
            }
            *(int *)(arg0 + 0xDC) = *(int *)(*(char **)(*(char **)(*(char **)(arg0 + 0x44) + 0x60) + 0x800) + 0x4C);
        }
        if (*(int *)(*(char **)(arg0 + 0x44) + 0x34) != 0) {
            gl_func_00000000(*(int *)(arg0 + 0xB8));
        }
        if (*(int *)(*(char **)(arg0 + 0x98) + 0xC8) <= 0) {
            gl_func_00000000(*(int *)(arg0 + 0xB8));
            *(float *)(*(char **)(arg0 + 0xB8) + 0x554) = 192.0f;
            *(int *)(*(char **)(arg0 + 0xB8) + 0x544) = 0xFF;
        }
        t0 = *(int *)(arg0 + 0xD8) + 1;
        *(int *)(arg0 + 0xD8) = t0;
        if (t0 >= 0x33) {
            *(int *)(arg0 + 0xD8) = 0;
        }
        p = *(char **)(arg0 + 0x98);
        if ((p != 0) && (*(int *)(p + 0xC4) >= 0xC) && (*(int *)(arg0 + 0xD8) == 0)) {
            gl_func_00000000(0x135, 0);
        }
        v1 = *(int *)(*(char **)(arg0 + 0xB8) + 0x4F0) & 0x10000;
    }
    if (v1 != 0) {
        if ((*(int *)(*(char **)(arg0 + 0xB8) + 0x4DC) == 1) && (gl_func_00000000(arg0) != 0)) {
            gl_func_00000000(*(int *)(arg0 + 0xB8));
            *(float *)(*(char **)(arg0 + 0xB8) + 0x554) = 192.0f;
            *(int *)(*(char **)(arg0 + 0xB8) + 0x544) = 0xFF;
            *(int *)(arg0 + 0x2C) = 0;
        }
        gl_func_00000000(*(int *)(arg0 + 0x80), *(int *)(*(char **)(arg0 + 0x44) + 0x30), 0);
        p44 = *(char **)(arg0 + 0x44);
        gl_proto_1c68(*(int *)(arg0 + 0x80), *(int *)(p44 + 8), *(int *)(p44 + 0xC), 0.0f, 0.0f);
        bc = *(char **)(arg0 + 0xB8);
        if ((*(int *)(bc + 0x4DC) == 2) && (*(int *)(bc + 0x4F8) == 0)) {
            t2 = *(int *)(arg0 + 0xAC) + 1;
            *(int *)(arg0 + 0xAC) = t2;
            if (t2 & 8) {
                p = *(char **)(arg0 + 0x78);
                *(int *)(p + 0x18) = *(int *)(p + 0x18) & ~4;
            } else {
                p = *(char **)(arg0 + 0x78);
                *(int *)(p + 0x18) = *(int *)(p + 0x18) | 4;
            }
        }
    }
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00001BCC);
#endif

void timproc_uso_b1_func_00001E44(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000083C((int*)(dst + 0x10));
}

void timproc_uso_b1_func_00001E74(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_00000878((float*)(dst + 0x10));
}

void timproc_uso_b1_func_00001EA4(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_000008B4((Quad4*)(dst + 0x10));
}

/* timproc_uso_b1_func_00001ED4: 36-insn (0x90) constructor — BYTE-IDENTICAL
 * mirror of eddproc_uso_func_000003BC (sig=f167638a8a, 4th clone of this
 * family). Same alloc + init + list-add structure with beql speculative
 * double-store. ~60% NM cap inherited. Multi-tick decomp.
 *
 * Find via: scripts/find-byte-identical-clones.py */
/* 2026-05-31: BYTE-IDENTICAL to the 100% eddproc_uso_func_000003BC; applied its body
 * (the old structure was wrong — nested the head-insert inside the alloc-success and
 * scrambled the slot/flag order; correct is the two-phase var-reuse below). */
void *timproc_uso_b1_func_00001ED4(int *arg0) {
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

void timproc_uso_b1_func_00001F64(char *dst) {
    int tmp;
    timproc_uso_b1_func_0000083C(&tmp);
    timproc_uso_b1_func_0000090C((Vec3*)(dst + 0x10));
}
/* 3-word trailing pad sidecar (emits exactly; >=2-word blocks are safe).
 * The old P0 "LEN -0xC" triage blamed this region incorrectly: the real
 * causes were the two dropped stolen-prologue orphans at 0x19B8/0x2028
 * (restored 2026-06-10 as standalone 2-word GLOBAL_ASM blocks) plus a
 * stale YAY0_TEXT_SIZE (0x2ED4 -> 0x2EE0). Block byte-verified vs
 * assets/timproc_uso_block_1.bin. */
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00001F64_pad.s")

void timproc_uso_b1_func_00001FA0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 4;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* EXACT 2026-05-03. Mirror of timproc_uso_b3_func_000021F4. Same recipe:
 * 3 unique externs (D_b1_1FE4_a/b/c) all mapped to 0x0 + offset cast in C.
 * (Its trailing stolen-prologue orphan at 0x2028 is now the standalone
 * 2-word GLOBAL_ASM block below -- the old SUFFIX_BYTES=8 absorption was
 * removed with the instruction-forcing purge 2026-05-23.)
 * Per feedback_unique_extern_with_offset_cast_breaks_cse.md. */
extern char D_b1_1FE4_a;
extern char D_b1_1FE4_b;
extern char D_b1_1FE4_c;
void timproc_uso_b1_func_00001FE4(void) {
    gl_func_00000000(*(int*)((char*)&D_b1_1FE4_a + 0x208));
    *(int*)((char*)&D_b1_1FE4_b + 0x40) = 6;
    gl_func_00000000(*(int*)((char*)&D_b1_1FE4_c + 0x20C), -1, 0);
}

/* vram 0x2028: 2-word stolen-prologue orphan (lui $a0,%hi; lw $a0,0x148($a0)
 * ahead of func_00002030's prologue). Standalone 2-word GLOBAL_ASM emits
 * exactly; replaces the banned SUFFIX_BYTES absorption (removed 2026-05-23)
 * noted in the comment above. Both neighbors stay matched C. */
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_orphan_00002028.s")

/* Dual-branch state setter (twin of timproc_uso_b3_func_00002240).
 * MATCHED 2026-06-10 (31/31): the old "register-allocator cap" had two
 * decode errors -- the first call's arg is the PARAMETER + 4 (not a
 * global), and both arms call through the SAME +0x208 target. Load-
 * bearing shapes: volatile pointer-fetch global for the per-store
 * reload of cur (+0x20C), and the if(1){} BB-split inside each arm
 * AFTER the jal (the documented v0/v1 lever, 4-for-4) which flips the
 * address temp into $v0 / the li-1 into $v1. */
extern int D_call_b1_2030_a;
extern int * volatile D_cur_b1_2030;
void timproc_uso_b1_func_00002030(char *a0) {
    if (gl_func_00000000(a0 + 4) != 0) {
        gl_func_00000000(D_call_b1_2030_a);
        if (1) {}
        D_cur_b1_2030[0x14] = 2;
        D_cur_b1_2030[0x16] = 1;
    } else {
        gl_func_00000000(D_call_b1_2030_a);
        if (1) {}
        D_cur_b1_2030[0x14] = 1;
        D_cur_b1_2030[0x16] = 1;
    }
}

void timproc_uso_b1_func_000020AC(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 1;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_000020F0(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 2;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

extern int gl_ref_00000208;
extern int gl_ref_0000020C;

void timproc_uso_b1_func_00002134(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 3;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

void timproc_uso_b1_func_00002178(void) {
    gl_func_00000000(gl_ref_00000208);
    gl_ref_00000040 = 0xD;
    gl_func_00000000(gl_ref_0000020C, -1, 0);
}

/* 000021BC/21C4/21CC: 3 empty stubs RECOVERED 2026-05-28 from the Yay0 gap
 * (no .s, missing from build; bytes from block_1). void f(void){} -> jr ra;nop. */
void timproc_uso_b1_func_000021BC(void) {}
void timproc_uso_b1_func_000021C4(void) {}
void timproc_uso_b1_func_000021CC(void) {}

#ifdef NON_MATCHING
/* Full structural decode 2026-06-01. Constructor: 3-stage find-or-create
 * cascade (sizes 0x6C/0x50/0x2C, all collapse to obj since arg!=0), vtable
 * wiring (->0x28 = &D, ->0xC = &D+0x4C0), 7 config calls (((D[0]+3)<<16)|N
 * for N in {1,6,7,4,3,2,5}), a 6-arg setup call, an indirect vtable call,
 * a PI-domain region check (0xA0000184/0x200 vs 0xAC29), and field init.
 * All cross-USO calls are the gl_func_00000000 import. */
void *timproc_uso_b1_func_000021D4(char *obj) {
    char *d = (char *)&D_00000000;
    char *o1, *o2;
    char *rec;
    char *vt;
    char *d190;

    if (obj != 0) goto have0;
    obj = (char *)gl_func_00000000(0x6C);
    if (obj == 0) goto Ret;
have0:
    o1 = obj;
    if (obj != 0) goto have1;
    o1 = (char *)gl_func_00000000(0x50);
    if (o1 == 0) goto Svt0;
have1:
    o2 = o1;
    if (o1 != 0) goto have2;
    o2 = (char *)gl_func_00000000(0x2C);
    if (o2 == 0) goto Svt1;
have2:
    gl_func_00000000(o2, d + 0x4B8);
    *(int *)(o2 + 0x28) = (int)d;
Svt1:
    *(int *)(o1 + 0x28) = (int)d;
Svt0:
    *(int *)(obj + 0x28) = (int)d;
    *(int *)(obj + 0xC) = (int)(d + 0x4C0);

    gl_func_00000000(obj);
    *(int *)(obj + 0x60) = 0x78;
    *(int *)(obj + 0x64) = 0xA1;
    *(int *)(obj + 0x68) = 0xBF;
    *(int *)(obj + 0x48) = gl_func_00000000(0);
    gl_func_00000000(*(int *)(obj + 0x48), obj);

    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 1, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 6, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 7, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 4, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 3, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 2, -1, d);
    gl_func_00000000(*(int *)(obj + 0x48), ((*(int *)d + 3) << 16) | 5, -1, d);

    *(int *)(*(int *)(obj + 0x48) + 0x30) =
        gl_func_00000000(0, d, 0x48, 0xDD, 3, 0xD);
    gl_func_00000000(*(int *)(obj + 0x48));
    gl_func_00000000(*(int *)(obj + 0x48), 0x8C);

    vt = *(char **)(*(char **)(obj + 0x48) + 0x28);
    ((void (*)(int))(*(int *)(vt + 0x5C)))(*(unsigned short *)(vt + 0x58) + *(int *)(obj + 0x48));

    rec = (char *)gl_func_00000000(obj + 0x10, *(int *)(obj + 0x48));
    if (*(int *)(rec + 0x14) != 0) {
        *(int *)(rec + 0x4) = 1;
    }
    *(int *)(rec + 0x14) = (int)obj;
    if (*(int *)0xA0000184 != 0) {
        if (*(int *)0xA0000200 != 0xAC290000) {
            *(int *)(*(char **)(obj + 0x48) + 0xD8) = 0;
        }
    }
    d190 = *(char **)(d + 0x190);
    gl_func_00000000(d190);
    if (*(int *)(d190 + 0x14) != 0) {
        *(int *)(d190 + 0x4) = 1;
    }
    *(int *)(d190 + 0x14) = (int)obj;
    gl_func_00000000(*(int *)(d + 0x190), 1, 0);

    *(int *)(obj + 0x54) = 0;
    *(int *)(obj + 0x50) = 0;
    *(int *)(obj + 0x30) = 1;
    *(int *)(obj + 0x2C) = 0;
Ret:
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_000021D4);
#endif

/* timproc_uso_b1_func_000024F4: GBI command emitter (8x 0x260000|(D<<3)+N etc).
 * The 0x260000-series `or a1, s1, tN` wants the hoisted constant (s1) as rs;
 * IDO defaults to value-as-rs. The old "not C-reachable" claim was WRONG —
 * forced via the assignment-expression operand-order lever `value | (t = const)`
 * (pins the const as rs at the op; CSE keeps the single lui). Byte-identical
 * sibling of timproc_uso_b3_func_00002700. See
 * docs/IDO_CODEGEN.md#feedback-ido-commutative-op-operand-order. */
void timproc_uso_b1_func_000024F4(int a0) {
    int t;
    gl_func_00000000((char *)&D_00000000 + 112,
                     (*(int *)&D_00000000 << 3) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 136,
                     ((*(int *)&D_00000000 << 3) + 1) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 160,
                     ((*(int *)&D_00000000 << 3) + 2) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 184,
                     ((*(int *)&D_00000000 << 3) + 3) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 208,
                     ((*(int *)&D_00000000 << 3) + 4) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 232,
                     ((*(int *)&D_00000000 << 3) + 5) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 256,
                     ((*(int *)&D_00000000 << 3) + 6) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 280,
                     ((*(int *)&D_00000000 << 3) + 7) | (t = 0x260000));
    gl_func_00000000((char *)&D_00000000 + 16, 0x280000);
    gl_func_00000000((char *)&D_00000000 + 40, 0x280000 | 1);
    gl_func_00000000((char *)&D_00000000 + 64, 0x280000 | 2);
    gl_func_00000000((char *)&D_00000000 + 88, 0x280000 | 3);
    gl_func_00000000((char *)&D_00000000 + 304,
                     (*(int *)&D_00000000 + 52) << 16);
    gl_func_00000000((char *)&D_00000000 + 328,
                     ((*(int *)&D_00000000 + 52) << 16) | 3);
    gl_func_00000000((char *)&D_00000000 + 352,
                     ((*(int *)&D_00000000 + 52) << 16) | 4);
    gl_func_00000000((char *)&D_00000000 + 448,
                     ((*(int *)&D_00000000 + 52) << 16) | 1);
    gl_func_00000000((char *)&D_00000000 + 472,
                     ((*(int *)&D_00000000 + 52) << 16) | 2);
    gl_func_00000000((char *)&D_00000000 + 376,
                     ((*(int *)&D_00000000 + 45) << 16) | 4);
    gl_func_00000000((char *)&D_00000000 + 400,
                     ((*(int *)&D_00000000 + 45) << 16) | 5);
    gl_func_00000000((char *)&D_00000000 + 424,
                     ((*(int *)&D_00000000 + 45) << 16) | 6);
    gl_func_00000000((char *)&D_00000000 + 496, 0x2F0012);
    (void)a0;
}

/* timproc_uso_b1_func_00002740 — 95.69% → 99.35% (2026-05-18) via distinct
 * externs D_b1_2740_g208/g20C for the &D+0x208/+0x20C absolute stores so each
 * sw gets its own R_MIPS_HI16/LO16 reloc (per
 * docs/IDO_CODEGEN.md#feedback-ido-cse-bust-via-distinct-externs).
 * switch on a0->0x50: case 0 → gl_func(&D,0x40100) gate, then walk
 *   slot = base + base->0x7C * 0x28; if slot->0x90 != 0 && slot->0x88 != 0
 *   { gl(5); D[0x208]=a0->0x48; D[0x20C]=a0; recompute slot2; (*slot2->0x90)(); }
 *   else gl(165). case 1/2 → gl_func(a0).
 * Was promoted 2026-05-21 with INSN_PATCH for fixed register/operand choice
 * caps plus raw-word relocation cleanup at 0x90/0x98/0x9C/0xA0. INSN_PATCH
 * REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to NM-wrap;
 * NATURAL CEILING (fixed-register diffs stay NM). docs/POST_CC_RECIPES.md
 * is DEPRECATED.
 *
 * 2026-05-31 MIGRATION-VALUE NOTE: this fn is the canonical MIXED-cap case —
 * 7 real diffs = 2 reloc-blind (`sw $8,0x208($1)`/`sw $6,0x20C($1)`: the
 * D_b1_2740_g208/g20C scalar %lo stores expected bakes but C-emit relocs,
 * NOT C-bakeable per MATCHING_WORKFLOW#addend-only-folds-in-addiu) PLUS 5
 * register-renumber/operand-order ($2/$3, addu $2+$15 vs $15+$2). So the
 * USO-reloc migration would only DROP the 2 reloc diffs (98.9%->~99.x), NOT
 * land it — the register caps remain. 2026-06-10: the if(1){} BB lever
 * after gl(5) cuts 5 register diffs to 3; the remaining 3 are the addu
 * OPERAND-ORDER canonical (target addu v1,v0,t7 base-first; every C
 * form tested — ptr+int, int+ptr, char* arith, &arr[idx], struct-idx,
 * 0xA*idx — emits scaled-first) + its dependent lw. Same cosmetic class
 * as the documented beq operand order. True ceiling = 2 reloc-blind +
 * 3 operand-order. General finding: near-100 USO fns are
 * typically mixed reloc-blind + regalloc, so the migration helps only fns
 * whose SOLE residual is reloc-blind; it does not credit the mixed near-100
 * band. C here is already CORRECT (right symbols); nothing to fix in C. */
extern int D_b1_2740_g208;
extern int D_b1_2740_g20C;
/* 2026-06-11: scoped permuter run IN FLIGHT (base 80, log
 * /tmp/perm2740.log) -- CONCLUDED 2026-06-11 ~02:50: both twins
 * terminally plateau at permuter-score 60 (= one diff, objdiff 99.84;
 * b3 at 573k iters, b1 at 289k). The class's LAST addu order resists
 * randomized search symmetrically -- consistent with a genuinely
 * allocator-internal choice. 99.84 is the twins' C+permuter ceiling;
 * uopt-internals research is the only remaining instrument. */
void timproc_uso_b1_func_00002740(int *a0)
{
  int new_var;
  switch (a0[0x50 / 4])
  {
    case 0:
      if (gl_func_00000000(&D_00000000, 0x40100) != 0)
    {
      typedef int Row2740[10];
      Row2740 *base = (Row2740 *) a0[0x48 / 4];
      int *slot = base[((int *) base)[0x7C / 4]];
      if (slot[0x90 / 4] != 0)
      {
        if (slot[0x88 / 4] != 0)
        {
          int *base2;
          int *slot2;
          gl_func_00000000(5);
          if (1)
          {
          }
          slot = a0;
          D_b1_2740_g208 = slot[0x48 / 4];
          D_b1_2740_g20C = (int) a0;
          base2 = (int *) slot[0x48 / 4];
          ;
          ((void (*)(void)) ((int *) (base2 + (base2[0x7C / 4] * 0xA)))[(0x90 ^ 0) / (new_var = 4)])();
        }
        else
        {
          gl_func_00000000(165);
        }
      }
    }
      break;

    case 1:

    case 2:
      gl_func_00000000(a0);
      break;

  }

}


/* timproc_uso_b1_func_00002838 - verified structural decode (~150-insn
 * state-dispatch registration; switch + beql branch-likely + 28 calls +
 * &D relocs = documented sub-80 ceiling -> INCLUDE_ASM build path;
 * struct-typing reference). 24F4-family but state-gated.
 *   s0 = a0;  func_00000000(a0);                  // X0 entry
 *   s0->0x5C -= 16;                                // counter decrement
 *   switch (s0->0x50) {                            // v0 = s0->0x50
 *     case 0: return;                              // -> 0x240
 *     case 1:                                      // -> 0x48
 *        func_00000000(&D+0);
 *        func_00000000(&D+496);
 *        func_00000000(&D+496, 160, 37, 3);
 *        func_00000000(s0, 37);
 *        func_00000000(s0, *(u8*)(&D+376), 80);
 *        func_00000000(&D+448);
 *        func_00000000(&D+448, 160, 105, 3);
 *        v = s0->0x68;
 *        if (*(int*)&D != 0) { v += 10; a0 = v-39; }
 *        else                  a0 = (s0->0x68)-39;
 *        a2 = (*(int*)&D == 0) ? a0 : a0-14;
 *        func_00000000(&D+328); func_00000000(&D+328,160,...); ...
 *        ... (continues: more &D+328 region registration calls)
 *        break;
 *     case 2:  // -> 0x13C : a different registration call sequence
 *        ...
 *     default: return;                             // -> 0x244
 *   }
 * Struct-typing: s0->0x50 state selector (0=idle/return, 1, 2), s0->0x5C
 * frame counter (-=16 each call), s0->0x68 a position/index (+10 when
 * D[0]!=0; offsets -39 / -14 derived for call args), &D[0] global mode
 * flag, &D+376 a u8 param. Per-state runs distinct gl_func_00000000
 * registration sequences against &D data regions (+0/+496/+448/+328 ...)
 * with const args (160,37,105,3,80). Caps <80: switch-dispatch + beql
 * branch-likely + 28-call spill + &D %hi/%lo reloc scheduling -
 * documented state-dispatch ceiling. Full per-state call lists are
 * INCLUDE_ASM-preserved (the .s is the source of truth for the exact
 * sequence). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
/* timproc_uso_b1_func_00002838: HUD draw dispatcher (switch arg0->0x50, cases
 * 0/1/2). cb(); decrement arg0->0x5C by 0x10. Each non-0 case draws a row of
 * panels (0x1F0/0x1C0/0x160/0x148/0x178 sprites via cb(id);cb(id);cb(id,0xA0,
 * g,3) triples) and a value at arg0->0x68 adjusted by a global flag *(int*)&D
 * and the *(u8*)(&D+0x178) digit. Case 2 falls through to case 0 (return). Fresh
 * decode 2026-05-29 (m2c-confirmed; both 0x178 loads are lbu; the draw-target IDs
 * 0x1F0/1C0/160/148/178 are &D-relative ADDRESSES = lui+addiu, not literals).
 * 78.8% reg-blind (148/149 insns). Residual: target promotes arg0 to $s0 (saved
 * reg) while mine spills it to stack — allocator choice. Caps: structs + cb
 * prototypes untyped (USO-reloc), &D not symbolized. NON_MATCHING. */
extern int gl_func_00000000();
void timproc_uso_b1_func_00002838(char *arg0) {
    int v0;
    int a2;
    int t1;

    gl_func_00000000();
    *(int *)(arg0 + 0x5C) = *(int *)(arg0 + 0x5C) - 0x10;
    switch (*(int *)(arg0 + 0x50)) {
    case 1:
        gl_func_00000000(0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0, 0xA0, 0x25, 3);
        gl_func_00000000(arg0, 0x25);
        gl_func_00000000(arg0, *(unsigned char *)((char *)&D_00000000 + 0x178), 0x50);
        gl_func_00000000((char *)&D_00000000 + 0x1C0);
        gl_func_00000000((char *)&D_00000000 + 0x1C0);
        gl_func_00000000((char *)&D_00000000 + 0x1C0, 0xA0, 0x69, 3);
        t1 = *(int *)&D_00000000;
        v0 = *(int *)(arg0 + 0x68);
        if (t1 != 0) {
            v0 += 0xA;
        }
        a2 = v0 - 0x27;
        if (t1 != 0) {
            a2 -= 0xE;
        }
        gl_func_00000000((char *)&D_00000000 + 0x148);
        gl_func_00000000((char *)&D_00000000 + 0x148);
        gl_func_00000000((char *)&D_00000000 + 0x148, 0xA0, a2, 3);
        gl_func_00000000(arg0, v0 - 0x14);
        return;
    case 2:
        gl_func_00000000(0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0);
        gl_func_00000000((char *)&D_00000000 + 0x1F0, 0xA0, 0x25, 3);
        gl_func_00000000(arg0, 0x25);
        gl_func_00000000(arg0, *(unsigned char *)((char *)&D_00000000 + 0x178), 0x50);
        gl_func_00000000((char *)&D_00000000 + 0x1C0);
        gl_func_00000000((char *)&D_00000000 + 0x1C0);
        gl_func_00000000((char *)&D_00000000 + 0x1C0, 0xA0, 0x69, 3);
        gl_func_00000000((char *)&D_00000000 + 0x160);
        gl_func_00000000((char *)&D_00000000 + 0x160);
        gl_func_00000000((char *)&D_00000000 + 0x160, 0xA0, 0x8E, 3);
        v0 = *(int *)(arg0 + 0x68);
        if (*(int *)&D_00000000 != 0) {
            v0 -= 8;
        }
        gl_func_00000000((char *)&D_00000000 + 0x178);
        gl_func_00000000((char *)&D_00000000 + 0x178);
        gl_func_00000000((char *)&D_00000000 + 0x178, 0xA0, v0 - 0x13, 3);
        gl_func_00000000(arg0, v0);
        break;
    case 0:
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002838);
#endif

/* timproc_uso_b1_func_00002A8C — sequence of gl_func_00000000(&D, mask)
 * gates toggling s0->0x58, then a recurring vtable-dispatch tail:
 *   obj=(int*)s0->0x48; s0->0x50=0; vt=(int*)obj->0x28;
 *   (*(fn)vt->0x5C)( (short)vt->0x58 + (int)obj );
 * Masks: 0x10001 (clear 0x58), 0x4002 (set 0x58=1), 0x40100 (branch:
 * s0->0x58==0 -> gl(5)+gl(&D,1)+obj->0xD8=0+vtail, else gl(2050)+vtail),
 * 0x200 (gl(2050)+vtail). IDO's allocator emits the vtail through v1/a1;
 * the target uses v0/v1 (obj reuses $v0 freed by the preceding void
 * call). INSN_PATCH removed 2026-05-23. 2026-06-10: the E04 web-order
 * inversion (inline the full vt chain, let CSE merge) is NEUTRAL here
 * -- 15 diffs either way; the lever flips v0/v1 pairs in single-block
 * chains (E04) but not in this multi-arm shape where each arm's vtail
 * re-derives the web after different call sequences. v0-reuse-after-
 * void-call coloring; uoptlist class. */
/* LANDED via twin-port from timproc_uso_b3_func_00002C98 (byte-identical
 * except the 0x40100-arm mask literal is 1 instead of 2). Same `if (1) {}`
 * basic-block-boundary lever that colors o48 into the dead $v0. */
void timproc_uso_b1_func_00002A8C(char *obj) {
    char *o48;
    char *vt;

    if (gl_func_00000000((char *)&D_00000000, 0x10001) != 0 && *(int *)(obj + 0x58) != 0) {
        gl_func_00000000(1);
        *(int *)(obj + 0x58) = 0;
    }
    if (gl_func_00000000((char *)&D_00000000, 0x4002) != 0 && *(int *)(obj + 0x58) == 0) {
        gl_func_00000000(1);
        *(int *)(obj + 0x58) = 1;
    }
    if (gl_func_00000000((char *)&D_00000000, 0x40100) != 0) {
        if (*(int *)(obj + 0x58) == 0) {
            gl_func_00000000(5);
            gl_func_00000000((char *)&D_00000000, 1);
            *(int *)(*(char **)(obj + 0x48) + 0xD8) = 0;
            if (1) {}
            o48 = *(char **)(obj + 0x48);
            *(int *)(obj + 0x50) = 0;
            vt = *(char **)(o48 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
        } else {
            gl_func_00000000(0x802);
            if (1) {}
            o48 = *(char **)(obj + 0x48);
            *(int *)(obj + 0x50) = 0;
            vt = *(char **)(o48 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
        }
    }
    if (gl_func_00000000((char *)&D_00000000, 0x200) != 0) {
        gl_func_00000000(0x802);
        if (1) {}
        o48 = *(char **)(obj + 0x48);
        *(int *)(obj + 0x50) = 0;
        vt = *(char **)(o48 + 0x28);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)o48);
    }
}

#ifdef NON_MATCHING
/* timproc_uso_b1_func_00002BE4: 0xFC (63 insns) — sibling of the just-matched
 * 00002CE0; preceding it in the .text segment.
 *
 * Saves 8 s-regs (s0..s7) — heavy long-lived-locals function. Frame 0x68.
 *
 * Structure (decoded 2026-05-05 first pass):
 *
 *   1. Copy 5 ints from D[0x4D0..0x4E0] to local Vec4-like buf at sp+0x54
 *      (5-int copy via t6 base ptr, interleaved lw/sw).
 *   2. jal gl_func_00000000(&D_00000000)   ; cleanup/notify call
 *   3. Outer loop:  for (s3 = 0x10; s3 != 0xF0; s3 += 0x20) { ... }    7 iters
 *   4. Inner loop: for (s0 = 0;     s0 != 0x140; s0 += 0x40) { ... }   5 iters
 *      Inner body:
 *        s1 = vec4;                       ; reset on outer iter
 *        ...
 *        s2 = (char*)&D + 0x10 + s0*24    ; mult s0, 24; addu s2, s4, t1
 *        gl_func_00000000(s2);            ; first per-iter call
 *        gl_func_00000000(s2, s0, s3, 0); ; second per-iter call (4-arg)
 *        s1 += 4;                         ; advance vec4 ptr (int*)
 *      Inner-end: s0 += 0x40
 *      Outer-end: s3 += 0x20, s1 = &sp+0x54 reset (delay slot)
 *   5. Restore s0..s7, ra; addiu sp, sp, 0x68; jr ra.
 *
 * Total inner iters: 7 outer * 5 inner = 35 dispatches. Likely a per-tile
 * (or per-sub-region) init loop indexing into a 0x600-byte-stride array
 * at &D_00000000 + 0x10.
 *
 * First-pass NM — captures outer/inner structure and per-iter call shape.
 * Register allocation across the 8 s-regs is sensitive to declaration
 * order; this body is not yet tuned for fuzzy. Fuzzy expected ~10-25%. */
/* (2) 2026-05-07: corrected inner-loop indexing — vec4[i]*24, not s0*24.
 * Vec4 entries are indices into the &D+0x10 stride-24 array; s0 is the
 * dispatch arg (0,0x40,0x80,0xC0,0x100), s3 is the outer arg (0x10..0xD0
 * step 0x20). Outer terminates with bnel (do-while-while-likely shape via
 * outer-end being s1 reset in delay slot).
 *
 * Promoted constants 0xF0/0x140/0x18 to register locals so they map to
 * $s5/$s6/$s7. Logic now correct; structure still differs in 2 places:
 *
 *   (a) IDO frame -0x78 (10 saved-regs incl $s8/$fp) vs expected -0x68
 *       (8 saved-regs s0..s7). The 9th saved-reg holds &vec4 cached as
 *       `addiu s7, sp, 0x64` then `move s1, s7` for outer-loop reset.
 *       Expected instead does `addiu s1, sp, 0x54` directly (no cache).
 *       Tried: volatile vec4, separate v0..v4 + pointer array, neither
 *       breaks IDO's CSE on the &vec4 base.
 *   (b) Vec4 init: built does all-loads-then-all-stores via t6..t0;
 *       expected interleaves `lw t9; lw t8; sw t9; sw t8; lw t9; sw t8;
 *       ...` (two-temp-reg ping-pong). IDO scheduler hoists loads.
 *
 * Net: 59 of 63 insns differ at NM build (6.3%). Logic-correct; remaining
 * diffs are IDO scheduler/CSE caps. Future passes: try forcing two-reg
 * ping-pong via barrier'd struct copy, or examine whether vec4-as-stack-
 * tail (offset 0x0) eliminates the cache. */
extern int gl_func_00000000();
void timproc_uso_b1_func_00002BE4(int *a0) {
    int vec4[5];
    register char *s4 = (char*)&D_00000000 + 0x10;
    register int s7 = 0xF0;
    register int s6 = 0x140;
    register int s5 = 0x18;
    register int *s1;
    register char *s2;
    register int s0, s3;
    (void)a0;

    vec4[0] = ((int*)((char*)&D_00000000 + 0x4D0))[0];
    vec4[1] = ((int*)((char*)&D_00000000 + 0x4D0))[1];
    vec4[2] = ((int*)((char*)&D_00000000 + 0x4D0))[2];
    vec4[3] = ((int*)((char*)&D_00000000 + 0x4D0))[3];
    vec4[4] = ((int*)((char*)&D_00000000 + 0x4D0))[4];
    gl_func_00000000(&D_00000000);

    s3 = 0x10;
    do {
        s1 = vec4;
        s0 = 0;
        do {
            s2 = s4 + (*s1) * s5;
            gl_func_00000000(s2);
            gl_func_00000000(s2, s0, s3, 0);
            s0 += 0x40;
            s1 += 1;
        } while (s0 != s6);
        s3 += 0x20;
    } while (s3 != s7);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1", timproc_uso_b1_func_00002BE4);
#endif

/* timproc_uso_b1_func_00002CE0: 26-insn (0x68) 3-call wrapper indexed by a1.
 * Promoted 95.12% → 100% via two levers:
 *   1. Unique extern at table offset (D_b1_2CE0_table = 0x70) bakes the
 *      0x70 into the addiu reloc, eliminating the redundant addiu.
 *   2. Second pointer local (`spillee = entry`) shifts IDO's spill slot
 *      from sp+0x18 to sp+0x1C to match target's frame layout. */
extern int gl_func_00000000();
extern char D_b1_2CE0_table;
void timproc_uso_b1_func_00002CE0(int a0, int a1, int a2) {
    char *entry, *spillee;
    (void)a0;
    (void)spillee;
    gl_func_00000000(&D_00000000);
    entry = (char*)&D_b1_2CE0_table + a1 * 24;
    spillee = entry;
    gl_func_00000000(entry);
    gl_func_00000000(entry, 0xA0, a2, 3);
}

/* timproc_uso_b1_func_00002D48: 0x108 (66 insns). Two-batch UI/render
 * dispatcher: each batch sets a Quad4-of-1.0 (only the first batch
 * stores it), calls a base init, then a mirror-swapped conditional
 * call selected by a0->0x58, then a secondary call. Frame 0x48; quad4
 * lands at sp+0x38 because it's declared FIRST (highest sp slot).
 * Adding `char pad[32]` AFTER quad4 holds the frame at -0x48. */
void timproc_uso_b1_func_00002D48(int *a0, int a1) {
    float quad4[4];
    char pad[32];
    (void)pad;

    quad4[0] = 1.0f;
    quad4[1] = 1.0f;
    quad4[2] = 1.0f;
    quad4[3] = 1.0f;
    gl_func_00000000((char*)&D_00000000 + 0x190);
    if (a0[0x58 / 4] == 0) {
        gl_func_00000000((char*)&D_00000000 + 0x190, a0[0x5C / 4], quad4, 0xFF);
    } else {
        gl_func_00000000((char*)&D_00000000 + 0x190, 0x40, quad4, 0xFF);
    }
    gl_func_00000000((char*)&D_00000000 + 0x190, 0x78, a1, 3);

    gl_func_00000000((char*)&D_00000000 + 0x1A8);
    if (a0[0x58 / 4] != 0) {
        gl_func_00000000((char*)&D_00000000 + 0x1A8, a0[0x5C / 4], quad4, 0xFF);
    } else {
        gl_func_00000000((char*)&D_00000000 + 0x1A8, 0x40, quad4, 0xFF);
    }
    gl_func_00000000((char*)&D_00000000 + 0x1A8, 0xC8, a1, 3);
}

/* 34-insn 3-jal UI/render dispatcher, sibling of 00002D48. Two Quad4 args:
 * quad_a = {1,1,1,1} (sp+0x48), quad_b = {1,0,1,1} (sp+0x38). The 0.0 at
 * quad_b[1] lands in the first-jal delay slot. char pad[32] grows the
 * frame from 0x38 to 0x58 to match target's stack layout. */
void timproc_uso_b1_func_00002E50(int *a0, int a1) {
    float quad_a[4];
    float quad_b[4];
    char pad[32];
    (void)pad;
    (void)a0;

    quad_a[0] = 1.0f;
    quad_a[1] = 1.0f;
    quad_a[2] = 1.0f;
    quad_a[3] = 1.0f;
    quad_b[0] = 1.0f;
    quad_b[1] = 0.0f;
    quad_b[2] = 1.0f;
    quad_b[3] = 1.0f;
    gl_func_00000000(&D_00000000, 0xFF, quad_a, quad_b);
    gl_func_00000000((char*)&D_00000000 + 0x130);
    gl_func_00000000((char*)&D_00000000 + 0x130, 0xA0, a1, 3);
}
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b1/timproc_uso_b1/timproc_uso_b1_func_00002E50_pad.s")

/* SUFFIX_BYTES-absorbed orphans (per
 * docs/MATCHING_WORKFLOW.md#feedback-splat-orphan-duplicate-symbol-pruning):
 * timproc_uso_b1_func_000021BC + 000021C4 (concatenated 6 words) ←
 * timproc_uso_b1_func_00002178 SUFFIX_BYTES
 *   (0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000).
 * Pre-prune symbols were at .o offsets 0x2EE0/0x2EE8 (tail, past natural
 * function layout end at 0x21D4); no-truncate variant of the orphan-prune. */

/* Orphan status (2026-06-10): _00002028 and _000019B8 are standalone
 * 2-word GLOBAL_ASM blocks at their vram positions (the old SUFFIX_BYTES /
 * C-emit absorptions silently vanished with the 2026-05-23 purge, leaving
 * the block -16). _000011D0 ← _00001130 (decl 0xA0, .o 0xA8) still
 * C-emit-absorbed and verified present. */
