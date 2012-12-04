#define SMOD_SM0b   (1<<7)
#define SMOD_SM1b   (1<<6)
#define SMOD_SM2b   (1<<5)
#define SMOD_RENb   (1<<4)
#define SMOD_TB8b   (1<<3)
#define SMOD_RB8b   (1<<2)
#define SMOD_TIb    (1<<1)
#define SMOD_RIb    (1<<0)

#define SMODE_0     (0)
#define SMODE_1     (SMOD_SM1b)
#define SMODE_2     (SMOD_SM0b)
#define SMODE_3     (SMOD_SM0b|SMOD_SM1b)

#define S1N8        (SMODE_1)
#define SINIT       (SMOD_RENb)

/*
Fosc (MHz) 11.0592
 Baudrate
    150      40h
    300      A0h
    600      D0h
   1200      E8h
   2400      F4h
   4800
   4800      FAh
   9600      FDh
   9600
  19200      FDh
  38400
  76800
  */

#define SBR_9600    (0xfd)

#ifdef SDCC
void serial_isr (void) __interrupt (4);
#else
void serial_isr (void);
#endif
void serial_init(void (*callback)(int));
void serial_putchar(char);
void serial_puts(unsigned char *);
int serial_getchar(void);
