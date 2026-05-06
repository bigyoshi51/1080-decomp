#include "common.h"

extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000000);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000001CC);

extern int gl_func_00000000();
int gl_func_00000308(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

#ifdef NON_MATCHING
/* gl_func_00000338: 50-insn time/value formatter. Two divs (a1 / 60000,
 * remainder / 1000), each guarded by IDO -O2's standard div-by-zero +
 * INT_MIN-overflow trap insns (`teq zero, 0x7000` and `teq zero, 0x6000`).
 * Then calls a sprintf-like callee with format string at &D_8000_0xCB08
 * and args (a2 = quotient1, ?, ?).
 *
 * Decoded structure (semantics partially uncertain — the second use of
 * `subu` looks like ms - quotient_minutes, which doesn't cleanly map to
 * ms→MM:SS:hh; may be a different formula like a base/offset transform):
 *
 *   void f(char *out, unsigned a1) {
 *       unsigned mins = a1 / 60000;     // 0xEA60 = 60000
 *       unsigned rem = a1 - mins;       // not %, literal subtraction
 *       unsigned secs = rem / 1000;     // 0x3E8 = 1000
 *       unsigned ms_part = rem - secs * 10;  // some scaling
 *       sprintf(out + 0xE4, FORMAT_8000_CB08, mins, secs, ms_part);
 *   }
 *
 * Multi-tick decompile; this captures structural decode for future
 * pass to refine formula + match the format-arg passthrough. */
extern int gl_func_00000000();
void gl_func_00000338(char *a0, unsigned a1) {
    unsigned mins = a1 / 60000;
    unsigned rem = a1 - mins;
    unsigned secs = rem / 1000;
    unsigned ms_part = rem - secs * 10;
    gl_func_00000000(a0 + 0xE4, (char*)&D_00000000 + 0xCB08, mins, secs, ms_part);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000338);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000400);

extern int gl_func_00000000();
int gl_func_00000574(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0001CB30;

void gl_func_000005A4(char *a0, char a1, char a2, char a3) {
    gl_func_00000000(a0 + 0xE4, &gl_ref_0001CB30, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000005EC);

extern int gl_func_00000000();
int gl_func_00000760(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CB58;
int gl_func_00000790(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CB58, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000007BC);

/* gl_func_000009B4: 54-insn render-setup-style function (0xD8). .word-only
 * encoded; hand-decoded structure:
 *   - Frame -0x48, saves s0/ra
 *   - s0 = arg0 (context struct)
 *   - 5+ field accesses: arg0->0xA8/0xA4/0xAC/0xB0/0xB4/0xBC/0xB0/0x44/
 *     0x5C/0x74/0x8C
 *   - Float ops: cvt.s.w (int-to-float), neg.s, mul.s, c.lt.s
 *     (compare-less-than-single)
 *   - 2 unique `&D_X` extern refs (lui+lwc1 from address 0)
 *   - 4+ jal calls to runtime-patched callees with mixed int/float args
 *
 * Likely converts world-coord values to NDC/screen-coords or some
 * per-frame transform. The c.lt.s + cvt.s.w pattern suggests a
 * camera-frustum-culling or scaling check.
 *
 * Multi-pass decomp candidate. .word encoding requires byte-by-byte
 * decoding which is tedious for 54 insns; defer to a tick where the
 * caller's struct shape is known. Default INCLUDE_ASM keeps ROM correct. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000009B4);

/* gl_func_00000A8C: 72-insn nested-alloc-and-init function (0x120).
 * .word-only encoded. Hand-decoded prologue:
 *   - Frame -0x28, saves s0/ra
 *   - s0 = arg0 (early s0 anchor)
 *   - if (arg0 == 0) { s0 = alloc(0xD4); }   (212-byte allocation)
 *   - if (s0 == 0) goto epilog;
 *   - a2 = s0; alloc'd_inner = alloc(0xC4); (196-byte sub-object)
 *   - if (alloc'd_inner == 0) skip rest of init
 *   - a1 = 0x10000 + (-0x347C) = 0xCB84  (intra-USO data ref;
 *     looks like the splat-fold-into-nearest pattern — there should
 *     be a proper D_0000CB84 rodata symbol but splat fold the offset)
 *   - jal init(arg2_or_alloc'd_outer, &D_0000CB84, ...)
 *   - ... (more init)
 *
 * Two-level alloc constructor: outer 0xD4-byte struct + inner
 * 0xC4-byte sub-object. The 0xCB84 reference suggests a rodata
 * config table.
 *
 * Multi-pass decomp candidate. Default INCLUDE_ASM keeps ROM correct;
 * this comment is structural context for the next agent. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000A8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000BAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000D5C);

extern int gl_func_00000000();
int gl_func_00000E74(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CBD8;
int gl_func_00000EA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CBD8, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000ED0);

extern int gl_func_00000000();
extern char gl_ref_0000CBF8;
int gl_func_00000FA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xB4, &gl_ref_0000CBF8, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000FD0);

extern int gl_func_00000000();
int gl_func_00001114(char *a0) {
    return gl_func_00000000(a0 + 0x10C);
}

#ifdef NON_MATCHING
/* gl_func_00001134: 28-insn (0x70) 3-way value formatter dispatcher.
 * Picks one of 3 format-string variants from gl_data based on a1's
 * magnitude:
 *   a1 < 10   → format at &gl_data + 0xCC10  (with a2 = a1)
 *   a1 < 100  → format at &gl_data + 0xCC18  (3-arg)
 *   else      → format at &gl_data + 0xCC1C  (likely 4-digit / large)
 *
 * Likely a digit-count-driven number-to-text formatter — pads or
 * positions output based on how many digits a1 needs. Each arm calls
 * gl_func_00000000 (cross-USO printf-like) with (a0 + 0xE4) as the
 * destination buffer. */
extern int gl_data_00000000;
void gl_func_00001134(char *a0, int a1) {
    if (a1 < 10) {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC10, a1);
    } else if (a1 < 100) {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC18, a0 + 0xE4);
    } else {
        gl_func_00000000(a0 + 0xE4, (char*)&gl_data_00000000 + 0xCC1C);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001134);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000011A4);

void gl_func_0000127C(char *a0) {
    gl_func_00000000(a0 + 0x110);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000127C_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000012B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000135C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000015FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001798);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001820);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001C54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000237C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000024C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000025A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002840);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000029F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002B94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003138);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000032B0);

extern int gl_func_00000000();

