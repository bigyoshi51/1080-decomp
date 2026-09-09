/* __osTimerInterrupt from libreultra src/os/timerintr.c.
 * IDO 7.1 -O1 reproduces all 94 original words; the main O2 unit retains
 * the same complete C body and uses this whole-function compiler output.
 * No instruction bytes are changed. Every named USO import is pinned zero.
 * Sym[2638] exports Text+0x842DC: synthetic 6FC70 is the real entry and
 * the former 6FC78 symbol was an internal prologue split. */
typedef unsigned long long Time6FC70;
typedef void *Mesg6FC70;
typedef struct Queue6FC70_s Queue6FC70;
typedef struct Timer6FC70_s {
    struct Timer6FC70_s *next, *prev;
    Time6FC70 interval, value;
    Queue6FC70 *mq;
    Mesg6FC70 msg;
} Timer6FC70;
extern Timer6FC70 *gl_timerlist_6FC70;
extern unsigned int gl_timercounter_6FC70;
extern void gl_setcompare_6FC70(unsigned int);
extern unsigned int gl_getcount_6FC70(void);
extern void gl_settimerintr_6FC70(Time6FC70);
extern int gl_sendmesg_6FC70(Queue6FC70 *, Mesg6FC70, int);
extern Time6FC70 gl_inserttimer_6FC70(Timer6FC70 *);
void game_libs_func_0006FC70(void)
{
	Timer6FC70 *t;
	unsigned int count;
	unsigned int elapsed_cycles;

	if (gl_timerlist_6FC70->next == gl_timerlist_6FC70)
		return;
	while (1)
	{
		t = gl_timerlist_6FC70->next;
		if (t == gl_timerlist_6FC70)
		{
			gl_setcompare_6FC70(0);
			gl_timercounter_6FC70 = 0;
			break;
		}
		count = gl_getcount_6FC70();
		elapsed_cycles = count - gl_timercounter_6FC70;
		gl_timercounter_6FC70 = count;
		if (elapsed_cycles < t->value)
		{
			t->value -= elapsed_cycles;
			gl_settimerintr_6FC70(t->value);
			return;
		}
		else
		{
			t->prev->next = t->next;
			t->next->prev = t->prev;
			t->next = 0;
			t->prev = 0;
			if (t->mq != 0)
			{
				gl_sendmesg_6FC70(t->mq, t->msg, 0);
			}
			if (t->interval != 0)
			{
				t->value = t->interval;
				gl_inserttimer_6FC70(t);
			}
		}
	}
}
