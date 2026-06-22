#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern char D_titproc_15F4_tmp;
extern char titproc_uso_D_00048C, titproc_uso_D_000194, import_00073B18;
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

extern char import_00020098;       /* a1 base (D[0x6C], D[0x148], D[0x40], D[0x44]) */
extern int titproc_uso_D_0000EC[]; /* t3-base table */
extern int titproc_uso_D_000100[]; /* v0-base table (return value) */
extern int titproc_uso_func_01EEE4();

#ifdef NON_MATCHING
/* SOURCE=1 refinement (2026-06-01): use a K&R dummy parameter for `counter`.
 * IDO colors the live state counter to $a0 through the branch-likely tests and
 * final table index, matching the target's main register choice better than a
 * plain local (which stayed in $v1).
 *
 * SOURCE=1 re-audit 2026-06-01: align the NM body's symbol names with the
 * target relocs (`import_00020098`, `titproc_uso_func_01EEE4`,
 * `titproc_uso_D_0000EC`, `titproc_uso_D_000100`). Objdiff's reloc-aware
 * score remains 98.13725%, but no-alias objdump now shows the same callee/table
 * names as expected. Residual is temp-register coloring around the initial
 * load/increments and final table-base load. Negative probes: splitting the
 * initial `D+0x6C` load into `raw` moved it to `$v1` instead of target `$t6`;
 * naming the final constant `four` compiled identically; a single
 * `char *s = &import_00020098` base pointer REGRESSES (+7 insns — `s` must
 * survive the two calls so it spills, rather than the target's per-access
 * reload). Keep the inline-macro form. Still NM. */
int titproc_uso_func_000000C0(counter)
    int counter;
{
    int v;

    counter = *(int*)((char*)&import_00020098 + 0x6C) + 1;
    *(int*)((char*)&import_00020098 + 0x6C) = counter;
    if (counter >= 5) {
        *(int*)((char*)&import_00020098 + 0x6C) = 0;
        counter = 0;
    }

    if (counter == 0) {
        v = titproc_uso_func_01EEE4(*(int*)((char*)&import_00020098 + 0x148) + 4);
        if (v != 2) {
            *(int*)((char*)&import_00020098 + 0x6C) =
                *(int*)((char*)&import_00020098 + 0x6C) + 1;
        }
        counter = *(int*)((char*)&import_00020098 + 0x6C);
    }
    if (counter == 1) {
        v = titproc_uso_func_01EEE4(*(int*)((char*)&import_00020098 + 0x148) + 4);
        if (v != 1) {
            *(int*)((char*)&import_00020098 + 0x6C) =
                *(int*)((char*)&import_00020098 + 0x6C) + 1;
        }
        counter = *(int*)((char*)&import_00020098 + 0x6C);
    }

    *(int*)((char*)&import_00020098 + 0x40) = 4;
    *(int*)((char*)&import_00020098 + 0x44) = titproc_uso_D_0000EC[counter];
    return titproc_uso_D_000100[counter];
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000000C0);
#endif
extern char D_00000194_A;
/* State-setter sibling of 000001E4/00000230/0000028C. MATCHED via pad-sidecar
 * boundary correction (replacing the banned PROLOGUE_STEALS/SUFFIX_BYTES): the
 * leading `lui v0,0; addiu v0,0` (&D_00000000 base for the 0x34/0x40/0x13C
 * stores) was emitted as predecessor 0xC0's pad sidecar; moved into this fn's
 * .s (0x48->0x50, starts 0x18C) and removed the pad pragma+.s. (The 0x1E4
 * orphan lives in the separate func_000001DC.s, fixed when 0x1E4 lands.) */
void titproc_uso_func_00000194(void) {
    *(int*)((char*)&D_00000000 + 0x34) = 3;
    *(int*)((char*)&D_00000000 + 0x40) = 0;
    *(int*)((char*)&D_00000000 + 0x13C) = 3;
    gl_func_00000000(0xC, 0);
    gl_func_00000000(*(int*)((char*)&D_00000194_A + 0xA8), -1, 0);
}

extern char D_000001E4_A;

/* MATCHED via pad-sidecar/orphan boundary correction: leading `lui v0,0; addiu
 * v0,0` (&D base) was the separate fake-fn func_000001DC; merged into this fn's
 * .s (0x4C->0x54, starts 0x1DC), orphan-fn + its INCLUDE_ASM removed. */
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

/* MATCHED 2026-05-28 (boundary fix): the .s was mislocated 8 bytes late as
 * "0000028C", dropping the `lui v0; addiu v0` &D base-load at 0x284..0x288
 * into an uncovered gap (prologue-stolen successor). Renamed to the true
 * entry 00000284 + restored the prefix words; the C (mirror of matched
 * sibling 00000230) then matches. */
