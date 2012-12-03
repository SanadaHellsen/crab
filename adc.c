#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "io.h"

void adc_init(void) {
    ADCB = 0xff; // Set port as input
}

unsigned char adc_read(void) {
    return ADCB;
}
