#include "common.h"

extern s32 func_80007A98(s32, s32, void*);
extern void func_800073F8(void*, s32, s32);

typedef struct { s32 pad0; u8 type; char pad5; s16 flags; s32 data[17]; } RmonBuf76;
typedef struct { s32 pad0; u8 type; char pad5[4]; u8 domain; char padA[2]; s32 id; } RmonMsg;

/* __rmonGetGRegisters */
s32 func_8000798C(RmonMsg* msg) {
    RmonMsg* p = msg;
    RmonBuf76 buf;
    if (func_80007A98(p->domain, p->id, &buf) != 0) {
        return -2;
    }
    buf.type = p->type;
    buf.flags = 0;
    func_800073F8(&buf, 0x4C, 1);
    return 0;
}

/* func_800079F4 - verified structural decode (0xA4, 41 insns).
 * Message-kind dispatcher; shares func_80007A98's epilogue via the
 * already-resolved cross-function labels .L80007AAC/.L80007AB4
 * (undefined_syms_auto.txt:319-320) - this function has no own jr ra,
 * it tail-jumps into func_80007A98's shared return. NOT a fragment;
 * boundary already correct.
 *   void func_800079F4(Msg *a0) {            // a0 spilled sp+0x74/0x78
 *       switch (a0->0x9) {                   // u8 kind (lbu)
 *       case 0:
 *           func_8000785C(a0->0xC);          // simple forward
 *           return;
 *       case 1:
 *           if (func_80008430() == 0) return;
 *           func_80008454();
 *           h = func_80006A98(0x40800000);   // a0 = 0x40800000
 *           if (h == 0) return;
 *           h -= 4;
 *           func_8000898C(1, 0x3E8, h + 0x40010000);
 *           if (h & 3) return;
 *           ... (continues into shared tail)
 *       default:
 *           goto alt_tail;                   // .L80007AAC
 *       }
 *   }
 * Struct-typing reference: a0 = message/event record; a0->0x9 (9) u8
 * dispatch kind (0 = forward payload a0->0xC to func_8000785C, 1 =
 * init/alloc sequence via func_80008430/_80008454/_80006A98/_8000898C
 * with magic args 0x40800000 / 0x40010000 / 0x3E8, else alt path);
 * a0->0xC (12) payload ptr. Caps <80: cross-function shared-epilogue
 * tail-jump (no local jr ra) + 5 jal calls + magic-constant lui/ori
 * args. Full body INCLUDE_ASM-preserved (.s = source of truth).
 * INCLUDE_ASM (no episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800079F4);
