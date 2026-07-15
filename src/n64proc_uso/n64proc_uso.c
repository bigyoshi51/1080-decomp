#include "common.h"

extern int gl_func_00000000();

/* USO entry-0: leading `beq zero,zero,+0x6F00` trampoline (loader-patched
 * at runtime) followed by an empty void body. The 4-byte trampoline is
 * injected post-cc via PREFIX_BYTES (Makefile + scripts/inject-prefix-bytes.py).
 * The body is just jr ra + nop (8 bytes); after injection the function
 * symbol covers the full 12 bytes target wants. */
void n64proc_uso_func_00000000(void) {
}

void n64proc_uso_func_0000000C(void) {
}

extern char D_00000000;

extern char gl_d_n64p14[];
void n64proc_uso_func_00000014(int arg0, int arg1) {
    char *base = gl_d_n64p14;
    char *base10 = gl_d_n64p14 + 0x10;
    int *cur;
    int flag = 0;
    int one = 1;
    int r;

    do {
        switch (arg1) {
        case 0:
            gl_func_00000000(base, one, 0, 0);
            flag = one;
            r = gl_func_00000000(0);
            gl_func_00000000(arg0, one, r);
            break;
        case 1:
            cur = (int*)gl_func_00000000(0, one, 0);
            flag = one;
            gl_func_00000000(base10, cur);
            if (*(int*)((char*)cur + 0x14) != 0) {
                *(int*)((char*)cur + 0x4) = one;
            }
            *(int*)((char*)cur + 0x14) = (int)base;
            break;
        }
        arg1 = *(int*)(gl_d_n64p14 + 0x40);
    } while (flag == 0);
}

/* n64proc_uso_func_00000100: 76-insn / 0x130 TRIPLE find-or-create cascade.
 * Fuzzy 99.24 % (13/76 words differ). Residual is a register-renumber +
 * spill-slot-coalescing cap — structure, schedule and CSE are all exact.
 *
 * Logic: cascade of `x = prev; if (!x) { x = alloc(N); if (!x) goto tail; }`
 * over p(=a0-reuse) / q / r, then shared labeled tails Lq28/Lp28 write each
 * sub-object's 0x28 vtable slot, then a large p-init block (see body).
 *
 * PROGRESS 2026-07-10 (agent-g): 95.01 -> 99.24 (+4.23pp) by porting the exact
 * idiom that made the sibling eddproc_uso_func_0000025C BYTE-EXACT:
 *   (1) REUSE the `a0` param as the running object p (not a fresh `void *p`
 *       local) — p lives to `return a0`, so IDO saves it in $s0 and homes its
 *       incoming value without a separate move. This fixed the prologue
 *       schedule (target `move s0,a0` at 0x108 + `sw ra` sunk into the bne
 *       delay slot at 0x110; the old nested-if wrap had these reversed).
 *   (2) goto-chain dispatch (have0/have1/have2) instead of nested `if` blocks —
 *       keeps the dead stage-guards as forward `bne` in target sense.
 *   (3) statement-line-join on the `have2:` line (label + gl_func call +
 *       vtable store on ONE source line) — flips IDO's scheduler.
 * DISTINCT vtable externs (D_n64_100_b/c/d/e -> 0x0) already bust the &D
 * address-CSE so the four stores re-materialize (t6/t7/t8/t9) — kept.
 *
 * REMAINING CAP (13 words, agent-g 2026-07-10, confirms the prior 2026-05-05
 * analysis): q is colored to $v1 but the target uses $a3; r/p are already
 * correct ($a0/$s0). Because p is forced into $s0 (live across the whole
 * post-cascade block) IDO's coloring numbers the remaining passthrough q into
 * $a3 in the target, $v1 in the build. That cascades into the spill layout:
 * target coalesces q's slot with the late z-pointer spill at sp+0x24 (frame
 * 0x28); the build gives q/r/z three distinct slots (sp+0x24/0x28/0x2C, frame
 * 0x30). This is a pure IDO RTL-allocator register-renumber + slot-coalesce
 * choice — NOT reachable from C. Prior agent already proved `register` hints,
 * block-scope z, ternary-cascade, and decl-order swap are all no-ops; agent-g
 * re-confirmed the decl-order swap (r/q) is a no-op at the 99.24 form. The
 * sibling eddproc match colored ITS q to $v1 (matching its target, which has
 * no post-cascade block forcing $s0), so the a3 coloring here is genuinely a
 * different, unreachable allocation. Leave NON_MATCHING. */
