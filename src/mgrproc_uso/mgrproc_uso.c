#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* Int-reader (pointer-indirect via volatile buf) with -O0 artifacts: 0x4C
 * (19 insns) vs -O2 template's 15 insns. Three -O0 markers in target:
 *   (a) `sw ra` BEFORE `sw a0` in prologue (-O2 opposite)
 *   (b) unfilled jal delay slot (`jal 0; nop`) — -O2 fills with `addiu a2, 4`
 *   (c) extra `b +1; nop` pair before epilogue (dead branch to next insn,
 *       characteristic -O0 basic-block boundary per feedback_ido_o0_empty_stub.md)
 * BLOCKED 2026-04-21: mgrproc_uso is Yay0-compressed. A second `.o`
 * (e.g., mgrproc_uso_o0_0.c.o) wouldn't land in ROM because the Makefile
 * Yay0 rule consumes only mgrproc_uso.c.o. Per
 * feedback_yay0_uso_blocks_file_split_recipe.md, the file-split recipe
 * (which works for bootup_uso and arcproc_uso) does NOT apply here.
 * Unblock path: add an `ld -r` pre-merge step before yay0 compression —
 * infrastructure work, out of single-tick scope.
 * Body semantics per feedback_uso_accessor_template_reuse.md int reader. */
/* K&R def so same-TU callers passing varying arg counts type-check in
 * NON_MATCHING build. See feedback_knr_def_for_inconsistent_arg_callers.md. */
void mgrproc_uso_func_00000000(dst) int *dst; {
    volatile int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000000);
#endif

#ifdef NON_MATCHING
/* Quad4-reader template at -O0 (25 insns, 0x64) — sibling of
 * mgrproc_uso_func_00000000 (int reader at -O0). Per
 * feedback_uso_accessor_template_reuse.md, this is the standard 16-byte
 * accessor compiled at -O0 vs -O2 (15 insns).
 *
 * -O0 markers in target:
 *   (a) `sw ra` BEFORE `sw a0` in prologue (-O2 opposite)
 *   (b) unfilled jal delay slot (`jal 0; nop`) — -O2 fills with `addiu a2,16`
 *   (c) pointer-indirect reload (`lw t6,0x28(sp); addiu t7,sp,0x18`) instead
 *       of -O2's direct `lw tN,0x18(sp)`
 *   (d) trailing `b +1; nop` (dead branch to next insn) before epilogue
 *
 * BLOCKED: mgrproc_uso is Yay0-compressed (per feedback_uso_yay0_compressed.md);
 * the file-split recipe for -O0 override (works for bootup_uso/arcproc_uso)
 * doesn't apply because the Yay0 rule consumes only one .o. Same blocker as
 * mgrproc_uso_func_00000000 (int-reader sibling). Unblock requires `ld -r`
 * pre-merge step before yay0 compression — infrastructure work, deferred. */
void mgrproc_uso_func_0000004C(Quad4 *dst) {
    volatile Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *(Quad4*)dst = *(Quad4*)&buf;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000004C);
#endif

#ifdef NON_MATCHING
/* Refcount-increment wrapper (18 insns, 0x48). -O0 style matching
 * mgrproc_uso_func_00000000 (int reader at -O0).
 *
 * Body: increment a0->field_04 (as int), then call gl_func_00000000(a0).
 *
 * -O0 tells in target:
 *   (a) shadow-space save of a0 at sp+0x28, then reload into $s0 at 0xC0
 *       (`lw s0, 0x28(sp)`) AND ANOTHER reload into $a0 at 0xD0
 *       (`lw a0, 0x28(sp)`) — -O0 never shares the reload
 *   (b) unfilled jal delay slot (`jal 0; nop`)
 *   (c) dead `b +1; nop` immediately before epilogue (basic-block boundary
 *       marker per feedback_ido_o0_empty_stub.md)
 *
 * To match exact: split mgrproc_uso_func_000000B0 into its own .c with a
 * `build/src/mgrproc_uso/<file>.c.o: OPT_FLAGS := -O0` override (same infra
 * as mgrproc_uso_func_00000000 plan and bootup_uso_o0_*.c files). Defer. */
