#include <mcs51/8051.h>
#include "interrupt.h"
#include "serial.h"

volatile char serial_buf[2][SBUFN];
volatile int  serial_i[2];
volatile char sr;
volatile char st;
static void (*s_callback)(int);


void serial_isr (void) __interrupt (4)
{
    if(RI) {
        sr =  SBUF;
        (*s_callback)((int)sr);
        RI = 0;
    } else {
        //SBUF = serial_buf[1][0];
        TI = 0;
    }
}

void serial_init(void (*callback)(int))
{
    IE |=   (IE_EAb|IE_ESb);
    //IE &=   ~IE_ET1b;

    SCON =   SINIT | S1N8;

    TMOD &=  0x0f;
    TMOD |=  0x20;

    TH1 =    SBR_9600;
    TR1 =    1;

    s_callback = callback;
}

int serial_getchar(void)
{
    char c, es;

    es = ES;
    ES = 0;
    while(!RI);
    c = SBUF;
    RI = 0;
    ES = es;

    return (int)c;
}

void serial_putchar(char c)
{
    char es;

    es = ES;
    ES = 0;
    while(TI);
    SBUF = c;
    while(!TI);
    ES = es;
}

