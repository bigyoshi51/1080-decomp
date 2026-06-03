#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { int a, b, c; } Tri3i;
typedef struct { int a, b; } Pair2;
typedef struct { float x, y, z; } Vec3;
#ifdef NON_MATCHING
#define GL_COUNT_2070 (*(int*)((char*)&D_00000000 + 0x2070))
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00070FCC);

/* game_libs_func_000710F8: 7-insn double-precision polynomial leaf.
 *   f8 = f2 * $f14   ; f4 = f8 * $f16 ; f6 = f4 + f2
 *   return -(float)f6
 * CAP: $f2 (and $f16) are CALLER-SET (read at entry, never loaded). IDO C
 * can't source $f2 as input. Sibling of game_libs_func_0006A2C0 (same
 * caller-set-$f2 double polynomial shape). Permanent INCLUDE_ASM —
 * caller-set-float subclass, feedback_caller_set_int_reg_cap_1080_game_libs. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000710F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00071114);

/* game_libs_func_00071130: 3-insn `lwc1 f0, 0x2520($at); jr ra; nop`.
 * Sibling of game_libs_func_0006A2F8 — same prologue-stolen-successor
 * CAP ($at set by predecessor's `lui $at, %hi(SYM)` tail). Standalone
 * C-emit would emit its own lui+lwc1 (2 insns) → 4-insn func vs target's
 * 3-insn. Was previously PROLOGUE_STEALS-promotable, REMOVED 2026-05-23.
 * Default INCLUDE_ASM remains byte-exact. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00071130);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00070C44_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071144);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00071144_pad.s")

#ifdef NON_MATCHING
/* gl_func_00071304: 27-insn 2-call wrapper. Three distinct extern POINTERS
 * (D_71304_A/B/C), each loaded via lui+lw, then stored to via offset.
 * Applied unique-extern recipe per
 * docs/IDO_CODEGEN.md#feedback-ido-cse-bust-via-distinct-externs.
 *
 * NEAR-MISS (88%, SIZE-MISMATCH: mine 24 insns vs target 27). Logic is exact;
 * the body, store order (a0->D_A+0x10, a1->D_B+0x14, a2->D_C+2), arg-home/reload
 * and the three hoisted lui's all match. The ONLY divergence: the 1st call's
 * result `rv` (passed as the 2nd call's a0). TARGET parks rv in callee-saved
 * $s0 (`or s0,v0` / `or a0,s0`), paying +1 move + `sw/lw s0` + frame 0x18->0x28.
 * Natural -O2 C keeps rv in $v0 and does `move a0,v0` (no s0, frame 0x18) -- a
 * SHORTER, more-optimized body than the target. IDO only promotes a cross-call
 * value to a callee-saved REGISTER when it's used 2+ times after the call; rv is
 * used 0 times after the 2nd call, so no C structure induces the s0 round-trip.
 * NEGATIVE RESULTS (do not repeat, all 2026-05-30, standalone IDO 7.1 -O2):
 *   - `register int rv` / `register int rv asm("$16")`: hint ignored / IDO rejects
 *     gcc register-asm (feedback_ido_no_gcc_register_asm). Still $v0.
 *   - `return rv` (rv live across 2nd call): IDO SPILLS TO STACK (sw $2,28(sp) +
 *     lw), frame 0x20, NOT s0 -- and target doesn't return rv anyway.
 *   - -O1: also stack-spills rv (frame 0x20), not s0.
 *   - rv used twice (stored to D_A AND passed), 2-arg 2nd call, tail-return,
 *     1st-call-takes-(a0,a1,a2), rv-as-pointer-base: all keep rv in $v0 / frame
 *     0x18. The s0-for-single-use-cross-call-arg form is not -O2-reachable. NM. */
extern int *D_71304_A;
extern int *D_71304_B;
extern short *D_71304_C;
void gl_func_00071304(int a0, int a1, int a2) {
    int rv = gl_func_00000000();
    *(int*)((char*)D_71304_A + 0x10) = a0;
    *(int*)((char*)D_71304_B + 0x14) = a1;
    *(short*)((char*)D_71304_C + 2) = (short)a2;
    gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071304);
#endif

