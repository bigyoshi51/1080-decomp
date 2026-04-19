#include "common.h"

typedef struct { int a, b, c, d; } Quad4;

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000000);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000001CC);

extern int gl_func_00000000();
int gl_func_00000308(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000338);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000400);

extern int gl_func_00000000();
int gl_func_00000574(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000005A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000005EC);

extern int gl_func_00000000();
int gl_func_00000760(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CB58;
int gl_func_00000790(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CB58, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000007BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000009B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000A8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000BAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000D5C);

extern int gl_func_00000000();
int gl_func_00000E74(char *a0) {
    gl_func_00000000(a0 + 0x10C);
    return gl_func_00000000(a0 + 0x124);
}

extern int gl_func_00000000();
extern char gl_ref_0000CBD8;
int gl_func_00000EA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xE4, &gl_ref_0000CBD8, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000ED0);

extern int gl_func_00000000();
extern char gl_ref_0000CBF8;
int gl_func_00000FA4(char *a0, int arg1) {
    return gl_func_00000000(a0 + 0xB4, &gl_ref_0000CBF8, arg1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00000FD0);

extern int gl_func_00000000();
int gl_func_00001114(char *a0) {
    return gl_func_00000000(a0 + 0x10C);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001134);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000011A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000127C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000012B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000135C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000015FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001798);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001820);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00001C54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000237C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000024C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000025A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002840);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000029F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00002B94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003138);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000032B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000033E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003430);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000038F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003B1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003C0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00003DB8);

extern int gl_ref_00013C70();
int gl_func_0000405C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013C70(a0 + 0x10);
}

extern int gl_ref_00013C70();
extern int gl_ref_00013CAC();
int gl_func_0000408C(char *a0) {
    int scratch;
    gl_ref_00013C70(&scratch);
    return gl_ref_00013CAC(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000040BC);

extern int gl_func_00000000();
void gl_func_00004104(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004140(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00004198(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000041D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00004244);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006900);

extern int gl_func_00000000();
int gl_func_00006A8C(char *a0, int a1) {
    *(int*)(a0 + 0x4F0) = a1;
    return gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006AAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006B80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006C38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006CDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006DC8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006DF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006E78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006EE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006F60);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00006F90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007010);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000070FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007344);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000076F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00007FF4);

#ifdef NON_MATCHING
/* NON_MATCHING: temp uses t6 not v0 */
#ifdef NON_MATCHING
/* NON_MATCHING: temp uses t6 instead of v0 (inline deref uses v0 for
 * multi-use; this single-compare pattern picks t-reg). */
extern int gl_func_00000000();
void gl_func_0000836C(int a0, int *a1) {
    if (*a1 == 9) {
        gl_func_00000000(a0, a1);
    }
    gl_func_00000000(a0, a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000836C);
#endif
#else
#ifdef NON_MATCHING
/* NON_MATCHING: temp uses t6 instead of v0 (inline deref uses v0 for
 * multi-use; this single-compare pattern picks t-reg). */
extern int gl_func_00000000();
void gl_func_0000836C(int a0, int *a1) {
    if (*a1 == 9) {
        gl_func_00000000(a0, a1);
    }
    gl_func_00000000(a0, a1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000836C);
#endif
#endif

extern int gl_func_00000000();
int gl_func_000083AC(char *a0) {
    return gl_func_00000000(a0 + 0x50);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000083CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008510);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000085B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008674);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000871C);

extern int gl_ref_00018770();
extern int gl_ref_000187AC();
int gl_func_000087F4(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_000187AC(a0 + 0x10);
}

extern int gl_ref_00018770();
int gl_func_00008824(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018770(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018804();
int gl_func_00008854(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018804(a0 + 0x10);
}

extern int gl_ref_00018770();
extern int gl_ref_00018840();
int gl_func_00008884(char *a0) {
    int scratch;
    gl_ref_00018770(&scratch);
    return gl_ref_00018840(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000088B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008944);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008990);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000089F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008A40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008AE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008C3C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008DAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008E48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00008FFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009204);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000092F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000093DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000949C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000094DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000951C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000955C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000959C);

extern int gl_func_00000000();
void gl_func_00009674(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_000096B0(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000096EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000975C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009DB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009EBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00009FA8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A00C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A0CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A130);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A1C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A2B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A4D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A670);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A768);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A7B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A990);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000A9F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AA7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AAEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AB70);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ABBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000ACBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AD9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000AFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B0A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B190);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B208);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B290);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B310);

extern int gl_func_00000000();
int gl_func_0000B3B0() {
    int r = gl_func_00000000();
    if (r != 0) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B3DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B450);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B4A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B560);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B5AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B638);

extern int gl_func_00000000();
void gl_func_0000B6AC(int *a0) {
    gl_func_00000000(a0[1]);
    gl_func_00000000(a0);
}

