#include "string.h"

void strcpy_(char *dst, char *src)
{
	while(*src) {
		*(dst++) = *(src++);
	}
    *dst = '\0';
}

int atoi_(char *s) {
    int acc = 0;
    
    for(; *s; s++) {
        acc = 10 * acc + *s - '0';
    }
    
    return acc;
}

int memcmp_(char *s1, char *s2, unsigned char n)
{
    for(; n > 0; n--, s1++, s2++) {
        if((*s1 - *s2) > 0) {
            return 1;
        }
    }
    
    return 0;
}