/* game_libs_func_00071370: leading-nop FPU-control-reg wrapper
 * (cfc1/ctc1 pair, libreultra __osSetFpcCsr-style). Hand-written MIPS
 * asm; INCLUDE_ASM stays. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00071370);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071384);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00071384_pad.s")

#ifdef NON_MATCHING
/* gl_func_00071624: 57-insn multi-stage status query + decision tree (size 0xE4, frame 0x28).
 *
 * Probes subsystem state via 6 jal calls (likely controller / save-data /
 * Controller-Pak status queries), then maps the result bit-flags into a
 * return status code.
 *
 * Decoded structure (raw-word disasm):
 *   int status_query(void *a0_state, void *a1_target) {
 *       int saved_v0 = 0;
 *       hook1(a1_target);                              // jal #1
 *       saved_v0 = hook2(1, &D_00000000);              // jal #2 — returns "default" status
 *       hook3(a0_state, &sp_buf_20, 1);                // jal #3 — write status to buf[0x20]
 *       saved_v0 = hook4(0, &D_00000000);              // jal #4 — get current status
 *       hook5(a0_state, &sp_buf_1C, 1);                // jal #5 — write status to buf[0x1C]
 *       hook6(a1_target, &sp_buf_1C);                  // jal #6 — finalize
 *
 *       uint8_t flags_1E = *(uint8_t*)(sp + 0x1E);
 *       uint8_t flags_1F = *(uint8_t*)(sp + 0x1F);
 *
 *       // Decision tree (mapping result bits to status code)
 *       if (flags_1E & 0x1) {
 *           if (flags_1E & 0x2) return 2;
 *           // else fall to check flags_1F
 *       }
 *       if (flags_1F != 0) {
 *           // skip to inner check (flags_1E & 0x4)
 *           if (flags_1E & 0x4) return 4;
 *           return saved_v0;
 *       }
 *       // (flags_1F == 0)
 *       if (!(flags_1E & 0x1)) return 1;
 *       if (flags_1E & 0x4) return 4;
 *       return saved_v0;
 *   }
 *
 * Notes:
 *  - Two stack buffers at sp+0x1C and sp+0x20 receive results of hook3 and
 *    hook5 — likely controller-pak status / save-data state structs.
 *  - The bit-test sequence on flags_1E/flags_1F (`& 0x1`, `& 0x2`, `& 0x4`)
 *    suggests a 3-bit status word per subsystem with flags like
 *    {present=1, formatted=2, writable=4}.
 *  - Likely a `pak_status_query` or `save_data_status` function returning
 *    an enum: 0=ok, 1=missing, 2=corrupted, 4=read-only.
 *  - Returns saved_v0 (default status from hook2/hook4) on the catch-all path.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071624);
#endif

#ifdef NON_MATCHING
/* gl_func_00071708: 49-insn record-stream sibling (zero-a0-bytes prefix variant).
 * Size 0xC4, frame 0x10. Member of the family in
 * reference_1080_record_stream_template_family.md.
 *
 * NEW VARIANT — distinct from prior siblings (0006D6F4 emit, 0006BD14/0006C1B8
 * reset-with-clear-prefix). This one:
 *   - Uses a SMALLER 6-byte template (not 8-byte): `{1, 3, 0, 0xFF, 0xFF, 0xFF}`
 *   - "Zero a0 bytes + advance dst" prefix (not full 60-byte table clear)
 *   - Writes template ONCE (not a loop) then terminates with 0xFE
 *
 * Decoded structure (raw-word disasm):
 *   void emit_after_zero_prefix(int a0_count) {
 *       *(uint8_t*)&D_00000000 = 0;                     // zero D+0 count byte
 *       int *dst = (int*)&D_00000000;                   // start dst at D+0
 *       *(int*)((char*)&D_00000000 + 0x3C) = 1;          // active flag
 *
 *       // Template buf[6] = {1, 3, 0, 0xFF, 0xFF, 0xFF}
 *
 *       // Stage 1: zero a0 bytes starting at dst, advance dst by a0
 *       for (int i = 0; i < a0_count; i++) {
 *           *(uint8_t*)dst = 0;
 *           dst = (char*)dst + 1;
 *       }
 *
 *       // Stage 2: write 6-byte template at advanced dst
 *       *(uint32_t*)dst = *(uint32_t*)buf;       // swl/swr unaligned 4 bytes
 *       *((uint8_t*)dst + 4) = buf[4];           // = 0xFF
 *       *((uint8_t*)dst + 5) = buf[5];           // = 0xFF
 *       dst = (char*)dst + 6;
 *
 *       // Stage 3: 0xFE terminator
 *       *(uint8_t*)dst = 0xFE;
 *   }
 *
 * Notes:
 *  - 6-byte template suggests a different record-type than the 8-byte sibs.
 *    Bytes {1, 3, 0, 0xFF×3} read as { type=1, subtype=3, len=0, pad×3 }.
 *  - The "zero a0 bytes" leading loop is the equivalent of the family's
 *    "advance dst" with side effect (clear pre-existing records before
 *    placing the new one).
 *  - This may be a "replace-at-offset" variant where caller passes a0 as
 *    "offset where new record goes" and the function clears any stale data
 *    in [0..a0) before placing the new record at [a0..a0+6).
 *  - Trailing 1-insn fragment (`lui $t6, 0x0`) post-epilogue — incomplete.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071708);
#endif

#ifdef NON_MATCHING
/* gl_func_000717CC: 38-insn single-record decode (sibling of gl_func_0006C11C).
 * Size 0x98, frame 0x10.
 *
 * Sibling decoder: where gl_func_0006C11C iterates over a stream of 8-byte
 * records, this function decodes ONE record at offset (caller-set src + a0).
 *
 * Decoded structure (raw-word disasm):
 *   void decode_single(int byte_offset [a0],
 *                      uint16_t *out      [a1],
 *                      uint8_t  *src      [$t6 caller-set])
 *   {
 *       // Stage 1: advance src by `byte_offset` bytes via counted loop
 *       // (semantically `src += byte_offset`; IDO emits a no-op increment
 *       // loop because the stack-slot `sw/lw` cycle defeats constant folding)
 *       for (int i = 0; i < byte_offset; i++) {
 *           src += 1;
 *       }
 *
 *       // Stage 2: copy 6 bytes from src into local buf at sp+0x4
 *       uint8_t buf[8];
 *       *(uint32_t*)(buf+0) = *(uint32_t*)src;   // lwl/lwr unaligned 4 bytes
 *       buf[4] = src[4];
 *       buf[5] = src[5];
 *
 *       // Stage 3: extract 2-bit tag from buf[1] top bits
 *       uint8_t tag = (buf[1] & 0xC0) >> 4;     // 0/4/8/0xC code
 *       buf[3] = tag;                            // overwrite sp+7
 *
 *       // Stage 4: write packed payload to *out if tag is zero
 *       if (tag == 0) {
 *           // Construct 16-bit value: (buf[4] << 8) | tag
 *           uint16_t packed = ((uint16_t)buf[4] << 8) | (uint16_t)tag;
 *           *out = packed;                       // sh to *a1
 *           *((uint8_t*)out + 2) = buf[5];      // tail byte
 *       }
 *       // (tag != 0: skip payload write — caller's *out unchanged)
 *   }
 *
 * Notes:
 *  - $t6 caller-set src ptr — fits caller-set-int-reg cap class
 *    (feedback_caller_set_int_reg_cap_1080_game_libs.md).
 *  - The "advance src via counted loop" is functionally equivalent to a
 *    single `addu src, src, a0` but IDO emits ~9 instructions instead. The
 *    stack-roundtrip on the loop_idx via `lw/sw` is the giveaway — looks like
 *    a compiler intrinsic for "volatile counter" semantics, or perhaps the
 *    original source has a side-effecting inner expression that we can't see
 *    in the disasm (e.g., `do_something(src); src++; i++;`).
 *  - Same 2-bit tag dispatch and bit-shifted offset stride as 0006C11C.
 *  - Reads 6 bytes from src but writes only 3 bytes (2-byte sh + 1-byte sb)
 *    to *out — outputs less than reads, so this is a "compress/decode"
 *    operation.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000717CC);
#endif

#ifdef NON_MATCHING
/* gl_func_00071864: 23-insn 16-bit byte-sum checksum.
 *   accum = 0; for (i=0; i<n; i++) accum = (accum + p[i]) & 0xFFFF;
 *   return (u16)accum;
 *
 * Target spills p/accum/i to stack every iteration (-O0-shaped emit).
 * `volatile`-laden -O2 body scores 23.8% (worse than naive 5.4%).
 * Confirmed: needs -O0 file split — deferred. Wrap preserves the
 * decoded C for permuter / future -O0-split work; INCLUDE_ASM stays
 * the build path. */
unsigned short gl_func_00071864(unsigned char *a0, int a1) {
    int accum = 0;
    int i;
    for (i = 0; i < a1; i++) {
        accum = (accum + a0[i]) & 0xFFFF;
    }
    return (unsigned short)accum;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071864);
#endif

/* gl_func_000718C0: 26-insn ones-complement-style checksum loop.
 *   *a2 = 0; *a1 = *a2; for (i = 0; i < 0x1C; i += 2) { v = *(u16*)(a0+i); *a1 += v; *a2 += ~v; }
 * Target is stack-resident + fully-filled-delay-slots (-O1 cap class, NOT -O0;
 * see corrected note on the #ifdef body below + docs/IDO_CODEGEN.md).
 * Naive -O2 unrolls badly (228B vs 104B); volatile-loop variant adds barriers (124B). Cap. */
