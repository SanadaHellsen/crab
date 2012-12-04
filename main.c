#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include <string.h>
#include "types.h"

#include "adc.h"
#include "delay.h"
#include "pid.h"
#include "pwm.h"
#include "serial.h"

enum cmd_type {
    PID_CMD,
    UNKNOWN_CMD
};

typedef struct cmd {
    unsigned char header[3];
    enum cmd_type type;
    unsigned char key[7];
    unsigned char value[7];
} cmd_t;
/*
#define BUFLEN 16
static cmd_t cmd;
volatile unsigned char serial_rx = 0;
volatile unsigned char bi = 0;
volatile unsigned char buffer[BUFLEN];*/
static unsigned char msg_ok[] = "OK\r\n";

void command_execute(char *);
unsigned char command_parse(char *);
/*
unsigned char command_parse(char *string)
{
    unsigned char i;
    unsigned char *key, *value;
    
    // HHTKKK...=VVV...
    memcpy(cmd.header, string, 2);
    cmd.header[2] = '\0';
    
    if(strcmp(cmd.header, "SB")) {
        return 0;
    }
    
    switch(string[2]) {
    case 'P':
        cmd.type = PID_CMD;
        break;
    default:
        cmd.type = UNKNOWN_CMD;
    }
    
    key = &string[3];
    value = key;
    i = 0;
    while(*value && *value != '=' && i < sizeof(cmd.key)) {
        value++;
    }
    *value = '\0';
    value++;
    
    strncpy(cmd.key, key, sizeof(cmd.key));
    cmd.key[sizeof(cmd.key)-1] = '\0';
    strncpy(cmd.value, value, sizeof(cmd.value));
    cmd.value[sizeof(cmd.value)-1] = '\0';

    return 1;
}

void command_execute(char *string)
{
    if(!command_parse(string)) {
        return;
    }
    
    serial_puts(msg_ok);

    switch(cmd.type) {
    case PID_CMD:
        pid_tune(cmd.key, cmd.value);
        break;
    }
}*/
/*
void serial_cb(int c) {

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
*/
void main(void)
{
    unsigned char adc_value;
    signed int pid_output;
    
/*
    adc_init();
    pid_init();*/
    pwm_init(18432);
    /*serial_init(serial_cb);*/
    
    /*serial_puts(msg_ok);*/

    pwm_start(1843);
        
    while(1) {
        /*if(serial_rx) {
            command_execute(buffer);
            serial_rx = 0;
        }*/

        P0_1 = 1;
        delay_ms(1000);
        P0_1 = 0;
        delay_ms(1000);
        P0_1 = 1;
        delay_ms(2000);
        P0_1 = 0;
        delay_ms(2000);
        /*adc_value = adc_read();
        pid_output = pid_process(adc_value);*/
        /*pwm_start(666 + pid_output);*/
    }
}
