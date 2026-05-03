#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by the standard -O2 int-reader template body. The
 * trampoline word is injected post-cc via PREFIX_BYTES (see Makefile +
 * scripts/inject-prefix-bytes.py). */
void eddproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

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

void eddproc_uso_func_00000144(int a0, int a1) {
}

void eddproc_uso_func_00000150(int a0, int a1) {
}

extern int D_00000004;

void eddproc_uso_func_0000015C(char *a0) {
    *(char**)(a0 + 0xC) = &D_00000000 + 0x220;
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0xD6, 0x13, *(char**)(a0 + 0x44) + 0x10);
    gl_func_00000000(a0, 0x6C, 0x11, (char*)a0 + 0xA0);
    *(int*)(a0 + 0xA0) = 0x2328;
    *(int*)(a0 + 0xA4) = 0;
    *(int*)&D_00000000 = gl_func_00000000(0x3E80);
    D_00000004 = 0;
    gl_func_00000000(a0);
}

void eddproc_uso_func_000001E8(char *a0) {
    if (*(int*)(&D_00000000 + 0x74) == 0) {
        gl_func_00000000();
        gl_func_00000000(a0);
        if ((*(int*)(a0 + 0xA0) -= 0xA) < 0) {
            *(int*)(a0 + 0xA0) = 0;
        }
    }
    gl_func_00000000(a0);
    gl_func_00000000(*(int*)(a0 + 0x84), *(int*)(a0 + 0xA0), 1);
    gl_func_00000000(a0);
}

#ifdef NON_MATCHING
/* Multi-stage allocator/initializer (50 insns, 0xC8). Pattern:
 *
 *   T* f(T *a0, T *a1) {
 *       T *p1 = a0;
 *       T *p2, *p3;
 *
 *       if (p1 == 0) {                     // a0 == 0: try first alloc
 *           p1 = gl_func_00000000(0x54);
 *           if (p1 == 0) return 0;         // alloc failed
 *       }
 *
 *       p2 = gl_func_00000000(0x50, p1, a1);  // alloc+link second
 *       if (p2 == 0) goto FINAL_P1;
 *
 *       p3 = gl_func_00000000(0x2C);       // alloc third
 *       if (p3 != 0) {
 *           gl_func_00000000(p3, &D_22C);  // init p3 from data table
 *           p3->0x28 = &D_0;
 *       }
 *       p2->0x28 = &D_0;                   // (only when p3 alloc reached)
 *
 *   FINAL_P1:
 *       p1->0x28 = &D_0;
 *       return p1;
 *   }
 *
 * Quirk: a1 is spilled to caller-arg-slot at sp+0x24 but never reloaded
 * (dead spill — IDO preserves it via the convention without reading back).
 * The 3 alloc stages each have an early-out branch.
 *
 * Multi-tick decomp: matching the exact branch nesting + 3 spill-slot
 * pattern requires careful arrangement of the 3 conditional alloc paths.
 * Stub body documented; default build INCLUDE_ASM matches.
 *
 * (current: 61.26 %, 2026-05-02). Attempted variations:
 *   - `int *` return: 59.66 % (added load+return overhead, regressed)
 *   - Ternary `(p1 != 0) ? call : 0` w/ goto chain: 52.02 % (added bne
 *     guards but wrong delay-slot fills)
 *   - Mutate a0 in-place vs `int *p1 = a0`: 60.44 % (no real diff)
 *   - 2026-05-02: alloc-or-init goto pattern (per
 *     feedback_alloc_or_init_goto_pattern.md) applied to all 3 stages:
 *     58.92 % (regressed — pattern works for SINGLE alloc-then-init,
 *     not for multi-stage with branched init blocks). Goto only on
 *     stage 1 + if-else for stages 2-3: 60.44 %. The memo's recipe
 *     is single-stage only.
 *
 * Target's structure has TWO defensive null checks (a2 != 0, v1 != 0)
 * that branch over the next jal — these are dead code in normal flow
 * (a2 is provably non-zero at that point) but IDO emits them anyway.
 * Probably came from `p2 = (p1 != 0) ? call(p1) : 0` style ternaries
 * in the source, which IDO evaluates as bne+delay+call instead of just
 * call. Frame size diff: target 0x20 (3 spill slots: 0x18/0x1C/0x20),
 * mine 0x28 (over-allocates). Bigger structural rework likely required. */
void eddproc_uso_func_0000025C(int *a0, int *a1) {
    int *p1 = a0;
    int *p2;
    int *p3;
    if (p1 == 0) {
        p1 = (int*)gl_func_00000000(0x54);
        if (p1 == 0) return;
    }
    p2 = (int*)gl_func_00000000(0x50, p1, a1);
    if (p2 != 0) {
        p3 = (int*)gl_func_00000000(0x2C);
        if (p3 != 0) {
            gl_func_00000000(p3, (char*)&D_00000000 + 0x22C);
            *(int*)((char*)p3 + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)p2 + 0x28) = (int)&D_00000000;
    }
    *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_0000025C);
#endif

void eddproc_uso_func_00000324(int a0) {
}

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

#ifdef NON_MATCHING
/* eddproc_uso_func_000003BC: 36-insn (0x90) constructor-like — alloc 0x40,
 * init via gl_func, set fields at +0x28 and +0x3C, then optional 2nd init
 * if arg0->0x40 is non-null.
 *
 * Decoded structure (insns 0x3BC-0x420):
 *   void *p = gl_func_00000000(0x40);    // alloc
 *   if (p != NULL) {
 *     gl_func_00000000(p);                // init(alloc)
 *     p->field_28 = &D_00000000;
 *     p->field_3C = 0;
 *     if (arg0->field_40 != NULL) {
 *       gl_func_00000000(p + 0x10, arg0->field_40);  // sub-init
 *       // remaining ~10 insns: more field setup, return p
 *     }
 *   }
 *
 * ~50% NM body; alloc+init structure correct, but matching exact register
 * spill patterns (sw v0, 0x1C(sp); sw v1, 0x24(sp)) and the lui/addiu
 * pair for &D_00000000 needs careful ordering. Deferred to future tick. */
void eddproc_uso_func_000003BC(int *arg0) {
    void *p = (void*)gl_func_00000000(0x40);
    if (p != NULL) {
        gl_func_00000000(p);
        *(int*)((char*)p + 0x28) = (int)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
        if (arg0[0x40 / 4] != 0) {
            gl_func_00000000((char*)p + 0x10, arg0[0x40 / 4]);
            /* TODO: ~10 more insns of field setup at offsets 0x?? */
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso", eddproc_uso_func_000003BC);
#endif

void eddproc_uso_func_0000044C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_000000D4((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso/eddproc_uso_func_0000044C_pad.s")

