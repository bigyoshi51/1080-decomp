#include "common.h"
extern int D_00000000;

/* gl_func_000718C0 = libultra __osIdCheckSum (io/contpfs.c), statically
 * linked into game_libs. Byte-exact ONLY with IDO 5.3 -O1 (per-file
 * CC/OPT_FLAGS override) from the verbatim libreultra source — same story
 * as gl_func_00071864 in the sibling unit. This unit starts 16-aligned
 * (0x718C0) and also carries gl_func_00071928's INCLUDE_ASM so the
 * following unit can start at the 16-aligned 0x71D40. */
s32 gl_func_000718C0(u16 *ptr, u16 *csum, u16 *icsum)
{
    u16 data;
    u32 j;
    data = 0;
    *icsum = 0;
    *csum = *icsum;
    for (j = 0; j < 28; j += 2)
    {
        data = *(u16 *)((u8 *)ptr + j);
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

/* gl_func_00071928 = libultra __osRepairPackId (io/contpfs.c), statically
 * linked into game_libs -- third contpfs function recovered via the ido53
 * carve (5.3 -O1, this unit's per-file override). Verbatim libreultra
 * source; the only edit vs libreultra is PFS_ERR_ID_FATAL = 10 spelled as a
 * literal. All 12 calls are runtime-patched USO relocations (target jal
 * words are 0x0C000000), so every callee is the gl_func_00000000 placeholder
 * (real identities: __osPfsSelectBank, __osContRamRead, __osContRamWrite,
 * osGetCount, __osIdCheckSum=gl_func_000718C0 above). 262/262 words. */
typedef struct {
    int status;
    void *queue;
    int channel;
    u8 id[32];
    u8 label[32];
    int version;
    int dir_size;
    int inode_table;
    int minode_table;
    int dir_table;
    int inode_start_page;
    u8 banks;
    u8 activebank;
} OSPfs;

typedef struct {
    u32 repaired;
    u32 random;
    u64 serial_mid;
    u64 serial_low;
    u16 deviceid;
    u8 banks;
    u8 version;
    u16 checksum;
    u16 inverted_checksum;
} __OSPackId;

extern int gl_func_00000000();

#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret;

s32 gl_func_00071928(OSPfs *pfs, __OSPackId *badid, __OSPackId *newid)
{
    s32 ret;
    u8 temp[32];
    u8 comp[32];
    u8 mask;
    int i;
    int j;
    u16 index[4];

    ret = 0;
    mask = 0;
    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(gl_func_00000000(pfs))
    }
    newid->repaired = -1;
    newid->random = gl_func_00000000();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;
    for (j = 0; j < 62;)
    {
        pfs->activebank = j;
        ERRCK(gl_func_00000000(pfs))
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 0, (u8*)&temp));
        temp[0] = j | 0x80;
        for (i = 1; i < 32; i++)
        {
            temp[i] = ~temp[i];
        }
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 0, (u8*)temp, 0));
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 0, (u8*)&comp));
        for (i = 0; i < 32; i++)
        {
            if (comp[i] != temp[i])
                break;
        }
        if (i != 32)
            break;
        if (j > 0)
        {
            pfs->activebank = 0;
            ERRCK(gl_func_00000000(pfs));
            ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 0, (u8*)temp));
            if (temp[0] != 128)
                break;
        }
        j++;
    }
    pfs->activebank = 0;
    ERRCK(gl_func_00000000(pfs));
    if (j > 0)
        mask = 1;
    else
        mask = 0;
    newid->deviceid = (badid->deviceid & (u16)~1) | mask;
    newid->banks = j;
    newid->version = badid->version;
    gl_func_00000000((u16*)newid, &newid->checksum, &newid->inverted_checksum);
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 0; i < 4; i++)
    {
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, index[i], (u8*)newid, 1));
    }
    ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 1, (u8*)temp));
    for (i = 0; i < 32; i++)
    {
        if (temp[i] != ((u8 *)newid)[i])
            return 10;
    }
    return 0;
}

