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
void gl_func_00062F64(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062F8C);

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

void gl_func_0006370C(char *a0) {
    int local;
    gl_func_00000000(&local);
    gl_func_00000000(a0 + 0x10);
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
    ((int(*)())gl_func_00062F64)(temp_a0, (int)arg0 + 0x10C, &sp130, arg0);
    ((int(*)())gl_func_00062F64)(sp18, (int)arg0 + 0x118, &sp124, arg0);
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
    ((int(*)())gl_func_00062F64)((s32) temp_f12, &sp108);
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
    ((int(*)())gl_func_00062F64)((*(f32*)((char*)arg0 + 0x108)), &sp118, &sp13C, arg0);
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
void *gl_func_00063DC4(void *a0, int a1, float a2, float a3) {
    void *s0 = a0;
    if (s0 == 0) {
        s0 = (void*)gl_func_00000000(368);
        if (s0 == 0) return s0;
    }
    gl_func_00000000(s0, (char*)&D_00000000 + 0x22390, 0.0f, 0.0f, 0.0f);
    *(int*)((char*)s0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)s0 + 0x16C) = a1;
    gl_func_00000000(s0, a2, a3, 0);
    gl_func_00000000(s0);
    *(float*)((char*)s0 + 0x164) =
        gl_func_00000000(a2 * a2 + a3 * a3 + 0.0f);
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
            ((int(*)())gl_func_00062F64)(&sp44);
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
            ((int(*)())gl_func_00062F64)(0.0f, FW(arg0, 0x16C), (int)arg0 + 0x120, &sp44, arg0);
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
        sp60.unk8 = (*(f32*)((char*)temp_v0 + 0x8)) - (*(f32*)((char*)temp_v1 + 0x8));
        sp60.unk4 = (*(f32*)((char*)temp_v0 + 0x4)) - (*(f32*)((char*)temp_v1 + 0x4));
        sp60.unk0 = (*(f32*)((char*)arg0 + 0x4)) - (*(f32*)((char*)arg0 + 0x28));
        sp6C.unk0 = (f32) sp60.unk0;
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
        ((int(*)())gl_func_00062F64)(temp_a1, temp_a1);
        ((int(*)())gl_func_00062F64)(arg1, temp_a1, sp90);
        temp_v0_2 = (int)arg0 + 0x10;
        sp30.unk0 = (*(f32*)((char*)arg0 + 0x10)) * 1.0f;
        sp30.unk4 = (*(f32*)((char*)temp_v0_2 + 0x4)) * 1.0f;
        sp30.unk8 = (*(f32*)((char*)temp_v0_2 + 0x8)) * 1.0f;
        sp6C.unk0 = (f32) sp30.unk0;
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
 *  - 13 simple slots, stride 0x18 from +8: get-or-alloc(0x18);
 *      init(slot, var_s0, DI(0x223D0 + i*4), 1);
 *      slot[0xC]=0x221D8; slot[0x14]=0; slot[0x10]=<float table/const>.
 *  - 1 complex slot at +0x160 (alloc 0x20): init w/ DI(0x22408);
 *      slot[0xC]=0x221F0; slot[0x1C]=0; slot[0x10..0x18]=Vec3{1,1,0}.
 *  - two 4-byte fields at arg0+0x39C / +0x3A0 set to 0; final
 *    gl_func_0001CA10(arg0).
 *
 * NOT matched: folded-pool data refs + ~37-call register allocation are a
 * multi-tick grind (project_1080_cap_analysis_2026-05-28). Full structure
 * documented for the next pass. */
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
        SI(arg0, 0x28, 0);
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
    ((int(*)())gl_func_00062F64)(temp_a0);
    temp_a1 = (int)arg0 + 0xCC;
    sp24 = temp_a1;
    ((int(*)())gl_func_00062F64)(temp_a0, temp_a1, temp_a1);
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
    ((int(*)())gl_func_00062F64)(arg0, sp24);
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
 *   // 1st dispatch — copies float fields from sp to self+0x33C..0x344:
 *   func1(self);
 *   self->[0x33C..0x344] = sp values (after func1);
 *
 *   // 2nd dispatch — loads Vec3 globals to self+0x288..0x290:
 *   func2(...);
 *   self->[0x288] = *(float*)(D + 0x120);
 *   self->[0x28C] = *(float*)(D + 0x138);
 *   self->[0x290] = *(float*)(D + 0x1B0);
 *   *(float*)(self + 0x348) = ...;
 *
 * Full transform-reset: quat (0,0,0,1), translation/rotation/scale = 0/0/1.
 * Sibling of gl_func_00065C54 (op-6 transform-reset) — same identity layout
 * at +0x2FC..+0x308 (quat) and +0x318..+0x320 (translation).
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00065060(char *self) {
    extern int D_global_sym;
    extern float D_pos_x, D_pos_y, D_pos_z;
    int i;
    *(short*)(self + 0x38C) = (short)0xFFFF;
    for (i = 0x2FC; i <= 0x320; i += 4) *(float*)(self + i) = 0.0f;
    for (i = 0x330; i <= 0x338; i += 4) *(float*)(self + i) = 0.0f;
    for (i = 0x34C; i <= 0x354; i += 4) *(float*)(self + i) = 0.0f;
    *(float*)(self + 0x308) = 1.0f;
    for (i = 0x390; i <= 0x398; i += 4) *(float*)(self + i) = 1.0f;
    /* Copy self->[0x318..0x320] to global */
    *(int*)((char*)&D_global_sym + 0x10) = *(int*)(self + 0x318);
    *(int*)((char*)&D_global_sym + 0x14) = *(int*)(self + 0x31C);
    *(int*)((char*)&D_global_sym + 0x18) = *(int*)(self + 0x320);
    gl_func_00000000(self);
    *(float*)(self + 0x348) = 1.0f;
    *(float*)(self + 0x288) = D_pos_x;
    *(float*)(self + 0x28C) = D_pos_y;
    *(float*)(self + 0x290) = D_pos_z;
    gl_func_00000000();
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
            spEC.unk0 = FW(var_s0, 0xDC);
            spEC.unk4 = (f32) FW(temp_v0, 0x4);
            spEC.unk8 = (f32) FW(temp_v0, 0x8);
            FW(var_s0, 0x120) = spEC.unk0;
            FW(var_s0, 0x124) = spEC.unk4;
            FW(var_s0, 0x128) = spEC.unk8;
            temp_f12 = FW(temp_v0, 0x8) - FW(temp_s4, 0x8);
            spDC.unk0 = FW(var_s0, 0xDC) - FW(arg0, 0xDC);
            spDC.unk8 = temp_f12;
            spDC.unk4 = FW(temp_v0, 0x4) - FW(temp_s4, 0x4);
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
            FW(var_s0, 0x114) = (f32) (FW(var_s0, 0x114) - sp128);
            FW(var_s0, 0x118) = (f32) (FW(var_s0, 0x118) - sp12C);
            FW(var_s0, 0x11C) = (f32) (FW(var_s0, 0x11C) - sp130);
            FW(var_s0, 0x114) = (f32) (FW(var_s0, 0x114) + FW(arg0, 0x318));
            FW(var_s0, 0x118) = (f32) (FW(var_s0, 0x118) + FW(arg0, 0x31C));
            FW(var_s0, 0x11C) = (f32) (FW(var_s0, 0x11C) + FW(arg0, 0x320));
            if (((int(*)())gl_func_00062F64)(*(int*)0, temp_s1, (f32 *)0x43C80000, &spF8) != 0) {
                FW(var_s0, 0x14C) = (s32) sp108;
                spEC.unk0 = spF8.unk0;
                spEC.unk4 = (f32) spF8.unk4;
                spEC.unk8 = (f32) spF8.unk8;
                var_f20 = sp104;
                sp13C = spEC.unk8;
                sp138 = spEC.unk4;
                sp134 = spEC.unk0;
            } else {
                var_f20 = FW(var_s0, 0x124);
                sp13C = 0.0f;
                sp138 = 1.0f;
                sp134 = 0.0f;
            }
            temp_v0_2 = FW(var_s0, 0x28);
            temp_f20 = var_f20 - FW(arg0, 0x218);
            FW(var_s0, 0x144) = temp_f20;
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
                sp8C.unk0 = FW(var_s0, 0x120) * temp_f16;
                sp8C.unk4 = FW(temp_s1, 0x4) * temp_f16;
                sp8C.unk8 = FW(temp_s1, 0x8) * temp_f16;
                spEC.unk0 = sp8C.unk0;
                spEC.unk4 = (f32) sp8C.unk4;
                spEC.unk8 = (f32) sp8C.unk8;
                spA8.unk0 = spEC.unk0;
                spA8.unk4 = (f32) spEC.unk4;
                spA8.unk8 = (f32) spEC.unk8;
                sp174 += spA8.unk0;
                sp178 += spA8.unk4;
                sp17C += spA8.unk8;
                var_f0 = (FW(var_s0, 0x114) * sp134) + (FW(var_s0, 0x118) * sp138) + (FW(var_s0, 0x11C) * sp13C);
                if (var_f0 > 0.0f) {
                    var_f0 = 0.0f;
                }
                temp_f14 = (temp_f16 * FW(arg0, 0x290)) + (FW(arg0, 0x28C) * -var_f0);
                temp_f12_2 = sp13C * temp_f14;
                sp78.unk0 = sp134 * temp_f14;
                sp78.unk4 = sp138 * temp_f14;
                sp78.unk8 = temp_f12_2;
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
        temp_f0 = -var_f30 * FW(arg0, 0x288);
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
void gl_func_00065C54(char *a0, int *a1) {
    if (a1[0] == 6) {
        int *src = (int*)a1[1];
        float x = *(float*)((char*)src + 0xEC);
        float y = *(float*)((char*)src + 0xF0);
        float z = *(float*)((char*)src + 0xF4);
        gl_func_00000000(a0, x, y, z);
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
/* gl_func_0006612C: 43-insn magic-value spin-handshake helper (0xAC, frame 0x20).
 *
 * Decoded structure (raw-word disasm) — repeated send-and-spin pattern:
 *   v = func(self, self->[0x28] + 8);                // initial send
 *   while (v != 0x12340004) {                         // spin until response
 *       v = func(self, self->[0x28] + 8);
 *   }
 *   func(self, self->[0x28] + 8, (a2) 0x12340002); // state-change call
 *   v = func(self, self->[0x28] + 8);                // another send
 *   while (v != 0x12340003) {                         // spin until next response
 *       v = func(self, self->[0x28] + 8);
 *   }
 *
 * Magic-value handshake protocol: send via call, spin reading response,
 * advance state with action call (passing different magic constant),
 * then spin for next response. Common in HW-IO / DMA / thread-sync code.
 *
 * CURIOSITY: the beql target lands at `ori a2, a2, 0x2` (0x4C), SKIPPING
 * the preceding `lui a2, 0x1234` (0x48). For this not to be broken, $a2
 * must be caller-set to 0x12340000 (so both arms converge a2 == 0x12340002).
 * Yet another caller-set int-reg case — adds $a2 to the list of caller-set
 * register conventions in 1080's game_libs.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_0006612C(int *self) {
    /* a2 incoming = 0x12340000 magic-base (caller-set int-reg convention). */
    int v;
    v = (int)gl_func_00000000(self, (char*)self[0x28 / 4] + 8);
    while (v != 0x12340004) {
        v = (int)gl_func_00000000(self, (char*)self[0x28 / 4] + 8);
    }
    gl_func_00000000(self, (char*)self[0x28 / 4] + 8, 0x12340002);
    v = (int)gl_func_00000000(self, (char*)self[0x28 / 4] + 8);
    while (v != 0x12340003) {
        v = (int)gl_func_00000000(self, (char*)self[0x28 / 4] + 8);
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
extern char gl_ref_00022498;
int gl_func_00066384(int a0) {
    return gl_func_00000000(&gl_ref_00022498, a0);
}

extern int gl_func_00000000();
extern char gl_ref_000224B0;
int gl_func_000663AC() {
    return gl_func_00000000(&gl_ref_000224B0);
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

#ifdef NON_MATCHING
/* gl_func_000665B4: too-big-N-function-bundle (declared size 0xC0, 48 words).
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
            v1 = gl_func_00000000(0, *(int *)a0);
            *(int *)(a0 + 4) = v1;
            *(int *)(a0 + 8) += 1;
        }
        v0 = gl_func_00000000(v1);
        if (v0 == 0) {
            *(int *)(a0 + 4) = 0;
        }
    } while (v0 == 0);
    return v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000665B4);
#endif


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

#ifdef NON_MATCHING
/* Returns the address constant 0x41310 (target: `lui v0,0x4; jr ra; addiu v0,
 * v0,0x1310` — ADDRESS-style lui+addiu). `return 0x41310` emits lui+ORI instead;
 * the addiu form requires referencing a symbol defined at 0x41310 (an address
 * inside game_libs between 412E0 and 41820 — a code/data label with no clean
 * symbol). Matching needs a gl_ref/undefined_syms entry → reloc-resolved %-mover;
 * deferred (disproportionate setup for a 3-insn fn). See IDO_CODEGEN
 * #feedback-return-const-lui-addiu-vs-lui-ori. */
int game_libs_func_000666FC(void) {
    return 0x41310;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000666FC);
#endif

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

#ifdef NON_MATCHING
/* gl_func_00066720: 29-insn chunked-transfer loop. Splits a (src, dst, len)
 * transfer into 0x2710 = 10000-byte chunks, calling gl_func_00000000 per
 * chunk. Early-exits on len==0.
 *
 * 58.6% match — structural decode correct, cap is the 0x2710 inlining:
 *   target: `addiu s0, 0, 0x2710; sltu at, s1, s0` (2 insns, register cmp)
 *   c-emit: `sltiu at, s1, 0x2710` (1 insn, immediate cmp)
 * IDO -O2 constant-folds chunk = 0x2710 into the sltiu when chunk is
 * function-local and the value is visible. To force the addiu+sltu pair,
 * 0x2710 must be opaque (memory load, asm barrier, or extern const) —
 * none of which the source likely had. Plus 1-insn prologue-spill order
 * (target spills s0 first, IDO defers s0 spill to after assignments).
 *
 * Variants tried 2026-05-15: int len, unsigned int len, register-keyword
 * on chunk — all 17/29 same. */
void gl_func_00066720(char *src, char *dst, unsigned int len) {
    unsigned int chunk;
    if (len == 0) return;
    do {
        chunk = 0x2710;
        if (len < chunk) chunk = len;
        gl_func_00000000(src, dst, chunk);
        len -= chunk;
        src += chunk;
        dst += chunk;
    } while (len != 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066720);
#endif

#ifdef NON_MATCHING
/* gl_func_00066794: 31-insn chunked transfer w/ 10000-byte limit (0x7C, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   if (count == 0) return;
 *   do {
 *       chunk = min(count, 10000);                  // 0x2710 limit (DMA boundary)
 *       func(dst, src, chunk);                       // perform transfer
 *       count -= chunk;
 *       src   += chunk;                              // advance per chunk
 *       dst   += chunk;
 *   } while (count != 0);
 *
 * The 0x2710 (10000) limit is a classic DMA boundary on N64 (libultra
 * osPiStartDma's per-call maximum). This wrapper amortizes large transfers
 * across multiple sub-DMA calls.
 *
 * Frame saves s0-s3 + ra (5 regs, 0x28 frame). The min() is emitted as
 * `sltu at, count, limit; beq at,$0,skip; move chunk, limit; <delay slot>;
 * move chunk, count` — IDO -O2 standard for ternary on unsigned comparison.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
void gl_func_00066794(char *dst, char *src, unsigned int count) {
    unsigned int limit = 10000;
    unsigned int chunk;
    if (count == 0) return;
    do {
        chunk = (count < limit) ? count : limit;
        gl_func_00000000(dst, src, chunk);
        count -= chunk;
        src += chunk;
        dst += chunk;
    } while (count != 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066794);
#endif
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

    ((int(*)())gl_func_00062F64)(0xFE);
    ((int(*)())gl_func_00062F64)(0x96, 0x41688U, 0x415C0, 0x32);
    ((int(*)())gl_func_00062F64)();
    ((int(*)())gl_func_00062F64)(0xA0);
    ((int(*)())gl_func_00062F64)(0x42);
    ((int(*)())gl_func_00062F64)(1);
    temp_v0 = *(int*)0;
    temp_a1 = FW(temp_v0, 0xC);
    if (temp_a1 != 0) {
        ((int(*)())gl_func_00062F64)(0x2114, temp_a1, FW(temp_v0, 0x14), FW(temp_v0, 0x1C));
    }
    temp_a1_2 = FW((*(int*)0), 0x8);
    if (temp_a1_2 != 0) {
        ((int(*)())gl_func_00062F64)(0x2138, temp_a1_2, FW((*(int*)0), 0x10));
    }
    ((int(*)())gl_func_00062F64)(FW((*(int*)0), 0x0), FW((*(int*)0), 0x4));
    ((int(*)())gl_func_00062F64)(0x2154, (u32) (FW((*(int*)0), 0x0) + 0x80000000) >> 0xA);
    FW((*(int*)0), 0x80) = 0;
    FW((*(int*)0), 0x34) = 0;
    FW((*(int*)0), 0x84) = 0;
    FW((*(int*)0), 0x98) = 0;
    FW((*(int*)0), 0x9C) = 0;
    FW((*(int*)0), 0x94) = 0;
    ((int(*)())gl_func_00062F64)(0x216C);
    ((int(*)())gl_func_00062F64)();
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

#ifdef NON_MATCHING
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
#else
#ifdef NON_MATCHING
/* gl_func_00066A50: 37-insn panic/hang. Logs an error via the (collapsed)
 * callback (fmt @ 0x3F160, args 2/&global/0 + stack 0x41310,0xA), writes the
 * 0x12345678 magic into the canary words at 0x3F310/0x3F314 (the canary SETTER,
 * sibling of the gl_func_00066AF0 checker), logs again, calls a halt, then loops
 * forever (b .). NM (reference decode): collapsed-placeholder calls + collapsed
 * D ref + fixed absolute addresses (raw-.word game_libs reloc depression). */
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00066A50(int a0) {
    gl_func_00000000(0x3F160, 2, &D_00000000, 0, 0x41310, 0xA);
    *(int *)0x3F310 = 0x12345678;
    *(int *)0x3F314 = 0x12345678;
    gl_func_00000000(0x3F160);
    gl_func_00000000(0, 0);
    for (;;) {
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066A50);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00066AE4);
#endif

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
    ((int(*)())gl_func_00062F64)(temp_s4, (int)arg0 + 0x13EC, (int)arg0 + 0x1218);
    var_s1 = 0;
    do {
        temp_s0 = 1 << var_s1;
        if (FW(arg0, 0x13EC) & temp_s0) {
            temp_s2 = (int)arg0 + (var_s1 * 4);
            if (!(FW(temp_s2, 0x121B) & 8)) {
                ((int(*)())gl_func_00062F64)(0x22570, var_s1);
                sp53 = 0;
                ((int(*)())gl_func_00062F64)(temp_s4, (s32) &sp53);
                if (sp53 & temp_s0) {
                    temp_s0_2 = (int)arg0 + (var_s1 * 0x68) + 0x1228;
                    temp_v0 = ((int(*)())gl_func_00062F64)(temp_s4, (s32) temp_s0_2, var_s1);
                    if (temp_v0 == 0xA) {
                        if (((int(*)())gl_func_00062F64)(temp_s4, (s32) temp_s0_2, var_s1) != 0) {
                            ((int(*)())gl_func_00062F64)(0x22584);
                            FW(temp_s2, 0x13C8) = 0;
                        } else {
                            ((int(*)())gl_func_00062F64)(0x2258C);
                            FW(temp_s2, 0x13C8) = 2;
                            FW(((int)arg0 + var_s1), 0x13DC) = 1;
                        }
                    } else if (temp_v0 == 0) {
                        ((int(*)())gl_func_00062F64)(0x22594);
                        FW(temp_s2, 0x13C8) = 1;
                    }
                } else {
                    ((int(*)())gl_func_00062F64)(0x22598);
                }
                ((int(*)())gl_func_00062F64)(0x225A0);
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
    ((int(*)())gl_func_00062F64)(temp_s4, &sp54, 1);
    temp_v1 = *(int*)sp54;
    if (temp_v1 == 0) {
        goto loop_1;
    }
    if (temp_v1 == 5) {
        sp4F = 0;
        ((int(*)())gl_func_00062F64)(temp_s4, (s32 **) &sp4F);
        var_s0 = 0;
        do {
            if (sp4F & (1 << var_s0)) {
                temp_s1 = (int)arg0 + (var_s0 * 0x68) + 0x1228;
                if (((int(*)())gl_func_00062F64)(temp_s4, temp_s1, var_s0) == 0) {
                    ((int(*)())gl_func_00062F64)(temp_s1);
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
                ((int(*)())gl_func_00062F64)(arg0, var_s0_2, FW(var_s1, 0x13E0));
                var_s0_2 += 1;
                var_s1 += 2;
            } while (var_s0_2 != (s32 **)4);
        }
        ((int(*)())gl_func_00062F64)(temp_s4);
        FW(arg0, 0x13E8) = 0;
        goto loop_1;
    }
    if (temp_v1 == 4) {
        goto loop_1;
    }
    if (temp_v1 != 2) {
        goto loop_1;
    }
    ((int(*)())gl_func_00062F64)((int)arg0 + 0x1200);
    if (var_s6 == 0) {
        ((int(*)())gl_func_00062F64)(arg0);
    }
    FW(arg0, 0x13E8) = 1;
    goto loop_1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066EEC);
#endif

#ifdef NON_MATCHING
/* gl_func_00067084: 44-insn indexed-entry state-toggle (0xB0, frame 0x20).
 *
 * Decoded structure (raw-word disasm):
 *   v1 = a0 + a1;                                    // index helper (a1 = byte offset)
 *   if (v1->byte[0x13DC] == 0) return;                // gate 1: enabled flag
 *   if (v1->byte[0x13D8] == a2) return;               // gate 2: already in state a2
 *   // Compute 104-byte-stride entry: addr = a0 + a1*104 + 0x1228
 *   addr = a0 + 104*a1 + 0x1228;
 *   if (a2 != 0) {
 *       if (func(addr) == 0) {                        // alloc/setup fail
 *           v1->byte[0x13D8] = 3;
 *       }
 *   } else {
 *       if (func(addr) != 0) {                        // destroy/teardown success
 *           if (v1->byte[0x13D8] > 0) {
 *               v1->byte[0x13D8] -= 1;                 // decrement counter
 *           }
 *       }
 *   }
 *
 * The `104*a1` multiplication is emitted as `sll t,2; subu t-a1; sll t,2;
 * addu t+a1; sll t,3` — i.e., 13*a1*8 via shift-subtract-shift chain
 * (cheaper than `mul`). 0x1228 is the offset into the indexed-entry array.
 * 0x13D8/0x13DC are byte fields at the entry's flags-region.
 *
 * 99.41% NM (2026-06-02, was 85.09%). Three structural fixes (+14pp):
 *  (1) gate-2 compare is `(unsigned char)v1[0x13D8] == a2` (lbu + direct
 *      compare); the `(char)a2` cast added a spurious `andi`.
 *  (2) dropped the unused 4th param (`int arg3`) — frees $a3 so IDO reuses it
 *      to hold original-a0 (target `or a3,a0`) instead of spilling a0 to stack.
 *  (3) decrement is plain `if (v1[0x13D8] > 0) v1[0x13D8]--;` — the
 *      `(signed char)`/`(char)` casts forced a redundant sll/sra sign-extend.
 * Residual ~0.6% = frame 0x28-vs-0x20 + the `addu a0,a0,t8` operand order on
 * the 104*a1 address adds — regalloc/scheduling, permuter-class.
 */
void gl_func_00067084(char *a0, int a1, int a2) {
    char *v1 = a0 + a1;
    char *addr;
    if (v1[0x13DC] == 0) return;
    if ((unsigned char)v1[0x13D8] == a2) return;
    addr = a0 + 104 * a1 + 0x1228;
    if (a2 != 0) {
        if (gl_func_00000000(addr) == 0) {
            v1[0x13D8] = 3;
        }
    } else {
        if (gl_func_00000000(addr) != 0) {
            if (v1[0x13D8] > 0) {
                v1[0x13D8]--;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067084);
#endif

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
 *   if (a0->[0x13E8] != 0) return;
 *   do { gl_func_00000000(); } while (a0->[0x13E8] == 0);
 *
 * 76.5 % byte-exact (13/17). Cap is the prologue-schedule order:
 * target emits `sw s0; move s0, a0; sw ra; lw t6, 0x13E8(s0)`,
 * built emits `sw ra; sw s0; lw t6, 0x13E8(a0); move s0, a0` —
 * IDO scheduler picks lw-via-a0 first then move; target picks
 * move-then-lw-via-s0. Tried plain `int *a0`, `register int *s0`,
 * and `int v = ...` named-local — all stay at 76.5 % or regress
 * (58.8 %). Cap class: IDO scheduler choice not C-controllable. */
void gl_func_00067220(int *a0) {
    register int *s0 = a0;
    if (s0[0x13E8 / 4] != 0) {
        return;
    }
    do {
        gl_func_00000000();
    } while (s0[0x13E8 / 4] == 0);
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
    if (counter < 31) return;                  // (sltiu < 31 → branch when not yet 31+)
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

void gl_func_00067370(void) {
    gl_func_00000000();
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00067370_pad.s")

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
    extern int gl_data_67470_addr;
    gl_func_00000000(&gl_data_67470_addr, a0[13], a1);
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
 * call gl_func(&D_0, a0); v0 &= (1 << (a0->[0x34] + 31)). Return v0. */
#ifdef NON_MATCHING
int gl_func_00067550(int *a0) {
    int v0 = 0;
    if (a0[0x34/4] != 0) {
        v0 = gl_func_00000000(&D_00000000, a0);
        v0 = v0 & (1 << (a0[0x34/4] + 31));
    }
    return v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067550);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000675A4);

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
extern char gl_ref_00022604;

void gl_func_00067A10(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x5C) = a1;
    *(int*)(a0 + 0x50) = 0;
    *(int*)(a0 + 0x54) = a2;
    *(int*)(a0 + 0x4C) = 1;
    gl_func_00000000(&gl_ref_00022604, *(int*)(a0 + 0x34));
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067ABC);

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
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00067B04);

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
extern char gl_ref_0002B3B8;

void gl_func_000682F8(int *self) {
    gl_func_00000000(self + 5, &gl_ref_0002B3B8, self);
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

void gl_func_00068350(int *self) {
    int *vtable = (int *)self[7];                         /* self->[0x1C] */
    /* inline function-ptr call → jalr $t9 per feedback-ido-indirect-call-t9 */
    (*(int(**)(int *))((char *)vtable + 0xC))((int *)(((short *)vtable)[4] + (char *)self));
    gl_func_00000000(self + 4);
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
 * explicit-local insertions grow the frame to 0x38. Stays NM. */
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
extern char gl_ref_0002B420;

int *gl_func_00068884(int *a0, int a1) {
    if (a0 == 0) {
        a0 = (int *)gl_func_00000000(0x38);
        if (a0 == 0) goto end;
    }
    gl_func_00000000(a0, &gl_ref_0002B420, 0);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00068BAC_pad.s")

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

    ((int(*)())gl_func_00062F64)();
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
    temp_v0_3 = ((int(*)())gl_func_00062F64)(0, (char *)0x2C568, temp_a2, 0);
    sp2C = temp_v0_3;
    ((int(*)())gl_func_00062F64)(FW(temp_v0_3, 0x44) * 8);
    temp_v0_4 = ((int(*)())gl_func_00062F64)(0, (char *)0x2C574, 0, sp2C);
    FW(arg0, 0x28) = temp_v0_4;
    FW(arg0, 0x10) = temp_v0_4;
    FW(temp_v0_4, 0x30) = (s32) (FW(temp_v0_4, 0x30) & ~0x400);
    temp_t0 = FW(arg0, 0x28);
    FW(temp_t0, 0x30) = (s32) (FW(temp_t0, 0x30) & ~0x800);
    if (sp30 == 0) {
        ((int(*)())gl_func_00062F64)(0x2C580);
    }
    temp_v0_5 = FW(FW(FW(arg0, 0x3C), 0x3C), 0xC);
    temp_t0_2 = FW(temp_v0_5, 0x28);
    ((GP_00068DD4)FW(temp_t0_2, 0x14))(FW(temp_t0_2, 0x10) + temp_v0_5);
    temp_v0_6 = ((int(*)())gl_func_00062F64)(sp30, FW(FW(arg0, 0x3C), 0xC), (s32) FW(arg0, 0x28));
    sp24 = temp_v0_6;
    ((int(*)())gl_func_00062F64)((s32) FW(FW(arg0, 0x3C), 0xC), temp_v0_6);
    ((int(*)())gl_func_00062F64)((s32) sp24);
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
 * (m2c-confirmed). 87.3% reg-blind (same 79-insn count). Residual: tail regalloc
 * — target reloads arg1 into the dead arg2 reg (s1) and increments in-place,
 * spilling a1ptr to 32(sp); my clean form spills p instead → +16-byte frame +
 * cascaded sp-offsets (forcing arg1 in-place promotes it to an extra saved reg,
 * worse). Also 0x2C5B0 wants lui+addiu (symbol-reloc) not lui+ori (literal).
 * Caps: self/arg2 structs + 3 cb prototypes untyped (USO-reloc). Kept NON_MATCHING. */
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
        gl_func_00000000(0x2C5B0);
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
            src = (short *)(*(char **)(arg2 + 0x60) + k);
            dst = (short *)(*(char **)(self + 0x3C) + k);
            k += 6;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
        } while (i < (unsigned int)*(int *)(arg2 + 0x40));
    }
    *(char **)(self + 0x34) = arg2;
    gl_func_00000000(self);
    a1ptr = self + 0x50;
    p = arg1 + 0x70;
    gl_func_00000000(p, a1ptr);
    *(char **)(*(char **)(self + 0x34) + 0xA8) = a1ptr;
    *(char **)(*(char **)(self + 0x34) + 0xAC) = p;
    return *(char **)(self + 0x34);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069688);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000697C4);

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

void gl_func_00069C58(char *a0) {
    int local;
    gl_func_00000000(&local);
    gl_func_00000000(a0 + 0x10);
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

    temp_s0 = ((int(*)())gl_func_00062F64)();
    if (FW(arg0, 0x8) >= FW(arg0, 0x10)) {
loop_1:
        if (arg2 == 1) {
            FW((*(int*)0), 0x10) = 8;
            ((int(*)())gl_func_00062F64)((int)arg0 + 4);
            if (FW(arg0, 0x8) < FW(arg0, 0x10)) {
                goto block_5;
            }
            goto loop_1;
        }
        ((int(*)())gl_func_00062F64)(temp_s0);
        return -1;
    }
block_5:
    *(int*)(FW(arg0, 0x14) + (((s32) (FW(arg0, 0xC) + FW(arg0, 0x8)) % (s32) FW(arg0, 0x10)) * 4)) = arg1;
    FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) + 1);
    if (*(int*)(FW(arg0, 0x0)) != 0) {
        ((int(*)())gl_func_00062F64)(((int(*)())gl_func_00062F64)(arg0));
    }
    ((int(*)())gl_func_00062F64)(temp_s0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069E04);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00069F50);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00069E04_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00069F64)();
s32 gl_func_00069F64(char *arg0, s32 *arg1, s32 arg2) {
    char *temp_s0;

    temp_s0 = ((int(*)())gl_func_00062F64)();
    if (FW(arg0, 0x8) == 0) {
loop_1:
        if (arg2 == 0) {
            ((int(*)())gl_func_00062F64)(temp_s0);
            return -1;
        }
        FW((*(int*)0), 0x10) = 8;
        ((int(*)())gl_func_00062F64)(arg0);
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
        ((int(*)())gl_func_00062F64)(((int(*)())gl_func_00062F64)((int)arg0 + 4));
    }
    ((int(*)())gl_func_00062F64)(temp_s0);
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
    ((int(*)())gl_func_00062F64)(sp1C, 0x40);
    ((int(*)())gl_func_00062F64)((char *)0x2B00);
    if (((int(*)())gl_func_00062F64)((char *)0x04001000) == -1) {
        do {

        } while (((int(*)())gl_func_00062F64)((char *)0x04001000) == -1);
    }
    if (((int(*)())gl_func_00062F64)((char *)1, 0x04000FC0, sp1C, 0x40) == -1) {
        do {

        } while (((int(*)())gl_func_00062F64)((char *)1, 0x04000FC0, sp1C, 0x40) == -1);
    }
    if (((int(*)())gl_func_00062F64)() != 0) {
        do {

        } while (((int(*)())gl_func_00062F64)() != 0);
    }
    if (((int(*)())gl_func_00062F64)((char *)1, 0x04001000, FW(sp1C, 0x8), FW(sp1C, 0xC)) == -1) {
        do {

        } while (((int(*)())gl_func_00062F64)((char *)1, 0x04001000, FW(sp1C, 0x8), FW(sp1C, 0xC)) == -1);
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006A5F0);

#ifdef NON_MATCHING
/* game_libs_func_0006AD68: v0 = *a0; *a0 = *(int*)v0 (double-deref); return v0.
 * Corrected from the prior *a0=*a0 mis-decode (asm derefs the loaded value:
 * lw v0,0(a0); lw,0(v0); sw,0(a0)). Residual: the intermediate lands in $t6
 * vs the target's $t9 -- a single-temp register-renumber cap.
 *
 * 2026-05-26 (re-screened): exhaustive variant grind confirms C-unreachable.
 * Tried 6 forms — all emit $t6 (or $t7 with comma-expr extra-temp):
 *   - int t = *(int*)v0; *a0 = t;             → $a1 (worse)
 *   - unsigned int*  a0;                       → $t6
 *   - *(volatile int *)a0 / *(volatile int *)v0 → $t6
 *   - (*a0 = *(int*)(*a0)), *(int*)*a0         → $t7
 *   - int **a0; (int*)*v0                      → $t6
 *   - register int t asm("$t9")                → IDO syntax error
 * Target's $t9 is from a different IDO state (likely surrounding-function
 * allocator-context spill), unreachable from a standalone C body. */
int game_libs_func_0006AD68(int *a0) {
    int v0 = *a0;
    *a0 = *(int *)v0;
    return v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006AD68);
#endif

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
    volatile int dummy;
    dummy = a0_unused;
    if (a3 == 0) goto out;
    do {
        if (a3 == a1) {
            *a2 = *a1;
            goto out;
        }
        a2 = a3;
        a3 = *(int**)a3;
    } while (a3 != 0);
out:
    ;
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
 * 2026-05-28 CLASSIFICATION: this is the libc `bzero`, which is HAND-WRITTEN
 * ASSEMBLY in every reference (libreultra/oot/papermario all ship src/.../bzero.s,
 * NOT a .c) — the swl unaligned-head + 8×sw unrolled block are hand-coded, not
 * compiler output. Per the /decompile skill's handwritten-libc rule, it is NOT
 * C-decompilable and stays INCLUDE_ASM permanently (the .s is the source of
 * truth). Do NOT attempt a C body. */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006B048);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006B0F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B0FC);

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

#ifdef NON_MATCHING
/* 20-insn 2-call init wrapper. Stores 1 to D_00000000 (via separate $at
 * temp), then calls gl_func(&D, 0x42750, 1) followed by gl_func(&D, 0, 0).
 * Declared size 0x58 includes 2 trailing dead insns (lui t6, 0; lw t6, 0(t6))
 * — stolen prologue setup for the successor.
 *
 * Two structural diffs from C-emit:
 * 1. Target loads &D into BOTH $at (for the sw 1) and $a0 (for the call).
 *    IDO's CSE makes mine reuse $a0 for both. Unique-extern alias not yet
 *    tried — could promote.
 * 2. Target encodes 0x42750 as `lui 0x4; addiu 0x2750`; mine encodes as
 *    `lui 0x4; ori 0x2750`. IDO picks ori for unsigned literals; addiu
 *    requires signed encoding. Castings tried: no flip from C.
 *
 * Default INCLUDE_ASM build matches. */
void gl_func_0006B9B4(void) {
    *(int*)&D_00000000 = 1;
    gl_func_00000000(&D_00000000, (void*)0x42750, 1);
    gl_func_00000000(&D_00000000, 0, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B9B4);
#endif
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006BC44);

#ifdef NON_MATCHING
/* gl_func_0006BC4C: 50-insn unaligned-load + byte-format-translate loop (0xC8, frame 0x18).
 *
 * Decoded structure (raw-word disasm):
 *   if (count <= 0) return;
 *   for (i = 0; i < count; i++) {
 *       // Unaligned word load via lwl/lwr (LE pair):
 *       int word_lo = lwl/lwr from src+0..3;
 *       int word_hi = lwl/lwr from src+4..7;
 *       *(int*)tmp_buf = word_lo;
 *       *(int*)(tmp_buf+4) = word_hi;
 *
 *       // Byte mask + shift + merge for nibble-pair processing:
 *       byte t = src->[0xE] & 0xC0;
 *       byte t_shifted = t >> 6 << 2 | t_other;       // pack into result halfword
 *       *(short*)dst = packed;
 *
 *       // Carry / adjust + dst-byte writes from tmp_buf
 *       advance pointers (src += stride, dst += stride);
 *   }
 *
 * Multi-byte format translation using lwl/lwr unaligned loads followed by
 * bit-field extract and short-store. Likely a packed-data-decoder
 * (palette indexes, 4-bit nibble unpacking, or similar bit-packed format).
 * Complex bit-twiddling — exact bit-layout depends on caller's data format.
 *
 * The `count <= 0` guard at top exits early on empty input. Loop body
 * advances by ~8 bytes/iter (matches lwl/lwr alignment + stride of byte
 * writes at sp+0x7, +0xE, +0x10).
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path
 * (lwl/lwr unaligned-load idiom is hard to reproduce from standard C
 * without intrinsics; bit-field shape needs source-data knowledge).
 */
void gl_func_0006BC4C(int count, void *src, void *dst, int unused) {
    /* Approximate structural decode. Real body uses lwl/lwr for unaligned
     * source reads + byte-level format translation. INCLUDE_ASM is the
     * authoritative build path. */
    int i;
    char *s = (char*)src;
    char *d = (char*)dst;
    if (count <= 0) return;
    for (i = 0; i < count; i++) {
        unsigned int t = (unsigned char)s[0xE] & 0xC0;
        *(short*)d = (short)((t >> 6) << 2);  /* approximate packing */
        d += 8;
        s += 8;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BC4C);
#endif

#ifdef NON_MATCHING
/* gl_func_0006BD14: 61-insn sibling of gl_func_0006D6F4 with prepended 60-byte CLEAR loop.
 * Size 0xF4, frame 0x10.
 *
 * SIBLING IDENTIFICATION: shares the template-emit code structure of
 * gl_func_0006D6F4 (8-byte template {0xFF,1,3,a0,0xFF×4}, unaligned swl/swr
 * store loop, 0xFE terminator). The DIFFERENCE is a 60-byte clear-loop
 * prefix that zeroes D+0..D+0x38, which ALWAYS makes the emit loop dead
 * because the loop-bound at D+0 is then 0.
 *
 * Decoded structure (raw-word disasm):
 *   void reset_and_terminate(int unused_a0 [masked to u8]) {
 *       // STAGE 1: Clear 60-byte state table (15 int slots) at D+0..D+0x38
 *       for (int i = 0; i < 15; i++) {
 *           *(int*)((char*)&D_00000000 + i*4) = 0;
 *       }
 *
 *       // STAGE 2: Read OLD count (now 0 after clear) for emit-skip gate
 *       int orig_count = *(uint8_t*)&D_00000000;     // = 0 always
 *
 *       // STAGE 3: Sister boilerplate from gl_func_0006D6F4 (dead-ish)
 *       *(int*)((char*)&D_00000000 + 0x3C) = 1;       // active flag
 *       uint8_t buf[8] = {0xFF, 0x01, 0x03, a0, 0xFF, 0xFF, 0xFF, 0xFF};
 *
 *       // STAGE 4: emit-loop entry (DEAD due to orig_count = 0)
 *       if (orig_count <= 0) goto write_sentinel;
 *       // (would emit template records to D_global_ptr if reached — never is)
 *
 *   write_sentinel:
 *       *(uint8_t*)(&D_00000000 + 0) = 0xFE;          // terminator byte at D+0
 *   }
 *
 * Notes:
 *  - Sibling of gl_func_0006D6F4 — likely produced by source-code variant
 *    where the same template-build/emit code is shared between "append" and
 *    "reset" variants. IDO didn't dead-code-eliminate the emit-loop because
 *    it depends on a global byte value, not a constant.
 *  - The 60-byte (15-slot) clear establishes the structure: D+0..D+0x38 is
 *    a 60-byte status table, D+0x3C is the activity flag. Consistent with the
 *    record-stream layout in 0006D6F4.
 *  - 0xFE terminator at D+0 = "all records reset, list-end marker present".
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BD14);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BD14_pad.s")

/* gl_func_0006BE14: stores 1 to D_00000000, then gl_func(<sym_b>, &D+0x42800, 1)
 * and gl_func(<sym_c>, 0, 0). MATCH: the 0x42800 arg is a SYMBOL reference
 * (&D_00000000 + 0x42800 -> lui 0x4; addiu 0x2800), not a literal (which gives
 * lui; ori). Decode the symbol, don't literal-match
 * (docs/IDO_CODEGEN.md#feedback-return-const-lui-addiu-vs-lui-ori). Real size
 * 0x50 (the .s's 0x58 over-extends 2 insns into successor 0006BE64). Byte-exact. */
extern char gl_data_BE14_b;
extern char gl_data_BE14_c;
void gl_func_0006BE14(void) {
    *(int*)&D_00000000 = 1;
    gl_func_00000000(&gl_data_BE14_b, (char*)&D_00000000 + 0x42800, 1);
    gl_func_00000000(&gl_data_BE14_c, 0, 0);
}
/* game_libs_func_0006BE64 (2-word splat mis-split: lui t6,0; lw t6,0(t6)) was
 * the stolen prologue of gl_func_0006BE6C — forward-merged into it (orphan-fn
 * removed). gl_func_0006BE6C MATCHED. */
void gl_func_0006BE6C(void) {
    int local;
    int pad;
    if (*(int*)&D_00000000 == 0) {
        gl_func_00000000();
    }
    gl_func_00000000(&D_00000000, &local, 1);
}

void gl_func_0006BEA8(void) {
    gl_func_00000000(&D_00000000, 0, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BEA8_pad.s")

/*
 * gl_func_0006BF34: 81-insn struct-init constructor.
 *   Args: (T *self, int a1, int a2, int a3, int arg5, int arg6)
 *     - arg5 / arg6 are stack-passed (sp+0x3C / sp+0x38 from caller).
 *   Field writes (offsets relative to a0):
 *     +0x00 = 0          +0x04 = arg5         +0x08 = 0
 *     +0x0C = D_NNNN_a   +0x10 = (s16) 1      +0x12 = (s16) 0
 *     +0x14 = a1         +0x18 = 0
 *     +0x38/+0x3C = (long long) a3
 *     +0xF0/+0xF4 = (long long)(arg6 - 16)
 *     +0x100/+0x104 = (long long)(int) &D_NNNN
 *     +0x118 = 0xFF03    +0x11C = a2
 *     +0x128 = 0x3F      +0x12C = 0x01000800
 *   Then: v0 = gl_func_00000000(); a0->0xC = D_NNNN_a; D_NNNN_b = a0;
 *         gl_func_00000000(v0);
 *   Open: the 0x3F at +0x128 is computed via spill+and+srl of constant
 *   0x003FFF01 (lui 0x3F + ori 0xFF01); looks like a bit-field extract.
 */
#ifdef NON_MATCHING
extern int D_00000000;
void gl_func_0006BF34(int *a0, int a1, int a2, int a3, int arg5, int arg6) {
    int *volatile self = a0;                        /* force reload of base each write */
    int v0_save;
    int x = 0x3FFF01;
    *(int*)((char*)self + 0x14) = a1;
    *(int*)((char*)self + 0x4) = arg5;
    *(int*)((char*)self + 0x0) = 0;
    *(int*)((char*)self + 0x8) = 0;
    *(int*)((char*)self + 0x11C) = a2;
    *(long long*)((char*)self + 0x38) = (long long)a3;
    *(long long*)((char*)self + 0xF0) = (long long)(arg6 - 16);
    *(long long*)((char*)self + 0x100) = (long long)(int)&D_00000000;
    *(int*)((char*)self + 0x118) = 0xFF03;
    *(int*)((char*)self + 0x128) = (x & 0x3F0000) >> 16;
    *(int*)((char*)self + 0x12C) = 0x01000800;
    *(int*)((char*)self + 0x18) = 0;
    *(short*)((char*)self + 0x10) = 1;
    *(short*)((char*)self + 0x12) = 0;
    v0_save = gl_func_00000000();
    *(int*)((char*)self + 0xC) = D_00000000;
    D_00000000 = (int)self;
    gl_func_00000000(v0_save);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BF34);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006BF34_pad.s")
#endif

#ifdef NON_MATCHING
/* gl_func_0006C084: 38-insn one-time init w/ guarded heavy path (0x98, frame 0x20).
 *
 * Decoded structure (raw-word disasm):
 *   func1(a0);
 *   if (D_lock_flag != 1) {
 *       func_at_0x80824();                          // direct-addr jal (not a sym)
 *       func3(1, &D_sym1);
 *       func4(a0, 0, 1);                            // 3-arg
 *   }
 *   // Always-run tail:
 *   v0_ret = func5(0, &D_sym2);
 *   func6();
 *   D_lock_flag = 1;                                 // sb 1 to lock
 *   return v0_ret;                                   // func5's result via sp+0x1C
 *
 * The `D_lock_flag` is a 1-byte (sb) global that guards re-running the
 * heavy init path on subsequent calls — classic "once" idiom.
 *
 * The `jal 0x80824` at offset 0x28 is a direct hardcoded jal-to-absolute,
 * not a relocated symbol — unusual for IDO; suggests inlined libc thunk.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_0006C084(int a0) {
    extern char D_lock_flag;
    extern int D_sym1, D_sym2;
    int v0_ret;
    gl_func_00000000(a0);
    if (D_lock_flag != 1) {
        ((void(*)(void))0x80824)();
        gl_func_00000000(1, &D_sym1);
        gl_func_00000000(a0, 0, 1);
    }
    v0_ret = (int)gl_func_00000000(0, &D_sym2);
    gl_func_00000000();
    D_lock_flag = 1;
    return v0_ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C084);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C110);

#ifdef NON_MATCHING
/* gl_func_0006C11C: 39-insn tagged-record-stream decoder loop (size 0x9C, frame 0x10).
 *
 * Decoded structure (raw-word disasm):
 *   void f(uint8_t *dst,         // $a0 — destination cursor (advanced +6 per iter)
 *          uint8_t *src,         // $t6 caller-set — source 8-byte records (advanced +8 per iter)
 *          int     count)        // $t7 caller-set — loop bound
 *   {
 *       int idx = 0;
 *       uint8_t buf[8];          // scratch on stack at sp+0x4
 *
 *       if (count <= 0) return;
 *       while (1) {
 *           // Read 8 unaligned bytes from src into buf
 *           lwl/lwr buf+0 = *(src+0..3);
 *           lwl/lwr buf+4 = *(src+4..7);
 *           uint8_t tag2 = (buf[2] & 0xC0) >> 4;  // top-2-bits → 0/4/8/0xC code
 *           dst[4] = tag2;
 *           if (tag2 == 0) {                      // case 0: full payload
 *               *(uint16_t*)(dst+0) = *(uint16_t*)(buf+4);  // [sp+0x8 = buf+4]
 *               *(int8_t  *)(dst+2) = *(int8_t  *)(buf+6);  // [sp+0xA = buf+6]
 *               *(int8_t  *)(dst+3) = *(int8_t  *)(buf+7);  // [sp+0xB = buf+7]
 *           }
 *           // (other tag codes leave dst+0..3 untouched, just dst+4 = tag2)
 *
 *           idx++;
 *           src += 8;
 *           dst += 6;
 *           if (idx >= *(uint8_t*)&D_00000000) break;   // limit byte at D+0
 *           // (note: limit reloaded from D+0 every iter — not hoisted)
 *       }
 *   }
 *
 * Notes:
 *  - $t6 and $t7 caller-set (no init in this function); both fit caller-set-int-reg
 *    cap (feedback_caller_set_int_reg_cap_1080_game_libs.md).
 *  - The 2-bit tag at top of buf[2] is interesting: a 4-way dispatch where only
 *    code 0 (no escape bits) writes the full halfword+2bytes payload to dst.
 *    Codes 1-3 just emit dst[4]=tag and leave dst+0..3 stale.
 *  - lwl/lwr unaligned-load pair indicates src may be arbitrarily aligned
 *    (asm-processor pattern; preserves IDO codegen).
 *  - Limit `*(uint8_t*)&D_00000000` is loaded every iter (no LICM by IDO -O2
 *    because it's a global volatile-equivalent access).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C11C);
#endif

#ifdef NON_MATCHING
/* gl_func_0006C1B8: 61-insn reset-sibling of gl_func_0006BD14 (size 0xF4, frame 0x10).
 *
 * SAME STRUCTURE as gl_func_0006BD14:
 *   1. 15-iter loop clears 60-byte table at D+0..D+0x38
 *   2. Reads D+0 byte (now 0) for emit-skip gate
 *   3. Sets D+0x3C = 1 (active flag)
 *   4. Builds 8-byte template buf
 *   5. Emit-record loop GATED on orig_count > 0 — always skipped (dead)
 *   6. Writes 0xFE terminator byte at D+0
 *
 * DIFFERENCE: template bytes
 *     gl_func_0006BD14 template: {0xFF, 0x01, 0x03, a0_in,  0xFF, 0xFF, 0xFF, 0xFF}
 *     gl_func_0006C1B8 template: {0xFF, 0x01, 0x04, 0x01,   0xFF, 0xFF, 0xFF, 0xFF}
 *                                            type^^  ^subtype
 *
 *   This sibling resets-with-type=4-subtype=1 (vs 0006BD14's type=3-subtype-from-arg).
 *   Also uses NO ARGS — `a0` isn't read by this function; subtype is hardcoded 1.
 *
 * Decoded structure (raw-word disasm):
 *   void reset_type4(void) {  // takes no arg; a0 unused
 *       for (int i = 0; i < 15; i++) {
 *           *(int*)((char*)&D_00000000 + i*4) = 0;
 *       }
 *       int orig_count = *(uint8_t*)&D_00000000;     // = 0 after clear
 *       *(int*)((char*)&D_00000000 + 0x3C) = 1;       // active flag
 *
 *       // Build template: {0xFF, 0x01, 0x04, 0x01, 0xFF, 0xFF, 0xFF, 0xFF}
 *       // Note: bytes [4,5] written as `sh 0xFFFF` (halfword), [6,7] as `sb 0xFF` each
 *
 *       if (orig_count > 0) {
 *           // emit-record loop — DEAD due to clear
 *           ...
 *       }
 *       *(uint8_t*)((char*)&D_00000000) = 0xFE;        // terminator
 *   }
 *
 * Notes:
 *  - Uses `sh $tN, 0x8(sp)` (store halfword) for the middle 2 bytes vs
 *    individual `sb` stores in 0006BD14. Same byte values, different
 *    instruction widths — likely IDO register allocation chose halfword
 *    because the constant 0xFFFF fits one ori-into-low-half.
 *  - No argument used: confirms this is a fixed-shape reset for one
 *    specific record type (type=4-subtype=1).
 *  - Trailing 2-insn `lui $t6,0; lw $t6,0xC($t6)` fragment post-epilogue —
 *    incomplete fragment per feedback_splat_too_big_incomplete_fragment_tail.md.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C1B8);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C2A4);

#ifdef NON_MATCHING
/* gl_func_0006C2AC: 52-insn caller-set-$t6 gate + multi-byte/word global init (0xD0, frame 0x20).
 *
 * Decoded structure (raw-word disasm):
 *   if (caller_t6 != 0xA6000000) {                   // caller-set-$t6 gate (cap class)
 *       goto skip;                                    // return stored value
 *   }
 *   // Init: write byte/word fields to several D_sym globals:
 *   *(byte*)&D_a = 1;                                 // sb 1, &D_a+0x4
 *   *(int*) &D_b = 0xA6000000;                        // sw to +0xC
 *   *(byte*)&D_c = 0x40;                              // sb 0x40, +0x5
 *   *(byte*)&D_d = 7;                                 // sb 7, +0x8
 *   *(byte*)&D_e = 7;                                 // sb 7, +0x6
 *   *(byte*)&D_f = 2;                                 // sb 2, +0x7
 *   *(byte*)&D_g = 0;                                 // sb 0, +0x9
 *   *(int*) &D_h = 0;                                 // sw 0, +0x10
 *   func1(&D_arg + 0x14, 0x60);                       // 0x60-byte init
 *   func2();
 *   *(int*)&D_x = *(int*)&D_y;                        // copy a global
 *   func3(saved_x);                                   // post-init
 * skip:
 *   return *(int*)&D_result;
 *
 * CALLER-SET $t6 = 0xA6000000 gate (5th member of caller-set-int-reg cap
 * family — see feedback_caller_set_int_reg_cap_1080_game_libs memo).
 * The 0xA6000000 constant is unusual — not a standard N64 hardware base
 * (0xA460/0xA480/0xA404 etc.) — may be a custom MMIO or debug region.
 *
 * Sibling of gl_func_0006F088 (PI DOM2 hardware init); both are libultra-
 * style boot-time hardware register setup.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
/* Whole-body decode 2026-06-01. Guard on caller-set t6 == 0xA6000000; if not,
 * return D_result. Else init a D-state block (bytes at +4=1,+5=64,+6=7,+7=2,
 * +8=7,+9=0; words at +0xC=0xA6000000,+0x10=0), call gl(st+0x14, 0x60) + gl(),
 * then a tail (copy a D word, store a D ptr, gl(saved)) and return D_result. */
int gl_func_0006C2AC(void) {
    extern int t6_caller_state_0006C2AC;
    extern int D_result_sym_0006C2AC;
    extern char D_state_0006C2AC;
    extern int D_tailsrc_0006C2AC, D_taildst_0006C2AC, D_tailptr_0006C2AC;
    char *st = &D_state_0006C2AC;
    int saved;
    if (t6_caller_state_0006C2AC != (int)0xA6000000) {
        return D_result_sym_0006C2AC;
    }
    *(char *)(st + 4) = 1;
    *(int *)(st + 0xC) = (int)0xA6000000;
    *(char *)(st + 5) = 64;
    *(char *)(st + 8) = 7;
    *(char *)(st + 6) = 7;
    *(char *)(st + 7) = 2;
    *(char *)(st + 9) = 0;
    *(int *)(st + 0x10) = 0;
    gl_func_00000000(st + 0x14, 0x60);
    saved = gl_func_00000000();
    D_taildst_0006C2AC = D_tailsrc_0006C2AC;
    D_tailptr_0006C2AC = (int)&D_state_0006C2AC;
    gl_func_00000000(saved);
    return D_result_sym_0006C2AC;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C2AC);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C2AC_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006C384: too-big-N-function-bundle (declared 0xF4, 61 words) — 2 libultra cache helpers.
 *
 * SUB-FUNCTION 1 (0x6C384..0x6C400, 31 insns) — __osVirtualToPhysical / osVirtualToPhysical:
 *     uint32_t osVirtualToPhysical(void *vaddr) {
 *         uint32_t a = (uint32_t)vaddr;
 *         if (a >= 0x80000000 && a < 0xA0000000)
 *             return a & 0x1FFFFFFF;   // KSEG0 cached → physical
 *         if (a >= 0xA0000000 && a < 0xC0000000)
 *             return a & 0x1FFFFFFF;   // KSEG1 uncached → physical
 *         return runtime_helper(vaddr);  // KSEG2/KUSEG: page-table lookup via jal
 *     }
 *   Standard libultra/n64 virtual-to-physical translation. KSEG0+KSEG1 are
 *   direct-mapped with `& 0x1FFFFFFF`; KSEG2/KUSEG require a page-table walk
 *   delegated to a runtime helper (whose target is unresolved at splat time).
 *
 * SUB-FUNCTION 2 (0x6C400..0x6C478, 30 insns) — osInvalDCache:
 *     void osInvalDCache(void *vaddr, s32 nbytes) {
 *         if (nbytes <= 0) return;
 *         if (nbytes >= 0x2000) {                          // 8KB threshold
 *             // Full D-cache flush via index-writeback-invalidate
 *             char *p   = (char*)0x80000000;
 *             char *end = (char*)0x80001FF0;               // 8KB - 16
 *             do {
 *                 __asm("cache 0x1, 0(%0)" :: "r"(p));     // INDEX_WRITEBACK_INV_D
 *                 p += 0x10;
 *             } while (p < end);
 *         } else {
 *             // Hit-invalidate for small range, line-aligned
 *             char *p   = (char*)vaddr;
 *             char *end = (char*)vaddr + nbytes;
 *             if (p >= end) return;
 *             uint32_t pre = (uintptr_t)p & 0xF;
 *             p   -= pre;
 *             end -= 0x10;                                  // round end down
 *             do {
 *                 __asm("cache 0x19, 0(%0)" :: "r"(p));    // HIT_WRITEBACK_INV_D
 *                 p += 0x10;
 *             } while (p < end);
 *         }
 *     }
 *   Standard libultra osInvalDCache. 0x10 = D-cache line size. The 0x2000
 *   threshold = D-cache size = 8 KB. Two cache opcodes:
 *     cache 0x01 = Index Writeback Invalidate D (flush all cache slots by index)
 *     cache 0x19 = Hit Writeback Invalidate D   (line-by-line for given addresses)
 *
 * Notes:
 *  - libultra-class helpers — see libreultra `src/os/invaldcache.c` and
 *    `src/os/virtualtophysical.c` for canonical source. Likely byte-match
 *    via libreultra exact source if compiled with IDO. Could be promoted to
 *    full byte-exact if INCLUDE_ASM is replaced with proper libreultra body.
 *    For this tick: structural wrap + INCLUDE_ASM build path.
 *  - Two jr $ra in f2 (one early-out at 0x6C44C, one post-full-flush at
 *    0x6C470) are both valid exits from the same function — NOT a bundle
 *    boundary within f2.
 *  - Bundle has 3 total jr $ra (f1 + f2's two exits).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
#ifdef NON_MATCHING
/* gl_func_0006C384: 31-insn KSEG->physical address translator. For a0 in KSEG0
 * (0x80000000..0x9FFFFFFF) or KSEG1 (0xA0000000..0xBFFFFFFF), return
 * a0 & 0x1FFFFFFF; otherwise fall back to the (collapsed) callback on a0.
 * NM (reference decode): collapsed-placeholder fallback call (raw-.word game_libs
 * reloc depression). */
extern int gl_func_00000000();
int gl_func_0006C384(unsigned int a0) {
    if (a0 >= 0x80000000U && a0 < 0xA0000000U) {
        return a0 & 0x1FFFFFFF;
    }
    if (a0 >= 0xA0000000U && a0 < 0xC0000000U) {
        return a0 & 0x1FFFFFFF;
    }
    return gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C384);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C400);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C454);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C384_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006C484)();
void gl_func_0006C484(void) {
    u32 sp34;
    u32 sp30;
    u32 sp24;
    u32 sp20;
    u32 temp_ret;
    u32 temp_ret_2;
    u32 temp_t1;
    u32 temp_t9;

    sp30 = 0;
    *(int*)0 = 1;
    ((int(*)())gl_func_00062F64)(((int(*)())gl_func_00062F64)() | 0x20000000);
    ((int(*)())gl_func_00062F64)(0x01000800U);
    if (((int(*)())gl_func_00062F64)(0x1FC007FCU, &sp34) != 0) {
        do {

        } while (((int(*)())gl_func_00062F64)(0x1FC007FCU, &sp34) != 0);
    }
    if (((int(*)())gl_func_00062F64)(0x1FC007FCU, (u32 *) (sp34 | 8)) != 0) {
        do {

        } while (((int(*)())gl_func_00062F64)(0x1FC007FCU, (u32 *) (sp34 | 8)) != 0);
    }
    *(u32 *)0x80000000 = *(int*)0;
    *(u32 *)0x80000004 = *(u32 *)4;
    *(u32 *)0x80000008 = *(u32 *)8;
    *(u32 *)0x8000000C = *(u32 *)0xC;
    (char *)FW(0x80000080, 0x0) = (u32) *(int*)0;
    (char *)FW(0x80000080, 0x4) = (u32) *(char *)4;
    (char *)FW(0x80000080, 0x8) = (u32) *(char *)8;
    (char *)FW(0x80000080, 0xC) = (u32) *(char *)0xC;
    (char *)FW(0x80000100, 0x0) = (u32) *(int*)0;
    (char *)FW(0x80000100, 0x4) = (u32) *(char *)4;
    (char *)FW(0x80000100, 0x8) = (u32) *(char *)8;
    (char *)FW(0x80000100, 0xC) = (u32) *(char *)0xC;
    (char *)FW(0x80000180, 0x0) = (u32) *(int*)0;
    (char *)FW(0x80000180, 0x4) = (u32) *(char *)4;
    (char *)FW(0x80000180, 0x8) = (u32) *(char *)8;
    (char *)FW(0x80000180, 0xC) = (u32) *(char *)0xC;
    ((int(*)())gl_func_00062F64)(0x80000000U, (u32 *)0x190);
    ((int(*)())gl_func_00062F64)(0x80000000U, (u32 *)0x190);
    ((int(*)())gl_func_00062F64)();
    ((int(*)())gl_func_00062F64)(4U, &sp30);
    temp_t9 = sp30 & ~0xF;
    sp30 = temp_t9;
    if (temp_t9 != 0) {
        *(int*)0 = 0U;
        *(char *)4 = temp_t9;
    }
    temp_ret = ((int(*)())gl_func_00062F64)(*(int*)0, (u32 *) *(char *)4, 0, 3);
    sp20 = temp_ret;
    sp24 = (u32) (u64) temp_ret;
    temp_ret_2 = ((int(*)())gl_func_00062F64)(sp20, (u32 *) sp24, 0, 4);
    temp_t1 = *(int*)0;
    *(int*)0 = temp_ret_2;
    *(char *)4 = (u32) (u64) temp_ret_2;
    if (temp_t1 == 0) {
        ((int(*)())gl_func_00062F64)(0U, (u32 *)0x40);
    }
    if (*(int*)0 == 0) {
        *(int*)0 = 0x02F5B2D2U;
        return;
    }
    if (*(int*)0 == 2) {
        *(int*)0 = 0x02E6025CU;
        return;
    }
    *(int*)0 = 0x02E6D354U;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C484);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C710);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C740);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C77C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C7B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C7E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C820);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C87C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C8AC);

#ifdef NON_MATCHING
/* gl_func_0006C90C: too-big-N-function-bundle (declared 0xE4, 57 words) — 4 MIPS3 runtime helpers.
 *
 * This bundle contains FOUR libgcc/runtime support functions emitted by the IDO
 * compiler. All use MIPS3 64-bit instructions (ld/sd/ddiv/dsrav/dsra32) and
 * CP0 access (mtc0/mfc0). Classic "support library" family.
 *
 * SUB-FUNCTION 1 (0x6C90C..0x6C9A8, 38 insns) — __floor_mod64:
 *     int64_t __floor_mod64(int64_t x, int64_t y) {
 *         if (y == 0) trap(7);                          // break 7 = div-by-0
 *         if (x == INT64_MIN && y == -1) trap(6);       // break 6 = overflow
 *         int64_t r = x % y;                            // ddiv → HI
 *         // Adjust for floored division: if signs differ and r != 0, add y
 *         if (!(r > 0)
 *             && !(y > 0 && r >= 0)
 *             && !(y >= 0 && r >= 0))
 *             r += y;
 *         return r;
 *     }
 *   Standard "signed 64-bit floored modulo" — adjusts truncating-toward-zero
 *   ddiv result to floor-toward-negative semantics by adding divisor when the
 *   signs of remainder and divisor differ.
 *   Returns 64-bit value in v0:v1 (lw $v0, 0($sp); lw $v1, 4($sp) — o32 ABI
 *   high-low split of saved 64-bit stack slot).
 *
 * SUB-FUNCTION 2 (0x6C9A8..0x6C9D4, 12 insns) — __ashr64:
 *     int64_t __ashr64(int64_t x, int64_t shift) {
 *         return x >> shift;          // dsrav: arithmetic shift, sa from low-6-bits of shift
 *     }
 *   Tail epilogue: dsra32 $v0, $v0, 0 in delay slot = no-op extra normalization
 *   (or part of sign-ext into the return register pair).
 *
 * SUB-FUNCTION 3 (0x6C9D4..0x6C9E4, 4 insns) — __set_cp0_status:
 *     void __set_cp0_status(uint32_t status) {
 *         asm("mtc0 $a0, $12");      // CP0 reg 12 = Status
 *         asm("nop");                 // CP0 hazard delay
 *     }
 *
 * SUB-FUNCTION 4 (0x6C9E4..0x6C9F0, 3 insns) — __get_cp0_status:
 *     uint32_t __get_cp0_status(void) {
 *         asm("mfc0 $v0, $12");      // returns Status register
 *         return v0;
 *     }
 *
 * Notes:
 *  - All four functions use MIPS3 instructions (ld/sd/ddiv/dsrav/dsll32/dsra32/
 *    mtc0/mfc0) that IDO C does not emit from standard C — they require inline
 *    asm OR are part of the libgcc/libult runtime emitted by the compiler.
 *  - 4 internal `jr $ra` confirm the bundle structure.
 *  - The MIPS3 64-bit family + CP0 access is hallmark of `__mips3_runtime`
 *    helpers — see libreultra `src/libgcc/` or libgcc-equivalent.
 *  - Splat boundary issue: candidate for split-fragments.py.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C90C);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C9A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C9D4);

/* game_libs_func_0006C9E4: 3-insn `mfc0 v0, $12; jr ra; nop` Status-register
 * read. CP0 access (mfc0) is MIPS3 runtime — IDO C can't emit CP0 ops from
 * standard C. CAP class per reference_1080_mips3_runtime_helpers. Default
 * INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006C9E4);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006C90C_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006C9F4: 56-insn game_libs USO equivalent of __osPiRawStartDma
 * (kernel func_80004650). Same structure: wait on PI status & 3, set up
 * DMA registers, dispatch by direction (0=read, 1=write, else=-1).
 *
 * USO version uses unresolved relocs for all PI hardware register
 * addresses (D_A460xxxx) and the kernel helper func_80004B30 (= virtual
 * to physical address translation). Initial structural wrap; D_/jal
 * alias-externs deferred to multi-pass. */
extern int gl_func_0001CA10();  /* placeholder for func_80004B30 equiv */
extern int gl_data_6C9F4_devCfg;
extern volatile int gl_pi_status;
extern volatile int gl_pi_dramAddr;
extern volatile int gl_pi_devAddr;
extern volatile int gl_pi_rdLen;
extern volatile int gl_pi_wrLen;
int gl_func_0006C9F4(int direction, unsigned int devAddr, int dramAddr, unsigned int size) {
    register unsigned int status;
    status = gl_pi_status;
    while (status & 3) status = gl_pi_status;
    gl_pi_dramAddr = gl_func_0001CA10(dramAddr);
    gl_pi_devAddr = (gl_data_6C9F4_devCfg | devAddr) & 0x1FFFFFFF;
    switch (direction) {
        case 0: gl_pi_rdLen = size - 1; break;
        case 1: gl_pi_wrLen = size - 1; break;
        default: return -1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C9F4);
#endif

#ifdef NON_MATCHING
/* gl_func_0006CAD4: 43-insn PIF DMA wrapper (Serial Interface I/O) (0xAC, frame 0x18).
 *
 * RECOGNIZED HARDWARE PATTERN: writes to 0xA4800000 (SI_DRAM_ADDR_REG) and
 * 0xA4800004 (SI_PIF_ADDR_RD64B_REG) / 0xA4800010 (SI_PIF_ADDR_WR64B_REG)
 * with the value 0x1FC007C0 = PIF RAM start (K1-mapped). This is an
 * N64 PIF controller-block 64-byte DMA wrapper.
 *
 * Decoded structure (raw-word disasm):
 *   if (factory(dir, buf) != 0) return -1;            // factory init / validate
 *   dma_buf = (dir == 1) ? func_prep_wr(buf, 0x40)
 *                        : func_prep_rd(buf);          // 0x40 = 64-byte PIF block
 *   *(volatile int*)0xA4800000 = dma_buf;              // SI_DRAM_ADDR
 *   if (dir == 0) {
 *       *(volatile int*)0xA4800004 = 0x1FC007C0;       // SI_PIF_ADDR_RD64B (trigger PIF→DRAM)
 *   } else {
 *       *(volatile int*)0xA4800010 = 0x1FC007C0;       // SI_PIF_ADDR_WR64B (trigger DRAM→PIF)
 *   }
 *   if (dir == 0) {
 *       func_post_rd(buf, 0x40);                       // post-read processing
 *   }
 *   return 0;
 *
 * Register addresses match libultra `osSiRawReadIo`/`osSiRawWriteIo`-style
 * direct hardware access for controller pak / EEPROM communication.
 * 0x1FC007C0 = PIF RAM start.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_0006CAD4(int dir, int buf) {
    int dma_buf;
    if (gl_func_00000000(dir, buf) != 0) return -1;
    if (dir == 1) {
        dma_buf = (int)gl_func_00000000(buf, 0x40);
    } else {
        dma_buf = (int)gl_func_00000000(buf);
    }
    *(volatile int*)0xA4800000 = dma_buf;
    if (dir == 0) {
        *(volatile int*)0xA4800004 = 0x1FC007C0;
    } else {
        *(volatile int*)0xA4800010 = 0x1FC007C0;
    }
    if (dir == 0) {
        gl_func_00000000(buf, 0x40);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CAD4);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CAD4_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006CB84: 35-insn RSP DMA setup helper.
 *   r = gl_func_00000000(direction, mem_addr, dram_ptr, len);  // probably bounds-check
 *   if (r != 0) return -1;
 *   *(int*)0xA4040000 = mem_addr;                           // SP_MEM_ADDR_REG
 *   *(int*)0xA4040004 = gl_func_00000000(dram_ptr);          // SP_DRAM_ADDR_REG = osVirtualToPhysical(dram_ptr)
 *   if (direction != 0)
 *     *(int*)0xA4040008 = len - 1;                           // SP_RD_LEN_REG (DMA read)
 *   else
 *     *(int*)0xA404000C = len - 1;                           // SP_WR_LEN_REG (DMA write)
 *   return 0;
 * Hardware regs at 0xA4040000+: SP MEM/DRAM/RD_LEN/WR_LEN. */
int gl_func_0006CB84(int direction, int mem_addr, int dram_ptr, int len) {
    int r = gl_func_00000000(direction, mem_addr, dram_ptr, len);
    if (r != 0) return -1;
    *(volatile int*)0xA4040000 = mem_addr;
    *(volatile int*)0xA4040004 = gl_func_00000000(dram_ptr);
    if (direction == 0) {
        *(volatile int*)0xA404000C = len - 1;
    } else {
        *(volatile int*)0xA4040008 = len - 1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CB84);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CB84_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006CC14: 19-insn 2-call helper.
 *   r = gl_func(a0);       (first call)
 *   *a0 = D[0];            (copy global into *a0)
 *   gl_func(r);            (second call)
 *   D2 = a0;               (store original a0 to second global)
 *   return 0;
 *
 * Use 'volatile int spill = (int)r;' to force the v0→stack→a0
 * round-trip that target uses (r is spilled to sp+0x18 then reloaded
 * as a0 of the second jal — without volatile, IDO uses 'or a0, v0, 0'
 * direct passthrough).
 *
 * Caps remaining at the byte level:
 * 1. Stack offset: target stores v0 at sp+0x1C; built at sp+0x18
 *    (4-byte difference — built doesn't allocate a 4-byte pad slot).
 * 2. Schedule: target splits 'lui at; sw t8, 0(at)' across the jal
 *    (lui at scheduled BEFORE the *a0 store, sw t8 scheduled AFTER
 *    the second jal's epilogue). Built keeps them adjacent. IDO's
 *    natural scheduling doesn't split symbol stores across calls. */
extern int D_cc14_alias2;
int gl_func_0006CC14(int *a0) {
    int *r = (int*)gl_func_00000000(a0);
    volatile int spill = (int)r;
    *a0 = *(int*)&D_00000000;
    gl_func_00000000((int*)spill);
    *(int**)&D_cc14_alias2 = a0;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CC14);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CC14_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006CC64: rv = func(a0); p = *(u16**)&D; if ((u8)a0) *p |= 0x20;
 * else *p &= ~0x20; func(rv). The &param lever (unsigned char *pa = &a0) forces
 * the a0 stack-home + post-call lbu reload that the prior 60.7% attempt missed ->
 * 74.5%. Residual (register-alloc, not C-forceable): target keeps rv in s0
 * (callee-save) w/ frame -0x28 and homes a0 BEFORE the call; -O2 here keeps rv in
 * a0 (rv never crosses a call so `register` is ignored) w/ frame -0x18 and homes
 * a0 in the jal delay slot. */
extern int gl_func_00000000();
void gl_func_0006CC64(unsigned char a0) {
    unsigned char *pa = &a0;
    int rv = gl_func_00000000();
    if (*pa != 0) {
        *(unsigned short *)(*(int *)&D_00000000) |= 0x20;
    } else {
        *(unsigned short *)(*(int *)&D_00000000) &= ~0x20;
    }
    gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CC64);
#endif

/* gl_func_0006CCD4: 20-insn DMA-sync + uncached-read helper. Calls
 * gl_func(src, dst); on success (returns 0), reads *src from the
 * KSEG1-uncached mirror (a0 | 0xA0000000) and writes to *dst. Returns
 * 0 on success, -1 on failure. NATURAL CEILING: pure delay-slot-fill
 * cap — IDO fills the beqz delay slot with the success-path's first lw
 * (delay-slot-fill-by-reorg.c); target leaves it as nop.
 * 2026-05-27 retests (both regressed):
 *   (a) `goto fail; ... fail: return -1;` form — moves -1 return
 *       out-of-line. Regressed 80.65% → 25% (goto-out moves fail block
 *       after success, swapping layout).
 *   (b) `register int rc = ...` hint — IDO ignored at -O2 and shifted
 *       the rc allocation. Regressed 80.65% → 35%.
 * Natural if/return-here form is the closest reachable.
 * Was previously documented (fresh decode 2026-05-14) as byte-exact via
 * 12-entry INSN_PATCH + 1-word SUFFIX_BYTES_FORCE — both REMOVED
 * 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
#ifdef NON_MATCHING
int gl_func_0006CCD4(int *src, int *dst) {
    int rc = gl_func_00000000(src, dst);
    if (rc != 0) {
        return -1;
    }
    *dst = *(volatile int*)((unsigned int)src | 0xA0000000);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CCD4);
#endif

extern int gl_func_00000000();
int gl_func_0006CD24() {
    return gl_func_00000000(0x400);
}

#ifdef NON_MATCHING
/* gl_func_0006CD44: 26-insn factory + 3 global-data stores + chain (0x68, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   result = gl_func(self);                          // 1st call (arg untouched)
 *   D_A[2] = self;                                   // store self into global table
 *   *D_B = 1;                                        // set flag (short)
 *   D_C[3] = ((int**)D_C)[2][1];                     // chain: D_C[3] = (D_C[2] as int*)[1]
 *   gl_func(result);                                 // 2nd call w/ 1st-call result
 *
 * The 3 global-data accesses (D_A/D_B/D_C) interleave with the s0 spill and
 * arg-reload — IDO -O2 fills the post-1st-call delay slot with the early s0
 * spill (afb00018) and amortizes lui+lw setup across the body. No FP.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
extern int *D_A;
extern short *D_B;
extern int *D_C;
void gl_func_0006CD44(int *self) {
    int *result = (int*)gl_func_00000000(self);
    D_A[2] = (int)self;
    *D_B = 1;
    D_C[3] = ((int**)D_C)[2][1];
    gl_func_00000000(result);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CD44);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006CD44_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CDB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CF54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D0F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D270);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006D270_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D554);

#ifdef NON_MATCHING
/* gl_func_0006D6F4: 54-insn record-stream emit helper (declared size 0xD8, frame 0x10).
 *
 * Decoded structure (raw-word disasm):
 *   void emit_records(int count_byte [a0, masked to u8]) {
 *       int orig_count = *(uint8_t*)&D_00000000;     // gate value (entry-skip)
 *       count_byte &= 0xFF;
 *       *(uint8_t*)&D_00000000 = count_byte;          // overwrite global counter
 *       *(int    *)((char*)&D_00000000 + 0x3C) = 1;   // flag = 1 (active)
 *
 *       // Build 8-byte template on stack at sp+0x4..sp+0xB
 *       uint8_t buf[8] = {
 *           0xFF, 0x01, 0x03, count_byte,
 *           0xFF, 0xFF, 0xFF, 0xFF
 *       };
 *
 *       // Skip if no prior records existed
 *       if (orig_count <= 0) goto write_sentinel;
 *
 *       int idx = 0;
 *       char *dst = (char*)D_global_ptr;  // saved at sp+0xC
 *       while (1) {
 *           // Unaligned 8-byte template store at *dst (swl/swr pair × 2)
 *           *(uint32_t*)(dst+0) = *(uint32_t*)(buf+0);
 *           *(uint32_t*)(dst+4) = *(uint32_t*)(buf+4);
 *           uint8_t bound = *(uint8_t*)&D_00000000;   // reloaded EVERY iter
 *           idx++;
 *           dst += 8;
 *           if (idx >= bound) break;
 *       }
 *   write_sentinel:
 *       *(uint8_t*)dst = 0xFE;                          // list-terminator byte
 *   }
 *
 * Notes:
 *  - Two D+0 byte loads (one before overwrite to capture original gate, one
 *    inside the loop as bound): the loop bound IS the NEWLY-written value
 *    while the entry gate is the OLD value. Could be deliberate (caller
 *    expects emit-when-empty semantics) or a subtle bug captured by IDO.
 *  - Template bytes `0xFF, 0x01, 0x03` suggest a packet/command record format
 *    where 0x01 = type, 0x03 = subtype, 0xFF = padding/flags.
 *  - 0xFE final-byte = list terminator (matches the "all-bytes-FF" record-not-
 *    terminator semantics).
 *  - Unaligned 8-byte writes via paired swl/swr indicate dst may not be 4-byte
 *    aligned — typical of packed binary stream emission.
 *  - Trailing 2-insn fragment (`lui $t7,0; lbu $t7,0($t7)`) post-jr+delay is
 *    incomplete — likely start of a next helper that reads D+0. Variant of
 *    feedback_splat_too_big_incomplete_fragment_tail.md.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D6F4);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006D7C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D7CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006D894);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006D94C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006D7CC_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006D964: 67-insn command-record builder + dual-dispatch helper.
 * Size 0x10C, frame 0x28, saves s0/s1.
 *
 * Builds a 20-byte command record at *a0 then dispatches via one of two
 * jal pairs based on the kind flag `a1`. Returns -1 if the global head
 * pointer at D+0 is NULL.
 *
 * Decoded structure (raw-word disasm):
 *   int build_and_send(uint8_t *out_record,  // a0 — record buffer (≥0x14 bytes)
 *                      int kind_flag,         // a1 (1 = path A, else path B)
 *                      int type_alt,          // a2 (0 = type 0xB, else 0xC)
 *                      int arg3,              // a3
 *                      int arg5,              // sp+0x38
 *                      int arg6,              // sp+0x3C
 *                      int arg4)              // sp+0x40 — order via stack-arg slots
 *   {
 *       void *head = *(void**)&D_00000000;
 *       if (head == NULL) return -1;
 *
 *       // Build 0x14-byte command record:
 *       *(uint16_t*)(out_record + 0x00) = (type_alt == 0) ? 0xB : 0xC;
 *       *(uint8_t *)(out_record + 0x02) = (uint8_t)kind_flag;
 *       *(uint32_t*)(out_record + 0x04) = arg4;       // sp+0x40
 *       *(uint32_t*)(out_record + 0x08) = arg5;       // sp+0x38
 *       *(uint32_t*)(out_record + 0x0C) = arg3;       // a3
 *       *(uint32_t*)(out_record + 0x10) = arg6;       // sp+0x3C
 *       *(uint32_t*)(out_record + 0x14) = 0;
 *
 *       // Dispatch
 *       int s1;
 *       if (kind_flag == 1) {
 *           s1 = func_a();           // jal #1
 *       } else {
 *           s1 = func_b();           // jal #1' (different target)
 *       }
 *       return func_send(s1, out_record, 0);   // jal #2 — common dispatch
 *   }
 *
 * Notes:
 *  - The two jal-pair branches share identical structure (`jal X; s1 = v0;
 *    jal send(s1, out_record, 0)`). Only the first jal target differs.
 *    IDO appears to have emitted them as separate code paths rather than
 *    a conditional callee lookup — probably the original C had two
 *    explicit if-branches, each with its own builder function call.
 *  - Type byte 0xB or 0xC suggests a command-ID enum where 0xB = some
 *    "write" command and 0xC = a related command variant.
 *  - 20-byte record matches typical OS-level message-queue entry size
 *    (osCreateMesgQueue size and friends).
 *  - Returns -1 on NULL head (early-out), else result of send-jal.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D964);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006D964_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006DA74)();
void gl_func_0006DA74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 temp_v0;

    if (*(int*)0 == 0) {
        ((int(*)())gl_func_00062F64)(arg1, arg2, arg3);
        ((int(*)())gl_func_00062F64)(0x43E90, 0x43EA8, 1);
        if (*(int*)0 == 0) {
            ((int(*)())gl_func_00062F64)();
        }
        ((int(*)())gl_func_00062F64)(8, 0x43E90, 0x22222222);
        sp28 = -1;
        sp24 = ((int(*)())gl_func_00062F64)(0);
        if (sp24 < arg0) {
            sp28 = sp24;
            ((int(*)())gl_func_00062F64)(0, arg0);
        }
        temp_v0 = ((int(*)())gl_func_00062F64)();
        *(int*)0 = 1;
        *(s32 *)4 = 0x42CE0;
        *(s32 *)0xC = 0x43E90;
        *(s32 *)8 = arg1;
        sp2C = temp_v0;
        *(s32 *)0x10 = 0;
        *(s32 *)0x14 = 0;
        *(s32 *)0x18 = 0;
        ((int(*)())gl_func_00062F64)(0x42CE0, 0, 0, 0, 0x43E90, arg0);
        ((int(*)())gl_func_00062F64)(0x42CE0);
        ((int(*)())gl_func_00062F64)(sp2C);
        if (sp28 != -1) {
            ((int(*)())gl_func_00062F64)(0, sp28);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DA74);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006DBFC);

#ifdef NON_MATCHING
/* gl_func_0006DC0C: 59-insn save-data / SRAM init helper (size 0xEC, frame 0x20).
 *
 * Sets up the hardware-mapped 0xB000_0000 region (N64 PI bus DOM2 = cartridge
 * SRAM / EEPROM / save-data mapping) and unpacks a status word from a
 * hardware/save-header call into byte fields in the D segment.
 *
 * Decoded structure (raw-word disasm):
 *   void *save_init(void) {
 *       if ($t6 == 0xB000_0000) {           // caller-set $t6 = current SRAM ptr
 *           *(int*)(sp+0x1C) = 0;
 *           return (void*)&D_00000000 + 0;  // already initialized, return cached
 *       }
 *
 *       // First-time init path:
 *       *(uint8_t*)(D+0x4)  = 0;            // status flag
 *       *(int    *)(D+0xC)  = 0xB000_0000;  // mapped SRAM base ptr (this is the
 *                                            //   "now initialized" sentinel that
 *                                            //   the caller-set $t6 will check)
 *
 *       uint32_t hdr = 0;
 *       hardware_query(0, &hdr);            // jal <func>(0, sp+0x1C)
 *
 *       // Unpack packed status word: layout looks like a date/version stamp
 *       *(uint8_t*)(D+0x5) = (hdr >>  0) & 0xFF;   // byte 0
 *       *(uint8_t*)(D+0x8) = (hdr >>  8) & 0xFF;   // byte 1
 *       *(uint8_t*)(D+0x6) = (hdr >> 16) & 0x0F;   // nibble 4
 *       *(uint8_t*)(D+0x7) = (hdr >> 20) & 0x0F;   // nibble 5
 *       *(uint8_t*)(D+0x9) = 0;
 *       *(int    *)(D+0x10) = 0;
 *
 *       init_struct((char*)D + 0x14, 0x60);       // 0x60-byte init at D+0x14
 *       int saved = alloc_or_create();             // jal <func> (no args set)
 *
 *       // Final cleanup: copy D+0 → D+0 and chain finalize-hook
 *       *(int*)(D+0) = *(int*)(D+0);              // self-copy (likely IDO peephole leftover)
 *       *(int*)(D+0) = (char*)&D_00000000 + 0;     // restore default pointer
 *       finalize_hook(saved);                       // jal <func>(saved_v0)
 *
 *       return (void*)&D_00000000 + 0;
 *   }
 *
 * Notes:
 *  - 0xB000_0000 is the N64 PI bus DOM2 (cart/SRAM) virtual address. Writes
 *    to *(D+0xC) here are storing the mapped pointer as a global for future
 *    code to access SRAM via *D+0xC dereference.
 *  - $t6 caller-set: the function expects caller to pass current value of
 *    `*(D+0xC)` in $t6 (the saved pointer). Fits caller-set-int-reg cap class
 *    (feedback_caller_set_int_reg_cap_1080_game_libs.md).
 *  - The unpacked byte fields look like a date+time stamp (or version
 *    YYYY-MM-DD HH:MM packed into 32 bits) parsed from save-header.
 *  - The "self-copy" `*(D+0) = *(D+0)` at insns 43-47 is IDO peephole leftover
 *    where a temporary went through register allocation but the load and store
 *    pair didn't get eliminated.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DC0C);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006DC0C_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DD14);

#ifdef NON_MATCHING
/* gl_func_0006E1A4: 30-insn table-write + call-and-call dispatcher.
 *   ret = gl_func_00000000(idx, a, b);                   // first call
 *   entry = &gl_data[idx * 2];                            // 8-byte entries
 *   entry[0] = a;
 *   entry[1] = b;
 *   gl_func_00000000(ret);                                // second call (1 arg)
 * Table base is a USO data symbol; idx is multiplied by 8 via sll for
 * pointer arithmetic.
 *
 * Cap: 62% — target spills `entry` to stack slot sp+0x20 and uses $s0
 * to hold the call return. Mine keeps both in temp regs. The store-and-
 * reload roundtrip of entry through stack is hard to reproduce from C
 * without ugly volatile tricks. Multi-tick polish. */
void gl_func_0006E1A4(int idx, int a, int b) {
    int* entry = (int*)((char*)&gl_data_00000000 + idx * 8);
    int ret = gl_func_00000000(idx, a, b);
    entry[0] = a;
    entry[1] = b;
    gl_func_00000000(ret);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E1A4);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006E20C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006E1A4_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E224);

#ifdef NON_MATCHING
/* gl_func_0006E894 - STRUCTURAL PASS (big-swing 2026-06-02).
 * printf/doprnt-style formatted-string emitter (0x648, 402 insns).
 * arg0 is the output callback (s32 (*)(s32,u8*,s32,u8*)); scans the
 * format string, flushes literal runs via arg0, and on '%' (0x25)
 * parses flags/width/precision/'*'/conversion using a spec-table
 * lookup (gl_func_0001CA10) + number formatting into the sp74 buffer.
 * Helpers gl_func_0001CA10 / gl_func_0007526C. Mechanically lifted
 * from m2c (X->unkN -> FW word access). The sp74..spB8 number buffer
 * is modeled as scalars (m2c didn't reconstruct the aliasing). NOT
 * matched; default INCLUDE_ASM path byte-exact. */
#define FW(p, o) (*(int *)((char *)(p) + (o)))
extern int gl_func_0001CA10();
extern int gl_func_0007526C();

s32 gl_func_0006E894(s32 (*arg0)(), s32 arg1, u8 *arg2, s32 arg3) {
    u8 spD4;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 spC4;
    int spA0;
    u8 sp74;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7_2;
    s32 temp_t8;
    int *temp_t8_2;
    s32 temp_t8_3;
    int *temp_t9;
    s32 temp_t9_3;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    s32 var_s0_6;
    s32 var_s0_7;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s1_4;
    s32 var_s1_5;
    s32 var_s3;
    u8 spA8[0x40];
    int spAC;
    int spB0;
    int spB4;
    int spB8;
    int spBC;
    int spC0;
    u8 *var_a3;
    u8 *var_s2;
    u8 *var_s2_2;
    u8 temp_t7;
    u8 temp_t9_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 var_a1;
    u8 var_a1_2;
    u8 var_s0;

    var_a3 = arg2;
    var_s3 = arg1;
    spCC = 0;
loop_1:
    temp_v0 = *var_a3;
    var_s2 = var_a3;
    var_s0 = temp_v0;
    if ((temp_v0 != 0) && (temp_v0 != 0x25)) {
loop_3:
        temp_v0_2 = FW(var_s2, 0x1);
        var_s2 += 1;
        var_s0 = temp_v0_2;
        if (temp_v0_2 != 0) {
            if (temp_v0_2 != 0x25) {
                goto loop_3;
            }
        }
    }
    temp_v0_3 = var_s2 - var_a3;
    if (temp_v0_3 > 0) {
        temp_v0_4 = arg0(var_s3, var_a3, temp_v0_3, var_a3);
        var_s3 = temp_v0_4;
        if (temp_v0_4 != 0) {
            spCC += temp_v0_3;
            goto block_9;
        }
        return spCC;
    }
block_9:
    var_s2_2 = var_s2 + 1;
    if (var_s0 == 0) {
        return spCC;
    }
    spD0 = 0;
    temp_v0_5 = gl_func_0001CA10(0x23D4, FW(var_s2, 0x1));
    var_s0_2 = temp_v0_5;
    if (temp_v0_5 != 0) {
        do {
            var_s2_2 += 1;
            spD0 |= FW(((var_s0_2 - 0x23D4) * 4), 0x23DC);
            temp_v0_6 = gl_func_0001CA10(0x23D4, *var_s2_2);
            var_s0_2 = temp_v0_6;
        } while (temp_v0_6 != 0);
    }
    if (*var_s2_2 == 0x2A) {
        temp_t9 = (arg3 + 3) & ~3;
        arg3 = temp_t9 + 4;
        temp_t8 = *temp_t9;
        var_s2_2 += 1;
        spC8 = temp_t8;
        if (temp_t8 < 0) {
            spC8 = -temp_t8;
            spD0 |= 4;
        }
        var_a1 = *var_s2_2;
    } else {
        spC8 = 0;
        var_a1 = *var_s2_2;
        if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
loop_19:
            if (spC8 < 0x3E7) {
                spC8 = (var_a1 + (spC8 * 0xA)) - 0x30;
            }
            var_a1 = FW(var_s2_2, 0x1);
            var_s2_2 += 1;
            if (((s32) var_a1 >= 0x30) && ((s32) var_a1 < 0x3A)) {
                goto loop_19;
            }
        }
    }
    if (var_a1 != 0x2E) {
        spC4 = -1;
        var_a1_2 = FW(var_s2_2, 0x0);
    } else {
        temp_t7 = FW(var_s2_2, 0x1);
        var_s2_2 += 1;
        if (temp_t7 == 0x2A) {
            temp_t8_2 = (arg3 + 3) & ~3;
            arg3 = temp_t8_2 + 4;
            var_s2_2 += 1;
            spC4 = *temp_t8_2;
            var_a1_2 = *var_s2_2;
        } else {
            spC4 = 0;
            var_a1_2 = *var_s2_2;
            if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
loop_29:
                if (spC4 < 0x3E7) {
                    spC4 = (var_a1_2 + (spC4 * 0xA)) - 0x30;
                }
                var_a1_2 = FW(var_s2_2, 0x1);
                var_s2_2 += 1;
                if (((s32) var_a1_2 >= 0x30) && ((s32) var_a1_2 < 0x3A)) {
                    goto loop_29;
                }
            }
        }
    }
    if (gl_func_0001CA10(0x23D0, var_a1_2) != 0) {
        temp_t9_2 = *var_s2_2;
        var_s2_2 += 1;
        spD4 = temp_t9_2;
    } else {
        spD4 = 0;
    }
    if ((spD4 == 0x6C) && (*var_s2_2 == 0x6C)) {
        spD4 = 0x4C;
        var_s2_2 += 1;
    }
    gl_func_0007526C();
    temp_t9_3 = (((((spC8 - spAC) - spB0) - spB4) - spB8) - spBC) - spC0;
    spC8 = temp_t9_3;
    temp_t6 = temp_t9_3 > 0;
    if (!(spD0 & 4) && (temp_t6 != 0)) {
        var_s1 = temp_t9_3;
        if (temp_t6 != 0) {
loop_42:
            var_s0_3 = var_s1;
            if ((u32) var_s1 >= 0x21U) {
                var_s0_3 = 0x20;
            }
            if (var_s0_3 > 0) {
                temp_v0_7 = arg0(var_s3, (u8 *)0x2E460, var_s0_3);
                var_s3 = temp_v0_7;
                if (temp_v0_7 != 0) {
                    spCC += var_s0_3;
                    goto block_48;
                }
                return spCC;
            }
block_48:
            var_s1 -= var_s0_3;
            if (var_s1 <= 0) {
                goto block_49;
            }
            goto loop_42;
        }
    }
block_49:
    if (spAC > 0) {
        temp_v0_8 = arg0(var_s3, &sp74, spAC);
        var_s3 = temp_v0_8;
        if (temp_v0_8 != 0) {
            spCC += spAC;
            goto block_53;
        }
        return spCC;
    }
block_53:
    temp_t6_2 = spB0 > 0;
    if (temp_t6_2 != 0) {
        var_s1_2 = spB0;
        if (temp_t6_2 != 0) {
loop_55:
            var_s0_4 = var_s1_2;
            if ((u32) var_s1_2 >= 0x21U) {
                var_s0_4 = 0x20;
            }
            if (var_s0_4 > 0) {
                temp_v0_9 = arg0(var_s3, (u8 *)0x2E484, var_s0_4);
                var_s3 = temp_v0_9;
                if (temp_v0_9 != 0) {
                    spCC += var_s0_4;
                    goto block_61;
                }
                return spCC;
            }
block_61:
            var_s1_2 -= var_s0_4;
            if (var_s1_2 <= 0) {
                goto block_62;
            }
            goto loop_55;
        }
    }
block_62:
    if (spB4 > 0) {
        temp_v0_10 = arg0(var_s3, spA8, spB4);
        var_s3 = temp_v0_10;
        if (temp_v0_10 != 0) {
            spCC += spB4;
            goto block_66;
        }
        return spCC;
    }
block_66:
    temp_t6_3 = spB8 > 0;
    if (temp_t6_3 != 0) {
        var_s1_3 = spB8;
        if (temp_t6_3 != 0) {
loop_68:
            var_s0_5 = var_s1_3;
            if ((u32) var_s1_3 >= 0x21U) {
                var_s0_5 = 0x20;
            }
            if (var_s0_5 > 0) {
                temp_v0_11 = arg0(var_s3, (u8 *)0x2E484, var_s0_5);
                var_s3 = temp_v0_11;
                if (temp_v0_11 != 0) {
                    spCC += var_s0_5;
                    goto block_74;
                }
                return spCC;
            }
block_74:
            var_s1_3 -= var_s0_5;
            if (var_s1_3 <= 0) {
                goto block_75;
            }
            goto loop_68;
        }
    }
block_75:
    if (spBC > 0) {
        temp_v0_12 = arg0(var_s3, &spA8[spB4], spBC);
        var_s3 = temp_v0_12;
        if (temp_v0_12 != 0) {
            spCC += spBC;
            goto block_79;
        }
        return spCC;
    }
block_79:
    temp_t8_3 = spC0 > 0;
    if (temp_t8_3 != 0) {
        var_s1_4 = spC0;
        if (temp_t8_3 != 0) {
loop_81:
            var_s0_6 = var_s1_4;
            if ((u32) var_s1_4 >= 0x21U) {
                var_s0_6 = 0x20;
            }
            if (var_s0_6 > 0) {
                temp_v0_13 = arg0(var_s3, (u8 *)0x2E484, var_s0_6);
                var_s3 = temp_v0_13;
                if (temp_v0_13 != 0) {
                    spCC += var_s0_6;
                    goto block_87;
                }
                return spCC;
            }
block_87:
            var_s1_4 -= var_s0_6;
            if (var_s1_4 <= 0) {
                goto block_88;
            }
            goto loop_81;
        }
    }
block_88:
    temp_t7_2 = spC8 > 0;
    if ((spD0 & 4) && (temp_t7_2 != 0)) {
        var_s1_5 = spC8;
        if (temp_t7_2 != 0) {
loop_91:
            var_s0_7 = var_s1_5;
            if ((u32) var_s1_5 >= 0x21U) {
                var_s0_7 = 0x20;
            }
            if (var_s0_7 > 0) {
                temp_v0_14 = arg0(var_s3, (u8 *)0x2E460, var_s0_7);
                var_s3 = temp_v0_14;
                if (temp_v0_14 != 0) {
                    spCC += var_s0_7;
                    goto block_97;
                }
                return spCC;
            }
block_97:
            var_s1_5 -= var_s0_7;
            if (var_s1_5 <= 0) {
                goto block_98;
            }
            goto loop_91;
        }
    }
block_98:
    var_a3 = var_s2_2 + 1;
    goto loop_1;
}
#undef FW
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E894);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006E894_pad.s")

extern int gl_func_00000000();
int gl_func_0006EEE4(int a0, int a1, int a2) {
    return gl_func_00000000(a0, a1) + a2;
}

/* gl_func_0006EF08: 22-insn string-format-style wrapper.
 *   rv = func("string@0x83550", a0, a1, &a2);
 *   if (rv >= 0) a0[rv] = 0;
 *   return rv;
 *
 * NATURAL CEILING: 89.77% NM. The 13-insn diff is a frame-size shift
 * (build emits 0x18 frame; target uses 0x20). C-only `char pad[8]` and
 * `volatile int pad[2]` are both elided by IDO -O2, so the natural emit
 * cannot grow the frame. Was previously documented as INSN_PATCH-promoted
 * to EXACT; INSN_PATCH REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
extern int func_00000000();
extern int D_00000000;
#ifdef NON_MATCHING
int gl_func_0006EF08(char *a0, int a1, int a2, int a3) {
    int rv = func_00000000((char*)&D_00000000 + 0x83550, a0, a1, &a2);
    if (rv >= 0) {
        a0[rv] = 0;
    }
    (void)a3;
    return rv;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006EF08);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006EF08_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006EF64: ~52-insn dispatch helper.
 *   if (g_state == 0) return -1;
 *   a1->word_14 = a0;
 *   a1->short_0  = (a2 == 0) ? 0xF : 0x10;
 *   if (a1->byte_2 == 1) { r = FUNC_A(); return FUNC_B(r, a1, 0); }
 *   else                 { r = FUNC_C(); return FUNC_D(r, a1, 0); }
 *
 * Args saved to caller slots (sp+0x28/2C/30) at prologue, reloaded
 * before each use. Build path stays INCLUDE_ASM; this NM wrap
 * documents the structure for future struct-typing. Sibling decode
 * after gl_func_0006EF08 (string-format wrapper). */
extern int D_6EF64_g;
extern int FUNC_6EF64_a(void);
extern int FUNC_6EF64_b(int, void*, int);
extern int FUNC_6EF64_c(void);
extern int FUNC_6EF64_d(int, void*, int);
int gl_func_0006EF64(int a0, void *a1, int a2) {
    int s1, s0;
    if (D_6EF64_g == 0) return -1;
    *(int*)((char*)a1 + 0x14) = a0;
    if (a2 == 0) {
        *(short*)a1 = 0xF;
    } else {
        *(short*)a1 = 0x10;
    }
    if (*(unsigned char*)((char*)a1 + 2) == 1) {
        s1 = FUNC_6EF64_a();
        s0 = FUNC_6EF64_b(s1, a1, 0);
    } else {
        s1 = FUNC_6EF64_c();
        s0 = FUNC_6EF64_d(s1, a1, 0);
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006EF64);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F038);

#ifdef NON_MATCHING
/* gl_func_0006F088: 47-insn N64 PI DOM2 setup + buffer-init dispatch (0xBC, frame 0x20).
 *
 * RECOGNIZED HARDWARE PATTERN: writes to PI (Peripheral Interface) BSD
 * timing registers for domain 2 (cart/disk):
 *   0xA4600024 = PI_BSD_DOM2_LAT_REG (latency, set to 3)
 *   0xA4600028 = PI_BSD_DOM2_PWD_REG (pulse width, from D_sym byte +8)
 *   0xA460002C = PI_BSD_DOM2_PGS_REG (page size, from D_sym byte +6)
 *   0xA4600030 = PI_BSD_DOM2_RLS_REG (release, from D_sym byte +7)
 *
 * Decoded structure (raw-word disasm):
 *   D_sym_a[9] = 1;                                  // flag set
 *   *(volatile int*)0xA4600024 = 3;                  // PI_BSD_DOM2_LAT
 *   *(volatile int*)0xA4600028 = D_sym_a[8];         // PI_BSD_DOM2_PWD
 *   *(volatile int*)0xA460002C = D_sym_b[6];         // PI_BSD_DOM2_PGS
 *   *(volatile int*)0xA4600030 = D_sym_c[7];         // PI_BSD_DOM2_RLS
 *   D_zero_sym = 0;
 *   func1(&D_arg_sym + 0x14, 0x60);                   // 0x60-byte buffer init
 *   func2();                                          // post-init
 *   D_other_syms = ... ;                              // additional sym writes
 *   return *(int*)&D_result;
 *
 * Cart/64DD domain-2 timing setup. Boot-time hardware init. Pairs with
 * the SI/PIF DMA helper in gl_func_0006CAD4 — both are libultra-style
 * hardware register configuration.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_0006F088(void) {
    /* distinct externs to bust IDO's &D base CSE — target re-materializes the
     * lui per buffer-byte access (separate lui;lbu each). */
    extern unsigned char D_6F088_b9, D_6F088_b8, D_6F088_b6, D_6F088_b7;
    extern int D_6F088_z10, D_6F088_arg, D_6F088_g, D_6F088_h, D_6F088_i, D_6F088_res;
    int r;
    (&D_6F088_b9)[9] = 1;
    *(volatile int*)0xA4600024 = 3;
    *(volatile int*)0xA4600028 = (&D_6F088_b8)[8];
    *(volatile int*)0xA460002C = (&D_6F088_b6)[6];
    *(volatile int*)0xA4600030 = (&D_6F088_b7)[7];
    *(int*)((char*)&D_6F088_z10 + 0x10) = 0;
    gl_func_00000000((char*)&D_6F088_arg + 0x14, 0x60);
    r = gl_func_00000000();
    D_6F088_g = D_6F088_h;
    D_6F088_i = (int)&D_6F088_res;
    *(int*)((char*)&D_6F088_z10 + 0x14) = (int)&D_6F088_res;
    gl_func_00000000(r);
    return (int)&D_6F088_res;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F088);
#endif

void gl_func_0006F144(int a0, ...) {
}

/* Varargs empty stub (sibling of matched gl_func_0006F144). */
void gl_func_0006F160(int a0, ...) {
}

#ifdef NON_MATCHING
/* memcpy: copy a2 bytes from a1 to a0, return a0. Reloc-free. Byte-match cap:
 * the target is a tight 13-insn non-unrolled byte loop, but IDO -O2 UNROLLS the
 * C memcpy by 4 (+ remainder) to 28 insns. Same unroll cap as 1FA20/611E4 —
 * couldn't suppress the unroll from C. */
void *game_libs_func_0006F17C(char *a0, char *a1, int a2) {
    char *p = a0;
    if (a2 != 0) {
        do {
            char c = *a1;
            a2--;
            p++;
            a1++;
            *(p - 1) = c;
        } while (a2 != 0);
    }
    return a0;
}
#else
/* game_libs_func_0006F17C = memcpy(void *dst, u8 *src, int count) -> dst. Same
 * UNROLL CAP as the memset twin 00067D50: target is the NON-unrolled byte-copy
 * loop (lower-opt build); IDO -O2 unrolls by 4. Needs a lower-opt file split. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F17C);
#endif

int game_libs_func_0006F1B0(char *a0) {
    char *p = a0;
    if (*p != 0) {
        do {
            p++;
        } while (*p != 0);
    }
    return p - a0;
}

/* game_libs_func_0006F1D8: leaf-branch-past-end CAP per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F1D8);

/* game_libs_func_0006F1FC: 7-insn string-walk loop-bottom tail-fragment:
 *   lbu v1,1(a0); addiu a0,a0,1; bne v0,v1,-0x1C; nop; move v0,a0;
 *   jr ra; nop
 * Caller-set $v0 + backward branch to 0x6F1EC (before .s start 0x6F1FC).
 * Splat captured loop tail per
 * feedback_backward_branch_before_s_start_is_loop_tail_splat_error. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F1FC);

#ifdef NON_MATCHING
/* Constructor: a0[0]=&sym1, a0[1]=&sym2, a0[2]=0, a0[3]=0, a0[4]=a2, a0[5]=a1
 * (a1 stored in jr delay slot). The function symbol includes 3 leading nops
 * (0x6F218-0x6F220) before the body at 0x6F224 — PREFIX_BYTES inject prepends
 * them to the .o but doesn't extend the symbol to cover them in the linked elf,
 * so byte-exact requires a splat boundary fix (shift symbol to 0x6F224 / absorb
 * the 3 nops as previous-fn padding), not just PREFIX_BYTES. Reloc-blind (two
 * distinct symbols both → 0; PM10 multi-symbol). Body documented; default build
 * stays INCLUDE_ASM. */
void game_libs_func_0006F218(int *a0, int a1, int a2) {
    extern int gl_func_00000000();
    a0[0] = (int)&D_00000000;
    a0[1] = (int)&gl_func_00000000;
    a0[2] = 0;
    a0[3] = 0;
    a0[4] = a2;
    a0[5] = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F218);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F250);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F2C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F35C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F380);

#ifdef NON_MATCHING
/* Sibling of gl_func_0006F3BC — same `(a0 & MASK) != 0 ? 1 : 0` shape
 * with forced sp=-8 frame + unfilled delay slots. Mask = 0x1C here vs
 * 0x3 there.
 *
 * 2026-05-07 boundary fix: split off the 3 trailing insns
 * (`nop; lui t6,0xA480; lw a0,0x18(t6)` — SI status preload for the
 * next function) into game_libs_func_0006F3B0 via split-fragments.py.
 * Symbol is now 9 insns (0x24) — matches target's body size exactly.
 *
 * Cap remaining: target's specific shape is `addiu sp,-8; andi; beqz;
 * nop(delay); b; li v0,1(delay); move v0,zero; jr ra; addiu sp,8(delay)`.
 * Closest C variants:
 *   - plain `if (a0 & MASK) return 1; return 0;` at -O2: 7 insns, no frame
 *   - same at -O1: 8 insns, frame in beqz delay slot (target wants
 *     prologue insn 0 + nop in delay slot)
 *   - -O1 -g2: 12 insns with 4 extra `b epilogue` jumps (no good)
 * Target's 9-insn shape with prologue-first + nop-delay-slot doesn't
 * reproduce from straight C source variation. Likely original used a
 * per-file compile mode (-O1 -g3?) that I haven't tested, OR an
 * inline-asm sequence that IDO accepted in 1998 but not in this build.
 * Wrap stays NM at the volatile form (closest decoded body but bytes
 * diverge by ~3 insns vs the new 9-insn target). */
int gl_func_0006F38C(int a0) {
    volatile int x = a0 & 0x1C;
    if (x != 0) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F38C);
#endif

#ifdef NON_MATCHING
/* game_libs_func_0006F3B0: 3-insn alt-entry/preamble fragment.
 *
 * Body: `nop; lui t6, 0xA480; lw a0, 0x18(t6)` — loads the word at
 * 0xA4800018 (SI_STATUS register) into $a0 then falls through into
 * gl_func_0006F3BC. NO prologue, NO jr ra, NO frame — caller's $ra
 * survives through to gl_func_0006F3BC's epilogue.
 *
 * Was the trailing 3 insns of gl_func_0006F38C until split-fragments.py
 * (2026-05-07) extracted it so gl_func_0006F38C could match its target
 * 9-insn body size. Symbol was named `game_libs_func_*` (not gl_func_*)
 * because splat had no clean callsite to attribute it to.
 *
 * Cap class: tail-fall-through alt-entry. Standard C `return *(int*)0xA4800018;`
 * emits lui + lw + jr ra + nop = 4 insns with jr ra, not the 3-insn
 * fall-through shape. IDO doesn't accept GCC's `register asm("$a0")`
 * (per docs/IDO_CODEGEN.md feedback_ido_no_gcc_register_asm). The
 * matching path requires either:
 *  - Inline asm at the call site that triggers this preamble
 *  - TRUNCATE_TEXT shrinking the C-emit + INSN_PATCH writing the 3
 *    insn words manually
 *  - merge-fragments back into gl_func_0006F3BC (would break that
 *    function's standalone matching at the new offset)
 *
 * Default INCLUDE_ASM build path produces correct bytes via the asm
 * file; this NM wrap exists only to document the cap. */
int game_libs_func_0006F3B0(void) {
    return *(volatile int*)0xA4800018;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F3B0);
#endif

#ifdef NON_MATCHING
/* return (a0 & 3) != 0 ? 1 : 0
 * 9-insn target with forced `addiu sp, -8/+8` stack frame AND NO stack
 * use, plus unfilled delay slot + explicit `b` to epilogue. IDO -O2
 * compacts most C variants to leafy output without the frame.
 *
 * Variant below uses `volatile int x = a0 & 3` — this DOES force the
 * sp=-8 frame AND produces `beqz` in the same direction as target,
 * at the cost of 2 extra insns (sw+lw for volatile materialization,
 * 11 insns total vs target's 9). Structurally closer to target than
 * the plain leafy variant; still NM. See
 * feedback_ido_sp_frame_without_stack_use.md — 30+ variants tested
 * 2026-04-20, the target's idiom (sp=-8 with no sw/lw) isn't reachable
 * from standard IDO -O2 C. Likely alloca/setjmp or per-file pragma.
 *
 * 2026-05-30 flag-matrix + frame-forcing sweep (14 new variants, all NEGATIVE):
 *  - opt/debug matrix {-O0,-O1,-O2} x {plain,-g,-g2,-g3}: EVERY combo is
 *    frameless-leaf (no addiu sp). The doc's "-O1 -g3?" speculation is FALSE
 *    (frameless). -g/-g2/-g3 only add/remove trailing alignment nops + an
 *    extra `jr ra`, never a frame.
 *  - frame-forcing tricks that avoid memory access {unused int[2], unused
 *    char[5], unused volatile int, addr-of-local sink}: ALL DCE'd by IDO -O2
 *    -> still frameless. IDO -O2 removes unused locals incl. their frame.
 *  - alloca(8) IS the only trick that forces a frame AND flips the andi dest
 *    to $t7 (target's reg!) — but it drags in `jal alloca` + a0 stack-reload
 *    (frame -24, sw ra/a0), structurally wrong. Confirms the target frame is
 *    real (not a pad) but has NO clean C trigger: sp=-8 + a0-used-direct +
 *    result-in-t7 needs a frame source IDO won't DCE yet that emits no sw/lw.
 *    None exists in standard C. Genuine cap; INCLUDE_ASM build emits correct
 *    bytes. */
int gl_func_0006F3BC(int a0) {
    volatile int x = a0 & 3;
    if (x != 0) return 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F3BC);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F3BC_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006F3E4)();
