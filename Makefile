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
build/src/arcproc_uso/arcproc_uso.c.o: TRUNCATE_TEXT := 0x50
build/src/arcproc_uso/arcproc_uso_o0_50.c.o: TRUNCATE_TEXT := 0x64
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_10310.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_120A8.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_123F0.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12B7C.c.o: OPT_FLAGS := -O0
build/src/bootup_uso/bootup_uso_o0_12DA4.c.o: OPT_FLAGS := -O0
# Trim .text sizes + reduce sh_addralign to 4 so split .o files link at the
# exact non-16-aligned offsets in bootup_uso. See feedback_non_aligned_o_split.md.
build/src/bootup_uso/bootup_uso.c.o: TRUNCATE_TEXT := 0xF76C
build/src/bootup_uso/bootup_uso_o0_F7F4.c.o: TRUNCATE_TEXT := 0xB0
build/src/bootup_uso/bootup_uso_tail1.c.o: TRUNCATE_TEXT := 0xA30
build/src/bootup_uso/bootup_uso_o0_1024C.c.o: TRUNCATE_TEXT := 0x14
build/src/bootup_uso/bootup_uso_tail2.c.o: TRUNCATE_TEXT := 0xB0
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
build/src/game_libs/game_libs_post.c.o: TRUNCATE_TEXT := 0x588F0

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
build/src/titproc_uso/titproc_uso.c.o: PROLOGUE_STEALS := titproc_uso_func_000001E4=8
build/src/game_libs/game_libs_post.c.o: PROLOGUE_STEALS := gl_func_0001FCD0=8

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