extern int gl_func_00000000();
extern char D_n64_100_a, D_n64_100_b, D_n64_100_c, D_n64_100_d, D_n64_100_e, D_n64_100_f;
void *n64proc_uso_func_00000100(void *a0) {
    void *q;
    void *r;

    if (a0 != 0) goto have0;
    a0 = (void*)gl_func_00000000(0x88);
    if (a0 == 0) goto end;
have0:
    q = a0;
    if (a0 != 0) goto have1;
    q = (void*)gl_func_00000000(0x50);
    if (q == 0) goto Lp28;
have1:
    r = q;
    if (q != 0) goto have2;
    r = (void*)gl_func_00000000(0x2C);
    if (r == 0) goto Lq28;
have2: gl_func_00000000(r, (char*)&D_n64_100_a + 0xB0); *(int*)((char*)r + 0x28) = (int)&D_n64_100_b;
Lq28:
    *(int*)((char*)q + 0x28) = (int)&D_n64_100_c;
Lp28:
    *(int*)((char*)a0 + 0x28) = (int)((char*)&D_n64_100_d + 0x18);
    *(int*)((char*)a0 + 0xC)  = (int)((char*)&D_n64_100_e + 0xB8);
    gl_func_00000000(a0);

    *(int*)((char*)a0 + 0x50) = 0;
    *(int*)((char*)a0 + 0x3C) = 0x64;
    *(int*)((char*)a0 + 0x54) = 0xFF;
    /* SAME-NAME destructive reuse (E9C0 lever): the late registration node is
     * the SAME variable as the cascade's q — its a1-arg spill/a3-reload web
     * joins q's family, coloring the whole family $a3 and COALESCING both
     * spills into one home slot 0x24 (frame 0x30 -> 0x28). A block-scoped
     * `int *z` gave q=$v1 + three distinct slots (the old 13-word cap). */
    q = *(void**)((char*)&D_n64_100_f + 0x190);
    gl_func_00000000((char*)a0 + 0x10, q);
    if (((int*)q)[0x14 / 4] != 0) ((int*)q)[1] = 1;
    ((int*)q)[0x14 / 4] = (int)a0;
    gl_func_00000000(*(int*)((char*)&D_n64_100_f + 0x190), 2, 0);
    gl_func_00000000(0xA3);
    *(int*)((char*)a0 + 0x48) = 0;
    *(int*)((char*)a0 + 0x30) = 0;
    *(int*)((char*)a0 + 0x2C) = 0;
end:
    return a0;
}

void n64proc_uso_func_00000230(char *a0) {
    gl_func_00000000(a0 + 0x58, 6);
    gl_func_00000000(a0 + 0x70, 3);
}

/* n64proc_uso_func_00000268: MATCHED 2026-06-01. State machine on a0->0x50
 * (key dispatch).
 *   case 0: decrement a0->0x3C; if <16, decay a0->0x54 by 16 (clamp>=0);
 *           when a0->0x3C hits 0, transition to mode 1 + reset a0->0x3C=100.
 *   case 1: ramp a0->0x54 by 8 (clamp<=255); decrement a0->0x3C; on 0 OR
 *           (a0->0x3C<0x55 && gl_func(&D,0x40100)!=0), set D[0x40]=1, call gl_func(a0,0,0).
 *
 * Switch form emits the target's beql-to-case dispatch polarity; in-place RMW
 * on the counters makes IDO re-read fields into fresh $t regs instead of
 * collapsing named temporaries into $v0. */
void n64proc_uso_func_00000268(int *a0) {
    int v;

    v = a0[0x50/4];
    switch (v) {
    case 0:
        a0[0x3C/4]--;
        if (a0[0x3C/4] < 0x10) {
            a0[0x54/4] -= 0x10;
            if (a0[0x54/4] < 0) a0[0x54/4] = 0;
            if (a0[0x3C/4] == 0) {
                a0[0x50/4] = 1;
                a0[0x3C/4] = 0x64;
            }
        }
        break;
    case 1:
        a0[0x54/4] += 8;
        if (a0[0x54/4] >= 0x100) a0[0x54/4] = 0xFF;
        a0[0x3C/4]--;
        if (a0[0x3C/4] == 0 || (a0[0x3C/4] < 0x55 && gl_func_00000000(&D_00000000, 0x40100) != 0)) {
            *(int*)((char*)&D_00000000 + 0x40) = 1;
            gl_func_00000000(a0, 0, 0);
        }
        break;
    }
}

/* n64proc_uso_func_0000035C: MATCHED 2026-05-31. key-dispatch on *(a0+0x50):
 * case 0 inits a0+0x58 subobject, case 1 inits a0+0x70, both from a 4x1.0f buf.
 * Cracked the key==1 branch-polarity cap with a `switch` — the if/goto chain
 * emitted `bne key,1,end` (k1 as fall-through); the switch emits the target's
 * `beq key,1,k1` dispatch. Frame layout via pad1[4]/pad2[12] around buf[4].
 * See docs/IDO_CODEGEN.md#switch-vs-if-goto-dispatch-polarity. */
void n64proc_uso_func_0000035C(char *a0) {
    char pad1[4];
    float buf[4];
    int key;
    int val;
    char pad2[12];
    buf[0] = 1.0f;
    buf[1] = 1.0f;
    buf[2] = 1.0f;
    buf[3] = 1.0f;
    key = *(int*)(a0 + 0x50);
    switch (key) {
    case 0:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x58);
        gl_func_00000000(a0 + 0x58, 0xA0, 0x78, 3);
        break;
    case 1:
        val = *(int*)(a0 + 0x54);
        gl_func_00000000(&D_00000000, val, buf);
        gl_func_00000000(a0 + 0x70);
        gl_func_00000000(a0 + 0x70, 0xA0, 0x78, 3);
        break;
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/n64proc_uso/n64proc_uso/n64proc_uso_func_0000035C_pad.s")
