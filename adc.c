#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "io.h"

void adc_init(void) {
}

unsigned char adc_read(void) {
    return ADC_PORT;
}