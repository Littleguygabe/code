		B	test_cwrdl

tcwrdl_string	DEFB	"THE CAT SAT ON THE MAT",0

		ALIGN

;; Do not modify this test code here, insert your code at strcpy below...
test_cwrdl
		MOV		R13,#0x10000

		ADRL	R0,tcwrdl_string
		SWI		3

		ADRL	R0,tcwrdl_string
		ADRL	R1,tcwrdl_array
		BL		CountWordLengths
		MOV		R3,R0
		MOV		R0,#10
		SWI		0

		MOV		R2,#0
		ADRL	R1,tcwrdl_array
		B		tcwrdl_cond
tcwrdl_loop
		LDR		R0, [R1, R2 LSL #2]
		SWI		4
		MOV		R0,#10
		SWI		0
		ADD		R2,R2,#1
tcwrdl_cond
		CMP		R2,R3
		BLT		tcwrdl_loop

		SWI		2


;; CountWordLengths -- fill in an array with the length of each word in the string
;; R0 <-- string
;; R1 <-- array to file
;; Returns: The number of words found in R0.

CountWordLengths
    MOV R2, #0
    MOV R4, #0

loop
    LDRB R3, [R0]
    CMP R3, #0
    BEQ terminate

    CMP R3, #32
    BEQ newWord

    ADD R0, R0, #1
    ADD R2, R2, #1
    B loop

newWord
    CMP R2, #0
    BEQ skipWord

    STR R2, [R1], #4
    ADD R4, R4, #1
    MOV R2, #0

skipWord
    ADD R0, R0, #1
    B loop

terminate
    CMP R2, #0
    BEQ endCount

    STR R2, [R1], #4
    ADD R4, R4, #1

endCount
    MOV R0, R4
    BX LR


;; DO NOT REMOVE THIS LABEL
tcwrdl_array	DEFW	0	
