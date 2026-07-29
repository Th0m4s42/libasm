;========================================================================================
; FILE: ft_strcmp.s
; DESCRIPTION: Assembly implementation of strcmp - compares two strings
; ARCHITECTURE: x86_64 (NASM syntax, System V ABI)
;========================================================================================

; Function prototype (reference):
;
;	int strcmp(const char *s1, const char *s2)
;
; @brief   Compares two null-terminated strings lexicographically.
;          Returns:
;            < 0 if s1 < s2
;            = 0 if s1 == s2
;            > 0 if s1 > s2
;
; @param   rdi - pointer to first string (s1)
; @param   rsi - pointer to second string (s2)
; @return  rax - integer result of comparison

;========================================================================================
; DATA SECTION (not needed here, but kept for structure)
;========================================================================================

section .text
	global ft_strcmp            ; Export the function symbol for external linking

;========================================================================================
; FUNCTION:	ft_strcmp
; PURPOSE:	Compare two strings character by character
; INPUT:	rdi = address of first string (s1)
;			rsi = address of second string (s2)
; OUTPUT:	rax = comparison result (< 0, 0, or > 0)
;========================================================================================

ft_strcmp:
	xor		rax, rax				; rax = 0 (initialize index to 0)
									; XOR is faster and smaller than "mov rax, 0"

.loop:								; Main comparison loop - compare byte by byte
	mov		cl, byte [rdi + rax]	; cl = load one byte from s1 at current index
									; rdi = base address of first string
									; rax = current index (offset from start)
									; byte [rdi + rax] accesses s1[index]

	mov		dl, byte [rsi + rax]	; dl = load one byte from s2 at current index
    								; rsi = base address of second string
    								; byte [rsi + rax] accesses s2[index]
    								; Now cl = s1[i], dl = s2[i]

	cmp		cl, dl					; Compare the two bytes (computes cl - dl)
    								; Sets CPU flags: ZF=1 if equal, SF=1 if cl < dl
    								; This comparison determines the return value

	jne		.done					; If bytes are NOT equal, jump to .done
									; "jne" = jump if not equal (checks ZF=0)

	test	cl, cl					; Check if current byte is null terminator '\0'
									; "test x, x" sets ZF=1 if x is zero
									; Equivalent to "cmp cl, 0" but smaller code

	jz		.done					; Exit point: strings differ OR one string ended
									; "jz" = jump if zero (ZF = 1 means cl == 0)
									; This means we reached the end of one/both strings

	inc		rax						; Increment index to move to next character
									; rax++ (equivalent to rax = rax + 1)

	jmp		.loop					; Go back to loop start for next character
									; Continue comparing until difference or end

.done:								; Exit point: strings differ OR one string ended
									; "movzx" extends 8-bit to 64-bit, filling with 0s
    								; rax now contains the byte from s1 (or 0)

	movzx	rax, cl					; Move cl into rax with zero-extension
									; "movzx" extends 8-bit to 64-bit, filling with 0s
									; rax now contains the byte from s1 (or 0)

	movzx	rdx, dl					; Move dl into rdx with zero-extension
									; rdx now contains the byte from s2 (or 0)

	sub		rax, rdx				; Compute final result: rax = rax - rdx

	ret								; Return to caller
									; Return value is in rax

;========================================================================================
; REGISTER SUMMARY:
;   rdi - first parameter: address of s1 (preserved by callee)
;   rsi - second parameter: address of s2 (preserved by callee)
;   rax - both index (loop counter) and return value
;   cl  - 8-bit: current byte from s1
;   dl  - 8-bit: current byte from s2
;
; HOW IT WORKS:
;   1. Initialize index to 0
;   2. Load s1[i] and s2[i] characters into cl and dl
;   3. If they differ -> compute (s1[i] - s2[i]) and return
;   4. If current char is '\0' -> strings are equal, return 0
;   5. Otherwise, increment index and repeat
;========================================================================================