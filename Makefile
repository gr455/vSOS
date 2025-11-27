# vSOS Makefile
# Build the OS image and all components

# Directories
BOOT_DIR := boot
KERNEL_DIR := kernel
DRIVERS_DIR := drivers
LIBC_DIR := libc
MMU_DIR := $(KERNEL_DIR)/mmu
IMAGE_DIR := image

# Output files
BOOT_BIN := $(BOOT_DIR)/bin/boot.bin
KERNEL_BIN := $(KERNEL_DIR)/bin/kernel.bin
OS_IMAGE := $(IMAGE_DIR)/os-image
OS_ISO := $(IMAGE_DIR)/os-image.iso

# Tools
AS := nasm
CC := gcc
LD := ld
OBJCOPY := objcopy
MKISO := genisoimage

# Flags
ASFLAGS := -f bin
CFLAGS := -m32 -ffreestanding -Wall -Wextra -nostdlib -fno-builtin -I$(KERNEL_DIR) -I$(DRIVERS_DIR) -I$(LIBC_DIR) -I$(MMU_DIR)
LDFLAGS := -m elf_i386 -T $(KERNEL_DIR)/vsos.ld

# Source files
BOOT_SRC := $(BOOT_DIR)/bootloader.asm
KERNEL_SRC := $(wildcard $(KERNEL_DIR)/*.c) $(wildcard $(KERNEL_DIR)/mmu/*.c)
DRIVERS_SRC := $(wildcard $(DRIVERS_DIR)/*.c)
LIBC_SRC := $(wildcard $(LIBC_DIR)/*.c)

KERNEL_OBJS := $(KERNEL_SRC:.c=.o) $(DRIVERS_SRC:.c=.o) $(LIBC_SRC:.c=.o)
KERNEL_OBJS := $(patsubst %,$(KERNEL_DIR)/doto/%,$(notdir $(KERNEL_OBJS)))

# Default target
all: $(OS_IMAGE)

# Build bootloader
$(BOOT_BIN): $(BOOT_SRC)
	$(AS) $(ASFLAGS) -o $@ $<

# Compile kernel objects
$(KERNEL_DIR)/doto/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(KERNEL_DIR)/doto/%.o: $(KERNEL_DIR)/mmu/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(KERNEL_DIR)/doto/%.o: $(DRIVERS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
$(KERNEL_DIR)/doto/%.o: $(LIBC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Link kernel
$(KERNEL_BIN): $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)
	$(OBJCOPY) -O binary $@ $@

# Build OS image
$(OS_IMAGE): $(BOOT_BIN) $(KERNEL_BIN)
	cat $(BOOT_BIN) $(KERNEL_BIN) > $@

# ISO image
iso: $(OS_IMAGE)
	$(MKISO) -o $(OS_ISO) -b os-image $(IMAGE_DIR)

# Clean
clean:
	rm -f $(BOOT_BIN) $(KERNEL_BIN) $(OS_IMAGE) $(OS_ISO)
	rm -f $(KERNEL_DIR)/doto/*.o $(KERNEL_DIR)/mmu/doto/*.o $(DRIVERS_DIR)/doto/*.o $(LIBC_DIR)/doto/*.o

.PHONY: all clean iso
