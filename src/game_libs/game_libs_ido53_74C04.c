#include "common.h"

/* gl_func_00074C04 = libultra osStartThread (sched/startthread.c), statically
 * linked into the game_libs USO. Byte-exact masked-twin of matched kernel
 * func_80009D10 (kernel_037): move the thread to RUNNABLE and (re)enqueue it on
 * the run queue per its current state, then if it now outranks the running
 * thread, preempt. IDO 5.3 -O1, spliced into game_libs_post2b_e.c.o via
 * REPLACE_FUNC_BODY. All OS-API callees collapse to the address-0 placeholder
 * gl_func_00000000; the two distinct globals (run queue, kernel D_8000A418, and
 * running-thread ptr, kernel D_8000A420) map to the two distinct zero-resolving
 * placeholders D_00000000 / gl_data_00000000 (kept separate so IDO does not CSE
 * them and renumber the register pair). */
typedef struct { int field0; int pri; int queue; int pad0C; unsigned short state; } Thread_74C04;

extern int gl_func_00000000();
extern int D_00000000;        /* run queue   (kernel D_8000A418) */
extern int gl_data_00000000;  /* running ptr  (kernel D_8000A420) */

void gl_func_00074C04(Thread_74C04 *t) {
    register int saveMask = gl_func_00000000();
    switch (t->state) {
    case 8:
        t->state = 2;
        gl_func_00000000(&D_00000000, t);
        break;
    case 1:
        if (t->queue == 0 || t->queue == (int)&D_00000000) {
            t->state = 2;
            gl_func_00000000(&D_00000000, t);
        } else {
            t->state = 8;
            gl_func_00000000((void *)t->queue, t);
            gl_func_00000000(&D_00000000, gl_func_00000000((void *)t->queue));
        }
        break;
    }
    if ((int)gl_data_00000000 == 0) {
        gl_func_00000000();
    } else {
        if (((Thread_74C04 *)gl_data_00000000)->pri < ((Thread_74C04 *)D_00000000)->pri) {
            ((Thread_74C04 *)gl_data_00000000)->state = 2;
            gl_func_00000000(&D_00000000);
        }
    }
    gl_func_00000000(saveMask);
}
