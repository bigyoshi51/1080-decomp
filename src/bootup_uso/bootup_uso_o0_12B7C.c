#include "common.h"

/* Run 10 members (now covers 0x12818..0x12BF8). */

extern int func_00000000();
extern int D_00000000;
extern int D_A0000200;

/* 99.73% NM cap (IDO -O0 fresh-temp allocator can't be flipped from C).
 * Promoted to exact via INSN_PATCH at offsets 0x5C/0x64 — Makefile entry
 * ports 2-word patch from agent-b. */
void func_00012818(char *a0, char *a1) {
    int i;
    register int *unused;

    i = 0;
    do {
        (*(char**)(a0 + 0x154))[i + 6] = a1[i];
    } while (++i < 8);

    unused = &D_00000000;

    if (D_A0000200 == 0xAC290000) {
        func_00000000(a0);
    }
}

void func_000128AC(char *a0, char *a1, char *a2) {
    if (a2 != 0) {
        *(int*)(a2 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a2,
            ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][2],
            ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][1]);
    }
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

void func_000129A0(char *a0, char *a1, char *a2) {
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
    if (a2 != 0) {
        if (*(int*)(a0 + 0x16C) == 0) {
            *(int*)(a0 + 0x16C) = func_00000000(*(int*)(a0 + 0x164) << 2);
        }
        *(int*)(a2 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a2, *(int*)(a0 + 0x16C), *(int*)(a0 + 0x164), a0 + 0x174);
        *(int*)(a0 + 0x184) = 0;
    }
}

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