s32 gl_func_0006F3E4(char *arg0, s32 arg1, s32 arg2) {
    s32 temp_t7;
    char *temp_s0;

    temp_s0 = ((int(*)())gl_func_00062F64)();
    if (FW(arg0, 0x8) >= FW(arg0, 0x10)) {
loop_1:
        if (arg2 == 1) {
            FW((*(int*)0), 0x10) = 8;
            ((int(*)())gl_func_00062F64)((int)arg0 + 4);
            if (FW(arg0, 0x8) < FW(arg0, 0x10)) {
                goto block_5;
            }
            goto loop_1;
        }
        ((int(*)())gl_func_00062F64)(temp_s0);
        return -1;
    }
block_5:
    temp_t7 = FW(arg0, 0x10);
    FW(arg0, 0xC) = (s32) ((s32) ((FW(arg0, 0xC) + temp_t7) - 1) % temp_t7);
    *(int*)(FW(arg0, 0x14) + (FW(arg0, 0xC) * 4)) = arg1;
    FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) + 1);
    if (*(int*)(FW(arg0, 0x0)) != 0) {
        ((int(*)())gl_func_00062F64)(((int(*)())gl_func_00062F64)(arg0));
    }
    ((int(*)())gl_func_00062F64)(temp_s0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F3E4);
