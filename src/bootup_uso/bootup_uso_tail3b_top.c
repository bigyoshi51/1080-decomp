#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;


#ifdef NON_MATCHING
/* func_00012188: 47-insn struct initializer at 0x12188. 55.30% NM.
 * Sets up 11 int fields + 3-byte init loop at 0x158 + 11 more int fields
 * grouped by value. Match cap (~8 insns) is structural codegen-class:
 *  1. Expected uses NEW reg per `1` value (t6,t7,t8,t9 each `addiu rN,
 *     zero, 1`); IDO -O2 hoists to one reg. Temp-var pattern collapses by
 *     CSE.
 *  2. Loop body has `addiu t1, zero, 0x2A` INSIDE loop; build hoists.
 *  3. Epilogue: `b L12238; nop; addiu sp,8; jr ra; nop` (5 unfilled-delay
 *     insns); build emits filled `jr ra; addiu sp,8` (2). `goto end;`
 *     attempt eliminated by IDO.
 *
 * Tried: -O0 (35%), -O1 (40%), -O2 (45%), -O2 -g3 (55%). -O2 -g3 wins.
 * volatile loop-counter required to match the stack-stored sp4 pattern
 * (`sw t5, 4(sp)` per-iter); without volatile, IDO eliminates the loop
 * structurally (register-only, no stack store). */
void func_00012188(char *a0) {
    volatile s32 sp4;
    s32 next;
    s32 v;

    *(s32*)(a0 + 0x68) = 0;
    v = 1; *(s32*)(a0 + 0x4C) = v;
    *(s32*)(a0 + 0x50) = 0;
    v = 1; *(s32*)(a0 + 0x54) = v;
    v = 1; *(s32*)(a0 + 0x58) = v;
    *(s32*)(a0 + 0x5C) = 0;
    v = 1; *(s32*)(a0 + 0x60) = v;
    v = 2; *(s32*)(a0 + 0x64) = v;
    *(s32*)(a0 + 0x80) = 0;
    sp4 = 0;
    do {
        *(a0 + sp4 + 0x158) = 0x2A;
        next = sp4 + 1;
        sp4 = next;
    } while (next < 3);
    *(s32*)(a0 + 0x15C) = 0;
    v = 4; *(s32*)(a0 + 0x90) = v; *(s32*)(a0 + 0xB4) = v;
    v = 3; *(s32*)(a0 + 0x94) = v; *(s32*)(a0 + 0xB0) = v;
    v = 1; *(s32*)(a0 + 0x98) = v; *(s32*)(a0 + 0xA8) = v;
    v = 2; *(s32*)(a0 + 0x9C) = v; *(s32*)(a0 + 0xAC) = v;
    v = 5; *(s32*)(a0 + 0xA0) = v; *(s32*)(a0 + 0xA4) = v;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012188);
#endif

#ifdef NON_MATCHING
/* func_00012244: 32-insn set-bit-and-call-if-not-set helper.
 *   short *p = a0->field_154;
 *   if ((*p & (1 << a1)) == 0) {
 *       *p |= (1 << a1);
 *       func_00000000(a0);
 *   }
 *
 * 36% NM at -O2 -g3 (file's default). This function is in one of the
 * scattered -O0 runs documented in project_1080_bootup_uso_o0_runs.md —
 * target asm has both args spilled at entry (sw a0, 0x28(sp); sw a1,
 * 0x2C(sp)) and every variable reloaded via stack at use sites, classic
 * -O0 emit pattern (32 insns, frame 0x28). My -O2 emit collapses to 14
 * insns with frame 0x18.
 *
 * To match: split this function into a separate .c file with OPT_FLAGS
 * := -O0 per the -O0-cluster recipe in
 * docs/IDO_CODEGEN.md#feedback-o0-cluster-split-with-layout-shim.
 * Needs paired predecessor + successor layout shim. Multi-tick effort. */
extern int func_00000000();
void func_00012244(int *a0, int a1) {
    unsigned short *p = (unsigned short*)a0[0x154/4];
    if ((*p & (1 << a1)) == 0) {
        *p = *p | (1 << a1);
        func_00000000(a0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012244);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);

