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

/* gl_func_00008C3C — VERIFIED 92/92 reloc-resolved EXACT (2026-07-03, agent-e W5).
 * Baseline was 88/92 raw = 84 byte-identical + 4 reloc-false (D_0000D138/D_0000D148
 * HI16/LO16: syms valued 0xD138/0xD148 in undefined_syms_auto.txt resolve to the
 * target's lui 0x1 / addiu -0x2EC8 words at link).
 *
 * CAP CRACKED: the long-documented "-O0 temp-pool artifact, NOT C-steerable"
 * call_root home-slot residual (mine sp+0x28 vs target sp+0x34) is pure DECL ORDER.
 * IDO -O0 assigns local frame slots top-down in declaration order, and `register`
 * locals RESERVE slots in that same order (unused). Old form declared call_root
 * inside an inner block AFTER register root/mid/child -> 4th slot = 0x28. Declaring
 * `int *call_root;` FIRST (before the register decls) gives it the top slot 0x34;
 * root/mid/child reserve 0x30/0x2C/0x28. (The old "function scope vs inner-block
 * score-neutral" test kept it after the register decls -- that's why it never moved.)
 *
 * VOID fn -> NOT blocked by the -O0 return-value dead-double-b toolchain gap.
 * PROMOTABLE: replace the #ifdef NON_MATCHING wrap with this body (drop INCLUDE_ASM).
 * No new undefined_syms needed (D_0000D138/D_0000D148/D_8C3C_* already present). */
extern int gl_func_00000000();
extern char D_00000000;
extern char D_8C3C_child_desc, D_8C3C_mid_desc, D_8C3C_root_desc;
extern char D_0000D138, D_0000D148, D_8C3C_v0;
gl_func_00008C3C(a0, a1) int * a0; int a1; {
    int *call_root;       /* declared FIRST -> top local slot 0x34 (-O0 slots are decl-order top-down; register vars reserve the slots below) */
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
    call_root = root;
    gl_func_00000000(call_root, a0[0]);
    gl_func_00000000(call_root);
    root = call_root;
    gl_func_00000000(a0, 0, root);
}

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
/* gl_func_00008E48 — VERIFIED 101/111 reloc-resolved (was 10/109 raw baseline).
 * ALL 109 target words reproduced in order except the live `b epilogue` offset
 * (10000003 vs 10000001) + a DEAD `b epilogue; nop` pair (build 111 vs target 109):
 * the documented -O0 RETURN-VALUE dead-double-b TOOLCHAIN-BINARY GAP
 * (docs/IDO_CODEGEN.md). Proven not C-fixable. HONEST CAP -> stays NM at ~98%
 * (up from 92.98%).
 *
 * Levers applied (all verified in-tree):
 * 1. sp3C/sp38/sp34 are PLAIN locals declared FIRST in that order -> slots
 *    0x3C/0x38/0x34 top-down; register base/o/tmp reserve 0x30/0x2C/0x28.
 *    (Old wrap had sp3C as register s1 -> `move s1,v0` instead of the target's
 *    sw v0,0x3C / lw s1,0x3C / return-from-home, and sp38/sp34 landed 0x30/0x2C.)
 * 2. Chain direction swapped: `sp34 = sp38 = (char *)D_0000004C;` -> target's
 *    store order sw t6,0x38 THEN sw t6,0x34 (old `sp38 = sp34 = ...` reversed it).
 * 3. First call arg1 via `*(int *)((char *)&D_8FFC_base + 8)` (base-0 alias,
 *    shared with 8FFC, in undefined_syms_auto.txt) -> 3-insn lui/addiu/lw-off-8
 *    with NO CSE against the &D_00000000 arg0 materialization.
 * 4. Separate `register char *o` (s1) alias of sp3C for the tail derefs;
 *    `tmp = base; FW(o,0x14) = (int)tmp;` two-step keeps the target's
 *    `move s2,s0; sw s2,20(s1)` (direct base store folds to sw s0 — wrong).
 * undefined_syms_auto.txt ADDITION (shared with 8FFC, line 578):
 *   D_8FFC_base = 0x00000000;
 */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int gl_func_00008C3C();  /* placeholder callee name as in current wrap */