#endif

#ifdef NON_MATCHING
/* gl_func_0006F534: 56-insn game_libs USO version of osSetThreadPri.
 * Same C body shape as kernel func_80006110 (which IS osSetThreadPri),
 * just with all OS-API calls funneled through gl_func_0001CA10 and
 * two distinct D_ aliases playing the role of __osRunningThread + __osRunQueue.
 *
 * Decoded structure (per imm-masked sibling match with func_80006110):
 *   sr = gl_func_0001CA10();   // osDisableInt
 *   if (thread == 0) thread = D_run;
 *   if (thread->pri != pri) {
 *       thread->pri = pri;
 *       if (thread != D_run && thread->state != 1) {
 *           gl_func_0001CA10(thread->queue, thread);  // dequeue
 *           gl_func_0001CA10(thread->queue, thread);  // enqueue (typo? both same call)
 *       }
 *       if (D_runq->pri < D_run->pri) {
 *           D_run->state = 2;
 *           gl_func_0001CA10(&D_runq);  // dispatch
 *       }
 *   }
 *   gl_func_0001CA10(sr);     // osRestoreInt
 *
 * Initial structural wrap; multi-pass tightening pending — needs alias-extern
 * for 2 distinct D_ symbols (D_run vs D_runq) + verified struct offsets. */
