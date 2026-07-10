/* IDO 5.3 -O1 donor for gl_func_000730CC = libultra osEPiRawReadIo
 * (epirawread.c verbatim, EPI_SYNC/UPDATE_REG macros from piint.h).
 * PROVEN EXACT 101/101 standalone at IDO 5.3 -O1. Absorbs the 2-word
 * orphan game_libs_func_000730C4 (lui/lw PI_STATUS_REG = the hoisted
 * first `stat = IO_READ` scheduled before the addiu-sp prologue; true
 * entry = 0x730C4, span 0x730C4..0x73258). stat colors a3 (free 4th
 * arg reg), domain t0; cHandle is the 4(sp) stack local.
 * Blank extern: D_00000000_pihandles = __osCurrentHandle[] (USO reloc
 * words, blanked). Spliced into game_libs_post2b_c.c.o via
 * REPLACE_FUNC_BODY. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next; /* 0x00 */
    u8 type;                   /* 0x04 */
    u8 latency;                /* 0x05 */
    u8 pageSize;               /* 0x06 */
    u8 relDuration;            /* 0x07 */
    u8 pulse;                  /* 0x08 */
    u8 domain;                 /* 0x09 */
    u32 baseAddress;           /* 0x0C */
    u32 speed;                 /* 0x10 */
} OSPiHandle;

extern OSPiHandle *D_00000000_pihandles[]; /* __osCurrentHandle */

#define IO_READ(a) (*(volatile u32 *)((a) | 0xA0000000))
#define IO_WRITE(a, v) (*(volatile u32 *)(a) = (v))
#define PI_STATUS_REG 0xA4600010

#define WAIT_ON_IOBUSY(stat)       \
    stat = IO_READ(PI_STATUS_REG); \
    while (stat & 3)               \
        stat = IO_READ(PI_STATUS_REG);

#define UPDATE_REG(reg, var)           \
    if (cHandle->var != pihandle->var) \
        IO_WRITE(reg, pihandle->var);

#define EPI_SYNC(pihandle, stat, domain)                    \
    WAIT_ON_IOBUSY(stat)                                    \
    domain = pihandle->domain;                              \
    if (D_00000000_pihandles[domain] != pihandle) {         \
        OSPiHandle *cHandle = D_00000000_pihandles[domain]; \
        if (domain == 0) {                                  \
            UPDATE_REG(0xA4600014, latency);                \
            UPDATE_REG(0xA460001C, pageSize);               \
            UPDATE_REG(0xA4600020, relDuration);            \
            UPDATE_REG(0xA4600018, pulse);                  \
        } else {                                            \
            UPDATE_REG(0xA4600024, latency);                \
            UPDATE_REG(0xA460002C, pageSize);               \
            UPDATE_REG(0xA4600030, relDuration);            \
            UPDATE_REG(0xA4600028, pulse);                  \
        }                                                   \
        D_00000000_pihandles[domain] = pihandle;            \
    }

s32 gl_func_000730CC(OSPiHandle *pihandle, u32 devAddr, u32 *data) {
    register u32 stat;
    register u32 domain;

    EPI_SYNC(pihandle, stat, domain);

    *data = IO_READ(pihandle->baseAddress | devAddr);
    return 0;
}
