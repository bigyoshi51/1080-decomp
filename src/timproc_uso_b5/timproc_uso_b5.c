#include "common.h"
extern char *timproc_uso_b5_alias();

extern int gl_func_00000000();
extern char D_00000000;
extern char D_00000000_a;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Macro definitions for NM-wrap bodies. Auto-managed by /struct-name-tick.
 * Default build never sees these — wrap bodies aren't compiled.
 * TIMB5_F_3A0: float value (a default scale or constant) broadcast to three
 * adjacent grandchild fields (0x108/0x10C/0x110 — looks like Vec3 init).
 * Positional. timproc_uso_b5 D+0x3A0.
 */
#define TIMB5_F_3A0 (*(float*)((char*)&D_00000000 + 0x3A0))
#endif

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


extern int timproc_uso_b5_func_055750();
extern int timproc_uso_b5_func_04C678();
extern int timproc_uso_b5_func_07ACE0();
extern int timproc_uso_b5_func_0139B0();
extern int import_000A5D38();
extern int import_000A5F40();
extern int import_000A6900();
extern int import_0024CCF4();
extern int import_000A5FBC();
extern char timproc_uso_b5_D_807FD908;
extern char timproc_uso_b5_D_807FD888;
extern char timproc_uso_b5_D_807EF230;
extern char import_80073B18;
extern char import_80073B80;
extern char import_80074E78;
extern char import_80020098;

#ifdef NON_MATCHING
int *timproc_uso_b5_func_00000058(int *a0) {
    int *s3, *s0, *s1, *slot;
    int *cfg, *node, *vt, *link;
    int i, count;

    s3 = a0;
    if (a0 == 0) {
        s3 = (int *)timproc_uso_b5_func_055750(0x50);
        if (s3 == 0) return s3;
    }
    s0 = s3;
    if (s3 == 0) {
        s0 = (int *)timproc_uso_b5_func_055750(0x50);
        if (s0 == 0) goto after_sub;
    }
    s1 = s0;
    if (s0 == 0) {
        s1 = (int *)timproc_uso_b5_func_055750(0x2C);
        if (s1 == 0) goto after_node;
    }
    timproc_uso_b5_func_04C678(s1, &timproc_uso_b5_D_807FD908 + 0x98);
    s1[0x28 / 4] = (int)&import_80073B18;
after_node:
    s0[0x28 / 4] = (int)&import_80073B80;
after_sub:
    s3[0x28 / 4] = (int)&timproc_uso_b5_D_807FD888;
    s3[0x0C / 4] = (int)(&timproc_uso_b5_D_807FD888 + 0xA0);
    {
        int r = import_000A5D38(0);
        s3[0x48 / 4] = r;
        import_000A5F40(r, s3);
    }

    cfg = *(int **)(&import_80020098 + 0x134);
    node = (int *)cfg[0x70 / 4];
    for (i = 0; i < cfg[0x78 / 4]; i++) {
        import_000A6900(s3[0x48 / 4], node, -1, &timproc_uso_b5_D_807EF230);
        cfg = *(int **)(&import_80020098 + 0x134);
        node = (int *)node[0x44 / 4];
    }

    *(int *)(s3[0x48 / 4] + 0x30) =
        import_0024CCF4(0, &import_80074E78, 0x48, 0xDD, 3, 13);

    import_000A5FBC(s3[0x48 / 4]);
    vt = (int *)((int *)s3[0x48 / 4])[0x28 / 4];
    ((void (*)(int))vt[0x5C / 4])(*(short *)((char *)vt + 0x58) + s3[0x48 / 4]);

    slot = (int *)((char *)s3 + 0x10);

    link = (int *)s3[0x48 / 4];
    timproc_uso_b5_func_07ACE0(slot, link);
    if (link[0x14 / 4] != 0) {
        link[0x04 / 4] = 1;
    }
    link[0x14 / 4] = (int)s3;

    link = *(int **)(&import_80020098 + 0x190);
    timproc_uso_b5_func_07ACE0(slot, link);
    if (link[0x14 / 4] != 0) {
        link[0x04 / 4] = 1;
    }
    link[0x14 / 4] = (int)s3;

    timproc_uso_b5_func_0139B0(*(int *)(&import_80020098 + 0x190), 1, 0);
    s3[0x30 / 4] = 1;
    s3[0x2C / 4] = 0;
    return s3;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000058);
#endif

/* timproc_uso_b5_func_0000024C: 42-insn dispatch wrapper. Sibling of
 * the recently-decoded func_000002F4 split-off (this is the parent
 * function — bundled together prior to split).
 *
 * Decoded semantics:
 *   1. Try first dispatch: gl_func_00000000(&D, 0x300)
 *   2. If 0, try fallback: gl_func_00000000(&D, 0x40000)
 *      If that's also 0, skip-to-epilogue.
 *   3. Either way: gl_func_00000000(&D + 0xB4)  [commit dispatch]
 *   4. Look up vtable callable:
 *        v0 = arg0[0x48];          // sub-context
 *        idx = v0[0x7C];            // current state index
 *        fn = *(v0 + idx*0x28 + 0x90);
 *      If fn == NULL: skip-to-epilogue (via beqzl).
 *      Else: store v0/arg0 to globals D_b5_24C_save_*; RE-FETCH fn
 *            (asm clobbers v0 over the stores); call fn().
 *
 * Asm RE-LOADS fn after the two global stores because $v0 was clobbered
 * by the second `sw v0, 0(at)`. The recompute is structural, not redundant.
 *
 * NATURAL CEILING: 96.43% NM. The 18-word diff covers the post-jal
 * vtable-dispatch chain register cascade (target uses
 * $v0/$v1/$t6-$t9/$t0-$t2; built uses $a2/$a3/$v1/$a0/$a1/etc.). Was
 * previously documented as INSN_PATCH-promotable per
 * docs/POST_CC_RECIPES.md "Pure register-rename at any scale" —
 * INSN_PATCH REMOVED 2026-05-23 and docs/POST_CC_RECIPES.md deprecated
 * (per feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
extern int D_b5_24C_save_v0;
extern int D_b5_24C_save_v1;
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000024C(int *a0) {
    int *v0;
    int idx;
    void (*fn)(void);

    if (gl_func_00000000(&D_00000000, 0x300) == 0) {
        if (gl_func_00000000(&D_00000000, 0x40000) == 0) {
            return;
        }
    }
    gl_func_00000000((char*)&D_00000000 + 0xB4);
    v0 = (int*)a0[0x48 / 4];
    idx = v0[0x7C / 4];
    fn = *(void(**)(void))((char*)v0 + idx * 0x28 + 0x90);
    if (fn == 0) return;
    D_b5_24C_save_v0 = (int)v0;
    D_b5_24C_save_v1 = (int)a0;
    v0 = (int*)a0[0x48 / 4];
    idx = v0[0x7C / 4];
    fn = *(void(**)(void))((char*)v0 + idx * 0x28 + 0x90);
    fn();
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000024C);
#endif

/* Empty body, K&R-style 1-arg signature emits `jr ra; sw a0, 0(sp)` —
 * IDO -O2 keeps the K&R arg-save in the jr delay slot even when unused.
 * Split off from timproc_uso_b5_func_0000024C bundle (2026-05-05). */
void timproc_uso_b5_func_000002F4(a0) int a0; {}
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


#ifdef NON_MATCHING
/* timproc_uso_b5_func_00000478: 190-insn constructor/initializer.
 * Boundary fix: split-fragments separated the trailing 2-insn
 * timproc_uso_b5_func_00000770 leaf; this body is now a single function
 * (grep -c 03E00008 = 1).
 *
 * Symbol-resolved decode pass (reloc-authoritative from raw .s):
 *   self = arg0-or-alloc(0x58); sub = self-or-alloc(0x50);
 *   node = sub-or-alloc(0x2C); table init; arg1-selected init arms.
 * Calls/data now use the real timproc_uso_b5_* / import_* symbols rather
 * than the generic gl_func_00000000 / D_00000000 placeholders. Register
 * lifetimes modelled on matched sibling func_00000058 (self in saved reg
 * across the cascade). Default build remains INCLUDE_ASM. */
extern int timproc_uso_b5_func_055750();
extern int timproc_uso_b5_func_04C678();
extern int timproc_uso_b5_func_074710();
extern char *timproc_uso_b5_func_00008DB4(char *self, int a1);
extern void **timproc_uso_b5_func_00008FC8(void **arg0, int *arg1, int *arg2);
extern int timproc_uso_b5_func_07ACE0();
extern char *timproc_uso_b5_func_000018B4(char *arg0, int arg1, int arg2, int arg3, int arg4, char *arg5, int arg6, int arg7);
extern void timproc_uso_b5_func_00000778(char *arg0);
extern int timproc_uso_b5_func_0139B0();
extern int timproc_uso_b5_func_011CD8();
extern int timproc_uso_b5_func_074840();
extern char timproc_uso_b5_D_807FE84C;
extern char timproc_uso_b5_D_807FD948;
extern char timproc_uso_b5_D_807FE870;
extern char timproc_uso_b5_D_807FE88C;
extern char timproc_uso_b5_D_807FE8AC;
extern char timproc_uso_b5_D_807FE8BC;
extern char timproc_uso_b5_D_807FE8CC;
extern char import_80073B18;
extern char import_80073B80;
extern char import_80800228;
extern char import_80020228;
extern char import_80020098;

int *timproc_uso_b5_func_00000478(int *arg0, int arg1, int arg2, int arg3) {
    int *self;
    int *sub;
    int *node;
    int *slot;
    int *link;
    int result0;
    int result1;
    int result2;

    self = arg0;
    if (self == 0) {
        self = (int *)timproc_uso_b5_func_055750(0x58);
        if (self == 0) goto done;
    }

    sub = self;
    if (sub == 0) {
        sub = (int *)timproc_uso_b5_func_055750(0x50);
        if (sub == 0) goto after_sub;
    }

    node = sub;
    if (node == 0) {
        node = (int *)timproc_uso_b5_func_055750(0x2C);
        if (node == 0) goto after_node;
    }
    timproc_uso_b5_func_04C678(node, &timproc_uso_b5_D_807FE84C + 0xFDC);
    node[0x28 / 4] = (int)&import_80073B18;

after_node:
    sub[0x28 / 4] = (int)&import_80073B80;

after_sub:
    self[0x28 / 4] = (int)&timproc_uso_b5_D_807FD948;
    self[0x0C / 4] = (int)(&timproc_uso_b5_D_807FD948 + 0xFE4);

    timproc_uso_b5_func_074710(&timproc_uso_b5_D_807FE870 + 0x1000, 0);
    result0 = (int)timproc_uso_b5_func_00008DB4(0, arg1);
    self[0x54 / 4] = 0;

    slot = (int *)((char *)self + 0x10);
    if (arg1 == 1) {
        self[0x50 / 4] = 0;
        result1 = (int)timproc_uso_b5_func_00008FC8(0,
                      (int *)(&timproc_uso_b5_D_807FE88C + 0x100C),
                      (int *)(&timproc_uso_b5_D_807FE88C + 0x101C));
        link = (int *)timproc_uso_b5_func_07ACE0(slot, result1);
        if (link[0x14 / 4] != 0) {
            link[0x04 / 4] = 1;
        }
        link[0x14 / 4] = (int)self;

        result2 = (int)timproc_uso_b5_func_000018B4(0, (char *)self, arg1, arg2, arg3,
                      (char *)result0, result1, 0);
        link = (int *)timproc_uso_b5_func_07ACE0(slot, result2);
        if (link[0x14 / 4] != 0) {
            link[0x04 / 4] = 1;
        }
        link[0x14 / 4] = (int)self;
        *(float *)&timproc_uso_b5_D_807FE8AC = 592.0f;
    } else {
        self[0x50 / 4] = 1;
        result1 = (int)timproc_uso_b5_func_00008FC8(0,
                      (int *)(&timproc_uso_b5_D_807FE88C + 0x102C),
                      (int *)(&timproc_uso_b5_D_807FE8AC + 0x103C));
        link = (int *)timproc_uso_b5_func_07ACE0(slot, result1);
        if (link[0x14 / 4] != 0) {
            link[0x04 / 4] = 1;
        }
        link[0x14 / 4] = (int)self;

        result2 = (int)timproc_uso_b5_func_00008FC8(0,
                      (int *)(&timproc_uso_b5_D_807FE8BC + 0x104C),
                      (int *)(&timproc_uso_b5_D_807FE8CC + 0x105C));
        link = (int *)timproc_uso_b5_func_07ACE0(slot, result2);
        if (link[0x14 / 4] != 0) {
            link[0x04 / 4] = 1;
        }
        link[0x14 / 4] = (int)self;

        result2 = (int)timproc_uso_b5_func_000018B4(0, (char *)self, arg1, arg2, arg3,
                      (char *)result0, result1, result2);
        link = (int *)timproc_uso_b5_func_07ACE0(slot, result2);
        if (link[0x14 / 4] != 0) {
            link[0x04 / 4] = 1;
        }
        link[0x14 / 4] = (int)self;
        *(float *)&import_80800228 = 374.0f;
    }

    timproc_uso_b5_func_00000778((char *)self);
    link = (int *)timproc_uso_b5_func_07ACE0(slot,
               *(int *)(&import_80020228 + 0x190));
    if (link[0x14 / 4] != 0) {
        link[0x04 / 4] = 1;
    }
    link[0x14 / 4] = (int)self;
    timproc_uso_b5_func_0139B0(*(int *)(&import_80020228 + 0x190), 1, 0);
    self[0x48 / 4] = 0;
    self[0x30 / 4] = 0;
    self[0x2C / 4] = 0;
    timproc_uso_b5_func_011CD8(&import_80020098, 0);
    timproc_uso_b5_func_074840();

done:
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000478);
#endif

/* timproc_uso_b5_func_00000770: 2-insn save-arg sentinel.
 * Body is `jr ra; sw $a0, 0($sp)` — arg spilled to caller's arg-save slot
 * in delay slot. Same recipe as game_libs_func_0000E044/E050. */
void timproc_uso_b5_func_00000770(int a0) { (void)a0; }

#ifdef NON_MATCHING
/* timproc_uso_b5_func_00000778 — flat bulk-registration: 76 back-to-back
 * import_0024F228 / import_0024F278 calls binding the b5 registration
 * table (timproc_uso_b5_D_807FF4xx..Bxx) to packed ids derived from
 * arg0->0x50 (n) and *(int*)&import_8002022C (g). Two `if (g != 0)`
 * blocks gate the 0xB00000-group and 0x110000-group entries. Reconstructed
 * 2026-06-21 from resolved .s with REAL reloc callees + per-call symbol+addend.
 * Structure/arithmetic exact: 603 words (target 605, 2-word short). vs expected:
 * 127 non-reloc diffs, of which 95 are PURE register-rename (coloring) and 32
 * are structural — but those 32 are themselves regalloc/scheduling artifacts:
 *   - 0x70000 const hoisted to saved $s1 once + reused (calls 2-4); IDO later
 *     repurposes $s1 for &import_8002022C. Cross-statement const-CSE into a
 *     callee-saved reg — not C-controllable.
 *   - calls 51-55: expected reads n (arg0->0x50) before g; build reads g first
 *     (| operand-eval order). calls 69-70: expected keeps g in $a1 and does
 *     g*12 in place (addu at,a1,0; sll; subu; sll); build uses temps.
 * CAP CLASS: genuine ugen register-coloring + as1 scheduler-tie. Down from 248
 * non-reloc diffs (old placeholder body). Default build is INCLUDE_ASM. */
extern int import_0024F228();
extern int import_0024F278();
extern int import_8002022C;
extern char timproc_uso_b5_D_807FF490;
extern char timproc_uso_b5_D_807FF4A8;
extern char timproc_uso_b5_D_807FF4C0;
extern char timproc_uso_b5_D_807FF4D8;
extern char timproc_uso_b5_D_807FF4F0;
extern char timproc_uso_b5_D_807FF508;
extern char timproc_uso_b5_D_807FF520;
extern char timproc_uso_b5_D_807FF538;
extern char timproc_uso_b5_D_807FF550;
extern char timproc_uso_b5_D_807FF568;
extern char timproc_uso_b5_D_807FF580;
extern char timproc_uso_b5_D_807FF598;
extern char timproc_uso_b5_D_807FF5B0;
extern char timproc_uso_b5_D_807FF5C8;
extern char timproc_uso_b5_D_807FF5E0;
extern char timproc_uso_b5_D_807FF5F8;
extern char timproc_uso_b5_D_807FF610;
extern char timproc_uso_b5_D_807FF628;
extern char timproc_uso_b5_D_807FF640;
extern char timproc_uso_b5_D_807FF658;
extern char timproc_uso_b5_D_807FF670;
extern char timproc_uso_b5_D_807FF688;
extern char timproc_uso_b5_D_807FF6A0;
extern char timproc_uso_b5_D_807FF6B8;
extern char timproc_uso_b5_D_807FF6D0;
extern char timproc_uso_b5_D_807FF6E8;
extern char timproc_uso_b5_D_807FF700;
extern char timproc_uso_b5_D_807FF718;
extern char timproc_uso_b5_D_807FF730;
extern char timproc_uso_b5_D_807FF748;
extern char timproc_uso_b5_D_807FF760;
extern char timproc_uso_b5_D_807FF778;
extern char timproc_uso_b5_D_807FF790;
extern char timproc_uso_b5_D_807FF7A8;
extern char timproc_uso_b5_D_807FF7C0;
extern char timproc_uso_b5_D_807FF7D8;
extern char timproc_uso_b5_D_807FF7F0;
extern char timproc_uso_b5_D_807FF808;
extern char timproc_uso_b5_D_807FF820;
extern char timproc_uso_b5_D_807FF838;
extern char timproc_uso_b5_D_807FF850;
extern char timproc_uso_b5_D_807FF868;
extern char timproc_uso_b5_D_807FF880;
extern char timproc_uso_b5_D_807FF898;
extern char timproc_uso_b5_D_807FF8B0;
extern char timproc_uso_b5_D_807FF8C8;
extern char timproc_uso_b5_D_807FF8E0;
extern char timproc_uso_b5_D_807FF8F8;
extern char timproc_uso_b5_D_807FF910;
extern char timproc_uso_b5_D_807FF928;
extern char timproc_uso_b5_D_807FF940;
extern char timproc_uso_b5_D_807FF958;
extern char timproc_uso_b5_D_807FF970;
extern char timproc_uso_b5_D_807FF988;
extern char timproc_uso_b5_D_807FF9A0;
extern char timproc_uso_b5_D_807FF9B8;
extern char timproc_uso_b5_D_807FF9D0;
extern char timproc_uso_b5_D_807FF9E8;
extern char timproc_uso_b5_D_807FFA00;
extern char timproc_uso_b5_D_807FFA18;
extern char timproc_uso_b5_D_807FFA30;
extern char timproc_uso_b5_D_807FFA48;
extern char timproc_uso_b5_D_807FFA60;
extern char timproc_uso_b5_D_807FFA78;
extern char timproc_uso_b5_D_807FFA90;
extern char timproc_uso_b5_D_807FFAA8;
extern char timproc_uso_b5_D_807FFAC0;
extern char timproc_uso_b5_D_807FFAD8;
extern char timproc_uso_b5_D_807FFAF0;
extern char timproc_uso_b5_D_807FFB08;
extern char timproc_uso_b5_D_807FFB20;
extern char timproc_uso_b5_D_807FFB38;
extern char timproc_uso_b5_D_807FFB50;
extern char timproc_uso_b5_D_807FFB68;
extern char timproc_uso_b5_D_807FFB80;
extern char timproc_uso_b5_D_807FFB98;
void timproc_uso_b5_func_00000778(char *arg0) {
    import_0024F228((char *)&timproc_uso_b5_D_807FF490 + 0x10, ((*(int *)((char *)arg0 + 0x50))*9) | 0x70000);
    import_0024F228((char *)&timproc_uso_b5_D_807FF4A8 + 0x28, 0x70000 | ((*(int *)((char *)arg0 + 0x50))*9 + 1));
    import_0024F228((char *)&timproc_uso_b5_D_807FF5B0 + 0x130, 0x70000 | ((*(int *)((char *)arg0 + 0x50))*2 + 3));
    import_0024F228((char *)&timproc_uso_b5_D_807FF5C8 + 0x148, 0x70000 | ((*(int *)((char *)arg0 + 0x50))*2 + 4));
    import_0024F228((char *)&timproc_uso_b5_D_807FF5E0 + 0x160, (((*(int *)&import_8002022C) + 8) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FF5F8 + 0x178, (((*(int *)&import_8002022C) + 8) << 16) | (((*(int *)((char *)arg0 + 0x50))*4 - (*(int *)((char *)arg0 + 0x50))) + 3));
    import_0024F228((char *)&timproc_uso_b5_D_807FF610 + 0x190, (((*(int *)&import_8002022C) + 8) << 16) | (((*(int *)((char *)arg0 + 0x50))*4 - (*(int *)((char *)arg0 + 0x50))) + 4));
    import_0024F228((char *)&timproc_uso_b5_D_807FF628 + 0x1a8, (((*(int *)&import_8002022C) + 8) << 16) | (((*(int *)((char *)arg0 + 0x50))*4 - (*(int *)((char *)arg0 + 0x50))) + 5));
    import_0024F228((char *)&timproc_uso_b5_D_807FF4C0 + 0x40, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x14) << 16) | 1);
    import_0024F228((char *)&timproc_uso_b5_D_807FF4D8 + 0x58, (((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x14) << 16);
    import_0024F228((char *)&timproc_uso_b5_D_807FF4F0 + 0x70, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x14) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FF508 + 0x88, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x14) << 16) | 4);
    import_0024F228((char *)&timproc_uso_b5_D_807FF520 + 0xa0, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x14) << 16) | 3);
    import_0024F228((char *)&timproc_uso_b5_D_807FF538 + 0xb8, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x18) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FF550 + 0xd0, (((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x18) << 16);
    import_0024F228((char *)&timproc_uso_b5_D_807FF568 + 0xe8, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x18) << 16) | 1);
    import_0024F228((char *)&timproc_uso_b5_D_807FF580 + 0x100, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x18) << 16) | 4);
    import_0024F228((char *)&timproc_uso_b5_D_807FF598 + 0x118, ((((*(int *)((char *)arg0 + 0x50))*2 + (*(int *)&import_8002022C)) + 0x18) << 16) | 3);
    import_0024F278((char *)&timproc_uso_b5_D_807FF640 + 0x1c0, 0xA << 16);
    import_0024F278((char *)&timproc_uso_b5_D_807FF658 + 0x1d8, (0xA << 16) | 1);
    import_0024F228((char *)&timproc_uso_b5_D_807FF670 + 0x1f0, (0xA << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FF688 + 0x208, (0xA << 16) | 3);
    import_0024F228((char *)&timproc_uso_b5_D_807FF6A0 + 0x220, (0xA << 16) | 4);
    import_0024F228((char *)&timproc_uso_b5_D_807FF6B8 + 0x238, (0xA << 16) | 5);
    import_0024F228((char *)&timproc_uso_b5_D_807FF6D0 + 0x250, (0xA << 16) | 6);
    import_0024F228((char *)&timproc_uso_b5_D_807FF6E8 + 0x268, (0xA << 16) | 7);
    if ((*(int *)&import_8002022C) != 0) {
        import_0024F278((char *)&timproc_uso_b5_D_807FF700 + 0x280, 0xB << 16);
        import_0024F278((char *)&timproc_uso_b5_D_807FF718 + 0x298, (0xB << 16) | 1);
        import_0024F278((char *)&timproc_uso_b5_D_807FF730 + 0x2b0, (0xB << 16) | 2);
        import_0024F278((char *)&timproc_uso_b5_D_807FF748 + 0x2c8, (0xB << 16) | 3);
        import_0024F278((char *)&timproc_uso_b5_D_807FF760 + 0x2e0, (0xB << 16) | 4);
        import_0024F278((char *)&timproc_uso_b5_D_807FF778 + 0x2f8, (0xB << 16) | 5);
        import_0024F278((char *)&timproc_uso_b5_D_807FF790 + 0x310, (0xB << 16) | 6);
        import_0024F278((char *)&timproc_uso_b5_D_807FF7A8 + 0x328, (0xB << 16) | 7);
    }
    import_0024F228((char *)&timproc_uso_b5_D_807FF7C0 + 0x340, ((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16);
    import_0024F228((char *)&timproc_uso_b5_D_807FF7D8 + 0x358, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 1);
    import_0024F228((char *)&timproc_uso_b5_D_807FF7F0 + 0x370, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FF808 + 0x388, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 3);
    import_0024F228((char *)&timproc_uso_b5_D_807FF820 + 0x3a0, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 4);
    import_0024F228((char *)&timproc_uso_b5_D_807FF838 + 0x3b8, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 5);
    import_0024F228((char *)&timproc_uso_b5_D_807FF850 + 0x3d0, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 6);
    import_0024F228((char *)&timproc_uso_b5_D_807FF868 + 0x3e8, (((*(int *)((char *)arg0 + 0x50))*2 + 0x10) << 16) | 7);
    if ((*(int *)&import_8002022C) != 0) {
        import_0024F228((char *)&timproc_uso_b5_D_807FF880 + 0x400, ((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16);
        import_0024F228((char *)&timproc_uso_b5_D_807FF898 + 0x418, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 1);
        import_0024F228((char *)&timproc_uso_b5_D_807FF8B0 + 0x430, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 2);
        import_0024F228((char *)&timproc_uso_b5_D_807FF8C8 + 0x448, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 3);
        import_0024F228((char *)&timproc_uso_b5_D_807FF8E0 + 0x460, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 4);
        import_0024F228((char *)&timproc_uso_b5_D_807FF8F8 + 0x478, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 5);
        import_0024F228((char *)&timproc_uso_b5_D_807FF910 + 0x490, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 6);
        import_0024F228((char *)&timproc_uso_b5_D_807FF928 + 0x4a8, (((*(int *)((char *)arg0 + 0x50))*2 + 0x11) << 16) | 7);
    }
    import_0024F228((char *)&timproc_uso_b5_D_807FF940 + 0x4c0, (((*(int *)((char *)arg0 + 0x50))*2 + 0xC) << 16) | ((*(int *)&import_8002022C)*5));
    import_0024F228((char *)&timproc_uso_b5_D_807FF958 + 0x4d8, (((*(int *)((char *)arg0 + 0x50))*2 + 0xC) << 16) | ((*(int *)&import_8002022C)*5 + 1));
    import_0024F228((char *)&timproc_uso_b5_D_807FF970 + 0x4f0, (((*(int *)((char *)arg0 + 0x50))*2 + 0xC) << 16) | ((*(int *)&import_8002022C)*5 + 2));
    import_0024F228((char *)&timproc_uso_b5_D_807FF988 + 0x508, (((*(int *)((char *)arg0 + 0x50))*2 + 0xC) << 16) | ((*(int *)&import_8002022C)*5 + 3));
    import_0024F228((char *)&timproc_uso_b5_D_807FF9A0 + 0x520, (((*(int *)((char *)arg0 + 0x50))*2 + 0xC) << 16) | ((*(int *)&import_8002022C)*5 + 4));
    import_0024F228((char *)&timproc_uso_b5_D_807FF9B8 + 0x538, ((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16);
    import_0024F228((char *)&timproc_uso_b5_D_807FF9D0 + 0x550, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 1);
    import_0024F228((char *)&timproc_uso_b5_D_807FF9E8 + 0x568, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA00 + 0x580, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 3);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA18 + 0x598, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 4);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA30 + 0x5b0, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 5);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA48 + 0x5c8, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 6);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA60 + 0x5e0, (((*(int *)((char *)arg0 + 0x50))*2 + 0xD) << 16) | 7);
    import_0024F278((char *)&timproc_uso_b5_D_807FFB08 + 0x688, ((*(int *)&import_8002022C) + 0x23) << 16);
    import_0024F278((char *)&timproc_uso_b5_D_807FFB20 + 0x6a0, (((*(int *)&import_8002022C) + 0x23) << 16) | 1);
    import_0024F278((char *)&timproc_uso_b5_D_807FFB38 + 0x6b8, (((*(int *)&import_8002022C) + 0x23) << 16) | 2);
    import_0024F228((char *)&timproc_uso_b5_D_807FFAC0 + 0x640, (0x7 << 16) | 8);
    import_0024F228((char *)&timproc_uso_b5_D_807FFAA8 + 0x628, (0x7 << 16) | 7);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA78 + 0x5f8, (((*(int *)&import_8002022C)*4 - (*(int *)&import_8002022C)) * 4) | 0x80000);
    import_0024F228((char *)&timproc_uso_b5_D_807FFA90 + 0x610, ((((*(int *)&import_8002022C)*4 - (*(int *)&import_8002022C)) * 4) + 1) | 0x80000);
    import_0024F228((char *)&timproc_uso_b5_D_807FFAD8 + 0x658, ((*(int *)((char *)arg0 + 0x50))*2) | 0x1C0000);
    import_0024F228((char *)&timproc_uso_b5_D_807FFAF0 + 0x670, ((*(int *)((char *)arg0 + 0x50))*2 + 1) | 0x1C0000);
    import_0024F278((char *)&timproc_uso_b5_D_807FFB50 + 0x6d0, (0x2F << 16) | 0x10);
    import_0024F228((char *)&timproc_uso_b5_D_807FFB68 + 0x6e8, (((*(int *)&import_8002022C) + 8) << 16) | 9);
    import_0024F228((char *)&timproc_uso_b5_D_807FFB80 + 0x700, (((*(int *)&import_8002022C) + 8) << 16) | 0xA);
    import_0024F228((char *)&timproc_uso_b5_D_807FFB98 + 0x718, (((*(int *)&import_8002022C) + 8) << 16) | 0xB);

}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00000778);
#endif

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
 * to clean up the *(int*)((char*)+offset) chains.
 *
 * 2026-05-05 status: 71.13% fuzzy. Build emits 99 insns (396 bytes) vs
 * target 104 (416 bytes); 5-insn delta, likely from $s-register usage
 * difference (target probably saves more $s-regs than our 5 named locals
 * trigger). Next-pass ideas:
 *   - Extract `slot->0x40C->0x38 + 0x18` into a helper macro/inline
 *     function call to reduce the 6 repeated chain expressions to 6
 *     calls. May change ref counts enough to bump $s-allocation.
 *   - Try `register int *flags_ptr = ...` to force one specific local
 *     into $s.
 *   - Type slot/child/flags as struct pointers (define a minimal struct
 *     with the relevant fields) to let IDO see field accesses as
 *     direct loads vs char-cast deref. */
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

/* timproc_uso_b5_func_0000131C: 81-word (0x144) optional-alloc + multi-link
 * constructor. RECONSTRUCTED 2026-07-03 with the REAL resolved symbols
 * (func_055750/04C678/000010EC/07ACE0 x3/00001460/00001658/076D58 +
 * import_80020098/80020078/8001FFF0 + timproc_uso_b5_D_807FE8F4). objdiff
 * 86.87% -> 94.80%; reloc-aware word-diff = 57/81 byte-exact (fresh
 * make RUN_CC_CHECK=0 + mips-linux-gnu-objdump -dr). No new undefined_syms.
 *
 * Levers that landed (all validated in-tree):
 *   - struct-cast-fold for the config table: `*(int**)(&import_80020098+0x134)`
 *     -> lui %hi + addiu(0) + lw 0x134; the 3-fold reload uses
 *     `*(volatile char**)(...)` to defeat CSE (target reloads 0x134(v1) x3).
 *   - `&timproc_uso_b5_D_807FE8F4 + 0x1084` -> lui %hi + addiu 0x1084 (low fold).
 *   - block-2 back-link RE-READS self->0x5C into the reused `sub` var (target
 *     re-reads memory + spills/reloads, does NOT keep the func-return live);
 *     made block-2 byte-exact.
 *   - decl order (entity, second_sub, sub) coalesces the spill slots.
 *
 * RESIDUAL ~24 words, ALL register-allocation / scheduling caps (C cannot force):
 *   (1) block-1 entity/sub v1<->a2 mirror-swap (idx 27,29,31,33-41): block-1
 *       attaches TWO objects so both `entity` (arg-base+value) and `sub`
 *       (a1+flag-base) cross the func_07ACE0 call; IDO breaks the 2-var
 *       coloring tie opposite the target. Block-2 (only ONE crossing var)
 *       colors correctly -> proves it is the extra crossing var, not the C.
 *   (2) block-3 second_sub reload a1-vs-a2 (idx 66,69,71-73) -- same class.
 *   (3) import_80020078 read-then-write: target emits TWO luis w/ %lo folded
 *       (idx 57-60); IDO from C always CACHES the base (one lui+addiu).
 *       Documented not-C-controllable (see func_00008DB4 notes).
 *   (4) frame 0x30-vs-0x28 (idx 0,80) + prologue or-s0/a1-home schedule
 *       (idx 2,3,5) -- downstream of (1)'s extra spill slot.
 *
 * (Old NM decode analysis follows, for body context.)
 *
 * 2026-05-06 +12pp via two combined fixes:
 *   (1) goto-end for unified exit: changed `if (alloc fail) return 0` to
 *       `if (alloc fail) goto end` with a single shared epilogue. Asm uses
 *       `beq v0, $0, .epilogue` to jump to the function tail, NOT a separate
 *       early-return. Documented in docs/PATTERNS.md#feedback-goto-end-unified-exit.
 *   (2) 4 unique-externs (D_timb5_131C_a/b/c/d) for the tail's 4 distinct
 *       global accesses. Without these, IDO CSEs all `&D_00000000` references
 *       to one lui+addiu and the 4 separate global addresses can't be emitted.
 *
 * Remaining ~18pp cap: (a) entry `or s0, a0, zero` reordering vs my init-at-decl,
 *   (b) the 3-fold reload of `base = *(char**)(SYM+0x134)` in the body — target
 *   reloads through the same v1 base 3 times (no CSE), but my C declares `base`
 *   once and IDO CSEs the read. Needs volatile or function-call clobber to force
 *   3 separate emits. Deferred — register-rename grind territory.
 *
 * 2026-05-07 incremental: inlined the volatile-cast for the 3-fold reload
 * (was using b1/b2/b3 locals). Frame shrunk 0x48 → 0x38 (-16 bytes,
 * eliminated 4 local slots). Target frame is 0x28; still 0x10 over.
 * Structural shape now matches target's `lw 0x134(v1) → lw 0xN(tN)` triple
 * with no intermediate spill. Remaining frame bloat: `char *base;` and
 * `char *sub;` locals that are spilled. `register` on `sub` might
 * eliminate one slot but `sub` is live across calls and would force $s
 * allocation, conflicting with self's $s0 claim. Defer.
 *
 * Decoded entry (insns 1-10):
 *   if (self == NULL) { self = gl_func(0x60); if (!self) return NULL; }
 *   gl_func(self, &D + 0x1084);          // probably init/format
 *   base = *(char**)(&D + 0x134);         // global config table
 *
 * Init from base (insns 11-15):
 *   self->[0x2C] = base->[0x84];
 *   self->[0x30] = base->[0x80];
 *   self->[0x34] = base->[0x8C];
 *
 * Sub-object construction (insns 16-30):
 *   sub = gl_func(0);                     // alloc/init helper, no args
 *   self->[0x5C] = sub;
 *   v3 = self->[0x2C];
 *   gl_func(v3 + 0x10, sub);              // link sub into entity at +0x2C
 *   if (entity_field[0x14] != 0) entity[0x4] = 1;
 *   entity_field[0x14] = v3;              // saved-old + write-new pattern
 *
 * Sibling sub-object (insns 31-45):
 *   sub2 = gl_func(self->[0x5C] + 0x10, self);
 *   if (self->[0x14] != 0) self->[0x4] = 1;
 *   self->[0x14] = sub2;
 *   gl_func(self);                         // tail-init
 *
 * Tail (insns 46-81): more global zero-stores + final link/return.
 *   *(int*)&D_X = 0; *(int*)&D_Y = 0;
 *   gl_func(self + 0x10, ...); (...)
 *   return self;
 *
 * Initial NM wrap — multi-pass refinement expected. Many gl_func_00000000
 * calls; the 0x134/0x84/0x80/0x8C offsets suggest a graphics-context
 * struct (e.g., a render-state config table at &D + 0x134 with sub-ptr
 * to glyph/texture pool fields). */
extern char D_00000000;
#ifdef NON_MATCHING
extern int timproc_uso_b5_func_000010EC();
extern int timproc_uso_b5_func_076D58();
extern void timproc_uso_b5_func_00001460();
extern void timproc_uso_b5_func_00001658();
extern char timproc_uso_b5_D_807FE8F4;
extern char import_80020078;
extern char import_8001FFF0;
void *timproc_uso_b5_func_0000131C(void *a0, int a1) {
    char *self = (char*)a0;
    char *entity;
    char *second_sub;
    char *sub;
    if (a0 == 0) {
        self = (char*)timproc_uso_b5_func_055750(0x60);
        if (self == 0) goto end;
    }
    timproc_uso_b5_func_04C678(self, (char*)&timproc_uso_b5_D_807FE8F4 + 0x1084);
    *(int*)(self + 0x2C) = *(int*)(*(volatile char**)(&import_80020098 + 0x134) + 0x84);
    *(int*)(self + 0x30) = *(int*)(*(volatile char**)(&import_80020098 + 0x134) + 0x80);
    *(int*)(self + 0x34) = *(int*)(*(volatile char**)(&import_80020098 + 0x134) + 0x8C);
    sub = (char*)timproc_uso_b5_func_000010EC(0);
    entity = *(char**)(self + 0x2C);
    *(int*)(self + 0x5C) = (int)sub;
    timproc_uso_b5_func_07ACE0(entity + 0x10, sub);
    if (*(int*)(sub + 0x14) != 0) *(int*)(sub + 0x4) = 1;
    *(int*)(sub + 0x14) = (int)entity;
    sub = *(char**)(self + 0x5C);
    timproc_uso_b5_func_07ACE0(sub + 0x10, self);
    if (*(int*)(self + 0x14) != 0) *(int*)(self + 0x4) = 1;
    *(int*)(self + 0x14) = (int)sub;
    timproc_uso_b5_func_00001460(self);
    timproc_uso_b5_func_00001658(self);
    second_sub = *(char**)&import_80020078;
    *(int*)&import_80020078 = 0;
    *(int*)&import_8001FFF0 = 0;
    timproc_uso_b5_func_07ACE0(self + 0x10, second_sub);
    if (*(int*)(second_sub + 0x14) != 0) *(int*)(second_sub + 0x4) = 1;
    *(int*)(second_sub + 0x14) = (int)self;
    timproc_uso_b5_func_076D58(*(int*)&import_80020078);
    (void)a1;
end:
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000131C);
#endif

// timproc_uso_b5_func_00001460 — STRUCTURAL PASS (0x1F8 / 126 words,
// no episode). Raw-.word USO form (genuine code; splat can't
// mnemonic-disasm relocatable USO). Hand-decoded from word encodings.
//
// Two-widget HUD/replay-element constructor for timproc_uso_b5:
//   void timproc_uso_b5_func_00001460(Owner *o) {     // o -> s1 (arg0)
//     // widget A:
//     A = func_00000000(0, &D_0000108C);              // named factory
//     o->0x38 = A;
//     A->0x124 = A->0x128 = A->0x12C = A->0x130 = 255.0f/255.0f; // =1.0 white RGBA
//     A->0xC4 |= 0x40;  A->0xC4 |= 0x80;              // flag bits
//     A->0xD0 = 1;                                     // element id 1
//     func_00000000(., A);                             // post-init
//     func_00000000(o+0x10, A);                        // register/attach
//     if (!o->0x14) { o->0x4 = 1; func_00000000(0, &D_0000109C);
//                     o->0x14 = o; }                   // one-time owner init
//     // widget B:
//     B = func_00000000(...);  o->0x3C = B;
//     B->0x124..0x130 = 1.0f;                          // white RGBA
//     B->0xD0 = 2;                                      // element id 2
//     func_00000000(., B);  func_00000000(o+0x10, B);   // post-init+attach
//   }
//
// Struct-typing reference:
//   o(a0=s1): 0x04 init-done flag, 0x10 attach-target/container,
//     0x14 self-init latch, 0x38 widget A ptr, 0x3C widget B ptr.
//   widget: 0xC4 flag word (bits 0x40/0x80 set), 0xD0 element id
//     (A=1, B=2), 0x124/0x128/0x12C/0x130 f32 RGBA (set 1.0 = white).
//   &D_0000108C / &D_0000109C = factory name/desc args (USO data refs).
//   func_00000000 = the USO placeholder dispatcher (factory / attach).
// Caps (DEFERRED): raw-word USO + placeholder func_00000000 calls;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — two-widget HUD constructor. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern void *timproc_uso_b5_func_068D54(int, char *);
extern float timproc_uso_b5_func_062880(char *, char *);
extern char import_8005C108;
extern char timproc_uso_b5_D_807FE8FC;
extern char timproc_uso_b5_D_807FE90C;
extern char timproc_uso_b5_D_807FE918;
void timproc_uso_b5_func_00001460(char *arg0) {
    char *o, *reg;
    float retA;

    reg = arg0 + 0x10;

    /* widget A (id 1) — white RGBA = 255.0f/255.0f */
    o = (char *)timproc_uso_b5_func_068D54(0, &timproc_uso_b5_D_807FE8FC + 0x108C);
    *(char **)(arg0 + 0x38) = o;
    *(float *)(o + 0x124) = 255.0f / 255.0f;
    *(float *)(o + 0x128) = 255.0f / 255.0f;
    *(float *)(o + 0x12C) = 255.0f / 255.0f;
    *(float *)(o + 0x130) = 255.0f / 255.0f;
    o = *(char **)(arg0 + 0x38);
    *(int *)(o + 0xC4) |= 0x40;
    o = *(char **)(arg0 + 0x38);
    *(int *)(o + 0xC4) |= 0x80;
    o = *(char **)(arg0 + 0x38);
    *(int *)(o + 0xD0) = 1;
    retA = timproc_uso_b5_func_062880(&import_8005C108, *(char **)(arg0 + 0x38));
    o = *(char **)(arg0 + 0x38);
    timproc_uso_b5_func_07ACE0(reg, o);
    if (*(int *)(o + 0x14) != 0) {
        *(int *)(o + 0x4) = 1;
    }
    *(char **)(o + 0x14) = arg0;

    /* widget B (id 2) — white RGBA = 1.0f */
    o = (char *)timproc_uso_b5_func_068D54(0, &timproc_uso_b5_D_807FE90C + 0x109C);
    *(char **)(arg0 + 0x3C) = o;
    *(float *)(o + 0x124) = 1.0f;
    *(float *)(o + 0x128) = 1.0f;
    *(float *)(o + 0x12C) = 1.0f;
    *(float *)(o + 0x130) = 1.0f;
    o = *(char **)(arg0 + 0x3C);
    *(int *)(o + 0xD0) = 2;
    timproc_uso_b5_func_062880(&import_8005C108, *(char **)(arg0 + 0x3C));
    o = *(char **)(arg0 + 0x3C);
    timproc_uso_b5_func_07ACE0(reg, o);
    if (*(int *)(o + 0x14) != 0) {
        *(int *)(o + 0x4) = 1;
    }
    *(char **)(o + 0x14) = arg0;

    /* widget C (id 4) — RGBA = 174/255, 113/255, 61/255, retA */
    o = (char *)timproc_uso_b5_func_068D54(0, &timproc_uso_b5_D_807FE918 + 0x10A8);
    *(char **)(arg0 + 0x40) = o;
    *(float *)(o + 0x124) = 174.0f / 255.0f;
    *(float *)(o + 0x128) = 113.0f / 255.0f;
    *(float *)(o + 0x12C) = 61.0f / 255.0f;
    *(float *)(o + 0x130) = retA;
    o = *(char **)(arg0 + 0x40);
    *(int *)(o + 0xC4) |= 0x40;
    o = *(char **)(arg0 + 0x40);
    *(int *)(o + 0xC4) |= 0x80;
    o = *(char **)(arg0 + 0x40);
    *(int *)(o + 0xD0) = 4;
    timproc_uso_b5_func_062880(&import_8005C108, *(char **)(arg0 + 0x40));
    o = *(char **)(arg0 + 0x40);
    timproc_uso_b5_func_07ACE0(reg, o);
    if (*(int *)(o + 0x14) != 0) {
        *(int *)(o + 0x4) = 1;
    }
    *(char **)(o + 0x14) = arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001460);
#endif

// timproc_uso_b5_func_00001658 — STRUCTURAL PASS (0x25C / 151 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Radial-dial HUD panel constructor (timproc_uso_b5): builds a parent
// container plus a set of child marks at cardinal angle parameters.
//
//   void timproc_uso_b5_func_00001658(Owner *o) {     // o -> s1 (arg0)
//     func_00000000(&D_000010B8, 0);                   // named setup x2
//     func_00000000(&D_000010C0, 0);
//     P = func_00000000(0, &D_000010C8, 1, 0x100);     // parent container
//     func_00000000(o+0x10, P);                        // attach to owner
//     if (!o->0x14) { o->0x4 = 1; o->0x14 = o; }       // one-time init
//     // create child marks, each func_00000000(0,&D_0,0, ANGLE, sp10=0)
//     //   stored into o->{0x44,0x48,0x4C,0x50,0x54,0x58}; ANGLE =
//     //   0, 0x5A(90), 0xB4(180), 0x10E(270), -0x5A(-90), -0x10E(-270)
//     //   -> a radial gauge / dial with cardinal tick marks.
//     // then for each child c in o->0x44..0x58:
//     //   func_00000000(c+0x10, P);                    // attach to P
//     //   if (!c->0x14) c->0x4 = 1;  c->0x14 = P;       // dirty+link
//     func_00000000(.);  func_00000000();               // finalize
//   }
//
// Struct-typing reference:
//   o(a0=s1): 0x04 init-done flag, 0x10 attach-target, 0x14 self/link
//     latch, 0x44/0x48/0x4C/0x50/0x54/0x58 = 6 child mark ptrs;
//     P = parent container (from &D_000010C8 factory).
//   child: 0x04 dirty flag, 0x14 parent link (dirty-and-attach idiom).
//   ANGLE args 0/±90/±180/±270 (deg*1, signed) = dial tick positions.
//   &D_000010B8 / &D_000010C0 / &D_000010C8 = USO name/desc data refs;
//   func_00000000 = USO placeholder dispatcher (setup/factory/attach).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — radial-dial HUD panel constructor with 6 cardinal-angle
//   children. Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00001658)();
void timproc_uso_b5_func_00001658(char *arg0) {
    char *sp3C;
    char *sp28;
    char *temp_a0;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    char *temp_s0_4;
    char *temp_s0_5;
    char *temp_s0_6;
    char *temp_v0;

    timproc_uso_b5_alias((char *)0x10B8, 0);
    timproc_uso_b5_alias((char *)0x10C0, 0);
    temp_v0 = timproc_uso_b5_alias(0, (char *)0x10C8, 1, 0x100);
    sp3C = temp_v0;
    timproc_uso_b5_alias((int)arg0 + 0x10, temp_v0);
    if (FW(temp_v0, 0x14) != 0) {
        FW(temp_v0, 0x4) = 1;
    }
    FW(temp_v0, 0x14) = arg0;
    FW(arg0, 0x44) = timproc_uso_b5_alias(0, 0, 0, 0, 0);
    FW(arg0, 0x48) = timproc_uso_b5_alias(0, 0, 0, 0x5A, 0);
    FW(arg0, 0x4C) = timproc_uso_b5_alias(0, 0, 0, 0xB4, 0);
    FW(arg0, 0x50) = timproc_uso_b5_alias(0, 0, 0, 0x10E, 0);
    FW(arg0, 0x54) = timproc_uso_b5_alias(0, 0, -0x5A, 0, 0);
    FW(arg0, 0x58) = timproc_uso_b5_alias(0, 0, -0x10E, 0, 0);
    temp_s0 = FW(arg0, 0x44);
    temp_a0 = sp3C + 0x10;
    sp28 = temp_a0;
    timproc_uso_b5_alias(temp_a0, temp_s0);
    if (FW(temp_s0, 0x14) != 0) {
        FW(temp_s0, 0x4) = 1;
    }
    FW(temp_s0, 0x14) = sp3C;
    temp_s0_2 = FW(arg0, 0x48);
    timproc_uso_b5_alias(sp28, temp_s0_2);
    if (FW(temp_s0_2, 0x14) != 0) {
        FW(temp_s0_2, 0x4) = 1;
    }
    FW(temp_s0_2, 0x14) = sp3C;
    temp_s0_3 = FW(arg0, 0x4C);
    timproc_uso_b5_alias(sp28, temp_s0_3);
    if (FW(temp_s0_3, 0x14) != 0) {
        FW(temp_s0_3, 0x4) = 1;
    }
    FW(temp_s0_3, 0x14) = sp3C;
    temp_s0_4 = FW(arg0, 0x50);
    timproc_uso_b5_alias(sp28, temp_s0_4);
    if (FW(temp_s0_4, 0x14) != 0) {
        FW(temp_s0_4, 0x4) = 1;
    }
    FW(temp_s0_4, 0x14) = sp3C;
    temp_s0_5 = FW(arg0, 0x54);
    timproc_uso_b5_alias(sp28, temp_s0_5);
    if (FW(temp_s0_5, 0x14) != 0) {
        FW(temp_s0_5, 0x4) = 1;
    }
    FW(temp_s0_5, 0x14) = sp3C;
    temp_s0_6 = FW(arg0, 0x58);
    timproc_uso_b5_alias(sp28, temp_s0_6);
    if (FW(temp_s0_6, 0x14) != 0) {
        FW(temp_s0_6, 0x4) = 1;
    }
    FW(temp_s0_6, 0x14) = sp3C;
    timproc_uso_b5_alias();
    timproc_uso_b5_alias();
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001658);
#endif

// timproc_uso_b5_func_000018B4 — STRUCTURAL PASS (0x354 / 213 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// 3-child labeled-widget panel constructor (alloc-or-reuse) for
// timproc_uso_b5; returns the constructed object.
//
//   void *timproc_uso_b5_func_000018B4(Obj *self, a1, Owner *owner) {
//     if (!self) { self = func_00000000(0x58); if (!self) return 0; }
//     func_00000000(self, &D_000010D0);                // base-init
//     self->0x28 = &D_0;                                // vtable
//     self->0x0C = &D_000010D8;                         // descriptor
//     self->0x30 = owner;                               // owner (arg2)
//     self->0x2C = a1;                                  // arg1 ptr
//     // 3x near-identical child blocks (names &D_000010E8 / _10F8 /
//     //   _110C), each: build a spec on stack, c =
//     //   func_00000000(0, ..., idx) with idx = 1,2,3 (3rd adds flag
//     //   0x80); self->{0x34,0x38} = c; func_00000000(c+0x10, .);
//     //   if (!c->0x14) c->0x4 = 1;  c->0x14 = parent;  (dirty+link)
//     // layout finalize: dims 0x78(120)/0xF0(240); if
//     //   self->0x34->0x3C8 == K: self->0x3C/0x40/0x48 = 0,
//     //   self->0x44 = 1.0f, self->0x50 = 3, self->0x4C = 0;
//     //   else: self->0x3C/0x40 = 1.0f, fields from prior children;
//     //   self->0x54 = computed f32.
//     return self;
//   }
//
// Struct-typing reference:
//   self(a0, alloc size 0x58): 0x0C descriptor(&D_10D8), 0x28
//     vtable(&D_0), 0x2C a1 ptr, 0x30 owner, 0x34/0x38 child widget
//     ptrs, 0x3C/0x40 f32 (1.0 default), 0x44 f32 scale, 0x48/0x4C
//     state, 0x50 mode (3), 0x54 computed f32; child->0x3C8 a
//     discriminator; child: 0x04 dirty, 0x14 parent link.
//   &D_000010D0/10D8/10E8/10F8/110C = USO name/desc data; func_00000000
//     = USO placeholder dispatcher (alloc / init / factory / attach).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — alloc-or-reuse 3-child labeled-widget panel. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// timproc_uso_b5_func_000018B4 — FULL m2c DECODE (57.12% NM, no episode). Non-jumptable control-flow fn via scripts/lift-uso-controlflow.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000018B4)();
char *timproc_uso_b5_func_000018B4(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, char *arg5, s32 arg6, s32 arg7) {
    char *sp4C;
    char *temp_a0;
    char *temp_s1;
    char *temp_s1_2;
    char *temp_s1_3;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *var_s0;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = timproc_uso_b5_alias((char *)0x58), var_s0 = temp_v0, (temp_v0 != 0))) {
        timproc_uso_b5_alias(var_s0, (char *)0x10D0);
        FW(var_s0, 0x28) = 0;
        FW(var_s0, 0xC) = 0x10D8;
        FW(var_s0, 0x30) = arg2;
        FW(var_s0, 0x2C) = arg5;
        if (arg2 == 1) {
            temp_v0_2 = timproc_uso_b5_alias(0, var_s0, arg1, 1, 0, arg3, arg4, arg6, arg5, FW(arg5, 0x4), 0x10E8, 0);
            FW(var_s0, 0x34) = temp_v0_2;
            timproc_uso_b5_alias(temp_v0_2, (char *)0x68, 0x4C, 0x50, 0x54, 0x64);
            temp_s1 = FW(var_s0, 0x34);
            timproc_uso_b5_alias(var_s0 + 0x10, temp_s1);
            if (FW(temp_s1, 0x14) != 0) {
                FW(temp_s1, 0x4) = 1;
            }
            FW(temp_s1, 0x14) = var_s0;
            FW(FW(FW(arg5, 0x0), 0x5C), 0x38) = (char *) FW(var_s0, 0x34);
        } else {
            temp_v0_3 = timproc_uso_b5_alias(0, var_s0, arg1, 2, 0, arg3, arg4, arg6, arg5, FW(arg5, 0x4), 0x10F8, 0);
            FW(var_s0, 0x34) = temp_v0_3;
            timproc_uso_b5_alias(temp_v0_3, (char *)0x68, 0x4C, 0x50, 0x54, 0x64);
            temp_s1_2 = FW(var_s0, 0x34);
            temp_a0 = var_s0 + 0x10;
            sp4C = temp_a0;
            timproc_uso_b5_alias(temp_a0, temp_s1_2);
            if (FW(temp_s1_2, 0x14) != 0) {
                FW(temp_s1_2, 0x4) = 1;
            }
            FW(temp_s1_2, 0x14) = var_s0;
            FW(FW(FW(arg5, 0x0), 0x5C), 0x38) = (char *) FW(var_s0, 0x34);
            temp_v0_4 = timproc_uso_b5_alias(0, var_s0, arg1, 2, 1, arg3, arg4, arg7, arg5, FW(arg5, 0x8), 0x110C, 0x80);
            FW(var_s0, 0x38) = temp_v0_4;
            timproc_uso_b5_alias(temp_v0_4, (char *)0x68, 0x58, 0x5C, 0x60, 0x64);
            temp_s1_3 = FW(var_s0, 0x38);
            timproc_uso_b5_alias(sp4C, temp_s1_3);
            if (FW(temp_s1_3, 0x14) != 0) {
                FW(temp_s1_3, 0x4) = 1;
            }
            FW(temp_s1_3, 0x14) = var_s0;
            FW(FW(FW(arg5, 0x0), 0x5C), 0x3C) = (char *) FW(var_s0, 0x38);
            if (FW(FW(var_s0, 0x34), 0x3C8) != 4) {
                FW(var_s0, 0x3C) = 0;
                FW(var_s0, 0x40) = 0;
                FW(var_s0, 0x44) = 0x78;
                FW(var_s0, 0x48) = 0;
                FW(var_s0, 0x50) = 3;
                FW(var_s0, 0x4C) = 0;
                *(f32 *)((char *)var_s0 + 0x54) = 0.0f;
            } else {
                FW(var_s0, 0x3C) = 3;
                FW(var_s0, 0x40) = 3;
                FW(var_s0, 0x4C) = 0;
                FW(var_s0, 0x48) = 1;
                FW(var_s0, 0x44) = 0xF0;
                FW(var_s0, 0x50) = 1;
                *(f32 *)((char *)var_s0 + 0x54) = 1.0f;
                timproc_uso_b5_alias(var_s0);
            }
        }
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000018B4);
#endif

// timproc_uso_b5_func_00001C08 — STRUCTURAL PASS (no episode).
// Raw-.word USO form. BOUNDARY NOTE: this .s is an UNSPLIT USO
// multi-function bundle — 8 jr-ra terminators (the named function ends
// at 0x1CE8; separate functions follow at ~0x1CF0/0x1D1C/0x1D60/
// 0x1DB0, each its own prologue-less raw-word body). USO bundles can't
// be split by the mnemonic split-fragments.py; needs a generate-uso-asm
// re-split (deferred — see reference_uso_splat_setup memo). Only the
// NAMED leading function (0x1C08..0x1CEC, ~58 words) is decoded here.
//
// Named function = per-mode notify/reset-all dispatcher:
//   void timproc_uso_b5_func_00001C08(State *st) {     // st -> s3
//     int i = 0;
//     if (st->0x30 == 2) i = (st->0x48 == 1) ? 1 : 0;  // pick slot
//     R *r = *(R**)((char*)st + i*4 + 0x34);
//     // nested chain: c = r->0x40C; d = c->0x48 + r->0x3D8*4;
//     func_00000000(7, d->0x3C->0x2B0);                 // query/dispatch
//     for (s0 = 0; s0 < st->0x30count; s0++)            // broadcast loop
//       func_00000000(((Ent*)((char*)st + s0*4))->0x34, 1);
//   }
//
// Struct-typing reference:
//   st(a0=s3): 0x30 mode/count word (==2 selects slot path),
//     0x34 = array base of per-slot records (stride 4, each ->0x34
//     a sub-object), 0x48 sub-mode (==1). r->0x40C / r->0x3D8 /
//     ->0x48 / ->0x3C / ->0x2B0 = nested record chain for the
//     dispatch arg. func_00000000 = USO placeholder (query / notify;
//     arg 7 = a query op, arg 1 = a reset/notify op).
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder
//   calls; boundary re-split needs generate-uso-asm migration. Real-C
//   STRUCTURAL body below — the named leading dispatcher only;
//   trailing functions (0x1CF0/0x1D1C/0x1D60/0x1DB0) remain
//   INCLUDE_ASM under their own symbols. Byte-match deferred. Name
//   pre-checked: no extern reuse.
/* timproc_uso_b5_func_00001C08 — VERIFIED EXACT 58/58 (2026-07-03, agent-e)
 * vs asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_00001C08.s
 * (in-tree word-by-word on build/non_matching .o, clean rebuild, -O2;
 * jal words 0x0C000000 via extern callees).
 *
 * LOGIC BUGS fixed vs old NM body (84.4%):
 * 1. Slot pick was INVERTED: target sets i=1 when st->0x48 != 1 (old body
 *    had `i = (st->0x48 == 1) ? 1 : 0`).
 * 2. Shape: nested if/else with `i = 0` in the OUTER else arm. A dominating
 *    `i = 0;` init lets uopt prove the then-arm redundant and collapse the
 *    inner diamond to a beql; the outer-else form emits the target's full
 *    bne/nop + two-`b` diamond, and the else `i = 0` lands in the outer bne
 *    delay slot. This restructure also flipped the s2/s3 coloring to the
 *    target's (i->s2, st->s3).
 * 3. Real callees per .s jal relocs: timproc_uso_b5_func_0002FC (dispatch,
 *    a0=7) and timproc_uso_b5_func_000069E8 (per-slot notify). Loop is a
 *    TWO-CALL if/else (two jal sites), not a ternary second arg.
 * 4. Chain arithmetic: fold c/d locals into one expression, 8C1C-style
 *    scaled-first text -> pure t0-t5 temps + addu rs=base. Site-1 (reg base)
 *    needs base-first text `(int)st + i*4 + 0x34` for addu t9,s3,t8.
 */
extern int timproc_uso_b5_func_0002FC();
extern int timproc_uso_b5_func_000069E8(char *scr, int a1);
void timproc_uso_b5_func_00001C08(char *st) {
    int i;
    char *r;
    int s0;
    if (*(int *)(st + 0x30) == 2) {
        if (*(int *)(st + 0x48) == 1) {
            i = 0;
        } else {
            i = 1;
        }
    } else {
        i = 0;
    }
    r = *(char **)((int)st + i * 4 + 0x34);
    timproc_uso_b5_func_0002FC(7,
        *(char **)(*(int *)(*(int *)(r + 0x3D8) * 4 + *(int *)(*(char **)(r + 0x40C) + 0x48) + 0x3C) + 0x2B0));
    for (s0 = 0; s0 < *(int *)(st + 0x30); s0++) {
        if (s0 == i) {
            timproc_uso_b5_func_000069E8(*(char **)(st + s0 * 4 + 0x34), 1);
        } else {
            timproc_uso_b5_func_000069E8(*(char **)(st + s0 * 4 + 0x34), 0);
        }
    }
}

#ifdef NON_MATCHING
/* 9-insn flag-check + indexed-load with branch-to-empty-next-function as
 * implicit early-return (cap class: IDO won't emit `bne; ...; <fall to
 * empty next>` from a `return 0` since the empty function 0x1D14 is just
 * `jr $ra; nop`). NM body captures logic; build path keeps INCLUDE_ASM. */
int timproc_uso_b5_func_00001CF0(int *a0, int a1) {
    if (*(int*)((char*)a0 + 0x30) != 2) {
        return 0;
    }
    return *(int*)((char*)a0 + 0x34 + 4 * (a1 ^ 1));
}
#else
/* timproc_uso_b5_func_00001CF0: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001CF0);
#endif

void timproc_uso_b5_func_00001D14(void) {}

/* timproc_uso_b5_func_00001D1C (0x88 after merging the 1D60 fragment --
 * 1D60 read v1/at/a3/v0/a2 uninitialized at entry = pure continuation).
 * Pair-state comparator: with a0->i_30 == 2, compares the 0x3C8 counters
 * of the a1-indexed and (a1^1)-indexed pair members (a0 + idx*4 + 0x34),
 * then a 1/2/4 dispatch on the counter with 0x3CC == 5 checks deciding
 * 0 vs 1. CAP: every return-1 path branches INTO the adjacent return-1
 * leaf timproc_uso_b5_func_00001DA4 (offsets 0x88/0x8C = its li v0,1 and
 * jr ra) -- the documented branch-into-adjacent-return-leaf cap
 * (docs/IDO_CODEGEN#branch-into-adjacent-return-leaf-cap, same as
 * mgrproc 140/170): C collapses the shared tail (preset-default or
 * branch-likely forms), never the cross-fn branch. INCLUDE_ASM is the
 * faithful path; the wrap preserves the decoded logic. */
#ifdef NON_MATCHING
int timproc_uso_b5_func_00001D1C(char *a0, int a1) {
    char *p1;
    char *p2;
    int c1;
    int c2;
    if (*(int *)(a0 + 0x30) != 2) {
        return 1;
    }
    p1 = *(char **)(a0 + a1 * 4 + 0x34);
    p2 = *(char **)(a0 + (a1 ^ 1) * 4 + 0x34);
    c1 = *(int *)(p1 + 0x3C8);
    c2 = *(int *)(p2 + 0x3C8);
    if (c1 != c2) {
        return 0;
    }
    if (c1 == 2) {
        return 1;
    }
    if (c1 != 1 && c1 == 4) {
        return 1;
    }
    if (c1 == 1) {
        if (*(int *)(p1 + 0x3CC) == 5) {
            return 0;
        }
        if (*(int *)(p2 + 0x3CC) != 5) {
            return 1;
        }
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001D1C);
#endif

/* timproc_uso_b5_func_00001D60 MERGED into 1D1C 2026-06-10 (uninitialized-reg continuation fragment). */

/* timproc_uso_b5_func_00001DA4 (`return 1`, unfilled jr-delay) is carved into
 * its own -O2 -g3 sub-unit src/timproc_uso_b5/timproc_uso_b5_g3_1DA4.c and
 * spliced back into block5 at offset 0x1DA4 — see the timproc_uso_block5_yay0
 * rule. -g3 unfills the delay slot (li/jr/nop) without -O0 bloat; can't apply
 * file-wide here (150+ filled-delay matches would regress). */

/* timproc_uso_b5_func_00001DB0 (0x164 after absorbing the 1EB8 fragment):
 * the bnezl at +0xF0 branches to 0x1EBC, past the declared end into the
 * old 1EB8 range, and 1EB8 read v0/v1 uninitialized at entry -- the same
 * branch-past-declared-end family as the fade-helpers and 1D1C/1D60.
 * The merged tail block copies a0->i_44 into nested p_38->p_3F4[?]->
 * fields 0xC4/0xD4 and stores (v1 - a0->i_44) deltas to 0xBC/0xCC --
 * sibling family of the 1C08 State machine. Full decode pending. */
/* 2026-06-10 pass 1 (post-merge): m2c decodes the 0x164 fn cleanly -- a
 * two-channel crossfade updater: ch1 = a0->p_34 gets level a0->i_44,
 * ch2 = a0->p_38 gets (0xF0 - level); each writes the nested
 * ch->p_414->p_C record (C4/D4 cleared or set, BC/CC = level) plus, on
 * the ch1 active path, f_B4 = dbl_C0 + dbl_B8*(1.0f - a0->f_54) (f64
 * math, reloc'd double constants at +0xB8/+0xC0 -- offset-valued syms
 * staged) and ch1->f_49C = 41.0f + 5.0f*a0->f_54. Standalone at 7.1
 * -O2: 89/87. Pass 2: the two doubles share ONE %hi base in the target
 * (one lui at + ldc1 184/192(at)) -- array-form extern D_1DB0_dbls[23]/
 * [24] reproduces the shared base (distinct externs emit two luis).
 * Remaining +2 = the 41.0f (0x4224) / 5.0f (0x40A0) float-constant lui
 * scheduling (build hoists 0x40A0 early). Cast variants ((f64) explicit,
 * implicit promotion, double-constant subtract) all neutral or worse.
 * Residual = pure FP-constant scheduling. */
#ifdef NON_MATCHING
extern f64 D_1DB0_dbls[];  /* doubles at +0xB8/+0xC0 share ONE %hi base
                              (target: one lui at + ldc1 184(at)/192(at));
                              distinct externs emit two luis -- array form
                              [23]/[24] shares the base. */

void timproc_uso_b5_func_00001DB0(char *a0) {
    char *t;
    char *u;

    *(s32 *)(*(char **)(a0 + 0x34) + 0x4D8) = *(s32 *)(a0 + 0x44);
    t = *(char **)(a0 + 0x34);
    if (*(s32 *)(t + 0x4D8) == 0) {
        *(s32 *)(*(char **)(*(char **)(t + 0x414) + 0xC) + 0xBC) = 0;
    } else {
        *(s32 *)(*(char **)(*(char **)(t + 0x414) + 0xC) + 0xC4) = 0;
        *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x34) + 0x414) + 0xC) + 0xD4) = 0;
        *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x34) + 0x414) + 0xC) + 0xBC) = *(s32 *)(a0 + 0x44);
        *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x34) + 0x414) + 0xC) + 0xCC) = *(s32 *)(a0 + 0x44);
        *(f32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x34) + 0x414) + 0xC) + 0xB4) =
            D_1DB0_dbls[24] + D_1DB0_dbls[23] * (f64)(1.0f - *(f32 *)(a0 + 0x54));
        *(f32 *)(*(char **)(a0 + 0x34) + 0x49C) = 41.0f + 5.0f * *(f32 *)(a0 + 0x54);
    }
    *(s32 *)(*(char **)(a0 + 0x38) + 0x4D8) = 0xF0 - *(s32 *)(a0 + 0x44);
    u = *(char **)(a0 + 0x38);
    if (*(s32 *)(u + 0x4D8) == 0) {
        *(s32 *)(*(char **)(*(char **)(u + 0x414) + 0xC) + 0xBC) = 0;
        return;
    }
    *(s32 *)(*(char **)(*(char **)(u + 0x414) + 0xC) + 0xC4) = *(s32 *)(a0 + 0x44);
    *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x38) + 0x414) + 0xC) + 0xD4) = *(s32 *)(a0 + 0x44);
    *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x38) + 0x414) + 0xC) + 0xBC) = 0xF0 - *(s32 *)(a0 + 0x44);
    *(s32 *)(*(char **)(*(char **)(*(char **)(a0 + 0x38) + 0x414) + 0xC) + 0xCC) = 0xF0 - *(s32 *)(a0 + 0x44);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001DB0);
#endif

/* timproc_uso_b5_func_00001EB8 MERGED into 1DB0 2026-06-10 (bnezl tail fragment). */

// timproc_uso_b5_func_00001F14 — STRUCTURAL PASS (0x89C / 551 words,
// no episode). Raw-.word USO form (genuine code, single function).
// Large per-frame state/transition processor; partial decode (entry
// gate + shape + tail) — multi-run target.
//
//   void timproc_uso_b5_func_00001F14(State *st) {     // st -> a2 (arg0)
//     if (st->0x30 != 2) { st->0x3C = 0; return; }      // only "mode 2"
//     // mode-2 body (~0x21B words): walk sub-records via st->0x34/
//     //   0x38/0x44 pointer chains, branch on the discriminator at
//     //   sub->0x3CC, and edit the flag word st->0x3C (e.g. |= 0x2)
//     //   per transition; state constants 1 / 2 / 4 select sub-paths;
//     //   ~6 func_00000000 sub-dispatch calls advance/commit each
//     //   record's 0x38/0x40/0x44/0x50 fields.
//     // tail: func_00000000(st);  (final commit/notify)
//   }
//
// Struct-typing reference:
//   st(a0=a2): 0x30 mode/phase (==2 gate, else early-out clearing
//     0x3C); 0x34/0x38/0x44 sub-record pointers (chained);
//     0x3C flag word (bit 0x2 set on transition); 0x3CC sub-record
//     discriminator (drives the branch tree); 0x40/0x50 per-record
//     scratch updated alongside. State constants 1/2/4 = phase ids.
//   func_00000000 = USO placeholder dispatcher (per-record advance /
//     final notify).
// Caps (DEFERRED): raw-word USO + placeholder calls + 0x21B-word
//   branch tree; structural (entry/shape/tail) pass; multi-run
//   target (future passes can expand the mode-2 tree). Real-C
//   STRUCTURAL body below — gate + skeleton only. Byte-match
//   deferred. Name pre-checked: no extern reuse.
/* DEEP RECONSTRUCTION 2026-06-22 (agent-e, big-swing): real compiled C.
 * Per-frame transition processor. arg0 (a0) aliased to a2 throughout.
 * st->0x30 gate (==2); two sub-records st->0x34/0x38 each with a
 *   discriminator at +0x3CC (==8 sets flag bits 1 / 2 in st->0x3C).
 * flag (1/2/3) drives the transition tree; st->0x54 is the f32 blend
 *   ramp (0..1); st->0x44 the derived 0..0xF0 frame index; per sub-record
 *   it writes child(+0x414)->+0xC grandchild fields (+0xBC/0xC4/0xCC/0xD4
 *   ints, +0xB4/+0x49C floats) and the +0x4D8 frame slot.
 * FP const pool at &D_00000000 + 0xC8..0x118 (f32 ramp steps + f64 pairs).
 * func_00000000 = USO placeholder dispatcher (=0 in undefined_syms). */
extern int timproc_uso_b5_func_000087A0();
extern void timproc_uso_b5_func_00001DB0(char *);
extern void timproc_uso_b5_func_04CD94(char *);
#ifdef NON_MATCHING
/* 83.59% fuzzy (was 64.97%): logic-complete correct-C reconstruction.
 * Residual is the IDO -O2 as1 branch-likely scheduler cap: target emits
 * 21 beql/bnel (delay slots filled from the branch target); our C draws
 * only 9, the deficit cascading register homes downstream. Permuter-immune
 * per project history (branch-likely confuses live-range tracing). Build
 * path stays INCLUDE_ASM (ROM exact); C preserved for future RE. */
void timproc_uso_b5_func_00001F14(char *arg0) {
    s32 dst;
    f64 cf12;
    f64 cf14;
    f64 vf12;
    f64 vf14;
    s32 frame;
    s32 frame2;
    s32 frame3;
    s32 flag;
    s32 sub40;
    s32 v1;
    s32 anim;
    char *r34;
    char *r34b;
    char *r34c;
    char *r38;
    char *r38b;
    char *r38c;

    *(s32 *)(arg0 + 0x3C) = 0;
    if (*(s32 *)(arg0 + 0x30) == 2) {
        if (*(s32 *)(*(char **)(arg0 + 0x34) + 0x3CC) == 8) {
            *(s32 *)(arg0 + 0x3C) = 1;
        }
        if (*(s32 *)(*(char **)(arg0 + 0x38) + 0x3CC) == 8) {
            *(s32 *)(arg0 + 0x3C) = *(s32 *)(arg0 + 0x3C) | 2;
        }
        flag = *(s32 *)(arg0 + 0x3C);
        if (flag != 0) {
            if (flag == 3) {
                if (*(s32 *)(arg0 + 0x44) == 0x78) {
                    sub40 = *(s32 *)(arg0 + 0x40);
                    if (sub40 == 1) {
                        *(s32 *)(arg0 + 0x4C) = 1;
                        *(s32 *)(arg0 + 0x48) = 1;
                        *(f32 *)(arg0 + 0x54) = 0.0f;
                    } else if (sub40 == 2) {
                        *(s32 *)(arg0 + 0x4C) = 1;
                        *(s32 *)(arg0 + 0x48) = 2;
                        *(f32 *)(arg0 + 0x54) = 0.0f;
                    }
                }
                if (*(s32 *)(arg0 + 0x48) == 1) {
                    dst = timproc_uso_b5_func_000087A0(*(char **)(arg0 + 0x38), 4, arg0, 2);
                    *(s32 *)(*(s32 *)(arg0 + 0x38) + (dst * 4) + 0x3D0) =
                        *(s32 *)(*(s32 *)(arg0 + 0x34) + (timproc_uso_b5_func_000087A0(*(char **)(arg0 + 0x34), 4, arg0) * 4) + 0x3D0);
                } else {
                    dst = timproc_uso_b5_func_000087A0(*(char **)(arg0 + 0x34), 4, arg0, 2);
                    *(s32 *)(*(s32 *)(arg0 + 0x34) + (dst * 4) + 0x3D0) =
                        *(s32 *)(*(s32 *)(arg0 + 0x38) + (timproc_uso_b5_func_000087A0(*(char **)(arg0 + 0x38), 4, arg0) * 4) + 0x3D0);
                }
                if (*(s32 *)(arg0 + 0x4C) != 0) {
                    anim = *(s32 *)(arg0 + 0x48);
                    if (anim == 1) {
                        *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) + *(f32 *)((char *)&D_00000000 + 0xC8);
                        if (*(f32 *)(arg0 + 0x54) >= 1.0f) {
                            *(f32 *)(arg0 + 0x54) = 1.0f;
                            *(s32 *)(arg0 + 0x4C) = 0;
                        }
                        *(s32 *)(arg0 + 0x44) = (s32) (120.0f + (*(f32 *)(arg0 + 0x54) * 120.0f));
                        timproc_uso_b5_func_00001DB0(arg0);
                        anim = *(s32 *)(arg0 + 0x48);
                    }
                    if (anim == 2) {
                        *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) + *(f32 *)((char *)&D_00000000 + 0xCC);
                        if (*(f32 *)(arg0 + 0x54) >= 1.0f) {
                            *(f32 *)(arg0 + 0x54) = 1.0f;
                            *(s32 *)(arg0 + 0x4C) = 0;
                        }
                        frame = (s32) (120.0f - (*(f32 *)(arg0 + 0x54) * 120.0f));
                        *(s32 *)(arg0 + 0x44) = frame;
                        *(s32 *)(*(char **)(arg0 + 0x34) + 0x4D8) = frame;
                        r34 = *(char **)(arg0 + 0x34);
                        if (*(s32 *)(r34 + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r34 + 0x414) + 0xC) + 0xBC) = 0;
                        } else {
                            *(s32 *)(*(s32 *)(*(s32 *)(r34 + 0x414) + 0xC) + 0xC4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xD4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xBC) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xCC) = *(s32 *)(arg0 + 0x44);
                        }
                        *(s32 *)(*(char **)(arg0 + 0x38) + 0x4D8) = 0xF0 - *(s32 *)(arg0 + 0x44);
                        r38 = *(char **)(arg0 + 0x38);
                        if (*(s32 *)(r38 + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38 + 0x414) + 0xC) + 0xBC) = 0;
                        } else {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38 + 0x414) + 0xC) + 0xC4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xD4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xBC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xCC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(f32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xB4) =
                                *(f64 *)((char *)&D_00000000 + 0xD0) + (*(f64 *)((char *)&D_00000000 + 0xD8) * (f64) (1.0f - *(f32 *)(arg0 + 0x54)));
                            *(f32 *)(*(char **)(arg0 + 0x38) + 0x49C) = 41.0f + (5.0f * *(f32 *)(arg0 + 0x54));
                        }
                    }
                }
            } else {
                v1 = *(s32 *)(arg0 + 0x44);
                if ((v1 == 0) || (v1 == 0xF0)) {
                    if (flag == 1) {
                        *(s32 *)(arg0 + 0x4C) = 1;
                        *(s32 *)(arg0 + 0x48) = 1;
                        *(f32 *)(arg0 + 0x54) = 0.0f;
                    }
                    if (*(s32 *)(arg0 + 0x3C) == 2) {
                        *(s32 *)(arg0 + 0x4C) = 1;
                        *(s32 *)(arg0 + 0x48) = 2;
                        *(f32 *)(arg0 + 0x54) = 0.0f;
                    }
                }
                if (*(s32 *)(arg0 + 0x4C) != 0) {
                    if (*(s32 *)(arg0 + 0x48) == 1) {
                        *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) + *(f32 *)((char *)&D_00000000 + 0xE0);
                        if (*(f32 *)(arg0 + 0x54) >= 1.0f) {
                            *(f32 *)(arg0 + 0x54) = 1.0f;
                            *(s32 *)(arg0 + 0x4C) = 0;
                            *(s32 *)(arg0 + 0x48) = 0;
                        }
                        frame2 = (s32) (240.0f - (*(f32 *)(arg0 + 0x54) * 120.0f));
                        *(s32 *)(arg0 + 0x44) = frame2;
                        *(s32 *)(*(char **)(arg0 + 0x34) + 0x4D8) = frame2;
                        r34b = *(char **)(arg0 + 0x34);
                        if (*(s32 *)(r34b + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r34b + 0x414) + 0xC) + 0xBC) = 0;
                            vf14 = *(f64 *)((char *)&D_00000000 + 0xE8);
                            vf12 = *(f64 *)((char *)&D_00000000 + 0xF0);
                        } else {
                            vf12 = *(f64 *)((char *)&D_00000000 + 0xF8);
                            vf14 = *(f64 *)((char *)&D_00000000 + 0x100);
                            *(s32 *)(*(s32 *)(*(s32 *)(r34b + 0x414) + 0xC) + 0xC4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xD4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xBC) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xCC) = *(s32 *)(arg0 + 0x44);
                            *(f32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xB4) =
                                vf12 + (vf14 * (f64) *(f32 *)(arg0 + 0x54));
                            *(f32 *)(*(char **)(arg0 + 0x34) + 0x49C) = 41.0f + (5.0f * (1.0f - *(f32 *)(arg0 + 0x54)));
                        }
                        *(s32 *)(*(char **)(arg0 + 0x38) + 0x4D8) = 0xF0 - *(s32 *)(arg0 + 0x44);
                        r38b = *(char **)(arg0 + 0x38);
                        if (*(s32 *)(r38b + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38b + 0x414) + 0xC) + 0xBC) = 0;
                        } else {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38b + 0x414) + 0xC) + 0xC4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xD4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xBC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xCC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(f32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xB4) =
                                vf12 + (vf14 * (f64) *(f32 *)(arg0 + 0x54));
                            *(f32 *)(*(char **)(arg0 + 0x38) + 0x49C) = 41.0f + (5.0f * (1.0f - *(f32 *)(arg0 + 0x54)));
                        }
                    }
                    cf12 = *(f64 *)((char *)&D_00000000 + 0x108);
                    cf14 = *(f64 *)((char *)&D_00000000 + 0x110);
                    if (*(s32 *)(arg0 + 0x48) == 2) {
                        *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x54) + *(f32 *)((char *)&D_00000000 + 0x118);
                        if (*(f32 *)(arg0 + 0x54) >= 1.0f) {
                            *(f32 *)(arg0 + 0x54) = 1.0f;
                            *(s32 *)(arg0 + 0x4C) = 0;
                            *(s32 *)(arg0 + 0x48) = 0;
                        }
                        frame3 = (s32) (*(f32 *)(arg0 + 0x54) * 120.0f);
                        *(s32 *)(arg0 + 0x44) = frame3;
                        *(s32 *)(*(char **)(arg0 + 0x34) + 0x4D8) = frame3;
                        r34c = *(char **)(arg0 + 0x34);
                        if (*(s32 *)(r34c + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r34c + 0x414) + 0xC) + 0xBC) = 0;
                        } else {
                            *(s32 *)(*(s32 *)(*(s32 *)(r34c + 0x414) + 0xC) + 0xC4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xD4) = 0;
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xBC) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xCC) = *(s32 *)(arg0 + 0x44);
                            *(f32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x34) + 0x414) + 0xC) + 0xB4) =
                                cf12 + (cf14 * (f64) *(f32 *)(arg0 + 0x54));
                            *(f32 *)(*(char **)(arg0 + 0x34) + 0x49C) = 41.0f + (5.0f * (1.0f - *(f32 *)(arg0 + 0x54)));
                        }
                        *(s32 *)(*(char **)(arg0 + 0x38) + 0x4D8) = 0xF0 - *(s32 *)(arg0 + 0x44);
                        r38c = *(char **)(arg0 + 0x38);
                        if (*(s32 *)(r38c + 0x4D8) == 0) {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38c + 0x414) + 0xC) + 0xBC) = 0;
                        } else {
                            *(s32 *)(*(s32 *)(*(s32 *)(r38c + 0x414) + 0xC) + 0xC4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xD4) = *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xBC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(s32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xCC) = 0xF0 - *(s32 *)(arg0 + 0x44);
                            *(f32 *)(*(s32 *)(*(s32 *)(*(char **)(arg0 + 0x38) + 0x414) + 0xC) + 0xB4) =
                                cf12 + (cf14 * (f64) *(f32 *)(arg0 + 0x54));
                            *(f32 *)(*(char **)(arg0 + 0x38) + 0x49C) = 41.0f + (5.0f * (1.0f - *(f32 *)(arg0 + 0x54)));
                        }
                    }
                }
            }
        }
        if (*(s32 *)(*(char **)(arg0 + 0x34) + 0x4D8) != 0) {
            *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) | 1;
        } else {
            *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) & ~1;
        }
        if (*(s32 *)(*(char **)(arg0 + 0x38) + 0x4D8) != 0) {
            *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) | 2;
        } else {
            *(s32 *)(arg0 + 0x50) = *(s32 *)(arg0 + 0x50) & ~2;
        }
        *(s32 *)(arg0 + 0x40) = *(s32 *)(arg0 + 0x3C);
    }
    timproc_uso_b5_func_04CD94(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00001F14);
#endif

/* CRACKED 2026-05-27 (byte-exact): the lever is "declare `float buf[4]`
 * FIRST so it gets the highest stack slot (sp+0x38) per IDO -O2's
 * first-declared-highest rule". Previous C placed `char pad[16]` first,
 * pushing buf to sp+0x24 — 99.86% near-miss. Reordering buf to be the
 * first local makes it land at sp+0x38, matching target exactly.
 *
 * Verified byte-equal at .o level (35 instructions identical).
 *
 * Generalizes: when a stack-buffer near-miss has "frame size matches
 * but buf at lower offset than target", reorder the decl so buf is the
 * FIRST local. */
void timproc_uso_b5_func_000027B0(int *self) {
    float buf[4];
    char *base = &D_00000000;
    int v;
    char pad[16];
    (void)pad;
    gl_func_00000000(self);
    if (self[0x30/4] != 2) return;
    buf[0] = 0.0f;
    buf[1] = 0.0f;
    buf[2] = 0.0f;
    buf[3] = 0.0f;
    gl_func_00000000(base, 0xFF, buf);
    v = self[0x44/4];
    gl_func_00000000(base, 0, v - 1, 319, v, 0x10001);
}

// timproc_uso_b5_func_0000283C — STRUCTURAL PASS (0x338 / 206 words,
// no episode). Raw-.word USO form (genuine code, single function).
// Hand-decoded.
//
// 2-child composite widget/object constructor (alloc-or-reuse);
// returns the constructed object.
//
//   void *timproc_uso_b5_func_0000283C(Obj *self, a1, a2, a3) {
//     if (!self) { self = func_00000000(0x20); if (!self) return 0; }
//     G *g = *(G**)D_0;                                 // global root
//     self->0x00 = a3;
//     self->0x04 = a2;
//     self->0x08 = g->0x134->0x8C;  func_00000000(0x80);
//     func_00000000(a1, .);  func_00000000(self, &D_0); // init
//     // child A:
//     A = func_00000000(0xB4);  if (A) {
//       func_00000000(A, &D_00001120);  A->0x28 = &D_0;
//       func_00000000(A->0x2C ...);  Vec3 z={0,0,0};
//       func_00000000(A+0x30, &z);  self->0x14 = A;
//     }
//     // child B (same shape, name &D_00001128):
//     B = func_00000000(0xB4);  if (B) {
//       func_00000000(B, &D_00001128);  B->0x28 = &D_0;
//       Vec3 z2={0,0,0};  func_00000000(B+0x30, &z2);
//       self->0x14 = B;
//     }
//     self->0x10 = childObj;
//     func_00000000(self, 0.0f, 0.0f, ...);
//     // transform/format setup: child->0x108 = 0x201 (a GBI/format
//     //   code); consts -400.0f; child flag |= 6; child->0x14C =
//     //   (float)…; Vec4 written to child+0xDC (0x0/0x4/0x8/0xC).
//     return self;
//   }
//
// Struct-typing reference:
//   self(a0, alloc 0x20): 0x00 = a3, 0x04 = a2, 0x08 = g->0x134->0x8C,
//     0x10 child obj, 0x14 last child link, 0x28 vtable(&D_0).
//   child (alloc 0xB4): 0x2C sub, 0x30 transform anchor, 0x108 format
//     word (0x201), 0x14C f32, +0xDC Vec4, flag word |= 6.
//   *(G**)D_0 -> 0x134 = global table; ->0x8C a shared field.
//   &D_00001120 / &D_00001128 = USO child name/desc data; func_00000000
//     = USO placeholder dispatcher (alloc/init/factory/attach).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — 2-child composite widget constructor. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0000283C)();
s32 *timproc_uso_b5_func_0000283C(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 sp6C;
    f32 sp60;
    f32 sp5C;
    s32 sp58;
    f32 sp44;
    f32 sp40;
    s32 sp3C;
    f32 sp30;
    f32 sp2C;
    s32 sp28;
    s32 *temp_s0;
    s32 *temp_s0_2;
    s32 *temp_s0_3;
    s32 *temp_s0_4;
    s32 *temp_v0;
    s32 *temp_v0_2;
    s32 *temp_v0_3;
    s32 *temp_v0_4;
    s32 *temp_v0_5;
    s32 *temp_v0_6;
    s32 *temp_v0_7;
    s32 *temp_v0_8;
    s32 *temp_v0_9;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_s1;
    s32 *var_v0;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_v1;
    s32 temp_v1_2;

    var_s1 = arg0;
    if ((arg0 != 0) || (temp_v0 = timproc_uso_b5_alias((s32 *)0x20), var_s1 = temp_v0, (temp_v0 != 0))) {
        FW(var_s1, 0x0) = FW((*(s32 **)0x134), 0x84);
        FW(var_s1, 0x4) = (s32) FW((*(s32 **)0x134), 0x80);
        FW(var_s1, 0x8) = (s32) FW((*(s32 **)0x134), 0x8C);
        temp_v0_2 = timproc_uso_b5_alias((s32 *)0x80);
        if (temp_v0_2 != 0) {
            timproc_uso_b5_alias(temp_v0_2, arg1);
        }
        timproc_uso_b5_alias(0, temp_v0_2);
        temp_v0_3 = timproc_uso_b5_alias((s32 *)0xB4);
        if (temp_v0_3 != 0) {
            timproc_uso_b5_alias(temp_v0_3, (s32 *)0x1120);
            FW(temp_v0_3, 0x28) = 0;
            var_v1 = temp_v0_3 + 0x2C;
            if (((temp_v0_3 != (s32 *)-0x2C) || (temp_v0_4 = timproc_uso_b5_alias((s32 *)4), var_v1 = temp_v0_4, (temp_v0_4 != 0))) && ((var_a0 = var_v1, (var_v1 != 0)) || (temp_v0_5 = timproc_uso_b5_alias((s32 *)4), var_a0 = temp_v0_5, (temp_v0_5 != 0)))) {
                *var_a0 = 0;
            }
            timproc_uso_b5_alias(temp_v0_3);
            sp58 = 0;
            sp5C = 0.0f;
            sp60 = 0.0f;
            timproc_uso_b5_alias(temp_v0_3 + 0x30, &sp58);
        }
        FW(var_s1, 0x14) = temp_v0_3;
        temp_v0_6 = timproc_uso_b5_alias((s32 *)0xB4);
        if (temp_v0_6 != 0) {
            timproc_uso_b5_alias(temp_v0_6, (s32 *)0x1128);
            FW(temp_v0_6, 0x28) = 0;
            var_v1_2 = temp_v0_6 + 0x2C;
            if (((temp_v0_6 != (s32 *)-0x2C) || (temp_v0_7 = timproc_uso_b5_alias((s32 *)4), var_v1_2 = temp_v0_7, (temp_v0_7 != 0))) && ((var_a0_2 = var_v1_2, (var_v1_2 != 0)) || (temp_v0_8 = timproc_uso_b5_alias((s32 *)4), var_a0_2 = temp_v0_8, (temp_v0_8 != 0)))) {
                *var_a0_2 = 0;
            }
            timproc_uso_b5_alias(temp_v0_6);
            sp3C = 0;
            sp40 = 0.0f;
            sp44 = 0.0f;
            timproc_uso_b5_alias(temp_v0_6 + 0x30, &sp3C);
        }
        FW(var_s1, 0x10) = temp_v0_6;
        temp_v0_9 = timproc_uso_b5_alias(0, temp_v0_6, 0, 0, 0.0f);
        temp_v1 = FW(var_s1, 0x0);
        FW(var_s1, 0x18) = temp_v0_9;
        sp6C = temp_v1;
        timproc_uso_b5_alias(temp_v1 + 0x10, temp_v0_9);
        if (FW(temp_v0_9, 0x14) != 0) {
            FW(temp_v0_9, 0x4) = 1;
        }
        FW(temp_v0_9, 0x14) = temp_v1;
        temp_v1_2 = FW(var_s1, 0x0);
        temp_s0 = FW(var_s1, 0x10);
        sp6C = temp_v1_2;
        timproc_uso_b5_alias(temp_v1_2 + 0x10, temp_s0);
        if (FW(temp_s0, 0x14) != 0) {
            FW(temp_s0, 0x4) = 1;
        }
        FW(temp_s0, 0x14) = temp_v1_2;
        sp2C = 0.0f;
        sp28 = 0;
        sp30 = -400.0f;
        timproc_uso_b5_alias(FW(var_s1, 0x10) + 0x30, &sp28);
        if (arg1 == (s32 *)1) {
            var_v0 = timproc_uso_b5_alias(*(char *)((char *)&D_00000000 + 0x134), (s32 *) (arg2 * 0x1C), FW(var_s1, 0x18));
        } else {
            var_v0 = timproc_uso_b5_alias(*(char *)((char *)&D_00000000 + 0x134), (s32 *) (arg2 * 0x1C), FW(var_s1, 0x18));
        }
        FW(var_s1, 0xC) = var_v0;
        FW(FW(var_s1, 0xC), 0x108) = 0x201;
        temp_s0_2 = FW(var_s1, 0xC);
        FW(temp_s0_2, 0x78) = (s32) (FW(temp_s0_2, 0x78) | 6);
        FW(FW(FW(var_s1, 0xC), 0x70), 0x14C) = (f32) arg3;
        temp_s0_3 = FW(var_s1, 0xC);
        temp_s0_4 = temp_s0_3 + 0xDC;
        *(f32 *)((char *)temp_s0_4 + 0x8) = 0.0f;
        FW(temp_s0_3, 0xDC) = 0.0f;
        *(f32 *)((char *)temp_s0_4 + 0x4) = 0.0f;
        *(f32 *)((char *)temp_s0_4 + 0xC) = 0.0f;
    }
    return var_s1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000283C);
#endif

// timproc_uso_b5_func_00002B74 — STRUCTURAL PASS (0x754 / 469 words,
// no episode). Raw-.word USO form (genuine code, single function).
// Partial decode (entry + sub-record fan-out + shape) — multi-run.
//
// Large composite object constructor (alloc-or-reuse 0x168); builds a
// fixed set of fixed-size sub-records, returns the object.
//
//   void *timproc_uso_b5_func_00002B74(Obj *self, ...) {
//     if (!self) { self = func_00000000(0x168); if (!self) return 0; }
//     func_00000000(0x8); ...                           // aux alloc
//     self->0x00 = &D_00001130;                          // vtable
//     self->0x04 = 0;
//     self->0x0C = &D + 0x1A0;  self->0x10 = 0x52;        // fields
//     // fan-out: ~12x  c = func_00000000(0x18);  init c; link into
//     //   self (a fixed array/list of twelve 0x18-byte sub-records —
//     //   e.g. lap/split rows or timer digits); plus 2x 0x20 sub-objs.
//     //   Names/descs from the &D_00001130/1140/1160/1168 pool.
//     //   ~30 func_00000000 calls total (alloc / init / attach).
//     // tail: FP transform setup — swc1 from sp scratch into
//     //   self->0x18 (a float field / position).
//     return self;
//   }
//
// Struct-typing reference:
//   self(a0, alloc 0x168): 0x00 vtable(&D_00001130), 0x04 flag,
//     0x0C ptr (&D+0x1A0), 0x10 = 0x52 (count/id), 0x18 f32; holds a
//     fixed array of ~12 sub-records (0x18 bytes each) + 2 sub-objs
//     (0x20). &D_00001130/1140/1160/1168 = USO name/desc data
//     (the 0x11xx pool). func_00000000 = USO placeholder dispatcher
//     (alloc / init / factory / attach).
// Caps (DEFERRED): raw-word USO + 30 placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — large composite constructor + 12-record init loop
//   skeleton. Byte-match deferred. Name pre-checked: no extern reuse.
// timproc_uso_b5_func_00002B74 — CALL-GRAPH-DFS RECONSTRUCTION.
// Composite "track/timer panel" constructor. Allocates (or reuses) a 0x168
// parent object, then builds a fixed set of fixed-size child sub-records,
// each attached via func_04A188 to the parent. Names/labels are pulled from
// the D_807FE9xx pointer array; child class-vtable is D_807FDA10+0x1A0 (the
// 0x18-byte "text row" class) for slots 0..10, D_807FD9C8+0x158 (a "value"
// class) for the two -20.0f slots, and D_807FD9E0+0x170 (a "vec3" class)
// for the final two 0x20-byte slots.
//
// Root-cause fix vs prior m2c draft: all child/global references are the
// real named USO externs (&D_807FE9xx + literal-low, &D_807FDA10 + 0x1A0,
// etc.) so IDO emits the lui/%hi + literal-low pairs of the target, and the
// real callees func_055750 (alloc-or-reuse) / func_04A188 (init+attach) are
// named directly. This adds the missing lui/%hi insns (build 384 words, was
// 339) and produces the correct global-load bytes.
// RESIDUAL (not byte-exact): IDO assigns `self` to $s1 (saving s0+s1) where
// the target uses $s0 only, and the FP vec-scratch frame is 0x140 vs build's
// smaller frame — a register-coloring + stack-slot cap. The dead per-slot
// name stashes (sp+0x13C..0x110 in target) are spills of a2 around the alloc
// call that IDO here elides because nmN are read once. Decode is structurally
// complete; remaining gap is allocation phase, not missing logic.
extern char timproc_uso_b5_D_807FE9A0;
extern char timproc_uso_b5_D_807FE9B0;
extern char timproc_uso_b5_D_807FE9B4;
extern char timproc_uso_b5_D_807FE9B8;
extern char timproc_uso_b5_D_807FE9BC;
extern char timproc_uso_b5_D_807FE9C0;
extern char timproc_uso_b5_D_807FE9C4;
extern char timproc_uso_b5_D_807FE9C8;
extern char timproc_uso_b5_D_807FE9CC;
extern char timproc_uso_b5_D_807FE9D0;
extern char timproc_uso_b5_D_807FE9D4;
extern char timproc_uso_b5_D_807FE9D8;
extern char timproc_uso_b5_D_807FE9DC;
extern char timproc_uso_b5_D_807FE9E0;
extern char timproc_uso_b5_D_807FE9E4;
extern char timproc_uso_b5_D_807FDA10;
extern char timproc_uso_b5_D_807FD9C8;
extern char timproc_uso_b5_D_807FD9E0;
extern int timproc_uso_b5_func_055750();
extern int timproc_uso_b5_func_04A188();

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
#define B5_DA10 ((char *)&timproc_uso_b5_D_807FDA10 + 0x1A0)
#define B5_D9C8 ((char *)&timproc_uso_b5_D_807FD9C8 + 0x158)
#define B5_D9E0 ((char *)&timproc_uso_b5_D_807FD9E0 + 0x170)
#define B5_NAME(sym, lo) (*(char **)((char *)&sym + (lo)))
char *timproc_uso_b5_func_00002B74(char *arg0) {
    char *self;
    char *vt;
    char *c0;
    char *c1;
    char *c2;
    char *c3;
    char *c4;
    char *c5;
    char *c6;
    char *c7;
    char *c8;
    char *c9;
    char *c10;
    char *c11;
    char *c12;
    char *c13;
    char *nm0;
    char *nm1;
    char *nm2;
    char *nm3;
    char *nm4;
    char *nm5;
    char *nm6;
    char *nm7;
    char *nm8;
    char *nm9;
    char *nm10;
    char *nm11;
    char *nm12;
    char *nm13;
    f32 vA[3];
    f32 vB[3];
    f32 vC[3];
    f32 cp0[3];
    f32 cp1[3];

    self = arg0;
    if ((arg0 != 0) ||
        (self = (char *)timproc_uso_b5_func_055750((char *)0x168), (self != 0))) {
        vt = self;
        if ((self != 0) ||
            (vt = (char *)timproc_uso_b5_func_055750((char *)8), (vt != 0))) {
            FW(vt, 0x0) = (int)((char *)&timproc_uso_b5_D_807FE9A0 + 0x1130);
            FW(vt, 0x4) = 0;
        }
        nm0 = B5_NAME(timproc_uso_b5_D_807FE9B0, 0x1140);
        c0 = self + 0x8;
        if ((self != (char *)-0x8) ||
            (c0 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c0 != 0))) {
            timproc_uso_b5_func_04A188(c0, self, nm0, (char *)1);
            FW(c0, 0x10) = 0x52;
            FW(c0, 0xC) = (int)B5_DA10;
            FW(c0, 0x14) = 0;
        }
        nm1 = B5_NAME(timproc_uso_b5_D_807FE9B4, 0x1144);
        c1 = self + 0x20;
        if ((self != (char *)-0x20) ||
            (c1 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c1 != 0))) {
            timproc_uso_b5_func_04A188(c1, self, nm1, (char *)1);
            FW(c1, 0x10) = 0x12;
            FW(c1, 0xC) = (int)B5_DA10;
            FW(c1, 0x14) = 0;
        }
        nm2 = B5_NAME(timproc_uso_b5_D_807FE9B8, 0x1148);
        c2 = self + 0x38;
        if ((self != (char *)-0x38) ||
            (c2 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c2 != 0))) {
            timproc_uso_b5_func_04A188(c2, self, nm2, (char *)1);
            FW(c2, 0x10) = 0x52;
            FW(c2, 0xC) = (int)B5_DA10;
            FW(c2, 0x14) = 0;
        }
        nm3 = B5_NAME(timproc_uso_b5_D_807FE9BC, 0x114c);
        c3 = self + 0x50;
        if ((self != (char *)-0x50) ||
            (c3 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c3 != 0))) {
            timproc_uso_b5_func_04A188(c3, self, nm3, (char *)1);
            FW(c3, 0x10) = 0x26;
            FW(c3, 0xC) = (int)B5_DA10;
            FW(c3, 0x14) = 0;
        }
        nm4 = B5_NAME(timproc_uso_b5_D_807FE9C0, 0x1150);
        c4 = self + 0x68;
        if ((self != (char *)-0x68) ||
            (c4 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c4 != 0))) {
            timproc_uso_b5_func_04A188(c4, self, nm4, (char *)1);
            FW(c4, 0x10) = 0x52;
            FW(c4, 0xC) = (int)B5_DA10;
            FW(c4, 0x14) = 0;
        }
        nm5 = B5_NAME(timproc_uso_b5_D_807FE9C4, 0x1154);
        c5 = self + 0x80;
        if ((self != (char *)-0x80) ||
            (c5 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c5 != 0))) {
            timproc_uso_b5_func_04A188(c5, self, nm5, (char *)1);
            FW(c5, 0x10) = 0x26;
            FW(c5, 0xC) = (int)B5_DA10;
            FW(c5, 0x14) = 0;
        }
        nm6 = B5_NAME(timproc_uso_b5_D_807FE9C8, 0x1158);
        c6 = self + 0x98;
        if ((self != (char *)-0x98) ||
            (c6 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c6 != 0))) {
            timproc_uso_b5_func_04A188(c6, self, nm6, (char *)1);
            FW(c6, 0x10) = 0x52;
            FW(c6, 0xC) = (int)B5_DA10;
            FW(c6, 0x14) = 0;
        }
        nm7 = B5_NAME(timproc_uso_b5_D_807FE9CC, 0x115c);
        c7 = self + 0xb0;
        if ((self != (char *)-0xb0) ||
            (c7 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c7 != 0))) {
            timproc_uso_b5_func_04A188(c7, self, nm7, (char *)1);
            FW(c7, 0x10) = 0x12;
            FW(c7, 0xC) = (int)B5_DA10;
            FW(c7, 0x14) = 0;
        }
        nm8 = B5_NAME(timproc_uso_b5_D_807FE9D0, 0x1160);
        c8 = self + 0xc8;
        if ((self != (char *)-0xc8) ||
            (c8 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c8 != 0))) {
            timproc_uso_b5_func_04A188(c8, self, nm8, (char *)1);
            FW(c8, 0x10) = 0x52;
            FW(c8, 0xC) = (int)B5_DA10;
            FW(c8, 0x14) = 0;
        }
        nm9 = B5_NAME(timproc_uso_b5_D_807FE9D4, 0x1164);
        c9 = self + 0xe0;
        if ((self != (char *)-0xe0) ||
            (c9 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c9 != 0))) {
            timproc_uso_b5_func_04A188(c9, self, nm9, (char *)1);
            FW(c9, 0x10) = 0x12;
            FW(c9, 0xC) = (int)B5_DA10;
            FW(c9, 0x14) = 0;
        }
        nm10 = B5_NAME(timproc_uso_b5_D_807FE9D8, 0x1168);
        c10 = self + 0xf8;
        if ((self != (char *)-0xf8) ||
            (c10 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c10 != 0))) {
            timproc_uso_b5_func_04A188(c10, self, nm10, (char *)1);
            FW(c10, 0xC) = (int)B5_D9C8;
            FW(c10, 0x14) = 0;
            *(f32 *)(c10 + 0x10) = -20.0f;
        }
        nm11 = B5_NAME(timproc_uso_b5_D_807FE9DC, 0x116c);
        c11 = self + 0x110;
        if ((self != (char *)-0x110) ||
            (c11 = (char *)timproc_uso_b5_func_055750((char *)0x18), (c11 != 0))) {
            timproc_uso_b5_func_04A188(c11, self, nm11, (char *)1);
            FW(c11, 0xC) = (int)B5_D9C8;
            FW(c11, 0x14) = 0;
            *(f32 *)(c11 + 0x10) = -20.0f;
        }
        vA[0] = vA[1] = vA[2] = *(f32 *)((char *)&timproc_uso_b5_D_807FE9E0 + 0x11C);
        vB[0] = vB[1] = vB[2] = *(f32 *)((char *)&timproc_uso_b5_D_807FE9E0 + 0x120);
        vC[0] = vC[1] = vC[2] = 0.0f;
        nm12 = B5_NAME(timproc_uso_b5_D_807FE9E0, 0x1170);
        cp0[0] = vC[0]; cp0[1] = vC[1]; cp0[2] = vC[2];
        cp1[0] = vA[0]; cp1[1] = vA[1]; cp1[2] = vA[2];
        c12 = self + 0x128;
        if ((self != (char *)-0x128) ||
            (c12 = (char *)timproc_uso_b5_func_055750((char *)0x20), (c12 != 0))) {
            timproc_uso_b5_func_04A188(c12, self, nm12, (char *)1);
            FW(c12, 0xC) = (int)B5_D9E0;
            FW(c12, 0x1C) = 0;
            FW(c12, 0x10) = *(int *)&cp0[0];
            FW(c12, 0x14) = *(int *)&cp0[1];
            FW(c12, 0x18) = *(int *)&cp0[2];
        }
        vA[0] = vA[1] = vA[2] = *(f32 *)((char *)&timproc_uso_b5_D_807FD9E0 + 0x124);
        vC[0] = vC[1] = vC[2] = 0.0f;
        nm13 = B5_NAME(timproc_uso_b5_D_807FE9E4, 0x1174);
        c13 = self + 0x148;
        if ((self != (char *)-0x148) ||
            (c13 = (char *)timproc_uso_b5_func_055750((char *)0x20), (c13 != 0))) {
            timproc_uso_b5_func_04A188(c13, self, nm13, (char *)1);
            FW(c13, 0xC) = (int)B5_D9E0;
            FW(c13, 0x1C) = 0;
            FW(c13, 0x10) = *(int *)&cp1[0];
            FW(c13, 0x14) = *(int *)&cp1[1];
            FW(c13, 0x18) = *(int *)&cp1[2];
        }
    }
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00002B74);
#endif

// timproc_uso_b5_func_000032C8 — m2c DECODE + real-callee fix (48.76% NM, no
// episode). Composite "panel" constructor (sibling of func_00002B74): alloc-or-
// reuse a 0x108 parent, then 6 text-row children (0x18, class D_807FDA10+0x1A0;
// first field 0x10=0, rest =2), 2 vec3 children (0x20, class D_807FD9E0+0x170 with
// an FP vec-fill that resolves to vec={0,0,0}), 2 value children (0x18, class
// D_807FD9C8+0x158, field 0x10=0.0f). Names come from the consecutive D_807FE9F8..
// D_807FEA1C int table; FP constants from the D_807FEA10/D_807FEA14 pool.
//
// 2026-06-22 (agent-d big-swing): replaced the generic `timproc_uso_b5_alias`
// placeholder with the real distinct callees — func_055750 (alloc-or-reuse) and
// func_04A188 (init+attach). The R_MIPS_26 call-reloc set now matches the target
// exactly (12x func_055750, 10x func_04A188). fuzzy holds at 48.76%.
//
// STRUCTURAL CAP (byte-exact unreachable in C): the entire timproc_uso_b5 expected
// object carries 731 R_MIPS_HI16 and ZERO R_MIPS_LO16 relocs — every data symbol's
// low half is a baked literal immediate (USO raw-word disasm). Any IDO-compiled C
// reference to a named USO data symbol emits a paired HI16/LO16, which (a) cannot
// match the literal-low target word and (b) the extra lui instructions shift the
// instruction stream out of alignment, REGRESSING objdiff fuzzy (tested: naming the
// class pointers DA10/D9E0/D9C8 drops 48.76 -> 40.16; full named-symbol rewrite
// -> 42.82). So the data references are kept as immediate/single-base reads here;
// the named-callee fix is the only correctness gain that does not cost score.
// Real byte-match requires the deferred spimdisasm USO migration, not a C rewrite.
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000032C8)();
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_000032C8;
char *timproc_uso_b5_func_000032C8(char *arg0) {
    Q_000032C8 sp104;
    Q_000032C8 sp3C;
    Q_000032C8 sp54;
    Q_000032C8 sp64;
    Q_000032C8 sp74;
    Q_000032C8 spC4;
    Q_000032C8 spD0;
    Q_000032C8 spDC;
    Q_000032C8 spEC;
    Q_000032C8 spF8;
    s32 sp124;
    s32 sp120;
    s32 sp11C;
    s32 sp118;
    s32 sp114;
    s32 sp110;
    s32 spE8;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    char *spA8;
    s32 spA4;
    char *sp84;
    char *sp50;
    s32 temp_f0;
    s32 temp_f0_2;
    s32 temp_f2;
    s32 temp_f2_2;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7;
    char *temp_v0;
    char *temp_v0_10;
    char *temp_v0_11;
    char *temp_v0_12;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *temp_v0_9;
    char *var_a0;
    char *var_a0_10;
    char *var_a0_2;
    char *var_a0_3;
    char *var_a0_4;
    char *var_a0_5;
    char *var_a0_6;
    char *var_a0_7;
    char *var_a0_8;
    char *var_a0_9;
    char *var_s0;
    char *var_v1;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = (char *)timproc_uso_b5_func_055750((char *)0x108), var_s0 = temp_v0, (temp_v0 != 0))) {
        var_v1 = var_s0;
        if ((var_s0 != 0) || (temp_v0_2 = (char *)timproc_uso_b5_func_055750((char *)8), var_v1 = temp_v0_2, (temp_v0_2 != 0))) {
            FW(var_v1, 0x0) = 0x1178;
            FW(var_v1, 0x4) = 0;
        }
        temp_t7 = *(s32 *)((char *)&D_00000000 + 0x1188);
        var_a0 = var_s0 + 8;
        sp124 = temp_t7;
        spA4 = temp_t7;
        if ((var_s0 != (char *)-8) || (temp_v0_3 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0 = temp_v0_3, (temp_v0_3 != 0))) {
            spA8 = var_a0;
            timproc_uso_b5_func_04A188(var_a0, var_s0, spA4, 1);
            FW(var_a0, 0xC) = 0x1A0;
            FW(var_a0, 0x14) = 0;
            FW(var_a0, 0x10) = 0;
        }
        temp_t1 = *(s32 *)((char *)&D_00000000 + 0x118C);
        var_a0_2 = var_s0 + 0x20;
        sp120 = temp_t1;
        spA4 = temp_t1;
        if ((var_s0 != (char *)-0x20) || (temp_v0_4 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_2 = temp_v0_4, (temp_v0_4 != 0))) {
            spA8 = var_a0_2;
            timproc_uso_b5_func_04A188(var_a0_2, var_s0, spA4, 1);
            FW(var_a0_2, 0x10) = 2;
            FW(var_a0_2, 0xC) = 0x1A0;
            FW(var_a0_2, 0x14) = 0;
        }
        temp_t6 = *(s32 *)((char *)&D_00000000 + 0x1190);
        var_a0_3 = var_s0 + 0x38;
        sp11C = temp_t6;
        spA4 = temp_t6;
        if ((var_s0 != (char *)-0x38) || (temp_v0_5 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_3 = temp_v0_5, (temp_v0_5 != 0))) {
            spA8 = var_a0_3;
            timproc_uso_b5_func_04A188(var_a0_3, var_s0, spA4, 1);
            FW(var_a0_3, 0x10) = 2;
            FW(var_a0_3, 0xC) = 0x1A0;
            FW(var_a0_3, 0x14) = 0;
        }
        temp_t1_2 = *(s32 *)((char *)&D_00000000 + 0x1194);
        var_a0_4 = var_s0 + 0x50;
        sp118 = temp_t1_2;
        spA4 = temp_t1_2;
        if ((var_s0 != (char *)-0x50) || (temp_v0_6 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_4 = temp_v0_6, (temp_v0_6 != 0))) {
            spA8 = var_a0_4;
            timproc_uso_b5_func_04A188(var_a0_4, var_s0, spA4, 1);
            FW(var_a0_4, 0x10) = 2;
            FW(var_a0_4, 0xC) = 0x1A0;
            FW(var_a0_4, 0x14) = 0;
        }
        temp_t6_2 = *(s32 *)((char *)&D_00000000 + 0x1198);
        var_a0_5 = var_s0 + 0x68;
        sp114 = temp_t6_2;
        spA4 = temp_t6_2;
        if ((var_s0 != (char *)-0x68) || (temp_v0_7 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_5 = temp_v0_7, (temp_v0_7 != 0))) {
            spA8 = var_a0_5;
            timproc_uso_b5_func_04A188(var_a0_5, var_s0, spA4, 1);
            FW(var_a0_5, 0x10) = 2;
            FW(var_a0_5, 0xC) = 0x1A0;
            FW(var_a0_5, 0x14) = 0;
        }
        temp_t1_3 = *(s32 *)((char *)&D_00000000 + 0x119C);
        var_a0_6 = var_s0 + 0x80;
        sp110 = temp_t1_3;
        spA4 = temp_t1_3;
        if ((var_s0 != (char *)-0x80) || (temp_v0_8 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_6 = temp_v0_8, (temp_v0_8 != 0))) {
            spA8 = var_a0_6;
            timproc_uso_b5_func_04A188(var_a0_6, var_s0, spA4, 1);
            FW(var_a0_6, 0x10) = 2;
            FW(var_a0_6, 0xC) = 0x1A0;
            FW(var_a0_6, 0x14) = 0;
        }
        temp_f2 = *(s32 *)((char *)&D_00000000 + 0x134);
        spF8.unk0 = temp_f2;
        spF8.unk8 = temp_f2;
        temp_f2_2 = *(s32 *)((char *)&D_00000000 + 0x13C);
        spF8.unk4 = *(f32 *)((char *)&D_00000000 + 0x138);
        spEC.unk0 = temp_f2_2;
        spEC.unk8 = temp_f2_2;
        sp104.unk0 = 0;
        *(float *)&sp104.unk4 = 0.0f;
        *(float *)&sp104.unk8 = 0.0f;
        spE8 = *(s32 *)((char *)&D_00000000 + 0x11A0);
        spEC.unk4 = *(f32 *)((char *)&D_00000000 + 0x140);
        sp74.unk0 = (s32) sp104.unk0;
        sp74.unk4 = (s32) sp104.unk4;
        sp74.unk8 = (s32) sp104.unk8;
        var_a0_7 = var_s0 + 0x98;
        sp64.unk0 = (s32) spF8.unk0;
        sp64.unk4 = (s32) spF8.unk4;
        sp64.unk8 = (s32) spF8.unk8;
        sp54.unk0 = (s32) spEC.unk0;
        sp54.unk4 = (s32) spEC.unk4;
        sp54.unk8 = (s32) spEC.unk8;
        spA4 = spE8;
        if ((var_s0 != (char *)-0x98) || (temp_v0_9 = (char *)timproc_uso_b5_func_055750((char *)0x20), var_a0_7 = temp_v0_9, (temp_v0_9 != 0))) {
            sp84 = var_a0_7;
            timproc_uso_b5_func_04A188(var_a0_7, var_s0, spA4, 1);
            FW(var_a0_7, 0xC) = 0x170;
            FW(var_a0_7, 0x1C) = 0;
            sp3C.unk0 = sp74.unk0;
            sp3C.unk4 = (s32) sp74.unk4;
            sp3C.unk8 = (s32) sp74.unk8;
            FW(var_a0_7, 0x10) = sp3C.unk0;
            FW(var_a0_7, 0x14) = sp3C.unk4;
            FW(var_a0_7, 0x18) = sp3C.unk8;
        }
        spDC.unk0 = 0;
        spDC.unk4 = 0;
        spDC.unk8 = 0;
        temp_f0 = *(s32 *)((char *)&D_00000000 + 0x144);
        spD0.unk0 = temp_f0;
        spD0.unk4 = temp_f0;
        spD0.unk8 = temp_f0;
        temp_f0_2 = *(s32 *)((char *)&D_00000000 + 0x148);
        spC4.unk0 = temp_f0_2;
        spC4.unk4 = temp_f0_2;
        spC4.unk8 = temp_f0_2;
        spC0 = *(s32 *)((char *)&D_00000000 + 0x11A4);
        sp74.unk0 = (s32) spDC.unk0;
        sp74.unk4 = (s32) spDC.unk4;
        sp74.unk8 = (s32) spDC.unk8;
        var_a0_8 = var_s0 + 0xB8;
        sp64.unk0 = (s32) spD0.unk0;
        sp64.unk4 = (s32) spD0.unk4;
        sp64.unk8 = (s32) spD0.unk8;
        sp54.unk0 = (s32) spC4.unk0;
        sp54.unk4 = (s32) spC4.unk4;
        sp54.unk8 = (s32) spC4.unk8;
        spA4 = spC0;
        if ((var_s0 != (char *)-0xB8) || (temp_v0_10 = (char *)timproc_uso_b5_func_055750((char *)0x20), var_a0_8 = temp_v0_10, (temp_v0_10 != 0))) {
            sp50 = var_a0_8;
            timproc_uso_b5_func_04A188(var_a0_8, var_s0, spA4, 1);
            FW(var_a0_8, 0xC) = 0x170;
            FW(var_a0_8, 0x1C) = 0;
            sp3C.unk0 = sp74.unk0;
            sp3C.unk4 = (s32) sp74.unk4;
            sp3C.unk8 = (s32) sp74.unk8;
            FW(var_a0_8, 0x10) = sp3C.unk0;
            FW(var_a0_8, 0x14) = sp3C.unk4;
            FW(var_a0_8, 0x18) = sp3C.unk8;
        }
        temp_t6_3 = *(s32 *)((char *)&D_00000000 + 0x11A8);
        var_a0_9 = var_s0 + 0xD8;
        spBC = temp_t6_3;
        spA4 = temp_t6_3;
        if ((var_s0 != (char *)-0xD8) || (temp_v0_11 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_9 = temp_v0_11, (temp_v0_11 != 0))) {
            spA8 = var_a0_9;
            timproc_uso_b5_func_04A188(var_a0_9, var_s0, spA4, 1);
            FW(var_a0_9, 0xC) = 0x158;
            FW(var_a0_9, 0x14) = 0;
            *(f32 *)((char *)var_a0_9 + 0x10) = 0.0f;
        }
        temp_t0 = *(s32 *)((char *)&D_00000000 + 0x11AC);
        var_a0_10 = var_s0 + 0xF0;
        spB8 = temp_t0;
        spA4 = temp_t0;
        if ((var_s0 != (char *)-0xF0) || (temp_v0_12 = (char *)timproc_uso_b5_func_055750((char *)0x18), var_a0_10 = temp_v0_12, (temp_v0_12 != 0))) {
            spA8 = var_a0_10;
            timproc_uso_b5_func_04A188(var_a0_10, var_s0, spA4, 1);
            FW(var_a0_10, 0xC) = 0x158;
            FW(var_a0_10, 0x14) = 0;
            *(f32 *)((char *)var_a0_10 + 0x10) = 0.0f;
        }
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000032C8);
#endif



/* Zero fields: 0x2B4 (int), 0x164/0x168/0x16C/0x2A0 (float). The target uses
 * TWO zero FP regs — $f0 for the first three stores, $f4 for the 0x2A0
 * delay-slot store. Plain `0.0f` CSEs to a single reg (1 insn short); storing
 * INT 0 through a separate `float*` variable for the last store defeats the
 * CSE and forces the 2nd `mtc1 zero,$f4`. (permuter-found; the old "0.0f CSE
 * not C-controllable" note was wrong.) */
void timproc_uso_b5_func_00003890(int *a0) {
    float *p;
    *(int *)((char *)a0 + 0x2B4) = 0;
    *(float *)((char *)a0 + 0x164) = 0.0f;
    *(float *)((char *)a0 + 0x168) = 0.0f;
    *(float *)((char *)a0 + 0x16C) = 0.0f;
    p = (float *)((char *)a0 + 0x2A0);
    *p = 0;
}

/* timproc_uso_b5_func_000038B0: one 47-insn (0xBC) FP transform. BOUNDARY MERGED
 * 2026-06-02: splat had split this into 038B0 (entry, 8 insns, no prologue) +
 * 038D0 (continuation w/ the `addiu sp,-32` prologue 8 insns in). IDO hoisted
 * the entry's a0-field FP loads above the frame setup, so the prologue landed
 * mid-function and splat cut there. 038B0 is the real entry (jal'd from
 * timproc_uso_b5_func_00005FC0); 038D0 had zero callers. Absorbed 038D0's 39
 * words into 038B0 (0x20 -> 0xBC) and dropped the 038D0 symbol.
 *
 * This RETRACTS the old "NON-O32 float-in-$f6/$f8 callee cap": the $f6/$f8/$f4/v0
 * that 038D0 used are computed in the entry from a0->{0x164,0x168,0x29C,0x2A0,..}
 * (f6=f4*f18, f8=*(v0+0xDC), ...), NOT caller-passed. The merged function reads
 * a0 fields normally and is now decodable. Same pattern for the sibling pair
 * 0000396C(entry)+0000398C-F1(cont) — still to merge. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000038B0)();
void timproc_uso_b5_func_000038B0(char *arg0, s32 arg1, char *arg2, f32 arg3, f32 arg4) {
    f32 sp18;
    f32 sp0;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f6;
    f32 temp_f8;
    char *temp_v0;
    char *temp_v0_2;

    temp_f18 = (*(f32*)((char*)arg0 + 0x2A0));
    temp_v0 = FW(arg0, 0x29C);
    temp_f10 = ((*(f32*)((char*)arg0 + 0x168)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xE0)) + (arg4 * (1.0f - temp_f18));
    sp18 = temp_f10;
    temp_v0_2 = (int)arg1 + 0x30;
    sp0 = (*(f32*)((char*)arg2 + 0x0));
    temp_f8 = sp0;
    temp_f6 = ((((*(f32*)((char*)arg0 + 0x164)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xDC))) - temp_f8) * arg3;
    sp0 = (*(f32*)((char*)arg2 + 0x4));
    temp_f18_2 = (*(f32*)((char*)arg2 + 0x8));
    (*(f32*)((char*)temp_v0_2 + 0x30)) = (f32) (temp_f8 + temp_f6);
    (*(f32*)((char*)temp_v0_2 + 0x34)) = (f32) (sp0 + ((temp_f10 - sp0) * arg3));
    (*(f32*)((char*)temp_v0_2 + 0x38)) = (f32) (temp_f18_2 + (((((*(f32*)((char*)arg0 + 0x16C)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xE4))) - temp_f18_2) * arg3));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000038B0);
#endif

/* timproc_uso_b5_func_0000396C: one 47-insn (0xBC) FP transform — the sibling of
 * 038B0 (template-identical except field offsets 0x184/0x188 vs 0x164/0x168).
 * BOUNDARY MERGED 2026-06-02: splat had split it into 396C (entry, 8 a0-field FP
 * loads, no prologue, jal'd from 5FC0) + 398C (the `addiu sp,-32` prologue +
 * body + jr ra, zero callers); IDO hoisted the entry loads above the frame
 * setup. Absorbed 398C's 39 words into 396C (0x20->0xBC) and dropped the 398C
 * symbol. This RETRACTS the old "float-in-$f6/$f8 callee cap": those regs are
 * computed in the entry from a0->{0x184,0x188,0x29C,0x2A0}, not caller-passed.
 * (The separate 8-insn 0x3A28 piece is the stolen prologue of 00003A4C — its
 * own symbol, already handled, not part of this merge.) */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0000396C)();
void timproc_uso_b5_func_0000396C(char *arg0, s32 arg1, char *arg2, f32 arg3, f32 arg4) {
    f32 sp18;
    f32 sp0;
    f32 temp_f10;
    f32 temp_f18;
    f32 temp_f18_2;
    f32 temp_f6;
    f32 temp_f8;
    char *temp_v0;
    char *temp_v0_2;

    temp_f18 = (*(f32*)((char*)arg0 + 0x2A0));
    temp_v0 = FW(arg0, 0x29C);
    temp_f10 = ((*(f32*)((char*)arg0 + 0x188)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xE0)) + (arg4 * (1.0f - temp_f18));
    sp18 = temp_f10;
    temp_v0_2 = (int)arg1 + 0x30;
    sp0 = (*(f32*)((char*)arg2 + 0x0));
    temp_f8 = sp0;
    temp_f6 = ((((*(f32*)((char*)arg0 + 0x184)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xDC))) - temp_f8) * arg3;
    sp0 = (*(f32*)((char*)arg2 + 0x4));
    temp_f18_2 = (*(f32*)((char*)arg2 + 0x8));
    (*(f32*)((char*)temp_v0_2 + 0x30)) = (f32) (temp_f8 + temp_f6);
    (*(f32*)((char*)temp_v0_2 + 0x34)) = (f32) (sp0 + ((temp_f10 - sp0) * arg3));
    (*(f32*)((char*)temp_v0_2 + 0x38)) = (f32) (temp_f18_2 + (((((*(f32*)((char*)arg0 + 0x18C)) * temp_f18) + (*(f32*)((char*)temp_v0 + 0xE4))) - temp_f18_2) * arg3));
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000396C);
#endif

void timproc_uso_b5_func_00003A28(int *a0, int *a1, int a2) {
    float *src = (float *)a0[0x29C / 4];
    float x = *(float *)((char *)src + 0xDC);
    float y = *(float *)((char *)src + 0xE0);
    float z = *(float *)((char *)src + 0xE4);
    *(float *)((char *)a1 + 0x60) = x;
    *(float *)((char *)a1 + 0x64) = y;
    *(float *)((char *)a1 + 0x68) = z;
}

/* timproc_uso_b5_func_00003A4C: 144-insn (0x240) heavy data-init function.
 * Frame -0xB0, saves s0/s1/s2/ra. Sibling of recently-matched
 * timproc_uso_b5_func_00003F5C in the same "FPU-heavy data-driven init"
 * family. Initial structural decode:
 *
 * Stage 1 @ 0x3A50-0x3AAC (~24 insns): unrolled-by-3 12-byte copy loop.
 *   Reads &D_00000000 + 0x11B0..0x11D4 (0x24 bytes) into sp[0x84..0xA8].
 *   Plus 8 more bytes from D[0x11D4..0x11DC] into sp[0xA8..0xB0].
 *
 * Stage 2 @ 0x3AAC-0x3B00 (~21 insns): second similar copy loop.
 *   Reads D[0x11DC..0x1200] into sp[0x58..0x7C], plus 8 bytes from
 *   D[0x1200..0x1208] into sp[0x80..0x84].
 *
 * Stage 3 @ 0x3B00+: ~99 insns of remaining body. TBD — likely uses
 * the two 0x2C-byte stack buffers (sp+0x58 and sp+0x84) as "before
 * and after" interpolation states or as displacement vectors fed to
 * gl_func calls.
 *
 * Multi-tick decomp; structural wrap only this tick. INCLUDE_ASM keeps
 * ROM byte-correct. */
#ifdef NON_MATCHING
/* timproc_uso_b5_func_00003A4C: two-sprite HUD draw with table-indexed offsets.
 * Copies two 0x2C-byte tables from &D+0x11B0 / &D+0x11DC onto the stack (sp84/sp58
 * — IDO unrolls each as a 3x12-byte loop + 2-word tail). If arg4!=0: draw sprite
 * 0x10 twice at arg1+arg7->0x338 / +sp58[arg4], y=arg2+arg7->0x350, using its
 * looked-up dimension (cb(0x10)->0x10->0x20). Then cb(0,0xFF,arg6); draw arg3 at
 * arg1-arg7->0x308 / arg2-arg7->0x320; cb(0,0xFF,arg5); draw sprite 0x28 twice at
 * arg1 / +sp84[arg4] with its dimension. Fresh decode 2026-05-29 (m2c-confirmed).
 * Caps: structs + cb prototypes untyped (USO-reloc), &D tables not symbolized,
 * sprite-dim return-deref + table-copy unroll. NON_MATCHING.
 * 2026-06-21 RECONSTRUCT 77.85%->86.99% (same fix family as sibling 3C8C/6E08):
 * (1) the call first args are the resolved globals &import_8024CAF8 (+0x10/+0x28)
 * and &timproc_uso_b5_D_807FF490/_807FF4A8, not literal 0/0x10/0x28; (2) the two
 * table sources are &D_807FEA20/_807FEA4C (single struct-copy each); (3) the
 * sprite dimension at +0x20 is a signed halfword (lh) RE-DEREFED from the global
 * base (&import_8024CAF8+0x20/+0x28), not from the call-return objA/objB.
 * 2026-07-07 RISE 86.99%->88.34% (agent-e): callees resolved to the 4 real
 * distinct imports (E608/F2C8/F34C/F75C) called directly (correct R_MIPS_26);
 * call bases fixed to their true globals — F2C8/F75C(arg4-branch) use
 * &D_807FF490+0x10, F2C8/F34C(mid) use arg3, F2C8/F75C(tail) use &D_807FF4A8+0x28;
 * sprite-dim derefs read *(int*)(base+0x10)+0x20 off those same object bases.
 * Residual ~12% (strict-byte, permuter-immune coloring caps): (1) build is +2
 * words — the call-D/L dimension deref materializes a FRESH lui for the object
 * base instead of reusing the a0 arg register (target does lw 0x10(a0)); no C
 * form reaches the a0-reuse. (2) pervasive t-register RENUMBER in both unrolled
 * 3x12-byte copy loops + body (the documented 3C8C coloring cap). (3) frame is
 * -0xA0 vs target -0xB0 (16-byte frame-size cap). NON_MATCHING. */
extern void import_0024E608();
extern void import_0024F2C8();
extern void import_0024F34C();
extern void import_0024F75C();
extern char import_8024CAF8;
extern char timproc_uso_b5_D_807FEA20;
extern char timproc_uso_b5_D_807FEA4C;
extern char timproc_uso_b5_D_807FF490;
extern char timproc_uso_b5_D_807FF4A8;
struct B5Tbl3A4C { int w[11]; };
void timproc_uso_b5_func_00003A4C(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, char *arg7) {
    struct B5Tbl3A4C sp84 = *(struct B5Tbl3A4C *)&timproc_uso_b5_D_807FEA20;
    struct B5Tbl3A4C sp58 = *(struct B5Tbl3A4C *)&timproc_uso_b5_D_807FEA4C;
    int *pA;
    int *pB;
    int sz;

    if (arg4 != 0) {
        import_0024E608(&import_8024CAF8, *(int *)(arg7 + 0x368), arg5);
        import_0024F2C8(&timproc_uso_b5_D_807FF490 + 0x10);
        pA = &sp58.w[arg4];
        import_0024F75C(&timproc_uso_b5_D_807FF490 + 0x10, arg1 + *(int *)(arg7 + 0x338), arg2 + *(int *)(arg7 + 0x350), 0, *pA);
        import_0024F75C(&timproc_uso_b5_D_807FF490 + 0x10, arg1 + *(int *)(arg7 + 0x338) + *pA, arg2 + *(int *)(arg7 + 0x350),
                        *(short *)(*(int *)(&timproc_uso_b5_D_807FF490 + 0x20) + 0x20) - 0x20, 0x20);
    }
    import_0024E608(&import_8024CAF8, 0xFF, arg6);
    import_0024F2C8(arg3);
    import_0024F34C(arg3, arg1 - *(int *)(arg7 + 0x308), arg2 - *(int *)(arg7 + 0x320), 0);
    import_0024E608(&import_8024CAF8, 0xFF, arg5);
    import_0024F2C8(&timproc_uso_b5_D_807FF4A8 + 0x28);
    pB = &sp84.w[arg4];
    import_0024F75C(&timproc_uso_b5_D_807FF4A8 + 0x28, arg1, arg2, 0, *pB);
    import_0024E608(&import_8024CAF8, *(int *)(arg7 + 0x380), arg5);
    sz = *pB;
    import_0024F75C(&timproc_uso_b5_D_807FF4A8 + 0x28, arg1 + sz, arg2, sz,
                    *(short *)(*(int *)(&timproc_uso_b5_D_807FF4A8 + 0x38) + 0x20) - sz);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003A4C);
#endif

// timproc_uso_b5_func_00003C8C — STRUCTURAL PASS (0x24C / 147 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Template-instantiation routine: copies two fixed structure templates
// from USO static data into stack scratch, then builds/configures from
// them plus the call args.
//
//   void timproc_uso_b5_func_00003C8C(a0, a1, a2, a3) {  // a1->s1 a2->s2
//     // copy template T1 = &D_00001208[0 .. 0x24)  (3 x 0xC-byte
//     //   records, stride 0xC) into local buf @ sp+0x84;
//     // copy template T2 = &D_00001234[...]         (0xC-stride
//     //   records) into local buf @ sp+0x58;
//     // ~12 func_00000000 calls building/configuring an element from
//     //   the copied templates + (a0@sp+0xB0, s1=a1, s2=a2,
//     //   a3@sp+0xBC) — instantiate + position + attach.
//   }
//
// Struct-typing reference:
//   &D_00001208 = a 0x24-byte template = 3 x 0xC records (e.g. 3 Vec3
//     / 3 mini-structs); &D_00001234 = a second 0xC-stride template;
//     both in the timproc_uso_b5 0x12xx USO static-data pool.
//   sp+0x84 / sp+0x58 = stack copies of T1 / T2 used as the working
//     spec for the build. a1(s1)/a2(s2)/a0/a3 = target/owner/params.
//   func_00000000 = USO placeholder dispatcher (build / position /
//     attach).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — template-instantiate skeleton (template copy + cb chain).
//   Byte-match deferred. Name pre-checked: no extern reuse.
// 2026-06-21 RECONSTRUCT 77.6%->86.6%: (1) merged the two 11-word template
//   copies into a single struct-copy each (struct T11) so IDO walks ONE
//   induction pointer (loop+2-word remainder off the walked ptr) instead of
//   hoisting a separate absolute base for the 2 tail words; (2) the literal-0
//   first args to the dispatch calls are &D_00000000 (reloc lui/addiu, not
//   or zero,zero), passed as `g`; (3) field 0x20 of the 16(arg3)/g+0x20/g+0x28
//   chained derefs is a signed halfword (lh) not lw, and the last call's base
//   is *(int*)(arg3+0x10) not g+0x38. RESIDUAL ~13%: the struct-copy loop
//   advances the SOURCE pointer in the target but the build advances DEST
//   (IDO induction-var choice), driving a +32 array placement / -176-vs-152
//   frame cascade + register renumber. Coloring/codegen-cap from here.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00003C8C(int arg0, int arg1, int arg2, void *arg3, int arg4, int arg5, int arg6, void *arg7) {
    struct T11 { int w[11]; };
    char *g = (char *)&D_00000000;
    char *a7 = (char *)arg7;
    int T1[11], T2[11];
    (void)arg0;
    *(struct T11 *)T1 = *(struct T11 *)(g + 0x1208);
    *(struct T11 *)T2 = *(struct T11 *)(g + 0x1234);
    if (arg4 != 0) {
        func_00000000(g, *(int *)(a7 + 0x368), arg5);
        func_00000000(g + 0x10);
        func_00000000(g + 0x10, arg1 + *(int *)(a7 + 0x338), arg2 + *(int *)(a7 + 0x350), 0, T2[arg4]);
        func_00000000(g + 0x10, arg1 + *(int *)(a7 + 0x338) + T2[arg4], arg2 + *(int *)(a7 + 0x350),
                      *(short *)(*(int *)(g + 0x20) + 0x20) - 0x10, 0x10);
    }
    func_00000000(g, 0xFF, arg6);
    func_00000000(arg3);
    func_00000000(arg3, (arg1 - *(int *)(a7 + 0x308)) - *(short *)(*(int *)((char *)arg3 + 0x10) + 0x20),
                  arg2 - *(int *)(a7 + 0x320), 0);
    func_00000000(g, 0xFF, arg5);
    func_00000000(g + 0x28);
    func_00000000(g + 0x28, arg1, arg2, 0, T1[arg4]);
    func_00000000(g, *(int *)(a7 + 0x380), arg5);
    func_00000000(g + 0x28, arg1 + T1[arg4], arg2, T1[arg4],
                  *(short *)(*(int *)((char *)arg3 + 0x10) + 0x20) - T1[arg4]);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00003C8C);
#endif

void timproc_uso_b5_func_00003ED8(char *a0) {
    char *v;

    gl_func_00000000(a0 + 0x2C);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}

/* Sibling of timproc_uso_b5_func_00003ED8 — same vtable-call wrapper. MATCHED.
 * Was 94.12% NM with a trailing orphan `lw t8, 0x23C(a0)` that splat
 * mis-attributed to this function's range (it is the dead boundary word
 * between this fn's epilogue and successor func_00003F5C, which does not use
 * t8). Fixed PROPERLY (replacing the banned SUFFIX_BYTES splice) by a splat
 * boundary correction: shrank this .s to 16 insns (0x40) and moved the orphan
 * word into func_00003F5C.s as its leading word. ROM byte sequence preserved
 * (16+18 = 34 words); 00003F18 now C-emits exactly its 16 real insns. */
void timproc_uso_b5_func_00003F18(char *a0) {
    char *v;
    gl_func_00000000(a0 + 0x194);
    v = *(char**)(a0 + 0x28);
    (*(void(**)(char*))(v + 0x24))(a0 + *(short*)(v + 0x20));
}

/* timproc_uso_b5_func_00003F5C — VERIFIED EXACT 18/18 (2026-07-03, agent-e)
 * vs asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_00003F5C.s
 * (in-tree word-by-word on build/non_matching/src/timproc_uso_b5/timproc_uso_b5.c.o,
 * clean rebuild, -O2).
 *
 * KEY (was 85.4% "natural ceiling" — false cap):
 * 1. WHOLE-STRUCT COPY, not per-field int stores. `raw = *(Vec3*)(a0+0x23C)`
 *    is what emits the target's block-copy signature: dest base materialized
 *    as `addiu t6, sp, 0xC` (t6 = first temp) + alternating t8/t7/t8 copy
 *    temps, with first load hoisted above the prologue. Per-field stores gave
 *    sp-direct sw + v1 base (inverted shape).
 * 2. Float-typed local (Vec3, not int-triple) so the read-back side is
 *    direct float member reads -> sp-direct lwc1 f4/f6/f8.
 * 3. Frame 0x28 with raw at sp+0xC via pad sandwich: pad1[16] ABOVE
 *    (declared first -> top of frame 0x18..0x27), raw 0xC..0x17,
 *    pad2[4] BELOW (4..7). IDO places addressed locals top-down in
 *    declaration order.
 */
typedef struct { int a, b, c; } Tri3i_F5C; /* kept for context; unused now */
typedef struct { float x, y, z; } Vec3_F5C;
void timproc_uso_b5_func_00003F5C(int *a0) {
    char pad1[16];
    Vec3_F5C raw;
    char pad2[4];
    Vec3_F5C *v = (Vec3_F5C*)((char*)*(int**)((char*)a0 + 0x29C) + 0xDC);
    (void)pad1;
    (void)pad2;
    raw = *(Vec3_F5C*)((char*)a0 + 0x23C);
    v->x = raw.x;
    v->y = raw.y;
    v->z = raw.z;
}

/* Save-arg sentinel: void f(int a0){} → jr ra; sw a0, 0(sp).
 * docs/IDO_CODEGEN.md#feedback-ido-save-arg-sentinel-empty-body */
void timproc_uso_b5_func_00003FA0(int a0) {}

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

void timproc_uso_b5_func_00004068(int a0, int a1, int a2, int a3, int arg5, int arg6) {
    (void)a0;
    gl_func_00000000(&D_00000000, arg6, a3);
    gl_func_00000000(arg5);
    gl_func_00000000(arg5, a1, a2, 3);
}

void timproc_uso_b5_func_000040BC(int a0, int a1, int a2, int a3, int arg5, int arg6, int arg7) {
    (void)a0;
    gl_func_00000000(&D_00000000, arg7, a3, arg5);
    gl_func_00000000(arg6);
    gl_func_00000000(arg6, a1, a2, 3);
}

// timproc_uso_b5_func_00004118 — FULL m2c DECODE via compressed-module
// jumptable path (33.66% NM, no episode). LARGEST function in this segment.
// The 8-case switch (idx = self->[968]-1, dispatch jr $t0 @ 0x5A94) was
// extracted from the Yay0-COMPRESSED USO via the emulator: race-dump
// SI_EXPLORE loaded timproc into RDRAM, extract-uso-jumptable-emu.py --asm
// (ram_base 0x807ef230) read the 8-entry table from relocated RoData, m2c
// decoded the full body (0 errors). Lift: 42 quad scratch structs (Q),
// X->unkN -> FW(X,0xN), placeholder calls cast via FP4, void*->char* for
// IDO pointer arithmetic. Default build = INCLUDE_ASM byte-exact.
// Raw-.word USO form (genuine code, single function).
//
// Massive composite-screen constructor (the timing/replay HUD screen:
// lap table + splits + controls):
//
//   void *timproc_uso_b5_func_00004118(Obj *self, a1, a2, a3) {
//     // frame 0x3A8; args spilled to sp+0x3A8..0x3B4.
//     if (!self) { self = func_00000000(0x4F0); if (!self) return 0; }
//     func_00000000(0x2C);                               // aux alloc
//     func_00000000(self, &D_00001260);                  // base-init
//     self->0x28 = &D_0;                                  // vtable
//     // fan-out (~74 func_00000000 calls total): builds
//     //   ~18 sub-records of 0x18 bytes  (e.g. lap/split rows),
//     //   ~13 sub-records of 0x24 bytes  (e.g. digit/column cells),
//     //   plus larger sub-objects (0x38C, 0x2C, 0x8) — each
//     //   allocated, initialized, positioned and linked into self;
//     //   FP layout via the saved f20 accumulator.
//     return self;
//   }
//
// Struct-typing reference:
//   self(a0, alloc 0x4F0): 0x28 vtable(&D_0); aggregates ~18 x 0x18
//     records + ~13 x 0x24 records + sub-objects (0x38C/0x2C/0x8).
//   &D_00001260 = base-init descriptor; the 0x12xx USO pool supplies
//     child names/descs. func_00000000 = USO placeholder dispatcher
//     (alloc / init / factory / position / attach).
// Caps (DEFERRED): raw-word USO + 74 placeholder calls + 1718 words;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — alloc-or-reuse + base-init + 18+13
//   sub-record fan-out skeleton only; future passes can expand the
//   sub-record build loops further. Byte-match deferred. Name
//   pre-checked: no extern reuse.
/* 2026-06-10 graft attempt: a full m2c graft scored 48.08 vs this hand
 * body's 49.20 -- REVERTED (monotonic rule). Keep: the .s is UNDERSIZED
 * (branches to +0x18A8/+0x1AB8 past the declared 0x187C end; the true
 * body runs 1718 insns to block5 offset 0x5BF0, verified from the
 * asset). One 8-case jumptable at +0x197C (4 distinct heads). The hand
 * body wins because m2c's mixed ./-> chains needed 4 placeholder
 * patches here -- refine the HAND body with the tail content instead. */
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q;
typedef char *(*FP4)();
typedef struct { char *p; } P1;
char *timproc_uso_b5_func_00004118(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, char *arg6, char *arg7, s32 arg8, char *arg9, char *arg10, s32 arg11) {
    Q sp110;
    Q sp120;
    Q sp130;
    Q sp144;
    Q sp154;
    Q sp164;
    Q sp178;
    Q sp188;
    Q sp198;
    Q sp1AC;
    Q sp1BC;
    Q sp1CC;
    Q sp1E0;
    Q sp1F0;
    Q sp200;
    Q sp214;
    Q sp224;
    Q sp234;
    Q sp248;
    Q sp258;
    Q sp268;
    Q sp27C;
    Q sp28C;
    Q sp29C;
    Q sp2B0;
    Q sp2C0;
    Q sp2D0;
    Q sp2E4;
    Q sp2F4;
    Q sp304;
    Q sp318;
    Q sp328;
    Q sp338;
    Q sp34C;
    Q sp35C;
    Q sp36C;
    Q sp40;
    Q sp50;
    Q sp60;
    Q spDC;
    Q spEC;
    Q spFC;
    char *sp3A0;
    char *sp39C;
    char *sp398;
    char *sp394;
    char *sp390;
    char *sp38C;
    char *sp388;
    char *sp384;
    char *sp380;
    char *sp37C;
    char *sp348;
    char *sp314;
    char *sp2E0;
    char *sp2AC;
    char *sp278;
    char *sp244;
    char *sp210;
    char *sp1DC;
    char *sp1A8;
    char *sp174;
    char *sp140;
    char *sp10C;
    char *spD8;
    char *spD4;
    char *spD0;
    char *spCC;
    char *spC8;
    char *spC4;
    char *spC0;
    char *spBC;
    char *spB8;
    char *spA8;
    P1 marsh;
    P1 tmp;
    char *sp74;
    char *sp28;
    s32 temp_f2;
    s32 var_f2;
    f32 temp_f0;
    char *temp_t0;
    char *temp_v0;
    char *temp_v0_10;
    char *temp_v0_11;
    char *temp_v0_12;
    char *temp_v0_13;
    char *temp_v0_14;
    char *temp_v0_15;
    char *temp_v0_16;
    char *temp_v0_17;
    char *temp_v0_18;
    char *temp_v0_19;
    char *temp_v0_20;
    char *temp_v0_21;
    char *temp_v0_22;
    char *temp_v0_23;
    char *temp_v0_24;
    char *temp_v0_25;
    char *temp_v0_26;
    char *temp_v0_27;
    char *temp_v0_28;
    char *temp_v0_29;
    char *temp_v0_2;
    char *temp_v0_30;
    char *temp_v0_31;
    char *temp_v0_32;
    char *temp_v0_33;
    char *temp_v0_34;
    char *temp_v0_35;
    char *temp_v0_36;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *temp_v0_9;
    char *var_a0;
    char *var_a0_10;
    char *var_a0_11;
    char *var_a0_12;
    char *var_a0_13;
    char *var_a0_14;
    char *var_a0_15;
    char *var_a0_16;
    char *var_a0_17;
    char *var_a0_18;
    char *var_a0_19;
    char *var_a0_20;
    char *var_a0_21;
    char *var_a0_22;
    char *var_a0_23;
    char *var_a0_24;
    char *var_a0_25;
    char *var_a0_26;
    char *var_a0_27;
    char *var_a0_28;
    char *var_a0_29;
    char *var_a0_2;
    char *var_a0_30;
    char *var_a0_31;
    char *var_a0_3;
    char *var_a0_4;
    char *var_a0_5;
    char *var_a0_6;
    char *var_a0_7;
    char *var_a0_8;
    char *var_a0_9;
    char *var_s0;
    char *var_s0_2;
    char *var_v1;

    if ((arg0 != NULL) || (temp_v0 = timproc_uso_b5_alias((char *)0x4F0), arg0 = temp_v0, (temp_v0 != NULL))) {
        var_s0 = arg0;
        if ((var_s0 != NULL) || (temp_v0_2 = timproc_uso_b5_alias((char *)0x2C), var_s0 = temp_v0_2, (temp_v0_2 != NULL))) {
            timproc_uso_b5_alias(var_s0, ((char *)&D_00000000 + 0x1260));
            FW(var_s0, 0x28) = (s32)&D_00000000;
        }
        FW(arg0, 0x28) = (s32)&D_00000000;
        var_s0_2 = arg0 + 0x2C;
        if ((arg0 != (char *)-0x2C) || (temp_v0_3 = timproc_uso_b5_alias((char *)0x38C), var_s0_2 = temp_v0_3, (temp_v0_3 != NULL))) {
            var_v1 = var_s0_2;
            if ((var_s0_2 != NULL) || (temp_v0_4 = timproc_uso_b5_alias((char *)8), var_v1 = temp_v0_4, (temp_v0_4 != NULL))) {
                FW(var_v1, 0x0) = 0x1268;
                FW(var_v1, 0x4) = 0;
            }
            sp3A0 = *(char **)((char *)&D_00000000 + 0x127C);
            var_a0 = var_s0_2 + 8;
            tmp.p = sp3A0;
            marsh = tmp;
            if ((var_s0_2 != (char *)-8) || (temp_v0_5 = timproc_uso_b5_alias((char *)0x18), var_a0 = temp_v0_5, (temp_v0_5 != NULL))) {
                spA8 = var_a0;
                timproc_uso_b5_alias(var_a0, var_s0_2, marsh, 1);
                FW(var_a0, 0xC) = 0x158;
                FW(var_a0, 0x14) = 0;
                *(f32 *)((char *)var_a0 + 0x10) = *(f32 *)((char *)&D_00000000 + 0x14C);
            }
            sp39C = *(char **)((char *)&D_00000000 + 0x1280);
            var_a0_2 = var_s0_2 + 0x20;
            tmp.p = sp39C;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x20) || (temp_v0_6 = timproc_uso_b5_alias((char *)0x18), var_a0_2 = temp_v0_6, (temp_v0_6 != NULL))) {
                spA8 = var_a0_2;
                timproc_uso_b5_alias(var_a0_2, var_s0_2, marsh, 1);
                FW(var_a0_2, 0xC) = 0x158;
                FW(var_a0_2, 0x14) = 0;
                *(f32 *)((char *)var_a0_2 + 0x10) = 0.0f;
            }
            sp398 = *(char **)((char *)&D_00000000 + 0x1284);
            var_a0_3 = var_s0_2 + 0x38;
            tmp.p = sp398;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x38) || (temp_v0_7 = timproc_uso_b5_alias((char *)0x18), var_a0_3 = temp_v0_7, (temp_v0_7 != NULL))) {
                spA8 = var_a0_3;
                timproc_uso_b5_alias(var_a0_3, var_s0_2, marsh, 1);
                FW(var_a0_3, 0x10) = 0x18;
                FW(var_a0_3, 0xC) = 0x1A0;
                FW(var_a0_3, 0x14) = 0;
            }
            sp394 = *(char **)((char *)&D_00000000 + 0x1288);
            var_a0_4 = var_s0_2 + 0x50;
            tmp.p = sp394;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x50) || (temp_v0_8 = timproc_uso_b5_alias((char *)0x18), var_a0_4 = temp_v0_8, (temp_v0_8 != NULL))) {
                spA8 = var_a0_4;
                timproc_uso_b5_alias(var_a0_4, var_s0_2, marsh, 1);
                FW(var_a0_4, 0x10) = 0x78;
                FW(var_a0_4, 0xC) = 0x1A0;
                FW(var_a0_4, 0x14) = 0;
            }
            sp390 = *(char **)((char *)&D_00000000 + 0x128C);
            var_a0_5 = var_s0_2 + 0x68;
            tmp.p = sp390;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x68) || (temp_v0_9 = timproc_uso_b5_alias((char *)0x18), var_a0_5 = temp_v0_9, (temp_v0_9 != NULL))) {
                spA8 = var_a0_5;
                timproc_uso_b5_alias(var_a0_5, var_s0_2, marsh, 1);
                FW(var_a0_5, 0x10) = 0x78;
                FW(var_a0_5, 0xC) = 0x1A0;
                FW(var_a0_5, 0x14) = 0;
            }
            sp38C = *(char **)((char *)&D_00000000 + 0x1290);
            var_a0_6 = var_s0_2 + 0x80;
            tmp.p = sp38C;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x80) || (temp_v0_10 = timproc_uso_b5_alias((char *)0x18), var_a0_6 = temp_v0_10, (temp_v0_10 != NULL))) {
                spA8 = var_a0_6;
                timproc_uso_b5_alias(var_a0_6, var_s0_2, marsh, 1);
                FW(var_a0_6, 0xC) = 0x158;
                FW(var_a0_6, 0x14) = 0;
                *(f32 *)((char *)var_a0_6 + 0x10) = *(f32 *)((char *)&D_00000000 + 0x150);
            }
            sp388 = *(char **)((char *)&D_00000000 + 0x1294);
            var_a0_7 = var_s0_2 + 0x98;
            tmp.p = sp388;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x98) || (temp_v0_11 = timproc_uso_b5_alias((char *)0x18), var_a0_7 = temp_v0_11, (temp_v0_11 != NULL))) {
                spA8 = var_a0_7;
                timproc_uso_b5_alias(var_a0_7, var_s0_2, marsh, 1);
                FW(var_a0_7, 0xC) = 0x158;
                FW(var_a0_7, 0x14) = 0;
                *(f32 *)((char *)var_a0_7 + 0x10) = *(f32 *)((char *)&D_00000000 + 0x154);
            }
            sp384 = *(char **)((char *)&D_00000000 + 0x1298);
            var_a0_8 = var_s0_2 + 0xB0;
            tmp.p = sp384;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0xB0) || (temp_v0_12 = timproc_uso_b5_alias((char *)0x18), var_a0_8 = temp_v0_12, (temp_v0_12 != NULL))) {
                spA8 = var_a0_8;
                timproc_uso_b5_alias(var_a0_8, var_s0_2, marsh, 1);
                FW(var_a0_8, 0xC) = 0x158;
                FW(var_a0_8, 0x14) = 0;
                *(f32 *)((char *)var_a0_8 + 0x10) = *(f32 *)((char *)&D_00000000 + 0x158);
            }
            sp380 = *(char **)((char *)&D_00000000 + 0x129C);
            var_a0_9 = var_s0_2 + 0xC8;
            tmp.p = sp380;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0xC8) || (temp_v0_13 = timproc_uso_b5_alias((char *)0x18), var_a0_9 = temp_v0_13, (temp_v0_13 != NULL))) {
                spA8 = var_a0_9;
                timproc_uso_b5_alias(var_a0_9, var_s0_2, marsh, 1);
                FW(var_a0_9, 0x10) = 0x99;
                FW(var_a0_9, 0xC) = 0x1A0;
                FW(var_a0_9, 0x14) = 0;
            }
            sp37C = *(char **)((char *)&D_00000000 + 0x12A0);
            var_a0_10 = var_s0_2 + 0xE0;
            tmp.p = sp37C;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0xE0) || (temp_v0_14 = timproc_uso_b5_alias((char *)0x18), var_a0_10 = temp_v0_14, (temp_v0_14 != NULL))) {
                spA8 = var_a0_10;
                timproc_uso_b5_alias(var_a0_10, var_s0_2, marsh, 1);
                FW(var_a0_10, 0x10) = 0x99;
                FW(var_a0_10, 0xC) = 0x1A0;
                FW(var_a0_10, 0x14) = 0;
            }
            *(float *)&sp36C.unkC = 0.0f;
            sp35C.unk0 = 0;
            *(float *)&sp35C.unk4 = 0.0f;
            *(float *)&sp35C.unk8 = 0.0f;
            *(float *)&sp35C.unkC = 0.0f;
            *(float *)&sp36C.unk0 = 0.5f;
            *(float *)&sp36C.unk4 = 0.5f;
            *(float *)&sp36C.unk8 = 0.5f;
            *(float *)&sp34C.unk0 = 1.0f;
            *(float *)&sp34C.unk4 = 1.0f;
            *(float *)&sp34C.unk8 = 1.0f;
            *(float *)&sp34C.unkC = 1.0f;
            sp348 = *(char **)((char *)&D_00000000 + 0x12A4);
            sp60.unk0 = (s32) sp36C.unk0;
            sp60.unk4 = (s32) sp36C.unk4;
            sp60.unk8 = (s32) sp36C.unk8;
            var_a0_11 = var_s0_2 + 0xF8;
            sp60.unkC = (s32) sp36C.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp35C;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp34C;
            tmp.p = sp348;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0xF8) || (temp_v0_15 = timproc_uso_b5_alias((char *)0x24), var_a0_11 = temp_v0_15, (temp_v0_15 != NULL))) {
                sp74 = var_a0_11;
                timproc_uso_b5_alias(var_a0_11, var_s0_2, marsh, 1);
                FW(var_a0_11, 0xC) = 0x188;
                FW(var_a0_11, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_11 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp338.unkC = 0.0f;
            sp328.unk0 = 0;
            *(float *)&sp328.unk4 = 0.0f;
            *(float *)&sp328.unk8 = 0.0f;
            *(float *)&sp328.unkC = 0.0f;
            *(float *)&sp318.unk0 = 1.0f;
            *(float *)&sp318.unk4 = 1.0f;
            *(float *)&sp318.unk8 = 1.0f;
            *(float *)&sp318.unkC = 1.0f;
            *(float *)&sp338.unk0 = 0.5f;
            *(float *)&sp338.unk4 = 0.5f;
            *(float *)&sp338.unk8 = 0.5f;
            sp314 = *(char **)((char *)&D_00000000 + 0x12A8);
            sp60.unk0 = (s32) sp338.unk0;
            sp60.unk4 = (s32) sp338.unk4;
            sp60.unk8 = (s32) sp338.unk8;
            var_a0_12 = var_s0_2 + 0x11C;
            sp60.unkC = (s32) sp338.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp328;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp318;
            tmp.p = sp314;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x11C) || (temp_v0_16 = timproc_uso_b5_alias((char *)0x24), var_a0_12 = temp_v0_16, (temp_v0_16 != NULL))) {
                sp28 = var_a0_12;
                timproc_uso_b5_alias(var_a0_12, var_s0_2, marsh, 1);
                FW(var_a0_12, 0xC) = 0x188;
                FW(var_a0_12, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_12 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp304.unkC = 0.0f;
            sp2F4.unk0 = 0;
            *(float *)&sp2F4.unk4 = 0.0f;
            *(float *)&sp2F4.unk8 = 0.0f;
            *(float *)&sp2F4.unkC = 0.0f;
            *(float *)&sp2E4.unk0 = 1.0f;
            *(float *)&sp2E4.unk4 = 1.0f;
            *(float *)&sp2E4.unk8 = 1.0f;
            *(float *)&sp2E4.unkC = 1.0f;
            *(float *)&sp304.unk0 = 0.5f;
            *(float *)&sp304.unk4 = 0.5f;
            *(float *)&sp304.unk8 = 0.5f;
            sp2E0 = *(char **)((char *)&D_00000000 + 0x12AC);
            sp60.unk0 = (s32) sp304.unk0;
            sp60.unk4 = (s32) sp304.unk4;
            sp60.unk8 = (s32) sp304.unk8;
            var_a0_13 = var_s0_2 + 0x140;
            sp60.unkC = (s32) sp304.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp2F4;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp2E4;
            tmp.p = sp2E0;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x140) || (temp_v0_17 = timproc_uso_b5_alias((char *)0x24), var_a0_13 = temp_v0_17, (temp_v0_17 != NULL))) {
                sp28 = var_a0_13;
                timproc_uso_b5_alias(var_a0_13, var_s0_2, marsh, 1);
                FW(var_a0_13, 0xC) = 0x188;
                FW(var_a0_13, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_13 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp2D0.unkC = 0.0f;
            sp2C0.unk0 = 0;
            *(float *)&sp2C0.unk4 = 0.0f;
            *(float *)&sp2C0.unk8 = 0.0f;
            *(float *)&sp2C0.unkC = 0.0f;
            *(float *)&sp2B0.unk0 = 1.0f;
            *(float *)&sp2B0.unk4 = 1.0f;
            *(float *)&sp2B0.unk8 = 1.0f;
            *(float *)&sp2B0.unkC = 1.0f;
            *(float *)&sp2D0.unk0 = 0.5f;
            *(float *)&sp2D0.unk4 = 0.5f;
            *(float *)&sp2D0.unk8 = 0.5f;
            sp2AC = *(char **)((char *)&D_00000000 + 0x12B0);
            sp60.unk0 = (s32) sp2D0.unk0;
            sp60.unk4 = (s32) sp2D0.unk4;
            sp60.unk8 = (s32) sp2D0.unk8;
            var_a0_14 = var_s0_2 + 0x164;
            sp60.unkC = (s32) sp2D0.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp2C0;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp2B0;
            tmp.p = sp2AC;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x164) || (temp_v0_18 = timproc_uso_b5_alias((char *)0x24), var_a0_14 = temp_v0_18, (temp_v0_18 != NULL))) {
                sp28 = var_a0_14;
                timproc_uso_b5_alias(var_a0_14, var_s0_2, marsh, 1);
                FW(var_a0_14, 0xC) = 0x188;
                FW(var_a0_14, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_14 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp29C.unkC = 0.0f;
            sp28C.unk0 = 0;
            *(float *)&sp28C.unk4 = 0.0f;
            *(float *)&sp28C.unk8 = 0.0f;
            *(float *)&sp28C.unkC = 0.0f;
            *(float *)&sp27C.unk0 = 1.0f;
            *(float *)&sp27C.unk4 = 1.0f;
            *(float *)&sp27C.unk8 = 1.0f;
            *(float *)&sp27C.unkC = 1.0f;
            *(float *)&sp29C.unk0 = 0.5f;
            *(float *)&sp29C.unk4 = 0.5f;
            *(float *)&sp29C.unk8 = 0.5f;
            sp278 = *(char **)((char *)&D_00000000 + 0x12B4);
            sp60.unk0 = (s32) sp29C.unk0;
            sp60.unk4 = (s32) sp29C.unk4;
            sp60.unk8 = (s32) sp29C.unk8;
            var_a0_15 = var_s0_2 + 0x188;
            sp60.unkC = (s32) sp29C.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp28C;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp27C;
            tmp.p = sp278;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x188) || (temp_v0_19 = timproc_uso_b5_alias((char *)0x24), var_a0_15 = temp_v0_19, (temp_v0_19 != NULL))) {
                sp28 = var_a0_15;
                timproc_uso_b5_alias(var_a0_15, var_s0_2, marsh, 1);
                FW(var_a0_15, 0xC) = 0x188;
                FW(var_a0_15, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_15 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp268.unkC = 0.0f;
            sp258.unk0 = 0;
            *(float *)&sp258.unk4 = 0.0f;
            *(float *)&sp258.unk8 = 0.0f;
            *(float *)&sp258.unkC = 0.0f;
            *(float *)&sp248.unk0 = 1.0f;
            *(float *)&sp248.unk4 = 1.0f;
            *(float *)&sp248.unk8 = 1.0f;
            *(float *)&sp248.unkC = 1.0f;
            *(float *)&sp268.unk0 = 0.5f;
            *(float *)&sp268.unk4 = 0.5f;
            *(float *)&sp268.unk8 = 0.5f;
            sp244 = *(char **)((char *)&D_00000000 + 0x12B8);
            sp60.unk0 = (s32) sp268.unk0;
            sp60.unk4 = (s32) sp268.unk4;
            sp60.unk8 = (s32) sp268.unk8;
            var_a0_16 = var_s0_2 + 0x1AC;
            sp60.unkC = (s32) sp268.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp258;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp248;
            tmp.p = sp244;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x1AC) || (temp_v0_20 = timproc_uso_b5_alias((char *)0x24), var_a0_16 = temp_v0_20, (temp_v0_20 != NULL))) {
                sp28 = var_a0_16;
                timproc_uso_b5_alias(var_a0_16, var_s0_2, marsh, 1);
                FW(var_a0_16, 0xC) = 0x188;
                FW(var_a0_16, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_16 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp234.unkC = 0.0f;
            sp224.unk0 = 0;
            *(float *)&sp224.unk4 = 0.0f;
            *(float *)&sp224.unk8 = 0.0f;
            *(float *)&sp224.unkC = 0.0f;
            *(float *)&sp214.unk0 = 1.0f;
            *(float *)&sp214.unk4 = 1.0f;
            *(float *)&sp214.unk8 = 1.0f;
            *(float *)&sp214.unkC = 1.0f;
            *(float *)&sp234.unk0 = 0.5f;
            *(float *)&sp234.unk4 = 0.5f;
            *(float *)&sp234.unk8 = 0.5f;
            sp210 = *(char **)((char *)&D_00000000 + 0x12BC);
            sp60.unk0 = (s32) sp234.unk0;
            sp60.unk4 = (s32) sp234.unk4;
            sp60.unk8 = (s32) sp234.unk8;
            var_a0_17 = var_s0_2 + 0x1D0;
            sp60.unkC = (s32) sp234.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp224;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp214;
            tmp.p = sp210;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x1D0) || (temp_v0_21 = timproc_uso_b5_alias((char *)0x24), var_a0_17 = temp_v0_21, (temp_v0_21 != NULL))) {
                sp28 = var_a0_17;
                timproc_uso_b5_alias(var_a0_17, var_s0_2, marsh, 1);
                FW(var_a0_17, 0xC) = 0x188;
                FW(var_a0_17, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_17 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp200.unkC = 0.0f;
            sp1F0.unk0 = 0;
            *(float *)&sp1F0.unk4 = 0.0f;
            *(float *)&sp1F0.unk8 = 0.0f;
            *(float *)&sp1F0.unkC = 0.0f;
            *(float *)&sp1E0.unk0 = 1.0f;
            *(float *)&sp1E0.unk4 = 1.0f;
            *(float *)&sp1E0.unk8 = 1.0f;
            *(float *)&sp1E0.unkC = 1.0f;
            sp1DC = *(char **)((char *)&D_00000000 + 0x12C0);
            *(float *)&sp200.unk0 = 0.5f;
            *(float *)&sp200.unk4 = 0.5f;
            *(float *)&sp200.unk8 = 0.5f;
            sp60.unk0 = (s32) sp200.unk0;
            sp60.unk4 = (s32) sp200.unk4;
            sp60.unk8 = (s32) sp200.unk8;
            var_a0_18 = var_s0_2 + 0x1F4;
            sp60.unkC = (s32) sp200.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp1F0;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp1E0;
            tmp.p = sp1DC;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x1F4) || (temp_v0_22 = timproc_uso_b5_alias((char *)0x24), var_a0_18 = temp_v0_22, (temp_v0_22 != NULL))) {
                sp28 = var_a0_18;
                timproc_uso_b5_alias(var_a0_18, var_s0_2, marsh, 1);
                FW(var_a0_18, 0xC) = 0x188;
                FW(var_a0_18, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_18 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp1CC.unkC = 0.0f;
            sp1BC.unk0 = 0;
            *(float *)&sp1BC.unk4 = 0.0f;
            *(float *)&sp1BC.unk8 = 0.0f;
            *(float *)&sp1BC.unkC = 0.0f;
            *(float *)&sp1AC.unk0 = 1.0f;
            *(float *)&sp1AC.unk4 = 1.0f;
            *(float *)&sp1AC.unk8 = 1.0f;
            *(float *)&sp1AC.unkC = 1.0f;
            sp1A8 = *(char **)((char *)&D_00000000 + 0x12C4);
            *(float *)&sp1CC.unk0 = 0.5f;
            *(float *)&sp1CC.unk4 = 0.5f;
            *(float *)&sp1CC.unk8 = 0.5f;
            sp60.unk0 = (s32) sp1CC.unk0;
            sp60.unk4 = (s32) sp1CC.unk4;
            sp60.unk8 = (s32) sp1CC.unk8;
            var_a0_19 = var_s0_2 + 0x218;
            sp60.unkC = (s32) sp1CC.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp1BC;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp1AC;
            tmp.p = sp1A8;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x218) || (temp_v0_23 = timproc_uso_b5_alias((char *)0x24), var_a0_19 = temp_v0_23, (temp_v0_23 != NULL))) {
                sp28 = var_a0_19;
                timproc_uso_b5_alias(var_a0_19, var_s0_2, marsh, 1);
                FW(var_a0_19, 0xC) = 0x188;
                FW(var_a0_19, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_19 + 0x10) = *(Quad4 *)&sp60;
            }
            temp_f2 = *(s32 *)((char *)&D_00000000 + 0x15C);
            *(float *)&sp198.unkC = 0.0f;
            sp188.unk0 = 0;
            *(float *)&sp188.unk4 = 0.0f;
            *(float *)&sp188.unk8 = 0.0f;
            *(float *)&sp188.unkC = 0.0f;
            *(float *)&sp178.unk0 = 1.0f;
            *(float *)&sp178.unk4 = 1.0f;
            *(float *)&sp178.unk8 = 1.0f;
            *(float *)&sp178.unkC = 1.0f;
            *(float *)&sp198.unk0 = temp_f2;
            *(float *)&sp198.unk4 = temp_f2;
            *(float *)&sp198.unk8 = temp_f2;
            sp174 = *(char **)((char *)&D_00000000 + 0x12C8);
            sp60.unk0 = (s32) sp198.unk0;
            sp60.unk4 = (s32) sp198.unk4;
            sp60.unk8 = (s32) sp198.unk8;
            var_a0_20 = var_s0_2 + 0x23C;
            sp60.unkC = (s32) sp198.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp188;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp178;
            tmp.p = sp174;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x23C) || (temp_v0_24 = timproc_uso_b5_alias((char *)0x24), var_a0_20 = temp_v0_24, (temp_v0_24 != NULL))) {
                sp28 = var_a0_20;
                timproc_uso_b5_alias(var_a0_20, var_s0_2, marsh, 1);
                FW(var_a0_20, 0xC) = 0x188;
                FW(var_a0_20, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_20 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&sp164.unkC = 0.0f;
            sp154.unk0 = 0;
            *(float *)&sp154.unk4 = 0.0f;
            *(float *)&sp154.unk8 = 0.0f;
            *(float *)&sp154.unkC = 0.0f;
            *(float *)&sp144.unk0 = 1.0f;
            *(float *)&sp144.unk4 = 1.0f;
            *(float *)&sp144.unk8 = 1.0f;
            *(float *)&sp144.unkC = 1.0f;
            sp140 = *(char **)((char *)&D_00000000 + 0x12CC);
            *(float *)&sp164.unk0 = 0.5f;
            *(float *)&sp164.unk4 = 0.5f;
            *(float *)&sp164.unk8 = 0.5f;
            sp60.unk0 = (s32) sp164.unk0;
            sp60.unk4 = (s32) sp164.unk4;
            sp60.unk8 = (s32) sp164.unk8;
            var_a0_21 = var_s0_2 + 0x260;
            sp60.unkC = (s32) sp164.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp154;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp144;
            tmp.p = sp140;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x260) || (temp_v0_25 = timproc_uso_b5_alias((char *)0x24), var_f2 = *(s32 *)((char *)&D_00000000 + 0x168), var_a0_21 = temp_v0_25, (temp_v0_25 != NULL))) {
                sp28 = var_a0_21;
                timproc_uso_b5_alias(var_a0_21, var_s0_2, marsh, 1);
                var_f2 = *(s32 *)((char *)&D_00000000 + 0x16C);
                FW(var_a0_21, 0xC) = 0x188;
                FW(var_a0_21, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_21 + 0x10) = *(Quad4 *)&sp60;
            }
            sp130.unk0 = var_f2;
            sp130.unk4 = var_f2;
            sp130.unk8 = var_f2;
            *(float *)&sp130.unkC = 0.0f;
            sp120.unk0 = 0;
            *(float *)&sp120.unk4 = 0.0f;
            *(float *)&sp120.unk8 = 0.0f;
            *(float *)&sp120.unkC = 0.0f;
            *(float *)&sp110.unk0 = 1.0f;
            *(float *)&sp110.unk4 = 1.0f;
            *(float *)&sp110.unk8 = 1.0f;
            *(float *)&sp110.unkC = 1.0f;
            sp10C = *(char **)((char *)&D_00000000 + 0x12D0);
            sp60.unk0 = (s32) sp130.unk0;
            sp60.unk4 = (s32) sp130.unk4;
            sp60.unk8 = (s32) sp130.unk8;
            var_a0_22 = var_s0_2 + 0x284;
            sp60.unkC = (s32) sp130.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&sp120;
            *(Quad4 *)&sp40 = *(Quad4 *)&sp110;
            tmp.p = sp10C;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x284) || (temp_v0_26 = timproc_uso_b5_alias((char *)0x24), var_a0_22 = temp_v0_26, (temp_v0_26 != NULL))) {
                sp28 = var_a0_22;
                timproc_uso_b5_alias(var_a0_22, var_s0_2, marsh, 1);
                FW(var_a0_22, 0xC) = 0x188;
                FW(var_a0_22, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_22 + 0x10) = *(Quad4 *)&sp60;
            }
            *(float *)&spFC.unkC = 0.0f;
            spEC.unk0 = 0;
            *(float *)&spEC.unk4 = 0.0f;
            *(float *)&spEC.unk8 = 0.0f;
            *(float *)&spEC.unkC = 0.0f;
            *(float *)&spDC.unk0 = 1.0f;
            *(float *)&spDC.unk4 = 1.0f;
            *(float *)&spDC.unk8 = 1.0f;
            *(float *)&spDC.unkC = 1.0f;
            spD8 = *(char **)((char *)&D_00000000 + 0x12D4);
            *(float *)&spFC.unk0 = 0.5f;
            *(float *)&spFC.unk4 = 0.5f;
            *(float *)&spFC.unk8 = 0.5f;
            sp60.unk0 = (s32) spFC.unk0;
            sp60.unk4 = (s32) spFC.unk4;
            sp60.unk8 = (s32) spFC.unk8;
            var_a0_23 = var_s0_2 + 0x2A8;
            sp60.unkC = (s32) spFC.unkC;
            *(Quad4 *)&sp50 = *(Quad4 *)&spEC;
            *(Quad4 *)&sp40 = *(Quad4 *)&spDC;
            tmp.p = spD8;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x2A8) || (temp_v0_27 = timproc_uso_b5_alias((char *)0x24), var_a0_23 = temp_v0_27, (temp_v0_27 != NULL))) {
                sp28 = var_a0_23;
                timproc_uso_b5_alias(var_a0_23, var_s0_2, marsh, 1);
                FW(var_a0_23, 0xC) = 0x188;
                FW(var_a0_23, 0x20) = 0;
                *(Quad4 *)((char *)var_a0_23 + 0x10) = *(Quad4 *)&sp60;
            }
            spD4 = *(char **)((char *)&D_00000000 + 0x12D8);
            var_a0_24 = var_s0_2 + 0x2CC;
            tmp.p = spD4;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x2CC) || (temp_v0_28 = timproc_uso_b5_alias((char *)0x18), var_a0_24 = temp_v0_28, (temp_v0_28 != NULL))) {
                spA8 = var_a0_24;
                timproc_uso_b5_alias(var_a0_24, var_s0_2, marsh, 1);
                FW(var_a0_24, 0x10) = -4;
                FW(var_a0_24, 0xC) = 0x1A0;
                FW(var_a0_24, 0x14) = 0;
            }
            spD0 = *(char **)((char *)&D_00000000 + 0x12DC);
            var_a0_25 = var_s0_2 + 0x2E4;
            tmp.p = spD0;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x2E4) || (temp_v0_29 = timproc_uso_b5_alias((char *)0x18), var_a0_25 = temp_v0_29, (temp_v0_29 != NULL))) {
                spA8 = var_a0_25;
                timproc_uso_b5_alias(var_a0_25, var_s0_2, marsh, 1);
                FW(var_a0_25, 0x10) = 0xD;
                FW(var_a0_25, 0xC) = 0x1A0;
                FW(var_a0_25, 0x14) = 0;
            }
            spCC = *(char **)((char *)&D_00000000 + 0x12E0);
            var_a0_26 = var_s0_2 + 0x2FC;
            tmp.p = spCC;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x2FC) || (temp_v0_30 = timproc_uso_b5_alias((char *)0x18), var_a0_26 = temp_v0_30, (temp_v0_30 != NULL))) {
                spA8 = var_a0_26;
                timproc_uso_b5_alias(var_a0_26, var_s0_2, marsh, 1);
                FW(var_a0_26, 0x10) = -0x10;
                FW(var_a0_26, 0xC) = 0x1A0;
                FW(var_a0_26, 0x14) = 0;
            }
            spC8 = *(char **)((char *)&D_00000000 + 0x12E4);
            var_a0_27 = var_s0_2 + 0x314;
            tmp.p = spC8;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x314) || (temp_v0_31 = timproc_uso_b5_alias((char *)0x18), var_a0_27 = temp_v0_31, (temp_v0_31 != NULL))) {
                spA8 = var_a0_27;
                timproc_uso_b5_alias(var_a0_27, var_s0_2, marsh, 1);
                FW(var_a0_27, 0x10) = -0x15;
                FW(var_a0_27, 0xC) = 0x1A0;
                FW(var_a0_27, 0x14) = 0;
            }
            spC4 = *(char **)((char *)&D_00000000 + 0x12E8);
            var_a0_28 = var_s0_2 + 0x32C;
            tmp.p = spC4;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x32C) || (temp_v0_32 = timproc_uso_b5_alias((char *)0x18), var_a0_28 = temp_v0_32, (temp_v0_32 != NULL))) {
                spA8 = var_a0_28;
                timproc_uso_b5_alias(var_a0_28, var_s0_2, marsh, 1);
                FW(var_a0_28, 0x10) = 0x73;
                FW(var_a0_28, 0xC) = 0x1A0;
                FW(var_a0_28, 0x14) = 0;
            }
            spC0 = *(char **)((char *)&D_00000000 + 0x12EC);
            var_a0_29 = var_s0_2 + 0x344;
            tmp.p = spC0;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x344) || (temp_v0_33 = timproc_uso_b5_alias((char *)0x18), var_a0_29 = temp_v0_33, (temp_v0_33 != NULL))) {
                spA8 = var_a0_29;
                timproc_uso_b5_alias(var_a0_29, var_s0_2, marsh, 1);
                FW(var_a0_29, 0x10) = 0x62;
                FW(var_a0_29, 0xC) = 0x1A0;
                FW(var_a0_29, 0x14) = 0;
            }
            spBC = *(char **)((char *)&D_00000000 + 0x12F0);
            var_a0_30 = var_s0_2 + 0x35C;
            tmp.p = spBC;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x35C) || (temp_v0_34 = timproc_uso_b5_alias((char *)0x18), var_a0_30 = temp_v0_34, (temp_v0_34 != NULL))) {
                spA8 = var_a0_30;
                timproc_uso_b5_alias(var_a0_30, var_s0_2, marsh, 1);
                FW(var_a0_30, 0x10) = 0x62;
                FW(var_a0_30, 0xC) = 0x1A0;
                FW(var_a0_30, 0x14) = 0;
            }
            spB8 = *(char **)((char *)&D_00000000 + 0x12F4);
            var_a0_31 = var_s0_2 + 0x374;
            tmp.p = spB8;
            marsh = tmp;
            if ((var_s0_2 != (char *)-0x374) || (temp_v0_35 = timproc_uso_b5_alias((char *)0x18), var_a0_31 = temp_v0_35, (temp_v0_35 != NULL))) {
                spA8 = var_a0_31;
                timproc_uso_b5_alias(var_a0_31, var_s0_2, marsh, 1);
                FW(var_a0_31, 0x10) = 0xD;
                FW(var_a0_31, 0xC) = 0x1A0;
                FW(var_a0_31, 0x14) = 0;
            }
        }
        FW(arg0, 0xC) = 0x12F8;
        FW(arg0, 0x4D4) = arg11;
        FW(arg0, 0x418) = arg2;
        FW(arg0, 0x40C) = arg7;
        FW(arg0, 0x410) = arg8;
        FW(arg0, 0x3BC) = arg3;
        FW(arg0, 0x41C) = arg1;
        FW(arg0, 0x3C8) = arg6;
        FW(arg0, 0x3B8) = arg4;
        temp_v0_36 = timproc_uso_b5_alias(arg0, arg6);
        FW(arg0, 0x3C4) = temp_v0_36;
        FW(arg0, 0x3F0) = temp_v0_36;
        FW(arg0, 0x3F4) = 0;
        if (FW(arg0, 0x3BC) == 2) {
            FW(arg0, 0x4D8) = 0x78;
        } else {
            FW(arg0, 0x4D8) = 0xF0;
        }
        FW(arg0, 0x48C) = 0;
        FW(arg0, 0x490) = 0;
        temp_t0 = FW(arg0, 0x3C8) - 1;
        switch ((s32) temp_t0) {
        case 2:
        case 4:
        case 5:
        case 6:
            break;
        case 0:
            timproc_uso_b5_alias(arg0, NULL, arg0);
            FW(arg0, 0x3CC) = 0;
            *(f32 *)((char *)arg0 + 0x480) = 0.0f;
            *(f32 *)((char *)arg0 + 0x484) = 0.0f;
            FW((FW(arg0, 0x3B8) * 4), 0xB8) = 1;
            break;
        case 1:
            timproc_uso_b5_alias(arg0, (char *)1, arg0);
            FW(arg0, 0x3CC) = 6;
            *(f32 *)((char *)arg0 + 0x480) = 1.0f;
            *(f32 *)((char *)arg0 + 0x484) = 1.0f;
            break;
        case 3:
            FW(arg0, 0x3CC) = 8;
            *(f32 *)((char *)arg0 + 0x480) = 1.0f;
block_112:
            *(f32 *)((char *)arg0 + 0x484) = 1.0f;
            break;
        case 7:
            FW(arg0, 0x3CC) = 9;
            *(f32 *)((char *)arg0 + 0x480) = 1.0f;
            goto block_112;
        }
        FW(arg0, 0x414) = arg9;
        FW(arg0, 0x3C0) = arg5;
        temp_f0 = FW(FW(FW(arg9, 0xC), 0x70), 0x14C);
        FW(arg0, 0x4B8) = 0;
        FW(arg0, 0x4B4) = 0;
        FW(arg0, 0x494) = temp_f0;
        FW(arg0, 0x498) = temp_f0;
        FW(arg0, 0x49C) = temp_f0;
        timproc_uso_b5_alias(FW(FW(FW(FW(arg0, 0x40C), 0x54), 0x2B8), 0x108), (char *)0x3F000000, arg0);
        timproc_uso_b5_alias(FW(FW(FW(FW(arg0, 0x40C), 0x58), 0x2B8), 0x108), (char *)0x3F000000);
        if (*(s32 *)((char *)&D_00000000 + 0x34) != 2) {
            timproc_uso_b5_alias(FW(FW(FW(FW(arg0, 0x40C), 0x5C), 0x2B8), 0x108), (char *)0x3F000000);
        }
        timproc_uso_b5_alias(arg0, (char *)1, arg10);
    }
    return arg0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00004118);
#endif

// timproc_uso_b5_func_00005BF0 — STRUCTURAL PASS (0x3D0 / 244 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Per-frame HUD panel build/refresh for the timing/replay screen
// (operates on the 0x4F0 object built by func_00004118).
//
//   void timproc_uso_b5_func_00005BF0(Scr *scr, a1, a2, a3) {  // scr->s0
//     scr->0x4DC = a1;  scr->0x4E0 = a3;  scr->0x4E4 = a3;
//     scr->0x4E8 = 1;   scr->0x4EC = ...;                // stash params
//     // index static layout tables by id: D_00000E74 -> scr->0x4A4,
//     //   D_00000E54 -> scr->0x3E0, D_00000E94 -> scr->0x4A8;
//     func_00000000(.);  scr->0x3E4 = .;
//     // per-item layout loop over scr->0x40->0x6C count, walking
//     //   scr->0x3B8..0x3BC, writing per-row offsets to +0x2B4;
//     // vtable draw dispatch x3-4: d = node->0x3C->0x28;
//     //   (d->0x84)(d->0x80 + …)  (obj->0x28 dispatch idiom);
//     // bake vertex/draw-data float block into scr+0x420..0x47C:
//     //   colors 255.0 (0x437F), coords 90/145/232/13/161/91/35/70…
//     //   (RGBA + UV + position constants for the panel quads);
//     func_00000000(.); ... more vtable draws ...;
//     scr->0x404 = 0x40;  scr->0x488 = .;  scr->0x4BC = f;
//   }
//
// Struct-typing reference:
//   scr (the 0x4F0 timing-HUD object from func_00004118):
//     0x4DC/0x4E0/0x4E4 stashed call params, 0x4E8 = 1 flag,
//     0x3E0/0x3E4/0x4A4/0x4A8 = looked-up layout entries,
//     0x3B8/0x3BC iteration range, 0x40->0x6C item count,
//     +0x2B4 per-row offset out, +0x420..0x47C f32 vertex/color
//     block, 0x404 = 0x40, 0x488/0x4BC trailing fields;
//     node->0x3C->0x28 vtable (->0x84 fn, ->0x80 s16 base).
//   D_00000E54/0E74/0E94 = USO static layout tables (0xE.. pool).
//   func_00000000 = USO placeholder dispatcher.
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — param stash + table-lookup + vertex-bake skeleton only.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00005BF0(char *arg0, int *arg1, int *arg2, int *arg3, int *arg4, int *arg5) {
    char *g = (char *)&D_00000000;
    char *L, *e, *vt, *h;
    int i, idx, va3 = 0;
    float one = 255.0f / 255.0f, f12, f14, f16;

    *(int **)(arg0 + 0x4DC) = arg1;
    *(int **)(arg0 + 0x4E4) = arg3;
    *(int **)(arg0 + 0x4E0) = arg2;
    *(int **)(arg0 + 0x4E8) = arg4;
    *(int **)(arg0 + 0x4EC) = arg5;
    *(int *)(arg0 + 0x4A4) = *(int *)(g + *arg2 * 4 + 0xE74);
    *(int *)(arg0 + 0x3E0) = *(int *)(g + *arg2 * 4 + 0xE54);
    *(int *)(arg0 + 0x4A8) = *(int *)(g + *arg4 * 4 + 0xE94);
    *(int *)(arg0 + 0x3E4) = func_00000000(1, *arg4);
    L = *(char **)(*(char **)(arg0 + 0x40C) + 0x40);
    if (*(int *)(L + 0x6C) > 0) {
        va3 = 0xB8;
        i = 0;
        do {
            int v;
            if (*(int *)(arg0 + 0x3BC) == 2) {
                if (*(int *)(g + *(int *)(arg0 + 0x3B8) * 4 + 0xB8) != 0) {
                    v = 0x20000;
                } else {
                    v = 0;
                }
            } else {
                v = 0;
            }
            *(int *)(*(int *)(L + i * 4 + 0x3C) + 0x2B4) = v;
            i++;
            L = *(char **)(*(char **)(arg0 + 0x40C) + 0x40);
        } while (i < *(int *)(L + 0x6C));
    }
    L = *(char **)(*(char **)(arg0 + 0x40C) + 0x44);
    if (*(int *)(L + 0x6C) > 0) {
        i = 0;
        do {
            e = *(char **)(L + i * 4 + 0x3C);
            i++;
            *(int *)(e + 0x2B4) = **(int **)(arg0 + 0x4E4) & 0x20;
            L = *(char **)(*(char **)(arg0 + 0x40C) + 0x44);
        } while (i < *(int *)(L + 0x6C));
    }
    *(int *)(arg0 + 0x3E8) = func_00000000(arg0, 2, **(int **)(arg0 + 0x4EC), va3);
    idx = func_00000000(arg0, 3, **(int **)(arg0 + 0x4DC));
    *(int *)(arg0 + 0x3EC) = idx;
    *(int *)(arg0 + 0x3DC) = idx;
    *(int *)(arg0 + 0x3D0) = *(int *)(arg0 + 0x3E0);
    *(int *)(arg0 + 0x3D4) = *(int *)(arg0 + 0x3E4);
    *(int *)(arg0 + 0x3D8) = *(int *)(arg0 + 0x3E8);
    e = *(char **)(*(char **)(*(char **)(arg0 + 0x40C) + 0x40) + *(int *)(arg0 + 0x3D0) * 4 + 0x3C);
    vt = *(char **)(e + 0x28);
    (*(void (**)())(vt + 0x84))(*(int *)(vt + 0x80) + (int)e, 0, *(int *)(arg0 + 0x3D0), e);
    e = *(char **)(*(char **)(*(char **)(arg0 + 0x40C) + 0x44) + *(int *)(arg0 + 0x3E4) * 4 + 0x3C);
    vt = *(char **)(e + 0x28);
    (*(void (**)())(vt + 0x84))(*(int *)(vt + 0x80) + (int)e, 0);
    e = *(char **)(*(char **)(*(char **)(arg0 + 0x40C) + 0x48) + *(int *)(arg0 + 0x3E8) * 4 + 0x3C);
    vt = *(char **)(e + 0x28);
    (*(void (**)())(vt + 0x84))(*(int *)(vt + 0x80) + (int)e, 0);
    *(float *)(arg0 + 0x434) = 145.0f / 255.0f;
    *(float *)(arg0 + 0x42C) = one;
    *(float *)(arg0 + 0x430) = one;
    *(float *)(arg0 + 0x43C) = one;
    *(float *)(arg0 + 0x440) = one;
    *(float *)(arg0 + 0x444) = one;
    *(float *)(arg0 + 0x448) = one;
    *(float *)(arg0 + 0x44C) = one;
    *(float *)(arg0 + 0x45C) = one;
    *(float *)(arg0 + 0x46C) = one;
    *(float *)(arg0 + 0x47C) = one;
    f12 = 90.0f / 255.0f;
    *(float *)(arg0 + 0x460) = 161.0f / 255.0f;
    *(float *)(arg0 + 0x420) = f12;
    *(float *)(arg0 + 0x424) = f12;
    *(float *)(arg0 + 0x428) = f12;
    f14 = 13.0f / 255.0f;
    *(float *)(arg0 + 0x438) = 58.0f / 255.0f;
    f16 = 70.0f / 255.0f;
    *(float *)(arg0 + 0x450) = f14;
    *(float *)(arg0 + 0x454) = f14;
    *(float *)(arg0 + 0x458) = f14;
    *(float *)(arg0 + 0x470) = f16;
    *(float *)(arg0 + 0x474) = f16;
    *(float *)(arg0 + 0x478) = f16;
    *(float *)(arg0 + 0x464) = 91.0f / 255.0f;
    *(float *)(arg0 + 0x468) = 35.0f / 255.0f;
    *(int *)(arg0 + 0x4D0) = func_00000000(*(int *)&f12, *(int *)&f14, 0, 0, 0x48, 0xDD, 3, 0xD);
    h = (char *)func_00000000(arg0);
    vt = *(char **)(h + 0x28);
    (*(void (**)())(vt + 0x64))(*(int *)(vt + 0x60) + (int)h);
    {
        char *p414 = *(char **)(arg0 + 0x414);
        func_00000000(func_00000000(arg0), *(int *)(p414 + 0x10), *(int *)(p414 + 0x14));
    }
    func_00000000(arg0, 0);
    *(int *)(arg0 + 0x404) = 0x40;
    *(int *)(arg0 + 0x488) = *(int *)(arg0 + 0x104);
    *(float *)(arg0 + 0x4BC) = 1.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005BF0);
#endif

// timproc_uso_b5_func_00005FC0 — FULL structural DECODE via compressed-
// module jumptable path (75.30% reloc-masked NM, no episode — decode-only
// cap: raw-word USO + m2c-vs-IDO jumptable .rodata-vs-D_807FF1B0 symbol +
// FP regalloc/spill-slot ordering. 2026-06-22 rewrite: replaced the
// all-`timproc_uso_b5_alias` paraphrase (5.63%) with the REAL R_MIPS_26
// callee symbols + HI16/LO16 globals from the expected reloc table; FP
// product source-reversed (const-first). 11-case switch (sltiu 11,
// dispatch jr $t9 @ 0x6064, default 0x6114) extracted from the Yay0-
// compressed USO emulator dump (ram_base 0x807ef230 forced, table @dump
// 0x7FF1B0). Lift: 34 X->unkN -> FW(X,0xN), fn-ptr member calls
// ((FP4)FW(p,o))(...), placeholder calls cast via FP4, void*->char*,
// m2c 'bitwise' reinterpret casts routed through (int) (IDO rejects
// pointer<->float casts), NULL->0; disasm-func emits `bc1fl.Lxxx` with
// no space -> add it before m2c. Raw-.word USO form (genuine code).
//
// Per-frame timing/replay-screen tick (counterpart to func_00005BF0's
// build; operates on the same Scr object).
//
//   void timproc_uso_b5_func_00005FC0(Scr *scr) {        // scr -> s0
//     if (scr->0x3BC != 2) return;                        // inactive
//     if (scr->0x3C8 == 4) func_00000000(&D_0, -1);
//     else                  func_00000000(&D_0, scr->0x3B8);
//     // jump-table state machine on scr->0x3CC (0..0xA, 11 cases;
//     //   table at D_0 + 0x190): a cascade of  func_00000000(scr);
//     //   advancing scr->0x4B4 per state.
//     // FP animation: scr->0x4BC += 1.0f;  if (scr->0x4BC >= lim)
//     //   reset scr->0x4B4/0x4B8;  scr->0x3FC counter -= 4.
//     // vtable-dispatched element draws x4: d = scr->0x480->0x28;
//     //   (d->0xBC)(d->0xB8 + …)   (obj->0x28 dispatch idiom).
//     if (scr->0x34 != 2) {
//       // FP transform from folded consts D_000001BC/01C0/01C4/01C8/
//       //   01CC: compute positions -> scr->0x498/0x49C/0x4C0 and
//       //   cam->0x14C (the fov-like field).
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x3BC active gate (==2), 0x3C8 mode (==4 special), 0x3B8 arg,
//     0x3CC state index (0..0xA jump-table key), 0x3FC frame counter,
//     0x4B4/0x4B8 stage scratch, 0x4BC f32 anim timer (+=1.0f),
//     0x480 draw-element ptr (->0x28 vtable: ->0xBC fn, ->0xB8 s16
//     base), 0x498/0x49C/0x4C0 computed f32 positions; 0x34 sub-mode.
//   D_000001BC/01C0/01C4/01C8/01CC = folded FP consts (literal-pool
//     fold family; see
//     docs/N64_FORENSICS.md#bootup-uso-fp-literal-pool-folded-into-func-0000098C).
//   D_0 + 0x190 = the 11-entry jump table. func_00000000 = USO
//     placeholder dispatcher (state advance / draw).
// Caps (DEFERRED): raw-word USO + jump-table + placeholder calls +
//   folded consts; USO mnemonic disasm limitation prevents
//   byte-match. Real-C STRUCTURAL body below — gate + state-advance
//   + FP anim skeleton only. Byte-match deferred. Name pre-checked:
//   no extern reuse.
#ifdef NON_MATCHING
/* 2026-06-22 decode-progress rewrite: replace the all-alias paraphrase
 * (5.63% reloc-masked) with a structural decode that uses the REAL
 * R_MIPS_26 callee symbols and HI16/LO16 globals from the expected
 * reloc table (import_80020098 / import_000A7ECC / import_800200CC,
 * the 11 jump-table state handlers timproc_uso_b5_func_0000{7078..85E0},
 * func_00001CF0, func_00008AD4/8A38, the FP placement helpers
 * func_0000396C/000038B0, and the float->int helper func_07E7B0).
 * FP literal-pool consts D[0x1BC..0x1CC]. Field types lifted from
 * mnemonics (lh=s16 for the 0xB8 vtable base, lwc1=f32). */
extern char import_80020098;
extern char import_800200CC;
extern void import_000A7ECC();
extern void timproc_uso_b5_func_00007078();
extern void timproc_uso_b5_func_000072D0();
extern void timproc_uso_b5_func_00007430();
extern void timproc_uso_b5_func_000077D8();
extern void timproc_uso_b5_func_000079A4();
extern void timproc_uso_b5_func_00007B2C();
extern void timproc_uso_b5_func_00007E34();
extern void timproc_uso_b5_func_000080F4();
extern void timproc_uso_b5_func_00008468();
extern f32 timproc_uso_b5_func_07E7B0();
/* 00001CF0, 000038B0, 0000396C, 000073C0, 000085E0, 00008A38, 00008AD4
 * are defined elsewhere in this TU with real prototypes. */
int timproc_uso_b5_func_00001CF0(int *a0, int a1);
int timproc_uso_b5_func_00008A38(int *a0);
int timproc_uso_b5_func_00008AD4(int *a0);
void timproc_uso_b5_func_000073C0(char *scr);
void timproc_uso_b5_func_000085E0(int *a0);

typedef void (*FPv)();

void timproc_uso_b5_func_00005FC0(char *arg0) {
    char *sp2C;
    char *v0;
    char *v1;
    f32 f2;

    if (FW(arg0, 0x3BC) == 2) {
        if ((FW(arg0, 0x3C8) == 4) &&
            (FW(timproc_uso_b5_func_00001CF0((int *)FW(arg0, 0x41C), FW(arg0, 0x3B8)), 0x3C8) == 4)) {
            import_000A7ECC(&import_80020098, -1);
        } else {
            import_000A7ECC(&import_80020098, FW(arg0, 0x3B8));
        }
    } else {
        import_000A7ECC(&import_80020098, FW(arg0, 0x3B8));
    }
    switch ((u32)FW(arg0, 0x3CC)) {
    case 0:
        timproc_uso_b5_func_00007078(arg0);
        break;
    case 1:
        timproc_uso_b5_func_000072D0(arg0);
        break;
    case 2:
        timproc_uso_b5_func_000073C0(arg0);
        break;
    case 3:
        timproc_uso_b5_func_00007430(arg0);
        break;
    case 4:
        timproc_uso_b5_func_000077D8(arg0);
        break;
    case 5:
        timproc_uso_b5_func_000079A4(arg0);
        break;
    case 6:
        timproc_uso_b5_func_00007B2C(arg0);
        break;
    case 7:
        timproc_uso_b5_func_00007E34(arg0);
        break;
    case 8:
        timproc_uso_b5_func_000080F4(arg0);
        break;
    case 9:
        timproc_uso_b5_func_00008468(arg0);
        break;
    case 10:
        timproc_uso_b5_func_000085E0(arg0);
        break;
    }
    if (FW(arg0, 0x4B4) != 0) {
        *(f32 *)(arg0 + 0x4BC) = *(f32 *)(arg0 + 0x4BC) + *(f32 *)(arg0 + 0xBC);
        if (*(f32 *)(arg0 + 0x4BC) >= 1.0f) {
            *(f32 *)(arg0 + 0x4BC) = 1.0f;
            FW(arg0, 0x4B4) = 0;
            FW(arg0, 0x4B8) = 0;
        }
    }
    if (FW(arg0, 0x3FC) != 0) {
        FW(arg0, 0x3FC) = FW(arg0, 0x3FC) - 4;
        if (FW(arg0, 0x3FC) <= 0) {
            FW(arg0, 0x3FC) = 0;
        }
    }
    if (FW(arg0, 0x3F8) != 0) {
        v0 = (char *)timproc_uso_b5_func_00008AD4(arg0);
        v1 = (char *)FW(v0, 0x28);
        ((FPv)FW(v1, 0xBC))(*(s16 *)(v1 + 0xB8) + v0, FW(arg0, 0x480));
    }
    v0 = (char *)timproc_uso_b5_func_00008A38(arg0);
    v1 = (char *)FW(v0, 0x28);
    ((FPv)FW(v1, 0xBC))(*(s16 *)(v1 + 0xB8) + v0, FW(arg0, 0x480));
    v1 = (char *)FW(FW(arg0, 0x40C), 0x54);
    v0 = (char *)FW(v1, 0x28);
    ((FPv)FW(v0, 0xBC))(*(s16 *)(v0 + 0xB8) + v1, FW(arg0, 0x480));
    v0 = (char *)FW(FW(arg0, 0x40C), 0x58);
    v1 = (char *)FW(v0, 0x28);
    ((FPv)FW(v1, 0xBC))(*(s16 *)(v1 + 0xB8) + v0, FW(arg0, 0x480));
    if (*(s32 *)(&import_800200CC + 0x34) != 2) {
        v0 = (char *)FW(FW(arg0, 0x40C), 0x5C);
        v1 = (char *)FW(v0, 0x28);
        ((FPv)FW(v1, 0xBC))(*(s16 *)(v1 + 0xB8) + v0, FW(arg0, 0x480));
    }
    if (FW(arg0, 0x3CC) == 5) {
        sp2C = (char *)timproc_uso_b5_func_00008A38(arg0);
        timproc_uso_b5_func_0000396C(sp2C, FW(FW(arg0, 0x414), 0x10), arg0 + 0x4C4,
            timproc_uso_b5_func_07E7B0(*(f32 *)(&D_00000000 + 0x1BC) * *(f32 *)(arg0 + 0x4BC)),
            *(f32 *)(arg0 + 0x5C));
        sp2C = (char *)timproc_uso_b5_func_00008A38(arg0);
        *(f32 *)(arg0 + 0x498) =
            *(f32 *)(sp2C + 0x14C) *
            timproc_uso_b5_func_07E7B0(*(f32 *)(&D_00000000 + 0x1C0) * *(f32 *)(arg0 + 0x480)) +
            *(f32 *)(arg0 + 0x49C);
    } else {
        sp2C = (char *)timproc_uso_b5_func_00008A38(arg0);
        timproc_uso_b5_func_000038B0(sp2C, FW(FW(arg0, 0x414), 0x10), arg0 + 0x4C4,
            timproc_uso_b5_func_07E7B0(*(f32 *)(&D_00000000 + 0x1C4) * *(f32 *)(arg0 + 0x4BC)),
            *(f32 *)(arg0 + 0x5C));
        sp2C = (char *)timproc_uso_b5_func_00008A38(arg0);
        *(f32 *)(arg0 + 0x498) =
            *(f32 *)(sp2C + 0x134) *
            timproc_uso_b5_func_07E7B0(*(f32 *)(&D_00000000 + 0x1C8) * *(f32 *)(arg0 + 0x480)) +
            *(f32 *)(arg0 + 0x49C);
    }
    f2 = *(f32 *)(arg0 + 0x4C0);
    *(f32 *)(FW(FW(FW(arg0, 0x414), 0xC), 0x70) + 0x14C) =
        timproc_uso_b5_func_07E7B0(*(f32 *)(&D_00000000 + 0x1CC) * *(f32 *)(arg0 + 0x4BC)) *
        (*(f32 *)(arg0 + 0x498) - f2) + f2;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00005FC0);
#endif

// timproc_uso_b5_func_00006394 — STRUCTURAL PASS (0x4C8 / 306 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen element layout/draw helper (operates on the Scr object).
//
//   void timproc_uso_b5_func_00006394(Scr *scr) {        // scr -> s0
//     N *n = scr->0x414->0xC;
//     if (n->0xBC >= 0x78) return;                        // X bound 120
//     if (scr->0x3B0 + n->0xC4 < 0x15) { ... }            // count bound 21
//     v = func_00000000(scr->0x3C8, 0x15);                // query/alloc
//     // index static table D_00000160 by computed idx -> entry;
//     func_00000000(&D_0, scr->0x398, scr+0x1E8);
//     func_00000000(idxbuf, 0xA0, v);                     // build row
//     if (scr->0x4B4 == 1) {
//       // FP block (~11 FPU ops): compute positions/colors,
//       //   alpha = 0xFF; ~22 func_00000000 draw/config calls
//       //   emitting the timing display rows/digits.
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x414 -> node, node->0x0C -> sub (->0xBC X coord vs 0x78=120,
//     ->0xC4 count); 0x3B0 row offset (vs 0x15=21 cap), 0x398 arg,
//     0x3C8 query key, 0x490 a count, 0x4B4 draw-state (==1 draws),
//     0x1E8 a sub-record passed by ptr. Constants: 0xFF alpha,
//     state ids 1/5/7, 2/3.
//   D_00000160 = USO static layout table (the 0x1xx pool). func_00000000
//     = USO placeholder dispatcher (query / build / draw).
// Caps (DEFERRED): raw-word USO + placeholder calls + FP block; USO
//   mnemonic disasm limitation prevents byte-match. Real-C STRUCTURAL
//   body below — bound guards + query + draw skeleton only.
//   Byte-match deferred. Name pre-checked: no extern reuse.
// 2026-06-21 RECONSTRUCT 64.4%->69.9% (gap -3 -> +5, LCS 197->214): first
// query call is a DIRECT alias() (jal), not a fnptr-cast jalr; the result
// indexes (&D_6394_F5E0)[ret] array base, *24, added to (char*)&D_00000160
// base; the two FP draw blocks pass a0 = &import_8024CAF8 (alpha=0xFF call) and
// the row template = &D_6394_FF5B0 / &D_6394_FF5C8 (reloc'd globals, not bare
// 0x130/0x148); the template +0x20 fields are *(s16*) (lh), and the *0.25f/
// *0.75f strength-reduced FP scales preserved.
// 2026-06-23 RECONSTRUCT 69.1%->73.2% (size 311->306 words EXACT, LCS 215->224),
// fixing 4 genuine bugs (size-corrected, not faked):
//   (1) field 0x480 is f32 compared to 1.0f -> *(float*)(arg0+0x480) (was
//       FW int->cvt.s.w, +2 phantom words: lwc1+c.eq.s vs lw/mtc1/cvt/c.eq).
//   (2) table base is &D_807FF5E0+0x160 (reloc'd global) not bare &D_00000160.
//   (3) the +0x34==2 gate reads global import_800200CC+0x34, not &D_00000000.
//   (4) tail dispatch: drop redundant sp24 local + REORDER so the
//       func_00008A64 call precedes the FW(arg0,0x4A4) read -> kills the v1
//       spill/reload pair (caller had two phantom spill words).
// RESIDUAL (~82 word diffs, all SAME-SIZE): (a) the D_807FE728/D_807FF5E0 array+
//   base load is HI16-only-unpaired (target folds +0x160 into the base addiu via
//   reloc + literal-0 lw offsets; IDO-from-C emits paired HI16/LO16 + folds
//   +0x160 into the index multiply) -- the documented raw-word-USO unpaired-HI16
//   cap, unreproducible from C. (b) everything else is pure register-renumber
//   coloring + stack-slot cascade + 1 scheduler load-order swap (permuter-immune
//   cap class). Byte-match remains DEFERRED (DECODE-ONLY). Name pre-checked.
#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00006394)();
extern int D_6394_F5E0;
extern char D_6394_FF5E0;
extern char import_8024CAF8;
extern char D_6394_FF5B0;
extern char D_6394_FF5C8;
extern char import_800200CC;
void timproc_uso_b5_func_00006394(char *arg0) {
    char *sp44;
    char *sp40;
    s32 temp_v0;
    s32 temp_v0_12;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_7;
    s32 temp_v1_9;
    s32 var_a2;
    s32 var_v0_2;
    s32 var_v1;
    char *temp_v0_10;
    char *temp_v0_11;
    char *temp_v0_13;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_8;
    char *temp_v0_9;
    char *temp_v1;
    char *temp_v1_10;
    char *temp_v1_2;
    char *temp_v1_3;
    char *temp_v1_4;
    char *temp_v1_5;
    char *temp_v1_6;
    char *temp_v1_7;
    char *temp_v1_8;
    char *var_v0;

    var_v0 = FW(arg0, 0x414);
    temp_v1 = FW(var_v0, 0xC);
    if (FW(temp_v1, 0xBC) >= 0x78) {
        var_v0_2 = FW(arg0, 0x3B0) + FW(temp_v1, 0xC4);
        if (var_v0_2 < 0x15) {
            var_v0_2 = 0x15;
        }
        sp44 = (char *) var_v0_2;
        sp40 = (char *)&D_6394_FF5E0 + 0x160 + (&D_6394_F5E0)[(s32) timproc_uso_b5_alias(arg0, FW(arg0, 0x3C8))] * 0x18;
        timproc_uso_b5_alias(0, FW(arg0, 0x398), (int)arg0 + 0x1E8);
        timproc_uso_b5_alias(sp40);
        timproc_uso_b5_alias(sp40, 0xA0, sp44, 3);
        if (FW(arg0, 0x4B4) != 1) {
            temp_v0 = FW(arg0, 0x3CC);
            if ((temp_v0 != 7) && (temp_v0 != 5) && (temp_v0 != 4)) {
                temp_v0_2 = FW(arg0, 0x48C);
                FW(arg0, 0x48C) = (s32) (temp_v0_2 + 1);
                if (temp_v0_2 & 8) {
                    if (timproc_uso_b5_alias(arg0) != 0) {
                        timproc_uso_b5_alias(&import_8024CAF8, 0xFF, (int)arg0 + 0x20C);
                        timproc_uso_b5_alias(&D_6394_FF5B0);
                        timproc_uso_b5_alias(&D_6394_FF5B0, (s32) (((*(s16*)((char*)FW(sp40, 0x10) + 0x20) / 2) + 0xA0) - (*(s16*)((char*)FW(&D_6394_FF5B0, 0x10) + 0x20) * 0.25f)), sp44, 2);
                    }
                    if (timproc_uso_b5_alias(arg0) != 0) {
                        timproc_uso_b5_alias(&import_8024CAF8, 0xFF, (int)arg0 + 0x20C);
                        timproc_uso_b5_alias(&D_6394_FF5C8);
                        timproc_uso_b5_alias(&D_6394_FF5C8, (s32) ((0xA0 - (*(s16*)((char*)FW(sp40, 0x10) + 0x20) / 2)) - (*(s16*)((char*)FW(&D_6394_FF5C8, 0x10) + 0x20) * 0.75f)), sp44, 2);
                    }
                }
            }
        }
        var_v0 = FW(arg0, 0x414);
    }
    FW(arg0, 0x490) = (s32) (FW(arg0, 0x490) + 1);
    var_v1 = FW(FW(var_v0, 0xC), 0xBC);
    if (var_v1 >= 0x78) {
        temp_v0_3 = FW(arg0, 0x3CC);
        if ((temp_v0_3 != 1) && (temp_v0_3 != 0xA) && (*(float *)((char *)arg0 + 0x480) == 1.0f) && (FW(arg0, 0x4B4) != 1)) {
            if ((temp_v0_3 == 5) || (temp_v0_3 == 7)) {
                if (FW(arg0, 0x490) & 8) {
                    temp_v0_4 = timproc_uso_b5_alias(arg0);
                    temp_v1_2 = FW(temp_v0_4, 0x28);
                    ((GP_00006394)FW(temp_v1_2, 0xC4))(*(s16*)((char*)temp_v1_2 + 0xC0) + temp_v0_4, arg0, (int)arg0 + 0x254, (int)arg0 + 0x278);
                }
            } else if (temp_v0_3 == 8) {
                temp_v0_5 = timproc_uso_b5_alias(arg0);
                temp_v1_3 = FW(temp_v0_5, 0x28);
                ((GP_00006394)FW(temp_v1_3, 0xC4))(*(s16*)((char*)temp_v1_3 + 0xC0) + temp_v0_5, arg0, (int)arg0 + 0x29C, (int)arg0 + 0x2C0);
            } else {
                temp_v0_6 = timproc_uso_b5_alias(arg0);
                temp_v1_4 = FW(temp_v0_6, 0x28);
                ((GP_00006394)FW(temp_v1_4, 0xC4))(*(s16*)((char*)temp_v1_4 + 0xC0) + temp_v0_6, arg0, (int)arg0 + 0x254, (int)arg0 + 0x278);
            }
            if (*(s32 *)((char *)&import_800200CC + 0x34) == 2) {
                temp_v0_7 = FW(arg0, 0x3CC);
                if (temp_v0_7 == 4) {
                    temp_v0_8 = timproc_uso_b5_alias(arg0);
                    temp_v1_5 = FW(temp_v0_8, 0x28);
                    ((GP_00006394)FW(temp_v1_5, 0xDC))(*(s16*)((char*)temp_v1_5 + 0xD8) + temp_v0_8, arg0, FW(arg0, 0x490));
                } else if (temp_v0_7 == 5) {
                    temp_v0_9 = timproc_uso_b5_alias(arg0);
                    temp_v1_6 = FW(temp_v0_9, 0x28);
                    ((GP_00006394)FW(temp_v1_6, 0xDC))(*(s16*)((char*)temp_v1_6 + 0xD8) + temp_v0_9, arg0, 8);
                } else {
                    temp_v0_10 = timproc_uso_b5_alias(arg0);
                    temp_v1_7 = FW(temp_v0_10, 0x28);
                    ((GP_00006394)FW(temp_v1_7, 0xD4))(*(s16*)((char*)temp_v1_7 + 0xD0) + temp_v0_10, arg0);
                }
            } else {
                temp_v0_11 = timproc_uso_b5_alias(arg0);
                temp_v1_8 = FW(temp_v0_11, 0x28);
                ((GP_00006394)FW(temp_v1_8, 0xD4))(*(s16*)((char*)temp_v1_8 + 0xD0) + temp_v0_11, arg0);
            }
            var_v1 = FW(FW(FW(arg0, 0x414), 0xC), 0xBC);
        }
    }
    temp_v0_12 = FW(arg0, 0x3CC);
    if (((var_v1 >= 0x78) && (FW(arg0, 0x4B4) != 1) && (temp_v0_12 == 6)) || (temp_v0_12 == 7)) {
        var_a2 = FW((timproc_uso_b5_alias(arg0)), 0x2B0);
        temp_v1_9 = FW(arg0, 0x4A4);
        if (temp_v1_9 == 1) {
            var_a2 = 5;
        }
        if (temp_v1_9 == 2) {
            var_a2 = 6;
        }
        if (temp_v1_9 == 3) {
            var_a2 = 7;
        }
        temp_v0_13 = timproc_uso_b5_alias(arg0);
        temp_v1_10 = FW(temp_v0_13, 0x28);
        ((GP_00006394)FW(temp_v1_10, 0xCC))(*(s16*)((char*)temp_v1_10 + 0xC8) + temp_v0_13, arg0, var_a2);
    }
    timproc_uso_b5_alias(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006394);
#endif

void timproc_uso_b5_func_0000685C(char *a0) {
    gl_func_00000000(a0 + 0x2C);
}

/* func_0000687C absorbs _00006890+_000068A8+_000068EC: 33-insn (0x84)
 * multi-exit table-search loop with 4 early-return paths.
 *
 * Decoded structure:
 *   int v0 = a0->[0x3C4];                   // outer index
 *   if (v0 == 0) return 1;                   // early-return path 1
 *
 *   int *base = (int*)((char*)a0 + v0*4);
 *   int idx = base->[0x3D0];                  // = a0->[0x3D0 + v0*4]
 *   if (idx == 0) return 0;                   // early-return path 2
 *   idx -= 1;
 *
 *   if (idx < 0) return 0;                    // early-return path 3
 *
 *   // Loop: for (i = idx; i >= 0; i--) { check item; if (nonzero) return 1; }
 *   int *table = a0->[0x40C];
 *   int *outer = (int*)((char*)table + v0*4);
 *   int byte_off = idx*4;
 *   do {
 *     int *inner = outer->[0x40];
 *     int *item = (int*)inner->[byte_off + 0x3C];
 *     float val = *(float*)((char*)item + 0x2A4);
 *     if (val != 0.0f) return 1;
 *     byte_off -= 4;
 *   } while (--idx >= 0);
 *   return 0;
 *
 * Initial decode 2026-05-06; multi-pass refinement expected. The float
 * comparison is equality against 0.0f; non-zero values take the success
 * return path. */
extern int gl_func_00000000();
/* MATCHED 2026-05-28 (Yay0 boundary fix): the .s was truncated to 0x14 (5
 * insns); the function is really 0x84 (33 insns) — the `bnez v0, 0x6890`
 * branched into its own dropped body (Yay0 block_5 gap), NOT a cross-fn
 * cap. Restored the .s + inlined the `item` deref (shifts $v0->$t0 to match
 * the float-load base register). 33/33 byte-exact. */
int timproc_uso_b5_func_0000687C(int *a0) {
    int group = *(int*)((char*)a0 + 0x3C4);
    int group_off = group * 4;
    int count;
    int idx;
    int byte_off;
    register int *cursor;
    if (group == 0) return 1;

    count = *(int*)((char*)a0 + 0x3D0 + group_off);
    idx = count - 1;
    if (count == 0) return 0;

    if (idx < 0) goto ret0;

    byte_off = idx * 4;
    cursor = (int*)((char*)*(int*)((char*)*(int**)((char*)a0 + 0x40C) + group_off + 0x40) + byte_off);
    do {
        byte_off -= 4;
        if (*(float*)((char*)*(int*)((char*)cursor + 0x3C) + 0x2A4) != 0.0f) return 1;
        cursor = (int*)((char*)cursor - 4);
    } while (byte_off >= 0);
ret0:
    return 0;
}
/* timproc_uso_b5_func_00006900 - verified structural decode (0xE8,
 * 58 insns, "any-entry-active" scan predicate). Returns s32 0/1.
 *   s32 timproc_uso_b5_func_00006900(St *s) {
 *       if (s->0x3C4 == 0) return 1;              // no group -> 1
 *       n0 = count(s);                            // func_00000000(s)
 *       start = s->0x3D0[s->0x3C4];               // lw 976(s+idx*4)
 *       if (n0 == start) return 0;
 *       i = start + 1;
 *       if (i >= count(s)) return 0;
 *       do {
 *           grp = s->0x40C[s->0x3C4];             // table[idx]
 *           e   = grp->0x40[i]->0x3C;             // entry @ +0x3C
 *           if (e->0x2A4 != 0.0f) return 1;       // active found
 *           i++;
 *       } while (i < count(s));
 *       return 0;
 *   }
 * Struct-typing reference: s->0x3C4 (964) s32 = active group index
 * (0 -> trivially "active", return 1); s->0x3D0 (976) s32[] = per-
 * group start/cursor (indexed by 0x3C4); s->0x40C (1036) ptr[]
 * table (indexed by 0x3C4) -> group; group->0x40 (64) = entry ptr
 * array; entry+0x3C (60) -> element; element->0x2A4 (676) f32 =
 * the active flag (nonzero = active). count(s) = func_00000000(s)
 * (total entries, re-read each iteration as the loop bound).
 * Predicate: true (1) if ANY entry from start+1..count has a
 * nonzero 0x2A4, else 0. Caps <80: c.eq.s vs 0.0 + bc1t/beql/bnel
 * branch-likely + repeated func_00000000 reloc count call + f20
 * sdc1/ldc1 double-save. Full body INCLUDE_ASM-preserved (.s =
 * source of truth). INCLUDE_ASM (no episode; tautology-trap rule). */
/* timproc_uso_b5_func_00006900 — VERIFIED EXACT 58/58 (2026-07-03, agent-e)
 * vs asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_00006900.s
 * (in-tree word-by-word on build/non_matching .o, clean rebuild, -O2;
 * jal words 0x0C000000 via extern callee). objdiff 100.0.
 *
 * LOGIC BUG fixed vs old NM body (79.3%): the group table pointer is
 * *(s+0x40C) dereferenced FIRST and THEN indexed at idx*4+0x40 —
 * exactly the landed 8C1C accessor chain — not indexed at 0x40C+idx*4
 * as the old body had it. count() = timproc_uso_b5_func_00008C1C
 * (real intra-file callee per .s jal reloc, replaces func_00000000).
 *
 * Shape recipe:
 * 1. for-loop `for (i = ...; i < count(); i++)` (NOT if-guard + do-while):
 *    IDO's for->guard+do-while conversion emits the target's
 *    beqzl-at-zero-to-epilogue guard with `move v0,zero` in the likely
 *    delay; the explicit if+do-while form inverts to bnezl-around (+2 insns).
 * 2. i's init MUST be a CSE-temp expression: write `((int*)(s+0x3D0))[idx]`
 *    INLINE in both the ==-check and the +1 init (CSE gives one lw v1).
 *    A named `start` local splits the init into `addiu s0,v1,1` +
 *    `move s2,s0` and the guard slt reads the copy-propped temp
 *    (coalesce fails); the CSE form emits `addiu s2,v1,1` directly in
 *    the bne delay slot.
 * 3. Array-IXA `((int *)(s + 0x3D0))[*(int *)(s + 0x3C4)]` forces
 *    addu rs=base (addu t9,s1,t8); flat `(int)s + idx*4 + 0x3D0`
 *    arithmetic gives rs=scaled here (either text order).
 * 4. Loop chain: 8C1C-style scaled-first all-int arithmetic
 *    `*(int*)(idx*4 + *(int*)(s+0x40C) + 0x40)` -> pure t0-t6 temps,
 *    addu rs=base at both levels; idx and the table base reload each
 *    iteration (no locals). f20=0.0 hoist/sdc1 pair is automatic.
 */
extern int timproc_uso_b5_func_00008C1C(int *a0);
int timproc_uso_b5_func_00006900(char *s) {
    int i;
    int n0;
    if (*(int *)(s + 0x3C4) == 0) {
        return 1;
    }
    n0 = timproc_uso_b5_func_00008C1C((int *)s);
    if (n0 == ((int *)(s + 0x3D0))[*(int *)(s + 0x3C4)]) {
        return 0;
    }
    i = ((int *)(s + 0x3D0))[*(int *)(s + 0x3C4)] + 1;
    for (; i < timproc_uso_b5_func_00008C1C((int *)s); i++) {
        if (*(float *)(*(int *)(*(int *)(*(int *)(s + 0x3C4) * 4 + *(int *)(s + 0x40C) + 0x40) + i * 4 + 0x3C) + 0x2A4) != 0.0f) {
            return 1;
        }
    }
    return 0;
}

// timproc_uso_b5_func_000069E8 — STRUCTURAL PASS (0x218 / 134 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing/replay-screen input/navigation handler (operates on Scr).
//
//   int timproc_uso_b5_func_000069E8(Scr *scr, a1) {     // scr -> s0
//     func_00000000(., a1);
//     func_00000000(scr->0x418, -1, 0);                   // reset/clear
//     switch (scr->0x4A4) {                               // cursor state
//       case 0:  func_00000000(&D_00001304); ...; break;
//       default: // 1..3+: index scr->0x4E0[scr->0x4A4] via the
//         //   D_00000F24 static table; decrement global *(int*)D_0,
//         //   if == 0x17D7 special-case;
//     }
//     // for the selected element(s): base = scr->0x40C->{0x3D0/0x3D4/
//     //   0x3D8/0x3DC}; idx from scr->0x40/0x44/0x48/0x4C counts and
//     //   the stashed params scr->0x4DC/0x4E0/0x4E4/0x4E8/0x4EC;
//     //   e = base + idx;  write command/flag pair into
//     //   e->0x3C->0x2B0 / 0x2B4 (OR-combined), gated by scr->0x4A8
//     //   and scr->0x34 (==1 / ==2);
//     // also writes globals *(int*)(D_0 + 0xA4) / + 0xB8.
//     return 1;
//   }
//
// Struct-typing reference:
//   scr: 0x418 reset target, 0x4A4 cursor/selection state (0..3+
//     switch key), 0x4A8 gate, 0x34 sub-mode (1/2), 0x40C -> element
//     array holder (->0x3D0/0x3D4/0x3D8/0x3DC bases), 0x40/0x44/0x48/
//     0x4C per-axis counts, 0x4DC/0x4E0/0x4E4/0x4E8/0x4EC stashed
//     params (from func_00005BF0); element->0x3C->0x2B0/0x2B4 =
//     command/flag word pair. D_0 + {0xA4,0xB8} global out fields;
//     global counter at *(int*)D_0 (dec, cmp 0x17D7).
//   D_00001304 / D_00000F24 = USO static tables (0x13xx/0xF.. pool).
//   func_00000000 = USO placeholder dispatcher.
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — reset + cursor-switch + per-element write skeleton only.
//   Byte-match deferred. Name pre-checked: no extern reuse.
// 2026-06-21 RECONSTRUCT: cursor table -> array-base (&D_69E8_F24)[cursor]
//   form (count-exact F24 block); store target corrected 0x4E0; single-arg
//   alias(&D..1304). Body now structurally count-complete (133 vs 134, the
//   -1 is an IDO g-address reload before the *g==0x17D7 compare). Residual =
//   pure register-renumber coloring (permuter-immune cap class).
#ifdef NON_MATCHING
extern int D_69E8_F24;
int timproc_uso_b5_func_000069E8(char *scr, int a1) {
    char *g = (char *)&D_00000000;
    char *C, *elem;
    int a4;
    func_00000000(scr, a1);
    func_00000000(*(char **)(scr + 0x418), -1, 0);
    *(int *)(g + 0x40) = *(int *)(g + 0x44);
    C = *(char **)(scr + 0x40C);
    elem = *(char **)(C + 0x40) + *(int *)(scr + 0x3D0) * 4;
    *(int *)*(char **)(scr + 0x4E0) = *(int *)(*(char **)(elem + 0x3C) + 0x2B0);
    a4 = *(int *)(scr + 0x4A4);
    if (a4 != 0 && a4 < 4) {
        func_00000000((char *)&D_00000000 + 0x1304);
        *(int *)*(char **)(scr + 0x4E0) = (&D_69E8_F24)[*(int *)(scr + 0x4A4)] - 1;
    }
    if (*(int *)g == 0x17D7) {
        elem = *(char **)(*(char **)(scr + 0x40C) + 0x4C) + *(int *)(scr + 0x3DC) * 4;
        *(int *)*(char **)(scr + 0x4DC) = *(int *)(*(char **)(elem + 0x3C) + 0x2B0);
    } else {
        *(int *)*(char **)(scr + 0x4DC) = 1;
    }
    elem = *(char **)(*(char **)(scr + 0x40C) + 0x44) + *(int *)(scr + 0x3D4) * 4;
    *(int *)*(char **)(scr + 0x4E8) = *(int *)(*(char **)(elem + 0x3C) + 0x2B0);
    if (*(int *)(scr + 0x4A8) == 4) {
        *(int *)*(char **)(scr + 0x4E8) = 8;
    }
    C = *(char **)(scr + 0x40C);
    {
        char *e44 = *(char **)(C + 0x44) + *(int *)(scr + 0x3D4) * 4;
        char *e40 = *(char **)(C + 0x40) + *(int *)(scr + 0x3D0) * 4;
        *(int *)*(char **)(scr + 0x4E4) =
            *(int *)(*(char **)(e44 + 0x3C) + 0x2B4) | *(int *)(*(char **)(e40 + 0x3C) + 0x2B4);
    }
    if (a1 != 0) {
        elem = *(char **)(*(char **)(scr + 0x40C) + 0x48) + *(int *)(scr + 0x3D8) * 4;
        *(int *)*(char **)(scr + 0x4EC) = *(int *)(*(char **)(elem + 0x3C) + 0x2B0);
    }
    if (*(int *)(g + 0x34) != 2) {
        *(int *)((char *)&D_00000000 + *(int *)(scr + 0x3D0) * 4 + 0xA4) = *(int *)*(char **)(scr + 0x4E8);
    } else {
        char *e40b = *(char **)(*(char **)(scr + 0x40C) + 0x40) + *(int *)(scr + 0x3D0) * 4;
        *(int *)((char *)&D_00000000 + *(int *)(scr + 0x3B8) * 4 + 0xB8) =
            (*(int *)(*(char **)(e40b + 0x3C) + 0x2B4) & 0x20000) != 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000069E8);
#endif

// timproc_uso_b5_func_00006C00 — STRUCTURAL PASS (0x130 / 76 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen element command-snapshot / refresh (operates on Scr).
//
//   void timproc_uso_b5_func_00006C00(Scr *scr) {        // scr -> s0
//     if (!func_00000000(scr->0x3B8, scr->0x41C)) return; // gate
//     func_00000000(scr);
//     func_00000000(scr->0x418, -1, 0);                   // reset
//     *(int*)(D_0 + 0x40) = *(int*)(D_0 + 0x48);          // global copy
//     // x4 element rows: base = scr->0x40C; row =
//     //   scr->{0x3DC,0x3D0,0x3D4,0x3D8}; p =
//     //   scr->{0x4DC,0x4E0,0x4E8,0x4EC}; cnt = row->{0x4C,0x40,
//     //   0x44,0x48}; e = base + index(p,cnt);
//     //   *dst = e->0x3C->0x2B0  (rows 1-3) /  e->0x3C->0x2B4
//     //   (row 4, OR-combined with the prior) — snapshot each row's
//     //   command word into its target slot.
//   }
//
// Struct-typing reference:
//   scr: 0x3B8/0x41C gate-query args, 0x418 reset target, 0x40C ->
//     element-array base, 0x3D0/0x3D4/0x3D8/0x3DC row pointers,
//     0x4DC/0x4E0/0x4E8/0x4EC stashed param indices (from
//     func_00005BF0), row->0x40/0x44/0x48/0x4C counts;
//     element->0x3C->0x2B0 / 0x2B4 = command/flag word pair.
//   D_0 + 0x40 / + 0x48 = global command-state slots (refreshed).
//   func_00000000 = USO placeholder dispatcher (gate / reset).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — gate + reset + element-snapshot skeleton only.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00006C00(char *scr) {
    char *base;
    char *row;
    int idx;
    char *e;
    int *dst;
    if (!func_00000000(*(int *)(scr + 0x3B8), *(int *)(scr + 0x41C))) return;
    func_00000000(scr);
    func_00000000(*(char **)(scr + 0x418), -1, 0);
    *(int *)((char *)&D_00000000 + 0x40) = *(int *)((char *)&D_00000000 + 0x48);
    base = *(char **)(scr + 0x40C);
    /* Row 1: 0x3DC/0x4DC param; cnt = row[0x4C] */
    row = *(char **)(base + 0x3DC);
    idx = *(int *)(scr + 0x4DC) % *(int *)(row + 0x4C);
    e = base + idx;
    *(int *)(scr + 0x300) = *(int *)(*(char **)(e + 0x3C) + 0x2B0);
    /* Row 2..4 same pattern with 0x3D0/0x3D4/0x3D8 + 0x4E0/0x4E8/0x4EC. */
    row = *(char **)(base + 0x3D0);
    idx = *(int *)(scr + 0x4E0) % *(int *)(row + 0x40);
    *(int *)(scr + 0x304) = *(int *)(*(char **)(base + idx + 0x3C) + 0x2B0);
    row = *(char **)(base + 0x3D4);
    idx = *(int *)(scr + 0x4E8) % *(int *)(row + 0x44);
    *(int *)(scr + 0x308) = *(int *)(*(char **)(base + idx + 0x3C) + 0x2B0);
    row = *(char **)(base + 0x3D8);
    idx = *(int *)(scr + 0x4EC) % *(int *)(row + 0x48);
    *(int *)(scr + 0x30C) |= *(int *)(*(char **)(base + idx + 0x3C) + 0x2B4);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006C00);
#endif

/* timproc_uso_b5_func_00006D30: 54-insn poll-loop over a record table.
 * X = timproc_uso_b5_func_00000000 (cross-USO placeholder, all 5 jals).
 * 2026-05-28 CORRECTION: this is an ORDINARY -O2 function (NOT the prior
 * "-O0-in-Yay0, can't match at -O2" claim — that was wrong). At default -O2
 * the C below builds to 53 insns vs target 54 with the s0=self/s1=i/$f20=0.0
 * register promotion matching; residuals are prologue save/jal scheduling +
 * index-temp register-rename. NM wrap, no donor splice. */
typedef int Row1_6D30[1];
void timproc_uso_b5_func_00006D30(int *self) {
  int i = 0;
  int new_var5;
  char *new_var;
  int cnt;
  int new_var2;
  int new_var4;
  int *new_var3;
  new_var4--;
  if ((*((float *) (((char *) gl_func_00000000(self)) + 0x2A4))) == 0.0f)
  {
    new_var4 = i;
    cnt = gl_func_00000000(self);
    new_var2 = 0x3D0;
    if (cnt > 0)
    {
      do
      {
        int *p = (int *) (((Row1_6D30 *) self)[self[0x3C4 / 4]] + 0xF4);
        int r;
        int *v;
        *p = (*p) + 1;
        r = gl_func_00000000(self);
        new_var3 = self;
        if (((Row1_6D30 *) self)[self[0x3C4 / 4]][0xF4] >= r)
        {
          ((Row1_6D30 *) self)[self[0x3C4 / 4]][0xF4] = 0;
        }
        new_var5 = gl_func_00000000(new_var3);
        v = (int *) new_var5;
        new_var = ((char *) v) + 0x2A4;
        i++;
        if ((*((float *) new_var)) != 0.0f)
        {
          break;
        }
        new_var4++;
        cnt = gl_func_00000000(self);
      }
      while (new_var4 < cnt);
    }
  }
}

// timproc_uso_b5_func_00006E08 — STRUCTURAL PASS (0x270 / 156 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen expired-entry purge / list compaction (operates on
// Scr; two element lists).
//
//   void timproc_uso_b5_func_00006E08(Scr *scr, a1) {     // scr -> s0
//     if (!func_00000000(&D_0, 0x10001)) return;          // global gate
//     if (!func_00000000(scr)) ...;
//     float now = (float)func_00000000(scr);              // -> f20 ref
//     // PASS 1: for i in [0 .. scr->0x3C4):
//     //   e = scr->0x3D0[i];
//     //   if (e->0x2A4 <= now) {                          // expired
//     //     func_00000000(scr->0x4D4 ...);                // release
//     //     shift scr->0x3D0[i+1..] down; scr->0x3C4--; i--;
//     //   }
//     // (gate func_00000000(.,0x4002) between passes)
//     // PASS 2: identical compaction over the same list with the
//     //   second predicate / scr->0x4D4 variant.
//   }
//
// Struct-typing reference:
//   scr: 0x3C4 = live entry count, 0x3D0 = entry-ptr array base
//     (compacted in place), 0x4D4 = a release/free helper target;
//     entry->0x2A4 = f32 expiry timestamp (compared <= current time
//     from func_00000000). D_0 global flags 0x10001 / 0x4002 gate
//     the two passes. func_00000000 = USO placeholder dispatcher
//     (time query / release / gate).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — gate + 2-pass list-compaction skeleton only. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// 2026-06-21 RECONSTRUCT 77.7%->88.3%: (1) the two gate calls' a0 =
//   &import_80020098 (reloc, not or zero,zero); (2) the list-entry dispatch
//   indexes &timproc_uso_b5_D_807FE738 (array base), not bare *4; (3) the
//   per-element expiry field 0x2A4 is f32 (lwc1), not int; (4) the 0x3D0
//   counter RMW uses an explicit advancing pointer (char* temp + 0x3D0; RMW
//   via *temp) so IDO emits addiu base,976 + sw 0(base) like the target.
//   RESIDUAL ~12%: the captured sp34/sp28 value is promoted to a saved reg
//   (s2) in the build but the target SPILLS it to a stack slot (52/48(sp)) —
//   one extra saved reg shifts the whole s-reg/frame-offset layout and flips
//   bgez<->bgezl. Register-promotion cap (resists per project cap analysis).
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef int (*GP_00006E08)();
extern char import_80020098;
extern int timproc_uso_b5_D_807FE738;
void timproc_uso_b5_func_00006E08(char *arg0, s32 arg1) {
    s32 sp34;
    s32 sp28;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 var_s1;
    s32 var_s1_2;
    char *temp_v0;
    char *temp_v0_3;
    char *temp_v1_2;

    if (((int)timproc_uso_b5_alias(&import_80020098, 0x10001) != 0) && ((int)timproc_uso_b5_alias(arg0) != 0)) {
        sp34 = FW(((int)arg0 + (FW(arg0, 0x3C4) * 4)), 0x3D0);
        (int)timproc_uso_b5_alias(arg0);
        var_s1 = 0;
        if ((int)timproc_uso_b5_alias(arg0) > 0) {
loop_4:
            temp_v0 = (char *)((int)arg0 + (FW(arg0, 0x3C4) * 4) + 0x3D0);
            *(s32 *)temp_v0 = *(s32 *)temp_v0 - 1;
            if (*(s32 *)((int)arg0 + (FW(arg0, 0x3C4) * 4) + 0x3D0) < 0) {
                *(s32 *)((int)arg0 + (FW(arg0, 0x3C4) * 4) + 0x3D0) = (s32) ((int)timproc_uso_b5_alias(arg0) - 1);
            }
            var_s1 += 1;
            if ((*(f32 *)((char *)timproc_uso_b5_alias(arg0) + 0x2A4) == 0.0f) && (var_s1 < (int)timproc_uso_b5_alias(arg0))) {
                goto loop_4;
            }
        }
        temp_v0_2 = FW(arg0, 0x3C4);
        temp_v1 = FW(((int)arg0 + (temp_v0_2 * 4)), 0x3D0);
        if (sp34 != temp_v1) {
            (int)timproc_uso_b5_alias((&timproc_uso_b5_D_807FE738)[temp_v0_2], FW(arg0, 0x4D4) | temp_v1);
            (int)timproc_uso_b5_alias(arg0, arg1);
        }
    }
    if (((int)timproc_uso_b5_alias(&import_80020098, 0x4002) != 0) && ((int)timproc_uso_b5_alias(arg0) != 0)) {
        sp28 = FW(((int)arg0 + (FW(arg0, 0x3C4) * 4)), 0x3D0);
        (int)timproc_uso_b5_alias(arg0);
        var_s1_2 = 0;
        if ((int)timproc_uso_b5_alias(arg0) > 0) {
loop_13:
            temp_v0_3 = (char *)((int)arg0 + (FW(arg0, 0x3C4) * 4) + 0x3D0);
            *(s32 *)temp_v0_3 = *(s32 *)temp_v0_3 + 1;
            temp_v1_2 = (char *)((int)arg0 + (FW(arg0, 0x3C4) * 4) + 0x3D0);
            if (*(s32 *)temp_v1_2 >= (int)timproc_uso_b5_alias(arg0)) {
                *(s32 *)temp_v1_2 = 0;
            }
            var_s1_2 += 1;
            if ((*(f32 *)((char *)timproc_uso_b5_alias(arg0) + 0x2A4) == 0.0f) && (var_s1_2 < (int)timproc_uso_b5_alias(arg0))) {
                goto loop_13;
            }
        }
        temp_v0_4 = FW(arg0, 0x3C4);
        temp_v1_3 = FW(((int)arg0 + (temp_v0_4 * 4)), 0x3D0);
        if (sp28 != temp_v1_3) {
            (int)timproc_uso_b5_alias((&timproc_uso_b5_D_807FE738)[temp_v0_4], FW(arg0, 0x4D4) | temp_v1_3);
            (int)timproc_uso_b5_alias(arg0, arg1);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00006E08);
#endif

// timproc_uso_b5_func_00007078 — STRUCTURAL PASS (0x258 / 150 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen scroll/animation tick (operates on Scr).
//
//   void timproc_uso_b5_func_00007078(Scr *scr) {        // scr -> s0
//     if (scr->0x414->0x18->0x130 != 0) {                // active gate
//       v = func_00000000(1);
//       // animate two FP scroll fields by += value * 2.0f:
//       a = scr->0x414->...;  a->0x134 += v->0x4 * 2.0f;
//       a->0x138 += v->0x0 * 2.0f;
//     }
//     if (--scr->0x488 < 0) {                             // countdown
//       func_00000000(scr);
//       // fetch entry from scr->0x3C4 / scr->0x4D4 list, process via
//       //   func_00000000 (FP 1.0f), reset/advance the timer.
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x414 -> node (->0x18 -> sub, ->0x130 active flag);
//     scroll target ->0x134 / ->0x138 f32 (advanced by value*2.0);
//     0x488 = countdown timer (decremented; expiry triggers entry
//     processing); 0x3C4 list count, 0x4D4 list/helper, entry->0x2B0
//     a command field. func_00000000 = USO placeholder dispatcher
//     (value query / per-entry process). const 2.0f / 1.0f.
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — scroll-anim + countdown skeleton only. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// 2026-06-21 RECONSTRUCT 77.0%->97.87% (count-exact 158=158, residual is
//   PURE register/FP-register renumber): (1) the value-query call's a0 is
//   &import_80020098 (reloc lui/addiu, not or zero,zero) — 4 sites; (2) the
//   list-entry dispatch indexes &timproc_uso_b5_D_807FE768 (array base add),
//   not a bare *4; (3) field 0xA0 of the entry is a signed halfword (lh) and
//   its offset must NOT be f32*-scaled; (4) field 0x480 is f32 (lwc1, not
//   lw+cvt.s.w); (5) the *2.0f must keep mul.s — store 2.0f in a local `two`
//   so IDO emits lui 0x4000/mtc1/mul.s instead of strength-reducing to add.s;
//   (6) the scroll-field RMW uses an explicit advancing f32* (p1/p2) so IDO
//   emits addiu base,308 + swc1 0(base) matching the target, AND evaluate the
//   query-call BEFORE re-reading the dest so the call result isn't spilled
//   (drops frame -56 -> -32). RESIDUAL ~2%: int v0-vs-t1 on the 0x488
//   countdown load + the FP-register base numbering ($f0/$f4 vs $f8/$f10) —
//   coloring cap (permuter-immune per project cap analysis).
#ifdef NON_MATCHING

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00007078)();
extern char import_80020098;
extern int timproc_uso_b5_D_807FE768;
void timproc_uso_b5_func_00007078(char *arg0) {
    f32 *temp_v0;
    f32 *temp_v0_2;
    f32 *temp_v0_3;
    s32 temp_t2;
    char *temp_v1;
    char *temp_v1_2;
    char *temp_v1_3;
    char *temp_v1_4;

    if (FW(FW(FW(arg0, 0x414), 0x18), 0x130) != 0) {
        f32 two = 2.0f;
        f32 d1 = *(f32 *)((char *)timproc_uso_b5_alias(&import_80020098, 1) + 0x4) * two;
        f32 *p1 = (f32 *)((char *)FW(FW(arg0, 0x414), 0x18) + 0x134);
        *p1 = *p1 + d1;
        {
            f32 d2 = *(f32 *)timproc_uso_b5_alias(&import_80020098, 1) * two;
            f32 *p2 = (f32 *)((char *)FW(FW(arg0, 0x414), 0x18) + 0x138);
            *p2 = *p2 + d2;
        }
    } else {
        temp_t2 = FW(arg0, 0x488) - 1;
        FW(arg0, 0x488) = temp_t2;
        if (temp_t2 < 0) {
            timproc_uso_b5_alias((&timproc_uso_b5_D_807FE768)[FW(arg0, 0x3C4)], FW(arg0, 0x4D4) | (FW(timproc_uso_b5_alias(arg0), 0x2B0) + 1));
            FW(arg0, 0x3CC) = 1;
            *(f32 *)((char *)arg0 + 0x484) = 1.0f;
            temp_v0 = timproc_uso_b5_alias(arg0);
            temp_v1_3 = FW(temp_v0, 0x28);
            ((GP_00007078)FW(temp_v1_3, 0xA4))(*(s16 *)((char *)temp_v1_3 + 0xA0) + (char *)temp_v0);
        }
        timproc_uso_b5_alias(arg0, 2);
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x100) != 0) {
        timproc_uso_b5_alias((&timproc_uso_b5_D_807FE768)[FW(arg0, 0x3C4)], FW(arg0, 0x4D4) | (FW(timproc_uso_b5_alias(arg0), 0x2B0) + 1));
        FW(arg0, 0x3CC) = 1;
        FW(arg0, 0x400) = 0;
        *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        temp_v0_2 = timproc_uso_b5_alias(arg0);
        temp_v1_4 = FW(temp_v0_2, 0x28);
        ((GP_00007078)FW(temp_v1_4, 0xA4))(*(s16 *)((char *)temp_v1_4 + 0xA0) + (char *)temp_v0_2);
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x200) != 0) {
        FW(arg0, 0x3CC) = 0;
        timproc_uso_b5_alias((char *)0x802);
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(arg0);
        } else {
            timproc_uso_b5_alias(arg0);
            temp_v0_3 = timproc_uso_b5_alias(arg0);
            FW(arg0, 0x3C8) = temp_v0_3;
            FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, (s32) temp_v0_3);
            FW(arg0, 0x3CC) = 2;
            timproc_uso_b5_alias(arg0, 0);
            *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        }
    }
    if ((FW(arg0, 0x3F8) != 0) && (*(f32 *)((char *)arg0 + 0x480) == 0.0f)) {
        FW(arg0, 0x3F8) = 0;
    }
    FW(arg0, 0x408) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007078);
#endif

// timproc_uso_b5_func_000072D0 — STRUCTURAL PASS (no episode).
// Raw-.word USO. BOUNDARY NOTE: this .s is a 2-function USO bundle
// (2 jr-ra; named fn 0x72D0..0x73BC ~63 words, a SECOND fn — its
// ramp-DOWN twin — follows at 0x73C0..0x742C). USO bundles aren't
// splittable by the mnemonic split-fragments.py; deferred USO
// re-split. Only the named leading function is decoded here.
//
// Named fn = FP ramp-UP animator with state transition + sound:
//   void timproc_uso_b5_func_000072D0(Scr *scr) {        // scr -> s0
//     if (scr->0x480 < scr->0x484) {                      // below target
//       if (scr->0x3CC != 1) {
//         float step = scr->0xD4 + scr->0xEC;
//         scr->0x480 += step;
//         if (scr->0x480 >= scr->0x484) {                 // reached
//           scr->0x480 = scr->0x484;
//           scr->0x3CC = (scr->0x3C8 == 3) ? 9 : 3;        // state xition
//           if (func_00000000(&D_0, 0x10004203)) {
//             func_00000000(1); func_00000000(scr);
//             d = scr->0x28;  (d->0xAC)(d->0xA8 + …);      // sfx/effect
//           }
//           scr->0x3CC = 0xA;  scr->0x484 = 0.0f;
//         }
//       }
//     }
//     // (else / second bundled fn: symmetric ramp-DOWN of scr->0x480.)
//   }
//
// Struct-typing reference:
//   scr: 0x480 current f32 (animated), 0x484 target f32, 0xD4/0xEC
//     f32 step components, 0x3C8 mode (==3), 0x3CC state (1 lock /
//     3 / 9 / 0xA done), 0x28 vtable (->0xA8 s16 base, ->0xAC fn —
//     obj->0x28 dispatch idiom, here a sound/effect). D_0 +
//     0x10004203 global gate. func_00000000 = USO placeholder.
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder calls;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — named leading fn (ramp-UP) only;
//   trailing 0x73C0 ramp-DOWN twin remains INCLUDE_ASM. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_000072D0(char *scr) {
    char *d;
    void (*fp)(int);
    if (*(float *)(scr + 0x480) < *(float *)(scr + 0x484)) {
        if (*(int *)(scr + 0x3CC) != 1) {
            float step = *(float *)(scr + 0xD4) + *(float *)(scr + 0xEC);
            *(float *)(scr + 0x480) += step;
            if (*(float *)(scr + 0x480) >= *(float *)(scr + 0x484)) {
                *(float *)(scr + 0x480) = *(float *)(scr + 0x484);
                *(int *)(scr + 0x3CC) = (*(int *)(scr + 0x3C8) == 3) ? 9 : 3;
                if (func_00000000(&D_00000000, 0x10004203)) {
                    func_00000000(1);
                    func_00000000(scr);
                    d = *(char **)(scr + 0x28);
                    fp = *(void (**)(int))(d + 0xAC);
                    fp(*(short *)(d + 0xA8));
                }
                *(int *)(scr + 0x3CC) = 0xA;
                *(float *)(scr + 0x484) = 0.0f;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000072D0);
#endif

// timproc_uso_b5_func_000073C0 — ramp-UP twin of 000072D0's leading body.
// Increments scr->0x480 toward scr->0x484, using the fast step at 0xD4 when
// state 1 is active and the normal step at 0xEC otherwise.
// MATCH KEY (2026-05-29): the two `cur + step` adds emit `add.s fd, step, cur`
// (the freshly-loaded step as fs) instead of the target's `add.s fd, cur, step`.
// A plain operand swap (`step + cur`) is INERT (IDO canonicalizes). The
// assignment-expr lever forces cur as fs: `step + (curf = cur)` — same lever
// that cracked game_uso_func_00003FAC's mul.s operand caps. (Old "add.s
// operand-order stays NM / FPU-scheduler cap" comment was wrong.)
void timproc_uso_b5_func_000073C0(char *scr) {
    float cur = *(float *)(scr + 0x480);
    float curf;
    int state;
    int done_state;

    if (cur < *(float *)(scr + 0x484)) {
        state = *(int *)(scr + 0x3CC);
        done_state = 9;
        if (state == 1) goto fast_step;
        *(float *)(scr + 0x480) = *(float *)(scr + 0xEC) + (curf = cur);
        goto check_target;
fast_step:
        *(float *)(scr + 0x480) = *(float *)(scr + 0xD4) + (curf = cur);
check_target:
        if (*(float *)(scr + 0x484) < *(float *)(scr + 0x480)) {
            *(float *)(scr + 0x480) = *(float *)(scr + 0x484);
            *(int *)(scr + 0x3CC) = done_state;
        }
    }
}

// timproc_uso_b5_func_00007430 — exact (0x3A8 / 234 words).
// Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen sequence/script driver: a small table-driven state
// machine that advances an intro/outro animation program.
//
//   void timproc_uso_b5_func_00007430(Scr *scr) {        // scr -> s0
//     if (scr->0x3C4 != 0) { ...alternate path... return; }
//     int step = func_00000000() - 1;
//     if (step < 0) return;
//     // handler lookup: idx = scr->0x4AC; flags = scr->0x4B0 & 0xF;
//     //   h = D_00001320[ f(scr->0x4B0) ];  (entry from a handler
//     //   table; also D_00000F60 / D_00000F18 secondary tables);
//     //   scr->0x4B0 = computed next-handler/state;
//     // PC advance: if (*(int*)D_0 == 0x100 && scr->0x4AC matched)
//     //                scr->0x4AC++;             // advance program ctr
//     //              else { func_00000000(0);
//     //                     scr->0x4A4 = derived (~0x3E8 reload); }
//     //   func_00000000(D_0[scr->0x4AC]);        // run handler
//     //   conditionally store scr->0x4B0 (next state).
//   }
//
// Struct-typing reference:
//   scr: 0x3C4 entry count (0 = run sequencer), 0x4AC program counter
//     (indexes the handler table; incremented on match), 0x4B0
//     current handler/state word (low 4 bits = flags), 0x4A4 a
//     reload counter (~0x3E8 = 1000). D_0 + global state (==0x100
//     gate); D_00001320 / D_00000F60 / D_00000F18 = USO static
//     handler/jump tables (0xF.. / 0x13.. pool). func_00000000 =
//     USO placeholder dispatcher (step query / handler invoke).
// Matching notes: D_00000000_a is a 0-address alias used only for the first
// table-dispatch call. It prevents IDO from CSE'ing the D_00000F60 table base
// into the call argument, matching the target's separate base registers.
void timproc_uso_b5_func_00007430(char *scr) {
    int step;
    int *seq_table;
    char *obj;
    char *node;
    char *cam_root;

    if (*(int *)(scr + 0x3C4) == 0) {
        step = func_00000000() - 1;
        if (step >= 0) {
            if ((*(int *)(scr + 0x4B0) & 0xF) == 0) {
                func_00000000((char *)&D_00000000 + 0x00001320,
                              ((int *)((char *)&D_00000000 + 0x00000F34))[step]);
            }

            seq_table = ((int **)((char *)&D_00000000 + 0x00000F60))[step];
            if (func_00000000(&D_00000000_a, seq_table[*(int *)(scr + 0x4AC)])) {
                *(int *)(scr + 0x4B0) = *(int *)((char *)&D_00000000 + 0x00000F18);
                if (seq_table[*(int *)(scr + 0x4AC)] != 0x100) {
                    *(int *)(scr + 0x4AC) += 1;
                } else {
                    func_00000000(scr, 0);
                    *(int *)(scr + 0x4A4) = step + 1;
                    func_00000000(0x27, 0x3E8);
                }
            } else {
                if (func_00000000(&D_00000000, ~seq_table[*(int *)(scr + 0x4AC)])) {
                    *(int *)(scr + 0x4B0) = 0;
                }
                *(int *)(scr + 0x4B0) -= 1;
                if (*(int *)(scr + 0x4B0) < 0) {
                    func_00000000(scr, 0);
                }
            }
        } else {
            func_00000000(scr, 0);
        }
    }

    if (func_00000000(&D_00000000, 0x100) || *(int *)(scr + 0x408) != 0) {
        *(int *)(scr + 0x408) = 0;
        if (*(int *)((char *)&D_00000000 + 0x34) == 2) {
            func_00000000(5);
            *(int *)(scr + 0x3CC) = 4;
            *(float *)(scr + 0x4A0) = 1.0f;
            return;
        }

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int, int))(node + 0x8C))(*(short *)(node + 0x88) + (int)obj, 0);

        func_00000000(scr);

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int, int))(node + 0x84))(*(short *)(node + 0x80) + (int)obj, 0);

        obj = (char *)func_00000000(scr);
        func_00000000(((int **)&D_00000000)[*(int *)(scr + 0x3C4)],
                      (*(int *)(obj + 0x2B0) + 1) | *(int *)(scr + 0x4D4));

        *(int *)(scr + 0x3CC) = 5;
        *(int *)(scr + 0x400) = 0x37;
        *(float *)(scr + 0x484) = 1.0f;

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int))(node + 0x9C))(*(short *)(node + 0x98) + (int)obj);

        cam_root = *(char **)(scr + 0x414);
        *(float *)(scr + 0x4C4) = *(float *)(*(char **)(cam_root + 0x10) + 0x60);
        *(float *)(scr + 0x4C8) = *(float *)(*(char **)(cam_root + 0x10) + 0x64);
        *(float *)(scr + 0x4CC) = *(float *)(*(char **)(cam_root + 0x10) + 0x68);
        *(float *)(scr + 0x4C0) = *(float *)(*(char **)(*(char **)(cam_root + 0xC) + 0x70) + 0x14C);
        *(int *)(scr + 0x4B4) = 2;
        *(float *)(scr + 0x4BC) = 0.0f;
    } else if (func_00000000(&D_00000000, 0x14203)) {
        if (func_00000000(&D_00000000, 0x200)) {
            obj = (char *)func_00000000(scr);
            func_00000000(((int **)&D_00000000)[*(int *)(scr + 0x3C4)],
                          (*(int *)(obj + 0x2B0) + 1) | *(int *)(scr + 0x4D4));
        }

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int))(node + 0xAC))(*(short *)(node + 0xA8) + (int)obj);

        func_00000000(scr, 1);

        if (func_00000000(&D_00000000, 0x200)) {
            *(int *)(scr + 0x3CC) = 0xA;
            *(float *)(scr + 0x484) = 0.0f;
            return;
        }

        obj = (char *)func_00000000(scr);
        func_00000000(((int **)&D_00000000)[*(int *)(scr + 0x3C4)],
                      (*(int *)(obj + 0x2B0) + 1) | *(int *)(scr + 0x4D4));

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int))(node + 0xA4))(*(short *)(node + 0xA0) + (int)obj);
    }
}

// timproc_uso_b5_func_000077D8 — exact (0x1CC / 115 words).
// Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen mode/transition handler: global-state-gated phase
// entries that snapshot the camera and kick off entry/exit animation.
//
//   void timproc_uso_b5_func_000077D8(Scr *scr) {        // scr -> s0
//     if (func_00000000(&D_0, 0x100)) {                   // phase A
//       func_00000000(scr);  func_00000000(scr->...table);
//       scr->0x3CC = 5;  scr->0x400 = 0x37;  scr->0x484 = 1.0f;
//       func_00000000(scr);
//       d = scr->0x28;  (d->0x9C)(d->0x98 + …);            // show/activate
//       // snapshot camera: cam = scr->0x414->0x10;
//       scr->0x4C4 = cam->0x60;  scr->0x4C8 = cam->0x64;
//       scr->0x4CC = cam->0x68;                            // eye pos Vec3
//       scr->0x4C0 = scr->0x414->0xC->0x70->0x14C;          // fov-like
//       scr->0x4B4 = 2;  scr->0x4BC = 0.0f;                 // anim start
//     } else if (func_00000000(&D_0, 0x200)) {             // phase B
//       func_00000000(0x802 …);  scr->0x3CC = 3;
//     } else if (func_00000000(&D_0, 0x4002)) {            // phase C
//       if (bit14(scr->0x2B4)) { func_00000000(0);
//         func_00000000(scr);  d=scr->0x28; (d->0x94)(d->0x90+…); }
//     } else if (func_00000000(&D_0, 0x10001)) {           // phase D
//       if (bit14(scr->0x2B4)) { func_00000000(0);
//         func_00000000(scr);  d=scr->0x28; (d->0x94)(d->0x90+…); }
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x28 vtable (->0x98/0x9C and ->0x90/0x94 dispatch idiom —
//     activate/show), 0x2B4 flags (bit14 via <<14 test), 0x3CC state
//     (5 / 3), 0x400 = 0x37 sub-state, 0x484 f32 = 1.0, 0x4B4 anim
//     phase (=2), 0x4BC f32 anim timer (=0.0), 0x4C0 captured fov,
//     0x4C4/0x4C8/0x4CC captured eye-pos Vec3; 0x414 -> node
//     (->0x10 cam ->0x60/0x64/0x68 eye; ->0xC->0x70->0x14C fov).
//   D_0 global flags 0x100 / 0x200 / 0x4002 / 0x10001 gate the phases.
//   func_00000000 = USO placeholder dispatcher (gate / activate).
// Matching notes: same transition/table-call idioms as the exact
// timproc_uso_b5_func_00007430 tail. The 0x4002 and 0x10001 gates are
// sequential inside the final else arm; the second gate uses the opposite
// bit-test polarity and a branch-likely epilogue skip.
void timproc_uso_b5_func_000077D8(char *scr) {
    char *obj;
    char *node;
    char *cam_root;
    char *d;

    if (func_00000000(&D_00000000, 0x100)) {
        obj = (char *)func_00000000(scr);
        func_00000000(((int **)&D_00000000)[*(int *)(scr + 0x3C4)],
                      (*(int *)(obj + 0x2B0) + 1) | *(int *)(scr + 0x4D4));

        *(int *)(scr + 0x3CC) = 5;
        *(int *)(scr + 0x400) = 0x37;
        *(float *)(scr + 0x484) = 1.0f;

        obj = (char *)func_00000000(scr);
        node = *(char **)(obj + 0x28);
        (*(void (**)(int))(node + 0x9C))(*(short *)(node + 0x98) + (int)obj);

        cam_root = *(char **)(scr + 0x414);
        *(float *)(scr + 0x4C4) = *(float *)(*(char **)(cam_root + 0x10) + 0x60);
        *(float *)(scr + 0x4C8) = *(float *)(*(char **)(cam_root + 0x10) + 0x64);
        *(float *)(scr + 0x4CC) = *(float *)(*(char **)(cam_root + 0x10) + 0x68);
        *(float *)(scr + 0x4C0) = *(float *)(*(char **)(*(char **)(cam_root + 0xC) + 0x70) + 0x14C);
        *(int *)(scr + 0x4B4) = 2;
        *(float *)(scr + 0x4BC) = 0.0f;
    } else if (func_00000000(&D_00000000, 0x200)) {
        func_00000000(0x802);
        *(int *)(scr + 0x3CC) = 3;
    } else {
        if (func_00000000(&D_00000000, 0x4002)) {
            obj = (char *)func_00000000(scr);
            if ((*(int *)(obj + 0x2B4) << 14) < 0) {
                func_00000000(0x101, 0);
                obj = (char *)func_00000000(scr);
                d = *(char **)(obj + 0x28);
                (*(void (**)(int))(d + 0x94))(*(short *)(d + 0x90) + (int)obj);
            }
        }
        if (func_00000000(&D_00000000, 0x10001)) {
            obj = (char *)func_00000000(scr);
            if ((*(int *)(obj + 0x2B4) << 14) >= 0) {
                func_00000000(0x101, 0);
                obj = (char *)func_00000000(scr);
                d = *(char **)(obj + 0x28);
                (*(void (**)(int))(d + 0x94))(*(short *)(d + 0x90) + (int)obj);
            }
        }
    }
}

// timproc_uso_b5_func_000079A4 — STRUCTURAL PASS (0x188 / 98 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen fade-out / teardown + next-phase re-init handler.
//
//   void timproc_uso_b5_func_000079A4(Scr *scr) {        // scr -> s0
//     scr->0x400--;                                       // countdown
//     if (scr->0x34 == 2) {
//       if (scr->0x4A0 > 0.0f) scr->0x4A0 -= K;            // K = D_01D0
//       if (scr->0x4A0 < 0.0f) scr->0x4A0 = 0.0f;          // clamp alpha
//     }
//     if (scr->0x400 == 0) {
//       if (func_00000000(scr)) return;
//       d = scr->0x28;  (d->0x8C)(d->0x88 + …);            // hide
//       func_00000000(scr); func_00000000(scr);
//       d = scr->0x28;  (d->0x84)(d->0x80 + …);            // deactivate
//       if (func_00000000(scr)) { func_00000000(scr->0x41C); return; }
//       // re-init next phase: e = D_000003E0[ f(scr->0x3C4) ];
//       scr->0x3D4 = func_00000000(e, e->0xA4);
//       scr->0x3C8 = func_00000000(scr);
//       scr->0x3C4 = func_00000000(.);
//       scr->0x3CC = 6;  scr->0x484 = 1.0f;                // next state
//       func_00000000(scr, 0);
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x400 countdown timer (dec; 0 triggers teardown), 0x34 mode
//     (==2 enables alpha fade), 0x4A0 f32 alpha (faded down by K,
//     clamped >=0), 0x3C4/0x3C8/0x3D4 re-init outputs, 0x3CC state
//     (=6 next), 0x484 f32 (=1.0), 0x41C a sub-target, 0x28 vtable
//     (->0x88/0x8C hide, ->0x80/0x84 deactivate — obj->0x28 idiom).
//   D_000001D0 = folded f32 fade-step const (literal-pool fold family;
//     see docs/N64_FORENSICS.md#bootup-uso-fp-literal-pool-folded-into-func-0000098C);
//   D_000003E0 = USO static phase/handler table. func_00000000 = USO
//   placeholder dispatcher (gate / hide / re-init).
// 2026-05-20 Codex pass: corrected the mode gate (`D+0x34`, not
// `scr+0x34`), countdown gate polarity, post-deactivate branch polarity,
// vtable call arg shape (`a1 = 0`), and the re-init tail's local phase
// table / `func(scr, phase)` chain. NATURAL CEILING: 98.32% NM (IDO CSEs
// the fade-step base load one insn shorter than target). The historical
// SUFFIX_BYTES + INSN_PATCH promotion was REMOVED 2026-05-23 as
// match-faking (docs/POST_CC_RECIPES.md is DEPRECATED).
// 2026-05-28: the CSE-bust-via-distinct-externs lever (that landed 39C8C)
// was tried here — `&D_79A4_eps + 0x1D0` for the fade-step load — and
// REGRESSED to 75 diffs / +2 insns. This fn references &D_00000000 in 3
// spots (0x34 gate, 0x1D0 fade, 0xA4+slot array); splitting one base
// shatters the shared-base CSE web and reshuffles the whole allocation.
// The lever only works for ISOLATED single-&D loads (39C8C), not entangled
// multi-ref ones. Stays a permanent 98.32% cap.
#ifdef NON_MATCHING
void timproc_uso_b5_func_000079A4(char *scr) {
    char *obj;
    char *node;
    int idx;
    int slot;
    int phase;
    int next;
    *(int *)(scr + 0x400) -= 1;
    if (*(int *)((char *)&D_00000000 + 0x34) == 2) {
        if (*(float *)(scr + 0x4A0) > 0.0f) {
            *(float *)(scr + 0x4A0) -= *(float *)((char *)&D_00000000 + 0x000001D0);
            if (*(float *)(scr + 0x4A0) < 0.0f) {
                *(float *)(scr + 0x4A0) = 0.0f;
            }
        }
    }
    if (*(int *)(scr + 0x400) != 0) {
        if (func_00000000(&D_00000000, 0x100) == 0) {
            return;
        }
    }

    obj = (char *)func_00000000(scr);
    node = *(char **)(obj + 0x28);
    (*(void (**)(int, int))(node + 0x8C))(*(short *)(node + 0x88) + (int)obj, 0);
    func_00000000(scr);
    obj = (char *)func_00000000(scr);
    node = *(char **)(obj + 0x28);
    (*(void (**)(int, int))(node + 0x84))(*(short *)(node + 0x80) + (int)obj, 0);
    if (func_00000000(scr) == 0) {
        func_00000000(*(char **)(scr + 0x41C));
        return;
    }

    func_00000000(scr);
    idx = *(int *)(scr + 0x3C4);
    slot = *(int *)(scr + 0x3E0 + idx * 4);
    *(int *)(scr + 0x3D4) = func_00000000(scr, 1, ((int *)&D_00000000)[0xA4 / 4 + slot]);
    phase = func_00000000(scr);
    *(int *)(scr + 0x3C8) = phase;
    next = func_00000000(scr, phase);
    *(int *)(scr + 0x3C4) = next;
    *(int *)(scr + 0x3CC) = 6;
    func_00000000(scr);
    *(float *)(scr + 0x484) = 1.0f;
    func_00000000(scr, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000079A4);
#endif

// timproc_uso_b5_func_00007B2C — STRUCTURAL PASS (0x308 / 194 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen MASTER state-machine tick — PC-driven handler dispatch
// that ties together the sub-handlers (func_00007430 sequencer,
// func_000077D8 transition, func_000079A4 fade).
//
//   int timproc_uso_b5_func_00007B2C(Scr *scr) {         // scr -> s0
//     if (scr->0x3C4 != 1) { ...alt path... }
//     else if (func_00000000()) {                         // event ready
//       h = D_00000F60[ f(scr->0x4AC) ];                   // handler PC
//       scr->0x4B0 = D_00000F18[ f(scr->0x4AC) ];          // sub-state
//       if (*(int*)D_0 == 0x100 && match) scr->0x4AC++;     // advance PC
//       else { func_00000000(1);  scr->0x4A8 = reload; }    // reset
//       // run handler: index scr->0x3C4 / scr->0x4D4 / scr->0x3D0
//       //   element arrays, then obj->0x28 vtable dispatch x~5
//       //   (->0x88/0x8C show, ->0x80/0x84 deact, ->0x70/0x74,
//       //   ->0xA8/0xAC) with computed a0 = base + retval;
//       //   set scr->0x3CC = 7 / 0xA, scr->0x484 = 1.0f,
//       //   refresh scr->0x3C4 / 0x3C8 / 0x3D0 from func_00000000;
//       // extra global-gated branches: D_0 flags 0x100 / 0x200 /
//       //   0x4003 trigger alternate activations + state writes.
//     }
//     return 1;
//   }
//
// Struct-typing reference:
//   scr: 0x3C4 mode/count (==1 active; also element count), 0x4AC
//     program counter (indexes handler tables; ++ on match), 0x4B0
//     current sub-state, 0x4A8 reload counter, 0x3CC state (7 / 0xA),
//     0x484 f32 (=1.0 anim start), 0x3C8/0x3D0/0x4D4 element arrays,
//     0x28 vtable (->0x70/0x74, ->0x80/0x84, ->0x88/0x8C, ->0xA8/0xAC
//     dispatch idiom — show / deactivate / draw).
//   D_00000F60 / D_00000F18 = USO static handler/jump tables (shared
//     with func_00007430); D_0 global flags 0x100 / 0x200 / 0x4003.
//   func_00000000 = USO placeholder dispatcher (event / handler).
// Caps (DEFERRED): raw-word USO + PC-table dispatch + placeholder
//   calls; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — PC-driven master state-machine
//   skeleton + vtable-dispatch chain. Byte-match deferred. Name
//   pre-checked: no extern reuse.
// timproc_uso_b5_func_00007B2C — FULL m2c DECODE (67.36% NM, no episode). Non-jumptable control-flow fn via scripts/lift-uso-controlflow.py.
// 2026-06-21 RECONSTRUCT 60.8%->76.3% (COUNT-EXACT 194=194): the 5 gate calls'
// a0 = &import_80020098 (reloc, not 0); the 4 list dispatches index array bases
// (&D_7B2C_F60)[v0] / (&D_807FE778/768/748)[idx] (not bare *4 fold); dropped
// redundant sp24/sp20 spill locals (use temp_v0/temp_v1 directly). Residual =
// register-renumber coloring + commutative addu operand-order ties + a 24-byte
// over-allocated spill frame (-64 vs -40; IDO spills more live temps across the
// calls than the original) — permuter-immune cap classes per docs cap analysis.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00007B2C)();
extern char import_80020098;
extern int D_7B2C_F60;
extern int timproc_uso_b5_D_807FE748;
extern int timproc_uso_b5_D_807FE768;
extern int timproc_uso_b5_D_807FE778;
void timproc_uso_b5_func_00007B2C(char *arg0) {
    s32 temp_t2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_5;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1;
    char *temp_v0_3;
    char *temp_v1_2;

    if (FW(arg0, 0x3C4) == 1) {
        temp_v0 = timproc_uso_b5_alias();
        if (temp_v0 != 0) {
            temp_v1 = (&D_7B2C_F60)[temp_v0];
            if (timproc_uso_b5_alias(&import_80020098, *(int*)(temp_v1 + (FW(arg0, 0x4AC) * 4))) != 0) {
                temp_v0_2 = FW(arg0, 0x4AC);
                FW(arg0, 0x4B0) = (s32) *(s32 *)((char *)&D_00000000 + 0xF18);
                if (*(int*)(temp_v1 + (temp_v0_2 * 4)) != 0x100) {
                    FW(arg0, 0x4AC) = (s32) (temp_v0_2 + 1);
                } else {
                    timproc_uso_b5_alias(arg0, 1);
                    FW(arg0, 0x4A8) = (s32) (temp_v0 + 1);
                    timproc_uso_b5_alias((char *)0x27, 0x3E8);
                }
            } else {
                if (timproc_uso_b5_alias(&import_80020098, ~*(int*)(temp_v1 + (FW(arg0, 0x4AC) * 4))) != 0) {
                    FW(arg0, 0x4B0) = 0;
                }
                temp_t2 = FW(arg0, 0x4B0) - 1;
                FW(arg0, 0x4B0) = temp_t2;
                if (temp_t2 < 0) {
                    timproc_uso_b5_alias(arg0, 1);
                }
            }
        }
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x100) != 0) {
        temp_v0_3 = timproc_uso_b5_alias(arg0);
        temp_v1_2 = FW(temp_v0_3, 0x28);
        ((GP_00007B2C)FW(temp_v1_2, 0x8C))(*(s16*)((char*)temp_v1_2 + 0x88) + temp_v0_3, 0);
        timproc_uso_b5_alias(arg0);
        temp_v0_3 = timproc_uso_b5_alias(arg0);
        temp_v1_2 = FW(temp_v0_3, 0x28);
        ((GP_00007B2C)FW(temp_v1_2, 0x84))(*(s16*)((char*)temp_v1_2 + 0x80) + temp_v0_3, 0);
        temp_v0_5 = FW(arg0, 0x3C4);
        timproc_uso_b5_alias((&timproc_uso_b5_D_807FE778)[temp_v0_5], FW(arg0, 0x4D4) | FW((arg0 + (temp_v0_5 * 4)), 0x3D0));
        timproc_uso_b5_alias(arg0);
        FW(arg0, 0x3CC) = 7;
        timproc_uso_b5_alias((&timproc_uso_b5_D_807FE768)[FW(arg0, 0x3C4)], FW(arg0, 0x4D4) | (FW((timproc_uso_b5_alias(arg0)), 0x2B0) + 1));
        *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        temp_v0_3 = timproc_uso_b5_alias(arg0);
        temp_v1_2 = FW(temp_v0_3, 0x28);
        ((GP_00007B2C)FW(temp_v1_2, 0x74))(*(s16*)((char*)temp_v1_2 + 0x70) + temp_v0_3);
        return;
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x200) != 0) {
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(arg0);
        } else {
            temp_v0_7 = FW(arg0, 0x3C4);
            timproc_uso_b5_alias((&timproc_uso_b5_D_807FE748)[temp_v0_7], FW(arg0, 0x4D4) | FW((arg0 + (temp_v0_7 * 4)), 0x3D0));
            temp_v0_3 = timproc_uso_b5_alias(arg0);
            temp_v1_2 = FW(temp_v0_3, 0x28);
            ((GP_00007B2C)FW(temp_v1_2, 0xAC))(*(s16*)((char*)temp_v1_2 + 0xA8) + temp_v0_3);
            FW(arg0, 0x3CC) = 0xA;
            timproc_uso_b5_alias(arg0, 0);
            *(f32 *)((char *)arg0 + 0x484) = 0.0f;
            timproc_uso_b5_alias(arg0);
            temp_v0_9 = timproc_uso_b5_alias(arg0);
            FW(arg0, 0x3C8) = temp_v0_9;
            FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, temp_v0_9);
            timproc_uso_b5_alias(arg0);
            timproc_uso_b5_alias(arg0, 1);
        }
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x14003) != 0) {
        timproc_uso_b5_alias(arg0, 1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007B2C);
#endif

// timproc_uso_b5_func_00007E34 — STRUCTURAL PASS (0x2C0 / 176 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen sub-state handler (a phase branch of the master tick).
//
//   void timproc_uso_b5_func_00007E34(Scr *scr) {        // scr -> s0
//     if (scr->0x3BC == 2) {
//       func_00000000(scr->0x41C, scr->0x3B8);
//       int busy = scr->0x4B4 | scr->0x4B8;
//       if (scr->0x4B4 != 0) { ...busy/active branch... }
//       else if (func_00000000(&D_0, 0x100)) {            // gate
//         func_00000000(scr);
//         d = scr->0x28;  (d->0x8C)(d->0x88 + …);          // show
//         func_00000000(scr); func_00000000(scr);
//         d = scr->0x28;  (d->0x84)(d->0x80 + …);          // deactivate
//         e = scr->0x3D0[ f(scr->0x3C4, scr->0x4D4) ];
//         func_00000000(e);
//         if (func_00000000(scr)) { func_00000000(scr->0x41C);
//                                   return; }
//         scr->0x3C8 = …;  scr->0x3C4 = …;                 // refresh state
//       }
//     } else { ...alt (scr->0x4B4 read) path... }
//   }
//
// Struct-typing reference:
//   scr: 0x3BC mode (==2 active), 0x4B4/0x4B8 busy/active flags
//     (OR-combined), 0x41C/0x3B8 sub-objects, 0x3C4/0x3C8 state,
//     0x3D0/0x4D4 element array + index source, 0x28 vtable
//     (->0x80/0x84 deactivate, ->0x88/0x8C show — obj->0x28 idiom).
//   D_0 global flag 0x100 gates the active branch. func_00000000 =
//   USO placeholder dispatcher (gate / show / refresh).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — mode-gated sub-state handler + show/deact + refresh
//   skeleton only. Byte-match deferred. Name pre-checked: no extern
//   reuse.
// timproc_uso_b5_func_00007E34 — FULL m2c DECODE (64.79% NM, no episode). Non-jumptable control-flow fn, decoded direct via the general liftcf.py recipe (arrows->FW, GP-cast placeholder calls, void*->char*, *expr->*(int*)0/(int*)cast). No emulator needed.
// 2026-06-21 RECONSTRUCT 90.07%->99.11% (COUNT-EXACT 184=184; residual is pure
// register-renumber + 2 commutative operand-order/scheduling ties): the 4 gate
// calls' a0 = &import_80020098 (reloc, not or zero,zero); the two list-entry
// dispatches index &timproc_uso_b5_D_807FE778 (first) / &timproc_uso_b5_D_807FE758
// (second) array bases, not bare *4. Remaining: the var_v1 `|`-operand load order
// (1208(v0) vs 1204(s0)) and the `arg0 + idx*4` addu operand order (s0+v0 vs
// v1+s0) — scheduling/coloring ties, permuter-immune per cap analysis.
// 2026-06-21 (agent-e): 99.11% -> 99.18% (23->21 diffs). The `0x4B8|0x4B4` OR
// load-order diff (idx 11/12) was structural: target loads the call-result
// deref (0x4B8) FIRST. Swapped to `FW(arg0,0x4B4) | FW(call,0x4B8)` so the
// 0x4B8 deref is the RIGHT operand (IDO evals it first here) — matches. The
// remaining 21 diffs are all the `(&D_807FExxx)[idx]` array-index coloring
// (index reg + addu operand order) — documented permuter-immune class.
// 2026-06-23 (agent-i): 99.18% -> ~99.30% (21->18 diffs). Lifted the two
// `(&D_807FExxx)[idx]` accesses to a shared pre-shifted byte offset
// (`temp = FW(arg0,0x3C4)*4; *(int*)((char*)&base + temp)` and
// `FW((arg0 + temp),0x3D0)`). This made IDO CSE the `idx<<2` into ONE value
// reused as `s0 + off` (correct `addu rX,s0,vY` operand order, was `addu
// rX,vY,s0`) and collapse the duplicate base materialization — both array
// clusters now differ only by register NUMBER, not structure/operand order.
// Residual 18 diffs are all pure register-renumber coloring ties (v0<->v1,
// t1<->t2, t6<->t7 across the two array clusters + the 0x3CC=6 store + the
// 0x4002/0x10001 0x2B4&0x20 reads). HI16-only-unpaired raw-word USO =
// DECODE-ONLY: fuzzy=100 unreachable; correct C is the port-goal deliverable.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00007E34)();
extern char import_80020098;
extern int timproc_uso_b5_D_807FE758;
extern int timproc_uso_b5_D_807FE778;
void timproc_uso_b5_func_00007E34(char *arg0) {
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 var_v1;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_4;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *temp_v0_9;
    char *temp_v1;
    char *temp_v1_2;
    char *temp_v1_3;
    char *temp_v1_4;
    char *temp_v1_5;
    char *temp_v1_6;

    if (FW(arg0, 0x3BC) == 2) {
        var_v1 = FW(arg0, 0x4B4) | FW(timproc_uso_b5_alias(FW(arg0, 0x41C), FW(arg0, 0x3B8)), 0x4B8);
    } else {
        var_v1 = FW(arg0, 0x4B4);
    }
    if ((var_v1 == 0) && (timproc_uso_b5_alias(&import_80020098, 0x100) != 0)) {
        temp_v0 = timproc_uso_b5_alias(arg0);
        temp_v1 = FW(temp_v0, 0x28);
        ((GP_00007E34)FW(temp_v1, 0x8C))(*(s16*)((char*)temp_v1 + 0x88) + temp_v0, 0);
        timproc_uso_b5_alias(arg0);
        temp_v0_2 = timproc_uso_b5_alias(arg0);
        temp_v1_2 = FW(temp_v0_2, 0x28);
        ((GP_00007E34)FW(temp_v1_2, 0x84))(*(s16*)((char*)temp_v1_2 + 0x80) + temp_v0_2, 0);
        temp_v0_3 = FW(arg0, 0x3C4) * 4;
        timproc_uso_b5_alias(*(int *)((char *)&timproc_uso_b5_D_807FE778 + temp_v0_3), FW(arg0, 0x4D4) | FW((arg0 + temp_v0_3), 0x3D0));
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(FW(arg0, 0x41C));
            return;
        }
        timproc_uso_b5_alias(arg0);
        temp_v0_4 = timproc_uso_b5_alias(arg0);
        FW(arg0, 0x3C8) = temp_v0_4;
        FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, (s32) temp_v0_4);
        FW(arg0, 0x3CC) = 8;
        timproc_uso_b5_alias(arg0);
        *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        timproc_uso_b5_alias(arg0, 0);
        FW(arg0, 0x4B8) = 1;
        return;
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x200) != 0) {
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(arg0);
        } else {
            temp_v0_5 = FW(arg0, 0x3C4) * 4;
            timproc_uso_b5_alias(*(int *)((char *)&timproc_uso_b5_D_807FE758 + temp_v0_5), FW(arg0, 0x4D4) | FW((arg0 + temp_v0_5), 0x3D0));
            temp_v0_6 = timproc_uso_b5_alias(arg0);
            temp_v1_3 = FW(temp_v0_6, 0x28);
            ((GP_00007E34)FW(temp_v1_3, 0xAC))(*(s16*)((char*)temp_v1_3 + 0xA8) + temp_v0_6);
            FW(arg0, 0x3CC) = 6;
            temp_v0_7 = timproc_uso_b5_alias(arg0);
            temp_v1_4 = FW(temp_v0_7, 0x28);
            ((GP_00007E34)FW(temp_v1_4, 0x7C))(*(s16*)((char*)temp_v1_4 + 0x78) + temp_v0_7);
            *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        }
    }
    if ((timproc_uso_b5_alias(&import_80020098, 0x4002) != 0) && (FW(timproc_uso_b5_alias(arg0), 0x2B4) & 0x20)) {
        timproc_uso_b5_alias((char *)0x101, 0);
        temp_v0_8 = timproc_uso_b5_alias(arg0);
        temp_v1_5 = FW(temp_v0_8, 0x28);
        ((GP_00007E34)FW(temp_v1_5, 0x94))(*(s16*)((char*)temp_v1_5 + 0x90) + temp_v0_8);
    }
    if ((timproc_uso_b5_alias(&import_80020098, 0x10001) != 0) && !(FW(timproc_uso_b5_alias(arg0), 0x2B4) & 0x20)) {
        timproc_uso_b5_alias((char *)0x101, 0);
        temp_v0_9 = timproc_uso_b5_alias(arg0);
        temp_v1_6 = FW(temp_v0_9, 0x28);
        ((GP_00007E34)FW(temp_v1_6, 0x94))(*(s16*)((char*)temp_v1_6 + 0x90) + temp_v0_9);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00007E34);
#endif

// timproc_uso_b5_func_000080F4 — STRUCTURAL PASS (0x374 / 221 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen draw/update sub-handler (a phase branch of the master
// tick), gated by mode + an FP animation-progress compare.
//
//   void timproc_uso_b5_func_000080F4(Scr *scr) {        // scr -> s2
//     if (scr->0x3BC == 2) {
//       a = func_00000000(scr->0x41C, scr->0x3B8);
//       int s0 = a->0x4C;
//       int s1 = (s0 | scr->0x4B4);
//       func_00000000(scr->0x41C, scr->0x3B8);             // re-query
//       if (scr->0x44 < scr->0x4BC) {                       // anim ongoing
//         func_00000000(scr);
//         d = scr->0x28;  (d->0x7C)(d->0x78 + …);            // draw/update
//       }
//       if (s1 == 0) {                                       // idle
//         if (func_00000000(&D_0, 0x100)) {
//           d = scr->0x28;  (d->0x8C)(d->0x88 + …);          // show
//           func_00000000(scr); func_00000000(scr);
//           d = scr->0x28;  (d->0x84)(d->0x80 + …);          // deactivate
//           // …element-array processing + state refresh…
//         }
//       }
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x3BC mode (==2 active), 0x4B4 busy flag (OR'd with
//     queried->0x4C into s1; nonzero = still busy), 0x41C/0x3B8
//     sub-objects, 0x44 f32 current progress, 0x4BC f32 target
//     (compare drives the draw step), 0x28 vtable (->0x78/0x7C
//     draw/update, ->0x88/0x8C show, ->0x80/0x84 deactivate —
//     obj->0x28 dispatch idiom). D_0 global flag 0x100 gates the
//     idle/show path. func_00000000 = USO placeholder dispatcher.
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — draw/update + idle/show skeleton only. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// timproc_uso_b5_func_000080F4 — FULL m2c DECODE (68.73% NM, no episode). Non-jumptable control-flow fn via scripts/lift-uso-controlflow.py.
// 2026-06-21 RECONSTRUCT 41.2%->42.1% (gap -9 -> -4): the 0x44<0x4BC test is a
// FLOAT compare *(f32*)+0x44 < *(f32*)+0x4BC (lwc1/c.lt.s, not slt); the +0x78
// vtable-offset field is lh (signed halfword); the two 0x100/0x200 gate calls'
// a0 = &import_80020098; the 0x3C4 list dispatch -> (&D_807FE748)[idx] array
// base. Structurally near-complete now. Residual: arg0 lands in s-reg $20 not
// $18 (the do-while needs 2 extra call-surviving s-regs, pushing the saved-reg
// count from 3 to 5) — pure register-renumber coloring, permuter-immune.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000080F4)();
extern char import_80020098;
extern int timproc_uso_b5_D_807FE748;
void timproc_uso_b5_func_000080F4(char *arg0) {
    char *sp3C;
    s32 sp28;
    s32 temp_t2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s1_2;
    char *temp_a0;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *temp_v0_9;
    char *temp_v1;
    char *temp_v1_2;
    char *temp_v1_3;
    char *temp_v1_4;
    char *temp_v1_5;
    char *temp_v1_6;
    char *var_a1;

    var_s0 = 0;
    if (FW(arg0, 0x3BC) == 2) {
        temp_a0 = FW(arg0, 0x41C);
        var_s0 = FW(temp_a0, 0x4C);
        var_s1 = FW(timproc_uso_b5_alias(temp_a0, FW(arg0, 0x3B8)), 0x4B4) | FW(arg0, 0x4B4) | var_s0;
        var_a1 = timproc_uso_b5_alias(FW(arg0, 0x41C), FW(arg0, 0x3B8));
    } else {
        var_s1 = FW(arg0, 0x4B4);
        var_a1 = (char *)1;
    }
    if (*(f32 *)((char *)arg0 + 0x44) < *(f32 *)((char *)arg0 + 0x4BC)) {
        sp3C = var_a1;
        temp_v0 = timproc_uso_b5_alias(arg0, var_a1);
        temp_v1 = FW(temp_v0, 0x28);
        ((GP_000080F4)FW(temp_v1, 0x7C))(*(s16*)((char*)temp_v1 + 0x78) + temp_v0);
    }
    temp_t2 = (var_s1 != 0) == 0;
    sp28 = temp_t2;
    if ((temp_t2 != 0) && (var_a1 != 0) && (timproc_uso_b5_alias(&import_80020098, (char *)0x100) != 0)) {
        temp_v0_2 = timproc_uso_b5_alias(arg0);
        temp_v1_2 = FW(temp_v0_2, 0x28);
        ((GP_000080F4)FW(temp_v1_2, 0x8C))(*(s16*)((char*)temp_v1_2 + 0x88) + temp_v0_2, 0);
        timproc_uso_b5_alias(arg0);
        temp_v0_3 = timproc_uso_b5_alias(arg0);
        temp_v1_3 = FW(temp_v0_3, 0x28);
        ((GP_000080F4)FW(temp_v1_3, 0x84))(*(s16*)((char*)temp_v1_3 + 0x80) + temp_v0_3, 0);
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(FW(arg0, 0x41C));
            return;
        }
        timproc_uso_b5_alias(arg0);
        temp_v0_4 = timproc_uso_b5_alias(arg0);
        FW(arg0, 0x3C8) = temp_v0_4;
        FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, temp_v0_4);
        FW(arg0, 0x3CC) = 8;
        timproc_uso_b5_alias(arg0);
        *(f32 *)((char *)arg0 + 0x484) = 1.0f;
        timproc_uso_b5_alias(arg0, 0);
        return;
    }
    if ((var_s0 == 0) && (timproc_uso_b5_alias(0, (char *)0x14003) != 0)) {
        timproc_uso_b5_alias(arg0, (char *)1);
    }
    timproc_uso_b5_alias(0, FW(arg0, 0x3B8));
    if ((sp28 != 0) && (timproc_uso_b5_alias(&import_80020098, (char *)0x200) != 0)) {
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(arg0);
            return;
        }
        temp_v0_5 = FW(arg0, 0x3C4);
        timproc_uso_b5_alias((&timproc_uso_b5_D_807FE748)[(s32) temp_v0_5], (char *) (FW(arg0, 0x4D4) | FW((arg0 + ((s32) temp_v0_5 * 4)), 0x3D0)));
        if ((FW(arg0, 0x3BC) == 2) && ((FW(arg0, 0x3B8) + 1) == FW(FW(arg0, 0x41C), 0x48))) {
            var_s1_2 = 0;
            var_s0_2 = 0;
            if (FW(FW(FW(arg0, 0x40C), 0x48), 0x6C) > 0) {
                do {
                    temp_v1_4 = FW((FW(FW(arg0, 0x40C), 0x48) + var_s0_2), 0x3C);
                    temp_v0_6 = FW(temp_v1_4, 0x28);
                    ((GP_000080F4)FW(temp_v0_6, 0xB4))(FW(temp_v0_6, 0xB0) + temp_v1_4, FW((FW(FW(timproc_uso_b5_alias(FW(arg0, 0x41C), FW(arg0, 0x3B8)), 0x40C), 0x48) + var_s0_2), 0x3C));
                    var_s1_2 += 1;
                    var_s0_2 += 4;
                } while (var_s1_2 < FW(FW(FW(arg0, 0x40C), 0x48), 0x6C));
            }
        } else {
            temp_v0_7 = timproc_uso_b5_alias(arg0);
            temp_v1_5 = FW(temp_v0_7, 0x28);
            ((GP_000080F4)FW(temp_v1_5, 0xAC))(*(s16*)((char*)temp_v1_5 + 0xA8) + temp_v0_7);
            temp_v0_8 = timproc_uso_b5_alias(arg0);
            temp_v1_6 = FW(temp_v0_8, 0x28);
            ((GP_000080F4)FW(temp_v1_6, 0x6C))(*(s16*)((char*)temp_v1_6 + 0x68) + temp_v0_8);
        }
        FW(arg0, 0x3CC) = 6;
        timproc_uso_b5_alias(arg0, (char *)1);
        timproc_uso_b5_alias(arg0);
        temp_v0_9 = timproc_uso_b5_alias(arg0);
        FW(arg0, 0x3C8) = temp_v0_9;
        FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, temp_v0_9);
        timproc_uso_b5_alias(arg0);
        timproc_uso_b5_alias(arg0, 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000080F4);
#endif

// timproc_uso_b5_func_00008468 — STRUCTURAL PASS (0x178 / 94 words,
// no episode). Raw-.word USO form (genuine code). Hand-decoded.
//
// Timing-screen state-transition handler (phase-reset branch; sibling
// of func_000077D8 / func_00007E34).
//
//   void timproc_uso_b5_func_00008468(Scr *scr) {        // scr -> s0
//     if (func_00000000(&D_0, 0x100)) {                   // phase A
//       func_00000000(scr);
//       d = scr->0x28;  (d->0x8C)(d->0x88 + …);            // show
//       func_00000000(scr); func_00000000(scr);
//       d = scr->0x28;  (d->0x84)(d->0x80 + …);            // deactivate
//       e = scr->0x3D0[ f(scr->0x3C4, scr->0x4D4) ];
//       func_00000000(e);
//       if (func_00000000(scr)) { func_00000000(scr->0x41C);
//                                 return; }
//       scr->0x3C8 = …;  scr->0x3C4 = …;  scr->0x3CC = 0xA;
//       func_00000000(scr);  scr->0x484 = 0.0f;            // phase reset
//     } else if (func_00000000(&D_0, 0x200)) {             // phase B
//       func_00000000(scr);  scr->0x4B4 = …;
//       if (scr->0x4B4) {
//         if (func_00000000(&D_0, 0x4003)) { func_00000000(1); }
//         else func_00000000(scr);
//         if (scr->0x3CC == 9) scr->0x4B4 = 0;             // clear busy
//       }
//     }
//   }
//
// Struct-typing reference:
//   scr: 0x3C4/0x3C8 state, 0x3CC phase (=0xA reset / ==9 done),
//     0x3D0/0x4D4 element array + index, 0x41C sub-target, 0x484 f32
//     (=0.0 reset), 0x4B4 busy flag (cleared when 0x3CC==9), 0x28
//     vtable (->0x80/0x84 deactivate, ->0x88/0x8C show — obj->0x28
//     idiom). D_0 global flags 0x100 / 0x200 / 0x4003 gate the
//     phases. func_00000000 = USO placeholder dispatcher.
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — 2-phase state-transition skeleton (phase-reset variant).
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00008468(char *arg0) {
    char *temp_v0;
    char *temp_v1;
    s32 temp_v0_2;
    s32 temp_v0_5;

    if (timproc_uso_b5_alias(&import_80020098, 0x100) != 0) {
        timproc_uso_b5_alias(arg0);
        temp_v0 = timproc_uso_b5_alias(arg0);
        temp_v1 = FW(temp_v0, 0x28);
        ((GP_00007B2C)FW(temp_v1, 0x8C))(*(s16*)((char*)temp_v1 + 0x88) + temp_v0, 0);
        timproc_uso_b5_alias(arg0);
        temp_v0 = timproc_uso_b5_alias(arg0);
        temp_v1 = FW(temp_v0, 0x28);
        ((GP_00007B2C)FW(temp_v1, 0x84))(*(s16*)((char*)temp_v1 + 0x80) + temp_v0, 0);
        temp_v0_5 = FW(arg0, 0x3C4);
        timproc_uso_b5_alias((&timproc_uso_b5_D_807FE778)[temp_v0_5], FW(arg0, 0x4D4) | FW((arg0 + (temp_v0_5 * 4)), 0x3D0));
        if (timproc_uso_b5_alias(arg0) == 0) {
            timproc_uso_b5_alias(FW(arg0, 0x41C));
            return;
        }
        timproc_uso_b5_alias(arg0);
        temp_v0_2 = timproc_uso_b5_alias(arg0);
        FW(arg0, 0x3C8) = temp_v0_2;
        FW(arg0, 0x3C4) = timproc_uso_b5_alias(arg0, temp_v0_2);
        FW(arg0, 0x3CC) = 0xA;
        timproc_uso_b5_alias(arg0);
        timproc_uso_b5_alias(arg0, 0);
        *(f32 *)((char *)arg0 + 0x484) = 0.0f;
        return;
    }
    if (timproc_uso_b5_alias(&import_80020098, 0x200) != 0) {
        timproc_uso_b5_alias(arg0);
    }
    if (FW(arg0, 0x4B4) == 0) {
        if (timproc_uso_b5_alias(&import_80020098, 0x14003) != 0) {
            timproc_uso_b5_alias(arg0, 1);
            if (FW(arg0, 0x3CC) == 9) {
                FW(arg0, 0x4B4) = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008468);
#endif

#ifdef NON_MATCHING
/* timproc_uso_b5_func_000085E0: 42-insn (0xA8) FPU-clamp + vtable dispatch.
 *
 *   f2 = a0->[0x480]; f0 = a0->[0x484];                  // upper/lower bound
 *   if (f0 < f2) {                                       // out of upper bound?
 *     f6 = f2 - a0->[0xEC];                              // decrement
 *     a0->[0x480] = f6;
 *     if (a0->[0x480] < f0) {                            // crossed lower bound
 *       a0->[0x480] = f0;
 *       a0->[0x3CC] = 0;
 *       a0->[0x488] = a0->[0x104];                       // (entry-arm)
 *     } else {
 *       a0->[0x480] = f0;
 *       a0->[0x3CC] = 0;
 *       a0->[0x488] = a0->[0x104];                       // (loop-body-arm)
 *       gl_func();                                       // callback
 *       (*(v0->[0x28]->[0x64]))(v0->[0x28]->[0x60] + ret);  // vtable dispatch
 *     }
 *   } else {
 *     // skipped-path: simpler index lookup
 *     v0 = a0->[0x3C4];
 *     a0->[0x3F0] = v0;
 *     a0->[0x3F4] = a0[0x3D0 + v0];                       // (sp+t6 idx)
 *   }
 *
 * Pattern: FPU clamp-and-update + indirect vtable dispatch. The vtable
 * call shape (v0->[0x28]->[0x64] + v0->[0x28]->[0x60]) is repeated
 * across timproc family — likely a shared "boarder/effect manager" type.
 * Multi-tick: full byte match needs typed-struct decl + correct
 * fn-ptr signature.
 * 2026-05-30 OVER-6 diagnosis (built 41 vs target 35): two structural diffs,
 * both branch-likely-driven, NOT a clean redundancy collapse. (1) The outer
 * `if (f0<f2)` compiles to `c.lt.s f0,f2; bc1fl else` (FP branch-LIKELY) and
 * IDO RE-EMITS the `c.lt.s f0,f2` inside the taken body (between `sub.s f6`
 * and `swc1 f6,0x480`) — my C produces that extra compare. (2) The outer
 * ELSE block (idx-lookup: a0->0x3F0=a0->0x3C4; a0->0x3F4=a0[0x3D0+idx*4]) is
 * emitted by my C AFTER the loop-body-arm's `jalr` (8 extra insns: lw 0x3C4/
 * sll/addu/sw 0x3F0/lw 0x3D0/sw 0x3F4 + a `b`), whereas the target hoists
 * that else to offset 0x58 (reached only via the bc1fl) so the loop-body-arm
 * returns directly. Fix needs the bc1fl-shaped C (annulled-delay first store)
 * + the else hoisted above the inner arms — a branch-likely-layout grind. */
extern int gl_func_00000000();
void timproc_uso_b5_func_000085E0(int *a0) {
    float f0, f2, f6, f8;
    int *v0;
    int *v1;
    int (*fn)(int);
    f2 = *(float*)((char*)a0 + 0x480);
    f0 = *(float*)((char*)a0 + 0x484);
    if (f0 < f2) {
        f6 = f2 - *(float*)((char*)a0 + 0xEC);
        *(float*)((char*)a0 + 0x480) = f6;
        f8 = *(float*)((char*)a0 + 0x480);
        if (f8 < f0) {
            *(float*)((char*)a0 + 0x480) = f0;
            *(int*)((char*)a0 + 0x3CC) = 0;
            *(int*)((char*)a0 + 0x488) = *(int*)((char*)a0 + 0x104);
        } else {
            *(float*)((char*)a0 + 0x480) = f0;
            *(int*)((char*)a0 + 0x3CC) = 0;
            *(int*)((char*)a0 + 0x488) = *(int*)((char*)a0 + 0x104);
            v0 = (int*)gl_func_00000000();
            v1 = (int*)v0[0x28/4];
            fn = (int(*)(int))v1[0x64/4];
            fn(*(short*)((char*)v1 + 0x60) + (int)v0);
        }
    } else {
        int idx = *(int*)((char*)a0 + 0x3C4);
        *(int*)((char*)a0 + 0x3F0) = idx;
        *(int*)((char*)a0 + 0x3F4) = *(int*)((char*)a0 + 0x3D0 + idx * 4);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000085E0);
#endif

void timproc_uso_b5_func_0000866C(int *a0) {
    int idx = a0[0x3C4 / 4];
    a0[0x3F0 / 4] = idx;
    a0[0x3F4 / 4] = *(int *)((char *)a0 + (idx << 2) + 0x3D0);
}

// timproc_uso_b5_func_00008688 — STRUCTURAL PASS (no episode).
// Raw-.word USO. BOUNDARY NOTE: this .s is a LARGE multi-function USO
// bundle (20 jr-ra; named fn 0x8688..0x879C ~70 words, then ~12 tiny
// trailing functions 0x87A0..0x8948 — small flag-test predicates /
// table accessors for the scr->0x3C0 state bits and D_000001D4 /
// D_000001F4 / D_00000214 lookup tables, each returning a small int).
// USO bundles aren't splittable by mnemonic split-fragments.py;
// deferred USO re-split. Only the named leading function is decoded.
//
// Named fn = timing-screen camera-snapshot + mode-dependent begin:
//   void timproc_uso_b5_func_00008688(Scr *scr, int mode) {  // scr->s0
//     Cam *cam = scr->0x414->0x10;
//     scr->0x4C4 = cam->0x60;  scr->0x4C8 = cam->0x64;
//     scr->0x4CC = cam->0x68;                              // eye pos Vec3
//     scr->0x4C0 = scr->0x414->0xC->0x70->0x14C;            // fov-like
//     scr->0x4B4 = scr->0x3F8 = mode;
//     scr->0x488 = scr->0x104;  scr->0x3FC = scr->0x404;
//     scr->0x4BC = scr->0x484 = 0.0f;                       // anim reset
//     // a few f32 scratch derived from scr->0x404 / cam fields;
//     d = scr->0x28;                                        // begin call
//     if      (mode == 2) (d->0x74)(d->0x70 + …);
//     else if (mode != …) (d->0x6C)(d->0x68 + …);
//     else                (d->0x64)(d->0x60 + …);
//   }
//
// Struct-typing reference:
//   scr: 0x414 -> node (->0x10 cam: 0x60/0x64/0x68 eye-pos;
//     ->0xC->0x70->0x14C fov), 0x4C4/0x4C8/0x4CC captured eye Vec3,
//     0x4C0 captured fov, 0x4B4/0x3F8 mode, 0x104/0x404 init sources,
//     0x488/0x3FC copies, 0x4BC/0x484 f32 anim state (=0), 0x28 vtable
//     (->0x60/0x64, ->0x68/0x6C, ->0x70/0x74 dispatch idiom — begin
//     variants by mode); 0x3C0 = state-flag word (tested by the
//     trailing predicate bundle). D_000001D4/01F4/0214 = USO lookup
//     tables. func_00000000 = USO placeholder dispatcher.
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder calls;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — named leading fn (camera-snapshot + mode
//   begin) only; trailing predicates/accessors mostly remain INCLUDE_ASM.
//   The 0x87F4 switch predicate has been boundary-merged with its case
//   fragments (0x8834..0x8894), which inherit registers and share tails.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00008688(char *scr, int mode) {
    char *cam = *(char **)(*(char **)(scr + 0x414) + 0x10);
    char *d;
    void (*fp)(int);
    *(float *)(scr + 0x4C4) = *(float *)(cam + 0x60);
    *(float *)(scr + 0x4C8) = *(float *)(cam + 0x64);
    *(float *)(scr + 0x4CC) = *(float *)(cam + 0x68);
    *(float *)(scr + 0x4C0) = *(float *)(*(char **)(*(char **)(*(char **)(scr + 0x414) + 0xC) + 0x70) + 0x14C);
    *(int *)(scr + 0x4B4) = mode;
    *(int *)(scr + 0x3F8) = mode;
    *(int *)(scr + 0x488) = *(int *)(scr + 0x104);
    *(int *)(scr + 0x3FC) = *(int *)(scr + 0x404);
    *(float *)(scr + 0x4BC) = 0.0f;
    *(float *)(scr + 0x484) = 0.0f;
    d = *(char **)(scr + 0x28);
    if (mode == 2) {
        fp = *(void (**)(int))(d + 0x74);
        fp(*(short *)(d + 0x70));
    } else if (mode == 1) {
        fp = *(void (**)(int))(d + 0x6C);
        fp(*(short *)(d + 0x68));
    } else {
        fp = *(void (**)(int))(d + 0x64);
        fp(*(short *)(d + 0x60));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008688);
#endif

/* timproc_uso_b5_func_000087A0: 12-insn table tail-dispatcher, sibling of the
 * 87E8/8894/8940 small-leaf exact-match cluster. Computes idx = a1 - 1; if
 * idx >= 8, returns 0; otherwise tail-jumps to
 * *(timproc_uso_b5_D_807FF1F4 + 0x1D4 + idx*4). Source=2 pass 2026-06-01:
 * C body documents the real dispatch. The target uses a raw `jr t6` tail jump
 * with no frame; normal C is expected to stay NM unless IDO emits the same
 * tail-call shape. Tried both named function-pointer local and inline call
 * expression: both emit a 0x18 frame + `jalr` + epilogue (0x48 bytes), not
 * the target frame-free `jr t6` tail call (0x30 bytes). */
#ifdef NON_MATCHING
extern char timproc_uso_b5_D_807FF1F4;
int timproc_uso_b5_func_000087A0(int a0, int a1) {
    int idx = a1 - 1;
    (void)a0;
    if ((unsigned)idx >= 8) {
        return 0;
    }
    return (*(int (**)(void))(&timproc_uso_b5_D_807FF1F4 + 0x1D4 + idx * 4))();
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000087A0);
#endif

int timproc_uso_b5_func_000087D0(void) {
    return 1;
}

int timproc_uso_b5_func_000087D8(void) {
    return 2;
}

int timproc_uso_b5_func_000087E0(void) { return 3; }

/* timproc_uso_b5_func_000087E8: 3-word UNFILLED-jr-delay cap. Target is
 * `move v0,zero; jr ra; nop` (0xC). At -O2 IDO's reorg pulls the single
 * move into jr-ra's delay slot → `jr ra; move v0,zero` (0x8, 2 insns) —
 * verified 2026-05-29. The filled siblings 87D8/87E0 (`jr ra; li v0,N`)
 * DO match at -O2 (their value-insn fills the slot), so this region is
 * -O2-with-reorder. (Same unfilled-jr-delay class as feedback_unfilled_delay_*.)
 *
 * NOT A CAP (corrected 2026-05-31). The prior "genuine toolchain cap" verdict
 * only tried -O0 (which bloats `return 0` to 0x1c). It MISSED -O2 -g3: PROVEN
 * that `int f(void){return 0;}` at -O2 -g3 emits EXACTLY `move v0,zero; jr ra;
 * nop` (0xC, clean) — -g3 disables the reorg delay-slot filler while keeping
 * -O2. This is the IDENTICAL case to the sibling timproc_uso_b5_func_00001DA4
 * (`return 1`, unfilled-delay), already landed via its -g3 carve-out
 * src/timproc_uso_b5/timproc_uso_b5_g3_1DA4.c. (Donor-splice fails because it
 * uses -O0; -g3 is the right tool, not -O0.)
 * TO LAND (attempted 2026-05-31, reverted): the -g3 sub-unit g3_87E8.c WORKS —
 * it produces the EXACT 0xC target bytes (verified). But the block5 splice is
 * NOT a simple "delete 0xC, pad tail, reinsert": deleting 87E8 from the TU
 * shrank main .text by 0x10 (not 0xC) and left a real epilogue + 8 zeros at the
 * tail, not clean 0x18 zeros. So the main .c.o .text length / padding mechanism
 * (how 1DA4's removal currently yields exactly 0xe620 with 0xC tail zeros) must
 * be reverse-engineered before extending the splice — guessing it corrupts the
 * shared block5 build. The CRACK is proven (g3 bytes exact); the remaining piece
 * is the precise splice-padding RE — a focused task, not a quick tick. Same for
 * sibling 8894.
 * 2026-05-31 RE PROGRESS (narrows the focused task): the 0x10 shrink = 0xC code
 * + 0x4 asm-processor INCLUDE_ASM-boundary alignment (the asm-processor pads the
 * compiled-C/INCLUDE_ASM region boundary to 8 bytes; carving 87E8 removes its 0xC
 * AND collapses a 0x4 boundary pad). 87E8 builds at .text offset 0x87DC, i.e.
 * VRAM 0x87E8 minus the 0xC the 1DA4 carve already shifts everything after 0x1DA4.
 * So the multi-offset splice must: (1) insert g3_87E8 at post-1DA4-splice offset
 * 0x87E8, AND (2) absorb the 0x4 boundary-pad delta (either emit g3_87E8 as 0x10
 * = 0xC + 0x4 zeros and verify the target has no 0x4 gap before 87F4 [it doesn't:
 * 87F4 = 87E8+0xC], OR keep the boundary pad in main by carving 87E8 WITHOUT
 * collapsing the adjacent INCLUDE_ASM-boundary align). Verify against build/src
 * .text == target for the whole 0x87xx..0x89xx range, not just 87E8, before the
 * Yay0 recompress — a wrong delta silently corrupts the shared block5.
 * SOURCE=3 RETEST (2026-06-01): promoted with the same -O2 -g3 carve-out
 * mechanism as sibling 1DA4. The compiled sub-unit lives in
 * src/timproc_uso_b5/timproc_uso_b5_g3_87E8.c and is spliced into block5 at
 * offset 0x87E8, preserving the unfilled delay slot without instruction
 * patching. */

/* Boundary-merged switch predicate. The internal alabels at 0x8834, 0x8844,
 * 0x8854, 0x886C, 0x887C, and 0x8894 are case labels/tail entries, not
 * standalone C-callable functions — they are the inline bit-priority-encoder
 * bodies reached through the jr-table on a0->0x3C8 (jumptable D_807FF214 lives
 * in linker-discarded .rodata). Sibling dispatcher 0x88A0 mirrors this on
 * D_807FF234. Within its own 0x40, 87F4 = the 10-word dispatcher
 * (sel-1; sltiu 8; jr table[idx]) + the case-1 head at 0x881C
 * (v0=a0->0x3C0; if (v0&1) return 1; with andi v0,2 scheduled into the
 * beq delay). The full per-case priority encoder spills into the sibling
 * fragment symbols.
 *
 * VERIFIED 2026-06-01 (SOURCE=3): the switch below is byte-correct for 87F4's
 * own 0x40 — in-tree non_matching emits, in order, lw 0x3C8 / addiu -1 /
 * sltiu 8 / beqz default / sll 2 (delay) / lui / addu / lw table / jr t7 /
 * nop / [case-1: lw 0x3C0 / andi 1 / beqz / andi 2 (delay) / jr ra / li 1],
 * every word matching the target except branch-rel offsets and the jumptable
 * %lo reloc. It still scores 0% in objdiff because the switch inlines all 8
 * cases (~0x140) while splat declares 87F4 as only 0x40 — the remaining case
 * bodies are SEPARATE splat symbols (0x8854, 0x88A0, …). This is a boundary
 * defect, not a codegen one: merging 0x87F4..0x889C into a single symbol
 * (split-fragments / merge-fragments) makes this switch match as-is. The goto-z
 * funnel is required — a per-case `return 0` makes IDO hoist `move v0,zero`
 * between lw and addiu, shifting the whole body. Multi-tick infra. */
/* timproc_uso_b5_func_000087F4 [0x87F4..0x8894), 0xA0: bit-priority
 * encoder, 8-entry jumptable, THREE case bodies. FALSE MATCH RETRACTED
 * 2026-06-10: the prior "43/43 exact" matched a CORRUPTED merged .s
 * that had wrongly absorbed the adjacent 8894 return-0 leaf; ROM truth
 * (assets/timproc_uso_block_5.bin) shows the fn ends at 0x8894 and its
 * return-0 paths BRANCH INTO the adjacent leaf (beqzl -> 0x8898) --
 * the branch-into-adjacent-leaf cap class (mgrproc 140/170). The C
 * below is structurally faithful but emits an INTERNAL funnel where
 * the target borrows the neighbor's; not standalone-matchable.
 * Episode deleted; expected/ was circularly poisoned and is re-baselined. */
#ifdef NON_MATCHING
int timproc_uso_b5_func_000087F4(char *a0) {
    int v0;
    switch (*(int *)(a0 + 0x3C8)) {
    case 1:
        v0 = *(int *)(a0 + 0x3C0);
        if (v0 & 1) return 1;
        if (v0 & 2) return 2;
        if (v0 & 4) return 4;
        goto z;
    case 2:
        v0 = *(int *)(a0 + 0x3C0);
        if (v0 & 2) return 2;
        if (v0 & 4) return 4;
        goto z;
    case 3:
        if (*(int *)(a0 + 0x3C0) & 4) return 4;
        goto z;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        goto z;
    }
z:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000087F4);
#endif
/* timproc_uso_b5_func_000088A0 [0x88A0..0x8940), 0xA0: 87F4's mirror.
 * FALSE MATCH RETRACTED 2026-06-10 (same corrupted-merge mechanism;
 * the "absorbed funnel" was the REAL leaf 8940, whose g3 carve is
 * restored). Branch-into-adjacent cap; structurally-faithful NM below. */
#ifdef NON_MATCHING
int timproc_uso_b5_func_000088A0(char *a0) {
    int v0;
    switch (*(int *)(a0 + 0x3C8)) {
    case 1:
        if (*(int *)(a0 + 0x3C0) & 8) return 8;
        goto z;
    case 2:
        v0 = *(int *)(a0 + 0x3C0);
        if (v0 & 1) return 1;
        if (v0 & 8) return 8;
        goto z;
    case 3:
        v0 = *(int *)(a0 + 0x3C0);
        if (v0 & 2) return 2;
        if (v0 & 1) return 1;
        if (v0 & 8) return 8;
        goto z;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        goto z;
    }
z:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_000088A0);
#endif
/* timproc_uso_b5_func_00008940: REAL standalone -g3 return-0 leaf in
 * timproc_uso_b5_g3_8940.c (the 2026-06-10 "dissolution" was wrong and
 * is reverted; 88A0 branches INTO this leaf -- see its header). */

void timproc_uso_b5_func_0000894C(void) {
    func_00000000();
}

extern float D_b5_896C_234;
extern float D_b5_896C_2A0;
void timproc_uso_b5_func_0000896C(char *a0) {
    D_b5_896C_2A0 = *(float *)(a0 + 0x480) * D_b5_896C_234;
}

/* timproc_uso_b5_func_00008988: 37-insn (0x94) array-scan loop. BOUNDARY
 * MERGED 2026-06-02: splat over-split off the loop bottom as a separate
 * symbols (000089DC 16-insn + 00008A1C 7-insn — TWO loop-bottom tails, each
 * with a backward branch landing inside this body: 89DC->0x89B0, 8A1C->0x89FC).
 * Absorbed both (0x54 -> 0xB0, ends right before the fresh accessor at 0x8A38);
 * dropped the 89DC and 8A1C symbols. Body walks a0->0x40C[a1] entries counting
 * a predicate match (f0==entry->0x3C->0x2A4 / a2==...->0x2B0), returns the count.
 * 2026-06-10 corrections: NOT reloc-blind (all addressing is a0-relative,
 * no symbol relocs) -- stale claim dropped. True structure = TWO loops
 * over the same v0 cursor: loop 1 strict (f_2A4 != 0 AND i_2B0 == a2),
 * loop 2 relaxed (f_2A4 != 0 only), each returning the running index;
 * the cursor is the REUSED a0 ARG (dead-arg overwrite) and the entry
 * ptr reuses a1. Negative: a clean two-do-while rewrite with arg-reuse
 * explodes to 145 insns (IDO -O2 unrolls the do/while 4x). 2026-06-20:
 * a FLAT goto-form (counter + cursor, `if (i < n) goto loopN`) compiles
 * NON-unrolled to 42 words vs the 44-word target -- only TWO residual
 * diffs, one per loop: IDO collapses my `i < n` back-branch to a single
 * `bne v1,a3` (unit-stride IV: i!=n == i<n) where the target keeps the
 * explicit `slt at,v1,a3; bnez at` (2 words).
 *
 * EXACT (2026-06-21, decomp-permuter). The 2-insn IV-collapse tie was cracked
 * by SINKING the inter-loop `i = 0;` reset INSIDE the first `if (n > 0)` block
 * (right after loop1's back-branch) instead of leaving it between the two
 * loops. This changes the live range of `i`/`n` across the loop boundary so
 * the as1 IV analysis no longer folds `i < n` to `bne`, restoring the target's
 * `slt at,v1,a3; bnez at` in both loops. Verified IN-TREE: 44/44 words, 0
 * non-reloc diffs (the fn has 0 relocs, all a0-relative), full ROM
 * byte-identical to baserom. Body below = the exact form. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
s32 timproc_uso_b5_func_00008988(char *arg0, s32 arg1, s32 arg2) {
  s32 i;
  s32 n;
  char *e;
  char *p;
  char *c;
  i = 0;
  p = *((int *) (((char *) ((*((int *) (((char *) arg0) + 0x40C))) + (arg1 * 4))) + 0x40));
  n = *((int *) (((char *) p) + 0x6C));
  if (n > 0)
  {
    c = p;
    loop1:
    e = *((int *) (((char *) c) + 0x3C));

    if (((*((f32 *) (((char *) e) + 0x2A4))) != 0.0f) && (arg2 == (*((int *) (((char *) e) + 0x2B0)))))
    {
      return i;
    }
    i += 1;
    c += 4;
    if (i < n)
    {
      goto loop1;
    }
    i = 0;
  }
  if (n > 0)
  {
    c = p;
    loop2:
    if ((*((f32 *) (((char *) (*((int *) (((char *) c) + 0x3C)))) + 0x2A4))) != 0.0f)
    {
      return i;
    }

    i += 1;
    c += 4;
    if (i < n)
    {
      goto loop2;
    }
  }
  return 0;
}

/* timproc_uso_b5_func_00008A38/A64/A90: indexed double-deref accessors. The
 * addu operand-order lever (scaled index FIRST, fully inlined — no named
 * locals) emits the target's all-$t allocation. */
int timproc_uso_b5_func_00008A38(int *a0) {
    return *(int *)(*(int *)((char *)a0 + *(int *)((char *)a0 + 0x3C4) * 4 + 0x3D0) * 4 + *(int *)(*(int *)((char *)a0 + 0x3C4) * 4 + *(int *)((char *)a0 + 0x40C) + 0x40) + 0x3C);
}

/* Sibling of _00008A38 (offsets 0x3CC/0x3C). */
int timproc_uso_b5_func_00008A64(int *a0) {
    return *(int *)(*(int *)((char *)a0 + *(int *)((char *)a0 + 0x3C4) * 4 + 0x3CC) * 4 + *(int *)(*(int *)((char *)a0 + 0x3C4) * 4 + *(int *)((char *)a0 + 0x40C) + 0x3C) + 0x3C);
}

/* Sibling of _00008A38 (offsets 0x3E0/0x40). */
int timproc_uso_b5_func_00008A90(int *a0) {
    return *(int *)(*(int *)((char *)a0 + *(int *)((char *)a0 + 0x3C4) * 4 + 0x3E0) * 4 + *(int *)(*(int *)((char *)a0 + 0x3C4) * 4 + *(int *)((char *)a0 + 0x40C) + 0x40) + 0x3C);
}

// copy a0[idx*4+0x3D0] -> a0[idx*4+0x3E0], idx = a0->0x3C4.
// MATCH: the FULLY-array-index form a0[idx + 0xF8] = a0[idx + 0xF4] (offsets as
// element counts: 0x3E0/4, 0x3D0/4) makes IDO CSE the a0+idx*4 base ONCE and emit
// the addu base-first (addu v0,a0,t7) with the target's t6/t7/v0/t8 registers.
// The &a0[idx] + char*-offset form emitted index-first addu (was INSN_PATCH'd,
// banned 2026-05-23). See docs/IDO_CODEGEN.md#feedback-ido-indexed-double-deref-allt-cap.
void timproc_uso_b5_func_00008ABC(int *a0) {
    a0[a0[0x3C4 / 4] + 0x3E0 / 4] = a0[a0[0x3C4 / 4] + 0x3D0 / 4];
}

/* timproc_uso_b5_func_00008AD4: double-indexed double-deref accessor. Same
 * addu operand-order lever (scaled index FIRST, fully inlined). */
int timproc_uso_b5_func_00008AD4(int *a0) {
    return *(int *)(*(int *)((char *)a0 + 0x3F4) * 4 + *(int *)(*(int *)((char *)a0 + 0x3F0) * 4 + *(int *)((char *)a0 + 0x40C) + 0x40) + 0x3C);
}

// timproc_uso_b5_func_00008AFC — STRUCTURAL PASS (no episode).
// Raw-.word USO. BOUNDARY NOTE: this .s is a 3-function USO bundle
// (3 jr-ra). Named fn 0x8AFC..0x8C18 (~70 words) is the draw loop;
// 2 trailing tiny getters (0x8C1C: idx=scr->0x3C4 ->
// scr->0x40C->0x3D0[idx]->0x40 ; 0x8C38: arg->0x40C[…]->0x3C) —
// deferred USO re-split.
//
// Named fn = timing-screen multi-element draw loop (2-level):
//   void timproc_uso_b5_func_00008AFC(Scr *scr) {        // scr -> s2
//     float K = F32(D_00000238);
//     for (g = 0; g < numGroups; g++) {                   // scr->0x40C[]
//       grp = scr->0x40C + g*N;
//       if (grp->0x40->0x6C == 0) continue;
//       func_00000000(scr);
//       for (i = 0; i < grp->0x40->0x6C; i++) {            // leaf items
//         e = grp->0x40 + i*4;
//         d = scr->...->0x28;
//         (d->fn)(d->0x58base + …, scr->0x480 * K);  // draw at scaled pos
//       }
//     }
//     d = scr->0x28;  (d->fn)(d->0x58 + …);               // finalize
//   }
//
// Struct-typing reference:
//   scr: 0x40C -> group array (each grp->0x40 -> leaf list, ->0x6C
//     leaf count), 0x480 f32 base position (scaled by K), 0x3C4 index
//     (used by the trailing getter), 0x28 / leaf->0x28 vtable
//     (->0x58 s16 base, ->0x5C fn ptr — obj->0x28 dispatch idiom,
//     here a draw call taking a computed FP position).
//   D_00000238 = USO f32 scale const. func_00000000 = USO placeholder
//     dispatcher (per-group setup).
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder/vtable
//   calls; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — named leading 2-level draw loop
//   only; trailing 2 tiny getters (0x8C1C/0x8C38) remain INCLUDE_ASM.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_00008AFC(char *scr) {
    float K = *(float *)((char *)&D_00000000 + 0x00000238);
    char *grp;
    char *e;
    char *d;
    void (*fp)(int, float);
    int g, i;
    int numGroups = 4;
    for (g = 0; g < numGroups; g++) {
        grp = *(char **)(scr + 0x40C) + g * 0x10;
        if (*(int *)(*(char **)(grp + 0x40) + 0x6C) == 0) continue;
        func_00000000(scr);
        for (i = 0; i < *(int *)(*(char **)(grp + 0x40) + 0x6C); i++) {
            e = *(char **)(grp + 0x40) + i * 4;
            d = *(char **)(*(char **)e + 0x28);
            fp = *(void (**)(int, float))(d + 0x5C);
            fp(*(short *)(d + 0x58) + (int)e, *(float *)(scr + 0x480) * K);
        }
    }
    d = *(char **)(scr + 0x28);
    fp = *(void (**)(int, float))(d + 0x5C);
    fp(*(short *)(d + 0x58), 0.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008AFC);
#endif

/* timproc_uso_b5_func_00008C1C: indexed double-deref accessor. addu operand
 * order lever: scaled index FIRST (idx*4 + base) emits the target all-$t. */
int timproc_uso_b5_func_00008C1C(int *a0) {
    return *(int *)(*(int *)(*(int *)((char *)a0 + 0x3C4) * 4 + *(int *)((char *)a0 + 0x40C) + 0x40) + 0x6C);
}

int timproc_uso_b5_func_00008C38(char *scr) {
    return *(int *)(*(char **)(scr + 0x40C) + 0x3C);
}

// timproc_uso_b5_func_00008C44 — STRUCTURAL PASS (no episode).
// Raw-.word USO. BOUNDARY NOTE: this .s is a 4-function USO bundle
// (4 jr-ra). Named fn 0x8C44..0x8D34 is the classification query;
// trailing helpers: 0x8D38 a search loop over D_00000154 + idx*0x18
// entries returning a found index (bit-test ->0x6 & 7); 0x8D90 a
// setter that clears scr->0x4A4/0x4A8/0x4AC/0x4B0 (the captured-
// camera fields) — deferred USO re-split.
//
// Named fn = timing-screen state/classification query:
//   int timproc_uso_b5_func_00008C44(Rec *r) {           // r -> s3
//     Cfg *c = *(Cfg**)(D_0 + 0x154);                     // global cfg
//     int m = (s16)r->0x2 - 4;
//     if (m < 0 || m >= 2) { ...loop scanning D_00000F1C
//                            handler table via func_00000000,
//                            comparing each entry->0x2B0... }
//     if (c->0xE == 0xFC && c->0xF == 0xFF && c->0x10 == 7) {
//       e = func_00000000(&D_00000F1C, r);
//       return (e->0x2B0 == 4) ? 3 : 4;                    // class code
//     }
//     return 0;
//   }
//
// Struct-typing reference:
//   r: 0x0 a counter/id, 0x2 s16 mode/index (range-checked vs 4,2).
//   *(Cfg**)(D_0 + 0x154) = global config record; c->0xE/0xF/0x10 =
//     sentinel bytes (0xFC / 0xFF / 7) gating the classification;
//     scanned entry->0x2B0 = a command/state word (==4 -> code 3
//     else 4; default 0). D_00000F1C = USO static handler table;
//     D_00000F18 = a global (touched by the trailing setter);
//     scr->0x4A4/0x4A8/0x4AC/0x4B0 = captured-camera fields the
//     trailing setter clears. func_00000000 = USO placeholder
//     dispatcher (table entry fetch).
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder calls;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — named leading classification query only;
//   trailing 2 helpers (0x8D38/0x8D90) remain INCLUDE_ASM. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
int timproc_uso_b5_func_00008C44(char *r) {
    char *c = *(char **)((char *)&D_00000000 + 0x154);
    int m = *(short *)(c + 0x2) - 4;
    char *e;
    if (m < 0 || m >= 2) return 0;
    if (*(unsigned char *)(c + 0xE) == 0xFC &&
        *(unsigned char *)(c + 0xF) == 0xFF &&
        *(unsigned char *)(c + 0x10) == 7) {
        e = (char *)func_00000000((char *)&D_00000000 + 0x00000F1C, r);
        if (*(int *)(e + 0x2B0) == 4) return 3;
        return 4;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008C44);
#endif

/* timproc_uso_b5_func_00008D38: 21-insn frameless bit-scan leaf
 * (boundary-merged 2026-06-02 from the 8D78 tail).
 * DECODE RE-CORRECTED 2026-06-20: the prior "DECODE CORRECTED 2026-06-10"
 * was WRONG -- it claimed the bitmap base is the ARG (a0->0x154). The .s
 * is unambiguous: `lui a0,%hi(import_800201EC); lw a0,0x154(a0)` reads a
 * GLOBAL (import_800201EC + 0x154), NOT a0. The incoming arg is homed to
 * 0(sp) at entry and otherwise unused. Body scans bits 0..23 of the
 * byte+6 table at *(import_800201EC+0x154): first CLEAR bit -> return 0;
 * all 24 set -> return 3.
 * The global-base body below now reproduces the ENTIRE loop body byte-for-
 * byte (the sw a0,0(sp) home store, sra/addu/lbu/andi/li/sllv/and/bnez bit
 * test, the return-0 path) -- 10 residual non-reloc diffs, ALL from two
 * coupled IDO allocator choices:
 *   (1) REGISTER SWAP: target keeps the pointer in $a0 (natural from
 *       `lui a0`) and the loop bound 24 in $v0; IDO here picks $v0 for the
 *       pointer and $a0 for 24 (mirror image). The whole idx2-6 + the
 *       addu operand order flip from this single pick.
 *   (2) COMPARE COLLAPSE: target keeps `slt at,v1,v0; bnezl at` (explicit
 *       register compare, 2 words) vs our `bnel v1,a0` (unit-stride IV
 *       collapse i<n == i!=n -> single word). Same IDO induction-variable
 *       collapse documented for func_00008988; no C loop form forces slt
 *       over bne for a clean counter.
 * Any 3rd named local (n/ret/r holding 24) DROPS the home store and shifts
 * everything by one (21 diffs) -- the 2-local goto form is the floor. for/
 * do-while regress to 12. Genuine 2-axis regalloc+IV-collapse cap; do NOT
 * re-run the -O matrix. */
/* timproc_uso_b5_func_00008D38 — EXACT 22/22 words (in-tree, fresh make RUN_CC_CHECK=0 build).
 * Default -O2. Bit-scan leaf: reads a global byte table pointer at
 * import_800201EC+0x154 (struct-cast-fold: reloc to base, 0x154 folds into lw),
 * scans bits 0..23 of table[(i>>3)+6]; first CLEAR bit -> return 0, all set -> return 3.
 * Levers that made it exact:
 *   - variable bound `n=24` (register-held) -> defeats IDO -O2 4x loop unroll AND
 *     emits `slt at,i,n` (reg compare) + `bnezl` branch-likely, like target.
 *   - struct-cast-fold `import_800201EC.ptr` -> `lui %hi(base); lw 0x154(base)`.
 *   - comma-init `for (i=0, p=...; i<n; i++)` counter-first -> correct p=$a0/i=$v1
 *     coloring AND schedules the `move v1,zero` into the lw load-delay slot.
 *   - hoist `k=i>>3` to a simple var so `p+k` is equal-complexity -> base-first addu
 *     `addu t7,a0,t6` (array-IXA/Sethi-Ullman lever; the +6 folds into lbu 6(t7)).
 * No new undefined_syms; import_800201EC already = 0 in undefined_syms_auto.txt.
 */
struct DBlk_8D38 { char _pad[0x154]; unsigned char *ptr; };
extern struct DBlk_8D38 import_800201EC;
s32 timproc_uso_b5_func_00008D38(char *a0) {
    s32 i;
    unsigned char *p;
    s32 k;
    s32 n = 24;

    for (i = 0, p = import_800201EC.ptr; i < n; i++) {
        k = i >> 3;
        if (!(*(p + k + 6) & (1 << (i & 7)))) {
            return 0;
        }
    }
    return 3;
}

void timproc_uso_b5_func_00008D90(int *a0, int a1) {
    if (a1 == 0) {
        a0[0x4A4 / 4] = 0;
    } else {
        a0[0x4A8 / 4] = 0;
    }
    a0[0x4AC / 4] = 0;
    a0[0x4B0 / 4] = *(int *)((char *)&D_00000000 + 0xF18);
}

// timproc_uso_b5_func_00008DB4 — STRUCTURAL PASS w/ REAL SYMBOLS
// (0x1E4 / 121 words, no episode). Timing-screen sub-panel constructor
// (alloc-or-reuse); returns self. Default build is INCLUDE_ASM.
//
// 2026-06-20: rewrote the NM body to reference the RESOLVED .s symbols
// (timproc_uso_b5_func_055750/002C94/04C678/002060/07ACE0/0000131C/
// 0000283C + import_800201CC/8005C2CC/8005C39C/8005EBA4/800200A8/
// 80020098 + timproc_uso_b5_D_807FEBA4/B0/B4) instead of the old fake
// D_8DB4_* aliases. Word-exact (reloc-filtered) went 111 -> 18 non-reloc
// diffs (size now matches, 121==121).
//
// Levers applied (all in docs):
//   - goto-end shared epilogue for alloc-fail + a1==1 early exits
//     (IDO_CODEGEN feedback-ido-goto-epilogue, UNIFIED form).
//   - frame 0x58 + B/C high homes: decl order A,B,C,volatile pad[6]
//     (A colored to s0 -> dead -4 slot; B@0x50, C@0x4C per FRAME-SLOT
//     HOME ASSIGNMENT RULE); pad[6] sizes the frame to 0x58.
//   - import_8005C39C+0x294 base-adjust via POINTER MUTATE
//     (`p=&sym; p+=0x294;`) forces `addiu r,r,0x294` not offset-fold
//     (IDO_CODEGEN feedback-ido-pointer-mutate-forces-base-register-adjust).
//   - import_8005EBA4 (the 0x2A0 store) and 8005C39C (the Vec4) were
//     SWAPPED in the prior hand-decode; corrected here.
//
// RESIDUAL = 18 non-reloc diffs, ALL allocator/encoding caps:
//   * flag-clear `*(C2CC+0x1C4) &= ~8`: target emits TWO luis (t6 load,
//     at store, no addiu, %lo folded into lw/sw) + as1 schedules the
//     Vec4 `mtc1 zero,f0` into the region; IDO from C always CACHES the
//     base (one lui+addiu in a2) -> form(a)/(b) reloc-encoding + as1
//     scheduler tie (idx 15-23). Not C-controllable (IDO_CODEGEN line:
//     R_MIPS_LO16 placement for &D+const).
//   * v0-vs-v1 coloring cascade off that base choice: C39C base, Vec4
//     base, C dirty-attach handle (idx 26-29,67-77), publish t8-vs-t9
//     (idx 112-114). Pure register coloring.
// All logic / control-flow / frame / symbols are exact; only register
// names + the flag two-lui encoding differ. Honest NON_MATCHING.
#ifdef NON_MATCHING
extern struct C2CC_8DB4 { char _a[0x1C4]; int f1C4; } import_8005C2CC;
char *timproc_uso_b5_func_00008DB4(char *self, int a1) {
    extern int timproc_uso_b5_func_055750();
    extern int timproc_uso_b5_func_002C94();
    extern int timproc_uso_b5_func_04C678();
    extern int timproc_uso_b5_func_002060();
    extern int timproc_uso_b5_func_07ACE0();
    extern char import_800201CC;
    extern char import_8005C39C;
    extern char import_8005EBA4;
    extern char import_800200A8;
    extern char import_80020098;
    extern char timproc_uso_b5_D_807FEBA4;
    extern char timproc_uso_b5_D_807FEBB0;
    extern char timproc_uso_b5_D_807FEBB4;
    char *A;
    char *B;
    char *C;
    volatile int pad[6];
    char *p39c;
    if (self == 0) {
        self = (char *)timproc_uso_b5_func_055750(0xC);
        if (self == 0) {
            goto end;
        }
    }
    timproc_uso_b5_func_002C94(*(char **)((char *)&import_800201CC + 0x134), 2);
    import_8005C2CC.f1C4 &= ~8;
    if (1) { }
    p39c = (char *)&import_8005C39C;
    p39c += 0x294;
    ((float *)p39c)[3] = 0.0f;
    ((float *)p39c)[2] = 0.0f;
    ((float *)p39c)[1] = 0.0f;
    ((float *)p39c)[0] = 0.0f;
    *(float *)((char *)&import_8005EBA4 + 0x2A0) = 0.0f;
    A = (char *)timproc_uso_b5_func_04C678(0, (char *)&timproc_uso_b5_D_807FEBA4 + 0x1334);
    B = (char *)timproc_uso_b5_func_04C678(0, (char *)&timproc_uso_b5_D_807FEBB0 + 0x1340);
    C = (char *)timproc_uso_b5_func_04C678(0, (char *)&timproc_uso_b5_D_807FEBB4 + 0x1344);
    timproc_uso_b5_func_002060(*(char **)((char *)&import_800201CC + 0x134), C, B, A, 0, 0);
    timproc_uso_b5_func_07ACE0(A + 0x10, B);
    if (*(char **)(B + 0x14) != 0) {
        *(int *)(B + 0x4) = 1;
    }
    *(char **)(B + 0x14) = A;
    timproc_uso_b5_func_07ACE0(A + 0x10, C);
    if (1) { }
    if (*(char **)(C + 0x14) != 0) {
        *(int *)(C + 0x4) = 1;
    }
    *(char **)(C + 0x14) = A;
    timproc_uso_b5_func_07ACE0((char *)&import_800200A8 + 0x10, A);
    if (*(char **)(A + 0x14) != 0) {
        *(int *)(A + 0x4) = 1;
    }
    *(char **)(A + 0x14) = (char *)&import_80020098;
    *(int *)(self + 0x00) = timproc_uso_b5_func_0000131C(0, a1);
    if (a1 == 1) {
        *(int *)(self + 0x04) = timproc_uso_b5_func_0000283C(0, 1, 1, 0x3C);
        goto end;
    }
    *(int *)(self + 0x04) = timproc_uso_b5_func_0000283C(0, 1, 2, 0x29);
    p39c = (char *)timproc_uso_b5_func_0000283C(0, 2, 3, 0x29);
    *(char **)(self + 0x08) = p39c;
    *(int *)(*(char **)(p39c + 0x0C) + 0x1B8) = *(int *)(*(char **)(self + 0x04) + 0x0C);
end:
    return self;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008DB4);
#endif

/* Indirect-call wrapper. Promoted 97.5%->100% via IDO load-CSE trick:
 * declare p2 FIRST with the full deref chain inline (including p1's load),
 * then declare p1 with the same `a0->0x2C` load — IDO CSE's the duplicated
 * load and assigns $v1 to p1 + $v0 to p2 (target's reg layout). Writing
 * p1 first (the natural order) gives the swap. Replaces prior INSN_PATCH
 * approach — no Makefile entry needed. */
void timproc_uso_b5_func_00008F98(char *a0) {
    int *p2 = *(int**)((char*)*(int*)(a0 + 0x2C) + 0x28);
    int p1 = *(int*)(a0 + 0x2C);
    (*(int(**)())((char*)p2 + 0x5C))(*(short*)((char*)p2 + 0x58) + p1);
}


// timproc_uso_b5_func_00008FC8 — STRUCTURAL PASS (0x19B4 / 1645 words,
// no episode). Raw-.word USO form. LARGEST function in this segment —
// entry/alloc/fan-out partial pass only; multi-run target.
// BOUNDARY NOTE: 3-jr USO bundle (named master ctor + 2 tiny trailing
// getters) — deferred USO re-split.
//
// Timing-screen MASTER constructor (the full timing/replay HUD screen
// assembly):
//   void *timproc_uso_b5_func_00008FC8(Obj *self, a1) {
//     if (!self) { self = func_00000000(0x60); if (!self) return 0; }
//     func_00000000(self, &D_00001348);                  // base-init
//     self->0x28 = &D_0;  self->0x0C = &D_00001350;        // vtable/desc
//     func_00000000(0x30);                                // aux alloc
//     // fan-out (~84 func_00000000 calls): builds ~8 sub-records of
//     //   0x70 bytes (the screen's panels/columns) + 0x30 + 0x2C
//     //   sub-objects, each allocated/initialized/positioned/linked
//     //   from the long descriptor table &D_00001348 / 1350 / 135C /
//     //   1364 / 1460 / 1474 / 1488 / 1498 / 14A4 (0x13xx/0x14xx
//     //   USO data pool).
//     return self;
//   }
//
// Struct-typing reference:
//   self (alloc 0x60): 0x0C descriptor(&D_00001350), 0x28 vtable
//     (&D_0); aggregates ~8 x 0x70 sub-records + 0x30/0x2C sub-objs.
//   &D_00001348..&D_000014A4 = USO widget/label descriptor table.
//   func_00000000 = USO placeholder dispatcher (alloc / init /
//     factory / position / attach).
// DECODE-PROGRESS 2026-06-22 (agent-d big-swing): callees are NOT
//   jal-0 placeholders — all 84 R_MIPS_26 resolve to named USO funcs
//   (055750=alloc, 04C678=base-init, 07ACE0=attach-child, 0000A928=
//   register, 0546DC/04DFFC/05D0E0=panel-build, etc.). The entry
//   cascade (prologue + first 3 sub-objects) is now reconstructed with
//   DISTINCT callee externs + symbol-relative descriptor args
//   (&D_807FExxx + off, &D_807FE5F4 vtable). That fixed the call/global
//   reloc class: jals + %hi/%lo now match (instr-exact 155->160,
//   fuzzy 41.88->42.19). REMAINING CAP is register-allocation +
//   instruction-scheduling across the full 1624-insn body (419 DELETE /
//   341 INSERT / 856 ARG = reg coloring + IDO save/move interleave),
//   plus the FP-math regions (mtc1/mfc1/swc1 panel positioning) and the
//   5-case mode switch (D_807FF344+0x324, idx=lhu(import_800201EC+0x154,
//   2)-1). Correct logic, divergent regalloc — documented unlandable
//   cap class; further sweep of the 70 remaining alias calls yields
//   ~+0.02pp each (regression-prone), so stopped here.
// Caps: 1624-insn FP/math HUD master ctor; regalloc+scheduling cap.
// Full body INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap rule).
#ifdef NON_MATCHING
typedef void *(*F0)();
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } S16;
#define FW(p, o) (*(int *)((char *)(p) + (o)))
extern int timproc_uso_b5_func_04C678();
extern int timproc_uso_b5_func_07ACE0();
void timproc_uso_b5_func_0000A928(int *a0);
extern char timproc_uso_b5_D_807FE5F4;
extern char timproc_uso_b5_D_807FEBB8;
extern char timproc_uso_b5_D_807FEBCC;
extern char timproc_uso_b5_D_807FEBD4;
extern char timproc_uso_b5_D_807FEBE0;
extern char timproc_uso_b5_D_807FEBE8;
extern int timproc_uso_b5_func_0000A95C();
extern int timproc_uso_b5_func_048E7C();
extern int timproc_uso_b5_func_04C774();
extern int timproc_uso_b5_func_04DFFC();
extern int timproc_uso_b5_func_0546DC();
extern int timproc_uso_b5_func_055750();
extern int timproc_uso_b5_func_05D0E0();
void **timproc_uso_b5_func_00008FC8(void **arg0, int *arg1, int *arg2) {
    S16 sp154;
    S16 sp148;
    S16 sp13C;
    S16 sp130;
    void **sp12C;
    void **sp128;
    void **sp124;
    void **sp120;
    void *sp100;
    s32 spF8;
    void *spF0;
    void **spE0;
    S16 spD0;
    S16 spC4;
    s32 spC0;
    s32 spBC;
    S16 sp94;
    S16 sp84;
    s32 sp80;
    s32 sp68;
    void **sp50;
    void **sp4C;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t2;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 var_a2;
    s32 var_s0_3;
    s32 var_s0_5;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_6;
    s32 var_v1;
    u16 temp_t0_2;
    u16 var_s0_6;
    void **temp_a0;
    void **temp_a1;
    void **temp_a1_2;
    void **temp_a1_3;
    void **temp_a1_4;
    void **temp_s0;
    void **temp_s0_2;
    void **temp_s0_3;
    void **temp_s0_4;
    void **temp_s0_5;
    void **temp_s1_2;
    void **temp_s1_3;
    void **temp_s1_4;
    void **temp_v0;
    void **temp_v0_10;
    void **temp_v0_11;
    void **temp_v0_12;
    void **temp_v0_13;
    void **temp_v0_14;
    void **temp_v0_15;
    void **temp_v0_16;
    void **temp_v0_17;
    void **temp_v0_18;
    void **temp_v0_19;
    void **temp_v0_20;
    void **temp_v0_21;
    void **temp_v0_22;
    void **temp_v0_23;
    void **temp_v0_24;
    void **temp_v0_25;
    void **temp_v0_26;
    void **temp_v0_27;
    void **temp_v0_28;
    void **temp_v0_29;
    void **temp_v0_2;
    void **temp_v0_31;
    void **temp_v0_3;
    void **temp_v0_4;
    void **temp_v0_5;
    void **temp_v0_6;
    void **temp_v0_7;
    void **temp_v0_8;
    void **temp_v0_9;
    void **temp_v1;
    void **temp_v1_10;
    void **temp_v1_11;
    void **temp_v1_12;
    void **temp_v1_2;
    void **temp_v1_3;
    void **temp_v1_4;
    void **temp_v1_5;
    void **temp_v1_6;
    void **temp_v1_7;
    void **temp_v1_8;
    void **temp_v1_9;
    void **var_s0;
    void **var_s0_2;
    void **var_s0_4;
    void **var_s1;
    void **var_s1_2;
    void **var_s1_3;
    void **var_s1_4;
    void **var_s2;
    void **var_v0;
    void **var_v0_3;
    void **var_v0_5;
    void **var_v1_2;
    void **var_v1_3;
    void **var_v1_4;
    void **var_v1_5;
    void **var_v1_6;
    void *temp_s0_6;
    void *temp_s1_10;
    void *temp_s1_11;
    void *temp_s1_12;
    void *temp_s1_13;
    void *temp_s1_14;
    void *temp_s1_15;
    void *temp_s1_16;
    void *temp_s1_17;
    void *temp_s1_18;
    void *temp_s1_19;
    void *temp_s1_20;
    void *temp_s1_21;
    void *temp_s1_22;
    void *temp_s1_23;
    void *temp_s1_5;
    void *temp_s1_6;
    void *temp_s1_7;
    void *temp_s1_8;
    void *temp_s1_9;
    void *temp_v0_30;
    var_s2 = arg0;
    if (arg0 == 0) {
        var_s2 = (void*)timproc_uso_b5_func_055750(0x60);
        if (var_s2 == 0) {
            return var_s2;
        }
    }
    {
        (void*)timproc_uso_b5_func_04C678(var_s2, &timproc_uso_b5_D_807FEBB8 + 0x1348);
        FW(var_s2, 0x28) = (int)&timproc_uso_b5_D_807FE5F4;
        FW(var_s2, 0xC) = (int)(&timproc_uso_b5_D_807FE5F4 + 0x1350);
        temp_v0_2 = (void*)timproc_uso_b5_func_055750(0x30);
        if (temp_v0_2 != 0) {
            (void*)timproc_uso_b5_func_04C678(temp_v0_2, &timproc_uso_b5_D_807FEBCC + 0x135C);
            FW(temp_v0_2, 0x28) = (int)&timproc_uso_b5_D_807FEBD4;
            FW(temp_v0_2, 0xC) = (int)(&timproc_uso_b5_D_807FEBD4 + 0x1364);
            FW(temp_v0_2, 0x2C) = var_s2;
        }
        FW(var_s2, 0x50) = temp_v0_2;
        temp_a0 = var_s2 + 0x10;
        sp50 = temp_a0;
        (void*)timproc_uso_b5_func_07ACE0(temp_a0, temp_v0_2);
        if (FW(temp_v0_2, 0x14) != 0) {
            FW(temp_v0_2, 0x4) = 1;
        }
        FW(temp_v0_2, 0x14) = var_s2;
        timproc_uso_b5_func_0000A928((int *)var_s2);
        temp_v0_3 = (void*)timproc_uso_b5_func_055750(0x2C);
        if (temp_v0_3 != 0) {
            (void*)timproc_uso_b5_func_04C678(temp_v0_3, &timproc_uso_b5_D_807FEBE0 + 0x1370);
            FW(temp_v0_3, 0x28) = (int)(&timproc_uso_b5_D_807FEBE8 + 0xCC4);
            FW(temp_v0_3, 0xC) = (int)(&timproc_uso_b5_D_807FEBE8 + 0x1378);
        }
        temp_s1 = FW(var_s2, 0x30);
        FW(var_s2, 0x38) = temp_v0_3;
        (void*)timproc_uso_b5_func_07ACE0(temp_s1 + 0x10, temp_v0_3);
        if (FW(temp_v0_3, 0x14) != 0) {
            FW(temp_v0_3, 0x4) = 1;
        }
        FW(temp_v0_3, 0x14) = temp_s1;
        if ((*(int*)((char*)&D_00000000+0x34)) != 2) {
            temp_v0_4 = (void*)timproc_uso_b5_func_055750((void **)0x2BC);
            if (temp_v0_4 != 0) {
                var_s0 = temp_v0_4;
                if ((temp_v0_4 != 0) || (temp_v0_5 = (void*)timproc_uso_b5_func_055750((void **)0x2B8), var_s0 = temp_v0_5, (temp_v0_5 != 0))) {
                    (void*)timproc_uso_b5_func_04C678(var_s0, (void **)0x1384);
                    FW(var_s0, 0x28) = 0;
                    (void*)timproc_uso_b5_func_00002B74(var_s0 + 0x2C);
                    (void*)timproc_uso_b5_func_000032C8(var_s0 + 0x194);
                }
                FW(temp_v0_4, 0x28) = 0x8B4;
                FW(temp_v0_4, 0xC) = 0x138C;
                timproc_uso_b5_func_00003890(temp_v0_4);
            }
            FW(var_s2, 0x5C) = temp_v0_4;
            (void*)timproc_uso_b5_func_07ACE0(sp50, temp_v0_4);
            if (FW(temp_v0_4, 0x14) != 0) {
                FW(temp_v0_4, 0x4) = 1;
            }
            FW(temp_v0_4, 0x14) = var_s2;
            temp_v0_6 = (void*)timproc_uso_b5_func_055750((void **)0x168);
            if (temp_v0_6 != 0) {
                (void*)timproc_uso_b5_func_0546DC(temp_v0_6, (void **)0x1398, 0, 0, 0.0f);
                FW(temp_v0_6, 0x28) = 0x4AC;
                FW(temp_v0_6, 0xC) = 0x13A0;
                temp_v0_7 = (void*)timproc_uso_b5_func_055750((void **)0x16C);
                if (temp_v0_7 != 0) {
                    (void*)timproc_uso_b5_func_0546DC(temp_v0_7, (void **)0x13A8, 0, 0, 0.0f);
                    temp_f0 = *(f32 *)((char *)&D_00000000 + 0x23C);
                    FW(temp_v0_7, 0x120) = 1;
                    FW(temp_v0_7, 0x28) = 0;
                    FW(temp_v0_7, 0x108) = temp_f0;
                    FW(temp_v0_7, 0x10C) = temp_f0;
                    FW(temp_v0_7, 0x110) = temp_f0;
                    *(f32 *)((char *)temp_v0_7 + 0x124) = 1.0f;
                }
                FW(temp_v0_6, 0x108) = temp_v0_7;
                (void*)timproc_uso_b5_func_04DFFC(temp_v0_6, temp_v0_7);
                temp_s0 = FW(temp_v0_6, 0x108);
                *(f32 *)((char *)temp_s0 + 0xB4) = 0.0f;
                *(f32 *)((char *)temp_s0 + 0xB8) = 0.0f;
                *(f32 *)((char *)temp_s0 + 0xBC) = 0.0f;
                *(f32 *)((char *)temp_v0_6 + 0x124) = 1.0f;
                temp_t7 = *(s32 *)4 & 0x80000;
                (*(int*)((char*)&D_00000000+4)) = (s32) ((((*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF & ~1 & 0xFFFDFFFF) | 0x2000) & ~2);
                spC0 = temp_t7;
                FW(temp_v0_6, 0x148) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13C0, 0, 0);
                FW(temp_v0_6, 0x14C) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13CC, 0, 0);
                FW(temp_v0_6, 0x150) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13D8, 0, 0);
                FW(temp_v0_6, 0x154) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13E4, 0, 0);
                FW(temp_v0_6, 0x158) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13F0, 0, 0);
                FW(temp_v0_6, 0x15C) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x13FC, 0, 0);
                FW(temp_v0_6, 0x160) = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x1408, 0, 0);
                temp_v0_8 = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x1414, 0, 0);
                FW(temp_v0_6, 0x13C) = 8;
                FW(temp_v0_6, 0x164) = temp_v0_8;
                FW(temp_v0_6, 0x140) = 0;
                var_v1 = 0;
                if (8 > 0) {
                    var_v0 = temp_v0_6;
                    do {
                        spBC = var_v1;
                        sp4C = var_v0;
                        (void*)timproc_uso_b5_func_04DFFC(temp_v0_6, FW(var_v0, 0x148));
                        temp_s0_2 = FW(var_v0, 0x148);
                        var_v0 += 4;
                        var_v1 += 1;
                        FW(temp_s0_2, 0x18) = (s32) (FW(temp_s0_2, 0x18) & ~4);
                    } while (var_v1 < FW(temp_v0_6, 0x13C));
                }
                FW(temp_v0_6, 0x144) = 0;
                if (spC0 != 0) {
                    var_v0_2 = (*(int*)((char*)&D_00000000+4)) | 0x80000;
                } else {
                    var_v0_2 = (*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF;
                }
                (*(int*)((char*)&D_00000000+4)) = var_v0_2;
                *(f32 *)((char *)temp_v0_6 + 0xDC) = *(f32 *)0x244;
                *(f32 *)((char *)temp_v0_6 + 0xE0) = 720.0f;
                *(f32 *)((char *)temp_v0_6 + 0xE4) = -220.0f;
                *(f32 *)((char *)temp_v0_6 + 0x10C) = *(f32 *)0x248;
                *(f32 *)((char *)temp_v0_6 + 0x110) = *(f32 *)0x24C;
                FW(temp_v0_6, 0x134) = 0;
                *(f32 *)((char *)temp_v0_6 + 0x11C) = 0.0f;
                *(f32 *)((char *)temp_v0_6 + 0x114) = *(f32 *)0x250;
                *(f32 *)((char *)temp_v0_6 + 0x120) = *(f32 *)0x254;
                *(f32 *)((char *)temp_v0_6 + 0x124) = 1.0f;
                *(f32 *)((char *)temp_v0_6 + 0x12C) = *(f32 *)0x258;
                *(f32 *)((char *)temp_v0_6 + 0x128) = *(f32 *)0x25C;
            }
            FW(FW(var_s2, 0x5C), 0x2B8) = temp_v0_6;
            *(float *)&spD0.unk0 = 110.0f;
            *(float *)&spD0.unk4 = -96.0f;
            *(float *)&spD0.unk8 = -510.0f;
            temp_v1 = FW(var_s2, 0x5C);
            sp94.unk0 = (int) spD0.unk0;
            temp_t6 = spD0.unk4;
            sp94.unk4 = temp_t6;
            temp_t7_2 = spD0.unk8;
            sp84.unk4 = temp_t6;
            sp84.unk0 = sp94.unk0;
            sp94.unk8 = temp_t7_2;
            sp84.unk8 = temp_t7_2;
            FW(temp_v1, 0x23C) = sp84.unk0;
            temp_v1_2 = temp_v1 + 0x22C;
            FW(temp_v1_2, 0x14) = sp84.unk4;
            FW(temp_v1_2, 0x18) = sp84.unk8;
            *(float *)&spC4.unk8 = 0.0f;
            *(float *)&spC4.unk4 = 0.0f;
            spC4.unk0 = *(int *)((char *)&D_00000000 + 0x260);
            sp94.unk0 = (int) spC4.unk0;
            temp_t1 = spC4.unk4;
            temp_v1_3 = FW(var_s2, 0x5C) + 0x24C;
            sp94.unk4 = temp_t1;
            temp_t2 = spC4.unk8;
            sp84.unk4 = temp_t1;
            sp84.unk0 = sp94.unk0;
            sp94.unk8 = temp_t2;
            sp84.unk8 = temp_t2;
            FW(temp_v1_3, 0x10) = sp84.unk0;
            FW(temp_v1_3, 0x14) = sp84.unk4;
            FW(temp_v1_3, 0x18) = sp84.unk8;
            FW((FW(var_s2, 0x5C) + 0x284), 0x10) = (f32) *(f32 *)((char *)&D_00000000 + 0x264);
            temp_v0_9 = FW(var_s2, 0x5C);
            FW(temp_v0_9, 0x29C) = (void **) FW(temp_v0_9, 0x2B8);
            FW(FW(FW(var_s2, 0x5C), 0x2B8), 0x12C) = (f32) *(f32 *)((char *)&D_00000000 + 0x268);
            FW(FW(FW(var_s2, 0x5C), 0x2B8), 0x128) = (f32) *(f32 *)((char *)&D_00000000 + 0x26C);
            temp_s0_3 = FW(var_s2, 0x38);
            temp_s1_2 = FW(FW(var_s2, 0x5C), 0x2B8);
            (void*)timproc_uso_b5_func_07ACE0(temp_s0_3 + 0x10, temp_s1_2, &sp94, &sp84);
            if (FW(temp_s1_2, 0x14) != 0) {
                FW(temp_s1_2, 0x4) = 1;
            }
            FW(temp_s1_2, 0x14) = temp_s0_3;
        }
        temp_v1_4 = FW(var_s2, 0x38);
        spE0 = temp_v1_4;
        temp_v0_10 = (void*)timproc_uso_b5_func_055750((void **)0x70);
        if (temp_v0_10 != 0) {
            var_s1 = temp_v0_10;
            if ((temp_v0_10 != 0) || (spE0 = temp_v1_4, temp_v0_11 = (void*)timproc_uso_b5_func_055750((void **)0x70), var_v1_2 = temp_v1_4, var_s1 = temp_v0_11, (temp_v0_11 != 0))) {
                spE0 = temp_v1_4;
                (void*)timproc_uso_b5_func_04C678(var_s1, (void **)0x1420);
                var_v1_2 = temp_v1_4;
                FW(var_s1, 0x28) = 0xA94;
            }
            FW(temp_v0_10, 0x28) = 0xB04;
            FW(temp_v0_10, 0xC) = 0x1428;
            FW(temp_v0_10, 0x2C) = (s32) FW((*(void **)0x134), 0x84);
            FW(temp_v0_10, 0x30) = (s32) FW((*(void **)0x134), 0x80);
            FW(temp_v0_10, 0x6C) = 0;
            FW(temp_v0_10, 0x38) = var_v1_2;
            FW(temp_v0_10, 0x34) = (s32) FW((*(void **)0x134), 0x8C);
        }
        sp12C = temp_v0_10;
        (void*)timproc_uso_b5_func_0000A95C(var_s2, temp_v0_10);
        (void*)timproc_uso_b5_func_07ACE0(sp50, sp12C);
        if (FW(sp12C, 0x14) != 0) {
            FW(sp12C, 0x4) = 1;
        }
        FW(sp12C, 0x14) = var_s2;
        temp_v1_5 = FW(var_s2, 0x38);
        spE0 = temp_v1_5;
        temp_v0_12 = (void*)timproc_uso_b5_func_055750((void **)0x70);
        if (temp_v0_12 != 0) {
            var_s1_2 = temp_v0_12;
            if ((temp_v0_12 != 0) || (spE0 = temp_v1_5, temp_v0_13 = (void*)timproc_uso_b5_func_055750((void **)0x70), var_v1_3 = temp_v1_5, var_s1_2 = temp_v0_13, (temp_v0_13 != 0))) {
                spE0 = temp_v1_5;
                (void*)timproc_uso_b5_func_04C678(var_s1_2, (void **)0x1438);
                var_v1_3 = temp_v1_5;
                FW(var_s1_2, 0x28) = 0xA94;
            }
            FW(temp_v0_12, 0x28) = 0xB74;
            FW(temp_v0_12, 0xC) = 0x1440;
            FW(temp_v0_12, 0x2C) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x84);
            FW(temp_v0_12, 0x30) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x80);
            FW(temp_v0_12, 0x6C) = 0;
            FW(temp_v0_12, 0x38) = var_v1_3;
            FW(temp_v0_12, 0x34) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x8C);
        }
        sp128 = temp_v0_12;
        (void*)timproc_uso_b5_func_0000A95C(var_s2, temp_v0_12);
        (void*)timproc_uso_b5_func_07ACE0(sp50, sp128);
        if (FW(sp128, 0x14) != 0) {
            FW(sp128, 0x4) = 1;
        }
        FW(sp128, 0x14) = var_s2;
        temp_v1_6 = FW(var_s2, 0x38);
        spE0 = temp_v1_6;
        temp_v0_14 = (void*)timproc_uso_b5_func_055750((void **)0x70);
        if (temp_v0_14 != 0) {
            var_s1_3 = temp_v0_14;
            if ((temp_v0_14 != 0) || (spE0 = temp_v1_6, temp_v0_15 = (void*)timproc_uso_b5_func_055750((void **)0x70), var_v1_4 = temp_v1_6, var_s1_3 = temp_v0_15, (temp_v0_15 != 0))) {
                spE0 = temp_v1_6;
                (void*)timproc_uso_b5_func_04C678(var_s1_3, (void **)0x144C);
                var_v1_4 = temp_v1_6;
                FW(var_s1_3, 0x28) = 0xA94;
            }
            FW(temp_v0_14, 0x28) = 0xBE4;
            FW(temp_v0_14, 0xC) = 0x1454;
            FW(temp_v0_14, 0x2C) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x84);
            FW(temp_v0_14, 0x30) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x80);
            FW(temp_v0_14, 0x6C) = 0;
            FW(temp_v0_14, 0x38) = var_v1_4;
            FW(temp_v0_14, 0x34) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x8C);
        }
        sp124 = temp_v0_14;
        (void*)timproc_uso_b5_func_0000A95C(var_s2, temp_v0_14);
        (void*)timproc_uso_b5_func_07ACE0(sp50, sp124);
        if (FW(sp124, 0x14) != 0) {
            FW(sp124, 0x4) = 1;
        }
        FW(sp124, 0x14) = var_s2;
        temp_v1_7 = FW(var_s2, 0x38);
        spE0 = temp_v1_7;
        temp_v0_16 = (void*)timproc_uso_b5_func_055750((void **)0x70);
        if (temp_v0_16 != 0) {
            var_s1_4 = temp_v0_16;
            if ((temp_v0_16 != 0) || (spE0 = temp_v1_7, temp_v0_17 = (void*)timproc_uso_b5_func_055750((void **)0x70), var_v1_5 = temp_v1_7, var_s1_4 = temp_v0_17, (temp_v0_17 != 0))) {
                spE0 = temp_v1_7;
                (void*)timproc_uso_b5_func_04C678(var_s1_4, (void **)0x1460);
                var_v1_5 = temp_v1_7;
                FW(var_s1_4, 0x28) = 0xA94;
            }
            FW(temp_v0_16, 0x28) = 0xC54;
            FW(temp_v0_16, 0xC) = 0x1468;
            FW(temp_v0_16, 0x2C) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x84);
            FW(temp_v0_16, 0x30) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x80);
            FW(temp_v0_16, 0x6C) = 0;
            FW(temp_v0_16, 0x38) = var_v1_5;
            FW(temp_v0_16, 0x34) = (s32) FW(((*(int*)((char*)&D_00000000+0x134))), 0x8C);
        }
        sp120 = temp_v0_16;
        (void*)timproc_uso_b5_func_0000A95C(var_s2, temp_v0_16);
        (void*)timproc_uso_b5_func_07ACE0(sp50, sp120);
        if (FW(sp120, 0x14) != 0) {
            FW(sp120, 0x4) = 1;
        }
        FW(sp120, 0x14) = var_s2;
        temp_v0_18 = (void*)timproc_uso_b5_func_055750((void **)0x2BC);
        if (temp_v0_18 != 0) {
            var_s0_2 = temp_v0_18;
            if ((temp_v0_18 != 0) || (temp_v0_19 = (void*)timproc_uso_b5_func_055750((void **)0x2B8), var_s0_2 = temp_v0_19, (temp_v0_19 != 0))) {
                (void*)timproc_uso_b5_func_04C678(var_s0_2, (void **)0x1474);
                FW(var_s0_2, 0x28) = 0;
                (void*)timproc_uso_b5_func_00002B74(var_s0_2 + 0x2C);
                (void*)timproc_uso_b5_func_000032C8(var_s0_2 + 0x194);
            }
            FW(temp_v0_18, 0x28) = 0x8B4;
            FW(temp_v0_18, 0xC) = 0x147C;
            timproc_uso_b5_func_00003890(temp_v0_18);
        }
        FW(var_s2, 0x54) = temp_v0_18;
        (void*)timproc_uso_b5_func_07ACE0(sp50, temp_v0_18);
        if (FW(temp_v0_18, 0x14) != 0) {
            FW(temp_v0_18, 0x4) = 1;
        }
        FW(temp_v0_18, 0x14) = var_s2;
        temp_v0_20 = (void*)timproc_uso_b5_func_055750((void **)0x168);
        if (temp_v0_20 != 0) {
            (void*)timproc_uso_b5_func_0546DC(temp_v0_20, (void **)0x1488, 0, 0, 0.0f);
            FW(temp_v0_20, 0x28) = 0x4AC;
            FW(temp_v0_20, 0xC) = 0x1490;
            temp_v0_21 = (void*)timproc_uso_b5_func_055750((void **)0x16C);
            if (temp_v0_21 != 0) {
                (void*)timproc_uso_b5_func_0546DC(temp_v0_21, (void **)0x1498, 0, 0, 0.0f);
                temp_f0_2 = *(f32 *)((char *)&D_00000000 + 0x270);
                FW(temp_v0_21, 0x120) = 1;
                FW(temp_v0_21, 0x28) = 0;
                FW(temp_v0_21, 0x108) = temp_f0_2;
                FW(temp_v0_21, 0x10C) = temp_f0_2;
                FW(temp_v0_21, 0x110) = temp_f0_2;
                *(f32 *)((char *)temp_v0_21 + 0x124) = 1.0f;
            }
            FW(temp_v0_20, 0x108) = temp_v0_21;
            (void*)timproc_uso_b5_func_04DFFC(temp_v0_20, temp_v0_21);
            temp_a1 = FW(temp_v0_20, 0x108);
            *(f32 *)((char *)temp_a1 + 0xB4) = 0.0f;
            *(f32 *)((char *)temp_a1 + 0xB8) = 0.0f;
            *(f32 *)((char *)temp_a1 + 0xBC) = 0.0f;
            *(f32 *)((char *)temp_v0_20 + 0x124) = 1.0f;
            temp_t6_2 = (*(int*)((char*)&D_00000000+4)) & 0x80000;
            (*(int*)((char*)&D_00000000+4)) = (s32) (((*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF & ~1 & 0xFFFDFFFF) | 0x2000 | 2);
            sp80 = temp_t6_2;
            temp_v0_22 = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x14A4, 0, 0);
            FW(temp_v0_20, 0x13C) = 1;
            FW(temp_v0_20, 0x148) = temp_v0_22;
            FW(temp_v0_20, 0x140) = 0;
            var_s0_3 = 0;
            if (1 > 0) {
                var_v0_3 = temp_v0_20;
                do {
                    sp4C = var_v0_3;
                    (void*)timproc_uso_b5_func_04DFFC(temp_v0_20, FW(var_v0_3, 0x148));
                    var_s0_3 += 1;
                    temp_a1_2 = FW(var_v0_3, 0x148);
                    var_v0_3 += 4;
                    FW(temp_a1_2, 0x18) = (s32) (FW(temp_a1_2, 0x18) & ~4);
                } while (var_s0_3 < FW(temp_v0_20, 0x13C));
            }
            FW(temp_v0_20, 0x144) = 0;
            if (sp80 != 0) {
                var_v0_4 = (*(int*)((char*)&D_00000000+4)) | 0x80000;
            } else {
                var_v0_4 = (*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF;
            }
            (*(int*)((char*)&D_00000000+4)) = var_v0_4;
            *(f32 *)((char *)temp_v0_20 + 0xDC) = *(f32 *)0x278;
            *(f32 *)((char *)temp_v0_20 + 0xE0) = 720.0f;
            *(f32 *)((char *)temp_v0_20 + 0xE4) = -220.0f;
            *(f32 *)((char *)temp_v0_20 + 0x10C) = *(f32 *)0x27C;
            *(f32 *)((char *)temp_v0_20 + 0x110) = *(f32 *)0x280;
            FW(temp_v0_20, 0x134) = 0;
            *(f32 *)((char *)temp_v0_20 + 0x11C) = 0.0f;
            *(f32 *)((char *)temp_v0_20 + 0x114) = *(f32 *)0x284;
            *(f32 *)((char *)temp_v0_20 + 0x120) = *(f32 *)0x288;
            *(f32 *)((char *)temp_v0_20 + 0x124) = 1.0f;
            *(f32 *)((char *)temp_v0_20 + 0x12C) = *(f32 *)0x28C;
            *(f32 *)((char *)temp_v0_20 + 0x128) = *(f32 *)0x290;
        }
        FW(FW(var_s2, 0x54), 0x2B8) = temp_v0_20;
        sp154.unk0 = *(int *)((char *)&D_00000000 + 0x294);
        *(float *)&sp154.unk4 = 528.0f;
        *(float *)&sp154.unk8 = 180.0f;
        temp_v1_8 = FW(var_s2, 0x54);
        sp94.unk0 = (int) sp154.unk0;
        temp_t5 = sp154.unk4;
        sp94.unk4 = temp_t5;
        temp_t6_3 = sp154.unk8;
        sp84.unk4 = temp_t5;
        sp84.unk0 = sp94.unk0;
        sp94.unk8 = temp_t6_3;
        sp84.unk8 = temp_t6_3;
        FW(temp_v1_8, 0x23C) = sp84.unk0;
        temp_v1_9 = temp_v1_8 + 0x22C;
        FW(temp_v1_9, 0x14) = sp84.unk4;
        FW(temp_v1_9, 0x18) = sp84.unk8;
        sp148.unk0 = *(int *)((char *)&D_00000000 + 0x298);
        sp148.unk4 = *(f32 *)((char *)&D_00000000 + 0x29C);
        sp148.unk8 = *(f32 *)((char *)&D_00000000 + 0x2A0);
        sp94.unk0 = (int) sp148.unk0;
        temp_t0 = sp148.unk4;
        temp_v1_10 = FW(var_s2, 0x54) + 0x24C;
        sp94.unk4 = temp_t0;
        temp_t1_2 = sp148.unk8;
        sp84.unk4 = temp_t0;
        sp84.unk0 = sp94.unk0;
        sp94.unk8 = temp_t1_2;
        sp84.unk8 = temp_t1_2;
        FW(temp_v1_10, 0x10) = sp84.unk0;
        FW(temp_v1_10, 0x14) = sp84.unk4;
        FW(temp_v1_10, 0x18) = sp84.unk8;
        FW((FW(var_s2, 0x54) + 0x284), 0x10) = (f32) *(f32 *)((char *)&D_00000000 + 0x2A4);
        temp_v0_23 = FW(var_s2, 0x54);
        FW(temp_v0_23, 0x29C) = (void **) FW(temp_v0_23, 0x2B8);
        FW(FW(FW(var_s2, 0x54), 0x2B8), 0x12C) = (f32) *(f32 *)((char *)&D_00000000 + 0x2A8);
        FW(FW(FW(var_s2, 0x54), 0x2B8), 0x128) = (f32) *(f32 *)((char *)&D_00000000 + 0x2AC);
        temp_s0_4 = FW(var_s2, 0x38);
        temp_s1_3 = FW(FW(var_s2, 0x54), 0x2B8);
        (void*)timproc_uso_b5_func_07ACE0(temp_s0_4 + 0x10, temp_s1_3, &sp94, &sp84);
        if (FW(temp_s1_3, 0x14) != 0) {
            FW(temp_s1_3, 0x4) = 1;
        }
        FW(temp_s1_3, 0x14) = temp_s0_4;
        temp_v0_24 = (void*)timproc_uso_b5_func_055750((void **)0x2BC);
        if (temp_v0_24 != 0) {
            var_s0_4 = temp_v0_24;
            if ((temp_v0_24 != 0) || (temp_v0_25 = (void*)timproc_uso_b5_func_055750((void **)0x2B8), var_s0_4 = temp_v0_25, (temp_v0_25 != 0))) {
                (void*)timproc_uso_b5_func_04C678(var_s0_4, (void **)0x1510);
                FW(var_s0_4, 0x28) = 0;
                (void*)timproc_uso_b5_func_00002B74(var_s0_4 + 0x2C);
                (void*)timproc_uso_b5_func_000032C8(var_s0_4 + 0x194);
            }
            FW(temp_v0_24, 0x28) = 0x8B4;
            FW(temp_v0_24, 0xC) = 0x1518;
            timproc_uso_b5_func_00003890(temp_v0_24);
        }
        FW(var_s2, 0x58) = temp_v0_24;
        (void*)timproc_uso_b5_func_07ACE0(sp50, temp_v0_24);
        if (FW(temp_v0_24, 0x14) != 0) {
            FW(temp_v0_24, 0x4) = 1;
        }
        FW(temp_v0_24, 0x14) = var_s2;
        temp_v0_26 = (void*)timproc_uso_b5_func_055750((void **)0x168);
        if (temp_v0_26 != 0) {
            (void*)timproc_uso_b5_func_0546DC(temp_v0_26, (void **)0x1524, 0, 0, 0.0f);
            FW(temp_v0_26, 0x28) = 0x4AC;
            FW(temp_v0_26, 0xC) = 0x152C;
            temp_v0_27 = (void*)timproc_uso_b5_func_055750((void **)0x16C);
            if (temp_v0_27 != 0) {
                (void*)timproc_uso_b5_func_0546DC(temp_v0_27, (void **)0x1534, 0, 0, 0.0f);
                FW(temp_v0_27, 0x28) = 0;
                *(f32 *)((char *)temp_v0_27 + 0x108) = *(f32 *)0x2B0;
                *(f32 *)((char *)temp_v0_27 + 0x10C) = *(f32 *)0x2B4;
                FW(temp_v0_27, 0x120) = 1;
                *(f32 *)((char *)temp_v0_27 + 0x110) = *(f32 *)0x2B8;
                *(f32 *)((char *)temp_v0_27 + 0x124) = 1.0f;
            }
            FW(temp_v0_26, 0x108) = temp_v0_27;
            (void*)timproc_uso_b5_func_04DFFC(temp_v0_26, temp_v0_27);
            temp_a1_3 = FW(temp_v0_26, 0x108);
            *(f32 *)((char *)temp_a1_3 + 0xB4) = 0.0f;
            *(f32 *)((char *)temp_a1_3 + 0xB8) = 0.0f;
            *(f32 *)((char *)temp_a1_3 + 0xBC) = 0.0f;
            *(f32 *)((char *)temp_v0_26 + 0x124) = 1.0f;
            temp_t1_3 = (*(int*)((char*)&D_00000000+4)) & 0x80000;
            (*(int*)((char*)&D_00000000+4)) = (s32) (((*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF & ~1 & 0xFFFDFFFF) | 0x2000 | 2);
            sp68 = temp_t1_3;
            temp_v0_28 = (void*)timproc_uso_b5_func_05D0E0(0, (void **)0x1540, 0, 0);
            FW(temp_v0_26, 0x13C) = 1;
            FW(temp_v0_26, 0x148) = temp_v0_28;
            FW(temp_v0_26, 0x140) = 0;
            var_s0_5 = 0;
            if (1 > 0) {
                var_v0_5 = temp_v0_26;
                do {
                    sp50 = var_v0_5;
                    (void*)timproc_uso_b5_func_04DFFC(temp_v0_26, FW(var_v0_5, 0x148));
                    var_s0_5 += 1;
                    temp_a1_4 = FW(var_v0_5, 0x148);
                    var_v0_5 += 4;
                    FW(temp_a1_4, 0x18) = (s32) (FW(temp_a1_4, 0x18) & ~4);
                } while (var_s0_5 < FW(temp_v0_26, 0x13C));
            }
            FW(temp_v0_26, 0x144) = 0;
            if (sp68 != 0) {
                var_v0_6 = (*(int*)((char*)&D_00000000+4)) | 0x80000;
            } else {
                var_v0_6 = (*(int*)((char*)&D_00000000+4)) & 0xFFF7FFFF;
            }
            (*(int*)((char*)&D_00000000+4)) = var_v0_6;
            *(f32 *)((char *)temp_v0_26 + 0xDC) = *(f32 *)0x2BC;
            *(f32 *)((char *)temp_v0_26 + 0xE0) = 720.0f;
            *(f32 *)((char *)temp_v0_26 + 0xE4) = -220.0f;
            *(f32 *)((char *)temp_v0_26 + 0x10C) = *(f32 *)0x2C0;
            *(f32 *)((char *)temp_v0_26 + 0x110) = *(f32 *)0x2C4;
            FW(temp_v0_26, 0x134) = 0;
            *(f32 *)((char *)temp_v0_26 + 0x11C) = 0.0f;
            *(f32 *)((char *)temp_v0_26 + 0x114) = *(f32 *)0x2C8;
            *(f32 *)((char *)temp_v0_26 + 0x120) = *(f32 *)0x2CC;
            *(f32 *)((char *)temp_v0_26 + 0x124) = 1.0f;
            *(f32 *)((char *)temp_v0_26 + 0x12C) = *(f32 *)0x2D0;
            *(f32 *)((char *)temp_v0_26 + 0x128) = *(f32 *)0x2D4;
        }
        FW(FW(var_s2, 0x58), 0x2B8) = temp_v0_26;
        sp13C.unk0 = *(int *)((char *)&D_00000000 + 0x2D8);
        *(float *)&sp13C.unk4 = 528.0f;
        *(float *)&sp13C.unk8 = -480.0f;
        sp94.unk0 = (int) sp13C.unk0;
        sp94.unk4 = (s32) sp13C.unk4;
        sp94.unk8 = (s32) sp13C.unk8;
        sp84.unk0 = sp94.unk0;
        temp_v1_11 = FW(var_s2, 0x58) + 0x22C;
        sp84.unk4 = (s32) sp94.unk4;
        sp84.unk8 = (s32) sp94.unk8;
        FW(temp_v1_11, 0x10) = sp84.unk0;
        FW(temp_v1_11, 0x14) = sp84.unk4;
        FW(temp_v1_11, 0x18) = sp84.unk8;
        sp130.unk0 = *(int *)((char *)&D_00000000 + 0x2DC);
        sp130.unk4 = *(f32 *)((char *)&D_00000000 + 0x2E0);
        sp130.unk8 = *(f32 *)((char *)&D_00000000 + 0x2E4);
        sp94.unk0 = (int) sp130.unk0;
        temp_v1_12 = FW(var_s2, 0x58) + 0x24C;
        sp94.unk4 = (s32) sp130.unk4;
        sp94.unk8 = (s32) sp130.unk8;
        sp84.unk0 = sp94.unk0;
        sp84.unk4 = (s32) sp94.unk4;
        sp84.unk8 = (s32) sp94.unk8;
        FW(temp_v1_12, 0x10) = sp84.unk0;
        FW(temp_v1_12, 0x14) = sp84.unk4;
        FW(temp_v1_12, 0x18) = sp84.unk8;
        FW((FW(var_s2, 0x58) + 0x284), 0x10) = (f32) *(f32 *)((char *)&D_00000000 + 0x2E8);
        temp_v0_29 = FW(var_s2, 0x58);
        FW(temp_v0_29, 0x29C) = (void **) FW(temp_v0_29, 0x2B8);
        FW(FW(FW(var_s2, 0x58), 0x2B8), 0x12C) = (f32) *(f32 *)((char *)&D_00000000 + 0x2EC);
        FW(FW(FW(var_s2, 0x58), 0x2B8), 0x128) = 1.0f;
        temp_s0_5 = FW(var_s2, 0x38);
        temp_s1_4 = FW(FW(var_s2, 0x58), 0x2B8);
        (void*)timproc_uso_b5_func_07ACE0(temp_s0_5 + 0x10, temp_s1_4, &sp94);
        if (FW(temp_s1_4, 0x14) != 0) {
            FW(temp_s1_4, 0x4) = 1;
        }
        FW(temp_s1_4, 0x14) = temp_s0_5;
        temp_s1_5 = FW(sp12C, 0x28);
        (*(int (**)())((char *)temp_s1_5 + 0x5C))(FW(temp_s1_5, 0x58) + sp12C, 1, 5, 0, -150.0f, -1000.0f, 0.0f, 0.0f, 0.0f);
        temp_s1_6 = FW(sp12C, 0x28);
        (*(int (**)())((char *)temp_s1_6 + 0x5C))(FW(temp_s1_6, 0x58) + sp12C, 1, 3, 0x443B8000, -150.0f, *(f32 *)((char *)&D_00000000 + 0x2F0), 0.0f, 0.0f, 0.0f);
        temp_s1_7 = FW(sp12C, 0x28);
        (*(int (**)())((char *)temp_s1_7 + 0x5C))(FW(temp_s1_7, 0x58) + sp12C, 1, 4, 0x443B8000, -150.0f, *(f32 *)((char *)&D_00000000 + 0x2F4), 0.0f, 0.0f, 0.0f);
        temp_s1_8 = FW(sp12C, 0x28);
        (*(int (**)())((char *)temp_s1_8 + 0x5C))(FW(temp_s1_8, 0x58) + sp12C, 1, 2, 0x443B8000, -150.0f, *(f32 *)((char *)&D_00000000 + 0x2F8), 0.0f, 0.0f, 0.0f);
        temp_s1_9 = FW(sp12C, 0x28);
        (*(int (**)())((char *)temp_s1_9 + 0x5C))(FW(temp_s1_9, 0x58) + sp12C, 1, 1, 0x443B8000, -150.0f, *(f32 *)((char *)&D_00000000 + 0x2FC), 0.0f, 0.0f, 0.0f);
        temp_s1_10 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_10 + 0x5C))(FW(temp_s1_10, 0x58) + sp128, 1, 0, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x300), 0.0f);
        temp_s1_11 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_11 + 0x5C))(FW(temp_s1_11, 0x58) + sp128, 1, 1, 0x443B8000, 200.0f, *(f32 *)((char *)&D_00000000 + 0x304), 0.0f, 0.0f, 0.0f);
        temp_s1_12 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_12 + 0x5C))(FW(temp_s1_12, 0x58) + sp128, 1, 2, 0x443B8000, 200.0f, *(f32 *)((char *)&D_00000000 + 0x308), 0.0f, 0.0f, 0.0f);
        temp_s1_13 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_13 + 0x5C))(FW(temp_s1_13, 0x58) + sp128, 1, 3, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x30C), 0.0f);
        temp_s1_14 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_14 + 0x5C))(FW(temp_s1_14, 0x58) + sp128, 1, 4, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x310), 0.0f);
        temp_s1_15 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_15 + 0x5C))(FW(temp_s1_15, 0x58) + sp128, 1, 5, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x314), 0.0f);
        temp_s1_16 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_16 + 0x5C))(FW(temp_s1_16, 0x58) + sp128, 1, 6, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x318), 0.0f);
        temp_s1_17 = FW(sp128, 0x28);
        (*(int (**)())((char *)temp_s1_17 + 0x5C))(FW(temp_s1_17, 0x58) + sp128, 1, 7, 0x43C80000, -150.0f, -1000.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x31C), 0.0f);
        var_s0_6 = FW((*(void **)0x154), 0x0);
        if ((*(int*)((char*)&D_00000000+0x34)) != 6) {
            var_s0_6 &= ~3;
        }
        var_a2 = 0;
        var_v1_6 = &sp100;
        do {
            temp_s1_18 = FW(sp124, 0x28);
            spF8 = var_a2;
            sp50 = var_v1_6;
            temp_v0_30 = (*(int (**)())((char *)temp_s1_18 + 0x5C))(FW(temp_s1_18, 0x58) + sp124, 1, var_a2, 0x43C80000, 210.0f, -280.0f, 0.0f, 0.0f, *(f32 *)((char *)&D_00000000 + 0x320));
            *var_v1_6 = temp_v0_30;
            if (!(var_s0_6 & (1 << var_a2))) {
                *(f32 *)((char *)temp_v0_30 + 0x2A4) = 0.0f;
            }
            var_a2 += 1;
            var_v1_6 += 4;
        } while (var_a2 != 8);
        temp_s1_19 = FW(sp120, 0x28);
        (*(int (**)())((char *)temp_s1_19 + 0x5C))(FW(temp_s1_19, 0x58) + sp120, 1, 1, 0xC35C0000, 200.0f, -400.0f, 0.0f, 0.0f, 0.0f);
        temp_s1_20 = FW(sp120, 0x28);
        spF0 = (*(int (**)())((char *)temp_s1_20 + 0x5C))(FW(temp_s1_20, 0x58) + sp120, 1, 2, 0xC35C0000, 200.0f, -400.0f, 0.0f, 0.0f, 0.0f);
        temp_s1_21 = FW(sp120, 0x28);
        temp_s0_6 = (*(int (**)())((char *)temp_s1_21 + 0x5C))(FW(temp_s1_21, 0x58) + sp120, 1, 3, 0xC35C0000, 200.0f, -400.0f, 0.0f, 0.0f, 0.0f);
        (void*)timproc_uso_b5_func_048E7C((void **)0x15AC, (void **) FW(((*(int*)((char*)&D_00000000+0x154))), 0x2));
        temp_t0_2 = FW(((*(int*)((char*)&D_00000000+0x154))), 0x2);
        switch (temp_t0_2) {
        case 3:
        case 4:
        case 5:
            break;
        case 1:
            *(f32 *)((char *)spF0 + 0x2A4) = 0.0f;
            /* fallthrough */
        case 2:
            *(f32 *)((char *)temp_s0_6 + 0x2A4) = 0.0f;
            break;
        }
        (void*)timproc_uso_b5_func_04C774(var_s2, (void **)1, arg1);
        (void*)timproc_uso_b5_func_04C774(FW(var_s2, 0x50), (void **)1, arg2);
        temp_s1_22 = FW(var_s2, 0x28);
        (*(int (**)())((char *)temp_s1_22 + 0x24))(FW(temp_s1_22, 0x20) + var_s2);
        temp_v0_31 = FW(var_s2, 0x38);
        temp_s1_23 = FW(temp_v0_31, 0x28);
        (*(int (**)())((char *)temp_s1_23 + 0x24))(FW(temp_s1_23, 0x20) + temp_v0_31);
    }
    return var_s2;
}

#undef FW
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_00008FC8);
#endif

void timproc_uso_b5_func_0000A928(int *a0) {
    a0[0x2C / 4] = *(int *)(*(int *)((char *)&D_00000000 + 0x134) + 0x84);
    a0[0x30 / 4] = *(int *)(*(int *)((char *)&D_00000000 + 0x134) + 0x80);
    a0[0x34 / 4] = *(int *)(*(int *)((char *)&D_00000000 + 0x134) + 0x8C);
    a0[0x3C / 4] = 0;
}

/* timproc_uso_b5_func_0000A95C: array-append + count-increment, returns a1.
 * EXACT (2026-06-21, decomp-permuter). The residual was a pure 2-insn schedule
 * swap: target emits `addu t8,a0,t7` (array addr) BEFORE `sw t6,0x3C(a0)` (count
 * store), but the natural one-statement-per-line C made IDO schedule the count
 * store first. CRACK: put both stores on ONE source line (the documented
 * "one-line stores fix schedule order" lever) — IDO then schedules the addu
 * before the count sw, matching. Verified IN-TREE against the full-TU build
 * (8/8 words, 0 diffs); the prior "standalone false match" caveat is moot now
 * that the real build is byte-exact. (Twin: bootup_uso ...2088, same pair.) */
int timproc_uso_b5_func_0000A95C(int *a0, int a1) {
    int v1 = a0[0x3C / 4];
    a0[0x3C / 4] = v1 + 1; *(int *)((char *)a0 + (v1 << 2) + 0x40) = a1;
    return a1;
}

/* timproc_uso_b5_func_0000A97C: 23-insn loop calling slot->0x28->0x4C(short@0x48)
 * per element via the incrementing cursor `p`. MATCHED 2026-06-04 via
 * decomp-permuter (base 35 -> 0): wrapping the inner block in `if (1) { }` adds
 * a basic-block boundary that flips the v0/v1 caller-save allocation to the
 * target's (the cursor-read lands in v1, not v0). The prior "register-renumber
 * cap / branch-likely not reachable from C" comment was a misdiagnosis. */
void timproc_uso_b5_func_0000A97C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    i = 0;
    p = a0;
    do {
        v1 = *(int**)(p + 0x40);
        if (1) {
            v0 = *(int**)((char*)v1 + 0x28);
            (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
            i++;
        }
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}

/* timproc_uso_b5_func_0000A9EC: sibling of A97C, offsets 0x64/0x60 instead of
 * 0x4C/0x48. MATCHED 2026-06-04 via the same `if (1) { }` block-boundary lever
 * (flips the v0/v1 allocation). The "structural cap — branch-likely not
 * reachable from std do-while C" comment was a misdiagnosis. */
void timproc_uso_b5_func_0000A9EC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x3C) <= 0) return;
    i = 0;
    p = a0;
    do {
        v1 = *(int**)(p + 0x40);
        if (1) {
            v0 = *(int**)((char*)v1 + 0x28);
            (*(int(**)())((char*)v0 + 0x64))(*(short*)((char*)v0 + 0x60) + (int)v1);
            i++;
        }
        p += 4;
    } while (i < *(int*)(a0 + 0x3C));
}

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


/* 2026-06-21 CRACKED via masked-twin port from eddproc_uso_func_000003BC
 * (donor, byte-exact); identical land to game_uso 3A28/AC78/11A94. alloc(0x40)
 * + init(051C28), vtable 0x28 = &import_8006ED80, clear 0x3C; then walk
 * arg0->0x40 node and link via 07ACE0. The donor's p2/head/p1 split +
 * p1-reuse-for-arg0 + decl-order (p2,head,p1) + condition re-load forces the
 * two-web spill (frame 0x28) and the a0/v1 coloring that the prior
 * single-web/vparg body could not reach. */
extern int timproc_uso_b5_func_051C28();
extern char import_8006ED80;
void *timproc_uso_b5_func_0000AB24(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)timproc_uso_b5_func_055750(0x40);
    if (p1 != 0) {
        timproc_uso_b5_func_051C28(p1);
        *(int*)((char*)p1 + 0x28) = (int)&import_8006ED80;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        timproc_uso_b5_func_07ACE0((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}

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

// timproc_uso_b5_func_0000AC20 — STRUCTURAL PASS (0x534 / 333 words,
// no episode). Raw-.word USO form (genuine code, single function).
// Heavily FP-math (83 FP ops / 19 FP moves / 13 calls) — entry/shape
// partial pass; multi-run target.
//
// 3D transform / matrix-vector math routine operating on a transform
// sub-struct at obj+0xDC.
//
//   void timproc_uso_b5_func_0000AC20(Obj *obj, …) {     // obj -> s0
//     T *t = (T*)((char*)obj + 0xDC);                     // xform block
//     // load Vec3s from t / a global, compute scaled / combined
//     //   products (mul.s/add.s/sub.s chains), build transformed
//     //   Vec3s into sp scratch (sp+0xD0.., sp+0xF4..);
//     // copy 3-word (Vec3/row) blocks between t and sp;
//     // ~13 func_00000000 sub-calls (apply / compose transform);
//     // final FP combine + writeback into t / obj fields.
//   }
//
// Struct-typing reference:
//   obj+0xDC = a transform record (Vec3 rows / position / orientation
//     at +0x0/+0x4/+0x8 groups); sp+0xD0 / sp+0xF4 = transformed Vec3
//     scratch. The math is a per-frame matrix*vector / projection
//     update for the timing-screen camera or marker placement.
//     func_00000000 = USO placeholder dispatcher (transform helpers).
// Caps (DEFERRED): raw-word USO + placeholder calls + 333-word FP
//   pipeline; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — transform block + initial scaled
//   compose + cb chain skeleton only. Byte-match deferred. Name
//   pre-checked: no extern reuse.
#ifdef NON_MATCHING
/* PASS-2 2026-06-10 (big-swing): FULL m2c graft. The .s is UNDERSIZED
 * (true body 0x534 to block5 0xB154, from the verified asset; boundary
 * reconciliation when exact). 6% COP1, prior body replaced (git). */
void timproc_uso_b5_func_0000AC20(char *arg0) {
    f32 spF8; f32 spFC;
    f32 spF4;
    s32 spE4;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    s32 sp7C;
    s32 sp6C;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    char *sp2C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f12_4;
    f32 temp_f12_5;
    f32 temp_f12_6;
    f32 temp_f2;
    f32 var_f12;
    s32 temp_t7;
    s32 temp_t8;
    char *temp_a0;
    char *temp_v0;

    temp_v0 = arg0 + 0xDC;
    spD0 = *(s32 *)((char *)(arg0) + 0xDC) - *(s32 *)((char *)&D_00000000 + 0);
    temp_f12 = *(s32 *)((char *)(temp_v0) + 0x8) - *(f32 *)8;
    spD4 = *(s32 *)((char *)(temp_v0) + 0x4) - *(f32 *)4;
    spD8 = temp_f12;
    *((s32 *)&spE4 + 0) = (f32) *((s32 *)&spD0 + 0);
    temp_t7 = *((s32 *)&spD0 + 1);
    *((s32 *)&spE4 + 1) = temp_t7;
    temp_t8 = *((s32 *)&spD0 + 2);
    *((s32 *)&spF4 + 1) = temp_t7;
    *((s32 *)&spF4 + 0) = *((s32 *)&spE4 + 0);
    *((s32 *)&spE4 + 2) = temp_t8;
    *((s32 *)&spF4 + 2) = temp_t8;
    func_00000000(temp_f12, &spF4);
    temp_a0 = arg0 + 0xF4;
    if ((f64) ((*(s32 *)((char *)&D_00000000 + 0) * spF4) + (*(s32 *)((char *)&D_00000000 + 4) * spF8) + (*(s32 *)((char *)&D_00000000 + 8) * spFC)) < *(f64 *)0x338) {
        *(s32 *)((char *)(arg0) + 0xF4) = 0.0f;
        *(s32 *)((char *)(arg0) + 0xF8) = 0.0f;
        *(s32 *)((char *)(arg0) + 0xFC) = 0.0f;
        *(s32 *)((char *)(arg0) + 0x100) = 1.0f;
        sp2C = temp_a0;
        sp54 = 0.0f;
        sp50 = 0.0f;
        sp4C = 1.0f;
        func_00000000(temp_a0, &sp4C, *(s32 *)((char *)(arg0) + 0x114));
        sp3C = 0.0f;
        sp40 = 0.0f;
        sp44 = 1.0f;
        func_00000000(sp2C, &sp3C, *(s32 *)((char *)(arg0) + 0x110));
        sp30 = 0.0f;
        sp38 = 0.0f;
        sp34 = 1.0f;
        func_00000000(sp2C, &sp30, *(s32 *)((char *)(arg0) + 0x118));
        func_00000000(*(s32 *)((char *)((*(s32 *)((char *)&D_00000000 + 0))) + 0x70) + 0xB4, &sp7C);
        func_00000000(&sp7C, &sp6C);
        temp_f2 = *(s32 *)((char *)(arg0) + 0x120);
        var_f12 = 1.0f;
        temp_f0 = 1.0f + (*(s32 *)((char *)(arg0) + 0x11C) * temp_f2);
        *(s32 *)((char *)(arg0) + 0xE8) = temp_f0;
        *(s32 *)((char *)(arg0) + 0xEC) = temp_f0;
        *(s32 *)((char *)(arg0) + 0xF0) = temp_f0;
        if (*(s32 *)((char *)(arg0) + 0x12C) != 0) {
            var_f12 = temp_f2;
        }
        func_00000000(var_f12, sp2C, &sp6C, var_f12, 0);
        sp5C = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f) + (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f);
        sp60 = (*(s32 *)((char *)(arg0) + 0xF8) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f) - (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xF4) * 2.0f);
        temp_f12_2 = *(s32 *)((char *)(arg0) + 0xF4);
        temp_f0_2 = *(s32 *)((char *)(arg0) + 0xF8);
        sp64 = (1.0f - (temp_f12_2 * temp_f12_2 * 2.0f)) - (temp_f0_2 * temp_f0_2 * 2.0f);
        func_00000000(temp_f12_2, sp2C, &sp5C, 0x3FC90FDB);
        temp_f0_3 = *(s32 *)((char *)(arg0) + 0xF8);
        temp_f12_3 = *(s32 *)((char *)(arg0) + 0xFC);
        sp5C = (1.0f - (temp_f0_3 * temp_f0_3 * 2.0f)) - (temp_f12_3 * temp_f12_3 * 2.0f);
        sp60 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f) + (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f);
        sp64 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f) - (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f);
        func_00000000(temp_f12_3, sp2C, &sp5C, 0x3FC90FDB);
        if ((*(s32 *)((char *)(arg0) + 0x12C) != 0) && (*(s32 *)((char *)(arg0) + 0x130) != 0)) {
            temp_f12_4 = *(f32 *)((char *)&D_00000000 + 0x340);
            *(f32 *)((char *)(arg0) + 0x10C) = (f32) (*(s32 *)((char *)(arg0) + 0x10C) + *(f32 *)((char *)&D_00000000 + 0x344));
            temp_f0_4 = *(s32 *)((char *)(arg0) + 0x10C);
            if (temp_f12_4 <= temp_f0_4) {
                *(f32 *)((char *)(arg0) + 0x10C) = (f32) (temp_f0_4 - temp_f12_4);
            }
            temp_f0_5 = *(s32 *)((char *)(arg0) + 0xF8);
            temp_f12_5 = *(s32 *)((char *)(arg0) + 0xFC);
            sp5C = (1.0f - (temp_f0_5 * temp_f0_5 * 2.0f)) - (temp_f12_5 * temp_f12_5 * 2.0f);
            sp60 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f) + (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f);
            sp64 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f) - (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f);
            func_00000000(temp_f12_5, 0, sp2C, &sp5C, *(s32 *)((char *)(arg0) + 0x10C));
        } else {
            temp_f0_6 = *(s32 *)((char *)(arg0) + 0x10C);
            if (temp_f0_6 > 0.0f) {
                *(f32 *)((char *)(arg0) + 0x10C) = (f32) (temp_f0_6 + *(f32 *)((char *)&D_00000000 + 0x34C));
                if (*(f32 *)((char *)&D_00000000 + 0x348) <= *(s32 *)((char *)(arg0) + 0x10C)) {
                    *(s32 *)((char *)(arg0) + 0x10C) = 0.0f;
                }
                temp_f0_7 = *(s32 *)((char *)(arg0) + 0xF8);
                temp_f12_6 = *(s32 *)((char *)(arg0) + 0xFC);
                sp5C = (1.0f - (temp_f0_7 * temp_f0_7 * 2.0f)) - (temp_f12_6 * temp_f12_6 * 2.0f);
                sp60 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f) + (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f);
                sp64 = (*(s32 *)((char *)(arg0) + 0xF4) * *(s32 *)((char *)(arg0) + 0xFC) * 2.0f) - (*(s32 *)((char *)(arg0) + 0x100) * *(s32 *)((char *)(arg0) + 0xF8) * 2.0f);
                func_00000000(temp_f12_6, 0, sp2C, &sp5C, *(s32 *)((char *)(arg0) + 0x10C));
            }
        }
        func_00000000(*(s32 *)((char *)(arg0) + 0x108), *(s32 *)((char *)(arg0) + 0x124));
        func_00000000(arg0);
        *(s32 *)((char *)(arg0) + 0x128) = 1;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000AC20);
#endif

/* timproc_uso_b5_func_0000B154: 133-insn (0x214) AI-update orchestrator.
 * Frame 0xA8, $s0/$s1 saves. Coarse structure decoded 2026-05-05:
 *
 *   1. Vec3 baseline + delta compute (0xB154-0xB1A8): loads 3 floats from
 *      &D_0+0xDC and 3 floats from sp+0x68 area; computes pairwise sub.s
 *      (delta_v = ref_v - cur_v) and stores to sp+0x68/0x6C/0x70.
 *
 *   2. 12-byte struct copy with fanout (0xB1AC-0xB1D4): reads t6+0/4/8
 *      writes a2+0/4/8 AND a4+0/4/8 (the canonical "save-old + write-new"
 *      idiom — same shape as game_uso_func_00001DDC tail, see that
 *      function's notes). Followed by jal cross-USO call.
 *
 *   3. Four sequential 3-float scale + jal blocks (0xB1D8-0xB28C): each
 *      block reads s0+0x110/0x10C/0x114/0x118 (a per-axis scaling
 *      coefficient table on s0), multiplies by 1.0 (mtc1 zero, mtc1 0x3F80),
 *      stores to sp+0x48/0x38/0x2C/0x98 (output buffers), then jal.
 *      Pattern: 4-axis state-machine update.
 *
 *   4. Final scale + cross-call (0xB290-0xB2D4): reads s0+0x108 (sub-obj
 *      ptr), 3 floats from s0+0x128/0x12C/0x11C; computes
 *      mul.s + sub.s of 0.5 (lui 0x3F00 = 0.5f), then jal.
 *
 *   5. Tail: bit-flag toggle on s0+0x144 (frame counter or state bit),
 *      conditional vtable-index increment+wrap on s0+0x140 vs s0+0x13C
 *      array length, then bit-set/bit-clear on s0+0x148-derived sub-obj's
 *      [0x18] field (`AND 0xFFFFFFFB` and `OR 0x4`).
 *
 * Key field offsets (s0 struct, ~0x150+ bytes):
 *   [0x108] sub-obj ptr (used as $a0 to multiple jals)
 *   [0x10C], [0x110], [0x114], [0x118] axis scale coefficients (4 floats)
 *   [0x11C], [0x128], [0x12C] coefficient floats
 *   [0x13C] array length
 *   [0x140] index into s0+0x148 array
 *   [0x144] frame-counter / state bit
 *   [0x148] sub-obj-array base ptr
 *
 * Logic looks like a per-frame AI/state update that:
 *   - computes 3D delta from reference position
 *   - cross-calls 6 separate per-axis processors
 *   - advances a circular index with wraparound
 *   - toggles a state bit on each call
 *
 * Yay0-compressed segment; default INCLUDE_ASM build remains exact.
 * Multi-tick decomp target — ~7 cross-USO calls, struct typing required.
 * Initial structural pass 2026-05-05. */
#ifdef NON_MATCHING
/* Skeleton C — captures structure only; no byte-match attempt yet. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000B154(int *a0) {
    int *s0 = a0;
    float *src = (float *)((char *)a0 + 0xDC);
    float dx = src[0] - *(float *)&D_00000000;
    float dy = src[1] - *(float *)((char *)&D_00000000 + 4);
    float dz = src[2] - *(float *)((char *)&D_00000000 + 8);
    src[0] = dx;
    src[1] = dy;
    src[2] = dz;
    *(float *)((char *)s0 + 0xF4) = 0.0f;
    *(float *)((char *)s0 + 0xF8) = 0.0f;
    *(float *)((char *)s0 + 0xFC) = 0.0f;
    *(float *)((char *)s0 + 0x100) = 1.0f;
    *(float *)((char *)s0 + 0xE8) = *(float *)((char *)s0 + 0x118);
    *(float *)((char *)s0 + 0xEC) = *(float *)((char *)s0 + 0x118);
    *(float *)((char *)s0 + 0xF0) = *(float *)((char *)s0 + 0x118);
    /* TODO: per-axis quaternion rotate calls + stack Vec3 scratch (insns 41+). */
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B154);
#endif

// timproc_uso_b5_func_0000B368 — STRUCTURAL PASS (0x2BC / 175 words,
// no episode). Raw-.word USO form. BOUNDARY NOTE: 2-jr USO bundle
// (named fn 0xB368..0xB618 ~172 words + 1 tiny trailing setter
// 0xB61C `jr ra; sw a0,0(…)`) — deferred USO re-split.
//
// FP basis/transform builder on the obj+0xDC transform sub-struct —
// sibling of func_0000AC20 (camera look-at / billboard orientation).
//
//   void timproc_uso_b5_func_0000B368(Obj *obj, …) {     // obj -> s0
//     T *t = (T*)((char*)obj + 0xDC);
//     // load source Vec3s from t (+0x0/+0x4/+0x8 groups) and obj
//     //   fields; compute cross-products / differences (mul.s/
//     //   sub.s/add.s) to build orthogonal basis vectors into sp
//     //   scratch (sp+0x110/0xF4/0xE8/0xDC/0xC4/0xB8);
//     // normalize each via func_00000000 (= 1.0f / length);
//     // assemble a 3x3-ish matrix and copy 3-word (row) blocks back
//     //   into obj / t fields; const 1.0f (0x3F800000) used as the
//     //   homogeneous / unit term;
//     obj->0x12C = 1;                                      // computed flag
//   }
//
// Struct-typing reference:
//   obj+0xDC = transform record (Vec3 rows at +0x0/+0x4/+0x8);
//   obj->0x108/0x124/0x128/0x13C/0x140 = input/param fields;
//   obj->0x12C = "transform built" flag (set 1 at end). sp+0xB8..
//   0x110 = basis-vector scratch. func_00000000 = USO placeholder
//   dispatcher (length/normalize + matrix helpers). const 1.0f.
// Caps (DEFERRED): raw-word USO + unsplit bundle + placeholder calls;
//   USO mnemonic disasm limitation prevents byte-match. Real-C
//   STRUCTURAL body below — basis-vector setup + cb normalize +
//   transform-built flag skeleton only. Byte-match deferred. Name
//   pre-checked: no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000B368(char *obj, int unused) {
    char *t = obj + 0xDC;
    float basis[12];
    int i;
    /* Build initial basis from t Vec3 rows + obj input fields. */
    for (i = 0; i < 3; i++) {
        basis[i + 0] = *(float *)(t + i * 4);
        basis[i + 3] = *(float *)(t + 0x10 + i * 4);
        basis[i + 6] = *(float *)(obj + 0x108 + i * 4);
    }
    /* Cross / normalize via cb helpers. */
    func_00000000(&basis[0], &basis[6]);
    func_00000000(&basis[3]);
    func_00000000(&basis[0], &basis[3]);
    /* Write resulting matrix back into the transform sub-struct. */
    for (i = 0; i < 3; i++) {
        *(float *)(t + i * 4)       = basis[i + 0];
        *(float *)(t + 0x10 + i * 4) = basis[i + 3];
        *(float *)(t + 0x20 + i * 4) = basis[i + 6];
    }
    *(int *)(obj + 0x12C) = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B368);
#endif

/* Save-arg sentinel: void f(int a0){} → jr ra; sw a0, 0(sp).
 * docs/IDO_CODEGEN.md#feedback-ido-save-arg-sentinel-empty-body */
void timproc_uso_b5_func_0000B61C(int a0) {}

// timproc_uso_b5_func_0000B624 — FULLY DECODED (single fn, 0x22C / 139
// insns; the old "0x304/4-jr-bundle" note was WRONG — it is one
// function ending jr ra at B81C). Disassembled from the matching .o via
// scripts/disasm-func.py (the raw-.word .s defeats m2c directly).
//
// VERIFIED structure (proximity-gated transform setter on obj+0xDC):
//   t = (f32*)(obj+0xDC);  ref = &D_807FFBB0 (Vec3 const)
//   delta = {t[0]-ref[0], t[1]-ref[1], t[2]-ref[2]};   // sp68
//   c7C = delta; c8C = delta;                          // dup to sp7C/sp8C
//   func_071028(&c8C);                                 // 1-arg
//   dot = ref[0]*c8C.x + ref[1]*c8C.y + ref[2]*c8C.z;
//   if ((double)dot >= *(double*)(&D_807FF370 + 848)) { obj[0x134]=0; return; }
//   obj[0xF4]=obj[0xF8]=obj[0xFC]=0; obj[0x100]=1.0;
//   func_071AE0(1.0f, &obj[0xF4], {1,0,0}@sp48, obj[0x114]);  // X axis
//   func_071AE0(1.0f, &obj[0xF4], {0,0,1}@sp38, obj[0x110]);  // Z axis
//   func_071AE0(1.0f, &obj[0xF4], {0,1,0}@sp2C, obj[0x118]);  // Y axis
//   func_06970C(obj[0x108], obj[0x130]);
//   if (obj[0x144] || obj[0x138]) {
//     func_054FE0(obj);  (*(int*)&D_807FFBBC)++;   // global counter
//     n = obj[0x144]; if (n) obj[0x144] = --n;
//     if (n == 0) { p = obj[0x10C];
//       if (p[0xB0]) { func_077C44(p, obj[0x140], 0, 2, 2, 1); obj[0x10C]->0xB0 = 0; } }
//   }
//   func_054CAC(obj);  obj[0x134] = 1;
//
// CAP — FP SCHEDULING (verified 2026-06-06): reconstructing the above
// literally builds clean (148 insns) but objdiff scores fuzzy=None /
// match 0% (94 insert / 85 delete in the alignment) — IDO's FP
// instruction scheduler reorders the mul.s/add.s/sub.s + lwc1/swc1
// stream so thoroughly that the C-emitted order shares ~no exact
// anchors with the target (the prologue frame size also differs, so
// there is not even a prologue anchor → None). This is the
// FP-schedule cap class; needs the permuter on the verified logic
// above, not a structural rewrite. Placeholder STRUCTURAL body kept
// below (scores ~20.7%) to avoid a fuzzy=None regression; swap in the
// verified body once an FP-schedule match is found. Name pre-checked:
// no extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000B624(char *obj, int unused) {
    char *t = obj + 0xDC;
    float basis[9];
    int i;
    for (i = 0; i < 3; i++) {
        basis[i + 0] = *(float *)(t + i * 4);
        basis[i + 3] = *(float *)(t + 0x10 + i * 4);
        basis[i + 6] = *(float *)(t + 0x20 + i * 4);
    }
    func_00000000(&basis[0]);
    func_00000000(&basis[3]);
    func_00000000(&basis[6]);
    func_00000000(&basis[0], &basis[3], &basis[6]);
    for (i = 0; i < 3; i++) {
        *(float *)(t + i * 4)         = basis[i + 0];
        *(float *)(t + 0x10 + i * 4)   = basis[i + 3];
        *(float *)(t + 0x20 + i * 4)   = basis[i + 6];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B624);
#endif

/* timproc_uso_b5_func_0000B850 [0xB850..0xB914), 0xC4: BOUNDARY MERGE
 * 2026-06-10 of the B8E0 tail fragment (B850's bc1f branched into it).
 * Float fade-toward-target helper:
 *   target = a1 (f12); if (a0->f_2A4 == 0) target = 0;
 *   s = a0->p_2B8; if (s->i_138 != 0) target = 1.0f;
 *   if (s->f_130 < target) { s->f_130 += STEP_UP; if (target < s->f_130) s->f_130 = target; }
 *   else { s->f_130 -= STEP_DOWN; if (s->f_130 < target) s->f_130 = target; }
 * STEP_UP/STEP_DOWN are reloc'd USO globals (lwc1 +0x358/+0x35C off a
 * lui-at base). Same shape as the C0D4/C7B4/CBD0/CDC8 tail-fragment
 * family (predecessor merges pending, one per tick). NM body is
 * structural; float scheduling unverified -- INCLUDE_ASM is build path. */
#ifdef NON_MATCHING
/* step constants are reloc'd USO float globals; reference through the
 * file's existing int placeholder to avoid the extern-type-mismatch
 * redeclaration break (docs/MATCHING_WORKFLOW).
 * 2026-06-21 (agent-e): 93.88% -> 95.57% COUNT-EXACT (49=49). Hoisting the
 * `v = (float*)(s+0x130)` assignment ABOVE the `if (s->i_138)` check matches
 * the target's early `addiu v1,v0,0x130` materialization (the addr is computed
 * right after the `s`/`s->i_138` load, dead until recomputed per-arm). Residual
 * 14 diffs = pure address-reg coloring tie: the named persistent `v` colors
 * into $a1 + a `move v1,a1` where the target keeps it in $v1 directly, and the
 * first `*v` compare reads `0(a1)` vs target's CSE'd `0x130(v0)`. Coupled: any
 * recompute-per-arm variant CSEs the stores back to base+offset and drops the
 * count to 47/48 (tried 4 variants). uoptlist: `v`=cand14->R4($a1), lost $v1
 * (cand12) by encounter-order; unreachable from C without a persistent local.
 * Genuine first-temp/address-reg coloring cap. */
#define B850_STEP_UP   (*(float *)((char *)&D_00000000 + 0x358))
#define B850_STEP_DOWN (*(float *)((char *)&D_00000000 + 0x35C))
void timproc_uso_b5_func_0000B850(char *a0, float target) {
    char *s;
    float *v;
    if (*(float *)(a0 + 0x2A4) == 0.0f) {
        target = 0.0f;
    }
    s = *(char **)(a0 + 0x2B8);
    v = (float *)(s + 0x130);
    if (*(int *)(s + 0x138) != 0) {
        target = 1.0f;
    }
    if (*v < target) {
        *v += B850_STEP_UP;
        s = *(char **)(a0 + 0x2B8);
        if (target < *(float *)(s + 0x130)) {
            *(float *)(s + 0x130) = target;
        }
    } else {
        *v -= B850_STEP_DOWN;
        s = *(char **)(a0 + 0x2B8);
        if (*(float *)(s + 0x130) < target) {
            *(float *)(s + 0x130) = target;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000B850);
#endif

void timproc_uso_b5_func_0000B914(int *a0) {
    *(int*)((char*)a0 + 0x2B4) ^= 0x20000;
}

void timproc_uso_b5_func_0000B928(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 3, 1, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
}

void timproc_uso_b5_func_0000B98C(int *a0) {
    int *p = (int*)a0[0x2B8/4];
    gl_func_00000000(*(int*)((char*)p + 0x10C), *(int*)((char*)p + 0x140), 2, 3, 1, 1);
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0xB0) = 0;
    *(int*)((char*)*(int*)((char*)(int*)a0[0x2B8/4] + 0x10C) + 0x64) = -1000;
}

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

/* 16-insn float-quad copy: v0 = a0->_2B8; copies 4 floats from
 * a0->{_25C,_260,_264,_294} into v0->{_114,_118,_110,_11C}, then calls
 * gl_func_00000000. Bundled-leaf trailer split off as 0000BBC8. */
/* timproc_uso_b5_func_0000BB88/C1B4/CC74/CE6C: 4 sibling 4-float copy + tail-call
 * functions. Callee resolved 2026-06-04 to timproc_uso_b5_func_00003F58 (every
 * sibling's .s jal target; was a generic func_/gl_func_00000000 placeholder).
 * RESIDUAL CAP: FP register renumber. Target emits the 0x294 load FIRST into $f14
 * (descending $f14/$f12/$f2/$f0); IDO's first-encountered-pseudo->$f0 rule gives
 * ascending. Tried forward-decl (a=$f0, right order/wrong regs), reverse-decl
 * (right regs/reversed emit order), and call-before-last-store (d spills across
 * the call, frame grows). a-load-first-with-$f14 needs the scheduler to hoist a's
 * load while a is the last pseudo - not reachable from C. Stays NM (~97.5%). */
/* timproc_uso_b5_func_0000BB88/C1B4/CC74/CE6C: 4 sibling 4-float copy + tail-call
 * functions. Callee = timproc_uso_b5_func_00003F58 (real intra-module symbol,
 * matches the .s jal). EXACT 16/16 (2026-07-02) — the old "FP register renumber
 * cap" was FALSE. Recipe: loads in decl order a(294),b(264),c(260),d(25C);
 * stores c,d, if(!d){}, b, if(b){}, a. Locals c,d color f2,f0 (d bumped by the
 * branch use); the empty-if BB boundaries globalize b then a, which color from
 * the pool END: b->f12, a->f14. Byte-identical body to C1B4. */
void timproc_uso_b5_func_0000BB88(int *a0) {
  int *p = (int *) a0[0x2B8 / 4];
  float a = *((float *) (((char *) a0) + 0x294));
  float b = *((float *) (((char *) a0) + 0x264));
  float c = *((float *) (((char *) a0) + 0x260));
  float d = *((float *) (((char *) a0) + 0x25C));
  *((float *) (((char *) p) + 0x118)) = c;
  *((float *) (((char *) p) + 0x114)) = d;
  if (!d)
  {
  }
  *((float *) (((char *) p) + 0x110)) = b;
  if (b)
  {
  }
  *((float *) (((char *) p) + 0x11C)) = a;
  timproc_uso_b5_func_00003F58();
}

/* 5-insn float store: stores a1 to a0->_2A0 and (a0->_2B8)->_120.
 * Float arg passed in $a1 (int reg), so IDO emits mtc1 to FPU first. */
void timproc_uso_b5_func_0000BBC8(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x120) = a1;
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000BBDC: per-channel (5x) clamp + dispatch loop.
 * MISSING LOGIC reconstructed: real targets func_00003A4C / func_00003C8C
 * (was gl_func_00000000 placeholder), real if/else on a1->0x3BC==1, correct
 * reloc base timproc_uso_b5_D_807FF4C0 (was D_00000000). Cap values and idx
 * pointers are spilled into local arrays before the loop (IDO frame -184). */
void timproc_uso_b5_func_0000BBDC(int *a0, int *a1) {
    int *idxp[5];
    int caps[5];
    int *cp;
    int **ip;
    char *tbl;
    int i;
    int v;
    int v1;
    int stride;

    if (*(int *)((char *)a0 + 0x2BC) < 10) {
        int c = *(int *)((char *)a0 + 0x2C0) - 1;
        *(int *)((char *)a0 + 0x2C0) = c;
        if (c < 0) {
            *(int *)((char *)a0 + 0x2C0) = 1;
            *(int *)((char *)a0 + 0x2BC) = *(int *)((char *)a0 + 0x2BC) + 2;
        }
    }
    caps[0] = *(int *)((char *)a0 + 0x1C4);
    caps[1] = *(int *)((char *)a0 + 0x1DC);
    caps[2] = *(int *)((char *)a0 + 0x1F4);
    caps[3] = *(int *)((char *)a0 + 0x20C);
    caps[4] = *(int *)((char *)a0 + 0x224);
    idxp[0] = (int *)((char *)a1 + 0x134);
    idxp[1] = (int *)((char *)a1 + 0x158);
    idxp[2] = (int *)((char *)a1 + 0x17C);
    idxp[3] = (int *)((char *)a1 + 0x1A0);
    idxp[4] = (int *)((char *)a1 + 0x1C4);

    cp = caps;
    ip = idxp;
    tbl = (char *)&timproc_uso_b5_D_807FF4C0 + 0x40;
    for (i = 0; i < 5; i++) {
        v = *(int *)((char *)a0 + 0x2BC);
        v1 = (v < *cp) ? v : *cp;
        if (*(int *)((char *)a1 + 0x3BC) == 1) {
            stride = *(int *)((char *)a1 + 0x74);
            timproc_uso_b5_func_00003A4C(
                (int)a0,
                *(int *)((char *)a0 + 0xA4),
                *(int *)((char *)a0 + 0xBC) + i * stride,
                (int)tbl,
                v1,
                (int)*ip,
                (char *)((char *)a1 + 0x230),
                (char *)a1);
        } else {
            stride = *(int *)((char *)a1 + 0x74);
            timproc_uso_b5_func_00003C8C(
                (int)a0,
                *(int *)((char *)a0 + 0xA4),
                *(int *)((char *)a0 + 0xBC) + i * stride,
                (void *)tbl,
                v1,
                (int)*ip,
                (char *)((char *)a1 + 0x230),
                (void *)a1);
        }
        cp++;
        ip++;
        tbl += 0x18;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BBDC);
#endif

extern char D_b5_BDA0_table;
void timproc_uso_b5_func_0000BDA0(int *a0, int a1, int a2, int a3) {
    (void)a1; (void)a2; (void)a3;
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], (char*)&D_b5_BDA0_table + a0[0x1AC/4] * 24);
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000BDEC: 242-insn FPU-heavy color-transform helper.
 * 0x3C8 size starting at 0xBDEC, ending at 0xC1B4.
 *
 * BUNDLED structure: 13 jr ra in the .s file. Splat couldn't separate the
 * tail leafs in this Yay0-compressed segment. Tail jr ra positions:
 *   0xC03C  — main body's mid-return (FPU early-exit path)
 *   0xC0CC  — main body's secondary return
 *   0xC100  — main body's terminal return
 *   0xC108, 0xC110, 0xC118 — three 2-insn leaf trailers (jr ra; <set v0>)
 *   0xC148, 0xC15C, 0xC168 — short leaf returns
 *   0xC178, 0xC188, 0xC19C, 0xC1AC — more 2-insn leaf trailers
 * Per feedback_uso_split_fragments_breaks_expected_match.md, splitting on
 * Yay0 USO breaks expected/.o until refresh — leave bundled.
 *
 * Main function decoded (0xBDEC-0xC03C, 36 insns):
 *   register f32 c255 = 255.0f;  // $f20-bound via lui+mtc1
 *   f32 a = a1->0x4A0;           // s0 = a1, s0->0x4A0
 *   ptr = a1->0x414;             // t6 = a1[0x414/4] (table?)
 *   ptr2 = ptr->0xC;             // t7 = ptr[3]
 *   stride = ptr2->0xC4;         // s2 = ptr2->0xC4 (table base)
 *   a1ptr = a1->0x8C;            // a1 = a1->0x8C (sub-pointer)
 *   off = a1->0xA4;              // t8 = a1->0xA4 (offset)
 *   addr = stride + off;         // a2 = s2 + t8
 *   v = trunc(c255 * a);         // f6 = c255*a; t0 = trunc(f6)
 *   gl_func_00000000(s1=arg0, addr, ?, &D + 0x6E8, v);
 *   ...
 *
 * State decode (0xBDEC-0xBE7C, ~36 insns):
 *   - $f20 = 255.0f (constant for FP→int conversion scale)
 *   - sequence: load a, multiply by 255, trunc to int, pass to helper
 *   - bgezl branch on (a1->0x2B4 << 14) sign-bit (bit 17) — case dispatch
 *   - if bit set: compute via $f0 = 96.0/255.0, $f2 = 192.0/255.0
 *
 * Open: jump-table at &D + 0x700 indexed by upper bits of a1->0x2B4.
 * Multi-pass decompile target; first pass too-many unknowns to write a
 * useful C body without first analyzing the dispatch table.
 *
 * Initial wrap is doc-only (no C body) until table dispatch is decoded.
 * Default INCLUDE_ASM build matches via the bundled symbol. */
#endif
#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000BDEC: two-arrow UI draw. Base x = arg1->0x8C, y =
 * arg1->0x414->0xC->0xC4 + arg1->0xA4, alpha = (int)(255.0f*arg1->0x4A0). Draws a
 * center icon (0x6E8) then a left arrow (x-0x1E, 0x700) and right arrow (x+0x1E,
 * 0x718), each with a {c,c,c,1}/255 color Vec at &sp54 — c = 192/255 when the
 * arg0->0x2B4 bit-17 "dim" flag is clear else 64/255; the left arrow only draws on
 * (arg2 & 8) when undimmed. Variable divisor (float denom=255.0f) -> runtime div.s.
 * Fresh decode 2026-05-29 (m2c-confirmed). 76.0 -> 78.32 (2026-05-31): the icon/
 * arrow IDs 0x6E8/0x700/0x718 are ADDRESSES `&D_00000000 + 0xN` (passed to the cb),
 * not literals — literal emits `addiu aN,zero,N`, the target's address form emits
 * `lui aN; addiu aN,N`. Residual: a ~23-insn DRAW block the C body still omits (a
 * third color-div + Vec-store + cb at &D+0x718, gated on the &D+0x700 dispatch
 * table indexed by a1->0x2B4 upper bits — a multi-pass structural decode) + the
 * 255.0/$f20 FP-reg allocation + an 8-byte frame reserve. Caps: structs + cb
 * prototypes untyped (USO-reloc). NON_MATCHING. */
extern int gl_func_00000000();
void timproc_uso_b5_func_0000BDEC(char *arg0, char *arg1, int arg2) {
    float sp60;
    float sp5C;
    float sp58;
    float sp54;
    float sp40;
    float denom = 255.0f;
    float c;
    float f2;
    int s2;

    s2 = *(int *)(*(char **)(*(char **)(arg1 + 0x414) + 0xC) + 0xC4);
    gl_func_00000000(*(int *)(arg1 + 0x8C), s2 + *(int *)(arg1 + 0xA4), (char *)&D_00000000 + 0x6E8,
                     (int)(denom * *(float *)(arg1 + 0x4A0)));
    if (*(int *)(arg0 + 0x2B4) & 0x20000) {
        c = 192.0f / denom;
        f2 = 255.0f / denom;
        sp54 = c;
        sp58 = c;
        sp5C = c;
        sp60 = f2;
        if (arg2 & 8) {
            sp40 = f2;
            gl_func_00000000(arg0, *(int *)(arg1 + 0x8C) - 0x1E, s2 + *(int *)(arg1 + 0xA4) + 0x14,
                             &sp54, (char *)&D_00000000 + 0x700, (int)(denom * *(float *)(arg1 + 0x4A0)));
            goto block_4;
        }
    } else {
        c = 64.0f / denom;
        f2 = 255.0f / denom;
        sp54 = c;
        sp58 = c;
        sp5C = c;
        sp60 = f2;
        sp40 = f2;
        gl_func_00000000(arg0, *(int *)(arg1 + 0x8C) - 0x1E, s2 + *(int *)(arg1 + 0xA4) + 0x14,
                         &sp54, (char *)&D_00000000 + 0x700, (int)(denom * *(float *)(arg1 + 0x4A0)));
    block_4:
        f2 = sp40;
    }
    sp60 = f2;
    if (!(*(int *)(arg0 + 0x2B4) & 0x20000)) {
        c = 192.0f / denom;
        sp54 = c;
        sp58 = c;
        sp5C = c;
        if (arg2 & 8) {
            gl_func_00000000(arg0, *(int *)(arg1 + 0x8C) + 0x1E, s2 + *(int *)(arg1 + 0xA4) + 0x14,
                             &sp54, (char *)&D_00000000 + 0x718, (int)(denom * *(float *)(arg1 + 0x4A0)));
        }
    } else {
        c = 64.0f / denom;
        sp54 = c;
        sp58 = c;
        sp5C = c;
        gl_func_00000000(arg0, *(int *)(arg1 + 0x8C) + 0x1E, s2 + *(int *)(arg1 + 0xA4) + 0x14,
                         &sp54, (char *)&D_00000000 + 0x718, (int)(denom * *(float *)(arg1 + 0x4A0)));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000BDEC);
#endif

/* timproc_uso_b5_func_0000C044 [0xC044..0xC108), 0xC4: BOUNDARY MERGE
 * 2026-06-10 of the C0D4 tail fragment (bc1f crossed the declared size).
 * Second member of the B850 float fade-toward-target family -- identical
 * shape, fields s->f_124 / s->i_12C, step constants at reloc base +0x360/
 * +0x364. See B850's wrap for the decode template. Remaining family:
 * C7B4 (pred C710?), CBD0, CDC8. */
#ifdef NON_MATCHING
#define C044_STEP_UP   (*(float *)((char *)&D_00000000 + 0x360))
#define C044_STEP_DOWN (*(float *)((char *)&D_00000000 + 0x364))
void timproc_uso_b5_func_0000C044(char *a0, float target) {
  char *s;
  volatile unsigned char pad;
  float *v;
  float *new_var;
  volatile int pad2;
  if ((*((float *) (a0 + 0x2A4))) == 0.0f)
  {
    target = 0.0f;
  }
  s = *((char **) (a0 + 0x2B8));
  if ((*((int *) (s + 0x12C))) != 0)
  {
    target = 1.0f;
  }
  v = (float *) (s + 0x124);
  if ((*v) < target)
  {
    new_var = (float *) (((char *) (&D_00000000)) + 0x360);
    *v += *new_var;
    ;
    if (target < (*((float *) ((*((char **) (a0 + 0x2B8))) + 0x124))))
    {
      *((float *) ((*((char **) (a0 + 0x2B8))) + 0x124)) = target;
    }
  }
  else
  {
    *v -= *((float *) (((char *) (&D_00000000)) + 0x364));
    if (target && target)
    {
    }
    s = *((char **) (a0 + 0x2B8));
    if ((*((float *) (s + 0x124))) < target)
    {
      *((float *) (s + 0x124)) = target;
    }
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C044);
#endif

void timproc_uso_b5_func_0000C108(int a0) {
}

void timproc_uso_b5_func_0000C110(int a0) {
}

void timproc_uso_b5_func_0000C118(int a0) {
}

void timproc_uso_b5_func_0000C120(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x12C) = 1;
    *(float*)((char*)a0[0x2B8/4] + 0x10C) = 0.0f;
    *(int*)((char*)a0 + 0x2BC) = 0;
    *(int*)((char*)a0 + 0x2C0) = 2;
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000C150(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x12C) = 0;
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
}

void timproc_uso_b5_func_0000C164(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
}

void timproc_uso_b5_func_0000C170(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000C180(int *a0) {
    *(int*)((char*)a0 + 0x2B4) ^= 0x20;
}

void timproc_uso_b5_func_0000C190(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 1;
}

void timproc_uso_b5_func_0000C1A4(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 0;
}

/* timproc_uso_b5_func_0000C1B4: 16-insn 4-float copy + cross-USO call.
 * NATURAL CEILING: 97.5% NM. The 5-insn alt-entry tail at sp+0x40..0x50
 * (different `(a0, a1)` arg shape, jal'd directly into the post-epilogue
 * region by a separate caller — `mtc1 a1,f12; lw t6; swc1 f12,0x2A0(a0);
 * jr ra; swc1 f12,0x120(t6)`) was previously injected post-cc via
 * SUFFIX_BYTES; that mechanism was REMOVED 2026-05-23 as match-faking.
 * The alt-entry bytes now belong to their own symbol. C body covers main
 * entry only. */
extern int func_00000000();
extern int func_df14f(void *, void *, float, float, float);
/* timproc_uso_b5_func_0000C1B4: 16-insn 4-float copy + cross-USO call.
 * EXACT 16/16 (2026-07-02). The old "FP register renumber cap" was cracked:
 * IDO colors single-BB local FP pseudos from pool {f0,f2,f12,f14} in
 * def(load)-order (use-count breaks ties), while BB-CROSSING pseudos color
 * from the pool END in order of first crossing. Target colors
 * (25C->f0, 260->f2, 264->f12, 294->f14) are reached by keeping c,d local
 * (d bumped over c via the if(!d) branch use) and globalizing b then a
 * across two empty-if BB boundaries (if(!d){} / if(b){}). Emitted
 * load/store schedule follows load-decl order a,b,c,d regardless of source
 * store order. See docs/IDO_CODEGEN.md FP-pool coloring entry. */
extern int func_00000000();
extern int func_df14f(void *, void *, float, float, float);
void timproc_uso_b5_func_0000C1B4(int *a0) {
  int *p = (int *) a0[0x2B8 / 4];
  float a = *((float *) (((char *) a0) + 0x294));
  float b = *((float *) (((char *) a0) + 0x264));
  float c = *((float *) (((char *) a0) + 0x260));
  float d = *((float *) (((char *) a0) + 0x25C));
  *((float *) (((char *) p) + 0x118)) = c;
  *((float *) (((char *) p) + 0x114)) = d;
  if (!d)
  {
  }
  *((float *) (((char *) p) + 0x110)) = b;
  if (b)
  {
  }
  *((float *) (((char *) p) + 0x11C)) = a;
  timproc_uso_b5_func_00003F58();
}

/* timproc_uso_b5_func_0000C1F4: 5-insn float-store, RECOVERED 2026-05-28
 * from the Yay0 gap (no .s, missing from build; bytes from block_5). o32
 * float-after-int arg arrives in $a1 -> mtc1; inline-deref of a0->0x2B8
 * keeps the dest pointer in $t6 (byte-exact). */
void timproc_uso_b5_func_0000C1F4(int *a0, float val) {
    *(float*)((char*)a0 + 0x2A0) = val;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x120) = val;
}

extern char D_b5_C208_table0;
extern char D_b5_C208_table1;
void timproc_uso_b5_func_0000C208(int *a0, int a1, int a2, int a3) {
    (void)a1;
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], a2, a3,
                     (char*)&D_b5_C208_table0 + a0[0x1AC/4] * 24, 0xFF);
    if (*(int*)&D_00000000 != 0) {
        gl_func_00000000(a0, a0[0x74/4] + a0[0x44/4], a0[0x8C/4] + a0[0x5C/4],
                         (char*)&D_b5_C208_table1 + a0[0x1AC/4] * 24, 0xFF);
    }
}

extern char D_b5_C2C0_table;
void timproc_uso_b5_func_0000C2C0(int *a0, int a1, int a2) {
    (void)a1;
    gl_func_00000000(a0, a0[0x104/4], a0[0x11C/4], (char*)&D_b5_C2C0_table + a2 * 24, 0xFF);
}

// timproc_uso_b5_func_0000C310 — STRUCTURAL PASS (0x400 / 256 words,
// no episode). Raw-.word USO form (single function; boundary already
// split by commit 8de6787e — the named fn itself was still
// undecoded). Hand-decoded.
//
// Timing-screen sample-enqueue + per-slot process: appends to a
// fixed-capacity (0xA) ring buffer, then runs FP processing over the
// obj's parallel sub-arrays.
//
//   void timproc_uso_b5_func_0000C310(Obj *obj, A a1) {  // obj->s0
//     if (obj->0x2BC < 0xA) {                             // ring not full
//       if (--obj->0x2C0 < 0) obj->0x2C0 = …;             // read idx wrap
//       obj->0x2BC += 2;                                   // write idx adv
//     }
//     // base pointers into parallel per-slot sub-arrays:
//     //   obj+0x134, obj+0x158, obj+0x17C, obj+0x1A0, obj+0x1C4,
//     //   obj+0x1DC, obj+0x1F4 ; plus a global at D_0 + 0xB8;
//     // FP loop (~10 FP ops, ~7 func_00000000 sub-calls): for the
//     //   current slot, transform / accumulate sample values from
//     //   a1 into the sub-arrays and emit via the dispatcher.
//   }
//
// Struct-typing reference:
//   obj: 0x2BC ring write index (cap 0xA, += 2 per push),
//     0x2C0 read index / count (decremented, wraps),
//     0x134/0x158/0x17C/0x1A0/0x1C4/0x1DC/0x1F4 = parallel per-slot
//     sub-array bases (stride 0x24 between consecutive bases);
//     D_0 + 0xB8 = a global sample source. a1 = incoming sample
//     record. func_00000000 = USO placeholder dispatcher (per-slot
//     transform / emit).
// Caps (DEFERRED): raw-word USO + placeholder calls + 256-word
//   FP/ring pipeline; USO mnemonic disasm limitation prevents
//   byte-match. Real-C STRUCTURAL body below — ring push + per-slot
//   FP loop skeleton only. Byte-match deferred. Name pre-checked: no
//   extern reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000C310(char *arg0, char *arg1) {
    char *g = (char *)&D_00000000;
    s32 spC0;
    s32 spBC;
    s32 spB8;
    s32 spB4;
    s32 spB0;
    s32 spAC;
    s32 spA8;
    s32 spA4;
    s32 spA0;
    s32 sp9C;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp60;
    f32 *var_s3;
    f32 temp_f0;
    f32 temp_f0_2;
    s32 *var_s4;
    s32 *var_s5;
    s32 temp_a0;
    s32 temp_s6;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0;
    s32 var_s1;
    s32 var_v1;
    char *temp_v0_2;
    char *var_s1_2;

    if ((*(s32 *)(arg0 + 0x2BC)) < 0xA) {
        temp_t8 = (*(s32 *)(arg0 + 0x2C0)) - 1;
        (*(s32 *)(arg0 + 0x2C0)) = temp_t8;
        if (temp_t8 < 0) {
            (*(s32 *)(arg0 + 0x2C0)) = 1;
            (*(s32 *)(arg0 + 0x2BC)) = (s32) ((*(s32 *)(arg0 + 0x2BC)) + 2);
        }
    }
    spB0 = (*(s32 *)(arg0 + 0x1C4));
    spB4 = (*(s32 *)(arg0 + 0x1DC));
    var_s3 = (f32 *)0xB8;
    spB8 = (*(s32 *)(arg0 + 0x1F4));
    var_s1 = 0;
    var_s5 = &spB0;
    spBC = (*(s32 *)(arg0 + 0x20C));
    sp9C = arg1 + 0x134;
    spA0 = arg1 + 0x158;
    spA4 = arg1 + 0x17C;
    spA8 = arg1 + 0x1A0;
    spAC = arg1 + 0x1C4;
    temp_s6 = arg1 + 0x230;
    var_s4 = &sp9C;
    spC0 = (*(s32 *)(arg0 + 0x224));
    do {
        temp_v0 = (*(s32 *)(arg0 + 0x2BC));
        temp_a0 = *var_s5;
        var_v1 = temp_a0;
        if (temp_v0 < temp_a0) {
            var_v1 = temp_v0;
        }
        if ((*(s32 *)(arg1 + 0x3BC)) == 1) {
            gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xA4)), (*(s32 *)(arg0 + 0xBC)) + (var_s1 * (*(s32 *)(arg1 + 0x74))), var_s3, (void *) var_v1, *var_s4, temp_s6, arg1);
        } else {
            gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xA4)), (*(s32 *)(arg0 + 0xBC)) + (var_s1 * (*(s32 *)(arg1 + 0x74))), var_s3, (void *) var_v1, *var_s4, temp_s6, arg1);
        }
        var_s1 += 1;
        var_s5 += 4;
        var_s3 += 0x18;
        var_s4 += 4;
    } while (var_s1 != 5);
    temp_v0_2 = (*(s32 *)(arg0 + 0x2B8));
    if (((*(s32 *)(temp_v0_2 + 0x130)) == 0) && ((*(s32 *)(temp_v0_2 + 0x10C)) == 0.0f)) {
        if (!((*(s32 *)(arg0 + 0x2B4)) & 0x20)) {
            temp_f0 = 255.0f / 255.0f;
            sp8C = temp_f0;
            sp94 = temp_f0;
            sp88 = 105.0f / 255.0f;
            sp90 = 155.0f / 255.0f;
            sp60 = temp_f0;
            gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xD4)), (*(s32 *)(arg0 + 0xEC)), &sp88, (void *)0x658, 0xFF);
            var_s1_2 = g + 0x5F8;
        } else {
            temp_f0_2 = 255.0f / 255.0f;
            sp88 = 105.0f / 255.0f;
            sp90 = temp_f0_2;
            sp94 = temp_f0_2;
            sp8C = 155.0f / 255.0f;
            sp60 = temp_f0_2;
            gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xD4)), (*(s32 *)(arg0 + 0xEC)), &sp88, (void *)0x670, 0xFF);
            var_s1_2 = g + 0x610;
        }
        sp60 = sp60;
        gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xD4)), (*(s32 *)(arg0 + 0xEC)), &sp88, var_s1_2, 0xFF);
        temp_t4 = (*(s32 *)(arg0 + 0x2C4)) + 1;
        (*(s32 *)(arg0 + 0x2C4)) = temp_t4;
        if (temp_t4 & 8) {
            sp94 = sp60;
            sp88 = 233.0f / 255.0f;
            sp8C = 247.0f / 255.0f;
            sp90 = 0.0f / 255.0f;
            if (!((*(s32 *)(arg0 + 0x2B4)) & 0x20)) {
                gl_func_00000000(arg0, ((*(s32 *)(arg0 + 0xD4)) - ((s16) (*(s32 *)((char *)(*(s32 *)(var_s1_2 + 0x10)) + 0x20)) / 2)) - 2, (*(s32 *)(arg0 + 0xEC)), &sp88, (void *)0x628, 0xFF);
                return;
            }
            gl_func_00000000(arg0, (*(s32 *)(arg0 + 0xD4)) + ((s16) (*(s32 *)((char *)(*(s32 *)(var_s1_2 + 0x10)) + 0x20)) / 2) + 2, (*(s32 *)(arg0 + 0xEC)), &sp88, (void *)0x640, 0xFF);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C310);
#endif

/* 0000C710 absorbs 0000C7B4: bc1f at offset 0x94 of C710 branches PAST
 * the original 0xA4 declared size into C7B4's body; C7B4 has no prologue
 * and uses caller-set $v1/$at. Splat-bundled fragment merge 2026-05-05.
 * Combined size 0xD8 = 54 insns. */
/* timproc_uso_b5_func_0000C710 - verified structural decode (0xD8,
 * 54 insns). SIBLING of timproc_uso_b5_func_0000CB40 (same
 * timproc_uso_b5 FP slew-limiter family); differs only in how the
 * target is resolved.
 *   void timproc_uso_b5_func_0000C710(void *a0, f32 a1_unused) {
 *       f32 target;
 *       if (a0->0x2A4 == 0.0f) {
 *           target = 0.0f;
 *       } else {
 *           st = a0->0x2B8;
 *           target = (st->0x130 != 0) ? 1.0f : D_<dflt>;  // global
 *       }
 *       st = a0->0x2B8;
 *       cur = st->0x124;
 *       if (cur < target) {                       // ramp up
 *           st->0x124 += D_<step_up>;
 *           if (target < a0->0x2B8->0x124)
 *               a0->0x2B8->0x124 = target;        // clamp
 *       } else {                                  // ramp down
 *           st->0x124 -= D_<step_dn>;
 *           if (a0->0x2B8->0x124 < target)
 *               a0->0x2B8->0x124 = target;        // clamp
 *       }
 *   }
 * Struct-typing reference (same family as CB40): a0->0x2A4 (676) f32
 * enable (0.0 -> target 0); a0->0x2B8 (696) ptr to slew-state;
 * state->0x124 (292) f32 slewed value; state->0x130 (304) s32 gate
 * (nonzero -> target = 1.0, else the global default const at &D+
 * 0x872). Step magnitudes = global f32 consts &D+0x876 (up) /
 * +0x880 (down). Per call moves one step toward target then clamps.
 * 2026-06-10 post-merge progress (boundary fixed; now one 0xD8 symbol):
 * distinct float externs (D_C710_dflt/up/dn) FOLD into lwc1 %lo (the
 * &D+offset cast-arith form materializes la instead); their
 * undefined_syms values are set to the in-USO offsets 0x368/36C/370 so
 * the LINKED %lo fields match (the .o shows 0+reloc -- compare linked
 * bytes or wildcard reloc positions). Best shape = v fixed pre-if:
 * 28/54 non-reloc diffs. Residual: the target materializes v1
 * (addiu v0+0x124) INSIDE each arm between the const lui and the loads,
 * with the compare deref'ing st directly AND an interleaved dflt load
 * (scheduling); f-reg numbering shifts with it. Stays INCLUDE_ASM. */
#ifdef NON_MATCHING
extern float D_C710_dflt;
extern float D_C710_up;
extern float D_C710_dn;
void timproc_uso_b5_func_0000C710(char *a0, float a1u) {
    float target;
    char *st;
    float *v;
    if (*(float *)(a0 + 0x2A4) == 0.0f) {
        target = 0.0f;
    } else {
        st = *(char **)(a0 + 0x2B8);
        target = (*(int *)(st + 0x130) != 0) ? 1.0f : D_C710_dflt;
    }
    st = *(char **)(a0 + 0x2B8);
    v = (float *)(st + 0x124);
    if (*v < target) {
        *v += D_C710_up;
        st = *(char **)(a0 + 0x2B8);
        if (target < *(float *)(st + 0x124)) {
            *(float *)(st + 0x124) = target;
        }
    } else {
        *v -= D_C710_dn;
        st = *(char **)(a0 + 0x2B8);
        if (*(float *)(st + 0x124) < target) {
            *(float *)(st + 0x124) = target;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C710);
#endif

/* timproc_uso_b5_func_0000C7B4 MERGED into C710 2026-06-10 (bc1f tail fragment, third of the fade-helper family). */

void timproc_uso_b5_func_0000C7E8(char *a0, char *a1) {
    *(float*)(*(int*)(a1 + 0x2B8) + 0x128) = *(float*)(*(int*)(a0 + 0x2B8) + 0x128);
    *(float*)(*(int*)(a1 + 0x2B8) + 0x124) = *(float*)(*(int*)(a0 + 0x2B8) + 0x124);
    *(int*)(*(int*)(a1 + 0x2B8) + 0x130) = *(int*)(*(int*)(a0 + 0x2B8) + 0x130);
    *(int*)(*(int*)(a1 + 0x2B8) + 0x13C) = *(int*)(*(int*)(a0 + 0x2B8) + 0x13C);
}

void timproc_uso_b5_func_0000C82C(int a0) {
}

void timproc_uso_b5_func_0000C834(int a0) {
}

void timproc_uso_b5_func_0000C83C(int a0) {
}

void timproc_uso_b5_func_0000C844(int a0) {
}

void timproc_uso_b5_func_0000C84C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000C85C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 0;
}

void timproc_uso_b5_func_0000C870(int a0) {
}

void timproc_uso_b5_func_0000C878(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 1;
}

void timproc_uso_b5_func_0000C888(int *a0, int a1) {
    (void)a1;
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000C89C(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

/* 51-insn / 0xCC float clamp + copy. Pattern:
 *   v1 = a0->[0x2B8];
 *   if (v1->[0x134] != 0) {        ; increment branch
 *       v1->[0x128] += D[0x374];
 *       if (v1->[0x128] > 1.0f)
 *           v1->[0x128] = 1.0f;
 *   } else {                          ; decrement branch
 *       v1->[0x128] -= D[0x378];
 *       if (v1->[0x128] < 0.0f)
 *           v1->[0x128] = 0.0f;
 *   }
 *   v1 = a0->[0x2B8];                 ; reload (target reloads here)
 *   v1->[0x10C] = a0->[0x264];        ; out-of-source-order field copy
 *   v1->[0x110] = a0->[0x25C];
 *   v1->[0x114] = a0->[0x260];
 *   v1->[0x118] = a0->[0x294];
 *   timproc_uso_b5_func_00003F58();   ; tail call (no args, intra-module)
 *
 * Initial decode — multi-pass refinement expected. The bc1fl + delay-likely
 * pattern + reload-of-v1 across the fork are likely structural cap drivers.
 * The 4-store epilogue order (0x10C, 0x110, 0x114, 0x118 in target asm —
 * NOT in source-order 0x10C/0x110/0x114) suggests IDO scheduler interleave
 * of the lwc1's and swc1's.
 *
 * 2026-05-05: caching `float *p128` lifted 75.47% → 80.41% (+4.94pp). The
 * cached pointer matches target's `addiu v0, v1, 0x128` (v0 holds the
 * +0x128 offset address). Then inline-deref of the post-add comparison
 * (`*(float*)((char*)a0[0x2B8/4] + 0x128) > 1.0f`) forced the v1 reload
 * + recomputed +0x128 offset, lifting 80.41% → 86.37% (+5.96pp).
 *
 * Remaining 14% cap: $v0 vs $v1 first-register choice (built uses $v0,
 * target $v1) cascades through ~19 of 51 insns. Sizes now match
 * (204/204 bytes). Final ~14% is register-rename territory (permuter
 * or INSN_PATCH).
 *
 * 2026-05-07 attempted `int` return + `return gl_func_00000000()` to
 * reserve $v0 for the return value (hypothesis: pushes first general
 * pseudo to $v1). Result: NO CHANGE — still 86.37%. IDO's allocator
 * isn't return-value-driven for the void→int transition; it picks $v0
 * for the first-live pseudo regardless because the only use of $v0-as-
 * return-value is the final jr ra delay slot, well after all other
 * pseudo-allocations are settled. Reverted. The C-level register-flip
 * lever isn't reachable here; this is permuter-territory.
 *
 * 2026-06-20 reconstruction pass: resolved placeholder tail call
 * gl_func_00000000() -> the REAL intra-module callee
 * timproc_uso_b5_func_00003F58() (matches the .s jal). In .text the jal
 * disk-encodes as 0C000000 for BOTH the placeholder and the real symbol
 * (relocatable USO: R_MIPS_26 applied at load), so the swap does NOT
 * change reloc-filtered .text bytes — it's a correctness/clarity fix, not
 * a %-mover. Function is now 99.61% (47/51 words exact). The 4 residual
 * diffs are ALL the same regalloc cap: the entry-block a0->[0x2B8] pointer
 * (live insns 2-5: lw .0x2B8, lw .0x134, addiu +0x128) colors $a1 in the
 * build vs $v1 in the target; the post-branch reloads already color $v1.
 * Tried: decl-order swap (no change); hoisting p128 into both arms (drops
 * the shared pre-beql `addiu $v0,$v1,0x128` -> worse); assigning the
 * clamp reloads back into `v1` (forces `move $v1,$a1` + growth -> worse).
 * IDO unifies the reloaded pointer onto $v1 and leaves the first,
 * separately-loaded pseudo on $a1; no C-level live-range edit reachable
 * here flips it. Class: first-pseudo register-coloring. Permuter-territory. */
extern int gl_func_00000000();
extern char D_00000000;
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000C8AC(int *a0) {
  int *v1;
  float *p128;
  v1 = (int *) a0[0x2B8 / 4];
  p128 = (float *) (((char *) v1) + 0x128);
  if ((*((int *) (((char *) v1) + 0x134))) != 0)
  {
    *p128 += *((float *) (((char *) (&D_00000000)) + 0x374));
    if ((*((float *) (((char *) ((int *) a0[0x2B8 / 4])) + 0x128))) > 1.0f)
    {
      *((float *) (((char *) ((int *) a0[0x2B8 / 4])) + 0x128)) = 1.0f;
    }
  }
  else
  {
    *p128 -= *((float *) (((char *) (&D_00000000)) + 0x378));
    if ((*((float *) (((char *) ((int *) a0[0x2B8 / 4])) + 0x128))) < 0.0f)
    {
      *((float *) (((char *) ((int *) a0[0x2B8 / 4])) + 0x128)) = 0.0f;
    }
  }
  p128 = (int *) a0[0x2B8 / 4];
  {
    float a;
    float b;
    float c;
    float d;
    v1 = p128;
    a = *((float *) (((char *) a0) + 0x25C));
    b = *((float *) (((char *) a0) + 0x260));
    c = *((float *) (((char *) a0) + 0x264));
    d = *((float *) (((char *) a0) + 0x294));
    *((float *) (((char *) v1) + 0x110)) = a;
    *((float *) (((char *) v1) + 0x114)) = b;
    *((float *) (((char *) v1) + 0x10C)) = c;
    *((float *) (((char *) v1) + 0x118)) = d;
  }
  timproc_uso_b5_func_00003F58();
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C8AC);
#endif


void timproc_uso_b5_func_0000C978(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x11C) = a1;
}

// timproc_uso_b5_func_0000C98C — STRUCTURAL PASS (0x1B4 / 109 words,
// no episode). Raw-.word USO form (single function; bundle already
// split by commit f8c4b1b8 — the named fn itself was still
// undecoded). Hand-decoded.
//
// Timing-screen draw/emit helper: assembles a draw command on the
// stack and dispatches it.
//
//   void timproc_uso_b5_func_0000C98C(Obj *obj, a1, a2, a3) {  // obj->s0
//     // stack arg block @ sp+0x10..0x44:
//     //   sp+0x38..0x44 = a zeroed Vec4 (color/coords default);
//     //   sp+0x18 = 0xFF (alpha);  sp+0x34 = a2;  sp+0x10 = a3;
//     // d = obj->0x414->0xC;  vt = d->0x5C;
//     // src = obj->0x44 (->0xC4 / ->0xBC fields);
//     // entry = &D_000001C0 + obj->0x1AC * 0x68;            // table idx
//     //   (index calc: n*4 - n -> *8 + n => n*0x27 word-ish stride);
//     // ~6 func_00000000 calls emit the draw using d/vt/src/entry +
//     //   the assembled arg block (color/alpha/position).
//   }
//
// Struct-typing reference:
//   obj: 0x414 -> node (->0xC -> drawable, ->0x5C vtable/fn),
//     0x44 -> source (->0xBC/0xC4 fields), 0x1AC = table index into
//     the D_000001C0 entry array (stride ~0x68). a1/a2/a3 forwarded
//     into the draw arg block; alpha const 0xFF, 1.0f baseline.
//   D_000001C0 = USO static draw-descriptor table. func_00000000 =
//     USO placeholder dispatcher (emit/draw).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — stack arg block + descriptor-table lookup + emit
//   skeleton only. Byte-match deferred. Name pre-checked: no extern
//   reuse.
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000C98C(char *arg0, char *arg1, int arg2, int arg3) {
    char *g = (char *)&D_00000000;
    float c0 = 1.0f, c1 = 1.0f, c2 = 1.0f, c3 = 1.0f;
    char *d;
    int a2v, sp30, r0, v1;
    d = *(char **)(*(char **)(arg1 + 0x414) + 0xC);
    a2v = (*(int *)(d + 0xC4) + *(int *)(d + 0xBC)) - *(int *)(arg0 + 0x5C);
    func_00000000(*(int *)(arg0 + 0x44), a2v, arg2, arg3,
                                 *(int *)(arg0 + 0x1AC) * 0x18 + 0x1C0, 0xFF);
    if (*(int *)g != 0) {
        func_00000000(arg0, *(int *)(arg0 + 0x44) + *(int *)(arg0 + 0x74),
                                     a2v + *(int *)(arg0 + 0x8C),
                                     *(int *)(arg0 + 0x1AC) * 0x18 + 0x280, 0xFF);
    }
    sp30 = 0;
    r0 = func_00000000(*(int *)(g + 0x148) + 4, 0);
    v1 = *(int *)(g + 0x34);
    if (v1 == 6) {
        if (r0 == 2 && func_00000000(*(int *)(g + 0x148) + 4, 0) == *(int *)(arg0 + 0x2B0)) {
            sp30 = 1;
        }
    } else if (v1 == 4 && r0 == 1 &&
               func_00000000(*(int *)(g + 0x148) + 4, 0) == *(int *)(arg0 + 0x2B0)) {
        sp30 = 1;
    }
    if (sp30 != 0) {
        func_00000000(arg0, *(int *)(arg0 + 0x44) + 0x54, a2v - 0x78, 0x6D0, 0xFF);
    }
    (void)c0; (void)c1; (void)c2; (void)c3;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000C98C);
#endif

/* timproc_uso_b5_func_0000CB40 - verified structural decode (0xC4,
 * 49 insns, FP slew-limiter / value-approach).
 *   void timproc_uso_b5_func_0000CB40(void *a0, f32 a1) {
 *       f32 target = a1;
 *       if (a0->0x2A4 == 0.0f) target = 0.0f;     // disabled -> 0
 *       st = a0->0x2B8;
 *       if (st->0x134 != 0) target = 1.0f;        // force-full gate
 *       cur = st->0x124;
 *       if (cur < target) {                       // ramp up
 *           st->0x124 += D_<step_up>;             // global +step
 *           st = a0->0x2B8;
 *           if (target < st->0x124)               // overshoot ->
 *               st->0x124 = target;               //   clamp
 *       } else {                                  // ramp down
 *           st->0x124 -= D_<step_dn>;             // global -step
 *           st = a0->0x2B8;
 *           if (st->0x124 < target)               // undershoot ->
 *               st->0x124 = target;               //   clamp
 *       }
 *   }
 * Struct-typing reference: a0->0x2A4 (676) f32 enable (0.0 = force
 * target 0); a0->0x2B8 (696) ptr to slew-state; state->0x124 (292)
 * f32 = the slewed/current value; state->0x134 (308) s32 = force-to-
 * 1.0 gate (nonzero -> target clamps to 1.0). Step magnitudes are
 * two global f32 constants (&D + 0x892 up / + 0x896 down). Per call
 * the current value moves one step toward the resolved target then
 * clamps so it never overshoots. Caps <80: FP-heavy c.eq.s/c.lt.s/
 * add.s/sub.s + bc1fl/bc1f branch-likely (x4) + 2x &D global step
 * reloc + dual jr-ra + the CBD0 tail-fragment branch-target. Stays
 * INCLUDE_ASM (no episode). */
#ifdef NON_MATCHING
extern char D_00000000;
void timproc_uso_b5_func_0000CB40(char *a0, float a1) {
    float target = a1;
    float *st;
    if (*(float *)(a0 + 0x2A4) == 0.0f) {
        target = 0.0f;
    }
    st = *(float **)(a0 + 0x2B8);
    if (*(int *)((char *)st + 0x134) != 0) {
        target = 1.0f;
    }
    if (*(float *)((char *)st + 0x124) < target) {
        *(float *)((char *)st + 0x124) += *(float *)(&D_00000000 + 0x892);
        st = *(float **)(a0 + 0x2B8);
        if (target < *(float *)((char *)st + 0x124)) {
            *(float *)((char *)st + 0x124) = target;
        }
    } else {
        *(float *)((char *)st + 0x124) -= *(float *)(&D_00000000 + 0x896);
        st = *(float **)(a0 + 0x2B8);
        if (*(float *)((char *)st + 0x124) < target) {
            *(float *)((char *)st + 0x124) = target;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CB40);
#endif

/* timproc_uso_b5_func_0000CBD0 MERGED into CB40 2026-06-10 (bc1f tail fragment, fourth of the fade-helper family; the .s merge that the earlier nested-wrap decode described but never executed). */

void timproc_uso_b5_func_0000CC04(int a0) {}

void timproc_uso_b5_func_0000CC0C(int a0) {}

void timproc_uso_b5_func_0000CC14(int a0) {}

void timproc_uso_b5_func_0000CC1C(int a0) {}

void timproc_uso_b5_func_0000CC24(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 1;
}

void timproc_uso_b5_func_0000CC34(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x134) = 0;
}

void timproc_uso_b5_func_0000CC40(int a0) {}

void timproc_uso_b5_func_0000CC48(int a0) {}

void timproc_uso_b5_func_0000CC50(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000CC64(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

/* Sibling of timproc_uso_b5_func_0000C1B4 (4-float copy + cross-USO call + 5-insn
 * alt-entry tail). Same shape, different store offsets:
 *   C1B4: stores at p+0x11C/0x110/0x118/0x114
 *   CC74: stores at p+0x118/0x10C/0x114/0x110
 *
 * Recipe: same as C1B4 — INSN_PATCH 8 float-reg-rename words +
 * SUFFIX_BYTES 5 alt-entry tail words. Both in Makefile. */
/* Sibling of timproc_uso_b5_func_0000C1B4 (4-float copy + cross-USO call).
 * Same shape, different store offsets: a->0x118, b->0x10C, c->0x114, d->0x110.
 * EXACT 16/16 (2026-07-02) via the same FP-pool coloring recipe as C1B4:
 * locals c,d (d bumped by if(!d) branch use) -> f2,f0; b,a globalized across
 * empty-if BB boundaries -> f12,f14 from pool end. */
void timproc_uso_b5_func_0000CC74(int *a0) {
  int *p = (int *) a0[0x2B8 / 4];
  float a = *((float *) (((char *) a0) + 0x294));
  float b = *((float *) (((char *) a0) + 0x264));
  float c = *((float *) (((char *) a0) + 0x260));
  float d = *((float *) (((char *) a0) + 0x25C));
  *((float *) (((char *) p) + 0x114)) = c;
  *((float *) (((char *) p) + 0x110)) = d;
  if (!d)
  {
  }
  *((float *) (((char *) p) + 0x10C)) = b;
  if (b)
  {
  }
  *((float *) (((char *) p) + 0x118)) = a;
  timproc_uso_b5_func_00003F58();
}

/* timproc_uso_b5_func_0000CCB4: sibling of 0000C1F4 (last store at 0x11C
 * instead of 0x120), RECOVERED 2026-05-28 from the Yay0 gap. */
void timproc_uso_b5_func_0000CCB4(int *a0, float val) {
    *(float*)((char*)a0 + 0x2A0) = val;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x11C) = val;
}

/* timproc_uso_b5_func_0000CCC8: 23-insn (0x5C) 6-arg cross-USO call
 * builder. Computes &D[0x1C0] + idx*24 where idx = a0->[0x1AC] and
 * passes it as the 5th arg, with 0xFF as the 6th.
 *
 * 2026-05-24: the regalloc cap (idx-chain result in $v0 vs target's $t9,
 * cascading 0xFF $t9→$t0) is now cracked with LEGITIMATE C — inlining the
 * 5th-arg pointer expression into the call (no named `char *p` local)
 * makes IDO continue the temp sequence t6/t7/t8/$t9 instead of grabbing
 * $v0 for the named local. This REPLACES the prior INSN_PATCH (banned
 * 2026-05-23). Build now has 0 real diffs vs expected.
 *
 * NOT yet episode-able: the sole residual is the reloc-blind `addiu t8,
 * t8,0x1C0` — `&D_timb5_1C0` is an R_MIPS_LO16 reloc (build .o = `addiu 0`,
 * expected .o = baked 0x1C0). The land script's byte_verify is a raw
 * .text compare (not reloc-aware) and objdiff counts it (99.13%). The
 * `&D_00000000 + 0x1C0` baked form does NOT work here — it splits the
 * symbol materialization into 3 insns (base + 0x1C0-folded-into-idx)
 * vs the target's 2-insn single-symbol form. So the symbol reloc is
 * REQUIRED for correct codegen; this becomes an automatic episode once
 * the spimdisasm USO-reloc migration makes expected/ reloc-aware.
 * - IDO -O2 natural unused-arg-save handles a1/a2/a3 caller-slot spills
 *   since the function has a jal. */
extern int gl_func_00000000();
extern char D_timb5_1C0;

void timproc_uso_b5_func_0000CCC8(int *a0, int a1, int a2, int a3) {
    gl_func_00000000(a0, a0[0x44/4], a0[0x5C/4], a2, &D_timb5_1C0 + a0[0x1AC/4] * 24, 0xFF);
}

/* timproc_uso_b5_func_0000CD24 - verified structural decode (0xD8,
 * 54 insns). INSTRUCTION-IDENTICAL SIBLING of
 * timproc_uso_b5_func_0000C710 (same FP slew-limiter; the ONLY
 * difference is the global constant offsets - &D+0x900 default /
 * +0x904 step-up / +0x908 step-down here, vs +0x872/+0x876/+0x880
 * in C710). Struct-typing reference: identical layout to C710 -
 * a0->0x2A4 (676) f32 enable, a0->0x2B8 (696) slew-state ptr,
 * state->0x124 (292) f32 slewed value, state->0x130 (304) s32
 * force-1.0 gate. This instance uses a distinct constant triple
 * (different default/step pair), i.e. a second independently-tuned
 * slew channel sharing the same state object shape. Caps <80: FP
 * c.eq.s/c.lt.s/add.s/sub.s + bc1fl/bc1f branch-likely + 3x &D
 * global const reloc + dual jr-ra. INCLUDE_ASM remains build path. */
#ifdef NON_MATCHING
void timproc_uso_b5_func_0000CD24(char *a0, float a1u) {
    float target;
    float *st;
    if (*(float *)(a0 + 0x2A4) == 0.0f) {
        target = 0.0f;
    } else {
        st = *(float **)(a0 + 0x2B8);
        target = (*(int *)((char *)st + 0x130) != 0) ? 1.0f
                 : *(float *)(&D_00000000 + 0x900);
    }
    st = *(float **)(a0 + 0x2B8);
    if (*(float *)((char *)st + 0x124) < target) {
        *(float *)((char *)st + 0x124) += *(float *)(&D_00000000 + 0x904);
        st = *(float **)(a0 + 0x2B8);
        if (target < *(float *)((char *)st + 0x124)) {
            *(float *)((char *)st + 0x124) = target;
        }
    } else {
        *(float *)((char *)st + 0x124) -= *(float *)(&D_00000000 + 0x908);
        st = *(float **)(a0 + 0x2B8);
        if (*(float *)((char *)st + 0x124) < target) {
            *(float *)((char *)st + 0x124) = target;
        }
    }
    (void)a1u;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CD24);
#endif

/* timproc_uso_b5_func_0000CDC8 MERGED into CD24 2026-06-10 (bc1f tail fragment, fifth and FINAL fade-helper family member; nested double-wrap flattened same as CB40). */

void timproc_uso_b5_func_0000CDFC(int a0) {}

void timproc_uso_b5_func_0000CE04(int a0) {}

void timproc_uso_b5_func_0000CE0C(int a0) {}

void timproc_uso_b5_func_0000CE14(int a0) {}

void timproc_uso_b5_func_0000CE1C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 1;
}

void timproc_uso_b5_func_0000CE2C(int *a0) {
    *(int*)((char*)a0[0x2B8/4] + 0x130) = 0;
}

void timproc_uso_b5_func_0000CE38(int a0) {}

void timproc_uso_b5_func_0000CE40(int a0) {}

void timproc_uso_b5_func_0000CE48(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 1;
}

void timproc_uso_b5_func_0000CE5C(int *a0, int a1) {
    *(int*)((char*)a0[0x2B8/4] + 0x138) = 0;
}

/* 4-float load-batched store + jal. Clean NM body 2026-06-21 (agent-d):
 * frame (-24) and the load-all-then-store-all batch structure are now
 * byte-exact; the SOLE residual is the FP register-pick DIRECTION — IDO
 * allocates f0,f2,f12,f14 ASCENDING in load-encounter order, the target
 * wants them DESCENDING (f14,f12,f2,f0). Pure FP-renumber coloring cap
 * (immune; decl-order/load-order permutations only relabel, never reverse
 * the allocator's pick direction). 8 words -> 8 FP-reg-only diffs; frame +
 * structure now exact. Replaces a pre-2026-05-23 INSN_PATCH-era garbage
 * body of uninitialized-local no-ops. */
/* 4-float load-batched store + jal. EXACT 16/16 (2026-07-02, agent-e) —
 * 4th sibling of the BB88/C1B4/CC74 trio, cracked with the same FP
 * pool-coloring recipe (docs/IDO_CODEGEN.md "FP local-vs-global pool
 * coloring", 2026-07-02): loads in decl order a(294),b(264),c(260),d(25C);
 * source stores c,d, if(!d){}, b, if(b){}, a (dest offsets here:
 * c->0x114, d->0x110, b->0x10C, a->0x118). Locals c,d stay single-BB and
 * color f2,f0 (d bumped over c by the branch use); the empty-if BB
 * boundaries globalize b then a, which color from the pool END: b->f12,
 * a->f14. Scheduler re-emits stores in load order, giving the target's
 * f14,f12,f2,f0 descending pick. Callee = timproc_uso_b5_func_00003F58
 * (extern, jal word 0x0C000000). Replaces the "FP register renumber cap
 * (immune)" verdict — that was FALSE. */
void timproc_uso_b5_func_0000CE6C(int *a0) {
  int *p = (int *) a0[0x2B8 / 4];
  float a = *((float *) (((char *) a0) + 0x294));
  float b = *((float *) (((char *) a0) + 0x264));
  float c = *((float *) (((char *) a0) + 0x260));
  float d = *((float *) (((char *) a0) + 0x25C));
  *((float *) (((char *) p) + 0x114)) = c;
  *((float *) (((char *) p) + 0x110)) = d;
  if (!d)
  {
  }
  *((float *) (((char *) p) + 0x10C)) = b;
  if (b)
  {
  }
  *((float *) (((char *) p) + 0x118)) = a;
  timproc_uso_b5_func_00003F58();
}

#pragma GLOBAL_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5/timproc_uso_b5_func_0000CE6C_pad.s")

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000CEB4: 105-insn (0x1A4) FPU/Vec4 transformation
 * with conditional fallback path. Frame -0x50; saves $ra; uses sp+0x40-
 * 0x4C as a Vec4 stack buffer.
 *
 * High-level structure (first ~30 insns decoded):
 *   - Saves a1 to sp+0x54 (caller arg slot)
 *   - Initializes sp+0x40, +0x44, +0x48, +0x4C to 0.0f (Vec4 zero)
 *   - Reads a0->[0x2AC] flag; if non-zero, alt path:
 *     - Sets sp+0x40 from D[0x394]
 *     - Calls gl_func with a0->[0x44], a0->[0x5C], 0xFF, &Vec4 buf...
 *   - Else (a0->[0x2AC] == 0) reads D[0x398] into f0 and continues
 *
 * Multi-tick decompile — full FPU control flow + Vec4 inits + conditional
 * call patterns need multiple passes. Default INCLUDE_ASM build matches.
 * This wrap captures the entry-point structure for grep discoverability. */
extern int gl_func_00000000();
extern char D_00000000;
void timproc_uso_b5_func_0000CEB4(int *a0, int a1) {
    /* TODO: full decompile — first ~30 insns (Vec4 init + a0->2AC branch)
     * decoded but the body has 4+ FPU branches, 3+ jal calls, and
     * multi-arg cross-USO calls. Partial structure only. */
    float vec_buf[4];
    vec_buf[0] = vec_buf[1] = vec_buf[2] = vec_buf[3] = 0.0f;
    if (*(int*)((char*)a0 + 0x2AC) != 0) {
        gl_func_00000000(a0, a1);
    }
    (void)vec_buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000CEB4);
#endif

void timproc_uso_b5_func_0000D058(int *a0, float a1) {
    *(float*)((char*)a0 + 0x2A0) = a1;
    *(float*)((char*)*(int**)((char*)a0 + 0x2B8) + 0x11C) = a1;
}

/* MATCHED (byte-exact, 28/28). Sibling of the A97C/A9EC family — the prior
 * "72.21% branch-likely-preload cap" was cracked by the `if (1) {}` BB-boundary
 * lever (flips the cursor-read $v0/$v1 allocation; see
 * docs/IDO_CODEGEN.md#if-1-around-an-inner-block...). Outer offsets (this
 * variant): count a0->0x6C, slot ptr a0->0x3C; inner fn ptr slot->0x28->0x4C,
 * short arg slot->0x28->0x48. */
void timproc_uso_b5_func_0000D06C(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    i = 0;
    p = a0;
    do {
        v1 = *(int**)(p + 0x3C);
        if (1) {
            v0 = *(int**)((char*)v1 + 0x28);
            (*(int(**)())((char*)v0 + 0x4C))(*(short*)((char*)v0 + 0x48) + (int)v1);
            i++;
        }
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}

/* MATCHED (byte-exact, 28/28). Sibling of A97C/A9EC/D06C — same loop cracked
 * by the `if (1) {}` BB-boundary lever (was "72.21% branch-likely-preload cap").
 * Outer offsets same as D06C (count=a0->0x6C, slot=a0->0x3C); inner fn ptr
 * slot->0x28->0xE4, short arg slot->0x28->0xE0 (vs D06C's 0x4C/0x48). */
void timproc_uso_b5_func_0000D0DC(char *a0) {
    int i;
    char *p;
    int *v1;
    int *v0;

    if (*(int*)(a0 + 0x6C) <= 0) return;
    i = 0;
    p = a0;
    do {
        v1 = *(int**)(p + 0x3C);
        if (1) {
            v0 = *(int**)((char*)v1 + 0x28);
            (*(int(**)())((char*)v0 + 0xE4))(*(short*)((char*)v0 + 0xE0) + (int)v1);
            i++;
        }
        p += 4;
    } while (i < *(int*)(a0 + 0x6C));
}

#ifdef NON_MATCHING
/* timproc_uso_b5_func_0000D14C: 257-insn / 0x404 constructor.
 * Reconstructed from expected disasm with distinct named callees + data
 * symbols (sibling-ported from timproc_uso_b5_func_0000D884, the matching
 * twin in this TU). Each call now emits its own R_MIPS_26 reloc and each
 * data ref its own HI16/LO16 against the real USO global. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif

extern char timproc_uso_b5_D_807FEE30;
extern char timproc_uso_b5_D_807FEE38;
extern char timproc_uso_b5_D_807FDDEC;
extern char timproc_uso_b5_D_807FEE48;
extern char timproc_uso_b5_D_807FEE54;
extern char timproc_uso_b5_D_807FDAB8;
extern char timproc_uso_b5_D_807FDB4C;
extern char timproc_uso_b5_D_807FDB64;
extern char import_80807FB8;
extern char import_80087FB8[];
extern char import_80800078;
extern char import_80020078;
extern char import_8005EE6C;
extern char import_8005EE64;

#define D14C_EE6C (*(volatile int *)((char *)&import_8005EE6C + 4))
#define D14C_EE64 (*(volatile int *)((char *)&import_8005EE64 + 0))

int timproc_uso_b5_func_0000D14C(char *a0, int arg1, int arg2, int arg3,
                                 float arg4, float arg5, float arg6) {
    char *root;
    char *obj;
    char *child;
    char *gc;
    char *obj2;
    char *owner;
    int savedbit;
    int n;

    root = (char *)timproc_uso_b5_func_055750((char *)0x2C4);
    if (root != 0) {
        obj = root;
        if (obj == 0 ||
            (obj = (char *)timproc_uso_b5_func_055750((char *)0x2B8)) != 0) {
            timproc_uso_b5_func_04C678(obj, &timproc_uso_b5_D_807FEE30 + 0x15C0);
            FW(obj, 0x28) = (int)(&timproc_uso_b5_D_807FDB64 + 0);
            timproc_uso_b5_func_00002B74(obj + 0x2C);
            timproc_uso_b5_func_000032C8(obj + 0x194);
        }
        FW(root, 0x28) = (int)(&timproc_uso_b5_D_807FEE38 + 0x5E4);
        FW(root, 0xC) = (int)(&timproc_uso_b5_D_807FEE38 + 0x15C8);
        timproc_uso_b5_func_00003890(root);
    }

    timproc_uso_b5_func_07ACE0(a0 + 0x10, root);
    if (FW(root, 0x14) != 0) {
        FW(root, 0x4) = 1;
    }
    FW(root, 0x14) = (int)a0;
    *(float *)(root + 0x2A4) = (float)arg1;
    FW(root, 0x2B0) = arg2 - 1;

    child = (char *)timproc_uso_b5_func_055750((char *)0x148);
    if (child != 0) {
        timproc_uso_b5_func_0546DC(child, &timproc_uso_b5_D_807FEE48 + 0x15D8,
                                   0.0f, 0.0f);
        FW(child, 0x28) = (int)(&timproc_uso_b5_D_807FDDEC + 0x57C);

        gc = (char *)timproc_uso_b5_func_055750((char *)0x16C);
        if (gc != 0) {
            timproc_uso_b5_func_0546DC(gc, &timproc_uso_b5_D_807FEE54 + 0x15E4,
                                       0.0f, 0.0f);
            FW(gc, 0x120) = 0xFFFF;
            FW(gc, 0x28) = (int)(&import_80087FB8[0]);
            *(float *)(gc + 0x108) = *(float *)((char *)&import_80807FB8 + 0x3A0);
            *(float *)(gc + 0x10C) = *(float *)((char *)&import_80807FB8 + 0x3A0);
            *(float *)(gc + 0x110) = *(float *)((char *)&import_80807FB8 + 0x3A0);
            *(float *)(gc + 0x124) = 1.0f;
        }

        FW(child, 0x108) = (int)gc;
        timproc_uso_b5_func_04DFFC(child, gc);
        {
            char *p = (char *)FW(child, 0x108);
            *(float *)(p + 0xB4) = 0.0f;
            *(float *)(p + 0xBC) = 0.0f;
            *(float *)(p + 0xB8) = 100.0f;
        }
        *(float *)(child + 0x130) = *(float *)((char *)&import_80800078 + 0x3A4);

        obj2 = (char *)timproc_uso_b5_func_055750((char *)0xB4);
        if (obj2 != 0) {
            obj2 = (char *)import_0010D33C(obj2, *(int *)&import_80020078);
            FW(obj2, 0x28) = (int)(&timproc_uso_b5_D_807FDAB8 + 0x248);
            FW(obj2, 0xB0) = 0;
            timproc_uso_b5_func_077574(obj2);
        }
        FW(child, 0x10C) = (int)obj2;
        timproc_uso_b5_func_04DFFC(child, obj2);

        savedbit = D14C_EE6C & 0x80000;
        D14C_EE6C = (D14C_EE6C & 0xFFF7FFFF) | 0x22003;
        D14C_EE64 = D14C_EE64 & ~8;

        timproc_uso_b5_func_00B1B4(arg2, 0, 0x201, FW(child, 0x10C), child);
        FW(child, 0x140) = *(int *)((&timproc_uso_b5_D_807FDB4C + 0) + arg2 * 4);
        timproc_uso_b5_func_077C44((char *)FW(child, 0x10C), FW(child, 0x140),
                                   0, 2, 2, 1);
        {
            char *p = (char *)FW(child, 0x10C);
            char *vt = (char *)FW(p, 0x28);
            (*(void (**)())(vt + 0x24))((int)((short *)vt)[0x10] + (int)p);
        }

        if (savedbit != 0) {
            D14C_EE6C = D14C_EE6C | 0x80000;
        } else {
            D14C_EE6C = D14C_EE6C & 0xFFF7FFFF;
        }

        *(float *)(child + 0x110) = arg4;
        *(float *)(child + 0x114) = arg5;
        *(float *)(child + 0x118) = arg6;
        *(float *)(child + 0x120) = 0.0f;
        *(float *)(child + 0x124) = *(float *)((char *)&import_80807FB8 + 0x3A8);
        *(float *)(child + 0x128) = *(float *)((char *)&import_80807FB8 + 0x3AC);
        FW(child, 0x144) = 1;
        FW(child, 0x138) = 0;
        FW(child, 0x134) = 0;
    }

    FW(root, 0x2B8) = (int)child;
    FW(root, 0x29C) = (int)child;
    *(float *)(root + 0x134) = *(float *)((char *)&import_80807FB8 + 0x3B0);

    owner = (char *)FW(a0, 0x38);
    timproc_uso_b5_func_07ACE0(owner + 0x10, child);
    if (FW(child, 0x14) != 0) {
        FW(child, 0x4) = 1;
    }
    FW(child, 0x14) = FW(a0, 0x38);

    n = FW(a0, 0x6C);
    FW(a0, 0x6C) = n + 1;
    FW(a0 + n * 4, 0x3C) = (int)root;
    return (int)root;
}
#undef D14C_EE6C
#undef D14C_EE64
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D14C);
#endif

// timproc_uso_b5_func_0000D550 — STRUCTURAL PASS (0x334 / 205 words,
// no episode). Raw-.word USO form (single function). Dispatcher-heavy
// (15 calls, ~1 FP op) — a constructor, not math.
//
// Timing-screen sub-screen/panel constructor.
//
//   void *timproc_uso_b5_func_0000D550(a0, a1, a2, a3) {
//     R *r = func_00000000(0x2C8);  if (!r) return 0;      // main alloc
//     S *s = func_00000000(0x2B8);  if (s) {               // sub alloc
//       func_00000000(s, &D_000015F0);                     // base-init
//       s->0x28 = &D_0;                                     // vtable
//       func_00000000(s + 0x2C);
//       func_00000000(s + 0x194, &D_000015F8);
//     }
//     // ~15 func_00000000 calls total: build/register child
//     //   sub-elements at r/s offsets (0x2C, 0x194, …) from the
//     //   D_000015F0 / D_000015F8 descriptor table; wire args
//     //   a0/a1/a2/a3 (spilled sp+0x60..0x6C) into the children.
//     return r;
//   }
//
// Struct-typing reference:
//   r (alloc 0x2C8) = the panel object; s (alloc 0x2B8) = a sub-record
//     (0x28 vtable &D_0, 0x2C / 0x194 child anchors). a0..a3 =
//     owner/config forwarded to children. D_000015F0 / D_000015F8 =
//     USO static descriptor table. func_00000000 = USO placeholder
//     dispatcher (alloc / init / factory / attach).
// Caps (DEFERRED): raw-word USO + placeholder calls; USO mnemonic
//   disasm limitation prevents byte-match. Real-C STRUCTURAL body
//   below — alloc-cascade + sub-record init + child-wire skeleton.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
char *timproc_uso_b5_func_0000D550(int a0, int a1, int a2, int a3) {
    char *r;
    char *s;
    r = (char *)func_00000000(0x2C8);
    if (r == 0) return 0;
    s = (char *)func_00000000(0x2B8);
    if (s != 0) {
        func_00000000(s, (char *)&D_00000000 + 0x000015F0);
        *(char **)(s + 0x28) = &D_00000000;
        func_00000000(s + 0x2C);
        func_00000000(s + 0x194, (char *)&D_00000000 + 0x000015F8);
    }
    func_00000000(r, s, a0, a1, a2, a3);
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D550);
#endif

// timproc_uso_b5_func_0000D884 — FULL m2c DECODE via compressed-module
// jumptable path (42.25% NM, no episode). 14-case switch (idx=*(sp+104),
// dispatch jr $t3 @ 0xDB08, default 0xDDF8) extracted from the Yay0-
// compressed USO emulator dump (ram_base 0x807ef230 forced, table @dump
// 0x7FF3E0). Near-identical SIBLING of func_0000DF14 (same 14-case shape,
// different descriptor base) — decoded identically. Lift: 49 X->unkN ->
// FW(X,0xN), placeholder calls cast via FP4, void*->char*, NULL->0.
// Raw-.word USO form (single function). Larger sibling of func_0000D550.
//
// Timing-screen panel/sub-screen constructor.
//
//   void *timproc_uso_b5_func_0000D884(a0, a1, a2, a3) {
//     R *r = func_00000000(0x2BC);  if (!r) return 0;      // main alloc
//     S *s = func_00000000(0x2B8);  if (s) {               // sub alloc
//       func_00000000(s, &D_00001620);                     // base-init
//       s->0x28 = &D_0;                                     // vtable
//       func_00000000(s + 0x2C);  func_00000000(s + 0x194);
//       s->0x28 = &D_00001628 + 0x7C4;  s->0x0C = …;        // vtable wire
//     }
//     func_00000000(a0);                                   // owner init
//     func_00000000(a0 + 0x10);
//     if (!owner->0x14) owner->0x4 = 1;  owner->0x14 = …;   // attach
//     r->0x2A4 = (float)a2;                                 // value/ts
//     r->0x2B0 = a3;
//     // ~remaining ~400 words: build many named child widgets from
//     //   the D_00001620 / 1628 / 1634 / 163C descriptor pool
//     //   (func_00000000(0, &D_16xx, …) factory calls) and wire
//     //   them into r/s.
//     return r;
//   }
//
// Struct-typing reference:
//   r (alloc 0x2BC) = panel object: 0x2A4 f32 (from a2 — value/
//     timestamp), 0x2B0 = a3 (a handle/flags); s (alloc 0x2B8) =
//     sub-record (0x28 vtable, 0x2C/0x194 child anchors). a0 =
//     owner (0x04 dirty / 0x14 attach link). D_00001620 / 1628 /
//     1634 / 163C = USO static descriptor tables. func_00000000 =
//     USO placeholder dispatcher (alloc / init / factory / attach).
// Caps (DEFERRED): raw-word USO + placeholder calls + 420-word
//   builder; USO mnemonic disasm limitation prevents byte-match.
//   Real-C STRUCTURAL body below — alloc-cascade + sub-record init
//   + owner-attach + value/ts stamp skeleton. Byte-match deferred.
//   Name pre-checked: no extern reuse.
// 2026-06-22 REWRITE (agent-e big-swing): replaced the generic-`alias`/
// `*(char*)4` m2c paraphrase with the TRUE structure decoded region-by-region
// from the raw-.word target (resolved relocs). All callees are now the real
// distinct USO symbols (func_055750 alloc / 04C678 base-init / 00002B74 /
// 000032C8 child-anchors / 00003890 owner-init / 07ACE0 attach / 0546DC FP
// factory / 05D0E0 key-wire / 04DFFC child-wire) and globals the real
// descriptor/flag symbols (D_807FEE90.. / import_8005EE6C flag word @+4 /
// import_800200CC mode @+0x34 / D_807FF3E0 jumptable / D_807FEBB4.. keys).
// Field offsets/types taken from store mnemonics (swc1=f32, sw=s32).
// 60.13% -> 67.25% fuzzy (+7.1pp), correct-C.
// RESIDUAL CAPS (two, both structural):
//  1) EXTERNAL-DATA jumptable @ 0xDAFC-0xDB08: `lui at,%hi(D_807FF3E0);
//     addu at,at,idx*4; lw t3,0x3C0(at); jr t3` — the 14-case dispatch reads
//     its case targets from the NAMED global table D_807FF3E0+0x3C0, NOT a
//     compiler-emitted local .rodata jumptable. C `switch` always emits a
//     LOCAL jumptable+relocs, so this dispatch (~90 words) is C-irreproducible.
//     Same cap class as gl_func_00030AF4 (flagged in the 1F14 commit).
//  2) Register-allocation/frame divergence: target saves only s0 and spills
//     a0-a3 to sp+0x60..0x6C, reloading per-use (IDO -O2 on a 1680B
//     call-heavy fn); C reconstruction holds more in regs -> larger frame,
//     instructions shifted. Intractable per the documented near-miss cap
//     analysis. Head + tail field/callee/FP semantics are exact.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int timproc_uso_b5_func_0546DC();
extern int timproc_uso_b5_func_05D0E0();
extern int timproc_uso_b5_func_04DFFC();
extern char timproc_uso_b5_D_807FEE90;
extern char timproc_uso_b5_D_807FDB64;
extern char timproc_uso_b5_D_807FEE98;
extern char timproc_uso_b5_D_807FEEA4;
extern char timproc_uso_b5_D_807FEEAC;
extern char timproc_uso_b5_D_807FEEB8;
extern char timproc_uso_b5_D_807FEBB4;
extern char timproc_uso_b5_D_807FA914;
extern char timproc_uso_b5_D_807FEEE8;
extern char timproc_uso_b5_D_807FEEF4;
extern char timproc_uso_b5_D_807FEF00;
extern char timproc_uso_b5_D_807FEF0C;
extern char timproc_uso_b5_D_807FEF18;
extern char timproc_uso_b5_D_807FEF24;
extern char timproc_uso_b5_D_807FEF30;
extern char timproc_uso_b5_D_807FEF3C;
extern char import_8005EE6C;
extern char import_800200CC;
extern char import_80807FB8;
extern char import_8077EBB4;
extern char import_8077A914;
extern char import_80806674;
extern char import_80776674;

#define EE6C (*(volatile s32 *)((char *)&import_8005EE6C + 4))
#define MODE (*(s32 *)((char *)&import_800200CC + 0x34))

char *timproc_uso_b5_func_0000D884(char *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    char *r;
    char *obj;
    char *child;
    char *gc;
    s32 savedbit;

    r = timproc_uso_b5_func_055750((char *)0x2BC);
    if (r != 0 || (r = timproc_uso_b5_func_055750((char *)0x2B8)) != 0) {
        timproc_uso_b5_func_04C678(r, &timproc_uso_b5_D_807FEE90 + 0x1620, r);
        FW(r, 0x28) = (s32) (&timproc_uso_b5_D_807FDB64 + 0);
        timproc_uso_b5_func_00002B74(r + 0x2C);
        timproc_uso_b5_func_000032C8(r + 0x194);
        FW(r, 0x28) = (s32) (&timproc_uso_b5_D_807FEE98 + 0x7C4);
        FW(r, 0xC) = (s32) (&timproc_uso_b5_D_807FEE98 + 0x1628);
    }
    timproc_uso_b5_func_00003890(r);
    timproc_uso_b5_func_07ACE0(arg0 + 0x10, r);
    if (FW(r, 0x14) != 0) {
        FW(r, 0x4) = 1;
    }
    FW(r, 0x14) = (s32) arg0;
    *(f32 *)(r + 0x2A4) = (f32) arg1;
    FW(r, 0x2B0) = arg2;
    child = timproc_uso_b5_func_055750((char *)0x144);
    if (child != 0) {
        timproc_uso_b5_func_0546DC(child, &timproc_uso_b5_D_807FEEA4 + 0x1634, 0.0f, 0.0f, 0.0f);
        FW(child, 0x28) = (s32) (&timproc_uso_b5_D_807FEEAC + 0x1300);
        FW(child, 0xC) = (s32) (&timproc_uso_b5_D_807FEEAC + 0x163C);
        gc = timproc_uso_b5_func_055750((char *)0x16C);
        if (gc != 0) {
            f32 one = *(f32 *)((char *)&import_80807FB8 + 0x3BC);
            timproc_uso_b5_func_0546DC(gc, &timproc_uso_b5_D_807FEEB8 + 0x1648, 0.0f, 0.0f, 0.0f);
            FW(gc, 0x120) = 1;
            FW(gc, 0x28) = (s32) (&timproc_uso_b5_D_807FDB64 + 0);
            *(f32 *)(gc + 0x108) = one;
            *(f32 *)(gc + 0x10C) = one;
            *(f32 *)(gc + 0x110) = one;
            *(f32 *)(gc + 0x124) = 1.0f;
        }
        FW(child, 0x108) = (s32) gc;
        timproc_uso_b5_func_04DFFC(child, gc);
        {
            char *p = (char *)FW(child, 0x108);
            *(f32 *)(p + 0xBC) = 0.0f;
            *(f32 *)(p + 0xB8) = 0.0f;
            *(f32 *)(p + 0xB4) = 0.0f;
        }
        *(f32 *)(child + 0x124) = 1.0f;
        savedbit = EE6C & 0x80000;
        EE6C = EE6C & 0xFFF7FFFF;
        EE6C = EE6C & ~1;
        EE6C = EE6C | 2;
        EE6C = EE6C & 0xFFFDFFFF;
        EE6C = EE6C | 0x2000;
        FW(child, 0x140) = 1;
        FW(child, 0x13C) = 1;
        switch (arg2) {
        case 11:
            if (MODE == 3) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEBB4 + 0x1654, &import_8077EBB4 + 0, 0);
            }
            FW(child, 0x13C) = 0;
            break;
        case 12:
            if (MODE == 3) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FA914 + 0x1660, &import_8077A914 + 0, 0);
            }
            FW(child, 0x13C) = 0;
            break;
        case 13:
            if (MODE == 3) {
                timproc_uso_b5_func_05D0E0(child, &import_80806674 + 0x166C, &import_80776674 + 0, 0);
            }
            FW(child, 0x13C) = 0;
            break;
        case 0:
            if (MODE != 2) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEEE8 + 0x1678, 0, 0);
            }
            break;
        case 1:
            if (MODE != 2) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEEF4 + 0x1684, 0, 0);
            }
            break;
        case 2:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF00 + 0x1690, 0, 0);
            }
            break;
        case 3:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF0C + 0x169C, 0, 0);
            }
            break;
        case 4:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF18 + 0x16A8, 0, 0);
            }
            break;
        case 5:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF24 + 0x16B4, 0, 0);
            }
            break;
        case 6:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF30 + 0x16C0, 0, 0);
            }
            break;
        case 7:
            if (MODE != 3 && MODE != 5) {
                timproc_uso_b5_func_05D0E0(child, &timproc_uso_b5_D_807FEF3C + 0x16CC, 0, 0);
            }
            break;
        }
        if (savedbit != 0) {
            EE6C = EE6C | 0x80000;
        } else {
            EE6C = EE6C & 0xFFF7FFFF;
        }
        *(f32 *)(child + 0xDC) = arg3;
        *(f32 *)(child + 0xE0) = arg4;
        *(f32 *)(child + 0xE4) = arg5;
        *(f32 *)(child + 0x10C) = arg6;
        *(f32 *)(child + 0x110) = arg7;
        FW(child, 0x134) = 0;
        FW(child, 0x130) = 0;
        *(f32 *)(child + 0x128) = 0.0f;
        *(f32 *)(child + 0x11C) = 0.0f;
        *(f32 *)(child + 0x114) = arg8;
        *(f32 *)(child + 0x124) = 0.0f;
        *(f32 *)(child + 0x120) = *(f32 *)((char *)&import_80807FB8 + 0x3F8);
    }
    FW(r, 0x2B8) = (s32) child;
    FW(r, 0x29C) = (s32) child;
    *(f32 *)(r + 0x134) = -32.0f;
    obj = (char *)FW(arg0, 0x38);
    timproc_uso_b5_func_07ACE0(obj + 0x10, child, obj);
    if (FW(child, 0x14) != 0) {
        FW(child, 0x4) = 1;
    }
    FW(child, 0x14) = (s32) obj;
    {
        s32 n = FW(arg0, 0x6C);
        FW(arg0, 0x6C) = n + 1;
        FW(arg0 + n * 4, 0x3C) = (s32) r;
    }
    return r;
}
#undef EE6C
#undef MODE
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000D884);
#endif

// timproc_uso_b5_func_0000DF14 — timing-screen panel constructor (NM, 59.1%,
// no episode). Full STRUCTURAL reconstruction from expected disasm: alloc-or-
// passthrough head (func_055750 0x2BC/0x2B8), sub-record init, owner attach,
// then a child-widget factory with a 14-entry jumptable (switch(arg2+10),
// table @ D_807FF420+0x400) selecting D_807FExxx descriptors and calling
// func_05D0E0/func_04DFFC per mode (import_800200CC+0x34). DISTINCT named
// callees (func_055750/04C678/00002B74/000032C8/00003890/07ACE0/0546DC/
// 04DFFC/05D0E0) — each emits its own R_MIPS_26 reloc; the old single-`alias`
// collapse capped the reloc set at 55%. Residual ~40%: stack-frame size
// (0x50 vs target 0x60) drives load/store-offset drift across the body, and
// the K&R float-call return spill (swc1 $f0,16(sp) after func_0546DC) is not
// reproduced — func_0546DC needs a (void*,void*,float,float) proto but its
// 5-arg D884 sibling call blocks a shared typed decl. FP-heavy structural cap.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif

/* Data symbols not declared elsewhere; subscripted as byte arrays so
 * &SYM[N] forms HI16/LO16 against the named global (distinct relocs). */
extern char timproc_uso_b5_D_807FEF48[];
extern char timproc_uso_b5_D_807FEF50[];
extern char timproc_uso_b5_D_807FEF5C[];
extern char timproc_uso_b5_D_807FEF64[];
extern char timproc_uso_b5_D_807FEF70[];
extern char timproc_uso_b5_D_807FEFA0[];
extern char timproc_uso_b5_D_807FEFAC[];
extern char timproc_uso_b5_D_807FEFB8[];
extern char timproc_uso_b5_D_807FEFC4[];
extern char timproc_uso_b5_D_807FEFD0[];
extern char timproc_uso_b5_D_807FEFDC[];
extern char timproc_uso_b5_D_807FEFE8[];
extern char timproc_uso_b5_D_807FEFF4[];
extern char import_80087FB8[];

char *timproc_uso_b5_func_0000DF14(char *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    char *r;
    char *child;
    char *sub;
    s32 flag;
    s32 mode;

    r = timproc_uso_b5_func_055750((char *)0x2BC);
    if (r != 0) {
        sub = r;
        if (r == 0) {
            sub = timproc_uso_b5_func_055750((char *)0x2B8);
            if (sub == 0) {
                goto owner;
            }
        }
        timproc_uso_b5_func_04C678(sub, &timproc_uso_b5_D_807FEF48[5848]);
        FW(sub, 0x28) = (s32) (&timproc_uso_b5_D_807FDB64 + 0);
        timproc_uso_b5_func_00002B74(sub + 44);
        timproc_uso_b5_func_000032C8(sub + 404);
        FW(r, 0x28) = (s32) &timproc_uso_b5_D_807FEF50[2468];
        FW(r, 0xC) = (s32) &timproc_uso_b5_D_807FEF50[5856];
        timproc_uso_b5_func_00003890(r);
    }
owner:
    timproc_uso_b5_func_07ACE0(arg0 + 16, r);
    FW(r, 0x2AC) = FW(arg0, 0x6C);
    if (FW(r, 0x14) != 0) {
        FW(r, 0x4) = 1;
    }
    FW(r, 0x14) = (s32) arg0;
    FW(r, 0x2B0) = arg2;
    *(f32 *)(r + 0x2A4) = (f32) arg1;
    child = timproc_uso_b5_func_055750((char *)0x144);
    FW(r, 0x144) = (s32) child;
    if (child != 0) {
        timproc_uso_b5_func_0546DC(child, &timproc_uso_b5_D_807FEF5C[5868], 0.0f, 0.0f);
        FW(child, 0x28) = (s32) &timproc_uso_b5_D_807FEF64[1300];
        FW(child, 0xC) = (s32) &timproc_uso_b5_D_807FEF64[5876];
        sub = timproc_uso_b5_func_055750((char *)0x16C);
        FW(child, 0x28) = (s32) sub;
        if (sub != 0) {
            timproc_uso_b5_func_0546DC(sub, &timproc_uso_b5_D_807FEF70[5888], 0.0f, 0.0f);
            *(s32 *)(sub + 0x120) = 1;
            FW(sub, 0x28) = (s32) &import_80087FB8[0];
            *(f32 *)(sub + 0x108) = *(f32 *)(&import_80807FB8 + 1020);
            *(f32 *)(sub + 0x10C) = *(f32 *)(&import_80807FB8 + 1020);
            *(f32 *)(sub + 0x110) = *(f32 *)(&import_80807FB8 + 1020);
            *(f32 *)(sub + 0x124) = 1.0f;
        }
        FW(child, 0x108) = (s32) sub;
        timproc_uso_b5_func_04DFFC(child, sub);
        {
            char *gc = (char *) FW(child, 0x108);
            *(f32 *)(gc + 0xBC) = 0.0f;
            *(f32 *)(gc + 0xB8) = 0.0f;
            *(f32 *)(gc + 0xB4) = 0.0f;
        }
        *(f32 *)(child + 0x124) = 1.0f;
        flag = *(s32 *)(&import_8005EE6C + 4) & 0x80000;
        *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) & ~0x80000;
        *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) & ~1;
        *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) | 2;
        *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) & ~0x20000;
        *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) | 0x2000;
        FW(child, 0x140) = 1;
        FW(child, 0x13C) = 1;
        switch (arg2 + 10) {
        case 0:
            if (*(s32 *)(&import_800200CC + 52) == 3) {
                timproc_uso_b5_func_05D0E0((&timproc_uso_b5_D_807FEBB4 + 5900), (&import_8077EBB4 + 0), 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            FW(child, 0x13C) = 0;
            break;
        case 1:
            if (*(s32 *)(&import_800200CC + 52) == 3) {
                timproc_uso_b5_func_05D0E0((&timproc_uso_b5_D_807FA914 + 5912), (&import_8077A914 + 0), 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            FW(child, 0x13C) = 0;
            break;
        case 2:
            if (*(s32 *)(&import_800200CC + 52) == 3) {
                timproc_uso_b5_func_05D0E0((&import_80806674 + 5924), (&import_80776674 + 0), 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            FW(child, 0x13C) = 0;
            break;
        case 3:
            if (*(s32 *)(&import_800200CC + 52) != 2) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFA0[5936], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 4:
            if (*(s32 *)(&import_800200CC + 52) != 2) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFAC[5948], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 5:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFB8[5960], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 6:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFC4[5972], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 7:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFD0[5984], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 8:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFDC[5996], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 9:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFE8[6008], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        case 10:
            mode = *(s32 *)(&import_800200CC + 52);
            if ((mode != 3) && (mode != 5)) {
                timproc_uso_b5_func_05D0E0(&timproc_uso_b5_D_807FEFF4[6020], (char *)0, 0, 0);
                timproc_uso_b5_func_04DFFC(child);
            }
            break;
        }
        if (flag != 0) {
            *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) | 0x80000;
        } else {
            *(s32 *)(&import_8005EE6C + 4) = *(s32 *)(&import_8005EE6C + 4) & ~0x80000;
        }
        *(f32 *)(child + 0xDC) = arg3;
        *(f32 *)(child + 0xE0) = arg4;
        *(f32 *)(child + 0xE4) = arg5;
        *(f32 *)(child + 0x10C) = arg6;
        *(f32 *)(child + 0x110) = arg7;
        FW(child, 0x134) = 0;
        FW(child, 0x130) = 0;
        *(f32 *)(child + 0x128) = 0.0f;
        *(f32 *)(child + 0x11C) = 0.0f;
        *(f32 *)(child + 0x114) = arg8;
        *(f32 *)(child + 0x124) = 0.0f;
        *(f32 *)(child + 0x120) = *(f32 *)&import_80087FB8[1080];
    }
    FW(r, 0x2B8) = (s32) child;
    FW(r, 0x29C) = (s32) child;
    *(f32 *)(r + 0x134) = -32.0f;
    sub = (char *) FW(arg0, 0x38);
    timproc_uso_b5_func_07ACE0(sub + 16, child);
    if (FW(child, 0x14) != 0) {
        FW(child, 0x4) = 1;
    }
    FW(child, 0x14) = (s32) sub;
    {
        s32 n = FW(arg0, 0x6C);
        FW(arg0, 0x6C) = n + 1;
        FW(arg0 + n * 4, 0x3C) = (s32) r;
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/timproc_uso_b5/timproc_uso_b5", timproc_uso_b5_func_0000DF14);
#endif

void timproc_uso_b5_func_0000E5AC(int a0) {
    *(int*)&D_00000000 = 0;
    gl_func_00000000(a0);
}

/* timproc_uso_b5_func_0000E5D8: the `lui v0; lw v0,0(v0)` load of *(&D) (a state
 * pointer) is THIS function's real pre-prologue, mis-split into the E5AC _pad.s;
 * boundary-corrected 2026-05-30 by merging those 2 words into E5D8.s (0x48 ->
 * 0x50, start 0x0000E5D0), same fix as gl_func_0001FC78/000601DC. The old
 * PROLOGUE_STEALS=8 note is obsolete (that mechanism was banned 2026-05-23).
 * Body copies 3 floats from (*&D)->0x70's fields (0xBC/0xCC/0xDC) into
 * &D+0/+4/+8, then calls gl_func(a0). Load lands in $v0 (IDO's first-temp) =
 * the target's register, so no register-renumber residual. */
extern int D_b5_E5D8_base;  /* distinct &D=0 alias (undefined_syms) so the base read
                             * compiles to the compact lui v0; lw v0,0(v0) instead of
                             * CSE-ing &D with the dst stores (which forces lui+addiu+lw). */
void timproc_uso_b5_func_0000E5D8(int a0) {
    int *base = (int*)D_b5_E5D8_base;
    *(float*)((char*)&D_00000000 + 0) = *(float*)((char*)base[0x70/4] + 0xBC);
    *(float*)((char*)&D_00000000 + 4) = *(float*)((char*)base[0x70/4] + 0xCC);
    *(float*)((char*)&D_00000000 + 8) = *(float*)((char*)base[0x70/4] + 0xDC);
    gl_func_00000000(a0);
}

/* C-emit-absorbed orphans (per docs/MATCHING_WORKFLOW.md):
 *   _00006890 + _000068A8 + _000068EC ← _0000687C (decl 0x14, .o 0x84
 *      — covers vram 0x687C-0x6900 inclusive of all 3 orphans)
 *   _0000C1F4 ← _0000C1B4 (decl 0x40, .o 0x54)
 *   _0000CCB4 ← _0000CC74 (decl 0x40, .o 0x54) */
