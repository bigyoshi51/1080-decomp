/* -O1 donor for gl_func_0006B7A0 — 58-insn PI/AI status-poll + 0xA5000510
 * DMA-register writes + hardcoded-jal call (frame 0x20, saves ra).
 * PROVEN EXACT 58/58 at IDO 7.1 -O1 (2026-07-08 standalone probe; 57/58 in
 * isolation with only the jal word blank — gl_ref_0007FEEC resolves it at link
 * to the target's baked `jal 0x7FEEC` = 0C01FFBB; 5.3 -O1 identical).
 * ABSORBS the 2-word orphan game_libs_func_0006B798 (its lui/lw t6 pair is
 * this function's stolen prologue: p = (int *)(D_00000000_a + 0x14)); the
 * donor's true entry is 0x6B798 and the splice grows the host symbol by 8.
 * Levers: (1) volatile int stat = the homed status local — each poll is
 *   sw 0x18(sp); lw; andi; branch (plain int registerizes the guard);
 * (2) while() pre-read + loop re-read gives the guard beqz + bottom bnez;
 * (3) second 0xA5000510 write has NO |0x10000000 and its sw sinks into the
 *   jal delay slot; (4) final D_c = D_b | 0x100401 keeps distinct blank
 *   externs for the lw and sw bases (no lui CSE).
 * Spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; blank-extern relocs imported by the splice). */
extern int gl_ref_0007FEEC();
extern char *D_00000000_a;   /* record base pointer */
extern int D_00000000_b;     /* source word */
extern int D_00000000_c;     /* dest word */

void gl_func_0006B7A0(void) {
    int *p;
    volatile int stat;

    p = (int *)(D_00000000_a + 0x14);
    stat = *(volatile int *)0xA4600010;
    while (stat & 3) {
        stat = *(volatile int *)0xA4600010;
    }
    *(volatile int *)0xA5000510 = p[4] | 0x10000000;
    stat = *(volatile int *)0xA4600010;
    while (stat & 3) {
        stat = *(volatile int *)0xA4600010;
    }
    *(volatile int *)0xA5000510 = p[4];
    gl_ref_0007FEEC();
    *(volatile int *)0xA4600010 = 2;
    D_00000000_c = D_00000000_b | 0x100401;
}
