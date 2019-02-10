// CSEE 4840 Lab 1: Display and modify the contents of a memory
//
// Spring 2019
//
// By: Jose Rubianes &
// Uni: jer2201

module lab1( input logic		  CLOCK_50,

		  input logic [3:0] 	KEY, // Pushbuttons; KEY[0] is rightmost

		  // 7-segment LED displays; HEX0 is rightmost
		  output logic [6:0] HEX0, HEX1, HEX2, HEX3, HEX4, HEX5
		  );

	logic [3:0] a = 4'b0000;// Address
	logic [7:0] din, dout; // RAM data in and out
	logic we; // RAM write enable

	logic 				clk;
	assign clk = CLOCK_50;

	
	//Instantiate hex decoders
	hex7seg h0( .a(a),.y(HEX0) ), // rightmost digit
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
	assign HEX5 = 7'b111_1111;

endmodule

module controller(input logic clk,
		  input logic [3:0] KEY,
		  input logic [7:0] dout,
		  output logic [3:0] a,
		  output logic [7:0] din,
		  output logic we);

	// Replace these with your code
	//assign a = 8'b0;
	//assign din = {KEY, ~KEY};
	assign we = 1'b1;
	
	
	//Debounce button inputs 
	wire KEY3db;
	wire KEY2db;
	wire KEY1db;
	wire KEY0db;
	
	debouncer db3(.clk(clk), .buttonIn(KEY[3]), .buttonOut(KEY3db));
	debouncer db2(.clk(clk), .buttonIn(KEY[2]), .buttonOut(KEY2db));
	debouncer db1(.clk(clk), .buttonIn(KEY[1]), .buttonOut(KEY1db));
	debouncer db0(.clk(clk), .buttonIn(KEY[0]), .buttonOut(KEY0db));
	
	//Signal for when an address has been changed
	reg addressButtonPressed;
	assign addressButtonPressed = !KEY3db || !KEY2db;
	
	//Incriment or decriment address value
	always @(posedge addressButtonPressed) begin  
		if (!KEY3db) begin
			a <= a + 1;
		end
		else if (!KEY2db) begin
			a <= a - 1;	
		end	
	end
	
	//Signal for when an data been changed
	reg dataButtonPressed;
	assign dataButtonPressed = !KEY1db || !KEY0db;
	
	//Incriment or decriment data value
	//assign we = dataButtonPressed;
	always @(posedge dataButtonPressed) begin  
		if (!KEY1db) begin
			din <= dout + 1;
		end
		else if (!KEY0db) begin
			din <= dout - 1;	
		end	
	end

endmodule

//Seven segment hex decoder
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
			10 : y = 7'b000_1000;  //a
			11 : y = 7'b000_0011;  //b
			12 : y = 7'b100_0110;  //c
			13 : y = 7'b010_0001;  //d
			14 : y = 7'b000_0110;  //e
			15 : y = 7'b000_1110;  //f
			default: y = 7'b011_1111;
		endcase
	end
endmodule

// 16 X 8 synchronous RAM with old data read-during-write behavior
module memory(input logic clk,
		input logic [3:0]  a,
		input logic [7:0]  din,
		input logic we,
		output logic [7:0] dout);

	logic [7:0] 			 mem [15:0];

	always_ff @(posedge clk) begin
		if (we) mem[a] <= din;
		dout <= mem[a];
	end

endmodule

//Debouncer for push buttons
module debouncer(input clk, input buttonIn, output reg buttonOut);
	reg[20:0] timer = 0;
	always @(posedge clk)
		timer <= timer - 1'b1;
	always @(posedge clk)
		if (timer == 0)
			buttonOut <= buttonIn;

endmodule
