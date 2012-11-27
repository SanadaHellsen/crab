#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include <string.h>
#include "adc.h"
#include "delay.h"
#include "pwm.h"
#include "serial.h"

typedef struct decimal {
    signed int n;
    signed int d;
} decimal_t;

static char buffer[25];
static char i;

static signed int pid_y;
static decimal_t pid_kp = {1, 1};
static decimal_t pid_ki = {1, 1};
static decimal_t pid_kd = {1, 1};


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
    unsigned char adc_v;
    decimal_t adc_k;
    signed int pid_v;
    signed int pid_pe;
    signed int pid_e;
    signed int pid_i;
    signed int pid_d;
    signed int pid_sp;
    decimal_t pid_dt;
    
    /*
    666
    800
    571
    */
    // 1/0.02 = 50
    pwm_init(50);
    adc_init();
    serial_init(serial_cb);
    
    pwm_start(666);
    
    pid_pe = 0;
    pid_i = 0;
    pid_sp = 10;
    pid_dt.n = 1;
    pid_dt.d = 1000;
    adc_k.n = 1;
    adc_k.d = 1;
    
    while(1) {
        adc_v = adc_read();
        pid_v = (adc_k.n * adc_v) / adc_k.d;
        
        pid_e  = pid_sp - pid_v;
        pid_i += (pid_dt.n * pid_e) / pid_dt.d;
        pid_d  = (pid_dt.d * (pid_e - pid_pe)) / pid_dt.n;
        
        pid_y  = 0;
        pid_y += (pid_kp.n * pid_e) / pid_kp.d;
        pid_y += (pid_ki.n * pid_i) / pid_ki.d;
        pid_y += (pid_kd.n * pid_d) / pid_kd.d;
        
        pid_pe = pid_e;
        
        pwm_start(666 + pid_y);
        
        delay_1ms();
    }
    return 0;
}
