--------------------------------------------------------------
--															--
--		Autores: Gabriel Buiar e Guilherme Gomes     		--
--															--
--------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pc is
	port(clk	  :	in std_logic;
		 rst 	  : in std_logic;
		 wr_en	  :	in std_logic;
		 data_i   :	in unsigned (6 downto 0);
		 data_o   : out unsigned (6 downto 0)
		);
end entity;

architecture a_pc of pc is
	signal registro : unsigned(6 downto 0) := "0000000";
	begin

		process(clk, wr_en, rst)
		begin
			if rst = '1' then
				registro <= "0000000";
			elsif rising_edge(clk) then
				if wr_en = '1' then
					registro <= data_i;
				end if;
			end if;
		end process;

		data_o <= registro;
end architecture;