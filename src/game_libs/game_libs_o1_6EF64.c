/* osEPiStartDma, references/libreultra/src/io/epidma.c.
 * IDO 7.1 -O1: all 53 body words equal ROM E5403C:E54110; IDO 5.3
 * agrees. Fixed arity (handle, message, direction), not varargs. The
 * argument homes/reloads and register ret follow naturally at -O1.
 * Existing host policy adds the three all-zero inter-object pad words.
 * D_6EF64_g = __osPiDevMgr.active; FUNC_6EF64_a = osPiGetCmdQueue;
 * FUNC_6EF64_b = osJamMesg; FUNC_6EF64_d = osSendMesg. USO relocs pin
 * these to zero in the ROM image; the loader supplies real addresses.
 */
typedef int s32;
typedef struct OSPiHandle OSPiHandle;
typedef struct OSMesgQueue OSMesgQueue;
typedef void *OSMesg;
typedef struct {
    unsigned short type;
    unsigned char pri;
    unsigned char status;
    OSMesgQueue *retQueue;
} OSIoMesgHdr;
typedef struct {
    OSIoMesgHdr hdr;
    void *dramAddr;
    unsigned int devAddr;
    unsigned int size;
    OSPiHandle *piHandle;
} OSIoMesg;
extern int D_6EF64_g;
extern OSMesgQueue *FUNC_6EF64_a(void);
extern s32 FUNC_6EF64_b(OSMesgQueue *, OSMesg, s32);
extern s32 FUNC_6EF64_d(OSMesgQueue *, OSMesg, s32);

s32 gl_func_0006EF64(OSPiHandle *pihandle, OSIoMesg *mb, s32 direction)
{
    register s32 ret;
    if (!D_6EF64_g)
        return -1;
    mb->piHandle = pihandle;
    if (direction == 0) {
        mb->hdr.type = 15;
    } else {
        mb->hdr.type = 16;
    }
    if (mb->hdr.pri == 1) {
        ret = FUNC_6EF64_b(FUNC_6EF64_a(), mb, 0);
    } else {
        ret = FUNC_6EF64_d(FUNC_6EF64_a(), mb, 0);
    }
    return ret;
}
