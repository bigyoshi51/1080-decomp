/* IDO 5.3 -O1 donor for func_8000698C — rmon memory-write handler (147
 * insns, frame 0x48). PROVEN EXACT 147/147 (2026-07-10 standalone probe vs
 * asm/nonmatchings/kernel/func_8000698C.s; only R_MIPS_26 jal placeholders
 * differ, resolved at link). 5th 5.3-vs-7.1 temp-rematerialization crack
 * (7564/8264/87B4/70A0 family). The documented "coloring + frame-layout
 * cap" (deferred `move s0,t6` prologue + slot-offset cascade) decomposes
 * into FOUR levers, all C-reachable at 5.3 -O1:
 *   (1) STRUCTURE FIX: the byte-merge is an if/else-if/else CHAIN (the ==1
 *       and ==2 merges `b` past the low-byte merge), not three independent
 *       ifs — the old NM body's shape was wrong.
 *   (2) PROLOGUE: first byte-read through the RAW PARAM (`*(u8*)((char*)
 *       sp48 + 9)`) with `arg0 = sp48` as a separate statement — the reload
 *       CSEs to the param temp (lbu t7,9(t6)) and the s0 commit stays a
 *       distinct `or s0,t6,zero` (build otherwise folds to `lw s0,home`).
 *   (3) FRAME MAP: IDO 5.3 -O1 gives EVERY `register` var a dead 4-byte
 *       home slot allocated in strict decl order (first decl = highest),
 *       exactly like homed locals. Target layout = `register arg0`
 *       declared FIRST (dead home 0x44), then struct (0x34) / sp30 / sp2C /
 *       sp28 / sp24 (0x24), then `register var_s1` LAST (dead home 0x20)
 *       -> frame 0x48. With both register decls adjacent the two dead homes
 *       fuse at one end and every slot shifts +4/+8.
 *   (4) ORDER TIES: word-loop init `sp28 = len>>2;` BEFORE `sp24 = ptr;`
 *       (lw-first ugen numbering t4/t5/t6); SP-range sum spelled
 *       `FW(0x14) + FW(0x10)` (len-first load pair); reply tail store
 *       order tag -> zero -> id (8264 lever).
 * Spliced into kernel_018_b.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * output; donor relocs imported by the splice). NOTE: target contains a
 * mid-function jal to 0x80006AEC (the merge-store join inside THIS
 * function) — from the compiler's view it is a plain extern call
 * (R_MIPS_26 func_80006AEC), resolved by undefined_syms_auto.txt. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;
typedef signed short s16;
#define FW(p, o) (*(s32 *)((char *)(p) + (o)))
extern s32 func_80004B30(u32);
extern s32 func_80006A98(s32);
extern void func_80006A50(s32, s32);
extern void func_80006AEC(s32, void *, s32);
extern void func_800073F8(void *, s32, s32);

s32 func_8000698C(void *sp48) {
    register void *arg0;
    struct { s32 w0; u8 tag; u8 p5; s16 zero; s32 w8; s32 id; } sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    s32 *sp24;
    register s32 var_s1;

    arg0 = sp48;
    if ((*(u8 *)((char *) sp48 + 9) == 0) && (func_80004B30(FW(arg0, 0x10)) == -1)) {
        return -5;
    }
    if ((u32) FW(arg0, 0x14) >= 0x401U) {
        return -8;
    }
    if (((u32) FW(arg0, 0x10) < 0x04000000U) || ((u32) (FW(arg0, 0x14) + FW(arg0, 0x10)) >= 0x05000000U)) {
        var_s1 = 0;
    } else {
        var_s1 = 1;
    }
    if (var_s1 != 0) {
        sp30 = FW(arg0, 0x10) & 3;
        if (sp30 != 0) {
            if (FW(arg0, 0x14) != 1) {
                return -5;
            }
            sp2C = func_80006A98(FW(arg0, 0x10) & ~3);
            if (sp30 == 1) {
                sp2C = (*(u8 *)((char *) arg0 + 0x18) << 0x10) | (sp2C & 0xFF00FFFF);
            } else if (sp30 == 2) {
                sp2C = (*(u8 *)((char *) arg0 + 0x18) << 8) | (sp2C & 0xFFFF00FF);
            } else {
                sp2C = *(u8 *)((char *) arg0 + 0x18) | (sp2C & ~0xFF);
            }
            func_80006A50(FW(arg0, 0x10) & ~3, sp2C);
            goto block_26;
        }
        sp28 = (u32) FW(arg0, 0x14) >> 2;
        sp24 = (s32 *)((char *) arg0 + 0x18);
        if (FW(arg0, 0x14) & 3) {
            return -5;
        }
        var_s1 = sp28;
        sp28 -= 1;
        if (var_s1 != 0) {
            do {
                func_80006A50(FW(arg0, 0x10), *sp24++);
                FW(arg0, 0x10) = FW(arg0, 0x10) + 4;
                var_s1 = sp28;
                sp28 -= 1;
            } while (var_s1 != 0);
        }
        goto block_26;
    }
    func_80006AEC(FW(arg0, 0x10), (char *) arg0 + 0x18, FW(arg0, 0x14));
block_26:
    sp34.tag = *(u8 *)((char *) arg0 + 4);
    sp34.zero = 0;
    sp34.id = FW(arg0, 0xC);
    func_800073F8(&sp34, 0x10, 1);
    return 0;
}
