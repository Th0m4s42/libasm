;	ft_strdup
;=========================================================================
;	char *strdup(const char *s)
;@brief   
;@param 
;@return 
;=========================================================================

section .text
	global	ft_strdup
	extern	ft_strlen
	extern	ft_strcpy
	extern	malloc

ft_strdup:
	push	rbx					;
	mov		rbx, rdi			;
	call	ft_strlen			;
	inc		rax					;
	mov		rdi, rax			;
	call	malloc wrt ..plt	;
	test	rax, rax			;
	jz		.done				;
	mov		rdi, rax			;
	mov		rsi, rbx			;
	call	ft_strcpy			;

.done:
	pop		rbx					;
	ret							;