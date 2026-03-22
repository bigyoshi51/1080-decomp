
/* Handwritten function */
nonmatching func_800023E0, 0x150

glabel func_800023E0
    /* 33E0 800023E0 8C870008 */  lw         $a3, 0x8($a0)
    /* 33E4 800023E4 8C99000C */  lw         $t9, 0xC($a0)
    /* 33E8 800023E8 8C980004 */  lw         $t8, 0x4($a0)
    /* 33EC 800023EC 00E43820 */  add        $a3, $a3, $a0 /* handwritten instruction */
    /* 33F0 800023F0 0324C820 */  add        $t9, $t9, $a0 /* handwritten instruction */
    /* 33F4 800023F4 00003025 */  or         $a2, $zero, $zero
    /* 33F8 800023F8 20840010 */  addi       $a0, $a0, 0x10 /* handwritten instruction */
    /* 33FC 800023FC 0305C020 */  add        $t8, $t8, $a1 /* handwritten instruction */
  .L80002400:
    /* 3400 80002400 14C00004 */  bnez       $a2, .L80002414
    /* 3404 80002404 00000000 */   nop
    /* 3408 80002408 8C880000 */  lw         $t0, 0x0($a0)
    /* 340C 8000240C 24060020 */  addiu      $a2, $zero, 0x20
    /* 3410 80002410 20840004 */  addi       $a0, $a0, 0x4 /* handwritten instruction */
  .L80002414:
    /* 3414 80002414 0100482A */  slt        $t1, $t0, $zero
    /* 3418 80002418 11200006 */  beqz       $t1, .L80002434
    /* 341C 8000241C 00000000 */   nop
    /* 3420 80002420 832A0000 */  lb         $t2, 0x0($t9)
    /* 3424 80002424 23390001 */  addi       $t9, $t9, 0x1 /* handwritten instruction */
    /* 3428 80002428 20A50001 */  addi       $a1, $a1, 0x1 /* handwritten instruction */
    /* 342C 8000242C 1000000E */  b          .L80002468
    /* 3430 80002430 A0AAFFFF */   sb        $t2, -0x1($a1)
  .L80002434:
    /* 3434 80002434 94EA0000 */  lhu        $t2, 0x0($a3)
    /* 3438 80002438 20E70002 */  addi       $a3, $a3, 0x2 /* handwritten instruction */
    /* 343C 8000243C 000A5B02 */  srl        $t3, $t2, 12
    /* 3440 80002440 314A0FFF */  andi       $t2, $t2, 0xFFF
    /* 3444 80002444 1160000D */  beqz       $t3, .L8000247C
    /* 3448 80002448 00AA4822 */   sub       $t1, $a1, $t2 /* handwritten instruction */
    /* 344C 8000244C 216B0002 */  addi       $t3, $t3, 0x2 /* handwritten instruction */
  .L80002450:
    /* 3450 80002450 812AFFFF */  lb         $t2, -0x1($t1)
    /* 3454 80002454 216BFFFF */  addi       $t3, $t3, -0x1 /* handwritten instruction */
    /* 3458 80002458 21290001 */  addi       $t1, $t1, 0x1 /* handwritten instruction */
    /* 345C 8000245C 20A50001 */  addi       $a1, $a1, 0x1 /* handwritten instruction */
    /* 3460 80002460 1560FFFB */  bnez       $t3, .L80002450
    /* 3464 80002464 A0AAFFFF */   sb        $t2, -0x1($a1)
  .L80002468:
    /* 3468 80002468 00084040 */  sll        $t0, $t0, 1
    /* 346C 8000246C 14B8FFE4 */  bne        $a1, $t8, .L80002400
    /* 3470 80002470 20C6FFFF */   addi      $a2, $a2, -0x1 /* handwritten instruction */
    /* 3474 80002474 03E00008 */  jr         $ra
    /* 3478 80002478 00000000 */   nop
  .L8000247C:
    /* 347C 8000247C 932B0000 */  lbu        $t3, 0x0($t9)
    /* 3480 80002480 23390001 */  addi       $t9, $t9, 0x1 /* handwritten instruction */
    /* 3484 80002484 1000FFF2 */  b          .L80002450
    /* 3488 80002488 216B0012 */   addi      $t3, $t3, 0x12 /* handwritten instruction */
    /* 348C 8000248C 00000000 */  nop
    /* 3490 80002490 400C6000 */  mfc0       $t4, $12 /* handwritten instruction */
    /* 3494 80002494 3182FF01 */  andi       $v0, $t4, 0xFF01
    /* 3498 80002498 3C088001 */  lui        $t0, %hi(D_8000A3E0)
    /* 349C 8000249C 2508A3E0 */  addiu      $t0, $t0, %lo(D_8000A3E0)
    /* 34A0 800024A0 8D0B0000 */  lw         $t3, 0x0($t0)
    /* 34A4 800024A4 2401FFFF */  addiu      $at, $zero, -0x1
    /* 34A8 800024A8 01614026 */  xor        $t0, $t3, $at
    /* 34AC 800024AC 3108FF00 */  andi       $t0, $t0, 0xFF00
    /* 34B0 800024B0 00481025 */  or         $v0, $v0, $t0
    /* 34B4 800024B4 3C0AA430 */  lui        $t2, %hi(D_A430000C)
    /* 34B8 800024B8 8D4A000C */  lw         $t2, %lo(D_A430000C)($t2)
    /* 34BC 800024BC 11400005 */  beqz       $t2, .L800024D4
    /* 34C0 800024C0 000B4C02 */   srl       $t1, $t3, 16
    /* 34C4 800024C4 2401FFFF */  addiu      $at, $zero, -0x1
    /* 34C8 800024C8 01214826 */  xor        $t1, $t1, $at
    /* 34CC 800024CC 3129003F */  andi       $t1, $t1, 0x3F
    /* 34D0 800024D0 01495025 */  or         $t2, $t2, $t1
  .L800024D4:
    /* 34D4 800024D4 000A5400 */  sll        $t2, $t2, 16
    /* 34D8 800024D8 004A1025 */  or         $v0, $v0, $t2
    /* 34DC 800024DC 3C01003F */  lui        $at, (0x3F0000 >> 16)
    /* 34E0 800024E0 00814024 */  and        $t0, $a0, $at
    /* 34E4 800024E4 010B4024 */  and        $t0, $t0, $t3
    /* 34E8 800024E8 000843C2 */  srl        $t0, $t0, 15
    /* 34EC 800024EC 3C0A8001 */  lui        $t2, %hi(D_8000A680)
    /* 34F0 800024F0 01485021 */  addu       $t2, $t2, $t0
    /* 34F4 800024F4 954AA680 */  lhu        $t2, %lo(D_8000A680)($t2)
    /* 34F8 800024F8 3C01A430 */  lui        $at, %hi(D_A430000C)
    /* 34FC 800024FC AC2A000C */  sw         $t2, %lo(D_A430000C)($at)
    /* 3500 80002500 3088FF01 */  andi       $t0, $a0, 0xFF01
    /* 3504 80002504 3169FF00 */  andi       $t1, $t3, 0xFF00
    /* 3508 80002508 01094024 */  and        $t0, $t0, $t1
    /* 350C 8000250C 3C01FFFF */  lui        $at, (0xFFFF00FF >> 16)
    /* 3510 80002510 342100FF */  ori        $at, $at, (0xFFFF00FF & 0xFFFF)
    /* 3514 80002514 01816024 */  and        $t4, $t4, $at
    /* 3518 80002518 01886025 */  or         $t4, $t4, $t0
    /* 351C 8000251C 408C6000 */  mtc0       $t4, $12 /* handwritten instruction */
    /* 3520 80002520 00000000 */  nop
    /* 3524 80002524 00000000 */  nop
    /* 3528 80002528 03E00008 */  jr         $ra
    /* 352C 8000252C 00000000 */   nop
endlabel func_800023E0
