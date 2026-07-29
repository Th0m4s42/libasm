;	ft_write

;=========================================================================
;	ssize_t write(int fd, const void *buf, size_t count)
;@brief	
;@param	
;@return	
;=========================================================================

section .text
	global	ft_write						;
	extern	__errno_location				;

ft_write:
	mov		rax, 1							;
	syscall									;
	test	rax, rax						;
	js		.error_handler					;
	ret										;

.error_handler:
	neg		rax								;
	push	rax								;
	call	__errno_location wrt ..plt		;
	pop		rdi								;
	mov		[rax], edi						;
	mov		rax, -1							;
	ret										;