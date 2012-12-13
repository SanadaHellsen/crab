#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "io.h"
#include "delay.h"

void adc_init(void) {
    ADC_DB = 0xff; // Set port as input
    ADC_INTRb = 0;
    delay_1ms();
    ADC_INTRb = 1;
}

unsigned char adc_read(void) {
    return ADC_DB;
}
