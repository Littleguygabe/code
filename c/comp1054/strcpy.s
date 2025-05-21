		B	test_strcpy

tsc_string	DEFB	"Hello World",0
tsc_dest	DEFB	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",0
tsc_copied	DEFB	"Copied '",0
tsc_to		DEFB	"' to '",0
tsc_eol		DEFB	"'\n",0
		ALIGN

;; Do not modify this test code here, insert your code at strcpy below...
test_strcpy
		MOV		R13,#0x10000

		ADRL	R0,tsc_dest
		ADRL	R1,tsc_string
		BL		strcpy

		ADRL	R0,tsc_copied
		SWI		3

		ADRL	R0,tsc_string
		SWI		3

		ADRL	R0,tsc_to
		SWI		3

		ADRL	R0,tsc_dest
		SWI		3

		ADRL	R0,tsc_eol
		SWI		3

		SWI		2


;; strcpy -- copy the string at R1 to the address at R0
;; R0 <--- destination
;; R1 <--- source

strcpy
;; Insert your code here
	LDRB R2,[R1]
	CMP R2,#0
	BEQ finalCpy

	STRB R2,[R0]

	ADD R1,R1,#1
	ADD R0,R0,#1

	B strcpy

finalCpy
	MOV R2,#0
	STRB R2,[R0]
	BX LR