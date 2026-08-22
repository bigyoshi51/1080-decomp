#include "common.h"




/* func_80005C50 GRAFT-BLOCKED 2026-06-10 (boundary puzzle): its
 * jumptable jtbl_8000A770 (ROM-true entries read from the byte-exact
 * ROM) targets [0x6354..0x647C] -- INSIDE func_800062F0's span, three
 * symbols away. func_800060F0 starts with bnez (no prologue = a
 * fragment of this fn), but 6110/62F0 have real prologues. The region
 * [0x5C50..0x65B0) needs a boundary-merge analysis (which "fns" are
 * case blocks vs real entries) before any C decode. The kernel
 * relayout verified SECTION bytes, not these internal symbol
 * boundaries (unmatched INCLUDEs kept splat's guesses).
 * 2026-06-10 CORRECTED ANALYSIS (the first map below used a WRONG
 * ROM base -- always take the ROM offset from the .s comment FIELD 1,
 * never a VRAM formula): the true text mapping is ROM = VRAM -
 * 0x7FFFF000. Prologue map confirms splat is mostly right: 5C50's
 * true span = [0x5C50..0x6110) WITH the prologue-less 60F0 fragment
 * merged in (one -72-frame fn containing the jr-t1 dispatch at
 * 0x5F4C); 6110/61F0/6250/62F0 are real fns. THE REGION IS A DEBUGGER
 * COMMAND DISPATCHER: "jtbl_8000A770" is MISLABELED -- at the text
 * formula's ROM offset it reads ASCII command names (SetFRegisters /
 * GetSRegisters / SetSRegisters / GetV...). The true handler table
 * needs the DATA-segment ROM mapping (kernel .data has its own
 * offset; check tenshoe.map). RESOLVED LAYOUT (map read): kernel VRAM
 * is CONTIGUOUS (text<0x9E60, rodata 0x9E60-0x9FD0, data blob
 * 0x9FD0-0xABC0), one ROM formula throughout -- so jtbl_8000A770
 * genuinely points at the ASCII block. HYPOTHESIS: the dispatch index
 * is BIASED (lw at 0xA770+t1 with t1 starting negative), making the
 * true table the 44-entry run at VRAM 0x8000A690 / ROM 0xB690 (ends
 * 0xA740, adjacent to the strings) -- but ITS targets [0x89FC..0x8B10]
 * belong to a dispatcher near 0x8A00, not 5C50. Also located: a
 * 54-entry table at ROM 0xB0A0 (targets 0x6FD8..0x7F3C).
 * FINAL RESOLUTION 2026-06-10: the t1 derivation is addiu t1,t9,-0xA;
 * sltiu 7 = cases 10..16, table exactly AT 0x8000A770 -- which, in
 * the data blob (assets/kernel.data.bin +0x7A0), holds the ASCII
 * strings at LOAD TIME. The handler pointers are RUNTIME-WRITTEN
 * (debugger handler registration), and a jumptable in .data (not
 * .rodata) is NOT IDO-emitted -- this dispatcher is handwritten-class
 * debugger code. Permanent INCLUDE_ASM (same disposition as the
 * 31F0/3C24 handwritten neighborhood). The 5C50 vein is CLOSED.
 * SIBLING LEAD (open): the 44-entry INITIALIZED handler table at VRAM
 * 0x8000A690 (.data, full of valid fn ptrs at load = a C
 * fn-ptr array, compilable) has NO direct lo16 reference in kernel
 * text -- reached via a base pointer or from data. Its targets
 * [0x89FC..0x8B10] are real handler fns; finding the indirect user
 * could open a decodable dispatcher family. EXHAUSTED at cadence
 * cost (2026-06-10): NO pointer to 0x8000A690 in the first 64KB and
 * NO per-slot lo16 references in kernel text -- the user is outside
 * kernel text (a USO overlay reading kernel globals, or dead debugger
 * data). The handler fns at [0x89FC..0x8B10] remain decodable on
 * their own merits regardless. */
/* func_80005C50 = libultra __osDevMgrMain (io/devmgr.c verbatim, IDO 5.3
 * -O1 donor: kernel_ido53_5C50.c). LANDED 2026-08-22 via REPLACE_FUNC_BODY
 * donor splice: 292/292 words -- every non-reloc word identical at first
 * compile; 22 jal fields resolve to osRecvMesg=4FE0 / osSendMesg=5DC0 /
 * __osResetGlobalIntMask=6650 / __osSetGlobalIntMask=65F0 /
 * osEPiRawWriteIo=9EB0 / osEPiRawReadIo=9C50 / osYieldThread=9E50, and
 * the one %hi/%lo pair is the switch jumptable pinned at 0x8000A770
 * (func_80005C50_rodata; lui 0x8001/lw 0xa770 signed-lo wrap). This
 * RETRACTS the 2026-06-10 "handwritten-class debugger dispatcher /
 * permanent INCLUDE_ASM" verdict above: the jr-t1 dispatch is IDO's own
 * switch on mb->hdr.type (OS_MESG_TYPE_BASE cases 10..16), jtbl_8000A770
 * is that switch's table, and the "ASCII at load time" read was a
 * mis-derived ROM offset. The 4 leading zero words (0x5C50..0x5C5C) are
 * re-homed to the _pad_pre GLOBAL_ASM below; true entry = 0x80005C60,
 * body 0x490. Body below is a placeholder for the splice. */
#pragma GLOBAL_ASM("asm/nonmatchings/kernel/func_80005C50_pad.s")

void func_80005C50(void *a0) {
    volatile int devmgr_spliced = 0;
    if (a0 != (void *)0) {
        devmgr_spliced = 1;
    }
}

