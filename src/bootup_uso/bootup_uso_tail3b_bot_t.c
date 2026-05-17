#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

void func_0001266C(char *a0, int a1) {
    register u16 *p;

    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p & ~3;
    p = (u16 *)(*(char **)(a0 + 0x154) + 4);
    *p = *p | a1;
    func_00000000((*(u16 *)(*(char **)(a0 + 0x154) + 4)) & 3);
}

#ifdef NON_MATCHING
/* func_000126EC: 56-insn -O0 vtable dispatcher. 53.57% NM first-pass.
 * Sibling of func_000127CC in this -O0-built file.
 *
 *   *(short*)((char*)*(int**)(a0+0x154) + 4) &= ~5;
 *   if (a1 != 0)
 *     *(short*)((char*)*(int**)(a0+0x154) + 4) |= 4;
 *   D_00000000 = a1;
 *   result = &local[0];                 // sp+0x34, always non-NULL
 *   if (result == NULL) {                // dead branch (sp+N never NULL)
 *     result = func(12);
 *     if (result == NULL) return 0;
 *   }
 *   result[0] = 0x15;
 *   msg = D_00000000->[0x28];
 *   return ((int(*)(...))(msg->[0x34]))((char*)&D_0 + msg->[0x30], result);
 *
 * Structural NM-only first-pass — full match needs typed-struct decl
 * for the vtable msg AND knowing the fn-ptr signature precisely. */
extern int func_00000000();
int func_000126EC(int *a0, int a1) {
    int local[5];
    int *result;
    int *msg;
    *(short*)((char*)*(int**)((char*)a0 + 0x154) + 4) &= ~5;
    if (a1 != 0) {
        *(short*)((char*)*(int**)((char*)a0 + 0x154) + 4) |= 4;
    }
    *(int*)&D_00000000 = a1;
    result = &local[0];
    if (result == 0) {
        result = (int*)func_00000000(12);
        if (result == 0) return 0;
    }
    result[0] = 0x15;
    msg = *(int**)((char*)&D_00000000 + 0x28);
    return ((int(*)(char*, int*))msg[0x34/4])(
        (char*)&D_00000000 + *(short*)((char*)msg + 0x30),
        result);
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_000126EC);
#endif

/* 19-insn 8-byte copy loop. Logic: copy 8 bytes from
 * (*(char**)(a0+0x154))+6 to a1[0..7].
 * Promoted from NM wrap 2026-05-17 (file is -O0 per file split). */
void func_000127CC(char *a0, char *a1) {
    int i;
    for (i = 0; i < 8; i++) {
        a1[i] = (*(char**)(a0 + 0x154))[i + 6];
    }
}
