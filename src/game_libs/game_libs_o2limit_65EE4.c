/* NM-only compiler donor for game_libs_func_00065EE4.
 * IDO 7.1 -O2 -Olimit 1 uses the size-limit fallback, NOT plain -O1.
 * All 146 instructions are emitted by the compiler. The default parent
 * object keeps its original INCLUDE_ASM; this donor is used only by the
 * non_matching comparison build. No exact episode is warranted yet.
 * Keep this C body synchronized with the parent post1b NM body.
 * See docs/IDO_CODEGEN.md#size-limit-fallback-65ee4.
 */
typedef struct {
    char pad0[8];
    int f8, fC;          /* 0x08, 0x0C: words read back from base / base+4 */
    char pad1[0x14];
    int data;            /* 0x24: base + 0x10 */
    int base;            /* 0x28 */
    int end;             /* 0x2C: base + 0x10 + size */
    int size;            /* 0x30 */
    int f34;             /* 0x34: cleared before the successor call */
} Save65EE4;
extern Save65EE4 D_65EE4_g;   /* sym1520 (BSS 0x3F030), = 0 in undefined_syms_auto.txt */
extern int func_00000000();
#define SAVE65EE4_BLOCK(B, SZ) \
    D_65EE4_g.base = (B); D_65EE4_g.data = (B) + 0x10; \
    D_65EE4_g.size = (SZ); D_65EE4_g.end = (B) + 0x10 + (SZ); \
    func_00000000(&D_65EE4_g, (B) + 4, D_65EE4_g.data); \
    func_00000000(&D_65EE4_g, D_65EE4_g.base, D_65EE4_g.data); \
    D_65EE4_g.f8 = func_00000000(&D_65EE4_g, D_65EE4_g.base); \
    D_65EE4_g.fC = func_00000000(&D_65EE4_g, D_65EE4_g.base + 4); \
    D_65EE4_g.f34 = 0; \
    func_00000000(&D_65EE4_g);
void game_libs_func_00065EE4(void) {
    SAVE65EE4_BLOCK(0xB1FF0000, 0x2700)
    SAVE65EE4_BLOCK(0xB1FF2710, 0x9C30)
    SAVE65EE4_BLOCK(0xB1FFC350, 0x2700)
}
