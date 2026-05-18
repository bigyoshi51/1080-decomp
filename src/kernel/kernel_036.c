#include "common.h"

extern void* func_80009C30(void);

typedef struct RmonThreadNode {
    s32 unk0;
    s32 state;
    s32 unk8;
    struct RmonThreadNode* next;
    s32 unk10;
    s32 threadId;
} RmonThreadNode;

/* __rmonSendHeader — find free comm slot and configure it */
void __rmonSendHeader(void) {
    register s32* node = (s32*)func_80009C30();
    while (node[1] != -1) {
        if (node[1] == 0) {
            *(s32*)((char*)node + 0x118) = *(s32*)((char*)node + 0x118) & 0xFFFF00FE;
            *(s32*)((char*)node + 0x118) = *(s32*)((char*)node + 0x118) | 0x6C01;
            break;
        }
        node = (s32*)node[3];
    }
}

/* func_800073DC is the prologue fragment of the original 31-insn function
 * at ROM 0x800073DC, which splat split into:
 *   - func_800073DC (this file, 7 insns / 0x1C — prologue + first jal,
 *     no jr ra — falls through to next function in linker layout)
 *   - func_800073F8 (kernel_018.c INCLUDE_ASM, 25 insns / 0x64 — body)
 *
 * The full decompiled body lives above as `__rmonSendHeader` (matched 100%
 * per report.json). The INCLUDE_ASM below is residual dead duplicate code
 * emitted at a separate .o offset; removing it would shift downstream .o
 * layout so it stays for now.
 *
 * 2026-05-05 — evaluated PREFIX_BYTES + INSN_PATCH promotion (per
 * `docs/POST_CC_RECIPES.md` and feedback_prefix_bytes_plus_insn_patch_
 * breaks_documented_caps.md): BLOCKED by two combined constraints:
 *   1. The function's `jal func_80009C30` must carry an R_MIPS_26
 *      relocation in the .o for byte_verify against expected/.o. Raw
 *      PREFIX_BYTES are reloc-less, so prefix-encoded jals would produce
 *      correct ROM bytes but mismatch expected/.o at the .o level.
 *   2. Putting the jal in the C body emits a reloc'd jal but also a
 *      full 8-insn prologue+epilogue (0x20), which can't shrink to
 *      target's 7-insn (0x1C) "no-epilogue, falls-through" shape.
 * No recipe combines "function with .o reloc on jal" + "no jr ra
 * epilogue." Combo applicability window narrowed: leading-N insns of
 * any prefix must contain zero reloc'd jal or lui-extern-pair.
 *
 * 2026-05-06: tested __attribute__((noreturn)) to strip the epilogue —
 * IDO cfe rejects with "Syntax Error" on the attribute syntax (the
 * GNU __attribute__ extension is not supported by IDO 7.1). Confirmed
 * structural cap; no C-level path can produce 7-insn body with reloc'd
 * jal AND no jr ra epilogue.
 *
 * 2026-05-07: tested `for(;;);` infinite-loop sentinel after jal to
 * mark fall-through as unreachable. IDO -O2 still emits full epilogue
 * (lw ra; addiu sp; jr ra; nop) AT the function tail, after a 4-insn
 * nop-padded unreachable region. Net 13 insns (vs 7-insn target).
 * Loop infiniteness is not propagated to reorg.c's epilogue-emission
 * logic. Same cap holds.
 *
 * 2026-05-18: promoted from INCLUDE_ASM with the C body below plus the
 * kernel_036.c.o post-cc recipe. IDO -O1 with a `register` node emits the
 * exact 0x80-byte logical `func_800073DC + func_800073F8` instruction stream,
 * including the relocatable `jal func_80009C30`. The Makefile then zeros the
 * first two successor-body words and clips the .text section to preserve the
 * historical 0x1C symbol boundary and 8 bytes of padding. */
RmonThreadNode* func_800073DC(s32 threadId) {
    register RmonThreadNode* node;

    node = func_80009C30();
    if (threadId <= 0) {
        return 0;
    }
    if (node->state != -1) {
        do {
            if (node->threadId == threadId) {
                return node;
            }
            node = node->next;
        } while (node->state != -1);
    }
    return 0;
}