extern int gl_func_00000000();
void gl_func_0000B6D8(int *a0) {
    gl_func_00000000(a0[2]);
    gl_func_00000000(a0[4], a0[2]);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B710);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B77C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B868);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B8E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000B958);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BA6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BB14);

extern int gl_func_00000000();
int gl_func_0000BBB0(int a0) {
    int tmp = gl_func_00000000(24);
    gl_func_00000000(a0, tmp, 504, 24);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BBF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BC84);

extern int gl_func_00000000();
void gl_func_0000BD78(int a0) {
    int pad_arr[5];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BDA8(int a0) {
    int tmp = gl_func_00000000(384);
    gl_func_00000000(a0, tmp, 8, 384);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BDE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000BEB8);

extern int gl_func_00000000();
void gl_func_0000BFAC(int a0) {
    int pad_arr[95];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

extern int gl_func_00000000();
int gl_func_0000BFDC(int a0) {
    int tmp = gl_func_00000000(96);
    gl_func_00000000(a0, tmp, 400, 96);
    return tmp;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C01C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C0EC);

extern int gl_func_00000000();
void gl_func_0000C1E0(int a0) {
    int pad_arr[23];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C210);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C28C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C378);

extern int gl_func_00000000();
void gl_func_0000C46C(int a0) {
    int pad_arr[3];
    int scratch;
    gl_func_00000000(&scratch);
    gl_func_00000000(a0, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C49C);

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD1C();
int gl_func_0000C4F0(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD1C(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DD58();
int gl_func_0000C520(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DD58(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
extern int gl_ref_0001DDC8();
int gl_func_0000C550(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DDC8(a0 + 0x10);
}

extern int gl_ref_0001DCE0();
int gl_func_0000C580(char *a0) {
    int scratch;
    gl_ref_0001DCE0(&scratch);
    return gl_ref_0001DCE0(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C5B0);

extern int gl_func_00000000();
void gl_func_0000C644(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C680(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0000C6BC(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C714);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C784);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000C8B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CB9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CBFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CD80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CDDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000CE38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D0D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D318);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D418);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D548);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D6A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D7B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D8E0);

#ifdef NON_MATCHING
/* NON_MATCHING: temp uses a1 not a3 */
extern int gl_func_00000000();
void gl_func_0000D9B8(int *a0) {
    int *p = (int*)a0[0x1B];
    if (p != 0) gl_func_00000000(p);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9B8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000D9E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DB34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DB80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DC90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DD44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DDE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DE30);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DE80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DED0);

#ifdef NON_MATCHING
/* NON_MATCHING: IDO spills a0/a1 defensively; expected skips those spills */
extern int gl_func_00000000();
void gl_func_0000DF20(int a0, int a1, float a2) {
    int rv = gl_func_00000000();
    if (rv != 0) {
        *(float*)(rv + 0x10) = a2;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DF20);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DF4C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DF8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000DFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E05C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E118);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E1DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E230);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E2A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E368);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E4A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E53C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E5D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E66C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E79C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E84C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E910);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000E9C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000EAAC);

extern int gl_ref_00020CB0();
int gl_func_0000EB38(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CB0(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020CEC();
int gl_func_0000EB68(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020CEC(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D28();
int gl_func_0000EB98(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D28(a0 + 0x10);
}

extern int gl_ref_00020CB0();
extern int gl_ref_00020D80();
int gl_func_0000EBC8(char *a0) {
    int scratch;
    gl_ref_00020CB0(&scratch);
    return gl_ref_00020D80(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0000EBF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CA10);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CD64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001CFDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D0AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D200);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D4C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001D870);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DA7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DB88);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001DCB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001E134);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001EE78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001EF20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001F248);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001F3C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FAE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FBD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FC50);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FC78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FCD0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FD20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FD5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FD98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FEC8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FF34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0001FFB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002003C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020100);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000201B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000208BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020914);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020A28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00020ED0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002119C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021498);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021D84);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021E08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021E58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021EA8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00021F40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000221D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000223DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022464);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022760);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022A9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022D68);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022DE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022E58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00022FC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023078);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000230D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000231B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023284);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000232E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000233E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002349C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023548);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023598);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000235E4);

extern int gl_ref_00038174();
extern int gl_ref_00037F80();
void gl_func_0002372C(int a0) {
    int r = gl_ref_00038174(0, a0);
    int scratch;
    gl_ref_00037F80(0, r, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023760);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023838);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023914);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023B08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023B44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023BDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023E60);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00023FA4);

extern int gl_ref_00037F80();
int gl_func_00024080(int a0, int a1) {
    int scratch;
    return gl_ref_00037F80(a0, a1, &scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000240A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024330);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024378);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002495C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024B28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024B94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024C08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024D90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024E34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00024F30);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025044);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000250C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025320);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025504);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000258CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025AC8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00025C54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000260B4);

extern int gl_ref_0003A880();
int gl_func_000261F4() {
    return gl_ref_0003A880();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026214);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026790);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026B48);

