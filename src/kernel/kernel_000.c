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
extern s32 D_80013000;
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
extern s32 func_80009EA0(void);
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

typedef struct {
    u8 pad_00[0x98];
    u8 in_use;
    u8 pad_99[3];
} UsoSlot;

typedef struct {
    UsoSlot slots[4];
} UsoSlotGroup;

extern u8 D_80013138;
extern UsoSlot D_800130A0;
extern u8 D_800131D4;
extern UsoSlot D_8001313C;
extern u8 D_80013270;
extern UsoSlot D_800131D8;
extern UsoSlotGroup D_80013274;
extern UsoSlotGroup D_800182E4;


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

#ifdef NON_MATCHING
/* String-compare returning 0 if equal, 1 if different.
 *
 * UPDATE 2026-05-02: 124 → 120 bytes (target 116) via goto-based structure
 * with `p1 = a0` saved across loop iter (mirrors target's `or v1, a0, zero`
 * delay slot). 4 bytes closer to target.
 *
 * Remaining 4 bytes / 1-insn cap: target uses `beql v0, zero, end` with
 * `sltu v1, zero, v0` in delay slot for entry/loop-tail v0==0 checks; mine
 * emits `beq v0, zero` with nop-filled delay. To reach target, IDO needs to
 * recognize the v0==0 branch's target as starting with the sltu pattern (so
 * it can hoist into delay), but my tail uses `if (v0 != 0) return 1;` which
 * compiles to a different shape. Tried (v4): explicit `v1 = v0 != 0; if(v1)
 * return v1;` — compiles to 124 bytes (back to baseline, sltu emitted but
 * with different surrounding structure). Cap is structural beql-emission
 * not flippable from C. */
s32 func_80000168(char *a0, char *a1) {
    s32 v0;
    s32 t7, t8;
    char *vv;
    char *p1;

    v0 = (u8)*a0;
    if (v0 == 0) goto tail;
    if ((u8)*a1 == 0) goto tail;
    p1 = a0;
loop:
    vv = a1;
    t7 = (u8)*vv;
    t8 = (u8)*p1;
    a1++;
    a0++;
    if (t7 != t8) return 1;
    v0 = (u8)*a0;
    if (v0 == 0) goto tail;
    if ((u8)*a1 == 0) goto tail;
    p1 = a0;
    goto loop;
tail:
    if (v0 != 0) return 1;
    return (u8)*a1 != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000168);
#endif

void func_800001DC(char* dst, char* src) {
    char* s = src;
    unsigned char c = *src;
    char* d = dst;

    *dst = c;
    if (c == 0) {
        return;
    }

    do {
        c = *(s + 1);
        s = s + 1;
        d = d + 1;
        *d = c;
    } while (c != 0);
}

/* uso_find_slash — scan a string for '/' and write its index to *arg1.
 *
 * Returns 1 if found (writing the slash's index to *arg1), 0 if end of
 * string reached.
 *
 * Cap (96 bytes vs target 84): IDO's bnel-back-branch with v0=v1 in delay
 * slot is the load-bearing optimization that target uses to merge the
 * "next-iteration v0 update" into the loop-tail branch. Standard C goto/do-while
 * shapes emit bne+nop without the delay-slot preload (3 extra insns).
 *
 * UPDATE 2026-05-02: cleaned up old wrap that had 6× `if (1) {}` dummy
 * blocks and a `dummy_label_580214` goto-into-fallthrough. Those didn't
 * close the bnel-preload gap and obscured the actual logic. */
#ifdef NON_MATCHING
s32 func_8000020C(char *arg0, s32 *arg1) {
    s32 v0;
    s32 v1;

    v0 = 0;
    v1 = 0;
    if ((u8)arg0[0] == 0) return 0;
    do {
        if ((u8)arg0[v0] == '/') {
            v1 -= 1;
            *arg1 = v1;
            return 1;
        }
        v0 = v1;
        v1++;
    } while ((u8)arg0[v1] != 0);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000020C);
