/* game_libs ido53 carve unit: gl_func_00072C88, the first -Olimit-fallback
 * match (IDO 5.3, -O1 -Olimit 1 -- uopt skipped so the emit is -O0-shaped
 * with homed args and per-use reloads, but the -O1 pipeline still fills
 * delay slots). 1080-custom osPfsChecker-family helper: builds a 256-byte
 * cross-bank inode link matrix. Match-critical shapes: reverse-declaration-
 * order locals (i lowest at 0x12C ... ret highest? no: i declared FIRST ->
 * 0x12C), &&-combined skip conditions (keeps unit.bank/bank live into the
 * marking block), |= (single address computation), (map + idx)[0x101]
 * (addu operand order), and ++bank inside the while condition (u8
 * truncation andi without a reload). See docs/IDO_CODEGEN -Olimit entry. */
typedef unsigned char u8;
typedef unsigned short u16;
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

typedef struct {
    __OSInodeUnit inode_page[128];
} __OSInode;

extern int gl_func_00000000();

s32 gl_func_00072C88(OSPfs *pfs, u8 *map) {
    s32 i;
    s32 idx;
    s32 startpage;
    u8 bank;
    __OSInodeUnit unit;
    __OSInode inode;
    s32 ret;

    for (i = 0; i < 256; i++) {
        map[i + 0x101] = 0;
    }
    map[0x100] = 0xFF;
    bank = 0;
    if (pfs->banks > 0) {
        do {
            if (bank > 0) {
                startpage = 1;
            } else {
                startpage = pfs->inode_start_page;
            }
            ret = gl_func_00000000(pfs, &inode, 0, bank);
            if (ret != 0) {
                if (ret != 3) {
                    return ret;
                }
            }
            for (i = startpage; i < 128; i++) {
                unit = inode.inode_page[i];
                if (unit.ipage >= pfs->inode_start_page && unit.inode_t.bank != bank) {
                    idx = unit.inode_t.page / 4 + (unit.inode_t.bank % 8) * 32;
                    (map + idx)[0x101] |= 1 << (bank % 8);
                }
            }
        } while (++bank < pfs->banks);
    }
    return 0;
}
