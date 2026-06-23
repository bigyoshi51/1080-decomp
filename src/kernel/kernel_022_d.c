#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern s32 func_80006A50(s32, s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];



/* split from kernel_022.c - 2026-06-10 kernel ROM-order relayout */








/* func_80008C30 - MATCHED (byte-exact, -O1). RSP/RDP-style command emit:
 * a0/a1 carry small signed bitfields (6-bit x from a0, 5-bit y from a1)
 * packed into a 4-byte stack command word (byte0 bits 2-7 = x<<2, byte1
 * bits 0-4 = y), then func_80006A50(0x04001000, word) submits and
 * func_80006A50(0x04080000, 0) kicks/commits.
 * MATCH KEY (was capped ~68% with char bitfields): use INT bitfields, not
 * char. char bitfields force an 8-bit sign-truncation (sll 0x18; sra 0x18)
 * on the assigned value; int bitfields store the already-6-bit sign-ext
 * value directly (matching target's plain `sll<<2; andi 0xfc`). And the
 * word-sized zero-init + the `*(int*)cmd` reads must go through a
 * union { struct bits; s32 w; } overlay — that yields the single
 * `sw zero,28(sp)` + direct frame `lb`/`sb` RMW (andi 0xff03 / 0xffe0 =
 * complement masks promoted to int, low-16 andi imm), instead of the
 * address-taken `addiu;sw` an array form produces. See docs/IDO_CODEGEN. */
typedef struct {
    int x : 6;
    int f0lo : 2;
    int f1hi : 3;
    int y : 5;
    int b2 : 8;
    int b3 : 8;
} CmdBits8C30;

typedef union {
    CmdBits8C30 c;
    s32 w;
} CmdU8C30;

void func_80008C30(int a0, int a1) {
    CmdU8C30 u;
    u.w = 0;
    u.c.x = (a0 << 26) >> 26;
    u.c.y = (a1 << 27) >> 27;
    func_80006A50(0x04001000, u.w);
    func_80006A50(0x04080000, 0);
}

/* func_80008CB4: 0x80008CB4-0x80008D44 - MATCHED (byte-exact, -O1). Sibling of
 * func_80008C30; same int-bitfield + union technique. Adds a 3rd field z at
 * byte2 bits 3-7 (`int z:5; int b2lo:3`), set to 4 so (4<<3)=0x20 -> the
 * `andi 0xff07; ori 0x20` byte2 RMW matches. */
typedef struct {
    int x : 6;
    int f0lo : 2;
    int f1hi : 3;
    int y : 5;
    int z : 5;
    int b2lo : 3;
    int b3 : 8;
} CmdBitsCB4;

typedef union {
    CmdBitsCB4 c;
    s32 w;
} CmdUCB4;

void func_80008CB4(int a0, int a1) {
    CmdUCB4 u;
    u.w = 0;
    u.c.x = (a0 << 26) >> 26;
    u.c.y = (a1 << 27) >> 27;
    u.c.z = 4;
    func_80006A50(0x04001000, u.w);
    func_80006A50(0x04080000, 0);
}
