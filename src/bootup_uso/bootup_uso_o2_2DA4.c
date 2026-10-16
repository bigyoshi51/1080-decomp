/* IDO 7.1 -O2 donor for func_00002DA4 -- bootup_uso subsystem init + 12-way
 * command dispatch (0x1EC / 123 words; word-exact standalone apart from the
 * reloc fields).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into bootup_uso.c.o (the game_libs
 * 7344 / 52CD4 recipe, docs/MATCHING_WORKFLOW.md#post0b-jumptable-donor-52cd4):
 * the switch's donor-local .rodata jumptable reloc is renamed
 * func_00002DA4_rodata and pinned in undefined_syms_auto.txt to 0x4F4, the
 * table bootup_uso ships in its RoData (module 0xD9FE28; file offset 0x4F8 =
 * imm + 4, the word at 0x4F4 is the preceding 0.04f literal). Table words
 * (cases 1..12): 2F10 2E98 2ED4 2EAC 2EE8 2EFC 2F74 2F74 2F38 2F4C 2F60 2EC0,
 * so the arms lay out in SOURCE order 2, 4, 12, 3, 5, 6, 1, 9, 10, 11 and
 * cases 7/8 share the default (&D_00007408). The 2026-07-10 NM decode had the
 * table one entry late (3,5,1,4,...); extract-uso-jumptable.py drops the
 * LAST entry here (0x2EC0), not the first.
 *
 * Load-bearing shapes:
 *  - distinct base-0 globals (docs/IDO_CODEGEN.md#lui-count-placeholder-
 *    sweep-44de4): the created object is stored through D_2DA4_obj and
 *    re-read at once through D_2DA4_obj_rd (one symbol forwards the stored
 *    v0 instead of the target's `lui a1; lw a1,0(a1)`); the config word is
 *    read through D_2DA4_cfg+4 and stored through D_00000000+4 (one symbol
 *    CSEs the lui).
 *  - calls whose result is unused go through the void alias
 *    func_00000000_2DA4_v: with the int-returning blank, the dead $v0 def
 *    pushes the named config value `v` to v1 (target v0).
 *  - case 1: `a1 = obj; if (1) { a1 += 0x18; } *(int *)a1 |= 4` reusing the
 *    a1 variable gives `lw t0,24(a1); addiu a1,a1,24; ... sw t1,0(a1)`.
 *  - `a1` declared before `v1` puts their spill homes at sp+0x1C / sp+0x18.
 *  - `v | 0x80000 | 0x2000 | 0x20000` stays unfolded (lui/or, ori, lui/or). */
#include "common.h"

extern int func_00000000();
extern void func_00000000_2DA4_v();
extern char D_000073EC, D_000073F8, D_00007408;
extern int D_2DA4_obj, D_2DA4_obj_rd;
extern char D_00000000, D_2DA4_cfg;

#define FW(p, o) (*(int *)((char *)(p) + (o)))

void func_00002DA4(char *arg0, s32 arg1, s32 arg2) {
    char *a1;
    char *v1;
    int v;
    func_00000000_2DA4_v(&D_000073EC, 0);
    func_00000000_2DA4_v();
    D_2DA4_obj = func_00000000(0, &D_000073F8);
    v1 = (char *)FW(arg0, 0x84);
    a1 = (char *)D_2DA4_obj_rd;
    func_00000000_2DA4_v(v1 + 0x10, a1);
    if (FW(a1, 0x14) != 0) {
        FW(a1, 0x4) = 1;
    }
    FW(a1, 0x14) = (int)v1;
    func_00000000_2DA4_v(D_2DA4_obj);
    v = *(int *)((char *)&D_2DA4_cfg + 4);
    v = v | 0x80000 | 0x2000 | 0x20000;
    *(int *)((char *)&D_00000000 + 4) = v;
    switch (arg1) {
    case 2: func_00000000_2DA4_v(arg0, arg2); break;
    case 4: func_00000000_2DA4_v(arg0, arg2); break;
    case 12: func_00000000_2DA4_v(arg0, arg2); break;
    case 3: func_00000000_2DA4_v(arg0, arg2); break;
    case 5: func_00000000_2DA4_v(arg0, arg2); break;
    case 6: func_00000000_2DA4_v(arg0, arg2); break;
    case 1:
        func_00000000_2DA4_v(arg0, 0);
        a1 = (char *)D_2DA4_obj; if (1) { a1 += 0x18; } *(int *)a1 = *(int *)a1 | 4;
        break;
    case 9: func_00000000_2DA4_v(arg0, arg2); break;
    case 10: func_00000000_2DA4_v(arg0, arg2); break;
    case 11: func_00000000_2DA4_v(arg0, arg2); break;
    default:
        func_00000000_2DA4_v(&D_00007408);
        break;
    }
}
