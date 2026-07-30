/* IDO -O1 donor for gl_func_0006F3E4 = libultra osJamMesg
 * (references/libreultra/src/os/jammesg.c, verbatim: disable ints;
 * while (validCount >= msgCount) either set running thread
 * OS_STATE_WAITING(8) + __osEnqueueAndYield(&mq->fullqueue) when
 * flag==OS_MESG_BLOCK, or restoreInt + return -1; then
 * first = (first + msgCount - 1) % msgCount (the break7/break6
 * signed-div fingerprint), msg[first] = msg, validCount++, pop+start
 * a blocked receiver, restoreInt, return 0).
 * Sits in the post1b2c -O1 libultra island next to 6FB54 (osGetTime)
 * and 6FE5C (__osInsertTimer) — same references-first vein; the old
 * 38.75% m2c stub was an -O2 misread.
 * Blank externs: _disint = __osDisableInt, _enqyield =
 * __osEnqueueAndYield, _resint = __osRestoreInt, _popthr =
 * __osPopThread, _startthr = osStartThread; D_00000000_runthread =
 * __osRunningThread (OSThread*, lui/lw pair).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef int s32;
typedef void *OSMesg;

typedef struct OSThread_s {
    /* 0x00 */ struct OSThread_s *next;
    /* 0x04 */ s32 priority;
    /* 0x08 */ struct OSThread_s **queue;
    /* 0x0C */ struct OSThread_s *tlnext;
    /* 0x10 */ u16 state;
    /* 0x12 */ u16 flags;
} OSThread;

typedef struct {
    /* 0x00 */ OSThread *mtqueue;
    /* 0x04 */ OSThread *fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg *msg;
} OSMesgQueue;

extern u32 gl_func_00000000_disint(void);              /* __osDisableInt */
extern void gl_func_00000000_enqyield(OSThread **);    /* __osEnqueueAndYield */
extern void gl_func_00000000_resint(u32);              /* __osRestoreInt */
extern OSThread *gl_func_00000000_popthr(OSThread **); /* __osPopThread */
extern void gl_func_00000000_startthr(OSThread *);     /* osStartThread */
extern OSThread *D_00000000_runthread;                 /* __osRunningThread */

s32 gl_func_0006F3E4(OSMesgQueue *mq, OSMesg msg, s32 flag)
{
    register u32 saveMask = gl_func_00000000_disint();

    while (mq->validCount >= mq->msgCount) {
        if (flag == 1) {
            D_00000000_runthread->state = 8;
            gl_func_00000000_enqyield(&mq->fullqueue);
        } else {
            gl_func_00000000_resint(saveMask);
            return -1;
        }
    }

    mq->first = (mq->first + mq->msgCount - 1) % mq->msgCount;
    mq->msg[mq->first] = msg;
    mq->validCount++;
    if (mq->mtqueue->next != 0) {
        gl_func_00000000_startthr(gl_func_00000000_popthr(&mq->mtqueue));
    }
    gl_func_00000000_resint(saveMask);
    return 0;
}
