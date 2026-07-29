;	ft_read

;=========================================================================
;	ssize_t read(int fd, void *buf, size_t count)
;@brief 
;@param 
;@return 
;=========================================================================

section .text
	global	ft_read
	extern	__errno_location

ft_read:
	xor		eax, eax					;
	syscall								;
	test	rax, rax					;
	js		.error_handler				;
	ret									;

.error_handler:
	neg		rax							;
	push	rax							;
	call	__errno_location wrt ..plt	;
	pop		rdi							;
	mov		[rax], edi					;
	mov		rax, -1						;
	ret									;