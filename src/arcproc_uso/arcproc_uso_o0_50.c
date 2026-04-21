#include "common.h"

/* -O0 run at 0x50: Quad4 reader accessor template. See
 * feedback_uso_accessor_o0_variant.md. */

extern int gl_func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void arcproc_uso_func_00000050(Quad4 *dst) {
    Quad4 buf;
    gl_func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}
