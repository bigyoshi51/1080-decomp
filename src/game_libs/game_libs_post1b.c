#include "common.h"
extern int D_00000000;
extern int gl_data_00000000;
extern int gl_data_67470_addr;
extern int gl_data_6C9F4_devCfg;
extern char gl_data_BE14_b;
extern char gl_data_BE14_c;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;
#ifdef NON_MATCHING
#define GL_COUNT_2070 (*(int*)((char*)&D_00000000 + 0x2070))
#endif


extern int gl_func_00000000();
int gl_func_00062F64(a0) int a0; {
    gl_func_00000000(a0);
    return gl_func_00000000(a0);
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00062F8C)();
void gl_func_00062F8C(char *arg0) {
    s32 sp3C;
    char *sp38;
    s32 sp34;
    s32 sp28;
    f32 sp24;
    s32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f16;
    s16 temp_a1_4;
    s32 temp_a2;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_t7;
    s32 var_t8;
    s32 var_v1;
    s32 var_v1_2;
    char *temp_a0;
    char *temp_a1;
    char *temp_a1_2;
    char *temp_a1_3;
    char *temp_v1;
    char *temp_v1_2;
    char *temp_v1_4;

    temp_v0 = FW(arg0, 0x98);
    if (temp_v0 != 0) {
        temp_a1 = FW(arg0, 0x74);
        if (temp_a1 != 0) {
            if (temp_v0 & 0x80) {
                if ((*(f32*)((char*)arg0 + 0x94)) < 0.0f) {
                    temp_a1_2 = FW(arg0, 0x8C);
                    FW(arg0, 0x74) = temp_a1_2;
                    sp34 = gl_func_00062F64(temp_a1_2, 0);
                    (*(f32*)((char*)arg0 + 0x78)) = (f32) ((((f32) gl_func_00062F64(arg0, FW(arg0, 0x74), 1) - (f32) sp34) * -(*(f32*)((char*)arg0 + 0x94))) + (f32) sp34);
                } else {
                    temp_a1_3 = FW(arg0, 0x90);
                    FW(arg0, 0x74) = temp_a1_3;
                    sp34 = gl_func_00062F64(arg0, temp_a1_3, 0);
                    var_f16 = (((f32) gl_func_00062F64(arg0, FW(arg0, 0x74), 1) - (f32) sp34) * (*(f32*)((char*)arg0 + 0x94))) + (f32) sp34;
                    goto block_26;
                }
            } else {
                sp24 = (f32) gl_func_00062F64(arg0, temp_a1, FW(arg0, 0x80));
                var_v1 = 0;
                if (sp24 < (f32) gl_func_00062F64(arg0, FW(arg0, 0x74), FW(arg0, 0x7C))) {
                    var_v1 = 1;
                }
                sp20 = var_v1;
                temp_f0_3 = (f32) gl_func_00062F64(arg0, FW(arg0, 0x74), FW(arg0, 0x80));
                if (var_v1 != 0) {
                    var_t7 = 0;
                    temp_f2 = (*(f32*)((char*)arg0 + 0x78)) - temp_f0_3;
                    (*(f32*)((char*)arg0 + 0x78)) = temp_f2;
                    if (temp_f2 <= sp24) {
                        var_t7 = 1;
                    }
                    sp28 = var_t7;
                } else {
                    var_t8 = 0;
                    temp_f2_2 = (*(f32*)((char*)arg0 + 0x78)) + temp_f0_3;
                    (*(f32*)((char*)arg0 + 0x78)) = temp_f2_2;
                    if (sp24 <= temp_f2_2) {
                        var_t8 = 1;
                    }
                    sp28 = var_t8;
                }
                temp_a2 = FW(arg0, 0x64);
                if (temp_a2 != -0x3E8) {
                    if (var_v1 != 0) {
                        if ((*(f32*)((char*)arg0 + 0x78)) <= (f32) gl_func_00062F64(arg0, FW(arg0, 0x74), temp_a2)) {
                            temp_v1 = FW(arg0, 0x28);
                            ((GP_00062F8C)FW(temp_v1, 0x5C))(FW(temp_v1, 0x58) + (int)arg0);
                        }
                    } else if ((f32) gl_func_00062F64(arg0, FW(arg0, 0x74), temp_a2) <= (*(f32*)((char*)arg0 + 0x78))) {
                        temp_v1_2 = FW(arg0, 0x28);
                        ((GP_00062F8C)FW(temp_v1_2, 0x5C))(FW(temp_v1_2, 0x58) + (int)arg0);
                    }
                }
                if (sp28 != 0) {
                    temp_v0_2 = FW(arg0, 0x98);
                    (*(f32*)((char*)arg0 + 0x78)) = sp24;
                    if (temp_v0_2 & 2) {
                        if (temp_v0_2 & 4) {
                            temp_t4 = FW(arg0, 0x80);
                            FW(arg0, 0x80) = (s32) FW(arg0, 0x7C);
                            FW(arg0, 0x7C) = temp_t4;
                        } else {
                            var_f16 = (f32) gl_func_00062F64(arg0, FW(arg0, 0x74), FW(arg0, 0x7C));
block_26:
                            (*(f32*)((char*)arg0 + 0x78)) = var_f16;
                        }
                    }
                }
            }
            temp_v0_3 = gl_func_00062F64(FW(arg0, 0x58), FW(arg0, 0x74));
            sp3C = temp_v0_3;
            temp_a1_4 = (*(s16*)((char*)temp_v0_3 + 0x2));
            var_v1_2 = (s32) (*(f32*)((char*)arg0 + 0x78));
            var_a0 = var_v1_2 + 1;
            if (var_a0 >= temp_a1_4) {
                (*(f32*)((char*)arg0 + 0x78)) = (f32) (temp_a1_4 - 1);
                var_v1_2 = (s32) (*(f32*)((char*)arg0 + 0x78));
                var_a0 = var_v1_2 + 1;
            }
            FW(arg0, 0x4C) = var_v1_2;
            FW(arg0, 0x50) = var_a0;
            FW(arg0, 0xAC) = 0;
            (*(f32*)((char*)arg0 + 0x54)) = (f32) ((*(f32*)((char*)arg0 + 0x78)) - (f32) var_v1_2);
            if (FW(arg0, 0x98) & 0x100) {
                temp_v1_3 = FW(arg0, 0x6C);
                temp_v0_4 = FW(arg0, 0x70) + 1;
                FW(arg0, 0x70) = temp_v0_4;
                FW(arg0, 0xAC) = (s32) (temp_v1_3 - temp_v0_4);
                (*(f32*)((char*)arg0 + 0xA8)) = (f32) ((f32) temp_v0_4 / (f32) temp_v1_3);
                if (temp_v0_4 >= temp_v1_3) {
                    FW(arg0, 0x98) = (s32) (FW(arg0, 0x98) & ~0x100);
                    if (FW(arg0, 0x68) == -1) {
                        temp_v1_4 = FW(arg0, 0x28);
                        ((GP_00062F8C)FW(temp_v1_4, 0x5C))(FW(temp_v1_4, 0x58) + (int)arg0, temp_a1_4);
                    }
                }
            }
            temp_v0_5 = FW(arg0, 0xA0) - 1;
            FW(arg0, 0xA0) = temp_v0_5;
            if (temp_v0_5 <= 0) {
                temp_a0 = FW(arg0, 0x58) + 0x40;
                sp38 = temp_a0;
                FW(arg0, 0x34) = gl_func_00062F64(temp_a0, (char *) sp3C, FW(arg0, 0x4C));
                FW(arg0, 0x38) = gl_func_00062F64(temp_a0, (char *) sp3C, FW(arg0, 0x50));
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062F8C);
#endif

#ifdef NON_MATCHING
/* STRUCTURAL first-pass 2026-05-31 (raw-.word USO decode). 64-insn list-walk
 * constructor. Guards: return if self->0xA0 != 0, or self->0x74 == 0. Allocs
 * via base = self->0x58 + 0x40 (shared a0 for both calls): self->0x44 =
 * f(base, self->0x34); self->0x48 = f(base, self->0x38). Then walks the linked
 * list at self->0x30 (node[0]=value-ptr, node[1]=next): for each node, with
 * off = ((int*)node[0])->0x10C * 14, calls f(self->0x44 + off, self->0x48 +
 * off, self->0x54, self->0xAC, self->0xA8 (float)). Finally self->0xA0 =
 * self->0xA4. % partial: exact list-walk reg/slot allocation (sp+0x2C node /
 * sp+0x30 next) not yet pinned. */
extern int gl_func_00000000();
void gl_func_0006337C(int *self) {
    int base;
    void **node;
    void **next;
    int val;
    if (self[0xA0 / 4] != 0) {
        return;
    }
    if (self[0x74 / 4] == 0) {
        return;
    }
    base = self[0x58 / 4] + 0x40;
    self[0x44 / 4] = gl_func_00000000(base, self[0x34 / 4]);
    self[0x48 / 4] = gl_func_00000000(base, self[0x38 / 4]);
    node = (void **)self[0x30 / 4];
    val = 0;
    if (node != 0) {
        next = (void **)node[1];
        val = (int)node[0];
    }
    while (val != 0) {
        int *obj = (int *)val;
        int off = obj[0x10C / 4] * 14;
        gl_func_00000000(self[0x44 / 4] + off, self[0x48 / 4] + off,
                         self[0x54 / 4], self[0xAC / 4],
                         *(float *)&self[0xA8 / 4]);
        node = next;
        val = 0;
        if (node != 0) {
            next = (void **)node[1];
            val = (int)node[0];
        }
    }
    self[0xA0 / 4] = self[0xA4 / 4];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006337C);
#endif

void game_libs_func_0006347C(int *a0, int a1) {
    if (a1 != *(int*)((char*)a0 + 0xA4)) {
        *(int*)((char*)a0 + 0xA4) = a1;
        *(int*)((char*)a0 + 0xA0) = a1;
    }
}

/* 24-insn setter. Promoted 92.86%→100% via feedback-ido-unused-arg-fix-
 * pass-to-callee: passed unused a1 to the first call to suppress its
 * K&R caller-slot spill. */
extern int func_00000000();
void gl_func_00063498(int *a0, int a1, int a2, int a3, float f) {
    int *r = (int*)func_00000000(a0[0x58/4], a1);
    *(int*)((char*)r[0x10/4] + a2*8) = a3;
    *(int*)((char*)r[0x10/4] + a2*8) = (int)f;
}

/* gl_func_000634F8: 28-insn bounds-check + array-deref.
 *   v0 = func(a0->[0x58]);
 *   if (a2 >= v0->[0xC]) {
 *     err = func(a1);
 *     func(0x22180, a2, err);  // assert
 *   }
 *   return v0->[0x10][a2*8/4]; */
int gl_func_000634F8(int *a0, int a1, int a2) {
    int *v0 = (int*)func_00000000(a0[0x58/4]);
    if (a2 >= v0[0xC/4]) {
        int v = func_00000000(a1);
        func_00000000((char*)&D_00000000 + 0x22180, a2, v);
    }
    return *(int*)((char*)v0[0x10/4] + a2*8);
}

/* gl_func_00063568: 28-insn float-version of gl_func_000634F8.
 *   Same bounds-check + array-deref pattern, but returns float from
 *   offset +4 in the 8-byte entry. */
float gl_func_00063568(int *a0, int a1, int a2) {
    int *v0 = (int*)func_00000000(a0[0x58/4]);
    if (a2 >= v0[0xC/4]) {
        int v = func_00000000(a1);
        func_00000000((char*)&D_00000000 + 0x22194, a2, v);
    }
    return *(float*)((char*)v0[0x10/4] + a2*8 + 4);
}

/* gl_func_000635D8: 37-insn constructor-style initializer.
 *   Takes (self, a1, a2, a3, stack_a5, stack_a4) — note the trailing
 *   args are stored in opposite-of-name positions in self per target asm.
 *   Body: log → fields → FUNC2(self,a1,a2) → -1000 + a4/a5 fields → tail call.
 * 9-insn INSN_PATCH closes a v0/v1 register rename for a3 and a 6-insn
 * cvt/swc1-vs-v1-store reorder. */
#ifdef NON_MATCHING
void gl_func_000635D8(int *self, int a1, int a2, int a3, int a4, int a5) {
    int r;
    func_00000000((char*)&D_00000000 + 0x221A8);
    self[0x88/4] = a3;
    self[0x80/4] = a3;
    self[0x74/4] = a1;
    self[0x7C/4] = a2;
    self[0x84/4] = a2;
    r = func_00000000(self, a1, a2);
    *(float*)&self[0x78/4] = (float)r;
    self[0x64/4] = -1000;
    self[0x68/4] = -1000;
    self[0x70/4] = 0;
    self[0x6C/4] = a5;
    self[0x98/4] = a4;
    func_00000000();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000635D8);
#endif

/* gl_func_0006366C: too-big-N-function-bundle (declared size 0xA0, 40 words).
 * Splat grouped 3 distinct functions under one symbol — 3 jr $ra terminators.
 * Candidate for split-fragments.py.
 *
 * SUB-FUNCTION 1 (0x6366C..0x636BC, 20 insns, 0x4C bytes):
 *     // 3-field compare + log if any differs
 *     void f1(Obj *a0, int a1, int a2, int a3, int arg5, int arg6) {
 *         if (a1 == a0->[0x74] &&
 *             a2 == a0->[0x84] &&
 *             a3 == a0->[0x88]) return;     // beql to epilogue
 *         // diff detected: stash args and log
 *         *(int*)(sp+0x10) = arg5;
 *         *(int*)(sp+0x14) = arg6;
 *         debug_log();                       // jal <func>
 *     }
 *
 * SUB-FUNCTION 2 (0x636BC..0x63700, 17 insns, 0x44 bytes, NO PROLOGUE — leaf):
 *     // 6-arg setter with flag-check on incoming bits
 *     void f2(Obj *a0, int a1, int a2, float a3, int sp_arg10, int sp_arg14) {
 *         int flag_new = a0->[0x98];     // pre-update flag
 *         a0->[0x8C] = a1;
 *         a0->[0x90] = a2;
 *         a0->[0x94] = a3;               // swc1 (float)
 *         if (flag_new & 0x100) a0->[0x6C] = sp_arg14;  // bit 8 set
 *         if (!(sp_arg10 & 0x100)) a0->[0x70] = 0;       // bit 8 clear in sp_arg10
 *         a0->[0x98] = sp_arg10 | 0x80;   // commit with new flag bit
 *     }
 *   Pattern: incoming float arg in $a3 → mtc1 $a3, $f12 first insn (FP convert),
 *   then standard sw stores. No-prologue leaf relies on caller's sp+0x10..0x14
 *   for 5th/6th args (standard O32 outgoing-arg-area aliasing).
 *
 * SUB-FUNCTION 3 (0x63700..0x63708, 2 insns, 0x8 bytes):
 *     void f3(int a0) {
 *         // body inlined-out; remaining: arg-save stub
 *         *(int*)(sp+0x0) = a0;
 *     }
 *   Pattern: vestigial "store arg to stack-slot" thunk. Body was likely inlined
 *   elsewhere but the IDO arg-save pseudo-prologue (caller saves a0-a3 to
 *   sp+0..0xC) remained as the only emitted insn. Returns without altering
 *   anything observable.
 *
 * Notes:
 *  - 3 internal `jr $ra` confirm the 3-function bundle.
 *  - f2 uses no-prologue leaf with caller-supplied sp+0x10/0x14 args — fits
 *    standard O32 stack-arg passing (args 5+).
 *  - f3 is functionally a no-op with arg-save side effect; possibly an
 *    inlining residue (compiler couldn't fully eliminate it because the symbol
 *    is taken by address elsewhere).
 *  - Now split to 0x50 (this fn only); decoded 2026-05-24. 6-arg passthrough
 *    with a 3-way AND guard (skip the call when all three fields already match). */
extern int gl_func_00000000();
void gl_func_0006366C(int a0, int a1, int a2, int a3, int a4, int a5) {
    if (a1 == *(int *)(a0 + 0x74) && a2 == *(int *)(a0 + 0x84) &&
        a3 == *(int *)(a0 + 0x88)) {
        return;
    }
    gl_func_00000000(a0, a1, a2, a3, a4, a5);
}

/* game_libs_func_000636BC: 18-insn struct-setter with 2 conditional state changes.
 *   void f(int *a0, int a1, int a2, float a3, int a4, int a5) {
 *     int old_98 = a0[0x98];
 *     a0[0x8C] = a1; a0[0x90] = a2; a0[0x94] = a3 (float);
 *     if (old_98 & 0x100)  a0[0x6C] = a5;
 *     if (!(a4 & 0x100))   a0[0x70] = 0;
 *     a0[0x98] = a4 | 0x80;
 *   }
 *
 * 2026-05-27: NM-wrap added with float-typed a3 (sig-type-fix lever).
 * 18-insn match in count but register-rename + scheduling diffs from
 * target's bnel-shared-tail pattern (TWO lw a4 reloads with branch-likely).
 * `int *p4 = &a4` lever produces the bnel form but reg cascade differs. */
#ifdef NON_MATCHING
void game_libs_func_000636BC(int *a0, int a1, int a2, float a3, int a4, int a5) {
    int old_98 = a0[0x98 / 4];
    int *p4 = &a4;
    a0[0x8C / 4] = a1;
    a0[0x90 / 4] = a2;
    *(float*)((char*)a0 + 0x94) = a3;
    if (old_98 & 0x100) {
        a0[0x6C / 4] = a5;
    }
    if (!((*p4) & 0x100)) {
        a0[0x70 / 4] = 0;
    }
    a0[0x98 / 4] = (*p4) | 0x80;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000636BC);
#endif


void game_libs_func_00063704(int a0) {}

extern int gl_ref_00076488();
extern int gl_ref_00076584();
void gl_func_0006370C(char *a0) {
    int local;
    gl_ref_00076488(&local);
    gl_ref_00076584(a0 + 0x10);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006370C_pad.s")

extern int gl_func_00000000();
void gl_func_00063744(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00063780(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

void gl_func_000637BC(Vec3 *dst) {
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

extern int gl_func_00000000();
void gl_func_0006382C(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

#ifdef NON_MATCHING
/* gl_func_00063884: 56-insn alloc-if-null constructor + 2 Vec3
 * int->float copies. a0 ?: alloc(292); init call; a0->[0x28]=&D;
 * a2 Vec3 -> a0->[0x10C..0x114]; a3 Vec3 -> a0->[0x118..0x120] (both
 * via shared sp+0x2C int tmp); a0->[0x108]=a1.
 *
 * 73.25% CAP: the init call passes three single-precision float zeros
 * — target `mtc1 zero,$f0; mfc1 a2,$f0; mfc1 a3,$f0; swc1 $f0,16(sp)`
 * (4-byte) — but the file-scope K&R `extern int gl_func_00000000()`
 * DOUBLE-PROMOTES the C `0.0f` literals: `cvt.d.s` + `sdc1` (8-byte)
 * + extra insns (+3 length). Provably unmatchable per
 * docs/IDO_CODEGEN.md#feedback-ido-knr-float-call (same cap class as
 * gl_func_0005DB58 / gl_func_00063DC4). Logic fully decoded; the Vec3
 * copies + struct stores ARE correct. INCLUDE_ASM is the build path. */
extern int gl_func_00000000();
extern int D_00000000;
void *gl_func_00063884(void *a0, int a1, int *a2, int *a3) {
    int tmp[3];
    if (a0 == 0) {
        a0 = (void*)gl_func_00000000(292);
        if (a0 == 0) return a0;
    }
    gl_func_00000000(a0, (char*)&D_00000000 + 0x22388, 0.0f, 0.0f, 0.0f);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    tmp[0] = a2[0]; tmp[1] = a2[1]; tmp[2] = a2[2];
    *(float*)((char*)a0 + 0x10C) = *(float*)&tmp[0];
    *(float*)((char*)a0 + 0x110) = *(float*)&tmp[1];
    *(float*)((char*)a0 + 0x114) = *(float*)&tmp[2];
    tmp[0] = a3[0]; tmp[1] = a3[1]; tmp[2] = a3[2];
    *(float*)((char*)a0 + 0x118) = *(float*)&tmp[0];
    *(float*)((char*)a0 + 0x11C) = *(float*)&tmp[1];
    *(float*)((char*)a0 + 0x120) = *(float*)&tmp[2];
    *(int*)((char*)a0 + 0x108) = a1;
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063884);
#endif

/* gl_func_00063964 graft attempt 2026-06-10: a fresh m2c graft scored
 * fuzzy=None (unalignable) despite only +0x10 oversize and none of the
 * documented None artifacts (no empty ifs / no-op gotos) -- an
 * uncharacterized None trigger. This 22.62 body stays (measurable
 * beats None). Hand-refinement territory. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00063964)();
typedef struct { f32 unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00063964;
void gl_func_00063964(char *arg0, f32 arg1, int arg2, int arg3) {
    Q_00063964 sp108;
    Q_00063964 sp1C;
    Q_00063964 sp28;
    Q_00063964 sp34;
    Q_00063964 sp48;
    Q_00063964 sp54;
    Q_00063964 sp60;
    Q_00063964 sp74;
    Q_00063964 sp90;
    Q_00063964 sp9C;
    Q_00063964 spAC;
    Q_00063964 spB8;
    Q_00063964 spD0;
    Q_00063964 spDC;
    f32 sp144;
    f32 sp140;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    s32 sp114;
    s32 sp18;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f8;
    f32 var_f16;
    s32 temp_a0;
    f32 temp_t0;
    f32 temp_t0_2;
    f32 temp_t1;
    f32 temp_t7;
    f32 temp_t8;
    f32 temp_t8_2;
    f32 temp_t9;
    f32 temp_t9_2;
    s32 var_v1;

    temp_a0 = (int)arg0 + 0xF4;
    sp18 = temp_a0;
    gl_func_00062F64(temp_a0, (int)arg0 + 0x10C, &sp130, arg0);
    gl_func_00062F64(sp18, (int)arg0 + 0x118, &sp124, arg0);
    temp_f8 = sp130 + (*(f32*)((char*)arg0 + 0xDC));
    sp130 = temp_f8;
    sp134 += (*(f32*)((char*)arg0 + 0xE0));
    sp138 += (*(f32*)((char*)arg0 + 0xE4));
    temp_f10 = sp124 + (*(f32*)((char*)arg0 + 0xDC));
    sp124 = temp_f10;
    sp128 += (*(f32*)((char*)arg0 + 0xE0));
    sp120 = 0.0f;
    sp11C = 0.0f;
    sp118 = 0.0f;
    sp12C += (*(f32*)((char*)arg0 + 0xE4));
    temp_f12 = sp138 - sp12C;
    spD0.unk0 = temp_f8 - temp_f10;
    spD0.unk8 = temp_f12;
    spD0.unk4 = sp134 - sp128;
    spDC.unk0 = (f32) spD0.unk0;
    temp_t7 = spD0.unk4;
    spDC.unk4 = temp_t7;
    temp_t8 = spD0.unk8;
    sp108.unk4 = temp_t7;
    sp108.unk0 = spDC.unk0;
    spDC.unk8 = temp_t8;
    sp108.unk8 = temp_t8;
    sp114 = 0;
    arg1 = 0.0f;
    gl_func_00062F64((s32) temp_f12, &sp108);
    var_v1 = sp114;
    var_f16 = arg1;
    if (sp134 < 0.0f) {
        spAC.unk0 = sp108.unk0 * sp134;
        var_v1 = 1;
        spAC.unk4 = sp108.unk4 * sp134;
        spAC.unk8 = sp108.unk8 * sp134;
        spDC.unk0 = (f32) spAC.unk0;
        spDC.unk4 = spAC.unk4;
        spDC.unk8 = spAC.unk8;
        spB8.unk0 = spDC.unk0;
        spB8.unk4 = spDC.unk4;
        spB8.unk8 = spDC.unk8;
        sp90.unk0 = sp130 + spB8.unk0;
        sp90.unk4 = sp134 + spB8.unk4;
        sp90.unk8 = sp138 + spB8.unk8;
        sp9C.unk0 = (f32) sp90.unk0;
        temp_t8_2 = sp90.unk4;
        sp9C.unk4 = temp_t8_2;
        temp_t9 = sp90.unk8;
        sp74.unk4 = temp_t8_2;
        sp74.unk0 = sp9C.unk0;
        sp9C.unk8 = temp_t9;
        sp74.unk8 = temp_t9;
        sp118 = sp74.unk0;
        sp120 = sp74.unk8;
        sp11C = sp74.unk4;
        var_f16 = 0.0f + sp134;
    }
    if (sp128 < 0.0f) {
        sp54.unk0 = sp108.unk0 * sp128;
        var_v1 += 1;
        sp54.unk4 = sp108.unk4 * sp128;
        var_f16 += sp128;
        sp54.unk8 = sp108.unk8 * sp128;
        spDC.unk0 = (f32) sp54.unk0;
        spDC.unk4 = sp54.unk4;
        spDC.unk8 = sp54.unk8;
        sp60.unk0 = spDC.unk0;
        sp60.unk4 = spDC.unk4;
        sp60.unk8 = spDC.unk8;
        sp48.unk0 = sp124 + sp60.unk0;
        sp48.unk4 = sp128 + sp60.unk4;
        sp48.unk8 = sp12C + sp60.unk8;
        sp9C.unk0 = (f32) sp48.unk0;
        temp_t9_2 = sp48.unk4;
        sp9C.unk4 = temp_t9_2;
        temp_t0 = sp48.unk8;
        sp74.unk4 = temp_t9_2;
        sp74.unk0 = sp9C.unk0;
        sp9C.unk8 = temp_t0;
        sp74.unk8 = temp_t0;
        sp120 = sp74.unk8;
        sp11C = sp74.unk4;
        sp118 = sp74.unk0;
    }
    if (var_v1 == 2) {
        sp28.unk0 = sp130 + sp124;
        sp28.unk4 = sp134 + sp128;
        sp28.unk8 = sp138 + sp12C;
        spDC.unk0 = (f32) sp28.unk0;
        spDC.unk4 = sp28.unk4;
        spDC.unk8 = sp28.unk8;
        sp34.unk0 = spDC.unk0;
        sp34.unk4 = spDC.unk4;
        sp34.unk8 = spDC.unk8;
        sp1C.unk0 = sp34.unk0 * 0.5f;
        sp1C.unk4 = sp34.unk4 * 0.5f;
        sp1C.unk8 = sp34.unk8 * 0.5f;
        sp9C.unk0 = (f32) sp1C.unk0;
        temp_t0_2 = sp1C.unk4;
        sp9C.unk4 = temp_t0_2;
        temp_t1 = sp1C.unk8;
        sp74.unk4 = temp_t0_2;
        sp74.unk0 = sp9C.unk0;
        sp9C.unk8 = temp_t1;
        sp74.unk8 = temp_t1;
        sp118 = sp74.unk0;
        sp11C = sp74.unk4;
        sp120 = sp74.unk8;
        var_f16 = (f32) ((f64) var_f16 * 0.5);
    }
    sp13C = 0.0f;
    sp140 = -var_f16;
    sp144 = 0.0f;
    gl_func_00062F64((*(f32*)((char*)arg0 + 0x108)), &sp118, &sp13C, arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063964);
#endif

#ifdef NON_MATCHING
/* gl_func_00063DC4: 48-insn alloc-if-null constructor + Vec3-magnitude.
 *   s0 = a0 ?: alloc(368); if(!s0) return s0;
 *   gl_func_00000000(s0, &D+0x22390, 0.0f, 0.0f, 0.0f);  // a2/a3/sp16=0
 *   s0->[0x28] = &D_00000000;
 *   s0->[0x16C] = a1;
 *   gl_func_00000000(s0, a2, a3, <sp+0x38>);
 *   gl_func_00000000(s0);
 *   s0->[0x164] = gl_func_00000000(a2*a2 + a3*a3 + <f>*<f>);  // jal#4
 *   return s0;
 *
 * CAP: jal#4 passes a single float (the magnitude²) to the file-scope
 * K&R `extern int gl_func_00000000()` via DIRECT jal — provably
 * unmatchable per docs/IDO_CODEGEN.md#feedback-ido-knr-float-call
 * (float→double promote / prototype-redecl cfe error / fn-ptr-cast
 * yields jalr). Same cap as gl_func_0005DB58. The early float-zero
 * args (jal#1) ARE matchable (GPR-passed after the ptr, like
 * gl_func_0000BBF0) — only jal#4 is the blocker, making the whole
 * function NM. INCLUDE_ASM is the build path (ROM byte-exact). */
extern int gl_func_00000000();
extern int aD63DC4_5(void*, void*, float, float, float);
extern int aD63DC4_4(void*, float, float, int);
extern float aD63DC4_1(float);
void *gl_func_00063DC4(void *a0, int a1, float a2, float a3) {
    void *s0 = a0;
    if (s0 == 0) {
        s0 = (void*)gl_func_00000000(368);
        if (s0 == 0) return s0;
    }
    aD63DC4_5(s0, (char*)&D_00000000 + 0x22390, 0.0f, 0.0f, 0.0f);
    *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)s0 + 0x16C) = a1;
    aD63DC4_4(s0, a2, a3, 0);
    gl_func_00000000(s0);
    *(float*)((char*)s0 + 0x164) =
        aD63DC4_1(a2 * a2 + a3 * a3 + 0.0f);
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063DC4);
#endif

#ifdef NON_MATCHING
/* gl_func_00063E84: 44-insn config-registration (2 float entries).
 *   gl_func_00000000(&D, &D+0x22398, 0);
 *   gl_func_00000000(&D, &D+0x223A4, a0+0x150, 0, 2.0f, 1);
 *   gl_func_00000000(&D, &D+0x223B0, a0+0x154, 0, 10.0f, 1);
 *   gl_func_00000000(&D);
 *   gl_func_00000000(a0);
 * The two float consts (2.0f / 10.0f) are passed in the 5th (stack)
 * arg slot as 4-byte `swc1 ,16(sp)` — single-precision, NOT
 * K&R-double-promoted, so this is NOT the knr-float-direct-jal cap;
 * but the file-scope K&R `extern int gl_func_00000000()` will
 * double-promote a plain float literal (sdc1, 8B). Reaching exact
 * needs the float bits passed as a 32-bit int (reinterpret) so a
 * single 4-byte stack store is emitted. Trailing `lui at,0x4120;
 * mtc1 a1,$f12; mtc1 at,$f4` in the symbol is the SUCCESSOR's stolen
 * prologue. First-pass structural decode; INCLUDE_ASM is the build
 * path (ROM byte-exact). */
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00063E84(char *a0) {
    union { float f; int i; } c2, c10;
    c2.f = 2.0f;
    c10.f = 10.0f;
    gl_func_00000000(&D_00000000, (char*)&D_00000000 + 0x22398, 0);
    gl_func_00000000(&D_00000000, (char*)&D_00000000 + 0x223A4,
                     a0 + 0x150, 0, c2.i, 1);
    gl_func_00000000(&D_00000000, (char*)&D_00000000 + 0x223B0,
                     a0 + 0x154, 0, c10.i, 1);
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063E84);
#endif


/* game_libs_func_00063F34: one 108-insn (0x1B0) function. BOUNDARY MERGED
 * 2026-06-02: splat had split it into 00063F34 (3-insn FP-const prologue:
 * `mtc1 a1,$f12` (input value, ARG-DERIVED) + `lui 0x4120`->$f4=10.0 — hoisted
 * above the frame; the real entry) + gl_func_00063F40 (the prologue+body using
 * f12 in `c.lt.s $f12,$f4`). SINGLE-entry per the dual-vs-single test (f12 is
 * arg-derived + FP-op use, NOT mfc1-back; no callers). Absorbed 00063F40's 105
 * words into 00063F34 (0xC -> 0x1B0); dropped the 00063F40 symbol. Brings f12
 * (=a1) and f4 (=10.0) in-scope (retracts the implicit caller-set-float cap);
 * the 105-insn body is decodable in a future pass. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00063F34)();
typedef struct { f32 unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00063F34;
void game_libs_func_00063F34(char *arg0, f32 arg1, char *arg2, f32 arg3) {
    Q_00063F34 sp44;
    f32 sp40;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f0;

    if (arg1 < 10.0f) {
        sp44.unk0 = (*(f32*)((char*)arg0 + 0x114));
        sp44.unk4 = (s32) (*(f32*)((char*)arg0 + 0x118));
        sp44.unk8 = (s32) (*(f32*)((char*)arg0 + 0x11C));
        temp_f2 = (*(f32*)((char*)arg2 + 0x0));
        temp_f0 = (sp44.unk0 * temp_f2) + (sp44.unk4 * (*(f32*)((char*)arg2 + 0x4))) + (sp44.unk8 * (*(f32*)((char*)arg2 + 0x8)));
        temp_f4 = (temp_f0 * temp_f2) - sp44.unk0;
        sp44.unk0 = temp_f4;
        temp_f16 = (temp_f0 * (*(f32*)((char*)arg2 + 0x4))) - sp44.unk4;
        sp44.unk4 = temp_f16;
        temp_f6 = (temp_f0 * (*(f32*)((char*)arg2 + 0x8))) - sp44.unk8;
        sp44.unk8 = temp_f6;
        temp_f0_2 = ((f32(*)())gl_func_00062F64)((temp_f4 * temp_f4) + (temp_f16 * temp_f16) + (temp_f6 * temp_f6));
        if ((*(f64*)((char*)&D_00000000 + 0x20A0)) < (f64) temp_f0_2) {
            sp40 = temp_f0_2;
            gl_func_00062F64(&sp44);
            temp_f0_3 = (f32) ((f64) ((int)arg3 + (FW(arg0, 0x150) * FW(FW(arg0, 0x16C), 0x360))) * (*(f64*)((char*)&D_00000000 + 0x20A8)));
            var_f0 = temp_f0_3 * temp_f0_3;
            if ((*(f64*)((char*)&D_00000000 + 0x20B0)) < (f64) var_f0) {
                var_f0 = (*(f32*)((char*)&D_00000000 + 0x20B8));
            }
            if (var_f0 < 0.0f) {
                var_f0 = 0.0f;
            }
            temp_f0_4 = var_f0 * sp40;
            sp44.unk0 *= temp_f0_4;
            sp44.unk4 *= temp_f0_4;
            sp44.unk8 *= temp_f0_4;
            gl_func_00062F64(0.0f, FW(arg0, 0x16C), (int)arg0 + 0x120, &sp44, arg0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00063F34);
#endif

/* gl_func_000640E4: 16-insn dispatcher. EXACT — keys: pass a0 through
 * to both calls (gl_func_00000000(a0)) so IDO does not emit the unused-
 * arg `sw a0` spill, and read `int v = *a1` into a named temp so the
 * compare value lands in $v0 (bare `*a1==9` uses $t6). */
void gl_func_000640E4(int a0, int *a1) {
    int v = *a1;
    if (v == 9) {
        gl_func_00000000(a0);
    } else {
        gl_func_00000000(a0);
    }
}

#ifdef NON_MATCHING
/* game_libs_func_00064124: struct-field initializer. Zeros several
 * int/float fields, sets three 1.0f fields + an int 256.
 *
 * 87.05% — logic fully decoded, store order matches. Residual caps:
 *  - Float-reg split: target materializes THREE fp consts —
 *    $f2=0.0f (bulk zero stores), $f0=1.0f, $f4=0.0f (used ONLY for
 *    the final a0+0x144 store, emitted in the jr-ra delay slot). C
 *    CSEs all `0.0f` to one reg ($f0) so the separate $f4 + delay-slot
 *    placement is lost. No plain-C expression yields two distinct 0.0f
 *    regs; needs the source's original distinct sub-expression (likely
 *    a variable, not a literal) — unknown.
 *  - The 0x50 symbol's trailing `mtc1 zero,$f0` is the SUCCESSOR's
 *    stolen prologue — historically captured via SUFFIX_BYTES on this
 *    predecessor and PROLOGUE_STEALS/INSN_PATCH on the successor
 *    gl_func_00064174. All of those mechanisms were REMOVED 2026-05-23
 *    as match-faking. The C-level distinct-$f4-for-0.0 lever is also
 *    missing. Multi-blocker; needs splat boundary correction (focused-
 *    session work) for the trailing-stolen-prologue piece, plus a real
 *    C source for the distinct-$f4 sub-expression.
 *
 *  2026-05-17: tested `float zero2 = 0.0f;` named-local lever (per
 *  docs/IDO_CODEGEN.md#feedback-ido-named-float-const-pins-fp-reg-across-body)
 *  using zero2 only for the a0+0x144 store. No change — fuzzy stayed
 *  87.05%. IDO -O2 constant-folds the named zero into the same $f0/$f2
 *  CSE as the literal 0.0f stores. The named-FP-const lever works for
 *  NON-zero literals (4.0f case) but not for 0.0f because mtc1 $0
 *  encoding doesn't need a distinct lui+mtc1 setup. */
void game_libs_func_00064124(char *a0) {
    *(int*)(a0 + 0x160) = 0;
    *(int*)(a0 + 0x14C) = 0;
    *(int*)(a0 + 0x168) = 256;
    *(float*)(a0 + 0x12C) = 0.0f;
    *(float*)(a0 + 0x130) = 0.0f;
    *(float*)(a0 + 0x134) = 0.0f;
    *(float*)(a0 + 0x108) = 0.0f;
    *(float*)(a0 + 0x10C) = 0.0f;
    *(float*)(a0 + 0x110) = 0.0f;
    *(float*)(a0 + 0x150) = 1.0f;
    *(float*)(a0 + 0x154) = 1.0f;
    *(float*)(a0 + 0x148) = 1.0f;
    *(float*)(a0 + 0x144) = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00064124);
#endif

/* gl_func_00064174: 26-insn 10-float zero + 3-int-to-float bit-copy.
 * $f0=0.0 prologue-stolen from predecessor game_libs_func_00064124's
 * trailing `mtc1 zero,$f0`. PROLOGUE_STEALS=4 splices the C-emit's
 * duplicate leading `mtc1 zero,$f0`. Splice script extended 2026-05-16
 * to accept opcode 0x11 mtc1-zero prefixes. */
#ifdef NON_MATCHING
void gl_func_00064174(float *a0, int *a1) {
    int pad[3];
    int tmp[3];
    (void)pad;
    a0[0] = 0.0f; a0[1] = 0.0f; a0[2] = 0.0f; a0[3] = 0.0f; a0[4] = 0.0f;
    a0[5] = 0.0f; a0[6] = 0.0f; a0[7] = 0.0f; a0[8] = 0.0f; a0[9] = 0.0f;
    tmp[0] = a1[0]; tmp[1] = a1[1]; tmp[2] = a1[2];
    a0[10] = *(float*)&tmp[0];
    a0[11] = *(float*)&tmp[1];
    a0[12] = *(float*)&tmp[2];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064174);
#endif

#ifdef NON_MATCHING
/* 84.75% NM. gl_func_000641DC: 107-insn Vec3 transform/accumulator.
 * First-pass NM with structural decode; register-alloc + scheduling
 * caps to be ground in later runs.
 *
 * Pseudocode:
 *   mag_a = sqrt_like(a2->x² + a2->y² + a2->z²);    // jal #1, ret in $f0
 *   a0->f00  += mag_a;                              // s0[0] += ret
 *   a0->f04  += a1->x * mag_a;                      // s0[1..3] += a1.xyz * mag_a
 *   a0->f08  += a1->y * mag_a;
 *   a0->f0C  += a1->z * mag_a;
 *   a0->f10  += a2->x;                              // s0[4..6] += a2.xyz
 *   a0->f14  += a2->y;
 *   a0->f18  += a2->z;
 *
 *   local = *a1;                                    // copy Vec3 via 3 word lw/sw
 *   mag_b = sqrt_like(local.x² + y² + z²);          // jal #2
 *   if (mag_b >= D_dbl_threshold) {                 // ldc1+cvt.d.s+c.lt.d
 *       out = some_transform(local, a2, &out);      // jal #3
 *       out *= 1.0f / mag_b;                        // 3x mul by 1/mag
 *       a0->f1C += out.x;                           // s0[7..9] += out
 *       a0->f20 += out.y;
 *       a0->f24 += out.z;
 *   }
 *
 * RESIDUAL (84.75%, 2026-06-02 forensic): the build FAILS to promote a0 to a
 * saved register. Target keeps `self` in s0 (`or s0,a0,zero` before the first
 * jal, frame -0x80/-128, saves s0) and spills a1/a2 to their incoming home
 * slots; my build uses NO callee-saved regs at all (frame -0x48/-72, saves only
 * ra) and instead re-homes a0 to sp+0x48 and reloads it as a3/a2 around every
 * jal — IDO chose caller-saved+spill over s0 for the long-lived self pointer.
 * Lever TESTED NEGATIVE: caching a2->x/y/z into float locals before jal #1 (to
 * shorten a2/a1 live ranges and leave a0 dominant) did NOT trigger s0-promotion
 * (still frame -72, no s0, 114 insns — worse). The real lever is forcing a0 into
 * a saved reg / matching the -128 frame; not yet found from C. Permuter-class.
 * Notable shapes:
 *  - $f12 set in jal delay slot for arg passing (mag-squared computed inline)
 *  - 3 jals total; #1 and #2 likely same fn (sqrtf-ish), #3 unknown 3-arg
 *  - a2 spilled at sp+0x88, reloaded as a3 mid-body (caller-slot reuse)
 *  - a1 spilled at sp+0x84
 *  - local buf at sp+0x64, out buf at sp+0x70
 *  - threshold comparison via ldc1 (8-byte double load) + cvt.d.s + c.lt.d
 *
 * Externs reference D_00000000 + offset for the threshold double constant
 * and the three jal targets; identifiers below are placeholders. */
extern float func_641DC_sqrtish(float magSq);
extern int func_641DC_xform(void *out, void *local, void *a2);

typedef struct S641DC_s {
    float f00, f04, f08, f0C;
    Vec3 v10;   /* f10..f18 */
    Vec3 v1C;   /* f1C..f24 */
} S641DC;

void gl_func_000641DC(S641DC *a0, Vec3 *a1, Vec3 *a2, void *a3) {
    Vec3 local;
    Vec3 out;
    float mag_a, mag_b, inv;
    (void)a3;

    mag_a = func_641DC_sqrtish(a2->x*a2->x + a2->y*a2->y + a2->z*a2->z);
    a0->f00 += mag_a;
    a0->f04 += a1->x * mag_a;
    a0->f08 += a1->y * mag_a;
    a0->f0C += a1->z * mag_a;
    a0->v10.x += a2->x;
    a0->v10.y += a2->y;
    a0->v10.z += a2->z;

    local = *a1;
    mag_b = func_641DC_sqrtish(local.x*local.x + local.y*local.y + local.z*local.z);
    if ((double)mag_b >= 1e-6) {   /* exact threshold = D_dbl_const, TBD */
        func_641DC_xform(&out, &local, a2);
        inv = 1.0f / mag_b;
        out.x *= inv; out.y *= inv; out.z *= inv;
        a0->v1C.x += out.x;
        a0->v1C.y += out.y;
        a0->v1C.z += out.z;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000641DC);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00064388)();
typedef struct { f32 unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00064388;
void gl_func_00064388(char *arg0, f32 arg1, char *arg2, f32 arg3) {
    Q_00064388 sp30;
    Q_00064388 sp44;
    Q_00064388 sp60;
    Q_00064388 sp6C;
    Q_00064388 spA4;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    char *sp28;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f2_2;
    char *temp_a1;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v1;

    temp_f2 = (*(f32*)((char*)arg0 + 0x0));
    if (!((f64) temp_f2 < (*(f64*)((char*)&D_00000000 + 0x20C8)))) {
        temp_v0 = (int)arg0 + 4;
        temp_v1 = (int)arg0 + 0x28;
        (*(f32*)((char*)arg0 + 0x4)) = (f32) ((*(f32*)((char*)arg0 + 0x4)) / temp_f2);
        (*(f32*)((char*)arg0 + 0x8)) = (f32) ((*(f32*)((char*)arg0 + 0x8)) / temp_f2);
        (*(f32*)((char*)arg0 + 0xC)) = (f32) ((*(f32*)((char*)arg0 + 0xC)) / temp_f2);
        *(float *)&sp60.unk8 = (*(f32*)((char*)temp_v0 + 0x8)) - (*(f32*)((char*)temp_v1 + 0x8));
        *(float *)&sp60.unk4 = (*(f32*)((char*)temp_v0 + 0x4)) - (*(f32*)((char*)temp_v1 + 0x4));
        *(float *)&sp60.unk0 = (*(f32*)((char*)arg0 + 0x4)) - (*(f32*)((char*)arg0 + 0x28));
        *(float *)&sp6C.unk0 = (f32) sp60.unk0;
        sp6C.unk4 = sp60.unk4;
        sp6C.unk8 = sp60.unk8;
        sp44.unk0 = sp6C.unk0;
        sp44.unk4 = sp6C.unk4;
        sp44.unk8 = sp6C.unk8;
        sp9C = sp44.unk8;
        sp98 = sp44.unk4;
        sp94 = sp44.unk0;
        temp_f0 = (*(f32*)((char*)arg0 + 0x1C));
        temp_f2_2 = (*(f32*)((char*)arg0 + 0x20));
        temp_f14 = (*(f32*)((char*)arg0 + 0x24));
        temp_a1 = (int)arg0 + 0x1C;
        temp_f16 = ((f32(*)())gl_func_00062F64)((temp_f0 * temp_f0) + (temp_f2_2 * temp_f2_2) + (temp_f14 * temp_f14), temp_f14) / (*(f32*)((char*)&D_00000000 + 0x20D0));
        sp28 = temp_a1;
        sp90 = temp_f16 * arg3;
        gl_func_00062F64(temp_a1, temp_a1);
        gl_func_00062F64(arg1, temp_a1, sp90);
        temp_v0_2 = (int)arg0 + 0x10;
        *(float *)&sp30.unk0 = (*(f32*)((char*)arg0 + 0x10)) * 1.0f;
        *(float *)&sp30.unk4 = (*(f32*)((char*)temp_v0_2 + 0x4)) * 1.0f;
        *(float *)&sp30.unk8 = (*(f32*)((char*)temp_v0_2 + 0x8)) * 1.0f;
        *(float *)&sp6C.unk0 = (f32) sp30.unk0;
        sp6C.unk4 = sp30.unk4;
        sp6C.unk8 = sp30.unk8;
        spA4.unk0 = sp6C.unk0;
        spA4.unk4 = sp6C.unk4;
        spA4.unk8 = sp6C.unk8;
        (*(f32*)((char*)arg2 + 0x0)) = (f32) ((*(f32*)((char*)arg2 + 0x0)) + spA4.unk0);
        (*(f32*)((char*)arg2 + 0x4)) = (f32) ((*(f32*)((char*)arg2 + 0x4)) + spA4.unk4);
        (*(f32*)((char*)arg2 + 0x8)) = (f32) ((*(f32*)((char*)arg2 + 0x8)) + spA4.unk8);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064388);
#endif

#ifdef NON_MATCHING
/* gl_func_00064588 - STRUCTURAL PASS (big-swing 2026-06-02).
 * game_libs get-or-alloc slot constructor (same idiom family as the
 * game_uso spine entry game_uso_func_000044F4). 0x864 / 537 insns, sole
 * callee gl_func_0001CA10 (alloc when 1 arg / init when 4 args -- the
 * file-wide generic placeholder, K&R int return, cast to ptr for allocs).
 *
 * Shape:
 *  - alloc/init parent (0x3D4) if arg0==NULL; init via (arg0, arg1, 0,0,0).
 *  - child region var_s0 = arg0+0x108 (alloc 0x180); head node (8 bytes)
 *    {D+0x223C0, 0}.
 *  - 13 simple slots, stride 0x18 from +8 (skipping +0xE0): get-or-alloc(0x18);
 *      init(slot, var_s0, DI(0x223D0 + i*4), 1);
 *      slot[0xC]=0x221D8; slot[0x14]=0; slot[0x10]=<float table/const>.
 *  - 2 complex slots (alloc 0x20) at +0xE0 (idx 0x223F4, slot[0xC]=0x221F0,
 *      Vec3{0,0,0} copied through a staged bounding-box struct {hdr; max{1000};
 *      min{-1000}; {0,0,0}}) and +0x160 (idx 0x22408, slot[0xC]=0x221F0,
 *      Vec3{1,1,0}). slot[0x1C]=0.
 *  - two 4-byte fields at arg0+0x39C / +0x3A0 set to 0; final
 *    gl_func_0001CA10(arg0).
 *
 * 2026-06-21 (agent-i deep-recon pass): added the previously-MISSING +0xE0
 * complex slot (data idx 0x223F4 between 0x223F0/0x223F8 confirmed the gap).
 * Call count now matches target exactly (37 jal). arg0[0x28] corrected to a
 * &D pointer (was 0). Structure complete (15 slots + head + parent + 2 fields
 * + final). NOT matched: single &D pool base referenced ~30x = base-pin cap
 * (infra-blocked); remaining word-diffs are IDO spill-home/regalloc numbering
 * driven by the 0x150 frame, not source-controllable. */
#define DI(o) (*(int *)((char *)&D_00000000 + (o)))
#define DF(o) (*(float *)((char *)&D_00000000 + (o)))
#define DP(o) ((void *)((char *)&D_00000000 + (o)))
#define SI(p, o, v) (*(int *)((char *)(p) + (o)) = (int)(v))
#define SF(p, o, v) (*(float *)((char *)(p) + (o)) = (v))

extern int gl_func_0001CA10();

void *gl_func_00064588(void *arg0, void *arg1) {
    void *base;
    void *node;
    void *slot;
    int val;

    if (arg0 != NULL ||
        (arg0 = (void *)gl_func_0001CA10((void *)0x3D4)) != NULL) {
        gl_func_0001CA10(arg0, arg1, 0, 0, 0.0f);
        SI(arg0, 0x28, (int)DP(0x0));
        base = (char *)arg0 + 0x108;
        if (base != NULL ||
            (base = (void *)gl_func_0001CA10((void *)0x180)) != NULL) {
            node = base;
            if (base != NULL ||
                (node = (void *)gl_func_0001CA10((void *)0x8)) != NULL) {
                SI(node, 0x0, (int)DP(0x223C0));
                SI(node, 0x4, 0);
            }
            val = DI(0x223D0);
            slot = (char *)base + 8;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 0.0f);
            }
            val = DI(0x223D4);
            slot = (char *)base + 0x20;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, DF(0x20D4));
            }
            val = DI(0x223D8);
            slot = (char *)base + 0x38;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 100.0f);
            }
            val = DI(0x223DC);
            slot = (char *)base + 0x50;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 0.0f);
            }
            val = DI(0x223E0);
            slot = (char *)base + 0x68;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, DF(0x20D8));
            }
            val = DI(0x223E4);
            slot = (char *)base + 0x80;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 0.0f);
            }
            val = DI(0x223E8);
            slot = (char *)base + 0x98;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, DF(0x20DC));
            }
            val = DI(0x223EC);
            slot = (char *)base + 0xB0;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, DF(0x20E0));
            }
            val = DI(0x223F0);
            slot = (char *)base + 0xC8;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 1.0f);
            }
            /* complex slot (0x20) at +0xE0: bounding-box init via a staged
             * struct {hdr=DI(0x223F4); max{1000,1000,1000}; min{-1000,-1000,
             * -1000}; {0,0,0}} copied through intermediate frame slots; the
             * Vec3 written into slot[0x10..0x18] resolves to {0,0,0}. */
            {
                struct { int hdr; float a[3]; float b[3]; float c[3]; } box;
                box.hdr = DI(0x223F4);
                box.a[0] = box.a[1] = box.a[2] = 1000.0f;
                box.b[0] = box.b[1] = box.b[2] = -1000.0f;
                box.c[0] = box.c[1] = box.c[2] = 0.0f;
                val = box.hdr;
                slot = (char *)base + 0xE0;
                if (slot != NULL ||
                    (slot = (void *)gl_func_0001CA10((void *)0x20)) != NULL) {
                    gl_func_0001CA10(slot, base, val, 1);
                    SI(slot, 0xC, 0x221F0);
                    SI(slot, 0x1C, 0);
                    SF(slot, 0x10, box.c[0]);
                    SF(slot, 0x14, box.c[1]);
                    SF(slot, 0x18, box.c[2]);
                }
            }
            val = DI(0x223F8);
            slot = (char *)base + 0x100;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 0.0f);
            }
            val = DI(0x223FC);
            slot = (char *)base + 0x118;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 1.0f);
            }
            val = DI(0x22400);
            slot = (char *)base + 0x130;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 420.0f);
            }
            val = DI(0x22404);
            slot = (char *)base + 0x148;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x18)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221D8);
                SI(slot, 0x14, 0);
                SF(slot, 0x10, 150.0f);
            }
            /* complex slot (0x20): bounding/transform object with a Vec3 */
            val = DI(0x22408);
            slot = (char *)base + 0x160;
            if (slot != NULL ||
                (slot = (void *)gl_func_0001CA10((void *)0x20)) != NULL) {
                gl_func_0001CA10(slot, base, val, 1);
                SI(slot, 0xC, 0x221F0);
                SI(slot, 0x1C, 0);
                SF(slot, 0x10, 1.0f);
                SF(slot, 0x14, 1.0f);
                SF(slot, 0x18, 0.0f);
            }
        }
        slot = (char *)arg0 + 0x39C;
        if (slot != NULL ||
            (slot = (void *)gl_func_0001CA10((void *)0x4)) != NULL) {
            SI(slot, 0x0, 0);
        }
        slot = (char *)arg0 + 0x3A0;
        if (slot != NULL ||
            (slot = (void *)gl_func_0001CA10((void *)0x4)) != NULL) {
            SI(slot, 0x0, 0);
        }
        gl_func_0001CA10(arg0);
    }
    return arg0;
}
#undef DI
#undef DF
#undef DP
#undef SI
#undef SF
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064588);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00064DEC)();
typedef struct { f32 unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00064DEC;
void gl_func_00064DEC(char *arg0) {
    Q_00064DEC sp34;
    Q_00064DEC sp54;
    Q_00064DEC sp70;
    Q_00064DEC sp7C;
    f32 spA4;
    char *sp28;
    char *sp24;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f8;
    char *temp_a0;
    char *temp_a1;
    char *temp_v0;
    char *temp_v1;

    temp_a0 = (int)arg0 + 0x2FC;
    sp28 = temp_a0;
    gl_func_00062F64(temp_a0);
    temp_a1 = (int)arg0 + 0xCC;
    sp24 = temp_a1;
    gl_func_00062F64(temp_a0, temp_a1, temp_a1);
    (*(f32*)((char*)arg0 + 0x31C)) = (f32) ((*(f32*)((char*)arg0 + 0x31C)) + (*(f32*)((char*)arg0 + 0x180)));
    (*(f32*)((char*)arg0 + 0xB4)) = (f32) ((*(f32*)((char*)arg0 + 0xB4)) + (*(f32*)((char*)arg0 + 0x318)));
    temp_v1 = (int)arg0 + 0x318;
    temp_v0 = (int)arg0 + 0x33C;
    (*(f32*)((char*)arg0 + 0xB8)) = (f32) ((*(f32*)((char*)arg0 + 0xB8)) + (*(f32*)((char*)arg0 + 0x31C)));
    (*(f32*)((char*)arg0 + 0xBC)) = (f32) ((*(f32*)((char*)arg0 + 0xBC)) + (*(f32*)((char*)arg0 + 0x320)));
    temp_f12 = (*(f32*)((char*)temp_v1 + 0x8)) - (*(f32*)((char*)temp_v0 + 0x8));
    sp70.unk8 = temp_f12;
    sp70.unk4 = (*(f32*)((char*)temp_v1 + 0x4)) - (*(f32*)((char*)temp_v0 + 0x4));
    sp70.unk0 = (*(f32*)((char*)arg0 + 0x318)) - (*(f32*)((char*)arg0 + 0x33C));
    sp7C.unk0 = sp70.unk0;
    sp7C.unk4 = (f32) sp70.unk4;
    sp7C.unk8 = (f32) sp70.unk8;
    sp54.unk0 = sp7C.unk0;
    sp54.unk4 = (f32) sp7C.unk4;
    sp54.unk8 = (f32) sp7C.unk8;
    (*(f32*)((char*)arg0 + 0x330)) = sp54.unk0;
    (*(f32*)((char*)arg0 + 0x334)) = sp54.unk4;
    (*(f32*)((char*)arg0 + 0x338)) = sp54.unk8;
    sp7C.unk0 = (*(f32*)((char*)arg0 + 0x318));
    sp7C.unk4 = (f32) (*(f32*)((char*)temp_v1 + 0x4));
    sp7C.unk8 = (f32) (*(f32*)((char*)temp_v1 + 0x8));
    (*(f32*)((char*)arg0 + 0x33C)) = sp7C.unk0;
    (*(f32*)((char*)arg0 + 0x340)) = sp7C.unk4;
    (*(f32*)((char*)arg0 + 0x344)) = sp7C.unk8;
    ((f32(*)())gl_func_00062F64)(temp_f12, sp24);
    sp7C.unk0 = (*(f32*)((char*)arg0 + 0xB4));
    sp7C.unk4 = (f32) (*(f32*)((char*)arg0 + 0xB8));
    sp7C.unk8 = (f32) (*(f32*)((char*)arg0 + 0xBC));
    (*(f32*)((char*)arg0 + 0xDC)) = sp7C.unk0;
    (*(f32*)((char*)arg0 + 0xE0)) = sp7C.unk4;
    (*(f32*)((char*)arg0 + 0xE4)) = sp7C.unk8;
    sp54.unk0 = (*(f32*)((char*)arg0 + 0xC0));
    sp54.unk4 = (f32) (*(f32*)((char*)arg0 + 0xC4));
    sp54.unk8 = (f32) (*(f32*)((char*)arg0 + 0xC8));
    (*(f32*)((char*)arg0 + 0xE8)) = sp54.unk0;
    (*(f32*)((char*)arg0 + 0xEC)) = sp54.unk4;
    (*(f32*)((char*)arg0 + 0xF0)) = sp54.unk8;
    sp34.unk0 = (*(f32*)((char*)sp24 + 0x0));
    sp34.unk4 = (s32) (*(f32*)((char*)sp24 + 0x4));
    sp34.unk8 = (s32) (*(f32*)((char*)sp24 + 0x8));
    (*(f32*)((char*)arg0 + 0xF4)) = sp34.unk0;
    (*(f32*)((char*)arg0 + 0xF8)) = sp34.unk4;
    (*(f32*)((char*)arg0 + 0x100)) = (f32) (*(f32*)((char*)arg0 + 0xD8));
    (*(f32*)((char*)arg0 + 0xFC)) = sp34.unk8;
    gl_func_00062F64(arg0, sp24);
    temp_f2 = (*(f32*)((char*)arg0 + 0x318));
    temp_f12_2 = (*(f32*)((char*)arg0 + 0x320));
    temp_f0 = (*(f32*)((char*)arg0 + 0x31C));
    temp_f8 = (temp_f2 * temp_f2) + (temp_f12_2 * temp_f12_2) + (temp_f0 * temp_f0);
    spA4 = temp_f8;
    if (temp_f8 != 0.0f) {
        temp_f0_2 = ((f32(*)())gl_func_00062F64)(temp_f8, 0);
        (*(f32*)((char*)arg0 + 0x348)) = temp_f0_2;
        (*(f32*)((char*)arg0 + 0x30C)) = (f32) ((*(f32*)((char*)arg0 + 0x318)) / temp_f0_2);
        (*(f32*)((char*)arg0 + 0x310)) = (f32) ((*(f32*)((char*)arg0 + 0x31C)) / temp_f0_2);
        (*(f32*)((char*)arg0 + 0x314)) = (f32) ((*(f32*)((char*)arg0 + 0x320)) / temp_f0_2);
        return;
    }
    (*(f32*)((char*)arg0 + 0x348)) = 0.0f;
    (*(f32*)((char*)arg0 + 0x30C)) = 0.0f;
    (*(f32*)((char*)arg0 + 0x310)) = 0.0f;
    (*(f32*)((char*)arg0 + 0x314)) = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064DEC);
#endif

#ifdef NON_MATCHING
/* gl_func_00065060: 58-insn full transform-reset + 2-dispatch (0xE8, frame 0x38).
 *
 * Decoded structure (raw-word disasm):
 *   // Initialize transform fields on self (a0):
 *   self->[0x38C] = 0xFFFF;                          // sentinel id
 *   *(float*)(self + 0x34C..0x354) = 0.0f;           // 3 floats zero
 *   *(float*)(self + 0x318..0x320) = 0.0f;           // Vec3 zero (translation)
 *   *(float*)(self + 0x2FC..0x304) = 0.0f;           // Vec3 zero (rotation x,y,z)
 *   *(float*)(self + 0x330..0x338) = 0.0f;           // Vec3 zero (scale-related)
 *   *(float*)(self + 0x390..0x398) = 1.0f;           // Vec3 = (1,1,1) (scale identity)
 *   *(float*)(self + 0x308) = 1.0f;                  // quaternion w = 1 (identity)
 *
 *   // Copy 3 ints from self->[0x318..0x320] to lui_sym->[0x10..0x18]:
 *   *(int*)(D_global + 0x10) = self->[0x318];
 *   *(int*)(D_global + 0x14) = self->[0x31C];
 *   *(int*)(D_global + 0x18) = self->[0x320];
 *
 *   // before 1st dispatch — type-pun copy self[0x318..0x320] -> self[0x33C..0x344]
 *   // (int load, float store via stack bounce sp1C):
 *   self->[0x33C..0x344] = self->[0x318..0x320];
 *   gl_func_00062F64(self);            // 1st dispatch
 *   // 2nd dispatch — copies self float fields 0x120/0x138/0x1B0 -> 0x288..0x290:
 *   *(float*)(self + 0x348) = 0.0f;
 *   self->[0x288] = *(float*)(self + 0x120);
 *   self->[0x28C] = *(float*)(self + 0x138);
 *   self->[0x290] = *(float*)(self + 0x1B0);
 *   gl_func_00062F64(self);            // 2nd dispatch
 *
 * Full transform-reset: quat (0,0,0,1), translation/rotation/scale = 0/0/1.
 * Sibling of gl_func_00065C54 (op-6 transform-reset) — same identity layout
 * at +0x2FC..+0x308 (quat) and +0x318..+0x320 (translation).
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00065060(char *arg0) {
    int sp1C0, sp1C4, sp1C8;
    *(s32 *)(arg0 + 0x38C) = 0xFFFF;
    *(f32 *)(arg0 + 0x34C) = 0.0f;
    *(f32 *)(arg0 + 0x350) = 0.0f;
    *(f32 *)(arg0 + 0x354) = 0.0f;
    *(f32 *)(arg0 + 0x318) = 0.0f;
    *(f32 *)(arg0 + 0x31C) = 0.0f;
    *(f32 *)(arg0 + 0x320) = 0.0f;
    *(f32 *)(arg0 + 0x2FC) = 0.0f;
    *(f32 *)(arg0 + 0x300) = 0.0f;
    *(f32 *)(arg0 + 0x304) = 0.0f;
    *(f32 *)(arg0 + 0x330) = 0.0f;
    *(f32 *)(arg0 + 0x334) = 0.0f;
    *(f32 *)(arg0 + 0x338) = 0.0f;
    *(f32 *)(arg0 + 0x390) = 1.0f;
    *(f32 *)(arg0 + 0x394) = 1.0f;
    *(f32 *)(arg0 + 0x398) = 1.0f;
    *(f32 *)(arg0 + 0x308) = 1.0f;
    *(s32 *)(arg0 + 0x18) |= 0x10;
    sp1C0 = *(s32 *)(arg0 + 0x318);
    sp1C4 = *(s32 *)(arg0 + 0x31C);
    sp1C8 = *(s32 *)(arg0 + 0x320);
    *(f32 *)(arg0 + 0x33C) = *(f32 *)&sp1C0;
    *(f32 *)(arg0 + 0x340) = *(f32 *)&sp1C4;
    *(f32 *)(arg0 + 0x344) = *(f32 *)&sp1C8;
    gl_func_00062F64(arg0);
    *(f32 *)(arg0 + 0x348) = 0.0f;
    *(f32 *)(arg0 + 0x288) = *(f32 *)(arg0 + 0x120);
    *(f32 *)(arg0 + 0x28C) = *(f32 *)(arg0 + 0x138);
    *(f32 *)(arg0 + 0x290) = *(f32 *)(arg0 + 0x1B0);
    gl_func_00062F64(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065060);
#endif

#ifdef NON_MATCHING
/* gl_func_00065148: 66-insn 3D affine-transform helper (size 0x108, frame 0x50).
 *
 * Performs:
 *   1. Two leading jal calls (likely matrix-composition / pre-update)
 *      jal func1(obj + 0xDC, obj + 0x294)   — sub-matrix update at +0xDC
 *      jal func2(obj + 0xDC, obj + 0x2C8)   — sub-matrix update at +0x2C8
 *   2. Bit-copies obj->[0x1F8..0x200] (Vec3 int bits) to local stack
 *      (effectively reinterprets the int-stored Vec3 as float via `lw/sw` →
 *      `lwc1` chain)
 *   3. Matrix-vector affine multiply:
 *        v_in[3] = float-bits-of(obj->[0x1F8], obj->[0x1FC], obj->[0x200])
 *        Matrix M (3 rows × 4 columns, row-major slots at +0x70+0x10*col):
 *            obj->[0x70]  obj->[0x80]  obj->[0x90]  obj->[0xA0]   ← row 0 → out[0]
 *            obj->[0x74]  obj->[0x84]  obj->[0x94]  obj->[0xA4]   ← row 1 → out[1]
 *            obj->[0x78]  obj->[0x88]  obj->[0x98]  obj->[0xA8]   ← row 2 → out[2]
 *        out[i] = M[i,0]*v_in[0] + M[i,1]*v_in[1] + M[i,2]*v_in[2] + M[i,3]
 *        // The last column (offsets 0xA0/0xA4/0xA8) is the translation
 *   4. Stores result to obj->[0x324..0x32C] (transformed Vec3)
 *
 * Notes:
 *  - "Bit-copy via lw/sw then lwc1" pattern: the input Vec3 at +0x1F8..0x200
 *    is stored as integers but reinterpreted as floats. Either the storage is
 *    union'd or the int and float fields share the same offset.
 *  - The 3 final accumulator regs ($f14, $f16, $f18) hold per-row results then
 *    swc1 into +0x324/0x328/0x32C — destination slot for transformed point.
 *  - swc1/lwc1 pair `swc1 $f4, 0x324(obj); lwc1 $f0, 0x324(obj)` is the
 *    standard IDO "move float through memory" pattern (no mov.s emit when the
 *    address-of operator is taken on adjacent stores).
 *  - The pre-matrix jal calls likely do matrix composition (apply parent
 *    transform, or recompute world-space transform from local + parent).
 *  - Pattern: this is a per-node update during scene-graph traversal. A
 *    node's local Vec3 at +0x1F8 gets transformed by the cached world matrix
 *    at +0x70..0xA8 and stored to a "transformed-position" slot at +0x324.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
// Per-node world-transform. Runs two cbs (obj+0x294/obj+0x2C8, both with
// obj+0xDC), copies the local Vec3 at obj->0x1F8..0x200 into obj->0x324..0x32C,
// then transforms it by the cached 3x3 matrix (rows at obj->0x70/0x74/0x78,
// stride 0x10) + translation obj->0xA0/0xA4/0xA8, storing back to obj->0x324..
// All FP is aligned lwc1/swc1/mul.s/add.s; reloc-blind cbs.
void gl_func_00065148(char *obj) {
    int tmp[3];
    float x, y, z;
    gl_func_00000000(obj + 0x294, obj + 0xDC);
    gl_func_00000000(obj + 0x2C8, obj + 0xDC);
    tmp[0] = *(int *)(obj + 0x1F8);
    tmp[1] = *(int *)(obj + 0x1FC);
    tmp[2] = *(int *)(obj + 0x200);
    *(float *)(obj + 0x324) = *(float *)&tmp[0];
    *(float *)(obj + 0x328) = *(float *)&tmp[1];
    *(float *)(obj + 0x32C) = *(float *)&tmp[2];
    x = *(float *)(obj + 0x324);
    y = *(float *)(obj + 0x328);
    z = *(float *)(obj + 0x32C);
    *(float *)(obj + 0x324) = *(float *)(obj + 0x70) * x + *(float *)(obj + 0x80) * y + *(float *)(obj + 0x90) * z + *(float *)(obj + 0xA0);
    *(float *)(obj + 0x328) = *(float *)(obj + 0x74) * x + *(float *)(obj + 0x84) * y + *(float *)(obj + 0x94) * z + *(float *)(obj + 0xA4);
    *(float *)(obj + 0x32C) = *(float *)(obj + 0x78) * x + *(float *)(obj + 0x88) * y + *(float *)(obj + 0x98) * z + *(float *)(obj + 0xA8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065148);
#endif

/* gl_func_00065250 — verified structural decode (Vec3-diff + double
 * struct-copy + call, 33 insns; FPU-load-order + struct-copy sp-slot
 * allocation diverges from clean C = documented sub-80 struct-copy class
 * → INCLUDE_ASM build path; struct-typing reference).
 * Struct-typing: a0 has a Vec3 @0x324 (subtrahend) and a target/object
 * @0x294 (passed to the callee); a1 is a Vec3*. Computes a1 - a0->0x324,
 * duplicates it twice on the stack, passes the last copy. Caps <80: the
 * target's specific base-then-a1 lwc1 load interleave + the 3-int struct
 * assignment lw/sw chain with exact sp-slot (52/68/84) allocation is not
 * reproduced by Vec3-local C (19/33 first pass). The documented finicky
 * struct-copy+FP-load-order class — multi-run/permuter, not a clean
 * vein win. INCLUDE_ASM is the build path (no episode). */
typedef struct Vec3_f { float x, y, z; } Vec3_f;
#ifdef NON_MATCHING
void gl_func_00065250(char *a0, Vec3_f *a1) {
    Vec3_f d, e, f;
    d.x = a1->x - *(float*)(a0 + 0x324);
    d.y = a1->y - *(float*)(a0 + 0x328);
    d.z = a1->z - *(float*)(a0 + 0x32C);
    e = d;
    f = e;
    gl_func_00000000(a0 + 0x294, &f);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065250);
#endif

#ifdef NON_MATCHING
/* gl_func_000652D8: 34-insn Vec3-diff + buf-copy chain + dispatch (0x88, frame 0x60).
 *
 * Decoded structure (raw-word disasm):
 *   diff[0] = a1[0] - *(float*)((char*)a0 + 0x324);
 *   diff[1] = a1[1] - *(float*)((char*)a0 + 0x328);
 *   diff[2] = a1[2] - *(float*)((char*)a0 + 0x32C);
 *   // 3 stack-resident Vec3 bufs (sp+0x34/+0x44/+0x54); int-by-int copy chain:
 *   buf1 = diff; buf2 = buf1;
 *   func((char*)a0 + 0x2C8, buf2);
 *
 * The triple-copy chain (sp+0x34 → sp+0x44 → sp+0x54 via lw/sw int pairs)
 * is IDO emit for 3 same-shape Vec3 locals all init'd from the same calc,
 * or ptr-laundering for type-aliasing safety.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_000652D8(int *a0, float *a1) {
    float diff[3];
    float buf1[3];
    float buf2[3];
    diff[0] = a1[0] - *(float*)((char*)a0 + 0x324);
    diff[1] = a1[1] - *(float*)((char*)a0 + 0x328);
    diff[2] = a1[2] - *(float*)((char*)a0 + 0x32C);
    buf1[0] = diff[0]; buf1[1] = diff[1]; buf1[2] = diff[2];
    buf2[0] = diff[0]; buf2[1] = diff[1]; buf2[2] = diff[2];
    gl_func_00000000((char*)a0 + 0x2C8, buf2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000652D8);
#endif

/* gl_func_00065360 - verified structural decode (58-insn transform/matrix
 * object init; dual-zero-FP-reg + a1-double-copy + 20-store grouping =
 * documented FP-regalloc/sp-scratch divergence -> INCLUDE_ASM build path;
 * HIGH struct-typing value).
 *   Vec3i s = *(Vec3i*)a1;            // a1[0..2] -> sp+36 scratch
 *   *(Vec3f*)((char*)a0+0xDC) = s;    // a0->0xDC/0xE0/0xE4 = a1 vec
 *   s = *(Vec3i*)a1;                  // re-copied (second sp pass)
 *   *(float*)(a0+0xB4) = s.x; *(float*)(a0+0xB8) = s.y;
 *   // zero block (f0/f2 = 0.0): a0-> 0xCC,0xD0,0xD4, 0xF4,0xF8,0xFC,
 *   //   0x2FC,0x300,0x304, 0x30C,0x310,0x314, 0x318,0x31C,0x320 = 0
 *   *(float*)(a0+0x308)=1.0f; *(float*)(a0+0x100)=1.0f;
 *   *(float*)(a0+0xD8)=1.0f;  *(float*)(a0+0xBC)=s.z;
 *   vt=(int*)a0->0x28; (*(fn)vt->0x14)((short)vt->0x10 + a0);  // dispatch
 * Struct-typing (high reuse - this is a transform/orientation object):
 *   a0->0xB4 (Vec3f, =a1) position-ish; a0->0xDC (Vec3f, =a1) duplicate;
 *   a0->0xBC z-component; a 4x3-ish float matrix spanning 0xCC..0xD8 (row
 *   with 0xD8=1), 0xF4..0x100 (0x100=1), 0x2FC..0x308 (0x308=1),
 *   0x30C..0x320 - i.e. THREE basis rows zeroed with their diagonal
 *   element set 1.0f (an identity-rotation init) + translation = a1.
 *   a0->0x28 vtable {fn@0x14, short@0x10} (obj-dispatch idiom, 0x14/0x10
 *   variant). Caps: IDO uses TWO FP zero regs (f0,f2 both mtc1 zero) for
 *   different store groups + copies a1 to sp scratch TWICE; clean C
 *   (one 0.0f, one struct copy) diverges across the 20-store block
 *   (FP-regalloc/sp-scratch class, not INSN_PATCH-able). INCLUDE_ASM
 *   (no episode). */
#ifdef NON_MATCHING
/* gl_func_00065360: 58-insn Vec3 transform initializer. Copies the Vec3 at a1
 * into a0's transform fields (0xDC..0xE4 and 0xB4..0xBC), zeros a block of float
 * fields, sets a few to 1.0 defaults, then dispatches a0->0x28's vtable method
 * (ptr +0x14, signed-halfword bias +0x10) with (bias + a0). RELOC-FREE (FP consts
 * + indirect jalr) -> landable with an FP/regalloc grind; the target stages the
 * Vec3 via a stack scratch (omitted here). NM (reference decode). */
struct V3i_65360 { int a, b, c; };
void gl_func_00065360(int a0, float *a1) {
    int v0;
    struct V3i_65360 tmp;
    tmp = *(struct V3i_65360 *)a1;
    *(float *)((char *)a0 + 0xDC) = *(float *)&tmp.a;
    *(float *)((char *)a0 + 0xE0) = *(float *)&tmp.b;
    *(float *)((char *)a0 + 0xE4) = *(float *)&tmp.c;
    v0 = *(int *)((char *)a0 + 0x28);
    tmp = *(struct V3i_65360 *)a1;
    *(float *)((char *)a0 + 0xB4) = *(float *)&tmp.a;
    *(float *)((char *)a0 + 0xB8) = *(float *)&tmp.b;
    *(float *)((char *)a0 + 0x304) = 0.0f;
    *(float *)((char *)a0 + 0x300) = 0.0f;
    *(float *)((char *)a0 + 0x2FC) = 0.0f;
    *(float *)((char *)a0 + 0xFC) = 0.0f;
    *(float *)((char *)a0 + 0xF8) = 0.0f;
    *(float *)((char *)a0 + 0xF4) = 0.0f;
    *(float *)((char *)a0 + 0xD4) = 0.0f;
    *(float *)((char *)a0 + 0xD0) = 0.0f;
    *(float *)((char *)a0 + 0xCC) = 0.0f;
    *(float *)((char *)a0 + 0x314) = 0.0f;
    *(float *)((char *)a0 + 0x310) = 0.0f;
    *(float *)((char *)a0 + 0x30C) = 0.0f;
    *(float *)((char *)a0 + 0x320) = 0.0f;
    *(float *)((char *)a0 + 0x31C) = 0.0f;
    *(float *)((char *)a0 + 0x318) = 0.0f;
    *(float *)((char *)a0 + 0x308) = 1.0f;
    *(float *)((char *)a0 + 0x100) = 1.0f;
    *(float *)((char *)a0 + 0xD8) = 1.0f;
    *(float *)((char *)a0 + 0xBC) = a1[2];
    (*(int (**)(int))(v0 + 0x14))(*(short *)(v0 + 0x10) + a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065360);
#endif

extern int gl_func_00000000();

void gl_func_00065448(char *a0) {
    gl_func_00000000(a0 + 0x294, a0 + 0x2FC, a0 + 0x318, *(int*)(a0 + 0x1E0));
    gl_func_00000000(a0 + 0x2C8, a0 + 0xCC, a0 + 0xB4, *(int*)(a0 + 0x1E0));
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00065494)();
typedef struct { f32 unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00065494;
#ifndef FF
#define FF(p, o) (*(f32 *)((char *)(p) + (o)))
#endif
void gl_func_00065494(f32 *arg0) {
    int sp104;
    int sp108;
    Q_00065494 sp78;
    Q_00065494 sp8C;
    Q_00065494 sp9C;
    Q_00065494 spA8;
    Q_00065494 spBC;
    Q_00065494 spDC;
    Q_00065494 spEC;
    Q_00065494 spF8;
    char **sp184;
    char **sp180;
    f32 sp17C;
    f32 sp178;
    f32 sp174;
    f32 sp170;
    f32 sp16C;
    f32 sp168;
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    f32 *sp6C;
    f32 *temp_s1;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_t1;
    f32 temp_t2;
    f32 var_f0;
    f32 var_f20;
    f32 var_f28;
    f32 var_f30;
    s32 var_s7;
    char **temp_t4;
    char **temp_t6;
    char *temp_s4;
    char *temp_v0;
    char *temp_v0_2;
    char *var_s0;
    char *var_v0;
    char *var_v0_2;

    temp_t6 = FW(arg0, 0x39C);
    var_s7 = 0;
    sp170 = 0.0f;
    sp16C = 0.0f;
    sp168 = 0.0f;
    sp17C = 0.0f;
    sp178 = 0.0f;
    sp174 = 0.0f;
    var_f28 = 0.0f;
    var_f30 = 0.0f;
    sp184 = temp_t6;
    sp180 = temp_t6;
    if (temp_t6 != 0) {
        sp184 = FW(temp_t6, 0x4);
        var_v0 = FW(temp_t6, 0x0);
    } else {
        var_v0 = 0;
    }
    var_s0 = var_v0;
    if (var_v0 != 0) {
        sp6C = (int)arg0 + 0x2FC;
        temp_s4 = (int)arg0 + 0xDC;
        do {
            sp134 = 0.0f;
            sp138 = 1.0f;
            sp13C = 0.0f;
            temp_v0 = var_s0 + 0xDC;
            *(float *)&spEC.unk0 = FF(var_s0, 0xDC);
            *(float *)&spEC.unk4 = FF(temp_v0, 0x4);
            *(float *)&spEC.unk8 = FF(temp_v0, 0x8);
            FF(var_s0, 0x120) = spEC.unk0;
            FF(var_s0, 0x124) = spEC.unk4;
            FF(var_s0, 0x128) = spEC.unk8;
            temp_f12 = FF(temp_v0, 0x8) - FF(temp_s4, 0x8);
            *(float *)&spDC.unk0 = FF(var_s0, 0xDC) - FF(arg0, 0xDC);
            *(float *)&spDC.unk8 = temp_f12;
            *(float *)&spDC.unk4 = FF(temp_v0, 0x4) - FF(temp_s4, 0x4);
            spEC.unk0 = spDC.unk0;
            spEC.unk4 = (f32) spDC.unk4;
            spEC.unk8 = (f32) spDC.unk8;
            spBC.unk0 = spEC.unk0;
            spBC.unk4 = (f32) spEC.unk4;
            spBC.unk8 = (f32) spEC.unk8;
            sp130 = spBC.unk8;
            sp12C = spBC.unk4;
            sp128 = spBC.unk0;
            ((int(*)())gl_func_00062F64)(temp_f12, sp6C, &sp128, var_s0 + 0x114);
            temp_s1 = var_s0 + 0x120;
            FF(var_s0, 0x114) = (f32) (FF(var_s0, 0x114) - sp128);
            FF(var_s0, 0x118) = (f32) (FF(var_s0, 0x118) - sp12C);
            FF(var_s0, 0x11C) = (f32) (FF(var_s0, 0x11C) - sp130);
            FF(var_s0, 0x114) = (f32) (FF(var_s0, 0x114) + FF(arg0, 0x318));
            FF(var_s0, 0x118) = (f32) (FF(var_s0, 0x118) + FF(arg0, 0x31C));
            FF(var_s0, 0x11C) = (f32) (FF(var_s0, 0x11C) + FF(arg0, 0x320));
            if (((int(*)())gl_func_00062F64)(*(int*)0, temp_s1, (f32 *)0x43C80000, &spF8) != 0) {
                FF(var_s0, 0x14C) = (s32) sp108;
                spEC.unk0 = spF8.unk0;
                spEC.unk4 = (f32) spF8.unk4;
                spEC.unk8 = (f32) spF8.unk8;
                var_f20 = sp104;
                sp13C = spEC.unk8;
                sp138 = spEC.unk4;
                sp134 = spEC.unk0;
            } else {
                var_f20 = FF(var_s0, 0x124);
                sp13C = 0.0f;
                sp138 = 1.0f;
                sp134 = 0.0f;
            }
            temp_v0_2 = FW(var_s0, 0x28);
            temp_f20 = var_f20 - FF(arg0, 0x218);
            FF(var_s0, 0x144) = temp_f20;
            ((GP_00065494)FW(temp_v0_2, 0x64))(FW(temp_v0_2, 0x60) + var_s0, temp_f20, &sp134, 0x3F800000);
            if (temp_f20 < 0.0f) {
                if (temp_f20 < var_f30) {
                    var_f30 = temp_f20;
                }
                sp168 += sp134;
                sp16C += sp138;
                var_s7 += 1;
                temp_f16 = -temp_f20;
                sp170 += sp13C;
                var_f28 += temp_f16;
                *(float *)&sp8C.unk0 = FF(var_s0, 0x120) * temp_f16;
                *(float *)&sp8C.unk4 = FF(temp_s1, 0x4) * temp_f16;
                *(float *)&sp8C.unk8 = FF(temp_s1, 0x8) * temp_f16;
                spEC.unk0 = sp8C.unk0;
                spEC.unk4 = (f32) sp8C.unk4;
                spEC.unk8 = (f32) sp8C.unk8;
                spA8.unk0 = spEC.unk0;
                spA8.unk4 = (f32) spEC.unk4;
                spA8.unk8 = (f32) spEC.unk8;
                sp174 += spA8.unk0;
                sp178 += spA8.unk4;
                sp17C += spA8.unk8;
                var_f0 = (FF(var_s0, 0x114) * sp134) + (FF(var_s0, 0x118) * sp138) + (FF(var_s0, 0x11C) * sp13C);
                if (var_f0 > 0.0f) {
                    var_f0 = 0.0f;
                }
                temp_f14 = (temp_f16 * FF(arg0, 0x290)) + (FF(arg0, 0x28C) * -var_f0);
                temp_f12_2 = sp13C * temp_f14;
                *(float *)&sp78.unk0 = sp134 * temp_f14;
                *(float *)&sp78.unk4 = sp138 * temp_f14;
                *(float *)&sp78.unk8 = temp_f12_2;
                spEC.unk0 = sp78.unk0;
                temp_t1 = sp78.unk4;
                spEC.unk4 = temp_t1;
                temp_t2 = sp78.unk8;
                sp9C.unk4 = temp_t1;
                sp9C.unk0 = (f32) spEC.unk0;
                spEC.unk8 = temp_t2;
                sp9C.unk8 = temp_t2;
                ((int(*)())gl_func_00062F64)(temp_f12_2, temp_f14, arg0, temp_s1, &sp9C);
            }
            temp_t4 = sp184;
            var_v0_2 = 0;
            sp180 = temp_t4;
            if (temp_t4 != 0) {
                sp184 = FW(temp_t4, 0x4);
                var_v0_2 = FW(temp_t4, 0x0);
            }
            var_s0 = var_v0_2;
        } while (var_v0_2 != 0);
    }
    if (var_s7 != 0) {
        temp_f2 = (f32) var_s7;
        temp_f6 = sp16C / temp_f2;
        temp_f4 = sp168 / temp_f2;
        sp16C = temp_f6;
        temp_f18 = sp170 / temp_f2;
        sp168 = temp_f4;
        sp170 = temp_f18;
        sp174 /= var_f28;
        sp178 /= var_f28;
        sp17C /= var_f28;
        temp_f0 = -var_f30 * FF(arg0, 0x288);
        sp168 = temp_f4 * temp_f0;
        sp16C = temp_f6 * temp_f0;
        sp170 = temp_f18 * temp_f0;
        ((int(*)())gl_func_00062F64)(arg0, &sp174, &sp168);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065494);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000659D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00065B40);

#ifdef NON_MATCHING
/* gl_func_00065B5C: 62-insn pure-FP quaternion/matrix arithmetic (0xF8, frame 0x30).
 *
 * CALLER-SET FLOAT CONVENTION (intra-USO non-O32): the function reads
 * $f0..$f16 directly without setting them, performing extensive FP
 * arithmetic (mul.s, sub.s, add.s, neg.s, mov.s) and writing results
 * to caller's struct via offsets in $a0 starting around 0x3B0..0x3D0.
 * Same cap class as gl_func_00010650 family.
 *
 * Decoded structure (raw-word disasm summary):
 *   // Reads caller-set floats f0, f2, f4, f6, f8, f10, f12, f14, f16
 *   // Computes ~30 mul/add/sub/neg ops producing 10+ float intermediates
 *   // Writes to:
 *   //   a0->[0x3B0..0x3D0]: 8+ output floats (transformed values)
 *   //   sp+0x00..+0x28: 10+ scratch floats (temporary registers)
 *
 * Per the FP operation count and output pattern (8 floats stored to a0->
 * [0x3B0..0x3D0]) this is likely a Quaternion-to-Matrix conversion or
 * Matrix×Matrix multiply emit. Caller passes operand floats via $f-regs
 * and gets output via the struct pointed at by $a0.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path (the
 * pure-caller-set-float convention is unreproducible from standard C —
 * IDO has no `register float x asm("$f4")` syntax).
 */
void gl_func_00065B5C(char *self_struct) {
    /* Pure-FP quaternion-or-matrix transform. Real body reads from $f0..f16
     * caller-set float regs and writes 8+ floats to self_struct+0x3B0..0x3D0.
     * Cannot byte-match — caller-set-float cap. INCLUDE_ASM is the build path. */
    (void)self_struct;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065B5C);
#endif

#ifdef NON_MATCHING
/* gl_func_00065C54: 45-insn op-6 special-case + transform-reset (0xB4, frame 0x48).
 *
 * Decoded structure (raw-word disasm):
 *   if (a1->[0] == 6) {
 *       int *src = a1->[1];
 *       float x = (float)src->[0xEC], y = (float)src->[0xF0], z = (float)src->[0xF4];
 *       func1(a0, x, y, z);
 *       // Identity-transform reset on a0:
 *       *(float*)(a0+0x2FC..+0x304) = 0.0f;          // quat x,y,z = 0
 *       *(float*)(a0+0x308) = 1.0f;                   // quat w = 1 (identity)
 *       *(float*)(a0+0x318..+0x320) = 0.0f;           // translation Vec3 = 0
 *   } else {
 *       func2(a0, a1);                                // default dispatch
 *   }
 *
 * Op-6 = "load-pos-and-reset-transform" event. Quaternion (0,0,0,1) +
 * translation (0,0,0) is a standard identity transform layout.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int a65C54(char*, float, float, float);
void gl_func_00065C54(char *a0, int *a1) {
    if (a1[0] == 6) {
        int *src = (int*)a1[1];
        float x = *(float*)((char*)src + 0xEC);
        float y = *(float*)((char*)src + 0xF0);
        float z = *(float*)((char*)src + 0xF4);
        a65C54(a0, x, y, z);
        *(float*)(a0 + 0x2FC) = 0.0f;
        *(float*)(a0 + 0x300) = 0.0f;
        *(float*)(a0 + 0x304) = 0.0f;
        *(float*)(a0 + 0x318) = 0.0f;
        *(float*)(a0 + 0x31C) = 0.0f;
        *(float*)(a0 + 0x320) = 0.0f;
        *(float*)(a0 + 0x308) = 1.0f;
    } else {
        gl_func_00000000(a0, a1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065C54);
#endif

/* gl_func_00065D08: 23-insn 7-call cascade. First call passes a0->[0xC];
 * subsequent 6 calls pass a0 itself. */
void gl_func_00065D08(int *a0) {
    gl_func_00000000(a0[0xC/4]);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000();
}

/* gl_func_00065D64: 6-call sequence. The two args 0x2240C / 0x22414 are SYMBOL
 * refs (&D + offset -> lui; addiu), not literals (lui; ori). Decode the symbol
 * (docs/IDO_CODEGEN.md#feedback-return-const-lui-addiu-vs-lui-ori). Byte-exact. */
void gl_func_00065D64(int *a0) {
    gl_func_00000000(&D_00000000, (char *)&D_00000000 + 0x2240C, 0);
    gl_func_00000000(&D_00000000, (char *)&D_00000000 + 0x22414);
    gl_func_00000000((char *)a0 + 0x108, 0);
    gl_func_00000000(&D_00000000);
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a0);
}

extern int gl_ref_00077DB0();
extern int gl_ref_00077DEC();
int gl_func_00065DDC(char *a0) {
    int scratch;
    gl_ref_00077DB0(&scratch);
    return gl_ref_00077DEC(a0 + 0x10);
}

/* 12-insn wrapper: stack scratch + 2 internal-game_libs jal calls.
 * The gl_ref_00077DB0/E28 named refs carry R_MIPS_26 relocs that the linker
 * resolves to 0x77DB0/0x77E28 (jal 0x0C01DF6C/0x0C01DF8A) — byte-exact ROM.
 * objdiff is reloc-aware so build/.o matches expected/.o without any patch. */
extern int gl_ref_00077DB0();
extern int gl_ref_00077E28();
void gl_func_00065E0C(char *a0) {
    int local;
    gl_ref_00077DB0(&local);
    gl_ref_00077E28(a0 + 0x10);
}

float game_libs_func_00065E3C(char *a0) {
    return *(float*)(a0 + 0x198);
}

extern int gl_func_00000000();
int gl_func_00065E44(char *a0) {
    return gl_func_00000000(a0 + 0x108);
}

extern int gl_func_00000000();
int gl_func_00065E64(char *a0) {
    return gl_func_00000000(a0 + 0x108);
}

extern int gl_ref_00077DB0();
extern int gl_ref_00077E98();
int gl_func_00065E84(char *a0) {
    int scratch;
    gl_ref_00077DB0(&scratch);
    return gl_ref_00077E98(a0 + 0x10);
}

/* gl_func_00065EB4: 12-insn 2-call wrapper. Both calls target func_00077DB0
 * (0x77DB0, cross-segment). Call 1 with &stack_local (out-param), call 2 with
 * a0+0x10. Byte-exact: func_00077DB0 reloc resolves to 0x77DB0 (verified
 * raw-diff=0). Successor game_libs_func_00065EE4 stays INCLUDE_ASM. */
extern void func_00077DB0();
void gl_func_00065EB4(int a0) {
    int local;
    func_00077DB0(&local);
    func_00077DB0(a0 + 0x10);
}
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00065EE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065F08);

#ifdef NON_MATCHING
/* gl_func_0006612C: magic-value spin-handshake helper (0xAC, frame 0x20).
 * Re-derived 2026-06-20 (agent-b): the prior "caller-set $a2 cap" comment was
 * WRONG — $a2 is set in-function (`lui a2,0x1234; ori a2,2`) before the third
 * call. Callee is gl_func_00062F64 (local 2-arg K&R int fn), called directly.
 */
void gl_func_0006612C(int *self) {
    while (gl_func_00062F64(self, (char *)self[10] + 8) != 0x12340004) {
    }
    gl_func_00062F64(self, (char *)self[10] + 8, 0x12340002);
    while (gl_func_00062F64(self, (char *)self[10] + 8) != 0x12340003) {
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006612C);
#endif

/* 10-insn 1-arg call wrapper: arg-homes caller's a0, then calls
 * gl_func_00000000(&D + 0x2246C). MATCH: the call arg is a SYMBOL reference
 * (&D_00000000 + 0x2246C) emitting lui %hi; addiu %lo, not a literal
 * (int*)0x2246C which gives lui; ori. Decode the symbol, don't literal-match
 * (docs/IDO_CODEGEN.md#feedback-return-const-lui-addiu-vs-lui-ori). Byte-exact. */
extern int gl_func_00000000();
void gl_func_000661D8(int a0_unused) {
    gl_func_00000000((char*)&D_00000000 + 0x2246C);
}

/* gl_func_00066200/00066208: 2 save-arg-sentinel stubs RECOVERED 2026-05-28
 * from the 000661D8 gap (dropped — no .s, missing from build). `void f(int
 * a0){}` compiles byte-exact to `jr ra; sw a0, 0(sp)` at -O2
 * (docs/IDO_CODEGEN.md#feedback-ido-empty-int-arg-fn-save-arg-sentinel). */
void gl_func_00066200(int a0) {}
void gl_func_00066208(int a0) {}

#ifdef NON_MATCHING
/* gl_func_00066210: 21-insn 5-call sequence with buffer + chain helper.
 * Cap (2026-05-14): target doesn't reset $a0 between calls 1 and 2.
 * Built emits explicit `li a0, 1` for both = 88 vs 84 bytes.
 *
 * Typed extern (gl_proto_66210) attempted as workaround — different
 * function name AND no arg-share-across-calls optimization. The K&R-
 * float-call workaround doesn't extend to "share int arg between
 * adjacent calls" because the typed extern still produces independent
 * call sites with full arg setup.
 * 95.0% / +4 CAP (2026-05-31): build emits a SECOND `addiu a0,1` for the second
 * `gl_func(1)` call; target sets a0=1 ONCE and REUSES it across both calls (the
 * second call's a0=1 survives the first jal in target's schedule). Tried swapping
 * the two calls (saved= first) -> 16 diffs WORSE; IDO re-emits a0=1 regardless of
 * call order. Deep IDO delay-slot/const-reuse scheduling, not C-controllable here.
 * Also a saved/buf stack-slot swap (sp+24<->28). Do not re-grind the call order. */
int gl_func_00066210(int a0, int a1) {
    int saved;
    int buf;
    gl_func_00000000(1);
    saved = gl_func_00000000(1);
    gl_func_00000000(&buf, 4);
    gl_func_00000000(a1, &buf);
    gl_func_00000000(saved);
    return buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066210);
#endif

#ifdef NON_MATCHING
/* gl_func_00066264: 33-insn aligned/unaligned-length dispatch (0x84, frame 0x30).
 *
 * Decoded structure (raw-word disasm):
 *   if ((len & 3) == 0) {
 *       // Aligned path: single direct call
 *       func0(a0=src, a1=a1, a2=len);
 *   } else {
 *       // Unaligned path: split into aligned-prefix + 4-byte-temp-buf tail
 *       int aligned = len & ~3;       // round down to 4-byte boundary
 *       int rem     = len & 3;         // remainder
 *       int tmpbuf[4];                 // sp+0x20 scratch
 *       func1(src, a1);                // pre-setup call (a0=src, a1=a1)
 *       func2(&tmpbuf, src + aligned, 4);              // read 4 bytes via tmpbuf
 *       func3(&tmpbuf, dst_a0 + aligned, rem);         // write `rem` bytes
 *   }
 *
 * The unaligned-tail copy uses a 4-byte scratch buffer at sp+0x20 to
 * load the partial word and write only the byte count specified by `rem`
 * (= len & 3). Classic unaligned-tail handler for word-only IO devices.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00066264(int dst_a0, int a1, int *src, int len) {
    int rem = len & 3;
    if (rem == 0) {
        gl_func_00000000(src, a1, len);
    } else {
        int aligned = len & ~3;
        int tmpbuf[4];
        gl_func_00000000(src, a1);
        gl_func_00000000(&tmpbuf, (char*)a1 + aligned, 4);
        gl_func_00000000(&tmpbuf, (char*)dst_a0 + aligned, rem);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066264);
#endif

extern int gl_func_00000000();

void gl_func_000662E8(int a0, int a1, int a2) {
    int r = gl_func_00000000(1);
    gl_func_00000000();
    gl_func_00000000(r);
    gl_func_00000000(a1, a2);
}

extern int gl_func_00000000();
void gl_func_00066330(int a0, int a1, int a2, int a3) {
    gl_func_00000000(a1, a2, a3);
}

extern int gl_func_00000000();
void gl_func_00066364(int a0) {
    gl_func_00000000();
}

extern int gl_func_00000000();
int gl_func_00066384(int a0) {
    return gl_func_00000000((char *)&D_00000000 + 0x22498, a0);
}

extern int gl_func_00000000();
int gl_func_000663AC() {
    return gl_func_00000000((char *)&D_00000000 + 0x224B0);
}

extern int gl_func_00000000();
void gl_func_000663D0(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

/* Standard int-reader accessor template (15 insns / 0x3C). Split out of
 * splat-bundled gl_func_00066404 (was 32 insns / 0x80 with 3 jr-ra) into
 * separate symbols via split-fragments.py: gl_func_00066404 (this clean
 * int-reader), game_libs_func_00066440 (8-insn fragment), and
 * game_libs_func_00066460 (9-insn fragment, predecessor-state-dependent).
 * The 2 split-off fragments stay INCLUDE_ASM (chain-state, no clean C). */
extern int gl_func_00000000();
void gl_func_00066404(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

/* game_libs_func_00066440: circular doubly-linked-list remove-self (17 insns;
 * the 00066460 tail was splat's jr-ra over-split of the v1==prev==a0 early
 * return, merged back here). The predecessor gl_func_00066404 ends `jr ra; nop`
 * (a complete separate int-reader), so this reads a0 fresh and is its own fn.
 * The combined self-link `a0[0] = (a0[1] = a0)` is the permuter-found form that
 * schedules the unlink's `next->prev = prev` to load a0->0 before a0->4 (no
 * plain-statement C variant flips that load order). */
int game_libs_func_00066440(int *a0) {
    int *next = (int*)a0[1];
    int *prev = (int*)a0[0];
    if (next != prev) {
        goto unlink;
    }
    if (a0 != prev) {
        goto unlink;
    }
    return 0;
unlink:
    prev[1] = (int)next;
    ((int*)a0[1])[0] = a0[0];
    {
        int old_prev = a0[0];
        a0[0] = (a0[1] = (int)a0);
        return old_prev;
    }
}

#ifdef NON_MATCHING
/* gl_func_00066484: 20-insn doubly-linked-list insert-before. Split from
 * bundled 36-insn parent on 2026-05-15 (extracted game_libs_func_000664D4
 * and game_libs_func_000664F0 as no-prologue chain-state fragments).
 *
 * If a0 is currently not in a list (a0->prev == a0->next), splice a0
 * before a1 in the doubly-linked list:
 *   - a0->next = a1 (anchor)
 *   - a0->prev = a1->prev (anchor's old prev)
 *   - (anchor's old prev)->next = a0
 *   - a1->prev = a0
 * Otherwise (a0 already linked) call placeholder gl_func_00000000().
 *
 * Cap: target uses `beql t6, t7, body` with `lw t8, 0(a1)` in the
 * delay-likely slot + duplicate `lw t8, 0(a1)` at offset 0x28 (between
 * `b end` and the body target — unreachable in normal flow). This is
 * the documented "beql with delay-slot pre-load" pattern from
 * docs/IDO_CODEGEN.md#feedback-ido-sparse-switch-beql-preload-unreachable
 * (sparse-switch-style dispatch — unreachable from plain C if/else, which
 * emits `bne + nop` without the pre-load). 19/20 word-match.
 *
 * Tried 2026-05-15: if-then-return form, if/else form, inverted-cond form
 * — all emit `bne` not `beql` with no duplicate load. Cap is structural. */
void gl_func_00066484(int *a0, int *a1) {
    if (a0[1] == a0[0]) {
        int t8 = a1[0];
        a0[1] = (int)a1;
        a0[0] = t8;
        ((int*)a1[0])[1] = (int)a0;
        a1[0] = (int)a0;
    } else {
        gl_func_00000000();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066484);
#endif

void game_libs_func_000664D4(int *a0, int *a1) {
    a0[1] = a1[1];
    a0[0] = (int)a1;
    ((int *)a1[1])[0] = (int)a0;
    a1[1] = (int)a0;
}

void game_libs_func_000664F0(int *a0, int *a1) {
    ((int *)a0[1])[0] = a1[0];
    ((int *)a1[0])[1] = a0[1];
    a1[0] = (int)a0;
    a0[1] = (int)a1;
}

/* gl_func_00066514: DynArr{void*array@0; int len@4; int cap@8} constructor
 * (f1 of the now-split 0xA0 bundle; .s is 0x58 = this fn only). Reloc-blind
 * jals -> gl_func_00000000 placeholder (alloc(0xC) + alloc_array(cap*8)).
 * IDO still picks $a2 as the working register (param→$a2 copy) but with the
 * a0-source pseudo the spill of $a2 across the 2nd alloc lands at 0x18 (a0's
 * home), not 0x20 (a2's home). Lever: drop the unused 3rd param; reuse a0.
 * See docs/IDO_CODEGEN.md#feedback-ido-drop-working-reg-param-spill-follows-source-pseudo. */
int gl_func_00066514(int a0, int a1) {
    if (a0 == 0) {
        a0 = gl_func_00000000(0xC);
        if (a0 == 0) goto ret;
    }
    *(int *)(a0 + 4) = 0;
    *(int *)(a0 + 8) = a1;
    *(int *)a0 = gl_func_00000000(a1 << 3);
ret:
    return a0;
}

/* Array slot-append: if idx (a0->4) < cap-1 (a0->8 - 1), advance idx and return
 * &base[idx] (base=a0->0, stride 8); else (full) return 0. Merged: the append
 * block was splat-split off as game_libs_func_0006658C (UNSHARED); merged back
 * (0x20 -> 0x38). Inlining a0[2]-1 (no `cap` local) keeps the limit temp in $t6,
 * matching the target register allocation. */
int game_libs_func_0006656C(int *a0) {
    int idx = a0[1];
    if ((unsigned)idx >= (unsigned)(a0[2] - 1)) {
        return 0;
    }
    a0[1] = idx + 1;
    return a0[0] + idx * 8;
}

void game_libs_func_000665A4(int *a0, int a1) { *(int*)a0 = a1; *(int*)((char*)a0 + 8) = 0; *(int*)((char*)a0 + 4) = 0; }

/* gl_func_000665B4: alloc-retry cache-lookup loop. MATCHED 2026-06-20 via
 * chained-assignment `v1 = *(p+4) = alloc(...)` forcing store-before-call-arg
 * (the prior "permuter-floored scheduler tie" cap was wrong — it was a
 * C-formulation issue). The two jal targets are the relocatable-USO placeholder
 * gl_func_00000000 (correct .text bytes; R_MIPS_26 supplied by USO loader).
 *
 * Original decode notes (bundle context):
 * 2-function bundle.
 *
 * SUB-FUNCTION 1 (0x665B4..0x66620, 27 insns, 0x6C bytes) — retry-alloc-cache lookup:
 *     void *f1(Obj *obj) {
 *         while (1) {
 *             if (obj->cache == NULL) {            // [0x4]
 *                 obj->cache = alloc(0);           // arg = 0
 *                 obj->refcount = obj->refcount+1; // [0x8]++
 *             }
 *             void *result = lookup_cached(obj->cache);  // jal <func>, no args
 *             if (result != NULL) return result;
 *             obj->cache = NULL;                   // invalidate, retry
 *         }
 *     }
 *   Pattern: lazy-init cache with retry-on-failure. The beql loop-back at the
 *   end uses the lw $a0, 0x4($s0) as delay-slot-likely (only executes on
 *   loop-back to refresh the cache pointer for the next iteration's check).
 *
 * SUB-FUNCTION 2 (0x66620..0x66674, 21 insns, 0x54 bytes) — linked-list-remove-by-key:
 *     void f2(LinkedList *list, int key) {
 *         Node *prev = NULL;
 *         Node *curr = list->head;  // [0]
 *         if (!curr) return;
 *         while (1) {
 *             if (curr->key == key) {  // [0]
 *                 if (prev) prev->next = curr->next;  // [4]
 *                 else      list->head = curr->next;
 *                 return;
 *             }
 *             prev = curr;
 *             curr = curr->next;
 *             if (!curr) return;
 *         }
 *     }
 *   Pattern: standard singly-linked-list remove-by-key with head + middle
 *   unlink paths. Uses bnel branch-likely for both the loop-skip ("not match,
 *   advance") and the unlink-head-vs-middle dispatch.
 *
 * Notes:
 *  - 3 internal `jr $ra` (at f1 epilogue 0x66618, f2 head-unlink 0x66648,
 *    f2 middle-unlink 0x66654) + final jr at 0x6666C. Bundle confirmed.
 *  - f2 layout uses 4-insn nodes: Node { int key; Node *next; } — 8 bytes each.
 *  - Now split to single fn; decoded 2026-05-24: alloc-retry loop (92.6%).
 *    SOLE residual = a 2-insn scheduling swap: target does sw v0,4(s0) THEN
 *    move a0,v0 (call-arg setup); -O2 C schedules move THEN sw. Both depend on
 *    the alloc result; permuter floored at base score 70 (not crackable). */
extern int gl_func_00000000();
int gl_func_000665B4(int a0) {
    int v1;
    int v0;
    do {
        v1 = *(int *)(a0 + 4);
        if (v1 == 0) {
            v1 = *(int *)(a0 + 4) = gl_func_00000000(0, *(int *)a0);
            *(int *)(a0 + 8) += 1;
        }
        v0 = gl_func_00000000(v1);
        if (v0 == 0) {
            *(int *)(a0 + 4) = 0;
        }
    } while (v0 == 0);
    return v0;
}


/* game_libs_func_00066620: leaf-branch-past-end CAP per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00066620);

/* game_libs_func_00066650: 3-insn `v1[1] = v0[1]; return` field-copy.
 * No prologue — both $v0 and $v1 are caller-set state-ptr args. IDO C
 * can't emit functions that read v0/v1 as inputs (the calling convention
 * is a0..a3). CAP class per feedback_caller_set_int_reg_cap_1080_game_libs.
 * Default INCLUDE_ASM keeps ROM byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00066650);

/* game_libs_func_0006665C: 6-insn tail-fragment of a list-walk loop:
 *   move v1,v0; lw v0,4(v0); bnel v0,zero,-0x34; lw t6,0(v0); jr ra; nop
 * Caller-set $v0 (loop iterator) + backward branch -0x34 to 0x66634
 * (BEFORE this .s start 0x6665C — splat boundary error). The actual
 * function spans from earlier (where the loop top + initial $v0 are) to
 * here. CAP class — needs splat boundary correction. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006665C);

#ifdef NON_MATCHING
/* gl_func_00066674: 27-insn append-to-linked-list + 3-stub BUNDLE (0xAC declared,
 * real fn ends at 0x6C; 0x70-0xAC is 3 small leaf stubs bundled by splat).
 *
 * Decoded structure (real fn, raw-word disasm):
 *   node = factory(*D_X);                            // allocate via factory
 *   node->[0] = data;                                 // data field
 *   node->[0x4] = NULL;                               // next pointer
 *   if (*head == NULL) {                              // empty list
 *       *head = node;
 *   } else {
 *       cur = *head;
 *       while (cur->[0x4] != NULL) cur = cur->[0x4]; // walk to tail
 *       cur->[0x4] = node;                            // append
 *   }
 *
 * Marker said "43-insn" but the real function is 27 insns (0x6C). The
 * remaining 16 insns (0x70-0xAC) are 3 bundled leaf stubs that splat
 * couldn't separate: D_Y setter (sw a0), D_Z getter (lw return), and a
 * 3rd small fn (lui v0+addiu return). Fragment-split required for byte-
 * exact; structural decode + bundle note is the one-tick output.
 * INCLUDE_ASM remains build path.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md.
 */
void gl_func_00066674(int **head, int data) {
    extern int D_X_66674;
    int *node = (int*)gl_func_00000000(D_X_66674);
    node[0] = data;
    node[1] = 0;
    if (*head == 0) {
        *head = node;
    } else {
        int *cur = *head;
        while (cur[1] != 0) {
            cur = (int*)cur[1];
        }
        cur[1] = (int)node;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066674);
#endif

/* ROM-truth order in this run (base 666E4..6671C): setter, getter,
 * 6-zero pad, then the 666FC addr-return — the addr-return's CODE sits at
 * link 66714 in the base ROM despite its 666FC name (splat-era naming).
 * Reordered 2026-06-10 during the full-ROM word-diff drive. */

/* game_libs_func_000666E4: setter for the segment-base int global (*D = a0).
 * Byte-exact plain C — the single &D_00000000 ref is offset-0, so objdiff's
 * reloc-aware compare resolves it to addr 0 and matches the reloc-blind
 * expected. Plain (compiled in BOTH build paths) so it counts in report.json
 * (was trapped in the #else branch -> fuzzy=None / uncounted). */
void game_libs_func_000666E4(int a0) {
    *(int *)&D_00000000 = a0;
}

/* game_libs_func_000666F0: getter for the segment-base int global (return *D).
 * Byte-exact plain C (offset-0 &D_00000000 ref, reloc-aware match like 000666E4).
 * Was trapped as INCLUDE_ASM in block A's #else -> fuzzy=None / uncounted. */
int game_libs_func_000666F0(void) {
    return *(int *)&D_00000000;
}

/* Returns the address constant 0x41310 (a code label inside game_libs).
 * MATCHED 2026-06-10 via the deferred undefined_syms route: D_gl_00041310
 * = 0x41310 in undefined_syms_auto.txt makes &-of-symbol emit the
 * ADDRESS-style lui+addiu (lui v0,4; jr ra; addiu v0,v0,0x1310) --
 * `return 0x41310` as a literal emits lui+ORI instead. See IDO_CODEGEN
 * #feedback-return-const-lui-addiu-vs-lui-ori. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/_pad_pre_666FC.s")
extern char D_gl_00041310;
int game_libs_func_000666FC(void) {
    return (int)&D_gl_00041310;
}

/* gl_func_00066720: chunked transfer w/ 10000-byte (0x2710) limit per call.
 * MATCHED 2026-06-20: sibling of gl_func_00066794 — same shared-limit/chunk
 * lever. The limit (0x2710) and the per-iteration chunk SHARE one register
 * (s0): a SINGLE `chunk` variable initialized ONCE outside the loop, only
 * narrowed in-loop by `if (len < chunk) chunk = len`. Reusing the single var
 * (no separate `limit` + ternary) makes IDO load `li s0,0x2710` ONCE in the
 * prologue and reuse it for the loop `sltu at,s1,s0` (register cmp, not the
 * constant-folded sltiu). Differs from 66794 only in the post-call update
 * order: here `dst += chunk` is the LAST source statement so it lands in the
 * bne delay slot. jal is the relocatable-USO placeholder gl_func_00000000. */
void gl_func_00066720(char *src, char *dst, unsigned int len) {
    unsigned int chunk = 10000;
    if (len == 0) return;
    do {
        if (len < chunk) {
            chunk = len;
        }
        gl_func_00000000(src, dst, chunk);
        len -= chunk;
        src += chunk;
        dst += chunk;
    } while (len != 0);
}

/* gl_func_00066794: chunked transfer w/ 10000-byte (0x2710) limit per call.
 * MATCHED 2026-06-20: the prior "0x2710 folds to sltiu" cap was wrong. The
 * limit (0x2710) and the per-iteration chunk SHARE one register (s0): IDO
 * loads it ONCE before the loop, and the `if (count < chunk) chunk = count`
 * only narrows it (full chunks keep s0=0x2710 so the next `sltu` reuses it).
 * Reusing the single `chunk` variable (no separate `limit` + ternary) makes
 * IDO emit `li s0,0x2710` (prologue) + `sltu at,s1,s0` (loop) — register cmp,
 * not the constant-folded sltiu. The jal is the relocatable-USO placeholder
 * gl_func_00000000 (correct .text; R_MIPS_26 supplied by the USO loader). */
void gl_func_00066794(char *dst, char *src, unsigned int count) {
    unsigned int chunk = 10000;
    if (count == 0) return;
    do {
        if (count < chunk) {
            chunk = count;
        }
        gl_func_00000000(dst, src, chunk);
        count -= chunk;
        src += chunk;
        dst += chunk;
    } while (count != 0);
}
/* game_libs_func_00066808 (2-word splat mis-split: lui t6,0; lw t6,0(t6)) was
 * the stolen prologue of gl_func_00066810 — forward-merged into it. */
void gl_func_00066810(int a0) {
    int v0 = (*(int(**)())((char*)*(void**)&D_00000000 + 0x40))();
    if (v0 < 0) {
        gl_func_00000000((char*)&D_00000000 + 0x20F0, a0, v0);
    }
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00066850)();
void gl_func_00066850(s32 arg0) {
    u32 temp_a1;
    u32 temp_a1_2;
    char *temp_v0;

    gl_func_00062F64(0xFE);
    gl_func_00062F64(0x96, 0x41688U, 0x415C0, 0x32);
    gl_func_00062F64();
    gl_func_00062F64(0xA0);
    gl_func_00062F64(0x42);
    gl_func_00062F64(1);
    temp_v0 = *(int*)0;
    temp_a1 = FW(temp_v0, 0xC);
    if (temp_a1 != 0) {
        gl_func_00062F64(0x2114, temp_a1, FW(temp_v0, 0x14), FW(temp_v0, 0x1C));
    }
    temp_a1_2 = FW((*(int*)0), 0x8);
    if (temp_a1_2 != 0) {
        gl_func_00062F64(0x2138, temp_a1_2, FW((*(int*)0), 0x10));
    }
    gl_func_00062F64(FW((*(int*)0), 0x0), FW((*(int*)0), 0x4));
    gl_func_00062F64(0x2154, (u32) (FW((*(int*)0), 0x0) + 0x80000000) >> 0xA);
    FW((*(int*)0), 0x80) = 0;
    FW((*(int*)0), 0x34) = 0;
    FW((*(int*)0), 0x84) = 0;
    FW((*(int*)0), 0x98) = 0;
    FW((*(int*)0), 0x9C) = 0;
    FW((*(int*)0), 0x94) = 0;
    gl_func_00062F64(0x216C);
    gl_func_00062F64();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066850);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000669AC);

#ifdef NON_MATCHING
/* gl_func_000669B8: 38-insn 5-call dispatch w/ caller-set $v0/$v1 (0x98, frame 0x20).
 *
 * CALLER-SET $v0 AND $v1 CONVENTION (intra-USO non-O32): the function
 * starts with `lw $t6, 0x30($v0)` and `lw $t7, 0x0($v1)` — both v0 and v1
 * are read without being set in this function. Same cap class as
 * gl_func_000744CC (caller-set $v0) and gl_func_000601DC (caller-set $t6).
 * Pattern: caller pre-loads register-passed state pointers, callee
 * dereferences directly. IDO C has no way to express receive-in-$v0.
 *
 * Decoded structure (raw-word disasm):
 *   t6 = caller_v0->[0x30];                          // load state field
 *   caller_v0->[0x34] = t6;                          // copy 0x30 → 0x34
 *   vt = (*caller_v1)->[0x44];                       // vtable lookup via *v1
 *   (*vt)();                                          // 1st indirect call
 *
 *   t8 = *D_X;
 *   vt2 = t8->[0x40];
 *   v0 = (*vt2)();                                    // 2nd indirect call (returns int)
 *
 *   if (v0 != 0) {
 *       func3(&D_BASE + 0x218C, v0);                 // banner call only when nonzero
 *   }
 *
 *   func4(&D_BASE + 0x21A4, saved_v0);                // 4th call
 *
 *   D_Y_ptr = *D_Y;
 *   func5(&D_BASE + 0x21AC, D_Y_ptr->[0], D_Y_ptr->[1]);  // 5th call
 *
 * Two indirect (jalr) + 3 direct (jal) calls. The 2-vtable lookups in
 * sequence (caller_v1 then global D_X) suggest a "self.dispatch then
 * global-singleton.dispatch" pattern.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path
 * (caller-set $v0/$v1 unreproducible from standard C).
 */
void gl_func_000669B8(void) {
    extern int *v0_caller_state;
    extern int **v1_caller_state;
    extern int D_00000000;
    extern int **D_X_669B8, **D_Y_669B8;
    int rc;
    int *state = v0_caller_state;
    int **vt = v1_caller_state;
    int (*fn1)(void), (*fn2)(void);
    state[0x34 / 4] = state[0x30 / 4];
    fn1 = (int(*)(void))(*vt)[0x44 / 4];
    fn1();
    fn2 = (int(*)(void))(*D_X_669B8)[0x40 / 4];
    rc = fn2();
    if (rc != 0) {
        gl_func_00000000((char*)&D_00000000 + 0x218C, rc);
    }
    gl_func_00000000((char*)&D_00000000 + 0x21A4, state);
    gl_func_00000000((char*)&D_00000000 + 0x21AC, (*D_Y_669B8)[0], (*D_Y_669B8)[1]);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000669B8);
#endif

/* gl_func_00066A50: 40-insn panic/fatal handler — canary-reset + halt (size 0xA0, frame 0x20).
 *
 * COMPANION FUNCTION: this is the PANIC-INIT counterpart to gl_func_00066AF0
 * (the canary verifier). 00066A50 RESETS the canary slots to 0x12345678 and
 * halts; 00066AF0 VERIFIES them and prints an error string on mismatch.
 *
 * Decoded structure (raw-word disasm):
 *   void f(int a0_save) {
 *       // STAGE 1: debug-print with file/line context
 *       *(sp+0x10) = (char*)&D_00000000 + 0x41310;  // file-name string ptr
 *       *(sp+0x14) = 0xA;                             // line number (10)
 *       debug_print(
 *           (char*)&D_00000000 + 0x3F160,  // arg0: format string
 *           2,                              // arg1: severity / category
 *           (char*)&D_00000000 + 0,         // arg2: another string
 *           0                               // arg3: nul
 *       );
 *
 *       // STAGE 2: canary slot reset to magic 0x12345678
 *       *(int*)((char*)&D_00000000 + 0x3F310) = 0x12345678;
 *       *(int*)((char*)&D_00000000 + 0x3F314) = 0x12345678;  // matches 0x66AF0 slot 1
 *
 *       // STAGE 3: invoke cleanup hooks (likely fflush / sync-and-shutdown)
 *       hook1((char*)&D_00000000 + 0x3F160);   // re-pass format string
 *       hook2(0, 0);                            // null-arg cleanup
 *
 *       // STAGE 4: halt forever (`b .` infinite loop)
 *       while (1) ;  // emit: b -1; nop
 *
 *       // STAGE 5: UNREACHABLE — IDO-emitted standard epilogue
 *       // (5 padding nops, then lw $ra / addiu $sp / jr $ra / nop)
 *       // (3-insn lead-in fragment at end: lui $t6,0x4; lw $t6,-0xCF0($t6);
 *       //  lui $at,0x1234 — incomplete read-canary-start sequence, dead code)
 *   }
 *
 * Notes:
 *  - Pairs with reference_1080_canary_sentinel_pattern.md: this is the SETTER
 *    half of the canary system (00066AF0 = checker).
 *  - `b -1; nop` is the unconditional halt loop (1000FFFF / 00000000).
 *  - Trailing nops + dead epilogue + 3-insn canary-read fragment all live
 *    inside the declared 0xA0 region; they're IDO unreachable-code emission.
 *    NOT a too-big-bundle (only one jr $ra).
 *  - File-name string at D+0x41310 (likely "<filename>.c") and format string
 *    at D+0x3F160 ("PANIC: %s line %d" or similar).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#ifdef NON_MATCHING
/* gl_func_00066A50: 37-insn panic/hang. Logs an error via the (collapsed)
 * callback (fmt @ 0x3F160, args 2/&global/0 + stack 0x41310,0xA), writes the
 * 0x12345678 magic into the canary words at 0x3F310/0x3F314 (the canary SETTER,
 * sibling of the gl_func_00066AF0 checker), logs again, calls a halt, then loops
 * forever (b .). NM (reference decode): collapsed-placeholder calls + collapsed
 * D ref + fixed absolute addresses (raw-.word game_libs reloc depression). */
extern int D_00000000;
void gl_func_00066A50(int a0) {
    gl_func_00062F64((char *)((char *)&D_00000000 + 0x3F160), 2, &D_00000000, 0,
                     (char *)((char *)&D_00000000 + 0x41310), 0xA);
    *(int *)((char *)&D_00000000 + 0x3F310) = 0x12345678;
    *(int *)((char *)&D_00000000 + 0x3F314) = 0x12345678;
    gl_func_00062F64((char *)((char *)&D_00000000 + 0x3F160));
    gl_func_00062F64(0, 0);
    for (;;) {
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066A50);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00066AE4);

#ifdef NON_MATCHING
/* gl_func_00066AF0: 29-insn debug-canary triple-check helper (size 0x74, frame 0x18).
 *
 * Decoded structure (raw-word disasm):
 *   // Pre-check: caller-set $at gates the first canary read
 *   if ((($at_caller | 0x5678) == 0x40000)) {  // gate (caller-supplied flag)
 *       t7 = *(int*)((char*)&D_00000000 + 0x3F314);  // canary slot 1
 *       if (t7 != 0x12345678)
 *           debug_print((char*)&D_00000000 + 0x21BC);  // error msg 1
 *   }
 *   t8 = *(int*)((char*)&D_00000000 + 0x414C0);      // canary slot 2
 *   if (t8 == 0x12345678) {
 *       t9 = *(int*)((char*)&D_00000000 + 0x414C4);  // canary slot 3
 *       if (t9 != 0x12345678)
 *           debug_print((char*)&D_00000000 + 0x21D8);  // error msg 2 (or 3)
 *   }
 *   return;
 *
 * Pattern: debug-assert / memory-canary check. Three 32-bit slots at
 *   D+0x3F314, D+0x414C0, D+0x414C4 each hold a magic sentinel 0x12345678.
 *   On mismatch, the helper prints an error message from D+0x21BC / D+0x21D8.
 *
 * Notes:
 *  - $at is caller-set (upper bits used by `ori $at, $at, 0x5678` at insn[2]
 *    with NO prior `lui` in this function). Fits the caller-set-int-reg cap
 *    class (feedback_caller_set_int_reg_cap_1080_game_libs.md). $at-as-arg
 *    is a unusual variant beyond the previously-documented $v0/$v1/$t6/$a2.
 *  - 0x12345678 is the canary sentinel value (classic 1234-5678 marker).
 *  - The error messages at D+0x21BC and D+0x21D8 are debug strings (likely
 *    "Memory canary corrupted" or similar — verify via objdump --full-contents).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path
 *    (caller-set $at can't be expressed in IDO C).
 */
extern int D_00000000;
// Canary/sentinel verifier. Checks a caller-set value + two fixed slots against
// the magic 0x12345678, asserting (cb with an error string) on mismatch:
// if (x != magic || *0x3F314 != magic) report(&D+0x21BC);
// if (*0x414C0 != magic || *0x414C4 != magic) report(&D+0x21D8);
// The magic's high half (lui 0x1234) is set by a predecessor for the first
// compare (caller-set), so that compare won't byte-match; the rest matches.
void gl_func_00066AF0(int x) {
    if (x != 0x12345678 || *(int *)0x0003F314 != 0x12345678) {
        gl_func_00000000((char *)&D_00000000 + 0x21BC);
    }
    if (*(int *)0x000414C0 != 0x12345678 || *(int *)0x000414C4 != 0x12345678) {
        gl_func_00000000((char *)&D_00000000 + 0x21D8);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066AF0);
#endif

/* gl_func_00066B64: 28-insn 3-call init + magic-write.
 *   func(a0);
 *   func(&D+0x41310, 1, &D, a0, &D+0x415C0, 1);
 *   D[0x414C0] = 0x12345678; D[0x414C4] = 0x12345678;
 *   func(&D + 0x41310);
 *
 * 93% cap — address-materialization form (split-or-constant class,
 * docs/IDO_CODEGEN.md#feedback-ido-split-or-constant). Target wants the
 * data addrs as `lui rX,0x4; addiu rX,rX,LO` (arithmetic, no reloc,
 * shared base reused for both magic stores via sw,DISP(base)). Three
 * C forms tested 2026-05-16, all wrong:
 *   1. `&D_00000000 + off` (extern reloc): %hi/%lo pair → spurious
 *      `addiu rX,rX,0` (+1 insn, 29 vs 28).
 *   2. `(void*)0xABS` literal: `lui;ori` (bitwise) not `lui;addiu`.
 *   3. `&D_000414C0` absolute-symbol (undefined_syms): still %hi/%lo
 *      reloc → same +0 addiu (absolute-symbol trick works for R_MIPS_26
 *      jal targets, NOT for data %hi/%lo).
 * No C form yields target's non-reloc arithmetic `lui;addiu`. Stays NM;
 * INCLUDE_ASM is the build path. */
extern int func_00000000();
extern int D_00000000;
#ifdef NON_MATCHING
void gl_func_00066B64(int *a0) {
    func_00000000(a0);
    func_00000000((void*)0x41310, 1, (void*)0, a0, (void*)0x415C0, 1);
    *(int*)0x414C0 = 0x12345678;
    *(int*)0x414C4 = 0x12345678;
    func_00000000((void*)0x41310);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066B64);
#endif

/* gl_func_00066BD4: 23-insn 3-call chain with mixed-arg middle call. */
void gl_func_00066BD4(int a0) {
    int *p = &a0;  /* &param forces the dead arg-home sw a0,0x20(sp) */
    gl_func_00000000(*p);
    gl_func_00000000((char*)&D_00000000 + 0x41310, 1, &D_00000000, 0,
                     (char*)&D_00000000 + 0x415C0, 1);
    gl_func_00000000((char*)&D_00000000 + 0x41310);
}

/* 8-insn: stores arg to D_00000000, calls gl_func_00000000(0).
 * Splat originally bundled 2 trailing empty (jr ra; nop) leaves —
 * split off 2026-05-15 as game_libs_func_00066C58 / _00066C60 below. */
extern int D_00000000;
void gl_func_00066C30(int a0) {
    D_00000000 = a0;
    gl_func_00000000(0);
}

void game_libs_func_00066C58(void) {}

void game_libs_func_00066C60(void) {}

#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00066C30_pad.s")

#ifdef NON_MATCHING
/* gl_func_00066C74: 56-insn 4-slot struct-array init + 2-call setup (0xE0, frame 0x30).
 *
 * Decoded structure (raw-word disasm):
 *   *(int*)0x000416B0 = 2;                            // global flag
 *   self->[0x13E8] = 0;
 *   func1(self + 0x11B0, self + 0x11C8, 4);           // setup call
 *   func2(5, self + 0x11B0, (char*)0x40000 + 0x16B0); // 2nd setup call
 *   self->[0x13F0] = 0;
 *   self->[0x13C8] = 3; self->[0x13CC] = 3; self->[0x13D0] = 3; self->[0x13D4] = 3;
 *   // Per-slot init (4 slots, structured as int + 4 bytes + 1 short):
 *   for (i = 0; i < 4; i++) {
 *       self->bytes[0x13D8 + i] = 0;                  // slot.[0]
 *       self->bytes[0x13DC + i] = 0;                  // slot.[4]
 *       self->shorts[0x13E0 + i*2] = 0;               // slot.[8]
 *   }
 *   func3(self);                                       // post-init
 *   func4(self + 0x1000, 6, self);                    // 3-arg final call
 *
 * 4-slot struct-array at self->[0x13C8..0x13E7], each slot has int +
 * 4 bytes + 2 shorts (or 1 short padded). The unrolled per-slot init
 * writes byte fields with offsets +0x10/+0x14 and short field +0x18
 * (relative to slot base).
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. 84.1 -> 85.12 (2026-05-31): the 3rd arg of
 * func2 is the ADDRESS `&D_00000000 + 0x416B0`, not the literal `(char*)0x416B0`
 * — the literal emits `ori a2,a2,0x16B0`, the address form `addiu a2,a2,5808`
 * (matching target). NOTE: only the ARG; routing the `*(int*)0x416B0=2` store
 * through &D too CSEs the base and regresses (79.9%) — leave the store a literal.
 * Residual: at-vs-t7 store-base regalloc + ra-save/field-init block scheduling.
 * INCLUDE_ASM remains build path.
 */
void gl_func_00066C74(char *self) {
    *(volatile int*)0x000416B0 = 2;
    *(int*)(self + 0x13E8) = 0;
    gl_func_00000000(self + 0x11B0, self + 0x11C8, 4);
    gl_func_00000000(5, self + 0x11B0, (char*)&D_00000000 + 0x416B0);
    *(int*)(self + 0x13F0) = 0;
    {
        int i;
        for (i = 0; i < 4; i++) {
            *(int*)(self + 0x13C8 + i*4) = 3;
            self[0x13D8 + i] = 0;
            self[0x13DC + i] = 0;
            *(short*)(self + 0x13E0 + i*2) = 0;
        }
    }
    gl_func_00000000(self);
    gl_func_00000000(self + 0x1000, 6, (char*)&D_00000000, self, self + 0x1000, 14);
    gl_func_00000000(self + 0x1000);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066C74);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00066D54)();
void gl_func_00066D54(char *arg0) {
    u8 sp53;
    s32 temp_s0;
    s32 temp_s4;
    s32 temp_v0;
    s32 var_s1;
    char *temp_s0_2;
    char *temp_s2;

    temp_s4 = (int)arg0 + 0x11B0;
    gl_func_00062F64(temp_s4, (int)arg0 + 0x13EC, (int)arg0 + 0x1218);
    var_s1 = 0;
    do {
        temp_s0 = 1 << var_s1;
        if (FW(arg0, 0x13EC) & temp_s0) {
            temp_s2 = (int)arg0 + (var_s1 * 4);
            if (!(FW(temp_s2, 0x121B) & 8)) {
                gl_func_00062F64(0x22570, var_s1);
                sp53 = 0;
                gl_func_00062F64(temp_s4, (s32) &sp53);
                if (sp53 & temp_s0) {
                    temp_s0_2 = (int)arg0 + (var_s1 * 0x68) + 0x1228;
                    temp_v0 = gl_func_00062F64(temp_s4, (s32) temp_s0_2, var_s1);
                    if (temp_v0 == 0xA) {
                        if (gl_func_00062F64(temp_s4, (s32) temp_s0_2, var_s1) != 0) {
                            gl_func_00062F64(0x22584);
                            FW(temp_s2, 0x13C8) = 0;
                        } else {
                            gl_func_00062F64(0x2258C);
                            FW(temp_s2, 0x13C8) = 2;
                            FW(((int)arg0 + var_s1), 0x13DC) = 1;
                        }
                    } else if (temp_v0 == 0) {
                        gl_func_00062F64(0x22594);
                        FW(temp_s2, 0x13C8) = 1;
                    }
                } else {
                    gl_func_00062F64(0x22598);
                }
                gl_func_00062F64(0x225A0);
            }
        }
        var_s1 += 1;
    } while (var_s1 != 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066D54);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00066EEC)();
void gl_func_00066EEC(s32 **arg0) {
    s32 *sp54;
    u8 sp4F;
    s16 var_s0;
    s32 **temp_s1;
    s32 **temp_s4;
    s32 **var_s0_2;
    s32 **var_s1;
    s32 temp_v1;
    s32 var_s6;

    var_s6 = 0;
    temp_s4 = (int)arg0 + 0x11B0;
loop_1:
    gl_func_00062F64(temp_s4, &sp54, 1);
    temp_v1 = *(int*)sp54;
    if (temp_v1 == 0) {
        goto loop_1;
    }
    if (temp_v1 == 5) {
        sp4F = 0;
        gl_func_00062F64(temp_s4, (s32 **) &sp4F);
        var_s0 = 0;
        do {
            if (sp4F & (1 << var_s0)) {
                temp_s1 = (int)arg0 + (var_s0 * 0x68) + 0x1228;
                if (gl_func_00062F64(temp_s4, temp_s1, var_s0) == 0) {
                    gl_func_00062F64(temp_s1);
                }
            }
            var_s0 += 1;
        } while (var_s0 != 4);
        var_s6 = 1;
        goto loop_1;
    }
    if (temp_v1 == 6) {
        goto loop_1;
    }
    if (temp_v1 == 1) {
        var_s0_2 = 0;
        if (var_s6 == 0) {
            var_s1 = arg0;
            do {
                gl_func_00062F64(arg0, var_s0_2, *(s16*)((char*)var_s1 + 0x13E0));
                var_s0_2 += 1;
                var_s1 += 2;
            } while (var_s0_2 != (s32 **)4);
        }
        gl_func_00062F64(temp_s4);
        FW(arg0, 0x13E8) = 0;
        goto loop_1;
    }
    if (temp_v1 == 4) {
        goto loop_1;
    }
    if (temp_v1 != 2) {
        goto loop_1;
    }
    gl_func_00062F64((int)arg0 + 0x1200);
    if (var_s6 == 0) {
        gl_func_00062F64(arg0);
    }
    FW(arg0, 0x13E8) = 1;
    goto loop_1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066EEC);
#endif

void gl_func_00067084(char *a0, int a1, int a2) {
    char *v1 = a0 + a1;
    if (v1[0x13DC] == 0) return;
    if ((unsigned char)v1[0x13D8] == a2) return;
    if (a2 != 0) {
        if (gl_func_00000000((a0 + 0x1228) + 104 * a1) == 0) {
            v1[0x13D8] = 3;
        }
    } else {
        if (gl_func_00000000((a0 + 0x1228) + 104 * a1) != 0) {
            if (v1[0x13D8] > 0) {
                v1[0x13D8]--;
            }
        }
    }
}

extern int gl_func_00000000();
extern int gl_ref_000416C0;

void gl_func_00067134(char *a0) {
    gl_ref_000416C0 = 6;
    gl_func_00000000(a0 + 0x11B0, &gl_ref_000416C0, 1);
}

extern int gl_func_00000000();
extern int gl_ref_000416D0;

void gl_func_00067168(char *a0) {
    gl_ref_000416D0 = 5;
    gl_func_00000000(a0 + 0x11B0, &gl_ref_000416D0, 1);
}

/* gl_func_0006719C was 18-insn 2-function bundle. Split via
 * split-fragments.py 2026-05-08:
 *   parent gl_func_0006719C (14 insns / 0x38, conditional+unconditional call)
 *   game_libs_func_000671D4 (5 insns / 0x10, indexed short-array store) */
extern int gl_func_00000000();
void gl_func_0006719C(int *a0) {
    if (*(int*)((char*)a0 + 0x13E8) == 0) {
        gl_func_00000000(a0);
    }
    gl_func_00000000(a0);
}

void game_libs_func_000671D4(short *a0, int a1, int a2) {
    *(short*)((char*)a0 + (a1 * 2) + 0x13E0) = a2;
}

#ifdef NON_MATCHING
/* NON_MATCHING: expected copies a0 to a3 via `or a3, a0, zero`; IDO does not
 * emit the copy from plain C, and `register T asm("$7")` (GCC extension) is
 * not supported by IDO cfe. (Sole residual at 92.7%.)
 * DO NOT rewrite the `&gl_ref_000416E0` alias to `&D_00000000 + 0x416E0`: the
 * distinct alias CSEs the address into ONE register (shared by the `*p=1` store
 * and the call arg, matching the target's single `lui a1`); the &D+offset form
 * makes IDO re-materialize it twice (two luis) and regresses this to 67.7%. */
extern int gl_func_00000000();
extern int gl_ref_000416E0;
void gl_func_000671E4(char *a0) {
    *(int*)(a0 + 0x13E8) = 0;
    *(int*)&gl_ref_000416E0 = 1;
    gl_func_00000000(a0 + 0x11B0, &gl_ref_000416E0, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000671E4);
#endif

#ifdef NON_MATCHING
/* gl_func_00067220: 17-insn (0x44) busy-wait loop on a0->[0x13E8].
 *   while (a0->[0x13E8] == 0) gl_func_00000000();
 *
 * 4-word residual (off 0x4..0x10), 88% byte-exact. Body+control-flow now
 * byte-exact via the `while` form (matches bnel + the loop's lw-via-s0).
 * Residual is purely the PROLOGUE-SCHEDULE tie: target emits
 * `sw s0; move s0,a0; sw ra; lw t6,0x13E8(s0)`, build emits
 * `sw ra; sw s0; lw t6,0x13E8(a0); move s0,a0`. The first field load is
 * scheduled via a0 (pre-move) by IDO's as1. Tried while/do-while/for-comma-
 * init, char* held-base, register int*s0, int v named-local — all hold the
 * 4-word prologue tie. Cap class: IDO as1 prologue-schedule choice, not
 * C-controllable here (2026-06-21 agent-i). */
void gl_func_00067220(char *a0) {
    char *s0 = a0;
    while (*(int *)(s0 + 0x13E8) == 0) {
        gl_func_00000000();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067220);
#endif

#ifdef NON_MATCHING
/* gl_func_00067264: 50-insn counter-gated 4-slot bit-dispatch + 2-stub BUNDLE
 * (0x10C declared, real fn ~50 insns ending at jr ra @0xCC; rest are 2 small stubs).
 *
 * Decoded fn 1 (real gl_func_00067264):
 *   self->[0x13F0]++;                                 // increment call counter
 *   if (self->[0x13F0] < 32) return;                  // skip until counter wraps
 *   self->[0x13F0] = 0;                                // reset
 *
 *   // Pre-init local 1-byte buffer at sp+0x4F, fetch active-slot bitmask:
 *   byte slot_mask;
 *   func_a(self + 0x11B0, &slot_mask);                // returns mask via &local
 *
 *   // Dispatch over 4 slots (s6=4 sentinel):
 *   for (i = 0; i < 4; i++) {
 *       if (slot_mask & (1 << i)) {                   // sllv-based bit test
 *           entry = self + i * 104 + 0x1228;          // 104-byte stride entry
 *           int rc = func_b(self + 0x11B0, entry, i);
 *           if (rc == 0) {
 *               func_c(entry);
 *               self[i*104 + 0x13DC] = 1;            // claim slot
 *           } else {
 *               self[i*104 + 0x13DC] = 0;            // clear slot
 *           }
 *       }
 *   }
 *
 * The 104-byte entry stride matches the alloc-empty-slot pattern in
 * gl_func_00062484 (also 104-byte) — same array layout. Combined with
 * a 32-call timer (`self->[0x13F0] >= 32`), this is a periodic
 * slot-refresher: every 32 calls, check the bitmask and refresh each
 * active slot's flag at +0x13DC.
 *
 * Bundled siblings @0xD0-0x10C: 2 small leaf functions (need fragment-split):
 *   - byte-array indexed lookup: `return self->[i*4 + 0x13C8]`
 *   - byte-load: `return *(byte*)(self + 0x13EC)`
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00067264(int *self) {
    char slot_mask;
    int i;
    int counter = self[0x13F0 / 4];
    self[0x13F0 / 4] = counter + 1;
    if ((u32)counter < 31U) return;                  // (sltiu < 31 → branch when not yet 31+)
    self[0x13F0 / 4] = 0;
    slot_mask = 0;
    gl_func_00000000((char*)self + 0x11B0, &slot_mask);
    for (i = 0; i < 4; i++) {
        if (slot_mask & (1 << i)) {
            char *entry = (char*)self + i * 104 + 0x1228;
            int rc = (int)gl_func_00000000((char*)self + 0x11B0, entry, i);
            if (rc == 0) {
                gl_func_00000000(entry);
                ((char*)self)[i * 104 + 0x13DC] = 1;
            } else {
                ((char*)self)[i * 104 + 0x13DC] = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067264);

#endif

int game_libs_func_00067358(char *a0, int a1) {
    return *(int *)((char *)a0 + a1 * 4 + 0x13C8);
}

int game_libs_func_00067368(char *a0) {
    return *(unsigned char *)(a0 + 0x13EC);
}

/* gl_func_00067370 + the 1-word ROM pad after it: pad sat between two
 * matched C fns (no emission host; 1-word blocks emit +4). Converted to
 * one combined [fn+pad] INCLUDE block (route b, 2026-06-10); the proven
 * matching C is preserved below. */
#ifdef NON_MATCHING
void gl_func_00067370(void) {
    gl_func_00000000();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067370);
#endif

/* gl_func_00067394: 26-insn rv-store + sign-flip-or-assert + call.
 *   rv = func(a0, a1); a0->[0x64] = rv;
 *   if (a1 > 0) a1 = -a1; else func(&D, a0);
 *   func(a0, a1); return 1; */
int gl_func_00067394(int *a0, int a1) {
    int rv = func_00000000(a0, a1);
    a0[0x64/4] = rv;
    if (a1 >= 0) {
        func_00000000(&D_00000000, a0);
    } else {
        a1 = -a1;
    }
    func_00000000(a0, a1);
    return 1;
}

void gl_func_000673FC(int *a0, int a1) {
    *(short *)((char *)a0 + 0x74) = 0;
    a0[0x78 / 4] = 0;
    *(short *)((char *)a0 + 0x76) = 0;
    a0[0x6C / 4] = -1;
    a0[0x68 / 4] = 0;
    a0[0x4C / 4] = 0;
    a0[0x34 / 4] = a1;
    a0[0x30 / 4] = 0;
    gl_func_00000000(a0);
    a0[0x28 / 4] = 0;
    a0[0x2C / 4] = 0;
    a0[0x38 / 4] = 0;
    a0[0x3C / 4] = 0;
    a0[0x40 / 4] = 0;
    a0[0x70 / 4] = 0;
    *(float *)((char *)a0 + 0x0) = 0.0f;
    *(float *)((char *)a0 + 0x4) = 0.0f;
    *(float *)((char *)a0 + 0x44) = 0.0f;
    *(float *)((char *)a0 + 0x48) = 0.0f;
}

/* gl_func_00067470: 27-insn 1-or-2 call dispatcher. Byte-exact (verified:
 * non-reloc words match ROM; the gl_func_00000000 calls are runtime-patched
 * jal-0 placeholders = the correct ROM bytes). No episode — placeholder relocs.
 * First call's arg uses absolute address 0x225D8 (lui $a0,0x2; addiu $a0,0x25D8). */
void gl_func_00067470(int* a0, int a1) {
    gl_func_00000000((char *)&D_00000000 + 0x225D8, a0[13], a1);
    if (a0[30] != 0) {
        gl_func_00000000(&gl_data_00000000, a0[13] - 1, 0);
    }
    a0[26] = a1;
}

extern int gl_func_00000000();
void gl_func_000674DC(int *a0) {
    int v = a0[0xD];
    if (v != 0) {
        gl_func_00000000(gl_func_00000000, v - 1, 0);
    }
}

int gl_func_00067510(int *a0) {
    int v = a0[0xD];
    if (v != 0) {
        return gl_func_00000000(&D_00000000, v - 1);
    }
    return 0;
}

/* gl_func_00067550: 21-insn bit-test helper. If a0->[0x34] != 0:
 * call gl_func(&D_0, a0); return v0 & (1 << (a0->[0x34] + 31)); else return 0.
 *
 * MATCH (2026-06-21, agent-b, permuter): the residual was the commutative-AND
 * operand order at 0x40 — target `and v0,v0,t0` (call-result v0 as rs), build
 * emitted `and v0,t0,v0`. The decomp-permuter found that wrapping the AND's
 * v0 operand in a `(0, v0)` comma expression forces v0 to be re-materialized as
 * the rs operand at coloring time, flipping the AND to the target order.
 * Byte-exact in-tree (reloc-filtered word-compare: 0 diffs). */
int gl_func_00067550(int *a0) {
    int v0 = 0;
    if (a0[0x34 / 4] != 0) {
        v0 = gl_func_00000000(&D_00000000, a0);
        return (1 << (a0[0x34 / 4] + 31)) & ((0, v0));
    }
    return v0;
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000675A4)();
void gl_func_000675A4(char *arg0) {
    f32 temp_f0;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f0_2;
    f64 temp_f14;
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_2;
    u32 temp_t3;
    char *temp_v0_3;

    temp_v1 = FW(arg0, 0x34);
    if ((temp_v1 != 0) && (FW(arg0, 0x68) == 0)) {
        temp_t0 = FW(arg0, 0x78);
        if (temp_t0 != 0) {
            temp_v0 = (*(s16*)((char*)arg0 + 0x74));
            (*(s16*)((char*)arg0 + 0x74)) = (s16) (temp_v0 + 1);
            gl_func_00062F64(0, temp_v1 - 1, *(u8*)(temp_t0 + temp_v0), arg0);
            if (*(u8*)(FW(arg0, 0x78) + (*(s16*)((char*)arg0 + 0x74))) == 0xFF) {
                FW(arg0, 0x78) = 0;
                (*(s16*)((char*)arg0 + 0x76)) = 0;
            }
        }
    }
    temp_t4 = FW(arg0, 0x10);
    FW(arg0, 0x10) = 0;
    FW(arg0, 0x14) = temp_t4;
    if (FW(arg0, 0x68) == 0) {
        if (FW(arg0, 0x34) != 0) {
            gl_func_00062F64(0, arg0);
        }
        if (FW(arg0, 0x70) != 0) {
            (*(s8*)((char*)arg0 + 0x8)) = (s8) -(*(s8*)((char*)arg0 + 0x8));
        }
        if (FW(arg0, 0x4C) != 0) {
            temp_t3 = FW(arg0, 0x50) + 1;
            FW(arg0, 0x50) = temp_t3;
            if (temp_t3 >= (u32) FW(arg0, 0x54)) {
                FW(arg0, 0x4C) = 0;
            }
            temp_v0_2 = FW(arg0, 0x4C);
            if (temp_v0_2 == 2) {
                *(s8*)(FW(arg0, 0x5C) + (FW(arg0, 0x50) * 4)) = (*(s8*)((char*)arg0 + 0x8));
                *(s8*)((FW(arg0, 0x5C) + (FW(arg0, 0x50) * 4)) + 0x1) = (*(s8*)((char*)arg0 + 0x9));
                *(s16*)((FW(arg0, 0x5C) + (FW(arg0, 0x50) * 4)) + 0x2) = FW(arg0, 0x10) & FW(arg0, 0x6C) & 0x1700;
                *(int*)(FW(arg0, 0x58)) = FW(arg0, 0x50);
            } else if (temp_v0_2 == 1) {
                temp_v0_3 = FW(arg0, 0x5C) + (FW(arg0, 0x50) * 4);
                FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | *(s16*)((char*)temp_v0_3 + 0x2));
                (*(s8*)((char*)arg0 + 0x8)) = *(s8*)((char*)temp_v0_3 + 0x0);
                (*(s8*)((char*)arg0 + 0x9)) = *(s8*)((char*)temp_v0_3 + 0x1);
            }
        }
        temp_f0 = (f32) (*(s8*)((char*)arg0 + 0x8)) / 80.0f;
        (*(f32*)((char*)arg0 + 0x0)) = temp_f0;
        (*(f32*)((char*)arg0 + 0x4)) = (f32) ((f32) (*(s8*)((char*)arg0 + 0x9)) / 80.0f);
        if (temp_f0 < 0.0f) {
            var_f0 = -(*(f32*)((char*)arg0 + 0x0));
        } else {
            var_f0 = (*(f32*)((char*)arg0 + 0x0));
        }
        temp_f14 = *(f64*)((char*)&D_00000000 + 0x2200);
        if ((f64) var_f0 < temp_f14) {
            (*(f32*)((char*)arg0 + 0x0)) = 0.0f;
        }
        temp_f2 = (*(f32*)((char*)arg0 + 0x4));
        if (temp_f2 < 0.0f) {
            var_f0_2 = -temp_f2;
        } else {
            var_f0_2 = temp_f2;
        }
        if ((f64) var_f0_2 < temp_f14) {
            (*(f32*)((char*)arg0 + 0x4)) = 0.0f;
        }
    }
    if (FW(arg0, 0x3C) != 0) {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | FW(arg0, 0x40));
        FW(arg0, 0x3C) = 0;
        (*(f32*)((char*)arg0 + 0x0)) = (f32) (*(f32*)((char*)arg0 + 0x44));
        (*(f32*)((char*)arg0 + 0x4)) = (f32) (*(f32*)((char*)arg0 + 0x48));
    }
    if ((f64) (*(f32*)((char*)arg0 + 0x0)) > 0.5) {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | 0x4000);
    } else {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) & ~0x4000);
    }
    if ((f64) (*(f32*)((char*)arg0 + 0x0)) < -0.5) {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | 0x10000);
    } else {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) & 0xFFFEFFFF);
    }
    if ((f64) (*(f32*)((char*)arg0 + 0x4)) > 0.5) {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | 0x2000);
    } else {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) & ~0x2000);
    }
    if ((f64) (*(f32*)((char*)arg0 + 0x4)) < -0.5) {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) | 0x8000);
    } else {
        FW(arg0, 0x10) = (s32) (FW(arg0, 0x10) & 0xFFFF7FFF);
    }
    temp_v0_4 = FW(arg0, 0x10);
    temp_v1_2 = FW(arg0, 0x14);
    temp_a0 = FW(arg0, 0x38);
    temp_t6 = temp_v0_4 & ~temp_v1_2;
    FW(arg0, 0x18) = temp_t6;
    FW(arg0, 0x1C) = (s32) (~temp_v0_4 & temp_v1_2);
    if (temp_a0 != 0) {
        temp_v0_5 = temp_a0 - 1;
        FW(arg0, 0x38) = temp_v0_5;
        if (temp_v0_5 > 0) {
            temp_v0_6 = FW(arg0, 0x24) & temp_t6;
            FW(arg0, 0x20) = temp_v0_6;
            if (temp_v0_6 != 0) {
                FW(arg0, 0x38) = 0;
            }
        }
    } else {
        temp_v0_7 = FW(arg0, 0x18);
        FW(arg0, 0x20) = 0;
        FW(arg0, 0x24) = temp_v0_7;
        if (temp_v0_7 != 0) {
            FW(arg0, 0x38) = 0xA;
        }
    }
    (*(s16*)((char*)arg0 + 0x7C)) = (s16) *(u8*)((char*)&D_00000000 + ((u32)(FW(arg0, 0x10) & 0x1E000) >> 0xD));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000675A4);