void titproc_uso_func_00000284(void) {
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

/* titproc_uso_func_00000418: 33-insn FP selector + scaled return.
 *
 * D[0x154] is a pointer to a u16 mask. The target loads the pointer before
 * the stack prologue, then keeps the u16 mask in v1 for the loop. For each
 * set low bit, a1 becomes the 1-based bit index; after the loop it calls
 * gl_func_00000000(8), treats f0 as the float return, and scales by a1 - 2.
 *
 * NATURAL CEILING via the no-arg placeholder (direct jal, f0 return).
 * Use target-named externs in the NM body so reloc names match expected.
 * The remaining frame-slot / scheduling codegen cap was
 * previously closed via INSN_PATCH — INSN_PATCH REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default build is INCLUDE_ASM. */
extern char import_00020098;
extern float titproc_uso_func_075EE4();
/* permuter crack 2026-06-18: the no-op `if (!selected) {}` forces the
 * uninitialized-`selected` preload (lw $5,24(sp)) to be scheduled ahead of
 * `index=0` (or $2,$0,$0), matching the target's order and resolving the
 * documented 2-diff scheduler swap (the 97k-iter run that "could not move
 * it" used the cached-mask shape; this is the inlined-mask + early-read form). */
int titproc_uso_func_00000418(void) {
    int index = 0;
    int selected;

    if (!selected) {
    }
    do {
        if ((**(unsigned short**)((char*)&import_00020098 + 0x154) & (1 << index)) != 0) {
            selected = index + 1;
        }
        index++;
    } while (index != 8);

    selected -= 2;
    return (int)((titproc_uso_func_075EE4() * (float)selected) + 2.0f);
}

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

/* titproc_uso_func_000005DC: 356-insn do-while + 12-case jr-table state machine.
 * Reconstructed 2026-06-22. D base (`import_00020098`) is HELD in s0 across the
 * whole function (and d16 = &D+0x10 in s8) — the target reloads neither, so the
 * two base pointers must be single locals that survive every call (callee-saved
 * coloring). `s5v` is a persistent cross-case local read from sp+92 at entry and
 * written back at epilogue (uninitialized stack-resident state). Jumptable reloc
 * is `import_00263E00`; objdiff scores .text only so the generated .rodata table
 * is harmless. Callees use the real intra-USO `titproc_uso_func_*` symbols.
 * LOGIC COMPLETE: jal call sequence is byte-identical to target (53/53 R_MIPS_26
 * relocs in order). RESIDUAL is the held-base allocator cap: the target keeps
 * `&import_00020098` in saved $s0 and emits `sw X,K($s0)` per field store (form b,
 * IDO_CODEGEN "&D+const folds to held base"), but our -O2 build re-materializes
 * `lui $at,%hi(import_00020098); sw X,%lo($at)` per store (form a) at ~24 sites —
 * the address-fold-vs-CSE allocator coin-flip documented as the SKIP class
 * (IDO_CODEGEN: "neither form is C-forceable; do NOT grind decl-order /
 * struct-wrap / pointer-hoist"). Compounded with s0/s1/s2 coloring + the s5v
 * spill-slot offset, this leaves a +15-insn frame/coloring gap. Stays NM. */
extern int titproc_uso_func_0120A8();
extern int titproc_uso_func_0027E8();
extern int titproc_uso_func_000C54();
extern int titproc_uso_func_01DA48();
extern int titproc_uso_func_000B6C();
extern int titproc_uso_func_000C0C();
extern int titproc_uso_func_000418();
extern int titproc_uso_func_011CD8();
extern int titproc_uso_func_001E9C();
extern int titproc_uso_func_01EF10();
extern int titproc_uso_func_01EF44();
extern int titproc_uso_func_01EF94();
extern int titproc_uso_func_01EFC8();
extern int import_000B3268();

#ifdef NON_MATCHING
void titproc_uso_func_000005DC(char *a0, int a1) {
    char *d = (char *)&import_00020098;
    char *d16 = d + 0x10;
    char *arg = a0;
    int done = 0;
    int one = 1;
    int s5v;
    do {
        if ((unsigned int)a1 < 12) {
            switch (a1) {
            case 0: {
                int *sub;
                titproc_uso_func_0120A8(d, 0, 0, 0);
                done = 1;
                *(int *)(d + 0x68) = 0;
                *(int *)(d + 0x8C) = 0x820000;
                sub = (int *)titproc_uso_func_0027E8(d, 2, 9, one);
                titproc_uso_func_07ACE0(d16);
                if (*(int *)((char *)sub + 0x14) != 0) {
                    *(int *)((char *)sub + 0x4) = one;
                }
                titproc_uso_func_000C54(0, sub);
                *(int *)((char *)sub + 0x14) = (int)d;
                titproc_uso_func_01DA48(arg, 0);
                break;
            }
            case 1:
                titproc_uso_func_000B6C(arg, -1);
                done = 1;
                import_000B3268(arg, 0x9FFF0, 0x10000, *(int *)arg);
                *(int *)(d + 0x44) = 2;
                break;
            case 2:
                titproc_uso_func_000C0C(arg);
                *(int *)(d + 0x40) = 0;
                break;
            case 3: {
                int a4 = *(int *)(d + 0x44);
                *(int *)(d + 0x44) = 0;
                s5v = 0x800000;
                *(int *)(d + 0x40) = a4;
                break;
            }
            case 4: {
                int *r1, *r2;
                int mask = (s5v | 0x10000) | 0x80000 | 0x898;
                done = 1;
                r1 = (int *)titproc_uso_func_000418();
                titproc_uso_func_0120A8(d, 4, r1, 0);
                r2 = (int *)titproc_uso_func_0027E8(d, r1, 10, one);
                titproc_uso_func_07ACE0(d16);
                if (*(int *)((char *)r2 + 0x14) != 0) {
                    *(int *)((char *)r2 + 0x4) = one;
                }
                titproc_uso_func_011CD8(d, one);
                *(int *)((char *)r2 + 0x14) = (int)d;
                titproc_uso_func_001E9C(0, mask, r2, 0);
                titproc_uso_func_01DA48(arg, 0);
                *(int *)(d + 0x40) = 0;
                break;
            }
            case 5: {
                int *r1, *r2;
                int mask;
                *(int *)(d + 0x40) = 0;
                mask = (s5v | 0x1010000) | 0x80000 | 0x898;
                done = 1;
                r1 = (int *)titproc_uso_func_000418();
                titproc_uso_func_0120A8(d, 4, r1, 0);
                r2 = (int *)titproc_uso_func_0027E8(d, r1, 11, 2);
                titproc_uso_func_07ACE0(d16);
                if (*(int *)((char *)r2 + 0x14) != 0) {
                    *(int *)((char *)r2 + 0x4) = one;
                }
                titproc_uso_func_011CD8(d, one);
                *(int *)((char *)r2 + 0x14) = (int)d;
                titproc_uso_func_001E9C(0, mask, r2, 0);
                titproc_uso_func_01DA48(arg, 0);
                *(int *)(d + 0x40) = 0;
                break;
            }
            case 6:
                titproc_uso_func_000C0C(arg);
                s5v = 0x2100000;
                *(int *)(d + 0x40) = 10;
                break;
            case 7: {
                int *r;
                int flag = s5v & 0x2000000;
                int mask = (s5v | 0x8020000) | 0x80000;
                done = 1;
                titproc_uso_func_000B6C(arg, 2);
                *(char *)(d + 0x181) = titproc_uso_func_01EF10(*(int *)(*(int *)arg + 8));
                *(char *)(d + 0x182) = titproc_uso_func_01EF44(*(int *)(*(int *)arg + 8));
                *(char *)(d + 0x183) = titproc_uso_func_01EF94(*(int *)(*(int *)arg + 8));
                if (flag != 0) {
                    titproc_uso_func_0120A8(d, 10, titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8)), 2);
                    *(int *)(d + 0x34) = 6;
                } else {
                    *(int *)(d + 0x34) = 6;
                    titproc_uso_func_0120A8(d, 4, titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8)), 0);
                }
                *(int *)(d + 0x64) = titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8));
                r = (int *)titproc_uso_func_0027E8(d, *(int *)(d + 0x64), 4, one);
                *(int *)(d + 0x34) = one;
                titproc_uso_func_07ACE0(d16);
                if (*(int *)((char *)r + 0x14) != 0) {
                    *(int *)((char *)r + 0x4) = one;
                }
                titproc_uso_func_011CD8(d, one);
                *(int *)((char *)r + 0x14) = (int)d;
                titproc_uso_func_001E9C(0, mask + *(int *)(*(int *)(*(int *)arg + 8) + 4), r, *(int *)arg);
                titproc_uso_func_01DA48(arg, 0);
                *(int *)(d + 0x40) = 11;
                break;
            }
            case 8:
                titproc_uso_func_000C0C(arg);
                s5v = 0x2100000;
                *(int *)(d + 0x40) = 9;
                break;
            case 9: {
                int *r;
                int flag = s5v & 0x2000000;
                int mask = (s5v | 0x8020000) | 0x80000;
                done = 1;
                titproc_uso_func_000B6C(arg, one);
                *(char *)(d + 0x181) = titproc_uso_func_01EF10(*(int *)(*(int *)arg + 8));
                *(char *)(d + 0x182) = titproc_uso_func_01EF44(*(int *)(*(int *)arg + 8));
                *(char *)(d + 0x183) = titproc_uso_func_01EF94(*(int *)(*(int *)arg + 8));
                if (flag != 0) {
                    titproc_uso_func_0120A8(d, 10, titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8)), one);
                } else {
                    titproc_uso_func_0120A8(d, 4, titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8)), 0);
                }
                *(int *)(d + 0x64) = titproc_uso_func_01EFC8(*(int *)(*(int *)arg + 8));
                r = (int *)titproc_uso_func_0027E8(d, *(int *)(d + 0x64), 4, one);
                titproc_uso_func_07ACE0(d16);
                if (*(int *)((char *)r + 0x14) != 0) {
                    *(int *)((char *)r + 0x4) = one;
                }
                titproc_uso_func_011CD8(d, one);
                *(int *)((char *)r + 0x14) = (int)d;
                titproc_uso_func_001E9C(0, mask + *(int *)(*(int *)(*(int *)arg + 8) + 4), r, *(int *)arg);
                titproc_uso_func_01DA48(arg, 0);
                *(int *)(d + 0x40) = 11;
                break;
            }
            case 10:
                break;
            case 11:
                titproc_uso_func_000C0C(arg);
                *(int *)(d + 0x40) = *(int *)(d + 0x44);
                break;
            }
        }
        a1 = *(int *)(d + 0x40);
    } while (done == 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000005DC);
#endif

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

#ifdef NON_MATCHING
/* Partial structural decode 2026-06-01. 4-case state machine (jr-table on
 * s0->0x40, written as an if-chain) advancing a title-screen sequence: each
 * state runs a timer, fires a virtual method on a sub-object, and transitions
 * on expiry. Cross-USO calls are the gl_func_00000000 import.
 *
 * 2026-06-02 GAP MAP (40.32%, target 290 insns / built 150 = 143 short). The
 * dispatch IS a jr-table (sltiu state,4; jr table[state]) but converting the
 * if-chain to `switch` REGRESSES to 37.1% (incomplete case bodies misalign
 * more than the dispatch helps — keep the if-chain until bodies are complete).
 * The two missing blocks are case-body TAILS, not new cases:
 *  - ~~state 1 tail @0x17C~~ DECODED 2026-06-10 (40.32 -> 47.10): the
 *    two vt-call arms are in the C below (the old d->0x34=1 line was a
 *    misread of `sw t0,64(s0)`).
 *  - ~~state 2/3 tail @0x29C~~ DECODED 2026-06-10 (47.10 -> 57.43):
 *    state 3's real spine = t==0 init (D->0x34=1 + gl(s0,v,0)) then the
 *    p->0x34-gated counter-clamp pair (+16 cap 255->720 / -16 floor 0
 *    with the gate-confirmed vt-call chain inside). Remaining: the
 *    shared 0x474 tail, jal identities, per-arm fine shapes.
 *  - PASS-9 2026-06-10: removed the d local (inline &D remat per use,
 *    matching the target's lui/addiu pattern) -- score-neutral, frame
 *    unchanged at 0x30 vs target 0x20. The frame driver is cross-call
 *    temp liveness (an afa60020 spill at slot 0x20), uoptlist class.
 *    Remaining structural gap = the jumptable head (capped, below) +
 *    the frame; the 277 positional diffs are head-cascade, fuzzy 84.87
 *    reflects aligned content.
 *  - PASS-8 NOTE 2026-06-10: the head's 4-entry jumptable (sltiu 4 +
 *    lui/addu/lw/jr) is NOT reproducible from a 4-case switch -- both
 *    IDO 7.1 and 5.3 at -O2 emit compare chains for 4 cases (tested
 *    minimal + big-body). EXHAUSTIVE 2026-06-10: 9 forms swept --
 *    5 labels gives sltiu 5 (table at the 5-label threshold, both
 *    compilers); guard+switch, shared labels (5 over range 0-3),
 *    4+default, double-switch, -O1, -O2 -g3 ALL emit compare chains
 *    or the wrong sltiu. NO tested C/flag combination produces a
 *    4-entry table. The head is a genuine compiler-config or
 *    hand-dispatch artifact; the compare-chain C stays as the
 *    closest form. Do not re-sweep switch shapes for this head.
 *    Remaining small gaps: lui/addiu materializes at 0x22C/0x28C and
 *    a nop/lw/li triplet at 0x2DC (per-arm reload items).
 *  - PASS-4 RECON 2026-06-10: the NM emit is 0x414 vs target 0x488 =
 *    29 insns SHORT; the gap is distributed (position diff useless at
 *    this delta -- next pass needs a mnemonic-level side-by-side to
 *    find the missing chunks; likely candidates: the 0x474 tail's
 *    sw-zero epilogue variants and un-decoded delay-slot content in
 *    the branch-heavy arms).
 * Next tick: extend state-1 then state-2/3 bodies (each adds ~15-25pp).
 * 2026-06-10 dispatcher-scan audit: the full 290-word [0x116C..0x15F4)
 * region is SELF-CONTAINED (zero out-branches; jumptable at word 11)
 * -- no boundary defect; the existing work-plan stands. This was the
 * 5th and last cross-USO jr-tN scan candidate (scorecard: 2 exact
 * matches landed, 1 control-flow fix, 1 harness gotcha, 1 double-cap,
 * 1 already-planned big decode = this). */
