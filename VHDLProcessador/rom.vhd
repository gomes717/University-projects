--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rom is
	port(	clk		:	in std_logic;
			address :	in unsigned(6 downto 0);
			data	:	out unsigned(14 downto 0)
		);
end entity;

architecture a_rom of rom is
	type mem is array (0 to 127) of unsigned(14 downto 0);
	constant conteudo_rom : mem := (
				0 => "010000100000000", -- MOV R1 0
				1 => "010001000000000", -- MOV R2 0
				2 => "000100100000001",	-- ADD R1 1
				3 => "110000100100000",	-- MOV (R1) R1
				4 => "100100100100000", -- CMP R1, 32
				5 => "011100001111100", -- JMPR < -4
				6 => "010000100000010", -- MOV R1 2
				7 => "000100100000010",	-- ADD R1 2
				8 => "110000101000000",	-- MOV (R1) R2
				9 => "100100100100000", -- CMP R1, 32
				10 => "011100001111100", -- JMPR < -4
				11 => "010000100000011", -- MOV R1 3
				12 => "000100100000011", -- ADD R1 3
				13 => "110000101000000", -- MOV (R1) R2
				14 => "100100100100000", -- CMP R1, 32
				15 => "011100001111100", -- JMPR < -4
				16 => "010000100000101", -- MOV R1 5
				17 => "000100100000101", -- ADD R1 5
				18 => "110000101000000", -- MOV (R1) R2
				19 => "100100100100000", -- CMP R1, 32
				20 => "011100001111100", -- JMPR < -4
				21 => "010000100000111", -- MOV R1 7
				22 => "000100100000111", -- ADD R1 7
				23 => "110000101000000", -- MOV (R1) R2
				24 => "100100100100000", -- CMP R1, 32
				25 => "011100001111100", -- JMPR < -4
				26 => "010000100001011", -- MOV R1 11
				27 => "000100100001011", -- ADD R1 11
				28 => "110000101000000", -- MOV (R1) R2
				29 => "100100100100000", -- CMP R1, 32
				30 => "011100001111100", -- JMPR < -4
				31 => "010000100000010", -- MOV R1 2
				32 => "000100100000001", -- ADD R1 1
				33 => "100100100100000", -- CMP R1, 32
				34 => "011100001111101", -- JMPR < -4
			others => (others => '0')
		);
	begin
		process(clk)
		begin
			if(rising_edge(clk)) then
				data <= conteudo_rom(to_integer(address));
			end if;
		end process;
	end architecture;