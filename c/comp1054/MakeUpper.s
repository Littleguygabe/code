		B	test_makeupper

tmu_string	DEFB	"Hello World",0
tmu_becomes	DEFB	"' becomes '",0
tmu_eol		DEFB	"'\n",0
		ALIGN

;; Do not modify this test code here, insert your code at strcpy below...
test_makeupper
		MOV		R13,#0x10000

		MOV		R0,#39
		SWI		0
		ADRL	R0,tmu_string
		SWI		3

		ADRL	R0,tmu_becomes
		SWI		3

		ADRL	R0,tmu_string
		BL		MakeUpper

		ADRL	R0,tmu_string
		SWI		3

		ADRL	R0,tmu_eol
		SWI		3

		SWI		2


;; MakeUpper -- convert the string at R0 to upper case (capital letters) in place
;; MakeUpper
;; R0 string


MakeUpper
;; Insert your code here
	LDRB R1,[R0]
	CMP R1,#0
	BEQ end

	CMP R1,#96
	BLT skip

	SUB R1,R1,#32
	STRB R1,[R0]


skip
	ADD R0,R0,#1
	B MakeUpper

end
	BX LR

