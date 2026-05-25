; ft_strlen

section .text
	global ft_strlen				; make ft_strlen visible

ft_strlen:
	xor		rax, rax				; put rax to 0
.loop:
	cmp		byte [rdi + rax], 0		; compare  to '\0'
	je		.end					; if yes jump to end
	inc		rax			 			; increment rax
	jmp		.loop					; jump to loop
.end:
	ret								; return rax