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
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_80012BE4;
extern s32 D_80012C64;
extern s32 D_80012C68;
extern s32 D_80012D60[];
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


INCLUDE_ASM("asm/nonmatchings/kernel", func_80000000);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800000B0);

/* Boot init */
void func_80000118(s32 a0, s32 a1) {
    s32 saved = func_80002890(1);
    func_8000A0E0();
    func_80005350(a0, a1);
    func_80005400(a0, a1);
    func_80002890(saved);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000168);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800001DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000020C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000260);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800003A8);

/* uso_set_alloc */
extern s32 D_8000A2E0;
void func_80000474(s32 val) {
    D_8000A2E0 = val;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000480);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800004B8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);

/* uso_stub_ret0 */
s32 func_8000058C(s32 arg0) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800005DC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000060C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000660);

/* uso_advance_position */
void func_80000688(s32* file, s32 offset) {
    file[1] += offset;
}

INCLUDE_ASM("asm/nonmatchings/kernel", uso_file_open);

/* uso_skip_to_end: reads USO section headers until End (type 11) */
/* NON_MATCHING: beq operand order (cosmetic, $s2/$t6 swap in 2 instructions) */
#ifdef NON_MATCHING
s32 uso_skip_to_end(FileState* file) {
    s32 pad;
    u32 header[3];
    s32 pad2;
    do {
        if (func_800009D8(header, 12, 1, file) < 0) {
            return D_80013004;
        }
        if (header[0] != 8) {
            file->position += header[1];
        }
    } while (header[0] != 11);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", uso_skip_to_end);
#endif

/* uso_file_check — always returns 1 (success) */
s32 func_800007C4(s32 a0, s32 a1) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800007D4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000085C);



INCLUDE_ASM("asm/nonmatchings/kernel", func_800008F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800009D8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800009EC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A88);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000A98);

/* uso_call_init — dispatches a function from the USO module vtable */
typedef s32 (*UsoFunc)(void*);

s32 func_80000C88(void) {
    s32 modIndex = D_80012C68;
    s32* mod;
    s32 funcIndex;
    s32 funcTable;

    if (modIndex < 0) {
        return -1;
    }

    mod = (s32*)D_80012D60[modIndex];
    if (mod == 0) {
        return -1;
    }

    funcIndex = D_80012C64;
    if (funcIndex < 0) {
        return -1;
    }

    funcTable = *(s32*)((char*)mod + 0x3C);
    if (funcTable == 0) {
        return -1;
    }

    {
        UsoFunc fn = (UsoFunc)*(s32*)(funcTable + funcIndex * 12 + 4);
        D_80012BE4 = fn(&D_80012BC0);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000D2C);

void func_80000E58(void) {
    D_80012C44(&D_8000A32C, &D_8000A340);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_80000E8C);

/* uso_get_vtable — returns pointer to USO vtable */
extern s32 D_80012BC0;
void* func_800010B4(void) {
    return &D_80012BC0;
}

/* uso_set_callbacks (no-op) */
void func_800010C0(s32 a0, s32 a1) {
}

void func_800010CC(s32 a0, ...) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800010E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001184);

INCLUDE_ASM("asm/nonmatchings/kernel", uso_find_file);

/* uso_get_error — returns last error code */
s32 func_800012AC(s32 arg0) {
    return D_80013004;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800012BC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001348);

/* uso_read */
s32 func_80001414(void* file, void* buf, s32 size) {
    extern s32 D_80013004;
    extern s32 func_800009D8(void*, s32, s32, void*);
    s32 result;
    result = func_800009D8(buf, size, 1, file);
    if (result < 0) {
        return D_80013004;
    }
    return result;
}

/* uso_file_end — returns file position + size */
s32 func_80001460(s32* file) {
    return file[1] + file[3];
}

/* uso_seek — set or adjust file position */
s32 func_80001470(s32* file, s32 whence, s32 offset) {
    if (whence) {
        file[1] += offset;
    } else {
        file[1] = offset;
    }
    return file[1];
}

/* uso_file_close (no-op) */
void func_80001494(s32 arg0) {
}

/* uso_ret_zero — returns 0.0f */
float func_8000149C(void) {
    return 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800014A8);




void func_800017B4(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800017BC);

void func_800018A8(void) {
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001994);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001ADC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001EC8);


INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002250);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000235C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800023E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002530);






INCLUDE_ASM("asm/nonmatchings/kernel", func_800029A0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800029B0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A10);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A3C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002A78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AB4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002AE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B1C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002B78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002BA8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002C08);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CA4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002CD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DB0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DE0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002DF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E70);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002E78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002F78);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800030D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031D0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800031F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003C24);


INCLUDE_ASM("asm/nonmatchings/kernel", func_80003D40);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E0C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E54);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003E64);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80003FF0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004030);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800044CC);






INCLUDE_ASM("asm/nonmatchings/kernel", func_800047E4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000487C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800049B8);

