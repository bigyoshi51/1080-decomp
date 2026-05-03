#include "common.h"

#ifdef NON_MATCHING
/* USO entry-0: character-to-glyph-index converter (82 insns / 0x148).
 * Leading 0x1000736F trampoline (loader-patched) + a bnel-chain dispatch
 * mapping ASCII chars to glyph indices.
 *
 * Decoded structure:
 *   - First test uses `bne` (not bnel): if c == 0x21 return 0x27.
 *   - Then a chain of bnel cases for special punctuation glyphs.
 *   - Then 3 range checks for 'a'..'z', 'A'..'Z', '0'..'9' (hex-style
 *     remapping with offsets -0x57, -0x37, -0x30).
 *   - Default: return c & 0xFF.
 *
 * Two structural blockers vs target:
 *   1. Leading 4-byte trampoline (PREFIX_BYTES injection unavailable —
 *      tried 2026-05-03; inject-prefix-bytes.py refuses with "first insn
 *      is 0x308400ff, expected addiu sp prologue ... or jr ra ... refusing
 *      to patch". The script only handles functions with a recognized
 *      prologue shape; leaf functions starting with arithmetic (here
 *      `andi a0, a0, 0xFF`) aren't a supported pattern. Would need the
 *      script to relax the prologue check, or a different mechanism.).
 *   2. bnel-chain emit with `li at, NEXT_X` in each delay slot — IDO needs
 *      a specific if-chain pattern (likely goto-chain with shared epilogue
 *      per feedback_ido_dispatch_goto_chain_beats_switch_and_ifelse.md) to
 *      reproduce. Plain `if (c==X) return Y;` chain doesn't trigger bnel.
 *
 * Multi-pass decomp; default build INCLUDE_ASM matches. C body recorded
 * here for reference and as a starting point for the bnel-chain match. */
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

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000148);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000918);

extern int gl_func_00000000();
#ifdef NON_MATCHING
/* gui rendering loop — iterates over a3-derived count, indexes via a0[5]
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
 * Inner loop body (88 insns) — heavy multi-jal iteration over the s7 counter:
 *   - reads from (a0[?] + s7 * 20) using s8 as the stride
 *   - dispatches via 4 separate jals (jal gl_func_00000000 placeholders)
 *   - clamps signed values via `seq -1, neq -1` pattern, sign-extension via
 *     `sll, sra` for byte/short reads
 *   - termination: `s7++; if (s7 < v0) loop;` (sltu + bnel branch likely)
 *
 * Multi-tick decompile; this commit captures structural decode + entry/exit
 * stages. Loop body C TODO. Default build still matches via INCLUDE_ASM. */
void gui_func_00000B58(int *a0, int a1, int a2, int a3) {
    int v0;
    int counter;
    int saved_a2 = a2;
    int saved_a3 = a3;
    int *base = a0;
    int len = a0[5];        /* a0->0x14: stored item count or string length */
    int width = a1;
    int handle = a3;

    v0 = gl_func_00000000(a3);
    if (v0 == 0) return;

    /* TODO: decode 80+ insn loop body. Iterates s7 = 0..v0-1, each iter:
     *   - read base[5+s7*5] (stride-20 indexed via s8=0x14)
     *   - 4× jal gl_func_00000000 dispatching on glyph/key data
     *   - signed-byte sign-extend via sll/sra
     *   - clamp to -1 via slti/seq
     */
    counter = 0;
    do {
        /* TODO: loop body */
        counter++;
    } while (counter < v0);
}
#else
INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000B58);
#endif

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00000D04);

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
 * separated them). 11 internal `jr ra` early-exits — single LOGICAL function
 * with multi-path dispatch (per feedback_split_fragments_overswallow_internal_jr_ra.md,
 * recursive splitting was rejected — these are not separate functions).
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
 *   This is "shift-all-glyph-table-entries by delta" — likely a kerning or
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

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_000027A0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002BB0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00002DE0);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_0000329C);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003714);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00003B80);

INCLUDE_ASM("asm/nonmatchings/gui_uso/gui_uso", gui_func_00004568);

