#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern int D_8C3C_arg;
extern char D_8C3C_child_desc;
extern char D_8C3C_mid_desc;
extern char D_8C3C_root_desc;

/* Mid section of game_libs.c, split off on 2026-05-07 along with
 * game_libs_o0_8944.c (the 3-fn -O0 cluster at 0x8944..0x8A40).
 * Covers gl_func_00008AE4..gl_func_000093DC (offset 0x8AE4..0x949C).
 * Built at -O2 (default). */

#ifdef NON_MATCHING
/* gl_func_00008C3C: 92-insn alloc-or-passthrough cascade. The first three
 * calls configure globals, then the root/mid/child chain allocates 0xD4,
 * 0x50, and 0x2C byte nodes through dead-arm passthrough guards.
 *
 * 2026-05-18 deep attempt: default -O2 emits a structurally short stack-temp
 * form; scratch -O0 matches the target's 0x38 frame, s0/s1/s2 cascade, branches.
 *
 * 2026-05-28 PRECISE DIAGNOSIS (supersedes the old "needs -O0 split" note — this
 * file is ALREADY -O0): the wrap is 99.793%, and the SOLE residual is ONE
 * stack-temp slot. `call_root`'s home is sp+0x28 (mine) vs sp+0x34 (target) —
 * everything else (ra@0x24, s0/s1/s2 saves@0x18/0x1C/0x20, a0@0x38, a1@0x3C arg
 * homes, all 3 data-ref relocs, every branch) is byte/reloc-exact. The temp
 * region is 0x28..0x34; IDO -O0 puts call_root's home at the BOTTOM (0x28),
 * target at the TOP (0x34). TESTED-NEGATIVE 2026-05-28: removing the call_root
 * indirection regresses to 96.4% (it's load-bearing); declaring call_root at
 * function scope vs inner-block is score-neutral (still 0x28). The slot is an
 * -O0 temp-allocator artifact, NOT C-steerable — same class as the
 * gl_func_0005D054 spill-slot swap. Honest cap at 99.79%; stays INCLUDE_ASM.
 * 2026-06-10: the decl-order slot lever that cracked 5D054 does NOT
 * transfer here -- adding pad locals grows the -O0 frame (every named
 * local gets a slot AND frame space; 5D054 was -O2 where pads only
 * permute existing SPILL slots). The 0x28..0x34 region neighbors are
 * COMPILER-INTERNAL temps (unnamed), so there is no decl list to
 * permute; call_root's pseudo number vs the internal temps' is fixed by
 * statement order already tested. Cap stands for -O0 units.
 * 2026-06-10 branch-nesting probe: the target's bnez/beqz pattern reads
 * as nested fail-checks (if(!p){p=alloc; if(!p) goto ...}) but the
 * nested-goto form REGRESSES to 91.5 at -O0 (gotos emit extra b/label
 * traffic).
 * 2026-06-20 BRANCH-EXACT via SHORT-CIRCUIT ||: the target's `bne +7`
 * (skip alloc AND the post-alloc null-check) is reproduced by
 * `if (p != 0 || (p = alloc()) != 0) { body }`. The `||` makes IDO -O0
 * emit `bne p,zero,body; alloc; beq p,zero,end:` -- a SINGLE beq (not the
 * bnez+b that an explicit `if(p==0)goto` produces), so the bne offset
 * spans both the alloc and the beq exactly like the target. This drops
 * the 3 branch-offset diffs (28/37/46) the flat double-check form had;
 * residual is now ONLY the call_root temp-slot (0x28 mine vs 0x34 target)
 * + the 2 D_D138/D148 reloc-addiu (FALSE, resolve to target bytes).
 * The slot stays 0x28 across every C steer tried (2026-06-20: int cast,
 * function-scope decl, explicit a0[0] temp [grows frame], block scope) --
 * confirmed IDO -O0 temp-pool artifact, same class as gl_func_0005D054.
 * Honest cap; stays INCLUDE_ASM. */
extern char D_0000D138, D_0000D148, D_8C3C_v0;
gl_func_00008C3C(a0, a1) int * a0; int a1; {
    register int *root;
    register int *mid;
    register int *child;

    gl_func_00000000(&D_00000000, &D_0000D138);
    gl_func_00000000(&D_00000000, *(int*)&D_8C3C_v0);
    gl_func_00000000(&D_00000000, 7, 0, 0);

    root = 0;
    if (root != 0 || (root = (int*)gl_func_00000000(0xD4)) != 0) {
        mid = root;
        if (mid != 0 || (mid = (int*)gl_func_00000000(0x50)) != 0) {
            child = mid;
            if (child != 0 || (child = (int*)gl_func_00000000(0x2C)) != 0) {
                gl_func_00000000(child, &D_0000D148);
                child[0x28 / 4] = (int)&D_8C3C_child_desc;
            }
            mid[0x28 / 4] = (int)&D_8C3C_mid_desc;
        }
        root[0x28 / 4] = (int)&D_8C3C_root_desc;
    }
    {
        int *call_root = root;
        gl_func_00000000(call_root, a0[0]);
        gl_func_00000000(call_root);
        root = call_root;
    }
    gl_func_00000000(a0, 0, root);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);
