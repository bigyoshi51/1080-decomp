#include "common.h"

extern int func_00000000();
/* Shared FP literal pool. splat misresolved this reloc to the .text symbol
 * func_00000C10 because the pool lives at the same module-offset (0xC10) in
 * .rodata. The honest target symbol is this pool, not the function's code. */
extern float D_FP_POOL_0C10[];

/* -O0 sub-file split out of bootup_uso_tail1.c on 2026-05-14. Holds the
 * 0x100F0..0x1016B -O0 cluster: 100F0 (init+dispatch wrapper) + 1016C
 * (INCLUDE_ASM stub for layout contiguity; migrates to C body in future
 * pass when verified at -O0).
 *
 * Pattern: -O0 frame -0x28 with K&R-style arg-save (a0/a1 -> sp+0x28/0x2C)
 * and per-statement sp+0x1C reload of intermediate results. */

/* func_000100F0: 31-insn init+dispatch wrapper. Sets two struct fields,
 * calls a cross-USO helper, dispatches through a struct vtable, then
 * writes a float constant.
 *
 *   a0->[0x2C] = a1;
 *   a0->[0x7C] = 0;
 *   func_00000000(a0);
 *   p = a0->[0x28];
 *   (*p->[0x64])(a0 + (short)p->[0x60]);
 *   *(float*)(a0->[0x74]) = 17.0f;
 *
 * Wait: the asm shows `*(float*)((char*)a0 + 0x74) = 17.0f`, not
 * `*(a0->[0x74]) = 17.0f`. Direct field write, not indirect. */
void func_000100F0(int *a0, int a1) {
    int *p;
    short adj;
    void (*fn)(int);
    *(int*)((char*)a0 + 0x2C) = a1;
    *(int*)((char*)a0 + 0x7C) = 0;
    func_00000000(a0);
    p = (int*)*(int*)((char*)a0 + 0x28);
    adj = *(short*)((char*)p + 0x60);
    fn = (void(*)(int))*(int*)((char*)p + 0x64);
    fn((int)a0 + adj);
    *(float*)((char*)a0 + 0x74) = 17.0f;
}

/* func_0001016C: -O0 FP-init for the a0->0x3C sub-struct (38 insns).
 *   a0->0x6C = 160.0f;
 *   a0->0x70 = 120.0f - (float)a0->0x78 * (a0->0x74 / 2.0f);
 *   a0->0x34 = 0xFF;  a0->0x38 = 0;
 *   { float *q = (float*)((char*)a0 + 0x3C);
 *     q[0] = pool[0]; q[1] = pool[1]; q[2] = pool[2]; q[3] = 0.0f; }
 *   func_00000000(a0);  func_00000000(a0);
 *
 * NM cap: q[0..2] load from a shared FP literal pool. The lwc1 %hi/%lo
 * reloc was misresolved by splat to the .text symbol func_00000C10 (same
 * module-offset 0xC10 in .rodata vs .text). Reproducing the exact pool
 * loads needs a .rodata pool symbol + shared-pool linker placement
 * (focused-session splat work, not tick-safe). The rest is byte-clean. */
#ifdef NON_MATCHING
void func_0001016C(int *a0) {
    float *q;
    *(float*)((char*)a0 + 0x6C) = 160.0f;
    *(float*)((char*)a0 + 0x70) =
        120.0f - (float)*(int*)((char*)a0 + 0x78) * (*(float*)((char*)a0 + 0x74) / 2.0f);
    *(int*)((char*)a0 + 0x34) = 0xFF;
    *(int*)((char*)a0 + 0x38) = 0;
    q = (float*)((char*)a0 + 0x3C);
    q[0] = D_FP_POOL_0C10[0];
    q[1] = D_FP_POOL_0C10[1];
    q[2] = D_FP_POOL_0C10[2];
    q[3] = 0.0f;
    func_00000000(a0);
    func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001016C);
#endif
