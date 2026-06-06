#include "common.h"

extern char D_00000000;

/* SOURCE=4 audit 2026-06-01: this cluster is not a missed accessor-template
 * candidate. The 0x0..0x148 char mapper is an over-split early-return chain;
 * the fragments look like leaf-branch-past-end/caller-set-register caps only
 * because predecessor tests branch into later entries while carrying $v0/$a0.
 * find-misplit-pairs.py does not flag it because each split entry has its own
 * jr ra. Proper recovery is a deliberate full-cluster merge, not per-fragment
 * C bodies. */

/* USO entry-0 trampoline leaf. The previous NM body described the old bundled
 * 0x148-byte glyph dispatch; after splitting, this symbol is just the first
 * 0x24 bytes. PREFIX_BYTES supplies the loader branch and arg-save delay slot. */
#ifdef NON_MATCHING
int gui_func_00000000(c)
int c;
{
    c &= 0xFF;
    if (c == 0x21) {
        c = 0x27;
    }
    return c & 0xFF;
}
#else
/* gui_func_00000000: leaf-branch-past-end CAP per feedback_leaf_branch_past_end_is_cross_fn_epilogue. */
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000000);
#endif

/* Branch-chain fragment: the predecessor leaves the character in $v0, and the
 * taken path jumps into gui_uso_func_0000003C after using this fragment's
 * delay slot to seed $at. IDO cannot name inherited $v0 from C. Was
 * previously documented as "Makefile post-cc recipe" promotion — those
 * recipes (INSN_PATCH/instruction-appending SUFFIX_BYTES) were REMOVED
 * 2026-05-23 as match-faking (per
 * feedback_no_instruction_forcing_matches_policy). Default INCLUDE_ASM
 * remains byte-exact. */
#ifdef NON_MATCHING
int gui_uso_func_00000024(void) {
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00000024);
#endif

/* Branch-chain sibling of gui_uso_func_00000024. This fragment inherits the
 * character in $v0 and cannot express the compare in C. Was previously
 * documented as Makefile INSN_PATCH/SUFFIX_BYTES — both REMOVED 2026-05-23
 * as match-faking (per feedback_no_instruction_forcing_matches_policy).
 * Default INCLUDE_ASM remains byte-exact. */
#ifdef NON_MATCHING
int gui_uso_func_0000003C(void) {
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000003C);
#endif

// gui_uso_func_00000054 — STRUCTURAL PASS (0x18 / 6 words, no episode).
// Raw-.word USO chained char-mapper entry (one of 10 contiguous entries
// at 0x54..0x124, each 0x18). Pattern: `bnel v0,$at,past-end` with the
// next-test addiu in the delay slot — falls THROUGH into the next entry
// if v0 != tested char.
//   if (v0 == 0x5B) { a0 = 0x26; return a0 & 0xFF; }   // ']' → '&'
//   else fall through to gui_uso_func_0000006C (next chained entry)
// Caps (DEFERRED): fall-through-on-mismatch can't be expressed in C
// without function-merge; keep INCLUDE_ASM as build path. The NM body
// below documents the MATCH branch only.
#ifdef NON_MATCHING
int gui_uso_func_00000054(int v0) {
    if (v0 == 0x5B) {
        int a0 = 0x26;
        return a0 & 0xFF;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00000054);
#endif

// Chained char-mapper entries (continuation of gui_uso_func_00000054).
// Each falls THROUGH to the next on mismatch — see
// reference_1080_chained_char_mapper_fallthrough memo. NM-wrap match
// branch only; INCLUDE_ASM is the build path.
#ifdef NON_MATCHING
int gui_uso_func_0000006C(int v0) { if (v0 == 0x5D) { int a0 = 0x27; return a0 & 0xFF; } return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000006C);
#endif

#ifdef NON_MATCHING
int gui_uso_func_00000084(int v0) { if (v0 == 0x2B) { int a0 = 0x24; return a0 & 0xFF; } return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00000084);
#endif

#ifdef NON_MATCHING
int gui_uso_func_0000009C(int v0) { if (v0 == 0x5F) { int a0 = 0x25; return a0 & 0xFF; } return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000009C);
#endif

#ifdef NON_MATCHING
int gui_uso_func_000000B4(int v0) { if (v0 == 0x2E) { int a0 = 0x25; return a0 & 0xFF; } return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000000B4);
#endif

#ifdef NON_MATCHING
int gui_uso_func_000000CC(int v0) { if (v0 == 0x2D) { int a0 = 0x25; return a0 & 0xFF; } return 0; }
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000000CC);
#endif

// Range entries: hex/digit decoders (lowercase 'a'-'z', uppercase 'A'-'Z',
// digit '0'-'9'); same fall-through-to-next-entry pattern on mismatch.
#ifdef NON_MATCHING
int gui_uso_func_000000E4(int v0) {
    if (v0 >= 0x61 && v0 < 0x7B) { int a0 = v0 - 0x57; return a0 & 0xFF; }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000000E4);
#endif

#ifdef NON_MATCHING
int gui_uso_func_00000104(int v0) {
    if (v0 >= 0x41 && v0 < 0x5B) { int a0 = v0 - 0x37; return a0 & 0xFF; }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00000104);
#endif

