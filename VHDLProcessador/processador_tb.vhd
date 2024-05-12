library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity processador_tb is
end entity;

architecture a_processador_tb of processador_tb is
	component processador
		port (	rst		:	in  std_logic;
			clk		:	in 	std_logic;
			state	:	out unsigned (2 downto 0);	
			PC_o	:	out unsigned (6 downto 0);
			opcode	:	out unsigned (14 downto 0);
			reg1_o	:	out unsigned (15 downto 0);
			reg2_o	:	out unsigned (15 downto 0);	
			ula_o	:	out unsigned (15 downto 0);
			ram_o_top	:	out unsigned (15 downto 0)
		);
	end component;

	signal clk, rst			:	std_logic;
	signal state_s			:	unsigned(2 downto 0);
	signal PC_s				:	unsigned(6 downto 0);
	signal opcode_s			:	unsigned(14 downto 0);
	signal reg1_o, reg2_o 	:	unsigned(15 downto 0);
	signal ula_o 			:	unsigned(15 downto 0);

	begin
		uut	:	processador port map (clk => clk, rst => rst, PC_o => PC_s, opcode => opcode_s, state => state_s,
									  reg1_o => reg1_o, reg2_o => reg2_o, ula_o => ula_o);

		process
		begin
			clk <= '0';
			wait for 50 ns;
			clk <= '1';
			wait for 50 ns;
		end process;

		process
		begin
			rst <= '1';
			wait for 100 ns;
			rst <= '0';
			wait;
		end process;

		process
		begin
			wait for 150000 ns;
			wait;
		end process;
end architecture;