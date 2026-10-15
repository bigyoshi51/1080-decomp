/* IDO 7.1 NCC (C++) donor for game_uso_func_0000F060 (0xDC / 55 words).
 *
 * Flag-dispatch state handler: clear self->0xF4, run 11888, then if the
 * 0xB4 object's 0x800 child has (!(flags & 0x100) || (flags & 0x200)) and
 * the 0xB4 object's 0x938 is set, F360(self) and return. Otherwise DB28,
 * D5F8 with the PMF at D_807FF4A0+0xEB0 passed by value, clear 0xE6,
 * bump 0xE4 and call 966AC(self->0xB4 + 0x808).
 *
 * The 0x800 child is read through an inlined member `V::child()`. edg keeps
 * the inline return temp in v0, so the 0xB4 pointer colours v1 as in the
 * target; the same expression written inline (cfe or NCC) colours it v0
 * (99.64%). `((x & 0x100) != 0) == 0` keeps the materialized bool
 * (`sltu; beqzl`), and the `unsigned *` re-read keeps the flag reload.
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern char game_uso_D_807FF4A0;
void import_0010DB28(void *, int, int, int, int, int);
void import_000966AC(void *);
void game_uso_func_0000F360(void *);
void game_uso_func_00011888(void *);
void game_uso_func_0000D5F8(void *, PM, int);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
#define I(b,o) AT(int,b,o)
struct V { int *child() { return AT(int *, this, 0x800); } };
extern "C" void game_uso_func_0000F060(int *a0) {
    int *s0 = a0;
    a0[0xF4 / 4] = 0;
    game_uso_func_00011888(a0);
    a0 = AT(V *, s0, 0xB4)->child();
    if ((((a0[0x10 / 4] & 0x100) != 0) == 0 || (((unsigned int *)a0)[0x10 / 4] & 0x200)) && I(AT(V *, s0, 0xB4), 0x938) != 0) {
        game_uso_func_0000F360(s0);
        return;
    }
    import_0010DB28(s0, 0x10011, 0, 0, 0x100, s0[0x16C / 4]);
    game_uso_func_0000D5F8(s0, AT(PM, &game_uso_D_807FF4A0, 0xEB0), -1);
    AT(short, s0, 0xE6) = 0;
    AT(short, s0, 0xE4) = AT(short, s0, 0xE4) + 1;
    import_000966AC(AT(char *, s0, 0xB4) + 0x808);
}
