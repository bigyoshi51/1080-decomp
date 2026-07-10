/* IDO 5.3 -O1 donor for gl_func_0006D0F4 — 95-insn 40-byte-record builder
 * (frame 0x48, saves ra; one jal). PROVEN EXACT 95/95 (2026-07-09
 * standalone probe; 7.1 -O1 = 76/95, $at struct-copy scratch again).
 * Zeroes out[0..14], sets out[15]=1, builds a 40-byte record {0xFF,35,1,3,
 * h4 = fn(x) | x<<5, data[32] from src, b38=0xFF}, optionally zero-fills
 * `count` bytes at the cursor, then struct-copies the record to the cursor
 * (IDO's 12-byte-chunk swl/swr copy loop with $at scratch), advances 40,
 * writes 0xFE terminator.
 * Levers:
 *   (1) FOR-loop shape for BOTH byte loops (see the 6C1B8 donor note):
 *       `for (i=0;i<32;i++){ buf.data[i]=*src; src+=1; }` (constant bound
 *       folds the entry guard) and `if (count != 0) for (i=0;i<count;i++)
 *       { *cursor=0; cursor+=1; }` (the != 0 wrapper gives the extra beq
 *       before the for's blez);
 *   (2) decl order cursor, buf, i = slots 68 / 28..67 / 24;
 *   (3) u16 param x: lhu arg-home reloads; h4 = fn(x) | (x << 5);
 *   (4) `*(Buf *)cursor = buf` with align-2 Buf = the unrolled x3
 *       swl/swr copy loop + tail word.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef struct {
    unsigned char b0, b1, b2, b3;   /* 0-3 */
    unsigned short h4;              /* 4-5 */
    unsigned char data[32];         /* 6-37 */
    unsigned char b38, b39;         /* 38-39 */
} Buf;
extern int gl_func_00000000(unsigned short);
void gl_func_0006D0F4(int count, unsigned short x, unsigned char *src, int *out) {
    unsigned char *cursor;
    Buf buf;
    int i;
    cursor = (unsigned char *)out;
    for (i = 0; i < 15; i++) {
        out[i] = 0;
    }
    out[15] = 1;
    buf.b0 = 255;
    buf.b1 = 35;
    buf.b2 = 1;
    buf.b3 = 3;
    buf.h4 = gl_func_00000000(x) | (x << 5);
    buf.b38 = 255;
    for (i = 0; i < 32; i++) {
        buf.data[i] = *src;
        src += 1;
    }
    if (count != 0) {
        for (i = 0; i < count; i++) {
            *cursor = 0;
            cursor += 1;
        }
    }
    *(Buf *)cursor = buf;
    cursor += 40;
    *cursor = 0xFE;
}
