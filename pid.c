#include "types.h"
#include "delay.h"
#include "pid.h"
#include "serial.h"
#include "string.h"

static pid_t pid;

void pid_init(void)
{
    pid.setpoint = 127;
    pid.previous_error = 0;
    pid.integral = 0;
    pid.kp.n = 5;
    pid.kp.d = 1;
    pid.ki.n = 1;
    pid.ki.d = 100;
    pid.kd.n = 1;
    pid.kd.d = 10;
    pid.sense = 1;
}

signed int pid_process(signed int measured_value)
{
    signed int output;
    signed int error;
    signed int derivative;
        
    error = pid.setpoint - measured_value;
    
    pid.integral += error;
    if(pid.integral > PID_INTEGRAL_MAX) {
        pid.integral = PID_INTEGRAL_MAX;
    } else if(pid.integral < PID_INTEGRAL_MIN) {
        pid.integral = PID_INTEGRAL_MIN;
    }
    
    derivative = error - pid.previous_error;
    
    output = 0;
    output += (pid.kp.n * error) / pid.kp.d;
    output += (pid.ki.n * pid.integral) / pid.ki.d;
    output += (pid.kd.n * derivative) / pid.kd.d;

    pid.previous_error = error;        
            
    do {
        unsigned char j;
        for(j = 0; j < 100; j++) {
            delay_1ms();
        }
    } while(0);
    
    if(pid.sense) {
        output *= -1;
    }
    
    return output;
}

void pid_tune(char *key, char *value) {
    unsigned char *p = value;
    unsigned char s = 0;
    
    while(*p && *p != '/') p++;
    
    if(*p == '/') {
        s = 1;
        
        *p = '\0';
        p++;
    }
    
    if(key[0] == 'S' && key[1] == 'P') {
        pid.setpoint = atoi_(value);
    } else
    if(key[0] == 'K' && key[1] == 'P') {
        pid.kp.n = atoi_(value);
        if(s) {
            pid.kp.d = atoi_(p);
        } else {
            pid.kp.d = 1;
        }
    } else
    if(key[0] == 'K' && key[1] == 'I') {
        pid.ki.n = atoi_(value);
        if(s) {
            pid.ki.d = atoi_(p);
        } else {
            pid.ki.d = 1;
        }
    } else
    if(key[0] == 'K' && key[1] == 'D') {
        pid.kd.n = atoi_(value);
        if(s) {
            pid.kd.d = atoi_(p);
        } else {
            pid.kd.d = 1;
        }
    }
    if(key[0] == 'P' && key[1] == 'S') {
        pid.sense = atoi_(value);
    }
}
