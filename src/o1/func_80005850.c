/* func_80005850 — compiled at -O1, matching C source */
#include "common.h"

/* __osSiCreateAccessQueue */


/* __osPiGetAccess */

void func_80005850(void) {
    s32 msg;
    if (D_8000A480 == 0) {
        func_80005C00();
    }
    func_80004FE0(&__osPiAccessQueue, &msg, 1);
}
