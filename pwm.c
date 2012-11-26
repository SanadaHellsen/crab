void pwm_isr(void);
void pwm_init(void);
void pwm_start(int duty);
void pwm_stop(void);

#include <mcs51/8051.h>
#include "interrupt.h"

void pwm_isr(void)
{
    TR0 = 0;

    if(1) {
        (void)1;
    } else {
        (void)1;
    }

    TR0 = 1;
}

void pwm_init(void)
{
    TMOD &= 0xf0;
    TMOD |= 0x01;

    TH0 = 0;
    TL0 = 0;

    IE |= (IE_EAb|IE_ET0b);
}

void pwm_start(int duty)
{
    (void)duty;
    TR0 = 1;
}

void pwm_stop(void)
{
    TR0 = 0;
}
