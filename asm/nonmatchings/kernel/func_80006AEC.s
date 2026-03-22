
nonmatching func_80006AEC, 0x34

glabel func_80006AEC
    /* 7AEC 80006AEC 8E040010 */  lw         $a0, 0x10($s0)
    /* 7AF0 80006AF0 2401FFFC */  addiu      $at, $zero, -0x4
    /* 7AF4 80006AF4 8FA5002C */  lw         $a1, 0x2C($sp)
    /* 7AF8 80006AF8 00815824 */  and        $t3, $a0, $at
    /* 7AFC 80006AFC 0C001A94 */  jal        func_80006A50
    /* 7B00 80006B00 01602025 */   or        $a0, $t3, $zero
    /* 7B04 80006B04 10000025 */  b          .L80006B9C
    /* 7B08 80006B08 00000000 */   nop
  .L80006B0C:
    /* 7B0C 80006B0C 8E0C0014 */  lw         $t4, 0x14($s0)
    /* 7B10 80006B10 260D0018 */  addiu      $t5, $s0, 0x18
    /* 7B14 80006B14 AFAD0024 */  sw         $t5, 0x24($sp)
    /* 7B18 80006B18 000C7082 */  srl        $t6, $t4, 2
    /* 7B1C 80006B1C AFAE0028 */  sw         $t6, 0x28($sp)
endlabel func_80006AEC
