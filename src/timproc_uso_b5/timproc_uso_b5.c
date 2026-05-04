#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

extern char D_b5_0_a;
extern char D_b5_0_b;
extern char D_b5_0_c;
void timproc_uso_b5_func_00000000(void) {
    *(int*)((char*)&D_b5_0_b + 0x64) = (*(int**)&D_b5_0_a)[0x1F];
    gl_func_00000000(*(int*)((char*)&D_b5_0_c + 0x4), -1, 0);
}

void timproc_uso_b5_func_00000040(void) {
}


void timproc_uso_b5_func_00000048(void) {
}


void timproc_uso_b5_func_00000050(void) {
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000058);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000024C);
#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000024C_pad.s")

void timproc_uso_b5_func_00000330(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}


void timproc_uso_b5_func_0000036C(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}


void timproc_uso_b5_func_000003A8(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}


typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void timproc_uso_b5_func_00000400(Vec3 *dst) {
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


void timproc_uso_b5_func_00000470(void) {
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000478);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000778);

int timproc_uso_b5_func_000010EC(int a0) {
    if (a0 != 0) goto init;
    a0 = gl_func_00000000(0x40);
    if (a0 == 0) goto end;
init:
    gl_func_00000000(a0, (char*)&D_00000000 + 0x106C);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x0C) = (int)((char*)&D_00000000 + 0x1074);
    *(int*)((char*)a0 + 0x38) = 0;
    *(int*)((char*)a0 + 0x3C) = 0;
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x2C) = 1;
end:
    return a0;
}

void timproc_uso_b5_func_00000000();

void timproc_uso_b5_func_0000115C(int *a0) {
    *(int*)((char*)a0 + 0x34) = 0;
    gl_func_00000000(a0);
}


#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000117C — 104 insns / 0x1A0.
 * State-toggle / dual-side flag operation. a0 has a counter at 0x34
 * indexing two slots at 0x38 and 0x3C (a0[0x34] selects active side,
 * `^1` toggles to other). Each slot stores a struct ptr; the struct
 * has flags at +0x40C->0x38+0x18 (bit 4 = side-active mask).
 *
 * Pattern (decoded from 0x117C-0x1318):
 *   1. Call gl_func_00000000(a0->0x38[count])     — call A on active side
 *   2. Call gl_func_00000000(a0->0x38[count])     — call B (same arg again)
 *   3. mask = 1 << count
 *   4. flag = active_side->0x41C->0x50
 *   5. if (flag & mask):
 *        if (a0->0x2C != 0): clear bit 4 on OTHER side; OR-4 active side
 *        else:                 clear bit 4 on active side; clear bit 4 on other
 *        gl_func_00000000(a0)                     — call C
 *   6. else: OR-4 on active side; clear bit 4 on other side
 *   7. count++; a0->0x34 = count;
 *
 * Field offsets identified (for future struct typing):
 *   a0->0x2C: dispatch-mode flag (controls clear-vs-set behavior)
 *   a0->0x34: side counter (0 or 1; flips by ^1)
 *   a0->0x38, 0x3C: slot pointers (two struct refs)
 *   slot->0x40C: child struct pointer
 *   child->0x38: another struct
 *   that_struct[6] (offset 0x18): flags word (bit 2 = OR-4 mask)
 *   slot->0x41C->0x50: flag table indexed by `1 << count`
 *
 * Logic decoded but not byte-matched this pass — needs typed struct
 * to clean up the *(int*)((char*)+offset) chains. */
