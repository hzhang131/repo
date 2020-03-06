//------------------------------------------------------------------------------
// Company:        UIUC ECE Dept.
// Engineer:       Stephen Kempf
//
// Create Date:    
// Design Name:    ECE 385 Lab 6 Given Code - SLC-3 
// Module Name:    SLC3
//
// Comments:
//    Revised 03-22-2007
//    Spring 2007 Distribution
//    Revised 07-26-2013
//    Spring 2015 Distribution
//    Revised 09-22-2015 
//    Revised 10-19-2017 
//    spring 2018 Distribution
//
//------------------------------------------------------------------------------
module slc3(
    input logic [15:0] S,
    input logic Clk, Reset, Run, Continue,
    output logic [11:0] LED,
    output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5, HEX6, HEX7,
    output logic CE, UB, LB, OE, WE,
    output logic [19:0] ADDR,
    inout wire [15:0] Data //tristate buffers need to be of type wire
);

// Declaration of push button active high signals
logic Reset_ah, Continue_ah, Run_ah;

assign Reset_ah = ~Reset;
assign Continue_ah = ~Continue;
assign Run_ah = ~Run;

// Internal connections
logic BEN, BEN_in;
logic LD_MAR, LD_MDR, LD_IR, LD_BEN, LD_CC, LD_REG, LD_PC, LD_LED;
logic GatePC, GateMDR, GateALU, GateMARMUX;
logic [1:0] PCMUX, ADDR2MUX, ALUK;
logic DRMUX, SR1MUX, SR2MUX, ADDR1MUX;
logic MIO_EN;

logic [15:0] MDR_In;
logic [15:0] MAR, MDR, IR, PC;
logic [15:0] Data_from_SRAM, Data_to_SRAM;
logic [15:0] MARMUX;
// Signals being displayed on hex display
logic [3:0][3:0] hex_4;
logic [15:0] bus;
logic [15:0] PCR_out, MDR_IN1, MDR_out, SR1_out, SR2_out;
logic [15:0] Imm5_ext, Imm6_ext, Imm9_ext, Imm11_ext, SR2_muxo, ALU_out, ADDR1_out, ADDR2_out, ADDR_out;
logic N, Z, P, N_out, Z_out, P_out;
logic [2:0] nzp_out;

assign Imm5_ext = {{11{IR[4]}}, IR[4:0]};
assign Imm6_ext = {{10{IR[5]}}, IR[5:0]};
assign Imm9_ext = {{7{IR[8]}}, IR[8:0]};
assign Imm11_ext = {{5{IR[10]}}, IR[10:0]};
assign BEN_in = (IR[11]&N_out) | (IR[10]&Z_out) | (IR[9]&P_out);
assign ADDR_out = ADDR1_out + ADDR2_out;
assign LED = IR[11:0];

always_comb
begin
	case(ADDR2MUX)
		2'b00: ADDR2_out = Imm11_ext;
		2'b01: ADDR2_out = Imm9_ext;
		2'b10: ADDR2_out = Imm6_ext;
		2'b11: ADDR2_out = 16'b0;
	endcase
end

always_comb
begin
	if(ADDR1MUX)
		ADDR1_out = PCR_out;
	else
		ADDR1_out = SR1_out;
end

