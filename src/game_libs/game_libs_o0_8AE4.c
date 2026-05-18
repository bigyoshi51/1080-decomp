#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;
extern int D_00000000_a;
extern int D_8AE4_mode;

void gl_func_00008AE4(int a0, int a1, int a2, int a3) {
    register int rv;

    gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x0));
    gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0xC));

    if (D_8AE4_mode == 3) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x10));
    }

    if (D_8AE4_mode != 2) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x14));
    }

    if ((D_8AE4_mode != 3) && (D_8AE4_mode != 5)) {
        gl_func_00000000(&D_00000000, *(int*)((char*)&D_00000000_a + 0x18));
    }

    gl_func_00000000(&D_00000000, 3, 0, 0);
    rv = gl_func_00000000(0, a1, a2, a3);
    gl_func_00000000(a0, 0, rv);
}