void timproc_uso_b5_func_0000117C(int *a0) {
    int v;
    int *slot;
    int *other;
    int *child;
    int *flags;

    v = *(int*)((char*)a0 + 0x34);
    gl_func_00000000(*(int*)((char*)a0 + v*4 + 0x38));
    v = *(int*)((char*)a0 + 0x34);
    gl_func_00000000(*(int*)((char*)a0 + v*4 + 0x38));
    v = *(int*)((char*)a0 + 0x34);
    slot = *(int**)((char*)a0 + v*4 + 0x38);
    if ((*(int*)(*(int*)((char*)slot + 0x41C) + 0x50) & (1 << v)) != 0) {
        if (*(int*)((char*)a0 + 0x2C) != 0) {
            child = *(int**)((char*)slot + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags | 4;
            other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
            if (other != 0) {
                child = *(int**)((char*)other + 0x40C);
                flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
                *flags = *flags & -5;
            }
        } else {
            child = *(int**)((char*)slot + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags & -5;
            other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
            if (other != 0) {
                child = *(int**)((char*)other + 0x40C);
                flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
                *flags = *flags & -5;
            }
        }
        gl_func_00000000(a0);
    } else {
        child = *(int**)((char*)slot + 0x40C);
        flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
        *flags = *flags | 4;
        v = *(int*)((char*)a0 + 0x34);
        other = *(int**)((char*)a0 + (v ^ 1)*4 + 0x38);
        if (other != 0) {
            child = *(int**)((char*)other + 0x40C);
            flags = (int*)((char*)*(int**)((char*)child + 0x38) + 0x18);
            *flags = *flags & -5;
        }
    }
    *(int*)((char*)a0 + 0x34) = *(int*)((char*)a0 + 0x34) + 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000117C);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000131C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001460);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001658);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000018B4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001C08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001F14);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000027B0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000283C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00002B74);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000032C8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000038D0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000398C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003A4C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003C8C);

void timproc_uso_b5_func_00003ED8(char *a0) {
    char *v;

    gl_func_00000000(a0 + 0x2C);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}

#ifdef NON_MATCHING
/* Sibling of timproc_uso_b5_func_00003ED8 — same vtable-call wrapper:
 *   gl_func_00000000(a0 + 0x194);     // first call (offset 0x194 vs ED8's 0x2C)
 *   v = a0->vtable;                    // a0+0x28
 *   (*(v->fp))(a0 + v->off);          // dispatch
 *
 * BLOCKED: trailing `lw t8, 0x23C(a0)` at offset 0x40 is the stolen
 * prologue for SUCCESSOR func_00003F5C. Standard pad-sidecar recipe
 * (trim .s to 0x40 + emit 4-byte _pad.s with the lw) doesn't work here:
 * asm-processor aligns the next function to 8 bytes, padding with an
 * extra nop AFTER the 4-byte pad — shifts func_00003F5C from baserom's
 * 0x3F5C to 0x3F60. Pad-sidecar mechanism naturally handles 8-byte
 * (lui+addiu/lw) prologue prefixes but not 4-byte single insns. Keep
 * INCLUDE_ASM until 00003F5C is decompiled with PROLOGUE_STEALS=4. */
void timproc_uso_b5_func_00003F18(char *a0) {
    char *v;
    gl_func_00000000(a0 + 0x194);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F18);
#endif

#ifdef NON_MATCHING
/* 19-insn (0x4C) function — main body 17 insns + 8-byte bundled trailer.
 *
 * Main body (offsets 0..0x44): structured Vec3-or-buf copy.
 *   - Loads a0->_29C → v0; offsets to v += 0xDC
 *   - Stores 3 t-regs at sp+0xC..0x14 (forms a stack buf)
 *   - Reloads as floats (lwc1 f4/f6/f8) and stores at v+0..v+8 (3 floats)
 *   - jr ra with swc1 f8 in delay slot
 *   The first `sw t8, 0(t6)` at insn 4 stores $t8 BEFORE the function
 *   loads $t8 (insn 8 lw t8, 0x244(a0)) — IDO has scheduled the store
 *   to fill the load-delay slot, but the source $t8 is the CALLER's
 *   pre-call value, not the soon-to-be-loaded value. Hard to express
 *   from C without extracting the source pattern.
 *
 * Bundled trailer (offsets 0x44/0x48): `jr ra; sw a0, 0(sp)` — trampoline
 * leaf that saves a0 to caller-slot then returns. Not analyzable here.
 *
 * Promotion path: needs SUFFIX_BYTES = 0x03e00008,0xafa40000 + a clean
 * C body for the main function. The t8-uninitialized issue may resolve
 * via a different parameter shape (function takes (a0, a1=t8?) directly).
 * Defer — multi-tick decomp. */
