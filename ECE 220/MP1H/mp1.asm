.ORIG x4000

PRINT_SLOT
	ST R0, SAVE_R0
	ST R1, SAVE_R1
	ST R2, SAVE_R2
	ST R3, SAVE_R3
	ST R4, SAVE_R4
	ST R5, SAVE_R5
	ST R6, SAVE_R6
	ST R7, SAVE_R7
	AND R2, R2, #0
	LEA R2, VII 
	AND R3, R3, #0		;Multiply logic
	ADD R3, R3, #7
	AND R0, R0, #0

KEEP	ADD R1, R1, #-1
	BRn DONE
	ADD R0, R0, R3
	ADD R1, R1, #0
	BRp KEEP

DONE    ADD R2, R2, R0
	ADD R0, R2, #0
	PUTS

	LD R0, SAVE_R0
	LD R1, SAVE_R1
	LD R2, SAVE_R2
	LD R3, SAVE_R3
	LD R4, SAVE_R4
	LD R5, SAVE_R5
	LD R6, SAVE_R6
	LD R7, SAVE_R7

	RET

;R1: HOLDS THE FIRST ADDRESS OF .STRINGZ
;R2: CHAR COUNTER
;R4: GARBAGE
;R3: CHAR GETER
;R5: ANOTHER GARBAGE


VII     .STRINGZ "07:00 "
VIII    .STRINGZ "08:00 "
IX      .STRINGZ "09:00 "
X       .STRINGZ "10:00 "
XI      .STRINGZ "11:00 "
XII     .STRINGZ "12:00 "
XIII    .STRINGZ "13:00 "
XIV     .STRINGZ "14:00 "
XV	.STRINGZ "15:00 "
XVI     .STRINGZ "16:00 "
XVII    .STRINGZ "17:00 "
XVIII   .STRINGZ "18:00 "
XIX     .STRINGZ "19:00 "
XX      .STRINGZ "20:00 "
XXI     .STRINGZ "21:00 "
XXII    .STRINGZ "22:00 "
SAVE_R0	.FILL x0
SAVE_R1	.FILL x0
SAVE_R2	.FILL x0
SAVE_R3	.FILL x0
SAVE_R4	.FILL x0
SAVE_R5	.FILL x0
SAVE_R6	.FILL x0
SAVE_R7 .FILL x0
TEMP_CHAR
	.FILL x0
ALT  	.FILL x0
DUMP    .BLKW #7
BACK    .FILL x0
FRONT   .FILL x0
SPACE   .FILL x20
FRONT_SP	
	.FILL x0
BACK_SP
	.FILL x0
; your code should go here ... don't forget .ORIG and .END

PRINT_CENTERED
	ST R0, SAVE_R0
	ST R1, SAVE_R1
	ST R2, SAVE_R2
	ST R3, SAVE_R3
	ST R4, SAVE_R4
	ST R5, SAVE_R5
	ST R6, SAVE_R6
	ST R7, SAVE_R7	
	ST R1, ALT
	AND R2, R2, #0
	ADD R2, R2, #-1
	AND R3, R3, #0
NEXT_CHAR
	
	LDR R5, R1, #0
	BRz FINISHED
	ADD R2, R2, #1
	ADD R1, R1, #0
	ADD R1, R1, #1
	LDR R5, R1, #0
	BRnp NEXT_CHAR

FINISHED
	ADD R2, R2, #1
	AND R4, R4, #0
	ADD R4, R4, #6
	NOT R4, R4
	ADD R4, R4, #1
	ADD R4, R4, R2
	BRp TRUNK		;Branches when R2 is greater to 6.

 	
	AND R6, R6, #0
	ADD R6, R6, #1
	AND R6, R2, R6		;Check for even or odd properties of bit count.
	BRz EVEN 

ODD	AND R6, R6, #0
	ADD R6, R6, #6
	AND R3, R3, #0
	ADD R3, R2, #0
	NOT R3, R3
	ADD R3, R3, #1
	ADD R6, R6, R3		;Check for # of spaces. R6 is now the space counter.
	AND R3, R3, #0		;R3 -- Front space counter.
	AND R4, R4, #0		;R4 -- Tralling space counter.
	ADD R4, R4, #1		;Increment one tralling space.
	ADD R6, R6, #-1
	BRz DONE_SPACE		;Branch out if there is no more space.