extern char D_00000000;
extern int D_0000004C, D_00000064;
extern unsigned char D_00000181, D_00000182, D_00000183;
extern char D_8FFC_base;   /* base-0 alias of D_00000000 (see gl_func_00008FFC note) */
char *gl_func_00008E48(char **arg0, int arg1, s32 arg2) {
    char *sp3C;            /* plain locals decl'd first: slots 0x3C/0x38/0x34 top-down */
    char *sp38;
    char *sp34;
    register char *base;   /* s0 */
    register char *o;      /* s1 */
    register char *tmp;    /* s2 */

    sp34 = sp38 = (char *)D_0000004C;
    gl_func_00008C3C(&D_00000000, *(int *)((char *)&D_8FFC_base + 8));
    if (FW(FW((*(int*)arg0), 0x8), 0x8) != 0) {
        D_00000181 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
        sp34 = (char *)(int)D_00000181;
        D_00000182 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
        D_00000183 = gl_func_00008C3C(FW((*(int*)arg0), 0x8));
    }
    gl_func_00008C3C(sp38, sp34);
    if (FW(FW((*(int*)arg0), 0x8), 0x8) != 0) {
        sp3C = (char *)gl_func_00008C3C(&D_00000000, D_00000064, 3, arg2);
    } else {
        sp3C = (char *)gl_func_00008C3C(&D_00000000, D_00000064, 2, arg2);
    }
    base = (char *)&D_00000000;
    o = sp3C;
    tmp = base + 0x10;
    gl_func_00008C3C(tmp, o);
    if (FW(o, 0x14) != 0) {
        FW(o, 0x4) = 1;
    }
    tmp = base;
    FW(o, 0x14) = (int)tmp;
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
/* gl_func_00008FFC — VERIFIED 57/67 reloc-resolved (was 19/65 raw baseline).
 * ALL 65 target words are reproduced in order except:
 *   [56] live `b epilogue` offset 10000003 vs target 10000001, and
 *   [58-59] a DEAD `b epilogue; nop` pair (2 extra words, build 67 vs target 65).
 * Both artifacts are ONE root cause: the documented -O0 RETURN-VALUE dead-double-b
 * TOOLCHAIN-BINARY GAP (docs/IDO_CODEGEN.md "-O0 RETURN-VALUE functions get a DEAD
 * second b epilogue; nop"): our ido-static-recomp cc emits return's `b` PLUS the
 * closing-brace `b`; the original 1080 cc folded them. Proven not C-fixable
 * (full 7.1/5.3 flag matrix in docs). HONEST CAP -> stays NM at ~97%.
 *
 * Levers applied this session (all verified in-tree, non_matching build):
 * 1. PLAIN `int obj` home + separate `register int *o` (s1) alias: target does
 *    sw v0,0x34(sp) / lw s1,0x34(sp) / ... / lw v0,0x34(sp) (return-from-home).
 *    The old single `register obj` gave move s1,v0 (no home). Fixed [33-37],[54].
 *    obj declared FIRST -> top local slot 0x34 (decl-order top-down; register vars
 *    reserve the lower slots).
 * 2. D_8FFC_base (NEW base-0 alias of D_00000000 in undefined_syms_auto.txt):
 *    first call's arg1 must be the 3-insn `lui t6; addiu t6; lw a1,8(t6)` form
 *    (&D+8 read) WITHOUT CSE-sharing the &D_00000000 materialized for arg0.
 *    Same-symbol form emitted lui t6/addiu t6/move a0,t6/lw a1,8(t6) (4 insns,
 *    a0 stolen from t6). Distinct base-0 extern re-materializes both. This also
 *    restores the target temp-reg phase (t6 consumed -> D_50 RMW uses t7/t8).
 *    The old distinct-extern D_00000008 2-insn form (lui;lw 0x8) was WRONG here.
 * undefined_syms_auto.txt ADDITION (line 578):
 *   D_8FFC_base = 0x00000000;
 */
extern int gl_func_00000000();
extern char D_00000000;
extern int D_0000004C, D_00000050, D_00000064;
extern unsigned char D_0000017D;
extern char D_8FFC_base;   /* base-0 alias of D_00000000: defeats -O0 CSE of &D between arg0 and the +8 read (target re-materializes lui/addiu) */
int gl_func_00008FFC(int a0, int a1, int a2) {
    int obj;                 /* plain local: home slot 0x34, sw v0/lw s1/return-from-home */
    register char *base;     /* s0 */
    register int *o;         /* s1 */
    register char *tmp;      /* s2 */

    gl_func_00000000(&D_00000000, *(int *)((char *)&D_8FFC_base + 8));
    gl_func_00000000(D_0000004C, D_0000017D);
    D_00000050 = D_00000050 & 0x20;
    obj = gl_func_00000000(&D_00000000, D_00000064, 5, a2);
    base = (char*)&D_00000000;
    o = (int*)obj;
    tmp = base + 0x10;
    gl_func_00000000(tmp, o);
    if (o[0x14 / 4] != 0) {
        o[0x4 / 4] = 1;
    }
    tmp = base;
    o[0x14 / 4] = (int)tmp;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
    (void)a1;
    return obj;
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
/* gl_func_00009100 — VERIFIED 57/67 reloc-resolved (was 28/66 raw baseline).
 * ALL 65 target words reproduced in order except the live `b epilogue` offset
 * (10000003 vs 10000001) + a DEAD `b epilogue; nop` pair (build 67 vs target 65):
 * the documented -O0 RETURN-VALUE dead-double-b TOOLCHAIN-BINARY GAP
 * (docs/IDO_CODEGEN.md; original 1080 cc folded the second b, ours can't).
 * Proven not C-fixable. HONEST CAP -> stays NM at ~97% (up from 93.5%).
 *
 * Lever applied: PLAIN `int obj` home-slot + separate `register int *o` (s1)
 * alias — target sw v0,0x34(sp); lui s0; addiu s0; lw s1,0x34(sp); ... and
 * returns from the home (lw v0,0x34). Statement order matters:
 * obj = ctor(...); base = &D; o = obj; tmp = base + 0x10;  (base materialization
 * BETWEEN the home store and the alias reload, exactly as target).
 * obj declared FIRST -> top local slot 0x34 (-O0 slots decl-order top-down;
 * register vars reserve the lower slots 0x28/0x2C/0x30).
 * The old "obj home-spill / spill-timing -O0 cap" comment is WRONG — it's the
 * two-variable (plain + register alias) shape, same as 8FFC/8E48 siblings.
 * No new undefined_syms needed (D_00000179..183/D_0000004C/D_00000064 present).
 */
extern int gl_func_00000000();
extern char D_00000000;
extern unsigned char D_00000179, D_0000017A, D_0000017B, D_00000181, D_00000182, D_00000183;
extern int D_0000004C, D_00000064;
int gl_func_00009100(int a0, int a1, int a2) {
    int obj;                 /* plain local: home slot 0x34, sw v0/lw s1/return-from-home */
    register char *base;     /* s0 */
    register int *o;         /* s1 */
    register char *tmp;      /* s2 */

    D_00000181 = D_00000179;
    D_00000182 = D_0000017A;
    D_00000183 = D_0000017B;
    gl_func_00000000(D_0000004C, D_0000004C);
    obj = gl_func_00000000(&D_00000000, D_00000064, 4, a2);
    base = (char*)&D_00000000;
    o = (int*)obj;
    tmp = base + 0x10;
    gl_func_00000000(tmp, o);
    if (o[0x14 / 4] != 0) {
        o[0x4 / 4] = 1;
    }
    tmp = base;
    o[0x14 / 4] = (int)tmp;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
    (void)a1;
    return obj;
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
extern int D_0000004C, D_00000058, D_00000064;
int gl_func_00009204(int a0, int a1, int a2) {
    register char *g;      /* s0 */
    register int *node;    /* s1 */
    register char *tmp;    /* s2 */
    gl_func_00000000(&D_00000000, *(int *)((char *)&D_00000000 + 8));
    gl_func_00000000(D_0000004C, D_00000058);
    node = (int *)gl_func_00000000(&D_00000000, D_00000064, 6, a2);
    g = (char *)&D_00000000;
    tmp = g + 0x10;
    gl_func_00000000(tmp, node);
    if (node[0x14 / 4] != 0) {
        node[0x4 / 4] = 1;
    }
    node[0x14 / 4] = (int)g;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
    (void)a1;
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
extern int D_0000004C;
int gl_func_000092F4(int a0, int a1) {
    register char *g;      /* s0 */
    register int *node;    /* s1 */
    register char *tmp;    /* s2 */
    gl_func_00000000(&D_00000000, *(int *)((char *)&D_00000000 + 8));
    gl_func_00000000(D_0000004C, D_0000004C);
    node = (int *)gl_func_00000000(&D_00000000, 8, 2, a1);
    g = (char *)&D_00000000;
    tmp = g + 0x10;
    gl_func_00000000(tmp, node);
    if (node[0x14 / 4] != 0) {
        node[0x4 / 4] = 1;
    }
    node[0x14 / 4] = (int)g;
    gl_func_00000000(&D_00000000, 0);
    (void)a0;
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
