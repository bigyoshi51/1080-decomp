#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

#ifdef NON_MATCHING
/* int reader template matching boarder5_uso_func_000000D4 (same 15-insn body
 * gl_func_00000000(&D_00000000, buf, 4); *dst = buf[0]) — but target has an
 * EXTRA first instruction `beq zero, zero, +0x736F` (word 0x1000736F) before
 * the standard prologue. That trampoline insn is USO-loader infrastructure
 * (arcproc/h2hproc/eddproc/n64proc func_00000000 share the same pattern with
 * different branch offsets), injected by the linker/loader, not emitted by
 * any C construct IDO knows. Body matches 15/16 insns; the trampoline prefix
 * is unreachable from C alone. A leading-pad sidecar analog (mirror of
 * feedback_pad_sidecar_unblocks_trailing_nops.md) was attempted 2026-04-21:
 * created `<func>_prefix.s` with `glabel boarder5_uso_func_00000000; .word
 * 0x1000736F; endlabel ...` and `#pragma GLOBAL_ASM(prefix.s)` placed BEFORE
 * the C function decl.
 *   Result: asm-processor fails with "symbol defined twice" because both the
 *   sidecar's glabel and the C function emit the same symbol. Using a
 *   different glabel name (`_pre_boarder5...`) resolves the collision but
 *   leaves the real symbol `boarder5_uso_func_00000000` at +0x04 with size
 *   0x3C — target has it at +0x00 with size 0x40. objdiff compares by name;
 *   post-link bytes match but the per-symbol .o-level comparison mismatches.
 * Root cause: asm-processor's pragma mechanism was designed for TRAILING
 * pads that don't overlap function symbols. A leading mechanism would need
 * linker-level support (extend symbol start 4 bytes earlier via `.size`
 * manipulation OR post-link ELF patch). Out of scope for a single tick.
 * Keep as INCLUDE_ASM. See feedback_prefix_sidecar_symbol_collision.md. */
void boarder5_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
#else
INCLUDE_ASM("asm/nonmatchings/boarder5_uso/boarder5_uso", boarder5_uso_func_00000000);
#endif

void boarder5_uso_func_00000040(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void boarder5_uso_func_00000098(char *dst) {
    int tmp;
    gl_func_00000000(&tmp);
    boarder5_uso_func_00000040((Quad4*)(dst + 0x10));
}
#pragma GLOBAL_ASM("asm/nonmatchings/boarder5_uso/boarder5_uso/boarder5_uso_func_00000098_pad.s")

void boarder5_uso_func_000000D4(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void boarder5_uso_func_00000110(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void boarder5_uso_func_00000168(char *dst) {
    int tmp;
    boarder5_uso_func_000000D4(&tmp);
    boarder5_uso_func_00000110((Quad4*)(dst + 0x10));
}