void mgrproc_uso_func_000000B0(int *a0) {
    a0[1]++;
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000000B0);
#endif

#ifdef NON_MATCHING
/* mgrproc_uso_func_000000F8: 5-function BUNDLE (0xA4 / 41 insns total).
 * Splat couldn't separate sub-functions (no inter-function relocs in
 * Yay0-compressed mgrproc_uso). 5 distinct jr-ra sequences inside the
 * declared symbol size:
 *
 *   F1 @ 0xF8-0x13C: 16 insns / 0x44 — main body. Decrement a0[0], then
 *      call gl_func_00000000(a0). -O0 emit (frame -0x28, sw a0 to caller
 *      slot at +0x28, reload via s0 then again into a0, unfilled jal
 *      delay, dead `b +1; nop` BBL marker). Same -O0 cap class as
 *      mgrproc_uso_func_000000B0 sibling (both are "mutate-and-call"
 *      shapes at -O0).
 *
 *   F2 @ 0x140-0x164: 9 insns / 0x28 — leaf function returning
 *      (a0[1] == a0[2]) ? 1 : 0. NO prologue (leaf). bne t6,t7,+4 form.
 *
 *   F3 @ 0x168-0x16C: 2 insns / 0x8 — empty `void f(void) {}`.
 *
 *   F4 @ 0x170-0x190: 9 insns / 0x24 — leaf returning (a0[0] == 0) ? 1 : 0.
 *      NO prologue. bne t6,0,+4 form. Sibling of F2 with one fewer load.
 *
 *   F5 @ 0x194-0x198: 2 insns / 0x8 — empty `void f(void) {}` trailer.
 *
 * BLOCKED for split: mgrproc_uso is Yay0-compressed (per
 * feedback_uso_yay0_compressed.md). Per
 * feedback_uso_split_fragments_breaks_expected_match.md, running
 * split-fragments.py on a USO function makes the build emit new symbols
 * but expected/.o keeps the OLD bundled symbol — match drops to 0%
 * across affected symbols even though .text bytes are identical. SAFE
 * SUFFIX_BYTES recipe (per feedback_suffix_bytes_for_bundled_empty_trailers.md)
 * applies only to bundles where ALL trailers are empty `jr ra; nop` — F2/F4
 * are non-empty 9-insn leafs, so this bundle can't use that recipe.
 *
 * Default INCLUDE_ASM build keeps ALL 5 functions matching via the bundled
 * symbol. Wrap captures F1 body (the only non-leaf, non-empty content) for
 * grep discoverability and as a sibling of mgrproc_uso_func_000000B0. */
void mgrproc_uso_func_000000F8(int *a0) {
    a0[0]--;
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000000F8);
#endif

