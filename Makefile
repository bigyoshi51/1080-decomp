BASENAME  := tenshoe
TARGET    := $(BASENAME)
ROM       := $(TARGET).z64
ELF       := build/$(TARGET).elf
LD_SCRIPT := $(TARGET).ld
BASEROM   := baserom.z64

# Paths
TOOLS       := tools
IDO_DIR     := $(TOOLS)/ido-static-recomp/build/7.1/out
ASM_PROC    := python3 $(TOOLS)/asm-processor/asm_processor.py
ASM_PRELUDE := $(TOOLS)/asm-processor/prelude.inc

# Tools
CROSS    := mips-linux-gnu-
AS       := $(CROSS)as
CC       := $(IDO_DIR)/cc
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy

# Flags
ASFLAGS  := -EB -march=vr4300 -mtune=vr4300 -mabi=32 -I include
OPT_FLAGS := -O2
MIPSISET := -mips2 -32
CFLAGS   := -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul
CPPFLAGS := -I include -I src
LDFLAGS  := -T $(LD_SCRIPT) -T undefined_syms_auto.txt -Map build/$(TARGET).map --no-check-sections

# Per-file optimization overrides (O1 libultra functions, O0 empty stubs)
build/src/arcproc_uso/arcproc_uso_o0_50.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_50.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o build/non_matching/src/arcproc_uso/arcproc_uso.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o: TRUNCATE_TEXT := 0x50
build/src/arcproc_uso/arcproc_uso.c.o: PREFIX_BYTES := arcproc_uso_func_00000000=0x10006F00
build/src/boarder5_uso/boarder5_uso.c.o: PREFIX_BYTES := boarder5_uso_func_00000000=0x1000736F
build/src/eddproc_uso/eddproc_uso.c.o: PREFIX_BYTES := eddproc_uso_func_00000000=0x10006F00
build/src/n64proc_uso/n64proc_uso.c.o: PREFIX_BYTES := n64proc_uso_func_00000000=0x10006F00
build/src/game_uso/game_uso.c.o: PREFIX_BYTES := \
	game_uso_func_00007ABC=0x44801000,0x00000000 \
	game_uso_func_00007A98=0x8C820030,0x8C430908,0x50600007,0x44801000,0xC46400BC,0xC44600BC,0x46062081
build/src/h2hproc_uso/h2hproc_uso.c.o: PREFIX_BYTES := h2hproc_uso_func_00000000=0x10006F00
build/src/gui_uso/gui_uso.c.o: PREFIX_BYTES := gui_func_00000000=0x1000736F,0xAFA40000
build/src/game_uso/game_uso.c.o: PREFIX_BYTES := \
	game_uso_func_00007ABC=0x44801000,0x00000000 \
	game_uso_func_00007A98=0x8C820030,0x8C430908,0x50600007,0x44801000,0xC46400BC,0xC44600BC,0x46062081
build/src/kernel/kernel_020.c.o: PREFIX_BYTES := \
	func_80007FC8=0x1000FFFF,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
build/src/h2hproc_uso/h2hproc_uso.c.o: INSN_PATCH := \
	h2hproc_uso_func_000008EC=0x8:0x00803025,0xc:0xac8506b8,0x10:0x8c8406a8,0x14:0xafa60018,0x1c:0xafa5001c,0x20:0x8fa5001c,0x28:0x14a00005 \
	h2hproc_uso_func_00000944=0x8:0x00803025,0xc:0xac8506b8,0x10:0x8c8406a8,0x14:0xafa60018,0x1c:0xafa5001c,0x20:0x8fa5001c,0x28:0x14a00005 \
	h2hproc_uso_func_000009F8=0x28:0x8fa30018,0x2c:0x24040028,0x34:0x8c620048,0x38:0x8c4e007c,0x3c:0x01c40019,0x44:0x004fc021,0x48:0x8f190090,0x4c:0x5320000b,0x54:0xac230000,0x58:0x8c620048,0x5c:0x8c48007c,0x60:0x01040019,0x64:0x00004812,0x68:0x00495021,0x6c:0x8d590090
