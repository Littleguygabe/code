		B	test_readstring

trs_prompt	DEFB 	"Enter a string:",0
trs_report	DEFB	"You entered:",0

		ALIGN

;; Do not modify this test code here, insert your code at strcpy below...
test_readstring
		MOV		R13,#0x10000

		ADRL	R0, trs_prompt
		SWI		3

		ADRL	R0,trs_str
		BL		ReadString

		ADRL	R0,trs_report
		SWI		3

		ADRL	R0,trs_str
		SWI		3

		MOV		R0,#10
		SWI		0
		SWI		2



;; ReadString -- read a string from the keyboard until ENTER/RETURN is pressed
;; 
;; R0 address to place string

ReadString
;; Insert your code here
	MOV R1,R0

getchar
	SWI 1s
	CMP R0,#10
	BEQ finish
		
	
	STRB R0,[R1]
	ADD R1,R1,#1

	SWI 0

	B getchar

finish
	MOV R0,#0
	STRB R0,[R1]

	BX LR


;; DO NOT REMOVE THIS LABEL AFTER YOUR CODE
trs_str	DEFW	0
