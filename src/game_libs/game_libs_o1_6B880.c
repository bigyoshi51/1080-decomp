/* -O1 donor for gl_func_0006B880 — 59-insn ring-buffer append with notify
 * callback (frame 0x30, saves s0). PROVEN EXACT 59/59 at IDO 7.1 -O1
 * (2026-07-08 standalone probe; plain -O1, no -g3). post1b builds -O2 (the
 * old wrap was 38%: -O2 register-promotes head). Levers:
 *   (1) guard fused into ONE expression `(head = load) == 0 || count >= cap`
 *       = the loaded reg (t8) stays live across the beq (home store rides the
 *       delay slot) and feeds the count/cap loads directly — separate
 *       statements reload from the sp home (+1 insn);
 *   (2) NESTED-IF tail (no early return) = uopt keeps the head reload (t6)
 *       live into the call, filling the jal delay with `or a0,t6` (the
 *       early-return form re-loads a0 from the home slot instead);
 *   (3) decl order bufp/head/slot = sp+0x2C/0x28/0x24 homes;
 *       `register int res;` = $s0 across the second call. */
extern int gl_func_00000000();
extern int D_00000000;

void gl_func_0006B880(void) {
    int *bufp;
    char *head;
    int slot;
    register int res;

    bufp = (int *)((char *)&D_00000000 + 0x40);
    if ((head = *(char **)((char *)&D_00000000 + 0x40)) == 0 ||
        *(int *)(head + 8) >= *(int *)(head + 0x10)) {
        return;
    }
    slot = (*(int *)(head + 0xC) + *(int *)(head + 8)) % *(int *)(head + 0x10);
    *(int *)(*(char **)(head + 0x14) + slot * 4) = bufp[1];
    *(int *)(head + 8) = *(int *)(head + 8) + 1;
    if (**(int ***)head != 0) {
        res = gl_func_00000000(head);
        gl_func_00000000((char *)&D_00000000, res);
    }
}