#endif

/* gl_func_000679BC: 21-insn 4-arg field-init helper. Fills 5 fields in
 * a0 (offsets 0x4C, 0x50, 0x54, 0x58, 0x5C) and clears *a3, then calls
 * gl_func(&D_0 + 0x225EC, a0->[0x34]). */
void gl_func_000679BC(int *a0, int a1, int a2, int *a3) {
    a0[0x5C/4] = a1;
    a0[0x50/4] = 0;
    a0[0x54/4] = a2;
    a0[0x58/4] = (int)a3;
    *a3 = 0;
    a0[0x4C/4] = 2;
    gl_func_00000000((char*)&D_00000000 + 0x225EC, a0[0x34/4]);
}

extern int gl_func_00000000();

void gl_func_00067A10(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x5C) = a1;
    *(int*)(a0 + 0x50) = 0;
    *(int*)(a0 + 0x54) = a2;
    *(int*)(a0 + 0x4C) = 1;
    gl_func_00000000((char *)&D_00000000 + 0x22604, *(int*)(a0 + 0x34));
}

/* gl_func_00067A54: too-big-N-function-bundle (declared size 0x74, 29 words).
 * Splat grouped 3 distinct functions + a 3-insn trailing fragment under one symbol.
 * Candidate for split-fragments.py — needs the script to recurse on each newly-
 * split-off boundary until no more splits happen.
 *
 * SUB-FUNCTION 1 (0x67A54 .. 0x67A8C, 15 insns, 0x3C bytes):
 *     void f1(Obj *a0, int new_int, int new_short) {
 *         if (a0->[0x78] == new_int)            return;   // beql to epilogue
 *         if (new_short < a0->[0x76]) [hu]    return;   // bnel to epilogue
 *         debug_print();                                   // jal <func>
 *     }
 *   Pattern: condition-then-debug-print helper. Likely "report change-of-state"
 *   when (new_int, new_short) escalates beyond stored (a0->[0x78], a0->[0x76]).
 *
 * SUB-FUNCTION 2 (0x67A90 .. 0x67A9C, 4 insns, 0x10 bytes):
 *     void f2(Obj *a0, int new_int, short new_short) {
 *         *(int  *)((char*)a0 + 0x78) = new_int;
 *         *(short*)((char*)a0 + 0x76) = new_short;
 *         *(short*)((char*)a0 + 0x74) = 0;
 *     }
 *   Pattern: paired setter for the f1 fields. (0x74 cleared as a "dirty" flag.)
 *
 * SUB-FUNCTION 3 (0x67AA0 .. 0x67ABC, 7 insns, 0x1C bytes):
 *     void f3(Obj *a0) {
 *         *(int*)((char*)a0 + 0x10) = 0;
 *         *(int*)((char*)a0 + 0x14) = 0;
 *         *(int*)((char*)a0 + 0x18) = 0;
 *         *(int*)((char*)a0 + 0x1C) = 0;
 *         *(int*)((char*)a0 + 0x20) = 0;
 *         *(int*)((char*)a0 + 0x24) = 0;
 *     }
 *   Pattern: clear-6-int-fields zero-init helper.
 *
 * TRAILING FRAGMENT (0x67ABC .. 0x67AC8, 3 insns):
 *     nop; nop; mtc1 $zero, $f12.
 *   Incomplete fragment (no prologue, no jr) — likely prologue-stub of a
 *   subsequent function whose body lives further in. Variant of
 *   feedback_splat_too_big_incomplete_fragment_tail.md.
 *
 * Notes:
 *  - Two `jr $ra` inside the declared region at 0x67A88 (f1 end) and 0x67A98 (f2)
 *    plus a third at 0x67AB4 (f3 end). 3 jr $ra = 3 functions bundle.
 *  - Splat boundary-issue family per docs/MATCHING_WORKFLOW.md
 *    "too-big-N-function-bundle".
 *  - Now split to 0x3C (this fn only); decoded 2026-05-24. */
