/* -O1 donor for gl_func_0006FAD4 — 32-insn flag-extract + conditional
 * bit-set/clear (frame 0x20, saves ra only). PROVEN EXACT 32/32 at IDO 7.1
 * -O1 (2026-07-08 standalone probe; plain -O1, no -g3; 5.3 -O1 emits the
 * identical 32 words). post1b2c builds -O2, where the flag if/else collapses
 * to beql/sw-in-delay — the target is simply -O1: args/locals sp-homed,
 * state reloaded per use, if/else emitted as li/b/sw + sw-zero arms, both
 * arg reloads for the two a0[1] statements kept separate.
 * Levers: (1) plain if/else (NOT ?:) for flag; (2) two separate a0[1]
 * statements (|= then &= ~2) — each reloads the homed arg; (3) return the
 * homed flag (lw v0,0x18(sp) in the epilogue).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; blank-extern jal reloc imported by the splice). */
extern int gl_func_00000000();

int gl_func_0006FAD4(int *arg) {
    int state;
    int flag;

    state = gl_func_00000000();
    if (state & 0x100) {
        flag = 1;
    } else {
        flag = 0;
    }
    if (state & 0x80) {
        arg[1] |= flag;
        arg[1] &= ~2;
    }
    return flag;
}
