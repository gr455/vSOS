#include "page_controller.h"

page_directory_t kpd __attribute__((aligned(4096)));
uint32_t kpg_presentbits[MAXPAGES / 32];
uint32_t FRAMECTL_KPG_START_FRAME_OFFSET = 0x0;

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

// Premap high memory one-to-one with physical memory on kpd
void kpd_init_highmem(page_directory_t* kpd) {
	extern uint32_t __kernel_heap_start;
	for (uint32_t addr = (uint32_t)&__kernel_heap_start; addr < 0x400000; addr += 0x1000) {
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


// Allocate new frame and map it to the virt in PD.
void pgctl_alloc_and_map(uint32_t virt, page_directory_t* pd) {
	extern uint32_t __kernel_heap_start;

	uint32_t pd_index = (virt >> 22) & 0x3FF;
	uint32_t pt_index = (virt >> 12) & 0x3FF;

	uint32_t pd_entry_flags = PDE_PRESENT | PDE_RW;
	if (pd_get_entry_phys_addr(pd, pd_index) == 0) {
		frame* pt_frame = fctl_get_free_frame();
		pd_set_entry(pd, pd_index, (uint32_t)pt_frame->phys, pd_entry_flags);
		pd_init((page_directory_t*)pt_frame->phys);
	}

	frame* new_frame = fctl_get_free_frame();
	uint32_t pt_phys = pd_get_entry_phys_addr(pd, pd_index);
	page_directory_t* pt = (page_directory_t*)pt_phys;
	pd_set_entry(pt, pt_index, (uint32_t)new_frame->phys, PDE_PRESENT | PDE_RW);
}


// Allocate k consecutive free pages from the heap region
// Returns the virtual address of the first allocated page, or 0 on failure
// use_cr3 indicates whether to use the current CR3 page directory or the kernel page directory
// TODO: kpg only for now
uint32_t pgctl_alloc_pages(uint32_t k, page_directory_t* pd) {
	extern uint32_t __kernel_heap_start;

	// printi((uint32_t)&__kernel_heap_start);
	// return 0;
	
	if (k == 0) return 0;
	
	uint32_t mask = (1 << k) - 1;
	
	// Search for k consecutive free pages in the bitmap
	for (uint32_t i = 0; i < MAXPAGES; i++) {
		uint32_t entry_idx = i / 32;
		uint32_t bit_idx = i % 32;
		
		// AND the mask with the bitmap window
		if (((kpg_presentbits[entry_idx] >> bit_idx) & mask) == 0) {
			// Mark k pages as used
			for (uint32_t j = 0; j < k; j++) {
				uint32_t page_idx = i + j;
				uint32_t idx = page_idx / 32;
				uint32_t bit = page_idx % 32;
				kpg_presentbits[idx] |= (1 << bit);
			}
			
			// Return the virtual address of the first page
			uint32_t virt_addr = ((uint32_t)&__kernel_heap_start + FRAMECTL_KPG_START_FRAME_OFFSET) + (i * 0x1000);
			
			// Map the pages in the page directory
			for (uint32_t j = 0; j < k; j++) {
				pgctl_alloc_and_map(virt_addr + (j * 0x1000), pd);
			}
			return virt_addr;
		}
	}
	
	// No k consecutive free pages found
	return 0;
}

void kpd_init_vga(page_directory_t* kpd) {
	uint32_t vga_phys_addr = 0xB8000;
	uint32_t vga_virt_addr = 0xB8000;
	uint32_t pd_index = (vga_virt_addr >> 22) & 0x3FF;
	uint32_t pt_index = (vga_virt_addr >> 12) & 0x3FF;

	uint32_t pd_entry_flags = PDE_PRESENT | PDE_RW;
	if (pd_get_entry_phys_addr(kpd, pd_index) == 0) {
		frame* new_frame = fctl_get_free_frame();
		pd_set_entry(kpd, pd_index, (uint32_t)new_frame->phys, pd_entry_flags);
		pd_init((page_directory_t*)new_frame->phys);
	}

	page_directory_t* pt = (page_directory_t*)pd_get_entry_phys_addr(kpd, pd_index);
	pd_set_entry(pt, pt_index, vga_phys_addr, PDE_PRESENT | PDE_RW);
}

// Free k pages starting from the given virtual address. Returns the number of pages freed.
// TODO: kpg only for now
uint32_t pgctl_free_pages(uint32_t virt, uint32_t k, page_directory_t* pd) {
	extern uint32_t __kernel_heap_start;
	
	if (k == 0) return 0;
	
	uint32_t start_page = (virt - ((uint32_t)&__kernel_heap_start + FRAMECTL_KPG_START_FRAME_OFFSET)) / 0x1000;
	uint32_t count = 0;
	// Mark k pages as free
	for (uint32_t j = 0; j < k; j++) {
		uint32_t page_idx = start_page + j;
		uint32_t idx = page_idx / 32;
		uint32_t bit = page_idx % 32;
		uint32_t was_set = (kpg_presentbits[idx] >> bit) & 1;
		kpg_presentbits[idx] &= ~(1 << bit);
		count += (uint32_t) was_set;
	}

	return count;
}

uint32_t kmalloc(size_t size) {
	if (size <= 0) return 0;
	
	uint32_t pgcount = (size + 0xFFF) / 0x1000; // round up to nearest page
	return pgctl_alloc_pages(pgcount, &kpd);
}

void kfree(uint32_t addr, size_t size) {
	if (size <= 0 || addr == 0) return;
	
	uint32_t pgcount = (size + 0xFFF) / 0x1000; // round up to nearest page
	pgctl_free_pages(addr, pgcount, &kpd);
}

void __test__k_setmem(uint32_t vaddr, char value) {
	char* ptr = (char*)vaddr;
}

char __test__k_getmem(uint32_t vaddr) {
	char* ptr = (char*)vaddr;
	return *ptr;
}

void pgctl_init() {
	pd_init(&kpd);
	kpd_init_lowmem(&kpd);
	kpd_init_highmem(&kpd);
	kpd_init_vga(&kpd);
	set_paging_enable((uint32_t)&kpd);
}