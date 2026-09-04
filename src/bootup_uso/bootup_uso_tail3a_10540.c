#include "common.h"

/* Bottom piece of the original bootup_uso_tail3a.c (carved 2026-07-10).
 * 2026-09-04: func_00010540 moved out to bootup_uso_o0_10540.c where it
 * MATCHES at -O0 (343/343). This file now holds only the two tiny matched
 * -O2 -g3 functions func_00010A9C / func_00010AA8 (TRUNCATE_TEXT 0x14 clips
 * the section pad that appears once the 0x55C body ahead of them is gone). */

void func_00010A9C(int *a0) {
    *(int*)((char*)a0 + 0x78) = 0;
}

void func_00010AA8(void) {
}