extern int gl_func_0001CA10();
extern int D_6F534_run;
extern int D_6F534_runq;
void gl_func_0006F534(int *thread, int pri) {
    int sr;
    int *cur;
    int *rq;
    sr = gl_func_0001CA10();
    if (thread == 0) thread = *(int**)&D_6F534_run;
    if (thread[1] != pri) {
        thread[1] = pri;
        cur = *(int**)&D_6F534_run;
        if (thread != cur && *(unsigned short*)((char*)thread + 0x10) != 1) {
            gl_func_0001CA10(thread[2], thread);
            gl_func_0001CA10(thread[2], thread);
        }
        cur = *(int**)&D_6F534_run;
        rq = *(int**)&D_6F534_runq;
        if (rq[1] < cur[1]) {
            *(short*)((char*)cur + 0x10) = 2;
            gl_func_0001CA10(&D_6F534_runq);
        }
    }
    gl_func_0001CA10(sr);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F534);
#endif

extern int *D_6F614_X;
int game_libs_func_0006F614(int *a0) {
    if (a0 == 0) a0 = D_6F614_X;
    return a0[1];
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F534_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006F634: 20-insn 2-call + 2-global-state-update.
 *   v = call(a0);
 *   (*p_state)[1] = a0;     // *(t7+4) = a0 where t7 = *D_state_ptr
 *   *(short*)*p_flag |= 0x10;  // *(short*)t8 |= 0x10 where t8 = *D_flag_ptr
 *   call(v);
 * Two pointer-deref globals (USO ind-data refs). */
extern int **D_6F634_state;
extern short **D_6F634_flag;
void gl_func_0006F634(int a0) {
    int v = gl_func_00000000(a0);
    (*D_6F634_state)[1] = a0;
    **D_6F634_flag |= 0x10;
    gl_func_00000000(v);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F634);
#endif


/* game_libs_func_0006F684: one 108-insn (0x1B0) function. BOUNDARY MERGED
 * 2026-06-02: splat had split it into 0006F684 (6-insn FP-const prologue:
 * `lwc1 $f0,D[0x24D0]` + `mtc1 a1,$f12`/`mtc1 a2,$f14`/`mtc1 a3,$f16` (THREE
 * inputs, ARG-DERIVED — a Vec3-style float triple — hoisted above the frame;
 * the real entry) + gl_func_0006F69C (the prologue+body using f14 in
 * `mul.s $f14,$f14,$f0`). SINGLE-entry per the dual-vs-single test (f12/f14/f16
 * arg-derived + FP-op use; no callers). Absorbed 0006F69C's 102 words into
 * 0006F684 (0x18 -> 0x1B0); dropped the 0006F69C symbol. Brings f12/f14/f16
 * (=a1/a2/a3) and f0 (=D[0x24D0]) in-scope, retracting the implicit
 * caller-set-float cap; the body is decodable in a future pass. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006F684)();
void game_libs_func_0006F684(char *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 sp40;
    f32 sp3C;
    f32 sp34;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f20;
    f32 temp_f22;

    temp_f0 = (*(f32*)((char*)&D_00000000 + 0x24D0));
    temp_f12 = arg1 * temp_f0;
    temp_f14 = arg2 * temp_f0;
    arg2 = temp_f14;
    arg1 = temp_f12;
    (*(f32*)((char*)&D_00000000 + 0x44030)) = temp_f0;
    arg3 *= temp_f0;
    temp_f20 = ((f32(*)())gl_func_00062F64)(temp_f12, temp_f14);
    temp_f22 = ((f32(*)())gl_func_00062F64)(arg1);
    sp40 = ((f32(*)())gl_func_00062F64)(arg2);
    sp34 = ((f32(*)())gl_func_00062F64)(arg2);
    sp3C = ((f32(*)())gl_func_00062F64)(arg3);
    temp_f0_2 = ((f32(*)())gl_func_00062F64)(arg3);
    (*(f32*)((char*)arg0 + 0x0)) = (f32) (sp34 * temp_f0_2 * arg4);
    (*(f32*)((char*)arg0 + 0x4)) = (f32) (sp34 * sp3C * arg4);
    (*(f32*)((char*)arg0 + 0xC)) = 0.0f;
    (*(f32*)((char*)arg0 + 0x8)) = (f32) (-sp40 * arg4);
    (*(f32*)((char*)arg0 + 0x1C)) = 0.0f;
    temp_f12_2 = temp_f20 * sp40;
    (*(f32*)((char*)arg0 + 0x10)) = (f32) (((temp_f12_2 * temp_f0_2) - (temp_f22 * sp3C)) * arg4);
    (*(f32*)((char*)arg0 + 0x14)) = (f32) (((temp_f12_2 * sp3C) + (temp_f22 * temp_f0_2)) * arg4);
    (*(f32*)((char*)arg0 + 0x18)) = (f32) (temp_f20 * sp34 * arg4);
    (*(f32*)((char*)arg0 + 0x2C)) = 0.0f;
    temp_f12_3 = temp_f22 * sp40;
    (*(f32*)((char*)arg0 + 0x20)) = (f32) (((temp_f12_3 * temp_f0_2) + (temp_f20 * sp3C)) * arg4);
    (*(f32*)((char*)arg0 + 0x24)) = (f32) (((temp_f12_3 * sp3C) - (temp_f20 * temp_f0_2)) * arg4);
    (*(f32*)((char*)arg0 + 0x28)) = (f32) (temp_f22 * sp34 * arg4);
    (*(f32*)((char*)arg0 + 0x30)) = arg5;
    (*(f32*)((char*)arg0 + 0x34)) = arg6;
    (*(f32*)((char*)arg0 + 0x3C)) = 1.0f;
    (*(f32*)((char*)arg0 + 0x38)) = arg7;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006F684);
#endif

#ifdef NON_MATCHING
/* gl_func_0006F834: 26-insn 2-call wrapper with float-bits-passthrough.
 * Decoded shape:
 *   void f(int x0, int x1, int x2, int x3, float a, float b, float c, float d) {
 *     char buf[0x40];
 *     gl_func_00000000(buf, x1, x2, x3, a, b, c, d);
 *     gl_func_00000000(buf, x0);
 *   }
 * Caller passes 4 int reg args + 4 floats via stack at sp+0x78..0x84.
 * Callee reads stack floats via lwc1, forwards to next callee via swc1
 * outgoing slots (sp+0x10..0x1C).
 *
 * Cap: target emits a mysterious mtc1 a1,f12; mtc1 a2,f14; mtc1 a3,f16
 * at entry IMMEDIATELY followed by mfc1 a1,f12; mfc1 a2,f14; mfc1 a3,f16
 * after the lwc1 reads — a net no-op round-trip through FP regs. Likely
 * an IDO emit artifact when args are typed `float` in C but arrive in
 * int regs per O32. No standard C produces this exactly. */
void gl_func_0006F834(int x0, int x1, int x2, int x3,
                      float a, float b, float c, float d) {
    char buf[0x40];
    typedef void (*Fn8)(char*, int, int, int, float, float, float, float);
    typedef void (*Fn2)(char*, int);
    ((Fn8)gl_func_00000000)(buf, x1, x2, x3, a, b, c, d);
    ((Fn2)gl_func_00000000)(buf, x0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F834);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F834_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0006F8A4)();
s32 gl_func_0006F8A4(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t7;
    u8 temp_t4;
    u8 temp_t5;
    u8 temp_t5_2;
    u8 temp_t5_3;
    u8 temp_t5_4;
    u8 temp_t8;
    u8 temp_t8_2;
    u8 temp_t8_3;
    u8 temp_t8_4;
    char *temp_t6;

    temp_t7 = *(s32 *)0xA4600010;
    sp2C = temp_t7;
    if (temp_t7 & 3) {
        do {
            sp2C = *(char *)0xA4600010;
        } while (sp2C & 3);
    }
    temp_t4 = FW(arg0, 0x9);
    temp_t6 = *(int*)(temp_t4 * 4);
    sp28 = (s32) temp_t4;
    if (temp_t6 != arg0) {
        sp24 = temp_t6;
        if (temp_t4 == 0) {
            temp_t8 = FW(arg0, 0x5);
            if (FW(temp_t6, 0x5) != temp_t8) {
                *(s32 *)0xA4600014 = (s32) temp_t8;
            }
            temp_t5 = FW(arg0, 0x6);
            if (FW(sp24, 0x6) != temp_t5) {
                *(s32 *)0xA460001C = (s32) temp_t5;
            }
            temp_t8_2 = FW(arg0, 0x7);
            if (FW(sp24, 0x7) != temp_t8_2) {
                *(s32 *)0xA4600020 = (s32) temp_t8_2;
            }
            temp_t5_2 = FW(arg0, 0x8);
            if (FW(sp24, 0x8) != temp_t5_2) {
                *(s32 *)0xA4600018 = (s32) temp_t5_2;
            }
        } else {
            temp_t8_3 = FW(arg0, 0x5);
            if (FW(sp24, 0x5) != temp_t8_3) {
                *(s32 *)0xA4600024 = (s32) temp_t8_3;
            }
            temp_t5_3 = FW(arg0, 0x6);
            if (FW(sp24, 0x6) != temp_t5_3) {
                *(s32 *)0xA460002C = (s32) temp_t5_3;
            }
            temp_t8_4 = FW(arg0, 0x7);
            if (FW(sp24, 0x7) != temp_t8_4) {
                *(s32 *)0xA4600030 = (s32) temp_t8_4;
            }
            temp_t5_4 = FW(arg0, 0x8);
            if (FW(sp24, 0x8) != temp_t5_4) {
                *(s32 *)0xA4600028 = (s32) temp_t5_4;
            }
        }
        *(int*)(sp28 * 4) = arg0;
    }
    *(s32 *)0xA4600000 = ((int(*)())gl_func_00062F64)(arg3);
    *(s32 *)0xA4600004 = (FW(arg0, 0xC) | arg2) & 0x1FFFFFFF;
    switch (arg1) {                                 /* irregular */
    case 0:
        *(s32 *)0xA460000C = arg4 - 1;
block_27:
        return 0;
    case 1:
        *(s32 *)0xA4600008 = arg4 - 1;
        goto block_27;
    default:
        return -1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F8A4);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0006F8A4_pad.s")

#ifdef NON_MATCHING
/* gl_func_0006FAD4: 32-insn flag-extract + conditional bit-set/clear.
 *   v0 = gl_func_00000000(a0);
 *   flag = (v0 & 0x100) ? 1 : 0;     // test bit 8
 *   if (v0 & 0x80) {                  // test bit 7
 *     a0[1] = a0[1] | flag;           // set bit 0 if flag
 *     a0[1] = a0[1] & ~2;             // clear bit 1
 *   }
 *   return flag;
 *
 * 67.6% — volatile-v0 + volatile-flag forces stack-resident locals as
 * target does. Remaining gap: IDO emits the flag-set as beql + sw-in-
 * delay-slot, but target uses `beq+nop; addiu;beq+sw; sw` (different
 * branch shape). The bitfield rule produces correct 2 sw t->0x4 stores. */
int gl_func_0006FAD4(int* a0) {
    volatile int v0 = gl_func_00000000(a0);
    volatile int flag = (v0 & 0x100) ? 1 : 0;
    if (v0 & 0x80) {
        a0[1] = a0[1] | flag;
        a0[1] = a0[1] & ~2;
    }
    return flag;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FAD4);
#endif

/* gl_func_0006FB54: 64-bit-add-carry helper. Verified decode (m2c via disasm-func.py):
 *   r1 = helper(); r2 = helper();
 *   helper(r1);
 *   sum = (r2 - D[0]) + D[1];
 *   return ((unsigned)sum < (unsigned)D[1]) + D[0];   // carry into the high word
 * (D[0]=*(int*)&D_00000000, D[1]=*(int*)(&D+4); reads D[0] twice = two luis.)
 * Logic exact but sub-80: built 25 insns vs target 34 — the target keeps r1 in $s0
 * across the calls AND spills diff/D[0]/D[1] across the 3rd call (IDO 64-bit-codegen
 * spill pattern); -O2 C optimizes the spills away. Resume: needs the spill pattern
 * (more live ranges across the 3rd call) — multi-tick / permuter. */
#ifdef NON_MATCHING
/* gl_func_0006FB54: 33-insn 64-bit accumulator. r0 = cb(); r1 = cb(); cb(r0);
 * returns a 64-bit global base (hi:lo from two globals) plus the 32-bit delta
 * (r1 - another global), with the manual sltu carry into the high word (long long
 * return in v0:v1). NM (reference decode): three collapsed-placeholder calls +
 * several collapsed D refs (distinct globals collapsed to D_00000000 here);
 * raw-.word game_libs reloc depression. */
extern int gl_func_00000000();
extern int D_00000000;
long long gl_func_0006FB54(int a0) {
    int r0 = gl_func_00000000(a0);
    int r1 = gl_func_00000000(a0);
    int delta = r1 - *(int *)&D_00000000;
    long long base = ((long long)*(int *)&D_00000000 << 32) |
                     (unsigned int)*(int *)((char *)&D_00000000 + 4);
    gl_func_00000000(r0);
    return base + (unsigned int)delta;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FB54);
#endif

#ifdef NON_MATCHING
/* STRUCTURAL first-pass 2026-05-31 (raw-.word USO decode). Straight-line
 * global-state reset: zeroes a struct at &D_fbd8_a (words 0,4) + scalars
 * D_fbd8_b/d, and re-links several global list heads (each `*D_x` is a node
 * pointer): D_c node self-links (n->4=n); D_e n->0=n->4; D_f n->0x10=0,n->0x14=0;
 * D_g copies n->0x10/0x14 to n->8/0xC; D_h n->0x18=0; D_i n->0x1C=0. Symbols are
 * placeholder externs (real D_ names unknown in raw-.word form).
 *
 * 18% partial — NEXT-PASS RESIDUAL ANALYSIS (side-by-side 2026-05-31):
 *  (1) Direct globals (D_a struct, D_b/D_d): target is at-FUSED `lui at,%hi;
 *      sw t,OFF(at)` with the zero pre-loaded into a REGISTER (`li t6,0;
 *      li t7,0`), ours is base-local `lui v1; addiu v1,v1,0; sw zero,OFF(v1)`
 *      (extra addiu + sw $zero). Needs inline-symbol-arith + named zero temps
 *      (docs feedback-ido-inline-symbol-arith-vs-base-local).
 *  (2) Pointer globals: target keeps each `*D_x` in a DISTINCT reg
 *      (t8/t9/t1/t4/t5/t8) with lui/lw HOISTED + interleaved with other
 *      globals' stores; ours reuses $v0 sequentially. Distinct named pointer
 *      locals declared early did NOT fix it (IDO still collapsed to 32 insns
 *      vs 38 — 6 short). Exact hoist/interleave is the hard part.
 *  LIKELY PERMANENT ~18% (2026-05-31, deeper look): the target REUSES scratch
 *  temps across globals (e.g. t6/t7 hold 0 for D_a's stores @0x04/08 then are
 *  reused as D_g's loaded fields @0x68/6C) AND heavily hoists/interleaves the
 *  lui/lw — both scheduler/allocator-determined, same C-uncontrollable class as
 *  the instruction-scheduler swaps. Correct logic; don't expect a 100% match
 *  from C. */
extern int D_fbd8_a, D_fbd8_b, D_fbd8_d;
extern int *D_fbd8_c, *D_fbd8_e, *D_fbd8_f, *D_fbd8_g, *D_fbd8_h, *D_fbd8_i;
void game_libs_func_0006FBD8(void) {
    int *n;
    (&D_fbd8_a)[1] = 0;
    (&D_fbd8_a)[0] = 0;
    D_fbd8_b = 0;
    D_fbd8_d = 0;
    n = D_fbd8_c;
    n[1] = (int)n;
    n = D_fbd8_e;
    n[0] = n[1];
    n = D_fbd8_f;
    n[0x10 / 4] = 0;
    n[0x14 / 4] = 0;
    n = D_fbd8_g;
    n[8 / 4] = n[0x10 / 4];
    n[0xC / 4] = n[0x14 / 4];
    n = D_fbd8_h;
    n[0x18 / 4] = 0;
    n = D_fbd8_i;
    n[0x1C / 4] = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006FBD8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0006FC70);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FC78);

#ifdef NON_MATCHING
/* gl_func_0006FDE8: 29-insn 4-call cascade w/ 64-bit-add via carry detect (0x74, frame 0x28).
 *
 * Decoded structure (raw-word disasm):
 *   func(a0, a1);                                   // 1st call
 *   v0_2 = func();                                  // 2nd call (a0/a1 post-1st-call state)
 *   *D_global = v0_2;                                // store 2nd-call result
 *   // 64-bit add: D_X = D_X + (a0_saved:a1_saved)
 *   {
 *       int low  = *D_X_low + a1_saved;
 *       int carry = ((unsigned)low < (unsigned)a1_saved);
 *       int high = D_X_hi + carry + a0_saved;
 *       // saved to sp+0x20 / sp+0x24 (callsite stack args for func3)
 *   }
 *   func(low, ..., high_via_stack);                  // 3rd call (low in $a0, high at sp+0x20/0x24)
 *   func(v0_2);                                      // 4th call w/ 2nd-call result
 *
 * The 64-bit add via `sltu at, low, addend` + `addu carry, sym_lo` pattern is
 * IDO's standard expansion for `(s64)X = (s64)D + (s64)(a0,a1)` when args
 * 0-1 are an int64 pair (a0=hi, a1=lo).
 *
 * 2026-05-31: 47.9%->73.9% by removing a PHANTOM D_X_hi global (the high part is
 * literal 0, not a global read) + branchless carry. Residual: the 3rd call passes
 * `high` via the stack (sp+0x20) not a1 — the 64-bit-stack-arg convention (frame
 * 0x28 vs 0x20). INCLUDE_ASM remains build path.
 */
extern int D_global_val;
extern unsigned int D_X_low;
/* 64-bit-add helper. X passed as a long long in a0:a1 (hi:lo); adds the
 * 32-bit global D_X_low (zero-extended) producing a 64-bit sum spilled to
 * sp+0x20/0x24. Residual cap: the target spills sum_hi/sum_lo and passes only
 * sum_lo (a0) to the third call (sum_hi spilled-but-dead), which the clean
 * `unsigned long long` add form can't reproduce — the long-long param makes the
 * 64-bit add itself match (carry chain + literal-0 hi word) but reshapes the
 * call convention and global-store ordering (63% vs 74% manual form below). */
void gl_func_0006FDE8(int a0_hi, unsigned int a1_lo) {
    int v0_2;
    unsigned int low;
    int high;
    gl_func_00000000(a0_hi, a1_lo);
    v0_2 = gl_func_00000000();
    D_global_val = v0_2;
    low = D_X_low + a1_lo;
    high = (low < a1_lo) + a0_hi;
    gl_func_00000000(low, high);
    gl_func_00000000(v0_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FDE8);
#endif

#ifdef NON_MATCHING
/* gl_func_0006FE5C: 98-insn 64-bit free-list / heap-block search-and-split helper.
 * Size 0x188, frame 0x38.
 *
 * Walks a singly-linked-list of memory blocks at *(void**)&D_00000000, each
 * node holding a 64-bit free-region (offsets 0x10/0x14 = lo/hi end-pointer
 * pair, offset 0x0 = next-link, offset 0x4 = secondary link). Returns the
 * allocated block via the saved sp+0x28/0x2C pair (v0:v1 64-bit return).
 *
 * Decoded structure (raw-word disasm — high-level):
 *   struct FreeNode {
 *       FreeNode *next;        // 0x0  — list link
 *       FreeNode *secondary;   // 0x4  — secondary link (size-sorted? aux list?)
 *       uint32_t  start_lo;    // 0x10
 *       uint32_t  start_hi;    // 0x14 — alternate: end_lo
 *       // (loop reads 0x10/0x14 as 64-bit range-end pointer)
 *   };
 *
 *   uint64_t alloc_range(uint64_t size) {  // a0:a1 = size (64-bit)
 *       FreeNode *head_jal = setup_alloc(...);            // jal #1 (entry hook)
 *       FreeNode *cursor   = *(FreeNode**)&D_00000000;     // head pointer
 *       if (cursor == NULL) goto epilogue;
 *
 *       // STAGE 1: walk the list looking for a free block where
 *       //   block->[0x14]:[0x10] >= size  (64-bit unsigned compare)
 *       while (cursor != NULL) {
 *           uint64_t end   = ((u64)cursor->[0x14] << 32) | cursor->[0x10];
 *           uint64_t avail = end - cursor_base;
 *           if (avail >= size) break;
 *           cursor = cursor->next;
 *       }
 *       if (!cursor) goto epilogue;
 *
 *       // STAGE 2: split or unlink the block
 *       uint64_t new_end = (((u64)cursor->[0x14] << 32) | cursor->[0x10]) - size;
 *       // Update cursor's range: [0x10]:[0x14] = new_end (shrunk)
 *       cursor->[0x10] = (uint32_t)new_end;
 *       cursor->[0x14] = (uint32_t)(new_end >> 32);
 *
 *       // STAGE 3: chain to secondary list at offset 0x4 — propagate the shrink
 *       FreeNode *sec = cursor->[0x4];
 *       sec->[0x10] = cursor->[0x10];
 *       sec->[0x14] = cursor->[0x14];
 *       sec->[0x0]  = cursor->[0x0];    // (link rewire)
 *       cursor->[0x0]->[0x4] = sec->[0x4];
 *
 *       // STAGE 4: finalize via second jal
 *       finalize(allocated_block);                         // jal #2
 *
 *   epilogue:
 *       return v0:v1 (saved at sp+0x28:0x2C);
 *   }
 *
 * Notes:
 *  - Standard "best-fit free-list with primary+secondary links" pattern,
 *    common in N64 heap allocators. The two-link layout suggests an explicit
 *    size-sorted secondary list for fast lookup.
 *  - 64-bit comparison uses canonical `sltu/subu` chain.
 *  - 2 jal calls bookend the function (entry setup + exit finalize) — likely
 *    interrupt-mask wrap (`__osDisableInt` / `__osRestoreInt` per
 *    reference_1080_libc_export_symbols_in_game_libs.md). Heap operations
 *    must be critical-section guarded.
 *  - Return value is 64-bit v0:v1 — likely (allocated_addr_hi, allocated_addr_lo)
 *    for the K1-mapped uncached address of the new block.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FE5C);
#endif

/* gl_func_0006FFE4: 19-insn 2-call wrapper with intermediate global OR.
 * Verified decode (sub-80 resume-comment per
 * docs/MATCHING_WORKFLOW.md#feedback-sub80-complex-embed-decode-resume-comment):
 *
 *   int r = gl_func(a0);
 *   *(int*)&D_OTHER = (*(int*)&D) | a0;
 *   return gl_func(r);
 *
 * Natural form: 16-17 insns, frame -0x18, r stays in $v0 (no $s0 save).
 * Target: 19 insns, frame -0x28, r preserved via $s0 across the 2nd call
 * (sw s0/lw s0 + or s0,v0,zero + or a0,s0,zero).
 *
 * Cap class: IDO's regalloc doesn't promote r to $s0 without longer live
 * range. `register int r` + struct ordering both ineffective 2026-05-17.
 * Target likely had additional source between calls (maybe a side-effecting
 * helper that got inlined away, leaving the spill+s0-use artifact).
 * Remains INCLUDE_ASM at 68.9%; multi-tick / permuter class. */
#ifdef NON_MATCHING
/* gl_func_0006FFE4: 19-insn wrapper. Calls the (collapsed) callback with a0,
 * OR-folds a0 into a global word, then re-invokes the callback with the first
 * result: r = cb(a0); *D_B = *D_A | a0; cb(r);  (a0 reloaded from its home slot
 * across the first call). NM (reference decode): two collapsed-placeholder calls
 * + two collapsed D refs (raw-.word game_libs reloc depression); the distinct
 * read/write D symbols collapse to D_00000000 here. */
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0006FFE4(int a0) {
    int r = gl_func_00000000(a0);
    *(int *)&D_00000000 = *(int *)&D_00000000 | a0;
    gl_func_00000000(r);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FFE4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070030);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070040);

#ifdef NON_MATCHING
/* gl_func_00070194: 44-insn CRC-5 hash (polynomial 0x15), 16-bit input → 5-bit output.
 * Size 0xB0, frame 0x10.
 *
 * Classic LFSR shift-and-XOR algorithm. Iterates 16 times over the input bits
 * (a0 & 0xFFFF), processing one bit per iteration via shift-feedback:
 *
 * Decoded structure (raw-word disasm):
 *   uint8_t crc5_n64(uint16_t a0) {
 *       uint8_t accum = 0;     // sp+0xF
 *       int     count = 0;     // sp+0x8
 *       a0 &= 0xFFFF;
 *       while (count < 16) {
 *           // If bit 4 of accum is set, XOR with polynomial 0x15
 *           uint8_t mask = (accum & 0x10) ? 0x15 : 0x00;
 *           // Inject next input bit into LSB of accum after shift-left
 *           uint8_t in_bit = (a0 & 0x400) ? 1 : 0;
 *           accum = ((accum << 1) | in_bit) & 0xFF;
 *           // XOR with polynomial
 *           accum ^= mask;
 *           // Shift input left by 1 (bring next bit into position 0x400)
 *           a0 = (a0 << 1) & 0xFFFF;
 *           count++;
 *       }
 *       return accum & 0x1F;   // low 5 bits = CRC-5 result
 *   }
 *
 * Notes:
 *  - Polynomial `0x15` = `0b10101` = CRC-5 / x^5 + x^2 + 1 (one of the
 *    standard CRC-5 polynomials).
 *  - 16-bit input matches N64 joybus controller cmd/status word size.
 *  - Likely `osContSetCh` / `__osControllerCrc` / `__osPfsCrc` family.
 *    Cross-reference libreultra `src/io/{controller,pfsisplug}.c` for
 *    canonical polynomial usage.
 *  - The "if bit 4 set, mask = 0x15 else 0" pattern is the classic LFSR
 *    feedback gate — when the MSB-to-be-shifted-out is 1, mix in the
 *    polynomial. Standard bit-serial CRC computation.
 *  - Bit-extraction via `andi 0x400` (bit 10) reads the MSB of the input
 *    after pre-shifting it to position 10 — IDO's choice of where to
 *    sample the bit may reflect the source-level mask constant being
 *    `0x8000 >> 5` or similar offset shenanigans.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
/* gl_func_00070194: 44-insn CRC-5 (poly 0x15 = x^5+x^2+1) over the low 16 bits of
 * a0. out=0; loop 16 iterations (do-while, NO top guard): tmp = (out&0x10)?0x15:0;
 * out = out<<1; out = out|bit (bit = (a0&0x400)?1:0); out = out^tmp;
 * a0 = (a0<<1)&0xFFFF; return out & 0x1F. RELOC-FREE.
 *
 * 2026-05-25 OPT-LEVEL CORRECTION (supersedes a prior wrong "-O0, 1-insn-off"
 * note): this is NOT an -O0 function. Definitive build-flag matrix vs the target:
 *   - target: 44 insns, do-while (no top guard), `out`/`tmp`/`i` stack-resident
 *     (sb/lbu/sw/lw each use), `bit` kept in a register (a1), delay slots FULLY
 *     filled (only 1 nop, the un-fillable beqz-t7 slot), return via andi->temp->move
 *     pairs (uchar return) with an inline epilogue.
 *   - existing matched -O0 fns (e.g. gl_func_00008944) have UNFILLED slots
 *     (b;nop / jr;nop) -> -O0 is ruled out by the target's filled slots.
 *   - plain -O1 (no -g): fills slots BUT register-allocates out/tmp/i (no
 *     residency) -> 37-40 insns, wrong shape.
 *   - -O1/-O2 -g1/-g2: forces stack residency (debug) BUT leaves slots UNFILLED
 *     (4 nops) -> wrong (target has them filled).
 * The target needs residency AND fully-filled slots SIMULTANEOUSLY, which the
 * project's IDO `cc` cannot emit from any single flag (residency<->-g disables
 * full fill; full fill<->no-g register-allocates). It is an -O1 build whose
 * original register pressure spilled out/tmp/i while the assembler still filled
 * slots -- not reproducible without that exact pressure, and the permuter cannot
 * add assembler-level delay-slot filling. Permuter at -O1 (volatile base) plateaus
 * (~1520, degenerate loop-removal optimum) and a volatile base has a structural
 * extra-reload the target lacks (the `^tmp` reuses the pre-store value, which
 * volatile forbids). See docs/IDO_CODEGEN.md "stack-residency + filled-delay-slots".
 * Genuine cap; keep INCLUDE_ASM. The C below is verified-correct (clean for-loop
 * for readability). */
/* Whole-body decode 2026-06-01 (was 0% — locals stayed in regs). 16-step LFSR:
 * out (sp+15) and i (sp+8) are STACK-resident (reloaded each access), so out's
 * update is three separate stores (<<1, |bit, ^tmp) with tmp at sp+14. Forced
 * via volatile so IDO emits the per-substep sb/lbu the target has. */
int gl_func_00070194(int a0) {
    volatile unsigned char out;
    volatile int i;
    volatile unsigned char tmp;
    int bit;
    a0 = a0 & 0xFFFF;
    out = 0;
    i = 0;
    do {
        tmp = (out & 0x10) ? 21 : 0;
        out = out << 1;
        bit = (a0 & 0x400) ? 1 : 0;
        out = out | bit;
        out = out ^ tmp;
        a0 = (a0 << 1) & 0xFFFF;
        i = i + 1;
    } while (i < 16);
    return out & 0x1F;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070194);
#endif

/* gl_func_00070244: bit-serial CRC (poly 0x85) over 32 input bytes + 1 flush.
 * FULLY DECODED — the exact C is:
 *   int gl_func_00070244(unsigned char *a0) {
 *       int j, i; unsigned char r = 0;
 *       for (j = 0; j < 33; j++) {                 // j==32 = trailing flush
 *           for (i = 7; i >= 0; i--) {             // MSB-first bits of *a0
 *               unsigned char poly = (r & 0x80) ? 0x85 : 0;
 *               r = r << 1;
 *               if (j == 32) r = r & 0xFF;
 *               else r |= (*a0 & (1 << i)) ? 1 : 0;
 *               r = r ^ poly;
 *           }
 *           a0++;
 *       }
 *       return r;
 *   }
 * This is an -O1 FUNCTION (all locals stack-resident, reloaded each use). At
 * default -O2 it register-promotes (36 insns, 35%); at -O0 it's 64 insns.
 * -O1 EMPIRICALLY TESTED 2026-06-02 (isolated carve .o vs expected): the
 * sequence matches BUT it does NOT cleanly match, for two reasons that
 * decl-order tuning does NOT fix:
 *   (1) 53 insns vs target 52 — a redundant truncation `andi`: the j==32 path
 *       `r = r<<1; r = r & 0xFF;` makes -O1 emit andi BOTH for the r<<1 uchar
 *       store AND the &0xFF, where target emits only one (its r<<1 store relies
 *       on `sb` to truncate, no andi). No C shape tested removes the first andi.
 *   (2) spill-slot offsets diverge (target r@15/poly@14/j@8/i@4 = ints-low/
 *       chars-high; every decl order tried gives chars-low/ints-high, ~37 byte
 *       diffs). IDO -O1 won't place the byte locals high from C.
 * Net est. <80% fuzzy, so a per-file -O1 carve (which needs a ~90-fn split of
 * post.c) is NOT worth it — it wouldn't clear the NM threshold. Permuter-class
 * spill-layout + truncation cap. Stays INCLUDE_ASM. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070244)();
u8 gl_func_00070244(u8 *arg0) {
    u8 spF;
    u8 spE;
    s32 sp8;
    s32 sp4;
    s32 temp_t5;
    s32 temp_t7;
    s32 var_a1;
    u8 *var_a0;
    u8 temp_t1;

    var_a0 = arg0;
    spF = 0;
    sp8 = 0;
    do {
        sp4 = 7;
loop_2:
        if (spF & 0x80) {
            spE = 0x85;
        } else {
            spE = 0;
        }
        temp_t1 = spF * 2;
        spF = temp_t1;
        if (sp8 == 0x20) {
            spF = temp_t1 & 0xFF;
        } else {
            if (*(int*)var_a0 & (1 << sp4)) {
                var_a1 = 1;
            } else {
                var_a1 = 0;
            }
            spF |= var_a1;
        }
        temp_t5 = sp4 - 1;
        sp4 = temp_t5;
        spF ^= spE;
        if (temp_t5 >= 0) {
            goto loop_2;
        }
        var_a0 += 1;
        temp_t7 = sp8 + 1;
        sp8 = temp_t7;
    } while (temp_t7 < 0x21);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070244);
#endif

/* game_libs_func_00070314: 3-insn `mtc0 a0, $11; jr ra; nop` Compare-register
 * write. CP0 access (mtc0) is MIPS3 runtime — IDO C can't emit CP0 ops from
 * standard C. CAP class per reference_1080_mips3_runtime_helpers. Default
 * INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070314);

/* game_libs_func_00070320: 194-insn (0x308) memmove/memcpy with overlap +
 * alignment dispatch. BOUNDARY MERGED 2026-06-02: a multi-path/multi-exit
 * routine (forward-copy, backward-copy, word-aligned, byte paths — several
 * internal `jr ra` exits) that splat carved into three symbols (70320 head +
 * 70398 middle + 70508 tail). 70320 branches forward to 0x704BC (in 70398);
 * 70398/70508 branch backward to 0x70370/0x704D8 (inside this body). Absorbed
 * 70398+70508 (0x78 -> 0x308); dropped both symbols (no external callers). All
 * branches verified in-range; ends at 0x70628 (pre-existing 0xC align pad
 * before gl_func_00070634). Reloc-blind USO; stays INCLUDE_ASM. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070320)();
s32 game_libs_func_00070320(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0_11;
    s16 temp_v0_3;
    s16 temp_v1;
    s16 temp_v1_5;
    s32 temp_a3;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t0_4;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t3;
    s32 temp_t3_2;
    s32 temp_t4;
    s32 temp_t4_2;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_v0;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 *var_a1_2;
    s32 var_a2;
    s8 *var_a0_3;
    s8 temp_v0_10;
    s8 temp_v0_12;
    s8 temp_v0_16;
    s8 temp_v0_2;
    s8 temp_v0_4;
    s8 temp_v0_8;
    char *var_a1_3;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    temp_a3 = var_a1;
    if ((var_a2 != 0) && (var_a0 != var_a1)) {
        if ((var_a1 >= var_a0) && (var_a1 < (var_a0 + var_a2))) {
            var_a0_2 = var_a0 + var_a2;
            var_a1_2 = var_a1 + var_a2;
            if (var_a2 >= 0x10) {
                temp_v0 = var_a0_2 & 3;
                if (temp_v0 == ((int)var_a1_2 & 3)) {
                    switch (temp_v0) {              /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        break;
                    default:                        /* switch 2 */
                        temp_v0_2 = FW(var_a0_2, -0x1);
                        var_a0_2 -= 1;
                        var_a1_2 -= 1;
                        var_a2 -= 1;
                        *var_a1_2 = temp_v0_2;
                        break;
                    case 2:                         /* switch 2 */
                        temp_v0_3 = FW(var_a0_2, -0x2);
                        var_a0_2 -= 2;
                        var_a1_2 -= 2;
                        var_a2 -= 2;
                        *var_a1_2 = temp_v0_3;
                        break;
                    case 3:                         /* switch 2 */
                        temp_v0_4 = FW(var_a0_2, -0x1);
                        temp_v1 = FW(var_a0_2, -0x3);
                        var_a0_2 -= 3;
                        var_a1_2 -= 3;
                        var_a2 -= 3;
                        FW(var_a1_2, 0x2) = temp_v0_4;
                        FW(var_a1_2, 0x0) = temp_v1;
                        break;
                    }