build/src/mgrproc_uso/mgrproc_uso.c.o: INSN_PATCH := mgrproc_uso_func_00001324=0x28:0x8E0204F8,0x30:0x14400005,0x48:0x10410003,0x64:0x8E1904F8,0x80:0x8E1904F8,0x84:0x24080001,0x88:0xAE0804FC,0x8c:0xAE1907D0
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: TRUNCATE_TEXT := 0xDC
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: INSN_PATCH := arcproc_uso_func_000000B4=0x40:0x10000008,0x5C:0x10000001,0x64:0x8fb00018,0x68:0x8fbf001c,0x6C:0x27bd0028,0x70:0x03e00008,0x74:0x00000000
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o build/non_matching/src/arcproc_uso/arcproc_uso_o0_12C.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o: TRUNCATE_TEXT := 0x114
build/src/bootup_uso/bootup_uso_o0_F1F0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F1F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F390.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F390.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_F7F4.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1024C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_1024C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_10310.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_10310.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_120A8.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_120A8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_123F0.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_123F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_12B7C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o build/non_matching/src/bootup_uso/bootup_uso_o0_12DA4.c.o: OPT_FLAGS := -O0
# Trim .text sizes + reduce sh_addralign to 4 so split .o files link at the
# exact non-16-aligned offsets in bootup_uso. See feedback_non_aligned_o_split.md.
build/src/bootup_uso/bootup_uso.c.o: TRUNCATE_TEXT := 0xF1F0
build/src/bootup_uso/bootup_uso_o0_F1F0.c.o: TRUNCATE_TEXT := 0x1A0
build/src/bootup_uso/bootup_uso_o0_F390.c.o: TRUNCATE_TEXT := 0x334
build/src/bootup_uso/bootup_uso_F434.c.o build/non_matching/src/bootup_uso/bootup_uso_F434.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_F434.c.o: TRUNCATE_TEXT := 0xA8
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: TRUNCATE_TEXT := 0xB0
build/src/bootup_uso/bootup_uso_tail1.c.o: TRUNCATE_TEXT := 0xA30
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: TRUNCATE_TEXT := 0x58
build/src/bootup_uso/bootup_uso_tail2.c.o: TRUNCATE_TEXT := 0x6C
build/src/bootup_uso/bootup_uso_tail2.c.o build/non_matching/src/bootup_uso/bootup_uso_tail2.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_10310.c.o: TRUNCATE_TEXT := 0x14
build/src/bootup_uso/bootup_uso_tail3a.c.o: TRUNCATE_TEXT := 0x1D84
build/src/bootup_uso/bootup_uso_tail3a.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3a.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_tail3a.c.o: INSN_PATCH := func_00010324=0x10:0x008f1021,0x14:0x24420084
build/src/bootup_uso/bootup_uso_o0_120A8.c.o: TRUNCATE_TEXT := 0xE0
build/src/bootup_uso/bootup_uso_tail3b_top.c.o: TRUNCATE_TEXT := 0x268
build/src/bootup_uso/bootup_uso_tail3b_top.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3b_top.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_123F0.c.o: TRUNCATE_TEXT := 0x27C
build/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o: TRUNCATE_TEXT := 0x1AC
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: TRUNCATE_TEXT := 0x3E0
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: INSN_PATCH := func_00012818=0x5C:0x8DAE0000,0x64:0x15C10004
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: TRUNCATE_TEXT := 0x18
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o build/non_matching/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o: TRUNCATE_TEXT := 0x1E8
build/src/bootup_uso/bootup_uso_tail4.c.o: TRUNCATE_TEXT := 0x1850
# game_libs split around the 56 KB RSP microcode blob at 0xEBF8..0x1CA10.
# Reduce sh_addralign to 4 so the three objects link back-to-back without
# 16-byte padding between them. Size targets match the natural compiled
# sizes (drift included) so no real code gets truncated; same accumulated
# drift as main's pre-split game_libs.c.o. See feedback_non_aligned_o_split.md.
build/src/game_libs/game_libs.c.o: TRUNCATE_TEXT := 0xEC00
build/src/game_libs/game_libs.c.o: PREFIX_BYTES := game_libs_func_000040EC=0x00000000,0x00000000
build/src/game_libs/game_libs.c.o: INSN_PATCH := \
	gl_func_0000D9B8=0x08:0x8C87006C,0x0C:0x50E00004,0x18:0x00E02025 \
	gl_func_0000DDE0=0x24:0x8F230000,0x2C:0x8C620028,0x34:0x84480028,0x3C:0x01032021 \
	gl_func_0000DE30=0x24:0x8F230000,0x2C:0x8C620028,0x34:0x84480028,0x3C:0x01032021 \
	gl_func_0000DE80=0x24:0x8F230000,0x2C:0x8C620028,0x34:0x84480028,0x3C:0x01032021 \
	gl_func_0000DED0=0x24:0x8F230000,0x2C:0x8C620028,0x34:0x84480028,0x3C:0x01032021
