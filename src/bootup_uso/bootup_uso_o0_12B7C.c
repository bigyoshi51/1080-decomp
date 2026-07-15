#include "common.h"

/* Run 10 members (now covers 0x12818..0x12BF8). */

extern int func_00000000();
extern int D_00000000;
extern int D_A0000200;

/* func_00012818: 99.73% NON_MATCHING. Sole diff (0x5C/0x64): the
 * `if (D_A0000200 == 0xAC290000)` value-load. IDO -O0 emits
 *   lui $t5,%hi; lw $t5,%lo($t5); bne $t5,$at   (REUSES the %hi base $t5)
 * but the target uses a FRESH dest:
 *   lui $t5,%hi; lw $t6,%lo($t5); bne $t6,$at
 * Pure -O0 value-load reg-reuse, NOT C-reachable here. Tried:
 *  - operand swap (0xAC29... == D_A0000200): IDO canonicalizes, no change.
 *  - struct member at offset 0 (D_A0000200.v): same reuse.
 *  - array form (D_A0000200[0]): DOES give fresh $t6, but materializes the
 *    full base (lui+addiu+lw) -> +1 insn, wrong size (0x98 vs 0x94).
 * No same-size C produces fresh-dest-with-folded-%lo, so this is also
 * permuter-immune (can't flip the reg without adding an instruction).
 * (Was an INSN_PATCH target; INSN_PATCH removed 2026-05-23 as match-faking.)
 * 2026-06-09 EXTENDED NEGATIVE (do not re-try): volatile D_A0000200 at 7.1
 * AND 5.3 (reuse persists); IDO 5.3 -O0 plain (identical 2 diffs -- the
 * value-load reuse is version-invariant); chaining the unused-assignment
 * into the condition via && (+3 insns, worse) or comma operator (same 2
 * diffs -- the -O0 temp counter resets per value, not per statement).
 * Every compiler-version/qualifier/expression-chaining axis now exhausted.
 * Genuine -O0 codegen cap. */
/* 2026-06-11 permuter CONCLUDED: base 20 (1 true diff) flat through
 * 551k iterations -- allocator-internal (-O0 temp allocator class).
 * 99.73 stands.
 * 2026-06-11 wave-2: two more axes dead — `D_A0000000[0x80]` zero-lo array
 * base gives fresh $t6 + folded 0x200 offset but -O0 keeps the `addiu
 * base,base,0` (+1 insn); switch-form adds a dispatch beq block. */
/* 2026-07-15 (agent-g) CAP RETRACTED — EXACT via LITERAL cast-pointer
 * deref `*(int*)0xA0000200`: with a CONSTANT address (not the extern
 * symbol) -O0 gives the address its own temp (lui t5,0xA000) and the
 * value a FRESH temp (lw t6,0x200(t5)) with the low16 folded into the
 * load offset — the exact target words 3C0DA000/8DAE0200, reloc-free.
 * All prior negatives had probed only SYMBOL spellings. objdiff shows
 * 99.73 as an artifact (expected .o carries %hi/%lo relocs with zeroed
 * fields); the linked ROM is byte-identical (cmp clean). */
void func_00012818(char *a0, char *a1) {
    int i;
    register int *unused;

    i = 0;
    do {
        (*(char**)(a0 + 0x154))[i + 6] = a1[i];
    } while (++i < 8);

    unused = &D_00000000;

    if (*(int*)0xA0000200 == 0xAC290000) {
        func_00000000(a0);
    }
}

void func_000128AC(char *a0, char *a1, char *a2) {
    if (a2 != 0) {
        *(int*)(a2 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a2,
            ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][2],
            ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][1]);
    }
    if (a1 != 0) {
        if (*(int*)(a0 + 0x168) == 0) {
            *(int*)(a0 + 0x168) = *(int*)(a0 + 0x160);
        }
        *(char*)(a0 + 0x178) = (char)*(int*)(a0 + 0x64);
        *(char*)(a0 + 0x179) = (char)*(int*)(a0 + 0x4C);
        *(char*)(a0 + 0x17A) = (char)*(int*)(a0 + 0x50);
        *(char*)(a0 + 0x17B) = (char)*(int*)(a0 + 0x54);
        *(int*)(a1 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x164), a0 + 0x170);
        *(int*)(a0 + 0x184) = 0;
    }
}

void func_000129A0(char *a0, char *a1, char *a2) {
    if (a1 != 0) {
        if (*(int*)(a0 + 0x168) == 0) {
            *(int*)(a0 + 0x168) = *(int*)(a0 + 0x160);
        }
        *(char*)(a0 + 0x178) = (char)*(int*)(a0 + 0x64);
        *(char*)(a0 + 0x179) = (char)*(int*)(a0 + 0x4C);
        *(char*)(a0 + 0x17A) = (char)*(int*)(a0 + 0x50);
        *(char*)(a0 + 0x17B) = (char)*(int*)(a0 + 0x54);
        *(int*)(a1 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x164), a0 + 0x170);
        *(int*)(a0 + 0x184) = 0;
    }
    if (a2 != 0) {
        if (*(int*)(a0 + 0x16C) == 0) {
            *(int*)(a0 + 0x16C) = func_00000000(*(int*)(a0 + 0x164) << 2);
        }
        *(int*)(a2 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a2, *(int*)(a0 + 0x16C), *(int*)(a0 + 0x164), a0 + 0x174);
        *(int*)(a0 + 0x184) = 0;
    }
}

void func_00012AC4(char *a0, char *a1, int a2) {
    if (a1 != 0) {
        if (*(int*)(a0 + 0x168) == 0) {
            *(int*)(a0 + 0x168) = *(int*)(a0 + 0x160);
        }
        *(char*)(a0 + 0x178) = (char)*(int*)(a0 + 0x64);
        *(char*)(a0 + 0x179) = (char)*(int*)(a0 + 0x4C);
        *(char*)(a0 + 0x17A) = (char)*(int*)(a0 + 0x50);
        *(char*)(a0 + 0x17B) = (char)*(int*)(a0 + 0x54);
        *(int*)(a1 + 0x6C) = 0xFFFBFFFF;
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x164), a0 + 0x170);
        *(int*)(a0 + 0x184) = 0;
    }
}

void func_00012B7C(char *a0, int a1, int a2) {
    if (a1 != 0) {
        func_00000000(a1, *(int*)(a0 + 0x168), *(int*)(a0 + 0x170));
    }
    if (a2 != 0) {
        func_00000000(a2, ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][2], ((int**)(*(char**)(a0 + 0x14C) + 0x8))[0][1]);
    }
}
