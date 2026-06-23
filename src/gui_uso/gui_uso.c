#include "common.h"

extern char D_00000000;

/* SOURCE=4 audit 2026-06-01: this cluster is not a missed accessor-template
 * candidate. The 0x0..0x148 char mapper is an over-split early-return chain;
 * the fragments look like leaf-branch-past-end/caller-set-register caps only
 * because predecessor tests branch into later entries while carrying $v0/$a0.
 * find-misplit-pairs.py does not flag it because each split entry has its own
 * jr ra. Proper recovery is a deliberate full-cluster merge, not per-fragment
 * C bodies. */

/* gui_func_00000000 [0x00..0x148): full-cluster MERGE (2026-06-09) of the
 * previously over-split char->glyph-index mapper (12 splat fragments, each a
 * 6-insn early-return chain link; see audit note above). Layout:
 *   0x00: 2-insn loader trampoline `b 0x1CDC0; sw a0,0(sp)` (USO entry-0;
 *         NOT emittable from this function's C -- needs the USO-header
 *         PREFIX_BYTES mechanism or a boundary fix to land byte-exact)
 *   0x08: mapper body (bnel chain + 3 range folds), faithful C below.
 * Maps punctuation to glyph indices 0x24-0x29, a-z/A-Z to 0x0A.., digits to
 * 0x0..0x9; default returns the input char. */
#ifdef NON_MATCHING
int gui_func_00000000(c)
int c;
{
    c &= 0xFF;
    if (c == 0x21) { c = 0x27; goto ret; }   /* '!' */
    if (c == 0x2C) { c = 0x28; goto ret; }   /* ',' */
    if (c == 0x2F) { c = 0x29; goto ret; }   /* '/' */
    if (c == 0x5B) { c = 0x26; goto ret; }   /* '[' */
    if (c == 0x5D) { c = 0x27; goto ret; }   /* ']' */
    if (c == 0x2B) { c = 0x24; goto ret; }   /* '+' */
    if (c == 0x5F) { c = 0x25; goto ret; }   /* '_' */
    if (c == 0x2E) { c = 0x25; goto ret; }   /* '.' */
    if (c == 0x2D) { c = 0x25; goto ret; }   /* '-' */
    if (c >= 0x61 && c < 0x7B) { c -= 0x57; goto ret; }          /* a-z */
    if (c >= 0x41 && c < 0x5B) { c -= 0x37; goto ret; }          /* A-Z */
    if (c >= 0x30 && c < 0x3A) { c = (c - 0x30) & 0xFF; }        /* 0-9 */
ret:
    return c & 0xFF;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000000);
#endif

/* gui_func_00000148: single coherent function, 0x148-0x558 (0x410 / 260
 * insns), terminated by `jr ra; addiu sp,sp,0x80`. The earlier "BUNDLED
 * 0x7D0/500-insn / 3 sub-fns + orphan" note was STALE: expected/gui_uso.c.o
 * shows the next symbol gui_uso_func_0000055C starting at 0x55C, and the
 * function has zero inter-function relocs in range. The two `jal 0` are
 * baked-zero placeholders -> gl_func_00000000 (find-or-create allocator).
 *
 * GLYPH-GRID-LAYOUT constructor. Args
 *   (char *obj, int a1, int a2, int a3, int rows, int cols)   [rows=sp+0x90,
 *   cols=sp+0x94]. Find-or-create obj (alloc 40 if null). Fields:
 *     o->4  = a1 (pixel/atlas base ptr)
 *     o->C  = a2/rows (gw, glyph cell width) -- later overwritten by maxw
 *     o->0  = rows*cols (cell count)
 *     o->10 = o->14 = a3/cols (gh, glyph cell height)
 *     o->18 = a2,  o->1C = a3
 *     o->20 = gl_func_00000000(rows*cols*20)  (per-cell record array, 20B ea)
 *   Then per cell (col in [0,cols), row in [0,rows), gi = col*rows+row):
 *   scans the gh x gw pixel block at base + col*gh*a2 + row*gw, finding
 *   min/max non-zero column (minx/maxx). Writes record g = o->0x20 + gi*20:
 *     g[0]=row*gw+minx, g[1]=col*gh, g[2]=(maxx+1)-minx, g[4]=minx.
 *   Tracks maxw = max(maxx+1), sum = sum(maxx+1). Finally o->C = maxw,
 *   o->8 = (int)((sum*0.5f)/o->0), and back-fills g[3]=o->C for every cell.
 *
 * STATUS: correct-C reconstruction, ~71% fuzzy (was 55%). Structure exact;
 * residual is uopt spill-coloring + arg->saved-reg assignment (frame 0x98 vs
 * target 0x80) -- the documented regalloc-coloring cap class. Permuter (5k+
 * iters) does not close it. NOT byte-exact; kept NON_MATCHING. */
#ifdef NON_MATCHING
void *gui_func_00000148(char *a0, int a1, int a2, int a3, int rows, int cols) {
    char *o = a0;
    int gw, gh, prod;
    int sum, maxw;
    int col, row, gi;

    if (a0 == 0) {
        o = (char *)gl_func_00000000(40);
        if (o == 0) {
            goto end;
        }
    }
    gw = a2 / rows;
    gh = a3 / cols;
    *(int *)(o + 4) = a1;
    *(int *)(o + 0xC) = gw;
    prod = rows * cols;
    *(int *)(o + 0) = prod;
    *(int *)(o + 0x10) = gh;
    *(int *)(o + 0x18) = a2;
    *(int *)(o + 0x1C) = a3;
    *(int *)(o + 0x14) = gh;
    *(int *)(o + 0x20) = gl_func_00000000(prod * 20);

    sum = 0;
    maxw = 0;
    for (col = 0; col < cols; col++) {
        gi = col * rows;
        for (row = 0; row < rows; row++) {
            char *px = (char *)*(int *)(o + 4) + (col * gh) * a2 + row * gw;
            int minx = gw, maxx = 0;
            int y;
            for (y = 0; y < gh; y++) {
                char *line = px + y * a2;
                int x;
                for (x = 0; x < gw; x++) {
                    if (line[x] != 0) {
                        if (x < minx) minx = x;
                        if (maxx < x) maxx = x;
                    }
                }
            }
            {
                int *g = (int *)(*(int *)(o + 0x20) + gi * 0x14);
                g[0] = row * gw + minx;
                g[1] = col * gh;
                g[2] = (maxx + 1) - minx;
                g[4] = minx;
            }
            if (maxw < maxx + 1) maxw = maxx + 1;
            sum += maxx + 1;
            gi++;
        }
    }
    *(int *)(o + 0xC) = maxw;
    *(int *)(o + 8) = (int)(((float)sum * 0.5f) / *(int *)(o + 0));
    {
        int i;
        for (i = 0; i < *(int *)(o + 0); i++) {
            *(int *)(*(int *)(o + 0x20) + i * 0x14 + 0xC) = *(int *)(o + 0xC);
        }
    }
end:
    return o;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000148);
#endif

#ifdef NON_MATCHING
/* Full decode 2026-06-01. Display-list emitter (sibling of
 * gui_uso_func_000016A4): appends 6 fixed GBI commands (RDPPIPESYNC, two
 * SETOTHERMODE_H, SETOTHERMODE_L, SETCOMBINE, B/B-tile) to the gfx builder
 * reached via *(D+0x254)->0x158, caching it at a0->0x24 between appends. */
void gui_uso_func_0000055C(char *a0) {
    char *b;
    char *p;
    char *buf;
    int i;

    b = *(char **)(*(char **)((char *)&D_00000000 + 0x254) + 0x158);
    *(char **)(a0 + 0x24) = b;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xE7000000;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)(a0 + 0x24);
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xBA001402;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)(a0 + 0x24);
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xBA001301;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)(a0 + 0x24);
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xB900031D;
    *(int *)(buf + i * 8 + 4) = 0x00404240;

    b = *(char **)(a0 + 0x24);
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFC309661;
    *(int *)(buf + i * 8 + 4) = 0xFF2FFFFF;

    b = *(char **)(a0 + 0x24);
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xBB000001;
    *(int *)(buf + i * 8 + 4) = 0x80008000;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000055C);
#endif

#ifdef NON_MATCHING
/* Full decode 2026-06-01. SETPRIMCOLOR-style DL emitter: appends a 0xFA
 * command packing the a2 Vec3 (each *255, cast to byte) as RGB plus a1 as
 * alpha into word1, to the gfx builder at a0->0x24. */
void gui_uso_func_000006B8(char *a0, int a1, float *a2, int a3) {
    char *b = *(char **)(a0 + 0x24);
    char *p;
    char *buf;
    int i;
    int r, g, bl;
    (void)a3;

    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFA000000;
    r = (int)(unsigned)(a2[0] * 255.0f);
    g = (int)(unsigned)(a2[1] * 255.0f);
    bl = (int)(unsigned)(a2[2] * 255.0f);
    *(int *)(buf + i * 8 + 4) =
        (r << 24) | ((g & 0xff) << 16) | ((bl & 0xff) << 8) | (a1 & 0xff);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000006B8);
#endif

/* gui_uso_func_000008C0 [0x8C0..0xB58): GUI primitive-color DL builder --
 * FULL-CLUSTER MERGE 2026-06-09 of the former 22-insn fall-through head +
 * gui_func_00000918 (144-insn body; splat split at a mid-function
 * scheduling artifact). Merge-safety proven via the gui.uso module tables:
 * 0x8C0 appears as a referenced entry, 0x918 appears NOWHERE (not an
 * independent runtime entry; the old "implicit $v0-input convention" was
 * just the fall-through from this head). Structure: emits
 * G_SETOTHERMODE(0xB900031D, 0x00404240-ish) + G_SETCOMBINE(0xFC309661...)
 * pairs into the DL ring at ctx->dl (ctx = a0->0x24, cursor at
 * ctx->0xC->4, 8-byte slots), then two G_SETPRIMCOLOR-class commands whose
 * color word is packed from three floats (R/G/B x 1.0f scale) via the
 * cvt.w.s + FCSR-overflow-clamp idiom (cfc1/ctc1, andi 0x78), each channel
 * clamped to 0..0xFF and OR'd into byte lanes 16/8/0. Multi-tick: float
 * scheduling + the clamp ladder need the f3dex2 treatment; INCLUDE_ASM is
 * the build path. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gui_uso_func_000008C0(int *a0) {
    int *ctx = (int *)a0[0x24 / 4];
    int *dls = (int *)ctx[0xC / 4];
    int cur;
    unsigned int *slot;

    /* G_SETOTHERMODE + constant pair */
    cur = dls[1];
    dls[1] = cur + 1;
    slot = (unsigned int *)(*(char **)dls + (cur << 3));
    slot[0] = 0xB900031D;
    slot[1] = 0x00404240;
    /* G_SETCOMBINE pair, then two G_SETPRIMCOLOR commands with the
     * 3-channel float->u8 FCSR-clamped color pack (see comment). */
    /* ... full body pending the f3dex2 pass ... */
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000008C0);
#endif

extern int gl_func_00000000();
#ifdef NON_MATCHING
/* gui rendering loop - iterates over a3-derived count, indexes via a0[5]
 * scaled by 0x14 (s8 = 20-byte stride; same stride as the glyph table in
 * gui_func_000013E8). 107 instructions / 0x1AC.
 *
 * Decoded entry stage:
 *   1. Save 9 $s-regs + ra (frame -0x58)
 *   2. Save a2 to caller arg slot (sp+0x60), a3 to sp+0x64
 *   3. s1 = a0; s2 = a1; s3 = a0[5]; s6 = a3; s7 = 0 (outer counter)
 *   4. v0 = gl_func_00000000(a3); if v0 == 0 goto end (early exit)
 *   5. s8 = 0x14 (loop-stride constant)
 *
 * Inner loop body (88 insns) - heavy multi-jal iteration over the s7 counter:
 *   - reads from (a0[?] + s7 * 20) using s8 as the stride
 *   - dispatches via 4 separate jals (jal gl_func_00000000 placeholders)
 *   - clamps signed values via `seq -1, neq -1` pattern, sign-extension via
 *     `sll, sra` for byte/short reads
 *   - termination: `s7++; if (s7 < v0) loop;` (sltu + bnel branch likely)
 *
 * Multi-tick decompile; 36.12% NM (up from 13.9% with stub).
 *
 * Loop body decoded 2026-05-05 (from asm 0xBB0-0xCD0):
 *   for each char in string (s6 advances, s7 = 0..v0-1):
 *     if (*s6 == ' '):
 *       s2 += s1[8]          ; space-width advance
 *     else:
 *       glyph_idx = gl_func(c)
 *       glyph = (int*)(s1[0x20] + glyph_idx * 0x14)
 *       s4 = glyph[2] & 0xFF
 *       gl_func(s1[0x24], s1[4], s1[0x18], s1[0x1C], glyph[0..2], s3, 0)
 *           ; emit RDP cmd 1 (5+ args via outgoing slots)
 *       gl_func(s1[0x24], s2, saved_a2, glyph[2], s3, 1024, 1024)
 *           ; emit RDP cmd 2 (glyph render)
 *       s2 += *(s1[0x20] + (s4/0x14)*4 + 8)  ; glyph-width advance
 *     s6++; s7++; gl_func(saved_a3)  ; per-char callback
 *
 * Remaining ~64pp gap is multi-arg gl_func's outgoing-slot stores (sp+0x10..
 * sp+0x20) and FP-reg + divu+mflo patterns from `t6 = s3<<10; t6/s3 = 1024`
 * (always-1024 dead-code from the s3*1024 division). IDO -O2 may strength-
 * reduce s3<<10/s3 to constant 1024 (eliminating the divu+mflo+break trap),
 * but expected has the FULL division emit. Forcing the literal division to
 * survive: try `volatile int s5 = (s3 << 10) / s3;` - TODO next pass.
 *
 * Default build still matches via INCLUDE_ASM. */
