/* -O1 donor for gl_func_0006B974 — 16-insn call-sandwich wrapper:
 * hook(); r = work(a0, a1); unhook(); return r.
 * PROVEN EXACT 16/16 at IDO 7.1 -O1 (2026-07-08 standalone probe; plain -O1,
 * NO -g3 — -g3 pins the sw s0 out of the first jal delay slot and breaks it).
 * post1b builds -O2 where the arg home stores (sw a0/a1 into the incoming
 * slots) are dead-store-eliminated. Levers:
 *   (1) plain (non-register) a0/a1 params = -O1 early homing to sp+0x28/0x2C
 *       and reload before the second call;
 *   (2) `register int r;` = result held in $s0 across the third call
 *       (plain local homes to a stack slot instead: sw/lw v0).
 * Spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY (real -O1 compiler
 * output; only blank-extern jal relocs, imported by the splice). */
extern int gl_func_00000000();

int gl_func_0006B974(int a0, int a1) {
    register int r;
    gl_func_00000000();
    r = gl_func_00000000(a0, a1);
    gl_func_00000000();
    return r;
}
