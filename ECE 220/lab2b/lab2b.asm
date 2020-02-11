;number to print in decimal is in R3.
;it will be positive.
.ORIG x3000
	

MAIN 
	JSR DIV
POPP	JSR POP
	ADD R5, R5, #0
	BRp FIN
	OUT
	BR POPP		;If stack is not yet empty, pop again.
FIN	HALT



ASCII_0 .FILL x30
ST_R7	.FILL x0
TEN 	.FILL #10
ST_R5   .FILL x0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0-quotient, R1-remainder
DIV	
	ST R7, ST_R7
	LD R5, TEN
	
	NOT R5, R5
	ADD R5, R5, #1		;R5 == -10
	AND R6, R6, #0
	AND R1, R1, #0		;Initialize quotient counter.
	ADD R3, R3, #0
	ADD R3, R3, R5		
	BRn PRE_DONE
	ADD R3, R3, #10
LOOP1	ADD R3, R3, R5		
	
	BRn DONE 		;SET quotient to zero
	
	ADD R1, R1, #1		;SET quotient to 1.
	ADD R6, R3, #0		;R3 --> R6
	ADD R6, R5, R6		;R6 == R6 - 10
	BRzp LOOP1		;If R3 >= 10, keep subtracting.
	LD R0, ASCII_0		;Load ascii 0
	ADD R0, R3, R0		;R3 --> R0
	ST R5, ST_R5		
	ADD R1, R1, #0
	LD R6, TEN
	JSR PUSH 		;Push remainder to stack.
	LD R6, ASCII_0 		
	NOT R6, R6
	ADD R6, R6, #1
	ADD R0, R0, R6		;Get original R0.	
	LD R5, ST_R5

	ADD R0, R1, #0		;R1 --> R0 (Previous quotient --> remainder)
	AND R1, R1, #0		;Set R1 back to zero.
	ADD R3, R0, #0		;Store R0 back to R3
	ADD R0, R0, #0		
	BRp LOOP1		;if quotient > 0, go back to loop1.

	
DONE	LD R6, ASCII_0
	ADD R0, R0, R6		;Push ascii remainder.
	JSR PUSH
	LD R7, ST_R7			
	RET			;Return to the main prog.

PRE_DONE
	ADD R0, R3, #0
	ADD R0, R0, #10
	BR DONE


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