#ifdef NON_MATCHING
/* gl_func_000718C0: 26-insn dual checksum over 14 input halfwords (a0[0..0x1A]).
 * *a1 accumulates the sum of the halfwords; *a2 accumulates the sum of their
 * bitwise complements (~v); returns 0. RELOC-FREE.
 * 2026-05-25 OPT-LEVEL CORRECTION (supersedes a prior wrong "-O0" note): same cap
 * class as gl_func_00070194 -- target is -O1-style with STACK-RESIDENT locals
 * (i, tmp reloaded each iter) AND FULLY-filled delay slots (0 nops). This combo is
 * not emittable by the project cc (residency needs -g which suppresses full fill;
 * full fill needs no-g which register-allocates). plain -O1=29 insns/1 nop,
 * -g2=32 insns/2 nops; target=26 insns/0 nops. NOT -O0 (which leaves slots
 * unfilled). See docs/IDO_CODEGEN.md "stack-residency + filled-delay-slots".
 * Genuine cap; keep INCLUDE_ASM. Algorithm below verified-correct. */
int gl_func_000718C0(short *a0, short *a1, short *a2) {
    short tmp;
    int i;
    tmp = 0;
    *a2 = 0;
    *a1 = *(unsigned short *)a2;
    i = 0;
    do {
        tmp = *(short *)((char *)a0 + i);
        *a1 = *(unsigned short *)a1 + (unsigned short)tmp;
        *a2 = *(unsigned short *)a2 + ~tmp;
        i += 2;
    } while (i < 0x1C);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000718C0);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071928);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071D40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071ED8);

#ifdef NON_MATCHING
/* gl_func_00072134: 63-insn save-data verification with retry-on-error-2 (size 0xFC, frame 0x40).
 *
 * Verifies a 32-byte block read from a save channel against a stored expected
 * copy. Includes a re-init early step (if flag at obj+0x65 is set) and a
 * one-time retry if the reader returns specific error code 2.
 *
 * Decoded structure (raw-word disasm):
 *   int verify_save_block(Obj *obj) {
 *       // Stage 1: optional re-init step
 *       if (obj->flag_65 != 0) {
 *           obj->flag_65 = 0;
 *           int err = reinit(obj);          // jal #1
 *           if (err != 0) return err;
 *       }
 *
 *       // Stage 2: read 32 bytes into local buffer at sp+0x1C
 *       uint8_t buf[32];
 *       int err = read_save_block(obj->[0x4], obj->[0x8], 1, &buf);  // jal #2
 *       if (err != 0) {
 *           if (err != 2) return err;       // hard error
 *           // err == 2: retry once
 *           err = read_save_block(obj->[0x4], obj->[0x8], 1, &buf);  // jal #3 (same args)
 *           if (err != 0) return err;
 *       }
 *
 *       // Stage 3: byte-compare 32 bytes at buf[] against obj->expected[]
 *       for (int i = 0; i < 0x20; i++) {
 *           uint8_t got      = *(uint8_t*)((char*)&buf + i + 0x0);
 *           uint8_t expected = *(uint8_t*)((char*)obj  + i + 0xC);
 *           if (got != expected) return 2;   // byte mismatch
 *       }
 *       return 0;                            // OK
 *   }
 *
 * Notes:
 *  - obj layout: `flag_65` at +0x65 (re-init flag), `channel/handle` at +0x4
 *    and +0x8 (likely controller-pak channel + file handle), expected hash
 *    at +0xC..+0x2B (32 bytes).
 *  - Error-code 2 has special "retry-once" semantics; other non-zero errors
 *    propagate directly. Caller likely uses error 2 from the verify to drive
 *    its own recovery (re-format pak, reset save state, etc.).
 *  - Compare loop uses `sp + loop_idx + 0x1C` addressing — addu $tN, $sp,
 *    $loop_idx then lbu with +0x1C offset = standard array indexing without
 *    multiplier (byte-stride).
 *  - The double-read-retry pattern is hallmark of N64 Controller Pak access
 *    (jitter / cmd-retry on hardware-level transient failures).
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072134);
#endif

#ifdef NON_MATCHING
extern int game_libs_func_00070FCC();


#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00072230)();
s32 gl_func_00072230(char *arg0, char *arg1, u8 arg2, u8 arg3) {
    u8 sp37;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    char *sp24;
    s32 temp_t0;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 var_v0;
    char *temp_t1;
    char *temp_t2;
    char *temp_t5_2;
    char *temp_t6;

    if (FW(arg0, 0x65) != 0) {
        FW(arg0, 0x65) = 0U;
        sp2C = game_libs_func_00070FCC(arg0);
        if (sp2C != 0) {
        }
    }
    if ((s32) arg3 > 0) {
        sp28 = 1;
    } else {
        sp28 = FW(arg0, 0x60);
    }
    if (arg2 == 1) {
        FW(arg1, 0x1) = game_libs_func_00070FCC((int)arg1 + (sp28 * 2), (sp28 * -2) + 0x100);
    }
    sp30 = 0;
loop_9:
    temp_t2 = (int)arg1 + (sp30 << 5);
    sp24 = temp_t2;
    if (arg2 == 1) {
        sp2C = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x54) + (arg3 * 8) + sp30, temp_t2, 0);
        var_v0 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x58) + (arg3 * 8) + sp30, sp24, 0);
    } else {
        var_v0 = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x54) + (arg3 * 8) + sp30, sp24);
    }
    sp2C = var_v0;
    if (sp2C != 0) {
    }
    temp_t5 = sp30 + 1;
    sp30 = temp_t5;
    if (temp_t5 >= 8) {
        if (arg2 == 0) {
            sp37 = game_libs_func_00070FCC((int)arg1 + (sp28 * 2), (sp28 * -2) + 0x100);
            if (FW(arg1, 0x1) != sp37) {
                sp30 = 0;
                do {
                    temp_t6 = (int)arg1 + (sp30 << 5);
                    sp24 = temp_t6;
                    sp2C = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x58) + (arg3 * 8) + sp30, temp_t6);
                    temp_t4 = sp30 + 1;
                    sp30 = temp_t4;
                } while (temp_t4 < 8);
                if (FW(arg1, 0x1) != sp37) {
                    return 3;
                }
                sp30 = 0;
                do {
                    temp_t5_2 = (int)arg1 + (sp30 << 5);
                    sp24 = temp_t5_2;
                    sp2C = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x54) + (arg3 * 8) + sp30, temp_t5_2, 0);
                    temp_t0 = sp30 + 1;
                    sp30 = temp_t0;
                } while (temp_t0 < 8);
                goto block_26;
            }
            sp30 = 0;
            do {
                temp_t1 = (int)arg1 + (sp30 << 5);
                sp24 = temp_t1;
                sp2C = game_libs_func_00070FCC(FW(arg0, 0x4), FW(arg0, 0x8), FW(arg0, 0x58) + (arg3 * 8) + sp30, temp_t1, 0);
                temp_t3 = sp30 + 1;
                sp30 = temp_t3;
            } while (temp_t3 < 8);
            goto block_26;
        }
block_26:
        return 0;
    }
    goto loop_9;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072230);
#endif

#ifdef NON_MATCHING
/* gl_func_00072550: fills a 32-byte stack buffer with a0[0x65] (same byte 32
 * times -- the lbu is INSIDE the loop, not hoisted), then calls
 *   gl_func_00000000(a0[1], a0[2], 0x400, buf, 0)   (5 args, 5th on stack)
 * and returns its value. The redundant sw v0 / lw v0 round-trip just before
 * `jr ra` is IDO -O2's spill-then-reload-return pattern for v0.
 *
 * Progression: naive for/i<32 → 28% (IDO unrolls 4x).
 *               volatile i → 50% (loop preserved, $s0 still used for a0).
 *               volatile i + volatile ret → 60% (frame layout closer).
 *               int* volatile a0 = arg, volatile i, volatile ret → 75%
 *                 (a0 reloaded from home slot each access, no $s0 promote).
 * Remaining cap: target computes `addu t9, sp, i` inside loop each iter;
 * mine precomputes `a3 = sp+0x28` outside (buf base). Mine: 80-byte frame;
 * target: 72-byte. Address-computation pattern difference. */
