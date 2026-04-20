#include "common.h"

/* Run 10 members (now covers 0x12AC4..0x12BF8). */

extern int func_00000000();

void func_00012AC4(char *a0, char *a1, int a2) {
    if (a1 != 0) {
        if (*(int*)(a0 + 0x168) == 0) {
            *(int*)(a0 + 0x168) = *(int*)(a0 + 0x160);
        }
        *(char*)(a0 + 0x178) = (char)*(int*)(a0 + 0x64);
        *(char*)(a0 + 0x179) = (char)*(int*)(a0 + 0x4C);
        *(char*)(a0 + 0x17A) = (char)*(int*)(a0 + 0x50);
        *(char*)(a0 + 0x17B) = (char)*(int*)(a0 + 0x54);
        *(int*)(a1 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x164), a0 + 0x170);
        *(int*)(a0 + 0x184) = 0;
    }
}

void func_00012B7C(char *a0, int a1, int a2) {
    if (a1 != 0) {
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x170));
    }
    if (a2 != 0) {
        func_00000000(a2, ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][2], ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][1]);
    }
}