void titproc_uso_func_0000116C(char *s0) {
    char *v1, *vt;
    int state = *(int *)(s0 + 0x40);
    int n, t, v;

    switch (state) {
    case 0: {
        t = *(int *)(s0 + 0x3C) - 1;
        *(int *)(s0 + 0x3C) = t;
        if (t >= 0) {
            if (gl_func_00000000((char *)&D_00000000, 0x40300) == 0) {
                return;
            }
        }
        v1 = *(char **)(s0 + 0x58);
        vt = *(char **)(v1 + 0x28);
        ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
        gl_func_00000000(*(int *)(s0 + 0x58));
        n = *(int *)(s0 + 0x70);
        *(int *)(s0 + 0x40) = state + 1;
        *(int *)(s0 + 0x3C) = (n * 16 - n) * 2;
        *(int *)(s0 + 0x68) = 40;
        gl_func_00000000(13);
        break;
    }
    case 1: {
        /* 2026-06-10 pass 5 FULL REWRITE from the 27-insn missing block:
         * the prior arms were misplaced (they sit AFTER a gate chain,
         * gated on an SI-status bit, not p->0x34) and a convergent
         * "fire" block (D->0x34=1 + gl(s0,gl(),0)) serves both the
         * t==0 path and the p-chain-nonzero path. */
        v = *(int *)(s0 + 0x68);
        if (v != 0) {
            v = v - 1;
            *(int *)(s0 + 0x68) = v;
        }
        if (v == 0) {
            v1 = *(char **)(s0 + 0x54);
            vt = *(char **)(v1 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
        }
        t = *(int *)(s0 + 0x3C) - 1;
        *(int *)(s0 + 0x3C) = t;
        if (t == 0) goto fire;
        if (*(int *)(*(char **)(*(char **)(s0 + 0x50) + 0x44) + 0x34) != 0) {
fire:
            *(int *)((char *)&D_00000000 + 0x34) = 1;
            v = gl_func_00000000();
            gl_func_00000000(s0, v, 0);
            return;
        }
        if (*(int *)(s0 + 0x68) != 0) {
            return;
        }
        if (gl_func_00000000((char *)&D_00000000, 0x40300) == 0) {
            return;
        }
        gl_func_00000000(*(int *)(s0 + 0x58));
        gl_func_00000000(*(int *)(s0 + 0x54));
        if (*(unsigned short *)(*(char **)((char *)&D_00000000 + 0x154) + 4) & 8) {
            v1 = *(char **)(s0 + 0x60);
            vt = *(char **)(v1 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
            *(int *)(s0 + 0x40) = 2;
            gl_func_00000000(144);
        } else {
            v1 = *(char **)(s0 + 0x5C);
            vt = *(char **)(v1 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
            n = *(int *)(s0 + 0x74);
            *(int *)(s0 + 0x40) = 3;
            *(int *)(s0 + 0x3C) = (n * 16 - n) * 2;
            gl_func_00000000(144);
        }
        break;
    }
    case 2: {
        gl_func_00000000(*(int *)(s0 + 0x60));
        if (gl_func_00000000((char *)&D_00000000, 0x40100) != 0) {
            char *reg;
            gl_func_00000000(5);
            reg = *(char **)((char *)&D_00000000 + 0x154);
            *(unsigned short *)(reg + 4) = *(unsigned short *)(reg + 4) & 0xFFF7;
            gl_func_00000000(*(int *)(s0 + 0x60));
            v1 = *(char **)(s0 + 0x5C);
            vt = *(char **)(v1 + 0x28);
            ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
            n = *(int *)(s0 + 0x74);
            *(int *)(s0 + 0x40) = 3;
            *(int *)(s0 + 0x3C) = (n * 16 - n) * 2;
        }
        break;
    }
    case 3: {
        /* 2026-06-10 restructure from @0x288: the old body's vt-call
         * chain actually lives INSIDE the gate-confirmed sub-branch;
         * the real spine is t==0-init then the counter clamp pair. */
        int *c;
        t = *(int *)(s0 + 0x3C);
        if (t == 0) {
            v = gl_func_00000000();
            *(int *)((char *)&D_00000000 + 0x34) = 1;
            gl_func_00000000(s0, v, 0);
        }
        if (*(int *)(*(char **)(*(char **)(s0 + 0x50) + 0x44) + 0x34) != 0) {
            c = (int *)(*(char **)(s0 + 0x64) + 0x3C);
            if (*c < 255) {
                *c = *c + 16;
                if (*(int *)(*(char **)(s0 + 0x64) + 0x3C) >= 256) {
                    *(int *)(*(char **)(s0 + 0x64) + 0x3C) = 720;
                }
            } else {
                v1 = (char *)&D_00000000;
                vt = *(char **)(v1 + 0x28);
                ((void (*)(int))(*(int *)(vt + 0x64)))(*(short *)(vt + 0x60) + (int)v1);
            }
        } else {
            int av;
            v1 = *(char **)(s0 + 0x64);
            av = *(int *)(v1 + 0x3C);
            c = (int *)(v1 + 0x3C);
            if (av > 0) {
                *c = *c - 16;
                v1 = *(char **)(s0 + 0x64);
                av = *(int *)(v1 + 0x3C);
                if (av < 0) {
                    *(int *)(v1 + 0x3C) = 0;
                    av = *(int *)(*(char **)(s0 + 0x64) + 0x3C);
                }
            }
            if (av == 0) {
                if (gl_func_00000000((char *)&D_00000000, 512) != 0) {
                    v1 = *(char **)(s0 + 0x58);
                    vt = *(char **)(v1 + 0x28);
                    ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
                    gl_func_00000000(*(int *)(s0 + 0x58));
                    v1 = *(char **)(s0 + 0x54);
                    vt = *(char **)(v1 + 0x28);
                    ((void (*)(int))(*(int *)(vt + 0x5C)))(*(short *)(vt + 0x58) + (int)v1);
                    gl_func_00000000(*(int *)(s0 + 0x5C));
                    n = *(int *)(s0 + 0x70);
                    *(int *)(s0 + 0x40) = 1;
                    *(int *)(s0 + 0x3C) = (n * 16 - n) * 2;
                    gl_func_00000000(2050);
                    /* 2026-06-10 pass 3: the 0x40100 gate + 40-byte-record
                     * fn-ptr table call (entry field 0x90 = callback;
                     * D->0xA8 = self, D->0x84 = index published first). */
                    if (gl_func_00000000((char *)&D_00000000, 0x40100) != 0) {
                        gl_func_00000000(*(int *)(s0 + 0x5C));
                        gl_func_00000000(5);
                        v1 = *(char **)(s0 + 0x5C);
                        n = *(int *)(v1 + 0x7C);
                        if (*(int *)(v1 + n * 40 + 0x90) != 0) {
                            *(char **)((char *)&D_00000000 + 0xA8) = s0;
                            *(int *)((char *)&D_00000000 + 0x84) = *(int *)(v1 + 0x7C);
                            v1 = *(char **)(s0 + 0x5C);
                            ((void (*)(void))(*(int *)(v1 + *(int *)(v1 + 0x7C) * 40 + 0x90)))();
                        }
                    }
                }
            }
        }
        break;
    }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000116C);
#endif

/* titproc_uso_func_000015F4 — alloc-or-passthrough constructor. The second
 * null guard is dead after the first successful alloc, but the original source
 * shape emitted it; preserve it per docs/PATTERNS.md's cascade recipe.
 * int *f(int *a0){
 *   int *p = a0;
 *   if (p == 0) { p = gl_func_00000000(60);  if (p == 0) return 0; }
 *   if (p == 0) { p = gl_func_00000000(44);  if (p == 0) goto init; }  // dead
 *   gl_func_00000000(p, &D_00000000 + 0x4C4);
 *   p->0x28 = &D_00000000;
 * init:                                                      // asm 0x68
 *   p->0x28 = &D_00000000;            // re-store (a2 base)
 *   p->0xC  = &D_00000000 + 0x4CC;
 *   p->0x2C = 0;
 *   p->0x30 = 0;
 *   p->0x34 = 160.0f;                 // 0x43200000
 *   p->0x38 = 210.0f;                 // 0x43520000
 *   gl_func_00000000(p);
 *   return p;                         // v0 = a2
 * }
 *
 * 2026-05-29: 95.9% (2-word diff), same size. The ONLY residual is an
 * instruction-scheduling SWAP at the first post-call3 `p->0x28 = &D` store:
 * build emits `lw a2,0x20(sp)` (p reload) then `addiu t6` (&D LO16); expected
 * emits `addiu t6` then `lw a2` (and the target even double-reloads p into both
 * a0@0x1648 and a2@0x1654). Two independent insns; pure scheduler tiebreak,
 * not C-controllable here. NEGATIVE: a faithful single-`p` rewrite (collapsing
 * the tmp/a0 split into one var) REGRESSES to 41 diffs — IDO eliminates the
 * dead-guard spill and re-lays the whole frame. The tmp/a0 split IS load-bearing;
 * keep it. Arg-count-lever check (per the 8EC win): a2 here is the object
 * pointer held across the calls, NOT an under-counted arg — lever N/A. */
int *titproc_uso_func_000015F4(a0)
int *a0;
{
  int *tmp;
  if (a0 == 0)
  {
    a0 = (int *) gl_func_00000000(60);
    if (a0 == 0)
    {
      goto end;
    }
  }
  tmp = a0;
  if (tmp == 0)
  {
    tmp = (int *) gl_func_00000000(44);
    if (tmp == 0)
    {
      goto common;
    }
 } gl_func_00000000(tmp, ((char *) (&titproc_uso_D_00048C)) + 0x4C4); *((int *) (((char *) tmp) + 0x28)) = (int) (&import_00073B18);
  common:
  *((int *) (((char *) a0) + 0x28)) = (int) (&titproc_uso_D_000194);

  *((int **) (((char *) a0) + 0xC)) = (int *) (((char *) (&titproc_uso_D_00048C)) + 0x4CC);
  *((int *) (((char *) a0) + 0x2C)) = 0;
  *((int *) (((char *) a0) + 0x30)) = 0;
  *((float *) (((char *) a0) + 0x34)) = 160.0f;
  *((float *) (((char *) a0) + 0x38)) = 210.0f;
  gl_func_00000000(a0);
  end:
  return a0;

}
/* (end verified decode)
 * Struct-typing value: object has int @0x28 (&D base), ptr @0xC (&D+0x4CC),
 * counters @0x2C/0x30 (zeroed; 16B8 sibling does the ±6 wrap on these),
 * floats @0x34=160.0 / @0x38=210.0 (the 16B8 threshold bounds 65..250 sit
 * between these). Allocator sig gl_func_00000000(size) → ptr; 60- and
 * 44-byte variants. The 2nd null-check is compiler-emitted dead code from a
 * defensive cascade in source. K&R parameter style plus reusing `a0` keeps
 * IDO on caller-slot spills; D_titproc_15F4_tmp prevents CSE of the two
 * base stores, and the Makefile retargets one %lo relocation for final
 * scheduling. */

/* titproc_uso_func_000016B8: 22-insn field oscillator (a0->0x2C counter,
 * a0->0x30 direction flag). +6 when flag==0 until >=0xFA, -6 otherwise
 * until <0x41, flipping the flag at each bound (branch-likely bnel idiom).
 *
 * 2026-05-28: BOUNDARY FIX. The .s was truncated to 0x30 (12 insns); the
 * function is actually 0x58 (22 insns) — its two conditional branches
 * (->0x16EC, ->0x1708) target the dropped 0x16E8..0x170C region, which no
 * .s covered (a 40-byte build gap, NOT a cross-fn epilogue cap as the old
 * comment claimed). Rewrote the .s to the true 0x58. C logic + insn count
 * now exact (22==22); remaining 15 diffs are pure register allocation
 * (loads land in $v0/$v1 vs target's $t2/$t7/$t8). Permuter candidate. */
/* In-place `a0[0x2C] += 6` (NOT `cur=...; nv=cur+6; a0[0x2C]=nv`) is what
 * matches: the named-temp form CSEs the field read into $v0/$v1; reading the
 * field fresh per access makes IDO use $t2/$t7/$t8 like the target. */
void titproc_uso_func_000016B8(int *a0) {
    if (a0[0x30 / 4] == 0) {
        a0[0x2C / 4] += 6;
        if (a0[0x2C / 4] >= 250) {
            a0[0x30 / 4] ^= 1;
        }
    } else {
        a0[0x2C / 4] -= 6;
        if (a0[0x2C / 4] < 65) {
            a0[0x30 / 4] ^= 1;
        }
    }
}

/* titproc_uso_func_00001710 — verified structural decode (FPU lerp, 76
 * insns; div.s/mul.s chain + 3 calls + recovered f16=1.0f stolen prologue
 * = documented sub-80 ceiling → INCLUDE_ASM build path; struct-typing ref).
 * Boundary: 0x000-0x004 (lui at,0x3f80; mtc1 at,$f16 = 1.0f) is this fn's
 * constant-hoisted prologue, recovered from 16B8's tail 2026-05-17.
 *   f16 = 1.0f;  sp[96..108] = f16 (a 1,1,1,1 vec);
 *   if (*(int*)(&D+0x18C) != 0) {
 *     dc = *(float*)(&D+0x40);
 *     sp[52]=1; sp[64]=1; sp[56]=dc; sp[60]=dc; sp[48]=1;
 *     t = (float)s0->0x2C / 255.0f;            // 0x437f0000 = 255.0
 *     sp[36] = sp[96] + (sp[52]-sp[96])*t;     // lerp(1, 1, t)
 *     sp[40] = sp[100]+ (sp[56]-sp[100])*t;    // lerp(1, dc, t)
 *     sp[44] = sp[104]+ (sp[60]-sp[104])*t;    // lerp(1, dc, t)
 *     gl_func_00000000(&D+0x18, s0->0x2C, &sp[36]);
 *   } else {
 *     gl_func_00000000(&D, s0->0x2C, &sp[96]);
 *   }
 *   r = gl_func_00000000(&D);
 *   gl_func_00000000(r, (int)*(float*)(s0+0x34), (int)*(float*)(s0+0x38), 3);
 * Struct-typing: s0->0x2C is a 0..255 alpha/blend (÷255 → t); s0->0x34 /
 * s0->0x38 are the 160.0f / 210.0f floats the 15F4 constructor sets, here
 * trunc.w.s'd back to int 160 / 210 (confirms the ctor field types).
 * D[0x18C] = mode flag, D[0x40] = a float constant, &D / &D+0x18 = two
 * GBI-ish data bases. Caps <80: div.s/mul.s/sub.s lerp scheduling + the
 * sp 1.0f stack-temp dance + &D %hi/%lo reloc + 3-call spill. INCLUDE_ASM
 * is the correct build path (no episode; tautology-trap rule). */
extern char import_00263E00;
extern char import_0024CAF8;
extern char import_00263D30;
extern void import_0024E608();
extern void import_0024F2C8();
extern void import_0024F34C();
#ifdef NON_MATCHING
/* SYMBOLS RE-DERIVED 2026-06-22: prior body used gl_func_00000000/&D
 * placeholders (relocs WRONG) and passed the F2C8 *return* to F34C — the
 * target instead saves a0 across F2C8 (sw a0,92(sp); lw a0,92(sp)) and reuses
 * the SAME import_00263D30[+0x18] base. Three calls are distinct real targets
 * (import_0024E608, import_0024F2C8, import_0024F34C); the first call's a0 is
 * import_0024CAF8 in BOTH branches, only a2 (lerped &sp36 vs ones &sp96) and
 * the tgt base (+0x18 in if, +0 in else) differ. Twin of
 * mgrproc_uso_func_00002850 (loop form). RELOCS + LOGIC now byte-faithful;
 * residual is a FRAME-SIZE cap (target -0x70 frame parks the ones-vec at
 * sp+96..108 with 3 extra stack-temp stores; natural C emits a -0x60 frame,
 * 73 vs 76 insns) PLUS the FP-renumber cap (1.0f colored to $f16 in target,
 * $f0 here). Both are SKIP-class caps (no pad-forcing); INCLUDE_ASM is the
 * build path. */
void titproc_uso_func_00001710(char *s0) {
    float f16 = 1.0f;
    float ones[4];
    float vec[5];   /* vec[0]=sp48 vec[1]=sp52 vec[2]=sp56 vec[3]=sp60 vec[4]=sp64 */
    float out[3];
    float t, dc;
    char *tgt;
    ones[0] = f16; ones[1] = f16; ones[2] = f16; ones[3] = f16;
    if (*(int *)((char *)&import_00020098 + 0x18C) != 0) {
        dc = *(float *)((char *)&import_00263E00 + 0x40);
        vec[1] = f16; vec[4] = f16; vec[2] = dc; vec[3] = dc;
        t = (float)*(int *)(s0 + 0x2C) / 255.0f;
        vec[0] = f16;
        out[0] = ones[0] + (vec[1] - ones[0]) * t;
        out[1] = ones[1] + (vec[2] - ones[1]) * t;
        out[2] = ones[2] + (vec[3] - ones[2]) * t;
        import_0024E608(&import_0024CAF8, *(int *)(s0 + 0x2C), out);
        tgt = (char *)&import_00263D30 + 0x18;
    } else {
        import_0024E608(&import_0024CAF8, *(int *)(s0 + 0x2C), ones);
        tgt = (char *)&import_00263D30;
    }
    import_0024F2C8(tgt);
    import_0024F34C(tgt, (int)*(float *)(s0 + 0x34), (int)*(float *)(s0 + 0x38), 3);
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001710);
#endif

/* titproc_uso_func_00001840: 68-insn (0x110) 2-cascade constructor with
 * 11-int + 4-float constant spray. Allocates main 0x74-byte object,
 * runs init helper from &D_0 + 0x4D8, sets vtable + 11 int field
 * constants (255, 163, 154, 67, 44, 1, -57, 28, 17, -3, 33) at offsets
 * 0x2C..0x70, plus 4 floats (1.0f x3, 0.0f) at 0x3C..0x48.
 *
 * 2026-05-14: applied fall-through-with-null-guard form (third sibling
 * of 1B10/1D7C in this dual-alloc dead-arm family). Same fix: rename
 * the dead-arm allocation result to `sub`, replace `if (X == 0) return X;`
 * with `if (X == 0) sub = alloc(...);`, fix the `*(self+0x28)` typo to
 * use `sub` then `self` for the two distinct stores. Pushed 76.87% →
 * 84.26% (+7.39pp; smaller gain than 1B10/1D7C because the body is
 * longer so proportional improvement is diluted).
 *
 * 2026-06-19: full exact-source reconstruction from the raw asm. Wired
 * the REAL intra-USO symbols (func_055750/04C678/001AF8/00F4CC, data
 * D_0001FC / D_00048C / import_00073B18) so relocs resolve correctly, and
 * restored the precise control flow: `sub = self; if (self==0){ sub =
 * alloc(0x2C); if(!sub) goto skip; }` (bne s0,zero fall-through into the
 * func_04C678 block; second-alloc null check is beq v0,zero,skip). This
 * drops the C-only emit to just 4 NON-RELOC diffs (~94%): (1+2) the
 * prologue `or s0,a0` vs `sw ra` delay-slot fill at 0x08/0x10 — as1's
 * fixed from-before delay fill, not C-reachable; (3+4) the saved-`sub`
 * arg-temp home at sp+0x24 vs our sp+0x20 (one-word spill-home delta).
 * A 1500s / ~80k-iter permuter found NO improvement past this base
 * (best score 120, no objdiff gain). Confirmed ugen temploc-binding /
 * as1-fill cap class; INSN_PATCH removed (banned 2026-05-23). Stays NM. */
#ifdef NON_MATCHING
extern int titproc_uso_func_04C678();
extern int titproc_uso_func_001AF8();
extern int titproc_uso_func_00F4CC();
extern char titproc_uso_D_0001FC;
void *titproc_uso_func_00001840(void *a0) {
    void *self = a0;
    void *sub;
    if (self == 0) {
        self = (void*)titproc_uso_func_055750(0x74);
        if (self == 0) goto end;
    }
    sub = self;
    if (self == 0) {
        sub = (void*)titproc_uso_func_055750(0x2C);
        if (sub == 0) goto skip;
    }
    titproc_uso_func_04C678(sub, (char*)&titproc_uso_D_00048C + 0x4D8);
    *(int*)((char*)sub + 0x28) = (int)&import_00073B18;
skip:
    *(int*)((char*)self + 0x28) = (int)&titproc_uso_D_0001FC;
    *(int*)((char*)self + 0x0C) = (int)((char*)&titproc_uso_D_00048C + 0x4E0);
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
    titproc_uso_func_001AF8(self);
    titproc_uso_func_00F4CC(self);
end:
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001840);
#endif

/* titproc_uso_func_00001950: 106-insn dual-phase display/alpha helper.
 * Decrements/fades through the D+0x60/D+0x78 display blocks while
 * a0->0x38 == 0, then increments/clamps a0->0x2C and dispatches the
 * D+0x90 block. C emit is same length; previously INSN_PATCH closed the
 * decrement scheduling, one-word stack-slot shift, and register-choice
 * diffs. INSN_PATCH REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy; now an honest NM cap. */
extern void import_0024E388();
#ifdef NON_MATCHING
/* RE-DERIVED 2026-06-22: prior body used gl_func_00000000/&D placeholders
 * (relocs WRONG). Real callees are import_0024F2C8 (begin), import_0024E388
 * (alpha+rgba), import_0024F34C (coords); base is import_00263D30 with the
 * +0x60/+0x78/+0x90 block offsets. Twin family of titproc_uso_func_00001710
 * / mgrproc_uso_func_00002E3C. RELOCS + LOGIC now byte-faithful (96.24%):
 * frame -0x60, decrement/clamp + increment/clamp blocks, all 9 calls + bases
 * match. RESIDUAL = register-coloring (target keeps v in a fresh $t8 and
 * fills the beq-delay with `addiu t8,v0,-4` + `or v0,t8` in the bgez-delay;
 * natural C reuses $v0 with a nop-delay) PLUS a 4-byte buf-position frame
 * shift (buf@sp+0x4c target vs +0x50 here). Both are SKIP-class regalloc/
 * frame caps; INCLUDE_ASM build path. */
void titproc_uso_func_00001950(int *a0) {
    float buf_a[4];
    char pad[24];
    float buf_b[4];
    int v;

    if (a0[0x38 / 4] == 0) {
        if (a0[0x34 / 4] != 0) {
            a0[0x34 / 4]--;
            v = a0[0x2C / 4];
        } else {
            v = a0[0x2C / 4];
            if (v != 0) {
                v -= 4;
                a0[0x2C / 4] = v;
                if (v < 0) {
                    a0[0x2C / 4] = 0;
                    a0[0x38 / 4] = 1;
                    v = 0;
                }
            }
        }
        if (v == 0) {
            return;
        }
        buf_a[0] = 1.0f;
        buf_a[1] = 1.0f;
        buf_a[2] = 1.0f;
        buf_a[3] = 1.0f;
        import_0024F2C8((char *)&import_00263D30 + 0x60);
        import_0024E388((char *)&import_00263D30 + 0x60, a0[0x2C / 4], buf_a, 0xFF);
        import_0024F34C((char *)&import_00263D30 + 0x60,
                        a0[0x4C / 4] + a0[0x54 / 4],
                        a0[0x50 / 4] + a0[0x58 / 4], 3);
        import_0024F2C8((char *)&import_00263D30 + 0x78);
        import_0024E388((char *)&import_00263D30 + 0x78, a0[0x2C / 4], buf_a, 0xFF);
        import_0024F34C((char *)&import_00263D30 + 0x78,
                        a0[0x4C / 4] + a0[0x64 / 4],
                        a0[0x50 / 4] + a0[0x68 / 4], 3);
    } else {
        v = a0[0x2C / 4];
        if (v < 0xFF) {
            v += 4;
            a0[0x2C / 4] = v;
            if (v >= 0xFF) {
                a0[0x2C / 4] = 0xFF;
            }
        }
        buf_b[0] = 1.0f;
        buf_b[1] = 1.0f;
        buf_b[2] = 1.0f;
        buf_b[3] = 1.0f;
        import_0024F2C8((char *)&import_00263D30 + 0x90);
        import_0024E388((char *)&import_00263D30 + 0x90, a0[0x2C / 4], buf_b, 0xFF);
        import_0024F34C((char *)&import_00263D30 + 0x90,
                        a0[0x6C / 4], a0[0x70 / 4], 3);
    }
    (void)pad;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_00001950);
#endif

void titproc_uso_func_00001AF8(int *a0) {
    a0[0x38 / 4] = 0;
    a0[0x34 / 4] = 150;
    a0[0x2C / 4] = 255;
}

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
 * 51.93% -> 73.40% (+21.47pp) C-only fuzzy.
 *
 * 2026-05-17: matched the dead-arm constructor shape used by sibling
 * 0x1D7C: the secondary alloc is unreachable after the primary non-null
 * guard, and the final dispatch is one-argument.
 *
 * 2026-06-20: full reconstruction with the REAL reloc callees/symbols
 * (titproc_uso_func_055750 alloc, titproc_uso_func_04C678 init,
 * &import_00073B18 for the sub-arm 0x28, &titproc_uso_D_000264 for the
 * common 0x28; base = &titproc_uso_D_00048C; final dispatch
 * titproc_uso_func_00F4CC(self) then self+0x3C = 0). Modeled exactly on
 * the reconstructed sibling 0x1D7C (reuse-param-as-object lever: `self`
 * IS the param so IDO arg-saves to the caller slot sw a2,0x20(sp)).
 * Collapsed the prior placeholder body's 44 reg/spill diffs to 2.
 *
 * EXACT (2026-06-21, decomp-permuter). The 2-insn as1 scheduler tie was
 * cracked by joining the `04C678(...)` init call and the sub->0x28 store onto
 * one statement (re-anchors the as1 schedule so the `self` reload lands after
 * the &import_00073B18 addiu rather than hoisting into its lui/addiu gap).
 * Verified IN-TREE: 42/42 words, 0 non-reloc diffs, 12 reloc records identical
 * to expected; full ROM byte-identical to baserom. NOTE: the twin 0x1D7C is
 * NOT cracked — its permuter "100" was an objdiff false-100 (the adjacent
 * independent-insn swap scores 100 fuzzy but the ROM bytes stayed wrong). The
 * ONLY valid gate for these as1 ties is the ROM cmp, not objdiff. */
extern int titproc_uso_func_055750();
extern int titproc_uso_func_04C678();
extern int titproc_uso_func_00F4CC();
extern char titproc_uso_D_000264;
void *titproc_uso_func_00001B10(void *self) {
  void *sub;
  char *base = &titproc_uso_D_00048C;
  if (self == 0)
  {
    self = (void *) titproc_uso_func_055750(0x40);
    if (self == 0)
    {
      goto end;
    }
  }
  sub = self;
  if (self == 0)
  {
    sub = (void *) titproc_uso_func_055750(0x2C);
    if (sub == 0)
    {
      goto common;
    }
  }
  titproc_uso_func_04C678(sub, base + 0x4EC); *((int *) (((char *) sub) + 0x28)) = (int) (&import_00073B18);
  common:
  *((int *) (((char *) self) + 0x28)) = (int) (&titproc_uso_D_000264);
  *((int *) (((char *) self) + 0x0C)) = (int) (base + 0x4F4);
  titproc_uso_func_00F4CC(self);
  *((int *) (((char *) self) + 0x3C)) = 0;
  end:
  return self;

}

/* titproc_uso_func_00001BB8: 42-insn dual-state-bracket helper. Two
 * gl_func dispatches with asymmetric inner-D[0] gates. LANDED fuzzy=100
 * at size 0xA8. The previously-documented 8-byte SUFFIX_BYTES tail for
 * SUCCESSOR (0x1C68)'s stolen prologue is no longer in the Makefile —
 * the bytes now correctly belong to 0x1C68's own symbol (verified
 * 2026-05-26: no SUFFIX_BYTES match for func_00001BB8, no .o size change).
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
/* titproc_uso_func_00001C68: boundary-corrected (orphan-fn delete+merge). The
 * 2-word orphan titproc_uso_func_00001C60 (`lui at,0x3F80; mtc1 at,$f0` = 1.0f)
 * was a splat mis-split of THIS function's prologue — it materializes the 1.0f
 * the C writes as buf[0..3]. Merged into titproc_uso_func_00001C68.s; NM-wrap C
 * already built build[2:]==expected -> byte-exact. */
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

/* titproc_uso_func_00001D7C: 44-insn (0xB0) 2-cascade ctor + 4 floats=1.0f.
 * Sibling of 1840: alloc(0x40) + dead-arm alloc(0x2C), init from
 * &D_0+0x500, vtable, 4 floats=1.0f at +0x2C..0x38, zero at +0x3C.
 *
 * 2026-05-14: applied fall-through-with-null-guard form to the dead-arm
 * second alloc (per docs/IDO_CODEGEN.md#feedback-ido-goto-epilogue) and
 * fixed a typo (duplicate `*(self+0x28) = base` should have been `sub`
 * vs `self`). Pushed 59.36% → 84.20% (+24.84pp). Remaining cap: frame
 * size (-0x28 vs target -0x20) due to the extra `sub` local.
 *
 * 2026-05-16: tested `register void *sub` lever — no change (84.20%).
 * Consistent with the documented "register keyword honored narrowly"
 * rule; doesn't influence the local-spill that drives the frame size.
 *
 * 2026-05-17: reusing a0 for the subobject removed the extra local frame
 * slot and raised C-only emit to 93.02%. The remaining same-size $v1/$a2
 * and spill-slot diffs were previously patched with INSN_PATCH (REMOVED
 * 2026-05-23 as match-faking).
 *
 * 2026-06-20: full reconstruction with the REAL reloc callees/symbols
 * (titproc_uso_func_055750 alloc, titproc_uso_func_04C678 init,
 * &import_00073B18 for the sub-arm 0x28, &titproc_uso_D_0002CC for the
 * common 0x28; base = &titproc_uso_D_00048C). The prior body used
 * placeholder gl_func_00000000 / &D_00000000 (objdiff-name-blind 100%
 * but byte/episode-WRONG). Applying the reuse-param-as-object lever
 * (docs/IDO_CODEGEN.md#feedback-ido-reuse-param-as-object-caller-slot-spill)
 * — `self` IS the parameter, so IDO arg-saves it to the caller slot
 * (sw a2,0x20(sp)) instead of an in-frame spill — collapsed 18 reg/spill
 * diffs to 2. RESIDUAL (same size 44/44, exact insns): a 2-insn as1
 * scheduler tie — the `self` reload `lw a2,0x20(sp)` fills the gap between
 * t6's `lui`/`addiu` (&import_00073B18) instead of scheduling after the
 * addiu. Dataflow-independent pair; no reliable C lever (per the for-loop
 * comma-init schedule rule, which is loop-specific).
 *
 * 2026-06-21: CRACKED (byte-exact, ROM-identical). The residual 2-insn as1
 * scheduler tie (`lw a2,0x20(sp)` reload vs t6's `addiu` for &import_00073B18)
 * flips when the post-alloc-block close-brace is JOINED onto the same source
 * statement-line as the `func_04C678` call + the `*(sub+0x28)` store +
 * `common:` label + the next store (one physical line). decomp-permuter found
 * this statement-join; it re-anchors the as1 schedule so the addiu precedes the
 * self-reload, matching the target. Verified IN-TREE: matching build 0/44 word
 * diffs vs expected, full ROM byte-identical (make: ROM OK), verify-blocks OK.
 * NOTE: the one-line layout is load-bearing — reflowing it onto separate lines
 * reverts to the 2-diff swap (as1 statement-boundary scheduling sensitivity). */
extern int titproc_uso_func_055750();
extern int titproc_uso_func_04C678();
extern char titproc_uso_D_0002CC;
void *titproc_uso_func_00001D7C(void *self) {
  void *sub;
  char *base = &titproc_uso_D_00048C;
  if (self == 0)
  {
    self = (void *) titproc_uso_func_055750(0x40);
    if (self == 0)
    {
      goto end;
    }
  }
  sub = self;
  if (self == 0)
  {
    sub = (void *) titproc_uso_func_055750(0x2C);
    if (sub == 0)
    {
      goto common;
    }
 } titproc_uso_func_04C678(sub, base + 0x500); *((int *) (((char *) sub) + 0x28)) = (int) (&import_00073B18); common: *((int *) (((char *) self) + 0x28)) = (int) (&titproc_uso_D_0002CC);
  *((int *) (((char *) self) + 0x0C)) = (int) (base + 0x508);
  *((int *) (((char *) self) + 0x3C)) = 0;
  *((float *) (((char *) self) + 0x2C)) = 1.0f;
  *((float *) (((char *) self) + 0x30)) = 1.0f;
  *((float *) (((char *) self) + 0x34)) = 1.0f;
  *((float *) (((char *) self) + 0x38)) = 1.0f;
  end:
  return self;

}

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
 * 2026-06-22 REAL-SYMBOL PASS: prior body used gl_func_00000000 / &D_00000000
 * placeholders + D_tit_1E9C_v0..3 fakes -> ALL jal/HI16/LO16 relocs were WRONG.
 * Remapped every callee/global from the resolved relocs in
 * expected/src/titproc_uso/titproc_uso.c.o: allocator titproc_uso_func_055750;
 * init titproc_uso_func_04C678; vtable ptrs import_00073B18/B80/745F8 +
 * titproc_uso_D_000334; node-init titproc_uso_func_07ACE0; dispatch allocs
 * 0015F4/001840/001D7C/001B10; data base titproc_uso_D_00048C
 * (+0x514/0x51C/0x52C/0x530) and import_00020098 (+0x84/0x138/0x190). Fuzzy
 * held at 73.5% (instruction shape unchanged) but relocs now resolve correctly.
 * RESIDUAL = pure register-coloring/economy cap: target binds self->s1 (mine
 * s0) and threads the dead-guard chain through v1/a0 with a single sp+0x38
 * spill, while IDO spills an extra temp here (~12-insn size gap). Same cap
 * class as NM-capped sibling titproc_uso_func_00001840 (94%). Stays NM.
 *
 * 2026-06-01 (18.67 -> 27.64): confirmed SIBLING of timproc_uso_b3_func_00000994
 * / timproc_uso_b1_func_0000097C (0x6A8-alloc constructor family). The prior
 * "multi-write to p->0x28" reading was WRONG — it's the standard cascade's 4
 * distinct vtable stores (n3/n2/n1/self ->0x28 = t6/t7/t8/t9). Ported the proven
 * cascade + field-init structure (goto-chain dead-guards + distinct externs
 * D_tit_1E9C_v0..3; self alloc 0x6C8, D-template 0x514/0x51C/0x530, self->0x6ac).
 * Removed the broken `_TODO_loop` placeholder call. TBD: titproc's tail is a
 * UNIQUE double-buffering sub-loop (NOT shared with 994) — needs per-fn decode
 * from /tmp/ttit.txt (insns ~78-245).
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
/* 2026-06-22: real-symbol pass (was placeholder gl_func/&D -> wrong relocs).
 * Callees/data mapped from resolved relocs in expected/.../titproc_uso.c.o.
 * Structure kept from the higher-fuzzy prior reconstruction. Register coloring
 * is the same ugen temploc-binding / as1-fill cap class as sibling
 * titproc_uso_func_00001840 (NM at 94%) -> stays NON_MATCHING. */
extern int titproc_uso_func_055750();
extern int titproc_uso_func_04C678();
extern int titproc_uso_func_074710();
extern int titproc_uso_func_01B0F8();
extern int titproc_uso_func_0015F4();
extern int titproc_uso_func_001D7C();
extern int titproc_uso_func_001B10();
extern int titproc_uso_func_0022BC();
extern int titproc_uso_func_0139B0();
extern int titproc_uso_func_074840();
extern int import_00073B80();
extern int import_000745F8();
extern int import_000AE700();
extern int import_000B0DBC();
extern int import_000A7ECC();
extern int import_000B6C40();
extern int import_000B88CC();
extern int import_000A5D38();
extern int import_000A5F40();
extern int import_000A5FBC();
extern int import_0024CCF4();
extern char titproc_uso_D_000334;
extern char titproc_uso_D_00052C;
void *titproc_uso_func_00001E9C(void *a0, void *a1, void *a2, void *a3) {
    int *p = (int *)a0;
    int *n1, *n2, *n3;
    /* 5-stage get-or-create cascade (sibling of timproc_uso_b3_func_00000994 /
     * timproc_uso_b1_func_0000097C; self alloc 0x6C8 here, D-template 0x514).
     * goto-chain dead-guards + distinct-extern vtable stores (CSE-bust). */
    if (a0 == NULL) {
        p = (int *)titproc_uso_func_055750(0x6C8);
        if (p == NULL) return (void *)p;
    }
    n1 = p;
    if (p == NULL) { n1 = (int *)titproc_uso_func_055750(0x6A8); if (n1 == NULL) goto S_self; }
    n2 = n1;
    if (n1 == NULL) { n2 = (int *)titproc_uso_func_055750(0x50); if (n2 == NULL) goto S_n1; }
    n3 = n2;
    if (n2 == NULL) { n3 = (int *)titproc_uso_func_055750(0x2C); if (n3 == NULL) goto S_n2; }
    titproc_uso_func_04C678(n3, (char *)&titproc_uso_D_00048C + 0x514);
    n3[0x28 / 4] = (int)&import_00073B18;
S_n2:
    n2[0x28 / 4] = (int)&import_00073B80;
S_n1:
    n1[0x28 / 4] = (int)&import_000745F8;
    import_000AE700((char *)n1 + 0x50);
S_self:
    p[0x28 / 4] = (int)&titproc_uso_D_000334;
    p[0x568 / 4] = 0;
    import_000B0DBC(p, a1, (char *)&titproc_uso_D_00048C + 0x51C, a2);
    p[0x528 / 4] = (int)a3;
    titproc_uso_func_000000(p);
    titproc_uso_func_074710((char *)&titproc_uso_D_00048C + 0x530, 0);
    import_000A7ECC(&import_00020098, 0);
    p[0x6AC / 4] = (int)import_000B6C40(0);
    *(int *)((char *)&import_00020098 + 0x138) = p[0x6AC / 4];

    /* tail: node init + virtual dispatch (insns 78-108) */
    import_000B88CC(p[0x6AC / 4]);
    {
        int *node = (int *)p[0x6AC / 4];
        titproc_uso_func_07ACE0((char *)p + 0x10, node);
        if (node[0x14 / 4] != 0) {
            node[0x4 / 4] = 1;
        }
        node[0x14 / 4] = (int)p;
    }
    titproc_uso_func_01B0F8(p, a1);
    p[0x48 / 4] = 0;
    p[0x4F4 / 4] = (int)a1 & 0xFFFF;
    if (((int)a1 << 6) < 0) {
        p[0x6B4 / 4] = 0;
    }
    {
        int *r6b0 = (int *)titproc_uso_func_0015F4(0);
        int *vt;
        p[0x6B0 / 4] = (int)r6b0;
        vt = (int *)r6b0[0x28 / 4];
        ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)r6b0);
    }
    titproc_uso_func_07ACE0((char *)p + 0x10, (int *)p[0x6B0 / 4]);
    {
        int *n = (int *)p[0x6B0 / 4];
        if (n[0x14 / 4] != 0) {
            n[0x4 / 4] = 1;
        }
        n[0x14 / 4] = (int)p;
    }
    p[0x6B4 / 4] = (int)titproc_uso_func_001840(0);
    {
        int *n = (int *)p[0x6B4 / 4];
        int *vt;
        n[0x38 / 4] = 1;
        n[0x2C / 4] = 0;
        vt = (int *)n[0x28 / 4];
        ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + (int)n);
    }
    titproc_uso_func_07ACE0((char *)p + 0x10, (int *)p[0x6B4 / 4]);
    {
        int *n = (int *)p[0x6B4 / 4];
        if (n[0x14 / 4] != 0) {
            n[0x4 / 4] = 1;
            n[0x14 / 4] = (int)p;
        } else {
            p[0x6B4 / 4] = 0;
        }
    }
    p[0x6BC / 4] = (int)titproc_uso_func_001D7C(0);
    titproc_uso_func_07ACE0((char *)p + 0x10, (int *)p[0x6BC / 4]);
    {
        int *n = (int *)p[0x6BC / 4];
        if (n[0x14 / 4] != 0) {
            n[0x4 / 4] = 1;
        }
        n[0x14 / 4] = (int)p;
    }
    if (((int)a1 << 8) >= 0) {
        p[0x6C0 / 4] = 0;
    } else {
        int *n6b8 = (int *)titproc_uso_func_001B10(0);
        p[0x6B8 / 4] = (int)n6b8;
        titproc_uso_func_07ACE0((char *)p + 0x10, n6b8);
        if (n6b8[0x14 / 4] != 0) {
            n6b8[0x4 / 4] = 1;
        }
        n6b8[0x14 / 4] = (int)p;
        p[0x6C0 / 4] = (int)import_000A5D38(0);
        import_000A5F40((int *)p[0x6C0 / 4], p);
        titproc_uso_func_0022BC(p);
        {
            int *n6c0 = (int *)p[0x6C0 / 4];
            n6c0[0x30 / 4] = (int)import_0024CCF4(0, &titproc_uso_D_00052C, 0x48, 0xDD, 3, 13);
            *(float *)((char *)n6c0 + 0x74) = 17.0f;
        }
        import_000A5FBC((int *)p[0x6C0 / 4]);
        titproc_uso_func_00F4CC((int *)p[0x6C0 / 4]);
        *(int *)((char *)p[0x6C0 / 4] + 0x7C) = *(int *)((char *)&import_00020098 + 0x84);
        titproc_uso_func_07ACE0((char *)p + 0x10, (int *)p[0x6C0 / 4]);
        {
            int *n = (int *)p[0x6C0 / 4];
            if (n[0x14 / 4] != 0) {
                n[0x4 / 4] = 1;
                n[0x14 / 4] = (int)p;
            } else {
                p[0x6C0 / 4] = 0;
            }
        }
    }
    p[0x6C4 / 4] = 0;
    {
        int *node = *(int **)((char *)&import_00020098 + 0x190);
        titproc_uso_func_07ACE0((char *)p + 0x10, node);
        if (node[0x14 / 4] != 0) {
            node[0x4 / 4] = 1;
            node[0x14 / 4] = (int)p;
        }
        titproc_uso_func_0139B0(*(int **)((char *)&import_00020098 + 0x190), 1, 0);
        titproc_uso_func_074840();
        import_000A7ECC(&import_00020098, 0);
    }
    return (void *)p;
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

extern int titproc_uso_D_count_22BC;
extern int titproc_uso_D_target_22BC;
extern int titproc_uso_D_arg0_22BC, titproc_uso_D_arg1_22BC, titproc_uso_D_arg2_22BC, titproc_uso_D_arg3_22BC, titproc_uso_D_arg4_22BC, titproc_uso_D_arg5_22BC, titproc_uso_D_arg6_22BC;
/* titproc_uso_func_000022BC: per-frame init orchestrator — submit 7 display
 * lists, then reset slot 0x128. BYTE-EXACT (336 bytes), ported from its
 * masked-hash twin donor titproc_uso_func_0000101C (84-word identical body,
 * only struct offset 0x5C->0x6C0 differs). Reading the count global directly
 * (no `register`) is what makes IDO pin %hi/%lo in $s1 across the 7 calls —
 * the residual the prior register-based NM attempt couldn't crack. */
void titproc_uso_func_000022BC(int *a0) {
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0));
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 1, 0, &titproc_uso_D_arg0_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 2, 1, &titproc_uso_D_arg1_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 3, 2, &titproc_uso_D_arg2_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 6, 3, &titproc_uso_D_arg3_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 4, 4, &titproc_uso_D_arg4_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 7, 5, &titproc_uso_D_arg5_22BC);
    gl_func_00000000(*(int*)((char*)a0 + 0x6C0), ((titproc_uso_D_count_22BC + 1) << 16) | 5, 6, &titproc_uso_D_arg6_22BC);
    if (gl_func_00000000(*(int*)((char*)&titproc_uso_D_target_22BC + 0xC4)) == 0) {
        *(int*)((char*)*(int**)((char*)a0 + 0x6C0) + 0x128) = 0;
    }
}