void timproc_uso_b5_func_00003F5C(int *a0);
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F5C);
#endif

void timproc_uso_b5_func_00003FA8(int a0, int a1, int a2, int a3) {
    (void)a0;
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a3);
    gl_func_00000000(a3, a1, a2, 0);
}

void timproc_uso_b5_func_00003FF8(int arg1, int arg2, int arg3, int arg4, int arg5) {
    float buf[4];
    char pad[20];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    gl_func_00000000(&D_00000000, arg5, buf, arg4);
    gl_func_00000000(arg4);
    gl_func_00000000(arg4, arg2, arg3, 3);
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004068);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000040BC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004118);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005BF0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005FC0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006394);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000685C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006900);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000069E8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006C00);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006D30);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006E08);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007078);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000072D0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007430);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000077D8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000079A4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007B2C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007E34);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000080F4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008468);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000085E0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008688);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000894C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008AFC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008C44);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008DB4);

/* Indirect-call wrapper: p1 = a0->0x2C; p2 = p1->0x28;
 * ((void(*)(int))p2->0x5C)(p2->0x58_short + p1).
 * 97.5% from C alone; pure $v0/$v1 swap on (p1,p2) — IDO assigns p1=$v0
 * but target wants $v1. Promoted to 100% via INSN_PATCH per
 * feedback_insn_patch_for_ido_codegen_caps.md (4-word patch swapping
 * v0/v1 in 4 dependent insns). */
void timproc_uso_b5_func_00008F98(char *a0) {
    int p1 = *(int*)(a0 + 0x2C);
    int *p2 = *(int**)((char*)p1 + 0x28);
    (*(int(**)())((char*)p2 + 0x5C))(*(short*)((char*)p2 + 0x58) + p1);
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008FC8);

#ifdef NON_MATCHING
/* 72.21% NM. 23-insn loop with branch-likely preload (bnezl at 0x50 with delay-slot
 * `lw v1, 0x40(s2)` preloading v1 for next iteration's body at 0x2C).
 *
 * Logic: for i in [0, a0->0x3C): call (a0->0x40)->0x28->0x4C as fn ptr,
 * arg = (signed short)(a0->0x40)->0x28->0x48 + (a0->0x40). Plus an
 * unused $s1 pointer that increments by 4 per iteration (dead but live
 * in IDO's view).
 *
 * Cap likely structural: the branch-likely with off-loop-body delay-slot
 * preload isn't reachable from std do-while C. The loop body at 0x2C
 * starts WITHOUT a lw v1 — it's pre-loaded by the previous iteration's
 * branch-likely delay slot (or by the initial lw at 0x28). */
void timproc_uso_b5_func_0000A97C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x40);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A97C);
#endif

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of timproc_uso_b5_func_0000A97C — same 23-insn loop with branch-
 * likely preload of v1 in bnezl delay slot. Different offsets:
 *   A97C: fn_ptr at slot->0x28->0x4C, short_arg at slot->0x28->0x48
 *   A9EC: fn_ptr at slot->0x28->0x64, short_arg at slot->0x28->0x60
 * Same structural cap — branch-likely w/ off-loop-body delay slot preload
 * not reachable from std do-while C. */
void timproc_uso_b5_func_0000A9EC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x40);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x64))(*(short*)((char*)v0 + 0x60) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A9EC);
#endif

