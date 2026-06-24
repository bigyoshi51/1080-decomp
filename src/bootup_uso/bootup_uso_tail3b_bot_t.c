#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void func_0001266C(char *a0, int a1) {
    register u16 *p;

    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p & ~3;
    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p | a1;
    func_00000000((*(u16 *)(*(char **)(a0 + 0x154) + 4)) & 3);
}

#ifdef NON_MATCHING



#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
/* func_000126EC [84.95%, -O0, capped]: residual is -O0 literal-address-0 materialization
 * (`*(int*)0=arg1` emits sw 0(zero) vs target lui;sw) + short-load + move-s0-s1. The
 * struct-cast-fold lever does NOT apply: relocs checked (2026-06-24) — the only reloc is the
 * R_MIPS_26 call; the 0/0x28 reads are LITERAL addresses, not D_00000000-relative, so there
 * is no base symbol to fold against. Don't re-attempt the struct-cast on it. */
typedef char *(*GP_000126EC)();
void func_000126EC(char *arg0, s32 arg1) {
    s32 sp34;
    register u16 *p;
    register s32 *q;
    register char *r;

    p = (u16 *)(*(char **)(arg0 + 0x154) + 4);
    *p = *p & ~4;
    if (arg1 != 0) {
        p = (u16 *)(*(char **)(arg0 + 0x154) + 4);
        *p = *p | 4;
    }
    *(int*)0 = arg1;
    q = &sp34;
    if ((q != 0) || (q = ((s32 *(*)())func_00000000)(0xC), (q != 0))) {
        *q = 0x15;
    }
    r = *(char **)0x28;
    ((GP_000126EC)FW(r, 0x34))(FW(r, 0x30), q);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);
#endif

/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 * Promoted from NM wrap 2026-05-17 (file is -O0 per file split). */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
