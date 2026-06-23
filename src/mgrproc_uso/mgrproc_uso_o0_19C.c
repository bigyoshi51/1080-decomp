#include "common.h"

/* Contiguous -O0 run [0x19C, 0xAE0) of the mgrproc_uso Yay0 block, carved into
 * a dedicated -O0 sub-unit (region 2) and concatenated with the -O2 objects
 * before crunch64 compression. See the mgrproc_uso_block1_yay0 rule in the
 * Makefile. func_000009A8 is byte-matched at -O0 (its D_0000014C store's %lo is
 * baked into the blob by scripts/bake-data-relocs.py); the rest are still
 * INCLUDE_ASM caps (NM bodies kept for objdiff scoring / grep). */

extern int gl_func_00000000();
extern int D_00000000;
extern int D_00000148;
extern int D_0000014C;

#define MGR_D_64 (*(int*)((char*)&D_00000000 + 0x64))
#define MGR_STATE_CODE (*(int*)((char*)&D_00000000 + 0x40))
#define MGR_D_44 (*(int*)((char*)&D_00000000 + 0x44))

#ifdef NON_MATCHING
/* 218-insn (0x368) jump-table state-machine dispatcher; 9 cases on a1, common
 * tail reloads a1 from D[0x40] and repeats while the sp[0x48] marker stays 0.
 * Won't byte-match (USO jump-table reloc shape); full decode scores ~37.9%. */
extern char D_a_4_x;
extern int D_b_4_x[];
extern char D_c_4_x;
extern char D_8_x;
mgrproc_uso_func_0000019C(a0, a1) char * a0; int a1; {
    volatile char *arg0 = a0;
    volatile int state = a1;
    volatile int loop_continue;
    int v0_save;
    int s0_save;
    loop_continue = 0;
    do {
        switch (state) {
            case 0:
                gl_func_00000000(arg0, 1, 0xB, 8);
                MGR_D_44 = 2;
                *(int*)((char*)&D_00000000 + 0x48) = 8;
                loop_continue = 1;
                break;
            case 1:
                gl_func_00000000(arg0, 1, 7, 4);
                MGR_D_44 = 2;
                *(int*)((char*)&D_00000000 + 0x48) = 8;
                loop_continue = 1;
                break;
            case 2:
                gl_func_00000000(arg0);
                MGR_STATE_CODE = 3;
                break;
            case 3:
                gl_func_00000000(arg0, *(int*)((char*)&D_00000000 + 0x68));
                MGR_STATE_CODE = 4;
                break;
            case 4: {
                int *p;
                int *q;
                gl_func_00000000(&D_a_4_x, D_b_4_x[1]);
                p = (int*)*(int**)((char*)arg0 + 8);
                q = p + p[1] * 1;
                MGR_D_64 = q[3];
                *(int*)((char*)&D_00000000 + 0x80) =
                    *(int*)((char*)&D_00000000 + 0x80) ^ 1;
                p = (int*)*(int**)((char*)arg0 + 8);
                q = p + p[1] * 1;
                *((char*)&D_00000000 + 0x17D) = (char)q[9];
                *((char*)&D_00000000 + 0x17F) =
                    (char)*(int*)((char*)&D_00000000 +
                                  ((unsigned char)*((char*)&D_00000000 + 0x17D) * 4) +
                                  0x90);
                gl_func_00000000(&D_c_4_x, 4, MGR_D_64, 0);
                gl_func_00000000(&D_c_4_x, MGR_D_64);
                v0_save = gl_func_00000000(arg0, *(int*)arg0, 1);
                s0_save = gl_func_00000000(0, 0x45000000, v0_save,
                                           *(int*)((char*)arg0 + 8),
                                           *(int*)arg0);
                gl_func_00000000(arg0, 0, s0_save);
                loop_continue = 1;
                break;
            }
            case 5: {
                int buf;
                int v0_local = gl_func_00000000(arg0, &buf);
                gl_func_00000000(arg0, (buf | 0x2000) | v0_local, 0x2000,
                                 *(int*)arg0);
                loop_continue = 1;
                break;
            }
            case 6:
                gl_func_00000000(arg0);
                MGR_STATE_CODE = 1;
                break;
            case 7:
                gl_func_00000000(arg0);
                MGR_STATE_CODE = 8;
                break;
            case 8: {
                int *s0_p = (int*)gl_func_00000000(0, 1, 0);
                gl_func_00000000((char*)&D_00000000 + 0x10, s0_p);
                if (s0_p[0x14 / 4] != 0) {
                    s0_p[1] = 1;
                }
                s0_p[0x14 / 4] = (int)&D_00000000;
                loop_continue = 1;
                break;
            }
            default:
                break;
        }
        state = MGR_STATE_CODE;
    } while (!loop_continue);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000019C);
#endif

/* 51-insn allocator+init wrapper, byte-matched at -O0. v3 is `register` (s0,
 * the target's callee-saved result reg); the dead `v3 = (int)&D_00000000`
 * reproduces the target's lui/addiu of &D in s0; the sentinel read uses the
 * direct int symbol D_00000000 for the $at-fused load. D_00000148/_0000014C are
 * fused stores/loads whose %lo bakes into the blob (bake-data-relocs). */
void mgrproc_uso_func_00000504(int *a0) {
    int v1;
    register int v3;
    v1 = gl_func_00000000(2);
    a0[2] = gl_func_00000000(0x3C);
    v3 = gl_func_00000000(0, D_00000148, -1, -1);
    a0[0] = v3;
    D_0000014C = v3;
    gl_func_00000000(v1);
    v3 = (int)&D_00000000;
    if (D_00000000 == 0x17D7) {
        *(int*)((char*)a0[0] + 0x14) = 1;
    } else {
        *(int*)((char*)a0[0] + 0x14) = 0;
    }
}

