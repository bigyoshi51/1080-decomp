#include "common.h"

/* kernel_018_o2: carve-out of func_8000745C (rmon thread/request-chain walker).
 *
 * NOTE: despite the historical "_o2" filename, this function actually builds at
 * -O1 (see OPT_FLAGS override in the Makefile). The target uses register vars in
 * s0/s1 with PLAIN branches (no branch-likely) and fresh `li at,-1` per compare
 * plus no-CSE double-loads of unk4 -- the -O1 codegen signature. Building it at
 * -O2 folds every branch to beql/bnel and hoists -1 into a saved reg, diverging
 * hard. -O1 + `register` keywords reproduces the exact saved-reg coloring.
 * Byte-exact 2026-06-23. */

typedef struct RmonNode {
    char pad0[4];
    s32 unk4;
    char pad8[4];
    struct RmonNode *unkC;
    char pad10[4];
    s32 unk14;
} RmonNode;

extern s32 func_800081D0(RmonNode *);
extern RmonNode *func_80009C30(void);

/* arg0 != 0: find the chain node whose unk14 == arg0 and, if it holds a live
 * request (0 < unk4 < 0x80), service it via func_800081D0; returns arg0.
 * arg0 == 0: service every live node in the chain; returns -1.
 * unk4 == -1 is the chain end sentinel; unkC links to the next node. */
s32 func_8000745C(s32 arg0) {
    register s32 result;
    register RmonNode *p;

    result = 0;
    p = func_80009C30();
    if (arg0 != 0) {
        if (p->unk4 != -1) {
            for (;;) {
                if (p->unk14 == arg0) {
                    break;
                }
                p = p->unkC;
                if (p->unk4 == -1) {
                    break;
                }
            }
        }
        if (p->unk4 == -1) {
            return 0;
        }
        if (p->unk4 > 0 && p->unk4 < 0x80) {
            func_800081D0(p);
            result = arg0;
        }
        goto end;
    }
    if (p->unk4 != -1) {
        do {
            if (p->unk4 > 0 && p->unk4 < 0x80) {
                func_800081D0(p);
                result = -1;
            }
            p = p->unkC;
        } while (p->unk4 != -1);
    }
end:
    return result;
}
