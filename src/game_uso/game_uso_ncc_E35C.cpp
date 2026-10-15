/* IDO 7.1 NCC (C++) donor for game_uso_func_0000E35C (0x208 / 130 words).
 *
 * Slot/queue advance, sibling of F6D4 (same body inside `if (self->0xF0)`,
 * no D6E4 pre-flush, 077C44 third arg 0, returns 1 / 0). Built with the
 * F6D4 recipe and exact on the first compile: no named prev local (the
 * F0 -> F4 move goes through the members, and the F8 compare and store
 * re-read F4), counter increment first, `F8 == F4`, base-first ceil-div
 * addu (edg), D5F8 / D5BC pairs are pointers to members by value. The
 * cfe wrap capped at 95.3%.
 * See docs/IDO_CODEGEN.md#ncc-no-named-copy-local-f6d4. Spliced into
 * game_uso.c.o via REPLACE_FUNC_BODY
 * (docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe). Every
 * symbol is extern "C". */
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
extern "C" {
extern int *game_uso_D_807FFBC0;
extern char import_800201D0;
extern char game_uso_D_807FF4B0;
extern char game_uso_D_807FF4B8;
extern char game_uso_D_807FF4C0;
void game_uso_func_0000EE30(void *, int, int);
void import_000B8518(int, void *, int);
void game_uso_func_0000E564(void *);
void game_uso_func_077C44(void *, int, int, int, int, int);
void game_uso_func_0000D5F8(void *, PM, int);
void game_uso_func_0000D5BC(void *, PM);
}
#define AT(T,b,o) (*(T *)((char *)(b) + (o)))
#define I(b,o) AT(int,b,o)
#define P(b,o) AT(char *,b,o)
extern "C" int game_uso_func_0000E35C(char *s0) {
    char *f4;
    if (P(s0, 0xF0) != 0) {
        game_uso_func_0000EE30(s0, I(P(s0, 0xF0), 0x30), 1);
        if (I(P(s0, 0xB4), 0xA58) & 0x20) {
            int base = (int)game_uso_D_807FFBC0;
            import_000B8518(I(&import_800201D0, 0x138), P(s0, 0xB4),
                ((base + (I(P(s0, 0xF0), 0x3C) << 6)) - base) / 64);
        } else {
            import_000B8518(I(&import_800201D0, 0x138), P(s0, 0xB4),
                ((int)P(s0, 0xF0) - (int)game_uso_D_807FFBC0) / 64);
        }
        I(s0, 0x100) = I(s0, 0x100) + 1;
        P(s0, 0xF4) = P(s0, 0xF0);
        P(s0, 0xF0) = 0;
        if (P(s0, 0xF8) == P(s0, 0xF4)) { I(s0, 0x100) = 0; }
        P(s0, 0xF8) = P(s0, 0xF4);
        game_uso_func_0000E564(s0);
        if ((I(P(s0, 0xB4), 0xA58) & 0x40) && I(P(s0, 0xF4), 0x28) != 0) {
            I(P(s0, 0xF4), 0x20) = I(P(s0, 0xF4), 0x28);
        } else {
            I(P(s0, 0xF4), 0x20) = I(P(s0, 0xF4), 0x24);
        }
        f4 = P(s0, 0xF4);
        if (I(f4, 0x38) & 2) {
            game_uso_func_077C44(s0, I(f4, 0x20), 0, 2, 1, 1);
            game_uso_func_0000D5F8(s0, AT(PM, &game_uso_D_807FF4B0, 0xEC0), 2);
        } else {
            game_uso_func_077C44(s0, I(f4, 0x20), 0, 3, 1, 1);
            game_uso_func_0000D5F8(s0, AT(PM, &game_uso_D_807FF4B8, 0xEC8), 3);
        }
        game_uso_func_0000D5BC(s0, AT(PM, &game_uso_D_807FF4C0, 0xED0));
        return 1;
    }
    return 0;
}
