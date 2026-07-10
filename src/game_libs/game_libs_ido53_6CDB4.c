/* IDO 5.3 -O1 donor for the word-identical twins gl_func_0006CDB4 and
 * gl_func_0006CF54 — 104-insn Nintendo-modified __osContRamRead-family
 * mempack transaction verifiers (cf. references/libreultra/src/io/
 * contramread.c). PROVEN EXACT 104/104 at IDO 5.3 -O1, first probe (7.1
 * -O1 = 81/104; the 40-byte `ramreadformat = *(fmt*)ptr` lwl/lwr $at
 * chunk-copy loop is the 5.3 discriminator). Both twins are blanked to
 * the same 104 words in ROM (relocs differ only in the USO reloc table),
 * so one donor TU defines both bodies (6C740 7-way precedent).
 * 1080 deltas vs libreultra __osContRamRead: takes an OSPfs* (queue at +4,
 * channel at +8) instead of (mq, channel, address, buffer); entry guard
 * `if (word_table[pfs->channel] == 0) return PFS_ERR_INVALID(5)`; no
 * retry loop; the write-side PIF buffer is a per-channel 64-byte array
 * (&D_bank[channel * 64], the sll-6 addu); the CRC check calls
 * __osContDataCrc on a GLOBAL buffer (not the stack copy) and just sets
 * PFS_ERR_CONTRFAIL(4) (no __osPfsGetStatus rescue); no copy-out.
 * Kept from libreultra: __osSiGetAccess / __osContLastCmd = 3 /
 * OS_WRITE-recv-OS_READ-recv DMA ladder / `if (channel != 0) for (i=0;
 * i<channel; i++) ptr++` / CHNL_ERR = (rxsize & 0xC0) >> 4 (assigned to
 * ret in the branch delay slot, both paths) / __osSiRelAccess.
 * Decl order i, ret, ptr, fmt = slots 0x4C / 0x48 / 0x44 / 0x1C (40-byte
 * fmt: dummy,tx,rx,cmd, u16 address, data[32], datacrc at +38).
 * Blank externs: fn0 = __osSiGetAccess, fn1 = __osSiRawStartDma, fn2 =
 * osRecvMesg, fn3 = __osContDataCrc, fn4 = __osSiRelAccess; D_table /
 * D_bank / D_pifram2 / D_base / D_crcbuf are distinct game_libs globals
 * (all USO reloc words blanked -> 0), D_lastcmd = __osContLastCmd.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY (real 5.3 -O1
 * compiler output; blank-extern relocs imported by the splice). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef struct { u8 dummy; u8 txsize; u8 rxsize; u8 cmd; u16 address; u8 data[32]; u8 datacrc; } RamReadFormat;
typedef struct { int unk0; void *queue; int channel; } PFS;
extern u8 D_00000000_pifram[];
extern s32 D_00000000_table[];
extern u8 D_00000000_bank[];
extern u8 D_00000000_pifram2[];
extern u8 D_00000000_base[];
extern u8 D_00000000_crcbuf[];
extern u8 D_00000000_lastcmd;
extern void gl_func_00000000(void);
extern s32 gl_func_00000001(s32, void *);
extern s32 gl_func_00000002(void *, void *, s32);
extern u8 gl_func_00000003(u8 *);
extern void gl_func_00000004(void);
s32 gl_func_0006CDB4(PFS *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    RamReadFormat ramreadformat;
    ptr = D_00000000_pifram;
    if (D_00000000_table[pfs->channel] == 0)
        return 5;
    gl_func_00000000();
    D_00000000_lastcmd = 3;
    gl_func_00000001(1, &D_00000000_bank[pfs->channel * 64]);
    gl_func_00000002(pfs->queue, 0, 1);
    ret = gl_func_00000001(0, D_00000000_pifram2);
    gl_func_00000002(pfs->queue, 0, 1);
    ptr = D_00000000_base;
    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }
    ramreadformat = *(RamReadFormat *)ptr;
    ret = (ramreadformat.rxsize & 0xc0) >> 4;
    if (ret == 0) {
        if (gl_func_00000003(D_00000000_crcbuf) != ramreadformat.datacrc)
            ret = 4;
    }
    gl_func_00000004();
    return ret;
}
s32 gl_func_0006CF54(PFS *pfs) {
    int i;
    s32 ret;
    u8 *ptr;
    RamReadFormat ramreadformat;
    ptr = D_00000000_pifram;
    if (D_00000000_table[pfs->channel] == 0)
        return 5;
    gl_func_00000000();
    D_00000000_lastcmd = 3;
    gl_func_00000001(1, &D_00000000_bank[pfs->channel * 64]);
    gl_func_00000002(pfs->queue, 0, 1);
    ret = gl_func_00000001(0, D_00000000_pifram2);
    gl_func_00000002(pfs->queue, 0, 1);
    ptr = D_00000000_base;
    if (pfs->channel != 0) {
        for (i = 0; i < pfs->channel; i++) {
            ptr++;
        }
    }
    ramreadformat = *(RamReadFormat *)ptr;
    ret = (ramreadformat.rxsize & 0xc0) >> 4;
    if (ret == 0) {
        if (gl_func_00000003(D_00000000_crcbuf) != ramreadformat.datacrc)
            ret = 4;
    }
    gl_func_00000004();
    return ret;
}