loop_35:
                    if (var_a2 >= 0x20) {
                        temp_v0_5 = FW(var_a0_2, -0x4);
                        temp_v1_2 = FW(var_a0_2, -0x8);
                        temp_t0 = FW(var_a0_2, -0xC);
                        temp_t1 = FW(var_a0_2, -0x10);
                        temp_t2 = FW(var_a0_2, -0x14);
                        temp_t3 = FW(var_a0_2, -0x18);
                        temp_t4 = FW(var_a0_2, -0x1C);
                        temp_t5 = FW(var_a0_2, -0x20);
                        var_a0_2 -= 0x20;
                        var_a1_2 -= 0x20;
                        var_a2 -= 0x20;
                        FW(var_a1_2, 0x1C) = temp_v0_5;
                        FW(var_a1_2, 0x18) = temp_v1_2;
                        FW(var_a1_2, 0x14) = temp_t0;
                        FW(var_a1_2, 0x10) = temp_t1;
                        FW(var_a1_2, 0xC) = temp_t2;
                        FW(var_a1_2, 0x8) = temp_t3;
                        FW(var_a1_2, 0x4) = temp_t4;
                        FW(var_a1_2, 0x0) = temp_t5;
                        goto loop_35;
                    }
loop_37:
                    if (var_a2 >= 0x10) {
                        temp_v0_6 = FW(var_a0_2, -0x4);
                        temp_v1_3 = FW(var_a0_2, -0x8);
                        temp_t0_2 = FW(var_a0_2, -0xC);
                        temp_t1_2 = FW(var_a0_2, -0x10);
                        var_a0_2 -= 0x10;
                        var_a1_2 -= 0x10;
                        var_a2 -= 0x10;
                        FW(var_a1_2, 0xC) = temp_v0_6;
                        FW(var_a1_2, 0x8) = temp_v1_3;
                        FW(var_a1_2, 0x4) = temp_t0_2;
                        FW(var_a1_2, 0x0) = temp_t1_2;
                        goto loop_37;
                    }