/* titproc_uso_func_0000240C - verified structural decode; SIBLING of
 * titproc_uso_func_000026FC (the titproc state-machine family).
 * Documented switch + vtable + branch-likely sub-80 ceiling ->
 * INCLUDE_ASM build path; struct-typing reference.
 *   s0 = a0;
 *   if (s0->0x6C0 == 0) goto end;                 // 1728 active gate
 *   switch (s0->0x6C4) {                          // 1732 state
 *     case 0:
 *        if (s0->0x6B4 != 0) gl_func_00000000(s0->0x6B4);   // 1716
 *        if (*(u16*)(*(int*)(&D+0x154) + 4) & 0x8) {
 *            gl_func_00000000(144);
 *            v1 = (int*)s0->0x6B8;                            // 1720
 *            (*(fn)((int*)v1->0x28)->0x5C)(
 *                (short)((int*)v1->0x28)->0x58 + (int)v1);    // vtable idiom
 *        }
 *        if (s0->0x6B0 != 0) gl_func_00000000(...);           // 1712
 *        s0->0x6C4 = 2;
 *        v1=(int*)s0->0x6C0; (*(fn)v1->0x28->0x5C)(...);      // vtable
 *        break;
 *     case 1: ...   case 2: ...   default: goto end;
 *   }
 * end: ...
 * Struct-typing: cross-confirms the titproc state-machine family -
 * s0->0x6C0 (1728) active/handle gate, s0->0x6C4 (1732) state selector
 * (0/1/2), s0->0x6B0/0x6B4/0x6B8 (1712/1716/1720) sub-handles,
 * D[0x154]->0x4 (u16) flag bit 0x8, obj->0x28 vtable {fn@0x5C,
 * short@0x58} dispatch (the engine-wide obj-dispatch idiom, 0x5C/0x58
 * variant). Per-state runs cleanup/vtable-notify then transitions
 * state. Caps <80: beql switch dispatch + vtable jalr + branch-likely
 * + &D reloc. Full per-state body INCLUDE_ASM-preserved (.s = source
 * of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
#ifdef NON_MATCHING
void titproc_uso_func_0000240C(char *s0) {
    char *v1;
    if (*(int *)(s0 + 0x6C0) == 0) return;
    switch (*(int *)(s0 + 0x6C4)) {
        case 0:
            if (*(int *)(s0 + 0x6B4) != 0) gl_func_00000000(*(int *)(s0 + 0x6B4));
            if (*(unsigned short *)(*(int *)((char *)&D_00000000 + 0x154) + 4) & 0x8) {
                gl_func_00000000(144);
                v1 = *(char **)(s0 + 0x6B8);
                {
                    char *vt = *(char **)(v1 + 0x28);
                    void (*fn)(char *) = *(void (**)(char *))(vt + 0x5C);
                    short base = *(short *)(vt + 0x58);
                    if (fn) fn((char *)((int)base + (int)v1));
                }
            }
            if (*(int *)(s0 + 0x6B0) != 0) gl_func_00000000(*(int *)(s0 + 0x6B0));
            *(int *)(s0 + 0x6C4) = 2;
            v1 = *(char **)(s0 + 0x6C0);
            {
                char *vt = *(char **)(v1 + 0x28);
                void (*fn)(char *) = *(void (**)(char *))(vt + 0x5C);
                if (fn) fn(v1);
            }
            break;
        case 1:
            if (*(int *)(*(char **)(s0 + 0x6BC) + 0x3C) == 0 &&
                gl_func_00000000((char *)&D_00000000, 0x200) != 0) {
                gl_func_00000000(0x802);
                gl_func_00000000(*(int *)(s0 + 0x6C0));
                v1 = *(char **)(s0 + 0x6B4);
                if (v1 != 0) {
                    char *vt = *(char **)(v1 + 0x28);
                    void (*fn)(char *) = *(void (**)(char *))(vt + 0x5C);
                    short base = *(short *)(vt + 0x58);
                    if (fn) fn((char *)((int)base + (int)v1));
                }
                if (*(int *)(s0 + 0x6B0) != 0) gl_func_00000000(*(int *)(s0 + 0x6B0));
                *(int *)(s0 + 0x6C4) = 0;
            } else {
                gl_func_00000000(*(int *)(s0 + 0x6C0));
                gl_func_00000000(5);
                v1 = *(char **)(s0 + 0x6C0);
                if (*(int *)(v1 + *(int *)(v1 + 0x7C) * 40 + 0x90) == 0) return;
                *(int *)((char *)&D_00000000 + 0xA8) = (int)s0;
                *(int *)((char *)&D_00000000 + 0x84) = *(int *)(*(char **)(s0 + 0x6C0) + 0x7C);
                if ((*(int *)(s0 + 0x4F0) << 4) < 0) {
                    if (*(int *)(s0 + 0x528) != 0) {
                        gl_func_00000000(*(int *)(s0 + 0x528), 3);
                    }
                    *(int *)(s0 + 0x528) = 0;
                    *(int *)((char *)&D_00000000 + 0x14C) = 0;
                }
                v1 = *(char **)(s0 + 0x6C0);
                (*(void (**)(void))(v1 + *(int *)(v1 + 0x7C) * 40 + 0x90))();
            }
            break;
        case 2:
            gl_func_00000000(5);
            {
                int *d154 = *(int **)((char *)&D_00000000 + 0x154);
                unsigned short v = *(unsigned short *)((char *)d154 + 4);
                gl_func_00000000((char *)&D_00000000);
                *(short *)((char *)d154 + 4) = (short)(v & 0xFFF7);
            }
            gl_func_00000000(*(int *)(s0 + 0x6B8));
            v1 = *(char **)(s0 + 0x6C0);
            {
                char *vt = *(char **)(v1 + 0x28);
                void (*fn)(char *) = *(void (**)(char *))(vt + 0x5C);
                short base = *(short *)(vt + 0x58);
                if (fn) fn((char *)((int)base + (int)v1));
            }
            *(int *)(s0 + 0x6C4) = 1;
            break;
        default:
            return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_0000240C);
#endif

void titproc_uso_func_00000000();

void titproc_uso_func_000026D0(int *a0) {
    int *p = *(int**)((char*)a0 + 0x6C0);
    if (p == 0) return;
    titproc_uso_func_00000000(p);
}

/* titproc_uso_func_000026FC — verified structural decode (113-insn scroll/
 * slider state machine; heavy beql/bnel/bgtzl branch-likely + 8 calls =
 * documented sub-80 ceiling → INCLUDE_ASM build path; struct-typing ref).
 * Struct-typing: s0->0x6C0 active flag, 0x6C4 state (==2 special, ==0
 * skip), 0x6B8 handle, 0x6AC obj(->0x44->0x34 gate), 0x6BC scroll obj
 * (->0x3C int offset clamped 0..255 / 256→720 / -16 / ≥0→0; ->0x28
 * vtable {fn@0x64, short@0x60}), 0x4F0 flag word (bit-17, &0xffff),
 * 0x4F4 derived counter, 0x528 list, D[0x134] global.
 * 2026-05-31 FULL DECODE: the previously-truncated else-branch (func(s0);
 * func(root[0xC4][0x800], 0); func(arg, o528[8][8], o528[8][4]); func(s0);
 * 0x4F4 = 0x4F0 & 0xffff), the dec_path (0x4F4>0 → 6BC[0x3C] -= 16, clamp ≥0),
 * and the tail (6AC->0x44->0x34 gate → func(6C0); func(s0,-1,0)) are now
 * decoded. Two merge labels: `final` (28a4 = func(s0)) vs `ret` (28ac,
 * else-branch skips the final call). Structure now byte-aligns (113/107);
 * residual is frame 0x38 vs 0x30 (extra locals) + register-renumber + &D
 * deferred-pool scheduling — a regalloc/symbolization ceiling, not structural.
 * INCLUDE_ASM remains build path. */
