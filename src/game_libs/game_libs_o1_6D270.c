/* IDO -O1 donor for gl_func_0006D270 = libultra osMotorInit
 * (references/libreultra/src/io/motor.c, verbatim: pfs init with
 * activebank = 128, 32-byte 0xFE probe write (retry on 2) + read
 * (2 -> PFS_ERR_CONTRFAIL(4)) to pak address 1024, temp[31]==0xFE ->
 * PFS_ERR_DEVICE(11) [a mempack holds the write], then the same probe
 * with 0x80, then one-time _MakeMotorData(channel, 1536, buf,
 * &_MotorData[channel]) setup pair guarded by __osMotorinitialized).
 * PROVEN EXACT 183/183 standalone at BOTH IDO 7.1 -O1 and 5.3 -O1
 * (identical output; built with 7.1).
 * Blank externs: fn0 = __osContRamWrite, fn1 = __osContRamRead;
 * D_00000000_motorinit = __osMotorinitialized (int[4]),
 * D_00000000_startbuf/_stopbuf = _motorstartbuf/_motorstopbuf (u8[32]),
 * D_00000000_startdata/_stopdata = _MotorStartData/_MotorStopData
 * (OSPifRam[4], 0x40 stride -> the sll-6 addu). gl_ref_00081760 =
 * _MakeMotorData, the target's BAKED intra-game_libs `jal 0x81760`
 * (no reloc in the .s) — resolved at link like gl_ref_0007FEEC.
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef int s32;
typedef unsigned char u8;
typedef struct {
    int status;           /* 0x00 */
    void *queue;          /* 0x04 */
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
extern s32 gl_func_00000000(void *, int, int, u8 *, int); /* __osContRamWrite */
extern s32 gl_func_00000001(void *, int, int, u8 *);      /* __osContRamRead */
extern s32 gl_ref_00081760(int, int, u8 *, void *);       /* _MakeMotorData */
extern int D_00000000_motorinit[]; /* __osMotorinitialized */
extern u8 D_00000000_startbuf[];   /* _motorstartbuf */
extern u8 D_00000000_stopbuf[];    /* _motorstopbuf */
extern u8 D_00000000_startdata[];  /* _MotorStartData (0x40 stride) */
extern u8 D_00000000_stopdata[];   /* _MotorStopData */

s32 gl_func_0006D270(void *mq, OSPfs *pfs, int channel) {
    int i;
    s32 ret;
    u8 temp[32];

    pfs->queue = mq;
    pfs->channel = channel;
    pfs->status = 0;
    pfs->activebank = 128;

    for (i = 0; i < 32; i++)
        temp[i] = 254;

    ret = gl_func_00000000(mq, channel, 1024, temp, 0);
    if (ret == 2)
        ret = gl_func_00000000(mq, channel, 1024, temp, 0);
    if (ret != 0)
        return ret;

    ret = gl_func_00000001(mq, channel, 1024, temp);
    if (ret == 2)
        ret = 4;
    if (ret != 0)
        return ret;
    if (temp[31] == 254)
        return 11;

    for (i = 0; i < 32; i++)
        temp[i] = 128;

    ret = gl_func_00000000(mq, channel, 1024, temp, 0);
    if (ret == 2)
        ret = gl_func_00000000(mq, channel, 1024, temp, 0);
    if (ret != 0)
        return ret;

    ret = gl_func_00000001(mq, channel, 1024, temp);
    if (ret == 2)
        ret = 4;
    if (ret != 0)
        return ret;
    if (temp[31] != 128)
        return 11;

    if (!D_00000000_motorinit[channel]) {
        for (i = 0; i < 32; i++) {
            D_00000000_startbuf[i] = 1;
            D_00000000_stopbuf[i] = 0;
        }
        gl_ref_00081760(channel, 1536, D_00000000_startbuf, &D_00000000_startdata[channel * 64]);
        gl_ref_00081760(channel, 1536, D_00000000_stopbuf, &D_00000000_stopdata[channel * 64]);
        D_00000000_motorinit[channel] = 1;
    }
    return 0;
}