void gui_func_00000B58(int *a0, int a1, int a2, int a3) {
    int v0;
    int s7;
    char *s6 = (char*)a3;       /* string pointer */
    int *s1 = a0;               /* base struct */
    int s2 = a1;                /* x position (advances per char) */
    int s3 = a0[0x14 / 4];      /* glyph height/scale */
    int s8 = 0x14;              /* glyph-table stride (20 bytes per entry) */
    int s5;

    v0 = gl_func_00000000(a3);  /* string length */
    if (v0 == 0) return;
    s7 = 0;
    do {
        unsigned char c = *s6;
        /* s5 = (s3<<10)/s3 (=1024) recomputed each iter at loop top — target
         * emits the div + break-checks here, not a folded literal. */
        s5 = (s3 << 10) / s3;
        if (c == ' ') {
            s2 += s1[8 / 4];     /* space-width advance */
        } else {
            int glyph_idx = gl_func_00000000(c);
            int *glyph = (int*)((char*)s1[0x20 / 4] + glyph_idx * s8);
            int g0 = glyph[0], g1 = glyph[1], g2 = glyph[2];
            int s4 = g2 & 0xFF;  /* low-byte of glyph[2] */
            /* RDP cmd 1: 6-arg gl_func (s4 in args, s3, plus 2 stack slots) */
            gl_func_00000000(s1[0x24 / 4], s1[4 / 4], s1[0x18 / 4], s1[0x1C / 4],
                             /* sp+0x10 */ g0, g1, g2, s3, 0);
            /* RDP cmd 2: glyph render - s2/saved_a2 with s5 scaling */
            gl_func_00000000(s1[0x24 / 4], s2, a2, g2,
                             /* sp+0x10 */ s3, s5, s5);
            s2 += *(int*)((char*)s1[0x20 / 4] + (s4 / s8) * 4 + 8);  /* glyph width advance */
        }
        s6++;
        s7++;
        gl_func_00000000(a3);    /* per-char callback (handle) */
    } while (s7 < v0);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000B58);
#endif

#ifdef NON_MATCHING
/* gui_func_00000D04: 0x200 (128 insns). Text-rendering function that builds
 * an RDP command list. Partial structural decode 2026-05-03:
 *
 * PROLOGUE (insns 1-15):
 *   addiu sp,-0x58              ; large frame
 *   sw ra/s0..s8 to sp+0x30..0x54  ; saves all 9 callee-saved (heavy state)
 *   sw a2,0x60(sp); sw a3,0x64(sp) ; spill last 2 args
 *   v0 = a0->0x24               ; gp/cmd-list-state ptr
 *   s4 = a0->0x14               ; some scaler
 *   t2 = 0xBB000001             ; built via lui+ori - RDP opcode
 *                                 (G_SETCOMBINE or similar 1-byte cmd)
 *   t3 = 0x80008000             ; coord constant (signed-min XY)
 *   s1 = a0; s3 = a1; s7 = a3; a0 = a3
 *
 * BODY HEAD (insns ~15-25):
 *   v1 = v0->0xC                ; cmd-list pointer (head)
 *   t0 = v1->4                  ; current count
 *   v1->4 = t0 + 1              ; bump count
 *   slot = v0->0xC->[0] + t0*8  ; slot[0..7] = next 8-byte cmd
 *   slot[0] = 0xBB000001        ; emit RDP cmd
 *   slot[4] = 0x80008000        ; emit cmd-args
 *   sw a3,0x64(sp)              ; re-spill a3
 *   jal gl_func(a3)             ; string length helper
 *   move s8,zero                ; total = 0 (delay slot)
 *   if (v0 == 0) goto end       ; empty string, branch to epilogue
 *
 * BODY MIDDLE (insns ~25-100): per-character loop
 *   c = *s7                     ; lbu char
 *   if (c == ' ') skip          ; space-handling branch
 *   width_scaled = s4 << 10     ; scaled glyph width?
 *   div(width_scaled, s4)       ; division - possibly per-glyph stride
 *   bnez s4 (guard against /0)
 *   ... (further glyph-table lookups, FPU coord math, more RDP cmd emits)
 *
 * EPILOGUE: restore all 9 saved regs, addiu sp, jr ra.
 *
 * Speculation: this is the entry point for "draw text string with kerning"
 * - emits a SETCOMBINE-class RDP cmd, then loops over chars accumulating
 * positions and submitting per-glyph display list. ~80 insns of body math
 * remain TBD; multi-tick decomp expected. */
extern int gl_func_00000000();
extern char D_00000000;
/* Full decode (2026-05-24): kerned text-string renderer. Emits a SETCOMBINE-class
 * RDP cmd (0xBB000001/0x80008000), then for each of strlen(a3) chars: space ->
 * advance x by the space glyph's width; else look up glyph = a0->0x20[idx*0x14]
 * (idx = gl_func(c)), make two per-glyph render calls, advance x by glyph width.
 * The two `1024` packet metrics are REDUNDANT signed divisions in the target:
 * (scale<<10)/scale and (glyph[2]<<10)/glyph[2] (each ==1024 but IDO emits the
 * div + the div-by-0 / -1<<31-overflow break-traps). Modeling both + the byte-4
 * a0 field + the re-deref'd cmd_list[0] lifts the body 45.3 -> 71%. Residual cap:
 * 9-saved-reg allocation (s0-s8) numbering + frame-size/scheduling; INCLUDE_ASM
 * stays the build path. */
