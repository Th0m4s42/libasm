; ft_write
; ssize_t write(int fd, const void *buf, size_t count);

section .text
	global	ft_write
	extern	__errno_location

ft_write:
	mov		rax, 1
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