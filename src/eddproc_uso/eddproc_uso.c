#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by the standard -O2 int-reader template body. The
 * trampoline word is injected post-cc via PREFIX_BYTES (see Makefile +
 * scripts/inject-prefix-bytes.py).
 *
 * 2026-05-27: confirmed bytes IDENTICAL with expected/.o (objdump -d
 * both shows the same 16 instructions @ 0x00 — trampoline + body). The
 * 93.75% fuzzy in report.json comes from RELOC-PRESENCE diff, not
 * byte-diff: our .o emits R_MIPS_HI16/LO16/26 for D_00000000 +
 * gl_func_00000000; expected/.o has no relocs (captured pre-reloc — raw
 * .word USO form). Same uso_raw_word-vs-reloc cap class as other USO
 * func_00000000 entries. Real fix needs USO spimdisasm migration
 * (focused-session per project_1080_uso_spimdisasm_migration_todo). No
 * C lever; do NOT re-grind. */
void eddproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void eddproc_uso_func_00000040(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void eddproc_uso_func_0000007C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void eddproc_uso_func_000000D4(Vec3 *dst) {
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

void eddproc_uso_func_00000144(int a0, int a1) {
    (void)&a0;
    (void)&a1;
}

void eddproc_uso_func_00000150(int a0, int a1) {
    (void)&a0;
    (void)&a1;
}

extern int D_00000004;

void eddproc_uso_func_0000015C(char *a0) {
    *(char**)(a0 + 0xC) = &D_00000000 + 0x220;
    gl_func_00000000(a0);
    gl_func_00000000(a0, 0xD6, 0x13, *(char**)(a0 + 0x44) + 0x10);
    gl_func_00000000(a0, 0x6C, 0x11, (char*)a0 + 0xA0);
    *(int*)(a0 + 0xA0) = 0x2328;
    *(int*)(a0 + 0xA4) = 0;
    *(int*)&D_00000000 = gl_func_00000000(0x3E80);
    D_00000004 = 0;
    gl_func_00000000(a0);
}

void eddproc_uso_func_000001E8(char *a0) {
    if (*(int*)(&D_00000000 + 0x74) == 0) {
        gl_func_00000000();
        gl_func_00000000(a0);
        if ((*(int*)(a0 + 0xA0) -= 0xA) < 0) {
            *(int*)(a0 + 0xA0) = 0;
        }
    }
    gl_func_00000000(a0);
    gl_func_00000000(*(int*)(a0 + 0x84), *(int*)(a0 + 0xA0), 1);
    gl_func_00000000(a0);
}

/* Multi-stage allocator/initializer (50 insns, 0xC8). Pattern:
 *
 *   T* f(T *a0, T *a1) {
 *       T *p1 = a0;
 *       T *p2, *p3;
 *
 *       if (p1 == 0) {                     // a0 == 0: try first alloc
 *           p1 = gl_func_00000000(0x54);
 *           if (p1 == 0) return 0;         // alloc failed
 *       }
 *
 *       p2 = gl_func_00000000(0x50, p1, a1);  // alloc+link second
 *       if (p2 == 0) goto FINAL_P1;
 *
 *       p3 = gl_func_00000000(0x2C);       // alloc third
 *       if (p3 != 0) {
 *           gl_func_00000000(p3, &D_22C);  // init p3 from data table
 *           p3->0x28 = &D_0;
 *       }
 *       p2->0x28 = &D_0;                   // (only when p3 alloc reached)
 *
 *   FINAL_P1:
 *       p1->0x28 = &D_0;
 *       return p1;
 *   }
 *
 * Quirk: a1 is spilled to caller-arg-slot at sp+0x24 but never reloaded
 * (dead spill — IDO preserves it via the convention without reading back).
 * The 3 alloc stages each have an early-out branch.
 *
 * Multi-tick decomp: matching the exact branch nesting + 3 spill-slot
 * pattern requires careful arrangement of the 3 conditional alloc paths.
 * Stub body documented; default build INCLUDE_ASM matches.
 *
 * NOT A CAP (2026-05-30). Prior analysis was WRONG on two counts:
 *  (1) The old C body had the WRONG control flow — it called gl_func(0x50)
 *      UNCONDITIONALLY with 3 args. The target is a CONDITIONAL 3-stage
 *      find-or-create cascade (each stage allocs only if the prior slot is
 *      null, one arg each). The body below is the corrected structure.
 *  (2) The target does NOT use $s0/s1/s2 — it spills a2/v1 (caller-saved)
 *      to stack, frame 0x20, reusing the INCOMING ARG-HOME slots (sp+0x20,
 *      sp+0x24 for the dead a0/a1) instead of new in-frame slots. The
 *      "needs $s promotion" conclusion was false.
 * Frame is now EXACT 0x20: reuse the dead `a0` param to hold the stage-3
 * object (no third local → no extra slot), and `(void)&a1` for a1's dead
 * home. The stage-1 null-return GOTOs the shared epilogue (`goto Ret`) not
 * `return a2` — `return` emits a separate epilogue + branch; `goto` shares
 * the one at the end (this alone was +9pp). Fuzzy 61.26→70.58, correct shape.
 *
 * BREAKTHROUGH 2026-06-01 (70.58 -> 96.0, +25.4pp). The prior "fold the dead
 * branches by routing the running value through memory" hypothesis was the
 * WRONG diagnosis. The real root cause of the fold was IDO CSE-ing the vtable
 * address: the three `obj->0x28 = &D_00000000` stores share ONE `&D` materialize
 * (a single hoisted `lui v1;addiu v1` reused for all three sw), and that shared
 * register is what merged the control flow and let IDO fold the stage-2/3
 * guards. Two coupled fixes recover the target shape:
 *   (1) THREE DISTINCT vtable externs (D_edd_vt0/1/2) — busts the address CSE so
 *       IDO re-materializes the vtable per store (target's t6/t7/t8 = 3 separate
 *       `lui;addiu;sw`). This ALSO un-folds the dead guards: with no shared reg
 *       the stage-2/3 `bne` guards reappear and the alloc checks flip to the
 *       target's fail-branches-forward `beq v0,zero,store` sense. Recipe per
 *       timproc_uso_b3_func_000021F4 (EXACT, 2026-05-03).
 *   (2) REUSE the `a0` param as the obj0 accumulator (not a fresh `a2` local) so
 *       its cross-jal spill homes at sp+0x20 (a0's incoming arg slot), matching
 *       target's spill layout obj0->0x20 / v1->0x1c / obj2->0x18.
 * MATCH 2026-06-21 (96.0 -> 100.0, byte-exact, ROM byte-identical). The
 * "final-mile scheduler cap" (the obj2 vtable block hoisted the two cross-jal
 * reloads `lw v1; lw a2` into the lui->addiu gap; target keeps `addiu` adjacent
 * to `lui`) WAS crackable via the STATEMENT-LINE-JOIN as1-tie lever: putting the
 * `have2:` label + the gl_func call + the vtable store all on ONE source line
 * (`have2: gl_func(...); *(...) = vt0;`) flips IDO's scheduler to keep the
 * materialize adjacent (target order `lui t6; addiu t6; lw v1; lw a2; sw t6`).
 * Found via focused permuter (perm_sameline). The three vtable externs resolve
 * to absolute 0 (undefined_syms_auto.txt: D_edd_vt0/1/2 = 0) so they emit
 * zero-immediate lui/addiu with NO ELF reloc, matching the target's raw words;
 * distinct symbols still bust the address CSE at the C level. */
extern char D_edd_vt0;
extern char D_edd_vt1;
extern char D_edd_vt2;
void *eddproc_uso_func_0000025C(int *a0, int *a1) {
    int *v1, *obj2;
    (void)&a1;
    /* obj0 is the reused `a0` param (homes its spill at sp+0x20 = a0 arg-slot,
     * matching target). goto-chain dispatch keeps the dead stage-guards as
     * `bne` (target shape). Three DISTINCT vtable externs bust IDO's address
     * CSE so the `&D` vtable materializes 3× (t6/t7/t8) per store instead of a
     * single hoisted reg — recipe per timproc_uso_b3_func_000021F4 (EXACT). */
    if (a0 != 0) goto have0;
    a0 = (int*)gl_func_00000000(0x54);
    if (a0 == 0) goto Ret;
have0:
    v1 = a0;
    if (a0 != 0) goto have1;
    v1 = (int*)gl_func_00000000(0x50);
    if (v1 == 0) goto Sa2;
have1:
    obj2 = v1;
    if (v1 != 0) goto have2;
    obj2 = (int*)gl_func_00000000(0x2C);
    if (obj2 == 0) goto Sv1;
have2: gl_func_00000000(obj2, (char*)&D_00000000 + 0x22C); *(int*)((char*)obj2 + 0x28) = (int)&D_edd_vt0;
Sv1:
    *(int*)((char*)v1 + 0x28) = (int)&D_edd_vt1;
Sa2:
    *(int*)((char*)a0 + 0x28) = (int)&D_edd_vt2;
Ret:
    return a0;
}

void eddproc_uso_func_00000324(int a0) {
}

void eddproc_uso_func_0000032C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    gl_func_00000000(dst + 0x10);
}

void eddproc_uso_func_0000035C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_edd_3C((float*)(dst + 0x10));
}

