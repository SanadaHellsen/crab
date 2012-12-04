    .globl _delay_1ms
    .area CSEG (CODE)
_delay_1ms:
    mov r7, #0x12
_delay_1ms_inner:
    mov r6, #0x18
_delay_1ms_inner2:
    djnz r6, _delay_1ms_inner2
    djnz r7, _delay_1ms_inner
    ret

    .globl _delay_ms
    .area CSEG (CODE)
_delay_ms:
	mov a, r7 ;1
_delay_ms_1:			
	mov r7, a ;1
_delay_ms_2:
	mov r5, #3eh		;1
_delay_ms_3:
	mov r4, #0ah	;1
_delay_ms_4:
	djnz r4, _delay_ms_4 ;2
	djnz r5, _delay_ms_3 ;2
	djnz r7, _delay_ms_2 ;2
	djnz r6, _delay_ms_1 ;2
	ret	;2
