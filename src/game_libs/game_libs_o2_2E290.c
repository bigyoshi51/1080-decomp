/* IDO 7.1 -O2 donor for game_libs_func_0002E290 -- selector-byte lookup
 * with a mask-narrowing retry loop. PROVEN EXACT 49/49 words standalone
 * (the 50th-52nd build words are .text alignment zeros; st_size = 0xC4).
 *
 * BOUNDARY FIX (2026-09-05, agent-g): ONE function that splat had split
 * into NINE symbols: 2E290 (the 26-word `jr t6` jumptable dispatcher +
 * the case-2 body), 2E2F8/2E300/2E308/2E310/2E318/2E320/2E328 (seven
 * 2-word `jr ra; li v0,K` case arms that were "matched" as
 * `int f(void) { return K; }` stubs WITH fake-exact episodes) and 2E330
 * (the 9-word `default:` mask/retry block + `return 0` exit, an
 * INCLUDE_ASM "caller-set $v0/$a1 loop tail CAP"). The old SOURCE=2 AUDIT
 * "boundary/codegen cap, non-contiguous selector tail" verdict is RETIRED:
 * the function IS contiguous, 0x2E290..0x2E354 = 0xC4 / 49 words.
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post.c.o (the
 * 29CCC / 6DD14 recipe, docs/MATCHING_WORKFLOW.md#donor-splice-switch-
 * jumptable-rodata-rename): a C `switch` puts its 32-entry jumptable in
 * the donor's local .rodata; the splice renames that reloc to
 * game_libs_func_0002E290_rodata, pinned in undefined_syms_auto.txt to
 * the table the USO ships in game_libs rodata at +0x1660 (read straight
 * out of bootup.uso RoData/RoDataReloc: sel 2 -> 2E2D8, 3 -> 2E300,
 * 5 -> 2E308, 9 -> 2E310, 17 -> 2E318, all others -> 2E330 default;
 * the shipped entry for sel 1 is a zero-addend reloc and the 2E320
 * `return 8` arm's address sits unrelocated just past the table at
 * +0x16E0 -- an original-linker quirk that does not affect .text).
 *
 * Load-bearing shapes:
 *  - `case 32:` sharing `default:` widens the table range to 1..32
 *    (`slti at,sel,0x21` / `sltiu at,idx,0x20`); without it IDO sizes the
 *    table 1..17 (0x12 / 0x11). Same lever as 6DD14's `case 15: case 16:`.
 *  - case arms are laid out in SOURCE order: 2, 3, 5, 9, 17, 1, 0x40,
 *    default -- `case 1: return 8` must come AFTER `case 17`.
 *  - `unsigned char mask = 0xFF; unsigned char sel` locals: `mask <<= 1`
 *    is sll + andi 0xFF, `sel &= mask` is and + andi 0xFF (v0 / a1).
 *  - do { switch } while (sel != 0); return 0;  gives the `bnel` back
 *    edge with the loop-top `slti` duplicated into its delay slot and the
 *    `move v0,zero; jr ra; nop` exit; the hoisted `li a2,0x40` is the
 *    switch's out-of-table compare constant made loop-invariant.
 *  - `return (unsigned char)(o[0x15] + 12)` = lbu/addiu/jr/andi tail. */
int game_libs_func_0002E290(unsigned char *o) {
    unsigned char mask = 0xFF;
    unsigned char sel = o[0x31];
    do {
        switch (sel) {
        case 2:
            if (o[0x14] == 1) {
                return (unsigned char)(o[0x15] + 12);
            }
            return 16;
        case 3:
            return 0;
        case 5:
            return 2;
        case 9:
            return 4;
        case 17:
            return 6;
        case 1:
            return 8;
        case 0x40:
            return 10;
        case 32:
        default:
            mask <<= 1;
            sel &= mask;
        }
    } while (sel != 0);
    return 0;
}
