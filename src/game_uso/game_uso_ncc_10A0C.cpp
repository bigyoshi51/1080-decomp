/* IDO 7.1 NCC (C++) donor for game_uso_func_00010A0C (0xBC / 47 words).
 *
 * EE84-family state handler, near-twin of 1094C: DB78(self, 0x20004,
 * 0x20005, self->0xB4->0x970, 0, 1); if self->0xB4->0x990 == 0 call
 * D5BC(self, PMF at D_807FF438+0xE48); if self->0xB4->0x9CC == 0 call
 * D5BC(self, PMF at D_807FF460+0xE70); then D8EC(self) and D7F4(self).
 *
 * The cfe C (93.4%) had every temp renumbered (t6/t7/t9/t3 vs the target's
 * v0/t6/t8/t1) and a late `or s0,a0`. The same logic under NCC, with the
 * PMFs passed by value (pointer-to-member type) and the param used
 * directly, matches on the first compile.
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern char game_uso_D_807FF438;
extern char game_uso_D_807FF460;
void import_0010DB78(void *, int, int, int, int, int);
void game_uso_func_0000D5BC(void *, PM);
void game_uso_func_0000D8EC(void *);
void game_uso_func_0000D7F4(void *);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
#define I(b,o) AT(int,b,o)
extern "C" void game_uso_func_00010A0C(int *a0) {
    int *p;
    import_0010DB78(a0, 0x20004, 0x20005, I(I(a0, 0xB4), 0x970), 0, 1);
    p = (int *)a0[0xB4 / 4];
    if (p[0x990 / 4] == 0) {
        game_uso_func_0000D5BC(a0, AT(PM, &game_uso_D_807FF438, 0xE48));
        p = (int *)a0[0xB4 / 4];
    }
    if (p[0x9CC / 4] == 0) {
        game_uso_func_0000D5BC(a0, AT(PM, &game_uso_D_807FF460, 0xE70));
    }
    game_uso_func_0000D8EC(a0);
    game_uso_func_0000D7F4(a0);
}
