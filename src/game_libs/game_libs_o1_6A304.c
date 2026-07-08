/* -O1 donor for gl_func_0006A304 — 71-insn pointer-relocation fixup driver
 * (frame 0x20, ra only). PROVEN EXACT 71/71 at IDO 7.1 -O1 (2026-07-08
 * standalone probe: 69/71 raw with the 2 remaining words being the UNBAKED
 * HI16/LO16 of D_00041710, which link to the target's lui 0x4 / addiu 0x1710;
 * final-ROM byte gate confirms). post1b builds -O2, which constant-folds every
 * field access into absolute lui/lw (the old "deferred: symbol plumbing" cap
 * note). Levers:
 *   (1) real relocated symbol D_00041710 (= 0x41710 in undefined_syms_auto.txt)
 *       so the base stays a symbol address held in a reg/stack home — the
 *       0x41710 int-constant form emits lui/ori (target has lui/addiu);
 *   (2) plain -O1: obj homed at sp+0x1C and reloaded `lw tN,0x1C(sp)` before
 *       every field test/store, a0 homed+reloaded for the first call. */
extern int gl_func_00000000();
extern char D_00041710[];

int gl_func_0006A304(int a0) {
    char *obj;

    obj = D_00041710;
    gl_func_00000000(a0, obj, 0x40);
    if (*(int *)(obj + 0x10)) {
        *(int *)(obj + 0x10) = gl_func_00000000(*(int *)(obj + 0x10));
    }
    if (*(int *)(obj + 0x18)) {
        *(int *)(obj + 0x18) = gl_func_00000000(*(int *)(obj + 0x18));
    }
    if (*(int *)(obj + 0x20)) {
        *(int *)(obj + 0x20) = gl_func_00000000(*(int *)(obj + 0x20));
    }
    if (*(int *)(obj + 0x28)) {
        *(int *)(obj + 0x28) = gl_func_00000000(*(int *)(obj + 0x28));
    }
    if (*(int *)(obj + 0x2C)) {
        *(int *)(obj + 0x2C) = gl_func_00000000(*(int *)(obj + 0x2C));
    }
    if (*(int *)(obj + 0x30)) {
        *(int *)(obj + 0x30) = gl_func_00000000(*(int *)(obj + 0x30));
    }
    if (*(int *)(obj + 0x38)) {
        *(int *)(obj + 0x38) = gl_func_00000000(*(int *)(obj + 0x38));
    }
    return (int)obj;
}
