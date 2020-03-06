module register (input logic reset, LD_EN, Clk, input logic [15:0] in, output logic [15:0] out);

	always_ff @ (posedge Clk) 
	begin
		if(reset)
		   out <= 16'b0;
		else if(LD_EN)
		   out <= in;
		else
			out <= out;
	end
	
endmodule


module datapath(input logic GatePC, GateMDR, GateALU, GateMARMUX, input logic [15:0] MAR, MDR, ALU, PC, output logic [15:0] data);
	
	always_comb 
	begin
		if(GatePC)
			data = PC;
		else if(GateMDR)
			data = MDR;
		else if(GateALU)
			data = ALU;
		else if(GateMARMUX)
			data = MAR;
		else
			data = 16'b0;
	end
	
endmodule


module nzp(input logic n, z, p, Clk, reset, LD_CC, output logic N_out, Z_out, P_out);

   always_ff @(posedge Clk)
	begin
	  if(reset)
		begin
		   N_out <= 1'b0;
			P_out <= 1'b0;
         Z_out <= 1'b0;
		end
		else if(LD_CC)
		begin
			N_out <= n;
			Z_out <= z;
			P_out <= p;
		end
		else
		begin
			N_out <= N_out;
			Z_out <= Z_out;
			P_out <= P_out;
		end
	end

endmodule



//IR1: IR[11:9]
//IR2: IR[8:6]
//SR2: IR[2:0]
module reg_file(input logic Clk, LD_reg, DR, SR1, reset, input logic [2:0] IR1, IR2, SR2, input logic [15:0] bus, output logic [15:0] SR1_out, SR2_out);
   
	logic [15:0] R0_out, R1_out, R2_out, R3_out, R4_out, R5_out, R6_out, R7_out;
	logic LD_R0, LD_R1, LD_R2, LD_R3, LD_R4, LD_R5, LD_R6, LD_R7;
	logic [2:0] DR_in, SR1_in;
	logic w0, w1, w2, w3, w4, w5, w6, w7; 

	register R0(.reset(reset), .LD_EN(LD_R0 & LD_reg), .in(bus), .out(R0_out), .Clk(Clk));
	register R1(.reset(reset), .LD_EN(LD_R1 & LD_reg), .in(bus), .out(R1_out), .Clk(Clk));
	register R2(.reset(reset), .LD_EN(LD_R2 & LD_reg), .in(bus), .out(R2_out), .Clk(Clk));
	register R3(.reset(reset), .LD_EN(LD_R3 & LD_reg), .in(bus), .out(R3_out), .Clk(Clk));
	register R4(.reset(reset), .LD_EN(LD_R4 & LD_reg), .in(bus), .out(R4_out), .Clk(Clk));
	register R5(.reset(reset), .LD_EN(LD_R5 & LD_reg), .in(bus), .out(R5_out), .Clk(Clk));
	register R6(.reset(reset), .LD_EN(LD_R6 & LD_reg), .in(bus), .out(R6_out), .Clk(Clk));
	register R7(.reset(reset), .LD_EN(LD_R7 & LD_reg), .in(bus), .out(R7_out), .Clk(Clk));
	
	always_comb
	begin 
		if(DR)
		  DR_in = IR1;
		else
		  DR_in = 3'b111;
	end
	
	always_comb
	begin 
		if(!SR1)
		  SR1_in = IR1;
		else
		  SR1_in = IR2;
	end
	
//	assign w0 = 
//	assign w1 = LD_R1 & LD_reg;
//	assign w2 = LD_R2 & LD_reg;
//	assign w3 = LD_R3 & LD_reg;
//	assign w4 = LD_R4 & LD_reg;
//	assign w5 = LD_R5 & LD_reg;
//	assign w6 = LD_R6 & LD_reg;
//	assign w7 = LD_R7 & LD_reg;
	
	always_comb
	begin
		LD_R0 = 1'b0;
		LD_R1 = 1'b0;
		LD_R2 = 1'b0;
		LD_R3 = 1'b0;
		LD_R4 = 1'b0;
		LD_R5 = 1'b0;
		LD_R6 = 1'b0;
		LD_R7 = 1'b0;

	   case(DR_in)
			3'b000: LD_R0 = 1'b1;
			3'b001: LD_R1 = 1'b1;
			3'b010: LD_R2 = 1'b1;
			3'b011: LD_R3 = 1'b1;
			3'b100: LD_R4 = 1'b1;
			3'b101: LD_R5 = 1'b1;
			3'b110: LD_R6 = 1'b1;
			3'b111: LD_R7 = 1'b1;
		endcase
	end
	
	always_comb
	begin
		 case(SR1_in)
			3'b000: SR1_out = R0_out;
			3'b001: SR1_out = R1_out;
			3'b010: SR1_out = R2_out;
			3'b011: SR1_out = R3_out;
			3'b100: SR1_out = R4_out;
			3'b101: SR1_out = R5_out;
			3'b110: SR1_out = R6_out;
			3'b111: SR1_out = R7_out;
		endcase
	end
	
	always_comb
	begin
		 case(SR2)
			3'b000: SR2_out = R0_out;
			3'b001: SR2_out = R1_out;
			3'b010: SR2_out = R2_out;
			3'b011: SR2_out = R3_out;
			3'b100: SR2_out = R4_out;
			3'b101: SR2_out = R5_out;
			3'b110: SR2_out = R6_out;
			3'b111: SR2_out = R7_out;
		endcase
	end
	
endmodule


	
module ALU(input logic [1:0] ALUK, input logic[15:0] A, B, output logic[15:0] ALU_out);
	
	always_comb
	begin
		case(ALUK)
			2'b00: ALU_out = A + B;
			2'b01: ALU_out = A & B;
			2'b10: ALU_out = ~A;
			2'b11: ALU_out = A;
		endcase
	end

endmodule


module ben(input logic reset, LD_BEN, Clk, in, output logic BEN);
	
	always_ff @ (posedge Clk) 
	begin
		if(reset)
		   BEN <= 1'b0;
		else if(LD_BEN)
		   BEN <= in;
		else
			BEN <= BEN;
	end
	
endmodule