int gl_func_00072550(int* arg) {
    char buf[32];
    int* volatile a0 = arg;
    volatile int ret = 0;
    volatile int i = 0;
    do {
        buf[i] = ((char*)a0)[0x65];
        i++;
    } while (i < 32);
    ret = gl_func_00000000(a0[1], a0[2], 0x400, buf, 0);
    return ret;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072550);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00072550_pad.s")

#ifdef NON_MATCHING
/* gl_func_000725C4 - STRUCTURAL PASS (big-swing 2026-06-02).
 * Multi-pass formatted-string layout/render driver, 0x6C4 (433 insns).
 * Sole callee gl_func_0001CA10 (the family's measure/emit/lookup helper;
 * each call returns an error code that is propagated immediately). No
 * folded-pool refs. Three passes over the FI(arg0, 0x50) glyph slots:
 *   pass 1 (loop_7): per slot decode a glyph (gl_func_0001CA10 -> &meas),
 *     run the line-fit inner loop (loop_15) advancing through the wrap
 *     candidates in sp27C[], track break opportunity, flush on overflow;
 *   pass 2 (loop_42): record the chosen break column into sp23C[slot];
 *   pass 3 (loop_51 over FI(arg0, 0x64) rows): build the per-row glyph table
 *     sp37C[] from sp27C[]/sp23C[] and emit it via gl_func_0001CA10.
 * Finally set/clear FI(arg0, 0x0) bit 1 from the overflow flag sp34.
 *
 * Locals: sp38/sp27C/sp37C/sp23C are u16[] working buffers; the (sp25C,
 * sp260..sp266) group is one measure-result struct (passed by &). m2c
 * artifacts resolved: unksp47D == (u8)sp47C (LSB of the u16 char), and the
 * inner-measure 2nd arg is the current char sp47C.
 *
 * NOT matched (working-buffer register allocation + the family helper's
 * untyped signature); default INCLUDE_ASM path byte-exact. Structure
 * documented for the next pass. */
#define FI(p, o) (*(int *)((char *)(p) + (o)))

extern int gl_func_0001CA10();

s32 gl_func_000725C4(void *arg0) {
    struct { s32 status; u16 code; u16 col; s8 b264; s16 h266; } meas;
    u16 sp38[0x80];
    u16 sp27C[0x80];
    u16 sp37C[0x80];
    u16 sp23C[0x80];
    u16 sp47C;
    s32 err;
    s32 slot;
    s32 brk;
    s32 prevw;
    s32 overflow;
    u8 row;
    s32 i;
    s32 n;

    err = gl_func_0001CA10(arg0);
    if (err == 2) {
        err = gl_func_0001CA10(arg0);
    }
    if (err != 0) {
        return err;
    }
    err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp38[0]);
    if (err != 0) {
        return err;
    }

    overflow = 0;
    slot = 0;
    if (FI(arg0, 0x50) > 0) {
    loop_7:
        err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas);
        if (err != 0) {
            return err;
        }
        if ((meas.code != 0) && (meas.status != 0)) {
            sp47C = meas.col;
            brk = 0;
            prevw = 0;
            if (((s32) sp47C >= FI(arg0, 0x60)) && ((s32) (u8) sp47C < (s32) FI(arg0, 0x64)) &&
                ((s32) (u8) sp47C > 0) && ((s32) (u8) sp47C < 0x80)) {
            loop_15:
                /* advance through wrap candidates accumulating width */
                err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp27C[0], NULL, (s32 *) (u8) sp47C);
                if ((err != 0) && (err != 3)) {
                    return err;
                }
                brk = gl_func_0001CA10(arg0, sp47C, (u16 (*)[]) &sp38[0]) - prevw;
                if (brk != 0) {
                    prevw = 1;
                    sp47C = sp27C[(u8) sp47C];
                    if (((s32) sp47C >= FI(arg0, 0x60)) && ((s32) (u8) sp47C < (s32) FI(arg0, 0x64)) &&
                        ((s32) (u8) sp47C > 0) && ((s32) (u8) sp47C < 0x80)) {
                        goto loop_15;
                    }
                }
            }
            if ((brk != 0) || (sp47C != 1)) {
                meas.code = 0;
                meas.status = 0;
                meas.col = 0;
                meas.b264 = 0;
                meas.h266 = 0;
                if (FI(arg0, 0x65) != 0) {
                    FI(arg0, 0x65) = 0;
                    err = gl_func_0001CA10(arg0);
                    if (err != 0) {
                        return err;
                    }
                }
                err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas, 0);
                if (err != 0) {
                    return err;
                }
                overflow += 1;
            }
        } else if ((meas.code != 0) || (meas.status != 0)) {
            meas.code = 0;
            meas.status = 0;
            meas.col = 0;
            meas.b264 = 0;
            meas.h266 = 0;
            if (FI(arg0, 0x65) != 0) {
                FI(arg0, 0x65) = 0;
                err = gl_func_0001CA10(arg0);
                if (err != 0) {
                    return err;
                }
            }
            err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas, 0);
            if (err != 0) {
                return err;
            }
            overflow += 1;
        }
        slot += 1;
        if (slot < FI(arg0, 0x50)) {
            goto loop_7;
        }
    }

    slot = 0;
    if (FI(arg0, 0x50) > 0) {
    loop_42:
        err = gl_func_0001CA10(FI(arg0, 0x4), FI(arg0, 0x8), FI(arg0, 0x5C) + slot, &meas);
        if (err != 0) {
            return err;
        }
        if ((meas.code != 0) && (meas.status != 0) && ((s32) meas.col >= (s32) FI(arg0, 0x62))) {
            sp23C[slot] = meas.col;
        } else {
            sp23C[slot] = 0;
        }
        slot += 1;
        if (slot < FI(arg0, 0x50)) {
            goto loop_42;
        }
    }

    row = 0;
    if ((s32) FI(arg0, 0x64) > 0) {
    loop_51:
        err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp27C[0], NULL, (s32 *) row);
        if ((err != 0) && (err != 3)) {
            return err;
        }
        if ((s32) row > 0) {
            n = 1;
        } else {
            n = FI(arg0, 0x60);
        }
        for (i = 0; i < n; i++) {
            sp37C[i] = sp27C[i];
        }
        for (; i < 0x80; i++) {
            sp37C[i] = 3;
        }
        for (i = 0; i < FI(arg0, 0x50); i++) {
            while ((sp23C[i] == row) && ((s32) sp23C[i] >= (s32) FI(arg0, 0x62))) {
                u8 idx = (u8) sp23C[i];
                u16 v = sp27C[idx];
                sp37C[idx] = v;
                sp23C[i] = v;
            }
        }
        err = gl_func_0001CA10(arg0, (u16 (*)[]) &sp37C[0], (u16 (*)[]) 1, (s32 *) row);
        if (err != 0) {
            return err;
        }
        row += 1;
        if ((row & 0xFF) < (s32) FI(arg0, 0x64)) {
            goto loop_51;
        }
    }

    if (overflow != 0) {
        FI(arg0, 0x0) = FI(arg0, 0x0) | 2;
    } else {
        FI(arg0, 0x0) = FI(arg0, 0x0) & ~2;
    }
    return 0;
}
#undef FI
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000725C4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072C88);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072E3C);

