; ft_strcpy
; char *strcpy(char *dst, const char *src)

section .text
	global ft_strcpy

ft_strcpy
	mov		rax, rdi

.loop:
	mov		cl, byte [rsi]
	mov		byte [rdi], cli
	test	cl, cl
	jz		.done
	inc		rsi
	inc		rdi
	jmp		.loop

.done:
	ret