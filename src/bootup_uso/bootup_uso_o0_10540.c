#include "common.h"

extern int func_00000000();

/* func_00010540: -O0 island carved out of bootup_uso_tail3a_10540.c on
 * 2026-09-04 and MATCHED at -O0 (343/343 target words; the 1 trailing pad
 * word is clipped by TRUNCATE_TEXT 0x55C). Same carve recipe as o0_1034C /
 * o0_10AB0.
 *
 * Element/sprite render loop: for each of a0->n78 ring records (skipping
 * the cursor a0->cur7C) compute an x-position from (int)f70 + i*f74, copy
 * the 16-byte int quad q5C -> q3C, halve the first three (float RGB) when
 * the record's f88 flag is 0, then draw via the placeholder callee (path A
 * through a0->n30 when the record has a p84 payload, else path B on the
 * record's own sub94 object). After the loop the cursor record is drawn
 * once the same way from q4C, gated by a0->flags38 & 8, with flags38
 * passed as the 4th arg of the 2nd call.
 *
 * -O0 levers that produced the exact bytes (all prior "deferred / typed-
 * struct refactor + regalloc grind" notes on this fn were wrong):
 *  - TYPED container struct with a member array `el[]` at +0x84 (stride
 *    0x28): gives base-first `addu tN, <a0>, <idx*0x28>` + folded 0x88 /
 *    0x84 / 0x94 displacements (the FI/EL char-arith macros of the old NM
 *    body emit offset-first addu and a 250-line temp cascade).
 *  - the 4-int copies are single STRUCT assignments (one base reload).
 *  - one `register char *s` colors s0 for BOTH the three RMW `/= 2.0f`
 *    sites (s = &field; *(float*)s /= 2.0f -> addiu s0 + 0(s0) lwc1/swc1)
 *    and the cross-call callee-return home (`or s0,v0` -> `or a1,s0`).
 *  - ONLY remaining diff was the loop-head compare `i != a0->cur7C`: cfe
 *    ranks the 2-load struct member above the 1-load local and emits it
 *    first regardless of operand order (`cur7C != i` identical). Casting
 *    the LOCAL to unsigned (`(unsigned)i != a0->cur7C`) raises its rank so
 *    i loads first -> beq i,cur7C. (The equivalent `i != (unsigned)cur7C`
 *    also works; `i - cur7C`, `!(i == cur)`, `(i != cur) != 0` do not.)
 *  - f6C is a FLOAT truncated per call ((int)a0->f6C), not an int field.
 *  - `pos - a0->n30->w / 2` shares the a0->n30 reload with the call's
 *    first arg within the one call expression (-O0 cfe DAG share). */
typedef struct { int a, b, c, d; } Quad540;
typedef struct { char pad[0x10]; int w; } Node540;
typedef struct { void *p84; int f88; char pad[8]; char sub94[0x18]; } Elem540;
typedef struct {
    char pad0[0x30];
    Node540 *n30;
    void *p34;
    int flags38;
    Quad540 q3C;
    Quad540 q4C;
    Quad540 q5C;
    float f6C;
    float f70;
    float f74;
    int n78;
    int cur7C;
    int pad80;
    Elem540 el[1];
} Obj540;

void func_00010540(Obj540 *arg0) {
    int i;
    int pos;
    register char *s;

    if (arg0->p34 != NULL) {
        for (i = 0; i < arg0->n78; i++) {
            if ((unsigned)i != arg0->cur7C) {
                pos = (float)(int)arg0->f70 + (float)i * arg0->f74;
                arg0->q3C = arg0->q5C;
                if (arg0->el[i].f88 == 0) {
                    s = (char *)&arg0->q3C.a; *(float *)s /= 2.0f;
                    s = (char *)&arg0->q3C.b; *(float *)s /= 2.0f;
                    s = (char *)&arg0->q3C.c; *(float *)s /= 2.0f;
                }
                if (arg0->el[i].p84 != NULL) {
                    func_00000000(arg0->n30);
                    func_00000000(arg0->n30, arg0->p34, &arg0->q3C, 0);
                    s = (char *)func_00000000(arg0->n30, (int)arg0->f6C, arg0->el[i].p84);
                    func_00000000(arg0->n30, s, pos - arg0->n30->w / 2, arg0->el[i].p84);
                } else {
                    func_00000000(arg0->el[i].sub94);
                    func_00000000(arg0->el[i].sub94, arg0->p34, &arg0->q3C, 0);
                    func_00000000(arg0->el[i].sub94, (int)arg0->f6C, pos, 3);
                }
            }
        }
        pos = (float)(int)arg0->f70 + (float)arg0->cur7C * arg0->f74;
        arg0->q3C = arg0->q4C;
        if (arg0->el[i].f88 == 0) {
            s = (char *)&arg0->q3C.a; *(float *)s /= 2.0f;
            s = (char *)&arg0->q3C.b; *(float *)s /= 2.0f;
            s = (char *)&arg0->q3C.c; *(float *)s /= 2.0f;
        }
        if (arg0->flags38 & 8) {
            if (arg0->el[arg0->cur7C].p84 != NULL) {
                func_00000000(arg0->n30);
                func_00000000(arg0->n30, arg0->p34, &arg0->q3C, arg0->flags38);
                s = (char *)func_00000000(arg0->n30, (int)arg0->f6C, arg0->el[arg0->cur7C].p84);
                func_00000000(arg0->n30, s, pos - arg0->n30->w / 2, arg0->el[arg0->cur7C].p84);
            } else {
                i = arg0->cur7C;
                func_00000000(arg0->el[i].sub94);
                func_00000000(arg0->el[i].sub94, arg0->p34, &arg0->q3C, arg0->flags38);
                func_00000000(arg0->el[i].sub94, (int)arg0->f6C, pos, 3);
            }
        }
    }
}
