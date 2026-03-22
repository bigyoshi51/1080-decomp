
nonmatching func_80009B60, 0xD0

glabel func_80009B60
    /* AB60 80009B60 908B0007 */  lbu        $t3, 0x7($a0)
    /* AB64 80009B64 3C0CA460 */  lui        $t4, %hi(D_A4600020)
    /* AB68 80009B68 AD8B0020 */  sw         $t3, %lo(D_A4600020)($t4)
  .L80009B6C:
    /* AB6C 80009B6C 8FAD0004 */  lw         $t5, 0x4($sp)
    /* AB70 80009B70 908E0008 */  lbu        $t6, 0x8($a0)
    /* AB74 80009B74 91AA0008 */  lbu        $t2, 0x8($t5)
    /* AB78 80009B78 114E0025 */  beq        $t2, $t6, .L80009C10
    /* AB7C 80009B7C 00000000 */   nop
    /* AB80 80009B80 908F0008 */  lbu        $t7, 0x8($a0)
    /* AB84 80009B84 3C18A460 */  lui        $t8, %hi(D_A4600018)
    /* AB88 80009B88 10000021 */  b          .L80009C10
    /* AB8C 80009B8C AF0F0018 */   sw        $t7, %lo(D_A4600018)($t8)
  .L80009B90:
    /* AB90 80009B90 8FB90004 */  lw         $t9, 0x4($sp)
    /* AB94 80009B94 908B0005 */  lbu        $t3, 0x5($a0)
    /* AB98 80009B98 93290005 */  lbu        $t1, 0x5($t9)
    /* AB9C 80009B9C 112B0004 */  beq        $t1, $t3, .L80009BB0
    /* ABA0 80009BA0 00000000 */   nop
    /* ABA4 80009BA4 908C0005 */  lbu        $t4, 0x5($a0)
    /* ABA8 80009BA8 3C0DA460 */  lui        $t5, %hi(D_A4600024)
    /* ABAC 80009BAC ADAC0024 */  sw         $t4, %lo(D_A4600024)($t5)
  .L80009BB0:
    /* ABB0 80009BB0 8FAA0004 */  lw         $t2, 0x4($sp)
    /* ABB4 80009BB4 908F0006 */  lbu        $t7, 0x6($a0)
    /* ABB8 80009BB8 914E0006 */  lbu        $t6, 0x6($t2)
    /* ABBC 80009BBC 11CF0004 */  beq        $t6, $t7, .L80009BD0
    /* ABC0 80009BC0 00000000 */   nop
    /* ABC4 80009BC4 90980006 */  lbu        $t8, 0x6($a0)
    /* ABC8 80009BC8 3C19A460 */  lui        $t9, %hi(D_A460002C)
    /* ABCC 80009BCC AF38002C */  sw         $t8, %lo(D_A460002C)($t9)
  .L80009BD0:
    /* ABD0 80009BD0 8FA90004 */  lw         $t1, 0x4($sp)
    /* ABD4 80009BD4 908C0007 */  lbu        $t4, 0x7($a0)
    /* ABD8 80009BD8 912B0007 */  lbu        $t3, 0x7($t1)
    /* ABDC 80009BDC 116C0004 */  beq        $t3, $t4, .L80009BF0
    /* ABE0 80009BE0 00000000 */   nop
    /* ABE4 80009BE4 908D0007 */  lbu        $t5, 0x7($a0)
    /* ABE8 80009BE8 3C0AA460 */  lui        $t2, %hi(D_A4600030)
    /* ABEC 80009BEC AD4D0030 */  sw         $t5, %lo(D_A4600030)($t2)
  .L80009BF0:
    /* ABF0 80009BF0 8FAE0004 */  lw         $t6, 0x4($sp)
    /* ABF4 80009BF4 90980008 */  lbu        $t8, 0x8($a0)
    /* ABF8 80009BF8 91CF0008 */  lbu        $t7, 0x8($t6)
    /* ABFC 80009BFC 11F80004 */  beq        $t7, $t8, .L80009C10
    /* AC00 80009C00 00000000 */   nop
    /* AC04 80009C04 90990008 */  lbu        $t9, 0x8($a0)
    /* AC08 80009C08 3C09A460 */  lui        $t1, %hi(D_A4600028)
    /* AC0C 80009C0C AD390028 */  sw         $t9, %lo(D_A4600028)($t1)
  .L80009C10:
    /* AC10 80009C10 00085880 */  sll        $t3, $t0, 2
    /* AC14 80009C14 3C018001 */  lui        $at, %hi(__osCurrentHandle)
    /* AC18 80009C18 002B0821 */  addu       $at, $at, $t3
    /* AC1C 80009C1C AC24A470 */  sw         $a0, %lo(__osCurrentHandle)($at)
  .L80009C20:
    /* AC20 80009C20 8C8C000C */  lw         $t4, 0xC($a0)
    /* AC24 80009C24 3C01A000 */  lui        $at, (0xA0000000 >> 16)
    /* AC28 80009C28 27BD0010 */  addiu      $sp, $sp, 0x10
    /* AC2C 80009C2C 01856825 */  or         $t5, $t4, $a1
endlabel func_80009B60
