#include <string.h>
#include "types.h"
#include "delay.h"
#include "pid.h"
#include "serial.h"

void pid_init(pid_t *pid)
{
    pid->setpoint = 0;
    pid->previous_error = 0;
    pid->integral = 0;
    pid->kp.n = 1;
    pid->kp.d = 1;
    pid->ki.n = 1;
    pid->ki.d = 1;
    pid->kd.n = 1;
    pid->kd.d = 1;
    pid->dt.n = 1;
    pid->dt.d = 1;
}

signed int pid_process(pid_t *pid, signed int measured_value)
{
    signed int output;
    signed int error;
    signed int derivative;
        
    error = pid->setpoint - measured_value;
    pid->integral += (pid->dt.n * error) / pid->dt.d;
    derivative = (pid->dt.d * (error - pid->previous_error)
                    ) / pid->dt.n;
    
    output = 0;
    output += (pid->kp.n * error) / pid->kp.d;
    output += (pid->ki.n * pid->integral) / pid->ki.d;
    output += (pid->kd.n * derivative) / pid->kd.d;

    pid->previous_error = error;        
    
    delay_1ms();
    
    return output;
}

static pid_pair_t pid_pairs[] = {
    {"SP", PID_PSP},
    {"KP", PID_PKP},
    {"KI", PID_PKI},
    {"KD", PID_PKD},
    {"DT", PID_PDT},
};

void pid_tune(pid_t *pid, char *key, char *value) {
    unsigned char i;
    
    for(i = 0; i < sizeof(pid_pairs)/sizeof(pid_pairs[0]); i++) {
        pid_pair_t *pair = &pid_pairs[i];
        
        if(strcmp(pair->key, key)) {
            continue;
        }
        
        switch(pair->sym) {
        case PID_PSP:
            pid->setpoint = 1;
            break;
        case PID_PKP:
            pid->kp.n = 1;
            break;
        case PID_PKI:
            pid->ki.n = 1;
            break;
        case PID_PKD:
            pid->kd.n = 1;
            break;
        case PID_PDT:
            pid->dt.n = 1;
            break;
        }
        
        serial_putchar('a');
        serial_putchar('\r');
        serial_putchar('\n');
    }
}