#endif

extern s32 func_800005DC();
extern s32 func_8000060C();

#ifdef NON_MATCHING
/* +472 bytes bloat (built 800 vs baserom 328). Unrolled byte-copy loops
 * produce 2.4x the original asm. Likely the original used memcpy/bcopy
 * helpers or a different byte-copy idiom. Preserved as INCLUDE_ASM in
 * default build so kernel section size matches baserom (this single bloat
 * was responsible for ~80% of the kernel-section ROM-size mismatch). */
void func_80000260(u8* arg0, s32 arg1, u8* arg2) {
    u8 sp48[0x40];
    s32 sp44;
    s32 sp40;
    s32 a2;
    s32 v1;

    if (func_8000060C(arg0, &sp44) != 0) {
        a2 = 0;
        if (sp44 > 0) {
            if ((sp44 & 3) != 0) {
                do {
                    sp48[a2] = arg0[a2];
                    a2++;
                } while ((sp44 & 3) != a2);

                if (a2 != sp44) {
                    do {
                        sp48[a2] = arg0[a2];
                        sp48[a2 + 1] = arg0[a2 + 1];
                        sp48[a2 + 2] = arg0[a2 + 2];
                        sp48[a2 + 3] = arg0[a2 + 3];
                        a2 += 4;
                    } while (a2 != sp44);
                }
            } else {
                do {
                    sp48[a2] = arg0[a2];
                    sp48[a2 + 1] = arg0[a2 + 1];
                    sp48[a2 + 2] = arg0[a2 + 2];
                    sp48[a2 + 3] = arg0[a2 + 3];
                    a2 += 4;
                } while (a2 != sp44);
            }
        }

        sp48[a2] = 0;
        sp40 = sp44 + 1;
        func_800005DC(arg1, sp48, sp40, arg0);

        v1 = 1;
        arg2[0] = arg0[sp40];
        sp40++;
        if (arg2[0] != 0) {
            do {
                arg2[v1] = arg0[sp40];
                v1++;
                sp40++;
            } while (arg2[v1 - 1] != 0);
        }
    } else {
        func_800005DC(arg1, arg0);
        arg2[0] = 0;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000260);
#endif

void func_800003A8(s32 arg0, s32 arg1, s32 arg2) {
    s32 savedMask;
    s32 status;
    u16 first16;
    u16 loop16;

    D_80013000 = 0;
    func_8000A0E0();
    while (func_80006640() & 3) {}
    func_80004A50(0, arg1, arg0, arg2);
    status = func_80006640();
    first16 = status;
    D_80013000 = status;
    if (first16 & 3) {
        do {
            status = func_80006640();
            loop16 = status;
            D_80013000 = status;
        } while (loop16 & 3);
    }
    savedMask = func_80002890(1);
    func_80005350(arg0, arg2);
    func_80005400(arg0, arg2);
    func_80002890(savedMask);
}

/* uso_set_alloc */
extern s32 D_8000A2E0;
void func_80000474(s32 val) {
    D_8000A2E0 = val;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} Struct00480Src;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
} Struct00480Dst;

void func_80000480(Struct00480Dst* dst, Struct00480Src* src) {
    dst->unk8 = src->unk0;
    dst->unkC = src->unk4;
    dst->unk10 = src->unk8;
    dst->unk14 = src->unkC;
    dst->unk4 = 0;
    dst->unk1C = dst->unk10;
    dst->unk18 = src->unk10;
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800004B8);

/* func_80000568: shared-epilogue-return-0 stub (`nop; or v0,zero,zero;
 * lw ra/s0/s1/s2/s3; jr ra; addiu sp,+0x28`). 4 callers `jal func_80000568`
 * (in func_800004B8, func_800008F0, func_80000A98, uso_find_file) — each
 * uses this as a shared "pop my 0x28 frame and return 0" sequence after
 * setting up matching stack/saves at their own prologue. Per
 * feedback_cross_function_epilogue_entry.md: cross-function epilogue share,
 * not reproducible from standard C. INCLUDE_ASM stays. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000568);

/* uso_stub_ret0 */
s32 func_8000058C(s32 arg0) {
    return 0;
}

