# verySimpleOS

### Run:
Image file in `image/os-image`

#### Run with QEMU(i386):
`qemu-system-i386 -fda image/os-image`

#### Run with VirtualBox
- Use type `Other`
- Use version `Other/Unkown`
- Allocate atleast 2GB of ram
- Set the iso image in `image/os-image.iso` in `IDE Secondary Master` storage device as a `Live CD`
- Boot the machine

### Source:
- `kernel/` contains all the kernel related files. `kernel/k_exec.c` contains the `k_main` function which gets executed on boot.
- `libc/` contains all the standard C Libraries written for vSOS.
- `boot/` contains files which help in booting up the OS. These include the bootloader, global descriptor table, protected mode switch and such.
- `drivers/` contains drivers for hardware devices that vSOS supports.
- `image/` contains the image for vSOS and compilation script.

### Features* :
- Hardware drivers
- Interactive shell
- Proprietory C library

... and more

#### Runs privilleged just like Terry Davis would have liked it

### References:

- https://stanislavs.org/helppc/idx_interrupt.html
- https://wiki.osdev.org/Meaty_Skeleton
- https://www.udacity.com/course/introduction-to-operating-systems--ud923
- http://www.jamesmolloy.co.uk/tutorial_html/
- https://wiki.osdev.org/PIC

#### Heavily used references:
- https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
- https://github.com/cfenollosa/os-tutorial
- 
**PLEASE RUN ONLY ON A VIRTUAL MACHINE / EMULATOR**
