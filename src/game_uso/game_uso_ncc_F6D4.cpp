/* IDO 7.1 NCC (C++) donor for game_uso_func_0000F6D4 (0x210 / 132 words).
 *
 * Node-process / queue-advance handler, sibling of E35C: optional D6E4
 * pre-flush (cur->0x38 & 1), EE30(self, active->0x30, 1), B8518 index call
 * (ceil-div-by-64 of the node offset, two forms on obj->0xA58 & 0x20),
 * counter++ / F4 = F0 / F0 = 0, reset the counter when F8 == F4, F8 = F4,
 * E564(self), then the 0xA58 & 0x40 / cur->0x28 select into cur->0x20 and
 * the 077C44 + D5F8 (PMF by value) pair on cur->0x38 & 2, then D5BC.
 *
 * C++ / edg facts this body depends on (the cfe wrap capped at 95.4%):
 *  - edg emits the ceil-div (base + (n << 6)) - base addu base-first
 *    (cfe always put the shift operand first).
 *  - There is NO named prev local: the target's t0 / t1 are expression temps.
 *    The F0 -> F4 move is written through the members, and the F8 compare
 *    and store re-read F4. A named local colours v0 and shifts every later
 *    temp by one register.
 *  - The compare is F8 == F4 (gives bne t0,t1); F4 == F8 swaps them.
 *  - The pairs passed to D5F8 / D5BC are pointers to members (by value).
 * Spliced into game_uso.c.o via REPLACE_FUNC_BODY
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
void game_uso_func_0000D6E4(void *);
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
extern "C" void game_uso_func_0000F6D4(char *s0) {
    char *f4;
    if (I(P(s0, 0xF4), 0x38) & 1) {
        game_uso_func_0000D6E4(s0);
    }
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
        game_uso_func_077C44(s0, I(f4, 0x20), 4, 2, 1, 1);
        game_uso_func_0000D5F8(s0, AT(PM, &game_uso_D_807FF4B0, 0xEC0), 2);
    } else {
        game_uso_func_077C44(s0, I(f4, 0x20), 4, 3, 1, 1);
        game_uso_func_0000D5F8(s0, AT(PM, &game_uso_D_807FF4B8, 0xEC8), 3);
    }
    game_uso_func_0000D5BC(s0, AT(PM, &game_uso_D_807FF4C0, 0xED0));
}
