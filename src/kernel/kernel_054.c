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

s32 func_800091FC(RmonMsg91FC* msg) {
    register RmonMsg91FC* p;
    RmonHdr16 hdr;
    s32* buf;
    f32 dummy;

    p = msg;
    if (msg->field_09 != 0) {
        return -2;
    }
    dummy = 0.0f;
    buf = (s32*)func_800077DC(p->field_0C);
    if (buf == 0) {
        return -2;
    }
    func_80006B20((char*)buf + 0x130, (char*)p + 0x10, 0x20);
    *(s32*)((char*)buf + 0x12C) = p->field_90;
    hdr.field_0C = p->field_0C;
    hdr.type = p->field_04;
    hdr.flags = 0;
    func_800073F8(&hdr, 0x10, 1);
    return 0;
}

s32 func_80009148(RmonMsg91FC* msg) {
    register RmonMsg91FC* p;
    char pad[8];
    RmonPkt98 pkt;
    s32* buf;
    f32 dummy;

    p = msg;
    if (msg->field_09 != 0) {
        return -2;
    }
    dummy = 0.0f;
    buf = (s32*)func_800077DC(p->field_0C);
    if (buf == 0) {
        return -2;
    }
    func_80006B20((char*)&pkt + 0x10, (char*)buf + 0x130, 0x20);
    pkt.field_90 = *(s32*)((char*)buf + 0x12C);
    pkt.type = p->field_04;
    pkt.flags = 0;
    pkt.field_0C = p->field_0C;
    func_800073F8(&pkt, 0x98, 1);
    return 0;
}


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
