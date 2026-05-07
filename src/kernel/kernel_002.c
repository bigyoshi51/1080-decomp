#include "common.h"


#ifdef NON_MATCHING
/* func_80004B10: 52-insn (0xD0) RDB read-loop with lazy init.
 * Likely __osRdbRead-style host-read function.
 *
 * Lazy-inits a message queue (D_8000A440 flag-guarded) on first call:
 *   osCreateMesgQueue(&readhost_bss_0000, &readhost_bss_0018, 1)
 *   osSetEventMesg(0xF, &readhost_bss_0000, 0)
 *
 * Then publishes (buf, ct) to global slots __osRdb_Read_Data_Buf/Ct,
 * and if ct != 0, loops osRecvMesg until accumulated recv > 0.
 * Final osSendMesg releases the queue.
 *
 * Initial structural decode - no register tuning yet. */
extern int func_800053D0(void*, void*, int);
extern int func_800051E0(int, void*, int);
extern int func_800066F0(void*, int, int);
extern int func_80004FE0(void*, int, int);
extern int D_8000A440;
extern int readhost_bss_0000;
extern int readhost_bss_0018;
extern int __osRdb_Read_Data_Buf;
extern int __osRdb_Read_Data_Ct;

void func_80004B10(void* buf, int ct) {
    int msg;
    int count = 0;
    if (D_8000A440 == 0) {
        func_800053D0(&readhost_bss_0000, &readhost_bss_0018, 1);
        func_800051E0(0xF, &readhost_bss_0000, 0);
        D_8000A440 = 1;
    }
    __osRdb_Read_Data_Buf = (int)buf;
    __osRdb_Read_Data_Ct = ct;
    if (ct != 0) {
        do {
            count += func_800066F0(&msg, 1, 5);
        } while (count == 0);
    }
    func_80004FE0(&readhost_bss_0000, 0, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004B10);
#endif


INCLUDE_ASM("asm/nonmatchings/kernel", func_80004BE0);




INCLUDE_ASM("asm/nonmatchings/kernel", func_80004D20);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004DB8);
