#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

/* K&R-style def: function name doubles as placeholder for unresolved
 * intra-USO jals elsewhere in the file (called with 1-arg sig at func_26D0).
 * K&R `()` decl + K&R def = no sig conflict. */
void titproc_uso_func_00000000()
{
    gl_func_00000000(&D_00000000, 4);
    gl_func_00000000(&D_00000000 + 0x18, 5);
    gl_func_00000000(&D_00000000 + 0x78, 2);
    gl_func_00000000(&D_00000000 + 0x90, 0);
    gl_func_00000000(&D_00000000 + 0x30, ((*(int*)&D_00000000 + 0x31) << 16) | 9);
    gl_func_00000000(&D_00000000 + 0x48, ((*(int*)&D_00000000 + 0x31) << 16) | 0xA);
}

void titproc_uso_func_00000098(void) {
    gl_func_00000000(&D_00000000 + 0x60, 1);
}

#ifdef NON_MATCHING
/* 51-insn / 0xCC titproc state-machine driver.
 *
 * Decoded structure:
 *   counter = D[0x6C/4] + 1;
 *   if (counter < 5) D[0x6C/4] = counter;
 *   else { D[0x6C/4] = 0; counter = 0; }
 *
 *   if (counter == 0) {                          // first sub-state
 *     v = gl_func(D[0x148/4] + 4);
 *     if (v != 2) D[0x6C/4] += 1;
 *     counter = D[0x6C/4];
 *   }
 *   if (counter == 1) {                          // second sub-state
 *     v = gl_func(D[0x148/4] + 4);
 *     if (v != 1) D[0x6C/4] += 1;
 *     counter = D[0x6C/4];
 *   }
 *   t2 = 4;                                       // delay-slot constant from
 *                                                ; bnel false-path
 *   D[0x40/4] = t2;                              // a fixed-flag store
 *   D[0x44/4] = D_table_a[counter];              // counter-indexed lookup
 *   return D_table_b[counter];                   // return value also indexed
 *
 * IDO scheduler hoists the initial `lui a1, 0; addiu a1, 0; lw t6, 0x6C(a1)`
 * BEFORE the prologue (offsets 0xC0..0xC8) — characteristic of -O2 aggressive
 * scheduling. Two indexed lookups at the tail use distinct table bases (t3
 * and v0 luis at 0x160 / 0x174).
 *
 * Logic-correct first-pass decode. Default build uses INCLUDE_ASM. Per
 * feedback_unique_extern_must_match_target_base_sharing.md, byte-match would
 * need 4-5 unique externs (one for the &D_0 reused as a1; two for the indexed
 * table bases; plus the call target). Deferred to next pass. */
extern char *D_titproc_C0_a;       /* a1 base (D[0x6C], D[0x148], D[0x40], D[0x44]) */
extern int D_titproc_C0_table_a[]; /* t3-base table */
extern int D_titproc_C0_table_b[]; /* v0-base table (return value) */

int titproc_uso_func_000000C0(void) {
    int counter;
    int v;

    counter = *(int*)((char*)&D_titproc_C0_a + 0x6C) + 1;
    if (counter < 5) {
        *(int*)((char*)&D_titproc_C0_a + 0x6C) = counter;
    } else {
        *(int*)((char*)&D_titproc_C0_a + 0x6C) = 0;
        counter = 0;
    }

    if (counter == 0) {
        v = gl_func_00000000(*(int*)((char*)&D_titproc_C0_a + 0x148) + 4);
        if (v != 2) {
            *(int*)((char*)&D_titproc_C0_a + 0x6C) =
                *(int*)((char*)&D_titproc_C0_a + 0x6C) + 1;
        }
        counter = *(int*)((char*)&D_titproc_C0_a + 0x6C);
    }
    if (counter == 1) {
        v = gl_func_00000000(*(int*)((char*)&D_titproc_C0_a + 0x148) + 4);
        if (v != 1) {
            *(int*)((char*)&D_titproc_C0_a + 0x6C) =
                *(int*)((char*)&D_titproc_C0_a + 0x6C) + 1;
        }
        counter = *(int*)((char*)&D_titproc_C0_a + 0x6C);
    }

    *(int*)((char*)&D_titproc_C0_a + 0x40) = 4;
    *(int*)((char*)&D_titproc_C0_a + 0x44) = D_titproc_C0_table_a[counter];
    return D_titproc_C0_table_b[counter];
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000000C0);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_000000C0_pad.s")

