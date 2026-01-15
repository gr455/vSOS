# verySimpleOS
x86_32 Kernel + Bootloader.

### Run:
Image file in `image/os-image`

#### Run with QEMU(i386):
`qemu-system-i386 -fda -m 64M image/os-image`

#### Run with VirtualBox
- Use type `Other`
- Use version `Other/Unkown`
- Allocate atleast 64M of ram
- Set the iso image in `image/os-image.iso` in `IDE Secondary Master` storage device as a `Live CD`
- Boot the machine

### Source:
- `kernel/` contains all the kernel related files. `kernel/k_exec.c` contains the `k_main` function which gets executed on boot.
   - `kernel/mmu` Has physical frame management
   - `kernel/paging` Has VMM and paging
   - `kernel/task` Has processes
   - `kernel/vsos.ld` is the linker file for vSOS.
- `libc/` contains all the standard C Libraries written for vSOS.
- `boot/` contains files which help in booting up the OS. These include the bootloader, global descriptor table, protected mode switch and such.
- `drivers/` contains drivers for hardware devices that vSOS supports.
- `image/` contains the image for vSOS and compilation script.

### Features* :
- Bootloader
- Hardware drivers
- Memory management and Paging
- Processes
- Interactive shell
... and more

#### Runs privilleged just like Terry Davis would have liked it

### References:

- https://stanislavs.org/helppc/idx_interrupt.html
- https://wiki.osdev.org/Meaty_Skeleton
- https://www.udacity.com/course/introduction-to-operating-systems--ud923
- http://www.jamesmolloy.co.uk/tutorial_html/
- https://wiki.osdev.org/PIC
- https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
- https://github.com/cfenollosa/os-tutorial
- Gemini, Claude, ChatGPT. Although they lie to me sometimes.
