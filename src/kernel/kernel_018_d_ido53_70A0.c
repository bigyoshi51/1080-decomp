/* IDO 5.3 -O1 donor for func_800070A0 — rmon word-streamer (72 insns,
 * frame 0x38). PROVEN EXACT 72/72 (2026-07-10 standalone probe vs
 * asm/nonmatchings/kernel/func_800070A0.s; only R_MIPS_26 jal placeholders
 * differ, resolved at link). 4th 5.3-vs-7.1 temp-rematerialization crack
 * (7564/8264/87B4 family). Two levers on top of the 2026-06-23 7.1 rebuild:
 *   (1) `int *p` + POST-INCREMENT at the use site (`func(p++)`, `*p++`)
 *       instead of `p += 4; func(p - 4)`. 5.3 -O1 materializes the
 *       post-increment through the old value: keeps old p in t2/t4, incs
 *       into a NEW reg (addiu t3,t2,4), and passes the OLD reg
 *       (`move a0,t2` / `lw a0,0(t4)`) — the documented "cart move a0,t2
 *       (keep old-p) vs addiu a0,t3,-4 (recompute)" + "lw a0,0(t4) vs
 *       lw a0,-4(t5)" residuals that no 7.1 C shape resolves (7.1 -O1
 *       folds the -4 into the operand either way).
 *   (2) everything else (decl order p/n/tmp/tmp2 for the frame slots,
 *       aligned path as if-BODY, both SP-range bounds) carried over
 *       unchanged from the 7.1 rebuild.
 * NEGATIVE for the record: the explicit `char *oldp = p; p += 4;` temp
 * form does NOT work at 5.3 -O1 — named locals always get a stack home
 * (frame 0x38 -> 0x40, +4 insns); only the post-increment expression temp
 * stays register-only. Spliced into kernel_018_d.c.o via REPLACE_FUNC_BODY
 * (real 5.3 -O1 output; donor relocs imported by the splice). */

extern void func_80006AEC(void *dst, void *src, int n);
extern void func_80005584(int word);
extern void func_80008FB0(void *src, void *dst);
extern void func_80005534(void);

void func_800070A0(char *addr, int len) {
    int *p = (int *)addr;
    unsigned int n = ((unsigned int)len + 3) >> 2;
    int tmp;
    int tmp2;
    if (!((unsigned int)addr & 3)) {
        while (n--) {
            if ((unsigned int)p >= 0x04000000U && (unsigned int)p < 0x05000000U) {
                func_80008FB0(p++, &tmp);
                func_80005584(tmp);
            } else {
                func_80005584(*p++);
            }
        }
    } else {
        while (n--) {
            func_80006AEC(&tmp2, p, 4);
            func_80005584(tmp2);
            p++;
        }
    }
    func_80005534();
}
