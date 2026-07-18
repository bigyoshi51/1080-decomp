/* -O1 donor for gl_func_00073034 — 16-insn call-sandwich wrapper, raw-word
 * IDENTICAL (16/16, 2026-07-17 sibling scan) to gl_func_0006B974:
 * hook(); r = work(a0, a1); unhook(); return r.
 * Same -O1 island recipe (0x6B7A0..0x73824 batch): plain -O1, NO -g3 (-g3
 * pins the sw s0 out of the first jal delay slot). Levers:
 *   (1) plain (non-register) a0/a1 params = -O1 early homing to sp+0x28/0x2C
 *       and reload before the second call;
 *   (2) `register int r;` = result held in $s0 across the third call.
 * The old post2b_c NM wrap's "permuter-range scheduling residual" verdict is
 * RETRACTED — that probe ran the wrap at the TU's default opt; the fn is
 * plain IDO 7.1 -O1 like its byte-twin. Spliced into game_libs_post2b_c.c.o
 * via REPLACE_FUNC_BODY (real -O1 compiler output; only blank-extern jal
 * relocs, imported by the splice). */
extern int gl_func_00000000();

int gl_func_00073034(int a0, int a1) {
    register int r;
    gl_func_00000000();
    r = gl_func_00000000(a0, a1);
    gl_func_00000000();
    return r;
}
