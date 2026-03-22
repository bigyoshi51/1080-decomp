
nonmatching __rmonSendHeader, 0x7C

glabel __rmonSendHeader
    /* 8360 80007360 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* 8364 80007364 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 8368 80007368 0C00270C */  jal        func_80009C30
    /* 836C 8000736C AFB00018 */   sw        $s0, 0x18($sp)
    /* 8370 80007370 00408025 */  or         $s0, $v0, $zero
    /* 8374 80007374 8E0E0004 */  lw         $t6, 0x4($s0)
    /* 8378 80007378 2401FFFF */  addiu      $at, $zero, -0x1
    /* 837C 8000737C 11C10012 */  beq        $t6, $at, .L800073C8
    /* 8380 80007380 00000000 */   nop
  .L80007384:
    /* 8384 80007384 8E0F0004 */  lw         $t7, 0x4($s0)
    /* 8388 80007388 15E0000A */  bnez       $t7, .L800073B4
    /* 838C 8000738C 00000000 */   nop
    /* 8390 80007390 8E180118 */  lw         $t8, 0x118($s0)
    /* 8394 80007394 3C01FFFF */  lui        $at, (0xFFFF00FE >> 16)
    /* 8398 80007398 342100FE */  ori        $at, $at, (0xFFFF00FE & 0xFFFF)
    /* 839C 8000739C 0301C824 */  and        $t9, $t8, $at
    /* 83A0 800073A0 AE190118 */  sw         $t9, 0x118($s0)
    /* 83A4 800073A4 8E080118 */  lw         $t0, 0x118($s0)
    /* 83A8 800073A8 35096C01 */  ori        $t1, $t0, 0x6C01
    /* 83AC 800073AC 10000006 */  b          .L800073C8
    /* 83B0 800073B0 AE090118 */   sw        $t1, 0x118($s0)
  .L800073B4:
    /* 83B4 800073B4 8E10000C */  lw         $s0, 0xC($s0)
    /* 83B8 800073B8 2401FFFF */  addiu      $at, $zero, -0x1
    /* 83BC 800073BC 8E0A0004 */  lw         $t2, 0x4($s0)
    /* 83C0 800073C0 1541FFF0 */  bne        $t2, $at, .L80007384
    /* 83C4 800073C4 00000000 */   nop
  .L800073C8:
    /* 83C8 800073C8 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 83CC 800073CC 8FB00018 */  lw         $s0, 0x18($sp)
    /* 83D0 800073D0 27BD0028 */  addiu      $sp, $sp, 0x28
    /* 83D4 800073D4 03E00008 */  jr         $ra
    /* 83D8 800073D8 00000000 */   nop
endlabel __rmonSendHeader
