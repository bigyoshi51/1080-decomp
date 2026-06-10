/* game_libs ido53 carve: gl_func_00074D54 -- 1080 interrupt-bracket float
 * setter, verbatim shape at IDO 5.3 -O1, 22/22 first try with ALL words
 * (incl. reloc fields) matching: sr = __osDisableInt-class call;
 * P1->f_24 = arg; *P2 |= 4; restore(sr). Globals are reloc'd POINTER
 * variables (lui+lw, %lo=0) -- zero-alias placeholders. The 8-byte pad
 * sidecar is reproduced by an all-zero SUFFIX. */
extern int gl_func_00000000();
extern char *D_74D54_p1;
extern unsigned short *D_74D54_p2;

void gl_func_00074D54(float f) {
    register int sr;
    sr = gl_func_00000000();
    *(float *)(D_74D54_p1 + 0x24) = f;
    *D_74D54_p2 |= 4;
    gl_func_00000000(sr);
}
