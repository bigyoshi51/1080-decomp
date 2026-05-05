#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* Array-indexing utility: return a0 + a0->field_7C * 0x28 + 0x84.
 * 7/8 NM cap structural (IDO -O2 fills jr-ra delay slot with addiu,
 * target had unfilled). Promoted to exact via INSN_PATCH at offsets
 * 0x10/0x14 (Makefile entry, ports the 2-word patch from agent-b). */
char *func_00010324(char *a0) {
    return a0 + *(int*)(a0 + 0x7C) * 0x28 + 0x84;
}

void func_00010344(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}

void func_00010AA8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010AB0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000118E4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001195C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011A34);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011AB4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011BF0);

#ifdef NON_MATCHING
/* append-to-array helper: a0->0x120 is the count, a0->0xE0[count] = a1.
 * 13 insns / 0x34. -O0 indicators: empty `addiu sp,-8` frame with no spill,
 * `b +1; nop` dead-branch BBL marker, leaf function. Verified 2026-05-02
 * that BYTE-IDENTICAL at standalone -O0 with `register s32 idx; register
 * s32 *p = a0;` decl order (idx FIRST so p gets $a3 = higher arg slot).
 *
 * BLOCKED: containing file bootup_uso_tail3a.c is built at -O2 -g3 (per
 * Makefile line 52). To match, would need to split this function out into
 * a new bootup_uso_o0_11C70.c with -O0 OPT_FLAGS, plus migrate ~20 other
 * 0x11C70..0x120A8 functions and adjust tenshoe.ld + tail3a's
 * TRUNCATE_TEXT. Infrastructure work, not single-tick scope. */
void func_00011C70(s32 *a0, s32 a1) {
    register s32 idx;
    register s32 *p = a0;
    idx = *(s32*)((char*)p + 0x120);
    *(s32*)((char*)p + 0x120) = idx + 1;
    *(s32*)((char*)a0 + idx*4 + 0xE0) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011C70);
#endif

#ifdef NON_MATCHING
/* 44.62% NM at -O2 (target -O0). Append-to-array helper at offsets 0x124
 * (count) + 0x100 (4-byte entries).
 * 13 insns / 0x34. -O0 indicators: minimal `addiu sp,-8` frame with no spill,
 * `b +1; nop` dead-branch BB-ender, leaf function, `or a3, a0, zero` arg copy
 * to high register. Same structure as adjacent func_00011C70 which is also
 * documented as O0-split-blocked.
 *
 * BLOCKED: this is part of the ~20-function 0x11C70..0x120A8 -O0 cluster
 * inside bootup_uso_tail3a.c (which builds at -O2 -g3). To match, would need
 * to split this function (and the rest of the cluster) into a new
 * bootup_uso_o0_11C70.c with -O0 OPT_FLAGS, plus adjust tail3a's
 * TRUNCATE_TEXT and the linker script. Same infrastructure scope as
 * func_00011C70's wrap doc.
 *
 * Body inferred (default -O2 emit will diverge — kept here for reference): */
void func_00011CA4(int *a0, int a1) {
    int idx = *(int*)((char*)a0 + 0x124);
    *(int*)((char*)a0 + 0x124) = idx + 1;
    *(int*)((char*)a0 + idx * 4 + 0x100) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CA4);
#endif

#ifdef NON_MATCHING
/* func_00011CD8: 46.35%, 26-insn flag-setter. Target is -O0-shape (full
 * arg-spill at entry, every var reloaded from stack, dead `b .L+1` BB
 * markers). bootup_uso_tail3a is -O2 -g3 which produces 19 insns — 7
 * insn deficit reproduces the logic but won't byte-match. Promotion
 * needs file split to -O0 (per project_1080_bootup_uso_o0_runs memo). */
void func_00011CD8(int *a0, int a1) {
    if (a1 != 0) {
        func_00000000(a0);
        *(int*)((char*)a0 + 0x188) = 0;
    } else {
        func_00000000(a0);
        *(int*)((char*)a0 + 0x188) = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CD8);
#endif

#ifdef NON_MATCHING
/* Structure matches but IDO -O2 emits beqzl with the body's lw in delay slot,
 * while target has beqz + nop + or v0,zero + jr ra (separate exit paths,
 * UNFILLED delay slots).
 *
 * 2026-05-04 standalone tests (-O0, -O1, -O1 -g, -O2 -- 8 C variants per level):
 *   -O2: ALL variants → beqzl + delay-slot lw (filled, ~17 insns)
 *   -O1 (no -g): beqz + FILLED jr ra delay (`move v0, zero` in slot)
 *   -O1 -g: same as -O1 — IDO does NOT use -g for delay-slot suppression
 *           (unlike KMC GCC where -g IS the delay-slot lever)
 *   -O0: bnez (wrong direction) + extra dead-code `b +4; nop` pair, jr ra
 *        delays UNFILLED — closer in delay-slot fill but wrong branch + extra
 *        code
 *
 * No standard IDO -O level produces target's exact shape (beqz + nop + or v0
 * + jr ra + nop). Target may have been compiled with a non-standard flag combo
 * or post-processed. INSN_PATCH could fix the 5-byte diff between our -O2
 * emit and target, but the size/insn-count mismatch (target 12 insns vs
 * -O2 emit's variable count) blocks INSN_PATCH per
 * feedback_insn_patch_size_diff_blocked.md. Defer.
 *
 * 2026-05-05 RE-DIAGNOSED: built/non_matching emits 11 insns / 0x2C, target
 * has 12 insns / 0x30. The 1-insn shrinkage is from IDO -O2 consolidating
 * the two return paths via `beql + lw $v0,0xdc(t8) [delay-likely]` (opcode
 * 0x50200004) — branch-likely with the lw cancelled when not taken. Target
 * uses an explicit if/else with two distinct jr-ra blocks (0xc additional
 * bytes for the second jr+epilogue). Promotion path: SUFFIX_BYTES=0x4
 * (add trailing nop) + INSN_PATCH on most insns to reorder into target's
 * shape — but that's effectively rewriting most bytes, defeating the
 * purpose. Real fix is suppressing branch-likely consolidation at C level,
 * which 8 source variants at 4 -O levels failed to do. */
int func_00011D40(int *a0, int a1) {
    if (*(int*)((char*)a0 + 0x120) < a1) return 0;
    return *(int*)((char*)a0 + a1 * 4 + 0xDC);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D40);
#endif

void func_00011D70(void) {
}

#ifdef NON_MATCHING
/* 40.00% NM at -O2 (target -O0). Indexed-pointer-array float load with
 * early-out. 15 insns / 0x3C.
 * -O0 indicators: 3 separate `jr ra` exits with dead jr-ra-nop pair at
 * 0xA0/0xA4, no shared epilogue. Same O0-split-blocked cluster as
 * adjacent func_00011C70/func_00011CA4.
 *
 * Structure:
 *   if (a0->0x18C != 0) return 0.0f;
 *   idx = a0->0x128;
 *   p = (float*)a0[+0xE0 + idx*4];   // pointer-array + index
 *   return *p;
 *
 * Per /decompile run: structural decode, % to be measured. */
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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011ED4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011FA8);

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