loop_39:
                    if (var_a2 >= 4) {
                        temp_v0_7 = FW(var_a0_2, -0x4);
                        var_a0_2 -= 4;
                        var_a1_2 -= 4;
                        var_a2 -= 4;
                        *var_a1_2 = temp_v0_7;
                        goto loop_39;
                    }
                }
            }
            if (var_a2 != 0) {
                var_a0_3 = var_a0_2 - 1;
                var_a1_3 = var_a1_2 - 1;
                temp_v1_4 = var_a0_3 - var_a2;
                do {
                    temp_v0_8 = *(int*)var_a0_3;
                    var_a0_3 -= 1;
                    var_a1_3 -= 1;
                    FW(var_a1_3, 0x1) = temp_v0_8;
                } while ((int)var_a0_3 != temp_v1_4);
                return temp_a3;
            }
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return temp_a3;
        }
        if (var_a2 >= 0x10) {
            temp_v0_9 = var_a0 & 3;
            if (temp_v0_9 == (var_a1 & 3)) {
                switch (temp_v0_9) {                /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    break;
                default:                            /* switch 1 */
                    temp_v0_10 = FW(var_a0, 0x0);
                    var_a0 += 1;
                    var_a1 += 1;
                    var_a2 -= 1;
                    FW(var_a1, -0x1) = temp_v0_10;
                    break;
                case 2:                             /* switch 1 */
                    temp_v0_11 = (s16) FW(var_a0, 0x0);
                    var_a0 += 2;
                    var_a1 += 2;
                    var_a2 -= 2;
                    FW(var_a1, -0x2) = temp_v0_11;
                    break;
                case 1:                             /* switch 1 */
                    temp_v0_12 = FW(var_a0, 0x0);
                    temp_v1_5 = FW(var_a0, 0x1);
                    var_a0 += 3;
                    var_a1 += 3;
                    var_a2 -= 3;
                    FW(var_a1, -0x3) = temp_v0_12;
                    FW(var_a1, -0x2) = temp_v1_5;
                    break;
                }
loop_17:
                if (var_a2 >= 0x20) {
                    temp_v0_13 = FW(var_a0, 0x0);
                    temp_v1_6 = FW(var_a0, 0x4);
                    temp_t0_3 = FW(var_a0, 0x8);
                    temp_t1_3 = FW(var_a0, 0xC);
                    temp_t2_2 = FW(var_a0, 0x10);
                    temp_t3_2 = FW(var_a0, 0x14);
                    temp_t4_2 = FW(var_a0, 0x18);
                    temp_t5_2 = FW(var_a0, 0x1C);
                    var_a0 += 0x20;
                    var_a1 += 0x20;
                    var_a2 -= 0x20;
                    FW(var_a1, -0x20) = temp_v0_13;
                    FW(var_a1, -0x1C) = temp_v1_6;
                    FW(var_a1, -0x18) = temp_t0_3;
                    FW(var_a1, -0x14) = temp_t1_3;
                    FW(var_a1, -0x10) = temp_t2_2;
                    FW(var_a1, -0xC) = temp_t3_2;
                    FW(var_a1, -0x8) = temp_t4_2;
                    FW(var_a1, -0x4) = temp_t5_2;
                    goto loop_17;
                }
loop_19:
                if (var_a2 >= 0x10) {
                    temp_v0_14 = FW(var_a0, 0x0);
                    temp_v1_7 = FW(var_a0, 0x4);
                    temp_t0_4 = FW(var_a0, 0x8);
                    temp_t1_4 = FW(var_a0, 0xC);
                    var_a0 += 0x10;
                    var_a1 += 0x10;
                    var_a2 -= 0x10;
                    FW(var_a1, -0x10) = temp_v0_14;
                    FW(var_a1, -0xC) = temp_v1_7;
                    FW(var_a1, -0x8) = temp_t0_4;
                    FW(var_a1, -0x4) = temp_t1_4;
                    goto loop_19;
                }
loop_21:
                if (var_a2 >= 4) {
                    temp_v0_15 = *(int*)var_a0;
                    var_a0 += 4;
                    var_a1 += 4;
                    var_a2 -= 4;
                    FW(var_a1, -0x4) = temp_v0_15;
                    goto loop_21;
                }
            }
        }
        if (var_a2 != 0) {
            temp_v1_8 = var_a0 + var_a2;
            do {
                temp_v0_16 = *(int*)var_a0;
                var_a0 += 1;
                var_a1 += 1;
                FW(var_a1, -0x1) = temp_v0_16;
            } while (var_a0 != temp_v1_8);
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return temp_a3;
    }
    return temp_a3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070320);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070244_pad.s")

