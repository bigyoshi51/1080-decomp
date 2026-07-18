nonmatching func_000090CC, 0x20E8

glabel func_000090CC
    /* DD9B38 000090CC 27BDFE88 */  addiu      $sp, $sp, -0x178
    /* DD9B3C 000090D0 AFB20030 */  sw         $s2, 0x30($sp)
    /* DD9B40 000090D4 00809025 */  or         $s2, $a0, $zero
    /* DD9B44 000090D8 AFBF0034 */  sw         $ra, 0x34($sp)
    /* DD9B48 000090DC AFB1002C */  sw         $s1, 0x2C($sp)
    /* DD9B4C 000090E0 AFB00028 */  sw         $s0, 0x28($sp)
    /* DD9B50 000090E4 AFA5017C */  sw         $a1, 0x17C($sp)
    /* DD9B54 000090E8 AFA60180 */  sw         $a2, 0x180($sp)
    /* DD9B58 000090EC 14800005 */  bnez       $a0, .L00009104
    /* DD9B5C 000090F0 AFA70184 */   sw        $a3, 0x184($sp)
    /* DD9B60 000090F4 0C000000 */  jal        func_00000000
    /* DD9B64 000090F8 24040A8C */   addiu     $a0, $zero, 0xA8C
    /* DD9B68 000090FC 10400826 */  beqz       $v0, .L0000B198
    /* DD9B6C 00009100 00409025 */   or        $s2, $v0, $zero
  .L00009104:
    /* DD9B70 00009104 3C050001 */  lui        $a1, %hi(D_00008730)
    /* DD9B74 00009108 24A58730 */  addiu      $a1, $a1, %lo(D_00008730)
    /* DD9B78 0000910C 0C000000 */  jal        func_00000000
    /* DD9B7C 00009110 02402025 */   or        $a0, $s2, $zero
    /* DD9B80 00009114 3C0E0000 */  lui        $t6, (0x0 >> 16)
    /* DD9B84 00009118 25CE0000 */  addiu      $t6, $t6, 0x0
    /* DD9B88 0000911C 2401FC14 */  addiu      $at, $zero, -0x3EC
    /* DD9B8C 00009120 AE4E0028 */  sw         $t6, 0x28($s2)
    /* DD9B90 00009124 16410005 */  bne        $s2, $at, .L0000913C
    /* DD9B94 00009128 265003EC */   addiu     $s0, $s2, 0x3EC
    /* DD9B98 0000912C 0C000000 */  jal        func_00000000
    /* DD9B9C 00009130 24040154 */   addiu     $a0, $zero, 0x154
    /* DD9BA0 00009134 10400144 */  beqz       $v0, .L00009648
    /* DD9BA4 00009138 00408025 */   or        $s0, $v0, $zero
  .L0000913C:
    /* DD9BA8 0000913C 3C050001 */  lui        $a1, %hi(D_00008738)
    /* DD9BAC 00009140 24A58738 */  addiu      $a1, $a1, %lo(D_00008738)
    /* DD9BB0 00009144 0C000000 */  jal        func_00000000
    /* DD9BB4 00009148 02002025 */   or        $a0, $s0, $zero
    /* DD9BB8 0000914C 3C0F0001 */  lui        $t7, %hi(func_000080EC + 0x1C)
    /* DD9BBC 00009150 25EF8108 */  addiu      $t7, $t7, %lo(func_000080EC + 0x1C)
    /* DD9BC0 00009154 2401FFD4 */  addiu      $at, $zero, -0x2C
    /* DD9BC4 00009158 AE0F0028 */  sw         $t7, 0x28($s0)
    /* DD9BC8 0000915C 16010005 */  bne        $s0, $at, .L00009174
    /* DD9BCC 00009160 2611002C */   addiu     $s1, $s0, 0x2C
    /* DD9BD0 00009164 0C000000 */  jal        func_00000000
    /* DD9BD4 00009168 24040128 */   addiu     $a0, $zero, 0x128
    /* DD9BD8 0000916C 10400136 */  beqz       $v0, .L00009648
    /* DD9BDC 00009170 00408825 */   or        $s1, $v0, $zero
  .L00009174:
    /* DD9BE0 00009174 16200005 */  bnez       $s1, .L0000918C
    /* DD9BE4 00009178 02203025 */   or        $a2, $s1, $zero
    /* DD9BE8 0000917C 0C000000 */  jal        func_00000000
    /* DD9BEC 00009180 24040008 */   addiu     $a0, $zero, 0x8
    /* DD9BF0 00009184 10400005 */  beqz       $v0, .L0000919C
    /* DD9BF4 00009188 00403025 */   or        $a2, $v0, $zero
  .L0000918C:
    /* DD9BF8 0000918C 3C180001 */  lui        $t8, %hi(D_00008740)
    /* DD9BFC 00009190 27188740 */  addiu      $t8, $t8, %lo(D_00008740)
    /* DD9C00 00009194 ACD80000 */  sw         $t8, 0x0($a2)
    /* DD9C04 00009198 ACC00004 */  sw         $zero, 0x4($a2)
  .L0000919C:
    /* DD9C08 0000919C 3C190001 */  lui        $t9, %hi(func_00008744 + 0x4)
    /* DD9C0C 000091A0 8F398748 */  lw         $t9, %lo(func_00008744 + 0x4)($t9)
    /* DD9C10 000091A4 2401FFF8 */  addiu      $at, $zero, -0x8
    /* DD9C14 000091A8 26240008 */  addiu      $a0, $s1, 0x8
    /* DD9C18 000091AC AFB90144 */  sw         $t9, 0x144($sp)
    /* DD9C1C 000091B0 16210005 */  bne        $s1, $at, .L000091C8
    /* DD9C20 000091B4 AFB90104 */   sw        $t9, 0x104($sp)
    /* DD9C24 000091B8 0C000000 */  jal        func_00000000
    /* DD9C28 000091BC 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9C2C 000091C0 1040000F */  beqz       $v0, .L00009200
    /* DD9C30 000091C4 00402025 */   or        $a0, $v0, $zero
  .L000091C8:
    /* DD9C34 000091C8 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9C38 000091CC 02202825 */  or         $a1, $s1, $zero
    /* DD9C3C 000091D0 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9C40 000091D4 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9C44 000091D8 0C000000 */  jal        func_00000000
    /* DD9C48 000091DC AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9C4C 000091E0 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9C50 000091E4 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DD9C54 000091E8 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DD9C58 000091EC 3C010000 */  lui        $at, %hi(func_0000085C + 0xC)
    /* DD9C5C 000091F0 AC8F000C */  sw         $t7, 0xC($a0)
    /* DD9C60 000091F4 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9C64 000091F8 C4240868 */  lwc1       $f4, %lo(func_0000085C + 0xC)($at)
    /* DD9C68 000091FC E4840010 */  swc1       $f4, 0x10($a0)
  .L00009200:
    /* DD9C6C 00009200 3C180001 */  lui        $t8, %hi(func_00008744 + 0x8)
    /* DD9C70 00009204 8F18874C */  lw         $t8, %lo(func_00008744 + 0x8)($t8)
    /* DD9C74 00009208 2401FFE0 */  addiu      $at, $zero, -0x20
    /* DD9C78 0000920C 26240020 */  addiu      $a0, $s1, 0x20
    /* DD9C7C 00009210 AFB80140 */  sw         $t8, 0x140($sp)
    /* DD9C80 00009214 16210005 */  bne        $s1, $at, .L0000922C
    /* DD9C84 00009218 AFB80104 */   sw        $t8, 0x104($sp)
    /* DD9C88 0000921C 0C000000 */  jal        func_00000000
    /* DD9C8C 00009220 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9C90 00009224 1040000F */  beqz       $v0, .L00009264
    /* DD9C94 00009228 00402025 */   or        $a0, $v0, $zero
  .L0000922C:
    /* DD9C98 0000922C 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9C9C 00009230 02202825 */  or         $a1, $s1, $zero
    /* DD9CA0 00009234 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9CA4 00009238 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9CA8 0000923C 0C000000 */  jal        func_00000000
    /* DD9CAC 00009240 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9CB0 00009244 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9CB4 00009248 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DD9CB8 0000924C 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DD9CBC 00009250 3C010000 */  lui        $at, %hi(func_0000085C + 0x10)
    /* DD9CC0 00009254 AC8E000C */  sw         $t6, 0xC($a0)
    /* DD9CC4 00009258 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9CC8 0000925C C426086C */  lwc1       $f6, %lo(func_0000085C + 0x10)($at)
    /* DD9CCC 00009260 E4860010 */  swc1       $f6, 0x10($a0)
  .L00009264:
    /* DD9CD0 00009264 3C0F0001 */  lui        $t7, %hi(func_00008744 + 0xC)
    /* DD9CD4 00009268 8DEF8750 */  lw         $t7, %lo(func_00008744 + 0xC)($t7)
    /* DD9CD8 0000926C 2401FFC8 */  addiu      $at, $zero, -0x38
    /* DD9CDC 00009270 26240038 */  addiu      $a0, $s1, 0x38
    /* DD9CE0 00009274 AFAF013C */  sw         $t7, 0x13C($sp)
    /* DD9CE4 00009278 16210005 */  bne        $s1, $at, .L00009290
    /* DD9CE8 0000927C AFAF0104 */   sw        $t7, 0x104($sp)
    /* DD9CEC 00009280 0C000000 */  jal        func_00000000
    /* DD9CF0 00009284 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9CF4 00009288 1040000F */  beqz       $v0, .L000092C8
    /* DD9CF8 0000928C 00402025 */   or        $a0, $v0, $zero
  .L00009290:
    /* DD9CFC 00009290 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9D00 00009294 02202825 */  or         $a1, $s1, $zero
    /* DD9D04 00009298 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9D08 0000929C AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9D0C 000092A0 0C000000 */  jal        func_00000000
    /* DD9D10 000092A4 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9D14 000092A8 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9D18 000092AC 3C014000 */  lui        $at, (0x40000000 >> 16)
    /* DD9D1C 000092B0 44814000 */  mtc1       $at, $f8
    /* DD9D20 000092B4 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DD9D24 000092B8 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DD9D28 000092BC AC8D000C */  sw         $t5, 0xC($a0)
    /* DD9D2C 000092C0 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9D30 000092C4 E4880010 */  swc1       $f8, 0x10($a0)
  .L000092C8:
    /* DD9D34 000092C8 3C0E0001 */  lui        $t6, %hi(func_00008744 + 0x10)
    /* DD9D38 000092CC 8DCE8754 */  lw         $t6, %lo(func_00008744 + 0x10)($t6)
    /* DD9D3C 000092D0 2401FFB0 */  addiu      $at, $zero, -0x50
    /* DD9D40 000092D4 26240050 */  addiu      $a0, $s1, 0x50
    /* DD9D44 000092D8 AFAE0138 */  sw         $t6, 0x138($sp)
    /* DD9D48 000092DC 16210005 */  bne        $s1, $at, .L000092F4
    /* DD9D4C 000092E0 AFAE0104 */   sw        $t6, 0x104($sp)
    /* DD9D50 000092E4 0C000000 */  jal        func_00000000
    /* DD9D54 000092E8 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9D58 000092EC 1040000F */  beqz       $v0, .L0000932C
    /* DD9D5C 000092F0 00402025 */   or        $a0, $v0, $zero
  .L000092F4:
    /* DD9D60 000092F4 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9D64 000092F8 02202825 */  or         $a1, $s1, $zero
    /* DD9D68 000092FC 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9D6C 00009300 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9D70 00009304 0C000000 */  jal        func_00000000
    /* DD9D74 00009308 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9D78 0000930C 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9D7C 00009310 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DD9D80 00009314 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DD9D84 00009318 3C010000 */  lui        $at, %hi(func_0000085C + 0x14)
    /* DD9D88 0000931C AC99000C */  sw         $t9, 0xC($a0)
    /* DD9D8C 00009320 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9D90 00009324 C42A0870 */  lwc1       $f10, %lo(func_0000085C + 0x14)($at)
    /* DD9D94 00009328 E48A0010 */  swc1       $f10, 0x10($a0)
  .L0000932C:
    /* DD9D98 0000932C 3C0D0001 */  lui        $t5, %hi(func_00008744 + 0x14)
    /* DD9D9C 00009330 8DAD8758 */  lw         $t5, %lo(func_00008744 + 0x14)($t5)
    /* DD9DA0 00009334 2401FF98 */  addiu      $at, $zero, -0x68
    /* DD9DA4 00009338 26240068 */  addiu      $a0, $s1, 0x68
    /* DD9DA8 0000933C AFAD0134 */  sw         $t5, 0x134($sp)
    /* DD9DAC 00009340 16210005 */  bne        $s1, $at, .L00009358
    /* DD9DB0 00009344 AFAD0104 */   sw        $t5, 0x104($sp)
    /* DD9DB4 00009348 0C000000 */  jal        func_00000000
    /* DD9DB8 0000934C 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9DBC 00009350 1040000F */  beqz       $v0, .L00009390
    /* DD9DC0 00009354 00402025 */   or        $a0, $v0, $zero
  .L00009358:
    /* DD9DC4 00009358 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9DC8 0000935C 02202825 */  or         $a1, $s1, $zero
    /* DD9DCC 00009360 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9DD0 00009364 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9DD4 00009368 0C000000 */  jal        func_00000000
    /* DD9DD8 0000936C AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9DDC 00009370 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9DE0 00009374 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DD9DE4 00009378 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DD9DE8 0000937C 3C010000 */  lui        $at, %hi(func_0000085C + 0x18)
    /* DD9DEC 00009380 AC98000C */  sw         $t8, 0xC($a0)
    /* DD9DF0 00009384 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9DF4 00009388 C4300874 */  lwc1       $f16, %lo(func_0000085C + 0x18)($at)
    /* DD9DF8 0000938C E4900010 */  swc1       $f16, 0x10($a0)
  .L00009390:
    /* DD9DFC 00009390 3C190001 */  lui        $t9, %hi(func_00008744 + 0x18)
    /* DD9E00 00009394 8F39875C */  lw         $t9, %lo(func_00008744 + 0x18)($t9)
    /* DD9E04 00009398 2401FF80 */  addiu      $at, $zero, -0x80
    /* DD9E08 0000939C 26240080 */  addiu      $a0, $s1, 0x80
    /* DD9E0C 000093A0 AFB90130 */  sw         $t9, 0x130($sp)
    /* DD9E10 000093A4 16210005 */  bne        $s1, $at, .L000093BC
    /* DD9E14 000093A8 AFB90104 */   sw        $t9, 0x104($sp)
    /* DD9E18 000093AC 0C000000 */  jal        func_00000000
    /* DD9E1C 000093B0 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9E20 000093B4 1040000F */  beqz       $v0, .L000093F4
    /* DD9E24 000093B8 00402025 */   or        $a0, $v0, $zero
  .L000093BC:
    /* DD9E28 000093BC 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9E2C 000093C0 02202825 */  or         $a1, $s1, $zero
    /* DD9E30 000093C4 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9E34 000093C8 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9E38 000093CC 0C000000 */  jal        func_00000000
    /* DD9E3C 000093D0 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9E40 000093D4 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9E44 000093D8 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DD9E48 000093DC 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DD9E4C 000093E0 3C010000 */  lui        $at, %hi(func_0000085C + 0x1C)
    /* DD9E50 000093E4 AC8F000C */  sw         $t7, 0xC($a0)
    /* DD9E54 000093E8 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9E58 000093EC C4320878 */  lwc1       $f18, %lo(func_0000085C + 0x1C)($at)
    /* DD9E5C 000093F0 E4920010 */  swc1       $f18, 0x10($a0)
  .L000093F4:
    /* DD9E60 000093F4 3C180001 */  lui        $t8, %hi(func_00008744 + 0x1C)
    /* DD9E64 000093F8 8F188760 */  lw         $t8, %lo(func_00008744 + 0x1C)($t8)
    /* DD9E68 000093FC 2401FF68 */  addiu      $at, $zero, -0x98
    /* DD9E6C 00009400 26240098 */  addiu      $a0, $s1, 0x98
    /* DD9E70 00009404 AFB8012C */  sw         $t8, 0x12C($sp)
    /* DD9E74 00009408 16210005 */  bne        $s1, $at, .L00009420
    /* DD9E78 0000940C AFB80104 */   sw        $t8, 0x104($sp)
    /* DD9E7C 00009410 0C000000 */  jal        func_00000000
    /* DD9E80 00009414 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9E84 00009418 1040000F */  beqz       $v0, .L00009458
    /* DD9E88 0000941C 00402025 */   or        $a0, $v0, $zero
  .L00009420:
    /* DD9E8C 00009420 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9E90 00009424 02202825 */  or         $a1, $s1, $zero
    /* DD9E94 00009428 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9E98 0000942C AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9E9C 00009430 0C000000 */  jal        func_00000000
    /* DD9EA0 00009434 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9EA4 00009438 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9EA8 0000943C 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DD9EAC 00009440 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DD9EB0 00009444 3C010000 */  lui        $at, %hi(.L0000087C)
    /* DD9EB4 00009448 AC8E000C */  sw         $t6, 0xC($a0)
    /* DD9EB8 0000944C AC800014 */  sw         $zero, 0x14($a0)
    /* DD9EBC 00009450 C424087C */  lwc1       $f4, %lo(.L0000087C)($at)
    /* DD9EC0 00009454 E4840010 */  swc1       $f4, 0x10($a0)
  .L00009458:
    /* DD9EC4 00009458 3C0F0001 */  lui        $t7, %hi(func_00008744 + 0x20)
    /* DD9EC8 0000945C 8DEF8764 */  lw         $t7, %lo(func_00008744 + 0x20)($t7)
    /* DD9ECC 00009460 2401FF50 */  addiu      $at, $zero, -0xB0
    /* DD9ED0 00009464 262400B0 */  addiu      $a0, $s1, 0xB0
    /* DD9ED4 00009468 AFAF0128 */  sw         $t7, 0x128($sp)
    /* DD9ED8 0000946C 16210005 */  bne        $s1, $at, .L00009484
    /* DD9EDC 00009470 AFAF0104 */   sw        $t7, 0x104($sp)
    /* DD9EE0 00009474 0C000000 */  jal        func_00000000
    /* DD9EE4 00009478 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9EE8 0000947C 1040000E */  beqz       $v0, .L000094B8
    /* DD9EEC 00009480 00402025 */   or        $a0, $v0, $zero
  .L00009484:
    /* DD9EF0 00009484 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9EF4 00009488 02202825 */  or         $a1, $s1, $zero
    /* DD9EF8 0000948C 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9EFC 00009490 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9F00 00009494 0C000000 */  jal        func_00000000
    /* DD9F04 00009498 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9F08 0000949C 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9F0C 000094A0 44803000 */  mtc1       $zero, $f6
    /* DD9F10 000094A4 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DD9F14 000094A8 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DD9F18 000094AC AC8D000C */  sw         $t5, 0xC($a0)
    /* DD9F1C 000094B0 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9F20 000094B4 E4860010 */  swc1       $f6, 0x10($a0)
  .L000094B8:
    /* DD9F24 000094B8 3C0E0001 */  lui        $t6, %hi(func_00008744 + 0x24)
    /* DD9F28 000094BC 8DCE8768 */  lw         $t6, %lo(func_00008744 + 0x24)($t6)
    /* DD9F2C 000094C0 2401FF38 */  addiu      $at, $zero, -0xC8
    /* DD9F30 000094C4 262400C8 */  addiu      $a0, $s1, 0xC8
    /* DD9F34 000094C8 AFAE0124 */  sw         $t6, 0x124($sp)
    /* DD9F38 000094CC 16210005 */  bne        $s1, $at, .L000094E4
    /* DD9F3C 000094D0 AFAE0104 */   sw        $t6, 0x104($sp)
    /* DD9F40 000094D4 0C000000 */  jal        func_00000000
    /* DD9F44 000094D8 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9F48 000094DC 1040000F */  beqz       $v0, .L0000951C
    /* DD9F4C 000094E0 00402025 */   or        $a0, $v0, $zero
  .L000094E4:
    /* DD9F50 000094E4 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9F54 000094E8 02202825 */  or         $a1, $s1, $zero
    /* DD9F58 000094EC 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9F5C 000094F0 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9F60 000094F4 0C000000 */  jal        func_00000000
    /* DD9F64 000094F8 AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9F68 000094FC 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9F6C 00009500 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DD9F70 00009504 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DD9F74 00009508 3C010000 */  lui        $at, %hi(D_00000880)
    /* DD9F78 0000950C AC99000C */  sw         $t9, 0xC($a0)
    /* DD9F7C 00009510 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9F80 00009514 C4280880 */  lwc1       $f8, %lo(D_00000880)($at)
    /* DD9F84 00009518 E4880010 */  swc1       $f8, 0x10($a0)
  .L0000951C:
    /* DD9F88 0000951C 3C0D0001 */  lui        $t5, %hi(func_00008744 + 0x28)
    /* DD9F8C 00009520 8DAD876C */  lw         $t5, %lo(func_00008744 + 0x28)($t5)
    /* DD9F90 00009524 2401FF20 */  addiu      $at, $zero, -0xE0
    /* DD9F94 00009528 262400E0 */  addiu      $a0, $s1, 0xE0
    /* DD9F98 0000952C AFAD0120 */  sw         $t5, 0x120($sp)
    /* DD9F9C 00009530 16210005 */  bne        $s1, $at, .L00009548
    /* DD9FA0 00009534 AFAD0104 */   sw        $t5, 0x104($sp)
    /* DD9FA4 00009538 0C000000 */  jal        func_00000000
    /* DD9FA8 0000953C 24040018 */   addiu     $a0, $zero, 0x18
    /* DD9FAC 00009540 1040000F */  beqz       $v0, .L00009580
    /* DD9FB0 00009544 00402025 */   or        $a0, $v0, $zero
  .L00009548:
    /* DD9FB4 00009548 8FA60104 */  lw         $a2, 0x104($sp)
    /* DD9FB8 0000954C 02202825 */  or         $a1, $s1, $zero
    /* DD9FBC 00009550 24070001 */  addiu      $a3, $zero, 0x1
    /* DD9FC0 00009554 AFA40108 */  sw         $a0, 0x108($sp)
    /* DD9FC4 00009558 0C000000 */  jal        func_00000000
    /* DD9FC8 0000955C AFA60008 */   sw        $a2, 0x8($sp)
    /* DD9FCC 00009560 8FA40108 */  lw         $a0, 0x108($sp)
    /* DD9FD0 00009564 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DD9FD4 00009568 44815000 */  mtc1       $at, $f10
    /* DD9FD8 0000956C 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DD9FDC 00009570 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DD9FE0 00009574 AC98000C */  sw         $t8, 0xC($a0)
    /* DD9FE4 00009578 AC800014 */  sw         $zero, 0x14($a0)
    /* DD9FE8 0000957C E48A0010 */  swc1       $f10, 0x10($a0)
  .L00009580:
    /* DD9FEC 00009580 3C190001 */  lui        $t9, %hi(func_00008744 + 0x2C)
    /* DD9FF0 00009584 8F398770 */  lw         $t9, %lo(func_00008744 + 0x2C)($t9)
    /* DD9FF4 00009588 2401FF08 */  addiu      $at, $zero, -0xF8
    /* DD9FF8 0000958C 262400F8 */  addiu      $a0, $s1, 0xF8
    /* DD9FFC 00009590 AFB9011C */  sw         $t9, 0x11C($sp)
    /* DDA000 00009594 16210005 */  bne        $s1, $at, .L000095AC
    /* DDA004 00009598 AFB90104 */   sw        $t9, 0x104($sp)
    /* DDA008 0000959C 0C000000 */  jal        func_00000000
    /* DDA00C 000095A0 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA010 000095A4 1040000F */  beqz       $v0, .L000095E4
    /* DDA014 000095A8 00402025 */   or        $a0, $v0, $zero
  .L000095AC:
    /* DDA018 000095AC 8FA60104 */  lw         $a2, 0x104($sp)
    /* DDA01C 000095B0 02202825 */  or         $a1, $s1, $zero
    /* DDA020 000095B4 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA024 000095B8 AFA40108 */  sw         $a0, 0x108($sp)
    /* DDA028 000095BC 0C000000 */  jal        func_00000000
    /* DDA02C 000095C0 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA030 000095C4 8FA40108 */  lw         $a0, 0x108($sp)
    /* DDA034 000095C8 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA038 000095CC 44818000 */  mtc1       $at, $f16
    /* DDA03C 000095D0 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDA040 000095D4 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDA044 000095D8 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDA048 000095DC AC800014 */  sw         $zero, 0x14($a0)
    /* DDA04C 000095E0 E4900010 */  swc1       $f16, 0x10($a0)
  .L000095E4:
    /* DDA050 000095E4 3C180001 */  lui        $t8, %hi(func_00008744 + 0x30)
    /* DDA054 000095E8 8F188774 */  lw         $t8, %lo(func_00008744 + 0x30)($t8)
    /* DDA058 000095EC 2401FEF0 */  addiu      $at, $zero, -0x110
    /* DDA05C 000095F0 26240110 */  addiu      $a0, $s1, 0x110
    /* DDA060 000095F4 AFB80118 */  sw         $t8, 0x118($sp)
    /* DDA064 000095F8 16210005 */  bne        $s1, $at, .L00009610
    /* DDA068 000095FC AFB80104 */   sw        $t8, 0x104($sp)
    /* DDA06C 00009600 0C000000 */  jal        func_00000000
    /* DDA070 00009604 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA074 00009608 1040000F */  beqz       $v0, .L00009648
    /* DDA078 0000960C 00402025 */   or        $a0, $v0, $zero
  .L00009610:
    /* DDA07C 00009610 8FA60104 */  lw         $a2, 0x104($sp)
    /* DDA080 00009614 02202825 */  or         $a1, $s1, $zero
    /* DDA084 00009618 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA088 0000961C AFA40108 */  sw         $a0, 0x108($sp)
    /* DDA08C 00009620 0C000000 */  jal        func_00000000
    /* DDA090 00009624 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA094 00009628 8FA40108 */  lw         $a0, 0x108($sp)
    /* DDA098 0000962C 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA09C 00009630 44819000 */  mtc1       $at, $f18
    /* DDA0A0 00009634 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDA0A4 00009638 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDA0A8 0000963C AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA0AC 00009640 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA0B0 00009644 E4920010 */  swc1       $f18, 0x10($a0)
  .L00009648:
    /* DDA0B4 00009648 2401FAC0 */  addiu      $at, $zero, -0x540
    /* DDA0B8 0000964C 16410005 */  bne        $s2, $at, .L00009664
    /* DDA0BC 00009650 26500540 */   addiu     $s0, $s2, 0x540
    /* DDA0C0 00009654 0C000000 */  jal        func_00000000
    /* DDA0C4 00009658 240402C0 */   addiu     $a0, $zero, 0x2C0
    /* DDA0C8 0000965C 10400313 */  beqz       $v0, .L0000A2AC
    /* DDA0CC 00009660 00408025 */   or        $s0, $v0, $zero
  .L00009664:
    /* DDA0D0 00009664 16000005 */  bnez       $s0, .L0000967C
    /* DDA0D4 00009668 02008825 */   or        $s1, $s0, $zero
    /* DDA0D8 0000966C 0C000000 */  jal        func_00000000
    /* DDA0DC 00009670 24040008 */   addiu     $a0, $zero, 0x8
    /* DDA0E0 00009674 10400005 */  beqz       $v0, .L0000968C
    /* DDA0E4 00009678 00408825 */   or        $s1, $v0, $zero
  .L0000967C:
    /* DDA0E8 0000967C 3C0F0001 */  lui        $t7, %hi(func_00008744 + 0x34)
    /* DDA0EC 00009680 25EF8778 */  addiu      $t7, $t7, %lo(func_00008744 + 0x34)
    /* DDA0F0 00009684 AE2F0000 */  sw         $t7, 0x0($s1)
    /* DDA0F4 00009688 AE200004 */  sw         $zero, 0x4($s1)
  .L0000968C:
    /* DDA0F8 0000968C 3C180001 */  lui        $t8, %hi(func_00008744 + 0x48)
    /* DDA0FC 00009690 8F18878C */  lw         $t8, %lo(func_00008744 + 0x48)($t8)
    /* DDA100 00009694 2401FFF8 */  addiu      $at, $zero, -0x8
    /* DDA104 00009698 26040008 */  addiu      $a0, $s0, 0x8
    /* DDA108 0000969C AFB80100 */  sw         $t8, 0x100($sp)
    /* DDA10C 000096A0 16010005 */  bne        $s0, $at, .L000096B8
    /* DDA110 000096A4 AFB80104 */   sw        $t8, 0x104($sp)
    /* DDA114 000096A8 0C000000 */  jal        func_00000000
    /* DDA118 000096AC 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA11C 000096B0 1040000F */  beqz       $v0, .L000096F0
    /* DDA120 000096B4 00402025 */   or        $a0, $v0, $zero
  .L000096B8:
    /* DDA124 000096B8 8FA60104 */  lw         $a2, 0x104($sp)
    /* DDA128 000096BC 02002825 */  or         $a1, $s0, $zero
    /* DDA12C 000096C0 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA130 000096C4 AFA4008C */  sw         $a0, 0x8C($sp)
    /* DDA134 000096C8 0C000000 */  jal        func_00000000
    /* DDA138 000096CC AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA13C 000096D0 8FA4008C */  lw         $a0, 0x8C($sp)
    /* DDA140 000096D4 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDA144 000096D8 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDA148 000096DC 3C010000 */  lui        $at, %hi(D_00000884)
    /* DDA14C 000096E0 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA150 000096E4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA154 000096E8 C4240884 */  lwc1       $f4, %lo(D_00000884)($at)
    /* DDA158 000096EC E4840010 */  swc1       $f4, 0x10($a0)
  .L000096F0:
    /* DDA15C 000096F0 3C0F0001 */  lui        $t7, %hi(func_00008744 + 0x4C)
    /* DDA160 000096F4 8DEF8790 */  lw         $t7, %lo(func_00008744 + 0x4C)($t7)
    /* DDA164 000096F8 27B800FC */  addiu      $t8, $sp, 0xFC
    /* DDA168 000096FC 27B1007C */  addiu      $s1, $sp, 0x7C
    /* DDA16C 00009700 AFAF00FC */  sw         $t7, 0xFC($sp)
    /* DDA170 00009704 8F0D0000 */  lw         $t5, 0x0($t8)
    /* DDA174 00009708 2401FFE0 */  addiu      $at, $zero, -0x20
    /* DDA178 0000970C 26040020 */  addiu      $a0, $s0, 0x20
    /* DDA17C 00009710 16010005 */  bne        $s0, $at, .L00009728
    /* DDA180 00009714 AE2D0000 */   sw        $t5, 0x0($s1)
    /* DDA184 00009718 0C000000 */  jal        func_00000000
    /* DDA188 0000971C 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA18C 00009720 1040000F */  beqz       $v0, .L00009760
    /* DDA190 00009724 00402025 */   or        $a0, $v0, $zero
  .L00009728:
    /* DDA194 00009728 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA198 0000972C AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA19C 00009730 02002825 */  or         $a1, $s0, $zero
    /* DDA1A0 00009734 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA1A4 00009738 0C000000 */  jal        func_00000000
    /* DDA1A8 0000973C AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA1AC 00009740 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA1B0 00009744 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA1B4 00009748 44813000 */  mtc1       $at, $f6
    /* DDA1B8 0000974C 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DDA1BC 00009750 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DDA1C0 00009754 AC98000C */  sw         $t8, 0xC($a0)
    /* DDA1C4 00009758 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA1C8 0000975C E4860010 */  swc1       $f6, 0x10($a0)
  .L00009760:
    /* DDA1CC 00009760 3C190001 */  lui        $t9, %hi(func_00008744 + 0x50)
    /* DDA1D0 00009764 8F398794 */  lw         $t9, %lo(func_00008744 + 0x50)($t9)
    /* DDA1D4 00009768 27AD00F8 */  addiu      $t5, $sp, 0xF8
    /* DDA1D8 0000976C 2401FFC8 */  addiu      $at, $zero, -0x38
    /* DDA1DC 00009770 AFB900F8 */  sw         $t9, 0xF8($sp)
    /* DDA1E0 00009774 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDA1E4 00009778 26040038 */  addiu      $a0, $s0, 0x38
    /* DDA1E8 0000977C 16010005 */  bne        $s0, $at, .L00009794
    /* DDA1EC 00009780 AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDA1F0 00009784 0C000000 */  jal        func_00000000
    /* DDA1F4 00009788 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA1F8 0000978C 1040000F */  beqz       $v0, .L000097CC
    /* DDA1FC 00009790 00402025 */   or        $a0, $v0, $zero
  .L00009794:
    /* DDA200 00009794 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA204 00009798 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA208 0000979C 02002825 */  or         $a1, $s0, $zero
    /* DDA20C 000097A0 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA210 000097A4 0C000000 */  jal        func_00000000
    /* DDA214 000097A8 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA218 000097AC 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA21C 000097B0 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA220 000097B4 44814000 */  mtc1       $at, $f8
    /* DDA224 000097B8 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDA228 000097BC 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDA22C 000097C0 AC8D000C */  sw         $t5, 0xC($a0)
    /* DDA230 000097C4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA234 000097C8 E4880010 */  swc1       $f8, 0x10($a0)
  .L000097CC:
    /* DDA238 000097CC 3C0E0001 */  lui        $t6, %hi(func_00008744 + 0x54)
    /* DDA23C 000097D0 8DCE8798 */  lw         $t6, %lo(func_00008744 + 0x54)($t6)
    /* DDA240 000097D4 27AF00F4 */  addiu      $t7, $sp, 0xF4
    /* DDA244 000097D8 2401FFB0 */  addiu      $at, $zero, -0x50
    /* DDA248 000097DC AFAE00F4 */  sw         $t6, 0xF4($sp)
    /* DDA24C 000097E0 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDA250 000097E4 26040050 */  addiu      $a0, $s0, 0x50
    /* DDA254 000097E8 16010005 */  bne        $s0, $at, .L00009800
    /* DDA258 000097EC AE390000 */   sw        $t9, 0x0($s1)
    /* DDA25C 000097F0 0C000000 */  jal        func_00000000
    /* DDA260 000097F4 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA264 000097F8 1040000F */  beqz       $v0, .L00009838
    /* DDA268 000097FC 00402025 */   or        $a0, $v0, $zero
  .L00009800:
    /* DDA26C 00009800 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA270 00009804 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA274 00009808 02002825 */  or         $a1, $s0, $zero
    /* DDA278 0000980C 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA27C 00009810 0C000000 */  jal        func_00000000
    /* DDA280 00009814 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA284 00009818 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA288 0000981C 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA28C 00009820 44815000 */  mtc1       $at, $f10
    /* DDA290 00009824 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDA294 00009828 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDA298 0000982C AC8F000C */  sw         $t7, 0xC($a0)
    /* DDA29C 00009830 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA2A0 00009834 E48A0010 */  swc1       $f10, 0x10($a0)
  .L00009838:
    /* DDA2A4 00009838 3C180001 */  lui        $t8, %hi(func_00008744 + 0x58)
    /* DDA2A8 0000983C 8F18879C */  lw         $t8, %lo(func_00008744 + 0x58)($t8)
    /* DDA2AC 00009840 27B900F0 */  addiu      $t9, $sp, 0xF0
    /* DDA2B0 00009844 2401FF98 */  addiu      $at, $zero, -0x68
    /* DDA2B4 00009848 AFB800F0 */  sw         $t8, 0xF0($sp)
    /* DDA2B8 0000984C 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDA2BC 00009850 26040068 */  addiu      $a0, $s0, 0x68
    /* DDA2C0 00009854 16010005 */  bne        $s0, $at, .L0000986C
    /* DDA2C4 00009858 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDA2C8 0000985C 0C000000 */  jal        func_00000000
    /* DDA2CC 00009860 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA2D0 00009864 1040000F */  beqz       $v0, .L000098A4
    /* DDA2D4 00009868 00402025 */   or        $a0, $v0, $zero
  .L0000986C:
    /* DDA2D8 0000986C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA2DC 00009870 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA2E0 00009874 02002825 */  or         $a1, $s0, $zero
    /* DDA2E4 00009878 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA2E8 0000987C 0C000000 */  jal        func_00000000
    /* DDA2EC 00009880 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA2F0 00009884 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA2F4 00009888 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA2F8 0000988C 44818000 */  mtc1       $at, $f16
    /* DDA2FC 00009890 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DDA300 00009894 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DDA304 00009898 AC99000C */  sw         $t9, 0xC($a0)
    /* DDA308 0000989C AC800014 */  sw         $zero, 0x14($a0)
    /* DDA30C 000098A0 E4900010 */  swc1       $f16, 0x10($a0)
  .L000098A4:
    /* DDA310 000098A4 3C0D0001 */  lui        $t5, %hi(func_00008744 + 0x5C)
    /* DDA314 000098A8 8DAD87A0 */  lw         $t5, %lo(func_00008744 + 0x5C)($t5)
    /* DDA318 000098AC 27AE00EC */  addiu      $t6, $sp, 0xEC
    /* DDA31C 000098B0 2401FF80 */  addiu      $at, $zero, -0x80
    /* DDA320 000098B4 AFAD00EC */  sw         $t5, 0xEC($sp)
    /* DDA324 000098B8 8DD80000 */  lw         $t8, 0x0($t6)
    /* DDA328 000098BC 26040080 */  addiu      $a0, $s0, 0x80
    /* DDA32C 000098C0 16010005 */  bne        $s0, $at, .L000098D8
    /* DDA330 000098C4 AE380000 */   sw        $t8, 0x0($s1)
    /* DDA334 000098C8 0C000000 */  jal        func_00000000
    /* DDA338 000098CC 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA33C 000098D0 1040000F */  beqz       $v0, .L00009910
    /* DDA340 000098D4 00402025 */   or        $a0, $v0, $zero
  .L000098D8:
    /* DDA344 000098D8 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA348 000098DC AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA34C 000098E0 02002825 */  or         $a1, $s0, $zero
    /* DDA350 000098E4 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA354 000098E8 0C000000 */  jal        func_00000000
    /* DDA358 000098EC AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA35C 000098F0 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA360 000098F4 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA364 000098F8 44819000 */  mtc1       $at, $f18
    /* DDA368 000098FC 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDA36C 00009900 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDA370 00009904 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA374 00009908 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA378 0000990C E4920010 */  swc1       $f18, 0x10($a0)
  .L00009910:
    /* DDA37C 00009910 3C0F0001 */  lui        $t7, %hi(func_000087A4)
    /* DDA380 00009914 8DEF87A4 */  lw         $t7, %lo(func_000087A4)($t7)
    /* DDA384 00009918 27B800E8 */  addiu      $t8, $sp, 0xE8
    /* DDA388 0000991C 2401FF68 */  addiu      $at, $zero, -0x98
    /* DDA38C 00009920 AFAF00E8 */  sw         $t7, 0xE8($sp)
    /* DDA390 00009924 8F0D0000 */  lw         $t5, 0x0($t8)
    /* DDA394 00009928 26040098 */  addiu      $a0, $s0, 0x98
    /* DDA398 0000992C 16010005 */  bne        $s0, $at, .L00009944
    /* DDA39C 00009930 AE2D0000 */   sw        $t5, 0x0($s1)
    /* DDA3A0 00009934 0C000000 */  jal        func_00000000
    /* DDA3A4 00009938 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA3A8 0000993C 1040000F */  beqz       $v0, .L0000997C
    /* DDA3AC 00009940 00402025 */   or        $a0, $v0, $zero
  .L00009944:
    /* DDA3B0 00009944 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA3B4 00009948 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA3B8 0000994C 02002825 */  or         $a1, $s0, $zero
    /* DDA3BC 00009950 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA3C0 00009954 0C000000 */  jal        func_00000000
    /* DDA3C4 00009958 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA3C8 0000995C 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA3CC 00009960 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA3D0 00009964 44812000 */  mtc1       $at, $f4
    /* DDA3D4 00009968 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DDA3D8 0000996C 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DDA3DC 00009970 AC98000C */  sw         $t8, 0xC($a0)
    /* DDA3E0 00009974 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA3E4 00009978 E4840010 */  swc1       $f4, 0x10($a0)
  .L0000997C:
    /* DDA3E8 0000997C 3C190001 */  lui        $t9, %hi(func_000087A4 + 0x4)
    /* DDA3EC 00009980 8F3987A8 */  lw         $t9, %lo(func_000087A4 + 0x4)($t9)
    /* DDA3F0 00009984 27AD00E4 */  addiu      $t5, $sp, 0xE4
    /* DDA3F4 00009988 2401FF50 */  addiu      $at, $zero, -0xB0
    /* DDA3F8 0000998C AFB900E4 */  sw         $t9, 0xE4($sp)
    /* DDA3FC 00009990 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDA400 00009994 260400B0 */  addiu      $a0, $s0, 0xB0
    /* DDA404 00009998 16010005 */  bne        $s0, $at, .L000099B0
    /* DDA408 0000999C AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDA40C 000099A0 0C000000 */  jal        func_00000000
    /* DDA410 000099A4 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA414 000099A8 1040000F */  beqz       $v0, .L000099E8
    /* DDA418 000099AC 00402025 */   or        $a0, $v0, $zero
  .L000099B0:
    /* DDA41C 000099B0 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA420 000099B4 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA424 000099B8 02002825 */  or         $a1, $s0, $zero
    /* DDA428 000099BC 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA42C 000099C0 0C000000 */  jal        func_00000000
    /* DDA430 000099C4 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA434 000099C8 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA438 000099CC 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDA43C 000099D0 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDA440 000099D4 3C010000 */  lui        $at, %hi(func_00000888)
    /* DDA444 000099D8 AC8D000C */  sw         $t5, 0xC($a0)
    /* DDA448 000099DC AC800014 */  sw         $zero, 0x14($a0)
    /* DDA44C 000099E0 C4260888 */  lwc1       $f6, %lo(func_00000888)($at)
    /* DDA450 000099E4 E4860010 */  swc1       $f6, 0x10($a0)
  .L000099E8:
    /* DDA454 000099E8 3C0E0001 */  lui        $t6, %hi(func_000087A4 + 0x8)
    /* DDA458 000099EC 8DCE87AC */  lw         $t6, %lo(func_000087A4 + 0x8)($t6)
    /* DDA45C 000099F0 27AF00E0 */  addiu      $t7, $sp, 0xE0
    /* DDA460 000099F4 2401FF38 */  addiu      $at, $zero, -0xC8
    /* DDA464 000099F8 AFAE00E0 */  sw         $t6, 0xE0($sp)
    /* DDA468 000099FC 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDA46C 00009A00 260400C8 */  addiu      $a0, $s0, 0xC8
    /* DDA470 00009A04 16010005 */  bne        $s0, $at, .L00009A1C
    /* DDA474 00009A08 AE390000 */   sw        $t9, 0x0($s1)
    /* DDA478 00009A0C 0C000000 */  jal        func_00000000
    /* DDA47C 00009A10 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA480 00009A14 1040000F */  beqz       $v0, .L00009A54
    /* DDA484 00009A18 00402025 */   or        $a0, $v0, $zero
  .L00009A1C:
    /* DDA488 00009A1C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA48C 00009A20 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA490 00009A24 02002825 */  or         $a1, $s0, $zero
    /* DDA494 00009A28 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA498 00009A2C 0C000000 */  jal        func_00000000
    /* DDA49C 00009A30 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA4A0 00009A34 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA4A4 00009A38 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDA4A8 00009A3C 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDA4AC 00009A40 3C010000 */  lui        $at, %hi(func_00000888 + 0x4)
    /* DDA4B0 00009A44 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDA4B4 00009A48 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA4B8 00009A4C C428088C */  lwc1       $f8, %lo(func_00000888 + 0x4)($at)
    /* DDA4BC 00009A50 E4880010 */  swc1       $f8, 0x10($a0)
  .L00009A54:
    /* DDA4C0 00009A54 3C180001 */  lui        $t8, %hi(func_000087A4 + 0xC)
    /* DDA4C4 00009A58 8F1887B0 */  lw         $t8, %lo(func_000087A4 + 0xC)($t8)
    /* DDA4C8 00009A5C 27B900DC */  addiu      $t9, $sp, 0xDC
    /* DDA4CC 00009A60 2401FF20 */  addiu      $at, $zero, -0xE0
    /* DDA4D0 00009A64 AFB800DC */  sw         $t8, 0xDC($sp)
    /* DDA4D4 00009A68 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDA4D8 00009A6C 260400E0 */  addiu      $a0, $s0, 0xE0
    /* DDA4DC 00009A70 16010005 */  bne        $s0, $at, .L00009A88
    /* DDA4E0 00009A74 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDA4E4 00009A78 0C000000 */  jal        func_00000000
    /* DDA4E8 00009A7C 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA4EC 00009A80 1040000F */  beqz       $v0, .L00009AC0
    /* DDA4F0 00009A84 00402025 */   or        $a0, $v0, $zero
  .L00009A88:
    /* DDA4F4 00009A88 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA4F8 00009A8C AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA4FC 00009A90 02002825 */  or         $a1, $s0, $zero
    /* DDA500 00009A94 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA504 00009A98 0C000000 */  jal        func_00000000
    /* DDA508 00009A9C AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA50C 00009AA0 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA510 00009AA4 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DDA514 00009AA8 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DDA518 00009AAC 3C010000 */  lui        $at, %hi(func_00000888 + 0x8)
    /* DDA51C 00009AB0 AC99000C */  sw         $t9, 0xC($a0)
    /* DDA520 00009AB4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA524 00009AB8 C42A0890 */  lwc1       $f10, %lo(func_00000888 + 0x8)($at)
    /* DDA528 00009ABC E48A0010 */  swc1       $f10, 0x10($a0)
  .L00009AC0:
    /* DDA52C 00009AC0 3C0D0001 */  lui        $t5, %hi(func_000087A4 + 0x10)
    /* DDA530 00009AC4 8DAD87B4 */  lw         $t5, %lo(func_000087A4 + 0x10)($t5)
    /* DDA534 00009AC8 27AE00D8 */  addiu      $t6, $sp, 0xD8
    /* DDA538 00009ACC 2401FF08 */  addiu      $at, $zero, -0xF8
    /* DDA53C 00009AD0 AFAD00D8 */  sw         $t5, 0xD8($sp)
    /* DDA540 00009AD4 8DD80000 */  lw         $t8, 0x0($t6)
    /* DDA544 00009AD8 260400F8 */  addiu      $a0, $s0, 0xF8
    /* DDA548 00009ADC 16010005 */  bne        $s0, $at, .L00009AF4
    /* DDA54C 00009AE0 AE380000 */   sw        $t8, 0x0($s1)
    /* DDA550 00009AE4 0C000000 */  jal        func_00000000
    /* DDA554 00009AE8 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA558 00009AEC 1040000F */  beqz       $v0, .L00009B2C
    /* DDA55C 00009AF0 00402025 */   or        $a0, $v0, $zero
  .L00009AF4:
    /* DDA560 00009AF4 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA564 00009AF8 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA568 00009AFC 02002825 */  or         $a1, $s0, $zero
    /* DDA56C 00009B00 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA570 00009B04 0C000000 */  jal        func_00000000
    /* DDA574 00009B08 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA578 00009B0C 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA57C 00009B10 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDA580 00009B14 44818000 */  mtc1       $at, $f16
    /* DDA584 00009B18 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDA588 00009B1C 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDA58C 00009B20 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA590 00009B24 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA594 00009B28 E4900010 */  swc1       $f16, 0x10($a0)
  .L00009B2C:
    /* DDA598 00009B2C 3C0F0001 */  lui        $t7, %hi(func_000087A4 + 0x14)
    /* DDA59C 00009B30 8DEF87B8 */  lw         $t7, %lo(func_000087A4 + 0x14)($t7)
    /* DDA5A0 00009B34 27B800D4 */  addiu      $t8, $sp, 0xD4
    /* DDA5A4 00009B38 2401FEF0 */  addiu      $at, $zero, -0x110
    /* DDA5A8 00009B3C AFAF00D4 */  sw         $t7, 0xD4($sp)
    /* DDA5AC 00009B40 8F0D0000 */  lw         $t5, 0x0($t8)
    /* DDA5B0 00009B44 26040110 */  addiu      $a0, $s0, 0x110
    /* DDA5B4 00009B48 16010005 */  bne        $s0, $at, .L00009B60
    /* DDA5B8 00009B4C AE2D0000 */   sw        $t5, 0x0($s1)
    /* DDA5BC 00009B50 0C000000 */  jal        func_00000000
    /* DDA5C0 00009B54 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA5C4 00009B58 1040000F */  beqz       $v0, .L00009B98
    /* DDA5C8 00009B5C 00402025 */   or        $a0, $v0, $zero
  .L00009B60:
    /* DDA5CC 00009B60 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA5D0 00009B64 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA5D4 00009B68 02002825 */  or         $a1, $s0, $zero
    /* DDA5D8 00009B6C 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA5DC 00009B70 0C000000 */  jal        func_00000000
    /* DDA5E0 00009B74 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA5E4 00009B78 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA5E8 00009B7C 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DDA5EC 00009B80 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DDA5F0 00009B84 3C010000 */  lui        $at, %hi(func_00000888 + 0xC)
    /* DDA5F4 00009B88 AC98000C */  sw         $t8, 0xC($a0)
    /* DDA5F8 00009B8C AC800014 */  sw         $zero, 0x14($a0)
    /* DDA5FC 00009B90 C4320894 */  lwc1       $f18, %lo(func_00000888 + 0xC)($at)
    /* DDA600 00009B94 E4920010 */  swc1       $f18, 0x10($a0)
  .L00009B98:
    /* DDA604 00009B98 3C190001 */  lui        $t9, %hi(func_000087A4 + 0x18)
    /* DDA608 00009B9C 8F3987BC */  lw         $t9, %lo(func_000087A4 + 0x18)($t9)
    /* DDA60C 00009BA0 27AD00D0 */  addiu      $t5, $sp, 0xD0
    /* DDA610 00009BA4 2401FED8 */  addiu      $at, $zero, -0x128
    /* DDA614 00009BA8 AFB900D0 */  sw         $t9, 0xD0($sp)
    /* DDA618 00009BAC 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDA61C 00009BB0 26040128 */  addiu      $a0, $s0, 0x128
    /* DDA620 00009BB4 16010005 */  bne        $s0, $at, .L00009BCC
    /* DDA624 00009BB8 AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDA628 00009BBC 0C000000 */  jal        func_00000000
    /* DDA62C 00009BC0 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA630 00009BC4 1040000F */  beqz       $v0, .L00009C04
    /* DDA634 00009BC8 00402025 */   or        $a0, $v0, $zero
  .L00009BCC:
    /* DDA638 00009BCC 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA63C 00009BD0 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA640 00009BD4 02002825 */  or         $a1, $s0, $zero
    /* DDA644 00009BD8 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA648 00009BDC 0C000000 */  jal        func_00000000
    /* DDA64C 00009BE0 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA650 00009BE4 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA654 00009BE8 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDA658 00009BEC 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDA65C 00009BF0 3C010000 */  lui        $at, %hi(func_00000888 + 0x10)
    /* DDA660 00009BF4 AC8D000C */  sw         $t5, 0xC($a0)
    /* DDA664 00009BF8 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA668 00009BFC C4240898 */  lwc1       $f4, %lo(func_00000888 + 0x10)($at)
    /* DDA66C 00009C00 E4840010 */  swc1       $f4, 0x10($a0)
  .L00009C04:
    /* DDA670 00009C04 3C0E0001 */  lui        $t6, %hi(func_000087A4 + 0x1C)
    /* DDA674 00009C08 8DCE87C0 */  lw         $t6, %lo(func_000087A4 + 0x1C)($t6)
    /* DDA678 00009C0C 27AF00CC */  addiu      $t7, $sp, 0xCC
    /* DDA67C 00009C10 2401FEC0 */  addiu      $at, $zero, -0x140
    /* DDA680 00009C14 AFAE00CC */  sw         $t6, 0xCC($sp)
    /* DDA684 00009C18 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDA688 00009C1C 26040140 */  addiu      $a0, $s0, 0x140
    /* DDA68C 00009C20 16010005 */  bne        $s0, $at, .L00009C38
    /* DDA690 00009C24 AE390000 */   sw        $t9, 0x0($s1)
    /* DDA694 00009C28 0C000000 */  jal        func_00000000
    /* DDA698 00009C2C 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA69C 00009C30 1040000F */  beqz       $v0, .L00009C70
    /* DDA6A0 00009C34 00402025 */   or        $a0, $v0, $zero
  .L00009C38:
    /* DDA6A4 00009C38 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA6A8 00009C3C AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA6AC 00009C40 02002825 */  or         $a1, $s0, $zero
    /* DDA6B0 00009C44 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA6B4 00009C48 0C000000 */  jal        func_00000000
    /* DDA6B8 00009C4C AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA6BC 00009C50 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA6C0 00009C54 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDA6C4 00009C58 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDA6C8 00009C5C 3C010000 */  lui        $at, %hi(func_00000888 + 0x14)
    /* DDA6CC 00009C60 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDA6D0 00009C64 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA6D4 00009C68 C426089C */  lwc1       $f6, %lo(func_00000888 + 0x14)($at)
    /* DDA6D8 00009C6C E4860010 */  swc1       $f6, 0x10($a0)
  .L00009C70:
    /* DDA6DC 00009C70 3C180001 */  lui        $t8, %hi(func_000087A4 + 0x20)
    /* DDA6E0 00009C74 8F1887C4 */  lw         $t8, %lo(func_000087A4 + 0x20)($t8)
    /* DDA6E4 00009C78 27B900C8 */  addiu      $t9, $sp, 0xC8
    /* DDA6E8 00009C7C 2401FEA8 */  addiu      $at, $zero, -0x158
    /* DDA6EC 00009C80 AFB800C8 */  sw         $t8, 0xC8($sp)
    /* DDA6F0 00009C84 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDA6F4 00009C88 26040158 */  addiu      $a0, $s0, 0x158
    /* DDA6F8 00009C8C 16010005 */  bne        $s0, $at, .L00009CA4
    /* DDA6FC 00009C90 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDA700 00009C94 0C000000 */  jal        func_00000000
    /* DDA704 00009C98 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA708 00009C9C 1040000F */  beqz       $v0, .L00009CDC
    /* DDA70C 00009CA0 00402025 */   or        $a0, $v0, $zero
  .L00009CA4:
    /* DDA710 00009CA4 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA714 00009CA8 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA718 00009CAC 02002825 */  or         $a1, $s0, $zero
    /* DDA71C 00009CB0 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA720 00009CB4 0C000000 */  jal        func_00000000
    /* DDA724 00009CB8 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA728 00009CBC 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA72C 00009CC0 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DDA730 00009CC4 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DDA734 00009CC8 3C010000 */  lui        $at, %hi(func_00000888 + 0x18)
    /* DDA738 00009CCC AC99000C */  sw         $t9, 0xC($a0)
    /* DDA73C 00009CD0 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA740 00009CD4 C42808A0 */  lwc1       $f8, %lo(func_00000888 + 0x18)($at)
    /* DDA744 00009CD8 E4880010 */  swc1       $f8, 0x10($a0)
  .L00009CDC:
    /* DDA748 00009CDC 3C0D0001 */  lui        $t5, %hi(func_000087A4 + 0x24)
    /* DDA74C 00009CE0 8DAD87C8 */  lw         $t5, %lo(func_000087A4 + 0x24)($t5)
    /* DDA750 00009CE4 27AE00C4 */  addiu      $t6, $sp, 0xC4
    /* DDA754 00009CE8 2401FE90 */  addiu      $at, $zero, -0x170
    /* DDA758 00009CEC AFAD00C4 */  sw         $t5, 0xC4($sp)
    /* DDA75C 00009CF0 8DD80000 */  lw         $t8, 0x0($t6)
    /* DDA760 00009CF4 26040170 */  addiu      $a0, $s0, 0x170
    /* DDA764 00009CF8 16010005 */  bne        $s0, $at, .L00009D10
    /* DDA768 00009CFC AE380000 */   sw        $t8, 0x0($s1)
    /* DDA76C 00009D00 0C000000 */  jal        func_00000000
    /* DDA770 00009D04 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA774 00009D08 1040000E */  beqz       $v0, .L00009D44
    /* DDA778 00009D0C 00402025 */   or        $a0, $v0, $zero
  .L00009D10:
    /* DDA77C 00009D10 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA780 00009D14 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA784 00009D18 02002825 */  or         $a1, $s0, $zero
    /* DDA788 00009D1C 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA78C 00009D20 0C000000 */  jal        func_00000000
    /* DDA790 00009D24 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA794 00009D28 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA798 00009D2C 44805000 */  mtc1       $zero, $f10
    /* DDA79C 00009D30 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDA7A0 00009D34 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDA7A4 00009D38 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA7A8 00009D3C AC800014 */  sw         $zero, 0x14($a0)
    /* DDA7AC 00009D40 E48A0010 */  swc1       $f10, 0x10($a0)
  .L00009D44:
    /* DDA7B0 00009D44 3C0F0001 */  lui        $t7, %hi(func_000087A4 + 0x28)
    /* DDA7B4 00009D48 8DEF87CC */  lw         $t7, %lo(func_000087A4 + 0x28)($t7)
    /* DDA7B8 00009D4C 27B800C0 */  addiu      $t8, $sp, 0xC0
    /* DDA7BC 00009D50 2401FE78 */  addiu      $at, $zero, -0x188
    /* DDA7C0 00009D54 AFAF00C0 */  sw         $t7, 0xC0($sp)
    /* DDA7C4 00009D58 8F0D0000 */  lw         $t5, 0x0($t8)
    /* DDA7C8 00009D5C 26040188 */  addiu      $a0, $s0, 0x188
    /* DDA7CC 00009D60 16010005 */  bne        $s0, $at, .L00009D78
    /* DDA7D0 00009D64 AE2D0000 */   sw        $t5, 0x0($s1)
    /* DDA7D4 00009D68 0C000000 */  jal        func_00000000
    /* DDA7D8 00009D6C 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA7DC 00009D70 1040000E */  beqz       $v0, .L00009DAC
    /* DDA7E0 00009D74 00402025 */   or        $a0, $v0, $zero
  .L00009D78:
    /* DDA7E4 00009D78 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA7E8 00009D7C AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA7EC 00009D80 02002825 */  or         $a1, $s0, $zero
    /* DDA7F0 00009D84 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA7F4 00009D88 0C000000 */  jal        func_00000000
    /* DDA7F8 00009D8C AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA7FC 00009D90 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA800 00009D94 44808000 */  mtc1       $zero, $f16
    /* DDA804 00009D98 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DDA808 00009D9C 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DDA80C 00009DA0 AC98000C */  sw         $t8, 0xC($a0)
    /* DDA810 00009DA4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA814 00009DA8 E4900010 */  swc1       $f16, 0x10($a0)
  .L00009DAC:
    /* DDA818 00009DAC 3C190001 */  lui        $t9, %hi(func_000087A4 + 0x2C)
    /* DDA81C 00009DB0 8F3987D0 */  lw         $t9, %lo(func_000087A4 + 0x2C)($t9)
    /* DDA820 00009DB4 27AD00BC */  addiu      $t5, $sp, 0xBC
    /* DDA824 00009DB8 2401FE60 */  addiu      $at, $zero, -0x1A0
    /* DDA828 00009DBC AFB900BC */  sw         $t9, 0xBC($sp)
    /* DDA82C 00009DC0 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDA830 00009DC4 260401A0 */  addiu      $a0, $s0, 0x1A0
    /* DDA834 00009DC8 16010005 */  bne        $s0, $at, .L00009DE0
    /* DDA838 00009DCC AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDA83C 00009DD0 0C000000 */  jal        func_00000000
    /* DDA840 00009DD4 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA844 00009DD8 1040000F */  beqz       $v0, .L00009E18
    /* DDA848 00009DDC 00402025 */   or        $a0, $v0, $zero
  .L00009DE0:
    /* DDA84C 00009DE0 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA850 00009DE4 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA854 00009DE8 02002825 */  or         $a1, $s0, $zero
    /* DDA858 00009DEC 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA85C 00009DF0 0C000000 */  jal        func_00000000
    /* DDA860 00009DF4 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA864 00009DF8 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA868 00009DFC 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDA86C 00009E00 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDA870 00009E04 3C010000 */  lui        $at, %hi(func_00000888 + 0x1C)
    /* DDA874 00009E08 AC8D000C */  sw         $t5, 0xC($a0)
    /* DDA878 00009E0C AC800014 */  sw         $zero, 0x14($a0)
    /* DDA87C 00009E10 C43208A4 */  lwc1       $f18, %lo(func_00000888 + 0x1C)($at)
    /* DDA880 00009E14 E4920010 */  swc1       $f18, 0x10($a0)
  .L00009E18:
    /* DDA884 00009E18 3C0E0001 */  lui        $t6, %hi(func_000087A4 + 0x30)
    /* DDA888 00009E1C 8DCE87D4 */  lw         $t6, %lo(func_000087A4 + 0x30)($t6)
    /* DDA88C 00009E20 27AF00B8 */  addiu      $t7, $sp, 0xB8
    /* DDA890 00009E24 2401FE48 */  addiu      $at, $zero, -0x1B8
    /* DDA894 00009E28 AFAE00B8 */  sw         $t6, 0xB8($sp)
    /* DDA898 00009E2C 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDA89C 00009E30 260401B8 */  addiu      $a0, $s0, 0x1B8
    /* DDA8A0 00009E34 16010005 */  bne        $s0, $at, .L00009E4C
    /* DDA8A4 00009E38 AE390000 */   sw        $t9, 0x0($s1)
    /* DDA8A8 00009E3C 0C000000 */  jal        func_00000000
    /* DDA8AC 00009E40 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA8B0 00009E44 1040000F */  beqz       $v0, .L00009E84
    /* DDA8B4 00009E48 00402025 */   or        $a0, $v0, $zero
  .L00009E4C:
    /* DDA8B8 00009E4C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA8BC 00009E50 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA8C0 00009E54 02002825 */  or         $a1, $s0, $zero
    /* DDA8C4 00009E58 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA8C8 00009E5C 0C000000 */  jal        func_00000000
    /* DDA8CC 00009E60 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA8D0 00009E64 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA8D4 00009E68 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDA8D8 00009E6C 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDA8DC 00009E70 3C010000 */  lui        $at, %hi(.L000008A8)
    /* DDA8E0 00009E74 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDA8E4 00009E78 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA8E8 00009E7C C42408A8 */  lwc1       $f4, %lo(.L000008A8)($at)
    /* DDA8EC 00009E80 E4840010 */  swc1       $f4, 0x10($a0)
  .L00009E84:
    /* DDA8F0 00009E84 3C180001 */  lui        $t8, %hi(func_000087A4 + 0x34)
    /* DDA8F4 00009E88 8F1887D8 */  lw         $t8, %lo(func_000087A4 + 0x34)($t8)
    /* DDA8F8 00009E8C 27B900B4 */  addiu      $t9, $sp, 0xB4
    /* DDA8FC 00009E90 2401FE30 */  addiu      $at, $zero, -0x1D0
    /* DDA900 00009E94 AFB800B4 */  sw         $t8, 0xB4($sp)
    /* DDA904 00009E98 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDA908 00009E9C 260401D0 */  addiu      $a0, $s0, 0x1D0
    /* DDA90C 00009EA0 16010005 */  bne        $s0, $at, .L00009EB8
    /* DDA910 00009EA4 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDA914 00009EA8 0C000000 */  jal        func_00000000
    /* DDA918 00009EAC 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA91C 00009EB0 1040000F */  beqz       $v0, .L00009EF0
    /* DDA920 00009EB4 00402025 */   or        $a0, $v0, $zero
  .L00009EB8:
    /* DDA924 00009EB8 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA928 00009EBC AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA92C 00009EC0 02002825 */  or         $a1, $s0, $zero
    /* DDA930 00009EC4 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA934 00009EC8 0C000000 */  jal        func_00000000
    /* DDA938 00009ECC AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA93C 00009ED0 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA940 00009ED4 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DDA944 00009ED8 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DDA948 00009EDC 3C010000 */  lui        $at, %hi(D_000008AC)
    /* DDA94C 00009EE0 AC99000C */  sw         $t9, 0xC($a0)
    /* DDA950 00009EE4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDA954 00009EE8 C42608AC */  lwc1       $f6, %lo(D_000008AC)($at)
    /* DDA958 00009EEC E4860010 */  swc1       $f6, 0x10($a0)
  .L00009EF0:
    /* DDA95C 00009EF0 3C0D0001 */  lui        $t5, %hi(func_000087A4 + 0x38)
    /* DDA960 00009EF4 8DAD87DC */  lw         $t5, %lo(func_000087A4 + 0x38)($t5)
    /* DDA964 00009EF8 27AE00B0 */  addiu      $t6, $sp, 0xB0
    /* DDA968 00009EFC 2401FE18 */  addiu      $at, $zero, -0x1E8
    /* DDA96C 00009F00 AFAD00B0 */  sw         $t5, 0xB0($sp)
    /* DDA970 00009F04 8DD80000 */  lw         $t8, 0x0($t6)
    /* DDA974 00009F08 260401E8 */  addiu      $a0, $s0, 0x1E8
    /* DDA978 00009F0C 16010005 */  bne        $s0, $at, .L00009F24
    /* DDA97C 00009F10 AE380000 */   sw        $t8, 0x0($s1)
    /* DDA980 00009F14 0C000000 */  jal        func_00000000
    /* DDA984 00009F18 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA988 00009F1C 1040000E */  beqz       $v0, .L00009F58
    /* DDA98C 00009F20 00402025 */   or        $a0, $v0, $zero
  .L00009F24:
    /* DDA990 00009F24 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA994 00009F28 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDA998 00009F2C 02002825 */  or         $a1, $s0, $zero
    /* DDA99C 00009F30 24070001 */  addiu      $a3, $zero, 0x1
    /* DDA9A0 00009F34 0C000000 */  jal        func_00000000
    /* DDA9A4 00009F38 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDA9A8 00009F3C 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDA9AC 00009F40 3C0E0001 */  lui        $t6, %hi(D_00008060)
    /* DDA9B0 00009F44 25CE8060 */  addiu      $t6, $t6, %lo(D_00008060)
    /* DDA9B4 00009F48 240F0019 */  addiu      $t7, $zero, 0x19
    /* DDA9B8 00009F4C AC8F0010 */  sw         $t7, 0x10($a0)
    /* DDA9BC 00009F50 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDA9C0 00009F54 AC800014 */  sw         $zero, 0x14($a0)
  .L00009F58:
    /* DDA9C4 00009F58 3C180001 */  lui        $t8, %hi(func_000087A4 + 0x3C)
    /* DDA9C8 00009F5C 8F1887E0 */  lw         $t8, %lo(func_000087A4 + 0x3C)($t8)
    /* DDA9CC 00009F60 27B900AC */  addiu      $t9, $sp, 0xAC
    /* DDA9D0 00009F64 2401FE00 */  addiu      $at, $zero, -0x200
    /* DDA9D4 00009F68 AFB800AC */  sw         $t8, 0xAC($sp)
    /* DDA9D8 00009F6C 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDA9DC 00009F70 26040200 */  addiu      $a0, $s0, 0x200
    /* DDA9E0 00009F74 16010005 */  bne        $s0, $at, .L00009F8C
    /* DDA9E4 00009F78 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDA9E8 00009F7C 0C000000 */  jal        func_00000000
    /* DDA9EC 00009F80 24040018 */   addiu     $a0, $zero, 0x18
    /* DDA9F0 00009F84 1040000F */  beqz       $v0, .L00009FC4
    /* DDA9F4 00009F88 00402025 */   or        $a0, $v0, $zero
  .L00009F8C:
    /* DDA9F8 00009F8C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDA9FC 00009F90 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAA00 00009F94 02002825 */  or         $a1, $s0, $zero
    /* DDAA04 00009F98 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAA08 00009F9C 0C000000 */  jal        func_00000000
    /* DDAA0C 00009FA0 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAA10 00009FA4 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAA14 00009FA8 3C014248 */  lui        $at, (0x42480000 >> 16)
    /* DDAA18 00009FAC 44814000 */  mtc1       $at, $f8
    /* DDAA1C 00009FB0 3C190001 */  lui        $t9, %hi(D_00008018)
    /* DDAA20 00009FB4 27398018 */  addiu      $t9, $t9, %lo(D_00008018)
    /* DDAA24 00009FB8 AC99000C */  sw         $t9, 0xC($a0)
    /* DDAA28 00009FBC AC800014 */  sw         $zero, 0x14($a0)
    /* DDAA2C 00009FC0 E4880010 */  swc1       $f8, 0x10($a0)
  .L00009FC4:
    /* DDAA30 00009FC4 3C0D0001 */  lui        $t5, %hi(func_000087A4 + 0x40)
    /* DDAA34 00009FC8 8DAD87E4 */  lw         $t5, %lo(func_000087A4 + 0x40)($t5)
    /* DDAA38 00009FCC 27AE00A8 */  addiu      $t6, $sp, 0xA8
    /* DDAA3C 00009FD0 2401FDE8 */  addiu      $at, $zero, -0x218
    /* DDAA40 00009FD4 AFAD00A8 */  sw         $t5, 0xA8($sp)
    /* DDAA44 00009FD8 8DD80000 */  lw         $t8, 0x0($t6)
    /* DDAA48 00009FDC 26040218 */  addiu      $a0, $s0, 0x218
    /* DDAA4C 00009FE0 16010005 */  bne        $s0, $at, .L00009FF8
    /* DDAA50 00009FE4 AE380000 */   sw        $t8, 0x0($s1)
    /* DDAA54 00009FE8 0C000000 */  jal        func_00000000
    /* DDAA58 00009FEC 24040018 */   addiu     $a0, $zero, 0x18
    /* DDAA5C 00009FF0 1040000F */  beqz       $v0, .L0000A030
    /* DDAA60 00009FF4 00402025 */   or        $a0, $v0, $zero
  .L00009FF8:
    /* DDAA64 00009FF8 8E260000 */  lw         $a2, 0x0($s1)
    /* DDAA68 00009FFC AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAA6C 0000A000 02002825 */  or         $a1, $s0, $zero
    /* DDAA70 0000A004 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAA74 0000A008 0C000000 */  jal        func_00000000
    /* DDAA78 0000A00C AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAA7C 0000A010 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAA80 0000A014 3C014316 */  lui        $at, (0x43160000 >> 16)
    /* DDAA84 0000A018 44815000 */  mtc1       $at, $f10
    /* DDAA88 0000A01C 3C0E0001 */  lui        $t6, %hi(D_00008018)
    /* DDAA8C 0000A020 25CE8018 */  addiu      $t6, $t6, %lo(D_00008018)
    /* DDAA90 0000A024 AC8E000C */  sw         $t6, 0xC($a0)
    /* DDAA94 0000A028 AC800014 */  sw         $zero, 0x14($a0)
    /* DDAA98 0000A02C E48A0010 */  swc1       $f10, 0x10($a0)
  .L0000A030:
    /* DDAA9C 0000A030 3C0F0001 */  lui        $t7, %hi(func_000087A4 + 0x44)
    /* DDAAA0 0000A034 8DEF87E8 */  lw         $t7, %lo(func_000087A4 + 0x44)($t7)
    /* DDAAA4 0000A038 27B800A4 */  addiu      $t8, $sp, 0xA4
    /* DDAAA8 0000A03C 2401FDD0 */  addiu      $at, $zero, -0x230
    /* DDAAAC 0000A040 AFAF00A4 */  sw         $t7, 0xA4($sp)
    /* DDAAB0 0000A044 8F0D0000 */  lw         $t5, 0x0($t8)
    /* DDAAB4 0000A048 26040230 */  addiu      $a0, $s0, 0x230
    /* DDAAB8 0000A04C 16010005 */  bne        $s0, $at, .L0000A064
    /* DDAABC 0000A050 AE2D0000 */   sw        $t5, 0x0($s1)
    /* DDAAC0 0000A054 0C000000 */  jal        func_00000000
    /* DDAAC4 0000A058 24040018 */   addiu     $a0, $zero, 0x18
    /* DDAAC8 0000A05C 1040000F */  beqz       $v0, .L0000A09C
    /* DDAACC 0000A060 00402025 */   or        $a0, $v0, $zero
  .L0000A064:
    /* DDAAD0 0000A064 8E260000 */  lw         $a2, 0x0($s1)
    /* DDAAD4 0000A068 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAAD8 0000A06C 02002825 */  or         $a1, $s0, $zero
    /* DDAADC 0000A070 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAAE0 0000A074 0C000000 */  jal        func_00000000
    /* DDAAE4 0000A078 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAAE8 0000A07C 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAAEC 0000A080 3C0142C8 */  lui        $at, (0x42C80000 >> 16)
    /* DDAAF0 0000A084 44818000 */  mtc1       $at, $f16
    /* DDAAF4 0000A088 3C180001 */  lui        $t8, %hi(D_00008018)
    /* DDAAF8 0000A08C 27188018 */  addiu      $t8, $t8, %lo(D_00008018)
    /* DDAAFC 0000A090 AC98000C */  sw         $t8, 0xC($a0)
    /* DDAB00 0000A094 AC800014 */  sw         $zero, 0x14($a0)
    /* DDAB04 0000A098 E4900010 */  swc1       $f16, 0x10($a0)
  .L0000A09C:
    /* DDAB08 0000A09C 3C190001 */  lui        $t9, %hi(func_000087A4 + 0x48)
    /* DDAB0C 0000A0A0 8F3987EC */  lw         $t9, %lo(func_000087A4 + 0x48)($t9)
    /* DDAB10 0000A0A4 27AD00A0 */  addiu      $t5, $sp, 0xA0
    /* DDAB14 0000A0A8 2401FDB8 */  addiu      $at, $zero, -0x248
    /* DDAB18 0000A0AC AFB900A0 */  sw         $t9, 0xA0($sp)
    /* DDAB1C 0000A0B0 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDAB20 0000A0B4 26040248 */  addiu      $a0, $s0, 0x248
    /* DDAB24 0000A0B8 16010005 */  bne        $s0, $at, .L0000A0D0
    /* DDAB28 0000A0BC AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDAB2C 0000A0C0 0C000000 */  jal        func_00000000
    /* DDAB30 0000A0C4 24040018 */   addiu     $a0, $zero, 0x18
    /* DDAB34 0000A0C8 1040000F */  beqz       $v0, .L0000A108
    /* DDAB38 0000A0CC 00402025 */   or        $a0, $v0, $zero
  .L0000A0D0:
    /* DDAB3C 0000A0D0 8E260000 */  lw         $a2, 0x0($s1)
    /* DDAB40 0000A0D4 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAB44 0000A0D8 02002825 */  or         $a1, $s0, $zero
    /* DDAB48 0000A0DC 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAB4C 0000A0E0 0C000000 */  jal        func_00000000
    /* DDAB50 0000A0E4 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAB54 0000A0E8 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAB58 0000A0EC 3C0142C8 */  lui        $at, (0x42C80000 >> 16)
    /* DDAB5C 0000A0F0 44819000 */  mtc1       $at, $f18
    /* DDAB60 0000A0F4 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDAB64 0000A0F8 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDAB68 0000A0FC AC8D000C */  sw         $t5, 0xC($a0)
    /* DDAB6C 0000A100 AC800014 */  sw         $zero, 0x14($a0)
    /* DDAB70 0000A104 E4920010 */  swc1       $f18, 0x10($a0)
  .L0000A108:
    /* DDAB74 0000A108 3C0E0001 */  lui        $t6, %hi(func_000087A4 + 0x4C)
    /* DDAB78 0000A10C 8DCE87F0 */  lw         $t6, %lo(func_000087A4 + 0x4C)($t6)
    /* DDAB7C 0000A110 27AF009C */  addiu      $t7, $sp, 0x9C
    /* DDAB80 0000A114 2401FDA0 */  addiu      $at, $zero, -0x260
    /* DDAB84 0000A118 AFAE009C */  sw         $t6, 0x9C($sp)
    /* DDAB88 0000A11C 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDAB8C 0000A120 26040260 */  addiu      $a0, $s0, 0x260
    /* DDAB90 0000A124 16010005 */  bne        $s0, $at, .L0000A13C
    /* DDAB94 0000A128 AE390000 */   sw        $t9, 0x0($s1)
    /* DDAB98 0000A12C 0C000000 */  jal        func_00000000
    /* DDAB9C 0000A130 24040018 */   addiu     $a0, $zero, 0x18
    /* DDABA0 0000A134 1040000E */  beqz       $v0, .L0000A170
    /* DDABA4 0000A138 00402025 */   or        $a0, $v0, $zero
  .L0000A13C:
    /* DDABA8 0000A13C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDABAC 0000A140 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDABB0 0000A144 02002825 */  or         $a1, $s0, $zero
    /* DDABB4 0000A148 24070001 */  addiu      $a3, $zero, 0x1
    /* DDABB8 0000A14C 0C000000 */  jal        func_00000000
    /* DDABBC 0000A150 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDABC0 0000A154 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDABC4 0000A158 44802000 */  mtc1       $zero, $f4
    /* DDABC8 0000A15C 3C0F0001 */  lui        $t7, %hi(D_00008018)
    /* DDABCC 0000A160 25EF8018 */  addiu      $t7, $t7, %lo(D_00008018)
    /* DDABD0 0000A164 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDABD4 0000A168 AC800014 */  sw         $zero, 0x14($a0)
    /* DDABD8 0000A16C E4840010 */  swc1       $f4, 0x10($a0)
  .L0000A170:
    /* DDABDC 0000A170 3C180001 */  lui        $t8, %hi(func_000087A4 + 0x50)
    /* DDABE0 0000A174 8F1887F4 */  lw         $t8, %lo(func_000087A4 + 0x50)($t8)
    /* DDABE4 0000A178 27B90098 */  addiu      $t9, $sp, 0x98
    /* DDABE8 0000A17C 2401FD88 */  addiu      $at, $zero, -0x278
    /* DDABEC 0000A180 AFB80098 */  sw         $t8, 0x98($sp)
    /* DDABF0 0000A184 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDABF4 0000A188 26040278 */  addiu      $a0, $s0, 0x278
    /* DDABF8 0000A18C 16010005 */  bne        $s0, $at, .L0000A1A4
    /* DDABFC 0000A190 AE2E0000 */   sw        $t6, 0x0($s1)
    /* DDAC00 0000A194 0C000000 */  jal        func_00000000
    /* DDAC04 0000A198 24040018 */   addiu     $a0, $zero, 0x18
    /* DDAC08 0000A19C 1040000E */  beqz       $v0, .L0000A1D8
    /* DDAC0C 0000A1A0 00402025 */   or        $a0, $v0, $zero
  .L0000A1A4:
    /* DDAC10 0000A1A4 8E260000 */  lw         $a2, 0x0($s1)
    /* DDAC14 0000A1A8 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAC18 0000A1AC 02002825 */  or         $a1, $s0, $zero
    /* DDAC1C 0000A1B0 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAC20 0000A1B4 0C000000 */  jal        func_00000000
    /* DDAC24 0000A1B8 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAC28 0000A1BC 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAC2C 0000A1C0 3C190001 */  lui        $t9, %hi(D_00008060)
    /* DDAC30 0000A1C4 27398060 */  addiu      $t9, $t9, %lo(D_00008060)
    /* DDAC34 0000A1C8 240D000A */  addiu      $t5, $zero, 0xA
    /* DDAC38 0000A1CC AC8D0010 */  sw         $t5, 0x10($a0)
    /* DDAC3C 0000A1D0 AC99000C */  sw         $t9, 0xC($a0)
    /* DDAC40 0000A1D4 AC800014 */  sw         $zero, 0x14($a0)
  .L0000A1D8:
    /* DDAC44 0000A1D8 3C0E0001 */  lui        $t6, %hi(func_000087A4 + 0x54)
    /* DDAC48 0000A1DC 8DCE87F8 */  lw         $t6, %lo(func_000087A4 + 0x54)($t6)
    /* DDAC4C 0000A1E0 27AF0094 */  addiu      $t7, $sp, 0x94
    /* DDAC50 0000A1E4 2401FD70 */  addiu      $at, $zero, -0x290
    /* DDAC54 0000A1E8 AFAE0094 */  sw         $t6, 0x94($sp)
    /* DDAC58 0000A1EC 8DF90000 */  lw         $t9, 0x0($t7)
    /* DDAC5C 0000A1F0 26040290 */  addiu      $a0, $s0, 0x290
    /* DDAC60 0000A1F4 16010005 */  bne        $s0, $at, .L0000A20C
    /* DDAC64 0000A1F8 AE390000 */   sw        $t9, 0x0($s1)
    /* DDAC68 0000A1FC 0C000000 */  jal        func_00000000
    /* DDAC6C 0000A200 24040018 */   addiu     $a0, $zero, 0x18
    /* DDAC70 0000A204 1040000E */  beqz       $v0, .L0000A240
    /* DDAC74 0000A208 00402025 */   or        $a0, $v0, $zero
  .L0000A20C:
    /* DDAC78 0000A20C 8E260000 */  lw         $a2, 0x0($s1)
    /* DDAC7C 0000A210 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDAC80 0000A214 02002825 */  or         $a1, $s0, $zero
    /* DDAC84 0000A218 24070001 */  addiu      $a3, $zero, 0x1
    /* DDAC88 0000A21C 0C000000 */  jal        func_00000000
    /* DDAC8C 0000A220 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDAC90 0000A224 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDAC94 0000A228 3C0F0001 */  lui        $t7, %hi(D_00008060)
    /* DDAC98 0000A22C 25EF8060 */  addiu      $t7, $t7, %lo(D_00008060)
    /* DDAC9C 0000A230 2418000F */  addiu      $t8, $zero, 0xF
    /* DDACA0 0000A234 AC980010 */  sw         $t8, 0x10($a0)
    /* DDACA4 0000A238 AC8F000C */  sw         $t7, 0xC($a0)
    /* DDACA8 0000A23C AC800014 */  sw         $zero, 0x14($a0)
  .L0000A240:
    /* DDACAC 0000A240 3C190001 */  lui        $t9, %hi(func_000087A4 + 0x58)
    /* DDACB0 0000A244 8F3987FC */  lw         $t9, %lo(func_000087A4 + 0x58)($t9)
    /* DDACB4 0000A248 27AD0090 */  addiu      $t5, $sp, 0x90
    /* DDACB8 0000A24C 2401FD58 */  addiu      $at, $zero, -0x2A8
    /* DDACBC 0000A250 AFB90090 */  sw         $t9, 0x90($sp)
    /* DDACC0 0000A254 8DAF0000 */  lw         $t7, 0x0($t5)
    /* DDACC4 0000A258 260402A8 */  addiu      $a0, $s0, 0x2A8
    /* DDACC8 0000A25C 16010005 */  bne        $s0, $at, .L0000A274
    /* DDACCC 0000A260 AE2F0000 */   sw        $t7, 0x0($s1)
    /* DDACD0 0000A264 0C000000 */  jal        func_00000000
    /* DDACD4 0000A268 24040018 */   addiu     $a0, $zero, 0x18
    /* DDACD8 0000A26C 1040000F */  beqz       $v0, .L0000A2AC
    /* DDACDC 0000A270 00402025 */   or        $a0, $v0, $zero
  .L0000A274:
    /* DDACE0 0000A274 8E260000 */  lw         $a2, 0x0($s1)
    /* DDACE4 0000A278 AFA40080 */  sw         $a0, 0x80($sp)
    /* DDACE8 0000A27C 02002825 */  or         $a1, $s0, $zero
    /* DDACEC 0000A280 24070001 */  addiu      $a3, $zero, 0x1
    /* DDACF0 0000A284 0C000000 */  jal        func_00000000
    /* DDACF4 0000A288 AFA60008 */   sw        $a2, 0x8($sp)
    /* DDACF8 0000A28C 8FA40080 */  lw         $a0, 0x80($sp)
    /* DDACFC 0000A290 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDAD00 0000A294 44813000 */  mtc1       $at, $f6
    /* DDAD04 0000A298 3C0D0001 */  lui        $t5, %hi(D_00008018)
    /* DDAD08 0000A29C 25AD8018 */  addiu      $t5, $t5, %lo(D_00008018)
    /* DDAD0C 0000A2A0 AC8D000C */  sw         $t5, 0xC($a0)
    /* DDAD10 0000A2A4 AC800014 */  sw         $zero, 0x14($a0)
    /* DDAD14 0000A2A8 E4860010 */  swc1       $f6, 0x10($a0)
  .L0000A2AC:
    /* DDAD18 0000A2AC 26500808 */  addiu      $s0, $s2, 0x808
    /* DDAD1C 0000A2B0 2401F7F8 */  addiu      $at, $zero, -0x808
    /* DDAD20 0000A2B4 16410005 */  bne        $s2, $at, .L0000A2CC
    /* DDAD24 0000A2B8 AFB00040 */   sw        $s0, 0x40($sp)
    /* DDAD28 0000A2BC 0C000000 */  jal        func_00000000
    /* DDAD2C 0000A2C0 2404000C */   addiu     $a0, $zero, 0xC
    /* DDAD30 0000A2C4 10400002 */  beqz       $v0, .L0000A2D0
    /* DDAD34 0000A2C8 00408025 */   or        $s0, $v0, $zero
  .L0000A2CC:
    /* DDAD38 0000A2CC AE000000 */  sw         $zero, 0x0($s0)
  .L0000A2D0:
    /* DDAD3C 0000A2D0 26510878 */  addiu      $s1, $s2, 0x878
    /* DDAD40 0000A2D4 2401F788 */  addiu      $at, $zero, -0x878
    /* DDAD44 0000A2D8 16410005 */  bne        $s2, $at, .L0000A2F0
    /* DDAD48 0000A2DC 02208025 */   or        $s0, $s1, $zero
    /* DDAD4C 0000A2E0 0C000000 */  jal        func_00000000
    /* DDAD50 0000A2E4 24040040 */   addiu     $a0, $zero, 0x40
    /* DDAD54 0000A2E8 10400006 */  beqz       $v0, .L0000A304
    /* DDAD58 0000A2EC 00408025 */   or        $s0, $v0, $zero
  .L0000A2F0:
    /* DDAD5C 0000A2F0 0C000000 */  jal        func_00000000
    /* DDAD60 0000A2F4 02002025 */   or        $a0, $s0, $zero
    /* DDAD64 0000A2F8 3C0F0000 */  lui        $t7, (0x0 >> 16)
    /* DDAD68 0000A2FC 25EF0000 */  addiu      $t7, $t7, 0x0
    /* DDAD6C 0000A300 AE0F0030 */  sw         $t7, 0x30($s0)
  .L0000A304:
    /* DDAD70 0000A304 8FA7017C */  lw         $a3, 0x17C($sp)
    /* DDAD74 0000A308 8FAB0180 */  lw         $t3, 0x180($sp)
    /* DDAD78 0000A30C AE400908 */  sw         $zero, 0x908($s2)
    /* DDAD7C 0000A310 26420018 */  addiu      $v0, $s2, 0x18
    /* DDAD80 0000A314 AE470848 */  sw         $a3, 0x848($s2)
    /* DDAD84 0000A318 AE4B08C4 */  sw         $t3, 0x8C4($s2)
    /* DDAD88 0000A31C 8C580000 */  lw         $t8, 0x0($v0)
    /* DDAD8C 0000A320 2401FFFD */  addiu      $at, $zero, -0x3
    /* DDAD90 0000A324 240E0019 */  addiu      $t6, $zero, 0x19
    /* DDAD94 0000A328 0301C824 */  and        $t9, $t8, $at
    /* DDAD98 0000A32C AC590000 */  sw         $t9, 0x0($v0)
    /* DDAD9C 0000A330 24020007 */  addiu      $v0, $zero, 0x7
    /* DDADA0 0000A334 11620009 */  beq        $t3, $v0, .L0000A35C
    /* DDADA4 0000A338 AE4008DC */   sw        $zero, 0x8DC($s2)
    /* DDADA8 0000A33C 24060006 */  addiu      $a2, $zero, 0x6
    /* DDADAC 0000A340 1166000D */  beq        $t3, $a2, .L0000A378
    /* DDADB0 0000A344 8FA90198 */   lw        $t1, 0x198($sp)
    /* DDADB4 0000A348 240D0004 */  addiu      $t5, $zero, 0x4
    /* DDADB8 0000A34C A64D0900 */  sh         $t5, 0x900($s2)
    /* DDADBC 0000A350 A6420902 */  sh         $v0, 0x902($s2)
    /* DDADC0 0000A354 1000000D */  b          .L0000A38C
    /* DDADC4 0000A358 8FA90198 */   lw        $t1, 0x198($sp)
  .L0000A35C:
    /* DDADC8 0000A35C 8FA90198 */  lw         $t1, 0x198($sp)
    /* DDADCC 0000A360 240F001A */  addiu      $t7, $zero, 0x1A
    /* DDADD0 0000A364 A64F0902 */  sh         $t7, 0x902($s2)
    /* DDADD4 0000A368 A64E0900 */  sh         $t6, 0x900($s2)
    /* DDADD8 0000A36C 24060006 */  addiu      $a2, $zero, 0x6
    /* DDADDC 0000A370 10000006 */  b          .L0000A38C
    /* DDADE0 0000A374 35290001 */   ori       $t1, $t1, 0x1
  .L0000A378:
    /* DDADE4 0000A378 24180017 */  addiu      $t8, $zero, 0x17
    /* DDADE8 0000A37C 24190018 */  addiu      $t9, $zero, 0x18
    /* DDADEC 0000A380 A6590902 */  sh         $t9, 0x902($s2)
    /* DDADF0 0000A384 A6580900 */  sh         $t8, 0x900($s2)
    /* DDADF4 0000A388 35290001 */  ori        $t1, $t1, 0x1
  .L0000A38C:
    /* DDADF8 0000A38C 24010001 */  addiu      $at, $zero, 0x1
    /* DDADFC 0000A390 14E10008 */  bne        $a3, $at, .L0000A3B4
    /* DDAE00 0000A394 00005025 */   or        $t2, $zero, $zero
    /* DDAE04 0000A398 3C0C0000 */  lui        $t4, (0x0 >> 16)
    /* DDAE08 0000A39C 258C0000 */  addiu      $t4, $t4, 0x0
    /* DDAE0C 0000A3A0 8D8D0058 */  lw         $t5, 0x58($t4)
    /* DDAE10 0000A3A4 8D8E004C */  lw         $t6, 0x4C($t4)
    /* DDAE14 0000A3A8 15AE0002 */  bne        $t5, $t6, .L0000A3B4
    /* DDAE18 0000A3AC 00000000 */   nop
    /* DDAE1C 0000A3B0 240A0001 */  addiu      $t2, $zero, 0x1
  .L0000A3B4:
    /* DDAE20 0000A3B4 3C0C0000 */  lui        $t4, (0x0 >> 16)
    /* DDAE24 0000A3B8 258C0000 */  addiu      $t4, $t4, 0x0
    /* DDAE28 0000A3BC 8D8F0034 */  lw         $t7, 0x34($t4)
    /* DDAE2C 0000A3C0 8FA80194 */  lw         $t0, 0x194($sp)
    /* DDAE30 0000A3C4 24010003 */  addiu      $at, $zero, 0x3
    /* DDAE34 0000A3C8 15E10009 */  bne        $t7, $at, .L0000A3F0
    /* DDAE38 0000A3CC 310D0008 */   andi      $t5, $t0, 0x8
    /* DDAE3C 0000A3D0 9198017D */  lbu        $t8, 0x17D($t4)
    /* DDAE40 0000A3D4 8D99004C */  lw         $t9, 0x4C($t4)
    /* DDAE44 0000A3D8 24100002 */  addiu      $s0, $zero, 0x2
    /* DDAE48 0000A3DC 17190004 */  bne        $t8, $t9, .L0000A3F0
    /* DDAE4C 0000A3E0 00000000 */   nop
    /* DDAE50 0000A3E4 14F00002 */  bne        $a3, $s0, .L0000A3F0
    /* DDAE54 0000A3E8 00000000 */   nop
    /* DDAE58 0000A3EC 240A0001 */  addiu      $t2, $zero, 0x1
  .L0000A3F0:
    /* DDAE5C 0000A3F0 11620003 */  beq        $t3, $v0, .L0000A400
    /* DDAE60 0000A3F4 24100002 */   addiu     $s0, $zero, 0x2
    /* DDAE64 0000A3F8 556600AA */  bnel       $t3, $a2, .L0000A6A4
    /* DDAE68 0000A3FC 8FA80194 */   lw        $t0, 0x194($sp)
  .L0000A400:
    /* DDAE6C 0000A400 11A00002 */  beqz       $t5, .L0000A40C
    /* DDAE70 0000A404 00000000 */   nop
    /* DDAE74 0000A408 240A0001 */  addiu      $t2, $zero, 0x1
  .L0000A40C:
    /* DDAE78 0000A40C 55620052 */  bnel       $t3, $v0, .L0000A558
    /* DDAE7C 0000A410 3C01437F */   lui       $at, (0x437F0000 >> 16)
    /* DDAE80 0000A414 11400027 */  beqz       $t2, .L0000A4B4
    /* DDAE84 0000A418 3C050001 */   lui       $a1, %hi(func_00008664 + 0x28)
    /* DDAE88 0000A41C 24A5868C */  addiu      $a1, $a1, %lo(func_00008664 + 0x28)
    /* DDAE8C 0000A420 90A20000 */  lbu        $v0, 0x0($a1)
    /* DDAE90 0000A424 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDAE94 0000A428 44810000 */  mtc1       $at, $f0
    /* DDAE98 0000A42C 44824000 */  mtc1       $v0, $f8
    /* DDAE9C 0000A430 90A30001 */  lbu        $v1, 0x1($a1)
    /* DDAEA0 0000A434 90A40002 */  lbu        $a0, 0x2($a1)
    /* DDAEA4 0000A438 04410005 */  bgez       $v0, .L0000A450
    /* DDAEA8 0000A43C 468042A0 */   cvt.s.w   $f10, $f8
    /* DDAEAC 0000A440 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAEB0 0000A444 44818000 */  mtc1       $at, $f16
    /* DDAEB4 0000A448 00000000 */  nop
    /* DDAEB8 0000A44C 46105280 */  add.s      $f10, $f10, $f16
  .L0000A450:
    /* DDAEBC 0000A450 46005483 */  div.s      $f18, $f10, $f0
    /* DDAEC0 0000A454 44832000 */  mtc1       $v1, $f4
    /* DDAEC4 0000A458 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAEC8 0000A45C 468021A0 */  cvt.s.w    $f6, $f4
    /* DDAECC 0000A460 04610004 */  bgez       $v1, .L0000A474
    /* DDAED0 0000A464 E65208E0 */   swc1      $f18, 0x8E0($s2)
    /* DDAED4 0000A468 44814000 */  mtc1       $at, $f8
    /* DDAED8 0000A46C 00000000 */  nop
    /* DDAEDC 0000A470 46083180 */  add.s      $f6, $f6, $f8
  .L0000A474:
    /* DDAEE0 0000A474 46003403 */  div.s      $f16, $f6, $f0
    /* DDAEE4 0000A478 44845000 */  mtc1       $a0, $f10
    /* DDAEE8 0000A47C 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAEEC 0000A480 468054A0 */  cvt.s.w    $f18, $f10
    /* DDAEF0 0000A484 04810004 */  bgez       $a0, .L0000A498
    /* DDAEF4 0000A488 E65008E4 */   swc1      $f16, 0x8E4($s2)
    /* DDAEF8 0000A48C 44812000 */  mtc1       $at, $f4
    /* DDAEFC 0000A490 00000000 */  nop
    /* DDAF00 0000A494 46049480 */  add.s      $f18, $f18, $f4
  .L0000A498:
    /* DDAF04 0000A498 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDAF08 0000A49C 44813000 */  mtc1       $at, $f6
    /* DDAF0C 0000A4A0 46009203 */  div.s      $f8, $f18, $f0
    /* DDAF10 0000A4A4 46003403 */  div.s      $f16, $f6, $f0
    /* DDAF14 0000A4A8 E64808E8 */  swc1       $f8, 0x8E8($s2)
    /* DDAF18 0000A4AC 10000029 */  b          .L0000A554
    /* DDAF1C 0000A4B0 E65008EC */   swc1      $f16, 0x8EC($s2)
  .L0000A4B4:
    /* DDAF20 0000A4B4 3C050001 */  lui        $a1, %hi(func_00008664 + 0x24)
    /* DDAF24 0000A4B8 24A58688 */  addiu      $a1, $a1, %lo(func_00008664 + 0x24)
    /* DDAF28 0000A4BC 90A20000 */  lbu        $v0, 0x0($a1)
    /* DDAF2C 0000A4C0 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDAF30 0000A4C4 44810000 */  mtc1       $at, $f0
    /* DDAF34 0000A4C8 44825000 */  mtc1       $v0, $f10
    /* DDAF38 0000A4CC 90A30001 */  lbu        $v1, 0x1($a1)
    /* DDAF3C 0000A4D0 90A40002 */  lbu        $a0, 0x2($a1)
    /* DDAF40 0000A4D4 04410005 */  bgez       $v0, .L0000A4EC
    /* DDAF44 0000A4D8 46805120 */   cvt.s.w   $f4, $f10
    /* DDAF48 0000A4DC 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAF4C 0000A4E0 44819000 */  mtc1       $at, $f18
    /* DDAF50 0000A4E4 00000000 */  nop
    /* DDAF54 0000A4E8 46122100 */  add.s      $f4, $f4, $f18
  .L0000A4EC:
    /* DDAF58 0000A4EC 46002203 */  div.s      $f8, $f4, $f0
    /* DDAF5C 0000A4F0 44833000 */  mtc1       $v1, $f6
    /* DDAF60 0000A4F4 00000000 */  nop
    /* DDAF64 0000A4F8 46803420 */  cvt.s.w    $f16, $f6
    /* DDAF68 0000A4FC 04610005 */  bgez       $v1, .L0000A514
    /* DDAF6C 0000A500 E64808E0 */   swc1      $f8, 0x8E0($s2)
    /* DDAF70 0000A504 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAF74 0000A508 44815000 */  mtc1       $at, $f10
    /* DDAF78 0000A50C 00000000 */  nop
    /* DDAF7C 0000A510 460A8400 */  add.s      $f16, $f16, $f10
  .L0000A514:
    /* DDAF80 0000A514 46008483 */  div.s      $f18, $f16, $f0
    /* DDAF84 0000A518 44842000 */  mtc1       $a0, $f4
    /* DDAF88 0000A51C 00000000 */  nop
    /* DDAF8C 0000A520 46802220 */  cvt.s.w    $f8, $f4
    /* DDAF90 0000A524 04810005 */  bgez       $a0, .L0000A53C
    /* DDAF94 0000A528 E65208E4 */   swc1      $f18, 0x8E4($s2)
    /* DDAF98 0000A52C 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAF9C 0000A530 44813000 */  mtc1       $at, $f6
    /* DDAFA0 0000A534 00000000 */  nop
    /* DDAFA4 0000A538 46064200 */  add.s      $f8, $f8, $f6
  .L0000A53C:
    /* DDAFA8 0000A53C 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDAFAC 0000A540 44818000 */  mtc1       $at, $f16
    /* DDAFB0 0000A544 46004283 */  div.s      $f10, $f8, $f0
    /* DDAFB4 0000A548 46008483 */  div.s      $f18, $f16, $f0
    /* DDAFB8 0000A54C E64A08E8 */  swc1       $f10, 0x8E8($s2)
    /* DDAFBC 0000A550 E65208EC */  swc1       $f18, 0x8EC($s2)
  .L0000A554:
    /* DDAFC0 0000A554 3C01437F */  lui        $at, (0x437F0000 >> 16)
  .L0000A558:
    /* DDAFC4 0000A558 44810000 */  mtc1       $at, $f0
    /* DDAFC8 0000A55C 5566004E */  bnel       $t3, $a2, .L0000A698
    /* DDAFCC 0000A560 2401FFFB */   addiu     $at, $zero, -0x5
    /* DDAFD0 0000A564 11400025 */  beqz       $t2, .L0000A5FC
    /* DDAFD4 0000A568 3C050001 */   lui       $a1, %hi(func_00008664 + 0x30)
    /* DDAFD8 0000A56C 24A58694 */  addiu      $a1, $a1, %lo(func_00008664 + 0x30)
    /* DDAFDC 0000A570 90A20000 */  lbu        $v0, 0x0($a1)
    /* DDAFE0 0000A574 90A30001 */  lbu        $v1, 0x1($a1)
    /* DDAFE4 0000A578 90A40002 */  lbu        $a0, 0x2($a1)
    /* DDAFE8 0000A57C 44822000 */  mtc1       $v0, $f4
    /* DDAFEC 0000A580 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDAFF0 0000A584 04410004 */  bgez       $v0, .L0000A598
    /* DDAFF4 0000A588 468021A0 */   cvt.s.w   $f6, $f4
    /* DDAFF8 0000A58C 44814000 */  mtc1       $at, $f8
    /* DDAFFC 0000A590 00000000 */  nop
    /* DDB000 0000A594 46083180 */  add.s      $f6, $f6, $f8
  .L0000A598:
    /* DDB004 0000A598 46003283 */  div.s      $f10, $f6, $f0
    /* DDB008 0000A59C 44838000 */  mtc1       $v1, $f16
    /* DDB00C 0000A5A0 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDB010 0000A5A4 468084A0 */  cvt.s.w    $f18, $f16
    /* DDB014 0000A5A8 04610004 */  bgez       $v1, .L0000A5BC
    /* DDB018 0000A5AC E64A08E0 */   swc1      $f10, 0x8E0($s2)
    /* DDB01C 0000A5B0 44812000 */  mtc1       $at, $f4
    /* DDB020 0000A5B4 00000000 */  nop
    /* DDB024 0000A5B8 46049480 */  add.s      $f18, $f18, $f4
  .L0000A5BC:
    /* DDB028 0000A5BC 46009203 */  div.s      $f8, $f18, $f0
    /* DDB02C 0000A5C0 44843000 */  mtc1       $a0, $f6
    /* DDB030 0000A5C4 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDB034 0000A5C8 468032A0 */  cvt.s.w    $f10, $f6
    /* DDB038 0000A5CC 04810004 */  bgez       $a0, .L0000A5E0
    /* DDB03C 0000A5D0 E64808E4 */   swc1      $f8, 0x8E4($s2)
    /* DDB040 0000A5D4 44818000 */  mtc1       $at, $f16
    /* DDB044 0000A5D8 00000000 */  nop
    /* DDB048 0000A5DC 46105280 */  add.s      $f10, $f10, $f16
  .L0000A5E0:
    /* DDB04C 0000A5E0 3C014324 */  lui        $at, (0x43240000 >> 16)
    /* DDB050 0000A5E4 44819000 */  mtc1       $at, $f18
    /* DDB054 0000A5E8 46005103 */  div.s      $f4, $f10, $f0
    /* DDB058 0000A5EC 46009203 */  div.s      $f8, $f18, $f0
    /* DDB05C 0000A5F0 E64408E8 */  swc1       $f4, 0x8E8($s2)
    /* DDB060 0000A5F4 10000027 */  b          .L0000A694
    /* DDB064 0000A5F8 E64808EC */   swc1      $f8, 0x8EC($s2)
  .L0000A5FC:
    /* DDB068 0000A5FC 3C050001 */  lui        $a1, %hi(func_00008664 + 0x2C)
    /* DDB06C 0000A600 24A58690 */  addiu      $a1, $a1, %lo(func_00008664 + 0x2C)
    /* DDB070 0000A604 90A20000 */  lbu        $v0, 0x0($a1)
    /* DDB074 0000A608 90A30001 */  lbu        $v1, 0x1($a1)
    /* DDB078 0000A60C 90A40002 */  lbu        $a0, 0x2($a1)
    /* DDB07C 0000A610 44823000 */  mtc1       $v0, $f6
    /* DDB080 0000A614 04410005 */  bgez       $v0, .L0000A62C
    /* DDB084 0000A618 46803420 */   cvt.s.w   $f16, $f6
    /* DDB088 0000A61C 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDB08C 0000A620 44815000 */  mtc1       $at, $f10
    /* DDB090 0000A624 00000000 */  nop
    /* DDB094 0000A628 460A8400 */  add.s      $f16, $f16, $f10
  .L0000A62C:
    /* DDB098 0000A62C 46008103 */  div.s      $f4, $f16, $f0
    /* DDB09C 0000A630 44839000 */  mtc1       $v1, $f18
    /* DDB0A0 0000A634 00000000 */  nop
    /* DDB0A4 0000A638 46809220 */  cvt.s.w    $f8, $f18
    /* DDB0A8 0000A63C 04610005 */  bgez       $v1, .L0000A654
    /* DDB0AC 0000A640 E64408E0 */   swc1      $f4, 0x8E0($s2)
    /* DDB0B0 0000A644 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDB0B4 0000A648 44813000 */  mtc1       $at, $f6
    /* DDB0B8 0000A64C 00000000 */  nop
    /* DDB0BC 0000A650 46064200 */  add.s      $f8, $f8, $f6
  .L0000A654:
    /* DDB0C0 0000A654 46004283 */  div.s      $f10, $f8, $f0
    /* DDB0C4 0000A658 44848000 */  mtc1       $a0, $f16
    /* DDB0C8 0000A65C 00000000 */  nop
    /* DDB0CC 0000A660 46808120 */  cvt.s.w    $f4, $f16
    /* DDB0D0 0000A664 04810005 */  bgez       $a0, .L0000A67C
    /* DDB0D4 0000A668 E64A08E4 */   swc1      $f10, 0x8E4($s2)
    /* DDB0D8 0000A66C 3C014F80 */  lui        $at, (0x4F800000 >> 16)
    /* DDB0DC 0000A670 44819000 */  mtc1       $at, $f18
    /* DDB0E0 0000A674 00000000 */  nop
    /* DDB0E4 0000A678 46122100 */  add.s      $f4, $f4, $f18
  .L0000A67C:
    /* DDB0E8 0000A67C 3C014324 */  lui        $at, (0x43240000 >> 16)
    /* DDB0EC 0000A680 44814000 */  mtc1       $at, $f8
    /* DDB0F0 0000A684 46002183 */  div.s      $f6, $f4, $f0
    /* DDB0F4 0000A688 46004283 */  div.s      $f10, $f8, $f0
    /* DDB0F8 0000A68C E64608E8 */  swc1       $f6, 0x8E8($s2)
    /* DDB0FC 0000A690 E64A08EC */  swc1       $f10, 0x8EC($s2)
  .L0000A694:
    /* DDB100 0000A694 2401FFFB */  addiu      $at, $zero, -0x5
  .L0000A698:
    /* DDB104 0000A698 10000020 */  b          .L0000A71C
    /* DDB108 0000A69C 01214824 */   and       $t1, $t1, $at
    /* DDB10C 0000A6A0 8FA80194 */  lw         $t0, 0x194($sp)
  .L0000A6A4:
    /* DDB110 0000A6A4 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDB114 0000A6A8 310E0008 */  andi       $t6, $t0, 0x8
    /* DDB118 0000A6AC 51C0000E */  beql       $t6, $zero, .L0000A6E8
    /* DDB11C 0000A6B0 44810000 */   mtc1      $at, $f0
    /* DDB120 0000A6B4 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* DDB124 0000A6B8 44810000 */  mtc1       $at, $f0
    /* DDB128 0000A6BC 44818000 */  mtc1       $at, $f16
    /* DDB12C 0000A6C0 3C0142EA */  lui        $at, (0x42EA0000 >> 16)
    /* DDB130 0000A6C4 44819000 */  mtc1       $at, $f18
    /* DDB134 0000A6C8 46008083 */  div.s      $f2, $f16, $f0
    /* DDB138 0000A6CC 46009103 */  div.s      $f4, $f18, $f0
    /* DDB13C 0000A6D0 E64208E0 */  swc1       $f2, 0x8E0($s2)
    /* DDB140 0000A6D4 E64208E4 */  swc1       $f2, 0x8E4($s2)
    /* DDB144 0000A6D8 E64208E8 */  swc1       $f2, 0x8E8($s2)
    /* DDB148 0000A6DC 1000000F */  b          .L0000A71C
    /* DDB14C 0000A6E0 E64408EC */   swc1      $f4, 0x8EC($s2)
    /* DDB150 0000A6E4 44810000 */  mtc1       $at, $f0
  .L0000A6E8:
    /* DDB154 0000A6E8 44813000 */  mtc1       $at, $f6
    /* DDB158 0000A6EC 3C01428C */  lui        $at, (0x428C0000 >> 16)
    /* DDB15C 0000A6F0 44814000 */  mtc1       $at, $f8
    /* DDB160 0000A6F4 46003083 */  div.s      $f2, $f6, $f0
    /* DDB164 0000A6F8 46004283 */  div.s      $f10, $f8, $f0
    /* DDB168 0000A6FC E64208E0 */  swc1       $f2, 0x8E0($s2)
    /* DDB16C 0000A700 E64208E4 */  swc1       $f2, 0x8E4($s2)
    /* DDB170 0000A704 E64208E8 */  swc1       $f2, 0x8E8($s2)
    /* DDB174 0000A708 E64A08EC */  swc1       $f10, 0x8EC($s2)
    /* DDB178 0000A70C 8D8F0034 */  lw         $t7, 0x34($t4)
    /* DDB17C 0000A710 520F0003 */  beql       $s0, $t7, .L0000A720
    /* DDB180 0000A714 35024800 */   ori       $v0, $t0, 0x4800
    /* DDB184 0000A718 35081000 */  ori        $t0, $t0, 0x1000
  .L0000A71C:
    /* DDB188 0000A71C 35024800 */  ori        $v0, $t0, 0x4800
  .L0000A720:
    /* DDB18C 0000A720 3C014348 */  lui        $at, (0x43480000 >> 16)
    /* DDB190 0000A724 44818000 */  mtc1       $at, $f16
    /* DDB194 0000A728 AE4208BC */  sw         $v0, 0x8BC($s2)
    /* DDB198 0000A72C AE420A58 */  sw         $v0, 0xA58($s2)
    /* DDB19C 0000A730 AE4908B8 */  sw         $t1, 0x8B8($s2)
    /* DDB1A0 0000A734 AFAA0174 */  sw         $t2, 0x174($sp)
    /* DDB1A4 0000A738 02202025 */  or         $a0, $s1, $zero
    /* DDB1A8 0000A73C 02402825 */  or         $a1, $s2, $zero
    /* DDB1AC 0000A740 2406006D */  addiu      $a2, $zero, 0x6D
    /* DDB1B0 0000A744 3C074316 */  lui        $a3, (0x43160000 >> 16)
    /* DDB1B4 0000A748 0C000000 */  jal        func_00000000
    /* DDB1B8 0000A74C E7B00010 */   swc1      $f16, 0x10($sp)
    /* DDB1BC 0000A750 8E580A58 */  lw         $t8, 0xA58($s2)
    /* DDB1C0 0000A754 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDB1C4 0000A758 02202825 */  or         $a1, $s1, $zero
    /* DDB1C8 0000A75C 33190008 */  andi       $t9, $t8, 0x8
    /* DDB1CC 0000A760 13200004 */  beqz       $t9, .L0000A774
    /* DDB1D0 0000A764 240D0004 */   addiu     $t5, $zero, 0x4
    /* DDB1D4 0000A768 A64D088C */  sh         $t5, 0x88C($s2)
    /* DDB1D8 0000A76C 10000005 */  b          .L0000A784
    /* DDB1DC 0000A770 A650088E */   sh        $s0, 0x88E($s2)
  .L0000A774:
    /* DDB1E0 0000A774 240E0001 */  addiu      $t6, $zero, 0x1
    /* DDB1E4 0000A778 240F0005 */  addiu      $t7, $zero, 0x5
    /* DDB1E8 0000A77C A64F088C */  sh         $t7, 0x88C($s2)
    /* DDB1EC 0000A780 A64E088E */  sh         $t6, 0x88E($s2)
  .L0000A784:
    /* DDB1F0 0000A784 0C000000 */  jal        func_00000000
    /* DDB1F4 0000A788 8C840000 */   lw        $a0, 0x0($a0)
    /* DDB1F8 0000A78C C7A0018C */  lwc1       $f0, 0x18C($sp)
    /* DDB1FC 0000A790 C7A20190 */  lwc1       $f2, 0x190($sp)
    /* DDB200 0000A794 44809000 */  mtc1       $zero, $f18
    /* DDB204 0000A798 3C040000 */  lui        $a0, (0x0 >> 16)
    /* DDB208 0000A79C 44070000 */  mfc1       $a3, $f0
    /* DDB20C 0000A7A0 8C840000 */  lw         $a0, 0x0($a0)
    /* DDB210 0000A7A4 24050001 */  addiu      $a1, $zero, 0x1
    /* DDB214 0000A7A8 27A6016C */  addiu      $a2, $sp, 0x16C
    /* DDB218 0000A7AC E7A00168 */  swc1       $f0, 0x168($sp)
    /* DDB21C 0000A7B0 E7A20010 */  swc1       $f2, 0x10($sp)
    /* DDB220 0000A7B4 E7A20170 */  swc1       $f2, 0x170($sp)
    /* DDB224 0000A7B8 0C000000 */  jal        func_00000000
    /* DDB228 0000A7BC E7B2016C */   swc1      $f18, 0x16C($sp)
    /* DDB22C 0000A7C0 3C010000 */  lui        $at, %hi(D_000008B0)
    /* DDB230 0000A7C4 C42608B0 */  lwc1       $f6, %lo(D_000008B0)($at)
    /* DDB234 0000A7C8 C7A4016C */  lwc1       $f4, 0x16C($sp)
    /* DDB238 0000A7CC 27B90168 */  addiu      $t9, $sp, 0x168
    /* DDB23C 0000A7D0 8FA60180 */  lw         $a2, 0x180($sp)
    /* DDB240 0000A7D4 46062200 */  add.s      $f8, $f4, $f6
    /* DDB244 0000A7D8 27B8005C */  addiu      $t8, $sp, 0x5C
    /* DDB248 0000A7DC 240F0001 */  addiu      $t7, $zero, 0x1
    /* DDB24C 0000A7E0 E7A8016C */  swc1       $f8, 0x16C($sp)
    /* DDB250 0000A7E4 8F2E0000 */  lw         $t6, 0x0($t9)
    /* DDB254 0000A7E8 AF0E0000 */  sw         $t6, 0x0($t8)
    /* DDB258 0000A7EC 8F2D0004 */  lw         $t5, 0x4($t9)
    /* DDB25C 0000A7F0 AF0D0004 */  sw         $t5, 0x4($t8)
    /* DDB260 0000A7F4 8F2E0008 */  lw         $t6, 0x8($t9)
    /* DDB264 0000A7F8 24190001 */  addiu      $t9, $zero, 0x1
    /* DDB268 0000A7FC AF0E0008 */  sw         $t6, 0x8($t8)
    /* DDB26C 0000A800 C7AA005C */  lwc1       $f10, 0x5C($sp)
    /* DDB270 0000A804 00CFC004 */  sllv       $t8, $t7, $a2
    /* DDB274 0000A808 E64A03A4 */  swc1       $f10, 0x3A4($s2)
    /* DDB278 0000A80C C7B00060 */  lwc1       $f16, 0x60($sp)
    /* DDB27C 0000A810 E65003A8 */  swc1       $f16, 0x3A8($s2)
    /* DDB280 0000A814 C7B20064 */  lwc1       $f18, 0x64($sp)
    /* DDB284 0000A818 AE5808C0 */  sw         $t8, 0x8C0($s2)
    /* DDB288 0000A81C AE59038C */  sw         $t9, 0x38C($s2)
    /* DDB28C 0000A820 AE400870 */  sw         $zero, 0x870($s2)
    /* DDB290 0000A824 AE400868 */  sw         $zero, 0x868($s2)
    /* DDB294 0000A828 AE40086C */  sw         $zero, 0x86C($s2)
    /* DDB298 0000A82C E65203AC */  swc1       $f18, 0x3AC($s2)
    /* DDB29C 0000A830 8FA5017C */  lw         $a1, 0x17C($sp)
    /* DDB2A0 0000A834 0C000000 */  jal        func_00000000
    /* DDB2A4 0000A838 8FA40040 */   lw        $a0, 0x40($sp)
    /* DDB2A8 0000A83C 8E4D0A58 */  lw         $t5, 0xA58($s2)
    /* DDB2AC 0000A840 31AE0003 */  andi       $t6, $t5, 0x3
    /* DDB2B0 0000A844 11C000C4 */  beqz       $t6, .L0000AB58
    /* DDB2B4 0000A848 3C040001 */   lui       $a0, %hi(func_000087A4 + 0x5C)
    /* DDB2B8 0000A84C 24848800 */  addiu      $a0, $a0, %lo(func_000087A4 + 0x5C)
    /* DDB2BC 0000A850 0C000000 */  jal        func_00000000
    /* DDB2C0 0000A854 00002825 */   or        $a1, $zero, $zero
    /* DDB2C4 0000A858 3C050001 */  lui        $a1, %hi(func_000087A4 + 0x64)
    /* DDB2C8 0000A85C 24A58808 */  addiu      $a1, $a1, %lo(func_000087A4 + 0x64)
    /* DDB2CC 0000A860 0C000000 */  jal        func_00000000
    /* DDB2D0 0000A864 00002025 */   or        $a0, $zero, $zero
    /* DDB2D4 0000A868 3C050001 */  lui        $a1, %hi(D_00008814)
    /* DDB2D8 0000A86C AE42086C */  sw         $v0, 0x86C($s2)
    /* DDB2DC 0000A870 24A58814 */  addiu      $a1, $a1, %lo(D_00008814)
    /* DDB2E0 0000A874 0C000000 */  jal        func_00000000
    /* DDB2E4 0000A878 00002025 */   or        $a0, $zero, $zero
    /* DDB2E8 0000A87C 8E50086C */  lw         $s0, 0x86C($s2)
    /* DDB2EC 0000A880 AE420868 */  sw         $v0, 0x868($s2)
    /* DDB2F0 0000A884 2401FFF7 */  addiu      $at, $zero, -0x9
    /* DDB2F4 0000A888 8E0F0018 */  lw         $t7, 0x18($s0)
    /* DDB2F8 0000A88C 3C190000 */  lui        $t9, %hi(func_000000F0 + 0x44)
    /* DDB2FC 0000A890 26100018 */  addiu      $s0, $s0, 0x18
    /* DDB300 0000A894 01E1C024 */  and        $t8, $t7, $at
    /* DDB304 0000A898 AE180000 */  sw         $t8, 0x0($s0)
    /* DDB308 0000A89C 8F390134 */  lw         $t9, %lo(func_000000F0 + 0x44)($t9)
    /* DDB30C 0000A8A0 8E51086C */  lw         $s1, 0x86C($s2)
    /* DDB310 0000A8A4 8F300088 */  lw         $s0, 0x88($t9)
    /* DDB314 0000A8A8 02202825 */  or         $a1, $s1, $zero
    /* DDB318 0000A8AC 0C000000 */  jal        func_00000000
    /* DDB31C 0000A8B0 26040010 */   addiu     $a0, $s0, 0x10
    /* DDB320 0000A8B4 8E2D0014 */  lw         $t5, 0x14($s1)
    /* DDB324 0000A8B8 3C050001 */  lui        $a1, %hi(D_00008820)
    /* DDB328 0000A8BC 24A58820 */  addiu      $a1, $a1, %lo(D_00008820)
    /* DDB32C 0000A8C0 11A00003 */  beqz       $t5, .L0000A8D0
    /* DDB330 0000A8C4 00002025 */   or        $a0, $zero, $zero
    /* DDB334 0000A8C8 240E0001 */  addiu      $t6, $zero, 0x1
    /* DDB338 0000A8CC AE2E0004 */  sw         $t6, 0x4($s1)
  .L0000A8D0:
    /* DDB33C 0000A8D0 0C000000 */  jal        func_00000000
    /* DDB340 0000A8D4 AE300014 */   sw        $s0, 0x14($s1)
    /* DDB344 0000A8D8 AE420868 */  sw         $v0, 0x868($s2)
    /* DDB348 0000A8DC 24430018 */  addiu      $v1, $v0, 0x18
    /* DDB34C 0000A8E0 8C6F0000 */  lw         $t7, 0x0($v1)
    /* DDB350 0000A8E4 2401FFF7 */  addiu      $at, $zero, -0x9
    /* DDB354 0000A8E8 3C190000 */  lui        $t9, %hi(func_000000F0 + 0x44)
    /* DDB358 0000A8EC 01E1C024 */  and        $t8, $t7, $at
    /* DDB35C 0000A8F0 AC780000 */  sw         $t8, 0x0($v1)
    /* DDB360 0000A8F4 8F390134 */  lw         $t9, %lo(func_000000F0 + 0x44)($t9)
    /* DDB364 0000A8F8 8E510868 */  lw         $s1, 0x868($s2)
    /* DDB368 0000A8FC 8F300084 */  lw         $s0, 0x84($t9)
    /* DDB36C 0000A900 02202825 */  or         $a1, $s1, $zero
    /* DDB370 0000A904 0C000000 */  jal        func_00000000
    /* DDB374 0000A908 26040010 */   addiu     $a0, $s0, 0x10
    /* DDB378 0000A90C 8E2D0014 */  lw         $t5, 0x14($s1)
    /* DDB37C 0000A910 24040001 */  addiu      $a0, $zero, 0x1
    /* DDB380 0000A914 11A00002 */  beqz       $t5, .L0000A920
    /* DDB384 0000A918 240E0001 */   addiu     $t6, $zero, 0x1
    /* DDB388 0000A91C AE2E0004 */  sw         $t6, 0x4($s1)
  .L0000A920:
    /* DDB38C 0000A920 0C000000 */  jal        func_00000000
    /* DDB390 0000A924 AE300014 */   sw        $s0, 0x14($s1)
    /* DDB394 0000A928 0C000000 */  jal        func_00000000
    /* DDB398 0000A92C 2404023C */   addiu     $a0, $zero, 0x23C
    /* DDB39C 0000A930 10400011 */  beqz       $v0, .L0000A978
    /* DDB3A0 0000A934 00408025 */   or        $s0, $v0, $zero
    /* DDB3A4 0000A938 14400005 */  bnez       $v0, .L0000A950
    /* DDB3A8 0000A93C 00408825 */   or        $s1, $v0, $zero
    /* DDB3AC 0000A940 0C000000 */  jal        func_00000000
    /* DDB3B0 0000A944 24040174 */   addiu     $a0, $zero, 0x174
    /* DDB3B4 0000A948 10400008 */  beqz       $v0, .L0000A96C
    /* DDB3B8 0000A94C 00408825 */   or        $s1, $v0, $zero
  .L0000A950:
    /* DDB3BC 0000A950 3C050001 */  lui        $a1, %hi(D_0000882C)
    /* DDB3C0 0000A954 24A5882C */  addiu      $a1, $a1, %lo(D_0000882C)
    /* DDB3C4 0000A958 0C000000 */  jal        func_00000000
    /* DDB3C8 0000A95C 02202025 */   or        $a0, $s1, $zero
    /* DDB3CC 0000A960 3C0F0000 */  lui        $t7, %hi(bu_90cc_vt545)
    /* DDB3D0 0000A964 25EF0000 */  addiu      $t7, $t7, %lo(bu_90cc_vt545)
    /* DDB3D4 0000A968 AE2F0028 */  sw         $t7, 0x28($s1)
  .L0000A96C:
    /* DDB3D8 0000A96C 3C180000 */  lui        $t8, %hi(bu_90cc_vt546)
    /* DDB3DC 0000A970 27180000 */  addiu      $t8, $t8, %lo(bu_90cc_vt546)
    /* DDB3E0 0000A974 AE180028 */  sw         $t8, 0x28($s0)
  .L0000A978:
    /* DDB3E4 0000A978 AFB00164 */  sw         $s0, 0x164($sp)
    /* DDB3E8 0000A97C 8E510868 */  lw         $s1, 0x868($s2)
    /* DDB3EC 0000A980 02002825 */  or         $a1, $s0, $zero
    /* DDB3F0 0000A984 0C000000 */  jal        func_00000000
    /* DDB3F4 0000A988 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB3F8 0000A98C 8E190014 */  lw         $t9, 0x14($s0)
    /* DDB3FC 0000A990 13200002 */  beqz       $t9, .L0000A99C
    /* DDB400 0000A994 240D0001 */   addiu     $t5, $zero, 0x1
    /* DDB404 0000A998 AE0D0004 */  sw         $t5, 0x4($s0)
  .L0000A99C:
    /* DDB408 0000A99C AE110014 */  sw         $s1, 0x14($s0)
    /* DDB40C 0000A9A0 8E4E0A58 */  lw         $t6, 0xA58($s2)
    /* DDB410 0000A9A4 31CF0001 */  andi       $t7, $t6, 0x1
    /* DDB414 0000A9A8 11E00023 */  beqz       $t7, .L0000AA38
    /* DDB418 0000A9AC 00000000 */   nop
    /* DDB41C 0000A9B0 0C000000 */  jal        func_00000000
    /* DDB420 0000A9B4 240401F4 */   addiu     $a0, $zero, 0x1F4
    /* DDB424 0000A9B8 10400013 */  beqz       $v0, .L0000AA08
    /* DDB428 0000A9BC 00408825 */   or        $s1, $v0, $zero
    /* DDB42C 0000A9C0 14400005 */  bnez       $v0, .L0000A9D8
    /* DDB430 0000A9C4 00403025 */   or        $a2, $v0, $zero
    /* DDB434 0000A9C8 0C000000 */  jal        func_00000000
    /* DDB438 0000A9CC 24040174 */   addiu     $a0, $zero, 0x174
    /* DDB43C 0000A9D0 1040000A */  beqz       $v0, .L0000A9FC
    /* DDB440 0000A9D4 00403025 */   or        $a2, $v0, $zero
  .L0000A9D8:
    /* DDB444 0000A9D8 3C050001 */  lui        $a1, %hi(D_00008834)
    /* DDB448 0000A9DC 24A58834 */  addiu      $a1, $a1, %lo(D_00008834)
    /* DDB44C 0000A9E0 00C02025 */  or         $a0, $a2, $zero
    /* DDB450 0000A9E4 0C000000 */  jal        func_00000000
    /* DDB454 0000A9E8 AFA60114 */   sw        $a2, 0x114($sp)
    /* DDB458 0000A9EC 8FA60114 */  lw         $a2, 0x114($sp)
    /* DDB45C 0000A9F0 3C180000 */  lui        $t8, %hi(bu_90cc_vt545_b)
    /* DDB460 0000A9F4 27180000 */  addiu      $t8, $t8, %lo(bu_90cc_vt545_b)
    /* DDB464 0000A9F8 ACD80028 */  sw         $t8, 0x28($a2)
  .L0000A9FC:
    /* DDB468 0000A9FC 3C190000 */  lui        $t9, %hi(bu_90cc_vt547)
    /* DDB46C 0000AA00 27390000 */  addiu      $t9, $t9, %lo(bu_90cc_vt547)
    /* DDB470 0000AA04 AE390028 */  sw         $t9, 0x28($s1)
  .L0000AA08:
    /* DDB474 0000AA08 AFB10160 */  sw         $s1, 0x160($sp)
    /* DDB478 0000AA0C 02208025 */  or         $s0, $s1, $zero
    /* DDB47C 0000AA10 8E51086C */  lw         $s1, 0x86C($s2)
    /* DDB480 0000AA14 02002825 */  or         $a1, $s0, $zero
    /* DDB484 0000AA18 0C000000 */  jal        func_00000000
    /* DDB488 0000AA1C 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB48C 0000AA20 8E0D0014 */  lw         $t5, 0x14($s0)
    /* DDB490 0000AA24 240E0001 */  addiu      $t6, $zero, 0x1
    /* DDB494 0000AA28 51A00003 */  beql       $t5, $zero, .L0000AA38
    /* DDB498 0000AA2C AE110014 */   sw        $s1, 0x14($s0)
    /* DDB49C 0000AA30 AE0E0004 */  sw         $t6, 0x4($s0)
    /* DDB4A0 0000AA34 AE110014 */  sw         $s1, 0x14($s0)
  .L0000AA38:
    /* DDB4A4 0000AA38 0C000000 */  jal        func_00000000
    /* DDB4A8 0000AA3C 24040174 */   addiu     $a0, $zero, 0x174
    /* DDB4AC 0000AA40 10400013 */  beqz       $v0, .L0000AA90
    /* DDB4B0 0000AA44 00408825 */   or        $s1, $v0, $zero
    /* DDB4B4 0000AA48 14400005 */  bnez       $v0, .L0000AA60
    /* DDB4B8 0000AA4C 00403025 */   or        $a2, $v0, $zero
    /* DDB4BC 0000AA50 0C000000 */  jal        func_00000000
    /* DDB4C0 0000AA54 24040174 */   addiu     $a0, $zero, 0x174
    /* DDB4C4 0000AA58 1040000A */  beqz       $v0, .L0000AA84
    /* DDB4C8 0000AA5C 00403025 */   or        $a2, $v0, $zero
  .L0000AA60:
    /* DDB4CC 0000AA60 3C050001 */  lui        $a1, %hi(D_0000883C)
    /* DDB4D0 0000AA64 24A5883C */  addiu      $a1, $a1, %lo(D_0000883C)
    /* DDB4D4 0000AA68 00C02025 */  or         $a0, $a2, $zero
    /* DDB4D8 0000AA6C 0C000000 */  jal        func_00000000
    /* DDB4DC 0000AA70 AFA60114 */   sw        $a2, 0x114($sp)
    /* DDB4E0 0000AA74 8FA60114 */  lw         $a2, 0x114($sp)
    /* DDB4E4 0000AA78 3C0F0000 */  lui        $t7, %hi(bu_90cc_vt545_c)
    /* DDB4E8 0000AA7C 25EF0000 */  addiu      $t7, $t7, %lo(bu_90cc_vt545_c)
    /* DDB4EC 0000AA80 ACCF0028 */  sw         $t7, 0x28($a2)
  .L0000AA84:
    /* DDB4F0 0000AA84 3C180000 */  lui        $t8, %hi(bu_90cc_vt548)
    /* DDB4F4 0000AA88 27180000 */  addiu      $t8, $t8, %lo(bu_90cc_vt548)
    /* DDB4F8 0000AA8C AE380028 */  sw         $t8, 0x28($s1)
  .L0000AA90:
    /* DDB4FC 0000AA90 AFB1015C */  sw         $s1, 0x15C($sp)
    /* DDB500 0000AA94 02208025 */  or         $s0, $s1, $zero
    /* DDB504 0000AA98 8E510868 */  lw         $s1, 0x868($s2)
    /* DDB508 0000AA9C 02002825 */  or         $a1, $s0, $zero
    /* DDB50C 0000AAA0 0C000000 */  jal        func_00000000
    /* DDB510 0000AAA4 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB514 0000AAA8 8E190014 */  lw         $t9, 0x14($s0)
    /* DDB518 0000AAAC 240D0001 */  addiu      $t5, $zero, 0x1
    /* DDB51C 0000AAB0 24040174 */  addiu      $a0, $zero, 0x174
    /* DDB520 0000AAB4 13200002 */  beqz       $t9, .L0000AAC0
    /* DDB524 0000AAB8 00000000 */   nop
    /* DDB528 0000AABC AE0D0004 */  sw         $t5, 0x4($s0)
  .L0000AAC0:
    /* DDB52C 0000AAC0 0C000000 */  jal        func_00000000
    /* DDB530 0000AAC4 AE110014 */   sw        $s1, 0x14($s0)
    /* DDB534 0000AAC8 10400013 */  beqz       $v0, .L0000AB18
    /* DDB538 0000AACC 00408825 */   or        $s1, $v0, $zero
    /* DDB53C 0000AAD0 14400005 */  bnez       $v0, .L0000AAE8
    /* DDB540 0000AAD4 00403025 */   or        $a2, $v0, $zero
    /* DDB544 0000AAD8 0C000000 */  jal        func_00000000
    /* DDB548 0000AADC 24040174 */   addiu     $a0, $zero, 0x174
    /* DDB54C 0000AAE0 1040000A */  beqz       $v0, .L0000AB0C
    /* DDB550 0000AAE4 00403025 */   or        $a2, $v0, $zero
  .L0000AAE8:
    /* DDB554 0000AAE8 3C050001 */  lui        $a1, %hi(D_00008844)
    /* DDB558 0000AAEC 24A58844 */  addiu      $a1, $a1, %lo(D_00008844)
    /* DDB55C 0000AAF0 00C02025 */  or         $a0, $a2, $zero
    /* DDB560 0000AAF4 0C000000 */  jal        func_00000000
    /* DDB564 0000AAF8 AFA60114 */   sw        $a2, 0x114($sp)
    /* DDB568 0000AAFC 8FA60114 */  lw         $a2, 0x114($sp)
    /* DDB56C 0000AB00 3C0E0000 */  lui        $t6, %hi(bu_90cc_vt545_d)
    /* DDB570 0000AB04 25CE0000 */  addiu      $t6, $t6, %lo(bu_90cc_vt545_d)
    /* DDB574 0000AB08 ACCE0028 */  sw         $t6, 0x28($a2)
  .L0000AB0C:
    /* DDB578 0000AB0C 3C0F0000 */  lui        $t7, %hi(bu_90cc_vt548)
    /* DDB57C 0000AB10 25EF0000 */  addiu      $t7, $t7, %lo(bu_90cc_vt548)
    /* DDB580 0000AB14 AE2F0028 */  sw         $t7, 0x28($s1)
  .L0000AB18:
    /* DDB584 0000AB18 AFB10158 */  sw         $s1, 0x158($sp)
    /* DDB588 0000AB1C 02208025 */  or         $s0, $s1, $zero
    /* DDB58C 0000AB20 8E510868 */  lw         $s1, 0x868($s2)
    /* DDB590 0000AB24 02002825 */  or         $a1, $s0, $zero
    /* DDB594 0000AB28 0C000000 */  jal        func_00000000
    /* DDB598 0000AB2C 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB59C 0000AB30 8E180014 */  lw         $t8, 0x14($s0)
    /* DDB5A0 0000AB34 24190001 */  addiu      $t9, $zero, 0x1
    /* DDB5A4 0000AB38 3404FFFF */  ori        $a0, $zero, 0xFFFF
    /* DDB5A8 0000AB3C 13000002 */  beqz       $t8, .L0000AB48
    /* DDB5AC 0000AB40 00000000 */   nop
    /* DDB5B0 0000AB44 AE190004 */  sw         $t9, 0x4($s0)
  .L0000AB48:
    /* DDB5B4 0000AB48 0C000000 */  jal        func_00000000
    /* DDB5B8 0000AB4C AE110014 */   sw        $s1, 0x14($s0)
    /* DDB5BC 0000AB50 0C000000 */  jal        func_00000000
    /* DDB5C0 0000AB54 00000000 */   nop
  .L0000AB58:
    /* DDB5C4 0000AB58 3C040001 */  lui        $a0, %hi(D_0000884C)
    /* DDB5C8 0000AB5C 2484884C */  addiu      $a0, $a0, %lo(D_0000884C)
    /* DDB5CC 0000AB60 0C000000 */  jal        func_00000000
    /* DDB5D0 0000AB64 00002825 */   or        $a1, $zero, $zero
    /* DDB5D4 0000AB68 0C000000 */  jal        func_00000000
    /* DDB5D8 0000AB6C 2404016C */   addiu     $a0, $zero, 0x16C
    /* DDB5DC 0000AB70 10400016 */  beqz       $v0, .L0000ABCC
    /* DDB5E0 0000AB74 00408825 */   or        $s1, $v0, $zero
    /* DDB5E4 0000AB78 44802000 */  mtc1       $zero, $f4
    /* DDB5E8 0000AB7C 3C050001 */  lui        $a1, %hi(D_0000885C)
    /* DDB5EC 0000AB80 24A5885C */  addiu      $a1, $a1, %lo(D_0000885C)
    /* DDB5F0 0000AB84 00402025 */  or         $a0, $v0, $zero
    /* DDB5F4 0000AB88 24060000 */  addiu      $a2, $zero, 0x0
    /* DDB5F8 0000AB8C 24070000 */  addiu      $a3, $zero, 0x0
    /* DDB5FC 0000AB90 0C000000 */  jal        func_00000000
    /* DDB600 0000AB94 E7A40010 */   swc1      $f4, 0x10($sp)
    /* DDB604 0000AB98 3C010000 */  lui        $at, %hi(func_000008B4)
    /* DDB608 0000AB9C C42008B4 */  lwc1       $f0, %lo(func_000008B4)($at)
    /* DDB60C 0000ABA0 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* DDB610 0000ABA4 44813000 */  mtc1       $at, $f6
    /* DDB614 0000ABA8 3C0D0000 */  lui        $t5, %hi(bu_90cc_d207dc)
    /* DDB618 0000ABAC 25AD0000 */  addiu      $t5, $t5, %lo(bu_90cc_d207dc)
    /* DDB61C 0000ABB0 340EFFFF */  ori        $t6, $zero, 0xFFFF
    /* DDB620 0000ABB4 AE2E0120 */  sw         $t6, 0x120($s1)
    /* DDB624 0000ABB8 AE2D0028 */  sw         $t5, 0x28($s1)
    /* DDB628 0000ABBC E6200108 */  swc1       $f0, 0x108($s1)
    /* DDB62C 0000ABC0 E620010C */  swc1       $f0, 0x10C($s1)
    /* DDB630 0000ABC4 E6200110 */  swc1       $f0, 0x110($s1)
    /* DDB634 0000ABC8 E6260124 */  swc1       $f6, 0x124($s1)
  .L0000ABCC:
    /* DDB638 0000ABCC AE510850 */  sw         $s1, 0x850($s2)
    /* DDB63C 0000ABD0 02402025 */  or         $a0, $s2, $zero
    /* DDB640 0000ABD4 0C000000 */  jal        func_00000000
    /* DDB644 0000ABD8 02202825 */   or        $a1, $s1, $zero
    /* DDB648 0000ABDC 8E500850 */  lw         $s0, 0x850($s2)
    /* DDB64C 0000ABE0 44800000 */  mtc1       $zero, $f0
    /* DDB650 0000ABE4 3C0142C8 */  lui        $at, (0x42C80000 >> 16)
    /* DDB654 0000ABE8 44814000 */  mtc1       $at, $f8
    /* DDB658 0000ABEC 3C050000 */  lui        $a1, (0x0 >> 16)
    /* DDB65C 0000ABF0 E60000B4 */  swc1       $f0, 0xB4($s0)
    /* DDB660 0000ABF4 E60000BC */  swc1       $f0, 0xBC($s0)
    /* DDB664 0000ABF8 E60800B8 */  swc1       $f8, 0xB8($s0)
    /* DDB668 0000ABFC 8CA50000 */  lw         $a1, 0x0($a1)
    /* DDB66C 0000AC00 00002025 */  or         $a0, $zero, $zero
    /* DDB670 0000AC04 02403025 */  or         $a2, $s2, $zero
    /* DDB674 0000AC08 0C000000 */  jal        func_00000000
    /* DDB678 0000AC0C 261000B4 */   addiu     $s0, $s0, 0xB4
    /* DDB67C 0000AC10 0C000000 */  jal        func_00000000
    /* DDB680 0000AC14 AE420840 */   sw        $v0, 0x840($s2)
    /* DDB684 0000AC18 8FAF0188 */  lw         $t7, 0x188($sp)
    /* DDB688 0000AC1C 8E450840 */  lw         $a1, 0x840($s2)
    /* DDB68C 0000AC20 02402025 */  or         $a0, $s2, $zero
    /* DDB690 0000AC24 0C000000 */  jal        func_00000000
    /* DDB694 0000AC28 AE4F0800 */   sw        $t7, 0x800($s2)
    /* DDB698 0000AC2C 8E500840 */  lw         $s0, 0x840($s2)
    /* DDB69C 0000AC30 2401FFF7 */  addiu      $at, $zero, -0x9
    /* DDB6A0 0000AC34 3C0D0000 */  lui        $t5, (0x0 >> 16)
    /* DDB6A4 0000AC38 8E180018 */  lw         $t8, 0x18($s0)
    /* DDB6A8 0000AC3C 3C020000 */  lui        $v0, %hi(func_00000000 + 0x4)
    /* DDB6AC 0000AC40 00002825 */  or         $a1, $zero, $zero
    /* DDB6B0 0000AC44 0301C824 */  and        $t9, $t8, $at
    /* DDB6B4 0000AC48 AE190018 */  sw         $t9, 0x18($s0)
    /* DDB6B8 0000AC4C 8DAD0000 */  lw         $t5, 0x0($t5)
    /* DDB6BC 0000AC50 8C420004 */  lw         $v0, %lo(func_00000000 + 0x4)($v0)
    /* DDB6C0 0000AC54 3C010000 */  lui        $at, (0x0 >> 16)
    /* DDB6C4 0000AC58 35AE0008 */  ori        $t6, $t5, 0x8
    /* DDB6C8 0000AC5C AC2E0000 */  sw         $t6, 0x0($at)
    /* DDB6CC 0000AC60 3C010002 */  lui        $at, (0x20000 >> 16)
    /* DDB6D0 0000AC64 00411025 */  or         $v0, $v0, $at
    /* DDB6D4 0000AC68 3C010000 */  lui        $at, %hi(func_00000000 + 0x4)
    /* DDB6D8 0000AC6C AC220004 */  sw         $v0, %lo(func_00000000 + 0x4)($at)
    /* DDB6DC 0000AC70 3C020000 */  lui        $v0, %hi(func_00000000 + 0x4)
    /* DDB6E0 0000AC74 8C420004 */  lw         $v0, %lo(func_00000000 + 0x4)($v0)
    /* DDB6E4 0000AC78 3C01FFF7 */  lui        $at, (0xFFF7FFFF >> 16)
    /* DDB6E8 0000AC7C 3421FFFF */  ori        $at, $at, (0xFFF7FFFF & 0xFFFF)
    /* DDB6EC 0000AC80 00411024 */  and        $v0, $v0, $at
    /* DDB6F0 0000AC84 2401FFFD */  addiu      $at, $zero, -0x3
    /* DDB6F4 0000AC88 00411024 */  and        $v0, $v0, $at
    /* DDB6F8 0000AC8C 3C010000 */  lui        $at, %hi(func_00000000 + 0x4)
    /* DDB6FC 0000AC90 AC220004 */  sw         $v0, %lo(func_00000000 + 0x4)($at)
    /* DDB700 0000AC94 3C010000 */  lui        $at, (0x0 >> 16)
    /* DDB704 0000AC98 AC320000 */  sw         $s2, 0x0($at)
    /* DDB708 0000AC9C 26100018 */  addiu      $s0, $s0, 0x18
    /* DDB70C 0000ACA0 2CA10028 */  sltiu      $at, $a1, 0x28
  .L0000ACA4:
    /* DDB710 0000ACA4 14200008 */  bnez       $at, .L0000ACC8
    /* DDB714 0000ACA8 00A03025 */   or        $a2, $a1, $zero
    /* DDB718 0000ACAC 3C040001 */  lui        $a0, %hi(D_00008868)
    /* DDB71C 0000ACB0 24848868 */  addiu      $a0, $a0, %lo(D_00008868)
    /* DDB720 0000ACB4 AFA50058 */  sw         $a1, 0x58($sp)
    /* DDB724 0000ACB8 0C000000 */  jal        func_00000000
    /* DDB728 0000ACBC AFA60114 */   sw        $a2, 0x114($sp)
    /* DDB72C 0000ACC0 8FA50058 */  lw         $a1, 0x58($sp)
    /* DDB730 0000ACC4 8FA60114 */  lw         $a2, 0x114($sp)
  .L0000ACC8:
    /* DDB734 0000ACC8 00067880 */  sll        $t7, $a2, 2
    /* DDB738 0000ACCC 3C010000 */  lui        $at, (0x0 >> 16)
    /* DDB73C 0000ACD0 002F0821 */  addu       $at, $at, $t7
    /* DDB740 0000ACD4 AC200000 */  sw         $zero, 0x0($at)
    /* DDB744 0000ACD8 24010023 */  addiu      $at, $zero, 0x23
    /* DDB748 0000ACDC 24A50001 */  addiu      $a1, $a1, 0x1
    /* DDB74C 0000ACE0 54A1FFF0 */  bnel       $a1, $at, .L0000ACA4
    /* DDB750 0000ACE4 2CA10028 */   sltiu     $at, $a1, 0x28
    /* DDB754 0000ACE8 3C020000 */  lui        $v0, (0x0 >> 16)
    /* DDB758 0000ACEC 3C100000 */  lui        $s0, (0x0 >> 16)
    /* DDB75C 0000ACF0 3C180002 */  lui        $t8, (0x2A003 >> 16)
    /* DDB760 0000ACF4 26100000 */  addiu      $s0, $s0, 0x0
    /* DDB764 0000ACF8 24420000 */  addiu      $v0, $v0, 0x0
    /* DDB768 0000ACFC 3718A003 */  ori        $t8, $t8, (0x2A003 & 0xFFFF)
    /* DDB76C 0000AD00 AC580004 */  sw         $t8, 0x4($v0)
    /* DDB770 0000AD04 AC400000 */  sw         $zero, 0x0($v0)
    /* DDB774 0000AD08 02002025 */  or         $a0, $s0, $zero
    /* DDB778 0000AD0C 24050001 */  addiu      $a1, $zero, 0x1
    /* DDB77C 0000AD10 0C000000 */  jal        func_00000000
    /* DDB780 0000AD14 00003025 */   or        $a2, $zero, $zero
    /* DDB784 0000AD18 AE4208F4 */  sw         $v0, 0x8F4($s2)
    /* DDB788 0000AD1C 02002025 */  or         $a0, $s0, $zero
    /* DDB78C 0000AD20 24050002 */  addiu      $a1, $zero, 0x2
    /* DDB790 0000AD24 0C000000 */  jal        func_00000000
    /* DDB794 0000AD28 00003025 */   or        $a2, $zero, $zero
    /* DDB798 0000AD2C AE4208F8 */  sw         $v0, 0x8F8($s2)
    /* DDB79C 0000AD30 02002025 */  or         $a0, $s0, $zero
    /* DDB7A0 0000AD34 24050003 */  addiu      $a1, $zero, 0x3
    /* DDB7A4 0000AD38 0C000000 */  jal        func_00000000
    /* DDB7A8 0000AD3C 00003025 */   or        $a2, $zero, $zero
    /* DDB7AC 0000AD40 AE4208FC */  sw         $v0, 0x8FC($s2)
    /* DDB7B0 0000AD44 8FB90174 */  lw         $t9, 0x174($sp)
    /* DDB7B4 0000AD48 13200017 */  beqz       $t9, .L0000ADA8
    /* DDB7B8 0000AD4C 3C030000 */   lui       $v1, (0x0 >> 16)
    /* DDB7BC 0000AD50 24620000 */  addiu      $v0, $v1, 0x0
    /* DDB7C0 0000AD54 8C4D0000 */  lw         $t5, 0x0($v0)
    /* DDB7C4 0000AD58 3C0E0000 */  lui        $t6, (0x0 >> 16)
    /* DDB7C8 0000AD5C 25CE0000 */  addiu      $t6, $t6, 0x0
    /* DDB7CC 0000AD60 11A0000F */  beqz       $t5, .L0000ADA0
    /* DDB7D0 0000AD64 8FA50180 */   lw        $a1, 0x180($sp)
    /* DDB7D4 0000AD68 3C040000 */  lui        $a0, %hi(func_00000148 + 0x18)
    /* DDB7D8 0000AD6C 24840160 */  addiu      $a0, $a0, %lo(func_00000148 + 0x18)
    /* DDB7DC 0000AD70 8DC30000 */  lw         $v1, 0x0($t6)
  .L0000AD74:
    /* DDB7E0 0000AD74 54A30007 */  bnel       $a1, $v1, .L0000AD94
    /* DDB7E4 0000AD78 8C430018 */   lw        $v1, 0x18($v0)
    /* DDB7E8 0000AD7C 8C4F0004 */  lw         $t7, 0x4($v0)
    /* DDB7EC 0000AD80 24590008 */  addiu      $t9, $v0, 0x8
    /* DDB7F0 0000AD84 000FC080 */  sll        $t8, $t7, 2
    /* DDB7F4 0000AD88 00988021 */  addu       $s0, $a0, $t8
    /* DDB7F8 0000AD8C AE190000 */  sw         $t9, 0x0($s0)
    /* DDB7FC 0000AD90 8C430018 */  lw         $v1, 0x18($v0)
  .L0000AD94:
    /* DDB800 0000AD94 24420018 */  addiu      $v0, $v0, 0x18
    /* DDB804 0000AD98 1460FFF6 */  bnez       $v1, .L0000AD74
    /* DDB808 0000AD9C 00000000 */   nop
  .L0000ADA0:
    /* DDB80C 0000ADA0 10000009 */  b          .L0000ADC8
    /* DDB810 0000ADA4 8E4D0A58 */   lw        $t5, 0xA58($s2)
  .L0000ADA8:
    /* DDB814 0000ADA8 3C020000 */  lui        $v0, %hi(func_00000148 + 0x18)
    /* DDB818 0000ADAC 3C030000 */  lui        $v1, %hi(func_00000148 + 0x24)
    /* DDB81C 0000ADB0 2463016C */  addiu      $v1, $v1, %lo(func_00000148 + 0x24)
    /* DDB820 0000ADB4 24420160 */  addiu      $v0, $v0, %lo(func_00000148 + 0x18)
  .L0000ADB8:
    /* DDB824 0000ADB8 24420004 */  addiu      $v0, $v0, 0x4
    /* DDB828 0000ADBC 1443FFFE */  bne        $v0, $v1, .L0000ADB8
    /* DDB82C 0000ADC0 AC40FFFC */   sw        $zero, -0x4($v0)
    /* DDB830 0000ADC4 8E4D0A58 */  lw         $t5, 0xA58($s2)
  .L0000ADC8:
    /* DDB834 0000ADC8 31AE0008 */  andi       $t6, $t5, 0x8
    /* DDB838 0000ADCC 11C00005 */  beqz       $t6, .L0000ADE4
    /* DDB83C 0000ADD0 00000000 */   nop
    /* DDB840 0000ADD4 0C000000 */  jal        func_00000000
    /* DDB844 0000ADD8 02402025 */   or        $a0, $s2, $zero
    /* DDB848 0000ADDC 10000004 */  b          .L0000ADF0
    /* DDB84C 0000ADE0 8FAF0184 */   lw        $t7, 0x184($sp)
  .L0000ADE4:
    /* DDB850 0000ADE4 0C000000 */  jal        func_00000000
    /* DDB854 0000ADE8 02402025 */   or        $a0, $s2, $zero
    /* DDB858 0000ADEC 8FAF0184 */  lw         $t7, 0x184($sp)
  .L0000ADF0:
    /* DDB85C 0000ADF0 8E470840 */  lw         $a3, 0x840($s2)
    /* DDB860 0000ADF4 8E4608B8 */  lw         $a2, 0x8B8($s2)
    /* DDB864 0000ADF8 A64F0904 */  sh         $t7, 0x904($s2)
    /* DDB868 0000ADFC AFB20010 */  sw         $s2, 0x10($sp)
    /* DDB86C 0000AE00 8FA50184 */  lw         $a1, 0x184($sp)
    /* DDB870 0000AE04 0C000000 */  jal        func_00000000
    /* DDB874 0000AE08 8FA40180 */   lw        $a0, 0x180($sp)
    /* DDB878 0000AE0C 8E450A58 */  lw         $a1, 0xA58($s2)
    /* DDB87C 0000AE10 02402025 */  or         $a0, $s2, $zero
    /* DDB880 0000AE14 0C000000 */  jal        func_00000000
    /* DDB884 0000AE18 30A50001 */   andi      $a1, $a1, 0x1
    /* DDB888 0000AE1C 8E580A58 */  lw         $t8, 0xA58($s2)
    /* DDB88C 0000AE20 33190003 */  andi       $t9, $t8, 0x3
    /* DDB890 0000AE24 132000A2 */  beqz       $t9, .L0000B0B0
    /* DDB894 0000AE28 3C040001 */   lui       $a0, %hi(D_00008880)
    /* DDB898 0000AE2C 24848880 */  addiu      $a0, $a0, %lo(D_00008880)
    /* DDB89C 0000AE30 0C000000 */  jal        func_00000000
    /* DDB8A0 0000AE34 00002825 */   or        $a1, $zero, $zero
    /* DDB8A4 0000AE38 3C050001 */  lui        $a1, %hi(D_00008888)
    /* DDB8A8 0000AE3C 24A58888 */  addiu      $a1, $a1, %lo(D_00008888)
    /* DDB8AC 0000AE40 0C000000 */  jal        func_00000000
    /* DDB8B0 0000AE44 00002025 */   or        $a0, $zero, $zero
    /* DDB8B4 0000AE48 AE420870 */  sw         $v0, 0x870($s2)
    /* DDB8B8 0000AE4C 24430018 */  addiu      $v1, $v0, 0x18
    /* DDB8BC 0000AE50 8C6D0000 */  lw         $t5, 0x0($v1)
    /* DDB8C0 0000AE54 2401FFFB */  addiu      $at, $zero, -0x5
    /* DDB8C4 0000AE58 02402025 */  or         $a0, $s2, $zero
    /* DDB8C8 0000AE5C 01A17024 */  and        $t6, $t5, $at
    /* DDB8CC 0000AE60 AC6E0000 */  sw         $t6, 0x0($v1)
    /* DDB8D0 0000AE64 0C000000 */  jal        func_00000000
    /* DDB8D4 0000AE68 8E450870 */   lw        $a1, 0x870($s2)
    /* DDB8D8 0000AE6C 8E510870 */  lw         $s1, 0x870($s2)
    /* DDB8DC 0000AE70 8FA50164 */  lw         $a1, 0x164($sp)
    /* DDB8E0 0000AE74 0C000000 */  jal        func_00000000
    /* DDB8E4 0000AE78 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB8E8 0000AE7C 8FA20164 */  lw         $v0, 0x164($sp)
    /* DDB8EC 0000AE80 8C4F0014 */  lw         $t7, 0x14($v0)
    /* DDB8F0 0000AE84 11E00002 */  beqz       $t7, .L0000AE90
    /* DDB8F4 0000AE88 24180001 */   addiu     $t8, $zero, 0x1
    /* DDB8F8 0000AE8C AC580004 */  sw         $t8, 0x4($v0)
  .L0000AE90:
    /* DDB8FC 0000AE90 AC510014 */  sw         $s1, 0x14($v0)
    /* DDB900 0000AE94 8E590A58 */  lw         $t9, 0xA58($s2)
    /* DDB904 0000AE98 332D0001 */  andi       $t5, $t9, 0x1
    /* DDB908 0000AE9C 51A0000D */  beql       $t5, $zero, .L0000AED4
    /* DDB90C 0000AEA0 8E510870 */   lw        $s1, 0x870($s2)
    /* DDB910 0000AEA4 8E510870 */  lw         $s1, 0x870($s2)
    /* DDB914 0000AEA8 8FA50160 */  lw         $a1, 0x160($sp)
    /* DDB918 0000AEAC 0C000000 */  jal        func_00000000
    /* DDB91C 0000AEB0 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB920 0000AEB4 8FA30160 */  lw         $v1, 0x160($sp)
    /* DDB924 0000AEB8 240F0001 */  addiu      $t7, $zero, 0x1
    /* DDB928 0000AEBC 8C6E0014 */  lw         $t6, 0x14($v1)
    /* DDB92C 0000AEC0 51C00003 */  beql       $t6, $zero, .L0000AED0
    /* DDB930 0000AEC4 AC710014 */   sw        $s1, 0x14($v1)
    /* DDB934 0000AEC8 AC6F0004 */  sw         $t7, 0x4($v1)
    /* DDB938 0000AECC AC710014 */  sw         $s1, 0x14($v1)
  .L0000AED0:
    /* DDB93C 0000AED0 8E510870 */  lw         $s1, 0x870($s2)
  .L0000AED4:
    /* DDB940 0000AED4 8FA5015C */  lw         $a1, 0x15C($sp)
    /* DDB944 0000AED8 0C000000 */  jal        func_00000000
    /* DDB948 0000AEDC 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB94C 0000AEE0 8FA2015C */  lw         $v0, 0x15C($sp)
    /* DDB950 0000AEE4 24190001 */  addiu      $t9, $zero, 0x1
    /* DDB954 0000AEE8 8C580014 */  lw         $t8, 0x14($v0)
    /* DDB958 0000AEEC 53000003 */  beql       $t8, $zero, .L0000AEFC
    /* DDB95C 0000AEF0 AC510014 */   sw        $s1, 0x14($v0)
    /* DDB960 0000AEF4 AC590004 */  sw         $t9, 0x4($v0)
    /* DDB964 0000AEF8 AC510014 */  sw         $s1, 0x14($v0)
  .L0000AEFC:
    /* DDB968 0000AEFC 8E510870 */  lw         $s1, 0x870($s2)
    /* DDB96C 0000AF00 8FA50158 */  lw         $a1, 0x158($sp)
    /* DDB970 0000AF04 0C000000 */  jal        func_00000000
    /* DDB974 0000AF08 26240010 */   addiu     $a0, $s1, 0x10
    /* DDB978 0000AF0C 8FA20158 */  lw         $v0, 0x158($sp)
    /* DDB97C 0000AF10 240E0001 */  addiu      $t6, $zero, 0x1
    /* DDB980 0000AF14 24040001 */  addiu      $a0, $zero, 0x1
    /* DDB984 0000AF18 8C4D0014 */  lw         $t5, 0x14($v0)
    /* DDB988 0000AF1C 11A00002 */  beqz       $t5, .L0000AF28
    /* DDB98C 0000AF20 00000000 */   nop
    /* DDB990 0000AF24 AC4E0004 */  sw         $t6, 0x4($v0)
  .L0000AF28:
    /* DDB994 0000AF28 0C000000 */  jal        func_00000000
    /* DDB998 0000AF2C AC510014 */   sw        $s1, 0x14($v0)
    /* DDB99C 0000AF30 8FAF0164 */  lw         $t7, 0x164($sp)
    /* DDB9A0 0000AF34 3C100000 */  lui        $s0, %hi(func_00000044 + 0x28)
    /* DDB9A4 0000AF38 8E02006C */  lw         $v0, %lo(func_00000044 + 0x28)($s0)
    /* DDB9A8 0000AF3C 8DF00028 */  lw         $s0, 0x28($t7)
    /* DDB9AC 0000AF40 3C010000 */  lui        $at, %hi(func_000008B4 + 0x4)
    /* DDB9B0 0000AF44 C42A08B8 */  lwc1       $f10, %lo(func_000008B4 + 0x4)($at)
    /* DDB9B4 0000AF48 86180058 */  lh         $t8, 0x58($s0)
    /* DDB9B8 0000AF4C 3C0142C8 */  lui        $at, (0x42C80000 >> 16)
    /* DDB9BC 0000AF50 8E450870 */  lw         $a1, 0x870($s2)
    /* DDB9C0 0000AF54 8E46086C */  lw         $a2, 0x86C($s2)
    /* DDB9C4 0000AF58 44818000 */  mtc1       $at, $f16
    /* DDB9C8 0000AF5C 24190010 */  addiu      $t9, $zero, 0x10
    /* DDB9CC 0000AF60 24510070 */  addiu      $s1, $v0, 0x70
    /* DDB9D0 0000AF64 AFB10014 */  sw         $s1, 0x14($sp)
    /* DDB9D4 0000AF68 AFB90010 */  sw         $t9, 0x10($sp)
    /* DDB9D8 0000AF6C E7AA0018 */  swc1       $f10, 0x18($sp)
    /* DDB9DC 0000AF70 E7B0001C */  swc1       $f16, 0x1C($sp)
    /* DDB9E0 0000AF74 8E19005C */  lw         $t9, 0x5C($s0)
    /* DDB9E4 0000AF78 02403825 */  or         $a3, $s2, $zero
    /* DDB9E8 0000AF7C 030F2021 */  addu       $a0, $t8, $t7
    /* DDB9EC 0000AF80 0320F809 */  jalr       $t9
    /* DDB9F0 0000AF84 00000000 */   nop
    /* DDB9F4 0000AF88 8E4D0A58 */  lw         $t5, 0xA58($s2)
    /* DDB9F8 0000AF8C 8FB80160 */  lw         $t8, 0x160($sp)
    /* DDB9FC 0000AF90 2419000C */  addiu      $t9, $zero, 0xC
    /* DDBA00 0000AF94 31AE0001 */  andi       $t6, $t5, 0x1
    /* DDBA04 0000AF98 11C00015 */  beqz       $t6, .L0000AFF0
    /* DDBA08 0000AF9C 3C010000 */   lui       $at, %hi(func_000008B4 + 0x8)
    /* DDBA0C 0000AFA0 8F100028 */  lw         $s0, 0x28($t8)
    /* DDBA10 0000AFA4 C43208BC */  lwc1       $f18, %lo(func_000008B4 + 0x8)($at)
    /* DDBA14 0000AFA8 3C0142C8 */  lui        $at, (0x42C80000 >> 16)
    /* DDBA18 0000AFAC 860F0058 */  lh         $t7, 0x58($s0)
    /* DDBA1C 0000AFB0 8E450870 */  lw         $a1, 0x870($s2)
    /* DDBA20 0000AFB4 8E46086C */  lw         $a2, 0x86C($s2)
    /* DDBA24 0000AFB8 44812000 */  mtc1       $at, $f4
    /* DDBA28 0000AFBC AFB10014 */  sw         $s1, 0x14($sp)
    /* DDBA2C 0000AFC0 AFB90010 */  sw         $t9, 0x10($sp)
    /* DDBA30 0000AFC4 E7B20018 */  swc1       $f18, 0x18($sp)
    /* DDBA34 0000AFC8 E7A4001C */  swc1       $f4, 0x1C($sp)
    /* DDBA38 0000AFCC 8E19005C */  lw         $t9, 0x5C($s0)
    /* DDBA3C 0000AFD0 02403825 */  or         $a3, $s2, $zero
    /* DDBA40 0000AFD4 01F82021 */  addu       $a0, $t7, $t8
    /* DDBA44 0000AFD8 0320F809 */  jalr       $t9
    /* DDBA48 0000AFDC 00000000 */   nop
    /* DDBA4C 0000AFE0 0C000000 */  jal        func_00000000
    /* DDBA50 0000AFE4 8FA40164 */   lw        $a0, 0x164($sp)
    /* DDBA54 0000AFE8 0C000000 */  jal        func_00000000
    /* DDBA58 0000AFEC 8FA40164 */   lw        $a0, 0x164($sp)
  .L0000AFF0:
    /* DDBA5C 0000AFF0 8FAD015C */  lw         $t5, 0x15C($sp)
    /* DDBA60 0000AFF4 3C100000 */  lui        $s0, %hi(func_00000008 + 0x2C)
    /* DDBA64 0000AFF8 8E020034 */  lw         $v0, %lo(func_00000008 + 0x2C)($s0)
    /* DDBA68 0000AFFC 8DB00028 */  lw         $s0, 0x28($t5)
    /* DDBA6C 0000B000 3C014200 */  lui        $at, (0x42000000 >> 16)
    /* DDBA70 0000B004 44813000 */  mtc1       $at, $f6
    /* DDBA74 0000B008 860E0058 */  lh         $t6, 0x58($s0)
    /* DDBA78 0000B00C 3C014294 */  lui        $at, (0x42940000 >> 16)
    /* DDBA7C 0000B010 8E450870 */  lw         $a1, 0x870($s2)
    /* DDBA80 0000B014 8E46086C */  lw         $a2, 0x86C($s2)
    /* DDBA84 0000B018 44814000 */  mtc1       $at, $f8
    /* DDBA88 0000B01C 240F0008 */  addiu      $t7, $zero, 0x8
    /* DDBA8C 0000B020 24580070 */  addiu      $t8, $v0, 0x70
    /* DDBA90 0000B024 AFB80014 */  sw         $t8, 0x14($sp)
    /* DDBA94 0000B028 AFAF0010 */  sw         $t7, 0x10($sp)
    /* DDBA98 0000B02C E7A60018 */  swc1       $f6, 0x18($sp)
    /* DDBA9C 0000B030 E7A8001C */  swc1       $f8, 0x1C($sp)
    /* DDBAA0 0000B034 8E19005C */  lw         $t9, 0x5C($s0)
    /* DDBAA4 0000B038 02403825 */  or         $a3, $s2, $zero
    /* DDBAA8 0000B03C 01CD2021 */  addu       $a0, $t6, $t5
    /* DDBAAC 0000B040 0320F809 */  jalr       $t9
    /* DDBAB0 0000B044 00000000 */   nop
    /* DDBAB4 0000B048 8FAE0158 */  lw         $t6, 0x158($sp)
    /* DDBAB8 0000B04C 3C100000 */  lui        $s0, %hi(func_00000044 + 0x4)
    /* DDBABC 0000B050 8E020048 */  lw         $v0, %lo(func_00000044 + 0x4)($s0)
    /* DDBAC0 0000B054 8DD00028 */  lw         $s0, 0x28($t6)
    /* DDBAC4 0000B058 3C014200 */  lui        $at, (0x42000000 >> 16)
    /* DDBAC8 0000B05C 44815000 */  mtc1       $at, $f10
    /* DDBACC 0000B060 860D0058 */  lh         $t5, 0x58($s0)
    /* DDBAD0 0000B064 3C014294 */  lui        $at, (0x42940000 >> 16)
    /* DDBAD4 0000B068 8E450870 */  lw         $a1, 0x870($s2)
    /* DDBAD8 0000B06C 8E46086C */  lw         $a2, 0x86C($s2)
    /* DDBADC 0000B070 44818000 */  mtc1       $at, $f16
    /* DDBAE0 0000B074 240F0008 */  addiu      $t7, $zero, 0x8
    /* DDBAE4 0000B078 24580070 */  addiu      $t8, $v0, 0x70
    /* DDBAE8 0000B07C AFB80014 */  sw         $t8, 0x14($sp)
    /* DDBAEC 0000B080 AFAF0010 */  sw         $t7, 0x10($sp)
    /* DDBAF0 0000B084 E7AA0018 */  swc1       $f10, 0x18($sp)
    /* DDBAF4 0000B088 E7B0001C */  swc1       $f16, 0x1C($sp)
    /* DDBAF8 0000B08C 8E19005C */  lw         $t9, 0x5C($s0)
    /* DDBAFC 0000B090 02403825 */  or         $a3, $s2, $zero
    /* DDBB00 0000B094 01AE2021 */  addu       $a0, $t5, $t6
    /* DDBB04 0000B098 0320F809 */  jalr       $t9
    /* DDBB08 0000B09C 00000000 */   nop
    /* DDBB0C 0000B0A0 0C000000 */  jal        func_00000000
    /* DDBB10 0000B0A4 3404FFFF */   ori       $a0, $zero, 0xFFFF
    /* DDBB14 0000B0A8 0C000000 */  jal        func_00000000
    /* DDBB18 0000B0AC 00000000 */   nop
  .L0000B0B0:
    /* DDBB1C 0000B0B0 3C020000 */  lui        $v0, (0x0 >> 16)
    /* DDBB20 0000B0B4 24420000 */  addiu      $v0, $v0, 0x0
    /* DDBB24 0000B0B8 8C4D0000 */  lw         $t5, 0x0($v0)
    /* DDBB28 0000B0BC 3C100000 */  lui        $s0, %hi(func_00000044 + 0x28)
    /* DDBB2C 0000B0C0 3C110000 */  lui        $s1, %hi(func_00000008)
    /* DDBB30 0000B0C4 AE4D0814 */  sw         $t5, 0x814($s2)
    /* DDBB34 0000B0C8 8C4E0008 */  lw         $t6, 0x8($v0)
    /* DDBB38 0000B0CC 3C180000 */  lui        $t8, %hi(func_00000044 + 0x30)
    /* DDBB3C 0000B0D0 3C060000 */  lui        $a2, %hi(func_00000044 + 0x24)
    /* DDBB40 0000B0D4 AE4E0818 */  sw         $t6, 0x818($s2)
    /* DDBB44 0000B0D8 8C4F0004 */  lw         $t7, 0x4($v0)
    /* DDBB48 0000B0DC 00002025 */  or         $a0, $zero, $zero
    /* DDBB4C 0000B0E0 02402825 */  or         $a1, $s2, $zero
    /* DDBB50 0000B0E4 AE4F081C */  sw         $t7, 0x81C($s2)
    /* DDBB54 0000B0E8 8E10006C */  lw         $s0, %lo(func_00000044 + 0x28)($s0)
    /* DDBB58 0000B0EC AE500824 */  sw         $s0, 0x824($s2)
    /* DDBB5C 0000B0F0 3C100000 */  lui        $s0, %hi(func_00000080 + 0x8)
    /* DDBB60 0000B0F4 8E100088 */  lw         $s0, %lo(func_00000080 + 0x8)($s0)
    /* DDBB64 0000B0F8 AE500820 */  sw         $s0, 0x820($s2)
    /* DDBB68 0000B0FC 8E310008 */  lw         $s1, %lo(func_00000008)($s1)
    /* DDBB6C 0000B100 3C100000 */  lui        $s0, %hi(func_00000044 + 0x2C)
    /* DDBB70 0000B104 AE510828 */  sw         $s1, 0x828($s2)
    /* DDBB74 0000B108 3C110000 */  lui        $s1, %hi(func_00000008 + 0x14)
    /* DDBB78 0000B10C 8E31001C */  lw         $s1, %lo(func_00000008 + 0x14)($s1)
    /* DDBB7C 0000B110 AE510830 */  sw         $s1, 0x830($s2)
    /* DDBB80 0000B114 3C110000 */  lui        $s1, %hi(func_00000000 + 0x4)
    /* DDBB84 0000B118 8E310004 */  lw         $s1, %lo(func_00000000 + 0x4)($s1)
    /* DDBB88 0000B11C AE51082C */  sw         $s1, 0x82C($s2)
    /* DDBB8C 0000B120 3C110000 */  lui        $s1, %hi(func_00000008 + 0x10)
    /* DDBB90 0000B124 8E310018 */  lw         $s1, %lo(func_00000008 + 0x10)($s1)
    /* DDBB94 0000B128 AE510834 */  sw         $s1, 0x834($s2)
    /* DDBB98 0000B12C 3C110000 */  lui        $s1, %hi(func_00000044 + 0xC)
    /* DDBB9C 0000B130 8E310050 */  lw         $s1, %lo(func_00000044 + 0xC)($s1)
    /* DDBBA0 0000B134 AE510838 */  sw         $s1, 0x838($s2)
    /* DDBBA4 0000B138 8E100070 */  lw         $s0, %lo(func_00000044 + 0x2C)($s0)
    /* DDBBA8 0000B13C AE500844 */  sw         $s0, 0x844($s2)
    /* DDBBAC 0000B140 3C100000 */  lui        $s0, %hi(func_00000080 + 0x4)
    /* DDBBB0 0000B144 8E100084 */  lw         $s0, %lo(func_00000080 + 0x4)($s0)
    /* DDBBB4 0000B148 AE500860 */  sw         $s0, 0x860($s2)
    /* DDBBB8 0000B14C 8F180074 */  lw         $t8, %lo(func_00000044 + 0x30)($t8)
    /* DDBBBC 0000B150 3C100000 */  lui        $s0, %hi(func_00000044 + 0x34)
    /* DDBBC0 0000B154 AE580854 */  sw         $t8, 0x854($s2)
    /* DDBBC4 0000B158 8E100078 */  lw         $s0, %lo(func_00000044 + 0x34)($s0)
    /* DDBBC8 0000B15C AE50085C */  sw         $s0, 0x85C($s2)
    /* DDBBCC 0000B160 3C100000 */  lui        $s0, %hi(func_00000044 + 0x38)
    /* DDBBD0 0000B164 8E10007C */  lw         $s0, %lo(func_00000044 + 0x38)($s0)
    /* DDBBD4 0000B168 AE500858 */  sw         $s0, 0x858($s2)
    /* DDBBD8 0000B16C 3C100000 */  lui        $s0, %hi(func_00000080)
    /* DDBBDC 0000B170 8E100080 */  lw         $s0, %lo(func_00000080)($s0)
    /* DDBBE0 0000B174 AE500864 */  sw         $s0, 0x864($s2)
    /* DDBBE4 0000B178 3C100000 */  lui        $s0, %hi(func_00000044 + 0x14)
    /* DDBBE8 0000B17C 8E100058 */  lw         $s0, %lo(func_00000044 + 0x14)($s0)
    /* DDBBEC 0000B180 AE500874 */  sw         $s0, 0x874($s2)
    /* DDBBF0 0000B184 0C000000 */  jal        func_00000000
    /* DDBBF4 0000B188 8CC60068 */   lw        $a2, %lo(func_00000044 + 0x24)($a2)
    /* DDBBF8 0000B18C AE420804 */  sw         $v0, 0x804($s2)
    /* DDBBFC 0000B190 0C000000 */  jal        func_00000000
    /* DDBC00 0000B194 02402025 */   or        $a0, $s2, $zero
  .L0000B198:
    /* DDBC04 0000B198 8FBF0034 */  lw         $ra, 0x34($sp)
    /* DDBC08 0000B19C 02401025 */  or         $v0, $s2, $zero
    /* DDBC0C 0000B1A0 8FB20030 */  lw         $s2, 0x30($sp)
    /* DDBC10 0000B1A4 8FB00028 */  lw         $s0, 0x28($sp)
    /* DDBC14 0000B1A8 8FB1002C */  lw         $s1, 0x2C($sp)
    /* DDBC18 0000B1AC 03E00008 */  jr         $ra
    /* DDBC1C 0000B1B0 27BD0178 */   addiu     $sp, $sp, 0x178
endlabel func_000090CC
