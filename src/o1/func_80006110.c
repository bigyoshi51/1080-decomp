/* func_80006110 — compiled at -O1, matching C source */
#include "common.h"

/* osSetThreadPri */


void func_80006110(Thread* thread, s32 pri) {
    register s32 sr = func_800066B0();
    if (thread == 0) {
        thread = (Thread*)D_8000A420;
    }
    if (thread->pri != pri) {
        thread->pri = pri;
        if (thread != (Thread*)D_8000A420 && thread->state != 1) {
            func_80003FF0(thread->queue, thread);
            func_80003E0C(thread->queue, thread);
        }
        if (((Thread*)D_8000A420)->pri < ((Thread*)D_8000A418)->pri) {
            ((Thread*)D_8000A420)->state = 2;
            func_80003D0C(&D_8000A418);
        }
    }
    func_800066D0(sr);
}
