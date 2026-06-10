#include "common.h"

extern int func_00000000();
/* The FP literal pool func_0001016C reads is reached through the symbol splat
 * assigned to that reloc — func_00000C10 (module-offset 0xC10). Referencing it
 * as a float struct reproduces the exact `lui $at,%hi(func_00000C10+N);
 * lwc1 %lo(func_00000C10+N)($at)` loads byte-for-byte (same reloc the ROM has),
 * the same way placeholder calls reference splat-assigned symbols. */
extern struct { float f0, f1, f2; } func_00000C10;

/* -O0 sub-file split out of bootup_uso_tail1.c on 2026-05-14. Holds the
 * 0x100F0..0x1016B -O0 cluster: 100F0 (init+dispatch wrapper) + 1016C
 * (INCLUDE_ASM stub for layout contiguity; migrates to C body in future
 * pass when verified at -O0).
 *
 * Pattern: -O0 frame -0x28 with K&R-style arg-save (a0/a1 -> sp+0x28/0x2C)
 * and per-statement sp+0x1C reload of intermediate results. */

/* func_000100F0: 31-insn init+dispatch wrapper (-O0). Sets two struct fields,
 * calls a cross-USO helper, dispatches through a struct vtable, then writes
 * a float constant (17.0f).
 *
 * MATCH KEYS (re-matched 2026-06-10; the 2026-05-14 body was a FALSE MATCH
 * that landed during the land-script byte_verify regression — it emitted
 * 0x94 bytes vs the target 0x7C and shifted the whole segment +0x18):
 *  (1) `register int *p` — the vtable base lives in $s0 (only callee-saved
 *      reg in the frame: ra@0x1C, s0@0x18, frame 0x28);
 *  (2) the p-assignment is EMBEDDED in the call's argument expression —
 *      -O0 reloads a0 from its home slot per statement, but the target
 *      reuses one $t9 a0-load for both the p-load and the `addu a0,t0,t9`
 *      arg add, which only happens within a single expression tree;
 *  (3) arg order `*(short*)(p+0x60) + (int)a0` puts the lh result in the
 *      first addu operand. */
void func_000100F0(int *a0, int a1) {
    register int *p;
    *(int*)((char*)a0 + 0x2C) = a1;
    *(int*)((char*)a0 + 0x7C) = 0;
    func_00000000(a0);
    (**(void (**)())((char*)p + 0x64))(
        *(short*)((char*)(p = (int*)*(int*)((char*)a0 + 0x28)) + 0x60) + (int)a0);
    *(float*)((char*)a0 + 0x74) = 17.0f;
}

/* func_0001016C: -O0 FP-init for the a0->0x3C sub-struct (38 insns). MATCHED.
 *   a0->0x6C = 160.0f;
 *   a0->0x70 = 120.0f - (a0->0x74 / 2.0f) * (float)a0->0x78;
 *   a0->0x34 = 0xFF;  a0->0x38 = 0;
 *   { float *q = (float*)((char*)a0 + 0x3C);
 *     q[0..2] = func_00000C10.{f0,f1,f2}; q[3] = 0.0f; }
 *   func_00000000(a0);  func_00000000(a0);
 * Keys: `register float *q` keeps the a0+0x3C base in $s0; the division as the
 * LEFT mul operand matches IDO's f18*f10 order; the pool loads fold to
 * lui $at,%hi(func_00000C10+N); lwc1 %lo(func_00000C10+N)($at). */
void func_0001016C(int *a0) {
    register float *q;
    *(float*)((char*)a0 + 0x6C) = 160.0f;
    *(float*)((char*)a0 + 0x70) =
        120.0f - (*(float*)((char*)a0 + 0x74) / 2.0f) * (float)*(int*)((char*)a0 + 0x78);
    *(int*)((char*)a0 + 0x34) = 0xFF;
    *(int*)((char*)a0 + 0x38) = 0;
    q = (float*)((char*)a0 + 0x3C);
    q[0] = func_00000C10.f0;
    q[1] = func_00000C10.f1;
    q[2] = func_00000C10.f2;
    q[3] = 0.0f;
    func_00000000(a0);
    func_00000000(a0);
}