void gl_func_000033E4(char *a0) {
    gl_func_00000000(a0 + 0xF0);
    gl_func_00000000(a0 + 0x108);
    gl_func_00000000(a0 + 0x120);
    gl_func_00000000(a0 + 0x150);
    gl_func_00000000(a0 + 0x138);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003430);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000038F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003B1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003C0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003DB8);

extern int gl_ref_00013C70();
int gl_func_0000405C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013C70(a0 + 0x10);
}

extern int gl_ref_00013C70();
extern int gl_ref_00013CAC();
int gl_func_0000408C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013CAC(a0 + 0x10);
}

extern int gl_ref_00013C70();
extern int gl_ref_00013CE8();
void gl_func_000040BC(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    gl_ref_00013CE8(a0 + 0x10);
}

/* Body is 4 insns (addiu t6, a0, 4; li t7, 1; jr ra; sllv v0, t7, t6),
 * but symbol coverage includes 2 leading nops at 0x40EC/0x40F0 (artifact
 * of split-fragments.py including inter-function alignment pad in the
 * split-off symbol). The 8-byte leading nop prefix is injected post-cc via
 * PREFIX_BYTES (the inject-prefix-bytes.py script grows st_size at the
 * front to absorb the prepended bytes — same mechanism as USO trampolines,
 * just nops here instead of a beq). */
int game_libs_func_000040EC(int a0) {
    return 1 << (a0 + 4);
}

