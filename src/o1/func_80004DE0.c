/* func_80004DE0 — compiled at -O1, matching C source */
#include "common.h"

/* osSetEventMesg */
typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];

void func_80004DE0(s32 event, void* queue, s32 msg) {
    register s32 sr = func_800066B0();
    OSEventState* es = &__osEventStateTab[event];
    es->queue = (s32)queue;
    es->msg = msg;
    func_800066D0(sr);
}
