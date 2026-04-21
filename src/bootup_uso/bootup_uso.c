#include "common.h"

/* func_00000000 is splat's synthetic symbol for unrelocated JAL target 0x0.
 * Its raw bytes are `jr $ra; nop` — keep as INCLUDE_ASM to preserve that
 * without IDO emitting a return-value or masking by the return type. Every
 * caller supplies their own forward decl with the return type they need. */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000000);

/* File-scope K&R decl, int return. Void-discarding callers just ignore
 * the value; value-using callers get it directly. Same underlying symbol. */

extern char D_00000000;
void func_00000008(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00000044(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

typedef struct { int a, b, c; } Tri3i;
typedef struct { float x, y, z; } Vec3;
void func_00000080(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

typedef struct { int a, b, c, d; } Quad4;
void func_000000F0(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

extern char D_00006538;
void func_00000148(int a0, int a1, int a2) {
    func_00000000(&D_00006538);
    func_00000000(a0, a1, a2);
}

extern char D_00006544;
void func_00000188(int a0, int a1, int a2) {
    func_00000000(&D_00006544);
    func_00000000(a0, a1, a2);
}

void func_000001C8(int a0) {
    if (a0 != 0) {
        func_00000000(2);
    } else {
        func_00000000(0);
    }
}

void func_000001FC(void) {
    func_00000000();
}

void func_0000021C(void) {
    func_00000000();
}

void func_0000023C(void) {
    func_00000000();
}

void func_0000025C(void) {
    func_00000000();
}

void func_0000027C(void) {
    func_00000000();
}

void func_0000029C(void) {
    func_00000000();
}

void func_000002BC(void) {
    func_00000000();
}

void func_000002DC(void) {
    func_00000000();
}

void func_000002FC(void) {
    func_00000000();
}

void func_0000031C(int a0, int a1, int a2) {
    int local1, local2;
    func_00000000(a1, &local1, &local2, a2);
    func_00000000(a0, local1, (signed char)local2);
}

extern char D_00006550;
void func_00000360(void) {
    func_00000000();
    func_00000000(&D_00006550);
}

extern char D_00006568;
void func_0000038C(void) {
    func_00000000();
    func_00000000(&D_00006568);
}

void func_000003B8(void) {
    func_00000000();
}

void func_000003D8(void) {
    func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000003F8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000057C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000610);

void func_0000085C(int *a0) {
    int a1 = *a0;
    if (a1 != 0) {
        func_00000000(a1);
    }
}

void func_00000888(int *a0) {
    int a1 = *a0;
    if (a1 != 0) {
        func_00000000(a1);
    }
}

void func_000008B4(int *a0) {
    func_00000000(*a0);
}

void func_000008D4(int *a0) {
    func_00000000(*a0);
}

void func_000008F4(int *a0, int a1_orig) {
    int ret = func_00000000(a0, a0[2]);
    int node = *a0;
    if (node != 0) {
        func_00000000(node, ret, 0, a1_orig);
    }
}

void func_00000940(int *a0, int a1_orig) {
    int ret = func_00000000(a0, a0[2]);
    int node = *a0;
    if (node != 0) {
        func_00000000(node, ret, 3, a1_orig);
    }
}

void func_0000098C(int *a0, int a1_orig) {
    int ret = func_00000000(a0, a0[2]);
    int node = *a0;
    if (node != 0) {
        func_00000000(node, ret, 1, a1_orig);
    }
}

void func_000009D8(int *a0, int a1_orig) {
    int ret = func_00000000(a0, a0[2]);
    int node = *a0;
    if (node != 0) {
        func_00000000(node, ret, 2, a1_orig);
    }
}

void func_00000A24(int *a0) {
    int a1 = *a0;
    if (a1 != 0) {
        func_00000000(a1);
    }
}

void func_00000A50(int **a0, int a1) {
    int *v0 = *a0;
    if (v0 != 0) {
        ((char*)v0)[0x1F] = (char)a1;
    }
}

void func_00000A68(int *a0) {
    int a1 = *a0;
    if (a1 != 0) {
        func_00000000(a1);
    }
}

void func_00000A94(int *a0, int a1) {
    a0[2] = a1;
}

#ifdef NON_MATCHING
/* 97.8 %: IDO uses $v0 directly in the delay-slot `addiu v0, 8` for the 'n'
 * case; target uses $v1 and `or v0, v1, zero` at the shared return block.
 * Tried: goto forms, named local, `register int r = 8` (ignored here since
 * value flows to return), `||` fusion of n/s (produces bnel chains, worse),
 * mid-function `r = 8; goto` splits. IDO's allocator always picks $v0 when
 * the value flows to the return register. Same unflippable pattern class as
 * feedback_ido_arg_save_reg_pick.md (IDO always $a1) and
 * feedback_ido_o2_tiny_wrapper_unflippable.md. */
int func_00000A9C(int a0, int a1) {
    if (a1 == 0)   goto L_AE4;
    if (a1 == 'e') goto L_AEC;
    if (a1 == 'd') goto L_AF4;
    if (a1 == 'm') goto L_AFC;
    if (a1 == 't') goto L_B04;
    if (a1 == 'n') goto L_B0C;
    if (a1 == 's') goto L_B0C;
    return 2;
L_AE4: return 1;
L_AEC: return 4;
L_AF4: return 0x10;
L_AFC: return 0x40;
L_B04: return 0x20;
L_B0C: return 8;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000A9C);
#endif

void func_00000B14(int **a0, int a1) {
    int *v0 = *a0;
    if (v0 != 0) {
        ((char*)v0)[0x1D] = (char)a1;
    }
}

extern float D_00000068;
void func_00000B2C(void **a0, float a1) {
    a1 = a1 / D_00000068;
    if (*a0 != 0) {
        *(float*)((char*)*a0 + 0x10) = a1;
    }
}

void func_00000B50(char *a0) {
    int scratch;
    func_00000008(&scratch);
    func_00000044((float*)(a0 + 0x10));
}

void func_00000B80(char *a0) {
    int scratch;
    func_00000008(&scratch);
    func_00000080(a0 + 0x10);
}

void func_00000BB0(char *a0) {
    int scratch;
    func_00000008(&scratch);
    func_000000F0(a0 + 0x10);
}

void func_00000BE0(char *a0) {
    int scratch;
    func_00000008(&scratch);
    func_00000008((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000C10);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000CA0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000D94);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000E68);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001A44);

void func_00001C10(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00001C4C(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_00001C88();
void func_00001C88(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_00001CF8(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_00001D34(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void *func_00001D8C(void *a0) {
    if (a0 == 0) {
        a0 = (void*)func_00000000(0x48);
    }
    return a0;
}

void *func_00001DB8(void *a0, int a1, int a2) {
    if (a0 == 0) {
        a0 = (void*)func_00000000(0x48);
        if (a0 == 0) goto end;
    }
    func_00000000(a0, a1);
    *(int*)((char*)a0 + 0x40) = a2;
end:
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001E08);

#ifdef NON_MATCHING
/* 98 %: IDO always picks $a1 to save `a0` across the jal; target chooses $a3.
 * Same bytes except for the 3-bit register field. See
 * feedback_ido_arg_save_reg_pick.md — 7+ C variants can't flip it. */
void func_00001F78(char *a0) {
    char *new_node = (char*)func_00000000(0);
    *(char**)(new_node + 0x44) = *(char**)(*(char**)(a0 + 0x74) + 0x44);
    *(char**)(*(char**)(a0 + 0x74) + 0x44) = new_node;
    *(char**)(a0 + 0x74) = new_node;
    *(int*)(a0 + 0x78) += 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001F78);
#endif

void *func_00001FC8(char *a0, int a1) {
    void *p = *(void**)(a0 + 0x70);
    int i;
    for (i = 0; i < a1; i++) {
        p = *(void**)((char*)p + 0x44);
    }
    return p;
}

void *func_00002014(char *a0, int a1) {
    void *p = *(void**)(a0 + 0x70);
    int i;
    for (i = 0; i < a1; i++) {
        p = *(void**)((char*)p + 0x44);
    }
    return p;
}

void func_00002060(char *a0, int a1, int a2, int a3, int a4, int a5) {
    *(int*)(a0 + 0x80) = a1;
    *(int*)(a0 + 0x84) = a2;
    *(int*)(a0 + 0x88) = a4;
    *(int*)(a0 + 0x7C) = a5;
    *(int*)(a0 + 0x8C) = a3;
}

void func_00002080(int *a0) { *(int*)((char*)a0 + 0x104) = 0; }

#ifdef NON_MATCHING
/* append to count+entries list at 0x104 (count) + 0x108 (4-byte entries).
 * 6/7 insns match. Only diff: IDO schedules `sw t6,0x104(a0)` BEFORE
 * `addu t8,a0,t7`; target has addu first, sw count second. Same
 * scheduler-reorder pattern as func_000020AC (the sibling 8-byte-pair
 * variant). See feedback_ido_sw_before_addu_unreachable.md — two
 * independent instructions' ordering not reachable from C at -O2. */
void func_00002088(char *a0, int a1) {
    int idx = *(int*)(a0 + 0x104);
    *(int*)(a0 + 0x104) = idx + 1;
    *(int*)(a0 + idx * 4 + 0x108) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002088);
#endif

void func_000020A4(int *a0) { *(int*)((char*)a0 + 0xC0) = 0; }

#ifdef NON_MATCHING
/* append-pair to a count+entries list at offset 0xC0 (count) + 0xC4 (pairs of 8).
 * 10/11 insns match — only diff is IDO schedules `sw t9,0xC0(a0)` BEFORE
 * `addu t1,a0,t0`; target has addu first. Swap of two independent
 * instructions not reachable from C. See feedback_ido_sw_before_addu_unreachable.md
 * for the 10+ variants tried and the scheduler-priority explanation. */
void func_000020AC(int *a0, int a1, int a2) {
    int idx;
    *(int*)((char*)a0 + *(int*)((char*)a0 + 0xC0) * 8 + 0xC8) = a2;
    idx = *(int*)((char*)a0 + 0xC0);
    *(int*)((char*)a0 + 0xC0) = idx + 1;
    *(int*)((char*)a0 + idx * 8 + 0xC4) = a1;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000020AC);
#endif

void func_000020D8(char *a0, int a1) {
    int i;
    char *p;
    if (*(int*)(a0 + 0xC0) > 0) {
        i = 0;
        p = a0;
        do {
            func_00000000(a1, *(int*)(p + 0xC4), *(int*)(p + 0xC8));
            i++;
            p += 8;
        } while (i < *(int*)(a0 + 0xC0));
    }
}

/* func_0000214C: 2 insns (0x8) — `jr $ra; sw $a0, 0($sp)` (DELAY).
 * "Save-arg-to-stack and return" sentinel. The delay-slot store places
 * the caller's $a0 into the callee's sp+0, which is the caller's return
 * slot for $a0 in O32 — effectively a no-op-as-return that leaves $a0
 * as caller sees it. Not expressible as C (no body can emit just a
 * delay-slot sw without either a prologue or C-level side effect).
 * Listed explicitly in feedback_ido_unfilled_store_return.md. Keep
 * INCLUDE_ASM. */
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000214C);

void func_00002154(char *a0) {
    int scratch;
    func_00001C10(&scratch);
    func_00001C4C((float*)(a0 + 0x10));
}

void func_00002184(char *a0) {
    int scratch;
    func_00001C10(&scratch);
    func_00001C88(a0 + 0x10);
}

void func_000021B4(char *a0) {
    int scratch;
    func_00001C10(&scratch);
    func_00001CF8((int*)(a0 + 0x10));
}

void func_000021E4(char *a0) {
    int scratch;
    func_00001C10(&scratch);
    func_00001D34((Quad4*)(a0 + 0x10));
}

void func_00002214(char *a0) {
    int scratch;
    func_00001C10(&scratch);
    func_00001C10((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002244);

void func_000022E0(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000231C(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_00002358();
void func_00002358(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_000023C8(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 93.8% match. IDO's list scheduler reorders: target emits
 *   sw t0,0x30(a0); lw t1,0x2C(sp)(s5-load); zero-stores; sw t2,0x48(a0)
 *   (0x2710 in $t2); sw t1,0x34(a0)
 * IDO produces instead:
 *   zero-stores; sw t1,0x48(a0) (0x2710 in $t1); sw t0,0x30(a0); lw t2,0x2C(sp);
 *   sw t2,0x34(a0)
 * i.e. IDO pushes the s4 store down past the zero-stores because stack-loaded
 * t0 has more pending dependency than $zero. Const 0x2710 register flips t2→t1
 * as a knock-on because the s5-load slot is gone. Tried: hoisting s5 into a
 * named local before zero-stores (no effect — const-prop), and reading order
 * variants. Same class as feedback_ido_sw_before_addu_unreachable.md — two
 * independent instructions' ordering is not reachable from C source. */
extern char D_0000731C;
int *func_00002420(int *a0, int a1, int a2, int a3, int s4, int s5) {
    if (a0 == 0) {
        a0 = (int*)func_00000000(0x50);
        if (a0 == 0) goto end;
    }
    func_00000000(a0, &D_0000731C);
    *(int*)((char*)a0 + 0x28) = (int)&D_00000000;
    *(int*)((char*)a0 + 0x38) = a1;
    *(int*)((char*)a0 + 0x40) = a2;
    *(int*)((char*)a0 + 0x2C) = a3;
    *(int*)((char*)a0 + 0x30) = s4;
    *(int*)((char*)a0 + 0x3C) = 0;
    *(int*)((char*)a0 + 0x44) = 0;
    *(int*)((char*)a0 + 0x48) = 0x2710;
    *(int*)((char*)a0 + 0x4C) = 0;
    *(int*)((char*)a0 + 0x34) = s5;
end:
    return a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002420);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000024B8);

void func_00002774(char *a0, int a1) {
    if (*(int*)(a0 + 0x18) & 8) {
        char *p;
        *(int*)(a0 + 0x3C) = a1;
        *(int*)(*(char**)(a0 + 0x2C) + 0x70) = ((int*)a0)[a1 + 12];
        p = *(char**)(*(char**)(a0 + 0x2C) + 0x70) + 0x134;
        *(float*)(p + 8) = 0.0f;
        *(float*)(p + 4) = 0.0f;
        *(float*)p = 0.0f;
    }
}

void func_000027C0(char *a0, int *a1) {
    int msg_type = *a1;
    int *flags = (int*)(a0 + 0x18);
    if (msg_type == 0x3ED) {
        *flags &= ~0x8;
    }
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000027E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002C94);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002DA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002F90);

void func_000031B8(int a0) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000031C0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000034E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00003638);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00003734);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000038C0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000039D8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00003B78);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00003D3C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00003F00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000411C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000043D4);

void func_0000462C(char *a0) {
    int scratch;
    func_000022E0(&scratch);
    func_0000231C((int*)(a0 + 0x10));
}

void func_0000465C(char *a0) {
    int scratch;
    func_000022E0(&scratch);
    func_00002358((int*)(a0 + 0x10));
}

void func_0000468C(char *a0) {
    int scratch;
    func_000022E0(&scratch);
    func_000023C8((int*)(a0 + 0x10));
}

void func_000046BC(char *a0) {
    int scratch;
    func_000022E0(&scratch);
    func_000022E0((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000046EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000477C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000485C);

void func_00004914(char *a0, int a1, char *a2) {
    *(float*)(a0 + 0x60) = *(float*)(a2 + 0x30);
    *(float*)(a0 + 0x64) = *(float*)(a2 + 0x34);
    *(float*)(a0 + 0x68) = *(float*)(a2 + 0x38);
    *(int*)(a0 + 0x158) = a1;
    *(float*)(a0 + 0x64) += 100.0f;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00004948);

void func_00004FF0(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000502C(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005068);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000050A0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005124);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000051D4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005284);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005334);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000053E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000054A0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000054D8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000553C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000055A0);

void func_00005EF8(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005F34);

void func_00006100(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000613C(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

extern void func_00006194();
void func_00006194(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

#ifdef NON_MATCHING
/* 77%: tiny `f(void) { func_00000000(&D_0); }` wrapper. Target insn
 * order `lui a0; sw ra; jal` — IDO emits `sw ra; lui a0; jal`
 * (insn 4 and 8 swapped). Documented as unreachable-from-C ceiling
 * in feedback_ido_o2_tiny_wrapper_unflippable.md. */
void func_00006204(void) {
    func_00000000(&D_00000000);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006204);
#endif

void func_00006228(char *a0) {
    func_0000502C((int*)(a0 + 0x3C));
    func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006254);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000063B4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006734);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006808);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007150);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007204);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007288);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007328);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000074E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007620);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000076F4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000077D0);

void func_00007A48(char *a0) {
    int scratch;
    func_00004FF0(&scratch);
    func_00006100((int*)(a0 + 0x10));
}

void func_00007A78(char *a0) {
    int scratch;
    func_00004FF0(&scratch);
    func_0000613C((int*)(a0 + 0x10));
}

void func_00007AA8(char *a0) {
    int scratch;
    func_00004FF0(&scratch);
    func_00004FF0((int*)(a0 + 0x10));
}

void func_00007AD8(char *a0) {
    int scratch;
    func_00004FF0(&scratch);
    func_00006194((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007B08);

void func_00007B98(char *a0) {
    int scratch;
    func_00004FF0(&scratch);
    func_0000502C((int*)(a0 + 0x10));
}

void func_00007BC8(char *a0) {
    func_00004FF0((int*)(a0 + 0x3C));
    func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007BF4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007C74);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007D04);

void func_00007E50(int *a0) {
    *(int*)((char*)a0 + 0x68) = 0;
    func_00000000(a0);
}

extern int D_func_00007E70_a;
extern int D_func_00007E70_b;
void func_00007E70(char *a0) {
    D_func_00007E70_a = 0;
    func_00000000(a0);
    if (D_func_00007E70_b != 0) {
        int counter = *(int*)(a0 + 0x68) + 1;
        *(int*)(a0 + 0x68) = counter;
        if (counter == 1) {
            func_00000000();
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007EC8);

void func_00008078(char *a0) {
    func_00000000(a0 + 0x3C, 0);
    func_00000000(a0 + 0x74);
    func_00000000(a0);
}

void func_000080B4(char *a0) {
    func_00000000((int*)(a0 + 0x3C));
    func_00000000((int*)(a0 + 0x74));
    func_00000000(a0);
}

void func_000080EC(char *a0) {
    func_00000000((int*)(a0 + 0x3C));
    func_00000000((int*)(a0 + 0x74));
    func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008124);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000082F8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000083D0);

void func_00008448(char *a0) {
    func_00000000((int*)(a0 + 0x3C));
    func_00000000(a0);
}

void func_00008474(char *a0) {
    func_00000000((int*)(a0 + 0x3C));
    func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000084A0);

void func_00008664(char *a0, int *a1) {
    func_00000000(a0);
    if (*a1 == 7 || *a1 == 19) {
        *(float*)(a0 + 0xA0) = *(float*)(a0 + 0x5C);
        *(float*)(a0 + 0xA4) = *(float*)(a0 + 0x60);
        *(float*)(a0 + 0xA8) = *(float*)(a0 + 0x64);
    }
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000086C0);

extern char D_func_00008744_arg1;
extern char D_func_00008744_arg2;
void func_00008744(char *a0) {
    int arg = *(int*)(a0 + 0xC);
    func_00000000(&D_func_00008744_arg1, arg, 0);
    func_00000000(a0 + 0x4C, 0);
    func_00000000(a0 + 0x5C);
    func_00000000(&D_func_00008744_arg2);
    func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000087A4);

extern char *D_00000130;
int func_00008920(int a0) {
    char *p = D_00000130;
    while (p != 0) {
        if (func_00000000(*(int*)p, a0) == 0) {
            return 1;
        }
        p = *(char**)(p + 4);
    }
    return 0;
}

int func_00008980(int arg0) {
    if (func_00000000(arg0) == 0) {
        func_00000000(&D_00000000, arg0);
        return 1;
    }
    return 0;
}

void func_000089C0(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_000089FC(short *dst) {
    short buf[4];
    func_00000000(&D_00000000, buf, 2);
    *dst = buf[0];
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008A38);

void func_00008A40(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_00008A7C();
void func_00008A7C(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_00008AEC(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008B44);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008BD4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008F18);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008FA8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000090CC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000B1B4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000B49C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000B520);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000B75C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000BF8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000C234);

void func_0000CACC(char *a0) {
    *(int*)(a0 + 0xA14) = 0xF4240;
    *(int*)(a0 + 0xA58) = *(int*)(a0 + 0xA58) ^ 0x100;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000CAE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000CCE0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000CFA0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000D440);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000D900);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000DDC4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000DDCC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000DF04);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E014);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E124);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E270);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E2D0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E4DC);

