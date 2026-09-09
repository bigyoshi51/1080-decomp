#include "common.h"

/* osContStartReadData, libreultra src/io/contreaddata.c, IDO 7.1 -O1.
 * ROM E5115C..E511E8, 35 words; bootup Text 0x806F0, export sym2457.
 * The old -O2 NM wrap put the command store after __osSiRelAccess and
 * used volatile to retain return-slot stores. Plain -O1 C with the real
 * source order emits every instruction exactly; no byte patch or padding.
 *
 * Verified bootup.uso relocations (all blank operands resolve to zero):
 * sym2569 Text 0x804D0 = __osSiGetAccess (gl_func_0006BE6C);
 * sym2556 BSS 0x427B0 = __osContLastCmd;
 * sym2555 BSS 0x42770 = __osContPifRam (both DMA directions);
 * sym2564 Text 0x81140 = __osSiRawStartDma;
 * sym1341 Text 0x7E5D0 = osRecvMesg;
 * sym2570 Text 0x80514 = __osSiRelAccess (gl_func_0006BEA8).
 * The module-base relocation at +0x28 retains jal 0x80824, the static
 * __osPackReadData at gl_func_0006C1B8. gl_ref_00080824 is already pinned.
 * Whole compiled body is spliced into the -O2 post1b2 host.
 */
extern u8 gl_cont_last_cmd_6C084;
extern char gl_cont_pif_ram_6C084[];
extern void gl_si_get_access_6C084(void);
extern void gl_ref_00080824(void);
extern int gl_si_raw_start_dma_6C084(int, void *);
extern int gl_recv_mesg_6C084(void *, void *, int);
extern void gl_si_rel_access_6C084(void);

int gl_func_0006C084(void *mq)
{
    int ret;
    int i;

    ret = 0;
    gl_si_get_access_6C084();
    if (gl_cont_last_cmd_6C084 != 1) {
        gl_ref_00080824();
        ret = gl_si_raw_start_dma_6C084(1, &gl_cont_pif_ram_6C084);
        gl_recv_mesg_6C084(mq, 0, 1);
    }
    ret = gl_si_raw_start_dma_6C084(0, &gl_cont_pif_ram_6C084);
    gl_cont_last_cmd_6C084 = 1;
    gl_si_rel_access_6C084();
    return ret;
}
