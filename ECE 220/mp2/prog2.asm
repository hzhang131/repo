
;
;
;
.ORIG x3000
;your code goes here
;This program first analyse the user input from KBSR --> R0
;Then it echoes the user input to the console.
;The user input is analyzed by comparing with various ASCII codes.
;Different kinds of user input leads to different subroutines.
;Invalid char leads to the Error Message. "Invalid input"
;Arithmetic char leads to ADD, MIN, PWR, MUL and DIV.
;Numbers are pushed onto the stack.
;In each arithmetic subrountine, two numbers are popped from the stack, calculated.
;After arithmetic subroutines, the results are pushed onto the stack.
;R5 is checked in each subroutine to ensure that the stack is non-empty.
;After "=" is entered, program goes to EVALUATE.
;R5 is also checked in EVALUATE to ensure that only the result of the calculation is stored in the stack.
;Finally, the result is printed by PRINT_HEX and stored in R5.
;Partner: xiaobai2, ziyaow2, hz13


		AND R5, R5, #0

MAIN     	GETC			;reads a character from user.
		OUT			;echos the character to the console.
		LD R1, SPACE_DIFF 
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1		;Check whether the input character is a space?
		BRz MAIN		;if it is, reads another character from user.

NOT_SPACE	LD R1, ADD_DIFF 	;Check whether the input character is a plus sign.
		NOT R1, R1		
		ADD R1, R1, #1	
		ADD R1, R0, R1
		BRz PLUS		

NOT_PLUS 	LD R1, SUB_DIFF		;Check whether the input character is a minus sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz MIN

NOT_MIN 	LD R1, MULT_DIFF	;Check whether the input character is a star.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz MUL

NOT_MUL 	LD R1, DIV_DIFF		;Check whether the input character is a slash.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz DIV

NOT_DIV 	LD R1, PWR_DIFF		;Check whether the input character is a power sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz PWR

NOT_PWR		LD R1, EQ_DIFF		;Check whether the input character is an equal sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz EVALUATE

COMPARE		LD R1, ZERO_DIFF	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRn INVALID		;If the input character is smaller than 0, than it's invalid.

MIGHT_BE_NUMBER LD R1, NINE_DIFF	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRp INVALID		;If the input character is greater than 9, than it's invalid.

IS_NUMBER	LD R1, ZERO_DIFF	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R0, R0, R1
		JSR PUSH		;Push the number (in decimal) onto the stack.
		BR  MAIN		;After pushing, go get a new character from user.

INVALID
	LEA R0, MSG			
	PUTS				;If input invalid, prints an error message, then halt.
	HALT



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;

ZERO_DIFF .FILL x30
NINE_DIFF .FILL x39
SPACE_DIFF .FILL x20
ADD_DIFF   .FILL x2B
SUB_DIFF   .FILL x2D
MULT_DIFF  .FILL x2A
DIV_DIFF   .FILL x2F
PWR_DIFF   .FILL x5E
EQ_DIFF    .FILL x3D
MSG	   .STRINGZ "Invalid Expression"
EMPTY_CHECK .FILL x3FFF

PRINT_HEX
		ST  R7, SAVE_R7
		
		
		AND R1, R1, #0
		AND R2, R2, #0
		AND R3, R3, #0
		AND R1, R1, #0				;Initialize bit counter.
		ADD R1, R1, #4				;To 4.
		AND R0, R0, #0				;Initialize digit.
		AND R2, R2, #0				;Initialize digit counter.
		ADD R2, R2, #4				;To 4.
		LD R3, REGISTER		
		;reg r3  x57c3				;R3.
		; write your code here
		BR CONTINUE_BIT
		
NEXT_DIGIT 	AND R0, R0, #0	
		AND R1, R1, #0	
		ADD R1, R1, #4
		BR CONTINUE_BIT

DONE_BIT 
		ADD R1, R1, #0
		BRp CONTINUE_BIT
		BR  DONE_DIGIT
		
CONTINUE_BIT
		ADD R0, R0, R0				;left shift R0
		ADD R3, R3, #0				
		BRn ADD_R0
		ADD R3, R3, R3				;Left shift R3
		ADD R1, R1, #-1				;Decrement bit counter
		BR DONE_BIT
		