/* CALLER-SET-$v0 CAP (digit '0'-'9' -> value, else passthrough). Target reads
 * the arg from $v0 (`slti $1,$2,48`), NOT $a0 — caller-set-register convention
 * (cf. caller_set_int_reg_cap), so a C `(int v0)` arg lands in $a0 and diverges.
 * Also the out-of-range path SHARES the return (`jr ra; andi $2,$4,0xff`)
 * returning the incoming $4&0xff (a 2nd caller-set/preserved reg), so there's
 * no explicit `return 0`; my C's `return 0` adds a `move $2,$0` + 2nd jr ra
 * (the +2 OVER in find-size-mismatch). Not C-reachable — INCLUDE_ASM stays. */
#ifdef NON_MATCHING
int gui_uso_func_00000124(int v0) {
    if (v0 >= 0x30 && v0 < 0x3A) { int a0 = (v0 - 0x30) & 0xFF; return a0 & 0xFF; }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00000124);
#endif

/* gui_func_00000148: BUNDLED splat symbol (0x7D0 total / 500 insns).
 * splat could not separate sub-functions (no inter-function relocs).
 * Per feedback_uso_split_fragments_breaks_expected_match.md, splitting
 * USO funcs is risky - expected/.o keeps the bundled symbol. Bundled.
 *
 * Sub-function layout (boundary = jr $ra + delay slot):
 *   F1 @ 0x148-0x558: 0x410 / 260 insns. addiu sp,-0x80 prologue, saves
 *     12 callee-saves (s0-s5+s6+s7+fp+s3+s4). HEAVY div idiom
 *     (multiple div+break-on-zero pairs at 0x1A4/0x1D0/0x20C). Alloc
 *     sub-object via gl_func_00000000(0x28) at insn 9. Stores results
 *     to s2->{0x4, 0xC, 0x0, 0x10, 0x14, 0x18, 0x1C}. Likely
 *     GLYPH-LAYOUT-MEASURE function: divides string-width / glyph-count
 *     to produce kerning/spacing fields.
 *   F2 @ 0x55C-0x6B4: 0x158 / 87 insns. Smaller helper.
 *   F3 @ 0x6B8-0x8BC: 0x204 / 129 insns. Mid-size.
 *   ORPHAN @ 0x8C0-0x914: 22 insns with NO jr $ra. Starts `lw v0,
 *     0x24(a0)`. Loads from $a0 + setup of 0xB900031D / 0x4242240
 *     constants (RDP DPC commands?). Either dead code or a tail-call
 *     site that doesn't return through the standard jr-ra path.
 *     gui_func_00000918 (next splat symbol) starts at 0x918 with its
 *     own addiu-sp prologue, so the 22 orphan insns DO NOT logically
 *     continue there. Verified 2026-05-03 via boundary recheck (0x918
 *     has 1 jr ra at 0xB50, single coherent function).
 *
 * Total cost to NM-wrap: would need to write 3 sub-bodies + an orphan
 * tail as one ~500-insn C function with goto-chains, which IDO won't
 * reproduce. Best path forward: type the GUI struct (sub-object @ 0x28
 * from gl_func) first via siblings, then attempt a
 * split-with-refresh-expected later.
 */
#ifdef NON_MATCHING
/* Partial decode 2026-06-01. Grid/table-allocator constructor: find-or-create
 * (size 40), stores the dims (cols=a2/rows, rows*cols, a3/cols) and allocates
 * the cell buffer (rows*cols*20) at obj->0x20. The nested-loop per-cell init
 * (~180 insns) is a follow-up. */
void *gui_func_00000148(char *a0, int a1, int a2, int a3, int rows, int cols) {
    char *o = a0;
    int prod;

    if (a0 == 0) {
        o = (char *)gl_func_00000000(40);
        if (o == 0) {
            return 0;
        }
    }
    *(int *)(o + 4) = a1;
    *(int *)(o + 0xC) = a2 / rows;
    prod = rows * cols;
    *(int *)(o + 0) = prod;
    *(int *)(o + 0x10) = a3 / cols;
    *(int *)(o + 0x18) = a2;
    *(int *)(o + 0x1C) = a3;
    *(int *)(o + 0x14) = a3 / cols;
    *(int *)(o + 0x20) = gl_func_00000000(prod * 20);
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

/* gui_uso_func_000008C0 (0x8C0..0x914, 0x58): F3DEX2 DL-builder HEAD. Clean entry
 * `lw v0,0x24(a0)` (state ptr = a0->[0x24]), builds 2 Gfx command pairs
 * (G_SETOTHERMODE 0xB900031D / 0x00404240, G_SETCOMBINE 0xFC309661...), loads 1.0f
 * (lui 0x3F80; mtc1). It has NO prologue and NO `jr ra`: it RUNS OFF THE END into
 * gui_func_00000918 (0x918), whose first insn is a prologue `addiu sp,-0x10` and
 * which then does `lw v1,0xC(v0)` -- reading the SAME v0 this head set.
 *
 * RESOLVES the open question in gui_func_00000918's note ("implicit v0-input
 * convention -- investigate the caller"): v0 is NOT a caller convention; it is set
 * HERE at 0x8C0 (`lw v0,0x24(a0)`) and the body at 0x918 is the fall-through
 * continuation. 000008C0 + 00000918 are one logical routine that splat split at the
 * mid-function prologue (a dual-entry / fall-through-into-prologue shape).
 * MERGE-SAFETY (2026-05-30): no static C or asm reference to gui_func_00000918 /
 * 0x918 exists, so a boundary merge into a single 0x298-byte unit is byte-safe AND
 * would let the body be decoded with `a0` as the real arg.
 *
 * SOURCE=4 AUDIT (2026-06-01): kept split. 0x8C0 has 0 `jr ra` insns, and
 * `scripts/find-misplit-pairs.py gui_uso --max-insn 220` still reports 0 closed
 * groups. A fresh static search found no current source/asm callers of 0x918
 * beyond this note and the preserved INCLUDE_ASM, but report/episode snapshots
 * are not runtime dispatch proof. Do not merge until the USO symbol/export table
 * proves 0x918 is not also an independent runtime entry. */
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_000008C0);

