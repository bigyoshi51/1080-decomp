nonmatching mgrproc_uso_func_00001B58, 0x7C

glabel mgrproc_uso_func_00001B58
    /* 001B58 00001B58 27BDFFD8 */  .word 0x27BDFFD8
    /* 001B5C 00001B5C AFBF0014 */  .word 0xAFBF0014
    jal mgrproc_uso_func_01B0F8   /* 001B60 0C000000 -> mgrproc_uso_func_01B0F8 */
    /* 001B64 00001B64 AFA40028 */  .word 0xAFA40028
    lui $v0, %hi(import_800201CC)   /* 001B68 3C020000 -> import_800201CC */
    /* 001B6C 00001B6C 8C420134 */  .word 0x8C420134
    /* 001B70 00001B70 8FA40028 */  .word 0x8FA40028
    /* 001B74 00001B74 8C4300C4 */  .word 0x8C4300C4
    /* 001B78 00001B78 8C6E0800 */  .word 0x8C6E0800
    /* 001B7C 00001B7C AFAE0020 */  .word 0xAFAE0020
    /* 001B80 00001B80 8C4500CC */  .word 0x8C4500CC
    /* 001B84 00001B84 8CAF0800 */  .word 0x8CAF0800
    jal mgrproc_uso_func_01CCD4   /* 001B88 0C000000 -> mgrproc_uso_func_01CCD4 */
    /* 001B8C 00001B8C AFAF0018 */  .word 0xAFAF0018
    /* 001B90 00001B90 8FA40020 */  .word 0x8FA40020
    jal mgrproc_uso_func_07BA68   /* 001B94 0C000000 -> mgrproc_uso_func_07BA68 */
    /* 001B98 00001B98 00002825 */  .word 0x00002825
    /* 001B9C 00001B9C 8FA40018 */  .word 0x8FA40018
    jal mgrproc_uso_func_07BA68   /* 001BA0 0C000000 -> mgrproc_uso_func_07BA68 */
    /* 001BA4 00001BA4 00002825 */  .word 0x00002825
    lui $a0, %hi(import_800201D0)   /* 001BA8 3C040000 -> import_800201D0 */
    /* 001BAC 00001BAC 8C840138 */  .word 0x8C840138
    /* 001BB0 00001BB0 00002825 */  .word 0x00002825
    jal import_000B7FF0   /* 001BB4 0C000000 -> import_000B7FF0 */
    /* 001BB8 00001BB8 00003025 */  .word 0x00003025
    /* 001BBC 00001BBC 8FB80028 */  .word 0x8FB80028
    /* 001BC0 00001BC0 AF0004F4 */  .word 0xAF0004F4
    /* 001BC4 00001BC4 8FBF0014 */  .word 0x8FBF0014
    /* 001BC8 00001BC8 27BD0028 */  .word 0x27BD0028
    /* 001BCC 00001BCC 03E00008 */  .word 0x03E00008
    /* 001BD0 00001BD0 00000000 */  .word 0x00000000
endlabel mgrproc_uso_func_00001B58
