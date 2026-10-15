/* IDO 7.1 NCC (C++) donor for game_uso_func_00010840 (0x10C / 67 words).
 *
 * State-entry handler, sibling of 10694: self->0xB4->0x3DC = 1, D8A8(self),
 * D8EC(self); f0 = self->0xB4->0x970; if |f0| exceeds the double at
 * D_807FFB78+0x258, DB78(self, 0x20002, 0x20003, f0, 0, 1), else
 * DB28(self, 0x20008, 0, 1, 6, 1); E1FC(self); if self->0xB4->0x9CC == 0,
 * D5BC(self, PMF at D_807FF400+0xE10); 11750(self).
 *
 * The cfe wrap (87.67%) had two wrong guesses: the `mfc1 a3,f0` is just
 * DB78's float 4th parameter (as in F13C), and the "dead arg-prep" before
 * the abs branch (a1 = 0x20008, a2 = 0, a3 = 1) is the else-arm's DB28
 * argument list, hoisted. With both fixed the NCC compile matches on the
 * first try.
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern char game_uso_D_807FFB78;
extern char game_uso_D_807FF400;
void import_0010DB28(void *, int, int, int, int, int);
void import_0010DB78(void *, int, int, float, int, int);
void game_uso_func_0000D8A8(void *);
void game_uso_func_0000D8EC(void *);
void game_uso_func_0000E1FC(void *);
void game_uso_func_0000D5BC(void *, PM);
void game_uso_func_00011750(void *);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
#define I(b,o) AT(int,b,o)
extern "C" void game_uso_func_00010840(int *a0) {
    float f0;
    I(I(a0, 0xB4), 0x3DC) = 1;
    game_uso_func_0000D8A8(a0);
    game_uso_func_0000D8EC(a0);
    f0 = AT(float, I(a0, 0xB4), 0x970);
    if ((double)(f0 < 0.0f ? -f0 : f0) > AT(double, &game_uso_D_807FFB78, 0x258)) {
        import_0010DB78(a0, 0x20002, 0x20003, f0, 0, 1);
    } else {
        import_0010DB28(a0, 0x20008, 0, 1, 6, 1);
    }
    game_uso_func_0000E1FC(a0);
    if (I(I(a0, 0xB4), 0x9CC) == 0) {
        game_uso_func_0000D5BC(a0, AT(PM, &game_uso_D_807FF400, 0xE10));
    }
    game_uso_func_00011750(a0);
}