int game_libs_func_00073024(void) {
    return *(volatile int *)0xA4500004;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00072E3C_pad.s")

#ifdef NON_MATCHING
/* gl_func_00073034: 16-insn (0x40) double-call wrapper, returns 2nd call's
 * value. Calls gl_func_0(a0, a1) twice; returns v0 of the second call.
 *
 * Trailing 2 insns (0x3C-0x40) are stolen-prologue donation to successor
 * gl_func_00073078: `lui t6, 0xA460; lw a2, 0x10(t6)` reads PI_STATUS_REG
 * (0xA4600010) into $a2 for the next function.
 *
 * Cap: target uses 0x28 frame + saves $s0 + does `s0 = v0; ...; v0 = s0`
 * round-trip in the epilogue. Standalone IDO -O2 emits 12 insns / 0x18
 * frame without the s0 save (~75% structural shape). The s0-via-v0
 * round-trip pattern isn't reachable from natural C — IDO chose it
 * because of some heuristic (maybe live-range across the lw ra in the
 * epilogue, even though lw doesn't clobber v0). Multi-tick. */
extern int gl_func_00000000();

int gl_func_00073034(int a0, int a1) {
    int v;
    gl_func_00000000(a0, a1);
    v = gl_func_00000000(a0, a1);
    return v;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073034);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073074);

#ifdef NON_MATCHING
/* gl_func_0007307C: 18-insn PI DMA-write helper. If (a2 & 3), spin-wait
 * for PI not busy. Then write a1 to (D_0 | a0) via KSEG1 uncached.
 * Returns 0.
 *
 * Symbol size 0x50 includes 2 trailing literal `.word` (lui+lw of
 * PI_STATUS_REG) — splat-absorbed boundary, solo SUFFIX_BYTES can
 * append (no relocs).
 *
 * 2026-05-14 C-only attempts:
 *   - Plain `while (D_A4600010 & 3) {}` — 68 bytes, no prologue+epilogue
 *     (IDO -O2 elides frame because no locals); 12 bytes short of target
 *   - `volatile u32 status` local — 96 bytes (too many stack roundtrips)
 *
 * Target has small 8-byte frame (`addiu sp,-8` / `addiu sp,+8`) even
 * without spillable locals — likely forced by the body's mid-function
 * `addiu sp,+8` BEFORE the trailing stores. INSN_PATCH+SUFFIX_BYTES
 * promotion path: ~17 entry INSN_PATCH + 2-word SUFFIX_BYTES for the
 * literal trailing. Deferred for now. */
int gl_func_0007307C(int a0, int a1, int a2) {
    extern s32 D_A4600010;
    if (a2 & 3) {
        while (D_A4600010 & 3) {}
    }
    *(int*)((D_00000000 | a0) | 0xA0000000) = a1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007307C);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000730C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000730CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073258);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000730CC_pad.s")

#ifdef NON_MATCHING
/* gl_func_000732C4: 19-insn 3-call sequence storing 2 into a singleton.
 * Decode:
 *   r = gl_func_00000000();          // jal #1 (no args)
 *   p = *(short**)&gl_data_X;        // lui+lw chain → t7
 *   p[8] = 2;                        // sh t6=2, 0x10(t7)  (delay slot of jal #2)
 *   gl_func_00000000(&gl_data_Y);    // jal #2 (a0 = &D_Y)
 *   gl_func_00000000(r);             // jal #3 (a0 = s0 = r)
 * 2026-05-17: natural C scored 61%. 2026-05-18 retry with explicit `short* p`
 * named local to force the lui+lw to compute t7 before the constant-2
 * generation, matching the target's instruction ordering. */
extern int gl_data_732C4_load;
extern int gl_data_732C4_arg;

void gl_func_000732C4(void) {
    register int r;
    short* p;
    r = gl_func_00000000();
    p = *(short**)&gl_data_732C4_load;
    p[8] = 2;
    gl_func_00000000(&gl_data_732C4_arg);
    gl_func_00000000(r);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000732C4);
#endif

/* VI-status read leaf. The leading nop pad and delay-slot temp move are
 * reproduced with PREFIX_BYTES + INSN_PATCH in the Makefile. */
#ifdef NON_MATCHING
u32 game_libs_func_00073310(void) {
    return *(volatile u32 *)0xA4400010 & 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073310);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000732C4_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073334);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073538);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00073688);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007369C);

