/* IDO 5.3 -O1 donor for gl_func_0006C11C — 42-insn 8-byte-record decoder
 * loop (frame 0x18, leaf). PROVEN EXACT 42/42 (2026-07-09 verify; 7.1 -O1
 * emits the same shape but colors the struct-copy scratch $t1/$t0 — only
 * 5.3 uses $at as the lwl/lwr block-copy scratch, the target's registers).
 * ABSORBS the 3-word orphan game_libs_func_0006C110 (its lui/lbu pair is
 * this function's stolen count-preload prologue): the donor's true entry is
 * 0x6C110 and the splice covers 0x6C110..0x6C1B8 (orphan INCLUDE_ASM
 * removed from the host). post1b2 builds -O2. Levers:
 *   (1) struct-copy `tmp = *(Rec *)cursor` of an 8-byte struct = the
 *       target's lwl/lwr pair loads into the sp home (0x10/0x14);
 *   (2) union field view gives the byte/halfword extracts from the home
 *       (lbu 0x12(sp) / lhu 0x14(sp) / lb 0x16/0x17(sp));
 *   (3) comma-expression loop bottom `++i < ((cursor += 1), (int)D_a)`
 *       sinks the cursor advance before the guard's lbu reload of the
 *       count global (per-iteration reload, no registerization).
 * Spliced into game_libs_post1b2.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef struct { unsigned char raw[8]; } RecBytes;
typedef union {
    RecBytes b;
    struct { unsigned char b0, b1, b2, b3; unsigned short h; signed char b6, b7; } f;
} Rec;
extern unsigned char D_00000000_a;
extern RecBytes D_00000000_b[];
void gl_func_0006C11C(unsigned char *out) {
    RecBytes *cursor;
    Rec tmp;
    int i;
    cursor = D_00000000_b;
    i = 0;
    if (D_00000000_a > 0) {
        do {
            tmp = *(Rec *)cursor;
            out[4] = (tmp.f.b2 & 0xC0) >> 4;
            if (out[4] == 0) {
                *(short *)out = tmp.f.h;
                out[2] = tmp.f.b6;
                out[3] = tmp.f.b7;
            }
            out += 6;
        } while (++i < ((cursor += 1), (int)D_00000000_a));
    }
}
