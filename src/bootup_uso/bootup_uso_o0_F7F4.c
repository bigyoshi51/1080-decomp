#include "common.h"

/* -O0 run: 0xF6C4..0xFBCB. These functions compile at -O0, not -O2.
 * See project_1080_bootup_uso_o0_runs.md + feedback_ido_o0_empty_stub.md. */

extern int func_00000000();
extern void *D_00000030;
extern char D_00000000;

/* func_0000F76C: -O0 init+dispatch wrapper (sibling of func_000100F0).
 * RE-MATCHED 2026-06-10 (previous body was a silent false match: it passed
 * NULL where the target passes &D_00000000 — lui/addiu vs move a0,zero —
 * and used a separate p-statement, leaving 8 wrong words at same length).
 * Match keys: (1) first call arg is &D_00000000 (reloc-bearing %hi/%lo pair);
 * (2) `register char *p` in $s0 with the p-assignment EMBEDDED in the call's
 * argument expression so one $t6 a0-load serves the p-load and the addu
 * (same lever as func_000100F0 in bootup_uso_o0_100F0.c). */
void func_0000F76C(char *a0) {
    register char *p;
    func_00000000(&D_00000000);
    (**(void (**)())(p + 0x74))(
        *(short*)((p = *(char**)(a0 + 0x28)) + 0x70) + (int)a0);
    func_00000000(a0);
}

void func_0000F7D0(int a0) {
    D_00000030 = (void*)func_00000000;
}

void func_0000F7F4(int a0) {}

void func_0000F808(int a0) {}