extern int gl_ref_0003B244();
void gl_func_00026C24(int a0, int a1) {
    gl_ref_0003B244(a0, &a1);
}

extern int gl_ref_0003B244();
void gl_func_00026C48(int a0, int a1) {
    gl_ref_0003B244(a0, &a1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026C6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026C9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026CF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00026D64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000270FC);

extern int gl_func_00000000();
int gl_func_00027160() {
    return gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027180);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000271D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002722C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000272C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002737C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027548);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002758C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000275C8);

extern int gl_func_0003B1AC();
int gl_func_000276E4() {
    return gl_func_0003B1AC();
}

extern int gl_func_00000000();
void gl_func_00027704(int a0, int a1) {
    int r = gl_func_00000000(1);
    gl_func_00000000(a0, a1);
    gl_func_00000000(r);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027744);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027804);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027D00);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00027E24);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028358);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002842C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028510);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028604);

extern int gl_ref_0003CC70();
int gl_func_0002886C(int a0) {
    return gl_ref_0003CC70(a0, 6);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002888C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000289B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028A18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028A68);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028B0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028C6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028E94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00028FCC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002902C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029078);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000290C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000291C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029494);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002978C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029978);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00029B6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A014);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A080);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A260);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A3AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A4D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A50C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A55C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A6C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A740);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A7D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002A904);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AA30);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AB34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002ABC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002AD1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002B09C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002B5F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BA38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BAAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002BB7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002C7A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002CF70);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D014);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D064);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D130);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D224);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D2F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D37C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D620);

extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002D670() {
    gl_func_00000000((void*)0xF2000000, 0);
    gl_func_00000000(0x91);
    D_00000000 = 0;
}

extern int gl_func_00000000();
extern int D_00000000;
void gl_func_0002D6A0() {
    gl_func_00000000((void*)0xF2000000, 0);
    D_00000000 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D6C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D710);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D74C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D788);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D7D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D838);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D870);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D8A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D8E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002D910);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DC7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DCF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DD58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DD90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DDF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DE24);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DEA4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DED0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF00);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF38);

#ifdef NON_MATCHING
/* NON_MATCHING: IDO cannot emit direct mfc1 from C; stack roundtrip instead */
extern int gl_func_00000000();
void gl_func_0002DF68(int a0, float a2) {
    gl_func_00000000(0x04000000 | ((a0 & 0xFF) << 8), *(int*)&a2);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF68);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002DF98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002E06C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002E1C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002E24C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002E354);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F584);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F638);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F72C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F8A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F934);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002F9D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002FA90);

extern int gl_func_00000000();
void gl_func_0002FB10(int a0) {
    int v = a0 == 0 ? 1 : 5;
    int x = (v & 0xFF) << 8;
    x |= 0x06000000;
    x |= 1;
    gl_func_00000000(x, -1);
}

extern int gl_func_00000000();
int gl_func_0002FB54(int a0) {
    return gl_func_00000000(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0002FB74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030504);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030564);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030598);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000305CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003061C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000307B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000308C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000309B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030A20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00030AF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031334);

extern int gl_func_00000000();
int gl_func_00031520() {
    return gl_func_00000000();
}

extern int gl_func_00000000();
int gl_func_00031540() {
    return gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031560);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000315C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031608);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000316CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031710);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031898);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003190C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031A74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031D7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031DA4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00031DD8);

extern int gl_func_00000000();
void gl_func_00032D84(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00032DC0(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00032E18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033094);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033228);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000332B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033338);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000333B4);

#ifdef NON_MATCHING
/* NON_MATCHING: sw ra scheduled wrong vs lui a0 */
extern int gl_func_00000000();
int gl_func_000333F4(int a0) {
    return gl_func_00000000(gl_func_00000000, a0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000333F4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003341C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003344C);

extern int gl_func_00000000();
extern char gl_ref_0001E250;
void gl_func_000334B0(int a0, int a1, int a2) {
    gl_func_00000000(&gl_ref_0001E250, a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000334E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000337AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033880);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003395C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000339B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033A20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033A8C);

extern int gl_func_00000000();
int gl_func_00033AE4(int a0, int a1, int a2) {{
    int r = gl_func_00000000(a0, a1, a2);
    gl_func_00000000(r, a0, a1, a2);
    return r;
}}

extern int gl_func_00000000();
int gl_func_00033B28(int a0, int a1, int a2) {{
    int r = gl_func_00000000(a0, a1, a2);
    gl_func_00000000(r, a0, a1, a2);
    return r;
}}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033B6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033BE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00033EB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034188);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034240);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034458);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034548);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034684);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000346F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034810);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034890);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000349E8);

extern int gl_func_00000000();
extern char gl_ref_0001E468;
int gl_func_00034A54() {
    return gl_func_00000000(&gl_ref_0001E468);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034A78);