#ifdef NON_MATCHING
/* gl_func_00070634: 22-insn 2-call bit-mask helper.
 *   v0 = func();                                          // (some setup call)
 *   mask = ~(a0 & ~0x401);                                // clear bits 0,9 of a0, invert
 *   *(D2) = *(D) & mask;                                  // mask bit-clear D into D2
 *   func(v0);                                             // (cleanup call)
 *
 * Uses 2 distinct extern symbols (D_00000000 + gl_data_00000000) to bust
 * IDO CSE per docs/IDO_CODEGEN.md#feedback-ido-cse-bust-via-distinct-externs.
 *
 * 85.45% cap: target uses $s0 to preserve v0=func() return across call#2,
 * giving frame -0x28 (s0-save + slot for caller a0). Built keeps v0 in $v0
 * across the call and spills a0 to caller arg slot, frame -0x18.
 *
 * 2026-05-17 tested `register int v0 = func();` — no change at 85.45%.
 * IDO ref-count formula doesn't promote v0 to $s0 from `register` alone
 * (per feedback-ido-register-keyword-doesnt-block-constant-fold style cap).
 * Permuter-class register-allocation cap. */
extern int gl_data_00000000;
void gl_func_00070634(int a0) {
    int v0 = func_00000000();
    int mask = ~(a0 & ~0x401);
    *(int*)&gl_data_00000000 = (*(int*)&D_00000000) & mask;
    func_00000000(v0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070634);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070634_pad.s")
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070694)();
void gl_func_00070694(char *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    s32 var_v1;
    char *temp_v0;
    char *var_v0;

    ((int(*)())gl_func_00062F64)();
    temp_f0 = arg2 - arg1;
    var_v0 = arg0;
    temp_f12 = arg6 - arg5;
    (*(f32*)((char*)var_v0 + 0x0)) = (f32) (2.0f / temp_f0);
    temp_f2 = arg4 - arg3;
    (*(f32*)((char*)var_v0 + 0x28)) = (f32) (-2.0f / temp_f12);
    (*(f32*)((char*)var_v0 + 0x14)) = (f32) (2.0f / temp_f2);
    (*(f32*)((char*)var_v0 + 0x30)) = (f32) (-(arg2 + arg1) / temp_f0);
    (*(f32*)((char*)var_v0 + 0x34)) = (f32) (-(arg4 + arg3) / temp_f2);
    (*(f32*)((char*)var_v0 + 0x3C)) = 1.0f;
    (*(f32*)((char*)var_v0 + 0x38)) = (f32) (-(arg6 + arg5) / temp_f12);
    var_v1 = 1;
    var_f18 = (*(f32*)((char*)var_v0 + 0x4));
    var_f12 = (*(f32*)((char*)var_v0 + 0x0)) * arg7;
    var_f14 = (*(f32*)((char*)var_v0 + 0x8));
    var_f16 = (*(f32*)((char*)var_v0 + 0xC));
    if (1 != 4) {
        do {
            temp_f10 = var_f18 * arg7;
            var_f18 = (*(f32*)((char*)var_v0 + 0x14));
            temp_f6 = var_f14 * arg7;
            var_f14 = (*(f32*)((char*)var_v0 + 0x18));
            var_v1 += 1;
            temp_f4 = var_f16 * arg7;
            var_f16 = (*(f32*)((char*)var_v0 + 0x1C));
            (*(f32*)((char*)var_v0 + 0x0)) = var_f12;
            var_f12 = (*(f32*)((char*)var_v0 + 0x10)) * arg7;
            (*(f32*)((char*)var_v0 + 0x4)) = temp_f10;
            (*(f32*)((char*)var_v0 + 0x8)) = temp_f6;
            var_v0 += 0x10;
            (*(f32*)((char*)var_v0 + -0x4)) = temp_f4;
        } while (var_v1 != 4);
    }
    temp_v0 = var_v0 + 0x10;
    (*(f32*)((char*)temp_v0 + -0x10)) = var_f12;
    (*(f32*)((char*)temp_v0 + -0xC)) = (f32) (var_f18 * arg7);
    (*(f32*)((char*)temp_v0 + -0x8)) = (f32) (var_f14 * arg7);
    (*(f32*)((char*)temp_v0 + -0x4)) = (f32) (var_f16 * arg7);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070694);
