/* IDO 5.3 -O1 donor for gl_func_00071708 — 48-insn record-stream emitter
 * with 6-byte template (frame 0x10, leaf). PROVEN EXACT 48/48 (2026-07-09
 * verify; 7.1 -O1 emits the same shape but colors the template struct-copy
 * scratch $t1/$t0 — only 5.3 uses $at, the target's register). The target
 * .s carries one TRAILING word (lui $t6 at 0x717C8) that is really
 * gl_func_000717CC's stolen prologue; it is emitted by the new 1-word
 * orphan game_libs_func_000717C8.s in the host, so this donor covers
 * exactly 0x71708..0x717C4. post2 builds -O2. Levers:
 *   (1) 6-byte struct/union template built field-by-field in the sp home,
 *       then `*(Tmpl *)cursor = tmpl` struct-copy = the target's unaligned
 *       swl/swr 4-byte pair + 2 byte stores;
 *   (2) Ctl struct with f3c at +0x3C gives the `&D + 0x3C = 1` store its
 *       own base reload (no CSE with the byte clear at &D_a);
 *   (3) plain counted for-loop zeroes the leading bytes via the cursor
 *       (per-iteration sb/addiu, guard at bottom).
 * Spliced into game_libs_post2.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef struct { unsigned char b[6]; } Rec6;
typedef union {
    Rec6 r;
    struct { unsigned char b0, b1, b2, b3, b4, b5; } f;
} Tmpl;
typedef struct { int pad[15]; int f3c; } Ctl;
extern unsigned char D_00000000_a;
extern Ctl D_00000000_b;
extern unsigned char D_00000000_c[];

void gl_func_00071708(int count) {
    unsigned char *cursor;
    Tmpl tmpl;
    int i;

    D_00000000_a = 0;
    D_00000000_b.f3c = 1;
    cursor = D_00000000_c;
    tmpl.f.b0 = 1;
    tmpl.f.b1 = 3;
    tmpl.f.b2 = 0;
    tmpl.f.b3 = 0xFF;
    tmpl.f.b4 = 0xFF;
    tmpl.f.b5 = 0xFF;
    for (i = 0; i < count; i++) {
        *cursor = 0;
        cursor++;
    }
    *(Tmpl *)cursor = tmpl;
    cursor += 6;
    *cursor = 0xFE;
}
