.PHONY: clean
.SUFFIXES: .c .rel

CC= sdcc
CFLAGS= -mmcs51

OBJS= adc.rel main.rel pid.rel pwm.rel serial.rel
TARGET= crab

.c.rel:
	$(CC) $(CFLAGS) -c $<

$(TARGET).hex: $(OBJS) delay.rel
	$(CC) $(CFLAGS) $(OBJS) delay.rel -o $(TARGET)-i.hex
	packihx $(TARGET)-i.hex > $(TARGET).hex
delay.rel:
	sdas8051 -plosgffw delay.rel delay-sdcc.a51
clean:
	rm *.hex *.ihx *.lk *.lst *.map *.mem *.rel \
	*.rst *.sym *.asm 