#ifdef NON_MATCHING
/* titproc_uso_func_00000194: 18-insn (0x48) state-setter taking arg pointer.
 * Sibling of 000001E4/00000230 (which use &D directly) but writes through
 * the a0 arg instead. Trailing 8 bytes (lui v0; addiu v0) at offset 0x1DC..
 * 0x1E0 inside this symbol are the stolen-prologue prefix for SUCCESSOR
 * func_000001E4 (which already has PROLOGUE_STEALS=8 in Makefile).
 *
 * To promote to exact match: write the 18-insn C body below + add
 * `titproc_uso_func_00000194_pad.s` containing the trailing 2 prologue
 * bytes (`lui v0, 0; addiu v0, v0, 0`) for 0x1E4, plus
 * `#pragma GLOBAL_ASM(...)` after this function. Per
 * feedback_pad_sidecar_unblocks_trailing_nops.md +
 * feedback_prologue_stolen_pad_sidecar_alternative.md.
 *
 * Default build uses INCLUDE_ASM which preserves the trailing 8 bytes that
 * 0x1E4's PROLOGUE_STEALS=8 expects to find at 0x1DC/0x1E0. */
void titproc_uso_func_00000194(int *a0) {
    int v1 = 3;
    *(int*)((char*)a0 + 0x34) = v1;
    *(int*)((char*)a0 + 0x40) = 0;
    *(int*)((char*)a0 + 0x13C) = v1;
    gl_func_00000000(0xC, 0);
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0xA8), -1, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000194);
#endif

extern char D_000001E4_A;

void titproc_uso_func_000001E4(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 4;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 1);
    gl_func_00000000(*(int*)((char*)&D_000001E4_A + 0xA8), -1, 0);
}

extern char D_00000230_A;

void titproc_uso_func_00000230(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 6;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 2);
    gl_func_00000000(*(int*)((char*)&D_00000230_A + 0xA8), -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000028C);

extern char D_000002D8_A;

/* Reverse-merge boundary: real function starts at 0x2D8 (splat put the
 * `lui $v0; addiu $v0` prologue 8 bytes earlier, attributed to 0x28C's
 * trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md. */
void titproc_uso_func_000002D8(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 2;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 4);
    gl_func_00000000(*(int*)((char*)&D_000002D8_A + 0xA8), -1, 0);
}

extern char D_0000032C_A;

/* Reverse-merge boundary: real function starts at 0x32C (splat put the
 * `lui $v0; addiu $v0` prologue 8 bytes earlier, attributed to 0x2E0's
 * trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md. */
void titproc_uso_func_0000032C(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 7;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 5);
    gl_func_00000000(*(int*)((char*)&D_0000032C_A + 0xA8), -1, 0);
}

extern char D_00000380_A;

/* Reverse-merge boundary fix: real function starts at 0x380 (splat put
 * the `lui $v0; addiu $v0` prologue 8 bytes earlier and attributed it to
 * 0x334's trailing bytes). Per feedback_splat_prologue_stolen_by_predecessor.md.
 * Signature is `void f(void)` — no args; $v0 = &D_00000000 via prologue. */
void titproc_uso_func_00000380(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 1;
    *(int*)((char*)&D_00000000 + 0x40) = 1;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(9);
    gl_func_00000000(*(int*)((char*)&D_00000380_A + 0xA8), -1, 0);
}

extern char D_000003D0_A;