#ifdef NON_MATCHING
/* gl_func_00073824: 53-insn 8-arg structure initializer + chained registration.
 * Size 0xD4, frame 0x20.
 *
 * Initializes an Obj at `a0` from 7 caller-provided fields (a2/a3 plus 5 stack
 * args at sp+0x30/0x34/0x38/0x3C plus default-fallback args), calls a
 * registration hook, then optionally chains a second hook if the object is the
 * currently-active global.
 *
 * Decoded structure (raw-word disasm):
 *   int init_and_register(Obj *obj, void *_unused_a1, int a2, int a3,
 *                         int arg5, int arg6, int arg7, int arg8) {
 *       obj->[0x0]  = 0;                       // zero head fields
 *       obj->[0x4]  = 0;
 *       obj->[0xC]  = arg6;                    // 6th arg (sp+0x34)
 *       obj->[0x8]  = arg5;                    // 5th arg (sp+0x30)
 *
 *       // Conditional field default: if both a2 and a3 are zero, use arg5/arg6 as fallback
 *       if (a2 != 0) {
 *           obj->[0x10] = a2;
 *           obj->[0x14] = a3;
 *       } else if (a3 != 0) {
 *           obj->[0x10] = a2;                  // = 0
 *           obj->[0x14] = a3;
 *       } else {
 *           obj->[0x10] = arg5;                // fallback to stack-arg defaults
 *           obj->[0x14] = arg6;
 *       }
 *
 *       obj->[0x18] = arg7;                    // 7th arg (sp+0x38)
 *       obj->[0x1C] = arg8;                    // 8th arg (sp+0x3C)
 *
 *       void *result = register_obj(obj);      // jal <func>(obj)
 *
 *       // Chain handler if this is the current global object
 *       if (obj->[0x0] == obj) {               // self-ref test (jal may have set [0])
 *           chain_handler(saved_v0, saved_v1);  // jal <func>
 *       }
 *
 *       return 0;
 *   }
 *
 * Notes:
 *  - The `obj->[0x0] == obj` self-reference check after the jal is unusual:
 *    register_obj() likely populates obj->[0x0] with the back-pointer for
 *    head-tracking. When the back-pointer is self, this object is its own
 *    "head" (i.e., the active one) — fire the chain handler.
 *  - Args 5-8 passed on stack (O32 ABI args 5+ at sp+0x30..0x3C after our
 *    frame adjust).
 *  - The a2/a3 branch is functionally equivalent to "if !(a2==0 && a3==0)
 *    use a2/a3 else use arg5/arg6" but IDO emits a 3-way tree.
 *  - v0:v1 from first jal saved at sp+0x18/0x1C (64-bit-return pair) then
 *    re-loaded as a0/a1 for the chain call.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073824);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00073824_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073904);

void game_libs_func_00073E6C(void) {}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073E74);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00073E74_pad.s")

#ifdef NON_MATCHING
/* gl_func_000743C4: 66-insn 64-bit-arithmetic timestamp/range helper (size 0x108, frame 0x30).
 *
 * Computes a 64-bit subtraction across two function-returned values, optionally
 * applies a wrap correction, and stores 4 32-bit fields to an output Obj.
 *
 * Decoded structure (raw-word disasm):
 *   void compute_delta(int *out_obj, [a0 = destination]
 *                      int unused_a1,
 *                      uint32_t a_hi, uint32_t a_lo,  // a2:a3 = first 64-bit operand
 *                      uint32_t b_hi, uint32_t b_lo,  // sp+0x40:0x44 = second
 *                      uint32_t c_hi, uint32_t c_lo)  // sp+0x48:0x4C = third? (read later)
 *   {
 *       // STAGE 1: jal #1 (a2, a3, sp_arg40_lo, sp_arg44_hi)
 *       int64_t r1 = func1(a_hi, a_lo, sp_arg44, sp_arg40);
 *
 *       // STAGE 2: jal #2 (sp_arg40, sp_arg44, r1_v0, r1_v1) — chain
 *       int64_t r2 = func2(sp_arg40, sp_arg44, r1.lo, r1.hi);
 *
 *       // STAGE 3: 64-bit subtract  diff = saved_a2:a3 - r2_v0:v1
 *       uint64_t diff = ((uint64_t)saved_a2 << 32 | saved_a3) -
 *                       ((uint64_t)r2.hi    << 32 | r2.lo);
 *       int32_t  d_hi = (int32_t)(diff >> 32);
 *       uint32_t d_lo = (uint32_t)diff;
 *
 *       // STAGE 4: range adjustment based on sign of d_hi
 *       if (d_hi > 0) {
 *           // positive: use diff as-is
 *       } else if (d_hi < 0) {
 *           // negative: subtract sp_arg40:sp_arg44 from diff (wrap correction)
 *           int64_t adj = (uint64_t)d_hi << 32 | d_lo;
 *           adj -= ((uint64_t)sp_arg40 << 32 | sp_arg44);
 *           d_hi = (int32_t)(adj >> 32);
 *           d_lo = (uint32_t)adj;
 *           // r1 also adjusted: r1.lo++; r1.hi += (r1.lo == 0 ? 1 : 0)  (saturating)
 *       }
 *       // (d_hi == 0: use diff as-is, no adjust)
 *
 *       // STAGE 5: store 4 fields to out_obj
 *       *(int*)(out_obj + 0x0) = r1.hi;
 *       *(int*)(out_obj + 0x4) = r1.lo;
 *       *(int*)(out_obj + 0x8) = d_hi;
 *       *(int*)(out_obj + 0xC) = d_lo;
 *   }
 *
 * Notes:
 *  - Uses standard 64-bit subtract sequence:
 *      subu $hi_diff, $hi_a, $hi_b
 *      sltu $borrow, $lo_a, $lo_b
 *      subu $hi_diff, $hi_diff, $borrow
 *      subu $lo_diff, $lo_a, $lo_b
 *  - The bltzl branch-likely after bgtz/bltz forms a 3-way dispatch on signed
 *    64-bit comparison (positive / negative / zero).
 *  - 4-field store is the canonical "save 64-bit timestamp pair + 64-bit delta"
 *    pattern. Likely tracks elapsed-time / lap-time / frame-counter delta.
 *  - Trailing 2-insn fragment (`mult $a1, $a2; mflo $v0`) past epilogue —
 *    likely incomplete next function fragment. Variant of
 *    feedback_splat_too_big_incomplete_fragment_tail.md.
 *  - Replaced 1-line "Multi-pass decode pending" bail-marker per
 *    feedback_doc_marker_is_bail.md.
 *
 * 2026-05-28: converted the comment-only bail into a real C body, 54.77%
 * (mnemonic disasm confirms the structure). KEY 64-bit-on-mips2 finding:
 * extracting hi/lo from a long-long call return via `(int)(r>>32)` compiles to
 * a CALL to a 64-bit-shift runtime helper (huge bloat: 0x214). Use the UNION
 * idiom instead — `union{long long ll; struct{int hi,lo;} w;}` — which stores
 * v0:v1 to the stack and reads the words back, exactly matching the target's
 * `sw v0,32(sp); sw v1,36(sp); lw ...` roundtrip (got 40%→55%). All 64-bit
 * arithmetic is manual int hi/lo (subu/sltu/subu), NOT long-long ops.
 * RESIDUAL (~45%, multi-tick): (a) frame 0x40 vs 0x30 — the two union temps
 * use extra stack; the target reuses ONE result area (sp+0x20..0x2C) that the
 * call result stores into DIRECTLY (needs aliasing result[0..1] with the call
 * return). (b) the result→out_obj copy: target uses a t0=&sp[0x20] pointer
 * loop, mine does indexed loads. (c) dispatch-branch ordering. Real wrap now
 * (compilable / permuter-able / correct logic), not a comment bail. */
/* long-long-returning view of the jal-0 placeholder (returns 64-bit in v0:v1).
 * Used ONLY to capture the pair; all arithmetic is manual int hi/lo to emit the
 * target's subu/sltu/subu (long-long shifts emulate to bloated/MIPS3 ops on -mips2). */
extern long long gl_ret64_743C4();
typedef union { long long ll; struct { int hi; int lo; } w; } Pair64;
void gl_func_000743C4(int *out_obj, int a1, int a2, int a3, int b_hi, int b_lo) {
    int result[4];
    Pair64 r1, r2;
    int r1_hi, r1_lo, r2_hi, r2_lo;
    int diff_hi, diff_lo;

    r1.ll = gl_ret64_743C4(a2, a3, b_hi, b_lo);
    r1_hi = r1.w.hi;
    r1_lo = r1.w.lo;
    r2.ll = gl_ret64_743C4(b_hi, b_lo, r1_lo, r1_hi);
    r2_hi = r2.w.hi;
    r2_lo = r2.w.lo;

    /* diff = {a2:a3} - {r2_hi:r2_lo}  (manual 64-bit subtract) */
    diff_hi = a2 - r2_hi - ((unsigned int)a3 < (unsigned int)r2_lo);
    diff_lo = a3 - r2_lo;

    result[0] = r1_hi;
    result[1] = r1_lo;
    result[2] = diff_hi;
    result[3] = diff_lo;

    if (r1_hi < 0) {
        if (diff_hi > 0 || (diff_hi == 0 && diff_lo != 0)) {
            /* saturating-increment r1 */
            int nlo = r1_lo + 1;
            int nhi = r1_hi + (nlo == 0);
            /* diff -= {b_hi:b_lo} */
            int nd_hi = diff_hi - b_hi - ((unsigned int)diff_lo < (unsigned int)b_lo);
            int nd_lo = diff_lo - b_lo;
            result[0] = nhi;
            result[1] = nlo;
            result[2] = nd_hi;
            result[3] = nd_lo;
        }
    }

    out_obj[0] = result[0];
    out_obj[1] = result[1];
    out_obj[2] = result[2];
    out_obj[3] = result[3];
    (void)a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000743C4);
