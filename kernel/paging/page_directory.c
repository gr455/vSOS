#include "page_directory.h"
#include "../mmu/frame_controller.h"

extern void set_paging_enable(uint32_t kpd_phys_addr);
extern void set_pd(uint32_t pd_phys_addr);

// premap_entry must be -1 or index of a single page that points to scratch page for now.
void pd_init(page_directory_t* pd) {
    extern uint32_t __kernel_heap_start;
    for (int i = 0; i < 1024; i++) {
        pd->entries[i].e = 0;
    }
}

void pd_set_entry(page_directory_t* pd, uint32_t index, uint32_t phys_addr, uint32_t flags) {
    pd->entries[index].e = (phys_addr & PDE_ADDR_MASK) | flags;
}

uint32_t pd_get_entry_phys_addr(page_directory_t* pd, uint32_t index) {
    return pd->entries[index].e & PDE_ADDR_MASK;
}

uint32_t pd_get_entry_flags(page_directory_t* pd, uint32_t index) {
    return pd->entries[index].e & ~PDE_ADDR_MASK;
}