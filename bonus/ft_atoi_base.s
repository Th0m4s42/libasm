;ft_atoi_base

;	int ft_atoi_base(char *str, char *base)
;	@convert a string to a integer
;	@the string to convert, the base used for the convertion
;	@return a integer

section .text
	global	ft_atoi_base
	extern	ft_strlen


is_whitespace:
	cmp		dil, ' '
	je		.yes
	cmp		dil, 9
	jb		.no
	cmp		dil, 13
	jbe		.yes
.no:
	xor		eax, eax
	ret
.yes:
	mov 	eax, 1
	ret

validate_base:
	sub		rsp, 8				; align stack for call
	mov		rdi, rsi
	push	rsi
	call	ft_strlen
	pop		rsi
	add		rsp, 8

	cmp		rax, 2
	jb		.invalid

	mov		rcx, rax
	xor		r8, r8				; r8 = 1 (index external loop)
.loop_i:
	cmp		r8, rcx
	jae		.valid

	movzx	edx, byte [rsi + r8] ; dl = base[i]

	cmp		dl, '+'
	je		.invalid
	cmp		dl, '-'
	je		.invalid

	push	rcx
	push	r8
	mov		dil, dl
	call	is_whitespace
	pop		r8
	pop		rcx
	test	al, al
	jnz		.invalid

	lea		r9, [r8 + 1]	; r9 = jae
.loop_j:
	cmp		r9, rcx
	jae		.next_i
	cmp		dl, [rsi + r9]
	je		.invalid
	inc		r9
	jmp		.loop_j

.next_i:
	inc		r8
	jmp		.loop_i

.valid:
	mov		rax, rcx
	ret
.invalid:
	xor		eax, eax			; Return 0
	ret

get_char_index:
	xor		rax, rax
.loop:
	cmp		rax, rcx
	jae		.notfound
	movzx	edx, byte [rsi + rax]
	cmp		dl, dil
	je		.done
	inc		rax
	jmp		.loop
.notfound:
	mov		rax, -1
.done:
	ret

ft_atoi_base:
	push	rbp
	mov		rbp, rsp
	push	rbx
	push	r12
	push	r13
	push	r14
	push	r15

	mov		r12, rdi
	mov		r13, rsi

	mov		rsi, r13
	call	validate_base
	test	rax, rax
	jz		.ret_zero
	mov		r14, rax

.skip_ws:
	movzx	edi, byte [r12]
	test		dil, dil
	jz		.done
	call	is_whitespace
	test	al, al
	jz		.parse_signs
	inc		r12
	jmp		.skip_ws

.parse_signs:
	mov		ebx, 1
.sign_loop:
	movzx	eax, byte [r12]
	cmp		al, '+'
	je		.plus
	cmp		al, '-'
	je		.minus
	jmp		.convert
.plus:
	inc		r12
	jmp		.sign_loop
.minus:
	neg		ebx
	inc		r12
	jmp		.sign_loop

.convert:
	xor		r15, r15
.cv_loop:
	movzx	edi, byte [r12]
	test	dil, dil
	jz		.done

	mov		rsi, r13
	mov		rcx, r14
	call	get_char_index

	test	rax, rax
	js		.done				; if négatif (-1), stop

	imul	r15, r14
	add		r15, rax

	inc		r12
	jmp		.cv_loop

.done:
	movsx	rbx, ebx
	imul	r15, rbx
	mov		rax, r15
	jmp		.epilogue

.ret_zero:
	xor		eax, eax

.epilogue:
	pop		r15
	pop		r14
	pop		r13
	pop		r12
	pop		rbx
	pop		rbp
	ret
