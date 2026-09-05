/* game_libs_func_00029CCC -- keyframe/envelope stepper: 9-state machine on a
 * packed status byte, returns the current value clamped to [0,1].
 *
 * BOUNDARY FIX (2026-09-05, agent-c): ONE function that splat had split into
 * FOUR symbols: 29CCC (the 15-word `jr t6` jumptable dispatcher), 29D08 (the
 * case bodies, 181 words), 29FDC (8 words) and 29FFC (3 words) -- the last two
 * are the beql/bc1fl dup-first-insn null blocks of the [0,1] clamp epilogue
 * (see docs/MATCHING_WORKFLOW.md#feedback-beql-next-symbol-plus-4-is-mis-split-
 * branch-likely-block). Merged .s = 0x33C / 207 words; this C is 207/207
 * word-exact at IDO 7.1 -O2 (the 208th build word is .text alignment padding,
 * st_size == 0x33C).
 *
 * WIRED via REPLACE_FUNC_BODY donor splice into game_libs_post.c.o: a C
 * `switch` puts its jumptable in the donor's local .rodata; the splice renames
 * that reloc to game_libs_func_00029CCC_rodata, pinned in undefined_syms_auto
 * to the table the USO ships at data +0xFF0 (9 entries: 29CFC 29D08 29D28
 * 29D38 29E78 29F68 29EB0 29EB0 29F40). The three float literals are also
 * shipped in the USO data segment right after the table (+0x1014 = 32767.0f,
 * +0x1018 = 1e-5f) and at +0x2058 (0.017453292f = pi/180) -> baked extern pins.
 *
 * Load-bearing shapes (docs/IDO_CODEGEN.md):
 *  - `case 3:` label INSIDE the key-reading loop body (Duff's-device layout):
 *    the jumptable enters the loop body while the `continue` back edge targets
 *    the loop's own top, so uopt performs NO code motion on the loop (no
 *    preheader, `tbl`/-2/-3 stay inside, compare constants materialize in $at,
 *    `cnt` colors $a1). A plain `case 3: for(;;)` gets a 3-word preheader.
 *  - `unsigned char s` switch local -> `or v0,v1,zero; andi v0,v0,0xf` head.
 *  - inner case bodies laid out in SOURCE order: 0, -1, -2, -3, default.
 *  - unsigned-int bitfields in the status word: stores narrow to
 *    lbu/andi 0xFFF0/ori/sb, 1-bit flag tests read the word (lw; sll; bgezl).
 *  - `p->idx = 0;` before `p->state = 3;` (target store order). */
typedef struct {
    short dur;
    short val;
} EnvKey;

typedef struct {
    unsigned f80:1, f40:1, f20:1, f10:1, state:4;   /* byte 0 */
    unsigned idx:8;                                   /* byte 1 */
    short cnt;                                        /* +2 */
    float f4;
    float step;                                       /* +8 */
    float fC;
    float val;                                        /* +0x10 */
    float f14;
    int pad18;
    EnvKey *tbl;                                      /* +0x1C */
} Env;

extern float gl_ref_00001014_f;  /* 32767.0f */
extern float gl_ref_00001018_f;  /* 1e-5f */
extern float gl_ref_00002058_f;  /* 0.017453292f (pi/180) */

float game_libs_func_00029CCC(Env *p) {
    unsigned char s = p->state;
    float r;

    switch (s) {
    case 0:
        return 0.0f;
    case 1:
        if (p->f40) {
            p->state = 5;
            break;
        }
    case 2:
        p->idx = 0;
        p->state = 3;
        for (;;) {
    case 3:
            p->cnt = p->tbl[p->idx].dur;
            switch (p->cnt) {
            case 0:
                p->state = 0;
                break;
            case -1:
                p->state = 5;
                break;
            case -2:
                p->idx = p->tbl[p->idx].val;
                continue;
            case -3:
                p->state = 1;
                break;
            default:
                p->cnt = p->cnt * gl_ref_00002058_f;
                if (p->cnt == 0) {
                    p->cnt = 1;
                }
                p->f14 = p->tbl[p->idx].val / gl_ref_00001014_f;
                p->state = 4;
                p->idx++;
                p->f14 = p->f14 * p->f14;
                p->step = (p->f14 - p->val) / p->cnt;
                break;
            }
            break;
        }
        if (p->state != 4) {
            break;
        }
    case 4:
        p->cnt--;
        p->val += p->step;
        if (p->cnt <= 0) {
            p->state = 3;
        }
        break;
    case 5:
        break;
    case 6:
    case 7:
        p->val -= p->fC;
        if (p->f4 != 0.0f && s == 6) {
            if (p->val < p->f4) {
                p->val = p->f4;
                p->cnt = 0x80;
                p->state = 8;
            }
        } else {
            if (p->val < gl_ref_00001018_f) {
                p->val = 0.0f;
                p->state = 0;
            }
        }
        break;
    case 8:
        p->cnt--;
        if (p->cnt == 0) {
            p->state = 7;
        }
        break;
    }
    if (p->f20) {
        p->state = 6;
        p->f20 = 0;
    }
    if (p->f10) {
        p->state = 7;
        p->f10 = 0;
    }
    r = p->val;
    if (r < 0.0f) {
        return 0.0f;
    }
    if (r > 1.0f) {
        return 1.0f;
    }
    return r;
}
