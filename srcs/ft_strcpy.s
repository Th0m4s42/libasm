; ft_strcpy
; char *strcpy(char *dst, const char *src)

section .text
	global ft_strcpy			; make ft_strcpy visible

ft_strcpy
	mov		rax, rdi			; put first argument (destinaion) in accumalotor(rax)

.loop:
	mov		cl, byte [rsi]		; read from source
	mov		byte [rdi], cl		; write in destination
	test	cl, cl				; test if cl equal zero and put the flag up to date
	jz		.done				; go to done if test equal to zero
	inc		rsi					; increment second argument (source)
	inc		rdi					; increment first argument (destination)
	jmp		.loop				; go to loop again

.done:
	ret							; return rax value