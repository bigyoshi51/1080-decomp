
nonmatching func_80009A50, 0x4C

glabel func_80009A50
    /* AA50 80009A50 27BDFFD8 */  addiu      $sp, $sp, -0x28
    /* AA54 80009A54 AFBF001C */  sw         $ra, 0x1C($sp)
    /* AA58 80009A58 0C0019AC */  jal        func_800066B0
    /* AA5C 80009A5C AFB00018 */   sw        $s0, 0x18($sp)
    /* AA60 80009A60 3C0F8001 */  lui        $t7, %hi(__osRunningThread)
    /* AA64 80009A64 8DEFA420 */  lw         $t7, %lo(__osRunningThread)($t7)
    /* AA68 80009A68 240E0002 */  addiu      $t6, $zero, 0x2
    /* AA6C 80009A6C 3C048001 */  lui        $a0, %hi(__osRunQueue)
    /* AA70 80009A70 00408025 */  or         $s0, $v0, $zero
    /* AA74 80009A74 2484A418 */  addiu      $a0, $a0, %lo(__osRunQueue)
    /* AA78 80009A78 0C000F43 */  jal        func_80003D0C
    /* AA7C 80009A7C A5EE0010 */   sh        $t6, 0x10($t7)
    /* AA80 80009A80 0C0019B4 */  jal        func_800066D0
    /* AA84 80009A84 02002025 */   or        $a0, $s0, $zero
    /* AA88 80009A88 8FBF001C */  lw         $ra, 0x1C($sp)
    /* AA8C 80009A8C 8FB00018 */  lw         $s0, 0x18($sp)
    /* AA90 80009A90 27BD0028 */  addiu      $sp, $sp, 0x28
    /* AA94 80009A94 03E00008 */  jr         $ra
    /* AA98 80009A98 00000000 */   nop
endlabel func_80009A50
    /* AA9C 80009A9C 00000000 */  nop
