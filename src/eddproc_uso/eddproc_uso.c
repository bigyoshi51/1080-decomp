#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_00000000);

void eddproc_uso_func_00000040(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void eddproc_uso_func_0000007C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void eddproc_uso_func_000000D4(Vec3 *dst) {
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
/* 3-insn save-args-to-caller-shadow-space stub (sw a0,0(sp); jr ra;
 * sw a1,4(sp)). No prologue, no body — stores to caller's a0/a1 O32
 * shadow space. Semantically `void f(int, int) {}` but IDO -O2 won't
 * produce these 3 insns (the stub doesn't even allocate a local frame).
 * Documented in the split-fragments commit chain as a variant of
 * feedback_ido_unfilled_store_return.md. */
void eddproc_uso_func_00000144(int a0, int a1) {
    (void)a0; (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_00000144);
#endif

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_00000150);

#ifdef NON_MATCHING
/* 5-call orchestrator with saved $s0=a0. Sets up 0xA0/0xA4 struct fields
 * plus two data-symbol stores (D_<eddproc>_B = retval of 4th call; +4 = 0).
 * 31 "real" insns + 2 stray `lui+lw` at 0x1E8/0x1EC past jr-ra (inside
 * declared size 0x94 — see feedback_uso_stray_trailing_insns.md: caps
 * match %, pad-sidecar may help). This pass: structure only — needs unique
 * D_eddproc_N extern symbols per call site (feedback_uso_multi_placeholder_wrapper.md)
 * and D_eddproc_220 data pointer. Deferred to future pass. */
void eddproc_uso_func_0000015C(char *a0) {
    extern int *D_eddproc_00000220;
    extern int D_eddproc_data_B;
    extern int D_eddproc_data_B4;
    *(int**)(a0 + 0xC) = &D_eddproc_00000220 + 0x88;  /* SYM+0x220 */
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0xD6, 0x13, *(char**)(a0 + 0x44) + 0x10);
    gl_func_00000000(a0, 0x6C, 0x11, (char*)a0 + 0xA0);
    *(int*)(a0 + 0xA0) = 0x2328;
    *(int*)(a0 + 0xA4) = 0;
    D_eddproc_data_B = gl_func_00000000(0x3E80);
    D_eddproc_data_B4 = 0;
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000015C);
#endif

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000001F0);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000025C);

void eddproc_uso_func_0000032C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    gl_func_00000000(dst + 0x10);
}

void eddproc_uso_func_0000035C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_00000040((float*)(dst + 0x10));
}

void eddproc_uso_func_0000038C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_0000007C((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000003BC);

INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000044C);

