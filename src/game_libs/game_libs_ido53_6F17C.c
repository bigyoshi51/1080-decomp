/* IDO 5.3 -O2 -mips2 donor for game_libs_func_0006F17C = libc memcpy
 * (Plauger, verbatim; size_t n unsigned => beqz/bnez loop guard).
 * PROVEN EXACT 2026-08-22: 11/11 body words identical at -O2 first
 * compile, ZERO relocs. 5.3 -O2 emits the target's NON-unrolled byte
 * loop exactly -- the old "UNROLL CAP" verdict was a 7.1-vs-5.3
 * artifact (7.1 -O2 unrolls by 4; 5.3 doesn't). The symbol's 2 leading
 * all-zero pad words (0x6F17C/0x6F180) are re-homed to the
 * _pad_pre_game_libs_func_0006F17C GLOBAL_ASM block in post1b2c; true
 * entry = 0x6F184, body 0x2C. Plauger string cluster: 6F17C = memcpy,
 * 6F1B0 = strlen (matched in-unit), 6F1D8 = strchr (landed).
 * POST_COMPILE renames memcpy -> game_libs_func_0006F17C for the
 * REPLACE_FUNC_BODY splice key. Spliced into game_libs_post1b2c.c.o. */

typedef unsigned int size_t;

void *memcpy(void *s1, const void *s2, size_t n)
{
	char *su1 = (char *)s1;
	const char *su2 = (const char *)s2;

	for (; 0 < n; ++su1, ++su2, --n)
		*su1 = *su2;
	return (s1);
}