/* mgrproc_uso_func_0000019C: 218-insn (0x368) state-machine orchestrator.
 *
 * Per-state init dispatcher: 9-way jump-table on a1 (state index), each case
 * does its own `gl_func_00000000(a0, ...)` call + sets a flag word at D[0x40]
 * or D[0x44]/0x48, optionally stores `1` to sp[0x48] (loop-continue marker).
 *
 * Frame: -0x50, save ra/s0/s1/s2 (4 callee-saves), spill a0 to sp+0x50,
 * a1 to sp+0x54 (caller-slot save).
 *
 * ENTRY DECODE (insns 0-7, 0x19C-0x1B8):
 *   addiu sp,-0x50; sw ra,0x2C; sw a0,0x50(caller); sw a1,0x54(caller);
 *   sw s2,0x28; sw s1,0x24; sw s0,0x20; sw $0,0x48(sp)  ; loop-continue=0
 *
 * JUMP-TABLE DISPATCH (0x1BC-0x1E0, 9 insns):
 *   t6 = a1
 *   if (t6 >= 9) goto epilogue                  ; bgeu via slti+bnez (0x1C0/0x1C4)
 *   t6 *= 8                                     ; sll t6,t6,3
 *   at = lui+addu(jumptbl + t6)                 ; jump-table base lui (rel'd)
 *   t6 = jumptbl[a1]                            ; lw t6,0(at)
 *   jr t6                                        ; indirect jump to case
 *
 * 9 CASE BODIES, all in one big switch-emit (each ends `b epilogue; nop` to
 * 0x4E8):
 *
 *   Case 0 @ 0x1E4 (15 insns): a0=sp[0x50]; gl_func(a0,1,0xB,8);
 *     D[0x44]=2; D[0x48]=8; sp[0x48]=1
 *   Case 1 @ 0x224 (15 insns): a0=sp[0x50]; gl_func(a0,1,7,4);
 *     D[0x44]=2; D[0x48]=8; sp[0x48]=1
 *   Case 2 @ 0x264 (4 insns): a0=sp[0x50]; gl_func(a0); D[0x40]=3
 *   Case 3 @ 0x284 (8 insns): a0=sp[0x50]; a1=D[0x68];
 *     gl_func(a0,a1); D[0x40]=4
 *   Case 4 @ 0x2AC (28 insns, BIGGEST): pulls 3 globals (D_a/D_b/D_c),
 *     looks like multi-pointer struct init. Loads sp[0x50]; deref +8 ->
 *     +4 -> indexed by sp[0x18]<<2; stores results to D[0x64]/D[0x80] (with
 *     bit-set: D[0x80] |= 1). Stores byte to D[0x17D] / +0x90 dispatch.
 *     Ends D[0x40]=4
 *   Case 5 @ 0x37C (5 insns): a0=sp[0x50]+1*0; a1=*(int*)(sp[0x50]);
 *     gl_func(a0,a1)... actually `a0=sp[0x50]+0; a1=load[a0]; jal gl_func(1)`
 *   Case 6 @ 0x38C (8 insns): saves v0 to sp[0x4C]; sp+0x4C addr; mixed args
 *     incl. immediate 0x45000000. Reads sp[0x50]->8->0 chain; stores into
 *     sp[0x10]; calls gl_func.
 *   Case 7 @ 0x3B4 (5 insns): s0=v0; a0=sp[0x50]; a1=0; a2=s0; gl_func.
 *     sp[0x48]=1.
 *   Case 8 @ 0x3DC (~25 insns): sp+0x44 base buf; calls gl_func(a0=sp[0x50],
 *     a1=&sp[0x44]); reads sp[0x44]; OR with 0x2000; calls gl_func with
 *     ASCII a0 immediate (0x24840000 reloc); a1=sp[0x40]; stores result.
 *     sp[0x48]=1.
 *
 * After each case `b 0x4E8` skip the others (no fall-through).
 *
 * LOOP-BACK GUARD (0x4D4-0x4DC):
 *   t9 = sp[0x48]
 *   if (t9 != 0) goto entry+0x48 (the dispatch — adds 1 to a1, repeats)
 *   ... actually back-branch target is offset -200/4 = -50, so goes back to
 *   the entry-dispatch zone. This implements a "state++; if marker set,
 *   re-dispatch" loop.
 *
 * EPILOGUE @ 0x4E8 (5 insns): lw s0/s1/s2/ra; addiu sp,+0x50; jr ra
 *
 * Pattern fingerprint: classic IDO -O2 jump-table dispatch with per-case
 * gl_func_00000000() trampoline calls. State 4 is the heavy multi-struct
 * init; states 0/1/7/8 set the loop-continue marker (sp[0x48]=1) so they
 * iterate; states 2/3/5/6 are terminal (no marker set).
 *
 * BLOCKED for byte match: jump-table emit from C requires `switch (a1) {
 * case 0: ...; }` form, but IDO's exact emit also needs:
 *   - The data-table entries to be linked at offset 0 (USO placeholder)
 *   - 9 unique jal-0 relocs (one per case's gl_func call)
 *   - Multiple D_NN_x unique-extern aliases for case 4's struct accesses
 *   - PROLOGUE_STEALS for the entry's `lui at` if it gets stolen
 * Each of those is a known recipe (`feedback_unique_extern_with_offset_cast_breaks_cse.md`,
 * `feedback_pattern_mass_match.md` for the table emit), but combining 9 cases
 * + struct externs + jump-table reloc in one tick is single-/decompile-run
 * overscope. Documented as multi-tick spine pick.
 *
 * Default INCLUDE_ASM build remains exact. Wrap captures the 9-case dispatch
 * skeleton + per-case fingerprints for the next tick to refine. */
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000019C);

