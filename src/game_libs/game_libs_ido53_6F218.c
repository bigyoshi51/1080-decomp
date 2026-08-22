/* IDO 5.3 -O1 -mips2 donor for game_libs_func_0006F218 = libultra
 * osCreateMesgQueue (os/createmesgqueue.c verbatim shape). PROVEN
 * EXACT 2026-08-22: 11/11 body words identical at -O1 first compile.
 * The two lui/addiu pairs are both &__osThreadTail in libreultra; the
 * USO bakes them as blank hi/lo (load-time relocs), and the reloc
 * table treats them as two symbol references -- so the donor uses two
 * DISTINCT blank externs (D_00000000_crmq_mt / D_00000000_crmq_full,
 * both pinned 0x0 in undefined_syms_auto.txt) to keep the -O1 emit
 * shape (no same-symbol CSE question) and bake lui 0/addiu 0 verbatim.
 * The symbol's 3 leading all-zero pad words (0x6F218/1C/20) are
 * re-homed to the _pad_pre GLOBAL_ASM block in post1b2c; true entry =
 * 0x6F224, body 0x2C. os cluster: 6F17C memcpy, 6F1B0 strlen, 6F1D8
 * strchr, 6F218 osCreateMesgQueue, then handwritten cache fns.
 * POST_COMPILE renames osCreateMesgQueue -> game_libs_func_0006F218
 * for the REPLACE_FUNC_BODY splice key. Spliced into
 * game_libs_post1b2c.c.o. */

typedef struct OSThread_s {
    struct OSThread_s *next;
} OSThread;

typedef void *OSMesg;

typedef struct OSMesgQueue_s {
    OSThread *mtqueue;
    OSThread *fullqueue;
    int validCount;
    int first;
    int msgCount;
    OSMesg *msg;
} OSMesgQueue;

extern OSThread D_00000000_crmq_mt;
extern OSThread D_00000000_crmq_full;

void osCreateMesgQueue(OSMesgQueue *mq, OSMesg *msg, int count)
{
    mq->mtqueue = (OSThread *)&D_00000000_crmq_mt;
    mq->fullqueue = (OSThread *)&D_00000000_crmq_full;
    mq->validCount = 0;
    mq->first = 0;
    mq->msgCount = count;
    mq->msg = msg;
}
