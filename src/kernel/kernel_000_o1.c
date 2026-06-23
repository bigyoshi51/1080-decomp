#include "common.h"

/* kernel_000_o1: -O1 file-split holding the two tail functions of kernel_000
 * (func_800048E8, func_800049B8) that are genuinely -O1 (verified 2026-06-04:
 * each spills every local to the stack and reloads per use; an -O2 build keeps
 * them in $s/$a regs and scores ~34-39%, an -O1 build scores 72-78%). Their
 * kernel_000 siblings func_80004808 / func_8000487C stay -O2 (they score HIGHER
 * at -O2), so only these two are carved out. objdiff compares per-function so the
 * .ld placement (right after kernel_000.c.o) is purely cosmetic. */

extern void* D_8000A420;

/* func_800048E8: chunked-write driver. Borrows hardware (init via
 * func_80004C7C if D_8000A490 was clear), processes arg1 bytes from arg0
 * in chunks of <=3 via func_80004C08, re-arming the hardware between chunks,
 * then conditionally re-invokes func_80004C7C if D_8000A490 was already set
 * on entry. -O1 file-split (matched 2026-06-23). */
extern s32 D_8000A490;
extern void func_80004C7C(void);
extern void func_80004C08(char *p, s32 n);
void func_800048E8(char *arg0, s32 arg1) {
    s32 chunkSize;
    s32 offset;
    s32 wasInit;

    offset = 0;
    if (D_8000A490 == 0) {
        func_80004C7C();
        wasInit = 0;
    } else {
        wasInit = 1;
    }

    while (arg1 != 0) {
        chunkSize = ((u32)arg1 < 3) ? arg1 : 3;
        func_80004C08(arg0 + offset, chunkSize);
        arg1 -= chunkSize;
        offset += chunkSize;
        if (arg1 != 0) {
            func_80004C7C();
        }
    }

    if (wasInit != 0) {
        func_80004C7C();
    }
}

/* func_800049B8: 64-insn rmon/kdebugserver packet parser. Receives 24
 * bits per call (high 3 bytes of arg0); appends them to packet buffer
 * kdebugserver_bss_01B0[] at write-position D_8000A430. After append:
 *   - if buf[0] == 2: send a fixed-size packet (0x190 bytes from
 *     D_8000A420+0x20 via func_80004CE8); reset position
 *   - else if pos < 9: return (need more data)
 *   - else if buf[0] == 1: parse two u32s (BE) at buf[1] and buf[5]
 *     via func_80004BB0; pass to func_80004CE8; reset position
 *   - else: return (other tag — discard)
 * -O1 split: byte-exact match (loop reads D_8000A430 + i directly, no
 * cached pos; ++i pre-incr in the while test; Y,X decl order = reverse
 * stack-slot numbering at -O1). */
extern u32 D_8000A430;
extern u8 kdebugserver_bss_01B0[];
extern void func_80004CE8(u32 a, u32 b);
extern u32 func_80004BB0(u8 *p);
void func_800049B8(u32 arg0) {
    s32 i;
    u32 Y, X;

    i = 0;
    do {
        kdebugserver_bss_01B0[D_8000A430] = ((u8*)&arg0)[1 + i];
        D_8000A430 = D_8000A430 + 1;
    } while ((u32)++i < 3);

    if (kdebugserver_bss_01B0[0] == 2) {
        func_80004CE8((u32)((u8*)D_8000A420 + 0x20), 0x190);
        D_8000A430 = 0;
    } else if (D_8000A430 >= 9) {
        if (kdebugserver_bss_01B0[0] == 1) {
            X = func_80004BB0(&kdebugserver_bss_01B0[1]);
            Y = func_80004BB0(&kdebugserver_bss_01B0[5]);
            func_80004CE8(X, Y);
            D_8000A430 = 0;
        }
    }
}
