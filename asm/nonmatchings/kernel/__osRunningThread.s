
nonmatching __osRunningThread

dlabel __osRunningThread
    /* B420 8000A420 78654E61 */ .word 0x78654E61 /* invalid instruction */

nonmatching D_8000A424

dlabel D_8000A424
    /* B424 8000A424 6D650A00 */ .word 0x6D650A00
    /* B428 8000A428 696D656D */ .word 0x696D656D
    /* B42C 8000A42C 00000000 */ .word 0x00000000

nonmatching D_8000A430

dlabel D_8000A430
    /* B430 8000A430 726D6F6E */ .word 0x726D6F6E /* invalid instruction */
    /* B434 8000A434 00000000 */ .word 0x00000000
    /* B438 8000A438 47657452 */ .word 0x47657452 /* invalid instruction */
    /* B43C 8000A43C 6567696F */ .word 0x6567696F

nonmatching D_8000A440

dlabel D_8000A440
    /* B440 8000A440 6E436F75 */ .word 0x6E436F75
    /* B444 8000A444 6E740A00 */ .word 0x6E740A00
    /* B448 8000A448 47657452 */ .word 0x47657452 /* invalid instruction */
    /* B44C 8000A44C 6567696F */ .word 0x6567696F

nonmatching D_8000A450

dlabel D_8000A450
    /* B450 8000A450 6E730A00 */ .word 0x6E730A00

nonmatching D_8000A454

dlabel D_8000A454
    /* B454 8000A454 00000000 */ .word 0x00000000

nonmatching D_8000A458

dlabel D_8000A458
    /* B458 8000A458 00000000 */ .word 0x00000000

nonmatching D_8000A45C

dlabel D_8000A45C
    /* B45C 8000A45C 00000000 */ .word 0x00000000

nonmatching D_8000A460

dlabel D_8000A460
    /* B460 8000A460 726D6F6E */ .word 0x726D6F6E /* invalid instruction */

nonmatching D_8000A464

dlabel D_8000A464
    /* B464 8000A464 3A205468 */ .word 0x3A205468

nonmatching D_8000A468

dlabel D_8000A468
    /* B468 8000A468 72656164 */ .word 0x72656164 /* invalid instruction */

nonmatching D_8000A46C

dlabel D_8000A46C
    /* B46C 8000A46C 20256420 */ .word 0x20256420
enddlabel __osRunningThread
