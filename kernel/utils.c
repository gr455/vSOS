/*
 * Contains utility functions used in multiple places throughout the kernel
 */

#include "utils.h"
#include "../libc/string.h"

void c_memcpy(char * source, char * dest, unsigned int bytes){
	unsigned int i = 0;
	for(i; i < bytes ; i++) {
		*(dest + i) = *(source + i );
	}
}
