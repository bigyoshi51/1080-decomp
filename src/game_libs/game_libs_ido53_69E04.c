#include "common.h"

/* gl_func_00069E04 = libultra osSendMesg (sched/sendmesg.c), statically linked
 * into the game_libs USO. Byte-exact masked-twin of matched kernel func_800059C0
 * (kernel_009): block while the queue is full (or fail if non-blocking), append
 * msg to the ring buffer, then if a thread is waiting on mtqueue wake it. IDO
 * 5.3 -O1, spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY. All OS-API
 * callees collapse to the address-0 placeholder gl_func_00000000; the single
 * global (running-thread ptr, kernel D_8000A420) maps to D_00000000. */
typedef struct {
    void *mtqueue;
    void *fullqueue;
    int validCount;
    int first;
    int msgCount;
    int **msg;
} OSMesgQueue_69E04;
typedef struct { int field0; int pri; int queue; int pad0C; unsigned short state; } Thread_69E04;

extern int gl_func_00000000();
extern int D_00000000;

int gl_func_00069E04(OSMesgQueue_69E04 *mq, int msg, int flags) {
    register int saveMask = gl_func_00000000();
    register int last;
    while (mq->validCount >= mq->msgCount) {
        if (flags == 1) {
            ((Thread_69E04 *)D_00000000)->state = 8;
            gl_func_00000000((int *)&mq->fullqueue);
        } else {
            gl_func_00000000(saveMask);
            return -1;
        }
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = (int *)msg;
    mq->validCount++;
    if (*(void **)mq->mtqueue != 0) {
        register void *t = (void *)gl_func_00000000(mq);
        gl_func_00000000(t);
    }
    gl_func_00000000(saveMask);
    return 0;
}
