#include "common.h"

#ifdef NON_MATCHING
/* USO entry-0: character-to-glyph-index converter (82 insns / 0x148).
 * Leading 0x1000736F trampoline (loader-patched) + a bnel-chain dispatch.
 *
 * 2026-05-05 retry: PREFIX_BYTES injection now WORKS (script's
 * VALID_ENTRY_OPCODES list accepts opcode 0x0C `andi`, the previous
 * blocker comment was outdated). Added Makefile entry:
 *   build/src/gui_uso/gui_uso.c.o: PREFIX_BYTES := gui_func_00000000=0x1000736F
 *
 * Remaining structural blocker: target's entry has `sw a0, 0(sp)` in the
 * trampoline's delay slot (caller arg-save area at sp+0). IDO -O2 elides
 * this from the K&R-form C body since `c` isn't address-taken inside the
 * function body. Tried standard prototype `int gui_func_00000000(int c)`
 * - breaks 2-arg callers (gui_func_000013E8 et al pass 2 args). Tried
 * `int tmp = c;` - folded by IDO.
 *
 * 2026-05-05: tested `int gui_func_00000000(int c, ...)` (varargs) at
 * both def and all 3 extern decl sites (305/337/403). Build succeeded
 * but match dropped from K&R baseline to 4.1% (built 0x128 vs expected
 * 0x148, -8 insns). The varargs form makes IDO's calling convention
 * for `c` change in a way that REGRESSES on the bnel-chain emit, not
 * helps. Don't re-attempt - neither standard prototype, K&R nudge, nor
 * varargs solves the trampoline-`sw a0, 0(sp)` blocker.
 *
 * 2026-05-06: tested 8-byte PREFIX_BYTES (extending to include the
 * `sw a0, 0(sp)` delay slot at 0xAFA40000): no help for objdiff scoring.
 * Reason: the inject runs on `build/src/` only (where INCLUDE_ASM path
 * already supplies these bytes via the .s file). objdiff compares
 * `build/non_matching/.o` to `expected/.o`; non_matching builds DONT
 * receive PREFIX_BYTES injection. The C body bnel-chain emits 71
 * insns (0x11C) vs target 82 (0x148) - the structural cap is the
 * 11-insn delta, not the 2-insn prefix. Reverted Makefile to single-word
 * PREFIX_BYTES (the 4-byte trampoline alone). The function IS byte-exact
 * in the actual ROM build via INCLUDE_ASM tautology; objdiff 4.1%
 * score is the documented .NON_MATCHING-build scoring quirk per
 * docs/MATCHING_WORKFLOW.md#feedback-byte-correct-match-via-include-asm-not-c-body.
 *
 * Stub C body decoded but NM wrap stays - default build INCLUDE_ASM is
 * correct bytes via the .s file. Multi-pass decomp; the bnel-chain emit
 * for the special-char branches is the last-mile blocker. */
