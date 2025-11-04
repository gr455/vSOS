#include "frame.h"

char* get_phys_start(frame* f) {
	return f->phys;
}

bool is_mapped(frame* f) {
	return f->mapped;
}
