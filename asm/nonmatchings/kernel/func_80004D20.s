
/* Handwritten function */
nonmatching func_80004D20, 0x98

glabel func_80004D20
    /* 5D20 80004D20 40085000 */  mfc0       $t0, $10 /* handwritten instruction */
    /* 5D24 80004D24 310900FF */  andi       $t1, $t0, 0xFF
    /* 5D28 80004D28 2401E000 */  addiu      $at, $zero, -0x2000
    /* 5D2C 80004D2C 00815024 */  and        $t2, $a0, $at
    /* 5D30 80004D30 012A4825 */  or         $t1, $t1, $t2
    /* 5D34 80004D34 40895000 */  mtc0       $t1, $10 /* handwritten instruction */
    /* 5D38 80004D38 00000000 */  nop
    /* 5D3C 80004D3C 00000000 */  nop
    /* 5D40 80004D40 00000000 */  nop
    /* 5D44 80004D44 42000008 */  tlbp /* handwritten instruction */
    /* 5D48 80004D48 00000000 */  nop
    /* 5D4C 80004D4C 00000000 */  nop
    /* 5D50 80004D50 400B0000 */  mfc0       $t3, $0 /* handwritten instruction */
    /* 5D54 80004D54 3C018000 */  lui        $at, (0x80000000 >> 16)
    /* 5D58 80004D58 01615824 */  and        $t3, $t3, $at
    /* 5D5C 80004D5C 1560001A */  bnez       $t3, .L80004DC8
    /* 5D60 80004D60 00000000 */   nop
    /* 5D64 80004D64 42000001 */  tlbr /* handwritten instruction */
    /* 5D68 80004D68 00000000 */  nop
    /* 5D6C 80004D6C 00000000 */  nop
    /* 5D70 80004D70 00000000 */  nop
    /* 5D74 80004D74 400B2800 */  mfc0       $t3, $5 /* handwritten instruction */
    /* 5D78 80004D78 216B2000 */  addi       $t3, $t3, 0x2000 /* handwritten instruction */
    /* 5D7C 80004D7C 000B5842 */  srl        $t3, $t3, 1
    /* 5D80 80004D80 01646024 */  and        $t4, $t3, $a0
    /* 5D84 80004D84 15800004 */  bnez       $t4, .L80004D98
    /* 5D88 80004D88 216BFFFF */   addi      $t3, $t3, -0x1 /* handwritten instruction */
    /* 5D8C 80004D8C 40021000 */  mfc0       $v0, $2 /* handwritten instruction */
    /* 5D90 80004D90 10000002 */  b          .L80004D9C
    /* 5D94 80004D94 00000000 */   nop
  .L80004D98:
    /* 5D98 80004D98 40021800 */  mfc0       $v0, $3 /* handwritten instruction */
  .L80004D9C:
    /* 5D9C 80004D9C 304D0002 */  andi       $t5, $v0, 0x2
    /* 5DA0 80004DA0 11A00009 */  beqz       $t5, .L80004DC8
    /* 5DA4 80004DA4 00000000 */   nop
    /* 5DA8 80004DA8 3C013FFF */  lui        $at, (0x3FFFFFC0 >> 16)
    /* 5DAC 80004DAC 3421FFC0 */  ori        $at, $at, (0x3FFFFFC0 & 0xFFFF)
    /* 5DB0 80004DB0 00411024 */  and        $v0, $v0, $at
    /* 5DB4 80004DB4 00021180 */  sll        $v0, $v0, 6
endlabel func_80004D20