#ifdef NON_MATCHING
/* 51-insn allocator+init wrapper. 4 cross-USO calls + branch on D[0] sentinel.
 *   v1 = gl_func(2);
 *   v2 = gl_func(0x3C);  a0[2] = v2;
 *   v3 = gl_func(0, D[0x148], -1, -1);  a0[0] = v3;  D[0x14C] = v3;
 *   gl_func(v1);
 *   if (D[0] == 0x17D7) (a0->0)->0x14 = 1; else (a0->0)->0x14 = 0;
 * BLOCKED: mgrproc_uso is Yay0-compressed; default build INCLUDE_ASM
 * matches via the Yay0 packing. The wrap captures the structural decode. */
void mgrproc_uso_func_00000504(int *a0) {
    int v1 = gl_func_00000000(2);
    int v2 = gl_func_00000000(0x3C);
    int v3;
    a0[2] = v2;
    v3 = gl_func_00000000(0, *(int*)((char*)&D_00000000 + 0x148), -1, -1);
    a0[0] = v3;
    *(int*)((char*)&D_00000000 + 0x14C) = v3;
    gl_func_00000000(v1);
    if (*(int*)&D_00000000 == 0x17D7) {
        *(int*)((char*)a0[0] + 0x14) = 1;
    } else {
        *(int*)((char*)a0[0] + 0x14) = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000504);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000005D0);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000700);

#ifdef NON_MATCHING
/* 27-insn -O0 cleanup wrapper. Mirror of arcproc_uso_func_00000748:
 * gl_func(a0->8); a0->8 = 0; gl_func(a0->0, 3); a0->0 = 0; D[0x14C] = 0.
 * -O0 indicators in target: unfilled jal delays + `b +1; nop` BBL marker.
 *
 * BLOCKED by Yay0 pipeline: mgrproc_uso is Yay0-compressed, so the -O0
 * file-split recipe doesn't apply (Yay0 rule consumes one .o). Default
 * build INCLUDE_ASM matches; wrap is for grep discoverability per the
 * established -O0-cap pattern. */
void mgrproc_uso_func_000009A8(int *a0) {
    gl_func_00000000((int*)a0[2]);
    a0[2] = 0;
    gl_func_00000000((int*)a0[0], 3);
    a0[0] = 0;
    *(int*)((char*)&D_00000000 + 0x14C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000009A8);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000A14);
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_func_00000A14_pad.s")

void mgrproc_uso_func_00000AE0(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)((char*)*(int**)(&D_00000000 + 0x30) + 0x6AC));
    gl_func_00000000(&D_00000000);
}

extern char D_mgr_B20_1;
extern char D_mgr_B20_2;
void mgrproc_uso_func_00000B20(void) {
    gl_func_00000000(*(int*)(&D_00000000 + 0x30));
    gl_func_00000000(*(int*)(&D_mgr_B20_1 + 0x30));
    gl_func_00000000(&D_mgr_B20_2);
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000B5C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000C14);

