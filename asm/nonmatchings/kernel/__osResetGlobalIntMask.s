
nonmatching __osResetGlobalIntMask, 0x48

glabel __osResetGlobalIntMask
    /* 7650 80006650 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* 7654 80006654 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 7658 80006658 AFA40018 */  sw         $a0, 0x18($sp)
    /* 765C 8000665C AFA5001C */  sw         $a1, 0x1C($sp)
    /* 7660 80006660 8FA5001C */  lw         $a1, 0x1C($sp)
    /* 7664 80006664 0C002824 */  jal        func_8000A090
    /* 7668 80006668 8FA40018 */   lw        $a0, 0x18($sp)
    /* 766C 8000666C 10400006 */  beqz       $v0, .L80006688
    /* 7670 80006670 00000000 */   nop
  .L80006674:
    /* 7674 80006674 8FA40018 */  lw         $a0, 0x18($sp)
    /* 7678 80006678 0C002824 */  jal        func_8000A090
    /* 767C 8000667C 8FA5001C */   lw        $a1, 0x1C($sp)
    /* 7680 80006680 1440FFFC */  bnez       $v0, .L80006674
    /* 7684 80006684 00000000 */   nop
  .L80006688:
    /* 7688 80006688 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 768C 8000668C 27BD0018 */  addiu      $sp, $sp, 0x18
    /* 7690 80006690 03E00008 */  jr         $ra
    /* 7694 80006694 00000000 */   nop
endlabel __osResetGlobalIntMask
