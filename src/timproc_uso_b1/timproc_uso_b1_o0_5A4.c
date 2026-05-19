#include "common.h"

extern int gl_func_00000000();
extern int D_00000148;
extern int D_0000014C;
extern int D_00000068;

void timproc_uso_b1_func_000005A4(int **arg0, int arg1, int arg2) {
    int handle = gl_func_00000000(2);
    register int new_obj = gl_func_00000000(0, D_00000148, 1, arg2);
    *arg0 = (int*)new_obj;
    D_0000014C = new_obj;
    gl_func_00000000(handle);
    if (arg1 != 0) {
        *(int*)((char*)*arg0 + 0x14) = 1;
    } else {
        *(int*)((char*)*arg0 + 0x14) = 0;
    }
    D_00000068 = 0;
}
