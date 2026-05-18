#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


/* func_00012E00 - verified structural decode (0x24C, 147 insns,
 * get-or-create constructor + work-buffer allocation). bootup_uso
 * constructor family (cf. func_00005124 / func_0001438C).
 *   void *func_00012E00(void *a0, int a1) {
 *       o = a0 ? a0 : func_00000000(0x78); if (!o) return 0;
 *       s = func_00000000(0x2C);
 *       func_00000000(s, &D_0000C730);            // init sub
 *       s->0x28 = &D_a;  o->0x28 = &D_b;          // descriptors
 *       o->0xC  = &D_0000C738;                    // type/vtable
 *       o->0x5C = 0x20;                            // dim W
 *       o->0x60 = 0x20;                            // dim H
 *       o->0x64 = 0x400;                           // cell count
 *       o->0x2C = a1;
 *       o->0x48 = 1.0f;                            // scale
 *       o->0x?? = func_00000000(...);              // init buffer
 *       o->0x4C = func_00000000(0x800, 0x10);     // alloc 2048 B
 *       o->0x50 = func_00000000(0x400, 0x10);     // alloc 1024 B
 *       o->0x58 = func_00000000(0x1000);          // alloc 4096 B
 *       ... = func_00000000(0x1000);              // another 4096
 *       ...
 *   }
 * Struct-typing reference: o = 0x78-byte object. o->0x28 (40)
 * descriptor (&D), o->0xC (12) type/vtable (&D_0000C738), o->0x2C
 * (44) = a1, o->0x48 (72) f32 = 1.0 (scale/alpha), o->0x5C (92) /
 * o->0x60 (96) s32 = grid dims 0x20 x 0x20, o->0x64 (100) s32 =
 * 0x400 cell count (= 32*32). o->0x4C (76) / o->0x50 (80) / o->0x58
 * (88) = pointers to work buffers allocated at sizes 0x800 / 0x400
 * / 0x1000 (some with 0x10 alignment arg). s = 0x2C-byte sub-object
 * (s->0x28 descriptor, init datum D_0000C730). Likely a 32x32
 * tile/heightfield/render-target context. Caps <80: get-or-create
 * + alloc-cascade (~8 func_00000000 buffer reloc) + &D descriptors
 * + FP-1.0 const. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001304C);

int func_00013924(int *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        if (*(int*)((char*)a0 + 0x68) == 0) {
            func_00000000(&D_00000000, 1);
        }
        return 1;
    }
    return 0;
}

int func_00013980(float *a0) {
    if (*(float*)((char*)a0 + 0x48) == 1.0f) {
        return 1;
    }
    return 0;
}

/* func_000139B0 - verified structural decode (0x170, 92 insns,
 * 2D grid reset + random scatter).
 *   void func_000139B0(St *s1, int a1, int a2) {
 *       s1->0x68 = a2;
 *       if (a2 == 0) { s1->0x6C = 1; s1->0x70 = 3; }
 *       else         { s1->0x6C = 0; }
 *       if (a1 == s1->0x40) return;
 *       s1->0x40 = a1;
 *       s1->0x44 = 4;
 *       s1->0x74 = 0;
 *       for (r = 0; r < s1->0x60; r++)            // clear grid
 *           for (c = 0; c < s1->0x5C; c++)
 *               ((f32*)s1->0x58)[c] = 0.0f;
 *       for (k = 0; k < 5; k++) {                 // scatter 5 pts
 *           x = (int)(rand01() * 32.0f);
 *           y = (int)(rand01() * 32.0f);
 *           v =       rand01() * D_00000C64;
 *           *(f32*)((char*)s1->0x58 + x*4 + (y << 7)) = v;
 *       }
 *       func_00000000(s1);                        // finalize
 *       s1->0x48 = 0.0f;
 *   }
 * (rand01 = func_00000000() with no args -> f0, a 0..1 RNG.)
 * Struct-typing reference: s1->0x58 (88) = base ptr of a 2D f32
 * grid, s1->0x5C (92) s32 columns, s1->0x60 (96) s32 rows (row
 * stride = 128 bytes = 0x80, i.e. 32 f32 cells/row given the
 * y<<7 index). s1->0x40 (64) s32 = current key/seed (skip if
 * unchanged), s1->0x44 (68) = 4 (state), s1->0x48 (72) f32 = 0.0
 * (reset accumulator), s1->0x68 (104) = a2 (mode), s1->0x6C (108)
 * / s1->0x70 (112) = mode-derived flags (1/3 when a2==0, else
 * 0), s1->0x74 (116) = 0. D_00000C64 = f32 value-scale for the
 * scattered amplitude. Looks like a randomized snow/terrain
 * height-field seed. Caps <80: FP-heavy mul.s/trunc.w.s +
 * f20/f22/f24 sdc1/ldc1 double-saves + D_00000C64 reloc + 3x
 * func_00000000 RNG calls + nested clear loop + bnel
 * branch-likely. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000139B0);

/* func_00013B20 - verified structural decode (0x144, 84 insns,
 * LUT index->value remap with all-ones fallback).
 *   void func_00013B20(St *a0) {
 *       root = *(void**)(func_0000023C + 4);
 *       v = root->0x28;
 *       lut = (u16*)(*(fn)v->0x64)((s16)v->0x60 + root); // vtable
 *       if (a0->0x68 != 0) {                      // remap path
 *           int *src = a0->0x54;                  // index array
 *           u16 *dst = a0->0x4C;                  // output
 *           for (i = 0; i != 0x1000/4; i += 4) {  // 4-unrolled
 *               dst[0] = lut[src[i+0]];
 *               dst[1] = lut[src[i+1]];
 *               dst[2] = lut[src[i+2]];
 *               dst[3] = lut[src[i+3]];
 *               dst += 4;
 *           }
 *       } else {                                  // fill path
 *           u16 *dst = a0->0x4C;
 *           for (j = 0; j != 0x800; j += 8) {     // 4-unrolled
 *               dst[0] = dst[1] = dst[2] = dst[3] = 1;
 *               dst += 4;
 *           }
 *       }
 *   }
 * Struct-typing reference: root = *(func_0000023C+4) global ctx;
 * root->0x28 (40) vtable ptr, fn @0x64 (100) + s16 base-adjust
 * @0x60 (96) returns a u16 lookup table (the obj-0x28 dispatch
 * idiom, 0x64/0x60 variant). a0->0x54 (84) = source int index
 * array (0x400 entries, 0x1000 bytes), a0->0x4C (76) = dest u16
 * array (0x400 entries, 0x800 bytes), a0->0x68 (104) = mode gate
 * (nonzero -> remap each src index through lut; zero -> fill dest
 * with 1). Likely a tile/palette index-to-colour expansion. Caps
 * <80: vtable jalr + func_0000023C+4 reloc data ref + 4-way
 * unrolled nested loop + beql branch-likely. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013B20);

void func_00013C70(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CAC(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00013CE8(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

/* func_00013D40 - verified structural decode (0x2A0, 168 insns).
 * NEAR-SIBLING of func_0001438C / func_00008124 (bootup_uso
 * get-or-create constructor + N child sub-objects family); variant:
 * object 0x98, more children, datums D_0000CAAC/CAC0/CAC4/CAC8 +
 * D_0000C764, child->0x10 = 0x1E.
 *   void *func_00013D40(void *a0) {
 *       o = a0 ? a0 : alloc(0x98); if (!o) return 0;
 *       s = alloc(8);
 *       if (s) { s->0x0 = &D_0000CAAC; s->0x4 = 0; }
 *       v = *(int*)&D_0000CAC0;
 *       if (o != (void*)-8) {                      // defensive
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);                  // func_00000000
 *               c->0x10 = 0x1E;
 *               c->0xC  = &D_0000C764;             // type/vtable
 *               c->0x14 = 0;
 *           }
 *       }
 *       v = *(int*)&D_0000CAC4;
 *       if (o != (void*)-0x20) { c2 = alloc(0x18); ... }
 *       ... (further children from D_0000CAC8, same shape) ...
 *   }
 * Struct-typing reference (same family as func_0001438C): o =
 * 0x98-byte object; s = 8-byte aux (s->0x0 = &D_0000CAAC
 * descriptor, s->0x4 = 0). Each child = 0x18-byte sub-object:
 * child->0xC (12) type/vtable ptr (&D_0000C764), child->0x10 (16)
 * s32 = 0x1E (a kind/priority), child->0x14 (20) = 0; built via
 * func_00000000(child, o, val, 1) with val pulled from the global
 * table D_0000CAC0 / D_0000CAC4 / D_0000CAC8. The o != -0x8 /
 * -0x20 tests are defensive impossible-pointer guards. Caps <80:
 * get-or-create + alloc-cascade (~8 reloc) + defensive-dead
 * guards + &D descriptors + cross-symbol (func_0000CACC) ref.
 * Full body INCLUDE_ASM-preserved (.s = source of truth).
 * INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013D40);

void func_00013FE0(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x44) = a1;
    *(int*)(a0 + 0x5C) = a2;
}

void func_00013FEC(char *a0, int a1, int a2, int a3, int arg5) {
    *(int*)(a0 + 0x74) = a1;
    *(int*)(a0 + 0x8C) = a2;
    *(int*)(a0 + 0xA4) = a3;
    *(int*)(a0 + 0xBC) = arg5;
}

void func_00014004(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x104) = a1;
    *(int*)(a0 + 0x108) = a2;
}

/* func_00014010 - verified structural decode (0xB4, 45 insns,
 * in-place string substitution cipher).
 *   void func_00014010(char *a0) {
 *       char *s = a0 + 0xE4;                      // string field
 *       u32 n = strlen_like(s);                   // func_00000000(s)
 *       u32 i = 0;
 *       while (i < n) {
 *           unsigned char c = s[i];
 *           i++;
 *           if (c != 'a' && c != 'b' && c != ' ') // 0x61/0x62/0x20
 *               s[i-1] = (char)(0x69 - c);        // 'i' - c
 *           n = strlen_like(s);                   // recomputed each iter
 *       }
 *   }
 * Behavior: each character of the NUL-terminated string at a0+0xE4
 * (offset 0xE4 = 228) is mapped c -> ('i' - c) UNLESS it is one of
 * the passthrough chars 'a' (0x61), 'b' (0x62), or space (0x20),
 * which are left unchanged. The length is re-evaluated via the
 * reloc helper func_00000000 on every iteration (bound = current
 * strlen). Struct-typing reference: a0->0xE4 (228) = char[] name/id
 * string buffer. Caps <80: bnel branch-likely loop-back + reloc
 * func_00000000 strlen recompute as the loop bound + 4 char
 * constants ('a'/'b'/' '/'i') hoisted into s3-s6 (8-sreg pressure,
 * IDO global-allocator order-sensitive). Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014010);

/* func_000140C4 - verified structural decode (0x164, 89 insns,
 * 3-element draw/place dispatcher).
 *   void func_000140C4(St *s0) {
 *       f32 col[4] = {1,1,1,1};                   // sp+0x58
 *       if (s0->0x104) {                          // sub-object A
 *           draw_select(s0->0x104);
 *           n = (int)((f32)s0->0xDC * D_g);       // scaled count
 *           draw_set(s0->0x104, n, col, 0);
 *           draw_pos(s0->0x104, s0->0x44 + s0->0x74,
 *                               s0->0x5C + s0->0x8C, 0);
 *       }
 *       if (s0->0x108) {                          // sub-object B
 *           draw_select(s0->0x108);
 *           n = (int)((f32)s0->0xD8 * D_g);
 *           draw_set(s0->0x108, n, col, 0);
 *           draw_pos(s0->0x108, s0->0x44 + s0->0xA4,
 *                               s0->0x5C + s0->0xBC, 0);
 *       }
 *       draw_select(s0->0xE0);                     // sub-object C
 *       n = (int)((f32)s0->0xD8 * D_g);
 *       draw_set(s0->0xE0, n, &s0->0xC4, s0->0xD4);
 *       draw_pos(s0->0xE0, s0->0x44, s0->0x5C, &s0->0xE4);
 *   }
 * (draw_* = func_00000000 reloc helpers: select, set count+color,
 * set position.) Struct-typing reference: s0->0x104 (260) / 0x108
 * (264) / 0xE0 (224) = three drawable sub-object handles (A/B
 * optional, C unconditional). s0->0xDC (220) / 0xD8 (216) s32
 * counts scaled by a global f32 (D_g) and truncated to int.
 * Position = common base s0->0x44 (68) x / s0->0x5C (92) y plus
 * per-element offsets: A {0x74 (116), 0x8C (140)}, B {0xA4 (164),
 * 0xBC (188)}. Object C uses object-local params instead of the
 * shared col: s0->0xC4 (196) colour/param block, s0->0xD4 (212)
 * flag, s0->0xE4 (228) extra struct. col = const (1,1,1,1) RGBA.
 * Caps <80: FP cvt.s.w/mul.s/trunc.w.s scaled counts + &D global +
 * ~10 func_00000000 reloc + beql branch-likely on the optional
 * handles. Full body INCLUDE_ASM-preserved (.s = source of truth).
 * INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000140C4);

/* func_00014228 - verified structural decode (0x164, 89 insns).
 * INSTRUCTION-IDENTICAL TWIN of func_000140C4 (the 3-element
 * draw/place dispatcher) - same exact body, only the internal
 * branch-label addresses differ (a second copy of the same routine,
 * e.g. for a different render pass / mirrored layout). See
 * func_000140C4 for the full decode and field map:
 *   if (s0->0x104) { select; n=(int)((f32)s0->0xDC*D_g);
 *       set(n,col); pos(s0->0x44+0x74, s0->0x5C+0x8C); }
 *   if (s0->0x108) { select; n=(int)((f32)s0->0xD8*D_g);
 *       set(n,col); pos(s0->0x44+0xA4, s0->0x5C+0xBC); }
 *   select(s0->0xE0); n=(int)((f32)s0->0xD8*D_g);
 *   set(s0->0xE0,n,&s0->0xC4,s0->0xD4);
 *   pos(s0->0xE0,s0->0x44,s0->0x5C,&s0->0xE4);
 * Struct-typing reference: identical layout to func_000140C4 -
 * s0->0x104/0x108/0xE0 drawable handles, s0->0xDC/0xD8 scaled
 * counts (* global f32 D_g), s0->0x44/0x5C base position, per-elem
 * offsets {0x74,0x8C}/{0xA4,0xBC}, obj-C local params s0->0xC4/
 * 0xD4/0xE4, const (1,1,1,1) col. Caps <80: FP cvt.s.w/mul.s/
 * trunc.w.s + &D global + ~10 func_00000000 reloc + beql
 * branch-likely. Full body INCLUDE_ASM-preserved (.s = source of
 * truth). INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014228);

/* func_0001438C - verified structural decode (0x128, 74 insns,
 * get-or-create constructor + 2 child sub-objects).
 *   void *func_0001438C(void *a0) {
 *       o = a0;
 *       if (o == 0) { o = alloc(0x38); if (!o) return 0; }
 *       s1 = alloc(8);
 *       if (s1) {
 *           s1->0x0 = &func_0000CACC[0xC];        // fn/descriptor
 *           s1->0x4 = 0;
 *       }
 *       v = *(int*)(func_0000CAE8 + 4);
 *       if (o != (void*)-8) {                     // defensive guard
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);                 // func_00000000
 *               c->0xC  = &D_0000C83C;            // descriptor
 *               c->0x14 = 0;
 *               c->0x10 = 30.0f;                  // 0x41F00000
 *           }
 *       }
 *       v = *(int*)(func_0000CAE8 + 8);
 *       if (o != (void*)-0x20) {
 *           c = alloc(0x18);
 *           if (c) {
 *               init(c, o, v, 1);
 *               c->0xC  = &D_0000C83C;
 *               c->0x14 = 0;
 *               c->0x10 = 30.0f;
 *           }
 *       }
 *       return o;
 *   }
 * Struct-typing reference: o = 0x38-byte object (get-or-create).
 * s1 = 8-byte aux: s1->0x0 (0) fn/descriptor ptr (&func_0000CACC+
 * 0xC), s1->0x4 (4) = 0. child = 0x18-byte sub-object: child->0xC
 * (12) descriptor ptr (&D_0000C83C), child->0x10 (16) f32 = 30.0,
 * child->0x14 (20) = 0; built twice with values from the global
 * table func_0000CAE8+4 / +8. The `o != -8 / -0x20` tests are
 * defensive impossible-pointer guards (always true for real
 * objects). Caps <80: get-or-create + ~5 func_00000000 reloc
 * (alloc/init) + &D / cross-symbol descriptor relocs + FP 30.0
 * const + defensive-dead guards. Full body INCLUDE_ASM-preserved
 * (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap
 * rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001438C);

void func_000144B4(int *a0, int a1, int a2, float a3, float arg5) {
    *(float*)((char*)a0 + 0x44) = (float)a1;
    *(float*)((char*)a0 + 0x5C) = (float)a2;
    *(float*)((char*)a0 + 0x88) = a3;
    *(float*)((char*)a0 + 0x8C) = arg5;
}

void func_000144E0(void *a0, float a1, float a2) {
    *(float*)((char*)a0 + 0x88) = a1;
    *(float*)((char*)a0 + 0x8C) = a2;
}

/* func_000144F4 - verified structural decode (leaf, 43 insns, FP
 * physics integrator). Returns s32 (0 = running, 1 = clamped).
 *   s32 func_000144F4(void *a0, s32 a1) {
 *       s32 r = 0;
 *       f32 spd = a0->0xA8;                  // rate/accumulator
 *       if (spd < 16.0f)                     // ramp-up gate
 *           a0->0xA8 = (f32)((f64)spd + 0.5);// +0.5 via double promo
 *       spd = a0->0xA8;
 *       a0->0x5C = a0->0x5C + spd;           // integrate position
 *       pos = a0->0x5C;
 *       if ((f32)a1 < pos) {                 // exceeded int limit a1
 *           r = 1;
 *           if (6.0f < spd)                  // overspeed branch
 *               a0->0xA8 = -(spd / 4.0f);    // reverse + damp /4
 *           a0->0x5C = pos - spd;            // back off one step
 *       }
 *       return r;
 *   }
 * Struct-typing reference: a0->0xA8 (168) f32 rate/speed accumulator
 * (ramps by 0.5/frame until >=16.0, then constant), a0->0x5C (92) f32
 * integrated position; a1 = s32 limit (compared as float). On reaching
 * the limit: clamp position back one step, set return flag, and if
 * speed>6.0 reverse-and-damp speed to -(speed/4). Caps <80: bc1fl
 * branch-likely (x2) + cvt.d.s/add.d/cvt.s.d double-promotion of the
 * +0.5 literal add + c.lt.s operand-order. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144F4);

/* func_00014598 - verified structural decode (0xB4, 45 insns).
 * INSTRUCTION-IDENTICAL SIBLING of func_00014010 (the in-place
 * string substitution cipher); the ONLY difference is the string
 * field offset 0xB4 here vs 0xE4 there.
 *   void func_00014598(char *a0) {
 *       char *s = a0 + 0xB4;                      // string field (180)
 *       u32 i = 0, n = strlen_like(s);            // func_00000000(s)
 *       while (i < n) {
 *           unsigned char c = s[i]; i++;
 *           if (c != 'a' && c != 'b' && c != ' ') // 0x61/0x62/0x20
 *               s[i-1] = (char)(0x69 - c);        // 'i' - c
 *           n = strlen_like(s);                   // recomputed each iter
 *       }
 *   }
 * Struct-typing reference: a0->0xB4 (180) = char[] name/id string
 * buffer (the func_00014010 cipher applied to a different field; an
 * object with cipher-able strings at BOTH 0xB4 and 0xE4). Caps <80:
 * bnel branch-likely loop + reloc func_00000000 strlen-recompute
 * bound + 4 char constants hoisted s3-s6 (8-sreg, allocator order-
 * sensitive) - same as func_00014010. Full body INCLUDE_ASM-
 * preserved (.s = source of truth). INCLUDE_ASM (no episode;
 * tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014598);
