#include "common.h"

/* byte memcpy variant: caller passes the count in BOTH a2 and a3
 * (a3 is the loop guard, a2 is the per-iteration counter that gets
 * pre-decremented). Logically equivalent to memcpy(dst, src, n). */
void func_800066F0(u8* dst, u8* src, s32 n, s32 ctr) {
    char pad[4];
    n--;
    if (ctr != 0) {
        do {
            *dst = *src;
            ctr = n;
            n--;
            dst++;
            src++;
        } while (ctr != 0);
    }
}
