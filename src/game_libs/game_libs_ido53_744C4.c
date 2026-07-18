/* IDO 5.3 -O2 donor for gl_func_000744CC = libc ldiv (xldiv.c verbatim).
 * PROVEN EXACT 33/33 standalone at IDO 5.3 -O2 against the concatenated
 * 0x744C4..0x74548 stream (7.1 -O2 = 29/33: only the sret struct-copy
 * scratch regs differ, $at/$t0 vs $t9/$t8 — 5.3 codegen signature).
 * BOUNDARY FIX: splat's game_libs_func_000744C4 (0x8, no jr ra:
 * `div $zero,$a1,$a2; mflo $v0`) was this function's HOISTED HEAD — IDO
 * 5.3 schedules the div/mflo before the addiu-sp prologue (div latency
 * hiding), and splat split at the prologue (0x744CC). True entry =
 * 0x744C4; the spliced symbol covers 0x744C4..0x74548 (0x84). Same class
 * as gl_func_0006C2AC osDriveRomInit / gl_func_0006DC0C osCartRomInit.
 * The old "caller-set $v0 quotient guess" reading was wrong: $v0 is the
 * quotient computed by the stolen div/mflo head. MIPS o32 struct return:
 * $a0 = sret pointer, ($a1,$a2) = (numer, denom). Zero relocations —
 * donor is position-free; still a splice (host TU is IDO 7.1 -O2). */
typedef struct {
    int quot; /* 0x0 */
    int rem;  /* 0x4 */
} ldiv_t;

ldiv_t gl_func_000744CC(int numer, int denom) {
    ldiv_t ret;

    ret.quot = numer / denom;
    ret.rem = numer - denom * ret.quot;
    if (ret.quot < 0 && 0 < ret.rem) {
        ret.quot += 1;
        ret.rem -= denom;
    }
    return ret;
}
