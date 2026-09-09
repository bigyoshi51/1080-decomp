/* IDO 5.3 -O1 -mips2 donor for gl_func_0006C484 = libultra osInitialize
 * (references/libreultra/src/os/initialize.c, verbatim). PROVEN EXACT
 * 163/163 words at 5.3 -O1 FIRST COMPILE (agent-g 2026-09-09); 7.1 -O1 is
 * 161 words (it schedules the `ori a1,8` into the __osSiRawWriteIo delay
 * slot and CSEs differently), so this is a 5.3 object like the rest of the
 * os/ tail. The 62.9% NM decode ("4 vector sources, 64-bit stack-arg
 * cascade") was this function: the four `lui/addiu __osExceptionPreamble`
 * re-materialisations are the -O1 per-statement reload of ONE symbol, and
 * the two blank jal + (hi,lo,0,3)/(hi,lo,0,4) calls are `osClockRate * 3 / 4`
 * lowered to __ll_mul / __ull_div under -mips2 (in-unit callees
 * game_libs_func_0006C87C / game_libs_func_0006C77C; the compiler names
 * them itself, pinned = 0 so the words stay blank 0C000000 + USO reloc).
 * Shape keys: osClockRate and osViClock DEFINED in-TU (shared `lui at` on
 * the two-word u64 stores -- extern would split them into two at-macro
 * halves, docs/IDO_CODEGEN.md#whole-tu-o1-in-tu-def-at-share-dead-epilogue-align);
 * __osFinalrom defined (bss). Everything else is a blank import (pins = 0).
 * Section offset 0x80AF0 = export sym 2445. Spliced over the placeholder in
 * game_libs_post1b2c.c via REPLACE_FUNC_BODY; the zero word at 0x6C710 is
 * this object's inter-object pad (SUFFIX_BYTES_FORCE gl_func_0006C484,
 * already present). */

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long OSTime;

typedef struct {
    /* 0x0 */ unsigned int inst1;
    /* 0x4 */ unsigned int inst2;
    /* 0x8 */ unsigned int inst3;
    /* 0xC */ unsigned int inst4;
} __osExceptionVector;

extern __osExceptionVector gl_ExceptionPreamble;   /* __osExceptionPreamble */
extern u32 gl_ResetType;                            /* osResetType */
extern u32 gl_AppNMIBuffer[];                       /* osAppNMIBuffer */
extern s32 D_00000000_tvtype;                       /* osTvType (existing pin) */

OSTime gl_ClockRate = 62500000;                     /* osClockRate -- MUST be defined in-TU */
s32 D_00000000_viclock = 48681812;                  /* osViClock  -- MUST be defined in-TU */
u32 gl_Finalrom;                                    /* __osFinalrom */

extern u32 gl_func_00000000_getsr(void);            /* __osGetSR */
extern void gl_func_00000000_setsr(u32);            /* __osSetSR */
extern void gl_func_00000000_setfpccsr(u32);        /* __osSetFpcCsr */
extern s32 gl_func_00000000_sirawreadio(u32, u32 *);  /* __osSiRawReadIo */
extern s32 gl_func_00000000_sirawwriteio(u32, u32);   /* __osSiRawWriteIo */
extern void gl_func_00000000_wbdcache(void *, s32);   /* osWritebackDCache (= game_libs_func_0006C400, in-unit) */
extern void gl_func_00000000_invalicache(void *, s32);/* osInvalICache */
extern void gl_func_00000000_maptlbrdb(void);         /* osMapTLBRdb */
extern s32 gl_func_00000000_pirawreadio(u32, u32 *);  /* osPiRawReadIo */
extern void gl_func_00000000_bzero(void *, s32);      /* bzero (existing pin) */

#define __osExceptionPreamble gl_ExceptionPreamble
#define osResetType gl_ResetType
#define osAppNMIBuffer gl_AppNMIBuffer
#define osTvType D_00000000_tvtype
#define osClockRate gl_ClockRate
#define osViClock D_00000000_viclock
#define __osFinalrom gl_Finalrom
#define __osGetSR gl_func_00000000_getsr
#define __osSetSR gl_func_00000000_setsr
#define __osSetFpcCsr gl_func_00000000_setfpccsr
#define __osSiRawReadIo gl_func_00000000_sirawreadio
#define __osSiRawWriteIo gl_func_00000000_sirawwriteio
#define osWritebackDCache gl_func_00000000_wbdcache
#define osInvalICache gl_func_00000000_invalicache
#define osMapTLBRdb gl_func_00000000_maptlbrdb
#define osPiRawReadIo gl_func_00000000_pirawreadio
#define bzero gl_func_00000000_bzero

#define TRUE 1
#define SR_CU1 0x20000000
#define FPCSR_FS 0x01000000
#define FPCSR_EV 0x00000800
#define PIF_RAM_END 0x1FC007FF
#define UT_VEC 0x80000000
#define XUT_VEC 0x80000080
#define ECC_VEC 0x80000100
#define E_VEC 0x80000180
#define OS_APP_NMI_BUFSIZE 64
#define OS_TV_PAL 0
#define OS_TV_MPAL 2
#define VI_NTSC_CLOCK 48681812
#define VI_PAL_CLOCK 49656530
#define VI_MPAL_CLOCK 48628316

void gl_func_0006C484(void)
{
   u32 pifdata;
   u32 clock = 0;
   __osFinalrom = TRUE;
   __osSetSR(__osGetSR() | SR_CU1);    /* enable fpu */
   __osSetFpcCsr(FPCSR_FS | FPCSR_EV); /* flush denorm to zero, enable invalid operation */

   while (__osSiRawReadIo(PIF_RAM_END - 3, &pifdata)) /* last byte of joychannel ram */
   {
      ;
   }
   while (__osSiRawWriteIo(PIF_RAM_END - 3, pifdata | 8))
   {
      ;
   }
   *(__osExceptionVector *)UT_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)XUT_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)ECC_VEC = __osExceptionPreamble;
   *(__osExceptionVector *)E_VEC = __osExceptionPreamble;
   osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
   osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
   osMapTLBRdb();
   osPiRawReadIo(4, &clock);
   clock &= ~0xf;
   if (clock != 0)
   {
      osClockRate = clock;
   }
   osClockRate = osClockRate * 3 / 4;
   if (osResetType == 0 /* cold reset */)
   {
      bzero(osAppNMIBuffer, OS_APP_NMI_BUFSIZE);
   }
   if (osTvType == OS_TV_PAL)
   {
      osViClock = VI_PAL_CLOCK;
   }
   else if (osTvType == OS_TV_MPAL)
   {
      osViClock = VI_MPAL_CLOCK;
   }
   else
   {
      osViClock = VI_NTSC_CLOCK;
   }
}
