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

void split(char s[], char des[], uint8_t word){
	unsigned int i = 0;
	unsigned int j = 0;
	uint8_t wc = 0;
	for(; i < strlen(s); i++){
		if(wc > word) return;
		if(s[i] == ' '){
			wc++;
		}

		if(wc == word){
			des[j] = s[i];
			j++;
		}
	}
}

int strcmp(char s1[], char s2[]){
	if(strlen(s1) != strlen(s2)) return 1;
	uint32_t i;
	for(i; i < strlen(s1); i++){
		if(s1[i] != s2[i]) return 1;
	}
	return 0;
}