void titproc_uso_func_000003D0(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 8;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x44) = 2;
    gl_func_00000000(*(int*)((char*)&D_000003D0_A + 0xA8), -1, 0);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000418);

void titproc_uso_func_0000049C(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void titproc_uso_func_000004D8(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void titproc_uso_func_00000514(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void titproc_uso_func_0000056C(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000005DC);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000B6C);

void titproc_uso_func_00000C0C(int *a0) {
    int v = *a0;
    if (v != 0) {
        gl_func_00000000(v, 3);
        *a0 = 0;
        *(int*)((char*)&D_00000000 + 0x14C) = 0;
    }
    *(int*)((char*)&D_00000000 + 0x168) = 0;
}

#ifdef NON_MATCHING
/* Constructor / orchestrator (223 insns, 0x37C). Allocates root object
 * (0x78 bytes) via gl_alloc(0x78), then:
 *   - sub-object 0x50: alloc(0x50) -> s0; alloc(0x2C) -> a0;
 *     calls a setup with &D_000004A8 as second arg (likely string label).
 *   - Sets s1->0x28 = D_NNNN (two D_ refs); s0->0x28 = D_NNNN.
 *   - Sets s1->0x28 again (overwrite or different field) + s1->0xC = D_NNNN+0x4B0.
 *   - jal_0(); s1->0x50 = v0; D_00000138 = v0.
 *   - Then a series of "alloc then bind" patterns for fields 0x54, 0x58,
 *     0x60, 0x64, 0x5C: alloc -> s0; if (s0->0x14 == 0) s0->0x4 = 1;
 *     s0->0x14 = s1; s1->fieldN = s0.
 *   - Indirect call: jalr t9 (vtable-style); arg0 = s0->0x58 + return.
 *   - Mid-function 0x40/0x3C setup with conditional check D_NNNN+0x88 != 0:
 *     uses arg1 (saved at sp+0x44) for some "rate" calc.
 *   - Final D_00000088 = 0; jal at end with arg0 = D_NNNN+0x000.
 *   - Returns s1.
 *
 * No exact match expected this pass — too many cross-USO calls + D_
 * placeholder relocations. NM wrap captures structure for future passes.
 * Documented field offsets: 0xC, 0x14, 0x28, 0x2C, 0x30, 0x38, 0x3C, 0x40,
 * 0x48, 0x50, 0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C, 0x70, 0x74. */
void titproc_uso_func_00000C54(int *a0, int a1) {
    int *root;
    int *sub;
    int *child;
    int t;

    if (a0 != 0) {
        root = a0;
    } else {
        root = (int*)gl_func_00000000(0x78);
        if (root == 0) goto end;
    }
    if (root != 0) {
        sub = (int*)gl_func_00000000(0x50);
        if (sub != 0) {
            child = (int*)gl_func_00000000(0x2C);
            if (child != 0) {
                gl_func_00000000(child, (char*)&D_00000000 + 0x4A8);
            }
            *(int*)((char*)sub + 0x28) = (int)&D_00000000;
        }
        *(int*)((char*)root + 0x28) = (int)&D_00000000;
    }
    *(int*)((char*)root + 0x28) = (int)&D_00000000;
    gl_func_00000000();
    *(int*)((char*)root + 0x0C) = (int)((char*)&D_00000000 + 0x4B0);
    gl_func_00000000(0);
    *(int*)((char*)root + 0x50) = 0; /* v0 of last call */
    *(int*)((char*)&D_00000000 + 0x138) = 0; /* same v0 */
    {
        int *s0;
        s0 = (int*)gl_func_00000000(*(int*)((char*)root + 0x50), root);
        t = *(int*)((char*)s0 + 0x14);
        if (t == 0) *(int*)((char*)s0 + 0x4) = 1;
        *(int*)((char*)s0 + 0x14) = (int)root;
        *(int*)((char*)root + 0x54) = (int)s0;
    }
    /* Pattern repeats for fields 0x58, 0x60, 0x64, 0x5C — each:
     *   gl_func_00000000(prev_s0_or_arg) -> new s0;
     *   if (s0->0x14 == 0) s0->0x4 = 1; s0->0x14 = root;
     *   root->fieldN = s0;
     * Indirect call inside via jalr t9. */
    {
        int *s0;
        int *v0;
        s0 = (int*)gl_func_00000000();
        if (s0 != 0) {
            v0 = (int*)*(int*)((char*)root + 0x54);
            v0 = (int*)*(int*)((char*)v0 + 0x28);
            ((void(*)(int))*(int*)((char*)v0 + 0x5C))(*(short*)((char*)v0 + 0x58));
        }
        gl_func_00000000(0);
        *(int*)((char*)root + 0x58) = 0;
    }
    /* ... (remaining 4 alloc-bind iterations for 0x60, 0x64, 0x5C and final
     * float setup with f4=17.0f — D_4188 = 0x41880000 = 17.0f). */
    *(int*)((char*)root + 0x40) = 0;
    *(int*)((char*)root + 0x3C) = 0;
    *(int*)((char*)root + 0x68) = 0;
    *(int*)((char*)&D_00000000 + 0x88) = 0;
    gl_func_00000000(&D_00000000, 0);
    *(int*)((char*)root + 0x2C) = 0;
    *(int*)((char*)root + 0x48) = 0;
    (void)a1;
end:
    return;
    /* return root; */
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000C54);
#endif

void titproc_uso_func_00000FD0(int *a0, int *a1) {
    int v = *a1;
    if (v == 0x15) {
        gl_func_00000000(a0);
        gl_func_00000000(a0);
    }
    gl_func_00000000(a0, a1);
}

extern int D_t_count_101C;
extern int D_t_target_101C;
extern int D_t_arg0_101C, D_t_arg1_101C, D_t_arg2_101C, D_t_arg3_101C, D_t_arg4_101C, D_t_arg5_101C, D_t_arg6_101C;
void titproc_uso_func_0000101C(int *a0) {
    gl_func_00000000(*(int*)((char*)a0 + 0x5C));
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 1, 0, &D_t_arg0_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 2, 1, &D_t_arg1_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 3, 2, &D_t_arg2_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 6, 3, &D_t_arg3_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 4, 4, &D_t_arg4_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 7, 5, &D_t_arg5_101C);
    gl_func_00000000(*(int*)((char*)a0 + 0x5C), ((D_t_count_101C + 1) << 16) | 5, 6, &D_t_arg6_101C);
    if (gl_func_00000000(*(int*)((char*)&D_t_target_101C + 0xC4)) == 0) {
        *(int*)((char*)*(int**)((char*)a0 + 0x5C) + 0x128) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000116C);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000015F4);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001718);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001840);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001950);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001B10);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001BB8);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001C68);

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001D7C);

