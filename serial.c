#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "interrupt.h"
#include "serial.h"

static void (*s_callback)(int);
volatile unsigned char serial_tx = 0;
static unsigned char serial_crlf[] = "\r\n";

#ifdef SDCC
void serial_isr (void) __interrupt (4)
#else
void serial_isr (void) interrupt 4
#endif
{
    if(RI) {
        RI = 0;
        (*s_callback)((int)SBUF);
    }

    if(TI) {
        TI = 0;
        serial_tx = 0;
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
    ET1 =   0;
    EA  =   1;

    TI  =   0;
    RI  =   0;

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
    serial_tx = 1;
    SBUF = c;
    while(serial_tx);
}

void serial_puts(unsigned char *s)
{
    for(; *s; s++) {
        serial_putchar(*s);
    }
    
    s = serial_crlf;
    for(; *s; s++) {
        serial_putchar(*s);
    }
}
