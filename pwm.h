//>>> int(11.0592e6/12)
//921600

#define CPU_SEC_TICKS 921600

void pwm_isr(void);
void pwm_init(unsigned int);
void pwm_start(unsigned int);
void pwm_stop(void);