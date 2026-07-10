/* -O1 donor for gl_func_0006BF34 — 81-insn struct-init constructor
 * (frame 0x28, saves ra+s0). PROVEN EXACT 81/81 at both IDO 7.1 and 5.3
 * -O1 (2026-07-09 standalone probe); built here with 7.1 (plain -O1).
 * The host post1b2 builds -O2, where the arg homes/reloads collapse — the
 * target is simply -O1: every self-> store reloads the homed a0.
 * Levers: (1) `register int tmp` — the fn1() result crosses two statements
 * and must color s0 (plain local memory-homes to a spill slot, no s0 save);
 * (2) decl order `register tmp; unsigned local` puts local at 0x20 (tmp
 * first = declared slot order, local next);
 * (3) `unsigned int local` — (local & 0x3F0000) >> 16 must emit srl (int
 * emits sra);
 * (4) ll240 = (long long)a4 - 16 gives the sltiu-borrow/subu pair; ll256 =
 * (int)D_e gives the sra-31 sign-extend of a symbol address.
 * Spliced into game_libs_post1b2.c.o via REPLACE_FUNC_BODY (real -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef struct {
    int f0;                 /* 0x00 */
    int f4;                 /* 0x04 */
    int f8;                 /* 0x08 */
    int f12;                /* 0x0C */
    short s16;              /* 0x10 */
    short s18;              /* 0x12 */
    int f20;                /* 0x14 */
    int f24;                /* 0x18 */
    char pad28[28];         /* 0x1C */
    long long ll56;         /* 0x38 */
    char pad64[176];        /* 0x40 */
    long long ll240;        /* 0xF0 */
    char pad248[8];         /* 0xF8 */
    long long ll256;        /* 0x100 */
    char pad264[16];        /* 0x108 */
    int f280;               /* 0x118 */
    int f284;               /* 0x11C */
    char pad288[8];         /* 0x120 */
    int f296;               /* 0x128 */
    int f300;               /* 0x12C */
} S;
extern int D_00000000_e[];
extern int D_00000000_f;
extern S *D_00000000_g;
extern int gl_func_00000000();
extern void gl_func_00000001(int);
void gl_func_0006BF34(S *self, int a1, int a2, int a3, int a4, int a5) {
    register int tmp;
    unsigned int local;
    self->f20 = a1;
    self->f4 = a5;
    self->f0 = 0;
    self->f8 = 0;
    self->f284 = a2;
    self->ll56 = a3;
    self->ll240 = (long long)a4 - 16;
    self->ll256 = (int)D_00000000_e;
    local = 0x3FFF01;
    self->f280 = 0xFF03;
    self->f296 = (local & 0x3F0000) >> 16;
    self->f300 = 0x1000800;
    self->f24 = 0;
    self->s16 = 1;
    self->s18 = 0;
    tmp = gl_func_00000000();
    self->f12 = D_00000000_f;
    D_00000000_g = self;
    gl_func_00000001(tmp);
}
