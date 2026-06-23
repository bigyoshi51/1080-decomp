#include "common.h"

extern int func_00000000();
extern char D_00000000;
typedef struct { int a, b, c, d; } Quad4;

extern int func_00000008;       /* USO-base reloc (D_-style placeholder pointer) */
extern int func_000000F0;       /* USO-base reloc */
extern int func_00000188;       /* USO-base reloc */
extern char D_0000C57C;
extern char D_0000C58C;
extern char D_0000C594;

#ifdef NON_MATCHING
/* func_0000F81C: 78-insn (0x138) allocator + init helper.
 *
 * Decoded structure:
 *   1. Set up local flags word = 0. If arg1 (a1) != 0, flags |= 0x6.
 *   2. Zero 4 floats at (&func_00000008 + 0x28)[0..C] (some Vec4-like slot).
 *   3. Big call gl_func_00000000(0, 0x64, &D_0000C57C, 0x6D, [stack args
 *      0x6E,0,0,0x6F,0x140,0xF0,0x70,flags|0x400,0x71,0x2,0]) — likely an
 *      object allocator with a long argument-list constructor pattern.
 *   4. result is saved to local + sp+0x80; another call:
 *      gl_func_00000000(&func_00000008+0x24, result).
 *   5. *(int*)((char*)*(int*)(&func_000000F0+0x44) + 0x114) = result.
 *   6. Return result.
 *
 * Big-constructor pattern, 13-arg call with many stack-passed args
 * (sp+0x10..sp+0x3C). First-draft, expect ~40-60% fuzzy. Multi-tick
 * refinement target. */
void* func_0000F81C(int a0, int a1) {
    int flags = 0;
    void *result;
    float *floats;
    if (a1 != 0) {
        flags |= 6;
    }
    floats = (float*)((char*)&func_00000008 + 0x28);
    floats[0] = 0.0f;
    floats[1] = 0.0f;
    floats[2] = 0.0f;
    floats[3] = 0.0f;
    result = (void*)func_00000000(0, 0x64, &D_0000C57C, 0x6D,
                                   0x6E, 0, 0, 0x6F, 0x140, 0xF0,
                                   0x70, flags | 0x400, 0x71, 2, 0);
    func_00000000((char*)&func_00000008 + 0x24, result);
    *(int*)((char*)*(int*)((char*)&func_000000F0 + 0x44) + 0x114) = (int)result;
    return result;
}
#else
INCLUDE_ASM("asm/nonmatchings/bootup_uso", func_0000F81C);
#endif

/* func_0000F954 + func_0000F9E8 split out to bootup_uso_o0_F954.c on 2026-06-23
 * (cluster -O0 split; F954 is a byte-exact -O0 match, F9E8 stays NM at 1w off).
 * Moved together so tail1.c keeps only the -O2 func_0000F81C and the linker layout
 * stays contiguous. */

/* func_0000FAE8 split out to bootup_uso_o0_FAE8.c on 2026-06-23 — it's an -O0
 * function (reloads self each use, register-var bit-manip in s0-s3, if(1)
 * dead-branch); now a byte-exact -O0 C match there (same recipe as 100F0/118E4). */

/* func_000100F0 + func_0001016C split out to bootup_uso_o0_100F0.c on
 * 2026-05-14 for -O0 build (same recipe as func_000118E4 ->
 * bootup_uso_o0_118E4.c earlier this date). */