int gui_func_00000000(c)
int c;
{
    c &= 0xFF;
    if (c == 0x21) return 0x27;
    if (c == 0x2C) return 0x28;
    if (c == 0x2F) return 0x29;
    if (c == 0x5B) return 0x26;
    if (c == 0x5D) return 0x27;
    if (c == 0x2B) return 0x24;
    if (c == 0x5F) return 0x25;
    if (c == 0x2E) return 0x25;
    if (c == 0x2D) return 0x25;
    if (c >= 0x61 && c < 0x7B) return (c - 0x57) & 0xFF;
    if (c >= 0x41 && c < 0x5B) return (c - 0x37) & 0xFF;
    if (c >= 0x30 && c < 0x3A) return (c - 0x30) & 0xFF;
    return c;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000000);
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
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000148);

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

    v0 = gl_func_00000000(a3);  /* string length */
    if (v0 == 0) return;
    s7 = 0;
    do {
        unsigned char c = *s6;
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
            /* RDP cmd 2: glyph render - s2/saved_a2 with s5=1024 scaling */
            gl_func_00000000(s1[0x24 / 4], s2, a2, g2,
                             /* sp+0x10 */ s3, /*s5=*/1024, /*1024=*/1024);
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
void gui_func_00000D04(int *a0, int *a1, int a2, char *a3) {
    /* TODO partial decode - full body 128 insns; stub for grep+wrap discoverability */
    int *cmd_state = (int*)a0[0x24/4];
    int *cmd_list = (int*)cmd_state[0xC/4];
    int idx = cmd_list[1];
    int *slot;
    cmd_list[1] = idx + 1;
    slot = (int*)((char*)cmd_list[0] + idx * 8);
    slot[0] = 0xBB000001;
    slot[1] = 0x80008000;
    if (gl_func_00000000(a3) == 0) return;
    /* TODO: text rendering loop (~100 insns) */
    (void)a1; (void)a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000D04);
#endif

/* gui_func_00000F04: 314-insn / 0x4E4 FPU-heavy coordinate transform.
 * Big stack frame (-0x108), saves s0-s7+fp+ra, lots of saved FP regs
 * (f20/f22/f24/f26/f28/f30 spilled to sp+0x30..0x48 - 6 doubles spilled).
 *
 * Function entry pattern (first 30 insns):
 *   - prologue: alloc 0x108, save 14 saved-regs (s0-s7+s7+fp+ra) + 6 dbl
 *     FP regs (f20..f30) - total of 20 callee-saves
 *   - lwc1/swc1 of $f12 to sp+offset (FP ARG passed in!) - caller passes
 *     1 float arg in $f12 + 2 int args in a0/a1
 *   - 16-bit constants: 0xBB00 (loaded with lui), 0x80008000 (lui+ori for
 *     bit-rotate or sign-extend mask)
 *   - dispatch table read: a0->0x14 (= struct ptr s6),
 *     a0->0x14->0xC (= ptr a3, table of glyph entries)
 *   - update count at a0->0x14->0x4: ++a0->0x14->0x4 - append new entry
 *   - allocates one entry of (a0->0x14->0xC[N]) - N is shifted by 12
 *     (0x0003C8C0 = sll v1, v1, 3 - index by stride 8?)
 *   - jal cross-USO callee with a1 = sp+0x11C (caller-arg slot)
 *
 * Structure inferred: this is likely a glyph-emit / draw-call recorder
 * function. Takes (a0=context, a1=str-or-glyph-ptr, $f12=float, ...) and
 * appends an entry to a draw-call buffer at a0->0x14, with FPU
 * coordinate transformation to derive the entry's data.
 *
 * Multi-tick decomp target. Strategy: type the draw-call buffer struct
 * first (the +0x4 count, +0xC ptr, +0x10 cap fields are visible across
 * 5+ gui_uso functions). Initial INCLUDE_ASM-only commit; structural
 * decode comment added for next pass. */
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000F04);

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
 * Multi-tick decomp; this commit captures the entry sub-function only as
 * stub documentation. Default build still matches via INCLUDE_ASM. */
void gui_func_0000161C(void) {
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000161C);
#endif

extern int gl_func_00000000();
extern int gui_ref_00000150;

void gui_func_0000267C(char *a0, int a1) {
    int saved;
    *(int*)(a0 + 0x14) = a1;
    saved = gl_func_00000000(7);
    *(int*)(a0 + 0x10) = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
    gl_func_00000000(saved);
}

void gui_func_000026CC(int *a0, int a1) {
    a0[5] = a1;
    a0[4] = 0;
}

extern int gui_func_00000000();
extern int gui_ref_00000150;

