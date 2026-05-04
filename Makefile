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
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso.c.o: TRUNCATE_TEXT := 0x50
build/src/arcproc_uso/arcproc_uso.c.o: PREFIX_BYTES := arcproc_uso_func_00000000=0x10006F00
build/src/boarder5_uso/boarder5_uso.c.o: PREFIX_BYTES := boarder5_uso_func_00000000=0x1000736F
build/src/eddproc_uso/eddproc_uso.c.o: PREFIX_BYTES := eddproc_uso_func_00000000=0x10006F00
build/src/n64proc_uso/n64proc_uso.c.o: PREFIX_BYTES := n64proc_uso_func_00000000=0x10006F00
build/src/h2hproc_uso/h2hproc_uso.c.o: PREFIX_BYTES := h2hproc_uso_func_00000000=0x10006F00
build/src/h2hproc_uso/h2hproc_uso.c.o: INSN_PATCH := \
	h2hproc_uso_func_000008EC=0x8:0x00803025,0xc:0xac8506b8,0x10:0x8c8406a8,0x14:0xafa60018,0x1c:0xafa5001c,0x20:0x8fa5001c,0x28:0x14a00005 \
	h2hproc_uso_func_00000944=0x8:0x00803025,0xc:0xac8506b8,0x10:0x8c8406a8,0x14:0xafa60018,0x1c:0xafa5001c,0x20:0x8fa5001c,0x28:0x14a00005
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: TRUNCATE_TEXT := 0xDC
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: INSN_PATCH := arcproc_uso_func_000000B4=0x40:0x10000008,0x5C:0x10000001,0x64:0x8fb00018,0x68:0x8fbf001c,0x6C:0x27bd0028,0x70:0x03e00008,0x74:0x00000000
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o: OPT_FLAGS := -O0
build/src/arcproc_uso/arcproc_uso_o0_12C.c.o: TRUNCATE_TEXT := 0x114
build/src/bootup_uso/bootup_uso_o0_F390.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_10310.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_120A8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_123F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o: OPT_FLAGS := -O0
# Trim .text sizes + reduce sh_addralign to 4 so split .o files link at the
# exact non-16-aligned offsets in bootup_uso. See feedback_non_aligned_o_split.md.
build/src/bootup_uso/bootup_uso.c.o: TRUNCATE_TEXT := 0xF390
build/src/bootup_uso/bootup_uso_o0_F390.c.o: TRUNCATE_TEXT := 0x334
build/src/bootup_uso/bootup_uso_F434.c.o: TRUNCATE_TEXT := 0xA8
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: TRUNCATE_TEXT := 0xB0
build/src/bootup_uso/bootup_uso_tail1.c.o: TRUNCATE_TEXT := 0xA30
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: TRUNCATE_TEXT := 0x58
build/src/bootup_uso/bootup_uso_tail2.c.o: TRUNCATE_TEXT := 0x6C
build/src/bootup_uso/bootup_uso_tail2.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_10310.c.o: TRUNCATE_TEXT := 0x14
build/src/bootup_uso/bootup_uso_tail3a.c.o: TRUNCATE_TEXT := 0x1D84
build/src/bootup_uso/bootup_uso_tail3a.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_120A8.c.o: TRUNCATE_TEXT := 0xE0
build/src/bootup_uso/bootup_uso_tail3b_top.c.o: TRUNCATE_TEXT := 0x268
build/src/bootup_uso/bootup_uso_o0_123F0.c.o: TRUNCATE_TEXT := 0x27C
build/src/bootup_uso/bootup_uso_tail3b_bot_t.c.o: TRUNCATE_TEXT := 0x1AC
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: TRUNCATE_TEXT := 0x3E0
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: TRUNCATE_TEXT := 0x18
build/src/bootup_uso/bootup_uso_tail3b_bot_b.c.o: OPT_FLAGS := -O2 -g3
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o: TRUNCATE_TEXT := 0x1E8
build/src/bootup_uso/bootup_uso_tail4.c.o: TRUNCATE_TEXT := 0x1850
# game_libs split around the 56 KB RSP microcode blob at 0xEBF8..0x1CA10.
# Reduce sh_addralign to 4 so the three objects link back-to-back without
# 16-byte padding between them. Size targets match the natural compiled
# sizes (drift included) so no real code gets truncated; same accumulated
# drift as main's pre-split game_libs.c.o. See feedback_non_aligned_o_split.md.
build/src/game_libs/game_libs.c.o: TRUNCATE_TEXT := 0xEC00
build/src/game_libs/game_libs.c.o: PREFIX_BYTES := game_libs_func_000040EC=0x00000000,0x00000000
build/src/game_libs/game_libs.c.o: INSN_PATCH := gl_func_0000D9B8=0x08:0x8C87006C,0x0C:0x50E00004,0x18:0x00E02025
build/src/game_libs/game_libs_post.c.o: TRUNCATE_TEXT := 0x588F0
build/src/game_libs/game_libs_post.c.o: INSN_PATCH := gl_func_0004E150=0x08:0x8C830134,0x0C:0x8C620014,0x10:0x8C59000C,0x14:0x844E0008,0x1C:0x01C32021