extern int gl_func_00000000();
void gl_func_00034B64(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0);
    gl_func_00000000(gl_func_00000000);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034B98);

extern int gl_func_00000000();
void gl_func_00034C14() {
    int r = gl_func_00000000(1);
    gl_func_00000000();
    gl_func_00000000(r);
}

extern int gl_func_00000000();
void gl_func_00034C44(int a0, int a1) {
    int r = gl_func_00000000(1);
    gl_func_00000000();
    gl_func_00000000(r);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034C7C);

extern int gl_func_00000000();
int gl_func_00034DBC(int a0) {
    gl_func_00000000(gl_func_00000000);
    return 1;
}

extern int gl_func_00000000();
void gl_func_00034DE8(int a0) {
    gl_func_00000000(gl_func_00000000);
}

extern int gl_func_00000000();
int gl_func_00034E10(int a0) {
    return gl_func_00000000(gl_func_00000000) == 2;
}

extern int gl_func_00000000();
void gl_func_00034E3C(int a0) {
    gl_func_00000000(gl_func_00000000);
}

extern int gl_func_00000000();
void gl_func_00034E64(int a0) {
    gl_func_00000000(gl_func_00000000);
}

extern int gl_func_00000000();
void gl_func_00034E8C(int a0) {
    gl_func_00000000(gl_func_00000000);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00034EB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035164);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035188);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000351EC);

extern int gl_func_00000000();
void gl_func_0003523C(int a0, int a1, int a2) {
    gl_func_00000000(gl_func_00000000, a1, a1 + a2);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035268);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035338);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035370);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035440);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000355A0);

extern int gl_func_00000000();
void gl_func_00035624(int a0, int a1) {
    gl_func_00000000(a1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035648);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000356FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035834);

extern int gl_func_00000000();
extern char gl_ref_0001E660;
int gl_func_00035894(int *a0) {
    if (a0[1] == 0) {
        return gl_func_00000000(gl_func_00000000);
    }
    gl_func_00000000(&gl_ref_0001E660);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000358DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003593C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000359C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035A18);

extern int gl_func_00000000();
void gl_func_00035AA4(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00035AE0(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035B1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035C6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035DAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035E6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00035FD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003604C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036088);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036224);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036694);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003695C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036A48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036B9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036C08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036E74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00036F0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000372D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037348);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003783C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003787C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000378D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037938);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037A9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037AF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037BEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037C70);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037CE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037D48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037DA8);

extern int gl_func_00000000();
void gl_func_00037E04(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037E40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037F58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00037FAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003800C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038108);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000381F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003829C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038360);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038598);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003863C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038728);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038830);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038964);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038A28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038BB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038C04);

extern int gl_func_00000000();
void gl_func_00038C70(int a0, int a1, int a2) {
    int args[2];
    int pad[4];
    args[0] = a1;
    args[1] = a2;
    gl_func_00000000(a0, args);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038C98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038D64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038DC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00038FE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039094);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000393B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039624);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000396FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039960);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039990);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039A04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039A9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039B0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039B58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039C8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039E24);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039EE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00039F7C);

extern int gl_ref_0004C470();
extern int gl_ref_0004C4AC();
int gl_func_0003A014(char *a0) {
    int scratch;
    gl_ref_0004C470(&scratch);
    return gl_ref_0004C4AC(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003A044);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003A0C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003A58C);

extern int gl_func_00000000();
void gl_func_0003A9AC(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003A9E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003AC5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003AE58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003AFD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003B01C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003B1AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003B2EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003B6A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003B9C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003BE1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003C43C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003C814);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003C86C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003CAA0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003CB2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003CB6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003CBB4);

extern int gl_ref_0004F018();
extern int gl_ref_0004F054();
int gl_func_0003CF94(char *a0) {
    int scratch;
    gl_ref_0004F018(&scratch);
    return gl_ref_0004F054(a0 + 0x10);
}

extern int gl_func_00000000();
void gl_func_0003CFC4(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0003D000(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

extern int gl_func_00000000();
void gl_func_0003D034(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

extern int gl_func_00000000();
void gl_func_0003D068(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

extern int gl_func_00000000();
void gl_func_0003D09C(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0003D0D8(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0003D114(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D16C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D228);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D2C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D3C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D48C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D550);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D5BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D620);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D68C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D71C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D7F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D8A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D914);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003D9AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DA18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DB3C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DBF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DC90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DD28);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DDC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DE4C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003DF5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E0F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E1B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E238);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E2B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E39C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E54C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E594);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E5E0);

extern int gl_func_00000000();
extern char gl_ref_0001F338;
void gl_func_0003E840(int a0) {
    gl_func_00000000(&gl_ref_0001F338);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E868);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E904);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E968);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003E9C8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EA98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EAE0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EB3C);

