/* IDO 7.1 NCC (C++) donor for game_uso_func_0000D204 (0x214 / 133 words).
 *
 * game_uso was written in C++ and compiled by IDO 7.1's own C++ driver NCC
 * (edg front end). The `if (pm != null) (this->*pm)();` block below is an
 * edg-lowered cfront-layout pointer-to-member-function test + call (memberwise
 * 2-word compare loop through `at` with `addi`, then the delta/index/vptr
 * dispatch with the class's vptr at +40); cfe cannot emit it (the old C NM
 * wrap capped at 85.8%). Built by the explicit NCC rule in the Makefile
 * (no asm-processor, no GLOBAL_ASM) and spliced into game_uso.c.o via
 * REPLACE_FUNC_BODY; this unit is never linked on its own.
 * docs/IDO_CODEGEN.md#game-uso-is-cplusplus-ncc-pmf-compare-d204,
 * docs/MATCHING_WORKFLOW.md#game-uso-ncc-cplusplus-donor-recipe.
 *
 * Every symbol is extern "C" so names stay unmangled for the splice's reloc
 * import. Comparing against the extern null PMF at game_uso_D_807FF3B8+0xDC8
 * (not literal 0) makes edg reference the USO's null object instead of
 * emitting its own .data copy. NCC wants `0x104 != 0x74` (cfe wanted the
 * reverse) for the same `beq a1,t9`. */
extern "C" {
extern char import_80020098;
extern char game_uso_D_807FF68C;
extern char game_uso_D_807FF3B8;
extern char D_00000000;
void game_uso_func_07C0C0(int, char *, int);
void game_uso_func_0000D9CC(void *);
void game_uso_func_0000ECE8(void *);
void game_uso_func_076E78(int, int);
void game_uso_func_0775F8(void *);
}
struct A { char pad[40]; virtual void m(); };
typedef void (A::*PM)();
struct H : A { char pad2[200-44]; PM pm; };
#define I(b,o) (*(int *)((char *)(b) + (o)))
#define F(b,o) (*(float *)((char *)(b) + (o)))
extern "C" void game_uso_func_0000D204(H *a0) {
    H *a3 = a0;
    if (I(&import_80020098, 0x64) == 0) {
        float th = F(&D_00000000, 0x1F4);
        if (F(I(a0, 0xB4), 0xBC) < th) {
            I(a0, 0x120) = 0;
        }
        if (F(I(a0, 0xB4), 0xBC) < th) goto clear_bits;
        if (I(a3, 0x120) == 0) goto set_bits;
    clear_bits:
        { int *child = (int *)(I(&import_80020098, 0x138) + 0xB4); *child &= ~3; }
        goto bits_done;
    set_bits:
        { int *child = (int *)(I(&import_80020098, 0x138) + 0xB4); *child |= 3; }
    bits_done:;
    }
    {
        int v0 = I(a3, 0xB4);
        if (I(v0, 0x938) == 0 && F(v0, 0x9D0) < 700.0f && F(v0, 0x31C) < -100.0f) {
            game_uso_func_07C0C0(I(v0, 0x800), &game_uso_D_807FF68C + 4252, 1);
        }
    }
    if (I(a3, 0x114) != 0) game_uso_func_0000D9CC(a3);
    if (a3->pm != *(PM *)(&game_uso_D_807FF3B8 + 0xDC8)) (a3->*(a3->pm))();
    game_uso_func_0000ECE8(a3);
    if (I(a3, 0x74) != 0) {
        game_uso_func_076E78(I(a3, 0x58), I(a3, 0x74));
        if (I(a3, 0x104) != I(a3, 0x74)) I(a3, 0x104) = I(a3, 0x74);
    }
    game_uso_func_0775F8(a3);
}
