#include "common.h"
extern int D_00000000;
typedef struct { int a, b, c, d; } Quad4;
typedef struct { float x, y, z; } Vec3;


#ifdef NON_MATCHING
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
extern int D_00000000;   // D_a: fixed data arg threaded to the cb (lui+addiu)
extern int D_74C_b;      // D_b: address compared against arg0->0x8
extern int *D_74C_c;     // *&D_c: gate pointer + record (->4)
extern int *D_74C_d;     // *&D_d: peer record stored into (->0x10)
// State-machine step keyed on the u16 arg0->0x10. st==1: if the handle
// arg0->0x8 is null or the sentinel &D_b, demote to 2 and notify(&D_a,arg0);
// else promote to 8, notify(handle,arg0) and notify(&D_a, notify(handle)).
// st==8: demote to 2 + notify(&D_a,arg0). Then a global-record pass: if *&D_c
// is null, notify(); else if (*&D_d)->4 < (*&D_c)->4 demote (*&D_d)->0x10 to 2
// + notify(&D_a). Finally notify(s0) with the saved first-call result. The cb
// (game_libs_func_00070FCC) and &D globals are reloc-blind (field-0 matchable).
// 2026-06-10 SUPERSEDED CAP ANALYSIS: at IDO 5.3 -O1 (the ido53-carve
// compiler) with `register char *s0; register int x;` (x holds st AND the
// later call result -- one variable, the s1 reuse), the build reproduces
// the s0/s1 saves, the v0->s0 capture, and 84/84 instruction count with
// correct branch polarity when the st arms are written as
// `if (x != 1) { if (x == 8) {...} } else {...}`. Residual (~5 real
// shapes cascading into ~73 word diffs via offset/regnum shift): (a) the
// target reloads p from its stack home INSIDE the st==8 arm while 5.3
// CSEs the earlier load (basic-block-boundary reload not yet forced --
// typed struct members did NOT change this, unlike the -O0 case); (b)
// frame 0x28 vs 0x30 (+8, likely the h temp slot). Next pass: shapes
// that force a fresh p reload in the st==8 arm (volatile-pointer-fetch
// lever from docs/IDO_CODEGEN?), then carve at 5.3 -O1.
void gl_func_00074C04(char *arg0) {
    char *s0;
    unsigned short st;
    int r;

    s0 = (char *)game_libs_func_00070FCC();
    st = *(unsigned short *)(arg0 + 0x10);
    if (st == 1) {
        char *h = *(char **)(arg0 + 0x8);
        if ((h == 0) || (h == (char *)&D_74C_b)) {
            *(unsigned short *)(arg0 + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000, arg0);
        } else {
            *(unsigned short *)(arg0 + 0x10) = 8;
            game_libs_func_00070FCC(*(char **)(arg0 + 0x8), arg0);
            r = game_libs_func_00070FCC(*(char **)(arg0 + 0x8));
            game_libs_func_00070FCC((char *)&D_00000000, r);
        }
    } else if (st == 8) {
        *(unsigned short *)(arg0 + 0x10) = 2;
        game_libs_func_00070FCC((char *)&D_00000000, arg0);
    }
    if (D_74C_c == 0) {
        game_libs_func_00070FCC();
    } else {
        if (D_74C_d[1] < D_74C_c[1]) {
            *(unsigned short *)((char *)D_74C_d + 0x10) = 2;
            game_libs_func_00070FCC((char *)&D_00000000);
        }
    }
    game_libs_func_00070FCC(s0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074C04);
#endif