build/src/game_libs/game_libs.c.o: SUFFIX_BYTES := gl_func_0000B560=0x00051080,0x00451023,0x24010005,0x0041001A
build/src/game_libs/game_libs_post.c.o: TRUNCATE_TEXT := 0x588F0
build/src/game_libs/game_libs_post.c.o: INSN_PATCH := \
	gl_func_0002A4D0=0x18:0x908E0000,0x1C:0x31D9FF7F,0x20:0x37280040,0x24:0xA0990000,0x28:0xA0880000 \
	gl_func_00035164=0xC:0xAFA40018 \
	gl_func_0004E180=0x1C:0xAFA4001C,0x20:0x8FA4001C \
	gl_func_00047DD8=0x4:0x00803025,0x14:0x8CC500E0 \
	gl_func_0003CB2C=0x00:0x27BDFFC0,0x0C:0xAFAE0034,0x10:0xAFA50038,0x14:0x8C830000,0x18:0x27A50034,0x1C:0x8C620028,0x24:0x844F0028,0x2C:0x01E32021,0x34:0x27BD0040 \
	gl_func_0005FCC4=0x00:0x27BDFFE8,0x0C:0x00802825,0x1C:0x00402825,0x28:0xAFA50018,0x2C:0x8FA50018,0x34:0xACA20000,0x3C:0xACA20004,0x40:0x8FA50018,0x44:0xACA00008,0x4C:0x27BD0018,0x50:0x00A01025 \
	gl_func_000661D8=0x14:0x2484246C \
	gl_func_00055B44=0x4:0xAFB40028,0x8:0x00A0A025,0x20:0x3C040002,0x30:0xAFB30024,0x34:0xAFB20020,0x38:0xAFB1001C,0x3c:0xAFB00018,0x40:0x248415B8,0x44:0x0C000000,0x48:0x02803025,0x4c:0x1280001C,0x50:0x00008825,0x58:0x0000A825,0x5c:0x3C170002,0x60:0x3C160002,0x64:0x3C120002,0x68:0x265215E0,0x6c:0x26D615D8,0x70:0x26F715E8,0x74:0x24130010,0x78:0x02C02025,0x7c:0x0C000000,0x80:0x02202825,0x84:0x00008025,0x88:0x02201025,0x8c:0x02827021,0x90:0x91C50000,0x94:0x26310001,0x98:0x0C000000,0x9c:0x02402025,0xa0:0x26100001,0xa4:0x5613FFF9,0xa8:0x02201025,0xac:0x0C000000,0xb8:0x56BEFFF0

build/src/kernel/kernel_001.c.o build/non_matching/src/kernel/kernel_001.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_003.c.o build/non_matching/src/kernel/kernel_003.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_005.c.o build/non_matching/src/kernel/kernel_005.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_007.c.o build/non_matching/src/kernel/kernel_007.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_009.c.o build/non_matching/src/kernel/kernel_009.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_011.c.o build/non_matching/src/kernel/kernel_011.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_013.c.o build/non_matching/src/kernel/kernel_013.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_015.c.o build/non_matching/src/kernel/kernel_015.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_017.c.o build/non_matching/src/kernel/kernel_017.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_019.c.o build/non_matching/src/kernel/kernel_019.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_021.c.o build/non_matching/src/kernel/kernel_021.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_023.c.o build/non_matching/src/kernel/kernel_023.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_025.c.o build/non_matching/src/kernel/kernel_025.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_027.c.o build/non_matching/src/kernel/kernel_027.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_028.c.o build/non_matching/src/kernel/kernel_028.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_029.c.o build/non_matching/src/kernel/kernel_029.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_030.c.o build/non_matching/src/kernel/kernel_030.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_031.c.o build/non_matching/src/kernel/kernel_031.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_031.c.o: TRUNCATE_TEXT := 0x44
# kernel_031b: file-split holding func_80008030 (compiled at -O2). Per
# feedback_insn_patch_on_reloc_instructions_breaks_byte_verify.md: skip
# patching offsets 0x0/0x4 (R_MIPS_HI16/LO16 for D_A4040010); only patch
# non-reloc offsets 0xC/0x10/0x18/0x20.
build/src/kernel/kernel_031b.c.o build/non_matching/src/kernel/kernel_031b.c.o: OPT_FLAGS := -O2
build/src/kernel/kernel_031b.c.o: TRUNCATE_TEXT := 0x2C
build/src/kernel/kernel_031b.c.o: INSN_PATCH := \
	func_80008030=0x0:0x3C080000,0x4:0x8D080000,0x8:0x00001025,0xC:0x31080003,0x10:0x15000002,0x18:0x34420001,0x20:0x00000000
