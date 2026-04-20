#include "common.h"

/* Run 8 of bootup_uso's -O0 region (0x120A8..0x12187). 3 functions.
 * See project_1080_bootup_uso_o0_runs.md + feedback_ido_o0_empty_stub.md. */

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
