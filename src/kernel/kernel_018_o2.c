#include "common.h"

/* kernel_018_o2: -O2 carve-out of func_8000745C, which is the ONE function in
 * kernel_018 that prefers -O2 (62.6%) over -O1 (58.8%, +14 insns bloat). The
 * rest of kernel_018 was flipped to -O1 (7 functions improved, e.g. func_80007698
 * 43->94%). objdiff is per-function so this carve keeps func_8000745C at -O2 with
 * no regression. Verified 2026-06-04. */

#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
#endif
extern void func_800081D0();
extern char *func_80009C30(void);
/* Thread/request-chain walker (rmon). func_80009C30 = chain head; nodes link
 * via ->unkC, carry a request-id at ->unk4 (-1 = end sentinel) and a key at
 * ->unk14. arg0!=0: find the node whose unk14==arg0 and, if it holds a live
 * request (0 < id < 0x80), service it via func_800081D0 (returns arg0).
 * arg0==0: service every live node, returns -1. */
s32 func_8000745C(s32 arg0) {
    s32 var_s0;
    void *var_s1;

    var_s0 = 0;
    var_s1 = (void *) func_80009C30();
    if (arg0 != 0) {
        if (FW(var_s1, 4) != -1) {
loop_2:
            if (FW(var_s1, 0x14) != arg0) {
                var_s1 = (void *) FW(var_s1, 0xC);
                if (FW(var_s1, 4) != -1) {
                    goto loop_2;
                }
            }
        }
        if (FW(var_s1, 4) == -1) {
            return 0;
        }
        if ((FW(var_s1, 4) > 0) && (FW(var_s1, 4) < 0x80)) {
            func_800081D0(var_s1);
            var_s0 = arg0;
        }
        goto block_14;
    }
    if (FW(var_s1, 4) != -1) {
        do {
            if ((FW(var_s1, 4) > 0) && (FW(var_s1, 4) < 0x80)) {
                func_800081D0(var_s1);
                var_s0 = -1;
            }
            var_s1 = (void *) FW(var_s1, 0xC);
        } while (FW(var_s1, 4) != -1);
    }
block_14:
    return var_s0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000745C);
#endif
