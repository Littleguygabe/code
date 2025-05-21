		B	test_rmvwls

trv_string	DEFB	"HELLO WORLD",0
trv_becomes	DEFB	"' becomes '",0
trv_eol		DEFB	"'\n",0

		ALIGN

;; Do not modify this test code here, insert your code at strcpy below...
test_rmvwls
		MOV		R13,#0x10000

		MOV		R0,#39
		SWI		0
		ADRL	R0,trv_string
		SWI		3

		ADRL	R0,trv_becomes
		SWI		3

		ADRL	R0,trv_string
		BL		RemoveVowels

		ADRL	R0,trv_string
		SWI		3

		ADRL	R0,trv_eol
		SWI		3

		SWI		2


;; The line below copies your isVowel subroutine into this file automatically
;; IT IS NOT NECESSARY TO COPY THE SUBROUTINE MANUALLY

;; RemoveVowels -- remove any vowels in the string at R0 using the isVowel subroutine to identify vowels
;; R0 <-- string

RemoveVowels
    MOV R2, R0          ; Source pointer (start of the input string)
    MOV R3, R0          ; Destination pointer (start of the output string)

loop
    LDRB R0, [R2]       ; Load the current character into R0
    CMP R0, #0          ; Check if the character is the null terminator
    BEQ end             ; If it is, exit the loop

    PUSH {R0}           ; Save R0 (current character) on the stack
    BL isVowellocal     ; Call isVowellocal to check if the character is a vowel
    POP {R0}            ; Restore R0 (original character) from the stack

    ADD R2, R2, #1      ; Increment source pointer
    B loop              ; Repeat the loop

end
    BX LR               ; Return from the subroutine


isVowellocal
;; Insert your code here
	MOV R1,#'A'
	CMP R0,R1
	BEQ confirmVowel

	MOV R1,#'E'
	CMP R0,R1
	BEQ confirmVowel

	MOV R1,#'I'
	CMP R0,R1
	BEQ confirmVowel

	MOV R1,#'O'
	CMP R0,R1
	BEQ confirmVowel

	MOV R1,#'U'
	CMP R0,R1
	BEQ confirmVowel

	MOV R1,#0
	BX LR

confirmVowel
	MOV R1,#1
	BX LR