extern int gl_func_00000000();
void gl_func_00067A54(int a0, int a1, int a2) {
    if (a1 == *(int *)(a0 + 0x78)) {
        return;
    }
    if (a2 < *(short *)(a0 + 0x76)) {
        return;
    }
    gl_func_00000000(a0, a1, a2);
}

void game_libs_func_00067A90(char *a0, int a1, int a2) {
    *(int *)(a0 + 0x78) = a1;
    *(short *)(a0 + 0x76) = a2;
    *(short *)(a0 + 0x74) = 0;
}

void game_libs_func_00067AA0(int *a0) {
    a0[8] = 0;
    a0[4] = 0;
    a0[5] = 0;
    a0[6] = 0;
    a0[7] = 0;
    a0[9] = 0;
}

/* ROM-truth order: 67A90 (4w), 67AA0 (7w), THEN this block (2 pad zeros +
 * the 44806000 mtc1-zero alt-entry word at link 67AC4, falling through into
 * gl_func_00067AC8). Was INCLUDEd before the two active fns, rotating the
 * whole 67A90..67AC4 run. Reordered 2026-06-10 (full-ROM word-diff drive). */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067ABC);

extern int gl_func_00067AC8_inner(float, float);

void gl_func_00067AC8(float a) {
    gl_func_00067AC8_inner(a, a);
}

