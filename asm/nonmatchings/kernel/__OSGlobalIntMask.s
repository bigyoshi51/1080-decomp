
nonmatching __OSGlobalIntMask

dlabel __OSGlobalIntMask
    /* B3E0 8000A3E0 20696E74 */ .word 0x20696E74
    /* B3E4 8000A3E4 65677261 */ .word 0x65677261
    /* B3E8 8000A3E8 6C206E75 */ .word 0x6C206E75
    /* B3EC 8000A3EC 6D626572 */ .word 0x6D626572

nonmatching D_8000A3F0

dlabel D_8000A3F0
    /* B3F0 8000A3F0 206F6620 */ .word 0x206F6620
    /* B3F4 8000A3F4 776F7264 */ .word 0x776F7264 /* invalid instruction */
    /* B3F8 8000A3F8 730A0000 */ .word 0x730A0000 /* invalid instruction */
    /* B3FC 8000A3FC 4C697374 */ .word 0x4C697374 /* invalid instruction */
    /* B400 8000A400 50726F63 */ .word 0x50726F63

nonmatching D_8000A404

dlabel D_8000A404
    /* B404 8000A404 65737365 */ .word 0x65737365

nonmatching D_8000A408

dlabel D_8000A408
    /* B408 8000A408 730A0000 */ .word 0x730A0000 /* invalid instruction */

nonmatching D_8000A40C

dlabel D_8000A40C
    /* B40C 8000A40C 4C6F6164 */ .word 0x4C6F6164 /* invalid instruction */

nonmatching D_8000A410

dlabel D_8000A410
    /* B410 8000A410 50726F67 */ .word 0x50726F67
    /* B414 8000A414 72616D0A */ .word 0x72616D0A /* invalid instruction */
enddlabel __OSGlobalIntMask
