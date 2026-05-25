; ft_strlen
; size_t strlen(const char *s)

section .text
	global ft_strlen				; make ft_strlen visible

ft_strlen:
	xor		rax, rax				; put rax to 0
.loop:
	cmp		byte [rdi + rax], 0		; compare  to '\0'
	je		.done					; if yes jump to done
	inc		rax			 			; increment rax
	jmp		.loop					; jump to loop
.done:
	ret								; return rax