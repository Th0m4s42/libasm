; ft_atoi_base
; int ft_atoi_base(char *str, char *base)

section .text
	global	ft_atoi_base
	extern	ft_strlen

check_base:
	sub		rsp, 8				; align stack for call
	mov		rdi, rsi
	call	ft_strlen
	add		rsp, 8
	cmp		rax, 2
	jl		.invalid

	xor		rcx, rcx
.outer:
	cmp		rcx, rax
	jge		.valid
	mov		dl, [rsi + rcx]
	cmp		dl, '+'
	je		.invalid
	cmp		dl, '-'
	je		.invalid
	cmp		dl, ' '
	je		.invalid
	cmp		dl, 9
	jl		.ok_char
	cmp		dl, 13
	jle		.invalid
.ok_char:
	lea		r8, [rcx + 1]
.inner:
	cmp		r8, rax
	jge		.next
	cmp		dl, [rsi + r8]
	je		.invalid
	inc		r8
	jmp		.inner
.next:
	inc		rcx
	jmp		.outer

.invalid:
	xor		eax, eax
.valid:
	ret

find_char:
	xor		rax, rax
.loop:
	cmp		rax, rcx
	jge		.notfound
	cmp		dil, [rsi + rax]
	je		.done
	inc		rax
	jmp		.loop
.notfound:
	mov		rax, -1
.done:
	ret

ft_atoi_base:
	push	rbx
	push	r12
	push	r13
	push	r14
	push	r15

	mov		r12, rdi
	mov		r13, rsi

	mov		rsi, r13
	call	check_base
	test	rax, rax
	jz		.ret_zero
	mov		r14, rax

.skip_ws:
	movzx	eax, byte [r12]
	cmp		al, ' '
	je		.adv
	cmp		al, 9
	jl		.signs
	cmp		al, 13
	jle		.adv
	jmp		.signs
.adv:
	inc		r12
	jmp		.skip_ws

.signs:
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
	call	find_char
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
	ret
