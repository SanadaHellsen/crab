    .globl _delay_1ms
    .area CSEG (CODE)
_delay_1ms:
    mov r7, #0x24
_delay_1ms_inner:
    mov r6, #0xff
_delay_1ms_inner2:
    djnz r6, _delay_1ms_inner2
    djnz r7, _delay_1ms_inner
    ret
