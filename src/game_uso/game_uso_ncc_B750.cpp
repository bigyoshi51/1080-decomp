/* IDO 7.1 NCC (C++) donor for game_uso_func_0000B750 (0x134 / 77 words).
 *
 * Camera/basis update: f0 = src->0x00 (+ k * 400 when flag 4), where k is
 * the stack float argument, replaced by 1.0 unless flag 8. Writes
 * a2 + a3 * f0 to the vec at import_8005C1A8 + 0xD0, copies src->0x18 to
 * obj->0xC0 (short), and if src->0x14 (* k when flag 2) exceeds the double
 * at game_uso_D_807FFA78 + 0x158, stores it to obj->0xB0/0xB4, builds a
 * 4-float temporary (src->0x04, 0x08, 0x0C, src->0x10 * k), passes it to
 * 05B750(&import_8005C108, &q) and calls obj's third virtual (vptr at +0x28).
 *
 * C++ facts this body depends on (cfe capped at 72.8%):
 *  - k IS the parameter (`arg4 = 1.0f`): the param is re-loaded from its
 *    stack home into its own register on each path (two `lwc1 f16,104(sp)`),
 *    and there is one less local slot.
 *  - The temporary is a Q whose constructor forwards to an inline set();
 *    the nested inline argument temps give the target's frame (88, q at
 *    sp+64) and the FP colouring (x f0, y f2, z f12, w f14). A plain
 *    4-arg constructor gives frame 80 and y/z/w in f12/f14/f16.
 *  - `(int)&sym + 0xA0` keeps the `lui/addiu sym+0xA0` base (edg folds a
 *    char * spelling).
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct V { char pad[40]; virtual void m0(); virtual void m1(); virtual void m2(); };
struct Q {
    float x, y, z, w;
    void set(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
    Q(float a, float b, float c, float d) { set(a, b, c, d); }
};
extern "C" {
extern char import_8005C108;
extern char import_8005C1A8;
extern char game_uso_D_807FFA78;
void game_uso_func_05B750(void *, Q *);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
extern "C" void game_uso_func_0000B750(char *a0, char *s0, float *a2, float *a3, float arg4) {
    float f0 = AT(float, a0, 0x00);
    float v;
    if (AT(int, a0, 0x1C) & 4) f0 += arg4 * 400.0f;
    if (!(AT(int, a0, 0x1C) & 8)) arg4 = 1.0f;
    AT(float, (int)&import_8005C1A8 + 0xA0, 0x30) = a2[0] + a3[0] * f0;
    AT(float, (int)&import_8005C1A8 + 0xA0, 0x34) = a2[1] + a3[1] * f0;
    AT(float, (int)&import_8005C1A8 + 0xA0, 0x38) = a2[2] + a3[2] * f0;
    AT(short, s0, 0xC0) = AT(int, a0, 0x18);
    v = AT(float, a0, 0x14);
    if (AT(int, a0, 0x1C) & 2) v *= arg4;
    if ((double)v > AT(double, &game_uso_D_807FFA78, 0x158)) {
        AT(float, s0, 0xB0) = v;
        AT(float, s0, 0xB4) = v;
        Q q(AT(float, a0, 0x04), AT(float, a0, 0x08), AT(float, a0, 0x0C), AT(float, a0, 0x10) * arg4);
        game_uso_func_05B750(&import_8005C108, &q);
        ((V *)s0)->m2();
    }
}
