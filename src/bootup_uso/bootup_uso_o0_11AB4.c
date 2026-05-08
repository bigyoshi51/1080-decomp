#include "common.h"

extern int func_00000000();

/* Sibling in the 0x11A34 O0 cluster. Clears the small object lists/counts,
 * probes a0->0xC0 twice, and initializes each live child slot. */
void func_00011AB4(char *a0) {
    s32 i;

    *(s32*)(a0 + 0x120) = 0;
    *(s32*)(a0 + 0x124) = 0;
    *(s32*)(a0 + 0x128) = -1;
    i = 0;
    do {
        if (func_00000000(*(s32*)(a0 + 0xC0)) == 0) {
            *(s32*)(a0 + 0x18C) = 1;
        } else {
            func_00000000(a0, *(s32*)(a0 + 0xC0 + (i * 4)));
        }
    } while (++i < 2);
}
