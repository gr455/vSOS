#pragma once
#include "utils.h"
#include "../libc/util_types.h"

typedef struct frame {
	uint32_t phys; // physical address start
	bool mapped; // mapped or free
	// TODO: dirty, cow, tlb meta etc.
}

uint32_t get_phys_start(frame* f);
bool is_mapped(frame* f);
