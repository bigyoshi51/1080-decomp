#include "common.h"

/* -O0 donor for arcproc_uso_func_00000688 (48-insn struct-init + zero-loop).
 * Spliced into the -O2 tail1 object via REPLACE_FUNC_BODY (real -O0 output).
 * a0->[0x8] holds a pointer to an int block; -O0 reloads it before every
 * store (no CSE). Fields 0x00..0x1C + 0x34 seeded, then the int array at
 * 0x20 is zeroed [0, a0->[8]->[2]). Reloc-free — no linker fixups needed. */
void arcproc_uso_func_00000688(int *a0) {
    int i;
    ((int **)a0)[2][0] = 1;
    ((int **)a0)[2][1] = 0;
    ((int **)a0)[2][2] = 5;
    ((int **)a0)[2][3] = 2;
    ((int **)a0)[2][4] = 0;
    ((int **)a0)[2][5] = 3;
    ((int **)a0)[2][6] = 1;
    ((int **)a0)[2][7] = 4;
    ((int **)a0)[2][13] = 0;
    for (i = 0; i < ((int **)a0)[2][2]; i++) {
        ((int **)a0)[2][8 + i] = 0;
    }
}