#ifdef NON_MATCHING
void titproc_uso_func_000026FC(char *s0) {
    char *v1;
    int *vt;
    int a1;
    int a0v;

    if (*(int*)(s0 + 0x6C0) != 0 && *(int*)(s0 + 0x6C4) == 2) {
        gl_func_00000000(*(int*)(s0 + 0x6B8));
    }
    if (*(int*)(s0 + 0x6C4) == 0) goto tail;

    if (*(int*)((char*)*(int**)((char*)*(int**)(s0 + 0x6AC) + 0x44) + 0x34) == 0) {
        if (*(int*)(s0 + 0x4F4) > 0) goto dec_path;
    }
    v1 = *(char**)(s0 + 0x6BC);
    if (*(int*)(v1 + 0x3C) < 255) {
        *(int*)(v1 + 0x3C) += 16;
        if (*(int*)(*(char**)(s0 + 0x6BC) + 0x3C) < 256) goto final;
        *(int*)(*(char**)(s0 + 0x6BC) + 0x3C) = 720;
        goto final;
    }
    a1 = *(int*)(s0 + 0x4F0);
    if ((a1 << 14) >= 0) {
        vt = *(int**)(*(char**)(s0 + 0x6BC) + 0x28);
        (*(void (**)(char*))((char*)vt + 0x64))(
            (char*)((int)(short)*(short*)((char*)vt + 0x60) + (int)*(char**)(s0 + 0x6BC)));
        goto final;
    } else {
        char *rc4 = *(char**)(*(char**)((char*)&D_00000000 + 0x134) + 0xC4);
        int arg = *(int*)(rc4 + 0x800);
        char *o528;
        gl_func_00000000(s0);
        gl_func_00000000(arg, 0);
        o528 = *(char**)(s0 + 0x528);
        gl_func_00000000(arg, *(int*)(*(char**)(o528 + 8) + 8),
                         *(int*)(*(char**)(o528 + 8) + 4));
        gl_func_00000000(s0);
        *(int*)(s0 + 0x4F4) = *(int*)(s0 + 0x4F0) & 0xFFFF;
        goto ret;
    }

dec_path:
    v1 = *(char**)(s0 + 0x6BC);
    if (*(int*)(v1 + 0x3C) > 0) {
        *(int*)(v1 + 0x3C) -= 16;
        v1 = *(char**)(s0 + 0x6BC);
        if (*(int*)(v1 + 0x3C) < 0) *(int*)(v1 + 0x3C) = 0;
    }
    goto final;

tail:
    if (*(int*)((char*)*(int**)((char*)*(int**)(s0 + 0x6AC) + 0x44) + 0x34) == 0 &&
        *(int*)(s0 + 0x4F4) > 0) {
        goto final;
    }
    a0v = *(int*)(s0 + 0x6C0);
    if (a0v != 0) {
        gl_func_00000000(a0v);
    }
    gl_func_00000000(s0, -1, 0);

final:
    gl_func_00000000(s0);
ret:
    ;
}
#else
INCLUDE_ASM("asm/nonmatchings/titproc_uso/titproc_uso", titproc_uso_func_000026FC);
#endif

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