#ifdef NON_MATCHING
/* gui_func_00000918: 144-insn display-list builder for GUI primitives.
 *
 * 2026-05-07 first-pass decode: this function takes its primary state
 * pointer in $v0 (NOT $a0) — the entry insns 0x04, 0x18 read
 * `lw v1, 0xC(v0)` and `lw t3, 0xC(v0)` BEFORE any code that sets v0.
 * Insn 0x44 `lw v0, 0x24(a0)` finally sets v0 from a0->[0x24], but the
 * prior 17 insns assumed v0 was pre-set. This is a non-standard
 * calling convention — the caller (likely gui_func_00000148 or similar)
 * leaves a state pointer in v0 (or v0 holds a0->[0x24] pre-call via
 * caller's setup). Documented so future passes know to investigate.
 *
 * Body shape: emits 2 G_SETPRIMCOLOR-ish DL commands, each:
 *   ctx->cursor++ (at a0->[0xC]->[0x4])
 *   dl_buf = ctx->dl_buf->[0]
 *   slot = (old_cursor << 3)
 *   *(u32*)(dl_buf + slot)     = 0xFA000000
 *   *(u32*)(dl_buf + slot + 4) = color_word
 * After the 2 DL writes, performs 3-channel R/G/B float→int conversion
 * with FCSR-overflow clamping (the cfc1/ctc1 pattern, andi 0x78 mask
 * checks the V|Z|U|I exception flags). Each channel:
 *   1. Load color_float from sp scratch
 *   2. Multiply by 0x4F000000 (= 2^31, max-int-as-float)
 *   3. cvt.w.s, then check FCSR for overflow
 *   4. If overflow: clamp to 0 (negative) or 0xFF (positive)
 *   5. Mask result to 0xFF
 *   6. Shift to byte position (0/8/16) and OR into accumulator
 * Final OR'd 24-bit color is stored to dl_buf+slot+4 of the second
 * DL command.
 *
 * Won't byte-match in one tick (144 insns of float scheduling +
 * implicit v0-input convention). Wrap captures structure for the next
 * pass. Default INCLUDE_ASM keeps ROM correct. */
extern int gl_func_00000000();
void gui_func_00000918(int *a0) {
    /* Stub: structural decode of 144-insn float-color converter. The v0
     * implicit-input convention prevents a clean standalone C body — the
     * function would need to reach in via a global state register or
     * factor through a wrapper that takes v0's role explicitly. Future
     * passes: (a) identify the caller and inline-merge to hide the v0
     * convention, OR (b) write the body assuming a hypothetical
     * `state *s = (state*)v0_input_via_register` and accept the prologue
     * shape mismatch. */
    (void)a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000918);
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
 *   - REMAINING: build spills arg5 (a1) to its own slot after the first call
 *     instead of reloading from the stack-arg home like the target. */
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
    cmd = (int*)(*(char**)dl + cnt * 8);
    cmd[0] = 0xBB000001;
    cmd[1] = 0x80008000;
    idx = 0;
    s7 = arg5;
    {
        /* named-local divisor forces div.s (not mul*0.5); target shares this
         * one 2.0 across both divisions AND the -2.0 sub (IDO_CODEGEN
         * #feedback-ido-div-2-mul-fold-and-mtc1-load-delay-nops). */
        float two = 2.0f;
        var_f22 = -((float)gl_func_00000000(arg0, arg5) / two) - two;
        spD4 = -((float)*(int*)((char*)arg0 + 0x10) / two);
    }
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
                wa3 = 0;
                f8 = (int)((float)arg1 + (var_f22 * arg3));
                cmd2 = (int*)(*(char**)dl + cnt2 * 8);
                ca0 = (f8 + (int)f0b) * 4;
                ca1 = f8 * 4;
                if (ca0 > 0) wa3 = ca0;
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

#ifdef NON_MATCHING
/* gui_func_0000161C: 0x1060 (1048 insns, 4.1 KB), no prologue (leaf-style
 * dispatcher operating on caller's stack frame). Split off from the splat-
 * bundled gui_func_000015F4 in a prior tick (the original symbol included
 * a 10-insn wrapper at 0x15F4 plus this whole 4 KB block; split-fragments.py
 * separated them). 11 internal `jr ra` early-exits - single LOGICAL function
 * with multi-path dispatch (per feedback_split_fragments_overswallow_internal_jr_ra.md,
 * recursive splitting was rejected - these are not separate functions).
 *
 * ENTRY (insns 1-21 @ 0x161C-0x166C, decoded 2026-05-02):
 *   void f0(int *a0, int unused_a1, int delta) {
 *     // Main loop: walk 0x14-stride entries in *(int*)(a0+0x20),
 *     //  for each entry, *(int*)(entry+0xC) gets the value loaded back +delta
 *     int n = a0[0];                                   // count at offset 0
 *     int i = 0; int idx = 0;
 *     for (i = 0; i < n; i++) {
 *       int *base = (int*)(*(char**)(a0 + 0x20) + idx);
 *       int *cell = (int*)((char*)base + 0xC);         // entry+0xC, modified
 *       int prev = *cell;                              // *cell read first
 *       *cell = prev + delta;                          // write back+delta
 *       idx += 0x14;
 *     }
 *     a0[3] += delta;                                  // a0+0xC += delta
 *   }
 *   This is "shift-all-glyph-table-entries by delta" - likely a kerning or
 *   advance-width adjustment after a font/text setting change. Returns at
 *   0x1668 jr ra.
 *
 * BODY (insns 22-1048): 10 more dispatch sub-functions with internal
 *   back-jumps and shared register state (no local prologues). Heavy float
 *   math from ~0x16A4 onward (matrix/quaternion display-list construction).
 *
 * Multi-tick decomp; the entry sub-function (this symbol, 0x161C-0x166C,
 * 21 insns) is now a real structural decode below — a per-element field
 * accumulate loop. Caps below exact: target keeps the byte-offset in the
 * loop-induction reg ($a1, += 0x14) and walks the pointer (`v1 += 0xC; sw
 * at v1+0`), whereas the natural C emits a separate offset var + direct
 * `p->0xC` store (20 vs 21 insns, register-layout diff). INCLUDE_ASM is
 * the build path; NM body documents the loop. */
