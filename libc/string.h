#ifndef STRINGLIBC_H
#define STRINGLIBC_H

#include "../libc/util_types.h"


char itoa(int a);
void int_to_ascii(int n, char str[]);
void reverse(char str[]);
int strlen(char str[]);
void split(char s[], char des[], uint8_t word);
int strcmp(char s1[], char s2[]);
int stoi(char s[]);

#endif