void eddproc_uso_func_0000038C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_edd_78((Quad4*)(dst + 0x10));
}

/* 36-insn / 0x90 constructor: alloc 0x40, init via gl_func, conditional
 * list-insert into arg0->field_40 if non-NULL. BYTE-EXACT 2026-05-30.
 *
 * The old "~94% cap (frame -0x20 vs -0x28, spill-not-saved-reg)" was NOT a
 * cap — the target spills the object pointer as TWO live ranges (frame 0x28).
 * Cracked via: (1) p1/p2 split so the block1 (init) and block2 (link) uses of
 * the pointer become two webs -> the second spill slot + frame 0x28; (2) the
 * permuter found that REUSING p1 to hold arg0 after the split lets IDO place
 * the pointer in $a0(block1)/$v1(block2) instead of $a2; (3) declaration order
 * p2,head,p1 fixes the spill-slot offsets (IDO assigns int slots in decl order,
 * see docs/IDO_CODEGEN.md interleave-decl-spill-slot); (4) re-loading the
 * arg0[0x40] condition (`if((int*)p1[0x40/4]!=0)`) puts head in $v0 + a plain
 * beqz. Do not "simplify" the variable reuse or the re-load — they're load-
 * bearing for the register/slot allocation. */
void *eddproc_uso_func_000003BC(int *arg0) {
    int *p2;
    int *head;
    int *p1;
    p1 = (int*)gl_func_00000000(0x40);
    if (p1 != 0) {
        gl_func_00000000(p1);
        *(int*)((char*)p1 + 0x28) = (int)&D_00000000;
        *(int*)((char*)p1 + 0x3C) = 0;
    }
    p2 = p1;
    p1 = arg0;
    head = (int*)p1[0x40 / 4];
    if ((int*)p1[0x40 / 4] != 0) {
        gl_func_00000000((char*)p2 + 0x10, head);
        if (*(int*)((char*)head + 0x14) != 0) {
            *(int*)((char*)head + 0x4) = 1;
        }
        *(int*)((char*)head + 0x14) = (int)p2;
    }
    return p2;
}

void eddproc_uso_func_0000044C(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    eddproc_uso_func_edd_D0((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/eddproc_uso/eddproc_uso/eddproc_uso_func_0000044C_pad.s")