always_comb                 
begin                       
	if(PCMUX == 2'b0)
		PC = PCR_out + 1;
	else if(PCMUX == 2'b01)
		PC = ADDR_out;
	else if(PCMUX == 2'b10)
		PC = bus;
	else
		PC = 16'bX;
end

always_comb                 
begin                       
	 if(MIO_EN == 1'b1)
		MDR_IN1 = MDR_In;
	 else
		MDR_IN1 = bus;
end

always_comb
begin
	if(!SR2MUX)
	   SR2_muxo = SR2_out;
	else
		SR2_muxo = Imm5_ext;
end

always_comb
begin
	if(bus[15] == 1'b1) 
	begin
		N = 1'b1;
		Z = 1'b0;
		P = 1'b0;       
	end
	
	else if(bus == 16'b0)
	begin
		N = 1'b0;
		Z = 1'b1;
		P = 1'b0;
	end
	
	else
	begin
		N = 1'b0;
		Z = 1'b0;
		P = 1'b1;
	end
end

register PCR(.reset(Reset_ah), .LD_EN(LD_PC), .in(PC), .out(PCR_out), .Clk(Clk));
register MARR(.reset(Reset_ah), .LD_EN(LD_MAR), .in(bus), .out(MAR), .Clk(Clk));
register MDRR(.reset(Reset_ah), .LD_EN(LD_MDR), .in(MDR_IN1), .out(MDR), .Clk(Clk));
register IRR(.reset(Reset_ah), .LD_EN(LD_IR), .in(bus), .out(IR), .Clk(Clk));

ben ben(.Clk, .reset(Reset_ah), .LD_BEN, .BEN, .in(BEN_in)); 
ALU alu(.ALUK(ALUK), .A(SR1_out), .B(SR2_muxo), .ALU_out);
nzp nzp(.n(N), .z(Z), .p(P), .reset(Reset_ah), .LD_CC(LD_CC), .N_out(N_out), .Z_out(Z_out), .P_out(P_out), .Clk(Clk));
datapath d0 (.GatePC(GatePC), .GateMDR(GateMDR), .GateALU(GateALU), .GateMARMUX(GateMARMUX), .MAR(ADDR_out), .MDR(MDR), .ALU(ALU_out), .PC(PCR_out), .data(bus));
reg_file regf(.Clk(Clk), .LD_reg(LD_REG), .DR(DRMUX), .SR1(SR1MUX), .reset(Reset_ah), .IR1(IR[11:9]), .IR2(IR[8:6]), .SR2(IR[2:0]), .bus(bus), .SR1_out, .SR2_out); 


//// For week 1, hexdrivers will display IR. Comment out these in week 2.
//HexDriver hex_driver3 (IR[15:12], HEX3);
//HexDriver hex_driver2 (IR[11:8], HEX2);
//HexDriver hex_driver1 (IR[7:4], HEX1);
//HexDriver hex_driver0 (IR[3:0], HEX0);

//For week 2, hexdrivers will be mounted to Mem2IO
HexDriver hex_driver3 (hex_4[3][3:0], HEX3);
HexDriver hex_driver2 (hex_4[2][3:0], HEX2);
HexDriver hex_driver1 (hex_4[1][3:0], HEX1);
HexDriver hex_driver0 (hex_4[0][3:0], HEX0);

// The other hex display will show PC for both weeks.
HexDriver hex_driver7 (PCR_out[15:12], HEX7);
HexDriver hex_driver6 (PCR_out[11:8], HEX6);
HexDriver hex_driver5 (PCR_out[7:4], HEX5);
HexDriver hex_driver4 (PCR_out[3:0], HEX4);

// Connect MAR to ADDR, which is also connected as an input into MEM2IO.
// MEM2IO will determine what gets put onto Data_CPU (which serves as a potential
// input into MDR)
assign ADDR = { 4'b00, MAR }; //Note, our external SRAM chip is 1Mx16, but address space is only 64Kx16
assign MIO_EN = ~OE;

// You need to make your own datapath module and connect everything to the datapath
// Be careful about whether Reset is active high or low



// Our SRAM and I/O controller
Mem2IO memory_subsystem(
    .*, .Reset(Reset_ah), .ADDR(ADDR), .Switches(S),
    .HEX0(hex_4[0][3:0]), .HEX1(hex_4[1][3:0]), .HEX2(hex_4[2][3:0]), .HEX3(hex_4[3][3:0]),
    .Data_from_CPU(MDR), .Data_to_CPU(MDR_In),
    .Data_from_SRAM(Data_from_SRAM), .Data_to_SRAM(Data_to_SRAM)
);

// The tri-state buffer serves as the interface between Mem2IO and SRAM
tristate #(.N(16)) tr0(
    .Clk(Clk), .tristate_output_enable(~WE), .Data_write(Data_to_SRAM), .Data_read(Data_from_SRAM), .Data(Data)
);

// State machine and control signals
ISDU state_controller(
    .*, .Reset(Reset_ah), .Run(Run_ah), .Continue(Continue_ah),
    .Opcode(IR[15:12]), .IR_5(IR[5]), .IR_11(IR[11]),
    .Mem_CE(CE), .Mem_UB(UB), .Mem_LB(LB), .Mem_OE(OE), .Mem_WE(WE)
);

//sync button_sync[2:0] (Clk, {~Reset, ~Continue, ~Run}, {Reset_ah, Continue_ah, Run_ah});


endmodule