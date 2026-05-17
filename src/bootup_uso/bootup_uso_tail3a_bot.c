#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* Tail-bot half of the original bootup_uso_tail3a.c, split on 2026-05-07
 * to carve func_00011D40 out into bootup_uso_o0_11D40.c (-O0). The rest
 * of the 0x11C70..0x120A8 -O0 cluster (CA4/CD8/D78/DBC) stays NM-wrapped
 * here at -O2 -g3 since their bodies haven't been verified byte-exact at
 * -O0 yet — separate /decompile runs will migrate them as they get
 * verified. */

void func_00011D70(void) {
}

#ifdef NON_MATCHING
/* Indexed-pointer-array float load with early-out. 15 insns / 0x3C target.
 * NOTE: this body builds at -O2 (its containing file) but target is -O0.
 *
 * 2026-05-07 -O0 standalone variant testing (detailed):
 *   - locals (no register), if-then-fallthrough → 22 insns w/ frame, spills
 *   - register int idx + register float *p, if/return-zero/main → 19 insns
 *     w/ frame (still spills despite register hint)
 *   - compound expr `**(float**)(...)` no locals, if(==0){return *p;} else
 *     return 0.0f → 13 insns NO frame, NO dead-pair (size 0x34 vs 0x3C)
 *   - same compound with explicit if/else { return 0.0f; } else block
 *     → 17 insns w/ shared epilogue + dispatch b (size 0x44, BAD)
 *   - goto-zero-label form → 15 insns but extra `b dispatch` after beqz
 *     (right size but wrong shape)
 *
 * Best -O0 standalone: 13 insns (no-locals compound-expr form). Missing the
 * 2-insn dead jr-ra-nop pair between main-return and .L_zero label that
 * target has. INSN_PATCH can't insert between, only replace. The dead-pair
 * shape is an -O0 inter-block emission that doesn't reproduce from any
 * straightforward C structure. SUFFIX_BYTES would append AFTER the
 * function, not in the middle.
 *
 * Migration to -O0 file blocked by adjacent empty stubs (11D70/11DB4/11DF8)
 * which can't INCLUDE_ASM into -O0 file (asm-processor min_instr_count=4
 * blocks 2-insn blocks). See docs/MATCHING_WORKFLOW.md
 * #feedback-asmproc-o0-min-insn-count-blocks-2insn-include-asm.
 *
 * Status: NM-cap-class -O0-inter-block-dead-pair. */
float func_00011D78(int *a0) {
    int idx;
    float *p;
    if (*(int*)((char*)a0 + 0x18C) != 0) return 0.0f;
    idx = *(int*)((char*)a0 + 0x128);
    p = *(float**)((char*)a0 + idx * 4 + 0xE0);
    return *p;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D78);
#endif

void func_00011DB4(void) {
}

#ifdef NON_MATCHING
/* Sibling of func_00011D78 — byte-identical structure, reads p[1] (.y)
 * instead of p[0] (.x). Same -O0 cluster blocker (3 separate jr ra exits,
 * no shared epilogue). 15 insns / 0x3C.
 *
 * Structure:
 *   if (a0->0x18C != 0) return 0.0f;
 *   idx = a0->0x128;
 *   p = (float*)a0[+0xE0 + idx*4];   // pointer-array + index
 *   return p[1];                     // .y component
 *
 * Same O0-split-blocked cluster as adjacent func_00011C70/CA4/D78. */
float func_00011DBC(int *a0) {
    int idx;
    float *p;
    if (*(int*)((char*)a0 + 0x18C) != 0) return 0.0f;
    idx = *(int*)((char*)a0 + 0x128);
    p = *(float**)((char*)a0 + idx * 4 + 0xE0);
    return p[1];
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011DBC);
#endif

void func_00011DF8(void) {
}

#ifdef NON_MATCHING
/* func_00011E00: 53-insn "find first slot with mask bit set".
 * Target appears to be -O0 (lots of separate load + branch + nop-filled
 * delay slots) but the file is built at -O2 -g3 — same -O0-cluster
 * blocker as adjacent func_00011D78 (per its wrap doc).
 *
 *   if (a0->[0x18C] != 0) return 0;
 *   if (a0->[0x128] != -1) {
 *       p = a0[0xE0 + idx*4];
 *       if (p->[0x18] & a1) return 1 << idx;
 *       return 0;
 *   }
 *   for (i = 0; i < a0->[0x120]; i++) {
 *       p = a0[0xE0 + i*4];
 *       if (p->[0x18] & a1) return 1 << i;
 *   }
 *   return 0;
 *
 * idx == -1 means scan all slots; otherwise check only slot[idx].
 *
 * Cap: -O2 -g3 emits 41 insns vs target's 53 (compact control flow
 * vs -O0 separate-load-and-branch pattern). Migration to a dedicated
 * -O0 file is blocked by the same adjacent-empty-stub issue noted on
 * func_00011D78 (per docs/MATCHING_WORKFLOW.md#feedback-asmproc-o0-min-insn-count-blocks-2insn-include-asm). */
int func_00011E00(int *a0, int a1) {
    int idx;
    int i;
    int *p;
    if (a0[0x18C/4] != 0) return 0;
    idx = a0[0x128/4];
    if (idx != -1) {
        p = (int*)a0[0xE0/4 + idx];
        if (p[0x18/4] & a1) return 1 << idx;
        return 0;
    }
    if (a0[0x120/4] <= 0) return 0;
    for (i = 0; i < a0[0x120/4]; i++) {
        p = (int*)a0[0xE0/4 + i];
        if (p[0x18/4] & a1) return 1 << i;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011E00);
#endif

#ifdef NON_MATCHING
/* func_00011ED4: byte-identical sibling of func_00011E00 except the
 * mask check reads `p->[0x10]` instead of `p->[0x18]`. Same cap class
 * (target is -O0 codegen but file builds at -O2 -g3). */
int func_00011ED4(int *a0, int a1) {
    int idx;
    int i;
    int *p;
    if (a0[0x18C/4] != 0) return 0;
    idx = a0[0x128/4];
    if (idx != -1) {
        p = (int*)a0[0xE0/4 + idx];
        if (p[0x10/4] & a1) return 1 << idx;
        return 0;
    }
    if (a0[0x120/4] <= 0) return 0;
    for (i = 0; i < a0[0x120/4]; i++) {
        p = (int*)a0[0xE0/4 + i];
        if (p[0x10/4] & a1) return 1 << i;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011ED4);
#endif

#ifdef NON_MATCHING
/* func_00011FA8: byte-identical sibling of func_00011E00 except the
 * mask check reads `p->[0x1C]` instead of `p->[0x18]`. Same cap class
 * (target is -O0 codegen but file builds at -O2 -g3). */
int func_00011FA8(int *a0, int a1) {
    int idx;
    int i;
    int *p;
    if (a0[0x18C/4] != 0) return 0;
    idx = a0[0x128/4];
    if (idx != -1) {
        p = (int*)a0[0xE0/4 + idx];
        if (p[0x1C/4] & a1) return 1 << idx;
        return 0;
    }
    if (a0[0x120/4] <= 0) return 0;
    for (i = 0; i < a0[0x120/4]; i++) {
        p = (int*)a0[0xE0/4 + i];
        if (p[0x1C/4] & a1) return 1 << i;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011FA8);
#endif

void func_0001207C(int *a0, int a1) {
    *(int*)((char*)a0 + 0x128) = a1;
}

void func_00012088(void) {
}

void func_00012090(int *a0) {
    *(int*)((char*)a0 + 0x128) = -1;
}

void func_000120A0(void) {
}
