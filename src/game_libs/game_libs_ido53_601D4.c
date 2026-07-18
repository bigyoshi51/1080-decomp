/* IDO 5.3 -O2 -mips2 donor for gl_func_000601DC = lazy-init tracker
 * update. PROVEN EXACT 30/30 standalone against the 0x601D4..0x60248
 * stream (the .s was already boundary-merged 2026-05-30: splat's 2-word
 * `lui $t6; lw $t6,0(t6)` pre-prologue head, true entry 0x601D4, 0x78).
 * The old "caller-set $t6" reading was falsified then; this donor
 * resolves the REMAINING "register/spill allocation around the two
 * calls" residual: it is the 5.3 fingerprint + decl order.
 * Body: v1 = trk->f40; if (!v1) init(&D+0x21CA4); v0 = get() [no args —
 * $a0 is hoisted above the branch for the conditional init call only];
 * v1->f04 = v0; v1->f08 += v0 - v1->f00; trk->f40 = v1->f20 (fused
 * lui/lw reload of the trk global after the v1 stores — aliasing);
 * return v1->f08 (re-read after the trk store).
 * COMPILER FINGERPRINT: IDO 5.3 -O2 -mips2 (7.1 diverges on the
 * jal-delay v1 spill pattern; mips1 pads load-use with hazard nops).
 * `Rec *v1` declared BEFORE `int v0` is load-bearing: decl order ranks
 * v1's cross-call spill at 0x1C not 0x18 (NOTE: 669AC donor needed the
 * OPPOSITE order — the knob is per-function, brute-force both).
 * The string arg is the full-addend form (char*)D_00000000 + 0x21CA4:
 * the assembler bakes hi=2 into the lui imm and lo=0x1CA4 into the
 * addiu under the HI16/LO16 relocs — this is how a "baked-USO-symbol"
 * lui;addiu pair IS reachable at .o level (addend, not int literal).
 * Blank externs: D_00000000_trk601 = tracker-state ptr global;
 * gl_func_00000000_init601 / _get601 = the two blank jals.
 * Spliced into game_libs_post0b.c.o via REPLACE_FUNC_BODY. */
typedef struct {
    int f00;            /* 0x00 */
    int f04;            /* 0x04 — last sample (= get() return) */
    int f08;            /* 0x08 — accumulator */
    char pad0c[0x14];   /* 0x0C */
    int f20;            /* 0x20 — next record link */
} Rec601;

typedef struct {
    char pad00[0x40];   /* 0x00 */
    Rec601 *f40;        /* 0x40 — current record */
} Trk601;

extern Trk601 *D_00000000_trk601;
extern char D_00000000[];
extern void gl_func_00000000_init601();
extern int gl_func_00000000_get601();

int gl_func_000601DC(void) {
    Rec601 *v1 = D_00000000_trk601->f40;
    int v0;

    if (v1 == 0) {
        gl_func_00000000_init601((char *)D_00000000 + 0x21CA4);
    }
    v0 = gl_func_00000000_get601();
    v1->f04 = v0;
    v1->f08 = v1->f08 + v0 - v1->f00;
    D_00000000_trk601->f40 = (Rec601 *)v1->f20;
    return v1->f08;
}
