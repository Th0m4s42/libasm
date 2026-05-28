; ft_write
; ssize_t write(int fd, const void buf[count], size_t count);

section .text
	global ft_write

ft_write
	xor			rax, rax ;

.loop

.error_handler.

.done
	ret