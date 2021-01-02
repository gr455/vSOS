#ifndef UTILS_H
#define UTILS_H

#include "../libc/util_types.h"

void v_memcpy(void * source, void * dest, unsigned int bytes);
void c_memcpy(char * source, char * dest, unsigned int bytes);

#endif