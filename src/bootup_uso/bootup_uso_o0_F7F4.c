#include "common.h"

/* These two functions compile at -O0, not -O2. The -O0 output is a 5-insn
 * stub (`sw a0,0(sp); b +1; nop; jr ra; nop`) that -O2 collapses to 2 insns.
 * See feedback_ido_o0_empty_stub.md. */

void func_0000F7F4(int a0) {}

void func_0000F808(int a0) {}
