/* IDO 7.1 -O2 donor for gl_func_0003AC5C -- constructor + token-stream loop
 * (0x1FC / 127 words; 127/127 word-exact standalone apart from reloc fields).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post0b.c.o (the
 * 29CCC / 44B78 / 52CD4 recipe, docs/MATCHING_WORKFLOW.md#post0b-jumptable-
 * donor-52cd4). The C switch over cmd 0..4 puts its 5-entry jumptable in the
 * donor's local .rodata; the splice renames that reloc to
 * gl_func_0003AC5C_rodata, pinned to 0x1A90 in undefined_syms_auto.txt
 * (bootup.uso RoData file offset 0x1A94.. = imm + 4; arms: case 0 -> +0xDC,
 * 1 -> +0xBC, 2 -> +0xA8, 3 -> +0x15C, 4 -> +0x180; raw word - 0x1466C -
 * 0x3AC5C). Arms are written in address (= source) order 2, 1, 0, 3, 4.
 *
 * Decode/levers from the 2026-08-22 agent-g rework (46.1 -> 97.5) kept:
 * plain switch, int stream words converted with (f32), post-increment temp
 * idiom per read, nested-goto alloc guard, args as the persistent regs,
 * if (1) around the loop (cmd/q in v1/v0). The last 4 scheduler words:
 *  - case 3: name the call arg (`q = arg1; arg1 = q + 1; v = *q;`, v passed
 *    in a2) -> `or v0,s0; lw a2,0(v0); addiu s0,4`; with *q inline in the
 *    call the addiu schedules before the lw.
 *  - case 4: skip word, then `q = arg1; arg1 = q + 1; flag = *q;` on one
 *    line -> lw s5 before the b, addiu in the delay; the old
 *    `q = arg1; arg1 += 1;` + `flag = *q;` put the lw in the delay slot.
 * The four baked lui/addiu message addresses are pinned data refs
 * (gl_ref_0001EExx_3AC5C). */
#include "common.h"

extern int gl_func_00000000();
extern char gl_ref_0001EE18_3AC5C, gl_ref_0001EE24_3AC5C, gl_ref_0001EE3C_3AC5C, gl_ref_0001EE48_3AC5C;

int *gl_func_0003AC5C(int *arg0, int *arg1) {
    int *q;    /* v0 post-increment temp */
    int cmd;   /* v1 */
    int flag;  /* s5 */
    int v;

    if (arg0 == 0) {
        arg0 = (int *) gl_func_00000000(0x90);
        if (arg0 == 0) {
            goto ret;
        }
    }
    gl_func_00000000(arg0, &gl_ref_0001EE18_3AC5C);
    *(int **)((char *)arg0 + 0x34) = arg1;
    flag = 0;
    gl_func_00000000(&gl_ref_0001EE24_3AC5C);
    *(int *)((char *)arg0 + 0x30) = 0;
    if (1) {
    q = arg1; arg1 = q + 1; cmd = *q;
    while (cmd != 6) {
        switch (cmd) {
        case 2:
            q = arg1; arg1 = q + 1;
            *(int *)((char *)arg0 + 0x30) = *q;
            break;
        case 1:
            q = arg1; arg1 = q + 1;
            *(f32 *)((char *)arg0 + 0x38) = (f32) *q;
            break;
        case 0:
            *(f32 *)((char *)arg0 + 0x3C) = (f32) arg1[0];
            arg1 += 6;
            *(f32 *)((char *)arg0 + 0x40) = (f32) arg1[-5];
            *(f32 *)((char *)arg0 + 0x44) = (f32) arg1[-4];
            *(f32 *)((char *)arg0 + 0x48) = (f32) arg1[-3];
            *(f32 *)((char *)arg0 + 0x4C) = (f32) arg1[-2];
            *(f32 *)((char *)arg0 + 0x50) = (f32) arg1[-1];
            break;
        case 3:
            q = arg1; arg1 = q + 1; v = *q;
            *(int *)((char *)arg0 + 0x84) = gl_func_00000000(0, &gl_ref_0001EE3C_3AC5C, v, 0);
            break;
        case 4:
            arg1 += 1;
            q = arg1; arg1 = q + 1; flag = *q;
            break;
        default:
            gl_func_00000000(&gl_ref_0001EE48_3AC5C);
            break;
        }
        q = arg1; arg1 = q + 1; cmd = *q;
    }
    }
    if (flag == 0) {
        *(int *)((char *)arg0 + 0x88) = 0;
        *(int *)((char *)arg0 + 0x8C) = 0;
    }
    *(f32 *)((char *)arg0 + 0x54) = 0.0f;
    *(f32 *)((char *)arg0 + 0x58) = 0.0f;
    *(f32 *)((char *)arg0 + 0x5C) = 0.0f;
    gl_func_00000000();
ret:
    return arg0;
}
