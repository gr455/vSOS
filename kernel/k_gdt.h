#include "../libc/utils.h"
#include "../libc/utils_types.h"

typedef struct gdt_entry {

	uint16_t l_limit;
	uint16_t l_base;
	uint8_t m_base;
	uint8_t flags_access;
	uint8_t flags_gran;
	uint8_t	h_base;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr {
	uint16_t lim;
	uint32_t base;
} __attribute__((packed)) gdt_ptr_t;