void func_0000E588(char *a0) {
    int scratch;
    func_000089C0(&scratch);
    func_00008A40((int*)(a0 + 0x10));
}

void func_0000E5B8(char *a0) {
    int scratch;
    func_000089C0(&scratch);
    func_00008A7C((int*)(a0 + 0x10));
}

float func_0000E5E8(char *a0) { return *(float*)(a0 + 0x198); }

void func_0000E5F0(char *a0) {
    func_00000000(a0 + 0x108);
}

void func_0000E610(char *a0) {
    func_00000000(a0 + 0x108);
}

void func_0000E630(char *a0) {
    int scratch;
    func_000089C0(&scratch);
    func_00008AEC((int*)(a0 + 0x10));
}

void func_0000E660(char *a0) {
    int scratch;
    func_000089C0(&scratch);
    func_000089C0((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E690);

void func_0000E720(char *a0) {
    func_00000000(a0 + 0x2C);
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E740);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E800);

void func_0000E8BC(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000E8F8(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_0000E934();
void func_0000E934(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_0000E9A4(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 83 %: structure correct. Target has `lui a0, 0x0` before `sw ra, 20(sp)`
 * in the prologue; IDO puts `sw ra` first. Same scheduling blocker as
 * feedback_ido_o2_tiny_wrapper_unflippable. */
extern char D_func_0000E9FC_arg1;
extern char D_func_0000E9FC_arg2;
extern int D_00000028;
void func_0000E9FC(void) {
    func_00000000(&D_func_0000E9FC_arg1);
    D_00000028 = (int)&D_func_0000E9FC_arg2;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E9FC);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EA2C);

extern int D_00000190;
void func_0000EAF8(int a0) {
    func_00000000(D_00000190, 3, 0);
}

void func_0000EB28(char *a0) {
    int scratch;
    func_0000E8BC(&scratch);
    func_0000E8F8((int*)(a0 + 0x10));
}

void func_0000EB58(char *a0) {
    int scratch;
    func_0000E8BC(&scratch);
    func_0000E934((int*)(a0 + 0x10));
}

void func_0000EB88(char *a0) {
    int scratch;
    func_0000E8BC(&scratch);
    func_0000E9A4((int*)(a0 + 0x10));
}

void func_0000EBB8(char *a0) {
    int scratch;
    func_0000E8BC(&scratch);
    func_0000E8BC((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EBE8);

void func_0000EC80(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000ECBC(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_0000ECF8();
void func_0000ECF8(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_0000ED68(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void func_0000EDC0(int a0, int a1) {}

void func_0000EDCC(char *a0) {
    int scratch;
    func_0000EC80(&scratch);
    func_0000ECBC((int*)(a0 + 0x10));
}

void func_0000EDFC(char *a0) {
    int scratch;
    func_0000EC80(&scratch);
    func_0000ECF8((int*)(a0 + 0x10));
}

void func_0000EE2C(char *a0) {
    int scratch;
    func_0000EC80(&scratch);
    func_0000ED68((int*)(a0 + 0x10));
}

void func_0000EE5C(char *a0) {
    int scratch;
    func_0000EC80(&scratch);
    func_0000EC80((int*)(a0 + 0x10));
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EE8C);

void func_0000EF20(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000EF5C(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_0000EF98();
void func_0000EF98(Vec3 *dst) {
    int pad_top[1];
    Tri3i raw;
    int pad_mid[2];
    Tri3i tmp;
    int pad_bot[2];
    func_00000000(&D_00000000, &raw, 12);
    tmp = raw;
    dst->x = *(float*)&tmp.a;
    dst->y = *(float*)&tmp.b;
    dst->z = *(float*)&tmp.c;
}

void func_0000F008(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

void func_0000F060(char *a0) {
    int scratch;
    func_0000EF20(&scratch);
    func_0000EF5C((int*)(a0 + 0x10));
}

void func_0000F090(char *a0) {
    int scratch;
    func_0000EF20(&scratch);
    func_0000EF98((int*)(a0 + 0x10));
}

void func_0000F0C0(char *a0) {
    int scratch;
    func_0000EF20(&scratch);
    func_0000F008((int*)(a0 + 0x10));
}

void func_0000F0F0(char *a0) {
    int scratch;
    func_0000EF20(&scratch);
    func_0000EF20((int*)(a0 + 0x10));
}

void func_0000F120(int *dst) {
    int buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

void func_0000F15C(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

#ifdef NON_MATCHING
/* 80 %: structurally exact composite (int reader + Quad4 reader) per the
 * cross-USO template memo. Function size is 0x30 but target symbol extends
 * to 0x3C with 3 trailing alignment nops — per feedback_function_trailing_nop_padding,
 * these nops are assembler-inserted and not reproducible from C. */
void func_0000F1B4(char *a0) {
    int scratch;
    func_0000F120(&scratch);
    func_0000F15C((Quad4*)(a0 + 0x10));
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F1B4);
#endif

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F1F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F23C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F288);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F2EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F390);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F3D4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F404);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F434);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F4CC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F564);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F5BC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F614);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F66C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F6C4);


