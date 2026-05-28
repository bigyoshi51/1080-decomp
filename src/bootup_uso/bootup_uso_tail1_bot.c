#include "common.h"

/* bootup_uso 0xFC28..0x100F0 region, split off bootup_uso_tail1.c on
 * 2026-05-28 so that func_0000FBCC could move to a -O0 sub-file
 * (bootup_uso_o0_FBCC.c) and land as a byte-exact match. These four
 * functions stay INCLUDE_ASM NM-wraps (documented -O0 alloc-cascade /
 * dead-BB / t-reg caps — see per-function notes). TRUNCATE_TEXT clips
 * this file's .text to FEE8's true end (0x4C8) so o0_100F0.c.o abuts at
 * bootup offset 0x100F0. */

extern int func_00000000();
extern int func_00000008;       /* USO-base reloc (D_-style placeholder pointer) */
extern char D_00000000;
extern char D_0000C58C;
extern char D_0000C594;
extern char D_0000C5A4;
extern char D_0000C5AC;

#ifdef NON_MATCHING
/* func_0000FC28: 73-insn (0x124) constructor + init chain.
 *
 * Decoded shape (a0 = optional preallocated buffer):
 *   if (a0 == 0) {
 *       a0 = alloc(0x50);
 *       if (a0 == 0) goto end;
 *   }
 *   s0 = a0;
 *   if (s0 == 0) {                        // dead branch (a0 known non-NULL)
 *       s0 = alloc(0x50);
 *       if (s0 == 0) goto skip_init1;
 *   }
 *   s1 = s0;
 *   if (s1 == 0) {                        // dead branch
 *       s1 = alloc(0x2C);
 *       if (s1 == 0) goto skip_init2;
 *   }
 *   init(s1, &D_0000C58C);
 *   s1->field_28 = &D_00000000;           // vtable
 * skip_init2:
 *   s0->field_28 = &D_00000000;           // vtable
 * skip_init1:
 *   a0->field_28 = &D_00000000;           // vtable
 *   a0->field_C = &D_0000C594;
 *   v0 = call(a0, 0);
 *   *(int*)&D_00000000 = v0;
 *   ptr = *(int*)&D_00000000;
 *   call(ptr, a0);
 * end:
 *   return a0;
 *
 * Dead-branch pattern (`s0 = a0; if (s0 == 0) alloc()`) suggests -O0
 * expansion of macros or inlined alloc-checks where the source had
 * `if (!a) a = alloc()` repeated. -O2 would eliminate the redundant
 * checks but -O0 keeps them.
 *
 * Likely O0-blocked like other tail1 wrappers; file-split deferred. */
void* func_0000FC28(void *a0) {
    void *s0, *s1;

    if (a0 == 0) {
        a0 = (void*)func_00000000(0x50);
        if (a0 == 0) goto end;
    }
    s0 = a0;
    if (s0 == 0) {
        s0 = (void*)func_00000000(0x50);
        if (s0 == 0) goto skip_init1;
    }
    s1 = s0;
    if (s1 == 0) {
        s1 = (void*)func_00000000(0x2C);
        if (s1 == 0) goto skip_init2;
    }
    func_00000000(s1, &D_0000C58C);
    *(int*)((char*)s1 + 0x28) = (int)&D_00000000;
skip_init2:
    *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
skip_init1:
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x0C) = (int)&D_0000C594;
    {
        int v = func_00000000(a0, 0);
        *(int*)&D_00000000 = v;
    }
    func_00000000(*(int*)&D_00000000, a0);
end:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);
#endif

#ifdef NON_MATCHING
/* func_0000FD4C: 85-insn (0x154) alloc-chain + multi-init helper.
 *
 * Larger sibling of func_0000FC28 (73-insn alloc-chain). Same nested
 * alloc/null-check pattern (a0 -> s0 -> s1 with sizes 0x50/0x50/0x2C)
 * plus additional state writes:
 *   - a0->field_0C = &D_0000C5AC
 *   - *(int*)(func_00000008 + 0x2C) = a1   // global a1 stash
 *   - *(int*)(func_00000008 + 0x38) = a2   // global a2 stash
 *   - a0->field_44 = 0
 *   - a0->field_48 = 0
 *   - call(a0, 0) -> store result at *&D_00000000
 *   - call(*&D_00000000, a0)
 *
 * Same -O0 cap class as FC28. File-split deferred. */
