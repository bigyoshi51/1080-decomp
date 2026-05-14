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

extern char D_titproc_C0_a;       /* a1 base (D[0x6C], D[0x148], D[0x40], D[0x44]) */
extern int D_titproc_C0_table_a[]; /* t3-base table */
extern int D_titproc_C0_table_b[]; /* v0-base table (return value) */

int titproc_uso_func_000000C0(void) {
    int counter;
    int v;

    counter = *(int*)((char*)&D_titproc_C0_a + 0x6C) + 1;
    *(int*)((char*)&D_titproc_C0_a + 0x6C) = counter;
    if (counter >= 5) {
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
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_000000C0_pad.s")

extern char D_00000194_A;
/* State-setter sibling of 000001E4/00000230/0000028C. Combines:
 *   - PROLOGUE_STEALS=8: splice IDO's auto-emitted &D prologue from the
 *     start (the &D setup actually lives in 0xC0_pad.s, emitted by
 *     predecessor 0xC0).
 *   - SUFFIX_BYTES: append the 8 dead `lui v0; addiu v0` bytes at the tail
 *     (these belong to 0x194's symbol but act as the stolen prologue setup
 *     that successor 0x1E4 inherits).
 * Per feedback_prologue_stolen_predecessor_no_recipe.md (the recipe this
 * tick built scripts/inject-suffix-bytes.py for). */
void titproc_uso_func_00000194(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 3;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(0xC, 0);
    gl_func_00000000(*(int*)((char*)&D_00000194_A + 0xA8), -1, 0);
}

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

extern char D_0000028C_A;

void titproc_uso_func_0000028C(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 5;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(12, 3);
    gl_func_00000000(*(int*)((char*)&D_0000028C_A + 0xA8), -1, 0);
}

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

#ifdef NON_MATCHING
/* titproc_uso_func_00000418: 33-insn FP selector + scaled return.
 *
 * D[0x154] is a pointer to a u16 mask. The target loads the pointer before
 * the stack prologue, then keeps the u16 mask in v1 for the loop. For each
 * set low bit, a1 becomes the 1-based bit index; after the loop it calls
 * gl_func_00000000(8), treats f0 as the float return, and scales by a1 - 2.
 *
 * Remaining mismatch (~16 reg-alloc diffs): target uses $t6 for D[0x154]
 * pointer + frame -0x20 + sp+0x18 spill slot; built uses $a0 + frame -0x28
 * + sp+0x1C spill. NOT a pure address-shift artifact — the body has real
 * register-allocation diffs that need permuter or specific temp/decl
 * arrangement to coerce IDO into using $t6 first.
 * The target also consumes gl_func_00000000(8)'s float return directly from f0.
 * Tested 2026-05-08: `((float (*)())gl_func_00000000)(8)` / typedef forms
 * do use f0, but IDO lowers them to indirect jalr through t9, regressing the
 * direct jal shape. The plain direct call keeps jal 0 but forces int->float.
 *
 * 2026-05-08: NOT promoted by upstream C0 byte-shift fix — the diffs are
 * intrinsic body diffs, not address-relative. */
int titproc_uso_func_00000418(void) {
    unsigned short *mask_ptr = *(unsigned short**)((char*)&D_00000000 + 0x154);
    int index;
    int selected;
    float result;

    index = 0;
    do {
        if ((*mask_ptr & (1 << index)) != 0) {
            selected = index + 1;
        }
        index++;
    } while (index != 8);

    selected -= 2;
    result = (float)gl_func_00000000(8);
    return (int)((result * (float)selected) + 2.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00000418);
#endif

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

/* titproc_uso_func_00000B6C: 40-insn (0xA0) 3-call alloc-and-link wrapper.
 * 1st cross-USO call allocates context (kept across calls), 2nd registers
 * via globals, 3rd cleans up the temporary. Inlining (*a0) twice in the
 * if-block (vs caching to a local p) is what commits IDO to keeping the
 * int** in $v1 — the cached form let IDO pick $t0 instead. */
void titproc_uso_func_00000B6C(int **a0, int a1) {
    int *r1;
    int *r2;
    r1 = gl_func_00000000(2);
    r2 = gl_func_00000000(0, *(int*)((char*)&D_00000000 + 0x148), a1, -1);
    *a0 = r2;
    *(int**)((char*)&D_00000000 + 0x14C) = r2;
    gl_func_00000000(r1);
    (*a0)[5] = 0;
    if (a1 != -1) {
        *(int*)((char*)&D_00000000 + 0x168) = ((int*)((*a0)[2]))[2];
        *(int*)((char*)&D_00000000 + 0x170) = ((int*)((*a0)[2]))[1];
    }
}

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
/* Constructor / orchestrator (223 insns, 0x37C). Allocates or accepts a
 * 0x78-byte root object, initializes the template/vtable fields, chains
 * children through root+0x10, and stores the constructed root in v0.
 *
 * 2026-05-08 NM-cap detail: with predecessor C0 fixed to use unconditional-
 * store-then-overwrite, C54 hovers at 90.03% as a real C body. Frame is
 * 0x48 (built) vs 0x40 (target). Earlier doc-claims that the 86.58% was a
 * pure address-shift artifact were wrong — the body itself does have ~22
 * register-allocation diffs that need permuter or multi-tick grinding.
 * Documented field offsets: 0xC, 0x14, 0x28, 0x2C, 0x30, 0x38, 0x3C, 0x40,
 * 0x48, 0x50, 0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C, 0x70, 0x74, 0x7C. */
void *titproc_uso_func_00000C54(int *a0, int a1) {
    int *root;
    int *sub;
    int *child;
    int *link;
    int *vtable;
    int count;

    root = a0;
    if (root == 0) {
        root = (int*)gl_func_00000000(0x78);
        if (root == 0) goto end;
    }
    if (root == 0) {
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
    *(int*)((char*)root + 0x0C) = (int)((char*)&D_00000000 + 0x4B0);
    gl_func_00000000();
    gl_func_00000000();
    *(int*)((char*)root + 0x50) = (int)gl_func_00000000(0);
    *(int*)((char*)&D_00000000 + 0x138) = *(int*)((char*)root + 0x50);

    gl_func_00000000(*(int*)((char*)root + 0x50));
    link = (int*)((char*)root + 0x10);

    sub = *(int**)((char*)root + 0x50);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    *(int*)((char*)root + 0x54) = (int)gl_func_00000000(0);

    sub = *(int**)((char*)root + 0x54);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    if (*(int*)((char*)&D_00000000 + 0x18C) != 0) {
        child = *(int**)((char*)root + 0x54);
        vtable = *(int**)((char*)child + 0x28);
        ((void(*)(int))*(int*)((char*)vtable + 0x5C))(
            *(short*)((char*)vtable + 0x58) + (int)child);
    }
    *(int*)((char*)root + 0x58) = (int)gl_func_00000000(0);

    sub = *(int**)((char*)root + 0x58);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    *(int*)((char*)root + 0x60) = (int)gl_func_00000000(0);

    sub = *(int**)((char*)root + 0x60);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    *(int*)((char*)root + 0x64) = (int)gl_func_00000000(0);

    sub = *(int**)((char*)root + 0x64);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    *(int*)((char*)root + 0x5C) = (int)gl_func_00000000(0);

    gl_func_00000000(*(int*)((char*)root + 0x5C), root);
    gl_func_00000000(root);
    *(int*)((char*)*(int**)((char*)root + 0x5C) + 0x30) =
        gl_func_00000000(0, &D_00000000, 0x48, 0xDD, 3, 0xD);
    *(float*)((char*)*(int**)((char*)root + 0x5C) + 0x74) = 17.0f;
    gl_func_00000000(*(int*)((char*)root + 0x5C));
    gl_func_00000000(*(int*)((char*)root + 0x5C));
    *(int*)((char*)*(int**)((char*)root + 0x5C) + 0x7C) =
        *(int*)((char*)&D_00000000 + 0x84);

    sub = *(int**)((char*)root + 0x5C);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;

    sub = *(int**)((char*)&D_00000000 + 0x190);
    gl_func_00000000(link, sub);
    if (*(int*)((char*)sub + 0x14) != 0) *(int*)((char*)sub + 0x4) = 1;
    *(int*)((char*)sub + 0x14) = (int)root;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190), 1, 0);

    *(int*)((char*)root + 0x6C) = 5;
    *(int*)((char*)root + 0x70) = 0x48;
    *(int*)((char*)root + 0x74) = 15000;
    count = *(volatile int*)((char*)root + 0x6C);

    if (*(int*)((char*)&D_00000000 + 0x88) != 0) {
        *(int*)((char*)root + 0x40) = 0;
        *(int*)((char*)root + 0x3C) = ((count << 4) - count) * 2;
    } else {
        *(int*)((char*)root + 0x40) = 1;
        *(int*)((char*)root + 0x3C) =
            ((*(int*)((char*)root + 0x70) << 4) - *(int*)((char*)root + 0x70)) * 2;
        *(int*)((char*)root + 0x68) = 0;
        *(int*)((char*)*(int**)((char*)root + 0x58) + 0x38) = 1;
        *(int*)((char*)*(int**)((char*)root + 0x58) + 0x2C) = 0;
        child = *(int**)((char*)root + 0x58);
        vtable = *(int**)((char*)child + 0x28);
        ((void(*)(int))*(int*)((char*)vtable + 0x5C))(
            *(short*)((char*)vtable + 0x58) + (int)child);
    }

    *(int*)((char*)&D_00000000 + 0x88) = 0;
    gl_func_00000000(&D_00000000, 0);
    *(int*)((char*)root + 0x2C) = 0;
    *(int*)((char*)root + 0x48) = 0;
    (void)a1;
end:
    return root;
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

#ifdef NON_MATCHING
/* titproc_uso_func_00001840: 68-insn (0x110) 2-cascade constructor with
 * 11-int + 4-float constant spray. Allocates main 0x74-byte object,
 * runs init helper from &D_0 + 0x4D8, sets vtable + 11 int field
 * constants (255, 163, 154, 67, 44, 1, -57, 28, 17, -3, 33) at offsets
 * 0x2C..0x70, plus 4 floats (1.0f x3, 0.0f) at 0x3C..0x48.
 *
 * Initial structural pass; default INCLUDE_ASM keeps ROM exact. */
void *titproc_uso_func_00001840(void *a0) {
    char *base = &D_00000000;
    void *self = a0;
    if (self == 0) {
        self = (void*)gl_func_00000000(0x74);
        if (self == 0) return self;
    }
    if (self == 0) {  /* dead-arm passthrough cascade */
        self = (void*)gl_func_00000000(0x2C);
        if (self == 0) return self;
    }
    gl_func_00000000(self, base + 0x4D8);
    *(int*)((char*)self + 0x28) = (int)base;
    *(int*)((char*)self + 0x28) = (int)base;
    *(int*)((char*)self + 0x0C) = (int)(base + 0x4E0);
    *(int*)((char*)self + 0x4C) = 163;
    *(int*)((char*)self + 0x50) = 154;
    *(int*)((char*)self + 0x6C) = 67;
    *(int*)((char*)self + 0x70) = 44;
    *(int*)((char*)self + 0x54) = 1;
    *(int*)((char*)self + 0x58) = -57;
    *(int*)((char*)self + 0x5C) = 28;
    *(int*)((char*)self + 0x60) = 17;
    *(int*)((char*)self + 0x64) = -3;
    *(int*)((char*)self + 0x68) = 33;
    *(int*)((char*)self + 0x2C) = 255;
    *(int*)((char*)self + 0x30) = 255;
    *(float*)((char*)self + 0x3C) = 1.0f;
    *(float*)((char*)self + 0x40) = 1.0f;
    *(float*)((char*)self + 0x44) = 1.0f;
    *(float*)((char*)self + 0x48) = 0.0f;
    gl_func_00000000(self);
    gl_func_00000000(self);
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001840);
#endif

INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001950);

#ifdef NON_MATCHING
/* titproc_uso_func_00001B10: 42-insn (0xA8) 3-stage chained alloc-cascade.
 * Same shape as eddproc_uso_func_0000025C and timproc_uso_b5_func_00000058
 * — gets/allocs primary obj (size 0x40), then init-call into +0x4EC
 * sub-block, then stores D_X pointers at +0x28 / +0xC / +0x3C of stages.
 *
 * Initial structural decode (multi-tick — this class caps at ~60% from
 * frame-size mismatch per the eddproc/0x25C documented blocker).
 * 2026-05-08: NOT promoted by upstream C0 byte-shift fix — body is
 * structurally different (51.93% fuzzy, 44 reg-alloc diffs in built).
 * Default INCLUDE_ASM matches; wrap captures structure for grep + typing.
 *
 * 2026-05-14: restructure — replaced `if (p2 == 0) return 0;` with
 * `if (p2 != 0) { ... }` inner-guard (target falls through to body with
 * p2 = 0 when p2-alloc fails; the body uses *p2 only inside the
 * conditional). Combined with goto-end form for p1-alloc-fail. Pushed
 * 51.93% → 73.40% (+21.47pp). Remaining caps: target has a redundant
 * `bne a2, 0` check that suggests original C had `if (p1 != 0) { ... }`
 * around the p2-init body, and p2 holds in $a3 (target) vs $a3/$a0
 * cascade (built). */
void *titproc_uso_func_00001B10(void *a0, void *a1) {
    void *p1;
    void *p2;
    p1 = a0;
    if (p1 == 0) p1 = (void*)gl_func_00000000(0x40);
    if (p1 == 0) goto end;
    p2 = a1;
    if (p2 == 0) p2 = (void*)gl_func_00000000(0x2C);
    if (p2 != 0) {
        gl_func_00000000(p2, (char*)&D_00000000 + 0x4EC);
        *(int*)((char*)p2 + 0x28) = (int)&D_00000000;
    }
    *(int*)((char*)p1 + 0x28) = (int)((char*)&D_00000000 + 0x4F4);
    *(int*)((char*)p1 + 0xC)  = (int)((char*)&D_00000000 + 0x4F4);
    gl_func_00000000(p1, p2);
    *(int*)((char*)p1 + 0x3C) = 0;
end:
    return p1;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001B10);
#endif

/* titproc_uso_func_00001BB8: 42-insn dual-state-bracket helper. Two
 * gl_func dispatches with asymmetric inner-D[0] gates.
 *
 * Trailing bundled bytes 0xA8-0xAF are the SUCCESSOR (0x1C68) stolen
 * prologue: `lui $at, 0x3F80; mtc1 $at, $f0` ($f0=1.0f setup that 0x1C68
 * stores via `swc1 $f0, 0x30(sp)` immediately after its prologue). Handled
 * via SUFFIX_BYTES + scripts/inject-suffix-bytes.py.
 *
 * Each lui+addiu/lw pair in the target is a distinct R_MIPS_HI16/LO16
 * reloc — 8 fresh loads of `&D_*` rather than CSE through $s0. To match,
 * 8 distinct externs (`D_titproc_BB8_a..h`) all aliased to 0 in
 * undefined_syms_auto.txt. Per
 * feedback_unique_extern_with_offset_cast_breaks_cse.md.
 *
 * Promoted to exact 2026-05-08 once predecessor C0 was fixed (upstream
 * byte-shift cascade). See docs/MATCHING_WORKFLOW.md
 * #feedback-upstream-byte-shift-cascade. */
extern int gl_func_00000000();
extern char D_titproc_BB8_a, D_titproc_BB8_b, D_titproc_BB8_c, D_titproc_BB8_d;
extern char D_titproc_BB8_e, D_titproc_BB8_f, D_titproc_BB8_g, D_titproc_BB8_h;
void titproc_uso_func_00001BB8(int a0) {
    if (gl_func_00000000(&D_titproc_BB8_a, 0x10001) != 0) {
        if (*(int*)&D_titproc_BB8_b != 0) {
            gl_func_00000000(1);
            gl_func_00000000(&D_titproc_BB8_d, *(int*)&D_titproc_BB8_c ^ 1);
        }
    }
    if (gl_func_00000000(&D_titproc_BB8_e, 0x4002) != 0) {
        if (*(int*)&D_titproc_BB8_f == 0) {
            gl_func_00000000(1);
            gl_func_00000000(&D_titproc_BB8_h, *(int*)&D_titproc_BB8_g ^ 1);
        }
    }
}

/* titproc_uso_func_00001C68: 69-insn (0x114) dual-dispatch FPU helper.
 * Sibling of 0x1BB8 (which provides the stolen-prologue $f0 = 1.0f).
 *
 * 10 unique externs (D_titproc_C68_A1..A4 + B + D + C1..C4) at 0x0 break
 * IDO's &D-base CSE: each site emits fresh lui+addiu/lw with its own
 * R_MIPS_HI16/LO16 reloc pair, matching target's per-site fresh-load shape.
 * Per feedback_unique_extern_with_offset_cast_breaks_cse.md.
 *
 * Asymmetric inner gates (first dispatch enters body when D==0; second when
 * D!=0) — same save/restore-state pattern as 0x1BB8.
 *
 * Promoted to exact 2026-05-08 once predecessor C0 was fixed (upstream
 * byte-shift cascade). See docs/MATCHING_WORKFLOW.md
 * #feedback-upstream-byte-shift-cascade. */
extern int gl_func_00000000();
extern char D_titproc_C68_A1, D_titproc_C68_A2, D_titproc_C68_A3, D_titproc_C68_A4;
extern char D_titproc_C68_C1, D_titproc_C68_C2, D_titproc_C68_C3, D_titproc_C68_C4;
extern int D_titproc_C68_B, D_titproc_C68_D;
void titproc_uso_func_00001C68(int *a0) {
    float buf[4];
    char pad[24];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    a0[0x3C / 4] -= 0x10;
    gl_func_00000000(&D_titproc_C68_A1 + 0x30);
    if (D_titproc_C68_B == 0) {
        gl_func_00000000(&D_titproc_C68_A3 + 0x30, a0[0x3C / 4], &buf, 0xFF);
    } else {
        gl_func_00000000(&D_titproc_C68_A2 + 0x30, 0x80, &buf, 0xFF);
    }
    gl_func_00000000(&D_titproc_C68_A4 + 0x30, 0x5A, 0x7E, 3);
    gl_func_00000000(&D_titproc_C68_C1 + 0x48);
    if (D_titproc_C68_D != 0) {
        gl_func_00000000(&D_titproc_C68_C3 + 0x48, a0[0x3C / 4], &buf, 0xFF);
    } else {
        gl_func_00000000(&D_titproc_C68_C2 + 0x48, 0x80, &buf, 0xFF);
    }
    gl_func_00000000(&D_titproc_C68_C4 + 0x48, 0xDC, 0x7E, 3);
    (void)pad;
}

#ifdef NON_MATCHING
/* titproc_uso_func_00001D7C: 44-insn (0xB0) 2-cascade ctor + 4 floats=1.0f.
 * Sibling of 1840: alloc(0x40) + dead-arm alloc(0x2C), init from
 * &D_0+0x500, vtable, 4 floats=1.0f at +0x2C..0x38, zero at +0x3C.
 *
 * Initial structural pass; default INCLUDE_ASM keeps ROM exact. */
void *titproc_uso_func_00001D7C(void *a0) {
    char *base = &D_00000000;
    void *self = a0;
    if (self == 0) {
        self = (void*)gl_func_00000000(0x40);
        if (self == 0) return self;
    }
    if (self == 0) {  /* dead-arm passthrough cascade */
        self = (void*)gl_func_00000000(0x2C);
        if (self == 0) return self;
    }
    gl_func_00000000(self, base + 0x500);
    *(int*)((char*)self + 0x28) = (int)base;
    *(int*)((char*)self + 0x28) = (int)base;
    *(int*)((char*)self + 0x0C) = (int)(base + 0x508);
    *(int*)((char*)self + 0x3C) = 0;
    *(float*)((char*)self + 0x2C) = 1.0f;
    *(float*)((char*)self + 0x30) = 1.0f;
    *(float*)((char*)self + 0x34) = 1.0f;
    *(float*)((char*)self + 0x38) = 1.0f;
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001D7C);
#endif

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
/* titproc_uso_func_00001E9C: 245-insn titproc constructor for ~0x6C8-byte object.
 *
 * Frame: -0x40, saves ra/s0/s1, spills a1/a2/a3 to caller slots at +0x44/+0x48/+0x4C.
 *
 * STRUCTURE (decoded ~120/245 insns):
 *
 *   p = a0 ?: alloc(0x6C8); if (!p) goto end;            // s1 = p
 *   q = p;  if (!q) { q = alloc(0x6A8); if (!q) goto end; }  // s0 = q (dead alloc path)
 *   r = q;  if (!r) { r = alloc(0x50);  if (!r) goto end; }  // v1 = r (dead alloc path)
 *   sub = alloc(0x2C);                                    // sp+0x38
 *   if (sub != NULL) {
 *     gl_func_00000000(sub, &D + 0x514);                  // init sub at template
 *     spill_v1 = sub  (sp+0x34)
 *     p->0x28 = &D_00000000;
 *     ((void*)p)->0x28 = &D + 0;                          // p[10] = &D
 *     p->0x28 = sub;                                      // overrides — multi-write
 *     gl_func_00000000(p + 0x50);                         // init p+0x50
 *     p->0x28 = &D + 0;
 *     p->0x568 = 0;
 *     gl_func_00000000(&D + 0x51C, *(int*)(sp+0x44)=a1, *(int*)(sp+0x48)=a2, p);
 *     p->0x528 = (gl_func ret);
 *     gl_func_00000000(&D + 0x530, 0);                    // 2nd cross-call
 *     gl_func_00000000(&D + 0,    0);                     // 3rd
 *     gl_func_00000000(0);                                // 4th
 *     p->0x6AC = (last gl_func ret val from sub-call set);
 *     D[0x138] = p->0x6AC;                                // global flag
 *     gl_func_00000000(p->0x6AC);
 *
 *     // SUB-LOOP (insns ~0x1FD8-0x2018, ~16 insns):
 *     spill_a4 = p->0x6AC + 0x10  (sp+0x2C)
 *     do {
 *       gl_func_00000000(p->0x6AC + 0x10, p);
 *       cnt = sub->0x14;
 *       if (cnt == 0) sub->0x4 = 1;                       // first-time flag
 *       sub->0x14 = s1 (= p);                             // back-pointer
 *       gl_func_00000000(*(int*)(sp+0x44)=a1);
 *       p->0x48 = a1_save;                                // 2 stores for outgoing arg
 *       p->0x4F4 = (a1 & 0xFFFF);                         // low-half of a1
 *       a1_high = (a1 >> 16) << 7                         // sll-srl shuffle
 *       if (a1_high < ?) p->0x6B4 = ?
 *       gl_func_00000000(0);
 *       p->0x6B0 = (gl_func ret val);
 *       sub2 = p->0x6B0->0x28;
 *       fn  = sub2->0x5C;
 *       arg = (int)(p->0x6B0) + (short)sub2->0x58;        // signed-short adjust
 *       fn(arg);
 *       sub3 = p->0x6B0;                                  // reload after call
 *       gl_func_00000000(p->0x6AC + 0x10, p);             // 2nd subobj init
 *       cnt = sub->0x14;
 *       if (cnt == 0) sub->0x4 = 1;
 *       sub->0x14 = p;
 *     } while (...);                                       // (TODO: terminator unclear)
 *
 *   // EPILOGUE (0x225C-0x226C):
 *   end:
 *     return s1;                                           // returns p
 *   }
 *
 * Quirks:
 *   - Multi-write to p->0x28: 3 distinct &D-derived addresses overwrite each
 *     other (looks like compiler initializing same field at different decoder
 *     stages — possibly union or struct-fill via `*(int*)(p+0x28) = ...`).
 *   - Sub-loop has 2 alloc-or-init blocks (sub at +0x10 and at base) — looks
 *     like double-buffering setup.
 *   - "(a1 & 0xFFFF) | shifted-bits-stored-at-+0x4F4" pattern is per-frame
 *     coordinate packing (sll/srl shuffle on a1 at insns 0x2010-0x202C).
 *
 * Identified field offsets (for future struct-typing):
 *   p->0x28: parent template ptr (multi-write)
 *   p->0x48: saved a1 ptr (caller-supplied parent)
 *   p->0x4F4: packed low-half of caller-arg
 *   p->0x528: gl_func return (sub-init-A)
 *   p->0x568: zeroed flag
 *   p->0x6AC: gl_func return (sub-init-B; primary inner pointer)
 *   p->0x6B0: gl_func return (sub-init-C; secondary inner pointer)
 *   p->0x6B4: conditional value
 *   p->0x6B8/0x6BC/0x6C0/0x6C4: more inner ptrs from later jal returns
 *
 * Default build INCLUDE_ASM matches. C body below covers the ~50% of insns
 * with the highest structural confidence; remaining ~120 insns of the
 * sub-loop tail are stubbed as TODO. */
extern void *titproc_uso_func_00001E9C_TODO_loop(void *p, void *sub, void *a1, void *a2, void *a3);
void *titproc_uso_func_00001E9C(void *a0, void *a1, void *a2, void *a3) {
    void *p, *q, *r, *sub;

    /* Stage 1: alloc main 0x6C8 if a0 == NULL */
    p = a0;
    if (p == NULL) {
        p = (void*)gl_func_00000000(0x6C8);
        if (p == NULL) goto end;
    }

    /* Stage 2 (dead-path alloc compiled in source): if (q == NULL) alloc(0x6A8) */
    q = p;
    if (q == NULL) {
        q = (void*)gl_func_00000000(0x6A8);
        if (q == NULL) goto end;
    }

    /* Stage 3 (dead-path): if (r == NULL) alloc(0x50) */
    r = q;
    if (r == NULL) {
        r = (void*)gl_func_00000000(0x50);
        if (r == NULL) goto end;
    }

    /* Sub-init stage: alloc 0x2C sub-struct */
    sub = (void*)gl_func_00000000(0x2C);
    if (sub != NULL) {
        gl_func_00000000(sub, (char*)&D_00000000 + 0x514);
        *(int*)((char*)p + 0x28) = (int)&D_00000000;
        *(int*)((char*)p + 0x28) = (int)((char*)&D_00000000 + 0);  /* multi-write */
        *(int*)((char*)p + 0x28) = (int)sub;
        gl_func_00000000((char*)p + 0x50);

        /* Cross-USO init chain — produces ptrs stored at p->0x528/0x6AC */
        *(int*)((char*)p + 0x528) = gl_func_00000000(
            (char*)&D_00000000 + 0x51C, a1, a2, p);
        gl_func_00000000((char*)&D_00000000 + 0x530, 0);
        gl_func_00000000(&D_00000000, 0);
        gl_func_00000000(0);
        *(int*)((char*)p + 0x6AC) = (int)q;       /* p->0x6AC = inner ptr */
        *(int*)((char*)&D_00000000 + 0x138) = (int)q;  /* global flag */

        /* Sub-loop: 2 sub-init blocks for objects at +0x10 and at base.
         * ~120 more insns of sub-init, double-buffered with back-pointer
         * patching at sub->0x4 / sub->0x14. Deferred to TODO. */
        return titproc_uso_func_00001E9C_TODO_loop(p, sub, a1, a2, a3);
    }
end:
    return p;
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

#ifdef NON_MATCHING
/* titproc_uso_func_00002980: 43-insn (0xAC) alloc-and-link node helper
 * with dead-code suffix. Sibling of mgrproc_uso_func_00003358 (39-insn
 * version, currently NM 89.22% with documented frame/regalloc cap).
 *
 * Structure (decoded from asm 0x2980-0x2A14):
 *   p = alloc(0x40)
 *   if (p == 0) return 0
 *   gl_func_00000000(p)                    ; init call (1 arg)
 *   p[0x28] = &D_00000000
 *   p[0x3C] = 0
 *   q = a0->[0x40]                          ; original-a0 reloaded from
 *                                             caller slot (sp+0x28)
 *   if (q == 0) goto end
 *   gl_func_00000000(p + 0x10, q)          ; link call (2 args)
 *   if (q->[0x14] == 0) {
 *       q->[0x14] = p
 *   } else {
 *       q->[0x4] = 1
 *       q->[0x14] = p
 *   }
 *   end: return p
 *
 * Trailing dead-code at 0x2A10/14: `jr ra; sw a0, 0(sp)` (a phantom
 * 2-insn alt-entry stub that's never branched to in this function but
 * lives inside its symbol). Plus a 4-insn data block at 0x2A18-0x2A28
 * (jump-table or constants — outside the 0xAC declared size?).
 *
 * Cap class likely matches mgrproc 33358's: frame-of-0x28 + extra
 * spills around the second jal won't reproduce from natural C; needs
 * INSN_PATCH or further refinement.
 *
 * Initial structural decode for grep + multi-tick refinement. */
extern int gl_func_00000000();
int *titproc_uso_func_00002980(int *a0) {
    int *p = (int*)gl_func_00000000(0x40);
    int *q;
    if (p == 0) return 0;
    gl_func_00000000(p);
    p[0x28/4] = (int)&D_00000000;
    p[0x3C/4] = 0;
    q = (int*)a0[0x40/4];
    if (q != 0) {
        gl_func_00000000((char*)p + 0x10, q);
        if (q[0x14/4] != 0) q[0x4/4] = 1;
        q[0x14/4] = (int)p;
    }
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00002980);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_00002980_pad.s")
