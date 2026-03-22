
nonmatching func_800051F0, 0xC4

glabel func_800051F0
    /* 61F0 800051F0 27BDFFD0 */  addiu      $sp, $sp, -0x30
    /* 61F4 800051F4 AFBF001C */  sw         $ra, 0x1C($sp)
    /* 61F8 800051F8 3C048002 */  lui        $a0, %hi(rmonsio_bss_0000)
    /* 61FC 800051FC 3C058002 */  lui        $a1, %hi(rmonsio_bss_0018)
    /* 6200 80005200 AFB00018 */  sw         $s0, 0x18($sp)
    /* 6204 80005204 24A59668 */  addiu      $a1, $a1, %lo(rmonsio_bss_0018)
    /* 6208 80005208 24849650 */  addiu      $a0, $a0, %lo(rmonsio_bss_0000)
    /* 620C 8000520C 0C0014F4 */  jal        func_800053D0
    /* 6210 80005210 24060001 */   addiu     $a2, $zero, 0x1
    /* 6214 80005214 3C058002 */  lui        $a1, %hi(rmonsio_bss_0000)
    /* 6218 80005218 24A59650 */  addiu      $a1, $a1, %lo(rmonsio_bss_0000)
    /* 621C 8000521C 24040014 */  addiu      $a0, $zero, 0x14
    /* 6220 80005220 0C001478 */  jal        func_800051E0
    /* 6224 80005224 00003025 */   or        $a2, $zero, $zero
    /* 6228 80005228 3C0E8002 */  lui        $t6, %hi(rmonRdbReadBuf)
    /* 622C 8000522C 25CE9670 */  addiu      $t6, $t6, %lo(rmonRdbReadBuf)
    /* 6230 80005230 3C018002 */  lui        $at, %hi(__osRdb_DbgRead_Buf)
    /* 6234 80005234 AC2E966C */  sw         $t6, %lo(__osRdb_DbgRead_Buf)($at)
  .L80005238:
    /* 6238 80005238 3C048002 */  lui        $a0, %hi(rmonsio_bss_0000)
    /* 623C 8000523C 24849650 */  addiu      $a0, $a0, %lo(rmonsio_bss_0000)
    /* 6240 80005240 00002825 */  or         $a1, $zero, $zero
    /* 6244 80005244 0C0013F8 */  jal        func_80004FE0
    /* 6248 80005248 24060001 */   addiu     $a2, $zero, 0x1
    /* 624C 8000524C 3C048002 */  lui        $a0, %hi(rmonRdbReadBuf)
    /* 6250 80005250 0C001A6F */  jal        func_800069BC
    /* 6254 80005254 24849670 */   addiu     $a0, $a0, %lo(rmonRdbReadBuf)
    /* 6258 80005258 3C0F8002 */  lui        $t7, %hi(rmonRdbReadBuf)
    /* 625C 8000525C 25EF9670 */  addiu      $t7, $t7, %lo(rmonRdbReadBuf)
    /* 6260 80005260 3C018002 */  lui        $at, %hi(__osRdb_DbgRead_Buf)
    /* 6264 80005264 AC2F966C */  sw         $t7, %lo(__osRdb_DbgRead_Buf)($at)
    /* 6268 80005268 AFA0002C */  sw         $zero, 0x2C($sp)
  .L8000526C:
    /* 626C 8000526C 27A40028 */  addiu      $a0, $sp, 0x28
    /* 6270 80005270 24050001 */  addiu      $a1, $zero, 0x1
    /* 6274 80005274 0C0019BC */  jal        func_800066F0
    /* 6278 80005278 2406000B */   addiu     $a2, $zero, 0xB
    /* 627C 8000527C 8FB8002C */  lw         $t8, 0x2C($sp)
    /* 6280 80005280 00408025 */  or         $s0, $v0, $zero
    /* 6284 80005284 0310C821 */  addu       $t9, $t8, $s0
    /* 6288 80005288 AFB9002C */  sw         $t9, 0x2C($sp)
    /* 628C 8000528C 8FA8002C */  lw         $t0, 0x2C($sp)
    /* 6290 80005290 1900FFF6 */  blez       $t0, .L8000526C
    /* 6294 80005294 00000000 */   nop
    /* 6298 80005298 1000FFE7 */  b          .L80005238
    /* 629C 8000529C 00000000 */   nop
    /* 62A0 800052A0 8FBF001C */  lw         $ra, 0x1C($sp)
    /* 62A4 800052A4 8FB00018 */  lw         $s0, 0x18($sp)
    /* 62A8 800052A8 27BD0030 */  addiu      $sp, $sp, 0x30
    /* 62AC 800052AC 03E00008 */  jr         $ra
    /* 62B0 800052B0 00000000 */   nop
endlabel func_800051F0
    /* 62B4 800052B4 00000000 */  nop
    /* 62B8 800052B8 00000000 */  nop
    /* 62BC 800052BC 00000000 */  nop
