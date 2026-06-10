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

/*(piece 1: func_8000894C; pieces b/c/d split out) from kernel_054.c - 2026-06-10 kernel ROM-order relayout */

void func_8000894C(s32 arg0, s32 arg1) {
    RmonBuf76B buf;
    register s32 id;

    if (arg0 != 0) {
        id = arg0;
    } else {
        id = 0x3EB;
    }
    func_80007A98(0, id, &buf);
    func_80008D0C(&buf);
    if (arg1 == 0xF) {
        buf.field_24 = 1;
        buf.field_26 = 2;
    }
    if (arg1 < 0x10) {
        arg1 = 0;
    } else {
        arg1 -= 0x10;
    }
    if (arg1 != 0) {
        buf.field_1C = 0xD;
    }
    func_800073F8(&buf, 0x4C, 2);
}