#endif


INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_000744C4);

#ifdef NON_MATCHING
/* gl_func_000744CC: 31-insn divide-correction helper w/ IDO trap prologue (0x7C, frame 0x08).
 *
 * Decoded structure (raw-word disasm) — division codegen idioms:
 *
 *   if (a2 == 0)                          break 0x1C0;   // div-by-zero
 *   if (a2 == -1 && a1 == 0x80000000)     break 0x180;   // overflow (INT_MIN/-1)
 *
 *   // Refinement body — assumes $v0 holds a caller-pre-computed quotient guess:
 *   prod_lo = (a2 * v0).lo;            // multu $a2, $v0; mflo
 *   rem = a1 - prod_lo;
 *   if (rem < 0) { v0++; rem -= a2; }  // sign-correction step
 *   a0[0] = v0;                        // write quotient
 *   a0[1] = rem;                       // write remainder
 *   return a0;                         // ($v0 = a0 at epilogue)
 *
 * The break codes 0x180/0x1C0 are IDO's standard div-trap signatures —
 * this is IDO `div` codegen output, not a hand-rolled libgcc helper.
 * The CURIOSITY is `multu $a2, $v0` with $v0 caller-set: $v0 is not a
 * standard arg register, so this is either (a) a custom intra-USO
 * calling convention (a la float-in-$f4/$f6/$f0), or (b) the result of
 * a fall-through from another function that set v0.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-18 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path (the
 * `multu $a2, $v0` w/ caller-set v0 is unreproducible from standard C).
 */
void gl_func_000744CC(int *a0_out, int a1_dividend_lo, int a2_divisor) {
    /* Custom-convention divide-correction helper. Real C below shows shape;
     * cannot byte-match due to caller-set $v0_guess. */
    extern int v0_caller_guess;
    int v0 = v0_caller_guess;
    int prod_lo, rem;
    if (a2_divisor == 0) __builtin_trap();
    if (a2_divisor == -1 && a1_dividend_lo == (int)0x80000000) __builtin_trap();
    prod_lo = (int)((unsigned)a2_divisor * (unsigned)v0);
    rem = a1_dividend_lo - prod_lo;
    if (rem < 0) {
        v0++;
        rem -= a2_divisor;
    }
    a0_out[0] = v0;
    a0_out[1] = rem;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000744CC);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000744CC_pad.s")

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00074554)();
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00074554;
void gl_func_00074554(char *arg0, s32 arg1) {
    int sp54;
    int sp5C;
    Q_00074554 sp78;
    s32 sp70;
    s32 sp64;
    s32 sp60;
    s32 sp50;
    s32 sp4C;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s0;
    s32 var_s3;
    s32 var_t0;
    s32 var_t1;
    u32 temp_v1;
    u64 temp_ret;
    u8 *temp_t7_2;
    u8 temp_t7;

    temp_v0 = arg1 & 0xFF;
    if (temp_v0 == 0x58) {
        var_s3 = 0x2E634;
    } else {
        var_s3 = 0x2E620;
    }
    var_s0 = 0x18;
    if (temp_v0 == 0x6F) {
        var_t1 = 8;
    } else {
        var_t0 = 0x10;
        if ((temp_v0 != 0x78) && (temp_v0 != 0x58)) {
            var_t0 = 0xA;
        }
        var_t1 = var_t0;
    }
    temp_t8 = FW(arg0, 0x0);
    temp_t9 = FW(arg0, 0x4);
    sp60 = temp_t8;
    sp40 = temp_t8;
    sp44 = temp_t9;
    sp64 = temp_t9;
    if (((temp_v0 == 0x64) || (temp_v0 == 0x69)) && (sp40 <= 0)) {
        if (sp40 >= 0) {

        } else {
            temp_t8_2 = ~sp60 + (sp64 == 0);
            sp64 = -sp64;
            sp60 = temp_t8_2;
        }
    }
    if ((sp60 != 0) || (sp64 != 0) || (FW(arg0, 0x24) != 0)) {
        var_s0 = 0x17;
        sp4C = 0x17;
        sp70 = var_t1;
        temp_t7 = *(int*)((u32) game_libs_func_00070FCC(sp60, sp64, var_t1 >> 0x1F, var_t1) + var_s3);
        *(u8 *)((char *)&sp78 + 0x17) = temp_t7;
    }
    sp70 = var_t1;
    temp_ret = game_libs_func_00070FCC(sp60, sp64, var_t1 >> 0x1F, var_t1);
    temp_v0_2 = temp_ret;
    temp_v1 = (u32) temp_ret;
    FW(arg0, 0x4) = (s32) temp_v1;
    FW(arg0, 0x0) = temp_v0_2;
    if ((temp_v0_2 >= 0) && ((temp_v0_2 > 0) || (temp_v1 != 0)) && (var_s0 > 0)) {
        sp3C = var_t1;
        sp38 = var_t1 >> 0x1F;
        sp40 = FW(arg0, 0x0);
        sp44 = FW(arg0, 0x4);
loop_24:
        game_libs_func_00070FCC((s32) &sp50, sp38, sp3C);
        temp_a0 = var_s0 - 1;
        FW(arg0, 0x0) = sp50;
        FW(arg0, 0x4) = sp54;
        temp_t7_2 = &sp78 + temp_a0;
        var_s0 = temp_a0;
        *temp_t7_2 = *(int*)(sp5C + var_s3);
        temp_t8_3 = FW(arg0, 0x0);
        temp_t9_2 = FW(arg0, 0x4);
        sp40 = temp_t8_3;
        sp44 = temp_t9_2;
        if ((temp_t8_3 >= 0) && ((temp_t8_3 > 0) || (temp_t9_2 != 0))) {
            if (var_s0 > 0) {
                goto loop_24;
            }
        }
    }
    temp_a2 = 0x18 - var_s0;
    FW(arg0, 0x14) = temp_a2;
    game_libs_func_00070FCC(FW(arg0, 0x8), (s32) (&sp78 + var_s0), temp_a2);
    temp_a1 = FW(arg0, 0x14);
    temp_a0_2 = FW(arg0, 0x24);
    if (temp_a1 < temp_a0_2) {
        FW(arg0, 0x10) = (s32) (temp_a0_2 - temp_a1);
    }
    if ((temp_a0_2 < 0) && ((FW(arg0, 0x30) & 0x14) == 0x10)) {
        temp_v0_3 = FW(arg0, 0x10);
        temp_s0 = ((FW(arg0, 0x28) - FW(arg0, 0xC)) - temp_v0_3) - temp_a1;
        if (temp_s0 > 0) {
            FW(arg0, 0x10) = (s32) (temp_v0_3 + temp_s0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074554);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074554_pad.s")

#ifdef NON_MATCHING
/* gl_func_000747F4: 19-insn uncached-write helper + 4-stub BUNDLE (0xAC declared,
 * real fn is 19 insns = 0x4C; rest are 4 small leaf utilities).
 *
 * Decoded fn 1 (gl_func_000747F4 proper):
 *   if (func_acquire() != 0) return -1;
 *   *(volatile int*)((uintptr_t)a0 | 0xA0000000) = a1;  // KSEG1 uncached write
 *   return 0;
 *
 * The `lui at, 0xA000; or t8, t7, at` is KSEG0→KSEG1 conversion: forces
 * write to bypass dcache (DMA-buffer poke / hardware register).
 *
 * Bundled siblings @0x4C-0xAC (need fragment-split for byte-exact):
 *   - @0x4C: `*(volatile int*)0xA4040010 = a0;`     // SP_STATUS_REG write
 *   - @0x58: `return *(volatile int*)0xA4040010;`   // SP_STATUS_REG read
 *   - @0x68: icache invalidate 0x80000000..0x80002000 (8KB via `cache 0x01`)
 *   - @0x94: getter — returns *(int*)&D_sym
 *
 * The cache-invalidate loop is the libultra-style `osInvalDCache` / icache
 * primitive — directly invokes `cache 0x01, off(t0)` insn for SI-related
 * hardware operations.
 *
 * Replaced 1-line "Multi-pass decode pending" bail-marker 2026-05-19 per
 * feedback_doc_marker_is_bail.md. INCLUDE_ASM remains build path.
 */
int gl_func_000747F4(void *a0, int a1) {
    int rc = (int)gl_func_00000000(a0, a1);
    if (rc != 0) return -1;
    *(volatile int*)((unsigned int)a0 | 0xA0000000) = a1;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000747F4);
#endif


/* game_libs_func_00074840 (0x10): RSP SP_STATUS (0xA4040010) WRITE accessor.
 * Body: `nop; lui t6,0xA404; jr ra; sw a0,0x10(t6)` = `*(volatile int*)0xA4040010 = a0`.
 * game_libs_func_00074850 (below) is the matching READ. CAP — the LEADING NOP is not
 * C-reproducible: a hardware-access hazard idiom (nop before the SP register touch).
 * Plain C `*(volatile int*)0xA4040010 = a0;` emits `lui t6; jr ra; sw a0,0x10(t6)` (no
 * leading nop). IDO has no inline-asm to inject a bare nop: `__asm__("nop")` compiles
 * to a JAL to a symbol `nop` (not an emitted nop), and `__asm__ volatile(...)` is a cfe
 * syntax error (feedback_ido_no_gcc_register_asm). Same leading-nop cap class as the VI
 * accessors (00069F50 etc.). Stays INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074840);

/* game_libs_func_00074850 (0x10): RSP SP_STATUS (0xA4040010) READ accessor (pair of
 * 00074840). Body: `nop; lui v0,0xA404; jr ra; lw v0,0x10(v0)` = `return
 * *(volatile int*)0xA4040010`. Same leading-nop hardware-hazard CAP — see 00074840. */
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074850);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074860);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_0007488C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_000747F4_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000748A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074AC0);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074AC0_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074C04);

