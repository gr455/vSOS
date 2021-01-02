#ifndef UTILS_H
#define UTILS_H

#include "../libc/util_types.h"

void v_memcpy(void * source, void * dest, unsigned int bytes);
void c_memcpy(char * source, char * dest, unsigned int bytes);
char itoa(int a);
void int_to_ascii(int n, char str[]);
void reverse(char str[]);
int strlen(char str[]);
void split(char s[], char des[], uint8_t word);
int strcmp(char s1[], char s2[]);

#endif