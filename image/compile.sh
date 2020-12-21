#! /bin/bash

cd ../boot/ && nasm ../boot/bootloader.asm -o ../boot/bin/boot.bin \
&& cd ../image/ \
&& gcc -ffreestanding -c ../kernel/kernel.c -o ../kernel/doto/kernel.o \
&& ld -o ../kernel/bin/kernel.bin -Ttext 0x1000 ../kernel/doto/kernel.o --oformat binary \
&& cat ../boot/bin/boot.bin ../kernel/bin/kernel.bin > os-image \
&& echo "done"