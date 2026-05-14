#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

extern int func_00000008;       /* USO-base reloc (D_-style placeholder pointer) */
extern int func_000000F0;       /* USO-base reloc */
extern int func_00000188;       /* USO-base reloc */
extern char D_0000C57C;

#ifdef NON_MATCHING
/* func_0000F81C: 78-insn (0x138) allocator + init helper.
 *
 * Decoded structure:
 *   1. Set up local flags word = 0. If arg1 (a1) != 0, flags |= 0x6.
 *   2. Zero 4 floats at (&func_00000008 + 0x28)[0..C] (some Vec4-like slot).
 *   3. Big call gl_func_00000000(0, 0x64, &D_0000C57C, 0x6D, [stack args
 *      0x6E,0,0,0x6F,0x140,0xF0,0x70,flags|0x400,0x71,0x2,0]) — likely an
 *      object allocator with a long argument-list constructor pattern.
 *   4. result is saved to local + sp+0x80; another call:
 *      gl_func_00000000(&func_00000008+0x24, result).
 *   5. *(int*)((char*)*(int*)(&func_000000F0+0x44) + 0x114) = result.
 *   6. Return result.
 *
 * Big-constructor pattern, 13-arg call with many stack-passed args
 * (sp+0x10..sp+0x3C). First-draft, expect ~40-60% fuzzy. Multi-tick
 * refinement target. */
void* func_0000F81C(int a0, int a1) {
    int flags = 0;
    void *result;
    float *floats;
    if (a1 != 0) {
        flags |= 6;
    }
    floats = (float*)((char*)&func_00000008 + 0x28);
    floats[0] = 0.0f;
    floats[1] = 0.0f;
    floats[2] = 0.0f;
    floats[3] = 0.0f;
    result = (void*)func_00000000(0, 0x64, &D_0000C57C, 0x6D,
                                   0x6E, 0, 0, 0x6F, 0x140, 0xF0,
                                   0x70, flags | 0x400, 0x71, 2, 0);
    func_00000000((char*)&func_00000008 + 0x24, result);
    *(int*)((char*)*(int*)((char*)&func_000000F0 + 0x44) + 0x114) = (int)result;
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F81C);
#endif

#ifdef NON_MATCHING
/* func_0000F954: 37-insn (0x94) -O0-shape init helper.
 *
 * Decoded structure:
 *   if (a0->field_48 != 0) func_00000000(a0->field_48);  // cleanup old
 *   func_00000000(&D_00000000);                            // gl-base call
 *   tmp = *(int*)((char*)&func_00000188 + 0x190);
 *   func_00000000(tmp, 3, 0);                              // 3-arg call
 *   a0->field_2C = 1;
 *   func_00000000(a1, a2, 0);                              // 3-arg call
 *
 * BLOCKED: -O0 shape (caller-arg spill at sp+0x18/1C/20, no register
 * promotion, `b .L+1; nop` dead BB markers). bootup_uso_tail1.c is
 * -O2 — wrap is documented-only. Promotion path: file split per
 * feedback_o0_cluster_split_with_layout_shim.md (same as func_000100F0
 * and func_000118E4 already done — bootup_uso_o0_F954.c). */
