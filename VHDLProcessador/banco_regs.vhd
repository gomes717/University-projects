--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity banco_regs is
	port (	read_reg_a	:	in unsigned (2 downto 0);
			read_reg_b	:	in unsigned (2 downto 0);
			write_reg	:	in unsigned (2 downto 0);
			write_data	:	in unsigned (15 downto 0);
			wr_en		:	in std_logic;	
			clk			:	in std_logic;
			rst			:	in std_logic;
			read_data_a :	out unsigned (15 downto 0);
			read_data_b :	out unsigned (15 downto 0)
		);
end entity;

architecture a_banco_regs of banco_regs is
	component reg16bits is
		port(clk	  :	in std_logic;
		 	rst 	  :	in std_logic;
		 	wr_en	  :	in std_logic;
		 	data_in  :	in unsigned (15 downto 0);
		 	data_out : out unsigned (15 downto 0)
			);
	end component;

	signal data0, data1, data2, data3, data4, data5, data6, data7 : unsigned (15 downto 0);
	signal wr_en1, wr_en2, wr_en3, wr_en4, wr_en5, wr_en6, wr_en7 : std_logic;

	begin
		reg0 : reg16bits port map(clk => clk, rst => rst, wr_en => '0', data_in => write_data, data_out => data0);
		reg1 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en1, data_in => write_data, data_out => data1);
		reg2 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en2, data_in => write_data, data_out => data2);
		reg3 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en3, data_in => write_data, data_out => data3);
		reg4 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en4, data_in => write_data, data_out => data4);
		reg5 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en5, data_in => write_data, data_out => data5);
		reg6 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en6, data_in => write_data, data_out => data6);
		reg7 : reg16bits port map(clk => clk, rst => rst, wr_en => wr_en7, data_in => write_data, data_out => data7);

		read_data_a <= data0 when read_reg_a = "000" else
					   data1 when read_reg_a = "001" else 	
					   data2 when read_reg_a = "010" else
					   data3 when read_reg_a = "011" else
					   data4 when read_reg_a = "100" else
					   data5 when read_reg_a = "101" else
					   data6 when read_reg_a = "110" else
					   data7 when read_reg_a = "111" else
					   "0000000000000000";

		read_data_b <= data0 when read_reg_b = "000" else
					   data1 when read_reg_b = "001" else 	
					   data2 when read_reg_b = "010" else
					   data3 when read_reg_b = "011" else
					   data4 when read_reg_b = "100" else
					   data5 when read_reg_b = "101" else
					   data6 when read_reg_b = "110" else
					   data7 when read_reg_b = "111" else
					   "0000000000000000";

		wr_en1 <= '1' when wr_en = '1' and write_reg = "001" else
				  '0';
		wr_en2 <= '1' when wr_en = '1' and write_reg = "010" else
				  '0';
		wr_en3 <= '1' when wr_en = '1' and write_reg = "011" else
				  '0';				 
		wr_en4 <= '1' when wr_en = '1' and write_reg = "100" else
				  '0';
		wr_en5 <= '1' when wr_en = '1' and write_reg = "101" else
				  '0';
		wr_en6 <= '1' when wr_en = '1' and write_reg = "110" else
				  '0';
		wr_en7 <= '1' when wr_en = '1' and write_reg = "111" else
				  '0';

end architecture;