void func_0000FD4C(void *a0, int a1, int a2) {
    void *s0, *s1;

    if (a0 == 0) {
        a0 = (void*)func_00000000(0x50);
        if (a0 == 0) goto end;
    }
    s0 = a0;
    if (s0 == 0) {
        s0 = (void*)func_00000000(0x50);
        if (s0 == 0) goto skip_init1;
    }
    s1 = s0;
    if (s1 == 0) {
        s1 = (void*)func_00000000(0x2C);
        if (s1 == 0) goto skip_init2;
    }
    func_00000000(s1, &D_0000C5A4);
    *(int*)((char*)s1 + 0x28) = (int)&D_00000000;
skip_init2:
    *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
skip_init1:
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x0C) = (int)&D_0000C5AC;
    *(int*)((char*)&func_00000008 + 0x2C) = a1;
    *(int*)((char*)&func_00000008 + 0x38) = a2;
    *(int*)((char*)a0 + 0x44) = 0;
    *(int*)((char*)a0 + 0x48) = 0;
    {
        int v = func_00000000(a0, 0);
        *(int*)&D_00000000 = v;
    }
    func_00000000(*(int*)&D_00000000, a0);
end:
    return;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);
#endif

#ifdef NON_MATCHING
/* 18-insn indirect-call wrapper. Logic verified:
 *   p = a0->field_28; off = (short)p->field_60; (*p->field_64)(a0 + off).
 *
 * BLOCKED: function is -O0-shape (frame -0x28 with s0 spill/reload pattern,
 * dead 'b +1; nop' BB-end marker after the jalr) but lives in
 * bootup_uso_tail1.c which builds at -O2. IDO -O2 inlines my C to 11
 * insns with t-regs only — 7-insn deficit + frame-size mismatch.
 *
 * 2026-05-08: tested the narrow `register self = a0` alias. In the -O2
 * tail1 unit it still emits the 11-insn t-reg-only shape (frame -0x18, no
 * s0 spill, no dead `b +1; nop`), so the -O0 file-split blocker remains.
 *
 * 2026-05-08 (later): exhaustive -O0 standalone test of 4 C-body variants
 * (register-p, register-a0, register-p+register-off named locals, typed
 * struct accessor). All produce 19-insn frame-0x28 emit vs target's 18
 * insns. Target form has SINGLE reload of a0 reused for both
 * `lw s0, 0x28(t6)` and `addu a0, t7, t6`; my variants all emit a SECOND
 * reload `lw t8, 0x28(sp)` before the addu. IDO -O0 doesn't peephole-
 * combine adjacent uses of an already-loaded stack value.
 *
 * Even at -O0 this stays +4 bytes (19 vs 18); the double-reload is the
 * residual cap. Stays INCLUDE_ASM. */
void func_0000FEA0(char *a0) {
    register char *self = a0;
    char *p = *(char**)(self + 0x28);
    ((void(*)(char*))*(int*)(p + 0x64))(self + *(short*)(p + 0x60));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);
#endif

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
void *func_0000FEE8(char *a0) {
    char *o;
    char *s;
    float *c;
    o = a0 ? a0 : (char *)func_00000000(0x304);
    if (!o) return 0;
    s = (char *)func_00000000(0x2C);
    if (s) {
        func_00000000(s, (char *)&D_00000000 + 0xC5BC);
        *(char **)(s + 0x28) = &D_00000000;
    }
    *(char **)(o + 0x28) = &D_00000000;
    *(char **)(o + 0xC) = (char *)&D_00000000 + 0xC5C4;
    c = (float *)(o + 0x4C);
    c[0] = (float)0x77 / 255.0f;
    c[1] = (float)0x75 / 255.0f;
    c[2] = (float)0xE5 / 255.0f;
    c[3] = 1.0f;
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);
#endif
