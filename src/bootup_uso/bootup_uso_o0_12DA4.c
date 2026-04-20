#include "common.h"

extern int func_00000000();
extern void func_0000F1F0(int *dst);
extern void func_0000F23C(int *dst);
extern void func_0000F2EC(int *dst);

void func_00012C10(char *a0) {
    *(int*)(a0 + 0x168) = 0;
    if (*(int*)(a0 + 0x16C) != 0) {
        func_00000000(*(int*)(a0 + 0x16C));
    }
    *(int*)(a0 + 0x16C) = 0;
}

void func_00012C64(char *arg0, int arg1) {
    int v0;
    *(int*)(arg0 + 0x14C) = func_00000000(0, *(int*)(arg0 + 0x148), 3, -1);
    v0 = func_00000000(*(int*)(arg0 + 0x170) << 2);
    func_00000000(v0, *(int*)(arg0 + 0x168), *(int*)(arg0 + 0x170) << 2);
    func_00000000(
        *(int*)(*(int*)(arg0 + 0x14C) + 0x8),
        arg1,
        *(unsigned char*)(arg0 + 0x178),
        *(unsigned char*)(arg0 + 0x179),
        *(unsigned char*)(arg0 + 0x17A),
        *(unsigned char*)(arg0 + 0x17B),
        v0,
        *(int*)(arg0 + 0x170)
    );
    func_00000000(*(int*)(arg0 + 0x148), *(int*)(*(int*)(arg0 + 0x14C) + 0x8));
    func_00000000(*(int*)(arg0 + 0x14C), 3);
    *(int*)(arg0 + 0x184) = 0;
    *(int*)(arg0 + 0x6C) = -1;
}

void func_00012D64(char *dst) {
    int tmp;
    func_0000F1F0(&tmp);
    func_0000F23C((int*)(dst + 0x10));
}

void func_00012DA4(int a0) {}

void func_00012DB8(char *dst) {
    int tmp;
    func_0000F1F0(&tmp);
    func_0000F2EC((int*)(dst + 0x10));
}