void func_0000F954(int *a0, int a1, int a2) {
    int tmp;
    if (*(int*)((char*)a0 + 0x48) != 0) {
        func_00000000(*(int*)((char*)a0 + 0x48));
    }
    func_00000000(&D_00000000);
    tmp = *(int*)((char*)&func_00000188 + 0x190);
    func_00000000(tmp, 3, 0);
    *(int*)((char*)a0 + 0x2C) = 1;
    func_00000000(a1, a2, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F954);
#endif

#ifdef NON_MATCHING
/* func_0000F9E8: 64-insn (0x100) init helper with dead-branch bit-clear.
 *
 * Decoded structure:
 *   func_00000000();                          // bare call (likely __init or similar)
 *   result = func_00000000(&D_00000000);      // alloc-ish, returns ptr
 *   self->field_38 = result;
 *   {
 *     aux = self->field_48;
 *     vt  = aux->field_28;
 *     fn  = vt->field_5C;
 *     off = (short)vt->field_58;
 *     fn(off + (int)aux);                     // indirect call
 *   }
 *   self->field_48->field_7C = 0;
 *   self->field_30 = 1;
 *   self->field_34 = 0;
 *   if (self->field_4C != 0) {
 *     p = self->field_4C + 0x18;
 *     *p &= ~8;                               // clear bit 3 (always — dead set-branch)
 *   }
 *
 * O0 markers: asm has `or s2, zero, zero; beqz s2` which is always-taken at
 * runtime (s2 starts 0, never modified before the branch) → the "set bit 8"
 * arm is dead code emitted by -O0. Simplified to plain `*p &= ~8` here.
 *
 * Likely O0-blocked (same cap class as siblings FBCC/FEA0/100F0). Path
 * forward: file-split. */
extern int func_00000000();
void func_0000F9E8(int *self) {
    int *result;
    int *aux;
    int *vt;
    int *p;
    short off;
    void (*fn)(int);

    func_00000000();
    result = (int*)func_00000000(&D_00000000);
    self[0x38 / 4] = (int)result;

    aux = (int*)self[0x48 / 4];
    vt = (int*)aux[0x28 / 4];
    off = *(short*)((char*)vt + 0x58);
    fn = (void(*)(int))vt[0x5C / 4];
    fn(off + (int)aux);

    ((int*)self[0x48 / 4])[0x7C / 4] = 0;
    self[0x30 / 4] = 1;
    self[0x34 / 4] = 0;

    if (self[0x4C / 4] != 0) {
        p = (int*)((char*)self[0x4C / 4] + 0x18);
        *p &= ~8;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F9E8);
#endif

#ifdef NON_MATCHING
/* func_0000FAE8: 57-insn (0xE4) reset+set-bit helper, sibling of func_0000F9E8.
 *
 * Decoded structure (very close to F9E8 but with opposite dead-branch
 * resolution — F9E8 has s2=0 → clear bit 8; this has s2=1 → set bit 8):
 *
 *   func_00000000();                          // bare call
 *   if (self->field_38 == 0) {
 *     func_00000000(&D_00000000);             // optional init
 *   }
 *   func_00000000(self->field_48);            // cleanup-prev?
 *   self->field_30 = 0;
 *   self->field_34 = 0;
 *   if (self->field_4C != 0) {
 *     p = self->field_4C + 0x18;
 *     *p |= 8;                                 // set bit 3 (always — dead clear-branch)
 *   }
 *
 * O0 markers: `addiu s2, zero, 1; beqz s2` dead-always-false branch (the
 * "clear bit 8" arm is dead code). Simplified to plain `*p |= 8`.
 *
 * Same -O0 cap class as F9E8. Promotion path: file-split. */
void func_0000FAE8(int *self) {
    int *p;

    func_00000000();
    if (self[0x38 / 4] == 0) {
        func_00000000(&D_00000000);
    }
    func_00000000(self[0x48 / 4]);
    self[0x30 / 4] = 0;
    self[0x34 / 4] = 0;
    if (self[0x4C / 4] != 0) {
        p = (int*)((char*)self[0x4C / 4] + 0x18);
        *p |= 8;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FAE8);
#endif

#ifdef NON_MATCHING
/* Single-block bit-clear (set=0, mask=8) on `(arg0->field_48) + 0x18`.
 * Same shape as the bootup_uso_o0_F390.c bit-set/clear cluster
 * (func_0000F564 etc.) but with one extra deref on arg0 (asm has
 * `lw a1, 0x48(a0); addiu a1, a1, 0x18` vs the F390 cluster's
 * `addiu a1, a0, 0x18`).
 *
 * O0-blocked: 23 insns / 0x5C with -O0 signals (extra `b +1; nop` at
 * 0xFC14, redundant `or t0, a2, zero` reload, no `register`-promoted
 * reg-only path). bootup_uso_tail1.c is -O2 by default so this wrap
 * won't byte-match; promotion path is the file-split recipe per
 * feedback_uso_accessor_o0_file_split_recipe.md (move to a new
 * bootup_uso_o0_FBCC.c file with OPT_FLAGS := -O0). */
void func_0000FBCC(int *a0) {
    register int *p1, *p2;
    register int set;
    register int *t;
    p1 = (int*)((char*)a0[0x48/4] + 0x18);
    p2 = p1;
    set = 0;
    if (set) { t = p2; *t = *t | 8; }
    else     { t = p2; *t = *t & ~8; }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FBCC);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);

#ifdef NON_MATCHING
/* 18-insn indirect-call wrapper. Logic verified:
 *   p = a0->field_28; off = (short)p->field_60; (*p->field_64)(a0 + off).
 *
 * BLOCKED: function is -O0-shape (frame -0x28 with s0 spill/reload pattern,
 * dead 'b +1; nop' BB-end marker after the jalr) but lives in
 * bootup_uso_tail1.c which builds at -O2. IDO -O2 inlines my C to 11
 * insns with t-regs only — 7-insn deficit + frame-size mismatch.
 *
 * 2026-05-08: tested the narrow `register self = a0` alias suggested by
 * the staged bootup_uso_o0_FBCC.c note. In the current -O2 tail1 unit it
 * still emits the same 11-insn t-reg-only shape (frame -0x18, no s0 spill,
 * no dead `b +1; nop` marker), so the -O0 file-split blocker remains.
 *
 * 2026-05-08 (later): exhaustive -O0 standalone test of 4 C-body variants
 * (register-p, register-a0, register-p+register-off named locals, typed
 * struct accessor). All produce 19-insn frame-0x28 emit vs target's 18
 * insns. Target form has SINGLE reload of a0 reused for both
 * `lw s0, 0x28(t6)` and `addu a0, t7, t6`; my variants all emit a SECOND
 * reload `lw t8, 0x28(sp)` before the addu. IDO -O0 doesn't peephole-
 * combine adjacent uses of an already-loaded stack value — each source-
 * level use of `a0` produces an independent reload.
 *
 * Closest variant (v2): `void func_0000FEA0(register char *a0) { register
 * char *p = *(char**)(a0 + 0x28); ((void(*)(char*))*(int*)(p + 0x64))
 * (a0 + *(short*)(p + 0x60)); }` — 19 insns, +4 bytes vs target. The
 * extra `lw t8, 40(sp); addu a0, t7, t8` pair could be patched away via
 * INSN_PATCH (replace the 2 insns with `nop; addu a0, t7, t6`) +
 * SUFFIX_BYTES=-4 (shrink), but that requires a TRUNCATE_TEXT shim.
 *
 * Promotion path: file split per feedback_o0_cluster_split_with_layout_shim.md
 * (create src/bootup_uso/bootup_uso_o0_FEA0.c with -O0 OPT_FLAGS, update
 * linker script) PLUS a 2-insn INSN_PATCH to collapse the redundant
 * a0-reload. Deferred — heavier than one-tick scope. */
void func_0000FEA0(char *a0) {
    register char *self = a0;
    char *p = *(char**)(self + 0x28);
    ((void(*)(char*))*(int*)(p + 0x64))(self + *(short*)(p + 0x60));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);

/* func_000100F0 + func_0001016C split out to bootup_uso_o0_100F0.c on
 * 2026-05-14 for -O0 build (same recipe as func_000118E4 ->
 * bootup_uso_o0_118E4.c earlier this date). */