extern int gl_ref_00051744();
extern int gl_ref_00051780();
int gl_func_0003EBAC(char *a0) {
    int scratch;
    gl_ref_00051744(&scratch);
    return gl_ref_00051780(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EBDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EC5C);

extern int gl_func_00000000();
int gl_func_0003ECEC(int a0) {
    return gl_func_00000000(gl_func_00000000, a0, 0xA0);
}

extern int gl_func_00000000();
int gl_func_0003ED18(int a0) {
    return gl_func_00000000(gl_func_00000000, a0, 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003ED44);

extern int gl_func_00000000();
void gl_func_0003ED8C(int *a0) {
    a0[1] = 0;
    a0[0] &= ~1;
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EDBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EE1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EE50);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EEC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EF2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EF78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003EFC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F008);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F044);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F0A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F0E8);

extern int gl_func_00000000();
void gl_func_0003F12C(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0x31;
    gl_func_00000000(&scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F158);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F198);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F1D4);

extern int gl_func_00000000();
void gl_func_0003F218(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0x2E;
    gl_func_00000000(&scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F244);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F278);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F2B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F308);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F350);

extern int gl_func_00000000();
void gl_func_0003F3A4(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0x13;
    gl_func_00000000(&scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F3D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F410);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F444);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F4F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F5B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F60C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F66C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F6CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F730);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F7A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F82C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F880);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F8B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F8E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F96C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003F9C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FA54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FAA8);

extern int gl_func_00000000();
void gl_func_0003FAE0(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0x20;
    gl_func_00000000(&scratch);
}

extern int gl_func_00000000();
void gl_func_0003FB0C(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0x27;
    gl_func_00000000(&scratch);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FB38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FB6C);

extern int gl_func_00000000();
void gl_func_0003FC00(int a0) {
    char pad[0x98];
    int pad2, scratch;
    scratch = 0xB;
    gl_func_00000000(&scratch);
}

extern int gl_func_00000000();
void gl_func_0003FC2C(int *a0) {
    gl_func_00000000(a0);
    a0[1] = 1;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FC58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0003FF44);

extern int gl_func_00000000();
void gl_func_0003FFDC(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00040018(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040070);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000402A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040304);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040640);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040974);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040CAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040DE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00040E90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041008);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000410AC);

extern int gl_func_00000000();
int gl_func_000410E4(int a0) {
    return gl_func_00000000(a0, 0);
}

extern int gl_func_00000000();
int gl_func_00041104() {
    return gl_func_00000000();
}

extern int gl_func_00000000();
extern char gl_ref_0001F568;
int gl_func_00041124() {
    return gl_func_00000000(&gl_ref_0001F568);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041148);

extern int gl_func_00000000();
int gl_func_00041258() {
    return gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041278);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000412A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000412E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041524);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000415A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041768);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000417CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004182C);

extern int gl_func_00000000();
extern char gl_ref_0001F63C;
void gl_func_00041A74(int a0) {
    gl_func_00000000(&gl_ref_0001F63C);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041A9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041D40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041EDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00041F90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042098);

extern int gl_func_00000000();
int gl_func_000420F4(int a0) {
    return gl_func_00000000(gl_func_00000000, a0);
}

extern int gl_func_00000000();
int gl_func_0004211C(int a0) {
    return gl_func_00000000(gl_func_00000000, a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000421D4);

extern int gl_func_00000000();
int gl_func_00042288() {
    return gl_func_00000000(gl_func_00000000);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000422AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042338);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000423D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042440);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042484);

extern int gl_func_00000000();
extern char gl_ref_0001FCB4;
int gl_func_000424D8() {
    return gl_func_00000000(&gl_ref_0001FCB4);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000424FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042570);

extern int gl_func_00000000();
void gl_func_000425BC(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

extern int gl_func_00000000();
void gl_func_000425F0(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00042648(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042684);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042778);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00042944);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000430E4);

extern int gl_func_00000000();
extern char gl_ref_0001FD00;
void gl_func_00043284(int *a0, int a1) {
    if ((*a0 & 7) != 0) {
        gl_func_00000000(&gl_ref_0001FD00);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000432BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043484);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043558);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043584);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000435FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043654);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000437C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043BEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043D38);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043EAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043F1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00043F50);

extern int gl_ref_00056BDC();
extern int gl_ref_00056C28();
void gl_func_00043FFC(char *a0) {
    gl_ref_00056BDC(a0);
    gl_ref_00056C28(a0 + 0x10);
    gl_ref_00056C28(a0 + 0x14);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044034);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000444B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044548);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000445AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044918);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044AEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044B84);

extern int gl_func_00000000();
void gl_func_00044CC4(int a0, int a1) {
    gl_func_00000000((unsigned char)a1);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044CE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044D94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044DE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00044EDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00045178);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000453A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000454C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00045CB0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00045E20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00045FF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046050);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046790);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000469A8);

extern int gl_func_00000000();
int gl_func_00046B44() {
    return gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046B64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046BC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046C4C);