ADD_R0 		ADD R0, R0, #1				;ADD 1 to R0
		ADD R3, R3, R3				;Left shift R3		
		ADD R1, R1, #-1				;Decrement bit counter
		BR DONE_BIT

DONE_DIGIT
		 ADD R0, R0, #-9				;Solve for the differential.
		 BRnz PRINT_NO
PRINT_LT
		 ADD R0, R0, #9					;RESTORE R0
		 ADD R0, R0, #15
		 ADD R0, R0, #15
		 ADD R0, R0, #15
		 ADD R0, R0, #10				;ADD #55
		 OUT
		 ADD R2, R2, #-1				;Decrement digit counter
		 BRp NEXT_DIGIT 
		 BR  ALL_DONE

PRINT_NO	 ADD R0, R0, #9
		 ADD R0, R0, #12
		 ADD R0, R0, #12
		 ADD R0, R0, #12
		 ADD R0, R0, #12				;ADD #48
		 OUT
		 ADD R2, R2, #-1				;Decrement digit counter
		 BRp NEXT_DIGIT
		 BR ALL_DONE

ALL_DONE 	 LD R3, REGISTER
		 LD R7, SAVE_R7
		 RET




;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R1, R2
;out R0
PLUS	
;your code goes here
JSR POP
ADD R1, R0, #0
ADD R4, R5, #0
ADD R4, R4, #-1
BRz INVALID
JSR POP
ADD R2, R0, #0				;POP two numbers off the stack.
ADD R4, R5, #0
ADD R4, R4, #-1
BRz INVALID
ADD R0, R1, R2				;Calculates the sum.
ADD R5, R5, #-1				;Check whether stack is empty
BRz INVALID				;If not, input is invalid.
JSR PUSH
BR  MAIN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
JSR POP
ADD R1, R0, #0
ADD R4, R5, #0
ADD R4, R4, #-1
BRz INVALID
JSR POP
ADD R2, R0, #0				;POP two numbers off the stack.
ADD R4, R5, #0
ADD R4, R4, #-1
BRz INVALID
NOT R1, R1
ADD R1, R1, #1				
ADD R0, R1, R2				;Calculates the Difference.
ADD R5, R5, #-1
BRz INVALID				;Check whether stack is empty
JSR PUSH				;If not, input is invalid.
BR  MAIN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
		
		AND R6, R6, #0
		JSR POP
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID
		ADD R1, R0, #0
		JSR POP
		ADD R2, R0, #0	
		BRz PRINT_ZERO 
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID
		ADD R1, R1, #0		
		BRn R1_NEG		;Branches when R1 is negative.
CHECK_R2	ADD R2, R2, #0
		BRn R2_NEG		;Branches when R2 is negative.
		
		
		AND R0, R0, #0
MULT_LOOP	ADD R2, R2, #-1		;Decrement counter.
		ADD R0, R0, R1
		ADD R2, R2, #0
		BRp MULT_LOOP		;Goes back to the loop if counter still positive.
		ADD R6, R6, #0		
		BRz ALLPO_ALLNEG	;If R6 remains to be 0, then the product is unchanged.
		NOT R0, R0		;If not, product negates itself.
		ADD R0, R0, #1
ALLPO_ALLNEG	JSR PUSH		;Push onto the stack.
		BR MAIN			

R1_NEG		NOT R1, R1		
		ADD R1, R1, #1
		ADD R6, R6, #1		;Add R6 to 1 if R1 is negative.
		BR CHECK_R2	
	
R2_NEG		NOT R2, R2
		ADD R2, R2, #1
		ADD R6, R6, #-1		;Add R6 to -1 if R2 is negative.
		AND R0, R0, #0
		BR MULT_LOOP
PRINT_ZERO AND R0, R0, #0
		JSR PUSH
		BR MAIN





;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	

AND R6, R6, #0
		JSR POP				
		ADD R1, R0, #0	
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID
		JSR POP
		ADD R2, R0, #0	
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID		
		ADD R1, R1, #0
		BRz INVALID		;Input invalid when the divisor is 0.
		BRn R1_NEG_DIV		
