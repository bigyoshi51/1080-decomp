#include "common.h"

extern int func_00000000();

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001016C);
