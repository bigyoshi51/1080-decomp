/* game_libs post2b unit == gl_func_000725C4 == libultra osPfsChecker
 * (io/pfschecker.c), verbatim at IDO 5.3 -O1 -- 433/433 FIRST TRY, the
 * largest ido53-carve recovery (1.7KB). The pfschecker.c trio is now
 * identified in segment order: osPfsChecker (here), corrupted_init
 * (= gl_func_00072C88, the -Olimit-fallback match -- mixed compilation
 * within one source file!), corrupted (likely 0x72E3C). All callees are
 * gl_func_00000000 runtime-patch placeholders; constants as literals:
 * PFS_ERR_NEW_PACK=2 (this build), PFS_ERR_INCONSISTENT=3, OS_WRITE=1,
 * DIR_STATUS_EMPTY=0, PFS_CORRUPTED=2. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct {
    int status; void *queue; int channel;
    u8 id[32]; u8 label[32];
    int version; int dir_size; int inode_table; int minode_table;
    int dir_table; int inode_start_page; u8 banks; u8 activebank;
} OSPfs;

typedef union {
    struct { u8 bank; u8 page; } inode_t;
    u16 ipage;
} __OSInodeUnit;

typedef struct { __OSInodeUnit inode_page[128]; } __OSInode;

typedef struct {
    u32 game_code; u16 company_code; __OSInodeUnit start_page;
    u8 status; s8 reserved; u16 data_sum;
    u8 ext_name[4]; u8 game_name[16];
} __OSDir;

typedef struct {
    __OSInode inode; u8 bank; u8 map[256];
} __OSInodeCache;

extern int gl_func_00000000();

#define ERRCK(fn) \
    ret = fn;     \
    if (ret != 0) \
        return ret;

s32 gl_func_000725C4(OSPfs *pfs)
{
    int j;
    s32 ret;
    __OSInodeUnit next_page;
    __OSInode checked_inode;
    __OSInode tmp_inode;
    __OSDir tmp_dir;
    __OSInodeUnit file_next_node[16];
    __OSInodeCache cache;
    int fixed;
    u8 bank;
    s32 cc;
    s32 cl;
    int offset;

    fixed = 0;
    ret = gl_func_00000000(pfs);
    if (ret == 2)
        ret = gl_func_00000000(pfs);
    if (ret != 0)
        return ret;
    ERRCK(gl_func_00000000(pfs, &cache));
    for (j = 0; j < pfs->dir_size; j++)
    {
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, pfs->dir_table + j, (u8*)&tmp_dir));
        if (tmp_dir.company_code != 0 && tmp_dir.game_code != 0)
        {
            next_page = tmp_dir.start_page;
            cc = 0;
            cl = 0;
            bank = 255;
            while (next_page.ipage >= pfs->inode_start_page && next_page.inode_t.bank < pfs->banks && next_page.inode_t.page > 0 && next_page.inode_t.page < 128)
            {
                if (bank != next_page.inode_t.bank)
                {
                    bank = next_page.inode_t.bank;
                    ret = gl_func_00000000(pfs, &tmp_inode, 0, bank);
                    if (ret != 0 && ret != 3)
                        return ret;
                }
                cc = gl_func_00000000(pfs, next_page, &cache) - cl;
                if (cc != 0)
                    break;
                cl = 1;
                next_page = tmp_inode.inode_page[next_page.inode_t.page];
            }
            if (cc == 0 && next_page.ipage == 1)
                continue;

            tmp_dir.company_code = 0;
            tmp_dir.game_code = 0;
            tmp_dir.start_page.ipage = 0;
            tmp_dir.status = 0;
            tmp_dir.data_sum = 0;
            if (pfs->activebank != 0) {
                pfs->activebank = 0;
                ERRCK(gl_func_00000000(pfs))
            }
            ERRCK(gl_func_00000000(pfs->queue, pfs->channel, pfs->dir_table + j, (u8*)&tmp_dir, 0));
            fixed++;
        }
        else
        {
            if (tmp_dir.company_code == 0 && tmp_dir.game_code == 0)
                continue;
            tmp_dir.company_code = 0;
            tmp_dir.game_code = 0;
            tmp_dir.start_page.ipage = 0;
            tmp_dir.status = 0;
            tmp_dir.data_sum = 0;
            if (pfs->activebank != 0) {
                pfs->activebank = 0;
                ERRCK(gl_func_00000000(pfs))
            }
            ERRCK(gl_func_00000000(pfs->queue, pfs->channel, pfs->dir_table + j, (u8*)&tmp_dir, 0));
            fixed++;
        }
    }
    for (j = 0; j < pfs->dir_size; j++)
    {
        ERRCK(gl_func_00000000(pfs->queue, pfs->channel, pfs->dir_table + j, (u8*)&tmp_dir));

        if (tmp_dir.company_code != 0 && tmp_dir.game_code != 0 &&
            tmp_dir.start_page.ipage >= ((__OSInodeUnit *)&(pfs->inode_start_page) + 1)->ipage)
        {
            file_next_node[j].ipage = tmp_dir.start_page.ipage;
        }
        else
        {
            file_next_node[j].ipage = 0;
        }
    }
    for (bank = 0; bank < pfs->banks; bank++)
    {
        ret = gl_func_00000000(pfs, &tmp_inode, 0, bank);
        if (ret != 0 && ret != 3)
            return ret;
        if (bank > 0)
        {
            offset = 1;
        }
        else
        {
            offset = pfs->inode_start_page;
        }
        for (j = 0; j < offset; j++)
        {
            checked_inode.inode_page[j].ipage = tmp_inode.inode_page[j].ipage;
        }
        for (; j < 128; j++)
        {
            checked_inode.inode_page[j].ipage = 3;
        }
        for (j = 0; j < pfs->dir_size; j++)
        {
            while (file_next_node[j].inode_t.bank == bank && file_next_node[j].ipage >= ((__OSInodeUnit *)&(pfs->inode_start_page) + 1)->ipage)
            {
                u8 pp = file_next_node[j].inode_t.page;
                file_next_node[j] = checked_inode.inode_page[pp] = tmp_inode.inode_page[pp];
            }
        }
        ERRCK(gl_func_00000000(pfs, &checked_inode, 1, bank));
    }
    if (fixed)
        pfs->status |= 2;
    else
        pfs->status &= ~2;

    return 0;
}
