.ORIG x3000
; Write code to read in characters and echo them
; till a newline character is entered.

MAIN
	
	JSR NEW_CHAR		;Get first character.
	JSR IS_BALANCED		;When string is done, check for empty stack.
	JSR COMPARE
OVER	HALT

NEW_CHAR 
	ST R7, TEMP_NEW_CHAR	
	GETC
	OUT			;Get first char
	LD R1, R_DIFF		
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz UNBALANCED		;If first char is ")",string is unbalanced.
	JSR CHECK_END		;Then, check for whether or not the string is done.
	LD R7, TEMP_NEW_CHAR		
	RET

IS_BALANCED 
	ST R7, TEMP_IS_BALANCED
	JSR POP			   ;POP to check whether or not stack is empty.
	LD R7, TEMP_IS_BALANCED
	RET

COMPARE
	ST R7, TEMP_COMPARE
	ADD R5, R5, #0
	AND R6, R6, #0
	ADD R6, R6, #1
	NOT R6, R6
	ADD R6, R6, #1
	ADD R6, R5, R6
	BRz ONE
	ADD R5, R5, #-1
ONE	LD R7, TEMP_COMPARE
	RET 

CHECK_END
	ST R7, TEMP_CHECK_END
NI	LD R1, CHAR_RETURN		
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz DONE			;CHECK IS END OF STRING OR NOT?
	LD R1, SPACE
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz NEW_INPUT			;CHECK IS SPACE OR NOT?	
	JSR CHECK_PAR			;CHECK INPUT A PARATHESIS OR NOT?

NEW_INPUT  	
	GETC				;Gets another char
	OUT
	BR NI				;Goes back to the CHECK_END loop.
	
CHECK_PAR 
	ST R7, TEMP_CHECK_PAR			
	LD R1, L_DIFF
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz IS_LT			;Left par goes to IS_LT
	BR  IS_RT			;Otherwise, right par goes to IS_RT
	



IS_LT 
	JSR PUSH			;Push left par onto the stack.
	LD R7, TEMP_CHECK_PAR
	RET
IS_RT
	JSR POP				;Pop right par out of the stack. 
	LD R7, TEMP_CHECK_PAR
	RET 

DONE 	
	LD R7, TEMP_CHECK_END			
	RET
	
	
TEMP_NEW_CHAR   .FILL x0
TEMP_CHECK_PAR  .FILL x1
TEMP_CHECK_END  .FILL x2
TEMP_IS_BALANCED .FILL x3
TEMP_COMPARE	.FILL x4
L_DIFF .FILL x28
R_DIFF .FILL x29
SPACE   .FILL x20
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
UNBALANCED
	AND R5, R5, #0
	ADD R5, R5, #-1
	BR  OVER			;If unbalanced, set R5 manually to -1.
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;if ( push onto stack if ) pop from stack and check if popped value is (
;input - R0 holds the input
;output - R5 set to -1 if unbalanced. else 1.


NEG_OPEN .FILL xFFD8
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH
        ST R3, PUSH_SaveR3      ;save R3
        ST R4, PUSH_SaveR4      ;save R4
	
        AND R5, R5, #0          ;
        LD R3, STACK_END        ;
        LD R4, STACk_TOP        ;
        ADD R3, R3, #-1         ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz OVERFLOW            ;stack is full
        STR R0, R4, #0          ;no overflow, store value in the stack
        ADD R4, R4, #-1         ;move top of the stack
        ST R4, STACK_TOP        ;store top of stack pointer
        BRnzp DONE_PUSH         ;
OVERFLOW
        ADD R5, R5, #1          ;
DONE_PUSH
        LD R3, PUSH_SaveR3      ;
        LD R4, PUSH_SaveR4      ;
	
        RET


PUSH_SaveR3     .BLKW #1        ;
PUSH_SaveR4     .BLKW #1        ;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
        ST R3, POP_SaveR3       ;save R3
        ST R4, POP_SaveR4       ;save R3
        AND R5, R5, #0          ;clear R5
        LD R3, STACK_START      ;
        LD R4, STACK_TOP        ;
        NOT R3, R3              ;
        ADD R3, R3, #1          ;
        ADD R3, R3, R4          ;
        BRz UNDERFLOW           ; R3 Becomes zero when the stack is empty.
        ADD R4, R4, #1          ;
        LDR R0, R4, #0          ;
        ST R4, STACK_TOP        ;
        BRnzp DONE_POP          ;
UNDERFLOW
        ADD R5, R5, #1          ;
	ADD R0, R0, #-13 	; 
	BRnp UNBALANCED		; If not end of the string, meaning that string is unbalanced.
EOS	ADD R0, R0, #13		;
DONE_POP
        LD R3, POP_SaveR3       ;
        LD R4, POP_SaveR4       ;
        RET


POP_SaveR3      .BLKW #1        ;
POP_SaveR4      .BLKW #1        ;
STACK_END       .FILL x3FF0     ;
STACK_START     .FILL x4000     ;
STACK_TOP       .FILL x4000     ;

.END

