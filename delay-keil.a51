; delay.SRC generated from: delay.c
; COMPILER INVOKED BY:
;        C:\Keil\C51\BIN\C51.EXE delay.c LARGE BROWSE DEBUG OBJECTEXTEND


NAME	DELAY

?PR?delay_1ms?DELAY  SEGMENT CODE 
?PR?_delay_ms?DELAY  SEGMENT CODE 
	PUBLIC	_delay_ms
	PUBLIC	delay_1ms

; void delay_1ms(void) {
	RSEG  ?PR?delay_1ms?DELAY
delay_1ms:
	mov r7, #12h		;1
delay_1ms_inner:
	mov r6, #18h	;1
	djnz r6, $			;2
	djnz r7, delay_1ms_inner ;2
	ret	;2
; }
; END OF delay_1ms

; void delay_ms(unsigned char millis) {

	RSEG  ?PR?_delay_ms?DELAY
_delay_ms:
			; SOURCE LINE # 4
	;; r6 H r7 L
	mov a, r7 ;1
delay_ms_1:			
	mov r7, a ;1
delay_ms_2:
	mov r5, #3eh		;1
delay_ms_3:
	mov r4, #0ah	;1
	djnz r4, $			;2
	djnz r5, delay_ms_3 ;2
	djnz r7, delay_ms_2 ;2
	djnz r6, delay_ms_1 ;2
	ret	;2
; END OF _delay_ms
; 9216*(d * 256 + c) = d*(c*(b*(2*a + 1) + 2*b + 1) + 2*c + 1) + 2*d + 1

	END
	
; t = 9216, 
; t = (2*a + 1) * b + 2 * b + 1 + 2
; t = b * (2*a + 3) + 3
; t = 2ab + 3b + 3
; 9216 - 3 = 2ab + 3b
; 9213 = 2ab + 3b
; 9213/b = 2a + 3
; 9213 = 3 * 37 * 83 = 111 * 83
