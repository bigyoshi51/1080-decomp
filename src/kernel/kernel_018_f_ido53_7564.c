/* IDO 5.3 -O1 donor for func_80007564 — rmon thread-list command handler
 * (__rmonListThreads family; 77 insns, frame 0x30). PROVEN EXACT 77/77
 * (2026-07-10 standalone probe vs asm/nonmatchings/kernel/func_80007564.s;
 * only HI16/LO16(__rmonUtilityBuffer) + R_MIPS_26 reloc placeholders differ,
 * resolved at link). The parent unit kernel_018_f.c is IDO 7.1 -O1, which
 * caps 1 insn short: 7.1 folds the tail's `count*4` shift in place
 * (`sll a1,a1,2`) while the target (and 5.3) materialize it through a temp
 * (`sll t0,a1,2; or a1,t0,zero`) — the documented "clean C at -O1 never
 * re-materializes through the temp" residual is a 7.1-only property. Same
 * 5.3 -O1 island vein as osInitialize/osCartRomInit/osCreatePiManager.
 * All other levers (frame layout, msg-vs-m reload split, direct-global
 * store in the -1 arm, pad slot before ub) carried over unchanged from the
 * 2026-06-23 kernel_018_f.c rebuild. Spliced into kernel_018_f.c.o via
 * REPLACE_FUNC_BODY (real 5.3 -O1 output; donor relocs imported by the
 * splice). */
typedef signed int s32;

extern void func_800073F8();        /* __rmonSendHeader */
extern char __rmonUtilityBuffer;
extern char *func_80009C30(void);   /* __osGetActiveQueue */

s32 func_80007564(char *msg) {
    int pad;
    char *ub = &__rmonUtilityBuffer;
    register char *m = msg;
    register char *t;
    if (*(int*)(m + 0xC) == -1) {
        *(int*)(&__rmonUtilityBuffer + 0xC) = 0x3EA;
    } else {
        *(int*)(ub + 0xC) = *(int*)(m + 0xC);
    }
    if (*(unsigned char*)(msg + 0x9) == 1) {
        *(unsigned short*)(ub + 0x10) = 1;
        *(int*)(ub + 0x14) = 0x3E8;
    } else {
        t = func_80009C30();
        *(unsigned short*)(ub + 0x10) = 0;
        if (*(int*)(t + 0x4) != -1) {
            do {
                if (*(int*)(t + 0x14) != 0) {
                    ((int*)(ub + 0x14))[*(unsigned short*)(ub + 0x10)] = *(int*)(t + 0x14);
                    *(unsigned short*)(ub + 0x10) += 1;
                }
                t = *(char**)(t + 0xC);
            } while (*(int*)(t + 0x4) != -1);
        }
    }
    *(unsigned char*)(ub + 0x4) = *(unsigned char*)(m + 0x4);
    *(unsigned short*)(ub + 0x6) = 0;
    func_800073F8(ub, *(unsigned short*)(ub + 0x10) * 4 + 0x14, 1);
    return 0;
}
