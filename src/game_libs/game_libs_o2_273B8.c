/* game_libs_func_000273B8 -- 14-case jumptable message handler (switch on
 * msg[0]): float/s8/short setters on the object with change-flag bits in
 * byte 1, a bit-4 insert into byte 0, and one indexed byte store.
 *
 * IDO 7.1 -O2 REPLACE_FUNC_BODY donor for game_libs_post.c.o (99/99 words;
 * the only word the build cannot bake is the `lw t7,%lo(jtbl)(at)` load).
 * A C `switch` puts its jumptable in this unit's local .rodata; the splice
 * renames that reloc to game_libs_func_000273B8_rodata, pinned in
 * undefined_syms_auto.txt to the table the USO ships in its data at +0xF88
 * (14 entries; entry 7 = default). Same recipe as game_libs_o2_29CCC.c.
 *
 * Load-bearing: the change flags (byte 1 bits 0x80/0x40/0x20) and the
 * byte-0 bit 0x10 are 1-bit unsigned BITFIELDS, not `a0[1] |= K` /
 * `(a0[0] & ~0x10) | ((v << 4) & 0x10)`. Each bitfield insert lowers through
 * one extra eliminated temp, which burns the ugen ring slot the old byte
 * spelling was missing (the documented "+5 temp-ring rotation" = cases
 * 1, 2, 3, 4 and 8, one slot each). See docs/IDO_CODEGEN.md
 * #single-bit-bitfield-set-extra-ring-temp-29000. */
#include "common.h"

typedef struct { unsigned int b0hi:3, bit4:1, b0lo:4, f80:1, f40:1, f20:1, b1lo:5, rest:16; } BF_273B8;
void game_libs_func_000273B8(unsigned char *a0, unsigned char *a1) {
    switch (a1[0]) {
    case 1:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 40)) {
            *(float *)(a0 + 40) = *(float *)(a1 + 4);
            ((BF_273B8 *)a0)->f40 = 1;
        }
        return;
    case 2:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 44)) {
            *(float *)(a0 + 44) = *(float *)(a1 + 4);
            ((BF_273B8 *)a0)->f40 = 1;
        }
        return;
    case 3:
        if (*(signed char *)(a1 + 4) != a0[10]) {
            a0[10] = *(signed char *)(a1 + 4);
            ((BF_273B8 *)a0)->f20 = 1;
        }
        return;
    case 4:
        if (*(float *)(a1 + 4) != *(float *)(a0 + 56)) {
            *(float *)(a0 + 56) = *(float *)(a1 + 4);
            ((BF_273B8 *)a0)->f80 = 1;
        }
        return;
    case 5:
        if (*(signed char *)(a1 + 4) != a0[4]) {
            a0[4] = *(signed char *)(a1 + 4);
        }
        return;
    case 6: {
        int idx = a1[3];
        if (idx < 8) {
            a0[idx + 212] = *(signed char *)(a1 + 4);
        }
        return;
    }
    case 8:
        ((BF_273B8 *)a0)->bit4 = *(signed char *)(a1 + 4);
        return;
    case 9:
        a0[3] = *(signed char *)(a1 + 4);
        return;
    case 10:
        *(short *)(a0 + 22) = a1[4] << 3;
        *(short *)(a0 + 26) = 1;
        return;
    case 11:
        *(short *)(a0 + 20) = a1[4] << 5;
        *(short *)(a0 + 24) = 1;
        return;
    case 12:
        a0[15] = a1[4];
        return;
    case 13:
        *(short *)(a0 + 32) = *(unsigned short *)(a1 + 4);
        return;
    case 14:
        a0[224] = a1[4];
        return;
    }
}
