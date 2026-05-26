#include "common.h"

extern int func_00000000();

/* Mid-tail assembly gap after func_00011AB4 was split to an -O0 file.
 * Holds 0x11B5C..0x11C70 so the following o0_11C70 split keeps its offset. */
#ifdef NON_MATCHING
/* func_00011B5C: 37-insn -O0 flag-set + per-element-1-call loop, returns the
 * old _188 flag (saves it, sets _188=1, calls helper(arg,1) per item).
 * CAP: -O0 return-value DEAD-double-b toolchain gap. Identical structure to
 * the LANDED void sibling func_00011BF0 below (if-guard + do-while) — the ONLY
 * difference is this one returns a value, so our cc emits `lw v0; b epi; nop;
 * b epi; nop` (second b dead/unreachable) where the target has ONE b -> built
 * .o is +8 bytes, never matches. Proven a toolchain-binary codegen gap (trivial
 * `int f(int*a){int x=a[0];g();return x;}` reproduces it; no -g/-O level or IDO
 * 5.3-vs-7.1 flips it; void -O0 fns are unaffected, hence BF0 lands). NOT
 * C-fixable, NOT permuter-fixable; stripping the dead b = match-faking (banned).
 * See docs/IDO_CODEGEN.md#feedback-ido-o0-return-value-dead-double-b. */
s32 func_00011B5C(s32 *a0) {
    s32 saved = *(s32*)((char*)a0 + 0x188);
    s32 i;
    *(s32*)((char*)a0 + 0x188) = 1;
    i = 0;
    if (*(s32*)((char*)a0 + 0x124) > 0) {
        do {
            func_00000000(*(s32*)((char*)a0 + 0x100 + i * 4), 1);
        } while (++i < *(s32*)((char*)a0 + 0x124));
    }
    return saved;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);
#endif

void func_00011BF0(char *a0) {
    s32 i;

    i = 0;
    if (*(s32*)(a0 + 0x124) > 0) {
        do {
            func_00000000(*(s32*)(a0 + 0x100 + i * 4), 0);
        } while (++i < *(s32*)(a0 + 0x124));
    }
    *(s32*)(a0 + 0x188) = 0;
}
