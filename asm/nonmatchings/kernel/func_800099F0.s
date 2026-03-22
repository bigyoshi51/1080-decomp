
/* Handwritten function */
nonmatching func_800099F0, 0x58

glabel func_800099F0
    /* A9F0 800099F0 40085000 */  mfc0       $t0, $10 /* handwritten instruction */
    /* A9F4 800099F4 2409001F */  addiu      $t1, $zero, 0x1F
    /* A9F8 800099F8 40890000 */  mtc0       $t1, $0 /* handwritten instruction */
    /* A9FC 800099FC 40802800 */  mtc0       $zero, $5 /* handwritten instruction */
    /* AA00 80009A00 240A0017 */  addiu      $t2, $zero, 0x17
    /* AA04 80009A04 3C09C000 */  lui        $t1, (0xC0000000 >> 16)
    /* AA08 80009A08 40895000 */  mtc0       $t1, $10 /* handwritten instruction */
    /* AA0C 80009A0C 3C098000 */  lui        $t1, (0x80000000 >> 16)
    /* AA10 80009A10 00095982 */  srl        $t3, $t1, 6
    /* AA14 80009A14 016A5825 */  or         $t3, $t3, $t2
    /* AA18 80009A18 408B1000 */  mtc0       $t3, $2 /* handwritten instruction */
    /* AA1C 80009A1C 24090001 */  addiu      $t1, $zero, 0x1
    /* AA20 80009A20 40891800 */  mtc0       $t1, $3 /* handwritten instruction */
    /* AA24 80009A24 00000000 */  nop
    /* AA28 80009A28 42000002 */  tlbwi /* handwritten instruction */
    /* AA2C 80009A2C 00000000 */  nop
    /* AA30 80009A30 00000000 */  nop
    /* AA34 80009A34 00000000 */  nop
    /* AA38 80009A38 00000000 */  nop
    /* AA3C 80009A3C 40885000 */  mtc0       $t0, $10 /* handwritten instruction */
    /* AA40 80009A40 03E00008 */  jr         $ra
    /* AA44 80009A44 00000000 */   nop
endlabel func_800099F0
    /* AA48 80009A48 00000000 */  nop
    /* AA4C 80009A4C 00000000 */  nop
