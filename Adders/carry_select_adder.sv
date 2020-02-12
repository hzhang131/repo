module carry_select_adder
(
    input   logic[15:0]     A,
    input   logic[15:0]     B,
    output  logic[15:0]     Sum,
    output  logic           CO
);
    
	 logic c_In = 1'b0;
	 logic c4, c8, c12;
	 logic BLOCK2_0_OUT, BLOCK2_1_OUT, BLOCK3_0_OUT, BLOCK3_1_OUT, BLOCK4_0_OUT, BLOCK4_1_OUT;
	 logic [3:0] CACHE_BLOCK2_0, CACHE_BLOCK2_1, CACHE_BLOCK3_0, CACHE_BLOCK3_1, CACHE_BLOCK4_0, CACHE_BLOCK4_1;
	 logic [3:0] RET;
    carry_select BLOCK1(.A(A[3:0]), .B(B[3:0]), .z(c_In), .c(c4), .Sum(RET[3:0]));
	 assign Sum[3:0] = RET;
	 
	 // construct the second layer.
	 carry_select BLOCK2_0(.A(A[7:4]), .B(B[7:4]), .z(1'b0), .c(BLOCK2_0_OUT), .Sum(CACHE_BLOCK2_0));
	 carry_select BLOCK2_1(.A(A[7:4]), .B(B[7:4]), .z(1'b1), .c(BLOCK2_1_OUT), .Sum(CACHE_BLOCK2_1));
	 
	 always_comb
	  begin
			if (c4) 
				Sum[7:4] = CACHE_BLOCK2_1; 
			else 
				Sum[7:4] = CACHE_BLOCK2_0;
		end
	 
	 assign c8 = (c4&BLOCK2_1_OUT)|BLOCK2_0_OUT;
	 
	 // construct the third layer.
	 carry_select BLOCK3_0(.A(A[11:8]), .B(B[11:8]), .z(1'b0), .c(BLOCK3_0_OUT), .Sum(CACHE_BLOCK3_0));
	 carry_select BLOCK3_1(.A(A[11:8]), .B(B[11:8]), .z(1'b1), .c(BLOCK3_1_OUT), .Sum(CACHE_BLOCK3_1));
	 
	 always_comb
	   begin
		if (c8) 
			Sum[11:8] = CACHE_BLOCK3_1;
		else 
			Sum[11:8] = CACHE_BLOCK3_0;
		end
		
	 assign c12 = (c8&BLOCK3_1_OUT)|BLOCK3_0_OUT;
	 
	 // construct the fourth layer.
	 carry_select BLOCK4_0(.A(A[15:12]), .B(B[15:12]), .z(1'b0), .c(BLOCK4_0_OUT), .Sum(CACHE_BLOCK4_0));
	 carry_select BLOCK4_1(.A(A[15:12]), .B(B[15:12]), .z(1'b1), .c(BLOCK4_1_OUT), .Sum(CACHE_BLOCK4_1));
	 
	 always_comb
		begin
			if (c12) 
				Sum[15:12] = CACHE_BLOCK4_1;
			else 
				Sum[15:12] = CACHE_BLOCK4_0;
		end
	 
	 assign CO = (c12&BLOCK4_1_OUT)|BLOCK4_0_OUT;
	 
     
endmodule

