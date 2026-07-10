#include "common.h"

extern int func_00000000();
extern char D_00000000;

/* Tail slice of the original bootup_uso_tail3a_bot.c (2026-07-10 carve, see
 * that file's header comment). Holds the 11DF8 empty stub, the 11E00/11ED4/
 * 11FA8 NM triplet and the matched 1207C..120A0 tail at -O2 -g3. */

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
 * func_00011D78 (per docs/MATCHING_WORKFLOW.md#feedback-asmproc-o0-min-insn-count-blocks-2insn-include-asm).
 *
 * 2026-06-23 -O0-C RECIPE (verified in isolation, ready when the split
 * unblocks): the target is -O0 (frame -8, loop counter i spilled to sp+4,
 * NO branch-likely). INLINE idx and p (reload a0[0x128] / the slot pointer
 * each use — do NOT cache them as locals; caching adds sp slots -> frame -16,
 * +18w). With inline idx/p + a single-exit `int result` form, the isolated
 * -O0 build is 59w vs 53w; residual is -O0 control-flow shape (target shares
 * ONE `move v0,zero` return-0 reached by all early exits + computes the value
 * returns directly in v0; multi-return-no-var duplicates return-0, result-var
 * spills to stack, goto-form 62w — none exact yet). Same recipe applies to the
 * mirror siblings func_00011ED4 / func_00011FA8 (all 6.6%, identical shape). */
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