#endif

#ifdef NON_MATCHING
/* gl_func_000707E8: 26-insn float-forwarding wrapper. Receives 7 floats (a1-a3
 * in arg regs + 4 on the stack) and a0; builds them into a stack scratch buffer
 * by calling the (collapsed) callback cb(buf, a1, a2, a3, f5, f6, f7, f8), then
 * processes it with cb(buf, a0). NM (reference decode): two collapsed-placeholder
 * calls (raw-.word game_libs reloc depression) + the mtc1/mfc1 float-arg
 * marshalling and K&R float promotion are not byte-reproducible. */
extern int gl_func_00000000();
void gl_func_000707E8(int a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7) {
    char buf[0x40];
    gl_func_00000000(buf, a1, a2, a3, a4, a5, a6, a7);
    gl_func_00000000(buf, a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000707E8);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00070850)();
void game_libs_func_00070850(char *arg0, char *arg1) {
    f32 var_f16;
    f32 var_f18;
    s32 temp_f12;
    s32 temp_f12_2;
    s32 temp_f14;
    s32 temp_f14_2;
    s32 var_a0;
    s32 var_a2;
    char *var_a3;
    char *var_t0;
    char *var_v0;
    char *var_v1;

    var_v0 = arg1;
    var_v1 = (int)arg1 + 0x20;
    var_a2 = 0;
    var_a3 = arg0;
    do {
        var_t0 = var_a3;
        var_a0 = 1;
        var_f18 = *(f32*)((char*)var_t0 + 0x0);
        var_f16 = *(f32*)((char*)var_t0 + 0x4) * 65536.0f;
        if (1 != 2) {
            do {
                var_a0 += 1;
                var_v0 += 4;
                var_v1 += 4;
                var_t0 += 8;
                temp_f12 = (s32) var_f16;
                temp_f14 = (s32) (var_f18 * 65536.0f);
                FW(var_v0, -0x4) = (s32) ((temp_f14 & 0xFFFF0000) | ((temp_f12 >> 0x10) & 0xFFFF));
                FW(var_v1, -0x4) = (s32) (((temp_f14 << 0x10) & 0xFFFF0000) | (temp_f12 & 0xFFFF));
                var_f18 = *(f32*)((char*)var_t0 + 0x0);
                var_f16 = *(f32*)((char*)var_t0 + 0x4) * 65536.0f;
            } while (var_a0 != 2);
        }
        var_v0 += 4;
        var_v1 += 4;
        temp_f12_2 = (s32) var_f16;
        temp_f14_2 = (s32) (var_f18 * 65536.0f);
        FW(var_v0, -0x4) = (s32) ((temp_f14_2 & 0xFFFF0000) | ((temp_f12_2 >> 0x10) & 0xFFFF));
        FW(var_v1, -0x4) = (s32) (((temp_f14_2 << 0x10) & 0xFFFF0000) | (temp_f12_2 & 0xFFFF));
        var_a2 += 1;
        var_a3 += 0x10;
    } while (var_a2 != 4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070850);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00070954: 4x4 identity matrix init. Outer runtime row loop;
 * inner (unrolled) cols set (row == col) ? 1.0f : 0.0f. 83% NM.
 * KEY: the single-level form (`m[0]=(row==0)?..; m[1]=(row==1)?..`) lets IDO
 * fold the ternaries (row known per unrolled iter) and FULLY unroll -> 45%. The
 * NESTED form below keeps `col` a runtime inner-loop var so `(row==col)` can't
 * fold, preserving the target's outer row loop + bnel column compares (+37pp).
 * Residual = constant-register shift (mine a1..a3/t0 for col consts 1/2/3 +
 * bound 4; target a0..a3) + first-col bne-vs-bnel — regalloc/scheduling. */
void game_libs_func_00070954(float *m) {
    int row, col;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            m[col] = (row == col) ? 1.0f : 0.0f;
        }
        m += 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070954);
#endif

/* 12-insn 2-call wrapper using a 0x40-byte stack buffer (0x30). LANDED
 * fuzzy=100. The 2 trailing stolen-prologue insns for the successor
 * (lui $at,0x3780; mtc1 $at,$f0 — float-constant load) were historically
 * absorbed via SUFFIX_BYTES; mechanism REMOVED 2026-05-23 as match-faking. */
void gl_func_000709DC(int a0) {
    char buf[0x40];
    gl_func_00000000(buf);
    gl_func_00000000(buf, a0);
}

#ifdef NON_MATCHING
/* gl_func_00070A14: too-big-N-function-bundle (declared 0xEC, 59 words) — 3 functions.
 * Bundle: 1 complex bit-pack routine + 2 libultra CP0 interrupt-mask helpers.
 *
 * SUB-FUNCTION 1 (0x70A14..0x70AC4, 44 insns) — bit-pack loop:
 *     // Caller passes start_ptr_1 (a0), start_ptr_2 (a1), count (a2-ish), val (a3)
 *     // Two pointer cursors advance in lockstep through paired buffers.
 *     // Inner loop body packs `(src1[i] >> 16) | (src2[j] & 0xFFFF_0000)` and
 *     // stores to dst at offsets advancing by +8 / +0x10. Includes lwc1 + fp
 *     // conversions (`cvt.s.w` / `mul.s` / `sub.s`) and swc1 stores at -8 / -4
 *     // offsets relative to the post-incremented cursor.
 *     // Pattern: likely a vertex-compression / paired-halfword packer for
 *     // RDP F3DEX2 vertex format or audio-sample blitter.
 *
 * SUB-FUNCTION 2 (0x70AC4..0x70AE4, 8 insns) — __osDisableInt:
 *     uint32_t __osDisableInt(void) {
 *         uint32_t prev;
 *         __asm("mfc0 %0, $12" : "=r"(prev));      // read Status (CP0 reg 12)
 *         __asm("mtc0 %0, $12" : : "r"(prev & ~1)); // clear IE bit
 *         return prev & 1;                          // return old IE state
 *     }
 *
 * SUB-FUNCTION 3 (0x70AE4..0x70AFC, 6 insns) — __osSetIntMask / __osRestoreInt:
 *     void __osSetIntMask(uint32_t mask) {
 *         uint32_t prev;
 *         __asm("mfc0 %0, $12" : "=r"(prev));
 *         __asm("mtc0 %0, $12" : : "r"(prev | mask));   // OR-set Status bits
 *     }
 *
 * Notes:
 *  - f2 + f3 are canonical libultra interrupt-control primitives.
 *    See libreultra `src/os/disableInt.c` and `setIntMask.c`. Could be
 *    promoted to byte-exact via libreultra source if compiled with IDO.
 *  - f1's inner pack `(a >> 16) | (b & 0xFFFF0000)` uses lui $t2, 0xFFFF as
 *    a 32-bit mask constant. The trailing `cvt.s.w` and `mul.s/sub.s` are
 *    fixed-point → float conversion (likely for vertex normalization).
 *  - 3 internal `jr $ra` confirm 3-function bundle. Splat boundary issue.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
/* gl_func_00070A14: 4x2 nested-loop packed-short→float converter. ARCHITECTURAL CAP
 * (caller-set $f0): each inner iter recombines halfwords from two src cursors (a1, a1+0x20),
 * cvt.s.w to float, and multiplies by $f0 — but $f0 is read with NO preceding load and is
 * NOT an o32 float-arg reg (f12/f14), so it is a caller-set float the C calling convention
 * can't express (cf. feedback_caller_set_int_reg / caller-set-float cap). Permanent
 * INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070A14);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070AC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070AE4);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070A14_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070B04);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070B04_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070C44);

/* game_libs_func_00070FA0: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070FA0);