/* titproc_uso_func_00002980: 36-insn (0x90) alloc-and-link node helper.
 * BYTE-IDENTICAL sibling of eddproc_uso_func_000003BC / mgrproc_uso_func_00003358.
 * The "frame-0x20-vs-0x28 spill cap" was a MISDIAGNOSIS — porting the exact
 * matched two-web sibling body (p1/p2 split + decl order p2,head,p1 + reload of
 * arg0[0x40] for the second condition) reproduces the frame-0x28 two-web spill
 * shape byte-for-byte. Do not "simplify" the reuse or the re-load; they are
 * load-bearing for the register/slot allocation. The trailing all-zero
 * _pad.s word is legit alignment data (no instruction-faking).
 * --- prior misdiagnosis kept for archaeology below ---
 * Sibling of mgrproc_uso_func_00003358 (same frame/regalloc cap class).
 *
 * Structure (decoded from asm 0x2980-0x2A0C). The three jals are DISTINCT
 * intra-USO (runtime-relocated, =0 in undefined_syms_auto.txt) targets, not
 * the gl_func_00000000 placeholder; the prior decode collapsed all three
 * into gl_func_00000000 and wrote &D_00000000 where the asm actually loads
 * &import_0006ED80 — both fixed here so the relocs/symbols match the target:
 *   p = func_055750(0x40)
 *   if (p != 0) {
 *       func_051C28(p)                     ; init call (1 arg)
 *       p[0x28] = &import_0006ED80
 *       p[0x3C] = 0
 *   }
 *   q = a0->[0x40]                          ; original-a0 reloaded from home
 *   if (q != 0) {
 *       func_07ACE0(p + 0x10, q)           ; link call (2 args)
 *       if (q->[0x14] != 0) q->[0x4] = 1
 *       q->[0x14] = p
 *   }
 *   return p
 *
 * NM cap (frame 0x20 vs target 0x28; 11/36 insns match): pure IDO spill-slot
 * allocation. Target reloads `p` into $a0 after call 1, then reuses $a0 for
 * `p+0x10` (clobber) which forces an `or $v1,$a0` survivor copy at the merge
 * — splitting `p` into two spill webs (0x1C around call 1, 0x24 around call
 * 2 → frame 0x28). IDO instead keeps our `p` in $a2 across both regions (one
 * slot 0x1C reused, frame 0x20) and sets $a2 eagerly in the beq delay slot
 * for the p==0 path. A 2-variable split (r = p) coalesces and does not split
 * the web; no natural-C lever observed to force the $a0-reuse/$v1-survivor
 * shape. Same cap class as mgrproc 33358. INSN_PATCH removed 2026-05-23. */
