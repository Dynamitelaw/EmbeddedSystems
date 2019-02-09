// CSEE 4840 Lab 1: Display and modify the contents of a memory
//
// Spring 2019
//
// By: Jose Rubianes &
// Uni: jer2201

module lab1( input logic        CLOCK_50,

	     input logic [3:0] 	KEY, // Pushbuttons; KEY[0] is rightmost

	     // 7-segment LED displays; HEX0 is rightmost
	     output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5
	     );

   logic [3:0] 		      a;         // Address
   logic [7:0] 		      din, dout; // RAM data in and out
   logic 		      we;        // RAM write enable

   logic 		      clk;
   assign clk = CLOCK_50;

   hex7seg h0( .a(a),         .y(HEX5) ), // Leftmost digit
           h1( .a(dout[7:4]), .y(HEX3) ), // left middle
           h2( .a(dout[3:0]), .y(HEX2) ); // right middle


   //Instantiate controller module
   controller c(.clk(clk),
   		.KEY(KEY),
   		.dout(dout),
   		.a(a),
   		.din(din),
   		.we(we) );

   //Instantiate memory module
   memory m( .clk(clk),
   		.a(a),
   		.din(din),
   		.we(we),
   		.dout(dout) );

   assign HEX4 = 7'b111_1111; // Display a blank; LEDs are active-low
   assign HEX1 = 7'b111_1111;
   assign HEX0 = 7'b111_1111;

endmodule

module controller(input logic        clk,
		  input logic [3:0]  KEY,
		  input logic [7:0]  dout,
		  output logic [3:0] a,
		  output logic [7:0] din,
		  output logic 	     we);

   // Replace these with your code
   assign a = 8'b0;
   assign din = {KEY, ~KEY};
   assign we = 1'b1;

   //
   //always @(KEY[3] or KEY[2]) begin

   //end

endmodule

module hex7seg(input logic [3:0] a,
	       output logic [6:0] y);

   always @ (a) begin
   	case(a)
   		0 : y = 7'b100_0000;
			1 : y = 7'b111_1001;
			2 : y = 7'b010_0100;
			3 : y = 7'b011_0000;
			4 : y = 7'b001_1001;
			5 : y = 7'b001_0010;
			6 : y = 7'b000_0010;
			7 : y = 7'b111_1000;
			8 : y = 7'b000_0000;
			9 : y = 7'b001_1000;
   		default: y = 7'b000_0000;
   	endcase
   end

   //assign y = {a[2:0],a}; // Replace this with your code

endmodule

// 16 X 8 synchronous RAM with old data read-during-write behavior
module memory(input logic        clk,
	      input logic [3:0]  a,
	      input logic [7:0]  din,
	      input logic 	 we,
	      output logic [7:0] dout);

   logic [7:0] 			 mem [15:0];

   always_ff @(posedge clk) begin
      if (we) mem[a] <= din;
      dout <= mem[a];
   end

endmodule
