/*
 * Contains utility functions used in multiple places throughout the kernel
 */

#include "utils.h"

void c_memcpy(char * source, char * dest, unsigned int bytes){
	for(unsigned int i = 0; i < bytes ; i++) {
		*(dest + i) = *(source + i );
	}
}