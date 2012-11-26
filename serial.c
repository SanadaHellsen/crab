#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "interrupt.h"
#include "serial.h"

volatile char serial_buf[2][SBUFN];
volatile int  serial_i[2];
volatile char sr;
volatile char st;
static void (*s_callback)(int);

#ifdef SDCC
void serial_isr (void) __interrupt (4)
#else
void serial_isr (void) interrupt 4
#endif
{
    if(RI) {
        RI = 0;
        sr =  SBUF;
        (*s_callback)((int)sr);
    } else {
        if(serial_i[1] > 0) {
            //SBUF = serial_buf[1][0];
            serial_i[1]--;
        }
        TI = 0;
    }
}

void serial_init(void (*callback)(int))
{
    SCON =   SINIT | S1N8;

    TMOD &=  0x0f;
    TMOD |=  0x20;

    TH1 =   SBR_9600;
    TL1 =   SBR_9600;
    ES  =   1;
    EA  =   1;

    s_callback = callback;
    
    TR1 =   1;
}

int serial_getchar(void)
{
    char c;

    while(!RI);
    c = SBUF;

    return (int)c;
}

void serial_putchar(char c)
{
    int k = 1;
    serial_i[1]++;
    serial_buf[1][0] = c;
    SBUF = serial_buf[1][0];
    TI = 1;
    while(k++) {
        if(!TI) break;
    }
}