void timproc_uso_b5_func_0000AA5C(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000330((int*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AA8C(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_0000036C((float*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AABC(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_000003A8((Quad4*)(a0 + 0x10));
}


void timproc_uso_b5_func_0000AAEC(int a0) {
}


void timproc_uso_b5_func_0000AAF4(char *a0) {
    int tmp;
    timproc_uso_b5_func_00000330(&tmp);
    timproc_uso_b5_func_00000400((Vec3*)(a0 + 0x10));
}


#ifdef NON_MATCHING
/* 89.3 % match. Previously NOTE was inverted: re-decoded 2026-05-02 the
 * post-jal stores DO use the 2nd jal's return value (call result spilled
 * to sp+0x20, reloaded as $a1 then used for q->0x14 / q->0x4 / q->0x14
 * stores). r (= arg0->0x40) is only used as the 2nd jal's a1-arg.
 * Adding `char pad[8]` coerces frame 0x20 -> 0x28 (target spills a0 to
 * caller's outgoing slot at sp+0x28).
 *
 * Remaining diffs (register-allocation flip):
 * - Target uses $a0 throughout the 1st init block (no scratch copy), then
 *   explicitly `or v1, a0, zero` to move p to $v1 right before the 2nd jal.
 *   Our build pre-allocates p to $a2 right after the 1st jal returns
 *   (extra `or a2, v0, zero` insertion + uses $a2 throughout). $v1 home
 *   for cross-jal preservation isn't reachable from C — IDO won't pick the
 *   v0/return-low register as a long-lived hold reg.
 * - Spill slot offsets: target 0x1C/0x20/0x24, ours 0x1C/0x18 (only 2
 *   distinct slots; not enough variables to need 3).
 * - Final beq vs beql: target `beq v0,zero,+0xC` then `or a1,v0,zero`
 *   delay-slot; ours `beql a1,zero,...` with epilogue-load delay-fill
 *   (because we named `r` as a local, IDO promotes it to a1 early).
 *
 * These are all knock-on from the same root: IDO's register allocator
 * picks $a2 instead of $a0/$v1 for p's hold-across-2nd-jal slot. Same
 * structural cap as `feedback_ido_arg_save_reg_pick.md` — the choice of
 * arg/scratch reg for cross-jal preserve isn't C-controllable.
 *
 * 2026-05-04: re-tested for INSN_PATCH eligibility. Built emits 34 insns,
 * expected has 36 — a 2-insn deficit (built lacks the `or v1, a0, zero`
 * + an extra spill-store). Per feedback_insn_patch_size_diff_blocked.md
 * INSN_PATCH alone can't fix this. Promotion needs a sibling
 * inject-insn-at.py recipe OR a different C shape that emits the extra
 * `or v1,a0` move. Deferred. */
void *timproc_uso_b5_func_0000AB24(void *arg0) {
    char pad[8];
    void *p;
    void *r;
    void *q;

    p = (void*)gl_func_00000000(0x40);
    if (p != 0) {
        gl_func_00000000(p);
        *(void**)((char*)p + 0x28) = (void*)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
    }
    r = *(void**)((char*)arg0 + 0x40);
    if (r != 0) {
        q = (void*)gl_func_00000000((char*)p + 0x10, r);
        if (*(int*)((char*)q + 0x14) != 0) {
            *(int*)((char*)q + 0x4) = 1;
        }
        *(void**)((char*)q + 0x14) = p;
    }
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AB24);
#endif

void timproc_uso_b5_func_0000ABB4(int *a0) {
    *(int*)((char*)a0 + 0xB0) = 1;
    *(int*)((char*)a0 + 0x64) = -1000;
}

void timproc_uso_b5_func_0000ABC8(int a0, int a1) {
}


void timproc_uso_b5_func_0000ABD4(int a0, int a1) {
}

void timproc_uso_b5_func_0000ABE0(int a0, int a1, int a2, int a3) {
}

void timproc_uso_b5_func_0000ABF4(int a0, int a1, int a2) {
}


void timproc_uso_b5_func_0000AC04(int a0, int a1) {
}

void timproc_uso_b5_func_0000AC10(int a0, int a1, int a2) {
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AC20);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B154);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B368);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B624);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B928);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B98C);

void timproc_uso_b5_func_0000B9F0(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 2, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = 2;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0x10;
}

void timproc_uso_b5_func_0000BA60(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 0, 2, 2, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 1;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0;
    *(int*)((char*)a0 + 0x2BC) = 0;
    *(int*)((char*)a0 + 0x2C0) = 2;
}

void timproc_uso_b5_func_0000BAE8(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 2, 1, 1);
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 0x20;
}

void timproc_uso_b5_func_0000BB44(int *a0) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x138) = 0;
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x144) = 8;
}

void timproc_uso_b5_func_0000BB5C(int a0) {
}

void timproc_uso_b5_func_0000BB64(int *a0, int unused) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x13C) = 1;
}

