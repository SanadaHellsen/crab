#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "io.h"
#include "interrupt.h"
#include "pwm.h"

volatile unsigned char  pwm;
volatile unsigned int   pwm_tw0;
volatile unsigned char  pwm_th0_on;
volatile unsigned char  pwm_tl0_on;
volatile unsigned char  pwm_th0_off;
volatile unsigned char  pwm_tl0_off;
static unsigned int     pwm_period;
static unsigned int     pwm_on;

#ifdef SDCC
void pwm_isr(void) __interrupt (1)
#else
void pwm_isr(void) interrupt 1
#endif
{
    TR0 = 0;

    PWMb = pwm;
    
    if(pwm) {
        TH0 = pwm_th0_off;
        TL0 = pwm_tl0_off;
    } else {
        TH0 = pwm_th0_on;
        TL0 = pwm_tl0_on;
    }

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
    
    pwm_period = period_ticks;
}

void pwm_start(unsigned int duty_ticks)
{
    pwm_on = duty_ticks;
    
    pwm_tw0 = (0xffff - pwm_period + pwm_on);
    pwm_th0_on = (pwm_tw0 >> 8) & 0xff;
    pwm_tl0_on = pwm_tw0 & 0xff;
    
    pwm_tw0 = (0xffff - pwm_on);
    pwm_th0_off = (pwm_tw0 >> 8) & 0xff;
    pwm_tl0_off = pwm_tw0 & 0xff;
    
    TH0 = pwm_th0_on;
    TL0 = pwm_tl0_on;
    
    pwm = 1;
    
    ET0 = 1;
    TR0 = 1;
}

void pwm_stop(void)
{
    ET0 = 0;
    TR0 = 0;
}
