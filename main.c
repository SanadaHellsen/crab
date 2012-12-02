#ifdef SDCC
#include <mcs51/8051.h>
#else
#include <regx51.h>
#endif

#include <string.h>
#include "types.h"

#include "adc.h"
#include "pid.h"
#include "pwm.h"
#include "serial.h"

static pid_t pid;

enum cmd_type {
    PID_CMD,
    UNKNOWN_CMD
};

typedef struct cmd {
    unsigned char header[3];
    enum cmd_type type;
    unsigned char key[15];
    unsigned char value[15];
} cmd_t;

static decimal_t adc_k  = {1, 1};

void command_execute(char *);
unsigned char command_parse(cmd_t *, char *);

unsigned char command_parse(cmd_t *cmd, char *string)
{
    //unsigned char i;
    unsigned char *key, *value;
    
    // HHTKKK...=VVV...
    memcpy(cmd->header, string, 2);
    cmd->header[2] = '\0';
    
    if(strcmp(cmd->header, "SB")) {
        return 0;
    }
    
    switch(string[2]) {
    case 'P':
    case 'p':
        cmd->type = PID_CMD;
    default:
        cmd->type = UNKNOWN_CMD;
    }
    
    key = &string[3];
    value = key;
    while(*value && *value != '=') {
        value++;
    }
    value = '\0';
    value++;
    
    strcpy(cmd->key, key);
    strcpy(cmd->value, value);
    
    return 1;
}

void command_execute(char *string)
{
    cmd_t cmd;
    
    if(!command_parse(&cmd, string)) {
        return;
    }
    
    switch(cmd.type) {
    case PID_CMD:
        pid_tune(&pid, cmd.key, cmd.value);
        break;
    default:
        break;
    }
}

#define BUF_LEN 25
void serial_cb(int c) {
    static unsigned char i = 0;
    static unsigned char buffer[BUF_LEN];

    if(i >= BUF_LEN) {
        i = 0;
    }
    
    buffer[i] = c;
    
    if('\r' == c || '\n' == c) {
        buffer[i] = '\0';
        command_execute(buffer);
	    i = 0;
    } else {
        i++;
    }
}

int main(void)
{
    unsigned char adc_v;
    signed int pid_v, pid_y;
    
    /*
    666
    800
    571
    */
    // 1/0.02 = 50
    pwm_init(50);
    adc_init();
    pid_init(&pid);
    serial_init(serial_cb);
    
    pwm_start(666);
    
    while(1) {
        adc_v = adc_read();
        pid_v = (adc_k.n * adc_v) / adc_k.d;
        pid_y = pid_process(&pid, pid_v);
        pwm_start(666 + pid_y);
    }
    
    pwm_stop();
    
    return 0;
}
