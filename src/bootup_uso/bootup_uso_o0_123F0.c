#include "common.h"

/* Run 9 subset: byte increment/decrement helpers at 0x123F0..0x1266C.
 * 3 decrementers (if byte > 0) and 3 incrementers (if byte < 10), at offsets
 * 0x12, 0x13, 0x14 within a pointer loaded from a0->0x154. At -O0 so IDO
 * emits stack-reload-per-use + `register char *p` for the $s0 pointer. */

extern int func_00000000();

void func_000123F0(char *a0) {
    register char *p;
    if (*(unsigned char*)(*(char**)(a0 + 0x154) + 0x12) != 0) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x12) -= 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x12));
}

void func_00012458(char *a0) {
    register char *p;
    if ((int)*(unsigned char*)(*(char**)(a0 + 0x154) + 0x12) < 10) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x12) += 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x12));
}

void func_000124C4(char *a0) {
    register char *p;
    if (*(unsigned char*)(*(char**)(a0 + 0x154) + 0x13) != 0) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x13) -= 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x13));
}

void func_0001252C(char *a0) {
    register char *p;
    if ((int)*(unsigned char*)(*(char**)(a0 + 0x154) + 0x13) < 10) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x13) += 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x13));
}

void func_00012598(char *a0) {
    register char *p;
    if (*(unsigned char*)(*(char**)(a0 + 0x154) + 0x14) != 0) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x14) -= 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x14));
}

void func_00012600(char *a0) {
    register char *p;
    if ((int)*(unsigned char*)(*(char**)(a0 + 0x154) + 0x14) < 10) {
        p = *(char**)(a0 + 0x154);
        *(p + 0x14) += 1;
    }
    func_00000000(*(unsigned char*)(*(char**)(a0 + 0x154) + 0x14));
}