/* Varargs empty stub (sibling of matched gl_func_0006F144). */
void gl_func_00067AE8(int a0, ...) {
}

/* game_libs_func_00067B04: 29-insn (0x74) string-compare/prefix-match loop.
 * BOUNDARY MERGED 2026-06-02: splat over-split the loop tail as a separate
 * symbol (00067B40, 14-insn whose `bnel` branches backward to 0x67B1C inside
 * this body; 67B04's own beql/beq branch forward into it at 0x40/0x54/0x58).
 * Absorbed 67B40's 14 words into 67B04 (0x3C -> 0x74, ending exactly at the
 * next func 0x67B78); dropped the 67B40 symbol. Branch-verified complete.
 * Reloc-blind USO body stays INCLUDE_ASM. */
#ifdef NON_MATCHING
/* String-difference predicate. Walks both strings while bytes match;
 * returns 1 the moment a byte differs. If one string ends first, returns
 * whether the OTHER still has chars (i.e. differing lengths -> nonzero).
 * Equal strings -> 0. Leaf, byte (lbu) compares. */
s32 game_libs_func_00067B04(unsigned char *arg0, unsigned char *arg1) {
    int c0 = *arg0;
    int r;

    if ((c0 != 0) && (*arg1 != 0)) {
        do {
            int x1 = *arg1;
            int x0 = *arg0;
            arg1++;
            arg0++;
            if (x1 != x0) {
                return 1;
            }
            c0 = *arg0;
        } while (!((c0 == 0) || (*arg1 == 0)));
    }
    r = c0 != 0;
    if (r == 0) {
        r = *arg1 != 0;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067B04);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00067B78: naive substring search returning a bool. a0 =
 * haystack, a1 = needle. Saves the needle start (v0); compares needle char vs
 * haystack char, advancing both on match and resetting the needle (a1 = start)
 * on mismatch while the haystack keeps advancing. Returns 1 when the needle is
 * exhausted (full match) or *needle==0 at exit, else 0. Unsigned-char loads.
 * 64.8% NM (from 13.8%): the single shared `return *a1==0` epilogue + combined
 * `if(*a0&&*a1){ do{}while(*a0&&*a1) }` guard collapsed 3 separate returns into
 * one (+51pp). Residual: the target makes per-iter copies (v1=a0, a2=a1) and
 * compares through them + re-reads *a0 after the needle reset, and its epilogue
 * is `sltu;sltiu` (normalize-then-negate) vs my single sltiu — codegen detail,
 * multi-pass. Correct algorithm preserved. */
int game_libs_func_00067B78(unsigned char *a0, unsigned char *a1) {
    unsigned char *v0 = a1;
    int cn, ch;
    if (*a0 != 0 && *a1 != 0) {
        do {
            cn = *a1;
            ch = *a0;
            a1++;
            a0++;
            if (cn != ch) {
                a1 = v0;
            }
        } while (*a0 != 0 && *a1 != 0);
    }
    return *a1 == 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067B78);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00067BDC: strcpy returning dst+len (ptr to the copied NUL).
 * Logic exact; near-miss: target is 16 insns (peeled first iteration + a
 * redundant per-iteration `move v1,a1; lbu 0(v1)` / `move v0,a0; sb 0(v0)` —
 * separate pre-increment pointer copies), while clean `*dst++=*src++` do-while
 * compiles to a tight 7-insn loop. The verbose -O1-ish codegen isn't
 * reproducible from clean -O2 C. Reloc-free. */
char *game_libs_func_00067BDC(char *dst, char *src) {
    char c;
    do {
        c = *src++;
        *dst++ = c;
    } while (c != 0);
    return dst - 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067BDC);
#endif

#ifdef NON_MATCHING
/* strcat-variant: find end of dst, append src (incl. NUL), return pointer to the
 * appended NUL (= stpcpy-of-the-tail). Recognized libc function (reloc-free).
 * Byte-match deferred (multi-run): target is 29 insns vs this 20 — it uses a
 * messier IDO codegen (initial *dst peek, a v1=src dual-use lag pointer, and
 * branch-likely bnezl in the strlen loop) that the clean C form doesn't
 * reproduce. Same 67xxx libc-string family as 67C98 (strncpy). */
char *game_libs_func_00067C1C(char *dst, char *src) {
    char *d = dst;
    while (*d) {
        d++;
    }
    while (*src) {
        *d++ = *src++;
    }
    *d = 0;
    return d;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067C1C);
#endif

int game_libs_func_00067C90(int a0) {
    return a0 & 0x5F;
}

#ifdef NON_MATCHING
/* strncpy(dst, src, n): copy up to n bytes from src, stop at NUL, pad the
 * remainder of the n-byte field with zeros, return dst. Algorithm verified
 * (reloc-free). Byte-match is a multi-run target: target keeps src in saved
 * $s0 (frame 0x8) because it reuses a1 as the *dst++ store temp (move a1,a0;
 * sb;..) evicting src from a1; the C-emit path so far keeps src in a $t reg
 * (no frame, -1(a0) store form) — frame + a1-reuse scheduling pending. */
char *gl_func_00067C98(char *dst, char *src, int n) {
    char *ret = dst;
    int i = 0;
    if (n > 0) {
        do {
            char c = *src++;
            *dst++ = c;
            i++;
            if (c == 0) {
                while (i < n) {
                    *dst++ = 0;
                    i++;
                }
                break;
            }
        } while (i < n);
    }
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067C98);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00067D18: counts occurrences of byte a1 in the string at a0,
 * returns -count (negative running tally). Logic clear; cap: target uses
 * branch-likely (bnel) for BOTH the match-test and the loop-continue
 * (branch-likely-reorg) — clean C emits regular beq/bne. Reloc-free. */
int game_libs_func_00067D18(unsigned char *a0, int a1) {
    int count = 0;
    if (*a0 != 0) {
        do {
            unsigned char c = *a0;
            a0++;
            if ((unsigned char)a1 == c) {
                count--;
            }
        } while (*a0 != 0);
    }
    return count;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067D18);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00067D50: byte-fill (memset) — writes a1 to a0[0..a2),
 * returns a0. Logic clear; near-miss: the target loop carries redundant per-
 * iteration moves (v1=v0 cursor-copy + a3=a2 dead) — -O0-ish loop-codegen
 * artifacts that clean -O2 C doesn't reproduce. Reloc-free. */
void *game_libs_func_00067D50(char *a0, int a1, int a2) {
    char *p = a0;
    if (a2 != 0) {
        do {
            *p++ = (char)a1;
        } while (--a2 != 0);
    }
    return a0;
}
#else
/* game_libs_func_00067D50 = memset(char *dst, char val, int count) -> dst (byte
 * fill loop, returns dst). UNROLL CAP: target is the 12-insn NON-unrolled loop
 * (no prologue, `v1=v0` reload + dead `a3=a2` per iter) — a lower-opt build. IDO
 * at -O2 UNROLLS by 4 (22 insns); -O1 adds a prologue+spill. No C form at the
 * file's -O2 reproduces the non-unrolled no-prologue target (tested 2026-05-24).
 * Needs a contiguous lower-opt file split (cf. -g3 batch) to match. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067D50);
#endif

/* Returns 0 (sibling of matched _0003D480). */
int game_libs_func_00067D80(int a0) {
    return 0;
}

/* game_libs_func_00067D8C: 51-insn (0xCC) hex-string parser. BOUNDARY MERGED
 * 2026-06-02: splat over-split the hex-digit accumulation loop tail as a
 * separate symbol (00067E28, whose `bnel` branches backward to 0x67DCC inside
 * this body; 67D8C's success paths branch forward into it). Absorbed 67E28's
 * 12 words into 67D8C (0x9C -> 0xCC, ending exactly at the next func 0x67E58);
 * dropped the 67E28 symbol (no external callers). Parses a "0x"-prefixed hex
 * string; on a non-"0x" prefix it tail-BRANCHES (PC-relative, not a call) to
 * the decimal parser game_libs_func_00067E58 — those inter-function branches
 * are intentional, not a missing fragment. Reloc-blind USO; stays INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067D8C);

// Merged fragment: splat split this string-to-int parser at the mid-function
// jr ra (0x67E90) into _00067E58 + _00067E98; the tail's `b` loops back into
// the head, so it's one function (size 0xA4). Caller-set $v1 accumulator
// (read on entry, *= 10 per digit via multu) — IDO C can't express, stays
// INCLUDE_ASM. Boundary now correct (one symbol).
/* Signed decimal string -> int parser (atoi-class, stops at '.'/NUL/non-digit).
 * Leading char must be a digit or '-' (else returns 0); '-' sets the sign and
 * scanning continues. Accumulates value += digit, then value *= 10 before the
 * next digit (read-ahead). Logic decoded & correct; NOT yet byte-exact: target
 * uses a single read-char/classify loop with a branch-likely (bnel) on the
 * sign test and a dead duplicate `lbu a1,0(a0)`. This goto form mirrors that
 * single-loop structure (42 insns vs target 41, 5/41 byte) — closer than the
 * earlier while+for (48 insns, 2/41). Residual: IDO's char/cursor register
 * assignment + the bnel sign-test + dead-dup-load aren't reproduced by C.
 * Reloc-free; INCLUDE_ASM is the build path. Multi-run grind. */
#ifdef NON_MATCHING
int game_libs_func_00067E58(char *str) {
    int negative = 0;
    int value = 0;
    int c, next;
loop:
    c = (unsigned char)*str;
    str++;
    if (c < '0' || c >= ':') {
        if (c != '-') return 0;
        negative = 1;
        goto loop;
    }
    next = (unsigned char)*str;
    value += c - '0';
    if (next != 0 && next != '.' && next >= '0' && next < ':') {
        value *= 10;
        goto loop;
    }
    return negative ? -value : value;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067E58);
#endif

/* 9-insn double-return wrapper (split off from 14-insn bundle 2026-05-15
 * via split-fragments.py). Target uses `cvt.d.w` (function 0x21), not
 * `cvt.s.w` — return type is double, not float. The `volatile int *p =
 * &a1` forces caller-slot a1 spill (target's `sw a1, 0x1C(sp)` in jal
 * delay slot). */
extern int func_00000000();
double gl_func_00067EFC(int a0, int a1) {
    volatile int *p = &a1;
    (void)p;
    return (double)func_00000000(a0, a1);
}

/* 14-insn strupr-like (split off from gl_func_00067EFC bundle 2026-
 * 05-15). Walks string a0, converts 'a'..'z' to 'A'..'Z' via ANDI
 * 0xDF. Leaf — no stack frame. Signature: `int f(unsigned char *)`
 * — `int` (not `char`) for c forces $v0 allocation; `unsigned char *`
 * matches the lbu/sb byte access pattern. */
int game_libs_func_00067F20(unsigned char *a0) {
    int c;
    while ((c = *a0) != 0) {
        if (c >= 'a' && c <= 'z') {
            *a0 = c & 0xDF;
        }
        a0++;
    }
    return 0;
}

/* gl_func_00067F58: 18-insn 4-call cascade + 5-stub BUNDLE (0xF0 declared,
 * real fn is 18 insns = 0x4C; rest are 5 small leaf utilities).
 *
 * Decoded fn 1 (gl_func_00067F58 proper):
 *   func1(a0);
 *   v0 = func2(...);                                  // arg setup overlaps via delay slot
 *   if (v0 == 0) {
 *       func3(&D_00000000 + 0x2AA40);                 // error log
 *   }
 *   func4(v0, a0);
 *   return v0;
 *
 * Bundled stubs @0x4C-0xF0 (5 small leaf utilities, need fragment-split):
 *   - @0x4C (19 insns): byte-counting helper — scan a string for char,
 *     returns count of bytes (`while (*p++) count++;` style)
 *   - @0xA0: FP-cast helper — short load (`lhu`) + cvt.d.w + arith — converts
 *     short to double w/ table lookup at &D + 0x2AA60 base
 *   - @0xE0: similar FP helper with table at &D + 0x2AA60
 *   - more stubs after
 *
 * Marker said 60-insn — real fn 18 + bundled stubs make total 60.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_00067F58(int a0) {
    extern int D_00000000;
    int v0;
    v0 = (int)gl_func_00000000(gl_func_00000000(a0) + 1);
    if (v0 == 0) {
        gl_func_00000000((char*)&D_00000000 + 0x2AA40);
    }
    gl_func_00000000(v0, a0);
    return v0;
}

#ifdef NON_MATCHING
/* strlen: count chars until NUL, return count. Recognized libc, reloc-free.
 * Byte-match multi-run: target uses the 67xxx-family two-pointer-lag idiom
 * (v0 = a0 copy per iteration, char read via v0, a0 the live cursor) + a
 * branch-likely bnezl loop that the clean `while(*s++)` C form (single cursor)
 * doesn't reproduce. Same family as 67C98 (strncpy) / 67C1C (strcat). */
int game_libs_func_00067FA4(char *s) {
    int n = 0;
    while (*s++) {
        n++;
    }
    return n;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067FA4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067FD8);

#ifdef NON_MATCHING
/* game_libs_func_00068004: float-ratio table lookup. idx = (int)(a0/a1 *
 * 1024.0f + 0.5f) (round-to-nearest via +0.5 then trunc); returns the u16 at
 * a u16 table indexed by idx. Table at segment offset 0x2AA60 (emitted as
 * lui 0x3 + lhu -0x55A0(base)). Standard $f12/$f14 float args.
 * 86.25% NM. BOUNDARY FIXED 2026-06-02: the trailing `mtc1 zero,$f0` was the
 * stolen prologue of the next function (which reads f0=0.0 uninitialized); it
 * has been forward-merged into gl_func_00068044 (68004 shrunk 0x44->0x40,
 * +5pp here). Remaining residual is permuter-class: FP-temp renumber (IDO
 * reserves $f4 for the trunc result; mine starts the chain at $f4) + the
 * $v0/$v1 return move (target loads the table u16 into $v1 then `or v0,v1`;
 * IDO returns it via the jr delay-slot lhu, 1 insn shorter). */
int game_libs_func_00068004(float a0, float a1) {
    int idx = (int)(a0 / a1 * 1024.0f + 0.5f);
    int r = *(unsigned short *)((char *)&D_00000000 + 0x2AA60 + idx * 2);
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00068004);
#endif

/* gl_func_00068048: 107-insn (0x1AC) FPU-heavy float clamp/range chain.
 * Single function (1 jr ra). Stack frame -0x28 with sdc1 f22/f20 (callee-
 * save FPU doubles spilled, suggests heavy FP register pressure).
 *
 * ENTRY DECODE (insns 0-22, 0x68048-0x680A4):
 *   sp -= 0x28; sdc1 f22, 0x18(sp); sdc1 f20, 0x10(sp); sw ra, 0x24(sp)
 *   f22 = f12 (= a2 float arg); f20 = f14 (= a3 float arg)
 *   if (f0 <= f12)  // float compare
 *     if (f0 <= f14)
 *       call helper at jal 0x7C650 (fixed jal target, repeated multiple times)
 *       passing f12, f14 in arg slots
 *
 * STRUCTURE: nested c.le.s branch chains (~10 of them) wrapping calls to
 * the same fixed helper at 0x07C650 (likely sqrt or norm helper). Multiple
 * `4500002A bc1f` / `45020013 bc1fl` branches with float-conditional-likely
 * forms. Two int constants 0x4000_0000 (= 2.0f as int bits) and 0x8000_0000
 * (= -0.0f as int bits) appear via `addiu` immediate loads — int-to-float
 * cast pattern. The `34 0F 8000` pattern at 0x680F8 is `ori t7, $0, 0x8000`
 * which is a 16-bit constant = 32768 (likely an angular wraparound mask).
 *
 * FAMILY: likely the float-arg clamp/wrap-or-norm helper for an angular
 * (rotation) value. The fixed-jal pattern (0x7C650) matches a standalone
 * scalar helper, with f12/f14 as a (value, threshold) pair the function
 * range-checks across multiple breakpoints.
 *
 * Multi-tick decompile (FPU-heavy with extensive branch chains).
 * Default INCLUDE_ASM keeps ROM exact. Capturing structural decode here
 * for grep + future pass to refine the breakpoint logic + identify the
 * helper signature. */
/* gl_func_00068044: entry is 0x68044 (the `mtc1 zero,$f0` that materializes
 * f0=0.0, used at insn 3 `c.le.s f0,f12`). IDO hoisted that FP-const prologue
 * above the `addiu sp` frame setup, so splat had mis-assigned it to the
 * preceding game_libs_func_00068004; forward-merged here 2026-06-02 (68004
 * shrunk 0x44->0x40, this symbol renamed 68048->68044 +1 word). */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00068044)();