CHECK_R2_DIV	ADD R2, R2, #0
		BRn R2_NEG_DIV		
		
		
		AND R0, R0, #0
NOT_R1		NOT R1, R1
		ADD R1, R1, #1		;reflip R1 if both are negative.
DIV_LOOP	ADD R2, R1, R2
		BRn PO_NEG_DIV
		ADD R0, R0, #1
		BR DIV_LOOP


PO_NEG_DIV	ADD R6, R6, #0
		BRz JSR_PUSH
		NOT R0, R0
		ADD R0, R0, #1
JSR_PUSH	JSR PUSH
		BR MAIN

R1_NEG_DIV	NOT R1, R1
		ADD R1, R1, #1		;Flip R1 if only R1 is negative.
		ADD R6, R6, #1
		BR CHECK_R2_DIV
	
R2_NEG_DIV	NOT R2, R2
		ADD R2, R2, #1
		ADD R6, R6, #-1
		AND R0, R0, #0
		BR NOT_R1



EVALUATE
	LD R6, INVALID_CK
	ADD R6, R6, #-1
	BRz INVALID
 	LD R3, STACK_TOP		
	LD R4, EMPTY_CHECK 
	NOT R4, R4
	ADD R4, R4, #1
	ADD R3, R3, R4			;Check whether stack is empty by comparing two addresses.
	BRnp INVALID
	LDI R5, STACK_START
	ST  R5, REGISTER
	JSR PRINT_HEX	
	HALT	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0

INVALID1
	LEA R0, MSG			
	PUTS				;If input invalid, prints an error message, then halt.
	HALT


PWR
;your code goes here
		JSR POP
		ADD R1, R0, #0
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID1
		JSR POP 
		ADD R2, R0, #0
		ADD R4, R5, #0
		ADD R4, R4, #-1
		BRz INVALID1
		JSR ZERO_EXP
		ADD R4, R4, #0
		BRz INVALID1
		JSR R1_PWR_ZERO
		ADD R0, R0, #0
		BRnp LOOP_2

		
		
		ADD R6, R2, #0
		ADD R6, R6, #-1
		BRz NUMBER_ONE		;Branches out 1 as 1^n is still 1.
		
		JSR R2_NEG_BASE
		JSR R1_NEG_PWR
		ADD R4, R4, #0
		BRz LOOP_2
		ADD R6, R2, #0
		ADD R6, R6, #-1
		BRz NUMBER_ONE		;Branches out 1 as 1^n is still 1.
		AND R4, R4, #0
		ADD R4, R4, #-1
		ADD R4, R1, R4
		BRz PRE_LOOP
		AND R0, R0, #0		
		ADD R1, R1, #-1		
		ADD R4, R2, #0		;Stores the base to another register.
		ADD R0, R2, #0
OUTER_LOOP	ADD R1, R1, #-1		;Decrement the degree counter.
		JSR INNER_LOOP
		ADD R1, R1, #0
		BRp OUTER_LOOP		;If the degree counter is not 0, go back to OUTER_LOOP again.
		BR  LOOP_2		;Else, push the result.

NUMBER_ONE  	AND R0, R0, #0
		ADD R0, R0, #1
	
	
		
LOOP_2		LD R4, NEG_BASE
		JSR NEG_RES
		JSR PUSH
		AND R6, R6, #0
		ST R6, INVALID_CK
		BR MAIN_AUX

ZERO_EXP	ADD R2, R2, #0
		BRnp NORMAL
		ADD R1, R1, #0
		BRzp NORMAL
		AND R4, R4, #0
		ADD R4, R4, #1
		ST R4, INVALID_CK
		AND R4, R4, #0
		RET

NORMAL 		RET		



PRE_LOOP	ADD R0, R2, #0
		BR LOOP_2	

INNER_LOOP	ADD R3, R2, #0		;Store the base to another register as a loop counter.
		ADD R3, R3, #-1        	;Decrement loop counter.
		
