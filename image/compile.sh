#! /bin/bash

cd ../boot/ && nasm ../boot/bootloader.asm -o ../boot/bin/boot.bin \
&& cd ../image/ \
&& cd ../kernel/doto/ \
&& gcc -c -ffreestanding ../*.c \
&& cd ../../drivers/doto/ \
&& gcc -c -ffreestanding ../*.c \
&& cd ../../libc/doto/ \
&& gcc -c -ffreestanding ../*c \
&& cd ../../image/ \
&& nasm ../kernel/kernel_entry.asm -f elf64 -o ../kernel/doto/entry/kernel_entry.o \
&& ld -o ../kernel/bin/kernel.bin -Ttext 0x1000 ../kernel/doto/entry/kernel_entry.o ../kernel/doto/*.o ../libc/doto/*.o ../drivers/doto/*.o --oformat binary \
&& cat ../boot/bin/boot.bin ../kernel/bin/kernel.bin > os-image \
&& echo "done"