EX_ODD	ADD R3, R3, #1		;
	ADD R4, R4, #1
	ADD R6, R6, #-2		
	BRz DONE_SPACE		;Branch out if there is no more space.
	BR EX_ODD		;Unconditional branch to EX_ODD if there are still more spaces.

EVEN
	LD  R1, ALT	
	AND R6, R6, #0
	ADD R6, R6, #6
	AND R3, R3, #0
	ADD R3, R2, #0
	NOT R3, R3
	ADD R3, R3, #1
	ADD R6, R6, R3		;Check for # of spaces. R6 is now the space counter.
	BRz OK
	AND R3, R3, #0		;R3 -- Front space counter.
	AND R4, R4, #0		;R4 -- Tralling space counter.
EX_EVEN	
	ADD R3, R3, #1
	ADD R4, R4, #1
	ADD R6, R6, #-2
	BRz DONE_SPACE		;Branch out if there is no more space.
	BR EX_EVEN		;Unconditional branch to EX_EVEN if there are still more spaces.

DONE_SPACE
	ST R3, FRONT_SP
	ST R4, BACK_SP
	LD R1, ALT
	AND R2, R2, #0		;Address counter.
	AND R5, R5, #0		;Space holder.
	AND R6, R6, #0
	ADD R6, R3, R4		;Sum of all spaces.
	
			
	LD R5, SPACE

	LEA R6, DUMP	
	ADD R6, R6, #5		;This is the DUMP End.
	LEA R2, DUMP		;This is the DUMP Top.

	
SPACE_CK
	
	ADD R4, R4, #-1
	STR R5, R6, #0		;Stores a space char at the trailing space.
	ADD R6, R6, #-1		;decrement Dump_front counter.
	ADD R3, R3, #0
	BRp NEXT_SP		;if there is still spaces to be distributed, go to the next part.
	ADD R4, R4, #0
	BRz PRE_OK		;You need trailing space first.

NEXT_SP
	ADD R3, R3, #-1		
	STR R5, R2, #0		
	ADD R2, R2, #1
	ADD R4, R4, #0		
	BRp SPACE_CK
	ADD R3, R3, #0
	BRz PRE_OK		;Then comes the front space.
	BR SPACE_CK		;Unconditional Branch to keep distributing spaces
	
PRE_OK
	LEA R6, DUMP
	ADD R6, R6, #6
	AND R2, R2, #0
	STR R2, R6, #0		;Putting a null char at the end of the blkw.
	
	LD R1, ALT		;LD the address of the original string.
	LEA R2, DUMP
	LD R3, FRONT_SP
	LD R4, BACK_SP
	ADD R2, R2, R3		;NEW START ADDRESS
	
	
	ADD R5, R3, R4
	BRz STEP		;If no spaces is needed, print the original string
				;(exactly 6 chars.)
FILL_IN	
	AND R5, R5, #0		;x0 == end of string char.
	LDR R6, R1, #0		;Fetch char from the original string.
	ADD R5, R5, R6		
	BRz STEP		;Branch out if the original string terminates.
	STR R6, R2, #0		;Store char into the new corresponding string.
	ADD R2, R2, #1		;Increment New String Pointer.
	ADD R1, R1, #1		;Increment Original String Pointer.
	BR  FILL_IN		;Unconditional Branch to fill in a new char.


	
STEP	LEA R1, DUMP
	
OK	ADD R0, R1, #0
	PUTS
	LD R0, SAVE_R0
	LD R1, SAVE_R1
	LD R2, SAVE_R2
	LD R3, SAVE_R3
	LD R4, SAVE_R4
	LD R5, SAVE_R5
	LD R6, SAVE_R6
	LD R7, SAVE_R7
	RET
TRUNK
	ST R7, SAVE_R7
	LD R1, ALT	
	ADD R1, R1, #6
	ADD R5, R1, #0
	LDR R5, R5, #0
	ST  R5, TEMP_CHAR
	AND R5, R5, #0
	STR R5, R1, #0
	LD R1, ALT
	ADD R0, R1, #0
	PUTS 
	LD R5, TEMP_CHAR
	ADD R1, R1, #6
	STR R5, R1, #0
	LD R4, SAVE_R4
	LD R7, SAVE_R7
	LD R1, SAVE_R1
	LD R5, SAVE_R5
	LD R2, SAVE_R2
	LD R0, SAVE_R0
	LD R3, SAVE_R3
	RET

.END



