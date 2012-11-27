#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include <string.h>
#include "adc.h"
#include "pwm.h"
#include "serial.h"


char buffer[25];
char i;
static unsigned char counter = 0;

void serial_cb(int c) {
    char *p;

    if(i < 24) {
        buffer[i] = c;
        if('\r' == c || '\n' == c) {
            buffer[i] = '\0';
            p = buffer;
            
            if(buffer[0] == 'S' && buffer[1] == 'B') {
                while(*p) {
                    serial_putchar(*p);
                    p++;
                }
                serial_putchar('\r');
                serial_putchar('\n');
                
                /*
                >>> int(1/0.0015)
                666
                >>> int(1/0.00125)
                800
                >>> int(1/0.00175)
                571
                */
                switch(counter) {
                case 0:
                    pwm_start(666);
                    break;
                case 1:
                    pwm_start(800);
                    break;
                case 2:
                    pwm_start(571);
                    break;
                default:
                    pwm_stop();
                }
                
                if(counter > 2) {
                    counter = 0;
                } else {
                    counter++;
                }
            }

		    i = 0;
        } else {
            i++; // Don't forget to increase the "pointer".
        }
    } else {
	    i = 0;
	}
}

int main(void)
{
    unsigned char adc_value;
    
    // 1/0.02 = 50
    pwm_init(50);
    adc_init();
    serial_init(serial_cb);
    pwm_start(666);
    while(1) {
        //adc_value = adc_read();
    }
    return 0;
}
