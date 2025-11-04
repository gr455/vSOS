#pragma once
#include "../utils.h"
#include "../../libc/util_types.h"

typedef struct frame {
	char* phys; // physical address start
	bool mapped; // mapped or free
	// TODO: dirty, cow, tlb meta etc.
} frame;

char* get_phys_start(frame* f);
bool is_mapped(frame* f);
