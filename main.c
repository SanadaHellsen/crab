#include <mcs51/8051.h>
#include <string.h>
#include "serial.h"
#include "pwm.h"

char buffer[25];
char i;

void serial_cb(int c) {
    char *p;

    if(i < 24) {
        buffer[++i] = c;
        if('\r' == c || '\n' == c) {
            buffer[i] = '\0';
            p = buffer;

            if(!strcmp(buffer, "ZYX")) {
                while(*p) {
                    serial_putchar(*p);
                    serial_putchar('\r');
                    serial_putchar('\n');
                    p++;
                }
            }
        }
    }
}

int main(void)
{
    serial_init(serial_cb);
    while(1);
    return 0;
}
