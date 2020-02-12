module carry_lookahead_adder
(
    input   logic[15:0]     A,
    input   logic[15:0]     B,
    output  logic[15:0]     Sum,
    output  logic           CO
);
    logic c0 = 1'b0;
	 logic c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16;
	 logic c_1, c_2, c_3, c_4, c_5, c_6, c_7, c_8, c_9, c_10, c_11, c_12, c_13, c_14, c_15;
	 logic p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15;
	 logic g0, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15, g16;
	 logic pg0, gg0, pg1, gg1, pg2, gg2;
	
	// First Carry-Lookahead Adder Block.
	full_adderlk FA0(.x(A[0]), .y(B[0]), .z(c0), .s(Sum[0]), .c(c1), .p(p0), .g(g0)); assign c_1 = g0|(p0&c0);
	full_adderlk FA1(.x(A[1]), .y(B[1]), .z(c_1), .s(Sum[1]), .c(c2), .p(p1), .g(g1)); assign c_2 = g1|(p1&c1);
	full_adderlk FA2(.x(A[2]), .y(B[2]), .z(c_2), .s(Sum[2]), .c(c3), .p(p2), .g(g2)); assign c_3 = g2|(p2&c2);
	full_adderlk FA3(.x(A[3]), .y(B[3]), .z(c_3), .s(Sum[3]), .c(c4), .p(p3), .g(g3));
	
	// Second Carry-Lookahead Adder Block.
   assign pg0 = (p0&p1&p2&p3);
   assign gg0 = (g3|(g2&p3)|(g1&p3&p2)|(g0&p3&p2&p2&p1));
   assign c_4 = gg0|(c0&pg0);	
	full_adderlk FA4(.x(A[4]), .y(B[4]), .z(c_4), .s(Sum[4]), .c(c5), .p(p4), .g(g4)); assign c_5 = g4|(p4&c4);
	full_adderlk FA5(.x(A[5]), .y(B[5]), .z(c_5), .s(Sum[5]), .c(c6), .p(p5), .g(g5)); assign c_6 = g5|(p5&c5);
	full_adderlk FA6(.x(A[6]), .y(B[6]), .z(c_6), .s(Sum[6]), .c(c7), .p(p6), .g(g6)); assign c_7 = g6|(p6&c6);
	full_adderlk FA7(.x(A[7]), .y(B[7]), .z(c_7), .s(Sum[7]), .c(c8), .p(p7), .g(g7));
   
	// Third Carry-Lookahead Adder Block.
   assign pg1 = (p4&p5&p6&p7);
   assign gg1 = (g7|(g6&p7)|(g5&p7&p6)|(g4&p7&p6&p5));
   assign c_8 = gg1|(gg0&pg1)|(c0&pg0&pg1);
   full_adderlk FA8(.x(A[8]), .y(B[8]), .z(c_8), .s(Sum[8]), .c(c9), .p(p8), .g(g8)); assign c_9 = g8|(p8&c8);
	full_adderlk FA9(.x(A[9]), .y(B[9]), .z(c_9), .s(Sum[9]), .c(c10), .p(p9), .g(g9)); assign c_10 = g9|(p9&c9);
	full_adderlk FA10(.x(A[10]), .y(B[10]), .z(c_10), .s(Sum[10]), .c(c11), .p(p10), .g(g10)); assign c_11 = g10|(p10&c10);
	full_adderlk FA11(.x(A[11]), .y(B[11]), .z(c_11), .s(Sum[11]), .c(c12), .p(p11), .g(g11));

	// Fourth Carry-Lookahead Adder Block
   assign pg2 = (p8&p9&p10&p11);
   assign gg2 = (g11|(g10&p11)|(g9&p11&p10)|(g8&p11&p10&p9));
   assign c_12 = gg2|(gg1&pg2)|(c0&pg2&pg1&pg0);
   full_adderlk FA12(.x(A[12]), .y(B[12]), .z(c_12), .s(Sum[12]), .c(c13), .p(p12), .g(g12)); assign c_13 = g12|(p12&c12);
	full_adderlk FA13(.x(A[13]), .y(B[13]), .z(c_13), .s(Sum[13]), .c(c14), .p(p13), .g(g13)); assign c_14 = g13|(p13&c13);
	full_adderlk FA14(.x(A[14]), .y(B[14]), .z(c_14), .s(Sum[14]), .c(c15), .p(p14), .g(g14)); assign c_15 = g14|(p14&c14);
	full_adderlk FA15(.x(A[15]), .y(B[15]), .z(c_15), .s(Sum[15]), .c(CO), .p(p15), .g(g15)); 
endmodule