#ifdef NON_MATCHING
/* +52 bytes bloat (built 120 vs baserom 68). Byte-copy loop; original was
 * shorter, possibly word-aligned. Preserved as INCLUDE_ASM in default
 * build so kernel section size matches baserom. */
void func_80000598(u8* src, u8* dst, s32 count) {
    s32 remaining;
    u8* dstCurr;
    u8* srcCurr;
    u8 byte;

    srcCurr = src;
    dstCurr = dst;
    remaining = count - 1;
    if (count != 0) {
        do {
            byte = *srcCurr;
            *dstCurr = byte;
            dstCurr++;
            srcCurr++;
            remaining--;
        } while (remaining != 0);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000598);
#endif

/* NOTE: `func_8000060C` and `func_80000660` are continuation fragments of
 * `func_800005DC`, not standalone ABI-safe helpers. Keep the fragment-merge
 * notes in DECOMPILED_FUNCTIONS.md in sync when this lane moves. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800005DC);
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000060C);

#ifdef NON_MATCHING
/* func_80000660: 10-insn (0x28) tail fragment of func_800005DC.
 * Reads $a3 from sp+0x2C (caller's spill from predecessor's frame), $a2
 * from sp+0x1C (also predecessor-set). Decoded:
 *   .L80000660: t2 = a3->4 + a2; a3->4 = t2; v0 = a2;
 *   .L80000678: epilogue (lw ra, addiu sp, jr ra)
 * Branch target .L8000066C and .L80000678 are jumped to from func_800005DC's
 * body. NOT a callable function — uninitialized $a2/$a3/$a7 at entry, no
 * prologue. Cannot be matched as standalone C. Wrap is for grep
 * discoverability per feedback_orphan_include_asm_after_split_function_decomp.md. */
void func_80000660(void) {
    /* see func_800005DC — this is its tail-merge + epilogue, called
     * via `b .L80000660` or fall-through from func_8000060C. */
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80000660);
#endif

/* uso_advance_position */
void func_80000688(s32* file, s32 offset) {
    file[1] += offset;
}

s32 uso_file_open(FileState* file, u32* arg1) {
    struct {
        u32 type;
        u32 size;
        u32 unk8;
        s32 pad;
    } header;

    if (func_800009D8(&header, 0xC, 1, file) < 0) {
        return D_80013004;
    }
    if (header.type == 0xA) {
        return 0;
    }
    if (func_800009D8(arg1, header.size, 1, file) < 0) {
        return D_80013004;
    }
    if (*arg1 != 0x12345678) {
        return -0x15;
    }
    return 1;
}

/* uso_skip_to_end: reads USO section headers until End (type 11) */
/* uso_skip_to_end: reads USO section headers until End (type 11) */
/* NON_MATCHING: file offset handling is now correct via `((s32*)file)[1]`,
 * but IDO still flips the 8/11 compare operand order (`beq s2,t6` and
 * `bnel s3,t0`) instead of the target's `beq t6,s2` / `bnel t0,s3`. */
#ifdef NON_MATCHING
s32 uso_skip_to_end(FileState* file) {
    s32 pad;
    u32 header[3];
    s32 pad2;
    do {
        if (func_800009D8(header, 12, 1, file) < 0) {
            return D_80013004;
        }
        if (8 != header[0]) {
            ((s32*)file)[1] += header[1];
        }
    } while (11 != header[0]);
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", uso_skip_to_end);
#endif

/* uso_file_check — always returns 1 (success) */
s32 func_800007C4(s32 a0, s32 a1) {
    return 1;
}

typedef struct {
    char pad_00[0x14];
    s32 field_14;
    char pad_18[0x34];
    s32 field_4C;
    char pad_50[0x22];
} UsoEntry74;

typedef struct {
    char pad_00[0x84];
    void (*field_84)(void*, void*, s32, s32);
} UsoCallbacks84;

extern s32 D_8000A2E4;
extern s32 D_80012F7C;

/* NON_MATCHING: callback dispatch structure is right, but the final
 * `field_84` argument pair still compiles to the wrong pointer/add order. */
#ifdef NON_MATCHING
void func_800007D4(void) {
    UsoEntry74** var_s0;
    void* arg0;
    UsoCallbacks84* state;
    UsoEntry74** end;
    UsoEntry74* temp_v0;

    var_s0 = (UsoEntry74**)&D_80012D60;
    arg0 = &D_8000A2E4;
    state = (UsoCallbacks84*)&D_80012BC0;
    end = (UsoEntry74**)&D_80012F7C;
    temp_v0 = *var_s0;
    do {
        if (temp_v0 != 0) {
            s32 temp_a2 = temp_v0->field_4C;
            state->field_84(arg0, (char*)temp_v0 + 0x72, temp_a2, temp_a2 + temp_v0->field_14);
        }
        var_s0++;
        if (var_s0 != end) {
            temp_v0 = *var_s0;
        }
    } while (var_s0 != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800007D4);
#endif

typedef struct {
    char pad_00[0x94];
    s32 field_94;
} UsoTable94;

extern s32 D_8000A2F4;

/* NON_MATCHING: traversal is correct, but the callback argument setup still
 * compiles with the wrong register pairing for `var_s0` and `var_s2`. */
#ifdef NON_MATCHING
void func_8000085C(void) {
    s32 var_s0;
    UsoTable94* var_s1;
    void* var_s2;
    void* arg0;
    UsoCallbacks84* state;
    s32 end;

    var_s1 = (UsoTable94*)0x800130A0;
    var_s2 = (void*)0x80013112;
    arg0 = &D_8000A2F4;
    state = (UsoCallbacks84*)&D_80012BC0;
    var_s0 = 0;
    end = 0x87;
    do {
        state->field_84(arg0, var_s0, var_s1->field_94, var_s2);
        var_s0 += 1;
        var_s1 = (UsoTable94*)((char*)var_s1 + 0x9C);
        var_s2 = (char*)var_s2 + 0x9C;
    } while (var_s0 != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000085C);
#endif



INCLUDE_ASM("asm/nonmatchings/kernel", func_800008F0);

/* func_800009D8 (5-insn shared-tail epilogue: lw s1/s2/s3, jr ra, addiu sp,+0x28)
 * merged into predecessor func_8000098C (size 0x4C → 0x60). Address re-exported
 * via undefined_syms_auto.txt for the many cross-jal callers (kernel_000.c
 * line 383, 389, 409, etc.). */
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

extern s32 D_80012D30;
extern s32 D_80012D34;
extern s32 D_80012D38;
extern s32 D_80012D3C[];
extern s32 D_80012D5C;

#ifdef NON_MATCHING
/* NON_MATCHING: IDO auto-unrolls a simple pointer-walk loop with a runtime
 * subu+andi guard, producing different prologue code than target. 4 structural
 * variants tried (do-while, for(i<8), explicit end pointer, 8-way unroll);
 * none match. Target uses a fixed 2-iter loop with no zero-guard. */
void func_80001184(void) {
    s32* ptr;
    s32* end;

    D_80012D5C = 0;
    D_80012D30 = 0;
    D_80012D34 = 0;
    D_80012D38 = 0;
    ptr = D_80012D3C;
    end = &D_80012D5C;
    do {
        ptr += 4;
        ptr[-4] = 0;
        ptr[-3] = 0;
        ptr[-2] = 0;
        ptr[-1] = 0;
    } while (ptr != end);
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80001184);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", uso_find_file);

/* uso_get_error — returns last error code */
s32 func_800012AC(s32 arg0) {
    return D_80013004;
}

extern void* (*D_80012BF4)(s32, s32);
extern s32 func_800015D0(void*, void*);

#ifdef NON_MATCHING
/* NON_MATCHING: control flow and return value match, but IDO keeps the frame
 * 8 bytes smaller than target, so the spill slots land at the wrong offsets. */
void* func_800012BC(void* arg0) {
    void* file;
    s32 header[3];

    file = D_80012BF4(0x28, 8);
    if (func_800015D0(arg0, file) < 0) {
        return 0;
    }
    if (func_800009D8(header, 0xC, 1, file) < 0) {
        return 0;
    }
    ((s32*)file)[8] = ((s32*)file)[1];
    ((s32*)file)[7] = ((s32*)file)[1] + header[1];
    return file;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800012BC);
#endif

extern void func_80000A88(void*, s32);

#ifdef NON_MATCHING
/* NON_MATCHING: local stack layout differs from target, so the loop header
 * buffer and file-state fields end up at different offsets and branch layout
 * drifts after the `header[0] == 6` check. */
s32 func_80001348(void* arg0, s32* arg1) {
    s32 file[10];
    s32 header[3];
    s32 result;

    result = func_800015D0(arg0, file);
    if (result < 0) {
        return result;
    }

    while (1) {
        result = func_800009D8(header, 0xC, 1, file);
        if (result <= 0) {
            if (result == 0) {
                result = -1000;
            }
            return result;
        }
        if (header[0] == 6) {
            *arg1 = file[3] + file[1];
            return 0;
        }
        if (header[0] != 8) {
            func_80000A88(file, header[1]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80001348);
#endif

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

#ifdef NON_MATCHING
/* NON_MATCHING: the pool-walk body matches well, but the first three singleton
 * flag checks still allocate the base registers differently from target
 * (`v1`/`a0` in build versus direct `t6`/`t8`/`t0` loads with `at` stores). */
void* func_800017BC(void) {
    register u8* var_v1;

    if (D_80013138 == 0) {
        D_80013138 = 1;
        return &D_800130A0;
    }
    if (D_800131D4 == 0) {
        D_800131D4 = 1;
        return &D_8001313C;
    }
    var_v1 = (u8*)&D_80013274;
    if (D_80013270 == 0) {
        D_80013270 = 1;
        return &D_800131D8;
    }
loop_7:
    if (*(u8*)(var_v1 + 0x98) == 0) {
        *(u8*)(var_v1 + 0x98) = 1;
        return var_v1;
    }
    if (*(u8*)(var_v1 + 0x134) == 0) {
        *(u8*)(var_v1 + 0x134) = 1;
        return var_v1 + 0x9C;
    }
    if (*(u8*)(var_v1 + 0x1D0) == 0) {
        *(u8*)(var_v1 + 0x1D0) = 1;
        return var_v1 + 0x138;
    }
    if (*(u8*)(var_v1 + 0x26C) == 0) {
        *(u8*)(var_v1 + 0x26C) = 1;
        return var_v1 + 0x1D4;
    }
    var_v1 += 0x270;
    if (var_v1 != (u8*)&D_800182E4) {
        goto loop_7;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800017BC);
#endif

void func_800018A8(void) {
}

void func_800018B0(void* arg0) {
    s32 i;
    char* ptr;

    *(u8*)((char*)arg0 + 0x99) = 1;
    *(s32*)((char*)arg0 + 0x38) = 0;
    *(s32*)((char*)arg0 + 0x3C) = 0;
    ptr = (char*)arg0 + 8;
    i = 2;
    do {
        i += 4;
        *(s32*)(ptr + 0x38) = 0;
        *(s32*)(ptr + 0x3C) = 0;
        *(s32*)(ptr + 0x40) = 0;
        *(s32*)(ptr + 0x44) = 0;
        ptr += 0x10;
    } while (i != 0xE);
}

INCLUDE_ASM("asm/nonmatchings/kernel", func_800018F0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001994);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001ADC);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001CF4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001DD0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80001EC8);


/* func_800021A4 absorbed func_800021D0 fragment via merge-fragments
 * (splat split at 0x800021D0 — fragment had no prologue, used $t1/$t2/$a1
 * set by the prologue at 0x800021A4). Combined: 43 insns / 0xAC. The
 * function walks an entry list of 12-byte records, dispatching on a
 * type field (a3 = halfword[0] & 7). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002250);

INCLUDE_ASM("asm/nonmatchings/kernel", func_8000235C);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800023E0);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002530);






void func_800029A0(void) {
}
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/func_800029A0_pad.s")

/* func_800029B0 + func_80002A10 split out to kernel_045.c (-O1) */

/* func_80002A3C split out to kernel_056.c (-O2 -mips3) */

/* func_80002A78 split out to kernel_056.c (-O2 -mips3) */

/* func_80002AB4 split out to kernel_056.c (-O2 -mips3) */

/* func_80002AE0 split out to kernel_056.c (-O2 -mips3) */

/* func_80002B1C split out to kernel_056.c (-O2 -mips3) */

/* func_80002B78 split out to kernel_056.c (-O2 -mips3) */

INCLUDE_ASM("asm/nonmatchings/kernel", func_80002BA8);

/* func_80002C08 split out to kernel_056.c (-O2 -mips3) */

/* func_80002CA4 split out to kernel_056.c (-O2 -mips3) */

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






/* func_800047E4: 8-insn fragment, uses uninitialized $t2 and $t5 at entry.
 * Splat-mis-split tail of func_800047B0 (predecessor falls through with no jr
 * ra at 0x800047E0, ending with `sll t5, t4, 8`). Combined function reads 4
 * bytes from a0[0..3] big-endian and returns an unaligned 32-bit word.
 *
 * BUT: 9+ callers `jal func_800047E4` directly (in func_80003E64, func_80004030
 * × 8 sites, etc.). Each caller's pre-jal sequence happens to set $t2 (high-24
 * bits assembled) and $t5 (byte-2 << 8) — a non-standard calling convention
 * where the caller pre-loads scratch regs and the helper finishes the byte
 * combine. This is the `feedback_uninit_tN_branch_at_entry.md` pattern: not
 * matchable from C without inline-asm (IDO rejects). Keep INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800047E4);

/* NON_MATCHING: stack data packing is correct, but IDO still chooses a
 * different local layout (`-0x10` frame with `lwl/lwr`) instead of the
 * target's tight `-0x8` frame and aligned `lw` from `sp+4`. */
#ifdef NON_MATCHING
void func_80004808(u8* arg0, u32 arg1) {
    u8 sp4;
    u32 sp0;
    u8 temp_t8;

    temp_t8 = (sp4 & 0xFF03) | 0x30;
    sp4 = temp_t8;
    sp4 = (arg1 & 3) | (temp_t8 & 0xFFFC);
    sp0 = 0;
    if (arg1 != 0) {
        do {
            *((u8*)&sp0 + sp0 + 5) = arg0[sp0];
            sp0++;
        } while (sp0 < arg1);
    }
    *(volatile u32*)0xC0000000 = *(u32*)&sp4;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_80004808);
#endif

/* NON_MATCHING: control flow is correct, but IDO still emits branch-likely
 * forms (`bnezl` / `beqzl`) for the two status polls instead of the target's
 * plain `bnez` / `beqz` layout. */
#ifdef NON_MATCHING
void func_8000487C(void) {
    if ((func_80009EA0() & 0x2000) == 0) {
        do {
        } while ((func_80009EA0() & 0x2000) == 0);
    }
    *(volatile u32*)0xC000000C = 0;
    if (func_80009EA0() & 0x2000) {
        do {
        } while (func_80009EA0() & 0x2000);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000487C);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800049B8);
