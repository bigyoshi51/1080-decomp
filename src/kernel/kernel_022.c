#include "common.h"

/* Forward declarations */
extern s32 __osPiAccessQueue;
extern s32 D_8000A480;
extern s32 D_80013004;
extern void func_80005DC0(s32*, s32, s32);
extern void func_80005C00(void);
extern void func_80004FE0(s32*, s32*, s32);
extern void func_800053D0(s32*, s32*, s32);
extern s32 D_8000A3E0;
extern s32 func_800066B0(void);
extern void func_800066D0(s32);
extern void func_80003D0C(s32*);
extern void* D_8000A420;
extern s32 D_8000A418;
extern s32 siacs_bss_0000;
extern s32 func_800009D8(void*, s32, s32, void*);
extern void func_80003FF0(s32, void*);
extern void* func_80003E54(void*);
extern void func_8000A110(void*);
extern void func_8000857C(void);
extern void func_8000785C(s32);
extern void func_80008ED0(void);
extern void func_80007760(void);
typedef void (*FuncPtr2)(void*, void*);
extern FuncPtr2 D_80012C44;
extern s32 D_8000A32C;
extern s32 D_8000A340;
extern s32 D_80012BC0;
extern s32 D_8000A2E0;
extern s32 D_8000A41C;
extern s32 func_80002890(s32);
extern void func_8000A0E0(void);
extern void func_80005350(s32, s32);
extern void func_80005400(s32, s32);
extern s32 func_80008430(s32);
extern void func_80009148(s32);
extern void func_80009030(s32, s32);
extern void func_80008498(void);
extern s32 func_80006A98(s32);
extern void func_800091F0(s32);
typedef struct { s32 pad[3]; s32 position; } FileState;

typedef struct {
    void* mtqueue;
    void* fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    s32** msg;
} OSMesgQueue;

typedef struct Thread {
    s32 field0;
    s32 pri;
    s32 queue;
    s32 pad0C;
    u16 state;
} Thread;

typedef struct { s32 queue; s32 msg; } OSEventState;
extern OSEventState __osEventStateTab[];



INCLUDE_ASM("asm/nonmatchings/kernel", func_80008454);

INCLUDE_ASM("asm/nonmatchings/kernel", func_80008498);

INCLUDE_ASM("asm/nonmatchings/kernel", func_800084AC);

/* func_800084D0 (size 0xBC, was 0xAC): merged in former func_8000857C
 * fragment (4-insn epilogue at 0x8000857C — `lw $s0,0x14(sp); lw $s1,0x18(sp);
 * jr $ra; addiu $sp,+0x48`). func_8000857C was the natural tail of
 * func_800084D0 (its body ends at 0x80008578 with `lw $ra, 0x1C(sp)`).
 * Several callers — func_80008A08 etc — `jal 0x8000857C` directly to reuse
 * the restore-saved-regs+sp-pop+return sequence (cross-function shared-tail
 * entry, same pattern as func_80006640 → func_800065F0). The address is
 * re-exported via undefined_syms_auto.txt for those callers. */
INCLUDE_ASM("asm/nonmatchings/kernel", func_800084D0);

/* func_8000858C - verified structural decode (kernel, 0x228, 138
 * insns, rmon MIPS instruction decoder / branch-target helper).
 * Part of the rmon single-step / breakpoint machinery.
 *   void func_8000858C(s32 mode, void *ctx, void *addr) {
 *       u32 insn = (mode == 1) ? func_80006A98((u32)addr) // reg rd
 *                              : *(u32*)addr;             // mem rd
 *       u32 op = (insn >> 26) & 0x3F;                     // opcode
 *       if (op >= 0x18) return;                            // guard
 *       switch (op) {                                      // jtbl_
 *           ...                                            //  8000AA90
 *           // SPECIAL (op 0): sub-decode funct, jr/jalr (8/9):
 *           //   rs = (insn >> 21) & 0x1F; ...
 *           //   func_80009B60(ctx, ctx2, rs);   // -> target
 *           // REGIMM / branch / jump classes: extract rs/rt/
 *           //   offset, compute the branch/jump destination
 *           //   (uses jtbl_8000AAF0 sub-table)
 *       }
 *   }
 * Struct-typing reference: classic MIPS field extraction - opcode
 * = bits 31..26, rs = bits 25..21 (>>21 &0x1F), rt = bits 20..16
 * (>>16 &0x1F), rd = bits 15..11, funct = bits 5..0 (&0x3F), the
 * SPECIAL jr/jalr funct = 8/9. func_80006A98 = the MMIO/cop
 * register read (mode 1 reads the live register file); func_
 * 80009B60 = the branch/jump-target resolver (a0=ctx, a1=ctx2,
 * a2=register index) used to find where a control-transfer
 * instruction will go (for setting the single-step / temp
 * breakpoint after a branch). jtbl_8000AA90 = 24-entry opcode
 * dispatch, jtbl_8000AAF0 = a secondary (REGIMM/funct) table.
 * This is the disassembler half of rmon hardware single-step.
 * Caps <80: two jump tables (jr $t1) + heavy bitfield sra/andi
 * extraction + mode branch + reloc callees.
 *
 * HARD INFRA CAP (verified 2026-06-23, agent-e): the two jump
 * tables are referenced by the absolute symbols jtbl_8000AA90 /
 * jtbl_8000AAF0 (encoded lui 0x8001 + lo -0x5570 => 0x8000AA90),
 * which splat assigned into the kernel .data blob (vram base
 * 0x80009FD0, assets/kernel.data.bin). BUT at data off 0xAC0
 * (vram 0x8000AA90) the blob holds AUDIO COEFFICIENT data, not
 * code-address pointers — splat mislabeled the address (cf.
 * jtbl_8000A720 @ data off 0x750 which DOES hold real pointers
 * 0x80008B9C/0x80008AB4, and jtbl_8000A63C/A64C/A770 which point
 * into rmon STRING data "HitBreak"/"SetRegisters"). An exhaustive
 * baserom scan finds NO run of words in the case-target range
 * 0x800085F0..0x800087B0 anywhere — the true 24/20-entry table
 * for this fn is not correctly extracted by the current splat
 * layout. This is the documented drift-region relayout cap
 * (residue=414 reloc words). A C switch reconstruction would emit
 * a duplicate compiler jumptable into .rodata at the wrong
 * address and BREAK the byte-identical ROM. Cannot match without
 * fixing the kernel .data/.rodata relayout first. Full body
 * INCLUDE_ASM-preserved (.s = source of truth). INCLUDE_ASM (no
 * episode; tautology-trap rule). */
INCLUDE_ASM("asm/nonmatchings/kernel", func_8000858C);
