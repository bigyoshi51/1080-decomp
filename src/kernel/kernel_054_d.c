#include "common.h"

extern void* func_800077DC(s32 id);
extern void func_80006B20(void* dst, void* src, s32 n);
extern void func_800073F8(void* hdr, s32 size, s32 flags);
extern void func_80007A98(s32 a, s32 b, void* buf);
extern void func_80008D0C(void* buf);

typedef struct { s32 pad0; u8 type; char pad5; s16 flags; s32 data[17]; } RmonBuf76;

typedef struct {
    s32  pad_00;
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[0x14];
    s32  field_1C;
    char pad_20[4];
    s16  field_24;
    s16  field_26;
    char pad_28[0x24];
} RmonBuf76B;

typedef struct {
    char pad_00[4];
    u8   field_04;
    char pad_05[4];
    u8   field_09;
    char pad_0A[2];
    s32  field_0C;
    char pad_10[0x80];
    s32  field_90;
} RmonMsg91FC;

typedef struct {
    char pad_00[4];
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[4];
    s32  field_0C;
} RmonHdr16;

typedef struct {
    char pad_00[4];
    u8   type;
    char pad_05;
    s16  flags;
    char pad_08[4];
    s32  field_0C;
    char pad_10[0x80];
    s32  field_90;
} RmonPkt98;

/* split from kernel_054.c - 2026-06-10 kernel ROM-order relayout */

extern s32 func_80008430();
extern void func_800090B4(s32, s32);
extern void func_80008498(void);
extern void func_800091F0(s32);

/* MATCHED 2026-07-15 (agent-h): the "IDO -O1 scheduler, permuter-only" verdict
 * was wrong. Two coupled levers:
 *  - `s32* volatile msg` param + `p = msg;` first statement: volatile-qualified
 *    param forces a direct home reload `lw s0,0x38(sp)` (plain `p = msg` went
 *    through a t6 temp; `*(s32* volatile*)&msg` materialized an addiu addr temp).
 *    as1 hoists the callee-saved load into the jal delay slot.
 *  - zero-arg K&R call `func_80008430()` (a0 still holds msg from the prologue):
 *    removes the redundant `lw a0,0x38(sp)` arg reload.
 * Prologue sw s0/sw s1 order flipped to match as a side effect of p's real def. */
s32 func_8000969C(s32* volatile msg) {
    register s32* p;
    RmonHdr16 hdr;
    register s32 i;

    p = msg;
    if (func_80008430() != 0) {
        return -4;
    }
    func_80009148((RmonMsg91FC*)1);
    for (i = 0; i < 0x20; i++) {
        func_80006B20((void*)0x04000000, (char*)p + i * 4 + 0x10, 4);
        func_800090B4(0x32, i);
        func_80008498();
    }
    func_800091F0(1);
    hdr.field_0C = p[3];
    hdr.type = ((u8*)p)[4];
    hdr.flags = 0;
    func_800073F8(&hdr, 0x10, 1);
    return 0;
}
