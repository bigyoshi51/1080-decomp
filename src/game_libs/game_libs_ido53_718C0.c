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

/* gl_func_00071D40 = libultra __osCheckPackId (io/contpfs.c) -- fourth
 * contpfs recovery via the ido53 carve (5.3 -O1). Verbatim libreultra
 * source; all callees are runtime-patched placeholders (gl_func_00000000):
 * __osPfsSelectBank, __osContRamRead, __osContRamWrite, __osIdCheckSum.
 * 102/102 raw words incl. jal fields. Moved here from game_libs_post2b
 * (whose TRUNCATE shrinks 0x356C->0x33D4; this unit grows 0x480->0x618). */
s32 gl_func_00071D40(OSPfs *pfs, __OSPackId *temp)
{
    u16 index[4];
    s32 ret;
    u16 sum;
    u16 isum;
    int i;
    int j;

    ret = 0;
    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(gl_func_00000000(pfs))
    }
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 1; i < 4; i++)
    {
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, index[i], (u8*)temp));
        gl_func_00000000((u16 *)temp, &sum, &isum);
        if (temp->checksum == sum && temp->inverted_checksum == isum)
            break;
    }
    if (i == 4)
        return 10;
    for (j = 0; j < 4; j++)
    {
        if (j != i)
        {
            ERRCK(gl_func_00000000(pfs->queue, pfs->channel, index[j], (u8*)temp, 1));
        }
    }
    return 0;
}

/* gl_func_00071ED8 = libultra __osGetId, gl_func_00072134 = __osCheckId
 * (io/contpfs.c) -- fifth and sixth contpfs recoveries via the ido53
 * carve. Verbatim libreultra source at IDO 5.3 -O1; all callees are
 * gl_func_00000000 runtime-patch placeholders; literals: PFS_ERR_ID_FATAL
 * =10, PFS_ERR_DEVICE=11, PFS_ONE_PAGE=8, and __osCheckId's mismatch
 * return is 2 in this libultra build (not the modern PFS_ERR_NEW_PACK
 * value). The entire contpfs.c is now matched: Sumcalc, IdCheckSum,
 * RepairPackId, CheckPackId, GetId, CheckId. */
s32 gl_func_00071ED8(OSPfs *pfs)
{
    int k;
    u16 sum;
    u16 isum;
    u8 temp[32];
    __OSPackId newid;
    s32 ret;
    __OSPackId *id;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(gl_func_00000000(pfs))
    }
    ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 1, (u8*)temp));
    gl_func_00000000((u16*)temp, &sum, &isum);
    id = (__OSPackId*)temp;
    if (id->checksum != sum || id->inverted_checksum != isum)
    {
        ret = gl_func_00000000(pfs, id);
        if (ret == 10)
        {
            ERRCK(gl_func_00000000(pfs, id, &newid));
            id = &newid;
        }
        else if (ret != 0)
        {
            return ret;
        }
    }
    if ((id->deviceid & 1) == 0)
    {
        ERRCK(gl_func_00000000(pfs, id, &newid));
        id = &newid;
        if ((id->deviceid & 1) == 0)
            return 11;
    }
    for (k = 0; k < 32; k++)
    {
        pfs->id[k] = ((u8 *)id)[k];
    }
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = pfs->banks * 2 + 3;
    pfs->dir_size = 16;
    pfs->inode_table = 8;
    pfs->minode_table = pfs->banks * 8 + 8;
    pfs->dir_table = pfs->minode_table + pfs->banks * 8;
    ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 7, pfs->label));
    return 0;
}

s32 gl_func_00072134(OSPfs *pfs)
{
    int k;
    u8 temp[32];
    s32 ret;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(gl_func_00000000(pfs))
    }
    ret = gl_func_00000000(pfs->queue, pfs->channel, 1, (u8*)temp);
    if (ret != 0)
    {
        if (ret != 2)
            return ret;
        else
            ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 1, (u8*)temp));
    }
    for (k = 0; k < 32; k++)
    {
        if (pfs->id[k] != temp[k])
            return 2;
    }
    return 0;
}

/* gl_func_00072230 = libultra __osPfsRWInode (io/contpfs.c continues) --
 * seventh recovery via the ido53 carve. Verbatim libreultra source at
 * IDO 5.3 -O1, first try, 200/200. Literals: PFS_WRITE=1, PFS_READ=0,
 * PFS_ERR_INCONSISTENT=3, PFS_ONE_PAGE=8 (confirmed vs 2.0I os.h). All
 * callees are gl_func_00000000 runtime-patch placeholders. */
typedef union {
    struct { u8 bank; u8 page; } inode_t;
    u16 ipage;
} __OSInodeUnit;

typedef struct {
    __OSInodeUnit inode_page[128];
} __OSInode;

extern int gl_func_00000000();

#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret;

s32 gl_func_00072230(OSPfs *pfs, __OSInode *inode, u8 flag, u8 bank)
{
    u8 sum;
    int j;
    s32 ret;
    int offset;
    u8 *addr;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ERRCK(gl_func_00000000(pfs))
    }
    if (bank > 0)
        offset = 1;
    else
        offset = pfs->inode_start_page;

    if (flag == 1)
        inode->inode_page[0].inode_t.page = gl_func_00000000((u8*)&inode->inode_page[offset], (-offset) * 2 + 256);

    for (j = 0; j < 8; j++)
    {
        addr = ((u8 *)inode->inode_page + j * 32);
        if (flag == 1)
        {
            ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
        }
        else
        {
            ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr);
        }
        if (ret != 0)
            return ret;
    }
    if (flag == 0)
    {
        sum = gl_func_00000000((u8*)&inode->inode_page[offset], (-offset) * 2 + 256);
        if (sum != inode->inode_page[0].inode_t.page)
        {
            for (j = 0; j < 8; j++)
            {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr);
            }
            if (sum != inode->inode_page[0].inode_t.page)
                return 3;
            for (j = 0; j < 8; j++)
            {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            }
        }
        else
        {
            for (j = 0; j < 8; j++)
            {
                addr = ((u8 *)inode->inode_page + j * 32);
                ret = gl_func_00000000(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
            }
        }
    }
    return 0;
}