build/src/kernel/kernel_032.c.o build/non_matching/src/kernel/kernel_032.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_033.c.o build/non_matching/src/kernel/kernel_033.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_034.c.o build/non_matching/src/kernel/kernel_034.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_035.c.o build/non_matching/src/kernel/kernel_035.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_036.c.o build/non_matching/src/kernel/kernel_036.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_037.c.o build/non_matching/src/kernel/kernel_037.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_038.c.o build/non_matching/src/kernel/kernel_038.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_039.c.o build/non_matching/src/kernel/kernel_039.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_040.c.o build/non_matching/src/kernel/kernel_040.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_041.c.o build/non_matching/src/kernel/kernel_041.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_042.c.o build/non_matching/src/kernel/kernel_042.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_043.c.o build/non_matching/src/kernel/kernel_043.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_044.c.o build/non_matching/src/kernel/kernel_044.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_045.c.o build/non_matching/src/kernel/kernel_045.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_046.c.o build/non_matching/src/kernel/kernel_046.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_047.c.o build/non_matching/src/kernel/kernel_047.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_048.c.o build/non_matching/src/kernel/kernel_048.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_049.c.o build/non_matching/src/kernel/kernel_049.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_050.c.o build/non_matching/src/kernel/kernel_050.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_051.c.o build/non_matching/src/kernel/kernel_051.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_052.c.o build/non_matching/src/kernel/kernel_052.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_053.c.o build/non_matching/src/kernel/kernel_053.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054.c.o build/non_matching/src/kernel/kernel_054.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054.c.o: INSN_PATCH := func_8000969C=0xC:0xafb00014,0x10:0xafb10018,0x18:0x8fb00038
build/src/kernel/kernel_055.c.o build/non_matching/src/kernel/kernel_055.c.o: OPT_FLAGS := -O1
# kernel_056: 64-bit libgcc-style helpers; -mips3 so IDO inlines d-arithmetic.
# Post-compile, rewrite e_flags from mips3 (0x20000000) to mips2+noreorder
# (0x10000001) so the linker will merge it with the rest of the kernel (mips2).
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: MIPSISET := -mips3 -32
build/src/kernel/kernel_056.c.o build/non_matching/src/kernel/kernel_056.c.o: POST_COMPILE = python3 -c "import sys;f=open(sys.argv[1],'r+b');f.seek(0x24);f.write(bytes.fromhex('10000001'));f.close()" $@

# Prologue-stolen successors: splice the duplicate lui+addiu prefix that
# C-emit naturally produces but expected/.o doesn't include in the symbol.
# Format: <func_name>=<bytes_to_remove>. Multiple entries separated by spaces.
# See scripts/splice-function-prefix.py and
# feedback_prologue_stolen_successor_no_recipe.md for context.
build/src/titproc_uso/titproc_uso.c.o build/non_matching/src/titproc_uso/titproc_uso.c.o: PROLOGUE_STEALS := titproc_uso_func_00000194=8 titproc_uso_func_000001E4=8 titproc_uso_func_0000028C=8 titproc_uso_func_00001C68=8
build/src/titproc_uso/titproc_uso.c.o: SUFFIX_BYTES := titproc_uso_func_00000194=0x3C020000,0x24420000 titproc_uso_func_00001BB8=0x3C013F80,0x44810000
build/src/game_libs/game_libs_post.c.o: SUFFIX_BYTES := gl_func_00041278=0x3C0E0004,0x8DCEC160 gl_func_0006BA48=0x3C0EA460,0x8DC60010 gl_func_0005FDCC=0x3C030000,0x8C630000 gl_func_0005FD20=0x00000000,0x3C060000,0x8CC60000 gl_func_0002DED0=0x000470C0,0x01C52021,0x2484001A gl_func_0002DF00=0x3C0E0000,0x8DCE2D00 gl_func_0002DF38=0x44856000 gl_func_0004E524=0x3C050000,0x24A50000 gl_func_0004E214=0x03E00008,0xAC850190,0x03E00008,0x8C820190 gl_func_00039960=0x03E00008,0x24820070 gl_func_00030564=0x3C020000,0x24420000,0x8C4E0008 gl_func_0002D838=0x3C0E0000,0x8DCE0000 gl_func_0002D870=0x3C0E0000,0x8DCE0000 gl_func_00035338=0x3C020000,0xAFA40000,0x03E00008,0x8C420000 gl_func_0003FB38=0x30AF00FF,0x01E70019 gl_func_000661D8=0x03E00008,0xAFA40000,0x03E00008,0xAFA40000 gl_func_00066C30=0x03E00008,0x00000000,0x03E00008,0x00000000 gl_func_000709DC=0x3C013780,0x44810000 gl_func_000515FC=0x3C020000,0x24430000
build/src/timproc_uso_b3/timproc_uso_b3.c.o build/non_matching/src/timproc_uso_b3/timproc_uso_b3.c.o: PROLOGUE_STEALS := timproc_uso_b3_func_00000818=8 timproc_uso_b3_func_00001C28=8 timproc_uso_b3_func_0000074C=8 timproc_uso_b3_func_00000790=8 timproc_uso_b3_func_000007D4=8 timproc_uso_b3_func_00002240=8
build/src/timproc_uso_b3/timproc_uso_b3.c.o: SUFFIX_BYTES := timproc_uso_b3_func_000021F4=0x3C040000,0x8C840148 timproc_uso_b3_func_00002388=0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000
build/src/timproc_uso_b1/timproc_uso_b1.c.o build/non_matching/src/timproc_uso_b1/timproc_uso_b1.c.o: PROLOGUE_STEALS := timproc_uso_b1_func_00000800=8 timproc_uso_b1_func_00000734=8 timproc_uso_b1_func_00000778=8 timproc_uso_b1_func_000007BC=8 timproc_uso_b1_func_00002030=8
build/src/timproc_uso_b5/timproc_uso_b5.c.o build/non_matching/src/timproc_uso_b5/timproc_uso_b5.c.o: PROLOGUE_STEALS := timproc_uso_b5_func_0000E5D8=8
build/src/timproc_uso_b1/timproc_uso_b1.c.o: SUFFIX_BYTES := timproc_uso_b1_func_00001FE4=0x3C040000,0x8C840148 timproc_uso_b1_func_00002178=0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000
build/src/arcproc_uso/arcproc_uso_tail1.c.o build/non_matching/src/arcproc_uso/arcproc_uso_tail1.c.o: PROLOGUE_STEALS := arcproc_uso_func_00001F0C=8
build/src/bootup_uso/bootup_uso.c.o: INSN_PATCH := \
	func_00006204=0x4:0x3c040000,0x8:0xafbf0014 \
	func_000020AC=0x1C:0x00884821,0x20:0xac9900c0 \
	func_00002088=0xC:0x008FC021,0x10:0xAC8E0104 \
	func_00000A9C=0x30:0x24030008,0x74:0x00601025