#ifdef NON_MATCHING
/* gl_func_00074D54: 22-insn float-arg + global-state wrapper.
 *   rv = func_a(f);            // jal#1 takes float
 *   g->[0x24] = f;              // store f as float
 *   *(short*)g |= 4;            // bit-set in halfword
 *   return func_b(rv);          // jal#2 takes int
 *
 * 2026-05-15 — applied unique-extern recipe (gl_data_00074_a and
 * gl_data_00074_b separate symbols added to undefined_syms_auto.txt) to
 * break IDO's CSE on the duplicate `lui+lw 0(*)` pair. Plus `register`
 * hint on rv. Result: 19/22 insns (still 3 short). Target uses $s0 for
 * rv across the FPU work; IDO sees rv's only post-jal use is the next
 * jal (immediate tail-call style) and keeps it in $v0 → no $s0 save.
 * The "rv needs $s0" can't be forced without an artificial extra use
 * that would add MORE insns. Cap holds at the documented 67-86% range. */
extern int gl_data_00074_a;
extern int gl_data_00074_b;
int gl_func_00074D54(int a0, float arg1) {
    int rv = gl_func_00000000(a0);
    *(float*)((char*)gl_data_00074_a + 0x24) = arg1;
    *(short*)gl_data_00074_b |= 4;
    return gl_func_00000000(rv);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074D54);
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_00074D54_pad.s")

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074DB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00074EDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074EFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007507C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075248);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", game_libs_func_00075260);

#ifdef NON_MATCHING
/* SP_PC_REG (uncached, 0xA4080000) conditional writer.
 *   if ((flag & 1) != 0) { *(volatile u32*)0xA4080000 = pc; return 0; }
 *   else { return -1; }
 *
 * 11-insn target with `addiu sp, -8` + matching `addiu sp, sp, 8` at the
 * very end — fake stack frame even though no body uses it. Per
 * feedback_ido_sp_frame_without_stack_use.md: IDO -O2 won't allocate a
 * frame from standard C unless something actually touches the stack.
 *   - With body alone: 9 insns, no frame (mismatch).
 *   - With `volatile int x = 0;` to force a slot: 11 insns + frame BUT also
 *     emits `sw zero, 4(sp)` in the delay slot AND shifts $tN registers up
 *     by 1 (target uses t7/t8; mine t6/t7). Mismatch.
 *
 * Cap: ~85 % via the volatile-int form. Real fix needs a way to allocate
 * frame without stack use — which IDO doesn't expose.
 *
 * 2026-05-30 — DUAL-ENTRY context: the predecessor orphan game_libs_func_00075260
 * (`nop; lui t6,0xA404; lw a1,0x10(t6)`, no jr ra) loads this body's `flag` (a1)
 * from the RSP register 0xA4040010 (SP_STATUS read), then falls through. So the fn
 * is an RSP-poll: entered via 0x75260, flag = SP_STATUS; entered directly here,
 * flag = caller's. NOT an orphan-merge candidate — (a) dual-entry (body callable
 * with caller flag), and (b) the merged single-entry C reads SP_STATUS into $v0 and
 * emits a different leaf shape (no frame), so it can't reproduce the body's frame.
 * The hw write target 0xA4080000 = SP_PC_REG (RSP program counter). Both INCLUDE_ASM. */
int gl_func_0007526C(unsigned int pc, int flag) {
    volatile int x = 0;
    if ((flag & 1) == 0) {
        return -1;
    }
    *(volatile unsigned int*)0xA4080000 = pc;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007526C);
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/gl_func_0007526C_pad.s")
#endif
