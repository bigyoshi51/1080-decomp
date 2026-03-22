
nonmatching func_80006BD8, 0x80

glabel func_80006BD8
    /* 7BD8 80006BD8 27BDFFC8 */  addiu      $sp, $sp, -0x38
    /* 7BDC 80006BDC AFA40038 */  sw         $a0, 0x38($sp)
    /* 7BE0 80006BE0 8FAE0038 */  lw         $t6, 0x38($sp)
    /* 7BE4 80006BE4 240F0001 */  addiu      $t7, $zero, 0x1
    /* 7BE8 80006BE8 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 7BEC 80006BEC AFA00028 */  sw         $zero, 0x28($sp)
    /* 7BF0 80006BF0 A7AF002C */  sh         $t7, 0x2C($sp)
    /* 7BF4 80006BF4 AFAE0034 */  sw         $t6, 0x34($sp)
    /* 7BF8 80006BF8 91D80009 */  lbu        $t8, 0x9($t6)
    /* 7BFC 80006BFC 24010001 */  addiu      $at, $zero, 0x1
    /* 7C00 80006C00 17010005 */  bne        $t8, $at, .L80006C18
    /* 7C04 80006C04 00000000 */   nop
    /* 7C08 80006C08 241903E9 */  addiu      $t9, $zero, 0x3E9
    /* 7C0C 80006C0C 27A8001C */  addiu      $t0, $sp, 0x1C
    /* 7C10 80006C10 10000004 */  b          .L80006C24
    /* 7C14 80006C14 AD190014 */   sw        $t9, 0x14($t0)
  .L80006C18:
    /* 7C18 80006C18 240903EA */  addiu      $t1, $zero, 0x3EA
    /* 7C1C 80006C1C 27AA001C */  addiu      $t2, $sp, 0x1C
    /* 7C20 80006C20 AD490014 */  sw         $t1, 0x14($t2)
  .L80006C24:
    /* 7C24 80006C24 8FAB0034 */  lw         $t3, 0x34($sp)
    /* 7C28 80006C28 27A4001C */  addiu      $a0, $sp, 0x1C
    /* 7C2C 80006C2C 24050018 */  addiu      $a1, $zero, 0x18
    /* 7C30 80006C30 916C0004 */  lbu        $t4, 0x4($t3)
    /* 7C34 80006C34 A7A00022 */  sh         $zero, 0x22($sp)
    /* 7C38 80006C38 24060001 */  addiu      $a2, $zero, 0x1
    /* 7C3C 80006C3C 0C001CFE */  jal        func_800073F8
    /* 7C40 80006C40 A3AC0020 */   sb        $t4, 0x20($sp)
    /* 7C44 80006C44 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 7C48 80006C48 27BD0038 */  addiu      $sp, $sp, 0x38
    /* 7C4C 80006C4C 00001025 */  or         $v0, $zero, $zero
    /* 7C50 80006C50 03E00008 */  jr         $ra
    /* 7C54 80006C54 00000000 */   nop
endlabel func_80006BD8
