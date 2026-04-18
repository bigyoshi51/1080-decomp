#include "common.h"

extern s32 func_800066F0(void*, s32, s32);

/* Polls func_800066F0 until it returns a positive value. Used to wait
 * for a single byte of host I/O. */
void func_80005134(void) {
    s32 totalRecv;
    s32 buf;
    totalRecv = 0;
    do {
        register s32 recv = func_800066F0(&buf, 1, 10);
        totalRecv += recv;
    } while (totalRecv <= 0);
}