void timproc_uso_b5_func_0000BB78(int *a0, int unused) {
    *(int*)((char*)(int*)a0[0x2B8/4] + 0x13C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BB88);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BBDC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDA0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDEC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C1B4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C208);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C2C0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C310);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C8AC);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C98C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CC74);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CCC8);

/* 4-float load-batched store + jal. Was 97.2% NM (8-insn float
 * register-renumbering cap). Promoted via INSN_PATCH per
 * feedback_insn_patch_for_ido_codegen_caps.md (and SUFFIX_BYTES for
 * trailing prologue-stolen-PREDECESSOR pattern). */
void timproc_uso_b5_func_0000CE6C(char *a0) {
    char *v;
    float a, b, c, d;
    v = *(char**)(a0 + 0x2B8);
    a = *(float*)(a0 + 0x294);
    b = *(float*)(a0 + 0x264);
    c = *(float*)(a0 + 0x260);
    d = *(float*)(a0 + 0x25C);
    *(float*)(v + 0x118) = a;
    *(float*)(v + 0x10C) = b;
    *(float*)(v + 0x114) = c;
    *(float*)(v + 0x110) = d;
    gl_func_00000000();
}

#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000CE6C_pad.s")

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CEB4);

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of A97C/A9EC family — same 23-insn loop with branch-likely
 * preload structural cap. Different outer offsets (this variant):
 *   count: a0->0x6C (was a0->0x3C in A97C)
 *   slot ptr: a0->0x3C (was a0->0x40 in A97C)
 *   fn ptr at slot->0x28->0x4C, short arg at slot->0x28->0x48 (same as A97C)
 * Same do-while + branch-likely-preload cap. */
void timproc_uso_b5_func_0000D06C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x3C);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D06C);
#endif

#ifdef NON_MATCHING
/* 72.21% NM. Sibling of A97C/A9EC/D06C — same 23-insn loop with branch-likely
 * preload cap. Outer offsets same as D06C (count=a0->0x6C, slot=a0->0x3C);
 * inner offsets fn ptr=slot->0x28->0xE4, short arg=slot->0x28->0xE0
 * (vs D06C's 0x4C/0x48). */
void timproc_uso_b5_func_0000D0DC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    p = a0;
    i = 0;
    do {
        v1 = *(int**)(a0 + 0x3C);
        v0 = *(int**)((char*)v1 + 0x28);
        (*(int(**)())((char*)v0 + 0xE4))(*(short*)((char*)v0 + 0xE0) + (int)v1);
        i++;
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D0DC);
#endif

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D14C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D550);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D884);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000DF14);

void timproc_uso_b5_func_0000E5AC(int a0) {
    *(int*)&D_00000000 = 0;
    gl_func_00000000(a0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000E5AC_pad.s")

#ifdef NON_MATCHING
/* Prologue-stolen successor (per E5AC's _pad.s): the 2-insn `lui v0;
 * lw v0, 0(v0)` preceding E5D8 sets v0 = *D_00000000 (a state pointer).
 * Body chains: copies 3 floats from `(*D_0)->0x70`'s fields (0xBC, 0xCC,
 * 0xDC) into D_0+0/+4/+8, then calls gl_func_00000000(a0).
 *
 * IDO emit produces 2 extra setup insns (lui+lw to load *D_0) at the
 * start of E5D8 which the stolen prologue already provides. Standard
 * PROLOGUE_STEALS=8 recipe applies but needs Makefile entry — deferring.
 * NM wrap captures the structure for next pass. */
void timproc_uso_b5_func_0000E5D8(int a0) {
    *(float*)((char*)&D_00000000 + 0) = *(float*)((char*)*(int**)((char*)*(int**)&D_00000000 + 0x70) + 0xBC);
    *(float*)((char*)&D_00000000 + 4) = *(float*)((char*)*(int**)((char*)*(int**)&D_00000000 + 0x70) + 0xCC);
    *(float*)((char*)&D_00000000 + 8) = *(float*)((char*)*(int**)((char*)*(int**)&D_00000000 + 0x70) + 0xDC);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000E5D8);
#endif