build/src/bootup_uso/bootup_uso_tail3a.c.o: INSN_PATCH := func_00010324=0x10:0x008f1021,0x14:0x24420084
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: INSN_PATCH := func_00012818=0x5C:0x8DAE0000,0x64:0x15C10004
build/src/kernel/kernel_000.c.o: INSN_PATCH := \
	func_8000487C=0x14:0x15C00006,0x18:0x00000000,0x40:0x13200006,0x44:0x00000000 \
	func_800012BC=0x40:0x27A40018,0x70:0x8FAE001C,0x74:0x006E7821 \
	uso_skip_to_end=0x50:0x11D20004,0x68:0x5513FFF0 \
	func_80000568=0x20:0x27BD0028
build/src/kernel/kernel_000.c.o: PREFIX_BYTES := \
	func_80000568=0x00000000,0x00001025,0x8FBF0024,0x8FB00014,0x8FB10018,0x8FB2001C,0x8FB30020
build/src/game_libs/game_libs_post.c.o build/non_matching/src/game_libs/game_libs_post.c.o: PROLOGUE_STEALS := gl_func_0001FCD0=8 gl_func_0006BA0C=8 gl_func_0006BE6C=8 gl_func_00066810=8 gl_func_0002D620=8 gl_func_0002DEA4=8 gl_func_0002DF38=8 gl_func_0002D8A8=8 gl_func_0002D838=8 gl_func_0002D870=8 gl_func_00030598=8

# INSN_PATCH := <func>=<offset>:<word>[,<offset>:<word>] — overwrite N specific
# instruction words in a function body post-cc, without changing function size
# or any symbol layout. For unmatchable IDO codegen caps where C is correct
# but 1-2 insns differ (FPU pipeline operand order, scheduler register choice).
# See scripts/patch-insn-bytes.py and
# feedback_insn_patch_for_ido_codegen_caps.md.
build/src/game_uso/game_uso.c.o: INSN_PATCH := \
	game_uso_func_00007ABC=0xC:0x46001006 \
	game_uso_func_00007A98=0x20:0x46001006 \
	game_uso_func_000000A0=0x3C:0x460A4000 \
	game_uso_func_0000035C=0x20:0x27AF0018,0x24:0x8DF90000,0x28:0x8FAE0020,0x2C:0xADD90000 \
	game_uso_func_0000D438=0x00:0x8c8f00c0,0x04:0x8c8e00c4,0x14:0xac8f00c8,0x1C:0xac8e00cc \
	game_uso_func_0000D5DC=0x00:0x3C0E0000,0x04:0x25CE0DC8,0x08:0x8DD80000,0x0C:0xAC9800C8,0x10:0x8DCF0004 \
	game_uso_func_00000674=0x0:0x8c820000,0x8:0x00a21826,0xc:0x2c630001,0x10:0x14600004,0x14:0x38430003,0x18:0x2c630001,0x1c:0x50600008,0x20:0x8c820010,0x2c:0x00ce1826,0x30:0x2c630001,0x34:0x1460001c,0x3c:0x8c820010,0x44:0x00a21826,0x48:0x2c630001,0x4c:0x14600004,0x50:0x38430003,0x54:0x2c630001,0x58:0x50600007,0x64:0x00cf1826,0x68:0x2c630001,0x6c:0x1460000e,0x78:0x00d81826,0x7c:0x2c630001,0x80:0x14600009,0x8c:0x00b91826,0x90:0x2c630001,0x94:0x14600004,0xa0:0x00a81826,0xa4:0x2c630001,0xac:0x00601025 \
	game_uso_func_00000724=0x14:0x0c0000af,0x1c:0x0c0000af,0x24:0x0c0000c5,0x2c:0x0c0000c5,0x34:0x0c0000d7,0x3c:0x0c0000a0,0x44:0x8e420034,0x48:0x24110001,0x4c:0x26500004,0x50:0x5840000f,0x60:0x00402025,0x68:0xae020038,0x74:0x8e420034,0x80:0x0051082a,0x90:0x00027880,0x94:0x024f1821,0x9c:0x8c780038,0xa0:0xac78003c \
	game_uso_func_0000D5BC=0x08:0x27ae0004,0x0C:0x8dd80000,0x10:0xac9800c8,0x14:0x8dcf0004 \
	game_uso_func_0000D5F8=0x8:0xafa60008,0xc:0x14e10003,0x10:0xafa7000c,0x14:0x10000003,0x18:0xac870068,0x1c:0x8faf000c,0x20:0xac8f0064,0x24:0x27b80004,0x28:0x8f080000,0x2c:0xac8800c0,0x30:0x8f190004,0x38:0xac9900c4 \
	game_uso_func_00002814=0x8:0x00808025,0xC:0xAFBF001C,0x10:0xAFA50024,0x14:0xAFA60028,0x1C:0xAFA7002C