extern int titproc_uso_func_055750();
extern int titproc_uso_func_051C28();
extern int titproc_uso_func_07ACE0();
extern char import_0006ED80;
void *titproc_uso_func_00002980(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)titproc_uso_func_055750(0x40);
    if (p1 != 0) {
        titproc_uso_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_0006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        titproc_uso_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}


/* titproc_uso_func_00002A10: last function in the segment — a 2-insn
 * `void f(int a0){}` save-arg sentinel (jr ra; sw a0,0(sp)). splat declared
 * size 0x1C, absorbing 0x14 of segment-tail data; corrected by shrinking the
 * .s to 0x8 and emitting the trailing data as a local block below. */
void titproc_uso_func_00002A10(int a0) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_tail_data.s")
#pragma GLOBAL_ASM("asm/nonmatchings/titproc_uso/titproc_uso/titproc_uso_func_00002980_pad.s")

/* titproc_uso_func_000016E8: orphan absorbed by C-emit of _000016B8
 * (decl 0x30, .o 0x58 — +0x28 bytes absorb the 40-byte orphan at vram
 * 0x16E8). C-emit-absorbed variant per docs/MATCHING_WORKFLOW.md. */

/* titproc_uso_func_00001C60 (2-word orphan: lui at,0x3F80; mtc1 at,$f0 = 1.0f)
 * was the stolen prologue of func_00001C68 — forward-merged into it (orphan removed). */
/* titproc_uso_func_000001DC (2-word orphan: lui v0,0; addiu v0,0) was the stolen
 * prologue of func_000001E4 — forward-merged into it (orphan-fn removed). */
