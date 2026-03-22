
nonmatching func_8000798C, 0x68

glabel func_8000798C
    /* 898C 8000798C 27BDFF98 */  addiu      $sp, $sp, -0x68
    /* 8990 80007990 AFA40068 */  sw         $a0, 0x68($sp)
    /* 8994 80007994 8FAE0068 */  lw         $t6, 0x68($sp)
    /* 8998 80007998 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 899C 8000799C 27A60018 */  addiu      $a2, $sp, 0x18
    /* 89A0 800079A0 AFAE0064 */  sw         $t6, 0x64($sp)
    /* 89A4 800079A4 8DC5000C */  lw         $a1, 0xC($t6)
    /* 89A8 800079A8 0C001EA6 */  jal        func_80007A98
    /* 89AC 800079AC 91C40009 */   lbu       $a0, 0x9($t6)
    /* 89B0 800079B0 10400003 */  beqz       $v0, .L800079C0
    /* 89B4 800079B4 00000000 */   nop
    /* 89B8 800079B8 1000000A */  b          .L800079E4
    /* 89BC 800079BC 2402FFFE */   addiu     $v0, $zero, -0x2
  .L800079C0:
    /* 89C0 800079C0 8FAF0064 */  lw         $t7, 0x64($sp)
    /* 89C4 800079C4 27A40018 */  addiu      $a0, $sp, 0x18
    /* 89C8 800079C8 2405004C */  addiu      $a1, $zero, 0x4C
    /* 89CC 800079CC 91F80004 */  lbu        $t8, 0x4($t7)
    /* 89D0 800079D0 A7A0001E */  sh         $zero, 0x1E($sp)
    /* 89D4 800079D4 24060001 */  addiu      $a2, $zero, 0x1
    /* 89D8 800079D8 0C001CFE */  jal        func_800073F8
    /* 89DC 800079DC A3B8001C */   sb        $t8, 0x1C($sp)
    /* 89E0 800079E0 00001025 */  or         $v0, $zero, $zero
  .L800079E4:
    /* 89E4 800079E4 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 89E8 800079E8 27BD0068 */  addiu      $sp, $sp, 0x68
    /* 89EC 800079EC 03E00008 */  jr         $ra
    /* 89F0 800079F0 00000000 */   nop
endlabel func_8000798C
