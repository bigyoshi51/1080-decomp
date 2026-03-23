/* func_80007DD0 — compiled at -O1, matching C source */
#include "common.h"

/* osStopThread */
void func_80007DD0(Thread* t) {
    register s32 saveMask = func_800066B0();
    register u16 state;
    if (t == 0) {
        state = 4;
    } else {
        state = t->state;
    }
    switch (state) {
    case 4:
        ((Thread*)D_8000A420)->state = 1;
        func_80003D0C(0);
        break;
    case 2:
    case 8:
        t->state = 1;
        func_80003FF0(t->queue, t);
        break;
    }
    func_800066D0(saveMask);
}
