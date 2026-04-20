#include "common.h"

/* -O0 run: 0xF6C4..0xFBCB. These functions compile at -O0, not -O2.
 * See project_1080_bootup_uso_o0_runs.md + feedback_ido_o0_empty_stub.md. */

extern int func_00000000();
extern void *D_00000030;

void func_0000F7D0(int a0) {
    D_00000030 = (void*)func_00000000;
}

void func_0000F7F4(int a0) {}

void func_0000F808(int a0) {}
