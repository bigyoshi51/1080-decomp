BASENAME  := tenshoe
TARGET    := $(BASENAME)
ROM       := $(TARGET).z64
ELF       := build/$(TARGET).elf
LD_SCRIPT := $(TARGET).ld
BASEROM   := baserom.z64

# Paths
TOOLS     := ../../tools
GCC_DIR   := $(TOOLS)/gcc_2.7.2/linux

# Tools
CROSS    := mips-linux-gnu-
AS       := $(CROSS)as
CC       := $(GCC_DIR)/gcc
LD       := $(CROSS)ld
OBJCOPY  := $(CROSS)objcopy
STRIP    := $(CROSS)strip

# Flags
ASFLAGS  := -march=vr4300 -mabi=32 -G 0 -I include
OPTFLAGS := -O2
CFLAGS   := -G 0 -mgp32 -mfp32
CPPFLAGS := -I include -DINCLUDE_ASM_USE_MACRO_INC=1
LDFLAGS  := -T $(LD_SCRIPT) -T undefined_syms_auto.txt -Map build/$(TARGET).map --no-check-sections

# Collect source files
C_FILES   := $(shell find src -name '*.c' -type f 2>/dev/null)
ASM_FILES := $(shell find asm -name '*.s' -not -path 'asm/nonmatchings/*' -type f 2>/dev/null)
BIN_FILES := $(shell find assets -name '*.bin' -type f)

# Object files
C_O_FILES   := $(patsubst src/%.c,build/src/%.c.o,$(C_FILES))
ASM_O_FILES := $(patsubst asm/%.s,build/asm/%.s.o,$(ASM_FILES))
BIN_O_FILES := $(patsubst assets/%.bin,build/assets/%.bin.o,$(BIN_FILES))
O_FILES     := $(BIN_O_FILES) $(C_O_FILES) $(ASM_O_FILES)

# Default target
all: verify

# Build ROM
$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(O_FILES) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@

# C source (using asm-processor to handle INCLUDE_ASM)
build/src/%.c.o: src/%.c
	@mkdir -p $(dir $@)
	COMPILER_PATH=$(GCC_DIR) python3 $(TOOLS)/asm-processor/build.py \
		--asm-prelude include/macro.inc \
		$(CC) -- $(AS) $(ASFLAGS) -- \
		-c $(OPTFLAGS) $(CFLAGS) $(CPPFLAGS) -o $@ $<

# Assembly (standalone asm files, NOT nonmatchings)
build/asm/%.s.o: asm/%.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Binary assets
build/assets/%.bin.o: assets/%.bin
	@mkdir -p $(dir $@)
	$(OBJCOPY) -I binary -O elf32-tradbigmips $< $@

# Verify ROM matches
verify: $(ROM)
	@md5sum -c checksum.md5 && echo "ROM OK" || echo "ROM MISMATCH"

clean:
	rm -rf build $(ROM)

.PHONY: all clean verify