extern int gl_func_00000000();
void gl_func_00046F80(int a0, int a1, int a2) {
    gl_func_00000000(0, a1, a2, 0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00046FA8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000470FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000473AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047644);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000476DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000478FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047B40);

#ifdef NON_MATCHING
/* NON_MATCHING: temp uses a3 not a2 */
extern int gl_func_00000000();
int gl_func_00047DD8(int *a0, int a1) {
    return gl_func_00000000(a1, a0[0x38]);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047DD8);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047E00);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047F48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00047F9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00048354);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000483BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00048510);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00048720);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004880C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000488A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00048A74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00048AEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00049308);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000493AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00049B3C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00049DBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A308);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A670);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A6E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A7CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A84C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004A890);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004AA90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004AAF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004ABD8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004ACD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004ADB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004AE40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004AFB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004B040);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004B0A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004B2FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004B620);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004BAF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C190);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C214);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C300);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C5E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004C928);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004CCB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004CDB8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004CF04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004CFD4);

extern int gl_ref_00056CB4();
extern int gl_ref_00056C5C();
int gl_func_0004D02C(char *a0) {
    int scratch;
    gl_ref_00056CB4(&scratch);
    return gl_ref_00056C5C(a0 + 0x10);
}

#ifdef NON_MATCHING
/* NON_MATCHING: sw ra scheduled wrong vs lui a0 */
extern int gl_func_00000000();
void gl_func_0004D05C(int a0) {
    extern char gl_ref_000201B0;
    gl_func_00000000(&gl_ref_000201B0);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D05C);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D084);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D0B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D224);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D2A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D354);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D3E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D468);

extern int gl_func_00000000();
extern char gl_ref_000201FC;
void gl_func_0004D658(int a0) {
    gl_func_00000000(&gl_ref_000201FC);
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004D688);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DA40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DB50);

extern int gl_func_00000000();
void gl_func_0004DC08(char *a0, int *a1) {
    gl_func_00000000(a1, a0 + 8);
    a1[0x19] = 0;
    a1[0x18] = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DC44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DCD4);

extern int gl_func_00000000();
void gl_func_0004DD64(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_0004DDA0(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DDF8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DE88);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DEF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004DF90);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E00C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E150);

#ifdef NON_MATCHING
/* NON_MATCHING: a0 spill slot off by 4 bytes */
extern int gl_func_00000000();
void gl_func_0004E180(char *a0) {
    char *newA0 = a0 + 0xA0;
    *(char**)(a0 + 0xE0) = newA0;
    gl_func_00000000(newA0);
    *(char**)(a0 + 0xE0) = newA0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E180);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E1BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E214);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E244);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E384);

extern int gl_ref_000623D0();
extern int gl_ref_0006240C();
int gl_func_0004E3F4(char *a0) {
    int scratch;
    gl_ref_000623D0(&scratch);
    return gl_ref_0006240C(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E424);

extern int gl_func_00000000();
void gl_func_0004E4E8(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E524);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E584);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E600);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E728);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E760);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E888);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E8D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E920);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004E96C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004EB54);

extern int gl_func_00000000();
extern char gl_ref_000205F0;
void gl_func_0004ECE4(int a0) {
    gl_func_00000000(&gl_ref_000205F0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004ED0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004ED7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004EE44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F0E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F2F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F704);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F85C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F9AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004F9E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004FBA4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0004FD18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000500EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000503A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00050444);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005062C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000510F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000513CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051448);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051520);

extern int gl_func_00000000();
void gl_func_000515C0(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000515FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005165C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051694);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051714);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051774);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000517B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005185C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000519A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051AD8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051E98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051ED8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00051F5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000520B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052104);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000521F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005231C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005256C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000525F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000526D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052994);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052AE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052BBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00052CD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000531C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000533EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00053560);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00053A2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00053C04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054228);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054264);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000545BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054668);

extern int gl_func_00000000();
int gl_func_000546BC(char *a0) {
    return gl_func_00000000(gl_func_00000000, a0 + 0x2C, a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000546E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054A14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054AEC);

extern int gl_func_00000000();
int gl_func_00054BE4(char *a0) {
    return gl_func_00000000(a0 + 0x10C);
}

extern int gl_func_00000000();
int gl_func_00054C04(char *a0) {
    return gl_func_00000000(a0 + 0x10C);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054C24);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054C6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054D04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00054E78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000550CC);

