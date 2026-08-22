/* IDO 5.3 -O2 -mips2 donor for game_libs_func_0006F1D8 +
 * game_libs_func_0006F1FC = libc strchr (Plauger, verbatim). PROVEN
 * EXACT 2026-08-22: 16/16 words identical at -O2 first compile, ZERO
 * relocs. splat split the ONE function at the loop-bottom label:
 *   0x6F1D8 [0x0,0x24)  = head (lbu/andi/andi + beql match test)
 *   0x6F1FC [0x24,0x40) = loop tail (lbu+1/addiu/bne back into the
 *                         head; incl. the jr-delay nop)
 * -- the old "leaf-branch-past-end CAP" / "caller-set $v0 tail
 * fragment" notes describe the two halves of this split, both retired.
 * Sits in the Plauger string cluster: 6F17C = memcpy (non-unrolled 5.3
 * shape), 6F1B0 = strlen (already matched in-unit), 6F1D8 = strchr.
 * POST_COMPILE adds the two splice-key symbols at their offsets
 * (metadata only, bytes untouched); both spliced from this one donor
 * into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */

char *strchr(const char *s, int c)
{
	const char ch = c;

	for (; *s != ch; ++s)
		if (*s == '\0')
			return (0);
	return ((char *)s);
}
