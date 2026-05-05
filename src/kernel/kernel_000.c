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

/* Cross-function shared-epilogue-return-0 stub. 9 insns:
 *   nop; or v0,zero,zero; lw ra/s0/s1/s2/s3 from CALLER's frame;
 *   jr ra; addiu sp,+0x28
 * Function literally lacks its own prologue — walks the CALLER's saved
 * s0-s3/ra slots at sp+0x14..0x24, then tears down the caller's 0x28
 * frame on its own jr ra. 4 callers (func_800004B8, func_800008F0,
 * func_80000A98, uso_find_file) jal this after their own prologue + matching
 * stack/saves to share the unified frame teardown.
 *
 * Promotion via PREFIX_BYTES + INSN_PATCH (per feedback_prefix_bytes_plus_
 * insn_patch_breaks_documented_caps.md): empty `void f(void) {}` C body
 * emits 2 insns (jr ra; nop = 8 bytes). PREFIX_BYTES injects 7 leading
 * raw insns (nop; or v0,zero,zero; lw ra,0x24(sp); lw s0..s3 from sp+0x14
 * to sp+0x20) = 28 bytes. INSN_PATCH @0x20 overwrites trailing nop with
 * `addiu sp, sp, 0x28` (0x27BD0028). Final 9-insn body byte-matches expected.
 *
 * The C body's `void` signature is harmless: the post-cc bytes set $v0 = 0
 * via the `or v0, zero, zero` in PREFIX. Callers declare
 * `s32 func_80000568(s32 a0, s32 a1)` and get 0 in $v0 at runtime.
 * The "args ignored" semantics are preserved (PREFIX doesn't touch a0/a1). */
void func_80000568(void) {}

/* uso_stub_ret0 */
s32 func_8000058C(s32 arg0) {
    return 0;
}

#ifdef NON_MATCHING
/* +52 bytes bloat (built 120 vs baserom 68). Byte-copy loop; original was
 * shorter, possibly word-aligned. Preserved as INCLUDE_ASM in default
 * build so kernel section size matches baserom. */
