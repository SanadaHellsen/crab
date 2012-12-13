#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include "config.h"
#include "types.h"

#include "interrupt.h"
#include "serial.h"

static void (*s_callback)(int);
volatile unsigned char serial_tx = 0;

unsigned char code msg_ok[] = MSG_OK;
unsigned char code msg_error[] = MSG_ERROR;
//unsigned char code serial_crlf[] = "\r\n";

#ifdef SDCC
void serial_isr (void) __interrupt (4)
#else
void serial_isr (void) interrupt 4
#endif
{
    if(RI) {
        RI = 0;
        (*s_callback)((int)SBUF);
    } else {
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

    IE |=  (IE_ESb|IE_EAb);
    IE &= ~(IE_ET1b);

    s_callback = callback;
    
    TR1 =   1;
}

int serial_getchar(void)
{
    while(!RI);
    return (int)SBUF;
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
    
    /*s = serial_crlf;
    for(; *s; s++) {
        serial_putchar(*s);
    }*/
    
    serial_putchar('\r');
    serial_putchar('\n');
}
