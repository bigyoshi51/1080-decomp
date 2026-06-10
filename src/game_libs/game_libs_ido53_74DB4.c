/* game_libs ido53 carve: gl_func_00074DB4 -- bigger sibling of the 74D54
 * interrupt-bracket setter, verbatim shape at IDO 5.3 -O1, 74/74 first
 * try (+ one register-declaration-order swap for the s0/s1 assignment:
 * v declared before sr puts v in s0, sr in s1). Shape: sr bracket;
 * P1->f_18 = arg; *P2 |= 2; v = P1->p_8->w_20 & 0xFFF;
 * P1->w_20 = (u32)(P1->f_18 * (float)(u32)v) & 0xFFF. The entire FCSR
 * save/set/convert/check/restore block is IDO's inline (u32)float cast;
 * the 0x4F800000 add is the standard (float)(u32) correction. The two
 * statements share one global load via same-BB CSE. */
typedef unsigned int u32;
extern int gl_func_00000000();
extern char *D_74DB4_p1;
extern unsigned short *D_74DB4_p2;

void gl_func_00074DB4(float f) {
    register int v;
    register int sr;
    sr = gl_func_00000000();
    *(float *)(D_74DB4_p1 + 0x18) = f;
    *D_74DB4_p2 |= 2;
    v = *(int *)(*(char **)(D_74DB4_p1 + 0x8) + 0x20) & 0xFFF;
    *(int *)(D_74DB4_p1 + 0x20) = (u32)(*(float *)(D_74DB4_p1 + 0x18) * (float)(u32)v) & 0xFFF;
    gl_func_00000000(sr);
}
