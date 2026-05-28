; ft_strcmp
; int strcmp(const char *s1, const char *s2);

section .text
	global ft_strcmp

ft_strcmp
	xor			rax, rax				;

.loop:
	mov			cl, byte [rdi + rax]	;
	mov			cl, byte [rsi + rax]	;
	cmp			cl, dl					;
	jne			.done					;
	test		cl, cl					;
	jz			.done					;
	inc			rax						;
	jmp			loop					;

.done:
	movxz		rax, cl					;
	movxz		rdx, dl					;
	sub			rax - rdx				;
	ret									;