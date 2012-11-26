#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "interrupt.h"

//>>> int(11.059e6/12)
//921583

#define CPUSEC 921583

static unsigned char pwm;
static unsigned int t0;
static unsigned int pwm_period;
static unsigned int pwm_on;

void pwm_isr(void) interrupt 1
{
    TR0 = 0;


    P0_0 = !pwm;
    
    if(pwm) {
        t0 = (0xffff - pwm_period + pwm_on);        
    } else {
        t0 = (0xffff - pwm_on);
    }
        
    pwm = !pwm;

    TH0 = (t0 >> 8) & 0xff;
    TL0 = (t0 >> 0) & 0xff;
        
    TR0 = 1;
}

void pwm_init(unsigned int period)
{
    TMOD &= 0xf0;
    TMOD |= 0x01;

    TH0 = 0;
    TL0 = 0;

    ET0 = 1;
    EA = 1;
    
    pwm_period = CPUSEC/period;
}

void pwm_start(unsigned int duty)
{
    pwm_on = CPUSEC/duty;
    // ON = T - a + x
    // OFF = T - x
    
    t0 = (0xffff - pwm_on);
    TH0 = (t0 >> 8) & 0xff;
    TL0 = (t0 >> 0) & 0xff;
    
    pwm = 1;
    ET0 = 1;
    TR0 = 1;
}

void pwm_stop(void)
{
    ET0 = 0;
    ET0 = 0;
    ET0 = 0;
    TR0 = 0;
}
