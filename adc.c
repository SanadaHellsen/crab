#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

void adc_init(void) {
}

unsigned char adc_read(void) {
    unsigned char wr, intr = 0, port = 0;
    wr = 1;
    wr = 0;
    while(intr);
    
    return port;
}