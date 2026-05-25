; ft_strcmp
; int strcmp(const char *s1, const char *s2);

section .text
	global ft_strcmp

ft_strcmp
	xor rax, rax
.loop:
.done: