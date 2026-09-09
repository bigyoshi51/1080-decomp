/* gl_func_00071304 = libultra osViSetEvent (io/visetevent.c).
 * IDO 7.1 -O1: all 27 instruction words match, including reloc immediates.
 * The register saveMask plus -O1 retains the target's s0 round-trip;
 * -O2 optimizes it away. One shared __osViNext pointer is correct: -O1
 * reloads it for each store, with no distinct-extern CSE workaround.
 * Whole-function compiler output is spliced into the mixed-opt post2 TU.
 * The existing osViSetSpecialFeatures import pins represent these same
 * __osDisableInt/__osRestoreInt/__osViNext load-time USO imports (all zero).
 */
typedef struct {
    unsigned short state;
    unsigned short retraceCount;
    void *framebuffer;
    void *mode;
    unsigned int features;
    void *msgq;
    void *msg;
} ViContext71304;
extern ViContext71304 *gl_func_00000000_vinext711;
extern unsigned int gl_func_00000000_disint711(void);
extern void gl_func_00000000_rstint711(unsigned int);

void gl_func_00071304(void *mq, void *m, unsigned int retraceCount) {
    register unsigned int saveMask;
    saveMask = gl_func_00000000_disint711();
    gl_func_00000000_vinext711->msgq = mq;
    gl_func_00000000_vinext711->msg = m;
    gl_func_00000000_vinext711->retraceCount = retraceCount;
    gl_func_00000000_rstint711(saveMask);
}
