nonmatching func_000102F0, 0x20

glabel func_000102F0
    /* DE0D5C 000102F0 44852000 */  mtc1       $a1, $f4
    /* DE0D60 000102F4 00000000 */  nop
    /* DE0D64 000102F8 468021A0 */  cvt.s.w    $f6, $f4
    /* DE0D68 000102FC E4860070 */  swc1       $f6, 0x70($a0)
    /* DE0D6C 00010300 03E00008 */  jr         $ra
    /* DE0D70 00010304 00000000 */   nop
    /* DE0D74 00010308 03E00008 */  jr         $ra
    /* DE0D78 0001030C 00000000 */   nop
endlabel func_000102F0
