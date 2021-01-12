library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity dotprod is
	port(
		\init\	: in	std_logic;
		\done\	: out	std_logic;
		\result\	: out	std_logic_vector(31 downto 0);
		\clk\		: in	std_logic;
		\reset\	: in	std_logic;
		\clear\	: in	std_logic
	); 
end dotprod;

architecture behavior of dotprod is 
component reg_op
generic (
	w_in	: integer := 16;
	initial	: integer := 0
);
port (
        clk      : in	std_logic;
        reset    : in	std_logic;
        we       : in    std_logic := '1';
        I0       : in    std_logic_vector(w_in-1 downto 0);
        O0       : out   std_logic_vector(w_in-1 downto 0)
);
end component;

component block_ram_0 
generic ( 
        data_width          : integer := 0; 
        address_width	: integer := 12 
); 
port ( 
        clk                 : in	std_logic; 
        we                  : in	std_logic := '0'; 
        oe                  : in	std_logic := '1'; 
        address             : in	std_logic_vector(address_width-1 downto 0); 
        data_in             : in	std_logic_vector(data_width-1 downto 0) := (others => '0'); 
        data_out            : out	std_logic_vector(data_width-1 downto 0) 
); 
end component; 

component block_ram_1 
generic ( 
        data_width          : integer := 0; 
        address_width	: integer := 12 
); 
port ( 
        clk                 : in	std_logic; 
        we                  : in	std_logic := '0'; 
        oe                  : in	std_logic := '1'; 
        address             : in	std_logic_vector(address_width-1 downto 0); 
        data_in             : in	std_logic_vector(data_width-1 downto 0) := (others => '0'); 
        data_out            : out	std_logic_vector(data_width-1 downto 0) 
); 
end component; 

component counter 
generic (
        bits		: integer := 8;
        steps		: integer := 1;
        increment           : integer := 1;
        down                : integer := 0;
        condition           : integer := 0
);
port (
        input		: in	std_logic_vector(bits-1 downto 0);
        termination         : in	std_logic_vector(bits-1 downto 0);
        clk                 : in	std_logic;
        clk_en		: in	std_logic := '1';
        reset		: in	std_logic;
        load		: in	std_logic := '0';
        step		: out	std_logic;
        done		: out	std_logic;
        output		: out	std_logic_vector(bits-1 downto 0)
); 
end component; 

component if_lt_op_s
generic (
	w_in1	: integer := 16;
	w_in2	: integer := 16;
	w_out	: integer := 1
);
port (
	I0	: in	std_logic_vector(w_in1-1 downto 0);
	I1	: in	std_logic_vector(w_in2-1 downto 0);
	O0	: out	std_logic_vector(0 downto 0)
);
end component;

component add_op_s
generic (
	w_in1	: integer := 16;
	w_in2	: integer := 16;
	w_out	: integer := 32
);
port (
	I0	: in	std_logic_vector(w_in1-1 downto 0);
	I1	: in	std_logic_vector(w_in2-1 downto 0);
	O0	: out	std_logic_vector(w_out-1 downto 0)
);
end component;

constant \N\ : std_logic_vector(31 downto 0);
constant \const_0\ : std_logic_vector(31 downto 0);

signal \from_i_to_if_lt_op_s_0\	: std_logic_vector(31 downto 0);
signal \from_sum_to_add_op_s_1\	: std_logic_vector(31 downto 0);
signal \recursive_from_add_op_s_1_to_sum\	: std_logic_vector(31 downto 0);

begin
	\sum\: reg_op
	generic map (
		w_in => 32,
		initial => 0
	)
	port map (
		clk => \clk\,
		reset => \reset\,
		I0 => \const_0\,
		I0 => \recursive_from_add_op_s_1_to_sum\,
		O0 => \from_sum_to_add_op_s_1\,
		O0 => \result\
	);

	\a\: block_ram_0
	generic map (
		data_width => 0,
		address_width => 12
	)
	port map (
		clk => \clk\
	);

	\b\: block_ram_1
	generic map (
		data_width => 0,
		address_width => 12
	)
	port map (
		clk => \clk\
	);

	\i\: counter
	generic map (
		bits => 0,
		steps => 32,
		increment => 1,
		down => 0,
		condition => 0
	)
	port map (
		input => \const_0\,
		termination => \N\,
		clk => \clk\,
		reset => \reset\,
		output => \from_i_to_if_lt_op_s_0\
	);

	\if_lt_op_s_0\: if_lt_op_s
	generic map (
		w_in1 => 32,
		w_in2 => 32,
		w_out => 1
	)
	port map (
		I0 => \from_i_to_if_lt_op_s_0\,
		I1 => \N\
	);

	\add_op_s_1\: add_op_s
	generic map (
		w_in1 => 32,
		w_in2 => 32,
		w_out => 32
	)
	port map (
		I0 => \from_sum_to_add_op_s_1\,
		O0 => \recursive_from_add_op_s_1_to_sum\
	);

end behavior;