#include "common.h"

extern s32 func_800066F0(void*, s32, s32);

/* Receive 0x1B0 bytes into arg0 buffer via repeated func_800066F0 calls.
 * The unused float local (`dummy = 0.0f`) is preserved from the original
 * — IDO emits the mtc1+swc1 even though the value is never read. */
void func_800050C0(void* arg0) {
    f32 dummy;
    void* p;
    s32 totalRecv;
    dummy = 0.0f;
    p = arg0;
    totalRecv = 0;
    do {
        register s32 recv = func_800066F0((char*)p + totalRecv, 0x1B0 - totalRecv, 2);
        totalRecv += recv;
    } while ((u32)totalRecv < 0x1B0);
}
