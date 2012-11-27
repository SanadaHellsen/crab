; delay.SRC generated from: delay.c
; COMPILER INVOKED BY:
;        C:\Keil\C51\BIN\C51.EXE delay.c LARGE BROWSE DEBUG OBJECTEXTEND


NAME	DELAY

?PR?delay_1ms?DELAY  SEGMENT CODE 
?PR?_delay_ms?DELAY  SEGMENT CODE 
?XD?_delay_ms?DELAY  SEGMENT XDATA OVERLAYABLE 
	PUBLIC	_delay_ms
	PUBLIC	delay_1ms

	RSEG  ?XD?_delay_ms?DELAY
?_delay_ms?BYTE:
     millis?140:   DS   1

; void delay_1ms(void) {
	RSEG  ?PR?delay_1ms?DELAY
delay_1ms:
	mov r7, #024h		;1
delay_1ms_inner:
	mov r6, #0ffh	;1
	djnz r6, $			;2
	djnz r7, delay_1ms_inner ;2
	ret	;2
; }
; END OF delay_1ms

; void delay_ms(unsigned char millis) {

	RSEG  ?PR?_delay_ms?DELAY
_delay_ms:
			; SOURCE LINE # 4
	MOV  	DPTR,#millis?140
	MOV  	A,R7
	MOVX 	@DPTR,A
; }			; SOURCE LINE # 5
	RET  	
; END OF _delay_ms

	END

	
; t = 9216, 
; t = (2*a + 1) * b + 2 * b + 1 + 2
; t = b * (2*a + 3) + 3
; t = 2ab + 3b + 3
; 9216 - 3 = 2ab + 3b
; 9213 = 2ab + 3b
; 9213/b = 2a + 3
; 9213 = 3 * 37 * 83 = 111 * 83
; b = 83 (0x53)
; 111 = 2a + 3
; 108 = 2a
; a = 54 (0x36)
;>>> a = 54
;>>> b = 83
;>>> (2*a + 1) * b + 2 * b + 1 + 2
;9216