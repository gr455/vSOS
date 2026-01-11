#pragma once

#include "../../libc/util_types.h"

#define PDE_PRESENT      0x001
#define PDE_RW           0x002
#define PDE_USER         0x004
#define PDE_PWT          0x008
#define PDE_PCD          0x010
#define PDE_ACCESSED     0x020
#define PDE_DIRTY        0x040 // PD hugepage entry only, PT all entries.
#define PDE_HUGEPAGE     0x080 // 4MiB. Skip PT lookup. Will not be used in vSOS
#define PDE_PHYS         0x100

#define PDE_ADDR_MASK    0xFFFFF000 // always 4KiB aligned

/**
 * - A PD has 1024 entries. A PD maps 4GiB of virtual address space.
 *   Each PD entry points to one PT.
 *
 * - A PT has 1024 entries. A PT maps 4 MiB of virtual address space.
 *   Each PT entry maps one 4 KiB physical page.
 *
 *
 *  A PD/PT entry is 4 bytes, 32 bits governed by defines above.
 *  Therefore each PD/PT is 4KiB large.
 *  Therefore both PD and PT must be 4KiB aligned.
 */

typedef struct {
	uint32_t e; // everything bitfield, governed by the defs above
} page_directory_entry_t;


typedef struct {
	page_directory_entry_t entries[1024];
} page_directory_t;

void pd_init(page_directory_t* pd);
void pd_set_entry(page_directory_t* pd, uint32_t index, uint32_t phys_addr, uint32_t flags);
uint32_t pd_get_entry_phys_addr(page_directory_t* pd, uint32_t index);
uint32_t pd_get_entry_flags(page_directory_t* pd, uint32_t index);