extern int gl_func_00000000();
extern char D_00000000;

/* Reads a0->0x3C as a count/index, clamps to <0x100, dispatches:
 *   v = a0->0x3C; if (v >= 0x100) v = 0xFF; if (v == 0) return;
 *   func_00000000(&D_0, v, a0+0x2C);
 *   func_00000000(&D_0, 0, 0, 0x13F, 0xEF, 0x10001);  // 6-arg call
 * Cross-USO template — same body matches h2hproc_uso_func_00000F60 byte-
 * identical (per feedback_uso_accessor_template_reuse.md). */
void titproc_uso_func_00001E2C(char *a0) {
    int v = *(int*)(a0 + 0x3C);
    if (v >= 0x100) v = 0xFF;
    if (v == 0) return;
    gl_func_00000000(&D_00000000, v, a0 + 0x2C);
    gl_func_00000000(&D_00000000, 0, 0, 0x13F, 0xEF, 0x10001);
}

#ifdef NON_MATCHING
/* titproc_uso_func_00001E9C: 245-insn (0x3D4) titproc constructor.
 * Frame: -0x40 (0x40 stack frame). 3-arg constructor (a0, a1, a2)
 * spilled to caller slots at +0x44/+0x48/+0x4C.
 *
 * ENTRY DECODE (first ~10 insns @ 0x1E9C-0x1EC8):
 *   prologue: addiu sp,-0x40; sw ra,0x24; sw s0/s1,0x1C/0x20
 *   spill s1 = a0
 *   spill a1/a2/a3 to caller slots
 *   if (a0 == NULL) {
 *     a0 = alloc(0x6C8);             // bne a0,zero skips this
 *     if (a0 == NULL) goto end;      // beq v0,zero,+0xE3 (very far)
 *     s1 = v0;                        // s1 = alloc result
 *   }
 *   if (a1 != NULL) {                 // bne s1, zero, +5
 *     a1 = a1;
 *   } else {
 *     a1 = alloc(0x6A8);
 *     if (a1 == NULL) goto end;
 *     s0 = v0;
 *   }
 *   ...
 *
 * Multi-iter sub-allocator follows (~200+ insns of nested alloc+init).
 * Per project_1080_strategy.md: defer big constructors until structs
 * are typed. Multi-tick decomp expected. Stub body so wrap parses;
 * default build INCLUDE_ASM matches. */
