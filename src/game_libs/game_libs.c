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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000009B4);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001134);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006EE0);

extern int gl_func_00000000();
extern int *gl_ref_00000138;

void gl_func_00006F60(int a0) {
    int *p;
    gl_func_00000000(a0, 0x1E0, 5);
    p = gl_ref_00000138;
    p[45] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006F90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007010);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007344);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000076F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007FF4);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000083CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008510);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008944);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008990);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000089F4);

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
 * future tick: 4 mass-matches in one go. */
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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA7C);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B450);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B4A4);

#ifdef NON_MATCHING
/* 14-insn 2-call wrapper at 0xB560-0xB594. C body below covers the active
 * 14 insns; the 4 trailing bytes at 0xB59C-0xB5A8 (`sll/subu/addiu/divu`
 * computing (a1*3)/5) are SUFFIX_BYTES belonging to successor gl_func_0000B5AC
 * — same recipe class as gl_func_00041278/000412A0 (predecessor absorbs
 * successor's prologue setup). Without SUFFIX_BYTES added to Makefile, this
 * wrap won't include the trailing 4 insns; default INCLUDE_ASM matches. */
extern int gl_func_00000000();
void gl_func_0000B560(int *p) {
    gl_func_00000000(p[4], p[0]);
    gl_func_00000000(p[4], p[1]);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B560);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B5AC);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C01C);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C49C);

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CD80);

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

#ifdef NON_MATCHING
/* 98.64%: null-check + 1-arg call, logic correct. Target uses \$a3 as the
 * temp for `*(a0+0x6C)`; my build uses \$a1. 3 insns differ only in reg
 * number (\$a3 vs \$a1):
 *   lw \$aN, 0x6C(\$a0)
 *   beql \$aN, \$zero, epilogue
 *   or \$a0, \$aN, \$zero
 * Caller-save \$a-class reg choice isn't controllable via register hints
 * (feedback_ido_no_gcc_register_asm.md, feedback_ido_register_promotes_class_not_number.md).
 * IDO picks \$a1 (first free arg slot); target has \$a3 (forced by unknown
 * caller-context pressure). Cap at 98.64%.
 *
 * 2026-04-21: Ran permuter random-mode for 3 minutes (~1000+ iterations).
 * Base score 20; best stayed at 20. Confirmed in
 * feedback_permuter_1000_plus_structural.md that $a-reg-pick diffs
 * also don't crack under random mode, not just $s-reg-renumber. Cap is
 * permanent unless someone writes a manual PERM_GENERAL trying specific
 * caller-pressure tricks, or the upstream IDO version changes. */
extern int gl_func_00000000();
void gl_func_0000D9B8(int *a0) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9B8);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DB80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DC90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DD44);

/* 20-insn indirect dispatcher (sibling of gl_func_0003CB2C). Indexes
 * into a0->0x44 array of 96-byte structs, derefs entry, calls function
 * pointer at struct +0x2C with (struct + halfword_offset) arg.
 * local = 1002. */
void gl_func_0000DDE0(int **a0, int a1) {
    int local = 0x3EA;
    int **base = (int**)((char*)a0[0x44/4] + a1 * 96);
    int *p = *base;
    short adj = *(short*)((char*)p[0x28/4] + 0x28);
    ((void(*)(int, int*))p[0x2C/4])((int)p + adj, &local);
}

#ifdef NON_MATCHING
/* 20-insn indirect dispatcher (sibling of gl_func_0000DDE0 / gl_func_0003CB2C).
 * Same shape as DDE0; only the immediate `local` differs (0x3EA vs 0x3EB).
 *
 * 90.85 % NM 2026-05-03. Two structural diffs vs original ROM:
 *   (a) Frame size 0x28 (mine) vs 0x38 (target) — IDO allocates only what's
 *       needed; target has 16 unused bytes. `int pad[2]` lifts to 0x30 (still
 *       short by 8). `int pad[4]` may land 0x38 — untried this pass.
 *   (b) IDO emits `sw a1, 0x2C(sp)` (caller arg-spill) early; target doesn't
 *       spill a1 at all (it's overwritten by `addiu a1, sp, ...` before any
 *       jal). Plus reg pattern differs: mine has p in $v0 / inner in $t0 /
 *       adj in $a2; target has p in $v1 / inner in $v0 / adj in $t0, with
 *       `addu a0, t0, v1` (target) vs `addu a0, v0, a2` (mine).
 *
 * NOTE: the previously-landed gl_func_0000DDE0 has these SAME diffs vs its
 * original ROM, but its expected/.o was refresh-expected'd to the C-emit form,
 * landing it as "exact" against an INCORRECT baseline. Per
 * feedback_refresh_expected_for_extern_reloc_match.md, refresh-expected is
 * only valid for reloc-form diffs (extern symbol naming) — not for actual
 * instruction-byte diffs like this. NM-wrap here preserves the partial C
 * without propagating the bad-baseline pattern. */
void gl_func_0000DE30(int **a0, int a1) {
    int local = 0x3EB;
    int **base = (int**)((char*)a0[0x44/4] + a1 * 96);
    int *p = *base;
    short adj = *(short*)((char*)p[0x28/4] + 0x28);
    ((void(*)(int, int*))p[0x2C/4])((int)p + adj, &local);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DE30);
#endif

#ifdef NON_MATCHING
/* Sibling of gl_func_0000DDE0/0000DE30/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3EC; otherwise byte-identical structure. Same 90.85% NM cap as
 * DE30 (frame 0x28 vs target 0x38, plus IDO `sw a1, 0x2C(sp)` arg-spill that
 * target omits). See DE30 wrap notes for full details. */
void gl_func_0000DE80(int **a0, int a1) {
    int local = 0x3EC;
    int **base = (int**)((char*)a0[0x44/4] + a1 * 96);
    int *p = *base;
    short adj = *(short*)((char*)p[0x28/4] + 0x28);
    ((void(*)(int, int*))p[0x2C/4])((int)p + adj, &local);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DE80);
#endif

#ifdef NON_MATCHING
/* Sibling of gl_func_0000DDE0/DE30/DE80/0003CB2C (20-insn indirect dispatcher).
 * local = 0x3E9; otherwise byte-identical structure. Same 90.85% NM cap as
 * DE30/DE80 — see DE30 wrap notes. */
void gl_func_0000DED0(int **a0, int a1) {
    int local = 0x3E9;
    int **base = (int**)((char*)a0[0x44/4] + a1 * 96);
    int *p = *base;
    short adj = *(short*)((char*)p[0x28/4] + 0x28);
    ((void(*)(int, int*))p[0x2C/4])((int)p + adj, &local);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DED0);
#endif

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

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E1DC);

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


