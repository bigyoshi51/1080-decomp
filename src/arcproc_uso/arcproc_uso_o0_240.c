#include "common.h"

extern int gl_func_00000000();
extern int D_arc240_A, D_arc240_B, D_arc240_C;
extern struct DArc {
    char _p40[0x40];
    int f40;
    int f44;
    int f48;
    char _p4c[0x64 - 0x4c];
    int f64;
} D_00000000;

/* -O0 donor for arcproc_uso_func_00000240 (226-insn / 0x388 11-way state-machine
 * dispatcher). VERIFIED BYTE-EXACT: isolated -O0 build = 226/226 words, 0 raw
 * mismatches vs the target .text (all gl_func_00000000 jals + D_arc240_A/B/C +
 * D_00000000 relocs resolve to address 0 in the static USO image, so the linked
 * .text bytes are identical). The .text codegen problem is SOLVED.
 *
 * LANDED 2026-07-10 as a normal C_FILES unit (NOT a REPLACE_FUNC_BODY splice).
 * The 11-way switch compiles a .rodata JUMPTABLE (R_MIPS_HI16/LO16 .text->.rodata
 * + 11x R_MIPS_32 .rodata->.text case labels). The USO ROM has the dispatch as raw
 * `lui at,0; lw at,0(at)` (both hi/lo fields ZERO -- the real table lives in the
 * baked arcproc.uso RoDataReloc in arcproc_uso_post, runtime-patched by the loader).
 * INFRA: pin this unit's .rodata NOLOAD at VMA 0x0 in tenshoe.ld
 * (.arcproc_uso_240_jtbl) so ld bakes %hi(0)=0 / %lo(0)=0 into the dispatch
 * (byte-exact) and emits ZERO ROM bytes for the compiled table (the _post bin is
 * untouched). This differs from bootup 10FEC, whose table offset 0xC20 is baked
 * into the lw %lo -> that one pins at VMA 0xC20. o0_240.c.o(.text) is pulled into
 * .arcproc_uso between o0_12C and tail1 at module offset 0x240 (TRUNCATE_TEXT
 * 0x388); tail1's TRUNCATE dropped 0x2740->0x23b8 since func_240 left it.
 * Verified: full make RUN_CC_CHECK=0, cmp tenshoe.z64 baserom.z64 byte-identical,
 * 226/226 words exact at ROM 0x5A6388.
 *
 * -O0 recipe (docs/IDO_CODEGEN.md -O0 dispatcher kit, sibling 019C):
 *  - Plain locals (v, done) declared BEFORE the register vars so the -O0 local
 *    column bases just below arg-home (v@sp+0x44, done@sp+0x40); register-first
 *    reserves dead words and drops the column to 0x34/0x38 (rule 1).
 *  - THREE fn-scope register vars, decl order = s0/s1/s2: r (reused gl result in
 *    cases 5/7/8/10), b1 (case-10 &D base), b2 (base+0x10 then base copy).
 *  - switch(a1) with a1 used DIRECTLY (no `state` local) and NO default: the
 *    switch emits the sltiu/beqz bound-check, out-of-range falls to the loop tail.
 *  - All D+offset globals via the extern struct member (D_00000000.f44) so IDO
 *    $at-fuses to lui+sw; the (char*)&D+off cast would emit lui+addiu+sw.
 *  - case 5: `((int**)a0)[2][((int**)a0)[2][1]+3]` — the INT** cast makes IDO -O0
 *    CSE the two identical a0[2] lvalue paths into one load (no named-q spill);
 *    the last call passes r (the 0x450000-call result), not v. */
void arcproc_uso_func_00000240(int a0, int a1) {
    int v;
    int done = 0;
    register int r;
    register int *b1;
    register int *b2;
    do {
        switch (a1) {
        case 0:
            gl_func_00000000(a0, 1, 3, 1);
            D_00000000.f44 = 3;
            D_00000000.f48 = 10;
            done = 1;
            break;
        case 1:
            gl_func_00000000(a0, 1, 3, 1);
            D_00000000.f44 = 4;
            D_00000000.f48 = 9;
            done = 1;
            break;
        case 2:
            gl_func_00000000(a0, 1, 3, 2);
            D_00000000.f44 = 4;
            D_00000000.f48 = 9;
            done = 1;
            break;
        case 3:
            gl_func_00000000(a0);
            D_00000000.f40 = 4;
            break;
        case 4:
            gl_func_00000000(a0);
            D_00000000.f40 = 5;
            break;
        case 5: {
            gl_func_00000000(&D_arc240_A, *(int *)((char *)&D_arc240_B + 4));
            D_00000000.f64 = ((int **)a0)[2][((int **)a0)[2][1] + 3];
            gl_func_00000000(&D_arc240_C, 4, D_00000000.f64, 3);
            v = gl_func_00000000(a0, ((int *)a0)[0], 1);
            r = gl_func_00000000(0, 0x450000, v, ((int *)a0)[2], ((int *)a0)[0]);
            gl_func_00000000(a0, 0, r);
            done = 1;
            break;
        }
        case 6:
            gl_func_00000000(a0, *(int *)a0);
            done = 1;
            break;
        case 7:
            r = gl_func_00000000(D_00000000.f64);
            gl_func_00000000(a0, (D_00000000.f64 | 0x8000) | r, 0x8000, ((int *)a0)[0]);
            done = 1;
            break;
        case 8:
            gl_func_00000000(&D_00000000, 7, 0, 0);
            r = gl_func_00000000(0);
            gl_func_00000000(a0, 1, r);
            done = 1;
            break;
        case 9:
            gl_func_00000000(a0);
            D_00000000.f40 = 10;
            break;
        case 10:
            r = gl_func_00000000(0, 1, 0);
            b1 = (int *)&D_00000000;
            b2 = b1 + 4;
            gl_func_00000000(b2, r);
            if (((int *)r)[0x14 / 4] != 0) {
                ((int *)r)[0x4 / 4] = 1;
            }
            b2 = b1;
            ((int *)r)[0x14 / 4] = (int)b2;
            done = 1;
            break;
        }
        a1 = D_00000000.f40;
    } while (done == 0);
}
