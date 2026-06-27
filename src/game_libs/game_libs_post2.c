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

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* gl_func_00071144: 8 independent flag-bit blocks over arg0, each toggling
 * a bit in field 0xC of a distinct global struct (lui+lw snapshot), plus a
 * trailing 16-bit OR into field 0x0. arg0 is re-read from its stack home
 * before each test (taken via &arg0). Residual = branch-likely vs plain
 * beqz+nop and s0/frame coloring (codegen-shape, register-allocation cap). */
void gl_func_00071144(s32 arg0) {
    s32 temp_s0;
    s32 *zero = (s32 *)0;
    s32 *ap = &arg0;

    temp_s0 = game_libs_func_00070FCC();
    if (*ap & 1) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 8;
    }
    if (*ap & 2) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~8;
    }
    if (*ap & 4) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 4;
    }
    if (*ap & 8) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~4;
    }
    if (*ap & 0x10) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 0x10;
    }
    if (*ap & 0x20) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~0x10;
    }
    if (*ap & 0x40) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | 0x10000;
        p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & ~0x300;
    }
    if (*ap & 0x80) {
        void *p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) & 0xFFFEFFFF;
        p = (void *)*zero;
        FW(p, 0xC) = FW(p, 0xC) | (FW(FW(p, 0x8), 0x4) & 0x300);
    }
    {
        void *p = (void *)*zero;
        FW(p, 0x0) = (u16)(FW(p, 0x0) | 8);
    }
    game_libs_func_00070FCC(temp_s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071144);
#endif
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

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_00071384)();
typedef struct { int unk0,unk4,unk8,unkC,unk10,unk14,unk18,unk1C; } Q_00071384;
extern int game_libs_func_00070FCC();
extern int game_libs_func_00070F2C();
s32 gl_func_00071384(u16 *arg0, u16 *arg1, u16 *arg2) {
    Q_00071384 sp18;
    Q_00071384 sp3C;
    s32 sp64;
    s32 sp60;
    u16 sp5E;
    u16 sp5C;
    u16 *sp38;
    s32 temp_t8;
    s32 temp_v0;

    sp60 = 0;
    game_libs_func_00070FCC();
    sp60 = game_libs_func_00070FCC(arg0, arg2);
    game_libs_func_00070FCC();
    if (sp60 != 0) {
        return sp60;
    }
    FW(arg1, 0x4) = arg0;
    FW(arg1, 0x8) = arg2;
    FW(arg1, 0x0) = 0;
    FW(arg1, 0x65) = 0;
    sp60 = game_libs_func_00070FCC(arg1);
    if (sp60 != 0) {
        return sp60;
    }
    sp60 = game_libs_func_00070FCC(FW(arg1, 0x4), FW(arg1, 0x8), (u16 *)1, &sp3C);
    if (sp60 != 0) {
        return sp60;
    }
    game_libs_func_00070FCC(&sp3C, &sp5E, &sp5C);
    sp38 = &sp3C;
    if (((*(u16*)((char*)&sp3C + 0x1C)) != sp5E) || ((*(u16*)((char*)&sp3C + 0x1E)) != sp5C)) {
        sp60 = game_libs_func_00070FCC(arg1, sp38);
        if (sp60 != 0) {
            return sp60;
        }
        if (sp60 != 0) {
            return sp60;
        }
    }
    if (!(FW(sp38, 0x18) & 1)) {
        sp60 = game_libs_func_00070FCC(arg1, sp38, &sp18);
        if (sp60 != 0) {
            return sp60;
        }
        sp38 = &sp18;
        if (!((*(u32*)((char*)&sp18 + 0x18)) & 1)) {
            return 0xB;
        }
    }
    sp64 = 0;
    do {
        FW(((int)arg1 + sp64), 0xC) = (u8) *(int*)(sp38 + sp64);
        temp_t8 = sp64 + 1;
        sp64 = temp_t8;
    } while (temp_t8 < 0x20);
    FW(arg1, 0x4C) = (s32) FW(sp38, 0x1B);
    FW(arg1, 0x64) = (u8) FW(sp38, 0x1A);
    FW(arg1, 0x60) = (s32) ((FW(arg1, 0x64) * 2) + 3);
    FW(arg1, 0x50) = 0x10;
    FW(arg1, 0x54) = 8;
    FW(arg1, 0x58) = (s32) ((FW(arg1, 0x64) * 8) + 8);
    FW(arg1, 0x5C) = (s32) (FW(arg1, 0x58) + (FW(arg1, 0x64) * 8));
    sp60 = game_libs_func_00070FCC(FW(arg1, 0x4), FW(arg1, 0x8), (u16 *)7, (int)arg1 + 0x2C);
    if (sp60 != 0) {
        return sp60;
    }
    temp_v0 = game_libs_func_00070FCC(arg1);
    sp60 = temp_v0;
    FW(arg1, 0x0) = (s32) (FW(arg1, 0x0) | 1);
    return temp_v0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071384);
