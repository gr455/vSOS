#! /bin/bash

cd ../ \
&& find . -type f -name '*.o' -delete \
&& find . -type f -name '*.bin' -delete \
&& cd image/ \
&& cd ../boot/ && nasm -f bin ../boot/bootloader.asm -o ../boot/bin/boot.bin \
&& cd ../image/ \
&& cd ../kernel/doto/ \
&& i386-elf-gcc -c -ffreestanding ../*.c \
&& cd ../../drivers/doto/ \
&& i386-elf-gcc -c -ffreestanding ../*.c \
&& cd ../../libc/doto/ \
&& i386-elf-gcc -c -ffreestanding ../*c \
&& cd ../../image/ \
&& nasm ../kernel/kernel_entry.asm -f elf -o ../kernel/doto/entry/kernel_entry.o \
&& i386-elf-ld -o ../kernel/bin/kernel.bin -Ttext 0x1000 ../kernel/doto/entry/kernel_entry.o ../kernel/doto/*.o ../libc/doto/*.o ../drivers/doto/*.o --oformat binary \
&& cat ../boot/bin/boot.bin ../kernel/bin/kernel.bin > os-image \
&& echo "done"