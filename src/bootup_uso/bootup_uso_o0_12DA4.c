#include "common.h"

extern void func_0000F1F0(int *dst);
extern void func_0000F23C(int *dst);
extern void func_0000F2EC(int *dst);

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
