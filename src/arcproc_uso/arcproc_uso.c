#include "common.h"

extern int gl_func_00000000();
extern char D_00000000;

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by the standard int-reader template body at -O0.
 * The 4-byte trampoline is injected post-cc by scripts/inject-prefix-bytes.py
 * (per PREFIX_BYTES Makefile var); the body is compiled at -O0 via the
 * arcproc_uso.c.o OPT_FLAGS override. The script inserts the bytes at the
 * function's start, shifts subsequent symbols, and grows the function symbol
 * to cover the full 0x50-byte target extent. */
void arcproc_uso_func_00000000(int *dst) {
    int buf[2];
    gl_func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}
