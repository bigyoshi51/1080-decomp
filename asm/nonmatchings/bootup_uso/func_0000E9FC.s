nonmatching func_0000E9FC, 0x30

glabel func_0000E9FC
    /* DDF468 0000E9FC 27BDFFE8 */  addiu      $sp, $sp, -0x18
    /* DDF46C 0000EA00 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDF470 0000EA04 AFBF0014 */  sw         $ra, 0x14($sp)
    /* DDF474 0000EA08 0C000000 */  jal        func_00000000
    /* DDF478 0000EA0C 24840000 */   addiu     $a0, $a0, 0x0
    /* DDF47C 0000EA10 8FBF0014 */  lw         $ra, 0x14($sp)
    /* DDF480 0000EA14 3C0E0000 */  lui        $t6, (0x0 >> 16)
    /* DDF484 0000EA18 25CE0000 */  addiu      $t6, $t6, 0x0
    /* DDF488 0000EA1C 3C010000 */  lui        $at, %hi(func_00000008 + 0x20)
    /* DDF48C 0000EA20 AC2E0028 */  sw         $t6, %lo(func_00000008 + 0x20)($at)
    /* DDF490 0000EA24 03E00008 */  jr         $ra
    /* DDF494 0000EA28 27BD0018 */   addiu     $sp, $sp, 0x18
endlabel func_0000E9FC
