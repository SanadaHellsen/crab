#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "config.h"
#include "types.h"
#include "io.h"

#include "adc.h"
#include "cmd.h"
#include "delay.h"
#include "pid.h"
#include "pwm.h"
#include "serial.h"
#include "string.h"


volatile unsigned char serial_rx = 0;
volatile unsigned char bi = 0;
volatile unsigned char buffer[BUFLEN];

void serial_cb(int c) {

    if(serial_rx) {
        return;
    }
    
    if(bi >= BUFLEN) {
        bi = 0;
    }
    
    buffer[bi] = c;
    
    if('\r' == c || '\n' == c) {
        buffer[bi] = '\0';
        serial_rx = 1;
	    bi = 0;
    } else {
        bi++;
    }
}

void main(void)
{
    signed int pwm_value;
    
    adc_init();
    pid_init();
    pwm_init(SERVO_PER);
    serial_init(serial_cb);
    
    pwm_start(SERVO_MIN);
    serial_puts(msg_ok);

    while(1) {
        if(serial_rx) {
            serial_puts(buffer);
            cmd_execute(buffer);
            serial_rx = 0;
        }
                
        pwm_value += pid_process(ADC_READ());

        if(pwm_value > SERVO_MAX) {
            pwm_value = SERVO_MAX;
        } else if(pwm_value < SERVO_MIN) {
            pwm_value = SERVO_MIN;
        }
        
        pwm_start((unsigned int)pwm_value);
    }
}
