#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000139B0);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000140C4);

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
