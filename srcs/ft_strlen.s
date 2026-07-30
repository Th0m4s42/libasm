;========================================================================================
; FILE: ft_strlen.s
; DESCRIPTION: Assembly implementation of strlen - iterate through a string
; ARCHITECTURE: x86_64 (NASM syntax, System V ABI)
;========================================================================================

; Function prototype (reference):
;
;			size_t strlen(const char *s)
;
; @brief	Iterates through a NUL-terminated string, counting all bytes until
:			(but not including) the NUL terminator ('\0'), and returns the total
;			number of characters.
; @param	rdi - pointer to the NUL-terminated input string
; @return	rax - length of the string as a size_t (unsigned, always >= 0)

;========================================================================================
; DATA SECTION (not needed here, but kept for structure)
;========================================================================================

section .text
	global ft_strlen				; make the fonction(ft_strlen) visible

;========================================================================================
; FUNCTION: ft_strlen
; PURPOSE:	Computes the length of a NUL-terminated string.
;			The length is defined as the number of bytes BEFORE
;			the first NUL terminator ('\0', value 0x00).
; STACK:    None — all values live in registers (no locals).
; CLOBBERS:	Nothing. All registers used are caller-saved or
;           explicitly managed (rax is the return register and
;           is overwritten, which is expected).
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