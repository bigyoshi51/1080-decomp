/* IDO 5.3 -O1 donor for gl_func_00071384 = libultra osPfsInitPak
 * (io/pfsinitpak.c verbatim, 1080 2.0-era OSPfs layout: status+0 /
 * queue+4 / channel+8, id[32]+0xC, label[32]+0x2C, version+0x4C ..
 * inode_start_page+0x60, banks+0x64, activebank+0x65). PROVEN EXACT
 * 165/165 vs expected gl_func_00071384 (first compile, 2026-07-30
 * probe): masked-reloc word compare 0 mismatches AND every reloc imm
 * already 0 on both sides. No data relocs at all -- the only relocs are
 * the 10 blank USO jals (= gl_func_00000000 placeholder; real callees
 * __osSiGetAccess, __osPfsGetStatus=gl_func_00071624, __osSiRelAccess,
 * __osPfsSelectBank, __osContRamRead x2, __osIdCheckSum=gl_func_000718C0,
 * __osCheckPackId=gl_func_00071D40, __osRepairPackId=gl_func_00071928,
 * osPfsChecker). post2 builds -O2 7.1; only 5.3 -O1 reproduces the
 * stack-resident ret/temp/newid locals and sequential sp-reload chains.
 * Spliced into game_libs_post2.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef unsigned long long u64;
typedef struct OSMesgQueue_s OSMesgQueue;

typedef struct {
    int status;           /* 0x00 */
    OSMesgQueue *queue;   /* 0x04 */
    int channel;          /* 0x08 */
    u8 id[32];            /* 0x0C */
    u8 label[32];         /* 0x2C */
    int version;          /* 0x4C */
    int dir_size;         /* 0x50 */
    int inode_table;      /* 0x54 */
    int minode_table;     /* 0x58 */
    int dir_table;        /* 0x5C */
    int inode_start_page; /* 0x60 */
    u8 banks;             /* 0x64 */
    u8 activebank;        /* 0x65 */
} OSPfs;

typedef struct {
    u32 repaired;           /* 0x00 */
    u32 random;             /* 0x04 */
    u64 serial_mid;         /* 0x08 */
    u64 serial_low;         /* 0x10 */
    u16 deviceid;           /* 0x18 */
    u8 banks;               /* 0x1A */
    u8 version;             /* 0x1B */
    u16 checksum;           /* 0x1C */
    u16 inverted_checksum;  /* 0x1E */
} __OSPackId;

extern int gl_func_00000000();

#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret;

s32 gl_func_00071384(OSMesgQueue *queue, OSPfs *pfs, int channel)
{
    int k;
    s32 ret;
    u16 sum;
    u16 isum;
    u8 temp[32];
    __OSPackId *id;
    __OSPackId newid;
    ret = 0;
    gl_func_00000000();                       /* __osSiGetAccess */
    ret = gl_func_00000000(queue, channel);   /* __osPfsGetStatus */
    gl_func_00000000();                       /* __osSiRelAccess */
    if (ret != 0)
        return ret;
    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 0;
    ERRCK(gl_func_00000000(pfs));             /* __osPfsSelectBank */
    ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 1, (u8*)temp)); /* __osContRamRead */
    gl_func_00000000((u16*)temp, &sum, &isum); /* __osIdCheckSum */
    id = (__OSPackId *)temp;
    if (id->checksum != sum || id->inverted_checksum != isum)
    {
        ERRCK(gl_func_00000000(pfs, id));     /* __osCheckPackId */
        if (ret != 0)
            return ret;
    }
    if ((id->deviceid & 1) == 0)
    {
        ERRCK(gl_func_00000000(pfs, id, &newid)); /* __osRepairPackId */
        id = &newid;
        if ((id->deviceid & 1) == 0)
            return 11; /* PFS_ERR_DEVICE */
    }
    for (k = 0; k < 32; k++)
    {
        pfs->id[k] = ((u8 *)id)[k];
    }
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = pfs->banks * 2 + 3;
    pfs->dir_size = 0x10;
    pfs->inode_table = 8;
    pfs->minode_table = pfs->banks * 8 + 8;   /* PFS_ONE_PAGE */
    pfs->dir_table = pfs->minode_table + pfs->banks * 8;
    ERRCK(gl_func_00000000(pfs->queue, pfs->channel, 7, pfs->label)); /* __osContRamRead */
    ret = gl_func_00000000(pfs);              /* osPfsChecker */
    pfs->status |= 1; /* PFS_INITIALIZED */
    return ret;
}
