;========================================================================================
; FILE: ft_strlen.s
; DESCRIPTION: Assembly implementation of strlen - iterate through a string
; ARCHITECTURE: x86_64 (NASM syntax, System V ABI)
;========================================================================================

; Function prototype (reference):
;
;	size_t strlen(const char *s)
;
; @brief	iterate through a string.
; 			Return:
; 				size of the string
;
; @param	rdi - string to iterate
; @return	rax - integer result of incrementation

;========================================================================================
; DATA SECTION (not needed here, but kept for structure)
;========================================================================================

section .text
	global ft_strlen				; make the fonction(ft_strlen) visible

;========================================================================================
; FUNCTION: ft_strlen
; PURPOSE:  Iterate on a string to calculate its lenght
; INPUT:    rdi = address of the string (s1)
; OUTPUT:   rax = incrementation
;========================================================================================

ft_strlen:
	xor		rax, rax				; put rax to 0

.loop:
	cmp		byte [rdi + rax], 0		; compare to '\0'
	je		.done					; if yes jump to done
	inc		rax			 			; increment rax
	jmp		.loop					; jump to loop

.done:
	ret								; return rax