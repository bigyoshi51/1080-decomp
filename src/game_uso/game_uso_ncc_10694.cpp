/* IDO 7.1 NCC (C++) donor for game_uso_func_00010694 (0x1AC / 107 words).
 *
 * State-entry handler: flag the 0xB4 object, set state 2, sample
 * 0xB4->0x970, run the E1FC/D8A8/D8EC enter hooks, pick the DB78 / DB28
 * import by |r| vs the D_807FFB70+0x250 double, then two SetState-style
 * calls game_uso_func_0000D5BC(this, pm) taking a pointer-to-member BY VALUE
 * (a1/a2 + home-slot stores): once with the null-ish PMF at
 * D_807FF438+0xE48, once with this->pm at +0xD0 when it is non-null (the
 * same edg 2-word `at`/`addi` PMF compare as D204). Spliced into
 * game_uso.c.o via REPLACE_FUNC_BODY (docs/MATCHING_WORKFLOW.md#game-uso-
 * ncc-cplusplus-donor-recipe). The float 4th arg of DB78 goes out as
 * `mfc1 a3,$f0` straight from the prototype -- the "mfc1-from-C cap" of the
 * old C wrap was a missing prototype, not an IDO limit. Every symbol is
 * extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern char game_uso_D_807FFB70;
extern char game_uso_D_807FF438;
extern char game_uso_D_807FF3B8;
void game_uso_func_0000E1FC(void *);
void game_uso_func_0000D8A8(void *);
void game_uso_func_0000D8EC(void *);
void import_0010DB78(void *, int, int, float, int, int);
void import_0010DB28(void *, int, int, int, int, int);
void game_uso_func_0000E91C(void *);
void game_uso_func_00011750(void *);
void game_uso_func_0000D5BC(void *, PM);
}
#define I(b,o) (*(int *)((char *)(b) + (o)))
#define F(b,o) (*(float *)((char *)(b) + (o)))
#define P(b,o) (*(PM *)((char *)(b) + (o)))
extern "C" void game_uso_func_00010694(A *a0) {
    float r;
    float ar;
    I(I(a0, 0xB4), 0xA18) = 1;
    I(a0, 0x114) = 2;
    I(I(a0, 0xB4), 0x3DC) = 1;
    F(a0, 0x11C) = 1.0f;
    r = F(I(a0, 0xB4), 0x970);
    game_uso_func_0000E1FC(a0);
    I(I(a0, 0xB4), 0x960) = 0;
    game_uso_func_0000D8A8(a0);
    game_uso_func_0000D8EC(a0);
    ar = (r < 0.0f) ? -r : r;
    if ((double)ar > *(double *)(&game_uso_D_807FFB70 + 0x250)) {
        int v = I(a0, 0xFC);
        import_0010DB78(a0, v | 2, v | 3, r, 0, 1);
    } else {
        import_0010DB28(a0, I(a0, 0xFC) | 8, 0, 1, 6, 1);
    }
    if (I(I(a0, 0xB4), 0x9CC) != 0) {
        game_uso_func_0000D5BC(a0, P(&game_uso_D_807FF438, 0xE48));
    }
    game_uso_func_0000E91C(a0);
    game_uso_func_00011750(a0);
    I(a0, 0xDC) = I(I(a0, 0xB4), 0x938);
    if (P(a0, 0xD0) != P(&game_uso_D_807FF3B8, 0xDC8)) {
        game_uso_func_0000D5BC(a0, P(a0, 0xD0));
    }
}