#endif

/* gl_func_00008DAC: 39-insn 4-call init sequencer. -O0 island (file built
 * OPT_FLAGS := -O0: all 4 args spilled at entry, unfilled jal delays, b-to-epilogue).
 * The 2nd arg is the data symbol at offset 0xD150 referenced DIRECTLY as
 * &D_0000D150 (defined = 0x0000D150 in undefined_syms) so -O0 emits the 2-insn
 * %hi/%lo (lui 0x1; addiu -0x2EB0) the target uses -- NOT &D_00000000+0xD150 (3
 * insns at -O0). rv kept in s0 via `register`. */
extern int gl_func_00000000();
extern char D_0000D150;
void gl_func_00008DAC(int a0, int a1, int a2, int a3) {
    register int rv;
    gl_func_00000000(&D_00000000, &D_0000D150);
    gl_func_00000000(&D_00000000, 8, 0, 0);
    rv = gl_func_00000000(0, a1, a2, a3);
    gl_func_00000000(a0, 1, rv);
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int D_0000004C, D_00000064;
extern unsigned char D_00000181, D_00000182, D_00000183;
/* gl_func_00008E48: -O0 alloc-cascade (sibling of 8C3C/8FFC/9100). 69.2->92.98%
 * (2026-06-23): distinct-externs D_0000004C/64/181/2/3 (valued at offset -> per-read
 * folded lui), &D+8 materialized arg, `0` call-args -> &D_00000000, base/sp3C/tmp
 * register (s0/s1/s2), sp3C[0x14]=base, chained sp38=sp34 (no temp_t6 round-trip).
 * Residual ~7% = -O0 temp-slot/reg-alloc (sp3C register `move s1,v0` vs target spill
 * `sw v0,60(sp)`+reload; sp3C-plain regresses to 89.98). Same cap class as 9100/8C3C. */
char *gl_func_00008E48(char **arg0, int arg1, s32 arg2) {
    register char *base;   /* s0 */
    register char *sp3C;   /* s1 */
    register char *tmp;    /* s2 */
    char *sp38;
    char *sp34;

    sp38 = sp34 = (char *)D_0000004C;
    gl_func_00008C3C(&D_00000000, *(int *)((char *)&D_00000000 + 8));
    if (FW(FW((*(int*)arg0), 0x8), 0x8) != 0) {
        D_00000181 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
        sp34 = (char *)(int)D_00000181;
        D_00000182 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
        D_00000183 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
    }
    gl_func_00008C3C(sp38, sp34);
    if (FW(FW((*(int*)arg0), 0x8), 0x8) != 0) {
        sp3C = gl_func_00008C3C(&D_00000000, D_00000064, 3, arg2);
    } else {
        sp3C = gl_func_00008C3C(&D_00000000, D_00000064, 2, arg2);
    }
    base = (char *)&D_00000000;
    tmp = base + 0x10;
    gl_func_00008C3C(tmp, sp3C);
    if (FW(sp3C, 0x14) != 0) {
        FW(sp3C, 0x4) = 1;
    }
    FW(sp3C, 0x14) = (int)base;
    gl_func_00008C3C(&D_00000000, 0);
    (void)arg1;
    return sp3C;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);
#endif

/* gl_func_00008FFC: -O0 init sequence (fresh decode 2026-05-28, mnemonic disasm).
 * Five callee calls bracketing a global-state mask + a constructor: configures
 * two globals, masks D[0x50] to bit 0x20, builds an object via call3 (returns
 * obj, a3=incoming a2), registers it (call4), links obj into D's list (obj->0x14),
 * sets obj->0x4=1 if obj->0x14 was non-null, then a final call5; returns obj.
 * Data refs use the &D_00000000+offset addend idiom; builds -O0 (game_libs_mid).
 * 82.38% -> 91.08% (2026-05-31). Lever: the target holds base (&D), obj, and a
 * scratch in s0/s1/s2 across the calls — at -O0 that means `register` locals
 * (declared base/obj/tmp in s0/s1/s2 order). The base-CSE residual (target
 * re-materializes &D per global VALUE read; mine shared the s0 base) was busted
 * by routing the +8/+0x4C/+0x17D/+0x50/+0x64 reads through DISTINCT externs
 * (D_00000008.. valued at the offset in undefined_syms_auto.txt) — each read now
 * gets its own lui base, matching the target (+8.7pp). Same distinct-extern
 * lever as the USO &D-CSE busts; works at -O0 too. The bare `&D_00000000` call
 * args + the `base`/`tmp` register pointer correctly stay on the shared s0 base.
 * RESIDUAL (~9%, genuine -O0 caps): obj home-spill — target stores the call3
 * result to obj's home (sw v0,0x34), reloads into s1, RETURNS from the home
 * (lw v0,0x34); `register int *obj` keeps it in s1 (no home), and a plain
 * `int *obj` regresses to 85.5% (loses the s1 deref allocation). Plus -O0 temp
 * reg-renumber. Real wrap, correct logic; stays NM. */
extern int D_00000008, D_0000004C, D_00000050, D_00000064;
extern unsigned char D_0000017D;
#ifdef NON_MATCHING
int gl_func_00008FFC(int a0, int a1, int a2) {
    register char *base;     /* s0 */
    register int *obj;       /* s1 */
    register char *tmp;      /* s2 */

    gl_func_00000000(&D_00000000, D_00000008);
    gl_func_00000000(D_0000004C, D_0000017D);
    D_00000050 = D_00000050 & 0x20;
    obj = (int*)gl_func_00000000(&D_00000000, D_00000064, 5, a2);
    base = (char*)&D_00000000;
    tmp = base + 0x10;
    gl_func_00000000(tmp, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    tmp = base;
    obj[0x14 / 4] = (int)tmp;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
    (void)a1;
    return (int)obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);
#endif

/* gl_func_00009100: -O0 init sequence (fresh decode 2026-05-28). Near-twin of
 * gl_func_00008FFC: 3 byte-field copies (D[0x179..0x17B] → D[0x181..0x183]), a
 * call with a duplicated arg (D[0x4C]), a constructor call (a2=4, a3=incoming
 * a2), then the identical obj-register/link tail (call(obj base), set obj->0x4=1
 * if obj->0x14!=0, link obj->0x14=&D, final call(&D,0)); returns obj.
 * base/obj/scratch held in s0/s1/s2 via `register` locals (the -O0 lever from
 * the 8FFC sibling). &D_00000000+offset addend idiom; builds -O0.
 * 79.85 -> 93.54 (2026-05-31): routed every &D byte/word access through DISTINCT
 * externs (D_00000179/17A/17B/181/182/183 unsigned char + D_0000004C/D_00000064
 * int, valued at the offset in undefined_syms_auto.txt) so each re-materializes
 * its own lui base — the build was CSE'ing the 3 byte-copies onto one shared base
 * where the target re-materializes per access. The old comment called this the
 * "-O0 base-CSE nuance hard to steer"; the distinct-extern lever busts it at -O0
 * too (same fix as the 8FFC sibling, +13.69pp). RESIDUAL (~6%): only the obj
 * spill-timing/return-from-home -O0 cap remains (target sw v0,0x34 + reload s1 +
 * return-from-home; register int *obj keeps it in s1) — identical to 8FFC. */
extern unsigned char D_00000179, D_0000017A, D_0000017B, D_00000181, D_00000182, D_00000183;
extern int D_0000004C, D_00000064;
/* gl_func_00009100 [-O0 temp-slot CAP, 93.5%]: same class as gl_func_00008C3C /
 * gl_func_00008FFC. obj is correctly `register` (s1) — objdiff reloc-resolves the
 * distinct-extern D_xxx loads so the lbu-0-vs-377 immediates already score matching;
 * the residual is the obj home-spill (target sw v0,52(sp) / reload, returns from the
 * home slot). TESTED-NEGATIVE 2026-06-23: making obj a plain (spilled) local -> 85.4%
 * (worse); rewriting the D-relative reads as &D_00000000+offset -> 74% (adds a
 * materializing addiu, worse). Original register form stays. */
#ifdef NON_MATCHING
int gl_func_00009100(int a0, int a1, int a2) {
    register char *base;     /* s0 */
    register int *obj;       /* s1 */
    register char *tmp;      /* s2 */

    D_00000181 = D_00000179;
    D_00000182 = D_0000017A;
    D_00000183 = D_0000017B;
    gl_func_00000000(D_0000004C, D_0000004C);
    obj = (int*)gl_func_00000000(&D_00000000, D_00000064, 4, a2);
    base = (char*)&D_00000000;
    tmp = base + 0x10;
    gl_func_00000000(tmp, obj);
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    tmp = base;
    obj[0x14 / 4] = (int)tmp;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
    (void)a1;
    return (int)obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);
#endif

#ifdef NON_MATCHING
/* gl_func_00009204: module-init/registration. cb(A, *(B+8)); cb(*(C+0x4C),
 * *(D+0x58)); node = cb(E, *(F+0x64), 6, a2); cb(G+0x10, node); if (node->0x14)
 * node->4=1; node->0x14 = G; cb(H, 0); return node. The &D globals are distinct
 * (no CSE). Fresh decode 2026-05-29: 74%, structure + the 8 distinct &D refs
 * match. RESIDUAL: target promotes node/G/(G+0x10) to callee-saved $s1/$s0/$s2
 * (frame -56); my C keeps fewer in s-regs (spills node, frame -32) — an
 * s-reg-promotion/allocation difference. */
extern int gl_func_00000000();
extern int D_9204_a, D_9204_b, D_9204_c, D_9204_d, D_9204_e, D_9204_f, D_9204_g, D_9204_h;
int gl_func_00009204(int a0, int a1, int a2) {
    int *node;
    char *g;
    gl_func_00000000(&D_9204_a, *(int *)((char *)&D_9204_b + 8));
    gl_func_00000000(*(int *)((char *)&D_9204_c + 0x4C), *(int *)((char *)&D_9204_d + 0x58));
    node = (int *)gl_func_00000000(&D_9204_e, *(int *)((char *)&D_9204_f + 0x64), 6, a2);
    g = (char *)&D_9204_g;
    gl_func_00000000(g + 0x10, node);
    if (node[0x14 / 4] != 0) {
        node[0x4 / 4] = 1;
    }
    node[0x14 / 4] = (int)g;
    gl_func_00000000(&D_9204_h, 0);
    return (int)node;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);
#endif

#ifdef NON_MATCHING
/* gl_func_000092F4: module-init/registration, sibling of gl_func_00009204.
 * cb(a, *(b+8)); cb(*(c+0x4C), *(c+0x4C)); node = cb(d, 8, 2, a1); cb(g+0x10,
 * node); if (node->0x14) node->4=1; node->0x14 = g; cb(f, 0); return node.
 * Distinct &D globals (no CSE). Fresh decode 2026-05-29: 73%, structure + the
 * distinct &D refs match. RESIDUAL (same as gl_func_00009204): target promotes
 * node/g to callee-saved $s1/$s0 (frame -56); my C keeps them in t-regs/spills
 * (frame -40) — s-reg-promotion cap. */
extern int gl_func_00000000();
extern int D_92f_a, D_92f_b, D_92f_c, D_92f_d, D_92f_e, D_92f_f;
int gl_func_000092F4(int a0, int a1) {
    int *node;
    char *g;
    int t;
    gl_func_00000000(&D_92f_a, *(int *)((char *)&D_92f_b + 8));
    t = *(int *)((char *)&D_92f_c + 0x4C);
    gl_func_00000000(t, t);
    node = (int *)gl_func_00000000(&D_92f_d, 8, 2, a1);
    g = (char *)&D_92f_e;
    gl_func_00000000(g + 0x10, node);
    if (node[0x14 / 4] != 0) {
        node[0x4 / 4] = 1;
    }
    node[0x14 / 4] = (int)g;
    gl_func_00000000(&D_92f_f, 0);
    return (int)node;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);
#endif

/* gl_func_000093DC: -O0 init/dispatch (scalar-only, no struct locals = no
 * frame-offset ceiling). Real direct-global symbols D_w0 (offset 0) / D_w134
 * (0x134) give the 2-insn at-macro/fold loads; &D+0x10 base = 3-insn; register
 * vars give the s0/s1/s2 usage. fuzzy=100. */
extern int D_w0, D_w134;
/* 2026-05-29: 1-diff cap (lw a0,0 vs lw a0,0x134 on the D_w134 load). D_w134
 * is a direct global at &D+0x134; expected is `lui a0; lw a0,0x134(a0)` (fresh,
 * independent). The placeholder D_w134 (link-resolved) bakes %lo=0 in the .o.
 * The &D+0x134 ADDEND form (which works for isolated loads, e.g. gl_func_00006DC8)
 * REGRESSES here: this function also materializes &D into `base`(s1) for other
 * uses, so IDO CSE-forces a full `lui;addiu;lw 0x134` (extra addiu) instead of the
 * fresh `lui;lw 0x134`. Array-index form same. Tooling-blocked (.o-unverifiable);
 * link-correct. See docs/MATCHING_WORKFLOW.md addend-vs-symbol caveat. */
void gl_func_000093DC(int a0, int a1, int *a2) {
    register int *obj;    /* s0 = a2 */
    register char *base;  /* s1 = &D */
    register char *p;     /* s2 */
    D_w0 = gl_func_00000000(a2, a1);
    obj = a2;
    base = (char *)&D_00000000;
    p = base + 0x10;
    gl_func_00000000(p, obj);
    if (*(int *)((char *)obj + 0x14) != 0) {
        *(int *)((char *)obj + 0x4) = 1;
    }
    p = base;
    *(int *)((char *)obj + 0x14) = (int)p;
    obj = a2;
    gl_func_00000000(D_w0, obj);
    gl_func_00000000(D_w134);
    (void)a0;
}
