#include "config.h"
#include "types.h"

#include "cmd.h"
#include "pid.h"
#include "pwm.h"
#include "serial.h"
#include "string.h"

static cmd_t cmd;
static unsigned char code cmd_hdr[] = CMD_HDR;

unsigned char cmd_parse(char *string)
{
    unsigned char *key, *value;
    
    // HHTKKK...=VVV...
    cmd.header[0] = string[0];
    cmd.header[1] = string[1];
    cmd.header[2] = '\0';
    
    if(0 != memcmp_(cmd.header, cmd_hdr, 3)) {
        return 0;
    }
    
    switch(string[2]) {
    case 'P':
        cmd.type = PID_CMD;
        break;
    case 'S':
        cmd.type = SERVO_CMD;
        break;    
    default:
        cmd.type = UNKNOWN_CMD;
        return 0;
    }
    
    key = &string[3];
    value = key;
    while(*value && *value != '=') {
        value++;
    }
    *value = '\0';
    value++;
    
    strcpy_(cmd.key, key);
    strcpy_(cmd.value, value);
    
    return 1;
}

void cmd_execute(char *string)
{
    if(!cmd_parse(string)) {
        serial_puts(msg_error);
        return;
    }
    
    serial_puts(msg_ok);

    switch(cmd.type) {
    case PID_CMD:
        pid_tune(cmd.key, cmd.value);
        break;
    case SERVO_CMD:
        pwm_start(SERVO_MIN);
        break;
    }
}