extern int game_libs_func_00070FA0(f32, f32);
f32 gl_func_00068044(f32 arg0, f32 arg1) {
    f32 d32768 = 32768.0f;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    s32 var_v1;

    if (arg0 >= 0.0f) {
        if (arg1 >= 0.0f) {
            if (arg0 <= arg1) {
                var_v1 = game_libs_func_00070FA0(arg0, arg1) << 0x10;
            } else {
                var_v1 = (0x4000 - game_libs_func_00070FA0(arg1, arg0)) << 0x10;
            }
        } else {
            temp_f20 = -arg1;
            if (temp_f20 < arg0) {
                var_v1 = (game_libs_func_00070FA0(temp_f20, arg0) + 0x4000) << 0x10;
            } else {
                var_v1 = (0x8000 - game_libs_func_00070FA0(arg0, temp_f20)) << 0x10;
            }
        }
    } else {
        temp_f22 = -arg0;
        if (arg1 < 0.0f) {
            temp_f20_2 = -arg1;
            if (temp_f22 <= temp_f20_2) {
                var_v1 = (game_libs_func_00070FA0(temp_f22, temp_f20_2) + 0x8000) << 0x10;
            } else {
                var_v1 = (0xC000 - game_libs_func_00070FA0(temp_f20_2, temp_f22)) << 0x10;
            }
        } else if (arg1 < temp_f22) {
            var_v1 = (game_libs_func_00070FA0(arg1, temp_f22) + 0xC000) << 0x10;
        } else {
            var_v1 = (0x10000 - game_libs_func_00070FA0(temp_f22, arg1)) << 0x10;
        }
    }
    return ((f32) (var_v1 >> 0x10) / d32768) * (*(f32*)((char*)&D_00000000 + 0x2210));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068044);
