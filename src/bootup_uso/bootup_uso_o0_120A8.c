#include "common.h"

/* Run 8 of bootup_uso's -O0 region (0x120A8..0x12243). 4 functions.
 * See project_1080_bootup_uso_o0_runs.md + feedback_ido_o0_empty_stub.md.
 * func_00012188 (0x12188, 0xBC) moved here from bootup_uso_tail3b_top.c:
 * it is -O0 codegen (fresh addiu rN,zero,1 per `=1` store, stack-stored
 * loop counter `sw zero,4(sp)`, unfilled-delay epilogue). `register int v`
 * reuses $a1 across the value-pair stores; plain `for` keeps `i` on stack.
 * Byte-exact at -O0; trailing 8-byte-align nop dropped by TRUNCATE 0x19C. */

extern int func_00000000();
extern int D_00000150;

void func_000120A8(char *a0, int a1, int a2, int a3) {
    *(int*)(a0 + 0x13C) = a1;
    *(int*)(a0 + 0x144) = a2;
    func_00000000(*(int*)(a0 + 0x13C), *(int*)(a0 + 0x144), 0);
    *(int*)(a0 + 0x144) = 0;
}

void func_00012110(int a0) {
    func_00000000(D_00000150);
    func_00000000(7);
}

void func_00012150(char *a0) {
    func_00000000(*(int*)(a0 + 0x148), *(int*)(a0 + 0x154));
}

void func_00012188(char *a0) {
    int i;
    register int v;
    *(s32*)(a0 + 0x68) = 0;
    *(s32*)(a0 + 0x4C) = 1;
    *(s32*)(a0 + 0x50) = 0;
    *(s32*)(a0 + 0x54) = 1;
    *(s32*)(a0 + 0x58) = 1;
    *(s32*)(a0 + 0x5C) = 0;
    *(s32*)(a0 + 0x60) = 1;
    *(s32*)(a0 + 0x64) = 2;
    *(s32*)(a0 + 0x80) = 0;
    for (i = 0; i < 3; i++) { *(a0 + i + 0x158) = 0x2A; }
    *(s32*)(a0 + 0x15C) = 0;
    v = 4; *(s32*)(a0 + 0x90) = v; *(s32*)(a0 + 0xB4) = v;
    v = 3; *(s32*)(a0 + 0x94) = v; *(s32*)(a0 + 0xB0) = v;
    v = 1; *(s32*)(a0 + 0x98) = v; *(s32*)(a0 + 0xA8) = v;
    v = 2; *(s32*)(a0 + 0x9C) = v; *(s32*)(a0 + 0xAC) = v;
    v = 5; *(s32*)(a0 + 0xA0) = v; *(s32*)(a0 + 0xA4) = v;
}
