glabel func_000127CC
    /* DE3238 000127CC 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* DE323C 000127D0 AFA00004 */  sw         $zero, 0x4($sp)
  .L000127D4:
    /* DE3240 000127D4 8C8E0154 */  lw         $t6, 0x154($a0)
    /* DE3244 000127D8 8FAF0004 */  lw         $t7, 0x4($sp)
    /* DE3248 000127DC 01CFC021 */  addu       $t8, $t6, $t7
    /* DE324C 000127E0 93190006 */  lbu        $t9, 0x6($t8)
    /* DE3250 000127E4 00AF4021 */  addu       $t0, $a1, $t7
    /* DE3254 000127E8 A1190000 */  sb         $t9, 0x0($t0)
    /* DE3258 000127EC 8FA90004 */  lw         $t1, 0x4($sp)
    /* DE325C 000127F0 252A0001 */  addiu      $t2, $t1, 0x1
    /* DE3260 000127F4 AFAA0004 */  sw         $t2, 0x4($sp)
    /* DE3264 000127F8 29410008 */  slti       $at, $t2, 0x8
    /* DE3268 000127FC 1420FFF5 */  bnez       $at, .L000127D4
    /* DE326C 00012800 00000000 */   nop
    /* DE3270 00012804 10000001 */  b          .L0001280C
    /* DE3274 00012808 00000000 */   nop
  .L0001280C:
    /* DE3278 0001280C 27BD0008 */  addiu      $sp, $sp, 0x8
    /* DE327C 00012810 03E00008 */  jr         $ra
    /* DE3280 00012814 00000000 */   nop
endlabel func_000127CC
