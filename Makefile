###############################################################################
# Project settings
###############################################################################

BUILD_DIR := build
OBJECT_DIR := $(BUILD_DIR)/objs
TARGET = STM32F407VGT6_DISC1.elf

CC = arm-none-eabi-gcc
DB = arm-none-eabi-gdb

###############################################################################
# Sources and includes
###############################################################################

ASSEMBLY_FILES  = $(wildcard STM32F407VGT6.s)

C_SOURCE_FILES  = $(wildcard bsp/src/*.c)
C_SOURCE_FILES += $(wildcard bsp/ext/src/*.c)
C_SOURCE_FILES += $(wildcard drivers/src/*.c)
C_SOURCE_FILES += $(wildcard src/*.c)
C_SOURCE_FILES += $(wildcard src/sys/*.c)

INCLUDE_DIRECTORIES  = .
INCLUDE_DIRECTORIES += bsp
INCLUDE_DIRECTORIES += bsp/ext
INCLUDE_DIRECTORIES += drivers
INCLUDE_DIRECTORIES += inc

###############################################################################
# Compilation setup
###############################################################################

# Compiler Flags
CFLAGS  = -g -O0 -Wall
CFLAGS += -mcpu=cortex-m4 -mfpu=fpv4-sp-d16
CLFAGS += -mthumb -mfloat-abi=hard -mlittle-endian
CFLAGS += $(foreach dir, $(INCLUDE_DIRECTORIES), $(addprefix -I, $(dir)))

# Linker Flags
LFLAGS = -TSTM32F407VGT6.ld -Wl,-Map=$(BUILD_DIR)/$(TARGET:.elf=.map)

###############################################################################
# Make targets
###############################################################################

# Setup object file list
ASM_OBJS = $(ASSEMBLY_FILES:.s=.o)
C_OBJS   = $(C_SOURCE_FILES:.c=.o)
ALL_OBJS = $(ASM_OBJS) $(C_OBJS)

# Compile
build: $(TARGET)
$(ASM_OBJS): %.o: %.s
$(C_OBJS): %.o: %.c
$(ALL_OBJS):
	@mkdir -p $(OBJECT_DIR)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $(OBJECT_DIR)/$(notdir $@)

# Link
%.elf: $(ALL_OBJS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(LFLAGS) $(foreach obj, $(ALL_OBJS), $(OBJECT_DIR)/$(notdir $(obj))) -o $(BUILD_DIR)/$(notdir $@)

# Clean
clean:
	@rmdir /S /Q $(BUILD_DIR)

# Flash
flash:
	@openocd -s "C:/Program Files (x86)/OpenOCD/share/openocd/scripts" -f interface/stlink-v1.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(TARGET) verify reset exit"
