#include "frame_controller.h"

void fctl_init(uint32_t start_phys, uint32_t end_phys) {
	uint32_t frames = (end_phys - start_phys + 1) / PAGE_SIZE;

	for (uint32_t i = 0; i < frames; i++) {

	}
}