#ifdef NON_MATCHING
/* 76-insn (0x130) random-unique-ID assignment: fills 4 entries at
 * (a0->8)->[idx*4 + 0x24] with 4 unique random IDs in {0..4}. */
typedef float (*FloatFn)(void);
void mgrproc_uso_func_000005D0(char *a0) {
    int count = 0;
    int result = -1;
    int candidate;
    int idx;
    int *arr;

    while (count < 4) {
        while (result == -1) {
            candidate = ((int)(((FloatFn)gl_func_00000000)() *
                               *(float*)((char*)&D_00000000 + 0x24))
                         + *(int*)((char*)&D_00000000 + 0x4C) + 1) % 5;
            arr = *(int**)(a0 + 8);
            for (idx = 0; idx < count; idx++) {
                if (*(int*)((char*)arr + idx * 4 + 0x24) == candidate) break;
            }
            if (idx == count) {
                result = candidate;
            }
        }
        arr = *(int**)(a0 + 8);
        *(int*)((char*)arr + count * 4 + 0x24) = result;
        count++;
        result = -1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000005D0);
#endif

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00000700)();
void mgrproc_uso_func_00000700(char *arg0, s32 arg1) {
    *(int*)(FW(arg0, 0x8)) = 3;
    FW(FW(arg0, 0x8), 0x4) = 0;
    switch (arg1) {                                 /* irregular */
    case 1:
        if (*(s32 *)0xA0000284 == 0x240B17D7) {
            FW(FW(arg0, 0x8), 0x8) = 4;
        } else {
            FW(FW(arg0, 0x8), 0x8) = 3;
        }
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        mgrproc_uso_func_0000019C(arg0);
        break;
    case 2:
        FW(FW(arg0, 0x8), 0x8) = 5;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        mgrproc_uso_func_0000019C(arg0);
        FW(FW(arg0, 0x8), 0x34) = (s32) *(char *)0x4C;
        break;
    case 3:
        FW(FW(arg0, 0x8), 0x8) = 6;
        FW(FW(arg0, 0x8), 0xC) = 2;
        FW(FW(arg0, 0x8), 0x10) = 3;
        FW(FW(arg0, 0x8), 0x14) = 4;
        FW(FW(arg0, 0x8), 0x18) = 5;
        FW(FW(arg0, 0x8), 0x1C) = 6;
        FW(FW(arg0, 0x8), 0x20) = 7;
        mgrproc_uso_func_0000019C(arg0);
        FW(FW(arg0, 0x8), 0x34) = (s32) *(s32 *)0x4C;
        if (FW((*(char **)0x154), 0x2) == 3) {
            FW(FW(arg0, 0x8), 0x38) = 5;
        } else if (FW((*(char *)0x154), 0x2) == 4) {
            FW(FW(arg0, 0x8), 0x38) = 6;
        } else {
            FW(FW(arg0, 0x8), 0x38) = 7;
        }
        break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000700);
#endif

/* 27-insn -O0 cleanup wrapper, byte-matched at -O0. The `register int z=0`
 * lands in callee-saved s0 (the target's shared-zero reg); D_0000014C (defined
 * = 0x14C) gives the $at-fused `lui at; sw %lo(D_0000014C)(at)` store, whose
 * %lo (0x14c) is baked into the blob by scripts/bake-data-relocs.py. */
void mgrproc_uso_func_000009A8(int *a0) {
    register int z;
    gl_func_00000000(a0[2]);
    a0[2] = 0;
    gl_func_00000000(a0[0], 3);
    z = 0;
    a0[0] = z;
    D_0000014C = z;
}

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int import_000B574C();
extern int mgrproc_uso_D_01F97C();
extern int import_000AE5B0();
/* -O0 OR-accumulate loop. 14-diff NM (45/48 insns exact): the entire algorithm,
 * all 3 import jals, the do-while loop, and the prologue match. Levers applied:
 *   - imports called DIRECTLY (not via `((int(*)())import)()` casts) -> `jal`
 *     not `lui;addiu;jalr` (K&R-direct-call lever; saved 6 insns).
 *   - `register s32 r` -> the call result lands in callee-saved s0 (target's
 *     `move s0,v0; or t2,acc,s0`), and the -O0 stack layout (buf@48,count@44,
 *     acc@40,i@36) falls out of decl order.
 *   - `} while (++i < count)` (NOT `i++; } while(i<count)`) reuses the
 *     incremented i in the slt instead of reloading from the stack.
 * Residual (3 insns, coupled -O0 codegen): the tail reads buf[0] via an
 * address recompute (`addiu t,sp,48; lw 0(t)`) vs target's direct `lw 48(sp)`,
 * plus a trailing dead `b epilogue` (the -O0 inner-exit-branch pattern,
 * docs/PATTERNS.md "Inner return ... extra branch" — goto-out made it worse
 * here). Not landable until those 3 insns close. */
s32 mgrproc_uso_func_00000A14(s32 *arg0, s32 *arg1) {
    s32 buf[8];
    s32 count;
    s32 acc;
    s32 i;
    register s32 r;

    acc = 0;
    count = import_000B574C(*arg0);
    mgrproc_uso_D_01F97C(*arg0, &buf[0]);
    i = 0;
    if (count > 0)
        do {
            r = import_000AE5B0(buf[i]);
            acc |= r;
        } while (++i < count);
    *arg1 = buf[0];
    return acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000A14);
/* func_00000A14_pad (0xC trailing block-alignment zeros) is added by the
 * block1 yay0 concat rule's intermediate pad-to-0xAE0, not a GLOBAL_ASM here:
 * asm-processor rejects the 3-word pad block as "too short". */
#endif
