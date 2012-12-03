#define ADCB P2
#ifdef SDCC
#define PWMb P0_0
#else
sbit PWMb = P0^0;  
#endif