extern int gl_ref_00065C2C();
extern int gl_ref_00065C68();
int gl_func_000551B0(char *a0) {
    int scratch;
    gl_ref_00065C2C(&scratch);
    return gl_ref_00065C68(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000551E0);

extern int gl_func_00000000();
extern char gl_ref_00021144;
void gl_func_00055264(char *a0) {
    if (*(int*)(*(int*)(a0 + 0x3C) + 0x10) == 0) {
        gl_func_00000000(&gl_ref_00021144);
    }
}

extern int gl_func_00000000();
extern char gl_ref_00021160;
void gl_func_00055298(char *a0) {
    if (*(int*)(*(int*)(a0 + 0x3C) + 0xC) == 0) {
        gl_func_00000000(&gl_ref_00021160);
    }
}

extern int gl_func_00000000();
extern char gl_ref_00021180;
void gl_func_000552CC(int *a0) {
    if (a0[4] == 0) {
        gl_func_00000000(&gl_ref_00021180);
    }
}

extern int gl_func_00000000();
extern char gl_ref_00021198;
void gl_func_000552FC(int *a0) {
    if (a0[3] == 0) {
        gl_func_00000000(&gl_ref_00021198);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005532C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005534C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00055470);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000558A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005591C);

extern int gl_func_00000000();
void gl_func_00055A7C(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00055AB8(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00055B10);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00055B44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00055C34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00055FB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056084);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000561A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005640C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056580);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056864);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056898);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056974);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056D14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00056FF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00057104);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000575E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00057700);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000578B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00059E80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005A2CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005A9D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005AB84);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005AD54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005AF64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005AFD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B070);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B23C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B3E0);

extern int gl_func_00000000();
void gl_func_0005B53C(int a0, int *a1) {
    gl_func_00000000(a0, *a1);
    *a1 = 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B568);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B68C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B6E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B764);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B848);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005B90C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005BAF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005BBCC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005BCD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005BD80);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005BE20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C284);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C43C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C66C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C6C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C784);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C810);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C960);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005C9BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005CB68);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005CCF4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005CE68);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D054);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D20C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D30C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D414);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D480);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D4F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D628);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D760);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D908);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005D9EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005DB0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005DB58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005DBB0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005DDE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E030);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E0B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E138);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E190);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E288);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E664);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E718);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005E950);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005EAA4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005EB4C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005ED60);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005EF00);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005F0C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005F3E0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005F54C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005F5F0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005F984);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FCC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FD20);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FDCC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FE1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FE7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FF14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0005FFD0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060028);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000600A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000601B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000601DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060260);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000602A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060318);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060370);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060468);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000604D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006052C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060584);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000608A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060A74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060AD0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060BDC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060D08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060D40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060DC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00060ED0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006126C);

extern int gl_func_00000000();
int gl_func_00061458() {
    return gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061478);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061734);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000617A8);

extern int gl_func_00000000();
int gl_func_000618D0(char *a0, int a1) {
    return gl_func_00000000(a1, a0 + 0x24);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000618F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061934);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000619D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061A0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061B30);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061BC8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061C9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061D1C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061D94);

extern int gl_func_00000000();
void gl_func_00061DE0(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00061E1C(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061E58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061E9C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061F18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00061F8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062194);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062298);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000622D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062368);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062484);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062540);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000625FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006264C);

extern int gl_func_00000000();
int gl_func_000626EC(char *a0) {
    return gl_func_00000000(a0 + 0x40);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006270C);

extern int gl_func_00000000();
int gl_func_0006273C(char *a0) {
    return gl_func_00000000(a0 + 0x40);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006275C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006280C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000628EC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062A2C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062E10);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062E80);

extern int gl_func_00000000();
void gl_func_00062F64(int a0) {
    gl_func_00000000(a0);
    gl_func_00000000(a0);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00062F8C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006337C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063498);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000634F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063568);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000635D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006366C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006370C);

extern int gl_func_00000000();
void gl_func_00063744(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00063780(float *dst) {
    int pad;
    float scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000637BC);

extern int gl_func_00000000();
void gl_func_0006382C(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063884);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063964);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063DC4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063E84);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00063F40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000640E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064174);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000641DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064388);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064588);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00064DEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065060);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065148);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065250);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000652D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065360);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065448);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065494);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000659D0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065B5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065C54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065D08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065D64);

extern int gl_ref_00077DB0();
extern int gl_ref_00077DEC();
int gl_func_00065DDC(char *a0) {
    int scratch;
    gl_ref_00077DB0(&scratch);
    return gl_ref_00077DEC(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065E0C);

extern int gl_func_00000000();
int gl_func_00065E44(char *a0) {
    return gl_func_00000000(a0 + 0x108);
}

extern int gl_func_00000000();
int gl_func_00065E64(char *a0) {
    return gl_func_00000000(a0 + 0x108);
}

extern int gl_ref_00077DB0();
extern int gl_ref_00077E98();
int gl_func_00065E84(char *a0) {
    int scratch;
    gl_ref_00077DB0(&scratch);
    return gl_ref_00077E98(a0 + 0x10);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065EB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00065F08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006612C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000661D8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066210);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066264);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000662E8);

extern int gl_func_00000000();
void gl_func_00066330(int a0, int a1, int a2, int a3) {
    gl_func_00000000(a1, a2, a3);
}

extern int gl_func_00000000();
void gl_func_00066364(int a0) {
    gl_func_00000000();
}

