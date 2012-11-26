.PHONY: clean
.SUFFIXES: .c .rel

OBJS= serial.rel pwm.rel main.rel
TARGET= crab

.c.rel:
	sdcc -mmcs51 -c $<

$(TARGET).hex: $(OBJS)
	sdcc -mmcs51 $(OBJS) -o $(TARGET)-i.hex
	packihx $(TARGET)-i.hex > $(TARGET).hex
clean:
	rm *.asm *.hex *.ihx *.lk *.lst *.map *.mem *.rel *.rst *.sym
