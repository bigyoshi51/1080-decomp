/* -O1 donor for gl_func_0006AF44 — 65-insn list-unlink + cleanup (frame 0x38,
 * saves s0/s1/s2). PROVEN EXACT 65/65 at IDO 7.1 -O1 (2026-07-08 standalone
 * probe; plain -O1, no -g3). post1b builds -O2, where `target` gets promoted
 * to an $s reg (57 insns) — the old "stack-residency-vs-s-reg-promotion cap"
 * note is RETRACTED: the target is simply -O1, where args stay sp-homed and
 * are reloaded into fresh $t regs per use. Levers:
 *   (1) `register` prelim/curr/next in decl order = s0/s1/s2;
 *   (2) NULL-arm-first `if (target == 0) {...} else {hook}` = target's
 *       bne-to-hook-block layout (fallthrough = null path, b to join);
 *   (3) DIRECT global access (D_00000000 as an int* variable, not
 *       *(int**)&D_00000000) = LO16-folded lui/lw + $at-fused sw
 *       (the &-cast form materializes the address with an extra addiu).
 * Spliced into game_libs_post1b.c.o via REPLACE_FUNC_BODY (real -O1 compiler
 * output; blank-extern relocs imported by the splice). */
extern int gl_func_00000000();
extern int *D_00000000;

void gl_func_0006AF44(int *target) {
    register int prelim;
    register int *curr;
    register int *next;

    prelim = gl_func_00000000();
    if (target == 0) {
        target = D_00000000;
    } else {
        if (*(unsigned short *)((char *)target + 0x10) != 1) {
            gl_func_00000000(target[2], target);
        }
    }
    if (D_00000000 == target) {
        D_00000000 = (int *)D_00000000[3];
    } else {
        curr = D_00000000;
        while (curr[1] != -1) {
            next = (int *)curr[3];
            if (next == target) {
                curr[3] = target[3];
                break;
            }
            curr = next;
        }
    }
    if (target == D_00000000) {
        gl_func_00000000();
    }
    gl_func_00000000(prelim);
}