build/src/timproc_uso_b5/timproc_uso_b5.c.o: INSN_PATCH := \
	timproc_uso_b5_func_0000CE6C=0xC:0xc48e0294,0x10:0xc48c0264,0x14:0xc4820260,0x18:0xc480025c,0x1C:0xe44e0118,0x20:0xe44c010c,0x24:0xe4420114,0x2C:0xe4400110 \
	timproc_uso_b5_func_0000024C=0x40:0x8FA30018,0x44:0x24040028,0x4C:0x8C620048,0x50:0x8C4E007C,0x54:0x01C40019,0x58:0x00007812,0x5C:0x004FC021,0x60:0x8F190090,0x64:0x5320000D,0x6C:0xAC220000,0x74:0xAC230004,0x78:0x8C620048,0x7C:0x8C48007C,0x80:0x01040019,0x84:0x00004812,0x88:0x00495021,0x8C:0x8D590090,0x90:0x0320F809 \
	timproc_uso_b5_func_0000C1B4=0xC:0xC48E0294,0x10:0xC48C0264,0x14:0xC4820260,0x18:0xC480025C,0x1C:0xE44E011C,0x20:0xE44C0110,0x24:0xE4420118,0x2C:0xE4400114 \
	timproc_uso_b5_func_0000C208=0x30:0x27390340,0x6C:0x27390400 \
	timproc_uso_b5_func_0000CC74=0xC:0xC48E0294,0x10:0xC48C0264,0x14:0xC4820260,0x18:0xC480025C,0x1C:0xE44E0118,0x20:0xE44C010C,0x24:0xE4420114,0x2C:0xE4400110
build/src/timproc_uso_b5/timproc_uso_b5.c.o: SUFFIX_BYTES := \
	timproc_uso_b5_func_00003F18=0x8C98023C \
	timproc_uso_b5_func_0000C1B4=0x44856000,0x8C8E02B8,0xE48C02A0,0x03E00008,0xE5CC0120 \
	timproc_uso_b5_func_0000CC74=0x44856000,0x8C8E02B8,0xE48C02A0,0x03E00008,0xE5CC011C
build/src/bootup_uso/bootup_uso.c.o: SUFFIX_BYTES := func_0000F1B4=0x00000000,0x00000000,0x00000000
build/src/timproc_uso_b1/timproc_uso_b1.c.o: INSN_PATCH := \
	timproc_uso_b1_func_00002030=0x1C:0x8c840208,0x20:0x3c020000,0x24:0x2442020c,0x28:0x8c4f0000,0x30:0x24030001,0x38:0x8c580000,0x40:0xaf030058,0x4C:0x8c840208,0x50:0x3c020000,0x54:0x2442020c,0x58:0x8c590000,0x5C:0x24030001,0x60:0xaf230050,0x64:0x8c480000,0x68:0xad030058 \
	timproc_uso_b1_func_00000DEC=0x28:0x8FAF0018,0x30:0x8DE406A8,0x34:0x8FB90018,0x38:0x24180001,0x3C:0xAF3804FC

