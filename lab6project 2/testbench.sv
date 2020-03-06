module testbench();

timeunit 10ns;

timeprecision 1ns;

logic Clk;
logic [7:0] S;
logic Reset, Run, ClearA_LoadB;
logic [6:0] AhexU, AhexL, BhexU, BhexL;
logic [7:0] Aval, Bval;
logic X, X_check;


logic [7:0] ans_a,ans_b;

multiplier Mult(.*);

always begin : CLOCK_GENERATION
#1 Clk = ~Clk;
end

initial begin: CLOCK_INITIALIZATION
    Clk = 0;
end 

initial begin: TEST_VECTORS
Reset = 1;		// Toggle Rest
ClearA_LoadB = 1;
Run = 1;
S = 8'hC5;


#2 Reset = 0;
#2 Reset = 1;

#2 ClearA_LoadB = 1;	// Toggle ClearA_LoadB to get intial value of B
#2 ClearA_LoadB = 0;
#2 ClearA_LoadB = 1;
	S = 8'h07;	// Change S
   
if(Bval != 8'hC5)
	$display("LoadB failed.");
else
	$display("LoadB success.");
	


#22 Run = 0;
	 $display("First test begins.");
    ans_a = 8'hFE; // Expected result of 1st cycle
    ans_b = 8'h63;
	 X_check = 1'b1;
    

#44 Run = 1;	 
		if (Aval != ans_a)
			$display("A part result failed.");
		else
			$display("A part passed.");
		if (Bval != ans_b)
			$display("B part result failed.");
		else
			$display("B part passed.");
		if (X != X_check)
			$display("X part result failed.");
		else
			$display("X part passed.");
		
#2 Reset = 0;
#2 Reset = 1;	 

#2 S = 8'h07;
#2 ClearA_LoadB = 0;
#2 ClearA_LoadB = 1;
#2 S = 8'hC5;

#22 Run = 0;
	 $display("Second test begins.");
    ans_a = 8'hFE; // Expected result of 1st cycle
    ans_b = 8'h63;
	 X_check = 1'b1;
    

#44 Run = 1;	 
		if (Aval != ans_a)
			$display("A part result failed.");
		else
			$display("A part passed.");
		if (Bval != ans_b)
			$display("B part result failed.");
		else
			$display("B part passed.");
		if (X != X_check)
			$display("X part result failed.");
		else
			$display("X part passed.");
		

#2 Reset = 0;
#2 Reset = 1;
// third test, continuous multiplying

#2 S = 8'hFF;	// Toggle Execute
#2 ClearA_LoadB = 0;
#2 ClearA_LoadB = 1;

#22 Run = 0;
	 $display("Third-1 test begins.");
	 ans_a = 8'h00;
	 ans_b = 8'h01;
	 X_check = 1'b0;
	 
#2 Run = 1;
#40 if (Aval != ans_a)
			$display("A part result failed.");
		else
			$display("A part passed.");
		if (Bval != ans_b)
			$display("B part result failed.");
		else
			$display("B part passed.");
		if (X != X_check)
			$display("X part result failed.");
		else
			$display("X part passed.");
#44 Run = 0;
	 $display("Third-2 test begins.");
	 ans_a = 8'hFF;
	 ans_b = 8'hFF;
	 X_check = 1'b1;
	 
#44    if (Aval != ans_a)
			$display("A part result failed.");
		else
			$display("A part passed.");
		if (Bval != ans_b)
			$display("B part result failed.");
		else
			$display("B part passed.");
		if (X != X_check)
			$display("X part result failed.");
		else
			$display("X part passed.");
#2 Run = 1;	 

end
endmodule
