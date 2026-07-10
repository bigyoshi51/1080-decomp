/* -O1 donor for func_800058C0 = libultra osCartRomInit (cartrominit.c;
 * PROVEN EXACT 60/60 standalone 2026-07-10 vs
 * asm/nonmatchings/kernel/func_800058C0.s, IDO 7.1 -O1 -mips2).
 * Breaks the 2026-06-10 documented "one extra lui" cap.
 * KEY LEVERS:
 *   - TU-DEFINED 2-byte struct `PgsRls D_8001B656 = {0};` (pageSize +
 *     relDuration) => the srl;srl;andi;andi;sb;sb pair emits under ONE
 *     `lui $at` (extern scalars = one lui per store = the old 60/61
 *     floor). Same shared-$at family as the 5520/6DA74 donors; the
 *     splice imports the reloc as UNDEF and undefined_syms_auto.txt
 *     carries D_8001B656 = 0x8001B656 (relDuration = %lo(D_8001B656)+1
 *     links byte-identically to the .s's D_8001B657 reloc).
 *   - CartRomHandle typed `extern void *` (the 0x00 `next` field):
 *     `CartRomHandle = D_8000A46C` emits the direct lui-$at global store
 *     (a struct/array deref form materializes a base pointer instead).
 *   - bzero arg `(u8 *)&CartRomHandle + 0x14` keeps the unfolded
 *     lui/addiu %lo/addiu +0x14 pair with the hoisted lui.
 * All other fields stay extern scalars => statement-granular own-lui
 * stores. Spliced into kernel_008.c.o via REPLACE_FUNC_BODY (real -O1
 * output; donor relocs imported; C_FILES filter-out). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct {
    u8 pageSize;     /* 0x8001B656 */
    u8 relDuration;  /* 0x8001B657 */
} PgsRls;

extern void *CartRomHandle;         /* 0x8001B650 (next field / handle base) */
extern u8 D_8001B654;               /* type */
extern u8 D_8001B655;               /* latency */
extern u8 D_8001B658;               /* pulse */
extern u8 D_8001B659;               /* domain */
extern volatile u32 D_8001B65C;     /* baseAddress */
extern u32 D_8001B660;              /* speed */
extern void *D_8000A46C;            /* __osPiTable */
extern s32 func_80002DB0(s32, u32 *);   /* osPiRawReadIo */
extern void func_800030D0(void *, s32); /* bzero */
extern s32 func_800066B0(void);         /* __osDisableInt */
extern void func_800066D0(s32);         /* __osRestoreInt */

PgsRls D_8001B656 = {0};

void *func_800058C0(void) {
    u32 domain;
    u32 saveMask;

    domain = 0;
    if (D_8001B65C == 0xB0000000) {
        return &CartRomHandle;
    }

    D_8001B654 = 0;
    D_8001B65C = 0xB0000000;
    func_80002DB0(0, &domain);
    D_8001B655 = domain & 0xFF;
    D_8001B658 = (domain >> 8) & 0xFF;
    D_8001B656.pageSize = (domain >> 0x10) & 0xF;
    D_8001B656.relDuration = (domain >> 0x14) & 0xF;
    D_8001B659 = 0;
    D_8001B660 = 0;
    func_800030D0((u8 *)&CartRomHandle + 0x14, 0x60);
    saveMask = func_800066B0();
    CartRomHandle = D_8000A46C;
    D_8000A46C = &CartRomHandle;
    func_800066D0(saveMask);
    return &CartRomHandle;
}
