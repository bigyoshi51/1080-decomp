#include "common.h"

/* -O0 Vec3 reader at 0x8A40. Mirrors bootup_uso func_0000F2EC:
 * same logical body, same s-reg/stack-offset encoding patch class. */

extern int gl_func_00000000();
extern char D_00000000;

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;

void gl_func_00008A40(Vec3 *dst) {
    register Vec3 *p1;
    register Vec3 *p2;
    register Vec3 *q;
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    register float *src;
    gl_func_00000000(&D_00000000, &raw, 12);
    p1 = dst;
    tmp = raw;
    p2 = p1;
    src = (float*)&tmp;
    p2->x = src[0];
    p2->y = src[1];
    p2->z = src[2];
    q = p1;
    (void)q;
}
