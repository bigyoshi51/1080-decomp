/* IDO 5.3 -O2 -mips2 donor for gl_func_000743C4 = libc lldiv
 * (ldiv.c/xldiv.c verbatim, the long-long sibling of the already-landed
 * gl_func_000744CC = ldiv). PROVEN EXACT 2026-08-22: 64/64 words
 * identical at -O2 first compile. o32 struct return: $a0 = sret
 * pointer, ($a2,$a3) = numer, (sp+0x40,0x44) = denom. The two jal-0
 * words are the compiler-generated __ll_div / __ll_mul intrinsics --
 * blank in the USO (load-time relocs); POST_COMPILE renames them to
 * gl_func_00000000_{lldivq743,llmul743} pins = 0 (undefined_syms_auto)
 * so the link bakes 0x0C000000 verbatim. (__ll_mul is pinned to its
 * KERNEL address 0x80002F78 for other units -- the rename is load-
 * bearing.) IDENTITY CORROBORATION: the xlitob.c donor (74554 = _Litob)
 * ships a blank lldiv jal whose USO load-time reloc points exactly
 * here. Old NM-wrap "timestamp/range helper" re-derivation (54.8%) and
 * its frame/aliasing residual notes are retired -- the "two chained
 * 64-bit helpers" were __ll_div and __ll_mul, and the whole fn is
 * verbatim Plauger lldiv. POST_COMPILE renames lldiv ->
 * gl_func_000743C4 for the REPLACE_FUNC_BODY splice key. Spliced into
 * game_libs_post2b_d.c.o. */

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

lldiv_t lldiv(long long num, long long denom)
{
    lldiv_t ret;

    ret.quot = num / denom;
    ret.rem = num - denom * ret.quot;
    if (ret.quot < 0 && ret.rem > 0)
    {
        ret.quot++;
        ret.rem -= denom;
    }

    return ret;
}