void gui_func_0000161C(int *a0, int a1) {
    int i = 0;
    int off = 0;
    if (*a0 > 0) {
        do {
            int *p = (int *)((char *)a0[0x20 / 4] + off);
            *(int *)((char *)p + 0xC) = *(int *)((char *)p + 0xC) + a1;
            off += 0x14;
            i++;
        } while (i < *a0);
    }
    a0[0xC / 4] = a0[0xC / 4] + a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000161C);
#endif

/* 0x1670 is a single alignment nop between gui_func_0000161C and the real
 * function at 0x1674 — splat mis-placed the gui_uso_func_00001670 symbol on the
 * pad (and over-split the loop tail into 0000168C). Declared as a local pad; the
 * true function is gui_uso_func_00001674 below. */
#pragma GLOBAL_ASM("asm/nonmatchings/gui_uso/gui_uso/gui_func_0000161C_pad.s")

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
 * alpha arg live in $7; our allocator instead spills $7 to 12(sp) (+2 insns),
 * renumbering all temps. INCLUDE_ASM stays the build path. */
#ifdef NON_MATCHING
void gui_uso_func_000017DC(int a0, int a1, float *col, int alpha) {
    int *rec = *(int **)&D_00000000;
    int *sub;
    int count;
    int *arr;
    int r0, r1, r2;

    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFC309A61; arr[1] = 0xFF37FFFF;

    rec = *(int **)&D_00000000;
    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFB000000; arr[1] = a1 & 0xFF;

    rec = *(int **)&D_00000000;
    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFA000000;
    r0 = (int)(unsigned)(col[0] * 255.0f);
    r1 = (int)(unsigned)(col[1] * 255.0f);
    r2 = (int)(unsigned)(col[2] * 255.0f);
    arr[1] = (alpha & 0xFF) | (r0 << 24) | ((r1 & 0xFF) << 16) | ((r2 & 0xFF) << 8);
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
    int *rec = *(int **)&D_00000000;
    int *sub;
    int count;
    int *arr;
    int r0;
    int r1;
    int r2;

    (void)&a0;
    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFC11EA23;
    arr[1] = 0xFFD7FFFF;

    rec = *(int **)&D_00000000;
    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFB000000;
    arr[1] = a1 & 0xFF;

    rec = *(int **)&D_00000000;
    sub = (int *)rec[3];
    count = sub[1];
    sub[1] = count + 1;
    arr = (int *)(((int *)rec[3])[0] + count * 8);
    arr[0] = 0xFA000000;
    r0 = (int)(unsigned)(col[0] * 255.0f);
    r1 = (int)(unsigned)(col[1] * 255.0f);
    r2 = (int)(unsigned)(col[2] * 255.0f);
    arr[1] = (alpha & 0xFF) | (r0 << 24) | ((r1 & 0xFF) << 16) | ((r2 & 0xFF) << 8);
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
/* gui_func_000027A0: 260-insn / 0x410 multi-flag dispatcher. Likely a text/glyph
 * positioning helper given its location in gui_uso (similar shape to nearby
 * text-rendering functions).
 *
 * ENTRY DECODE (0x27A0-0x2820, ~24 insns):
 *   Args: (a0=widget?, a1=x, a2=*, a3=flags)
 *   Saves s0-s7, s8 (8 saved regs); 0x78-byte frame.
 *   s0 = a0; s8 = a1 (x position cached)
 *   if (a3 & 4) {
 *       v0 = a0[4];                      // a0->field_10
 *       a1 = (s16)v0[0x10];               // signed-half load
 *       s8 -= a1;                          // shift x position
 *       goto common;
 *   }
 *   if (!(a3 & 1)) {
 *       // a3 lacks bit-1: alternative arm (continues at 0x281C+)
 *   } else {
 *       v0 = s0[4];
 *       a1 = (s16)v0[0x10];
 *       // ... continues
 *   }
 * common:
 *   ... (large body, decoded in future passes)
 *
 * Saves & frame layout (sp+0x78):
 *   ra:   sp+0x54
 *   s8:   sp+0x50
 *   s7-s0: sp+0x4C..0x30 (decreasing offsets in declared order)
 *   a2 spill: sp+0x80 (caller-arg-save slot)
 *
 * 256+ insns of body decode deferred - multi-pass NM. Default build still
 * uses INCLUDE_ASM via #else; this wrap captures the entry signature and
 * the bit-4/bit-1/bit-2 flag-dispatch shape for next pass. */
/* 2026-05-07: entry-stage decode (insns 0-40 / 0x00-0xA8).
 *
 * The bit-4/bit-1/bit-2 dispatch resolves x/y adjustments BEFORE the
 * shared body. The signed-half-load + bgtz-or-add-then-sra pattern is
 * "x - rounded_half" — taking a0->field_10's halfword field and
 * subtracting (val + (val<0 ? 1 : 0)) >> 1 from x_pos:
 *
 *   if (a3 & 4) {
 *       a1_h = (s16)a0->[0x10]->[0x20];
 *       x_pos -= a1_h;                    // FULL value subtracted
 *       goto common;
 *   }
 *   if (a3 & 1) {
 *       a1_h = (s16)a0->[0x10]->[0x20];
 *       x_pos -= (a1_h + (a1_h <= 0 ? 1 : 0)) >> 1;  // HALF (rounded)
 *   }
 *   if (a3 & 2) {
 *       a1_h = (s16)a0->[0x10]->[0x22];
 *       a2 -= (a1_h + (a1_h <= 0 ? 1 : 0)) >> 1;  // HALF (rounded)
 *   }
 *  common:
 *   ... 220 more insns of body ...
 *
 * The "bgtz + add 1 + sra 1" is the standard signed-int divide-by-2
 * with round-to-nearest-toward-zero correction. Confirms a1_h is
 * signed (lh, not lhu).
 *
 * 220+ insns of body still TODO. Default INCLUDE_ASM keeps ROM exact. */
extern int D_27A0_fn1032, D_27A0_fn272, D_27A0_fn288, D_27A0_fndef;
void gui_func_000027A0(int *a0, int a1, int a2, int a3) {
    int *p;
    int a1_h;
    if (a3 & 4) {
        p = (int*)a0[0x10 / 4];
        a1_h = *(short*)((char*)p + 0x20);
        a1 -= a1_h;
    } else {
        if (a3 & 1) {
            p = (int*)a0[0x10 / 4];
            a1_h = *(short*)((char*)p + 0x20);
            if (a1_h <= 0) a1_h += 1;
            a1 -= a1_h >> 1;
        }
        if (a3 & 2) {
            p = (int*)a0[0x10 / 4];
            a1_h = *(short*)((char*)p + 0x22);
            if (a1_h <= 0) a1_h += 1;
            a2 -= a1_h >> 1;
        }
    }
    {
        int *gctx = *(int **)&D_00000000;
        int *dl = (int *)gctx[0xC / 4];
        int idx = dl[1];
        dl[1] = idx + 1;
        {
            int *slot = (int *)(((int *)gctx[0xC / 4])[0]) + idx * 2;
            slot[0] = 0xBB000001;
            slot[1] = (int)0x80008000;
        }
    }
    {
        int *a3v = (int *)a0[0x10 / 4];
        int mode = a3v[0x24 / 4];
        int (*render_fn)();
        int v1, w, h;
        if (mode == 1032) { v1 = 4096; render_fn = (int (*)())&D_27A0_fn1032; }
        else if (mode == 272) { v1 = 2048; render_fn = (int (*)())&D_27A0_fn272; }
        else if (mode == 288) { v1 = 1024; render_fn = (int (*)())&D_27A0_fn288; }
        else { v1 = 2048; render_fn = (int (*)())&D_27A0_fndef; }
        w = *(short *)((char *)a3v + 0x20);
        h = *(short *)((char *)a3v + 0x22);
        if (v1 >= w * h) {
            render_fn(*(int **)&D_00000000, a3v[8 / 4], w, h, 0, 0, w, h, 0);
            gl_func_00000000(*(int **)&D_00000000, a1, a2, w, h, (w << 10) / w, (h << 10) / h);
        } else {
            int cols = v1 / h;
            int acc = 0;
            int tile = gl_func_00000000(cols);
            int rem = w;
            int s4 = (h << 10) / h;
            if (w != 0) {
                while (rem != 0) {
                    if (tile < rem) {
                        int s3 = (tile << 10) / tile;
                        render_fn(*(int **)&D_00000000, ((int *)a0[0x10 / 4])[8 / 4], w, h, acc, 0, tile, h, 0);
                        gl_func_00000000(*(int **)&D_00000000, a1, a2, tile, h, s3, s4);
                        a1 += tile;
                        acc += tile;
                        rem -= tile;
                    } else {
                        int t0 = (rem << 10) / rem;
                        render_fn(*(int **)&D_00000000, ((int *)a0[0x10 / 4])[8 / 4], w, h, acc, 0, rem, h, 0);
                        gl_func_00000000(*(int **)&D_00000000, a1, a2, rem, h, t0, s4);
                        rem = 0;
                    }
                }
            }
        }
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
    int *s7 = (int *)&D_00000000;
    int *ctx = *(int **)s7;
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
    s32 sp3C;
    s32 sp38;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f14;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v0_3;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_t0;
    s16 var_t0_2;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_s0_2;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0_3;
    s32 var_t1;
    s32 var_v0;
    s32 var_v1;
    void **var_t3;
    char *temp_a0_4;
    char *temp_a3;
    char *temp_s0;
    char *temp_s0_3;
    char *temp_s0_4;
    char *temp_s0_5;
    char *temp_t0;
    char *temp_t1;
    char *temp_t2;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_4;
    char *temp_v0_7;

    var_t3 = g;
    temp_s0 = (*(s32 *)g);
    temp_v0 = (*(s32 *)(temp_s0 + 0xC));
    temp_v1 = (*(s32 *)(temp_v0 + 0x4));
    (*(s32 *)(temp_v0 + 0x4)) = (s32) (temp_v1 + 1);
    temp_a3 = (*(s32 *)((char *)(*(s32 *)(temp_s0 + 0xC)) + 0x0)) + (temp_v1 * 8);
    (*(s32 *)(temp_a3 + 0x0)) = 0xBB000001;
    (*(s32 *)(temp_a3 + 0x4)) = 0x80008000;
    temp_t0 = (*(s32 *)(arg0 + 0x10));
    sp3C = (s32) (*(s32 *)(temp_t0 + 0x20));
    sp38 = (s32) (*(s32 *)(temp_t0 + 0x22));
    temp_s0_2 = (*(s32 *)(temp_t0 + 0x24));
    switch (temp_s0_2) {                            /* irregular */
    case 0x408:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
block_7:
        var_t3 = g;
        break;
    case 0x120:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        goto block_7;
    case 0x110:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t0 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        goto block_7;
    }
    temp_s0_3 = *var_t3;
    temp_v0_2 = (*(s32 *)(temp_s0_3 + 0xC));
    var_t0 = 0;
    temp_v1_2 = (*(s32 *)(temp_v0_2 + 0x4));
    (*(s32 *)(temp_v0_2 + 0x4)) = (s32) (temp_v1_2 + 1);
    temp_f0 = (f32) sp3C;
    var_s0 = 0;
    temp_t1 = (*(s32 *)((char *)(*(s32 *)(temp_s0_3 + 0xC)) + 0x0)) + (temp_v1_2 * 8);
    temp_f12 = temp_f0 * arg3;
    temp_f4 = (s32) ((f32) arg1 + (-(temp_f0 / 2.0f) * arg3));
    temp_f0_2 = (f32) sp38;
    temp_a0 = (temp_f4 + (s32) temp_f12) * 4;
    if (temp_a0 > 0) {
        var_s0 = temp_a0;
    }
    temp_f14 = temp_f0_2 * arg4;
    var_s0_2 = 0;
    temp_a1 = temp_f4 * 4;
    temp_f10 = (s32) ((f32) arg2 + (-(temp_f0_2 / 2.0f) * arg4));
    temp_v0_3 = (temp_f10 + (s32) temp_f14) * 4;
    temp_a2 = temp_f10 * 4;
    if (temp_v0_3 > 0) {
        var_t0 = temp_v0_3;
    }
    (*(s32 *)(temp_t1 + 0x0)) = (s32) (((var_s0 & 0xFFF) << 0xC) | 0xE4000000 | (var_t0 & 0xFFF));
    if (temp_a1 > 0) {
        var_s0_2 = temp_a1;
    }
    if (temp_a2 > 0) {
        var_t0_2 = temp_a2;
    } else {
        var_t0_2 = 0;
    }
    (*(s32 *)(temp_t1 + 0x4)) = (s32) (((var_s0_2 & 0xFFF) << 0xC) | (var_t0_2 & 0xFFF));
    temp_s0_4 = *var_t3;
    temp_v0_4 = (*(s32 *)(temp_s0_4 + 0xC));
    temp_v1_3 = (*(s32 *)(temp_v0_4 + 0x4));
    (*(s32 *)(temp_v0_4 + 0x4)) = (s32) (temp_v1_3 + 1);
    temp_t2 = (*(s32 *)((char *)(*(s32 *)(temp_s0_4 + 0xC)) + 0x0)) + (temp_v1_3 * 8);
    (*(s32 *)(temp_t2 + 0x0)) = 0xB4000000;
    if (temp_a1 < 0) {
        var_t1 = (s32) (((f32) (sp3C - 1) * 1024.0f) / temp_f12);
        if ((s16) var_t1 < 0) {
            temp_a0_2 = (s32) (temp_a1 * (s16) var_t1) >> 7;
            if (temp_a0_2 > 0) {
                var_s0_3 = temp_a0_2;
            } else {
                var_s0_3 = 0;
            }
        } else {
            var_v0 = 0;
            temp_a0_3 = (s32) (temp_a1 * (s16) var_t1) >> 7;
            if (temp_a0_3 < 0) {
                var_v0 = temp_a0_3;
            }
            var_s0_3 = var_v0;
        }
    } else {
        var_s0_3 = 0;
        var_t1 = (s32) (((f32) (sp3C - 1) * 1024.0f) / temp_f12);
    }
    if (temp_f10 & 0x20000000) {
        var_t3 = g;
        var_a2 = (s32) (((f32) (sp38 - 1) * 1024.0f) / temp_f14);
        if ((s16) var_a2 < 0) {
            var_a1 = 0;
            temp_v0_5 = (s32) (temp_a2 * (s16) var_a2) >> 7;
            if (temp_v0_5 > 0) {
                var_t3 = g;
                var_a1 = temp_v0_5;
            } else {
                var_t3 = g;
            }
        } else {
            var_v1 = 0;
            temp_v0_6 = (s32) (temp_a2 * (s16) var_a2) >> 7;
            if (temp_v0_6 < 0) {
                var_v1 = temp_v0_6;
            }
            var_a1 = var_v1;
        }
    } else {
        var_a1 = 0;
        var_a2 = (s32) (((f32) (sp38 - 1) * 1024.0f) / temp_f14);
    }
    (*(s32 *)(temp_t2 + 0x4)) = (s32) ((var_s0_3 * -0x10000) | (-var_a1 & 0xFFFF));
    temp_s0_5 = *var_t3;
    temp_v0_7 = (*(s32 *)(temp_s0_5 + 0xC));
    temp_v1_4 = (*(s32 *)(temp_v0_7 + 0x4));
    (*(s32 *)(temp_v0_7 + 0x4)) = (s32) (temp_v1_4 + 1);
    temp_a0_4 = (*(s32 *)((char *)(*(s32 *)(temp_s0_5 + 0xC)) + 0x0)) + (temp_v1_4 * 8);
    (*(s32 *)(temp_a0_4 + 0x4)) = (s32) ((var_t1 << 0x10) | (var_a2 & 0xFFFF));
    (*(s32 *)(temp_a0_4 + 0x0)) = 0xB3000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002DE0);
#endif

#ifdef NON_MATCHING
void gui_func_0000329C(char *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    char *g = (char *)&D_00000000;
    s32 sp3C;
    s32 sp38;
    f32 temp_f0;
    f32 temp_f2;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v0_3;
    s16 var_s0;
    s16 var_s0_2;
    s16 var_t2;
    s16 var_t2_2;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_f6;
    s32 temp_f8;
    s32 temp_s0_2;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0_3;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    void **var_t3;
    char *temp_a0_4;
    char *temp_s0;
    char *temp_s0_3;
    char *temp_s0_4;
    char *temp_s0_5;
    char *temp_t0;
    char *temp_t0_2;
    char *temp_t1;
    char *temp_t2;
    char *temp_v0;
    char *temp_v0_2;
    char *temp_v0_4;
    char *temp_v0_7;

    var_t3 = g;
    temp_s0 = (*(s32 *)g);
    temp_v0 = (*(s32 *)(temp_s0 + 0xC));
    temp_v1 = (*(s32 *)(temp_v0 + 0x4));
    (*(s32 *)(temp_v0 + 0x4)) = (s32) (temp_v1 + 1);
    temp_t0 = (*(s32 *)((char *)(*(s32 *)(temp_s0 + 0xC)) + 0x0)) + (temp_v1 * 8);
    (*(s32 *)(temp_t0 + 0x0)) = 0xBB000001;
    (*(s32 *)(temp_t0 + 0x4)) = 0x80008000;
    temp_t2 = (*(s32 *)(arg0 + 0x10));
    sp3C = (s32) (*(s32 *)(temp_t2 + 0x20));
    sp38 = (s32) (*(s32 *)(temp_t2 + 0x22));
    temp_s0_2 = (*(s32 *)(temp_t2 + 0x24));
    switch (temp_s0_2) {                            /* irregular */
    case 0x408:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
block_7:
        var_t3 = g;
        break;
    case 0x120:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        goto block_7;
    case 0x110:
        gui_func_00000000((*(s32 *)g), (*(s32 *)(temp_t2 + 0x8)), sp3C, sp38, 0, 0, sp3C, sp38, 0);
        goto block_7;
    }
    temp_s0_3 = *var_t3;
    var_t2 = 0;
    temp_v0_2 = (*(s32 *)(temp_s0_3 + 0xC));
    temp_v1_2 = (*(s32 *)(temp_v0_2 + 0x4));
    (*(s32 *)(temp_v0_2 + 0x4)) = (s32) (temp_v1_2 + 1);
    temp_t0_2 = (*(s32 *)((char *)(*(s32 *)(temp_s0_3 + 0xC)) + 0x0)) + (temp_v1_2 * 8);
    temp_f0 = (f32) (arg3 - arg1);
    var_s0 = 0;
    temp_f8 = (s32) (f32) arg1;
    temp_f2 = (f32) (arg4 - arg2);
    temp_a0 = (temp_f8 + (s32) temp_f0) * 4;
    temp_a1 = temp_f8 * 4;
    if (temp_a0 > 0) {
        var_s0 = temp_a0;
    }
    temp_f6 = (s32) (f32) arg2;
    var_s0_2 = 0;
    temp_v0_3 = (temp_f6 + (s32) temp_f2) * 4;
    temp_a2 = temp_f6 * 4;
    if (temp_v0_3 > 0) {
        var_t2 = temp_v0_3;
    }
    (*(s32 *)(temp_t0_2 + 0x0)) = (s32) (((var_s0 & 0xFFF) << 0xC) | 0xE4000000 | (var_t2 & 0xFFF));
    if (temp_a1 > 0) {
        var_s0_2 = temp_a1;
    }
    if (temp_a2 > 0) {
        var_t2_2 = temp_a2;
    } else {
        var_t2_2 = 0;
    }
    (*(s32 *)(temp_t0_2 + 0x4)) = (s32) (((var_s0_2 & 0xFFF) << 0xC) | (var_t2_2 & 0xFFF));
    temp_s0_4 = *var_t3;
    temp_v0_4 = (*(s32 *)(temp_s0_4 + 0xC));
    temp_v1_3 = (*(s32 *)(temp_v0_4 + 0x4));
    (*(s32 *)(temp_v0_4 + 0x4)) = (s32) (temp_v1_3 + 1);
    temp_t1 = (*(s32 *)((char *)(*(s32 *)(temp_s0_4 + 0xC)) + 0x0)) + (temp_v1_3 * 8);
    (*(s32 *)(temp_t1 + 0x0)) = 0xB4000000;
    if (temp_a1 < 0) {
        var_t0 = (s32) (((f32) (sp3C - 1) * 1024.0f) / temp_f0);
        if ((s16) var_t0 < 0) {
            temp_a0_2 = (s32) (temp_a1 * (s16) var_t0) >> 7;
            if (temp_a0_2 > 0) {
                var_s0_3 = temp_a0_2;
            } else {
                var_s0_3 = 0;
            }
        } else {
            var_v0 = 0;
            temp_a0_3 = (s32) (temp_a1 * (s16) var_t0) >> 7;
            if (temp_a0_3 < 0) {
                var_v0 = temp_a0_3;
            }
            var_s0_3 = var_v0;
        }
    } else {
        var_s0_3 = 0;
        var_t0 = (s32) (((f32) (sp3C - 1) * 1024.0f) / temp_f0);
    }
    if (temp_f6 & 0x20000000) {
        var_a2 = (s32) (((f32) (sp38 - 1) * 1024.0f) / temp_f2);
        if ((s16) var_a2 < 0) {
            temp_v0_5 = (s32) (temp_a2 * (s16) var_a2) >> 7;
            if (temp_v0_5 > 0) {
                var_a1 = temp_v0_5;
            } else {
                var_a1 = 0;
            }
        } else {
            var_v1 = 0;
            temp_v0_6 = (s32) (temp_a2 * (s16) var_a2) >> 7;
            if (temp_v0_6 < 0) {
                var_v1 = temp_v0_6;
            }
            var_a1 = var_v1;
        }
    } else {
        var_a1 = 0;
        var_a2 = (s32) (((f32) (sp38 - 1) * 1024.0f) / temp_f2);
    }
    (*(s32 *)(temp_t1 + 0x4)) = (s32) ((var_s0_3 * -0x10000) | (-var_a1 & 0xFFFF));
    temp_s0_5 = (*(s32 *)g);
    temp_v0_7 = (*(s32 *)(temp_s0_5 + 0xC));
    temp_v1_4 = (*(s32 *)(temp_v0_7 + 0x4));
    (*(s32 *)(temp_v0_7 + 0x4)) = (s32) (temp_v1_4 + 1);
    temp_a0_4 = (*(s32 *)((char *)(*(s32 *)(temp_s0_5 + 0xC)) + 0x0)) + (temp_v1_4 * 8);
    (*(s32 *)(temp_a0_4 + 0x4)) = (s32) ((var_t0 << 0x10) | (var_a2 & 0xFFFF));
    (*(s32 *)(temp_a0_4 + 0x0)) = 0xB3000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000329C);
#endif

#ifdef NON_MATCHING
/* gui_func_00003714: 256-insn / 0x400 RDP DL builder (originally bundled
 * with a 27-insn trailing helper at 0x3B14, split-fragments output
 * already INCLUDE_ASM-wired below).
 *
 * Same family entry shape as gui_func_0000329C / gui_func_00002DE0 /
 * gui_func_00002BB0 — D_GUI_CTX deref, cursor bump on ctx[0xC]->[1],
 * RDP 0xBB000001 + 0x80008000 segment-marker emit at slot 0.
 *
 * 4-arg signature, frame to be characterized in next pass. Multi-pass
 * NM remains. Default INCLUDE_ASM keeps ROM exact. */
void gui_func_00003714(int *a0, int a1, int a2, int a3) {
    /* TODO: full body decode. Stub captures arg signature and
     * RDP-builder family identity. Body has ~256 insns. */
    (void)a0; (void)a1; (void)a2; (void)a3;
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
/* Whole-body decode 2026-06-01 (was 1.81% stub). Paginated RDP texture-DL
 * builder: D_GUI_CTX deref + RDP 0xBB000001/0x80008000 marker emit, switch on
 * a0->0xc selecting a row-emit fn-ptr (sp+92) + max-bytes-per-page, then split
 * a0->8 (height) into pages of (max/height) rows — per-page frow(ctx,..)+gl(..)
 * calls, with a single-page fast path when width*height fits. Stack-arg/loop
 * details approximate; multi-tick remainder. */
void gui_func_00003B80(int *a0, int a1, int a2, int a3) {
    int *s7 = (int *)&D_00000000;
    int *ctx = *(int **)s7;
    int *s5 = a0;
    int s8 = 0;
    int s2, s0, s3, s1;
    int max;
    void (*frow)();

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
    switch (a0[0xC / 4]) {
    case 0:  frow = (void (*)())&D_3B80_f0; max = 4096; break;
    case 1:  frow = (void (*)())&D_3B80_f1; max = 2048; break;
    case 2:  frow = (void (*)())&D_3B80_f2; max = 1024; break;
    default: frow = 0;                      max = a3;   break;
    }
    s2 = a0[4 / 4];   /* width  */
    s0 = a0[8 / 4];   /* height */
    if (s2 * s0 > max) {
        s1 = gl_func_00000000(max / s0);   /* rows per page */
        s3 = s0;                            /* height */
        s0 = a0[4 / 4];                     /* width as page counter */
        while (s0 != 0) {
            if (s1 < s0) {
                frow(ctx, a0[0], s2, a0[8 / 4], 0, s8, 0, s1, s3, 0);
                gl_func_00000000(ctx, a1, a2, s1, s3, (s1 << 10) / s1, (s3 << 10) / s3);
                s8 += s1;
                s0 -= s1;
                a1 += s1;
            } else {
                frow(ctx, a0[0], s2, a0[8 / 4], 0, s8, 0, s0, s3, 0);
                gl_func_00000000(ctx, a1, a2, s0, s3, (s0 << 10) / s0);
                s0 -= s1;
            }
        }
    } else {
        frow(ctx, a0[0], s2, s0, 0, 0, s2, s0, 0);
        gl_func_00000000(ctx, a1, a2, s2, s0, (s2 << 10) / s2, (s0 << 10) / s0);
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
