/* IDO 7.1 -O2 donor for game_libs_func_000343F4 -- selector -> address of
 * a 0xC-stride table entry (game_libs data +0x1E3BC..+0x1E3EC). PROVEN
 * EXACT 25/25 words standalone (st_size = 0x64).
 *
 * BOUNDARY FIX (2026-09-05, agent-g, fifteenth mis-split case): ONE
 * function that splat had split into FIVE symbols: 343F4 (the 9-word
 * `addiu t6,a0,-1; sltiu at,t6,8; beqz -> default; jr t6` jumptable
 * dispatcher + the case-2 arm), 34424 / 34430 / 3443C (three 3-word
 * `lui v0,2; jr ra; addiu v0,v0,K` arms "matched" as
 * `return (int)(&D_00000000 + K);` stubs WITH fake-exact episodes) and
 * 34448 (the 4-word `lui; addiu; jr ra; nop` default block, carved into
 * its own -O2 -g3 TRUNCATE_TEXT unit game_libs_g3_34448.c because its jr
 * delay is unfilled). The "leaf-branch-past-end CAP" note on 343F4 is
 * RETIRED: the beqz lands on the function's own default block. Plain -O2
 * emits that unfilled `jr ra; nop` by itself (the final return block of a
 * switch-terminated fn is not delay-filled, same as 2E290's exit and
 * 560E4's shared epilogue), so the -g3 carve-out is gone.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post.c.o (the
 * 29CCC / 6DD14 / 2E290 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-
 * switch-jumptable-rodata-rename): the C `switch` puts its 8-entry table
 * in the donor's local .rodata; the splice renames that reloc to
 * game_libs_func_000343F4_rodata, pinned in undefined_syms_auto.txt to the
 * table the USO ships in game_libs rodata at +0x19B8 (raw words: entry 1
 * (a0=2) -> 34418, 2 (a0=3) -> 34424, 4 (a0=5) -> 34430, 3/5/6/7 -> 34448
 * default; the a0=1 entry at +0x19B8 is the unrelocated quirk word and the
 * 3443C arm's address sits just past the table at +0x19D8 -- the same
 * original-linker quirk 2E290's table shows, irrelevant to .text).
 *
 * Load-bearing shapes:
 *  - cases in SOURCE order 2, 3, 5, 1 (arms lay out in source order;
 *    `case 1` is the LAST arm at 3443C);
 *  - `case 8:` sharing `default:` widens the table range to 1..8
 *    (`sltiu at,t6,8`); without it IDO sizes it 1..5;
 *  - the default `return` written either inside the switch or after it
 *    compiles identically (both 25/25).
 * The 64 NM-body call sites that name game_libs_func_0003443C as a callee
 * are placeholder decodes (their raw jal word 0x0C00C7EC resolves through
 * the bootup TextReloc table to symIdx 3, not to this address). */
extern char D_00000000;

int game_libs_func_000343F4(int a0) {
    switch (a0) {
    case 2:
        return (int)(&D_00000000 + 0x1E3BC);
    case 3:
        return (int)(&D_00000000 + 0x1E3C8);
    case 5:
        return (int)(&D_00000000 + 0x1E3D4);
    case 1:
        return (int)(&D_00000000 + 0x1E3E0);
    case 8:
    default:
        return (int)(&D_00000000 + 0x1E3EC);
    }
}
