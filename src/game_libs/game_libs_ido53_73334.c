/* game_libs ido53 carve: contramwrite.c pair, verbatim at IDO 5.3 -O1.
 * gl_func_00073334 = __osContRamWrite (129/129) and gl_func_00073538 =
 * __osPackRamWriteData (84/84), both first try. PARITY NOTE: this carve
 * span is [0x73334..0x73694) = 0x360 (0 mod 8) -- PackRamWriteData gets a
 * 12-byte all-zero SUFFIX (the genuine padding mechanism) so the tail
 * unit's include-block alignment parity is preserved (see
 * docs/MATCHING_WORKFLOW mid-file-carve parity pre-check). RamWrite calls
 * __osPackRamWriteData via the BUILD-TIME-PATCHED hardcoded jal
 * gl_ref_00087BA4 (= USO 0x73538 + game_libs reloc base 0x1466C); other
 * callees are runtime-patch placeholders. Data placeholders:
 * D_73334_pifram = __osPfsPifRam, D_73334_lastcmd = __osContLastCmd.
 * Literals: CONT_CMD_WRITE_MEMPACK=3, WRITE_MEMPACK_TX=35, RX=1,
 * CONT_CMD_NOP=255, CONT_CMD_END=254, CONT_CMD_EXE=1, CONTRFAIL=4,
 * NOPACK=1. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct {
    int ramarray[15];
    int pifstatus;
} GlPifRam;

typedef struct {
    u8 dummy; u8 txsize; u8 rxsize; u8 cmd;
    u16 address;
    u8 data[32];
    u8 datacrc;
} __OSContRamReadFormat;

extern int gl_func_00000000();
extern int gl_ref_00087BA4();
extern GlPifRam D_73334_pifram;
extern u8 D_73334_lastcmd;

s32 gl_func_00073334(void *mq, int channel, u16 address, u8 *buffer, int force)
{
    s32 ret;
    int i;
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int retry;

    ret = 0;
    ptr = (u8 *)&D_73334_pifram;
    retry = 2;
    if (force != 1 && address < 7 && address != 0)
        return 0;
    gl_func_00000000();
    D_73334_lastcmd = 3;
    gl_ref_00087BA4(channel, address, buffer);
    ret = gl_func_00000000(1, &D_73334_pifram);
    gl_func_00000000(mq, 0, 1);
    do
    {
        ret = gl_func_00000000(0, &D_73334_pifram);
        gl_func_00000000(mq, 0, 1);
        ptr = (u8 *)&D_73334_pifram;
        if (channel != 0)
            for (i = 0; i < channel; i++)
                ptr++;

        ramreadformat = *(__OSContRamReadFormat *)ptr;

        ret = ((ramreadformat.rxsize & 0xC0) >> 4);
        if (ret == 0)
        {
            if (gl_func_00000000(buffer) != ramreadformat.datacrc)
            {
                ret = gl_func_00000000(mq, channel);
                if (ret != 0)
                {
                    gl_func_00000000();
                    return ret;
                }
                ret = 4;
            }
        }
        else
        {
            ret = 1;
        }
        if (ret != 4)
            break;
    } while ((retry-- >= 0));
    gl_func_00000000();
    return ret;
}

void gl_func_00073538(int channel, u16 address, u8 *buffer)
{
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8 *)D_73334_pifram.ramarray;
    D_73334_pifram.pifstatus = 1;
    ramreadformat.dummy = 255;
    ramreadformat.txsize = 35;
    ramreadformat.rxsize = 1;
    ramreadformat.cmd = 3;
    ramreadformat.address = (address << 0x5) | gl_func_00000000(address);
    ramreadformat.datacrc = 255;
    for (i = 0; i < 32; i++)
    {
        ramreadformat.data[i] = *buffer++;
    }
    if (channel != 0)
    {
        for (i = 0; i < channel; ptr++, i++)
        {
            *ptr = 0;
        }
    }
    *(__OSContRamReadFormat *)ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = 254;
}
