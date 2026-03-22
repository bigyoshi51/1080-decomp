
nonmatching func_80009AB0, 0xB0

glabel func_80009AB0
    /* AAB0 80009AB0 3C0EA460 */  lui        $t6, %hi(D_A4600010)
    /* AAB4 80009AB4 8DC70010 */  lw         $a3, %lo(D_A4600010)($t6)
    /* AAB8 80009AB8 27BDFFF0 */  addiu      $sp, $sp, -0x10
    /* AABC 80009ABC 30EF0003 */  andi       $t7, $a3, 0x3
    /* AAC0 80009AC0 11E00006 */  beqz       $t7, .L80009ADC
    /* AAC4 80009AC4 00000000 */   nop
  .L80009AC8:
    /* AAC8 80009AC8 3C18A460 */  lui        $t8, %hi(D_A4600010)
    /* AACC 80009ACC 8F070010 */  lw         $a3, %lo(D_A4600010)($t8)
    /* AAD0 80009AD0 30F90003 */  andi       $t9, $a3, 0x3
    /* AAD4 80009AD4 1720FFFC */  bnez       $t9, .L80009AC8
    /* AAD8 80009AD8 00000000 */   nop
  .L80009ADC:
    /* AADC 80009ADC 90880009 */  lbu        $t0, 0x9($a0)
    /* AAE0 80009AE0 3C0A8001 */  lui        $t2, %hi(D_8000A470)
    /* AAE4 80009AE4 254AA470 */  addiu      $t2, $t2, %lo(D_8000A470)
    /* AAE8 80009AE8 00084880 */  sll        $t1, $t0, 2
    /* AAEC 80009AEC 012A5821 */  addu       $t3, $t1, $t2
    /* AAF0 80009AF0 8D6C0000 */  lw         $t4, 0x0($t3)
    /* AAF4 80009AF4 1184004A */  beq        $t4, $a0, .L80009C20
    /* AAF8 80009AF8 00000000 */   nop
    /* AAFC 80009AFC 00086880 */  sll        $t5, $t0, 2
    /* AB00 80009B00 01AA7021 */  addu       $t6, $t5, $t2
    /* AB04 80009B04 8DCF0000 */  lw         $t7, 0x0($t6)
    /* AB08 80009B08 15000021 */  bnez       $t0, .L80009B90
    /* AB0C 80009B0C AFAF0004 */   sw        $t7, 0x4($sp)
    /* AB10 80009B10 91F80005 */  lbu        $t8, 0x5($t7)
    /* AB14 80009B14 90990005 */  lbu        $t9, 0x5($a0)
    /* AB18 80009B18 13190004 */  beq        $t8, $t9, .L80009B2C
    /* AB1C 80009B1C 00000000 */   nop
    /* AB20 80009B20 90890005 */  lbu        $t1, 0x5($a0)
    /* AB24 80009B24 3C0BA460 */  lui        $t3, %hi(D_A4600014)
    /* AB28 80009B28 AD690014 */  sw         $t1, %lo(D_A4600014)($t3)
  .L80009B2C:
    /* AB2C 80009B2C 8FAC0004 */  lw         $t4, 0x4($sp)
    /* AB30 80009B30 908A0006 */  lbu        $t2, 0x6($a0)
    /* AB34 80009B34 918D0006 */  lbu        $t5, 0x6($t4)
    /* AB38 80009B38 11AA0004 */  beq        $t5, $t2, .L80009B4C
    /* AB3C 80009B3C 00000000 */   nop
    /* AB40 80009B40 908E0006 */  lbu        $t6, 0x6($a0)
    /* AB44 80009B44 3C0FA460 */  lui        $t7, %hi(D_A460001C)
    /* AB48 80009B48 ADEE001C */  sw         $t6, %lo(D_A460001C)($t7)
  .L80009B4C:
    /* AB4C 80009B4C 8FB80004 */  lw         $t8, 0x4($sp)
    /* AB50 80009B50 90890007 */  lbu        $t1, 0x7($a0)
    /* AB54 80009B54 93190007 */  lbu        $t9, 0x7($t8)
    /* AB58 80009B58 13290004 */  beq        $t9, $t1, .L80009B6C
    /* AB5C 80009B5C 00000000 */   nop
endlabel func_80009AB0