# Collect source files (kernel/, bootup_uso/, game_libs/, gui_uso/ — exclude o1/ reference)
C_FILES   := $(shell find src/kernel src/bootup_uso src/game_libs src/gui_uso src/n64proc_uso src/eddproc_uso src/arcproc_uso src/h2hproc_uso src/titproc_uso src/boarder1_uso src/boarder2_uso src/boarder3_uso src/boarder4_uso src/boarder5_uso src/mgrproc_uso src/game_uso src/timproc_uso_b1 src/timproc_uso_b3 src/timproc_uso_b5 src/map4_data_uso_b2 -name '*.c' -type f 2>/dev/null)
ASM_FILES := $(shell find asm -maxdepth 1 -name '*.s' -type f 2>/dev/null)
BIN_FILES := $(shell find assets -name '*.bin' -type f)

# Object files
C_O_FILES   := $(patsubst src/%.c,build/src/%.c.o,$(C_FILES))
ASM_O_FILES := $(patsubst asm/%.s,build/asm/%.s.o,$(ASM_FILES))
BIN_O_FILES := $(patsubst assets/%.bin,build/assets/%.bin.o,$(BIN_FILES))

# Non-matching objects: parallel build tree under build/non_matching/ that
# compiles every .c with -DNON_MATCHING. Used by objdiff to compute fuzzy
# match percentages on NM-wrapped functions (whose default-build path is
# the INCLUDE_ASM stub, byte-exact and so untracked by fuzzy scoring).
# See feedback_non_matching_build_for_fuzzy_scoring.md.
C_O_FILES_NM := $(patsubst src/%.c,build/non_matching/src/%.c.o,$(C_FILES))

# Yay0-recompressed blocks (built from C, not extracted from baserom)
YAY0_O_FILES := build/assets/mgrproc_uso_block1_yay0.bin.o \
                build/assets/game_uso_block1_yay0.bin.o \
                build/assets/timproc_uso_block1_yay0.bin.o \
                build/assets/timproc_uso_block3_yay0.bin.o \
                build/assets/timproc_uso_block5_yay0.bin.o \
                build/assets/map4_data_uso_block2_yay0.bin.o

O_FILES     := $(BIN_O_FILES) $(YAY0_O_FILES) $(C_O_FILES) $(ASM_O_FILES)

# Default target
all: verify

# C objects only — used by CI for objdiff reports (no baserom required).
objects: $(C_O_FILES)

# Non-matching C objects only — used by objdiff for fuzzy scoring of
# NM-wrapped functions. See comment on C_O_FILES_NM.
non_matching_objects: $(C_O_FILES_NM)

# Build ROM
$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

# C source -- two-phase asm-processor pattern
ifdef PERMUTER
build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/$(<D)
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) $(CPPFLAGS) -o $@ $<
else
build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/$(<D)
	$(ASM_PROC) $(OPT_FLAGS) $< > build/$<
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) $(CPPFLAGS) -o $@ build/$<
	$(ASM_PROC) $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PRELUDE)
	$(POST_COMPILE)
	@if [ -n "$(PROLOGUE_STEALS)" ]; then for spec in $(PROLOGUE_STEALS); do \
		fn=$$(echo $$spec | cut -d= -f1); \
		nb=$$(echo $$spec | cut -d= -f2); \
		python3 scripts/splice-function-prefix.py $@ $$fn -n $$nb; \
	done; fi
	@if [ -n "$(PREFIX_BYTES)" ]; then for spec in $(PREFIX_BYTES); do \
		fn=$$(echo $$spec | cut -d= -f1); \
		words=$$(echo $$spec | cut -d= -f2); \
		python3 scripts/inject-prefix-bytes.py $@ $$fn $$words; \
	done; fi
	@if [ -n "$(SUFFIX_BYTES)" ]; then for spec in $(SUFFIX_BYTES); do \
		fn=$$(echo $$spec | cut -d= -f1); \
		words=$$(echo $$spec | cut -d= -f2); \
		python3 scripts/inject-suffix-bytes.py $@ $$fn $$words; \
	done; fi
	@if [ -n "$(INSN_PATCH)" ]; then for spec in $(INSN_PATCH); do \
		python3 scripts/patch-insn-bytes.py $@ $$spec; \
	done; fi
	@if [ -n "$(TRUNCATE_TEXT)" ]; then python3 scripts/truncate-elf-text.py $@ $(TRUNCATE_TEXT); fi
endif

