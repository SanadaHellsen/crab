#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "delay.h"
#include "pid.h"
#include "serial.h"

static pid_t pid;

void pid_init(void)
{
    pid.setpoint = 0;
    pid.previous_error = 0;
    pid.integral = 0;
    pid.kp.n = 1;
    pid.kp.d = 1;
    pid.ki.n = 1;
    pid.ki.d = 1;
    pid.kd.n = 1;
    pid.kd.d = 1;
    pid.dt.n = 100;
    pid.dt.d = 1;
}

signed int pid_process(signed int measured_value)
{
    signed int output;
    signed int error;
    signed int derivative;
        
    error = pid.setpoint - measured_value;
    pid.integral += (pid.dt.n * error) / pid.dt.d;
    derivative = (pid.dt.d * (error - pid.previous_error)
                    ) / pid.dt.n;
    
    output = 0;
    output += (pid.kp.n * error) / pid.kp.d;
    output += (pid.ki.n * pid.integral) / pid.ki.d;
    output += (pid.kd.n * derivative) / pid.kd.d;

    pid.previous_error = error;        
    
    delay_1ms(); // delay_ms(pid.dt.d)
    
    return output;
}

void pid_tune(char *key, char *value) {
    if(key[0] == 'S' && key[1] == 'P') {
        pid.setpoint = atoi(value);
    } else
    if(key[0] == 'K' && key[1] == 'P') {
        pid.kp.n = atoi(value);
    } else
    if(key[0] == 'K' && key[1] == 'I') {
        pid.ki.n = atoi(value);
    } else
    if(key[0] == 'K' && key[1] == 'D') {
        pid.kd.n = atoi(value);
    } else
    if(key[0] == 'D' && key[1] == 'T') {
        pid.dt.n = atoi(value);
    }
}
