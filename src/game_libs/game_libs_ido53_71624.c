/* IDO 5.3 -O1 donor for gl_func_00071624 = libultra __osPfsGetStatus
 * (io/pfsgetstatus.c verbatim, 2.0I layout) -- pfs sibling family of
 * gl_func_00071384 = osPfsInitPak (which jals this at its PFS_GET_STATUS
 * head). PROVEN EXACT 57/57 vs expected gl_func_00071624 (first compile,
 * 2026-07-30 probe): masked-reloc word compare 0 mismatches AND every
 * reloc imm field already 0 on both sides (__osPfsPifRam refs are
 * addend-0 lui/addiu pairs = blank D_00000000 extern; all 6 jals are
 * blank USO runtime relocs = gl_func_00000000 placeholder, real callees
 * __osPfsRequestOneChannel / __osSiRawStartDma x2 / osRecvMesg x2 /
 * __osPfsGetOneChannelData=gl_func_000717CC). post2 builds -O2 7.1;
 * only 5.3 -O1 reproduces the stack-resident ret/data locals.
 * Spliced into game_libs_post2.c.o via REPLACE_FUNC_BODY. */
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef void *OSMesg;
typedef struct OSMesgQueue_s OSMesgQueue;

typedef struct
{
    u16 type;   /* 0x0 */
    u8 status;  /* 0x2 */
    u8 errno;   /* 0x3 */
} OSContStatus;

extern int gl_func_00000000();
extern u8 D_00000000; /* __osPfsPifRam */

s32 gl_func_00071624(OSMesgQueue *queue, int channel)
{
    s32 ret;
    OSMesg dummy;
    OSContStatus data;
    ret = 0;
    gl_func_00000000(channel);              /* __osPfsRequestOneChannel */
    ret = gl_func_00000000(1, &D_00000000); /* __osSiRawStartDma(OS_WRITE, &__osPfsPifRam) */
    gl_func_00000000(queue, &dummy, 1);     /* osRecvMesg(queue, &dummy, OS_MESG_BLOCK) */
    ret = gl_func_00000000(0, &D_00000000); /* __osSiRawStartDma(OS_READ, &__osPfsPifRam) */
    gl_func_00000000(queue, &dummy, 1);     /* osRecvMesg */
    gl_func_00000000(channel, &data);       /* __osPfsGetOneChannelData */
    if (((data.status & 1) != 0) && ((data.status & 2) != 0))
        return 2;  /* PFS_ERR_NEW_PACK */
    if ((data.errno != 0) || ((data.status & 1) == 0))
        return 1;  /* PFS_ERR_NOPACK */
    if ((data.status & 4) != 0)
        return 4;  /* PFS_ERR_CONTRFAIL */
    return ret;
}
