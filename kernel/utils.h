#ifndef UTILS_H
#define UTILS_H

void v_memcpy(void * source, void * dest, unsigned int bytes);
void c_memcpy(char * source, char * dest, unsigned int bytes);
char itoa(int a);
void int_to_ascii(int n, char str[]);
void reverse(char str[]);
int strlen(char str[]);

#endif