extern int gl_func_00000000();
extern char gl_ref_00022498;
int gl_func_00066384(int a0) {
    return gl_func_00000000(&gl_ref_00022498, a0);
}

extern int gl_func_00000000();
extern char gl_ref_000224B0;
int gl_func_000663AC() {
    return gl_func_00000000(&gl_ref_000224B0);
}

extern int gl_func_00000000();
void gl_func_000663D0(int *a0) {
    int pad, scratch;
    scratch = *a0;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066404);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066484);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066514);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000665B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066674);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066720);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066794);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066810);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066850);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000669B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066A50);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066AF0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066B64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066BD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066C30);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066C74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066D54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00066EEC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067084);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067134);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067168);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006719C);

#ifdef NON_MATCHING
/* NON_MATCHING: expected copies a0 to a3 via `or a3, a0, zero`; IDO does not
 * emit the copy from plain C, and `register T asm("$7")` (GCC extension) is
 * not supported by IDO cfe. */
extern int gl_func_00000000();
extern char gl_ref_000416E0;
void gl_func_000671E4(char *a0) {
    *(int*)(a0 + 0x13E8) = 0;
    *(int*)&gl_ref_000416E0 = 1;
    gl_func_00000000(a0 + 0x11B0, &gl_ref_000416E0, 1);
}
#else
INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000671E4);
#endif

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067220);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067264);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067370);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067394);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000673FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067470);

extern int gl_func_00000000();
void gl_func_000674DC(int *a0) {
    int v = a0[0xD];
    if (v != 0) {
        gl_func_00000000(gl_func_00000000, v - 1, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067510);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067550);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000675A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000679BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067A10);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067A54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067AC8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067AE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067C98);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067EFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00067F58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068048);

extern int gl_func_00000000();
void gl_func_000681F4(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068230);

extern int gl_func_00000000();
void gl_func_00068280(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_000682BC(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000682F8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068350);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000683D4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000684AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068524);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000685C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006869C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000686D8);

extern int gl_func_00000000();
int gl_func_0006870C() {
    gl_func_00000000();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068730);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006877C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000687B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068884);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000688F8);

extern int gl_func_00000000();
void gl_func_00068960(char *a0) {
    *(short*)(a0 + 0x20) = 0;
    *(short*)(a0 + 0x22) = 0;
    *(int*)(a0 + 0x24) = 0;
    *(int*)(a0 + 0x8) = 0;
    *(int*)(a0 + 0x2C) = 0;
    gl_func_00000000();
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068990);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068B04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068BAC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068C14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068D18);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068DD4);

extern int gl_func_00000000();
void gl_func_00068F28(int *dst) {
    int pad, scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 4);
    *dst = scratch;
}

extern int gl_func_00000000();
void gl_func_00068F64(Quad4 *dst) {
    Quad4 scratch;
    gl_func_00000000(gl_func_00000000, &scratch, 16);
    *dst = scratch;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00068FBC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000690A8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000693A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000695F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069688);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000697C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069B94);

extern int gl_func_00000000();
int gl_func_00069C38(char *a0) {
    return gl_func_00000000(a0 + 0x48);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069C58);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069C94);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069CD0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069E04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00069F64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006A304);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006A420);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006A5B0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006AF0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006AF44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B0FC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B7A0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B880);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B974);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006B9B4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BA0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BA48);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BA7C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BAD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BC4C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BD14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BE14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BE6C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BEA8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006BF34);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C084);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C11C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C1B8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C2AC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C384);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C484);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C90C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006C9F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CAD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CB84);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CC14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CC64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CCD4);

extern int gl_func_00000000();
int gl_func_0006CD24() {
    return gl_func_00000000(0x400);
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CD44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CDB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006CF54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D0F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D270);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D554);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D6F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D7CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006D964);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DA74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DC0C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006DD14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E1A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E224);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006E894);

extern int gl_func_00000000();
int gl_func_0006EEE4(int a0, int a1, int a2) {
    return gl_func_00000000(a0, a1) + a2;
}

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006EF08);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006EF64);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F088);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F160);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F38C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F3BC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F3E4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F534);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F634);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F69C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F834);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006F8A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FAD4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FB54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FC78);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FDE8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FE5C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0006FFE4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070040);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070194);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070244);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070634);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070694);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000707E8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000709DC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070A14);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070B04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00070C44);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071144);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071304);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071384);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071624);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071708);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000717CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071864);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000718C0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071928);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071D40);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00071ED8);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072134);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072230);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072550);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000725C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072C88);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00072E3C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073034);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007307C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000730CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000732C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073334);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073538);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007369C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073824);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073904);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00073E74);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000743C4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000744CC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074554);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000747F4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_000748A4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074AC0);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074C04);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074D54);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074DB4);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_00074EFC);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007507C);

INCLUDE_ASM("asm/nonmatchings/game_libs/game_libs", gl_func_0007526C);

