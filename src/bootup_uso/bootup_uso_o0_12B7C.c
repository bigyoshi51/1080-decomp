#include "common.h"

/* Run 10 member (single function pulled out for -O0 match). */

extern int func_00000000();

void func_00012B7C(char *a0, int a1, int a2) {
    if (a1 != 0) {
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x170));
    }
    if (a2 != 0) {
        func_00000000(a2, ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][2], ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][1]);
    }
}