#endif
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
extern int gl_func_00000000();
extern int D_00000000;
// pak/save-data status query. Runs hook chain (notify a1; status=cb(1,&D);
// cb(a0,&buf20,1); status=cb(0,&D); cb(a0,&buf20,1); cb(a1,&buf1C)), then
// decodes the flag bytes at buf1C[2] (flags_1E) / buf1C[3] (flags_1F):
// (1&2)->2, flags_1F!=0 or !(flags_1E&1)->1, flags_1E&4->4, else the saved
// hook status. Reloc-blind cbs + &D.
int gl_func_00071624(char *a0, char *a1) {
    int status;
    int buf20;
    int buf1C;
    unsigned char flags;
    status = 0;
    gl_func_00000000(a1);
    status = gl_func_00000000(1, (char *)&D_00000000);
    gl_func_00000000(a0, &buf20, 1);
    status = gl_func_00000000(0, (char *)&D_00000000);
    gl_func_00000000(a0, &buf20, 1);
    gl_func_00000000(a1, &buf1C);
    flags = ((unsigned char *)&buf1C)[2];
    if ((flags & 1) && (flags & 2)) {
        return 2;
    }
    if (((unsigned char *)&buf1C)[3] != 0) {
        return 1;
    }
    if ((flags & 1) == 0) {
        return 1;
    }
    if (flags & 4) {
        return 4;
    }
    return status;
}
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
extern int D_00000000;
// Record-stream emitter (swl/swr template family). Clears a flag byte at &D,
// sets &D+0x3C=1, inits the dst cursor to &D. Builds a 6-byte template
// {1,3,0,0xFF,0xFF,0xFF} on the stack; clears a0 leading bytes via the cursor,
// then writes the template (unaligned 4-byte swl/swr + 2 bytes), advances 6,
// and lays a 0xFE terminator. Reloc-blind &D globals.
void gl_func_00071708(int a0) {
    unsigned char tmpl[8];
    unsigned char *dst;
    int i;
    *(char *)&D_00000000 = 0;
    *(int *)((char *)&D_00000000 + 0x3C) = 1;
    dst = (unsigned char *)&D_00000000;
    tmpl[0] = 1;
    tmpl[1] = 3;
    tmpl[2] = 0;
    tmpl[3] = 0xFF;
    tmpl[4] = 0xFF;
    tmpl[5] = 0xFF;
    for (i = 0; i < a0; i++) {
        *dst = 0;
        dst++;
    }
    *(int *)dst = *(int *)tmpl;
    dst[4] = tmpl[4];
    dst[5] = tmpl[5];
    dst += 6;
    *dst = 0xFE;
}
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
// Record decoder. Advances the (caller-set) src cursor by a0 records, reads a
// 6-byte record (lwl/lwr + 2 bytes) into a local, then decodes: out->3 =
// (rec[1] & 0xC0) >> 4; if that is 0, out->0 = (rec[4]<<8)|rec[3] (halfword)
// and out->2 = rec[5]. The cursor base is caller-set ($t6) — modeled as a
// param, so only the dispatch reg differs.
void gl_func_000717CC(int a0, char *out, char *cursor) {
    unsigned char rec[8];
    int i;
    if (a0 > 0) {
        i = 0;
        do {
            cursor += 1;
            i++;
        } while (i < a0);
    }
    *(int *)rec = *(int *)cursor;
    rec[4] = cursor[4];
    rec[5] = cursor[5];
    *(char *)(out + 3) = (rec[1] & 0xC0) >> 4;
    if (*(unsigned char *)(out + 3) == 0) {
        *(short *)(out + 0) = (rec[4] << 8) | rec[3];
        *(char *)(out + 2) = rec[5];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000717CC);
#endif
