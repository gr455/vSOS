ENTRY(_start)

SECTIONS
{
    . = 0x010000;

    .text ALIGN(4K) : {
        *(.multiboot_header)
        *(.text*)
    }

    .rodata ALIGN(4K) : {
        *(.rodata*)
    }

    .data ALIGN(4K) : {
        *(.data*)
    }

    .bss ALIGN(4K) (NOLOAD) : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    }

    __kernel_heap_start = .;
}