void gui_func_000026D8(char *a0) {
    if (*(int*)(a0 + 0x10) != 0) {
        gui_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14), a0);
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
    v0 = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
    v1 = *(int*)(a0 + 0x10);
    if (v1 == 0 || v0 != v1) {
        *(int*)(a0 + 0x10) = gl_func_00000000(gui_ref_00000150, *(int*)(a0 + 0x14));
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
    /* TODO: 220-insn body — display-list builder for the adjusted
     * (a1, a2) coordinates, using a0->[0x10]->[various] glyph metrics. */
    (void)a0; (void)a1; (void)a2;
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
void gui_func_00002BB0(int *a0, int a1, int a2, int a3, int a4_stack) {
    int *ctx;
    int *p;
    int slot, idx;
    int sub_ctx_field;  /* a0->[0x10]->[0x20] (s16) */
    (void)a3; (void)a4_stack; (void)a1;
    /* DL-command emit: RDP 0xBB000001 + 0x80008000 (segment-0 marker) */
    ctx = *(int**)((char*)&D_00000000);  /* s7 = &D_GUI_CTX; ctx = s7[0] */
    idx = ctx[0xC / 4];  /* dl-counter container */
    slot = ((int*)idx)[1];  /* current cursor */
    ((int*)idx)[1] = slot + 1;  /* bump */
    p = (int*)((*(int**)idx)[0]) + (slot << 1);
    p[0] = 0xBB000001;
    p[1] = (int)0x80008000;
    /* Sub-context load + early exit on a4_stack == 0 */
    sub_ctx_field = *(short*)((char*)a0[0x10 / 4] + 0x20);
    (void)sub_ctx_field;
    /* TODO: ~100 more insns of body — second DL command + per-iteration
     * loop emitting tile/vertex/scissor commands using a4_stack as the
     * tile count. Multi-pass NM remains. */
    (void)ctx; (void)a2;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002BB0);
#endif

#ifdef NON_MATCHING
/* gui_func_00002DE0: 303-insn / 0x4BC RDP/RSP display-list builder.
 * Same family as gui_func_00002BB0 (just NM-wrapped sibling) - both
 * load ctx from `&D_GUI_CTX`, bump the display-list write counter, and
 * emit a G_SETSCISSOR (0xBB00_0001) command at ctx[12][0] + count*8.
 *
 * ENTRY DECODE (0x2DE0-0x2E40, ~24 insns):
 *   ctx = *(int**)&D_GUI_CTX;        // s0 = ctx (global ptr deref)
 *   ctx[12]->[4] += 1;               // bump display-list counter
 *   v1_old = pre-bump value
 *   at = 0x408                        // some constant (1032 = 0x408 lookup)
 *   t4 = 0xBB00_0001                  // RDP G_SETSCISSOR opcode
 *   t5 = 0x80008000                   // RDRAM segment-0 base marker
 *   a3 = ctx[12][0] + (v1_old << 3)  // dl_ptr at base + index*8
 *   *a3 = t4                          // RDP cmd word 1
 *   *(a3+4) = t5                      // RDP cmd word 2
 *   t0 = a0[4]                        // (continues - likely viewport/scissor
 *                                       params from arg0 widget struct)
 *
 * 4 args saved to caller-arg-spill at sp+0x6C..0x74 (a1, a2, a3 stack).
 * 1 saved reg (s0) + ra. 0x68-byte frame (smaller than 0x2BB0's 0x70).
 * 280+ insns of body deferred - multi-pass NM-decomp. The 0x408
 * literal (1032) is suspicious - possibly a viewport/scissor scale
 * factor (240*4 = 960; 1024+8 = 1032). Default build INCLUDE_ASM. */
/* 2026-05-08: entry-stage decode (insns 0-24 / 0x00-0x60). Replaces
 * empty stub with the documented 4-arg signature + first DL command
 * emit (RDP 0xBB000001 opcode at slot 0, sibling shape of gui_func_00002BB0).
 *
 * Frame -0x68 (saves s0 + ra). 4 arg signature with a1/a2/a3 spilled to
 * caller-arg-save slots at sp+0x6C/0x70/0x74 (defensive). The 0x408
 * (=1032) literal materialized at insn 0x4C is likely a viewport scale
 * factor used in the per-vertex-emit loop (~280 insns deferred). */
void gui_func_00002DE0(int *a0, int a1, int a2, int a3) {
    int *ctx;
    int *p;
    int slot, idx;
    (void)a1; (void)a2; (void)a3;
    ctx = *(int**)((char*)&D_00000000);  /* s0 = D_GUI_CTX[0] */
    idx = ctx[0xC / 4];                   /* dl-counter container */
    slot = ((int*)idx)[1];                /* current cursor */
    ((int*)idx)[1] = slot + 1;            /* bump */
    p = (int*)((*(int**)idx)[0]) + (slot << 1);
    p[0] = 0xBB000001;                    /* RDP G_SETSCISSOR opcode */
    p[1] = (int)0x80008000;               /* RDRAM segment-0 marker */
    /* TODO: ~280 more insns of body — likely scissor/viewport/vertex
     * setup using a0 widget args + 0x408 (1032) scale factor.
     * Multi-pass NM remains. */
    (void)a0; (void)ctx;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002DE0);
#endif

#ifdef NON_MATCHING
/* gui_func_0000329C: 286-insn / 0x478 RDP DL builder.
 *
 * 2026-05-08 first-pass structural decode: byte-identical entry shape
 * to gui_func_00002DE0 / gui_func_00002BB0 family — *(int**)&D_GUI_CTX
 * deref, cursor bump on ctx[0xC]->[1], RDP 0xBB000001 + 0x80008000
 * segment marker emit at slot 0. 0x408 (1032) literal at insn 0x4C
 * is the same viewport-scale constant as 2DE0.
 *
 * Frame -0x58 (88 bytes — smaller than 2DE0's -0x68 since this fn
 * has fewer body locals). Saves s0 + ra, defensive-spills a1/a2/a3
 * at sp+0x5C/0x60/0x64.
 *
 * 4-arg signature with same shape as 2DE0/2BB0 family.
 *
 * ~270 insns of body deferred — likely scissor/viewport/DL setup
 * sequence using 0x408 viewport scale + a0 widget args. Multi-pass
 * NM remains. Default INCLUDE_ASM keeps ROM exact. */
void gui_func_0000329C(int *a0, int a1, int a2, int a3) {
    int *ctx;
    int *p;
    int slot, idx;
    (void)a1; (void)a2; (void)a3;
    ctx = *(int**)((char*)&D_00000000);
    idx = ctx[0xC / 4];
    slot = ((int*)idx)[1];
    ((int*)idx)[1] = slot + 1;
    p = (int*)((*(int**)idx)[0]) + (slot << 1);
    p[0] = 0xBB000001;
    p[1] = (int)0x80008000;
    /* TODO: ~270 more insns of body. Multi-pass NM. */
    (void)a0; (void)ctx;
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
 * IDO emits the two final `or` instructions in the OPPOSITE order from target
 * (entry[0] computation first vs target's entry[1] first). 2-insn INSN_PATCH
 * at offsets 0x58/0x5C swaps them — see Makefile. Per
 * `docs/POST_CC_RECIPES.md#feedback-insn-patch-for-ido-codegen-caps`. */
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
    entry[0] = 0xF6000000 | ((a3 & 0x3FF) << 14) | ((arg5 & 0x3FF) << 2);
    entry[1] = ((a1 & 0x3FF) << 14) | ((a2 & 0x3FF) << 2);
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
void gui_func_00003B80(int *a0, int a1, int a2, int a3) {
    /* TODO: full body decode. ~230 insns. */
    (void)a0; (void)a1; (void)a2; (void)a3;
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
void gui_uso_func_00003F18(int a0, int a1, int a2, int a3);
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00003F18);
#endif

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_0000413C);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_uso_func_00004354);

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
void gui_func_00004568(int *a0, int a1, int a2, int a3, int y_hi) {
    /* Stub: structural decode of 198-insn TEXRECT DL builder. The
     * complex coord-packing + dual-cmd DL emit + 2 conditional skips
     * need multi-pass decode; this NM wrap captures the 5-arg
     * signature and entry guards as a first-pass anchor. */
    (void)a0; (void)a1; (void)a2; (void)a3; (void)y_hi;
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00004568);
#endif

