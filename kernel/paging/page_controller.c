#include "page_controller.h"

page_directory_t kpd;

// initialize lower memory one-to-one with physical memory
void kpd_init_lowmem(page_directory_t* kpd) {
	extern uint32_t __kernel_heap_start;
	for (uint32_t addr = (uint32_t)0; addr < (uint32_t)&__kernel_heap_start; addr += 0x1000) {
		uint32_t pd_index = (addr >> 22) & 0x3FF;
		uint32_t pt_index = (addr >> 12) & 0x3FF;

		uint32_t pd_entry_flags = PDE_PRESENT | PDE_RW;
		if (pd_get_entry_phys_addr(kpd, pd_index) == 0) {
			frame* new_frame = fctl_get_free_frame();
			pd_set_entry(kpd, pd_index, (uint32_t)new_frame->phys, pd_entry_flags);
			pd_init((page_directory_t*)new_frame->phys);
		}

		page_directory_t* pt = (page_directory_t*)pd_get_entry_phys_addr(kpd, pd_index);
		pd_set_entry(pt, pt_index, addr, PDE_PRESENT | PDE_RW);
	}
}

void kpd_init_vga(page_directory_t* kpd) {
	uint32_t vga_phys_addr = 0xB8000;
	uint32_t vga_virt_addr = 0xB8000;
	uint32_t pd_index = (vga_virt_addr >> 22) & 0x3FF;
	uint32_t pt_index = (vga_virt_addr >> 12) & 0x3FF;

	uint32_t pd_entry_flags = PDE_PRESENT | PDE_RW;
	if (pd_get_entry_phys_addr(kpd, pd_index) == 0) {
		frame* new_frame = fctl_get_free_frame();
		printi((uint32_t)new_frame->phys);
		pd_set_entry(kpd, pd_index, (uint32_t)new_frame->phys, pd_entry_flags);
		pd_init((page_directory_t*)new_frame->phys);
	}

	page_directory_t* pt = (page_directory_t*)pd_get_entry_phys_addr(kpd, pd_index);
	pd_set_entry(pt, pt_index, vga_phys_addr, PDE_PRESENT | PDE_RW);
}

void pgctl_init() {
	pd_init(&kpd);
	kpd_init_lowmem(&kpd);
	kpd_init_vga(&kpd);
	set_paging_enable((uint32_t)&kpd);
}