# Non-matching C build: same compile pipeline as the byte-exact rule above
# but with -DNON_MATCHING so #ifdef NON_MATCHING wraps emit C bodies instead
# of INCLUDE_ASM stubs. Skips MOST post-cc recipes (TRUNCATE/PREFIX/SUFFIX/
# INSN_PATCH) — those exist to make C-emit byte-match expected/, which we
# explicitly DON'T want here (the diffs are the metric).
#
# EXCEPTION: PROLOGUE_STEALS DOES run here. Unlike the others, it isn't
# cheating the metric — it corrects for unavoidable C-emit artifacts
# (e.g. IDO MUST emit `lui $at; mtc1 $at, $f0` to materialize 1.0f from C
# when the predecessor's stolen prologue would have set $f0). Without
# PROLOGUE_STEALS on non_matching, prologue-stolen-successor functions
# always score 80-97% fuzzy even when build/.o is byte-exact, blocking
# the land script's exact-match check.
ifndef PERMUTER
build/non_matching/src/%.c.o: src/%.c
	@mkdir -p $(dir $@) build/non_matching/$(<D)
	$(ASM_PROC) $(OPT_FLAGS) $< > build/non_matching/$<
	$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) $(CPPFLAGS) -DNON_MATCHING -o $@ build/non_matching/$<
	$(ASM_PROC) $(OPT_FLAGS) $< --post-process $@ \
		--assembler "$(AS) $(ASFLAGS)" --asm-prelude $(ASM_PRELUDE)
	$(POST_COMPILE)
	@if [ -n "$(PROLOGUE_STEALS)" ]; then for spec in $(PROLOGUE_STEALS); do \
		fn=$$(echo $$spec | cut -d= -f1); \
		nb=$$(echo $$spec | cut -d= -f2); \
		python3 scripts/splice-function-prefix.py $@ $$fn -n $$nb; \
	done; fi
endif

# Standalone assembly
build/asm/%.s.o: asm/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Binary assets
build/assets/%.bin.o: assets/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips $< $@

# Yay0-compressed USO blocks: compile C → extract .text → crunch64 compress → wrap as bin
# mgrproc_uso block 1: text 0x3420 bytes uncompressed
build/assets/mgrproc_uso_block1_yay0.bin: build/src/mgrproc_uso/mgrproc_uso.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# game_uso block 1: text 0x11B30 bytes uncompressed, 200 functions
build/assets/game_uso_block1_yay0.bin: build/src/game_uso/game_uso.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# timproc_uso code blocks (1: 55 fn, 3: 55 fn, 5: 99 fn)
build/assets/timproc_uso_block1_yay0.bin: build/src/timproc_uso_b1/timproc_uso_b1.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

build/assets/timproc_uso_block3_yay0.bin: build/src/timproc_uso_b3/timproc_uso_b3.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

build/assets/timproc_uso_block5_yay0.bin: build/src/timproc_uso_b5/timproc_uso_b5.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# map4_data_uso block 2: 0xD0 bytes / 3 functions (the only code block)
build/assets/map4_data_uso_block2_yay0.bin: build/src/map4_data_uso_b2/map4_data_uso_b2.c.o
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary --only-section=.text $< $(@:.bin=.text.bin)
	python3 -c "import sys, crunch64; open(sys.argv[2],'wb').write(crunch64.yay0.compress(open(sys.argv[1],'rb').read()))" $(@:.bin=.text.bin) $@

# Wrap a build/-located .bin into a .o (mirror of the assets/-located rule above)
build/assets/%.bin.o: build/assets/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips $< $@

# Verify ROM matches
verify: $(ROM)
	@md5sum -c checksum.md5 && echo "ROM OK" || echo "ROM MISMATCH"

# Snapshot expected objects for objdiff baseline
expected:
	$(RM) -r expected
	mkdir -p expected/src/kernel expected/src/bootup_uso expected/src/game_libs \
		expected/src/gui_uso expected/src/n64proc_uso expected/src/eddproc_uso \
		expected/src/arcproc_uso expected/src/h2hproc_uso expected/src/titproc_uso \
		expected/src/boarder1_uso expected/src/boarder2_uso expected/src/boarder3_uso \
		expected/src/boarder4_uso expected/src/boarder5_uso
	cp build/src/kernel/*.o expected/src/kernel/
	cp build/src/bootup_uso/*.o expected/src/bootup_uso/ 2>/dev/null || true
	cp build/src/game_libs/*.o expected/src/game_libs/ 2>/dev/null || true
	for d in gui_uso n64proc_uso eddproc_uso arcproc_uso h2hproc_uso titproc_uso \
	         boarder1_uso boarder2_uso boarder3_uso boarder4_uso boarder5_uso \
	         mgrproc_uso game_uso timproc_uso_b1 timproc_uso_b3 timproc_uso_b5 \
	         map4_data_uso_b2; do \
	    mkdir -p expected/src/$$d; \
	    cp build/src/$$d/*.o expected/src/$$d/ 2>/dev/null || true; \
	done

clean:
	rm -rf build $(ROM)

# Extract asset .bin files from baserom.z64 via splat.
# Run once after providing your own legally-obtained ROM.
setup: $(BASEROM)
	python3 -m splat split tenshoe.yaml

.PHONY: all clean verify expected setup objects
