module full_adder (input x, y, z, output s, c);
  assign s = x^y^z;
  assign c = (x&y)|(y&z)|(x&z);
endmodule

module full_adderlk (input x, y, z, output s, c, p, g);
  assign s = x^y^z;
  assign c = (x&y)|(y&z)|(x&z);
  assign g = x&y;
  assign p = x^y;
endmodule

module carry_select(input z,
						  input [3:0] A, B,
						  output c,
						  output [3:0] Sum);
	logic c1, c2, c3;
	full_adder FA0(.x(A[0]), .y(B[0]), .z(z), .s(Sum[0]), .c(c1));
	full_adder FA1(.x(A[1]), .y(B[1]), .z(c1), .s(Sum[1]), .c(c2));
	full_adder FA2(.x(A[2]), .y(B[2]), .z(c2), .s(Sum[2]), .c(c3));
	full_adder FA3(.x(A[3]), .y(B[3]), .z(c3), .s(Sum[3]), .c(c4));  
	assign c = c4;			  			  
endmodule