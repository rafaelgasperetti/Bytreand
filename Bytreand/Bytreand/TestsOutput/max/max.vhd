library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity max is
	port(
		\init\	: in	std_logic;
		\done\	: out	std_logic;
		\result\	: out	std_logic_vector(31 downto 0);
		\clk\		: in	std_logic;
		\reset\	: in	std_logic;
		\clear\	: in	std_logic
	); 
end max;

architecture behavior of max is 
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

component if_gt_op_s
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

constant \N\ : std_logic_vector(31 downto 0);
constant \const_0\ : std_logic_vector(31 downto 0);

signal \from_i_to_if_lt_op_s_1\	: std_logic_vector(31 downto 0);
signal \from_v_to_if_gt_op_s_3\	: std_logic_vector(31 downto 0);
signal \i_address_to_v\	: std_logic_vector(11 downto 0);
signal \from_v_to_if_gt_op_s_3\	: std_logic_vector(31 downto 0);
signal \i_address_to_v\	: std_logic_vector(11 downto 0);

begin
	\v\: block_ram_0
	generic map (
		data_width => 0,
		address_width => 12
	)
	port map (
		clk => \clk\,
		address => \i_address_to_v\,
		address => \i_address_to_v\,
		data_out => \from_v_to_if_gt_op_s_3\,
		data_out => \from_v_to_if_gt_op_s_3\
	);

	\maxval\: reg_op
	generic map (
		w_in => 32,
		initial => 0
	)
	port map (
		clk => \clk\,
		reset => \reset\,
		I0 => \\const_0\\,
		O0 => \result\
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
,
		termination => \N\,
		clk => \clk\,
		reset => \reset\,
		output => \from_i_to_if_lt_op_s_1\,
		output(11 downto 0) => \i_address_to_v\(11 downto 0),
		output(11 downto 0) => \i_address_to_v\(11 downto 0)
	);

	\if_lt_op_s_1\: if_lt_op_s
	generic map (
		w_in1 => 32,
		w_in2 => 32,
		w_out => 1
	)
	port map (
		I0 => \from_i_to_if_lt_op_s_1\,
		I1 => \N\
	);

	\if_gt_op_s_3\: if_gt_op_s
	generic map (
		w_in1 => 32,
		w_in2 => 32,
		w_out => 1
	)
	port map (
		I0 => \from_v_to_if_gt_op_s_3\		I0 => \from_v_to_if_gt_op_s_3\
	);

end behavior;