#endif

extern int gl_func_00000000();
void gl_func_000681F4(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

/* Vec3 (Tri3i) reader template — 20 insns / 0x50. Same shape as Quad4
 * reader but with size 12 / 3 lw-sw pairs. Requires `int pad` before buf
 * to push buf to sp+0x18 (matches target's stack layout vs IDO's natural
 * sp+0x1C). */
void gl_func_00068230(Tri3i *dst) {
    int pad;
    Tri3i buf;
    gl_func_00000000(&D_00000000, &buf, 0xC);
    *dst = buf;
    (void)pad;
}

extern int gl_func_00000000();
void gl_func_00068280(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_000682BC(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

/* gl_func_000682F8: 16-insn zero-init wrapper (0x40). Calls a 3-arg
 * helper with (self+0x14, &gl_ref_0002B3B8, self) then zeros self[0,2,4].
 * The bundle had 3 trailing 8-byte stubs (sw a0, 0(sp); jr ra) that
 * split-fragments separated as game_libs_func_0006833{8,40,48} —
 * those remain INCLUDE_ASM in this file (sandwich-ordered). */
void gl_func_000682F8(int *self) {
    gl_func_00000000(self + 5, (char *)&D_00000000 + 0x2B3B8, self);
    self[4] = 0;
    self[0] = 0;
    self[2] = 0;
}

/* Three save-arg-sentinel stubs split from gl_func_000682F8 bundle. Each
 * is `jr ra; sw a0, 0(sp)` — `void f(int)` body produces exact bytes. */
void game_libs_func_00068338(int a0) {}
void game_libs_func_00068340(int a0) {}
void game_libs_func_00068348(int a0) {}

/* gl_func_00068350: 29-insn (0x74) vtable-dispatch + flag-gated init.
 * 2026-05-13 tightened 64.07% → 99.59% via three fixes:
 *   1. Offset is (s16)vtable->field_8, NOT self->field_8 — target reads via $v0.
 *   2. Swap if/else arms: `if (D[1] == 0) {|=1} else {jal}` matches target's
 *      else-fall-through + branch-to-if layout.
 *   3. Inline the function-pointer call expression (don't name a local) to
 *      get `jalr $t9` per feedback-ido-indirect-call-t9.
 *
 * Decoded body (corrected):
 *   1. vtable = self->[0x1C]; method = vtable->[0xC];
 *      method(self + (s16)vtable->[8]);
 *   2. gl_func_X(self + 0x10) — fixed jal target 0x07C89C (cross-SEGMENT
 *      relocated; byte placeholder differs from C-compile-time emit:
 *      built emits 0c000000, target has 0c01f227).
 *   3. if (D[1] == 0) self[0] |= 1; else self[1] = gl_func(&D, 1, 0);
 *
 * Remaining 0.41% diff: the cross-segment jal at offset 0x28 produces
 * different placeholder bytes (gl_func_00000000 → 0c000000 vs target's
 * 0c01f227 jal to 0x07C89C past game_libs segment end). Needs INSN_PATCH
 * for this single insn to byte-match. Defer until INSN_PATCH recipe for
 * cross-segment jal-target patching is generalized.
 *
 * 4-insn split-off game_libs_func_000683C4 covers the post-bundle
 * stub (sw a1, 0xC(a0); sw $0, 8(a0); sw $0, 4(a0); jr ra). */
extern int gl_func_00000000();

extern int gl_ref_0007C89C();
void gl_func_00068350(int *self) {
    int *vtable = (int *)self[7];                         /* self->[0x1C] */
    /* inline function-ptr call → jalr $t9 per feedback-ido-indirect-call-t9 */
    (*(int(**)(int *))((char *)vtable + 0xC))((int *)(((short *)vtable)[4] + (char *)self));
    gl_ref_0007C89C(self + 4);
    if (*(int *)((char *)&D_00000000 + 4) == 0) {
        self[0] |= 1;
    } else {
        self[1] = gl_func_00000000(&D_00000000, 1, 0);
    }
}

/* Split off from gl_func_00068350 bundle 2026-05-08: 4-insn field setter. */
void game_libs_func_000683C4(int *a0, int a1) {
    *(int*)((char*)a0 + 0xC) = a1;
    *(int*)((char*)a0 + 0x8) = 0;
    *(int*)((char*)a0 + 0x4) = 0;
}

#ifdef NON_MATCHING
/* gl_func_000683D4: 54-insn (0xD8) array-allocator + per-element vtable
 * init constructor. Sibling of gl_func_00068350 (which sets up the
 * single-instance form).
 *
 * Decoded body:
 *   1. helper(self + 8)             — gl_func at jal target 0x07C860
 *      (same fixed jal as 68350; both use this initializer for the
 *      header at self+0x8).
 *   2. self[1] = gl_func_0(self->[8] * 4)
 *                                     — alloc(count * sizeof(ptr)) into
 *                                     self->[4]. self->[8] is the count.
 *   3. for (i = 0; i < self->[8]; i++) {
 *        parent = self->[0xC]->[0x28];
 *        instance = (*parent->[0x5C])(parent + (lh) parent->[0x58]);
 *        self->[4][i] = instance;
 *        instance->[0xC] = self->[0xC];   // back-link to owner
 *        gl_func_0(instance);             // post-init / register hook
 *        (*instance->[0x1C]->[0x2C])(instance->[0x1C] +
 *                                    (lh) instance->[0x1C]->[0x28]);
 *      }
 *
 * Two vtable hops per iteration (parent for instance creation, then
 * instance's own [0x1C] for finalize). Both use signed-short field
 * offsets — `lh` opcode pattern requires `short` not `unsigned short`.
 *
 * Loop tail uses `bnel $at, $0` with `lw v1, 0xC(s1)` in the delay
 * slot (likely-annulled reload of self->[0xC] for the loop body's
 * first use), so the C body should keep `parent_holder = self[3]`
 * inside the loop, NOT hoisted outside.
 *
 * Multi-tick byte-matching pending. Default INCLUDE_ASM keeps ROM
 * matching while the structural decode lives here for grep
 * discoverability. */
extern int gl_func_00000000();

void gl_func_000683D4(int *self) {
    unsigned int i;
    int *parent;
    int *instance;
    int (*ctor)(int *);
    int (*finalize)(int *);
    short ctor_off;
    short finalize_off;
    int *finalize_vt;

    gl_func_00000000(self + 2);                       /* self + 8 */
    self[1] = gl_func_00000000(self[2] * 4);          /* alloc */

    for (i = 0; i < (unsigned int)self[2]; i++) {
        parent = (int *)((int *)self[3])[10];          /* self->[0xC]->[0x28] */
        ctor = (int (*)(int *))parent[23];             /* parent->[0x5C] */
        ctor_off = ((short *)parent)[44];              /* (lh) parent->[0x58] */
        instance = (int *)ctor((int *)((char *)parent + ctor_off));
        ((int **)self[1])[i] = instance;
        instance[3] = self[3];                         /* instance->[0xC] = owner */
        gl_func_00000000(instance);                    /* post-init hook */
        finalize_vt = (int *)instance[7];              /* instance->[0x1C] */
        finalize = (int (*)(int *))finalize_vt[11];    /* vt->[0x2C] */
        finalize_off = ((short *)finalize_vt)[20];     /* (lh) vt->[0x28] */
        finalize((int *)((char *)finalize_vt + finalize_off));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000683D4);
#endif

/* gl_func_000684AC: 30-insn (0x78) alloc-or-passthrough constructor.
 * If a0 is null, alloc 0x38 bytes; else use given a0. Init phase 1 calls
 * helper(a0, a1), sets a0->[0x28] = &D_00000000, zeros a0->[0x30/0x34],
 * and conditionally calls helper(a0, 1, a2) if a2 != 0. Returns a0
 * (which may be 0 from a failed alloc — exits via shared epilogue
 * `move v0, a0`, exploiting the a0=v0=0 chain post-failed-alloc). */
int *gl_func_000684AC(int *a0, int a1, int a2) {
    if (a0 == 0) {
        a0 = (int *)gl_func_00000000(0x38);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, a1);
    a0[0xA] = (int)&D_00000000;
    a0[0xD] = 0;
    a0[0xC] = 0;
    if (a2 != 0) {
        gl_func_00000000(a0, 1, a2);
    }
end:
    return a0;
}

/* gl_func_00068524: 39-insn (0x9C) alloc-and-init-loop. Sibling of
 * gl_func_000685C0 (the bounds-checker for the same table). The
 * INITIALIZER/CONSTRUCTOR for the 2-level table that 685C0 / 68730 read.
 *
 * The in-segment absolute jal to 0x7C860 (= func_7C860 per
 * undefined_funcs_auto.txt) is a 26-bit pre-resolved address (vs the
 * usual `jal 0` + R_MIPS_26 placeholder for cross-USO calls). */
extern int gl_func_00000000();
extern int func_7C860();
void gl_func_00068524(int *a0, int a1) {
    int s1, s0;
    a0[0x2C/4] = (int)gl_func_00000000(&D_00000000, a1);
    func_7C860((int)&a0[0x34/4]);
    a0[0x30/4] = (int)gl_func_00000000(a0[0x34/4] << 4);
    if (a0[0x34/4] != 0) {
        s1 = 0;
        s0 = 0;
        do {
            gl_func_00000000(a0[0x30/4] + s0, a0);
            gl_func_00000000(a0[0x30/4] + s0);
            s1++;
            s0 += 16;
        } while ((unsigned int)s1 < (unsigned int)a0[0x34/4]);
    }
}

/* gl_func_000685C0: 55-insn (0xDC) bounds-checked 2-level table lookup
 * with 3 assertion-call sites. Sibling of matched gl_func_00068524
 * (constructor for the same table).
 *
 * NEAR-MISS: 6 stack-slot offset diffs (was 8). Declaring key_l BEFORE
 * key_h (decl-order spill-slot lever, see docs/IDO_CODEGEN.md
 * #feedback-ido-interleave-decl-spill-slot-alignment) fixes a2's slot
 * (0x20 in both), dropping 8→6. Residual: target reserves slot 0x18
 * unused and spills v1@0x1C/a2@0x20/a3@0x24; mine packs v1@0x18/a3@0x1C
 * /a2@0x20. Both frames 0x30. The reserved 0x18 needs IDO to allocate a
 * 4th (phantom, never-stored) spill slot at the bottom — no C structure
 * induces it: adding a real spilled local regresses to 13 diffs; pad/
 * explicit-local insertions grow the frame to 0x38. Stays NM.
 * 2026-06-10: the 5D054 split-decl slot lever swept (all 6 decl
 * permutations of key_l/key_h/row) -- all neutral at 6 diffs. The
 * spilled values here are UNNAMED caller-save temps of the assertion
 * calls, not named vars, so the decl-order lever has nothing to grip
 * (same boundary as 8C3C's internal temps). Phantom-slot cap stands. */
extern int gl_func_00000000();
#ifdef NON_MATCHING
void gl_func_000685C0(int *a0, unsigned int a1) {
    unsigned int key_l = a1 & 0xFFFF;
    unsigned int key_h = (a1 >> 16) & 0xFFFF;
    int *row;

    if (!(key_h < (unsigned int)a0[0x34/4])) {
        gl_func_00000000((char*)&D_00000000 + 0x2B3C0, key_h, key_l);
    }
    row = (int*)((char*)a0[0x30/4] + key_h * 16);
    if (!(key_l < (unsigned int)row[2])) {
        gl_func_00000000((char*)&D_00000000 + 0x2B3E4, key_h, key_l);
    }
    row = (int*)((char*)a0[0x30/4] + key_h * 16);
    if (((int*)((int*)((char*)row[1] + key_l * 4))[0])[0x10/4] == 0) {
        gl_func_00000000((char*)&D_00000000 + 0x2B404, key_h);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000685C0);
#endif

extern int gl_func_00000000();

int gl_func_0006869C(void) {
    int r = gl_func_00000000();
    char *p = *(char**)(r + 0x1C);
    (*(int(**)(int))(p + 0x14))(*(short*)(p + 0x10) + r);
    return r;
}

extern int gl_func_00000000();

void gl_func_000686D8(void) {
    char *r = (char*)gl_func_00000000();
    char *p = *(char**)(r + 0x1C);
    (*(int(**)(char*))(p + 0x1C))(r + *(short*)(p + 0x18));
}

extern int gl_func_00000000();
int gl_func_0006870C() {
    gl_func_00000000();
    return 0;
}

int gl_func_00068730(int *a0, int a1) {
    gl_func_00000000(a0, a1);
    {
        int *row = (int*)((char*)a0[0x30/4] + (((unsigned int)a1 >> 16) << 4));
        return ((int*)row[1])[a1 & 0xFFFF];
    }
}

extern int gl_func_00000000();

int gl_func_0006877C(int a0) {
    int *r = (int*)gl_func_00000000(0x20);
    if (r != 0) {
        r[7] = (int)gl_func_00000000;
    }
    return (int)r;
}

extern int gl_func_00000000();
/* gl_func_000687B8: 51-insn nested for-loops with vtable dispatch.
 * NM 88.82% → 99.41% via:
 *   (a) Inlined `n_outer` and `n_inner` named locals — IDO was allocating
 *       v0 for n_outer first, capturing it across the if-test and pushing
 *       all subsequent loads up by one register. Inlining `s2[0x08/4]`
 *       directly at each comparison frees v0 for the load result.
 *   (b) Loop counters declared `unsigned int` to emit sltu (matching
 *       target) instead of slt.
 *
 * LANDED fuzzy=100. The final 5-insn v0/v1 register-swap cap in the
 * inner-body block (target uses v1 for `e` and v0 for `vt`; built had
 * them swapped) was historically promoted via INSN_PATCH at offsets
 * 0x54..0x64; that mechanism was REMOVED 2026-05-23 as match-faking,
 * and the function still lands — the register-swap apparently resolved
 * naturally via accumulated upstream codegen changes. */
void gl_func_000687B8(int *a0)
{
  int outer_offset;
  int new_var;
  unsigned int j_outer;
  int *s2;
  if (a0[0x34 / 4] == 0)
  {
    return;
  }
  s2 = (int *) a0[0x30 / 4];
  outer_offset = 0;
  j_outer = 0;
  do
  {
    unsigned int j;
    int inner_offset;
    if (s2[0x08 / 4] != 0)
    {
      j = 0;
      inner_offset = 0;
      new_var = 0x04 / 4;
      do
      {
        int *vt;
        int *e = *((int **) (((char *) s2[new_var]) + inner_offset));
        vt = (int *) e[0x1C / 4];
        ((void (*)(int *)) vt[0x24 / 4])((int *) (((char *) (*((int **) (((char *) s2[new_var]) + inner_offset)))) + (*((short *) (((char *) vt) + 0x20)))));
        s2 = (int *) (((char *) a0[0x30 / 4]) + outer_offset);
        j++;
        inner_offset += 4;
      }
      while (j < ((unsigned int) s2[0x08 / 4]));
    }
    j_outer++;
    outer_offset += 0x10;
    s2 = (int *) (((char *) s2) + 0x10);
  }
  while (j_outer < ((unsigned int) a0[0x34 / 4]));
}


/* gl_func_00068884: 29-insn (0x74) alloc-or-passthrough constructor variant
 * of gl_func_000684AC. Differences from 684AC: takes 2 args (not 3); first
 * post-alloc init call uses fixed args (a0, &gl_ref_0002B420, 0) instead of
 * (a0, orig_a1); only sets a0[0xA] (no zeroing of a0[0xC]/a0[0xD]); the
 * orig a1 is forwarded to the second optional init call as its a2 arg. */
int *gl_func_00068884(int *a0, int a1) {
    if (a0 == 0) {
        a0 = (int *)gl_func_00000000(0x38);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, (char *)&D_00000000 + 0x2B420, 0);
    a0[0xA] = (int)&D_00000000;
    if (a1 != 0) {
        gl_func_00000000(a0, 1, a1);
    }
end:
    return a0;
}

/* gl_func_000688F8: 26-insn (0x68) double-alloc constructor with redundant
 * post-test on alloc result. NATURAL CEILING: 80.46% NM. Was previously
 * documented (2026-05-14) as promoted to byte-exact via 22-entry
 * INSN_PATCH + SUFFIX_BYTES_FORCE (+1 nop) to grow built 24->25 insns +
 * 1 trailing nop — INSN_PATCH and instruction-appending SUFFIX_BYTES
 * REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM.
 *
 * Old decode comments below — kept for reference. */
/* gl_func_000688F8 (original wrap):
 * post-test on alloc result. Sibling of gl_func_00068884 (single-alloc form).
 *
 * Asm structure decoded:
 *   v = alloc(0x30)
 *   if (v == 0) return 0           ; beqz v0, +0xF — early exit
 *   a1 = v                          ; delay
 *   if (v != 0) goto store_D       ; bnez v0, +7  — ALWAYS taken in
 *                                                    practice (v != 0
 *                                                    here), making the
 *                                                    fallback below dead
 *   v1 = v                          ; delay
 *   /-- dead code begins --/
 *   p = alloc(0x20)
 *   *(sp+0x18) = p
 *   a1 = *(sp+0x18)                 ; reloads p into a1 (overwrites first
 *                                     alloc!)
 *   if (p == 0) goto store_a1
 *   v1 = p                          ; delay
 *   /-- dead code ends --/
 *   store_D:
 *   v1->[0x1C] = &D                 ; via v1 register
 *   store_a1:
 *   a1->[0x1C] = &D                 ; via a1 register
 *   return a1
 *
 * The redundant `bnez v0` after `beqz v0, ret` is a compiler artifact —
 * IDO didn't fold the second test, leaving the alloc(0x20) fallback as
 * unreachable but emitted code. Possible C origin:
 *
 *   int *p = alloc(0x30);
 *   if (p == 0) return 0;
 *   if (p == 0) {                          // tautological at runtime, but
 *       p = alloc(0x20);                    // gets emitted anyway
 *       if (p == 0) goto skip;
 *   }
 *   p[7] = &D;
 * skip:
 *   p[7] = &D;
 *   return p;
 *
 * — i.e. paranoid double-check of the alloc result with a fallback to a
 * smaller size that IDO emits but never reaches. Multi-tick byte-match
 * deferred; structural decode here for grep + permuter seed.
 *
 * 2026-05-08 cap measurements (objdiff 27/27 insns, 80.46% fuzzy):
 *   - Frame: built -0x18 (24), expected -0x20 (32). 8-byte gap.
 *   - Reg-alloc: built collapses q/p to single $v1, expected uses $a1 + $v1
 *     for the SAME value with explicit spill+reload (`sw v0, 24(sp);
 *     lw a1, 24(sp)`).
 *   - Tried `char pad[8] + (void)pad`: 0pp (DCE'd, frame stays -0x18 — per
 *     `feedback-ido-pad-array-dce` already documented).
 *   - Tried intermediate `int *spill = alloc(0x20); p = spill; ...`:
 *     -5pp (forced spill but wrong shape). Reverted.
 *
 * 2026-05-08 (later): tried `volatile int *pp = (volatile int*)&a0` to
 * force a0's caller-slot spill via the new
 * `feedback-ido-arg-addr-via-volatile-ptr-forces-caller-spill` trick.
 * This DOES emit `sw a0, 0x18(sp)` but at the wrong byte offset (sp+0x18
 * with frame 0x18) — target's `sw a0, 0x20(sp)` requires frame 0x20.
 * Without growing the frame independently, the spill insn doesn't byte-
 * match. Combining the volatile-arg trick with `*(volatile int*)&q_alloc
 * = q_alloc` (force a stack slot for the second alloc result) grows
 * frame to 0x28 — overshoots by 8 bytes and adds extra spills (-pp).
 *
 * Cap class: needs simultaneous (a) frame=0x20 AND (b) sw v0, 0x18 mid-
 * function spill of dead-code alloc result. The volatile-arg trick alone
 * doesn't grow frame; forcing a stack-resident local for q_alloc grows
 * frame too much (extra address-take overhead). Likely permuter
 * territory or needs a fresh-shape rewrite that lands at frame=0x20 by
 * IDO's natural reservations rather than via volatile coercion.
 *
 * 2026-05-08 (later): tried `volatile int *spill = (volatile int*)alloc(0x20);
 * p = (int*)spill;` — pointer-cast variant of the value-spill trick. IDO
 * optimizes the pointer-load away (volatile is on the POINTEE int, not on
 * the local pointer var, so reading `p = (int*)spill` doesn't force a stack
 * round-trip). Result: identical 24-insn frame-0x18 emit, 0pp. The actual
 * mid-function spill needs a `volatile int slot;` (stack-resident, not
 * pointer) where the value is *written* and *read* through the volatile
 * lvalue — but per the prior `*(volatile int*)&q_alloc = q_alloc` attempt
 * that overshoots frame to 0x28. The narrow 0x20 frame target appears
 * unreachable with `volatile` levers.
 *
 * 2026-05-08 (later still): retried with the new declaration-order sub-rule
 * (docs/IDO_CODEGEN.md#feedback-ido-arg-addr-via-volatile-ptr-forces-caller-spill).
 * Variants tested:
 *   (a) `volatile int spill; volatile int *vparg = &a0;` — frame=0x20, spill
 *       slot at sp+0x1C, sw v0 at 0x1C(sp). Off by 4 from target's 0x18.
 *   (b) `volatile int *vparg = &a0; volatile int spill;` — frame=0x30 (worse).
 *       Volatile-arg + volatile-int-slot interaction makes IDO over-allocate.
 *   (c) volatile-arg alone (no spill): frame=0x18, sw a0 at sp+0x18 (caller-
 *       slot for THIS frame, but target wants frame=0x20 + sw a0 at sp+0x20).
 * Conclusion: declaration-order sub-rule works for forcing slot offsets but
 * the COMBINATION volatile-arg + volatile-int-spill cannot land at frame=0x20
 * with spill at sp+0x18. The volatile-arg recipe relies on frame growing
 * naturally (other locals); if the only lever to grow frame is the spill
 * itself, the slot offset can't simultaneously be 0x18. Cap class confirmed:
 * needs a NON-volatile mechanism to grow frame to 0x20 (e.g. a permuter find,
 * an unused-arg sentinel that IDO honors, or compiler upgrade). */
extern int gl_func_00000000();

#ifdef NON_MATCHING
int *gl_func_000688F8(int a0) {
    int *p;
    int *q;
    p = (int *)gl_func_00000000(0x30);
    if (p == 0) goto end;
    q = p;
    if (p != 0) goto store_D;          /* tautological — keeps fallback live */
    p = (int *)gl_func_00000000(0x20);
    if (p == 0) goto store_first;
    q = p;
store_D:
    q[7] = (int)&D_00000000;           /* via v1 register */
store_first:
    p[7] = (int)&D_00000000;           /* via a1 register */
end:
    return p;
}
#else
#ifdef NON_MATCHING
/* gl_func_000688F8: 26-insn allocate-and-init. p = alloc(0x30); if p==0 return 0;
 * set p->0x1C to a global pointer; return p. (The target also carries a
 * compiler-dead alloc(0x20) branch -- unreachable once p!=0 is established -- and
 * a redundant pre-write of p->0x1C to a first global that the second write
 * overwrites; both collapse to D_00000000 here.) NM (reference decode): collapsed
 * call + collapsed D refs (raw-.word game_libs reloc depression). */
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_000688F8(int a0) {
    int p = gl_func_00000000(0x30);
    if (p == 0) {
        return 0;
    }
    *(int *)((char *)p + 0x1C) = (int)&D_00000000;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000688F8);
#endif
#endif

extern int gl_func_00000000();
void gl_func_00068960(char *a0) {
    *(short*)(a0 + 0x20) = 0;
    *(short*)(a0 + 0x22) = 0;
    *(int*)(a0 + 0x24) = 0;
    *(int*)(a0 + 0x8) = 0;
    *(int*)(a0 + 0x2C) = 0;
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068990);

#ifdef NON_MATCHING
/* gl_func_00068B04: 42-insn 2-guard + lazy-init + 5-dispatch (0xA8, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   if (*self & 1) return;                          // bnel guard 1 (LSB set → skip)
 *   if (self->[0x8] != 0) return;                   // bnel guard 2 (already cached)
 *   v0 = func1(self->[0x2C]);                       // factory call
 *   self->[0x8] = v0;                                // cache
 *   saved_dx1 = D_X[1];                              // capture early (sp+0x24 spill)
 *   func2(&D_X, 1);                                  // dispatch 1
 *   func3(&D_X, ((int*)self->[0xC])->[0x2C]);        // dispatch 2 (chained deref)
 *   func4(&D_X, 0, self->[0x28]);                    // dispatch 3
 *   func5(&D_X, v0, self->[0x2C]);                   // dispatch 4 (with cached v0)
 *   func6(&D_X, saved_dx1);                          // dispatch 5 (with pre-captured D_X[1])
 *
 * The early-capture of D_X[1] (spilled to sp+0x24 before any callee that
 * could modify it) ensures the LAST call sees the pre-dispatch value.
 * Common idiom for "snapshot state before mutating helpers".
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00068B04(int *self) {
    extern int *D_X;
    int v0;
    int saved_dx1;
    if (*self & 1) return;
    if (self[0x8 / 4] != 0) return;
    v0 = (int)gl_func_00000000(self[0x2C / 4]);
    self[0x8 / 4] = v0;
    saved_dx1 = D_X[1];
    gl_func_00000000(D_X, 1);
    gl_func_00000000(D_X, ((int*)self[0xC / 4])[0x2C / 4]);
    gl_func_00000000(D_X, 0, self[0x28 / 4]);
    gl_func_00000000(D_X, v0, self[0x2C / 4]);
    gl_func_00000000(D_X, saved_dx1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068B04);
#endif

void gl_func_00068BAC(int *a0) {
    if ((*a0 & 1) == 0) {
        int *p = (int*)a0[2];
        if (p != 0) {
            gl_func_00000000(p);
        }
        a0[2] = 0;
    }
}

/* game_libs_func_00068BF4: 7-insn sibling without the func call.
 *   if (!(*a0 & 1)) a0[2] = 0; */
void game_libs_func_00068BF4(int *a0) {
    if (!(*a0 & 1)) {
        a0[2] = 0;
    }
}

#ifdef NON_MATCHING
/* gl_func_00068C14: 65-insn ext-pre-init + 3-call cascade + linked-set finalizer (0x104, frame 0x38).
 *
 * Decoded structure (raw-word disasm):
 *   func_pre(a0);                                     // pre-init (unknown args)
 *   // Write to extension buffer self->[0]:
 *   {
 *       int **bufp = &self->[0];
 *       int *p = *bufp; *bufp = p + 1;
 *       p[0] = &D + 0x3C4F4;
 *       p[1] = &D + 0x3C508;                          // sym pair (config keys)
 *   }
 *   // Conditional log on count <= 3:
 *   if (count > 3) func_log(0xDD);                   // overflow log
 *
 *   // Write another sym to ext buffer:
 *   {
 *       int *p = *bufp; *bufp = p + 1;
 *       p[0] = &D + 0x3C538;
 *   }
 *   // 2nd conditional log on diff condition
 *   if (some_count != 0) func_log2(saved_arg);
 *
 *   // Sub-init via 2nd call returning v0:
 *   func_sub(0, child_arg);                           // returns v0 = obj
 *   self->[0x18] = v0;
 *   self->[0x10] = v0;
 *   v1 = *(int*)(v0+0x10); v1++; *(int*)(v0+0x10) = v1;  // post-incr ref-count
 *
 *   // Linked-set finalizer (back-link-with-conditional-flag — 6th sibling
 *   // in the linked-set finalizer family per
 *   // feedback_1080_linked_set_finalizer_tail_idiom memo):
 *   if (obj->[0x14] != 0) obj->[0x4] = 1;
 *   obj->[0x14] = self;
 *   D_global->[0] = saved_a2 + i*4;                   // global update
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md.
 *
 * 2026-05-31: body completed to full logic (40.7->47.6% fuzzy): two read-advance-
 * conditional-log blocks, 3-arg sub-init, child wiring via self->0x3C, func_d, the
 * linked-set finalizer, and the D_global[count1] indexed store. Logic now CORRECT
 * (build 63 insns vs 65 expected, same operations). RESIDUAL is purely register
 * allocation: the target SPILLS count1 to stack slot 52(sp) (frame 0x38), while
 * IDO here promotes count1 (a call-surviving value) to saved reg s1 (frame 0x40),
 * shifting every subsequent insn. Saved-reg-vs-stack-spill cap (count1 can't be
 * recomputed — it's a consumed buffer read — so the inline-recompute lever doesn't
 * apply). Permuter candidate. INCLUDE_ASM remains build path.
 */
void gl_func_00068C14(int *self) {
    extern int D_00000000;
    extern int D_global_00068C14;
    int *bufstruct;
    int *p;
    int count1, count2;
    int *obj;
    int *child;
    int *cf;

    gl_func_00000000(self);                         /* pre(self) */

    /* block 1: advance buffer pos by one int, read count, conditional overflow log */
    bufstruct = (int *)self[0];
    p = (int *)bufstruct[0];
    bufstruct[0] = (int)(p + 1);
    count1 = p[0];
    self[1] = count1;                               /* self->4 = count1 */
    if (count1 >= 4) {
        gl_func_00000000((char *)&D_00000000 + 0x2C4F4, (char *)&D_00000000 + 0x2C508, 221);
    }

    /* block 2: advance again, read count2, conditional log */
    bufstruct = (int *)self[0];
    p = (int *)bufstruct[0];
    bufstruct[0] = (int)(p + 1);
    count2 = p[0];
    self[1] = count2;                               /* self->4 = count2 */
    if (count2 == 0) {
        gl_func_00000000((char *)&D_00000000 + 0x2C538, count1);
    }

    /* sub-init returning the child object */
    obj = (int *)gl_func_00000000(0, self[0x14 / 4], count2);
    child = (int *)self[0x3C / 4];
    child[0x18 / 4] = (int)obj;                     /* (self->0x3C)->0x18 = obj */
    self[0x10 / 4] = (int)obj;
    self[0x18 / 4] = (int)obj;
    cf = (int *)((int *)self[0x3C / 4])[0x10 / 4];  /* (self->0x3C)->0x10 */
    gl_func_00000000((char *)cf + 0x10);            /* func_d(cf + 0x10) */

    /* linked-set finalizer */
    if (obj[0x14 / 4] != 0) {
        obj[0x4 / 4] = 1;
    }
    obj[0x14 / 4] = (int)cf;

    /* D_global indexed store: D_global[count1] = self->0x18 (obj) */
    *(int *)((char *)&D_global_00068C14 + count1 * 4) = self[0x18 / 4];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068C14);
#endif

#ifdef NON_MATCHING
/* gl_func_00068D18: 47-insn double entry-write + lookup + 2-dispatch (0xBC, frame 0x38).
 *
 * Decoded structure (raw-word disasm):
 *   // Two near-identical entry-write blocks into a packed buffer at self->[0]:
 *   for (block = 0; block < 2; block++) {
 *       int **bufp = (int**)self->[0];
 *       int *p = *bufp;
 *       *bufp = p + 1;                                // post-incr buf ptr
 *       p[0] = (int)self->[0];                         // store back-ref
 *       p[1] = (*self) * 4;                            // sll 2 emit (4-byte align)
 *   }
 *   // (Optional log via direct sym if D_X != 0)
 *   if (D_X != 0) func_log(&D + 0x3C550);
 *   // Lookup via D_X[0x90 + i*8] sub-array (8-byte stride):
 *   sub = D_X[0x90/4 + i*2];
 *   if (sub->next != NULL) {
 *       func_d1(self, sub->next->[0x3C]);
 *       func_d2(saved_log_arg, sub->next);
 *   }
 *
 * Pattern: packed command-stream writer (post-incr ptr-array) followed
 * by lookup and dual-dispatch. Approximate decode; exact struct field
 * roles need a typing pass.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00068D18(int *self) {
    extern int D_00000000;
    extern int D_X_global;
    int idx;
    /* Block 1 */
    {
        int **bufp = (int**)&self[0];
        int *p = *bufp;
        *bufp = p + 1;
        p[0] = (int)self[0];
        idx = (*self) * 4;
        p[1] = idx;
    }
    if (D_X_global != 0) {
        gl_func_00000000((char*)&D_00000000 + 0x3C550);
    }
    /* Block 2 (mirror) */
    {
        int **bufp = (int**)&self[0];
        int *p = *bufp;
        *bufp = p + 1;
        p[0] = (int)self[0];
        p[1] = idx;
    }
    /* Lookup + dual dispatch */
    {
        int *sub = ((int**)&D_X_global)[0x90 / 4 + idx * 2];
        if (sub != 0 && sub[1] != 0) {
            int *target = (int*)sub[1];
            gl_func_00000000(self, target[0x3C / 4]);
            gl_func_00000000(self[0xC / 4], target);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068D18);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00068DD4)();
void gl_func_00068DD4(char *arg0) {
    s32 sp30;
    char *sp2C;
    char *sp24;
    s32 **temp_v0;
    s32 **temp_v1_2;
    s32 *temp_t1;
    s32 *temp_v0_2;
    s32 temp_a2;
    s32 temp_v1;
    char *temp_t0;
    char *temp_t0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;

    gl_func_00062F64();
    FW(FW(FW(arg0, 0x3C), 0xC), 0xB0) = 8;
    temp_v0 = FW(arg0, 0x0);
    temp_t1 = *(int*)temp_v0;
    *temp_v0 = temp_t1 + 4;
    temp_v1 = *(int*)temp_t1;
    FW(arg0, 0x4) = temp_v1;
    sp30 = *(int*)(temp_v1 * 4);
    temp_v1_2 = FW(arg0, 0x0);
    temp_v0_2 = *(int*)temp_v1_2;
    *temp_v1_2 = temp_v0_2 + 4;
    temp_a2 = *(int*)temp_v0_2;
    FW(arg0, 0x4) = temp_a2;
    temp_v0_3 = gl_func_00062F64(0, (char *)0x2C568, temp_a2, 0);
    sp2C = temp_v0_3;
    gl_func_00062F64(FW(temp_v0_3, 0x44) * 8);
    temp_v0_4 = gl_func_00062F64(0, (char *)0x2C574, 0, sp2C);
    FW(arg0, 0x28) = temp_v0_4;
    FW(arg0, 0x10) = temp_v0_4;
    FW(temp_v0_4, 0x30) = (s32) (FW(temp_v0_4, 0x30) & ~0x400);
    temp_t0 = FW(arg0, 0x28);
    FW(temp_t0, 0x30) = (s32) (FW(temp_t0, 0x30) & ~0x800);
    if (sp30 == 0) {
        gl_func_00062F64(0x2C580);
    }
    temp_v0_5 = FW(FW(FW(arg0, 0x3C), 0x3C), 0xC);
    temp_t0_2 = FW(temp_v0_5, 0x28);
    ((GP_00068DD4)FW(temp_t0_2, 0x14))(FW(temp_t0_2, 0x10) + temp_v0_5);
    temp_v0_6 = gl_func_00062F64(sp30, FW(FW(arg0, 0x3C), 0xC), (s32) FW(arg0, 0x28));
    sp24 = temp_v0_6;
    gl_func_00062F64((s32) FW(FW(arg0, 0x3C), 0xC), temp_v0_6);
    gl_func_00062F64((s32) sp24);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068DD4);
#endif

extern int gl_func_00000000();
void gl_func_00068F28(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00068F64(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

#ifdef NON_MATCHING
/* gl_func_00068FBC: 59-insn nested alloc/init constructor (size 0xEC, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   if (obj == NULL) {
 *       obj = alloc(0xA8);          // master record
 *       if (!obj) return NULL;
 *   }
 *   sub = obj;                       // delay-slot a1 init = s0
 *   if (sub == NULL) {
 *       sub = alloc(0x18);
 *       if (!sub) return obj;
 *   }
 *   if (sub == NULL) {                // dead branch (sub is set above)
 *       inner = alloc(0x10);
 *       if (inner) {
 *           *(int*)(inner+0)  = -1;
 *           *(int*)(inner+8)  = 0x8000;
 *           *(int*)(inner+4)  = 0;
 *       }
 *   }
 *   if (sub == (void*)0xFFFFFFF0) {   // magic-sentinel branch
 *       inner = alloc(0x4);
 *       if (inner) *(int*)inner = 0;
 *   }
 *   *((char*)sub + 0xC) = D+0x2C58C;  // sub-object vtable/info
 *   *((char*)sub + 0x14) = 0;
 *   *((char*)obj + 0xC) = D+0x2C598;  // master vtable/info
 *   *((char*)obj + 0x18) = arg3;
 *   *((char*)obj + 0x1C) = arg2;
 *   *((char*)obj + 0x20) = arg1;
 *   return obj;
 *
 * Notes:
 *  - `jal 0x0` raw-word entries are unsymbolicated callees in USO disasm
 *    (reloc resolves at link), NOT the hardcoded-libc-thunk family.
 *  - 0xFFFFFFF0 magic check is preserved from asm; appears dead in practice.
 *  - D+0x2C58C / D+0x2C598 are USO data relocs (vtable/info pointers).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int D_00000000;
extern void *alloc(int size);
void *gl_func_00068FBC(void *obj, int arg1, int arg2, int arg3) {
    void *sub;
    void *inner;

    if (obj == NULL) {
        obj = alloc(0xA8);
        if (obj == NULL) return obj;
    }
    sub = obj;
    if (sub == NULL) {
        sub = alloc(0x18);
        if (sub == NULL) return obj;
    }
    if (sub == NULL) {
        inner = alloc(0x10);
        if (inner != NULL) {
            *(int*)((char*)inner + 0x0) = -1;
            *(int*)((char*)inner + 0x8) = 0x8000;
            *(int*)((char*)inner + 0x4) = 0;
        }
    }
    if (sub == (void*)0xFFFFFFF0) {
        inner = alloc(0x4);
        if (inner != NULL) *(int*)inner = 0;
    }
    *(int*)((char*)sub + 0xC)  = (int)((char*)&D_00000000 + 0x2C58C);
    *(int*)((char*)sub + 0x14) = 0;
    *(int*)((char*)obj + 0xC)  = (int)((char*)&D_00000000 + 0x2C598);
    *(int*)((char*)obj + 0x18) = arg3;
    *(int*)((char*)obj + 0x1C) = arg2;
    *(int*)((char*)obj + 0x20) = arg1;
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068FBC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000690A8);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000693A4)();
void gl_func_000693A4(char *arg0, char *arg1, s32 arg2) {
    f32 sp20;
    f32 sp1C;
    f32 sp18;
    f32 sp14;
    f32 sp10;
    f32 temp_f10;
    f32 temp_f14;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f6_2;
    s16 temp_a2;
    s16 temp_v0_2;
    s32 var_a3;
    s32 var_t9;
    s32 var_v1;
    char *temp_a1;
    char *temp_t0;
    char *temp_t1;
    char *temp_t1_2;
    char *temp_v0;
    char *temp_v1;
    char *var_a1;

    temp_v1 = FW(arg1, 0x38);
    temp_v0 = FW(arg0, 0x18);
    var_a3 = 0;
    if (FW(arg0, 0x20) > 0) {
        var_v1 = 0;
        do {
            temp_a1 = FW(arg0, 0x1C) + var_v1;
            temp_v0_2 = *(s16*)((char*)temp_a1 + 0x2);
            if (temp_v0_2 > 0) {
                temp_a2 = *(s16*)((char*)temp_a1 + 0x0);
                temp_t0 = FW(arg0, 0x24) + (var_a3 * 6);
                sp18 = (f32)*(s16*)((char*)temp_t0 + 0x0);
                sp1C = (f32)*(s16*)((char*)temp_t0 + 0x2);
                sp20 = (f32)*(s16*)((char*)temp_t0 + 0x4);
                temp_t1 = FW(arg0, 0x18);
                temp_t1_2 = temp_t1 + 0x70;
                sp10 = sp18;
                temp_f4 = sp10;
                sp10 = sp1C;
                sp14 = sp20;
                temp_f10 = sp10;
                temp_f6 = ((*(f32*)((char*)temp_t1_2 + 0x4)) * temp_f4) + ((*(f32*)((char*)temp_t1_2 + 0x14)) * temp_f10);
                sp10 = temp_f4;
                temp_f6_2 = ((*(f32*)((char*)temp_t1 + 0x70)) * sp18) + ((*(f32*)((char*)temp_t1 + 0x80)) * sp1C) + ((*(f32*)((char*)temp_t1_2 + 0x20)) * sp20) + ((*(f32*)((char*)temp_v0 + 0xA0)) - (*(f32*)((char*)temp_v1 + 0xA0)));
                sp1C = temp_f6 + ((*(f32*)((char*)temp_t1_2 + 0x24)) * sp14) + ((*(f32*)((char*)temp_v0 + 0xA4)) - (*(f32*)((char*)temp_v1 + 0xA4)));
                sp18 = temp_f6_2;
                sp20 = ((*(f32*)((char*)temp_t1_2 + 0x8)) * sp10) + ((*(f32*)((char*)temp_t1_2 + 0x18)) * temp_f10) + ((*(f32*)((char*)temp_t1_2 + 0x28)) * sp14) + ((*(f32*)((char*)temp_v0 + 0xA8)) - (*(f32*)((char*)temp_v1 + 0xA8)));
                if (temp_v0_2 == 0x64) {
                    var_a1 = (int)arg2 + (temp_a2 * 6);
                    (*(s16*)((char*)var_a1 + 0x0)) = (s16) (s32) sp18;
                    (*(s16*)((char*)var_a1 + 0x2)) = (s16) (s32) sp1C;
                    var_t9 = (s32) sp20;
                } else {
                    temp_f14 = (f32) temp_v0_2 * (*(f32*)((char*)&D_00000000 + 0x2240));
                    var_a1 = (int)arg2 + (temp_a2 * 6);
                    (*(s16*)((char*)var_a1 + 0x0)) = (s16) ((*(s16*)((char*)var_a1 + 0x0)) + (s32) (sp18 * temp_f14));
                    (*(s16*)((char*)var_a1 + 0x2)) = (s16) ((*(s16*)((char*)var_a1 + 0x2)) + (s32) (sp1C * temp_f14));
                    var_t9 = (*(s16*)((char*)var_a1 + 0x4)) + (s32) (sp20 * temp_f14);
                }
                (*(s16*)((char*)var_a1 + 0x4)) = (s16) var_t9;
            }
            var_a3 += 1;
            var_v1 += 4;
        } while (var_a3 < FW(arg0, 0x20));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000693A4);
#endif

#ifdef NON_MATCHING
/* gl_func_000695F4: 37-insn alloc-or-init + sym-store + sentinel-branch (0x94, frame 0x18).
 *
 * Decoded structure (raw-word disasm):
 *   if (self_or_null == NULL) {
 *       obj = func1(0x98);                          // alloc 0x98 bytes
 *       if (obj == NULL) return NULL;
 *   } else {
 *       obj = self_or_null;
 *   }
 *   func2(obj, &D_00000000 + 0x2C5A8);              // init w/ string sym
 *   obj->[0x28] = &D_sym;
 *   if (obj == (int*)-72) {                          // sentinel-pointer guard
 *       int *v1 = func3(4);
 *       if (v1 != NULL) *v1 = 0;
 *   } else {
 *       *(int*)((char*)obj + 0x48) = 0;             // normal: clear obj->[0x48]
 *   }
 *   obj->[0x38] = 0;
 *   obj->[0x90] = a2;
 *   return obj;
 *
 * The `bne a3, at(-72)` compares obj-pointer to magic -72 — likely a
 * sentinel "error pointer" check or IDO codegen peculiarity.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int* gl_func_000695F4(int *self_or_null, int a1, int a2) {
    extern int D_00000000;
    extern int D_sym_695F4;
    int *obj = self_or_null;
    if (self_or_null == 0) {
        obj = (int*)gl_func_00000000(0x98);
        if (obj == 0) return 0;
    }
    gl_func_00000000(obj, (char*)&D_00000000 + 0x2C5A8);
    obj[0x28 / 4] = (int)&D_sym_695F4;
    if (obj == (int*)-72) {
        int *v1 = (int*)gl_func_00000000(4);
        if (v1 != 0) *v1 = 0;
    } else {
        *(int*)((char*)obj + 0x48) = 0;
    }
    obj[0x38 / 4] = 0;
    obj[0x90 / 4] = a2;
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000695F4);
#endif

#ifdef NON_MATCHING
/* gl_func_00069688: constructor — stores arg1 at self->0x38 (logs via cb(0x2C5B0)
 * if already set), allocates 3 buffers sized n*6/n*6/n*2 (n=arg2->0x40) into
 * self->0x3C/0x40/0x30, zeros self->0x94, then a per-element loop: writes 100 to
 * self->0x30[i] and copies a 3-short (6-byte) record from arg2->0x60 to self->0x3C;
 * stores arg2 at self->0x34, inits via cb(self), wires cb(arg1+0x70, self+0x50)
 * and back-links self->0x34->0xA8/0xAC. Returns self->0x34. Fresh decode 2026-05-29
 * (m2c-confirmed). 2026-06-21 base-pin lever applied (agent-i): 25->7 gate-diffs
 * (objcopy .text vs expected/.o, reloc-blind = the land gate). THREE cracks:
 *   (1) HELD-POINTER BASE-PIN: cb(0x2C5B0) was an INT LITERAL -> lui;ori; passing
 *       (char*)&D_00000000 + 0x2C5B0 (held pointer) -> lui 0x3;addiu -14928, which
 *       asm-processor BAKES into .text identically to expected (D_00000000 resolves
 *       to USO offset 0 + addend; surviving HI16/LO16 relocs are reloc-blind to the
 *       byte_verify gate -- verified via objcopy .text compare). Killed 2 diffs.
 *   (2) tail decl-order p-before-a1ptr -> IDO reloads arg1 into dead arg2 reg (s1)
 *       and increments in-place exactly like target (killed the structural tail diff).
 *   (3) copy-loop: compute dst BEFORE src -> src->v1, dst->v0 matching target
 *       (killed the 12-diff v0/v1 copy-loop renumber).
 * RESIDUAL (7 diffs): pure FRAME-SIZE allocator cap. Body+control-flow+regs are now
 * byte-exact; IDO allocates a 72-byte frame where target uses 56 (+16), shifting the
 * a1ptr spill 32->36 and the arg1 home slot 60->76. Tried: inline a1ptr (re-CSE'd),
 * pointer-store arg1, decl reorder, j/k loop order -- all frame-neutral. Irreducible
 * IDO stack-rounding/min-frame artifact. Caps: self/arg2 structs untyped. NON_MATCHING. */
extern int gl_func_00000000();
void *gl_func_00069688(char *self, char *arg1, char *arg2) {
    unsigned int i;
    int j;
    int k;
    short *src;
    short *dst;
    char *a1ptr;
    char *p;

    if (*(int *)(self + 0x38) != 0) {
        gl_func_00000000((char *)&D_00000000 + 0x2C5B0);
    }
    *(int *)(self + 0x38) = (int)arg1;
    *(int *)(self + 0x3C) = gl_func_00000000(*(int *)(arg2 + 0x40) * 6);
    *(int *)(self + 0x40) = gl_func_00000000(*(int *)(arg2 + 0x40) * 6);
    *(int *)(self + 0x30) = gl_func_00000000(*(int *)(arg2 + 0x40) * 2);
    *(int *)(self + 0x94) = 0;
    i = 0;
    j = 0;
    k = 0;
    if (*(int *)(arg2 + 0x40) != 0) {
        do {
            i += 1;
            *(short *)(*(char **)(self + 0x30) + j) = 100;
            j += 2;
            dst = (short *)(*(char **)(self + 0x3C) + k);
            src = (short *)(*(char **)(arg2 + 0x60) + k);
            k += 6;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
        } while (i < (unsigned int)*(int *)(arg2 + 0x40));
    }
    *(char **)(self + 0x34) = arg2;
    gl_func_00000000(self);
    p = arg1 + 0x70;
    a1ptr = self + 0x50;
    gl_func_00000000(p, a1ptr);
    *(char **)(*(char **)(self + 0x34) + 0xA8) = a1ptr;
    *(char **)(*(char **)(self + 0x34) + 0xAC) = p;
    return *(char **)(self + 0x34);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069688);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000697C4)();
void gl_func_000697C4(char *arg0) {
    f32 sp38;
    f32 sp34;
    f32 sp30;
    char **sp2C;
    char **sp28;
    f32 sp24;
    f32 sp20;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f14;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f8;
    s16 *temp_v0_4;
    s16 *temp_v0_7;
    s16 temp_t5;
    s32 temp_a0;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    u32 temp_a0_2;
    u32 temp_v1_4;
    u32 temp_v1_6;
    u32 var_a3;
    u32 var_a3_2;
    u32 var_v0;
    char **temp_t6;
    char **temp_t9;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v1;
    char *var_v0_2;
    char *var_v0_3;

    temp_v0 = *(s32*)((char*)&D_00000000 + 0x14);
    if (FW(arg0, 0x4C) != temp_v0) {
        FW(arg0, 0x4C) = temp_v0;
        if (FW(arg0, 0x38) == 0) {
            gl_func_00062F64((char*)((char*)&D_00000000 + 0x2C5CC));
        }
        var_a3 = 0;
        var_a0 = 0;
        var_v0 = FW(FW(arg0, 0x34), 0x40);
        var_a1 = 0;
        if (var_v0 != 0) {
            do {
                temp_f0 = (f32) *(s16*)(FW(arg0, 0x30) + var_a0);
                if (temp_f0 != 0.0f) {
                    temp_f0_2 = temp_f0 * *(f32*)((char*)&D_00000000 + 0x2244);
                    temp_v1 = FW(arg0, 0x3C) + var_a1;
                    sp30 = (f32) *(s16*)((char*)temp_v1 + 0x0);
                    sp34 = (f32) *(s16*)((char*)temp_v1 + 0x2);
                    sp38 = (f32) *(s16*)((char*)temp_v1 + 0x4);
                    temp_v0_2 = FW(arg0, 0x38);
                    temp_v0_3 = temp_v0_2 + 0x70;
                    temp_f14 = (*(f32*)((char*)temp_v0_2 + 0x70) * sp30) + (*(f32*)((char*)temp_v0_2 + 0x80) * sp34) + (*(f32*)((char*)temp_v0_3 + 0x20) * sp38);
                    temp_f4 = (*(f32*)((char*)temp_v0_3 + 0x4) * sp30) + (*(f32*)((char*)temp_v0_3 + 0x14) * sp34) + (*(f32*)((char*)temp_v0_3 + 0x24) * sp38);
                    temp_f8 = (*(f32*)((char*)temp_v0_3 + 0x8) * sp30) + (*(f32*)((char*)temp_v0_3 + 0x18) * sp34) + (*(f32*)((char*)temp_v0_3 + 0x28) * sp38);
                    *(s16*)(FW(arg0, 0x40) + var_a1) = (s16) (s32) (temp_f14 * temp_f0_2);
                    *(s16*)((FW(arg0, 0x40) + var_a1) + 0x2) = (s16) (s32) (temp_f4 * temp_f0_2);
                    *(s16*)((FW(arg0, 0x40) + var_a1) + 0x4) = (s16) (s32) (temp_f8 * temp_f0_2);
                } else {
                    *(s16*)((FW(arg0, 0x40) + var_a1) + 0x4) = 0;
                    *(s16*)((FW(arg0, 0x40) + var_a1) + 0x2) = 0;
                    *(s16*)(FW(arg0, 0x40) + var_a1) = 0;
                }
                var_a3 += 1;
                var_a0 += 2;
                var_v0 = FW(FW(arg0, 0x34), 0x40);
                var_a1 += 6;
            } while (var_a3 < var_v0);
        }
        temp_v1_2 = FW(arg0, 0x94);
        if (temp_v1_2 != 0) {
            temp_t1 = temp_v1_2 / 2;
            var_a3_2 = 0;
            if (var_v0 != 0) {
                var_a1_2 = 0;
                do {
                    var_a3_2 += 1;
                    temp_v1_3 = (*(u32*)((char*)&D_00000000 + 0x2C4F0) * 4) + 2;
                    temp_v1_4 = (u32) (temp_v1_3 * (temp_v1_3 + 1)) >> 2;
                    *(u32*)((char*)&D_00000000 + 0x2C4F0) = temp_v1_4;
                    temp_v0_4 = FW(arg0, 0x40) + var_a1_2;
                    *temp_v0_4 = (*temp_v0_4 + ((s32) ((temp_v1_4 & 0xFFFF) * temp_v1_2) >> 0x10)) - temp_t1;
                    temp_a0 = (*(u32*)((char*)&D_00000000 + 0x2C4F0) * 4) + 2;
                    temp_a0_2 = (u32) (temp_a0 * (temp_a0 + 1)) >> 2;
                    *(u32*)((char*)&D_00000000 + 0x2C4F0) = temp_a0_2;
                    temp_v0_5 = FW(arg0, 0x40) + var_a1_2;
                    *(s16*)((char*)temp_v0_5 + 0x2) = (s16) ((*(s16*)((char*)temp_v0_5 + 0x2) + ((s32) ((temp_a0_2 & 0xFFFF) * temp_v1_2) >> 0x10)) - temp_t1);
                    temp_v1_5 = (*(u32*)((char*)&D_00000000 + 0x2C4F0) * 4) + 2;
                    temp_v1_6 = (u32) (temp_v1_5 * (temp_v1_5 + 1)) >> 2;
                    *(u32*)((char*)&D_00000000 + 0x2C4F0) = temp_v1_6;
                    temp_v0_6 = FW(arg0, 0x40) + var_a1_2;
                    temp_t5 = FW(temp_v0_6, 0x4);
                    temp_v0_7 = temp_v0_6 + 4;
                    var_a1_2 += 6;
                    *temp_v0_7 = (temp_t5 + ((s32) ((temp_v1_6 & 0xFFFF) * temp_v1_2) >> 0x10)) - temp_t1;
                } while (var_a3_2 < (u32) FW(FW(arg0, 0x34), 0x40));
            }
            FW(arg0, 0x94) = 0;
        }
        sp2C = FW(arg0, 0x48);
        var_v0_2 = 0;
        sp28 = sp2C;
        if (sp2C != 0) {
            var_v0_2 = FW(sp2C, 0x0);
            sp2C = FW(sp2C, 0x4);
        }
        if (var_v0_2 != 0) {
            do {
                gl_func_00062F64(*(int*)sp28, arg0, FW(arg0, 0x40));
                var_v0_3 = 0;
                sp28 = sp2C;
                if (sp2C != 0) {
                    var_v0_3 = FW(sp2C, 0x0);
                    sp2C = FW(sp2C, 0x4);
                }
            } while (var_v0_3 != 0);
        }
        gl_func_00062F64(FW(arg0, 0x34), FW(arg0, 0x40));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000697C4);
#endif

#ifdef NON_MATCHING
/* gl_func_00069B94: 41-insn linked-list walk + per-node dispatch (0xA4, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   t6 = self->[0x38];                              // discriminator field
 *   if (t6 != 3) func1(&D + 0x3C5F0);               // log/setup if not = 3
 *
 *   // Two-level linked-list walk: outer at self->[0x48] via [0x4] next-ptr,
 *   // inner per-node sub-chain. NULL-terminated.
 *   for (p = self->[0x48]; p != NULL; p = p->[0x4]) {
 *       int key = p->[0x0];
 *       if (key == 0) continue;                      // sentinel skip
 *       int *result = func2(self->[0x3C], key);
 *       for (q = result; q != NULL; q = q->[0x4]) {
 *           if (q->[0x0] == 0) continue;
 *           // (inner processing — exact details omitted in this pass)
 *       }
 *   }
 *
 * Standard hash-bucket-walk dispatch pattern. The inner-loop body skipped
 * in C body — full decode would require sub-pass.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 *
 * 2026-05-31: logic verified CORRECT (the cb(obj,self,self->0x3C) walk + the
 * self->0x38==0 bnel-guarded init cb are right). Residual at 52.5% is the
 * cursor/next rotated-loop saved-reg-vs-stack-spill cap (same family as
 * gl_func_00038728). RULED OUT: rewriting to the rotated-prefetch C form
 * (next=cursor->4; obj=*cursor; if(!obj)break) REGRESSES this fn to 51.3%
 * (measured) — the plain while-loop here is closer; do NOT re-try the rotated
 * form. Needs focused regalloc grinding, not a quick lever.
 */
void gl_func_00069B94(int *self) {
    extern int D_00000000;
    int *node;
    if (self[0x38 / 4] == 0) {
        gl_func_00000000((char*)&D_00000000 + 0x2C5F0);
    }
    node = (int*)self[0x48 / 4];
    while (node != 0 && node[0] != 0) {
        gl_func_00000000(node[0], self, self[0x3C / 4]);
        node = (int*)node[1];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069B94);
#endif

extern int gl_func_00000000();
int gl_func_00069C38(char *a0) {
    return gl_func_00000000(a0 + 0x48);
}

extern int gl_ref_0007D594();
extern int gl_ref_0007D5D0();
void gl_func_00069C58(char *a0) {
    int local;
    gl_ref_0007D594(&local);
    gl_ref_0007D5D0(a0 + 0x10);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00069C58_pad.s")

/* gl_func_00069C94: 9-insn function-pointer indirect call (a0->[1] is the
 * fn ptr). Inline the call — a named `fn` local gets $v0, but an inline
 * `((void(*)(void))a0[1])()` uses $t9 (the MIPS computed-call register),
 * matching the target. */
void gl_func_00069C94(int *a0) {
    ((void (*)(void))a0[1])();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00069CB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069CD0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00069CD0_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00069E04)();
s32 gl_func_00069E04(char *arg0, s32 arg1, s32 arg2) {
    char *temp_s0;

    temp_s0 = gl_func_00062F64();
    if (FW(arg0, 0x8) >= FW(arg0, 0x10)) {
loop_1:
        if (arg2 == 1) {
            FW((*(int*)0), 0x10) = 8;
            gl_func_00062F64((int)arg0 + 4);
            if (FW(arg0, 0x8) < FW(arg0, 0x10)) {
                goto block_5;
            }
            goto loop_1;
        }
        gl_func_00062F64(temp_s0);
        return -1;
    }
block_5:
    *(int*)(FW(arg0, 0x14) + (((s32) (FW(arg0, 0xC) + FW(arg0, 0x8)) % (s32) FW(arg0, 0x10)) * 4)) = arg1;
    FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) + 1);
    if (*(int*)(FW(arg0, 0x0)) != 0) {
        gl_func_00062F64(gl_func_00062F64(arg0));
    }
    gl_func_00062F64(temp_s0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069E04);
#endif

/* game_libs_func_00069F50 = 1 zero pad word + a VI_CURRENT_REG
 * (0xA4400010) reader at 0x69F54 (template-scan find 2026-06-10). The
 * 3-insn C body is trivial but an in-place swap shifts all downstream
 * unit content (mid-file C-for-INCLUDE replacement never reproduces the
 * block layout -- see docs/MATCHING_WORKFLOW "in-place C matches ONLY
 * safe at unit-END"). Land via a carve split or a unit relayout pass. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00069F50);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00069F64)();
s32 gl_func_00069F64(char *arg0, s32 *arg1, s32 arg2) {
    char *temp_s0;

    temp_s0 = gl_func_00062F64();
    if (FW(arg0, 0x8) == 0) {
loop_1:
        if (arg2 == 0) {
            gl_func_00062F64(temp_s0);
            return -1;
        }
        FW((*(int*)0), 0x10) = 8;
        gl_func_00062F64(arg0);
        if (FW(arg0, 0x8) != 0) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    if (arg1 != 0) {
        *arg1 = *(int*)(FW(arg0, 0x14) + (FW(arg0, 0xC) * 4));
    }
    FW(arg0, 0xC) = (s32) ((s32) (FW(arg0, 0xC) + 1) % (s32) FW(arg0, 0x10));
    FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) - 1);
    if (*(int*)(FW(arg0, 0x4)) != 0) {
        gl_func_00062F64(gl_func_00062F64((int)arg0 + 4));
    }
    gl_func_00062F64(temp_s0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069F64);
#endif

/* game_libs_func_0006A09C: __osSetIntMask-style interrupt-mask updater. ARCHITECTURAL
 * CAP (mfc0/mtc0, not C-emittable): reads CP0 Status $12 (mfc0), rebuilds the SR/RCP
 * interrupt-enable bits from a global mask word + an MI_INTR_MASK read/write at
 * 0xA430000C, and writes Status back (mtc0 $12). The mfc0/mtc0 + the SR bit-twiddling
 * cannot be produced by IDO C (cf. reference_1080_mips3_runtime_helpers). Permanent
 * INCLUDE_ASM; the .s is the source of truth. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A09C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A1BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A1C4);

/* game_libs_func_0006A2C0: 7-insn double-precision polynomial leaf.
 *   f8  = f2 * $f12   ; $f12 = arg0 (double)
 *   f18 = f8 * $f14   ; $f14 = arg1 (double)
 *   f16 = f18 + f2
 *   return -(float)f16   = -(float)(f2*arg0*arg1 + f2)
 * CAP: $f2 is CALLER-SET (read at entry, never loaded) — not an O32 FP arg
 * register ($f12/$f14 only). IDO C can't source $f2 as input. Same
 * caller-set-float subclass as feedback_caller_set_int_reg_cap_1080_game_libs.
 * Sibling of game_libs_func_000710F8 (same shape, caller-set $f2 + $f16).
 * Permanent INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A2C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A2DC);

/* game_libs_func_0006A2F8: 3-insn `lwc1 f0, 0x2350($at); jr ra; nop` —
 * prologue-stolen successor. $at is set by the PREDECESSOR's tail
 * (`lui $at, %hi(SYM)`); this function reuses that as the base register
 * for an absolute float load. Standalone C-emit would emit its own
 * lui+lwc1 (2 insns), making the function 4 insns vs target's 3. CAP
 * class — was previously PROLOGUE_STEALS-promotable, now REMOVED
 * 2026-05-23 (per feedback_no_instruction_forcing_matches_policy).
 * Default INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A2F8);

#ifdef NON_MATCHING
/* gl_func_0006A304: pointer-relocation fixup driver. Gets the fixed
 * object at segment offset 0x41710, calls the USO init/register cb
 * (a0, obj, 0x40), then for each of 7 pointer fields
 * (0x10/0x18/0x20/0x28/0x2C/0x30/0x38) if non-null replaces it with
 * cb(field) (a relocate/resolve helper), returns obj.
 *
 * Cap: target keeps the reloc base in a spilled register (sw obj,
 * 0x1C(sp); reloaded `lw tN,0x1C(sp); lw tM,OFF(tN)` base+offset
 * before every field). With `(char*)&D_00000000 + 0x41710` IDO -O2
 * constant-folds each field into an ABSOLUTE `lui;lw` (D+0x4171x),
 * never keeping a base — 67 vs 71 insns, frame 0x18 vs 0x20. The
 * base+offset form needs a DISTINCT relocated symbol `&D_00041710`
 * (its own HI/LO reloc, so offsets stay immediates and IDO holds the
 * symbol address in a reg/stack). That symbol is not in the segment
 * symbol table (link error if referenced) — needs an
 * undefined_syms_auto.txt / splat entry first. Deferred: symbol
 * plumbing, then expect a clean match with the obj[] index form. */
extern int D_00000000;
extern int gl_func_00000000();
int gl_func_0006A304(int a0) {
    char *obj = (char *)&D_00000000 + 0x41710;
    gl_func_00000000(a0, obj, 0x40);
    if (*(int *)(obj + 0x10)) {
        *(int *)(obj + 0x10) = gl_func_00000000(*(int *)(obj + 0x10));
    }
    if (*(int *)(obj + 0x18)) {
        *(int *)(obj + 0x18) = gl_func_00000000(*(int *)(obj + 0x18));
    }
    if (*(int *)(obj + 0x20)) {
        *(int *)(obj + 0x20) = gl_func_00000000(*(int *)(obj + 0x20));
    }
    if (*(int *)(obj + 0x28)) {
        *(int *)(obj + 0x28) = gl_func_00000000(*(int *)(obj + 0x28));
    }
    if (*(int *)(obj + 0x2C)) {
        *(int *)(obj + 0x2C) = gl_func_00000000(*(int *)(obj + 0x2C));
    }
    if (*(int *)(obj + 0x30)) {
        *(int *)(obj + 0x30) = gl_func_00000000(*(int *)(obj + 0x30));
    }
    if (*(int *)(obj + 0x38)) {
        *(int *)(obj + 0x38) = gl_func_00000000(*(int *)(obj + 0x38));
    }
    return (int)obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006A304);
#endif

#ifdef NON_MATCHING
extern int game_libs_func_00070FA0(f32, f32);



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006A420)();
void gl_func_0006A420(char *arg0) {
    char *sp1C;

    sp1C = ((int(*)())game_libs_func_00070FA0)(arg0);
    if (FW(sp1C, 0x4) & 1) {
        FW(sp1C, 0x18) = (s32) FW(sp1C, 0x38);
        FW(sp1C, 0x1C) = (s32) FW(sp1C, 0x3C);
        FW(arg0, 0x4) = (s32) (FW(arg0, 0x4) & ~1);
        if (FW(sp1C, 0x4) & 4) {
            FW(sp1C, 0x10) = (s32) *(int*)((FW(arg0, 0x38) + 0xBFC) | 0xA0000000);
        }
    }
    gl_func_00062F64(sp1C, 0x40);
    gl_func_00062F64((char *)0x2B00);
    if (gl_func_00062F64((char *)0x04001000) == -1) {
        do {

        } while (gl_func_00062F64((char *)0x04001000) == -1);
    }
    if (gl_func_00062F64((char *)1, 0x04000FC0, sp1C, 0x40) == -1) {
        do {

        } while (gl_func_00062F64((char *)1, 0x04000FC0, sp1C, 0x40) == -1);
    }
    if (gl_func_00062F64() != 0) {
        do {

        } while (gl_func_00062F64() != 0);
    }
    if (gl_func_00062F64((char *)1, 0x04001000, FW(sp1C, 0x8), FW(sp1C, 0xC)) == -1) {
        do {

        } while (gl_func_00062F64((char *)1, 0x04001000, FW(sp1C, 0x8), FW(sp1C, 0xC)) == -1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006A420);
#endif

/* gl_func_0006A5B0: poll-loop — call an intra-USO helper(a0); if nonzero, spin
 * calling it until it returns 0; then call it with 293 (0x125). BYTE-EXACT.
 * Two keys: (1) `int *p = &a0; ...(*p)` (take the parameter's address) forces the
 * incoming-a0 home `sw a0,0x18(sp)` in the first jal delay slot — the arg-home that
 * plain `(a0)` can't produce; found by the PERMUTER (base 215 -> 0). The `&param`
 * lever CRACKS the used-arg-home cap (see docs/IDO_CODEGEN). (2) the 3 jals are
 * reloc-blind in expected (baked `0c000000`), so calls use the canonical
 * gl_func_00000000 placeholder (resolves to 0). No episode (reloc-blind jal-0). */
extern int gl_func_00000000();
void gl_func_0006A5B0(int a0) {
    int *p = &a0;
    if (gl_func_00000000(*p) != 0) {
        do {
        } while (gl_func_00000000() != 0);
    }
    gl_func_00000000(293);
}

/* game_libs_func_0006A5F0 CLASSIFIED 2026-06-10: HANDWRITTEN exception-
 * handler code (the __osException family fingerprint): k0-register
 * trampolines (lui k0/addiu k0/jr k0) at the head, sd/ld 64-bit register
 * saves, 11 CP0 words (mfc0/mtc0), and dispatch tables 3 insns in.
 * Inexpressible in IDO C (reference_1080_mips3_runtime_helpers class):
 * PERMANENT INCLUDE_ASM -- do not graft or decode. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A5F0);

/* game_libs_func_0006AD68 = libultra __osPopThread (os/exceptasm.s) --
 * HANDWRITTEN assembly (LEAF in the exception-handler file; verified
 * against libreultra: lw v0,0(a0); lw t9,0(v0); jr ra; sw t9,0(a0)).
 * IDENTIFIED 2026-06-10: the old wrap ground 5 C variants chasing the
 * $t9 "allocator state" -- the t9 is simply the hand-written register
 * choice. The neighbor game_libs_func_0006AD78 is the exception
 * context-switch block from the same file (k-regs, ld/ldc1 GPR+FPR
 * restore, eret -- also handwritten). Permanent INCLUDE_ASM, always-
 * skip class. Reference-search-first would have caught this. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006AD68);

/* game_libs_func_0006AD78 = the exception-handler context block from
 * os/exceptasm.s (HANDWRITTEN: mtc0/k-regs, full ld GPR + ldc1 FPR
 * restore, eret, PIF-watchdog tail). Permanent INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006AD78);

/* 14-insn linked-list traversal. Searches for `a1` in a list rooted at `a3`
 * (linked via *p == next). When found, copies *a3 (= *a1) to *a2 and returns.
 * a0 unused.
 *
 * 2026-05-08 refined to do-while form (structural match closer to target):
 *   do { if (a3 == a1) { *a2 = *a3; return; } a2 = a3; a3 = *a3; }
 *   while (a3 != 0);
 * Built emits 13 insns (mine) vs 14 (target). Differences:
 * - Target has `addiu sp, -8/+8` frame; built has none (no spill).
 * - Target uses `bne a3, a1, +4 ; nop` (regular branch); built uses
 *   `bnel a3, a1, +5` (likely-branch with delay annulled).
 * - Target has 1 jr-ra at end with shared epilogue; built has 2 jr-ras
 *   (one mid-function for early-return on match).
 *
 * Cap class: structural match good but frame-of-8 with no spills is hard
 * to force from C. `char pad[N]` DCE'd at IDO -O2. Multi-tick refinement
 * to align register allocation + frame layout.
 *
 * 2026-05-08 — `volatile int dummy` lever forces the addiu sp,-8 frame
 * (70.71% → 79.28%, +8.57pp). Cost: dummy adds 2 unwanted insns (spill
 * to sp+0x8 and trailing `lw zero, 0x4(sp)` use). Without dummy, frame
 * is gone. Tried `int pad[1]` (no volatile) — DCE'd, no frame, 70.71%.
 *
 * 2026-05-14 — two-step refinement to 86.78% (+7.50pp from 79.28%):
 *   (a) Match target asm: `*a2 = *a1` (uses a1) instead of `*a2 = *a3`
 *       (uses a3). At the match site a1==a3 functionally, but IDO encodes
 *       the source register from the literal expression. +0.36pp.
 *   (b) Drop the `(void)dummy` read; use `dummy = a0_unused` WRITE-ONLY.
 *       Volatile-write keeps the slot allocated (frame stays -8) without
 *       emitting the trailing `lw zero, 0x4(sp)` dead-load. Insn count
 *       drops 16 → 14 (matches target). +7.14pp.
 *   Net: 9/14 insns match. Remaining 5-insn diff:
 *   - `sw a0, 4(sp)` at DS-of-beqz vs target nop (volatile-write artifact)
 *   - `bnel a3,a1` + `or a2,a3,0` in DS vs target `bne a3,a1; nop` (IDO
 *     branch-likely scheduling — pulled the continue-side or-to-DS)
 *   - `lw a3, 0(a3)` vs target `lw a3, 0(a2)` (functionally same since
 *     a2 just set to a3, but encodes different source reg)
 *   These last 3 diffs are IDO -O2 scheduler/encoder cascades from the
 *   bnel optimization; no obvious C lever. Would need INSN_PATCH for
 *   final 5-insn promotion. */
/* gl_func_0006AF0C: 14-insn linked-list walk to find a1 from head a3,
 * patching predecessor's next-ptr to a1's next if found.
 * 4-insn INSN_PATCH closes the bnel→bne demotion + delay-slot nopping +
 * base-reg lw a3,0(a2) vs lw a3,0(a3). Volatile dummy preserved in C
 * for body-fidelity; INSN_PATCH overwrites its sw with nop. */
#ifdef NON_MATCHING
void gl_func_0006AF0C(int a0_unused, int *a1, int *a2, int *a3) {
    if (a3 != 0) {
        do {
            if (a3 == a1) {
                *a2 = *a3;
                return;
            }
            a2 = a3;
            a3 = *(int **)a3;
        } while (a3 != 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006AF0C);
#endif

#ifdef NON_MATCHING
/* gl_func_0006AF44: 65-insn list-unlink + cleanup helper (size 0x104, frame 0x38, saves s0/s1/s2).
 *
 * Operates on a singleton linked list at D+0:
 *   struct Node {
 *       int     _0;        // 0x0
 *       int     tag;       // 0x4 — -1 means list-end sentinel
 *       void   *sub_ptr;   // 0x8
 *       int    _C_or_next; // 0xC — next pointer (for list nodes) / data (for sentinel)
 *       u16     state;     // 0x10 — halfword: != 1 means "needs pre-unlink hook"
 *   };
 *
 * Decoded structure (raw-word disasm):
 *   void unlink_and_cleanup(Node *target) {
 *       void *prelim = setup_hook();           // jal <func> (no args set, uses caller-supplied?)
 *       int saved_target = (int)target;
 *
 *       if (target == NULL) {
 *           target = *(Node**)&D_00000000;      // load head as fallback
 *           goto search_list;
 *       }
 *
 *       // Pre-unlink hook: if state != 1, fire callback
 *       if (target->state != 1) {
 *           callback(target->sub_ptr, target);   // jal <func>(target->[0x8], target)
 *       }
 *
 *   search_list:
 *       Node *head = *(Node**)&D_00000000;
 *       if (head == target) {
 *           // Unlink at head: shift head pointer to next
 *           *(Node**)&D_00000000 = head->_C_or_next;
 *           goto post_unlink;
 *       }
 *       // Search through list for target
 *       Node *curr = *(Node**)&D_00000000;      // re-load head (separate lui/lw pair)
 *       while (curr->tag != -1) {                // -1 sentinel terminator
 *           Node *next = curr->_C_or_next;
 *           if (next == target) {
 *               curr->_C_or_next = target->_C_or_next;   // unlink middle
 *               goto post_unlink;
 *           }
 *           curr = next;
 *       }
 *       // (fell off end: target not in list — no-op for unlink)
 *
 *   post_unlink:
 *       // If target was the head: extra cleanup call
 *       Node *new_head = *(Node**)&D_00000000;
 *       if (target == new_head) {
 *           extra_cleanup();                     // jal <func> (no args)
 *       }
 *       final_cleanup(prelim);                  // jal <func>(prelim_from_first_jal)
 *   }
 *
 * Notes:
 *  - The `lui $s1, 0; lw $s1, 0($s1)` PAIR re-loads head AFTER the head==target
 *    check — slight redundancy from IDO not folding the load. Both reads return
 *    the same value when the head wasn't modified.
 *  - "tag = -1 sentinel" pattern: walking ends when curr->[0x4] == 0xFFFFFFFF.
 *    Likely a global static node placed as list terminator.
 *  - 5 jal calls total: 1 setup_hook (entry), 1 pre-unlink callback (conditional),
 *    1 extra_cleanup (if target was head), 1 final_cleanup (always), and 1
 *    in the search-not-found-target path (not shown — actually no, only 4 jal
 *    are visible in the raw asm).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md.
 *
 * 2026-05-28: converted the comment-only bail to a real C body, 38%. call1/call3
 * are no-arg (a0 left as-is), call2(target->8, target), call4(prelim). Walk the
 * D[0] singleton list (sentinel tag==-1) to unlink target. Logic verified vs
 * disasm. RESIDUAL (~62%, regalloc): the target makes `target` STACK-RESIDENT
 * (homed at sp+0x38, reloaded into a fresh $t reg at each of its ~5 uses across
 * the 4 calls) and uses s0/s1/s2 for prelim + the list-walk curr/next; IDO instead
 * promotes `target` to a callee-save $s reg (survives the calls without reload),
 * giving a smaller frame + fewer insns (57 vs 65). This is the stack-residency-vs-
 * s-reg-promotion cap (cf. gl_func_000718C0/00070194) — not reliably C-forceable
 * (volatile over-corrects). Real compilable wrap with correct logic; stays NM. */
extern int gl_func_00000000();
void gl_func_0006AF44(int *target) {
    int prelim;
    int *head;
    int *curr;

    prelim = gl_func_00000000();
    if (target != 0) {
        if (*(unsigned short*)((char*)target + 0x10) != 1) {
            gl_func_00000000(*(int*)((char*)target + 8), target);
        }
    } else {
        target = *(int**)&D_00000000;
    }
    head = *(int**)&D_00000000;
    if (head == target) {
        *(int**)&D_00000000 = (int*)head[0xC / 4];
    } else {
        curr = *(int**)&D_00000000;
        while (curr[0x4 / 4] != -1) {
            if ((int*)curr[0xC / 4] == target) {
                curr[0xC / 4] = target[0xC / 4];
                break;
            }
            curr = (int*)curr[0xC / 4];
        }
    }
    if (target == *(int**)&D_00000000) {
        gl_func_00000000();
    }
    gl_func_00000000(prelim);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006AF44);
#endif

#ifdef NON_MATCHING
/* game_libs_func_0006B048: libc-style bzero / memset-zero (declared size 0xB4, 45 words).
 *
 * Splat declares the symbol at offset 0, but the real function body starts at
 * offset 0xC (the first 3 words are leading nops — either splat misalignment
 * or compiler-emitted padding). The body is a standard IDO libc bzero.
 *
 * Decoded structure (real body 0xB054..0xB0F0):
 *     void bzero(void *dst, size_t n) {
 *         if (n < 0xC) goto byte_tail;          // small case, skip optimizations
 *         // Align dst to 4-byte boundary via swl (store-word-left)
 *         size_t pre = (-(intptr_t)dst) & 3;
 *         if (pre) {
 *             *(unsigned*)dst = 0;              // emit swl $zero, 0(dst)
 *             dst += pre;
 *             n -= pre;
 *         }
 *         // 32-byte unrolled chunks
 *         size_t big = n & ~0x1F;
 *         if (big) {
 *             void *end = (char*)dst + big;
 *             n -= big;
 *             do {
 *                 dst += 0x20;
 *                 ((int*)dst)[-8] = 0;
 *                 ((int*)dst)[-7] = 0;
 *                 ((int*)dst)[-6] = 0;
 *                 ((int*)dst)[-5] = 0;
 *                 ((int*)dst)[-4] = 0;
 *                 ((int*)dst)[-3] = 0;
 *                 ((int*)dst)[-2] = 0;
 *                 ((int*)dst)[-1] = 0;          // delay slot of bne
 *             } while (dst != end);
 *         }
 *         // 4-byte chunks
 *         size_t med = n & ~3;
 *         if (med) {
 *             void *end = (char*)dst + med;
 *             n -= med;
 *             do {
 *                 dst += 4;
 *                 ((int*)dst)[-1] = 0;
 *             } while (dst != end);
 *         }
 *     byte_tail:
 *         // 1-byte tail
 *         if ((ssize_t)n <= 0) return;
 *         void *end = (char*)dst + n;
 *         do {
 *             dst += 1;
 *             ((char*)dst)[-1] = 0;
 *         } while (dst != end);
 *     }
 *
 * TRAILING FRAGMENT (0x6B0F0..0x6B0FC, 3 insns): nop; lui $t6, 0x0; lw $t6, 0($t6).
 *   Incomplete fragment (no prologue, no jr) — likely start of a hardcoded-
 *   address libc thunk that the linker fills in. Variant of
 *   feedback_splat_too_big_incomplete_fragment_tail.md.
 *
 * Notes:
 *  - This is the IDO-canonical bzero emission (4-align prefix, 32-byte unroll
 *    of 8 sw $zero, 4-byte cleanup, 1-byte tail). Standard libc pattern.
 *  - Symbol prefix `game_libs_func_` (not `gl_func_`) suggests this was a libc
 *    function exported into the game_libs USO at compile time.
 *  - Splat boundary issue: candidate for split-fragments.py.
 *
 * CLASSIFICATION (corrected 2026-06-06): the body LOOKS like canonical IDO
 * libc bzero (slti/negu/andi head + do/while loops), not obviously hand-coded
 * (the 2026-05-28 "handwritten, do NOT attempt" reason was imprecise). BUT
 * three things block a C match, confirmed empirically this date:
 *   (1) the expected symbol has 3 LEADING NOPS at 0x6B048 (real body at
 *       0x6B054) — a splat boundary misattribution; C cannot emit leading nops.
 *   (2) the leading partial-word zero is a LONE `swl zero,0(a0)`; `*(int*)p=0`
 *       emits plain `sw` (and at the unaligned head would fault) — no standard
 *       C idiom yields a lone swl.
 *   (3) the BSD-bzero C body compiled at this file's -O2 EXPANDS to ~104 insns
 *       (vs the 42-insn target) — IDO does not reproduce the tight unrolled
 *       form here (measured fuzzy=None). So it is not C-matchable as-is.
 * Stays INCLUDE_ASM. Re-attempt only after a splat boundary split (drops the
 * 3 nops) AND finding what produces the tight 39-insn form + the lone swl. */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006B048);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006B0F0);

#ifdef NON_MATCHING
/* PASS-1 2026-06-10 (big-swing): FULL m2c graft (423 insns; pristine
 * profile -- no tables, no CP0/f64/COP1 moves). */
s32 gl_func_0006B0FC(void) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    char *sp30;
    char *sp2C;
    u32 sp28;
    s32 *sp24;
    u32 temp_t9;
    char *temp_t0;
    char *temp_t3;
    char *temp_t7;

    temp_t7 = 0 /* M2C unset $t6 */ + 0x14;
    sp3C = 0;
    sp30 = temp_t7;
    temp_t0 = temp_t7 + (*(s32 *)((char *)&D_00000000 + 0x1A) /* M2C unset $t6 */ * 0x24);
    sp2C = temp_t0 + 0x18;
    sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
    if (sp38 & 1) {
        *(s32 *)((char *)&D_00000000 + 0) = (s32) (*(s32 *)((char *)&D_00000000 + 0) & ~0x800);
        *(s32 *)((char *)(temp_t0) + 0x18) = 0x1D;
        gl_func_0007FEEC();
        goto block_59;
    }
    sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
    if (sp38 & 3) {
        do {
            sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
        } while (sp38 & 3);
    }
    sp3C = *(s32 *)((char *)&D_00000000 + 0xA5000508);
    if (sp3C & 0x02000000) {
        sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
        if (sp38 & 3) {
            do {
                sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
            } while (sp38 & 3);
        }
        *(s32 *)((char *)&D_00000000 + 0xA5000510) = *(s32 *)((char *)(sp30) + 0x10) | 0x01000000;
        *(s32 *)((char *)(sp2C) + 0x0) = 0;
        return 0;
    }
    if (*(s32 *)((char *)(sp30) + 0x0) == 2) {
        goto block_59;
    }
    if (sp3C & 0x08000000) {
        sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
        if (sp38 & 3) {
            do {
                sp38 = *(s32 *)((char *)&D_00000000 + 0xA4600010);
            } while (sp38 & 3);
        }
        sp3C = *(s32 *)((char *)&D_00000000 + 0xA5000508);
        *(s32 *)((char *)(sp2C) + 0x0) = 0x16;
        gl_func_0007FEEC();
        *(s32 *)((char *)&D_00000000 + 0xA4600010) = 2;
        *(s32 *)((char *)&D_00000000 + 0) = (s32) (*(s32 *)((char *)&D_00000000 + 0) | 0x100401);
        goto block_59;
    }
    if (*(s32 *)((char *)(sp30) + 0x0) == 1) {
        if (!(sp3C & 0x40000000)) {
            if ((*(s32 *)((char *)(sp30) + 0x8) + 1) != (*(s32 *)((char *)(sp30) + 0x4) * 0x55)) {
                *(s32 *)((char *)(sp2C) + 0x0) = 0x18;
                gl_func_0007FE04();
            } else {
                *(s32 *)((char *)&D_00000000 + 0xA4600010) = 2;
                *(s32 *)((char *)&D_00000000 + 0) = (s32) (*(s32 *)((char *)&D_00000000 + 0) | 0x100401);
                *(s32 *)((char *)(sp2C) + 0x0) = 0;
                gl_func_0007FEEC();
            }
        } else {
            *(s32 *)((char *)(sp2C) + 0x4) = (s32) (*(s32 *)((char *)(sp2C) + 0x4) + *(s32 *)((char *)(sp2C) + 0xC));
            *(s32 *)((char *)(sp30) + 0x8) = (s32) (*(s32 *)((char *)(sp30) + 0x8) + 1);
            func_00000000(*(s32 *)((char *)&D_00000000 + 0), 1, 0x05000400, *(s32 *)((char *)(sp2C) + 0x4), *(s32 *)((char *)(sp2C) + 0xC));
        }
        goto block_59;
    }
    if (*(s32 *)((char *)(sp30) + 0x0) == 0) {
        if (*(s32 *)((char *)(sp30) + 0x4) == 3) {
            if ((*(s32 *)((char *)(sp2C) + 0x10) + 0x11) < *(s32 *)((char *)(sp30) + 0x8)) {
                *(s32 *)((char *)(sp2C) + 0x0) = 0;
                gl_func_0007FE04();
                goto block_59;
            }
            if (!(sp3C & 0x40000000)) {
                *(s32 *)((char *)(sp2C) + 0x0) = 0x17;
                gl_func_0007FE04();
                goto block_59;
            }
            goto block_27;
        }
        *(s32 *)((char *)(sp2C) + 0x4) = (s32) (*(s32 *)((char *)(sp2C) + 0x4) + *(s32 *)((char *)(sp2C) + 0xC));
block_27:
        sp34 = *(s32 *)((char *)&D_00000000 + 0xA5000510);
        if (((sp34 & 0x200000) && (sp34 & 0x400000)) || (sp34 & 0x02000000)) {
            if ((u32) *(s32 *)((char *)(sp2C) + 0x10) >= 4U) {
                if ((*(s32 *)((char *)(sp30) + 0x4) != 3) || (*(s32 *)((char *)(sp30) + 0x8) >= 0x53)) {
                    *(s32 *)((char *)(sp2C) + 0x0) = 0x17;
                    gl_func_0007FE04();
                    goto block_59;
                }
                goto block_35;
            }
            temp_t9 = *(s32 *)((char *)(sp2C) + 0x10);
            sp28 = temp_t9;
            *(s32 *)((char *)((sp2C + (temp_t9 * 4))) + 0x14) = (s32) (*(s32 *)((char *)(sp30) + 0x8) + 1);
block_35:
            *(s32 *)((char *)(sp2C) + 0x10) = (u32) (*(s32 *)((char *)(sp2C) + 0x10) + 1);
            goto block_36;
        }
block_36:
        if (sp3C & 0x10000000) {
            if (*(s32 *)((char *)(sp30) + 0x8) != 0x57) {
                *(s32 *)((char *)(sp2C) + 0x0) = 0x18;
                gl_func_0007FE04();
            }
            if ((*(s32 *)((char *)(sp30) + 0x4) == 2) && (*(s32 *)((char *)(sp30) + 0x6) == 0)) {
                *(s32 *)((char *)(sp30) + 0x6) = 1U;
                *(s32 *)((char *)(sp30) + 0x8) = -1;
                *(s32 *)((char *)(sp30) + 0x40) = (s32) (*(s32 *)((char *)(sp30) + 0x40) - *(s32 *)((char *)(sp30) + 0x48));
                *(s32 *)((char *)(sp2C) + 0x0) = 0x16;
            } else {
                *(s32 *)((char *)&D_00000000 + 0xA4600010) = 2;
                *(s32 *)((char *)&D_00000000 + 0) = (s32) (*(s32 *)((char *)&D_00000000 + 0) | 0x100401);
                *(s32 *)((char *)(sp30) + 0x0) = 2;
                *(s32 *)((char *)(sp2C) + 0x0) = 0;
            }
            func_00000000(*(s32 *)((char *)&D_00000000 + 0), 0, 0x05000000, *(s32 *)((char *)(sp2C) + 0x8), *(s32 *)((char *)(sp2C) + 0xC) * 4);
            goto block_59;
        }
        if ((*(s32 *)((char *)(sp30) + 0x8) == -1) && (*(s32 *)((char *)(sp30) + 0x4) == 2) && (*(s32 *)((char *)(sp30) + 0x6) == 1)) {
            sp24 = sp30 + 0x18;
            if (*(s32 *)((char *)(sp30) + 0x28) == 0) {
                temp_t3 = *(s32 *)((char *)(sp30) + 0x20);
                if ((*(s32 *)((char *)(temp_t3) + 0xC) | (*(s32 *)((char *)(temp_t3) + 0x0) | *(s32 *)((char *)(temp_t3) + 0x4) | *(s32 *)((char *)(temp_t3) + 0x8))) != 0) {
                    *(s32 *)((char *)(sp30) + 0x18) = 0x18;
                    gl_func_0007FE04();
                    goto block_59;
                }
            }
            *sp24 = 0;
            gl_func_0007FEEC();
            goto block_51;
        }
block_51:
        *(s32 *)((char *)(sp30) + 0x8) = (s32) (*(s32 *)((char *)(sp30) + 0x8) + 1);
        if (sp3C & 0x40000000) {
            if (*(s32 *)((char *)(sp30) + 0x8) >= 0x55) {
                *(s32 *)((char *)(sp2C) + 0x0) = 0x18;
                gl_func_0007FE04();
                goto block_59;
            }
            func_00000000(*(s32 *)((char *)&D_00000000 + 0), 0, 0x05000400, *(s32 *)((char *)(sp2C) + 0x4), *(s32 *)((char *)(sp2C) + 0xC));
            *(s32 *)((char *)(sp2C) + 0x0) = 0;
            return 1;
        }
        if (*(s32 *)((char *)(sp30) + 0x8) < 0x55) {
            *(s32 *)((char *)(sp2C) + 0x0) = 0x18;
            gl_func_0007FE04();
        }
        goto block_59;
    }
    *(s32 *)((char *)(sp2C) + 0x0) = 4;
    gl_func_0007FE04();
block_59:
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B0FC);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006B798);

#ifdef NON_MATCHING
/* gl_func_0006B7A0: 56-insn hardware-register status-poll + DMA setup (0xE0, frame 0x20).
 *
 * Heavy N64 hardware access:
 *   - 0xA460xxxx (PI cluster) — status polls via lw +0x10 (PI_STATUS_REG)
 *   - 0xA500xxxx (AI cluster) — status polls via lw +0x10 (AI_STATUS_REG)
 *   - 0xA4600510 / 0xA4500510 — extended register writes (non-standard offsets,
 *     possibly devkit-specific or PIF-adjacent)
 *
 * Decoded structure (raw-word disasm):
 *   // Spin-wait for PI_STATUS_REG busy bits (& 3) to clear
 *   while ((*(volatile int*)0xA4600010 & 3) != 0) { [spin] }
 *
 *   // Write to extended PI register at 0xA4600510 with cart-mapped address:
 *   *(volatile int*)0xA4600510 = (a0 + 0x14) | 0x10000000;
 *
 *   // Spin-wait for AI_STATUS_REG busy bits to clear
 *   while ((*(volatile int*)0xA4500010 & 3) != 0) { [spin] }
 *
 *   // Write to extended AI register at 0xA4500510 with similar mapping
 *   *(volatile int*)0xA4500510 = ...;
 *
 *   // Call direct-addr jal 0x807EC (libc-family — registered in
 *   //   reference_1080_hardcoded_jal_addresses memo as 5th site)
 *   ((void(*)())0x807EC)();
 *
 *   *(volatile int*)0xA4600010 = 2;                  // PI_STATUS reset
 *   D_global_sym = D_other_sym | (some bits);         // global update
 *
 * PI + AI dual-DMA setup with status-polling — likely cart-to-AI streaming
 * audio DMA initialization. The 0xA4600510 / 0xA4500510 writes target
 * non-standard register offsets (PI/AI register blocks end ~0x1C), so
 * these are devkit-extended registers or PIF-adjacent regions.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0006B7A0(int *a0) {
    /* Spin-wait PI not busy */
    while ((*(volatile int*)0xA4600010 & 3) != 0) { }
    *(volatile int*)0xA4600510 = (int)((char*)a0 + 0x14) | 0x10000000;
    /* Spin-wait AI not busy */
    while ((*(volatile int*)0xA4500010 & 3) != 0) { }
    *(volatile int*)0xA4500510 = *(volatile int*)0xA4600010 | 0x10000000;
    ((void(*)(void))0x807EC)();
    *(volatile int*)0xA4600010 = 2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B7A0);
#endif

#ifdef NON_MATCHING
/* gl_func_0006B880: 59-insn ring-buffer-append with notify-list callback (size 0xEC, frame 0x30).
 *
 * Operates on a singleton ring buffer at D+0x40:
 *   struct RingBuf *head = *(struct RingBuf**)(D+0x40);
 *   struct RingBuf {
 *       struct Notify *first;  // 0x0
 *       int            _4;     // 0x4
 *       int            count;  // 0x8  — current occupied slots
 *       int            base;   // 0xC  — read cursor
 *       int            cap;    // 0x10 — capacity
 *       int           *slots;  // 0x14 — slot array (int-stride)
 *   };
 *
 * Decoded structure (raw-word disasm):
 *   void enqueue(void) {
 *       struct RingBuf *head = *(void**)(D+0x40);
 *       if (head == NULL) return;
 *       if (head->count >= head->cap) return;            // full, drop
 *
 *       // Signed-div slot index with full safety traps (break 7=div0, break 6=INT_MIN/-1)
 *       int slot = (head->base + head->count) % head->cap;
 *       head->slots[slot] = *(int*)(D+0x44);              // enqueue value
 *       head->count++;
 *
 *       // Chain callback if notify-list has any entries
 *       if (head->first && head->first->next != NULL) return;
 *       int *result = callback1(head);                    // jal <func>(head)
 *       callback2((char*)&D_00000000 + 0, result);        // jal <func>(D+0, result)
 *   }
 *
 * Notes:
 *  - The signed-div safety trap pattern (`div + mfhi + bnez/break 7 + bne $at,-1
 *    + bne $at,INT_MIN + break 6`) is the standard IDO-emitted modulo guard
 *    sequence — see reference_1080_mips3_runtime_helpers.md for the recognition.
 *    This is INLINE rather than via runtime-call because the divisor is sized
 *    at 32-bit (`div` not `ddiv`).
 *  - Ring buffer is singleton at D+0x40; the value-to-enqueue lives at D+0x44.
 *  - "notify-list" empty-check is `head->first->next == NULL` (head->first must
 *    be non-NULL for the deref) — if list has no successors, fire callbacks.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int gl_func_00000000();
extern int D_00000000;
// Ring-buffer append (singleton at &D+0x40, value at &D+0x44). Drop if head
// null or count>=cap; else slot = (head->0xC + count) % cap (signed-div with
// IDO break-guards), head->slots[slot] = *(&D+0x44), count++. Then if the
// notify list has a successor (head->first->next != 0) fire cb(head) and
// cb(&D, result). Reloc-blind cbs/&D.
void gl_func_0006B880(void) {
    char *head;
    int count;
    int slot;
    char *first;
    int s0;
    head = *(char **)((char *)&D_00000000 + 0x40);
    if (head == 0) {
        return;
    }
    count = *(int *)(head + 0x8);
    if (count >= *(int *)(head + 0x10)) {
        return;
    }
    slot = (*(int *)(head + 0xC) + count) % *(int *)(head + 0x10);
    *(int *)(*(char **)(head + 0x14) + slot * 4) = *(int *)((char *)&D_00000000 + 0x44);
    *(int *)(head + 0x8) = *(int *)(head + 0x8) + 1;
    first = *(char **)head;
    if (*(char **)first == 0) {
        return;
    }
    s0 = gl_func_00000000(head);
    gl_func_00000000((char *)&D_00000000, s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B880);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006B880_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006B974: 16-insn (0x40) 3-call wrapper that returns call-2's
 * value. Frame 0x28 includes $s0 spill (target uses $s0 for rv across the
 * 3 calls; mine uses sp+0x1C stack spill).
 *
 * Decoded structure:
 *   gl_func_00000000(a0, a1)         ; call 1 — args inherited from caller
 *   rv = gl_func_00000000(a0, a1)    ; call 2 — return saved
 *   gl_func_00000000(a0, a1)         ; call 3
 *   return rv                         ; return value of call 2
 *
 * Cap: target uses $s0 to hold rv across all 3 calls; mine uses stack
 * spill (sp+0x1C). Tried `register int rv` hint — IDO ignores for
 * single-use vars (only 1 ref + return). Other variants (more refs)
 * would need to introduce dummy uses, which would add insns. Net wash.
 *
 * Uncertain: target's call 3 has $a0 stale (clobbered by call 2, no
 * explicit reload) — suggesting the original C might have had a different
 * arg pattern. The (a0, a1) form here passes both args to all calls
 * (~equivalent semantics, different codegen).
 *
 * Default INCLUDE_ASM build matches; wrap is for grep + future-pass seed. */
int gl_func_0006B974(int a0, int a1) {
    int rv;
    gl_func_00000000(a0, a1);
    rv = gl_func_00000000(a0, a1);
    gl_func_00000000(a0, a1);
    return rv;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B974);
#endif

/* gl_func_0006B9B4: byte-identical twin of matched gl_func_0006BE14 (differs
 * only in the arg2 offset, 0x42750 vs 0x42800). Same crack: the 0x42750 arg is
 * a SYMBOL reference (&D_00000000 + 0x42750 -> lui 0x4; addiu 0x2750), not a
 * literal (which gives lui; ori). arg1 bases are distinct externs (gl_data_B9B4
 * _b/_c), mirroring gl_func_0006BE14's gl_data_BE14_b/_c. */
extern char gl_data_B9B4_b;
extern char gl_data_B9B4_c;
void gl_func_0006B9B4(void) {
    *(int*)&D_00000000 = 1;
    gl_func_00000000(&gl_data_B9B4_b, (char*)&D_00000000 + 0x42750, 1);
    gl_func_00000000(&gl_data_B9B4_c, 0, 0);
}
/* game_libs_func_0006BA04 (2-word splat mis-split: lui t6,0; lw t6,0(t6))
 * was the stolen prologue of gl_func_0006BA0C — forward-merged into it
 * (boundary correction; orphan-function removed). */

/* gl_func_0006BA0C: MATCHED via forward-merge of the orphan prologue (above).
 * The leading `lui t6,0; lw t6,0(t6)` (= *(int*)&D_00000000 read) was split off
 * by splat as the fake 2-word function game_libs_func_0006BA04; merged back. */
void gl_func_0006BA0C(void) {
    int local;
    int pad;
    if (*(int*)&D_00000000 == 0) {
        gl_func_00000000();
    }
    gl_func_00000000(&D_00000000, &local, 1);
}

/* 11-insn passthrough wrapper (0x2C). LANDED fuzzy=100. The 2 trailing
 * stolen-prologue insns for the successor (lui t6,0xA460; lw a2,0x10(t6)
 * — N64 PI_STATUS_REG read setup) historically absorbed via SUFFIX_BYTES;
 * mechanism REMOVED 2026-05-23 as match-faking. Those insns belong to
 * separate symbols now. (Previously-documented 0x34 size is stale.) */
void gl_func_0006BA48(void) {
    gl_func_00000000(&D_00000000, 0, 0);
}

#ifdef NON_MATCHING
/* gl_func_0006BA7C: 19-insn (0x4C) PI-DMA-wait + uncached-cart-read.
 * Spin-waits while (a2 & 3) testing PI_STATUS_REG (0xA4600010) — bits 0
 * and 1 are PI_STATUS_DMA_BUSY and PI_STATUS_IO_BUSY. Once PI is idle,
 * reads the value at ((D_00000000 | a0) | 0xA0000000) — uncached KSEG1
 * access — and stores it to *a1.
 *
 * D_00000000 here is the relocatable cartridge-segment base (gets
 * resolved by the USO loader to e.g. 0x10000000+). The OR-with-a0
 * computes a ROM-domain offset, OR-with-0xA0000000 puts it in KSEG1
 * for cache-bypass read post-DMA.
 *
 * This is a direct-cart-read helper used after a PI DMA completes
 * (caller passes a2 = previous PI_STATUS read; if non-busy already,
 * skip the spin-wait).
 *
 * Caps at the byte level:
 *   1. Stack frame: target has `addiu sp, -8` (leaf with no spills).
 *      IDO -O2 from natural C produces no frame.
 *   2. PI_STATUS_REG addressing: target uses `lui t8, 0xA460; lw a2,
 *      0x10(t8)` (lui + signed-offset load). IDO emits `lui+ori; lw
 *      0(p)` (full 32-bit materialization). Tried various constant-
 *      fold tricks (raw, base+offset, ORed, extern-as-pointer): no
 *      change. Likely needs a HW_REG-style macro or compiler flag.
 *   3. bnez vs bnel: target spin-loop uses `bnez t9, -4; nop`. IDO
 *      emits `bnel t7, $0, -2; lw a2(delay)` (branch-likely + delay-
 *      load). Same scheduler quirk seen on EA98.
 *
 * NM-wrap with structural decode. Default INCLUDE_ASM matches bytes. */
void gl_func_0006BA7C(int a0, int *a1, unsigned int a2) {
    while (a2 & 3) {
        a2 = *(volatile int*)0xA4600010;
    }
    *a1 = *(volatile int*)((((int)&D_00000000) | a0) | 0xA0000000);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BA7C);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BA7C_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BAD4);
