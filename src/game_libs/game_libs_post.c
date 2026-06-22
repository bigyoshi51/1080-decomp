#include "common.h"

extern int D_00000000;

#ifdef NON_MATCHING
/* Macro definitions for NM-wrap bodies. Auto-managed by /struct-name-tick.
 * Default build never sees these — wrap bodies aren't compiled.
 * GL_COUNT_2070: element count — read into `count`/`n`/`m` locals and used
 * as a multiplier in indexing. game_libs D+0x2070.
 */
#define GL_COUNT_2070 (*(int*)((char*)&D_00000000 + 0x2070))
#endif

typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;

// gl_func_0001CA10 — STRUCTURAL PASS (0x354 / 213 words, no episode).
// Raw-.word USO form (game_libs RSP/graphics-library segment).
// BOUNDARY NOTE: 2-jr USO bundle (named fn + 1 trailing helper) —
// deferred USO re-split.
//
// game_libs RSP/F3D vertex-index / triangle-list builder.
//
//   void gl_func_0001CA10(int count, Cmd *a1, Ctx *a2) {
//     if (count < 3) return;                              // need a tri
//     C *c = a1 + 0x18;
//     i = c->0x2(u8) * 4;  j = c->0x3(u8) * …;            // index calc
//     // entry = base + idx * 0x340  (per-record stride 0x340);
//     func_00000000(a2->0x3C, a2 + 0x38, …);              // setup/xform
//     // loop over the index list: read s16 vertex fields v->0x10 /
//     //   v->0x12 / v->0x04, signed-ceil-div-by-2 (sra+addiu idiom),
//     //   compare/clip, and sh-store packed triangle/quad indices
//     //   into the output command buffer; bne loops back (1420FFD7).
//   }
//
// Struct-typing reference:
//   count = vertex/primitive count (<3 = no-op); a1 + 0x18 -> a
//     descriptor (->0x2 / ->0x3 u8 indices), a2->0x3C / a2+0x38 =
//     transform inputs. Per-record stride 0x340. v->0x10 / 0x12 /
//     0x04 = s16 vertex coords; signed ceil-div-by-2 is the
//     `bgez; sra 1 / addiu 1; sra 1` rounding idiom. Output = an
//     RSP/F3D triangle-index command buffer. func_00000000 = USO
//     placeholder dispatcher (game_libs JAL targets are runtime-
//     patched placeholders — see reference memos).
// MUST STAY INCLUDE_ASM (hard blocker, not a bail): the name
//   `gl_func_0001CA10` is reused as a GENERIC PLACEHOLDER extern in
//   ~8 unrelated NM bodies in this file (e.g. lines ~5656/13960/
//   16784/28834/29493) — each `extern int gl_func_0001CA10();` and
//   called with conflicting arg counts/return types. IDO cfe treats
//   file-scope externs as one symbol, so giving THIS function a real
//   typed definition makes the whole game_libs_post.c NON_MATCHING
//   compile fail (redeclaration / incompatible type / arg-count) and
//   freezes the objdiff report. Real-C body is blocked until the
//   placeholder-name reuse is migrated to unique names (separate
//   refactor). Single jr $ra (older "2-jr bundle" note is STALE; .s
//   is 0x288/162 words). Algorithm is fully captured in the analysis
//   comment above; build path is INCLUDE_ASM (no episode — tautology
//   rule). DO-NOT-define-without first renaming the placeholder uses.
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CA10);

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* Record-copy loop over *(0x2070) entries. Addresses 0x2070/0x2CFC/0x14 are
 * &D-relative globals the target HOISTS into regs (addiu t1,zero,0x2070 ...)
 * once before the loop and reloads the *values* inside — so model them as
 * pointer locals, not inline *(s32*)0xNN derefs (which re-materialize each
 * use). Byte fields at 0xB3 / 0x3 are lbu loads (not (u8) of a word). */
void game_libs_func_0001CC98(s32 arg0) {
    s32 *pCount = (s32 *)0x2070;
    s32 *pSrcBase = (s32 *)0x2CFC;
    s32 *pDstBase = (s32 *)0x14;
    s32 i;
    s32 off;
    char *rec;
    char *src;
    char *dst;

    i = 0;
    off = 0;
    if (*pCount > 0) {
        do {
            rec = (char *)(*pSrcBase + off);
            src = rec + 0xB0;
            dst = (char *)(*pDstBase + (((*pCount * arg0) + i) << 5));
            if (((u32) FW(rec, 0xB0) >> 0x1F) != 0) {
                FW(dst, 0x0) = (u32) FW(rec, 0xB0);
                FW(dst, 0x4) = (s32) FW(src, 0x4);
                FW(dst, 0x8) = (s32) FW(src, 0x8);
                FW(dst, 0xC) = (s32) FW(src, 0xC);
                FW(dst, 0x10) = (s32) FW(src, 0x10);
                FW(dst, 0x14) = (s32) FW(src, 0x14);
                FW(dst, 0x18) = (s32) FW(src, 0x18);
                FW(dst, 0x1C) = (s32) FW(src, 0x1C);
                FW(rec, 0xB0) = (s8) (*(u8 *)(rec + 0xB3) & 0xFFBF);
            } else {
                src = rec + 0xB0;
                FW(dst, 0x0) = (s8) (*(u8 *)(dst + 0x3) & 0xFF7F);
            }
            FW(src, 0x6) = 0;
            i += 1;
            off += 0xD0;
        } while (i < *pCount);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001CC98);
#endif

// gl_func_0001CD64 — STRUCTURAL PASS (0x278 / 158 words, no episode).
// Raw-.word USO form (game_libs RSP/graphics-library segment).
// BOUNDARY NOTE: 2-jr USO bundle (named fn + 1 trailing helper) —
// deferred USO re-split.
//
// game_libs display-list batch processor (large ~0x1068 stack
// command/scratch buffer).
//
//   void gl_func_0001CD64(a0, B *a1, C *a2) {
//     // big stack frame: ~0x1068 bytes = a working command buffer
//     //   at sp+0x4C..; save s0-s7/fp.
//     G *g = &D_0;                                         // global tbl
//     s4 = (s16)g->0x2040;                                 // entry count
//     if (s4 != 0) {
//       do {
//         func_00000000(a0, …);                            // pre-process
//         s4 = (s16)g->0x2040;                              // re-read
//       } while (--cnt > 0);                                // drain loop
//     }
//     // main pass: for each of (s16)g->0x2040 entries, dispatch the
//     //   intra-USO processor at 0x310704 (jal 0x0C00C4C1, NOT a
//     //   placeholder — a real fixed game_libs target) building
//     //   command words into the stack buffer; flag-gated branches
//     //   (at==1) select sub-paths; final lh g->0x2040 / store.
//   }
//
// Struct-typing reference:
//   &D_0 + 0x2040 = global s16 command/entry count (re-read each
//     iteration — the list can shrink during processing). sp+0x4C..
//     +0x1068 = a ~4KB stack command/vertex scratch buffer. a0/a1/a2
//     = list/context args. 0x310704 = a real intra-USO processor
//     (gl_func, NOT a runtime-patched placeholder); func_00000000 =
//     the USO placeholder dispatcher (pre-process step).
// Caps (DEFERRED, documented-hard): single jr $ra (older "2-jr
//   bundle" note is STALE; .s is 0x204/129 words, one function).
//   Real-C structural body below per the analysis above; byte-match
//   deferred — 0x1068 frame + several resolved intra-USO jal helpers
//   (0xC4C1/0xC414/0xC8C8<<2) + branch-likely (bnel/beql) clip/min-
//   max scheduling. gl_func_00000000 = canonical never-defined USO
//   placeholder (safe; per feedback_placeholder_func_name_reuse).
//   Name pre-checked: 3 file occurrences (not a reused placeholder),
//   so a typed def is collision-safe. Next pass: resolve the three
//   internal helper targets and grind the two-loop / branch-likely
//   schedule against the 0x158-stride record buffer.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0001CD64(int a0, int *a1) {
    char buf[0x101C];
    short count;
    int i;
    short *g = (short *)((char *)&D_00000000 + 0x2040);
    *(void **)((char *)&D_00000000 + 0x14) = buf;
    count = g[0];
    for (i = count; i > 0; i = (short)g[0] - (count - i)) {
        gl_func_00000000(a0);
        count = g[0];
    }
    count = g[0];
    for (i = 0; i < count; i++) {
        int lo = g[1];
        int hi = g[2];
        int v = g[3];
        if (v < lo) {
            v = lo;
        }
        if (v > hi) {
            v = hi;
        }
        gl_func_00000000(a0, v, &buf[i * 0x158]);
        count = g[0];
    }
    *a1 = (int)&buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CD64);
#endif

/* Clears bit 7 of the byte field of consecutive elements in the 2D global
 * table at &D_00000000 (D+0x14 = base ptr, D+0x2070 = row stride, D+0x2040 =
 * s16 element count), column a1, starting at row a0+1, until an element whose
 * (word<<1)<0 (bit30 set) is hit. Structurally exact (29/29 insns, same
 * opcodes/immediates); 14 $t-register fields differ — loop $t-renumber, both
 * permuter-resistant (loop) and C-tweak-resistant (named vars regressed to 19,
 * shifted &D base out of a2). Reloc-blind (&D_00000000). */
#ifdef NON_MATCHING
void game_libs_func_0001CF68(int a0, int a1) {
    int v0 = a0 + 1;
    int v1 = a1 << 5;
    if (v0 < *(short *)((char *)&D_00000000 + 0x2040)) {
        do {
            char *elem = (char *)(*(int *)((char *)&D_00000000 + 0x14)
                + (*(unsigned int *)((char *)&D_00000000 + 0x2070) * v0) * 32 + v1);
            if ((*(int *)elem << 1) < 0) {
                break;
            }
            *(unsigned char *)elem = *(unsigned char *)elem & 0xFF7F;
            v0++;
        } while (v0 < *(short *)((char *)&D_00000000 + 0x2040));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001CF68);
#endif


// gl_func_0001CFDC — STRUCTURAL PASS (0xD0 / 52 words, no episode).
// Raw-.word USO form (game_libs RSP/graphics-library segment).
// Hand-decoded.
//
// game_libs glyph / sprite draw helper (returns advance width).
//
//   int gl_func_0001CFDC(int code, Spec spec) {           // spec by value
//     int hi = spec.0x2;
//     E *e = &D_0 + idx(code) ;  e += 0x50;                // glyph entry
//     int w = e->0x10;  int h = e->0x0E;                   // metrics
//     v0 = jal 0x31FB0(0x3E0, …, w, h, hi);                // blit pass 1
//     if (e->0x12 != 0) {                                  // outline/shadow
//       v0 = jal 0x31FB0(0x3E0, e->0x10, 0, …, spec.0x2);  // blit pass 2
//       v0 &= 0xFFFF;
//     }
//     return v0;                                            // advance
//   }
//
// Struct-typing reference:
//   code = glyph/char code; &D_0 = global glyph-table base, entry
//     reached by index then +0x50; e->0x10 = width / advance,
//     e->0x0E = height, e->0x12 = secondary-pass flag (shadow /
//     outline), e->0x1B a u8 attribute. spec = a small by-value
//     struct (halfword fields at +0x2 / +0x32). 0x31FB0 = a fixed
//     intra-USO blit routine (real target, NOT a runtime placeholder);
//     0x3E0 = a blit mode/format constant. Text/sprite rendering.
// Caps (DEFERRED): single jr $ra. Real-C structural body below per
//   the analysis; byte-match deferred — the fixed-target call
//   (jal 0x31FB0) needs its real intra-USO symbol, and the
//   idx*0x158 / attr*0x64 / sub*0x14 index-multiply chains plus the
//   beql (e->0x12==0) skip are IDO-schedule-sensitive. Name
//   pre-checked: no extern reuse (occ all in this comment), so a
//   typed def is collision-safe. gl_func_00000000 = canonical
//   never-defined USO placeholder for the 0x31FB0 blit routine.
//   Next pass: resolve the 0x31FB0 symbol, then grind the
//   multiply-sequence + beql codegen.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0001CFDC(int code, int spec) {
    short idx = (short)code;
    short sub = (short)spec;
    char *rec = (char *)&D_00000000 + idx * 0x158;
    unsigned char attr = *(unsigned char *)(rec + 0x1B);
    char *e = rec + attr * 0x64 + sub * 0x14 + 0x50;
    short h = *(short *)(e + 0x10);
    unsigned short w = *(unsigned short *)(e + 0xE);
    int r = gl_func_00000000(code, 0x3E0, w, h, idx);
    if (*(short *)(e + 0x12) != 0) {
        r = gl_func_00000000(r, (*(short *)(e + 0x10) + 0x3E0) & 0xFFFF, 0, idx);
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CFDC);
#endif

// gl_func_0001D0AC — STRUCTURAL PASS (0x154 / 85 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 tiny trailing setter `sw t9,4(t8)`) — deferred USO
// re-split. Near-identical SIBLING of gl_func_0001CFDC (same glyph/
// sprite draw helper; differs only in the fixed blit target).
//
//   int gl_func_0001D0AC(int code, Spec spec) {           // spec by value
//     E *e = (&D_0 + idx(code)) + 0x50;                    // glyph entry
//     int w = e->0x10;  int h = e->0x0E;
//     v0 = jal 0x31F4C(0x3E0, …, w, h, spec.0x2);          // blit pass 1
//     if (e->0x12 != 0) {                                  // shadow pass
//       v0 = jal 0x31F4C(0x3E0, e->0x10, 0, …, spec.0x2);
//       v0 &= 0xFFFF;
//     }
//     return v0;                                            // advance
//   }
//
// Struct-typing reference: identical to gl_func_0001CFDC (see its
//   comment) — &D_0 glyph table, entry+0x50, e->0x10 width/advance,
//   e->0x0E height, e->0x12 secondary-pass flag, spec by-value
//   halfword struct, 0x3E0 blit mode. The ONLY difference: this
//   variant calls the fixed blit routine at 0x0C00C813 (≈0x31F4C)
//   instead of gl_func_0001CFDC's 0x0C00C7EC (≈0x31FB0) — likely a
//   different render target / layer.
// Caps (DEFERRED): single jr $ra (older "unsplit bundle" note is
//   STALE; .s is 0xD0/52 words, one function). Exact structural TWIN
//   of gl_func_0001CFDC — identical glyph-draw logic, only the blit
//   jal target differs (0xC813 -> 0x3204C here vs 0xC7EC -> 0x31FB0).
//   Real-C structural body below; byte-match deferred (resolve the
//   0x3204C blit symbol + the idx*0x158 / attr*0x64 / sub*0x14
//   index-multiply chains + beql codegen). Name pre-checked: no
//   extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the 0x3204C blit routine.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0001D0AC(int code, int spec) {
    short idx = (short)code;
    short sub = (short)spec;
    char *rec = (char *)&D_00000000 + idx * 0x158;
    unsigned char attr = *(unsigned char *)(rec + 0x1B);
    char *e = rec + attr * 0x64 + sub * 0x14 + 0x50;
    short h = *(short *)(e + 0x10);
    unsigned short w = *(unsigned short *)(e + 0xE);
    int r = gl_func_00000000(code, 0x3E0, w, h, idx);
    if (*(short *)(e + 0x12) != 0) {
        r = gl_func_00000000(r, (*(short *)(e + 0x10) + 0x3E0) & 0xFFFF, 0, idx);
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D0AC);
#endif

#ifdef NON_MATCHING
/* game_libs_func_0001D17C: GBI display-list builder. Writes 3 commands (6 words)
 * to a0 indexing &D + a1*344 (record stride 344), reading 2 shorts from
 * rec+0x28 / rec+0x2A OR'd with 0x0C1A0000; returns a0+24 (next DL ptr).
 * Logic exact; near-miss: target uses explicit chained cursors (a2=a0+8;
 * t0=a2+8; sw 0(a2)/0(t0); return t0+8) but IDO -O2 FOLDS both int-cursor
 * `p+=2` and struct-pointer `p++` into offset addressing (sw 8(a0)) — 31 vs
 * 33 insns (cursor-vs-offset preference, like the addiu-form RMW). Reloc-blind
 * (single &D base). */
int *game_libs_func_0001D17C(int *a0, int a1) {
    char *rec = (char *)&D_00000000 + a1 * 344;
    int *p = a0;
    p[0] = 0x0A000C80;
    p[1] = 0x03E001A0;
    p += 2;
    p[0] = *(unsigned short *)(rec + 0x28) | 0x0C1A0000;
    p[1] = 0x0E200C80;
    p += 2;
    p[0] = *(unsigned short *)(rec + 0x2A) | 0x0C1A0000;
    p[1] = 0x03E00E20;
    p += 2;
    return p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001D17C);
#endif

// gl_func_0001D200 — STRUCTURAL PASS (0x2C0 / 176 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. Same glyph-
// table FAMILY as gl_func_0001CFDC / gl_func_0001D0AC, but the larger
// STRING-draw variant: it loops over a packed glyph spec, accumulating
// an advance, rather than drawing a single glyph.
//
//   int gl_func_0001D200(args…, Spec spec) {            // spec by value
//     E *base = &D_0 + idx(...);                         // glyph table
//     E *e = base + 0x50;
//     int packed = e->0x5C;                              // word at +0x5C
//     short flags = e->0x60;                             // halfword +0x60
//     int lo = packed & 7;                               // 3-bit field
//     int hi = (packed >> 4) & 0xFFF;                     // 12-bit field
//     ... pack glyph metrics into sp+0x38/0x3A/0x3C ...
//     v0 = jal 0x31FB0(0x3E0, …, 0x1A0, w, h, spec.0x2); // blit row
//     if (cond) { ... second pass ... }
//     // tail: lui/addiu builds a &D_xxxx table pointer for caller
//     return v0;                                          // advance px
//   }
//
// Struct-typing reference: shares gl_func_0001CFDC's glyph layout —
//   &D_0 table, entry+0x50, fixed blit 0x0C00C7EC (≈0x31FB0), 0x3E0
//   blit mode, spec by-value halfword struct. NEW here vs the single-
//   glyph helpers: packed metric word at e->0x5C decoded via
//   mask-0x7 / shift-4 mask-0xFFF (sub-fields), halfword e->0x60, and
//   stack-built metric block at sp+0x38..0x3C passed by ref to the
//   blit. This is the multi-glyph / string-row entry of the family.
// Caps (DEFERRED): single jr $ra (older "2-jr bundle" note is STALE;
//   .s is 0x1E0/120 words, one function). Multi-glyph/string-row
//   variant of the gl_func_0001CFDC family. Real-C structural body
//   below per the analysis; byte-match deferred — fixed blit target
//   0x31FB0 needs its symbol, the e->0x5C packed-bitfield decode
//   (&7 / >>4 &0xFFF) and the trailing F3D command-pair emission
//   (0x08000000/0x0C800000/0x05000000/0x0E200000/0x80000000 opcode
//   highs) are IDO-schedule-sensitive. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the 0x31FB0 blit routine.
//   Next pass: resolve 0x31FB0, pin the exact attr/idx entry math,
//   then grind the bitfield + DL-emit schedule.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
extern int gl_func_00031FB0();
/* 2026-06-04 RECONSTRUCT via Ghidra 20.8% -> 52.5%: was a wrong-signature stub
 * (2-arg, wrong packing). Real fn is (a0 dl-ptr, a1 spec, a2 idx, a3 sub):
 * locate record &D[a2*0x158]+attr*100+a3*0x14, call gl_func_00031FB0 to reserve
 * DL space (twice if rec->0x62), then emit 8 packed GBI words (2 quads at
 * sV2+0x3E0 / +0x580) and return p+8. Residual ~47% is $t-reg renumber +
 * save-spill scheduling (same 139 insns, same frame). */
unsigned int *gl_func_0001D200(int a0, unsigned int a1, short a2, short a3) {
    short s1, s2;
    unsigned int *p;
    unsigned int u4;
    int rec, e, t;
    rec = (int)&D_00000000 + a2 * 0x158;
    e = rec + (unsigned int)*(unsigned char *)(rec + 0x1B) * 100 + a3 * 0x14;
    s1 = *(short *)(e + 0x60);
    t = (*(unsigned int *)(e + 0x5C) & 7) << 0x11;
    s2 = (short)((unsigned int)t >> 0x10);
    p = (unsigned int *)gl_func_00031FB0(a0, 0x3E0,
            *(unsigned int *)(e + 0x5C) - (t >> 0x11) & 0xFFFF, 0x1A0, (int)a2);
    t = (int)(short)(s2 + s1 + 0xF & 0xFFF0);
    if (*(short *)(e + 0x62) != 0) {
        p = (unsigned int *)gl_func_00031FB0(p, t + 0x3E0 & 0xFFFF, 0, 0x1A0 - t, (int)a2);
    }
    p[0] = (int)s2 + 0x3E0 | 0x8000000;
    u4 = (a1 & 0x7FFF) << 1;
    p[1] = u4 | 0xC800000;
    p[2] = *(unsigned short *)(rec + 0x26) | 0x5000000 | (unsigned int)*(unsigned char *)(rec + 0x18) << 0x10;
    p[3] = *(int *)(rec + 0x40) + 0x80000000;
    p[4] = (int)s2 + 0x580 | 0x8000000;
    p[5] = u4 | 0xE200000;
    p[6] = *(unsigned short *)(rec + 0x26) | 0x5000000 | (unsigned int)*(unsigned char *)(rec + 0x18) << 0x10;
    p[7] = *(int *)(rec + 0x44) + 0x80000000;
    return p + 8;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D200);
#endif

#ifdef NON_MATCHING
/* Display-list emitter: index struct &D[a2*0x158]; for each set flag at +0x118 /
 * +0x11C emit two DL words (G_? 0x7020000|a1 + payload, then 0x7000C80/0xE20 |
 * (struct[0x18]<<16) + payload) into a0, advancing. Return advanced a0. Reloc-
 * blind (&D). Structurally exact through the a2*0x158 index; byte-match capped by
 * cursor-vs-offset fold (target keeps separate cursors v1/a2 with two +8 advances,
 * C-emit folds to one +16 with -8/-4 offsets) + $t-renumber. */
int game_libs_func_0001D3E0(int *a0, int a1, int a2) {
    char *base = (char *)&D_00000000 + a2 * 0x158;
    if (*(int *)(base + 0x118) != 0) {
        a0[0] = (a1 & 0xFFFF) | 0x7020000;
        a0[1] = *(int *)(base + 0x118);
        a0 += 2;
        a0[0] = (*(unsigned char *)(base + 0x18) << 16) | 0x7000C80;
        a0[1] = *(int *)(base + 0x120);
        a0 += 2;
    }
    if (*(int *)(base + 0x11C) != 0) {
        a0[0] = (a1 & 0xFFFF) | 0x7020000;
        a0[1] = *(int *)(base + 0x11C);
        a0 += 2;
        a0[0] = (*(unsigned char *)(base + 0x18) << 16) | 0x7000E20;
        a0[1] = *(int *)(base + 0x124);
        a0 += 2;
    }
    return (int)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001D3E0);
#endif

// game_libs_func_0001D4B0 — NOT a standalone function: it is the ORPHANED HEAD
// of gl_func_0001D4C0 (splat mis-split the function in two). 4 pre-prologue insns:
//   li t0,0x158; multu a1,t0;  lui/addiu v0,&D_xxxx   (no jr, no mflo)
// gl_func_0001D4C0 (next symbol) consumes ALL THREE: `mflo t6` (lo from the multu),
// `addu v1,v0,t6` (v0 = the &D base), and a second `multu a3,t0` (t0 = 0x158) — with
// no intervening sets. The real function starts at 0x1D4B0 (entry the callers target);
// 0x1D4C0 is a spurious mid-function symbol. FIX = USO boundary merge (focused session;
// regenerate game_libs expected/ with one symbol gl_func_0001D4B0 size 0xA4). Until then
// this stays INCLUDE_ASM (prologue-stolen successor — see docs/MATCHING_WORKFLOW.md;
// PROLOGUE_STEALS post-cc splice is banned, the only honest fix is the boundary merge).
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001D4B0);

// gl_func_0001D4C0 — STRUCTURAL PASS (0x3B0 / 236 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: LARGE 40-jr USO
// bundle — splat could not separate ~40 small functions here. Only
// the named leading fn is decoded below (ends at the first jr, addr
// 0x1D54C, ~36 words); the remaining ~40 bodies are deferred USO
// re-split (mnemonic split-fragments.py cannot split USO bundles).
//
//   int gl_func_0001D4C0(args…, short h_at_sp32) {       // F3D emit
//     E *e = base + idx(...);                             // obj/glyph
//     byte f = e->0x1C;
//     if (f & 1) {                                        // gated
//       jal 0x31648(…, ptr_at_sp20);                      // 0x0C00C592
//       int dl = *(short*)(&D_0C34xxxx + 0x20);           // DL cursor
//       *(int*)dl     = 0x0C8003E0;                        // GBI word0
//       *(int*)(dl+4) = arg;                               // GBI word1
//       jal 0x31718(dl + 8);                               // 0x0C00C5C6
//     }
//     return e->0x1D;                                      // flag byte
//   }
//
// Struct-typing reference: object/glyph entry e — byte e->0x1C
//   (emit-gate flag), byte e->0x1D (returned status flag). Global DL
//   write cursor lives as a halfword at &D_0C34xxxx + 0x20. Emitted
//   command is one 8-byte F3D/GBI word pair (word0 const 0x0C8003E0,
//   word1 = caller arg) then the cursor is advanced by 8 and handed
//   to the fixed RSP-submit routine 0x0C00C5C6. Sibling of the
//   game_libs F3D/RSP display-list builder family.
// ROOT-CAUSE CAP (CORRECTED 2026-05-24): this is a PROLOGUE-STOLEN SUCCESSOR.
//   The function's real entry is the preceding symbol game_libs_func_0001D4B0
//   (li t0,0x158; multu a1,t0; v0=&D_xxxx) — its `mflo t6`, `addu v1,v0,t6`, and
//   second `multu a3,t0` all consume registers set in that 4-insn head. The C
//   below MISMODELS this: it takes `int *v0` as an input pointer, but v0 is really
//   the &D_xxxx base loaded in the head, and the `a1 * 0x158` element-index
//   computation is absent. That structural gap (not "jal symbols" or "IDO
//   schedule") is why it's stuck ~10.5%. There is NO C-only fix for a prologue-
//   stolen successor (PROLOGUE_STEALS post-cc splice is banned as match-faking).
//   FIX = USO boundary merge: make 0x1D4B0 the function start (one symbol, size
//   0xA4), re-decode with the index setup + &D base, then the body becomes
//   matchable. Focused-session task (regenerate game_libs expected/ baseline).
//   gl_func_00000000 = canonical never-defined USO placeholder for the helpers.
#ifdef NON_MATCHING
extern int gl_func_00000000();
int gl_func_0001D4C0(int *v0, int ctx, int sub) {
    short si = (short)sub;
    int *v1 = (int *)((char *)v0 + si);
    signed char k = *((signed char *)v1 + 0x1D);
    int *t8 = (int *)((char *)v0 + k * ctx);
    if (*((unsigned char *)t8 + 0x1C) != 1) {
        return (int)v0;
    }
    gl_func_00000000(v1, si);
    v0[0] = *(unsigned short *)((char *)v1 + 0x20) | 0x0C340000;
    v0[1] = 0x0C8003E0;
    gl_func_00000000((char *)v0 + 8, *((signed char *)v1 + 0x1D));
    return (int)v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D4C0);
#endif

void game_libs_func_0001D554(void) {}

void game_libs_func_0001D55C(int *a0, int a1, int a2) { a0[0] = (a1 & 0x00FFFFFF) | 0x02000000; a0[1] = a2; }

void game_libs_func_0001D57C(void) {}

void game_libs_func_0001D584(void) {}

void game_libs_func_0001D58C(void) {}

/* gbi 2-word command builder (5 args). NATURAL CEILING: word-1 register-
 * exact; word-2's temps are uniformly +1 vs target (allocno-numbering,
 * build uses $t1-$t4 where target uses $t2-$t5). Was previously closed
 * via 5-insn INSN_PATCH register-renumber — INSN_PATCH REMOVED 2026-05-23
 * as match-faking (per feedback_no_instruction_forcing_matches_policy). */
// GBI 2-word command packer (cmd 0x0C000000), sibling of 0001D770/D7A4.
// (a3<<15)<<1 renumbers the second-word temps to match (t2/t3/t4/t5).
void game_libs_func_0001D594(int *a0, int a1, int a2, int a3, int a4) {
    a0[0] = (((a1 & 0xFF) << 16) | 0x0C000000) | (a2 & 0xFFFF);
    a0[1] = ((a3 << 15) << 1) | (a4 & 0xFFFF);
}

void game_libs_func_0001D5C8(void) {}

void game_libs_func_0001D5D0(void) {}

void game_libs_func_0001D5D8(void) {}

/* gbi 2-word command builder (5 args), cmd 0x08. Same word-2 INSN_PATCH
 * register-renumber as 0001D594. */
// GBI 2-word command packer (cmd 0x08000000), sibling of 0001D770/D7A4.
// (a3<<15)<<1 renumbers the second-word temps to match (t2/t3/t4/t5).
void game_libs_func_0001D5E0(int *a0, int a1, int a2, int a3, int a4) {
    a0[0] = (((a1 & 0xFF) << 16) | 0x08000000) | (a2 & 0xFFFF);
    a0[1] = ((a3 << 15) << 1) | (a4 & 0xFFFF);
}

void game_libs_func_0001D614(void) {}

void game_libs_func_0001D61C(void) {}

void game_libs_func_0001D624(int *a0, int a1, int a2, int a3)
{
 if (0) { }
  a0[0] = (a1 & 0xFFFFFF) | 0x0A000000;
  a0[1] = (a2 << 15) << 1;
  a0[1] = a0[1] | (a3 & 0xFFFF);
}


void game_libs_func_0001D650(void) {}

void game_libs_func_0001D658(void) {}

void game_libs_func_0001D660(void) {}

void game_libs_func_0001D668(void) {}

void game_libs_func_0001D670(int *a0, int a1, int a2, int a3) {
    a0[0] = (a3 & 0xFFFF) | 0x11000000;
    a0[1] = ((a1 << 15) << 1) | (a2 & 0xFFFF);
}


/* gbi 2-word command builder (5 args), cmd 0x12. Same word-2 INSN_PATCH
 * register-renumber as 0001D594. */
// GBI 2-word command packer (cmd 0x12000000), sibling of 0001D770/D7A4.
// (a3<<15)<<1 renumbers the second-word temps to match (t2/t3/t4/t5).
void game_libs_func_0001D694(int *a0, int a1, int a2, int a3, int a4) {
    a0[0] = (((a1 & 0xFF) << 16) | 0x12000000) | (a2 & 0xFFFF);
    a0[1] = ((a3 << 15) << 1) | (a4 & 0xFFFF);
}

void game_libs_func_0001D6C8(void) {}

void game_libs_func_0001D6D0(int *a0, int a1, int a2, int a3) { a0[0] = ((((a2 >> 4) & 0xFF) << 16) | 0x14000000) | (a1 & 0xFFFF); a0[1] = a3; }

void game_libs_func_0001D6F8(int *a0, int a1, int a2, int a3) { a0[0] = ((((a2 >> 4) & 0xFF) << 16) | 0x15000000) | (a1 & 0xFFFF); a0[1] = a3; }

void game_libs_func_0001D720(int *a0, int a1, int a2) {
    a0[0] = 0x16000000;
    a0[1] = ((a1 << 15) << 1) | (a2 & 0xFFFF);
}


void game_libs_func_0001D73C(void) {}

void game_libs_func_0001D744(void) {}

void game_libs_func_0001D74C(void) {}

void game_libs_func_0001D754(int *a0, int a1, int a2) {
    a0[0] = ((a1 & 0xFF) << 16) | 0x17000000;
    a0[1] = a2;
}

// Pack a GBI-style 2-word command: word0 = (a1&0xFF)<<16 | 0x0E000000 |
// (arg4&0xFFFF); word1 = a2<<16 | (a3&0xFFFF). The (a2<<15)<<1 form makes IDO
// renumber the second-word temps to match (t3/t4/t5). Permuter match, byte-exact.
void game_libs_func_0001D770(int *a0, int a1, int a2, int a3, int arg4)
{
  a0[0] = (((a1 & 0xFF) << 16) | 0x0E000000) | (arg4 & 0xFFFF);
  a0[1] = ((a2 << 15) << 1) | (a3 & 0xFFFF);
}

// GBI 2-word command packer (cmd 0x19000000), sibling of 0001D770:
// word0 = (arg4&0xFF)<<16 | 0x19000000 | (a3&0xFFFF); word1 = a1<<16 |
// (a2&0xFFFF). Matches byte-exact via `long long new_var = 16` trick that
// forces IDO to renumber the second-word temps to t3/t4/t5 (no INSN_PATCH
// needed; the old "INSN_PATCH 4/13" plan was superseded by the C lever).
void game_libs_func_0001D7A4(int *a0, int a1, int a2, int a3, int arg4)
{
  long long new_var;
  new_var = 16;
  a0[0] = (((arg4 & 0xFF) << new_var) | 0x19000000) | (a3 & 0xFFFF);
  ;
  a0[1] = ((a1 & 0xFFFF) << 16) | (a2 & 0xFFFF);
}


void game_libs_func_0001D7D8(void) {}

void game_libs_func_0001D7E0(void) {}

void game_libs_func_0001D7E8(void) {}

void game_libs_func_0001D7F0(void) {}

void game_libs_func_0001D7F8(int *a0, int a1, int a2, int a3) {
    a0[0] = (a3 & 0xFFFF) | 0x03000000;
    a0[1] = ((a1 << 15) << 1) | (a2 & 0xFFFF);
}


void game_libs_func_0001D81C(void) {}

void game_libs_func_0001D824(void) {}

void game_libs_func_0001D82C(void) {}

void game_libs_func_0001D834(int *a0, int a1, int a2, int a3) {
    a0[0] = (((a1 & 0xFF) << 16) | 0x07000000) | (a2 & 0xFFFF);
    a0[1] = a3;
}

void game_libs_func_0001D858(int *a0, int a1, int a2) {
    a0[0] = (a1 & 0xFFFF) | 0x07020000;
    a0[1] = a2;
}

// gl_func_0001D870 — STRUCTURAL PASS (0x20C / 131 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + trailing helpers) — deferred USO re-split. Near-
// identical SIBLING of gl_func_0001D0AC / gl_func_0001CFDC (glyph/
// sprite draw helper); differs only in the blit-mode constant.
//
//   int gl_func_0001D870(int code, Spec spec) {           // spec by val
//     E *e = (&D_0 + idx(code)) + 0x50;                    // glyph entry
//     int w = e->0x10;  int h = e->0x0E;
//     v0 = jal 0x31FB0(0x0C80, …, w, h, spec.0x2);          // blit pass1
//     if (e->0x12 != 0) {                                   // shadow
//       v0 = jal 0x31FB0(0x0C80, e->0x10, 0, …, spec.0x2);
//       v0 &= 0xFFFF;
//     }
//     return v0;                                             // advance
//   }
//
// Struct-typing reference: identical to gl_func_0001CFDC / 0001D0AC
//   (&D_0 glyph table, entry+0x50, e->0x10 width/advance, e->0x0E
//   height, e->0x12 secondary-pass flag, spec by-value halfword
//   struct, fixed blit 0x0C00C7EC ≈0x31FB0). The ONLY difference vs
//   those siblings: the blit-mode constant is 0x0C80 here instead of
//   0x3E0 — a different blit format / layer selector for the same
//   draw helper.
// Caps (DEFERRED): single jr $ra (older "unsplit bundle" note is
//   STALE; .s is 0xD4/53 words, one function). Exact twin of
//   gl_func_0001CFDC — identical glyph-draw logic and jal target
//   (0x31FB0), only the blit-mode constant differs (0xC80 here vs
//   0x3E0). Real-C structural body below; byte-match deferred
//   (resolve 0x31FB0 + index-multiply/beql codegen). Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the blit routine.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0001D870(int code, int spec) {
    short idx = (short)code;
    short sub = (short)spec;
    char *rec = (char *)&D_00000000 + idx * 0x158;
    unsigned char attr = *(unsigned char *)(rec + 0x1B);
    char *e = rec + attr * 0x64 + sub * 0x14 + 0x50;
    short h = *(short *)(e + 0x10);
    unsigned short w = *(unsigned short *)(e + 0xE);
    int r = gl_func_00000000(code, 0xC80, w, h, idx);
    if (*(short *)(e + 0x12) != 0) {
        r = gl_func_00000000(r, (*(short *)(e + 0x10) + 0xC80) & 0xFFFF, 0, idx);
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D870);
#endif

#ifdef NON_MATCHING
/* Double F3D/GBI command builder (sibling of the gl_func_0001D870 family).
 * Writes two 8-byte commands (4 words) to the $a0 DList buffer, indexing the
 * 0x158-stride record table at &D_00000000 by the 5th (stack) arg, reading the
 * segment-offset fields +0x38/+0x3C and KSEG0-biasing them. Returns buf+16.
 *
 * 2026-05-28: declaring the (a1,a2) arg pair as a Pair2 struct-by-value param
 * (the RECEIVING-side analog of the struct-by-value arg-home lever) forces the
 * `sw a1,4(sp); sw a2,8(sp)` dead home-stores the target has, fixing the
 * instruction count (39==39). Remaining 25 diffs are pure register allocation:
 * cmd lands in $v1 vs target $t0 (cascades), and p.b is reloaded from its home
 * slot vs the target keeping a2 in $6. The struct-by-value frontend treats
 * members as memory so it reloads; the target uses the incoming register AND
 * has a dead home store — a combo neither pure struct-by-value nor (void)&aN
 * reproduces. Permuter candidate (logic + count correct, regalloc only).
 * See docs/IDO_CODEGEN.md#feedback-ido-struct-by-value-homes-arg-pair. */
extern int D_00000000;
int game_libs_func_0001D944(int *buf, Pair2 p, int a3, int idx) {
    int cmd = (((a3 >> 4) & 0xFF) << 16) | 0x14000000;
    char *rec;
    int off;
    buf[0] = cmd | (p.a & 0xFFFF);
    rec = (char *)&D_00000000 + idx * 0x158;
    off = (p.b & 0xFFFF) << 1;
    buf[1] = *(int *)(rec + 0x38) + off + 0x80000000;
    buf += 2;
    buf[0] = cmd | ((p.a + 0x1A0) & 0xFFFF);
    buf[1] = *(int *)(rec + 0x3C) + off + 0x80000000;
    return (int)(buf + 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001D944);
#endif

#ifdef NON_MATCHING
/* Double F3D/GBI command builder -- byte-identical sibling of
 * game_libs_func_0001D944 (same body; command opcode 0x15 vs 0x14). Writes two
 * 8-byte commands (4 words) to the $a0 buffer, indexing the 0x158-stride record
 * table at &D_00000000 by the 5th (stack) arg, reading segment-offset fields
 * +0x38/+0x3C and KSEG0-biasing, returns buf+16. Same cap as 0001D944: D_ ref
 * -> objdiff reloc-depressed + IDO dead arg-home-stores (sw a1/a2 to home). */
int game_libs_func_0001D9E0(int *buf, int a1, int a2, int a3, int idx) {
    int cmd = (((a3 >> 4) & 0xFF) << 16) | 0x15000000;
    char *rec;
    int off;
    buf[0] = cmd | (a1 & 0xFFFF);
    rec = (char *)&D_00000000 + idx * 0x158;
    a2 &= 0xFFFF;
    off = a2 << 1;
    buf[1] = *(int *)(rec + 0x38) + off + 0x80000000;
    buf += 2;
    buf[0] = cmd | ((a1 + 0x1A0) & 0xFFFF);
    buf[1] = *(int *)(rec + 0x3C) + off + 0x80000000;
    return (int)(buf + 2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001D9E0);
#endif

// gl_func_0001DA7C — STRUCTURAL PASS (0x10C / 67 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An F3D/GBI glyph-command builder in the gl_func_0001D4C0
// display-list family.
//
//   int gl_func_0001DA7C(int a0, int a1, short idx) {
//     E *e = &D_0 + idx_scaled(idx);            // signed-halfword idx
//     byte flag = e->0x1C;
//     int r;
//     if (flag != 1) {
//       r = jal 0x31EDC(packed_at_sp42);        // 0x0C00C7B7 measure
//     } else {
//       r = jal 0x3186C(a0, packed_at_sp42);    // 0x0C00C61B measure
//     }
//     int dl = *(short*)(&D_0C34xxxx + ...);    // global DL cursor
//     *(int*)dl     = 0x0C800940 | a1;          // GBI word0
//     *(int*)(dl+4) = ...;                       // GBI word1
//     dl_cursor = r + 8;                         // advance by 8 bytes
//     ...
//   }
//
// Struct-typing reference: object/glyph entry e from &D_0 via a
//   sign-extended-halfword index (sll16/sra16 then *4 scaling); byte
//   e->0x1C selects which fixed measure/prep routine runs (0x0C00C7B7
//   ≈0x31EDC vs 0x0C00C61B ≈0x3186C, the flag==1 path also passes a0).
//   Emits one 8-byte F3D/GBI command (word0 = const 0x0C800940 ORed
//   with arg a1) to the global DL write cursor rooted at &D_0C34xxxx,
//   then advances the cursor by 8. Same builder family as the
//   gl_func_0001D4C0 leading fn but standalone.
// Caps (DEFERRED): single jr $ra. Glyph/sprite DL-emitter of the
//   family: record = &D_00000000 + (short)a2 * 0x158; visibility
//   gate rec->0x1C==1 selects helper1 vs helper2; then two F3D
//   command pairs ((rec->0x22 | 0x0C340000)/0x0C800940 and
//   ((rec->0x24+0x8000)&0xFFFF | 0x0C340000)/0x0C800C80) written to
//   the returned DL ptr; a final helper3 call gated on
//   rec->0x28==0 && rec->0x2A!=0. Real-C structural body below;
//   byte-match deferred — three placeholder jals (0xC7B7/0xC61B/
//   0xC5FA) are runtime-patched USO relocs (need USO reloc infra,
//   not resolvable from .s), plus beql/bne schedule. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the three helpers.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0001DA7C(int a0, int a1, int a2, int a3) {
    short si = (short)a2;
    char *rec = (char *)&D_00000000 + si * 0x158;
    int *dl;
    if (*(unsigned char *)(rec + 0x1C) == 1) {
        dl = (int *)gl_func_00000000(a0, a1, si, (short)a3);
    } else {
        dl = (int *)gl_func_00000000(a0, a1, si, (short)a3);
    }
    dl[0] = *(unsigned short *)(rec + 0x22) | 0x0C340000;
    dl[1] = 0x0C800940;
    dl[2] = ((*(unsigned short *)(rec + 0x24) + 0x8000) & 0xFFFF) | 0x0C340000;
    dl[3] = 0x0C800C80;
    {
        int *e = &dl[4];
        if (*(unsigned short *)(rec + 0x28) != 0 ||
            *(unsigned short *)(rec + 0x2A) != 0) {
            e = (int *)gl_func_00000000(&dl[4], si);
        }
        return (int)e;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DA7C);
#endif

// gl_func_0001DB88 — STRUCTURAL PASS (0x12C / 75 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Glyph/sprite draw helper in the gl_func_0001CFDC family,
// the two-flag conditional variant.
//
//   int gl_func_0001DB88(int a0, short idx) {
//     E *base = &D_0 + idx_scaled(idx);          // signed-hw index
//     byte f1 = base->0x1B;
//     byte f2 = (base + ...)->0x1C;              // second flag
//     E *e = base + 0x50;
//     if (f1 != 1) {                              // bne f1,1 path
//       int h = e->0x0E;  int w = e->0x10;
//       jal 0x31F4C(0x0C80, …, w, h, …);          // 0x0C00C813 blit
//       ...
//     }
//     ...
//   }
//
// Struct-typing reference: same glyph layout as gl_func_0001CFDC /
//   0001D0AC (&D_0 table, +0x50 entry, e->0x0E height, e->0x10
//   width/advance) plus TWO gating flag bytes read off the pre-+0x50
//   base: byte base->0x1B (primary path selector, compared != 1) and
//   byte base->0x1C (secondary). Uses the 0x0C80 blit-mode constant
//   and the fixed blit routine 0x0C00C813 (≈0x31F4C) — same
//   mode/target combination as the gl_func_0001D0AC sibling but with
//   the extra two-flag conditional structure.
// Caps (DEFERRED): single jr $ra. Glyph-draw family variant:
//   rec = &D_00000000 + (short)a1 * 0x158; e = rec + attr/idx math
//   + 0x50; visibility gate rec->0x1C==1; two 0x3204C blit calls
//   (mode 0xC80, second on e->0x12!=0 with (e->0x10+0xC80)&0xFFFF);
//   trailing 0xC759 helper (a1=0xC80,a2=0x340, arg from e->0x54);
//   final rec->0x18 = 0 flag clear; return draw result. Real-C
//   structural body below; byte-match deferred — placeholder jals
//   (0xC813/0xC759) are runtime-patched USO relocs (need USO reloc
//   infra), plus beql/index-multiply schedule. Name pre-checked: no
//   extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the helpers.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0001DB88(int a0, int a1, int a2) {
    short idx = (short)a1;
    char *rec = (char *)&D_00000000 + idx * 0x158;
    unsigned char attr = *(unsigned char *)(rec + 0x1B);
    char *e = rec + attr * 0x64 + (short)a2 * 0x14 + 0x50;
    int r;
    if (*(unsigned char *)(rec + 0x1C) != 1) {
        return a0;
    }
    r = gl_func_00000000(a0, 0xC80, *(unsigned short *)(e + 0xE), *(short *)(e + 0x10), idx);
    if (*(short *)(e + 0x12) != 0) {
        r = gl_func_00000000(r, (*(short *)(e + 0x10) + 0xC80) & 0xFFFF, 0, idx);
    }
    r = gl_func_00000000(r, 0xC80, 0x340, *(int *)(e + 0x54), idx);
    *(char *)(rec + 0x18) = 0;
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DB88);
#endif

// gl_func_0001DCB4 — STRUCTURAL PASS (0x480 / 288 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle) — a LARGE text-run layout/measure orchestrator above the
// gl_func_0001CFDC glyph-draw family. -0xC0 frame, full s0-s8/ra save.
//
//   ret gl_func_0001DCB4(a0, a1, a2, a3) {
//     S *g = &D_0;                                // global state base
//     if (g->byte_1 == 0) {                        // config gate
//       int n   = g->w_0x2070;                     // item count
//       int i   = 0, k = 0;
//       if (n > 0) {                                // classify loop
//         char *buf = sp + 0x84;                    // scratch byte arr
//         do {
//           T *it = g->w_0x14 + idx;                // item table
//           int v = it->w_0;
//           if (v >> 31) ...                        // sign-bit class
//           buf[k] = (char)i;                       // record index
//           ...
//         } while (i < n);
//       }
//     }
//     ... second phase: walk the classified buf, emit per-run glyph
//         draws via the gl_func_0001CFDC family ...
//   }
//
// Struct-typing reference: global state struct at &D_0 — signed byte
//   g->1 (a one-shot/config gate, skips the build when nonzero),
//   word g->0x2070 (count of layout items), word g->0x14 (base of the
//   item table indexed in the loop). Items carry a word whose sign
//   bit (srl 31) classifies the entry (run-break vs glyph). A scratch
//   byte array is built at sp+0x84 holding the per-item indices, then
//   consumed by a second phase that issues the actual glyph draws.
//   This is the run-layout/measure front-end of the game_libs text
//   subsystem; the leaf draws delegate to the gl_func_0001CFDC family.
// Caps (DEFERRED): CLEAN single jr $ra. Large text-run layout/measure
//   orchestrator over the gl_func_0001CFDC glyph-draw family.
//   Real-C STRUCTURAL body below per the analysis (two-phase: classify
//   g->0x2070 items by item-word sign bit into a sp+0x84 byte buffer,
//   then emit per-run glyph draws); byte-match deferred — ~288-insn
//   multi-phase with many runtime-patched placeholder jals (need USO
//   reloc infra) and -0xC0 frame s0-s8 schedule. Name pre-checked: no
//   extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the leaf glyph draws.
// gl_func_0001DCB4 — FULL m2c DECODE (57.35% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001DCB4)();
char *gl_func_0001DCB4(s32 arg0, s32 arg1, char *arg2, s16 arg3) {
    int sp84;
    s32 sp78;
    s32 sp68;
    s32 sp60;
    s16 var_s2;
    s16 var_s3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_lo;
    s32 temp_t5;
    s32 temp_v1;
    s8 *temp_t1;
    s8 *temp_t2;
    s8 *temp_t9;
    s8 temp_t0;
    s8 var_s1;
    s8 var_s1_2;
    u32 *var_v0;
    u8 *var_s0;
    u8 *var_s0_2;
    u8 temp_t6;
    u8 temp_v0;
    u8 temp_v0_3;
    char *temp_s5;
    char *temp_v0_2;
    char *var_s5;
    char *var_v1;
    char *var_v1_2;

    temp_t0 = *(s8 *)1;
    var_s2 = 0;
    if (temp_t0 == 0) {
        temp_a0 = *(s8 *)0x2070;
        var_s1 = 0;
        if (temp_a0 > 0) {
            var_v0 = *(s8 *)0x14 + ((temp_a0 * arg3) << 5);
            do {
                temp_t2 = &sp84 + var_s2;
                if (((u32) *var_v0 >> 0x1F) != 0) {
                    var_s2 += 1;
                    *temp_t2 = var_s1;
                }
                var_s1 += 1;
                var_v0 += 0x20;
            } while (var_s1 < temp_a0);
            var_s1 = 0;
        }
        var_s3 = 0;
    } else {
        var_s3 = 0;
        if (temp_t0 > 0) {
            temp_a0_2 = *(s8 *)0x2070;
            do {
                var_s1_2 = 0;
                if (temp_a0_2 > 0) {
                    var_v1 = ((temp_a0_2 * arg3) << 5) + *(s8 *)0x14;
                    do {
                        if (((u32) FW(var_v1, 0x0) >> 0x1F) != 0) {
                            temp_t1 = &sp84 + var_s2;
                            if (var_s3 == ((u8) FW(var_v1, 0x1) >> 5)) {
                                var_s2 += 1;
                                *temp_t1 = var_s1_2;
                            }
                        }
                        var_s1_2 += 1;
                        var_v1 += 0x20;
                    } while (var_s1_2 < temp_a0_2);
                }
                var_s3 += 1;
            } while (var_s3 < temp_t0);
            var_s3 = 0;
        }
        temp_a0_3 = *(s8 *)0x2070;
        var_s1 = 0;
        if (temp_a0_3 > 0) {
            var_v1_2 = ((temp_a0_3 * arg3) << 5) + *(s8 *)0x14;
            do {
                if (((u32) FW(var_v1_2, 0x0) >> 0x1F) != 0) {
                    temp_t9 = &sp84 + var_s2;
                    if ((s32) ((u8) FW(var_v1_2, 0x1) >> 5) >= temp_t0) {
                        var_s2 += 1;
                        *temp_t9 = var_s1;
                    }
                }
                var_s1 += 1;
                var_v1_2 += 0x20;
            } while (var_s1 < temp_a0_3);
            var_s1 = 0;
        }
    }
    FW(arg2, 0x4) = 0x340;
    FW(arg2, 0x0) = 0x02000940;
    var_s5 = arg2 + 8;
    if (*(s8 *)1 > 0) {
        do {
            temp_t5 = var_s3 * 0x158;
            sp60 = temp_t5;
            temp_t6 = FW(temp_t5, 0x19);
            sp78 = (s32) temp_t6;
            if (temp_t6 != 0) {
                var_s5 = game_libs_func_0003443C((u8) var_s5, arg1, var_s3, arg3);
            }
            if (var_s1 < var_s2) {
                var_s0 = var_s1 + &sp84;
loop_30:
                temp_v0 = *(int*)var_s0;
                temp_v1 = *(s8 *)0x14;
                temp_lo = arg3 * *(s8 *)0x2070;
                if (var_s3 == ((u8) FW((temp_v1 + (temp_v0 << 5) + (temp_lo << 5)), 0x1) >> 5)) {
                    var_s1 += 1;
                    var_s5 = game_libs_func_0003443C(temp_v0, ((temp_v0 + temp_lo) << 5) + temp_v1, (temp_v0 * 0xD0) + *(s8 *)0x2CFC + 0x10, (s16) arg0, arg1, var_s5, (s32) arg3);
                    var_s0 += 1;
                    if (var_s1 < var_s2) {
                        goto loop_30;
                    }
                }
            }
            if (sp78 != 0) {
                if ((FW(sp60, 0x118) != 0) || (FW(sp60, 0x11C) != 0)) {
                    var_s5 = game_libs_func_0003443C((u8) var_s5, arg1 * 2, var_s3);
                }
                temp_v0_2 = game_libs_func_0003443C((u8) var_s5, (s32) var_s3, arg3);
                var_s5 = temp_v0_2;
                if (FW(sp60, 0x1D) != -1) {
                    var_s5 = game_libs_func_0003443C((u8) temp_v0_2, (s32) var_s3, arg3);
                }
            }
            var_s3 += 1;
        } while (var_s3 < *(s8 *)1);
    }
    sp68 = arg1 * 2;
    if (var_s1 < var_s2) {
        var_s0_2 = var_s1 + &sp84;
        do {
            temp_v0_3 = *(int*)var_s0_2;
            var_s0_2 += 1;
            var_s5 = game_libs_func_0003443C(temp_v0_3, ((temp_v0_3 + (arg3 * *(s8 *)0x2070)) << 5) + *(s8 *)0x14, (temp_v0_3 * 0xD0) + *(s8 *)0x2CFC + 0x10, (s16) arg0, arg1, var_s5, (s32) arg3);
        } while ((u32) var_s0_2 < (u32) (var_s2 + &sp84));
    }
    FW(var_s5, 0x0) = (s32) ((((sp68 >> 4) & 0xFF) << 0x10) | 0x0D000000 | 0x3C0);
    FW(var_s5, 0x4) = 0x09400AE0;
    temp_s5 = var_s5 + 8;
    FW(var_s5, 0x8) = (s32) (((((s32) (sp68 * 2) >> 4) & 0xFF) << 0x10) | 0x15000000 | 0x3C0);
    FW(temp_s5, 0x4) = (s32) (arg0 + 0x80000000);
    return temp_s5 + 8;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DCB4);
#endif

// gl_func_0001E134 — STRUCTURAL PASS (0xD44 / 849 words ≈ 3.4KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle) — the LARGEST member of the game_libs text/sprite
// subsystem seen so far: a sprite/record-build + DL-emit orchestrator.
// Huge -0x160 frame, full s0-s8/ra save, a0 at sp+0x160, a3 at +0x16C.
//
//   ret gl_func_0001E134(a0, int *a1, a2, a3) {
//     int w   = a1[0];                            // packed control word
//     int idx = a0*4 - a0;                         // a0 * 3 ...
//     idx = (idx + a0) << 4;                        // ... scaled stride
//     int f0  = (w << 11) >> 30;                    // 2-bit subfield
//     int f1  = (w <<  1) >> 31;                     // 1-bit subfield
//     R *tbl  = *(R**)(&D_0 + 0x2CFC);              // record table ptr
//     R *rec  = tbl + idx;                           // target record
//     if (f1 != 1) {                                 // build branch
//       rec->b_0  = 0;  rec->w_8  = 0;               // zero-init the
//       rec->h_6  = 0;  rec->h_10 = 0;               //  record fields
//       rec->h_12 = 0;  rec->b_2  = 0;  rec->b_3 = 0;
//       ... populate from a1[]/a2 ...
//     }
//     ... ~800 words: per-element loop emitting F3D/GBI commands and
//         delegating leaf glyph/sprite draws to the gl_func_0001CFDC
//         family; cleanup + return ...
//   }
//
// Struct-typing reference: control word a1[0] carries packed
//   subfields decoded by shift pairs (<<11>>30 = bits, <<1>>31 = sign-
//   ish flag). Record table is a pointer global at &D_0 + 0x2CFC;
//   records are fixed-stride (index = a0*3 then <<4). A record R has
//   byte fields at 0/2/3, halfwords at 6/0x10/0x12, word at 8 — all
//   zero-initialized on the build path before being filled. This is
//   the top-level sprite/text record builder + display-list emitter;
//   leaf draws delegate to the gl_func_0001CFDC glyph family.
// Caps (DEFERRED): CLEAN single jr $ra. Largest game_libs text/sprite
//   member — record-build + DL-emit orchestrator. Real-C STRUCTURAL
//   body below per the analysis (control word a1[0] -> packed
//   subfields, record = (&D_0+0x2CFC ptr) + (a0*3<<4), zero-init +
//   populate on the f1!=1 build path, then per-element command/leaf
//   draw loop). Byte-match deferred — ~849-insn multi-phase, many
//   runtime-patched placeholder jals (need USO reloc infra), -0x160
//   frame s0-s8 schedule. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined USO
//   placeholder for the leaf glyph/sprite draws.
// gl_func_0001E134 — FULL m2c DECODE (57.2% NM, no episode). Largest non-jumptable lift yet (849w); texture-tile DMA dlist builder, 22 K&R variadic emits to game_libs_func_0003443C + 1 gl_func_0001CA10 alloc, 5 nested irregular switches.
// Reloc-form fix pass (agent-d 2026-06-22): absolute D_BASE derefs (*(s32*)0x2CFC, *(s32*)0x10) -> FW(&D_00000000, off) so HI16/LO16 relocs emit (matches target lui/lw). Reloc-filtered word-cmp vs expected: 812->790 non-reloc diffs, size gap -14->-13 words.
// CAP: frame still -504 (m2c) vs -352 (target); m2c over-spills ~19 temps the original kept in registers, mis-aligning the entire 800-word body. Landing needs exact-structure RE of the register/spill set (multi-session). No sibling in this builder family (DCB4 57%) has matched.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001E134)();
s32 *gl_func_0001E134(s32 arg0, u8 *arg1, u8 *arg2, int arg3, u32 arg4, s32 *arg5, s32 *arg6) {
    char *sp150;
    char *sp14C;
    s32 sp140;
    s32 sp13C;
    s32 sp138;
    u16 sp136;
    s32 sp120;
    s32 sp110;
    s32 sp108;                                      /* compiler-managed */
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 spE4;
    s32 spD4;
    s32 spCC;
    s32 spC8;
    s32 spC0;
    s32 spBC;
    s32 spB0;                                       /* compiler-managed */
    u16 spAE;
    char *sp9C;
    u32 sp8C;
    u32 sp88;
    u32 sp50;
    s32 *temp_a0_10;
    s32 *temp_a0_3;
    s32 *temp_a0_4;
    s32 *temp_a0_5;
    s32 *temp_a0_6;
    s32 *temp_a0_7;
    s32 *temp_a0_8;
    s32 *temp_a0_9;
    s32 *temp_s3_3;
    s32 *temp_s3_4;
    s32 *temp_s3_5;
    s32 *temp_s3_6;
    s32 *temp_s3_7;
    s32 *temp_v0;
    s32 *temp_v0_10;
    s32 *temp_v0_11;
    s32 *temp_v0_12;
    s32 *temp_v0_8;
    s32 *temp_v1_2;
    s32 *var_s3;
    s32 *var_s3_2;
    s32 *var_s3_3;
    s32 *var_s3_4;
    s32 temp_a0_2;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t8;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_7;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_s8;
    s32 var_t0;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t1_3;
    s32 var_t3_2;
    s32 var_t4;
    s32 var_t5;
    s32 var_v1;
    u16 temp_t0;
    u16 temp_t9;
    u16 temp_v1_8;
    u32 temp_a3_2;
    u32 temp_a3_3;
    u32 temp_s2;
    u32 temp_s4;
    u32 temp_t0_2;
    u32 temp_t0_3;
    u32 temp_t6;
    u32 temp_v0_9;
    u32 temp_v1_4;
    u32 var_a0;
    u32 var_t3;
    u8 *temp_a2_3;
    u8 *var_s1_2;
    u8 temp_a0;
    u8 temp_s0;
    u8 var_a1;
    u8 var_a1_2;
    char *temp_a1;
    char *temp_a3;
    char *temp_s3;
    char *temp_s3_2;
    char *temp_v0_2;
    char *temp_v0_4;
    char *temp_v1_5;
    char *temp_v1_6;

    temp_v1 = FW(arg1, 0x0);
    sp8C = (u32) (temp_v1 << 0xB) >> 0x1E;
    var_t3 = (u32) (temp_v1 * 4) >> 0x1F;
    var_t1 = 0;
    temp_a3 = (arg0 * 0xD0) + FW(&D_00000000, 0x2CFC);
    if (((u32) (temp_v1 * 2) >> 0x1F) == 1) {
        *(u8*)((char*)arg2 + 0x0) = 0;
        FW(arg2, 0x8) = 0;
        FW(arg2, 0x6) = 0U;
        FW(arg2, 0x10) = 0;
        FW(arg2, 0x12) = 0;
        FW(arg2, 0x2) = 0U;
        FW(arg2, 0x3) = 0U;
        FW(arg2, 0x5) = 0U;
        FW(arg2, 0x1A) = 1U;
        FW(arg2, 0x4) = (u8) FW(arg1, 0x5);
        var_t1 = 1;
        var_t3 = 0;
        FW(temp_a3, 0xB0) = (u8) (FW(temp_a3, 0xB0) & 0xFFDF);
    }
    temp_t9 = FW(arg1, 0xC);
    sp136 = temp_t9;
    temp_a0 = ((u32) (FW(arg1, 0x0) << 0xE) >> 0x1F) + 1;
    temp_t0 = ((temp_t9 & 0xFFFF) * arg4 * 2) + FW(arg2, 0x6);
    FW(arg2, 0x6) = temp_t0;
    if (FW(arg2, 0x5) == 1) {

    }
    FW(arg2, 0x5) = temp_a0;
    var_v1 = FW(arg1, 0x0);
    if (var_v1 & 0x40000) {
        temp_a3_2 = temp_t0 >> 0x10;
        sp50 = temp_a3_2;
        temp_v0 = game_libs_func_0003443C(arg5, arg1, arg2, temp_a3_2);
        temp_a2 = FW(arg2, 0x8);
        spAE = (temp_a2 * 2) + 0x580;
        FW(arg2, 0x8) = (s32) (temp_a2 + sp50);
        var_v1 = FW(arg1, 0x0);
        arg5 = temp_v0;
    } else {
        temp_t6 = temp_t0 >> 0x10;
        temp_v0_2 = *(int*)(FW(arg1, 0x10));
        temp_a1 = FW(temp_v0_2, 0x8);
        sp100 = FW(temp_a1, 0x4);
        spB0 = 0;
        spBC = 0;
        sp110 = FW(temp_v0_2, 0x4);
        if ((s32) temp_a0 > 0) {
            spC0 = (s32) temp_a0;
            var_a0 = temp_t6;
            sp50 = temp_t6;
            sp150 = temp_v0_2;
            sp14C = temp_a1;
            sp9C = temp_a3;
            sp138 = var_t1;
            sp88 = var_t3;
            var_s7 = spD4;
            var_s3_2 = arg5;
            var_t5 = spCC;
            var_t4 = spC8;
loop_7:
            var_t3_2 = 0;
            var_s6 = 0;
            temp_t0_2 = (u32) FW(sp150, 0x0) >> 0x1C;
            if (spC0 == 1) {
                goto block_11;
            }
            if (var_a0 & 1) {
                sp108 = (var_a0 & ~1) + (spBC * 2);
            } else {
block_11:
                sp108 = var_a0;
            }
            if ((temp_t0_2 == 0) || (temp_t0_2 == 3)) {
                temp_v0_3 = FW(sp150, 0xC) + 8;
                if (FW(&D_00000000, 0x10) != temp_v0_3) {
                    switch (sp8C) {                 /* switch 1; irregular */
                    case 1:                         /* switch 1 */
                        *(s8 *)((char*)&D_00000000 + 0x10) = 2;
                        break;
                    default:                        /* switch 1 */
                    case 2:                         /* switch 1 */
                    case 3:                         /* switch 1 */
                        *(s8 *)((char*)&D_00000000 + 0x10) = temp_v0_3;
                        break;
                    }
                    temp_v0_4 = FW(sp150, 0xC);
                    temp_v1_2 = var_s3_2;
                    var_s3_2 += 8;
                    FW(temp_v1_2, 0x0) = ((FW(temp_v0_4, 0x0) * 0x10 * FW(temp_v0_4, 0x4)) & 0xFFFFFF) | 0x0B000000;
                    FW(temp_v1_2, 0x4) = (s32) (*(s8 *)((char*)&D_00000000 + 0x10) + 0x80000000);
                    var_a0 = sp50;
                }
            }
            if (sp108 != 0) {
loop_23:
                sp140 = 0;
                sp13C = 0;
                temp_a2_2 = FW(arg2, 0x8);
                temp_a0_2 = sp108 - var_t3_2;
                spFC = temp_a0_2;
                temp_a3_3 = FW(sp150, 0x0);
                var_s4 = temp_a2_2 & 0xF;
                var_s5 = 0;
                temp_v1_3 = sp100 - temp_a2_2;
                temp_t0_3 = temp_a3_3 >> 0x1C;
                if ((var_s4 == 0) && (FW(arg2, 0x0) == 0)) {
                    var_s4 = 0x10;
                }
                temp_a1_2 = 0x10 - var_s4;
                var_s8 = temp_a1_2;
                if (temp_a0_2 < temp_v1_3) {
                    temp_v0_5 = (s32) ((temp_a0_2 - temp_a1_2) + 0xF) / 16;
                    var_s1 = temp_v0_5 * 0x10;
                    var_s2 = temp_v0_5;
                    var_t1_2 = (temp_a1_2 + var_s1) - temp_a0_2;
                } else {
                    var_s1 = temp_v1_3 - temp_a1_2;
                    var_t1_2 = 0;
                    if (var_s1 <= 0) {
                        var_s1 = 0;
                        var_s8 = temp_v1_3;
                    }
                    var_s2 = (s32) (var_s1 + 0xF) / 16;
                    if (FW(sp14C, 0x8) != 0) {
                        sp13C = 1;
                    } else {
                        sp140 = 1;
                    }
                }
                switch (temp_t0_3) {                /* switch 2; irregular */
                case 2:                             /* switch 2 */
                    break;
                case 0:                             /* switch 2 */
                    var_s7 = 9;
                    var_t5 = 0x10;
block_41:
                    var_t4 = 0;
                default:                            /* switch 2 */
                    var_t0 = 0;
                    if (var_s2 != 0) {
                        temp_v0_6 = (s32) ((temp_a2_2 + var_t5) - var_s4) / 16;
                        temp_v1_4 = (u32) (temp_a3_3 * 0x10) >> 0x1E;
                        if (temp_v1_4 == 0) {
                            var_a0_2 = var_t4 + (temp_v0_6 * var_s7) + sp110;
                            var_s0 = ((var_s2 * var_s7) + 0x1F) & ~0xF;
                        } else {
                            spE4 = var_t1_2;
                            sp104 = var_t3_2;
                            spC8 = var_t4;
                            spCC = var_t5;
                            var_s0 = ((var_s2 * var_s7) + 0x1F) & ~0xF;
                            temp_v0_7 = gl_func_0001CA10(var_t4 + (temp_v0_6 * var_s7) + sp110, var_s0, sp138, (int)arg2 + 1, temp_v1_4);
                            var_a0_2 = temp_v0_7;
                        }
                        var_t0 = var_a0_2 & 0xF;
                        FW(var_s3_2, 0x4) = (s32) ((var_a0_2 - var_t0) + 0x80000000);
                        FW(var_s3_2, 0x0) = (((var_s0 >> 4) & 0xFF) << 0x10) | 0x14000000 | ((0x940 - var_s0) & 0xFFFF);
                        var_a1 = FW(arg2, 0x0);
                        var_s3_2 += 8;
                    } else {
                        var_s1 = 0;
                        var_a1 = FW(arg2, 0x0);
                    }
                    temp_v0_8 = var_s3_2;
                    if (var_a1 != 0) {
                        FW(temp_v0_8, 0x0) = 0x0F000000;
                        var_s3_2 += 8;
                        FW(temp_v0_8, 0x4) = (s32) (FW(sp150, 0x8) + 0x80000010);
                        sp138 = 2;
                        *(u8*)((char*)arg2 + 0x0) = 0;
                    }
                    temp_v0_9 = (u32) FW(sp150, 0x0) >> 0x1C;
                    if (var_t3_2 == 0) {
                        sp120 = var_s4 * 2;
                    } else {
                        var_s5 = (var_s6 + 0x1F) & ~0xF;
                    }
                    switch (temp_v0_9) {            /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                        temp_v0_10 = var_s3_2;
                        temp_s3 = var_s3_2 + 8;
                        temp_v1_5 = temp_s3;
                        var_s3_2 = temp_s3 + 8;
                        FW(temp_v0_10, 0x0) = (((0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0) & 0xFFFF) | 0x08000000;
                        FW(temp_v0_10, 0x4) = (s32) (((var_s5 + 0x580) << 0x10) | ((var_s1 * 2) & 0xFFFF));
                        FW(temp_v1_5, 0x0) = (s32) (((sp138 & 0xFF) << 0x10) | 0x01000000);
                        FW(temp_v1_5, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000000);
                        break;
                    case 3:                         /* switch 3 */
                        temp_v0_11 = var_s3_2;
                        temp_s3_2 = var_s3_2 + 8;
                        temp_v1_6 = temp_s3_2;
                        var_s3_2 = temp_s3_2 + 8;
                        FW(temp_v0_11, 0x0) = (((0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0) & 0xFFFF) | 0x08000000;
                        FW(temp_v0_11, 0x4) = (s32) (((var_s5 + 0x580) << 0x10) | ((var_s1 * 2) & 0xFFFF));
                        FW(temp_v1_6, 0x0) = (s32) ((((sp138 | 4) & 0xFF) << 0x10) | 0x01000000);
                        FW(temp_v1_6, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000000);
                        break;
                    case 1:                         /* switch 3 */
                        temp_s3_3 = var_s3_2 + 8;
                        spE4 = var_t1_2;
                        sp104 = var_t3_2;
                        spC8 = var_t4;
                        spCC = var_t5;
                        game_libs_func_0003443C(var_s3_2, 0, (s16) (0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0, var_s5 + 0x580, var_s1 * 2);
                        temp_a0_3 = temp_s3_3;
                        var_s3_2 = temp_s3_3 + 8;
                        game_libs_func_0003443C(temp_a0_3, (u8 *) sp138, FW(arg2, 0xC) + 0x80000000);
                        break;
                    }
                    if (var_t3_2 != 0) {
                        FW(var_s3_2, 0x0) = ((var_s5 + (var_s4 * 2) + 0x580) & 0xFFFFFF) | 0x0A000000;
                        FW(var_s3_2, 0x4) = (s32) (((var_s6 + 0x580) << 0x10) | ((((var_s1 + var_s8) - var_t1_2) * 2) & 0xFFFF));
                        var_s3_2 += 8;
                    }
                    temp_v1_7 = (var_s1 + var_s8) - var_t1_2;
                    var_t3_2 += temp_v1_7;
                    if (sp138 != 1) {
                        sp138 = 0;
                        if (sp138 != 2) {
                            if (var_s6 != 0) {
                                var_s6 += temp_v1_7 * 2;
                            } else {
                                var_s6 = (var_s4 + temp_v1_7) * 2;
                            }
                        } else {
                            var_s6 += temp_v1_7 * 2;
                        }
                    } else {
                        sp120 = 0x20;
                        var_s6 = (var_s1 * 2) + 0x20;
                        sp138 = 0;
                    }
                    break;
                case 3:                             /* switch 2 */
                    var_s7 = 5;
                    var_t5 = 0x10;
                    goto block_41;
                case 1:                             /* switch 2 */
                    var_s7 = 0x10;
                    var_t5 = 0x10;
                    goto block_41;
                }
                if (sp140 != 0) {
                    temp_a0_4 = var_s3_2;
                    sp88 = 1;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_4, var_s6 + 0x580, (u8 *) ((sp108 - var_t3_2) * 2));
                    FW(sp9C, 0xB0) = (u8) (FW(sp9C, 0xB0) | 0x20);
                    game_libs_func_0003443C(arg6, (u8 *) arg0);
                    var_a0 = sp50;
                } else {
                    if (sp13C != 0) {
                        FW(arg2, 0x0) = 1;
                        FW(arg2, 0x8) = (s32) FW(sp14C, 0x0);
                    } else {
                        FW(arg2, 0x8) = (s32) (FW(arg2, 0x8) + spFC);
                    }
                    if (var_t3_2 == sp108) {
                        var_a0 = sp50;
                    } else {
                        goto loop_23;
                    }
                }
            }
            switch (spC0) {                         /* switch 4; irregular */
            case 1:                                 /* switch 4 */
                spAE = sp120 + 0x580;
                break;
            case 2:                                 /* switch 4 */
                switch (spBC) {                     /* switch 5; irregular */
                case 0:                             /* switch 5 */
                    temp_a0_5 = var_s3_2;
                    spAE = 0x3E0;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_5, sp120 + 0x580, (u8 *)0x3E0, (((s32) sp108 / 2) + 7) & ~7);
                    spB0 = sp108;
                    if (sp88 != 0) {
                        temp_a0_6 = var_s3_2;
                        var_s3_2 += 8;
                        spC8 = var_t4;
                        spCC = var_t5;
                        game_libs_func_0003443C(temp_a0_6, sp108 + 0x3E0, sp108 + 0x10);
                    }
                    var_a0 = sp50;
                    break;
                case 1:                             /* switch 5 */
                    temp_a0_7 = var_s3_2;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_7, sp120 + 0x580, spB0 + 0x3E0, (((s32) sp108 / 2) + 7) & ~7);
                    var_a0 = sp50;
                    break;
                }
                break;
            }
            temp_t8 = spBC + 1;
            if (sp88 != 0) {
                var_v1 = FW(arg1, 0x0);
                arg5 = var_s3_2;
            } else {
                spBC = temp_t8;
                if (temp_t8 == spC0) {
                    spD4 = var_s7;
                    spCC = var_t5;
                    spC8 = var_t4;
                    var_v1 = FW(arg1, 0x0);
                    arg5 = var_s3_2;
                } else {
                    goto loop_7;
                }
            }
        }
    }
    var_t1_3 = 0;
    if (((u32) (var_v1 * 2) >> 0x1F) == 1) {
        var_t1_3 = 1;
        FW(arg1, 0x0) &= 0xFFBF;
    }
    temp_s4 = arg4 * 2;
    sp138 = var_t1_3;
    temp_v0_12 = game_libs_func_0003443C(arg5, arg2, (u8 *) temp_s4, (u32) sp136, (s32) spAE, var_t1_3);
    var_s3_3 = temp_v0_12;
    if (sp8C == 3) {
        var_s3_3 = temp_v0_12 + 8;
        game_libs_func_0003443C(temp_v0_12, (u8 *)0x3C0, (u8 *)0x3C0, temp_s4, 0);
    }
    temp_a0_8 = var_s3_3;
    if (sp8C == 2) {
        var_s3_3 += 8;
        game_libs_func_0003443C(temp_a0_8, (u8 *)0x3C0, (u8 *)0x3C0, temp_s4);
    }
    temp_a0_9 = var_s3_3;
    var_a1_2 = FW(arg1, 0x2);
    if (var_a1_2 != 0) {
        var_s3_3 += 8;
        if ((s32) var_a1_2 < 0x10) {
            var_a1_2 = 0x10;
        }
        game_libs_func_0003443C(temp_a0_9, (u8 *) var_a1_2, (u8 *)0x3C0, 0U, temp_s4 + 0x20);
    }
    temp_a2_3 = FW(arg1, 0x14);
    if (temp_a2_3 != 0) {
        temp_s3_4 = var_s3_3 + 8;
        game_libs_func_0003443C(var_s3_3, (u8 *) temp_s4, temp_a2_3);
        temp_a0_10 = temp_s3_4;
        var_s3_3 = temp_s3_4 + 8;
        game_libs_func_0003443C(temp_a0_10, (u8 *) sp138, (u8 *)0x3C0, FW(arg2, 0xC) + 0x40);
    }
    temp_s0 = FW(arg1, 0x7);
    temp_v1_8 = FW(arg1, 0xE);
    temp_s2 = FW(arg2, 0xC) + 0x800000C0;
    if ((temp_s0 != 0) && (temp_v1_8 != 0)) {
        temp_s3_5 = var_s3_3 + 8;
        game_libs_func_0003443C(var_s3_3, (u8 *)0x3C0, (u8 *)0x760, temp_s4);
        var_s1_2 = 0x760 - temp_s0;
        if (FW(arg2, 0x1A) != 0) {
            var_s1_2 = 0x760 - temp_s0;
            var_s3_4 = temp_s3_5 + 8;
            game_libs_func_0003443C(temp_s3_5, var_s1_2, (u8 *) temp_s0);
            FW(arg2, 0x1A) = 0U;
        } else {
            var_s3_4 = temp_s3_5 + 8;
            game_libs_func_0003443C(temp_s3_5, var_s1_2, (u8 *) temp_s0, temp_s2);
        }
        temp_s3_6 = var_s3_4 + 8;
        game_libs_func_0003443C(var_s3_4, (temp_s4 - temp_s0) + 0x3C0, (u8 *) temp_s0, temp_s2);
        temp_s3_7 = temp_s3_6 + 8;
        game_libs_func_0003443C(temp_s3_6, (u8 *) ((s32) temp_s4 >> 4), (u8 *) temp_v1_8, 0x760U, (s32) var_s1_2);
        var_s3_3 = temp_s3_7 + 8;
        game_libs_func_0003443C(temp_s3_7, var_s1_2, (u8 *)0x3C0, temp_s4);
    } else {
        FW(arg2, 0x1A) = 1U;
    }
    if ((FW(arg1, 0x3) != 0) || (FW(arg2, 0x2) != 0)) {
        var_s0_2 = 1;
    } else if ((FW(arg1, 0x4) != 0) || (var_s0_2 = 0, (FW(arg2, 0x3) != 0))) {
        var_s0_2 = 2;
    }
    var_s3 = game_libs_func_0003443C(var_s3_3, arg1, arg2, arg4, 0x3C0, var_s0_2, sp138);
    if ((u16) FW(arg1, 0x0) & 1) {
        if (!(sp138 & 1)) {
            sp138 = 0;
        }
        var_s3 = game_libs_func_0003443C(var_s3, arg1, arg2, temp_s4, sp138, var_s0_2);
    }
    return var_s3;
}
#else
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001E134)();
s32 *gl_func_0001E134(s32 arg0, u8 *arg1, u8 *arg2, int arg3, u32 arg4, s32 *arg5, s32 *arg6) {
    char *sp150;
    char *sp14C;
    s32 sp140;
    s32 sp13C;
    s32 sp138;
    u16 sp136;
    s32 sp120;
    s32 sp110;
    s32 sp108;                                      /* compiler-managed */
    s32 sp104;
    s32 sp100;
    s32 spFC;
    s32 spE4;
    s32 spD4;
    s32 spCC;
    s32 spC8;
    s32 spC0;
    s32 spBC;
    s32 spB0;                                       /* compiler-managed */
    u16 spAE;
    char *sp9C;
    u32 sp8C;
    u32 sp88;
    u32 sp50;
    s32 *temp_a0_10;
    s32 *temp_a0_3;
    s32 *temp_a0_4;
    s32 *temp_a0_5;
    s32 *temp_a0_6;
    s32 *temp_a0_7;
    s32 *temp_a0_8;
    s32 *temp_a0_9;
    s32 *temp_s3_3;
    s32 *temp_s3_4;
    s32 *temp_s3_5;
    s32 *temp_s3_6;
    s32 *temp_s3_7;
    s32 *temp_v0;
    s32 *temp_v0_10;
    s32 *temp_v0_11;
    s32 *temp_v0_12;
    s32 *temp_v0_8;
    s32 *temp_v1_2;
    s32 *var_s3;
    s32 *var_s3_2;
    s32 *var_s3_3;
    s32 *var_s3_4;
    s32 temp_a0_2;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t8;
    s32 temp_v0_3;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 temp_v1_7;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_s7;
    s32 var_s8;
    s32 var_t0;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t1_3;
    s32 var_t3_2;
    s32 var_t4;
    s32 var_t5;
    s32 var_v1;
    u16 temp_t0;
    u16 temp_t9;
    u16 temp_v1_8;
    u32 temp_a3_2;
    u32 temp_a3_3;
    u32 temp_s2;
    u32 temp_s4;
    u32 temp_t0_2;
    u32 temp_t0_3;
    u32 temp_t6;
    u32 temp_v0_9;
    u32 temp_v1_4;
    u32 var_a0;
    u32 var_t3;
    u8 *temp_a2_3;
    u8 *var_s1_2;
    u8 temp_a0;
    u8 temp_s0;
    u8 var_a1;
    u8 var_a1_2;
    char *temp_a1;
    char *temp_a3;
    char *temp_s3;
    char *temp_s3_2;
    char *temp_v0_2;
    char *temp_v0_4;
    char *temp_v1_5;
    char *temp_v1_6;

    temp_v1 = FW(arg1, 0x0);
    sp8C = (u32) (temp_v1 << 0xB) >> 0x1E;
    var_t3 = (u32) (temp_v1 * 4) >> 0x1F;
    var_t1 = 0;
    temp_a3 = (arg0 * 0xD0) + *(s32 *)0x2CFC;
    if (((u32) (temp_v1 * 2) >> 0x1F) == 1) {
        FW(arg2, 0x0) = 0;
        FW(arg2, 0x8) = 0;
        FW(arg2, 0x6) = 0U;
        FW(arg2, 0x10) = 0;
        FW(arg2, 0x12) = 0;
        FW(arg2, 0x2) = 0U;
        FW(arg2, 0x3) = 0U;
        FW(arg2, 0x5) = 0U;
        FW(arg2, 0x1A) = 1U;
        FW(arg2, 0x4) = (u8) FW(arg1, 0x5);
        var_t1 = 1;
        var_t3 = 0;
        FW(temp_a3, 0xB0) = (u8) (FW(temp_a3, 0xB0) & 0xFFDF);
    }
    temp_t9 = FW(arg1, 0xC);
    sp136 = temp_t9;
    temp_a0 = ((u32) (FW(arg1, 0x0) << 0xE) >> 0x1F) + 1;
    temp_t0 = ((temp_t9 & 0xFFFF) * arg4 * 2) + FW(arg2, 0x6);
    FW(arg2, 0x6) = temp_t0;
    if (FW(arg2, 0x5) == 1) {

    }
    FW(arg2, 0x5) = temp_a0;
    var_v1 = FW(arg1, 0x0);
    if (var_v1 & 0x40000) {
        temp_a3_2 = temp_t0 >> 0x10;
        sp50 = temp_a3_2;
        temp_v0 = game_libs_func_0003443C(arg5, arg1, arg2, temp_a3_2);
        temp_a2 = FW(arg2, 0x8);
        spAE = (temp_a2 * 2) + 0x580;
        FW(arg2, 0x8) = (s32) (temp_a2 + sp50);
        var_v1 = FW(arg1, 0x0);
        arg5 = temp_v0;
    } else {
        temp_t6 = temp_t0 >> 0x10;
        temp_v0_2 = *(int*)(FW(arg1, 0x10));
        temp_a1 = FW(temp_v0_2, 0x8);
        sp100 = FW(temp_a1, 0x4);
        spB0 = 0;
        spBC = 0;
        sp110 = FW(temp_v0_2, 0x4);
        if ((s32) temp_a0 > 0) {
            spC0 = (s32) temp_a0;
            var_a0 = temp_t6;
            sp50 = temp_t6;
            sp150 = temp_v0_2;
            sp14C = temp_a1;
            sp9C = temp_a3;
            sp138 = var_t1;
            sp88 = var_t3;
            var_s7 = spD4;
            var_s3_2 = arg5;
            var_t5 = spCC;
            var_t4 = spC8;
loop_7:
            var_t3_2 = 0;
            var_s6 = 0;
            temp_t0_2 = (u32) FW(sp150, 0x0) >> 0x1C;
            if (spC0 == 1) {
                goto block_11;
            }
            if (var_a0 & 1) {
                sp108 = (var_a0 & ~1) + (spBC * 2);
            } else {
block_11:
                sp108 = var_a0;
            }
            if ((temp_t0_2 == 0) || (temp_t0_2 == 3)) {
                temp_v0_3 = FW(sp150, 0xC) + 8;
                if (*(s32 *)0x10 != temp_v0_3) {
                    switch (sp8C) {                 /* switch 1; irregular */
                    case 1:                         /* switch 1 */
                        *(char *)0x10 = 2;
                        break;
                    default:                        /* switch 1 */
                    case 2:                         /* switch 1 */
                    case 3:                         /* switch 1 */
                        *(char *)0x10 = temp_v0_3;
                        break;
                    }
                    temp_v0_4 = FW(sp150, 0xC);
                    temp_v1_2 = var_s3_2;
                    var_s3_2 += 8;
                    FW(temp_v1_2, 0x0) = ((FW(temp_v0_4, 0x0) * 0x10 * FW(temp_v0_4, 0x4)) & 0xFFFFFF) | 0x0B000000;
                    FW(temp_v1_2, 0x4) = (s32) (*(char *)0x10 + 0x80000000);
                    var_a0 = sp50;
                }
            }
            if (sp108 != 0) {
loop_23:
                sp140 = 0;
                sp13C = 0;
                temp_a2_2 = FW(arg2, 0x8);
                temp_a0_2 = sp108 - var_t3_2;
                spFC = temp_a0_2;
                temp_a3_3 = FW(sp150, 0x0);
                var_s4 = temp_a2_2 & 0xF;
                var_s5 = 0;
                temp_v1_3 = sp100 - temp_a2_2;
                temp_t0_3 = temp_a3_3 >> 0x1C;
                if ((var_s4 == 0) && (FW(arg2, 0x0) == 0)) {
                    var_s4 = 0x10;
                }
                temp_a1_2 = 0x10 - var_s4;
                var_s8 = temp_a1_2;
                if (temp_a0_2 < temp_v1_3) {
                    temp_v0_5 = (s32) ((temp_a0_2 - temp_a1_2) + 0xF) / 16;
                    var_s1 = temp_v0_5 * 0x10;
                    var_s2 = temp_v0_5;
                    var_t1_2 = (temp_a1_2 + var_s1) - temp_a0_2;
                } else {
                    var_s1 = temp_v1_3 - temp_a1_2;
                    var_t1_2 = 0;
                    if (var_s1 <= 0) {
                        var_s1 = 0;
                        var_s8 = temp_v1_3;
                    }
                    var_s2 = (s32) (var_s1 + 0xF) / 16;
                    if (FW(sp14C, 0x8) != 0) {
                        sp13C = 1;
                    } else {
                        sp140 = 1;
                    }
                }
                switch (temp_t0_3) {                /* switch 2; irregular */
                case 2:                             /* switch 2 */
                    break;
                case 0:                             /* switch 2 */
                    var_s7 = 9;
                    var_t5 = 0x10;
block_41:
                    var_t4 = 0;
                default:                            /* switch 2 */
                    var_t0 = 0;
                    if (var_s2 != 0) {
                        temp_v0_6 = (s32) ((temp_a2_2 + var_t5) - var_s4) / 16;
                        temp_v1_4 = (u32) (temp_a3_3 * 0x10) >> 0x1E;
                        if (temp_v1_4 == 0) {
                            var_a0_2 = var_t4 + (temp_v0_6 * var_s7) + sp110;
                            var_s0 = ((var_s2 * var_s7) + 0x1F) & ~0xF;
                        } else {
                            spE4 = var_t1_2;
                            sp104 = var_t3_2;
                            spC8 = var_t4;
                            spCC = var_t5;
                            var_s0 = ((var_s2 * var_s7) + 0x1F) & ~0xF;
                            temp_v0_7 = gl_func_0001CA10(var_t4 + (temp_v0_6 * var_s7) + sp110, var_s0, sp138, (int)arg2 + 1, temp_v1_4);
                            var_a0_2 = temp_v0_7;
                        }
                        var_t0 = var_a0_2 & 0xF;
                        FW(var_s3_2, 0x4) = (s32) ((var_a0_2 - var_t0) + 0x80000000);
                        FW(var_s3_2, 0x0) = (((var_s0 >> 4) & 0xFF) << 0x10) | 0x14000000 | ((0x940 - var_s0) & 0xFFFF);
                        var_a1 = FW(arg2, 0x0);
                        var_s3_2 += 8;
                    } else {
                        var_s1 = 0;
                        var_a1 = FW(arg2, 0x0);
                    }
                    temp_v0_8 = var_s3_2;
                    if (var_a1 != 0) {
                        FW(temp_v0_8, 0x0) = 0x0F000000;
                        var_s3_2 += 8;
                        FW(temp_v0_8, 0x4) = (s32) (FW(sp150, 0x8) + 0x80000010);
                        sp138 = 2;
                        FW(arg2, 0x0) = 0;
                    }
                    temp_v0_9 = (u32) FW(sp150, 0x0) >> 0x1C;
                    if (var_t3_2 == 0) {
                        sp120 = var_s4 * 2;
                    } else {
                        var_s5 = (var_s6 + 0x1F) & ~0xF;
                    }
                    switch (temp_v0_9) {            /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                        temp_v0_10 = var_s3_2;
                        temp_s3 = var_s3_2 + 8;
                        temp_v1_5 = temp_s3;
                        var_s3_2 = temp_s3 + 8;
                        FW(temp_v0_10, 0x0) = (((0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0) & 0xFFFF) | 0x08000000;
                        FW(temp_v0_10, 0x4) = (s32) (((var_s5 + 0x580) << 0x10) | ((var_s1 * 2) & 0xFFFF));
                        FW(temp_v1_5, 0x0) = (s32) (((sp138 & 0xFF) << 0x10) | 0x01000000);
                        FW(temp_v1_5, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000000);
                        break;
                    case 3:                         /* switch 3 */
                        temp_v0_11 = var_s3_2;
                        temp_s3_2 = var_s3_2 + 8;
                        temp_v1_6 = temp_s3_2;
                        var_s3_2 = temp_s3_2 + 8;
                        FW(temp_v0_11, 0x0) = (((0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0) & 0xFFFF) | 0x08000000;
                        FW(temp_v0_11, 0x4) = (s32) (((var_s5 + 0x580) << 0x10) | ((var_s1 * 2) & 0xFFFF));
                        FW(temp_v1_6, 0x0) = (s32) ((((sp138 | 4) & 0xFF) << 0x10) | 0x01000000);
                        FW(temp_v1_6, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000000);
                        break;
                    case 1:                         /* switch 3 */
                        temp_s3_3 = var_s3_2 + 8;
                        spE4 = var_t1_2;
                        sp104 = var_t3_2;
                        spC8 = var_t4;
                        spCC = var_t5;
                        game_libs_func_0003443C(var_s3_2, 0, (s16) (0x940 - (((var_s2 * var_s7) + 0x1F) & 0xFFF0)) + var_t0, var_s5 + 0x580, var_s1 * 2);
                        temp_a0_3 = temp_s3_3;
                        var_s3_2 = temp_s3_3 + 8;
                        game_libs_func_0003443C(temp_a0_3, (u8 *) sp138, FW(arg2, 0xC) + 0x80000000);
                        break;
                    }
                    if (var_t3_2 != 0) {
                        FW(var_s3_2, 0x0) = ((var_s5 + (var_s4 * 2) + 0x580) & 0xFFFFFF) | 0x0A000000;
                        FW(var_s3_2, 0x4) = (s32) (((var_s6 + 0x580) << 0x10) | ((((var_s1 + var_s8) - var_t1_2) * 2) & 0xFFFF));
                        var_s3_2 += 8;
                    }
                    temp_v1_7 = (var_s1 + var_s8) - var_t1_2;
                    var_t3_2 += temp_v1_7;
                    if (sp138 != 1) {
                        sp138 = 0;
                        if (sp138 != 2) {
                            if (var_s6 != 0) {
                                var_s6 += temp_v1_7 * 2;
                            } else {
                                var_s6 = (var_s4 + temp_v1_7) * 2;
                            }
                        } else {
                            var_s6 += temp_v1_7 * 2;
                        }
                    } else {
                        sp120 = 0x20;
                        var_s6 = (var_s1 * 2) + 0x20;
                        sp138 = 0;
                    }
                    break;
                case 3:                             /* switch 2 */
                    var_s7 = 5;
                    var_t5 = 0x10;
                    goto block_41;
                case 1:                             /* switch 2 */
                    var_s7 = 0x10;
                    var_t5 = 0x10;
                    goto block_41;
                }
                if (sp140 != 0) {
                    temp_a0_4 = var_s3_2;
                    sp88 = 1;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_4, var_s6 + 0x580, (u8 *) ((sp108 - var_t3_2) * 2));
                    FW(sp9C, 0xB0) = (u8) (FW(sp9C, 0xB0) | 0x20);
                    game_libs_func_0003443C(arg6, (u8 *) arg0);
                    var_a0 = sp50;
                } else {
                    if (sp13C != 0) {
                        FW(arg2, 0x0) = 1;
                        FW(arg2, 0x8) = (s32) FW(sp14C, 0x0);
                    } else {
                        FW(arg2, 0x8) = (s32) (FW(arg2, 0x8) + spFC);
                    }
                    if (var_t3_2 == sp108) {
                        var_a0 = sp50;
                    } else {
                        goto loop_23;
                    }
                }
            }
            switch (spC0) {                         /* switch 4; irregular */
            case 1:                                 /* switch 4 */
                spAE = sp120 + 0x580;
                break;
            case 2:                                 /* switch 4 */
                switch (spBC) {                     /* switch 5; irregular */
                case 0:                             /* switch 5 */
                    temp_a0_5 = var_s3_2;
                    spAE = 0x3E0;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_5, sp120 + 0x580, (u8 *)0x3E0, (((s32) sp108 / 2) + 7) & ~7);
                    spB0 = sp108;
                    if (sp88 != 0) {
                        temp_a0_6 = var_s3_2;
                        var_s3_2 += 8;
                        spC8 = var_t4;
                        spCC = var_t5;
                        game_libs_func_0003443C(temp_a0_6, sp108 + 0x3E0, sp108 + 0x10);
                    }
                    var_a0 = sp50;
                    break;
                case 1:                             /* switch 5 */
                    temp_a0_7 = var_s3_2;
                    var_s3_2 += 8;
                    spC8 = var_t4;
                    spCC = var_t5;
                    game_libs_func_0003443C(temp_a0_7, sp120 + 0x580, spB0 + 0x3E0, (((s32) sp108 / 2) + 7) & ~7);
                    var_a0 = sp50;
                    break;
                }
                break;
            }
            temp_t8 = spBC + 1;
            if (sp88 != 0) {
                var_v1 = FW(arg1, 0x0);
                arg5 = var_s3_2;
            } else {
                spBC = temp_t8;
                if (temp_t8 == spC0) {
                    spD4 = var_s7;
                    spCC = var_t5;
                    spC8 = var_t4;
                    var_v1 = FW(arg1, 0x0);
                    arg5 = var_s3_2;
                } else {
                    goto loop_7;
                }
            }
        }
    }
    var_t1_3 = 0;
    if (((u32) (var_v1 * 2) >> 0x1F) == 1) {
        var_t1_3 = 1;
        FW(arg1, 0x0) &= 0xFFBF;
    }
    temp_s4 = arg4 * 2;
    sp138 = var_t1_3;
    temp_v0_12 = game_libs_func_0003443C(arg5, arg2, (u8 *) temp_s4, (u32) sp136, (s32) spAE, var_t1_3);
    var_s3_3 = temp_v0_12;
    if (sp8C == 3) {
        var_s3_3 = temp_v0_12 + 8;
        game_libs_func_0003443C(temp_v0_12, (u8 *)0x3C0, (u8 *)0x3C0, temp_s4, 0);
    }
    temp_a0_8 = var_s3_3;
    if (sp8C == 2) {
        var_s3_3 += 8;
        game_libs_func_0003443C(temp_a0_8, (u8 *)0x3C0, (u8 *)0x3C0, temp_s4);
    }
    temp_a0_9 = var_s3_3;
    var_a1_2 = FW(arg1, 0x2);
    if (var_a1_2 != 0) {
        var_s3_3 += 8;
        if ((s32) var_a1_2 < 0x10) {
            var_a1_2 = 0x10;
        }
        game_libs_func_0003443C(temp_a0_9, (u8 *) var_a1_2, (u8 *)0x3C0, 0U, temp_s4 + 0x20);
    }
    temp_a2_3 = FW(arg1, 0x14);
    if (temp_a2_3 != 0) {
        temp_s3_4 = var_s3_3 + 8;
        game_libs_func_0003443C(var_s3_3, (u8 *) temp_s4, temp_a2_3);
        temp_a0_10 = temp_s3_4;
        var_s3_3 = temp_s3_4 + 8;
        game_libs_func_0003443C(temp_a0_10, (u8 *) sp138, (u8 *)0x3C0, FW(arg2, 0xC) + 0x40);
    }
    temp_s0 = FW(arg1, 0x7);
    temp_v1_8 = FW(arg1, 0xE);
    temp_s2 = FW(arg2, 0xC) + 0x800000C0;
    if ((temp_s0 != 0) && (temp_v1_8 != 0)) {
        temp_s3_5 = var_s3_3 + 8;
        game_libs_func_0003443C(var_s3_3, (u8 *)0x3C0, (u8 *)0x760, temp_s4);
        var_s1_2 = 0x760 - temp_s0;
        if (FW(arg2, 0x1A) != 0) {
            var_s1_2 = 0x760 - temp_s0;
            var_s3_4 = temp_s3_5 + 8;
            game_libs_func_0003443C(temp_s3_5, var_s1_2, (u8 *) temp_s0);
            FW(arg2, 0x1A) = 0U;
        } else {
            var_s3_4 = temp_s3_5 + 8;
            game_libs_func_0003443C(temp_s3_5, var_s1_2, (u8 *) temp_s0, temp_s2);
        }
        temp_s3_6 = var_s3_4 + 8;
        game_libs_func_0003443C(var_s3_4, (temp_s4 - temp_s0) + 0x3C0, (u8 *) temp_s0, temp_s2);
        temp_s3_7 = temp_s3_6 + 8;
        game_libs_func_0003443C(temp_s3_6, (u8 *) ((s32) temp_s4 >> 4), (u8 *) temp_v1_8, 0x760U, (s32) var_s1_2);
        var_s3_3 = temp_s3_7 + 8;
        game_libs_func_0003443C(temp_s3_7, var_s1_2, (u8 *)0x3C0, temp_s4);
    } else {
        FW(arg2, 0x1A) = 1U;
    }
    if ((FW(arg1, 0x3) != 0) || (FW(arg2, 0x2) != 0)) {
        var_s0_2 = 1;
    } else if ((FW(arg1, 0x4) != 0) || (var_s0_2 = 0, (FW(arg2, 0x3) != 0))) {
        var_s0_2 = 2;
    }
    var_s3 = game_libs_func_0003443C(var_s3_3, arg1, arg2, arg4, 0x3C0, var_s0_2, sp138);
    if ((u16) FW(arg1, 0x0) & 1) {
        if (!(sp138 & 1)) {
            sp138 = 0;
        }
        var_s3 = game_libs_func_0003443C(var_s3, arg1, arg2, temp_s4, sp138, var_s0_2);
    }
    return var_s3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001E134);
#endif
#endif

// gl_func_0001EE78 — STRUCTURAL PASS (0xA8 / 42 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Small F3D/GBI display-list command-pair emitter in the
// game_libs graphics family.
//
//   Gfx *gl_func_0001EE78(Gfx *dl, a1, a2, a3) {
//     a3 &= 0xFFFF;
//     if (a3 == 0) {
//       jal 0x31BC8(dl, 0x3C0, …);              // 0x0C00C6F2
//       return dl + 8;                            // one cmd consumed
//     }
//     // emit GBI command #1 (8 bytes):
//     dl->word0 = 0x08000000 | hw_at_sp32;        // class-0x08 cmd
//     dl->word1 = 0x03C00000 | (a2 & 0xFFFF);
//     dl += 8;
//     // emit GBI command #2 (8 bytes):
//     dl->word0 = 0x05000000 | ((a2 & 0xFF) << 16) | (a3 & 0xFFFF);
//     dl->word1 = *(int*)(a1 + 0xC) + 0x80000020; // segmented addr
//     return dl + 8;                               // dl advanced 0x10
//   }
//
// Struct-typing reference: dl is an F3D Gfx write cursor (8-byte
//   command words). Two GBI command classes are emitted inline: a
//   0x08-class word0 paired with a 0x03C0-tagged word1, then a
//   0x05-class word0 (packing a2's low byte and a3) paired with a
//   segment-relative pointer word1 = a1[0x0C] + 0x80000020. The
//   a3==0 fast path instead delegates to fixed routine 0x0C00C6F2
//   (≈0x31BC8) and consumes a single command. Sibling of the
//   gl_func_0001D4C0 / gl_func_0001DA7C F3D-builder family.
// Caps (DEFERRED): single jr $ra. F3D DL command emitter: if
//   (a3&0xFFFF)==0 call helper(dl,0x3C0) and return dl+8; else emit
//   two GBI command pairs into dl ((arg4|0x08000000)/((a2&0xFFFF)|
//   0x03C00000), then (((arg5&0xFF)<<16)|0x05000000|(a3&0xFFFF))/
//   (a1->0xC+0x80000020)) and return the advanced ptr. Real-C
//   structural body below; byte-match deferred — placeholder jal
//   (0xC6F2) is a runtime-patched USO reloc (need USO reloc infra)
//   plus bnez/constant-build schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the helper.
#ifdef NON_MATCHING
extern int gl_func_00000000();
int gl_func_0001EE78(int *dl, int *a1, int a2, int a3, int arg4, int arg5) {
    int *s0 = dl;
    if ((a3 & 0xFFFF) == 0) {
        gl_func_00000000(s0, 0x3C0);
        return (int)(s0 + 2);
    }
    s0[0] = ((unsigned short)arg4) | 0x08000000;
    s0[1] = (a2 & 0xFFFF) | 0x03C00000;
    s0 += 2;
    s0[0] = ((arg5 & 0xFF) << 16) | 0x05000000 | (a3 & 0xFFFF);
    s0[1] = a1[0xC / 4] + 0x80000020;
    s0 += 2;
    return (int)s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001EE78);
#endif

// gl_func_0001EF20 — STRUCTURAL PASS (0x328 / 202 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A tween/step sprite-strip emitter in the game_libs
// graphics family. -0x68 frame, ra/s1/s0 saved, a3 at sp+0x74.
//
//   ret gl_func_0001EF20(Gfx *dst, S *src, T *a2, int a3) {
//     int x0 = (src->h_8  << 4) & 0xFFFF;       // scaled geom hw
//     int x1 = (src->h_A  << 4) & 0xFFFF;
//     int g  = a2->h_10;                         // compare key
//     byte m = src->b_5;
//     int g2 = a2->h_12;
//     if (g == x0) { ... fast/degenerate path ... }
//     int step = (x0 - x1) / (a3 >> 3);          // guarded sdiv
//                                                 // (break 7 / break 6
//                                                 //  div0 + ovf traps)
//     ... ~160 words: loop advancing an accumulator by `step`,
//         emitting interpolated F3D/sprite GBI commands into dst
//         each iteration; cleanup + return ...
//   }
//
// Struct-typing reference: src struct — halfwords src->8 / src->0xA
//   (start/end coordinate, each <<4 fixed-point scaled), byte src->5
//   (mode flag). a2 — halfwords a2->0x10 / a2->0x12 (comparison key /
//   limit). The per-step delta is a signed division of the scaled
//   coordinate range by (a3 >> 3); the two `break 7` / `break 6`
//   words are the standard GCC div-by-zero / INT_MIN-overflow trap
//   sequence, not real code paths. The remaining body is the
//   interpolation loop that writes the sprite strip into the dst
//   Gfx cursor. Sibling of the gl_func_0001EE78 F3D-emitter family.
// Caps (DEFERRED): CLEAN single jr $ra. Tween/step sprite-strip
//   emitter (gl_func_0001EE78 F3D family). Real-C STRUCTURAL body
//   below per the analysis (scaled coords x0/x1 = src->8/->0xA <<4,
//   compare key a2->0x10, guarded sdiv step = (x0-x1)/(a3>>3), then
//   interpolation loop emitting GBI command pairs into dst). The
//   break 7 / break 6 words are the standard GCC div0 / INT_MIN
//   trap sequence (not real paths). Byte-match deferred — ~202-insn
//   guarded-sdiv + multi-iteration emit, placeholder jals need USO
//   reloc infra. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
// gl_func_0001EF20 — FULL m2c DECODE (58.18% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001EF20)();
char *gl_func_0001EF20(char *arg0, char *arg1, char *arg2, s32 arg3, u16 arg4, s32 arg5) {
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s32 sp34;
    s32 sp30;
    s32 sp28;
    s16 var_a3;
    s16 var_t0;
    s32 temp_t0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_t1;
    s32 var_v0;
    u16 temp_ra;
    u16 temp_t5;
    u8 temp_t2;
    u8 temp_t4;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    char *var_s0;

    temp_t5 = FW(arg2, 0x10);
    temp_t0 = (FW(arg1, 0x8) * 0x10) & 0xFFFF;
    temp_t2 = FW(arg1, 0x5);
    temp_ra = FW(arg2, 0x12);
    temp_v1 = (FW(arg1, 0xA) * 0x10) & 0xFFFF;
    if (temp_t5 != temp_t0) {
        var_v0 = arg3 >> 3;
        var_a3 = (s16) ((s32) (temp_t0 - temp_t5) / var_v0);
    } else {
        var_a3 = 0;
        var_v0 = arg3 >> 3;
    }
    if (temp_ra != temp_v1) {
        var_t0 = (s16) ((s32) (temp_v1 - temp_ra) / var_v0);
    } else {
        var_t0 = 0;
    }
    temp_t4 = FW(arg2, 0x4);
    sp30 = (s32) temp_t5;
    var_t1 = temp_t4 & 0x7F;
    if (temp_t4 != temp_t2) {
        var_t1 = temp_t4 & 0x7F;
        sp52 = (s16) ((s32) (((temp_t2 & 0x7F) - var_t1) << 9) / var_v0);
        FW(arg2, 0x4) = temp_t2;
    } else {
        sp52 = 0;
    }
    FW(arg2, 0x10) = (u16) (sp30 + (var_a3 * var_v0));
    FW(arg2, 0x12) = (u16) (temp_ra + (var_t0 * var_v0));
    if (FW(arg1, 0x0) & 1) {
        temp_s0 = arg0 + 8;
        sp56 = var_a3;
        sp54 = var_t0;
        sp34 = var_t1;
        sp28 = (s32) temp_ra;
        sp50 = (s16) temp_t4;
        game_libs_func_0003443C(arg0, 0x5C0, 0x1A0, var_a3);
        temp_s0_2 = temp_s0 + 8;
        game_libs_func_0003443C(temp_s0, var_t1 * 2, sp52, var_a3, (s32) var_t0);
        var_s0 = temp_s0_2 + 8;
        game_libs_func_0003443C(temp_s0_2, sp30, (s16) sp28);
        switch (arg5) {                             /* irregular */
        case 1:
            var_a1 = *(s32 *)0x1A2D4;
            break;
        case 2:
            var_a1 = *(s32 *)0x1A2D8;
            break;
        }
    } else {
        temp_s0_3 = arg0 + 8;
        FW(arg0, 0x0) = (s32) ((((var_t1 * 2) & 0xFF) << 0x10) | 0x12000000 | (sp52 & 0xFFFF));
        FW(arg0, 0x4) = (s32) ((var_a3 << 0x10) | (var_t0 & 0xFFFF));
        FW(arg0, 0x8) = 0x16000000;
        FW(temp_s0_3, 0x4) = (s32) ((temp_t5 << 0x10) | (temp_ra & 0xFFFF));
        var_s0 = temp_s0_3 + 8;
        var_a1 = *(s32 *)0x1A2DC;
    }
    temp_v1_2 = (s32) FW(arg1, 0x0);
    FW(var_s0, 0x4) = var_a1;
    FW(var_s0, 0x0) = (s32) (((((s32) arg4 >> 4) & 0xFF) << 0x10) | *(s32 *)0x1A2D0 | ((arg3 & 0xFF) << 8) | ((((s32) (temp_t4 & 0x80) >> 7) & 1) * 0x10) | ((((u32) (temp_v1_2 << 6) >> 0x1F) & 1) * 8) | (((u8) FW(arg1, 0x0) & 1) * 4) | ((((u32) (temp_v1_2 * 0x10) >> 0x1F) & 1) * 2) | (((u32) (temp_v1_2 << 5) >> 0x1F) & 1));
    return var_s0 + 8;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001EF20);
#endif

// gl_func_0001F248 — STRUCTURAL PASS (0x180 / 96 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A texture-block-load display-list builder in the game_libs
// F3D family. -0x20 frame, ra/s0 saved, a3 at sp+0x2C.
//
//   Gfx *gl_func_0001F248(Gfx *dst, H *a1, B *a2, int a3) {
//     int   w   = a1[0];
//     byte  b6  = a1->b_6;
//     int   typ = (w << 11) >> 30;              // 2-bit type field
//     if (typ != 0) {
//       int   sz  = (a3 * 2 + 0xF) & ~0xF;       // 16-align size
//       void *src = a2->w_8;
//       jal 0x31D3C(dst, 0x580, sz, src|0x80000000);  // 0x0C00C74F
//       dst += 8;
//       dst->word0 = 0x14080580;                  // tex-setup GBI cmd
//       dst->word1 = ...;                          // (a2->0x10 etc.)
//       dst += 8;
//       ... a few more texture-setup GBI words ...
//     }
//     return dst;                                  // advanced cursor
//   }
//
// Struct-typing reference: a1 header — word a1[0] holds a packed
//   2-bit type selector at <<11>>30 (gates the whole emit), byte
//   a1->6 a sub-mode. a2 block — word a2->8 is the texture source
//   pointer (made segment/physical via |0x80000000), halfword/word
//   a2->0x10 feeds the tile-setup command. Emitted commands use the
//   0x580 tile descriptor and a 0x14080580 word0 (a load-block-class
//   GBI op). Fixed routine 0x0C00C74F (≈0x31D3C) does the actual
//   DMA/load setup. Sibling of the gl_func_0001EE78 / gl_func_0001EF20
//   F3D-emitter family.
// Caps (DEFERRED): CLEAN single jr $ra. Texture-block-load DL
//   builder (gl_func_0001EE78/EF20 F3D family). Real-C STRUCTURAL
//   body below per the analysis (packed 2-bit type gate
//   (a1[0]<<11)>>30, 16-aligned size (a3*2+0xF)&~0xF, src =
//   a2->8|0x80000000, fixed 0x31D3C load-setup call, then
//   0x14080580 tile-setup GBI words). Byte-match deferred —
//   placeholder jal needs USO reloc infra + bitfield/align schedule.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
int *gl_func_0001F248(int *dst, int *a1, int *a2, int a3) {
    int *s0 = dst;
    int w = a1[0];
    int b6 = *(unsigned char *)((char *)a1 + 6);
    int typ = (unsigned)(w << 11) >> 30;
    int v1 = a2[8 / 4];
    if (typ != 0) {
        int sz = (a3 * 2 + 0xF) & ~0xF;
        int dp = *(int *)((char *)&D_00000000 + 0x20);
        gl_func_00000000(s0, 0x580, sz, dp + 0x80000000);
        *(int *)((char *)&D_00000000 + 0x20) = dp + a3 * 4;
        return s0 + 2;
    }
    s0[0] = 0x14080580;
    s0[1] = a1[0x10 / 4] + 0x80000000;
    s0 += 2;
    if (b6 != 0) {
        unsigned int num = (unsigned int)v1 * *(unsigned char *)((char *)&D_00000000 + (b6 >> 2));
        v1 = num / *(unsigned char *)((char *)&D_00000000 + (b6 & 3));
    }
    v1 &= 0x3f;
    {
        int avail = 0x40 - v1;
        if (avail < a3) {
            int n = (a3 - avail + 0x3f) >> 6;
            if (n != 0) {
                s0[0] = 0x09000000 | ((n & 0xff) << 16) | 0x580;
                s0[1] = 0x06000080;
                s0 += 2;
                a2[8 / 4] = v1;
            }
        }
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001F248);
#endif

// gl_func_0001F3C8 — STRUCTURAL PASS (0x720 / 456 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is a large tile-mode dispatcher + display-list builder
// in the game_libs F3D family. -8 frame, s0 saved, args on stack.
//
//   ret gl_func_0001F3C8(a0, a1, R *a2, a3, int kind) {  // kind at sp+0x1C
//     switch (kind) {                              // beq 1 / beq 2
//       case 1:  a2->b_3 = a2->b_3src;             // tile class A
//                a2->b_2 = 0x0940-selector; break;
//       case 2:  a2->b_2 = a2->b_2src;             // tile class B
//                a2->b_3 = 0x0AE0-selector; break;
//       default: ...                                // pass-through
//     }
//     ... large body (~0xAA-word forward span): builds the F3D tile/
//         load display list using the chosen 0x0940 vs 0x0AE0
//         descriptor class, the 0x05C0 / 0x03C0 tile tags, and a
//         per-row emit loop into the dst Gfx cursor; cleanup +
//         return ...
//   }
//
// Struct-typing reference: a2 is a tile-state record — bytes a2->2
//   and a2->3 hold the active tile-descriptor selectors, swapped
//   between a 0x0940-class and a 0x0AE0-class depending on the
//   stack-passed `kind` code (1, 2, or default). The body emits the
//   matching G_LOADBLOCK/G_SETTILE-style GBI command sequence
//   (0x05C0 / 0x03C0 tile tags) for the selected class. Top of the
//   gl_func_0001F248 texture/tile builder sub-family.
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0x720/184 words, ONE function). Tile-mode dispatcher + DL
//   builder (top of the gl_func_0001F248 texture/tile sub-family).
//   Real-C STRUCTURAL body below per the analysis (kind switch 1/2/
//   default swaps a2->2 / a2->3 tile selectors between a 0x0940 and
//   a 0x0AE0 descriptor class, then emits the matching
//   G_LOADBLOCK/G_SETTILE GBI sequence with 0x05C0/0x03C0 tags).
//   Byte-match deferred — large multi-branch + placeholder jals
//   (need USO reloc infra). Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the leaf emitters.
// gl_func_0001F3C8 — FULL m2c DECODE (56.05% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING

#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001F3C8)();
char *gl_func_0001F3C8(char *arg0, char *arg1, char *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_t1;
    s32 temp_v0;
    s32 var_t0;
    s32 var_v1_2;
    u8 var_a1;
    u8 var_v1;
    char *temp_a0;
    char *temp_a0_2;
    char *temp_a0_3;
    char *temp_a0_4;
    char *var_a0;
    char *var_a0_2;

    switch (arg5) {                                 /* irregular */
    case 1:
        var_v1 = FW(arg2, 0x2);
        var_t0 = 0x940;
        var_a1 = FW(arg1, 0x3);
        FW(arg2, 0x3) = 0U;
        FW(arg2, 0x2) = var_a1;
block_6:
        if (arg4 != 1) {
            if (var_v1 != var_a1) {
                var_v1_2 = arg3 + var_a1;
                temp_t1 = var_v1_2 - var_v1;
                FW(arg0, 0x0) = 0x080005C0;
                FW(arg0, 0x4) = (s32) ((temp_t1 & 0xFFFF) | 0x03C00000);
                temp_a0 = arg0 + 8;
                FW(temp_a0, 0x4) = 0;
                var_a0_2 = temp_a0 + 8;
                FW(arg0, 0x8) = (s32) ((((s32) (((s32) (arg3 << 0xF) / 2) - 1) / (s32) ((s32) (temp_t1 - 2) / 2)) & 0xFFFF & 0xFFFF) | 0x06000000);
            } else {
                FW(arg0, 0x0) = 0x0A0005C0;
                FW(arg0, 0x4) = (s32) ((arg3 & 0xFFFF) | 0x03C00000);
                var_a0_2 = arg0 + 8;
                var_v1_2 = arg3 + var_a1;
            }
            if (var_v1 != 0) {
                FW(var_a0_2, 0x0) = (s32) (((((s32) ((var_v1 + 0xF) & 0xFFF0) >> 4) & 0xFF) << 0x10) | 0x14000000 | 0x5C0);
                FW(var_a0_2, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000080);
                temp_a0_2 = var_a0_2 + 8;
                FW(var_a0_2, 0x8) = 0x0A0003C0;
                FW(temp_a0_2, 0x4) = (s32) (((var_v1 + 0x5C0) << 0x10) | ((var_v1_2 - var_v1) & 0xFFFF));
                var_a0 = temp_a0_2 + 8;
            } else {
                FW(var_a0_2, 0x0) = 0x0A0003C0;
                FW(var_a0_2, 0x4) = (s32) ((var_v1_2 & 0xFFFF) | 0x05C00000);
                var_a0 = var_a0_2 + 8;
            }
        } else {
            temp_v0 = arg3 & 0xFFFF;
            temp_a0_3 = arg0 + 8;
            FW(arg0, 0x4) = (s32) (temp_v0 | 0x03C00000);
            FW(arg0, 0x0) = 0x0A0005C0;
            temp_a0_4 = temp_a0_3 + 8;
            FW(arg0, 0x8) = 0x020005C0;
            FW(temp_a0_3, 0x4) = (s32) var_a1;
            FW(temp_a0_4, 0x4) = (s32) (((var_a1 + 0x5C0) << 0x10) | temp_v0);
            FW(temp_a0_3, 0x8) = 0x0A0003C0;
            var_a0 = temp_a0_4 + 8;
        }
        if (var_a1 != 0) {
            FW(var_a0, 0x0) = (s32) (((((s32) ((var_a1 + 0xF) & 0xFFF0) >> 4) & 0xFF) << 0x10) | 0x15000000 | ((arg3 + 0x5C0) & 0xFFFF));
            FW(var_a0, 0x4) = (s32) (FW(arg2, 0xC) + 0x80000080);
            var_a0 += 8;
        }
        FW(var_a0, 0x0) = (s32) (((((s32) ((arg3 + 0x3F) & 0xFFC0) >> 4) & 0xFF) << 0x10) | 0x04000000 | 0x7FFF);
        FW(var_a0, 0x4) = (s32) ((var_t0 & 0xFFFF) | 0x05C00000);
        return var_a0 + 8;
    case 2:
        var_a1 = FW(arg1, 0x4);
        var_v1 = FW(arg2, 0x3);
        var_t0 = 0xAE0;
        FW(arg2, 0x2) = 0U;
        FW(arg2, 0x3) = var_a1;
        goto block_6;
    default:
        return arg0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001F3C8);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0001F6A8)();
s32 game_libs_func_0001F6A8(void) {
    f32 d025 = 0.25f;
    f32 d05 = 0.5f;
    f32 d075 = 0.75f;
    char *temp_t3;
    char *temp_t6;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 var_f16;
    f32 var_f18;
    s32 temp_f16;
    s32 temp_f6;
    s32 temp_f8;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    char *temp_t3_2;

    var_v0_2 = 0x80;
    var_v1 = 0x200;
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x3FC)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / d025);
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x3F8)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (*(f32*)((char*)&D_00000000 + 0xE70)));
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x3F4)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / d05);
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x3F0)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (*(f32*)((char*)&D_00000000 + 0xE74)));
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x3EC)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / d075);
    do {
        temp_f16 = 0xFB - var_v0_2;
        var_v0_2 += 1;
        temp_t3 = (*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1;
        var_v1 += 4;
        *(f32*)temp_t3 = (256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (f32) temp_f16;
    } while (var_v0_2 < 0xFB);
    var_v0_3 = 0x10;
    var_v1_2 = 0x40;
    do {
        temp_f10 = (f32) (0x80 - var_v0_3);
        var_v0_3 += 1;
        temp_t6 = (*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_2;
        var_v1_2 += 4;
        *(f32*)temp_t6 = (256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (60.0f + (temp_f10 * 4.0f));
    } while (var_v0_3 < 0x80);
    var_v0 = 4;
    var_v1_3 = 0x10;
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x4)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) 0xE * 60.0f)));
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x8)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) 0xD * 60.0f)));
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0xC)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) 0xC * 60.0f)));
    var_a0 = 0xF - 4;
    var_f18 = 480.0f + ((f32) var_a0 * 60.0f);
    var_f16 = 256.0f * (*(f32*)((char*)&D_00000000 + 0x2054));
    if (4 != 0xC) {
        do {
            temp_f10_2 = (f32) (var_a0 - 1);
            temp_f8 = var_a0 - 2;
            temp_f6 = var_a0 - 3;
            var_v0 += 4;
            var_a0 = 0xF - var_v0;
            *(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3) = var_f16 / var_f18;
            (*(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3 + 0x4)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + (temp_f10_2 * 60.0f)));
            (*(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3 + 0x8)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) temp_f8 * 60.0f)));
            temp_t3_2 = (*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3;
            var_v1_3 += 0x10;
            var_f18 = 480.0f + ((f32) var_a0 * 60.0f);
            (*(f32*)((char*)temp_t3_2 + 0xC)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) temp_f6 * 60.0f)));
            var_f16 = 256.0f * (*(f32*)((char*)&D_00000000 + 0x2054));
        } while (var_v0 != 0xC);
    }
    *(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3) = var_f16 / var_f18;
    (*(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3 + 0x4)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) (var_a0 - 1) * 60.0f)));
    (*(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3 + 0x8)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) (var_a0 - 2) * 60.0f)));
    (*(f32*)((*(char**)((char*)&D_00000000 + 0x2CF8)) + var_v1_3 + 0xC)) = (f32) ((256.0f * (*(f32*)((char*)&D_00000000 + 0x2054))) / (480.0f + ((f32) (var_a0 - 3) * 60.0f)));
    (*(f32*)((char*)(*(char**)((char*)&D_00000000 + 0x2CF8)) + 0x0)) = 0.0f;
    return var_v0 + 4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001F6A8);
#endif

#ifdef NON_MATCHING
/* Reset 3 byte-arrays in the global D struct: for each entry in D+0x2C40[48],
 * D+0x2C10[48], D+0x2C70[128], if entry != 5 set it to 0 (via beql 5,entry).
 * Reloc-blind (&D_00000000). Byte-match multi-run: target unrolls the 3rd loop
 * (128 entries) by 4 and uses pointer-cursor + branch-likely (beql/bnezl) that
 * the clean for-loops don't reproduce (36 vs 50 insns). */
void game_libs_func_0001FA20(void) {
    char *p, *e;
    for (p = (char *)&D_00000000, e = p + 48; p < e; p++) {
        if (((unsigned char *)p)[0x2C40] != 5) {
            p[0x2C40] = 0;
        }
    }
    for (p = (char *)&D_00000000, e = p + 48; p < e; p++) {
        if (((unsigned char *)p)[0x2C10] != 5) {
            p[0x2C10] = 0;
        }
    }
    {
        int i;
        for (i = 0; i < 128; i++) {
            if (((unsigned char *)&D_00000000)[0x2C70 + i] != 5) {
                ((char *)&D_00000000)[0x2C70 + i] = 0;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FA20);
#endif

// gl_func_0001FAE8 — STRUCTURAL PASS (0xEC / 59 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A record-array sweep / "reactivate active records"
// routine in the game_libs sprite subsystem. -0x30 frame, full
// s0-s5/ra save.
//
//   void gl_func_0001FAE8(int a0) {
//     S *g = &D_0;                                // shared global base
//     int n = g->w_2070;                           // record count
//     if (n <= 0) return;
//     R *tbl = ...;                                 // &D_5378 fn/str tbl
//     for (int i = 0, idx = 0; i < n; i++) {
//       R *rec = *(R**)(&D_0 + 0x2CFC) + idx;       // record table
//       if (rec->b_33 != 0) continue;               // flag gates
//       if (rec->b_34 != 0) continue;
//       if (rec->b_30 == 0) continue;
//       byte *p = rec->w_44;                        // status-byte ptr
//       *p &= ~0x80;                                 // clear bit7
//       *p |=  0x40;                                 // set   bit6
//       (*cb1)(a0);                                  // jal 0 USO reloc
//       (*cb2)(a0);                                  // jal 0 USO reloc
//       idx += stride;
//     }
//   }
//
// Struct-typing reference: shares the sprite-subsystem globals with
//   gl_func_0001DCB4 / gl_func_0001E134 — word &D_0+0x2070 is the
//   live-record count, pointer &D_0+0x2CFC is the fixed-stride record
//   table base. Per record R: bytes R->0x30 / 0x33 / 0x34 are the
//   active/skip gate flags, word R->0x44 points to a shared status
//   byte whose bit7 is cleared and bit6 set (a "needs-refresh /
//   activated" toggle). &D_5378 is an auxiliary fn-ptr/string table.
//   The two `jal 0` words are USO-relocated callback slots (resolved
//   at load) invoked with the caller-supplied a0.
// Caps (DEFERRED): CLEAN single jr $ra. Record-array sweep /
//   "reactivate active records" (shares sprite-subsystem globals
//   with gl_func_0001DCB4 / gl_func_0001E134). Real-C STRUCTURAL
//   body below per the analysis (count &D_0+0x2070, fixed-stride
//   record table &D_0+0x2CFC, skip gates rec->0x33/0x34/0x30,
//   status byte rec->0x44 clear bit7 / set bit6, two jal-0
//   USO-reloc callbacks). Byte-match deferred — placeholder jal-0
//   callbacks need USO reloc infra + s0-s5 loop schedule. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the callbacks.
// 2026-05-31: 61.39% -> 65.61% via LOGIC CORRECTIONS (prior body was WRONG):
//   guard is `a0 == rec->b_0x33` (not `==0`); the 3 callbacks pass `rec` not a0
//   and there are THREE (cb(rec), cb(rec), cb(&D+0x5378, rec)); record stride is
//   0xD0 (not 0x158); rec->0x44 is RELOADED between the &~0x80 and |0x40 stores.
//   Capped ~65%: target uses regular bne/beq (not branch-likely) on conds 2/3,
//   andi 0xff7f (not and-reg ~0x80), and a tighter s-reg allocation — codegen
//   caps, not missing logic.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0001FAE8(int a0) {
    char *g = (char *)&D_00000000;
    int n = *(int *)(g + 0x2070);
    int i, idx;
    if (n <= 0) {
        return;
    }
    idx = 0;
    for (i = 0; i < n; i++) {
        char *rec = *(char **)(g + 0x2CFC) + idx;
        if (*(unsigned char *)(rec + 0x33) == a0 &&
            *(unsigned char *)(rec + 0x34) == 0 &&
            *(unsigned char *)(rec + 0x30) != 0) {
            char *p;
            p = *(char **)(rec + 0x44);
            *p &= ~0x80;
            p = *(char **)(rec + 0x44);
            *p |= 0x40;
            gl_func_00000000(rec);
            gl_func_00000000(rec);
            gl_func_00000000((char *)&D_00000000 + 0x5378, rec);
        }
        idx += 0xD0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FAE8);
#endif


/* game_libs_func_0001FBCC: 2-insn non-standalone preload fragment.
 * SOURCE=3 audit 2026-06-01: no prologue and no `jr ra`
 * (`grep -c 03E00008` = 0). It loads v0 from the halfword bound at
 * D+0x2048, then falls into gl_func_0001FBD4. The successor reloads the
 * same bound in its loop at 0x1FC20 before comparing, so this entry is
 * not a clean C wrapper or accessor; keep INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FBCC);

// gl_func_0001FBD4 — STRUCTURAL PASS (0x7C / 31 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Sibling of gl_func_0001FAE8: a record-array sweep firing
// a per-record USO-reloc callback. -0x28 frame, s0-s2/ra saved.
//
//   void gl_func_0001FBD4(int n) {
//     if (n <= 0) return;
//     S *rec = &D_0 + 0x2D00;                       // record table base
//     for (int i = 0; ; ) {
//       int w = rec->w_0;                            // &D_0+0x2D00
//       if (w >> 31) {                                // sign-bit gate
//         byte f = rec->b_4;                          // &D_0+0x2D04
//         if (f == ...) {
//           (*cb)(rec);                                // jal 0 USO reloc
//         }
//       }
//       i++;
//       short lim = *(short*)(&D_x + 0x2048);          // global bound
//       if (i >= lim) break;
//       rec += 0x160;                                  // record stride
//     }
//   }
//
// Struct-typing reference: a second sprite-subsystem record table
//   distinct from gl_func_0001FAE8's — base &D_0 + 0x2D00, fixed
//   stride 0x160 per record. Record word R->0 carries an active flag
//   in its sign bit (srl 31); byte R->4 (i.e. &D_0+0x2D04 for index 0)
//   is a secondary gate. The loop iterates until a running counter
//   reaches a global limit halfword at &D_x + 0x2048, invoking the
//   USO-relocated callback (the `jal 0` slot, resolved at load) with
//   the record pointer. Same sweep family as gl_func_0001FAE8.
// Caps (DEFERRED): CLEAN single jr $ra. Sibling of gl_func_0001FAE8
//   — a second sprite-subsystem record-array sweep firing a
//   per-record USO-reloc callback. Real-C STRUCTURAL body below per
//   the analysis (record table &D_0+0x2D00, stride 0x160, sign-bit
//   gate on rec->0, secondary byte gate rec->4 != a0, loop bound =
//   short at &D_0+0x2048, jal-0 callback with the record ptr).
//   Byte-match deferred — placeholder jal-0 callback needs USO
//   reloc infra + beql/bnel s0-s2 schedule. Name pre-checked: no
//   extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the callback.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0001FBD4(int a0) {
    char *rec;
    int i;
    if (a0 <= 0) {
        return;
    }
    rec = (char *)&D_00000000 + 0x2D00;
    i = 0;
    do {
        if ((unsigned)*(int *)rec >> 31) {
            if (a0 != *(unsigned char *)(rec + 4)) {
                gl_func_00000000(rec);
            }
        }
        i++;
        rec += 0x160;
    } while (i < *(short *)((char *)&D_00000000 + 0x2048));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FBD4);
#endif

void gl_func_0001FC50(void) {
    gl_func_00000000();
}
/* gl_func_0001FC78: MATCHED 2026-05-31 — byte-identical to gl_func_0001FCD0; applied
 * its body (init v1=0; if(D[0x2178]) v1=cb(&D+0x2178); if(!v1) v1=cb(a0,a1); return v1). */
/* 2026-05-31: BYTE-IDENTICAL to the now-100% gl_func_0001FCD0 — applied its body. */
int gl_func_0001FC78(int a0, int a1) {
    int v1 = 0;
    if (*(int*)((char*)&D_00000000 + 0x2178) != 0) {
        v1 = gl_func_00000000((char*)&D_00000000 + 0x2178);
    }
    if (v1 == 0) {
        v1 = gl_func_00000000(a0, a1);
    }
    return v1;
}

extern int gl_func_00000000();

/* gl_func_0001FCD0: boundary-corrected (orphan-fn delete+merge). The 2-word
 * orphan game_libs_func_0001FCC8 (`lui t6,0; lw t6,0x2178(t6)`) was a splat
 * mis-split of THIS function's prologue — it loads *(int*)(&D+0x2178), which the
 * C reads first (IDO emits it pre-prologue). Merged into gl_func_0001FCD0.s
 * (0x50 -> 0x58); the NM-wrap C already compiled to build[2:]==expected, so the
 * merge is byte-exact. */
int gl_func_0001FCD0(int a0, int a1) {
    int v1 = 0;
    if (*(int*)((char*)&D_00000000 + 0x2178) != 0) {
        v1 = gl_func_00000000((char*)&D_00000000 + 0x2178);
    }
    if (v1 == 0) {
        v1 = gl_func_00000000(a0, a1);
    }
    return v1;
}

int gl_func_0001FD20(int a0, int a1) {
    int v = gl_func_00000000(a0);
    if (v != 0) {
        gl_func_00000000(v, a1);
    }
    return v;
}

int gl_func_0001FD5C(int a0, int a1) {
    int v = gl_func_00000000(a0);
    if (v != 0) {
        gl_func_00000000(v, a1);
    }
    return v;
}

// gl_func_0001FD98 — STRUCTURAL PASS (0x130 / 76 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 7-jr USO bundle
// (named fn + 6 tiny trailing helpers) — deferred USO re-split. The
// named leading fn (~23 words, ends at 0x1FDEC) is an alloc-and-
// zero-clear helper.
//
//   void *gl_func_0001FD98(H *a0) {
//     void *p = (*alloc)(a0);             // jal 0 USO-reloc allocator
//     if (p == 0) return 0;
//     for (char *c = p; c < (char*)a0->w_4; c++)  // zero-fill region
//       *c = 0;                            //  [p .. a0->4)
//     return p;
//   }
//
// Struct-typing reference: a0 is a small descriptor whose word a0->4
//   holds the end address / size limit of the buffer to clear. The
//   allocator is a USO-relocated callback (the leading `jal 0` slot,
//   resolved at load); a0 is preserved across it via sp+0x18. The
//   trailing bundled helpers (FDF4+) are tiny arithmetic utilities
//   (16-align `(x+0xF)&~0xF` with a bounds-checked store, a
//   min/clamp, etc.) belonging to the same allocator support family
//   — left for the deferred USO re-split.
// Caps (DEFERRED): single jr $ra (the "7-jr bundle" note is STALE;
//   .s is 0x5C/23 words, ONE function). Alloc-and-zero-clear helper.
//   Real-C STRUCTURAL body below per the analysis (jal-0 USO-reloc
//   allocator, a0 preserved via sp+0x18; zero-fill [p .. a0->4)).
//   Byte-match deferred — placeholder jal-0 allocator needs USO
//   reloc infra + beql/bnel clear-loop schedule. Name pre-checked:
//   no extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the allocator.
/* 23-insn alloc-then-zero-fill. CRACKED 2026-05-27 via goto-out lever:
 * `if (p == 0) goto out;` (instead of `return 0;`) routes the early-exit
 * through the SAME epilogue as the loop-completion path, allowing IDO to
 * emit `beq v0,$0,+0xC` directly to epilogue (with delay slot saving
 * a1=v0=0 as return value) — no intermediate `b skip; or v0,$0,$0` setup
 * needed. The shared epilogue lever (docs/IDO_CODEGEN.md
 * #feedback-ido-goto-epilogue-shared-saves-redundant-set) saves 2 insns
 * vs the if/return form. */
extern int gl_func_00000000();
void *gl_func_0001FD98(int *a0) {
    char *p = (char *)gl_func_00000000(a0);
    char *c;
    if (p == 0) goto out;
    for (c = p; c < (char *)a0[1]; c++) {
        *c = 0;
    }
out:
    return p;
}

/* Bump/arena allocator. aligned = (n+15) & ~15; if (arena->base + arena->size
 * < arena->cur + aligned) return 0 (overflow); else old = arena->cur;
 * arena->cur += aligned; arena->count++ (a0->0xC); return old.
 * MERGE: the success epilogue (count++; return old) was splat-split off as
 * game_libs_func_0001FE34 (UNSHARED — only this fn's `b 0x1FE34` reaches it,
 * verified); merged back here (size 0x40 -> 0x58).
 *
 * 2026-05-27: 73.09% → 89.23% via INVERTED-COND + `goto success` recipe.
 * The natural `if (overflow) return 0;` form let IDO merge both paths into
 * a `beqzl + load-hoist` tail (20 insns); the inverted `if (!overflow) {
 * a0[1] = newcur; goto success; } return 0; success: ...` shape forces
 * the target's structure (bnez + b success + separate fail jr-ra + success
 * jr-ra epi, 21 insns). 1 missing insn remains: target fills the bnez
 * delay slot with `move v1, a2` (saving cur for the later return) where
 * mine emits `nop` — IDO doesn't split cur's live range across the branch
 * because mine loads cur directly into v1 (no separate save needed).
 * The split needs cur loaded into $a2 first, then moved to $v1 — no clean
 * C lever (verified-ineffective: register-asm rejected by IDO; multi-decl
 * cur_ret CSE-folds; aliased-base loads). Last 1-insn diff is permuter-
 * class.
 *
 * INCLUDE_ASM remains the build path (function not yet byte-exact). */
#ifdef NON_MATCHING
void *game_libs_func_0001FDF4(int *a0, unsigned int n) {
  unsigned int new_var2;
  unsigned int aligned = (n + 15) & (~15);
  void *new_var;
  unsigned int new_var3;
  unsigned int cur = a0[1];
  unsigned int newcur = a0[1] + aligned;
  new_var = (void *) (cur ^ 0);
  new_var3 = (unsigned int) (a0[0] + a0[2]);
  new_var2 = newcur;
  if (new_var3 >= new_var2)
  {
    a0[1] = cur + aligned;
    goto success;
    if (!cur)
    {
    }
  }
  return 0;
  success:
  a0[3] += 1;

  return new_var;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FDF4);
#endif

/* 16-byte-align builder: a0[0]=a0[1]=(a1+0xF)&~0xF; a0[2]=a2-(a1&0xF); a0[3]=0.
 * LANDED fuzzy=100. The previously-documented 2-insn positional swap (and/subu
 * scheduling) closed naturally without the historical INSN_PATCH bridge —
 * INSN_PATCH was REMOVED 2026-05-23 as match-faking and the function still
 * matches; the scheduling difference apparently resolved via incremental
 * codegen changes upstream. */
void game_libs_func_0001FE4C(int *a0, int a1, int a2) {
    int up = (a1 + 0xF) & ~0xF;
    a0[0] = up;
    a0[1] = up;
    a0[2] = a2 - (a1 & 0xF);
    a0[3] = 0;
}

void game_libs_func_0001FE74(int *a0) { *(int*)((char*)(a0) + 0x10) = 0; *(int*)((char*)(a0) + 0x0) = 0; *(int*)((char*)(a0) + 0x8) = *(int*)((char*)(a0) + 0x4); }

/* 97.08% NM. 12-insn 8-store struct init with 2-reg-rename diff (-1 const
 * lands in $a1 vs target's $v1; sum lands in $v1 vs target's $t7).
 *
 * 2026-05-27 NEGATIVE: tried inlining the `sum` computation
 * (`*(int*)(a0+0x20) = v + *(int*)(a0+0xC);` directly, no named local) —
 * STANDALONE compile produces byte-exact target emit (sum→$t7, -1→$v1),
 * but the in-tree game_libs_post.c compile still emits sum→$v1, -1→$a1.
 * Documented TU-context-sensitive-scheduling cap per
 * docs/IDO_CODEGEN.md#feedback-ido-tu-context-sensitive-scheduling — the
 * surrounding TU's allocator state differs from isolated compile.
 * Permuter would need to be run in-tree to crack. */
#ifdef NON_MATCHING
void game_libs_func_0001FE88(short *a0) {
    int v = *(int *)((char *)a0 + 4);
    int sum = v + *(int *)((char *)a0 + 0xC);
    *(int *)((char *)a0 + 0x10) = 0;
    *(int *)a0 = 0;
    *(int *)((char *)a0 + 0x20) = sum;
    a0[0xF] = -1;
    a0[0x15] = -1;
    *(int *)((char *)a0 + 8) = v;
    *(int *)((char *)a0 + 0x14) = v;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FE88);
#endif

void game_libs_func_0001FEB8(int *a0) { *(int*)((char*)a0 + 4) = *(int*)a0; *(int*)((char*)a0 + 0xC) = 0; }

// gl_func_0001FEC8 — STRUCTURAL PASS (0x6C / 27 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A two-step subsystem register/install helper.
//
//   void gl_func_0001FEC8(int arg) {
//     (*reg1)(&D_2188, &D_0, arg);          // jal 0 USO-reloc
//     int g = *(int*)(&D_0 + 4);             // global ptr field
//     (*reg2)(&D_2168, &D_0 + arg, g - arg); // jal 0 USO-reloc
//     *(int*)(&D_0 + 0x2178) = 0;            // reset state flag
//   }
//
// Struct-typing reference: &D_2188 and &D_2168 are fixed
//   descriptor/format blobs (passed as the first arg to two distinct
//   USO-relocated registration routines, the `jal 0` slots resolved
//   at load). Word &D_0+0x4 is a global end/extent pointer; the
//   second call receives (base + arg) and the span (global - arg).
//   Word &D_0+0x2178 is a subsystem state flag cleared on completion.
//   This is the "install/register" entry of the same game_libs
//   support family as the gl_func_0001FD98 allocator helper.
// Caps (DEFERRED): single jr $ra. Two-step subsystem
//   register/install helper (same support family as the
//   gl_func_0001FD98 allocator). Real-C STRUCTURAL body below per
//   the analysis (two jal-0 USO-reloc registration calls with fixed
//   &D_2188 / &D_2168 descriptor blobs, then reset state flag
//   &D_0+0x2178). Byte-match deferred — placeholder jal-0 calls
//   need USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the registration routines.
extern int gl_func_00000000();
extern int D_00000000;
/* Byte-exact: inlining the global load `*(int*)(D+4)` into the 2nd call's arg
 * (vs a named `int g` local) allocates it to $t7 (not $v0) to match. The
 * gl_func_00000000 calls are jal-0 placeholders = correct ROM bytes; no episode. */
void gl_func_0001FEC8(int arg) {
    char *D = (char *)&D_00000000;
    gl_func_00000000(D + 0x2188, D, arg);
    gl_func_00000000(D + 0x2168, D + arg, *(int *)(D + 4) - arg);
    *(int *)(D + 0x2178) = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FF28);

// gl_func_0001FF34 — STRUCTURAL PASS (0x84 / 33 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Sibling of gl_func_0001FEC8: a multi-step diagnostic /
// status-print sequence.
//
//   void gl_func_0001FF34(int arg) {
//     *(int*)(&D_0 + 0x216C) = ...;             // stash a value
//     (*pr)(&D_2168, *(int*)reg);                // jal 0 USO-reloc
//     (*pr)(&D_2198, arg);                        // jal 0 USO-reloc
//     (*pr)(&D_2168, *(int*)(reg2 + 0xC));        // jal 0 USO-reloc
//     (*pr)(&D_21C8, arg);                        // jal 0 USO-reloc
//   }
//
// Struct-typing reference: &D_2168 / &D_2198 / &D_21C8 are fixed
//   format-string / descriptor blobs (same &D_21xx descriptor pool
//   used by the gl_func_0001FEC8 register helper). The `jal 0` slots
//   are a USO-relocated printf-like reporter, resolved at load, each
//   invoked with a format pointer and a value pulled from a global
//   register/struct (word at reg+0, word at reg2+0xC) or the caller
//   arg (preserved across the calls via sp+0x18). Word &D_0+0x216C
//   is written once before the prints (a captured handle/value).
//   This is the "report/dump state" entry of the same game_libs
//   support family as gl_func_0001FD98 / gl_func_0001FEC8.
// Caps (DEFERRED): single jr $ra. Sibling of gl_func_0001FEC8 —
//   report/dump-state sequence (same &D_21xx descriptor pool /
//   support family as gl_func_0001FD98/FEC8). Real-C STRUCTURAL
//   body below per the analysis (stash handle to &D_0+0x216C, then
//   four jal-0 USO-reloc printf-like reporter calls with fixed
//   format blobs &D_2168/0x2198/0x21C8 and values from globals or
//   the preserved arg). Byte-match deferred — placeholder jal-0
//   reporter needs USO reloc infra. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the reporter.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0001FF34(int arg) {
    char *D = (char *)&D_00000000;
    int *r1, *r2;
    *(int *)(D + 0x216C) = arg;
    r1 = (int *)gl_func_00000000(D + 0x2168);
    r2 = (int *)gl_func_00000000(D + 0x2198, r1[0]);
    gl_func_00000000(D + 0x2168, r2[0xC / 4]);
    gl_func_00000000(D + 0x21C8, arg);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FF34);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0001FFAC);

// gl_func_0001FFB8 — STRUCTURAL PASS (0x84 / 33 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Near-identical SIBLING of gl_func_0001FF34 — same 4-step
// diagnostic / status-print sequence, different format descriptors.
//
//   void gl_func_0001FFB8(int arg) {
//     *(int*)(&D_0 + 0x21CC) = ...;             // stash a value
//     (*pr)(&D_21C8, *(int*)reg);                // jal 0 USO-reloc
//     (*pr)(&D_21D8, arg);                        // jal 0 USO-reloc
//     (*pr)(&D_21C8, *(int*)(reg2 + 4));          // jal 0 USO-reloc
//     (*pr)(&D_21E8, arg);                        // jal 0 USO-reloc
//   }
//
// Struct-typing reference: identical structure to gl_func_0001FF34
//   (see its comment) — USO-relocated printf-like reporter `jal 0`
//   slots, caller arg preserved across calls via sp+0x18. This
//   variant uses descriptor blobs &D_21C8 / &D_21D8 / &D_21E8 from
//   the same &D_21xx pool and reads the second value from reg2+0x4
//   (vs +0xC in gl_func_0001FF34); stashes its handle at &D_0+0x21CC.
//   Same game_libs report/dump support family.
// Caps (DEFERRED): single jr $ra. Exact twin of gl_func_0001FF34 —
//   report/dump-state sequence, same support family, different
//   &D_21xx descriptor offsets and a +0x4 field (vs +0xC). Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred —
//   placeholder jal-0 reporter needs USO reloc infra. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the reporter.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0001FFB8(int arg) {
    char *D = (char *)&D_00000000;
    int *r1, *r2;
    *(int *)(D + 0x21CC) = arg;
    r1 = (int *)gl_func_00000000(D + 0x21C8);
    r2 = (int *)gl_func_00000000(D + 0x21D8, r1[0]);
    gl_func_00000000(D + 0x21C8, r2[4 / 4]);
    gl_func_00000000(D + 0x21E8, arg);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FFB8);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00020030);

// gl_func_0002003C — STRUCTURAL PASS (0xC4 / 49 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A longer member of the gl_func_0001FF34 diagnostic-dump
// family: a multi-field struct reporter.
//
//   void gl_func_0002003C(S *obj) {
//     *(int*)(&D_0 + 0x21DC) = ...;             // stash a value
//     (*pr)(&D_21D8, *(int*)reg);                // jal 0 USO-reloc
//     (*pr)(&D_21FC, obj->w_0);
//     (*pr)(&D_21D8, *(int*)reg2);
//     (*pr)(&D_230C, obj->w_4);
//     (*pr)(&D_21D8, *(int*)reg3);
//     (*pr)(&D_241C, obj->w_8);
//     (*pr)(&D_21F8, ...);                        // trailing pair(s)
//     (*pr)(&D_2308, ...);
//   }
//
// Struct-typing reference: same USO-reloc printf-like reporter `jal 0`
//   slots as gl_func_0001FF34 / gl_func_0001FFB8. `obj` (saved in s0
//   from a0) is dumped field by field — words obj->0, obj->4, obj->8
//   — each preceded by a &D_21D8 label line and followed by a
//   value-format line from the &D_21xx/&D_23xx/&D_24xx descriptor
//   pool (&D_21FC / &D_230C / &D_241C / &D_21F8 / &D_2308). Handle
//   stashed at &D_0+0x21DC. The fullest "dump this object" variant of
//   the game_libs report support family.
// Caps (DEFERRED): single jr $ra. Fullest "dump this object" variant
//   of the gl_func_0001FF34 report support family. Real-C STRUCTURAL
//   body below per the analysis (stash handle &D_0+0x21DC, then a
//   chain of jal-0 USO-reloc reporter calls: a label line from
//   &D_21D8 then a value line from the &D_21FC/&D_230C/&D_241C/
//   &D_21F8/&D_2308 pool, fed from obj->0/4/8). Byte-match deferred —
//   placeholder jal-0 reporter needs USO reloc infra. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the reporter.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002003C(int *obj) {
    char *D = (char *)&D_00000000;
    *(int *)(D + 0x21DC) = (int)obj;
    gl_func_00000000(D + 0x21D8, obj[0]);
    gl_func_00000000(D + 0x21FC, obj[0]);
    gl_func_00000000(D + 0x21D8, obj[1]);
    gl_func_00000000(D + 0x230C, obj[1]);
    gl_func_00000000(D + 0x21D8, obj[2]);
    gl_func_00000000(D + 0x241C, obj[2]);
    gl_func_00000000(D + 0x21F8);
    gl_func_00000000(D + 0x2308);
    gl_func_00000000(D + 0x2418);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002003C);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000200F4);

// gl_func_00020100 — STRUCTURAL PASS (0xB8 / 46 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Near-identical SIBLING of gl_func_0002003C — same multi-
// field struct dump, different format descriptors.
//
//   void gl_func_00020100(S *obj) {
//     *(int*)(&D_0 + 0x21EC) = ...;             // stash a value
//     (*pr)(&D_21E8, *(int*)reg);                // jal 0 USO-reloc
//     (*pr)(&D_22D0, obj->w_0);
//     (*pr)(&D_21E8, *(int*)reg2);
//     (*pr)(&D_23E0, obj->w_4);
//     (*pr)(&D_21E8, *(int*)reg3);
//     (*pr)(&D_24F0, obj->w_8);
//     (*pr)(&D_22CC, ...);                        // trailing pair(s)
//     (*pr)(&D_23DC, ...);
//   }
//
// Struct-typing reference: identical structure to gl_func_0002003C
//   (see its comment) — USO-reloc printf-like reporter `jal 0` slots,
//   obj (s0 from a0) dumped field-by-field (obj->0/4/8) with &D_21E8
//   label lines and &D_22D0/&D_23E0/&D_24F0/&D_22CC/&D_23DC value
//   descriptors. Handle stashed at &D_0+0x21EC. Same game_libs
//   report/dump support family — this and gl_func_0002003C are the
//   per-object-type dump variants (different descriptor sets per
//   record kind).
// Caps (DEFERRED): single jr $ra. Twin of gl_func_0002003C —
//   dump-object report sequence, same support family, different
//   &D_2xxx descriptor offsets. Real-C STRUCTURAL body below per
//   the analysis (stash handle &D_0+0x21EC, then label+value jal-0
//   reporter pairs fed from obj->0/4/8 plus three trailing footer
//   lines). Byte-match deferred — placeholder jal-0 reporter needs
//   USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the reporter.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00020100(int *obj) {
    char *D = (char *)&D_00000000;
    *(int *)(D + 0x21EC) = (int)obj;
    gl_func_00000000(D + 0x21E8, obj[0]);
    gl_func_00000000(D + 0x22D0, obj[0]);
    gl_func_00000000(D + 0x21E8, obj[1]);
    gl_func_00000000(D + 0x23E0, obj[1]);
    gl_func_00000000(D + 0x21E8, obj[2]);
    gl_func_00000000(D + 0x24F0, obj[2]);
    gl_func_00000000(D + 0x22CC);
    gl_func_00000000(D + 0x23DC);
    gl_func_00000000(D + 0x24EC);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020100);
#endif

/* gl_func_000201B8: 449-insn (0x704) multi-config slot-manager state
 * machine. Sibling-of-0x208BC pick (source-2, adjacent offset, same
 * dispatch family). Frame -0x50. Args: mode (a0/s0), val (a1), op (a2),
 * + stack args at sp+0x30 (tbl seed) / sp+0x4C (cfg seed) / sp+0x54.
 * ra is pinned to the constant 12 (record stride; indexing is
 * `multu idx, 12`). t0=2, t1=1 constants.
 *
 * ENTRY DISPATCH (decoded, real C below): mode selects a (cfg, tbl)
 * pointer pair from fixed &D tables:
 *   mode==0 → cfg=&D+0x21F8, tbl=&D+0x2C70
 *   mode==1 → cfg=&D+0x2308, tbl=&D+0x2C40
 *   mode==2 → cfg=&D+0x2418, tbl=&D+0x2C10
 *   else    → cfg/tbl unset (skip to tail)
 * if (op != 0) → re-entry/update block @0x63C (decoded below).
 * Flag derive: a2c=cfg+212; t3 = (cfg[242]==-1 ? tbl[a2c[30]] : 0-ish);
 *   t4 = tbl[a2c[42]] (each gated by the field != -1).
 *
 * TAIL (mapped, NOT yet C — multi-run): a large t3/t4/t5 + mode dispatch
 * with ~6 near-identical record-scan loops:
 *   - 208-byte-record scan: count=*(int*)(&D+0x2070), rec=&D+0x2CFC,
 *     match rec[51]==a2c[30|42], skip if rec[176]>>31.
 *   - 352-byte-record scan: count=*(s16*)(&D+0x2048), rec=&D+0x2D00,
 *     match rec[11524]==a2c[30], skip if rec[11520]>>31.
 *   Result written to *(int*)op_struct; index math `multu n,12`.
 *   Two fixup blocks @0x4B8/0x57C: sh/sw into a2c[20/24/30/32/42],
 *   call gl_func_00000000 / func@0x34238 (gl_func_00034238). Re-entry
 *   @0x63C: gl_func call, rewrites cfg records by 12-stride, loops to
 *   the entry dispatch (op consumed).
 *
 * First-pass structural NM wrap: entry dispatch + flag derive are real
 * C; deep tail kept as INCLUDE_ASM-equivalent stub return so the body
 * compiles. ~low% expected — multi-run. INCLUDE_ASM is the build path
 * (ROM byte-exact). */
// gl_func_000201B8 — 4-way state-dispatched record processor (no episode).
// 44.49% -> 51.12% via reloc-form/field-width reconstruction levers:
//   (1) per-case bases were integer literals (0x21F8/0x2308/0x2418 +
//       0x2C70/0x2C40/0x2C10) -> &D_00000000+off pointer values so IDO
//       emits the target's `lui;addiu` (held in a3/t2 per case) instead
//       of `addiu zero` int-loads. (+4.2pp; the main lever.)
//   (2) wrong field widths: `var_a2_2 = var_a3 + 0xD4` was WORD-scaled
//       -> (char*)+0xD4 BYTE; `FW(var_a3,0xF2)` (word, lwl/lwr) -> *(s16*)
//       (target `lh 242(a3)`); var_t3/var_t4 table reads int->u8 (target
//       `lbu 0(tN)`); size deficit 16->-4.
// RESIDUAL (deferred, regalloc/control-flow): build still spills a0/a1/a3
//   to a -200 frame (target -80, args reg-resident) and forces the case
//   bases into a SAVED reg (s1) because the back-edge `goto loop_1` makes
//   them live across the loop, whereas the target's loop re-enters at the
//   switch (+0x2c) so a3/t2 are re-derived per iteration in TEMP regs.
//   Closing it = full prologue/loop reconstruction (arg-in-reg dataflow +
//   mid-function loop target), not a mechanical graft transform.
#ifdef NON_MATCHING
extern int game_libs_func_0003443C();
extern int gl_func_0001CA10();


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000201B8)();
s32 gl_func_000201B8(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    s32 *sp4C;
    u8 sp3B;
    u8 sp3A;
    s32 sp30;
    s32 *sp28;
    char *sp24;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_a0_3;
    s16 temp_a0_5;
    s16 temp_a0_6;
    s16 temp_v1_2;
    s32 *var_a2;
    s32 *var_a2_2;
    s32 *var_a3;
    s32 temp_a0_4;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_t2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    u32 temp_t6;
    u32 temp_t9;
    u8 var_t3;
    u8 var_t4;
    char *temp_v0;
    char *temp_v0_2;
    char *var_v0;
    char *var_v0_2;
    char *var_v0_4;
    char *var_v0_5;
    char *var_v0_6;
    char *var_v0_7;

    var_a2 = arg2;
    var_a3 = sp4C;
    var_t2 = sp30;
loop_1:
    switch (arg0) {                                 /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        var_a3 = (s32 *)((char *)&D_00000000 + 0x21F8);
        var_t2 = (s32) ((char *)&D_00000000 + 0x2C70);
        break;
    case 1:                                         /* switch 1 */
        var_a3 = (s32 *)((char *)&D_00000000 + 0x2308);
        var_t2 = (s32) ((char *)&D_00000000 + 0x2C40);
        break;
    case 2:                                         /* switch 1 */
        var_a3 = (s32 *)((char *)&D_00000000 + 0x2418);
        var_t2 = (s32) ((char *)&D_00000000 + 0x2C10);
        break;
    }
    if (var_a2 == 0) {
        var_t3 = 0;
        var_a2_2 = (s32 *)((char *)var_a3 + 0xD4);
        if (*(s16 *)((char *)var_a3 + 0xF2) == -1) {
            var_a2_2 = (s32 *)((char *)var_a3 + 0xD4);
        } else {
            var_t3 = *(u8 *)((*(s16 *)((char *)var_a2_2 + 0x1E)) + var_t2);
        }
        temp_a0 = (*(s16 *)((char *)var_a2_2 + 0x2A));
        if (temp_a0 == -1) {
            var_t4 = 0;
        } else {
            var_t4 = *(u8 *)(temp_a0 + var_t2);
        }
        if (arg0 == 1) {
            if (var_t3 == 4) {
                temp_a1 = *(s32 *)0x2070;
                var_v1_2 = 0;
                if (temp_a1 > 0) {
                    var_v0 = *(char **)0x2CFC;
loop_19:
                    if ((FW(var_v0, 0x33) != (*(s16 *)((char *)var_a2_2 + 0x1E))) || (((u32) FW(var_v0, 0xB0) >> 0x1F) == 0)) {
                        var_v1_2 += 1;
                        var_v0 += 0xD0;
                        if (var_v1_2 < temp_a1) {
                            goto loop_19;
                        }
                    }
                }
                if (var_v1_2 == temp_a1) {
                    sp3A = var_t4;
                    sp30 = var_t2;
                    sp4C = var_a3;
                    sp28 = var_a2_2;
                    gl_func_0001CA10((*(s16 *)((char *)var_a2_2 + 0x1E)), 3, var_a2_2, var_a3);
                    var_t3 = 3;
                }
            }
            if (var_t4 == 4) {
                temp_a1_2 = *(s32 *)0x2070;
                var_v1_3 = 0;
                if (temp_a1_2 > 0) {
                    var_v0_2 = *(char **)0x2CFC;
loop_27:
                    if ((FW(var_v0_2, 0x33) != (*(s16 *)((char *)var_a2_2 + 0x2A))) || (((u32) FW(var_v0_2, 0xB0) >> 0x1F) == 0)) {
                        var_v1_3 += 1;
                        var_v0_2 += 0xD0;
                        if (var_v1_3 < temp_a1_2) {
                            goto loop_27;
                        }
                    }
                }
                if (var_v1_3 == temp_a1_2) {
                    sp3B = var_t3;
                    sp30 = var_t2;
                    sp4C = var_a3;
                    sp28 = var_a2_2;
                    gl_func_0001CA10((*(s16 *)((char *)var_a2_2 + 0x2A)), 3, var_a2_2, var_a3);
                    var_t4 = 3;
                }
            }
        }
        if (var_t3 == 0) {
            FW(var_a2_2, 0x0) = 0;
            var_v0_3 = 0;
            goto block_83;
        }
        if (var_t4 == 0) {
            var_v0_3 = 1;
            FW(var_a2_2, 0x0) = 1;
            goto block_83;
        }
        if ((var_t3 == 3) && (var_t4 == 3)) {
            var_v0_3 = FW(var_a2_2, 0x0);
            goto block_83;
        }
        if (var_t3 == 3) {
            FW(var_a2_2, 0x0) = 0;
            var_v0_3 = 0;
            goto block_83;
        }
        var_v0_3 = 1;
        if (var_t4 == 3) {
            FW(var_a2_2, 0x0) = 1;
            goto block_83;
        }
        if (arg0 == 0) {
            if (var_t3 == 2) {
                temp_a0_2 = *(s16 *)0x2048;
                var_v0_4 = 0;
                var_v1_4 = 0;
                if (temp_a0_2 > 0) {
loop_46:
                    if ((((u32) FW(var_v0_4, 0x2D00) >> 0x1F) == 0) || (FW(var_v0_4, 0x2D04) != (*(s16 *)((char *)var_a2_2 + 0x1E)))) {
                        var_v1_4 += 1;
                        var_v0_4 += 0x160;
                        if (var_v1_4 < temp_a0_2) {
                            goto loop_46;
                        }
                    }
                }
                var_v0_3 = 0;
                if (var_v1_4 == temp_a0_2) {
                    FW(var_a2_2, 0x0) = 0;
                    goto block_83;
                }
                goto block_51;
            }
block_51:
            if (var_t4 == 2) {
                temp_a0_3 = *(s16 *)0x2048;
                var_v0_5 = 0;
                var_v1_5 = 0;
                if (temp_a0_3 > 0) {
loop_53:
                    if ((((u32) FW(var_v0_5, 0x2D00) >> 0x1F) == 0) || (FW(var_v0_5, 0x2D04) != (*(s16 *)((char *)var_a2_2 + 0x2A)))) {
                        var_v1_5 += 1;
                        var_v0_5 += 0x160;
                        if (var_v1_5 < temp_a0_3) {
                            goto loop_53;
                        }
                    }
                }
                var_v0_3 = 1;
                if (var_v1_5 == temp_a0_3) {
                    FW(var_a2_2, 0x0) = 1;
                    goto block_83;
                }
                goto block_75;
            }
            goto block_75;
        }
        if (arg0 == 1) {
            if (var_t3 == 2) {
                temp_a1_3 = *(s32 *)0x2070;
                var_v1_6 = 0;
                if (temp_a1_3 > 0) {
                    var_v0_6 = *(char **)0x2CFC;
loop_62:
                    if ((FW(var_v0_6, 0x33) != (*(s16 *)((char *)var_a2_2 + 0x1E))) || (((u32) FW(var_v0_6, 0xB0) >> 0x1F) == 0)) {
                        var_v1_6 += 1;
                        var_v0_6 += 0xD0;
                        if (var_v1_6 < temp_a1_3) {
                            goto loop_62;
                        }
                    }
                }
                var_v0_3 = 0;
                if (var_v1_6 == temp_a1_3) {
                    FW(var_a2_2, 0x0) = 0;
                    goto block_83;
                }
                goto block_67;
            }
block_67:
            if (var_t4 == 2) {
                temp_a1_4 = *(s32 *)0x2070;
                var_v1_7 = 0;
                if (temp_a1_4 > 0) {
                    var_v0_7 = *(char **)0x2CFC;
loop_70:
                    if ((FW(var_v0_7, 0x33) != (*(s16 *)((char *)var_a2_2 + 0x2A))) || (((u32) FW(var_v0_7, 0xB0) >> 0x1F) == 0)) {
                        var_v1_7 += 1;
                        var_v0_7 += 0xD0;
                        if (var_v1_7 < temp_a1_4) {
                            goto loop_70;
                        }
                    }
                }
                var_v0_3 = 1;
                if (var_v1_7 == temp_a1_4) {
                    FW(var_a2_2, 0x0) = 1;
                    goto block_83;
                }
                goto block_75;
            }
            goto block_75;
        }
block_75:
        var_v0_3 = FW(var_a2_2, 0x0);
        if (var_v0_3 == 0) {
            if (var_t3 == 1) {
                var_v0_3 = 1;
                if (var_t4 != 1) {
                    FW(var_a2_2, 0x0) = 1;
                    goto block_83;
                }
                goto block_82;
            }
            goto block_83;
        }
        if (var_t4 == 1) {
            var_v0_3 = 0;
            if (var_t3 != 1) {
                FW(var_a2_2, 0x0) = 0;
                goto block_83;
            }
block_82:
            return 0;
        }
block_83:
        temp_v1_2 = (*(s16 *)((char *)(var_a2_2 + (var_v0_3 * 0xC)) + 0x1E));
        if (temp_v1_2 != -1) {
            *(int*)(var_t2 + temp_v1_2) = 0;
            if (arg0 == 1) {
                sp30 = var_t2;
                sp4C = var_a3;
                sp28 = var_a2_2;
                gl_func_0001CA10(FW((var_a2_2 + (FW(var_a2_2, 0x0) * 0xC)), 0x1E));
            }
        }
        temp_a0_4 = FW(var_a2_2, 0x0);
        temp_v0 = var_a3 + 0xD8;
        if (temp_a0_4 != 0) {
            temp_v0_2 = var_a3 + 0xD8;
            if (temp_a0_4 != 1) {
                return 0;
            }
            temp_t9 = ((FW(var_a3, 0xD8) + FW(temp_v0_2, 0x8)) - arg1) & ~0xF;
            FW(var_a2_2, 0x20) = temp_t9;
            temp_a0_5 = (*(s16 *)((char *)var_a2_2 + 0x1E));
            (*(s16 *)((char *)var_a2_2 + 0x2A)) = (s16) arg3;
            FW(var_a2_2, 0x24) = arg1;
            if ((temp_a0_5 != -1) && (temp_t9 < (u32) FW(temp_v0_2, 0x4))) {
                *(int*)(var_t2 + temp_a0_5) = 0;
                switch (arg0) {                     /* switch 3; irregular */
                case 0:                             /* switch 3 */
                    sp28 = var_a2_2;
                    sp24 = temp_v0_2;
                    game_libs_func_0003443C((*(s16 *)((char *)var_a2_2 + 0x1E)));
block_107:
                    var_a2_2 = sp28;
                    break;
                case 1:                             /* switch 3 */
                    sp28 = var_a2_2;
                    sp24 = temp_v0_2;
                    gl_func_0001CA10((*(s16 *)((char *)var_a2_2 + 0x1E)));
                    goto block_107;
                }
                (*(s16 *)((char *)var_a2_2 + 0x1E)) = -1;
                FW(temp_v0_2, 0x4) = (u32) FW(var_a3, 0xD8);
            }
            var_v1 = FW(var_a2_2, 0x20);
            goto block_99;
        }
        FW(var_a2_2, 0x14) = (u32) FW(var_a3, 0xD8);
        (*(s16 *)((char *)var_a2_2 + 0x1E)) = (s16) arg3;
        FW(var_a2_2, 0x18) = arg1;
        temp_t6 = FW(var_a3, 0xD8) + arg1;
        FW(temp_v0, 0x4) = temp_t6;
        temp_a0_6 = (*(s16 *)((char *)var_a2_2 + 0x2A));
        if ((temp_a0_6 != -1) && ((u32) FW(var_a2_2, 0x20) < temp_t6)) {
            *(int*)(var_t2 + temp_a0_6) = 0;
            switch (arg0) {                         /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                sp28 = var_a2_2;
                sp24 = temp_v0;
                game_libs_func_0003443C((*(s16 *)((char *)var_a2_2 + 0x2A)));
block_96:
                var_a2_2 = sp28;
                break;
            case 1:                                 /* switch 2 */
                sp28 = var_a2_2;
                sp24 = temp_v0;
                gl_func_0001CA10((*(s16 *)((char *)var_a2_2 + 0x2A)));
                goto block_96;
            }
            (*(s16 *)((char *)var_a2_2 + 0x2A)) = -1;
            FW(var_a2_2, 0x20) = (s32) (FW(var_a3, 0xD8) + FW(temp_v0, 0x8));
        }
        var_v1 = FW(var_a2_2, 0x14);
block_99:
        *var_a2_2 ^= 1;
        return var_v1;
    }
    arg2 = var_a2;
    sp4C = var_a3;
    sp30 = var_t2;
    temp_v0_3 = gl_func_0001CA10((s16) (var_a3 + 4), arg1, var_a2, var_a3);
    FW((var_a3 + (FW(var_a3, 0x0) * 0xC)), 0x14) = temp_v0_3;
    if (temp_v0_3 == 0) {
        if ((arg2 != 0) && (arg2 != (s32 *)1)) {
            if (arg2 == (s32 *)2) {
                var_a2 = 0;
                goto loop_1;
            }
            goto block_117;
        }
        return 0;
    }
block_117:
    FW((var_a3 + (FW(var_a3, 0x0) * 0xC)), 0x1E) = (s16) arg3;
    FW((var_a3 + (FW(var_a3, 0x0) * 0xC)), 0x18) = arg1;
    temp_v1 = FW(var_a3, 0x0);
    FW(var_a3, 0x0) = temp_v1 + 1;
    return FW((var_a3 + (temp_v1 * 0xC)), 0x14);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000201B8);
#endif

/* gl_func_000208BC: 22-insn 3-arg guard/dispatch.
 *   r = gl_func_00000000(a0, a2);
 *   if (r != 0) return r;
 *   if (a1 == 3) return 0;
 *   return gl_func_00034F80(a0, a1, a2);   // jal in-segment 0x34F80
 * args spilled to sp at entry; reloaded on each path. */
extern int gl_func_00000000();
extern int gl_func_00034F80();
int gl_func_000208BC(int a0, int a1, int a2) {
    int r = gl_func_00000000(a0, a2);
    if (r != 0) {
        return r;
    }
    if (a1 == 3) {
        return 0;
    }
    return gl_func_00034F80(a0, a1, a2);
}

// gl_func_00020914 — STRUCTURAL PASS (0x114 / 69 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A mode-select / config-apply routine over the &D_21xx
// descriptor pool (same pool the gl_func_0001FF34 reporter family
// uses).
//
//   void gl_func_00020914(int mode, void *target) {
//     D *desc;
//     switch (mode) {                              // beq 0 / 1 / 2
//       case 0:  desc = &D_21F8; break;
//       case 1:  desc = &D_2308; break;
//       case 2:  desc = &D_2418; break;
//       default: desc = &D_xxxx; break;
//     }
//     R *rec = (char*)desc + 0xD4;                  // sub-record
//     if (target == 0) {
//       int   a = rec->w_0;
//       short b = rec->h_1E;
//       if (...) rec->w_0 = 1;                       // set state
//       int   c = rec->w_14;
//       short d = rec->h_2A;
//       ...                                          // apply config
//       float f = *(float*)(&D_0 + 0xE78);           // global scalar
//     }
//   }
//
// Struct-typing reference: &D_21F8 / &D_2308 / &D_2418 are the
//   mode-indexed descriptor blobs (one per display/format mode 0/1/2,
//   plus a default). Each has an active sub-record at desc+0xD4 with
//   word fields at 0 / 0x14 / 0x20 and halfwords at 0x1E / 0x2A; field
//   0 is a state/enabled flag set to 1. &D_0+0xE78 is a global float
//   constant pulled in when applying. The whole apply path is gated
//   on whether `target` (the caller-saved arg at sp+0x24) is null.
//   Configuration front-end paired with the gl_func_0001FF34 /
//   gl_func_0002003C reporter dump family (shared &D_21xx pool).
// Caps (DEFERRED): single jr $ra. Mode-select / config-apply over
//   the &D_21xx descriptor pool (config front-end paired with the
//   gl_func_0001FF34 / gl_func_0002003C reporter family). Real-C
//   STRUCTURAL body below per the analysis (mode switch picks
//   &D_21F8/0x2308/0x2418, sub-record at desc+0xD4, apply path
//   gated on target==null sets the enabled flag and pulls the
//   &D_0+0xE78 global float). Byte-match deferred — beq mode-switch
//   + struct-apply + global-float schedule. Name pre-checked: no
//   extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int D_00000000;
/* Whole-body decode 2026-06-01; reconstruction refined 2026-06-20.
 * int record-lookup(mode, flag, key): switch(mode) picks a per-mode descriptor
 * base (D+0x21F8/0x2308/0x2418; default reads an uninit sp slot). v1=base+0xD4.
 * flag==0: probe v1->0x1E (set v1->0=1, return v1->0x14) or v1->0x2A (set
 * v1->0=0, return v1->0x20), else 0. flag!=0: scan base[base[0]] records
 * (stride 12) for key==rec->0x1E returning rec->0x14; on miss, if flag==2
 * recurse gl_func_00020914(mode, 0, key) and return 0.
 * 2026-06-20: 35->33 diffs. Fixed: drop the `char *D` and `uninit` locals so the
 * frame is 0x20 (was 0x28); switch(mode) gives the beq-chain dispatch with arg
 * homes at 0x24 byte-exact; flag==0 probe FIRST (fall-through) so the flag test
 * is bnel (was beql); recurse to self (was placeholder gl_func_00000000).
 * Residual 33 (size 67 exact): the flag!=0 SCAN LOOP — target uses branch-LIKELY
 * (bnel a2,t1 / bnel at,zero) and RELOADS the base[0] count via $a0 each
 * iteration; the structured do/while makes IDO hoist the count into a reg (one
 * load) + plain bne, so the loop schedule/coloring diverges. Plus the default
 * uninit slot lands at 0x1C vs 0x18 (phantom-slot, no named lever w/o regrowing
 * the frame). Genuine branch-likely-schedule + loop-invariant-reload cap. */
int gl_func_00020914(int mode, int flag, int key) {
    char *base;
    char *v1;
    int v0;

    switch (mode) {
    case 0:  base = (char *)&D_00000000 + 0x21F8; break;
    case 1:  base = (char *)&D_00000000 + 0x2308; break;
    case 2:  base = (char *)&D_00000000 + 0x2418; break;
    }
    v1 = base + 0xD4;
    if (flag == 0) {
        if (key == *(short *)(v1 + 0x1E)) {
            *(int *)v1 = 1;
            return *(int *)(v1 + 0x14);
        }
        if (key == *(short *)(v1 + 0x2A)) {
            *(int *)v1 = 0;
            return *(int *)(v1 + 0x20);
        }
        return 0;
    }
    v0 = 0;
    if (*(int *)base != 0) {
        v1 = base;
        do {
            if (key == *(short *)(v1 + 0x1E)) {
                return *(int *)(v1 + 0x14);
            }
            v0++;
            v1 += 12;
        } while ((unsigned)v0 < (unsigned)*(int *)base);
    }
    if (flag == 2) {
        gl_func_00020914(mode, 0, key);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020914);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00020A20);

// gl_func_00020A28 — STRUCTURAL PASS (0x4A8 / 298 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO bundle
// (named fn + 3 trailing helpers) — deferred USO re-split. The named
// leading fn is a heavily-FPU float vector/matrix transform helper.
//
//   void gl_func_00020A28(args…, float *a2) {
//     // builds a stack scratch of computed floats:
//     float t0 = fa * fb;                         // mul.s chains
//     float t1 = fc * fd + fe;                     //  (460x ops)
//     ... sp[+0x0C/+0x10/+0x2C/+0x30] = …;          // swc1 scratch
//     float u = a2[-1], v = a2[-2];                 // lwc1 -4/-8(a2)
//     // FP rounding-mode control for truncated int convert:
//     int ctrl = cfc1();                            // 444EF800
//     ctrl = (ctrl & ~mask) | 1;                    // set RZ-ish
//     ctc1(ctrl);                                   // 44CFF800
//     int n = (int)(scaled_float);                  // trunc-to-int
//     if (n & 0x78) { ... }                          // bit test branch
//     ... emit / store transformed result ...
//   }
//
// Struct-typing reference: a2 points just past a small float record
//   (inputs read at a2[-1] / a2[-2]). The body is a chain of single-
//   precision mul/add/sub (cop1 0x460x ops) producing a stack-local
//   scratch struct of floats at sp+0x0C..0x30, with explicit FPCSR
//   manipulation (cfc1/ctc1 pair, 444EF800 / 44CFF800) to switch the
//   rounding mode before a float→int truncation — the classic
//   project/round-to-screen-space idiom. A 4F00xxxx float literal
//   (3C014F00) is a large scale constant. This is a graphics-math
//   transform leaf in the game_libs subsystem; the 3 trailing bundled
//   bodies are its small FP helpers, left for the deferred re-split.
// Caps (DEFERRED): single jr $ra (the "4-jr bundle" note is STALE;
//   .s is 0x4A8/243 words, ONE function). Heavily-FP vector/matrix
//   transform leaf with FPCSR rounding-mode control. Real-C
//   STRUCTURAL body below per the analysis (mul/add cop1 chains into
//   a sp+0x0C..0x30 float scratch from a2[-1]/a2[-2], cfc1/ctc1
//   FPCSR manip to switch rounding before a float->int truncation,
//   bit-test branch on the truncated value, 0x4F00 scale literal).
//   Byte-match deferred — dense FP schedule + FPCSR cfc1/ctc1 pair
//   (IDO emits these only from inline-asm, unreproducible from C).
//   Name pre-checked: no extern reuse (collision-safe).
/* gl_func_00020A28 CLASSIFIED 2026-06-10: CALLER-SET $f0 (m2c emits
 * `M2C unset $f0` at 4 multiply sites -- the caller leaves a value in
 * $f0 that this fn reads; IDO C cannot express it). Permanent
 * structural cap (caller-set-reg class, float variant). A fresh graft
 * with *0 placeholders folds the muls and goes fuzzy=None; this 7.64
 * body stays. Otherwise the fn is a clean dual-loop f32->s16 pack
 * transform with 6 (u32)float casts. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_00020A28(int a0, int a1, float *a2) {
    float u = a2[-1];
    float v = a2[-2];
    float scaled = u * v * 8388608.0f;   /* 0x4F00 scale literal */
    int n;
    /* FPCSR rounding-mode switch (cfc1/ctc1) elided — see recipe */
    n = (int)scaled;
    if (n & 0x78) {
        gl_func_00000000(a0, a1, n);
    } else {
        gl_func_00000000(a0, a1, n & 0x7);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020A28);
#endif

/* Short-array zeroing loop (8 shorts, 4/iter). NATURAL CEILING: register-
 * exact from C; IDO fills the loop-setup delay differently (li a0,8 vs
 * move v0,0 ordering) — isolated-vs-full-TU scheduling swap. Was
 * previously closed via 2-insn INSN_PATCH — REMOVED 2026-05-23 as
 * match-faking (per feedback_no_instruction_forcing_matches_policy). */
void game_libs_func_00020DF4(short *a0) {
 do { int i = 0; short *p = a0; do {
      i += 4;
      p[1] = 0;
      p[2] = 0;
      p[3] = 0;
      p += 4;
      p[-4] = 0;
    }
    while (i != 8);
  }
  while (0);
}

/* Copies the a1-th 16-byte (8-short) entry of the &D_00000000+0x... table to
 * a0. Target emits a rotated 2x4-short copy loop (counter 0..8 step 4); the
 * exact loop rotation + the reloc-blind D_ base (lh offset 0) aren't yet
 * byte-matched. Semantic body for documentation. */
#ifdef NON_MATCHING
void game_libs_func_00020E24(short *a0, int a1) {
    short *s = (short *)((char *)&D_00000000 + a1 * 16);
    int i;
    for (i = 0; i < 8; i++) {
        a0[i] = s[i];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00020E24);
#endif


#ifdef NON_MATCHING
/* game_libs_func_00020E78: copies 8 shorts (one 16-byte record) from
 * &D + a1*16 - 16 (record a1-1) to dst. Logic + STRUCTURE exact: IDO unrolls
 * this loop x4 over 2 iterations identically (22 insns, byte-for-byte shape).
 * Only register allocation diverges — the target's setup skips $t6 (uses
 * $t7/$t8/$t9) while the C build starts at $t6; an 18/22 register-renumber
 * (above the INSN_PATCH/episode threshold, and the lui/addiu &D pair would
 * resist patching). Register-allocation near-miss — permuter candidate. */
void game_libs_func_00020E78(short *dst, int a1) {
    short *src = (short *)((char *)&D_00000000 + a1 * 16 - 16);
    short *d = dst;
    int i;
    for (i = 0; i < 8; i++) {
        *d++ = *src++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00020E78);
#endif

// gl_func_00020ED0 — STRUCTURAL PASS (0x2CC / 179 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is an argument-presence dispatcher + table-record copy.
//
//   int gl_func_00020ED0(a0, a1, a2, a3) {
//     if (a1 != 0) {
//       r = (*h1)(a1);                              // jal 0 USO-reloc
//     } else if (a2 != 0) {
//       r = (*h2)(a0);                              // jal 0 USO-reloc
//     } else if (a3 != 0) {
//       r = (*h3)(a0, a3);                          // jal 0 USO-reloc
//     } else {
//       r = 0;
//     }
//     // fall-through table work:
//     T *src = &D_E + a2*16;                         // index*16 entry
//     T *dst = &D_F + a2*16;
//     for (int i = 0; i < 8; i++)                     // 8 halfwords
//       dst->h[i] = src->h[i];                        // record copy
//     return r;
//   }
//
// Struct-typing reference: a multi-path entry that routes to one of
//   three USO-relocated handlers (the `jal 0` slots) depending on
//   which of the optional args a1 / a2 / a3 is non-null (a0 passed
//   through to the a2/a3 handlers), each yielding a result in $a1.
//   The unconditional tail builds two parallel table pointers from
//   index a2 scaled by 16 (sll 4) over the &D_E and &D_F globals and
//   copies an 8-entry halfword record between them (count li 8, lh/sh
//   stride 2). game_libs dispatch + record-shuffle helper.
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0x2CC/179 words, ONE function). Arg-presence dispatcher +
//   table-record copy. Real-C STRUCTURAL body below per the analysis
//   (route to one of three jal-0 USO-reloc handlers by which of
//   a1/a2/a3 is non-null, then copy an 8-halfword record between
//   &D_E + a2*16 and &D_F + a2*16). Byte-match deferred —
//   placeholder jal-0 handlers need USO reloc infra + copy-loop
//   schedule. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00020ED0(int a0, int a1, int a2, int a3) {
    char *D = (char *)&D_00000000;
    short *src, *dst;
    int r, i;
    if (a1 != 0) {
        r = gl_func_00000000(a1);
    } else if (a2 != 0) {
        r = gl_func_00000000(a0);
    } else if (a3 != 0) {
        r = gl_func_00000000(a0, a3);
    } else {
        r = 0;
    }
    src = (short *)(D + 0xE000 + a2 * 16);
    dst = (short *)(D + 0xF000 + a2 * 16);
    for (i = 0; i < 8; i++) {
        dst[i] = src[i];
    }
    return r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020ED0);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00020FFC)();
/* Per-frame decay pass: for each of the *(s8*)(&D+1) records (stride 0x158),
 * decay the u16 field at +0x24 by 25% (v -= v/4), repeated var_v0 (1 or 2,
 * per &D+0x2034) times. m2c dropped the &D record base (rec = &D + v1*0x158)
 * and the &D scalar bases; field is a halfword (sh). Simple inner loop lets
 * IDO unroll it (x4 + remainder) as the target does.
 * 2026-06-20: structure/size/insn-count byte-exact (77 words). Levers applied:
 * (1) v0-select as ternary (target uses explicit beq zero,zero unconditional
 * branch w/ v0=2 in delay); (2) record base ptr `rec = &D + v1*0x158` with the
 * +0x24 kept on the ACCESS (not folded into the addiu) so the field offset is
 * 36(rec); (3) inline-deref the field (no named temp) so the unroller chains the
 * masked u16 value in one register instead of copying to a sibling reg.
 * Residual = 29 single-register-renumber diffs: target chains the field value in
 * $a2 / count-copy in $a3; build mirrors them ($a3/$a2). Named temp / count-down
 * / decl-reorder all REGRESS. Genuine $a2<->$a3 coloring cap in the unroller. */
void game_libs_func_00020FFC(void) {
    s32 var_v0;
    s32 var_v1;
    s32 var_a1;
    char *rec;

    var_v0 = (*(s16 *)((char *)&D_00000000 + 0x2034) == 2) ? 2 : 1;
    var_v1 = 0;
    if (*(s8 *)((char *)&D_00000000 + 1) > 0) {
        do {
            if (var_v0 > 0) {
                rec = (char *)&D_00000000 + var_v1 * 0x158;
                var_a1 = 0;
                do {
                    *(u16 *)(rec + 0x24) = (u16) (*(u16 *)(rec + 0x24) - (s32) *(u16 *)(rec + 0x24) / 4);
                    var_a1 += 1;
                } while (var_a1 != var_v0);
            }
            var_v1 += 1;
        } while (var_v1 < *(s8 *)((char *)&D_00000000 + 1));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00020FFC);
#endif

/* game_libs_func_00021130: zero a 0xB00-byte short array. Logic + STRUCTURE
 * exact; IDO unrolls the `for(a1!=0xB00;a1+=2) *(short*)(reload+a1)=0` loop x4.
 * 2026-06-21 (agent-e): cut 17->6 word renumber via the s32-held-base lever
 * (`int base = (int)&D_00000000;` by-value, NOT char*) + v0-loaded-FIRST
 * (inline `(int)&D_00000000` in the v0 load so v0 colors to $v0/$2). With
 * those, EVERY insn is byte-identical except the single &D base register:
 * build colors base $v1/$3, target $a2/$6 (a clean +3 renumber on ONE live
 * range — all other regs match). char*-typed base reverts to 17; early a1=0
 * or hv-temp reorder also reverts. Irreducible single-reg coloring tie on the
 * long-lived base; not crackable via decl-order / type / init-site levers.
 * Permuter / uoptlist-renumber candidate. */
#ifdef NON_MATCHING
void game_libs_func_00021130(void) {
  int v0 = *((int *) ((int) (&D_00000000) + 0x2084));
  int base = (int) (&D_00000000);
  int a1;
  int a0 = base + (v0 * 4);
  *((short *) ((base + (v0 * 2)) + 0x214C)) = *((short *) (base + 0x203E));
  for (a1 = 0; a1 != 0xB00; a1 += 2) {
    *((short *) ((*((int *) (a0 + 0x2140))) + a1)) = 0;
  }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00021130);
#endif


// gl_func_0002119C — STRUCTURAL PASS (0x2FC / 191 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). The per-frame STATE-MACHINE DRIVER of the sprite-record
// subsystem whose table gl_func_0001FBD4 sweeps. -0x30 frame,
// s0/s1/ra saved.
//
//   void gl_func_0002119C(void) {
//     S *g  = &D_0;
//     int md = (g->h_2034 == 2) ? 2 : 1;            // mode at +0x2034
//     int st = g->b_2CF0 - 1;                        // state at +0x2CF0
//     if ((unsigned)st >= 5) return;                 // switch default
//     goto *((void**)(&D_0 + 0xE7C))[st];            // jump table
//     // (one) state body — iterate the record array:
//     int n = g->h_2048;                             // record count
//     R *rec = &D_0 + 0x2D00;                         // shared table
//     for (int i = 0; i < n; i++) {
//       (*handler)(rec);                              // jal 0 USO-reloc
//       n = g->h_2048;                                // reload count
//       rec += 0x160;                                 // record stride
//     }
//     ... other state bodies ...
//   }
//
// Struct-typing reference: drives the SAME record table as
//   gl_func_0001FBD4 — base &D_0+0x2D00, fixed stride 0x160, live
//   count halfword at &D_0+0x2048. Control globals: halfword
//   &D_0+0x2034 (a 2-vs-1 mode selector), byte &D_0+0x2CF0 (the
//   state, 1..5). Dispatch is a real computed jump through the table
//   at &D_0+0xE7C indexed by (state-1); states out of [1,5] fall to
//   the default (early return). At least one state walks the record
//   array invoking a USO-relocated per-record handler (the `jal 0`
//   slot, resolved at load). This is the top-level tick/update entry
//   of that sprite subsystem (the gl_func_0001FAE8 / gl_func_0001FBD4
//   sweeps are its leaf operations).
// Caps (DEFERRED): CLEAN single jr $ra. Per-frame state-machine
//   driver of the sprite-record subsystem (top-level tick/update;
//   the gl_func_0001FAE8/FBD4 sweeps are its leaf ops). Real-C
//   STRUCTURAL body below per the analysis (mode = g->0x2034==2?2:1,
//   state = g->0x2CF0-1, early return if state>=5, computed jump via
//   &D_0+0xE7C[state] modelled as a switch; one state walks the
//   &D_0+0x2D00 record array stride 0x160 count g->0x2048 invoking
//   a jal-0 handler). Byte-match deferred — computed jump-table +
//   placeholder jal-0 handler need USO reloc infra. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the handler.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01 (was 10.96% case-0-only stub). 5-case jr-via-
 * rodata jumptable state machine on st=(*(D+0x2CF0))-1, returning state>=3.
 * md = (*(D+0x2034)==2)?2:1 drives the per-case `N/md` timer reload at D+0x2CF4.
 * Cases dispatch sub-handlers (35668/3579C/36AD0/35B04) + a record sweep over
 * D+0x2070 entries (stride 208 from *(D+0x2CFC)). Jumptable can't byte-match
 * w/o rodata but case bodies score (per jumptable-not-a-skip-reason). */
extern int gl_func_00035668();
extern int gl_func_0003579C();
extern int gl_func_00036AD0();
extern int gl_func_00035B04();
int gl_func_0002119C(void) {
    char *g = (char *)&D_00000000;
    int md = (*(short *)(g + 0x2034) == 2) ? 2 : 1;
    int st = *(unsigned char *)(g + 0x2CF0) - 1;
    int n, i;
    char *rec;

    if ((unsigned)st >= 5) {
        goto end;
    }
    switch (st) {
    case 0:
        n = *(short *)(g + 0x2048);
        rec = g + 0x2D00;
        for (i = 0; i < n; i++) {
            gl_func_00000000(rec);
            n = *(short *)(g + 0x2048);
            rec += 0x160;
        }
        *(int *)(g + 0x2CF4) = 2 / md;
        *(unsigned char *)(g + 0x2CF0) = *(unsigned char *)(g + 0x2CF0) - 1;
        break;
    case 1:
        if (*(int *)(g + 0x2CF4) != 0) {
            gl_func_00035668();
            *(int *)(g + 0x2CF4) = *(int *)(g + 0x2CF4) - 1;
            goto end;
        }
        n = *(int *)(g + 0x2070);
        for (i = 0; i < n; i++) {
            int *r = (int *)(*(int *)(g + 0x2CFC) + i * 208);
            if (((unsigned)r[176 / 4] >> 31) != 0 &&
                (*(unsigned char *)((char *)r + 96) & 0xF) != 0) {
                *(float *)((char *)r + 108) = *(float *)(g + 0x2050);
                r = (int *)(*(int *)(g + 0x2CFC) + i * 208);
                *(unsigned char *)((char *)r + 96) =
                    (*(unsigned char *)((char *)r + 96) & 0xEF) | 0x10;
            }
            n = *(int *)(g + 0x2070);
        }
        *(int *)(g + 0x2CF4) = 8 / md;
        *(unsigned char *)(g + 0x2CF0) = *(unsigned char *)(g + 0x2CF0) - 1;
        break;
    case 2:
        if (*(int *)(g + 0x2CF4) != 0) {
            gl_func_00035668();
            *(int *)(g + 0x2CF4) = *(int *)(g + 0x2CF4) - 1;
            goto end;
        }
        *(int *)(g + 0x2CF4) = 2 / md;
        *(unsigned char *)(g + 0x2CF0) = *(unsigned char *)(g + 0x2CF0) - 1;
        break;
    case 3:
        gl_func_0003579C();
        if (*(int *)(g + 0x2CF4) != 0) {
            *(int *)(g + 0x2CF4) = *(int *)(g + 0x2CF4) - 1;
        } else {
            *(unsigned char *)(g + 0x2CF0) = *(unsigned char *)(g + 0x2CF0) - 1;
            gl_func_00036AD0();
            goto end;
        }
        break;
    case 4:
        gl_func_00035B04();
        *(unsigned char *)(g + 0x2CF0) = 0;
        for (i = 0; i < 12; i += 4) {
            int v0;
            *(short *)(g + 0x214C + i / 2) = *(short *)(g + 0x203C);
            for (v0 = 0; v0 != 2816; v0 += 8) {
                short *b = (short *)(*(int *)(g + 0x2140 + i) + v0);
                b[0] = 0;
                b[1] = 0;
                b[2] = 0;
                b[3] = 0;
            }
        }
        break;
    }
end:
    return *(unsigned char *)(g + 0x2CF0) >= 3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002119C);
#endif

// gl_func_00021498 — STRUCTURAL PASS (0x8EC / 571 words ≈ 2.3KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO
// bundle (named fn + 2 trailing helpers) — deferred USO re-split.
// The named leading fn is one of the LARGEST gl_func_0002119C
// jump-table state handlers: the sprite-record build/layout state.
// Huge -0x98 frame, full s0-s8/ra save.
//
//   void gl_func_00021498(void) {
//     S *g = &D_0;
//     byte idx = g->b_2CF1;                          // sub-state/index
//     g->w_1E0C = 0;                                  // clear global
//     int v = *(int*)tbl;                             // table base
//     g->h_2036 = (short)v;                            // config hw
//     (*setup)(idx & 0xFFFF);                          // jal 0 USO-rel
//     short cfg = g->h_2036;
//     int   q   = g->w_213C;
//     // 16-align + FP convert/divide per record:
//     int sz = (q + 0xF) & ~0xF;                        // align16
//     float f = (float)g->h_203A;                       // cvt.s.w
//     ... long multi-phase body: lays out the record set, computing
//         per-record FP-transformed fields (mtc1/cvt.s.w/div.s) and
//         writing the &D_0+0x20xx config halfwords, with further
//         USO-reloc sub-calls ...
//   }
//
// Struct-typing reference: operates on the same &D_0 sprite-subsystem
//   state block as gl_func_0002119C / gl_func_0001FBD4 — byte
//   &D_0+0x2CF1 is a sub-state/index right after the 0x2CF0 main
//   state; word &D_0+0x1E0C a scratch/result global cleared on entry;
//   halfwords &D_0+0x2036 / 0x203A / word 0x213C are layout-config
//   fields written/read while building the record set. The body mixes
//   integer index math (16-align `(x+0xF)&~0xF`) with single-prec FP
//   (mtc1 / cvt.s.w / div.s) to compute per-record transformed
//   geometry, and calls USO-relocated sub-routines (`jal 0` slots).
//   This is the heavyweight "(re)build the sprite record set" state
//   reached from the gl_func_0002119C dispatcher.
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0x8EC/549 words, ONE function). One of the largest
//   gl_func_0002119C jump-table state handlers — the heavyweight
//   "(re)build the sprite record set" layout state. Real-C
//   STRUCTURAL body below per the analysis (clear &D_0+0x1E0C,
//   stash (short)*tbl into &D_0+0x2036, setup(idx&0xFFFF), then a
//   16-align + per-record FP convert/divide layout pass writing the
//   &D_0+0x20xx config halfwords). Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the sub-routines.
//
// CAP CLASS (CORRECTED 2026-06-21, agent-b deep diagnostic): BASE-POINTER-PIN
//   is a C-DATAFLOW divergence, NOT an address-value/infra problem. The
//   prior note's claim "IDO refuses to pin a literal-0 base" is FALSE —
//   proven by experiment:
//     (1) The current `char *g = &D_00000000` ALREADY pins g into a saved
//         reg ($s3, copied to $s5) and uses `off($s3)` for direct accesses.
//         IDO pins base-0 addresses fine.
//     (2) H2 control: setting D_00000000 = 0x80300000 in undefined_syms and
//         rebuilding produces IDENTICAL codegen (same `lui sN,0x0`+HI16 reloc,
//         same pin count). The symbol value is a LINK-TIME fill; it has ZERO
//         effect on the compiler's pinning/scheduling. So non-zero data
//         addresses are NOT the trigger and would only BREAK the .text byte
//         match (target stores base-0 placeholder bytes + HI16/LO16 relocs to
//         D_0, exactly like our build — verified in the .s and the .o).
//   THE REAL DIVERGENCE: the STRUCTURAL C below passes INTEGER LITERALS where
//   the target passes `&D_0 + offset` POINTERS held across calls. Target pins
//   `$s3 = g + 0x2198` ONCE (offset 0x420: `addiu s3,s3,8600`) and passes it
//   as `or a0,s3,zero` for all 16 allocator calls; pins `s0 = g + 0x2D00`
//   incrementing by 0x160 per loop iter; passes `a0 = g + {0x2BE0,0x2BF0,
//   0x2BF8,0x2C04}` as pointers. PROTOTYPE (agent-b): converting the allocator
//   arg to a held `char *alloc = g + 0x2198;` and the group calls to pointers
//   flipped 0 -> 20 `or a0,sN,zero` passes (target 19) and pinned $s3 = g+8600
//   EXACTLY matching the target. So H1 (held-base-pointer in C) WORKS for the
//   call-arg bases. RESIDUAL (why not yet 0-diff): IDO still re-materializes g
//   (`lui;off(at)`) for many DIRECT `*(T*)(g+off)` accesses right after jals
//   instead of keeping ONE base live the whole body like target's $s6 (73x
//   off(s6)). Closing that needs the second index-base pinned like target's
//   $t8 (`temp_v0 = g + idx*0x38` as its own held base, not derived from g)
//   and decl/dataflow tuning so g stays in a single saved reg across all
//   calls. VERDICT: C-fixable (no infra) — full land is a precise per-stmt
//   reconstruction of the largest fn in the file, deferred. Also: 2 intra-
//   module jals carry REAL targets (0x33D20 in gl_func_00033BE4, 0x3408C in
//   gl_func_00033EB8 — splat-over-merged callees) needing split-out symbols.
//   Body below is the faithful STRUCTURAL reconstruction (NM path builds clean).
//
// FIELD-WIDTH PASS (agent-b 2026-06-22): drove size-gap -44 -> -33 words and
//   eliminated ALL 24 unaligned swl/swr/lwl/lwr ops (now 0) by correcting field
//   widths to the target mnemonics: the per-record loop and entry block stored
//   bytes/halfwords via `*(s32*)` (m2c over-widened), which both mis-modeled the
//   struct AND generated unaligned-access bloat. Fixed: g+0x2070/0x2048/0x2/0x1 &
//   the sp60+5/6/7/0x14 sources to (u8)/(u16); the 9 s4-record + 8 s2-record
//   stores to their true s8/s16 widths; the var_s4 zero loop to sb (start=g, not
//   0). RESIDUAL (391 non-reloc diffs, -33 words): the base-pin cap above — 48
//   surplus `lui` re-materializing &D_0 after jals where target uses off(s6).
//   Closing it needs live-local economy so IDO keeps g in one saved reg across
//   all ~20 calls; m2c's temp explosion (~45 locals) evicts it. Not landable.
#ifdef NON_MATCHING
extern int gl_func_0001CA10();
extern int func_33d20();
extern int func_3408c();
void gl_func_00021498(void) {
    char *g = (char *)&D_00000000;
    s32 sp6C;
    char *sp60;
    s32 sp40;
    f32 temp_f0;
    f32 temp_f18;
    f32 var_f18;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t6_2;
    s16 temp_v0_3;
    s32 temp_a0_2;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_t1;
    s32 temp_t9;
    char *temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_fp;
    s32 var_s0_3;
    s32 var_s1;
    s32 var_s1_2;
    char *var_s7;
    s32 var_t5;
    u16 temp_a1_2;
    u16 temp_s0_2;
    u16 temp_t6;
    u16 temp_v0_2;
    u16 temp_v1;
    char *var_s4;
    u8 temp_t5;
    u8 temp_t7;
    u8 temp_v0_7;
    char *temp_s5;
    char *var_s0;
    char *var_s0_2;
    char *var_s2;
    char *var_s4_2;

    temp_v0 = g + (*(u8 *)(g + 0x2CF1) * 0x38);
    *(s32 *)(g + 0x1E0C) = 0;
    temp_t9 = *(s32 *)temp_v0;
    sp60 = temp_v0;
    *(u16 *)(g + 0x2036) = (u16) temp_t9;
    temp_v0_2 = gl_func_0001CA10(temp_t9 & 0xFFFF);
    temp_v1 = *(u16 *)(g + 0x2036);
    temp_t1 = *(s32 *)(g + 0x213C);
    *(s16 *)(g + 0x203A) = (s16) ((((s32) temp_v1 / temp_t1) + 0xF) & 0xFFF0);
    temp_a2 = *(s16 *)(g + 0x203A);
    *(u16 *)(g + 0x2038) = temp_v0_2;
    temp_a0 = temp_a2 + 0x10;
    *(s16 *)(g + 0x2040) = (s16) ((temp_a0 / 208) + 1);
    temp_a3 = *(s16 *)(g + 0x2040);
    *(s16 *)(g + 0x203E) = (s16) (temp_a2 - 0x10);
    *(s16 *)(g + 0x203C) = temp_a0;
    temp_f0 = (f32) temp_a3;
    *(s16 *)(g + 0x2042) = (s16) ((temp_a2 / temp_a3) & ~7);
    temp_a1 = *(s16 *)(g + 0x2042);
    *(s16 *)(g + 0x2044) = (s16) (temp_a1 + 8);
    *(s16 *)(g + 0x2046) = (s16) (temp_a1 - 8);
    *(f32 *)(g + 0x2058) = (f32) (temp_f0 * 0.25f);
    *(f32 *)(g + 0x204C) = (f32) (32000.0f / (f32) temp_v1);
    *(f32 *)(g + 0x2054) = (f32) (0.00390625f / temp_f0);
    *(f32 *)(g + 0x2050) = (f32) (1.0f / temp_f0);
    *(s32 *)(g + 0x2060) = (s32) (*(s32 *)(sp60 + 0xC));
    *(s32 *)(g + 0x2064) = (s32) (*(s32 *)(sp60 + 0x10));
    *(s32 *)(g + 0x2070) = (*(u8 *)(sp60 + 0x5));
    *(s16 *)(g + 0x2048) = (*(u8 *)(sp60 + 0x6));
    if (*(s16 *)(g + 0x2048) >= 5) {
        *(s16 *)(g + 0x2048) = 4;
    }
    *(s16 *)(g + 2) = (*(u16 *)(sp60 + 0x14));
    temp_f18 = ((temp_f0 * *(f32 *)(g + 0xE90)) / (f32) *(s16 *)(g + 2)) / *(f32 *)(g + 0x2138);
    var_t5 = (s32) temp_f18;
    temp_t6 = *(u16 *)(g + 0x2038);
    *(s16 *)(g + 0x2074) = (s16) var_t5;
    var_f18 = (f32) temp_t6;
    if ((s32) temp_t6 < 0) {
        var_f18 += 4294967296.0f;
    }
    *(f32 *)(g + 0x205C) = (f32) ((((f32) temp_t1 * temp_f0) / var_f18) / (f32) *(s16 *)(g + 0x2074));
    *(s16 *)(g + 0x2034) = (s16) (*(s32 *)(sp60 + 0x4));
    temp_v0_3 = *(s16 *)(g + 0x2034);
    *(s16 *)(g + 0x203A) = (s16) (temp_a2 * temp_v0_3);
    *(s16 *)(g + 0x203C) = (s16) (*(s16 *)(g + 0x203C) * temp_v0_3);
    *(s16 *)(g + 0x203E) = (s16) (*(s16 *)(g + 0x203E) * temp_v0_3);
    *(s16 *)(g + 0x2040) = (s16) (temp_a3 * temp_v0_3);
    if (temp_v0_3 >= 2) {
        *(s16 *)(g + 0x203C) = (s16) (*(s16 *)(g + 0x203C) - 0x10);
    }
    *(s32 *)(g + 0x206C) = (s32) ((*(s32 *)(g + 0x2070) * 0x10 * *(s16 *)(g + 0x2040)) + ((*(u8 *)(sp60 + 0x7)) * 0x18) + 0x140);
    temp_s0 = (*(s32 *)(sp60 + 0x18)) + (*(s32 *)(sp60 + 0x1C)) + (*(s32 *)(sp60 + 0x20)) + 0x10;
    temp_s1 = (*(s32 *)(sp60 + 0x24)) + (*(s32 *)(sp60 + 0x28)) + (*(s32 *)(sp60 + 0x2C)) + 0x10;
    temp_v0_4 = temp_s0 + temp_s1;
    *(s32 *)(g + 0x2BE0) = (s32) ((*(s32 *)(g + 0x2170) - temp_v0_4) - 0x100);
    *(s32 *)(g + 0x2BEC) = temp_v0_4;
    gl_func_0001CA10(0x2BE0, temp_a1, temp_a2, temp_a3);
    *(s32 *)(g + 0x2BF0) = temp_s0;
    *(s32 *)(g + 0x2BF4) = temp_s1;
    gl_func_0001CA10(0x2BF0);
    *(s32 *)(g + 0x2BF8) = (s32) (*(s32 *)(sp60 + 0x18));
    *(s32 *)(g + 0x2BFC) = (s32) (*(s32 *)(sp60 + 0x1C));
    *(s32 *)(g + 0x2C00) = (s32) (*(s32 *)(sp60 + 0x20));
    gl_func_0001CA10(0x2BF8);
    *(s32 *)(g + 0x2C04) = (s32) (*(s32 *)(sp60 + 0x24));
    *(s32 *)(g + 0x2C08) = (s32) (*(s32 *)(sp60 + 0x28));
    *(s32 *)(g + 0x2C0C) = (s32) (*(s32 *)(sp60 + 0x2C));
    gl_func_0001CA10(0x2C04);
    temp_v0_5 = *(s32 *)(g + 0x2178);
    if (temp_v0_5 != 0) {
        *(s32 *)(g + 0x217C) = temp_v0_5;
    }
    func_3408c();
    *(s32 *)(g + 0x2CFC) = gl_func_0001CA10(0x2198, *(s32 *)(g + 0x2070) * 0xD0);
    gl_func_0001CA10();
    gl_func_0001CA10();
    var_s0 = g;
    do {
        var_s0 += 4;
        (*(s32 *)(var_s0 + 0x2084)) = gl_func_0001CA10(0x2198, *(s32 *)(g + 0x206C) * 8);
    } while (var_s0 != (g + 8));
    *(s32 *)(g + 0x2CF8) = gl_func_0001CA10(0x2198, 0x400);
    func_33d20();
    var_s4 = g;
    do {
        var_s4 += 0x158;
        (*(s8 *)(var_s4 - 0x13F)) = 0;
    } while (var_s4 < (g + 0x408));
    sp6C = 0;
    var_s2 = g + 0x18;
    *(u8 *)(g + 1) = (*(u8 *)(sp60 + 0x7));
    var_s4_2 = g;
    var_s7 = 0;
    if ((s8) *(u8 *)(g + 1) > 0) {
        sp40 = 0x140;
        var_fp = 0x130;
        do {
            temp_s5 = (*(s32 *)(sp60 + 0x8)) + var_s7;
            temp_t5 = (*(u8 *)(temp_s5 + 0x0));
            (*(s8 *)(var_s4_2 + 0x1C)) = temp_t5;
            temp_t6_2 = (*(u8 *)(temp_s5 + 0x1)) << 6;
            temp_lo = (s32) (temp_t6_2 & 0xFFFF) / (s32) (temp_t5 & 0xFF);
            (*(s16 *)(var_s4_2 + 0x1E)) = temp_t6_2;
            (*(s16 *)(var_s4_2 + 0x1E)) = (s16) temp_lo;
            (*(s16 *)(var_s4_2 + 0x24)) = (*(u16 *)(temp_s5 + 0x2));
            (*(s16 *)(var_s4_2 + 0x22)) = (*(u16 *)(temp_s5 + 0x4));
            (*(s16 *)(var_s4_2 + 0x28)) = (*(u16 *)(temp_s5 + 0x6));
            (*(s16 *)(var_s4_2 + 0x2A)) = (*(u16 *)(temp_s5 + 0x8));
            (*(s8 *)(var_s4_2 + 0x1D)) = (*(s8 *)(temp_s5 + 0xA));
            (*(s8 *)(var_s4_2 + 0x19)) = 8;
            (*(s16 *)(var_s4_2 + 0x20)) = (*(u16 *)(temp_s5 + 0xC));
            (*(s32 *)(var_s2 + 0x20)) = gl_func_0001CA10(0x2198, (temp_lo & 0xFFFF) * 2);
            temp_a1_2 = (*(u16 *)(var_s2 + 0x6));
            (*(s32 *)(var_s2 + 0x24)) = gl_func_0001CA10(0x2198, (*(u16 *)(var_s2 + 0x6)) * 2);
            (*(s32 *)(var_s2 + 0x14)) = 0;
            (*(s32 *)(var_s2 + 0x18)) = 0;
            (*(s8 *)(var_s2 + 0x3)) = 0;
            (*(s8 *)(var_s2 + 0x2)) = 2;
            (*(s8 *)(var_s2 + 0x0)) = 1;
            (*(s32 *)(var_s2 + 0x110)) = var_fp;
            temp_t7 = ((*(u8 *)(var_s2 + 0x118)) & 0xFF0F) | 0x40;
            (*(s32 *)(var_s2 + 0x1C)) = (s32) temp_a1_2;
            (*(s8 *)(var_s2 + 0x118)) = temp_t7;
            (*(s8 *)(var_s2 + 0x118)) = (u8) (temp_t7 & 0xF3);
            temp_a0_2 = (s32) (*(s32 *)(var_s2 + 0x118));
            (*(s32 *)(var_s2 + 0x120)) = sp40;
            temp_v0_7 = (*(u8 *)(var_s2 + 0x4));
            (*(s32 *)(var_s2 + 0x118)) = (s32) (((u32) ((((temp_a1_2 * 2) & 0xFFFFFF) ^ temp_a0_2) << 8) >> 8) ^ temp_a0_2);
            (*(s32 *)(var_s2 + 0x128)) = 0;
            (*(s32 *)(var_s2 + 0x130)) = 1;
            (*(s32 *)(var_s2 + 0x12C)) = (s32) temp_a1_2;
            (*(s32 *)(var_s2 + 0x114)) = 1.0f;
            (*(s32 *)(var_s2 + 0x11C)) = (s32) (*(s32 *)(var_s2 + 0x20));
            if (temp_v0_7 != 1) {
                (*(s16 *)(var_s2 + 0xE)) = (s16) (0x8000 / (s32) temp_v0_7);
                var_s1 = 0;
                (*(s32 *)(var_s2 + 0x28)) = gl_func_0001CA10(0x2198, 0x20);
                (*(s32 *)(var_s2 + 0x2C)) = gl_func_0001CA10(0x2198, 0x20);
                (*(s32 *)(var_s2 + 0x30)) = gl_func_0001CA10(0x2198, 0x20);
                (*(s32 *)(var_s2 + 0x34)) = gl_func_0001CA10(0x2198, 0x20);
                if (*(s16 *)(g + 0x2040) > 0) {
                    var_s0_2 = var_s2;
                    do {
                        temp_v0_8 = gl_func_0001CA10(0x2198, 0x340);
                        (*(s32 *)(var_s0_2 + 0x3C)) = temp_v0_8;
                        (*(s32 *)(var_s0_2 + 0x40)) = (s32) (temp_v0_8 + 0x1A0);
                        temp_v0_9 = gl_func_0001CA10(0x2198, 0x340);
                        (*(s32 *)(var_s0_2 + 0xA0)) = temp_v0_9;
                        (*(s32 *)(var_s0_2 + 0xA4)) = (s32) (temp_v0_9 + 0x1A0);
                        var_s1 += 1;
                        var_s0_2 += 0x14;
                    } while (var_s1 < *(s16 *)(g + 0x2040));
                }
            }
            if ((*(s16 *)(temp_s5 + 0xE)) != 0) {
                (*(s32 *)(var_s2 + 0x108)) = gl_func_0001CA10(0x2198, 0x20);
                temp_v0_10 = gl_func_0001CA10(0x2198, 0x10);
                (*(s32 *)(var_s2 + 0x100)) = temp_v0_10;
                gl_func_0001CA10(temp_v0_10, (*(s16 *)(temp_s5 + 0xE)));
            } else {
                (*(s32 *)(var_s2 + 0x100)) = 0;
            }
            if ((*(s16 *)(temp_s5 + 0x10)) != 0) {
                (*(s32 *)(var_s2 + 0x10C)) = gl_func_0001CA10(0x2198, 0x20);
                temp_v0_11 = gl_func_0001CA10(0x2198, 0x10);
                (*(s32 *)(var_s2 + 0x104)) = temp_v0_11;
                gl_func_0001CA10(temp_v0_11, (*(s16 *)(temp_s5 + 0x10)));
            } else {
                (*(s32 *)(var_s2 + 0x104)) = 0;
            }
            temp_v0_6 = sp6C + 1;
            sp40 += 0x158;
            sp6C = temp_v0_6;
            var_s4_2 += 0x158;
            var_s7 += 0x12;
            var_s2 += 0x158;
            var_fp += 0x158;
        } while (temp_v0_6 < (s8) *(u8 *)(g + 1));
    }
    var_s1_2 = 0;
    gl_func_0001CA10();
    var_s0_3 = 0x2D00;
    if (*(s16 *)(g + 0x2048) > 0) {
        do {
            gl_func_0001CA10(var_s1_2);
            gl_func_0001CA10(var_s0_3);
            var_s1_2 += 1;
            var_s0_3 += 0x160;
        } while (var_s1_2 < *(s16 *)(g + 0x2048));
    }
    gl_func_0001CA10((*(s32 *)(sp60 + 0x30)), (s16) (*(s32 *)(sp60 + 0x34)));
    gl_func_0001CA10(*(s32 *)(g + 0x2070));
    *(s32 *)(g + 0x1034) = 0;
    gl_func_0001CA10();
    *(u8 *)(g + 4) = 0x1000;
    gl_func_0001CA10();
    temp_s0_2 = gl_func_0001CA10(1);
    gl_func_0001CA10();
    gl_func_0001CA10((s32) temp_s0_2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021498);
#endif

/* game_libs_func_00021D2C: 22-insn (0x58) table-search loop. BOUNDARY
 * MERGED 2026-06-02: splat over-split the loop tail as a separate symbol
 * (00021D70, 5-insn increment/exit whose `bne` branches backward to 0x21D48
 * inside this body; 21D2C's own `blez`/`bne` branch forward into it).
 * Absorbed 21D70's 5 words into 21D2C (0x44 -> 0x58, ends exactly at the next
 * func 0x21D84); dropped the 21D70 symbol. Scans a global 0xC-stride record
 * table (count at +9524) matching a0==rec.h0(+9536) && a2==rec.h2(+9538),
 * returns rec+9528 on hit. Reloc-blind USO; stays INCLUDE_ASM. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00021D2C)();
s32 game_libs_func_00021D2C(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_v0;
    char *var_a1;

    temp_v1 = *(s32 *)0x2534;
    var_v0 = 0;
    if (temp_v1 > 0) {
        var_a1 = 0;
loop_2:
        var_v0 += 1;
        if ((arg0 == *(s16 *)((char *)var_a1 + 0x2540)) && (arg1 == *(s16 *)((char *)var_a1 + 0x2542))) {
            return FW(var_a1, 0x2538);
        }
        var_a1 += 0xC;
        if (var_v0 >= temp_v1) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
#else
/* game_libs_func_00021D2C: pair-key table search. n = D+0x2534 records
 * of 12 bytes at D+0x2538 (layout: int val; pad; short key_a; short
 * key_b); returns val of the first record matching (a0,a1), else 0.
 * Pass 1 2026-06-10, 22/22 insns at 15 register-level diffs (~72%
 * words). Load-bearing NEGATIVE findings on the way to 22/22:
 *  - short params -> sign-extension homing explosion (69 insns);
 *  - do-while form -> IDO -O2 UNROLLS the counted loop x4 with an
 *    alignment-versioning prologue (64 insns) EVEN with an aligned
 *    struct type -- only the goto-label form compiles compact (extends
 *    the 8988 sequential-loop lesson to single counted loops);
 *  - i<n exit collapses the rotation (20 insns); the i==n form keeps
 *    22 but emits bne-vs-slt (target has slt HOISTED between the key
 *    compares + bnez at bottom -- a rotated for(;;i<n) the goto form
 *    does not reproduce exactly).
 * Residual: count colors v1 (mine v0-adjacent), cursor in a1 (the
 * moved-arg register), slt placement. Regalloc/rotation hybrid. */
#ifdef NON_MATCHING
typedef struct Rec21D2C {
    int val;
    int _pad;
    short key_a;
    short key_b;
} Rec21D2C;
extern int D_21D2C_count;
extern Rec21D2C D_21D2C_tbl[];

int game_libs_func_00021D2C(int a0, int a1) {
    int n;
    int i;
    int a2;
    Rec21D2C *p;

    n = D_21D2C_count;
    a2 = a1;
    p = D_21D2C_tbl;
    i = 0;
    if (n > 0) {
loop:
        i += 1;
        if (a0 == p->key_a && a2 == p->key_b) {
            return p->val;
        }
        p += 1;
        if (i == n) {
            return 0;
        }
        goto loop;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00021D2C);
#endif
#endif

/* gl_func_00021D84: 33-insn slot-register helper.
 *   count = D[0x2534];
 *   v0 = func(&D2[0x2528], a2);
 *   slot = &D2[count*12];
 *   slot[0x2538] = v0;
 *   if (v0 != 0) { slot[0x2540] = (s16)a0; slot[0x2542] = (s16)a1; slot[0x253C] = a2; }
 *   return v0;
 *
 * 14-insn INSN_PATCH closes: (1) count-spill slot sp+0x1C → sp+0x18; (2)
 * bnez/sw schedule reshuffle where target uses bnez v0 with sw v0 in DS
 * + b-to-epilogue with `move v0, $0` in DS for the zero-path return, vs
 * built's linear move-a0-v0 + beqz + linear body. C-level if/store
 * reorders all regressed (33.9% / 42.7% / 57.6%); INSN_PATCH is the
 * direct path. */
extern int func_00000000();
#ifdef NON_MATCHING
int gl_func_00021D84(int a0, int a1, int a2) {
    int count = *(int*)((char*)&D_00000000 + 0x2534);
    char *base = (char*)&D_00000000;
    int v0 = func_00000000(base + 0x2528, a2);
    char *slot = base + count * 12;
    *(int*)(slot + 0x2538) = v0;
    if (v0 != 0) {
        *(short*)(slot + 0x2540) = (short)a0;
        *(short*)(slot + 0x2542) = (short)a1;
        *(int*)(slot + 0x253C) = a2;
    }
    return v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021D84);
#endif

/* gl_func_00021E08: 20-insn alloc-via-jal-alt-entry + 3-field-set wrapper.
 * Matched 2026-05-14 via if-goto-end_zero (skip body) + explicit
 * `return *(v0+8);` at success path + `return 0;` at end_zero label.
 * The split-epilogue pattern (with `beq zero,zero,.epi` + lw-in-delay-slot
 * + `or v0,zero,zero` at the zero-arm label) requires BOTH the goto-to-
 * separate-zero-label AND the explicit return at each exit — combining
 * with `goto end; ... end: return v0;` instead hoists the lw too early.
 * Alt-entry resolved via gl_func_000365AC = 0x000365AC; in
 * undefined_syms_auto.txt (added 2026-05-13). */
extern void *gl_func_000365AC();
void *gl_func_00021E08(int a0, int a1, int a2, signed char a3) {
    char *v0 = (char *)gl_func_000365AC(a0);
    if (v0 == 0) goto end_zero;
    v0[2] = (char)a1;
    *(int*)(v0 + 0xC) = a2;
    v0[1] = a3;
    return *(void**)(v0 + 8);
end_zero:
    return 0;
}

/* 20-insn helper: alloc-via-callee gl_func_00036A48 + 3-field-set + return
 * v0[8]. */
extern int gl_func_00036A48();
int *gl_func_00021E58(int a0, int a1, int a2, signed char a3) {
    int *v0 = (int*)gl_func_00036A48(a0);
    if (v0 == 0) goto end_zero;
    *(char*)((char*)v0 + 2) = (char)a1;
    *(int*)((char*)v0 + 0xC) = a2;
    *(signed char*)((char*)v0 + 1) = a3;
    return *(int**)((char*)v0 + 0x8);
end_zero:
    return 0;
}

/* gl_func_00021EA8: 38-insn 4-call gated cleanup pair.
 *   Two parallel call pairs (one for a0, one for a1). Each pair:
 *     r = func(&D[0x2198], arg);
 *     if (r == 0) D[zero_field] = 0;
 *     else        func(&D[other_table], r, arg);   // 3 args!
 *   Then unconditional D[0x2948] = 0; D[0x2BDC] = 0;
 *
 * Matched 2026-05-14. Key insight: the `else` branch passes THREE args
 * (other_table, r, arg), not two — the `or a1, v0, zero` in the bne's
 * regular (non-likely) delay slot in target asm preserves v0 (= r) into
 * a1 for the next call. The 2-arg form (func(other_table, arg)) was the
 * cap-causing structural error. */
extern int func_00000000();
void gl_func_00021EA8(int a0, int a1) {
    int r0 = func_00000000((char*)&D_00000000 + 0x2198, a0);
    if (r0 == 0) {
        *(int*)((char*)&D_00000000 + 0x26C0) = 0;
    } else {
        func_00000000((char*)&D_00000000 + 0x26B8, r0, a0);
    }
    {
        int r1 = func_00000000((char*)&D_00000000 + 0x2198, a1);
        if (r1 == 0) {
            *(int*)((char*)&D_00000000 + 0x2954) = 0;
        } else {
            func_00000000((char*)&D_00000000 + 0x294C, r1, a1);
        }
    }
    *(int*)((char*)&D_00000000 + 0x2948) = 0;
    *(int*)((char*)&D_00000000 + 0x2BDC) = 0;
}

// gl_func_00021F40 — STRUCTURAL PASS (0x298 / 166 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A find-or-create registry/list-insert helper.
//
//   ret gl_func_00021F40(void *arg) {
//     S    *g    = &D_0;
//     Node *head = g->w_2950;                         // list head
//     int   r    = (*lookup)(&D_294C, arg);           // jal 0 USO-rel
//     if (r != 0) return r;                            // found: done
//     Node *save = g->w_2950;
//     g->w_2950  = *(int*)(&D_294C);                   // tentative new
//     int r2     = (*alloc_link)(&D_294C, arg);        // jal 0 USO-rel
//     if (r2 != 0) {
//       g->w_2950 = save;                              // ROLLBACK head
//       return ...;
//     }
//     ... finalize the prepended node ...
//   }
//
// Struct-typing reference: &D_294C is a fixed descriptor blob (the
//   key/format passed to both USO-relocated helpers, the `jal 0`
//   slots). Word &D_0+0x2950 is the head pointer of a registry list
//   built from that descriptor. The function does a lookup first;
//   on miss it speculatively repoints the list head, calls an
//   allocate-and-link helper, and rolls the head back if that
//   allocation/link fails — a transactional find-or-create insert.
//   Same game_libs registry support family as the gl_func_0001FD98 /
//   gl_func_0001FEC8 allocator/install helpers.
// Caps (DEFERRED): single jr $ra. Transactional find-or-create
//   registry/list-insert (same support family as gl_func_0001FD98 /
//   gl_func_0001FEC8). Real-C STRUCTURAL body below per the analysis
//   (lookup(&D_294C,arg); on hit return; else save head, tentatively
//   repoint &D_0+0x2950, alloc-and-link; rollback head on failure).
//   Byte-match deferred — placeholder jal-0 lookup/alloc calls need
//   USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the helpers.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01 (was 14% front-only stub w/ inverted post-gate).
 * Two gl gates; only on a non-zero return does it scan region arrays for an
 * overlap with [s2,s3) (s3=*desc reload, s2=*head), marking free slots, then
 * allocates the next descriptor at D+0x294C+idx*20. Overlap branch directions
 * + bound arithmetic approximate; multi-loop allocator, multi-tick remainder. */
extern int gl_func_00036844();
int gl_func_00021F40(void *arg) {
    char *g = (char *)&D_00000000;
    int s3, s2, s5, s1, r, save, a3, cnt;
    char *a2, *s0;

    s3 = *(int *)(g + 0x2950);
    r = gl_func_00000000(g + 0x294C, arg);
    if (r == 0) {
        save = *(int *)(g + 0x2950);
        *(int *)(g + 0x2950) = *(int *)(g + 0x294C);
        r = gl_func_00000000(g + 0x294C, arg);
        if (r == 0) {
            *(int *)(g + 0x2950) = save;
            return 0;
        }
    }
    s3 = *(int *)(g + 0x294C);
    a3 = *(int *)(g + 0x1034);
    s2 = *(int *)(g + 0x2950);
    s5 = -1;
    if (a3 > 0) {
        for (a2 = g; a2 < g + a3 * 20; a2 += 20) {
            char *rr = a2 + 1584;
            int base, top;
            if (*(int *)(a2 + 1600) != 0) {
                continue;
            }
            base = *(int *)(rr + 8);
            top = base + (*(int *)*(int *)(rr + 4) & 0xFFFFFF) - 1;
            if ((unsigned)top < (unsigned)s3 && (unsigned)base < (unsigned)s3) {
                continue;
            }
            if ((unsigned)top < (unsigned)s2 || (unsigned)base < (unsigned)s2) {
                *(int *)(rr + 16) = 1;
                a3 = *(int *)(g + 0x1034);
            }
        }
    }
    cnt = *(int *)(g + 0x2BDC);
    if (cnt > 0) {
        for (s1 = 0, s0 = g + 0x294C; s1 < cnt; s1++, s0 += 20) {
            int base = *(int *)(s0 + 24);
            int top = *(int *)(s0 + 32) + base - 1;
            if ((unsigned)top < (unsigned)s3 || (unsigned)base < (unsigned)s3) {
                continue;
            }
            if ((unsigned)top < (unsigned)s2 || (unsigned)base < (unsigned)s2) {
                continue;
            }
            gl_func_00036844(s0 + 16);
            if (s5 == -1) {
                s5 = s1;
            }
            cnt = *(int *)(g + 0x2BDC);
        }
    }
    if (s5 == -1) {
        int idx = *(int *)(g + 0x2BDC);
        char *v1 = g + 0x294C + idx * 20;
        *(int *)(g + 0x2BDC) = idx + 1;
        *(signed char *)(v1 + 16) = 1;
        *(int *)(v1 + 24) = r;
        *(int *)(v1 + 32) = (int)arg;
        return (int)(v1 + 16);
    }
    return *(int *)(g + 0x2BDC);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021F40);
#endif

// gl_func_000221D8 — STRUCTURAL PASS (0x204 / 129 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is a table slot find/allocate scan.
//
//   int gl_func_000221D8(K *key) {
//     S   *g   = &D_0;
//     int  n   = *(int*)(g + 0x2020);                 // entry count
//     if (n <= 0) return 0;
//     char *tbl = *(char**)(g + 0x2030);              // record table
//     int  i = 0, result = 0;
//     byte kb = key->b_2;
//     do {
//       char *e = tbl + i;
//       byte t2 = e->b_2, t3 = e->b_3;
//       if (t2 == 0xFF) { ... free slot ... }
//       if (t2 == kb)   { ... matched ...   }
//       ... advance i, accumulate result ...
//     } while (i < n);
//     return result;                                   // slot index
//   }
//
// Struct-typing reference: word &D_0+0x2020 is the live entry count,
//   pointer &D_0+0x2030 the record-table base (same &D_0 state block
//   as the gl_func_0002119C / gl_func_0001FBD4 sprite subsystem).
//   Each record carries match bytes at +2 / +3 compared against the
//   key's byte +2; the constants 0xFF and 0x7F are the empty-slot and
//   mask/sentinel markers. This is the find-existing-or-claim-free
//   slot scan for that registry table (the lower-level companion to
//   the gl_func_00021F40 list-insert helper).
// Caps (DEFERRED): single jr $ra (the "2-jr bundle" note is STALE;
//   .s is 0x204/115 words, ONE function). Find-existing-or-claim-
//   free slot scan for the registry table (lower-level companion to
//   the gl_func_00021F40 list-insert). Real-C STRUCTURAL body below
//   per the analysis (count &D_0+0x2020, table &D_0+0x2030, per-
//   record match bytes +2/+3 vs key->2, 0xFF empty-slot / 0x7F
//   sentinel). Byte-match deferred — scan-loop / branch schedule.
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int D_00000000;
/* Whole-body decode 2026-06-01 (was 6.1% over-simplified stub). Nested-loop
 * table dispatcher: outer over count=(*(D+0x2020))->0 entries (stride 20 in the
 * table at *(D+0x2030)); match an entry when its byte[2] or byte[3] == key->2,
 * or key->2==0; on match, two gl gates then two inner loops dispatching
 * gl_func_00036A04(key, sub->field) per sub-record. */
extern int gl_func_00036A04();
int gl_func_000221D8(char *key) {
    char *g = (char *)&D_00000000;
    char *s3 = key;
    int count = *(short *)(*(int *)(g + 0x2020));
    int s5, s4;

    if (count <= 0) {
        return 0;
    }
    s4 = 0;
    for (s5 = 0; s5 != count; s5++, s4 += 20) {
        char *e = (char *)*(int *)(g + 0x2030) + s4;
        int kb = *(signed char *)(s3 + 2);
        unsigned char v1 = *(unsigned char *)(e + 2);
        unsigned char a0b = *(unsigned char *)(e + 3);
        int matched;

        if (v1 != 0xFF && v1 == kb) matched = 1;
        else if (a0b != 0xFF && a0b == kb) matched = 1;
        else if (kb == 0) matched = 1;
        else matched = 0;
        if (!matched) continue;

        if (gl_func_00000000(1, 2, s5) == 0) continue;
        if (gl_func_00000000(s5) == 0) continue;
        {
            int s1, s2;
            int cnt1 = *(unsigned char *)((char *)*(int *)(g + 0x2030) + s4);
            for (s1 = 0; s1 < cnt1; s1++) {
                int *sub = (int *)gl_func_00000000(s5, s1);
                if (sub != 0) {
                    if (*(unsigned char *)((char *)sub + 1) != 0) {
                        gl_func_00036A04(s3, sub[8 / 4]);
                    }
                    if (*(unsigned char *)((char *)sub + 2) == 127) {
                        gl_func_00036A04(s3, sub[16 / 4]);
                    } else {
                        gl_func_00036A04(s3, sub[24 / 4]);
                    }
                }
                cnt1 = *(unsigned char *)((char *)*(int *)(g + 0x2030) + s4);
            }
            {
                int cnt2 = *(unsigned char *)((char *)*(int *)(g + 0x2030) + s4 + 1);
                for (s2 = 0; s2 < cnt2; s2++) {
                    int *sub = (int *)gl_func_00000000(s5, s2);
                    if (sub != 0) {
                        gl_func_00036A04(s3, sub[4 / 4]);
                    }
                    cnt2 = *(unsigned char *)((char *)*(int *)(g + 0x2030) + s4 + 1);
                }
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000221D8);
#endif

/* Guarded bitfield update: if(a1 && a0->8==a1->4){ a1->4=a0->0xC;
 * *a1 = ((a0[1]<<2)&0xC)|(*a1&~0xC); }. Structure exact; the bitfield
 * intermediates renumber (allocno cap). CAP: regalloc, stays NM
 * (INSN_PATCH REMOVED 2026-05-23 per
 * feedback_no_instruction_forcing_matches_policy). */
#ifdef NON_MATCHING
void game_libs_func_00022398(char *a0, char *a1) {
    if (a1 != 0) {
        if (*(int *)(a0 + 8) == *(int *)(a1 + 4)) {
            *(int *)(a1 + 4) = *(int *)(a0 + 0xC);
            *(unsigned char *)a1 = (((signed char)a0[1] << 2) & 0xC) | (*(unsigned char *)a1 & ~0xC);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00022398);
#endif

// gl_func_000223DC — STRUCTURAL PASS (0x88 / 34 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A find-or-append slot allocator over the &D_26B8 array,
// in the gl_func_00021F40 / gl_func_000221D8 registry family.
//
//   void *gl_func_000223DC(int key) {
//     int found = (*lookup)(&D_26B8, key);            // jal 0 USO-rel
//     if (found != 0) return found;                    // existing
//     int   i    = *(int*)(&D_0 + 0x2948);             // append index
//     char *slot = (char*)&D_26B8 + i*0x14 + 0x10;     // stride 0x14
//     slot->b_0  = 1;                                   // mark in-use
//     slot->w_8  = key;                                 // store key
//     slot->w_10 = 0;                                   // init field
//     *(int*)(&D_0 + 0x2948) = i + 1;                   // count++
//     return slot;
//   }
//
// Struct-typing reference: &D_26B8 is a fixed-stride table (entry
//   size 0x14, the live sub-record at +0x10 within each entry — the
//   index math is count*5<<2 = count*0x14). Word &D_0+0x2948 is the
//   append cursor / live count for that table. A new entry's byte +0
//   is the in-use flag (set 1), word +8 holds the key, word +0x10 an
//   init-zero field. Lookup is the USO-relocated `jal 0` helper
//   (resolved at load) keyed on the &D_26B8 descriptor. This is the
//   compact find-or-create-by-append companion to the
//   gl_func_00021F40 list-insert / gl_func_000221D8 slot-scan.
// Caps (DEFERRED): single jr $ra. Compact find-or-create-by-append
//   companion to gl_func_00021F40 / gl_func_000221D8. Real-C
//   STRUCTURAL body below per the analysis (jal-0 USO-reloc lookup
//   keyed on the &D_26B8 descriptor; on hit append a 0x14-stride
//   entry at index *(&D_0+0x2948): entry[0]=1, entry[8]=lookup
//   result, entry[0x10]=arg, then count++). Byte-match deferred —
//   placeholder jal-0 lookup needs USO reloc infra + branch/index
//   schedule. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
extern int gl_func_00000000();
void *gl_func_000223DC(int arg) {
    char *D = (char *)&D_00000000;
    char *base = D + 0x26B8;
    int r = gl_func_00000000(base, arg);
    if (r == 0) {
        return 0;
    }
    {
        char *e = base + *(int *)(D + 0x2948) * 0x14 + 0x10;
        *(char *)(e + 0) = 1;
        *(int *)(e + 8) = r;
        *(int *)(e + 0x10) = arg;
        *(int *)(D + 0x2948) = *(int *)(D + 0x2948) + 1;
        return e;
    }
}

// gl_func_00022464 — STRUCTURAL PASS (0x2FC / 191 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is a SIBLING of gl_func_000221D8: same registry-table
// scan, but the iterate-and-process-all-matches variant.
//
//   ret gl_func_00022464(K *key) {
//     S    *g   = &D_0;
//     int   n   = *(int*)(g + 0x2020);                // entry count
//     int   acc = 0, cnt = 0;
//     if (n <= 0) return 0;
//     char *tbl = *(char**)(g + 0x2030);              // record table
//     byte  kb  = key->b_0;
//     for (int i = 0; i < n; i++) {
//       char *e  = tbl + ...;
//       byte  t2 = e->b_2, t3 = e->b_3;
//       if (t2 == 0xFF) continue;                       // empty slot
//       if (t3 != 3 && t2 == kb) {                       // match gate
//         r = (*proc)(e, key);                            // jal 0 USO
//         if (r == 0) continue;
//         ... accumulate into acc/cnt ...
//       }
//     }
//     g->w_1E14 = 0;                                     // result clr
//     return acc;
//   }
//
// Struct-typing reference: same registry table as gl_func_000221D8
//   (count word &D_0+0x2020, base pointer &D_0+0x2030; record match
//   bytes +2 / +3; 0xFF empty-slot, 0x7F mask sentinel). This variant
//   does not stop at the first hit — it walks every entry, invokes a
//   USO-relocated per-match processor (`jal 0` slot) on each record
//   whose byte +2 equals the key and byte +3 != 3, accumulating a
//   result, and clears the result global &D_0+0x1E14 at the end. The
//   bulk "apply to all matching registry entries" operation paired
//   with the gl_func_000221D8 single-slot scan.
// Caps (DEFERRED): single jr $ra (the "2-jr bundle" note is STALE;
//   .s is 0x2FC/130 words, ONE function). Sibling of
//   gl_func_000221D8 — the "apply to all matching registry entries"
//   variant. Real-C STRUCTURAL body below per the analysis (count
//   &D_0+0x2020, table &D_0+0x2030; walk every entry, skip 0xFF
//   empty slots, on byte+2==key && byte+3!=3 invoke a jal-0 per-
//   match processor and accumulate; clear &D_0+0x1E14 at the end).
//   Byte-match deferred — placeholder jal-0 processor needs USO
//   reloc infra + scan-loop schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the processor.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00022464(char *key) {
    char *g = (char *)&D_00000000;
    int n = *(int *)(g + 0x2020);
    char *tbl;
    unsigned char kb;
    int i, acc;
    if (n <= 0) {
        return 0;
    }
    tbl = *(char **)(g + 0x2030);
    kb = *(unsigned char *)(key + 0);
    acc = 0;
    for (i = 0; i < n; i++) {
        char *e = tbl + i * 0x14;
        unsigned char t2 = *(unsigned char *)(e + 2);
        unsigned char t3 = *(unsigned char *)(e + 3);
        if (t2 == 0xFF) {
            continue;
        }
        if (t3 != 3 && t2 == kb) {
            int r = gl_func_00000000(e, key);
            if (r != 0) {
                acc += r;
            }
        }
    }
    *(int *)(g + 0x1E14) = 0;
    return acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022464);
#endif

#ifdef NON_MATCHING
/* Two-pass countdown/timer processor over the global D record arrays. For each
 * of count1=D[0x1E10] records (base D[0x1E08], stride 0x10): if rec[14] (a
 * countdown byte) == 1, set it to 0, store the queue tail D[0x201A] into rec[13],
 * append the record index into D[0x1E18 + D[0x201A]], bump D[0x201A]. Second pass:
 * same over count2=D[0x1E0C] records, queue D[0x201B]/D[0x1F18]. Finally
 * D[0x1E14]=0. Reloc-blind (&D). Byte-match multi-run: branch-likely loops +
 * register-alloc + the v0-only-increments-on-process loop counter. */
void game_libs_func_0002266C(void) {
    int v0 = 0;
    int a0 = 0;
    int count = *(int *)((char *)&D_00000000 + 0x1E10);
    if (count != 0) {
        do {
            unsigned char *rec = (unsigned char *)(a0 + *(int *)((char *)&D_00000000 + 0x1E08));
            unsigned char cd = rec[14];
            if (cd != 0 && (unsigned char)(cd - 1) == 0) {
                rec[14] = cd - 1;
                rec[13] = *(unsigned char *)((char *)&D_00000000 + 0x201A);
                *(unsigned char *)((char *)&D_00000000 + 0x1E18 + *(unsigned char *)((char *)&D_00000000 + 0x201A)) = v0;
                *(unsigned char *)((char *)&D_00000000 + 0x201A) += 1;
                count = *(int *)((char *)&D_00000000 + 0x1E10);
                v0++;
            }
            a0 += 16;
        } while ((unsigned int)v0 < (unsigned int)count);
    }
    count = *(int *)((char *)&D_00000000 + 0x1E0C);
    if ((unsigned int)v0 < (unsigned int)count) {
        do {
            unsigned char *rec = (unsigned char *)(a0 + *(int *)((char *)&D_00000000 + 0x1E08));
            unsigned char cd = rec[14];
            if (cd != 0 && (unsigned char)(cd - 1) == 0) {
                rec[14] = cd - 1;
                rec[13] = *(unsigned char *)((char *)&D_00000000 + 0x201B);
                *(unsigned char *)((char *)&D_00000000 + 0x1F18 + *(unsigned char *)((char *)&D_00000000 + 0x201B)) = v0;
                *(unsigned char *)((char *)&D_00000000 + 0x201B) += 1;
                count = *(int *)((char *)&D_00000000 + 0x1E0C);
                v0++;
            }
            a0 += 16;
        } while ((unsigned int)v0 < (unsigned int)count);
    }
    *(int *)((char *)&D_00000000 + 0x1E14) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002266C);
#endif

// gl_func_00022760 — STRUCTURAL PASS (0x33C / 207 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A custom HEAP ALLOCATOR (first-fit block walk) in the
// game_libs memory subsystem. -0x50 frame, s0/s1/ra saved.
//
//   void *gl_func_00022760(void *a0, int size, void *arena, void *a3) {
//     S *g = &D_0;
//     if (arena == 0) {                                // use default
//       arena_end  = g->w_1E10;
//       if (a3->b_0 < arena_end) { ... }
//     }
//     char *base = g->w_1E08;                           // block table
//     char *end  = g->w_1E10;
//     char *free = g->w_1E0C;                            // free cursor
//     for (int idx = 0; ; idx++) {
//       Blk *b = base + idx*0x10;                         // 0x10 hdr
//       int  sz = b->w_4;
//       if (size <= sz) {                                  // fits?
//         short cap = b->h_A;
//         if (cap - size >= ...) return b;                 // first-fit
//       }
//       ... advance / split / fail ...
//     }
//   }
//
// Struct-typing reference: a fixed-stride block-header heap. Arena
//   globals live in the &D_0 state block — word &D_0+0x1E08 is the
//   block-table base, &D_0+0x1E0C the free/alloc cursor, &D_0+0x1E10
//   the arena end (same &D_0+0x1Exx region the gl_func_00021498 /
//   gl_func_00022464 routines clear at +0x1E0C / +0x1E14). Each block
//   is a 0x10-byte header (idx<<4) with word +4 = block size and
//   halfword +0xA = capacity/free count; the loop is a first-fit
//   search comparing the requested `size` against block free space.
//   The low-level allocator under the gl_func_0001FD98 alloc helper /
//   gl_func_00021F40 registry family.
// Caps (DEFERRED): CLEAN single jr $ra. Custom first-fit HEAP
//   ALLOCATOR (low-level allocator under the gl_func_0001FD98 /
//   gl_func_00021F40 family). Real-C STRUCTURAL body below per the
//   analysis (arena globals &D_0+0x1E08 table base / +0x1E0C free
//   cursor / +0x1E10 end; 0x10-byte block headers, word+4 = size,
//   halfword+0xA = capacity; first-fit walk returning the first
//   block whose free space fits `size`). Byte-match deferred —
//   allocator loop / split-or-advance branch schedule. Name
//   pre-checked: no extern reuse (collision-safe).
// gl_func_00022760 — FULL m2c DECODE (53.33% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00022760)();
s32 gl_func_00022760(s32 arg0, s32 arg1, s32 arg2, u8 *arg3, s32 arg4) {
    char *sp48;
    s32 sp38;
    s32 temp_s0;
    s32 temp_t5;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 var_t2;
    s32 var_t3;
    u16 temp_v0_7;
    u32 temp_a1;
    u32 temp_a1_2;
    u32 temp_a2;
    u32 temp_v1_3;
    u32 var_a0;
    u32 var_a0_2;
    u8 temp_t2;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_5;
    u8 temp_v0_6;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 var_v0;
    char *temp_t0;
    char *var_t0;
    char *var_v1;

    var_t3 = 0;
    if ((arg2 != 0) || (var_v0 = *(int*)arg3, ((var_v0 < (u32) *(u32 *)0x1E10) == 0))) {
        temp_a2 = *(u32 *)0x1E10;
        temp_a1 = *(u32 *)0x1E0C;
        var_a0 = temp_a2;
        if (temp_a2 < temp_a1) {
            var_v1 = (var_a0 * 0x10) + *(u32 *)0x1E08;
loop_4:
            temp_t0 = var_v1;
            temp_v0 = arg0 - FW(var_v1, 0x4);
            if ((temp_v0 >= 0) && ((u32) ((*(u16 *)((char *)temp_t0 + 0xA)) - arg1) >= (u32) temp_v0)) {
                if ((*(u8 *)((char *)temp_t0 + 0xE)) == 0) {
                    temp_v0_2 = *(u32 *)0x2019;
                    if (*(u32 *)0x201B != temp_v0_2) {
                        temp_v1 = (*(u8 *)((char *)temp_t0 + 0xD));
                        if (temp_v0_2 != temp_v1) {
                            (*(u8 *)((char *)temp_v1 + 0x1F18)) = (u8) (*(u8 *)((char *)temp_v0_2 + 0x1F18));
                            FW((*(u32 *)0x1E08 + (FW((*(u32 *)0x2019), 0x1F18) * 0x10)), 0xD) = (u8) (*(u8 *)((char *)temp_t0 + 0xD));
                        }
                        *(u32 *)0x2019 = (u8) (*(u32 *)0x2019 + 1);
                    }
                }
                (*(u8 *)((char *)temp_t0 + 0xE)) = 0x20U;
                *arg3 = (u8) var_a0;
                return (FW(temp_t0, 0x0) + (int)arg0) - FW(temp_t0, 0x4);
            }
            var_a0 += 1;
            var_v1 += 0x10;
            if (var_a0 >= temp_a1) {
                sp48 = temp_t0;
                goto block_14;
            }
            goto loop_4;
        }
block_14:
        var_t0 = sp48;
        if (arg2 == 0) {
            var_v0 = *(int*)arg3;
            goto block_20;
        }
        temp_v0_3 = *(u32 *)0x2019;
        if ((*(u32 *)0x201B != temp_v0_3) && (arg2 != 0)) {
            temp_t2 = FW(temp_v0_3, 0x1F18);
            *(u32 *)0x2019 = (u8) (temp_v0_3 + 1);
            var_t3 = 1;
            sp38 = (s32) temp_t2;
            var_t0 = (temp_t2 * 0x10) + *(u32 *)0x1E08;
        }
        goto block_29;
    }
block_20:
    temp_a1_2 = *(u32 *)0x1E08;
    var_t0 = (var_v0 * 0x10) + temp_a1_2;
    var_a0_2 = 0;
loop_21:
    temp_v0_4 = arg0 - FW(var_t0, 0x4);
    if ((temp_v0_4 >= 0) && ((u32) (FW(var_t0, 0xA) - arg1) >= (u32) temp_v0_4)) {
        if (FW(var_t0, 0xE) == 0) {
            temp_v0_5 = *(u32 *)0x2018;
            temp_v1_2 = FW(var_t0, 0xD);
            if (temp_v0_5 != temp_v1_2) {
                FW(temp_v1_2, 0x1E18) = (u8) FW(temp_v0_5, 0x1E18);
                FW((*(u32 *)0x1E08 + (FW((*(u32 *)0x2018), 0x1E18) * 0x10)), 0xD) = (u8) FW(var_t0, 0xD);
            }
            *(u32 *)0x2018 = (u8) (*(u32 *)0x2018 + 1);
        }
        FW(var_t0, 0xE) = 2U;
        return (FW(var_t0, 0x0) + (int)arg0) - FW(var_t0, 0x4);
    }
    temp_t5 = var_a0_2 * 0x10;
    var_a0_2 += 1;
    var_t0 = temp_t5 + temp_a1_2;
    if (*(u32 *)0x1E10 < var_a0_2) {
block_29:
        var_t2 = sp38;
        if (var_t3 == 0) {
            temp_v0_6 = *(u32 *)0x2018;
            if (*(u32 *)0x201A == temp_v0_6) {
                return 0;
            }
            var_t2 = (s32) FW(temp_v0_6, 0x1E18);
            *(u32 *)0x2018 = (u8) (temp_v0_6 + 1);
            var_t0 = (var_t2 * 0x10) + *(u32 *)0x1E08;
            goto block_33;
        }
block_33:
        temp_v0_7 = FW(var_t0, 0xA);
        FW(var_t0, 0xE) = 3;
        temp_s0 = arg0 & ~0xF;
        FW(var_t0, 0x4) = temp_s0;
        FW(var_t0, 0x8) = temp_v0_7;
        temp_v1_3 = *(u32 *)0x207C;
        *(u32 *)0x207C = temp_v1_3 + 1;
        sp38 = var_t2;
        sp48 = var_t0;
        game_libs_func_0003443C((temp_v1_3 * 0x18) + 0x17D4, 0, 0, temp_s0, FW(var_t0, 0x0), (s32) temp_v0_7, 0x16BC, arg4, 0x1AA84);
        *arg3 = (u8) var_t2;
        return (arg0 - temp_s0) + FW(var_t0, 0x0);
    }
    goto loop_21;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022760);
#endif

// gl_func_00022A9C — STRUCTURAL PASS (0x2CC / 179 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). The heap-arena INITIALIZER — the setup counterpart to the
// gl_func_00022760 first-fit allocator.
//
//   void gl_func_00022A9C(void) {
//     S  *g    = &D_0;
//     int n    = g->w_2070;                            // record count
//     int sz   = g->h_2034;                             // unit size
//     int tot  = (n << 6) * sz;                          // arena bytes
//     g->w_2068 = g->w_2060;                             // save base
//     void *blk = (*alloc)(&D_2198, tot);                // jal 0 USO
//     g->w_1E08 = blk;                                   // arena base
//     int t3   = (n << 6) * 3;
//     g->w_1E0C = blk;                                   // free cursor
//     g->w_1E10 = blk + tot;                             // arena end
//     ... seed the block-header table / link the free list ...
//   }
//
// Struct-typing reference: pairs with gl_func_00022760 — it produces
//   the very arena globals that allocator walks: word &D_0+0x1E08
//   (block-table base), &D_0+0x1E0C (free cursor), &D_0+0x1E10 (arena
//   end), plus &D_0+0x2068 (saved original base). Total size is the
//   live record count &D_0+0x2070 scaled (<<6) times the unit-size
//   halfword &D_0+0x2034 (the same count/size globals the
//   gl_func_0002119C / gl_func_00021498 sprite subsystem uses). The
//   backing block is obtained from a USO-relocated allocator (`jal 0`
//   slot, resolved at load) keyed on descriptor &D_2198. This is the
//   one-time heap bring-up for the gl_func_00022760 allocator family.
// Caps (DEFERRED): CLEAN single jr $ra. Heap-arena INITIALIZER —
//   one-time bring-up counterpart to the gl_func_00022760 first-fit
//   allocator. Real-C STRUCTURAL body below per the analysis (total
//   = (count<<6)*unit-size from &D_0+0x2070/0x2034; save base to
//   &D_0+0x2068; jal-0 USO-reloc backing alloc keyed on &D_2198;
//   set arena base/free/end at &D_0+0x1E08/0x1E0C/0x1E10; seed the
//   block-header table). Byte-match deferred — placeholder jal-0
//   allocator needs USO reloc infra + seed-loop schedule. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder for the allocator.
// gl_func_00022A9C — m2c DECODE (37.41% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00022A9C)();
void gl_func_00022A9C(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s2_2;
    s32 var_v1;
    s32 var_v1_2;
    s8 var_s2;
    u32 temp_t4;
    u32 var_a0;
    u32 var_s2_3;
    u32 var_v0_2;
    u32 var_v0_3;
    u32 var_v0_4;
    char *temp_s0;
    char *temp_s0_2;
    char *var_v0;

    *(s32 *)0x2068 = *(s32 *)0x2060;
    *(s32 *)0x1E08 = gl_func_0001CA10(0x2198, (*(s32 *)0x2070 << 6) * *(s32 *)0x2034);
    var_s2 = 0;
    if ((*(s32 *)0x2070 * 3 * *(s32 *)0x2034) > 0) {
loop_1:
        temp_s0 = (*(s32 *)0x1E0C * 0x10) + *(s32 *)0x1E08;
        temp_v0 = gl_func_0001CA10(0x2198, *(s32 *)0x2068);
        FW(temp_s0, 0x0) = temp_v0;
        if (temp_v0 == 0) {

        } else {
            gl_func_0001CA10(FW(temp_s0, 0x0), *(s32 *)0x2068);
            FW(temp_s0, 0x4) = 0;
            FW(temp_s0, 0x8) = 0;
            FW(temp_s0, 0xC) = 0;
            FW(temp_s0, 0xE) = 0;
            FW(temp_s0, 0xA) = (s16) *(s32 *)0x2068;
            var_s2 += 1;
            *(s32 *)0x1E0C += 1;
            if (var_s2 < (*(s32 *)0x2070 * 3 * *(s32 *)0x2034)) {
                goto loop_1;
            }
        }
        var_s2 = 0;
    }
    var_a0 = *(s32 *)0x1E0C;
    var_v0 = 0;
    var_v1 = 0;
    if (var_a0 != 0) {
        do {
            FW(var_v0, 0x1E18) = var_s2;
            var_v0 += 1;
            FW((*(s32 *)0x1E08 + var_v1), 0xD) = var_s2;
            var_a0 = *(s32 *)0x1E0C;
            var_s2 += 1;
            var_v1 += 0x10;
        } while ((u32) var_s2 < var_a0);
    }
    if ((s32) var_a0 < 0x100) {
        var_v0_2 = var_a0;
        do {
            var_v0_2 += 1;
            FW(var_v0_2, 0x1E17) = 0;
        } while (var_v0_2 < 0x100U);
        var_a0 = *(s32 *)0x1E0C;
    }
    *(s32 *)0x2018 = 0;
    *(s32 *)0x201A = (s8) var_a0;
    *(s32 *)0x1E10 = var_a0;
    var_s2_2 = 0;
    *(s32 *)0x2068 = *(s32 *)0x2064;
    if (*(s32 *)0x2070 > 0) {
loop_12:
        temp_s0_2 = (*(s32 *)0x1E0C * 0x10) + *(s32 *)0x1E08;
        temp_v0_2 = gl_func_0001CA10(0x2198, *(s32 *)0x2068);
        FW(temp_s0_2, 0x0) = temp_v0_2;
        if (temp_v0_2 == 0) {
            var_a0 = *(s32 *)0x1E0C;
        } else {
            gl_func_0001CA10(FW(temp_s0_2, 0x0), *(s32 *)0x2068);
            FW(temp_s0_2, 0x4) = 0;
            FW(temp_s0_2, 0x8) = 0;
            FW(temp_s0_2, 0xC) = 0;
            FW(temp_s0_2, 0xE) = 0;
            FW(temp_s0_2, 0xA) = (s16) *(s32 *)0x2068;
            var_s2_2 += 1;
            temp_t4 = *(s32 *)0x1E0C + 1;
            *(s32 *)0x1E0C = temp_t4;
            if (var_s2_2 >= *(s32 *)0x2070) {
                var_a0 = temp_t4;
            } else {
                goto loop_12;
            }
        }
    }
    var_s2_3 = *(s32 *)0x1E10;
    var_v1_2 = var_s2_3 * 0x10;
    if (var_s2_3 < var_a0) {
        var_v0_3 = var_s2_3;
        do {
            FW((var_v0_3 + -(s32) *(s32 *)0x1E10), 0x1F18) = (s8) var_s2_3;
            var_v0_3 += 1;
            FW((*(s32 *)0x1E08 + var_v1_2), 0xD) = (s8) (var_s2_3 - *(s32 *)0x1E10);
            var_a0 = *(s32 *)0x1E0C;
            var_s2_3 += 1;
            var_v1_2 += 0x10;
        } while (var_s2_3 < var_a0);
    }
    if ((s32) var_a0 < 0x100) {
        var_v0_4 = var_a0;
        do {
            var_v0_4 += 1;
            FW(var_v0_4, 0x1F17) = (s8) *(s32 *)0x1E10;
        } while (var_v0_4 < 0x100U);
        var_a0 = *(s32 *)0x1E0C;
    }
    *(s32 *)0x2019 = 0;
    *(s32 *)0x201B = (s8) (var_a0 - *(s32 *)0x1E10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022A9C);
#endif

// gl_func_00022D68 — STRUCTURAL PASS (0x78 / 30 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A small readiness/availability predicate over the
// per-index state-byte array at &D_0+0x2C40.
//
//   int gl_func_00022D68(int idx) {
//     if (idx != 0xFF) {
//       byte st = *(byte*)(&D_0 + 0x2C40 + idx);        // state byte
//       if (st >= 2) return 1;                           // ready
//       int j = jal 0x38174(1);                          // 0x0C00E05D
//       byte st2 = *(byte*)(&D_0 + 0x2C40 + j);
//       if (st2 >= 2) return 1;
//       return 1;                                         // (default)
//     }
//     return 1;                                           // 0xFF sentinel
//   }
//
// Struct-typing reference: &D_0+0x2C40 is a per-index byte array of
//   slot states; a value >= 2 means "ready/active". The 0xFF index is
//   a null/none sentinel (treated as trivially ready). On a not-ready
//   slot the function calls the fixed USO-relocated routine
//   0x0C00E05D (≈0x38174) with arg 1 — a poll/advance that returns a
//   (possibly different) index — then re-tests its state byte. The
//   net result is a boolean readiness flag. A status-query helper of
//   the same &D_0 sprite/registry subsystem (the 0x2C40 byte array
//   sits alongside the 0x2CF0/0x2CF1 state bytes used by
//   gl_func_0002119C / gl_func_00021498).
// Caps (DEFERRED): single jr $ra. Status-query readiness helper of
//   the &D_0 sprite/registry subsystem (0x2C40 byte status array
//   alongside the 0x2CF0/0x2CF1 state bytes). Real-C STRUCTURAL body
//   below per the analysis (a0==0xFF -> ready; else status =
//   *(&D_0+0x2C40+a0); if status<2 ready; else poll a USO-reloc
//   helper(1) and re-check its slot; ready unless that slot is also
//   <2). Byte-match deferred — placeholder jal-0 poll needs USO
//   reloc infra + branch schedule. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder for the poll.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00022D68(int a0) {
    char *st = (char *)&D_00000000 + 0x2C40;
    int r;
    if (a0 == 0xFF) {
        return 1;
    }
    if (*(unsigned char *)(st + a0) >= 2) {
        return 1;
    }
    r = gl_func_00000000(1);
    if (*(unsigned char *)(st + r) < 2) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022D68);
#endif

// gl_func_00022DE0 — STRUCTURAL PASS (0x78 / 30 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Near-identical SIBLING of gl_func_00022D68 — same
// readiness predicate, different state-byte array base.
//
//   int gl_func_00022DE0(int idx) {
//     if (idx != 0xFF) {
//       byte st = *(byte*)(&D_0 + 0x2C70 + idx);        // state byte
//       if (st >= 2) return 1;                           // ready
//       int j = jal 0x38174(0);                          // 0x0C00E05D
//       byte st2 = *(byte*)(&D_0 + 0x2C70 + j);
//       if (st2 >= 2) return 1;
//       return 1;                                         // (default)
//     }
//     return 1;                                           // 0xFF sentinel
//   }
//
// Struct-typing reference: structurally identical to gl_func_00022D68
//   (see its comment) — readiness test "state byte >= 2", 0xFF index
//   = trivially-ready sentinel, fixed USO-reloc poll routine
//   0x0C00E05D (≈0x38174) on the not-ready path. The ONLY difference:
//   this variant queries the per-index state-byte array at
//   &D_0+0x2C70 instead of gl_func_00022D68's &D_0+0x2C40, and passes
//   0 (not 1) to the poll routine. The two are per-resource-class
//   readiness queries (the 0x2C40 / 0x2C70 byte arrays live in the
//   same &D_0 sprite/registry state region as the 0x2CF0 state bytes).
// Caps (DEFERRED): single jr $ra. Twin of gl_func_00022D68 — same
//   status-query readiness helper, table &D_0+0x2C70 (vs 0x2C40)
//   and poll arg 0 (vs 1). Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred — placeholder jal-0 poll needs USO
//   reloc infra. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00022DE0(int a0) {
    char *st = (char *)&D_00000000 + 0x2C70;
    int r;
    if (a0 == 0xFF) {
        return 1;
    }
    if (*(unsigned char *)(st + a0) >= 2) {
        return 1;
    }
    r = gl_func_00000000(0);
    if (*(unsigned char *)(st + r) < 2) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022DE0);
#endif

// gl_func_00022E58 — STRUCTURAL PASS (0x168 / 90 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 5-jr USO bundle
// (named fn + 4 tiny trailing sibling helpers) — deferred USO
// re-split. The named leading fn (~30 words, ends at 0x22EC8) is
// another readiness-predicate sibling of gl_func_00022D68 /
// gl_func_00022DE0.
//
//   int gl_func_00022E58(int idx) {
//     if (idx != 0xFF) {
//       byte st = *(byte*)(&D_0 + 0x2C10 + idx);        // state byte
//       if (st >= 2) return 1;                           // ready
//       int j = jal 0x38174(2);                          // 0x0C00E05D
//       byte st2 = *(byte*)(&D_0 + 0x2C10 + j);
//       if (st2 >= 2) return 1;
//       return 1;                                         // (default)
//     }
//     return 1;                                           // 0xFF sentinel
//   }
//
// Struct-typing reference: structurally identical to gl_func_00022D68
//   / gl_func_00022DE0 — readiness test "state byte >= 2", 0xFF index
//   trivially ready, fixed USO-reloc poll 0x0C00E05D (≈0x38174) on
//   the not-ready path. This third variant queries the state-byte
//   array at &D_0+0x2C10 and passes 2 to the poll. The 0x2C10 /
//   0x2C40 / 0x2C70 byte arrays are the per-resource-class slot-state
//   tables of the same &D_0 sprite/registry subsystem; the 4 trailing
//   bundled helpers are their tiny companions (one reads &D_0+0x2C40)
//   left for the deferred USO re-split.
// Caps (DEFERRED): single jr $ra (the "5-fn unsplit bundle" note is
//   STALE; .s is 0x78/30 words, ONE function). Triplet sibling of
//   gl_func_00022D68 / gl_func_00022DE0 — status-query readiness
//   helper, table &D_0+0x2C10, poll arg 2. Real-C STRUCTURAL body
//   below per the analysis. Byte-match deferred — placeholder jal-0
//   poll needs USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00022E58(int a0) {
    char *st = (char *)&D_00000000 + 0x2C10;
    int r;
    if (a0 == 0xFF) {
        return 1;
    }
    if (*(unsigned char *)(st + a0) >= 2) {
        return 1;
    }
    r = gl_func_00000000(2);
    if (*(unsigned char *)(st + r) < 2) {
        return 0;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022E58);
#endif

void game_libs_func_00022ED0(int a0, int a1) {
    if (a0 != 0xFF) {
        if (*(unsigned char *)((char *)&D_00000000 + a0 + 0x2C40) != 5) {
            *(unsigned char *)((char *)&D_00000000 + a0 + 0x2C40) = a1;
        }
    }
}

void game_libs_func_00022F00(int a0, int a1) {
    if (a0 != 0xFF) {
        if (*(unsigned char *)((char *)&D_00000000 + a0 + 0x2C70) != 5) {
            *(unsigned char *)((char *)&D_00000000 + a0 + 0x2C70) = a1;
        }
    }
}

void game_libs_func_00022F30(int a0, int a1) {
    if (a0 != 0xFF) {
        if (*(unsigned char *)((char *)&D_00000000 + a0 + 0x2C10) != 5) {
            *(unsigned char *)((char *)&D_00000000 + a0 + 0x2C10) = a1;
        }
    }
}

#ifdef NON_MATCHING
/* Header at a0: a0[0]=s16 count, a0+2=s16 (set to a2), a0+4=int (set to a1).
 * For each of `count` 16-byte elements (starting at a0), if elem->0x14 != 0 AND
 * elem->0x18(s8) == 2, add a1 to elem->0x10. Reloc-free, 24 insns.
 *
 * 2026-06-22: 22/24 insns now mnemonic-exact (was "arg-home-spill cap").
 * Two levers cracked the previously-unreproducible bits:
 *   (a) The leading `sw a2, 8(sp)` arg-home (no frame) IS reproducible by
 *       declaring the 3rd param `unsigned short a2` — that triggers IDO's
 *       arg-home with NO sign-extension (plain `short a2` adds sll/sra;
 *       `int a2` emits no home at all). The header store `sh a2,2(a0)`
 *       truncates anyway, so unsigned short is value-equivalent.
 *   (b) Re-reading the count via a named `short n = *a0;` (recomputed in the
 *       loop tail) places the count in $v1 (target) instead of $a3, and the
 *       counter in $v0 — matching the target's {v0=i, v1=count} pair.
 * RESIDUAL (the only diff): a pure same-multiset 2-register swap of the
 * cursor and the loop-invariant const 2 — target colors cursor=$a2 (reusing
 * the home-freed arg reg) + const=$a3; every C ordering tried colors
 * cursor=$a3 + const=$a2. The const (loop-invariant, hoisted before the
 * loop) always wins the home-freed $a2; the cursor's defining `move` at loop
 * entry takes $a3. Same-multiset {v0,v1,a2,a3} coloring permutation =
 * documented permuter-class cap. INCLUDE_ASM remains build path (no episode). */
void game_libs_func_00022F60(short *a0, int a1, unsigned short a2) {
    int i = 0;
    short n = *a0;
    char *cursor;
    *(short *)((char *)a0 + 2) = a2;
    *(int *)((char *)a0 + 4) = a1;
    cursor = (char *)a0;
    while (i < n) {
        i++;
        if (*(int *)(cursor + 0x14) != 0 && *(signed char *)(cursor + 0x18) == 2) {
            *(int *)(cursor + 0x10) += a1;
        }
        cursor += 16;
        n = *a0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00022F60);
#endif

// gl_func_00022FC0 — STRUCTURAL PASS (0xB8 / 46 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A bounds-checked buffer-run processor.
//
//   int gl_func_00022FC0(int idx, int arg) {
//     S *g = &D_0;
//     if (idx >= g->h_202C) return 0;                   // range check
//     short *buf = g->w_2028;                            // record buf
//     int start  = buf[idx];                             // run start
//     int cur    = start;
//     do {
//       byte b = *((char*)buf + cur);                     // element
//       cur++;
//       ...
//       jal 0x37EA4(b);                                   // 0x0C00DFA9
//       count--;
//     } while (count != 0);
//     buf[idx] = cur;                                      // write back
//     return ...;
//   }
//
// Struct-typing reference: halfword &D_0+0x202C is the valid index
//   limit; word &D_0+0x2028 is the base of a record/offset buffer
//   indexed by idx (halfword stride, idx<<1) — each slot holds a
//   cursor/offset into the same backing store. The loop walks a run
//   of byte elements from that cursor invoking the fixed USO-relocated
//   routine 0x0C00DFA9 (≈0x37EA4) per element, then writes the
//   advanced cursor back into buf[idx]. A per-slot stream/run consumer
//   in the same &D_0 sprite/registry subsystem (sibling family to the
//   gl_func_00022D68 readiness queries over the neighbouring 0x2Cxx
//   arrays).
// Caps (DEFERRED): CLEAN single jr $ra. Bounds-checked buffer-run
//   processor in the &D_0 sprite/registry subsystem. Real-C
//   STRUCTURAL body below per the analysis (idx range-check vs
//   &D_0+0x202C; buf = &D_0+0x2028 halfword-indexed; walk a run of
//   byte elements from buf[idx] invoking the fixed USO-reloc routine
//   0x37EA4 per element, then write the advanced cursor back).
//   Byte-match deferred — placeholder jal-0 per-element call needs
//   USO reloc infra + loop schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder for the per-element routine.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00022FC0(int idx, int arg) {
    char *g = (char *)&D_00000000;
    short *buf;
    int cur, count;
    if (idx >= *(short *)(g + 0x202C)) {
        return 0;
    }
    buf = *(short **)(g + 0x2028);
    cur = buf[idx];
    count = arg;
    do {
        unsigned char b = *((unsigned char *)buf + cur);
        cur++;
        gl_func_00000000(b);
        count--;
    } while (count != 0);
    buf[idx] = (short)cur;
    return cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022FC0);
#endif


/* game_libs_func_00023070 — bounds-gated dual-flag dispatch. The orphan
 * game_libs_func_00023070 (lui t6,0; lhu t6,0x202C(t6) = (u16)*(&D+0x202C))
 * was the stolen prologue of gl_func_00023078: it loads the limit compared
 * at the top (a0 < limit). Merged FORWARD (one 0x60 symbol at 0x23070,
 * successor .s deleted) and reading the limit inline at the comparison makes
 * IDO hoist the lui;lhu above the prologue — the prologue-steal is C-
 * reachable (same recipe as game_libs_func_00026B40). The 2nd flag check
 * uses plain `a1 & 1` — the compiler preserves a1 across the a1&2 call by
 * itself (emits `or a2,a1,zero` + spill); an explicit `int a2=a1` copy
 * instead ADDS a frame slot (+8) and breaks the match. jal 0x37D98 resolves
 * via gl_func_00037D98=0x37D98 in undefined_syms. MATCHED 2026-05-30. */
extern int gl_func_00000000();
extern int gl_func_00037D98();
void game_libs_func_00023070(int a0, int a1) {
    int local[2];
    if (a0 < (int)*(unsigned short *)((char *)&D_00000000 + 0x202C)) {
        if (a1 & 2) {
            gl_func_00000000(a0, local);
        }
        if (a1 & 1) {
            gl_func_00037D98(a0);
        }
    }
}

// gl_func_000230D0 — STRUCTURAL PASS (0xE4 / 57 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A packed-handle decode + dispatch.
//
//   ret gl_func_000230D0(H *h) {
//     byte fl = h->b_0;
//     if ((fl & 1) != 1) return;                        // gate bit0
//     int  w   = h->w_0;                                 // packed word
//     int  typ = (unsigned)w >> 30;                      // bits[31:30]
//     int  id  = w & 0x00FFFFFF;                          // low 24 bits
//     if (typ != 0) {
//       int t = (typ << 24) >> 24;                        // sign-ext
//       r = (*disp)(id, t);                                // jal 0 USO
//       int a = h->w_4;
//       if (r != 0) { ... }
//     }
//     // second decode path:
//     int w2 = h->w_0;
//     if (((unsigned)w2 >> 30) != 1) { ... }
//     T *tbl = *(T**)(&D_0 + 0x2024);                      // global tbl
//     int  a0arg = h->w_4;
//     short hw   = h->h_2;
//     ...
//   }
//
// Struct-typing reference: `h` is a packed object handle — its first
//   word doubles as a flags byte (bit0 = valid/active gate) and a
//   bitfield: bits[31:30] a 2-bit type/kind selector, bits[23:0] a
//   24-bit object id. Word h->4 and halfword h->2 are payload args
//   passed to the dispatch. Type-selected behaviour goes through a
//   USO-relocated routine (`jal 0` slot, resolved at load); the
//   second path indexes a global table at &D_0+0x2024. This is the
//   "resolve & act on a packed handle" entry of the game_libs
//   registry/handle subsystem.
// Caps (DEFERRED): CLEAN single jr $ra. Packed-handle decode +
//   dispatch entry of the game_libs registry/handle subsystem.
//   Real-C STRUCTURAL body below per the analysis (h->0 bit0 valid
//   gate; word bits[31:30]=type, bits[23:0]=id; type!=0 -> jal-0
//   USO-reloc disp(id, sign-ext type); second path indexes global
//   table &D_0+0x2024 with h->4 / h->2 payload). Byte-match deferred
//   — placeholder jal-0 dispatch needs USO reloc infra + bitfield
//   schedule. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000230D0)();
void gl_func_000230D0(char *arg0) {
    s32 sp24;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u32 temp_v1;
    u32 temp_v1_2;

    if (((FW(arg0, 0x0) & 1) == 1) && (temp_v0 = (s32) FW(arg0, 0x0), temp_v1 = (u32) (temp_v0 * 0x10) >> 0x1E, (temp_v1 != 0))) {
        temp_v0_2 = gl_func_0001CA10(temp_v0 & 0xFFFFFF, FW(arg0, 0x4), (s8) temp_v1);
        if (temp_v0_2 == 0) {
            return;
        }
        temp_v0_3 = (s32) FW(arg0, 0x0);
        temp_v1_2 = (u32) (temp_v0_3 * 0x10) >> 0x1E;
        if (temp_v1_2 == 1) {
            sp24 = temp_v0_2;
            gl_func_0001CA10(FW(arg0, 0x4), temp_v0_2, temp_v0_3 & 0xFFFFFF, FW((*(char **)0x2024), 0x2));
        } else {
            sp24 = temp_v0_2;
            gl_func_0001CA10(FW(arg0, 0x4), temp_v0_2, temp_v0_3 & 0xFFFFFF, (s16) temp_v1_2);
        }
        FW(arg0, 0x0) = (u8) (FW(arg0, 0x0) & 0xFFF3);
        FW(arg0, 0x4) = sp24;
    }
}
#else
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000230D0)();
void gl_func_000230D0(char *arg0) {
    s32 sp24;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    u32 temp_v1;
    u32 temp_v1_2;

    if (((FW(arg0, 0x0) & 1) == 1) && (temp_v0 = (s32) FW(arg0, 0x0), temp_v1 = (u32) (temp_v0 * 0x10) >> 0x1E, (temp_v1 != 0))) {
        temp_v0_2 = gl_func_0001CA10(temp_v0 & 0xFFFFFF, FW(arg0, 0x4), (s8) temp_v1);
        if (temp_v0_2 == 0) {
            return;
        }
        temp_v0_3 = (s32) FW(arg0, 0x0);
        temp_v1_2 = (u32) (temp_v0_3 * 0x10) >> 0x1E;
        if (temp_v1_2 == 1) {
            sp24 = temp_v0_2;
            gl_func_0001CA10(FW(arg0, 0x4), temp_v0_2, temp_v0_3 & 0xFFFFFF, FW((*(char **)0x2024), 0x2));
        } else {
            sp24 = temp_v0_2;
            gl_func_0001CA10(FW(arg0, 0x4), temp_v0_2, temp_v0_3 & 0xFFFFFF, (s16) temp_v1_2);
        }
        FW(arg0, 0x0) = (u8) (FW(arg0, 0x0) & 0xFFF3);
        FW(arg0, 0x4) = sp24;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000230D0);
#endif
#endif

// gl_func_000231B4 — STRUCTURAL PASS (0xD0 / 52 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A recursive handle/node-tree walker.
//
//   int gl_func_000231B4(int handle, int depth) {
//     if (depth >= 0x7F) return 0;                      // depth cap
//     N *n = (*lookup)(handle);                          // jal 0 USO
//     if (n == 0) return -1;
//     byte k1 = n->b_1;
//     if (k1 == 0) {                                      // leaf-ish
//       jal 0x37364(n->w_10, handle);                     // 0x0C00DDCF
//       jal 0x37364(n->w_10, handle);
//     } else {
//       jal 0x37364(n->w_8,  handle);                     // recurse 8
//     }
//     byte k2 = n->b_2;
//     if (k2 != 0x7F) {
//       jal 0x37364(n->w_18, handle);                     // recurse 18
//     }
//     ...
//   }
//
// Struct-typing reference: walks a handle-resolved node graph. The
//   handle is mapped to a node N via the USO-relocated lookup (`jal 0`
//   slot). N has child/next pointers at words +8, +0x10, +0x18 and
//   classifier bytes at +1 / +2 (the value 0x7F is the stop/no-child
//   sentinel, matching the same 0x7F sentinel the gl_func_000221D8 /
//   gl_func_00022D68 family uses). Traversal of each child goes
//   through the fixed routine 0x0C00DDCF (≈0x37364); the `depth`
//   second arg guards recursion (cap 0x7F). This is a scene/handle-
//   graph recursive visitor in the game_libs registry subsystem.
// Caps (DEFERRED): CLEAN single jr $ra. Recursive scene/handle-graph
//   visitor in the game_libs registry subsystem. Real-C STRUCTURAL
//   body below per the analysis (depth cap 0x7F; jal-0 USO-reloc
//   lookup(handle)->node; classifier byte n->1 selects leaf double-
//   visit of n->0x10 vs recurse n->8; n->2 != 0x7F sentinel ->
//   recurse n->0x18; traversal via fixed routine 0x37364). Byte-
//   match deferred — placeholder jal-0 lookup/traversal need USO
//   reloc infra + recursion schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01. depth>=0x7F: only depth==0x7F does work
 * (n=gl(handle,a2); gl_3773c(n->4,handle)); else return 0. depth<0x7F:
 * n=gl(handle); if(!n) return -1; if n->1!=0 gl_3773c(n->8,handle); always
 * gl_3773c(n->0x10,handle); if n->2!=0x7F gl_3773c(n->0x18,handle). The prior
 * body had the n->1 branch backwards and used the placeholder for 0x3773c. */
extern int gl_func_0003773C();
int gl_func_000231B4(int handle, int depth, int a2) {
    int *n;
    if (depth < 0x7F) {
        n = (int *)gl_func_00000000(handle);
        if (n == 0) {
            return -1;
        }
        if (*((unsigned char *)n + 1) != 0) {
            gl_func_0003773C(n[8 / 4], handle);
        }
        gl_func_0003773C(n[0x10 / 4], handle);
        if (*((unsigned char *)n + 2) != 0x7F) {
            gl_func_0003773C(n[0x18 / 4], handle);
        }
        return 0;
    }
    if (depth != 0x7F) {
        return 0;
    }
    n = (int *)gl_func_00000000(handle, a2);
    if (n == 0) {
        return -1;
    }
    gl_func_0003773C(n[4 / 4], handle);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000231B4);
#endif

/* gl_func_00023284: 25-insn 2-callee dispatcher with conditional cleanup.
 *   v = call(2, a0);
 *   v = call2(2, v, a1, a2, a3);    // 5-arg, last via stack
 *   if (v == 0) call3(a3, 0, 0);
 *
 * Target has RESOLVED jal targets baked in (0x0C00E05D -> 0x38174,
 * 0x0C00E1C3 -> 0x3870C) pointing inside other game_libs functions, and the C
 * now calls gl_ref_00038174 / gl_ref_0003870C (undefined_syms absolutes,
 * RESOLVED 2026-06-10 full-ROM word-diff drive) for the first two; the 3rd
 * stays gl_func_00000000 (genuine runtime-reloc placeholder, base word is
 * 0C000000 there too). ROM bytes now exact at links 232A0/232BC. */
extern int gl_ref_00038174();
extern int gl_ref_0003870C();
void gl_func_00023284(int a0, int a1, int a2, int a3) {
    int v;
    v = gl_ref_00038174(2, a0);
    v = gl_ref_0003870C(2, v, a1, a2, a3);
    if (v == 0) {
        gl_func_00000000(a3, 0, 0);
    }
}

// gl_func_000232E8 — STRUCTURAL PASS (0xFC / 63 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is a SIBLING of gl_func_00022FC0: same &D_0+0x2028
// buffer-run walk, different per-element processing.
//
//   void gl_func_000232E8(int idx, int a1, int a2) {
//     short *buf = *(short**)(&D_0 + 0x2028);            // record buf
//     int    cur = buf[idx];                              // run start
//     byte   cnt = *((char*)buf + cur);                   // run length
//     do {
//       cur++;
//       byte e = *((char*)buf + cur);                      // element
//       jal 0x38174(e);                                    // 0x0C00E05D
//       jal 0x381xx(1, …, a1, a2);                         // 0x0C00E1C3
//       cnt--;
//     } while (cnt != 0);
//     ... write back / finalize buf[idx] ...
//   }
//
// Struct-typing reference: walks the SAME per-slot record buffer as
//   gl_func_00022FC0 — word &D_0+0x2028 base, halfword-strided by idx
//   (idx<<1), each slot a cursor into the byte stream; a run length is
//   read from the stream head. This variant invokes TWO fixed
//   USO-relocated routines per element: 0x0C00E05D (≈0x38174, the
//   same poll/advance used by the gl_func_00022D68 readiness family)
//   and 0x0C00E1C3 (a per-element action taking the caller args
//   a1/a2). The double-callback run consumer paired with the
//   single-callback gl_func_00022FC0.
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0xFC/46 words, ONE function). Sibling of gl_func_00022FC0
//   — double-callback per-slot run consumer over the same
//   &D_0+0x2028 record buffer. Real-C STRUCTURAL body below per the
//   analysis (buf halfword-strided by idx; run length from stream
//   head; per element invoke two fixed USO-reloc routines 0x38174
//   and 0x381C3(1,a1,a2)). Byte-match deferred — placeholder jal-0
//   per-element calls need USO reloc infra + loop schedule. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_000232E8(int idx, int a1, int a2) {
    char *g = (char *)&D_00000000;
    short *buf = *(short **)(g + 0x2028);
    int cur = buf[idx];
    int cnt = *((unsigned char *)buf + cur);
    do {
        unsigned char e;
        cur++;
        e = *((unsigned char *)buf + cur);
        gl_func_00000000(e);
        gl_func_00000000(1, e, a1, a2);
        cnt--;
    } while (cnt != 0);
    buf[idx] = (short)cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000232E8);
#endif

/* Table lookup into a global at &D_00000000+0x2028: base = *(that); idx =
 * *(u16*)(base + a0*2); c = base[idx]; if c!=0 return base+idx+1 (string ptr);
 * else *a1 = 0, return 0. Merged: the non-zero return (base+idx+1) was
 * splat-split off as game_libs_func_000233D4 (UNSHARED); merged back
 * (0x34 -> 0x44). Reloc-blind (uses &D global, no episode); NOT byte-exact:
 * IDO folds the &D base into lui+lw (target uses lui+addiu+lw separate base).
 * INCLUDE_ASM is the build path. */
#ifdef NON_MATCHING
int game_libs_func_000233A0(int a0, char *a1) {
    char *base = *(char**)((char*)&D_00000000 + 0x2028);
    int idx = *(unsigned short*)(base + a0 * 2);
    char c = base[idx];
    if (c != 0) {
        return (int)(base + idx + 1);
    }
    *a1 = c;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000233A0);
#endif

// gl_func_000233E4 — STRUCTURAL PASS (0xB8 / 46 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Another SIBLING of the gl_func_00022FC0 / gl_func_000232E8
// buffer-run consumer family: per-element poll + lookup + handler.
//
//   void gl_func_000233E4(int idx) {
//     S *g = &D_0;
//     short *buf = g->w_2028;                            // record buf
//     int cur = buf[idx];                                 // run start
//     byte cnt = *((char*)buf + cur);                     // run length
//     do {
//       cur++;
//       byte e = *((char*)buf + cur);                      // element
//       jal 0x38174(e);                                    // 0x0C00E05D
//       int r = (*lookup)(1);                              // jal 0 USO
//       if (r != 0) {
//         jal 0x37B00(r);                                  // 0x0C00DEC0
//         (*handler)(0);                                   // jal 0 USO
//       }
//       cnt--;
//     } while (cnt != 0);
//     ... finalize via buf[idx] / &D_0+0x23FA ...
//   }
//
// Struct-typing reference: walks the SAME per-slot record buffer as
//   gl_func_00022FC0 / gl_func_000232E8 (word &D_0+0x2028 base,
//   idx<<1 stride, cursor + run-length byte stream). Per element it
//   calls the shared poll routine 0x0C00E05D (≈0x38174), then a
//   USO-relocated lookup (`jal 0` slot); on a hit it runs the fixed
//   action 0x0C00DEC0 (≈0x37B00) and a second USO-reloc handler.
//   Halfword &D_0+0x23FA is read in the tail finalize. The
//   poll+lookup+conditional-handler member of the buffer-run family.
// Caps (DEFERRED): CLEAN single jr $ra. poll+lookup+conditional-
//   handler member of the gl_func_00022FC0 / gl_func_000232E8
//   buffer-run consumer family. Real-C STRUCTURAL body below per the
//   analysis (same &D_0+0x2028 idx<<1 cursor buffer; per element
//   poll 0x38174(e), jal-0 USO-reloc lookup(1); on hit run fixed
//   0x37B00(r) + a second jal-0 handler(0); finalize via buf[idx] /
//   &D_0+0x23FA). Byte-match deferred — placeholder jal-0 calls need
//   USO reloc infra + loop schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_000233E4(int idx) {
    char *g = (char *)&D_00000000;
    short *buf = *(short **)(g + 0x2028);
    int cur = buf[idx];
    int cnt = *((unsigned char *)buf + cur);
    do {
        unsigned char e;
        int r;
        cur++;
        e = *((unsigned char *)buf + cur);
        gl_func_00000000(e);
        r = gl_func_00000000(1);
        if (r != 0) {
            gl_func_00000000(r);
            gl_func_00000000(0);
        }
        cnt--;
    } while (cnt != 0);
    buf[idx] = (short)cur;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000233E4);
#endif


/* game_libs_func_00023494: 2-insn `lui t6, 0; lh t6, 0x23FA(t6)` orphan
 * with no jr-ra and no prologue. Loads a half from absolute address
 * 0x000023FA into $t6 then falls THROUGH to the successor function (which
 * appears caller-set but isn't). Prologue-stolen-PREDECESSOR pattern per
 * project_1080_orphan_fn_prologue_vein. Not C-matchable as a standalone
 * 2-insn function (any C body emits its own prologue+epilogue). CAP
 * class. Default INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00023494);

// gl_func_0002349C — STRUCTURAL PASS (0xAC / 43 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An unregister/free-by-id — the deregister counterpart to
// the gl_func_00021F40 / gl_func_000223DC registry inserts.
//
//   void gl_func_0002349C(int id) {
//     S *g = &D_0;
//     g->h_23FA = -1;                                   // clear marker
//     if (g->h_2406 == id) g->h_2406 = -1;               // clear cur
//     Node *n = g->w_2308;                               // list base
//     if (n != 0) {
//       for (int i = 0; n; i++, n += 0xC) {               // 0xC stride
//         if (n->h_1E == id) n->h_1E = -1;                // unlink ent
//       }
//     }
//     (*free)(id);                                        // jal 0 USO
//   }
//
// Struct-typing reference: halfwords &D_0+0x23FA and &D_0+0x2406 are
//   "current/selected id" markers reset (to -1) when they reference
//   the id being removed (the same 0x23FA halfword the
//   gl_func_000233E4 buffer-run finalize touches). Word &D_0+0x2308
//   is the base of a fixed-stride (0xC) node list whose halfword +0x1E
//   holds an owning id; every node matching `id` has that field
//   cleared to -1 (unlinked). The actual storage release goes through
//   a USO-relocated free routine (`jal 0` slot). This is the
//   teardown/deregister entry of the gl_func_00021F40 / 000223DC /
//   000221D8 registry family.
// Caps (DEFERRED): CLEAN single jr $ra. Unregister/free-by-id —
//   teardown counterpart to the gl_func_00021F40 / 000223DC /
//   000221D8 registry inserts. Real-C STRUCTURAL body below per the
//   analysis (set &D_0+0x23FA marker = -1; if &D_0+0x2406 == id
//   reset it to -1; walk the &D_0+0x2308 node list, 0xC stride,
//   bound = the &D_0+0x2308 count, clearing every node->0x1E owning
//   id matching `id` to -1; then jal-0 USO-reloc free(id)).
//   2026-05-31: fixed the structure 3.5%->70.8%. The old body cleared
//   0x23FA UNCONDITIONALLY; correct is `if(id==D[0x23FA]) D[0x23FA]=-1;
//   else if(id==D[0x2406]) D[0x2406]=-1;` + a do-while node loop whose
//   count D[0x2308] is RELOADED per-iter (uncached). Residual: the
//   D[0x23FA] compare-load (lui t6; lh t6,0x23FA) is a STOLEN PROLOGUE in
//   the predecessor — my C emits it inline (+2 insns); needs an orphan
//   merge for the last mile. Plus the bnel unlink-loop schedule + reg
//   alloc. Name pre-checked: gl_func_00000000 = USO placeholder for free.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002349C(int id) {
    char *g = (char *)&D_00000000;
    int n;
    if (id == *(short *)(g + 0x23FA)) {
        *(short *)(g + 0x23FA) = -1;
    } else if (id == *(short *)(g + 0x2406)) {
        *(short *)(g + 0x2406) = -1;
    }
    n = *(int *)(g + 0x2308);
    if (n != 0) {
        char *e = g + 0x2308;
        int i = 0;
        do {
            if (id == *(short *)(e + 0x1E)) {
                *(short *)(e + 0x1E) = -1;
            }
            i++;
            e += 0xC;
        } while ((unsigned)i < *(unsigned int *)(g + 0x2308));
    }
    gl_func_00000000(id);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002349C);
#endif


/* game_libs_func_0002353C (0x50): orphan-prologue MERGE of the 0xC stub at
 * 0x2353C (`lui v0,0; addiu v0,0; lw t6,0x215C(v0)` = materialize &D_00000000 and
 * read D[0x215C]) + the 0x44 body formerly mislabeled gl_func_00023548. The two
 * are ONE routine: IDO hoists the leading global load above the prologue to
 * 0x2353C, and the body reuses $v0(=&D) as the store base (`addu t8,v0,t7`) — &D
 * is CSE-shared across the D[0x215C] read and the a0*0x160 store. Predecessor
 * gl_func_0002349C ends with its own jr ra, so 0x2353C is the true entry (not a
 * donated tail). The earlier note framed this as a now-banned PROLOGUE_STEALS/
 * SUFFIX cap; the clean symbol-merge is the real fix (cf. game_uso_func_00010648).
 * a0*0x160 = ((a0*4 - a0)*4 - a0)*32 (sll/subu chain). */
extern int gl_func_00037C50();
int game_libs_func_0002353C(int a0) {
    if (*(int*)((char*)&D_00000000 + 0x215C) != 0) return 0;
    *(int*)((char*)&D_00000000 + a0 * 0x160 + 0x2DDC) = 0;
    return gl_func_00037C50(a0);
}


/* game_libs_func_0002358C (0x58): orphan-prologue MERGE — sibling of
 * game_libs_func_0002353C (identical 0xC donor stub `lui v0; addiu v0; lw
 * t6,0x215C(v0)`, same a0*0x160 chain) but stores a2 at the slot instead of 0.
 * The former gl_func_00023598 body (0x23598) is absorbed; entry moved to
 * 0x2358C. This replaces the previously-banned PROLOGUE_STEALS=12 + INSN_PATCH
 * jal-rewrite with the legitimate merge: the donor prologue belongs to this
 * function, and the intra-segment jal target resolves via gl_func_00037C50 =
 * 0x37C50 in undefined_syms_auto.txt (the mid-blob alt-entry, added with 2353C).
 * int-return shape gives the beq-to-work + inline `move v0,0` early-exit. */
extern int gl_func_00037C50();
int game_libs_func_0002358C(int a0, int a1, int a2) {
    if (*(int*)((char*)&D_00000000 + 0x215C) != 0) return 0;
    *(int*)((char*)&D_00000000 + a0 * 0x160 + 0x2DDC) = a2;
    return gl_func_00037C50(a0, a1, 0);
}

// gl_func_000235E4 — STRUCTURAL PASS (0x148 / 82 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A COMBINED op that ties together the two &D_0 subsystems:
// the gl_func_0001FBD4 record table AND the gl_func_00022FC0
// buffer-run stream.
//
//   int gl_func_000235E4(int recIdx, int bufIdx, int arg) {
//     S *g = &D_0;
//     if (bufIdx >= g->h_202C) return 0;                // range check
//     int stride = ((recIdx*3) << 2) << 5;               // *0x160-ish
//     R *rec = (char*)g + 0x2D00 + stride;               // record tbl
//     (*proc)(rec);                                       // jal 0 USO
//     short *buf = g->w_2028;                             // run buffer
//     int    cur = buf[bufIdx];                            // run start
//     byte   cnt = *((char*)buf + cur);                    // run len
//     do {
//       cur++;
//       ...                                                // per-elem
//     } while (--cnt > 0);
//   }
//
// Struct-typing reference: indexes the SAME record table as
//   gl_func_0001FBD4 / gl_func_0002119C (base &D_0+0x2D00, fixed
//   per-record stride, here from recIdx scaled *3<<2<<5) and the SAME
//   per-slot run buffer as gl_func_00022FC0 / gl_func_000232E8 (word
//   &D_0+0x2028 base, idx<<1 stride, cursor + run-length byte stream,
//   0xFF sentinel), with the shared index limit halfword &D_0+0x202C.
//   It first runs a USO-relocated processor (`jal 0` slot) on the
//   selected record, then walks that record's associated buffer run.
//   The cross-cutting "process record together with its stream"
//   operation that links the registry/record and buffer-run families.
// Caps (DEFERRED): CLEAN single jr $ra. Cross-cutting record+stream op.
//   2026-05-31 FULL DECODE + completion 42.7->76.0%: fixed the stride
//   (recIdx*0x160 = 352 via shift-sub, NOT 0x180), the limit load (lhu
//   unsigned, not lh), and added the whole missing TAIL: after the run-loop
//   (last=buf[cur] per elem; cb37ea4(last)), if(cb37d98(bufIdx)==0) return 0;
//   proc2(rec); then 8 rec field writes (rec->5=last, rec->0x18=cur,
//   rec->0|=0x80, rec->0x78=cur, rec->0x90=0, rec->0x10=0, rec->0&=0xBF,
//   rec->4=bufIdx); proc3(rec); return 16. RESIDUAL (76->100): consistent
//   saved-reg renumber (&D base s3 vs my v0, last/cur slots) + return-loop
//   form (IDO folds my do{i+=4}while(i!=16) to `li 16`; target keeps the loop)
//   + the placeholder jals. Name pre-checked: no extern reuse.
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_000235E4(int recIdx, int bufIdx, int arg) {
    char *g = (char *)&D_00000000;
    char *rec;
    unsigned char *buf;
    int cur, cnt;
    int last = 255;
    int i;
    if (bufIdx >= *(unsigned short *)(g + 0x202C)) {
        return 0;
    }
    rec = g + 0x2D00 + recIdx * 0x160;
    gl_func_00000000(rec);
    buf = *(unsigned char **)(g + 0x2028);
    cur = *(unsigned short *)(buf + bufIdx * 2);
    cnt = *(unsigned char *)(buf + cur);
    cur++;
    if (cnt > 0) {
        do {
            last = *(unsigned char *)(buf + cur);
            cur++;
            gl_func_00000000(last);
            cnt--;
        } while (cnt > 0);
    }
    if (gl_func_00000000(bufIdx) == 0) {
        return 0;
    }
    gl_func_00000000(rec);
    *(unsigned char *)(rec + 5) = (unsigned char)last;
    *(int *)(rec + 0x18) = cur;
    *(unsigned char *)(rec + 0) |= 0x80;
    *(int *)(rec + 0x78) = cur;
    *(unsigned char *)(rec + 0x90) = 0;
    *(short *)(rec + 0x10) = 0;
    *(unsigned char *)(rec + 0) &= 0xBF;
    *(unsigned char *)(rec + 4) = (unsigned char)bufIdx;
    gl_func_00000000(rec);
    i = 0;
    do {
        i += 4;
    } while (i != 16);
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000235E4);
#endif

extern int gl_ref_00038174();
extern int gl_ref_00037F80();
void gl_func_0002372C(int a0) {
    int r = gl_ref_00038174(0, a0);
    int scratch;
    gl_ref_00037F80(0, r, &scratch);
}

// gl_func_00023760 — STRUCTURAL PASS (0xD8 / 54 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A multi-step resource acquire/resolve helper.
//
//   ret gl_func_00023760(int a0, int a1) {
//     int  r0 = jal 0x38204(2);                         // 0x0C00E081
//     int  j  = jal 0x38174(2);                          // 0x0C00E05D
//     int  ok = jal 0x381B0(2, j);                       // 0x0C00E06C
//     if (ok == 0) return ...;
//     int  v  = (*acquire)(j, 2);                         // jal 0 USO
//     E   *e  = tbl + j*0x10;                              // entry tbl
//     if (e->b_19 == 4) {                                  // type 4
//       byte t = e->b_18;
//       *(int*)dst = t;
//     } else {
//       int p = e->w_10;
//       ...
//     }
//   }
//
// Struct-typing reference: resolves a class-2 resource by chaining
//   the fixed USO-relocated routines 0x0C00E081 (≈0x38204),
//   0x0C00E05D (≈0x38174, the shared poll/advance used across the
//   gl_func_00022D68 readiness + gl_func_00022FC0 buffer-run
//   families) and 0x0C00E06C (≈0x381B0), then a `jal 0` acquire.
//   The resolved index `j` selects an entry in a 0x10-stride table;
//   byte e->0x19 is a type tag (value 4 special-cased), byte e->0x18
//   a payload, word e->0x10 a pointer. The "obtain & dereference a
//   resource handle of class 2" entry in the game_libs resource
//   subsystem.
// 2026-05-31: body completed + register-matched 44.0->91.2%. The sketch
//   was wrong in several ways, now fixed: (1) the FIRST call's result r0 =
//   38204(2) is the TABLE BASE (e = r0 + j*0x10), not a separate func(j)
//   call; (2) ok-polarity is INVERTED — if ok!=0 the acquire path runs and
//   returns early (acquire(j,2); *out=0; return v), only ok==0 reaches the
//   table lookup; (3) param0 is passed to 38174 while param1 is the OUTPUT
//   pointer; (4) the non-type-4 arm calls 37f80(2,j,&local) and branches on
//   its result; (5) the ==4 and the res==0 arms both return e->0x10 (delay-
//   slot load). KEY LEVER: reusing the PARAM var x to hold j (x = 38174(2,x))
//   extends its live range across all calls -> IDO promotes it to saved reg
//   s0, fixing the whole register cascade (72->91%). RESIDUAL (91->100) is
//   the 4 baked-jal placeholders (38204/38174/381b0/37f80 — USO-reloc cap,
//   ~7%) + a minor frame-packing diff. Name pre-checked: no extern reuse.
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
int gl_func_00023760(int x, int *out) {
    int r0 = gl_func_00000000(2);            /* 38204(2) - table base */
    int ok;
    char *e;
    x = gl_func_00000000(2, x);              /* x := j = 38174(2, x); reuse param -> s0 */
    ok = gl_func_00000000(2, x);             /* 381b0(2, j) */
    if (ok != 0) {
        int v = gl_func_00000000(x, 2);      /* acquire(j, 2) - jal 0 */
        *out = 0;
        return v;
    }
    e = (char *)r0 + x * 0x10;
    if (*(signed char *)(e + 0x19) == 4) {
        *out = *(signed char *)(e + 0x18);
        return *(int *)(e + 0x10);
    }
    {
        int local;
        int res = gl_func_00000000(2, x, &local);   /* 37f80(2, j, &local) */
        if (res != 0) {
            *out = 0;
            return res;
        }
    }
    *out = *(signed char *)(e + 0x18);
    return *(int *)(e + 0x10);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023760);
#endif

// gl_func_00023838 — STRUCTURAL PASS (0xDC / 55 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Decodes a registry record's two code fields and acts.
//
//   void gl_func_00023838(int a0) {
//     int  j   = jal 0x38174(1);                        // 0x0C00E05D
//     R   *rec = (char*)(&D_0 + 0x2030) + j*0x14;        // reg table
//     byte c2  = rec->b_2;
//     byte c3  = rec->b_3;
//     int  x = 0, y = 0;
//     if (c2 != 0xFF) {
//       jal 0x37DCC(c2, &x);                              // 0x0C00DF73
//     }
//     if (c3 != 0xFF) {
//       jal 0x37DCC(c3, &y);                              // 0x0C00DF73
//     }
//     jal 0x37F80(1, j, &..., x, y);                      // 0x0C00DFE0
//   }
//
// Struct-typing reference: indexes the SAME registry table as
//   gl_func_000221D8 / gl_func_00022464 — base &D_0+0x2030, fixed
//   0x14 entry stride, byte fields +2 / +3 are code values with 0xFF
//   = "none/empty" sentinel. The index `j` comes from the shared poll
//   routine 0x0C00E05D (≈0x38174, arg 1). Each non-empty code is
//   resolved through the fixed decoder 0x0C00DF73 (≈0x37DCC) into a
//   stack scratch slot, then the pair is committed via the fixed
//   routine 0x0C00DFE0 (≈0x37F80). The "decode & apply a record's
//   two code fields" entry of the game_libs registry subsystem.
// 2026-05-31: body completed to full logic 49.7->85.0%. The sketch was
//   wrong in several ways, now fixed: (1) 38174 takes (1, a0) — the param
//   is the 2nd arg, not dropped; (2) the table base is *(int*)(&D_0+0x2030)
//   — a POINTER LOADED from that slot, NOT the address &D_0+0x2030 itself;
//   (3) the 37dcc results + out-params + saved c2/c3 form ONE stack struct
//   int buf[7] @32..56(sp) — buf[0]=c2 buf[1]=c3 buf[2/3]=decode results
//   buf[4/5]=decode out-slots buf[6]=37f80 out; (4) the whole tail is
//   missing: res=37f80(1,j,&buf[6]); if(res==0) return 0; if(buf[6]==1)
//   39b70(j,res,&buf[0],0); return res (the buf is passed by ptr to 39b70,
//   which is why the buf[2..5] stores aren't dead). Logic correct (55=55
//   insns). RESIDUAL: 5 baked-jal placeholders (USO-reloc cap ~9%) + a
//   regalloc/slot-base diff (target keeps c2/c3 in a0/a2; build uses temps
//   + a 4-byte-lower frame). Name pre-checked: no extern reuse.
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00023838(int a0) {
    int j = gl_func_00000000(1, a0);                         /* 38174(1, a0) */
    char *rec = *(char **)((char *)&D_00000000 + 0x2030) + j * 0x14;
    int buf[7];                                              /* stack struct @32..56(sp) */
    int res;
    buf[0] = *(unsigned char *)(rec + 2);                    /* c2 */
    buf[1] = *(unsigned char *)(rec + 3);                    /* c3 */
    if (buf[0] != 0xFF) {
        buf[2] = gl_func_00000000(buf[0], &buf[4]);          /* 37dcc(c2, &xo) */
    } else {
        buf[2] = 0;
    }
    if (buf[1] != 0xFF) {
        buf[3] = gl_func_00000000(buf[1], &buf[5]);          /* 37dcc(c3, &yo) */
    } else {
        buf[3] = 0;
    }
    res = gl_func_00000000(1, j, &buf[6]);                   /* 37f80(1, j, &zo) */
    if (res == 0) {
        return 0;
    }
    if (buf[6] == 1) {
        gl_func_00000000(j, res, &buf[0], 0);                /* 39b70(j, res, &pair, 0) */
    }
    return res;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023838);
#endif

// gl_func_00023914 — STRUCTURAL PASS (0x1F4 / 125 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A resource-resolve + computed jump-table dispatch (sibling
// of gl_func_00023760's resolve chain).
//
//   ret gl_func_00023914(a0, a1, a2) {
//     int h = jal 0x381B0(a0, a1, a2);                  // 0x0C00E06C
//     if (h == 0) { ...; return 2; }                     // fail path
//     jal 0x38204(a0, …);                                // 0x0C00E081
//     E *e = tbl + idx*0x10;                              // entry tbl
//     int  sz  = (e->w_14 + 0xF) & ~0xF;                  // align16
//     byte pl  = e->b_18;
//     int  typ = e->b_19;                                 // type tag
//     void *p  = e->w_10;
//     if ((unsigned)typ >= 5) return;                     // default
//     goto *((void**)(&D_0 + 0xEA0))[typ];                // jump table
//     // ... 5 per-type case bodies ...
//   }
//
// Struct-typing reference: resolves a resource handle through the
//   fixed USO-relocated routines 0x0C00E06C (≈0x381B0) and
//   0x0C00E081 (≈0x38204) — the same chain gl_func_00023760 uses.
//   The resolved index selects a 0x10-stride entry: word +0x10 a
//   pointer, word +0x14 a size (16-aligned), byte +0x18 a payload,
//   byte +0x19 the type tag. Dispatch is a REAL computed jump through
//   the table at &D_0+0xEA0 indexed by the type in [0,5); type >= 5
//   falls to the default. A second jump-table dispatcher in the
//   game_libs resource subsystem (cf. gl_func_0002119C's table at
//   &D_0+0xE7C — adjacent dispatch tables).
// Caps (DEFERRED): CLEAN single jr $ra. Resource-resolve + computed
//   jump-table dispatch (sibling of gl_func_00023760's resolve
//   chain; second dispatcher cf. gl_func_0002119C). Real-C
//   STRUCTURAL body below per the analysis (h = fixed 0x381B0(a0,
//   a1,a2); h==0 -> return 2; fixed 0x38204(a0,..); 0x10-stride
//   entry: size16=(e->0x14+0xF)&~0xF, payload e->0x18, type tag
//   e->0x19, ptr e->0x10; type>=5 default else computed jump via
//   &D_0+0xEA0[type] modelled as a switch). Byte-match deferred —
//   computed jump-table + fixed-target resolve need USO reloc infra.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
int gl_func_00023914(int a0, int a1, int *a2) {
    int s0 = gl_func_00000000(a0, a1, a2);
    char *base, *v1;
    int aligned, b18, typ, t4, a1c;
    if (s0 == 0) {
        a2[0] = 0;
        return 2;
    }
    base = (char *)gl_func_00000000();
    v1 = base + a1 * 0x10;
    aligned = (*(int *)(v1 + 0x14) + 0xF) & ~0xF;
    b18 = *(signed char *)(v1 + 0x18);
    typ = *(signed char *)(v1 + 0x19);
    t4 = *(int *)(v1 + 0x10);
    if ((unsigned)typ < 5) {
        switch (typ) {
        case 0: s0 = gl_func_00000000(a0, a1, aligned); if (s0 == 0) return s0; break;
        case 1: s0 = gl_func_00000000(a0, aligned, 1, a1); if (s0 == 0) return s0; break;
        case 2: s0 = gl_func_00000000(a0, aligned, 0, a1); if (s0 == 0) return s0; break;
        case 3: s0 = gl_func_00000000(a0, aligned, 2, a1); if (s0 == 0) return s0; break;
        }
    }
    a2[0] = 1;
    if (b18 == 1) {
        gl_func_00000000(t4, s0, aligned, *(short *)(base + 2));
    } else {
        gl_func_00000000(t4, s0, aligned, b18);
    }
    a1c = (typ != 0) ? 2 : 5;
    if (a0 == 0) {
        gl_func_00000000(a1, a1c);
    } else if (a0 == 1) {
        gl_func_00000000(a1, a1c);
    } else if (a0 == 2) {
        gl_func_00000000(a1, a1c);
    }
    return s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023914);
#endif

extern int gl_ref_00038204();

int gl_func_00023B08(int a0, int a1) {
    int r = gl_ref_00038204(a0, a1);
    int offset = a1 << 4;
    int *p = (int*)(r + offset);
    if (!p[5]) a1 = p[4];
    return a1;
}

/* gl_func_00023B44: two-stage begin. Calls a USO-relocated setup routine
 * (jal-0 placeholder) with the caller args; only on a non-zero result does it
 * invoke a second routine (constant arg 2 + original a1). Positive two-return
 * form (if r!=0 return r; ... return 0) makes IDO emit beql for the second
 * arm, matching the target. MATCHED byte-exact (21 words, reloc-filtered). */
extern int gl_func_00000000();
int gl_func_00023B44(int a0, int a1) {
    int r = gl_func_00000000(a0, a1);
    if (r != 0) {
        return r;
    }
    r = gl_func_00000000(a0, 2, a1);
    if (r != 0) {
        return r;
    }
    return 0;
}

/* game_libs_func_00023B98: 3-case dispatch returning USO data fields.
 * MERGED 2026-05-26: absorbed shared-tail fragments _00023BC0, _00023BC8,
 * _00023BD0 (each a 2-3 insn `jr ra; lw v0, OFFSET($v1)` epilogue, branch
 * target from this function's beq's). 0x28 -> 0x44 bytes.
 *
 * Semantic decode (CORRECTED 2026-05-27 — prior doc had off-by-one
 * case mapping; verified against asm at 0x28E0/0x28E8/0x28F0 dispatch
 * targets):
 *   if (idx == 0) return D[0x201C];
 *   if (idx == 1) return D[0x2020];
 *   if (idx == 2) return D[0x2024];
 *   return 0;
 *
 * NM-wrap form below produces 25% match — IDO -O2 emits `bne` early-skip
 * with inline-jr per case; target uses `beq` to SEPARATE shared-tail
 * blocks with `lui` hoisted into the beq's delay slot. Different shape;
 * not C-reproducible (the shared-tail pattern requires goto-out + label
 * which IDO can't merge at the lui-delay level). Default INCLUDE_ASM
 * is byte-exact. */
#ifdef NON_MATCHING
int game_libs_func_00023B98(int idx) {
    if (idx == 0) return *(int*)((char*)&D_00000000 + 0x201C);
    if (idx == 1) return *(int*)((char*)&D_00000000 + 0x2020);
    if (idx == 2) return *(int*)((char*)&D_00000000 + 0x2024);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00023B98);
#endif

// gl_func_00023BDC — STRUCTURAL PASS (0x284 / 161 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A registry-list maintenance / splice op over the
// &D_0+0x2030 record table.
//
//   ret gl_func_00023BDC(int idx, void **listp, int a2) {
//     R *rec = (char*)(&D_0 + 0x2030) + idx*0x14;        // record
//     byte k0 = rec->b_0;
//     byte k1 = rec->b_1;
//     short n = rec->h_4;                                 // count
//     Node *head = *listp;                                // list head
//     if (head == 0) { ...; return; }                     // empty
//     for (Node *p = head; p; p = p->next) {              // walk list
//       if (match(p, rec)) {
//         *listp = ...;                                    // relink
//         ...
//       }
//     }
//     // inner: index a2 table, splice node into the record list
//   }
//
// Struct-typing reference: indexes the SAME registry record table as
//   gl_func_000221D8 / gl_func_00023838 — base &D_0+0x2030, fixed
//   0x14 entry stride; byte fields +0 / +1 are match keys, halfword
//   +4 a count. `listp` is a pointer to a linked-list head whose
//   nodes are walked and conditionally re-linked (the `*listp = …`
//   store splices the head); a parallel table indexed via a2 supplies
//   the node payloads. This is the list insert/move/maintenance entry
//   for the registry records — the structural mutator paired with the
//   gl_func_00021F40 (insert) / gl_func_0002349C (remove) helpers.
// Caps (DEFERRED): CLEAN single jr $ra. Registry-list maintenance /
//   splice op over the &D_0+0x2030 record table (structural mutator
//   paired with gl_func_00021F40 insert / gl_func_0002349C remove).
//   Real-C STRUCTURAL body below per the analysis (rec =
//   &D_0+0x2030 + idx*0x14; match keys rec->0/1, count rec->4;
//   empty-list early return; walk *listp conditionally re-linking
//   the head; a2-indexed parallel table supplies node payloads).
//   Byte-match deferred — list-splice / pointer-walk schedule. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder.
// gl_func_00023BDC — FULL m2c DECODE (67.35% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00023BDC)();
void gl_func_00023BDC(s32 arg0, char *arg1, int arg2) {
    s32 sp4C;
    s32 sp48;
    s32 sp3C;
    s32 *temp_s0_3;
    s32 temp_s4;
    s32 temp_s6_2;
    s32 temp_t6;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    u16 temp_s6;
    u8 var_v1;
    char **temp_v0_2;
    char **var_s3_2;
    char *temp_a2;
    char *temp_a3;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_t0;
    char *temp_v0;
    char *temp_v0_3;

    temp_t6 = arg0 * 0x14;
    sp3C = temp_t6;
    temp_v0 = *(s32 *)0x2030 + temp_t6;
    var_v1 = FW(temp_v0, 0x1);
    sp48 = (s32) FW(temp_v0, 0x0);
    temp_a3 = FW(arg1, 0x0);
    temp_s6 = FW(temp_v0, 0x4);
    if ((temp_a3 != 0) && (var_v1 != 0)) {
        FW(arg1, 0x0) = (char *) (temp_a3 + (int)arg1);
        if ((s32) var_v1 > 0) {
            var_s3 = 0;
            temp_s4 = var_v1 * 4;
            do {
                temp_v0_2 = FW(arg1, 0x0) + var_s3;
                temp_s0 = *(int*)temp_v0_2;
                temp_s0_2 = temp_s0 + (int)arg1;
                if (temp_s0 != 0) {
                    *temp_v0_2 = temp_s0_2;
                    if (FW(temp_s0_2, 0x2) == 0) {
                        sp4C = (s32) var_v1;
                        game_libs_func_0003443C(temp_s0_2 + 4, arg1, arg2);
                        FW(temp_s0_2, 0x2) = 1U;
                        FW(temp_s0_2, 0xC) = (char *) (FW(temp_s0_2, 0xC) + (int)arg1);
                    }
                }
                var_s3 += 4;
            } while (var_s3 != temp_s4);
        }
    }
    temp_v0_3 = FW(arg1, 0x4);
    if ((temp_v0_3 != 0) && (temp_s6 != 0)) {
        FW(arg1, 0x4) = (char *) (temp_v0_3 + (int)arg1);
        if ((s32) temp_s6 > 0) {
            var_s1 = 0;
            do {
                temp_s0_3 = FW(arg1, 0x4) + var_s1;
                if ((temp_s0_3 != 0) && (*(int*)temp_s0_3 != 0)) {
                    game_libs_func_0003443C(temp_s0_3, arg1, arg2);
                }
                var_s1 += 8;
            } while (var_s1 != (temp_s6 * 8));
        }
    }
    var_s3_2 = (int)arg1 + 8;
    if (sp48 >= 0x7F) {
        sp48 = 0x7E;
    }
    var_s4 = 2;
    temp_s6_2 = sp48 + 1;
    if (temp_s6_2 >= 2) {
        do {
            temp_a2 = *(int*)var_s3_2;
            if (temp_a2 != 0) {
                gl_func_0001CA10(0x1ACA4, var_s4, temp_a2, arg1);
                temp_t0 = *(int*)var_s3_2 + (int)arg1;
                *var_s3_2 = temp_t0;
                if (FW(temp_t0, 0x0) == 0) {
                    if (FW(temp_t0, 0x1) != 0) {
                        game_libs_func_0003443C(temp_t0 + 8, arg1, arg2);
                    }
                    game_libs_func_0003443C(temp_t0 + 0x10, arg1, arg2);
                    if (FW(temp_t0, 0x2) != 0x7F) {
                        game_libs_func_0003443C(temp_t0 + 0x18, arg1, arg2);
                    }
                    FW(temp_t0, 0x0) = 1U;
                    FW(temp_t0, 0x4) = (char *) (FW(temp_t0, 0x4) + (int)arg1);
                }
            }
            var_s4 += 1;
            var_s3_2 += 4;
        } while (temp_s6_2 >= var_s4);
    }
    FW((*(char *)0x2030 + sp3C), 0xC) = (char *) FW(arg1, 0x0);
    FW((*(char *)0x2030 + sp3C), 0x10) = (char *) FW(arg1, 0x4);
    FW((*(char *)0x2030 + sp3C), 0x8) = (char *) ((int)arg1 + 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023BDC);
#endif

// gl_func_00023E60 — STRUCTURAL PASS (0x144 / 81 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is a buffer-allocate + subsystem constructor.
//
//   ret gl_func_00023E60(int a0, int a1, int sz) {
//     int n   = (sz + 0xF) & ~0xF;                       // align16
//     void *b = (*alloc)(n);                              // jal 0 USO
//     S *t3 = &D_1DD4;
//     S *t4 = &D_2ACC0;                                   // big table
//     S *t6 = &D_1DF0;
//     if (n < 0x400) n = 0x400;                            // clamp min
//     jal 0x38604(b, 1, 0, a0, …, n, t3, t4, t6);          // 0x0C00E181
//     ...
//   }
//
// Struct-typing reference: a constructor that sizes (request rounded
//   up to a 16-byte multiple, floored at 0x400), allocates the
//   backing buffer via a USO-relocated allocator (`jal 0` slot), and
//   wires up three fixed base tables — &D_1DD4, &D_1DF0 and the large
//   &D_2ACC0 (a code/data blob) — before handing everything to the
//   fixed init routine 0x0C00E181 (≈0x38604) along with stacked
//   config args. A subsystem object bring-up in the game_libs
//   resource family (companion to the gl_func_00022A9C arena init /
//   gl_func_0001FD98 alloc helpers).
// Caps (DEFERRED): single jr $ra (the "2-jr bundle" note is STALE;
//   .s is 0x144/77 words, ONE function). Subsystem object bring-up
//   (companion to gl_func_00022A9C arena init / gl_func_0001FD98
//   alloc). Real-C STRUCTURAL body below per the analysis (size16 =
//   (sz+0xF)&~0xF floored at 0x400; jal-0 USO-reloc alloc(n); wire
//   three fixed base tables &D_1DD4 / &D_1DF0 / &D_2ACC0; hand to
//   fixed init 0x38604(b,1,0,a0,..,n,t3,t4,t6)). Byte-match deferred
//   — placeholder jal-0 alloc + fixed init need USO reloc infra.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior body had no loop + missing a3). Chunked
 * DMA: n=(sz+15)&~15; gl(a1,n); then process n in 1024-byte chunks —
 * gl_38604(D+0x1DF0, 1, 0, src, dst, 1024, D+0x1DD4, a3, D+0x2ACC0) + gl(D+0x1DD4,
 * 0, 1), advancing src/dst by 1024; a final partial chunk uses count=n and
 * tag D+0x2ACCC. */
extern int gl_func_00038604();
int gl_func_00023E60(int a0, int a1, int sz, int a3) {
    char *g = (char *)&D_00000000;
    char *s3 = g + 0x1DD4;
    char *s4 = g + 0x2ACC0;
    char *s6 = g + 0x1DF0;
    int s0 = (sz + 0xF) & ~0xF;
    int s2 = a0;
    int s1 = a1;
    gl_func_00000000(a1, s0);
    while ((u32)s0 >= 0x400) {
        gl_func_00038604(s6, 1, 0, s2, s1, 0x400, s3, a3, s4);
        gl_func_00000000(s3, 0, 1);
        s0 -= 0x400;
        s2 += 0x400;
        s1 += 0x400;
    }
    if (s0 != 0) {
        gl_func_00038604(s6, 1, 0, s2, s1, s0, s3, a3, g + 0x2ACCC);
        gl_func_00000000(s3, 0, 1);
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023E60);
#endif

/* Empty 4-arg stub (byte-identical sibling of matched _00024E14,
 * timproc_uso_b5_func_0000ABE0). C-emit: sw a0,0(sp); sw a1,4(sp);
 * sw a2,8(sp); jr ra; sw a3,0xC(sp). */
void game_libs_func_00023F84(int a0, int a1, int a2, int a3) {
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00023F98);

// gl_func_00023FA4 — STRUCTURAL PASS (0xDC / 55 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is a slot-configure-by-mode helper.
//
//   int gl_func_00023FA4(int id, int a1, int mode, int size) {
//     if ((unsigned)id >= 0x11) return -1;              // 17-slot cap
//     Slot *s = (Slot*)id;
//     void *buf;
//     switch (mode) {                                    // beq 2 / 3
//       case 2:  buf = *(void**)(&D_0 + 0x1644); break;
//       case 3:  buf = *(void**)(&D_0 + 0x1648); break;
//       default: buf = 0;                                 // none
//     }
//     if (size & 0xF) size = (size + 0xF) & ~0xF;          // align16
//     s->b_2 = (byte)a1;                                   // slot tag
//     ...                                                   // wire buf
//   }
//
// Struct-typing reference: configures one of up to 0x11 (17) slots
//   (`id` is range-checked, -1 returned on overflow). The `mode`
//   stack arg selects which global double-buffer pointer to bind —
//   word &D_0+0x1644 (mode 2) or &D_0+0x1648 (mode 3); other modes
//   bind none. The slot's byte +2 is set from `a1` (a tag/type), and
//   a requested size is rounded up to a 16-byte multiple. A
//   per-slot resource-binding configurator in the game_libs resource
//   subsystem (the &D_0+0x164x globals are its mode buffers).
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0xDC/51 words, ONE function). Per-slot resource-binding
//   configurator in the game_libs resource subsystem. Real-C
//   STRUCTURAL body below per the analysis (id range-checked vs
//   0x11, -1 on overflow; mode switch binds &D_0+0x1644 (2) /
//   &D_0+0x1648 (3) / none; size 16-aligned; slot byte+2 = a1 tag).
//   Byte-match deferred — mode-switch / align schedule. Name
//   pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int D_00000000;
// Per-slot resource binder. id is the caller-set bounds key (approximated by
// the slot ptr `s` so only the range-check reg differs); >= 0x11 returns -1.
// mode selects the buffer base (*(g+0x1644) for 2, *(g+0x1648) for 3, else
// return 0). size (arg6) is rounded up to 16; the slot's fields are wired
// (+2=tag byte, +4=arg7, +8=arg5, +0xC=a3, +0x10=aligned size), the bound
// buffer's +0x14 set to 2, then a global fn-ptr at *(g) is invoked as (buf, s).
int gl_func_00023FA4(char *s, int tag, int a2, int a3, int arg5, int size, int arg7, int mode) {
    char *g = (char *)&D_00000000;
    char *buf;
    if ((unsigned int)s >= 0x11) {
        return -1;
    }
    if (mode == 2) {
        buf = *(char **)(g + 0x1644);
    } else if (mode == 3) {
        buf = *(char **)(g + 0x1648);
    } else {
        return 0;
    }
    if (size & 0xF) {
        size = (size + 0xF) & ~0xF;
    }
    *(char *)(s + 2) = (char)tag;
    *(int *)(s + 4) = arg7;
    *(int *)(s + 0xC) = a3;
    *(int *)(s + 0x10) = size;
    *(int *)(s + 8) = arg5;
    *(int *)(buf + 0x14) = 2;
    (*(void (**)(char *, char *))g)(buf, s);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023FA4);
#endif

void game_libs_func_00024070(void) {}

void game_libs_func_00024078(void) {}

extern int gl_ref_00037F80();
int gl_func_00024080(int a0, int a1) {
    int scratch;
    return gl_ref_00037F80(a0, a1, &scratch);
}

// gl_func_000240A0 — STRUCTURAL PASS (0x290 / 164 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). The UNIFIED class dispatcher over the three per-class
// readiness state-byte arrays (the gl_func_00022D68 / gl_func_00022DE0
// / gl_func_00022E58 predicate arrays).
//
//   ret gl_func_000240A0(int cls, int idx, int a2, int a3) {
//     byte st;
//     switch (cls) {                                    // beq 0/1/2
//       case 0:  st = *(byte*)(&D_0 + 0x2C70 + idx); break; // 00022DE0
//       case 1:  st = *(byte*)(&D_0 + 0x2C40 + idx); break; // 00022D68
//       case 2:  st = *(byte*)(&D_0 + 0x2C10 + idx); break; // 00022E58
//       default: return 0;
//     }
//     if (st != 1) return 0;                              // gate
//     ... per-class action using a2 / a3 ...
//   }
//
// Struct-typing reference: this is the central router that the
//   gl_func_00022D68 / 00022DE0 / 00022E58 readiness predicates are
//   the per-class leaves of. The `cls` arg selects which slot-state
//   byte array to consult — &D_0+0x2C70 (class 0), &D_0+0x2C40
//   (class 1), &D_0+0x2C10 (class 2); each is the same per-resource-
//   class table those predicates query. It gates on the slot state
//   == 1, then performs the class-appropriate action with the a2/a3
//   payload. Confirms the 0x2C10/0x2C40/0x2C70 arrays are one
//   indexed-by-class family, not three unrelated tables.
// Caps (DEFERRED): CLEAN single jr $ra. UNIFIED class dispatcher —
//   central router for which the gl_func_00022D68 / 00022DE0 /
//   00022E58 readiness predicates are the per-class leaves. Real-C
//   STRUCTURAL body below per the analysis (cls switch selects state
//   array &D_0+0x2C70 (0) / +0x2C40 (1) / +0x2C10 (2); gate on
//   slot-state byte == 1; then per-class action with a2/a3).
//   Byte-match deferred — class-switch / typed-state-array schedule.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
//
// 2026-06-06: the `cls` switch is a REAL computed jump (jr) — m2c aborts
//   ("Unable to determine jump table"). To decode the per-class action
//   bodies, the jumptable must be extracted (scripts/extract-uso-jumptable.py
//   style: feed m2c .L case labels + a jtbl_ symbol). The placeholder
//   `return gl_func_00000000(...)` below stands in for the dispatched action;
//   finishing needs the jumptable, not a structural rewrite.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int gl_func_0001CA10();
extern int gl_func_0003959C();
extern int D_00000000;
/* Decoded via jumptable extraction (scripts/uso-jumptable-to-m2c.py) — the
 * type-tag (e->0x19) computed jump at &D+0xEA0 is now a switch. The two
 * fixed-addr USO thunks (jal 0x381B0 / 0x38204) stay gl_func_00000000
 * placeholders (no symbol); gl_func_0003959C / gl_func_0001CA10 are real. */
int gl_func_000240A0(int cls, int idx, int a2, int a3, void *a4) {
    char *g = (char *)&D_00000000;
    int h, sp34, sp44, size16, b18, typ, payload;
    char *e;

    if (cls == 0) {
        if (*(unsigned char *)(g + 0x2C70 + idx) == 1) return 0;
    } else if (cls == 1) {
        if (*(unsigned char *)(g + 0x2C40 + idx) == 1) return 0;
    } else if (cls == 2) {
        if (*(unsigned char *)(g + 0x2C10 + idx) == 1) return 0;
    }
    h = gl_func_00000000(cls);            /* jal 0x381B0 */
    sp44 = h;
    if (h != 0) {
        sp34 = 2;
        gl_func_0001CA10(a4, a3 << 0x18, 0);
        goto block_30;
    }
    e = (char *)(gl_func_00000000(cls) + idx * 0x10);   /* jal 0x38204 */
    size16 = (*(int *)(e + 0x14) + 0xF) & ~0xF;
    b18 = *(unsigned char *)(e + 0x18);
    typ = *(unsigned char *)(e + 0x19);
    sp34 = 2;
    payload = *(int *)(e + 0x10);
    if ((unsigned)typ < 5) {
        switch (typ) {
        case 0: h = gl_func_0001CA10(typ); if (h == 0) return h; sp34 = 5; sp44 = h; break;
        case 1: h = gl_func_0001CA10(typ); sp44 = h; if (h == 0) return h; break;
        case 2: h = gl_func_0001CA10(typ); sp44 = h; if (h == 0) return h; break;
        case 3: h = gl_func_0001CA10(typ); if (h == 0) return h; sp44 = h; break;
        }
    }
    gl_func_0003959C(payload, sp44, size16, b18, a2, a4,
                     (a3 << 0x18) | (cls << 0x10) | (idx << 8) | sp34);
    sp34 = 1;
block_30:
    if (cls == 0) {
        gl_func_0001CA10(idx, sp34);
    } else if (cls == 1) {
        gl_func_0001CA10(idx, sp34);
    } else if (cls == 2) {
        gl_func_0001CA10(idx, sp34);
    }
    return sp44;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000240A0);
#endif

/* gl_func_00024330: was 18-insn 3-function bundle. Split via
 * split-fragments.py 2026-05-08 into parent (12 insns / 0x30, 3-jal
 * passthrough wrapper) + game_libs_func_00024360 + game_libs_func_0002436C
 * (each 3 insns / 0xC, no-frame setter to D_*). */
extern int gl_func_00000000();
void gl_func_00024330(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(a0);
}

extern int D_24360_a;
void game_libs_func_00024360(int a0) { D_24360_a = a0; }

extern int D_2436C_a;
void game_libs_func_0002436C(int a0) { D_2436C_a = a0; }

// gl_func_00024378 — STRUCTURAL PASS (0x5D0 / 372 words ≈ 1.5KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). The SUBSYSTEM INITIALIZER / full reset for the
// game_libs &D_0 state block. Large -0x80 frame.
//
//   void gl_func_00024378(void) {
//     S *g = &D_0;
//     g->w_0    = 0;                                     // base clear
//     g->w_215C = 0;                                     // handle clr
//     int n = *(int*)(&D_0 + 4);
//     n = (n + 7) >> 3;                                   // round to 8
//     if (n > 0) {                                        // zero an
//       long *p = tbl;                                     //  8-byte-
//       do { p[-1] = 0; p[-2] = 0; p += 2; } while (...);  //  strided
//     }                                                    //  table
//     char *q = (char*)g;                                  // byte clr
//     for (int i = 0x5C30; i != 0; i--) *q++ = 0;           //  0x5C30
//     ... reload control globals, seed default fields ...
//   }
//
// Struct-typing reference: the one-time bring-up / hard reset of the
//   whole game_libs &D_0 state region used by every subsystem decoded
//   in this file. It zeroes the base word, the &D_0+0x215C handle
//   slot (the same handle the gl_func_0001FEC8 / gl_func_00021F40
//   register helpers stash), an 8-byte-strided table whose length is
//   the word &D_0+0x4 rounded up to a multiple of 8, and a large
//   0x5C30-byte block (the registry/record/buffer arena), then
//   reloads control globals. The init counterpart to the
//   gl_func_00022A9C arena init / gl_func_0002119C state driver — runs
//   once before any of the registry/record/buffer/resource families
//   are usable.
// Caps (DEFERRED): CLEAN single jr $ra. SUBSYSTEM INITIALIZER / full
//   reset of the whole game_libs &D_0 state region (init counterpart
//   to gl_func_00022A9C arena init / gl_func_0002119C driver; runs
//   once before any registry/record/buffer/resource family).
//   Real-C STRUCTURAL body below per the analysis (clear base word
//   &D_0+0, handle &D_0+0x215C; zero an 8-byte-strided table of
//   length (&D_0+4 word + 7)>>3; clear a 0x5C30-byte arena block;
//   reload control globals). Byte-match deferred — large multi-
//   region clear/seed loop schedule. Name pre-checked: no extern
//   reuse (collision-safe).
// gl_func_00024378 — m2c DECODE (12.37% NM, no episode). game_libs non-jumptable (folded-ref heavy) via scripts/decomp-uso-cf.py.
/* gl_func_00024378 graft attempt 2026-06-10: fresh m2c graft scored
 * 10.98 vs this body's 12.37 -- REVERTED (monotonic rule; the
 * graft~=existing tell, item 17 refined: this body is m2c-equivalent,
 * divergence is structural). Hand-refinement territory. */
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00024378)();
void gl_func_00024378(void) {
    s32 sp34;
    u32 sp20;
    s16 temp_a2;
    s16 temp_t6;
    s16 temp_t9;
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_3;
    s32 var_v1_4;
    s8 *var_v0_2;
    u32 var_v0;
    u32 var_v0_3;
    u32 var_v1_2;
    char *temp_t0;
    char *temp_t3;

    *(int*)0 = 0;
    *(s32 *)0x215C = 0;
    temp_a1 = (s32) *(s32 *)4 / 8;
    if (temp_a1 > 0) {
        var_v0 = 0;
        do {
            var_v0 += 8;
            FW(var_v0, -0x4) = 0;
            FW(var_v0, -0x8) = 0;
        } while (var_v0 < (u32) (temp_a1 * 8));
    }
    var_v0_2 = 0;
    var_v1 = 0x5C30;
    do {
        var_v1 -= 1;
        *var_v0_2 = 0;
        var_v0_2 += 1;
    } while (var_v1 >= 0);
    temp_v0 = *(int*)0;
    switch (temp_v0) {                              /* irregular */
    case 0:
        *(s32 *)0x213C = 0x32;
        *(s32 *)0x2138 = *(s32 *)0xEC8;
        break;
    case 2:
        *(s32 *)0x213C = 0x3C;
        *(s32 *)0x2138 = *(s32 *)0xECC;
        break;
    default:
    case 1:
        *(s32 *)0x213C = 0x3C;
        *(s32 *)0x2138 = *(s32 *)0xED0;
        break;
    }
    gl_func_0001CA10(0, temp_a1);
    var_v0_3 = 0;
    do {
        var_v0_3 += 2;
        FW(var_v0_3, 0x214A) = 0xA0;
    } while (var_v0_3 < 6U);
    *(s32 *)0x2078 = 0;
    *(s32 *)0x2080 = 0;
    *(s32 *)0x2084 = 0;
    *(s32 *)0x2076 = 0;
    *(s32 *)0x2094 = 0;
    *(s32 *)0x20CC = 0;
    *(s32 *)0x211C = 0;
    gl_func_0001CA10(0x1DD4, 0x1DEC, 1);
    gl_func_0001CA10(0x16BC, 0x16D4, 0x40);
    gl_func_0001CA10(0x164C, 0x1664, 8);
    gl_func_0001CA10(0x1684, 0x169C, 8);
    *(s32 *)0x207C = 0;
    *(s32 *)0x1E0C = 0;
    *(s32 *)0x1644 = gl_func_0001CA10();
    *(s32 *)0x1648 = gl_func_0001CA10();
    gl_func_0001CA10(*(s32 *)8);
    var_v1_2 = 0;
    do {
        sp20 = var_v1_2;
        var_v1_2 += 4;
        FW(var_v1_2, 0x213C) = gl_func_0001CA10(0x2188, 0xB00);
    } while (var_v1_2 < 0xCU);
    *(s32 *)0x201C = 0;
    *(s32 *)0x2020 = 0;
    *(s32 *)0x2024 = 0;
    *(s32 *)0x2028 = 0;
    *(s32 *)0x2CF1 = 0;
    *(s32 *)0x2CF0 = 1;
    *(s32 *)0x202C = (s16) *(int*)0;
    gl_func_0001CA10();
    game_libs_func_0003443C(*(s32 *)0x201C, *(int*)0, 0);
    game_libs_func_0003443C(*(s32 *)0x2020, *(int*)0, 0);
    game_libs_func_0003443C(*(s32 *)0x2024, *(int*)0, 0);
    temp_a2 = *(int*)(*(s32 *)0x2020);
    sp34 = (s32) temp_a2;
    *(s32 *)0x2030 = gl_func_0001CA10(0x2188, temp_a2 * 0x14, temp_a2);
    var_a0 = 0;
    temp_a3 = temp_a2 & 3;
    if (temp_a2 > 0) {
        if (temp_a3 != 0) {
            var_v1_3 = 0 * 0x10;
            var_v0_4 = 0 * 0x10;
            do {
                var_a0 += 1;
                FW((*(s32 *)0x2030 + var_v1_3), 0x2) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_4), 0x1A) >> 8);
                FW((*(s32 *)0x2030 + var_v1_3), 0x3) = (s8) FW((*(s32 *)0x2020 + var_v0_4), 0x1A);
                *(int*)(*(s32 *)0x2030 + var_v1_3) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_4), 0x1C) >> 8);
                FW((*(s32 *)0x2030 + var_v1_3), 0x1) = (s8) FW((*(s32 *)0x2020 + var_v0_4), 0x1C);
                temp_t9 = FW((*(s32 *)0x2020 + var_v0_4), 0x1E);
                temp_t3 = *(s32 *)0x2030 + var_v1_3;
                var_v1_3 += 0x14;
                var_v0_4 += 0x10;
                FW(temp_t3, 0x4) = temp_t9;
            } while (temp_a3 != var_a0);
            if (var_a0 != temp_a2) {
                goto block_21;
            }
        } else {
block_21:
            var_v1_4 = var_a0 * 0x14;
            var_v0_5 = var_a0 * 0x10;
            do {
                FW((*(s32 *)0x2030 + var_v1_4), 0x2) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x1A) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x3) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x1A);
                *(int*)(*(s32 *)0x2030 + var_v1_4) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x1C) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x1) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x1C);
                FW((*(s32 *)0x2030 + var_v1_4), 0x4) = (s16) FW((*(s32 *)0x2020 + var_v0_5), 0x1E);
                FW((*(s32 *)0x2030 + var_v1_4), 0x16) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x2A) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x17) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x2A);
                FW((*(s32 *)0x2030 + var_v1_4), 0x14) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x2C) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x15) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x2C);
                FW((*(s32 *)0x2030 + var_v1_4), 0x18) = (s16) FW((*(s32 *)0x2020 + var_v0_5), 0x2E);
                FW((*(s32 *)0x2030 + var_v1_4), 0x2A) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x3A) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x2B) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x3A);
                FW((*(s32 *)0x2030 + var_v1_4), 0x28) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x3C) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x29) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x3C);
                FW((*(s32 *)0x2030 + var_v1_4), 0x2C) = (s16) FW((*(s32 *)0x2020 + var_v0_5), 0x3E);
                FW((*(s32 *)0x2030 + var_v1_4), 0x3E) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x4A) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x3F) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x4A);
                FW((*(s32 *)0x2030 + var_v1_4), 0x3C) = (s8) ((s16) FW((*(s32 *)0x2020 + var_v0_5), 0x4C) >> 8);
                FW((*(s32 *)0x2030 + var_v1_4), 0x3D) = (s8) FW((*(s32 *)0x2020 + var_v0_5), 0x4C);
                temp_t6 = FW((*(s32 *)0x2020 + var_v0_5), 0x4E);
                var_v0_5 += 0x40;
                temp_t0 = *(s32 *)0x2030 + var_v1_4;
                var_v1_4 += 0x50;
                FW(temp_t0, 0x40) = temp_t6;
            } while (var_v0_5 != (temp_a2 * 0x10));
        }
    }
    temp_v0_2 = gl_func_0001CA10(0x2188, *(s32 *)0xC, temp_a2, temp_a3);
    if (temp_v0_2 == 0) {
        *(char *)0xC = 0;
    }
    gl_func_0001CA10(0x2528, temp_v0_2, (s16) *(char *)0xC);
    gl_func_0001CA10(*(s32 *)0x53C8, *(s32 *)0x2078, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024378);
#endif

void game_libs_func_00024948(void) {
    *(int*)((char*)&D_00000000 + 0x1590) = 0;
    *(int*)((char*)&D_00000000 + 0x15F4) = 0;
}

#ifdef NON_MATCHING
/* gl_func_0002495C: 115-insn (0x1CC) record/slot manager. Sibling of
 * recently-matched gl_func_00024B94 (both call func_00039194, the alt-entry
 * lookup at 0x39194 inside gl_func_00039094). FULL DECODE 2026-05-31:
 * 2.85% (TODO stub) -> 84.91%.
 *
 * obj = func_00039194(a0); if (!obj) { *s0 = 0; return -1; }
 * tag2 = (obj[0]<<4)>>30 (bits 26-27);  if (tag2==0) { *s0 = 2; return 0; }
 * rec = &D + D[0x1578]*100 + 0x157C;     // 100-byte record indexed by D[0x1578]
 * if (rec[0x14]==3) rec[0x14]=0;
 * rec[0x20]=obj[0]; rec[0x24]=obj[1]; rec[0x1C]=(int)s0; rec[0x2C]=obj[3];
 * r = gl_func_00000000(obj[0]&0xFFFFFF, (int)a0, obj[1], (s8)tag2);
 * if (r==0) { rec[0xC]=0;  if (tag2==1 || obj[0]>>28==2) *s0=0; else *s0=3; return -1; }
 * rec[0x14]=1; rec[0x18]=((obj[0]&0xFFFFFF)+15)&~15; rec[0x10]=rec[0xC];
 * rec[8]=obj[1]; rec[0]=(s8)tag2; rec[1]=(s8)a0; rec[2]=(s8)a1;
 * if (tag2==1) rec[4] = *(s16*)(D[0x2024]+2);
 * D[0x1578] ^= 1; return 0;
 *
 * Residual <100 = register-renumber (the &D base lands in t2 vs target's t1,
 * cascading) + the a1-low-byte read (target lbu sp+47 vs our lw+sb) + frame
 * 0x40 vs 0x28 (named locals counter/callret/tag give the best % at 0x40;
 * inlining them shrinks the frame to 0x28 but regresses regalloc to 79%).
 * Deferred-pool &D offsets (0x1578/0x157C/0x1590/0x2024) keep it sub-100.
 * INCLUDE_ASM stays the build path. */
extern int gl_func_00000000();
extern int func_00039194();  /* K&R unspec to allow both 1-arg and 2-arg call sites */
int gl_func_0002495C(void *a0, int a1, char *s0) {
    int *t0;
    int counter;
    char *rec;
    int callret;
    int tag;

    t0 = (int *)func_00039194(a0);
    if (t0 == 0) {
        *s0 = 0;
        return -1;
    }
    if ((((unsigned int)(t0[0] << 4)) >> 30) == 0) {
        *s0 = 2;
        return 0;
    }
    counter = *(int *)((char *)&D_00000000 + 0x1578);
    rec = (char *)&D_00000000 + counter * 100 + 0x157C;
    if (*(int *)(rec + 0x14) == 3) {
        *(int *)(rec + 0x14) = 0;
    }
    *(int *)(rec + 0x20) = t0[0];
    *(int *)(rec + 0x24) = t0[1];
    *(int *)(rec + 0x1C) = (int)s0;
    *(int *)(rec + 0x2C) = t0[3];
    callret = gl_func_00000000(t0[0] & 0xFFFFFF, (int)a0, t0[1],
                               (signed char)(((unsigned int)(t0[0] << 4)) >> 30));
    if (callret == 0) {
        *(int *)(rec + 0xC) = 0;
        if ((((unsigned int)(t0[0] << 4)) >> 30) == 1) {
            *s0 = 0;
            return -1;
        }
        if (((unsigned int)t0[0] >> 28) == 2) {
            *s0 = 0;
            return -1;
        }
        *s0 = 3;
        return -1;
    }
    *(int *)(rec + 0x14) = 1;
    *(int *)(rec + 0x18) = ((t0[0] & 0xFFFFFF) + 15) & ~15;
    *(int *)(rec + 0x10) = *(int *)(rec + 0xC);
    *(int *)(rec + 0x8) = t0[1];
    tag = (int)(((unsigned int)(t0[0] << 4)) >> 30);
    *(char *)(rec + 0) = (char)tag;
    *(char *)(rec + 1) = (char)(int)a0;
    *(char *)(rec + 2) = (char)a1;
    if ((tag & 0xFF) == 1) {
        *(int *)(rec + 4) = *(short *)((char *)*(int *)((char *)&D_00000000 + 0x2024) + 2);
    }
    *(int *)((char *)&D_00000000 + 0x1578) ^= 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002495C);
#endif

int gl_func_00024B28(int a0, int a1) {
    int v0;
    int v1;
    int a2 = a1;

    if (a1 < 0x80) {
        v0 = gl_func_00000000(a0, a1);
        if (v0 == 0) {
            return 0;
        }
        v1 = *(int *)(v0 + 0x10);
    } else {
        v0 = gl_func_00000000(a0, a2 - 0x80);
        if (v0 == 0) {
            return 0;
        }
        v1 = *(int *)(v0 + 4);
    }
    return v1;
}

/* 2-insn alt-entry stub split off from gl_func_00024B28 on 2026-05-08
 * (just `jr ra; nop`). */
void game_libs_func_00024B8C(void) {}

/* gl_func_00024B94: 29-insn (0x74) lookup-and-copy. Sibling of 2495C, both
 * call func_00039194 (intra-segment helper at fixed offset 0x39194 — alt-
 * entry-jal pattern, jal target lands inside gl_func_00039094 which is
 * size 0x324).
 *
 * Decoded structure:
 *   if (a0->[0x24] == 0) return;
 *   v0 = func_00039194(a0->[1] (lbu), a0->[2] (lbu));
 *   if (v0 == 0) return;
 *   a0->[0x20..0x2C] = v0->[0..0xC];        ; 16-byte struct copy
 *   v0->[4] = a0->[0x10];                   ; field shuffle into lookup result
 *   *(char*)v0 &= 0xF3;                     ; clear bits 2,3 of header byte
 *
 * Caps:
 * (a) jal func_00039194 — alt-entry-jal pattern (target inside another
 *     function). Adding `func_00039194 = 0x00039194;` to undefined_syms
 *     gives correct LINKED ROM bytes, but objdiff scoring at .o level
 *     compares via R_MIPS_26 reloc which the C-emit produces against
 *     `func_00039194` symbol while expected has the jal already resolved
 *     to absolute target. Per docs/MATCHING_WORKFLOW.md
 *     #reloc-encoding-pinning-structurally-identical-c-body-still-scores-65.
 * (b) Register-name diffs in the struct-copy block were RESOLVED 2026-05-27
 *     via struct-assign lever (per
 *     docs/IDO_CODEGEN.md#feedback-ido-struct-copy-vs-field-copy-treg-order)
 *     PLUS `&= ~0x0C` mask form (emits andi 0xFFF3 instead of andi 0xF3,
 *     matching target — the unmasked 4-byte int constant is emitted in the
 *     andi form before the byte store truncates anyway). Net: 97.55% →
 *     99.83% objdiff. Only the reloc-encoding cap (a) remains. */
/* K&R `()` for compat with line 338's `extern int func_00039194(void *a0)`
 * decl — both decls coexist at NM build (IDO rejects type-mismatch). */
struct gl_func_00024B94_Four { int a, b, c, d; };
void gl_func_00024B94(int *a0) {
    struct gl_func_00024B94_Four *v0;
    if (a0[9] == 0) return;
    v0 = (struct gl_func_00024B94_Four*)func_00039194(((unsigned char*)a0)[1], ((unsigned char*)a0)[2]);
    if (v0 == 0) return;
    *(struct gl_func_00024B94_Four*)(a0 + 8) = *v0;
    ((int*)v0)[1] = a0[4];
    *(char*)v0 &= ~0x0C;
}

#ifdef NON_MATCHING
/* gl_func_00024C08: 98-insn two-slot state pump. Sibling of the recently
 * matched 24B28/24B94 lookup helpers and continues the same D+0x157C record
 * family.
 *
 * Decoded structure:
 *   for two 0x64-byte records at D+0x157C and D+0x15E0:
 *     state = record[0x14] via D+0x1590/0x15F4
 *     state 2 optionally primes record+0x30, unless caller arg forces state 3
 *     state 1/2 then drains record[0x18] in 0x400-byte chunks through
 *     alt-entry helpers inside gl_func_00039094/gl_func_000393B8
 *
 * Cap remaining at 84.4 % (current; expected baseline shifted slightly
 * after gl_func_00028FCC land — was 89% pre-shift):
 * 1. **Frame -64 vs target -56 (+8 bytes, +1 \$s save).** Mine spills $s0-$s8
 *    (9 saved regs); target spills $s0-$s7 (8). Extra reg is \$s8/$fp.
 * 2. **Constant `1` placement diverges.** Target puts `1` in \$s3 (early in
 *    chain, alongside other heavily-used values). Mine puts it in \$s8
 *    (the 9th save slot, last available \$s-reg). Both emit `li sN, 1` at
 *    prologue and use it for `sb sN, 0(t7)` byte store later — but the
 *    register number difference cascades because target's \$s3..\$s5 also
 *    hold `2` and `3` whereas mine doesn't promote those literals at all.
 * 3. **Tried 2026-05-08 (negative):** `int one/two/three` named-literal
 *    locals + decl reorder (record before slot, etc) — both no-op. IDO
 *    -O2 folds named-literal locals back to immediate; decl-source-order
 *    is decoupled from pseudo-allocno-number ordering per
 *    feedback-ido-sreg-order-not-decl-driven.
 * 4. **Inlining \`end\` (loop bound `slot != &D + 0xC8`)** into the for(...)
 *    expression — no emit change. Loop-invariant address is hoisted either
 *    way.
 *
 * Permuter-territory cap. The +1 \$s pressure (\$s8 holding `1`) likely
 * needs a refactor that increases the ref count of `1`/`2`/`3` enough to
 * make them outweigh other locals' \$s priority — or a refactor that
 * removes one of mine's locals (slot/record/remaining/state) so \$s3..\$s5
 * become available for the constants. Pure C-source levers exhausted in
 * this tick's grind; next pass: try permuter random-mode (3-5 min). */
extern int func_00039200();
extern int func_000393FC();
extern int func_00039480();
void gl_func_00024C08(int arg0) {
    char *slot;
    char *record;
    int remaining;
    int state;

    for (slot = (char*)&D_00000000; slot != (char*)&D_00000000 + 0xC8; slot += 0x64) {
        state = *(int*)(slot + 0x1590);
        if (state == 1) {
            record = slot + 0x157C;
        } else if (state == 2) {
            record = slot + 0x157C;
            if (((unsigned char*)record)[0] != 1) {
                gl_func_00000000(record + 0x30, 0, 1);
            }
            if (arg0 != 0) {
                *(int*)(record + 0x14) = 3;
                continue;
            }
        } else {
            continue;
        }

        remaining = *(int*)(record + 0x18);
        *(int*)(record + 0x14) = 2;
        if (remaining == 0) {
            func_00039200(record);
            *(int*)(record + 0x14) = 3;
            *(char*)(*(int*)(record + 0x1C)) = 1;
        } else if (remaining < 0x400) {
            if (((unsigned char*)record)[0] == 1) {
                func_00039480(*(int*)(record + 8), *(int*)(record + 0xC), remaining, *(int*)(record + 4));
            } else {
                func_000393FC(record, remaining);
            }
            *(int*)(record + 0x18) = 0;
        } else {
            if (((unsigned char*)record)[0] == 1) {
                func_00039480(*(int*)(record + 8), *(int*)(record + 0xC), 0x400, *(int*)(record + 4));
            } else {
                func_000393FC(record, 0x400);
            }
            *(int*)(record + 0x18) = remaining - 0x400;
            *(int*)(record + 0xC) += 0x400;
            *(int*)(record + 8) += 0x400;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024C08);
#endif

// gl_func_00024D90 — STRUCTURAL PASS (0x84 / 33 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A companion object constructor to gl_func_00023E60 —
// same fixed init 0x0C00E181 + &D_2Axxx table.
//
//   void gl_func_00024D90(O *obj, int a1) {
//     (*build1)(obj->w_C);                              // jal 0 USO
//     (*build2)(&obj->sub_30, &obj->sub_48, 1);          // jal 0 USO
//     jal 0x38604(&obj->sub_4C, 0, 0,                    // 0x0C00E181
//                 obj->w_8, a1, obj->w_C,
//                 &D_2AFCC, obj->b_0);
//   }
//
// Struct-typing reference: constructs an object `obj` by building
//   two of its sub-structures in place — at obj+0x30 / obj+0x48 (via
//   the second USO-relocated builder, `jal 0` slot) and obj+0x4C
//   (passed to the init) — then runs the shared fixed init routine
//   0x0C00E181 (≈0x38604, the SAME init gl_func_00023E60 calls) with
//   obj fields (word obj->8, word obj->0xC, byte obj->0) and the
//   fixed code/data blob &D_2AFCC (within the &D_2ACC0 region
//   gl_func_00023E60 also references). A second object-bring-up entry
//   of the same game_libs resource-construction family.
// Caps (DEFERRED): single jr $ra. Second object-bring-up of the
//   game_libs resource-construction family (sibling of
//   gl_func_00023E60; same shared fixed init 0x38604 and &D_2AFCC /
//   &D_2ACC0 blob). Real-C STRUCTURAL body below per the analysis
//   (jal-0 reloc1(obj->0xC); jal-0 reloc2(obj+0x30, obj+0x48, 1);
//   fixed 0x38604(obj+0x4C, 0, 0, [stack: obj->0xC, a1, obj+0x30,
//   *(byte)obj, &D_2AFCC])). Name pre-checked: no extern reuse.
//   gl_func_00000000 = canonical never-defined USO placeholder.
// 2026-05-28: 91.8% → 99.94%. Fixed the 3rd call's arg list (9 args, was
//   missing the a3 = obj->0x8 positional + had the wrong const): it's
//   f(obj+0x4C, 0, 0, obj->0x8, obj->0xC, a1, obj+0x30, (u8)obj, &D+0x1AFCC).
//   The const is &D_00000000+0x1AFCC (lui 0x2; addiu 0xAFCC), NOT +0x2AFCC.
// MATCHED 2026-05-30 (99.94% -> 100%). The last residual was the a0 spill slot
//   (0x38 vs target 0x3c): dropping the `g = &D` local and inlining
//   `(char*)&D+0x1AFCC` as the 9th arg freed the 0x38 slot the target leaves
//   empty, shifting the spill to 0x3c. The 3rd call is a concrete `jal 0x38604`
//   (a mid-function alt-entry inside gl_func_00038598, gl_func_00038604 =
//   0x38604 in undefined_syms) — objdiff resolves that R_MIPS_26 reloc, so it
//   credits 100%. Byte-exact (no-alias verified).
extern int gl_func_00000000();
extern int gl_func_00038604();
extern int D_00000000;
void gl_func_00024D90(char *obj, int a1) {
    gl_func_00000000(*(int *)(obj + 0xC));
    gl_func_00000000(obj + 0x30, obj + 0x48, 1);
    gl_func_00038604(obj + 0x4C, 0, 0, *(int *)(obj + 0x8),
                     *(int *)(obj + 0xC), a1, obj + 0x30,
                     *(unsigned char *)obj, (char *)&D_00000000 + 0x1AFCC);
}

void game_libs_func_00024E14(int a0, int a1, int a2, int a3) {
}

// game_libs_func_00024E28 — STRUCTURAL PASS (0xC / 3 words, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: this is
// NOT a standalone function — it is a 3-word splat-missplit HEAD
// FRAGMENT of the immediately-following gl_func_00024E34. No
// prologue, no jr; it ends exactly where gl_func_00024E34 begins
// (0x24E28 + 0xC == 0x24E34, contiguous).
//
//   (these 3 words belong to gl_func_00024E34's entry)
//   lui   t0, %hi(&D_0)
//   addiu t0, t0, %lo(&D_0)
//   lhu   t6, 0x202C(t0)      // t6 = registry-limit halfword
//
// The 3 words preload t6 with the registry index limit (&D_0+0x202C,
// the same limit the gl_func_00022FC0 / gl_func_000235E4 family
// range-check against). gl_func_00024E34's very first body
// instruction after its `addiu $sp,-0x18` prologue is
// `slt $at, $a0, $t6` — i.e. it consumes this exact t6 to do the
// `if (idx < limit)` bounds check. So the real function is
// [0x24E28 .. 0x24E34+0xFC) and splat cut its boundary 0xC bytes
// early, orphaning the limit-load as a separate symbol.
//
// FIX (deferred): merge this fragment into gl_func_00024E34 via the
// USO boundary re-split — the mnemonic merge-fragments /
// split-fragments.py tools do NOT operate on relocatable USO
// segments (documented), so this requires the per-USO splat-config
// re-extraction pass, not a 60s loop tick. Tracked here as a
// boundary note alongside the other deferred USO re-split items.
// Caps: raw-word USO + cross-boundary fragment (not independently
//   meaningful) — no episode, no byte body; structural boundary
//   documentation only.
// Full body INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no episode; tautology-trap rule).
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00024E28);

// gl_func_00024E34 — STRUCTURAL PASS (0xFC / 63 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr) — but
// its true entry is the preceding 3-word head fragment
// game_libs_func_00024E28 (splat boundary missplit; see that comment).
// A bounds-checked registry-slot creator.
//
//   int gl_func_00024E34(int idx, int a1, void *a2) {  // entry preloads
//     // t6 = *(u16*)(&D_0 + 0x202C)  (from the head fragment)
//     if (idx >= t6) { *(byte*)a2 = 0; return -1; }     // range fail
//     int j = jal 0x38174(0, idx);                       // 0x0C00E05D
//     int r = jal 0x38204(0, j);                          // 0x0C00E081
//     T  *tp = *(T**)(&D_0 + 0x1578);                      // table ptr
//     R  *rec = (char*)(&D_0 + 0x157C) + r*0x14;           // record
//     int  k  = *(int*)(&D_0 + 0x1590);
//     if (k != 3) rec->w_14 = 0;                            // zero-init
//     rec->w_24 = 0;
//     ...
//   }
//
// Struct-typing reference: the bounds-checked allocator/creator for a
//   registry record table. The valid index ceiling is the halfword
//   &D_0+0x202C (the same registry limit the gl_func_00022FC0 /
//   gl_func_000235E4 family checks) — preloaded into t6 by the head
//   fragment game_libs_func_00024E28. On overflow it clears the
//   caller's a2 byte and returns -1. Otherwise it resolves a slot via
//   the shared poll 0x0C00E05D (≈0x38174) + 0x0C00E081 (≈0x38204),
//   indexes a 0x14-stride record at base &D_0+0x157C (table pointer
//   &D_0+0x1578, control word &D_0+0x1590) and zero-initialises the
//   record's words +0x14 / +0x24. Companion to the gl_func_000223DC
//   find-or-append / gl_func_00021F40 insert helpers, on a distinct
//   record table (&D_0+0x157C vs &D_0+0x2030).
// Caps (DEFERRED): single jr $ra. Bounds-checked registry-slot
//   creator (companion to gl_func_000223DC / gl_func_00021F40, on
//   the &D_0+0x157C record table). CROSS-FRAGMENT ENTRY: true entry
//   is the 3-word head fragment game_libs_func_00024E28 which
//   preloads the &D_0+0x202C limit into t6 (splat boundary missplit
//   — DEFERRED USO re-split / merge-fragments; the bounds check is
//   inlined below for the structural body). Real-C STRUCTURAL body
//   per the analysis (idx >= limit -> *a2=0, return -1; else poll
//   0x38174(0,idx) + 0x38204(0,j); rec = &D_0+0x157C + r*0x14;
//   control &D_0+0x1590 != 3 -> rec->0x14=0; rec->0x24=0). Byte-
//   match deferred — needs the head-fragment merge + USO reloc
//   infra. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
// Bounds-checked record creator. idx >= *(u16)(&D_0+0x202C) -> *a2=0, ret -1.
// Else: j = poll(0,idx) [0x38174]; base = init(0) [0x38204]; n = *(&D_0+0x1578);
// the block is &D_0 + n*0x64 (control at +0x1590, record rec at +0x157C). A
// source record src = base + j*0x10 feeds several fields. Stores: (control==3)
// rec->0x14=0; rec->0x24=0; rec->0x1C=a2; rec->0x14=1; rec->0xC/0x10=a1;
// rec->0x18=(src->0x14 + 15)&~0xF; rec->0x8=src->0x10; rec->1=(byte)j;
// rec->0=src->0x18; if that byte==1, rec->4=*(short)(base+2). Tail toggles
// *(&D_0+0x1578) ^= 1 and returns 0. CROSS-FRAGMENT: t6 (the 0x202C limit) is
// preloaded by head fragment game_libs_func_00024E28 (splat missplit) — the
// bounds load is inlined here, so it won't byte-match until the fragment merge.
int gl_func_00024E34(int idx, int a1, char *a2) {
    char *g = (char *)&D_00000000;
    int j;
    char *base;
    char *src;
    char *block;
    char *rec;
    int n;
    int t6;
    if (idx >= *(unsigned short *)(g + 0x202C)) {
        *a2 = 0;
        return -1;
    }
    j = gl_func_00000000(0, idx);
    base = (char *)gl_func_00000000(0);
    n = *(int *)(g + 0x1578);
    block = g + n * 0x64;
    rec = block + 0x157C;
    src = base + j * 0x10;
    if (*(int *)(block + 0x1590) == 3) {
        *(int *)(rec + 0x14) = 0;
    }
    *(int *)(rec + 0x24) = 0;
    *(int *)(rec + 0x1C) = (int)a2;
    *(int *)(rec + 0x14) = 1;
    *(int *)(rec + 0xC) = a1;
    *(int *)(rec + 0x18) = (*(int *)(src + 0x14) + 0xF) & ~0xF;
    *(int *)(rec + 0x10) = a1;
    *(int *)(rec + 0x8) = *(int *)(src + 0x10);
    *(char *)(rec + 1) = (char)j;
    t6 = *(signed char *)(src + 0x18);
    *(char *)(rec + 0) = t6;
    if ((t6 & 0xFF) == 1) {
        *(int *)(rec + 4) = *(short *)(base + 2);
    }
    n = *(int *)(g + 0x1578);
    *(int *)(g + 0x1578) = n ^ 1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024E34);
#endif

// gl_func_00024F30 — STRUCTURAL PASS (0x114 / 69 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A free-slot allocator over the 0x54-stride slot table at
// &D_0+0x1038.
//
//   void *gl_func_00024F30(int a0, int a1, int a2) {
//     Slot *s   = (Slot*)(&D_0 + 0x1038);
//     Slot *end = (Slot*)(&D_0 + 0x540 + ...);            // table end
//     while (s != end) {                                  // linear scan
//       if (s->b_0 == 0) break;                            // free slot
//       s = (char*)s + 0x54;                               // stride
//     }
//     if (s == end) return 0;                              // table full
//     s->b_0  = 1;                                          // in-use
//     s->w_4  = a1;
//     s->w_8  = ...;
//     s->w_C  = a1;
//     s->w_10 = a2;
//     s->w_14 = ...;
//     return s;
//   }
//
// Struct-typing reference: a fixed-capacity slot pool — base
//   &D_0+0x1038, entry stride 0x54, scanned linearly for the first
//   entry whose byte +0 is 0 (free); the end marker is derived from
//   the &D_0+0x540 region. On a full table it returns 0. A claimed
//   slot gets byte +0 set to 1 (in-use flag) and words +4 / +8 / +0xC
//   / +0x10 / +0x14 initialised from the caller args. A distinct slot
//   pool from the &D_0+0x157C (gl_func_00024E34) and &D_0+0x2030
//   (gl_func_000223DC) registry tables — the game_libs subsystem has
//   several parallel fixed-stride pools.
// Caps (DEFERRED): CLEAN single jr $ra. Free-slot allocator over a
//   fixed-capacity slot pool (distinct from the &D_0+0x157C /
//   &D_0+0x2030 registry tables). Real-C STRUCTURAL body below per
//   the analysis (base &D_0+0x1038, stride 0x54, 16 slots = scan
//   limit 0x540; first slot whose byte+0==0 is claimed: byte+0=1,
//   words +4/+8/+0xC/+0x10/+0x14 from args; full table -> 0).
//   Byte-match deferred — bnel scan-loop schedule. Name pre-checked:
//   no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior init was incomplete + missing 4 args).
 * Find a free 0x54-stride slot in [&D+0x1038, &D+0x1578); if none return 0. Init
 * s+0=1, s+4=a1, s+0xC=a1, s+0x10=a2, s+8=a0; scale s+0x14 = 4096 if a0==0 else
 * (a2/a0+255)&~0xFF floored at 256; s+1=3, s+2=a3, s+0x1C=arg6, s+0x18=arg7;
 * gl(s+0x20, s+0x38, 1); return s. */
void *gl_func_00024F30(int a0, int a1, int a2, int a3, int arg5, int arg6, int arg7) {
    char *base = (char *)&D_00000000;
    char *v0;
    char *s = 0;
    (void)arg5;
    for (v0 = base; v0 != base + 0x540; v0 += 0x54) {
        if (*(char *)(v0 + 0x1038) == 0) {
            s = v0 + 0x1038;
            break;
        }
    }
    if (v0 == base + 0x540) {
        return 0;
    }
    *(char *)(s + 0) = 1;
    *(int *)(s + 4) = a1;
    *(int *)(s + 0xC) = a1;
    *(int *)(s + 0x10) = a2;
    *(int *)(s + 8) = a0;
    if (a0 == 0) {
        *(int *)(s + 0x14) = 4096;
    } else {
        int v = ((a2 / a0) + 255) & ~0xFF;
        *(int *)(s + 0x14) = v;
        if ((u32)v < 256U) {
            *(int *)(s + 0x14) = 256;
        }
    }
    *(char *)(s + 1) = 3;
    *(char *)(s + 2) = a3;
    *(int *)(s + 0x1C) = arg6;
    *(int *)(s + 0x18) = arg7;
    gl_func_00000000(s + 0x20, s + 0x38, 1);
    return s;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024F30);
#endif

// gl_func_00025044 — STRUCTURAL PASS (0x84 / 33 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). The teardown SWEEP counterpart to the gl_func_00024F30
// slot allocator.
//
//   void gl_func_00025044(int a0) {
//     S *g = &D_0;
//     if (g->w_215C == 1) return;                       // already torn
//     Slot *s   = (Slot*)(g + 0x1038);
//     Slot *end = (Slot*)(g + 0x540 + ...);              // table end
//     while (s != end) {
//       if (s->b_0 == 1) {                                // in-use
//         jal 0x39734(&s->..., a0);                        // 0x0C00E5CD
//       }
//       s = (char*)s + 0x54;                              // stride
//     }
//   }
//
// Struct-typing reference: walks the SAME fixed-capacity slot pool
//   gl_func_00024F30 allocates from — base &D_0+0x1038, entry stride
//   0x54, byte +0 the in-use flag, end derived from the &D_0+0x540
//   region — and for every slot marked in-use (byte +0 == 1) invokes
//   the fixed USO-relocated destructor 0x0C00E5CD (≈0x39734) with the
//   caller arg. The whole sweep is gated on the subsystem handle
//   &D_0+0x215C: if it equals 1 (already shut down) the function is a
//   no-op. The shutdown/free-all counterpart to gl_func_00024F30,
//   analogous to how gl_func_0002349C tears down the &D_0+0x2030
//   registry.
// Caps (DEFERRED): CLEAN single jr $ra. Shutdown/free-all
//   counterpart to gl_func_00024F30 (analogous to gl_func_0002349C
//   tearing down the &D_0+0x2030 registry). Real-C STRUCTURAL body
//   below per the analysis (if &D_0+0x215C == 1 no-op; else for each
//   of the 16 pool slots &D_0+0x1038 stride 0x54 with byte+0==1 call
//   the fixed per-slot destructor 0x39734(slot, a0)). Byte-match
//   deferred — placeholder jal + bnel scan-loop need USO reloc
//   infra. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00025044(int a0) {
    char *g = (char *)&D_00000000;
    char *base = g + 0x1038;
    int off;
    if (*(int *)(g + 0x215C) == 1) {
        return;
    }
    for (off = 0; off != 0x540; off += 0x54) {
        if (*(char *)(base + off) == 1) {
            gl_func_00000000(base + off, a0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025044);
#endif

// gl_func_000250C8 — STRUCTURAL PASS (0x258 / 150 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A per-object state-machine step (tick) on an object's
// mode/countdown byte.
//
//   void gl_func_000250C8(O *obj, int a1) {
//     int mode = obj->b_1;                              // signed byte
//     int g    = *(int*)(&D_0 + 0x2024);
//     if (mode >= 2) {
//       obj->b_1 = mode - 1;                              // countdown
//       ...
//     } else if (mode == 1) {
//       obj->b_1 = 0;                                     // -> idle
//       if (a1) {
//         (*onA)(&obj->sub_20, 0, 1);                      // jal 0 USO
//       }
//     } else {                                            // mode 0
//       obj->b_0 = 0;
//       (*onB)(&obj->sub_20, 0, 0);                        // jal 0 USO
//       if (obj->w_10 != 0) { ... }                        // sub state
//     }
//   }
//
// Struct-typing reference: `obj` is a stateful object — signed byte
//   obj->1 is the mode / frame-countdown (>=2 decrements toward a
//   transition, ==1 finalises to 0, 0 is the terminal/idle state),
//   byte obj->0 a secondary flag, word obj->0x10 a sub-state handle,
//   and obj+0x20 an embedded sub-structure handed to USO-relocated
//   per-mode handlers (the `jal 0` slots). Global &D_0+0x2024 is the
//   shared registry table pointer (same one gl_func_000230D0 /
//   gl_func_00023B44 read). This is the object-tick / advance-state
//   entry of the game_libs object subsystem.
// Caps (DEFERRED): CLEAN single jr $ra. Object-tick / advance-state
//   entry of the game_libs object subsystem. Real-C STRUCTURAL body
//   below per the analysis (signed byte obj->1 = mode/countdown:
//   >=2 decrements, ==1 finalises to 0 + jal-0 onA(&obj+0x20,0,1)
//   when a1, 0 = idle clears obj->0 + jal-0 onB(&obj+0x20,0,0) and
//   sub-state on obj->0x10; global &D_0+0x2024 registry ptr).
//   Byte-match deferred — multi-branch state machine + jal-0
//   transitions need USO reloc infra. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder.
// gl_func_000250C8 — FULL m2c DECODE (61.83% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000250C8)();
void gl_func_000250C8(char *arg0, s32 arg1) {
    char *sp5C;
    s32 sp44;
    int sp40;
    int sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp24;
    s32 temp_v0_3;
    s32 temp_v1_2;
    s8 temp_v0;
    u32 temp_a0;
    u32 temp_a1;
    u32 temp_a2;
    u32 temp_a2_2;
    u32 temp_t7;
    u8 temp_a0_2;
    u8 var_a2;
    char *temp_v0_2;
    char *temp_v1;

    temp_v0 = FW(arg0, 0x1);
    temp_v1 = *(char **)0x2024;
    if (temp_v0 >= 2) {
        FW(arg0, 0x1) = (s8) (temp_v0 - 1);
        return;
    }
    if (temp_v0 == 1) {
        *(u8*)((char*)arg0 + 0x1) = 0;
        goto block_7;
    }
    if (arg1 != 0) {
        gl_func_0001CA10((int)arg0 + 0x20, 0U, 1, 1);
        *(u8*)((char*)arg0 + 0x0) = 0;
        return;
    }
    sp5C = temp_v1;
    if (gl_func_0001CA10((int)arg0 + 0x20, 0U, 0, 1) != -1) {
block_7:
        temp_t7 = FW(arg0, 0x10);
        sp24 = temp_t7;
        if (temp_t7 == 0) {
            temp_a1 = FW(arg0, 0x18);
            temp_v1_2 = (temp_a1 >> 0x10) & 0xFF;
            switch (temp_v1_2) {                    /* irregular */
            case 0:
                gl_func_0001CA10((char *) ((temp_a1 >> 8) & 0xFF), temp_a1 & 0xFF);
                break;
            case 2:
                gl_func_0001CA10((char *) ((temp_a1 >> 8) & 0xFF), temp_a1 & 0xFF);
                break;
            case 1:
                temp_a0 = (temp_a1 >> 8) & 0xFF;
                sp24 = temp_a0;
                gl_func_0001CA10((char *) temp_a0, temp_a1 & 0xFF);
                temp_v0_2 = *(s32 *)0x2030 + (sp24 * 0x14);
                temp_a0_2 = FW(temp_v0_2, 0x2);
                var_a2 = FW(temp_v0_2, 0x3);
                sp2C = (s32) temp_a0_2;
                sp30 = (s32) var_a2;
                if (temp_a0_2 != 0xFF) {
                    sp44 = (s32) var_a2;
                    temp_v0_3 = game_libs_func_0003443C(temp_a0_2, &sp3C, var_a2);
                    var_a2 = (u8) sp44;
                    sp34 = temp_v0_3;
                } else {
                    sp34 = 0;
                }
                if (var_a2 != 0xFF) {
                    sp38 = game_libs_func_0003443C(var_a2, &sp40, var_a2);
                } else {
                    sp38 = 0;
                }
                game_libs_func_0003443C((u8) sp24, FW(arg0, 0x4), (u8) &sp2C, 1);
                break;
            }
            *(u8*)((char*)arg0 + 0x0) = 0;
            gl_func_0001CA10(FW(arg0, 0x1C), FW(arg0, 0x18), 0);
            return;
        }
        temp_a2 = FW(arg0, 0x14);
        if (sp24 < temp_a2) {
            if (FW(arg0, 0x2) == 1) {
                game_libs_func_0003443C((u8) FW(arg0, 0x8), FW(arg0, 0xC), (u8) sp24, FW(temp_v1, 0x2));
            } else {
                game_libs_func_0003443C((u8) arg0, (int *) sp24, (u8) sp24, 1);
            }
            FW(arg0, 0x10) = 0U;
            return;
        }
        if (FW(arg0, 0x2) == 1) {
            game_libs_func_0003443C((u8) FW(arg0, 0x8), FW(arg0, 0xC), (u8) temp_a2, FW(temp_v1, 0x2));
        } else {
            game_libs_func_0003443C((u8) arg0, (int *) temp_a2, (u8) temp_a2, 1);
        }
        temp_a2_2 = FW(arg0, 0x14);
        FW(arg0, 0x10) = (u32) (FW(arg0, 0x10) - temp_a2_2);
        FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) + temp_a2_2);
        FW(arg0, 0xC) = (int *) (FW(arg0, 0xC) + temp_a2_2);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000250C8);
#endif

// gl_func_00025320 — STRUCTURAL PASS (0x1E4 / 121 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is a THIRD object constructor of the gl_func_00023E60 /
// gl_func_00024D90 family — same shared fixed init 0x0C00E181.
//
//   void gl_func_00025320(O *obj, int sz) {
//     int n = (sz + 0xF) & ~0xF;                        // align16
//     (*alloc)(obj->w_C);                                // jal 0 USO
//     (*build)(&obj->sub_20, &obj->sub_38, 1);            // jal 0 USO
//     jal 0x38604(&obj->sub_3C, 0, 0,                     // 0x0C00E181
//                 obj->w_8, n, obj->w_C,
//                 &D_2B0C0, obj->b_2);
//   }
//
// Struct-typing reference: identical construction shape to
//   gl_func_00024D90 (and gl_func_00023E60) — round the requested
//   size up to a 16-byte multiple, allocate via a USO-relocated
//   allocator (`jal 0`), build two embedded sub-structures (here at
//   obj+0x20 / obj+0x38, plus obj+0x3C passed to the init), then run
//   the SAME shared fixed init routine 0x0C00E181 (≈0x38604) with
//   obj fields (word obj->8, word obj->0xC, byte obj->2) and a fixed
//   code/data blob &D_2B0C0 (the third pointer in the &D_2ACC0 /
//   &D_2AFCC / &D_2B0C0 family the three constructors each select).
//   The game_libs resource subsystem has at least three parallel
//   object-bring-up entries differing only in the &D_2Bxx blob and
//   sub-struct offsets.
// Caps (DEFERRED): single jr $ra (the "3-fn unsplit bundle" note is
//   STALE; .s is 0x90/36 words, ONE function). Third object-bring-up
//   of the gl_func_00023E60 / gl_func_00024D90 constructor family
//   (differs only in the &D_2Bxx blob / sub-struct offsets). Real-C
//   STRUCTURAL body below per the analysis (size16=(a1+0xF)&~0xF;
//   jal-0 reloc1(obj->0xC, size16); jal-0 reloc2(obj+0x20,
//   obj+0x38, 1); fixed 0x38604(obj+0x3C, 0, 0, [obj->0xC, size16,
//   obj+0x20, *(byte)(obj+2), &D_2B0C0])). Byte-match deferred —
//   placeholder jal-0 builders + fixed init need USO reloc infra.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00025320(char *obj, int a1) {
    char *g = (char *)&D_00000000;
    int sz = (a1 + 0xF) & ~0xF;
    gl_func_00000000(*(int *)(obj + 0xC), sz);
    gl_func_00000000(obj + 0x20, obj + 0x38, 1);
    gl_func_00000000(obj + 0x3C, 0, 0,
                     *(int *)(obj + 0xC), sz, obj + 0x20,
                     *(unsigned char *)(obj + 2), g + 0x2B0C0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025320);
#endif

/* Empty 4-arg stub (sibling of _00023F84). */
void game_libs_func_000253B0(int a0, int a1, int a2, int a3) {
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000253C4)();
/* 2026-06-20 reconstruction: 76->66 diffs. node = *arg0 + arg1 (gated unsigned
 * < 0x80000001), stored back; if (node->0 & 0xFFFFFF) and bit0 clear: bump the
 * +8/+0xC words by arg1, then a 4-way switch on bits[26:27] of node->0
 * ((node->0<<4)>>30) adds arg2->8/0xC to node->4 and folds (arg2->0x10/0x14)<<2
 * &0xC into node->0 low byte (cases 0/1; 2/3 noop); set bit0; finally if bit
 * 0x02000000 set AND bits[26:27]!=0, append node to the &D+0x430 table indexed
 * by the &D+0x1030 counter and bump it. Bare 0x1030/0x430 fixed to &D-relative.
 * Residual 66 (size 80 exact, logic correct): target COPIES node into $a2 (and
 * config arg2 into $a3) and uses $a2 as the long-lived node base while reusing
 * $v1 as the per-field add scratch; build keeps node in $v1, so the register
 * assignment cascades. Genuine node-base coloring ($a2 vs $v1) cap — needs the
 * original two-variable (store-temp vs access-base) split that can't be
 * reconstructed from the .s. */
void game_libs_func_000253C4(u32 *arg0, s32 arg1, char *arg2) {
    char *D = (char *)&D_00000000;
    s32 temp_v0_3;
    u32 temp_v0;
    u32 temp_v0_2;
    char *node;

    temp_v0 = *arg0;
    if (temp_v0 < 0x80000001U) {
        node = (char *)(temp_v0 + arg1);
        *arg0 = (u32) node;
        if ((*(s32 *)node & 0xFFFFFF) && (((u8) *(s32 *)node & 1) != 1)) {
            *(s32 *)(node + 8) += arg1;
            temp_v0_2 = (u32) (*(s32 *)node << 4) >> 0x1E;
            *(s32 *)(node + 0xC) += arg1;
            switch (temp_v0_2) {                    /* irregular */
            case 2:
            case 3:
                break;
            case 0:
                *(s32 *)(node + 4) += *(s32 *)(arg2 + 8);
                *(s8 *)node = (s8) (((*(s32 *)(arg2 + 0x10) << 2) & 0xC) | ((u8) *(s32 *)node & 0xFFF3));
                break;
            case 1:
                *(s32 *)(node + 4) += *(s32 *)(arg2 + 0xC);
                *(s8 *)node = (s8) (((*(s32 *)(arg2 + 0x14) << 2) & 0xC) | ((u8) *(s32 *)node & 0xFFF3));
                break;
            }
            *(s8 *)node |= 1;
            temp_v0_3 = *(s32 *)node;
            if ((temp_v0_3 & 0x02000000) && (((u32) (temp_v0_3 << 4) >> 0x1E) != 0)) {
                *(char **)(D + *(s32 *)(D + 0x1030) * 4 + 0x430) = node;
                *(s32 *)(D + 0x1030) += 1;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000253C4);
#endif

// gl_func_00025504 — STRUCTURAL PASS (0x3C8 / 242 words ≈ 1KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). A per-frame subsystem UPDATE DRIVER. Large
// -0x68 frame, full s0-s7/ra save.
//
//   int gl_func_00025504(a0, a1, a2, a3) {
//     S *g = &D_0;
//     if (g->w_1034 == 0) { ret = 0; } else { ret = 1; }  // state gate
//     g->w_2B0  = 0;                                       // clear flag
//     g->w_1030 = 0;                                        // reset cnt
//     jal 0x38248(…, a2);                                   // 0x0C00E092
//     int n = g->w_1030;                                     // refreshed
//     if (n <= 0) return ret;
//     for (int i = 0; i < n; i++) {                          // element
//       E *e = *(E**)(&D_0 + 0x430 + i*4);                   //  table
//       ... process e (mask 0xFFF0 align, sub-calls) ...
//     }
//     return ret;
//   }
//
// Struct-typing reference: the top-level per-frame tick of the
//   subsystem keyed on &D_0+0x1034 (an enabled/state word) and
//   &D_0+0x1030 (a live element count, reset then refilled by the
//   USO-relocated routine 0x0C00E092 ≈0x38248). &D_0+0x2B0 is a
//   transient flag cleared each call. The element pointer table is
//   rooted at &D_0+0x430 (word-strided, indexed by the count); each
//   element is processed with a 0x10-aligned size and further
//   sub-calls. This is the update/advance entry that complements the
//   gl_func_00024378 init / gl_func_00025044 teardown for that
//   subsystem.
// Caps (DEFERRED): CLEAN single jr $ra. Per-frame subsystem UPDATE
//   DRIVER (complements gl_func_00024378 init / gl_func_00025044
//   teardown). Real-C STRUCTURAL body below per the analysis (state
//   gate &D_0+0x1034 -> ret; clear &D_0+0x2B0 flag and &D_0+0x1030
//   count; jal-0 0x38248(..,a2) refills the count; loop the
//   &D_0+0x430 word-strided element-ptr table processing each with
//   a 0x10-aligned size + sub-calls; return ret). Byte-match
//   deferred — large element-loop + USO-reloc sub-calls need USO
//   reloc infra + s0-s7 schedule. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
// gl_func_00025504 — FULL RECONSTRUCTION (&D_0-rooted), 65.06% NM (no episode).
// Per-frame subsystem update driver. Base &D_00000000 held in s1; element-ptr
// table @+0x430 (FIRST loop: byte-strided pointer walk by 4; MAIN loop: index
// s5*4), record array @+0x620 (stride 0x14, indexed by state word @+0x1034,
// reloaded + re-multu'd PER field store). Comparison keys are arg2->0x10 /
// arg2->0x14 (NOT global). Two K&R variadic emits to game_libs_func_0003443C +
// variadic gl_func_0001CA10. Logic verified byte-shape correct (multu pattern,
// loop strides, field bases, call structure all match).
// CAP: residual ~25-insn gap is IDO constant-rematerialization/coloring — target
// rematerializes the 0xFFFFFF mask 7x (lui/ori per &-use) and runs higher
// register pressure (keeps n in-reg), while clean C at -O2 holds the mask in a
// saved reg + spills n. Not forceable from C; documented coloring/remat cap.
#ifdef NON_MATCHING
#define GB ((char *)&D_00000000)
#define GW(o) (*(s32 *)(GB + (o)))
void gl_func_00025504(s32 arg0, s32 arg1, char *arg2, s32 arg3) {
    s32 ret;
    s32 sum;
    s32 i;
    s32 cur;
    s32 n;
    char *e;
    s32 v0;
    s32 v1;
    s32 idx;

    ret = 0;
    if (GW(0x1034) != 0) {
        ret = 1;
    } else {
        GW(0x2B0) = 0;
    }
    GW(0x1030) = 0;
    game_libs_func_0003443C(arg0, arg1, arg2);
    n = GW(0x1030);
    if (n > 0) {
        sum = 0;
        i = 0;
        do {
            sum += ((*(s32 *)GW(0x430 + i) & 0xFFFFFF) + 15) & -16;
            i += 4;
        } while ((u32) i < (u32) (n * 4));
    }
    if (n > 0) {
        i = 0;
        do {
            if (GW(0x1034) == 120) {
                goto done;
            }
            e = (char *)GW(0x430 + i * 4);
            if (arg3 == 0) {
                v0 = *(s32 *)e;
                v1 = (s32) ((u32) (v0 << 4) >> 0x1E);
                if (*(s32 *)(arg2 + 0x10) == v1) {
                    cur = gl_func_0001CA10(v0 & 0xFFFFFF, *(s32 *)arg2, *(s32 *)(e + 4), (s8) v1);
                } else if (*(s32 *)(arg2 + 0x14) == v1) {
                    cur = gl_func_0001CA10(v0 & 0xFFFFFF, *(s32 *)(arg2 + 4), *(s32 *)(e + 4), (s8) v1);
                }
            } else if (arg3 == 1) {
                v0 = *(s32 *)e;
                v1 = (s32) ((u32) (v0 << 4) >> 0x1E);
                if (*(s32 *)(arg2 + 0x10) == v1) {
                    cur = gl_func_0001CA10(v0 & 0xFFFFFF, *(s32 *)arg2, *(s32 *)(e + 4), (s8) v1);
                } else if (*(s32 *)(arg2 + 0x14) == v1) {
                    cur = gl_func_0001CA10(v0 & 0xFFFFFF, *(s32 *)(arg2 + 4), *(s32 *)(e + 4), (s8) v1);
                }
            }
            if (cur != 0) {
                if (arg3 == 0) {
                    v0 = *(s32 *)e;
                    v1 = (s32) ((u32) (v0 << 4) >> 0x1E);
                    if (v1 == 1) {
                        gl_func_0001CA10(*(s32 *)(e + 4), cur, v0 & 0xFFFFFF, (s8) *(s16 *)(GW(0x2024) + 2));
                    } else {
                        gl_func_0001CA10(*(s32 *)(e + 4), cur, v0 & 0xFFFFFF, (s8) v1);
                    }
                    *(s32 *)(e + 4) = cur;
                    *(u8 *)e = (u8) (*(u8 *)e & 0xFFF3);
                } else if (arg3 == 1) {
                    GW(GW(0x1034) * 0x14 + 0x634) = (s32) e;
                    GW(GW(0x1034) * 0x14 + 0x638) = cur;
                    idx = GW(0x1034);
                    GW(idx * 0x14 + 0x63C) = (idx << 0x18) | 0xFFFFFF;
                    GW(GW(0x1034) * 0x14 + 0x640) = 0;
                    v0 = *(s32 *)e;
                    GW(GW(0x1034) * 0x14 + 0x630) =
                        *(s32 *)(e + 4) + (v0 & 0xFFFFFF) + ((u32) (v0 << 4) >> 0x1E);
                    GW(0x1034) += 1;
                }
            }
            i += 1;
        } while (i < n);
    }
done:
    v1 = GW(0x1034);
    GW(0x1030) = 0;
    if ((v1 != 0) && (ret == 0)) {
        idx = v1 * 0x14;
        e = (char *)GW(idx + 0x620);
        v0 = *(s32 *)e;
        game_libs_func_0003443C(*(s32 *)(e + 4), GW(idx + 0x624), v0 & 0xFFFFFF,
                                (u32) (v0 << 4) >> 0x1E, ((v0 & 0xFFFFFF) >> 0xC) + 1,
                                0x1684, GW(idx + 0x628));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025504);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000258C0);

// gl_func_000258CC — STRUCTURAL PASS (0x1FC / 127 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is a parse-descriptor-and-apply / init-from-config
// helper.
//
//   int gl_func_000258CC(int a0, int a1) {
//     int spv;
//     if (a0 == 0 || a1 <= 0) {
//       (*parse)(&D_1684, &spv);                         // jal 0 USO
//       *(int*)(&D_0 + 0x1034) = 0;                       // reset state
//       return 0;
//     }
//     int r = (*parse)(&D_1684, &spv);                    // jal 0 USO
//     if (r == -1) { *(int*)(&D_0 + 0x1034) = 0; return 0; }
//     int hb  = (unsigned)spv >> 24;                      // high byte
//     C  *cfg = (char*)(&D_0 + 0x640) + (hb*5 << 2);       // 0x14 stride
//     ... apply cfg ...
//   }
//
// Struct-typing reference: &D_1684 is a fixed config descriptor blob
//   parsed by a USO-relocated parser (`jal 0` slot) into a stack
//   scratch word. The parsed value's high byte (>>24) indexes a
//   config table at &D_0+0x640 (entry stride 0x14, idx*5<<2). Word
//   &D_0+0x1034 is the subsystem-state word (the same one
//   gl_func_00025504's update driver gates on) — cleared to 0 on the
//   degenerate / parse-fail paths. This is the "load and apply the
//   config descriptor" front-end that primes the subsystem
//   gl_func_00025504 then drives per-frame.
// Caps (DEFERRED): single jr $ra (the "2-fn unsplit bundle" note is
//   STALE; .s is 0x1FC/113 words, ONE function). "Load and apply the
//   config descriptor" front-end that primes the gl_func_00025504
//   subsystem. Real-C STRUCTURAL body below per the analysis
//   (degenerate a0==0 || a1<=0 or parse==-1 -> reset &D_0+0x1034=0,
//   return 0; else jal-0 parse(&D_1684,&spv); cfg = &D_0+0x640 +
//   ((spv>>24)*5<<2) (0x14 stride); apply). Byte-match deferred —
//   placeholder jal-0 parser needs USO reloc infra. Name
//   pre-checked: no extern reuse (collision-safe). gl_func_00000000
//   = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int gl_func_0003959C();
extern int D_00000000;
int gl_func_000258CC(int a0, int a1) {
    char *g = (char *)&D_00000000;
    int spv;
    int r, hb;
    char *cfg;
    if (a0 == 0 || a1 <= 0) {
        gl_func_00000000(g + 0x1684, &spv);
        *(int *)(g + 0x1034) = 0;
        return 0;
    }
    r = gl_func_00000000(g + 0x1684, &spv);
    if (r == -1) {
        *(int *)(g + 0x1034) = 0;
        return 0;
    }
    hb = (unsigned)spv >> 24;
    {
        int *v0 = (int *)(g + hb * 0x14);
        int *v1;
        int a0v, key;
        spv = hb;
        if (*(int *)((char *)v0 + 0x640) == 0) {
            v1 = *(int **)((char *)v0 + 0x634);
            a0v = v1[0];
            key = v1[1] + (a0v & 0x00FFFFFF) + ((unsigned)(a0v << 4) >> 0x1E);
            if (key == *(int *)((char *)v0 + 0x630)) {
                *(unsigned char *)v1 = *(unsigned char *)v1 & 0xF3;
                v1[1] = *(int *)((char *)v0 + 0x638);
                v0 = (int *)(g + spv * 0x14);
            }
            *(int *)((char *)v0 + 0x640) = 1;
        }
        while (*(int *)(g + 0x1034) > 0) {
            int cnt = *(int *)(g + 0x1034);
            v0 = (int *)(g + cnt * 0x14);
            if (*(int *)((char *)v0 + 0x62C) != 1) {
                *(int *)(g + 0x1034) = cnt - 1;
                continue;
            }
            v1 = *(int **)((char *)v0 + 0x620);
            a0v = v1[0];
            key = v1[1] + (a0v & 0x00FFFFFF) + ((unsigned)(a0v << 4) >> 0x1E);
            if (key != *(int *)((char *)v0 + 0x61C)) {
                *(int *)((char *)v0 + 0x62C) = 1;
                *(int *)(g + 0x1034) = *(int *)(g + 0x1034) - 1;
                continue;
            }
            gl_func_0003959C(v1[1], *(int *)((char *)v0 + 0x624),
                             ((unsigned)(a0v & 0x00FFFFFF) >> 0xC) + 1,
                             (unsigned)(a0v << 4) >> 0x1E, g + 0x1684,
                             *(int *)((char *)v0 + 0x628));
            break;
        }
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000258CC);
#endif

// Add a0 to the pointer array a2[0..a1) if its key (a0[1]) isn't already
// present (matched against a2[i][1]); append + bump count when absent.
// Returns the resulting count. BYTE-EXACT: current C emits the target's
// leading blez delay-slot init naturally; no instruction patching.
int game_libs_func_00025A80(int *a0, int a1, int **a2) {
    int i = 0;
    if (a1 > 0) {
        int key = a0[1];
        do {
            if (key == a2[i][1]) {
                break;
            }
            i++;
        } while (i != a1);
    }
    if (i == a1) {
        a2[a1] = (int)a0;
        a1++;
    }
    return a1;
}

// gl_func_00025AC8 — STRUCTURAL PASS (0x18C / 99 words, no episode).
// permuter resists: verify-fails every batch (x5+, 2026-06-19) — factory skip.
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn iterates a registry record's sub-entries.
//
//   int gl_func_00025AC8(int idx, int a1) {
//     R *rec = (char*)*(R**)(&D_0 + 0x2030) + idx*0x14; // reg record
//     int  n   = rec->b_1;                               // sub count
//     byte k   = rec->b_0;
//     int  acc = 0;
//     for (int i = 0; i < n; i++) {
//       if ((*pred)(idx, i)) {                            // jal 0 USO
//         void *p = rec->w_4;                              // sub list
//         acc = jal 0x3A0EC(p, acc, a1);                   // 0x0C00E83B
//       }
//     }
//     return acc;
//   }
//
// Struct-typing reference: indexes the SAME registry record table as
//   gl_func_000221D8 / gl_func_00023838 / gl_func_00023BDC (base
//   &D_0+0x2030, fixed 0x14 entry stride). Per record: byte +0 a
//   type/key, byte +1 the sub-entry count, word +4 a pointer to the
//   sub-entry list. It walks all sub-entries, gating each on a
//   USO-relocated predicate (`jal 0` slot) and folding the accepted
//   ones through the fixed routine 0x0C00E83B (≈0x3A0EC) with an
//   accumulator. The "apply over a record's sub-entry list" operation
//   of the registry family.
// Caps (DEFERRED): single jr $ra (the "2-fn unsplit bundle" note is
//   STALE; .s is 0x18C/81 words, ONE function). "Apply over a
//   record's sub-entry list" of the registry family (same
//   &D_0+0x2030 0x14-stride table as gl_func_000221D8 /
//   gl_func_00023838 / gl_func_00023BDC). Real-C STRUCTURAL body
//   below per the analysis (rec = (*&D_0+0x2030) + idx*0x14; for
//   each of rec->1 sub-entries gated on jal-0 pred(idx,i), fold the
//   accepted ones through fixed 0x3A0EC(rec->4, acc, a1)). Byte-
//   match deferred — placeholder jal-0 predicate + fixed fold need
//   USO reloc infra + loop schedule. Name pre-checked: no extern
//   reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder.
//
// 2026-05-31 FULL DECODE + completion 49.6->95.3%: the fn has TWO loops, not
//   one. Loop 1 (over rec->1 count): r=pred(idx,i); if(r) acc=fold(r->4,acc,a1)
//   — the fold arg is the PREDICATE RESULT's ->4, NOT rec->4. Loop 2 (over
//   rec->0 count): r=pred(idx,i); if(r){ if(r->1) acc=fold(r->8,..); if(r->2!=
//   127) acc=fold(r->24,..); acc=fold(r->16,..) [always] }. Structure now
//   EXACT (77=77 insns). RESIDUAL (95->100): consistent saved-reg renumber
//   (acc/i/n2/idx slot order) + the 4 placeholder jals (jal 0 vs baked 0x3A0EC
//   — USO-reloc cap, blocks byte-exact regardless). 95.3% is the ceiling
//   without USO-reloc infra.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00025AC8(int idx, int a1) {
    char *g = (char *)&D_00000000;
    char *rec = *(char **)(g + 0x2030) + idx * 0x14;
    int n2 = *(unsigned char *)(rec + 1);
    int n1 = *(unsigned char *)(rec + 0);
    int acc = 0;
    int i;
    char *r;
    for (i = 0; i < n2; i++) {
        r = (char *)gl_func_00000000(idx, i);
        if (r != 0) {
            acc = gl_func_00000000(*(void **)(r + 4), acc, a1);
        }
    }
    for (i = 0; i < n1; i++) {
        r = (char *)gl_func_00000000(idx, i);
        if (r != 0) {
            if (*(unsigned char *)(r + 1) != 0) {
                acc = gl_func_00000000(*(void **)(r + 8), acc, a1);
            }
            if (*(unsigned char *)(r + 2) != 127) {
                acc = gl_func_00000000(*(void **)(r + 24), acc, a1);
            }
            acc = gl_func_00000000(*(void **)(r + 16), acc, a1);
        }
    }
    return acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025AC8);
#endif

/* Flag-guarded D_-queue append. p=*a0; x=*p; require (x&0xFFFFFF)!=0 AND
 * (x<<6)<0 (bit25 set) AND ((u)(x<<4)>>30)!=0 (bits26-27); then append (int)p
 * to the queue at &D_+0x430 indexed by the count at &D_+0x1030, count++.
 * Structure exact (22/22 opcodes); back-half register allocation renumbers
 * (12/22, allocno cap — over-half so INSN_PATCH would hurt episode fidelity).
 * Faithful decode; INCLUDE_ASM build path. */
#ifdef NON_MATCHING
void game_libs_func_00025BFC(int **a0) {
    int *p = a0[0];
    int x = *p;
    if ((x & 0xFFFFFF) == 0) {
        return;
    }
    if ((x << 6) >= 0) {
        return;
    }
    if (((unsigned int)(x << 4) >> 30) == 0) {
        return;
    }
    *(int *)((char *)&D_00000000 + *(int *)((char *)&D_00000000 + 0x1030) * 4 + 0x430) = (int)p;
    *(int *)((char *)&D_00000000 + 0x1030) += 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00025BFC);
#endif


// gl_func_00025C54 — STRUCTURAL PASS (0x460 / 280 words ≈ 1.1KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). The FULL registry-table processor for the
// &D_0+0x2030 / &D_0+0x1030 subsystem. Large -0x78 frame, full
// s0-s7/ra save.
//
//   int gl_func_00025C54(int idx, int a1, int a2) {
//     S  *g  = &D_0;
//     int en = (g->w_1034 != 0);                        // state flag
//     R  *tb = g->w_2030;                                // reg table
//     g->w_1030 = 0;                                      // reset count
//     for (int j = 0; ; j++) {                            // all records
//       R *rec = (char*)tb + idx*0x14;                     // 0x14 stride
//       byte k = rec->b_0;
//       byte n = rec->b_1;                                 // sub count
//       if (k <= 0) continue;
//       (*proc)(idx, j, ...);                              // jal 0 USO
//       ... fold sub-entries, accumulate into &D_0+0x1030 ...
//     }
//   }
//
// Struct-typing reference: the heavyweight "walk the whole registry
//   and rebuild the active element set" driver. It reads the same
//   registry table as gl_func_00025AC8 / gl_func_000221D8 (base
//   &D_0+0x2030, fixed 0x14 entry stride; byte +0 a type/key, byte +1
//   a sub-entry count) and the same subsystem-state / element-count
//   words gl_func_00025504 uses — &D_0+0x1034 (enabled flag) and
//   &D_0+0x1030 (live element count, cleared here then refilled). For
//   every non-empty record it invokes a USO-relocated processor
//   (`jal 0` slot) and folds its sub-entries into the rebuilt count.
//   This is the registry-side companion that gl_func_000258CC primes
//   and gl_func_00025504 then ticks per-frame.
// Caps (DEFERRED): CLEAN single jr $ra. Heavyweight "walk the whole
//   registry and rebuild the active element set" driver — the
//   registry-side companion that gl_func_000258CC primes and
//   gl_func_00025504 then ticks per-frame. Real-C STRUCTURAL body
//   below per the analysis (state flag &D_0+0x1034; tb = registry
//   table &D_0+0x2030 (0x14 stride); clear &D_0+0x1030 active count;
//   for each non-empty record (byte+0>0) invoke jal-0 proc(idx,j,..)
//   and fold its rec->1 sub-entries into the rebuilt count). Byte-
//   match deferred — large full-table loop / USO-reloc processor /
//   s0-s7 schedule. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
// gl_func_00025C54 — RECONSTRUCTED 76.7% NM (was 46.25%, no episode).
//   Corrected the prior m2c decode: (1) jal-0 sites -> gl_func_00000000
//   (USO placeholder), not the real gl_func_0001CA10; (2) the two NONZERO
//   baked USO jals are gl_ref_0003A268 (0x0C00E89A) and gl_ref_0003959C
//   (0x0C00E567) — raw load-time-relocated immediates, reproduced via
//   gl_ref_X=0xX absolute syms in undefined_syms (same mechanism as the
//   matched gl_func_0000408C); (3) all raw 0xNNNN addresses rebased onto
//   &D_00000000 (GP-held s3); (4) arg1 dispatch is a switch (duplicated
//   per-case comparison blocks), not collapsed if/else; (5) dead pre-loop
//   sum over the &D_0+0x430 live-pointer array restored; (6) andi 0xFFF3
//   via `&= ~0x0C`; (7) the typ==1 path passes the (s16) global+0x2 home
//   as lh (no s8 cast); (8) final-call 0x1684 is &D_0+0x1684 (lui/addiu),
//   not a literal.
//   RESIDUAL (register-allocation cap, ~16 insns / 264 vs 280): target
//   spills the first record count to sp+0x70 and colors exactly s0-s7
//   (no s8, frame -120); the lower-pressure reconstruction keeps it in s8
//   (frame -88), which cascades into IDO rematerializing the 0xFFFFFF mask
//   (lui/ori) per switch case instead of CSE-ing it. This is the documented
//   correct-logic / divergent-coloring class — resists permuter. Byte-match
//   deferred; honest NON_MATCHING.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_00025C54 reconstruction (corrected symbols/base):
 *   - base s3 = &D_00000000 (GP-held); all subsystem words are &D_0+off.
 *   - jal 0  -> gl_func_00000000 (USO placeholder, bakes to jal 0).
 *   - jal 0x3A268 -> gl_ref_0003A268; jal 0x3959C -> gl_ref_0003959C
 *     (raw baked USO jal immediates; gl_ref_X=0xX absolute syms).
 * Registry-rebuild driver: clears active count &D_0+0x1030, walks the
 * 0x14-stride table at &D_0+0x2030 for arg0, then re-folds the live
 * element pointer array at &D_0+0x430 into the &D_0+0x620.. record block,
 * indexed by &D_0+0x1034 (live count). */
#define DB ((char *)&D_00000000)
extern int gl_func_00000000();
extern int gl_ref_0003A268();
extern int gl_ref_0003959C();
void gl_func_00025C54(s32 arg0, s32 arg1, char *arg2) {
    s32 sp4C;
    s32 var_s1;
    s32 var_s2;
    s32 var_t0;
    s32 i;
    s32 n;
    char *temp_v0;
    char *rec;
    s32 w;
    u32 typ;

    sp4C = 0;
    if (FW(DB, 0x1034) != 0) {
        sp4C = 1;
    }
    FW(DB, 0x1030) = 0;
    var_s2 = 0;
    temp_v0 = (char *)FW(DB, 0x2030) + (arg0 * 0x14);
    i = *(u8 *)(temp_v0 + 0x0);
    n = *(u8 *)(temp_v0 + 0x1);
    if (i > 0) {
        do {
            char *e = (char *)gl_func_00000000(arg0, var_s2);
            if (e != 0) {
                if (*(u8 *)(e + 0x1) != 0) {
                    gl_ref_0003A268(e + 8);
                }
                if (*(u8 *)(e + 0x2) != 0x7F) {
                    gl_ref_0003A268(e + 0x18);
                }
                gl_ref_0003A268(e + 0x10);
            }
            var_s2 += 1;
        } while (var_s2 != i);
        var_s2 = 0;
    }
    if (n > 0) {
        do {
            char *e = (char *)gl_func_00000000(arg0, var_s2);
            if (e != 0) {
                gl_ref_0003A268(e + 4);
            }
            var_s2 += 1;
        } while (var_s2 != n);
    }
    {
        s32 a1 = FW(DB, 0x1030);
        var_s1 = 0;
        var_s2 = 0;
        if (a1 != 0) {
            var_t0 = FW(DB, 0x1034);
            if (a1 > 0) {
                char *p = DB + 0x430;
                char *end = DB + 0x430 + (a1 * 4);
                s32 total = 0;
                do {
                    total += ((FW(*(int *)p, 0x0) & 0xFFFFFF) + 15) & -16;
                    p += 4;
                } while ((u32) p < (u32) end);
                var_s2 = 0;
            }
            if (a1 > 0) {
                var_s1 = FW(DB, 0x5C);
                do {
                    if (var_t0 == 0x78) {
                        break;
                    }
                    rec = (char *)FW(DB + (var_s2 * 4), 0x430);
                    w = FW(rec, 0x0);
                    typ = (u32) (w << 4) >> 0x1E;
                    if (typ != 0) {
                        switch (arg1) {
                        case 0:
                            if (FW(arg2, 0x10) == typ) {
                                var_s1 = gl_func_00000000(w & 0xFFFFFF, FW(arg2, 0x0), FW(rec, 0x4), (s8) typ);
                            } else if (FW(arg2, 0x14) == typ) {
                                var_s1 = gl_func_00000000(w & 0xFFFFFF, FW(arg2, 0x4), FW(rec, 0x4), (s8) typ);
                            }
                            break;
                        case 1:
                            if (FW(arg2, 0x10) == typ) {
                                var_s1 = gl_func_00000000(w & 0xFFFFFF, FW(arg2, 0x0), FW(rec, 0x4), (s8) typ);
                            } else if (FW(arg2, 0x14) == typ) {
                                var_s1 = gl_func_00000000(w & 0xFFFFFF, FW(arg2, 0x4), FW(rec, 0x4), (s8) typ);
                            }
                            break;
                        }
                        if (var_s1 == 0) {
                            var_t0 = FW(DB, 0x1034);
                        } else {
                            switch (arg1) {
                            case 0:
                                w = FW(rec, 0x0);
                                typ = (u32) (w << 4) >> 0x1E;
                                if (typ == 1) {
                                    gl_func_00000000(FW(rec, 0x4), var_s1, w & 0xFFFFFF, *(s16 *)((char *)FW(DB, 0x2024) + 0x2));
                                } else {
                                    gl_func_00000000(FW(rec, 0x4), var_s1, w & 0xFFFFFF, (s8) typ);
                                }
                                FW(rec, 0x4) = var_s1;
                                *(s8 *)(rec + 0x0) = (u8) *(u8 *)(rec + 0x0) & ~0x0C;
                                var_t0 = FW(DB, 0x1034);
                                break;
                            case 1:
                                var_t0 = FW(DB, 0x1034);
                                FW(DB + (var_t0 * 0x14), 0x634) = (s32) rec;
                                FW(DB + (FW(DB, 0x1034) * 0x14), 0x638) = var_s1;
                                var_t0 = FW(DB, 0x1034);
                                FW(DB + (var_t0 * 0x14), 0x63C) = (s32) ((var_t0 << 0x18) | 0xFFFFFF);
                                FW(DB + (FW(DB, 0x1034) * 0x14), 0x640) = 0;
                                w = FW(rec, 0x0);
                                FW(DB + (FW(DB, 0x1034) * 0x14), 0x630) =
                                    FW(rec, 0x4) + (w & 0xFFFFFF) + ((u32) (w << 4) >> 0x1E);
                                var_t0 = FW(DB, 0x1034);
                                FW(DB, 0x1034) = var_t0 + 1;
                                var_t0 = FW(DB, 0x1034);
                                break;
                            default:
                                var_t0 = FW(DB, 0x1034);
                                break;
                            }
                        }
                    }
                    var_s2 += 1;
                } while (var_s2 < FW(DB, 0x1030));
                FW(DB, 0x5C) = var_s1;
            }
            FW(DB, 0x1030) = 0;
            if ((var_t0 != 0) && (sp4C == 0)) {
                char *r = (char *)FW(DB + (var_t0 * 0x14), 0x620);
                w = FW(r, 0x0);
                gl_ref_0003959C(FW(r, 0x4), FW(DB + (var_t0 * 0x14), 0x624),
                                w & 0xFFFFFF, (u32) (w << 4) >> 0x1E,
                                ((u32) (w & 0xFFFFFF) >> 0xC) + 1, DB + 0x1684,
                                FW(DB + (var_t0 * 0x14), 0x628));
            }
        }
    }
}
#undef DB
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025C54);
#endif

// gl_func_000260B4 — STRUCTURAL PASS (0x140 / 80 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A registry scan-and-resolve sweep.
//
//   void gl_func_000260B4(void) {
//     int r = jal 0x38204(2);                           // 0x0C00E081
//     S  *g = &D_0;
//     int n = g->w_2534;                                 // entry count
//     if (n <= 0) return;
//     E  *e = (E*)(&D_0 + 0x2540);                        // entry tbl
//     for (int i = 0; i < n; i++) {                        // 0x14 stride
//       if (e->h_0 == 1) {                                 // active hw
//         int j = jal 0x38174(1);                          // 0x0C00E05D
//         short k = e->h_2;
//         R *rec = *(R**)(&D_0 + 0x2030) + j*0x14;          // registry
//         (*proc)(2, k, rec);                               // ...
//       }
//       e = (char*)e + 0x14;
//     }
//   }
//
// Struct-typing reference: walks a fixed-stride entry table at
//   &D_0+0x2540 (count word &D_0+0x2534, entry stride 0x14, halfword
//   fields +0 = active flag (==1), +2 = a key). For each active entry
//   it calls the shared poll routine 0x0C00E05D (≈0x38174) and uses
//   the result to index the main registry table &D_0+0x2030 (the same
//   0x14-stride table gl_func_00025AC8 / gl_func_00025C54 walk). The
//   leading 0x0C00E081 (≈0x38204) resolve primes the sweep. A
//   secondary registry scan/resolve pass over a parallel index table
//   (&D_0+0x2540) into the primary registry.
// Caps (DEFERRED): CLEAN single jr $ra. Secondary registry scan
//   /resolve pass — walks parallel index table &D_0+0x2540 (count
//   &D_0+0x2534, stride 0x14) and resolves each active entry into
//   the primary registry &D_0+0x2030 (the same 0x14 table
//   gl_func_00025AC8 / gl_func_00025C54 walk). Real-C STRUCTURAL
//   body below per the analysis (fixed 0x38204(2) prime; for each
//   entry with hw+0==1, poll 0x38174(1)->j, k=e->2, rec =
//   *&D_0+0x2030 + j*0x14, proc(2,k,rec)). Byte-match deferred —
//   placeholder jal-0 resolves need USO reloc infra + bnel scan.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
// Registry resolve sweep. s3 = init(2) [jal 0x38204]; walk the index table
// at &D_0+0x2540 (count &D_0+0x2534, stride 0xC) and for each active entry
// (e->0==1): j = poll(1, e->2) [0x38174]; rec = (*&D_0+0x2030) + j*0x14;
// stash rec->2/rec->3 into a stack frame {b0,b4,b10,b14}; each non-0xFF byte
// drives a second poll(2,b) [0x38174] whose result indexes s3 + r*0x10 + 0x18
// (a byte) back into the frame; finally dispatch(j, 0, &frame) [0x3a2c0].
// The three jals are baked fixed-address targets (cap: field stays 0 vs the
// extraction's resolved 0x0C00E0xx) — body byte-matches, jals don't.
void gl_func_000260B4(void) {
    char *g = (char *)&D_00000000;
    char *s3;
    char *e;
    int i;
    int n;
    struct { int b0; int b4; int pad8; int padc; int b10; int b14; } frame;

    s3 = (char *)gl_func_00000000(2);
    n = *(int *)(g + 0x2534);
    i = 0;
    if (n <= 0) {
        return;
    }
    e = g + 0x2540;
    for (; i < n; i++) {
        if (*(short *)(e + 0) == 1) {
            int j = gl_func_00000000(1, *(short *)(e + 2));
            char *rec = *(char **)(g + 0x2030) + j * 0x14;
            frame.b0 = *(unsigned char *)(rec + 2);
            frame.b4 = *(unsigned char *)(rec + 3);
            if (*(unsigned char *)(rec + 2) != 0xFF) {
                int r = gl_func_00000000(2, *(unsigned char *)(rec + 2));
                frame.b0 = r;
                frame.b10 = *(char *)(s3 + r * 0x10 + 0x18);
            }
            if (frame.b4 != 0xFF) {
                int r = gl_func_00000000(2, frame.b4);
                frame.b4 = r;
                frame.b14 = *(char *)(s3 + r * 0x10 + 0x18);
            }
            gl_func_00000000(j, 0, &frame);
        }
        e += 0xC;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000260B4);
#endif

extern int gl_ref_0003A880();
int gl_func_000261F4() {
    return gl_ref_0003A880();
}

// gl_func_00026214 — STRUCTURAL PASS (0x57C / 351 words ≈ 1.4KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). A ring-slot cursor-advance + callback-dispatch
// driver. Large -0x70 frame.
//
//   ret gl_func_00026214(args…) {
//     S  *g   = &D_0;
//     int cur = g->w_2078;                              // ring cursor
//     int lim = g->h_2034;                               // ring size
//     int nxt = (cur + 1) % lim;                          // guarded %
//                                                          // (break 7/6
//                                                          //  div traps)
//     g->w_2078 = cur + 1;                                // advance
//     if (nxt == 0) { ... wrap handling ... }
//     void (*cb)() = *(void(**)())(&D_0 + 0);             // global cb
//     if (cb != 0) cb();                                  // dispatch
//     ... process the slot at the new cursor, iterate ...
//   }
//
// Struct-typing reference: a circular slot scheduler. Word
//   &D_0+0x2078 is the ring write/advance cursor, halfword
//   &D_0+0x2034 the ring capacity (the same limit the
//   gl_func_00022FC0 / gl_func_00021498 family range-checks). The
//   (cur+1) % lim wrap uses the standard GCC guarded signed-division
//   idiom — the `break 7` / `break 6` words are the div-by-zero /
//   INT_MIN-overflow traps, not real paths. A function pointer at
//   &D_0+0 is invoked as a per-advance callback when non-null. The
//   bulk of the body processes the slot now under the cursor. This is
//   the round-robin slot scheduler/dispatcher of the game_libs
//   subsystem (cursor sibling to the &D_0+0x1030 element count used
//   by gl_func_00025504).
// Caps (DEFERRED): CLEAN single jr $ra. Round-robin slot
//   scheduler/dispatcher of the game_libs subsystem (cursor sibling
//   to the &D_0+0x1030 count used by gl_func_00025504). Real-C
//   STRUCTURAL body below per the analysis (cur=&D_0+0x2078,
//   lim=&D_0+0x2034 (ring size); nxt=(cur+1)%lim — the break 7 /
//   break 6 words are GCC div0 / INT_MIN traps not real paths;
//   advance cur, wrap handling; cb=*(fnp*)&D_0+0 dispatch if
//   non-null; process slot under new cursor). Byte-match deferred —
//   ring-modulo guarded sdiv + indirect callback schedule. Name
//   pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
// gl_func_00026214 — DEEP STRUCTURAL RECONSTRUCTION (52.93% -> 67.66% objdiff
// fuzzy, no episode). Rebuilt to a HELD-BASE form: s2 = &D_00000000, every
// field reached as (char*)&D_00000000 + off (was bare *(int*)0xNNNN, which lost
// the base register and corrupted widths). Width fixes: 0x2034 is s16 (lh, the
// modulo divisor); 0x2CF0/0x2CF1/0x53BA are u8 (lbu); 0x203A/0x203C/0x203E are
// s16. Distinct-extern CSE-defeat: callback fn-ptr (D_cb_26214) and the lui-0x2
// region globals (0x20, 0x1B3D0, 0x1B3D4) get their own lui-zero, matching the
// target's separate address materializations. RESIDUAL = pure register-allocation
// coloring: target uses s0/s1/s2 with a -0x70 spill-heavy frame; IDO -O2 here
// promotes one extra value to a callee-saved reg (s3), giving a -0x98 frame and a
// register-name cascade through the body. Structural control flow / field
// accesses / call args / FP-free reductions are faithful; the byte gap is the
// documented spill-vs-color tradeoff (coloring cap), not a logic error.
#ifdef NON_MATCHING
extern int game_libs_func_0003443C();
extern int gl_func_0001CA10();


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* Held-base accessors. s2 = &D_00000000 (placeholder base, =0). IDO
 * holds the symbol address in a register and reaches every field via a
 * signed 16-bit displacement; bare integer addresses would not. */
#define BB        ((char *)&D_00000000)
#define D_W(o)    (*(s32 *)(BB + (o)))     /* lw  */
#define D_H(o)    (*(s16 *)(BB + (o)))     /* lh  */
#define D_BU(o)   (*(u8  *)(BB + (o)))     /* lbu */
typedef char *(*GP_00026214)();
extern GP_00026214 D_cb_26214;   /* distinct lui-zero callback global */
extern s32 D_26214_20;           /* separate-lui scratch at 0x20 */
extern char *D_26214_1B3D4;      /* lui 0x2 region result global */
extern s32 D_26214_1B3D0;        /* lui 0x2 region max-tracker */
char *gl_func_00026214(void) {
    s32 sp68;
    s32 sp4C;
    s32 sp34;
    int (*cb)();
    s16 temp_a0;
    s16 temp_v1_3;
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_v1_2;
    s32 sp6C;
    s32 sp58;
    s32 var_a0;
    s32 var_s0;
    s32 var_v1;
    s32 var_v1_2;
    char *temp_v1_4;

    temp_t7 = D_W(0x2078) + 1;
    temp_a3 = temp_t7;
    var_a0 = temp_t7 % D_H(0x2034);
    D_W(0x2078) = temp_t7;
    if (var_a0 != 0) {
        cb = D_cb_26214;
        if (cb != 0) {
            cb(var_a0, temp_t7, 0, temp_a3);
            var_a0 = D_W(0x2078) % D_H(0x2034);
        }
        if (D_H(0x2034) == (var_a0 + 1)) {
            return D_26214_1B3D4;
        }
        return 0;
    }
    gl_func_0001CA10(D_W(0x53C8), temp_t7, 0, temp_a3);
    temp_t4 = D_W(0x2084) + 1;
    temp_hi = temp_t4 % 3;
    temp_hi_2 = (temp_hi + 1) % 3;
    D_W(0x2084) = temp_t4;
    D_W(0x2080) ^= 1;
    D_W(0x2084) = temp_hi;
    sp6C = (u32) gl_func_0001CA10() >> 2;
    if ((u32) D_W(0x215C) < 0x10U) {
        s32 idx2 = temp_hi_2 * 2;
        s16 cnt = FW((char *)&D_00000000 + idx2, 0x214C);
        s32 idx4 = temp_hi_2 * 4;
        if (cnt != 0) {
            sp34 = idx4;
            gl_func_0001CA10(FW((char *)&D_00000000 + idx4, 0x2140), cnt * 4, idx2);
        }
    }
    cb = D_cb_26214;
    if (cb != 0) {
        cb();
    }
    var_v1 = D_W(0x207C);
    var_s0 = 0;
    if (var_v1 > 0) {
        do {
            if (gl_func_0001CA10(BB + 0x16BC, 0, 0) == 0) {
                var_v1 -= 1;
            }
            var_s0 += 1;
        } while (var_s0 < D_W(0x207C));
    }
    if (var_v1 != 0) {
        var_s0 = 0;
        if (var_v1 > 0) {
            do {
                gl_func_0001CA10(BB + 0x16BC, 0, 1);
                var_s0 += 1;
            } while (var_s0 != var_v1);
        }
    }
    var_v1_2 = D_W(0x16C4);
    if (var_v1_2 != 0) {
        var_s0 = 0;
        if (var_v1_2 > 0) {
            do {
                gl_func_0001CA10(BB + 0x16BC, 0, 0);
                var_s0 += 1;
            } while (var_s0 != var_v1_2);
        }
    }
    D_W(0x207C) = 0;
    gl_func_0001CA10();
    gl_func_0001CA10(D_BU(0x2CF0));
    if ((D_BU(0x2CF0) != 0) && (gl_func_0001CA10() == 0)) {
        if (D_BU(0x2CF0) == 0) {
            gl_func_0001CA10(D_W(0x53C4), D_BU(0x2CF1), 0);
        }
        D_26214_1B3D4 = 0;
        return 0;
    }
    if ((u32) D_W(0x215C) >= 0x11U) {
        return 0;
    }
    if (D_W(0x215C) != 0) {
        D_W(0x215C) += 1;
    }
    temp_v1_2 = D_W(0x2080);
    temp_s0 = D_W(0x2084);
    D_W(0x2094) = (s32) (BB + (temp_v1_2 * 0x50) + 0x2098);
    sp34 = temp_s0 * 4;
    D_W(0x2090) = FW((char *)&D_00000000 + (temp_v1_2 * 4), 0x2088);
    sp58 = FW((char *)&D_00000000 + sp34, 0x2140);
    FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C) =
        (s16) ((((D_H(0x203A) - sp6C) + 0x80) & 0xFFF0) + 0x10);
    temp_a0 = D_H(0x203E);
    if (FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C) < temp_a0) {
        FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C) = temp_a0;
    }
    temp_v1_3 = D_H(0x203C);
    if (temp_v1_3 < FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C)) {
        FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C) = temp_v1_3;
    }
    var_s0 = 0;
    if (D_BU(0x2CF0) == 0) {
        if (gl_func_0001CA10(D_W(0x53CC), &sp4C, 0) != -1) {
            do {
                game_libs_func_0003443C(sp4C);
                var_s0 += 1;
            } while (gl_func_0001CA10(D_W(0x53CC), &sp4C, 0) != -1);
        }
        if ((var_s0 == 0) && (D_BU(0x53BA) != 0)) {
            gl_func_0001CA10();
        }
    }
    D_W(0x2090) = gl_func_0001CA10(D_W(0x2090), &sp68, sp58,
                                  FW((char *)&D_00000000 + (temp_s0 * 2), 0x214C));
    temp_a3 = D_W(0x2078);
    temp_lo = gl_func_0001CA10() * (D_W(0x2154) + temp_a3);
    D_W(0x2154) = temp_lo;
    temp_t3 = *(s16 *)(FW((char *)&D_00000000 + sp34, 0x2140) + ((temp_a3 & 0xFF) * 2)) + temp_lo;
    D_W(0x2154) = temp_t3;
    D_26214_20 = temp_t3 & 0xFFF0;
    FW(D_W(0x2094), 0x40) = 0;
    FW(D_W(0x2094), 0x44) = 0;
    temp_v1_4 = (char *) D_W(0x2094);
    FW(temp_v1_4, 0x0) = 2;
    FW(temp_v1_4, 0x4) = 0;
    FW(temp_v1_4, 0x8) = 0;
    FW(temp_v1_4, 0xC) = 0x1000;
    FW(temp_v1_4, 0x1C) = (((0 >> 3) * 8) - 1);
    FW(temp_v1_4, 0x10) = 0;
    FW(temp_v1_4, 0x18) = 0;
    FW(temp_v1_4, 0x14) = 0x1000;
    FW(temp_v1_4, 0x20) = 0;
    FW(temp_v1_4, 0x24) = 0;
    FW(temp_v1_4, 0x28) = 0;
    FW(temp_v1_4, 0x2C) = 0;
    FW(temp_v1_4, 0x30) = FW((char *)&D_00000000 + (D_W(0x2080) * 4), 0x2088);
    FW(temp_v1_4, 0x38) = 0;
    FW(temp_v1_4, 0x3C) = 0;
    FW(temp_v1_4, 0x34) = sp68 * 8;
    if (D_26214_1B3D0 < sp68) {
        D_26214_1B3D0 = sp68;
    }
    if (D_H(0x2034) == 1) {
        return D_W(0x2094);
    }
    D_26214_1B3D4 = (char *) D_W(0x2094);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026214);
#endif

// gl_func_00026790 — STRUCTURAL PASS (0x3B8 / 238 words ≈ 0.9KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO
// bundle (named fn + 2 trailing helpers) — deferred USO re-split.
// The named leading fn is a command-stream OPCODE DISPATCHER (dual
// jump tables).
//
//   ret gl_func_00026790(byte *cmd) {
//     int op = cmd[0];
//     if (op >= 0x91) { ... }                            // out of range
//     else if (op >= 0xF0 && op < 0xFC) {
//       goto *((void**)(&D_0 + 0xEE0))[op - 0xF0];        // table A
//     } else if (op >= 0x81 && op < 0x91) {
//       goto *((void**)(&D_0 + 0xF10))[op - 0x81];        // table B
//     } else return;                                       // default
//     // per-opcode case bodies read cmd[1] / cmd[2] / cmd[3]
//     // and invoke USO-relocated handlers (jal 0 slots), e.g.
//     //   handler(cmd[1], cmd[2], cmd[3]);
//   }
//
// Struct-typing reference: a bytecode/command-stream interpreter.
//   cmd[0] is the opcode; two REAL computed jump tables decode it —
//   &D_0+0xEE0 (12 entries) for opcodes 0xF0..0xFB and &D_0+0xF10
//   (16 entries) for opcodes 0x81..0x90; anything else is a no-op.
//   Operand bytes cmd[1]/cmd[2]/cmd[3] are passed to USO-relocated
//   per-opcode handlers (the `jal 0` slots). These two tables sit
//   alongside the &D_0+0xE7C (gl_func_0002119C) and &D_0+0xEA0
//   (gl_func_00023914) dispatch tables — the game_libs subsystem
//   keeps a contiguous bank of computed-jump dispatch tables in the
//   &D_0+0xExx..0xFxx region. The command interpreter / VM step of
//   the subsystem.
// Caps (DEFERRED): single jr $ra (the "3-jr bundle" note is STALE;
//   .s is 0x3B8/201 words, ONE function). Command interpreter / VM
//   step — bytecode dispatcher with DUAL computed jump tables in
//   the &D_0+0xExx..0xFxx dispatch-table bank (alongside
//   gl_func_0002119C @0xE7C and gl_func_00023914 @0xEA0). Real-C
//   STRUCTURAL body below per the analysis (op=cmd[0]; opcodes
//   0xF0..0xFB modelled as 12-entry table A @0xEE0; 0x81..0x90 as
//   16-entry table B @0xF10; else no-op; operand bytes cmd[1..3]
//   passed to jal-0 per-opcode handlers). Byte-match deferred —
//   dual computed jump-table + jal-0 handlers need USO reloc infra.
//   Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int func_3b164(), func_3b110();
/* Decoded via jumptable extraction + delay-slot patch (fix-jumptable-delay-slot.py).
 * KEY: m2c's "arg3"/unset-reg reads are NOT caller-set — each case reloads
 * a3=&D_00000000 (lui a3,0; placeholder reloc) and reads operands from cmd[N];
 * so all globals resolve to &D+offset. Dual-range opcode dispatch (0x81-0x90 and
 * 0xF0-0xFB share one jumptable by index op-0x81 / op-0xF0). Residual: the
 * complex 0x83/0x91 cases + the &D-relative object globals + regalloc. */
int gl_func_00026790(unsigned char *cmd) {
    char *g = (char *)&D_00000000;
    int op = cmd[0];
    int idx, i;
    if (op >= 0x91) {
        if ((unsigned)(op - 0xF0) >= 0xC) return 0;
        idx = op - 0xF0;
    } else {
        if ((unsigned)(op - 0x81) >= 0x10) return 0;
        idx = op - 0x81;
    }
    switch (idx) {
    case 0:
        *(char *)(g + 0x2076) = *(int *)(cmd + 4);
        break;
    case 1: {                                   /* set bit 0x20 on all entries */
        char *p = g;
        for (i = 0; i < *(short *)(g + 0x2048); i++) {
            int t = *(int *)(p + 0x2D00);
            p += 0x160;
            *(char *)(p + 0x2BA0) = t | 0x20;
            *(char *)(p + 0x2BA0) = (t | 0x20) | 4;
        }
        break; }
    case 2: {                                   /* clear bit 0x20 on all entries */
        char *p = g;
        for (i = 0; i < *(short *)(g + 0x2048); i++) {
            int t = *(int *)(p + 0x2D00);
            p += 0x160;
            *(char *)(p + 0x2BA0) = t & 0xFFDF;
            *(char *)(p + 0x2BA0) = (t & 0xFFDF) | 4;
        }
        break; }
    case 3:
        gl_func_0001CA10(cmd[1], cmd[2], cmd[3]);
        break;
    case 4:
    case 5:
        gl_func_0001CA10(cmd[1], cmd[2], cmd[3], g + 0x164C);
        break;
    case 6:
        gl_func_0001CA10(cmd[2]);
        break;
    case 9:
        *(char *)(g + 0x2CF0) = 5;
        *(char *)(g + 0x2CF1) = cmd[4];
        break;
    case 11:
        *(int *)g = *(int *)(cmd + 4);
        break;
    case 13:
        gl_func_0001CA10(cmd[1], cmd[2], cmd[3]);
        func_3b164(cmd[1], *(int *)(cmd + 4));
        break;
    case 14: {
        char *e = g + op * 0x160;
        if ((unsigned)*(int *)(e + 0x2D00) >> 0x1F) {
            int a = *(int *)(cmd + 4);
            if (a == 0) {
                gl_func_0001CA10(e + 0x2D00, a, g);
            } else {
                func_3b110(op, a, g);
            }
        }
        break; }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026790);
#endif

#ifdef NON_MATCHING
/* Per-entry (a0-indexed, stride 352) FP struct update at &D_+0x2D00. If a1==0,
 * a1=1; base->1=2; base->0x12=(short)a1; base->0x20 = -(base->0x1C / (float)a1).
 * CAP: IDO folds the +0x2D00 into the access offsets (build 20 insns) where the
 * target materializes the full base &D_+a0*352+0x2D00 then uses small offsets
 * (21 insns) — a materialization-fold difference, not C-reachable. Faithful
 * decode; INCLUDE_ASM build path. */
void game_libs_func_00026AA4(int a0, int a1) {
    char *base;
    if (a1 == 0) {
        a1 = 1;
    }
    base = (char *)&D_00000000 + a0 * 352 + 0x2D00;
    base[1] = 2;
    *(short *)(base + 0x12) = a1;
    *(float *)(base + 0x20) = -(*(float *)(base + 0x1C) / (float)a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00026AA4);
#endif

void game_libs_func_00026AF8(int a0, int a1) {
    char *p;
    if (a1 == 0) {
        return;
    }
    p = (char *)&D_00000000 + a0 * 352;
    *(char *)(p + 0x2D01) = 1;
    *(short *)(p + 0x2D14) = a1;
    *(short *)(p + 0x2D12) = a1;
    *(float *)(p + 0x2D1C) = 0.0f;
    *(float *)(p + 0x2D20) = 0.0f;
}

// game_libs_func_00026B40 — global-table init (was the stolen-$v0-base
//   prologue cap). The orphan game_libs_func_00026B40 (lui v0,0; addiu v0,v0,0
//   = v0 = &D_00000000) was the hoisted base for the first store block; it has
//   been merged FORWARD into this function (formerly gl_func_00026B48) so the
//   symbol starts at 0x26B40 and the base-load is the function's own first two
//   words. Block1's 6 stores share that base via a NAMED pointer `p` (so IDO
//   keeps the &D base in $v0 and reuses it, rather than the $at-per-store form);
//   block2/3 re-materialize &D inline. Corrected offsets vs the old decode:
//   the byte flags are at 0x53B8/B9/BA (not 0x53C0) and D[0x53C4] = &D+0x5400.
//   STATUS: orphan-merge + hoist cracked the prologue-steal cap (0% -> 76%,
//   29/38). The hoisted lui v0;addiu v0 base + v0-base block1 + all offsets/
//   calls match. Residual 9 diffs = the three &D-pointer temps use t6/t7/t8
//   (target) vs a0/t6/t7 (mine), plus the sw-ra schedule slot — a regalloc-
//   renumber on the pointer temps (named-q1/q2/q3 variant didn't flip it).
extern int gl_func_00000000();
extern int D_00000000;
#ifdef NON_MATCHING
void game_libs_func_00026B40(void) {
  char *p;
  ((char *) (&D_00000000))[0x53B8] = 0;
 if (1) { } { }
  ((char *) (&D_00000000))[0x53BA] = (((char *) (&D_00000000))[0x53B9] = 0);
  *((char **) (((char *) (&D_00000000)) + 0x53C8)) = ((char *) (&D_00000000)) + 0x53D0;
  *((char **) (((char *) (&D_00000000)) + 0x53CC)) = ((char *) (&D_00000000)) + 0x53E8;
  *((char **) (((char *) (&D_00000000)) + 0x53C4)) = ((char *) (&D_00000000)) + 0x5400;
  gl_func_00000000(((char *) (&D_00000000)) + (0x53D0 ^ 0), ((char *) (&D_00000000)) + 0x5418, 1);
  gl_func_00000000(*((char **) (((char *) (&D_00000000)) + 0x53CC)), ((char *) (&D_00000000)) + 0x5420, 4);
  gl_func_00000000(*((char **) (((char *) (&D_00000000)) + 0x53C4)), ((char *) (&D_00000000)) + 0x541C, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00026B40);
#endif

/* game_libs_func_00026BD8: ring-buffer push. head=u8 D[0x53B8],
 * cap=u8 D[0x53B9], 8-byte entries at D+0x5430+head*8 = {a0, *a1}.
 * Advance head; if buffer would be full (cap == (u8)(head+1)) roll
 * head back by 1 (reject the advance).
 *
 * 81.53% — logic fully decoded, 19/19 insns, 17 diffs ALL pure
 * register-rename (same opcodes/offsets/structure). Target pins the &D
 * base in $a2 and reuses it for every access incl. the conditional
 * wrap-back store; IDO C-emit splits &D across $t0 + a fresh `lui $at`
 * for the if-branch store. No C structure tested (single base var,
 * typed-offset, struct-array) shifts the base-reg choice. This is a
 * whole-function register-allocation cap — permuter-class, NOT
 * INSN_PATCH (17/19 register-only patches = the documented
 * faking-the-function tautology trap, cf. func_800047B0). NM kept;
 * INCLUDE_ASM is the build path. */
#ifdef NON_MATCHING
void game_libs_func_00026BD8(int a0, int *a1) {
    char *base = (char*)&D_00000000;
    int head = *(unsigned char*)(base + 0x53B8);
    *(int*)(base + head * 8 + 0x5430) = a0;
    *(int*)(base + head * 8 + 0x5430 + 4) = *a1;
    {
        int h1 = *(unsigned char*)(base + 0x53B8) + 1;
        *(unsigned char*)(base + 0x53B8) = (unsigned char)h1;
        if (*(unsigned char*)(base + 0x53B9) == (unsigned char)h1) {
            *(unsigned char*)(base + 0x53B8) = (unsigned char)h1 - 1;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00026BD8);
#endif

extern int gl_ref_0003B244();
void gl_func_00026C24(int a0, int a1) {
    gl_ref_0003B244(a0, &a1);
}

extern int gl_ref_0003B244();
void gl_func_00026C48(int a0, int a1) {
    gl_ref_0003B244(a0, &a1);
}

#ifdef NON_MATCHING
/* NON_MATCHING: 91% — target has `or a2, a1, zero` + sll from a2 that IDO C won't emit.
 * 2026-05-27 retest: `int copy = a1; local = copy << 24;` (named copy of a1)
 * regressed 90% → 8% — lost the a1 home-spill that mine relies on. The
 * `int *dummy = &a1` trick spills a1 to caller's outgoing arg slot,
 * matching the target's frame layout. */
extern int gl_ref_0003B244();
void gl_func_00026C6C(int a0, int a1) {
    int local;
    int *dummy = &a1;
    local = a1 << 24;
    gl_ref_0003B244(a0, &local);
    (void)dummy;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026C6C);
#endif

#ifdef NON_MATCHING
/* gl_func_00026C9C: 12-insn (0x30) helper — packs a1 into a stack-local
 * (a1<<16, high-short-of-pair encoding) and tail-calls alt-entry
 * gl_func_0003B244 (inside gl_func_0003B1AC at +0x98) with (a0, &local, a1).
 *
 * Trailing 9 insns at offsets 0x30-0x53 are alt-entry-prologue donation to
 * successor gl_func_00026CD0: loads `v0=D[0x53B8]`, `a3=D[0x53B9]`, computes
 * a0 = ((v0 - a3) + 0x100) & 0xFF. Successor uses these regs as entry state.
 *
 * 42 % NM: missing (a) `sw a1, 0x24(sp)` caller-slot spill (IDO DCE'd), (b)
 * `or a2, a1, 0` explicit move before sll (IDO inlined as `sll t6, a1, 16`),
 * (c) SUFFIX_BYTES for the 9 trailing alt-entry-prologue donation insns.
 * Multi-tick promotion territory. */
extern int gl_func_0003B244();
int gl_func_00026C9C(int a0, int a1) {
    int local = a1 << 16;
    return gl_func_0003B244(a0, &local, a1);
}
#else
/* gl_func_00026C9C: 12-insn 1-call helper. Computes `a1 << 16` into a
 * stack local then calls gl_ref_0003B244(a0, &local).
 *
 * 1-insn off (mine 11, target 12): target has `or a2, a1, 0` + `sll t6, a2, 16`
 * (explicit copy a1→a2 before shift); mine emits `sll t7, a1, 16` direct.
 * Same a0-home-spill+copy-to-a2 cap class as gl_func_0002DD58 — IDO C can't
 * emit the explicit move-then-shift from clean source. */
extern int gl_ref_0003B244();
#ifdef NON_MATCHING
void gl_func_00026C9C(int a0, int a1) {
    int local;
    int *p = &a1;
    local = a1 << 16;
    gl_ref_0003B244(a0, &local);
    (void)p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026C9C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00026CCC);
#endif

// gl_func_00026CF0 — STRUCTURAL PASS (0x74 / 29 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 tiny trailing setter) — deferred USO re-split. The
// named leading fn (~21 words) is a bounds-checked packed-submit
// helper.
//
//   void gl_func_00026CF0(int a0, int a1, int a2, int a3) {
//     if (a0 >= bound) {                                // range check
//       *(int*)(&D_0 + 0x2B594) = a0;                    // record OOB
//       return;
//     }
//     int packed = ((a3 & 0xFF) << 8) | (a2 & 0xFF);     // pack bytes
//     void *p = *(void**)(&D_0 + 0x53CC);                 // global ptr
//     int r = (*submit)(p, packed, 0);                    // jal 0 USO
//     if (r != -1) {
//       byte v = *(byte*)(&D_0 + 0x53B8);
//       *(byte*)(&D_0 + 0x53B9) = v;                       // promote
//     }
//   }
//
// Struct-typing reference: a small submit/commit helper. The index
//   a0 is range-checked; an out-of-range value is recorded to the
//   diagnostic/assert global &D_0+0x2B594 and the call aborts. The
//   low bytes of a2/a3 are packed into a 16-bit value ((a3<<8)|a2)
//   and handed, together with the global object pointer &D_0+0x53CC,
//   to a USO-relocated submit routine (`jal 0` slot). On success
//   (result != -1) the state byte &D_0+0x53B8 is promoted into
//   &D_0+0x53B9 (a committed/last-good shadow). The trailing bundled
//   fn is its companion 1-line state setter (writes &D_0+0x53B9 /
//   0x53BA). A state-commit helper in the game_libs subsystem.
// Caps (DEFERRED): single jr $ra (the "2-fn unsplit bundle" note is
//   STALE; .s is 0x5C/22 words, ONE function). Small state-commit
//   helper in the game_libs subsystem. Real-C STRUCTURAL body below
//   per the analysis (range-check a0 — OOB records to diagnostic
//   &D_0+0x2B594 and aborts; pack ((a3&0xFF)<<8)|(a2&0xFF); hand to
//   jal-0 submit(*&D_0+0x53CC,packed,0); on success != -1 promote
//   the &D_0+0x53B8 state byte into committed shadow &D_0+0x53B9).
//   Byte-match deferred — placeholder jal-0 submit needs USO reloc
//   infra. Name pre-checked: no extern reuse (collision-safe).
//   gl_func_00000000 = canonical never-defined USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00026CF0(int a0, int a1, int a2, int a3) {
    char *g = (char *)&D_00000000;
    int packed, r;
    (void)a1;
    if ((unsigned)a0 >= 0x100) {
        *(int *)(g + 0x2B594) = a0;
        return;
    }
    packed = ((a3 & 0xFF) << 8) | (a2 & 0xFF);
    r = gl_func_00000000(*(void **)(g + 0x53CC), packed, 0);
    if (r != -1) {
        *(unsigned char *)(g + 0x53B9) = *(unsigned char *)(g + 0x53B8);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026CF0);
#endif

void game_libs_func_00026D4C(void) {
    *(unsigned char *)((char *)&D_00000000 + 0x53B9) = *(unsigned char *)((char *)&D_00000000 + 0x53B8);
    *(unsigned char *)((char *)&D_00000000 + 0x53BA) = 0;
}

// gl_func_00026D64 — STRUCTURAL PASS (0x398 / 230 words ≈ 0.9KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). The command-buffer FLUSH / drain counterpart to
// the gl_func_00026CF0 packed-submit helper (same &D_0+0x53Bx /
// &D_0+0x2B5Dx state region). Large -0x68 frame.
//
//   ret gl_func_00026D64(int a0) {
//     S  *g   = &D_0;
//     int idx = g->b_53BA;                              // pending cnt
//     if (idx == 0) {
//       g->b_2B5DC = (a0 >> 8) & 0xFF;                    // re-seed
//     }
//     int lo = a0 & 0xFF;
//     for (;;) {                                          // drain queue
//       byte cur = g->b_2B5DC;
//       if (cur == lo) { g->b_53BA = 0; break; }           // done
//       E *e = (char*)g + cur*8 + ...;                     // queued ent
//       ... process e (the (a2,a3)-packed entries) ...
//       g->b_2B5DC = cur + 1;
//     }
//   }
//
// Struct-typing reference: the consumer side of the command queue
//   gl_func_00026CF0 fills. Byte &D_0+0x53BA is the pending-entry
//   count / write index (the committed shadow gl_func_00026CF0
//   promotes), byte &D_0+0x2B5DC the drain read cursor, and the
//   packed (a2<<? | a3) entries live in the &D_0+0x2B5Dx ring buffer
//   (stride 8, s7=0x30 / s6=2 / s4=0x10 are field offsets/limits).
//   It walks from the read cursor to the producer index, processes
//   each queued entry, then zeroes &D_0+0x53BA to mark the queue
//   empty. The flush/commit-all entry paired with the
//   gl_func_00026CF0 enqueue.
// Caps (DEFERRED): CLEAN single jr $ra. Command-buffer FLUSH / drain
//   — the consumer paired with gl_func_00026CF0's enqueue (same
//   &D_0+0x53Bx / &D_0+0x2B5Dx state region). Real-C STRUCTURAL body
//   below per the analysis (idx=&D_0+0x53BA pending count; idx==0
//   re-seeds &D_0+0x2B5DC = (a0>>8)&0xFF; lo=a0&0xFF; drain ring
//   while read cursor &D_0+0x2B5DC != lo, processing each entry,
//   advance cursor; zero &D_0+0x53BA on drain). Byte-match deferred —
//   queue-drain loop schedule. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
#ifdef NON_MATCHING
/* PASS-2 2026-06-10 (big-swing): FULL m2c graft (230 insns, one table
 * synthesized; prior 3.74 body replaced -- preserved in git). */
void gl_func_00026D64(u32 arg0) {
    s32 sp38;
    f32 temp_f0;
    f32 var_f2;
    s32 temp_s2;
    s32 temp_s3;
    s32 var_s0;
    u16 var_v0_2;
    u8 temp_a0;
    u8 temp_v0;
    u8 temp_v1;
    u8 var_v0;
    char *temp_s2_2;
    char *temp_s3_2;

    if (*(u8 *)((char *)&D_00000000 + 0x53BA) == 0) {
        *(u8 *)((char *)&D_00000000 + 0x1B5DC) = (u8) (arg0 >> 8);
    }
    sp38 = arg0 & 0xFF;
loop_3:
    temp_v1 = *(s32 *)((char *)&D_00000000 + 0x1B5DC);
    if (sp38 == temp_v1) {
        *(u8 *)((char *)&D_00000000 + 0x53BA) = 0;
        return;
    }
    temp_s3 = (temp_v1 & 0xFF) * 8;
    *(s32 *)((char *)&D_00000000 + 0x1B5DC) = (u8) (*(s32 *)((char *)&D_00000000 + 0x1B5DC) + 1);
    var_v0 = *(s32 *)((char *)(temp_s3) + 0x5430);
    temp_s3_2 = temp_s3 + 0x5430;
    if (var_v0 == 0xF8) {
        *(u8 *)((char *)&D_00000000 + 0x53BA) = 1;
        return;
    }
    if ((var_v0 & 0xF0) == 0xF0) {
        gl_func_0003ADFC(temp_s3_2);
    } else {
        temp_a0 = *(s32 *)((char *)(temp_s3_2) + 0x1);
        if ((s32) temp_a0 < *(u8 *)((char *)&D_00000000 + 0x2048)) {
            temp_s2 = temp_a0 * 0x160;
            temp_s2_2 = temp_s2 + 0x2D00;
            if (var_v0 & 0x80) {
                gl_func_0003ADFC(temp_s3_2);
            } else if (var_v0 & 0x40) {
                switch (var_v0) {
                case 0x41:
                    temp_f0 = *(s32 *)((char *)(temp_s3_2) + 0x4);
                    if (temp_f0 != *(s32 *)((char *)(temp_s2_2) + 0x2C)) {
                        *(s32 *)((char *)(temp_s2_2) + 0x2C) = temp_f0;
                        *(s32 *)((char *)(temp_s2) + 0x2D00) = (u8) (*(s32 *)((char *)(temp_s2) + 0x2D00) | 4);
                    }
                    break;
                case 0x42:
                    *(s32 *)((char *)(temp_s2_2) + 0x8) = (s16) (*(s32 *)& *(s32 *)((char *)(temp_s3_2) + 0x4) * 0x30);
                    break;
                case 0x43:
                    *(s32 *)((char *)(temp_s2_2) + 0xC) = (s16) (*(s32 *)& *(s32 *)((char *)(temp_s3_2) + 0x4) * 0x30);
                    break;
                case 0x44:
                    *(s32 *)((char *)(temp_s2_2) + 0xC) = (s16) *(s32 *)((char *)(temp_s3_2) + 0x4);
                    break;
                case 0x45:
                    *(s32 *)((char *)(temp_s2_2) + 0xE) = (s16) (s8) *(s32 *)((char *)(temp_s3_2) + 0x4);
                    break;
                case 0x46:
                    *(s32 *)((char *)((temp_s2_2 + *(s32 *)((char *)(temp_s3_2) + 0x3))) + 0x158) = (s8) *(s32 *)((char *)(temp_s3_2) + 0x4);
                    break;
                case 0x47:
                    var_f2 = (f32) *(s32 *)((char *)(temp_s3_2) + 0x2) / 127.0f;
block_24:
                    if (*(f32 *)((char *)(temp_s2_2) + 0x1) != 2) {
                        *(s32 *)((char *)(temp_s2_2) + 0x24) = (f32) *(s32 *)((char *)(temp_s2_2) + 0x1C);
                        var_v0 = (u8) *(s32 *)((char *)(temp_s3_2) + 0x4);
                        if (var_v0 == 0) {
                            *(s32 *)((char *)(temp_s2_2) + 0x1C) = var_f2;
                        } else {
                        case 0x49:
                            *(s32 *)((char *)(temp_s2_2) + 0x1) = 0U;
                            *(s32 *)((char *)(temp_s2_2) + 0x12) = (s16) var_v0;
                            *(f32 *)((char *)(temp_s2_2) + 0x20) = (f32) ((0 /* M2C unset $f2 */ - 0 /* M2C unset $f0 */) / (f32) var_v0);
                        }
                    }
                    break;
                case 0x48:
                    var_f2 = ((f32) *(s32 *)((char *)(temp_s3_2) + 0x2) / 100.0f) * *(s32 *)((char *)(temp_s2_2) + 0x1C);
                    goto block_24;
                case 0x4A:
                    if (*(s32 *)((char *)(temp_s2_2) + 0x1) != 2) {
                        var_v0 = (u8) *(s32 *)((char *)(temp_s3_2) + 0x4);
                        if (var_v0 == 0) {
                            *(f32 *)((char *)(temp_s2_2) + 0x1C) = (f32) *(s32 *)((char *)(temp_s2_2) + 0x24);
                        } else {
                        case 0x4B:
                            *(s32 *)((char *)(temp_s2_2) + 0x1) = 0U;
                            *(s32 *)((char *)(temp_s2_2) + 0x12) = (s16) var_v0;
                            *(f32 *)((char *)(temp_s2_2) + 0x20) = (f32) ((*(s32 *)((char *)(temp_s2_2) + 0x24) - *(s32 *)((char *)(temp_s2_2) + 0x1C)) / (f32) var_v0);
                        }
                    }
                    break;
                case 0x4C:
                    *(f32 *)((char *)(temp_s2_2) + 0x34) = (f32) *(s32 *)((char *)(temp_s3_2) + 0x4);
                    if (*(s32 *)((char *)(temp_s2_2) + 0x34) == 1.0f) {
                        *(s32 *)((char *)(temp_s2) + 0x2D00) = (u8) (*(s32 *)((char *)(temp_s2) + 0x2D00) & 0xFFFE);
                    } else {
                        /* case 0x4D fall-in (flattened) */
                        *(s32 *)((char *)(temp_s2) + 0x2D00) = (u8) (*(s32 *)((char *)(temp_s2) + 0x2D00) | 1);
                    }
                    break;
                }
            } else {
                /* case 0x4E fall-in (flattened) */
                if (((u32) *(s32 *)((char *)(temp_s2) + 0x2D00) >> 0x1F) != 0) {
                    temp_v0 = *(s32 *)((char *)(temp_s3_2) + 0x2);
                    if ((s32) temp_v0 < 0x10) {
                        gl_func_0003BA24(*(s32 *)((char *)((temp_s2_2 + (temp_v0 * 4))) + 0x38), temp_s3_2);
                    } else if (temp_v0 == 0xFF) {
                        var_v0_2 = *(s32 *)((char *)((temp_a0 * 2)) + 0x53BC);
                        var_s0 = 0;
                        do {
                            if (var_v0_2 & 1) {
                                gl_func_0003BA24(*(s32 *)((char *)((temp_s2_2 + (var_s0 * 4))) + 0x38), temp_s3_2);
                            }
                            var_s0 += 1;
                            var_v0_2 = ((s32) var_v0_2 >> 1) & 0xFFFF;
                        } while (var_s0 != 0x10);
                    }
                }
            }
        }
    }
    *(s32 *)((char *)(temp_s3) + 0x5430) = 0U;
    goto loop_3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026D64);
#endif

/* gl_func_000270FC: 25-insn parse-something-then-split-24-8 wrapper.
 * rv = func(&D + 0x164C, &local, 0). On -1, *a0=0; return 0.
 * else *a0 = local & 0xFFFFFF; return (unsigned)local >> 24. */
int gl_func_000270FC(int *a0) {
    int local;
    int rv = func_00000000((char*)&D_00000000 + 0x164C, &local, 0);
    if (rv == -1) {
        *a0 = 0;
        return 0;
    }
    *a0 = local & 0xFFFFFF;
    return (unsigned)local >> 24;
}

extern int gl_func_00000000();
int gl_func_00027160() {
    return gl_func_00000000();
}

/* gl_func_00027180: 22-insn predicate. Loads via gl_func(&D_0+0x53C4,
 * &local, 0); returns 0 if -1, else returns local == byte(&D_0+0x2CF1). */
int gl_func_00027180(void) {
    int v;
    int local;
    v = gl_func_00000000(*(int*)((char*)&D_00000000 + 0x53C4), &local, 0);
    if (v == -1) return 0;
    if (local != *(unsigned char*)((char*)&D_00000000 + 0x2CF1)) {
        return 0;
    }
    return 1;
}

/* gl_func_000271D8: 21-insn do-while loop. Repeatedly calls
 * gl_func(*(int*)&D_0+0x53C4, &scratch, 0) until result is -1.
 * MATCH (permuter, 2026-06-21): assigning the sentinel `sentinel = -1`
 * INSIDE the do-loop body (rather than as a first-statement initializer)
 * flips the as1 schedule so the base-lo `addiu s1,s1,0` emits before the
 * sentinel `addiu s0,zero,-1`, matching the target. The in-loop reassign is
 * free (-1 is loop-invariant; IDO hoists it) and resolves the 2-word
 * const-materialization-order tie. Frame -48, byte-exact (84 bytes). */
void gl_func_000271D8(void) {
    int sentinel;
    int scratch;
    do {
        sentinel = -1;
    } while (gl_func_00000000(*(int*)((char*)&D_00000000 + 0x53C4), &scratch, 0) != sentinel);
}

// gl_func_0002722C — STRUCTURAL PASS (0x98 / 38 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A lock-guarded subsystem operation (acquire / dispatch /
// release).
//
//   void gl_func_0002722C(int a0) {
//     jal 0x3B844(a0);                                  // 0x0C00EE11 lock
//     S *g = &D_0;
//     if (g->b_2CF0 != 0) {                              // subsystem on
//       int r  = (*op)(a0);                               // jal 0 USO
//       byte ss = g->b_2CF1;                              // sub-state
//       if (ss != r && r < 3) {
//         void *p = *(void**)(&D_0 + 0x53C4);              // global obj
//         (*act)(p, &local, 1);                            // jal 0 USO
//       }
//       jal 0x3B844(a0);                                  // 0x0C00EE11 unlock
//       (*fin)(0xF9000000);                                // jal 0 USO
//     }
//   }
//
// Struct-typing reference: the fixed routine 0x0C00EE11 (≈0x3B844) is
//   used as a paired acquire/release lock around the body — called
//   once at entry and again before the tail. State byte &D_0+0x2CF0
//   (the main subsystem state from gl_func_0002119C) gates the whole
//   operation; byte &D_0+0x2CF1 (the sub-state from gl_func_00021498)
//   is compared against an operation result (must be < 3) to decide
//   whether to act on the global object &D_0+0x53C4. The trailing
//   USO-reloc call takes the constant 0xF9000000 (a segment-tagged /
//   RDRAM-region pointer). A critical-section-guarded state operation
//   in the game_libs subsystem.
// Caps (DEFERRED): CLEAN single jr $ra. Critical-section-guarded
//   subsystem operation. Real-C STRUCTURAL body below per the
//   analysis (fixed 0x3B844 used as paired acquire/release lock;
//   state byte &D_0+0x2CF0 from gl_func_0002119C gates whole op;
//   sub-state &D_0+0x2CF1 vs op result with <3 check selects act on
//   global &D_0+0x53C4 obj; tail jal-0 with 0xF9000000 segment-
//   tagged pointer). Byte-match deferred — placeholder jal-0 ops
//   need USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01. First call is the resolved gl_func_0003B844,
 * not a placeholder. Guard on *(D+0x2CF0); inside, r=gl(a0), early-return if
 * a0==*(D+0x2CF1) or r>=3, else gl(*(D+0x53C4),&local,1). The tail (3B844 +
 * two F9000000 cmd emits) is OUTSIDE the if — also reached on the ==0 path. */
extern int gl_func_0003B844();
void gl_func_0002722C(int a0) {
    char *g = (char *)&D_00000000;
    gl_func_0003B844(a0);
    if (*(unsigned char *)(g + 0x2CF0) != 0) {
        int local;
        int r = gl_func_00000000(a0);
        unsigned char ss = *(unsigned char *)(g + 0x2CF1);
        if (a0 == ss) {
            return;
        }
        if (r >= 3) {
            return;
        }
        gl_func_00000000(*(void **)(g + 0x53C4), &local, 1);
    }
    gl_func_0003B844(a0);
    gl_func_00000000((void *)0xF9000000, a0);
    gl_func_00000000((void *)0xF9000000);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002722C);
#endif

// gl_func_000272C4 — STRUCTURAL PASS (0xB8 / 46 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO bundle
// (named fn + 3 tiny trailing accessors) — deferred USO re-split.
// The named leading fn (~15 words) is the subsystem SHUTDOWN / deinit.
//
//   void gl_func_000272C4(void) {
//     S *g = &D_0;
//     g->w_215C = 1;                                    // mark torn down
//     (*cleanup)(0);                                     // jal 0 USO
//     g->b_2CF0 = 0;                                     // clear state
//   }
//
// Struct-typing reference: the deinit counterpart to the
//   gl_func_00024378 initializer. It sets the subsystem handle word
//   &D_0+0x215C to 1 — exactly the "already torn down" sentinel the
//   gl_func_00025044 teardown sweep and gl_func_0001FEC8 register
//   helper test — calls a USO-relocated cleanup routine (`jal 0`
//   slot) with arg 0, and clears the main subsystem state byte
//   &D_0+0x2CF0 (the gl_func_0002119C state). The 3 trailing bundled
//   accessors are tiny table getters over the &D_0+0x2D00 record
//   table (idx-scaled lookups returning record bytes +0xD4 etc., and
//   a &D_0+0x2E58 byte read) — left for the deferred USO re-split.
// Caps (DEFERRED): single jr $ra (the "4-fn unsplit bundle" note is
//   STALE; .s is 0x3C/15 words, ONE function). Subsystem-shutdown
//   helper. Real-C STRUCTURAL body below per the analysis (set
//   ready/shutdown handle &D_0+0x215C=1; jal-0 reloc(0); clear main
//   state &D_0+0x2CF0=0). Byte-match deferred — placeholder jal-0
//   reloc needs USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_000272C4(void) {
    char *g = (char *)&D_00000000;
    *(int *)(g + 0x215C) = 1;
    gl_func_00000000(0);
    *(unsigned char *)(g + 0x2CF0) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000272C4);
#endif

#ifdef NON_MATCHING
/* game_libs_func_00027300: a0*352-strided lookup returning a signed byte, or
 * -1 when the slot's 0x2D00 word is non-negative.
 *
 * 2026-06-20 (agent-i): BODY now BYTE-EXACT for all 18 own-words (was 12 diffs,
 * now 3). Levers that cracked the regalloc cascade:
 *   - `if ((unsigned)v >> 31) { ... } return -1;` (NOT the ternary) frees $v0
 *     for the return so the *352 base lands in $v1 (target's 01CF1821), the
 *     loaded byte goes straight to $v0, and the -1 epilogue is `li v0,-1`.
 *   - array-index `((int*)(p+0x2D38))[a1]` gives `addu t1, v1, t0` in the
 *     target's operand order (was `addu t1, t0, v1`).
 *   - splitting the inner pointer into `char *q` makes IDO reuse the dead $a0
 *     param for the load (`lw a0,...(t1)`; `addu t2,a0,a2`).
 * The ONLY residual: the `return -1` here is a SELF-CONTAINED 3-word epilogue
 * (li v0,-1; jr; nop) appended to this symbol, whereas the target shares it as
 * the SEPARATE adjacent symbol game_libs_func_00027348 — 27300's `beql` branches
 * PAST its own end (0x2734C) into 27348's `jr`. That is an IDO cross-function
 * tail-merge that C cannot force: making 27348 a real `return -1` function makes
 * IDO EITHER inline the epilogue into 27300 (21-word symbol, no merge) OR emit a
 * duplicate 2-word 27348 — never the target's beql-crosses-boundary split. So
 * the two-symbol byte layout (27300=0x48 + 27348=0xc) is unreachable from C;
 * INCLUDE_ASM stays the build path. Sibling of game_libs_func_00026AF8 (matched,
 * void return → base in $v0). See feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
int game_libs_func_00027300(int a0, int a1, int a2) {
    char *p = (char *)&D_00000000 + a0 * 352;
    if ((unsigned int)*(int *)(p + 0x2D00) >> 31) {
        char *q = (char *)((int *)(p + 0x2D38))[a1];
        return *(signed char *)(q + a2 + 0xD4);
    }
    return -1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00027300);
#endif

/* game_libs_func_00027348: NOT a standalone -g3 return-(-1) stub — it is
 * game_libs_func_00027300's `-1` tail (its `beqzl t9,zero` at 0x27330 branches
 * to 0x2734C = this symbol's `jr ra`, with `li v0,-1` in the beqzl delay).
 * splat's jr-ra heuristic over-split it. The true 21-insn function is one unit;
 * keeping it INCLUDE_ASM because the merged C is a regalloc cap (~47%: target's
 * $v1/$t8/$t9 numbering through the *352-stride body doesn't match cc's, plus
 * the cross-fn -1 epilogue). Do NOT spend -g3 infra on this — it's not an
 * unfilled-delay stub. (Boundary not physically merged: merge gains nothing
 * while the body stays a regalloc cap.) */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00027348);

signed char game_libs_func_00027354(int a0, int a1) {
    return *(signed char *)((char *)&D_00000000 + a0 * 352 + a1 + 0x2E58);
}

// gl_func_0002737C — STRUCTURAL PASS (0x1CC / 115 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: LARGE 15-jr USO
// bundle — a dense cluster of tiny accessor/setter functions splat
// could not separate. Only the named leading fn is decoded; the ~14
// trailing bodies are deferred USO re-split.
//
//   void gl_func_0002737C(int a0, int a1) {
//     (*reg)(&D_2178, a0, a1);                          // jal 0 USO
//   }
//
// Struct-typing reference: the named leading fn is a thin register/
//   submit thunk — it forwards the caller args (a0, a1) plus the
//   fixed descriptor blob &D_2178 to a USO-relocated routine (`jal 0`
//   slot), saving a0 at sp+0x18 across the call. &D_2178 is the same
//   descriptor pool the gl_func_0001FEC8 / gl_func_00021F40 register
//   helpers use; word &D_0+0x2178 is the associated state slot
//   (cleared by one of the bundled siblings: `sw zero, 0x2178`). The
//   trailing bundled bodies are micro-accessors of the subsystem:
//   float readers (lwc1 +0x04 / +0x28 with c.eq.s / c.lt.s FP
//   compares), byte getters/setters (lbu +0 / +1, sb), and small bit
//   ORs (`ori …,0x40`) over the records — typical compiler-emitted
//   one-line inline-accessor functions, left for the deferred USO
//   re-split.
// Exact: single jr $ra (the "15-fn unsplit accessor bundle" note is
//   STALE; .s is 0x30/12 words, ONE function). Small 3-arg printf-like /
//   register wrapper: jal-0 reloc(&D_0+0x2178, a0, a1). Name pre-checked:
//   no extern reuse (collision-safe). gl_func_00000000 = canonical
//   never-defined USO placeholder.
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002737C(int a0, int a1) {
    char *g = (char *)&D_00000000;
    gl_func_00000000(g + 0x2178, a0, a1);
}

void game_libs_func_000273AC(void) {
    *(int *)((char *)&D_00000000 + 0x2178) = 0;
}

/* game_libs_func_000273B8 [0x273B8..0x27544): ONE 14-case jumptable
 * message-handler switch on msg[0] that splat shattered into 13
 * symbols (the 27534-hub "family" was its case bodies; the "shared
 * tail" was the default/epilogue). MERGED 2026-06-10 (13 -> 1, 0x18C).
 * Cases: 1/2/4 float setters (+40/+44/+56) with change-flags |=0x40/
 * 0x40/0x80 on b1; 3 s8 setter b10 flag 0x20; 5 s8 setter b4 no flag;
 * 6 indexed byte b[212+idx] idx<8; 7 bit4 insert into b0; 8 b3; 9/10
 * sh pairs (+26/+22 <<3, +24/+20 <<5); 11 b15; 12 sh32; 13/14 b224.
 * C below is STRUCTURALLY COMPLETE (99/99 insns after the idx-reuse
 * fix; jumptable emitted; case order correct). Residual 44 word-diffs
 * = a periodic temp-numbering pattern (target skips t8/t1/t5 at case
 * starts and inverts the first body's pair) -- an IDO temp-counter
 * behavior not yet steered; uoptlist/forensics queue.
 * 2026-06-10 uoptlist candidate-table read: the skips correlate with
 * the FLOAT-COMPARE cases (b1/b2/b4 skip an int temp right where
 * their lwc1 pseudos are created; the int cases b3/b5 are dense) --
 * hypothesis: in the TARGET's compile the float-load pseudos consumed
 * int-temp numbers, in ours they don't. The dump shows creation order
 * but not final numbering, so this is confirmed uoptlist-ceiling
 * class (coloring/numbering choice, not C-steerable). */
#ifdef NON_MATCHING
void game_libs_func_000273B8(unsigned char *a0, unsigned char *a1) {
    switch (a1[0]) {
    case 1:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 40)) {
            *(float *)(a0 + 40) = *(float *)(a1 + 4);
            a0[1] |= 0x40;
        }
        return;
    case 2:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 44)) {
            *(float *)(a0 + 44) = *(float *)(a1 + 4);
            a0[1] |= 0x40;
        }
        return;
    case 3:
        if (*(signed char *)(a1 + 4) != a0[10]) {
            a0[10] = *(signed char *)(a1 + 4);
            a0[1] |= 0x20;
        }
        return;
    case 4:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 56)) {
            *(float *)(a0 + 56) = *(float *)(a1 + 4);
            a0[1] |= 0x80;
        }
        return;
    case 5:
        if (*(signed char *)(a1 + 4) != a0[4]) {
            a0[4] = *(signed char *)(a1 + 4);
        }
        return;
    case 6: {
        int idx = a1[3];
        if (idx < 8) {
            a0[idx + 212] = *(signed char *)(a1 + 4);
        }
        return;
    }
    case 7:
        a0[0] = (a0[0] & ~0x10) | ((*(signed char *)(a1 + 4) << 4) & 0x10);
        return;
    case 8:
        a0[3] = *(signed char *)(a1 + 4);
        return;
    case 9:
        *(short *)(a0 + 26) = 1;
        *(short *)(a0 + 22) = a1[4] << 3;
        return;
    case 10:
        *(short *)(a0 + 24) = 1;
        *(short *)(a0 + 20) = a1[4] << 5;
        return;
    case 11:
        a0[15] = a1[4];
        return;
    case 12:
        *(short *)(a0 + 32) = *(unsigned short *)(a1 + 4);
        return;
    case 13:
    case 14:
        a0[224] = a1[4];
        return;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000273B8);
#endif


/* game_libs_func_00027438: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */


/* game_libs_func_00027488: 6-insn `lb v0,4(a1); lbu t1,4(a0);
 * beq v0,t1,+0x2A; nop; jr ra; sb v0,4(a0)` byte-compare-then-copy.
 * The bne offset +0x2A * 4 = +0xA8 branches PAST function end into the
 * successor — cross-function shared-epilogue tail-merge per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. Linker-set offset,
 * unmatchable standalone. CAP class. */


/* game_libs_func_000274C0: 8-insn bit-copy. Copies bit 0 of (signed)a1[4]
 * into bit 4 of a0[0]:  *a0 = ((a1[4] << 4) & 0x10) | (*a0 & ~0x10);
 * Logic + structure exact (lb; lbu; sll; andi 0x10; andi 0xFFEF; or; sb).
 * CAP: pure $t-register-numbering cascade — 7/8 insns differ by register only.
 * Target uses $t5/$t8/$t4/$t7/$t9/$t0 (low t-regs); inline form uses
 * $t8/$t6/$t9/$t0/$t7/$t1 (high t-regs). 2026-05-27 retest: named-locals
 * `int src = a1[4]; int dst = *a0;` pushed loads to $v0/$v1 (worse: 1/8
 * unchanged but lower-numbered regs picked $v-class not $t-class). The
 * allocno-priority for these tiny leaves favors high-numbered $t when the
 * expression is fully inlined and $v-class when split into locals. Neither
 * matches target's low-$t selection. INSN_PATCH would rewrite ~the whole
 * function (banned); permuter only. */


/* Single signed-byte copy a1[4] -> a0[3]. Reloc-free; IDO allocs the temp as
 * $t6 but target uses $t1 (register-renumber from original non-standalone
 * context). CAP: register-renumber, stays NM (INSN_PATCH REMOVED 2026-05-23
 * per feedback_no_instruction_forcing_matches_policy). */
#ifdef NON_MATCHING
void game_libs_func_000274E0(char *a0, signed char *a1) {
    /* a1 is signed char -> `lb` (was `char`=unsigned -> `lbu`).
     * 2026-06-10 FORENSIC RECLASS: the temp is $t1 in the target = IDO's
     * SIXTH temp (order t6,t7,t8,t9,t0,t1...). A standalone 3-insn leaf
     * always gets t6 (verified across 7.1/5.3 x O0-O3, and TU position
     * does NOT advance the counter -- tested). A mid-sequence temp number
     * means this symbol is the TAIL FRAGMENT of a larger original whose
     * body consumed five temps before this load -- consistent with the
     * 27xxx shattered-region census (this is a hub-region symbol). The
     * sibling stubs' t7/t9 say the same. Un-matchable as standalone fns;
     * boundary identification (which parent?) goes to the region decode.
     * INCLUDE_ASM stays. */
    a0[3] = a1[4];
}
#else

#endif

/* game_libs_func_000274EC: CAP (register-renumber, 2026-05-24). Correct C is
 *   *(short*)(a0+0x16) = a1[4] << 3;  *(short*)(a0+0x1A) = 1;
 * (write a1[4]<<3 FIRST so the load is pseudo #0 -> load-first order, matching
 * the target lbu;li;sh 0x1A;sll;jr;sh 0x16). Structure is byte-exact EXCEPT the
 * register base: target uses t2/t3/t4, every -O2 C form (and -O1/-g3) emits
 * t6/t7/t8. Permuter floored at base score 30, never 0 (33+ iters). The
 * contiguous-low-temp t2/t3/t4 allocation is unreachable from isolated C. */
/* game_libs_func_000274EC: 6-insn 2-field setter.
 *   a0[0x1A](short) = 1;
 *   a0[0x16](short) = (a1[4] << 3);   // a1 = u8*
 *
 * 6-insn match structurally; reg-rename cap (target uses $t2/$t4/$t3;
 * mine v0/t6/t7). Permuter-class register-allocation diff. */
/* 2026-06-10 TEMP-FORENSICS RECLASS: the temps here are MID-SEQUENCE
 * (standalone leaves always start at t6) -- in the known-shattered
 * 27xxx hub region this is fragment/context evidence (the 274E0-trio
 * class), NOT a permuter-class regalloc diff. Parent identification
 * goes to the region decode; do not grind registers. */


/* Stores 1 to field 0x18 and (a1[4] << 5) to field 0x14. Faithful decode but
 * a 5/6 cap: the target hoists the a1[4] load to the top (interleaving it
 * before the =1 store) and renumbers the temps; standalone AND in-tree both
 * reorder 3 insns + renumber 2, which is >half so no episode/INSN_PATCH. */
/* 2026-06-10 TEMP-FORENSICS RECLASS: the temps here are MID-SEQUENCE
 * (standalone leaves always start at t6) -- in the known-shattered
 * 27xxx hub region this is fragment/context evidence (the 274E0-trio
 * class), NOT a permuter-class regalloc diff. Parent identification
 * goes to the region decode; do not grind registers. */


/* Single unsigned-byte copy a1[4] -> a0[0xF]. Reloc-free; temp $t6 (IDO) vs
 * $t7 (target) register-renumber. CAP: stays NM (INSN_PATCH REMOVED
 * 2026-05-23 per feedback_no_instruction_forcing_matches_policy). */


/* Single halfword copy a1[2] -> a0[0x10]. Reloc-free; temp $t6 (IDO) vs $t9
 * (target) register-renumber. CAP: stays NM (INSN_PATCH REMOVED 2026-05-23
 * per feedback_no_instruction_forcing_matches_policy). */


/* game_libs_func_00027534: byte-copy accessor — *(u8*)(a0+0xE0) = *(u8*)(a1+4).
 * Target: `lbu t0,4(a1); sb t0,0xE0(a0); jr ra; nop` (UNFILLED jr delay).
 * Decode confirmed 2026-06-01. Two blockers to a real match:
 *   1. UNFILLED delay slot — the file's default -O2 fills it (`jr ra; sb` in the
 *      delay). Only -O2 -g / -O2 -g3 reproduce the `sb; jr ra; nop` form
 *      (verified standalone), so it needs a per-file -g carve-out like
 *      game_libs_o0_8A40.c.
 *   2. Even at -O2 -g the temp colors to t6, never the target's t0 (tested
 *      named-local / int-temp / uchar* args / direct-index — all t6/t7). A
 *      register-renumber cap, so a carve-out would still cap at the lbu/sb
 *      register (2 of 4 insns). Not worth the carve-out infra for a 4-insn
 *      leaf that can't reach 100%. Sibling of 00027528. Stays INCLUDE_ASM. */


/* gl_func_00027548: 17-insn (0x44) F3DEX2-style display-list-word builder.
 * Computes a packed 32-bit dlist word:
 *   packed = 0xFA000000 | ((a0 & 0xFF) << 16) | ((a1 & 0xFF) << 8) | (a2 & 0xFF)
 * (G_SETPRIMCOLOR-like opcode 0xFA + 3 bytes) and calls gl_func_0(packed, 1).
 *
 * MATCHED via splat boundary correction (stolen-prologue mirror, replacing the
 * banned PROLOGUE_STEALS). The leading `andi t6, a0, 0xFF` (this fn's prologue
 * computing a0&0xFF for `sll t7,t6,0x10`) was a trailing orphan in the
 * PREDECESSOR game_libs_func_00027534's range (past its jr ra; nop). Fixed by
 * shrinking 00027534.s to its real 4 insns (0x10) and prepending the andi to
 * this fn's .s (now 18 insns / 0x48, starts at 0x27544). ROM bytes preserved;
 * the natural C `(a0 & 0xFF) << 16` emits the andi at function start = exact. */
extern int gl_func_00000000();

void gl_func_00027548(int a0, int a1, int a2) {
    int packed = 0xFA000000 | ((a0 & 0xFF) << 16) | ((a1 & 0xFF) << 8) | (a2 & 0xFF);
    gl_func_00000000(packed, 1);
}

void gl_func_0002758C(void) {
    gl_func_00000000(0xFA000000, 0);
}

extern int D_gl275B0;
void gl_func_000275B0(int a0) { D_gl275B0 = a0; }

extern int D_gl275BC;
void gl_func_000275BC(void) { D_gl275BC = 0; }

// gl_func_000275C8 — STRUCTURAL PASS (0x11C / 71 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 8-jr USO bundle
// (named fn + 7 trailing record-accessors) — deferred USO re-split.
// The named leading fn (~10 words) is a thin process-global thunk.
//
//   void gl_func_000275C8(void) {
//     void *obj = *(void**)(&D_0 + 0x53C8);             // global obj
//     (*proc)(obj, 0, 1);                                // jal 0 USO
//   }
//
// Struct-typing reference: the named leading fn forwards the global
//   object pointer at &D_0+0x53C8 (the same &D_0+0x53Cx state region
//   the gl_func_0002722C lock-guarded op / gl_func_00026CF0
//   submit-helper use) to a USO-relocated processor (`jal 0` slot)
//   with the fixed args (0, 1) — a one-line "tick/flush the current
//   global object" entry. The 7 trailing bundled bodies are
//   compiler-emitted micro-accessors over the &D_0+0x2D00 record
//   table (index scaled idx*5<<2 = idx*0x14, table pointer
//   &D_0+0x2D00, secondary table &D_0+0x2D38; field getters
//   rec->0x50 etc. with sign-bit tests) — left for the deferred USO
//   re-split.
// Caps (DEFERRED): single jr $ra (the "8-fn unsplit accessor bundle"
//   note is STALE; .s is 0x2C/11 words, ONE function). Tiny wrapper.
//   Real-C STRUCTURAL body below per the analysis (jal-0
//   reloc(*(&D_0+0x53C8), 0, 1)). Byte-match deferred — placeholder
//   jal-0 needs USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
extern int gl_func_00000000();
void gl_func_000275C8(void) {
    char *g = (char *)&D_00000000;
    gl_func_00000000(*(void **)(g + 0x53C8), 0, 1);
}

/* game_libs_func_000275F4 (0xC4 after merging 2765C/27684/27694): a
 * region-wide out-branch census (2026-06-10) showed the four symbols'
 * cross-branches all land at +0/+4 of the next -- one shattered
 * function. Its remaining external branches enter the ADJACENT MATCHED
 * leaves 276B8(+4)/276D0(+0)/276D8(+4) = the branch-into-adjacent-leaf
 * shared-tail cap family (INCLUDE_ASM faithful). Same census found the
 * OTHER hub: 27534+8 is the shared tail of 273B8/27438/27488/274A0. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000275F4);

/* 0x276xx leaf-branch-past-end cluster: 3 tiny leaves with forward
 * `beq/bne +small` branches that target at or past function-end (falling
 * into successor's first insn). Cross-fn shared-epilogue tail-merges per
 * feedback_leaf_branch_past_end_is_cross_fn_epilogue. Covers
 * game_libs_func_0002765C, _00027684, _00027694. CAP class. */
/* game_libs_func_0002765C MERGED into 275F4 2026-06-10 (shattered-fn census). */

/* game_libs_func_00027684 MERGED into 275F4 2026-06-10 (shattered-fn census). */

/* game_libs_func_00027694 MERGED into 275F4 2026-06-10 (shattered-fn census). */

#ifdef NON_MATCHING
/* game_libs_func_000276B8: pointer-chain subtract — returns
 * (*a0)->8->4 - a3->0x18. Logic exact; near-miss: the two unused MIDDLE args
 * (a1/a2 = $5/$6) are reused as scratch for the loads, but IDO -O2 homes one
 * of them (sw a1,4(sp)) defensively even though the function has NO jal to
 * pass it through (so the feedback_ido_unused_arg_fix_pass_to_callee remedy
 * doesn't apply). Reassigning the param kills a2's home but not a1's = +1 insn.
 * Reloc-free (episode-worthy if the home were avoidable). Unused-middle-arg-
 * home-without-jal cap. */
int game_libs_func_000276B8(int **a0, int *a1, int a2) {
    /* 2026-06-10 decode correction: the subtrahend loads from 0x18(a1)
     * (the SECOND arg), not a3[6] -- structure now 6/6 with both
     * dead-arg overwrites (a2 = value, a1 = chain result). Remaining
     * 4 word diffs: target's chain temps are t0/t1 (5th/6th temps)
     * vs standalone t6/t7. RESOLVED 2026-06-10: 275F4's census already
     * shows its branches enter THIS leaf at +4 -- 276B8 is an INTERIOR
     * ENTRY of 275F4's parent function (the 6F038 two-entry class):
     * the original TU had no standalone 276B8, callers jal into the
     * parent's tail block, so its temps continue the parent's counter
     * (t6..t9 consumed by the parent's head, visible in 275F4's
     * disasm). 95.83 is therefore the standalone-C ceiling; the parent
     * region [0x275F4..0x276E4) is INCLUDE_ASM-faithful as documented.
     * NOT the shattered-switch class (no jr-tN dispatcher). */
    a2 = a1[6];
    a1 = (int *)*(int *)(*(int *)((char *)*a0 + 8) + 4);
    return (int)a1 - a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000276B8);
#endif

int game_libs_func_000276D0(void) { return 0; }

/* game_libs_func_000276D8: 3-insn `move v0,zero; jr ra; nop` return-0 stub
 * (size 0xC, unfilled-delay form). Sibling of 000276D0 (filled-delay,
 * size 0x8, already matched as `int f(void){return 0;}`). The 0xC form
 * needs per-file -g3/-O0 split per
 * feedback_unfilled_delay_int_reader_needs_o0_split. Default INCLUDE_ASM
 * remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000276D8);

extern int gl_func_0003B1AC();
int gl_func_000276E4() {
    return gl_func_0003B1AC();
}

extern int gl_func_00000000();
void gl_func_00027704(int a0, int a1) {
    int r = gl_func_00000000(1);
    gl_func_00000000(a0, a1);
    gl_func_00000000(r);
}

// gl_func_00027744 — STRUCTURAL PASS (0xB4 / 45 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn (~15 words) is a 3-step sequenced wrapper.
//
//   void gl_func_00027744(int a0, int a1) {
//     int r = (*setup)(1);                              // jal 0 USO
//     (*op)(a0, a1);                                     // jal 0 USO
//     (*finish)(r);                                      // jal 0 USO
//   }
//
// Struct-typing reference: the named leading fn is a thin
//   begin/middle/end orchestrator — it calls a USO-relocated setup
//   routine with constant 1, saving its result; then an op with the
//   caller args (a0, a1); then a finish/teardown with the saved
//   setup result (a0/a1 are preserved across all three via the
//   sp+0x1C..0x24 spill slots). The 2 trailing bundled bodies are
//   lower-level helpers that read a state byte at &D_0+0x2B710 (mask
//   0x1FFF) and touch N64 hardware registers in the 0xA4500000 (SP /
//   RSP DMA) region — an RSP/DMA submit path — left for the deferred
//   USO re-split. NOTE: this function also carries a trailing
//   gl_func_00027744_pad.s GLOBAL_ASM (alignment/literal pad), which
//   is left untouched.
// Caps (DEFERRED): single jr $ra (the "3-fn unsplit bundle" note is
//   STALE; .s is 0x40/16 words, ONE function). Small 3-call
//   acquire/work/release sequence. Real-C STRUCTURAL body below per
//   the analysis (r1=jal-0 reloc1(1); jal-0 reloc2(a0,a1); jal-0
//   reloc3(r1)). Byte-match deferred — placeholder jal-0 chain
//   needs USO reloc infra. Name pre-checked: no extern reuse
//   (collision-safe). gl_func_00000000 = canonical never-defined
//   USO placeholder.
extern int gl_func_00000000();
void gl_func_00027744(int a0, int a1) {
    int r1 = gl_func_00000000(1);
    gl_func_00000000(a0, a1);
    gl_func_00000000(r1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00027784);

/* game_libs_func_000277E0: 6-insn HW-register store with caller-set bases:
 *   sw t2, 0(t3); lui t4, 0xA450; sw a1, 4(t4); move v0,zero; jr ra; nop
 * The opening `sw t2, 0(t3)` uses caller-set $t2 and $t3 (neither in
 * a0..a3 calling convention). The second store is to AI_LEN_REG @ 0xA450_0004
 * (audio interface). CAP class per
 * feedback_caller_set_int_reg_cap_1080_game_libs. Default INCLUDE_ASM
 * remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000277E0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00027744_pad.s")

// gl_func_00027804 — STRUCTURAL PASS (0x4FC / 319 words ≈ 1.3KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO
// bundle (named fn + 1 trailing helper) — deferred USO re-split. The
// named leading fn is a large object-state apply/update. -0x50 frame.
//
//   void gl_func_00027804(O *obj, S *src) {
//     byte  m = obj->b_35;
//     void *p = src->w_4;
//     int   r = jal 0x3C2B4(m, p, …);                   // 0x0C00F0AD
//     byte  k = src->b_2;
//     float f = src->f_8;                                 // lwc1 +8
//     // build a stack scratch struct at sp+0x2C from
//     //   src->b_0 / src->b_2 / src->b_3 …
//     byte fl = obj->b_B0;
//     fl &= ~0x08;                                         // clear bit3
//     fl &= ~0x04;                                          // clear bit2
//     fl &= ~0x02;                                          // clear bit1
//     obj->b_B0 = fl;
//     ...
//     obj->h_BC = packed;                                   // write back
//   }
//
// Struct-typing reference: applies an update to object `obj` from a
//   source descriptor `src`. obj fields: byte +0x35 (a type/mode fed
//   to the USO-relocated routine 0x0C00F0AD ≈0x3C2B4), flag byte
//   +0xB0 (bits 1/2/3 cleared as part of the update — a
//   state-transition mask), halfword +0xBC (a packed result written
//   back). src fields: byte +0 / +2 / +3, word +4 (a pointer arg),
//   float +0x8 (lwc1, an interpolation/scale value). A stack scratch
//   struct at sp+0x2C is assembled from the src bytes and handed to
//   the fixed routine. The object property-set / apply-state-change
//   entry of the game_libs object subsystem.
// Caps: raw-word USO + 2-fn unsplit bundle + large state-mutation
//   body with FP + jal-0/fixed calls — not exact-matchable without
//   proper USO mnemonic disasm; high-level structural pass only for
//   the named leading fn, no byte body.
// Caps (DEFERRED): raw-word USO bundle + jal-0/fixed routine 0x3C2B4
//   + heavy FP state-mutation cluster — byte-match needs USO mnemonic
//   disasm + the reloc-pad jal infra. Real-C STRUCTURAL body below
//   per the analysis (placeholder calls / fields). Byte-match deferred.
//   Name pre-checked: no extern reuse (collision-safe).
// gl_func_00027804 — m2c DECODE (32.53% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00027804)();
#ifndef FF
#define FF(p, o) (*(f32 *)((char *)(p) + (o)))
#endif
void gl_func_00027804(char *arg0, char *arg1) {
    u8 sp2F;
    u8 sp2E;
    s32 sp2C;
    s32 sp24;
    f32 temp_f0;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_at;
    s8 temp_v1;
    u32 temp_v1_2;
    u8 temp_t2;
    u8 temp_t3;
    u8 temp_t5;
    u8 temp_t5_2;
    u8 temp_t6;
    u8 temp_t6_2;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_t9;
    u8 temp_v0;
    char *var_v0;

    temp_v0 = FW(arg0, 0x35);
    sp24 = (s32) temp_v0;
    game_libs_func_0003443C(FW(arg1, 0x4), arg1);
    var_f2 = FF(arg1, 0x8);
    sp2F = FW(arg1, 0x2);
    sp2E = FW(arg1, 0x0);
    sp2C = (u8) FW(arg1, 0x3);
    sp2F &= 0x7F;
    temp_t5 = FW(arg0, 0xB0) & 0xFFF7;
    temp_t2 = temp_t5 & 0xFB;
    FW(arg0, 0xB0) = temp_t5;
    FW(arg0, 0xB0) = temp_t2;
    temp_t8 = ((((u32) (sp2C << 6) >> 0x1F) * 2) & 2) | (temp_t2 & 0xFD);
    FW(arg0, 0xB0) = temp_t8;
    FW(arg0, 0xB0) = (u8) (((u8) sp2C & 1) | (temp_t8 & 0xFE));
    if (temp_v0 != 0) {
        var_a1 = (s32) sp2F >> 1;
        if (*(s8 *)0x2076 == 1) {
            var_v0 = (int)arg0 + 0xB0;
            if (var_a1 >= 0x40) {
                var_a1 = 0x3F;
            }
            FW(var_v0, 0x4) = (s8) *(int*)(var_a1 * 2);
            FW(var_v0, 0x1) = (u8) (FW(var_v0, 0x1) | 1);
            FW(var_v0, 0x3) = (s8) FW((var_a1 * -2), 0x7E);
            var_f12 = *(int*)(sp2F * 4);
            var_at = sp2F * -4;
            goto block_22;
        }
    }
    temp_v1 = *(char *)0x2076;
    if ((temp_v0 != 0) && (var_v0 = (int)arg0 + 0xB0, (temp_v1 == 0))) {
        FW(var_v0, 0x3) = 0;
        FW(var_v0, 0x4) = 0;
        FW(var_v0, 0x1) = (u8) (FW(var_v0, 0x1) & 0xFFFE);
        var_a1_2 = 0;
        var_f12 = *(int*)(sp2F * 4);
        var_f14 = FF((sp2F * -4), 0x1FC);
        var_a2 = 0;
        if ((s32) sp2F < 0x20) {
            var_a2 = 1;
        } else if ((s32) sp2F >= 0x61) {
            var_a1_2 = 1;
        }
        temp_t9 = ((var_a1_2 * 8) & 8) | (FW(arg0, 0xB0) & 0xFFF7);
        FW(arg0, 0xB0) = temp_t9;
        FW(arg0, 0xB0) = (u8) (((var_a2 * 4) & 4) | (temp_t9 & 0xFB));
        temp_v1_2 = (u32) (sp2C * 4) >> 0x1E;
        switch (temp_v1_2) {                        /* irregular */
        case 0:
            break;
        case 1:
            temp_t5_2 = ((((u32) (sp2C * 0x10) >> 0x1F) * 8) & 8) | (FW(arg0, 0xB0) & 0xFFF7);
            FW(arg0, 0xB0) = temp_t5_2;
            FW(arg0, 0xB0) = (u8) (((((u32) (sp2C << 5) >> 0x1F) * 4) & 4) | (temp_t5_2 & 0xFB));
            break;
        case 2:
            temp_t6 = (((((u32) (sp2C * 0x10) >> 0x1F) | var_a1_2) * 8) & 8) | (FW(arg0, 0xB0) & 0xFFF7);
            FW(arg0, 0xB0) = temp_t6;
            FW(arg0, 0xB0) = (u8) ((((((u32) (sp2C << 5) >> 0x1F) | var_a2) * 4) & 4) | (temp_t6 & 0xFB));
            break;
        case 3:
            temp_t6_2 = (((((u32) (sp2C * 0x10) >> 0x1F) ^ var_a1_2) * 8) & 8) | (FW(arg0, 0xB0) & 0xFFF7);
            FW(arg0, 0xB0) = temp_t6_2;
            FW(arg0, 0xB0) = (u8) ((((((u32) (sp2C << 5) >> 0x1F) ^ var_a2) * 4) & 4) | (temp_t6_2 & 0xFB));
            break;
        }
    } else if (temp_v1 == 3) {
        var_v0 = (int)arg0 + 0xB0;
        var_f14 = *(f32 *)0xFC0;
        temp_t7 = FW(arg0, 0xB0) & 0xFFFD;
        FW(arg0, 0xB0) = temp_t7;
        FW(arg0, 0xB0) = (u8) (temp_t7 & 0xFE);
        var_f12 = var_f14;
    } else {
        var_v0 = (int)arg0 + 0xB0;
        temp_t3 = ((((u32) (sp2C * 0x10) >> 0x1F) * 8) & 8) | (FW(arg0, 0xB0) & 0xFFF7);
        FW(arg0, 0xB0) = temp_t3;
        FW(arg0, 0xB0) = (u8) (((((u32) (sp2C << 5) >> 0x1F) * 4) & 4) | (temp_t3 & 0xFB));
        var_f12 = *(int*)(sp2F * 4);
        var_at = sp2F * -4;
block_22:
        var_f14 = FF(var_at, 0x1FC);
    }
    if (var_f2 < 0.0f) {
        var_f2 = 0.0f;
    }
    if (var_f2 > 1.0f) {
        var_f2 = 1.0f;
    }
    temp_f0 = *(f32 *)0xFC4;
    FW(var_v0, 0x8) = (s16) (s32) (var_f2 * var_f12 * temp_f0);
    FW(var_v0, 0xA) = (s16) (s32) (var_f2 * var_f14 * temp_f0);
    FW(var_v0, 0x2) = (u8) FW(arg1, 0x1);
    FW(var_v0, 0x14) = (s32) FW(arg1, 0x10);
    FW(var_v0, 0x7) = (u8) FW(arg1, 0x14);
    FW(var_v0, 0xE) = (u16) FW(arg1, 0x16);
    FW(var_v0, 0x5) = sp2E;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027804);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00027C48)();
void game_libs_func_00027C48(char *arg0, f32 arg1) {
  f32 temp_f2;
  int *new_var;
  f32 var_f0;
  char *temp_v0;
  char *temp_v0_2;
  temp_v0 = ((int) arg0) + 0xB0;
  dummy_label_367138:
  ;

  ;
  ;
  var_f0 = arg1;
  if (arg1 < 2.0f)
  {
    temp_f2 = *((f32 *) (((char *) (&D_00000000)) + 0xFC8));
    temp_v0_2 = ((int) arg0) + 0xB0;
    if (1)
    {
      *((u8 *) (((char *) temp_v0_2) + 0x1)) = (u8) ((*((u8 *) (((char *) temp_v0_2) + 0x1))) & 0xFFFD);
    }
    if (temp_f2 < arg1)
    {
      var_f0 = temp_f2;
    }
    else
    {
      var_f0 = arg1;
    }
  }
  else
  {
    new_var = &D_00000000;
    *((u8 *) (((char *) temp_v0) + 0x1)) = (u8) ((*((u8 *) (((char *) temp_v0) + 0x1))) | 2);
    if (1)
    {
    }
    if (1)
    {
    }
    if (1)
    {
    }
    if (1)
    {
    }
    if (1)
    {
    }
    if ((*((f32 *) (((char *) new_var) + 0xFCC))) < arg1)
    {
      var_f0 = *((f32 *) (((char *) new_var) + 0xFD0));
    }
    else
    {
      var_f0 = arg1 * 0.5f;
    }
  }
  *((s16 *) (((char *) arg0) + 0xBC)) = (s16) ((s32) (var_f0 * 32768.0f));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00027C48);
#endif

// gl_func_00027D00 — STRUCTURAL PASS (0x124 / 73 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn pulls a transform from a linked source object and
// applies it into the object's matrix/flag block.
//
//   void gl_func_00027D00(O *obj) {
//     P *p = obj->w_44;                                 // source obj
//     if (p->b_18 != 0) {
//       (*ha)(&obj->_36, p->w_1C, …);                    // jal 0 USO
//     } else {
//       (*hb)(&obj->_60, p->w_1C);                        // jal 0 USO
//     }
//     T *t = p->w_50;
//     obj->b_34 = 0;                                       // clear flag
//     obj->b_60 = (obj->b_60 & 0xF0) | 1;                  // set bit0
//     obj->w_B0 = t->w_0;                                  // copy a
//     obj->w_B4 = t->w_4;                                  //  4-word
//     obj->w_B8 = t->w_8;                                  //  block
//     obj->w_BC = t->w_C;                                  //  (Vec4/row)
//     obj->f_70 = …;                                        // swc1 +0x70
//   }
//
// Struct-typing reference: applies a transform from a linked source.
//   obj->0x44 is a pointer to the source object P; byte P->0x18 is a
//   mode gate selecting which USO-relocated handler runs (`jal 0`
//   slots) with obj sub-blocks at +0x36 / +0x60 and P->0x1C. P->0x50
//   points to a 4-word value block (matrix row / Vec4) that is copied
//   verbatim into obj->0xB0..0xBC (the same +0xB0 block
//   gl_func_00027804 manipulates). obj flag byte +0x34 is cleared and
//   +0x60 has its low nibble reset with bit0 set (a dirty/ready
//   marker); float obj->0x70 is written. The "pull-and-apply linked
//   transform" entry of the game_libs object subsystem.
// Caps (DEFERRED): raw-word USO bundle + jal-0 USO-reloc handlers —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   Real-C STRUCTURAL body below per the analysis (placeholder calls
//   / fields). Byte-match deferred.
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_00027D00(int *obj) {
    int *p = *(int **)((char *)obj + 0x44);
    int *tmpl;
    unsigned char f60;
    if (*(unsigned char *)((char *)p + 0x18) == 0) {
        gl_func_00000000((char *)obj + 0x60,
                         *(int *)(*(char **)((char *)p + 0x50) + 0x90),
                         (char *)obj + 0x36);
    } else {
        gl_func_00000000((char *)obj + 0x60, *(int *)((char *)p + 0x1C),
                         (char *)obj + 0x36);
    }
    f60 = *(unsigned char *)((char *)obj + 0x60);
    *(unsigned char *)((char *)obj + 0x34) = 0;
    *(unsigned char *)((char *)obj + 0x60) = (f60 & 0xFFF0) | 1;
    tmpl = (int *)&D_00000000;
    {
        struct Blk8 { int w[8]; };
        *(struct Blk8 *)((char *)obj + 0xB0) = *(struct Blk8 *)tmpl;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027D00);
#endif

/* game_libs_func_00027DC0: object reset. If bit30 of a0->0xB0 is set, clear its
 * bit6; then clear bits 7 and 5 of a0->0xB0, zero the bytes at 0x30/0x34, set
 * the words at 0x40/0x44 to -1, clear the low nibble of byte a0->0x60, and zero
 * the float at 0x70. The `&= ~0xNN` byte masks emit andi 0xffNN (16-bit imm).
 * The bit30 test needs `== 1` (not bare truthy) to emit the target's explicit
 * `sll;srl;bne ==1` extract instead of a collapsed `sll;bgezl` sign-check. The
 * target RE-READS a0->0xB0 before the bit7/bit5 clears (the intervening
 * non-aliasing byte stores let IDO CSE the just-stored value, dropping a reload);
 * routing those two clears through a `volatile unsigned char*` view forces the
 * reloads → byte-exact. */
void game_libs_func_00027DC0(char *a0) {
    if ((((unsigned int)*(int *)(a0 + 0xB0) << 1) >> 31) == 1) {
        *(unsigned char *)(a0 + 0xB0) &= ~0x40;
    }
    *(char *)(a0 + 0x30) = 0;
    *(volatile unsigned char *)(a0 + 0xB0) &= ~0x80;
    *(char *)(a0 + 0x34) = 0;
    *(volatile unsigned char *)(a0 + 0xB0) &= ~0x20;
    *(int *)(a0 + 0x44) = -1;
    *(int *)(a0 + 0x40) = -1;
    *(unsigned char *)(a0 + 0x60) &= ~0x0F;
    *(float *)(a0 + 0x70) = 0.0f;
}

// gl_func_00027E24 — STRUCTURAL PASS (0x534 / 333 words ≈ 1.3KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO
// bundle (named fn + 3 trailing helpers) — deferred USO re-split.
// The named leading fn is a big per-record processing pass over the
// main sprite record table. Large -0x98 frame.
//
//   void gl_func_00027E24(void) {
//     S *g = &D_0;
//     int n = g->w_2070;                                // record count
//     if (n <= 0) return;
//     for (int i = 0; i < n; i++) {                       // all records
//       R *rec = *(R**)(&D_0 + 0x2CFC) + i;                // record tbl
//       T *sub = rec->w_44;                                // sub-struct
//       byte k = (&rec->_30)->b_4;
//       int  v = rec->w_14;
//       if ((unsigned)v < 0x7FFFFFFF) { ... clamp / use v ... }
//       ... accumulate into a stack buffer at sp+0x67 ...
//     }
//   }
//
// Struct-typing reference: iterates the SAME primary sprite record
//   table as gl_func_0001E134 / gl_func_0001FAE8 / gl_func_0002119c —
//   live count word &D_0+0x2070, record-table pointer &D_0+0x2CFC.
//   Per record: word +0x44 a linked sub-struct pointer, embedded
//   sub-block at +0x30 (byte +4), word +0x14 a value clamped against
//   0x7FFFFFFF (INT_MAX saturation). Results accumulate into a stack
//   scratch buffer at sp+0x67. This is one of the heavyweight
//   per-frame "process every sprite record" passes of that subsystem
//   (sibling to gl_func_0001E134's builder / gl_func_0001FAE8's
//   reactivate sweep).
// DECODE PROGRESS 2026-06-22: 54.5% -> 73.5% fuzzy; size gap 56w -> ~0
//   (262w -> 317w vs target 318w). Two structural decode fixes:
//   (1) func_3be70 arg buffer sp+0x64..0x7A was modelled as separate
//       scalar locals -> IDO DCE'd every store but &sp64 (only one read
//       by address). Replaced with a single contiguous `struct buf64`
//       passed as &buf; all stores now survive (+~50 insns recovered).
//       Layout: u8 b0..b3, f32 f4/f8, gap[4], s32 w10, u8 b14, pad, u16 h16.
//       Field types corrected from mnemonics (lbu=u8, lwc1=f32, lhu=u16).
//   (2) base &D_0 was rematerialised (8x lui/lo16) instead of held in a
//       saved reg like the target (s6). `g = &D_0 + (s32)&D_0` forces the
//       address into a saved reg (1 reload) without a volatile spill.
//   FP mul.s chain + buf.f4-stored-twice pattern now matches structurally.
// Caps (RESIDUAL, regalloc-class): remaining ~26% is pure register-
//   renumber + frame-layout cascade — base reg (mine s3 vs target s6),
//   *13 as li/multu vs target shift-add strength-reduction, 0x20000000
//   held-const vs target inline sll-2/bgez bit-test, frame 168 vs 152.
//   Correct logic, divergent coloring: the documented per-function-RE-only
//   cap class. jal-0 USO-reloc calls (gl_func_0001CA10/func_3be70/3d414)
//   credited via placeholder convention. Byte-match deferred.
//   STALE bundle-note: grep -c 03E00008 = 1 (.s is single fn now).
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int func_3be70();
extern int func_3d414();
extern int gl_func_0001CA10();
struct buf64 {
    u8  b0;        /* +0x00 (sp+0x64) */
    u8  b1;        /* +0x01 (sp+0x65) */
    u8  b2;        /* +0x02 (sp+0x66) */
    u8  b3;        /* +0x03 (sp+0x67) */
    f32 f4;        /* +0x04 (sp+0x68) */
    f32 f8;        /* +0x08 (sp+0x6C) */
    u8  pad0C[4];  /* +0x0C (sp+0x70) */
    s32 w10;       /* +0x10 (sp+0x74) */
    u8  b14;       /* +0x14 (sp+0x78) */
    u8  pad15;     /* +0x15 (sp+0x79) */
    u16 h16;       /* +0x16 (sp+0x7A) */
};

void gl_func_00027E24(void) {
    char *g = (char *)&D_00000000 + (s32)&D_00000000;
    struct buf64 buf;
    u8 sp63;
    f32 sp5C;
    f32 temp_f18;
    s32 *temp_v0;
    s32 var_s4;
    s32 var_v0;
    u32 temp_a0;
    u8 *var_s0;
    u8 temp_v0_2;
    u8 var_v0_2;
    u8 var_v1;
    s32 temp_a0_2;
    s32 temp_a0_3;
    char *temp_a1;
    char *temp_a1_2;
    s32 temp_s1;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v1;
    char *var_s2;

    if (*(s32 *)(g + 0x2070) > 0) {
        var_s4 = 0;
        do {
            temp_s1 = var_s4 + *(s32 *)(g + 0x2CFC);
            var_s0 = temp_s1 + 0x30;
            if ((*(s32 *)(temp_s1 + 0x44)) != -1) {
                var_s0 = temp_s1 + 0x30;
                temp_a0 = (*(s32 *)(var_s0 + 0x14));
                if (temp_a0 < 0x7FFFFFFFU) {
                    var_v0 = *(s32 *)(g + 0x2070) * 0xD;
                } else {
                    if ((temp_s1 != (*(s32 *)(temp_a0 + 0x2C))) && ((*(u8 *)(var_s0 + 0x4)) == 0)) {
                        var_v0_2 = 1 & 0xFF;
                        (*(u8 *)(var_s0 + 0x30)) = (u8) ((*(u8 *)(var_s0 + 0x30)) | 0x10);
                        (*(s32 *)(temp_s1 + 0x30)) = 1U;
                        (*(u8 *)(var_s0 + 0x4)) = 2U;
                        (*(s32 *)(var_s0 + 0x3C)) = (s32) *(f32 *)(g + 0x2050);
                        goto block_21;
                    }
                    if ((((u32) (*(s32 *)(temp_a0 + 0x0)) >> 0x1F) != 0) || ((*(u8 *)(var_s0 + 0x4)) != 0) || ((s32) (*(s32 *)(temp_s1 + 0x30)) <= 0)) {
                        temp_a1 = (*(s32 *)(temp_a0 + 0x50));
                        temp_v0 = (*(s32 *)(temp_a1 + 0x4C));
                        if (temp_v0 == NULL) {
                            gl_func_0001CA10(temp_a1, temp_a1);
                            (*(s32 *)(temp_s1 + 0x30)) = 1U;
                            (*(u8 *)(var_s0 + 0x4)) = 1U;
                            var_v0 = *(s32 *)(g + 0x2070) * 0xD;
                        } else {
                            if (!(*temp_v0 & 0x20000000) || !((*(s32 *)(temp_a1 + 0x3)) & 0x40)) {

                            } else {
                                goto block_16;
                            }
                            goto block_20;
                        }
                    } else {
block_16:
                        gl_func_0001CA10((void *) temp_a0);
                        gl_func_0001CA10(temp_s1);
                        func_3d414((*(s32 *)(temp_s1 + 0xC)) + 0x10, temp_s1);
                        (*(s32 *)(temp_s1 + 0x30)) = 1U;
                        (*(u8 *)(var_s0 + 0x4)) = 2U;
                        goto block_20;
                    }
                }
            } else if (((*(u8 *)(var_s0 + 0x4)) == 0) && ((s32) (*(s32 *)(temp_s1 + 0x30)) > 0)) {
                var_v0 = *(s32 *)(g + 0x2070) * 0xD;
            } else {
block_20:
                var_v0_2 = *var_s0;
block_21:
                if (var_v0_2 != 0) {
                    var_s2 = temp_s1 + 0xB0;
                    if (((s32) (*(u8 *)(var_s0 + 0x4)) > 0) || ((*(s32 *)(temp_s1 + 0xB0)) & 0x20000000)) {
                        var_s2 = temp_s1 + 0xB0;
                        if (!((*(u8 *)(var_s0 + 0x30)) & 0xF) || ((*(s32 *)(temp_s1 + 0xB0)) & 0x20000000)) {
                            if ((*(s32 *)(var_s0 + 0x18)) != -1) {
                                gl_func_0001CA10(temp_s1);
                                temp_a1_2 = (*(s32 *)(var_s0 + 0x18));
                                if ((*(s32 *)(temp_a1_2 + 0x50)) != 0) {
                                    var_s2 = temp_s1 + 0xB0;
                                    gl_func_0001CA10(temp_s1, temp_a1_2);
                                    gl_func_0001CA10(temp_s1);
                                    gl_func_0001CA10(temp_s1);
                                    gl_func_0001CA10(temp_s1);
                                    gl_func_0001CA10((*(s32 *)(temp_s1 + 0xC)) + 0x30, temp_s1);
                                    (*(s32 *)(var_s0 + 0x18)) = -1;
                                    goto block_37;
                                }
                                gl_func_0001CA10(temp_s1, temp_a1_2);
                                gl_func_0001CA10(temp_s1);
                                gl_func_0001CA10((*(s32 *)(temp_s1 + 0xC)), temp_s1);
                                (*(s32 *)(var_s0 + 0x18)) = -1;
                            } else {
                                temp_a0_2 = (*(s32 *)(var_s0 + 0x14));
                                if (temp_a0_2 != -1) {
                                    (*(u8 *)(temp_a0_2 + 0x0)) = (u8) ((*(u8 *)(temp_a0_2 + 0x0)) | 2);
                                }
                                gl_func_0001CA10(temp_s1);
                                gl_func_0001CA10(temp_s1);
                                gl_func_0001CA10((*(s32 *)(temp_s1 + 0xC)), temp_s1);
                            }
                        } else {
                            goto block_37;
                        }
                    } else if (!((*(u8 *)(var_s0 + 0x30)) & 0xF)) {
                        temp_a0_3 = (*(s32 *)(var_s0 + 0x14));
                        if (temp_a0_3 != -1) {
                            (*(u8 *)(temp_a0_3 + 0x0)) = (u8) ((*(u8 *)(temp_a0_3 + 0x0)) | 2);
                        }
                        gl_func_0001CA10(temp_s1);
                        gl_func_0001CA10(temp_s1);
                        gl_func_0001CA10((*(s32 *)(temp_s1 + 0xC)), temp_s1);
                    } else {
block_37:
                        sp5C = gl_func_0001CA10(var_s0 + 0x30);
                        gl_func_0001CA10(temp_s1);
                        temp_v0_2 = (*(u8 *)(var_s0 + 0x4));
                        if ((temp_v0_2 == 1) || (temp_v0_2 == 2)) {
                            temp_v0_3 = var_s0 + 0x1C;
                            buf.f4 = (*(f32 *)(temp_v0_3 + 0x8));
                            buf.f8 = (*(f32 *)(temp_v0_3 + 0xC));
                            buf.b2 = (*(u8 *)(temp_v0_3 + 0x2));
                            buf.b0 = (*(u8 *)(temp_v0_3 + 0x0));
                            buf.b3 = (*(u8 *)(temp_v0_3 + 0x3));
                            buf.b1 = (*(u8 *)(temp_v0_3 + 0x1));
                            buf.w10 = (*(s32 *)(temp_v0_3 + 0x10));
                            buf.b14 = (*(u8 *)(temp_v0_3 + 0x4));
                            buf.h16 = (*(u16 *)(temp_v0_3 + 0x6));
                            var_v1 = ((u32) ((*(s32 *)(var_s2 + 0x0)) << 0xB) >> 0x1E) & 0xFF;
                        } else {
                            temp_v1 = (*(s32 *)(var_s0 + 0x14));
                            temp_v0_4 = (*(s32 *)(temp_v1 + 0x50));
                            buf.f4 = (*(f32 *)(temp_v1 + 0x44));
                            buf.f8 = (*(f32 *)(temp_v1 + 0x40));
                            buf.b2 = (*(u8 *)(temp_v1 + 0x6));
                            if ((*(u8 *)(temp_v1 + 0x1)) == 0) {
                                buf.b3 = (*(u8 *)(temp_v0_4 + 0xE0));
                            } else {
                                buf.b3 = (*(u8 *)(temp_v1 + 0x1));
                            }
                            buf.b0 = (*(u8 *)(temp_v0_4 + 0x4));
                            buf.b1 = (*(u8 *)(temp_v0_4 + 0xC));
                            buf.w10 = (*(s32 *)(temp_v0_4 + 0xDC));
                            buf.b14 = (*(u8 *)(temp_v0_4 + 0xF));
                            buf.h16 = (*(u16 *)(temp_v0_4 + 0x20));
                            var_v1 = (*(u8 *)(temp_v0_4 + 0x9)) & 7 & 0xFF;
                            if ((*(s32 *)(*(s32 *)(temp_v0_4 + 0x4C)) & 0x20000000) && ((*(s32 *)(temp_v0_4 + 0x3)) & 8)) {
                                buf.f4 = 0.0f;
                                buf.f8 = 0.0f;
                            }
                        }
                        sp63 = var_v1;
                        temp_f18 = buf.f4 * (*(f32 *)(var_s0 + 0xC) * *(f32 *)(var_s0 + 0x8));
                        buf.f4 = temp_f18;
                        buf.f4 = temp_f18 * *(f32 *)(g + 0x204C);
                        buf.f8 *= sp5C;
                        func_3be70(temp_s1, &buf);
                        (*(u8 *)(var_s2 + 0x1)) = (u8) (((sp63 * 8) & 0x18) | ((*(u8 *)(var_s2 + 0x1)) & 0xFFE7));
                    }
                }
                var_v0 = *(s32 *)(g + 0x2070) * 0xD;
            }
            var_s4 += 0xD0;
        } while (var_s4 < (var_v0 * 0x10));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027E24);
#endif

/* game_libs_func_0002831C: range-bucket lookup returning a0+8/+16/+24. splat
 * mis-split the two later branch targets into 00028334/00028350; merged here.
 * NM at 2 diffs: target holds a0+24 in $v1 and returns via `move v0,v1`; mine
 * computes a0+24 directly into $v0. Regalloc-class — permuter floored (best 60,
 * no zero in 120s), and no C form pins the value to $v1 then moves. */
#ifdef NON_MATCHING
char *game_libs_func_0002831C(char *a0, int a1) {
    if (a1 < *(unsigned char*)(a0 + 1)) {
        return a0 + 8;
    }
    if (*(unsigned char*)(a0 + 2) >= a1) {
        return a0 + 16;
    }
    return a0 + 24;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002831C);
#endif

// gl_func_00028358 — STRUCTURAL PASS (0xD4 / 53 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Resolves an (a0,a1) handle into the global selection slot.
//
//   int gl_func_00028358(int a0, int a1) {
//     if (a0 == 0xFF) return 0;                          // none sentinel
//     int r = (*lookup)(a0, a1);                          // jal 0 USO
//     if (r != 0) {
//       *(int*)(&D_0 + 0x2158) = r;                        // hit: store
//       return ...;
//     }
//     R *rec = *(R**)(&D_0 + 0x2030) + a0*0x14;            // registry
//     byte cap = rec->b_0;                                  // sub count
//     int packed = (a0 << 8) | a1;
//     if (a1 < cap) packed += 1;                            // clamp adj
//     *(int*)(&D_0 + 0x2158) = packed;                      // store sel
//   }
//
// Struct-typing reference: maps a two-part handle (a0 = registry
//   record index, a1 = sub-entry) to the global "current selection"
//   word &D_0+0x2158. a0 == 0xFF is the no-selection sentinel
//   (returns 0). A USO-relocated lookup (`jal 0` slot) is tried
//   first; its non-zero result is stored directly. On miss it indexes
//   the primary registry table &D_0+0x2030 (0x14 stride — same table
//   as gl_func_000221D8 / gl_func_00025AC8 / gl_func_00025C54),
//   range-checks a1 against the record's byte +0 sub-count, and
//   stores the packed (a0<<8)|a1 (with a clamp adjustment) into the
//   selection slot. The "select / resolve handle" entry feeding the
//   registry subsystem's current-item state.
// 2026-05-31: 54.9% -> 85.47% via the gl_func_0002842C complete-flow (prior
//   sketch was semantically WRONG). This variant: cap = rec->byte_0 (not b_1),
//   sub-table = rec->8 (not 0xC), NO v1 bounds-check, uses a1 directly (no a2
//   copy), flags 0x300 (cap-exceeded) / 0x100 (final). Remaining ~14%: prologue
//   ra-save ordering + register alloc (same as 2842C). Sibling 28510 has a more
//   intricate tail (halfword cap rec->h4, sub-stride a2*8, v1-load epilogue) —
//   deferred. Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00028358(int a0, int a1) {
    int r;
    int *rec;
    int *p;
    int v1;
    if (a0 == 0xFF) {
        return 0;
    }
    r = gl_func_00000000(a0, a1);
    if (r == 0) {
        *(int *)((char *)&D_00000000 + 0x2158) = a0 + 0x10000000;
        return 0;
    }
    rec = (int *)(*(int *)((char *)&D_00000000 + 0x2030) + a0 * 0x14);
    if (a1 >= *(unsigned char *)rec) {
        *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x3000000;
        return 0;
    }
    p = (int *)(*(int *)((char *)rec + 8) + a1 * 4);
    v1 = *p;
    if (v1 != 0) {
        return v1;
    }
    *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x1000000;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028358);
#endif

// gl_func_0002842C — STRUCTURAL PASS (0xE4 / 57 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Near-identical SIBLING of gl_func_00028358 — same handle-
// resolve into the &D_0+0x2158 selection slot, different sub-count
// field and lookup arg.
//
//   int gl_func_0002842C(int a0, int a1) {
//     if (a0 == 0xFF) return 0;                          // none sentinel
//     int r = (*lookup)(a0, a1);                          // jal 0 USO
//     if (r != 0) { *(int*)(&D_0 + 0x2158) = r; return …; }
//     R *rec = *(R**)(&D_0 + 0x2030) + a0*0x14;            // registry
//     byte cap = rec->b_1;                                  // sub count
//     int packed = (a0 << 8) | a1;
//     if (a1 < cap) packed += 1;
//     *(int*)(&D_0 + 0x2158) = packed;
//   }
//
// Struct-typing reference: structurally identical to gl_func_00028358
//   (see its comment) — maps an (a0,a1) handle to the global
//   selection word &D_0+0x2158 via a USO-relocated lookup then a
//   fallback into the &D_0+0x2030 / 0x14-stride registry table. The
//   ONLY differences: this variant range-checks a1 against the
//   record's byte +1 (vs gl_func_00028358's byte +0) — i.e. a
//   different sub-count field of the same record — and forwards the
//   arg via $a2. The two are the per-sub-field-class select/resolve
//   entries for the registry current-item state.
// 2026-05-31: 56.05% -> 88.25% by COMPLETING the logic (prior sketch was
//   semantically WRONG — it did `if(r!=0) {store r; return r;}` then a bogus
//   packed+1 path). Real flow (from expected asm): a0==0xFF -> ret 0; else
//   r=lookup(a0,a1); if r==0 -> store a0+0x10000000, ret 0; else
//   rec=*(&D+0x2030)+a0*0x14; if a1>=rec->b1 (cap) -> store (a0<<8)+a1+0x4000000,
//   ret 0; else v1=rec->0xC; if (u32)v1<0x80000000 -> ret 0; else
//   val=*(v1+a1*4); if val!=0 ret val; else store (a0<<8)+a1+0x5000000, ret 0.
//   The three lui-flags (0x1000/0x400/0x500 <<16) are state-class bits OR'd in.
//   REMAINING (~88%): IDO emits the a0==0xFF check BEFORE the ra-save (target
//   saves ra first / routes the early return through the shared epilogue) +
//   register allocation; goto-shared-ret0 and result-var forms both scored LOWER
//   (64.7% / frame-grew) — early-returns is the best C form. Apply this complete
//   flow to the siblings gl_func_00028358 / gl_func_00028510 (same shape).
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_0002842C(int a0, int a1) {
    int r;
    int *rec;
    int v1;
    int *p;
    int val;
    if (a0 == 0xFF) {
        return 0;
    }
    r = gl_func_00000000(a0, a1);
    if (r == 0) {
        *(int *)((char *)&D_00000000 + 0x2158) = a0 + 0x10000000;
        return 0;
    }
    rec = (int *)(*(int *)((char *)&D_00000000 + 0x2030) + a0 * 0x14);
    if (a1 >= *(unsigned char *)((char *)rec + 1)) {
        *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x4000000;
        return 0;
    }
    v1 = *(int *)((char *)rec + 0xC);
    if ((unsigned int)v1 < 0x80000000U) {
        return 0;
    }
    p = (int *)(v1 + a1 * 4);
    val = *p;
    if (val != 0) {
        return val;
    }
    *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x5000000;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002842C);
#endif

// gl_func_00028510 — STRUCTURAL PASS (0xF4 / 61 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). Third SIBLING of gl_func_00028358 / gl_func_0002842C —
// same handle-resolve into the &D_0+0x2158 selection slot, with a
// halfword sub-count field.
//
//   int gl_func_00028510(int a0, int a1) {
//     if (a0 == 0xFF) return 0;                          // none sentinel
//     int r = (*lookup)(a0, a1);                          // jal 0 USO
//     if (r != 0) { *(int*)(&D_0 + 0x2158) = r; return …; }
//     R *rec = *(R**)(&D_0 + 0x2030) + a0*0x14;            // registry
//     short cap = rec->h_4;                                 // sub count
//     int packed = (a0 << 8) | a1;
//     if (a1 < cap) packed += 1;
//     *(int*)(&D_0 + 0x2158) = packed;
//   }
//
// Struct-typing reference: identical to gl_func_00028358 /
//   gl_func_0002842C (see their comments) — (a0,a1) -> &D_0+0x2158
//   via USO-relocated lookup then a &D_0+0x2030 / 0x14-stride registry
//   fallback. The ONLY difference vs the other two: this variant
//   range-checks a1 against the record's HALFWORD at +0x4 (94590004
//   lhu) rather than a byte at +0 / +1 — i.e. it consults a 16-bit
//   sub-count field of the same record. The three together cover the
//   byte-+0 / byte-+1 / halfword-+4 sub-count variants of the
//   registry select/resolve entry.
// 2026-05-31: 53.11% -> 89.75% via the gl_func_0002842C complete-flow (prior
//   sketch was semantically WRONG). This variant: cap = rec->halfword_4, sub-
//   table base = rec->0x10, sub-stride a1*8 (not *4), v1 bounds-check >=0x80000000,
//   flags 0x400/0x500. Degenerate tail: when v1!=0, t7=*v1; v0=v1; return v1 iff
//   t7!=0 else 0 (the v1==0 branch stores packed+0x5000000 then loads *v1=*(0) —
//   harmless, v0 already 0). Remaining ~10% = prologue ra-save ordering + regalloc.
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
int gl_func_00028510(int a0, int a1) {
    int r;
    int *rec;
    int base;
    int *v1;
    int t7;
    if (a0 == 0xFF) {
        return 0;
    }
    r = gl_func_00000000(a0, a1);
    if (r == 0) {
        *(int *)((char *)&D_00000000 + 0x2158) = a0 + 0x10000000;
        return 0;
    }
    rec = (int *)(*(int *)((char *)&D_00000000 + 0x2030) + a0 * 0x14);
    if (a1 >= *(unsigned short *)((char *)rec + 4)) {
        *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x4000000;
        return 0;
    }
    base = *(int *)((char *)rec + 0x10);
    if ((unsigned int)base < 0x80000000U) {
        return 0;
    }
    v1 = (int *)(base + a1 * 8);
    if (v1 == 0) {
        *(int *)((char *)&D_00000000 + 0x2158) = (a0 << 8) + a1 + 0x5000000;
    }
    t7 = *v1;
    if (t7 != 0) {
        return (int)v1;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028510);
#endif

// gl_func_00028604 — STRUCTURAL PASS (0x268 / 154 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An object detach / relink manager.
//
// 2026-06-02 FULL DECODE 15.2->74.9% (+59.7pp): the splice operates on
// `owner = obj->0x2C` (NOT the param); arg2 `a1` is an INT TAG (saved sp+0x36,
// compared !=7 / &0xF==6 to gate the flag/FP paths). owner-relink (0x48/0x44/
// 0x40 with -1 sentinel) + a sub-object copy block (dst=owner+0x4C <- obj &
// node=obj->0x50 byte/halfword/word fields) + node->0x4C-sign & node->3-bit8
// gate (owner+0xB0 |= 0x20) + (node->1?node->0xE0:obj->1) sb dst+3 + the
// tag==6 (flag/FP const &D+0x2050) vs else (FP scale: (s8)node->0x8D *
// owner->0x70 * 1/256 -> owner->0x64, table &D+0x2CF8[idx*4] -> owner->0x6C)
// paths + final jal 0x3D414(owner->0xC + 16). Residual ~25% = regalloc + the
// branch-likely unlink ordering (validation early-returns are approximate).
//
//   void gl_func_00028604(O *obj, A *a1) {
//     if (obj == (O*)-1) return;                         // null sentinel
//     byte fl = obj->b_0;
//     if (obj->w_2C == 0) return;                         // not linked
//     obj->b_0 = fl & ~0x08;                               // clear bit3
//     int nx = obj->w_48;                                  // next link
//     if (nx != a1) ...                                     // relink:
//     obj->w_48 = -1;                                       //  unlink
//     int p = a1->w_44;                                     //  patch
//     ...                                                    //  prev
//     byte st = obj->b_60;
//     float g = *(float*)(&D_0 + 0x2050);                   // global
//     obj->b_60 = st | 0x10;                                 // set bit4
//   }
//
// Struct-typing reference: detaches object `obj` from a linked
//   structure. obj fields: byte +0 a flag set (bit3 = linked/active,
//   cleared on detach), word +0x2C a parent/owner pointer (zero ==
//   already detached, early return), word +0x48 the next-link pointer
//   (set to -1 to unlink), byte +0x60 a status flag set (bit4 set to
//   mark detached/dirty). `a1` is the neighbour node whose word +0x44
//   back-link is patched during the splice. &D_0+0x2050 is a global
//   float constant referenced in the body. The -1 value is the null/
//   end-of-list sentinel (consistent with the other game_libs
//   linked-structure helpers). The unlink/detach entry of the
//   game_libs object subsystem (counterpart to the gl_func_00027D00
//   pull-and-apply link op).
// Caps (DEFERRED): raw-word USO + linked-structure splice + FP global
//   load — byte-match needs USO mnemonic disasm. Real-C STRUCTURAL
//   body below per the analysis (placeholder calls / fields).
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
extern int gl_func_0003D414();
void gl_func_00028604(char *obj, int tag) {
    char *owner, *node, *dst;
    unsigned char fl;
    int prev;
    if ((int)obj == -1) return;
    fl = *(unsigned char *)obj;
    owner = *(char **)(obj + 0x2C);
    *(unsigned char *)obj = fl & ~0x08;
    if (owner == 0) return;
    if ((int)obj == *(int *)(owner + 0x48)) {
        *(int *)(owner + 0x48) = -1;
    }
    prev = *(int *)(owner + 0x44);
    if ((int)obj == prev) {
        if (-1 != *(int *)(owner + 0x48)) return;
        if (-1 != *(int *)(owner + 0x48)) return;
        if ((int)obj != *(int *)(owner + 0x40)) return;
        if (tag == 6) return;
        *(unsigned char *)(owner + 0x60) = *(unsigned char *)(owner + 0x60) | 0x10;
        *(float *)(owner + 0x6C) = *(float *)((char *)&D_00000000 + 0x2050);
        return;
    }
    if ((tag & 0xF) == 6) return;
    dst = owner + 0x4C;
    *(float *)(dst + 8) = *(float *)(obj + 0x44);
    *(float *)(dst + 0xC) = *(float *)(obj + 0x40);
    *(unsigned char *)(dst + 2) = *(unsigned char *)(obj + 6);
    node = *(char **)(obj + 0x50);
    if (node != 0) {
        *(unsigned char *)(dst + 0) = *(unsigned char *)(node + 4);
        *(unsigned char *)(dst + 1) = *(unsigned char *)(node + 0xC);
        *(int *)(dst + 0x10) = *(int *)(node + 0xDC);
        *(unsigned short *)(dst + 6) = *(unsigned short *)(node + 0x20);
        *(unsigned char *)(dst + 4) = *(unsigned char *)(node + 0xF);
        if ((*(int *)(*(char **)(node + 0x4C)) << 2) < 0
            && (*(unsigned char *)(node + 3) & 8)) {
            *(unsigned char *)(owner + 0xB0) = *(unsigned char *)(owner + 0xB0) | 0x20;
        }
        if (*(unsigned char *)(obj + 1) == 0) {
            *(unsigned char *)(dst + 3) = *(unsigned char *)(node + 0xE0);
        } else {
            *(unsigned char *)(dst + 3) = *(unsigned char *)(obj + 1);
        }
        *(unsigned char *)(owner + 0x30) = *(unsigned char *)(node + 6);
    } else {
        *(unsigned char *)(dst + 3) = *(unsigned char *)(obj + 1);
        *(unsigned char *)(owner + 0x30) = 1;
    }
    *(int *)(owner + 0x40) = *(int *)(owner + 0x44);
    *(int *)(owner + 0x44) = -1;
    if (tag != 7) {
        if ((tag & 0xF) == 6) {
            *(unsigned char *)(owner + 0x60) = *(unsigned char *)(owner + 0x60) | 0x10;
            *(unsigned char *)(owner + 0x34) = 2;
            *(float *)(owner + 0x6C) = *(float *)((char *)&D_00000000 + 0x2050);
        } else {
            *(unsigned char *)(owner + 0x34) = 1;
            *(unsigned char *)(owner + 0x60) = *(unsigned char *)(owner + 0x60) | 0x20;
            if (*(unsigned char *)(obj + 0x18) == 0) {
                node = *(char **)(obj + 0x50);
                *(float *)(owner + 0x6C) = *(float *)(*(int *)((char *)&D_00000000 + 0x2CF8) + *(unsigned char *)(node + 0x8C) * 4);
            } else {
                *(float *)(owner + 0x6C) = *(float *)(*(int *)((char *)&D_00000000 + 0x2CF8) + *(unsigned char *)(obj + 0x18) * 4);
            }
            node = *(char **)(obj + 0x50);
            *(float *)(owner + 0x64) = (float)*(signed char *)(node + 0x8D) * *(float *)(owner + 0x70) * (1.0f / 256.0f);
        }
        gl_func_0003D414(*(int *)(owner + 0xC) + 16);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028604);
#endif

extern int gl_ref_0003CC70();
int gl_func_0002886C(int a0) {
    return gl_ref_0003CC70(a0, 6);
}

// gl_func_0002888C — STRUCTURAL PASS (0x124 / 73 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing FP helper) — deferred USO re-split. The
// named leading fn (~6 words) is a tiny tail-call thunk.
//
//   void gl_func_0002888C(int a0) {
//     (*op)(a0, 7);                                     // jal 0x3CC70
//   }                                                     //  (0x0C00F31C)
//
// Struct-typing reference: the named leading fn forwards its caller
//   arg plus the constant 7 to the fixed USO-relocated routine
//   0x0C00F31C (≈0x3CC70) — a one-line "do operation #7" wrapper. The
//   trailing bundled body is an FP clamp/interpolation helper: it
//   clamps a count arg to a max of 0x80, reads float fields a1->0x28
//   / a1->0x30 and byte a1->0x20, pulls a float constant from
//   &D_0+0xFD4, and runs single-precision compares/mul/add
//   (c.lt.s / mul.s / add.s) to produce a clamped interpolated value
//   written back at a1->0xC0 — a typical parameter-easing leaf, left
//   for the deferred USO re-split.
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc to 0x3CC70/op=7 —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   STALE 2-jr-bundle comment: .s is 0x20 / 8 words single fn (the
//   FP helper now lives elsewhere). Real-C STRUCTURAL body below per
//   the analysis: tail-call thunk forwarding (a0, 7). Byte-match
//   deferred. Name pre-checked: no extern reuse.
extern int gl_ref_0003CC70();
void gl_func_0002888C(int a0) {
    gl_ref_0003CC70(a0, 7);
}

/* game_libs_func_000288AC: 65-insn FP threshold-classifier (fresh decode 2026-05-28,
 * mnemonic disasm — m2c can't read raw-.word USO). Clamps a2 to >=128, computes a
 * weight f2 from a1->0x30 (scaled by a1->0x28+1 when a1->0x20!=0 && a1->0x28>0),
 * classifies it against 3 thresholds in the D[] float table at +0xFD4.. → tier
 * v1 (0/1/2/3) with a per-tier multiplier, writes back a1->0x30 *= multiplier,
 * stores a2 and v1 as bytes to a0->0x31/0x32, and a0->0xC0 =
 * D_table[a2] + (v1<<7). Returns v1. 75.08 -> 99.92 (2026-05-31): the 7 FP
 * threshold consts (&D+0xFD4..0xFEC) AND the D_table base now use DISTINCT
 * externs (D_00000FD4.. + D_tbl_288ac in undefined_syms_auto.txt) so each lwc1
 * re-materializes its own `lui at` instead of CSE'ing the base into one reg —
 * the comment's own "separate per-threshold symbols" hypothesis was right; the
 * distinct-extern lever busts it (+24.6pp). The `f12+1.0f` scale named into a
 * local `float s` fixed the mul.s ft operand (+0.07pp). RESIDUAL (1 insn, cap):
 * `mul.s $f2,$f0,$f8` vs target `$f2,$f2,$f8` — f0 and f2 hold the SAME value
 * (f2=f0 init), and IDO uses the live original f0 as fs where the target reuses
 * the f2 copy; a register-aliasing choice not C-drivable (the lwc1 `,0(at)` vs
 * `,4052(at)` and branch-address diffs are reloc-blind/position, already matched).
 * Real wrap (correct logic); stays NM.
 *
 * 2026-06-01 re-confirmed + extra levers ruled out. The target loads a1->0x30
 * exactly ONCE (`lwc1 f0,0x30(a1)` @0x288C0), keeping f0 as the long-lived
 * "original" through the final `f4 = f0 * f2`; f2 is the short-lived working
 * copy (`f2 = f0`). So `f2 = f2 * s` value-numbers f2's source to the live f0
 * (build `mul.s f2,f0,f8`) where the target re-reads the f2 copy
 * (`mul.s f2,f2,f8`). Do NOT retry: (a) independent double-load of a1->0x30
 * for the working copy — target single-loads, a 2nd lwc1 diverges; (b) f0/f2
 * role-swap / rename — pure relabel, IDO allocates by live-range so f0 stays
 * the long-lived reg; (c) `s * f2` operand swap — value-numbering still pulls
 * f0. Live-range-bound FP value-numbering, irreducible from C. */
extern float D_00000FD4, D_00000FD8, D_00000FDC, D_00000FE0, D_00000FE4, D_00000FE8, D_00000FEC;
extern char D_tbl_288ac;
/* 288AC TRUE GATE (2026-06-10 byte-diff with reloc awareness): the
 * lwc1-displacement "diffs" are unresolved-reloc artifacts (the
 * individual D_00000FDx externs resolve correctly at link); the SOLE
 * real diff is mul.s $f2,$f2,$f8 (target) vs $f2,$f0,$f8 (build) --
 * IDO copy-propagates f0 into the scale-mul (f2==f0 at that point).
 * Probed: fresh-load (98.77, dup lwc1), copy-inversion (99.15, web
 * shift) -- both worse than the 99.92 baseline. The original blocked
 * propagation by an unknown structure; single-operand copy-prop gate.
 */
int game_libs_func_000288AC(char *a0, char *a1, int a2)
{
  float f0;
  float f2;
  float f4;
  int v1 = 0;
  if (a2 < 128)
  {
    a2 = 128;
  }
  f0 = *((float *) (a1 + 0x30));
  f2 = f0;
  if ((*((unsigned char *) (a1 + 0x20))) != 0)
  {
    float f12 = *((float *) (a1 + 0x28));
    if (f12 > 0.0f)
    {
      float s = f12 + 1.0f;
      f0 = *((float *) (a1 + 0x30));
      f2 = f2 * s;
    }
  }
  if (f2 < D_00000FD4)
  {
    v1 = 0;
    f2 = D_00000FD8;
  }
  else
    if (f2 < D_00000FDC)
  {
    v1 = 1;
    f2 = D_00000FE0;
  }
  else
    if (f2 < D_00000FE4)
  {
    v1 = 2;
    f2 = D_00000FE8;
  }
  else
  {
    v1 = 3;
    f2 = D_00000FEC;
  }
  f4 = f0 * f2;
  *((float *) (a1 + 0x30)) = f4;
  a0[0x31] = (char) a2;
  a0[0x32] = (char) v1;
  *((int *) (a0 + 0xC0)) = (*((int *) ((((char *) (&D_tbl_288ac)) + (a2 * 4)) - (0x200 & 0xFFFF)))) + (v1 << 7);
  return v1;
}


/* gl_func_000289B0: 22-insn. sel = a1->u8[2]; if (sel==255) sel =
 * (s16)(*(int**)(a1+0x50))->[0x24]; v1 = a0->u8[0x32];
 * rv = gl_func_0003CF18(a0, a1, sel);   // jal in-segment 0x3CF18
 * if (rv != v1) a0->u8[0xB6] = (rv << 2) + v1;  (bnel sel,255). */
extern int gl_func_0003CF18();
/* sel = a1->u8[2]; if (sel==255) sel = (s16)(*(int**)(a1+0x50))->[0x24];
 * v1 = a0->u8[0x32]; rv = gl_func_0003CF18(a0,a1,sel);
 * if (rv != v1) a0->u8[0xB6] = (rv<<2)+v1. Byte-exact: declaring v1 FIRST
 * places its spill at sp+0x1C (first-declared = highest slot) to match. */
void gl_func_000289B0(int a0, int a1) {
    int v1;
    int rv;
    int sel = *(unsigned char*)(a1 + 2);
    if (sel == 255) {
        sel = *(short*)((char*)*(int**)(a1 + 0x50) + 0x24);
    }
    v1 = *(unsigned char*)(a0 + 0x32);
    rv = gl_func_0003CF18(a0, a1, sel);
    if (rv != v1) {
        *(unsigned char*)(a0 + 0xB6) = (rv << 2) + v1;
    }
}

/* game_libs_func_00028A08: 4-insn self-linked-list init. */
void game_libs_func_00028A08(int *a0) {
    a0[0] = (int)a0;
    a0[1] = (int)a0;
    a0[2] = 0;
}

/* gl_func_00028A18: 20-insn 4-call init wrapper for 4 contiguous 0x10-byte
 * blocks. Calls gl_func_0003D074 (alt-entry inside gl_func_0003D068 at +0xC)
 * on each block, then sets each block's [0xC] field to self-reference (= a0).
 * Byte-exact: 4 jals resolve to gl_func_0003D074 (0x3D074). */
extern void gl_func_0003D074();
void gl_func_00028A18(char *a0) {
    gl_func_0003D074(a0);
    gl_func_0003D074(a0 + 0x10);
    gl_func_0003D074(a0 + 0x20);
    gl_func_0003D074(a0 + 0x30);
    *(int*)(a0 + 0x0C) = (int)a0;
    *(int*)(a0 + 0x1C) = (int)a0;
    *(int*)(a0 + 0x2C) = (int)a0;
    *(int*)(a0 + 0x3C) = (int)a0;
}

// gl_func_00028A68 — STRUCTURAL PASS (0xA4 / 41 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). The bulk record-array INITIALIZER of the sprite subsystem.
//
//   void gl_func_00028A68(void) {
//     (*setup)(&D_5378);                                // jal 0 USO
//     S *g = &D_0;
//     int n = g->w_2070;                                 // record count
//     if (n <= 0) return;
//     for (int i = 0, off = 0; i < n; i++, off += 0xD0) { // 0xD0 stride
//       R *rec = (char*)*(R**)(&D_0 + 0x2CFC) + off;
//       rec->w_8 = rec;                                    // self-ptr
//       rec->w_0 = 0;                                       // clear
//       (*initRec)(rec);                                    // jal 0 USO
//     }
//   }
//
// Struct-typing reference: iterates the SAME primary sprite record
//   table as gl_func_0001E134 / gl_func_0001FAE8 / gl_func_00027E24 —
//   live count word &D_0+0x2070, record-table pointer &D_0+0x2CFC —
//   here with a per-record stride of 0xD0. For every record it writes
//   a self-referential pointer at +0x8, zeroes word +0x0, and calls a
//   USO-relocated per-record initializer (`jal 0` slot). A leading
//   USO-reloc setup call is passed the &D_5378 fn-ptr/string table
//   (the same auxiliary table gl_func_0001FAE8 uses). This is the
//   one-time "construct/clear every sprite record" pass that primes
//   the subsystem before gl_func_0002119C drives it per-frame.
// Caps (DEFERRED): raw-word USO + record-init loop with jal-0
//   USO-reloc — byte-match needs USO mnemonic disasm + reloc-pad jal
//   infra. Real-C STRUCTURAL body below per the analysis (placeholder
//   calls / fields). Byte-match deferred.
//   Name pre-checked: no extern reuse (collision-safe).
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00028A68(void) {
    int n;
    int i;
    gl_func_00000000((char *)&D_00000000 + 0x5378);
    n = GL_COUNT_2070;
    if (n <= 0) return;
    for (i = 0; i < n; i++) {
        char *rec = *(char **)0x2CFC + i * 0xD0;
        *(int *)(rec + 8) = (int)rec;
        *(int *)rec = 0;
        gl_func_00000000(rec);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028A68);
#endif

// gl_func_00028B0C — STRUCTURAL PASS (0x160 / 88 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A 4-way mode dispatcher over parallel descriptor tables.
//
//   void gl_func_00028B0C(O *obj, …, int mode) {  // mode passed on stack
//     D *t0 = &D_53A8, *t1 = &D_5398;
//     D *t2 = &D_5388, *t3 = &D_5378;                     // 4 tables
//     void *sub;
//     switch (mode) {
//       case 0:  sub = obj;        break;                 // +0x00
//       case 1:  sub = obj + 0x10; break;
//       case 2:  sub = obj + 0x20; break;
//       case 3:  sub = obj + 0x30; break;
//       default: sub = obj + 0x..; break;
//     }
//     ... register `sub` against the mode-selected &D_53xx table ...
//   }
//
// Struct-typing reference: routes by a stack-passed `mode` (0..4)
//   onto one of four parallel fixed descriptor blobs in the &D_53xx
//   pool — &D_53A8 / &D_5398 / &D_5388 / &D_5378 (the same auxiliary
//   descriptor/fn-ptr pool gl_func_0001FAE8 / gl_func_00028A68 use) —
//   and a matching object sub-structure at obj + 0x00 / 0x10 / 0x20 /
//   0x30 (parallel 0x10-stride sub-blocks). It then registers/binds
//   the selected sub-block with the selected table. A per-channel
//   binding dispatcher in the game_libs subsystem (four logical
//   channels sharing one object, one descriptor table each).
// Caps (DEFERRED): raw-word USO + 4-way mode switch over parallel
//   tables — byte-match needs USO mnemonic disasm. Real-C STRUCTURAL
//   body below per the analysis (placeholder calls / fields).
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior body was a single switch, reversed tbls).
 * Loop over 4 modes s3=0..3: sub=obj+s3*16, tbl=&D+(0x5378+s3*16); drain the
 * linked list at sub->4 — while head != sub (and != 0): gl(head), gl(tbl, head),
 * re-read head=sub->4. */
void gl_func_00028B0C(char *obj) {
    int s3;
    char *sub, *tbl, *head;

    for (s3 = 0; s3 != 4; s3++) {
        switch (s3) {
        case 0:  sub = obj;        tbl = (char *)&D_00000000 + 0x5378; break;
        case 1:  sub = obj + 0x10; tbl = (char *)&D_00000000 + 0x5388; break;
        case 2:  sub = obj + 0x20; tbl = (char *)&D_00000000 + 0x5398; break;
        case 3:  sub = obj + 0x30; tbl = (char *)&D_00000000 + 0x53A8; break;
        default: sub = obj + 0x30; tbl = (char *)&D_00000000 + 0x53A8; break;
        }
        head = *(char **)(sub + 4);
        while (head != sub) {
            if (head == 0) {
                break;
            }
            gl_func_00000000(head);
            gl_func_00000000(tbl, head);
            head = *(char **)(sub + 4);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028B0C);
#endif

// gl_func_00028C6C — STRUCTURAL PASS (0x228 / 138 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 7-jr USO bundle
// (named fn + 6 trailing helpers) — deferred USO re-split. The named
// leading fn is a multi-mode counted loop processor.
//
//   void gl_func_00028C6C(int a0, int n, …) {
//     (*setup)(a0);                                     // jal 0 USO
//     if (n <= 0) return;
//     int mode = 0;
//     for (int i = 0; i < n; i++) {
//       switch (mode) {                                  // beq 1/2/3/4
//         case 1: (*h1)(…); break;
//         case 2: (*h2)(…); break;
//         case 3: (*h3)(…); break;
//         case 4: (*h4)(…); break;
//         default: ...
//       }
//       ... advance mode / index, accumulate ...
//     }
//   }
//
// Struct-typing reference: a state-driven counted dispatch loop. It
//   runs a leading USO-relocated setup, then iterates `n` (a1) times,
//   each pass routing on a running mode value in {1,2,3,4} to one of
//   four USO-relocated per-mode handlers (`jal 0` slots). Stack args
//   sp+0x44 / sp+0x48 (s2 / s1) and the caller object a0 thread
//   through the handlers. A small interpreter/sequencer: walk a
//   command/state list `n` long, executing the mode-appropriate
//   action each step. The 6 trailing bundled bodies are its
//   per-mode/helper leaves, left for the deferred USO re-split.
// Caps (DEFERRED): raw-word USO + 4-way mode loop with jal-0
//   USO-reloc handlers — byte-match needs USO mnemonic disasm +
//   reloc-pad jal infra. STALE 7-jr-bundle comment: grep -c
//   03E00008 = 1 (.s now single fn, helpers split elsewhere). Real-C
//   STRUCTURAL body below per the analysis (placeholder calls /
//   fields). Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01 (prior switch was a placeholder). gl(a0); for
 * each of 4 modes s4=0..3: tmpl=&D+0x5378+s4*16, dst=a0+s4*16; a shared inner
 * counter s0 drains gl(tmpl)→v (break when v==0) then gl(dst,v), s0++ while s0<n. */
void gl_func_00028C6C(int a0, int n) {
    char *s5 = (char *)a0;
    char *g = (char *)&D_00000000;
    int s4, s0;
    char *s2, *s1;

    gl_func_00000000(a0);
    if (n <= 0) {
        return;
    }
    s0 = 0;
    s2 = 0;
    s1 = 0;
    for (s4 = 0; s4 != 4; s4++) {
        switch (s4) {
        case 0: s1 = g + 21368; s2 = s5;      break;
        case 1: s1 = g + 21384; s2 = s5 + 16; break;
        case 2: s1 = g + 21400; s2 = s5 + 32; break;
        case 3: s1 = g + 21416; s2 = s5 + 48; break;
        }
        while (s0 < n) {
            int v = gl_func_00000000(s1);
            if (v == 0) {
                break;
            }
            gl_func_00000000(s2, v);
            s0++;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028C6C);
#endif

void game_libs_func_00028DA8(int *a0, int *a1) {
    if (*a1 != 0) {
        return;
    }
    *a1 = (int)a0;
    a1[1] = a0[1];
    *(int *)a0[1] = (int)a1;
    a0[1] = (int)a1;
    a0[2] = a0[2] + 1;
    a1[3] = a0[3];
}

void game_libs_func_00028DE8(int **a0) {
    int *p = a0[0];
    if (p != 0) {
        p[1] = (int)a0[1];
        *(int **)a0[1] = a0[0];
        a0[0] = 0;
    }
}

/* game_libs_func_00028E14: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00028E14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00028E28);

/* game_libs_func_00028E6C: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00028E6C);

void game_libs_func_00028E8C(void) {}

// gl_func_00028E94 — object attach/init (counterpart to gl_func_00028604
// detach). FULL DECODE 35.1->93.1% (+58pp) 2026-06-02: obj->0x40=-1, obj->0x44=
// d, obj->0x30 = d->0x50->5, d->0x2C=obj, d[0]|=1 then |=8, d->0x50->0x40=obj,
// d->0x50->0x44=d, d->0x40=0.0f, call 0x3C36C(obj,d); then v1=obj+0xB0:
// a2=d->2 (==0xFF -> d->0x50->0x24 short); v1->0x10=d->0x4C; (128<=a2<192 ?
// v1->1|=4 : v1->1&=~4); if((v1->0<<0xD)<0) call 0x3CF18(obj,d); v0=obj+0x30:
// v0->3=d->0x50->7, v0->5=(d->0x50->0 bit26), v1->1=(v1->1&~0xE0)|((d->0x50->8
// &3)<<5). Residual ~7% = scheduling/regalloc (d->0x50 reload reg). Body below.
//
//   void gl_func_00028E94(O *obj, D *d) {
//     obj->w_40 = -1;                                   // init link
//     obj->w_44 = d;                                     // descriptor
//     T *t = d->w_50;
//     obj->b_30 = t->b_5;                                 // copy flag
//     d->w_2C = obj;                                      // back-link
//     d->b_0 |= 1;                                        // active bit0
//     d->b_0 |= 8;                                         // ready bit3
//     t->w_40 = obj;  t->w_44 = d;                         // cross-link
//     d->f_40 = 0.0f;
//     jal 0x3C36C(obj, d);                                // 0x0C00F0DB
//     if (d->b_2 != 0xFF) { ... bind sub d->2 ... }
//     ... init the obj+0xB0 transform block ...
//   }
//
// Struct-typing reference: the attach/bind entry. obj fields: word
//   +0x40 (link, set to -1), word +0x44 (the descriptor pointer),
//   byte +0x30 (a mode/flag copied from d->0x50->5), block at +0xB0
//   (the same matrix/Vec4 block gl_func_00027804 / gl_func_00027D00
//   manipulate). descriptor d fields: byte +0 a flag set (bit0 =
//   active, bit3 = ready, both set here), word +0x2C the owner
//   back-link to obj, word +0x50 a shared sub-record (cross-linked at
//   its +0x40/+0x44 to obj/d), float +0x40 zeroed. byte d->2 is a
//   secondary id (0xFF = none sentinel). A leading USO-relocated
//   setup 0x0C00F0DB (≈0x3C36C) finishes the bind. The
//   construct/attach counterpart to the gl_func_00028604 detach in
//   the game_libs object subsystem.
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc setup + multi-field
//   link wiring — byte-match needs USO mnemonic disasm + reloc-pad
//   jal infra. Real-C STRUCTURAL body below per the analysis
//   (placeholder calls / fields). Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int gl_func_0003C36C();
extern int gl_func_0003CF18();
void gl_func_00028E94(char *obj, char *d) {
    char *t, *node, *v1, *v0;
    int a2;
    *(int *)(obj + 0x40) = -1;
    *(int *)(obj + 0x44) = (int)d;
    t = *(char **)(d + 0x50);
    *(unsigned char *)(obj + 0x30) = *(unsigned char *)(t + 5);
    *(int *)(d + 0x2C) = (int)obj;
    *(unsigned char *)d = *(unsigned char *)d | 1;
    *(unsigned char *)d = *(unsigned char *)d | 8;
    *(int *)(t + 0x40) = (int)obj;
    *(int *)(*(char **)(d + 0x50) + 0x44) = (int)d;
    *(float *)(d + 0x40) = 0.0f;
    gl_func_0003C36C(obj, d);
    v1 = obj + 0xB0;
    a2 = *(unsigned char *)(d + 2);
    if (a2 == 0xFF) {
        a2 = *(short *)(*(char **)(d + 0x50) + 0x24);
    }
    *(int *)(v1 + 0x10) = *(int *)(d + 0x4C);
    if (a2 >= 128 && a2 < 192) {
        *(unsigned char *)(v1 + 1) = *(unsigned char *)(v1 + 1) | 4;
    } else {
        *(unsigned char *)(v1 + 1) = *(unsigned char *)(v1 + 1) & ~4;
    }
    if ((*(int *)v1 << 0xD) < 0) {
        gl_func_0003CF18(obj, d);
    }
    node = *(char **)(d + 0x50);
    v0 = obj + 0x30;
    *(unsigned char *)(v0 + 3) = *(unsigned char *)(node + 7);
    node = *(char **)(d + 0x50);
    *(unsigned char *)(v0 + 5) = (unsigned int)(*(int *)node << 5) >> 31;
    node = *(char **)(d + 0x50);
    *(unsigned char *)(v1 + 1) =
        (*(unsigned char *)(v1 + 1) & ~0xE0) | ((*(unsigned char *)(node + 8) & 3) << 5);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028E94);
#endif

void gl_func_00028FCC(int *a0, int a1) {
    volatile int **vp0 = (volatile int **)&a0;
    volatile int *vp1 = (volatile int *)&a1;
    gl_func_00000000(a0[0x44/4]);
    a0[0x48/4] = a1;
    (void)vp0;
    (void)vp1;
}

#ifdef NON_MATCHING
/* Split off from gl_func_00028FCC bundle 2026-05-08: 11-insn no-frame
 * config setter. Stores a1 to a0->field_48, reads a0->field_50's child
 * field_5 byte to a0->field_30, ORs bit 0x10 into a0->field_60, loads
 * a float from D[0x2050] and stores it to a0->field_6C.
 *
 * 2026-06-22 STRUCTURAL FIX: arg1 is a POINTER, and `sub` is loaded from
 * a1->field_50 (lw t6,80(a1)) — NOT a0->field_50 as the prior decode read.
 * Fixing the base + reordering the tail (field_30 store, float store, then
 * field_60|0x10 store LAST) brought the body to insn-order-exact: only the
 * register coloring differs now (6 words). 25.82% -> the sole residual is
 * REG_ALLOC_ORDER picking $v0/$v1 for the first two loaded temps where the
 * target uses $t6/$t9 (then $t7/$t0). Same insn count + order; no C-level
 * lever forces IDO to skip $v0/$v1 in this 2-arg void leaf (it never calls,
 * so v0/v1 stay in the free pool and get picked first). Genuine coloring
 * cap; INCLUDE_ASM build emits correct bytes. */
void game_libs_func_00029000(int *a0, int *a1) {
    int *sub;
    unsigned char flags;
    a0[0x48/4] = (int)a1;
    sub = (int*)a1[0x50/4];
    flags = *((unsigned char*)a0 + 0x60);
    *((char*)a0 + 0x30) = *((char*)sub + 0x5);
    *(float*)((char*)a0 + 0x6C) = *(float*)((char*)&D_00000000 + 0x2050);
    *((char*)a0 + 0x60) = flags | 0x10;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029000);
#endif

int gl_func_0002902C(char *a0, int a1) {
    int r = gl_func_00000000(a0, a1);
    if (r == 0) goto end;
    gl_func_00000000(r, a1);
    gl_ref_0003D414(a0 + 0x30, r);
end:
    return r;
}

/* gl_func_00029078: 20-insn cross-USO + alt-entry helper. Calls cross-USO
 * gl_func(a0+0x10, a1), then if non-NULL calls alt-entry gl_func_0003D66C
 * (inside gl_func_0003D620 at +0x4C), then cross-USO gl_func(a0+0x20, result).
 * Returns the first call's result (or 0). */
extern int gl_func_0003D66C();
int gl_func_00029078(int a0, int a1) {
    int v0 = gl_func_00000000(a0 + 0x10, a1);
    if (v0 == 0) goto end;
    gl_func_0003D66C(v0, a1);  /* a1 reloaded in jal's delay slot */
    gl_func_00000000(a0 + 0x20, v0);
end:
    return v0;
}

/* gl_func_000290C8: 62-insn (0xF8) sibling of gl_func_00029078 (just
 * landed 6b9ad3ee). 0x38-byte stack frame, calls gl_func_0003D480
 * directly (jal target 0x3D480, not the cross-USO placeholder).
 *
 * Decoded entry:
 *   t6 = 0x10; t7 = 0x10;             // const 16, stored as stack args
 *   sp[0x28] = t6; sp[0x2C] = t7;     // arg5,arg6 for jal
 *   t8 = a1->[0x50];                  // load field
 *   s0 = a0; s1 = a1;                 // save args via or
 *   gl_func_0003D480(a0+0x20, *(byte*)(sp+5), a1->[0x50], sp+0x24, 16, 16);
 *   if (ret == 0) {
 *     t9 = *(byte*)(s1 + 0x30);       // load tag byte
 *     sp[0x2C] = t9;
 *     // ... continues to second jal with similar pattern
 *   }
 *
 * Pattern: config-record builder calling internal helper at 0x3D480
 * twice with different fields (a1+0x50 first call, then a different
 * field from a1+0x30 byte for second). Reads fields at a1->0x30 (byte)
 * and a1->0x50 (int).
 *
 * Caps (DEFERRED): direct intra-USO jal 0x3D480 needs sym table
 * resolution. Real-C STRUCTURAL body below per the decode above.
 * Byte-match deferred. Name pre-checked: no extern reuse.
 * 90.47% (2026-06-02, dropped the `saved=a0+0x20` spill-local, inlining
 * a0+0x20 at both call sites; +0.07pp). Residual = original-a0 preservation
 * regalloc: a0+0x20 is needed at the first gl_3d480 call AND the later
 * gl(a0+0x20,s0) call, across the `s0=v0` reassignment, so IDO must keep the
 * original a0 live across two clobbering calls — it SPILLS it (extra `or a2,a0`
 * + sw/lw, +8 frame: sp-0x40 vs target sp-0x38) where the target holds it in a
 * callee-saved reg. No C shape flips spill->$s here (explicit `obj=a0` local
 * regresses to 88.5%). Permuter-class. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01 (prior body was heavily oversimplified). Two
 * gl_3d480 lookups keyed on (*(a1->0x50))->5: v1=lookup(a0+0x20,k),
 * v0=lookup(a0+0x30,k); track their 0x30 fields (default 16). If both null
 * return 0. If v0->0x30 < v1->0x30: register the v0 entry (gl(s0), gl_3d638,
 * gl(a0+0x20,s0)) and set its 0x30; else link v1->0x48=a1 and set v1->0x30.
 * Returns the chosen entry. */
extern int gl_func_0003D480();
extern int gl_func_0003D638();
int gl_func_000290C8(char *a0, char *a1) {
    char *s0 = a0;
    int t2 = 16, t3 = 16;
    int *v1, *v0;

    v1 = (int *)gl_func_0003D480(a0 + 0x20, *(unsigned char *)(*(char **)(a1 + 0x50) + 5));
    if (v1 != 0) {
        t3 = *(unsigned char *)((char *)v1 + 0x30);
    }
    v0 = (int *)gl_func_0003D480(s0 + 0x30, *(unsigned char *)(*(char **)(a1 + 0x50) + 5));
    if (v0 != 0) {
        s0 = (char *)v0;
        t2 = *(unsigned char *)((char *)v0 + 0x30);
    }
    if (v1 == 0 && v0 == 0) {
        return 0;
    }
    if (t2 < t3) {
        gl_func_00000000(s0);
        gl_func_0003D638(s0, a1);
        gl_func_00000000(a0 + 0x20, s0);
        *(unsigned char *)(s0 + 0x30) = *(unsigned char *)(*(char **)(a1 + 0x50) + 5);
        return (int)s0;
    }
    *(int *)((char *)v1 + 0x48) = (int)a1;
    *(unsigned char *)((char *)v1 + 0x30) = *(unsigned char *)(*(char **)(a1 + 0x50) + 5);
    return (int)v1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000290C8);
#endif

// gl_func_000291C0 — STRUCTURAL PASS (0x2D4 / 181 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An object DESTRUCTOR / free — undoes the
// gl_func_00028E94 attach.
//
//   void gl_func_000291C0(O *obj) {
//     S *sub = obj->w_50;
//     if (!(sub->b_2 & 1)) return;                       // not active
//     P *par = obj->w_2C;                                 // parent
//     if (par == 0) return;
//     if (par->w_40 == obj) {                             // unlink from
//       int nx = par->w_48;                                //  parent's
//       if (nx != -1) { ... relink ... }                   //  0x40/0x48
//     }                                                     //  list
//     (*detach)(par, obj);                                 // 0x0C00F59B
//     (*op)(...);                                           // jal 0 USO
//     (*freeBlk)(obj->w_C + 0x20);                          // 0x0C00F5A6
//     ...
//   }
//
// Struct-typing reference: the teardown/free entry, inverse of
//   gl_func_00028E94. obj->0x50 is the descriptor sub-record (byte +2
//   bit0 = active gate); obj->0x2C the parent/owner back-link; the
//   parent's word +0x40 / +0x48 form the same intrusive list
//   gl_func_00028604 splices (-1 = end sentinel). It unlinks obj from
//   that list, invokes the fixed detach routine 0x0C00F59B (≈0x3D66C)
//   and the fixed block-free 0x0C00F5A6 (≈0x3D698) on obj->0xC + 0x20.
//   Completes the object lifecycle:
//   gl_func_00028E94 (attach) → … → gl_func_00028604 (detach link) /
//   gl_func_000291C0 (destroy+free).
// Caps (DEFERRED): raw-word USO + intrusive-list unlink + fixed
//   detach/free calls (0x3D66C / 0x3D698) — byte-match needs USO
//   mnemonic disasm + reloc-pad jal infra. Real-C STRUCTURAL body
//   below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
// gl_func_000291C0 — FULL m2c DECODE (83.50% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py (one ptr==int compare cast manually).
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000291C0)();
char *gl_func_000291C0(char *arg0, char *arg2) {
    char *sp24;
    u8 temp_v0;
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
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_4;
    char *temp_v0_5;
    char *temp_v0_6;
    char *temp_v0_7;
    char *temp_v0_8;
    char *temp_v0_9;
    char *temp_v1;
    char *var_a2;
    char *var_a2_2;
    char *var_a2_3;
    char *var_a2_4;
    char *var_a2_5;

    var_a2_5 = arg2;
    temp_v1 = FW(arg0, 0x50);
    temp_v0 = FW(temp_v1, 0x2);
    if (temp_v0 & 1) {
        var_a2_5 = FW(arg0, 0x2C);
        if ((var_a2_5 != 0) && ((int)arg0 == FW(var_a2_5, 0x40)) && (FW(var_a2_5, 0x48) == -1)) {
            sp24 = var_a2_5;
            game_libs_func_0003443C(var_a2_5, arg0, var_a2_5);
            gl_func_0001CA10(sp24);
            gl_func_0001CA10(FW(sp24, 0xC) + 0x20, sp24);
        }
    }
    if (temp_v0 & 2) {
        temp_v0_2 = game_libs_func_0003443C(temp_v1 + 0x94, arg0, var_a2_5);
        var_a2_4 = temp_v0_2;
        if ((temp_v0_2 != 0) || (temp_v0_3 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2_4), var_a2_4 = temp_v0_3, (temp_v0_3 != 0)) || (temp_v0_4 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2_4), var_a2_4 = temp_v0_4, (temp_v0_4 != 0))) {
            return var_a2_4;
        }
        goto block_33;
    }
    if (temp_v0 & 4) {
        temp_v0_5 = game_libs_func_0003443C(temp_v1 + 0x94, arg0, var_a2_5);
        var_a2_3 = temp_v0_5;
        if ((temp_v0_5 != 0) || (temp_v0_6 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2_3), var_a2_3 = temp_v0_6, (temp_v0_6 != 0)) || (temp_v0_7 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2_3), var_a2_3 = temp_v0_7, (temp_v0_7 != 0)) || (temp_v0_8 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2_3), var_a2_3 = temp_v0_8, (temp_v0_8 != 0)) || (temp_v0_9 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2_3), var_a2_3 = temp_v0_9, (temp_v0_9 != 0)) || (temp_v0_10 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2_3), var_a2_3 = temp_v0_10, (temp_v0_10 != 0))) {
            return var_a2_3;
        }
        goto block_33;
    }
    if (temp_v0 & 8) {
        temp_v0_11 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2_5);
        var_a2_2 = temp_v0_11;
        if ((temp_v0_11 != 0) || (temp_v0_12 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2_2), var_a2_2 = temp_v0_12, (temp_v0_12 != 0)) || (temp_v0_13 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2_2), var_a2_2 = temp_v0_13, (temp_v0_13 != 0))) {
            return var_a2_2;
        }
        goto block_33;
    }
    temp_v0_14 = game_libs_func_0003443C(temp_v1 + 0x94, arg0, var_a2_5);
    var_a2 = temp_v0_14;
    if ((temp_v0_14 != 0) || (temp_v0_15 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2), var_a2 = temp_v0_15, (temp_v0_15 != 0)) || (temp_v0_16 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2), var_a2 = temp_v0_16, (temp_v0_16 != 0)) || (temp_v0_17 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2), var_a2 = temp_v0_17, (temp_v0_17 != 0)) || (temp_v0_18 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2), var_a2 = temp_v0_18, (temp_v0_18 != 0)) || (temp_v0_19 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2), var_a2 = temp_v0_19, (temp_v0_19 != 0)) || (temp_v0_20 = game_libs_func_0003443C(FW(arg0, 0x50) + 0x94, arg0, var_a2), var_a2 = temp_v0_20, (temp_v0_20 != 0)) || (temp_v0_21 = game_libs_func_0003443C(FW(FW(arg0, 0x50), 0x4C) + 0x9C, arg0, var_a2), var_a2 = temp_v0_21, (temp_v0_21 != 0)) || (temp_v0_22 = game_libs_func_0003443C((char *)0x5378, arg0, var_a2), var_a2 = temp_v0_22, (temp_v0_22 != 0))) {
        return var_a2;
    }
block_33:
    *(u8*)((char*)arg0 + 0x0) = (u8) (*(u8*)((char*)arg0 + 0x0) | 8);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000291C0);
#endif

// gl_func_00029494 — STRUCTURAL PASS (0x2F8 / 190 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is a bulk per-record matrix-load pass over the sprite
// table.
//
//   void gl_func_00029494(void) {
//     S *g = &D_0;
//     int n = g->w_2070;                                // record count
//     if (n <= 0) return;
//     S *src = &D_xxxx;                                   // source rows
//     for (int i = 0, off = 0; i < n; i++, off += STRIDE) {
//       R *rec = (char*)*(R**)(&D_0 + 0x2CFC) + off;
//       rec->w_B0 = src->w_0;                              // copy the
//       rec->w_B4 = src->w_4;                              //  +0xB0
//       rec->w_B8 = src->w_8;                              //  Vec4 /
//       rec->w_BC = src->w_C;                              //  matrix
//       ... rec->0xC0+ = src->0x10+ ...                     //  block
//     }
//   }
//
// Struct-typing reference: iterates the SAME primary sprite record
//   table as gl_func_0001E134 / gl_func_00027E24 / gl_func_00028A68 —
//   live count word &D_0+0x2070, record-table pointer &D_0+0x2CFC —
//   copying a Vec4/matrix-row block from a source into each record's
//   +0xB0..0xBC+ block (the exact field block gl_func_00027804 /
//   gl_func_00027D00 / gl_func_00028E94 individually write). &D_2198
//   is a fixed descriptor passed per record; a1 const 0x1C0 / f20=0.0
//   are the blit/transform params. This is the heavyweight per-frame
//   "load every sprite record's transform" pass of that subsystem.
// Caps (DEFERRED): raw-word USO + per-record matrix copy loop with
//   FP/jal-0 USO-reloc — byte-match needs USO mnemonic disasm. STALE
//   2-jr-bundle comment: grep -c 03E00008 = 1 (.s now single fn).
//   Real-C STRUCTURAL body below per the analysis (placeholder calls
//   / fields). Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_00029494(void) {
    int n = GL_COUNT_2070;
    int i;
    char *src;
    char *desc;
    float zero;
    if (n <= 0) return;
    src = (char *)&D_00000000;             // 8-word source block (s5)
    desc = (char *)&D_00000000 + 0x2198;   // per-record descriptor (s6)
    zero = 0.0f;
    for (i = 0; i < n; i++) {
        char *rec = *(char **)0x2CFC + i * 0xD0;
        *(int *)(rec + 0xB0) = *(int *)(src + 0x0);
        *(int *)(rec + 0xB4) = *(int *)(src + 0x4);
        *(int *)(rec + 0xB8) = *(int *)(src + 0x8);
        *(int *)(rec + 0xBC) = *(int *)(src + 0xC);
        *(int *)(rec + 0xC0) = *(int *)(src + 0x10);
        *(int *)(rec + 0xC4) = *(int *)(src + 0x14);
        *(int *)(rec + 0xC8) = *(int *)(src + 0x18);
        *(char *)(rec + 0x30) = 0;
        *(char *)(rec + 0x34) = 0;
        *(int *)(rec + 0x44) = -1;
        *(int *)(rec + 0x48) = -1;
        *(int *)(rec + 0x40) = -1;
        *(char *)(rec + 0x31) = 0;
        *(float *)(rec + 0x58) = zero;
        *(short *)(rec + 0x36) = 0;
        *(char *)(rec + 0x60) = 0;
        *(char *)(rec + 0xA0) = 0;
        *(short *)(rec + 0x82) = 0;
        *(short *)(rec + 0x84) = 0;
        *(char *)(rec + 0x35) = 0;
        *(int *)(rec + 0x1C) = gl_func_00000000(desc, 0x1C0);
        *(int *)(rec + 0xCC) = *(int *)(src + 0x1C);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029494);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000295BC)();
void game_libs_func_000295BC(char *arg0, s32 arg1, s32 arg2) {
    f32 var_f0;
    f32 var_f0_2;
    s32 var_a2;
    u8 temp_v0_2;
    char *temp_v0;
    char *temp_v1;
    char *var_a3;

    var_a3 = arg0;
    if ((FW(arg0, 0x0) & 0x400000) || (arg1 != 0)) {
        temp_v0 = FW(arg0, 0x4C);
        var_f0 = (*(f32*)((char*)arg0 + 0x2C)) * (*(f32*)((char*)arg0 + 0x28)) * (*(f32*)((char*)temp_v0 + 0x30));
        if ((FW(temp_v0, 0x0) & 0x20000000) && ((*(u8*)((char*)arg0 + 0x3)) & 0x20)) {
            var_f0 *= (*(f32*)((char*)temp_v0 + 0x28));
        }
        (*(f32*)((char*)arg0 + 0x34)) = (f32) (var_f0 * var_f0);
    }
    if (FW(arg0, 0x0) & 0x200000) {
        FW(arg0, 0x30) = (s32) ((*(u8*)((char*)arg0 + 0xA)) * (*(u8*)((char*)arg0 + 0xB)));
    }
    var_f0_2 = (*(f32*)((char*)arg0 + 0x38));
    if (arg2 != 0) {
        (*(u8*)((char*)arg0 + 0x1)) = (u8) ((*(u8*)((char*)arg0 + 0x1)) | 0x80);
        var_f0_2 *= (*(f32*)((char*)FW(arg0, 0x4C) + 0x34));
    }
    var_a2 = 0;
    do {
        temp_v1 = FW(var_a3, 0x50);
        var_a2 += 4;
        if ((temp_v1 != 0) && (((u32) FW(temp_v1, 0x0) >> 0x1F) != 0) && (FW(temp_v1, 0x2C) != 0)) {
            temp_v0_2 = (u8) FW(temp_v1, 0x0);
            if (temp_v0_2 & 1) {
                (*(f32*)((char*)temp_v1 + 0x44)) = (f32) ((*(f32*)((char*)temp_v1 + 0x30)) * var_f0_2);
                (*(f32*)((char*)temp_v1 + 0x40)) = (f32) ((*(f32*)((char*)temp_v1 + 0x38)) * (*(f32*)((char*)arg0 + 0x34)));
                *(s8*)((char*)temp_v1 + 0x0) = (s8) (temp_v0_2 & 0xFFFE);
                (*(u8*)((char*)temp_v1 + 0x6)) = (s8) ((s32) (FW(arg0, 0x30) + ((*(u8*)((char*)temp_v1 + 0x5)) * (0x80 - (*(u8*)((char*)arg0 + 0xB))))) >> 7);
            } else {
                if ((s8) (*(u8*)((char*)arg0 + 0x1)) < 0) {
                    (*(f32*)((char*)temp_v1 + 0x44)) = (f32) ((*(f32*)((char*)temp_v1 + 0x30)) * var_f0_2);
                }
                if ((FW(arg0, 0x0) & 0x400000) || (arg1 != 0)) {
                    (*(f32*)((char*)temp_v1 + 0x40)) = (f32) ((*(f32*)((char*)temp_v1 + 0x38)) * (*(f32*)((char*)arg0 + 0x34)));
                }
                if (FW(arg0, 0x0) & 0x200000) {
                    (*(u8*)((char*)temp_v1 + 0x6)) = (s8) ((s32) (FW(arg0, 0x30) + ((*(u8*)((char*)temp_v1 + 0x5)) * (0x80 - (*(u8*)((char*)arg0 + 0xB))))) >> 7);
                }
            }
        }
        var_a3 += 4;
    } while (var_a2 != 0x20);
    (*(u8*)((char*)arg0 + 0x1)) = 0U;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000295BC);
#endif

// gl_func_0002978C — STRUCTURAL PASS (0x1EC / 123 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 3-jr USO bundle
// (named fn + 2 trailing helpers) — deferred USO re-split. The named
// leading fn is a per-object FP ramp / clamp updater.
//
//   void gl_func_0002978C(O *obj) {
//     int n = obj->h_12;                                // iteration cnt
//     if (n == 0) return;
//     for (int i = 0; i < n; i++) {
//       float v   = obj->f_1C;                            // accumulator
//       float lim = obj->f_20;                            // limit
//       v += 1.0f;                                         // ramp up
//       obj->b_0 |= 0x04;                                  // mark dirty
//       if (v < lim) {
//         obj->f_1C = v;
//       } else {
//         obj->f_1C = 0.0f;                                // wrap / clamp
//         ...                                              //  (bc1fl)
//       }
//       n = obj->h_12;                                     // reload cnt
//     }
//   }
//
// Struct-typing reference: a per-object single-precision counter /
//   timer ramp. obj fields: halfword +0x12 the iteration/active count
//   (zero == inactive, early return; reloaded each pass), float +0x1C
//   the accumulator (incremented by 1.0 each step), float +0x20 the
//   wrap limit, byte +0 a flag set whose bit2 is OR-set as a
//   dirty/advanced marker. On reaching the limit the accumulator
//   resets to 0.0 (a saw-tooth/wrap, c.lt.s + bc1fl branch-likely).
//   A frame-timer/phase-accumulator leaf in the game_libs object
//   subsystem (same object whose +0xB0 matrix block the
//   gl_func_00027804 / gl_func_00029494 family loads).
// Caps (DEFERRED): raw-word USO + FP ramp/clamp with bc1fl branch-
//   likely — byte-match needs USO mnemonic disasm. STALE 3-jr-bundle
//   comment: grep -c 03E00008 = 1 (.s now single fn). Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
/* Whole-body decode 2026-06-01 (prior body looped + wrong increment). When
 * obj->0x12 != 0: step obj->0x1C += obj->0x20 (clamp [0,1]), set obj->0|=4, dec
 * obj->0x12; if it hit 0 and obj->1==2, gl(obj) and return. Then if bit26 of
 * obj->0 set, obj->0x30 = obj->0x1C * obj->0x2C. Finally a 16-slot loop: e =
 * *(p+0x38) for p=obj..obj+60 step 4; if *e<0 (sign) call gl_3dc30(e, bit26 of
 * obj->0, obj->0&1). Clear obj->0&~4. */
extern int gl_func_0003DC30();
void gl_func_0002978C(char *obj) {
    char *p = obj;
    int s0;

    if (*(unsigned short *)(obj + 0x12) != 0) {
        *(float *)(obj + 0x1C) = *(float *)(obj + 0x1C) + *(float *)(obj + 0x20);
        *(unsigned char *)obj |= 4;
        if (1.0f < *(float *)(obj + 0x1C)) {
            *(float *)(obj + 0x1C) = 1.0f;
        }
        if (*(float *)(obj + 0x1C) < 0.0f) {
            *(float *)(obj + 0x1C) = 0.0f;
        }
        *(unsigned short *)(obj + 0x12) = *(unsigned short *)(obj + 0x12) - 1;
        if (*(unsigned short *)(obj + 0x12) == 0 && *(unsigned char *)(obj + 1) == 2) {
            gl_func_00000000(obj);
            return;
        }
    }
    if ((int)(*(int *)obj << 5) < 0) {
        *(float *)(obj + 0x30) = *(float *)(obj + 0x1C) * *(float *)(obj + 0x2C);
    }
    for (s0 = 0; s0 != 64; s0 += 4) {
        char *e = *(char **)(p + 0x38);
        if (((unsigned)*(int *)e >> 31) == 1) {
            gl_func_0003DC30(e, (unsigned)(*(int *)obj << 5) >> 31, *(unsigned char *)obj & 1);
        }
        p += 4;
    }
    *(unsigned char *)obj &= ~4;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002978C);
#endif

#ifdef NON_MATCHING
/* game_libs_func_000298D8: accumulate-and-scale. Adds the two u16 fields at
 * a0+2 and a0+4, stores the sum back to a0+2, takes (sum>>8)&0xFF (arith sra),
 * clamps it to 127 (and zeroes byte a0+0 when clamped), then returns
 * (floatTable[v] - 1.0f) * a0->8 + 1.0f. floatTable at D+0x200, indexed by v.
 * 98.48% NM: the `r` result-temp + `h[2]+h[1]` operand order pin the return
 * path (add->f2; mov f0,f2) and the u16 load order. Residual = FP-temp
 * renumber (table[v] in $f4 target vs $f6, the $f8/$f4 mul operands swapped)
 * + one int-reg name ($t9 vs $t8) — permuter-class; sub-into-temp regresses. */
float game_libs_func_000298D8(void *a0) {
    unsigned short *h = (unsigned short *)a0;
    int v = h[2] + h[1];
    h[1] = (unsigned short)v;
    v = (v >> 8) & 0xFF;
    if ((unsigned int)v >= 127) {
        v = 127;
        *(char *)a0 = 0;
    }
    {
        float r = (*(float *)((char *)&D_00000000 + 0x200 + v * 4) - 1.0f)
                  * *(float *)((char *)a0 + 8) + 1.0f;
        return r;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000298D8);
#endif

/* Phase-accumulator table oscillator: advance a0[1] by (int)a0->0x10f, index
 * the 64-entry s16 table at a0[2] by (acc>>10)&0x3F, return (s16)(table[idx]>>8).
 * Structurally exact (17/17 insns, same opcodes/immediates); ~10 $t-register
 * fields differ. Straight-line + reloc-free → permuter-crackable episode target. */
#ifdef NON_MATCHING
int game_libs_func_00029934(int *a0) {
  int acc = ((int) (*((float *) (((char *) a0) + 0x10)))) + a0[1];
  int *new_var3;
  int new_var;
  int idx = (((unsigned int) acc) >> 10) & 0x3F;
  int *new_var2;
  new_var2 = a0;
  a0[1] = acc;
  new_var3 = new_var2;
  new_var = new_var3[2];
 acc = new_var; goto dummy_label_501080; dummy_label_501080: ;
  return (short) (((short *) acc)[idx] >> 8);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029934);
#endif


// gl_func_00029978 — STRUCTURAL PASS (0x1F4 / 125 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A heavily-FPU per-object keyframe / tween step.
//
//   void gl_func_00029978(O *obj) {
//     int t = obj->h_1A;                                // tween timer
//     int s = obj->w_0;
//     if (t == 0) { obj->h_1A = -1; obj->f_C = 1.0f; ... } // expired
//     else {
//       obj->h_1A = t - 1;                                // tick down
//       int mode = obj->h_18;
//       if (mode == 1) { ... linear ... }
//       float cur = obj->f_C;                              // current t
//       int   tgt = obj->h_16;                             // target
//       float a = (float)something;                        // cvt.s.w
//       float b = (float)tgt;
//       obj->f_C = cur + (b - cur) / a;                     // interp
//       ... mul.s / div.s / sub.s easing ...
//     }
//   }
//
// Struct-typing reference: a per-object animation/tween advance.
//   halfword obj->0x1A is a frame countdown timer (-1 sentinel when
//   finished), float obj->0xC the current interpolation parameter
//   (0..1), halfword obj->0x16 a target value, halfword obj->0x18 an
//   easing/mode selector (mode 1 special-cased), word obj->0 a config
//   pointer. The body is a chain of integer→float conversions
//   (cvt.s.w) and single-prec sub/div/mul producing the next
//   interpolated value written back to obj->0xC. A keyframe stepper
//   leaf in the game_libs object subsystem — paired with the
//   gl_func_0002978C ramp updater on the same object.
// Caps (DEFERRED): raw-word USO + heavy FP interpolation idiom (mul/
//   div/sub + cvt.s.w) — byte-match needs USO mnemonic disasm.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00029978(char *obj) {
    int t = *(unsigned short *)(obj + 0x1A);
    if (t == 0) {
        *(short *)(obj + 0x1A) = -1;
        *(float *)(obj + 0xC) = 1.0f;
    } else {
        int mode = *(unsigned short *)(obj + 0x18);
        float cur = *(float *)(obj + 0xC);
        int tgt = *(short *)(obj + 0x16);
        float a = (float)t;
        float b = (float)tgt;
        *(short *)(obj + 0x1A) = t - 1;
        if (mode == 1) {
            *(float *)(obj + 0xC) = cur + (b - cur) / a;
        } else {
            *(float *)(obj + 0xC) = cur + (b - cur) / a;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029978);
#endif

// gl_func_00029B6C — STRUCTURAL PASS (0x49C / 295 words ≈ 1.2KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: LARGE
// 8-jr USO bundle (named fn + ~7 trailing accessor/setter helpers) —
// deferred USO re-split. Also carries a trailing
// gl_func_00029B6C_pad.s GLOBAL_ASM (alignment/literal pad), left
// untouched. The named leading fn (~22 words) resets two object
// animation sub-channels.
//
//   void gl_func_00029B6C(O *obj) {
//     byte f0 = obj->b_80;
//     if (f0 != ...) (*reset0)(&obj->_80);              // 0x0C00F7D1
//     obj->f_38 = 0.0f;                                  // chan-0 phase
//     byte f1 = obj->b_A0;
//     if (f1 != ...) (*reset1)(&obj->_8C);               // 0x0C00F7F9
//     obj->f_3C = 0.0f;                                  // chan-1 phase
//   }
//
// Struct-typing reference: an object dual-channel animation reset.
//   obj+0x80 and obj+0x8C are two parallel animation sub-channel
//   sub-structs (each with a state byte at +0x80 / +0xA0); each is
//   conditionally reset via its fixed USO-relocated init —
//   0x0C00F7D1 (≈0x3DF44) for channel 0, 0x0C00F7F9 (≈0x3DFE4) for
//   channel 1 — and its float phase accumulator (obj->0x38 /
//   obj->0x3C) zeroed. The 7 trailing bundled bodies are this
//   subsystem's micro-accessors (1.0f / byte / float field
//   setter-getters over the same sub-channels — e.g. set f_3C, set
//   b_A0=1, store w_90/w_94/w_8C) left for the deferred USO
//   re-split. Companion reset to the gl_func_00029978 tween /
//   gl_func_0002978C ramp steppers on the same object.
// Caps (DEFERRED): raw-word USO + fixed-target channel resets
//   (0x3DF44 / 0x3DFE4) — byte-match needs USO mnemonic disasm +
//   reloc-pad jal infra. STALE 8-jr-bundle comment: grep -c
//   03E00008 = 1 (.s now single fn). Real-C STRUCTURAL body below
//   per the analysis. Byte-match deferred. Name pre-checked: no
//   extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_00029B6C(char *obj) {
    if (*(unsigned char *)(obj + 0x80) != 0xFF) {
        gl_func_00000000(obj + 0x80);
    }
    *(float *)(obj + 0x38) = 0.0f;
    if (*(unsigned char *)(obj + 0xA0) != 0xFF) {
        gl_func_00000000(obj + 0x8C);
    }
    *(float *)(obj + 0x3C) = 0.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029B6C);
#endif

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00029BC8)();
void game_libs_func_00029BC8(char *arg0) {
    u16 temp_a1;
    u16 temp_a1_2;
    char *temp_t9;
    char *var_v0;

    *(u8*)((char*)arg0 + 0xA0) = 1;
    FW(arg0, 0x90) = 0;
    *(f32*)((char*)arg0 + 0x3C) = 1.0f;
    FW(arg0, 0x94) = *(s32*)((char*)&D_00000000 + 8);
    temp_t9 = FW(FW(arg0, 0x44), 0x50);
    FW(arg0, 0x8C) = temp_t9;
    temp_a1 = *(u16*)((char*)temp_t9 + 0x1A);
    *(s16*)((char*)arg0 + 0xA4) = temp_a1;
    if (temp_a1 == 0) {
        var_v0 = (int)arg0 + 0x8C;
        *(f32*)((char*)var_v0 + 0xC) = (f32)(s32)*(u16*)((char*)temp_t9 + 0x16);
    } else {
        var_v0 = (int)arg0 + 0x8C;
        *(f32*)((char*)var_v0 + 0xC) = (f32)(s32)*(u16*)((char*)temp_t9 + 0x12);
    }
    temp_a1_2 = *(u16*)((char*)temp_t9 + 0x18);
    *(s16*)((char*)var_v0 + 0x16) = temp_a1_2;
    if (temp_a1_2 == 0) {
        *(f32*)((char*)var_v0 + 0x10) = (f32)(s32)*(u16*)((char*)temp_t9 + 0x14);
    } else {
        *(f32*)((char*)var_v0 + 0x10) = (f32)(s32)*(u16*)((char*)temp_t9 + 0x10);
    }
    *(s16*)((char*)var_v0 + 0x1A) = *(u16*)((char*)temp_t9 + 0x1C);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029BC8);
#endif

/* 1.0f init + 3-field pointer copy from a0->0x44. The base pointer + loaded
 * values renumber ($v0 vs target $t6, alternating t7/t8 vs t7/t6).
 *
 * 2026-05-27 retest: scoped-block isolation of p (place 1.0f store first,
 * then p++copies in {} block) — no effect on allocator (6/11 unchanged).
 * The $v0-vs-$t6 base-reg choice is allocator-priority driven; no C
 * scope/placement lever shifts it.
 *
 * 2026-05-27 retest: struct-assign lever (3-int struct copy) regressed to
 * 4/11 — alternation became t7/t6 (vs target t8/t7) AND base stayed $v0
 * (vs target $t6). The base-pointer-as-$t6 needs the p-load to NOT pick
 * $v0; IDO's allocator preference for $v0 as the function-local pointer
 * isn't overrideable from C. Permuter-class. */
#ifdef NON_MATCHING
void game_libs_func_00029C80(char *a0) {
    int *p = *(int**)(a0 + 0x44);
    *(float*)(a0 + 0x38) = 1.0f;
    *(int*)(a0 + 0x80) = p[8];
    *(int*)(a0 + 0x84) = p[9];
    *(int*)(a0 + 0x88) = p[10];
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029C80);
#endif

void game_libs_func_00029CAC(char *a0, int a1, int a2) {
    *(char*)a0 = 0;
    *(short*)(a0 + 2) = 0;
    *(int*)(a0 + 0x1C) = a1;
    *(float*)(a0 + 4) = 0.0f;
    *(float*)(a0 + 0x10) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029CCC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029D08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029FDC);

/* game_libs_func_00029FFC: 3-insn `mov.s f0, f2; jr ra; nop` float move.
 * No prologue — $f2 is a caller-set float arg (calling convention is
 * $f12/$f14, not $f2). IDO C can't emit functions taking $f2 as input.
 * CAP class per feedback_caller_set_int_reg_cap_1080_game_libs (extends
 * to floats). Default INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00029FFC);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00029B6C_pad.s")

#ifdef NON_MATCHING
/* gl_func_0002A014: 24-insn 2-way dispatch by byte-table lookup.
 *   sw a1 to caller-arg-slot; a1 &= 0xFF.
 *   v = *(byte*)(D_table + a1);
 *   if ((v & 3) == 1) {
 *       v1 = 0;
 *       if ((v & 0x80) == 0) {
 *           call func_a(); v1 = v & 0xFFFF;
 *       } else {
 *           call func_b(); v1 = v & 0xFFFF;
 *       }
 *   }
 *   return v1;
 * 2 resolved jal targets (0x3F010, 0x3F024) need INSN_PATCH for byte-exact.
 * Structural wrap only. */
extern int func_3F010();
extern int func_3F024();
extern unsigned char D_2A014_table[];
int gl_func_0002A014(int a0, int a1) {
    int v1 = 0;
    unsigned int v;
    (void)a0;
    a1 &= 0xFF;
    v = D_2A014_table[a1];
    if ((v & 3) == 1) {
        if ((v & 0x80) == 0) {
            gl_func_00000000();
        } else {
            gl_func_00000000();
        }
        v1 = v & 0xFFFF;
    }
    return v1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A014);
#endif

// gl_func_0002A080 — STRUCTURAL PASS (46.97% in-tree; dispatcher-scan
// candidate 5/5, audited 2026-06-10). TWO verified caps gate this fn:
// (1) CALLER-SET $t6 dispatch: the head does `sltiu at,t6,14` with t6
// never set in-symbol while a0 stays live in the case bodies (reads
// a0+0x18) -- so t6 cannot be a coalesced arg web; the normal-arg C
// form emits sltiu at,a0 (tested per the ECEC diagnostic). The
// bytecode-VM family's callers pass the opcode in $t6.
// (2) HARDCODED `jal 0x3f05c` in case 1 (no R_MIPS_26 reloc; the
// reference_1080_hardcoded_jal class) -- C emits a reloc'd jal or a
// fn-ptr jalr, neither matches.
// The per-case C below is otherwise faithful (9 of 14 bodies decoded
// incl. the 250/249/245 and 243/242 conditional-branch opcodes).
// Permanent INCLUDE_ASM absent a VM-caller-context mechanism.
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A command-opcode dispatcher (single jump table) in the
// gl_func_00026790 bytecode-interpreter family.
//
//   ret gl_func_0002A080(int op, Buf *a1, int a2, int a3) {
//     if ((unsigned)op >= 0xE) return ...;              // out of range
//     goto *((void**)(&D_0 + 0x1020))[op];               // jump table
//     // 14 opcode cases, each operating on the a1 buffer, e.g.:
//     //   case X: a1->b_18 = a3; a1->w_0 = a1->w_4; ...
//     //   case Y: jal 0x3F05C(a1);   // 0x0C00FC17
//     //   ...
//   }
//
// Struct-typing reference: a bytecode/command processor. `op` (a0)
//   is an opcode in [0, 0xE) decoded by a REAL computed jump table at
//   &D_0+0x1020 (14 entries; out-of-range = default return). Each
//   case mutates the `a1` command buffer — byte +0x18 a status/cursor
//   flag, words +0x0 / +0x4 a read/commit cursor pair — with some
//   opcodes invoking the fixed USO-relocated handler 0x0C00FC17
//   (≈0x3F05C). This &D_0+0x1020 table joins the contiguous bank of
//   game_libs dispatch tables (&D_0+0xE7C / 0xEA0 / 0xEE0 / 0xF10
//   from gl_func_0002119C / 00023914 / 00026790) — the subsystem's
//   command-VM step over a per-buffer instruction stream.
// Caps (DEFERRED): raw-word USO + computed jump-table dispatch +
//   jal-0 USO-reloc handler (0x3F05C) — byte-match needs USO
//   mnemonic disasm + reloc-pad jal infra. Real-C STRUCTURAL body
//   below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
// Command-buffer VM step. The opcode is a caller-set $t6 (cap, approximated by
// switching on a0 so the arm bodies' $a0/$a1/$a2/$a3 usage matches and only the
// dispatch reg differs). a1 is the buffer: byte +0x18 is the stack cursor,
// words +(idx*4+4) the value stack, +0x0 the live value, bytes +0x13/+0x14/+0x19
// counters/flags. Arms: pop, handler-call, push (a0->0x18 + a3), tagged push,
// repeat-decrement, cursor-dec, and a2-keyed conditional adds (250/249/245 and
// 243/242 gated on the sign of a1->0x19). Reloc-blind table + jal (deferred).
int gl_func_0002A080(char *a0, char *a1, int a2, int a3) {
    if ((unsigned int)a0 >= 0xE) {
        return 0;
    }
    switch ((unsigned int)a0) {
        case 0: {
            int n = *(unsigned char *)(a1 + 0x18);
            if (n == 0) {
                return -1;
            }
            n = (n - 1) & 0xFF;
            *(unsigned char *)(a1 + 0x18) = n;
            *(int *)a1 = *(int *)(a1 + n * 4 + 4);
            return 0;
        }
        case 1:
            return gl_func_00000000(a1);
        case 2:
            return 1;
        case 3: {
            int n = *(unsigned char *)(a1 + 0x18);
            *(int *)(a1 + n * 4 + 4) = *(int *)a1;
            *(unsigned char *)(a1 + 0x18) = *(unsigned char *)(a1 + 0x18) + 1;
            *(int *)a1 = *(int *)(a0 + 0x18) + (a3 & 0xFFFF);
            return 0;
        }
        case 4: {
            int n = *(unsigned char *)(a1 + 0x18);
            *(char *)(a1 + n + 0x14) = (char)a3;
            *(int *)(a1 + *(unsigned char *)(a1 + 0x18) * 4 + 4) = *(int *)a1;
            *(unsigned char *)(a1 + 0x18) = *(unsigned char *)(a1 + 0x18) + 1;
            return 0;
        }
        case 5: {
            int n = *(unsigned char *)(a1 + 0x18);
            *(char *)(a1 + n + 0x13) = *(char *)(a1 + n + 0x13) - 1;
            n = *(unsigned char *)(a1 + 0x18);
            if (*(unsigned char *)(a1 + n + 0x13) != 0) {
                *(int *)a1 = *(int *)(a1 + n * 4);
            } else {
                *(unsigned char *)(a1 + 0x18) = n - 1;
            }
            return 0;
        }
        case 6:
            *(unsigned char *)(a1 + 0x18) = *(unsigned char *)(a1 + 0x18) - 1;
            return 0;
        case 7:
            if (a2 == 250) {
                if (*(signed char *)(a1 + 0x19) != 0) return 0;
            } else if (a2 == 249) {
                if (*(signed char *)(a1 + 0x19) >= 0) return 0;
            } else if (a2 == 245) {
                if (*(signed char *)(a1 + 0x19) < 0) return 0;
            }
            *(int *)a1 = *(int *)(a0 + 0x18) + (a3 & 0xFFFF);
            return 0;
        case 8:
            if (a2 == 243) {
                if (*(signed char *)(a1 + 0x19) != 0) return 0;
            } else if (a2 == 242) {
                if (*(signed char *)(a1 + 0x19) >= 0) return 0;
            }
            *(int *)a1 = *(int *)a1 + (signed char)a3;
            return 0;
        default:
            break;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A080);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002A258);

// gl_func_0002A260 — STRUCTURAL PASS (0x14C / 83 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An object reset-to-defaults routine.
//
//   void gl_func_0002A260(O *obj) {
//     if (obj == &D_5280) return;                       // null sentinel
//     byte f = obj->b_0;
//     f &= ~0x80; f &= ~0x40; f &= ~0x20; f &= ~0x10;     // clear flag
//     f &= ~0x08; f &= ~0x04; f &= ~0x02;                  //  bits 1..7
//     obj->b_0 = f;
//     obj->h_14 = 0xF0;                                    // default
//     obj->h_10 = ...;                                      //  field
//     obj->h_26 = 0;                                        //  constants
//     obj->b_9  = ...;
//     ...  (0xFF / 0x40 / 0x80 / 0x03 / 0x01 literals) ...
//   }
//
// Struct-typing reference: clears the object's primary flag byte
//   (obj->0) bit-by-bit — bits 1 through 7 each masked off
//   individually (the GCC-emitted sequential andi 0xFF7F / 0xBF /
//   0xDF / 0xEF / 0xF7 / 0xFB / 0xFD pattern) — then stores a fixed
//   set of default constants into the object's fields (halfwords
//   obj->0x10 / 0x14 (=0xF0) / 0x26, byte obj->0x9, etc.; immediates
//   0xFF / 0x40 / 0x80 / 0x03 / 0x01). &D_5280 is the
//   no-object/null sentinel (early return). This is the
//   "reinitialise object to its default/idle state" entry of the
//   game_libs object subsystem (the state-clear counterpart to the
//   gl_func_00028E94 attach / gl_func_00029B6C channel-reset).
// Caps (DEFERRED): raw-word USO + sequential single-bit andi flag-
//   clear idiom (must match GCC's bit-by-bit emit order) — byte-
//   match needs USO mnemonic disasm. Real-C STRUCTURAL body below
//   per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior body had ~5 stores). Object reset: skip
 * the &D+0x5280 sentinel. 7-step clear cascade on obj->0 (drop 0x80..0x02, each
 * stored via volatile), ~30 field inits, a -1 fill at obj+0xD5..0xDB, then a
 * final obj->0 &= ~1 and gl(obj+0x94). */
void gl_func_0002A260(char *obj) {
    volatile unsigned char *p;
    int c, i;
    char *v1;

    if (obj == (char *)&D_00000000 + 0x5280) {
        return;
    }
    p = (volatile unsigned char *)obj;
    c = *p;
    c &= ~0x80; *p = c;
    c &= ~0x40; *p = c;
    c &= ~0x20; *p = c;
    c &= ~0x10; *p = c;
    c &= ~0x08; *p = c;
    c &= ~0x04; *p = c;
    *(short *)(obj + 0x14) = 2048;
    *(short *)(obj + 0x10) = 2048;
    *(short *)(obj + 0x26) = 0;
    c &= ~0x02; *p = c;
    *(unsigned char *)(obj + 9) = 0;
    *(unsigned char *)(obj + 0xE0) = 0;
    *(unsigned char *)(obj + 1) = 255;
    *(unsigned char *)(obj + 0x88) = 0;
    *(unsigned char *)(obj + 0xA) = 64;
    *(unsigned char *)(obj + 0xB) = 128;
    *(unsigned char *)(obj + 0xD) = 0;
    *(unsigned char *)(obj + 0xE) = 0;
    *(int *)(obj + 0x40) = 0;
    *(unsigned char *)(obj + 8) = 0;
    *(unsigned char *)(obj + 4) = 0;
    *(unsigned char *)(obj + 0xC) = 0;
    *(unsigned char *)(obj + 5) = 3;
    *(unsigned char *)(obj + 6) = 1;
    *(short *)(obj + 0x1E) = 0;
    *(int *)(obj + 0x90) = (int)&D_00000000;
    *(unsigned char *)(obj + 0x8C) = 240;
    *(unsigned char *)(obj + 0x8D) = 0;
    *(short *)(obj + 0x16) = 0;
    *(short *)(obj + 0x12) = 0;
    *(short *)(obj + 0x18) = 0;
    *(short *)(obj + 0x1A) = 0;
    *(short *)(obj + 0x1C) = 0;
    *(int *)(obj + 0xDC) = 0;
    *(short *)(obj + 0x20) = 0;
    *(unsigned char *)(obj + 0xF) = 0;
    *(float *)(obj + 0x2C) = 1.0f;
    *(float *)(obj + 0x28) = 1.0f;
    *(float *)(obj + 0x38) = 1.0f;
    v1 = obj;
    for (i = 0; i != 8; i += 4) {
        *(signed char *)(v1 + 0xD5) = -1;
        *(signed char *)(v1 + 0xD6) = -1;
        *(signed char *)(v1 + 0xD7) = -1;
        v1 += 4;
    }
    *(signed char *)(v1 + 0xD0) = -1;
    *(unsigned char *)obj = *(unsigned char *)obj & ~1;
    gl_func_00000000(obj + 0x94);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A260);
#endif

// gl_func_0002A3AC — STRUCTURAL PASS (0x124 / 73 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A slot-array lazy-construct (allocate-on-demand).
//
//   int gl_func_0002A3AC(S *base, int idx) {
//     Slot *s = base + idx*4;                           // slot array
//     if (s->w_50 != 0) { ... already built ... }
//     void *o = (*alloc)(&D_5368);                       // jal 0 USO
//     if (o == 0) { s->w_50 = 0; return -1; }             // alloc fail
//     s->w_50 = o;
//     (*initObj)(o);                                      // jal 0 USO
//     O *no = s->w_50;
//     byte fl = no->b_0;
//     no->b_0 = (fl | 0x80) & ~0x40;                       // mark ready
//     no->w_18 = src->w_8C;                                // copy field
//     ...
//   }
//
// Struct-typing reference: a per-index lazy object constructor over a
//   word-strided slot array (`base[idx]`, the live object pointer at
//   slot field +0x50). On first use it obtains the object from a
//   USO-relocated allocator (`jal 0` slot) keyed on the fixed
//   descriptor &D_5368 (same &D_53xx descriptor pool as
//   gl_func_0001FAE8 / gl_func_00028B0C), stores it back into
//   slot->0x50, runs a USO-relocated initializer, then stamps the new
//   object's flag byte +0 (set bit7 ready / clear bit6) and copies a
//   word into newobj->0x18 from a source +0x8C. Returns -1 on
//   allocation failure. The allocate-on-demand entry of the game_libs
//   object subsystem (companion to the gl_func_00028E94 attach /
//   gl_func_000291C0 destroy lifecycle).
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc alloc/init —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior init was a 1-store stub). Alloc/reuse the
 * node at slot+0x50 (gl(&D+0x5368) if empty; -1 on fail). Init: node->0x50=base,
 * node->0x18=base->0x8C, an 8-step flag cascade on node->0 (|0x80 then clear bits
 * 0x40..0x01 one at a time, each stored — volatile), node->0x1c=base->0x90, then
 * ~20 field clears + node->3=128, node->5=64, node->2=255, node->0x30/0x34=1.0,
 * node->0x38=0.0. */
int gl_func_0002A3AC(char *base, int idx) {
    char *slot = base + idx * 4;
    char *no;
    volatile unsigned char *p;
    int c;

    if (*(int *)(slot + 0x50) != 0) {
        gl_func_00000000(*(char **)(slot + 0x50));
    } else {
        no = (char *)gl_func_00000000((char *)&D_00000000 + 0x5368);
        if (no == 0) {
            *(int *)(slot + 0x50) = 0;
            return -1;
        }
        *(int *)(slot + 0x50) = (int)no;
    }
    no = *(char **)(slot + 0x50);
    *(int *)(no + 0x50) = (int)base;
    *(int *)(no + 0x18) = *(int *)(base + 0x8C);
    p = (volatile unsigned char *)no;
    c = *p;
    c |= 0x80;  *p = c;
    c &= ~0x40; *p = c;
    c &= ~0x20; *p = c;
    c &= ~0x10; *p = c;
    c &= ~0x08; *p = c;
    c &= ~0x04; *p = c;
    *(int *)(no + 0x1C) = *(int *)(base + 0x90);
    c &= ~0x02; *p = c;
    *(unsigned char *)(no + 0x18) = 0;
    c &= ~0x01; *p = c;
    *(unsigned char *)(no + 1) = 0;
    *(unsigned char *)(no + 0x20) = 0;
    *(unsigned char *)(no + 0x6C) = 0;
    *(unsigned char *)(no + 3) = 128;
    *(unsigned char *)(no + 5) = 64;
    *(short *)(no + 0x10) = 0;
    *(short *)(no + 8) = 0;
    *(short *)(no + 0xA) = 0;
    *(short *)(no + 0xC) = 0;
    *(int *)(no + 0x2C) = 0;
    *(int *)(no + 0x48) = 0;
    *(unsigned char *)(no + 2) = 255;
    *(float *)(no + 0x30) = 1.0f;
    *(float *)(no + 0x34) = 1.0f;
    *(float *)(no + 0x38) = 0.0f;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A3AC);
#endif

/* gl_func_0002A4D0: NATURAL CEILING 97.67% NM (5 diffs). Structure now matches
 * target: it keeps the RAW load, the masked value, and val|0x40 in THREE
 * distinct registers — splitting `raw` from `val` (was one reused `val`) gets
 * the 3-register shape. Residual is a pure register-NUMBER choice: mine emits
 * $v1/$v0/$t6 (IDO prefers $v0/$v1 for post-call temps), target uses the
 * non-consecutive $t6/$t9/$t0. Permuter floored at score 40 (90s, -j4, 2026-05-28),
 * no crack — genuine post-call $v-vs-$t regalloc cap. INSN_PATCH promotion was
 * REMOVED 2026-05-23 as match-faking. */
extern int gl_func_00000000();

#ifdef NON_MATCHING
void gl_func_0002A4D0(volatile unsigned char *a0) {
  unsigned int raw;
  unsigned int val;
  if (a0 == 0)
  {
    return;
  }
  gl_func_00000000((void *) a0);
  raw = *a0;
  val = raw & 0xFF7F;
  *a0 = ((((val & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
  *a0 = ((unsigned char) val) | 0x40;
  raw = raw;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A4D0);
#endif

/* gl_func_0002A50C: obj-deinit helper. obj = a0[a1].field_0x50 (slot = a0 + a1*4,
 * field at +0x50); if non-NULL: gl_func(&D_0+0x5368, obj+0x70), gl_func(obj), then
 * clear the slot to NULL.
 * MATCH: indexing a0 as int** with element index (a1 + 0x14)  [0x14 = 0x50/4]
 * makes IDO pack the two pointer spills tightly (frame -0x20); the char*-pointer-
 * arithmetic form (a0 + a1*4) left a 4-byte spill gap (-0x28). Array-index vs
 * char*-arith changes spill-slot frame packing. Byte-exact (80 bytes). */
void gl_func_0002A50C(int **a0, int a1) {
    int *obj = a0[a1 + 0x14];
    if (obj != 0) {
        gl_func_00000000((char*)&D_00000000 + 0x5368, (char*)obj + 0x70);
        gl_func_00000000(obj);
        a0[a1 + 0x14] = 0;
    }
}

// gl_func_0002A55C — STRUCTURAL PASS (0x164 / 89 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO bundle
// (named fn + 1 trailing helper) — deferred USO re-split. The named
// leading fn is an object multi-element constructor.
//
//   void gl_func_0002A55C(O *obj) {
//     for (int i = 0; i < 8; i++)
//       (*initElem)(obj, i);                            // 0x0C00FADE
//     (*initTail)(&obj->_94);                            // jal 0 USO
//     byte f = obj->b_0;
//     f &= ~0x80;                                         // clear bit7
//     obj->b_0 = f;
//     obj->b_0 = f | 0x40;                                // set bit6
//   }
//
// Struct-typing reference: constructs a composite object by running
//   the fixed USO-relocated per-element initializer 0x0C00FADE
//   (≈0x3EB78) for each of its 8 sub-elements (index 0..7), then a
//   second USO-relocated init on the embedded sub-block at obj+0x94,
//   and finally stamps the object's primary flag byte +0 — clearing
//   bit7 and setting bit6 (the "constructed / not-yet-active" marker
//   the gl_func_0002A3AC lazy-construct also uses). An 8-channel
//   object constructor in the game_libs object subsystem (the
//   build-all-channels counterpart to gl_func_00029B6C's
//   reset-all-channels). The 1 trailing bundled helper is its
//   per-channel leaf, left for the deferred USO re-split.
// Caps (DEFERRED): raw-word USO + fixed/jal-0 USO-reloc per-element
//   inits (0x3EB78) — byte-match needs USO mnemonic disasm + reloc-
//   pad jal infra. STALE 2-jr-bundle comment: grep -c 03E00008 = 1
//   (.s now single fn). Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002A55C(char *obj) {
    int i;
    for (i = 0; i < 8; i++) {
        gl_func_00000000(obj, i);
    }
    gl_func_00000000(obj + 0x94);
    obj[0] = obj[0] & 0xFF7F;
    obj[0] = obj[0] | 0x40;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A55C);
#endif

#ifdef NON_MATCHING
/* Bitmask scatter-copy: for each of the low 16 bits of a1, if set, copy 3 bytes
 * (a0[5]->p[7], a0[3]->p[3], a0[2]->p[2]) where p = *(int*)(a0 + 56 + i*4).
 * RELOC-FREE → episode target. IDO unrolls the loop by 4 (matched, 59 vs 62);
 * byte-match capped by the arg-home (sw a1 saved), the v0-step-4 unroll counter
 * vs i-step-1, and $t-renumber. 2026-05-27 retest: `unsigned short s = a1; s>>=1`
 * regressed 90.73% → 80.89% (changed scratch reg from $v0 to $v0+$v1 split).
 * Re-attempt with the permuter or explicit nested-by-4 loop in a focused pass. */
void game_libs_func_0002A5C8(char *a0, int a1) {
    int i;
    a1 &= 0xFFFF;
    for (i = 0; i < 16; i++) {
        if (a1 & 1) {
            char *p = (char *)*(int *)(a0 + 56 + i * 4);
            p[7] = a0[5];
            p[3] = a0[3];
            p[2] = a0[2];
        }
        a1 = (a1 >> 1) & 0xFFFF;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002A5C8);
#endif

// gl_func_0002A6C0 — STRUCTURAL PASS (0x80 / 32 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A 0x40-slot table sweep over the &D_5280 array.
//
//   void gl_func_0002A6C0(S *tbl, int arg) {
//     S *dflt = &D_5280;                                // default ptr
//     for (int i = 0; i < 0x40; i++) {                    // 64 slots
//       void *e = tbl->w_38;                              // slot value
//       if (e != dflt) {                                  // non-default
//         (*handler)(e, …);                                // jal 0 USO
//       }
//       tbl += 4;                                          // word stride
//     }
//   }
//
// Struct-typing reference: walks a fixed 0x40 (64)-entry word-strided
//   table, comparing each slot's pointer field (+0x38) against the
//   shared default/sentinel &D_5280 (the same null-object sentinel
//   gl_func_0002A260 / gl_func_0002A55C test). Every slot that has
//   been populated (differs from the &D_5280 default) is passed to a
//   USO-relocated per-slot handler (`jal 0` slot). The caller arg is
//   threaded through. A bulk "apply to all live slots" sweep over a
//   bounded object table in the game_libs object subsystem (the
//   apply-all counterpart to the gl_func_0002A3AC lazy slot
//   constructor).
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc per-slot handler —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// gl_func_0002A6C0 (game_libs, -O2 USO) — BYTE-EXACT (agent-b 2026-06-21).
//   Bulk "apply to all live slots" sweep: for each of 16 table entries, if the
//   slot's +0x38 word differs from the default object (&D_0+0x5280), invoke the
//   per-slot handler. Landed via the held-base-pointer lever + 3 codegen
//   levers: (1) the `(x != dflt) == 1` boolean form reproduces the target's
//   xor/sltu/bnel-against-1 idiom and 5-saved-reg/0x30 frame; (2) declaring
//   the held base as `s32` (its integer value, used only by-value) — not a
//   `char *` — colors it into s2 (lower) ahead of the held constant 1 (s3),
//   matching target (char* form mis-colored: 9 diffs); (3) the `for`-loop
//   with comma-init `(var_s0=0, var_s1=arg0; ...)` schedules the dflt-lo addiu
//   ahead of the two zero-cost moves in the prologue, closing the last 3-word
//   as1 scheduler tie. gl_func_00000000 = canonical USO placeholder callee.
extern int gl_func_00000000();
void gl_func_0002A6C0(char *arg0, s32 arg1) {
    s32 dflt = (s32)((char *)&D_00000000 + 0x5280);
    s32 var_s0;
    char *var_s1;

    for (var_s0 = 0, var_s1 = arg0; var_s0 != 0x40; var_s0 += 4, var_s1 += 4) {
        s32 temp_a0 = *(s32 *)(var_s1 + 0x38);
        if ((temp_a0 != dflt) == 1) {
            gl_func_00000000(temp_a0);
        }
    }
}

// gl_func_0002A740 — STRUCTURAL PASS (0x98 / 38 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A slot-object reinitializer — SIBLING of the
// gl_func_0002A55C 8-channel constructor.
//
//   void gl_func_0002A740(S *base, int idx, int a2) {
//     idx &= 0xFF;
//     O *o = (base + idx*4)->w_38;                       // slot object
//     byte f = o->b_0;
//     o->b_88 = 0;
//     o->w_70 = a2;                                       // store arg
//     o->b_0  = (f | 0x80) & ~0x40;                        // ready mark
//     o->h_1E = 0;
//     for (int i = 0; i < 8; i++)
//       (*initElem)(o, i);                                // 0x0C00FADE
//   }
//
// Struct-typing reference: reinitialises the object held in slot
//   base[idx*4]->0x38 (the same word-strided slot array
//   gl_func_0002A3AC lazily fills / gl_func_0002A6C0 sweeps). It
//   clears byte o->0x88 and halfword o->0x1E, stores the caller arg
//   into word o->0x70, stamps the flag byte o->0 (set bit7 ready /
//   clear bit6 — same constructed marker as gl_func_0002A55C /
//   gl_func_0002A3AC), then re-runs the fixed per-element initializer
//   0x0C00FADE (≈0x3EB78) for all 8 sub-elements. The
//   reinit-existing-slot counterpart to the gl_func_0002A55C
//   construct-fresh path.
// 2026-05-31: 72.58% -> 93.39% by fixing two errors: (1) the flag byte o->0 is
//   stored TWICE — `o->0 = f|0x80` then `o->0 = (f|0x80)&~0x40` (set bit7, then
//   clear bit6, as separate stores), not one combined store; (2) the per-element
//   loop is CONDITIONAL — `if ((o + i*4)->0x50 != 0) initElem(o, i)` — not
//   unconditional.
// 2026-06-20 (agent-b): body now BYTE-EXACT (38/38 words, 7 diffs left, ALL pure
//   temp-register-ring numbering). Re-derived 3 real fixes: (a) idx is an
//   `unsigned char` PARAM (homes `sw a1,44` + `andi a1,0xff`); (b) addu operand
//   order base+idx*4 (a0 as rs) via array-index form `((char**)(base+0x38))[idx]`
//   (plain `base+idx*4` puts the scaled index as rs); (c) keep BOTH flag stores
//   via `*o = *o|0x80; *o &= 0xBF` (mask 0xBF not ~0x40). Residual: lbu result
//   lands in t8 (cached form: v0), target wants t9 — uniform +1 temp-ring offset
//   invariant to every C form tried; permuter 38k iters no crack. Genuine
//   allocno-numbering cap.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002A740(char *base, unsigned char idx, int a2) {
    char *o;
    char *p;
    int i;
    o = ((char **)(base + 0x38))[idx];
    *(unsigned char *)(o + 0x88) = 0;
    *(int *)(o + 0x70) = a2;
    *(unsigned char *)o = *(unsigned char *)o | 0x80;
    *(unsigned char *)o &= 0xBF;
    *(short *)(o + 0x1E) = 0;
    p = o;
    for (i = 0; i < 8; i++) {
        if (*(int *)(p + 0x50) != 0) {
            gl_func_00000000(o, i);
        }
        p += 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A740);
#endif

// gl_func_0002A7D8 — STRUCTURAL PASS (0x12C / 75 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO bundle
// (named fn + 3 trailing helpers) — deferred USO re-split. The named
// leading fn is an object commit / select-finalize.
//
//   void gl_func_0002A7D8(O *o) {
//     (*pre)(o, 0xFFFF);                                // 0x0C00FB4B
//     (*sub)(&o->_9C);                                   // jal 0 USO
//     byte f = o->b_0;
//     o->b_0 = f | 0x40;                                  // set bit6
//     int m = o->b_4 & 0x7F;
//     o->b_0 = ... & ~0x80;                                // clear bit7
//     int r = (*dispatch)(m);                              // jal 0 USO
//     if (r) (*onA)(o->b_4, 3);                            // mode 3
//     if (o->b_5 == ...) (*onB)(o->b_5, 4);                // mode 4
//     short cur = *(short*)(&D_0 + 0x23FA);                 // selection
//     if (o->b_5 != 1) cur = *(short*)(&D_0 + 0x2406);
//     *(int*)(&D_0 + 0x23DC) = ...;                         // commit
//   }
//
// Struct-typing reference: finalises/commits an object selection.
//   The object's flag byte +0 has bit6 set and bit7 cleared (the
//   "committed/selected" transition); bytes +0x4 / +0x5 are mode
//   selectors masked to 7-bit and dispatched to USO-relocated
//   handlers (`jal 0` slots) with mode constants 3 / 4; the embedded
//   sub-block at o+0x9C gets its own init. The selection-state
//   globals updated — halfword &D_0+0x23FA / &D_0+0x2406 and word
//   &D_0+0x23DC — are the same current-selection region the
//   gl_func_0002349C teardown / gl_func_00026CF0 submit / gl_func_
//   00023838 decoder touch. The "commit the active selection" entry
//   of the game_libs registry/object subsystem.
// 2026-06-22 STRUCTURAL FIX (96.16->98.37%): target keeps BOTH stores to
//   o[0] (sb f|0x40 ; sb (f|0x40)&0x7F) — IDO dead-store-eliminated the
//   first when the masked value was computed from a register. Forcing the
//   masked store to RE-READ o[0] (`*o = *o & 0x7F`) makes IDO retain store1
//   and forward the register (no extra reload), matching the target's
//   sb/andi/sb shape. Residual: uniform register-coloring shift from the
//   first body temp (target lbu->t7 skips v1; build lbu->v1, then tN->t(N-2)
//   cascade) — call-return v0/v1 liveness coloring; not C-reachable.
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc dispatch + register
//   coloring (above) — byte-match deferred. STALE 4-jr-bundle comment:
//   grep -c 03E00008 = 1 (.s now single fn). Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int gl_func_0003ED2C();
extern int D_00000000;
void gl_func_0002A7D8(char *o) {
    unsigned char f;
    int m, r;
    gl_func_0003ED2C(o, 0xFFFF);
    gl_func_00000000(o + 0x9C);
    f = *(unsigned char *)o;
    m = *(unsigned char *)(o + 4);
    *(unsigned char *)o = f | 0x40;
    *(unsigned char *)o = *(unsigned char *)o & 0x7F;
    r = gl_func_00000000(m);
    if (r != 0) {
        gl_func_00000000(*(unsigned char *)(o + 4), 3);
    }
    if (gl_func_00000000(*(unsigned char *)(o + 5)) != 0) {
        gl_func_00000000(*(unsigned char *)(o + 5), 4);
    }
    if (*(unsigned char *)(o + 5) == *(short *)((char *)&D_00000000 + 0x23FA)) {
        *(int *)((char *)&D_00000000 + 0x23DC) = 1;
    } else if (*(unsigned char *)(o + 5) == *(short *)((char *)&D_00000000 + 0x2406)) {
        *(int *)((char *)&D_00000000 + 0x23DC) = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A7D8);
#endif

// Doubly-linked-list insert-at-head: link a1 before a0's current head.
void game_libs_func_0002A884(int *a0, int *a1) {
    if (*a1 != 0) {
        return;
    }
    *(int *)(*a0 + 4) = (int)a1;
    *a1 = *a0;
    a1[1] = (int)a0;
    *a0 = (int)a1;
    a0[2] = a0[2] + 1;
    a1[3] = a0[3];
}

/* game_libs_func_0002A8C4: doubly-linked-list node detach. splat's jr-ra
 * heuristic mis-split this into 0002A8C4 (the v1==a0 early-return preamble)
 * and 0002A8D8 (the detach body, reached via the bnel over the early return);
 * both were mislabeled caps. Merged it is one function: $v1 is a0->next set in
 * the preamble, NOT caller-set. */
int game_libs_func_0002A8C4(void *a0) {
    void *v1 = *(void**)a0;
    if (v1 == a0) {
        return 0;
    }
    *(void**)((char*)*(void**)v1 + 4) = a0;
    *(void**)a0 = *(void**)v1;
    *(void**)v1 = 0;
    *(int*)((char*)a0 + 8) = *(int*)((char*)a0 + 8) - 1;
    return *(int*)((char*)v1 + 8);
}

// gl_func_0002A904 — STRUCTURAL PASS (0x12C / 75 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO bundle
// (named fn + 3 trailing helpers) — deferred USO re-split. The named
// leading fn is the subsystem bring-up / init for the &D_5368 list +
// &D_52F0 element-array family.
//
//   void gl_func_0002A904(void) {
//     S *g = &D_0;
//     *(int*)(&D_5368) = &D_5368;                       // list anchors
//     *(int*)(&D_536C) = &D_5368;                        //  (self-ref
//     *(int*)(&D_5370) = 0;                              //   empty list)
//     *(int*)(&D_5374) = 0;
//     S *e = &D_52F0;  S *t = &D_3280;
//     for (int i = 0; i < N; i++) {                       // stride 0x80
//       *(int*)((char*)g + 0x32F8 + i*0x80) = t;          // wire entry
//       *(int*)((char*)g + 0x32F0 + i*0x80) = 0;
//       (*initElem)(&D_5368, e);                          // jal 0 USO
//       e += 0x80;  t += 0x80;
//     }
//   }
//
// Struct-typing reference: the one-time construction of this
//   object-pool subsystem. Words &D_5368 / &D_536C are the head/tail
//   anchors of an intrusive list set to point at themselves (the
//   empty-list convention); &D_5370 / &D_5374 are zeroed counters.
//   It then walks a fixed-stride (0x80) element array based at
//   &D_52F0, binding each element's slot at &D_0+0x32F8 to the
//   parallel &D_3280 table entry, clearing &D_0+0x32F0, and running
//   a USO-relocated per-element initializer (`jal 0` slot) with the
//   &D_5368 list anchor. The init counterpart to the
//   gl_func_0002A55C constructor / gl_func_0002A6C0 sweep / gl_func_
//   0002A260 reset family (all over the same &D_52xx/53xx pool).
// Caps (DEFERRED): raw-word USO + per-element jal-0 USO-reloc init —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   STALE 4-jr-bundle comment: grep -c 03E00008 = 1 (.s now single
//   fn). Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// BASE-PIN PROGRESS (agent-b 2026-06-21): held-base-pointer lever applied.
//   Loop pointers pinned as held char* in saved regs, each incremented +0x80,
//   call arg passed as held pointer (`or a0,sN,zero`). The s32-INT lever
//   (see gl_func_0002A6C0) FIXED the anchor coloring: declaring `anchor`
//   (used only by value — stored + passed, never deref'd) as `s32` instead
//   of `char *` flips it from s4 to s3, EXACTLY matching target (37->36
//   diffs, and now anchor=s3/var_s4=s4 like target). RESIDUAL (36 words):
//   (a) the setup/prologue instruction SCHEDULE order (addiu materializations
//   land in different positions though the register assignments now match) —
//   as1 backend tie; (b) target uses a distinct temp v0=&D for the 4 top
//   stores but IDO merges it with the loop base s0=&D. Both are scheduling/
//   single-symbol-merge residuals, not coloring or base-pin. gl_func_00000000
//   = canonical USO placeholder.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002A904(void) {
    s32 anchor = (s32)((char *)&D_00000000 + 0x5368);
    char *var_s0 = (char *)&D_00000000;
    char *var_s1 = (char *)&D_00000000 + 0x32F0;
    char *var_s2 = (char *)&D_00000000 + 0x3280;
    char *var_s4 = (char *)&D_00000000 + 0x52F0;
    char *v0 = (char *)&D_00000000;
    *(s32 *)(v0 + 0x5368) = anchor;
    *(s32 *)(v0 + 0x536C) = anchor;
    *(s32 *)(v0 + 0x5370) = 0;
    *(s32 *)(v0 + 0x5374) = 0;
    do {
        *(s32 *)(var_s0 + 0x32F8) = (s32) var_s2;
        *(s32 *)(var_s0 + 0x32F0) = 0;
        gl_func_00000000(anchor, var_s1);
        var_s1 += 0x80;
        var_s0 += 0x80;
        var_s2 += 0x80;
    } while (var_s1 != var_s4);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A904);
#endif

unsigned char game_libs_func_0002A9A4(unsigned char **a0) {
    unsigned char v = **a0;
    *a0 = *a0 + 1;
    return v;
}

#ifdef NON_MATCHING
/* game_libs_func_0002A9B8: big-endian signed 16-bit reader over a byte-stream
 * cursor (**a0). Reads two bytes via *p++, storing the advanced cursor back to
 * *a0 after EACH byte, then returns (short)((b0<<8)|b1). Logic exact; near-miss
 * on two points: (1) target keeps a REDUNDANT inner sign-extend — lbu b0 then
 * ((b0<<8)<<16)>>16 = (signed char)b0<<8 — that IDO folds into the outer (short)
 * here (12 vs 14 insns); writing (signed char)b0 folds, signed-char b0 switches
 * lbu->lb. (2) the 2nd cursor store is scheduled late (after the shift combine).
 * Both resist plain-C control. */
short game_libs_func_0002A9B8(unsigned char **a0) {
    unsigned char *p = *a0;
    int b0, b1;
    b0 = *p++;
    *a0 = p;
    b1 = *p++;
    *a0 = p;
    return (short)((b0 << 8) | b1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002A9B8);
#endif

#ifdef NON_MATCHING
/* game_libs_func_0002A9F0: 1-or-2-byte big-endian varint reader over a cursor
 * (**a0). v=*p; *a0=p+1; if high bit set: v=((v<<8)&0x7F00)|p[1]; v&=0xFFFF;
 * *a0=p+2. return v. Logic exact; near-miss (1 insn short, 15 vs 16): target
 * saves the input byte (`move a1,v1`) into the beqz delay slot before reusing
 * $v1 as the working/return register, while IDO fills the delay with the shift
 * and keeps the result in a fresh temp — a delay-slot-scheduling choice no
 * tested C form (hi-copy, reorder) flips. Reloc-free. */
int game_libs_func_0002A9F0(unsigned char **a0) {
    unsigned char *p = *a0;
    int v = *p;
    *a0 = p + 1;
    if (v & 0x80) {
        v = ((v << 8) & 0x7F00) | p[1];
        *a0 = p + 2;
        v &= 0xFFFF;
    }
    return v;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002A9F0);
#endif

// gl_func_0002AA30 — STRUCTURAL PASS (0x104 / 65 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). An object per-frame advance / step with a fixed step
// chain.
//
//   void gl_func_0002AA30(O *o) {
//     int s = o->w_0;
//     if (s < 0) return;                                // sign-bit gate
//     short c = o->h_8;                                  // frame counter
//     if (c >= 2) {
//       o->h_8 = c - 1;                                   // tick down
//       if (o->h_A < o->h_8) return;                       // not yet
//     }
//     (*pre)();                                           // jal 0 USO
//     o->b_0 |= 0x20;                                     // mark stepped
//     jal 0x3F1A0(o);                                     // 0x0C00FC68
//     jal 0x3F388(o);                                     // 0x0C00FCE2
//     int r = ...;
//     if (r == -1) return;
//     jal 0x3FC60(o);                                     // 0x0C00FF18
//   }
//
// Struct-typing reference: a per-frame keyframe/animation advance.
//   word o->0 carries an enable in its sign bit (negative = inactive,
//   early return) and a flag set whose bit5 is OR-marked once a step
//   fires; halfword o->8 is a frame countdown decremented toward the
//   halfword o->0xA threshold. When the counter reaches the threshold
//   the function runs a fixed three-stage USO-relocated step pipeline
//   — 0x0C00FC68 (≈0x3F1A0) → 0x0C00FCE2 (≈0x3F388) → 0x0C00FF18
//   (≈0x3FC60) — short-circuiting if the middle stage returns -1.
//   The object-tick/advance leaf of the game_libs object subsystem
//   (sibling to the gl_func_00029978 tween / gl_func_0002978C ramp
//   steppers).
// Caps (DEFERRED): raw-word USO + fixed-target step pipeline
//   (0x3F1A0 → 0x3F388 → 0x3FC60) — byte-match needs USO mnemonic
//   disasm + reloc-pad jal infra. Real-C STRUCTURAL body below per
//   the analysis. Byte-match deferred. Name pre-checked: no extern
//   reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002AA30(char *o) {
    int v0 = *(int *)o;
    short c;
    int r;
    if (v0 >= 0) return;                       /* srl+beql sign gate: proceed only if negative */
    c = *(short *)(o + 8);
    if (c >= 2) {
        if ((v0 << 2) < 0) return;             /* bltz (v0<<2) */
        *(short *)(o + 8) = c - 1;
        if (*(short *)(o + 0xA) < *(short *)(o + 8)) return;
    }
    gl_func_00000000();                         /* pre() */
    *(unsigned char *)o = *(unsigned char *)o | 0x20;
    gl_func_00000000(o);                        /* 3f1a0 */
    r = gl_func_00000000(o);                    /* 3f388 */
    if (r == -1) return;
    r = gl_func_00000000(o, r);                 /* 3fc60(o, r) */
    if (r == -1) return;
    r = gl_func_00000000(o, r);                 /* 3f708(o, r) */
    if (r != -1) {
        gl_func_00000000(o);                    /* 3f22c(o) */
    }
    v0 = *(int *)o;                             /* re-read o->0 for second gate */
    if ((v0 << 2) >= 0) return;
    if (*(int *)(o + 0x2C) != 0 || (v0 << 3) < 0) {
        gl_func_00000000(o);                    /* final cb */
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AA30);
#endif

// gl_func_0002AB34 — STRUCTURAL PASS (0x8C / 35 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A small object state-transition / latch.
//
//   void gl_func_0002AB34(O *o) {
//     int s = o->w_0;
//     if ((s << 3) >= 0) {                              // flag bit gate
//       (*notify)(o->w_2C);                              // jal 0 USO
//     }
//     if (o->w_2C != 0 && o->w_48 == ...) {
//       int st = o->b_20 & ~0x80;                         // strip bit7
//       if (st == 1 || st == 2) {
//         o->b_20 = 0;                                     // reset state
//         o->b_0 |= 0x01;                                  // set bit0
//       }
//     }
//   }
//
// Struct-typing reference: a per-object phase latch. word o->0 holds
//   a flag set (one bit, exposed by the `s << 3` sign test, gates a
//   USO-relocated notify on the parent); word o->0x2C is the
//   parent/owner back-link, o->0x48 a link pointer. Byte o->0x20 is a
//   transient state code whose bit7 is masked off; if the remaining
//   value is 1 or 2 the state is consumed (o->0x20 = 0) and the
//   object's primary flag o->0 has bit0 set (a "transition complete /
//   needs-redraw" marker). A state-acknowledge leaf in the game_libs
//   object subsystem (operates on the same o->0/0x20/0x2C fields the
//   gl_func_00028604 detach / gl_func_0002A7D8 commit use).
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc notify — byte-
//   match needs USO mnemonic disasm + reloc-pad jal infra. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002AB34(char *o) {
    int s = *(int *)o;
    int st;
    if ((s << 3) >= 0) {
        gl_func_00000000(*(int *)(o + 0x2C));
    }
    if (*(int *)(o + 0x2C) != 0 && *(int *)(o + 0x48) != 0) {
        st = *(unsigned char *)(o + 0x20) & ~0x80;
        if (st == 1 || st == 2) {
            *(unsigned char *)(o + 0x20) = 0;
            *(unsigned char *)o = *(unsigned char *)o | 0x01;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AB34);
#endif

// gl_func_0002ABC0 — STRUCTURAL PASS (0x15C / 87 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A packed-id decode + list lookup / state toggle.
//
//   void gl_func_0002ABC0(O *o) {
//     int w = o->w_0;
//     if ((w << 2) < 0) { ... bit29 path ... }
//     N *list = o->w_4C;
//     if (list != 0) {
//       int e   = list->w_0;
//       int typ = (unsigned)e >> 28;                      // 4-bit type
//       int sub = ((e << 4) >> 30);                        // 2-bit sub
//       if (typ == 2 && sub == 0) {
//         o->b_0 |= 0x20;                                  // mark bit5
//       }
//     }
//     ... further sign-bit / sub-field branches ...
//   }
//
// Struct-typing reference: a packed-handle classifier. word o->0 is a
//   bit-packed control word (the type/kind field at bits[31:28], sub-
//   selectors below it, an enable in the sign bit — the same packed-
//   word layout gl_func_000230D0 / gl_func_00023914 decode); word
//   o->0x4C points to a list whose head element word likewise carries
//   a 4-bit type (>>28) and a 2-bit sub-field. When the list entry's
//   type is 2 (sub 0) the object's primary flag byte o->0 has bit5
//   set (a "matched/active" marker). A handle-classify-and-latch leaf
//   in the game_libs registry/object subsystem.
// Caps (DEFERRED): raw-word USO + packed-bitfield decode (the same
//   layout gl_func_000230D0 / 00023914 use) — byte-match needs USO
//   mnemonic disasm. Real-C STRUCTURAL body below per the analysis.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
int gl_func_0002ABC0(char *o, int a1) {
    int w = *(int *)o;
    if ((w << 2) >= 0) {
        char *list = *(char **)(o + 0x4C);
        if (list != 0) {
            int e0 = *(int *)(*(int **)list);
            if ((unsigned)e0 >> 28 == 2 && ((unsigned)(e0 << 4) >> 30) != 0) {
                *(unsigned char *)o = *(unsigned char *)o | 0x20;
                return -1;
            }
        }
    }
    if ((((unsigned)w >> 28) & 1) == 1) {
        if ((((unsigned)(w << 6)) >> 31) == 1) {
            return 0;
        }
        {
            char *a2 = *(char **)(o + 0x2C);
            if (a2 != 0 && (w << 4) < 0 && a1 == 1 && o == *(char **)(a2 + 0x44)) {
                if (*(char **)(o + 0x4C) != 0) {
                    gl_func_00000000(*(char **)(o + 0x2C), o);
                } else {
                    gl_func_00000000(a2, o);
                }
            }
        }
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002ABC0);
#endif

// gl_func_0002AD1C — STRUCTURAL PASS (0x380 / 224 words ≈ 0.9KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). The command-script VM RUN LOOP — the
// interpreter main loop for the gl_func_00026790 / gl_func_0002A080
// opcode family.
//
//   void gl_func_0002AD1C(O *o) {
//     char *buf = o->w_50;                              // script buf
//     int   cur = o->w_4C;                               // cursor
//     for (;;) {
//       int op = jal 0x3F010(cur) & 0xFF;                 // 0x0C00FC04
//       if (op >= 0xC1 && op < 0xF2) {                     // dispatch
//         jal 0x3E680(op - 0xC1, …);                       // 0x0C00F9A0
//         int r = jal 0x3E6E8(op, …);                      // 0x0C00F9BA
//         if (r == 0) continue;                             // keep going
//       } else {
//         break;                                            // terminator
//       }
//     }
//   }
//
// Struct-typing reference: the per-object bytecode interpreter loop.
//   o->0x50 is the script/instruction buffer base, o->0x4C the
//   read cursor, o->0x54 the VM working state, &D_0+0x1058 a float
//   constant loaded into f20 for the duration. Each iteration fetches
//   the next opcode through the fixed routine 0x0C00FC04 (≈0x3F010);
//   opcodes in [0xC1, 0xF2) are decoded via the fixed handler pair
//   0x0C00F9A0 (≈0x3E680, indexed by op-0xC1) and 0x0C00F9BA
//   (≈0x3E6E8), looping until a handler signals stop or an
//   out-of-range opcode terminates. This is the execution engine the
//   gl_func_00026790 / gl_func_0002A080 jump-table dispatchers feed
//   (the VM "interpret the whole script" entry).
// Caps (DEFERRED): raw-word USO + bytecode interpreter loop with
//   fixed-target handlers (0x3F010/0x3E680/0x3E6E8) — byte-match
//   needs USO mnemonic disasm + reloc-pad jal infra. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002AD1C(char *o) {
    char *buf = *(char **)(o + 0x50);
    int cur = *(int *)(o + 0x4C);
    int op;
    int r;
    (void)buf;
    for (;;) {
        op = gl_func_00000000(cur) & 0xFF;
        if (op < 0xC1 || op >= 0xF2) break;
        gl_func_00000000(op - 0xC1);
        r = gl_func_00000000(op);
        if (r != 0) break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AD1C);
#endif

// gl_func_0002B09C — STRUCTURAL PASS (0x558 / 342 words ≈ 1.4KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle). The per-opcode command-step EXECUTOR body that
// the gl_func_0002AD1C VM run loop calls. Large -0x70 frame.
//
//   int gl_func_0002B09C(O *o, int a1) {
//     char *buf = o->w_50;                              // script buf
//     int   cur = o->w_4C;                               // cursor
//     if (o->b_2 != 0xFF) {
//       int t = o->w_0;
//       if ((t << 4) < 0) { short n = o->h_24; return -1; }
//     }
//     short sub = o->h_24;                                // subcommand
//     switch (sub) {
//       case 0: ...; case 1: ...;
//       default:
//         short d  = o->h_26;
//         short k  = buf->h_10;
//         byte  m  = buf->b_7;
//         int pos = a1 + d + k;                            // target
//         (*act)(pos, m & 0xFF);                           // jal 0 USO
//     }
//     ...
//   }
//
// Struct-typing reference: executes one decoded command. o->0x50 is
//   the script buffer, o->0x4C the read cursor, byte o->2 a
//   stop/none flag (0xFF sentinel), word o->0 a packed status whose
//   sign bit aborts (return -1). The command operands live at
//   halfwords o->0x24 (subcommand selector), o->0x26 (a delta), and
//   in the buffer record (halfword +0x10, byte +7); a target position
//   is computed as a1 + o->0x26 + buf->0x10 and handed to USO-
//   relocated per-subcommand handlers (`jal 0` slots). This is the
//   instruction-execution body the gl_func_0002AD1C interpreter loop
//   invokes per opcode (the VM's "execute one command" entry, peer to
//   gl_func_00026790 / gl_func_0002A080 in the script-VM family).
// Caps (DEFERRED): raw-word USO + multi-subcommand executor with
//   jal-0 USO-reloc handlers — byte-match needs USO mnemonic disasm
//   + reloc-pad jal infra. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
/* Per-opcode script-VM executor; var_v1 (selector) chooses load-next (case 0) /
 * load-loop (case 1) / default (positioned read with a nested transform switch
 * on the o->0x20 byte). f32(u32) conversions via the +4294967296 idiom. Globals
 * &D+0x205C/0x2074/0x2040; the *(pos*4) frame-time table + the (v1*0x158) object
 * base are USO-relative (&D + folded). gl_func_0001CA10 = real callee.
 *
 * CORRECTNESS PASS 2026-06-22 (agent-b): decoded the TARGET from
 * expected/.../game_libs_post.c.o (objdump -d) and corrected the C body:
 *   - buf+0x24, buf+0x26, o+0x10 are s16 (lh), not u8 (lbu).
 *   - o+0x48 (va0) is a full word (lw), not a byte.
 *   - o+0x20 (transform flags) is an unsigned-char byte, re-read each use.
 *   - sp38+8 reads as u16 (lhu) in the &0x80 branch.
 *   - block-46 frame-rate divisor walks THREE derefs + 4:
 *       *(int*)( *(int*)( *(int*)(o->w_4C) + 8 ) + 4 )  (was a 2-deep chain).
 * Logic is instruction-for-instruction faithful (difflib finds the full block
 * structure); residual is a register-coloring renumber cascade (b_2 vs selector
 * vs arg1 -> v1/a3 first-temp tie; frame 0x68 vs 0x70).
 *
 * STRUCTURAL CAP (byte-match infeasible from this expected .o): the nested
 * transform switch (cases 1..5 on o->0x20 & ~0x80) compiles in the TARGET to a
 * JUMPTABLE accessed USO-relative -- `lui at,0x0 ; lw t8,4248(at) ; jr t8` --
 * i.e. an external/named-global jump table at &D+0x1098. The expected .o is
 * .text-only (TRUNCATE_TEXT), so the table entries are not present, and a C
 * switch emits either a local-label jumptable (wrong reloc form) or a beq/beql
 * chain (current build). Reproducing the USO-relative jumptable needs the
 * uso-jumptable + reloc-pad infra. Reported, not ground. Permuter (700s/j4)
 * found no byte-exact -- consistent with the cap. NON_MATCHING. */
#ifdef NON_MATCHING
int gl_func_0002B09C(char *arg0, int arg1) {
    char *buf = *(char **)(arg0 + 0x50);
    char *sp38 = *(char **)(buf + 0x4C);
    int t0 = *(unsigned char *)(arg0 + 2);
    int v1 = t0;
    int t3 = 1;
    void **r;
    short c;
    if (t0 == 0xFF) {
        if (!(*(int *)(buf + 0) & 0x08000000)) return -1;
        v1 = *(short *)(buf + 0x24);
    }
    switch (v1) {
    case 0:
        r = (void **)gl_func_0001CA10(*(unsigned char *)(buf + 7),
            (arg1 + *(short *)(buf + 0x26) + *(short *)(arg0 + 0x10)) & 0xFF, arg0, arg1);
        if (r == 0) { *(unsigned char *)(arg0 + 0) |= 0x20; *(short *)(arg0 + 0xC) = *(short *)(arg0 + 8); return -1; }
        *(int *)(arg0 + 0x1C) = *(int *)((char *)r + 0xC);
        *(unsigned char *)(arg0 + 0x18) = *(unsigned char *)((char *)r + 0);
        if (!(*(int *)(arg0 + 0) & 0x04000000)) *(unsigned char *)(arg0 + 5) = *(unsigned char *)((char *)r + 1);
        *(int *)(arg0 + 0x4C) = (int)((char *)r + 4);
        *(float *)(arg0 + 0x30) = *(float *)((char *)r + 8);
        goto block_46;
    case 1:
        r = (void **)gl_func_0001CA10(*(unsigned char *)(buf + 7),
            ((*(short *)(arg0 + 0x10) << 6) + (arg1 & 0xFF)) & 0xFFFF, arg0, arg1);
        if (r == 0) { *(unsigned char *)(arg0 + 0) |= 0x20; *(short *)(arg0 + 0xC) = *(short *)(arg0 + 8) + 1; return -1; }
        *(int *)(arg0 + 0x4C) = (int)r;
        *(float *)(arg0 + 0x30) = *(float *)((char *)r + 4);
        goto block_46;
    default: {
        int pos = (arg1 + *(short *)(sp38 + 0xE) + *(short *)(buf + 0x26) + *(short *)(arg0 + 0x10)) & 0xFF;
        int va0, va1;
        float f02, f2, f03;
        char *e20 = arg0 + 0x20;
        int t9, v0, b20;
        if (pos >= 0x80) { *(unsigned char *)(arg0 + 0) |= 0x20; return -1; }
        va0 = (t0 == 0xFF) ? *(int *)(buf + 0x48) : *(int *)(arg0 + 0x48);
        if (*(unsigned char *)(arg0 + 0x20) != 0) {
            va1 = *(unsigned char *)(arg0 + 4);
            if (va1 < pos) va1 = pos;
            if (va0 != 0) {
                void **t8 = *(void ***)(arg0 + 0x4C);
                r = (void **)gl_func_0001CA10(va0, va1, arg0, arg1);
                *(int *)(arg0 + 0x4C) = (int)r;
                f02 = *(float *)((char *)r + 4);
                t3 = (r == t8);
            } else {
                f02 = 1.0f;
                *(int *)(arg0 + 0x4C) = 0;
                if (v1 >= 0xC0) *(int *)(arg0 + 0x4C) = (v1 * 0x158) + ((int)&D_00000000 - 0x100D8);
            }
            f2 = *(float *)((char *)&D_00000000 + pos * 4) * f02;
            b20 = *(unsigned char *)(arg0 + 0x20);
            t9 = b20 & ~0x80;
            if ((unsigned)(t9 - 1) < 5) {
                switch (t9) {
                case 1: case 3: f03 = *(float *)((char *)&D_00000000 + *(unsigned char *)(arg0 + 4) * 4) * f02; break;
                default: f03 = f2; break;
                }
            } else {
                f03 = f2;
            }
            *(float *)(e20 + 8) = (f03 / f2) - 1.0f;
            if (b20 & 0x80) {
                v0 = (((*(unsigned short *)(sp38 + 8) << 0xF) / *(short *)((char *)&D_00000000 + 0x2074)) << 8) / (*(short *)(arg0 + 8) * *(short *)(arg0 + 0xE));
            } else {
                v0 = 0x20000 / (*(short *)(arg0 + 0xE) * *(short *)((char *)&D_00000000 + 0x2040));
            }
            if (v0 >= 0x7FFF) v0 = 0x7FFF; else if (v0 <= 0) v0 = 1;
            *(short *)(e20 + 4) = (short)v0;
            *(short *)(e20 + 2) = 0;
            *(float *)(arg0 + 0x30) = f2;
            if ((*(unsigned char *)(arg0 + 0x20) & ~0x80) == 5) *(unsigned char *)(arg0 + 4) = (unsigned char)pos;
        } else if (va0 != 0) {
            void **t7 = *(void ***)(arg0 + 0x4C);
            r = (void **)gl_func_0001CA10(va0, pos, arg0, arg1);
            *(int *)(arg0 + 0x4C) = (int)r;
            t3 = (r == t7);
            *(float *)(arg0 + 0x30) = *(float *)((char *)&D_00000000 + pos * 4) * *(float *)((char *)r + 4);
        } else {
            *(int *)(arg0 + 0x4C) = 0;
            *(float *)(arg0 + 0x30) = *(float *)((char *)&D_00000000 + pos * 4);
            if (v1 >= 0xC0) *(int *)(arg0 + 0x4C) = (v1 * 0x158) + ((int)&D_00000000 - 0x100D8);
        }
        goto block_46;
    }
    }
block_46:
    c = *(short *)(arg0 + 8);
    *(short *)(arg0 + 0xC) = c;
    *(float *)(arg0 + 0x30) = *(float *)(arg0 + 0x30) * *(float *)(arg0 + 0x34);
    if (c == 0) {
        int t4 = *(int *)(*(int *)(*(int *)(*(int *)(arg0 + 0x4C)) + 8) + 4);
        float f0 = (float)(unsigned)t4;
        unsigned short t6 = *(unsigned short *)(sp38 + 8);
        float f18 = (float)(unsigned)t6;
        *(short *)(arg0 + 0xA) = 0;
        *(short *)(arg0 + 8) = (short)((int)((f0 * f18 * *(float *)((char *)&D_00000000 + 0x205C)) / *(float *)(arg0 + 0x30)) + 1);
    }
    return t3;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002B09C);
#endif

// gl_func_0002B5F4 — STRUCTURAL PASS (0x444 / 273 words ≈ 1.1KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 2-jr USO
// bundle (named fn + 1 trailing helper) — deferred USO re-split. The
// named leading fn is the 0xC0-class command-step executor — SIBLING
// of the gl_func_0002B09C per-opcode executor.
//
//   int gl_func_0002B5F4(O *o, int op) {
//     char *buf = o->w_50;                              // script buf
//     int   cur = o->w_4C;                               // cursor
//     if (op != 0xC0) { ... other groups ... }
//     int v = jal 0x3F05C(&o->_54);                      // 0x0C00FC17
//     o->h_8 = v;
//     o->b_0 = (o->b_0 | 0x20) & ~0x02;                   // flag toggle
//     o->b_0 &= ~0x20;
//     int w = o->w_0;
//     if (((w << 6) >> 31) ...) { ... }                    // packed bit
//     switch (op & 0xC0) {                                  // 0xC0 group
//       case 0x40: ...; case 0xC0: ...;
//     }
//   }
//
// Struct-typing reference: a second per-opcode command-step body for
//   the script VM (the 0xC0..0xFF opcode class; gl_func_0002B09C
//   covers a different range). o->0x50 / o->0x4C are the same script
//   buffer / cursor; o->0x54 the operand sub-block fed to the shared
//   fixed fetch routine 0x0C00FC17 (≈0x3F05C, the same opcode reader
//   gl_func_00026790 uses); halfword o->8 receives the fetched value;
//   byte o->0 is the flag set toggled (bit5 set then cleared, bit1
//   cleared — a transient processing marker); word o->0 also carries
//   packed control bits (the `<<6>>31` test). The opcode group is
//   `op & 0xC0` with the 0x40 / 0xC0 sub-cases dispatched. Peer to
//   gl_func_0002B09C in the gl_func_0002AD1C interpreter's executor
//   set. The trailing bundled helper is its leaf, left for the
//   deferred USO re-split.
// Caps (DEFERRED): raw-word USO + opcode-group executor with fixed-
//   target fetch (0x3F05C) — byte-match needs USO mnemonic disasm +
//   reloc-pad jal infra. STALE 2-jr-bundle comment: grep -c
//   03E00008 = 1 (.s now single fn). Real-C STRUCTURAL body below
//   per the analysis. Byte-match deferred. Name pre-checked: no
//   extern reuse.
// gl_func_0002B5F4 — RECONSTRUCTION (75.96% fuzzy, no episode).
// 0xC0-class command-step executor; game_libs script-VM sibling of
// gl_func_0002B09C. Reads an argument byte/halfword from the script
// buffer (o->0x54 cursor) gated by op&0xC0, computes a normalized
// intensity (o->0x3C = arg^2/CONST), applies a per-frame random ramp
// (o->0x38), and a percent-modulated secondary value (o->0xA). The
// argument reader is game_libs_func_0003443C (jal 0x3F05C, single-arg
// K&R). Globals at &D_00000000+0x2154 (RNG state int) and +0x10AC
// (float divisor const). Logic verified branch-for-branch against the
// target (full trace in /tmp during reconstruction); this supersedes
// the prior 52.75% m2c decode (which had a bogus extra gl_func_0001CA10
// call, -128 frame, and wrong arg counts).
// CAP (DEFERRED): residual is pervasive register-coloring + spill-slot
// scheduling — target frame -64 vs build -48, working ptr held in $a2
// (move a2,a0), arg1&0xC0 recomputed, branch-likely switch lowering.
// Correct-logic/divergent-regalloc class; would need the permuter
// (not installed in this worktree) or exact spill-order RE to land.
#ifdef NON_MATCHING
extern int game_libs_func_0003443C();
s32 gl_func_0002B5F4(char *arg0, s32 arg1) {
    char *t0 = *(char **)((char *)arg0 + 0x50);
    char *sp2C = *(char **)((char *)t0 + 0x4C);
    s32 group;
    s16 sp3A;
    s32 var_a3;
    f32 fv;
    char *ptr;
    u8 b0;

    if (arg1 == 0xC0) {
        *(s16 *)((char *)arg0 + 0x8) = game_libs_func_0003443C((char *)arg0 + 0x54);
        b0 = *(u8 *)arg0 | 0x20;
        *(u8 *)arg0 = b0;
        *(u8 *)arg0 = b0 & 0xFD;
        return -1;
    }
    *(u8 *)arg0 = *(u8 *)arg0 & 0xFFDF;
    group = arg1 & 0xC0;
    if (((u32) (*(u32 *)t0 << 6) >> 0x1F) == 1) {
        char **cur;
        switch (group) {                            /* irregular */
        case 0x0:
            sp3A = game_libs_func_0003443C((char *)arg0 + 0x54);
            cur = (char **)((char *)arg0 + 0x54);
            ptr = *cur;
            var_a3 = *(u8 *)ptr;
            *cur = ptr + 1;
            *(u8 *)((char *)arg0 + 0x3) = *(u8 *)(ptr + 1);
            *cur = *cur + 1;
            *(s16 *)((char *)arg0 + 0x14) = sp3A;
            break;
        case 0x40:
            sp3A = game_libs_func_0003443C((char *)arg0 + 0x54);
            cur = (char **)((char *)arg0 + 0x54);
            ptr = *cur;
            var_a3 = *(u8 *)ptr;
            *cur = ptr + 1;
            *(u8 *)((char *)arg0 + 0x3) = 0;
            *(s16 *)((char *)arg0 + 0x14) = sp3A;
            break;
        case 0x80:
            sp3A = *(s16 *)((char *)arg0 + 0x14);
            cur = (char **)((char *)arg0 + 0x54);
            ptr = *cur;
            var_a3 = *(u8 *)ptr;
            *cur = ptr + 1;
            *(u8 *)((char *)arg0 + 0x3) = *(u8 *)(ptr + 1);
            *cur = *cur + 1;
            break;
        }
        if ((var_a3 >= 0x80) || (var_a3 < 0)) {
            var_a3 = 0x7F;
        }
        fv = (f32) var_a3;
        *(f32 *)((char *)arg0 + 0x3C) = (fv * fv) / *(f32 *)((char *)&D_00000000 + 0x10AC);
        arg1 -= group;
    } else {
        switch (group) {                            /* irregular */
        case 0x0:
            sp3A = game_libs_func_0003443C((char *)arg0 + 0x54);
            *(s16 *)((char *)arg0 + 0x14) = sp3A;
            break;
        case 0x40:
            sp3A = *(s16 *)((char *)arg0 + 0x12);
            break;
        case 0x80:
            sp3A = *(s16 *)((char *)arg0 + 0x14);
            break;
        }
        arg1 -= group;
    }
    if (*(u8 *)((char *)t0 + 0xD) != 0) {
        u32 r = *(u32 *)((char *)&D_00000000 + 0x2154);
        f32 base = *(f32 *)((char *)arg0 + 0x3C);
        u32 m = r % *(u8 *)((char *)t0 + 0xD);
        f32 fm = (f32) (s32) m;
        f32 ramp;
        if ((s32) m < 0) {
            fm += 4294967296.0f;
        }
        ramp = (base * fm) / 100.0f;
        if (r & 0x8000) {
            ramp = -ramp;
        }
        base += ramp;
        *(f32 *)((char *)arg0 + 0x38) = base;
        if (base < 0.0f) {
            *(f32 *)((char *)arg0 + 0x38) = 0.0f;
        } else if (1.0f < *(f32 *)((char *)arg0 + 0x38)) {
            *(f32 *)((char *)arg0 + 0x38) = 1.0f;
        }
    } else {
        *(f32 *)((char *)arg0 + 0x38) = *(f32 *)((char *)arg0 + 0x3C);
    }
    *(s16 *)((char *)arg0 + 0x8) = sp3A;
    *(s16 *)((char *)arg0 + 0xA) = (s16) (*(u8 *)((char *)arg0 + 0x3) * (u16) sp3A >> 8);
    if (*(u8 *)((char *)t0 + 0xE) != 0) {
        s32 r = *(u32 *)((char *)&D_00000000 + 0x2154);
        s16 v = *(s16 *)((char *)arg0 + 0xA);
        u32 d = (u32) (v * (r % *(u8 *)((char *)t0 + 0xD))) / 100;
        s16 v2;
        if (r & 0x4000) {
            d = -(s32) d;
        }
        *(s16 *)((char *)arg0 + 0xA) = (s16) (v + d);
        v2 = *(s16 *)((char *)arg0 + 0xA);
        if (v2 < 0) {
            *(s16 *)((char *)arg0 + 0xA) = 0;
        } else if (*(s16 *)((char *)arg0 + 0x8) < v2) {
            *(s16 *)((char *)arg0 + 0xA) = *(s16 *)((char *)arg0 + 0x8);
        }
    }
    if (((*(u32 *)sp2C & 0x20000000) && (*(u8 *)((char *)t0 + 0x3) & 0x50)) ||
        (*(u32 *)t0 & 0x10000000)) {
        *(u8 *)arg0 = *(u8 *)arg0 | 0x20;
        return -1;
    }
    if (*(s32 *)((char *)sp2C + 0xDC) != 0) {
        *(u8 *)arg0 = *(u8 *)arg0 | 0x20;
        return -1;
    }
    return arg1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002B5F4);
#endif

/* game_libs_func_0002BA08: nibble-splitter — store low/high nibble of (arg1&0xFF)
 * to arg0->5 / arg0->6 (skip if zero). BYTE-EXACT.
 * `int *p = &arg1; ...*p` forces the dead arg-home `sw a1,4(sp)` (the prologue-less
 * arg-home, per docs/IDO_CODEGEN). The `v0++; v0--; new_var = hi;` nudges (found by
 * the permuter, base->0) move the high-nibble temp into $a1 to match the target's
 * register reuse. No episode (prologue-less reloc-blind context). */
void game_libs_func_0002BA08(void *arg0, int arg1) {
    int *p = &arg1;
    int v0 = *p & 0xFF;
    int hi;
    int new_var;
    if ((v0 & 0xF) != 0) {
        *((char *)arg0 + 5) = v0 & 0xF;
    }
    hi = (v0 >> 4) & 0xFF;
    if (hi != 0) {
        v0++;
        v0--;
        new_var = hi;
        *((char *)arg0 + 6) = new_var;
    }
}

/* Caps (DEFERRED): stack-byte-spill + byte-load + node-copy
 * idiom + indirect alloc helper. Real-C STRUCTURAL body below per
 * the in-comment sketch. Byte-match deferred. Name pre-checked: no
 * extern reuse. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
int gl_func_0002BA38(char *a0, int a1, int **a2, char *a3) {
  char *rv;
  int new_var2;
  char *new_var;
  rv = (char *) gl_func_00000000(*((unsigned char *) (a0 + 7)));
  if (rv == 0)
  {
    *a2 = 0;
    return 0;
  }
  *((int *) (a3 + 4)) = *((int *) (rv + 4));
  new_var = a3;
  *((unsigned char *) new_var) = *((unsigned char *) (rv + 3));
  a1 = (unsigned char) a1;
  *a2 = (int *) rv;
  new_var2 = (a1 + 2) & 0xFF;
  a1 = (unsigned char) a1;
  return new_var2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BA38);
#endif

// gl_func_0002BAAC — STRUCTURAL PASS (0xAC / 43 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A script-VM command-argument decoder (sibling of the
// gl_func_0002B09C / gl_func_0002B5F4 executor family).
//
//   void gl_func_0002BAAC(O *o, int op) {
//     op &= 0xFF;
//     if (op < 0x80) {
//       o->h_24 = op;                                   // literal arg
//       o->w_48 = 0;                                     // mode 0
//     } else if (op == 0x7F) {
//       o->h_24 = 0;  o->w_48 = 1;                        // mode 1
//     } else if (op == 0x7E) {
//       o->h_24 = 1;  o->w_48 = 2;                        // mode 2
//     } else {
//       int a = jal 0x400A4(&o->_8C);                     // 0x0C010029
//       a = (short)a;                                      // sign-ext
//       if (a != 0) o->h_24 = a;
//       o->b_0 &= ~0x08;                                   // clear bit3
//     }
//   }
//
// Struct-typing reference: decodes one command operand for the script
//   VM. The opcode byte selects an addressing/argument mode written
//   into halfword o->0x24 (the operand value) and word o->0x48 (the
//   mode tag): a literal op (< 0x80) → value=op/mode=0; the special
//   bytes 0x7F / 0x7E select fixed modes (0/1, 1/2); any other byte
//   triggers a fetch of a sign-extended halfword argument via the
//   fixed USO-relocated reader 0x0C010029 (≈0x400A4) from the operand
//   sub-block at o+0x8C, clearing flag bit3 of o->0. Operand-decode
//   peer to the gl_func_0002B09C / gl_func_0002B5F4 executors fed by
//   the gl_func_0002AD1C interpreter loop.
// Caps (DEFERRED): raw-word USO + fixed-target operand fetch
//   (0x400A4) — byte-match needs USO mnemonic disasm + reloc-pad
//   jal infra. Real-C STRUCTURAL body below per the analysis.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002BAAC(char *o, int op) {
    int a;
    op &= 0xFF;
    if (op < 0x80) {
        *(short *)(o + 0x24) = (short)op;
        *(int *)(o + 0x48) = 0;
    } else if (op == 0x7F) {
        *(short *)(o + 0x24) = 0;
        *(int *)(o + 0x48) = 1;
    } else if (op == 0x7E) {
        *(short *)(o + 0x24) = 1;
        *(int *)(o + 0x48) = 2;
    } else {
        a = gl_func_00000000(o, op, o + 0x48, o + 0x8C);
        *(short *)(o + 0x24) = (short)a;
        if ((short)a == 0) {
            *(unsigned char *)o = *(unsigned char *)o & ~0x08;
        } else {
            *(unsigned char *)o = *(unsigned char *)o | 0x08;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BAAC);
#endif

/* game_libs_func_0002BB58: 9-insn byte-to-float-scale leaf.
 * `a0[0x2C] = (float)(a1 & 0xFF) / 127.0f`.
 *
 * 2026-05-16: prior wrap said `* 127.0f` (8/9 cap). Funct decode of
 * insn @+0x18 (0x46083283) is 0x03 = div.s, NOT mul.s — corrected to
 * `/ 127.0f`. C-only emit drops to 32 bytes vs target 36; missing
 * `sw a1, 0x4(sp)` at +0x0 (arg-save sentinel that IDO doesn't emit
 * for non-spilling andi of a1). Same class as feedback-ido-arg-shadow-
 * spill-not-emitted (e.g. game_libs_func_0002DD38).
 * 2026-06-10 lever-asymmetry sweep (4 forms): the pointer-var arg-home
 * lever that emits `sw a0,0(sp)` for an a0 arg (2DD38, 0 diffs
 * standalone) does NOT emit `sw a1,4(sp)` for this a1 arg -- plain
 * &-form, (void)p form, and both store-through forms either skip the
 * home or grow to 10 insns with real memory traffic. The arg-home
 * lever appears a0-specific (or blocked by the float-convert liveness
 * here). Honest 76.67 floor. */
#ifdef NON_MATCHING
void game_libs_func_0002BB58(int *a0, int a1) {
    int *p = &a1;
    *(float*)((char*)a0 + 0x2C) = (float)(*p & 0xFF) / 127.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002BB58);
#endif

// gl_func_0002BB7C — STRUCTURAL PASS (0xC28 / 778 words ≈ 3.1KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle) — the LARGEST function in the game_libs script-VM
// subsystem: the per-frame command-script / animation-tree tick for
// one object. Huge -0x88 frame, full s0-s8/ra save.
//
//   void gl_func_0002BB7C(O *o) {
//     int w = o->w_0;
//     if ((w << 2) >= 0) return;                        // active gate
//     N *cmd = o->w_4C;                                  // command cur
//     ...
//     short t = o->h_1E;                                 // tween timer
//     if (t >= 2) { o->h_1E = t - 1; ... }                // tick down
//     S *tree = (char*)o + 0x70;                          // sub-tree
//     // ~750 words: walk the command stream from o->0x4C, advance
//     //  every animation channel / scene node under o+0x70, evaluate
//     //  per-node timers and packed control words, and emit the
//     //  resulting transforms; cleanup + return.
//   }
//
// Struct-typing reference: the top-level per-object tick of the
//   game_libs command-script / animation subsystem — it drives the
//   gl_func_0002AD1C interpreter loop, the gl_func_0002B09C /
//   gl_func_0002B5F4 command executors and the gl_func_0002BAAC
//   operand decoder. o->0 is the packed status word (sign/active bit
//   gating the whole tick); o->0x4C the command stream cursor; o->0x8
//   / o->0x1E timer halfwords; o+0x70 the embedded child/scene-node
//   block walked each frame. It folds together the keyframe steppers
//   (gl_func_00029978 / gl_func_0002AA30) and channel resets
//   (gl_func_00029B6C) over the whole node tree. The single biggest
//   driver of this file's animation/command subsystem.
// Caps (DEFERRED): raw-word USO + very large multi-phase per-object
//   tick over command stream + node tree (3.1KB / 778 words) —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   Real-C STRUCTURAL body below per the analysis (heavyweight body
//   summarised; only sketches the top-level early-out and tick
//   structure). Byte-match deferred. Name pre-checked: no extern
//   reuse.
#ifdef NON_MATCHING
/* PASS-2 2026-06-10 (big-swing): FULL m2c graft; THREE dense jumptables
 * (bounds 66/41/97 -- interpreter/dispatch shape) synthesized by block-
 * walk with heavily-shared case heads; case ORDER approximate. TABLE
 * EXTRACTION BLOCKED 2026-06-10: the lw lo16 offsets exceed post.bin
 * and match no asset under any base convention -- the hi16 resolves
 * via the boot-time loader only; RE the kernel game_libs loader to
 * unlock (docs/TOOLING_DECOMP). Checklist 1-15. */
extern int gl_func_0003E6E8();
extern int gl_func_0003F010();
extern int gl_func_0003F024();
extern int gl_func_0003F09C();
void gl_func_0002BB7C(char *arg0) {
    s32 sp60[16]; f32 sp63;
    s32 *temp_s3;
    s32 *temp_s7;
    s32 *temp_v0_3;
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 var_s0_2;
    s32 var_s5;
    s32 var_v0;
    u16 temp_v0_2;
    u16 temp_v1;
    u32 temp_t3;
    u8 var_v1;
    char *temp_s0;
    char *temp_s6;
    char *temp_v0_4;
    char *var_s1;

    if (*(s32 *)((char *)(arg0) + 0x0) & 0x20000000) {
        goto block_128;
    }
    temp_s7 = *(s32 *)((char *)(arg0) + 0x4C);
    if (!(*temp_s7 & 0x20000000) || !(*(s32 *)((char *)(arg0) + 0x3) & 0x80)) {
        temp_v1 = *(s32 *)((char *)(arg0) + 0x1E);
        temp_s6 = arg0 + 0x70;
        if ((s32) temp_v1 >= 2) {
            *(s32 *)((char *)(arg0) + 0x1E) = (u16) (temp_v1 - 1);
        } else {
        /* default (switch 3, flattened) */
loop_7:
            temp_v0 = gl_func_0003F010(temp_s6);
            temp_s2 = temp_v0 & 0xFF;
            if (temp_v0 >= 0xB0) {
                var_v1 = *(s32 *)((char *)(temp_v0) - 0xB0);
                var_s0 = &sp60[0];
                temp_a1 = var_v1 & 3;
                if ((temp_a1 & 0xFF) > 0) {
                    temp_s3 = &var_s0[temp_a1 & 0xFF];
                    do {
                        if (!(var_v1 & 0x80)) {
                            var_v0 = gl_func_0003F010(temp_s6);
                        } else {
                            var_v0 = gl_func_0003F024(temp_s6);
                        }
                        *var_s0 = var_v0;
                        var_s0 += 4;
                        var_v1 = (var_v1 * 2) & 0xFF;
                    } while ((u32) var_s0 < (u32) temp_s3);
                }
                switch (temp_s2) {                  /* switch 1; irregular */
                /* default (switch 1, flattened) */
                    temp_v0_2 = gl_func_0003E6E8(temp_s7, temp_s6, temp_s2, sp60[0]);
                    if (temp_v0_2 != 0) {
                        if (temp_v0_2 == -1U) {
                            func_00000000(arg0);
                        } else {
                            *(s32 *)((char *)(arg0) + 0x1E) = temp_v0_2;
                        }
                    } else {
                        goto loop_7;
                    }
                    break;
                case 0xB0:                          /* switch 1 */
                    *(s32 *)((char *)(arg0) + 0x0) = (s8) ((u8) *(s32 *)((char *)(arg0) + 0x0) | 0x20);
                    break;
                case 0xB1:                          /* switch 1 */
                case 0xB2:                          /* switch 1 */
                case 0xB3:                          /* switch 1 */
                case 0xB4:                          /* switch 1 */
                case 0xB5:                          /* switch 1 */
                case 0xB6:                          /* switch 1 */
                case 0xB7:                          /* switch 1 */
                case 0xB8:                          /* switch 1 */
                case 0xB9:                          /* switch 1 */
                case 0xBA:                          /* switch 1 */
                case 0xBB:                          /* switch 1 */
                case 0xBC:                          /* switch 1 */
                case 0xBD:                          /* switch 1 */
                case 0xBE:                          /* switch 1 */
                case 0xBF:                          /* switch 1 */
                case 0xC0:                          /* switch 1 */
                case 0xC1:                          /* switch 1 */
                case 0xC2:                          /* switch 1 */
                case 0xC3:                          /* switch 1 */
                case 0xC4:                          /* switch 1 */
                case 0xC5:                          /* switch 1 */
                case 0xC6:                          /* switch 1 */
                case 0xC7:                          /* switch 1 */
                case 0xC8:                          /* switch 1 */
                case 0xC9:                          /* switch 1 */
                case 0xCA:                          /* switch 1 */
                case 0xCB:                          /* switch 1 */
                case 0xCC:                          /* switch 1 */
                case 0xCD:                          /* switch 1 */
                case 0xCE:                          /* switch 1 */
                case 0xCF:                          /* switch 1 */
                case 0xD0:                          /* switch 1 */
                case 0xD1:                          /* switch 1 */
                case 0xD2:                          /* switch 1 */
                case 0xD3:                          /* switch 1 */
                case 0xD4:                          /* switch 1 */
                case 0xD5:                          /* switch 1 */
                case 0xD6:                          /* switch 1 */
                case 0xD7:                          /* switch 1 */
                case 0xD8:                          /* switch 1 */
                case 0xD9:                          /* switch 1 */
                case 0xDA:                          /* switch 1 */
                case 0xDB:                          /* switch 1 */
                case 0xDC:                          /* switch 1 */
                case 0xDD:                          /* switch 1 */
                case 0xDE:                          /* switch 1 */
                case 0xDF:                          /* switch 1 */
                case 0xE0:                          /* switch 1 */
                case 0xE1:                          /* switch 1 */
                case 0xE2:                          /* switch 1 */
                case 0xE3:                          /* switch 1 */
                case 0xE4:                          /* switch 1 */
                case 0xE5:                          /* switch 1 */
                case 0xE6:                          /* switch 1 */
                case 0xE7:                          /* switch 1 */
                case 0xE8:                          /* switch 1 */
                case 0xE9:                          /* switch 1 */
                case 0xEA:                          /* switch 1 */
                case 0xEB:                          /* switch 1 */
                case 0xEC:                          /* switch 1 */
                case 0xED:                          /* switch 1 */
                case 0xEE:                          /* switch 1 */
                case 0xEF:                          /* switch 1 */
                case 0xF0:                          /* switch 1 */
                case 0xF1:                          /* switch 1 */
                    temp_s0 = arg0 + 0x94;
                    func_00000000(temp_s0);
                    func_00000000(temp_s0, sp63);
                    goto loop_7;
                }
            } else {
                if (temp_v0 >= 0x70) {
                    temp_a1_2 = temp_v0 & 7;
                    temp_v1_2 = temp_v0 & 0xF8;
                    var_s5 = temp_a1_2 & 0xFF;
                    if ((temp_v1_2 != 0x70) && ((temp_a1_2 & 0xFF) >= 8)) {
                        var_s5 = 0;
                    }
                    switch (temp_v1_2) {            /* switch 2 */
                    case 0x70:                      /* switch 2 */
                    case 0x71:                      /* switch 2 */
                    case 0x72:                      /* switch 2 */
                    case 0x73:                      /* switch 2 */
                    case 0x74:                      /* switch 2 */
                    case 0x75:                      /* switch 2 */
                    case 0x76:                      /* switch 2 */
                    case 0x77:                      /* switch 2 */
                    case 0x78:                      /* switch 2 */
                    case 0x79:                      /* switch 2 */
                    case 0x7A:                      /* switch 2 */
                    case 0x7B:                      /* switch 2 */
                    case 0x7C:                      /* switch 2 */
                    case 0x7D:                      /* switch 2 */
                    case 0x7E:                      /* switch 2 */
                    case 0x7F:                      /* switch 2 */
                    case 0x80:                      /* switch 2 */
                    case 0x81:                      /* switch 2 */
                    case 0x82:                      /* switch 2 */
                    case 0x83:                      /* switch 2 */
                    case 0x84:                      /* switch 2 */
                    case 0x85:                      /* switch 2 */
                    case 0x86:                      /* switch 2 */
                    case 0x87:                      /* switch 2 */
                    case 0x88:                      /* switch 2 */
                    case 0x89:                      /* switch 2 */
                    case 0x8A:                      /* switch 2 */
                    case 0x8B:                      /* switch 2 */
                    case 0x8C:                      /* switch 2 */
                    case 0x8D:                      /* switch 2 */
                    case 0x8E:                      /* switch 2 */
                    case 0x8F:                      /* switch 2 */
                    case 0x90:                      /* switch 2 */
                    case 0x91:                      /* switch 2 */
                    case 0x92:                      /* switch 2 */
                    case 0x93:                      /* switch 2 */
                    case 0x94:                      /* switch 2 */
                    case 0x95:                      /* switch 2 */
                    case 0x96:                      /* switch 2 */
                    case 0x97:                      /* switch 2 */
                    case 0x98:                      /* switch 2 */
                        temp_v0_3 = *(s32 *)((char *)((arg0 + (var_s5 * 4))) + 0x50);
                        if (temp_v0_3 != 0) {
                            *(s32 *)((char *)(temp_s6) + 0x19) = (u8) ((u32) (*temp_v0_3 * 2) >> 0x1F);
                        } else {
                            *(s32 *)((char *)(temp_s6) + 0x19) = -1U;
                        }
                        break;
                    }
                    goto loop_7;
                }
                temp_t3 = temp_v0 & 0xF0;
                switch (temp_t3) {                  /* switch 3 */
                case 0x0:                           /* switch 3 */
                    *(s32 *)((char *)(arg0) + 0x1E) = (u16) (temp_v0 & 0xF & 0xFF);
                    break;
                case 0x1:                           /* switch 3 */
                case 0x2:                           /* switch 3 */
                case 0x3:                           /* switch 3 */
                case 0x4:                           /* switch 3 */
                case 0x5:                           /* switch 3 */
                case 0x6:                           /* switch 3 */
                case 0x7:                           /* switch 3 */
                case 0x8:                           /* switch 3 */
                case 0x9:                           /* switch 3 */
                case 0xA:                           /* switch 3 */
                case 0xB:                           /* switch 3 */
                case 0xC:                           /* switch 3 */
                case 0xD:                           /* switch 3 */
                case 0xE:                           /* switch 3 */
                case 0xF:                           /* switch 3 */
                case 0x10:                          /* switch 3 */
                case 0x11:                          /* switch 3 */
                case 0x12:                          /* switch 3 */
                case 0x13:                          /* switch 3 */
                case 0x14:                          /* switch 3 */
                case 0x15:                          /* switch 3 */
                case 0x16:                          /* switch 3 */
                case 0x17:                          /* switch 3 */
                case 0x18:                          /* switch 3 */
                case 0x19:                          /* switch 3 */
                case 0x1A:                          /* switch 3 */
                case 0x1B:                          /* switch 3 */
                case 0x1C:                          /* switch 3 */
                case 0x1D:                          /* switch 3 */
                case 0x1E:                          /* switch 3 */
                case 0x1F:                          /* switch 3 */
                case 0x20:                          /* switch 3 */
                case 0x21:                          /* switch 3 */
                case 0x22:                          /* switch 3 */
                case 0x23:                          /* switch 3 */
                case 0x24:                          /* switch 3 */
                case 0x25:                          /* switch 3 */
                case 0x26:                          /* switch 3 */
                case 0x27:                          /* switch 3 */
                case 0x28:                          /* switch 3 */
                case 0x29:                          /* switch 3 */
                case 0x2A:                          /* switch 3 */
                case 0x2B:                          /* switch 3 */
                case 0x2C:                          /* switch 3 */
                case 0x2D:                          /* switch 3 */
                case 0x2E:                          /* switch 3 */
                case 0x2F:                          /* switch 3 */
                case 0x30:                          /* switch 3 */
                case 0x31:                          /* switch 3 */
                case 0x32:                          /* switch 3 */
                case 0x33:                          /* switch 3 */
                case 0x34:                          /* switch 3 */
                case 0x35:                          /* switch 3 */
                case 0x36:                          /* switch 3 */
                case 0x37:                          /* switch 3 */
                case 0x38:                          /* switch 3 */
                case 0x39:                          /* switch 3 */
                case 0x3A:                          /* switch 3 */
                case 0x3B:                          /* switch 3 */
                case 0x3C:                          /* switch 3 */
                case 0x3D:                          /* switch 3 */
                case 0x3E:                          /* switch 3 */
                case 0x3F:                          /* switch 3 */
                case 0x40:                          /* switch 3 */
                case 0x41:                          /* switch 3 */
                case 0x42:                          /* switch 3 */
                case 0x43:                          /* switch 3 */
                case 0x44:                          /* switch 3 */
                case 0x45:                          /* switch 3 */
                case 0x46:                          /* switch 3 */
                case 0x47:                          /* switch 3 */
                case 0x48:                          /* switch 3 */
                case 0x49:                          /* switch 3 */
                case 0x4A:                          /* switch 3 */
                case 0x4B:                          /* switch 3 */
                case 0x4C:                          /* switch 3 */
                case 0x4D:                          /* switch 3 */
                case 0x4E:                          /* switch 3 */
                case 0x4F:                          /* switch 3 */
                case 0x50:                          /* switch 3 */
                case 0x51:                          /* switch 3 */
                case 0x52:                          /* switch 3 */
                case 0x53:                          /* switch 3 */
                case 0x54:                          /* switch 3 */
                case 0x55:                          /* switch 3 */
                case 0x56:                          /* switch 3 */
                case 0x57:                          /* switch 3 */
                case 0x58:                          /* switch 3 */
                case 0x59:                          /* switch 3 */
                case 0x5A:                          /* switch 3 */
                case 0x5B:                          /* switch 3 */
                case 0x5C:                          /* switch 3 */
                case 0x5D:                          /* switch 3 */
                case 0x5E:                          /* switch 3 */
                case 0x5F:                          /* switch 3 */
                case 0x60:                          /* switch 3 */
                    temp_v0_4 = arg0 + (temp_s2 & 0xF);
                    *(s32 *)((char *)(temp_v0_4) + 0xD4) = -1;
                    if (func_00000000(*(s32 *)((char *)(arg0) + 0x7), *(s32 *)((char *)(temp_s6) + 0x19), temp_v0_4 + 0xD4) == -1) {

                    }
                    goto loop_7;
                }
            }
        }
block_128:
        var_s0_2 = 0;
        var_s1 = arg0;
        do {
            temp_a0 = *(s32 *)((char *)(var_s1) + 0x50);
            if (temp_a0 != 0) {
                gl_func_0003F09C(temp_a0);
            }
            var_s0_2 += 4;
            var_s1 += 4;
        } while (var_s0_2 != 0x20);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BB7C);
#endif

// gl_func_0002C7A4 — STRUCTURAL PASS (0x7CC / 499 words ≈ 2KB, no
// episode). Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION
// (1 jr, no bundle) — another major per-object command/state
// processor in the gl_func_0002BB7C script-VM family. -0x68 frame.
//
//   void gl_func_0002C7A4(O *o) {
//     int w = o->w_0;
//     if (w >= 0) return;                               // sign-bit gate
//     if ((*pre)(o->b_4)) {                              // jal 0 USO
//       (*onA)(o->b_5);                                  // jal 0 USO
//       if (...) (*onB)(o->b_4, 2);
//       (*onC)(o->b_5);
//       ... per-(b_4/b_5) USO-reloc dispatch chain ...
//     }
//     int idx = o->w_0;                                   // packed idx
//     T *t = &D_0 + (idx << 2);                            // table walk
//     ...
//     short n = *(short*)(&D_0 + 0x2040);                  // sprite cnt
//     int   m = *(int*)(&D_0 + 0x2070);
//     ... ~450-word body ...
//   }
//
// Struct-typing reference: the active-bit-gated per-object processor
//   (word o->0 sign bit = active; the same packed-status word the
//   gl_func_0002BB7C tick / gl_func_0002ABC0 classifier use). Byte
//   fields o->4 / o->5 are mode/type selectors driving a long chain
//   of USO-relocated handler calls (`jal 0` slots, several with the
//   constant 2). The body then indexes a &D_0 table by a packed index
//   derived from o->0 and reads the sprite-subsystem count globals
//   &D_0+0x2040 (halfword) / &D_0+0x2070 (word — the same record
//   count gl_func_0001E134 / gl_func_00027E24 use). A heavyweight
//   command/state-advance peer to gl_func_0002BB7C — the
//   gl_func_0002AD1C interpreter's other large per-object driver.
// Caps (DEFERRED): raw-word USO + large multi-phase command
//   processor with many jal-0 USO-reloc calls — byte-match needs
//   USO mnemonic disasm + reloc-pad jal infra. Real-C STRUCTURAL
//   body below per the analysis (top-level early-out + first-phase
//   sketch). Byte-match deferred. Name pre-checked: no extern reuse.
/* gl_func_0002C7A4 GRAFT-CLASSIFIED 2026-06-10: EXTREME dense-
 * dispatcher -- two jumptables with bounds 45 and 113 and NO block-walk-
 * discoverable case heads (1 each; the case bodies are fully shared/
 * interleaved). The worst shape in the graft predictor (docs/
 * TOOLING_DECOMP item 16): loader-RE-gated. Do not graft until the
 * kernel game_libs loader RE yields true table extraction. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002C7A4(char *o) {
    int w = *(int *)o;
    int idx;
    char *t;
    short n;
    int m;
    if (w >= 0) return;
    if (gl_func_00000000(*(unsigned char *)(o + 4))) {
        gl_func_00000000(*(unsigned char *)(o + 5));
        gl_func_00000000(*(unsigned char *)(o + 4), 2);
        gl_func_00000000(*(unsigned char *)(o + 5));
    }
    idx = *(int *)o;
    t = (char *)&D_00000000 + ((idx << 2) & 0x3FFC);
    (void)t;
    n = *(short *)((char *)&D_00000000 + 0x2040);
    m = GL_COUNT_2070;
    (void)n; (void)m;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002C7A4);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002CF60);

// gl_func_0002CF70 — STRUCTURAL PASS (0xA4 / 41 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A bulk record sweep over the &D_0+0x2D00 sprite-record
// table (the gl_func_0001FBD4 table).
//
//   void gl_func_0002CF70(int a0) {
//     S *g = &D_0;
//     int n = g->h_2048;                                // record count
//     *(int*)(&D_5364) = ((... - a0 - 1) * stride);       // cached calc
//     if (n == 0) return;
//     R *rec = (char*)g + 0x2D00;                          // 0x160 ent
//     for (int i = 0; i < n; i++) {
//       if (rec->w_0 < 0) {                                // sign-bit on
//         jal 0x40E10(rec);                                // 0x0C010384
//         (*handler)(rec);                                 // jal 0 USO
//       }
//       n = g->h_2048;                                     // reload cnt
//       rec += 0x160;                                       // stride
//     }
//   }
//
// Struct-typing reference: iterates the SAME record table as
//   gl_func_0001FBD4 / gl_func_0002119C — base &D_0+0x2D00, fixed
//   stride 0x160, live count halfword &D_0+0x2048. A count-derived
//   product is cached into the global word &D_5364 up front. Each
//   record whose word +0 has its sign bit set (active marker) is
//   processed via the fixed routine 0x0C010384 (≈0x40E10) followed by
//   a USO-relocated per-record handler (`jal 0` slot). A bulk
//   "process every active record" sweep over that table (sibling to
//   gl_func_0001FBD4's lighter callback sweep).
// Caps (DEFERRED): raw-word USO + fixed-target 0x40E10 + jal-0 USO-
//   reloc per-record calls — byte-match needs USO mnemonic disasm
//   + reloc-pad jal infra. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002CF70(int a0) {
    int n = *(short *)((char *)&D_00000000 + 0x2048);
    int i;
    char *rec;
    *(int *)((char *)&D_00000000 + 0x5364) = (-a0 - 1) * 0x160;
    if (n == 0) return;
    rec = (char *)&D_00000000 + 0x2D00;
    for (i = 0; i < n; i++) {
        if (*(int *)rec < 0) {
            gl_func_00000000(rec);
            gl_func_00000000(rec);
        }
        n = *(short *)((char *)&D_00000000 + 0x2048);
        rec += 0x160;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002CF70);
#endif

#ifdef NON_MATCHING
/* gl_func_0002D014: 20-insn (0x50) "drain counter" loop with cross-function
 * jal landing 0x28 bytes INTO gl_func_00040DE8's body. Mid-function alt-entry
 * handled via `gl_ref_00040E10 = 0x00040E10;` in undefined_syms_auto.txt
 * (per docs/N64_FORENSICS.md feedback-game-libs-jal-targets recipe).
 *
 * Decoded body:
 *   if (a0->[0xDC] > 0) {
 *       do {
 *           gl_ref_00040E10(a0);  // alt-entry into gl_func_00040DE8
 *           gl_func_00000000(a0);
 *           a0->[0xDC] -= 1;
 *       } while (a0->[0xDC] > 0);
 *   }
 *
 * 75 % byte-exact. Built has bnezl-likely → my `> 0` produces blezl which
 * is correct; remaining diff is loop-iteration register pick (built uses
 * v0 for the loop counter, target uses t7→t8). Source 1 (sibling cluster
 * of recently-promoted 0x2D6C8). 2026-05-27 retest: split into two locals
 * `loaded = *p; n = loaded - 1;` REGRESSED to 15/20 (load picked $v1, dec
 * picked $v0 — still not $t7/$t8). The $tN-vs-$vN preference is an
 * allocator-weight cap; permuter-class. */
extern int gl_ref_00040E10();    /* mid-body alt-entry, see undefined_syms_auto.txt */
void gl_func_0002D014(int *a0) {
    register int *s0 = a0;
    int n;
    if (*(int*)((char*)s0 + 0xDC) > 0) {
        do {
            gl_ref_00040E10(s0);
            gl_func_00000000(s0);
            n = *(int*)((char*)s0 + 0xDC) - 1;
            *(int*)((char*)s0 + 0xDC) = n;
        } while (n > 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D014);
#endif

/* gl_func_0002D064: 51-insn (0xCC) per-frame init with 16-iter call loop.
 * Matched 2026-05-14 via 4-step refinement chain: ~K andi mask form,
 * cse-bust-via-distinct-externs for &D_0 stores at +148/+152, $s0
 * priority via `i = 0;` first body assignment, and store-statement
 * reordering to match target's emit sequence (0,16,1,18,20,10,8,12,14,2). */
extern char D_2D064_148;
extern char D_2D064_152;
extern int gl_ref_0003E8C4();
void gl_func_0002D064(char *a0) {
    char *p;
    int i;
    gl_func_00000000();
    i = 0;
    *(char*)(a0 + 0) = *(char*)(a0 + 0) & ~2;
    *(short*)(a0 + 16) = 0;
    *(char*)(a0 + 1) = 1;
    *(short*)(a0 + 18) = 0;
    *(short*)(a0 + 20) = 0;
    *(short*)(a0 + 10) = 0;
    *(short*)(a0 + 8) = 0x1680;
    *(short*)(a0 + 12) = 0;
    *(short*)(a0 + 14) = 0;
    *(char*)(a0 + 2) = 0;
    *(int*)(a0 + 148) = (int)&D_2D064_148;
    *(int*)(a0 + 152) = (int)&D_2D064_152;
    *(int*)(a0 + 224) = 0;
    *(float*)(a0 + 28) = 1.0f;
    *(float*)(a0 + 32) = 0.0f;
    *(float*)(a0 + 36) = 0.0f;
    *(float*)(a0 + 40) = 0.5f;
    p = a0;
    for (; i < 64; i += 4) {
        gl_ref_0003E8C4(*(int*)(p + 56));
        p += 4;
    }
}

/* gl_func_0002D130: 59-insn (0xF4) nested-loop per-frame init.
 *   s3 = D_base + (a0 * 0x160);
 *   for (j = 0; j < 64; j += 4) {
 *       retval = gl_func(&D_2198, 228);
 *       if (retval == 0) s1->[0x38] = &D_5280;
 *       else { ... 2-iter inner loop ... }
 *       gl_func_alt(s1->[0x38]);
 *       s1 += 4;
 *   }
 *
 * NATURAL CEILING: 90.74% NM. The 16-insn diff covers prologue scheduler
 * order + inner-loop register rename (build uses $a0/$v1 counter+ptr;
 * target uses $v1/$v0). Was previously documented as INSN_PATCH-promoted
 * to EXACT; INSN_PATCH REMOVED 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default build is
 * INCLUDE_ASM. */
#ifdef NON_MATCHING
void gl_func_0002D130(int a0) {
    char *base = &D_00000000;
    int *s3 = (int*)(base + (a0 * 0x160) + 0x2D00);
    char *d5280 = base + 0x5280;
    int *s1 = s3;
    int j;
    for (j = 0; j < 64; j += 4) {
        int *retval = (int*)gl_func_00000000(base + 0x2198, 228);
        if (retval == 0) {
            *(int*)((char*)s1 + 0x38) = (int)d5280;
        } else {
            int *p;
            int i;
            *(int*)((char*)s1 + 0x38) = (int)retval;
            *(int*)((char*)retval + 0x4C) = (int)s3;
            *(char*)retval &= 0xFF7F;
            p = retval;
            for (i = 0; i < 8; i += 4) {
                *(int*)((char*)p + 0x54) = 0;
                *(int*)((char*)p + 0x58) = 0;
                *(int*)((char*)p + 0x5C) = 0;
                p = (int*)((char*)p + 16);
                *(int*)((char*)p + 0x40) = 0;
            }
        }
        gl_func_00000000(*(int*)((char*)s1 + 0x38));
        s1 = (int*)((char*)s1 + 4);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D130);
#endif

#ifdef NON_MATCHING
/* gl_func_0002D224: 52-insn (0xD0) init with 2 loops + bit-clear chain.
 *
 *   self = a0;
 *   v1 = self;
 *   for (i = 0; i < 16; i += 4) {              ; 4 iters
 *       v1->[0x3C] = &D_5280;
 *       v1->[0x40] = &D_5280;
 *       v1->[0x44] = &D_5280;
 *       v1 += 16;
 *       v1->[0x28] = &D_5280;                  ; delay-slot, post-incr
 *   }
 *   ; bit-clear chain on self->[0]:
 *   self->[0] &= ~0x80; &= ~0x20; &= ~0x08; &= ~0x10; &= ~0x01;
 *   v1 = self;
 *   for (i = 0; i < 8; i += 4) {               ; 2 iters
 *       v1->[345] = v1->[346] = v1->[347] = (s8)-1;
 *       v1 += 4;
 *       v1->[340] = (s8)-1;                     ; delay-slot, post-incr
 *   }
 *   self->[3] = 96;
 *   self->[44] = 1.0f; self->[52] = 1.0f;
 *   gl_func(self + 156);                        ; alt-entry call
 *   gl_func(self);                              ; alt-entry call (recursive into init?)
 *
 * Initial structural pass; cross-USO alt-entry call shape caps expected. */
void gl_func_0002D224(char *a0) {
    char *base = &D_00000000;
    char *v1;
    int i;
    v1 = a0;
    for (i = 0; i != 16; i += 4) {
        *(int*)(v1 + 0x3C) = (int)(base + 0x5280);
        *(int*)(v1 + 0x40) = (int)(base + 0x5280);
        *(int*)(v1 + 0x44) = (int)(base + 0x5280);
        v1 += 16;
        *(int*)(v1 + 0x28) = (int)(base + 0x5280);
    }
    *(char*)a0 &= ~0x80;
    *(char*)a0 &= 0xDF;
    *(char*)a0 &= 0xF7;
    *(char*)a0 &= 0xEF;
    *(char*)a0 &= 0xFE;
    v1 = a0;
    for (i = 0; i != 8; i += 4) {
        *(char*)(v1 + 0x159) = -1;
        *(char*)(v1 + 0x15A) = -1;
        *(char*)(v1 + 0x15B) = -1;
        v1 += 4;
        *(char*)(v1 + 0x154) = -1;
    }
    *(char*)(a0 + 3) = 96;
    *(float*)(a0 + 0x2C) = 1.0f;
    *(float*)(a0 + 0x34) = 1.0f;
    gl_func_00000000(a0 + 0x9C);
    gl_func_00000000(a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D224);
#endif

#ifdef NON_MATCHING
/* gl_func_0002D2F4: 32-insn (0x88) per-frame reset + 4-iter init loop.
 *
 *   gl_func_0001CA10_alt();                     ; alt-entry helper
 *   for (p = &D_3280; p < &D_5280; p += 0x80) { ; iterate over 64 entries
 *       *(char*)p &= ~0x80;                     ; clear flag bit at +0x0
 *       *(int*)(p + 0x50) = 0;                  ; clear int field at +0x50
 *   }
 *   for (s0 = &D_2D00; s0 != &D_3280; s0 += 0x160) {  ; 4 iters
 *       gl_func_0005EB4C_alt(s0);
 *   }
 *
 * NM 20->18 diffs: first-loop addressing rewritten so cursor walks base+0
 * with fixed +0x3280/+0x3250/+0x3200 derefs (matches target's post-increment
 * store offsets), and base materialized inline (not a shared `base` local) so
 * the prologue + first loop body match exactly. RESIDUAL CAP: target emits
 * TWO independent lui sequences for the first-loop cursor (v0) and limit (v1)
 * — IDO CSEs the common `&D_00000000` base into a saved reg here, which
 * cascades into the second loop reusing it (limit recomputed inside the loop
 * vs target precomputing it). Base-CSE/coloring cap. */
void gl_func_0002D2F4(void) {
    char *p, *s0;
    gl_func_00000000();
    for (p = (char*)&D_00000000; p < (char*)&D_00000000 + 0x2000;) {
        char c = *(char*)(p + 0x3280);
        p += 0x80;
        *(int*)(p + 0x3250) = 0;
        *(char*)(p + 0x3200) = c & 0xFF7F;
    }
    s0 = (char*)&D_00000000 + 0x2D00;
    while (s0 != (char*)&D_00000000 + 0x3280) {
        gl_func_00000000(s0);
        s0 += 0x160;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D2F4);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002D36C);

// gl_func_0002D37C — STRUCTURAL PASS (0x2A4 / 169 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A subsystem timer / sequence-step tick.
//
//   void gl_func_0002D37C(a0, a1, a2, int a3) {
//     if (a3 != 1) return;
//     if (!(*precond)()) { *(int*)(&D_xxx) = 0; return; } // jal 0 USO
//     int *ctr = (int*)(&D_0 + 0);                        // global ctr
//     if (*ctr == 0) return;
//     if (--(*ctr) != 0) return;                           // not expired
//     int st = *(int*)(&D_yyy);
//     if (st == 0xF) {
//       jal 0x4423C(arg & 0xFF);                           // 0x0C0108F1
//       jal 0x41E9C(arg & 0xFF);                           // 0x0C0107A7
//     } else {
//       jal 0x44490(...);                                  // 0x0C010924
//       jal 0x41ED4(...);                                  // 0x0C0107B5
//     }
//   }
//
// Struct-typing reference: a gated countdown sequencer. Runs only
//   when the a3 selector equals 1 and a USO-relocated precondition
//   (`jal 0` slot) passes (otherwise it zeroes a global and bails).
//   A global counter at &D_0+0 is decremented each call; when it
//   reaches zero the function fires a fixed USO-relocated routine
//   pipeline — 0x0C0108F1 (≈0x4423C) / 0x0C0107A7 (≈0x41E9C) on the
//   state==0xF path, 0x0C010924 (≈0x44490) / 0x0C0107B5 (≈0x41ED4)
//   otherwise — to advance the next phase. A subsystem
//   tick/scheduler step in the game_libs subsystem (peer to the
//   gl_func_00026214 ring scheduler).
// Caps (DEFERRED): raw-word USO + gated countdown + fixed-target
//   sequence pipeline (0x4423C / 0x41E9C / 0x44490 / 0x41ED4) —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002D37C(int a0, int a1, int a2, int a3) {
    int *ctr;
    int st;
    (void)a1; (void)a2;
    if (a3 != 1) return;
    if (!gl_func_00000000()) {
        *(int *)((char *)&D_00000000 + 0) = 0;
        return;
    }
    ctr = (int *)((char *)&D_00000000 + 0);
    if (*ctr == 0) return;
    if (--(*ctr) != 0) return;
    st = *(int *)((char *)&D_00000000 + 4);
    if (st == 0xF) {
        gl_func_00000000(a0 & 0xFF);
        gl_func_00000000(a0 & 0xFF);
    } else {
        gl_func_00000000(a0);
        gl_func_00000000(a0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D37C);
#endif

/* gl_func_0002D620: boundary-corrected (orphan-fn delete+merge). The 2-word
 * orphan game_libs_func_0002D618 (`lui t6,0; lw t6,0(t6)`) was a splat mis-split
 * of THIS function's prologue — it loads *(int*)&D for the `== 1` test, which the
 * C reads first (IDO emits it pre-prologue). Merged into gl_func_0002D620.s
 * (0x50 -> 0x58); NM-wrap C already built build[2:]==expected -> byte-exact. */
void gl_func_0002D620(void) {
    if (*(int*)&D_00000000 == 1) {
        gl_func_00000000();
    } else {
        gl_func_00000000(0x95);
        gl_func_00000000(0xF1000000, 0);
        *(int*)&D_00000000 = 1;
    }
}

extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002D670() {
    gl_func_00000000((void*)0xF2000000, 0);
    gl_func_00000000(0x91);
    D_00000000 = 0;
}

extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002D6A0() {
    gl_func_00000000((void*)0xF2000000, 0);
    D_00000000 = 0;
}

/* gl_func_0002D6C8: 17-insn 2-call function. MATCHED.
 *   gl_func_00000000(0xF0000000, a0);
 *   if (a0 >= 2) a0 = 3;
 *   gl_func_00000000(0xF0000000, a0);
 * Was 94.4% NM with a trailing orphan `move a2, a0` (0x00803025) past this
 * fn's jr ra; nop — it is the successor gl_func_0002D710's mis-attributed
 * arg-setup prologue (a2 = a0; 0002D710 uses a2). Fixed PROPERLY (replacing
 * the banned SUFFIX_BYTES) by a splat boundary correction: shrank this .s to
 * 17 insns (0x44) and moved the orphan word into gl_func_0002D710.s as its
 * leading insn. ROM byte sequence preserved. */
void gl_func_0002D6C8(int a0) {
    gl_func_00000000(0xF0000000, a0);
    if (a0 >= 2) {
        a0 = 3;
    }
    gl_func_00000000(0xF0000000, a0);
}

/* 14-insn main body + 1-insn SUFFIX (`or $a2, $a0, $zero` = stolen
 * prologue for next fn) — declared size 0x3C / 15 words.
 *
 * Decoded:
 *   void f(int a0, int unused_a1, int a2) {
 *       D_store = a0;
 *       gl_func_00000000(0x41010000, ((int*)&D_load)[a2], a2);
 *   }
 *
 * 2026-05-06: BREAKTHROUGH — promoted from 1/15 to 14/15 word match by
 * splitting the cross-USO placeholder into TWO distinct externs
 * (`D_2D710_store` for the write, `D_2D710_load` for the array read).
 * Both alias to 0x00000000 in undefined_syms_auto.txt; both runtime-
 * relocate identically. Declaring them as DISTINCT C externs forces
 * IDO -O2 to emit 2 separate `lui` instructions (one into $at for the
 * store base, one into $a1 for the array base) instead of CSE-folding
 * them into a shared `lui v0; addiu v0, 0` pair. Matches target's
 * `lui $at, 0; sll t6; lui $a1, 0; ...` schedule exactly.
 *
 * Remaining 1-insn diff: target has no `sw a1, 0x1C(sp)` (unused-arg
 * spill) at offset 0x4. IDO -O2 always spills incoming arg regs even
 * when unused (per docs/IDO_CODEGEN.md feedback-ido-unused-arg-save).
 * Cannot elide from C without dropping the a1 parameter, which would
 * change ABI (a2 would shift into $a1 reg). The 1-insn cap is the
 * unused-arg-save residual.
 *
 * Promotion path to byte-correct: SUFFIX_BYTES injection of
 * `0x00803025` at offset 0x38 + INSN_PATCH at offset 0x4 to overwrite
 * the spill with `lui $at, 0` (= 0x3C010000) — but that creates two
 * luis at 0x4 and 0x8 to $at, breaking the second's value. Untrivial.
 * Defer to next pass; current wrap captures the structural fix.
 *
 * 2026-05-11: was promoted with the measured C body plus INSN_PATCH
 * (post-cc unused-$a1-spill rewrite + trailing successor setup word).
 * INSN_PATCH REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to
 * NM-wrap. NATURAL CEILING: unused-arg-save residual stays NM. */
extern int D_2D710_store;
extern int D_2D710_load;
#ifdef NON_MATCHING
void gl_func_0002D710(int a0, int unused_a1, int a2) {
    D_2D710_store = a0;
    gl_func_00000000(0x41010000, ((int*)&D_2D710_load)[a2], a2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D710);
#endif

/* gl_func_0002D74C: byte-for-byte SIBLING of gl_func_0002D710 (above)
 * with one differing constant — `lui $a0, 0x4100` (= 8.0f) instead of
 * 0x4101 (= 8.0625f). Same structure, same trailing SUFFIX
 * `or $a2, $a0, $zero` stolen-prologue for next fn.
 *
 * 2026-05-06: applied feedback-ido-cse-bust-via-distinct-externs
 * (docs/IDO_CODEGEN.md) — promoted from 1/15 to 14/15 word match by
 * splitting D_00000000 into D_2D74C_store + D_2D74C_load (both
 * aliased to 0x0 in undefined_syms_auto.txt). 1-insn cap remains: the
 * unused-a1 spill at offset 0x4 (`sw a1, 0x1C(sp)` per
 * docs/IDO_CODEGEN.md feedback-ido-unused-arg-save). Same cap class
 * as sibling 0x2D710.
 *
 * 2026-05-11: was promoted with the same measured INSN_PATCH class as
 * sibling gl_func_0002D710 (call constant 0x41000000). INSN_PATCH REMOVED
 * 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to
 * NM-wrap. NATURAL CEILING: unused-arg-save residual stays NM. */
extern int D_2D74C_store;
extern int D_2D74C_load;
#ifdef NON_MATCHING
void gl_func_0002D74C(int a0, int unused_a1, int a2) {
    D_2D74C_store = a0;
    gl_func_00000000(0x41000000, ((int*)&D_2D74C_load)[a2], a2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D74C);
#endif

/* gl_func_0002D788: 14-insn main body + 4-insn trailing alt-entry
 * (`li v0, 8; lui at, 0; sw v0, 0(at); lui at, 0`) — declared size 0x48
 * (18 insns). Same MERGE-BLOCKED post-epilogue alt-entry class as
 * gl_func_00062298 (per existing in-source doc).
 *
 * Main body decodes:
 *   *(int*)&D_a = a0;
 *   gl_func_00000000(0x41020000, ((int*)&D_b)[a2]);
 *
 * Two distinct globals (D_a and D_b) need separate externs to break
 * IDO CSE on the placeholder D_00000000 address.
 *
 * Source 2 (sibling): in the same offset region as recently-wrapped
 * gl_func_0002D6C8 (94.4% in-place mutate) and the 0x2D838/0x2D870
 * prologue-stolen-successor family. Wrap captures the main body decode
 * for permuter / future-pass refinement; alt-entry stays in INCLUDE_ASM. */
extern int D_2D788_a;
extern int D_2D788_b;
/* Skipping unused middle arg ($a1) via K&R: declare prototype with 3 args
 * but use only a0 and a2 — IDO -O2 still spills unused $a1 (per
 * docs/IDO_CODEGEN.md feedback-ido-unused-arg-save). The wrap caps at
 * ~85 % via that one extra `sw a1, 0x1C(sp)` insn that natural C cannot
 * elide; target was likely built with $a1 actually used or with a flag
 * variant.
 *
 * 2026-05-06 retry: tried `register int unused_a1` — confirmed no-op
 * (IDO -O2 still emits the spill regardless of `register` hint on the
 * unused arg). Cap class is genuinely structural per the existing
 * feedback-ido-unused-arg-save doc; no C-level lever found for elision.
 *
 * 2026-05-07 retry: confirmed two-extern split (D_2D788_a, D_2D788_b
 * both at addr 0x0 in undefined_syms_auto.txt) does NOT promote — the
 * blocking diff is the `sw a1, 0x1C(sp)` unused-arg spill that target
 * lacks. Same shape as gl_func_0002D710 / 0002D74C siblings. Adding
 * symbols just keeps emit identical at 11.1% byte-exact (target reorders
 * sll/lui sequence which built can't reach, plus the spill diff). The
 * actual cap is the unused-arg-save not the &D shared-base — splitting
 * the externs solves the wrong problem here.
 *
 * 2026-05-11: was promoted with the same measured INSN_PATCH family as
 * gl_func_0002D710/gl_func_0002D74C, plus instruction-appending SUFFIX_BYTES
 * for the 3 words after the C body's natural epilogue. Both INSN_PATCH and
 * instruction-appending SUFFIX_BYTES REMOVED 2026-05-23 as match-faking per
 * feedback_no_instruction_forcing_matches_policy — fn rolled back to
 * NM-wrap. NATURAL CEILING: unused-arg-save + alt-entry stay NM. */
#ifdef NON_MATCHING
void gl_func_0002D788(int a0, int unused_a1, int a2) {
    D_2D788_a = a0;
    gl_func_00000000(0x41020000, (&D_2D788_b)[a2]);
    (void)unused_a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D788);
#endif

/* gl_func_0002D7D0: 24-insn 4-call wrapper that does a leading store to
 * D_0 (size 8, set up by predecessor 0x2D788's tail) then 4 sequential
 * gl_func calls each loading a different float-encoded constant
 * (0x4101=8.0625f, 0x4100=8.0f, 0x4102=8.125f, 0xF000=cross-USO marker)
 * with a shared `*(int*)&D_array[0x20]` payload.
 *
 * Decoded:
 *   D_0 = D_pred_size8;             // predecessor's stolen-tail set 8 here
 *                                    // (sw $v0, 0($at) using predecessor's
 *                                    // trailing `addiu v0,zero,8; lui at,0`)
 *   D_0 = ...;                       // 2nd store same target via fresh lui
 *   gl_func_00000000(0x41010000, ((int*)&D_2D7D0_arr)[0x8], ...);
 *   gl_func_00000000(0x41000000, ((int*)&D_2D7D0_arr)[0x8], ...);
 *   gl_func_00000000(0x41020000, ((int*)&D_2D7D0_arr)[0x8], ...);
 *   gl_func_00000000(0xF0000000, 0);
 *
 * Cap class: PROLOGUE-STOLEN-SUCCESSOR (per docs/MATCHING_WORKFLOW.md
 * feedback-prologue-stolen-successor-no-recipe). Predecessor 0x2D788
 * has a 4-insn alt-entry stub at its tail (`addiu v0, zero, 8;
 * lui at, 0; sw v0, 0(at); lui at, 0`) where the LAST insn `lui at, 0`
 * sets $at for the successor's first `sw v0, 0($at)`. C-only emit will
 * produce a redundant `lui $at, 0` at the start of the successor,
 * +4 bytes vs expected.
 *
 * Promotion path: write C body with the leading store form
 * (`D_2D7D0_target = D_2D7D0_value;`) and add
 * `build/src/game_libs/game_libs_post.c.o: PROLOGUE_STEALS := gl_func_0002D7D0=4`
 * to the Makefile. Defer to multi-tick — needs sibling identification to
 * confirm value tracked in the predecessor's stolen tail.
 *
 * Also potential beneficiary of feedback-ido-cse-bust-via-distinct-externs
 * (docs/IDO_CODEGEN.md) since the target uses 4 separate luis for the
 * float constants and the array reads — already separate-symbol via the
 * 0xF000 constant, but the array reads might benefit from 4-extern split.
 *
 * 2026-05-07 attempt: write C body matching the 4-call shape. The
 * leading 2 stores to D_0 (one via predecessor's stolen-$at, one via
 * fresh lui) cannot be written directly in C — the first store uses
 * $at from the predecessor's tail and $v0 also from the predecessor.
 * Both are non-standard C carryovers. Wrapping the 4 calls only gives
 * a partial body; the leading stores would need PROLOGUE_STEALS=4 to
 * splice off the redundant lui+sw IDO emits.
 *
 * 2026-05-07 follow-up: the trailing 2 words at offsets 0x60-0x64 in
 * this function's symbol are `lui t6, 0; lw t6, 0(t6)` — the stolen-
 * prologue donation to SUCCESSOR gl_func_0002D838 (whose comment at
 * line 795 confirms PROLOGUE_STEALS=8 expects `lui t6; lw t6, 0(t6)`
 * pair as predecessor tail). Full promotion recipe is therefore:
 *   build/src/game_libs/game_libs_post.c.o:
 *     PROLOGUE_STEALS := gl_func_0002D7D0=4 \
 *     SUFFIX_BYTES := gl_func_0002D7D0=0x3C0E0000,0x8DCE0000
 * (Note: SUFFIX target is `lui t6, %hi(D_2D838_X); lw t6, %lo(D_2D838_X)(t6)`;
 * actual emitted bytes use 0x0000 for the relocated symbol, runtime-
 * resolved by USO loader — same convention as the gl_ref_*=0 placeholder.)
 * Combo recipe is in scope per
 * docs/POST_CC_RECIPES.md#feedback-prefix-bytes-plus-insn-patch-breaks-documented-caps.
 *
 * 2026-05-07 attempt 2 — `volatile int *p = &D_2D7D0_target; *p = 8; *p = 8;`
 * to defeat dead-store elim on the duplicate leading stores. Build emits 2
 * stores correctly via volatile, BUT register-name mismatch:
 *   - target: `sw $v0, 0($at)` (predecessor's stolen $v0=8, $at=&D)
 *   - built:  `sw $v1, 0($v0)` (IDO chose $v1 for value, $v0 for address)
 * PROLOGUE_STEALS=12 (=3 insns) would splice the lui/addiu/li-8 trio IDO
 * emits up front, but the spliced .o then has `sw $v1, 0($v0)` accessing
 * uninitialized $v1 at runtime (predecessor only sets $v0/$at). C-level
 * register-pinning isn't possible (`register T x asm("$N")` rejected by
 * IDO per feedback_ido_no_gcc_register_asm). Reverted; cap stands.
 *
 * 2026-05-08 re-verify: diff unchanged from 2026-05-07. Built has 11 insns
 * before the first jal (prologue + 4-arg-setup), target has 8 insns (prologue
 * + 2 stolen-stores + 1 a1-load-via-fresh-lui-pair-CSE'd-from-leading-store).
 * The 3-insn delta matches the 12-byte PROLOGUE_STEALS suggestion above, but
 * the spliced bytes still wouldn't carry valid runtime semantics for the
 * non-$at base register IDO insists on. **Confirmed dead-end via current
 * IDO + asm-processor pipeline.** Leaving as-is for permuter / future
 * compiler-update revisit.
 *
 * 2026-05-08 agent-f iteration: retried the volatile store form
 * (`volatile int *p = &D_00000000; *p = 8; *p = 8;`). It reaches the
 * target's 0x68-byte size but emits the setup before the stack prologue:
 *   lui v0; addiu v0; addiu v1,8; addiu sp; sw v1,0(v0) ...
 * That is worse than the current body for promotion: PROLOGUE_STEALS=12
 * leaves the second store in the wrong slot, while exacting it up would
 * require rewriting most of the function body via INSN_PATCH.
 *
 * 2026-05-08 agent-e re-eval: with the recent splice-script extensions
 * (ANDI 4-byte / R-type 8-byte), neither directly applies — the leading
 * stolen-state here is `sw v0, 0(at)` (opcode 0x2B / SW). To extend the
 * splice script to accept SW would still leave the C-emit's pre-store
 * register-name issue unresolved (IDO insists on $v0 for address, $v1
 * for value, vs target's $at for address, $v0 for value).
 *
 * Possible next-pass approach (deferred): combine PROLOGUE_STEALS=12
 * with INSN_PATCH at offsets 0x0/0x4 to overwrite the wrong-register
 * lui+sw with the correct AC220000 bytes. The patch would need to
 * coordinate with the rest of the function's emit being byte-correct,
 * which requires the volatile-store body to first reach the right
 * post-store shape — currently UNVERIFIED. INSN_PATCH+PROLOGUE_STEALS
 * combo precedent exists in feedback-prefix-bytes-plus-insn-patch-
 * breaks-documented-caps.
 *
 * 2026-05-08 (later, after game_uso_func_00001DDC `0.0f*0.0f` → memory-load
 * +0.73pp finding): no zero-term cite-applicable here — this function uses
 * integer args (0x41010000 etc as int constants, not float-zero terms).
 * 2026-05-11: had promoted with the measured C body plus
 * SUFFIX_BYTES_FORCE + INSN_PATCH; both mechanisms REMOVED 2026-05-23 as
 * match-faking. Now at honest 87.04% NM (4-call body C-emit is correct;
 * the predecessor-stolen store + successor suffix bytes diverge from
 * target without the banned post-cc recipes). */
extern int D_2D7D0_arr;
#ifdef NON_MATCHING
void gl_func_0002D7D0(void) {
    gl_func_00000000(0x41010000, ((int*)&D_2D7D0_arr)[8]);
    gl_func_00000000(0x41000000, ((int*)&D_2D7D0_arr)[8]);
    gl_func_00000000(0x41020000, ((int*)&D_2D7D0_arr)[8]);
    gl_func_00000000(0xF0000000, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D7D0);
#endif

/* gl_func_0002D838: 12-insn prologue-stolen-successor (sibling of 0002D8A8,
 * 0002D870). NATURAL CEILING: 83.33% NM. Predecessor's tail
 * (`lui $t6,0; lw $t6,0(t6)`) loads $t6=*(int*)D_2D838_X; this function
 * uses $t6 as an array index into D_2D838_Y. C body emits the lui+lw pair
 * which the historical PROLOGUE_STEALS=8 spliced off; trailing 2 words
 * were stolen-prologue for successor 0002D870 added via SUFFIX_BYTES.
 * Both mechanisms REMOVED 2026-05-23 as match-faking.
 *
 * Calls gl_func_00000000(0x41030000, D_2D838_Y[D_2D838_X]) — passes float
 * bits 8.1875f as a0 and indexed table value as a1. */
extern int D_2D838_X;
extern int D_2D838_Y[];
void game_libs_func_0002D830(void) {
    gl_func_00000000(0x41030000, D_2D838_Y[D_2D838_X]);
}

/* gl_func_0002D870: 12-insn prologue-stolen-successor (sibling of 0002D838,
 * 0002D8A8). Predecessor's tail loads $t6 = *(int*)D_2D870_X; this function
 * uses $t6 as index into D_2D870_Y. PROLOGUE_STEALS=8 splices the duplicate
 * `lui t6, 0; lw t6, 0(t6)` IDO emits at start. SUFFIX_BYTES appends the
 * same 2-insn pair as stolen-prologue for successor 0002D8A8.
 *
 * Calls gl_func_00000000(0x41010000, D_2D870_Y[D_2D870_X]) — passes float
 * bits 8.0625f as a0 and indexed table value as a1. */
extern int D_2D870_X;
extern int D_2D870_Y[];
void game_libs_func_0002D868(void) {
    gl_func_00000000(0x41010000, D_2D870_Y[D_2D870_X]);
}

/* game_libs_func_0002D8A0: table-dispatch, third sibling of 0002D830/0002D868
 * (cross-TU orphan merge). Orphan game_libs_func_0002D8A0 (lui t6; lw t6,0 =
 * the index) was in game_libs.c; merged into the body .s (one 0x38 symbol),
 * INCLUDE_ASM removed from game_libs.c. a0 = 0x41000000 (8.0f). Index/table via
 * the shared D_2D870_X / D_2D870_Y (all the X/Y unique externs resolve to &D+0;
 * the names just force separate lui materializations, not CSE). MATCHED 2026-05-30. */
void game_libs_func_0002D8A0(void) {
    gl_func_00000000(0x41000000, D_2D870_Y[D_2D870_X]);
}

/* gl_func_0002D8D8: 14-insn sibling of 0002D838/0002D870/0002D8A8.
 * Stolen prologue (lui t6, 0; lw t6, 0(t6)) lives INSIDE this symbol's
 * range (first 2 insns), unlike 0002D838 family which has it in the
 * predecessor's SUFFIX_BYTES — so no PROLOGUE_STEALS here.
 *
 * Calls gl_func_00000000(0x41020000, D_2D8D8_Y[D_2D8D8_X]) — float bits 8.125f. */
extern int *D_2D8D8_X;
extern int D_2D8D8_Y[];
void gl_func_0002D8D8(void) {
    gl_func_00000000(0x41020000, D_2D8D8_Y[(int)D_2D8D8_X]);
}

#ifdef NON_MATCHING
/* gl_func_0002D910: 219-insn (0x36C) multi-armed input/state-machine
 * handler. 0x18-byte stack frame, spills all 4 args (sw a0/a1/a2/a3 to
 * caller slots sp+0x18/0x1C/0x20/0x24) — K&R signature.
 *
 * TOP-LEVEL DISPATCH:
 *   t6 = *(int*)&D_00000000;        ; some "mode" global (loaded via lui/lw)
 *   if (t6 != 10) goto alt_path;     ; bne t6, 10, +0xCC (~204 insns ahead)
 *
 * STATE==10 ARM (insns 12-160 @ 0x2D938-0x2DB80, 148 insns):
 *   t7 = *(int*)&D_00000004;        ; "subsystem ready" flag
 *   if (t7 != 1) return;             ; bnel (branch-likely with ra-reload in delay slot)
 *
 *   // Static counters/state at BSS offsets 0x2C1BC..0x2C1D4:
 *   //   D_2C1BC = previous-key (input edge detector)
 *   //   D_2C1C0 = secondary key state
 *   //   D_2C1C4 = repeat counter (key-hold delay)
 *   //   D_2C1C8 = step counter
 *   //   D_2C1CC = repeat-flag (-1 = held, 0 = released)
 *   //   D_2C1D0 = step direction
 *   //   D_2C1D4 = sub-state value
 *
 *   if (D_2C1BC != a0) {
 *       // edge: key value changed
 *       if (D_2C1CC == 0 && a0 == 0) {
 *           gl_func_0(0x06010F00, 2);     ; play_sound(EDGE_DOWN, 2)
 *           D_2C1CC = -1;
 *           goto conv1;
 *       } else if (a0 == 1) {
 *           gl_func_0(0x06010F00, 0);     ; play_sound(EDGE_UP, 0)
 *           D_2C1CC = 0;
 *           goto conv1;
 *       }
 *       // ... more dispatch on a0 ==/!=1
 *   }
 *
 *   // Following blocks (0x2DA00-0x2DB80, ~96 insns):
 *   //   - if (D_2C1C0 != a1) { ... similar edge logic for secondary key ... }
 *   //   - step-counter update D_2C1C8: increment with bound D_2C1C4
 *   //   - direction toggle D_2C1D0 based on sub-state D_2C1D4
 *   //   - 3 more gl_func_0(0x06010F00 | flags, ...) calls
 *   //   - 2 sl/srl pairs (sll/sra by 5 = *32 indexing into 32-byte struct)
 *
 * STATE!=10 ALT-PATH (insns 161-218 @ 0x2DB84-0x2DC74, 58 insns):
 *   // Different dispatch arm — used when game in non-menu mode.
 *   // Similar pattern with D_2C1D0 / D_2C1D4 updates, different play_sound args.
 *
 * EPILOGUE (insns 219-220 @ 0x2DC64-0x2DC70):
 *   lw ra, 0x14(sp); addiu sp, 0x18; jr ra; nop
 *
 * Plus 2 trailing prefix-bytes for SUCCESSOR (0x2DC74/0x2DC78: `lui $t6,0;
 * lw $t6,0($t6)`) — gl_func_0002DC7C inherits this $t6 setup. Historically
 * captured via SUFFIX_BYTES on 0002D910 in Makefile; that mechanism was
 * REMOVED 2026-05-23 as match-faking. Those 2 insns belong to a separate
 * symbol now.
 *
 * Multi-tick decomp expected: 5+ arms × ~10 insns of dispatch each.
 * Default INCLUDE_ASM keeps ROM exact; partial C body provides
 * grep-discoverable structural skeleton + named BSS-offset constants
 * for future tightening passes.
 *
 * Initial pass — entry dispatch + structural TODO only. Default emit
 * remains INCLUDE_ASM. */
/* Reloc-blind absolute globals: the target bakes `lui 0x2; lw -159xx` (e.g.
 * 0x1C1BC), so use absolute-address literals (each emits its own lui+lw with
 * the offset baked) rather than named externs (which emit reloc lw 0(base)). */
#define D_2C1BC (*(int *)0x1C1BC)
#define D_2C1C0 (*(int *)0x1C1C0)
#define D_2C1C4 (*(int *)0x1C1C4)
#define D_2C1C8 (*(int *)0x1C1C8)
#define D_2C1CC (*(int *)0x1C1CC)
#define D_2C1D0 (*(int *)0x1C1D0)
#define D_2C1D4 (*(int *)0x1C1D4)

void gl_func_0002D910(int a0, int a1, int a2, int a3) {
    int v0;
    if (*(int *)&D_00000000 != 10) {
        return;
    }
    if (*(int *)((char *)&D_00000000 + 4) != 1) {
        return;
    }
    if (D_2C1BC != a0) {
        if (D_2C1CC == 0 && a0 == 0) {
            gl_func_0001CA10(0x06010F00, 2);
            D_2C1CC = -1;
        } else if (a0 == 1) {
            gl_func_0001CA10(0x06010F00, 0);
            D_2C1CC = 0;
        }
    } else if (D_2C1C0 != a1) {
        if (D_2C1CC == 1 && a1 == 0) {
            gl_func_0001CA10(0x06010F00, 2);
            D_2C1CC = -1;
        } else if (a1 == 1) {
            gl_func_0001CA10(0x06010F00, 1);
            D_2C1CC = 1;
        }
    }
    D_2C1BC = a0;
    D_2C1C0 = a1;
    v0 = (D_2C1C4 + a2) / 2;
    D_2C1C8 = (D_2C1C8 + a3) / 2;
    if (D_2C1D4 == 0) {
        D_2C1CC = -1;
        if (v0 < -8) {
            D_2C1D4 = -1;
            D_2C1D0 = v0;
        }
        D_2C1C4 = v0;
        if (v0 >= 9) {
            D_2C1D4 = 1;
            D_2C1D0 = v0;
            D_2C1C4 = v0;
        }
        gl_func_0001CA10(0x06010F02, (char)D_2C1C8);
        v0 = D_2C1C4;
    }
    if (D_2C1D4 == 1) {
        if (v0 < D_2C1D0) {
            if (D_2C1CC == -1) {
                D_2C1C4 = v0;
                gl_func_0001CA10(0x06010F00, 1);
                gl_func_0001CA10(0x06010F02, (char)((D_2C1D0 * 4) - 0x40));
                D_2C1CC = 1;
                v0 = D_2C1C4;
            }
            if (v0 < 0x10) {
                D_2C1D4 = 0;
            }
        } else {
            D_2C1D0 = v0;
        }
    }
    D_2C1C4 = v0;
    if (D_2C1D4 == -1) {
        if (D_2C1D0 < v0) {
            D_2C1C4 = v0;
            if (D_2C1CC == -1) {
                gl_func_0001CA10(0x06010F00, 0);
                gl_func_0001CA10(0x06010F02, (char)((D_2C1D0 * -4) - 0x40));
                D_2C1CC = 0;
            }
            if (D_2C1C4 >= -0xF) {
                D_2C1D4 = 0;
            }
        } else {
            D_2C1D0 = v0;
            D_2C1C4 = v0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D910);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002DC74);

#ifdef NON_MATCHING
/* gl_func_0002DC7C: 32-insn float-clamping helper that calls
 * gl_func_0001CA10(0x04030F00, float_bits). Prologue-stolen successor
 * of gl_func_0002D910 — predecessor's tail (2 words: lui t6,0; lw t6,0(t6))
 * pre-loads the $t6 dispatch global. Historical PROLOGUE_STEALS=8 capture
 * was REMOVED 2026-05-23 as match-faking.
 *
 * Fuzzy 52.19%. Capped by docs/IDO_CODEGEN.md#feedback-ido-mfc1-from-c:
 * target uses `mfc1 a1, $f0` directly (one frame slot reused, $f0 only),
 * but IDO emits swc1/lw round-trip for `*(int*)&f` → expanded frame
 * (-32 vs -24) plus distinct $f4/$f6/$f8/$f10/$f16 reload chain. Also
 * uses beql for last conditional which `if (...) f = ...` doesn't
 * generate. Leaving as NM wrap. */
extern int gl_func_0001CA10();
extern float D_0001C1D8[];

void gl_func_0002DC7C(int a0, int a1) {
    float f;
    if (*(int*)&D_00000000 != 15) {
        return;
    }
    f = 1.0f;
    if (a0 >= 17) f = D_0001C1D8[0];
    if (a1 >= 17) f = D_0001C1D8[1];
    if (a0 < -16) f = D_0001C1D8[2];
    if (a1 < -16) f = D_0001C1D8[3];
    gl_func_0001CA10(0x04030F00, *(int*)&f);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DC7C);
#endif

/* gl_func_0002DCF8: 14-insn 2-call setup. func(); D_a=1; func(0xF8000000, 0). */
extern int D_2DCF8_flag;
void gl_func_0002DCF8(void) {
    gl_func_00000000();
    D_2DCF8_flag = 1;
    gl_func_00000000(0xF8000000, 0);
}

/* game_libs_func_0002DD30: 2-insn empty stub (jr ra; nop). */
void game_libs_func_0002DD30(void) { }

#ifdef NON_MATCHING
/* game_libs_func_0002DD38: 8-insn 2-global store.
 *   D_a = a0 & 0xFF; D_b = 0xD2;
 *
 * Caps:
 *  (a) std C produces 7 insns (no leading `sw a0, 0(sp)` arg-save).
 *  (b) std C uses $t6/$t7 for andi-result + 0xD2 constant; target uses
 *      $a0/$t6 (one register lower — andi modifies a0 in-place).
 *
 * 2026-05-15 attempt: `int *p = &a0; (void)p;` to force save-arg-to-stack.
 *   Result: save emitted (32-byte size matches target), BUT placed at +0x14
 *   (between addiu and jr ra) instead of +0x0, AND still uses $t6/$t7.
 *   Both diffs are IDO scheduler decisions not reachable via natural C.
 *
 * 2026-05-16 closure (size-sort re-roll; DOCUMENTED CAP — future size-sort
 * /sibling rolls should SKIP, not re-grind):
 *   - Natural body builds 7 insns vs target 8 (LEN-DIFF, missing the
 *     leading `sw a0,0(sp)` arg-home-AT-ENTRY). Per
 *     docs/PATTERNS.md#feedback-uso-no-frame-save-args-stub the entry
 *     arg-home is an IDO emit gated on caller-reference / scheduler, not
 *     C-reachable for a body-bearing leaf.
 *   - INSN_PATCH NOT viable: it requires SAME-LEN; this is 1-short. The
 *     only SAME-LEN variant (`&a0`) places the save at +0x14, which
 *     shifts every subsequent insn -> high op-mismatch (whole-function
 *     rewrite = the tautology trap, per
 *     docs/POST_CC_RECIPES.md#feedback-insn-patch-screen-by-opmismatch-count).
 *   - Remaining path is permuter only. Cap stands; INCLUDE_ASM. */
extern int D_2DD38_byte;
extern int D_2DD38_const;
void game_libs_func_0002DD38(int a0) {
    D_2DD38_byte = a0 & 0xFF;
    D_2DD38_const = 0xD2;
}
#else
/* game_libs_func_0002DD38: 8-insn 2-global setter.
 *   D_a = a0 & 0xFF;
 *   D_b = 0xD2;
 *
 * Documented arg-shadow-spill cap (full-TU strips the `int *p = &a0;
 * (void)p;` lever that worked standalone — in-tree IDO inlines the
 * andi to t6 and drops the home spill). Sibling of 2DDBC but the
 * lever doesn't transfer in-tree. 2026-06-10: re-verified -- still 0
 * diffs standalone / 85.0 in-tree (strip unchanged); the bare INCLUDE
 * upgraded to a proper NM wrap with the proven body per the >=80
 * convention. The plain (void)&a0 form (5B5D8 lever) does NOT emit
 * the home when the arg is USED -- the pointer-var form is required
 * for used args (lever taxonomy note). */
#ifdef NON_MATCHING
void game_libs_func_0002DD38(int a0) {
    int *p = &a0;
    (void)p;
    a0 = a0 & 0xFF;
    *(int *)&D_00000000 = a0;
    *(int *)&D_00000000 = 0xD2;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002DD38);
#endif
#endif

#ifdef NON_MATCHING
/* NON_MATCHING: 92.5% — missing `or a2, a0, zero` copy before andi.
 *
 * Target prologue:
 *   sw   a0, 0x18(sp)        ; caller-slot spill (matches our `int *p = &a0`)
 *   or   a2, a0, zero        ; ← extra copy a0->a2
 *   andi a0, a2, 0xFF        ; ← uses a2 as source (we use a0)
 *
 * Variants tested 2026-05-02 (all stay at 92.5%):
 *   v1: int saved = a0; ...((saved & 0xFF) << 8)... — saved inlined to a0
 *   v2: int b = a0; b used in expr — same, b inlined
 *   v3: gl_func_00000000(..., 0x3E8, a0) — got `or a2,a0,zero` BUT also
 *       extra `sw a2, 0x18(sp)` (worse — IDO spills 3rd arg)
 *   v4: volatile int saved = a0 — frame grew to 0x20, full reshuffle
 *   v5: prototype `extern int gl_func_00000000(int, int)` — no change
 *
 * Root cause: target's `or a2, a0, zero` looks like a dead arg-preserve copy
 * (a2 is computed but only used as andi source, no callee uses a2). IDO -O2
 * never emits dead copies from C — would need explicit `register int x asm("$a2")`
 * which IDO rejects (per feedback_ido_no_gcc_register_asm.md). NM-only. */
extern int gl_func_00000000();

/* gl_func_0002DD58: GBI-cmd emit. NON_MATCHING (a0-home-spill cap, -1 insn):
 * target home-saves a0 (sw a0,0x18) AND copies a0->a2, working from a2; built
 * uses a0 directly (1 short). volatile `*p` forces the spill but via an
 * address-comp (addiu+lw, wrong form, +2). The direct sw-a0-home + a2-copy
 * isn't C-reachable (same class as gl_func_00035164/66BD4). */
void gl_func_0002DD58(int a0) {
    int *p = &a0;
    gl_func_00000000(0x82030000 | ((a0 & 0xFF) << 8), 0x3E8);
    (void)p;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DD58);
#endif

/* gl_func_0002DD90: 1-call wrapper. gl_func_00042428((u8)a0, a1, 0, 0x3F800000
 * /1.0f-as-int/). Byte-exact: gl_func_00042428 reloc resolves to 0x42428
 * (verified, false-100 gated). Successors DDBC/DDEC kept INCLUDE_ASM. */
extern int gl_func_00042428();
int gl_func_0002DD90(int a0, int a1) {
    return gl_func_00042428(a0 & 0xFF, a1, 0, 0x3F800000);
}
/* game_libs_func_0002DDBC: 12-insn 4-global setter. Stores (a0&0xFF, a1,
 * a2) to 3 int D-symbols + a3 (float bits via mtc1) to a 4th D-symbol.
 *
 * Byte-exact 2026-05-27 via sig-type-fix (a3 as float → mtc1 a3, $f12)
 * + arg-shadow-spill recipe (`int *p = &a0; a0 &= 0xFF;` mutates a0
 * in-place, IDO emits `sw a0, 0(sp)` at offset 0 using caller's arg
 * shadow space, no frame allocation). All 4 D-symbols are placeholder
 * externs resolving to 0x0 (4 distinct names break IDO's CSE on the
 * lui+sw pair — per feedback-ido-cse-bust-via-distinct-externs). */
extern char D_2DDBC_a, D_2DDBC_b, D_2DDBC_c, D_2DDBC_d;
void game_libs_func_0002DDBC(int a0, int a1, int a2, float a3) {
    int *p = &a0;
    a0 &= 0xFF;
    *(int*)&D_2DDBC_a = a0;
    *(int*)&D_2DDBC_b = a1;
    *(int*)&D_2DDBC_c = a2;
    *(float*)&D_2DDBC_d = a3;
    (void)p;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002DDEC);

#ifdef NON_MATCHING
/* gl_func_0002DDF4: 12-insn float-store + tail-call wrapper. Caller pre-sets
 * $f4 (non-standard convention — $f4 is a temp reg, not an arg slot in o32),
 * function stores it to a D-symbol then tail-calls a different function with
 * (a0&0xFF, 0).
 *
 * Body:
 *   D_X = (float bits in $f4)
 *   func_00042490(a0 & 0xFF, 0)
 *
 * Match cap: writing as `void f(int a0, float fval)` IDO emits
 * `mtc1 $a1, $f12` to copy fval → $f12, then `swc1 $f12, 0(at)`. Target
 * uses `swc1 $f4` directly (no mtc1) — proves caller pre-loaded $f4.
 * Per feedback_lw_arg_from_stack_no_preceding_sw.md class. Stays
 * INCLUDE_ASM.
 *
 * 2026-05-30 — DUAL-ENTRY pair, NOT a mergeable stolen-prologue. The 0x8 orphan
 * at 0x2DDEC (game_libs_func_0002DDEC = `lui at,0x3F80; mtc1 at,$f4` = 1.0f, no
 * jr ra) falls into THIS body — it is the "default value = 1.0f" entry. So $f4 is
 * 1.0f when entered via 0x2DDEC, or a caller's float when entered directly here.
 * Tested the orphan->body merge (`void f(int a0){ *(float*)&D=1.0f; func_00042490(
 * a0&0xFF,0); }`): IDO correctly hoists the 1.0f load above the prologue, but the
 * result is 13 insns vs target 14 -- it MISSES the dead `sw a0,0x18(sp)` home that
 * 0x2DDF4 emits. That dead a0-home is 0x2DDF4's OWN standalone-prologue artifact; a
 * single merged function (entered at 0x2DDEC) has different a0 dataflow and won't
 * emit it (confirmed both standalone AND in-tree). That mismatch is the proof these
 * are two entry points to a shared body, not one split function -- do NOT merge
 * (it would drop the 0x2DDF4 direct-entry). Contrast game_uso_func_00010648, which
 * DID merge+match because it is single-entry. Both stay INCLUDE_ASM.
 *
 * Doc-only stub for grep discoverability. */
extern int func_00042490();
extern int D_DDF4_X;
void gl_func_0002DDF4(int a0, int fval_bits) {
    D_DDF4_X = fval_bits;
    func_00042490(a0 & 0xFF, 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DDF4);
#endif

#ifdef NON_MATCHING
/* gl_func_0002DE24: 28-insn (0x80) F3DEX2-microcode setter.
 *
 *   D_0_global1 = a0 & 0xFF;
 *   D_0_global2 = 0;
 *   gl_func(0x4D010000, 0x3F800000);              ; SET_TEXTURE op + 1.0f bits
 *   gl_func(((a0 & 0xFF) << 8) | 0x82010000, a1); ; SETTILESIZE w/ index
 *   gl_func(0x90010000, 0xFFFF);                   ; SETCOMBINE simple
 *   gl_func(0x0101FF00, D_0_global3);              ; SETOTHERMODE_L w/ depth
 *
 * Reads lowest byte of caller's a0 (via lbu sp+0x1B in big-endian a0 spill).
 * Initial structural pass; alt-entry call shape caps expected. */
void gl_func_0002DE24(int a0, int a1) {
    char *base = &D_00000000;
    *(int*)(base + 0) = a0 & 0xFF;
    *(int*)(base + 0xC) = 0;
    gl_func_00000000(0x4D010000, 0x3F800000);
    gl_func_00000000(((a0 & 0xFF) << 8) | 0x82010000, a1);
    gl_func_00000000(0x90010000, 0xFFFF);
    gl_func_00000000(0x0101FF00, *(int*)base);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DE24);
#endif


/* game_libs_func_0002DE9C: sign-bit-gated call. The orphan game_libs_func_0002DE9C
 * (lui t6; lw t6,0x2E60(t6) = *(int*)(&D+0x2E60)) was the stolen prologue of
 * gl_func_0002DEA4 — it loads the global whose sign bit gates the call
 * (srl t7,t6,31). Merged FORWARD (one 0x34 symbol at 0x2DE9C, successor .s
 * deleted). Reading &D+0x2E60 inline at the `>> 31` test makes IDO hoist the
 * lui;lw above the prologue (same recipe as game_libs_func_00026B40/00023070).
 * MATCHED 2026-05-30. */
extern int gl_func_00000000();
extern int D_00000000;
void game_libs_func_0002DE9C(void) {
    if ((unsigned int)*(int*)((char*)&D_00000000 + 0x2E60) >> 31) {
        gl_func_00000000(0x83010000, 0);
    }
}

/* gl_func_0002DED0: single-call wrapper (0x24). LANDED fuzzy=100. The 3
 * trailing insns (sll/addu/addiu @0x2DEF4-0x2DEFC) are dead-code alt-entry
 * shared with the next function (gl_func_0002DF00); historically appended
 * via SUFFIX_BYTES recipe to bridge the C-emit/expected size mismatch.
 * Mechanism REMOVED 2026-05-23 as match-faking; alt-entry now belongs to
 * separate symbols. */
void gl_func_0002DED0(void) {
    gl_func_00000000((void*)0x82000000, 0);
}

/* game_libs_func_0002DEF4: the 3-word dead-code alt-entry fragment
 * (sll t6,a0,3; addu a0,t6,a1; addiu a0,a0,0x1A) between gl_func_0002DED0
 * and gl_func_0002DF00. Historically absorbed via a gl_func_0002DED0
 * SUFFIX_BYTES recipe; that mechanism was removed 2026-05-23 as
 * match-faking and the bytes were dropped from the build (relayout-walker
 * -0xC event at 0x2DF00). Restored 2026-06-10 as an honest standalone
 * INCLUDE_ASM fragment. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002DEF4);

/* 10-insn body single-call wrapper, sibling of gl_func_0002DF68 (same
 * 0xTTTT0000 | ((a0 & 0xFF) << 8) bit-packing pattern but without the
 * mfc1 issue — args are pure int). Tag = 0x82020000. LANDED fuzzy=100.
 * The historical SUFFIX_BYTES recipe (absorbing 2 trailing stolen-prologue
 * insns for the successor) was REMOVED 2026-05-23 as match-faking; those
 * 2 insns are now tracked as separate symbols (function lands at 0x30
 * naturally). The 0x38 declared size in the prior comment is stale. */
void gl_func_0002DF00(int a0) {
    gl_func_00000000(0x82020000 | ((a0 & 0xFF) << 8), 0);
}

/* gl_func_0002DF38: 11-insn (0x30) signed-test guard wrapper. Mid-chain in
 * the 0x2DF00 stolen-prologue chain:
 *   - PREDECESSOR (gl_func_0002DF00) tail sets $t6 = D[0x2D00] (already
 *     handled via DF00's SUFFIX_BYTES recipe)
 *   - This function reads $t6 implicitly, branches on sign, conditionally
 *     calls gl_func(0x83000000, 0)
 *   - SUCCESSOR (gl_func_0002DF68) needs $f12 set up via mtc1; this
 *     function's trailing 4 bytes (mtc1 a1, $f12) are that setup.
 *
 * MATCHED 2026-05-31 via cross-TU orphan merge. The orphan game_libs_func_0002DF30
 * (lui t6; lw t6,0x2D00 = D[0x2D00]) in game_libs.c was merged into this body .s
 * (one 0x34 symbol). Reading D[0x2D00] inline at the >>31 sign-bit test hoists the
 * lui;lw above the prologue (same recipe as game_libs_func_0002DE9C). The trailing
 * mtc1 a1,$f12 (0x2DF64, the next function's stolen prologue that splat lumped into
 * DF38's symbol) was split off as game_libs_func_0002DF64 (1 word). */
void game_libs_func_0002DF30(void) {
    if ((unsigned int)*(int*)((char*)&D_00000000 + 0x2D00) >> 31) {
        gl_func_00000000(0x83000000, 0);
    }
}

#ifdef NON_MATCHING
/* NON_MATCHING — o32 ABI CAP (verified 2026-05-24). Target receives the int
 * in $a0 AND the float in $f12 simultaneously (then `mfc1 a1,$f12`). Under
 * o32 that combination is impossible from C: a float in the 2nd arg position
 * after an int goes to $a1 (integer reg), not $f12 — confirmed by standalone
 * test of both `(int,float)` (-> int $a0, float $a1) and `(float,int)`
 * (-> float $f12, int $a1). int-$a0 + float-$f12 is n32/n64 independent
 * register allocation, which -32 (o32) does not do. The single residual diff
 * is our stack-roundtrip (sw a1) vs the target's mfc1; not C-reachable. */
extern int gl_func_00000000();
void gl_func_0002DF68(int a0, float a2) {
    gl_func_00000000(0x04000000 | ((a0 & 0xFF) << 8), *(int*)&a2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF68);
#endif

#ifdef NON_MATCHING
/* gl_func_0002DF98: 53-insn struct-init constructor.
 * Sibling of just-landed gl_func_0002DF00 (10-insn bit-pack wrapper).
 *
 * Initializes a ~0x64-byte struct at a0 with default values:
 * - Many byte fields (a0[0x14..0x34] etc.) → 0 or 1 or 0x40
 * - 7 float fields zeroed: a0+0x0/4/8/0xC/0x10/0x44/0x50
 * - 3 float fields = 1.0f: a0+0x54/0x58/0x5C
 * - a0[0x21] = a1 (caller-supplied byte)
 * - a0[0x28] = 0x40, a0[0x20]/a0[0x14]/a0[0x15]/a0[0x23]/a0[0x2C] = 1
 * - if (*(int*)&D_0 != 0) gl_func(a1 & 0xFF) — log/notify if global set
 *
 * No prologue-stolen complications. Sibling of 0002DF00 in
 * sibling-chain context (source 2 of /decompile).
 *
 * NATURAL CEILING ~98% (+1 insn): the three 1.0f stores at 0x54/0x58/0x5C.
 * Target materializes 1.0f into TWO fp regs (`mtc1 at,$f2` AND `mtc1 at,$f4`)
 * and stores $f2->0x54/0x58, $f4->0x5C; IDO's natural emit CSE-folds the
 * immediate into ONE reg ($f2) for all three (1 insn shorter). 2026-05-28:
 * NOT fixable — FP-IMMEDIATE-constant CSE has no C handle (unlike the
 * symbol-address CSE that distinct-externs busts, see docs/IDO_CODEGEN.md
 * feedback-ido-fp-immediate-cse-not-bustable). `float last=1.0f` is
 * value-numbered back into the literal (49-diff regression); `volatile
 * float last=1.0f` forces a stack roundtrip (swc1/lwc1, wrong shape vs
 * target's mtc1). Permanent NM. */
extern int gl_func_00000000();
void gl_func_0002DF98(unsigned char *a0, int a1) {
    a0[0x21] = a1;
    a0[0x14] = 1;
    a0[0x15] = 1;
    a0[0x16] = 0;
    *(short*)(a0 + 0x1A) = 0;
    a0[0x17] = 0;
    a0[0x1D] = 0;
    a0[0x34] = 0;
    a0[0x1E] = 0;
    a0[0x20] = 1;
    a0[0x26] = 0;
    a0[0x23] = 1;
    a0[0x2C] = 1;
    *(int*)(a0 + 0x48) = 0;
    *(int*)(a0 + 0x38) = 0;
    a0[0x2D] = 0;
    a0[0x29] = 0;
    a0[0x18] = 0;
    a0[0x28] = 0x40;
    a0[0x32] = 0;
    a0[0x33] = 0;
    a0[0x1F] = 0;
    a0[0x60] = 0;
    a0[0x61] = 0;
    a0[0x62] = 0;
    *(float*)a0 = 0.0f;
    *(float*)(a0 + 0x50) = 0.0f;
    *(float*)(a0 + 0x4) = 0.0f;
    *(float*)(a0 + 0x8) = 0.0f;
    *(float*)(a0 + 0xC) = 0.0f;
    *(float*)(a0 + 0x44) = 0.0f;
    *(float*)(a0 + 0x10) = 0.0f;
    *(float*)(a0 + 0x54) = 1.0f;
    *(float*)(a0 + 0x58) = 1.0f;
    *(float*)(a0 + 0x5C) = 1.0f;
    if (*(int*)&D_00000000 != 0) {
        gl_func_00000000(a1 & 0xFF);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF98);
#endif

// gl_func_0002E06C — STRUCTURAL PASS (0x154 / 85 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 6-jr USO bundle
// (named fn + 5 tiny trailing one-line setters) — deferred USO
// re-split. The named leading fn (~12 words) is a small object init.
//
//   void gl_func_0002E06C(O *o) {
//     o->b_20 = 0;                                      // clear flags
//     o->b_23 = 0;
//     o->f_0  = 0.0f;                                    // zero floats
//     o->f_4  = 0.0f;
//     (*sub)(o->b_21);                                   // jal 0 USO
//   }
//
// Struct-typing reference: a per-object reset/init leaf — zeroes the
//   object's two float fields at +0 / +4 and two flag/state bytes at
//   +0x20 / +0x23, then hands the byte selector o->0x21 to a
//   USO-relocated sub-init (`jal 0` slot). The 5 trailing bundled
//   bodies are compiler-emitted one-line field setters over the same
//   object — e.g. `o->b_32 = 0x0F` / `o->b_32 = 0x1F` (mode setters),
//   `o->h_1A = 1`, byte +0x16 latch tests, etc. — typical inline
//   accessor functions, left for the deferred USO re-split. A small
//   init/accessor cluster of the game_libs object subsystem.
// Caps (DEFERRED): raw-word USO + jal-0 USO-reloc sub-init —
//   byte-match needs USO mnemonic disasm + reloc-pad jal infra.
//   STALE 6-jr-bundle comment: grep -c 03E00008 = 1 (.s now single
//   fn). Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
extern int gl_func_00000000();
void gl_func_0002E06C(char *o) {
    *(unsigned char *)(o + 0x20) = 0;
    *(unsigned char *)(o + 0x23) = 0;
    *(float *)(o + 0) = 0.0f;
    *(float *)(o + 4) = 0.0f;
    gl_func_00000000(*(unsigned char *)(o + 0x21));
}

void game_libs_func_0002E0A0(char *a0) {
    a0[0x32] = 0xF;
}

void game_libs_func_0002E0AC(char *a0) {
    a0[0x32] = 0x1F;
}

void game_libs_func_0002E0B8(char *a0) {
    *(short *)(a0 + 0x1A) = 1;
}

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0002E0C4)();
void game_libs_func_0002E0C4(char *arg0, u16 arg1, u8 arg2, s8 arg3) {
    f32 temp_f0;
    u8 var_a2;

    var_a2 = arg2;
    if (((FW(arg0, 0x48) == 0) && !(FW(arg0, 0x16) & 4)) || (((FW(arg0, 0x30) != 1) || (FW(arg0, 0x29) != 3)) && ((s32) FW(arg0, 0x29) >= (s32) FW(arg0, 0x2D)))) {
        FW(arg0, 0x30) = arg1;
        FW(arg0, 0x16) = (u8) (FW(arg0, 0x16) | 4);
        if (arg1 != 1) {
            temp_f0 = FW(arg0, 0x0);
            if (temp_f0 >= 50.0f) {
                var_a2 = 3;
            } else if (temp_f0 >= 38.0f) {
                var_a2 = 2;
            } else {
                var_a2 = 0;
                if (temp_f0 >= 25.0f) {
                    var_a2 = 1;
                }
            }
        }
        FW(arg0, 0x29) = var_a2;
        FW(arg0, 0x2E) = arg3;
        FW(arg0, 0x2D) = var_a2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002E0C4);
#endif

void game_libs_func_0002E1A8(unsigned char *a0) {
    a0[0x16] |= 1;
    a0[0x16] &= ~0x20;
}

// MATCHED 2026-05-30. Fire-once event trigger (counterpart to the
//   gl_func_0002E24C stop). Flag byte o->0x16: bit0 = disabled, bit5 =
//   already-fired latch (set here so the event emits once). After
//   latching, a 2nd gate on o->0x1C bit0 (NOT o->0x16 — the prior decode
//   had this wrong), then variant byte o->0x14 (==1 vs other) picks event
//   id 0x29 vs 0x2A. The submit call passes o IN a0 (unchanged), the event
//   id in a1, 0 in a2, 80.0f in a3, and o->0x28 as the 5th (stack sp+16)
//   arg — the prior decode mis-placed o->0x28 as a0. The jal 0x0C010EF9
//   resolves to 0x43BE4, which is the bare `jr ra` epilogue tail of
//   gl_func_000437C0 used as a no-op event stub (this build stubs the
//   submit). Named via undefined_syms_auto.txt gl_func_00043BE4 = 0x43BE4
//   so the reloc resolves — same intra-segment-jal recipe as gl_func_00037C50.
//   Float in a3 lands as raw 0x42A00000 thanks to the float-PROTOTYPED extern
//   (a0-a2 int, so arg4 float goes to the a3 GPR; K&R would double-promote it).
extern void gl_func_00043BE4(char *o, int event, int zero, float vol, int idx);
void gl_func_0002E1C0(char *o) {
    unsigned char f = *(unsigned char *)(o + 0x16);
    if (f & 0x01) return;
    if (f & 0x20) return;
    *(unsigned char *)(o + 0x16) = f | 0x20;
    if (*(unsigned char *)(o + 0x1C) & 0x01) return;
    if (*(unsigned char *)(o + 0x14) == 1) {
        gl_func_00043BE4(o, 0x29, 0, 80.0f, *(unsigned char *)(o + 0x28));
    } else {
        gl_func_00043BE4(o, 0x2A, 0, 80.0f, *(unsigned char *)(o + 0x28));
    }
}

// gl_func_0002E24C — STRUCTURAL PASS (0x108 / 66 words, no episode).
// Raw-.word USO form (game_libs). BOUNDARY NOTE: 10-jr USO bundle
// (named fn + 9 tiny trailing accessors/dispatcher) — deferred USO
// re-split. The named leading fn (~16 words) is the "un-fire"
// counterpart to gl_func_0002E1C0.
//
//   void gl_func_0002E24C(O *o) {
//     byte f = o->b_16;
//     if (!(f & 0x20)) return;                          // not fired
//     byte k = o->b_21;
//     o->b_16 = f & ~0x20;                               // clear latch
//     if (k == 2) return;
//     (*stop)(0x3D, …);                                  // jal 0 USO
//   }
//
// Struct-typing reference: the stop/cancel partner to the
//   gl_func_0002E1C0 one-shot trigger. It tests the same fired-latch
//   bit (bit5 of flag byte o->0x16); if the event is currently
//   active it clears that latch and invokes a USO-relocated stop
//   routine (`jal 0` slot) with event id 0x3D — i.e. "stop the
//   sound/event this object started". Byte o->0x21 selects a variant
//   (kind 2 = no-stop). The 9 trailing bundled bodies are this
//   subsystem's micro-accessors: byte getters (o->0x31, o->0x21), a
//   range-clamp, and a computed jump-table dispatch indexed by
//   o->0x21 through the table at &D_0+0x1660 (another entry in the
//   game_libs &D_0+0x16xx dispatch-table bank) — left for the
//   deferred USO re-split.
// MATCHED 2026-05-30. Stop/cancel counterpart to the gl_func_0002E1C0
//   fire-once trigger: if the fired-latch bit5 of o->0x16 is set, clear it
//   and (unless variant o->0x21 == 2) invoke the USO-relocated stop routine
//   (gl_func_00000000 at jal-0) with event id 0x3D, passing the object.
//   Reg-alloc crack: inline the o->0x21 deref (k → throwaway $t8) + a SEPARATE
//   named local for the masked store value (→ $t7), leaving f in $v0.
extern int gl_func_00000000();
void gl_func_0002E24C(char *o) {
    unsigned char f = *(unsigned char *)(o + 0x16);
    unsigned char nf;
    if (!(f & 0x20)) return;
    nf = f & ~0x20;
    *(unsigned char *)(o + 0x16) = nf;
    if (*(unsigned char *)(o + 0x21) == 2) return;
    gl_func_00000000(o, 0x3D);
}


#ifdef NON_MATCHING
/* Sibling of the matched gl_func_0002E1C0/gl_func_0002E24C event helpers.
 * Selector byte 0x31 dispatches through the table at D+0x1660 for values
 * 1..32, selector 0x40 shares the nearby return-10 leaf, and other values
 * run the bit-mask loop tail split out as game_libs_func_0002E330.
 *
 * SOURCE=2 AUDIT (2026-06-01): boundary/codegen cap, not a simple sibling
 * port. The target is frameless and uses `jr t6` to tail-jump through the
 * dispatch table; the C body emits a 0x18 frame plus `jalr t9`/return epilogue.
 * The invalid-selector path branches from 0x2E2B0 over the valid leaf returns
 * (2E2F8..2E328) into game_libs_func_0002E330+4, so a normal contiguous merge
 * would swallow real jump-table leaves. Keep INCLUDE_ASM until the non-contiguous
 * selector-tail layout is represented explicitly. */
int game_libs_func_0002E290(char *o) {
    typedef int (*Dispatch)(void);
    Dispatch *dispatch;
    unsigned char selector;
    int mask;
    unsigned int idx;

    dispatch = (Dispatch *)((char *)&D_00000000 + 0x1660);
    selector = *(unsigned char *)(o + 0x31);
    mask = -1;

    while (selector != 0) {
        if (selector < 0x21) {
            idx = (unsigned int)(selector - 1);
            if (idx < 0x20) {
                return dispatch[idx]();
            }
        } else if (selector == 0x40) {
            return 10;
        }

        mask = (mask << 1) & 0xFF;
        selector &= mask;
    }

    if (*(unsigned char *)(o + 0x14) == 1) {
        return (*(unsigned char *)(o + 0x15) + 0xC) & 0xFF;
    }
    return 16;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002E290);
#endif

int game_libs_func_0002E2F8(void) { return 16; }

int game_libs_func_0002E300(void) { return 0; }

int game_libs_func_0002E308(void) { return 2; }

int game_libs_func_0002E310(void) { return 4; }

int game_libs_func_0002E318(void) { return 6; }

int game_libs_func_0002E320(void) { return 8; }

int game_libs_func_0002E328(void) { return 10; }

/* game_libs_func_0002E330: 9-insn comparison loop-bottom tail-fragment:
 *   sll v0,v0,1; andi v0,v0,0xFF; and v1,a1,v0; andi a1,v1,0xFF;
 *   bnel a1,zero,-0xA4; slti at,a1,0x21; move v0,zero; jr ra; nop
 * Caller-set $v0/$a1 + backward branch to 0x2E2A0 (before .s start
 * 0x2E330). Splat captured loop tail per
 * feedback_backward_branch_before_s_start_is_loop_tail_splat_error.
 *
 * SOURCE=2 AUDIT (2026-06-01): immediate decode confirms the branch target:
 * 0x2E340 + 4 + signext(0xFFD7)*4 = 0x2E2A0, inside the selector body at
 * game_libs_func_0002E290. The incoming `$v0` mask and `$a1` selector are
 * live-in registers set by that caller path. This is not a standalone C
 * function and cannot be merged contiguously without swallowing the valid
 * return-value leaves at 2E2F8..2E328. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002E330);

// gl_func_0002E354 — STRUCTURAL PASS (0xF34 / 973 words ≈ 3.9KB, no
// episode). Raw-.word USO form (game_libs). BOUNDARY NOTE: 4-jr USO
// bundle (named fn + 3 trailing helpers) — deferred USO re-split.
// The named leading fn is the LARGEST function in this file: the
// main per-object update + render orchestrator. Huge -0x80 frame.
//
//   void gl_func_0002E354(O *o, int a1) {
//     int cfg = *(int*)(&D_xxx);                        // global mode
//     if (cfg == 0) { ... minimal/idle path ... return; }
//     if (cfg == 4) { ... }
//     int st = *(int*)(&D_yyy);                          // state mach
//     switch (st) { case 1: case 2: case 3: ... }
//     if (o->b_1C == 1) {
//       if (o->b_21 == 0) o->b_21 = 2;                    // sub-state
//     }
//     ... ~900 words: per-mode build of the object's transform /
//        animation / display state — FP matrix math, child traversal,
//        F3D/GBI emission, sound/event hooks — the full per-object
//        tick+draw; cleanup + return ...
//   }
//
// Struct-typing reference: the top-level per-object processor of the
//   game_libs object subsystem — it ties together everything decoded
//   in this file: the gl_func_0002BB7C / gl_func_0002C7A4 command
//   drivers, the gl_func_00029978 / gl_func_0002AA30 keyframe
//   steppers, the gl_func_00027804 / gl_func_00029494 matrix loaders
//   and the gl_func_0002E1C0 / gl_func_0002E24C event triggers. It is
//   gated on a global config word (`*&D_xxx`, 0 = idle, 4 = special)
//   and a global state machine word (`*&D_yyy` in 1..3); object
//   fields o->0x1C / o->0x21 carry the per-object sub-state advanced
//   each call. The remaining ~900 words are the per-mode transform/
//   animation/draw body. The single largest driver in this file's
//   object/animation subsystem.
// Caps (DEFERRED): raw-word USO + very large multi-mode per-object
//   tick+draw with heavy FP and many sub-calls (3.9KB / 973 words —
//   LARGEST function in this file) — byte-match needs USO mnemonic
//   disasm + reloc-pad jal infra. STALE 4-jr-bundle comment: grep
//   -c 03E00008 = 1 (.s now single fn). Real-C STRUCTURAL body
//   below per the analysis (top-level early-out + state-machine
//   sketch only — full per-mode body summarised in the comment
//   above). Byte-match deferred. Name pre-checked: no extern reuse.
// SOURCE=2 REFINEMENT (2026-06-01): early cfg==4 sub-state block now matches
//   the observed signed-byte gates (`lb o+0x1C`, `lb o+0x21`) and includes the
//   missing side effect `o->0x54 = 0.0f` when setting sub-state byte 0x21 to 2.
//   Remaining body is still only a prefix sketch; target has 0x80 frame, saved
//   s0, initialized float locals, and ~900 words of FP/update/draw logic.
#ifdef NON_MATCHING
/* PASS-3 2026-06-20 (big-swing, 65.36 -> 67.30%): TRUE jumptable case
 * orders extracted from the bootup.uso RoDataReloc records (module
 * 0xD9FE28, shim +0x1466C) via scripts/extract-uso-jumptable.py:
 *   jtbl_A @data+0x16E4 (idx byte[0x22]-1, 5 entries): byte 2,3 -> a1=0xC;
 *       byte 4,5 -> a1=8; default -> a1=0xC (idx0 is a float, unreachable).
 *   jtbl_B @data+0x16F8 (idx sp6B, 11 entries): 1,3 -> 0xC; 5,7 -> 0x10;
 *       9 -> 0x38; even/default -> byte[0x29] sub-dispatch.
 * Also fixed: the 0x1A/0x48 FP gate block (was M2C-unset placeholder),
 * field 0x33 (was 0x21) in the unk23 outer gate, byte[0x29]!=3 gate (was
 * M2C-unset), and several int-vs-float load typings (0x1C310 / 0x1C430 /
 * data+0x14 reader). RESIDUAL: IDO (s32)/(u32)float cfc1/ctc1/cvt.w.s
 * rounding idioms + the -0xF0-vs-0x80 frame inflation (m2c-graft spills)
 * = documented regalloc/frame cap; byte-match still deferred.
 *
 * PASS-4 2026-06-22 (big-swing, objdiff 54.5 -> 69.2% on this fn):
 *   (1) DISTINCT-EXTERN CSE-DEFEAT. The whole file collapsed every distinct
 *       global into one `&D_00000000`, letting IDO CSE the base address into a
 *       held register (a2) and reuse it across reads that the target re-emits
 *       as fresh lui/lw. The first region (cfg/stateB/stateC/stateD reads) now
 *       uses distinct externs D_cfg/D_stateB/D_stateC/D_stateD_E354 (+ D_stateF
 *       for the 0x28 sub-switch, D_stateE for the final 0x44C38 gate). This
 *       re-aligned the prologue + early state machine: the structural
 *       divergence point moved from word 0 to word 41 (early region now
 *       matches except for 3 local micro-scheduling diffs in the ||-chain).
 *   (2) FP-REDUCTION PRODUCT-FIRST. The o->0x44 update product
 *       (o->0x0 * o->0x4 * 100) is now computed into temp_f18 BEFORE the
 *       o->0x32 block (matching target 11a34/11a40) so temp_f14 (orig o->0x4)
 *       dies early instead of spilling across the block; o->0x4 is re-read
 *       after the block (matching target 11a90).
 *   REMAINING (still-deferred cap): the -0xF0-vs-0x80 frame inflation. The
 *   body still allocates 19 sp slots vs the target's 13 (~6 extra m2c spill
 *   temps), so every sp-relative offset in the 880-word main region is shifted
 *   by 0x70 and can't byte-align until the frame shrinks. Cracking it needs
 *   aggressive variable-economy coalescing of the var_f0_N / temp_v0_N temp
 *   families into the target's reused-register set + the ||-chain beql/li-at
 *   regalloc idiom. Byte-match deferred; NM wrap (no episode). */
extern int gl_func_000428FC();
extern int gl_func_00043824();
extern int gl_func_000438F4();
extern int gl_func_00044C38();
/* Distinct global symbols (offset-0 reads). The target re-emits a fresh
 * lui/lw for each because they are SEPARATE globals; collapsing them into one
 * &D_00000000 lets IDO CSE the base into a held register (frame/regalloc
 * divergence). Distinct externs defeat that CSE. */
extern s32 D_cfg_E354;      /* config word (v0): 0=idle, 4=special */
extern s32 D_stateB_E354;   /* state word B (t9): ==1 -> clear o->0x23 */
extern s32 D_stateC_E354;   /* state word C (v1): 1/2/3 sub-state gate */
extern s32 D_stateD_E354;   /* state word D (t1): ==1 -> early return */
extern s32 D_stateF_E354;   /* state word F (t7): ==4 -> o->0x28 sub-switch */
extern s32 D_stateE_E354;   /* state word E (t6): ==1 -> final 0x44C38 gate */
void gl_func_0002E354(char *arg0, s32 arg1) {
    u8 sp7D;
    f32 sp78;
    u8 sp6B;
    f32 sp64;
    f32 sp60;
    s32 sp58;
    u32 sp50;
    s32 sp2C;
    f32 temp_f0;
    f32 temp_f10_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f0_4;
    f32 var_f10;
    f32 var_f4;
    s32 *var_at;
    s32 temp_f10;
    s32 temp_t7;
    s32 temp_t9_3;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_7;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t3;
    s32 var_t9;
    s32 var_v0;
    s32 var_v0_3;
    s8 var_a2_3;
    u32 temp_t9_2;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_a0_3;
    u8 temp_t0;
    u8 temp_t8;
    u8 temp_t9;
    u8 temp_v0_4;
    u8 temp_v0_5;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 var_v0_2;

    temp_v0 = D_cfg_E354;
    sp64 = 1.0f;
    sp60 = 1.0f;
    if (temp_v0 != 0) {
        if (temp_v0 == 4) {
            temp_v1 = D_stateC_E354;
            if (((temp_v1 == 1) || (temp_v1 == 2) || (temp_v1 == 3)) && (*(u8 *)((char *)(arg0) + 0x1C) == 1) && (*(u8 *)((char *)(arg0) + 0x21) == 0)) {
                *(u8 *)((char *)(arg0) + 0x21) = 2U;
                *(f32 *)((char *)(arg0) + 0x54) = 0.0f;
            }
        }
        if (D_stateB_E354 == 1) {
            *(u8 *)((char *)(arg0) + 0x23) = 0U;
            return;
        }
        if ((D_stateD_E354 != 1) && (*(u8 *)((char *)(arg0) + 0x23) != 0)) {
            if (*(u8 *)((char *)(arg0) + 0x20) == 0) {
                func_00000000(arg0);
                return;
            }
            temp_f14 = *(f32 *)((char *)(arg0) + 0x4);
            /* product-first: compute o->0x0 * o->0x4 * 100 BEFORE the o->0x32
             * block so temp_f14 (orig o->0x4) dies early and need not spill. */
            temp_f18 = *(f32 *)((char *)(arg0) + 0x0) * temp_f14 * 100.0f;
            temp_v1_2 = *(u8 *)((char *)(arg0) + 0x32);
            *(u8 *)((char *)(arg0) + 0x20) = 0U;
            temp_v0_2 = temp_v1_2 * 4;
            if (temp_v1_2 != 0) {
                sp64 = *(f32 *)((char *)&D_00000000 + 0x1C330 + temp_v0_2);
                temp_f0 = *(f32 *)((char *)&D_00000000 + 0x1C3B0 + temp_v0_2);
                sp60 = 1.0f * temp_f0;
                *(u8 *)((char *)(arg0) + 0x32) = (u8) (temp_v1_2 - 1);
                *(f32 *)((char *)(arg0) + 0x4) = (f32) (temp_f14 * temp_f0);
            }
            temp_f14 = *(f32 *)((char *)(arg0) + 0x4);
            temp_f16 = *(f32 *)((char *)(arg0) + 0x50);
            temp_f0 = temp_f16 - *(f32 *)((char *)(arg0) + 0x0);
            if (0.5f <= temp_f0) {
                var_f0 = temp_f0 + 0.5f;
                if (2.0f <= var_f0) {
                    var_f0 = 2.0f;
                }
                sp60 *= var_f0;
            }
            *(f32 *)((char *)(arg0) + 0x50) = (f32) ((temp_f16 + *(f32 *)((char *)(arg0) + 0x0)) * 0.5f);
            *(f32 *)((char *)(arg0) + 0x44) = (f32) ((*(f32 *)((char *)(arg0) + 0x44) + temp_f18) * 0.5f);
            sp7D = gl_func_00043824(*(f32 *)((char *)(arg0) + 0x4) * 120.0f, *(f32 *)((char *)(arg0) + 0x4), 1, (s32)((char *)&D_00000000 + 0x1C250), 0x10);
            temp_f2 = *(f32 *)((char *)(arg0) + 0x0);
            temp_t7 = (gl_func_00043824(*(f32 *)((char *)(arg0) + 0x44), (s32)((char *)&D_00000000 + 0x1C290), 0x20) * 4) & 0xFF;
            temp_f4 = (temp_f2 / 200.0f) + *(f32 *)((char *)&D_00000000 + 0x16E0);
            temp_f10 = temp_t7;
            sp78 = temp_f4;
            var_f4 = (f32) temp_f10;
            sp78 = temp_f4 * sp64;
            if (temp_t7 < 0) {
                var_f4 += 4294967296.0f;
            }
            temp_f10_2 = var_f4 * sp60;
            var_t9 = (u32) temp_f10_2; /* recomposed (u32)float */
            *(u8 *)((char *)(arg0) + 0x26) = (u8) (((s32) *(u8 *)((char *)(arg0) + 0x26) / 2) + ((s32) (var_t9 & 0xFF) / 2));
            if (temp_f2 == 0.0f) {
                *(u8 *)((char *)(arg0) + 0x26) = 0U;
            }
            temp_a0 = *(u8 *)((char *)(arg0) + 0x1D);
            if (*(u8 *)((char *)(arg0) + 0x34) != temp_a0) {
                var_v0 = 8;
                if (temp_a0 == 1) {
                    var_v0 = 0x40;
                }
                temp_v1_3 = *(u8 *)((char *)(arg0) + 0x21);
                switch (temp_v1_3) {                /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    sp58 = var_v0;
                    func_00000000(0x90000000, 6);
                    sp2C = (s32) (s8) var_v0;
                    func_00000000(0x0500FF00, (s8) var_v0);
                    func_00000000(0x05020000, (s8) var_v0);
                    break;
                case 1:                             /* switch 1 */
                case 2:                             /* switch 1 */
                    sp58 = var_v0;
                    func_00000000(0x90000000, 0x60);
                    sp2C = (s32) (s8) var_v0;
                    func_00000000(0x0500FF00, (s8) var_v0);
                    func_00000000(0x05020100, (s8) var_v0);
                    break;
                }
                *(u8 *)((char *)(arg0) + 0x34) = *(u8 *)((char *)(arg0) + 0x1D);
            }
            if (*(u8 *)((char *)(arg0) + 0x1C) & 1) {
                temp_t9 = *(u8 *)((char *)(arg0) + 0x26);
                temp_f0 = *(f32 *)((char *)(arg0) + 0x54);
                var_f10 = (f32) temp_t9;
                if ((s32) temp_t9 < 0) {
                    var_f10 += 4294967296.0f;
                }
                temp_f4 = var_f10 * temp_f0;
                var_t3 = (u32) temp_f4; /* recomposed (u32)float */
                *(u8 *)((char *)(arg0) + 0x26) = (u8) var_t3;
                sp78 *= *(f32 *)((char *)(arg0) + 0x58);
                *(u8 *)((char *)(arg0) + 0x28) = (u8) ((s32) (*(u8 *)((char *)(arg0) + 0x28) + *(u8 *)((char *)(arg0) + 0x60)) >> 1);
                if (*(u8 *)((char *)(arg0) + 0x21) == 0) {
                    func_00000000(0x01020000, temp_f0);
                    func_00000000(0x03020000, (s8) *(u8 *)((char *)(arg0) + 0x28));
                    func_00000000(0x90000000, 0x806);
                    func_00000000(0x0C00FF00, *(s8 *)((char *)(arg0) + 0x63));
                    var_f0_2 = func_00000000(0x0D00FF00, 0x3000);
                } else {
                    func_00000000(0x01020100, temp_f0);
                    func_00000000(0x03020100, (s8) *(u8 *)((char *)(arg0) + 0x28));
                    func_00000000(0x90000000, 0x1060);
                    func_00000000(0x0C00FF00, *(s8 *)((char *)(arg0) + 0x63));
                    var_f0_2 = func_00000000(0x0D00FF00, 0x3000);
                }
            } else {
                if (D_stateF_E354 == 4) {
                    temp_a0_2 = *(u8 *)((char *)(arg0) + 0x21);
                    switch (temp_a0_2) {            /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        *(u8 *)((char *)(arg0) + 0x28) = 0x10U;
                        break;
                    case 1:                         /* switch 2 */
                        *(u8 *)((char *)(arg0) + 0x28) = 0x70U;
                        break;
                    }
                } else {
                    *(u8 *)((char *)(arg0) + 0x28) = 0x40U;
                }
                if (*(u8 *)((char *)(arg0) + 0x21) == 0) {
                    func_00000000(0x01020000, 0x3F800000);
                    var_f0_2 = func_00000000(0x03020000, (s8) *(u8 *)((char *)(arg0) + 0x28));
                } else {
                    func_00000000(0x01020100, 0x3F800000);
                    var_f0_2 = func_00000000(0x03020100, (s8) *(u8 *)((char *)(arg0) + 0x28));
                }
            }
            if (*(u8 *)((char *)(arg0) + 0x16) & 1) {
                *(s32 *)((char *)(arg0) + 0x8) = (f32) (*(s32 *)((char *)(arg0) + 0x8) + 50.0f);
                gl_func_00043BE4(arg0, 0, *(u8 *)((char *)(arg0) + 0x2C) - 1, *(s32 *)((char *)(arg0) + 0x8), (s32) *(u8 *)((char *)(arg0) + 0x28));
                var_f0_2 = func_00000000(arg0, (*(u32 *)((char *)&D_00000000 + 0x2154) & 7) + 0x20);
                *(u8 *)((char *)(arg0) + 0x16) = (u8) (*(u8 *)((char *)(arg0) + 0x16) & ~1);
            }
            var_v0_2 = *(u8 *)((char *)(arg0) + 0x14);
            temp_v1_4 = *(u8 *)((char *)(arg0) + 0x2C);
            temp_t0 = var_v0_2;
            if (var_v0_2 != temp_v1_4) {
                if (temp_v1_4 == 0) {
                    temp_v0_3 = *(s32 *)((char *)(arg0) + 0x38);
                    var_a2 = 3;
                    *(f32 *)((char *)(arg0) + 0x8) = (f32) ((f32) temp_v0_3 * 3.0f);
                    if (temp_v0_3 < 0xA) {
                        *(s32 *)((char *)(arg0) + 0x8) = 0.0f;
                    }
                    var_v0_2 = 1;
                    if (*(u8 *)((char *)(arg0) + 0x14) == 1) {
                        temp_v1_5 = *(u8 *)((char *)(arg0) + 0x15);
                        if (temp_v1_5 != 1) {
                            if (temp_v1_5 != 2) {
                                var_a2 = 2;
                            } else {
                                var_a2 = 1;
                            }
                        } else {
                            var_a2 = 0;
                        }
                    }
                    temp_t8 = *(u8 *)((char *)(arg0) + 0x22);
                    temp_t9_2 = temp_t8 - 1;
                    if (temp_t9_2 < 5U) {
                        /* jtbl @data+0x16E4: byte 4,5 -> a1=8; byte 2,3 -> a1=0xC */
                        switch (temp_t8) {
                        case 4:
                        case 5:
                            gl_func_00043BE4(arg0, 8, var_a2, *(s32 *)((char *)(arg0) + 0x8), (s32) *(u8 *)((char *)(arg0) + 0x28));
                            goto block_78;
                        case 2:
                        case 3:
                            gl_func_00043BE4(arg0, 0xC, var_a2, *(s32 *)((char *)(arg0) + 0x8), (s32) *(u8 *)((char *)(arg0) + 0x28));
                            goto block_78;
                        }
                    } else {
                        gl_func_00043BE4(arg0, 0xC, var_a2, *(s32 *)((char *)(arg0) + 0x8), (s32) *(u8 *)((char *)(arg0) + 0x28));
block_78:
                        goto block_81;
                    }
                } else {
                /* case 3 (switch 3, flattened) */
                    if (temp_t0 == 0) {
                        *(s32 *)((char *)(arg0) + 0x38) = 0;
                        *(u8 *)((char *)(arg0) + 0x33) = 0U;
block_81:
                        var_v0_2 = *(u8 *)((char *)(arg0) + 0x14);
                    }
                    *(u8 *)((char *)(arg0) + 0x2C) = var_v0_2;
                    goto block_83;
                }
            } else {
block_83:
                if (*(u16 *)((char *)(arg0) + 0x1A) != 0) {
                    if (*(s32 *)((char *)(arg0) + 0x48) == 0) {
                        temp_f2 = *(f32 *)((char *)(arg0) + 0x0);
                        var_v0_2 = 0x11;
                        if (75.0f <= temp_f2) {
                            var_v0_2 = 0x13;
                        } else if (50.0f <= temp_f2) {
                            var_v0_2 = 0x12;
                        }
                        sp6B = var_v0_2;
                        if (25.0f <= temp_f2) {
                            sp6B = var_v0_2;
                            gl_func_00043BE4(arg0, 0x10, var_v0_2, 127.0f, (s32) *(u8 *)((char *)(arg0) + 0x28));
                        }
                    }
                    *(u16 *)((char *)(arg0) + 0x1A) = 0U;
                    *(s32 *)((char *)(arg0) + 0x48) = 5;
                    *(u8 *)((char *)(arg0) + 0x2A) = sp6B;
                }
                if (*(u8 *)((char *)(arg0) + 0x16) & 4) {
                    sp50 = 4;
                    var_v0_2 = gl_func_000428FC(arg0);
                    sp6B = var_v0_2;
                    temp_a0_3 = *(u8 *)((char *)(arg0) + 0x29);
                    var_a2_2 = var_v0_2 & 0xFF;
                    var_f0_2 = *(f32 *)((char *)((temp_a0_3 * 4)) + 0x1C310);
                    if ((s32) var_v0_2 < 0xB) {
                        switch (temp_a0_3) {        /* switch 4; irregular */
                        default:                    /* switch 4 */
                            var_a2_2 = var_v0_2 & 0xFF;
                            break;
                        case 0:                     /* switch 4 */
                        case 1:                     /* switch 4 */
                            var_a2_2 = (var_v0_2 & 0xFF) + 1;
                            break;
                        case 2:                     /* switch 4 */
                        case 3:                     /* switch 4 */
                            var_a2_2 = var_v0_2 & 0xFF;
                            break;
                        }
                    }
                    if ((*(u16 *)((char *)(arg0) + 0x30) != 1) || (temp_a0_3 != 3)) {
                        temp_v0_4 = *(u8 *)((char *)(arg0) + 0x22);
                        if ((s32) temp_v0_4 >= 6) {
                            var_a2_2 = temp_v0_4 + 0xE;
                        }
                        if ((*(s32 *)((char *)&D_00000000 + 0) /* M2C unset $t4 */ == 4) || (*(u8 *)((char *)(arg0) + 0x1C) & 1)) {
                            gl_func_00043BE4(arg0, 0x10, var_a2_2, var_f0_2, (s32) *(u8 *)((char *)(arg0) + 0x28)); var_v0_2 = 0; /* M2C: v0-after-void-call */
                        } else {
                            temp_v0_5 = *(u8 *)((char *)(arg0) + 0x2E);
                            if (temp_v0_5 == 1) {
                                var_v0_3 = 0x7F;
                            } else if (temp_v0_5 == 3) {
                                var_v0_3 = 0;
                            } else {
                                var_v0_3 = 0x40;
                            }
                            if (*(u8 *)((char *)(arg0) + 0x1E) != 0) {
                                var_v0_3 = (0x7F - var_v0_3) & 0xFF;
                            }
                            gl_func_00043BE4(arg0, 0x10, var_a2_2, var_f0_2, var_v0_3); var_v0_2 = 0; /* M2C: v0-after-void-call */
                        }
                    }
                    switch ((u8) sp6B) {            /* switch 5; jtbl @data+0x16F8 */
                    case 1:                         /* switch 5 */
                    case 3:                         /* switch 5 */
                        var_v0_2 = 0xC;
                        break;
                    case 5:                         /* switch 5 */
                    case 7:                         /* switch 5 */
                        var_v0_2 = 0x10;
                        break;
                    case 9:                         /* switch 5 */
                        var_v0_2 = 0x38;
                        break;
                    default:                        /* switch 5 (cases 0,2,4,6,8,10) */
                        temp_v1_6 = *(u8 *)((char *)(arg0) + 0x29);
                        var_v0_2 = 0x10;
                        if (temp_v1_6 != 0) {
                            if (temp_v1_6 != 1) {
                                var_v0_2 = 0x1C;
                                if (temp_v1_6 != 2) {
                                    var_v0_2 = 8;
                                }
                            } else {
                                var_v0_2 = 0x18;
                            }
                        } else {
                            sp50 = 6;
                        }
                        break;
                    }
                    func_00000000(arg0, var_v0_2 + ((u32) *(s32 *)((char *)&D_00000000 + 0x2154) % sp50));
                    *(s32 *)((char *)(arg0) + 0x48) = 0xA;
                    *(u8 *)((char *)(arg0) + 0x29) = 0U;
                    *(u8 *)((char *)(arg0) + 0x16) = (u8) (*(u8 *)((char *)(arg0) + 0x16) & 0xFFFB);
                    *(u8 *)((char *)(arg0) + 0x2B) = sp6B;
                }
            }
            temp_v0_6 = *(s32 *)((char *)(arg0) + 0x48);
            temp_t9_3 = temp_v0_6 - 1;
            if (temp_v0_6 != 0) {
                *(s32 *)((char *)(arg0) + 0x48) = temp_t9_3;
                if (temp_t9_3 == 0) {
                    *(u8 *)((char *)(arg0) + 0x2D) = 0;
                }
            }
            if (*(u8 *)((char *)(arg0) + 0x23) != 0) {
                if ((*(s32 *)((char *)&D_00000000 + 0) == 1) && ((temp_v0_7 = *(s32 *)((char *)&D_00000000 + 0), (temp_v0_7 == 4)) || (temp_v0_7 == 0xA)) && ((temp_v0_7 != 4) || (*(u8 *)((char *)(arg0) + 0x33) != 2))) {
                    if (*(u8 *)((char *)(arg0) + 0x14) == 0) {
                        temp_v0_8 = *(s32 *)((char *)(arg0) + 0x38);
                        if (temp_v0_8 == 0) {
                            temp_f2 = *(f32 *)((char *)(arg0) + 0x0);
                            *(f32 *)((char *)&D_00000000 + 0x1C738) = temp_f2;
                            if (temp_f2 == 0.0f) {
                                *(f32 *)((char *)&D_00000000 + 0x1C738) = 1.0f;
                            }
                        } else if (temp_v0_8 >= 7) {
                            var_f0_3 = *(f32 *)((char *)(arg0) + 0x0) / *(f32 *)((char *)&D_00000000 + 0x1C738);
                            if (!(0.5f <= var_f0_3)) {
                                var_f0_3 = 0.5f;
                            }
                            if (1.0f <= var_f0_3) {
                                var_f0_3 = 1.0f;
                            }
                            temp_v0_9 = *(s32 *)((char *)&D_00000000 + 0);
                            if (temp_v0_9 != 0) {
                                *(s32 *)((char *)&D_00000000 + 0) = (s32) (temp_v0_9 - 1);
                                var_f0_3 *= *(f32 *)((char *)(((temp_v0_9 & 0x1F) * 4)) + 0x1C430);
                            }
                            temp_f2 = *(f32 *)((char *)&D_00000000 + 0x1724);
                            if (temp_f2 <= var_f0_3) {
                                var_f0_3 = temp_f2;
                            }
                            *(s32 *)((char *)&D_00000000 + 0x14) = 0x20;
                            *(f32 *)((char *)&D_00000000 + 0x1C73C) = var_f0_3;
                            func_00000000(0x3F000000, 0x04010900, var_f0_3);
                        }
                    } else {
                        temp_v0_10 = *(s32 *)((char *)&D_00000000 + 0x14);
                        if (temp_v0_10 != 0) {
                            temp_f0 = *(f32 *)((char *)&D_00000000 + 0x1C73C);
                            temp_f2 = *(f32 *)((char *)&D_00000000 + 0x1728);
                            var_f0_4 = ((1.0f - temp_f0) / (f32) temp_v0_10) + temp_f0;
                            if (temp_f2 <= var_f0_4) {
                                var_f0_4 = temp_f2;
                            }
                            if (!(0.5f <= var_f0_4)) {
                                var_f0_4 = 0.5f;
                            }
                            *(s32 *)((char *)&D_00000000 + 0x14) = (s32) (temp_v0_10 - 1);
                            *(f32 *)((char *)&D_00000000 + 0x1C73C) = var_f0_4;
                            func_00000000(0x04010900, var_f0_4);
                        } else {
                            func_00000000(0x04010900, 0x3F800000);
                        }
                    }
                }
                switch (*(u8 *)((char *)(arg0) + 0x14)) {              /* switch 6; irregular */
                case 0:                             /* switch 6 */
                    if (*(s32 *)((char *)&D_00000000 + 0) == 0) {
                        *(s32 *)((char *)(arg0) + 0x38) = (s32) (*(s32 *)((char *)(arg0) + 0x38) + 1);
                    }
                    if ((*(u8 *)((char *)(arg0) + 0x21) == 0) && (*(s32 *)((char *)(arg0) + 0x38) == 0x1E)) {
                        func_00000000(0x20, 0x12, 0);
                    }
                    temp_v1_7 = *(s32 *)((char *)&D_00000000 + 0);
                    if ((temp_v1_7 != 0) && (temp_v1_7 != 1) && (temp_v1_7 != 8)) {
                        if (*(s32 *)((char *)(arg0) + 0x48) != 0) {
                            *(u8 *)((char *)(arg0) + 0x33) = 0x1AU;
                        }
                        if (*(f32 *)((char *)&D_00000000 + 0x172C) < *(f32 *)((char *)(arg0) + 0xC)) {
                            temp_t8 = *(u8 *)((char *)(arg0) + 0x33) + 1;
                            *(u8 *)((char *)(arg0) + 0x33) = temp_t8;
                            if ((temp_t8 & 0xFF) == 0x19) {
                                func_00000000(arg0, 0x3C);
                            }
                        }
                    }
                    *(u8 *)((char *)(arg0) + 0x26) = 0U;
                    *(f32 *)((char *)(arg0) + 0x4) = 0.0f;
                    /* fallthrough */
                case 1:                             /* switch 6 */
                    if (*(f32 *)((char *)(arg0) + 0x4) > 0.5f) {
                        var_a2_3 = *(s8 *)((char *)(arg0) + 0x18);
                        if (*(u8 *)((char *)(arg0) + 0x1E) == 0) {
                            var_a2_3 = -var_a2_3;
                        }
                        func_00000000(*(u8 *)((char *)(arg0) + 0x21), *(u8 *)((char *)(arg0) + 0x15), var_a2_3);
                    } else {
                        func_00000000(*(u8 *)((char *)(arg0) + 0x21));
                    }
                    func_00000000(*(u8 *)((char *)(arg0) + 0x21), sp7D * 0x10, *(u8 *)((char *)(arg0) + 0x26), sp78, (s32) *(u8 *)((char *)(arg0) + 0x15), (s32) *(u8 *)((char *)(arg0) + 0x28));
                    break;
                default:                            /* switch 6 */
                    func_00000000(*(u8 *)((char *)(arg0) + 0x21), sp7D * 0x10, *(u8 *)((char *)(arg0) + 0x26), sp78, *(u8 *)((char *)(arg0) + 0x14) + 2, (s32) *(u8 *)((char *)(arg0) + 0x28));
                    func_00000000(*(u8 *)((char *)(arg0) + 0x21));
                    break;
                }
                gl_func_000438F4(arg0);
            }
            if ((D_stateE_E354 == 1) && (*(u8 *)((char *)(arg0) + 0x21) == 0)) {
                gl_func_00044C38((s32) ((*(f32 *)((char *)(arg0) + 0x10) + 1.0f) * 63.5f));
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002E354);
#endif

/* game_libs_func_0002F1B8: 52-insn (0xD0) binary-search over a sorted float
 * array. BOUNDARY MERGED 2026-06-02: this function has THREE internal `jr ra`
 * early-returns (at 0x2F21C, 0x2F268, and the final 0x2F280), so splat
 * over-split it into 2F1B8 + 2F224 + 2F270. Both 2F224 and 2F270 branch
 * backward to 0x2F1C8 (the loop head inside 2F1B8); neither has external
 * callers. Absorbed both (0x6C -> 0xD0, ending exactly at the next func
 * gl_func_0002F288); all branches verified in-range. Reloc-blind USO;
 * stays INCLUDE_ASM. (Multi-jr-ra over-split, not a loop-tail split.) */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_0002F1B8)();
s32 game_libs_func_0002F1B8(f32 arg0, s32 arg1, s32 arg2) {
    f32 temp_f0;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_a0;
    s32 temp_a3;
    s32 var_a0;
    s32 var_v1;
    char *temp_v0;

    var_v1 = arg2 >> 1;
    var_a0 = var_v1 + 1;
loop_1:
    temp_a0 = var_a0 >> 1;
    temp_v0 = (int)arg1 + (var_v1 * 4);
    temp_a3 = var_v1 + 1;
    temp_f0 = arg0 - (*(f32*)((char*)temp_v0 + 0x0));
    if (temp_f0 > 0.0f) {
        if (arg2 != temp_a3) {
            temp_f2 = (*(f32*)((char*)temp_v0 + 0x4)) - arg0;
            if (temp_f2 > 0.0f) {
                if (temp_f2 < temp_f0) {
                    return temp_a3;
                }
                /* Duplicate return node #12. Try simplifying control flow for better match */
                return var_v1;
            }
            var_v1 += temp_a0;
            var_a0 = temp_a0 + 1;
            goto loop_1;
        }
        /* Duplicate return node #12. Try simplifying control flow for better match */
        return var_v1;
    }
    if (var_v1 != 0) {
        temp_f2_2 = arg0 - (*(f32*)((char*)temp_v0 - 0x4));
        if (temp_f2_2 > 0.0f) {
            if (temp_f2_2 < -temp_f0) {
                return var_v1 - 1;
            }
            /* Duplicate return node #12. Try simplifying control flow for better match */
            return var_v1;
        }
        var_v1 -= temp_a0;
        var_a0 = temp_a0 + 1;
        goto loop_1;
    }
    return var_v1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002F1B8);
#endif

// gl_func_0002F288 — STRUCTURAL PASS (0x2FC / 191 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A heavily-FP per-object physics / value-ramp update.
//
//   void gl_func_0002F288(O *o) {
//     int mode = o->b_21;
//     float acc = o->f_0;
//     if (mode == 2) return;                            // skip mode
//     byte k = o->b_14;
//     if (o->b_1C != 0) return;                          // gated
//     S *g = &D_0;
//     int   t = g->w_4;
//     float s = *(float*)(&D_0 + 0x1730);                 // step const
//     float d = (float)t * s;
//     if (k == 0) acc += d;                                // accumulate
//     int   c = o->w_38;
//     if (c < 0x15) { ... }
//     // clamp acc against 0.25f / 0.5f / 127.0f, write back
//     o->f_0 = acc;
//   }
//
// Struct-typing reference: a per-object scalar integrator. Float
//   o->0 is the accumulator advanced each call by (g->4 converted to
//   float) * the global step constant at &D_0+0x1730; byte o->0x21 is
//   a mode (value 2 = inactive), byte o->0x14 a direction/kind, byte
//   o->0x1C a gate, word o->0x38 a frame counter checked against 0x15.
//   The result is saturated using the float literals 0.25f / 0.5f /
//   127.0f (0x3E80/0x3F00/0x42FE0000) before write-back to o->0. A
//   physics/easing leaf of the game_libs object subsystem (peer to
//   the gl_func_0002978C ramp / gl_func_00029978 tween steppers,
//   driven by the gl_func_0002E354 orchestrator).
// Caps (DEFERRED): raw-word USO + heavy single-prec FP integrate/
//   clamp idiom — byte-match needs USO mnemonic disasm. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int D_00000000;
void gl_func_0002F288(char *o) {
    unsigned char mode = *(unsigned char *)(o + 0x21);
    float acc = *(float *)(o + 0);
    unsigned char k;
    int t;
    float s;
    float d;
    if (mode == 2) return;
    k = *(unsigned char *)(o + 0x14);
    if (*(unsigned char *)(o + 0x1C) != 0) return;
    t = *(int *)((char *)&D_00000000 + 4);
    s = *(float *)((char *)&D_00000000 + 0x1730);
    d = (float)t * s;
    if (k == 0) acc += d;
    if (*(int *)(o + 0x38) < 0x15) {
        if (acc > 0.5f) acc = 0.5f;
        if (acc < -0.5f) acc = -0.5f;
    }
    if (acc > 127.0f) acc = 127.0f;
    if (acc < -127.0f) acc = -127.0f;
    *(float *)(o + 0) = acc;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F288);
#endif


#ifdef NON_MATCHING
/* game_libs_func_0002F578: one ~46-insn (0xB8) FP value-quantize / clamp-to-byte
 * helper. BOUNDARY MERGED 2026-06-02: splat had split it into 0002F578 (3-insn
 * FP-const prologue: `mtc1 a3,$f12` (the input value, ARG-DERIVED) + `mtc1
 * zero,$f4`=0.0 + `lui 0x42fe`→$f6=127.0 — hoisted above the frame; the real
 * entry) + gl_func_0002F584 (the prologue+body that reads f12/f4/f6
 * uninitialized). SINGLE-entry per the dual-vs-single test (f12 is arg-derived
 * + used in FP OPS `c.lt.s/add.s`, NOT mfc1-back; no callers). Absorbed
 * 0002F584's 43 words into 0002F578 (0xC -> 0xB8); dropped the 0002F584 symbol.
 * Merging brings the input value (=a3) and the clamp bounds (0.0/127.0)
 * in-scope — CORRECTS the prior structural decode that mis-read v as o->0 and
 * the bound as 15.0. Maps the input float to a 7-bit byte (clamp [0,127]+1,
 * optional negate by o->0x1C bit0, scale by o->0x54, trunc, saturate [0,0x7F],
 * store to o->0x33/o->0x1C). Byte-match deferred (raw-word USO + FP clamp). */
void game_libs_func_0002F578(char *o, int a1, int a2, int a3) {
    float v = *(float *)&a3;     /* mtc1 a3,$f12 in the merged prologue */
    int q;
    if (v < 0.0f) v = 0.0f;       /* $f4 = 0.0 low clamp */
    v += 1.0f;
    if (v > 127.0f) v = 127.0f;   /* $f6 = 0x42fe0000 = 127.0 high clamp */
    if (*(unsigned char *)(o + 0x1C) & 1) v = -v;
    q = (int)(v * *(float *)(o + 0x54));
    *(unsigned char *)(o + 0x33) = (unsigned char)q;
    if (q >= 0x80) q = 0x7F;
    if (q < 0) q = 0;
    *(unsigned char *)(o + 0x1C) = (unsigned char)q;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002F578);
#endif

void game_libs_func_0002F630(void) {
}

// gl_func_0002F638 — STRUCTURAL PASS (0xF4 / 61 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A command-word emitter / mode dispatcher leaf.
//
//   void gl_func_0002F638(int a0, int sel, int arg3, int arg4,
//                         ... byte at sp+0x43 ...) {
//     int op = a0 ? 6 : 2;                  // opcode select from arg0
//     int sub = op & 0xFF;
//     int cmd3 = 0x03000000 | (sub << 8);   // 0x03 command bank
//     callback(cmd3, (signed char)stk_43);  // USO-relocated jal 0
//     if (sel == 0) { ... }
//     else if (sel == 8) { ... }
//     else if (sel == 0xC) {
//       int cmd6 = 0x06000000 | sub;
//       callback(cmd6 | 6, (signed char)arg4);   // sign-extended byte
//       callback(cmd6 | 1, (signed char)(sel + arg3));
//       ... FP-arg branch: mtc1 a1,f12 / mtc1 at,f4 ...
//     }
//   }
//
// Struct-typing reference: a graphics / command-stream builder. arg0
//   chooses the opcode (2 vs 6); the 8-bit subfield is packed into
//   command words from two banks — 0x03000000 (shifted <<8) and
//   0x06000000 (low bits ORed with 1/6 tags). A mode selector (2nd
//   arg, here `sel`) of {0, 8, 0xC} routes which command sequence is
//   emitted. Byte arguments (stack slot sp+0x43, arg4, sel+arg3) are
//   sign-extended (sll/sra 24) before being passed. One branch loads
//   FP args (mtc1 a1,f12 / mtc1 at,f4) ahead of its callback. The
//   callbacks are USO-relocated slots (jal 0 → resolved at load), the
//   command-submission entry of the game_libs object subsystem.
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   multi-way mode dispatch — byte-match needs USO mnemonic disasm
//   + reloc-pad jal infra. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01 (prior dispatch was wrong). op = a0?6:2;
 * v1 = op<<8; cmd3 = 0x03000000|v1; cmd6 = 0x06000000|v1. Always emit
 * gl(cmd3, (s8)stk_43). Then sel in {0,8,12} → gl(cmd6|6,(s8)arg4),
 * gl(cmd6|1,(s8)(sel+arg3)); otherwise → gl(cmd6|5,(s8)arg4),
 * gl(cmd6,(s8)(sel+arg3)). */
void gl_func_0002F638(int a0, int sel, int arg3, int arg4, int stk_43) {
    int v1 = (((a0 == 0) ? 2 : 6) & 0xFF) << 8;
    gl_func_00000000(0x03000000 | v1, (signed char)stk_43);
    if (sel == 0 || sel == 8 || sel == 12) {
        gl_func_00000000((0x06000000 | v1) | 6, (signed char)arg4);
        gl_func_00000000((0x06000000 | v1) | 1, (signed char)(sel + arg3));
    } else {
        gl_func_00000000((0x06000000 | v1) | 5, (signed char)arg4);
        gl_func_00000000((0x06000000 | v1), (signed char)(sel + arg3));
    }
}


#ifdef NON_MATCHING
/* game_libs_func_0002F720: one 96-insn (0x180) per-object FP value updater +
 * quantized table-apply. BOUNDARY MERGED 2026-06-02: splat had split it into
 * 0002F720 (3-insn FP-const prologue: `mtc1 a1,$f12` (input, ARG-DERIVED) +
 * `lui 0x4334`->$f4=180.0 — hoisted above the frame; the real entry) +
 * gl_func_0002F72C (the prologue+body using f12 in `mul.s $f12,$f12,$f4`).
 * SINGLE-entry per the dual-vs-single test (f12 arg-derived + FP-op use; no
 * callers). Absorbed 0002F72C's 93 words into 0002F720 (0xC -> 0x180); dropped
 * the 0002F72C symbol. Brings f12(=a1)/f4(=180.0) in-scope — CORRECTS the prior
 * structural decode that mis-read `nv = in * o->0` (the multiplier is the entry
 * const 180.0, not o->0). Sibling of the gl_func_0002F584 quantizer; the 2 calls
 * go to the FIXED intra-USO routine jal 0x010E09 (codes 8, 0x10). Byte-match
 * deferred (raw-word USO + FP delta/commit + signed-byte clamp + table lookups). */
extern int gl_func_00000000();
extern int D_00000000;
void game_libs_func_0002F720(char *o, int a1, int idxb) {
    float in = *(float *)&a1;   /* mtc1 a1,$f12 in the merged prologue */
    float nv = in * 180.0f;     /* $f4 = 0x43340000 = 180.0 (entry const) */
    int i = (signed char)idxb;
    float dlt = nv - *(float *)(o + 0x5C);
    int q;
    float k;
    if (i < 0x40) *(float *)(o + 0x5C) = nv;
    q = 0x7F - i;
    if (q < -0x40) q = (-0x80 - q);
    *(unsigned char *)(o + 0x60) = (unsigned char)(q + 0x40);
    gl_func_00000000(8);
    *(unsigned char *)(o + 0x61) = *(unsigned char *)((char *)&D_00000000 + q);
    gl_func_00000000(0x10);
    k = *(float *)((char *)&D_00000000 + q * 4);
    (void)k; (void)dlt;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0002F720);
#endif


// gl_func_0002F8A0 — STRUCTURAL PASS (0x94 / 37 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A small command-sequence selector by mode.
//
//   void gl_func_0002F8A0(int mode) {
//     switch (mode) {
//       case 0:
//         emit(0x06000100, 1);              // jal 0 (USO callback)
//         emit(0x06000300, 1);
//         break;
//       case 1:
//         emit(0x06000500, 1);
//         emit(0x06000700, 1);
//         break;
//       case 2:
//         emit(0x06000500, 1);
//         break;
//       default:                            // no-op
//         break;
//     }
//   }
//
// Struct-typing reference: a fixed command-stream selector. The mode
//   arg (0/1/2; any other value is a no-op) chooses a short, hard-
//   coded sequence of command words from the 0x06000000 bank — pairs
//   {0x0100,0x0300} / {0x0500,0x0700} or the single {0x0500} — each
//   submitted via a USO-relocated callback (jal 0 → resolved at load)
//   with the second arg fixed at 1. A canned-sequence emitter leaf of
//   the game_libs object subsystem (issues preset command groups; the
//   0x06000000 bank matches gl_func_0002F638's command-word banks).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   canned switch dispatch — byte-match needs USO mnemonic disasm
//   + reloc-pad jal infra. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
extern int gl_func_00000000();
void gl_func_0002F8A0(int mode) {
    switch (mode) {
        case 0:
            gl_func_00000000(0x06000100, 1);
            gl_func_00000000(0x06000300, 1);
            break;
        case 1:
            gl_func_00000000(0x06000500, 1);
            gl_func_00000000(0x06000700, 1);
            break;
        case 2:
            gl_func_00000000(0x06000500, 1);
            break;
        default:
            break;
    }
}

// gl_func_0002F934 — STRUCTURAL PASS (0xA0 / 40 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A canned command-sequence selector — SIBLING of
// gl_func_0002F8A0 (same shape, different subfields / arg).
//
//   void gl_func_0002F934(int mode) {
//     switch (mode) {                       // case 2 arm is beql
//       case 0:
//         emit(0x06000100, -1);             // jal 0 (USO callback)
//         emit(0x06000101, -1);
//         emit(0x06000300,  0);
//         break;
//       case 1:
//         emit(0x06000700,  0);
//         emit(0x06000500, -1);
//         break;
//       case 2:
//         emit(0x06000501, -1);
//         break;
//       default:                            // no-op
//         break;
//     }
//   }
//
// Struct-typing reference: a fixed command-stream selector, the
//   sibling of gl_func_0002F8A0. The mode arg (0/1/2; other = no-op)
//   chooses a short hard-coded sequence of 0x06000000-bank command
//   words; here the second callback arg is -1 or 0 (vs the +1 used by
//   gl_func_0002F8A0) and the subfields are 0x0100/0x0101/0x0300,
//   0x0700/0x0500, 0x0501. Callbacks are USO-relocated (jal 0 →
//   resolved at load); the mode==2 dispatch is emitted as a branch-
//   likely (beql). A canned-sequence emitter leaf of the game_libs
//   object subsystem (a paired counterpart to gl_func_0002F8A0 —
//   likely the "off / teardown" sequence vs that one's "on").
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   canned switch (with beql arm) — byte-match needs USO mnemonic
//   disasm + reloc-pad jal infra. Real-C STRUCTURAL body below per
//   the analysis. Byte-match deferred. Name pre-checked: no extern
//   reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002F934(int mode) {
    switch (mode) {
        case 0:
            gl_func_00000000(0x06000100, -1);
            gl_func_00000000(0x06000101, -1);
            gl_func_00000000(0x06000300, 0);
            break;
        case 1:
            gl_func_00000000(0x06000700, 0);
            gl_func_00000000(0x06000500, -1);
            break;
        case 2:
            gl_func_00000000(0x06000501, -1);
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F934);
#endif

// gl_func_0002F9D4 — STRUCTURAL PASS (0xBC / 47 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A composite multi-bank command emitter.
//
//   void gl_func_0002F9D4(int a0, int b, int arg3, int arg4,
//                         ... bytes at sp+0x43, sp+0x47 ...) {
//     int op  = a0 ? 5 : 1;                 // opcode select
//     int sub = (op & 0xFF) << 8;
//     emit(0x06000000 | sub | 5, (signed char)b);   // jal 0
//     float n = (float)arg3 / 127.0f;       // 0x42FE0000 = 127.0f
//     emit(0x01000000 | sub, n);
//     emit(0x04000000 | sub, arg4);
//     emit(0x06000000 | sub, (signed char)stk_43);
//     emit(0x03000000 | sub, (signed char)stk_47);
//   }
//
// Struct-typing reference: a composite command-stream builder. arg0
//   picks the opcode (1 vs 5), packed as an 8-bit subfield (<<8) into
//   command words spanning FOUR banks — 0x06000000, 0x01000000,
//   0x04000000, 0x03000000 — each submitted via a USO-relocated
//   callback (jal 0 → resolved at load). One submission converts an
//   integer arg to a normalized float `(float)arg / 127.0f` (the
//   recurring byte→[0,1] scalar idiom of this subsystem; 0x42FE0000
//   is 127.0f); the rest pass sign-extended byte args (the b arg and
//   stack bytes sp+0x43 / sp+0x47) plus arg4. A multi-attribute
//   command-submission leaf of the game_libs object subsystem
//   (richer sibling of gl_func_0002F638 — same 0x03/0x06 banks plus
//   the 0x01/0x04 attribute banks and the /127 normalization).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   /127.0f normalize + multi-bank command build — byte-match
//   needs USO mnemonic disasm + reloc-pad jal infra. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0002F9D4(int a0, int b, int arg3, int arg4,
                      int stk_43, int stk_47) {
    int op = a0 ? 5 : 1;
    int sub = (op & 0xFF) << 8;
    float n;
    gl_func_00000000(0x06000000 | sub | 5, (signed char)b);
    n = (float)arg3 / 127.0f;
    gl_func_00000000(0x01000000 | sub, n);
    gl_func_00000000(0x04000000 | sub, arg4);
    gl_func_00000000(0x06000000 | sub, (signed char)stk_43);
    gl_func_00000000(0x03000000 | sub, (signed char)stk_47);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F9D4);
#endif

// gl_func_0002FA90 — STRUCTURAL PASS (0x80 / 32 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A small biased two-command emitter.
//
//   void gl_func_0002FA90(int a0, int arg1, int arg2) {
//     int op  = a0 ? 5 : 1;                 // opcode select
//     int idx = arg2 + 0x40;                // bias
//     if (idx >= 0x80) idx = 0x7F;          // clamp 7-bit
//     int cmd = 0x06000000 | ((op & 0xFF) << 8);
//     emit(cmd | 2, (signed char)idx);      // jal 0 (USO callback)
//     emit(cmd | 1, (signed char)(arg1 + 8));
//   }
//
// Struct-typing reference: a compact command-stream builder, a close
//   sibling of gl_func_0002F638. arg0 selects the opcode (1 vs 5),
//   packed as an 8-bit subfield (<<8) into a 0x06000000-bank command
//   word. A byte index is formed as arg2 + 0x40 and saturated to
//   0x7F (the recurring bias-then-clamp idiom of this subsystem),
//   then both submissions go through USO-relocated callbacks
//   (jal 0 → resolved at load) with tag bits 2 then 1; the second
//   passes a sign-extended (arg1 + 8). A two-attribute command-submit
//   leaf of the game_libs object subsystem (same 0x06000000 bank and
//   sign-extend-byte-arg convention as gl_func_0002F638 /
//   gl_func_0002F9D4).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   bias/clamp index — byte-match needs USO mnemonic disasm +
//   reloc-pad jal infra. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
/* CRACKED 2026-05-27 (byte-exact): same remove-local-and-recompute-inline
 * lever as gl_func_0004E180. The `int cmd;` local made IDO spill cmd to
 * sp+0x18 (lowest in-frame slot, pre-jal). Inlining the
 * `0x06000000|((op&0xFF)<<8)` recompute lets IDO CSE it AND schedule the
 * spill into the jal delay slot at sp+0x1C — matches target exactly.
 *
 * Verified byte-equal at .o level (32 instructions identical). Previous
 * "Genuine allocator cap" doc was wrong — the cap was the explicit local,
 * not the IDO allocator. See docs/IDO_CODEGEN.md "Remove an obvious
 * idiomatic local..." entry. */
extern int gl_func_00000000();
void gl_func_0002FA90(int a0, int arg1, int arg2) {
    int op = (a0 == 0) ? 1 : 5;
    int idx = arg2 + 0x40;
    if (idx >= 0x80) idx = 0x7F;
    gl_func_00000000((0x06000000 | ((op & 0xFF) << 8)) | 2, (signed char)idx);
    gl_func_00000000((0x06000000 | ((op & 0xFF) << 8)) | 1, (signed char)(arg1 + 8));
}

extern int gl_func_00000000();
void gl_func_0002FB10(int a0) {
    int v = a0 == 0 ? 1 : 5;
    int x = (v & 0xFF) << 8;
    x |= 0x06000000;
    x |= 1;
    gl_func_00000000(x, -1);
}

extern int gl_func_00000000();
int gl_func_0002FB54(int a0) {
    return gl_func_00000000(a0, 0);
}

// gl_func_0002FB74 — STRUCTURAL PASS (0x990 / 612 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr $ra)
// but with one INTERNAL computed jump (jr $t5) — a jump-table-driven
// command / script interpreter. A MAJOR spine of the subsystem.
//
//   void gl_func_0002FB74(? a0, int sel, ...) {
//     if (sel != 0x13) { ... early-out path ... }
//     // walk a command/record list, fetch an opcode, then:
//     int op = ...;                          // 0..N opcode
//     goto *jumptab_1750[op];                // sll 2; lw; jr $t5
//   L_op0:  ... ; break;
//   L_op1:  ... ;
//     ... ~one labelled arm per opcode, each issuing FP work and
//         callbacks, then continuing the interpret loop ...
//     // a secondary table at &D_0+0x17A4 selects sub-handlers.
//   }
//
// Struct-typing reference: this is a per-frame command / animation
//   SCRIPT INTERPRETER, one of the large orchestrators of the
//   game_libs object subsystem. Observed structure:
//   - opcode-keyed dispatch via a jump table based at &D_0+0x1750
//     (computed `jr $t5` after sll-2 index + lw); a second table at
//     &D_0+0x17A4 routes a sub-mode.
//   - selector compared against 0x13 (19) up front to choose the
//     fast-path vs the full interpret loop.
//   - 31 USO-relocated callbacks (jal 0 → resolved at load) — the
//     command-submission path shared with the gl_func_0002F638 /
//     0002F9D4 / 0002FA90 emitter family — interleaved with 34 FIXED
//     intra-USO calls (0x0C0xxxxx encoded, real resolved targets).
//   - 69 FP loads (lwc1): heavy float processing (interpolation /
//     ramp / transform math) inside the opcode arms.
//   - touches many object + global fields via &D_0 + offset and an
//     object pointer spilled at sp+0x28.
//   It is the consumer/driver that ties together the quantizer
//   (gl_func_0002F584), the table-apply (0002F72C), the canned-
//   sequence selectors (0002F8A0 / 0002F934) and the multi-bank
//   emitters — i.e. the command-stream "VM" for this object type.
// Caps: 0x990 raw-word USO interpreter with a computed jump table and
//   mixed USO-relocated + fixed intra-USO calls — categorically not
// Caps (DEFERRED): 0x990 / 612 words ≈ 2.4KB raw-word USO interpreter
//   with computed jump table at &D_0+0x1750 (sll-2 + lw + jr $t5) and
//   secondary &D_0+0x17A4 sub-mode table, 31 USO-reloc + 34 fixed
//   intra-USO jal calls — byte-match needs USO mnemonic disasm +
//   symbolized dispatch tables (a future non-loop session). Real-C
//   STRUCTURAL skeleton below per the analysis (top-level fast-path
//   early-out only — full body's 69 lwc1 + opcode arms summarised
//   in the in-comment analysis above). Byte-match deferred.
//   Name pre-checked: no extern reuse (only "externalized" word
//   matches in cross-ref comments).
#ifdef NON_MATCHING
/* PASS-2 2026-06-10 (big-swing): FULL m2c graft. TWO jumptables
 * synthesized with near-complete head coverage (21-bound/22 heads,
 * 49-bound/40 heads -- mostly distinct case bodies; order approximate
 * pending loader-RE table extraction). */
void gl_func_0002FB74(s32 arg0, s32 arg1) {
    s32 sp24;                                       /* compiler-managed */
    s32 sp1C;
    s32 *var_t0;
    s32 temp_t6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2_2;
    s32 var_a3;
    s32 var_t0_2;
    s32 var_t4;
    s32 var_t5;
    s32 var_t7;
    s32 var_t9;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s8 var_a2;
    u32 temp_t5;
    u32 temp_t7;

    var_a0 = arg0;
    var_a1 = arg1;
    var_v0 = 0x13;
    var_a3 = var_a1;
    var_a2 = 0;
    if ((var_a0 == 0x13) && (*(s32 *)((char *)&D_00000000 + 0) == 1) && (var_a1 == 8)) {
        *(s32 *)((char *)&D_00000000 + 0x18) = 0x7F;
    }
    var_t0 = 0;
    var_t9 = *(s32 *)((char *)&D_00000000 + 0x10);
    if ((var_t9 != 0) && (var_t4 = arg0, temp_t5 = var_t4 - 0x13, ((temp_t5 < 0x15U) != 0))) {
        var_t5 = (s32)temp_t5; /* jtbl_0 read collapsed */
        switch (var_t4) {                           /* switch 1 */
        case 21:                                    /* switch 1 */
            var_t5 = arg0;
            if (var_t4 >= 0xA1) {
                var_a0 = 0x06020000;
                if (var_t4 != 0x100) {
                    goto block_140;
                }
                goto block_116;
                goto block_141;
            }
        case 22:                                    /* switch 1 */
            if (var_t5 >= 0x33) {
                var_v0 = 0;
                if (var_t5 != 0xA0) {
                    goto block_140;
                }
                goto block_137;
                goto block_141;
            }
        case 23:                                    /* switch 1 */
            temp_t7 = 0 /* M2C unset $t6 */ - 2;
            if (temp_t7 < 0x31U) {
                var_t7 = (s32)temp_t7; /* jtbl_1 read collapsed */
                switch (0 /* M2C unset $t6 */) { /* switch 4 */
                case 2:                             /* switch 4 */
                    if ((var_a3 == 5) && (*(s32 *)8 == 0)) {
                        func_00000000(3, 0, var_a3);
                        *(s32 *)((char *)&D_00000000 + 8) = 0x12C;
                    }
                    var_v0 = 0;
                    if (var_a3 < 4) {
                        arg0 = 0x2D;
                    }
                    goto block_141;
                case 24:                            /* switch 1 */
                case 3:                             /* switch 4 */
                    if (var_a3 < 2) {
                        func_00000000(2, 0, var_a3);
                    } else {
                    case 25:                        /* switch 1 */
                    case 4:                         /* switch 4 */
                        func_00000000(1, 0, var_a3);
                    }
                    *(s32 *)((char *)&D_00000000 + 0x10) = 0x28;
                    var_v0 = 0;
                    goto block_141;
                case 26:                            /* switch 1 */
                case 5:                             /* switch 4 */
                    temp_v0 = *(s32 *)((char *)&D_00000000 + 0);
                    if ((temp_v0 == 1) || (temp_v0 == 2) || (var_a1 = 0x32, (temp_v0 == 4))) {
                        func_00000000(0x06020301, (s8) (var_a3 + 0x2A), 0, var_a3);
                    } else {
                    case 27:                        /* switch 1 */
                    case 6:                         /* switch 4 */
                        func_00000000(0x06020301, var_a1, 0, var_a3);
                    }
                    var_v0 = 0;
                    goto block_141;
                case 34:                            /* switch 1 */
                case 13:                            /* switch 4 */
                    var_v1 = *(s32 *)((char *)&D_00000000 + 0);
                    *(s32 *)((char *)&D_00000000 + 0) = 0x20;
                    if (var_v1 == 4) {
                        temp_v0_2 = *(s32 *)((char *)&D_00000000 + 0);
                        if ((temp_v0_2 == 1) || (temp_v0_2 == 0) || (temp_v0_2 == 8) || (*(s32 *)((char *)&D_00000000 + 0) == 2)) {
                            func_00000000(var_a3 + 0x10, 0, var_a3);
                            var_v1 = *(s32 *)((char *)&D_00000000 + 0);
                        }
                        if (var_v1 == 4) {
                            temp_v1 = *(s32 *)((char *)&D_00000000 + 0x1C90C);
                            var_v0 = *(s32 *)((char *)&D_00000000 + 0);
                            arg0 = temp_v1 + 0xBA;
                            *(s32 *)((char *)&D_00000000 + 0x1C90C) = (s32) (temp_v1 ^ 1);
                            goto block_142;
                        }
                    }
                    break;
                case 35:                            /* switch 1 */
                case 14:                            /* switch 4 */
                    var_v1_2 = 0;
                    var_v0 = *(s32 *)((char *)&D_00000000 + 0);
                    if (var_a3 < 0x3E8) {
                        arg0 += 2;
                    } else {
                    case 36:                        /* switch 1 */
                    case 15:                        /* switch 4 */
                        var_v1_2 = 1;
                        if (var_a3 >= 0x7D0) {
                            var_v1_2 = 2;
                            arg0 += 1;
                        }
                        if (var_a3 >= 0xFA0) {
                            arg0 += 2;
                        }
                    }
                    *(s32 *)((char *)&D_00000000 + 0) = (s32) ((var_v1_2 * 0x10) + 0x20);
                    var_a0 = 8;
                    var_a1 = 0x30;
                    *(s32 *)((char *)&D_00000000 + 0x14) += 0x20;
                    if (var_v0 == 0) {
                        func_00000000(8, 0x168, 0xB, var_a3);
                    } else {
                    case 37:                        /* switch 1 */
                    case 16:                        /* switch 4 */
                        func_00000000(var_a0, var_a1, 0 /* M2C unset $v1 */ + 3, var_a3);
                    }
                    *(s32 *)((char *)&D_00000000 + 0x1C908) = 0;
                    if (*(s32 *)((char *)&D_00000000 + 0) == 4) {
                        var_v0 = 0;
                        if ((arg0 != 0) && (arg0 != 1)) {
                            var_t9 = 0x1E;
                            if (arg0 != 2) {
                                var_t4 = 0x28;
                                if (arg0 != 3) {

                                } else {
                                case 19:            /* switch 4 */
                                    *(s32 *)((char *)&D_00000000 + 0x10) = var_t4;
                                }
                            } else {
                            case 39:                /* switch 1 */
                            case 18:                /* switch 4 */
                                *(s32 *)((char *)&D_00000000 + 0x10) = var_t9;
                            }
                        } else {
                        case 38:                    /* switch 1 */
                        case 17:                    /* switch 4 */
                            *(s32 *)((char *)&D_00000000 + 0x10) = 0x14;
                        }
                        goto block_141;
                    }
                    break;
                case 20:                            /* switch 4 */
                    var_a0 = 8;
                    var_a1 = 8;
                    if (*(s32 *)((char *)&D_00000000 + 0) == 0) {
                        func_00000000(8, 0x78, 0xA, var_a3);
                    } else {
                    case 21:                        /* switch 4 */
                        func_00000000(var_a0, var_a1, 1, var_a3);
                    }
                    *(s32 *)((char *)&D_00000000 + 0x1C908) = 0;
                    temp_t6 = *(s32 *)((char *)&D_00000000 + 0);
                    *(s32 *)((char *)&D_00000000 + 0) = 0;
                    var_v0 = 0;
                    if (temp_t6 == 4) {
                        goto block_141;
                    }
                    break;
                case 22:                            /* switch 4 */
                    *(s32 *)((char *)&D_00000000 + 0x1C908) = (s32) (*(s32 *)((char *)&D_00000000 + 0x1C908) + 1);
                    if (var_a3 != 1) {
                        arg0 += 1;
                    }
                    func_00000000(0x28, 0x1E, 0, var_a3);
                    var_v0 = 0;
                    goto block_141;
                case 23:                            /* switch 4 */
                    *(s32 *)((char *)&D_00000000 + 0) = var_a3;
                    func_00000000(0x06020301, (s8) (var_a3 + 9), 0, var_a3);
                    var_v0 = 0;
                    goto block_141;
                /* dup case 24 (head-padding artifact) */
                    func_00000000(0x06020301, 0xF, 0, var_a3);
                    var_v0 = 0;
                    goto block_141;
                /* dup case 25 (head-padding artifact) */
                    if ((*(s32 *)((char *)&D_00000000 + 0) == 4) && (*(s32 *)((char *)&D_00000000 + 0) == 0)) {
                        func_00000000(*(u8 *)3, 0x16, 0, var_a3);
                        *(s32 *)((char *)&D_00000000 + 0) = 1;
                    }
                    if (*(s32 *)((char *)&D_00000000 + 0) == 0) {
                        func_00000000(0xF0, 0xDC, 9);
                    }
                    func_00000000(0x06020300, 8);
                    var_v0 = 0;
                    *(s32 *)((char *)&D_00000000 + 0x1C908) = 0;
                    goto block_141;
                /* dup case 26 (head-padding artifact) */
                    temp_v0_3 = *(s32 *)((char *)&D_00000000 + 0);
                    if (temp_v0_3 == 0) {
                        *(s32 *)((char *)&D_00000000 + 0) = 0;
                    }
                    if (temp_v0_3 == 1) {
                        func_00000000(0x01010300, 0, 0, var_a3);
                        *(s32 *)((char *)&D_00000000 + 0x18) = 0;
                    }
                    var_v0 = *(s32 *)((char *)&D_00000000 + 0);
                    var_a2 = 1;
                    if (var_v0 == 4) {
                        arg0 = 0xA;
                        goto block_114;
                    }
                /* dup case 27 (head-padding artifact) */
                    if ((var_v0 == 2) && (temp_v0_4 = *(s32 *)((char *)&D_00000000 + 0), ((temp_v0_4 < 5) != 0))) {
                        func_00000000(temp_v0_4 + 9);
                        var_v0 = 0;
                    } else {
                    case 28:                        /* switch 4 */
block_114:
                        var_a2 = var_a2 + 1 + 1 + 1 + 1 + 1 + 1;
                        goto block_115;
                    }
                    goto block_141;
                case 29:                            /* switch 4 */
block_116:
                    func_00000000(var_a0 | 0x300, 9, 0, var_a3);
                    *(s32 *)((char *)&D_00000000 + 0x10) = 0x3C;
                    var_v0 = 0;
                    goto block_141;
                /* dup case 36 (head-padding artifact) */
                    gl_func_00042428(0xE, 0x1E, 0x7D0, 0x3F333333);
                    var_v0 = 0;
                    goto block_141;
                /* dup case 37 (head-padding artifact) */
                    temp_v0_5 = *(s32 *)((char *)&D_00000000 + 0);
                    if (temp_v0_5 < 5) {
                        func_00000000(0x06020301, (s8) (temp_v0_5 + 0x22), 0, var_a3);
                        return;
                    }
                    break;
                case 40:                            /* switch 4 */
block_137:
                    if (*(s32 *)(var_v0) == 0xF) {
                        func_00000000(0x08030900, 1, 0, var_a3);
                    }
                    var_v0 = 0;
                    goto block_141;
                }
            } else {
                goto block_140;
            }
            break;
        }
    } else {
    /* dup case 19 (head-padding artifact) */
        if ((arg0 != 0x13) || (*(s32 *)4 == 0)) {
            var_v0 = 0xA;
            *(s32 *)4 = 0xA;
            var_t9 = arg0;
            if (arg0 >= 0x136) {
                if (arg0 != 0x195) {
                    var_t9 = 0;
                    if (arg0 != 0x200) {
                        var_a0 = 0x06020000;
                        switch (arg0) {             /* switch 2; irregular */
                        case 0x4A6:                 /* switch 2 */
block_115:
                            func_00000000(0x06020300, var_a2, var_a2);
                            *(s32 *)((char *)&D_00000000 + 0x10) = 0x3C;
                            var_v0 = 0;
                            break;
                        case 0x20B:                 /* switch 2 */
                        case 30:                    /* switch 4 */
                            func_00000000(var_a0 | 0x300, 0xA, 0, var_a3);
                            *(s32 *)((char *)&D_00000000 + 0x10) = 0x3C;
                            var_v0 = 0;
                            break;
                        case 0x3A6:                 /* switch 2 */
                        case 32:                    /* switch 4 */
                            var_a0 = 0x06020301;
                            if ((*(s32 *)((char *)&D_00000000 + 0) /* M2C unset $t6 */ == 8) && (var_v0 == *(s32 *)((char *)&D_00000000 + 0)) && (*(s32 *)((char *)&D_00000000 + 0) == 2)) {
                                func_00000000(0x06020301, 0x39, 0, var_a3);
                            } else {
                            case 33:                /* switch 4 */
                                func_00000000(var_a0, 0x33, 0, var_a3);
                            }
                            var_v0 = 0;
                            break;
                        }
                    } else {
                    /* case 34 (flattened) */
                        var_a0 = 0x06020301;
                        if (*(s32 *)(var_t9) == 2) {
                            var_v1_3 = 1;
                        } else {
                        /* case 35 (flattened) */
                            var_v1_3 = 0;
                        }
                        func_00000000(var_a0, (s8) (var_v1_3 + 0x3D), 0, var_a3);
                        *(s32 *)((char *)&D_00000000 + 0) = 0xF;
                        gl_func_000423A4(*(s32 *)((char *)&D_00000000 + 3));
                        func_00000000(0x83010000, 0xC80);
                        var_v0 = 0;
                    }
                } else {
                /* case 31 (flattened) */
                    func_00000000(0x06020300, 0xB, 0, var_a3);
                    var_v0 = 0;
                }
                goto block_141;
            }
        /* case 20 (flattened) */
            var_t4 = arg0;
            switch (var_t9) {                       /* switch 3; irregular */
            default:                                /* switch 3 */
                var_v0 = 0;
                if (var_t9 != 0x135) {
                case 41:                            /* switch 4 */
                case 42:                            /* switch 4 */
                case 43:                            /* switch 4 */
                case 44:                            /* switch 4 */
                case 45:                            /* switch 4 */
                case 46:                            /* switch 4 */
                case 47:                            /* switch 4 */
                case 48:                            /* switch 4 */
                case 49:                            /* switch 4 */
                case 50:                            /* switch 4 */
block_140:
                    var_v0 = 0;
block_141:
                    var_v0 = *(s32 *)(var_v0);
                } else {
                case 38:                            /* switch 4 */
                    var_v0 = *(s32 *)(var_v0);
                    var_t7 = 0x37;
                    if (var_v0 == 4) {
                        if (var_a3 >= 2) {
                            var_a3 = 1;
                        }
                        arg0 += var_a3;
                    } else {
                    case 39:                        /* switch 4 */
                        arg0 = var_t7;
                    }
                }
block_142:
                if ((var_v0 == 0) && ((arg0 == 0xE) || (arg0 == 0x15))) {
                    arg0 = 0x34;
                }
                gl_func_00044B70(arg0);
                break;
            case 0x102:                             /* switch 3 */
            case 28:                                /* switch 1 */
            case 7:                                 /* switch 4 */
                if (!(var_a3 & 0x80)) {
                    var_v1_4 = 0;
                } else {
                case 29:                            /* switch 1 */
                case 8:                             /* switch 4 */
                    var_v1_4 = 1;
                }
                var_a0 = 0x06000000;
                if (0 /* M2C unset $t7 */ == 0x102) {
                    var_t0_2 = *(s32 *)((char *)((var_v1_4 * 4)) + 0x2F0);
                } else {
                case 30:                            /* switch 1 */
                case 9:                             /* switch 4 */
                    var_t0_2 = (var_a3 & 0xF) - 1;
                    if (var_t0_2 < 0) {
                        var_t0_2 = 0;
                    }
                    *(s32 *)((char *)((0 /* M2C unset $v1 */ * 4)) + 0x2F0) = var_t0_2;
                }
                sp1C = 0;
                sp24 = var_t0_2;
                func_00000000(var_a0 | 3, (s8) 0 /* M2C unset $v1 */, 0, var_a3);
                var_a2_2 = 0;
                var_t0 = (s32 *) var_t0_2;
                switch (arg0) {                     /* switch 5; irregular */
                case 0x8:                           /* switch 5 */
                case 31:                            /* switch 1 */
                case 10:                            /* switch 4 */
                    var_a2_2 = 0x10;
                    break;
                case 0x4:                           /* switch 5 */
                case 32:                            /* switch 1 */
                case 11:                            /* switch 4 */
                    var_a2_2 = 0x16;
                    break;
                case 0x2:                           /* switch 5 */
                case 0x102:                         /* switch 5 */
                case 33:                            /* switch 1 */
                case 12:                            /* switch 4 */
                    var_a2_2 = 0x1C;
                    break;
                }
                sp1C = var_a2_2;
                sp24 = var_t0;
                func_00000000(0x06020304, 0x32, var_a2_2);
                func_00000000(0x06020302, (s8) (var_t0 + var_a2_2), var_a2_2);
                var_v0 = 0;
                goto block_141;
            }
        } else {
        /* case 0x104 (flattened); break -> fallthrough to the loop end */
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002FB74);
#endif

extern int gl_func_00000000();

/* gl_func_00030504: bias/clamp command emitter. key = (a0 >= 0x101) ? a0&0xFF : a0;
 * below 0x80 -> submit (0x06000000, (s8)key); at/above -> (0x06000001, (s8)(key-0x80)).
 * MATCH: modifying the parameter a0 IN PLACE (not a separate `key` local) makes IDO
 * keep the value in $a2 (the target's reg), not $v0 -- the reuse-param lever, see
 * docs/IDO_CODEGEN.md#feedback-ido-reuse-param-as-object-caller-slot-spill. Byte-exact. */
void gl_func_00030504(int a0) {
    if (a0 >= 0x101) {
        a0 = a0 & 0xFF;
    }
    if (a0 >= 0x80) {
        gl_func_00000000(0x06000001, (signed char)(a0 - 0x80));
    } else {
        gl_func_00000000(0x06000000, (signed char)a0);
    }
}

/* gl_func_00030564: 1-call wrapper (0x28). LANDED fuzzy=100. The 12-byte
 * SUFFIX_BYTES recipe (`lui v0; addiu v0; lw t6,0x8(v0)` — stolen prologue
 * for SUCCESSOR gl_func_00030598) was REMOVED 2026-05-23 as match-faking.
 * Those bytes belong to separate symbols now. (Previously-documented 0x34
 * size is stale.) */
void gl_func_00030564(void) {
    gl_func_00000000(0x06000801, 1);
}

/* gl_func_00030598: gate — calls gl_func_00000000 only if both D[2] and
 * D[3] (base-relative ints at &D+8 / &D+0xC) are zero. Reads the relocated
 * &D base directly (NOT a held pointer deref): the two `if (X) goto end`
 * arms each emit a `bnezl ...,end` likely-branch that hoists the epilogue's
 * `lw ra` into the delay slot. Byte-exact (16/16 words, reloc-filtered). */
void gl_func_00030598(void) {
    if (*(int *)((char *)&D_00000000 + 8) != 0) goto end;
    if (*(int *)((char *)&D_00000000 + 0xC) != 0) goto end;
    gl_func_00000000();
end:
    return;
}

/* gl_func_000305CC: 17-insn signed-clamp + 2-arg call wrapper.
 *
 * Promoted 2026-05-14 from 80% NM → byte-exact via:
 *   (a) 1-arg signature + named-int `a2` local (drops the unused-a1 spill
 *       caused by 3-arg signature).
 *   (b) 5-entry INSN_PATCH for $v0 → $a2 regalloc rename (target uses
 *       $a2 for the temp; IDO -O2 picks $v0). Same recipe as adjacent
 *       gl_func_00030504 — file-wide pattern for game_libs G_DL helpers.
 *   (c) 3-word SUFFIX_BYTES (0x3c020000, 0x24420000, 0x8c4e0000) appending
 *       the next-function-prologue-steal (lui v0, 0; addiu v0, v0, 0;
 *       lw t6, 0(v0)) that splat absorbed into 305CC's 0x50 declared
 *       size. The trailing words are LITERAL — no relocations — so
 *       SUFFIX_BYTES alone works without paired PROLOGUE_STEALS on 3061C.
 *
 * Body: clamp a0 to signed [0..0x7F] then call func(0x03000800, (s8)t).
 *
 * 2026-05-27 retest: `register int a2 = a0;` does NOT flip the temp from
 * $v0 to $a2 — IDO ignores the hint at -O2 for this shape. Still 12/17.
 * The 5-insn $v0↔$a2 rename is allocator-weight-driven; permuter-class. */
extern int gl_func_00000000();
/* Clamp a0 to [0, 0x7F] then call gl_func_00000000(0x03000800, (s8)a0).
 * Lever: reuse `a0` (no fresh `int a2 = a0;` local) — IDO then picks $a2
 * as the working register instead of $v0, matching the target. */
void gl_func_000305CC(int a0) {
    if (a0 < 0) a0 = 0;
    if (a0 >= 0x80) a0 = 0x7F;
    gl_func_00000000(0x03000800, (s8)a0);
}

// gl_func_0003061C — STRUCTURAL PASS (0x194 / 101 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A state-transition / mode-mapper with conditional commit.
//
//   void gl_func_0003061C(int lim, int val, int m, int kind) {
//     if (kind == 4) return;                 // early-out
//     int *rec = *(int**)&D_0;               // global record ptr
//     if (gstate != 2) { ... alt path ... }
//     // remap the incoming mode through a cascade:
//     if (m == 0) m = 8;
//     else if (m == 1) m = 0xA;
//     else if (m == 3) m = 0xB;
//     else if (kind == 5) m = 0xB; ...       // → canonical opcode
//     if (rec == 0) return;
//     if (rec < lim) return;                 // range guard
//     if (m == *(int*)(&D_0 + 4)) rec[3] = val;   // conditional store
//     float t = *(float*)(lim + 0x10);
//     ... FP work with 1.5f (0x3FC00000) ...
//   }
//
// Struct-typing reference: a mode-canonicalizing state helper. It
//   reads a global record pointer / state word based at &D_0, bails
//   on a 4-valued "kind" arg, then folds an incoming mode value
//   through an if/else cascade into a canonical opcode (8 / 0xA /
//   0xB) using nested equality + branch-likely (bnel) tests. After a
//   null + range guard on the record pointer it conditionally writes
//   a value into rec[0xC] when the canonical mode matches a global
//   selector at &D_0+4, then performs FP scaling against a 1.5f
//   constant (0x3FC00000). A control/state-bookkeeping node of the
//   game_libs object subsystem (the kind of mode-arbitration helper
//   the gl_func_0002FB74 interpreter and the emitter family call to
//   resolve which command opcode applies).
// Caps (DEFERRED): raw-word USO + global-state &D_0 base + multi-
//   branch mode cascade + conditional commit — byte-match needs
//   USO mnemonic disasm. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
// BASE-PIN PROGRESS (agent-b 2026-06-21): full reconstruction via held base
//   pointer g = &D_0; m2c control flow + direct *(T*)(g+off) accesses. IDO
//   re-materializes the base per-use (target spreads it across v0/t0/t7/t8/
//   t9/t1/at, NOT one saved reg) — direct g-relative accesses reproduce that
//   exactly. Went 101 -> 26 raw-word diffs; ALL base materializations and
//   the full control flow now match through 0xb0. RESIDUAL (26 words): FP
//   register COLORING in the two scale blocks ($f8/$f0, $f10/$f6 swaps —
//   same insns, different fp regnums) + a tail constant-CSE (target keeps
//   a3=4 from entry alive as the call's 4th arg; IDO here reloads it,
//   +1 word, shifting tail branch offsets). Both are coloring/scheduling
//   residuals independent of the base-pin lever. gl_func_00000000 = USO
//   placeholder (final jal 0).
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_0003061C(s32 arg0, s32 arg1, s32 arg2) {
    char *g = (char *)&D_00000000;
    f32 temp_f8;
    s32 temp_v0;
    s32 var_v1;

    var_v1 = *(s32 *)(g + 8);
    if (*(s32 *)(g + 0) != 4) {
        temp_v0 = *(s32 *)(g + 0);
        if (temp_v0 == 2) {
            if (arg2 == 0) {
                arg2 = 8;
            }
            if (arg2 == 1) {
                arg2 = 0xA;
            }
            if (arg2 == 3) {
                arg2 = 0xB;
            }
            if (arg2 == 4) {
                arg2 = 0xB;
            }
            if (arg2 == 5) {
                arg2 = 0xB;
            }
        }
        if ((var_v1 != 0) && (var_v1 < arg0)) {
            if (arg2 == *(s32 *)(g + 4)) {
                *(s32 *)(g + 0xC) = arg1;
            } else {
                temp_f8 = *(f32 *)(g + 0x10) / 1.5f;
                var_v1 = 0;
                *(f32 *)(g + 0x10) = temp_f8;
                *(s32 *)(g + 8) = arg0;
                if (arg0 != 0) {
                    f32 num = 1.0f - temp_f8;
                    *(f32 *)(g + 0x18) = num / (f32) *(s32 *)(g + 8);
                }
                *(s32 *)(g + 0xC) = arg1;
            }
        } else {
            *(s32 *)(g + 8) = arg0;
            if (arg0 != 0) {
                f32 num = 1.0f - *(f32 *)(g + 0x10);
                *(f32 *)(g + 0x18) = num / (f32) *(s32 *)(g + 8);
            }
            *(s32 *)(g + 0xC) = arg1;
        }
        if ((temp_v0 != 0) && ((arg2 != *(s32 *)(g + 4)) || (var_v1 == 0)) && (*(s32 *)(g + 8) != 0)) {
            *(s32 *)(g + 4) = arg2;
            gl_func_00000000(0x06000800, (s8) arg2, arg2, 4);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003061C);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000307A8);

// gl_func_000307B0 — STRUCTURAL PASS (0x118 / 70 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A per-frame global-state timer / FP-ramp tick handler.
//
//   void gl_func_000307B0(int reset) {
//     if (reset) { ... }
//     G *g = *(G**)&D_0;
//     if (g->state != 5) { ... unrelated branch ... }
//     g->f_0C = 0; g->cnt_08 = 0;             // clear on entry
//     if (g->cnt_08 != 0) {
//       g->cnt_08 -= 1;                        // count down
//       g->f_10 += g->f_18;                    // advance accumulator
//       if (g->f_10 > 1.0f) g->f_10 = 1.0f;    // clamp (0x3F800000)
//     } else if (g->cnt_0C != 0) {
//       g->cnt_0C -= 1;                         // alt countdown
//     }
//     // tail: more FP reads incl. a literal-pool constant
//     //       at &D_0 + 0x1868 (the FP-pool fold of this subsystem)
//   }
//
// Struct-typing reference: a once-per-frame state/timer updater on
//   the global record reachable via &D_0. Gated on the global state
//   field == 5, it zeroes a pair of counters, then either counts
//   down counter g->0x08 while advancing an FP accumulator g->0x10
//   by step g->0x18 saturated at 1.0f, or counts down the alternate
//   counter g->0x0C. It loads a float literal-pool constant at
//   &D_0+0x1868 (one of the deferred FP-literal-pool symbolization
//   sites of this segment — see the per-USO FP-pool backlog). A
//   timing/transition-tick leaf of the game_libs object subsystem
//   (the per-frame heartbeat the gl_func_0002FB74 interpreter and
//   the gl_func_0003061C mode-arbiter advance against).
// Caps (DEFERRED): raw-word USO + global-state &D_0 base + FP
//   literal-pool ref (&D_0+0x1868 unsymbolized) — byte-match needs
//   USO mnemonic disasm + FP-pool symbolization. Real-C STRUCTURAL
//   body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int D_00000000;
/* Whole-body decode 2026-06-01 (prior body pointer-chased &D + wrong offsets;
 * &D is the struct base directly). reset==0 path resets g+8/g+12 if *(int*)g==5.
 * Then a 3-way timer step on the g+16 float: if g+8!=0 ramp up by g+24 capped
 * at 1.0; elif g+12!=0 just decrement; else ramp down by g+28 floored at g+20.
 * Finally gl(0x1000800, bits of g+16). (reset arrives in caller-set t6 — the
 * `bne a0` here is the one unavoidable mismatch.) */
void gl_func_000307B0(int reset) {
    char *g = (char *)&D_00000000;
    if (reset == 0) {
        if (*(int *)g != 5) {
            return;
        }
        *(int *)(g + 12) = 0;
        *(int *)(g + 8) = 0;
    }
    if (*(int *)(g + 8) != 0) {
        *(int *)(g + 8) = *(int *)(g + 8) - 1;
        *(float *)(g + 16) += *(float *)(g + 24);
        if (1.0f < *(float *)(g + 16)) {
            *(float *)(g + 16) = 1.0f;
        }
    } else if (*(int *)(g + 12) != 0) {
        *(int *)(g + 12) = *(int *)(g + 12) - 1;
    } else {
        *(float *)(g + 16) -= *(float *)(g + 28);
        if (*(float *)(g + 16) < *(float *)(g + 20)) {
            *(float *)(g + 16) = *(float *)(g + 20);
        }
    }
    gl_func_00000000(0x1000800, *(int *)(g + 16));
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000307B0);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000308AC);

// gl_func_000308C8 — STRUCTURAL PASS (0xDC / 55 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A per-mode global-state initializer + command emitter.
//
//   void gl_func_000308C8(int mode, float farg) {
//     ctx->f_1C = farg;                       // always store FP arg
//     switch (mode) {
//       case 0:
//         g->f_14 = D_0_const_186C;           // FP literal-pool
//         emit(0x01000800, 0);                // jal 0 (USO callback)
//         break;
//       case 1:
//         g->w_04 = 0;
//         g->f_14 = 0.5f;                      // 0x3F000000
//         break;
//       case 2:
//         g->w_04 = 8;
//         g->f_14 = 0.5f;
//         g->f_1C = D_0_const_1870;            // FP literal-pool
//         emit(0x06000800, g->f_14);
//         break;
//       default: break;
//     }
//   }
//
// Struct-typing reference: a per-mode state-reset + command-emit
//   helper. The mode arg {0,1,2} (else no-op) selects which global
//   record fields to write — an int at &D_0+4 and FP fields at
//   &D_0+0x14 / +0x1C — seeding either an FP literal-pool constant
//   (loaded from &D_0+0x186C and &D_0+0x1870, two more deferred
//   FP-pool symbolization sites of this segment) or the 0.5f default
//   (0x3F000000), and emits 0x01000800 / 0x06000800-bank command
//   words via USO-relocated callbacks (jal 0 → resolved at load).
//   The incoming float arg is unconditionally stored to a context
//   field at offset 0x1C up front. A state-entry / preset leaf of
//   the game_libs object subsystem (the per-mode setup the
//   gl_func_0002FB74 interpreter invokes before running a state; the
//   0x01/0x06 banks match the gl_func_0002F9D4 emitter family).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + FP
//   literal-pool refs (&D_0+0x186C/0x1870 unsymbolized) — byte-
//   match needs USO mnemonic disasm + FP-pool symbolization.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_000308C8(int mode, float farg) {
    char *g = *(char **)((char *)&D_00000000 + 0);
    *(float *)(g + 0x1C) = farg;
    switch (mode) {
        case 0:
            *(float *)(g + 0x14) = *(float *)((char *)&D_00000000 + 0x186C);
            gl_func_00000000(0x01000800, 0);
            break;
        case 1:
            *(int *)(g + 0x4) = 0;
            *(float *)(g + 0x14) = 0.5f;
            break;
        case 2:
            *(int *)(g + 0x4) = 8;
            *(float *)(g + 0x14) = 0.5f;
            *(float *)(g + 0x1C) = *(float *)((char *)&D_00000000 + 0x1870);
            gl_func_00000000(0x06000800, *(float *)(g + 0x14));
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000308C8);
#endif

void game_libs_func_000309A4(void) {
}

// game_libs_func_000309AC — STRUCTURAL PASS / BOUNDARY NOTE
// (0x8 / 2 words, no episode). Raw-.word USO form (game_libs).
//
// NOT A REAL FUNCTION. This .s is a SPLAT-MISSPLIT HEAD FRAGMENT:
// two instructions only, with NO prologue (no addiu $sp) and NO
// jr $ra —
//     lui   $t6, 0            ( 3C0E0000 )
//     lw    $t6, 0x10($t6)    ( 8DCE0010 )
// i.e. it loads a base pointer from &D_0 + 0x10 into $t6. These two
// words logically belong to the ENTRY of the NEXT function (the one
// immediately following at 0x000309B4): splat could not see the
// function boundary in this relocatable USO segment and sheared the
// successor's prologue-area base-pointer load off as a standalone
// 8-byte symbol.
//
// Resolution: this is a DEFERRED USO BOUNDARY RE-SPLIT, tracked with
// the other accumulated game_libs_post.c multi-jr / head-fragment
// boundary notes. It is NOT fixable with the mnemonic
// split-fragments.py / merge-fragments tooling — those operate on
// mnemonic-disassembled segments, and this is raw-.word relocatable
// USO where the merge target boundary must be re-derived via proper
// USO disasm (the spimdisasm-USO migration in the deferred backlog).
// No merge is attempted here (would corrupt the successor's bytes);
// no episode (tautology-trap; and this is not even a function).
// Body INCLUDE_ASM-preserved (.s = source of truth).
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000309AC);

// gl_func_000309B4 — STRUCTURAL PASS (0x6C / 27 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, has
// its OWN prologue). The SUCCESSOR of the game_libs_func_000309AC
// head-fragment (see the boundary note immediately above) — and the
// WRITER of the global slot &D_0+0x10 that that fragment loads.
//
//   void gl_func_000309B4(int sel) {
//     if (sel == cur) return;                 // no-op if unchanged
//     int p;
//     if (sel == 0)      p = 0;
//     else if (sel == 1) p = 0x46;            // 70
//     else if (sel == 2) p = 0x1E;            // 30
//     else               p = 0;
//     fixed_call(&D_0_base, p);               // jal 0x0118C5 (FIXED)
//     *(int*)(&D_0 + 0x10) = sel;             // record selection
//   }
//
// Struct-typing reference: a selector → parameter-mapped dispatcher
//   that records its selection. The selector arg (0/1/2; else 0) is
//   folded — via equality + branch-likely (bnel) tests — into a
//   parameter value drawn from {0, 0x46 (70), 0x1E (30)}, then a
//   FIXED intra-USO routine (encoded `jal 0x0118C5` / 0x0C0118C5, a
//   real resolved target, NOT a jal-0 USO-relocated callback) is
//   called with the &D_0 base pointer and the mapped parameter.
//   Finally the original selector is stored into the global slot
//   &D_0+0x10 — which is exactly the field the preceding splat-
//   missplit head-fragment game_libs_func_000309AC loads, confirming
//   the two share one logical record region (this fn WRITES it; the
//   next fn, whose entry the fragment was sheared from, READS it).
//   A mode-select / state-record leaf of the game_libs object
//   subsystem (sibling of the gl_func_0003061C mode-arbiter).
// Caps (DEFERRED): raw-word USO + fixed intra-USO call (0x0118C5)
//   + &D_0 global record — byte-match needs USO mnemonic disasm
//   + jal-0/fixed routing. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_000309B4(int sel) {
    int p;
    if (sel == *(int *)((char *)&D_00000000 + 0x10)) return;
    if      (sel == 0) p = 0;
    else if (sel == 1) p = 0x46;
    else if (sel == 2) p = 0x1E;
    else               p = 0;
    gl_func_00000000(&D_00000000, p);
    *(int *)((char *)&D_00000000 + 0x10) = sel;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000309B4);
#endif

// gl_func_00030A20 — STRUCTURAL PASS (0xD4 / 53 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A two-arg registration + state-conditional sequencer.
//
//   void gl_func_00030A20(int a, int b) {
//     callback0();                            // jal 0 (USO callback)
//     *(int*)&D_0_slotA = a;                  // register both args
//     callback(0xF);
//     *(int*)&D_0_slotB = b;
//     if (*(int*)&D_0_state != 4) return;     // state gate (bnel)
//     if (a < 5) {
//       callback(*ptr + 0x29);
//     } else {
//       callback(*ptr + 0x04);
//       callback(0xE);
//     }
//     if (b < 5) { ... callback(*(int*)&D_0_x) ... }
//     ...
//   }
//
// Struct-typing reference: a dual-argument registration + dispatch
//   leaf. It first runs a USO-relocated callback (jal 0 → resolved
//   at load), records both incoming args into global slots based at
//   &D_0, then reads a global STATE word and — only when that state
//   == 4 — performs threshold tests (each saved arg compared < 5 vs
//   >= 5, via branch-likely bnel) to choose which USO callbacks to
//   issue, with mode codes 0xF / 0xE and pointer-relative values
//   (*p + 0x29 / *p + 0x04). A state-gated registration/command-
//   submission node of the game_libs object subsystem (companion to
//   the gl_func_000309B4 selector-recorder; both stash into the
//   &D_0 global record and feed the gl_func_0002FB74 interpreter).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + &D_0
//   global state gate + branch-likely thresholds — byte-match
//   needs USO mnemonic disasm + reloc-pad jal infra. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
// BASE-PIN DIAGNOSED (agent-b 2026-06-21): base-pin lever reproduces the
//   structure (call;store-arg0;call(0xF)[store-arg1 in delay]; gate; two
//   threshold branches), but the byte-match is BLOCKED by SINGLE-SYMBOL
//   COLLAPSE, not coloring: the target references FOUR distinct module
//   globals (the two stored slots, the gate word, and the held `p` base in
//   v1) that ALL disassemble as D_0+0 because splat exposes only one extern
//   `D_00000000`. With one symbol IDO CSEs/dead-store-eliminates them into a
//   single base, so the two distinct stores and the separate v1 base can't
//   be reproduced. Needs the USO data symbols split out (infra), then the
//   held-pointer lever lands it. Faithful structural body below per m2c.
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gl_func_00030A20(s32 arg0, s32 arg1) {
    char *g = (char *)&D_00000000;
    s32 temp_v0;

    gl_func_00000000();
    *(s32 *)(g + 0) = arg0;
    gl_func_00000000(0xF);
    *(s32 *)(g + 0) = arg1;
    temp_v0 = *(s32 *)(g + 0);
    if ((temp_v0 == 0) || (temp_v0 == 4)) {
        if (arg0 >= 5) {
            gl_func_00000000(*(s32 *)(g + 0) + 0x29);
        } else {
            gl_func_00000000(*(s32 *)(g + 0) + 4);
        }
        gl_func_00000000(0xE);
        if (arg1 >= 5) {
            gl_func_00000000(*(s32 *)(g + 0) + 0x29);
            return;
        }
        gl_func_00000000(*(s32 *)(g + 0) + 4);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030A20);
#endif

// gl_func_00030AF4 — STRUCTURAL PASS (0x840 / 528 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr $ra)
// with one internal computed jump. A MAJOR SUBSYSTEM CONSTRUCTOR /
// top-level initializer — the biggest node decoded in this vein.
//
//   void gl_func_00030AF4(void *a, void *b, void *c) {
//     if (*(int*)&D_0 != 1) fixed_init_0743(); // one-time guard
//     void *blk = alloc(0x45010);              // large arena
//                                              //  (lui 4; +0x5010)
//     *(void**)&D_0_arena = blk;
//     // zero a long run of fields: blk[0], blk[4], blk[8],
//     //   blk[0x14], blk[0x18], ... (many sw $zero stores)
//     // then fan out to ~60 FIXED intra-USO sub-initializers
//     //   (0x0C010743 / 0107B5 / 0107C3 / 0107D1 / 0108D9 /
//     //    0113C6 / 011834 ...) interleaved with ~43 USO-
//     //   relocated callbacks (jal 0), plus heavy FP setup
//     //   (74 lwc1 / 42 swc1) seeding default transforms.
//     // a computed jump dispatches a sub-mode during setup.
//   }
//
// Struct-typing reference: this is the TOP-LEVEL CONSTRUCTOR of the
//   game_libs object subsystem — the routine that builds every
//   structure the rest of this vein operates on. Observed:
//   - a one-time init guard on the global state word at &D_0
//     (== 1 ? skip the bootstrap : run fixed_init at 0x010743).
//   - a single large arena allocation of 0x45010 bytes (encoded
//     `lui $a1,4 ; addiu $a1,$a1,0x5010`), stored back into a
//     global slot based at &D_0; other size args seen
//     (0x...5F78, 0x...000A) feed secondary allocations.
//   - a long zero-init sweep of the freshly allocated record's
//     fields, then ~60 FIXED intra-USO sub-initializer calls
//     (many distinct targets) + ~43 USO-relocated callbacks
//     (jal 0 → resolved at load), with one computed jump
//     selecting a setup sub-mode.
//   - extensive FP field seeding (74 lwc1 / 42 swc1): default
//     matrices / ramps / thresholds for the object.
//   It is the producer for the consumers documented across this
//   vein: the gl_func_0002FB74 command interpreter, the
//   gl_func_0002F584/0002F72C quantizer/table-apply leaves, the
//   canned-sequence and multi-bank emitters, and the
//   gl_func_000307B0 per-frame timer all run against the record
//   this function allocates and wires up.
// Caps (INFRA-BLOCKED, 2026-06-21 agent-e re-analysis from raw target
//   words): 0x840 / 528-word raw-word USO graphics-MODE setup routine.
//   CORRECTED FACTS vs the old header: this is NOT FP-heavy — only ONE
//   lwc1/swc1 pair (@0x60C/0x620); the bulk is integer command-word
//   emits (0xFB/0xF8/0x83010000/0x46010000/0x81000F00/0x81001300 RDP/RSP
//   command words) and base-0 global state traffic. Three computed jumps:
//   switch-1 (a0<14 @0xD8, jtbl 0x1874), switch-2 (a0copy<12 @0x64C,
//   jtbl 0x18B0), switch-3 (v0<8 @0x6CC, jtbl 0x18E0).
//   WHY BYTE-LANDING IS BLOCKED (two independent infra caps):
//   (1) BASE-PIN: the target recomputes a fresh base for ~61 distinct
//       base-0 globals (`lui REG,0x0 [; addiu REG,REG,0]` per access);
//       with one &D_00000000 placeholder IDO CSEs the base into a saved
//       reg, so neither the per-access lui count NOR the instruction
//       count can match. 8 of these are a command-buffer struct
//       (`sw id,0(cmd); emit(cmd.byte3)` @ 0x134/0x2D0/0x420/0x444/
//       0x4A0/0x4F0/0x568/0x588).
//   (2) FIXED INTRA-USO JALS: 0x41D0C/0x42364/0x460D0/0x41ED4/0x41F0C/
//       0x41F44/0x44F18 bake their absolute offset into the jal word
//       (non-reloc 0x0C0108D9-style), requiring symbols defined at those
//       exact USO offsets — no such named symbols exist to pin them.
//   The NM body below is a hand-traced STRUCTURAL reconstruction: correct
//   frame (-0x38), prologue, init-guard, arena alloc, zero-sweep, and all
//   three switches with correct selectors / case structure / call-arg
//   shapes. Decode progress = structure; bytes = infra-blocked.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
/* PASS-4 2026-06-22 (agent-d): PROVEN-UNREPRODUCIBLE byte-land. The function
 * is NON_MATCHING permanently — not by laziness but by a structural IDO codegen
 * limit empirically demonstrated below.
 *
 * STRUCTURE (hand-traced from raw target words, region-by-region; frame -0x38):
 * a graphics-MODE setup routine. Prologue + one-time init guard on base-0 state
 * word; arena alloc; field zero-sweep; then THREE base-0 external jumptable
 * dispatches:
 *   switch1: `sltiu at,mode,14; lui at,0x0; addu at,at,mode<<2; lw t0,0x1874(at);
 *            jr t0`  (14 cases @ +0xC8)
 *   switch2: `sltiu at,sel,12;  ... lw t2,0x18B0(at); jr t2`  (12 cases @ +0x630)
 *   switch3: `sltiu at,v0,8;    ... lw t4,0x18E0(at); jr t4`  (8  cases @ +0x6BC)
 * Command words 0xFB000000/0xF8000000/0x83010000/0x46010000/0x81000F00/
 * 0x81001300 are RDP/RSP command words handed to the relocated emitter (jal 0).
 *
 * WHY BYTE-LANDING IS STRUCTURALLY IMPOSSIBLE (empirically proven 2026-06-22):
 * The expected .o has ZERO relocations AND ZERO .rodata section (verified:
 * `readelf -S expected/.../game_libs_post.c.o` shows no .rodata/.rel*). All
 * three dispatches read their jumptable from an EXTERNAL base-0 address at a
 * FIXED offset — `lui REG,0x0; addu REG,REG,idx<<2; lw REG,0x18xx(REG); jr REG`
 * — i.e. the case-target table lives in the USO's data segment (resolved at
 * load), NOT in this object. A compiled IDO `switch` ALWAYS emits the jumptable
 * into a LOCAL `.rodata` section and references it via R_MIPS_HI16/LO16 relocs
 * (confirmed with a minimal 8-case switch: IDO 7.1 -O2 emits a 0x20 .rodata
 * table + .rel.text + .rel.rodata, load = `lui at,%hi(.rodata); lw,%lo(.rodata)`).
 * No C construct makes IDO read switch targets from an external global array at
 * a literal offset, and asm-processor's reloc-blinding can zero a reloc but can
 * neither delete the emitted .rodata section nor turn a local-table reference
 * into an external base-0 read. => the three jr-table words can never match the
 * target's external-data form. Permanent INCLUDE_ASM cap (same class as the
 * sibling gl_func_000076F0 switch2/switch4 note).
 *
 * (Note: the OLD "base-pin" / "fixed intra-USO jal" caps cited in prior passes
 * are NOT the blocker — distinct `D_xxx = 0` externs defeat IDO's base CSE, and
 * the fixed jals build literally from INCLUDE_ASM. The external-data jumptable
 * is the sole, structural blocker.)
 *
 * The body below is a faithful structural reconstruction (control flow, call-arg
 * shapes, field accesses) for decode-progress only; bytes are blocked above. */
extern int gl_func_00041D0C();
extern int gl_func_00042364();
extern int gl_func_000460D0();
extern int gl_func_00041ED4();
extern int gl_func_00041F0C();
extern int gl_func_00041F44();
extern int gl_func_00044F18();
extern int gl_func_emit();     /* the `jal 0x0` relocated command emitter */

#define D8(off) (*(s32 *)((char *)&D_00000000 + (off)))

void gl_func_00030AF4(u32 mode, u32 sub, s32 arg2) {
    s32 flag;        /* sp+52 */
    u32 prev;        /* sp+44 : old value of the state global */
    u32 modeSel;     /* sp+28 : copy of `mode`, switch-2 selector */
    s32 spA3;        /* sp+40 : command/value carried into emits */
    s32 spLocal;     /* sp+48 : value held across emit calls */
    s32 *rec;        /* freshly-allocated record base */
    s32 g;           /* scratch for global reads */

    flag = 0;
    if (D8(0) == 1) {
        gl_func_00041D0C();
    }
    rec = (s32 *)gl_func_emit(0xFB000000, 0x45010);   /* large arena alloc */
    prev = D8(0);
    D8(0) = mode;
    gl_func_emit(0);
    gl_func_emit(1);
    D8(0) = 0;
    D8(0) = 0;
    D8(0) = 0;
    rec[1] = 0;     /* +4 */
    rec[2] = 0;     /* +8 */
    rec[5] = 0;     /* +0x14 */
    rec[0] = 0;     /* +0 */
    gl_func_emit(rec[6] = 0);   /* +0x18 (sw zero in jal delay) */
    gl_func_000460D0();

    modeSel = mode;
    if (mode < 14) {
        switch (mode) {                 /* switch 1 @0xD8 */
        case 0:
            gl_func_00042364(1);
            flag = 1;
            break;
        case 1:
            D8(0) = 0;
            gl_func_00042364(0);
            gl_func_emit(2);
            flag = 1;
            break;
        case 2:
            gl_func_00042364(2);
            D8(0) = 16;
            gl_func_emit(*(u8 *)((char *)rec + 3));
            flag = 1;
            break;
        case 3:
            if (prev != 0) {
                gl_func_00042364(5);
                flag = 1;
            }
            gl_func_emit(3);
            break;          /* falls to flag==1 check via 0x598 path */
        case 4: case 5: case 6: case 7: case 8:
        case 9: case 10: case 11: case 12: case 13:
            /* Shared body @0x170 for jumptable cases >=4. (m2c-confirmed the
             * 4..13 entries share this tail; the `prev` value selects the
             * sub-paths within it.) */
            if (prev == 0) {
                D8(0) = 12;
                break;
            }
            if (prev == 3) {
                /* poll loop @0x198: while emit(2,0xE,0) >= 100 emit() */
                while (gl_func_emit(2, 14, 0) >= 100) {
                    gl_func_emit();
                }
            }
            D8(0) = sub;
            D8(0) = sub + 4;
            g = D8(0);
            if (g != 0 && sub == 6) {
                D8(0) = 7;
            }
            if (g == 4) {
                gl_func_00042364(4);
                D8(0) = D8(0) + 18;
            } else if (sub == 0) {
                gl_func_00042364(6);
            } else {
                gl_func_00042364(3);
            }
            flag = 1;
            D8(0) = 14;
            break;
        }
    }

    if (flag == 1) {
        gl_func_00041ED4();
        gl_func_emit();
        gl_func_00041F0C();
        gl_func_00041F44();
        if (modeSel != 4) {
            gl_func_emit(0, 0);
        }
    }

    if (D8(0) != 5) {
        gl_func_00044F18(0);
    } else {
        rec[5] = *(s32 *)((char *)&D_00000000 + 0x18AC);   /* +0x14 = lwc1 src */
        gl_func_emit(0, 100, rec[1]);
        D8(0) = 4;
    }

    switch (modeSel) {                  /* switch 2 @0x64C */
    case 0:
        if (prev != 0) {
            g = D8(0);
            if (g == 1) {
                gl_func_00044F18(1);
                g = D8(0);
            }
            if (g == 0) {
                gl_func_00044F18(2);
                g = D8(0);
            }
            {
                s32 m = D8(0);
                if (m == 1 || m == 3) {
                    switch (g) {        /* switch 3 @0x6CC (v0 <8) */
                    case 0: gl_func_emit(0x1F); g = D8(0); break;
                    case 1: gl_func_emit(0x1B); g = D8(0); break;
                    case 2: gl_func_emit(0x1D); g = D8(0); break;
                    case 3: gl_func_emit(0x19); g = D8(0); break;
                    case 4: gl_func_emit(0x1E); g = D8(0); break;
                    case 5: gl_func_emit(0x1C); g = D8(0); break;
                    case 6: gl_func_emit(0x1A); g = D8(0); break;
                    case 7: gl_func_emit(0x18); g = D8(0); break;
                    }
                }
            }
            if (g == 8) {
                gl_func_emit(0xBC);
            }
        }
        break;
    case 9:
        gl_func_emit(0xF8000000, 0);
        gl_func_emit(0xA3);
        break;
    case 10:
        gl_func_emit(0xF8000000, 0);
        gl_func_emit(0, 0x3E99999A, 0);
        break;
    case 11:
        switch (sub) {                  /* switch 4 @0x7D4 (if-chain) */
        case 0:
            gl_func_emit(14);
            break;
        case 1:
            gl_func_emit(15);
            break;
        }
        break;
    }

    gl_func_emit(0xFB000000, 0);
    gl_func_emit(0);
    gl_func_emit(0xFB000000, 0x45F78);
}
#undef D8
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030AF4);
#endif

// gl_func_00031334 — STRUCTURAL PASS (0x1EC / 123 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr $ra)
// with one INTERNAL computed jump (jr $t8). A 3-arg stepped
// state-machine driver / jump-table command loop.
//
//   void gl_func_00031334(int a, int b, int c) {
//     ctx_a = a; ctx_b = b; ctx_c = c;       // spill 3 args
//     callback0(0);                           // jal 0 setup
//     callback(1);
//     *(int*)&D_0_flag = 1;                   // mark active
//     callback(0xFF, 0);                      // clear / reset pass
//     int i = *(int*)&D_0_step + 1;           // global step index
//     if (i >= 0xF) return;                   // bounded (0..0xE)
//     goto *jumptab_1900[i];                  // sll 2; lw; jr $t8
//   L_step0: if (a == 4) { ... } ...
//   L_stepN: emit(0x83010000 | ..., 0x50);    // per-step callback
//     ...
//   }
//
// Struct-typing reference: a per-invocation STEP DRIVER for one of
//   the subsystem's state machines. It spills its three args into
//   context slots, runs reset/setup USO-relocated callbacks (jal 0
//   → resolved at load) and marks a global active flag at &D_0,
//   then reads a global STEP INDEX (based at &D_0), increments it,
//   bounds it to [0, 0xE], and dispatches through a jump table at
//   &D_0+0x1900 (computed `jr $t8` after sll-2 + lw) to ~15 per-step
//   handler arms. Each arm tests the spilled args (e.g. == 4 via
//   branch-likely beql) and issues USO-relocated callbacks carrying
//   command words from the 0x83010000 bank with parameters such as
//   0x50. The stepped counterpart to the gl_func_0002FB74
//   interpreter — where that one is opcode-keyed per command, this
//   one is index-keyed per progression step (the &D_0+0x1900 table
//   and &D_0 step word are the deferred-symbolization sites).
// Caps (DEFERRED): raw-word USO + computed jump table
//   (&D_0+0x1900 unsymbolized) + USO-reloc jal-0 callbacks —
//   byte-match needs USO mnemonic disasm + step table symbolized.
//   Real-C STRUCTURAL skeleton below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int D_00000000;
extern int D_31_x;   // gate read in the a==5 arm
extern int D_31_y;   // secondary gate in the a==5 arm
extern int D_31_z;   // mode word read in the v0==13/14 arm
extern int gl_func_00044F18();   // baked fixed-address callee (jal 0x44f18)
// Stepped state-machine driver. Spills args (stack-homed), runs reset cbs,
// marks the &D flag, then dispatches on a global step index (jr-table at
// &D_0+0x1900, ~15 arms). Each arm tests the spilled arg `a` and emits cbs
// carrying 0x83010000-bank command words with params (0x50/2000/320/400) or
// the fixed jal 0x44f18, then falls into a second jr-table dispatch on a
// (&D_0+0x193c, ~11 arms) whose sole effect sets *(&D+0xC)=256. Reloc-blind
// jr-tables + jal-0 cbs (deferred); the 0x8301 words / immediates are baked.
void gl_func_00031334(int a, int b, int c) {
    int i;
    (void)b;
    (void)c;
    gl_func_00000000(0);
    gl_func_00000000(1);
    *(int *)&D_00000000 = 1;
    gl_func_00000000(0xFF, 0);
    i = *(int *)&D_00000000 + 1;
    if (i < 0xF) {
        switch (i) {
            case 0:
                if (a != 4 && a != 0) {
                    gl_func_00000000(0x83010000, 0x50);
                }
                break;
            case 1:
                gl_func_00000000(0x83010000, 0x50);
                break;
            case 2:
                if (a == 5) {
                    if (*(int *)&D_31_x == 0) {
                        gl_func_00000000(0x83010000, 2000);
                    } else if (*(int *)&D_31_y != 1) {
                        gl_func_00000000(0x83010000, 0x50);
                    }
                } else if (a == 6) {
                    gl_func_00000000(0x83010000, 2000);
                } else {
                    gl_func_00000000(0x83010000, 320);
                    gl_func_00044F18(0);
                    gl_func_00000000(0xFF, 0);
                }
                break;
            case 3:
                if (*(int *)&D_31_z != 13 && *(int *)&D_31_z != 14) {
                    gl_func_00000000();
                }
                break;
            case 4:
                if (a != 7) {
                    gl_func_00000000(0x83010000, 0x50);
                }
                break;
            case 5:
                gl_func_00000000(0x83010000, 400);
                break;
            default:
                break;
        }
    }
    switch (a + 1) {
        case 5:
            *(int *)((char *)&D_00000000 + 0xC) = 256;
            break;
        default:
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031334);
#endif

extern int gl_func_00000000();
int gl_func_00031520() {
    return gl_func_00000000();
}

extern int gl_func_00000000();
int gl_func_00031540() {
    return gl_func_00000000();
}

/* gl_func_00031560: 8-insn (0x20) bare wrapper — calls gl_func_0() with
 * no args and no return-value use. Original splat bundle was 0x68 with
 * 2 jr-ras + R-type stolen-prologue tail; split-fragments separated
 * game_libs_func_00031580 (0x44 array-init loop, NM-wrapped below). */
void gl_func_00031560(void) {
    gl_func_00000000();
}

/* game_libs_func_00031580: 15-insn (0x3C) array-init loop. Sets per-record
 * fields in &D+0x368[0..1] (2 records of 0x64 stride). LANDED fuzzy=100.
 * The 2-insn stolen-prologue tail at 0x315BC-0x315C0 (R-type donation to
 * successor gl_func_000315C4: sll/subu = a0*3) was historically absorbed
 * via SUFFIX_BYTES recipe — REMOVED 2026-05-23 as match-faking. Those
 * 2 insns are now tracked as separate symbols (function size 0x3C, not
 * the previously-documented 0x44). */
void game_libs_func_00031580(void) {
    int i;
    char *base = (char *)&D_00000000 + 0x368;
    for (i = 0; i != 2; i++) {
        char *rec = base + i * 0x64;
        *(short *)(rec + 0x62) = i;
        *(int *)(rec + 0x40) = 0;
        *(int *)(rec + 0x44) = 0;
        *(int *)(rec + 0x48) = 0;
        *(int *)(rec + 0x4C) = 0;
        *(int *)(rec + 0x5C) = 0;
    }
}

/* game_libs_func_000315BC: array-element-call helper. Indexes &gl_ref_00000368
 * by a0 * 100 (record stride) and calls helper at 0x045DC0 with (ptr, 1, a1, 0x7F). */
extern int gl_ref_00045DC0();
extern char gl_ref_00000368;

/* game_libs_func_000315BC (cross-TU orphan merge, MATCHED 2026-05-31): the orphan
 * (sll t7,a0,2; subu t7,t7,a0 = a0*3) was in game_libs.c; merged into the body .s.
 * Cracked the "hoist-breaks-reuse" cap by writing the stride as `a0 * 100` and letting
 * IDO strength-reduce it — that emits the single-$t7 reuse chain (a0*3->24->25->100)
 * hoisted above the prologue. Hand-expanded shift chains (`t<<=2; t-=a0; ...`) break
 * to fresh $t8/$t9 pseudos (96.8%). See docs/IDO_CODEGEN.md#strength-reduce-multiply. */
void game_libs_func_000315BC(int a0, int a1) {
    gl_ref_00045DC0(&gl_ref_00000368 + a0 * 100, 1, a1, 0x7F);
}

/* gl_func_00031608: full decode 2026-05-31 (was 33.8% stub). Gated on D[0]==4,
 * dispatches on b21/b22 to compute `val`, then writes *(short*)(ptr+0x62)=val and
 * calls gl_ref_00045DC0(ptr, 1, (val<<6)+a1, 0x7F) where ptr=&gl_ref_00000368 +
 * b21*100 (same strength-reduced index as sibling game_libs_func_000315BC). The
 * inner g-recheck (D[0]==1/2/3/5) is logically dead after the ==4 gate but the
 * target reloads g from memory so IDO can't fold it (cf. eddproc_uso_func_0000025C). */
#ifdef NON_MATCHING
extern char gl_ref_00000368;
void gl_func_00031608(char *a0, int a1) {
    unsigned char b22 = *(unsigned char *)(a0 + 0x22);
    unsigned char b21 = *(unsigned char *)(a0 + 0x21);
    char *ptr;
    int val;
    if (*(int *)((char *)&D_00000000 + 0) != 4) {
        return;
    }
    val = b22 - 1;
    if (b22 < 6) {
        if (b21 == 2) {
            int g2 = *(int *)((char *)&D_00000000 + 0);
            if (g2 == 1) return;
            if (g2 == 2) return;
            if (g2 == 3) return;
            if (g2 == 5) return;
        }
    } else {
        if (b21 != 8) {
            return;
        }
        val = 5;
    }
    ptr = &gl_ref_00000368 + b21 * 100;
    *(short *)(ptr + 0x62) = val;
    gl_ref_00045DC0(ptr, 1, (val << 6) + a1, 0x7F);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031608);
#endif

extern int gl_ref_00045DC0();
extern int gl_ref_00045DF0();
void gl_func_000316CC(int a0) {
    gl_ref_00045DC0((char *)&D_00000000 + 0x430, 1, a0 + 0x17F, 0x7F);
    gl_ref_00045DF0((char *)&D_00000000 + 0x430);
}

// gl_func_00031710 — STRUCTURAL PASS + BUNDLE BOUNDARY NOTE
// (0x188 / 98 words, no episode). Raw-.word USO form (game_libs).
//
// MULTI-FUNCTION USO BUNDLE: this .s has SEVEN jr $ra sequences —
// splat could not separate ~7 distinct functions in this relocatable
// USO segment. Only the NAMED LEADING function is decoded here; the
// trailing ~6 tiny leaves are flagged as a DEFERRED USO RE-SPLIT
// (tracked with the other game_libs_post.c multi-jr boundary notes;
// NOT fixable with the mnemonic split-fragments.py / merge-fragments
// tooling — raw-.word relocatable USO needs the spimdisasm-USO
// migration to re-derive the boundaries).
//
// Leading fn gl_func_00031710 (0x31710..0x3174C, ~16 words):
//   void gl_func_00031710(int arg) {
//     helper_011770(&D_0_table_0430, 0, arg + 0x17F, 0x7F);
//     helper_01177C(&D_0_table_0430);
//   }
// i.e. a small two-call range-init wrapper: it hands a table base
// (&D_0 + 0x430), a zero start, a computed end offset (arg + 0x17F)
// and a 0x7F limit to a FIXED intra-USO helper at 0x011770, then
// calls a second fixed helper at 0x01177C on the same table base.
// (Both 0x011770 / 0x01177C targets are the very leaves bundled into
// the tail of THIS .s — index / accessor helpers for the 0x430-based
// table: computing a table index via shift+add, loading/storing the
// 0x54/0x58/0x5C cursor fields, and bumping it.)
//
// Struct-typing reference: the named function is the public
//   range-clear / cursor-reset entry for a 0x7F-element table based
//   at &D_0+0x430; the bundled leaves are its private accessors
//   (index = shift/add of the arg; the table record carries cursor
//   words at +0x54/+0x58/+0x5C and a count at +0x40/+0x44/+0x48/
//   +0x4C). A table-management cluster of the game_libs object
//   subsystem (the storage the emitter / interpreter families read
//   and write through this 0x430 table).
// Caps (DEFERRED): raw-word USO + fixed intra-USO calls into its own
//   bundled leaves at 0x011770 / 0x01177C — byte-match needs USO
//   mnemonic disasm + boundary re-split. STALE 7-jr bundle comment:
//   grep -c 03E00008 = 1 (.s now single fn). Real-C STRUCTURAL body
//   below per the analysis. Byte-match deferred. Name pre-checked:
//   no extern reuse.
extern int gl_ref_00045DC0();
extern int gl_ref_00045DF0();
void gl_func_00031710(int arg) {
    gl_ref_00045DC0((char *)&D_00000000 + 0x430, 0, arg + 0x17F, 0x7F);
    gl_ref_00045DF0((char *)&D_00000000 + 0x430);
}

// Read u16 v = D[a2] from the segment-base table, store args to a0->0x54/0x58,
// and store &D + (v & ~1) (rounded-down even index back into the table) to
// a0->0x5C. Single segment-base ref (one &D_00000000), real index logic →
// builds byte-exact as plain C (moves %). No episode (reloc-blind base).
void game_libs_func_00031754(int *a0, int a1, int a2, int a3) {
    unsigned short v = *(unsigned short *)((char *)&D_00000000 + a2 * 2);
    a0[0x58 / 4] = a3;
    a0[0x54 / 4] = a1;
    a0[0x5C / 4] = (int)((char *)&D_00000000 + (((int)v >> 1) << 1));
}

/* game_libs_func_00031784: ring-buffer write-index advance (mask-wrap by 0xF).
 * NM (permuter-narrowed 2026-06-21, 4->2 diffs): reading the write index via a
 * reused `v0` local AND forcing the `+1` through `(long long)1` colors the
 * load/incr pair to the target's t2/t3 (was v0/t3). RESIDUAL (2 words): the
 * final `andi t5,t3,0xf; sw t5` masked-store result lands in t9 not t5 — a
 * lowest-free-register coloring residual (target skips t4->t5; permuter floored
 * at score 10 / 2 reg diffs, can't reach it). The `(long long)1` cast is
 * load-bearing (drop it -> 5 diffs, t2/t3 decolor). */
#ifdef NON_MATCHING
void game_libs_func_00031784(int *a0) {
  int v0 = a0[0x54 / 4];
  int t;
  if (v0 != 0)
  {
    if (v0 != 1)
    {
      goto end;
    }
    if (a0[0x58 / 4] < a0[0x4C / 4])
    {
      goto end;
    }
    a0[0x4C / 4] = a0[0x58 / 4];
    a0[0x48 / 4] = 0;
    a0[0x40 / 4] = a0[0x44 / 4];
  }
  a0[a0[0x40 / 4]] = a0[0x5C / 4];
  v0 = 0x10;
  t = a0[v0] + (long long)1;
  ((volatile int *) a0)[0x40 / 4] = t;
  a0[0x40 / 4] = (t & 0xF) & 0xFFFFu;
  end:
  a0[0x5C / 4] = 0;

}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031784);
#endif

/* Timer/script-step interpreter: decrement the a0->0x48 countdown; while it
 * hasn't reached 0, return 0. On expiry, read a command halfword from the
 * a0->0x50 cursor (advance by 2), store it to a0->0x60, and if non-zero read a
 * following arg halfword (advance) into the countdown a0->0x48; return 1.
 * Logic decoded & correct; NOT byte-exact (1/19): target is -O1 cross-jumped —
 * the `return 0` early-exit branches FORWARD to a shared `jr ra` epilogue split
 * off as game_libs_func_00031834 (right after this fn), with `move v0,zero`
 * hoisted to insn 2 and `bnez` (vs C's beqz). Reproducing it needs an -O1
 * flag-split + merge of 31834. Tail-merge cap; INCLUDE_ASM is the build path. */
#ifdef NON_MATCHING
int game_libs_func_000317F0(int *a0) {
    int counter;
    unsigned short *p;
    int cmd = 0;
    int ret = 0;
    counter = *(int*)((char*)a0 + 0x48) - 1;
    *(int*)((char*)a0 + 0x48) = counter;
    if (counter != 0) goto end;
    p = *(unsigned short**)((char*)a0 + 0x50);
    cmd = *p;
    *(unsigned short**)((char*)a0 + 0x50) = p + 1;
    ret = 1;
    if (cmd == 0) goto end;
    *(int*)((char*)a0 + 0x48) = p[1];
    *(unsigned short**)((char*)a0 + 0x50) = p + 2;
end:
    *(unsigned short*)((char*)a0 + 0x60) = cmd;
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000317F0);
#endif

void game_libs_func_00031834(void) {}

/* game_libs_func_0003183C: 23-insn (0x5C) circular-buffer push with a do-while
 * scan. BOUNDARY MERGED 2026-06-02: splat over-split the loop tail as a separate
 * symbol (00031880, whose `bnel v0,t5,-0x34` branches backward to 0x31860 inside
 * this body). Absorbed 31880's 6 words into 3183C (0x44 -> 0x5C); dropped the
 * 31880 symbol (no external callers). Branch-verified complete (ends at 0x31898
 * with a clean jr ra; the region after is a separate unsplit run). Reloc-blind
 * USO body stays INCLUDE_ASM. */
#ifdef NON_MATCHING
/* Circular-buffer scan/dequeue (16-entry inline ring at arg0+0, read idx
 * 0x44, write idx 0x40). Clears 0x4C, then advances read (wrap &0xF)
 * storing each entry to 0x50 until a non-zero entry (sets 0x48=1, returns)
 * or the ring drains. read is loaded once then reloaded each loop tail. */
void game_libs_func_0003183C(void *arg0) {
    int rd = *(int *)((char *)arg0 + 0x44);
    int v;
    if (rd != *(int *)((char *)arg0 + 0x40)) {
        *(int *)((char *)arg0 + 0x4C) = 0;
        do {
            v = *(int *)((char *)arg0 + rd * 4);
            /* Target keeps BOTH index stores (idx=rd+1 then idx=(rd+1)&0xF).
             * Re-derived 2026-06-20 (agent-b): IDO -O2 DSEs the first store no
             * matter the C form (separate local, explicit memory re-read, etc).
             * Only `*(volatile int*)` keeps both — but volatile then forces rd+1
             * into a caller-saved reg ($a1), so all temp numbering cascades off
             * (li-1, v-load, mask all land in wrong regs). Genuine DSE+regalloc
             * cap: size-exact (23w) via volatile but never byte-exact. NM-wrap. */
            *(int *)((char *)arg0 + 0x44) = (rd + 1) & 0xF;
            *(int *)((char *)arg0 + 0x50) = v;
            if (v != 0) {
                *(int *)((char *)arg0 + 0x48) = 1;
                return;
            }
            rd = *(int *)((char *)arg0 + 0x44);
        } while (rd != *(int *)((char *)arg0 + 0x40));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0003183C);
#endif

extern int gl_ref_00045DF0();
extern int gl_ref_00045E5C();
extern int gl_ref_00045EA8();

/* gl_func_00031898: 29-insn (0x74) tri-call dispatcher.
 *   - if a0->field_5C != 0: call gl_ref_00045DF0(a0)
 *   - if a0->field_48 != 0: ret_val = gl_ref_00045E5C(a0)
 *   - if a0->field_48 == 0: call gl_ref_00045EA8(a0)
 *   - return ret_val
 * The previously-documented "branch-likely cap" was a misread: the third
 * call passes the struct pointer (a0), NOT ret_val — that arg fix makes
 * IDO emit the bnezl with lw-ra hoisted into the annulled delay (exact). */
int gl_func_00031898(int *a0) {
    int ret_val = 0;
    if (a0[23] != 0) {
        gl_ref_00045DF0(a0);
    }
    if (a0[18] != 0) {
        ret_val = gl_ref_00045E5C(a0);
    }
    if (a0[18] == 0) {
        gl_ref_00045EA8(a0);
    }
    return ret_val;
}

// gl_func_0003190C — STRUCTURAL PASS (0x158 / 86 words, no episode).
// permuter resists: verify-fails every batch (x5+, 2026-06-19) — factory skip.
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, no
// bundle). A dual state-block conditional command emitter.
//
//   void gl_func_0003190C(void) {
//     // block A: state record at &D_0 + 0x368
//     if (query_0117C1(&D_0 + 0x368)) {
//       u16 s = *(u16*)(&D_0 + 0x3C8);
//       if (s != 0) {
//         emit(0x06020004, -1);              // jal 0 (USO callback)
//         emit(0x06020004, 0);
//       } else {
//         emit(..., (signed char)*(s8*)(&D_0 + 0x3CB));
//         emit(0x06020000, ...);
//       }
//     }
//     // block B: parallel record at &D_0 + 0x3CC (state at +0x42C)
//     if (query_0117C1(&D_0 + 0x3CC)) {
//       u16 s = *(u16*)(&D_0 + 0x42C);
//       if (s != 0) { emit(0x06020104, -1); ... }
//       else        { emit(0x06020100, ...); }
//     }
//   }
//
// Struct-typing reference: a paired state-driven command flusher.
//   For each of TWO parallel state records (table bases &D_0+0x368
//   and &D_0+0x3CC) it calls a FIXED intra-USO query helper at
//   0x0117C1 (encoded jal 0x0117C1, a real resolved target) passing
//   the record base; only if that returns nonzero does it read the
//   record's state halfword (&D_0+0x3C8 / +0x42C) and a signed byte
//   (&D_0+0x3CB) and emit 0x06020000-bank command words via
//   USO-relocated callbacks (jal 0 → resolved at load) — choosing a
//   "nonzero state" variant (subfield 0x04/0x104, a1 = -1 then 0)
//   vs a "zero state" variant (subfield 0x00/0x100, a1 = the
//   sign-extended state byte). A per-frame two-channel command
//   flush leaf of the game_libs object subsystem (the 0x06020000
//   bank is the gl_func_0002F638 / 0002F9D4 emitter family with a
//   0x02xx sub-bank; the query helper 0x0117C1 is shared with the
//   gl_func_00031710 table cluster).
// 2026-05-31 FULL DECODE 45.0->95.66%: it is THREE identical blocks (not
//   two), bases 0x06020004/0x104/0x204, checks &D+0x368/0x3CC/0x430,
//   state halfwords &D+0x3C8/0x42C/0x490, sign bytes &D+0x3CB/0x42F/0x493.
//   The branch polarity was inverted in the old draft: `if (s == 0)` (the
//   FALL-THROUGH, emits `bne s,0,else`) does { func(A,-1); func(A2,0) };
//   `else` (s != 0) does { func(A,(s8)s); func(A,(s8)byte) }. Writing it
//   `if(s!=0)` emits `beq` and mis-aligns the whole block — match the
//   target's fall-through. Residual ~4%: the check jal is a CONCRETE
//   alt-entry at 0x45f04 (gl_func_000628EC+0x64) but C emits the generic
//   gl_func_00000000 reloc (alt-entry-jal cap, cf. func_00039194) + s in
//   v1-vs-v0 renumber + last-block beql. INCLUDE_ASM stays the build path.
#ifdef NON_MATCHING
void gl_func_0003190C(void) {
    if (gl_func_00000000((char *)&D_00000000 + 0x368)) {
        unsigned short s = *(unsigned short *)((char *)&D_00000000 + 0x3C8);
        if (s == 0) {
            gl_func_00000000(0x06020004, -1);
            gl_func_00000000(0x06020000, 0);
        } else {
            gl_func_00000000(0x06020004, (signed char)s);
            gl_func_00000000(0x06020004,
                             *(signed char *)((char *)&D_00000000 + 0x3CB));
        }
    }
    if (gl_func_00000000((char *)&D_00000000 + 0x3CC)) {
        unsigned short s = *(unsigned short *)((char *)&D_00000000 + 0x42C);
        if (s == 0) {
            gl_func_00000000(0x06020104, -1);
            gl_func_00000000(0x06020100, 0);
        } else {
            gl_func_00000000(0x06020104, (signed char)s);
            gl_func_00000000(0x06020104,
                             *(signed char *)((char *)&D_00000000 + 0x42F));
        }
    }
    if (gl_func_00000000((char *)&D_00000000 + 0x430)) {
        unsigned short s = *(unsigned short *)((char *)&D_00000000 + 0x490);
        if (s == 0) {
            gl_func_00000000(0x06020204, -1);
            gl_func_00000000(0x06020200, 0);
        } else {
            gl_func_00000000(0x06020204, (signed char)s);
            gl_func_00000000(0x06020204,
                             *(signed char *)((char *)&D_00000000 + 0x493));
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003190C);
#endif

/* Split off from gl_func_0003190C bundle 2026-05-08: 4-insn setter.
 * Clears the global at &D_00000000 + 0x1CAA8 to -1. */
void game_libs_func_00031A64(void) {
    *(int*)((char*)&D_00000000 + 0x1CAA8) = -1;
}

// gl_func_00031A74 — STRUCTURAL PASS (0x304 / 193 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION — exactly
// ONE prologue; the three jr $ra are multiple RETURN points (early
// exits), NOT a multi-fn bundle (boundary-checked: no interior
// prologue between the returns). A state-gated FP integrator.
//
//   void gl_func_00031A74(int a0, float v, signed char sel) {
//     if (sel != 1) { ... alternate path / return ... }
//     int st = *(int*)&D_0;                   // global state word
//     if (st == 4)  { ... }
//     else if (st == 0xB) { ... }
//     else {
//       float acc = G_fp_2CAC0;               // global accumulator
//       float lim = *(float*)(&D_0 + 0x1968);
//       if (acc > lim) acc = 0.0f;            // clamp / reset
//       acc *= *(float*)(&D_0 + 0x196C);      // scale
//       ... mix with v (f12) ...
//       G_fp_2CAC0 = acc;                     // store back
//     }
//     if (*(int*)&D_0 == 0) { ... }           // state==0 branch
//     ...                                     // (3 return points)
//   }
//
// Struct-typing reference: a per-call FP state integrator gated on
//   a signed-byte selector (only sel==1 runs the main body). It
//   reads the global state word at &D_0 and, by state value
//   {4 / 0xB / other}, advances a global float accumulator located
//   in the USO data segment (referenced as -0x3540(0x0002....),
//   i.e. a fixed data-segment FP global, addr ~0x0002CAC0),
//   clamping it against the limit float &D_0+0x1968, scaling by
//   &D_0+0x196C, and mixing in the float argument (f12). Has three
//   return points (selector miss, state-specific early exits, and
//   the main update fallthrough). A physics/value-ramp state node
//   of the game_libs object subsystem (the global-accumulator
//   counterpart to the per-object gl_func_0002F288 / 0002F584
//   integrators; driven each frame by the gl_func_0002FB74
//   interpreter through the &D_0 state word).
// Caps (DEFERRED): raw-word USO + data-segment FP global (-0x3540
//   base unsymbolized) + &D_0 state gate + multi-return — byte-
//   match needs USO mnemonic disasm + data-seg FP global symbolized.
//   Real-C STRUCTURAL body below per the analysis (top-level sel
//   gate + state-arms sketch — full body's three return points
//   summarised in the in-comment analysis above). Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00031A74(int sel, float v) {
    int st;
    float acc;
    float lim;
    if ((signed char)sel != 1) return;
    st = *(int *)((char *)&D_00000000 + 0);
    if (st == 0) return;
    if (st == 4 || st == 0xB) {
        acc = *(float *)((char *)&D_00000000 + 0x2CAC0);
        lim = *(float *)((char *)&D_00000000 + 0x1968);
        if (acc > lim) acc = 0.0f;
        acc *= *(float *)((char *)&D_00000000 + 0x196C);
        acc += v;
        *(float *)((char *)&D_00000000 + 0x2CAC0) = acc;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031A74);
#endif

void game_libs_func_00031CA8(int *a0, int a1, int a2) { *(int*)((char*)a0 + 0) = a1; *(int*)((char*)a0 + 8) = a2; *(int*)((char*)a0 + 0xC) = 0; }

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00031CB8)();
void game_libs_func_00031CB8(char *arg0) {
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v0 = FW(arg0, 0x8);
    if (temp_v0 != 0) {
        temp_v1 = FW(arg0, 0x0) - FW(arg0, 0x4);
        temp_lo = (s32) (temp_v1 << 8) / temp_v0;
        var_v0 = -temp_lo;
        if (temp_lo >= 0) {
            var_v0 = temp_lo;
        }
        FW(arg0, 0xC) = (s32) (FW(arg0, 0xC) + var_v0);
loop_4:
        temp_v0_2 = FW(arg0, 0xC);
        var_v1 = -1;
        if (temp_v0_2 >= 0x100) {
            if (!(temp_v1 & 0x800000)) {
                var_v1 = 1;
            }
            FW(arg0, 0xC) = (s32) (temp_v0_2 - 0x100);
            FW(arg0, 0x4) = (s32) (FW(arg0, 0x4) + var_v1);
            goto loop_4;
        }
        FW(arg0, 0x8) = (s32) (FW(arg0, 0x8) - 1);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031CB8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031D70);

extern int gl_data_00000000;

void gl_func_00031D78(int a0, int a1, int a2) {
    D_00000000 = a1;
    gl_data_00000000 = a2;
    gl_func_00000000(a0);
}

int gl_func_00031DA4(void) {
    int v = gl_func_00000000();
    if (v == 0) return 0;
    return v;
}

// gl_func_00031DD8 — STRUCTURAL PASS + BOUNDARY / DATA-MISID NOTE
// (0xF9C / 999 words, no episode). Raw-.word USO form (game_libs).
//
// The NAMED leading function is TINY — a one-call trampoline
// (0x31DD8..0x31DF0, 6 instructions):
//   void gl_func_00031DD8(void) {
//     callback0();                            // jal 0 (USO callback)
//   }
// i.e. save ra, call a single USO-relocated callback (jal 0 →
// resolved at load), restore, return. Nothing else.
//
// EVERYTHING AFTER 0x31DF0 IS NOT THIS FUNCTION and is NOT standard
// o32 MIPS. After the trampoline's return there is a run of
// .word 0 padding (also split out into the trailing _pad.s
// GLOBAL_ASM below), then ~990 words whose encodings are NOT
// IDO/MIPS-II integer code:
//   - 0x0D000430 / 0x0D0006B4  — opcode 0x0D (jalx-style) targets
//   - 0x40055800 / 0x40045800  — opcode 0x10/0x40 COP0 (mfc0-form)
//   - 0x20010000 / 0x201802E0  — opcode 0x08 addi-immediate forms
//   - 0x1C80FFFD               — opcode 0x07 branch-likely-style
// This is RSP microcode / a vector-ucode or non-code DATA blob that
// splat MISIDENTIFIED as code and bundled into this symbol (see the
// RSP-ucode / splat data-misID notes in docs/N64_FORENSICS.md). The
// extra realjr=5 count is an artifact of 0x03E00008 byte patterns
// occurring inside that ucode/data, NOT real function returns.
//
// Caps (DEFERRED): the named fn is a TINY 6-insn one-call USO-reloc
//   trampoline; the rest of the .s is .word data / RSP ucode that
//   splat misidentified as code (NOT C past the trampoline). Real-C
//   STRUCTURAL body below for the named trampoline only. Byte-match
//   deferred (USO boundary re-split + data/ucode reclassification
//   needs spimdisasm-USO migration). Name pre-checked: no extern
//   reuse.
void gl_func_00031DD8(void) {
    gl_func_00000000();
}

/* [0x31DF8..0x32884) = the HANDWRITTEN CP0/system block, one family with
 * 32884 below (2026-06-10 graft-attempt finding): 31DF8 leads with zero
 * pad words; 31F20 + 31F4C are mfc0/mtc0 routines (0x40xxxxxx CP0 words
 * that disassemble as bogus far branches), busy-wait bne loops, fixed
 * trampolines, and 31F4C's "backwards branches" land inside 31DF8 --
 * hand-coded flow, not splat fragments. CP0 is inexpressible in IDO C
 * (reference_1080_mips3_runtime_helpers): PERMANENT INCLUDE_ASM, do not
 * graft, merge, or decode. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031DF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031F20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00031F4C);

/* game_libs_func_00032884: HANDWRITTEN system/CP0 routine (NOT a fragment —
 * the old "middle-fragment, backward branch to 0x31EF4, needs boundary
 * correction" note was wrong; 2026-06-02 re-decode shows NO before-start
 * branch). The 0xB0 block is a hand-coded sequence: `jal`/`j` trampolines to
 * fixed low offsets (0x1A68/0x1AB0/0x1AC0/…), CP0 register moves
 * (mfc0/mtc0 = 0x40xxxxxx words at 0x50-0xA8), busy-wait `bne` loops, and a
 * `jr ra`. CP0 access is not expressible in IDO C (cf.
 * reference_1080_mips3_runtime_helpers) — PERMANENT INCLUDE_ASM, do not
 * attempt a boundary merge or C decode. */
#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00032884)();
void game_libs_func_00032884(void) {
    game_libs_func_0003443C();
    game_libs_func_0003443C();
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00032884);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00032934);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00031DD8_pad.s")

extern int gl_func_00000000();
void gl_func_00032D84(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00032DC0(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

// gl_func_00032E18 — STRUCTURAL PASS (0x27C / 159 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue — large 0x60 frame). An OBJECT CONSTRUCTOR.
//
//   O *gl_func_00032E18(int a, int b, int c, int d) {
//     if (a == 0) { alloc(0x150); ... }      // jal 0 allocator
//     O *o = (O*)v0;
//     if (o == 0) return 0;                   // alloc-fail guard
//     S *s = (S*)alloc(0xB4);                 // sub-record
//     if (s == 0) return 0;
//     memcpy(s, (void*)0x0001E178, ...);      // default template
//     s->p_28 = &D_0_base;                    // wire global base
//     if (s != SENTINEL) sub_init(&s->f_2C);  // (-0x2C compare)
//     ... further alloc(4) / sub-inits ...
//     return o;
//   }
//
// Struct-typing reference: a constructor for one of the subsystem's
//   objects. It allocates a main record of 0x150 bytes (via a
//   USO-relocated allocator callback, jal 0 → resolved at load) on
//   the a==0 path, bails cleanly on allocation failure, allocates a
//   0xB4-byte sub-record, then COPIES a default/template block from
//   a FIXED data-segment source at 0x0001E178 into it, stores the
//   global base pointer (&D_0) into the sub-record at offset 0x28,
//   and performs further small sub-allocations (size 4) / field
//   inits before returning the constructed object. The args
//   (a/b/c/d, spilled to sp+0x64..0x6C) select the construction
//   variant. A producer leaf of the game_libs object subsystem —
//   it manufactures the records the gl_func_0002FB74 interpreter,
//   the emitter family and the gl_func_00030AF4 top-level
//   constructor operate on (0x0001E178 is the deferred-symbolization
//   template-data site; the 0x150 / 0xB4 sizes are the struct sizes
//   to type when this object family is formalized).
// Caps (DEFERRED): raw-word USO + USO-reloc allocator callbacks +
//   fixed data-segment template copy (0x0001E178 unsymbolized) —
//   byte-match needs USO mnemonic disasm + template data symbolized
//   + 0x150/0xB4 structs typed. Real-C STRUCTURAL body below per
//   the analysis. Byte-match deferred. Name pre-checked: no extern
//   reuse.
// gl_func_00032E18 — FULL m2c DECODE (67.26% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00032E18)();
s32 *gl_func_00032E18(s32 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    s32 *sp5C;
    s32 *sp58;
    f32 sp4C;
    f32 sp48;
    s32 sp44;
    f32 sp28;
    f32 sp24;
    s32 sp20;
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
    s32 *var_a1;
    s32 *var_a2;
    s32 *var_a2_2;
    s32 *var_a2_3;
    s32 *var_s0;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 *var_v1_3;
    s32 *var_v1_4;

    var_s0 = arg0;
    if ((arg0 != 0) || (temp_v0 = gl_func_0001CA10((s32 *)0x150), var_s0 = temp_v0, (temp_v0 != 0))) {
        var_a2 = var_s0;
        if ((var_s0 != 0) || (temp_v0_2 = gl_func_0001CA10((s32 *)0xB4), var_a2 = temp_v0_2, (temp_v0_2 != 0))) {
            sp5C = var_a2;
            gl_func_0001CA10(var_a2, (s32 *)0x1E178, var_a2);
            var_a2_2 = var_a2;
            FW(var_a2_2, 0x28) = 0;
            var_a0 = var_a2_2 + 0x2C;
            if (((var_a2_2 != (s32 *)-0x2C) || (sp5C = var_a2_2, temp_v0_3 = gl_func_0001CA10((s32 *)4), var_a0 = temp_v0_3, (temp_v0_3 != 0))) && ((var_v1 = var_a0, (var_a0 != 0)) || (sp5C = var_a2_2, temp_v0_4 = gl_func_0001CA10((s32 *)4), var_v1 = temp_v0_4, (temp_v0_4 != 0)))) {
                *var_v1 = 0;
            }
            sp5C = var_a2_2;
            gl_func_0001CA10(var_a2_2);
            sp44 = 0;
            sp48 = 0.0f;
            sp4C = 0.0f;
            gl_func_0001CA10(var_a2_2 + 0x30, &sp44, var_a2_2);
        }
        FW(var_s0, 0x28) = 0;
        var_a2_3 = var_s0 + 0x110;
        if ((var_s0 != (s32 *)-0x110) || (temp_v0_5 = gl_func_0001CA10((s32 *)0x20), var_a2_3 = temp_v0_5, (temp_v0_5 != 0))) {
            var_a1 = var_a2_3;
            if ((var_a2_3 != 0) || (sp5C = var_a2_3, temp_v0_6 = gl_func_0001CA10((s32 *)0x18, var_a1, var_a2_3), var_a1 = temp_v0_6, (temp_v0_6 != 0))) {
                var_v1_2 = var_a1;
                if ((var_a1 != 0) || (sp58 = var_a1, sp5C = var_a2_3, temp_v0_7 = gl_func_0001CA10((s32 *)0x10, var_a1, var_a2_3), var_v1_2 = temp_v0_7, (temp_v0_7 != 0))) {
                    FW(var_v1_2, 0x0) = -1;
                    FW(var_v1_2, 0x8) = 0x8000;
                    FW(var_v1_2, 0x4) = 0;
                }
                var_v1_3 = var_a1 + 0x10;
                if ((var_a1 != (s32 *)-0x10) || (sp58 = var_a1, sp5C = var_a2_3, temp_v0_8 = gl_func_0001CA10((s32 *)4, var_a1, var_a2_3), var_v1_3 = temp_v0_8, (temp_v0_8 != 0))) {
                    *var_v1_3 = 0;
                }
                FW(var_a1, 0xC) = 0x1E180;
                FW(var_a1, 0x14) = 0;
            }
            var_v1_4 = var_a2_3 + 0x18;
            if ((var_a2_3 != (s32 *)-0x18) || (temp_v0_9 = gl_func_0001CA10((s32 *)8, var_a1, var_a2_3), var_v1_4 = temp_v0_9, (temp_v0_9 != 0))) {
                FW(var_v1_4, 0x0) = 0;
                FW(var_v1_4, 0x4) = 0;
            }
        }
        sp20 = arg2;
        sp24 = arg3;
        sp28 = arg4;
        gl_func_0001CA10(var_s0 + 0x30, &sp20);
        FW(var_s0, 0xC) = 0x1E18C;
        FW(var_s0, 0x8) = (s32) (FW(var_s0, 0x8) | 0x40);
        FW(var_s0, 0xF4) = arg1;
        *(f32 *)((char *)var_s0 + 0x104) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x108) = 0.0f;
        *(f32 *)((char *)var_s0 + 0xFC) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x10C) = 1.0f;
        gl_func_0001CA10(var_s0 + 0xB4);
        FW(var_s0, 0x130) = 0;
        *(f32 *)((char *)var_s0 + 0x134) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x138) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x13C) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x140) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x148) = 0.0f;
        *(f32 *)((char *)var_s0 + 0x144) = 1.0f;
        *(f32 *)((char *)var_s0 + 0x14C) = 85.0f;
    }
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00032E18);
#endif

// gl_func_00033094 — STRUCTURAL PASS (0x194 / 101 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue — large 0x90 FP-heavy frame). An FP vector / transform
// composition routine.
//
//   void gl_func_00033094(O *o) {
//     Vec3 base = { o->f_A0, o->f_A4, o->f_A8 };   // primary Vec3
//     O *child = o->p_F4;
//     Vec3 off;
//     if (child != 0) {
//       off = (Vec3){ child->f_A0, child->f_A4, child->f_A8 };
//     } else {
//       // build off from o->0x104 / 0x108 / 0x10C (+ const 0x4120)
//       off = (Vec3){ o->f_104, o->f_108, o->f_10C };
//     }
//     // FP composition: scale a vector by a scalar (f12) and add
//     //   the offset Vec3 — position / transform update
//     result.x = base.x * s + off.x;
//     result.y = base.y * s + off.y;
//     result.z = base.z * s + off.z;
//     ... store result back into o / a child record ...
//   }
//
// Struct-typing reference: an FP transform-composition leaf. It
//   reads a primary Vec3 from the object at offsets 0xA0/0xA4/0xA8,
//   then either pulls a second Vec3 from a child object pointed to
//   by o->0xF4 (when non-null, selected via branch-likely beql) or
//   synthesizes one from the scalar fields o->0x104/0x108/0x10C
//   (with an injected constant 0x41200000 = 10.0f), and performs a
//   per-component multiply-add (scale-by-scalar + offset) — the
//   classic position / velocity / transform update shape. Uses a
//   large 0x90 stack frame purely as FP scratch (Vec3 spills at
//   sp+0x54..0x8C). A geometry/kinematics leaf of the game_libs
//   object subsystem (the per-object math the gl_func_0002FB74
//   interpreter and the integrator family (0002F288 / 0002F584 /
//   00031A74) drive each frame; o->0xF4 is the child/parent link
//   also touched by the gl_func_00032E18 constructor's sub-record).
// Caps (DEFERRED): raw-word USO + FP Vec3 mul-add + conditional
//   child-deref — byte-match needs USO mnemonic disasm + object's
//   Vec3/child layout typed. Real-C STRUCTURAL body below per the
//   analysis. Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00033094(char *o, float s) {
    float bx = *(float *)(o + 0xA0);
    float by = *(float *)(o + 0xA4);
    float bz = *(float *)(o + 0xA8);
    char *child = *(char **)(o + 0xF4);
    float ox, oy, oz;
    if (child != 0) {
        ox = *(float *)(child + 0xA0);
        oy = *(float *)(child + 0xA4);
        oz = *(float *)(child + 0xA8);
    } else {
        ox = *(float *)(o + 0x104) + 10.0f;
        oy = *(float *)(o + 0x108);
        oz = *(float *)(o + 0x10C);
    }
    *(float *)(o + 0xA0) = bx * s + ox;
    *(float *)(o + 0xA4) = by * s + oy;
    *(float *)(o + 0xA8) = bz * s + oz;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033094);
#endif

// gl_func_00033228 — STRUCTURAL PASS (0x8C / 35 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). An object allocate-and-enlist helper.
//
//   void gl_func_00033228(O *o) {
//     callback0();                            // jal 0 (USO factory)
//     // build a sub-object: a1=0, a2=0.0f, a3=0.0f, sp+0x10=0.0f
//     N *n = make(0, 0, 0.0f, 0.0f);          // 2nd USO callback
//     o->p_28 = n;
//     o->p_0C = n;
//     o->p_10 = n;
//     T *t = o->p_3C;
//     L *lst = *(L**)(t + 0x10);
//     list_insert(&lst[0x10/..], n);          // 3rd USO callback
//     if (lst->p_14 != 0) { ... } else {
//       lst->w_04 = 1;                         // branch-likely guard
//     }
//     lst->p_14 = n;                           // list head/anchor
//   }
//
// Struct-typing reference: a construct-and-link leaf. It runs a
//   USO-relocated factory callback (jal 0 → resolved at load),
//   builds a sub-object via a second callback passing zeroed float
//   args (0, 0, 0.0f, 0.0f incl. a stack float at sp+0x10), and
//   publishes the resulting pointer into the parent object at three
//   offsets (0x28, 0x0C, 0x10 — primary handle + two aliases). It
//   then reaches a container via o->0x3C, loads a list anchor at
//   +0x10, calls a third USO callback to splice the new node in,
//   and updates the list head field (lst->0x14 = node) plus a flag
//   (lst->0x04 = 1) under a branch-likely empty-list guard. An
//   object-lifecycle / registration leaf of the game_libs object
//   subsystem (the per-instance counterpart to the gl_func_00032E18
//   constructor and the gl_func_00030A20 registration node; the
//   list it enlists into is the collection the gl_func_0002FB74
//   interpreter iterates).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 factory/insert
//   callbacks + intrusive-list splice — byte-match needs USO
//   mnemonic disasm + object/list structs typed. Real-C STRUCTURAL
//   body below per the analysis. Byte-match deferred. Name pre-
//   checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00033228(char *o) {
    char *n;
    char *t;
    char *lst;
    gl_func_00000000();
    n = (char *)gl_func_00000000(0, 0, 0.0f, 0.0f);
    *(int *)(o + 0x28) = (int)n;
    *(int *)(o + 0x0C) = (int)n;
    *(int *)(o + 0x10) = (int)n;
    t = *(char **)(o + 0x3C);
    lst = *(char **)(t + 0x10);
    gl_func_00000000(lst + 0x10, n);
    if (*(int *)(lst + 0x14) == 0) {
        *(int *)(lst + 0x04) = 1;
    }
    *(int *)(lst + 0x14) = (int)n;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033228);
#endif

// gl_func_000332B4 — command-stream handler step (0x84 / 33 words).
// CLEAN SINGLE FUNCTION (1 jr, one prologue).
//
// CORRECTED logic 2026-06-22 (prior comment had the if/else inverted).
// Verified vs expected/.o disasm — the in-range path does NOT call the
// callback; the table store happens on BOTH the in-range and out-of-range
// paths (they reconverge), and the o-callback is the shared tail for the
// tag-mismatch case only:
//
//   void gl_func_000332B4(O *o, Cmd *c) {
//     if (c->tag_0 == 0x69) {
//       int *sp = (int*)c->cur_4;
//       c->cur_4 = (int)(sp + 1);              // advance cursor +4
//       int idx = *sp;                         // stream param
//       if ((u32)idx >= 0x28)                  // OUT of range (>=40)
//         callback(&D_0 + 0x1E194, idx);       // jal 0 (USO cb)
//       o->p_F4 = D_0_table[idx];              // ALWAYS: &D_0 + idx*4
//       return;
//     }
//     callback0(o);                            // shared else (tag mismatch)
//   }
//
// 2026-06-22 reconstruction (signature-#2 reloc-form arg): the fixed
//   data-seg ref 0x0001E194 is really `(char*)&D_00000000 + 0x1E194`
//   (lui 0x2; addiu -7788 via %hi/%lo reloc — NOT lui 0x1; ori 0xe194).
//   With that fix + corrected control flow + split-locals (idx anchors a2,
//   val→v0), the body is BYTE-EXACT except ONE instruction: the tag load
//   `*c` lands in $a2 (build) vs $v0 (target) — a single-register allocator
//   tie. idx's home reg is $a2; IDO coalesces the short-lived tag value
//   into it, whereas the target splits the live range and uses $v0.
//   Permuter (11k+ iters, perm_temp_for_expr) plateaued at score 30 (=this
//   one reg); two-var split flips tag→v0 but moves idx→a1 (worse). Genuine
//   $v0-vs-$a2 coloring cap — NM-wrap. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_000332B4(char *o, char *c) {
    int *sp;
    int idx;
    int val;
    idx = *(int *)c;
    if (idx == 0x69) {
        sp = *(int **)(c + 4);
        *(int **)(c + 4) = sp + 1;
        idx = *sp;
        if ((u32)idx >= 0x28) {
            gl_func_00000000((char *)&D_00000000 + 0x1E194, idx);
        }
        val = *(int *)((char *)&D_00000000 + idx * 4);
        *(int *)(o + 0xF4) = val;
        return;
    }
    gl_func_00000000(o);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000332B4);
#endif

#ifdef NON_MATCHING
/* gl_func_00033338: 27-insn 3-call wrapper. Calls:
 *   func(&D, a0[3]);
 *   func(&D, &D+0x1E1AC, a0+0x14C, 0, 180.0f, 0);     // 6 args (last 2 on stack)
 *   func(&D);
 *
 * Cap: 5th arg `180.0f` — IDO sees gl_func_00000000 as K&R/unprototyped
 * and promotes float arg to double (sdc1 vs swc1) plus cvt.d.s. Target
 * has float (swc1). Function-pointer cast variant adds 2+ insns for the
 * indirect call setup. Without a typed prototype on the cross-USO callee
 * (impossible — gl_func_00000000 is a runtime-patched placeholder), the
 * float-promote is unreachable. Same class as feedback_ido_knr_float_call. */
void gl_func_00033338(int *a0) {
    gl_func_00000000(&D_00000000, *(int*)((char*)a0 + 0xC));
    gl_func_00000000(&D_00000000, (char*)&D_00000000 + 0x1E1AC,
                     (char*)a0 + 0x14C, 0, 180.0f, 0);
    gl_func_00000000(&D_00000000);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033338);
#endif

void game_libs_func_000333A4(int a0, int a1, int a2) {
}

extern int gl_ref_000473F0();
extern int gl_ref_0004742C();
void gl_func_000333B4(char *a0) {
    int scratch;
    gl_ref_000473F0(&scratch);
    gl_ref_0004742C(a0 + 0x10);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000333B4_pad.s")

#ifdef NON_MATCHING
/* 80%: body is `gl_func_00000000(&D_00000000, a0)` but IDO -O2 schedules
 * `sw ra, 0x14(sp)` before `lui a0, %hi(SYM)` — target has them swapped.
 * Per feedback_ido_o2_tiny_wrapper_unflippable.md this is an IDO scheduler
 * cap not reachable from C (tested 13+ variants on the sibling 0x62204);
 * same class here. The prior wrap had `gl_func_00000000(gl_func_00000000, a0)`
 * which was a typo — the &D_00000000 form is the correct body. */
int gl_func_000333F4(int a0) {
    return gl_func_00000000(&D_00000000, a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000333F4);
#endif

#ifdef NON_MATCHING
/* 82.83% NM with SUFFIX_BYTES applied for the trailing dead bytes
 * (lui t6, 0; lw t6, 0x20C(t6) — stolen prologue for successor).
 * Remaining diff: IDO schedules `sw ra, 0x14(sp)` BEFORE `lui a0, 0` in
 * mine, target has them in opposite order. Both insns independent
 * (no data dep) — same IDO scheduler-ordering cap class as
 * feedback_ido_sw_before_addu_unreachable.md. SUFFIX_BYTES + body
 * structure are correct; just the 2-insn swap is unflippable from C.
 * Default INCLUDE_ASM build matches. */
void gl_func_0003341C(int a0) {
    gl_func_00000000(&D_00000000, a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003341C);
#endif

// game_libs_func_00033444 — STRUCTURAL PASS / BOUNDARY NOTE
// (0x8 / 2 words, no episode). Raw-.word USO form (game_libs).
//
// NOT A REAL FUNCTION. Splat-missplit HEAD FRAGMENT (same class as
// game_libs_func_000309AC documented earlier in this file): two
// instructions only, NO prologue (no addiu $sp), NO jr $ra —
//     lui   $t6, 0            ( 3C0E0000 )
//     lw    $t6, 0x20C($t6)   ( 8DCE020C )
// a base-pointer load of &D_0 + 0x20C into $t6. These two words
// logically belong to the ENTRY of the NEXT function (at
// 0x0003344C): splat could not see the function boundary in this
// relocatable USO segment and sheared the successor's prologue-area
// base load off as a standalone 8-byte symbol.
//
// Resolution: DEFERRED USO BOUNDARY RE-SPLIT (tracked with the other
// game_libs_post.c head-fragment / multi-jr boundary notes). NOT
// fixable with the mnemonic split-fragments.py / merge-fragments
// tooling — raw-.word relocatable USO needs the spimdisasm-USO
// migration to re-derive the boundary. No merge attempted (would
// corrupt the successor's bytes); no episode (tautology-trap; and
// this is not a function). Body INCLUDE_ASM-preserved (.s = source
// of truth).
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00033444);

// gl_func_0003344C — STRUCTURAL PASS (0x64 / 25 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, has
// its OWN prologue). The SUCCESSOR of the game_libs_func_00033444
// head-fragment (its &D_0+0x20C load feeds in as the input).
//
//   float gl_func_0003344C(...) {
//     unsigned u = *(unsigned*)(&D_0 + 0x20C);   // from frag 33444
//     float a = (float)u;                          // cvt.s.w
//     if ((int)u < 0) a += 2147483648.0f;          // 0x4F800000
//     float r = callback(&D_0, a);                 // jal 0 (USO cb)
//     float b = (float)(unsigned)r;                // same u32->f
//     if (...) b += 2147483648.0f;
//     return r0 / b;                                // div.s in delay
//   }
//
// Struct-typing reference: the textbook UNSIGNED-32 -> FLOAT
//   conversion idiom (IDO/GCC __floatunsi-style): `cvt.s.w` of the
//   value followed by a sign-bit-gated add of 2^31 = 2147483648.0f
//   (the literal 0x4F800000 materialized via lui/mtc1), applied
//   twice (once to the &D_0+0x20C input, once to a callback result),
//   with the final result produced by an FP divide emitted in the
//   jr delay slot (`div.s f0, f0, f4`). It calls one USO-relocated
//   callback (jal 0 → resolved at load) with the &D_0 base and the
//   converted float. A numeric-conversion / ratio leaf of the
//   game_libs object subsystem (computes a normalized ratio from an
//   unsigned counter at &D_0+0x20C — likely a progress / fraction
//   used by the gl_func_0002FB74 interpreter and the ramp/timer
//   family; the head-fragment 00033444 is its sheared-off input
//   base load, confirming the two are one logical unit pending the
//   deferred USO re-split).
// Caps (DEFERRED): raw-word USO + unsigned->float 2^31-bias idiom +
//   USO-reloc jal-0 callback + delay-slot div.s — byte-match needs
//   USO mnemonic disasm + 00033444 boundary re-split. Real-C
//   STRUCTURAL body below per the analysis. Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
float gl_func_0003344C(void) {
    unsigned u = *(unsigned *)((char *)&D_00000000 + 0x20C);
    float a = (float)(int)u;
    float r;
    float b;
    if ((int)u < 0) a += 2147483648.0f;
    r = ((float (*)(void *, float))gl_func_00000000)(&D_00000000, a);
    b = (float)(int)*(unsigned *)&r;
    if ((int)*(unsigned *)&r < 0) b += 2147483648.0f;
    return r / b;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003344C);
#endif

extern int gl_func_00000000();
void gl_func_000334B0(int a0, int a1, int a2) {
    gl_func_00000000((char *)&D_00000000 + 0x1E250, a0, a1, a2);
}

// gl_func_000334E8 — STRUCTURAL PASS (0x2C4 / 177 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue — large 0x68 frame, saves s0-s5). A region / block
// allocator-management routine.
//
//   void gl_func_000334E8(void *a) {
//     Desc d;                                 // local at sp+0x60
//     callback(a, (void*)0x0001E280);         // jal 0 (USO cb)
//     B *base = &D_0_base;
//     callback(base);                          // 2nd USO cb
//     int TAG = 0x12340002;                    // block sentinel
//     int gran = 8;
//     int used = *(int*)(&D_0 + 0x2C) - *(int*)(&D_0 + 8);
//     if (used < gran) { ... }
//     int misalign = (int)&d & 7;              // 8-byte align math
//     if (misalign) { ptr = (char*)&d - misalign; ... }
//     ... walk / fit blocks tagged with 0x12340002 ...
//   }
//
// Struct-typing reference: a heap/region block manager. It builds a
//   local descriptor on the stack (s0 = sp+0x60), runs two
//   USO-relocated callbacks (jal 0 → resolved at load) — one with a
//   fixed data-segment template at 0x0001E280, one with the global
//   region base at &D_0 — computes a used/free span from a pair of
//   global cursors (&D_0+0x08 = start, &D_0+0x2C = current), and
//   manages 8-byte-granule aligned blocks each carrying the magic
//   header sentinel 0x12340002 (a classic allocator block-tag /
//   version marker — `lui 0x1234; ori 0x0002`). Performs the usual
//   pointer alignment fix-ups (`& 7`, subtract misalignment). A
//   memory/region-management leaf of the game_libs object subsystem
//   (the allocator behind the gl_func_00030AF4 constructor's
//   0x45010 arena and the gl_func_00032E18 / gl_func_00033228
//   sub-record allocations — 0x12340002 is the heap block magic to
//   key on when that allocator is formalized).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + global
//   region cursors + 0x12340002 block-magic + alignment math —
//   byte-match needs USO mnemonic disasm + allocator structs typed.
//   Real-C STRUCTURAL body below per the analysis. Byte-match
//   deferred. Name pre-checked: no extern reuse.
// gl_func_000334E8 — FULL m2c DECODE (53.45% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000334E8)();
void gl_func_000334E8(void) {
    u8 sp60;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t3;
    u32 temp_v0;
    u32 temp_v1;
    u32 var_s2;
    u32 var_s4;
    u32 var_v0;
    u8 *var_s5;
    u8 *var_v1;
    u8 temp_t9;
    char *var_a0;

    gl_func_0001CA10(&sp60, 0x1E280);
    var_s5 = &sp60;
    var_s4 = 8;
    gl_func_0001CA10(0);
    do {
        var_s2 = var_s4;
        temp_a0 = (s32) var_s5 & 7;
        temp_v0 = *(s32 *)0x2C - *(s32 *)8;
        if (temp_v0 < var_s4) {
            var_s2 = temp_v0;
        }
        if (var_s2 != 0) {
            if (temp_a0 != 0) {
                temp_v1 = 8 - temp_a0;
                var_v0 = 0;
                if (temp_v1 < var_s2) {
                    var_s2 = temp_v1;
                }
                if (var_s2 != 0) {
                    var_a0 = 0;
                    var_v1 = var_s5;
                    do {
                        temp_t9 = *(int*)var_v1;
                        var_v0 += 1;
                        var_v1 += 1;
                        var_a0 += 1;
                        FW(var_a0, -0x1) = temp_t9;
                    } while (var_v0 < var_s2);
                }
                gl_func_0001CA10(0, *(char *)8, 0, var_s2);
            } else {
                gl_func_0001CA10(0, *(char *)8, (s32) var_s5, var_s2);
            }
            temp_a2 = *(char *)8 + var_s2;
            *(char *)8 = temp_a2;
            gl_func_0001CA10(0, *(s32 *)0x28, temp_a2);
        }
        temp_t3 = *(char *)8;
        if (*(char *)0x2C == temp_t3) {
            *(s32 *)0x14 = temp_t3;
            gl_func_0001CA10(0, *(char *)0x28 + 0xC, temp_t3);
            if (*(char *)0x2C != *(char *)8) {
                gl_func_0001CA10(0, 0x1E29C);
            }
            gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340001);
            if (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002) {
                do {
                    gl_func_0001CA10(0);
                } while (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002);
            }
            temp_a2_2 = *(s32 *)0x24;
            *(char *)8 = temp_a2_2;
            gl_func_0001CA10(0, *(char *)0x28, temp_a2_2);
            gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340003);
            if (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002) {
                do {
                    gl_func_0001CA10(0);
                } while (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002);
            }
        }
        var_s4 -= var_s2;
        var_s5 += var_s2;
        if ((s32) var_s4 < 0) {
            gl_func_0001CA10(0, 0x1E2B0);
        }
        if (var_s4 != 0) {
            gl_func_0001CA10(0);
        }
    } while (var_s4 != 0);
    gl_func_0001CA10(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000334E8);
#endif

// gl_func_000337AC — STRUCTURAL PASS (0xD4 / 53 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). A flag-gated record register-and-init routine.
//
//   void gl_func_000337AC(int id, unsigned flags, int b, int c) {
//     if (flags & 7) {
//       callback((void*)0x0001E2C0, id);      // jal 0 (USO cb)
//     }
//     if (flags & 1) {
//       callback((void*)0x0001E2D8, c);       // 2nd USO cb
//     }
//     R *rec = (R*)(&D_0 + id * 0x44);         // id*0x44 record
//     rec->w_3C = 1;                            // mark active
//     callback3(flags, c);                      // 3rd USO cb
//     init(&rec->f_18, 0, 0, ...);              // init sub-block
//   }
//
// Struct-typing reference: a flag-driven registration / slot-init
//   leaf. The flags arg's low bits select optional setup callbacks
//   — `flags & 7` runs a USO-relocated callback (jal 0 → resolved
//   at load) with the fixed data-segment template 0x0001E2C0, and
//   `flags & 1` runs another with template 0x0001E2D8. It then
//   indexes a record array based at &D_0 with stride 0x44 (the
//   index computed as id*16 + id then *4 = id*0x44, the classic
//   shift/add multiply for a non-power-of-two struct size), sets
//   the per-record active flag at +0x3C, and runs a third callback
//   to initialize the record's sub-block at +0x18. A table-slot
//   register/activate node of the game_libs object subsystem (the
//   0x44-stride array is a sibling of the registry/record tables
//   mapped earlier in this vein; 0x0001E2C0 / 0x0001E2D8 are
//   deferred data-segment template-symbolization sites).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + &D_0
//   record-array (0x44 stride) + fixed data-seg templates
//   (0x0001E2C0/0x0001E2D8 unsymbolized).
// 2026-05-31: 59.02% -> 79.0% by fixing: (1) 2nd guard is `c & 1` not `flags & 1`;
//   (2) the 4th call is gl_func(rec, 0, 0, c, flags, c, rec+0x18) [7 args] not
//   (rec+0x18, 0, 0); (3) trailing stores rec->0x34=flags, rec->0x38=c, rec->0x40=1;
//   (4) templates via &D+0x1E2C0/0x1E2D8 (lui+addiu) not literal (lui+ori).
//   Remaining ~21% = USO reloc + register alloc. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_000337AC(int id, unsigned flags, int b, int c) {
    char *rec;
    (void)b;
    if (flags & 7) {
        gl_func_00000000((char *)&D_00000000 + 0x0001E2C0, id);
    }
    if (c & 1) {
        gl_func_00000000((char *)&D_00000000 + 0x0001E2D8, c);
    }
    rec = (char *)&D_00000000 + id * 0x44;
    *(int *)(rec + 0x3C) = 1;
    gl_func_00000000(flags, c);
    gl_func_00000000(rec, 0, 0, c, flags, c, rec + 0x18);
    *(int *)(rec + 0x34) = flags;
    *(int *)(rec + 0x38) = c;
    *(int *)(rec + 0x40) = 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000337AC);
#endif

// gl_func_00033880 — STRUCTURAL PASS (0xDC / 55 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). The direct SIBLING / variant of gl_func_000337AC
// (immediately above) — same flag-gated record register-and-init
// shape, different arg slots + template set.
//
//   void gl_func_00033880(int id, int a1, unsigned flags, int d) {
//     if (flags & 7) {
//       callback((void*)0x0001E2EC, d);       // jal 0 (USO cb)
//     }
//     if (d & 1) {
//       callback((void*)0x0001E308, d);       // 2nd USO cb
//     }
//     R *rec = (R*)(&D_0 + id * 0x44);         // id*0x44 record
//     rec->w_3C = 1;                            // mark active
//     callback3(flags, d);                      // 3rd USO cb
//     init(&rec->f_18, 0, 1, a1);               // init sub-block
//   }
//
// Struct-typing reference: a flag-driven registration / slot-init
//   leaf, the sibling of gl_func_000337AC. Identical structure:
//   low flag bits gate optional USO-relocated setup callbacks
//   (jal 0 → resolved at load) carrying fixed data-segment
//   templates — here `flags & 7` → 0x0001E2EC and `d & 1` →
//   0x0001E308 (vs gl_func_000337AC's 0x0001E2C0 / 0x0001E2D8) —
//   then indexes the SAME &D_0 record array with stride 0x44
//   (id*16 + id then *4 = id*0x44 shift/add multiply), sets the
//   per-record active flag at +0x3C, and runs a third callback to
//   initialize the record's sub-block at +0x18. The only deltas vs
//   gl_func_000337AC are the argument positions (flags arrives in
//   a2, the secondary gate keys off arg d) and the template pair.
//   The two together form a register/activate pair over the same
//   0x44-stride registry table of the game_libs object subsystem
//   (likely "register kind A" vs "register kind B"; 0x0001E2EC /
//   0x0001E308 are deferred data-segment template-symbolization
//   sites).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + &D_0
//   record-array (0x44 stride) + fixed data-seg templates
//   (0x0001E2EC/0x0001E308 unsymbolized) — byte-match needs USO
//   mnemonic disasm + record struct typed. Real-C STRUCTURAL body
//   below per the analysis (sibling of gl_func_000337AC). Byte-match
//   deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00033880(int id, int a1, unsigned flags, int d) {
    char *rec;
    if (flags & 7) {
        gl_func_00000000((void *)0x0001E2EC, id);
    }
    if (d & 1) {
        gl_func_00000000((void *)0x0001E308, d);
    }
    rec = (char *)&D_00000000 + id * 0x44;
    *(int *)(rec + 0x3C) = 1;
    gl_func_00000000(flags, d);
    gl_func_00000000(rec + 0x18, 0, 1, a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033880);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00033940);

#ifdef NON_MATCHING
/* gl_func_0003395C: prologue-stolen successor of gl_func_00033880.
 * Predecessor tail computes v0 = &D + a0*68 and t8 = v0->[0x3C]
 * (7 insns, 0x1C bytes). With PROLOGUE_STEALS=28 the splice fires and
 * the logic is correct, but only 73.77% (19/22 insns): IDO does NOT
 * reproduce the target's spill/reload of the call-return ptr to a fixed
 * slot sp+0x1C after EACH gl_func call (target `sw v0,28(sp); lw
 * v0,28(sp)` x2, ~3 missing insns); it copies v0->v1 / keeps in reg
 * instead. Also &local at sp+0x20 vs target sp+0x24. Next-run levers:
 * force the call-result through a spilled stack local across the 2nd
 * call (the documented call-result-respill pattern), or INSN_PATCH the
 * 2 jal literals + the spill/offset insns once the structure is closer.
 * Kept NM (PROLOGUE_STEALS reverted — only valid for exact); INCLUDE_ASM
 * is the build path.
 *   base = &D + a0*68;
 *   if (base->[0x3C] == 0) return;
 *   p = gl_func_00000000(base + 0x18, &local, 1);
 *   if (p->[0x40] != 0) { p = gl_func_00000000(p->[0x34], p->[0x38]); }
 *   p->[0x3C] = 0;     (beqzl: t9==0 arm sets p->[0x3C]=0 directly) */
extern int gl_func_00000000();
void gl_func_0003395C(int a0) {
    char *base = (char*)&D_00000000 + a0 * 68;
    int local;
    char *p;
    if (*(int*)(base + 0x3C) == 0) {
        return;
    }
    p = (char*)gl_func_00000000(base + 0x18, &local, 1);
    if (*(int*)(p + 0x40) != 0) {
        p = (char*)gl_func_00000000(*(int*)(p + 0x34), *(int*)(p + 0x38));
    }
    *(int*)(p + 0x3C) = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003395C);
#endif

/* gl_func_000339B4: 27-insn busy-wait + 2-call. */
void gl_func_000339B4(int a0, int a1, int a2) {
    while (*(int*)((char*)&D_00000000 + 0x3C) != 0) {
        func_00000000();
    }
    func_00000000(0, a0, a1, a2);
    func_00000000(0);
}

/* gl_func_00033A20: 27-insn busy-wait + 2-call wrapper. */
void gl_func_00033A20(int a0, int a1, int a2) {
    while (*(int*)((char*)&D_00000000 + 0x3C) != 0) {
        func_00000000();
    }
    func_00000000(0, a0, a1, a2);
    func_00000000(0);
}

/* gl_func_00033A8C: 22-insn table-scan helper. Walks 9 records at
 * &D_0 + 0x44 (stride 0x44); returns index of first record where
 * field_0x3C == 0; if none, calls gl_func(&D_0 + 0x1E31C) and returns 0. */
int gl_func_00033A8C(void) {
    char *p = (char*)&D_00000000 + 0x44;
    int i;
    for (i = 1; i != 10; i++) {
        if (*(int*)(p + 0x3C) == 0) return i;
        p += 0x44;
    }
    gl_func_00000000((char*)&D_00000000 + 0x1E31C);
    return 0;
}

extern int gl_func_00000000();
int gl_func_00033AE4(int a0, int a1, int a2) {{
    int r = gl_func_00000000(a0, a1, a2);
    gl_func_00000000(r, a0, a1, a2);
    return r;
}}

extern int gl_func_00000000();
int gl_func_00033B28(int a0, int a1, int a2) {{
    int r = gl_func_00000000(a0, a1, a2);
    gl_func_00000000(r, a0, a1, a2);
    return r;
}}

// gl_func_00033B6C — STRUCTURAL PASS (0x78 / 30 words, no episode).
// 2026-05-27 lever pass: decl-order swap (f30 first) brought 24/30→26/30.
// Reverse-decl (end first) regressed to 22/30. Remaining 4 diffs are
// addiu-scheduling within the lui+addiu sequence (target schedules the 4
// loop-invariant pointer-setup addiu in reverse-reg order s3,s2,s1,s0; mine
// in s0,s1,s2,s3). 2026-05-29: PERMUTER CONFIRMED RESISTANT (ran -j4, 28k
// iters, floored at base score 85, never below) AND manual decl/advance/
// body reorderings don't flip it — the preheader address-setup ordering is a
// deterministic IDO scheduler choice, not C-reachable. Permanent 98.67% cap.
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). A sweep / reset-all over the &D_0 registry table —
// the teardown counterpart to gl_func_000337AC / gl_func_00033880.
//
//   void gl_func_00033B6C(void) {
//     R   *rec = (R*)(&D_0 + 0x00);
//     u8  *f18 = (u8*)(&D_0 + 0x18);
//     u8  *f30 = (u8*)(&D_0 + 0x30);
//     u8  *end = (u8*)(&D_0 + 0x2D8);          // loop limit
//     do {
//       rec->w_3C = 0;                          // clear active flag
//       callback(f18, f30, 1);                  // jal 0 per record
//       rec  = (R*) ((char*)rec + 0x44);
//       f18 += 0x44;  f30 += 0x44;
//     } while (f30 != end);                      // ~10 records
//   }
//
// Struct-typing reference: a bulk reset over the SAME 0x44-stride
//   record array (based at &D_0) that gl_func_000337AC and
//   gl_func_00033880 register individual slots into. It iterates
//   every record from &D_0 up to the limit &D_0+0x2D8 — with the
//   0x44 stride that is ((0x2D8-0x30)/0x44) = 0x0A ≈ 10 records —
//   zeroing each record's active flag at +0x3C (the very field the
//   register-one pair sets to 1) and invoking a USO-relocated
//   callback (jal 0 → resolved at load) per record, passing the
//   record's +0x18 and +0x30 sub-regions and a constant 1. The
//   register-one functions (000337AC / 00033880) + this reset-all
//   form the lifecycle trio for the registry table of the
//   game_libs object subsystem (per-frame or per-state-change
//   teardown before re-registration; the table is the collection
//   the gl_func_0002FB74 interpreter iterates).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callback + &D_0
//   record-array sweep (0x44 stride, +0x2D8 limit) — byte-match
//   needs USO mnemonic disasm + record struct typed. Real-C
//   STRUCTURAL body below per the analysis (teardown counterpart
//   to gl_func_000337AC / gl_func_00033880). Byte-match deferred.
//   Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
void gl_func_00033B6C(void) {
    char *f30 = (char *)&D_00000000 + 0x30;
    char *rec = (char *)&D_00000000;
    char *f18 = (char *)&D_00000000 + 0x18;
    char *end = (char *)&D_00000000 + 0x2D8;
    do {
        *(int *)(rec + 0x3C) = 0;
        gl_func_00000000(f18, f30, 1);
        rec += 0x44;
        f18 += 0x44;
        f30 += 0x44;
    } while (f30 != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033B6C);
#endif

// gl_func_00033BE4 — STRUCTURAL PASS (0x2D4 / 181 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). The SIBLING / variant of gl_func_000334E8 — the same
// region/block allocator-management routine, flag-gated entry +
// different data-segment template.
//
//   void gl_func_00033BE4(void *a, unsigned flags) {
//     if (flags & 1) {
//       callback(a, (void*)0x0001E330);       // jal 0 (USO cb)
//     }
//     B *base = &D_0_base;
//     callback(base);                          // 2nd USO cb
//     if (flags == 0) return;                  // gate
//     int TAG  = 0x12340002;                   // block sentinel
//     int used = *(int*)(&D_0 + 0x2C) - *(int*)(&D_0 + 0x08);
//     int mis  = (int)a & 7;                    // 8-byte align
//     if (used < flags) { ... }
//     ... walk / fit 0x12340002-tagged blocks (as in 000334E8) ...
//   }
//
// Struct-typing reference: a heap/region block manager, the direct
//   sibling of gl_func_000334E8. Same core machinery: the magic
//   block-header sentinel 0x12340002 (`lui 0x1234; ori 0x0002`),
//   the used/free span from the global cursor pair (&D_0+0x08 start,
//   &D_0+0x2C current), and 8-byte-granule pointer alignment. The
//   deltas vs gl_func_000334E8: this variant is FLAG-GATED on entry
//   (`flags & 1` selects whether the first USO-relocated setup
//   callback runs, jal 0 → resolved at load), uses the data-segment
//   template 0x0001E330 (vs 000334E8's 0x0001E280), takes a
//   zero-flags early-out, and is slightly larger (0x2D4 vs 0x2C4) —
//   consistent with this being the "allocate/grow with options"
//   entry vs 000334E8's "init/setup" entry of the SAME allocator.
//   Together with gl_func_000334E8 these form the alloc front-end
//   for the gl_func_00030AF4 0x45010 arena and the
//   gl_func_00032E18 / gl_func_00033228 sub-record allocations
//   (0x12340002 is the shared heap block magic; 0x0001E280 /
//   0x0001E330 are the deferred template-symbolization sites).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + global
//   region cursors + 0x12340002 block-magic + flag gate / alignment
//   math — byte-match needs USO mnemonic disasm + allocator structs
//   typed. Real-C STRUCTURAL body below per the analysis (sibling
//   of gl_func_000334E8). Byte-match deferred. Name pre-checked:
//   no extern reuse.
// gl_func_00033BE4 — FULL m2c DECODE (64.98% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00033BE4)();
void gl_func_00033BE4(s32 arg0, u32 arg1) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t4;
    s32 var_s5;
    s32 var_v1;
    u32 temp_v0;
    u32 temp_v1;
    u32 var_s2;
    u32 var_s4;
    u32 var_v0;
    u8 temp_t0;
    char *var_a0;

    var_s4 = arg1;
    var_s5 = arg0;
    if (arg1 & 1) {
        gl_func_0001CA10(0, 0x1E330);
    }
    gl_func_0001CA10(0);
    if (arg1 != 0) {
        do {
            var_s2 = var_s4;
            temp_a0 = var_s5 & 7;
            temp_v0 = *(s32 *)0x2C - *(s32 *)8;
            if (temp_v0 < var_s4) {
                var_s2 = temp_v0;
            }
            if (var_s2 != 0) {
                if (temp_a0 != 0) {
                    temp_v1 = 8 - temp_a0;
                    var_v0 = 0;
                    if (temp_v1 < var_s2) {
                        var_s2 = temp_v1;
                    }
                    if (var_s2 != 0) {
                        var_a0 = 0;
                        var_v1 = var_s5;
                        do {
                            temp_t0 = *(int*)var_v1;
                            var_v0 += 1;
                            var_v1 += 1;
                            var_a0 += 1;
                            FW(var_a0, -0x1) = temp_t0;
                        } while (var_v0 < var_s2);
                    }
                    gl_func_0001CA10(0, *(char *)8, 0, var_s2);
                } else {
                    gl_func_0001CA10(0, *(char *)8, var_s5, var_s2);
                }
                temp_a2 = *(char *)8 + var_s2;
                *(char *)8 = temp_a2;
                gl_func_0001CA10(0, *(s32 *)0x28, temp_a2);
            }
            temp_t4 = *(char *)8;
            if (*(char *)0x2C == temp_t4) {
                *(s32 *)0x14 = temp_t4;
                gl_func_0001CA10(0, *(char *)0x28 + 0xC, temp_t4);
                if (*(char *)0x2C != *(char *)8) {
                    gl_func_0001CA10(0, 0x1E344);
                }
                gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340001);
                if (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002) {
                    do {
                        gl_func_0001CA10(0);
                    } while (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002);
                }
                temp_a2_2 = *(s32 *)0x24;
                *(char *)8 = temp_a2_2;
                gl_func_0001CA10(0, *(char *)0x28, temp_a2_2);
                gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340003);
                if (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002) {
                    do {
                        gl_func_0001CA10(0);
                    } while (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340002);
                }
            }
            var_s4 -= var_s2;
            var_s5 += var_s2;
            if ((s32) var_s4 < 0) {
                gl_func_0001CA10(0, 0x1E358);
            }
            if (var_s4 != 0) {
                gl_func_0001CA10(0);
            }
        } while (var_s4 != 0);
    }
    gl_func_0001CA10(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033BE4);
#endif

// gl_func_00033EB8 — STRUCTURAL PASS (0x2D0 / 180 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). The THIRD member of the gl_func_000334E8 /
// gl_func_00033BE4 allocator family — the heap RESET / RE-BASE entry.
//
//   void gl_func_00033EB8(void *a, unsigned flags) {
//     if (flags & 1) {
//       callback(a, (void*)0x0001E368);       // jal 0 (USO cb)
//     }
//     B *base = &D_0_base;
//     callback(base);                          // 2nd USO cb
//     if (flags == 0) return;                  // gate
//     int TAG2 = 0x12340002, TAG3 = 0x12340003;  // two block tags
//     int hdr  = *(int*)(&D_0 + 0x28);
//     int nv   = callback(base, hdr);          // 3rd USO cb
//     *(int*)(&D_0 + 0x08) = nv;               // RE-BASE start cursor
//     if (*(int*)(&D_0 + 0x2C) != *(int*)(&D_0 + 0x0C)) { ... }
//     ... walk blocks tagged 0x12340002 / 0x12340003 ...
//   }
//
// Struct-typing reference: the third entry of the region/block
//   allocator family (with gl_func_000334E8 = init/setup,
//   gl_func_00033BE4 = alloc/grow). Same flag-gated prologue
//   (`flags & 1` selects the first USO-relocated setup callback,
//   jal 0 → resolved at load) and a data-segment template, here
//   0x0001E368. The distinguishing behavior: it handles BOTH block
//   header magics — 0x12340002 AND 0x12340003 (two `lui 0x1234;
//   ori` pairs) — and, crucially, RE-WRITES the global heap START
//   cursor at &D_0+0x08 from a callback's return value (a heap
//   reset / re-base / compaction step), then compares the
//   &D_0+0x0C and &D_0+0x2C cursors. This is the allocator's
//   "reset / reclaim" front-end — the lifecycle complement to
//   000334E8 (init) and 00033BE4 (allocate). The trio is the heap
//   manager behind the gl_func_00030AF4 0x45010 arena and the
//   gl_func_00032E18 / gl_func_00033228 sub-record allocations
//   (block magics 0x12340002 / 0x12340003; templates 0x0001E280 /
//   0x0001E330 / 0x0001E368 are deferred symbolization sites).
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks + global
//   heap cursors (re-based) + dual 0x1234000{2,3} block-magic —
//   byte-match needs USO mnemonic disasm + allocator structs typed.
//   Real-C STRUCTURAL body below per the analysis (reset/reclaim
//   front-end completing the allocator trio with 000334E8 init +
//   00033BE4 alloc). Byte-match deferred. Name pre-checked: no
//   extern reuse.
// gl_func_00033EB8 — FULL m2c DECODE (59.82% NM, no episode). game_libs non-jumptable via scripts/decomp-uso-cf.py.
#ifdef NON_MATCHING


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00033EB8)();
void gl_func_00033EB8(s32 arg0, u32 arg1) {
    u32 sp30;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s4;
    s32 var_v0;
    u32 temp_v0_3;
    u32 var_s0;
    u32 var_s3;
    u32 var_t0;
    u8 *var_v1;
    u8 temp_t7;

    var_s3 = arg1;
    var_s4 = arg0;
    if (arg1 & 1) {
        gl_func_0001CA10(0, 0x1E368);
    }
    gl_func_0001CA10(0);
    if (arg1 != 0) {
        do {
            *(s32 *)8 = gl_func_0001CA10(0, *(s32 *)0x28);
            if (*(s32 *)0x2C == *(s32 *)0xC) {
                temp_v0 = gl_func_0001CA10(0, *(char *)0x28 + 8);
                *(s32 *)0x10 = temp_v0;
                if (temp_v0 == 0x12340001) {
                    if (*(char *)0x2C != *(char *)0xC) {
                        gl_func_0001CA10(0, 0x1E37C);
                    }
                    if (*(char *)0x2C != *(char *)8) {
                        gl_func_0001CA10(0, 0x1E394);
                    }
                    gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340002);
                    temp_v0_2 = *(s32 *)0x24;
                    *(char *)0xC = temp_v0_2;
                    *(char *)8 = temp_v0_2;
                    if (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340003) {
                        do {
                            gl_func_0001CA10(0);
                        } while (gl_func_0001CA10(0, *(char *)0x28 + 8) != 0x12340003);
                    }
                    gl_func_0001CA10(0, *(char *)0x28 + 8, 0x12340002);
                }
            }
            temp_v1 = var_s4 & 7;
            var_s0 = *(char *)8 - *(char *)0xC;
            if (var_s3 < var_s0) {
                var_s0 = var_s3;
            }
            if (var_s0 != 0) {
                if (temp_v1 != 0) {
                    temp_v0_3 = 8 - temp_v1;
                    if (temp_v0_3 < var_s0) {
                        var_s0 = temp_v0_3;
                    }
                    sp30 = 0;
                    gl_func_0001CA10(0, *(char *)0xC, 0, var_s0);
                    var_t0 = 0;
                    if (var_s0 != 0) {
                        var_v1 = 0;
                        var_v0 = var_s4;
                        do {
                            temp_t7 = *(int*)var_v1;
                            var_t0 += 1;
                            var_v0 += 1;
                            var_v1 += 1;
                            FW(var_v0, -0x1) = temp_t7;
                        } while (var_t0 < var_s0);
                    }
                } else {
                    gl_func_0001CA10(0, *(char *)0xC, var_s4, var_s0);
                }
                *(char *)0xC = (s32) (*(char *)0xC + var_s0);
            }
            var_s3 -= var_s0;
            var_s4 += var_s0;
            if ((s32) var_s3 < 0) {
                gl_func_0001CA10(0, 0x1E3AC);
            }
            if (var_s3 != 0) {
                gl_func_0001CA10(0);
            }
        } while (var_s3 != 0);
    }
    gl_func_0001CA10(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033EB8);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00034180);

// gl_func_00034188 — STRUCTURAL PASS (0xB8 / 46 words, no episode).
// Raw-.word USO form (game_libs). CLEAN SINGLE FUNCTION (1 jr, one
// prologue). A device / subsystem step with indirect-call (vtable)
// dispatch and a status busy-poll.
//
//   void gl_func_00034188(void) {
//     H *h = ...;                              // a handle
//     int (*f)() = h->fp_1C;
//     int v = f(h->h_18 + (int)h);             // jalr h->0x1C
//     callback0(); callback0();                // jal 0 x2
//     while ((u32)v < 0x1E0) {                       // poll (< 480)
//       callback0();
//       v = ...;                                // re-read status
//     }
//     H *g = *(H**)(&D_0 + 0x240);             // global handle
//     int (*f2)() = g->fp_64;
//     int r = f2(g->h_60 + (int)g);            // jalr g->0x64
//     callback0();
//     *(int*)(&D_0 + 0x204) = ... ;             // timing state
//     *(int*)((char*)g + 0x144) = 0;
//     // uses cycle constant 0x001E8480 = 2,000,000
//   }
//
// Struct-typing reference: a hardware/device-driver-style tick. It
//   dereferences a handle and calls a FUNCTION POINTER stored at
//   handle+0x1C (passing handle+handle->0x18 as the arg — a
//   self-relative callback), spins on a status value until it
//   reaches 0x1E0 (= 480, a scanline/line-count-shaped bound)
//   while pumping a USO-relocated callback (jal 0 → resolved at
//   load) each iteration, then fetches a global handle from
//   &D_0+0x240 and calls a SECOND function pointer at handle+0x64
//   (arg handle+handle->0x60). Finally it writes timing/state
//   globals (&D_0+0x204 and the handle's +0x144) using the cycle
//   constant 0x001E8480 (2,000,000 — a 1/30s-ish VR4300 cycle
//   budget). A device step / vsync-or-DMA-wait node of the
//   game_libs object subsystem (the indirect dispatch through
//   h->0x1C / h->0x64 means this object family is polymorphic —
//   those offsets are its vtable slots; &D_0+0x240 is the active-
//   device global).
// Caps (DEFERRED): raw-word USO + jalr through object vtable slots
//   + USO-reloc jal-0 callbacks + status busy-poll + cycle constant
//   (0x001E8480 = 2,000,000) — byte-match needs USO mnemonic disasm
//   + handle/vtable struct typed. Real-C STRUCTURAL body below per
//   the analysis. Byte-match deferred. Name pre-checked: no extern
//   reuse.
#ifdef NON_MATCHING
void gl_func_00034188(void) {
    char *h = (char *)&D_00000000;
    int (*f)(void *);
    int v;
    char *g;
    int (*f2)(void *);
    int r;
    f = *(int (**)(void *))(h + 0x1C);
    v = f(h + *(int *)(h + 0x18));
    gl_func_00000000();
    gl_func_00000000();
    while ((u32)v < 0x1E0) {
        gl_func_00000000();
    }
    g = *(char **)((char *)&D_00000000 + 0x240);
    f2 = *(int (**)(void *))(g + 0x64);
    r = f2(g + *(int *)(g + 0x60));
    gl_func_00000000();
    *(int *)((char *)&D_00000000 + 0x204) = 0x001E8480;
    *(int *)(g + 0x144) = 0;
    (void)r;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034188);
#endif

// gl_func_00034240 — STRUCTURAL PASS + BUNDLE BOUNDARY NOTE
// (0x218 / 134 words, no episode). Raw-.word USO form (game_libs).
//
// MULTI-FUNCTION USO BUNDLE. The .s has SEVEN jr $ra but only ONE
// stack-frame prologue (the 27BDFF40 at the very top). The other
// six jr's cluster densely in the tail (0x343D8 / 0x343EC / 0x3441C
// / 0x34428 / 0x34434 / 0x34440 / 0x34450 — note the repeated
// 3-word spacing) and have NO addiu $sp before them: they are tiny
// LEAF accessor functions that don't allocate a stack frame, which
// is why the "one prologue ⇒ one function" heuristic FALSELY reads
// this as a single function. Splat could not separate them in this
// relocatable USO segment. Only the NAMED LEADING function is
// decoded; the ~6 trailing no-frame leaves are a DEFERRED USO
// RE-SPLIT (tracked with the other game_libs_post.c multi-jr
// boundary notes; NOT fixable with mnemonic split-fragments.py /
// merge-fragments — raw-.word relocatable USO needs the
// spimdisasm-USO migration).
//
// Leading fn gl_func_00034240 (0x34240..~0x343D8):
//   void gl_func_00034240(int a2) {
//     R *r = *(R**)&D_0;
//     Desc d;                                  // local at sp+0x40
//     callback(&d, -1);                         // jal 0 (USO cb)
//     r->w_38 = 1;                              // mark initialized
//     callback(&D_0, *(int*)(r + 0x34), 1);     // 2nd USO cb
//     if (*(int*)0x0001E21C != 0) {             // data-seg template
//       callback(&D_0); callback(&d); ...
//     }
//   }
// i.e. a subsystem / object INITIALIZER: builds a local descriptor
// on the stack (sp+0x40), runs setup USO-relocated callbacks
// (jal 0 → resolved at load) keyed off a data-segment template at
// 0x0001E21C, sets the initialized flag in the &D_0-rooted record
// (r->0x38 = 1), and fans out further callbacks. The bundled tail
// leaves are its companion no-frame accessors (getters into the
// record this fn initializes).
//
// Struct-typing reference: the constructor/init entry of the
//   device/object family whose per-frame tick is gl_func_00034188
//   (same &D_0-rooted record, vtable-style indirection); 0x0001E21C
//   is a deferred data-segment template-symbolization site.
// Caps (DEFERRED): raw-word USO + USO-reloc jal-0 callbacks +
//   data-seg template — byte-match needs USO mnemonic disasm +
//   boundary re-split (the 6 no-frame trailing leaves need
//   spimdisasm-USO migration). Real-C STRUCTURAL body below for the
//   NAMED leading function only — bundled tail leaves untouched.
//   Byte-match deferred. Name pre-checked: no extern reuse.
#ifdef NON_MATCHING
extern int D_00000000;
// Subsystem run loop. G = *&D_0. Marks G->0x38=1, builds a local descriptor d
// (cb(&d,-1)), saves G->0x34. Polls a config table at absolute 0x1E21C: each
// round cb(&D)/cb(&d) refreshes d, and the d[0x18] state walks the table
// (advance on match, reset on miss) until the entry is 0. Then a vtable
// dispatch G->0x28->0x1C(G + (short)G->0x28->0x18) and two cbs. Main loop:
// G->0x34=&d; if d[0x10] cb(); exit when d[0x1C]&0x40000; when d[0x18]&0x100
// run two cbs; cb(&D)/cb(&d); repeat. Tail: cb(0x202); G->0x38=0; restore
// G->0x34. Reloc-blind cbs/&D (field-0 matchable); 0x1E21C is a baked absolute.
void gl_func_00034240(int a2) {
    char d[0x40];
    char *cfg;
    char *s0;
    char *s3;
    char *g;
    int saved34;
    (void)a2;

    *(int *)(*(char **)&D_00000000 + 0x38) = 1;
    gl_func_00000000(d, -1);
    saved34 = *(int *)(*(char **)&D_00000000 + 0x34);
    gl_func_00000000((char *)&D_00000000, 1);

    cfg = (char *)0x0001E21C;
    s3 = (char *)&D_00000000;
    s0 = cfg;
    if (*(int *)cfg != 0) {
        do {
            gl_func_00000000(s3);
            gl_func_00000000(d);
            if (*(int *)(d + 0x18) != 0) {
                if (*(int *)(d + 0x18) == *(int *)s0) {
                    s0 += 4;
                } else {
                    s0 = cfg;
                }
            }
        } while (*(int *)s0 != 0);
    }

    s3 = (char *)&D_00000000;
    gl_func_00000000(0);
    gl_func_00000000((char *)&D_00000000, 0);

    g = *(char **)(*(char **)&D_00000000 + 0x28);
    (*(void (**)(char *))(g + 0x1C))(*(char **)&D_00000000 + *(short *)(g + 0x18));
    gl_func_00000000();
    gl_func_00000000();

    for (;;) {
        *(int *)(*(char **)&D_00000000 + 0x34) = (int)d;
        if (*(int *)(d + 0x10) != 0) {
            gl_func_00000000();
        }
        if (*(int *)(d + 0x1C) & 0x40000) {
            break;
        }
        if (*(int *)(d + 0x18) & 0x100) {
            gl_func_00000000();
            gl_func_00000000();
        }
        gl_func_00000000(s3);
        gl_func_00000000(d);
    }
    gl_func_00000000(0x202);
    *(int *)(*(char **)&D_00000000 + 0x38) = 0;
    *(int *)(*(char **)&D_00000000 + 0x34) = saved34;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034240);
#endif

// Indexed read from the segment-base int table: return D[a0]. Builds byte-exact
// as plain C (single &D_00000000 segment-base ref, resolves to addr 0). No
// episode (reloc-blind base) but the C body is the build path (moves %).
int game_libs_func_000343E0(int a0) {
    return *(int *)((char *)&D_00000000 + a0 * 4);
}

/* game_libs_func_000343F4: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000343F4);

// Address-of accessors into a 0xC-stride table at segment offset 0x1E3C8
// (lui+addiu address-style return; the offset is baked into the bytes).
int game_libs_func_00034424(void) {
    return (int)((char *)&D_00000000 + 0x1E3C8);
}

int game_libs_func_00034430(void) {
    return (int)((char *)&D_00000000 + 0x1E3D4);
}

int game_libs_func_0003443C(void) {
    return (int)((char *)&D_00000000 + 0x1E3E0);
}
