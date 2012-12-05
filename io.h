#define ADCB P2
#ifdef SDCC
#define PWMb P1_0
#else
sbit PWMb = P1^0;  
#endif
