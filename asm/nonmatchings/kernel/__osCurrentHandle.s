
nonmatching __osCurrentHandle

dlabel __osCurrentHandle
    /* B470 8000A470 63726561 */ .word 0x63726561
    /* B474 8000A474 7465640A */ .word 0x7465640A /* invalid instruction */
    /* B478 8000A478 00000000 */ .word 0x00000000
    /* B47C 8000A47C 726D6F6E */ .word 0x726D6F6E /* invalid instruction */
enddlabel __osCurrentHandle
