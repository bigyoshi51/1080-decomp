/* IDO 5.3 -O1 donor for gl_func_0006C1B8 — 59-insn table-reset + 8-byte
 * record emitter, reset-sibling of gl_func_0006BD14 and same family as the
 * landed gl_func_0006C11C decoder (frame 0x10, leaf). PROVEN EXACT 59/59
 * (2026-07-09 standalone probe). 5.3 required: it colors the struct-copy
 * scratch $at for the swl/swr pair (7.1 uses $t-regs — 44/59 floor).
 * Levers:
 *   (1) FOR-loop shape for the emit loop — `for (i = 0; i < D_a; i++)
 *       { *(Rec*)cursor = tmp; cursor += 1; }` — is what puts sw-i before
 *       the bne and sinks the cursor store into the branch delay slot.
 *       Every do-while/comma spelling emits the two sw's swapped (57/59
 *       floor, verified exhaustively). The for-guard also provides the
 *       entry blez.
 *   (2) decl order cursor, tmp, i = slots 12 / 4..11 / 0;
 *   (3) `Zeros` struct-member flag — D_c.flag (offset 60) emits the
 *       $at-fused single-lui `sw t1,60(at)` (an int D_d extern emits its
 *       own lui; indexing D_c[15] array-decays to an addiu base ✗);
 *   (4) union Rec view: u16 h member = the `sh 0xFFFF` middle store.
 * Spliced into game_libs_post1b2.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef struct { unsigned char raw[8]; } RecBytes;
typedef union {
    RecBytes b;
    struct { unsigned char b0, b1, b2, b3; unsigned short h; signed char b6, b7; } f;
} Rec;
typedef struct { int arr[15]; int flag; } Zeros;
extern unsigned char D_00000000_a;
extern RecBytes D_00000000_b[];
extern Zeros D_00000000_c;
void gl_func_0006C1B8(void) {
    RecBytes *cursor;
    Rec tmp;
    int i;
    cursor = D_00000000_b;
    for (i = 0; i < 15; i++) {
        D_00000000_c.arr[i] = 0;
    }
    D_00000000_c.flag = 1;
    tmp.f.b0 = 0xFF;
    tmp.f.b1 = 1;
    tmp.f.b2 = 4;
    tmp.f.b3 = 1;
    tmp.f.h = 0xFFFF;
    tmp.f.b6 = -1;
    tmp.f.b7 = -1;
    for (i = 0; i < D_00000000_a; i++) {
        *(Rec *)cursor = tmp;
        cursor += 1;
    }
    cursor->raw[0] = 0xFE;
}
