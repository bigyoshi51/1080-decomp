/* IDO 5.3 -O1 -mips2 donor for game_libs_func_0006FBE4 = libultra
 * __osTimerServicesInit (os/timerintr.c verbatim). PROVEN EXACT 2026-09-09
 * (agent-g): 35/35 words at 5.3 -O1 AND 7.1 -O1 first compile once the ONE
 * structural key is in place -- __osCurrentTime (u64, USO .bss 0x44060) is
 * DEFINED in this TU, exactly as timerintr.c defines it. An `extern` u64
 * splits the 64-bit zero store into two at-macro halves (`li t6; lui at;
 * sw t6,0(at); lui at; li t7; sw t7,4(at)`, 36 words); the in-TU
 * definition keeps it ONE store with a shared `lui at` and the low word
 * first (`lui at; li t6,0; li t7,0; sw t7,4(at); sw t6,0(at)`) -- the
 * same lever as the vimgr.c __osViDevMgr burst
 * (docs/IDO_CODEGEN.md#whole-tu-o1-in-tu-def-at-share-dead-epilogue-align).
 * __osBaseCounter / __osViIntrCount / __osTimerList stay extern (their
 * stores were already exact). -O2 (either compiler) CSEs the six
 * __osTimerList reloads into a v1 base (31 words) -- the target reloads
 * the pointer per statement, which is -O1 (no uopt), matching libultra's
 * os/ build flags.
 * Reloc story: every masked word is a blank USO import -> pins = 0
 * (gl_fbe4_CurrentTime is this TU's own .bss definition, imported by the
 * splice as an undefined symbol and pinned to 0 like gl_viDevMgr;
 * gl_BaseCounter / gl_viIntrCount / D_00000000_timerlist are the existing
 * pins). Spliced over the placeholder in game_libs_post1b2c.c via
 * REPLACE_FUNC_BODY. The 3 zero words before the entry (0x6FBD8..0x6FBE0)
 * are gl_func_0006FB54's (osGetTime, 0x84) 16-byte inter-object pad:
 * SUFFIX_BYTES_FORCE on 6FB54, not part of this object. */

typedef unsigned int u32;
typedef unsigned long long OSTime;
typedef void *OSMesg;
typedef struct OSMesgQueue_s OSMesgQueue;
typedef struct OSTimer_s {
    struct OSTimer_s *next;
    struct OSTimer_s *prev;
    OSTime interval;
    OSTime value;
    OSMesgQueue *mq;
    OSMesg msg;
} OSTimer;
#define NULL 0

extern OSTimer *D_00000000_timerlist;   /* __osTimerList (USO .data 0x2E4B0) */
OSTime gl_fbe4_CurrentTime;             /* __osCurrentTime -- MUST be defined in-TU */
extern u32 gl_BaseCounter;              /* __osBaseCounter */
extern u32 gl_viIntrCount;              /* __osViIntrCount */

#define __osTimerList D_00000000_timerlist
#define __osCurrentTime gl_fbe4_CurrentTime
#define __osBaseCounter gl_BaseCounter
#define __osViIntrCount gl_viIntrCount

void game_libs_func_0006FBE4(void)
{
	__osCurrentTime = 0;
	__osBaseCounter = 0;
	__osViIntrCount = 0;
	__osTimerList->prev = __osTimerList;
	__osTimerList->next = __osTimerList->prev;
	__osTimerList->value = 0;
	__osTimerList->interval = __osTimerList->value;
	__osTimerList->mq = NULL;
	__osTimerList->msg = 0;
}
