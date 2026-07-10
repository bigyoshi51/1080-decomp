#include "common.h"

/* timproc_uso_b3_func_000000B0 — -O0 donor (REPLACE_FUNC_BODY into
 * timproc_uso_b3.c.o). 14-case state-machine dispatcher on arg1; loop
 * re-reads the next state from D_00000000.f40 until a case sets `done`.
 * -O0 keeps the switch jumptable in .rodata at offset 0, so the lui/lw
 * dispatch words carry in-place addend 0 — matching the target's raw
 * (pre-USO-reloc) words. All module-global accesses are extern-struct
 * member reads/writes on D_00000000 so the byte offsets bake into the
 * HI16/LO16 in-place addends. b1 twin: timproc_uso_b1_o0_B0.c — this b3
 * copy differs only in case 5 second-call a3 / case 7 first-call a3
 * (1 -> 2) and the case 12 mask/arg (0x2000 -> 0x4000). */

extern int gl_func_00000000();

typedef struct {
    /* 0x000 */ int f00;
    /* 0x004 */ int f04;
    /* 0x008 */ int pad08[14];
    /* 0x040 */ int f40;
    /* 0x044 */ int f44;
    /* 0x048 */ int f48;
    /* 0x04C */ int pad4C[6];
    /* 0x064 */ int f64;
    /* 0x068 */ int pad68[66];
    /* 0x170 */ int f170;
    /* 0x174 */ int pad174;
    /* 0x178 */ unsigned char f178;
} TimProcState;

extern TimProcState D_00000000;
/* Same module base, distinct symbol: case 5's second argument materializes
 * the base pointer into its own temp reg (lui/addiu addend 0) instead of
 * CSE-sharing the &D_00000000 already loaded into a0. */
extern char D_00000000_raw[];

void timproc_uso_b3_func_000000B0(int *arg0, int arg1) {
    int v;
    int done = 0;
    register int s0v;
    register char *base;
    register char *p2;
    register char *p3;

    do {
        switch (arg1) {
        case 0:
            gl_func_00000000(arg0, 1, 7, 1);
            D_00000000.f44 = 4;
            D_00000000.f48 = 13;
            done = 1;
            break;
        case 1:
            gl_func_00000000(arg0, 1, 7, 1);
            D_00000000.f44 = 4;
            D_00000000.f48 = 13;
            done = 1;
            break;
        case 2:
            gl_func_00000000(arg0, 1, 7, 2);
            D_00000000.f44 = 4;
            D_00000000.f48 = 13;
            done = 1;
            break;
        case 3:
            gl_func_00000000(arg0, 1, 7, 4);
            D_00000000.f44 = 4;
            D_00000000.f48 = 13;
            done = 1;
            break;
        case 4:
            gl_func_00000000(arg0, 1, D_00000000.f64);
            D_00000000.f40 = 5;
            break;
        case 5:
            gl_func_00000000(&D_00000000, *(int *)(D_00000000_raw + 4));
            gl_func_00000000(&D_00000000, 4, D_00000000.f64, 2);
            v = gl_func_00000000(arg0, *arg0, 1);
            s0v = gl_func_00000000(0, 0x410000, v, *arg0);
            gl_func_00000000(arg0, 0, s0v);
            done = 1;
            break;
        case 6:
            gl_func_00000000(arg0, 0, D_00000000.f178);
            D_00000000.f40 = 7;
            break;
        case 7:
            gl_func_00000000(&D_00000000, 10, D_00000000.f64, 2);
            v = gl_func_00000000(arg0, *arg0, 1);
            s0v = gl_func_00000000(0, D_00000000.f170 + 0x1A000F, v, *arg0);
            gl_func_00000000(arg0, 0, s0v);
            done = 1;
            break;
        case 8:
            gl_func_00000000(arg0);
            D_00000000.f40 = D_00000000.f44;
            break;
        case 9:
            gl_func_00000000(arg0);
            D_00000000.f40 = 10;
            break;
        case 10:
            gl_func_00000000(&D_00000000, 7, 0, 0);
            s0v = gl_func_00000000(0);
            gl_func_00000000(arg0, 1, s0v);
            done = 1;
            break;
        case 11:
            v = gl_func_00000000(arg0, *arg0, 4);
            s0v = gl_func_00000000(0, D_00000000.f170 + 0x20000, v, *arg0);
            base = (char *)&D_00000000;
            p2 = base + 0x10;
            gl_func_00000000(p2, s0v);
            if (*(int *)((char *)s0v + 0x14) != 0) {
                *(int *)((char *)s0v + 4) = 1;
            }
            p2 = base;
            *(int *)((char *)s0v + 0x14) = (int)p2;
            gl_func_00000000(arg0, *arg0);
            done = 1;
            break;
        case 12:
            s0v = gl_func_00000000(D_00000000.f64);
            gl_func_00000000(arg0, (D_00000000.f64 | 0x4000) | s0v, 0x4000, *arg0);
            done = 1;
            break;
        case 13:
            s0v = gl_func_00000000(0, 1, 0);
            base = (char *)&D_00000000;
            p2 = base + 0x10;
            gl_func_00000000(p2, s0v);
            if (*(int *)((char *)s0v + 0x14) != 0) {
                *(int *)((char *)s0v + 4) = 1;
            }
            p3 = base;
            *(int *)((char *)s0v + 0x14) = (int)p3;
            done = 1;
            break;
        }
        arg1 = D_00000000.f40;
    } while (done == 0);
}
