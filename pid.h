#define PID_INTEGRAL_MAX  1000
#define PID_INTEGRAL_MIN -1000

typedef struct pid {
    signed int  setpoint;
    signed int  previous_error;
    signed int  integral;
    decimal_t   kp;
    decimal_t   ki;
    decimal_t   kd;
    decimal_t   dt;
} pid_t;
/*
enum pid_key {
    PID_PSP,
    PID_PKP,
    PID_PKI,
    PID_PKD,
    PID_PAK,
    PID_PDT
};

typedef struct pid_pair {
    unsigned char key[3];
    enum pid_key sym;
} pid_pair_t;
*/
void pid_init();
signed int pid_process(signed int);
void pid_tune(char *key, char *value);