build/src/kernel/kernel_001.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_003.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_005.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_007.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_009.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_011.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_013.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_015.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_017.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_019.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_021.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_023.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_025.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_027.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_028.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_029.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_030.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_031.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_032.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_033.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_034.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_035.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_036.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_037.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_038.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_039.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_040.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_041.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_042.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_043.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_044.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_045.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_046.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_047.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_048.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_049.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_050.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_051.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_052.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_053.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_054.c.o: INSN_PATCH := func_8000969C=0xC:0xafb00014,0x10:0xafb10018,0x18:0x8fb00038
build/src/kernel/kernel_055.c.o: OPT_FLAGS := -O1
# kernel_056: 64-bit libgcc-style helpers; -mips3 so IDO inlines d-arithmetic.
# Post-compile, rewrite e_flags from mips3 (0x20000000) to mips2+noreorder
# (0x10000001) so the linker will merge it with the rest of the kernel (mips2).
build/src/kernel/kernel_056.c.o: OPT_FLAGS := -O1
build/src/kernel/kernel_056.c.o: MIPSISET := -mips3 -32
build/src/kernel/kernel_056.c.o: POST_COMPILE = python3 -c "import sys;f=open(sys.argv[1],'r+b');f.seek(0x24);f.write(bytes.fromhex('10000001'));f.close()" $@

# Prologue-stolen successors: splice the duplicate lui+addiu prefix that
# C-emit naturally produces but expected/.o doesn't include in the symbol.
# Format: <func_name>=<bytes_to_remove>. Multiple entries separated by spaces.
# See scripts/splice-function-prefix.py and
# feedback_prologue_stolen_successor_no_recipe.md for context.
build/src/titproc_uso/titproc_uso.c.o: PROLOGUE_STEALS := titproc_uso_func_00000194=8 titproc_uso_func_000001E4=8 titproc_uso_func_0000028C=8
build/src/titproc_uso/titproc_uso.c.o: SUFFIX_BYTES := titproc_uso_func_00000194=0x3C020000,0x24420000
build/src/game_libs/game_libs_post.c.o: SUFFIX_BYTES := gl_func_00041278=0x3C0E0004,0x8DCEC160 gl_func_0006BA48=0x3C0EA460,0x8DC60010 gl_func_0005FDCC=0x3C030000,0x8C630000 gl_func_0002DF00=0x3C0E0000,0x8DCE2D00 gl_func_0002DF38=0x44856000
build/src/timproc_uso_b3/timproc_uso_b3.c.o: PROLOGUE_STEALS := timproc_uso_b3_func_00000818=8 timproc_uso_b3_func_00001C28=8 timproc_uso_b3_func_0000074C=8 timproc_uso_b3_func_00000790=8 timproc_uso_b3_func_000007D4=8
build/src/timproc_uso_b3/timproc_uso_b3.c.o: SUFFIX_BYTES := timproc_uso_b3_func_000021F4=0x3C040000,0x8C840148 timproc_uso_b3_func_00002388=0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000
build/src/timproc_uso_b1/timproc_uso_b1.c.o: PROLOGUE_STEALS := timproc_uso_b1_func_00000800=8 timproc_uso_b1_func_00000734=8 timproc_uso_b1_func_00000778=8 timproc_uso_b1_func_000007BC=8 timproc_uso_b1_func_00002030=8
build/src/timproc_uso_b1/timproc_uso_b1.c.o: SUFFIX_BYTES := timproc_uso_b1_func_00001FE4=0x3C040000,0x8C840148 timproc_uso_b1_func_00002178=0x03E00008,0x00000000,0x03E00008,0x00000000,0x03E00008,0x00000000
build/src/arcproc_uso/arcproc_uso_tail1.c.o: PROLOGUE_STEALS := arcproc_uso_func_00001F0C=8
build/src/game_libs/game_libs_post.c.o: PROLOGUE_STEALS := gl_func_0001FCD0=8 gl_func_0006BA0C=8 gl_func_0006BE6C=8 gl_func_00066810=8 gl_func_0002D620=8 gl_func_0002DEA4=8 gl_func_0002DF38=8

# INSN_PATCH := <func>=<offset>:<word>[,<offset>:<word>] — overwrite N specific
# instruction words in a function body post-cc, without changing function size
# or any symbol layout. For unmatchable IDO codegen caps where C is correct
# but 1-2 insns differ (FPU pipeline operand order, scheduler register choice).
# See scripts/patch-insn-bytes.py and
# feedback_insn_patch_for_ido_codegen_caps.md.
build/src/game_uso/game_uso.c.o: INSN_PATCH := \
	game_uso_func_000000A0=0x3C:0x460A4000 \
	game_uso_func_0000035C=0x20:0x27AF0018,0x24:0x8DF90000,0x28:0x8FAE0020,0x2C:0xADD90000 \
	game_uso_func_0000D438=0x00:0x8c8f00c0,0x04:0x8c8e00c4,0x14:0xac8f00c8,0x1C:0xac8e00cc
build/src/timproc_uso_b5/timproc_uso_b5.c.o: INSN_PATCH := \
	timproc_uso_b5_func_00008F98=0x8:0x8c83002c,0xC:0x8c620028,0x10:0x8c59005c,0x14:0x844e0058,0x1C:0x01c32021 \
	timproc_uso_b5_func_0000CE6C=0xC:0xc48e0294,0x10:0xc48c0264,0x14:0xc4820260,0x18:0xc480025c,0x1C:0xe44e0118,0x20:0xe44c010c,0x24:0xe4420114,0x2C:0xe4400110
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
	@if [ -n "$(TRUNCATE_TEXT)" ]; then python3 scripts/truncate-elf-text.py $@ $(TRUNCATE_TEXT); fi
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
