;; Branch examples
	B forwards		; This should be positive
self	B 	self

l2	BL some_func
forwards	B l2		; This should be negative 

	B	self		; this will have a different opcode since instruction is in a different relative place
	B	self		; as will this one

some_func
	MOV	PC,R14

