#!/bin/bash

cd ../ \
&& find . -type f -name '*.o' -delete \
&& find . -type f -name '*.bin' -delete \
&& cd image/ \
&& cd ../boot/ \
&& mkdir -p bin \
&& nasm -f bin boot_min.asm -o bin/boot_stage1.bin \
&& nasm -f bin bootloader.asm -o bin/boot_stage2.bin \
&& cat bin/boot_stage1.bin bin/boot_stage2.bin > bin/boot.bin \
&& cd ../image/ \
&& cd ../kernel/doto/ \
&& i386-elf-gcc -c -ffreestanding -fno-stack-protector -nostdlib ../*.c \
&& cd ../mmu/doto/ \
&& i386-elf-gcc -c -ffreestanding -fno-stack-protector -nostdlib ../*.c \
&& cd ../../../drivers/doto/ \
&& i386-elf-gcc -c -ffreestanding -fno-stack-protector -nostdlib ../*.c \
&& cd ../../libc/doto/ \
&& i386-elf-gcc -c -ffreestanding -fno-stack-protector -nostdlib ../*.c \
&& cd ../../image/ \
&& nasm ../kernel/kernel_entry.asm -f elf -o ../kernel/doto/entry/kernel_entry.o \
&& nasm ../kernel/intr.asm -f elf -o ../kernel/doto/intr.o \
&& i386-elf-ld -o ../kernel/bin/kernel.elf -T ../kernel/vsos.ld ../kernel/doto/entry/kernel_entry.o ../kernel/doto/*.o ../libc/doto/*.o ../drivers/doto/*.o ../kernel/mmu/doto/*.o \
&& i386-elf-objcopy -O binary ../kernel/bin/kernel.elf ../kernel/bin/kernel.bin \
&& cat ../boot/bin/boot.bin ../kernel/bin/kernel.bin > os-image \
&& echo "done" \
&& truncate -s 40k os-image \
&& find . -type f -name '*.iso' -delete \
&& mkisofs -o os-image.iso -b os-image . \
&& echo "iso image created"