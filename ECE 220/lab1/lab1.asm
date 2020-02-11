.ORIG x3000
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
		 HALT 

REGISTER 	 .FILL xFFFF
.END 





