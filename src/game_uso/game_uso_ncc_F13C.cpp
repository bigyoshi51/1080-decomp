/* IDO 7.1 NCC (C++) donor for game_uso_func_0000F13C (0x144 / 81 words).
 *
 * Same opening flag block as F060: if the 0xB4 object's 0x800 child has
 * (!(flags & 0x100) || (flags & 0x200)) and the 0xB4 object's 0x938 is set,
 * F360(self). Otherwise DB78 (float 4th arg = 0xB4->0x970) when |0x970|
 * exceeds the D_807FFB58+0x238 double, else DB28; then 1001C(self) when
 * 0xB4->0x938 is clear. Finally ++self->0xE6 and D5BC(self, PMF by value)
 * once the old counter passes self->0x184.
 *
 * The inlined `V::child()` member puts the 0xB4 pointer in v1 (edg keeps the
 * inline return temp in v0); written inline it colours v0 (cfe 99.57%).
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern char game_uso_D_807FFB58;
extern char game_uso_D_807FF498;
void import_0010DB28(void *, int, int, int, int, int);
void import_0010DB78(void *, int, int, float, int, int);
void game_uso_func_0000F360(void *);
void game_uso_func_0001001C(void *);
void game_uso_func_0000D5BC(void *, PM);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
#define I(b,o) AT(int,b,o)
struct V { int *child() { return AT(int *, this, 0x800); } };
extern "C" void game_uso_func_0000F13C(int *a0, int *a1) {
    int *s0 = a0;
    a1 = AT(V *, s0, 0xB4)->child();
    if ((((a1[0x10 / 4] & 0x100) != 0) == 0 || (((unsigned int *)a1)[0x10 / 4] & 0x200)) && I(AT(V *, s0, 0xB4), 0x938) != 0) {
        game_uso_func_0000F360(s0);
    } else {
        float f0 = AT(float, AT(V *, s0, 0xB4), 0x970);
        float abs_f0 = (f0 < 0.0f) ? -f0 : f0;
        if (AT(double, &game_uso_D_807FFB58, 0x238) < (double)abs_f0) {
            import_0010DB78(s0, 0x10028, 0x10029, f0, 0, 1);
        } else {
            import_0010DB28(s0, 0x10011, 0, 1, 6, 1);
        }
        if (I(AT(V *, s0, 0xB4), 0x938) == 0) {
            game_uso_func_0001001C(s0);
        }
    }
    {
        short v0 = AT(short, s0, 0xE6);
        AT(short, s0, 0xE6) = v0 + 1;
        if (s0[0x184 / 4] < v0) {
            game_uso_func_0000D5BC(s0, AT(PM, &game_uso_D_807FF498, 0xEA8));
        }
    }
}
