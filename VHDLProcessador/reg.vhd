--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity reg is
	port(clk	  	:	in std_logic;
		 rst 	  	:	in std_logic;
		 wr_en	  	:	in std_logic;
		 data_in  	:	in unsigned (14 downto 0);
		 data_out	:	out unsigned (14 downto 0);
		 cte		:	out unsigned (7 downto 0);
		 add_jmp    :	out unsigned (6 downto 0);
		 ALUop		:	out unsigned (4 downto 0);
		 instr		:	out unsigned (3 downto 0);
		 read_reg_a	:	out unsigned (2 downto 0);
		 read_reg_b	:	out unsigned (2 downto 0);
		 BranchOp   :   out unsigned (3 downto 0);
		 state 		:	in unsigned (2 downto 0);
		 flagEn		:	out std_logic;
		 REGscr		:	out std_logic;
		 ram_add	:	out unsigned (6 downto 0);
		 RAMread	:	out std_logic
		);
end entity;

architecture a_reg of reg is
	signal registro : unsigned(14 downto 0);
	signal instr_s 	: unsigned(3 downto 0);
	begin

		process(clk, rst, wr_en)
		begin
			if rst = '1' then
				registro <= "000000000000000";
			end if;
			if rising_edge(clk) then
				if wr_en = '1' then
					registro <= data_in;
				end if;
			end if;
		end process;

		instr_s <= registro(14 downto 11);
		instr <= instr_s;
		read_reg_a <= registro(10 downto 8);
		read_reg_b <= registro(7 downto 5);
		cte <= registro(7 downto 0);
		add_jmp <= registro(6 downto 0);
		ALUop <= registro(4 downto 0) when instr_s = "0000" else
				 "00000" when instr_s = "0001" else
				 "00001" when instr_s = "0010" else
				 "00011" when instr_s = "0011" else
				 "00100" when instr_s = "0101" else
				 "10000" when instr_s = "0100" else
				 "01000" when instr_s = "1001" else  
				 "01000" when instr_s = "1010" else  
				 "01000" when instr_s = "1011" else  
				 "11000" when instr_s = "1100" else
				 "00001";

		flagEn <= '1' when instr_s = "0000" and registro(4 downto 0) /= "10000" and state = "011" else
				  '1' when instr_s = "0001" and state = "010" else
				  '1' when instr_s = "0010" and state = "010" else
				  '1' when instr_s = "1001" and state = "010" else
				  '0';

		BranchOp <= registro(10 downto 7) when instr_s = "0111" else
					"1111";

		data_out <= registro;

		ram_add <= registro(6 downto 0);

		REGscr <= '1' when instr_s = "1010" or instr_s = "1101" else
				  '0';

		RAMread <= '1' when instr_s = "1100" else
				   '0';

end architecture;