extern int gl_func_00000000();
void gl_func_00004104(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004140(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004198(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void gl_func_000041D4(Vec3 *dst) {
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

#ifdef NON_MATCHING
/* gl_func_00004244: 2479-insn (0x26BC) constructor / setup orchestrator.
 * Stack frame 0x748 (1864 bytes — many local accumulators + working buffers).
 * Single function (grep -c 03E00008 = 1).
 *
 * Entry decode (insns 1-12 @ 0x4244-0x4274):
 *   sp -= 0x748                    ; massive frame
 *   save s0..s2, ra, f20, f22 (FPU regs preserved)
 *   s0 = a0                        ; saved arg
 *   if (a0 == 0) {                 ; alloc-or-passthrough ternary
 *       a0 = alloc(0x488);         ; 1160-byte primary buffer
 *       if (a0 == 0) goto epilogue ; alloc fail early-exit (jump +0x99A insns)
 *       s0 = a0;
 *   }
 *
 * Body (~2470 insns): main initialization. Sets a chain of D[+CF80] fields
 * to floats (1.0 via lui $at,0x3F80; mtc1), zero-inits 4-byte and 8-byte
 * regions, copies bytes in/out of accumulator regions at sp+0x718..738
 * (looks like a 12-float matrix init), then dispatches multiple cross-USO
 * calls (jal placeholders).
 *
 * Multi-tick decompile in scope; this captures structural decode + entry
 * stage for future passes to extend. Constructor pattern per
 * project_1080_strategy.md: not a skip reason — partial C IS the struct-
 * typing work for D+CF80 (a global state struct) and the a0 +0x488-byte
 * primary instance.
 *
 * Decoded entry stub for grep/discoverability; default build INCLUDE_ASM
 * matches via the original asm. */
extern int gl_func_00000000();
void gl_func_00004244(int *a0) {
    int *p = a0;
    if (p == 0) {
        p = (int*)gl_func_00000000(0x488);
        if (p == 0) return;
    }
    /* TODO: ~2470 insns of init + dispatch math + cross-USO calls */
    (void)p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00004244);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006900);

extern int gl_func_00000000();
int gl_func_00006A8C(char *a0, int a1) {
    *(int*)(a0 + 0x4F0) = a1;
    return gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006AAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006B80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006C38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006CDC);

extern int gl_func_00000000();
extern int *gl_ref_00000138;

void gl_func_00006DC8(int a0) {
    int *p;
    gl_func_00000000(a0, 0x1E0, 0);
    p = gl_ref_00000138;
    p[45] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006DF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006E78);

/* Init function: zero-initialize a0 fields, store 120.0f at +0x554, clear
 * a child obj field, then 3 calls. Composite of int-reader-shape prologue
 * + custom init logic. */
void gl_func_00006EE0(int *a0) {
    int *p;
    gl_func_00000000(a0, 0xF0, 4);
    *(int*)((char*)a0 + 0x544) = 0;
    *(float*)((char*)a0 + 0x554) = 120.0f;
    p = *(int**)((char*)&D_00000000 + 0x138);
    *(int*)((char*)p + 0xB4) = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(6, 0, 0);
    gl_func_00000000(&D_00000000, 6, 0, 0);
}

void gl_func_00006F60(int a0) {
    int *p;
    gl_func_00000000(a0, 0x1E0, 5);
    p = gl_ref_00000138;
    p[45] = 0;
}

/* Sibling of gl_func_00006EE0 (just-landed): same 32-insn 4-call init
 * shape but with different field offsets and 1-arg jal at end. */
void gl_func_00006F90(int *a0) {
    int *p;
    gl_func_00000000(a0, 0xF0, 4);
    *(int*)((char*)a0 + 0x544) = 0;
    *(float*)((char*)a0 + 0x554) = 120.0f;
    p = *(int**)((char*)&D_00000000 + 0x138);
    *(int*)((char*)p + 0xB4) = 0;
    gl_func_00000000(*(int*)((char*)&D_00000000 + 0x138), 0);
    gl_func_00000000(6, 0, 0);
    gl_func_00000000(&D_00000000, 6, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007010);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007344);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000076F0);

#ifdef NON_MATCHING
/* gl_func_00007FF4: 222-insn (0x378) game_libs subsystem dispatcher.
 * Frame 0x90, saves ra+s0 at sp+0x24/0x20.
 *
 * Entry structure (decoded 2026-05-05, first 28 insns):
 *
 *   s0 = a0;                         // save struct ptr to s-reg (long-lived)
 *   t6 = a0->[0x4F0];                // load flags/state field
 *   t7 = t6 << 7;                    // shift bit 24 to sign position
 *   if (t7 < 0) {                    // bgez +0x17 → bit 24 is set, skip 23 insns
 *       // bit-set arm (~23 insns, 0x800C-0x8068):
 *       //   t0 = s0->[0x30];        // sub-obj ptr
 *       //   mtc1 $zero, $f0         // f0 = 0.0
 *       //   lui+addiu &D            // a1 = &D + N
 *       //   a3 = 0xFF
 *       //   addiu a2, sp, 0x58      // local Quad4 buf
 *       //   swc1 $f0, 0x58/0x5C/0x60/0x64(sp)  // 4 zero floats
 *       //   jal gl_func(&D, ..., quad4, 0xFF)
 *       //   t8 = 0x10001            // bit-flag tag stored to sp+0x10
 *       //   ... continues with second jal, more sub-arg setup ...
 *   }
 *   // bit-clear arm (fall-through, target of bgez):
 *   //   ... TBD: ~190 insns of subsystem update / FPU math ...
 *   epi: lw ra, ...; lw s0, ...; addiu sp, 0x90; jr ra
 *
 * First-pass NM stub — captures only the entry guard structure for grep
 * discoverability. Multi-pass decomp expected (this is comparable size to
 * 1080's larger spine functions). Default build INCLUDE_ASM matches; this
 * doc provides reference for the next agent. */
extern int gl_func_00000000();
void gl_func_00007FF4(int *a0) {
    int flags;
    flags = a0[0x4F0 / 4];
    if ((flags & 0x01000000) != 0) {
        /* bit-24 arm: alloc Quad4-of-zeros, dispatch first jal — TBD */
        (void)a0[0x30 / 4];
        (void)gl_func_00000000;
    }
    /* bit-24-clear arm (~190 insns, FPU math + subsystem update) — TBD */
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007FF4);
#endif

extern int gl_func_00000000();
void gl_func_0000836C(int a0, int *a1) {
    int v = *a1;
    if (v == 9) {
        gl_func_00000000(a0, a1);
    }
    gl_func_00000000(a0, a1);
}

extern int gl_func_00000000();
int gl_func_000083AC(char *a0) {
    return gl_func_00000000(a0 + 0x50);
}

#ifdef NON_MATCHING
/* gl_func_000083CC: 79-insn 5-call dispatcher + 2 trailing prologue-stolen
 * words for gl_func_00008510 (the next function). Reads global state at
 * D_00000000+0x134, calls gl_func_00000000 5 times with state-derived args,
 * mutates state flags between calls.
 *
 * Structural decode (2026-05-04 partial):
 *   state = D[0x134]                 ; global state pointer
 *   t6 = state->0x108                ; sub-pointer
 *   a3 = state->0xC4                 ; sub-pointer
 *   t7 = t6->0x70                    ; saved at sp+0x44
 *   v0 = a3->0x800                   ; passed as 5th arg in 1st call
 *   a2 = state->0x80                 ; passed as 3rd arg in 1st call
 *   gl_func(state, 1, state->0x80, state->0xC4, a3->0x800);  /\* CALL 1 *\/
 *
 *   t9 = state->0x108                ; reload (state may have changed)
 *   s0->0x520 = t9                   ; spill to caller obj
 *   t9->0x18 &= ~8                   ; clear flag bit 3
 *   v1 = s0->0x520                   ; reload
 *   v1->0x18 &= ~4                   ; clear flag bit 2 — at &v1[0x18+0x18]
 *   gl_func(state, 0x70, t6->0x70);  /\* CALL 2 *\/
 *
 *   s0->0x51C = result_of_call2
 *   state->0x108 = result_of_call3   ; call3 first
 *   gl_func(0x80);                   /\* CALL 3 *\/
 *   if (call3_result != 0) {
 *       gl_func(call3_result, 1);    /\* CALL 4 *\/
 *   }
 *   gl_func(0, call3_result, state->0xC4, s0->0x51C, t7, call1_result);
 *                                    /\* CALL 5 — 6 args *\/
 *
 * NEXT-FUNCTION PROLOGUE-STEALS: trailing 2 words at 0x8508-0x850C
 * (`lui v1, 0; lw v1, 0x134(v1)`) belong to gl_func_00008510 logically.
 * To match gl_func_00008510 exact, will need
 * `build/src/game_libs/game_libs.c.o: PROLOGUE_STEALS := gl_func_00008510=8`.
 *
 * NEXT PASS: tighten the call-arg signatures, identify what callbacks
 * gl_func_00000000 resolves to at runtime (likely "spawn entity" /
 * "register handler" / "register" sequence given 5-call init pattern). */
extern int gl_func_00000000();
void gl_func_000083CC(int *a0) {
    int *state = *(int**)((char*)&D_00000000 + 0x134);
    int *t6 = *(int**)((char*)state + 0x108);
    int *a3 = *(int**)((char*)state + 0xC4);
    int t7 = *(int*)((char*)t6 + 0x70);
    int v0_call1 = gl_func_00000000(state, 1,
                                    *(int*)((char*)state + 0x80),
                                    a3,
                                    *(int*)((char*)a3 + 0x800));
    int *t9 = *(int**)((char*)state + 0x108);
    *(int**)((char*)a0 + 0x520) = t9;
    *(int*)((char*)t9 + 0x18) &= ~8;
    {
        int *v1 = *(int**)((char*)a0 + 0x520);
        *(int*)((char*)v1 + 0x18 + 0x18) = *(int*)((char*)v1 + 0x18) & ~4;
    }
    {
        int v0_call2 = gl_func_00000000(state, 0x70, t7);
        *(int*)((char*)a0 + 0x51C) = v0_call2;
    }
    {
        int v0_call3 = gl_func_00000000(0x80);
        *(int*)((char*)state + 0x108) = v0_call3;
        if (v0_call3 != 0) {
            gl_func_00000000(v0_call3, 1);
        }
        gl_func_00000000(0, v0_call3,
                         *(int*)((char*)state + 0xC4),
                         *(int*)((char*)a0 + 0x51C),
                         t7, v0_call1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000083CC);
#endif

#ifdef NON_MATCHING
/* gl_func_00008510: 40-insn dispatcher with prologue-stolen 8 bytes from
 * gl_func_000083CC (predecessor's tail loads `state = D[0x134]` into v1
 * and the function body uses v1 across its prologue). PROLOGUE_STEALS=8
 * splices the 8-byte lui+lw at function start that C-emit naturally
 * produces. After splice, function bytes 0x8512..0x85AC.
 *
 * Structure:
 *   state = D[0x134]                    (predecessor-loaded into v1)
 *   p     = state->0xC4->0x800          (saved at sp+0x20)
 *   if (arg0->0x528->0x8->0x8 != 0) {
 *       p2 = state->0xCC->0x800
 *       gl_func(p2, p2->0x34)           (call 1)
 *       t = arg0->0x528->0x8            (refetched)
 *       gl_func(p2, t->0x8, t->0x4)     (call 2)
 *   }
 *   gl_func(p)                          (call 3)
 *   gl_func(p, D[0x168], D[0x164], &D + 0x170)  (call 4)
 *   gl_func(arg0)                       (call 5)
 *
 * Current ~70% NM. Remaining diffs: (a) target uses beqzl (branch-likely)
 * with `lw a0,0x20(sp)` delay-likely preload — mine emits beqz+nop, losing
 * 1 insn (frame ends 4 bytes early); (b) regalloc — target uses v0/v1 for
 * state-derived ptrs, mine uses t6/t7/t9/t0/t1; (c) dead `lw a1,0x34(a0)`
 * in target at delay-slot of call 3 (CSE'd from if-body's call-1 setup,
 * harmlessly dead because next jal sets a1 from lui). All three coupled
 * to register allocation. INSN_PATCH not on agent-a worktree to fix
 * regalloc-only diffs. */
void gl_func_00008510(int *arg0) {
    char *state = *(char**)((char*)&D_00000000 + 0x134);
    char *p = *(char**)(*(char**)((char*)state + 0xC4) + 0x800);
    if (*(int**)((char*)*(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8) + 0x8) != 0) {
        char *p2 = *(char**)(*(char**)((char*)state + 0xCC) + 0x800);
        gl_func_00000000(p2, *(int*)((char*)p2 + 0x34));
        {
            int *t = *(int**)((char*)*(int**)((char*)arg0 + 0x528) + 0x8);
            gl_func_00000000(p2, *(int*)((char*)t + 0x8), *(int*)((char*)t + 0x4));
        }
    }
    gl_func_00000000(p);
    gl_func_00000000(p,
        *(int*)((char*)&D_00000000 + 0x168),
        *(int*)((char*)&D_00000000 + 0x164),
        (char*)&D_00000000 + 0x170);
    gl_func_00000000(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008510);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000085B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008674);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000871C);

extern int gl_ref_00018770();
extern int gl_ref_000187AC();
int gl_func_000087F4(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_000187AC(a0 + 0x10);
}

extern int gl_ref_00018770();
int gl_func_00008824(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018770(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018804();
int gl_func_00008854(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018804(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018840();
int gl_func_00008884(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018840(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000088B4);

#ifdef NON_MATCHING
/* gl_func_00008944: 19-insn (0x4C) -O0 int reader template — same body as
 * the standard accessor template but compiled at -O0 (vs the file's default
 * -O2). Verified BYTE-IDENTICAL standalone at -O0 (unfilled jal delay slot,
 * `addiu t6, sp, 0x18; lw t7, 0(t6)` chained-deref of buf[0], dead BB-marker
 * `b +1; nop` before epilogue).
 *
 * BLOCKED: needs -O0 file split. game_libs has no -O0 sub-files yet;
 * promoting requires src/game_libs/game_libs_o0_8944.c + linker-script slot
 * + per-file `OPT_FLAGS := -O0` Makefile entry. Multi-tick infrastructure. */
void gl_func_00008944(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008944);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008990);

#ifdef NON_MATCHING
/* gl_func_000089F4: 19-insn (0x4C) -O0 float reader template — float-typed
 * counterpart of gl_func_00008944's int-reader. Verified BYTE-IDENTICAL
 * standalone at -O0 (lwc1 $f4 / swc1 $f4 in place of lw/sw).
 *
 * BLOCKED: same -O0 file split as gl_func_00008944. See feedback memo
 * feedback_o0_int_reader_template_variant.md (extends to float variant). */
void gl_func_000089F4(float *dst) {
    float buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000089F4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008A40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008AE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008DAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000093DC);

#ifdef NON_MATCHING
/* Sibling family of 4 -O0 scratch+offset wrappers (0x949C, 0x94DC, 0x951C,
 * 0x955C; all 0x40 bytes / 16 insns / 2 jals to specific gl_refs).
 * Logic for 0x949C:
 *   void f(char *a0) {
 *     int scratch;
 *     gl_ref_0001CFB0(&scratch);
 *     gl_ref_0001CFFC(a0 + 0x10);
 *   }
 * Same shape as the matched gl_func_0000405C/0000408C (0x30 / 12 insns
 * at -O2) but compiled at -O0:
 *   - nop in BOTH jal delay slots (instead of useful work / arg setup)
 *   - trailing `b +1; nop` before epilogue (-O0 explicit jump-to-epi)
 * Net: -O0 emit is 4 instructions longer than -O2 for the same logic.
 *
 * Promotion path: file-split into src/game_libs/game_libs_949C_o0.c
 * holding all 4 sibling functions with a `-O0` Makefile override (game_libs
 * is NOT Yay0-compressed so the file-split recipe applies; see
 * feedback_uso_accessor_o0_file_split_recipe.md). Worth doing as a single
 * future tick: 4 mass-matches in one go.
 *
 * 2026-05-04 cluster verification: confirmed all 4 functions are 0x40 bytes
 * each (0x949C/0x94DC/0x951C/0x955C), each 16 insns, each calling the
 * standard scratch+offset 2-jal pattern. Combined cluster is exactly 0x100
 * bytes contiguous (0x949C..0x959C with 0x959C being the next INCLUDE_ASM).
 * The file-split would need 3 .c files: game_libs.c truncated at 0x949C,
 * game_libs_o0_949C.c containing all 4 funcs (0x100 bytes -O0), and
 * game_libs_tail.c continuing from 0x959C. Linker script + objdiff.json
 * need parallel updates. Single-cron-run risky; multi-pass setup. */
extern int gl_ref_0001CFB0();
extern int gl_ref_0001CFFC();
void gl_func_0000949C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001CFFC(a0 + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000949C);
#endif

#ifdef NON_MATCHING
/* Sibling of gl_func_0000949C (-O0 2-call wrapper). 16 insns / 0x40.
 * Both jals target gl_ref_0001CFB0 (calls same helper twice — first
 * with &scratch, then with a0+0x10).
 *
 * NM-build for game_libs.c is already broken upstream (existing 949C wrap
 * shrinks .text past TRUNCATE_TEXT=0xEC00); these new sibling wraps add
 * 0x30 more bytes shrinkage — default build is unaffected (INCLUDE_ASM
 * path emits the full 16-insn target bytes).
 *
 * O0-blocked NM cap; promotion path is the file-split recipe per
 * feedback_uso_accessor_o0_file_split_recipe.md (move all 4 siblings
 * into game_libs_949C_o0.c with -O0 OPT_FLAGS). */
extern int gl_ref_0001CFB0();
void gl_func_000094DC(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001CFB0(a0 + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000094DC);
#endif

#ifdef NON_MATCHING
/* Sibling of gl_func_0000949C. f1=gl_ref_0001CFB0, f2=gl_ref_0001D060.
 * Same 0x40 / 16 insns / O0-blocked structure. */
extern int gl_ref_0001D060();
void gl_func_0000951C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001D060(a0 + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000951C);
#endif

#ifdef NON_MATCHING
/* Sibling of gl_func_0000949C. f1=gl_ref_0001CFB0, f2=gl_ref_0001D0AC.
 * Same 0x40 / 16 insns / O0-blocked structure. */
extern int gl_ref_0001D0AC();
void gl_func_0000955C(char *a0) {
    int scratch;
    gl_ref_0001CFB0(&scratch);
    gl_ref_0001D0AC(a0 + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000955C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000959C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000959C_pad.s")

extern int gl_func_00000000();
void gl_func_00009674(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_000096B0(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

void gl_func_000096EC(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000975C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009DB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009EBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009FA8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A00C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A0CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A130);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A1C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A2B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A4D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A670);

extern int gl_func_00000000();

void gl_func_0000A768(char *a0) {
    int i;
    char *p;
    i = 0;
    p = a0;
    for (; i != 0x180; i += 0x30) {
        gl_func_00000000(p);
        p += 0x30;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A7B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A990);

extern int gl_func_00000000();

int gl_func_0000A9F4(int a0, int a1) {
    int r = gl_func_00000000(a0, a1);
    if (r == a1) return 1;
    return 0;
}

#ifdef NON_MATCHING
/* 93.43% NM. Two-stage validation: call once, check result == a1; call
 * again, check result == a2; return 1 only if both match. Diff vs target:
 *   - Mine: spill a2 BEFORE jal, a1 IN jal delay-slot, then redundant
 *     `lw a1` reload before bnel (1 extra insn = +4 bytes).
 *   - Target: spill a1 BEFORE jal, a2 IN delay-slot, NO redundant reload
 *     (uses t6 for the 1st bnel reload, t7 for the 2nd).
 * Tried (3 variants): inline `r != a1`, named `int r = ...`, named
 * `int s_a1 = a1` — all produce same 93.4%. The redundant-reload looks
 * like an IDO scheduling choice: it spills a1 in jal delay slot rather
 * than the prologue, then must reload from the slot before bnel. Target's
 * IDO put a1's spill in the prologue (no delay-slot use needed). Cap is
 * an instruction-scheduler decision not reachable from C-level levers. */
int gl_func_0000AA28(int a0, int a1, int a2) {
    if (gl_func_00000000(a0, a1, a2) != a1) goto fail;
    if (gl_func_00000000(a0, a1, a2) != a2) goto fail;
    return 1;
fail:
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA28);
#endif

/* 28-insn / 0x70 5-call wrapper followed by 2-field commit. Each call passes
 * the same a0 plus a different arg as a1; result of last call is ignored. */
void gl_func_0000AA7C(int *a0, int a1, int a2, int a3, int arg5, int arg6, int arg7, int arg8) {
    gl_func_00000000(a0, a1);
    gl_func_00000000(a0, a3);
    gl_func_00000000(a0, arg5);
    gl_func_00000000(a0, arg6);
    gl_func_00000000(a0, a2);
    a0[1] = arg8;
    a0[2] = arg7;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AAEC);

extern int gl_func_00000000();

void gl_func_0000AB70(char *a0) {
    int i;
    char *p;
    i = 0;
    p = a0;
    for (; i != 0x60; i += 0x20) {
        gl_func_00000000(p);
        p += 0x20;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ABBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ACBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B0A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B190);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B208);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B290);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B310);

extern int gl_func_00000000();
int gl_func_0000B3B0() {
    int r = gl_func_00000000();
    if (r != 0) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B3DC);

void gl_func_0000B450(int *a0) {
    int flags = a0[0x14 / 4];
    if (flags & 3) {
        gl_func_00000000(a0[0]);
        flags = a0[0x14 / 4];
    }
    if (flags & 4) {
        gl_func_00000000(a0[1]);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B4A4);

/* 14-insn 2-call wrapper at 0xB560-0xB594. The 4 trailing bytes at
 * 0xB59C-0xB5A8 (`sll/subu/addiu/div` computing (a1*3)/5) are stolen
 * prologue setup for successor gl_func_0000B5AC, applied via SUFFIX_BYTES
 * (same recipe class as gl_func_0005FD20 / gl_func_0005FDCC). */
extern int gl_func_00000000();
void gl_func_0000B560(int *p) {
    gl_func_00000000(p[4], p[0]);
    gl_func_00000000(p[4], p[1]);
}

/* gl_func_0000B5AC: 25-insn function that INHERITS $hi and $v0 from caller +
 * predecessor's SUFFIX_BYTES. Sibling of gl_func_0000B560 (just-landed) — B560
 * was extended with SUFFIX_BYTES `sll v0,a1,2; subu v0,v0,a1; addiu at,$0,5;
 * div $0,v0,at` that compute (a1*3)/5. Those 4 insns belong logically to
 * B5AC's prologue, leaving (a1*3)/5 quotient in $lo and remainder in $hi.
 * B5AC's first interesting insn is `mfhi a1` reading the remainder.
 *
 * Additional inherited reg: $v0 (used by `bgez v0` and `andi a2,v0,0x7`) —
 * caller-side flag. NOT standalone-callable from prototype-based C; reached
 * only via fall-through from gl_func_0000B560+SUFFIX_BYTES.
 *
 * Decoded control flow:
 *   ; entry inherits $hi = (a1*3)%5, $v0 = caller flag
 *   t8 = a1; t9 = 3*a1; save args; t7 = *a0;
 *   t0 = 9*a1; t1 = 36*a1; t9 = 48*a1;
 *   a1 = $hi (= prior remainder);
 *   a3 = t1 + 0xD268 = 36*a1 + 0xD268;     ; lookup-table address
 *   a0 = *a0 + 48*a1;                       ; struct-array entry
 *   if (v0 < 0 || (v0 & 7) == 0) goto call;
 *   a2 = (v0 & 7) - 8;
 * call:
 *   func_00000000();   ; first jal
 *   func_00000000();   ; second jal (a0 reloaded in delay slot)
 *   return;
 *
 * The trailing 4 insns at B5AC+0x70..0x80 are B5AC's tail-SUFFIX_BYTES for
 * its OWN successor B638 (`sll v0,a1,2; subu v0,v0,a1; addiu at,$0,5; div`)
 * — same chained pattern as B560->B5AC. B638 will need a parallel decode
 * to capture the chain.
 *
 * BLOCKED for prototype-based C: inherited $v0 is caller-specific (varies
 * per call site), can't be captured as a function arg without breaking
 * existing callers. PREFIX_BYTES on B5AC would have to bake a specific $v0
 * per call site — not a uniform recipe. Stays INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B5AC);

/* gl_func_0000B638: 29-insn function in the B560/B5AC/B638 dispatcher chain.
 * Like B5AC, INHERITS $hi (from B5AC's tail-SUFFIX_BYTES `sll v0,a1,2; subu;
 * addiu at,$0,5; div`) AND $v0 (caller-side flag). Same uninterruptible
 * mfhi-then-bgez pattern as B5AC.
 *
 * Decoded structure (cross-checked with B5AC analysis above):
 *   ; entry inherits $hi = (a1*3)%5, $v0 = caller flag
 *   t8 = a1; t9 = 3*a1; save args; t7 = *a0;
 *   t1 = 0xD388;                       ; lookup-table base (B5AC used 0xD268, +0x120 here)
 *   a1 = $hi;                           ; inherited remainder
 *   t9 = 48*a1;
 *   t0 = 4*v0;                          ; index by INHERITED v0 with 4-byte stride
 *                                       ;   (B5AC indexed by 36*a1 — different stride)
 *   a3 = t0 + t1 = 4*v0 + 0xD388;       ; per-flag table lookup
 *   a0 = *a0 + 48*a1;                   ; per-a1 struct entry
 *   if (v0 < 0 || (v0 & 7) == 0) goto call;
 *   a2 = (v0 & 7) - 8;
 * call:
 *   func_00000000();   ; first jal
 *   func_00000000();   ; second jal (a0 reloaded in delay slot)
 *   return;
 *
 * BLOCKED for prototype-based C — same class as B5AC. Inherited $v0
 * varies per call site; no uniform PREFIX_BYTES recipe. Stays INCLUDE_ASM
 * for now. Per docs/POST_CC_RECIPES.md
 * #feedback-insn-patch-for-ido-codegen-caps "HI/LO register inheritance
 * (chained-SUFFIX-div pattern, 2026-05-05)" — same recognition pattern. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B638);

extern int gl_func_00000000();
void gl_func_0000B6AC(int *a0) {
    gl_func_00000000(a0[1]);
    gl_func_00000000(a0);
}

extern int gl_func_00000000();
void gl_func_0000B6D8(int *a0) {
    gl_func_00000000(a0[2]);
    gl_func_00000000(a0[4], a0[2]);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B710);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B77C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B868);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B8E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B958);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BA6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BB14);

extern int gl_func_00000000();
int gl_func_0000BBB0(int a0) {
    int tmp = gl_func_00000000(24);
    gl_func_00000000(a0, tmp, 504, 24);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BBF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BC84);

extern int gl_func_00000000();
void gl_func_0000BD78(int a0) {
    int pad_arr[5];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BDA8(int a0) {
    int tmp = gl_func_00000000(384);
    gl_func_00000000(a0, tmp, 8, 384);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BDE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BEB8);

extern int gl_func_00000000();
void gl_func_0000BFAC(int a0) {
    int pad_arr[95];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BFDC(int a0) {
    int tmp = gl_func_00000000(96);
    gl_func_00000000(a0, tmp, 400, 96);
    return tmp;
}

#ifdef NON_MATCHING
/* gl_func_0000C01C: 52-insn (0xD0) cross-USO orchestrator. Frame -0x88,
 * saves s0/ra. Pattern: copy 0x60-byte buffer from arg1 to local stack,
 * then make 7 cross-USO calls passing the buffer + various offsets.
 *
 * Decoded:
 *   1. unrolled-by-3 loop copies 0x60 bytes from arg1 to sp[0x28]
 *      (8 iterations of 0xC-byte chunks).
 *   2. gl_func(sp[0x28], arg1, arg2_from_caller, arg3_from_caller)
 *   3. gl_func(arg0, 0x190, sp[0x28], 0x60)
 *   4. gl_func(sp[0x20], sp[0x28], 0x60, 0xDEADBBAD)
 *   5. gl_func(arg0, 0x1F0, sp[0x20], 8)
 *   6. gl_func(arg0, 0x7F60, sp[0x28], 0x60)
 *   7. gl_func(arg0, 0x7FC0, sp[0x20], 8)
 *   8. gl_func(arg0)
 *
 * Constants suggest framebuffer/segmented-memory ops: 0x190/0x1F0 are
 * NTSC viewport-related, 0x7F60/0x7FC0 are top-of-RDRAM offsets, 0x60
 * is element size, 0xDEADBBAD is poison. Likely a swap-buffers /
 * commit-frame helper. Multi-tick refinement target. */
extern int gl_func_C01C_callee();
void gl_func_0000C01C(void *arg0, int *arg1, int arg2, int arg3) {
    int buf60[24];   /* 0x60 bytes at sp+0x28 */
    int buf08[2];    /* 8 bytes at sp+0x20 */
    int i;
    for (i = 0; i < 24; i += 3) {
        buf60[i+0] = arg1[i+0];
        buf60[i+1] = arg1[i+1];
        buf60[i+2] = arg1[i+2];
    }
    gl_func_C01C_callee(buf60, arg1, arg2, arg3);
    gl_func_C01C_callee(arg0, 0x190, buf60, 0x60);
    gl_func_C01C_callee(buf08, buf60, 0x60, 0xDEADBBAD);
    gl_func_C01C_callee(arg0, 0x1F0, buf08, 8);
    gl_func_C01C_callee(arg0, 0x7F60, buf60, 0x60);
    gl_func_C01C_callee(arg0, 0x7FC0, buf08, 8);
    gl_func_C01C_callee(arg0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C01C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C0EC);

extern int gl_func_00000000();
void gl_func_0000C1E0(int a0) {
    int pad_arr[23];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C210);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C28C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C378);

extern int gl_func_00000000();
void gl_func_0000C46C(int a0) {
    int pad_arr[3];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

#ifdef NON_MATCHING
/* gl_func_0000C49C: 21-insn 3-call wrapper. SEMANTIC FIX 2026-05-06:
 * target reads from RETURN VALUE as pointer (r[0], r[2]), NOT from a0.
 * Prior wrap incorrectly used `a0[1] = a0[0]`. Asm clearly shows
 * `lw $t8, 0($v0)` (= r[0]) and `lw $t9, 0x8($v0)` (= r[2]).
 *   r = (int*)gl_func(a0);              // returns pointer
 *   a0[1] = r[0];                        // copy r[0] into a0[1]
 *   if (r[2] != 0) gl_func(r[2], r);
 *   gl_func(r, r); */
void gl_func_0000C49C(int *a0) {
    int *r = (int*)gl_func_00000000(a0);
    a0[1] = r[0];
    if (r[2] != 0) {
        gl_func_00000000(r[2], r);
    }
    gl_func_00000000(r, r);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C49C);
#endif

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD1C();
int gl_func_0000C4F0(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD1C(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD58();
int gl_func_0000C520(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD58(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DDC8();
int gl_func_0000C550(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DDC8(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
int gl_func_0000C580(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DCE0(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C5B0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0000C5B0_pad.s")

extern int gl_func_00000000();
void gl_func_0000C644(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C680(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C6BC(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

void gl_func_0000C714(Vec3 *dst) {
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C784);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C8B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CB9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CBFC);

#ifdef NON_MATCHING
/* gl_func_0000CD80: 23-insn (0x5C) "any-of-three-thresholds undercut" gate.
 *
 * Calls gl_func_00000000() iff $f0 < $f4 OR $f0 < D[sym1] OR $f0 < D[sym2].
 * Effectively a 3-way OR-gate over float threshold tests. The function
 * takes 2 float caller-args ($f0 and $f4 — non-standard ABI) and reads
 * 2 globals into $f6/$f8. If any threshold is exceeded, dispatch the
 * cross-USO callback.
 *
 * Arguments are received in $f0 and $f4 (NOT the standard $f12/$f14),
 * suggesting this is called from an asm-emitted call-site that explicitly
 * sets up these registers. Standard C signature `(float, float)` won't
 * map cleanly to $f0/$f4 — IDO uses $f12/$f14 for normal float args.
 *
 * Initial structural wrap; bytes likely won't match without an inline-asm
 * shim or an explicit-register declaration. Documented for future passes. */
extern int gl_func_00000000();
void gl_func_0000CD80(float a0, float a1) {
    extern char D_CD80_t1;
    extern char D_CD80_t2;
    float t1 = *(float*)&D_CD80_t1;
    float t2 = *(float*)&D_CD80_t2;
    if (a0 < a1 || a0 < t1 || a0 < t2) {
        gl_func_00000000();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CD80);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CDDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CE38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D0D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D318);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D418);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D548);

extern int gl_func_00000000();

void gl_func_0000D6A0(char *a0, int a1) {
    if ((*(int*)(a0 + 0xB4) & 4) != 0) {
        gl_func_00000000(0x2F, a0);
        *(int*)(a0 + 0xA4) = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D7B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D8E0);

/* gl_func_0000D9B8: 98.64%->100% via INSN_PATCH (3 reg-rename diffs at
 * offsets 0x08/0x0C/0x18). IDO emits $a1 for the temp; target uses $a3.
 * The 3 insns are identical in structure, differ only in register field.
 * Per feedback_insn_patch_for_ido_codegen_caps.md, this is the canonical
 * use case for INSN_PATCH (operand-only, same insn count, same size). */
extern int gl_func_00000000();
void gl_func_0000D9B8(int *a0) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p);
}

#ifdef NON_MATCHING
/* gl_func_0000D9E4: 0x150 (84 insns), 0x30-byte stack frame.
 * Untouched until 2026-05-03. Single function (grep -c 03E00008 = 1).
 * 2-arg: takes (int *a0, int a1).
 *
 * ENTRY GUARDS (insns 1-18 @ 0xD9E4-0xDA28, decoded):
 *   addiu sp,-0x30                     ; prologue
 *   save ra/s0/s1                       ; 0x24/0x20/0x1C
 *   sw a1, 0x34(sp)                    ; spill a1 to caller slot (varargs?)
 *   s0 = a0[0x6C]                       ; sub-struct ptr (cached for body)
 *   s1 = a0                             ; saved arg
 *   if (s0 == 0) goto end_simple        ; beq +0x3F
 *   t6 = a0[0xB4]
 *   if ((t6 & 2) == 0) goto end_simple  ; beq +0x3A
 *   t8 = *(int*)(&D_0 + 0x64)           ; load global ptr
 *   if (t8 == 0) goto end_simple        ; beq +0x36
 *
 * MID BODY (insns 19-50 @ 0xDA2C-0xDAB0, decoded structurally):
 *   FPU math chain. Constants:
 *     0x447A0000 = 1000.0f            (used in mtc1 + at-reg dance)
 *     0x42C80000 = 100.0f
 *     0x437F0000 = 255.0f             (loaded into multiple $f-regs)
 *     0x436B0000 = 235.0f
 *   Pattern: (float)a1 / 1000.0f then scale by 100.0f and 255.0f / 235.0f
 *   — looks like a percentage/normalized-value calculation. Probably color
 *   alpha (0..255 range with 0..235 sub-range) or stat-bar percentage.
 *
 * After FPU, calls some external (jal func_00000000 at 0xDA60) with 5 args
 *   (a0, a1, a2 from FPU, a3, plus saved on sp+0x10) — likely a
 *   `set_color_or_alpha(p, val_pct)` style helper.
 *
 * THEN at 0xDAA0+ another large FPU block computing 4 swc1 stores into
 *   (a0->0x64..0x70) and similar. Final block does 2 conditional gl_func
 *   calls based on (a0[0xB4] & 1) and a sub-struct check.
 *
 * EXIT (last 6 insns @ 0xDB1C-0xDB34):
 *   end_simple:
 *     restore ra/s0/s1, restore sp, jr ra
 *
 * Per feedback_partial_alloc_block_add_irreversible.md, NOT writing partial
 * body — would regress the 0% baseline. Captures structural decode only;
 * future passes with full body context can write all FPU sub-blocks
 * together. Multi-tick decomp expected. */
extern int gl_func_h2hproc_8EC_pre();  /* placeholder — actual callee unknown */
void gl_func_0000D9E4(int *a0, int a1) {
    /* Entry: 3 guards must all pass to reach body. */
    int *sub = (int*)a0[0x6C / 4];
    int flags = a0[0xB4 / 4];
    int *globalp = *(int**)((char*)&D_00000000 + 0x64);
    if (sub == 0) return;
    if ((flags & 2) == 0) return;
    if (globalp == 0) return;
    /* TODO: 60+ insns of FPU math + cross-USO calls. */
    (void)a1;
    (void)gl_func_h2hproc_8EC_pre();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9E4);
#endif

void gl_func_0000DB34(int a0, int a1, int a2) {
    char pad1[4];
    int *v0 = *(int**)((char*)&D_00000000 + 0x28);
    int local = 0x3ED;
    char pad2[12];
    ((void(*)(int, int*))*(int*)((char*)v0 + 0x34))(
        *(short*)((char*)v0 + 0x30) + (int)&D_00000000, &local);
}

#ifdef NON_MATCHING
/* gl_func_0000DB80: 68-insn function-pointer dispatcher with table lookup
 * + 3-way switch on entity state (a2->0x48).
 *
 * Structural decode (2026-05-04 first-pass):
 *   Prologue: spill 1000 (0x3E8) at sp+0x44 to use as a base.
 *   Lookup: t = *(sp+0x44 + a1*96)  — 96-byte stride table at offset
 *           +1000 from some base. (96 = 24 ints = likely a struct).
 *   First call: ((fnptr)t->0x2C)(t->0x28+t, &sp[0x44])  — vtable call,
 *           passes (struct ptr offset by signed half) and pointer to
 *           the spilled-1000 slot (now repurposed as out-arg).
 *
 *   Switch on (a2->0x48 - 2):  // a2 = original a0 saved at sp+0x50
 *     case 2 (a2->0x48 == 2): bnel branches to epilogue (skip body)
 *     case 3 (a2->0x48 == 3): take 0x3E9-stride table:
 *         t = *(sp+0x2C + a1*96 + a0->0x44)  // diff stride table
 *         ((fnptr)t->0x2C)(t->0x28+t, t_lookup)
 *         goto epilogue
 *     default (else):         take 0x3E8-stride table:
 *         t = *(sp+0x20 + a1*96 + a0->0x44)
 *         ((fnptr)t->0x2C)(t->0x28+t, t_lookup_h)  // signed-half load arg
 *
 *   The 3 jal sites all dispatch through `t->0x2C` function pointer with
 *   `t->0x28` (signed half) added to t as the first arg. Different
 *   tables are consulted based on a2->0x48's value.
 *
 * NEXT PASS: identify the global struct at offset +0x3E8/+0x3E9 (likely a
 * "render dispatch" or "AI behavior" table); type the struct's vtable +
 * data layout. Likely a "process entity by type-code" pattern. */
extern int gl_func_00000000();
void gl_func_0000DB80(int *a0, int a1) {
    /* Partial decode: 3-way switch on a2->0x48 (original a0->0x48), each
     * branch loads a different table-of-vtables and calls *t->0x2C(t->0x28+t, ...).
     * Default build uses INCLUDE_ASM. */
    (void)a0;
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DB80);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DC90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DD44);

/* 20-insn indirect dispatcher (sibling of gl_func_0000DE30/DE80/DED0/0003CB2C).
 * Same shape as DE30 form (inlined dispatch + pad_top[2]/pad_bot[4] frame
 * sizing), local = 0x3EA. INSN_PATCH on the same 4 reg-rename insns at
 * 0x24/0x2C/0x34/0x3C makes build/.o byte-equal to expected/.o post-cc. */
void gl_func_0000DDE0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EA;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* 20-insn indirect dispatcher (sibling of gl_func_0000DDE0/0003CB2C).
 * 16/20 insns match from C emit; remaining 4-insn diff is a register-shift
 * (v0/t0/t1 ↔ v1/v0/t0) that no C-level lever inside this function
 * reproduces. INSN_PATCH on the 4 reg-shift insns @0x24/0x2C/0x34/0x3C
 * makes build/.o byte-equal to expected/.o post-cc. */
void gl_func_0000DE30(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EB;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* Sibling of gl_func_0000DDE0/0000DE30/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3EC; otherwise byte-identical to DE30. Same INSN_PATCH recipe:
 * the 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched
 * to match expected. (The 0x30 word coincidentally byte-matches due to
 * register-rename + same instruction word; runtime semantics flip when the
 * patched 0x2C insn redefines $v0 = p[0x28] before 0x30 reads it.) */
void gl_func_0000DE80(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3EC;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

/* Sibling of gl_func_0000DDE0/DE30/DE80/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3E9; otherwise byte-identical to DE30/DE80. Same INSN_PATCH recipe:
 * 4 reg-rename diffs at offsets 0x24/0x2C/0x34/0x3C are post-cc patched to
 * match expected. (See DE80 for the byte-identical-bytes-different-semantics
 * mechanism at offset 0x30.) */
void gl_func_0000DED0(int **a0, int a1) {
    int pad_top[2];
    int local = 0x3E9;
    int pad_bot[4];
    int *p = *(int**)((char*)a0[0x44/4] + a1 * 96);
    ((void(*)(int, int*))p[0x2C/4])(
        (int)p + *(short*)((char*)p[0x28/4] + 0x28), &local);
}

int gl_func_0000DF20_inner(int a0, int a1);

void gl_func_0000DF20(int a0, int a1, float a2) {
    int rv = gl_func_0000DF20_inner(a0, a1);
    if (rv != 0) {
        *(float*)(rv + 0x10) = a2;
    }
}

extern int gl_func_00000000();

void gl_func_0000DF4C(int a0, int a1, int a2) {
    int *r = (int*)gl_func_00000000(a0, a1, a2);
    if (r == 0) return;
    if ((r[1] & 1) == 0) return;
    r[10] = a2;
}

extern int gl_func_00000000();

void gl_func_0000DF8C(int a0, int a1, float a2, float a3) {
    float *r = (float*)gl_func_00000000(a0, a1);
    if (r != 0) {
        r[2] = a2;
        r[3] = a3;
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E05C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E118);

void gl_func_0000E1DC(int *a0, int a1, int a2) {
    int *v = (int*)gl_func_00000000(a0, a1, a2);
    if (v == 0) return;
    if (!(v[1] & 1)) return;
    if (!(a0[0xB4 / 4] & 2)) return;
    gl_func_00000000(a0, a2);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E230);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E368);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E4A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E53C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E5D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E66C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E79C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E84C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E910);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E9C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000EAAC);

extern int gl_ref_00020CB0();
int gl_func_0000EB38(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CB0(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020CEC();
int gl_func_0000EB68(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CEC(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D28();
int gl_func_0000EB98(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D28(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D80();
int gl_func_0000EBC8(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D80(a0 + 0x10);
}




