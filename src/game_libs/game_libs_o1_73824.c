/* -O1 donor for gl_func_00073824 — 53-insn 8-word record init + u64-return
 * call + conditional u64-arg call (frame 0x20, saves ra). PROVEN EXACT 53/53
 * at IDO 7.1 -O1 (2026-07-08 standalone probe; 5.3 -O1 emits the identical
 * 53 words). Signature is the load-bearing lever: params 2 and 3 are
 * unsigned long long — the 8-byte alignment makes p skip $a1 (its slot
 * 0x24 is never homed, matching the target's missing sw a1) and land in
 * a2/a3, with q on the stack at 0x30/0x34. Other levers:
 *   (1) u64 pair copies `*(u64 *)(dst+2) = q` / `(dst+4) = p|q` give the
 *       shared-dst-reload lw/lw/sw/sw quads (lo word first);
 *   (2) `if (p != 0)` on a u64 = the target's bnez-hi / beqz-lo two-branch
 *       chain, and the then-arm reuses the condition's loaded pair;
 *   (3) r = gl_func_00000000_ll(dst) homes v0/v1 at 0x18/0x1C; passing r
 *       as a u64 arg reloads them into a0/a1 (lw a1 fills the jal delay).
 * Spliced into game_libs_post2b_d.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; blank-extern relocs imported by the splice). */
extern unsigned long long gl_func_00000000_ll(int *);
extern void gl_func_00000000(unsigned long long);
extern int **D_00000000_a;

int gl_func_00073824(int *dst, unsigned long long p, unsigned long long q, int g, int h) {
    unsigned long long r;

    dst[0] = 0;
    dst[1] = 0;
    *(unsigned long long *)(dst + 2) = q;
    if (p != 0) {
        *(unsigned long long *)(dst + 4) = p;
    } else {
        *(unsigned long long *)(dst + 4) = q;
    }
    dst[6] = g;
    dst[7] = h;
    r = gl_func_00000000_ll(dst);
    if (*D_00000000_a == dst) {
        gl_func_00000000(r);
    }
    return 0;
}
