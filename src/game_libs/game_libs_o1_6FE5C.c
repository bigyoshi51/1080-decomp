/* IDO -O1 donor for gl_func_0006FE5C = libultra __osInsertTimer
 * (references/libreultra/src/os/timerintr.c, verbatim: walk
 * __osTimerList->next accumulating tim -= timep->value until
 * timep == __osTimerList || tim <= timep->value; store t->value,
 * decrement the successor, doubly-linked insert before timep, under
 * __osDisableInt/__osRestoreInt). PROVEN EXACT 98/98 standalone at
 * BOTH IDO 7.1 -O1 and 5.3 -O1 (identical output; built with 7.1).
 * Retires the old "64-bit free-list / heap-block search-and-split"
 * -O2 NM decode: the 64-bit sltu-chain compares are u64 `tim >
 * timep->value` at -O1, not heap sizes.
 * Blank externs: _disint = __osDisableInt, _resint = __osRestoreInt;
 * D_00000000_timerlist = __osTimerList (OSTimer*, next+0 prev+4
 * interval+8 value+0x10).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef unsigned long long OSTime;

typedef struct OSTimer_s {
    /* 0x00 */ struct OSTimer_s *next;
    /* 0x04 */ struct OSTimer_s *prev;
    /* 0x08 */ OSTime interval;
    /* 0x10 */ OSTime value;
    /* 0x18 */ void *mq;
    /* 0x1C */ void *msg;
} OSTimer;

extern u32 gl_func_00000000_disint(void);   /* __osDisableInt */
extern void gl_func_00000000_resint(u32);   /* __osRestoreInt */
extern OSTimer *D_00000000_timerlist;       /* __osTimerList */

OSTime gl_func_0006FE5C(OSTimer *t)
{
    OSTimer *timep;
    OSTime tim;
    u32 savedMask;
    savedMask = gl_func_00000000_disint();
    for (timep = D_00000000_timerlist->next, tim = t->value;
         timep != D_00000000_timerlist && tim > timep->value;
         tim -= timep->value, timep = timep->next)
    {
        ;
    }
    t->value = tim;
    if (timep != D_00000000_timerlist)
        timep->value -= tim;
    t->next = timep;
    t->prev = timep->prev;
    timep->prev->next = t;
    timep->prev = t;
    gl_func_00000000_resint(savedMask);
    return tim;
}
