#include "common.h"

/* gl_func_000732C4 = libultra scheduler yield/dispatch helper, statically linked
 * into the game_libs USO. Byte-exact masked-twin of matched kernel func_80009A50
 * (kernel_023): disable-int, set the running-thread state word to 2, dispatch
 * the run-queue head, restore-int. IDO 5.3 -O1, spliced into
 * game_libs_post2b_c.c.o via REPLACE_FUNC_BODY. Three OS-API callees collapse to
 * gl_func_00000000; the two distinct globals (running-thread ptr D_8000A420,
 * run-queue head D_8000A418) map to the two distinct zero-resolving placeholders
 * D_00000000 / gl_data_00000000 (kept separate so IDO does not CSE them). */
extern int gl_func_00000000();
extern void *D_00000000;       /* running thread ptr placeholder */
extern int gl_data_00000000;   /* run-queue head placeholder */

void gl_func_000732C4(void) {
    register int sr = gl_func_00000000();
    *(short *)((char *)D_00000000 + 0x10) = 2;
    gl_func_00000000(&gl_data_00000000);
    gl_func_00000000(sr);
}
