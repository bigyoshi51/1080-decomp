#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000000);

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
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000400);


void timproc_uso_b5_func_00000470(void) {
}


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000478);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000778);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000010EC);

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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003ED8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F18);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003F5C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003FA8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003FF8);

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

#ifdef NON_MATCHING
/* 97.5 % match. Indirect-call wrapper:
 *   p1 = a0->0x2C; p2 = p1->0x28;
 *   ((fn*)p2->0x5C)(p2->0x58_short + p1);
 *
 * Remaining 2.5 %: $v0/$v1 reg-swap on the p1/p2 named locals (mine
 * v0=p1,v1=p2 vs target v1=p1,v0=p2). Inlining all derefs to remove the
 * named locals regressed (97.08 %) due to extra reload of a0->0x2C.
 * Pure regalloc swap; not C-controllable. */
void timproc_uso_b5_func_00008F98(char *a0) {
    int p1 = *(int*)(a0 + 0x2C);
    int *p2 = *(int**)((char*)p1 + 0x28);
    (*(int(**)())((char*)p2 + 0x5C))(*(short*)((char*)p2 + 0x58) + p1);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008F98);
#endif


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008FC8);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A97C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000A9EC);

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


INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AAF4);


#ifdef NON_MATCHING
/* 89.3 % match (2026-05-02, up from 83 %). Logic-fix: prior wrap read/wrote
 * through `q` (the 2nd jal's return), but the asm uses $a1 = r
 * (= arg0->0x40) for the post-jal stores. The 2nd gl_func_00000000 return
 * value is unused. Adding `char pad[8]` coerces frame 0x20 -> 0x28
 * (target spills a0 to caller's outgoing slot at sp+0x28).
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
 * arg/scratch reg for cross-jal preserve isn't C-controllable. */
void *timproc_uso_b5_func_0000AB24(void *arg0) {
    char pad[8];
    void *p;
    void *r;

    p = (void*)gl_func_00000000(0x40);
    if (p != 0) {
        gl_func_00000000(p);
        *(void**)((char*)p + 0x28) = (void*)&D_00000000;
        *(int*)((char*)p + 0x3C) = 0;
    }
    r = *(void**)((char*)arg0 + 0x40);
    if (r != 0) {
        gl_func_00000000((char*)p + 0x10, r);
        if (*(int*)((char*)r + 0x14) != 0) {
            *(int*)((char*)r + 0x4) = 1;
        }
        *(void**)((char*)r + 0x14) = p;
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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B9F0);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BA60);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BAE8);

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

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CE6C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CEB4);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D06C);

INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D0DC);

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

