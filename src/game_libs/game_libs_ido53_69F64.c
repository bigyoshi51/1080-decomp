#include "common.h"

/* gl_func_00069F64 = libultra osRecvMesg (os/recvmesg.c verbatim), statically
 * linked into the game_libs USO right after osSendMesg (gl_func_00069E04) and
 * osViGetCurrentLine (game_libs_func_00069F54). IDO 5.3 -O1 (the 69E04 recipe),
 * spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY. Block while the
 * queue is empty (or fail if non-blocking), pop msg[first], advance first
 * modulo msgCount, and if a thread waits on fullqueue, wake it. All OS-API
 * callees (__osDisableInt / __osRestoreInt / __osEnqueueAndYield /
 * __osPopThread / osStartThread) collapse to the address-0 placeholder
 * gl_func_00000000; __osRunningThread maps to D_00000000. */
typedef struct {
    void *mtqueue;
    void *fullqueue;
    int validCount;
    int first;
    int msgCount;
    int **msg;
} OSMesgQueue_69F64;
typedef struct { int field0; int pri; int queue; int pad0C; unsigned short state; } Thread_69F64;

extern int gl_func_00000000();
extern int D_00000000;

int gl_func_00069F64(OSMesgQueue_69F64 *mq, int **msg, int flags) {
    register int saveMask = gl_func_00000000();

    while (mq->validCount == 0) {
        if (flags == 0) {
            gl_func_00000000(saveMask);
            return -1;
        }
        ((Thread_69F64 *)D_00000000)->state = 8;
        gl_func_00000000((int *)&mq->mtqueue);
    }
    if (msg != 0) {
        *msg = mq->msg[mq->first];
    }
    mq->first = (mq->first + 1) % mq->msgCount;
    mq->validCount--;
    if (*(void **)mq->fullqueue != 0) {
        gl_func_00000000(gl_func_00000000((int *)&mq->fullqueue));
    }
    gl_func_00000000(saveMask);
    return 0;
}
