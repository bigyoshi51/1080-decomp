/* func_800059C0 — compiled at -O1, matching C source */
#include "common.h"

/* osSendMesg */
s32 func_800059C0(OSMesgQueue* mq, s32 msg, s32 flags) {
    register s32 saveMask = func_800066B0();
    register s32 last;
    while (mq->validCount >= mq->msgCount) {
        if (flags == 1) {
            ((Thread*)D_8000A420)->state = 8;
            func_80003D0C((s32*)&mq->fullqueue);
        } else {
            func_800066D0(saveMask);
            return -1;
        }
    }
    last = (mq->first + mq->validCount) % mq->msgCount;
    mq->msg[last] = (s32*)msg;
    mq->validCount++;
    if (*(void**)mq->mtqueue != 0) {
        register void* t = (void*)func_80003E54(mq);
        func_8000A110(t);
    }
    func_800066D0(saveMask);
    return 0;
}