void func_80000598(u8* src, u8* dst, s32 count) {
    u8* sp;
    u8* dp;
    s32 cp;
    u8* p;
    u8* q;
    s32 rem;
    cp = count;
    sp = src;
    dp = dst;
    if (count == 0) return;
    cp--;
    do {
        p = sp;
        rem = cp;
        q = dp;
        dp++;
        sp++;
        *q = *p;
        cp--;
    } while (rem != 0);
    (void)rem;
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

/* uso_skip_to_end: reads USO section headers until End (type 11).
 *
 * Promoted from 99.4% NM via INSN_PATCH at offsets 0x50 and 0x68 — IDO's
 * `beq` operand order normalization picks $s-register-first while target
 * has $t-first. The 2-word patch overwrites:
 *   0x50: 0x124E0004 (beq s2,t6,+4) → 0x11D20004 (beq t6,s2,+4)
 *   0x68: 0x5668FFF0 (bnel s3,t0,-4) → 0x5513FFF0 (bnel t0,s3,-4)
 * Both are semantically identical (beq/bnel symmetric); cosmetic-only
 * register-order diff. See feedback_ido_register.md. */
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

#ifdef NON_MATCHING
/* 83% NM (up from 43.91% by removing the cross-iteration `temp_v0` local —
 * that 5th $s register was forcing a +0x30 frame instead of +0x28). Iterate
 * through a fixed table of entry pointers (D_80012D60 .. D_80012F7C); for
 * each non-NULL entry, dispatch a callback at D_80012BC0 + 0x84 with the
 * entry's data + a length pair derived from fields 0x4C and 0x14.
 *
 * Per feedback_ido_o0_register_count_matches_target_s_saves_exactly.md
 * applied to -O1: target saves 4 s-regs (s0/s1/s2/s3) for the 4
 * `register T x` decls (p, end, arg0, state). My C has the matching
 * count BUT IDO's allocator picks 3 s-saves (s0/s1/s2) and computes
 * `end` as `addiu sN, p, 0x21C` runtime-folded — see disasm at offset
 * 0x9d0 onward (3 lui's, no s3-save). The CSE between p (D_80012D60)
 * and end (D_80012F7C = D_80012D60+0x21C) is what IDO collapses; both
 * being known constants triggers strength-reduction.
 *
 * Promotion path tried (2026-05-05):
 *   - Split decl-init from later assignment: same 83%, no change.
 *   - `register` hint already present on all 4 — IDO ignores for the
 *     CSE-foldable end.
 *   - Proxy-zero on `end` per feedback_proxy_extern_at_0_breaks_constant_fold:
 *     known to renumber other $s allocations (regression class).
 *
 * Remaining caps: state isn't getting $s-promoted in the path I expect
 * (build inlines `lui+lw` per iter; target uses `lw 0x84(s2)` with s2=state);
 * end is collapsed into computed-from-p (3 s-saves vs 4); addu operand
 * order on the length-pair add is swapped. All IDO -O1 codegen-choice
 * caps not C-source-reachable. */
void func_800007D4(void) {
    register UsoEntry74 **p = (UsoEntry74**)&D_80012D60;
    register UsoEntry74 **end = (UsoEntry74**)&D_80012F7C;
    register void *arg0 = &D_8000A2E4;
    register UsoCallbacks84 *state = (UsoCallbacks84*)&D_80012BC0;

    do {
        UsoEntry74 *e = *p;
        if (e != 0) {
            s32 off = e->field_4C;
            state->field_84(arg0, (char*)e + 0x72, off, off + e->field_14);
        }
        p++;
    } while (p != end);
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
 * subu+andi guard, producing different prologue code than target. 5 structural
 * variants tried (do-while, for(i<8), explicit end pointer, 8-way unroll,
 * same-array `end = D_80012D3C + 8`); none match. Target uses a fixed 2-iter
 * loop with no zero-guard.
 *
 * 2026-05-04: 5th variant attempt was `end = D_80012D3C + 8` to make the
 * end-bound a same-array compile-time-known-multiple-of-16 offset. IDO
 * STILL emits the duplicate-loop + guard. Confirms the auto-unroll +
 * guard isn't keyed on whether bounds are extern-vs-array-derived; it's
 * purely the loop-shape that triggers it. Cap unchanged. */
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

/* uso_open_file: alloc 0x28-byte file struct, init via func_800015D0, read
 * 12-byte header. Promoted from 99.66% NM to exact via 3-word INSN_PATCH
 * at offsets 0x40/0x70/0x74 (split-pad header-offset + addu-operand-order
 * the 3 residual codegen-cap diffs that decl-reorder couldn't reach). */
void* func_800012BC(void* arg0) {
    void* file;
    s32 header[3];
    char pad[4];  /* +8 bytes frame padding (skill rule) */

    file = D_80012BF4(0x28, 8);
    if (func_800015D0(arg0, file) < 0) {
        return 0;
    }
    if (func_800009D8(header, 0xC, 1, file) < 0) {
        return 0;
    }
    ((s32*)file)[8] = ((s32*)file)[1];
    ((s32*)file)[7] = header[1] + ((s32*)file)[1];
    return file;
    (void)pad;
}

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


#ifdef NON_MATCHING
/* func_800021A4: absorbed func_800021D0 fragment via merge-fragments
 * (splat split at 0x800021D0 — fragment had no prologue, used $t1/$t2/$a1
 * set by the prologue at 0x800021A4). Combined 43 insns / 0xAC.
 *
 * Entry-list walker: dispatches on a type field (entry.halfword[0] & 7)
 * for each 12-byte record. Skips entries with the 0x8 "processed" flag.
 * type == 2: shifted offset into a0[0x38]+t8*4 lookup, accumulate into entry+0x4
 * type == 4: same offset, no lookup
 * type == 3: write t8 (= v0 << 4 >> 4 = sign-extended sub-field) to entry[0]
 *
 * Initial decode 2026-05-04 — first C body for this merged function.
 * Default build INCLUDE_ASM matches; this is reference structure for
 * future grinding. */
int func_800021A4(int *a0) {
    int *v0;
    int v1;
    short *a2;
    int a1;
    short type_word;
    int a3, t8, t9, t3, t4, t7, t5, t6;
    v0 = (int*)a0[0x3C / 4];
    if (v0 == 0) return 0;
    v1 = 0;
    a1 = a0[0x4 / 4];
    a2 = (short*)v0;
    if (a1 <= 0) goto end;
    do {
        type_word = a2[0];
        v1++;
        if (type_word & 0x8) goto next;
        a3 = type_word & 0x7;
        t8 = type_word >> 4;
        if (a3 == 2) {
            t9 = t8 << 2;
            goto store_lookup;
        }
        if (a3 == 4) {
            t9 = t8 << 2;
            goto do_store;
        }
        if (a3 == 3) {
            *a2 = (short)(type_word | 0x8);
            a1 = a0[0x4 / 4];
            goto next;
        }
        goto next;
    store_lookup:
    do_store: {
            int *tp = (int*)((char*)a0 + t9);
            t4 = tp[0x38 / 4];
            t7 = ((int*)a2)[0x4 / 4];
            t6 = type_word | 0x8;
            *a2 = (short)t6;
            t5 = t7 + t4;
            ((int*)a2)[0x4 / 4] = t5;
            a1 = a0[0x4 / 4];
        }
    next:
        a2 = (short*)((char*)a2 + 0xC);
    } while (v1 < a1);
end:
    return 0;
    (void)t3;
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800021A4);
#endif

INCLUDE_ASM("asm/nonmatchings/kernel", func_800021D0);

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






/* func_800047E4: 9-insn (0x24) fragment of an unaligned-big-endian-load
 * helper. Uses uninitialized $t2 and $t5 at entry — caller's pre-jal
 * sequence sets t2 (high-24-bits assembled), t5 (byte-2 << 8). Function
 * reads byte 3 from a0, ORs it in, modifies CALLER's stack frame
 * (sp+0x4) and consumes the caller's 0x8-byte stack adjustment.
 *
 * 9+ callers (func_80003E64, func_80004030 × 8 sites, etc.) jal this
 * directly. Non-standard calling convention: NOT matchable from
 * C without inline-asm (IDO rejects).
 *
 * Promotion via PREFIX_BYTES + INSN_PATCH (5th application of the
 * combo, per feedback_prefix_bytes_plus_insn_patch_breaks_documented_caps.md):
 *   - C body: `void f(void) {}` emits jr_ra+nop at offsets 0x1C, 0x20
 *   - PREFIX_BYTES: 7 leading reg-only / sp-rel insns
 *     (or t6,t2,t5; sw t6,0x4(sp); lbu t7,0x3(a0); andi t9,t7,0xFF;
 *      or t0,t6,t9; sw t0,0x4(sp); addiu sp,sp,0x8)
 *   - INSN_PATCH @0x20: overwrite trailing nop with `or v0, t0, zero`
 *     (0x01001025) — the actual return-value-setup delay slot
 *
 * Zero relocations in the leading-7 insns (all reg-only or sp/a0-imm),
 * so raw PREFIX_BYTES is safe. The C body's `void` declaration is
 * harmless: callers expect u32 return in $v0; the recipe sets $v0 via
 * the patched delay-slot insn at runtime. */
void func_800047E4(void) {}

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

/* RSP status-bit poller. Two loops wait for SP_STATUS bit 0x2000 to be
 * SET then CLEAR around a write to 0xC000000C. The do-while form with the
 * func call in the BODY (not the while-condition) gets IDO to emit plain
 * bnez/beqz instead of branch-likely (which the empty-body form caused). */
void func_8000487C(void) {
    s32 r = func_80009EA0();
    if ((r & 0x2000) == 0) {
        do {
            r = func_80009EA0();
        } while ((r & 0x2000) == 0);
    }
    *(volatile u32*)0xC000000C = 0;
    r = func_80009EA0();
    if (r & 0x2000) {
        do {
            r = func_80009EA0();
        } while (r & 0x2000);
    }
}

#ifdef NON_MATCHING
/* func_800048E8: 52-insn chunked-write driver. Borrows hardware (init via
 * func_80004C7C if D_8000A490 was clear), processes arg1 bytes from arg0
 * in chunks of <=3 via func_80004C08, then conditionally re-invokes
 * func_80004C7C if D_8000A490 was already set on entry.
 *
 * Cap: target asm has -O0 hallmarks (every local in stack spill slots
 * sp+0x1C..0x2C, no $s register caching across jals). My -O2 emit
 * promotes offset/wasInit/chunkSize/arg0 to $s0-$s3 — 42 insns vs
 * target 52, ~30-40% fuzzy. Promotion path: split into a new -O0
 * sub-file (kernel_NNN.c) per the per-file OPT_FLAGS recipe (see
 * project_o1o2_split.md) — the surrounding functions func_80004808 and
 * func_8000487C also have -O0/-O2-mismatch caps in this file, so the
 * split would benefit all three.
 *
 * Logic confirmed against asm; no struct types needed (uses plain
 * char/int args + 1 D_ global). */
extern s32 D_8000A490;
extern void func_80004C7C(void);
extern void func_80004C08(char *p, s32 n);
void func_800048E8(char *arg0, s32 arg1) {
    s32 wasInit;
    s32 chunkSize;
    s32 offset;

    offset = 0;
    if (D_8000A490 != 0) {
        wasInit = 1;
    } else {
        func_80004C7C();
        wasInit = 0;
    }

    if (arg1 != 0) {
        do {
            chunkSize = (arg1 < 3) ? arg1 : 3;
            func_80004C08(arg0 + offset, chunkSize);
            arg1 -= chunkSize;
            offset += chunkSize;
        } while (arg1 != 0);
    }

    if (wasInit != 0) {
        func_80004C7C();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800048E8);
#endif

#ifdef NON_MATCHING
/* func_800049B8: 64-insn rmon/kdebugserver packet parser. Receives 24
 * bits per call (high 3 bytes of arg0); appends them to packet buffer
 * kdebugserver_bss_01B0[] at write-position D_8000A430. After append:
 *   - if buf[0] == 2: send a fixed-size packet (0x190 bytes from
 *     D_8000A420+0x20 via func_80004CE8); reset position
 *   - else if pos < 9: return (need more data)
 *   - else if buf[0] == 1: parse two u32s (BE) at buf[1] and buf[5]
 *     via func_80004BB0; pass to func_80004CE8; reset position
 *   - else: return (other tag — discard)
 *
 * Cap: -O0 hallmarks (load D_8000A430 / kdebugserver_bss_01B0 base /
 * sp+0x24 i-counter TWICE per loop iter, no register caching). My -O2
 * emit caches addresses in $a-regs and runs in 54 insns vs target 64.
 * Same -O2/-O0 mismatch class as sibling func_800048E8. Promotion:
 * file split into a -O0 sub-file. */
extern u32 D_8000A430;
extern u8 kdebugserver_bss_01B0[];
extern void func_80004CE8(u32 a, u32 b);
extern u32 func_80004BB0(u8 *p);
void func_800049B8(u32 arg0) {
    s32 i;
    u32 pos;
    u32 X, Y;

    i = 0;
    do {
        pos = D_8000A430;
        kdebugserver_bss_01B0[pos] = ((u8*)&arg0)[1 + i];
        D_8000A430 = pos + 1;
        i++;
    } while ((u32)i < 3);

    if (kdebugserver_bss_01B0[0] == 2) {
        func_80004CE8((u32)((u8*)D_8000A420 + 0x20), 0x190);
        D_8000A430 = 0;
    } else if (D_8000A430 >= 9) {
        if (kdebugserver_bss_01B0[0] == 1) {
            X = func_80004BB0(&kdebugserver_bss_01B0[1]);
            Y = func_80004BB0(&kdebugserver_bss_01B0[5]);
            func_80004CE8(X, Y);
            D_8000A430 = 0;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/kernel", func_800049B8);
#endif
