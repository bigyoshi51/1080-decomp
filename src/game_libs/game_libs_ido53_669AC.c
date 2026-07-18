/* IDO 5.3 -O2 -mips2 donor for gl_func_000669B8 = 5-call debug-print
 * dispatch. PROVEN EXACT 41/41 standalone against the concatenated
 * 0x669AC..0x66A4C stream.
 * BOUNDARY FIX: splat's game_libs_func_000669AC (0xC, no jr ra:
 * `lui $v1,%hi(D); addiu $v1; lw $v0,0($v1)`) was this function's HOISTED
 * HEAD — IDO 5.3 -O2 schedules the debug-state global load before the
 * addiu-sp prologue, and splat split at the prologue (0x669B8). True
 * entry = 0x669AC; the spliced symbol covers 0x669AC..0x66A4C (0xA4).
 * The old "caller-set $v0/$v1 cap" reading was wrong: $v1 = &global,
 * $v0 = its loaded value, both compiler-hoisted.
 * COMPILER FINGERPRINT: needs 5.3 -O2 AND -mips2 (the default MIPSISET;
 * mips1 scheduling pads `lw $t9; jalr $t9` with a hazard nop and floats
 * the str-addius into the load gaps). `int rc;` declared BEFORE the `st`
 * alias is load-bearing: decl order sets rc's cross-call spill slot
 * (target 0x1C vs 0x18 in the 0x20 frame); the no-alias direct-deref
 * spelling is byte-identical (both renumber rc's spill to 0x1C).
 * Blank externs: D_00000000_dbg669 = the debug-state pointer global
 * (kept-address head load in $v1/$v0, then two lui/lw reloads after the
 * aliasing f34 store / the calls); D_00000000 + 0x217C/0x2184/0x218C/
 * 0x21A4/0x21AC = the five format strings; gl_func_00000000_print669 =
 * the print sink (blank jal x3).
 * Spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY. */
typedef struct {
    int f00;            /* 0x00 */
    int f04;            /* 0x04 */
    char pad08[0x28];   /* 0x08 */
    int f30;            /* 0x30 */
    int f34;            /* 0x34 — copied from f30 each dispatch */
    char pad38[0x8];    /* 0x38 */
    int (*vt40)();      /* 0x40 — status query, returns rc */
    void (*vt44)();     /* 0x44 — banner print */
} Dbg669;

extern Dbg669 *D_00000000_dbg669;
extern char D_00000000[];
extern void gl_func_00000000_print669();

void gl_func_000669B8(void) {
    int rc;
    Dbg669 *st = D_00000000_dbg669;

    st->f34 = st->f30;
    D_00000000_dbg669->vt44((char *)D_00000000 + 0x217C);
    rc = D_00000000_dbg669->vt40((char *)D_00000000 + 0x2184);
    if (rc != 0) {
        gl_func_00000000_print669((char *)D_00000000 + 0x218C, rc);
    }
    gl_func_00000000_print669((char *)D_00000000 + 0x21A4, rc);
    gl_func_00000000_print669((char *)D_00000000 + 0x21AC, D_00000000_dbg669->f00, D_00000000_dbg669->f04);
}
