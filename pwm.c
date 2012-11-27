#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "io.h"
#include "interrupt.h"
#include "pwm.h"

static unsigned char    pwm;
static unsigned int     pwm_tw0;
static unsigned int     pwm_period;
static unsigned char    pwm_on;

void pwm_isr(void) interrupt 1
{
    TR0 = 0;


    PWM_BIT = !pwm;
    
    if(pwm) {
        pwm_tw0 = (0xffff - pwm_period + pwm_on);        
    } else {
        pwm_tw0 = (0xffff - pwm_on);
    }

    TH0 = (pwm_tw0 >> 8) & 0xff;
    TL0 = (pwm_tw0 >> 0) & 0xff;

    pwm = !pwm;
            
    TR0 = 1;
}

void pwm_init(unsigned int period_ticks)
{
    TMOD &= 0xf0;
    TMOD |= 0x01;

    TH0 = 0;
    TL0 = 0;

    ET0 = 1;
    EA = 1;
    
    pwm_period = CPU_SEC_TICKS/period_ticks;
}

void pwm_start(unsigned int duty_ticks)
{
    pwm_on = CPU_SEC_TICKS/duty_ticks;
    
    pwm_tw0 = (0xffff - pwm_on);
    
    TH0 = (pwm_tw0 >> 8) & 0xff;
    TL0 = (pwm_tw0 >> 0) & 0xff;
    
    pwm = 1;
    
    ET0 = 1;
    TR0 = 1;
}

void pwm_stop(void)
{
    ET0 = 0;
    TR0 = 0;
}
