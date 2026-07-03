#include "common.h"

extern int func_00000000();
typedef struct { int a, b, c, d; } Quad4;
extern Quad4 D_00000000;

void func_0001266C(char *a0, int a1) {
    register u16 *p;

    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p & ~3;
    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p | a1;
    func_00000000((*(u16 *)(*(char **)(a0 + 0x154) + 4)) & 3);
}

/* func_000126EC — 56/56 EXACT (2026-07-03, agent-e). Previous "capped 84.95%"
 * comment was WRONG on the logic: the tail is NOT FW(r,0x30) — it is
 * lh (SIGNED short) at 0x30(s2) PLUS the materialized &D_00000000 base, with
 * s2 = *(char**)(&D+0x28) and an `or s0,s1` q-copy passed as a1 via reusing p.
 * Levers: (1) decl order p,q,sp34,r,pad -> -O0 top-down slot map puts sp34 at
 * 0x34 with frame 0x40 (pad = 5th 4-byte slot, frame 0x3C rounds to 0x40);
 * (2) store must be a DIRECT struct-typed global field ref (extern Quad4
 * D_00000000; D_00000000.a = arg1) to fold to lui at; sw %lo — both
 * *(int*)&D and ((Quad4*)&D)->a keep the 3-insn lui/addiu/sw scalar form;
 * (3) direct K&R call (not fn-ptr cast) -> jal; (4) single-statement embed of
 * the r= assignment inside the call arg so &D stays cached in t5 (base reused
 * in addu), with the lh chain as the RIGHT operand of the add (IDO -O0
 * evaluates right operand first -> rs of addu); (5) p reused for the q copy
 * (or s0,s1) — first-declared register var = s0.
 * Requires TU-level: typedef Quad4 BEFORE `extern Quad4 D_00000000;`. */
#ifndef FW
#define FW(p, o) (*(int *)((char *)(p) + (o)))
#endif
typedef char *(*GP_000126EC)();
void func_000126EC(char *arg0, s32 arg1) {
    register u16 *p;
    register s32 *q;
    s32 sp34;
    register char *r;
    s32 pad;

    p = (u16 *)(*(char **)(arg0 + 0x154) + 4);
    *p = *p & ~4;
    if (arg1 != 0) {
        p = (u16 *)(*(char **)(arg0 + 0x154) + 4);
        *p = *p | 4;
    }
    D_00000000.a = arg1;
    q = &sp34;
    if ((q != 0) || (q = (s32 *)func_00000000(0xC), (q != 0))) {
        *q = 0x15;
    }
    p = (u16 *)q;
    ((GP_000126EC)FW(r, 0x34))((int)&D_00000000 + *(short *)((r = *(char **)((char *)&D_00000000 + 0x28)) + 0x30), p);
}

/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 * Promoted from NM wrap 2026-05-17 (file is -O0 per file split). */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
