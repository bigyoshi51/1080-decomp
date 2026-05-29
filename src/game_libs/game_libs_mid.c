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
 * gl_func_0005D054 spill-slot swap. Honest cap at 99.79%; stays INCLUDE_ASM. */
extern char D_0000D138, D_0000D148, D_8C3C_v0;
void gl_func_00008C3C(int *a0, int a1) {
    register int *root;
    register int *mid;
    register int *child;

    gl_func_00000000(&D_00000000, &D_0000D138);
    gl_func_00000000(&D_00000000, *(int*)&D_8C3C_v0);
    gl_func_00000000(&D_00000000, 7, 0, 0);

    root = 0;
    if (root == 0) {
        root = (int*)gl_func_00000000(0xD4);
    }
    if (root != 0) {
        mid = root;
        if (mid == 0) {
            mid = (int*)gl_func_00000000(0x50);
        }
        if (mid != 0) {
            child = mid;
            if (child == 0) {
                child = (int*)gl_func_00000000(0x2C);
            }
            if (child != 0) {
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
    (void)a1;
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

/* gl_func_00008FFC: -O0 init sequence (fresh decode 2026-05-28, mnemonic disasm).
 * Five callee calls bracketing a global-state mask + a constructor: configures
 * two globals, masks D[0x50] to bit 0x20, builds an object via call3 (returns
 * obj, a3=incoming a2), registers it (call4), links obj into D's list (obj->0x14),
 * sets obj->0x4=1 if obj->0x14 was non-null, then a final call5; returns obj.
 * Data refs use the &D_00000000+offset addend idiom; builds -O0 (game_libs_mid).
 * 82.38% as of 2026-05-28 (fresh decode 0→67→82). Lever: the target holds base
 * (&D), obj, and a scratch in s0/s1/s2 across the calls — at -O0 that means
 * `register` locals (declared base/obj/tmp in s0/s1/s2 order). RESIDUAL (~18%,
 * -O0 codegen, hard to steer): (a) base re-materialization order — target emits
 * `lui a0;addiu a0` for call1's arg0 separately from the t6 used for the +8 load,
 * mine shares one base via `move a0,t6` (the -O0 inverse of base-CSE); (b) obj
 * spill-timing — target stores the call3 result to obj's home (sw v0,0x34) +
 * reloads into s1, and RETURNS from the home (lw v0,0x34), whereas mine uses
 * `move s1,v0` + returns s1 directly. Real wrap, correct logic; stays NM. */
#ifdef NON_MATCHING
int gl_func_00008FFC(int a0, int a1, int a2) {
    register char *base;     /* s0 */
    register int *obj;       /* s1 */
    register char *tmp;      /* s2 */

    gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000 + 8));
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x4C),
                     *(unsigned char*)((char*)&D_00000000 + 0x17D));
    *(int*)((char*)&D_00000000 + 0x50) =
        *(int*)((char*)&D_00000000 + 0x50) & 0x20;
    obj = (int*)gl_func_00000000(&D_00000000,
                                 *(int*)((char*)&D_00000000 + 0x64), 5, a2);
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
 * 79.85% as of 2026-05-28 (0→77→80; inlining the call1 duplicated arg dropped
 * the named-temp home roundtrip). RESIDUAL (~20%, -O0 codegen, hard to steer):
 * the 3 byte-copies share ONE &D base (lui+addiu) where the target re-materializes
 * lui per access (the -O0 base-CSE nuance, cf. 8FFC), plus the same obj
 * spill-timing/return-from-home as the 8FFC sibling. Real wrap, correct logic. */
#ifdef NON_MATCHING
int gl_func_00009100(int a0, int a1, int a2) {
    register char *base;     /* s0 */
    register int *obj;       /* s1 */
    register char *tmp;      /* s2 */

    *(unsigned char*)((char*)&D_00000000 + 0x181) =
        *(unsigned char*)((char*)&D_00000000 + 0x179);
    *(unsigned char*)((char*)&D_00000000 + 0x182) =
        *(unsigned char*)((char*)&D_00000000 + 0x17A);
    *(unsigned char*)((char*)&D_00000000 + 0x183) =
        *(unsigned char*)((char*)&D_00000000 + 0x17B);
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x4C),
                     *(int*)((char*)&D_00000000 + 0x4C));
    obj = (int*)gl_func_00000000(&D_00000000,
                                 *(int*)((char*)&D_00000000 + 0x64), 4, a2);
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
