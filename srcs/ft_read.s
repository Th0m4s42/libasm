; ft_read
; ssize_t read(int fd, void *buf, size_t count);

section .text
	global	ft_read
	extern	__errno_location

ft_read:
	xor		eax, eax
	syscall
	cmp		rax, 0
	jl		.error_handler
	ret

.error_handler:
	neg		rax
	mov		r8, rax
	call	__errno_location wrt ..plt
	mov		[rax], r8d
	mov		rax, -1
	ret