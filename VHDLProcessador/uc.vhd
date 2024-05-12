--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity uc is
	port (	clk			:	in std_logic;
			state 		:	in unsigned (2 downto 0);
			instr		:	in unsigned (3 downto 0);
			flag_i      :   in unsigned (1 downto 0);
			zero		:	in std_logic;
			carry		:	in std_logic;
			rst			:	in std_logic;
			branchop	:   in unsigned (3 downto 0);
			jump_en 	:	out std_logic;
			PCWrite		:	out std_logic;
			IRWrite		:	out std_logic;
			ALUen		:	out std_logic;
			ALUScrB		:	out std_logic;
			PCScr		:	out unsigned (1 downto 0);
			RegWrite	:   out std_logic;
			BranchEn    :   out std_logic;
			RAMen		:	out std_logic;
			RAMsrc		:	out std_logic
		);
end entity;

architecture a_uc of uc is

	signal instr_s 	:	unsigned (3 downto 0);
	signal registro :   unsigned (1 downto 0);

	begin



		instr_s <= instr;

		jump_en <= '1' when instr_s = "1111" else
				   '0';

		PCWrite <= '1' when state = "010" else
				 '0';

		IRWrite <= '1' when state = "010" else
				 '0';

		ALUen <= '1' when state = "010" else
				 '0';

		ALUScrB <= '0' when instr = "0000" or instr = "1100" else
				   '1';

		PCScr <= "01" when instr = "1000"  and state = "001" else
				 "10" when instr = "0111"  and branchop = "0000" and zero = '0' and carry = '0' else --blt
				 "10" when instr = "0111"  and branchop = "0001" and zero = '0' and carry = '1' else --bgt
			     "10" when instr = "0111"  and branchop = "0010" and zero = '1' and carry = '0' else -- beq 
				 "00";

		RegWrite <= '1' when state = "010"  and not (instr = "1000" or instr = "0111" or instr = "1100") else
					'0';

		BranchEn <= '1' when instr = "0111" else
					'0';

		RAMen <= '1' when state = "010" and instr = "1011" else
				 '1' when state = "010" and instr = "1100" else
				 '0';

		RAMsrc <= '1' when instr = "1100" else
				  '0';

end architecture;