MULTY_LOOP	
		ADD R3, R3, #-1		;Decrement loop counter again.
		ADD R0, R4, R0		;Add R4	to R0 repetitively.
		ADD R3, R3, #0		
		BRp MULTY_LOOP		;If the loop counter is not 0, go back to INNER_LOOP again.
		ADD R4, R0, #0		;Else stores the result to R4 again.
		
		RET

NEG_RES		ADD R4, R4, #0
		ADD R4, R4, #-1
		BRz NEGATE_RES
		RET


NEGATE_RES	NOT R0, R0
		ADD R0, R0, #1
		RET

SAVE_R7	   .FILL x2
SAVE_HEX   .FILL x78
INVALID_CK .FILL x6
ZERO_DIFF1 .FILL x30
NINE_DIFF1 .FILL x39
SPACE_DIFF1 .FILL x20
ADD_DIFF1   .FILL x2B
SUB_DIFF1   .FILL x2D
MULT_DIFF1  .FILL x2A
DIV_DIFF1   .FILL x2F
PWR_DIFF1   .FILL x5E
EQ_DIFF1    .FILL x3D
REGISTER   .FILL x1

MAIN_AUX     	GETC			;reads a character from user.
		OUT			;echos the character to the console.
		LD R1, SPACE_DIFF1 
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1		;Check whether the input character is a space?
		BRz MAIN_AUX		;if it is, reads another character from user.

NOT_SPACE_AUX	LD R1, ADD_DIFF1 	;Check whether the input character is a plus sign.
		NOT R1, R1		
		ADD R1, R1, #1	
		ADD R1, R0, R1
		BRz PLUS		

NOT_PLUS_AUX 	LD R1, SUB_DIFF1		;Check whether the input character is a minus sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz MIN

NOT_MIN_AUX	LD R1, MULT_DIFF1	;Check whether the input character is a star.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz MUL

NOT_MUL_AUX 	LD R1, DIV_DIFF1		;Check whether the input character is a slash.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz DIV

NOT_DIV_AUX 	LD R1, PWR_DIFF1		;Check whether the input character is a power sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz PWR

NOT_PWR_AUX	LD R1, EQ_DIFF1		;Check whether the input character is an equal sign.
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRz EVALUATE

COMPARE_AUX	LD R1, ZERO_DIFF1	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRn INVALID1		;If the input character is smaller than 0, than it's invalid.

MIGHT_NUMBER_AU LD R1, NINE_DIFF1	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R1, R0, R1
		BRp INVALID1		;If the input character is greater than 9, than it's invalid.

IS_NUMBER_AUX	LD R1, ZERO_DIFF1	
		NOT R1, R1
		ADD R1, R1, #1
		ADD R0, R0, R1
		JSR PUSH		;Push the number (in decimal) onto the stack.
		BR  MAIN_AUX		;After pushing, go get a new character from user.
			
PWR_BASE   .FILL x0


NEG_BASE   .FILL x3


R1_NEG_PWR	
		ADD R6, R2, #0
		ADD R6, R6, #-1
		BRz BASE_ONE	
		AND R4, R4, #0
		ADD R4, R4, #1		
		ADD R1, R1, #0
		BRn TO_THE_ZERO
		RET

BASE_ONE      	ADD R4, R2, #0
		ADD R4, R4, #-1
		AND R0, R0, #0
		ADD R0, R0, #1
		RET

R2_NEG_BASE	ADD R2, R2, #0
		BRzp NON_NEG
		AND R6, R6, #0
		ADD R6, R6, #1
		AND R6, R1, R6
		BRp NEG_ODD_PWR

NEG_POS_PWR	AND R6, R6, #0
		ST R6, NEG_BASE
		NOT R2, R2
		ADD R2, R2, #1
		RET		
		

NEG_ODD_PWR	AND R6, R6, #0
		ADD R6, R6, #1
		ST  R6, NEG_BASE
		NOT R2, R2
		ADD R2, R2, #1
		RET

TO_THE_ZERO	AND R0, R0, #0
		AND R4, R4, #0
		RET

NON_NEG 	RET

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET

R1_PWR_ZERO
	ADD R1, R1, #0
	BRnp NOT_ZERO
	AND R0, R0, #0
	ADD R0, R0, #1
	RET

NOT_ZERO
	AND R0, R0, #0
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;

DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END

