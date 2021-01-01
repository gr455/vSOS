/*
 * Contains utility functions used in multiple places throughout the kernel
 */

#include "utils.h"

void c_memcpy(char * source, char * dest, unsigned int bytes){
	unsigned int i = 0;
	for(i; i < bytes ; i++) {
		*(dest + i) = *(source + i );
	}
}

char itoa(int a) {
	return (char) a - '0';
}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}