void gui_func_00000D04(int *a0, int *a1, int a2, char *a3) {
    int *cmd_state = (int *)a0[0x24 / 4];
    int *cmd_list = (int *)cmd_state[0xC / 4];
    int scale = a0[0x14 / 4];
    int idx = cmd_list[1];
    int *slot;
    int count, i, x;
    char *p = a3;
    cmd_list[1] = idx + 1;
    slot = (int *)((char *)((int *)cmd_state[0xC / 4])[0] + idx * 8);
    slot[0] = 0xBB000001;
    slot[1] = 0x80008000;
    count = gl_func_00000000(a3);
    if (count == 0) return;
    x = (int)a1;
    for (i = 0; i < count; i++) {
        char c = *p;
        if (c != ' ') {
            int g = gl_func_00000000((int)c);
            int *glyph = (int *)((char *)a0[0x20 / 4] + g * 0x14);
            gl_func_00000000(a0[0x24 / 4], a0[0x4 / 4], a0[0x18 / 4], a0[0x1C / 4],
                             glyph[0], glyph[1], glyph[2], scale, 0);
            gl_func_00000000(a0[0x24 / 4], x + glyph[4], a2, glyph[2], scale,
                             (glyph[2] * 1024) / glyph[2], (scale * 1024) / scale);
            x += glyph[3];
        } else {
            x += ((int *)a0[0x20 / 4])[3];
        }
        p++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000D04);
#endif

/* gui_func_00000F04: 313-insn / 0x4E4 F3DEX2 glyph-STRING renderer.
 * 2026-06-05 FULL DECODE (was INCLUDE_ASM-only + prose). Disassembled the
 * raw .word USO body to mnemonics, fed m2c, then translated to compilable C.
 *
 * Iterates the string arg5 char-by-char (skip 0x20 space), and for each glyph
 * appends F3DEX2 commands to the DL buffer at ctx->0x24 (->0xC = {base=0x0,
 * count=0x4}; each cmd = 8 bytes at base + count*8, count post-incremented):
 *   - one G_RDPHALF-ish header pair (0xBB000001 / 0x80008000) before the loop
 *   - per glyph: a callee (gl_func placeholder) draws the glyph quad, then
 *     TEXRECT (0xE4......), G_RDPHALF_1 (0xB4......) with scaled S/T deltas,
 *     and TEXRECT_FLIP/half (0xB3......) with the DSDX/DTDY frac (sp7C).
 *   - var_f22 (pen X advance) accumulates each glyph's width (glyph->0xC),
 *     scaled by arg3; arg4 scales the Y/row, spD4 = -ctx->0x10/2 centers it.
 *   glyph table: ctx->0x20 base, entry = base + glyphIdx*0x14
 *   (glyphIdx = gl_func(ch)); entry->0x0/0x4 = tex coords, ->0x8 = width.
 *
 * NON_MATCHING: first-pass structural decode (313 FPU insns, multi-run).
 * All callees are the gl_func_00000000 cross-USO placeholder (raw objdump
 * lost the real reloc symbols + the exact arg signature / f12-f14 float-arg
 * order), and the s0-s7/f20-f30 regalloc + glyph-struct typing are not yet
 * pinned, so this is reference C, not a byte match.
 *
 * 2026-06-05 RESIDUAL (full target<->build disasm diff): LOGIC confirmed
 * correct (per-char loop, 4 DL appends, FP scale+clamp chains, both var_f22
 * arms line up). Gap is FRAME size + cascading regalloc renumber.
 *   - FIXED this pass: the m2c artifact `if (f10 & 0x20000000)` was really
 *     `if (s4 < 0)` (target gate is `bgez s4`); `f10=(int)f2` was held across
 *     the big glyph-draw call ONLY for that test, so correcting the gate let
 *     `f10` be inlined into `s4` → dropped one cross-call spill, frame
 *     0x130->0x128, 323->318 insns.
 *   - REMAINING: frame 0x128 vs target 0x108 (4 more spill words). Target
 *     fits its 9 cross-call-live values in $s0-$s8 (s2=ctx, s6=ctx->0x14,
 *     s7=cursor, s8=idx, s4=(int)f2*4, s3=(short)s4, s1=clamp, s5=f10b,
 *     s0=glyph-width) + spills only sp7C/spD3; build's expr structure makes
 *     IDO spill 4 extra. Cascading: build ctx=$s3 vs target $s2.
 *   - FIXED 2026-06-05 (pass 2): first call is gl_func(arg0,arg5) — target
 *     leaves a0=ctx from entry and loads a1=arg5 in the delay slot; m2c had
 *     gl_func(arg5,a3) (wrong). 523->519 diffs.
 *   - FIXED 2026-06-05 (pass 3): named-local `float two=2.0f` divisor forces
 *     `div.s` (not `mul *0.5`) and the target shares that one 2.0 across both
 *     divisions AND the `-2.0` sub — div.s now 5/5, 519->503 diffs, 316 insns.
 *     (IDO_CODEGEN#feedback-ido-div-2-mul-fold-and-mtc1-load-delay-nops.)
 *     COST: frame 0x128->0x130 — `two` is declared/used with the gl_func call
 *     INSIDE the divide expr, so 2.0 is live ACROSS that call (target
 *     materializes 2.0 AFTER the call, in $f0, dead before the loop). Net diffs
 *     still improved. Next: get `two`/2.0 to materialize post-call (splitting
 *     the call to an explicit `rw` temp REGRESSED earlier — needs care).
 *   - 2026-06-05 (pass 4): moved idx/s7 init AFTER the first call to match
 *     target order (523->501 diffs cumulative). Tried `rw` temp to push 2.0
 *     materialization post-call: REGRESSED to 519 — don't retry.
 *   - REGALLOC CAP (the last frame word): build caches arg5 in an in-frame
 *     slot (sp+0x118, written twice) instead of reloading from the stack-arg
 *     HOME slot each time like the target (frame 0x130 vs 0x108 = this 1 slot
 *     + the s2/s3 ctx renumber it cascades). IDO chooses to cache the
 *     stack-passed arg5 rather than re-`lw` from its home; no C lever found to
 *     force home-reload. Structure + FP (div.s 5/5) + arg/init order all now
 *     match; the residual is this IDO spill-vs-reload choice (permuter-class).
 *   - 2026-06-22 (agent-b): 69.97% -> 75.45% fuzzy via three correct-C levers:
 *     (1) CURSOR SPILL ELIMINATED: the two TEXRECT clamps used `wa3=0; if(..)`
 *         init-then-override; switching to symmetric `if(..)x;else x=0;` (like
 *         the target's other clamps) freed a saved reg so the cursor lives in
 *         $s7 instead of spilling to sp+0x118 — frame dropped one extra slot
 *         and insn count is now exact (313). (2) CURSOR/IDX REGISTER MATCH:
 *         swapping the `s7=arg5;`/`idx=0;` decl-init order flipped IDO to
 *         cursor=$s7, idx=$s8 (was idx=$s7, cursor=$s8) matching the target.
 *         (3) DL-WRITE RE-READ: the header append's base pointer is re-loaded
 *         from `a3->0xC` (write `**(char***)(a3+0xC)`), not the cached `dl`;
 *         this matched the target's exact pre-loop DL-build schedule (insns
 *         0-57 now identical bar reg-renumber). NB: applying the same re-read
 *         to the 3 LOOP appends REGRESSED (the loop already caches dl for
 *         cnt+write, so re-reading double-loads) — header only.
 *   - REMAINING (permuter/coloring-class, no C lever found): frame still 0x130
 *     vs 0x108 (+40 = IDO places the 3 spills sp7C/spD3/spD4 high w/ small top
 *     reservation; target places them low w/ a 0x34 top hole — same spill COUNT,
 *     different layout); one duplicated `multu` in the cmd3[1] f10b clamp (IDO
 *     tail-duplicates it into both inner branches, target keeps it single — a
 *     short-cast temp did NOT defeat it); `beql` vs `beq` on the space-skip
 *     test; and the resulting recompute(sll/sra)-vs-reload(lw/move) opcode
 *     skew. Opcode multiset differs by these few; logic is byte-correct. */
#ifdef NON_MATCHING
extern int gl_func_00000000();
void gui_func_00000F04(void *arg0, int arg1, int arg2, float arg3, float arg4, unsigned char *arg5) {
    float spD4;
    unsigned char spD3;
    int sp7C;
    float var_f22;
    int s6;
    unsigned char *s7;
    unsigned int idx;
    int *a3;
    int *dl;
    int cnt;
    int *cmd;

    a3 = *(int**)((char*)arg0 + 0x24);
    s6 = *(int*)((char*)arg0 + 0x14);
    dl = *(int**)((char*)a3 + 0xC);
    cnt = dl[1];
    dl[1] = cnt + 1;
    cmd = (int*)(**(char***)((char*)a3 + 0xC) + cnt * 8);
    cmd[0] = 0xBB000001;
    cmd[1] = 0x80008000;
    {
        /* named-local divisor forces div.s (not mul*0.5); target shares this
         * one 2.0 across both divisions AND the -2.0 sub (IDO_CODEGEN
         * #feedback-ido-div-2-mul-fold-and-mtc1-load-delay-nops). */
        float two = 2.0f;
        var_f22 = -((float)gl_func_00000000(arg0, arg5) / two) - two;
        spD4 = -((float)*(int*)((char*)arg0 + 0x10) / two);
    }
    s7 = arg5;
    idx = 0;
    if (gl_func_00000000(arg5) != 0) {
        do {
            unsigned char ch = *s7;
            if (ch != 0x20) {
                float f0 = (float)s6 * arg4;
                float f2 = (float)arg2 + (spD4 * arg4);
                short s4 = (int)f2 * 4;
                short s1 = ((int)f2 + (int)f0) * 4;
                int f10b = (int)(((float)(s6 - 1) * 1024.0f) / f0);
                int *glyph;
                int s0;
                float f0b;
                int f8;
                short ca0, ca1;
                short xa3, xa0b;
                int wa3, wa0;
                int cnt2, cnt3, cnt4;
                int *cmd2, *cmd3, *cmd4;
                int a2v, a1v, a3v;

                sp7C = f10b & 0xFFFF;
                spD3 = (unsigned char)gl_func_00000000(ch);
                glyph = (int*)(*(int*)((char*)arg0 + 0x20) + (int)spD3 * 0x14);
                s0 = glyph[2];
                gl_func_00000000(*(int*)((char*)arg0 + 0x24), *(int*)((char*)arg0 + 0x4),
                                 *(int*)((char*)arg0 + 0x18), *(int*)((char*)arg0 + 0x1C),
                                 glyph[0], glyph[1], s0, s6, 0);
                a3 = *(int**)((char*)arg0 + 0x24);
                dl = *(int**)((char*)a3 + 0xC);
                cnt2 = dl[1];
                f0b = (float)s0 * arg3;
                dl[1] = cnt2 + 1;
                f8 = (int)((float)arg1 + (var_f22 * arg3));
                cmd2 = (int*)(*(char**)dl + cnt2 * 8);
                ca0 = (f8 + (int)f0b) * 4;
                ca1 = f8 * 4;
                if (ca0 > 0) wa3 = ca0; else wa3 = 0;
                if (s1 > 0) wa0 = s1; else wa0 = 0;
                cmd2[0] = ((wa3 & 0xFFF) << 0xC) | 0xE4000000 | (wa0 & 0xFFF);
                if (ca1 > 0) xa3 = ca1; else xa3 = 0;
                if (s4 > 0) xa0b = s4; else xa0b = 0;
                cmd2[1] = ((xa3 & 0xFFF) << 0xC) | (xa0b & 0xFFF);
                a3 = *(int**)((char*)arg0 + 0x24);
                dl = *(int**)((char*)a3 + 0xC);
                cnt3 = dl[1];
                dl[1] = cnt3 + 1;
                cmd3 = (int*)(*(char**)dl + cnt3 * 8);
                cmd3[0] = 0xB4000000;
                if (ca1 < 0) {
                    a2v = (int)(((float)(s0 - 1) * 1024.0f) / f0b);
                    if ((short)a2v < 0) {
                        int t = (int)(ca1 * (short)a2v) >> 7;
                        if (t > 0) a3v = t; else a3v = 0;
                    } else {
                        int v = 0;
                        int t = (int)(ca1 * (short)a2v) >> 7;
                        if (t < 0) v = t;
                        a3v = v;
                    }
                } else {
                    a3v = 0;
                    a2v = (int)(((float)(s0 - 1) * 1024.0f) / f0b);
                }
                if (s4 < 0) {
                    int t = (int)(s4 * (short)f10b) >> 7;
                    if ((short)f10b < 0) {
                        if (t > 0) a1v = t; else a1v = 0;
                    } else {
                        int v = 0;
                        if (t < 0) v = t;
                        a1v = v;
                    }
                } else {
                    a1v = 0;
                }
                cmd3[1] = (a3v * -0x10000) | (-a1v & 0xFFFF);
                a3 = *(int**)((char*)arg0 + 0x24);
                dl = *(int**)((char*)a3 + 0xC);
                cnt4 = dl[1];
                dl[1] = cnt4 + 1;
                cmd4 = (int*)(*(char**)dl + cnt4 * 8);
                cmd4[0] = 0xB3000000;
                cmd4[1] = (a2v << 0x10) | sp7C;
                var_f22 += (float)*(int*)((char*)(*(int*)((char*)arg0 + 0x20) + (int)spD3 * 0x14) + 0xC);
            } else {
                var_f22 += (float)*(int*)((char*)*(int**)((char*)arg0 + 0x20) + 0xC);
            }
            s7 += 1;
            idx += 1;
        } while (idx < (unsigned int)gl_func_00000000(arg5));
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000F04);
#endif

/* Text-width accumulator with glyph-table lookup.
 *   a0 = font-info struct: +0x08 = space-width, +0x20 = glyph-table ptr
 *   a1 = string
 * For each char up to gl_func_00000000(a1) length:
 *   if ' ': total += a0[2] (space-width at +0x8)
 *   else:   key = gl_func_00000000(c);
 *           total += *(int*)(glyph_table + key*20 + 8)  (stride 20). */
int gui_func_000013E8(char *a0, unsigned char *a1) {
    int total = 0;
    unsigned char *p = a1;
    unsigned int i = 0;
    unsigned char c;
    int key;

    if (gl_func_00000000(a1) != 0) {
        do {
            c = *p;
            if (c != 0x20) {
                key = gl_func_00000000(c);
                total += *(int*)(*(char**)(a0 + 0x20) + key * 20 + 8);
            } else {
                total += *(int*)(a0 + 0x8);
            }
            p++;
            i++;
        } while (i < gl_func_00000000(a1));
    }
    return total;
}

extern int gui_func_00000000();

int gui_func_000014B4(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

extern int gl_func_00000000();

int gui_func_000014EC(int a0, int a1, int a2) {
    return a1 - gl_func_00000000(a0, a2);
}

extern int gl_func_00000000();
int gui_func_00001514(int *a0, unsigned char *a1) {
    int total = 0;
    unsigned char *p = a1;
    unsigned int i = 0;

    if (gl_func_00000000(a1) != 0) {
        do {
            if (*p != 0x20) {
                total += a0[3];
            } else {
                total += a0[2];
            }
            p++;
            i++;
        } while (i < (unsigned int)gl_func_00000000(a1));
    }
    return total;
}

extern int gui_func_00000000();

int gui_func_000015BC(int a0, int a1, int a2) {
    return a1 - (gui_func_00000000(a0, a2) / 2);
}

int gui_func_000015F4(int a0, int a1, int a2) {
    return a1 - gl_func_00000000(a0, a2);
}

/* gui_func_0000161C: shift-all-table-entries-by-delta (advance/kerning
 * adjust): for each of *a0 entries (0x14 stride, base at a0->0x20), add the
 * delta to entry->0xC; then a0->0xC += delta. Split off from the original
 * 4.1 KB splat bundle in a prior tick (the dispatch body lives in the
 * following symbols). MATCHED 2026-06-09 via three levers: (1) declare a
 * third parameter and `a2 = a1` -- IDO homes the copy in $a2 exactly like
 * the target's `or a2,a1` (the fn is 2-arg at call sites; K&R-compatible);
 * (2) reuse a1 as the byte-offset IV, i declared first (wins $v0);
 * (3) write the update as bump-then-RMW (`v1 = v1+0xC; *v1 = *v1 + a2;`)
 * -- the load becomes an expression temp ($t8 pool, not a named-local $a3)
 * and IDO schedules it BEFORE the addiu with the 0xC offset folded. */
void gui_func_0000161C(int *a0, int a1, int a2) {
    int i;
    a2 = a1;
    a1 = 0;
    i = 0;
    if (*a0 > 0) {
        do {
            int *v1 = (int *)((char *)a0[0x20 / 4] + a1);
            v1 = (int *)((char *)v1 + 0xC);
            a1 += 0x14;
            i++;
            *v1 = *v1 + a2;
        } while (i < *a0);
    }
    a0[0xC / 4] = a0[0xC / 4] + a2;
}

/* 0x1670 is a single alignment nop between gui_func_0000161C and the real
 * function at 0x1674 — splat mis-placed the gui_uso_func_00001670 symbol on the
 * pad (and over-split the loop tail into 0000168C). The nop is emitted via
 * all-zero SUFFIX_BYTES_FORCE on gui_func_0000161C in the Makefile — a 1-word
 * GLOBAL_ASM pad block emits 2 words (+4 segment length drift, the documented
 * trap). The true function is gui_uso_func_00001674 below. */

/* gui_uso_func_00001674: highest-set-bit / mask-down scan. Returns the largest
 * power-of-two <= a0 (walking 0x8000 down), or 1 if a0 < 1. Merged from the
 * mis-split 00001670 body + 0000168C loop tail. */
int gui_uso_func_00001674(int a0) {
    int v1 = 0x8000;
    do {
        if (!(a0 < v1)) {
            return v1;
        }
        v1 >>= 1;
    } while (v1 != 0);
    return 1;
}

#ifdef NON_MATCHING
/* Full decode 2026-06-01. Display-list emitter: appends 4 fixed GBI
 * commands (RDPPIPESYNC, two SETOTHERMODE_H, a B9/SETOTHERMODE_L) to the
 * gfx builder reached via *(D+0x254)->0x158, caching it at &D for each
 * append. */
extern char D_gui16a4_cache;
extern char D_gui16a4_c1;
extern char D_gui16a4_c2;
extern char D_gui16a4_c3;
void gui_uso_func_000016A4(int a0) {
    char *b;
    char *p;
    char *buf;
    int i;
    (void)a0;

    b = *(char **)(*(char **)((char *)&D_00000000 + 0x254) + 0x158);
    *(char **)&D_gui16a4_cache = b;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xE7000000;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)&D_gui16a4_c1;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xBA001402;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)&D_gui16a4_c2;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xBA001301;
    *(int *)(buf + i * 8 + 4) = 0;

    b = *(char **)&D_gui16a4_c3;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xB900031D;
    *(int *)(buf + i * 8 + 4) = 0x00404240;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000016A4);
#endif

/* MATCHED 2026-05-31 via decomp-permuter (the prior "permanent NM constant-
 * materialization scheduling-order cap" was WRONG — it was cracked, not by
 * manual C swaps, but by the permuter: putting the two arr[] stores on a SINGLE
 * source line shifts IDO's lui/ori scheduling to interleave t1's ori before
 * t0's, matching the target. Byte-exact. Lesson: 2-diff load/schedule-ORDER
 * residuals are permuter-crackable even when manual statement-reorder fails. */
void gui_uso_func_00001794(int a0) {
    int *rec = *(int **)&D_00000000;
    int *sub = (int *)rec[3];
    int count = sub[1];
    int *arr;
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFCFFFFFF; arr[1] = 0xFFFCF279;
}

/* Display-list color-command builder (sibling of gui_uso_func_00001794 /
 * _00003B14 — same 8-byte-entry/increment-counter template, here repeated 3x).
 * Entry 1: fixed 0xFC309A61 / 0xFF37FFFF. Entry 2: 0xFB000000 / (a1 & 0xFF).
 * Entry 3: 0xFA000000 / packed RGBA, where R/G/B = float*255 -> byte and the
 * low byte is the alpha arg. 88.4% (objdiff). Logic + FP idiom both correct;
 * the (unsigned) cast (NOT (int)) is the key: it emits IDO's FULL cvt.w.s +
 * cfc1/ctc1/andi-0x78/sub.s-2^31 overflow-correction dance (the target form),
 * whereas (int) emits a single trunc.w.s. See docs/IDO_CODEGEN.md. Residual is
 * the register-allocation cascade: target dead-homes a0 at 0(sp) and keeps the
 * alpha arg live in $7.
 * 2026-06-05: FIXED the +2 alpha-spill by inlining the 3 color conversions
 * into ONE accumulating OR expression (col0<<24 | col1<<16 | col2<<8 | alpha)
 * instead of 3 simultaneously-live r0/r1/r2 locals — that dropped peak
 * register pressure so $7(alpha) no longer spills. insns 162->160 (now ==
 * target), 198->182 diffs. Applied to the sibling color-emit fn too. REMAINING
 * 12 opcode diffs are the per-channel cvt/andi/sll SCHEDULING order in the
 * combine; the rest is $t-renumber across the 3 DL-appends. Permuter -j4 220s/
 * 44k iters best score ~1800 (NOT 0) — did NOT crack it; the score is high
 * because the $t-renumber + combine-scheduling compound across the 3 record-
 * appends. Don't re-run the permuter. INCLUDE_ASM stays the build path. */
#ifdef NON_MATCHING
void gui_uso_func_000017DC(int a0, int a1, float *col, int alpha) {
  int *new_var;
  int *rec = *((int **) (&D_00000000));
  int new_var2;
  int *sub;
  int count;
  int *arr;
  sub = (int *) rec[3];
  count = sub[1];
  sub[1] = count + 1;
  new_var = (int *) (((int *) rec[3])[0] + (count * 8));
 arr = new_var; arr[0] = 0xFC309A61; arr[1] = 0xFF37FFFF; rec = *((int **) (&D_00000000)); sub = (int *) rec[3]; new_var2 = sub[1]; count = new_var2; sub[1] = count + 1; arr = (int *) (((int *) rec[3])[0] + (count * 8)); arr[0] = 0xFB000000; arr[1] = a1 & 0xFF; rec = *((int **) (&D_00000000)); sub = (int *) rec[3];
  count = sub[1];
  sub[1] = count + 1;
  arr = (int *) (((int *) rec[3])[0] + (count * 8));
  arr[0] = 0xFA000000;
  arr[1] = (((((int) ((unsigned) (col[0] * 255.0f))) << 24) | (((((int) ((unsigned) (col[1] * 255.0f))) & 0xFF) << 3) << 13)) | ((((unsigned) (col[2] * 255.0f)) & 0xFF) << 8)) | (alpha & 0xFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000017DC);
#endif

#ifdef NON_MATCHING
/* Full decode 2026-06-01. DL emitter: appends a SETCOMBINE (FC309661/
 * FF2FFFFF) then a SETPRIMCOLOR (FA) packing the a2 Vec3*255 (RGB) + a1
 * alpha into word1, to the gfx builder at *(&D). Uses the b->0xC re-read
 * and (int)(unsigned) float->byte dance. */
void gui_uso_func_00001A5C(char *a0, int a1, float *a2) {
    char *b;
    char *p;
    char *buf;
    int i;
    int r, g, bl;
    (void)a0;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFC309661;
    *(int *)(buf + i * 8 + 4) = 0xFF2FFFFF;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFA000000;
    r = (int)(unsigned)(a2[0] * 255.0f);
    g = (int)(unsigned)(a2[1] * 255.0f);
    bl = (int)(unsigned)(a2[2] * 255.0f);
    *(int *)(buf + i * 8 + 4) =
        (r << 24) | ((g & 0xff) << 16) | ((bl & 0xff) << 8) | (a1 & 0xff);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00001A5C);
#endif

#ifdef NON_MATCHING
/* Full decode 2026-06-01. Sibling of gui_uso_func_00001A5C: appends a
 * SETCOMBINE (FCFFFFFF/FFFDF6FB) then a SETPRIMCOLOR (FA) packing the a2
 * Vec3*255 (RGB) + a1 alpha into word1, to the builder at *(&D). */
void gui_uso_func_00001CA8(char *a0, int a1, float *a2) {
    char *b;
    char *p;
    char *buf;
    int i;
    int r, g, bl;
    (void)a0;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFCFFFFFF;
    *(int *)(buf + i * 8 + 4) = 0xFFFDF6FB;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFA000000;
    r = (int)(unsigned)(a2[0] * 255.0f);
    g = (int)(unsigned)(a2[1] * 255.0f);
    bl = (int)(unsigned)(a2[2] * 255.0f);
    *(int *)(buf + i * 8 + 4) =
        (r << 24) | ((g & 0xff) << 16) | ((bl & 0xff) << 8) | (a1 & 0xff);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00001CA8);
#endif

#ifdef NON_MATCHING
/* Full decode 2026-06-01. DL emitter: SETCOMBINE (FC309A61/5536FF7F), then
 * an FB command packing a3 Vec3*255 + a1 alpha, then an FA (SETPRIMCOLOR)
 * packing a2 Vec3*255 + a1 alpha, to the builder at *(&D). Same b->0xC
 * re-read + (int)(unsigned) levers as gui_uso_func_00001A5C. */
void gui_uso_func_00001EF4(char *a0, int a1, float *a2, float *a3) {
    char *b;
    char *p;
    char *buf;
    int i;
    int r, g, bl;
    (void)a0;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFC309A61;
    *(int *)(buf + i * 8 + 4) = 0x5536FF7F;

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFB000000;
    r = (int)(unsigned)(a3[0] * 255.0f);
    g = (int)(unsigned)(a3[1] * 255.0f);
    bl = (int)(unsigned)(a3[2] * 255.0f);
    *(int *)(buf + i * 8 + 4) =
        (r << 24) | ((g & 0xff) << 16) | ((bl & 0xff) << 8) | (a1 & 0xff);

    b = *(char **)&D_00000000;
    p = *(char **)(b + 0xC);
    i = *(int *)(p + 4);
    *(int *)(p + 4) = i + 1;
    buf = *(char **)(*(char **)(b + 0xC));
    *(int *)(buf + i * 8) = 0xFA000000;
    r = (int)(unsigned)(a2[0] * 255.0f);
    g = (int)(unsigned)(a2[1] * 255.0f);
    bl = (int)(unsigned)(a2[2] * 255.0f);
    *(int *)(buf + i * 8 + 4) =
        (r << 24) | ((g & 0xff) << 16) | ((bl & 0xff) << 8) | (a1 & 0xff);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00001EF4);
#endif

/* SOURCE=2 sibling of gui_uso_func_000025B4 / gui_uso_func_000017DC:
 * three display-list command writes. Entry 1 sets the combiner
 * (0xFC11EA23/0xFFD7FFFF), entry 2 writes primitive alpha from a1, and entry 3
 * packs RGB from float*255 plus the a3 alpha byte. Address-taken K&R a0 keeps
 * the target's caller-slot spill shape. First NM body verifies at 84.46%;
 * `register alpha` was a no-op (IDO still spills a3 to 12(sp)), so the
 * remaining gap mirrors gui_uso_func_000017DC's alpha-live regalloc cascade. */
#ifdef NON_MATCHING
void gui_uso_func_00002334(a0, a1, col, alpha)
    int a0;
    int a1;
    float *col;
    int alpha;
{
  int *rec = *((int **) (&D_00000000));
  int new_var;
  int *sub;
  int new_var3;
  int count;
  int *arr;
  int r0;
  int r1;
  int new_var2;
  int r2;
  new_var2 = rec[3];
  (void) (&a0);
  sub = (int *) new_var2;
  count = sub[1];
  sub[1] = count + 1;
  arr = (int *) (((int *) rec[3])[0] + (count * 8));
  arr[0] = 0xFC11EA23;
  arr[1] = 0xFFD7FFFF;
  rec = *((int **) (&D_00000000));
  sub = (int *) rec[3];
  count = sub[1];
  new_var3 = count;
  sub[1] = new_var3 + 1;
  new_var = ((int *) rec[3])[0] + (count * 8);
  arr = (int *) new_var;
  ((int *) new_var)[0] = 0xFB000000;
  arr[1] = a1 & 0xFF;
 do { } while (0);
  rec = *((int **) (&D_00000000));
  sub = (int *) rec[3];
  count = sub[1];
  sub[1] = count + 1;
  arr = (int *) (((int *) rec[3])[0] + (count * 8));
  arr[0] = 0xFA000000;
  arr[1] = (((((int) ((unsigned) (col[0] * 255.0f))) << 24) | ((((int) ((unsigned) (col[1] * 255.0f))) & 0xFF) << 16)) | ((((unsigned) (col[2] * 255.0f)) & 0xFF) << 8)) | (alpha & 0xFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00002334);
#endif

/* SOURCE=4 decode (2026-06-01): display-list rectangle command writer.
 * Uses the global GUI context at D[0] -> ctx, appends one 2-word command at
 * ctx->dl[ctx->cursor++] and packs x/y coordinates as 12-bit fixed-point
 * values after multiplying by 4. The target stores a0 into its caller arg slot
 * and reads the fifth arg from sp+0x10; the address-taken K&R arg keeps that
 * shape in the NM body. */
void gui_uso_func_000025B4(a0, x0, y0, x1, y1)
    int a0;
    int x0;
    int y0;
    int x1;
    int y1;
{
    int *global = *(int **)&D_00000000;
    int *ctx = *(int **)((char *)global + 0xC);
    int cursor = *(int *)((char *)ctx + 4);
    int *dst;
    int sx0;
    int sy0;
    int sx1;
    int sy1;

    (void)&a0;
    *(int *)((char *)ctx + 4) = cursor + 1;
    dst = (int *)(*(int *)((char *)*(int **)((char *)global + 0xC) + 0) + (cursor << 3));

    sx0 = (int)((float)x0 * 4.0f) & 0xFFF;
    sy0 = (int)((float)y0 * 4.0f) & 0xFFF;
    sx1 = (int)((float)x1 * 4.0f) & 0xFFF;
    sy1 = (int)((float)y1 * 4.0f) & 0xFFF;

    dst[0] = 0xED000000 | (sx0 << 12) | sy0;
    dst[1] = (sx1 << 12) | sy1;
}

extern int gl_func_00000000();
extern char D_00000000;

void gui_func_0000267C(char *a0, int a1) {
    int saved;
    *(int*)(a0 + 0x14) = a1;
    saved = gl_func_00000000(7);
    *(int*)(a0 + 0x10) = gl_func_00000000((*(int *)((char *)&D_00000000 + 0x150)), *(int*)(a0 + 0x14));
    gl_func_00000000(saved);
}

void gui_func_000026CC(int *a0, int a1) {
    a0[5] = a1;
    a0[4] = 0;
}

extern int gui_func_00000000();
extern char D_00000000;

void gui_func_000026D8(char *a0) {
    if (*(int*)(a0 + 0x10) != 0) {
        gui_func_00000000((*(int *)((char *)&D_00000000 + 0x150)), *(int*)(a0 + 0x14), a0);
    }
    *(int*)(a0 + 0x10) = 0;
}

extern int gl_func_00000000();
void gui_func_0000271C(char *a0) {
    int saved;
    int v0;
    int v1;
    if (*(int*)(a0 + 0x14) == -1) {
        *(int*)(a0 + 0x14) = 0;
    }
    saved = gl_func_00000000(7);
    v0 = gl_func_00000000((*(int *)((char *)&D_00000000 + 0x150)), *(int*)(a0 + 0x14));
    v1 = *(int*)(a0 + 0x10);
    if (v1 == 0 || v0 != v1) {
        *(int*)(a0 + 0x10) = gl_func_00000000((*(int *)((char *)&D_00000000 + 0x150)), *(int*)(a0 + 0x14));
    }
    gl_func_00000000(saved);
}

#ifdef NON_MATCHING
/* gui_func_000027A0: 260-insn / 0x410 tiled-texture / glyph blitter.
 * FULL-BODY reconstruction (2026-06-22). Structure matches target end-to-end
 * (~81% mnemonic); residual is register-coloring + a 1-insn prologue schedule
 * (a2-home spill vs move-s8) + 3-insn count gap from IDO's distinct coloring
 * of the held info/budget pointers. Logic is exact.
 *
 * Args: (a0=widget, a1=x, a2=y, a3=flags). info = a0->field_10.
 *
 * 1. Flag-driven origin adjustment (signed div-by-2 = bgez/sra/addiu+1/sra):
 *      if (flags & 4)  x  -= (s16)info[0x20];          // full width
 *      else if (flags & 1) x -= (s16)info[0x20] / 2;   // half width
 *      if (flags & 2)  y  -= (s16)info[0x22] / 2;       // half height
 * 2. Emit RDP setothermode word pair (0xBB000001 / 0x80008000) into the
 *    current DL (gctx[3]), bumping the DL index.
 * 3. Mode dispatch (info[0x24]) selects a texel budget + per-mode tile fn:
 *      1032 -> 4096, fn1032 ; 272 -> 2048, fn272 ;
 *      288  -> 1024, fn288  ; default -> 2048, fndef.
 * 4. If budget >= w*h: single blit (load whole sprite, one tile+draw).
 *    Else: tile horizontally in columns of width (gl_func(budget/h)),
 *    looping render+draw per column, advancing x and the source x-offset,
 *    until the remaining width is consumed.
 *
 * Frame 0x78: ra@0x54, s8@0x50, s7..s0@0x4C..0x30, mode-fn@0x5c,
 * held-widget spill@0x78, a2(y) home@0x80.
 *
 * Default build uses INCLUDE_ASM via #else; ROM stays exact. */
extern int D_27A0_fn1032, D_27A0_fn272, D_27A0_fn288, D_27A0_fndef;
void gui_func_000027A0(int *a0, int a1, int a2, int a3) {
    int *info;
    int s8 = a1;
    int budget;
    int w, h;
    int s6;
    int (*render_fn)();
    int *gctx;
    int *dl;
    int idx;

    if (a3 & 4) {
        info = (int *)a0[0x10 / 4];
        s8 -= *(short *)((char *)info + 0x20);
    } else if (a3 & 1) {
        s8 -= (*(short *)((char *)(int *)a0[0x10 / 4] + 0x20)) / 2;
    }
    if (a3 & 2) {
        a2 -= (*(short *)((char *)(int *)a0[0x10 / 4] + 0x22)) / 2;
    }

    gctx = *(int **)&D_00000000;
    dl = (int *)gctx[0xC / 4];
    idx = dl[1];
    dl[1] = idx + 1;
    {
        int *slot = (int *)(((int *)gctx[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xBB000001;
        slot[1] = (int)0x80008000;
    }

    s6 = 0;
    info = (int *)a0[0x10 / 4];
    budget = 2048;
    switch (info[0x24 / 4]) {
    case 1032: budget = 4096; render_fn = (int (*)())&D_27A0_fn1032; break;
    case 272:  render_fn = (int (*)())&D_27A0_fn272;  break;
    case 288:  budget = 1024; render_fn = (int (*)())&D_27A0_fn288;  break;
    default:   render_fn = (int (*)())&D_27A0_fndef;  break;
    }
    w = *(short *)((char *)info + 0x20);
    h = *(short *)((char *)info + 0x22);

    if (budget < w * h) {
        int tile = gl_func_00000000(budget / h);
        int s0 = w;
        int s4 = (h << 10) / h;
        if (w != 0) {
            do {
                if (tile < s0) {
                    int s3 = (tile << 10) / tile;
                    render_fn(*(int **)&D_00000000, ((int *)a0[0x10 / 4])[8 / 4], w, h, s6, 0, tile, h, 0);
                    gl_func_00000000(*(int **)&D_00000000, s8, a2, tile, h, s3, s4);
                    s8 += tile;
                    s6 += tile;
                    s0 -= tile;
                } else {
                    int t0 = (s0 << 10) / s0;
                    render_fn(*(int **)&D_00000000, ((int *)a0[0x10 / 4])[8 / 4], w, h, s6, 0, s0, h, 0);
                    gl_func_00000000(*(int **)&D_00000000, s8, a2, s0, h, t0, s4);
                    s0 -= tile;
                }
            } while (s0 != 0);
        }
    } else {
        render_fn(*(int **)&D_00000000, info[8 / 4], w, h, 0, 0, w, h, 0);
        gl_func_00000000(*(int **)&D_00000000, s8, a2, w, h, (w << 10) / w, (h << 10) / h);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000027A0);
#endif

#ifdef NON_MATCHING
/* gui_func_00002BB0: 140-insn / 0x230 RDP/RSP display-list builder.
 * Constructs graphics commands into a display-list buffer at *(D_xxx)[0]
 * - likely setting up scissor/viewport/texture for a GUI quad.
 *
 * ENTRY DECODE (0x2BB0-0x2C30, ~32 insns):
 *   ctx = *(int**)&D_GUI_CTX;        // s7 = &D_xxx; s2 = ctx (s7[0])
 *   ctx[12]->[4] += 1;               // bump display-list counter
 *   v1_old = pre-bump value
 *   t2 = 0x80008000                  // RDRAM segment-0 base marker
 *   t9 = v1_old << 3                 // 8-byte stride per RDP command
 *   t8 = ctx[12][0]                  // display-list base ptr
 *   t0 = t8 + t9                     // dl_ptr = base + index*8
 *   s5 = a1 (saved arg);  s4 = a3 (saved arg)
 *   s6 = sp[128] (5th stack arg)
 *   sp[120] = a2 (caller arg-spill)
 *   ... (continues writing RDP commands at dl_ptr; opcode 0xBB00_0001
 *        observed = G_SETSCISSOR or similar; full sequence ~100 more
 *        insns of dl_ptr[N] = (cmd<<24) | data assignments)
 *
 * 9 saved regs (s0-s7, s8) + ra in 0x70 frame. 5+ args (a0-a3 + at least
 * one stack arg via sp+0x80 = caller-arg slot 5).
 *
 * 100+ insns of body deferred - multi-pass NM. Default build INCLUDE_ASM. */
/* 2026-05-08: entry-stage decode (insns 0-32 / 0x00-0x80). Replaces
 * empty stub with the documented 5-arg signature + first DL command
 * emit (RDP 0xBB000001 opcode at slot 0).
 *
 * Frame -0x70 (saves s0-s7, s8 + ra). 5th arg `a4_stack` arrives via
 * sp[0x80] (caller arg-save slot 5). a2 spilled to sp+0x78. */
void gui_func_00002BB0(int *a0, int a1, int a2, int a3, int a4) {
    int **s7 = (int **)&D_00000000;
    int *ctx = *s7;
    int s5 = a1, s4 = a3, s1 = a4;
    int field58, s0, s8;
    int *v1, *tex;
    /* first DL emit: G_SETSCISSOR (BB000001 / 80008000) */
    {
        int *v0 = (int *)ctx[0xC / 4];
        int idx = v0[1];
        v0[1] = idx + 1;
        {
            int *slot = (int *)(((int *)ctx[0xC / 4])[0]) + idx * 2;
            slot[0] = 0xBB000001;
            slot[1] = (int)0x80008000;
        }
    }
    {
        int *s2 = (int *)a0[0x10 / 4];
        field58 = *(short *)((char *)s2 + 0x20);
        if (a4 == 0) return;
        s0 = *(short *)((char *)s2 + 0x22);
    }
    s8 = (s0 << 10) / s0;
    do {
        v1 = (int *)a0[0x10 / 4];
        if (s1 >= 33) {
            int s6 = (32 << 10) / 32;
            tex = (int *)v1[8 / 4];
            gl_func_00000000((*s7), tex, field58, s0, s4, 0, 32, s0, 0);
            gl_func_00000000((*s7), s5, a2, 32, s0, s6, s8);
            s5 += 32;
            s4 += 32;
            s1 -= 32;
        } else {
            int s3div;
            tex = (int *)v1[8 / 4];
            gl_func_00000000((*s7), tex, field58, s0, s4, 0, s1, s0, 0);
            s3div = (s1 << 10) / s1;
            gl_func_00000000((*s7), s5, a2, s1, s0, s3div, s8);
            s1 = 0;
        }
    } while (s1 != 0);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002BB0);
#endif

#ifdef NON_MATCHING
void gui_func_00002DE0(char *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    char *g = (char *)&D_00000000;
    char *gctx;
    char *dl;
    char *slot;
    s32 idx;
    s32 sp3C;
    s32 sp38;
    char *t0;
    s32 mode;
    f32 fW;
    f32 fH;
    f32 wScaled;
    f32 hScaled;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s32 ulx;
    s32 uly;
    s32 lrx;
    s32 lry;
    s32 dsdx;
    s32 dtdy;
    s32 tmp;

    gctx = (*(char **)g);
    dl = (*(char **)(gctx + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(gctx + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x0)) = 0xBB000001;
    (*(s32 *)(slot + 0x4)) = 0x80008000;

    t0 = (*(char **)(arg0 + 0x10));
    sp3C = (*(s16 *)(t0 + 0x20));
    sp38 = (*(s16 *)(t0 + 0x22));
    mode = (*(s32 *)(t0 + 0x24));
    switch (mode) {
    case 0x408:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        gctx = (*(char **)g);
        break;
    case 0x120:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        gctx = (*(char **)g);
        break;
    case 0x110:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        gctx = (*(char **)g);
        break;
    }

    dl = (*(char **)(gctx + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    fW = (f32) sp3C;
    y0 = 0;
    x0 = 0;
    slot = (char *)((*(s32 *)((*(char **)(gctx + 0xC)) + 0x0)) + idx * 8);
    ulx = (s32) ((f32) arg1 + (-(fW / 2.0f) * arg3));
    wScaled = fW * arg3;
    fH = (f32) sp38;
    if ((s16) ((ulx + (s32) wScaled) * 4) > 0) {
        x0 = (ulx + (s32) wScaled) * 4;
    }
    hScaled = fH * arg4;
    x1 = 0;
    lrx = ulx * 4;
    uly = (s32) ((f32) arg2 + (-(fH / 2.0f) * arg4));
    if ((s16) ((uly + (s32) hScaled) * 4) > 0) {
        y0 = (uly + (s32) hScaled) * 4;
    }
    lry = uly * 4;
    (*(s32 *)(slot + 0x0)) = (s32) (((x0 & 0xFFF) << 0xC) | 0xE4000000 | (y0 & 0xFFF));
    if (lrx > 0) {
        x1 = lrx;
    }
    if (lry > 0) {
        y1 = lry;
    } else {
        y1 = 0;
    }
    (*(s32 *)(slot + 0x4)) = (s32) (((x1 & 0xFFF) << 0xC) | (y1 & 0xFFF));

    gctx = (*(char **)g);
    dl = (*(char **)(gctx + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(gctx + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x0)) = 0xB4000000;
    if (lrx < 0) {
        dsdx = (s32) (((f32) (sp3C - 1) * 1024.0f) / wScaled);
        if ((s16) dsdx < 0) {
            tmp = (s32) (lrx * (s16) dsdx) >> 7;
            if (tmp > 0) {
                ulx = tmp;
            } else {
                ulx = 0;
            }
        } else {
            uly = 0;
            tmp = (s32) (lrx * (s16) dsdx) >> 7;
            if (tmp < 0) {
                uly = tmp;
            }
            ulx = uly;
        }
    } else {
        ulx = 0;
        dsdx = (s32) (((f32) (sp3C - 1) * 1024.0f) / wScaled);
    }
    if (lry < 0) {
        dtdy = (s32) (((f32) (sp38 - 1) * 1024.0f) / hScaled);
        if ((s16) dtdy < 0) {
            lrx = 0;
            tmp = (s32) (lry * (s16) dtdy) >> 7;
            if (tmp > 0) {
                lrx = tmp;
            }
        } else {
            uly = 0;
            tmp = (s32) (lry * (s16) dtdy) >> 7;
            if (tmp < 0) {
                uly = tmp;
            }
            lrx = uly;
        }
    } else {
        lrx = 0;
        dtdy = (s32) (((f32) (sp38 - 1) * 1024.0f) / hScaled);
    }
    (*(s32 *)(slot + 0x4)) = (s32) ((ulx * -0x10000) | (-lrx & 0xFFFF));

    gctx = (*(char **)g);
    dl = (*(char **)(gctx + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(gctx + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x4)) = (s32) ((dsdx << 0x10) | (dtdy & 0xFFFF));
    (*(s32 *)(slot + 0x0)) = 0xB3000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002DE0);
#endif

#ifdef NON_MATCHING
/* gui_func_0000329C: int-arg sibling of gui_func_00002DE0 (same RDP scissor +
 * texrect-scale DL builder; double-deref base = *(int*)g, cursor = base[0xC],
 * bump cur[1], emit at *cur + n*8). Rewritten 2026-06-22 from m2c into the
 * clean reused-local 00002DE0 shape -> 58.6% -> 70.7% fuzzy. Two real
 * misdecodes fixed: sp3C/sp38 are s16 reads (lh) not lw; the H-block guard is
 * `(s16)(by*4) < 0` not the m2c `temp_f6 & 0x20000000` phantom. All ops/field-
 * types now match target; residual is pure whole-function register coloring +
 * scheduling (target keeps the deref base + accumulator in callee-saved s0
 * across blocks; IDO here colors them caller-saved, -88 vs -80 frame). Permuter
 * can't score this (USO-relocatable raw-.word target). Default INCLUDE_ASM
 * keeps ROM byte-exact. */
void gui_func_0000329C(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    char *g = (char *)&D_00000000;
    char *base;
    char *dl;
    char *slot;
    s32 idx;
    s32 sp3C;
    s32 sp38;
    char *t2;
    s32 mode;
    f32 fW;
    f32 fH;
    s32 bx;
    s32 by;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
    s32 dsdx;
    s32 dtdy;
    s32 tmp;

    base = (*(char **)g);
    dl = (*(char **)(base + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(base + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x0)) = 0xBB000001;
    (*(s32 *)(slot + 0x4)) = 0x80008000;

    t2 = (*(char **)(arg0 + 0x10));
    sp3C = (*(s16 *)(t2 + 0x20));
    sp38 = (*(s16 *)(t2 + 0x22));
    mode = (*(s32 *)(t2 + 0x24));
    switch (mode) {
    case 0x408:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        break;
    case 0x120:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        break;
    case 0x110:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        break;
    }
    base = (*(char **)g);
    y0 = 0;
    dl = (*(char **)(base + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(base + 0xC)) + 0x0)) + idx * 8);
    fW = (f32) (arg3 - arg1);
    x0 = 0;
    bx = (s32) (f32) arg1;
    fH = (f32) (arg4 - arg2);
    if ((s16) ((bx + (s32) fW) * 4) > 0) {
        x0 = (bx + (s32) fW) * 4;
    }
    by = (s32) (f32) arg2;
    x1 = 0;
    if ((s16) ((by + (s32) fH) * 4) > 0) {
        y0 = (by + (s32) fH) * 4;
    }
    (*(s32 *)(slot + 0x0)) = (s32) (((x0 & 0xFFF) << 0xC) | 0xE4000000 | (y0 & 0xFFF));
    if ((s16) (bx * 4) > 0) {
        x1 = bx * 4;
    }
    if ((s16) (by * 4) > 0) {
        y1 = by * 4;
    } else {
        y1 = 0;
    }
    (*(s32 *)(slot + 0x4)) = (s32) (((x1 & 0xFFF) << 0xC) | (y1 & 0xFFF));
    base = (*(char **)g);
    dl = (*(char **)(base + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(base + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x0)) = 0xB4000000;
    if ((s16) (bx * 4) < 0) {
        dsdx = (s32) (((f32) (sp3C - 1) * 1024.0f) / fW);
        if ((s16) dsdx < 0) {
            tmp = (s32) ((s16) (bx * 4) * (s16) dsdx) >> 7;
            if (tmp > 0) {
                x0 = tmp;
            } else {
                x0 = 0;
            }
        } else {
            y0 = 0;
            tmp = (s32) ((s16) (bx * 4) * (s16) dsdx) >> 7;
            if (tmp < 0) {
                y0 = tmp;
            }
            x0 = y0;
        }
    } else {
        x0 = 0;
        dsdx = (s32) (((f32) (sp3C - 1) * 1024.0f) / fW);
    }
    if ((s16) (by * 4) < 0) {
        dtdy = (s32) (((f32) (sp38 - 1) * 1024.0f) / fH);
        if ((s16) dtdy < 0) {
            tmp = (s32) ((s16) (by * 4) * (s16) dtdy) >> 7;
            if (tmp > 0) {
                y1 = tmp;
            } else {
                y1 = 0;
            }
        } else {
            x1 = 0;
            tmp = (s32) ((s16) (by * 4) * (s16) dtdy) >> 7;
            if (tmp < 0) {
                x1 = tmp;
            }
            y1 = x1;
        }
    } else {
        y1 = 0;
        dtdy = (s32) (((f32) (sp38 - 1) * 1024.0f) / fH);
    }
    (*(s32 *)(slot + 0x4)) = (s32) ((x0 * -0x10000) | (-y1 & 0xFFFF));
    base = (*(char **)g);
    dl = (*(char **)(base + 0xC));
    idx = (*(s32 *)(dl + 0x4));
    (*(s32 *)(dl + 0x4)) = idx + 1;
    slot = (char *)((*(s32 *)((*(char **)(base + 0xC)) + 0x0)) + idx * 8);
    (*(s32 *)(slot + 0x4)) = (s32) ((dsdx << 0x10) | (dtdy & 0xFFFF));
    (*(s32 *)(slot + 0x0)) = 0xB3000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000329C);
#endif

#ifdef NON_MATCHING
/* gui_func_00003714: 256-insn / 0x400 RDP DL builder, same D_GUI_CTX family as
 * gui_func_0000329C. Double-deref base = *(int*)g; cursor q = *(base+0xC); bump
 * q[1]; emit at *q + n*8. Reconstructed from expected m2c (2026-06-22): true
 * double-deref + `/two` named divisor (forces div.s 2.0f, target form) +
 * per-block base capture -> 64.5% -> 68.5% fuzzy. Residual is a register-
 * coloring / &D-rematerialization cap (target holds &D in t4 across blocks
 * 3-4; IDO here rematerializes lui/addiu) + frame -88 vs -96 + sp30 sh-vs-sw
 * home. Default INCLUDE_ASM keeps ROM byte-exact. */
void gui_func_00003714(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6) {
    char *g = (char *)&D_00000000;
    f32 two = 2.0f;
    s32 sp30;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_t0_2;
    s16 temp_t3;
    s16 temp_v1_3;
    s16 var_a0;
    s16 var_a0_2;
    s16 var_a3;
    s16 var_a3_2;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3_3;
    s32 var_t4;
    char *temp_t0;
    char *temp_t1;
    char *temp_t1_2;
    char *temp_t1_3;
    char *temp_t1_4;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_3;
    char *temp_v0_8;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s0_3;
    char *temp_s0_4;

    temp_s0 = (*(s32 *)g);
    temp_v0 = (*(s32 *)(temp_s0 + 0xC));
    temp_v1 = (*(s32 *)(temp_v0 + 0x4));
    (*(s32 *)(temp_v0 + 0x4)) = (s32) (temp_v1 + 1);
    temp_t1 = (*(s32 *)((char *)(*(s32 *)(temp_s0 + 0xC)) + 0x0)) + (temp_v1 * 8);
    (*(s32 *)(temp_t1 + 0x0)) = 0xBB000001;
    (*(s32 *)(temp_t1 + 0x4)) = 0x80008000;
    temp_t0 = (*(s32 *)(arg0 + 0x10));
    temp_t3 = (*(s16 *)(temp_t0 + 0x22));
    sp30 = (s32) temp_t3;
    gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t0 + 0x8)), (*(s16 *)(temp_t0 + 0x20)), temp_t3, arg3, 0, arg4, (s32) temp_t3, 0);
    temp_s0_2 = (*(s32 *)g);
    temp_v0_2 = (*(s32 *)(temp_s0_2 + 0xC));
    temp_f0 = (f32) arg4;
    temp_v1_2 = (*(s32 *)(temp_v0_2 + 0x4));
    temp_f12 = temp_f0 * arg5;
    (*(s32 *)(temp_v0_2 + 0x4)) = (s32) (temp_v1_2 + 1);
    temp_t1_2 = (*(s32 *)((char *)(*(s32 *)(temp_s0_2 + 0xC)) + 0x0)) + (temp_v1_2 * 8);
    var_a3 = 0;
    temp_f10 = (s32) ((f32) arg1 + (-(temp_f0 / two) * arg5));
    temp_a1 = ((s32) temp_f12 + temp_f10) * 4;
    if (temp_a1 > 0) {
        var_a3 = temp_a1;
    }
    temp_f0_2 = (f32) temp_t3;
    temp_f14 = temp_f0_2 * arg6;
    temp_a1_2 = temp_f10 * 4;
    var_a0 = 0;
    var_a3_2 = 0;
    temp_f10_2 = (s32) ((f32) arg2 + (-(temp_f0_2 / two) * arg6));
    temp_v1_3 = ((s32) temp_f14 + temp_f10_2) * 4;
    if (temp_v1_3 > 0) {
        var_a0 = temp_v1_3;
    }
    temp_t0_2 = temp_f10_2 * 4;
    (*(s32 *)(temp_t1_2 + 0x0)) = (s32) (((var_a3 & 0xFFF) << 0xC) | 0xE4000000 | (var_a0 & 0xFFF));
    if (temp_a1_2 > 0) {
        var_a3_2 = temp_a1_2;
    }
    if (temp_t0_2 > 0) {
        var_a0_2 = temp_t0_2;
    } else {
        var_a0_2 = 0;
    }
    (*(s32 *)(temp_t1_2 + 0x4)) = (s32) (((var_a3_2 & 0xFFF) << 0xC) | (var_a0_2 & 0xFFF));
    temp_s0_3 = (*(s32 *)g);
    temp_v0_3 = (*(s32 *)(temp_s0_3 + 0xC));
    temp_v1_4 = (*(s32 *)(temp_v0_3 + 0x4));
    (*(s32 *)(temp_v0_3 + 0x4)) = (s32) (temp_v1_4 + 1);
    temp_t1_3 = (*(s32 *)((char *)(*(s32 *)(temp_s0_3 + 0xC)) + 0x0)) + (temp_v1_4 * 8);
    (*(s32 *)(temp_t1_3 + 0x0)) = 0xB4000000;
    if (temp_a1_2 < 0) {
        var_t4 = (s32) (((f32) (arg4 - 1) * 1024.0f) / temp_f12);
        if ((s16) var_t4 < 0) {
            temp_v0_4 = (s32) ((s16) var_t4 * temp_a1_2) >> 7;
            if (temp_v0_4 > 0) {
                var_a1 = temp_v0_4;
            } else {
                var_a1 = 0;
            }
        } else {
            temp_v0_5 = (s32) ((s16) var_t4 * temp_a1_2) >> 7;
            if (temp_v0_5 < 0) {
                var_a1 = temp_v0_5;
            } else {
                var_a1 = 0;
            }
        }
    } else {
        var_a1 = 0;
        var_t4 = (s32) (((f32) (arg4 - 1) * 1024.0f) / temp_f12);
    }
    if (temp_t0_2 < 0) {
        var_a3_3 = (s32) (((f32) (temp_t3 - 1) * 1024.0f) / temp_f14);
        if ((s16) var_a3_3 < 0) {
            temp_v0_6 = (s32) ((s16) var_a3_3 * temp_t0_2) >> 7;
            if (temp_v0_6 > 0) {
                var_a2 = temp_v0_6;
            } else {
                var_a2 = 0;
            }
        } else {
            temp_v0_7 = (s32) ((s16) var_a3_3 * temp_t0_2) >> 7;
            if (temp_v0_7 < 0) {
                var_a2 = temp_v0_7;
            } else {
                var_a2 = 0;
            }
        }
    } else {
        var_a2 = 0;
        var_a3_3 = (s32) (((f32) (temp_t3 - 1) * 1024.0f) / temp_f14);
    }
    (*(s32 *)(temp_t1_3 + 0x4)) = (s32) ((var_a1 * -0x10000) | (-var_a2 & 0xFFFF));
    temp_s0_4 = (*(s32 *)g);
    temp_v0_8 = (*(s32 *)(temp_s0_4 + 0xC));
    temp_v1_5 = (*(s32 *)(temp_v0_8 + 0x4));
    temp_t1_4 = (*(s32 *)((char *)(*(s32 *)(temp_s0_4 + 0xC)) + 0x0)) + (temp_v1_5 * 8);
    (*(s32 *)(temp_v0_8 + 0x4)) = (s32) (temp_v1_5 + 1);
    (*(s32 *)(temp_t1_4 + 0x0)) = 0xB3000000;
    (*(s32 *)(temp_t1_4 + 0x4)) = (s32) ((var_t4 << 0x10) | (var_a3_3 & 0xFFFF));
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003714);
#endif

/* gui_uso_func_00003B14: 27-insn / 0x6C RDP G_FILLRECT display-list builder.
 * 0xF6 << 24 = G_FILLRECT command word (per F3DEX2 gbi.h).
 *
 * MATCHED 2026-05-31 via decomp-permuter. The prior "2-insn order-swap CAP"
 * (target emits entry[1]'s `or` before entry[0]'s) was cracked: putting the two
 * entry[] stores on a SINGLE source line shifts IDO's `or` scheduling to match.
 * Byte-exact. (Same crack as gui_uso_func_00001794.) */
extern int gl_func_00000000();
extern char D_00000000;
void gui_uso_func_00003B14(int a0, int a1, int a2, int a3, int arg5) {
    typedef struct DLState { int *base; int idx; } DLState;
    typedef struct GameState { char pad[0xC]; DLState *dlp; } GameState;
    GameState *gs = *(GameState**)&D_00000000;
    DLState *dlp = gs->dlp;
    int idx = dlp->idx;
    int *entry;
    (void)a0;
    dlp->idx = idx + 1;
    entry = gs->dlp->base + idx * 2;
    entry[0] = 0xF6000000 | ((a3 & 0x3FF) << 14) | ((arg5 & 0x3FF) << 2); entry[1] = ((a1 & 0x3FF) << 14) | ((a2 & 0x3FF) << 2);
}

#ifdef NON_MATCHING
/* gui_func_00003B80: 230-insn / 0x398 RDP DL builder (originally bundled
 * 4-function 0x9E8; split-fragments output already INCLUDE_ASM-wired
 * below for 3 trailing helpers).
 *
 * Same family entry shape as gui_func_0000329C / 0000_2DE0 / 0000_2BB0:
 * D_GUI_CTX deref + cursor bump on ctx[0xC]->[1] + RDP 0xBB000001 +
 * 0x80008000 segment-marker emit at slot 0. ~230 insns of body to
 * decode in next pass. Multi-pass NM remains. */
extern int D_3B80_f0, D_3B80_f1, D_3B80_f2;
/* Whole-body re-decode 2026-06-22 (agent-e). Paginated RDP texture-DL builder.
 * &D_00000000 referenced DIRECTLY at each use (not via a held-pointer local) so
 * IDO's LICM promotes the address into a saved reg + single `lw 0(base)` per ctx
 * deref, matching target's held base (see docs/IDO_CODEGEN "Reference the SYMBOL
 * DIRECTLY"). s5=a0 held; a1/a2 spilled to home slots and reloaded; frow ptr on
 * stack. Switch on a0[3] selects frow + max-bytes-per-page; split a0[2] (height)
 * into pages of (max/height) rows.
 * RESIDUAL (raw-word USO, permuter N/A): base colored into $s4 not target's $s7
 * (longest-LR coloring tie); +8 frame; switch li-hoist + a3-spill scheduler ties.
 * Logic byte-correct; 79% mnemonic / 87.3% fuzzy. */
void gui_func_00003B80(int *a0, int a1, int a2, int a3) {
    int *s5 = a0;
    int s8 = 0;
    int s2, s0, s3, s1, s4, s6;
    int max;
    void (*frow)();

    {
        int *dlp = (int *)(*(int **)&D_00000000)[0xC / 4];
        int idx = dlp[1];
        dlp[1] = idx + 1;
        {
            int *slot = (int *)(((int *)(*(int **)&D_00000000)[0xC / 4])[0]) + idx * 2;
            slot[0] = 0xBB000001;
            slot[1] = (int)0x80008000;
        }
    }
    switch (a0[0xC / 4]) {
    case 0:  frow = (void (*)())&D_3B80_f0; max = 4096; break;
    case 1:  frow = (void (*)())&D_3B80_f1; max = 2048; break;
    case 2:  frow = (void (*)())&D_3B80_f2; max = 1024; break;
    default: frow = 0;                      max = a3;   break;
    }
    s2 = s5[4 / 4];   /* width  */
    s0 = s5[8 / 4];   /* height */
    if (s2 * s0 > max) {
        s1 = gl_func_00000000(max / s0);   /* rows per page */
        s3 = s0;                            /* height */
        s0 = s5[4 / 4];                     /* width as page counter */
        s6 = (s3 << 10) / s3;
        while (s0 != 0) {
            if (s1 < s0) {
                s4 = (s1 << 10) / s1;
                frow(*(int **)&D_00000000, s5[0], s2, s5[8 / 4], s8, 0, s1, s3, 0);
                gl_func_00000000(*(int **)&D_00000000, a1, a2, s1, s3, s4, s6);
                s8 += s1;
                s0 -= s1;
                a1 += s1;
            } else {
                s1 = s0;
                frow(*(int **)&D_00000000, s5[0], s2, s0, s8, 0, s0, s3, 0);
                gl_func_00000000(*(int **)&D_00000000, a1, a2, s0, s3, (s0 << 10) / s0, s6);
                s0 -= s1;
            }
        }
    } else {
        frow(*(int **)&D_00000000, s5[0], s2, s0, 0, 0, s2, s0, 0);
        s2 = s5[4 / 4];
        s0 = s5[8 / 4];
        gl_func_00000000(*(int **)&D_00000000, a1, a2, s2, s0, (s2 << 10) / s2, (s0 << 10) / s0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003B80);
#endif

#ifdef NON_MATCHING
/* gui_uso_func_00003F18: 137-insn / 0x224 prologue-less DL builder, sibling of
 * gui_uso_func_00003B14 (the smaller 27-insn fillrect builder).
 *
 * STRUCTURAL CAP: function starts with 3 leading nops (0x3F18-0x3F20) AND
 * has NO `addiu sp, -N` prologue / NO `addiu sp, +N` epilogue. Body uses
 * sp+0xC..0x20 as scratch (caller's frame). C-emit always produces a
 * frame even when empty, AND IDO never emits 3 leading nops from a void
 * body, so plain C cannot match these structural shapes.
 *
 * Entry decode (post-leading-nops):
 *   sw a3, 0xC(sp)              ; save a3 to caller's arg-save slot
 *   v0 = a0->_C                 ; some DL state ptr
 *   v1 = v0->_4                 ; current entry counter
 *   v0->_4 = v1 + 1             ; bump
 *   t6 = a3 & 0xFFF             ; arg masked to 12 bits
 *   ... builds Gfx entry words from a1/a2/a3 + sp+0x10/0x14/0x18 ...
 *   final entries store via t7 (= v0->_0 base + v1*8).
 *
 * Likely a G_TEXRECTFLIP or G_SETOTHERMODE-class command builder bundled
 * with sibling 0x413C (which has the same body sans 3 leading nops) and
 * 0x4354 (same again, sans nops). The 3-nop variant might be "shared
 * backward-compatible entry that landed mid-cache-line" (alignment or
 * cache-friendliness consideration).
 *
 * Recipe options for byte-match (none tried this tick):
 *   1. Hand-written .s file in src/gui_uso/, removed from INCLUDE_ASM list,
 *      compiled directly. Equivalent to keeping INCLUDE_ASM forever — no
 *      C representation.
 *   2. SUFFIX_BYTES on predecessor (gui_func_00003B80) injecting 3 nops
 *      then this function emits without leading padding. Predecessor
 *      already ends at 0x3F14, and 0x3F18 sits 4-byte aligned — adding
 *      SUFFIX_BYTES of 3 nops to predecessor + matching successor's body
 *      from its first non-nop insn could work. Untested.
 *
 * Stays INCLUDE_ASM until a recipe is verified. */
// GBI texture-load display list (sibling of gui_uso_func_00004354; constants
// 0xFD18/0xF518/0x07020080/0x20080 + a *2 in the SetTile size calc). 7 command
// packets via the cursor idiom. NOTE: the function .s has 3 leading nops
// (0x3F18..0x3F20) that C cannot emit, so the body aligns but the head won't.
void gui_uso_func_00003F18(char *a0, int a1, int a2, int a3, int arg5,
                           int arg6, int arg7, int arg8, int arg9) {
    char *buf;
    int i;
    int *p;
    int t0, a3v, a1v, t1, t3;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xFD180000 | ((a2 - 1) & 0xFFF);
    p[1] = a1;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    a3v = arg5 + arg7;
    t0 = a3v - arg5;
    t1 = ((((t0 * 2 + 7) >> 3) & 0x1FF) << 9) | 0xF5180000 | ((arg9 << 8) & 0x1FF);
    p[0] = t1;
    p[1] = 0x07020080;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    a2 = arg6;
    p[0] = 0xE6000000;
    p[1] = 0;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xF4000000 | ((((arg5 << 2) & 0xFFF) << 0xC)) | ((a2 << 2) & 0xFFF);
    a1v = a2 + arg8;
    p[1] = 0x07000000 | ((((a3v - 1) << 2) & 0xFFF) << 0xC) | (((a1v - 1) << 2) & 0xFFF);

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xE7000000;
    p[1] = 0;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = t1;
    t3 = (arg9 & 7) << 0x18;
    p[1] = t3 | 0x00020000 | 0x80;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xF2000000;
    p[1] = t3 | ((((t0 - 1) << 2) & 0xFFF) << 0xC) | ((((a1v - a2) - 1) << 2) & 0xFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00003F18);
#endif

/* gui_uso_func_0000413C — verified structural decode (no-call/no-branch RDP
 * display-list builder, 134 insns, 1% first pass; GfxCtx-idiom regalloc
 * cascade needs multi-run → INCLUDE_ASM build path; N64-forensics ref).
 * Args: f(GfxCtx **a0, a1, a2, a3, arg4@sp16, arg5@sp20, arg6@sp24,
 *         arg7@sp28, arg8@sp32). a0->0xC = ptr to {Gfx *buf @0; int idx @4}.
 * Per-packet idiom (×7): g=(ctx*)a0->0xC; i=g->idx; g->idx=i+1;
 *   slot=(int*)g->buf + i*2; slot[0]=w0; slot[1]=w1;  (a0->0xC reloaded
 *   TWICE per packet in target — once for ->idx, once for ->buf).
 * Forensics: this is a texture-load DL fragment (SETTIMG→SETTILE→LOADSYNC→
 * LOADTILE→PIPESYNC→SETTILE→SETTILESIZE). t1 is CSE'd across packets 2&6;
 * arg6=texW, arg7=texH-ish, arg8=tile fmt/palette.
 * Caps far <80: the a0->0xC double-reload GfxCtx idiom ×7 + cross-packet
 * CSE drive a regalloc cascade no first-pass C reproduces (multi-run
 * target). INCLUDE_ASM remains build path. */
#ifdef NON_MATCHING
void gui_uso_func_0000413C(char **a0, int a1, int a2, int a3,
                            int arg4, int arg5, int arg6, int arg7, int arg8) {
    char *g;
    int i;
    int *slot;
    int t1;
    (void)a3;
    t1 = ((((((arg4 + arg6) - arg4) << 1) + 7) >> 3) & 0x1FF) << 9 | 0xF5100000 |
         ((arg8 << 8) & 0x1FF);
    /* packet 1: G_SETTIMG */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = ((a2 - 1) & 0xFFF) | 0xFD100000;
    slot[1] = a1;
    /* packet 2: G_SETTILE */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = t1;
    slot[1] = 0x07020080;
    /* packet 3: G_RDPLOADSYNC */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = 0xE6000000;
    slot[1] = 0;
    /* packet 4: G_LOADTILE */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = (((arg4 << 2) & 0xFFF) << 12) | 0xF4000000 | ((arg5 << 2) & 0xFFF);
    slot[1] = ((((arg4 + arg6 - 1) << 2) & 0xFFF) << 12) | 0x07000000 |
              (((arg5 + arg7 - 1) << 2) & 0xFFF);
    /* packet 5: G_RDPPIPESYNC */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = 0xE7000000;
    slot[1] = 0;
    /* packet 6: G_SETTILE var */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = t1;
    slot[1] = ((arg8 & 7) << 24) | 0x00020000 | 0x80;
    /* packet 7: G_SETTILESIZE */
    g = *(char**)((char*)a0 + 0xC);
    i = *(int*)(g + 4);  *(int*)(g + 4) = i + 1;
    slot = (int*)(*(char**)g) + i * 2;
    slot[0] = 0xF2000000;
    slot[1] = ((arg8 & 7) << 24) | ((((arg6 - 1) << 2) & 0xFFF) << 12) |
              (((arg7 - 1) << 2) & 0xFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000413C);
#endif

#ifdef NON_MATCHING
/* gui_uso_func_00004354: 133-insn (0x214) Gfx-display-list builder.
 * Leaf function (no stack frame, only caller-slot a3 spill at sp+0xC)
 * that writes ~6 RDP commands into a display list buffer at a0->[0xC].
 *
 * Args (inferred from asm structure):
 *   a0 — gui-state struct; a0->[0xC] is a Gfx-buffer descriptor:
 *        - +0: dlist pointer (Gfx **) into the actual command buffer
 *        - +4: command counter (advanced by 1 per command emitted)
 *   a1 — image segment-address (used as second word of G_SETTIMG)
 *   a2 — width minus 1 (asm pre-decrements: addiu t4, a2, -1)
 *   a3 — saved at sp+0xC at function entry, never used in body
 *   sp+0x10..0x20 — additional stack args (4..5 more ints)
 *
 * RDP command sequence (each emits a 64-bit Gfx command pair):
 *   0xFD68 hi-word — G_SETTIMG (set texture image)
 *   0xE600 hi-word — G_RDPLOADSYNC
 *   0xF400 hi-word — G_LOADTILE
 *   0x0700 hi-word — appears in tile-size cmd
 *   0xE700 hi-word — G_RDPPIPESYNC
 *   0xF200 hi-word — G_SETTILESIZE
 *   0xF568 hi-word — variant of SETTIMG (8-bit format?)
 *
 * Pattern: classic "render textured quad" setup — set texture image,
 * load the tile, set tile params, set tile size, draw a texture
 * rectangle. Common in N64 GUI/HUD code.
 *
 * Structural cap: complex F3DEX2 / RDP gfx code with heavy bit-shifting
 * (sll t9, v1, 3 = stride*8 for 64-bit Gfx) and packing
 * (multiple `andi rN, 0xFFF` for 12-bit width/height fields). Multi-
 * tick decomp; first pass documents the structure, future passes can
 * decode each command into gsDPSetTextureImage / gsDPLoadTile /
 * gsDPSetTile / gsDPSetTileSize / gsSPTextureRectangle macros (or
 * their open-coded equivalents).
 *
 * 2026-05-08: structural NM-only first pass. The 0xC-byte addressing
 * pattern (a0->[0xC] = Gfx-buffer descriptor with .dlist + .count
 * fields) recurs across gui_uso_func_*413C, *4354, *4568, *4774 —
 * worth typing as `GfxBuf { Gfx **dlist; int count; }` in a future
 * pass once decoded for one of them. */
#if 0
/* Pseudo-shape for future ticks:
 *   void gui_uso_func_00004354(GuiState *a0, u32 imgaddr, int w,
 *                              int unused_a3, int p5, int p6, int p7,
 *                              int p8) {
 *       Gfx *dl = a0->gfxBuf->dlist;
 *       int *count = &a0->gfxBuf->count;
 *       (*count)++;
 *       gDPPipeSync(dl);                       // 0xE700 hi
 *       gDPSetTextureImage(dl++, ...);         // 0xFD68 hi
 *       gDPLoadSync(dl++);                     // 0xE600 hi
 *       gDPLoadTile(dl++, ...);                // 0xF400 hi
 *       gDPSetTile(dl++, ...);
 *       gDPSetTileSize(dl++, 0, 0, w-1, h-1);  // 0xF200 hi
 *       gSPTextureRectangle(dl++, ...);
 *   }
 */
#endif
// GBI texture-load display list: 7 command packets via the cursor idiom
// (buf=a0->0xC; i=buf->4; buf->4=i+1; p=*buf+i*8; p[0]=cmd; p[1]=arg).
// SetTextureImage(0xFD68), SetTile(0xF568), LoadSync(0xE600), LoadTile(0xF400),
// PipeSync(0xE700), a second SetTile (reused word), SetTileSize(0xF200).
// Pure-linear; reused intermediates (arg7, arg5+arg7, arg6+arg8, the F568
// word, (arg9&7)<<24) thread across packets exactly as the target.
void gui_uso_func_00004354(char *a0, int a1, int a2, int a3, int arg5,
                           int arg6, int arg7, int arg8, int arg9) {
    char *buf;
    int i;
    int *p;
    int t0, a3v, a1v, t1, t3;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xFD680000 | ((a2 - 1) & 0xFFF);
    p[1] = a1;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    a3v = arg5 + arg7;
    t0 = a3v - arg5;
    t1 = ((((t0 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000 | ((arg9 << 8) & 0x1FF);
    p[0] = t1;
    p[1] = 0x07020090;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    a2 = arg6;
    p[0] = 0xE6000000;
    p[1] = 0;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xF4000000 | ((((arg5 << 2) & 0xFFF) << 0xC)) | ((a2 << 2) & 0xFFF);
    a1v = a2 + arg8;
    p[1] = 0x07000000 | ((((a3v - 1) << 2) & 0xFFF) << 0xC) | (((a1v - 1) << 2) & 0xFFF);

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xE7000000;
    p[1] = 0;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = t1;
    t3 = (arg9 & 7) << 0x18;
    p[1] = t3 | 0x00020000 | 0x90;

    buf = *(char **)(a0 + 0xC); i = *(int *)(buf + 4); *(int *)(buf + 4) = i + 1;
    p = (int *)(*(int *)buf + i * 8);
    p[0] = 0xF2000000;
    p[1] = t3 | ((((t0 - 1) << 2) & 0xFFF) << 0xC) | ((((a1v - a2) - 1) << 2) & 0xFFF);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00004354);
#endif

#ifdef NON_MATCHING
/* gui_func_00004568: 198-insn / 0x318 RDP TEXRECT display-list builder.
 *
 * 2026-05-07 first-pass structural decode. Frame -8 ($s0 + nothing else;
 * $s0 = a0/ctx). 5-arg signature: a0=ctx, a1=x_lo (signed),
 * a2=y_lo (signed), a3=x_hi, sp[0x18]=y_hi (5th arg via stack).
 *
 * Entry-stage decode (insns 0-3):
 *   if (x_lo < 0) goto skip_first_dl;     // bltz a1
 *   if (y_lo < 0) goto skip_second_dl;    // bltzl a2 (annulled delay)
 *
 * Body shape (0x18-0xA8, ~38 insns): emits 2 RDP TEXRECT commands.
 *   Each DL command (8 bytes) is built from packed coordinate fields:
 *     ctx->[0xC]->[0x4]++           ; bump cursor
 *     dl_buf = ctx->[0xC]->[0]      ; DL base ptr
 *     slot = (cursor << 3)          ; 8-byte stride
 *     p = dl_buf + slot
 *     p[0] = 0xE4000000 | ((x_lo+x_hi) << 14 & 0xFFF000)
 *                       | (((y_lo+y_hi) << 2) & 0xFFF)
 *     p[1] = ((x_lo << 14) & 0xFFF000) | ((y_lo << 2) & 0xFFF)
 *     ; second DL: same shape but opcode 0xB4000000 (next-tile?)
 *
 * The 0xE4 opcode = G_TEXRECT (F3DEX2 RDP); 0xB4 = G_TEXRECTFLIP variant
 * or coord-extension. Each rect uses 12-bit fixed-point coords (10.2
 * format, mask 0xFFF = 0xFFC for 0x3FF.x maxes).
 *
 * REMAINING ~155 insns at 0xA8-0x318: continued DL writes + skip_first_dl
 * + skip_second_dl convergence + frame teardown. Multi-tick decode.
 *
 * Default INCLUDE_ASM keeps ROM exact. Wrap captures entry signature
 * and TEXRECT shape for the next pass. */
extern int gl_func_00000000();
/* Whole-body decode 2026-06-01 (was 1.35% stub); alt path faithfully
 * reconstructed 2026-06-05 (39.8% -> 54.2%). 7-arg TEXRECT DL builder.
 * Main path (a1>=0 && a2>=0): emit 3 RDP cmds — 0xE4 (G_TEXRECT) with
 * 10.2 fixed-point coords ((a1+a3)<<2 etc, mask 0xfff), 0xB4 (zero), 0xB3
 * (a5:a6 pack). Alt path (a1<0 || a2<0): each coord 16-bit-sign-extended +
 * clamp-to->0; the 0xB4 carries a multiply-SCALE — for each raw coord < 0,
 * p = ((u32)coord * (u32)(short)scale) >> 7 with a sign clamp whose direction
 * flips on sign(scale) ((short)a5 for x via lh sp+0x1e, (short)a6 for y via
 * lh sp+0x22), then slot[1] = (-sx << 16) | (-sy & 0xffff). Cmd-emit idiom:
 * st=ctx->0xc; slot=(ctx->0xc->0)+idx*8; bump st->4. RESIDUAL ~46%: target
 * keeps a1/a2/a3 register-resident (frame -8); this C homes them (arg spill) —
 * regalloc/scheduling, multi-pass. Default INCLUDE_ASM keeps ROM exact. */
void gui_func_00004568(int *a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    int *s0 = a0;
    int *st, *slot, idx;

    if (a1 >= 0 && a2 >= 0) {
        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xE4000000 | ((((a1 + a3) << 2) & 0xFFF) << 12) | (((a2 + a4) << 2) & 0xFFF);
        slot[1] = (((a1 << 2) & 0xFFF) << 12) | ((a2 << 2) & 0xFFF);

        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xB4000000;
        slot[1] = 0;

        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xB3000000;
        slot[1] = (a5 << 16) | (a6 & 0xFFFF);
    } else {
        int x0r = (short)(a1 << 2);          /* raw, reused by the 0xB4 scale */
        int y0r = (short)(a2 << 2);
        int sx = 0, sy = 0;

        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xE4000000 |
                  (((((short)((a1 + a3) << 2)) > 0 ? (short)((a1 + a3) << 2) : 0) & 0xFFF) << 12) |
                  ((((short)((a2 + a4) << 2)) > 0 ? (short)((a2 + a4) << 2) : 0) & 0xFFF);
        slot[1] = (((x0r > 0 ? x0r : 0) & 0xFFF) << 12) | ((y0r > 0 ? y0r : 0) & 0xFFF);

        if (x0r < 0) {
            short m = (short)a5;
            int p = (int)((u32)x0r * (u32)m) >> 7;
            sx = (m < 0) ? (p > 0 ? p : 0) : (p < 0 ? p : 0);
        }
        if (y0r < 0) {
            short m = (short)a6;
            int p = (int)((u32)y0r * (u32)m) >> 7;
            sy = (m < 0) ? (p > 0 ? p : 0) : (p < 0 ? p : 0);
        }

        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xB4000000;
        slot[1] = ((-sx) << 16) | ((-sy) & 0xFFFF);

        st = (int *)s0[0xC / 4];
        idx = st[1];
        st[1] = idx + 1;
        slot = (int *)(((int *)s0[0xC / 4])[0]) + idx * 2;
        slot[0] = 0xB3000000;
        slot[1] = (a5 << 16) | (a6 & 0xFFFF);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00004568);
#endif
