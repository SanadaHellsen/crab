#include "string.h"

void strcpy_(char *dst, char *src)
{
	while(*src) {
		*(dst++) = *(src++);
	}
    *dst = '\0';
}
/*
int memcmp_(char *s1, char *s2, unsigned char n)
{
    int r = 0;
    
    for(; n > 0; n--) {
        r += *s1 - *s2;
        if(r > 0) {
            break;
        }
        s1++;
        s2++;
    }
    
    return r;
}*/