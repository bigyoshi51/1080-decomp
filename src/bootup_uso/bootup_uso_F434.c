#include "common.h"

/* -O0 sub-file covering bootup_uso offset 0xF6C4..0xF76B (single function,
 * 42 insns, 0xA8 bytes). Layout shim between bootup_uso_o0_F390.c and
 * bootup_uso_o0_F7F4.c -O0 clusters. The asm has -O0 hallmarks (8-byte
 * a0-spill on every use, dead `b +1; nop` BB-end marker before epilogue,
 * no register caching across statements) so the file-level OPT_FLAGS is
 * -O0 (set in the Makefile). */

extern int func_00000000();
extern int func_00000188();

#ifdef NON_MATCHING
/* 42-insn -O0 method dispatcher: optionally invokes a pre-call hook
 * (vtable[0x6C] with arg = base + h_68) when state field 0x2C is zero,
 * runs the USO helper on a0, then optionally invokes a post-call hook
 * (vtable[0x64], h_60) gated by both state-nonzero AND a global-flag
 * predicate read from `func_00000188 + 0x198`.
 *
 * Cap: 1 extra `lw a0_spill` per indirect-call arm. Expected reuses the
 * a0-load (in $t8) that fed the m-deref to also feed the addu; my -O0
 * emit reissues the load. Net 2 extra insns vs expected (44 vs 42).
 * Shift cascades through the file giving fuzzy ~63%. The lui+addiu+lw
 * (3 insns) for `&func_00000188+0x198` vs expected lui+lw direct (2)
 * adds 1 more diff per arm; baked into the 63% as well. */
void func_0000F6C4(char *a0) {
    register char *m;
    if (*(int*)(a0 + 0x2C) == 0) {
        m = *(char**)(a0 + 0x28);
        (*(int(**)())(m + 0x6C))(*(short*)(m + 0x68) + a0);
    }
    func_00000000(a0);
    if (*(int*)(a0 + 0x2C) != 0) {
        if (func_00000000(*(int*)((char*)&func_00000188 + 0x8 + 0x190))) {
            m = *(char**)(a0 + 0x28);
            (*(int(**)())(m + 0x64))(*(short*)(m + 0x60) + a0);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F6C4);
#endif
