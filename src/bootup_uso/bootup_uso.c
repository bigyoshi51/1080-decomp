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

extern void func_00000080(void *dst);
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000080);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000031C);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000A9C);

void func_00000B14(int **a0, int a1) {
    int *v0 = *a0;
    if (v0 != 0) {
        ((char*)v0)[0x1D] = (char)a1;
    }
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00000B2C);

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

extern void func_00001C10();
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001C10);

void func_00001C4C(float *dst) {
    float buf[2];
    func_00000000(&D_00000000, buf, 4);
    *dst = buf[0];
}

extern void func_00001C88();
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001C88);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001D8C);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001F78);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00001FC8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002014);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002060);

void func_00002080(int *a0) { *(int*)((char*)a0 + 0x104) = 0; }

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002088);

void func_000020A4(int *a0) { *(int*)((char*)a0 + 0xC0) = 0; }

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000020AC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000020D8);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002358);

void func_000023C8(Quad4 *dst) {
    Quad4 buf;
    func_00000000(&D_00000000, &buf, 16);
    *dst = buf;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002420);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000024B8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00002774);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000031B8);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000462C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000465C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000468C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000046BC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000046EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000477C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000485C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00004914);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00004948);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00004FF0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000502C);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005EF8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00005F34);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006100);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000613C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006194);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006204);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00006228);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007A48);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007A78);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007AA8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007AD8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007B08);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007B98);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007BC8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007BF4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007C74);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007D04);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007E50);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007E70);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00007EC8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008078);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000080B4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000080EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008124);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000082F8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000083D0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008448);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008474);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000084A0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008664);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000086C0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008744);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000087A4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008920);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008980);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000089C0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000089FC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008A38);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008A40);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008A7C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00008AEC);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E588);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E5B8);

float func_0000E5E8(char *a0) { return *(float*)(a0 + 0x198); }

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E5F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E610);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E630);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E660);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E690);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E720);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E740);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E800);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E8BC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E8F8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E934);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E9A4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000E9FC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EA2C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EAF8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EB28);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EB58);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EB88);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EBB8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EBE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EC80);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000ECBC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000ECF8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000ED68);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EDC0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EDCC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EDFC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EE2C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EE5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EE8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EF20);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EF5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000EF98);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F008);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F060);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F090);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F0C0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F0F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F120);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F15C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F1B4);

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

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F76C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F7D0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F7F4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F808);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F81C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F954);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F9E8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FAE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FBCC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FC28);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FD4C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEA0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000FEE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000100F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001016C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001024C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010260);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102A4);

void func_000102E8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000102F0);

void func_00010308(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010310);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010324);

void func_00010344(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001034C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010540);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010A9C);

void func_00010AA8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010AB0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010B6C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010C8C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00010FEC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000116C8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000117FC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000118E4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001195C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011A34);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011AB4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011B5C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011BF0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011C70);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011CD8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D40);

void func_00011D70(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011D78);

void func_00011DB4(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011DBC);

void func_00011DF8(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011ED4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00011FA8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001207C);

void func_00012088(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012090);

void func_000120A0(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000120A8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012110);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012150);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012188);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012244);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000122C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000123F0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012458);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000124C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001252C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012598);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012600);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001266C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000127CC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012818);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000128AC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000129A0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012AC4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012B7C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012BF8);

void func_00012C08(void) {
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012C10);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012C64);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012D64);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012DA4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012DB8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00012E00);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001304C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013924);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013980);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000139B0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013B20);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013C70);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013CAC);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013CE8);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00013D40);

void func_00013FE0(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x44) = a1;
    *(int*)(a0 + 0x5C) = a2;
}

void func_00013FEC(char *a0, int a1, int a2, int a3, int arg5) {
    *(int*)(a0 + 0x74) = a1;
    *(int*)(a0 + 0x8C) = a2;
    *(int*)(a0 + 0xA4) = a3;
    *(int*)(a0 + 0xBC) = arg5;
}

void func_00014004(char *a0, int a1, int a2) {
    *(int*)(a0 + 0x104) = a1;
    *(int*)(a0 + 0x108) = a2;
}

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014010);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000140C4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014228);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0001438C);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144B4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144E0);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000144F4);

INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_00014598);
