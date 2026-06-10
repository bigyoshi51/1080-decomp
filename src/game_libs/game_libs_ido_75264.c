#include "common.h"

/* game_libs_func_00075264 = the TRUE function behind the 75260/7526C
 * "dual-entry" pair: an RSP kick -- read SP_STATUS (0xA4040010), and if
 * the halt bit (bit 0) is set, write the new RSP program counter to
 * SP_PC_REG (0xA4080000). The old gl_func_0007526C cap analysis
 * ("empty 8-byte frame, temps start at t7, v0 set directly") all fell
 * out of the REAL boundary: the fn starts at 0x75264 with the SP_STATUS
 * load (t6 consumed there; result OVERWRITES the dead arg `flag`, which
 * is why it lands in $a1), and the unused local allocates the empty
 * frame (IDO -O1 allocates unused-local slots; -O2 drops them).
 * 13/13 at IDO 7.1 -O1 (also exact at 5.3 -O1). The leading nop at
 * 0x75260 is 75254's trailing pad, kept in post2b_f as a pad word. */
int game_libs_func_00075264(unsigned int pc, unsigned int flag) {
    int unused;
    flag = *(volatile unsigned int *)0xA4040010;
    if (!(flag & 1)) {
        return -1;
    }
    *(volatile unsigned int *)0xA4080000 = pc;
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_libs/game_libs/game_libs_func_00075264_pad.s")