void mgrproc_uso_func_00000CC4(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D00(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void mgrproc_uso_func_00000D3C(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void mgrproc_uso_func_00000D94(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00000E04);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000011A4);

void mgrproc_uso_func_000012AC(char *a0) {
    gl_func_00000000(&D_00000000);
    gl_func_00000000(a0 + 0x6B0);
    gl_func_00000000(a0 + 0x6C8);
    gl_func_00000000(a0 + 0x6E0);
    gl_func_00000000(a0 + 0x6F8);
}

void mgrproc_uso_func_00000000();  /* K&R-style: matches the K&R def above */

void mgrproc_uso_func_00001304(void) {
    mgrproc_uso_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001324);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000013C8);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000014F4);

#ifdef NON_MATCHING
/* mgrproc_uso_func_00001594: 32-insn (0x80) check-then-vtable-call helper.
 *
 * Logic outline:
 *   if (gl_func(D[0x190], a0) == 0) return;
 *   // a0 was saved in $a1; reload after call
 *   int *t = (a0)[0x48 / 4];
 *   int idx = D[0x7C/4];
 *   int *entry = t + (idx * 0x28 + 0x90);  // byte offset
 *   if (*entry != 0) {
 *       // entry's pointer is non-null: store and return
 *       D[0x30/4] = a0;
 *   } else {
 *       // recompute (target uses different t-regs in this branch)
 *       int *t2 = (a0)[0x48 / 4];
 *       void (*fn)() = (void(*)())t2[idx * 0xA + 0x24];
 *       fn();
 *   }
 *
 * Wait — actually re-reading the asm: bnezl t9 (branch likely if t9 != 0),
 * delay slot is `sw a1, 0x30(at)`. Branch-likely's delay only executes if
 * branch IS taken, so `sw a1, 0x30(at)` runs ONLY when t9 != 0.
 * The fall-through case (t9 == 0) does the SECOND vtable lookup +
 * jalr — which is the actual call path.
 *
 * Re-corrected logic:
 *   if (entry[0] != 0) {
 *       D[0x30/4] = a0;
 *       return;
 *   }
 *   // recompute and call
 *   t2 = a0[0x48/4]; entry2 = t2 + idx*0x28 + 0x90;
 *   ((void(*)())entry2[0])();
 *
 * Initial fresh decode — multi-pass refinement expected. */
extern int gl_func_00000000();
void mgrproc_uso_func_00001594(int *a0) {
    int *t;
    int idx;
    void (*fn)();
    if (gl_func_00000000(*(int*)((char*)&D_00000000 + 0x190), a0) == 0) return;
    t = (int*)a0[0x48 / 4];
    idx = *(int*)((char*)&D_00000000 + 0x7C);
    if (*(int*)((char*)t + idx * 0x28 + 0x90) != 0) {
        *(int*)((char*)&D_00000000 + 0x30) = (int)a0;
        return;
    }
    t = (int*)a0[0x48 / 4];
    fn = (void(*)())*(int*)((char*)t + idx * 0x28 + 0x90);
    fn();
}
#else
INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001594);
#endif

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001614);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_0000179C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001824);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001AD0);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001B58);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001BE4);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001C90);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00001F30);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002294);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002324);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_000023FC);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002850);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002940);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002AFC);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002B7C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002E3C);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00002F10);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003074);

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003240);

void mgrproc_uso_func_000032C8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000CC4((int*)(dst + 0x10));
}

void mgrproc_uso_func_000032F8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D00((float*)(dst + 0x10));
}

void mgrproc_uso_func_00003328(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D3C((Quad4*)(dst + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso", mgrproc_uso_func_00003358);

void mgrproc_uso_func_000033E8(char *dst) {
    int tmp;
    mgrproc_uso_func_00000CC4(&tmp);
    mgrproc_uso_func_00000D94((Vec3*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/mgrproc_uso/mgrproc_uso/mgrproc_uso_func_000033E8_pad.s")