void titproc_uso_func_00001E9C(void *a0, void *a1, void *a2) {
    /* TODO: 3-stage alloc-or-use entry (0x6C8 main, 0x6A8 child, ...);
     * ~200 insns of sub-alloc loop with template inits. */
    (void)a0; (void)a1; (void)a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001E9C);
#endif

void titproc_uso_func_00002270(int a0, int *a1) {
    int v = *a1;
    if (v == 0x15) {
        gl_func_00000000(a0);
        gl_func_00000000(a0);
    }
    gl_func_00000000(a0, a1);
}

#ifdef NON_MATCHING
/* titproc_uso_func_000022BC: 84-insn (0x150) per-frame init orchestrator.
 * Structural decode: ~7 iterations of setup-and-call pattern, each calling
 * gl_func(D[0x6C0], packed-a1, a2=N, a3=base) for N=0..6.
 *
 * Per-iter shape (decoded from 0x22D0-0x2310):
 *   a0 = D[0x6C0];
 *   s1 = &D + offset; a1 = *s1;
 *   a3 = &D + constant;
 *   a1 = ((a1+1) << 16) | low_bits;       // pack (count, flag)
 *   gl_func(a0_reload, a1, a2=N, a3);
 *
 * Tail (0x23E0-0x23F4):
 *   a0 = D[0xC4];
 *   if (a0 != 0) D[0x6C0]->0x128 = 0;     // bnel-likely + delay-slot store
 *
 * Likely a per-frame "submit N display lists, then reset slot 0x128".
 * Multi-tick decomp expected. Stub body so wrap parses; default build
 * matches via INCLUDE_ASM. */
void titproc_uso_func_000022BC(int a0) {
    int i;
    /* TODO: decode 7 iterations of indexed cross-USO call setup +
     * tail bnel-likely conditional store. */
    for (i = 0; i < 7; i++) {
        gl_func_00000000(*(int*)((char*)&D_00000000 + 0x6C0));
    }
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000022BC);
#endif

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000240C);

void titproc_uso_func_00000000();

void titproc_uso_func_000026D0(int *a0) {
    int *p = *(int**)((char*)a0 + 0x6C0);
    if (p == 0) return;
    titproc_uso_func_00000000(p);
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000026FC);

void titproc_uso_func_000028C0(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_0000049C((int*)(dst + 0x10));
}

void titproc_uso_func_000028F0(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_000004D8((float*)(dst + 0x10));
}

void titproc_uso_func_00002920(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_00000514((Quad4*)(dst + 0x10));
}

void titproc_uso_func_00002950(char *dst) {
    int tmp;
    titproc_uso_func_0000049C(&tmp);
    titproc_uso_func_0000056C((Vec3*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00002980);
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_00002980_pad.s")

