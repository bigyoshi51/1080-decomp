/* IDO -O1 donor for gl_func_0006FB54 = libultra osGetTime
 * (references/libreultra/src/os/gettime.c, verbatim: saveMask =
 * __osDisableInt(); tmptime = osGetCount(); elapseCount = tmptime -
 * __osBaseCounter; currentCount = __osCurrentTime;
 * __osRestoreInt(saveMask); return currentCount + elapseCount).
 * PROVEN EXACT 33/33 standalone at BOTH IDO 7.1 -O1 and 5.3 -O1
 * (identical output; built with 7.1). Retires the old "keeps r1 in $s0
 * across the calls / 64-bit spill pattern" -O2 NM note: this is an -O1
 * libultra helper; `register u32 saveMask` across the calls at -O1 IS
 * the s0 coloring, and the u64 add is native (li t2,0 zero-extend +
 * sltu carry).
 * Blank externs: _disint = __osDisableInt, _count = osGetCount,
 * _resint = __osRestoreInt; D_00000000_basecnt = __osBaseCounter (u32),
 * D_00000000_curtime = __osCurrentTime (u64, per-half lui pair).
 * Spliced into game_libs_post1b2c.c.o via REPLACE_FUNC_BODY. */
typedef unsigned int u32;
typedef unsigned long long OSTime;

extern u32 gl_func_00000000_disint(void);   /* __osDisableInt */
extern u32 gl_func_00000000_count(void);    /* osGetCount */
extern void gl_func_00000000_resint(u32);   /* __osRestoreInt */
extern u32 D_00000000_basecnt;              /* __osBaseCounter */
extern OSTime D_00000000_curtime;           /* __osCurrentTime */

OSTime gl_func_0006FB54(void)
{
    u32 tmptime;
    u32 elapseCount;
    OSTime currentCount;
    register u32 saveMask;
    saveMask = gl_func_00000000_disint();
    tmptime = gl_func_00000000_count();
    elapseCount = tmptime - D_00000000_basecnt;
    currentCount = D_00000000_curtime;
    gl_func_00000000_resint(saveMask);
    return currentCount + elapseCount;
}
